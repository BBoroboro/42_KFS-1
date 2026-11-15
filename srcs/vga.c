#include "kernel.h"


// size_t  newline(char c) {
//     if (c == '\n') {
//         ter_column = 0;
//         ter_row++;
//         return 1;
//     }
//     return 0;
// }

void    ter_scroll() {
    for(uint16_t y = 0; y < VGA_HEIGHT; y++) {
        for (uint16_t x = 0; x < VGA_WIDTH; x++) {
            ter_buffer[y * VGA_WIDTH + x] = ter_buffer[(y + 1) * VGA_WIDTH + x];
        }
    }
    uint16_t blank = ' ' | (ter_color << 8);
    for (uint16_t x = 0; x < VGA_WIDTH; x++) {
        ter_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = blank;
    }
}

void  newline() {
    if (ter_row < -1) {
        ter_row++;
        ter_column = 0;
    }
    else {
        ter_scroll();
        ter_column = 0;
    }
}

void    reset() {
    ter_row = 0;
    ter_column = 0;
    ter_color = ter_defColor;

    for(uint16_t y = 0; y < VGA_HEIGHT; y++) {
        for(uint16_t x = 0; x < VGA_WIDTH; x++)
            ter_buffer[y * VGA_WIDTH + x] = ' ' | ter_defColor;
    }
}


void    ter_putentry(char c, uint8_t color, size_t column, size_t row) {

    if (c == '\n') {
        newline();
        return ;
    }

    const size_t i = row * VGA_WIDTH + column;
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
