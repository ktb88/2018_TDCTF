#!/usr/bin/python
#-*- coding:utf-8 -*-
import os
import sys
import time
import hashlib
from struct import pack, unpack
from flag import FLAG

p32 = lambda x: pack("<I", x)
u32 = lambda x: unpack("<I", x)[0]

def ws(msg):
	sys.stdout.write(msg)
	sys.stdout.flush()
	time.sleep(0.1)

salt = 20372966

def load_maps():
	maps_dir = os.listdir("/home/onmyway/maps")

	for i in range(0, 101):
		hash_msg = "%d%d" % (salt, i)
		hash_sha256 = hashlib.sha256(hash_msg).hexdigest()
		hash_maps[hash_sha256] = i

	for i in range(0, 10):
		file_name = "/home/onmyway/maps/%d.map" % (i)
		dict_name = "%d" % (i)
		with open(file_name, "r") as fd:
			data = fd.read().splitlines()

			# ['5 3 0', '#####', '#G.S#', '#####']
			tmp = data[0].split(" ")
			maps[dict_name] = {}
			maps[dict_name]["info"] = {}
			maps[dict_name]["info"]["x"] = int(tmp[0])
			maps[dict_name]["info"]["y"] = int(tmp[1])
			maps[dict_name]["info"]["c"] = int(tmp[2])
			maps[dict_name]["map"] = data[1:]

			for j in range(1, len(data)):
				if "S" in data[j]:
					maps[dict_name]["start_x"] = data[j].index("S")
					maps[dict_name]["start_y"] = j-1
					break

	for cmd in ["U", "L", "D", "R", "Q"]:
		hash_msg = "%d%c" % (salt, cmd)
		hash_sha256 = hashlib.sha256(hash_msg).hexdigest()
		hash_maps[hash_sha256] = cmd

def chk_block(y, x, map_name):
	if maps[map_name]["map"][y][x] == "#":
		return True
	return False

def game_start():
	current_level = 0
	p_x = -1
	p_y = -1

	ws("*: Current Location\nS: Starting Point\nG: Goal\n")
	ws("(L) Left, (D) Down, (R) Right, (U) Up, (Q) Quit\n")

	while 1:
		ws("LEVEL : %d / %d\n" % (current_level, 9))
		map_name = "%d" % (current_level)

		if p_x == -1 or p_y == -1:
			p_x = maps[map_name]["start_x"]
			p_y = maps[map_name]["start_y"]
			map_x = maps[map_name]["info"]["x"]
			map_y = maps[map_name]["info"]["y"]
			map_c = maps[map_name]["info"]["c"]

		show_s_x = p_x - 2
		if show_s_x < 0: show_s_x = 0
		show_e_x = p_x + 2
		if show_e_x >= map_x: show_e_x = map_x

		show_s_y = p_y - 2
		if show_s_y < 0: show_s_y = 0
		show_e_y = p_y + 2
		if show_e_y >= map_y: show_e_y = map_y

		show_data = ''
		for y in range(show_s_y, show_e_y):
			for x in range(show_s_x, show_e_x):
				if p_x == x and p_y == y:
					show_data += "*"
				else:
					b = maps[map_name]["map"][y][x]
					if b == "E" or b == "C":
						show_data += " "
					else:
						show_data += maps[map_name]["map"][y][x]
			show_data += "\n"

		ws(p32(0xdeadbeef) + p32(current_level) + p32(p_x) + p32(p_y) + show_data + "\n")
		data = raw_input()
		len_data = len(data)
		for i in range(0, len_data):
			if data[i:i+0x40] in hash_maps:
				data = data[i:]
				break

		if len(data) < 0x40*4:
			sys.stdin.flush()
			continue

		hash_cmd = data[0:0x40]
		hash_level = data[0x40:0x80]
		hash_x = data[0x80:0xc0]
		hash_y = data[0xc0:0x100]
		cmd = None
		level = None
		temp_x = None
		temp_y = None

		if hash_cmd in hash_maps:
			cmd = hash_maps[hash_cmd]
		if hash_level in hash_maps:
			level = hash_maps[hash_level]
		if hash_x in hash_maps:
			temp_x = hash_maps[hash_x]
		if hash_y in hash_maps:
			temp_y = hash_maps[hash_y]

		if level is None or temp_x is None or temp_y is None:
			ws("w...what the ... what the hell are you doing?? Don't do that :(\n")
			ws("recv data [%s]\n" % (data.encode("hex")))
			continue

		if hash_cmd is None:
			ws("[*] only 'L', 'D', 'R', 'U', 'Q' is allowed\n\n")
			continue

		if cmd == 'Q':
			ws("bye :P\n\n")
			exit(0)

		p_x = temp_x
		p_y = temp_y
		current_level = level

		if cmd == "L":
			if p_x - 1 >= 0:
				if chk_block(p_y, p_x-1, map_name) == False:
					p_x -= 1
		elif cmd == "R":
			if p_x + 1 < map_x:
				if chk_block(p_y, p_x+1, map_name) == False:
					p_x += 1
		elif cmd == "U":
			if p_y - 1 >= 0:
				if chk_block(p_y-1, p_x, map_name) == False:
					p_y -= 1
		elif cmd == "D":
			if p_y + 1 < map_y:
				if chk_block(p_y+1, p_x, map_name) == False:
					p_y += 1

		if maps[map_name]["map"][p_y][p_x] == "G":
			current_level += 1
			ws("Yep! Go to the next floor\n")
			p_y = -1
			p_x = -1

			if current_level > 10 or current_level < 0:
				ws("I think you are cheeter. GET OUT! :(\n")
				exit(-1)

			if current_level == 10:
				ws("Congratz!! Here is your prize :)\n")
				ws(FLAG + "\n")
				break

if __name__ == "__main__":
	maps = {}
	hash_maps = {}
	load_maps()
	game_start()

