// irq.cpp -- High level hardware interrupt request handlers.
// Part of this code is modified from Bran's kernel development tutorials.
// and JamesM's kernel development tutorials.
//

#include "Terminal.h"
#include "common.h"
#include "idt.h"
#include "inout.h"
#include "irq.h"

// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t* regs)
{
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs->int_no >= 0x28)
    {
        // Send reset signal to slave.
        outb(IDT::PIC_EOI, IDT::PIC_SLAVE_COMMAND);
    }
    // Send reset signal to master.
    outb(IDT::PIC_EOI, IDT::PIC_MASTER_COMMAND);

//    if (interrupt_handlers[regs.int_no] != 0)
//    {
//        isr_t handler = interrupt_handlers[regs.int_no];
//        handler(regs);
//    }
    Terminal::write("recieved IRQ: ");
    Terminal::write((char)('0' + regs->int_no - 0x20));
    Terminal::write("\n");
}