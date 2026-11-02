BITS 32

; boot into grub in the text section
;1st DD is a constant that grub is gonna look for to determine where the os actually is
;2nd DD is set flags to 0
;3rd DD the checksum, the negation of the signature + the flag sets. Checks if something has been modified while booting into the system

section .text
    ALIGN   4
    DD      0x1BADB002
    DD      0x00000000
    DD      -(0x1BADB002 + 0x00000000)

global start

; kernal main function
extern kmain

; CLI turns off the interupt
; initialize the esp to a value called stack_spaced
start:
    CLI
    MOV  esp, stack_space
    CALL kmain
    HLT

HaltKernel:
    CLI
    HLT
    JMP HaltKernel

; remaining space available to us
section .bss
RESB 8192
stack_space:
