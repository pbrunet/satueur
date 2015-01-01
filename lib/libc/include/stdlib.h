#ifndef STDLIB_H
#define STDLIB_H
 
#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

char* itoa(int value, char *str, int base);
__attribute__((__noreturn__)) void abort(void);

#ifdef __cplusplus
}
#endif

#endif
