#!/usr/local/bin/python
from scapy.all import *

src="10.211.55.2"
pcap_file = './ping_ping_ping.pcapng'
pcap = rdpcap(pcap_file)

f = open("raw_data.docx", 'wb')

data = ""
check_count = 0

for packet in pcap:
	check_count += 1

	if check_count % 2 == 0:
		continue
	else:
		ip_layer = packet.getlayer("IP")
		icmp_layer = packet.getlayer("ICMP")

		if packet.getlayer("Raw"):
			data += str(icmp_layer.payload)

f.write(data)
f.close()