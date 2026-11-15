#include "kernel.h"

# define low_16(address) (uint16_t)((address) & 0xFFFF)
# define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

#define IRQ1 33
#define IDT_ENTRIES 256

typedef struct {
    uint16_t   low_offset;
    uint16_t   high_offset;
    uint16_t   selector;
    uint8_t    always0;
    uint8_t    flags;
}   __attribute__((packed)) idt_gate_t;

// can do that in asm no?
typedef struct {
    uint32_t    ds;
    uint32_t    edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t    int_no, err_code;
    uint32_t    eip, cs, eflags, useresp, ss;
}   registers_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_registers_t;

typedef void (*isr_t)(registers_t *);

idt_gate_t idt[256];

isr_t interrupt_handlers[256];

idt_registers_t idt_reg;


unsigned char    *execpt_msgs[] = {
    "Division by zero", 
    "Debug",
    "NMI Interrupt",
    "Breakpoint",
    "Overflow",
    "BOUND Range Exceeded",
    "Invalid Upcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun", 
    "Invalid TSS",
    "Segment Not Present", 
    "Stack-Segment Fault", 
    "General Protection",
    "Page Fault",
    "Reserved",
    "Floating-Point Error",
    "Alignment Check",
    "Machine Check",
    "SMID Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved"
};

void    set_idt_gate(int n, uint32_t handler) {
    idt[n].low_offset = low_16(handler);
    idt[n].selector = 0x08;
    idt[n].always0 = 0;

    idt[n].flags = 0x8E;
    idt[n].high_offset = high_16(handler);
}

void    isr_handler(registers_t *r) {
    // print_string(execpt_msgs[r->int_no]);
    ter_print(execpt_msgs[r->int_no]);
    ter_putchar('\n');
}

void    irq_handler(registers_t *r) {
    if (interrupt_handlers[r->int_no] != 0) {
        isr_t handler = interrupt_handlers[r->int_no];
        handler(r);
    }
    if (r->int_no < 40) {
        outb(0xA0, 0x20); // secondary EOI
    }
    outb(0x20, 0x20); // primary EOI
}

void load_idt() {
    idt_reg.base = (uint32_t) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    asm volatile("lidt (%0)" : : "r" (&idt_reg));
}

void isr_install() {
    set_idt_gate(0, (uint32_t) isr0);
    set_idt_gate(1, (uint32_t) isr1);
    set_idt_gate(2, (uint32_t) isr2);
    set_idt_gate(3, (uint32_t) isr3);
    set_idt_gate(4, (uint32_t) isr4);
    set_idt_gate(5, (uint32_t) isr5);
    set_idt_gate(6, (uint32_t) isr6);
    set_idt_gate(7, (uint32_t) isr7);
    set_idt_gate(8, (uint32_t) isr8);
    set_idt_gate(9, (uint32_t) isr9);
    set_idt_gate(10, (uint32_t) isr10);
    set_idt_gate(11, (uint32_t) isr11);
    set_idt_gate(12, (uint32_t) isr12);
    set_idt_gate(13, (uint32_t) isr13);
    set_idt_gate(14, (uint32_t) isr14);
    set_idt_gate(15, (uint32_t) isr15);
    set_idt_gate(16, (uint32_t) isr16);
    set_idt_gate(17, (uint32_t) isr17);
    set_idt_gate(18, (uint32_t) isr18);
    set_idt_gate(19, (uint32_t) isr19);
    set_idt_gate(20, (uint32_t) isr20);
    set_idt_gate(21, (uint32_t) isr21);
    set_idt_gate(22, (uint32_t) isr22);
    set_idt_gate(23, (uint32_t) isr23);
    set_idt_gate(24, (uint32_t) isr24);
    set_idt_gate(25, (uint32_t) isr25);
    set_idt_gate(26, (uint32_t) isr26);
    set_idt_gate(27, (uint32_t) isr27);
    set_idt_gate(28, (uint32_t) isr28);
    set_idt_gate(29, (uint32_t) isr29);
    set_idt_gate(30, (uint32_t) isr30);
    set_idt_gate(31, (uint32_t) isr31);

    // ICW1
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    // ICW2
    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    // ICW3
    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    // ICW4
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    // OCW1
    outb(0x21, 0xFD); // Enable IRQ1, mask other master IRQs
    outb(0xA1, 0xFF); // Mask all slave IRQs

    // IRQ ISRs (primary PIC)
    set_idt_gate(32, (uint32_t)irq0);
    // ...
    set_idt_gate(39, (uint32_t)irq7);

    // IRQ ISRs (secondary PIC)
    set_idt_gate(40, (uint32_t)irq8);
    // ...
    set_idt_gate(47, (uint32_t)irq15);

    load_idt();
}



void print_letter(uint8_t scancode) {
    switch (scancode) {
        case 0x0:
            ter_print("ERROR");
            break;
        case 0x1:
            ter_print("ESC");
            break;
        case 0x2:
            ter_print("1");
            break;
        case 0x3:
            ter_print("2");
            break;
        // ...
        case 0x39:
            ter_print("Space");
            break;
        default:
            if (scancode <= 0x7f) {
                ter_print("Unknown key down");
            } else if (scancode <= 0x39 + 0x80) {
                ter_print("key up ");
                print_letter(scancode - 0x80);
            } else {
                ter_print("Unknown key up");
            }
            break;
    }
}

static void keyboard_callback(registers_t *regs) {
    uint8_t scancode = inb(0x60);
    // ter_putchar(scancode);
    // ter_putchar('\n');
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}