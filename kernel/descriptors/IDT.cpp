//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
// distributed libc includes
#include <sys/io.h>

// kernel include
#include <descriptors/IDT.hpp>
#include <descriptors/isr.hpp>

//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------
//0x08 Means the code section set by the gdt
#define ADD_IRQ(i)                                          \
    add_entry(i, (uint32_t)irq##i , 0x08, F_BASE | RING_0);

//------------------------------------------------------------------------------
// global var
//------------------------------------------------------------------------------
void (*_isr_callbacks_[32])(uint32_t, uint32_t);

//==============================================================================
// 
// Cst / Dst
//
//==============================================================================
//------------------------------------------------------------------------------
// cst
//------------------------------------------------------------------------------
IDT* IDT::m_instance = nullptr;

IDT::IDT()
{
    // singleton instance
    m_instance = this;

    // init m_ptr
    m_ptr.limit = sizeof(entry_t) * NB_ENTRIES -1;
    m_ptr.base  = (uint32_t)&m_entries;

    // init m_entries mem
    memset(&m_entries, 0, sizeof(entry_t) * NB_ENTRIES);

    // Remap PIC to 32-40 for Master PIC and 40-48 for Slave PIC
    PIC_remap(0x20, 0x28);

    // isr 
    add_isr_entries();
    map_isr_callbacks();

    // irq
    add_irq_entries();

    // flush table
    idt_flush((uint32_t)&m_ptr);
}

//==============================================================================
// 
// Public methods
//
//==============================================================================
//------------------------------------------------------------------------------
// isr_handler
//------------------------------------------------------------------------------
void IDT::isr_handler(uint32_t isr_number, uint32_t errcode) 
{
    _isr_callbacks_[isr_number](isr_number, errcode);
}

//------------------------------------------------------------------------------
// set_isr_callback
//------------------------------------------------------------------------------
void IDT::set_isr_callback(uint32_t isr_number, 
                           void (*callback)(uint32_t, uint32_t))
{
    _isr_callbacks_[isr_number] = callback;
}

//------------------------------------------------------------------------------
// set_timer
//------------------------------------------------------------------------------
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

//==============================================================================
// 
// Private methods
//
//==============================================================================
//------------------------------------------------------------------------------
// PIC_remap
//------------------------------------------------------------------------------
void IDT::PIC_remap(uint8_t offset1, uint8_t offset2)
{
    // PIC: Programmable Interrupt Controller
    // Only device directly connected to to the CPU's interrupt pin.
    // 2 PIC: master and slave with each one 8 IRQ lines. Thus, we have 15
    // IRQ lines available (16 - 1 lines for communication. Slave PIC is behind
    // the Master).
    // A remap is necessary to avoid conflict between ISR and IRQ (same adress).

    /* reinitialize the PIC controllers, giving them specified vector offsets
     * rather than 8h and 70h, as configured by default */

    // starts the initialization sequence (in cascade mode)
    outb(ICW1_INIT | ICW1_ICW4, PIC_MASTER_COMMAND);
    outb(ICW1_INIT | ICW1_ICW4, PIC_SLAVE_COMMAND);
    
    // ICW2: Master PIC vector offset
    outb(offset1, PIC_MASTER_DATA); 
    // ICW2: Slave PIC vector offset
    outb(offset2, PIC_SLAVE_DATA);  
    // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    outb(0x04, PIC_MASTER_DATA);    
    // ICW3: tell Slave PIC its cascade identity (0000 0010)
    outb(0x02, PIC_SLAVE_DATA);    

    outb(ICW4_8086, PIC_MASTER_DATA);
    outb(ICW4_8086, PIC_SLAVE_DATA);

    // Enable only IRQ0
    outb(0xFE, PIC_MASTER_DATA);      
    outb(0xFF, PIC_SLAVE_DATA);
}

//------------------------------------------------------------------------------
// add_isr_entries
//------------------------------------------------------------------------------
void IDT::add_isr_entries()
{
    // ISR: Interrupt Service Routine
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
}

//------------------------------------------------------------------------------
// add_irq_entries
//------------------------------------------------------------------------------
void IDT::add_irq_entries()
{
    // IRQ: Interrupt Request (from PIC device)
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
}

//------------------------------------------------------------------------------
// map_isr_callbacks
//------------------------------------------------------------------------------
void IDT::map_isr_callbacks()
{
    // TODO : map all error/except to specific fcts

    // 0 - Division by zero exception - no error code
    _isr_callbacks_[0] = isr_divide_by_zero_except_callback;

    for (int j=1; j<8; j++)
        _isr_callbacks_[j] = isr_default_callback;

    // 1 - Debug exception
    //_isr_callbacks_[1] = isr_debug_except_callback;

    // 2 - Non maskable interrupt
    //_isr_callbacks_[2] = isr_non_mask_int_callback;

    // 3 - Breakpoint exception
    //_isr_callbacks_[3] = isr_breakpoint_except_callback;

    // 4 - 'Into detected overflow'
    //_isr_callbacks_[4] = isr_overflow_callback;

    // 5 - Out of bounds exception
    //_isr_callbacks_[5] = isr_out_of_bound_except_callback;

    // 6 - Invalid opcode exception
    //_isr_callbacks_[6] = isr_invalid_opcode_except_callback;

    // 7 - No coprocessor exception
    //_isr_callbacks_[7] = isr_nocoprocessor_except_callback;

    // 8 - Double fault (pushes an error code)
    _isr_callbacks_[8] = isr_dble_fault_callback;

    // 9 - Coprocessor segment overrun
    //_isr_callbacks_[9] = isr_coprocessor_seg_overrun_callback;

    // 10 - Bad TSS (pushes an error code)
    //_isr_callbacks_[10] = isr_invalid_opcode_except_callback;

    // 11 - Segment not present (pushes an error code)
    //_isr_callbacks_[11] = isr_seg_not_present_callback;

    // 12 - Stack fault (pushes an error code)
    //_isr_callbacks_[12] = isr_stack_fault_callback;

    // 13 - General protection fault (pushes an error code)
    //_isr_callbacks_[13] = isr_general_prot_fault_callback;

    // 14 - Page fault (pushes an error code)
    //_isr_callbacks_[14] = isr_page_fault_callback;

    // 15 - Unknown interrupt exception
    //_isr_callbacks_[15] = isr_unknown_int_except_callback;

    // 16 - Coprocessor fault
    //_isr_callbacks_[16] = isr_coprocessor_fault_callback;

    // 17 - Alignment check exception
    //_isr_callbacks_[17] = isr_align_check_except_callback;

    // 18 - Machine check exception
    //_isr_callbacks_[18] = isr_machine_check_except_callback;

    // 19-31 - Reserved
    for (int j=9; j<32; j++)
        _isr_callbacks_[j] = isr_default_callback;
}

//------------------------------------------------------------------------------
// add_entry
//------------------------------------------------------------------------------
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
