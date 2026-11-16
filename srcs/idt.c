// Doc: https://wiki.osdev.org/Interrupt_Descriptor_Table

#include "kernel.h"

idt_entry_t  idt_entries[256];
idt_ptr_t    idt_ptr;

extern void idt_flush(uint32_t);

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
    "SMID Floating-Point Exception", // RESERVED
    "Virtualization Exception", // RESERVED
    "Control Protection Exception", // RESERVED
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception", // RESERVED
    "VMM Communication Exception", // RESERVED
    "Security Exception", // RESERVED
    "Reserved"
};

// UTILS.C

void* ft_memset(void *ptr, int c, size_t n) {
    unsigned char *temp = ptr;
    for(size_t x = 0; x < n; x++) {
        temp[x] = c;
    }
    return ptr;
}


void outPortB(unsigned short port, unsigned char value)
{
    asm volatile ( "outb %1, %0" : : "dN"(port), "a"(value));
}

unsigned char inPortB(unsigned short port)
{
    unsigned char ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "dN"(port) );

    return ret;
}

// UTILS.C

void    isr_handler(idt_register_t *r) {
    if (r->int_no < 32) {
        ter_print(execpt_msgs[r->int_no]);
        ter_putchar('\n');
        ter_print("Exception caught! System halted\n");
        for(;;);
    }
}

void    setIdtGate(uint8_t n, uint32_t base, uint16_t selector, uint8_t flags) {
    idt_entries[n].low_offset = base & 0xFFFF;
    idt_entries[n].high_offset = (base >> 16) & 0xFFFF;
    idt_entries[n].selector = selector;
    idt_entries[n].always0 = 0;
    // idt_entries[n].flags = flags | 0x60; // or it to eleminate unnecessary flags
    idt_entries[n].flags = flags;
}

void    initIdt() {
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (uint32_t) &idt_entries;

    ft_memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

    // Conventional way to initialize PICs, make them available for interrupts
    // 1st PIC, 0x20 for commands and 0x21 for data
    // 2nd PIC, 0xA0 for commands and 0xA1 for data
    outPortB(0x20, 0x11); // sending 0x11 put the chips in initializing mode
    outPortB(0xA0, 0x11);

    outPortB(0x21, 0x20); // sets the offsets of our chips
    outPortB(0xA1, 0x28);

    outPortB(0x21, 0x04); // 
    outPortB(0xA1, 0x02);

    outPortB(0x21, 0x01); //
    outPortB(0xA1, 0x01);

    // outPortB(0x21, 0x0); // 
    // outPortB(0xA1, 0x0);
    outPortB(0x21, 0xFD); // Master PIC: only IRQ1 enabled
    outPortB(0xA1, 0xFF); // Slave PIC: all IRQs disabled

    // 0x8E -> sets 47 to 40 in Gate descriptor
    setIdtGate(0, (uint32_t)isr0, 0x08, 0x8E);
    setIdtGate(1, (uint32_t) isr1, 0x08, 0x8E);
    setIdtGate(2, (uint32_t) isr2, 0x08, 0x8E);
    setIdtGate(3, (uint32_t) isr3, 0x08, 0x8E);
    setIdtGate(4, (uint32_t) isr4, 0x08, 0x8E);
    setIdtGate(5, (uint32_t) isr5, 0x08, 0x8E);
    setIdtGate(6, (uint32_t) isr6, 0x08, 0x8E);
    setIdtGate(7, (uint32_t) isr7, 0x08, 0x8E);
    setIdtGate(8, (uint32_t) isr8, 0x08, 0x8E);
    setIdtGate(9, (uint32_t) isr9, 0x08, 0x8E);
    setIdtGate(10, (uint32_t) isr10, 0x08, 0x8E);
    setIdtGate(11, (uint32_t) isr11, 0x08, 0x8E);
    setIdtGate(12, (uint32_t) isr12, 0x08, 0x8E);
    setIdtGate(13, (uint32_t) isr13, 0x08, 0x8E);
    setIdtGate(14, (uint32_t) isr14, 0x08, 0x8E);
    setIdtGate(15, (uint32_t) isr15, 0x08, 0x8E);
    setIdtGate(16, (uint32_t) isr16, 0x08, 0x8E);
    setIdtGate(17, (uint32_t) isr17, 0x08, 0x8E);
    setIdtGate(18, (uint32_t) isr18, 0x08, 0x8E);
    setIdtGate(19, (uint32_t) isr19, 0x08, 0x8E);
    setIdtGate(20, (uint32_t) isr20, 0x08, 0x8E);
    setIdtGate(21, (uint32_t) isr21, 0x08, 0x8E);
    setIdtGate(22, (uint32_t) isr22, 0x08, 0x8E);
    setIdtGate(23, (uint32_t) isr23, 0x08, 0x8E);
    setIdtGate(24, (uint32_t) isr24, 0x08, 0x8E);
    setIdtGate(25, (uint32_t) isr25, 0x08, 0x8E);
    setIdtGate(26, (uint32_t) isr26, 0x08, 0x8E);
    setIdtGate(27, (uint32_t) isr27, 0x08, 0x8E);
    setIdtGate(28, (uint32_t) isr28, 0x08, 0x8E);
    setIdtGate(29, (uint32_t) isr29, 0x08, 0x8E);
    setIdtGate(30, (uint32_t) isr30, 0x08, 0x8E);
    setIdtGate(31, (uint32_t) isr31, 0x08, 0x8E);

        
    setIdtGate(32, (uint32_t)irq0, 0x08, 0x8E);
    setIdtGate(33, (uint32_t)irq1, 0x08, 0x8E);
    setIdtGate(34, (uint32_t)irq2, 0x08, 0x8E);
    setIdtGate(35, (uint32_t)irq3, 0x08, 0x8E);
    setIdtGate(36, (uint32_t)irq4, 0x08, 0x8E);
    setIdtGate(37, (uint32_t)irq5, 0x08, 0x8E);
    setIdtGate(38, (uint32_t)irq6, 0x08, 0x8E);
    setIdtGate(39, (uint32_t)irq7, 0x08, 0x8E);
    setIdtGate(40, (uint32_t)irq8, 0x08, 0x8E);
    setIdtGate(41, (uint32_t)irq9, 0x08, 0x8E);
    setIdtGate(42, (uint32_t)irq10, 0x08, 0x8E);
    setIdtGate(43, (uint32_t)irq11, 0x08, 0x8E);
    setIdtGate(44, (uint32_t)irq12, 0x08, 0x8E);
    setIdtGate(45, (uint32_t)irq13, 0x08, 0x8E);
    setIdtGate(46, (uint32_t)irq14, 0x08, 0x8E);
    setIdtGate(47, (uint32_t)irq15, 0x08, 0x8E);

    setIdtGate(128, (uint32_t) isr128, 0x08, 0x8E); // syscalls
    setIdtGate(177, (uint32_t) isr177, 0x08, 0x8E); // syscalls

    idt_flush((uint32_t)&idt_ptr);
}

void   *irq_routines[16] = {
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};

void    irq_install_handler(int irq, void (*handler)(idt_register_t *r)) {
    irq_routines[irq] = handler;
}

void    irq_uninstall_handler(int irq) {
    irq_routines[irq] = 0;
}

void    irq_handler(idt_register_t *r) {
    void (*handler)(idt_register_t *r);

    handler = irq_routines[r->int_no - 32];
    if(handler)
        handler(r);
    if(r->int_no >= 40)
        outPortB(0xA0, 0x20); // secondary EOI
    outPortB(0x20, 0x20); 
}