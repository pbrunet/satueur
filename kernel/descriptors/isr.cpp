/* 
 * @file isr.cpp
 * @author tergeist
 * @date 2014/11/02 17:54:14
 */

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <descriptors/isr.hpp>
#include <descriptors/IDT.hpp>
#include <console/Console.hpp>

#include <stdlib.h>

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
    Console::write("isr_default_callback ");
	Console::write('0'+isr_number);
	Console::write("\n");
}

//------------------------------------------------------------------------------
// isr_divide_by_zero_except_callback
//------------------------------------------------------------------------------
void isr_divide_by_zero_except_callback(uint32_t /*isr_number*/, 
										uint32_t /*errcode*/)
{
    Console::write("[ERROR] Division by zero.\n");
	abort();
}

//------------------------------------------------------------------------------
// isr_dble_fault_callback
//------------------------------------------------------------------------------
void isr_dble_fault_callback(uint32_t /*isr_number*/, 
							 uint32_t errcode)
{
    Console::write("[ERROR] Double fault (errcode = ");
	Console::write('0'+errcode);
	Console::write(" ).\n");
	Console::write("\n");
	abort();	
}
