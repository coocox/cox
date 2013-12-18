//*****************************************************************************
//
//! @page AT45DBxxxD_testcase AT45DBxxxD function test
//!
//! File: @ref AT45DBxxxDTest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the AT45DBxxxD sub component.<br><br>
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
//! - \subpage test_AT45DBxxxD_Function
//! .
//! \file AT45DBxxxDTest.c
//! \brief AT45DBxxxD test source file
//! \brief AT45DBxxxD test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "AT45DBxxxD.h"

#define Length 4096
unsigned char ucWriteData[Length];
unsigned char ucReadData[Length];
extern AT45DBxxxDInfoStruct AT45DBxxxDInfo;
//*****************************************************************************
//
//! \brief Get the Test description of AT45DBxxxD Function test.
//!
//! \return the desccription of the AT45DBxxxD test.
//
//*****************************************************************************
static char* AT45DBxxxDGetTest(void)
{
    return "AT45DBxxxD Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of AT45DBxxxD test.
//!
//! \return None.
//
//*****************************************************************************
static void AT45DBxxxDSetup(void)
{
    unsigned long i;
    //
    // Set SysClk 50MHz using Extern 12M oscillator
    //
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN|xSYSCTL_XTAL_8MHZ);

    for(i=0;i<Length;i++)
    {
        ucWriteData[i] = (unsigned char)(i); 
    }
    AT45DBxxxDInit(1000000);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of AT45DBxxxD test.
//!
//! \return None.
//
//*****************************************************************************
static void AT45DBxxxDTearDown(void)
{
   return;
}

//*****************************************************************************
//
//! \brief AT45DBxxxD test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void AT45DBxxxDExecute(void)
{
    unsigned long i;
    unsigned char ucChipID[2];

    AT45DBxxxDChipIDGet(ucChipID);
    TestAssert(ucChipID[0] == 0x1F,
                "AT45DBxxxD API \"AT45DBxxxD_GetChipID()\"error!");
    
    AT45DBxxxDWrite(ucWriteData, 100, Length);
    xSysCtlDelay(5000000);
    AT45DBxxxDRead(ucReadData, 100, Length);

    for(i = 0; i < Length; i++)
    {
    	if(ucWriteData[i] != ucReadData[i])break;
        TestAssert((ucWriteData[i] == ucReadData[i]),
              "AT45DBxxxD API \"AT45DBxxxD_Write() and AT45DBxxxD_Read()\"error!");
    }
    

    AT45DBxxxDPageErase(1);
    AT45DBxxxDPageRead(1,ucReadData, AT45DBxxxDInfo.usPageSize);
    for(i = 0; i < AT45DBxxxDInfo.usPageSize; i++)
    {
        TestAssert((255 == ucReadData[i]), 
                 "AT45DBxxxD API \"AT45DBxxxD_PageErase()\"error!");
    }

    AT45DBxxxDBufferWrite(AT45DBxxxD_BUF1, ucWriteData, 0, 500);
    xSysCtlDelay(50000);
    AT45DBxxxDBufferRead(AT45DBxxxD_BUF1, ucReadData, 0, 500);
    for(i = 0; i < 500; i++)
    {
    	if(ucWriteData[i] != ucReadData[i])break;
        TestAssert((ucWriteData[i] == ucReadData[i]),
                 "AT45DBxxxD API \"AT45DBxxxD_WriteBuffer() and AT45DBxxxD_ReadBuffer()\"error!");
    };
}
//
// AT45DBxxxD Function test case struct.
//
const tTestCase sTestAT45DBxxxDFunction = {
        AT45DBxxxDGetTest,
        AT45DBxxxDSetup,
        AT45DBxxxDExecute,
        AT45DBxxxDTearDown
};

//
// AT45DBxxxD test suits.
//
const tTestCase * const psPatternAT45DBxxxDTest[] =
{
    &sTestAT45DBxxxDFunction,
    0
};
