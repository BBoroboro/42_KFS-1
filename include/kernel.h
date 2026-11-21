#ifndef KFS_H
# define KFS_H

#pragma once

// For freestanding (no C standard library)
#include <stdbool.h> // for bool datatype
#include <stddef.h>  // for size_t and NULL
#include <stdint.h>   // for intx_t and uintx_t datatypes
// all three unvaluable for os development where you need to make sure of exact size
// Additionally can use  <float.h>, <iso646.h>, <limits.h>, and <stdarg.h>

#include "vga.h"
#include "idt.h"
#include "gdt.h"
#include "utils.h"


void initKeyboard();


void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void update_cursor(int x, int y);

// void isr_install();

void init_keyboard();

// void initKeyboard();
// void keyboardHandler(struct interruptRegister *r);

#endif