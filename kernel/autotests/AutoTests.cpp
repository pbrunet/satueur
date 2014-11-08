/*
 * @file AutoTests.cpp
 */

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <autotests/AutoTests.hpp>
#include <autotests/isr_test_callback.hpp>
#include <console/Console.hpp>

//==============================================================================
// 
// Cst / Dst
//
//==============================================================================
//------------------------------------------------------------------------------
// cst
//------------------------------------------------------------------------------
AutoTests::AutoTests()
{
}

//==============================================================================
// 
// Public methods
//
//==============================================================================
//------------------------------------------------------------------------------
// init_isr_tests
//------------------------------------------------------------------------------
void AutoTests::init_isr_tests()
{
	init_isr_tests_callbacks();
	init_isr_tests_asm_int();
}

//------------------------------------------------------------------------------
// test_divide_by_zero
//------------------------------------------------------------------------------
void AutoTests::test_divide_by_zero()
{
	Console::write('a'/0);
}

//==============================================================================
// 
// Private methods
//
//==============================================================================
//------------------------------------------------------------------------------
// init_isr_tests_callbacks
//------------------------------------------------------------------------------
void AutoTests::init_isr_tests_callbacks()
{
	Console::write("AUTOTESTS\n");

	// doesn't test isr with error code because it has to be aborted
	IDT::set_isr_callback(0, isr0_test_callback);
	IDT::set_isr_callback(1, isr1_test_callback);
	IDT::set_isr_callback(2, isr2_test_callback);
	IDT::set_isr_callback(3, isr3_test_callback);
	IDT::set_isr_callback(4, isr4_test_callback);
	IDT::set_isr_callback(5, isr5_test_callback);
	IDT::set_isr_callback(6, isr6_test_callback);
	IDT::set_isr_callback(7, isr7_test_callback);
	IDT::set_isr_callback(9, isr9_test_callback);
	IDT::set_isr_callback(15, isr15_test_callback);	
	IDT::set_isr_callback(16, isr16_test_callback);	
	IDT::set_isr_callback(17, isr17_test_callback);	
	IDT::set_isr_callback(18, isr18_test_callback);	
	IDT::set_isr_callback(19, isr19_test_callback);		
}

//------------------------------------------------------------------------------
// init_isr_tests_asm_int
//------------------------------------------------------------------------------
void AutoTests::init_isr_tests_asm_int()
{
	asm volatile ("int $0x00"); // ISR 1
	asm volatile ("int $0x01"); // ISR 1
	asm volatile ("int $0x02"); // ISR 2
	asm volatile ("int $0x03"); // ISR 3
	asm volatile ("int $0x04"); // ISR 4
	asm volatile ("int $0x05"); // ISR 5
	asm volatile ("int $0x06"); // ISR 6
	asm volatile ("int $0x07"); // ISR 7
	
    //asm volatile ("int $0x08"); // ISR 8: error code => abort
	
	asm volatile ("int $0x09"); // ISR 9

	//asm volatile ("int $0x0A"); // ISR 10: error code => abort
	//asm volatile ("int $0x0B"); // ISR 11: error code => abort
	//asm volatile ("int $0x0C"); // ISR 12: error code => abort
	//asm volatile ("int $0x0D"); // ISR 13: error code => abort
	//asm volatile ("int $0x0E"); // ISR 14: error code => abort

	asm volatile ("int $0x0F"); // ISR 15
	asm volatile ("int $0x10"); // ISR 16
	asm volatile ("int $0x11"); // ISR 17
	asm volatile ("int $0x12"); // ISR 18
	asm volatile ("int $0x13"); // ISR 19
}
