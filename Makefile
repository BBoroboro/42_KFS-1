
NAME = kfs1

SRC = 

OBJ = ${SRC:.c=.o}

CC = gcc -m32
CFLAGS = -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs
RM = rm -rf
AR = ar rc

KERNEL 	= MY_OS/boot/kernel
ISO		= MY_OS/MY_OS.iso

BOOT 	= srcs/boot.s
# ASM		= srcs/ISR.s
ASM		= srcs/idt_asm.s \
		  srcs/gdt_asm.s
KERNELC = srcs/kernel.c \
		  srcs/vga.c \
		  srcs/utils.c \
		  srcs/gdt.c \
		  srcs/idt.c \
		  srcs/cursor.c \
		  srcs/keyboard1.c 
		  
LINKER  = srcs/linker.ld
KERNELOBJ = $(patsubst srcs/%.c,MY_OS/%.o,$(KERNELC))
ASMOBJ = MY_OS/idt_asm.o \
		 MY_OS/gdt_asm.o

all:  $(KERNEL)
# 	@mkdir -p MY_OS/boot
# 	@$(CC) $(CFLAGS) -Iinclude/ -c $(KERNELC) -o MY_OS/kernel.o
# 	@nasm -f elf32 $(BOOT) -o MY_OS/boot.o
# 	@ld -m elf_i386 -T $(LINKER) -o $(KERNEL) MY_OS/boot.o MY_OS/kernel.o
# 	@echo 'BUILD IS DONE'

$(KERNEL): MY_OS/boot.o  $(ASMOBJ)  $(KERNELOBJ)
# $(KERNEL): MY_OS/boot.o $(KERNELOBJ)
	mkdir -p MY_OS/boot
	ld -m elf_i386 -T $(LINKER) -o $@ $^

# MY_OS/boot.o: $(BOOT)
# 	mkdir -p MY_OS
# 	nasm -f elf32 $< -o $@

MY_OS/%.o: srcs/%.s
	mkdir -p MY_OS
	nasm -f elf32 $< -o $@

iso:
	@mkdir -p MY_OS/boot/grub
	@cp grub.cfg MY_OS/boot/grub
#	@cp $(KERNEL) MY_OS/boot
	@grub-mkrescue -o MY_OS.iso MY_OS/
	@echo 'KERNEL ISO IS BUILT'

launch:
	qemu-system-i386 MY_OS.iso

MY_OS/%.o: srcs/%.c
	$(CC) $(CFLAGS) -m32 -Iinclude/ -c $< -o $@

clean:
	$(RM) $(KERNEL) $(ISO)

fclean: 
	$(RM) MY_OS MY_OS.iso

re: fclean all

.PHONY: all clean fclean re