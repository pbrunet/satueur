#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

struct registers
{
    uint16_t ds, es, fs, gs;           // Data segment selector
    // useless_value from http://wiki.osdev.org/James_Molloy%27s_Tutorial_Known_Bugs#Problem:_Interrupt_handlers_corrupt_interrupted_state
    uint32_t edi, esi, ebp, useless_value, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32_t int_no, err_code;         // Interrupt number and error code (if applicable)
    uint32_t eip, cs, eflags, esp, ss; // Pushed by the processor automatically.
} __attribute__((packed));

typedef registers registers_t;

#endif
