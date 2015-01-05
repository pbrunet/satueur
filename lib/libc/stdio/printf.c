//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
// system includes
#include <stdarg.h>

// kernel includes
#include <console/console.h>

// libc includes
#include <stdio.h>
#include <stdlib.h>

//==============================================================================
// 
// Functions
//
//==============================================================================
//------------------------------------------------------------------------------
// prints
//------------------------------------------------------------------------------
int32_t prints(const char* s)
{
    int32_t written = 0;

    while(*s != 0)
    {
        console_putchar(*s++);
        written++;
    }

    return written;
}

//------------------------------------------------------------------------------
// printi
//------------------------------------------------------------------------------
int32_t printi(size_t size, uint32_t base, int32_t value)
{
    char maxbuf[size+1];
    itoa(value, maxbuf, base);

    char buf[strlen(maxbuf)];
    for(size_t j=0; j<strlen(maxbuf); j++)
        buf[j] = maxbuf[j];
    buf[strlen(maxbuf)] = '\0';

    return prints(buf);
}

//------------------------------------------------------------------------------
// printf
//------------------------------------------------------------------------------
int printf(const char* restrict format, ...)
{
    int32_t written = 0;
	va_list args;
	va_start(args, format);

    // print
    while(*format != '\0')
    {
		if ( *format != '%' )
        {
            console_putchar(*format);
            format++;
            written++;
        }
        else
        {
            format++;
            
            if( *format == 'c' )
            {
                char c = (char) va_arg(args, int);
                console_putchar(c);
                written++;
            }
            else if ( *format == 's' )
            {
                const char* s = va_arg(args, const char*);
                written += prints(s);
            }
            else if ( *format == 'x' )
            {
                int32_t i = va_arg(args, int32_t);
                written += printi(4, 16, i); // 32bits => 4 bytes
                
            }
            else if ( *format == 'd' )
            {
                int32_t i = va_arg(args, int32_t);
                written += printi(11, 10, i); // 32bits max value: 2147483647
            }
            format++;
        }
    }

    va_end(args);

    return written;
}
