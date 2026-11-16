global gdt_flush

gdt_flush:
    mov     eax, [esp+4]
    lgdt    [eax]

    mov     ax, 0x10
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax

    ; then jump to the code segment since we cant set value three
    jmp     0x08:.flush
.flush:
    ret