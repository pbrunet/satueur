#ifndef AUTOTESTS_HPP
#define AUTOTESTS_HPP

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <descriptors/IDT.hpp>

//------------------------------------------------------------------------------
// class AutoTests
//------------------------------------------------------------------------------
class AutoTests
{
public:
    AutoTests();

    void init_isr_tests();

    void test_divide_by_zero();

private:
    void init_isr_tests_callbacks();
    void init_isr_tests_asm_int();
};

#endif
