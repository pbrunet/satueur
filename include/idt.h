#ifndef IDT_H
#define IDT_H

#include <stddef.h>
#include <stdint.h>

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

        enum flags: uint8_t {
            RING_0=0x00,
            RING_1=0x20,
            RING_2=0x40,
            RING_3=0x60,
            F_BASE=0x8E
        };
        
        // Ports use to communicate with PIC master and slaves controllers.
        // DATA access interrupt mask. COMMAND is about general settings.
        enum pic_port: uint8_t {
            PIC_MASTER_DATA=0x21,
            PIC_MASTER_COMMAND=0x20,
            PIC_SLAVE_DATA=0xA1,
            PIC_SLAVE_COMMAND=0xA0,
            PIT_COMMAND=0x43,
            PIT_CHAN0_DATA=0x40
        };

        // Initialisation word 1 for PIC communication.
        // ICW1 : Global initialisation
        enum pic_icw1: uint8_t {
            ICW1_INIT=0x10, // Base initialization
            ICW1_ICW4=0x01, // Need ICW4
        };

        // Initialisation word 4 for PIC communication.
        // ICW4 : Gives additional information about the environment.
        enum pic_icw4: uint8_t {
            ICW4_8086=0x01, // Use 8086 mode
        };

        enum pic_command: uint8_t {
            PIC_EOI=0x20, // End of interruption signal
            PIT_REPEAT=0x36, // Set PIT to repeat mode and ask for speed
        };

        constexpr static uint16_t NB_ENTRIES = 256;

        IDT();
        void set_timer(uint32_t freq);

    private:
        entry_t m_entries[NB_ENTRIES];
        ptr_t m_ptr;
        void add_entry(size_t i, uint32_t isr, uint16_t selector, uint8_t flags);

        /* reinitialize the PIC controllers, giving them specified vector offsets
         * rather than 8h and 70h, as configured by default */
        void PIC_remap(uint8_t offset1, uint8_t offset2);
};

// These extern directives let us access the addresses of our ASM ISR handlers.
extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

extern "C" void irq32();
extern "C" void irq33();
extern "C" void irq34();
extern "C" void irq35();
extern "C" void irq36();
extern "C" void irq37();
extern "C" void irq38();
extern "C" void irq39();
extern "C" void irq40();
extern "C" void irq41();
extern "C" void irq42();
extern "C" void irq43();
extern "C" void irq44();
extern "C" void irq45();
extern "C" void irq46();
extern "C" void irq47();

extern "C" void idt_flush(uint32_t);

#endif
