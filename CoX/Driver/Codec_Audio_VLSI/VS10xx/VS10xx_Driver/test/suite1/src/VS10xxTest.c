//*****************************************************************************
//
//! @page VS10xx_testcase VS10xx function test
//!
//! File: @ref VSxxTest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the VS10xx sub component.<br><br>
//! - \p Board: STM32F103 board <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. <br><br>
//! .
//!
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define:
//! <br>(1)None.<br><br>
//! - \p Option-hardware:
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:
//! <br>Connect an COM cable to the development board.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//!
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_VS10xx_Function
//! .
//! \file VS10xxTest.c
//! \brief VS10xx test source file
//! \brief VS10xx test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "VS10xx.h"

//*****************************************************************************
//
//! \brief Get the Test description of VS10xx Function test.
//!
//! \return the desccription of the VS10xx test.
//
//*****************************************************************************
static char* VS10xxGetTest(void)
{

    return "VS10xx Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of VS10xx test.
//!
//! \return None.
//
//*****************************************************************************
static void VS10xxSetup(void)
{
    VS10xxInit();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of VS10xx test.
//!
//! \return None.
//
//*****************************************************************************
static void VS10xxTearDown(void)
{
    return;
}

//*****************************************************************************
//
//! \brief VS10xx test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void VS10xxExecute(void)
{
    unsigned long i;
    short sBalance;
    
	//
	// Left channel test
	//
	VS10xxSetVolume2(0x41FE);
	VS10xxSineTest(0x79, 10000000);
	//
	// Right channel test
	//
	VS10xxSetVolume2(0xFE41);
    VS10xxSineTest(0x79, 10000000);
	//
	// Volume adjust test
	//
	for(i=100;i<200;i++)
	{
		VS10xxSetVolume(i);
		VS10xxSineTest(0x85, 1000000);
	}
	//
	// Balance adjust test
	//
	for(sBalance=-45;sBalance<45;sBalance++)
	{
		VS10xxSetBalance(sBalance);
		VS10xxSineTest(0x85, 1000000);
	}
}
//
// VS10xx Function test case structure.
//
const tTestCase sTestVS10xxFunction = {
        VS10xxGetTest,  
        VS10xxSetup,
        VS10xxTearDown,
        VS10xxExecute
};

//
// VS10xx test suits.
//
const tTestCase * const psPatternVS10xxTest[] =
{
    &sTestVS10xxFunction,
    0
};
