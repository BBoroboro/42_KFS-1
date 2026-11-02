
NAME = kfs1

SRC = 

OBJ = ${SRC:.c=.o}

CC = gcc
CFLAGS = -fno-builtin -fno-stack-protector
RM = rm -rf
AR = ar rc

KERNEL 	= MY_OS/boot/kernel
ISO		= MY_OS/MY_OS.iso

BOOT 	= srcs/boot.s
KERNELC = srcs/kernel.c
LINKER  = srcs/linker.ld

all: 
	@mkdir -p MY_OS/boot
	@gcc -m32 $(CFLAGS) -c $(KERNELC) -o MY_OS/kernel.o
	@nasm -f elf32 $(BOOT) -o MY_OS/boot.o
	@ld -m elf_i386 -T $(LINKER) -o $(KERNEL) MY_OS/boot.o MY_OS/kernel.o
	@echo 'BUILD IS DONE'

iso:
	@mkdir -p MY_OS/boot/grub
	@cp grub.cfg MY_OS/boot/grub
#	@cp $(KERNEL) MY_OS/boot
	@grub-mkrescue -o MY_OS.iso MY_OS/
	@echo 'KERNEL ISO IS BUILT'

launch:
	qemu-system-i386 MY_OS.iso


clean:
	$(RM) $(KERNEL) $(ISO)

fclean: 
	$(RM) MY_OS

re: fclean all

.PHONY: all clean fclean re