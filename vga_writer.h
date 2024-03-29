#ifndef _VGA_WRITER_INCLUDED
#define _VGA_WRITER_INCLUDED

class vga_text_display
  {
    enum vga_color
      {
  	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
       };
    size_t terminal_row;
    size_t terminal_column;
    uint8_t terminal_color;
    uint16_t* terminal_buffer;

     uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);
     uint16_t vga_entry(unsigned char uc, uint8_t color);

    
    static const size_t VGA_WIDTH = 80;
    static const size_t VGA_HEIGHT=25;

    public:
      vga_text_display();
      void scroll(); 
      size_t strlen(const char* str);
      void setcolor(uint8_t color);
      void clear_row(size_t row);
      void putentryat(char c, uint8_t color, size_t x, size_t y);
      void putchar(char c);
      void write(const char* data, size_t size);
      void writestring(const char* data);

  
  };	 

inline uint8_t vga_text_display::vga_entry_color(enum vga_color fg, enum vga_color bg )
  {
    return fg | bg << 4;  
  }	  

inline uint16_t vga_text_display::vga_entry(unsigned char uc, uint8_t color)
  {
    return(uint16_t) uc | (uint16_t) color <<8;
  }	  

#endif
