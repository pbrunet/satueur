#include "inout.h"


unsigned char inb(unsigned short port)
{
    unsigned char rega;
    __asm__ __volatile__("inb %1,%0" : "=a" (rega) : "Nd" (port));
    return rega;
}

void outb(unsigned char value, unsigned short port)
{
    __asm__ __volatile__("outb %0, %1" : : "a" (value), "Nd" (port));
}
