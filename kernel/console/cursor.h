#ifndef CURSOR_H
#define CURSOR_H

#include <stdint.h>

#define CURSOR_BYTE_LOW 0x0F
#define CURSOR_BYTE_HIGH 0x0E

void cursor_update(uint32_t row, uint32_t column, uint32_t width);

#endif
