// gcc source.c -Wl,-z,relro,-z,now -pie -fpie -o EFN
#include <unistd.h>
#include <stdlib.h>

char buf[17];
static void _dummy() __attribute__((destructor));

void wrong(){ write(1, "wrong!", 6); exit(0); }
void correct(){ write(1, "correct!", 8); exit(0); }

int main()
{
	read(0, buf, 16);
	return 0;
}

static void _dummy(){}
