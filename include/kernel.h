#ifndef KFS_H
# define KFS_H

#include <stdbool.h> // for bool datatype
#include <stddef.h>  // for size_t and NULL
#include <stdint.h>   // for intx_t and uintx_t datatypes

#define VGA_HEIGHT 25
#define VGA_WIDTH  80
#define VGA_MEMORY 0xB8000


void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void update_cursor(int x, int y);

#endif