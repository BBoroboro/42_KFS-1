#ifndef KFS_H
# define KFS_H

// For freestanding (no C standard library)
#include <stdbool.h> // for bool datatype
#include <stddef.h>  // for size_t and NULL
#include <stdint.h>   // for intx_t and uintx_t datatypes
// all three unvaluable for os development where you need to make sure of exact size
// Additionally can use  <float.h>, <iso646.h>, <limits.h>, and <stdarg.h>


// #######################
// ######## VGA H ########
// #######################

#define VGA_HEIGHT 25
#define VGA_WIDTH  80
#define VGA_MEMORY 0xB8000

extern size_t               ter_row;
extern size_t               ter_column;
extern uint16_t const     ter_defColor;
extern uint16_t             ter_color;
extern uint16_t             *ter_buffer;

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

// #######################
// ######## IDT H ########
// #######################

typedef struct {
    uint16_t   low_offset;
    uint16_t   high_offset;
    uint16_t   selector;
    uint8_t    always0;
    uint8_t    flags;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

typedef struct {
    uint32_t    cr2;
    uint32_t    ds;
    uint32_t    edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t    int_no, err_code;
    uint32_t    eip, cs, eflags, useresp, ss;
}   idt_register_t;

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

extern void isr128(void);
extern void isr177(void);

// extern void irq0(void);
// extern void irq1(void);
// extern void irq2(void);
// extern void irq3(void);
// extern void irq4(void);
// extern void irq5(void);
// extern void irq6(void);
// extern void irq7(void);
// extern void irq8(void);
// extern void irq9(void);
// extern void irq10(void);
// extern void irq11(void);
// extern void irq12(void);
// extern void irq13(void);
// extern void irq14(void);
// extern void irq15(void);

// #######################
// ######## IDT H ########
// #######################

// ######### ######### ######### 
// ######### FUNCTIONS ######### 
// ######### ######### ######### 


// #########    VGA    ######### 

void    newline(void);
void    reset(void);
void    ter_scroll();
void    ter_putentry(char c, uint8_t color, size_t column, size_t row);
void    ter_putchar(char c);
void    ter_print(const char *str);

// ############################# 


size_t  ft_strlen(const char *str);


// static inline void outb(unsigned short port, unsigned char value);
// static inline unsigned char inb(unsigned short port);

static inline void outb(unsigned short port, unsigned char value)
{
    asm volatile ( "outb %0, %1" : : "a"(value), "Nd"(port) );
}

static inline unsigned char inb(unsigned short port)
{
    unsigned char ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );

    return ret;
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void update_cursor(int x, int y);

// void isr_install();

// void init_keyboard();

// void initKeyboard();
// void keyboardHandler(struct interruptRegister *r);

#endif