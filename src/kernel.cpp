#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* For now, it only work for the 32-bit x86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#include "Terminal.h"


/*kernel_main
 *-----------
 *
 * Startup function for the kernel.
 */
extern "C"
void kernel_main()
{
    Terminal terminal;
    for(size_t i = 0; i < 25; i++)
    {
        terminal.write("Hello World!\n");
    }
    terminal.write("Hello, kernel World!");
}
