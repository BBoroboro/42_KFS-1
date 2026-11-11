// For freestanding (no C standard library)
#include <stdbool.h> // for bool datatype
#include <stddef.h>  // for size_t and NULL
#include <stdint.h>   // for intx_t and uintx_t datatypes
// all three unvaluable for os development where you need to make sure of exact size
// Additionally can use  <float.h>, <iso646.h>, <limits.h>, and <stdarg.h>

// /* Check if the compiler thinks you are targeting the wrong operating system. */
// #if defined(__linux__)
// #error "You are not using a cross-compiler, you will most certainly run into trouble"
// #endif

// /* This tutorial will only work for the 32-bit ix86 targets. */
// #if !defined(__i386__)
// #error "This tutorial needs to be compiled with a ix86-elf compiler"
// #endif

/* Hardware text mode color constants. */
enum vga_color {
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

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t  ft_strlen(const char *str) {
    size_t  len = 0;
    while(str[len])
        len++;
    return len;
}

#define VGA_HEIGHT 25
#define VGA_WIDTH  80
#define VGA_MEMORY 0xB8000

size_t      ter_row;
size_t      ter_column;
uint8_t     ter_color;
uint16_t    *ter_buffer = (uint16_t*)VGA_MEMORY;


void ter_init(void) 
{
	ter_row = 0;
	ter_column = 0;
	ter_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			ter_buffer[index] = vga_entry(' ', ter_color);
		}
	}
}

void    ter_putentry(char c, uint8_t color, size_t x, size_t y) {
    const size_t i = y * VGA_WIDTH + x;
    ter_buffer[i] = vga_entry(c, color);
}

void    ter_putchar(char c) {
    ter_putentry(c, ter_color, ter_column, ter_row);
    if(++ter_column == VGA_WIDTH) {
        ter_column = 0;
        if (++ter_row == VGA_HEIGHT) {
            ter_row = 0;
        }
    }
}

void    ter_print(const char *str) {
    size_t len = ft_strlen(str);
    for(size_t i = 0; i < len; i++) {
        ter_putchar(str[i]);
    }
}


void    kmain(void);

void    kmain(void) { 
    ter_init();

    ter_print("Hello world!\n");
}