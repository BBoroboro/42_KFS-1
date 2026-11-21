#include "kernel.h"

// /* Check if the compiler thinks you are targeting the wrong operating system. */
// #if defined(__linux__)
// #error "You are not using a cross-compiler, you will most certainly run into trouble"
// #endif

// /* This tutorial will only work for the 32-bit ix86 targets. */
// #if !defined(__i386__)
// #error "This tutorial needs to be compiled with a ix86-elf compiler"
// #endif

size_t      ter_row = 0;
size_t      ter_column = 0;
uint16_t const     ter_defColor = (VGA_COLOR_BLACK << 8) | (VGA_COLOR_LIGHT_GREY << 12);
uint16_t    *ter_buffer = (uint16_t*)VGA_MEMORY;
uint16_t    ter_color = ter_defColor;

void    test_div_zero(void) {
    volatile int z = 0;
    volatile int res;

    res = 10 / z;
}

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
    // enable_cursor(0, 15);
}


void    kmain(void);

void    kmain(void) { 
    ter_init();
    // char *index = "123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // char *str = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    ter_print("$ Hello world! This is 42!\n");
    // ter_print(str);

    // for(size_t i = 0; i < 5; i++) {
    //     if (ter_row == VGA_HEIGHT - 1) {
    //         ter_row--;
    //         ter_scroll();
    //     }
    //     // update_cursor(ter_column, ter_row + 1);
    //     ter_putchar(index[i]);
    //     ter_putchar('\n');
    // }

    asm volatile("cli");

    initGdt();
    ter_print("GDT IS DONE\n"); // test
    initIdt();
    ter_print("IDT IS DONE\n");

    // update_cursor(ter_column, ter_row + 1);
    // test_div_zero();
    // update_cursor(ter_column, ter_row + 1);

    initKeyboard();
    // update_cursor(ter_column, ter_row + 1);
    asm volatile("sti");
    for (;;) {
        update_cursor(ter_column, ter_row);
        if (ter_row + 1 == VGA_HEIGHT) {
            ter_scroll();
            ter_column = 1; // not normal compared to newline
            ter_row--;
        }
        asm volatile("hlt");
    }

    
}