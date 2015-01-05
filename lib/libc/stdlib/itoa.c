#include <stdlib.h>

char* itoa(int value, char *str, int base)
{
    // var
    char * rc;
    char * ptr;
    char * low;

    // check base
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;

    // manage negative value for base 10
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    low = ptr;

    // convert with a trick to avoid a call to abs() function
    do
    {
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );

    // end the string
    *ptr-- = '\0';

    // 
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    
    // return value
    return rc;
}
