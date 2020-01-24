#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "vga_writer.h"
#include "isr_dispatcher.h"
#include "klib.h"

//! \class isr_dispatcher
//! The isr_dispatcher class will initialize the IDT in it's constructor and encapsulate the  
//! ISR's as methods.

bool isr_ran = 0; //This will be set when any ISR runs as a test

isr_dispatcher::isr_dispatcher(vga_text_display terminal)
  {
    terminal.writestring("WTFFFFFFFFFFFFFFFFFFF\n"); 
    //set up IDT space
    IDTDescr IDT[256];

    klib::memset(&IDT,0,sizeof(IDTDescr)*256);
    //Disable Interrupts if they are enabled
    if(interrupt_status())
      {            
        asm("CLI");
      }



    idt_type_attr attr_test;
    attr_test.P = 1;
    attr_test.DPL = 0; //minimum calling priv level
    attr_test.S = 0;
    attr_test.GateType = 0xE; //32bit interrupt gate

    //Set up each actual descriptors
    //so I can test by just printing out
    //the name of interrupt as it comes in
    create_idt_entry(IDT,0,(uint32_t)&isr_dispatcher::isr_zero,attr_test);
    create_idt_entry(IDT,35,(uint32_t)&isr_dispatcher::isr_thirtyfive,attr_test);


    uint32_t base = (uint32_t)&IDT;
    uint16_t length = sizeof(IDTDescr) * 256 - 1;

    struct
      {
        uint16_t length;
        uint32_t    base;
      }__attribute__((packed)) IDTR = {length,base};
    
    
    terminal.writestring("Size of IDT ptr:\n");

    char result[9];
    terminal.writestring(klib::itoa(sizeof(IDTR),10,result));
    terminal.writestring("\n");
    terminal.writestring("Size of IDT entry 35: \n");
    terminal.writestring(klib::itoa(sizeof(IDT[35]),10,result));


    terminal.writestring("\n");
    terminal.writestring("Size of IDT ATTR/FLAGS: \n");
    terminal.writestring(klib::itoa(sizeof(attr_test),10,result));


    asm ("lidt %0" : : "m"(IDTR) );

    //re-enable interrupts
    asm("STI");

  }

void isr_dispatcher::create_idt_entry(IDTDescr IDT[], uint8_t index, uint32_t isrptr,idt_type_attr attr)
  {

    IDT[index].offset_1 = isrptr & 0xFFFF;
    IDT[index].selector = 0x08 ;//index 1 of GDT (kern code seg)
    IDT[index].zero = 0;
    IDT[index].type_attr = attr;
    IDT[index].offset_2 = (isrptr  >> 16) & 0xFFFF;
    
  }        

__attribute__((interrupt)) void isr_dispatcher::isr_zero()
  {
    isr_ran = 1;          
  }       


__attribute__((interrupt)) void isr_dispatcher::isr_thirtyfive()
  {
    vga_text_display iterm;
    iterm.scroll();
    iterm.writestring("\n");
    iterm.writestring("........INT 35!...........");    
    isr_ran = 1;          
  }        
