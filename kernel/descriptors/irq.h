// irq.h -- Interface and structures for high level interrupt service routines.
// Part of this code is modified from Bran's kernel development tutorials.
// and JamesM's kernel development tutorials.
//

#ifndef IRQ_H
#define IRQ_H

#include <string.h>
#include <descriptors/registers.h>

extern "C" void irq_handler(registers_t*);
#endif
