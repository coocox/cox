//*****************************************************************************
//
//! @page AT25FS0x_testcase AT25FS0x function test
//!
//! File: @ref AT25FS0xTest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the AT25FS0x sub component.<br><br>
//! - \p Board: NUC140 <br><br>
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
//! - \subpage test_AT25FS0x_Function
//! .
//! \file AT25FS0xTest.c
//! \brief AT25FS0x test source file
//! \brief AT25FS0x test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "AT25FS0x.h"

#define Length 4096
unsigned char ucWriteData[Length];
unsigned char ucReadData[Length];

//*****************************************************************************
//
//! \brief Get the Test description of AT25FS0x Function test.
//!
//! \return the desccription of the AT25FS0x test.
//
//*****************************************************************************
static char* AT25FS0xGetTest(void)
{
    return "AT25FS0x Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of AT25FS0x test.
//!
//! \return None.
//
//*****************************************************************************
static void AT25FS0xSetup(void)
{
    unsigned long i;
    //
    // Set SysClk 50MHz using Extern 12M oscillator
    //
    xSysCtlClockSet(50000000, xSYSCTL_OSC_MAIN|xSYSCTL_XTAL_12MHZ);
    AT25FS0xInit(2000000);
    for(i=0;i<Length;i++)
    {
        ucWriteData[i] = (unsigned char)(i); 
    }
}

//*****************************************************************************
//
//! \brief something should do after the test execute of AT25FS0x test.
//!
//! \return None.
//
//*****************************************************************************
static void AT25FS0xTearDown(void)
{
   AT25FS0xDisable();
}

//*****************************************************************************
//
//! \brief AT25FS0x test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void AT25FS0xExecute(void)
{
    unsigned long i;
    unsigned long ulID;
    unsigned char ulStatusVal;
    
    AT25FS0xPageWrite(ucWriteData,138,Length);
    xSysCtlDelay(50000000);
    AT25FS0xDataRead(ucReadData, 138, Length);
    for(i = 0; i < Length; i++)
    {
        TestAssert((ucWriteData[i] == ucReadData[i]), 
                 "w25xxx API \"AT25FS0xWrite() and AT25FS0xDataRead()\"error!");
    };
    
    ulID = AT25FS0xIDcodeGet();
    TestAssert((ulID == 0x202017), 
                 "w25xxx API \"W25XxxReadIDTest()\"error!");
    AT25FS0xChipErase();
    AT25FS0xDataRead(ucReadData, 0, Length);
    for(i = 0; i < Length; i++)
    {
        TestAssert((255 == (unsigned long)ucReadData[i]), 
                 "AT25FS0x API \"EraseChipTest()\"error!");
    } 
    
    //
    // Test AT25FS0x Read and write Status Register
    //
    AT25FS0xStatusRegWrite(0x1f);
    ulStatusVal = AT25FS0xStatusRegRead();
    TestAssert((ulStatusVal == 0x1f), 
                 "AT25FS0x API \"AT25FS0xRWSRTest()\"error!");
    

    
}
//
// AT25FS0x Function test case struct.
//
const tTestCase sTestAT25FS0xFunction = {
        AT25FS0xGetTest,	
        AT25FS0xSetup,
        AT25FS0xTearDown,
        AT25FS0xExecute
};

//
// AT25FS0x test suits.
//
const tTestCase * const psPatternAT25FS0xTest[] =
{
    &sTestAT25FS0xFunction,
    0
};
