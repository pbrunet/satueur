/*
 * @file main.cpp
 */

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* For now, it only work for the 32-bit x86 targets. */
#if !defined(__i386__)
#error "This kernel needs to be compiled with a ix86-elf compiler"
#endif

#if defined STR_AUTOTEST && (STR_AUTOTEST+0) == 1
#include <autotests/AutoTests.hpp>
#endif

#include <console/Console.hpp>
#include <tools/inout.h>
#include <descriptors/GDT.hpp>
#include <descriptors/IDT.hpp>

//------------------------------------------------------------------------------
// kernel_main: startup function for the kernel
//------------------------------------------------------------------------------
extern "C"
void kernel_main(struct multiboot */*mboot_ptr*/)
{
	// console
	Console terminal;
	Console::write("Starting kernel\n");

	// descriptors tables
	volatile GDT mygdt;
	IDT myidt;

	Console::write("Kernel initialized\n");

#if defined STR_AUTOTEST && (STR_AUTOTEST+0) == 1
	AutoTests at;
	at.init_isr_tests();
	at.test_divide_by_zero();
#endif

	//myidt.set_timer(4);

	while(true);
}
