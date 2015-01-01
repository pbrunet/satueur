#ifndef CONSOLE_H
#define CONSOLE_H

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
// system includes
#include <stdint.h>

// local includes
#include "vga.h"

//------------------------------------------------------------------------------
// constants, struct, enums
//------------------------------------------------------------------------------
#define CONSOLE_TAB_SIZE 4

typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t tab;
    uint32_t row;
    uint32_t column;
    enum VGA_COLOR fg;
    enum VGA_COLOR bg;
} CONSOLE;

//------------------------------------------------------------------------------
// functions
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

CONSOLE* console_init();
void console_putchar(char c);

#ifdef __cplusplus
}
#endif

#endif
