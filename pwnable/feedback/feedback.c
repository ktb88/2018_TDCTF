// gcc feedback. -o feedback && strip feedback
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define MAX_FILENAME_SIZE 128
#define MAX_MODE_SIZE 1024
#define MAX_MSG_SIZE 256
#define MAX_LIST 10

typedef struct _t_feedback
{
	char msg[MAX_MSG_SIZE];
	void (*print_ptr)(char *);
	unsigned int nLen;
}t_feedback;

t_feedback *g_ptr[MAX_LIST];
unsigned int nList;

int handle_feedback();
int show_feedback();
int delete_feedback();
int modify_feedback();
int print_menu();
int init();
unsigned int get_num();
void print_msg(char *);

int main()
{
	unsigned int idx;

	init();

	while (1) {
		print_menu();
		idx = get_num();
		switch( idx ) {
			case 1:
				handle_feedback();
				break;
			case 2:
				show_feedback();
				break;
			case 3:
				delete_feedback();
				break;
			case 4:
				modify_feedback();
				break;
			case 5:
				printf("Bye~\n");
				return 0;
			default:
				printf("wrong input :(\n");
				break;
		}
	}
	return 0;
}

int init() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);

	if (mkdir("tmp", 0777) == -1 && errno != EEXIST) {
		printf("Oops! please, let me know this issue (hackability@naver.com)\n");
		exit(-1);
	}

	return 0;
}

int handle_feedback() {
	char filename[MAX_FILENAME_SIZE] = {0,};
	char finalPath[MAX_FILENAME_SIZE+32] = {0,};
	char mode[MAX_MODE_SIZE] = {0,};
	char msg[MAX_MSG_SIZE] = {0,};
	FILE *fp = NULL;

	printf("File Name : ");
	read(0, filename, MAX_FILENAME_SIZE-1);

	printf("Mode : ");
	read(0, mode, MAX_MODE_SIZE-1);

	if (strstr(filename, "/") != NULL ||
		strstr(filename, ".") != NULL) {
		printf("filtered ! \n");
		return -1;
	}

	strcpy(finalPath, "tmp/");
	strcat(finalPath, filename);

	fp = fopen(finalPath, mode);
	if (fp == NULL) {
		printf("fopen failed\n");
		return -2;
	}

	unsigned int nRead;
	if (mode[0] == 'r') {
		fread(msg, MAX_MSG_SIZE, 1, fp);
		printf("Message : %s\n", msg);
	} else if (mode[0] == 'w') {
		if (nList >= MAX_LIST) {
			printf("feedback is full... sorry :(\n");
			return -3;
		}

		t_feedback *ptr;
		ptr = (t_feedback *)malloc(sizeof(t_feedback));

		printf("Message : ");
		nRead = read(0, msg, MAX_MSG_SIZE-1);
		fwrite(msg, nRead, 1, fp);

		memcpy(ptr->msg, msg, nRead);
		ptr->print_ptr = &print_msg;
		ptr->nLen = nRead;

		for (int i=0 ; i<MAX_LIST ; i++)
			if (g_ptr[i] == NULL) {
				g_ptr[i] = ptr;
				nList++;
				break;
			}
	}

	printf("handling done\n");
	fclose(fp);
	return 0;
}

int show_feedback() {
	unsigned int idx;

	printf("Feedback index : ");
	idx = get_num();

	if (! (idx >= 0 && idx <MAX_LIST)) {
		printf("range error: 0 ~ 9\n");
		return -1;
	}

	if (g_ptr[idx] == NULL) {
		printf("The feedback is not available! \n");
		return -2;
	}

	g_ptr[idx]->print_ptr(g_ptr[idx]->msg);
	return 0;
}

int delete_feedback() {
	unsigned int idx;

	printf("Feedback index : ");
	idx = get_num();

	if (! (idx >= 0 && idx <MAX_LIST)) {
		printf("range error: 0 ~ 9\n");
		return -1;
	}

	if (g_ptr[idx] == NULL) {
		printf("The feedback is not available! \n");
		return -2;
	}

	memset(g_ptr[idx], 0, sizeof(t_feedback));
	free(g_ptr[idx]);
	return 0;
}

int modify_feedback() {
	unsigned int idx;

	printf("Feedback index : ");
	idx = get_num();

	if(! (idx >= 0 && idx <MAX_LIST)) {
		printf("range error: 0 ~ 9\n");
		return -1;
	}

	if (g_ptr[idx] == NULL) {
		printf("The feedback is not available! \n");
		return -2;
	}

	printf("message : ");
	read(0, g_ptr[idx]->msg, g_ptr[idx]->nLen);
	printf("Done!\n");
	return 0;
}

void print_msg(char *msg) {
	printf("message: %s\n", msg);
}

unsigned int get_num()
{
	char buf[8] = {0,};
	read(0, buf, 8-1);
	return atoi(buf);
}

int print_menu()
{
	printf("\t$10 Feedback Service \n");
	printf("1) Create Feedback \n");
	printf("2) Show Feedback \n");
	printf("3) Delete Feedback \n");
	printf("4) Modify Feedback \n");
	printf("5) Exit \n");
	printf(">> ");
	return 0;
}

