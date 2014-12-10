/* 
 * @file memset.c
 * @author tergeist
 * @date 2014/11/08 17:35:48
 */

#include <string.h>
#include <stdint.h>

void *memset(void* s, int c, size_t n)
{
    uint8_t* byte_ptr = (uint8_t*)s;
    while(n--)
        *byte_ptr++ = c;
    return s;
}
