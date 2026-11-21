#include "kernel.h"


size_t  ft_strlen(const char *str);
void* ft_memset(void *ptr, int c, size_t n);
void outPortB(unsigned short port, unsigned char value);
unsigned char inPortB(unsigned short port);