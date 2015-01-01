//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
// system include
#include <stddef.h>

// libc includes
#include <string.h>

// local includes
#include "console.h"
#include "cursor.h"

//------------------------------------------------------------------------------
// static
//------------------------------------------------------------------------------
static CONSOLE console = {0};

//==============================================================================
// 
// Private functions
//
//==============================================================================
//------------------------------------------------------------------------------
// __console_getcolor
//------------------------------------------------------------------------------
static inline uint8_t __console_getcolor()
{
    return console.fg | console.bg << 4;
}

//------------------------------------------------------------------------------
// __console_getindex
//------------------------------------------------------------------------------
static inline size_t __console_getindex(uint32_t x, uint32_t y)
{
    return (size_t) 2 * y * console.width + 2 * x;
}

//------------------------------------------------------------------------------
// __console_getentry
//------------------------------------------------------------------------------
static inline uint16_t __console_getentry(char c)
{
    uint16_t c16 = c;
    uint16_t color16 = __console_getcolor();
    return c16 | color16 << 8;
}

//------------------------------------------------------------------------------
// __console_putcharat
//------------------------------------------------------------------------------
static inline void __console_putcharat(char c, uint32_t column, uint32_t row)
{
    *(uint16_t*)(VGA_TEXT_MODE_VIDEO_MEMORY_BUFFER 
                 + __console_getindex(column, row)) = 
        __console_getentry(c);
}

//------------------------------------------------------------------------------
// __console_clear
//------------------------------------------------------------------------------
void __console_clear()
{
    for(size_t x = 0; x < console.width; x++)
    {
        for(size_t y = 0; y < console.height; y++)
        {
            __console_putcharat(' ', x, y);
        }
    }
}

//------------------------------------------------------------------------------
// __console_scrollup
//------------------------------------------------------------------------------
void __console_scrollup()
{
    for(size_t row = 0; row < console.height; row++)
    {
        memcpy((char *)(VGA_TEXT_MODE_VIDEO_MEMORY_BUFFER 
                        + row*console.width*2) ,
               (char *)(VGA_TEXT_MODE_VIDEO_MEMORY_BUFFER 
                        + (row+1)*console.width*2),
               console.width*2);
    }
}

//==============================================================================
// 
// Public functions
//
//==============================================================================
//------------------------------------------------------------------------------
// console_init
//------------------------------------------------------------------------------
CONSOLE* console_init() 
{
    // init console static variable
    console.width = VGA_SIZE_WIDTH;
    console.height = VGA_SIZE_HEIGHT;
    console.tab = CONSOLE_TAB_SIZE;
    console.row = 0;
    console.column = 0;
    console.fg = VGA_COLOR_LIGHT_GREY;
    console.bg = VGA_COLOR_BLACK;

    // clear 
    __console_clear();

    return &console;
}

//------------------------------------------------------------------------------
// console_putchar
//------------------------------------------------------------------------------
void console_putchar(char c)
{    
    if(c == '\n')
    {
        console.column = 0;
        if( ++console.row == console.height )
        {
            console.row--;
            __console_scrollup();
        }
    }
    else if (c == '\r')
    {
        console.column = 0;
    }
    else if(c == '\b')
    {
        console.column = console.column ? console.column - 1 : console.column;
    }
    else if(c == '\t')
    {
        console.column += console.tab - console.column % console.tab;
        console.row += console.column / console.width;
        console.column = console.column % console.width;
    }
    else if(c == '\f')
    {
        __console_clear();
        console.column = 0;
        console.row = 0;
    }
    else 
    {
        __console_putcharat(c, console.column, console.row);
        if(++console.column == console.width)
        {
            console.column = 0;
            if(++console.row == console.height)
            {
                console.row--;
                __console_scrollup();
            }
        }
    }

    cursor_update(console.row, console.column, console.width);
}
