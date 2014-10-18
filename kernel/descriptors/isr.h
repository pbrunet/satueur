// isr.h -- Interface and structures for high level interrupt service routines.
// Part of this code is modified from Bran's kernel development tutorials.
// and JamesM's kernel development tutorials.
//

#ifndef ISR_H
#define ISR_H

#include <tools/common.h>
#include "registers.h"

extern "C" void isr_handler(registers_t*);
#endif
