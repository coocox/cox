//*****************************************************************************
//
//! @page HC-SR04 test
//!
//! File: @ref HC_SR04Test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for HC-SR04 Driver.<br><br>
//! - \p Board: STM32 <br><br>
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
//! - \subpage HC-SR04
//! .
//! \file HC_SR04Test.c
//! \brief HC-SR04Test test source file
//! \brief HC-SR04Test test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "HC_SR04.h"

//*****************************************************************************
//
//! \brief Get the Test description of HC-SR04 test.
//!
//! \return the desccription of the HC-SR04 test.
//
//*****************************************************************************
static char* HCSR04GetTest(void)
{
    return "HC-SR04 ultrasonic distance measure module test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of HC-SR04 test.
//!
//! \return None.
//
//*****************************************************************************
static void HCSR04Setup(void)
{

    HCSR04Init();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of HC-SR04 test.
//!
//! \return None.
//
//*****************************************************************************
static void HCSR04TearDown(void)
{   
    return; 
}

//*****************************************************************************
//
//! \brief HC-SR04 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void HCSR04Execute(void)
{
	unsigned short usDistance;
    usDistance = HCSR04GetDistance(UNIT_CM);
	TestAssert((usDistance != 0), "Timer doesn't work or the distance is too far!");
}

//
// HC-SR04 test case struct.
//
const tTestCase sHCSR04Test = {
    HCSR04GetTest,
    HCSR04Setup,
	HCSR04Execute,
    HCSR04TearDown   
};

//
// HC-SR04 test suits.
//
const tTestCase * const psPatternHCSR04Test[] =
{
    &sHCSR04Test,
    0
};
