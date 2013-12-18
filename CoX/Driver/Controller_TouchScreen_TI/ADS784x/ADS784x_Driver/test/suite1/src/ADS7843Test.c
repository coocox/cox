//*****************************************************************************
//
//! @page ADS7843_testcase ADS7843 function test
//!
//! File: @ref ADS7843Test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the ADS7843 sub component.<br><br>
//! - \p Board: STM32F107 <br><br>
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
//! - \subpage test_ADS7843_Function
//! .
//! \file ADS7843Test.c
//! \brief ADS7843 test source file
//! \brief ADS7843 test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "ADS7843.h"

//*****************************************************************************
//
//! \brief Get the Test description of ADS7843 Function test.
//!
//! \return the desccription of the ADS7843 test.
//
//*****************************************************************************
static char* ADS7843GetTest(void)
{

    return "ADS7843 Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of ADS7843 test.
//!
//! \return None.
//
//*****************************************************************************
static void ADS7843Setup(void)
{
    ADS7843Init();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of ADS7843 test.
//!
//! \return None.
//
//*****************************************************************************
static void ADS7843TearDown(void)
{
   return;
}

//*****************************************************************************
//
//! \brief ADS7843 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void ADS7843Execute(void)
{
	unsigned short adx, ady, posx, posy;
    
	// Wait for touch
	while(ADS7843PenInq())
	{
		ADS7843ReadADXY(&adx, &ady);
		ADS7843ReadPiontXY(&posx, &posy);
	}

	TestAssert((adx > 100)&&(adx < 2000)&&(ady > 100)&&(ady < 2000),
			"BMP085 API \"ADS7843ReadADXY()\" Error!");

	TestAssert((posx < TOUCH_SCREEN_WIDTH)&&(posy < TOUCH_SCREEN_HEIGHT),
			"BMP085 API \"ADS7843ReadPiontXY()\" Error!");
}

//
// ADS7843 Function test case struct.
//
const tTestCase sTestADS7843Function = {
    ADS7843GetTest,
    ADS7843Setup,
    ADS7843TearDown,
    ADS7843Execute
};

//
// ADS7843 test suits.
//
const tTestCase * const psPatternADS7843Test[] =
{
    &sTestADS7843Function,
    0
};

