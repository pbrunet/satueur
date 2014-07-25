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
#include "gdt.h"


/*kernel_main
 *-----------
 *
 * Startup function for the kernel.
 */
extern "C"
void kernel_main(struct multiboot *mboot_ptr)
{
    Terminal terminal;
    Terminal::write("Starting kernel\n");
    GDT();
}
