#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

void stage1();

void stage2();

void stage3();

void j_stage3();

int main() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    int fd = open("/dev/urandom", O_RDONLY);
    int64_t address = 0;
    read(fd, &address, 6);
    close(fd);
    int64_t offset = address & 0xff0;

    void *new_stack =
            mmap(address & 0x00000ffffffff000, 0x20000, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (new_stack != (void*)(address & 0x00000ffffffff000))
        exit(-1);

    asm volatile (
    "movq %0, %%rsp\n"
    "addq $0xff00, %%rsp\n"
    "addq %1, %%rsp\n"
    : "=r" (new_stack): "m" (offset)
    );
    asm volatile (
    "movq $0, %rbp\n"
    "movq $0, %rdi\n"
    "movq $0, %rsi\n"
    "movq $0, %rdx\n"
    "movq $0, %rcx\n"
    "movq $0, %r8\n"
    "movq $0, %r9\n"
    );
    stage1();
}

void stage1() {
    char *buffer = malloc(21);
    register int fd = open("/dev/urandom", O_RDONLY);
    register unsigned char *secret_bin = malloc(10);
    read(fd, secret_bin, 10);
    close(fd);

    char *secret = malloc(21);

    for (register size_t i = 0; i < 10; i++)
        snprintf(&secret[i * 2], 3, "%02hhx", secret_bin[i]);

    for (register size_t i = 0; i < 2; i++) {
        scanf("%20s", buffer);
        if (!strcmp(secret, buffer)) {
            asm volatile (
            "movq $0, %rbp\n"
            "movq $0, %rdi\n"
            "movq $0, %rsi\n"
            "movq $0, %rdx\n"
            "movq $0, %rcx\n"
            "movq $0, %r8\n"
            "movq $0, %r9\n"
            );
            stage2();
        }
        if (strchr(buffer, 'n') || strchr(buffer, '$'))
            exit(-1);

        asm volatile (
        "movq $0, %rsi\n"
        "movq $0, %rdx\n"
        "movq $0, %rcx\n"
        "movq $0, %r8\n"
        "movq $0, %r9\n"
        );
        printf(buffer);
    }
    exit(0);
}

void j_printf(register char *buffer) {
    printf(buffer);
}

void jj_printf(register char *buffer) {
    j_printf(buffer);
}

void jjj_printf(register char *buffer) {
    jj_printf(buffer);
}

void stage2() {
    puts("Congratulations!");
    register char *buffer = malloc(33);
    register char *secret2 = malloc(33);

    register int fd = open("/dev/urandom", O_RDONLY);
    register unsigned char *secret2_bin = malloc(16);
    read(fd, secret2_bin, 16);
    close(fd);
    for (register size_t i = 0; i < 16; i++)
        snprintf(&secret2[i * 2], 3, "%02hhx", secret2_bin[i]);

    for (register size_t i = 0; i < 6; i++) {
        scanf("%32s", buffer);
        if (!strcmp(secret2, buffer)) {
            asm volatile (
            "movq $0, %rbp\n"
            "movq $0, %rdi\n"
            "movq $0, %rsi\n"
            "movq $0, %rdx\n"
            "movq $0, %rcx\n"
            "movq $0, %r8\n"
            "movq $0, %r9\n"
            );
            j_stage3();
        }
        if (strchr(buffer, '$'))
            exit(-1);

        fd = open("/dev/urandom", O_RDONLY);
        register int64_t address = calloc(1, sizeof(address));
        read(fd, (int64_t *) address, 5);
        address = *(int64_t *) address;
        close(fd);
        address = (address << 12) & 0x00000ffffffff000;

        register void *temp_stack = mmap(address, 0x20000, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

        if (temp_stack != (void *) address)
            exit(-1);

        asm volatile (
        "addq $0x1f000, %0\n"
        "movq %0, %%rsp\n"
        : "=r" (temp_stack)
        );
        asm volatile (
        "movq $0, %rsi\n"
        "movq $0, %rdx\n"
        "movq $0, %rcx\n"
        "movq $0, %r8\n"
        "movq $0, %r9\n"
        );
        jjj_printf(buffer);
    }
    exit(0);
}

void j_stage3() {
    stage3();
}

void stage3() {
    puts("Congratulations!");
    const uint64_t prefix_length = 0x13041;
    uint64_t mi_address = 0;

    int fd = open("/dev/urandom", O_RDONLY);
    read(fd, &mi_address, 5);
    close(fd);

    mi_address = (mi_address << 12) & 0x0000fffffffff000;

    register char *command = calloc(16, 1);
    strcpy(command, "echo gogo");

    char *buffer = malloc(prefix_length + 33);;
    memset(buffer, '\r', prefix_length);

    size_t *const mi = mmap(mi_address, 0x1000, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (mi != (void *) mi_address)
        exit(-1);

    for (*mi = 1; *mi < 2; (*mi)++) {
        scanf("%32s", buffer + prefix_length);

        asm volatile (
        "movq $0, %rsi\n"
        "movq $0, %rdx\n"
        "movq $0, %rcx\n"
        "movq $0, %r8\n"
        "movq $0, %r9\n"
        );
        printf(buffer);

        system(command);
    }
    exit(0);
}