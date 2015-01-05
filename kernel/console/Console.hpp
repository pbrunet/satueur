#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "console.h"

class Console
{
public:
    Console();

    static void write(const char *s);
    static void set_color(enum VGA_COLOR fg, enum VGA_COLOR bg);
    static void finalize();

private:
    static Console* _instance;
    CONSOLE *_console;
};

#endif
