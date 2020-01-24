#!/bin/bash
export PATH="/home/kevin/cross-compile-tools/bin":$PATH
i686-elf-as k_entry/k_entry_i686.asm -o ../k_entry.o
i686-elf-g++ -c k_main.cpp -o ../KhaOS.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
i686-elf-g++ -c klib.cpp -o ../klib.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
i686-elf-g++ -c vga_writer.cpp -o ../vga_writer.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
i686-elf-g++ -c gdt_enable.cpp -o ../gdt_enable.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
i686-elf-g++ -c isr_dispatcher.cpp -o ../isr_dispatcher.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -mgeneral-regs-only
i686-elf-gcc -T linker_scripts/linker.ld -o ../KhaOS.bin -ffreestanding -O2 -nostdlib ../k_entry.o ../KhaOS.o ../klib.o ../vga_writer.o ../gdt_enable.o ../isr_dispatcher.o -lgcc
