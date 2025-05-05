#include "io.h"
#include <stddef.h>

#define MAXARG 10

void mmio_write(uint32_t reg, uint32_t data)
{
    *(volatile uint32_t*)reg = data;
}

uint32_t mmio_read(uint32_t reg)
{
    return *(volatile uint32_t*)reg;
}

// Loop <delay> times in a way that the compiler won't optimize away
void delay(int32_t count)
{
    asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
            : "=r"(count): [count]"0"(count) : "cc");
}

enum
{
    // The GPIO registers base address.
    GPIO_BASE = 0x3F200000, // for raspi2 & 3, 0x20200000 for raspi1

    GPPUD = (GPIO_BASE + 0x94),
    GPPUDCLK0 = (GPIO_BASE + 0x98),

    // The base address for UART.
    UART0_BASE = 0x3F201000, // for raspi2 & 3, 0x20201000 for raspi1

    UART0_DR     = (UART0_BASE + 0x00),
    UART0_RSRECR = (UART0_BASE + 0x04),
    UART0_FR     = (UART0_BASE + 0x18),
    UART0_ILPR   = (UART0_BASE + 0x20),
    UART0_IBRD   = (UART0_BASE + 0x24),
    UART0_FBRD   = (UART0_BASE + 0x28),
    UART0_LCRH   = (UART0_BASE + 0x2C),
    UART0_CR     = (UART0_BASE + 0x30),
    UART0_IFLS   = (UART0_BASE + 0x34),
    UART0_IMSC   = (UART0_BASE + 0x38),
    UART0_RIS    = (UART0_BASE + 0x3C),
    UART0_MIS    = (UART0_BASE + 0x40),
    UART0_ICR    = (UART0_BASE + 0x44),
    UART0_DMACR  = (UART0_BASE + 0x48),
    UART0_ITCR   = (UART0_BASE + 0x80),
    UART0_ITIP   = (UART0_BASE + 0x84),
    UART0_ITOP   = (UART0_BASE + 0x88),
    UART0_TDR    = (UART0_BASE + 0x8C),
};

void uart_init()
{
    mmio_write(UART0_CR, 0x00000000);

    mmio_write(GPPUD, 0x00000000);
    delay(150);

    mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);

    mmio_write(GPPUDCLK0, 0x00000000);

    mmio_write(UART0_ICR, 0x7FF);

    mmio_write(UART0_IBRD, 1);
    mmio_write(UART0_FBRD, 40);

    mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

    mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
            (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

    mmio_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}

void uart_putc(unsigned char c)
{
    while ( mmio_read(UART0_FR) & (1 << 5) ) { }
    mmio_write(UART0_DR, c);
}

unsigned char uart_getc()
{
    while ( mmio_read(UART0_FR) & (1 << 4) ) { }
    return mmio_read(UART0_DR);
}

void uart_puts(const char* str)
{
    for (size_t i = 0; str[i] != '\0'; i ++)
        uart_putc((unsigned char)str[i]);
}

//read a string from user
void uart_gets(char *buffer, int max_len) {
    int i = 0;
    while (i < max_len - 1) {
        char c = uart_getc();
        uart_putc(c); // echo back
        if (c == '\r' || c == '\n')
            break;
        buffer[i++] = c;
    }
    buffer[i] = '\0';
} 

void uart_puts_slow(const char *str) {
    while (*str) {
        uart_putc(*str++); //send one char to console
        delay(10000000); //wait before printing the next
    }
}

//use special uart code to clear screen
//actually just skips a bunch of lines in the emulator
void clear_screen(void) {
    uart_puts("\033[2J\033[H");
}

//compare strings
//return 0 if they are the same
int strcmp(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
      if (*str1 != *str2) {
        return (*str1 - *str2);
      }
      str1++;
      str2++;
    }
    return (*str1 - *str2);
}

//read command adapted from xargs lab, uart instead of read, buff instead of stdin
char** read_args(char *buf) {
    static char *args[MAXARG];
    int i = 0;

    char *p = buf;

    //char *p = buf;
    while (*p != '\0' && i < MAXARG - 1) {
        // Skip leading spaces
        while (*p == ' ') p++;

        if (*p == '\0')
            break;

        args[i++] = p;  // Mark start of the argument

        // Move to end of word
        while (*p != '\0' && *p != ' ') p++;

        if (*p != '\0') {
            *p = '\0';  // Null-terminate the argument
            p++;
        }
    }

    args[i] = 0;  // Null-terminate the args list
    return args;
}

//Int to string needed for health print out
char* int_to_string(int num) {
    static char str[20];
    int i = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    while (num > 0 && i < 19) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }

    str[i] = '\0';

    // Reverse the string
    int left = 0, right = i - 1;
    while (left < right) {
        char temp = str[left];
        str[left++] = str[right];
        str[right--] = temp;
    }

    return str;
}