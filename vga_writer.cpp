#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "vga_writer.h"


//! \class vga_text_display
//!  A simple VGA Text mode output driver

//! This class allows writing of strings to the VGA memory mapped buffer
//! with support for newlines and scrolling.
//! It's a simple driver meant for early kernel output.

size_t vga_text_display::strlen(const char* str)
  {
    size_t len = 0;
    while(str[len])
      len++;
    return len;
  }  //!< A basic string length implementation

vga_text_display::vga_text_display()
  {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;
 
    for (size_t y = 0; y < VGA_HEIGHT; y++) 
      {
        for (size_t x = 0; x < VGA_WIDTH; x++) 
          {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
          } 
      }

  }  //!< The constructor sets up the VGA buffer with whitespace
     //!  And sets a default font color bit


void vga_text_display::setcolor(uint8_t color)
  {
    terminal_color = color;
  }

void vga_text_display::clear_row(size_t row)
  {

    for(size_t c_index = 0; c_index < VGA_WIDTH; c_index++)
      {
        terminal_buffer[row * VGA_WIDTH + c_index] = vga_entry(' ',terminal_color);
      }    
  }

void vga_text_display::scroll()
  {


    for(size_t r_index = 0; r_index < VGA_HEIGHT - 1 ; r_index++)
      {          
        for(size_t c_index=0; c_index < VGA_WIDTH; c_index++)
          {      
            terminal_buffer[r_index * VGA_WIDTH + c_index] = terminal_buffer[(r_index+1) * VGA_WIDTH + c_index];
          }  
      }

    clear_row(VGA_HEIGHT-1);
  }

void vga_text_display::putentryat(char c, uint8_t color, size_t x, size_t y)
  {
     if(c == '\n')
      {
        terminal_row++;
        terminal_column = 0;
  
      	return;
      }	  


       
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
 
  }

void vga_text_display::putchar(char c)
  {
    putentryat(c, terminal_color, terminal_column, terminal_row);

    if (++terminal_column == VGA_WIDTH) 
      {
         terminal_column = 0;
	  if (++terminal_row == VGA_HEIGHT)
            {          
              scroll();
              terminal_row = VGA_HEIGHT - 1;
            }
       }

    if(terminal_row == VGA_HEIGHT)
      {
        scroll();             
        terminal_row = VGA_HEIGHT - 1; 
      }           


  }

void vga_text_display::write(const char* data, size_t size)
  {
    for (size_t i = 0; i < size; i++)
      {
        putchar(data[i]);
      }

  }

void vga_text_display::writestring(const char* data)
  {
   
    write(data, strlen(data));

  }
