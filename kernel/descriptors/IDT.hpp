#ifndef IDT_HPP
#define IDT_HPP

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <descriptors/registers.h>

//------------------------------------------------------------------------------
// class IDT
//------------------------------------------------------------------------------
class IDT {
public:
    // A struct describing an interrupt gate.

//selector
//--------
//Always set to 0
//
//flags
//-----
//  7                           0
//  +---+---+---+---+---+---+---+---+
//  | P |  DPL  | S |    GateType   |
//  +---+---+---+---+---+---+---+---+
//
//  P : presence of interrupt (set to 0 will cause triple fault if interrupt
//      is called
//  DPL: Descriptor privilege (ring level)
//  S  : 0 for interrupt gate
//  GateType : 0b1110 for 32-bit interrupt gate
    struct entry_struct
    {
        uint16_t base_lo;        // The lower 16 bits of the address to jump to when this interrupt fires.
        uint16_t sel;            // Kernel segment selector.
        uint8_t  always0;        // This must always be zero.
        uint8_t  flags;          // More flags. See documentation.
        uint16_t base_hi;        // The upper 16 bits of the address to jump to.
    } __attribute__((packed));
    typedef struct entry_struct entry_t;

    // A struct describing a pointer to an array of interrupt handlers.
    // This is in a format suitable for giving to 'lidt'.
    struct ptr_struct
    {
        uint16_t limit;
        uint32_t base;        // The address of the first element in our entry_t array.
    } __attribute__((packed));
    typedef struct ptr_struct ptr_t;

    enum flags: uint8_t 
    {
        RING_0=0x00,
        RING_1=0x20,
        RING_2=0x40,
        RING_3=0x60,
        F_BASE=0x8E
    };
        
    // Ports use to communicate with PIC master and slaves controllers.
    // DATA access interrupt mask. COMMAND is about general settings.
    enum pic_port: uint8_t 
    {
        PIC_MASTER_DATA=0x21,
        PIC_MASTER_COMMAND=0x20,
        PIC_SLAVE_DATA=0xA1,
        PIC_SLAVE_COMMAND=0xA0,
        PIT_COMMAND=0x43,
        PIT_CHAN0_DATA=0x40
    };

    // Initialisation word 1 for PIC communication.
    // ICW1 : Global initialisation
    enum pic_icw1: uint8_t 
    {
        ICW1_INIT=0x10, // Base initialization
        ICW1_ICW4=0x01 // Need ICW4
    };

    // Initialisation word 4 for PIC communication.
    // ICW4 : Gives additional information about the environment.
    enum pic_icw4: uint8_t 
    {
        ICW4_8086=0x01 // Use 8086 mode
    };

    enum pic_command: uint8_t 
    {
        PIC_EOI=0x20, // End of interruption signal
        PIT_REPEAT=0x36 // Set PIT to repeat mode and ask for speed
    };

    constexpr static uint16_t NB_ENTRIES = 256;

    IDT();

    static void isr_handler(uint32_t isr_number, uint32_t errcode=0);
    static void set_isr_callback(uint32_t isr_number, 
                                 void (*callback)(uint32_t, uint32_t));

    void set_timer(uint32_t freq);


private:
    // meths
    void add_isr_entries();
    void map_isr_callbacks();
    void add_irq_entries();
    void add_entry(size_t i, uint32_t isr, uint16_t selector, uint8_t flags);
    void PIC_remap(uint8_t offset1, uint8_t offset2);

    // attr
    static IDT* m_instance;

    entry_t m_entries[NB_ENTRIES];
    ptr_t m_ptr;
};

#endif
