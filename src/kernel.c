#include "game.h"
#include "io.h"
#include <stddef.h>
#include <stdint.h>

#define BUFSIZE 512

//kernel
void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags) {
    (void) r0;
    (void) r1;
    (void) atags;

    uart_init();
    show_menu();

    char buff[BUFSIZE];

    while (1) {
        uart_puts("\r\n> ");
        uart_gets(buff, BUFSIZE);
        char** commands_arr = read_args(buff);
        handle_command(commands_arr);
    }
}