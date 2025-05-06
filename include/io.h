#ifndef IO_H
#define IO_H

#include <stdint.h>

// uart functions
void uart_init(void);
void uart_putc(unsigned char c);
unsigned char uart_getc(void);
void uart_puts(const char *str);
void uart_gets(char *buffer, int max_len);

// utility
void clear_screen(void);
int strcmp(const char *s1, const char *s2);
char* int_to_string(int num);
char** read_args(char *buf);
void uart_puts_slow(const char *str);

// mmio helpers
void mmio_write(uint32_t reg, uint32_t data);
uint32_t mmio_read(uint32_t reg);
void delay(int32_t count);

#endif
