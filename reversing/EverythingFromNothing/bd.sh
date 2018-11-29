gcc source.c -Wl,-z,relro,-z,now -pie -fpie -o source
python patch.py source
cp source.patch EFN
chmod +x EFN
