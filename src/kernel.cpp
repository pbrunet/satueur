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

#include "Terminal.h"
#include "inout.h"


/*kernel_main
 *-----------
 *
 * Startup function for the kernel.
 */
extern "C"
void kernel_main(struct multiboot *mboot_ptr)
{
    Terminal terminal;
    terminal.write("Hello, kernel World!\b");
    terminal.write("a\n\b");
    terminal.write("\tlato\tla\b\b\bpppp");
    terminal.write("\f");
    for(size_t i = 0; i < 25; i++)
    {
        terminal.write("Hello World!\n");
    }
    terminal.write("Hello, kernel World!\b");
    terminal.write("a\n\b");
    terminal.write("\tlato\tla\b\b\bpppp");
}
