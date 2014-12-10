/* 
 * @file memcpy.c
 * @author tergeist
 * @date 2014/11/08 17:34:48
 */

#include <string.h>
#include <stdint.h>

void *memcpy(void *dest, const void *src, size_t n)
{
    uint8_t const* byte_src = (uint8_t const*)src;
    uint8_t* byte_dest = (uint8_t*)dest;
    while(n--)
        *byte_dest++ = *byte_src++;
    return dest;
}
