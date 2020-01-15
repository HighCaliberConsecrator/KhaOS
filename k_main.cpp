#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga_writer.h"

#include "gdt_enable.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
static inline bool interrupt_status()
  {
    unsigned long flags;
    asm volatile ("pushf\n\t"
                  "pop %0"
                  : "=g"(flags) );
    return flags & (1 << 9);    
  }        

extern "C" 
  { 
    void kernel_main(void) 
      {
    	  /* Initialize terminal interface */
	 // terminal_initialize();
	 //

	 vga_text_display terminal;
 
	  /* Newline support is left as an exercise. */
          terminal.writestring(" __       ___\n");   
          terminal.writestring("|  |     /  /   __                     ___________ ________ \n");
          terminal.writestring("|  |    /  /   |  |                   |           |        |\n");
          terminal.writestring("|  |   /  /    |  |                   |           | _______|\n");
          terminal.writestring("|  |  /  /     |  |                   |           | |       \n");
          terminal.writestring("|  | /  /      |  |                   |           | |       \n");
          terminal.writestring("|  |/  /       |  |                   |           | |       \n");
          terminal.writestring("|  |  /        |  |                   |           | |       \n");
          terminal.writestring("|  | /         |  |                   |    @@@    | |       \n");
          terminal.writestring("|  |/          |  |                   |    @ @    | |______ \n");
          terminal.writestring("|  |\\          |  |                   |    @ @    |        |\n");
          terminal.writestring("|  | \\         |  |________  ___      |    @ @    |_____   |\n");
          terminal.writestring("|  |  \\        |  |______  |/   \\     |    @ @    |     |  |\n");
          terminal.writestring("|  |   \\       |  |     |  |     \\    |    @@@    |     |  |\n");
          terminal.writestring("|  |\\   \\      |  |     |  |      |   |           |     |  |\n");
          terminal.writestring("|  | \\   \\     |  |     |  |  @@@ |   |           |     |  |\n");
          terminal.writestring("|  |  \\   \\    |  |     |  |  @ @  \\  |           |     |  |\n");
          terminal.writestring("|  |   \\   \\   |  |     |  |  @@@ \\ \\ |           |     |  |\n");
          terminal.writestring("|  |    \\   \\  |  |     |  |     | \\ \\|           |_____|  |\n");
          terminal.writestring("|  |     \\   \\ |__|     |__|_____|  \\_|___________|________|\n");
          terminal.writestring("|--|      \\___\\                                             \n");

          terminal.writestring("Initializing GDT...");
          gdt_enable();
          terminal.writestring("...GDT Initalized!");

       }
   }
