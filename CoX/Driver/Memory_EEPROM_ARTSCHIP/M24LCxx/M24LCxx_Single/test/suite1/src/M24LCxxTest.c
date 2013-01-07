//*****************************************************************************
//
//! @page M24LCxx_testcase M24LCxx function test
//!
//! File: @ref M24LCxxTest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the M24LCxx sub component.<br><br>
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
//! - \subpage test_M24LCxx_Function
//! .
//! \file M24LCxxTest.c
//! \brief M24LCxx test source file
//! \brief M24LCxx test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "M24LCxx.h"

#define Length 32
unsigned char ucWriteData[Length] = "STM32F10x M24LCxx example";;
unsigned char ucReadData[Length];
unsigned short ucWriteAddr = 0x20;
unsigned short ucReadAddr = 0x20;

//*****************************************************************************
//
//! \brief Get the Test description of M24LCxx Function test.
//!
//! \return the desccription of the M24LCxx test.
//
//*****************************************************************************
static char* M24LCxxGetTest(void)
{

    return "M24LCxx Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of M24LCxx test.
//!
//! \return None.
//
//*****************************************************************************
static void M24LCxxSetup(void)
{
  
    M24LCxxInit();
   
}

//*****************************************************************************
//
//! \brief something should do after the test execute of M24LCxx test.
//!
//! \return None.
//
//*****************************************************************************
static void M24LCxxTearDown(void)
{
}

//*****************************************************************************
//
//! \brief M24LCxx test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void M24LCxxExecute(void)
{
    unsigned long i;
    M24LCxxByteWrite(ucWriteData, ucWriteAddr);
    M24LCxxWaitEepromStandbyState();
    M24LCxxBufferRead(ucReadData, ucReadAddr , 1);
    TestAssert((ucWriteData[0] == ucReadData[0]), 
               "M24LCxx API \"M24LCxxByteWrite() and M24LCxxBufferRead()\"error!");
   
    
    M24LCxxBufferWrite(ucWriteData, ucWriteAddr, Length); 
    M24LCxxBufferRead(ucReadData, ucReadAddr, Length);
    for(i = 0; i < Length ; i++)
    {
      TestAssert((ucWriteData[i] == ucReadData[i]), 
                 "M24LCxx API \"M24LCxxBufferWrite() and M24LCxxBufferRead()\"error!");
    }    
}
//
// M24LCxx Function test case struct.
//
const tTestCase sTestM24LCxxFunction = {
    M24LCxxGetTest,	
    M24LCxxSetup,
    M24LCxxTearDown,
    M24LCxxExecute
};

//
// M24LCxx test suits.
//
const tTestCase * const psPatternM24LCxxTest[] =
{
    &sTestM24LCxxFunction,
    0
};
