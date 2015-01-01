//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
// libc includes
#include <stdlib.h>
#include <string.h>

// kernel includes
#include <logger/Logger.hpp>
#include <autotests/isr_test_callback.hpp>

//------------------------------------------------------------------------------
// check_isr_validity
//------------------------------------------------------------------------------
void check_isr_validity(int32_t isr_waited, int32_t isr_received)
{
    // convert isr number to to char
    char isr_waited_str[3];
    itoa(isr_waited, isr_waited_str, 10);

    char isr_received_str[3];
    itoa(isr_received, isr_received_str, 10);

    // print test result
    char result[30] = "isr ";

    if ( isr_waited == isr_received )
    {
        strcat(result, isr_waited_str);
        Logger::log(result, LOGGER_LOGLEVEL::OK);
    }
    else
    {
        strcat(result, isr_waited_str);
        strcat(result, " (");
        strcat(result, isr_received_str);
        strcat(result, " received)");
        Logger::log(result, LOGGER_LOGLEVEL::FAIL);
    }
}

//------------------------------------------------------------------------------
// isr0_test_callback
//------------------------------------------------------------------------------
void isr0_test_callback(uint32_t isr_number, uint32_t /*errcode*/)
{
    check_isr_validity(0, isr_number);
}

//------------------------------------------------------------------------------
// isr1_test_callback
//------------------------------------------------------------------------------
void isr1_test_callback(uint32_t isr_number, uint32_t /*errcode*/)
{
    check_isr_validity(1, isr_number);
}

//------------------------------------------------------------------------------
// isr2_test_callback
//------------------------------------------------------------------------------
void isr2_test_callback(uint32_t isr_number, uint32_t /*errcode*/)
{
    check_isr_validity(2, isr_number);
}

//------------------------------------------------------------------------------
// isr3_test_callback
//------------------------------------------------------------------------------
void isr3_test_callback(uint32_t isr_number, uint32_t /*errcode*/)
{
    check_isr_validity(3, isr_number);
}

//------------------------------------------------------------------------------
// isr4_test_callback
//------------------------------------------------------------------------------
void isr4_test_callback(uint32_t isr_number, uint32_t /*errcode*/)
{
    check_isr_validity(4, isr_number);
}

//------------------------------------------------------------------------------
// isr5_test_callback
//------------------------------------------------------------------------------
void isr5_test_callback(uint32_t isr_number, uint32_t /*errcode*/)
{
    check_isr_validity(5, isr_number);
}

//------------------------------------------------------------------------------
// isr6_test_callback
//------------------------------------------------------------------------------
void isr6_test_callback(uint32_t isr_number, uint32_t /*errcode*/)
{
    check_isr_validity(6, isr_number);
}

//------------------------------------------------------------------------------
// isr7_test_callback
//------------------------------------------------------------------------------
void isr7_test_callback(uint32_t isr_number, uint32_t /*errcode*/)
{
    check_isr_validity(7, isr_number);
}

//------------------------------------------------------------------------------
// isr9_test_callback
//------------------------------------------------------------------------------
void isr9_test_callback(uint32_t isr_number, uint32_t /*errcode*/)
{
    check_isr_validity(9, isr_number);
}

//------------------------------------------------------------------------------
// isr15_test_callback
//------------------------------------------------------------------------------
void isr15_test_callback(uint32_t isr_number, uint32_t /*errcode*/)
{
    check_isr_validity(15, isr_number);
}

//------------------------------------------------------------------------------
// isr16_test_callback
//------------------------------------------------------------------------------
void isr16_test_callback(uint32_t isr_number, uint32_t /*errcode*/)
{
    check_isr_validity(16, isr_number);
}

//------------------------------------------------------------------------------
// isr17_test_callback
//------------------------------------------------------------------------------
void isr17_test_callback(uint32_t isr_number, uint32_t /*errcode*/)
{
    check_isr_validity(17, isr_number);
}

//------------------------------------------------------------------------------
// isr18_test_callback
//------------------------------------------------------------------------------
void isr18_test_callback(uint32_t isr_number, uint32_t /*errcode*/)
{
    check_isr_validity(18, isr_number);
}

//------------------------------------------------------------------------------
// isr19_test_callback
//------------------------------------------------------------------------------
void isr19_test_callback(uint32_t isr_number, uint32_t /*errcode*/)
{
    check_isr_validity(19, isr_number);
}
