#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "klib.h"

//! \namespace klib 
//! This namespace will contain some basic utility functions 
//! that will be helpful. A basic library for my kernelspace code

//! Convert integers to ASCII.
//! Can output in hex or binary or whatever.
//! Very helpful for debugging so I can print sizeof() results
char * klib::itoa(int value,int base,char* result)
  {       
    // check that the base if valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }

		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;

		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );

		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
		return result;
  }    

//! A basic memset 
//! Let's see if this helps me get my IDT working
//! fffffffffuuuuuuuuu

void* klib::memset(void* ptr, int value, size_t num)
  {
    unsigned char* ptr_byte = (unsigned char*) ptr;
    
    for (size_t i=0; i < num; ptr_byte[i] = (unsigned char)value,i++);
    return ptr;    
  }        

