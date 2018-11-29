// gcc maze_client.c -pie -fpie -lssl -lcrypto -o onmyway
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define LEN_SHA256	64

int encrypt(char *p_recv, char *p_send, char ch, unsigned int rnd_seed) {
	SHA256_CTX context;

	char digest[LEN_SHA256/2+1] = {0,};
	char temp[LEN_SHA256*4+1] = {0,};
	char sha256string[LEN_SHA256+1] = {0,};
	unsigned int *ptr;

	memset(temp, 0, LEN_SHA256*4);
	sprintf(temp, "%u%c", rnd_seed, ch);

	SHA256_Init(&context);
	SHA256_Update(&context, temp, strlen(temp));
	SHA256_Final(digest, &context);

	memset(sha256string, 0, LEN_SHA256);
	for(int i=0 ; i<LEN_SHA256/2 ; i++)
		sprintf(&sha256string[i*2], "%02x", (unsigned char)digest[i]);
	memcpy(p_send, sha256string, LEN_SHA256);

	for(int i=1 ; i<4 ; i++)
	{
		memset(temp, 0, LEN_SHA256*4);
		memset(sha256string, 0, LEN_SHA256);

		ptr = (unsigned int *)(p_recv + 4 * i);
		sprintf(temp, "%u%u", rnd_seed, *ptr);

		SHA256_Init(&context);
		SHA256_Update(&context, temp, strlen(temp));
		SHA256_Final(digest, &context);

		for(int i=0 ; i<LEN_SHA256/2 ; i++)
			sprintf(&sha256string[i*2], "%02x", (unsigned char)digest[i]);
		memcpy(p_send+(LEN_SHA256*i), sha256string, (LEN_SHA256*i));
	}
	p_send[strlen(p_send)] = '\n';
	p_send[strlen(p_send)] = 0;
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("[USAGE] %s [SERVER IP]\n", argv[0]);
		return 0;
	}

	srand(31337);
	unsigned int rnd_seed = 0;
	int i, n;

	for (i=0 ; i<31337; i++)
		rnd_seed ^= rand();

	int sockfd = 0;
	struct sockaddr_in serv_addr;
	char recvBuf[1024];
	char sendBuf[1024];

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("[*] Fail to create socket\n");
        return 1;
    }

	memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(31337);

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
		printf("[*] Fail to get inet_pton\n");
        return 1;
    }

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
		printf("[*] Fail to connect the server \n");
       	return 1;
    }

    while ("RUN")
    {
		memset(recvBuf, 0, 1024);
		n = read(sockfd, recvBuf, sizeof(recvBuf)-1);
        recvBuf[n] = 0;

        if (n < 0) {
            printf("[*] recv error \n");
            return 1;
        }

		unsigned int offset = 0;
		unsigned int *p = recvBuf;
		char ch;

		if (*p == 0xdeadbeef)
			offset = 0x10;

		printf("%s\n", recvBuf + offset);

		if (*p == 0xdeadbeef) {
			do {
				ch = getchar();
				fflush(stdin);
			} while (ch != 'U' && ch != 'D' && ch != 'R' && ch != 'L' && ch != 'Q');
			memset(sendBuf, 0, 1024);
			encrypt(recvBuf, sendBuf, ch, rnd_seed);
			write(sockfd, sendBuf, strlen(sendBuf));
		}
    }

	return 0;
}

