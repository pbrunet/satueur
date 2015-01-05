//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
// system includes
#include <stddef.h>
#include <stdint.h>

// kernel include
#include <logger/Logger.hpp>
#include <descriptors/GDT.hpp>
#include <descriptors/IDT.hpp>
#include <console/Console.hpp>

#ifdef STR_DEBUG
#include <autotests/AutoTests.hpp>
#endif

//------------------------------------------------------------------------------
// check
//------------------------------------------------------------------------------
// Check if the compiler thinks if we are targeting the wrong operating system
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

// For now, it only works for the 32-bit x86 targets
#if !defined(__i386__)
#error "This kernel needs to be compiled with a ix86-elf compiler"
#endif

//==============================================================================
//
// Functions
//
//==============================================================================
//------------------------------------------------------------------------------
// kernel_main: startup function for the kernel
//------------------------------------------------------------------------------
extern "C"
void kernel_main(struct multiboot */*mboot_ptr*/)
{
    // first thing todo: init console!
    Console console;

    // loading msg
    Console::write("Loading, please wait...\n");

    // GDT
    Logger::log("Loading GDT", LOGGER_LOGLEVEL::INIT);
    volatile GDT gdt;
    Logger::log("Loading GDT", LOGGER_LOGLEVEL::OK);

    // IDT
    Logger::log("Loading IDT", LOGGER_LOGLEVEL::INIT);
    IDT idt;
    Logger::log("Loading IDT", LOGGER_LOGLEVEL::OK);

#ifdef STR_DEBUG
    Logger::log("Kernel initialized in debug mode", LOGGER_LOGLEVEL::INFO);
    AutoTests at;
    at.init_isr_tests();
    //at.test_divide_by_zero(); // abort
#else
    Logger::log("Kernel initialized in normal mode", LOGGER_LOGLEVEL::INFO);
#endif

    //myidt.set_timer(4);

    while(true);
}
