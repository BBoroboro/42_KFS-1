// #include "stdint.h"
// #include "interrupts/idt.h"
#include "kernel.h"
// #include "keyboard.h"

const uint32_t UNKOWN = 0xFFFFFFFF;
const uint32_t ESC = 0xFFFFFFFF - 1;
const uint32_t CTRL = 0xFFFFFFFF - 2;
const uint32_t LSHIFT = 0xFFFFFFFF - 3;
const uint32_t RSHIFT = 0xFFFFFFFF - 4;
const uint32_t ALT = 0xFFFFFFFF - 5;
const uint32_t CAPS = 0xFFFFFFFF - 6; //
const uint32_t F1 = 0xFFFFFFFF - 7;
const uint32_t F2 = 0xFFFFFFFF - 8;
const uint32_t F3 = 0xFFFFFFFF - 9;
const uint32_t F4 = 0xFFFFFFFF - 10;
const uint32_t F5 = 0xFFFFFFFF - 11;
const uint32_t F6 = 0xFFFFFFFF - 12;
const uint32_t F7 = 0xFFFFFFFF - 13;
const uint32_t F8 = 0xFFFFFFFF - 14;
const uint32_t F9 = 0xFFFFFFFF - 15;
const uint32_t F10 = 0xFFFFFFFF - 16;
const uint32_t NUMLOCK = 0xFFFFFFFF - 17;
const uint32_t SCRLOCK = 0xFFFFFFFF - 18;
const uint32_t HOME = 0xFFFFFFFF - 19;
const uint32_t UP = 0xFFFFFFFF - 20;
const uint32_t PCUP = 0xFFFFFFFF - 21;
const uint32_t LEFT = 0xFFFFFFFF - 22;
const uint32_t RIGHT = 0xFFFFFFFF - 23;
const uint32_t END = 0xFFFFFFFF - 24;

const uint32_t DOWN = 0xFFFFFFFF - 25;
const uint32_t PGDOWN = 0xFFFFFFFF - 26;
const uint32_t INS = 0xFFFFFFFF - 27;
const uint32_t DEL = 0xFFFFFFFF - 28;
const uint32_t F11 = 0xFFFFFFFF - 29;
const uint32_t F12 = 0xFFFFFFFF - 30;


const uint32_t lowercase[128] = {
    0, ESC, '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 
    'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    CTRL, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    LSHIFT, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', RSHIFT,
    '*', ALT, ' ', CAPS, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, NUMLOCK,
    SCRLOCK, HOME, UP, PCUP, '-', LEFT, 0, RIGHT, '+', END, DOWN, PGDOWN, INS, DEL, 0, 0, 0,
    F11, F12, 0, 
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

// const uint32_t uppercase[128] {
//     0, ESC, '!', '@',
// };

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

    // ter_print("IRD RECEIVED !");
    // ter_print("Scancode code: ");
    // ter_putchar(scancode);
    // ter_print("Scancode code in hex: ");
    // ter_print_hex(scancode);

    // ter_print(", Press: ");
    // ter_putchar(press);
    // ter_print("Press in hex: ");
    // ter_print_hex(press);
    // ter_putchar('\n');

    // // if (press == 'P')
    if (press == 0)
        ter_putchar(lowercase[scancode]);
}

void initKeyboard() {
    irq_install_handler(1, &keyboardHandler);
}    

