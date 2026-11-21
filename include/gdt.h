#include "kernel.h"

// #######################
// ######## GDT H ########
// #######################

// has to be loaded the exact same way as in the segment descriptor! same with idt ?

typedef struct {
    uint16_t    limit;
    uint16_t    base_low;
    uint8_t     base_middle;
    uint8_t     accessB;
    uint8_t     flags;
    uint8_t     base_high;
}   __attribute__((packed)) gdt_entry_t;

typedef struct {
    uint16_t     limit;
    unsigned int base;
}   __attribute__((packed)) gdt_ptr_t;

void    initGdt();

