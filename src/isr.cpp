// isr.cpp -- High level interrupt service routines and interrupt request handlers.
// Part of this code is modified from Bran's kernel development tutorials.
// and JamesM's kernel development tutorials.
//

#include "common.h"
#include "isr.h"
#include "Terminal.h"

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t* regs)
{
    Terminal::write("recieved interrupt: ");
    Terminal::write((char)('0' + regs->int_no));
    Terminal::write("\n");
}
