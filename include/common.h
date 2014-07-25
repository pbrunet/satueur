#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

void *memset(void* s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memcpy(void *dest, const void *src, size_t n);

#ifdef __cplusplus
}
#endif

#endif
