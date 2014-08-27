// isr.h -- Interface and structures for high level interrupt service routines.
// Part of this code is modified from Bran's kernel development tutorials.
// and JamesM's kernel development tutorials.
//

#ifndef ISR_H
#define ISR_H

#include "common.h"

struct registers
{
    uint16_t ds, es, fs, gs;           // Data segment selector
    // useless_value from http://wiki.osdev.org/James_Molloy%27s_Tutorial_Known_Bugs#Problem:_Interrupt_handlers_corrupt_interrupted_state
    uint32_t edi, esi, ebp, useless_value, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32_t int_no, err_code;         // Interrupt number and error code (if applicable)
    uint32_t eip, cs, eflags, esp, ss; // Pushed by the processor automatically.
} __attribute__((packed));

typedef registers registers_t;

extern "C" void isr_handler(registers_t*);
#endif
