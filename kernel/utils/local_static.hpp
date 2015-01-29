#ifndef KERNEL_UTILS_LOCAL_STATIC_HPP
#define KERNEL_UTILS_LOCAL_STATIC_HPP

/* This is a GCC hook to support local static variables.  */

void *__dso_handle;
 
// Function call at the end of the program to call destructor on local static
// variables. It may do nothing as a kernel never return.
extern "C"
int __cxa_atexit(void (*/*destructor*/) (void *), void */*arg*/, void */*dso*/)
{
    return 0;
}

namespace __cxxabiv1 
{
    /* guard variables */
    // FIXME It should use mutex but they are not available yet.

    __extension__ typedef int __guard __attribute__((mode(__DI__)));

    extern "C" int __cxa_guard_acquire (__guard *);
    extern "C" void __cxa_guard_release (__guard *);
    extern "C" void __cxa_guard_abort (__guard *);

    extern "C" int __cxa_guard_acquire (__guard *g) 
    {
        return !*(char *)(g);
    }

    extern "C" void __cxa_guard_release (__guard *g)
    {
        *(char *)g = 1;
    }

    extern "C" void __cxa_guard_abort (__guard *)
    {

    }
}

#endif
