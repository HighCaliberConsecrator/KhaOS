#ifndef _ISR_DISPATCHER_INCLUDED
#define _ISR_DISPATCHER_INCLUDED

extern bool isr_ran;

extern inline bool interrupt_status()
  {
    unsigned long flags;
    asm volatile ("pushf\n\t"
                  "pop %0"
                  : "=g"(flags) );
    return flags & (1 << 9);    
  }        

//!Bit field struct representing type attribute flags of an IDT entry
struct __attribute__((__packed__)) idt_type_attr
  {
    int GateType :4;
    bool S :1;
    int DPL :2;
    bool P :1;
  };
//Interrupt Descriptor struct
struct  __attribute__ ((__packed__)) IDTDescr
  {
    uint16_t offset_1;
    uint16_t selector;
    uint8_t zero;
    idt_type_attr type_attr;
    uint16_t offset_2;   
  };


//Pointer to IDT to load
struct __attribute__((__packed__)) idt_pointer
  {
    uint16_t limit;
    uint32_t base;
  };    


class isr_dispatcher
  {
    size_t terminal_row;
    size_t terminal_column;
    uint8_t terminal_color;
    uint16_t* terminal_buffer;

    void create_idt_entry(IDTDescr IDT[], uint8_t index, uint32_t isrptr,idt_type_attr attr);
    public:
      isr_dispatcher(vga_text_display terminal);
      void scroll(); 
      size_t strlen(const char* str);
      void setcolor(uint8_t color);
      void clear_row(size_t row);
      void putentryat(char c, uint8_t color, size_t x, size_t y);
      void putchar(char c);
      void write(const char* data, size_t size);
      void writestring(const char* data);
      static void isr_zero();
      static void isr_thirtyfive();

  
  };	 


#endif
