
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

# ASM		= srcs/interrupts/idt_asm.s \
# 		  srcs/gdt_asm.s
ASM		:= $(shell find srcs -name '*.s')
KERNELC := $(shell find srcs -name '*.c')

# KERNELC = srcs/kernel.c \
# 		  srcs/vga.c \
# 		  srcs/utils.c \
# 		  srcs/gdt.c \
# 		  srcs/interrupts/idt.c \
# 		  srcs/cursor.c \
# 		  srcs/keyboard1.c 
		  
LINKER  = srcs/linker.ld

KERNELOBJ = $(patsubst srcs/%.c,MY_OS/%.o,$(KERNELC))
KERNELOBJ += $(patsubst srcs/%.s,MY_OS/%.o,$(ASM))

# ASMOBJ = MY_OS/idt_asm.o \
# 		 MY_OS/gdt_asm.o

all:  $(KERNEL)

$(KERNEL): MY_OS/boot/boot.o  $(ASMOBJ)  $(KERNELOBJ)
	mkdir -p MY_OS/boot
	ld -m elf_i386 -T $(LINKER) -o $@ $^


iso:
	@mkdir -p MY_OS/boot/grub
	@cp grub.cfg MY_OS/boot/grub
#	@cp $(KERNEL) MY_OS/boot
	@grub-mkrescue -o MY_OS.iso MY_OS/
	@echo 'KERNEL ISO IS BUILT'

launch:
	qemu-system-i386 MY_OS.iso

MY_OS/%.o: srcs/%.s
	mkdir -p $(dir $@)
	nasm -f elf32 $< -o $@

MY_OS/%.o: srcs/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -m32 -Iinclude/ -c $< -o $@

clean:
	$(RM) $(KERNEL) $(ISO)

fclean: 
	$(RM) MY_OS MY_OS.iso

re: fclean all

.PHONY: all clean fclean re