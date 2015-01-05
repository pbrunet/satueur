//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
// system includes
#include <stdint.h>

// libc includes
#include <stdio.h>

// kernel includes
#include <console/Console.hpp>

//------------------------------------------------------------------------------
// enum, const
//------------------------------------------------------------------------------
const enum VGA_COLOR loglevel_color_none = VGA_COLOR_BLACK;
const enum VGA_COLOR loglevel_color_info = VGA_COLOR_CYAN;
const enum VGA_COLOR loglevel_color_ok = VGA_COLOR_GREEN;
const enum VGA_COLOR loglevel_color_fail = VGA_COLOR_RED;

enum LOGGER_LOGLEVEL
{
    INIT,
    INFO,
    OK,
    FAIL
};

//------------------------------------------------------------------------------
// class
//------------------------------------------------------------------------------
class Logger
{
public:
    Logger();
    ~Logger();
    
    static void log(const char* s, enum LOGGER_LOGLEVEL);
};
