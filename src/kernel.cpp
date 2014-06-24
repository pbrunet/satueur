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

/* Hardware text mode color constants. */
enum vga_color
{
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
};


/* make_color
 * ----------
 *
 * Create a 8 bytes color for vga input.
 *
 * Merge foreground and background color in a single 8 bytes variables.
 *
 * bytes :  1 | 2 | 3 | 4 | 5 | 6 | 7 | 8
 * values: bg |bg |bg |bg |fg |fg |fg |fg
 */
uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}


/* make_vgaentry
 * -------------
 *
 * Create a 16 bytes word for vga test input.
 *
 * Merge color and text in a single 16 bytes variables.
 *
 * bytes : 1 ... 8 | 9 ... 16
 * values: colors  | texts
 *
 */
uint16_t make_vgaentry(char c, uint8_t color)
{
    uint16_t c16 = c;
    uint16_t color16 = color;
    return c16 | color16 << 8;
}

//Default size for VGA buffer
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

// Current row location
size_t terminal_row;
// Current column location
size_t terminal_column;
// Current color
uint8_t terminal_color;
// VGA buffer to write text
uint16_t* terminal_buffer;

/*terminal_initialize
 *-------------------
 *
 * Initialize terminal setting cursor at upper right corner and setting
 * the default color. Fill the VGA buffer with space as it could be
 * unititialize.
 */
void terminal_initialize()
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
    // hardware VGA buffer location
    terminal_buffer = (uint16_t*) 0xB8000;
    for(size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for(size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = make_vgaentry(' ', terminal_color);
        }
    }
}


/*terminal_putentryat
 *-------------------
 *
 * Write a char in the terminal.
 */
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = make_vgaentry(c, color);
}


/*terminal_scrollup
 *-----------------
 *
 * Scroll text up for one line in the terminal.
 */
void terminal_scrollup()
{
    for(size_t y = 1; y < VGA_HEIGHT; y++)
    {
        for(size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = terminal_buffer[index - VGA_WIDTH];
        }
    }
}


/*terminal_putchar
 *----------------
 *
 * Write a char in the terminal and move cursor and view accordingly
 */
void terminal_putchar(char c)
{
    if(c == '\n')
    {
        terminal_column = 0;
        if(++terminal_row == VGA_HEIGHT)
        {
            terminal_row--;
            terminal_scrollup();
        }
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if(++terminal_column == VGA_WIDTH)
        {
            terminal_column = 0;
            if(++terminal_row == VGA_HEIGHT)
            {
                terminal_row--;
                terminal_scrollup();
            }
        }
    }
}


/*terminal_writestring
 *--------------------
 *
 * Write the given string in the terminal.
 */
void terminal_writestring(const char* data)
{
    size_t i = 0;
    while(data[i] != 0)
        terminal_putchar(data[i++]);
}


/*kernel_main
 *-----------
 *
 * Startup function for the kernel.
 */
extern "C"
void kernel_main()
{
    terminal_initialize();
    for(size_t i = 0; i < 25; i++)
    {
        terminal_writestring("Hello World!\n");
    }
    terminal_writestring("Hello, kernel World!");
}
