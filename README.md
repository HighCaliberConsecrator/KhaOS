# KhaOS
## Kevin's Half-assed Operating System

1. What is it
2. Build/install
3. Some more stuff in another sectin


#### What is it
KhaOS is a hobby  operating system I'm building for fun and as a systems
programming exercise.  I will be using a lot of examples from OSDev and
the Minix book

#### Build/Install
Assemble  Kernel Multiboot entry point:
i686-elf-as k_entry/k_entry_i686.asm -o k_entry.o

Compile kernel cpp:
i686-elf-g++ -c kernel.c++ -o KhaOS.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

Link with (requires linker.ld linker script):
i686-elf-gcc -T linker.ld -o KhaOS.bin -ffreestanding -O2 -nostdlib k_entry.o KhaOS.o -lgcc

Test with:
qemu-system-i386 -kernel KhaOS.bin

#### Some other stuff
To create a HDD image with GRUB on the MBR pointed to my OS partition
I do the following
1. dd if=/dev/zero of=KhaOS.img bs=1M count=50
2. sudo losetup --find --show KhaOS.img
3. sudo cfdisk /devloop0  (create a DOS primary partition in free space,
starting at sector 2048 (which it does by default) leaves a 1MB MBR space
for GRUB).
4. sudo losetup /dev/loop1 KhaOS.img -o 1048576 (set up the partition
on another loopback device)
5. sudo mkfs.ext4 /dev/loop1
6. sudo mount /dev/loop1 /mnt
7. sudo grub-install --root-directory=/mnt --no-floppy --modules="normal part_msdos ext2 multiboot" /dev/loop0

