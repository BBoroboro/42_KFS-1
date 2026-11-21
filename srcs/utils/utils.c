#include "kernel.h"

size_t  ft_strlen(const char *str) {
    size_t  len = 0;
    while(str[len])
        len++;
    return len;
}

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
