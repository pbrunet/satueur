/* 
 * @file abort.c
 * @author tergeist
 * @date 2014/11/01 18:01:01
 */

#include <stdlib.h>
 
__attribute__((__noreturn__))
void abort(void)
{
	// TODO: Add proper kernel panic.
	//printf("Kernel Panic: abort()\n");
	while ( 1 ) { }
	//__builtin_unreachable();
}
