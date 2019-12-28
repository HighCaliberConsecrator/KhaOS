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

