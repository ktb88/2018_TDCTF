#coding: utf-8

from PIL import Image

def decrypt_png(png_name, output_name):
	img = Image.open(png_name, "r").convert("RGBA")
	width, height = img.size
	data = img.load()

	output = ""

	for w in range(0, width):
		for h in range(0, height):
			pixel = data[w, h]
			(r, g, b, a) = pixel
			output += chr(a)

	open(output_name, "wb").write(output)
	print "Fin"

# out.png is extracted from challenge.png
decrypt_png("out.png", "out.zip")
