#include <sys/io.h>
#include "cursor.h"
#include "vga.h"

void cursor_update(uint32_t row, uint32_t column, uint32_t width)
{
    unsigned short position=(row * width) + column;
    
    // cursor LOW port to vga INDEX register
    outb(CURSOR_BYTE_LOW, VGA_CONTROLLER_PORT_LOW);
    outb((unsigned char)(position & 0xFF), VGA_CONTROLLER_PORT_HIGH);

    // cursor HIGH port to vga INDEX register
    outb(CURSOR_BYTE_HIGH, VGA_CONTROLLER_PORT_LOW);
    outb((unsigned char)((position>>8) & 0xFF), VGA_CONTROLLER_PORT_HIGH);
}
