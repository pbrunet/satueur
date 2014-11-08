/* 
 * @file stdlib.h
 * @author tergeist
 * @date 2014/11/01 17:55:10
 */

#ifndef STDLIB_H
#define STDLIB_H
 
#include <sys/cdefs.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
	__attribute__((__noreturn__))
	void abort(void);
 
#ifdef __cplusplus
}
#endif
 
#endif
