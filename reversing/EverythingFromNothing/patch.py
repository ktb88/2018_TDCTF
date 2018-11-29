from pwn import *
import sys
import random

def patch_fini():
	rel = e.get_section_by_name('.rela.dyn')
	print "rela.dyn :", hex(rel.header.sh_offset)
	print "first_landing:", hex(first_landing)

	# at 0x540
	print "searching for :", hex(fini_array_addr + 8)
	for _ in rel.iter_relocations():
		if _['r_offset'] == (0x200000 + fini_array_addr + 8):
			print _, hex(_['r_offset']), hex(_['r_addend'])

	e.write(0x540 + 0x10, p64(first_landing))
	print hexdump(e.read(0x530, 0x18))

def offset_of(section_name):
	return e.get_section_by_name(section_name).header.sh_addr

e = ELF(sys.argv[1])
print (e)

fini_array = e.get_section_by_name(".fini_array")
fini_array_addr = fini_array.header.sh_offset

eh_frame = e.get_section_by_name(".eh_frame")
eh_frame_addr = eh_frame.header.sh_addr
print "eh_frame addr :", hex(eh_frame_addr)

#do_mprotect = eh_frame_addr + 217 + 5 + 20
#print "do_mprotect :", hex(do_mprotect)

first_landing = eh_frame_addr + 0x80
print "first landing :", hex(first_landing)

get_buf_addr = e.symbols['buf']
wrong = e.symbols['wrong']
correct = e.symbols['correct']
print "wrong : ", hex(wrong), "correct : ", hex(correct)

patch_fini()
note = e.get_section_by_name(".note.gnu.build-id")
note_addr = note.header.sh_addr

print "note addr:", hex(note_addr)
# 0x180 = 192
#e.write(first_landing+0x180, "ab4c36297a7b7f68fff3e26e6e32113a".decode("hex"))
#open("dump","wb").write("0313fd0e60dafc5943a7627300554e47".decode("hex")[::-1])
flag = "b9f98dde25fdedc81273721300554e47"
open("dump","wb").write(flag.decode("hex")[::-1])
print flag

def tsc(sh):
	n = random.randint(1, 4)*4
	_ = asm(sh, arch='amd64')
	_ += asm("jmp $+{}".format(n+2), arch='amd64')
	_ += "\x00" * n
	return _

#xor byte ptr [rbx + 0x24], 0x9f

# patch do mprotect

sc = ""
sc += tsc("mov rdi, [rbx]")
sc += tsc("mov rsi, rdi")
sc += tsc("add rsi, {}".format(note_addr + 0xc))
sc += tsc("movdqu xmm0, XMMWORD PTR [rsi]")
sc += tsc("mov rsi, rdi")
sc += tsc("add rsi, {}".format(get_buf_addr))
sc += tsc("movdqu xmm1, XMMWORD PTR [rsi]")
sc += tsc("ucomisd xmm1, xmm0")

_sc = '''
  je ok
  mov rcx, 0x100
loop:
  push 0
  dec rcx
  test rcx, rcx
  jz wrong
  jmp loop
wrong:
  add rdi, {}
  mov rax, 0
  mov r12, 3
  mov rbp, 0
  jmp rdi
ok:
  add rdi, {}
  jmp rdi
'''.format(wrong, correct)
sc += asm(_sc, arch='amd64')
print disasm(sc, arch='amd64')

e.write(first_landing, sc)

print "note addr :", hex(note_addr+0xc)
print hexdump(e.read(note_addr+0xc, 16))

e.save(sys.argv[1] + ".patch")
