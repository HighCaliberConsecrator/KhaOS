#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "klib.h"
#include "vga_writer.h"
#include "gdt_enable.h"
#include "isr_dispatcher.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This will only work for the 32-bit x86 targets. 
   ...for now, plan to add support for switching to long mode on x64 
   and loading alternative GDT/IDT objects for running on x64
 * */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 

extern "C" 
  { 
    void kernel_main(void) 
      {
    	  /* Initialize terminal interface */
	 // terminal_initialize();
	 //
   isr_ran = 0;
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

          terminal.writestring("Initializing GDT...\n");
          gdt_enable();
          terminal.writestring("...GDT Initalized!\n");
          
          terminal.writestring("Initializing IDT...\n");
          isr_dispatcher interrupt_dispatcher(terminal);

          //Fire an interrupt to validate IDT
          asm("INT $0x23");       
          if(!isr_ran)
            {
              terminal.writestring("ISR did not run...\n"); 
            }
          else
            {
              terminal.writestring("ISR Ran!\n");
            }          

          terminal.writestring("...IDT Initialized!\n");



       }
   }
