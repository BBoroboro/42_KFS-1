#include "kernel.h"

// Doc: https://wiki.osdev.org/Global_Descriptor_Table
// Doc: https://wiki.osdev.org/GDT_Tutorial

extern  gdt_flush(addr_t);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

void    setGdtGate(uint32_t n, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) { // change gran with flags?
    gdt_entries[n].base_low = (base & 0xFFFF);
    gdt_entries[n].base_middle = ((base >> 16) & 0xFF);
    gdt_entries[n].base_high = ((base >> 24) & 0xFF);

    gdt_entries[n].limit = (limit & 0xFFFF);
    gdt_entries[n].flags = (limit >> 16) & 0x0F;
    gdt_entries[n].flags |= (gran & 0xF0);

    gdt_entries[n].accessB = access;
}

void    initGdt(){
    gdt_ptr.limit = (sizeof(gdt_entries) * 5 - 1); // -1 to get it to the right offset of mem
    gdt_ptr.base = (unsigned int)&gdt_entries;

    setGdtGate(0,0,0,0,0); // Required null segment, done by convention
    setGdtGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); //  Kernel Mode Code Segment, i understand the 9A but confused with CF
    setGdtGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); //  Kernel Mode Data Segment,
    setGdtGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User Kernel Mode Code Segment
    setGdtGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User Mode Data Segment

    gdt_flush(&gdt_ptr);
}
