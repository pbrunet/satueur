/* 
 * @file memmove.c
 * @author tergeist
 * @date 2014/11/08 17:31:34
 */

#include <string.h>
#include <stdint.h>

void *memmove(void *dest, const void *src, size_t n)
{
    uint8_t const* byte_src = (uint8_t const*)src;
    uint8_t* byte_dest = (uint8_t*)dest;
    if(dest < src) {
        while(n--)
            *byte_dest++ = *byte_src++;
    } else {
        byte_src += n;
        byte_dest += n;
        while(n--)
            *--byte_dest = *--byte_src;
    }
    return dest;
}
