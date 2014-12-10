//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <descriptors/registers.h>
#include <stdint.h>

//------------------------------------------------------------------------------
// macros
//------------------------------------------------------------------------------
//0x08 Means the code section set by the gdt
#define ADD_ISR(i)											\
    add_entry(i, (uint32_t)isr##i , 0x08, F_BASE | RING_0);

//------------------------------------------------------------------------------
// C
//------------------------------------------------------------------------------
extern "C" void isr_handler(registers_t*);

extern "C" void isr_default_callback(uint32_t, uint32_t);
extern "C" void isr_divide_by_zero_except_callback(uint32_t, uint32_t);
extern "C" void isr_dble_fault_callback(uint32_t, uint32_t);

//------------------------------------------------------------------------------
// Asm
//------------------------------------------------------------------------------
// Defined in interrupt.s
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

// Defined in idt_flush.s
extern "C" void idt_flush(uint32_t);
