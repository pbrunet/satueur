//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
// kernel includes
#include <logger/Logger.hpp>

//==============================================================================
//
// Public methods
//
//==============================================================================
//------------------------------------------------------------------------------
// log
//------------------------------------------------------------------------------
void Logger::log(const char* s, enum LOGGER_LOGLEVEL l)
{
    switch(l)
    {
    case LOGGER_LOGLEVEL::INIT:
    {
        printf("[...] %s...\r", s);
        break;
    }
    case LOGGER_LOGLEVEL::INFO:
    {
        printf("[");
        Console::set_color(loglevel_color_info, VGA_COLOR_BLACK);
        printf("info");
        Console::set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printf("] %s  \n", s);
        break;
    }
    case LOGGER_LOGLEVEL::OK:
    {
        printf("[");
        Console::set_color(loglevel_color_ok, VGA_COLOR_BLACK);
        printf(" ok");
        Console::set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printf(" ] %s  \n", s);
        break;
    }
    case LOGGER_LOGLEVEL::FAIL:
    {
        printf("[");
        Console::set_color(loglevel_color_fail, VGA_COLOR_BLACK);
        printf("fail");
        Console::set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printf("] %s  \n", s);
        break;
    }
    default:
        // we shouldn't be here
        break;
    }
}
