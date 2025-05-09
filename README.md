**About**
Our goal was to build a bare bones operating system compatible with a Raspberry Pi 2, Model B with 16GB of RAM that can support a text based adventure game. To accomplish this we implemented a simple bootloader, linker, and kernel that uses UART to communicate with the user. Although we could not run our system on a real Raspberry Pi, we built an operating system compatible with an emulated version of Raspberry Pi 2. The system successfully boots directly into a text based game, can read and write to a user interface, handle delays, and parse commands.

**Packages to install**
gcc-arm-embedded (Mac) or gcc-arm-none-eabi (Linux)
qemu-system-arm

**How to run**
Navigate to project directory. Run the following commands: (1) make clean (2) make (3) make run.

**Acknowledgements**
Professor Jamie Macbeth of Smith College for constant assistance throughout the project.
Professor Michael Robson of Smith College and Professor Huang of Smith College for lending us materials.
Jake Sandler for his inspiring tutorial (https://jsandler18.github.io/tutorial/dev-env.html).
