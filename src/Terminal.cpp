#include "Terminal.h"


uint8_t Terminal::make_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}


uint16_t Terminal::make_vgaentry(char c)
{
    uint16_t c16 = c;
    uint16_t color16 = color;
    return c16 | color16 << 8;
}


Terminal::Terminal():
    row(0),
    column(0),
    color(make_color(COLOR_LIGHT_GREY, COLOR_BLACK)),
    buffer((uint16_t*) 0xB8000)  // hardware VGA buffer location
{
    for(size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for(size_t x = 0; x < VGA_WIDTH; x++)
        {
            putentryat(' ', x, y);
        }
    }
}


void Terminal::putentryat(char c, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    buffer[index] = make_vgaentry(c);
}


void Terminal::scrollup()
{
    for(size_t y = 1; y < VGA_HEIGHT; y++)
    {
        for(size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            buffer[index - VGA_WIDTH] = buffer[index];
        }
    }
    for(size_t x = 1; x <= VGA_WIDTH; x++)
    {
        const size_t index = VGA_HEIGHT * VGA_WIDTH - x;
        buffer[index] = make_vgaentry(' ');
    }
}


void Terminal::write(char c)
{
    if(c == '\n')
    {
        column = 0;
        if(++row == VGA_HEIGHT)
        {
            row--;
            scrollup();
        }
    } else {
        putentryat(c, column, row);
        if(++column == VGA_WIDTH)
        {
            column = 0;
            if(++row == VGA_HEIGHT)
            {
                row--;
                scrollup();
            }
        }
    }
}


void Terminal::write(const char* data)
{
    size_t i = 0;
    while(data[i] != 0)
        write(data[i++]);
}

