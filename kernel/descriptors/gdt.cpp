#include "gdt.h"
#include <console/Terminal.h>

GDT::GDT()
{
    m_ptr.size= (sizeof(entry_t) * NB_ENTRIES) - 1;
    m_ptr.offset  = (uint32_t)&m_entries;

    add_entry(0, 0, 0, 0, 0);                // Null segment
    add_entry(1, 0, 0x000FFFFF, ACC_BASE | SEG | RING_0 | EXEC | RW,
              GR_BASE | OP32 | GRKB); // Code segment
    add_entry(2, 0, 0x000FFFFF, ACC_BASE | SEG | RING_0 | RW,
              GR_BASE | OP32 | GRKB); // Data segment
    add_entry(3, 0, 0x000FFFFF, ACC_BASE | SEG | RING_3 | EXEC | RW,
              GR_BASE | OP32 | GRKB); // User mode code segment
    add_entry(4, 0, 0x000FFFFF, ACC_BASE | SEG | RING_3 | RW,
              GR_BASE | OP32 | GRKB); // User mode data segment

    gdt_flush((uint32_t)&m_ptr);
    Terminal::write("GDT Initialised\n");
}

void GDT::add_entry(size_t id, uint32_t base, uint32_t limit, uint8_t access,
                    uint8_t granularity)
{
    if(limit>GDT::MAX_LIMIT)
    {
        Terminal::write("Max limit for GDT reached...\n");
        return;
    }

    //Set base
    m_entries[id].base_low = base & 0xFFFF;
    m_entries[id].base_middle = (base >> 16) & 0xFF;
    m_entries[id].base_high = (base >> 24) & 0xFF;

    //Set limit
    m_entries[id].limit_low = limit & 0xFFFF;

    //Set granularity (contains limit_high)
    m_entries[id].granularity = (limit >> 16) & 0x0F;
    m_entries[id].granularity |= granularity & 0xF0;

    //Set access
    m_entries[id].access = access;
}
