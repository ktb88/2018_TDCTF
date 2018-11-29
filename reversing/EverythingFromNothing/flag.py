header = "ff08757d3c002006cf878a5f00554e47".decode("hex")
flag   = "TDCTF{_n0th1ng_}"

print len(header), len(flag)

res = ""
for i in range(0, len(header)):
	res += chr( ord(header[i]) ^ ord(flag[i]) )

print res, res.encode("hex")


