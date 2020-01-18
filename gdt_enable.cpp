#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "gdt_enable.h"


gdt_entry gdt_entries[5];
gdt_ptr gdt_pointer;

//! This function does the bitwise operations to set
//! the fields of each gdt_entry appropriately.
//! Thank you jamesmolloy.co.uk and OSDev.
static void gdt_set_fields(uint32_t gdt_index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
  {
    gdt_entries[gdt_index].base_low = base & 0xFFFF;
    gdt_entries[gdt_index].base_middle = (base >> 16) & 0xFF;
    gdt_entries[gdt_index].base_high = (base >> 24) & 0xFF;    

    gdt_entries[gdt_index].limit_low = (limit & 0xFFFF);
    gdt_entries[gdt_index].granularity = (limit >> 16 ) & 0x0F;

    gdt_entries[gdt_index].granularity |= gran & 0xF0;
    gdt_entries[gdt_index].access = access;
  } 

//! This function disables interrupts, creates the GDT pointer,
//! and then calls gdt_set_fields() 5 times to set up 
//! a flat memory model GDT. Then it calls
//! lgdt in inline assembly and flushes the data and code segment
//! registers to kickstart the use of the new GDT.

void gdt_enable()
  {       
    //!disable interrupts       
    asm("CLI");

    gdt_pointer.limit = (sizeof(gdt_entry) * 5) - 1;
    gdt_pointer.base = (uint32_t)&gdt_entries;

    //flat memory model for segmengs, each segment addresses whole memory space
    //just with diff access
    gdt_set_fields(0,0,0,0,0);   //required null seg descriptor
    gdt_set_fields(1,0,0xFFFFFFFF,0x9A,0xCF); //ring0 code segment
    gdt_set_fields(2,0,0xFFFFFFFF,0x92,0xCF); //ring0 data segment
    gdt_set_fields(3,0,0xFFFFFFFF,0xFA,0xCF); //ring3 code seg
    gdt_set_fields(4,0,0xFFFFFFFF,0xF2,0xCF); //ring3 data seg

    asm ("lgdt %0" : : "m"(gdt_pointer) ); //load pointer to gdt
//flush_gdt:\t\n
    asm (
         "jmp $0x08,$flush_ds\n"
         "flush_ds:\n"
         "mov $0x10, %ax\n"
         "mov %ax, %ds\n"
         "mov %ax, %es\n"
         "mov %ax, %fs\n"
         "mov %ax, %gs\n"
         "mov %ax, %ss\n"
         "ret\n"         
         );//flush CS/DS selector registers

    //re-enable interrupts
    asm("STI");
    
    
  }



