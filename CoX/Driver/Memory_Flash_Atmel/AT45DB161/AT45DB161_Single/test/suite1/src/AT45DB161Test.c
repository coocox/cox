//*****************************************************************************
//
//! @page AT45DB161_testcase AT45DB161 function test
//!
//! File: @ref AT45DB161Test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the AT45DB161 sub component.<br><br>
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
//! - \subpage test_AT45DB161_Function
//! .
//! \file AT45DB161Test.c
//! \brief AT45DB161 test source file
//! \brief AT45DB161 test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "AT45DB161.h"

#define Length 4096
unsigned char ucWriteData[Length];
unsigned char ucReadData[Length];

//*****************************************************************************
//
//! \brief Get the Test description of AT45DB161 Function test.
//!
//! \return the desccription of the AT45DB161 test.
//
//*****************************************************************************
static char* AT45DB161GetTest(void)
{
    return "AT45DB161 Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of AT45DB161 test.
//!
//! \return None.
//
//*****************************************************************************
static void AT45DB161Setup(void)
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
    AT45DB161_Init(16000000);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of AT45DB161 test.
//!
//! \return None.
//
//*****************************************************************************
static void AT45DB161TearDown(void)
{
   return;
}

//*****************************************************************************
//
//! \brief AT45DB161 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void AT45DB161Execute(void)
{
    unsigned long i;
    unsigned char ucChipID[4];
    
    AT45DB161_Write(ucWriteData, 0, Length);
    xSysCtlDelay(5000000);
    AT45DB161_Read(ucReadData, 0, Length);

    AT45DB161_GetChipID(ucChipID);
    TestAssert((ucChipID[0] == 0x1F)&&(ucChipID[1] == 0x26),
                "AT45DB161 API \"AT45DB161_GetChipID()\"error!");
    for(i = 0; i < Length; i++)
    {
    	if(ucWriteData[i] != ucReadData[i])break;
        TestAssert((ucWriteData[i] == ucReadData[i]),
              "AT45DB161 API \"AT45DB161_Write() and AT45DB161_Read()\"error!");
    }
    

    AT45DB161_ErasePage(1);
    AT45DB161_Read(ucReadData, 528, 512);
    for(i = 0; i < 512; i++)
    {
        TestAssert((255 == ucReadData[i]), 
                 "AT45DB161 API \"AT45DB161_EraseChip()\"error!");
    }
    AT45DB161_EraseChip();
    AT45DB161_Read(ucReadData, 1000, Length);
    for(i = 0; i < Length; i++)
    {
        TestAssert((255 == ucReadData[i]), 
                 "AT45DB161 API \"AT45DB161_EraseChip()\"error!");
    } 

    AT45DB161_WriteBuffer(1, ucWriteData, 0, 500);
    xSysCtlDelay(50000);
    AT45DB161_ReadBuffer(1, ucReadData, 0, 500);
    for(i = 0; i < 500; i++)
    {
    	if(ucWriteData[i] != ucReadData[i])break;
        TestAssert((ucWriteData[i] == ucReadData[i]),
                 "AT45DB161 API \"AT45DB161_WriteBuffer() and AT45DB161_ReadBuffer()\"error!");
    };
}
//
// AT45DB161 Function test case struct.
//
const tTestCase sTestAT45DB161Function = {
        AT45DB161GetTest,	
        AT45DB161Setup,
        AT45DB161Execute,
        AT45DB161TearDown
};

//
// AT45DB161 test suits.
//
const tTestCase * const psPatternAT45DB161Test[] =
{
    &sTestAT45DB161Function,
    0
};
