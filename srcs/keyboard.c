
// typedef struct {
//     uint16t_t   low_offset;
//     uint16t_t   selector;
//     uint16t_t   high_offset;
//     uint8t_t    always0;
//     uint8t_t    flags;
// }   _attribute_((packed)) idt_gat_t;

// idt_gat_t idt[256];

// void    set_idt_gate(int n, uint32_t handler) {
//     idt[n].low_offset = low_16(handler);
//     idt[n].selector = 0x08;
//     idt[n].always0 = 0;

//     idt[n].flags = 0x8E;
//     idt[n].high_offset = high_16(handler);
// }