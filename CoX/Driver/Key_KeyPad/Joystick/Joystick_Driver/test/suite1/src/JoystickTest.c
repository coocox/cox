//*****************************************************************************
//
//! @page Joystick_testcase Joystick function test
//!
//! File: @ref JoystickTest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the Joystick sub component.<br><br>
//! - \p Board: STM32 board <br><br>
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
//! - \subpage test_Joystick_Function
//! .
//! \file JoystickTest.c
//! \brief Joystick test source file
//! \brief Joystick test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "Joystick.h"

//*****************************************************************************
//
//! \brief Get the Test description of Joystick Function test.
//!
//! \return the desccription of the Joystick test.
//
//*****************************************************************************
static char* JoystickGetTest(void)
{

    return "Joystick Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of Joystick test.
//!
//! \return None.
//
//*****************************************************************************
static void JoystickSetup(void)
{
    JoystickInit();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of Joystick test.
//!
//! \return None.
//
//*****************************************************************************
static void JoystickTearDown(void)
{
     return;
}

//*****************************************************************************
//
//! \brief Joystick test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void JoystickExecute(void)
{
    unsigned char i = 0, ucKeyVal1 = 0, ucKeyVal2 = 0;
    while(i<5)
    {
    	ucKeyVal1 = JoystickKeyRead();
    	if((ucKeyVal1 != 0)&&(ucKeyVal1 != ucKeyVal2))
    	{
    		i++;
    		ucKeyVal2 = ucKeyVal1;
    	}
    }
}
//
// Joystick Function test case struct.
//
const tTestCase sTestJoystickFunction = {
        JoystickGetTest,	
        JoystickSetup,
        JoystickTearDown,
        JoystickExecute
};

//
// Joystick test suits.
//
const tTestCase * const psPatternJoystickTest[] =
{
    &sTestJoystickFunction,
    0
};
