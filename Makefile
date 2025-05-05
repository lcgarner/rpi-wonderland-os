CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc

CFLAGS = -mcpu=cortex-a7 -fpic -ffreestanding -O2 -Wall -Wextra -Iinclude
LDFLAGS = -T linker.ld -nostdlib

all: build build/myos.elf

build:
	mkdir -p build

build/boot.o: src/boot.S
	$(CC) $(CFLAGS) -c $< -o $@

build/kernel.o: src/kernel.c
	$(CC) $(CFLAGS) -std=gnu99 -c $< -o $@

build/io.o: src/io.c
	$(CC) $(CFLAGS) -std=gnu99 -c $< -o $@

build/game.o: src/game.c
	$(CC) $(CFLAGS) -std=gnu99 -c $< -o $@

build/myos.elf: build/boot.o build/kernel.o build/io.o build/game.o
	$(CC) $(LDFLAGS) -o $@ $^

run: build/myos.elf
	qemu-system-arm -M raspi2b -serial stdio -kernel $< 2>/dev/null

clean:
	rm -rf build/


