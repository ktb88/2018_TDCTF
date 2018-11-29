import hashlib
from pwn import *

def gen_msg(cmd, lv, x, y, salt):
	hash_1 = hashlib.sha256("{}{}".format(salt, cmd)).hexdigest()
	hash_2 = hashlib.sha256("{}{}".format(salt, lv)).hexdigest()
	hash_3 = hashlib.sha256("{}{}".format(salt, x)).hexdigest()
	hash_4 = hashlib.sha256("{}{}".format(salt, y)).hexdigest()
	return "{}{}{}{}".format(hash_1, hash_2, hash_3, hash_4)

def search_goal():
	for y in range(1, 99, 2):
		for x in range(1, 99, 2):
			print "[Searching] {}.{}".format(x, y)

			res = gen_msg('R', 9, x, y, CONST_SALT)
			r.sendline(res)
			recv = r.recv()
			recv = r.recv()[0x10:]

			if "G" in recv:
				print "found it"
				print "x = {}, y = {}".format(x, y)
				print recv
				return x, y

r = remote("onmyway.tendollar.kr", 31337)

for _ in range(4):
	print r.recv()

CONST_SALT = 20372966

# find goal
print "[*] search for 'G'"
x, y = search_goal()

print "[*] input as cmd,x,y"
while True:
	data = raw_input("> ").rstrip()
	cmd = data.split(",")[0]
	x = data.split(",")[1]
	y = data.split(",")[2]
	print x, y

	msg = gen_msg(cmd, 9, x, y, CONST_SALT)
	r.sendline(msg)
	recv = r.recv()
	if "Yep! Go to the next floor" in recv:
		print r.recv()
		print r.recv()
		break

	print r.recv()[0x10:]

