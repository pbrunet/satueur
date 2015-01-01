#include <sys/io.h>

void outb(unsigned char value, unsigned short port)
{
    __asm__ __volatile__("outb %0, %1" : : "a" (value), "Nd" (port));
}
