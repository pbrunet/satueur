#include "idt.h"
#include <tools/common.h>
#include <tools/inout.h>


//0x08 Means the code section set by the gdt
#define ADD_ISR(i)\
    add_entry(i, (uint32_t)isr##i , 0x08, F_BASE | RING_0);

//0x08 Means the code section set by the gdt
#define ADD_IRQ(i)\
    add_entry(i, (uint32_t)irq##i , 0x08, F_BASE | RING_0);

IDT::IDT()
{
    m_ptr.limit = sizeof(entry_t) * NB_ENTRIES -1;
    m_ptr.base  = (uint32_t)&m_entries;

    PIC_remap(0x20, 0x28); // Remap PIC to 32-40 40-48

    memset(&m_entries, 0, sizeof(entry_t) * NB_ENTRIES);

    ADD_ISR(0);
    ADD_ISR(1);
    ADD_ISR(2);
    ADD_ISR(3);
    ADD_ISR(4);
    ADD_ISR(5);
    ADD_ISR(6);
    ADD_ISR(7);
    ADD_ISR(8);
    ADD_ISR(9);
    ADD_ISR(10);
    ADD_ISR(11);
    ADD_ISR(12);
    ADD_ISR(13);
    ADD_ISR(14);
    ADD_ISR(15);
    ADD_ISR(16);
    ADD_ISR(17);
    ADD_ISR(18);
    ADD_ISR(19);
    ADD_ISR(20);
    ADD_ISR(21);
    ADD_ISR(22);
    ADD_ISR(23);
    ADD_ISR(24);
    ADD_ISR(25);
    ADD_ISR(26);
    ADD_ISR(27);
    ADD_ISR(28);
    ADD_ISR(29);
    ADD_ISR(30);
    ADD_ISR(31);

    ADD_IRQ(32);
    ADD_IRQ(33);
    ADD_IRQ(34);
    ADD_IRQ(35);
    ADD_IRQ(36);
    ADD_IRQ(37);
    ADD_IRQ(38);
    ADD_IRQ(39);
    ADD_IRQ(40);
    ADD_IRQ(41);
    ADD_IRQ(42);
    ADD_IRQ(43);
    ADD_IRQ(44);
    ADD_IRQ(45);
    ADD_IRQ(46);
    ADD_IRQ(47);

    idt_flush((uint32_t)&m_ptr);
}

void IDT::PIC_remap(uint8_t offset1, uint8_t offset2)
{
    outb(ICW1_INIT | ICW1_ICW4, PIC_MASTER_COMMAND);  // starts the initialization sequence (in cascade mode)
    outb(ICW1_INIT | ICW1_ICW4, PIC_SLAVE_COMMAND);
    outb(offset1, PIC_MASTER_DATA); // ICW2: Master PIC vector offset
    outb(offset2, PIC_SLAVE_DATA);  // ICW2: Slave PIC vector offset
    outb(0x04, PIC_MASTER_DATA);    // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    outb(0x02, PIC_SLAVE_DATA);     // ICW3: tell Slave PIC its cascade identity (0000 0010)

    outb(ICW4_8086, PIC_MASTER_DATA);
    outb(ICW4_8086, PIC_SLAVE_DATA);

    outb(0xFE, PIC_MASTER_DATA);      // Enable only IRQ0
    outb(0xFF, PIC_SLAVE_DATA);
}

void IDT::add_entry(size_t id, uint32_t isr, uint16_t selector, uint8_t flags)
{
    m_entries[id].base_lo = isr & 0xFFFF;
    m_entries[id].base_hi = (isr >> 16) & 0xFFFF;

    m_entries[id].sel     = selector;
    m_entries[id].always0 = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    m_entries[id].flags   = flags /* | 0x60 */;
}

void IDT::set_timer(uint32_t freq)
{
    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    uint32_t divisor = 1193180 / freq;

    // Send the command byte.
    outb(PIT_REPEAT, PIT_COMMAND);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8_t l = (uint8_t)(divisor & 0xFF);
    uint8_t h = (uint8_t)((divisor>>8) & 0xFF);

    // Send the frequency divisor.
    outb(l, PIT_CHAN0_DATA);
    outb(h, PIT_CHAN0_DATA);
}
