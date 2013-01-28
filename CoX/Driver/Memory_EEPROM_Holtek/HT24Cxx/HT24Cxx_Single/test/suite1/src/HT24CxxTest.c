//*****************************************************************************
//
//! @page HT24Cxx_testcase HT24Cxx function test
//!
//! File: @ref HT24CxxTest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the HT24Cxx sub component.<br><br>
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
//! - \subpage test_HT24Cxx_Function
//! .
//! \file HT24CxxTest.c
//! \brief HT24Cxx test source file
//! \brief HT24Cxx test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "HT24Cxx.h"

#define Length 32
unsigned char ucWriteData[Length] = "STM32F10x HT24Cxx example";;
unsigned char ucReadData[Length];
unsigned short ucWriteAddr = 0x20;
unsigned short ucReadAddr = 0x20;

//*****************************************************************************
//
//! \brief Get the Test description of HT24Cxx Function test.
//!
//! \return the desccription of the HT24Cxx test.
//
//*****************************************************************************
static char* HT24CxxGetTest(void)
{

    return "HT24Cxx Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of HT24Cxx test.
//!
//! \return None.
//
//*****************************************************************************
static void HT24CxxSetup(void)
{
  
    HT24CxxInit();
   
}

//*****************************************************************************
//
//! \brief something should do after the test execute of HT24Cxx test.
//!
//! \return None.
//
//*****************************************************************************
static void HT24CxxTearDown(void)
{
}

//*****************************************************************************
//
//! \brief HT24Cxx test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void HT24CxxExecute(void)
{
    unsigned long i;
    TestIOPut('0');
    HT24CxxByteWrite(ucWriteData, ucWriteAddr);
    TestIOPut('1');
    HT24CxxWaitEepromStandbyState();
    TestIOPut('2');
    HT24CxxBufferRead(ucReadData, ucReadAddr , 1);
    TestIOPut('3');
    TestAssert((ucWriteData[0] == ucReadData[0]), 
               "HT24Cxx API \"HT24CxxByteWrite() and HT24CxxBufferRead()\"error!");
   
    TestIOPut('4');
    xSysCtlDelay(1000000);
    HT24CxxBufferWrite(ucWriteData, ucWriteAddr, Length);
    TestIOPut('5');
    HT24CxxBufferRead(ucReadData, ucReadAddr, Length);
    TestIOPut('6');
    for(i = 0; i < Length ; i++)
    {
      TestAssert((ucWriteData[i] == ucReadData[i]), 
                 "HT24Cxx API \"HT24CxxBufferWrite() and HT24CxxBufferRead()\"error!");
    }    
}
//
// HT24Cxx Function test case struct.
//
const tTestCase sTestHT24CxxFunction = {
    HT24CxxGetTest,
    HT24CxxSetup,
    HT24CxxTearDown,
    HT24CxxExecute
};

//
// HT24Cxx test suits.
//
const tTestCase * const psPatternHT24CxxTest[] =
{
    &sTestHT24CxxFunction,
    0
};
