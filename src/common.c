#include "common.h"

void *memset(void* s, int c, size_t n)
{
    uint8_t* byte_ptr = (uint8_t*)s;
    while(n--)
        *byte_ptr++ = c;
    return s;
}

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

void *memcpy(void *dest, const void *src, size_t n)
{
    uint8_t const* byte_src = (uint8_t const*)src;
    uint8_t* byte_dest = (uint8_t*)dest;
    while(n--)
        *byte_dest++ = *byte_src++;
    return dest;
}
