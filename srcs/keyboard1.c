// #include "stdint.h"
// #include "interrupts/idt.h"
#include "kernel.h"
// #include "keyboard.h"

const uint32_t lowercase[128] = {
    'U', 'E', '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 
    'y',
};


void ter_print_hex(uint8_t value) {
    const char *hex = "0123456789ABCDEF";

    ter_print("0x");
    ter_putchar(hex[(value >> 4) & 0x0F]);
    ter_putchar(hex[value & 0x0F]);
    ter_print("\n");
}

void keyboardHandler(idt_register_t *r) {
    char scancode = inPortB(0x60) & 0x7F; // what key is pressed
    char press = inPortB(0x60) & 0x80; // down or up

    ter_print("IRD RECEIVED !");
    ter_print("Scancode code: ");
    ter_putchar(scancode);
    ter_print(", Press: ");
    ter_putchar(press);
    ter_putchar('\n');
    ter_putchar(lowercase[scancode]);
}

void initKeyboard() {
    irq_install_handler(1, &keyboardHandler);
}    

