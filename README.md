
documentations:https:
https://wiki.osdev.org/Bare_Bones

interesting videos (starting vid 37 for kfs but previous videos also interesting for asm)
https://www.youtube.com/watch?v=6zPBNEDKbpk&list=PL2EF13wm-hWCoj6tUBGUmrkJmH1972dBB&index=37 




gcc commands to run in the makefile later

; -m32 becasue we want to work in 32 bits
gcc -m32 -fno-stack-protector -fno-builtin -c kernel.c -o kernel.o
nasm -f elf32 boot.s -o boot.o
ld -m elf_i386 -T linker.ld -o kernel boot.o kernel.o
mv kernel MY_OS/boot/kernel
(for this one we need to install xorriso) 
grub-mkrescue -o MY_OS.iso MY_OS/

(need to install - sudo apt install qemu-system-x86)
qemu-system-i386 MY_OS.iso