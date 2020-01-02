#!/bin/bash
i686-elf-as k_entry/k_entry_i686.asm -o ../k_entry.o
i686-elf-g++ -c k_main.cpp -o ../KhaOS.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
i686-elf-gcc -T linker_scripts/linker.ld -o ../KhaOS.bin -ffreestanding -O2 -nostdlib ../k_entry.o ../KhaOS.o -lgcc
