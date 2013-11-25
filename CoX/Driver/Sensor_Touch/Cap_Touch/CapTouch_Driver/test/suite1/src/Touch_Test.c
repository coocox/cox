//*****************************************************************************
//
//! @page Touch_testcase Touch function test
//!
//! File: @ref TouchTest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the CapacitiveTouch sub component.<br><br>
//! - \p Board: STM32F103 <br><br>
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
//! - \subpage test_CapTouch_Function
//! .
//! \file Touch.c
//! \brief Touch test source file
//! \brief Touch test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "touch.h"

#define LED  PC3 

//*****************************************************************************
//
//! \brief Get the Test description of CapacitiveTouch Function test.
//!
//! \return the description of the capture touch test.
//
//*****************************************************************************
static char* CapacitiveTouchGetTest(void)
{
    return "capacitive touch Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of M24Cxx test.
//!
//! \return None.
//
//*****************************************************************************
static void CapacitiveTouchSetup(void)
{
   xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(LED));
   xGPIOSPinTypeGPIOOutput(LED);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of CapacitiveTouch test.
//!
//! \return None.
//
//*****************************************************************************
static void CapacitiveTouchTearDown(void)
{
  
}

//*****************************************************************************
//
//! \brief CapacitiveTouch test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void CapacitiveTouchExecute(void)
{
    xGPIOSPinWrite(LED, 0);
    xSysCtlDelay(xSysCtlClockGet()/4);
    while(1)
    {
        if(CapTouchRead())
            xGPIOSPinWrite(LED, 0);
        else
            xGPIOSPinWrite(LED, 1);
    }
}

//
// STMPE811 Function test case struct.
//
const tTestCase sTestTouchFunction = {
    CapacitiveTouchGetTest,	
    CapacitiveTouchSetup,
    CapacitiveTouchTearDown,
    CapacitiveTouchExecute
};

//
// STMPE811 test suits.
//
const tTestCase * const psPatternTouchTest[] =
{
    &sTestTouchFunction,
    0
};

