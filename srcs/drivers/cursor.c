#include "kernel.h"

// static inline void outb(unsigned short port, unsigned char value)
// {
//     asm volatile ( "outb %0, %1" : : "a"(value), "Nd"(port) );
// }

// static inline unsigned char inb(unsigned short port)
// {
//     unsigned char ret;
//     asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );

//     return ret;
// }


void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outPortB(0x3D4, 0x0A);
	outPortB(0x3D5, (inPortB(0x3D5) & 0xC0) | cursor_start);

	outPortB(0x3D4, 0x0B);
	outPortB(0x3D5, (inPortB(0x3D5) & 0xE0) | cursor_end);
}


void disable_cursor()
{
	outPortB(0x3D4, 0x0A);
	outPortB(0x3D5, 0x20);
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outPortB(0x3D4, 0x0F);
	outPortB(0x3D5, (uint8_t) (pos & 0xFF));
	outPortB(0x3D4, 0x0E);
	outPortB(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

uint16_t get_cursor_position(void)
{
    uint16_t pos = 0;
    outPortB(0x3D4, 0x0F);
    pos |= inPortB(0x3D5);
    outPortB(0x3D4, 0x0E);
    pos |= ((uint16_t)inPortB(0x3D5)) << 8;
    return pos;
}