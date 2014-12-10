//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <console/Console.hpp>
#include <string.h>
#include <tools/inout.h>

//------------------------------------------------------------------------------
// constants and enums
//------------------------------------------------------------------------------
// hardware VGA buffer location
constexpr uint16_t* VGA_BUFFER = reinterpret_cast<uint16_t*>(0xB8000);

enum VGA_PORT: uint16_t {
	CURSOR_BYTE_POS=0x3D4,
	CURSOR_POS=0x3D5
};

enum BYTE_POS: uint8_t {
	LOW=0x0F,
	HIGH=0x0E
};

//==============================================================================
// 
// Cst / Dst
//
//==============================================================================
//------------------------------------------------------------------------------
// cst
//------------------------------------------------------------------------------
Console* Console::m_instance = nullptr;

Console::Console():
	row(0),
	column(0),
	color(make_color(COLOR_LIGHT_GREY, COLOR_BLACK)),
	buffer(VGA_BUFFER)
{
	m_instance = this;
	clear();
}

//==============================================================================
// 
// Public functions
//
//==============================================================================
//------------------------------------------------------------------------------
// get
//------------------------------------------------------------------------------
Console* Console::get()
{
	return m_instance;
}

//------------------------------------------------------------------------------
// write
//------------------------------------------------------------------------------
void Console::write(const char* data)
{
	size_t i = 0;
	while(data[i] != 0)
		m_instance->print(data[i++]);
	m_instance->update_cursor();
}

//------------------------------------------------------------------------------
// write
//------------------------------------------------------------------------------
void Console::write(char c)
{
	m_instance->print(c);
	m_instance->update_cursor();
}

//------------------------------------------------------------------------------
// finalize
//------------------------------------------------------------------------------
void Console::finalize()
{
	m_instance = nullptr;
}

//==============================================================================
// 
// Private functions
//
//==============================================================================
//------------------------------------------------------------------------------
// make_color
//------------------------------------------------------------------------------
uint8_t Console::make_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

//------------------------------------------------------------------------------
// make_vgaentry
//------------------------------------------------------------------------------
uint16_t Console::make_vgaentry(char c)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

//------------------------------------------------------------------------------
// clear
//------------------------------------------------------------------------------
void Console::clear()
{
	for(size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for(size_t x = 0; x < VGA_WIDTH; x++)
		{
			putentryat(' ', x, y);
		}
	}
}

//------------------------------------------------------------------------------
// putentryat
//------------------------------------------------------------------------------
void Console::putentryat(char c, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	buffer[index] = make_vgaentry(c);
}

//------------------------------------------------------------------------------
// scrollup
//------------------------------------------------------------------------------
void Console::scrollup()
{
	memmove(buffer, buffer + VGA_WIDTH, (VGA_HEIGHT - 1) * VGA_WIDTH);
	for(size_t x = 1; x <= VGA_WIDTH; x++)
	{
		const size_t index = VGA_HEIGHT * VGA_WIDTH - x;
		buffer[index] = make_vgaentry(' ');
	}
}

//------------------------------------------------------------------------------
// print
//------------------------------------------------------------------------------
void Console::print(char c)
{
	if(c == '\n')
	{
		column = 0;
		if(++row == VGA_HEIGHT)
		{
			row--;
			scrollup();
		}
	} else if(c == '\b')
	{
		column = column ? column - 1 : column;
	} else if(c == '\t')
	{
		column += 4 - column % 4;
		row += column / 80;
		column = column % 80;
	} else if(c == '\f')
	{
		clear();
		column = 0;
		row = 0;
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

//------------------------------------------------------------------------------
// update_cursor
//------------------------------------------------------------------------------
void Console::update_cursor()
{
	unsigned short position=(row * VGA_WIDTH) + column;

	// cursor LOW port to vga INDEX register
	outb(BYTE_POS::LOW, VGA_PORT::CURSOR_BYTE_POS);
	outb((unsigned char)(position & 0xFF), VGA_PORT::CURSOR_POS);
	// cursor HIGH port to vga INDEX register
	outb(BYTE_POS::HIGH, VGA_PORT::CURSOR_BYTE_POS);
	outb((unsigned char)((position>>8) & 0xFF), VGA_PORT::CURSOR_POS);
}
