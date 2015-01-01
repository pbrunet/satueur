//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
// libc includes
#include <stdlib.h>
#include <stdio.h>

// kernel includes
#include <logger/Logger.hpp>
#include <descriptors/isr.hpp>
#include <descriptors/IDT.hpp>

//==============================================================================
// 
// C functions
//
//==============================================================================
//------------------------------------------------------------------------------
// isr_handler
//------------------------------------------------------------------------------
void isr_handler(registers_t* regs)
{
    IDT::isr_handler(regs->int_no);
}

//------------------------------------------------------------------------------
// isr_default_callback
//------------------------------------------------------------------------------
void isr_default_callback(uint32_t isr_number, uint32_t /*errcode*/)
{
    printf("isr_default_callback %d\n", isr_number);
}

//------------------------------------------------------------------------------
// isr_divide_by_zero_except_callback
//------------------------------------------------------------------------------
void isr_divide_by_zero_except_callback(uint32_t /*isr_number*/, 
                                        uint32_t /*errcode*/)
{
    Logger::log("Division by zero", LOGGER_LOGLEVEL::FAIL);
    abort();
}

//------------------------------------------------------------------------------
// isr_dble_fault_callback
//------------------------------------------------------------------------------
void isr_dble_fault_callback(uint32_t /*isr_number*/, 
                             uint32_t errcode)
{
    printf("[ERROR] Double fault (errcode = %d ).\n\n", errcode);
    abort();    
}
