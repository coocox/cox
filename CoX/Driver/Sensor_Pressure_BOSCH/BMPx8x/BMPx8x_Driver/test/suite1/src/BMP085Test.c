//*****************************************************************************
//
//! @page BMP085_testcase BMP085 function test
//!
//! File: @ref BMP085Test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the BMP085 sub component.<br><br>
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
//! - \subpage test_BMP085_Function
//! .
//! \file BMP085Test.c
//! \brief BMP085 test source file
//! \brief BMP085 test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "BMP085.h"

//*****************************************************************************
//
//! \brief Get the Test description of BMP085 Function test.
//!
//! \return the desccription of the BMP085 test.
//
//*****************************************************************************
static char* BMP085GetTest(void)
{

    return "BMP085 Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of BMP085 test.
//!
//! \return None.
//
//*****************************************************************************
static void BMP085Setup(void)
{
	unsigned long t;

    t = BMP085Init(400000);
    TestAssert((t == 0), "BMP085 API \"BMP085Init()\" Failed!");
}

//*****************************************************************************
//
//! \brief something should do after the test execute of BMP085 test.
//!
//! \return None.
//
//*****************************************************************************
static void BMP085TearDown(void)
{
   return;
}

//*****************************************************************************
//
//! \brief BMP085 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void BMP085Execute(void)
{
    int temperature, pressure, altitude;
    
    //  test condition only consider common situation
    temperature = BMP085GetTemperature();
    TestAssert((temperature > -10)&&(temperature < 50),
    		"BMP085 API \"BMP085GetTemperature()\" Error!");
    
    //  test condition only consider common situation
    pressure = BMP085GetPressure(BMP085_OSS_0);
    TestAssert((pressure > 90000)&&(pressure < 120000), "BMP085 API \"BMP085GetPressure()\" Error!");

    //  test condition only consider common situation
    altitude = BMP085GetAltitude();
    TestAssert((altitude > -100)&&(altitude < 5000), "BMP085 API \"BMP085GetAltitude()\" Error!");
}

//
// BMP085 Function test case struct.
//
const tTestCase sTestBMP085Function = {
    BMP085GetTest,
    BMP085Setup,
    BMP085TearDown,
    BMP085Execute
};

//
// BMP085 test suits.
//
const tTestCase * const psPatternBMP085Test[] =
{
    &sTestBMP085Function,
    0
};

