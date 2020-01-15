#ifndef _GDT_ENABLE_INCLUDED
#define _GDT_ENABLE_INCLUDED

struct __attribute__((__packed__)) gdt_entry
  {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t granularity;
    uint8_t base_high;
  };    

struct __attribute__((__packed__)) gdt_ptr
  {
    uint16_t limit;
    uint32_t base;    
  };

void gdt_enable();

#endif
