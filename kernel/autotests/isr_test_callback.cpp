/* 
 * @file isr_test_callback.cpp
 * @author tergeist
 * @date 2014/11/01 10:50:26
 */

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <console/Console.hpp>
#include <autotests/isr_test_callback.hpp>

//------------------------------------------------------------------------------
// check_isr_validity
//------------------------------------------------------------------------------
void check_isr_validity(int32_t isr_waited, int32_t isr_received)
{
	if ( isr_waited == isr_received )
	{
		Console::write("[OK] isr ");
		Console::write('0'+isr_waited);
		Console::write("\n");
	}
	else
	{
		Console::write("[FAIL] isr ");
		Console::write('0'+isr_waited);
		Console::write(" (");
		Console::write('0'+isr_received);
		Console::write(" received)");
		Console::write("\n");
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
