// #include "stdint.h"
// #include "interrupts/idt.h"
// #include "kernel.h"
// #include "keyboard.h"

// void initKeyboard() {
//     irq_inst_handler(1, &keyboardHandler);
// }

// void keyboardHandler(struct interruptRegister *r) {
//     char scancode = inb(0x60) & 0x07F; // what key is pressed
//     char press = inb(0x60) & 0x80; // down or up

//     ter_putchar(scancode);
//     ter_putchar(press);
// }


