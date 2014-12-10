/*
 * @file isr_test_callback.h
 */

#ifndef ISR_TEST_CALLBACK_H
#define ISR_TEST_CALLBACK_H

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <stdint.h>

//------------------------------------------------------------------------------
// functions
//------------------------------------------------------------------------------
extern "C" void check_isr_validity(int32_t isr_waited, int32_t isr_received);

extern "C" void isr0_test_callback(uint32_t, uint32_t);
extern "C" void isr1_test_callback(uint32_t, uint32_t);
extern "C" void isr2_test_callback(uint32_t, uint32_t);
extern "C" void isr3_test_callback(uint32_t, uint32_t);
extern "C" void isr4_test_callback(uint32_t, uint32_t);
extern "C" void isr5_test_callback(uint32_t, uint32_t);
extern "C" void isr6_test_callback(uint32_t, uint32_t);
extern "C" void isr7_test_callback(uint32_t, uint32_t);
extern "C" void isr9_test_callback(uint32_t, uint32_t);
extern "C" void isr15_test_callback(uint32_t, uint32_t);
extern "C" void isr16_test_callback(uint32_t, uint32_t);
extern "C" void isr17_test_callback(uint32_t, uint32_t);
extern "C" void isr18_test_callback(uint32_t, uint32_t);
extern "C" void isr19_test_callback(uint32_t, uint32_t);

#endif

