/*
 * @file Terminal.hpp
 */

#ifndef CONSOLE_HPP
#define CONSOLE_HPP

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <stddef.h>
#include <stdint.h>

//------------------------------------------------------------------------------
// constants, enums
//------------------------------------------------------------------------------
//Default size for VGA buffer
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

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

//------------------------------------------------------------------------------
// class
//------------------------------------------------------------------------------
class Console
{
public:
	/*Console
	 *--------
	 *
	 * Initialize terminal setting cursor at upper right corner and setting
	 * the default color. Fill the VGA buffer with space as it could be
	 * uninitialized.
	 *
	 * Console save current buffer to enable use of it from everywhere.
	 * It can't be done with singleton as new allocator doesn't exist for
	 * now.
	 */
	Console();

	/*get
	 *----
	 * Get the current Console instance if exists or create it
	 */
	static Console* get();

	/*write
	 *-----
	 *
	 * Write the given string in the terminal.
	 */
	static void write(const char* data);

	/*write
	 *-----
	 *
	 * Write a char in the terminal and update location and view accordingly
	 */
	static void write(char c);

	/*finalize
	 *--------
	 *Remove the current Console.
	 */
	static void finalize();

private:
	///Methods

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
	uint8_t make_color(enum vga_color fg, enum vga_color bg);

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
	uint16_t make_vgaentry(char c);

	/*putentryat
	 *----------
	 *
	 * Write a char in the terminal.
	 */
	void putentryat(char c, size_t x, size_t y);

	/*scrollup
	 *--------
	 *
	 * Scroll text up for one line in the terminal.
	 */
	void scrollup();

	/*print
	 *-----
	 *
	 * print a character in the terminal and update location
	 */
	void print(char c);

	/*update_cursor
	 *-------------
	 *
	 * update the cursor location according to current location
	 */
	void update_cursor();

	/*clear
	 *-----
	 *
	 * Set all character to empty space in the buffer
	 */
	void clear();

	///Attributs

	static Console* m_instance;
	// Current row location
	size_t row;
	// Current column location
	size_t column;
	// Current color
	uint8_t color;
	// VGA buffer to write text
	uint16_t* buffer;

};

#endif
