#include "idt.h"
#include "common.h"


//0x08 Means the code section set by the gdt
#define ADD_ENTRY(i)\
    add_entry(i, (uint32_t)isr##i , 0x08, F_BASE | RING_0);

IDT::IDT()
{
    m_ptr.limit = sizeof(entry_t) * NB_ENTRIES -1;
    m_ptr.base  = (uint32_t)&m_entries;

    memset(&m_entries, 0, sizeof(entry_t) * NB_ENTRIES);

    ADD_ENTRY(0);
    ADD_ENTRY(1);
    ADD_ENTRY(2);
    ADD_ENTRY(3);
    ADD_ENTRY(4);
    ADD_ENTRY(5);
    ADD_ENTRY(6);
    ADD_ENTRY(7);
    ADD_ENTRY(8);
    ADD_ENTRY(9);
    ADD_ENTRY(10);
    ADD_ENTRY(11);
    ADD_ENTRY(12);
    ADD_ENTRY(13);
    ADD_ENTRY(14);
    ADD_ENTRY(15);
    ADD_ENTRY(16);
    ADD_ENTRY(17);
    ADD_ENTRY(18);
    ADD_ENTRY(19);
    ADD_ENTRY(20);
    ADD_ENTRY(21);
    ADD_ENTRY(22);
    ADD_ENTRY(23);
    ADD_ENTRY(24);
    ADD_ENTRY(25);
    ADD_ENTRY(26);
    ADD_ENTRY(27);
    ADD_ENTRY(28);
    ADD_ENTRY(29);
    ADD_ENTRY(30);
    ADD_ENTRY(31);

    idt_flush((uint32_t)&m_ptr);
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
