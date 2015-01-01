#include <sys/io.h>

unsigned char inb(unsigned short port)
{
    unsigned char rega;
    __asm__ __volatile__("inb %1,%0" : "=a" (rega) : "Nd" (port));
    return rega;
}

