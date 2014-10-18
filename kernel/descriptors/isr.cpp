// isr.cpp -- High level interrupt service routines and interrupt request handlers.
// Part of this code is modified from Bran's kernel development tutorials.
// and JamesM's kernel development tutorials.
//

#include <console/Console.hpp>

#include <descriptors/isr.h>

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t* regs)
{
    Console::write("recieved interrupt: ");
    Console::write((char)('0' + regs->int_no));
    Console::write("\n");
}
