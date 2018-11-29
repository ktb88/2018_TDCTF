// gcc sb_school_1.c -o sb1
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

int main()
{
	void (*sc)();
	void *shellcode;

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);

	shellcode = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (shellcode == MAP_FAILED) {
		printf("[err] Please, let me know this issue (hackability@naver.com)\n");
		return -1;
	}

	printf("[*] Welcome to sandbox school for beginner!\n");
	printf("[*] Put your shellcode as binary stream. I'll ready for your input as read(0, shellcode, 1024)\n");
	printf("[*] Lv   : Gate\n");
	printf("[*] Desc : Can you enter this world ?\n");
	printf("> ");

	alarm(10);

	read(0, shellcode, 1024);
	sc = shellcode;
	sc();	
	
	return 0;
}
