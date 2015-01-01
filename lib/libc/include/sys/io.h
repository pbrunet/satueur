#ifndef IO_H
#define IO_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned char inb(unsigned short port);
void outb(unsigned char value, unsigned short port);

#ifdef __cplusplus
}
#endif

#endif
