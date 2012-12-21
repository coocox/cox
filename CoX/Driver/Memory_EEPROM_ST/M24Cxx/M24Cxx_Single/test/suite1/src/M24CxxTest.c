//*****************************************************************************
//
//! @page M24Cxx_testcase M24Cxx function test
//!
//! File: @ref M24CxxTest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the M24Cxx sub component.<br><br>
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
//! - \subpage test_M24Cxx_Function
//! .
//! \file M24CxxTest.c
//! \brief M24Cxx test source file
//! \brief M24Cxx test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "M24Cxx.h"

#define Length 32
unsigned char ucWriteData[Length] = "STM32F10x M24Cxx example";;
unsigned char ucReadData[Length];
unsigned short ucWriteAddr = 0x20;
unsigned short ucReadAddr = 0x20;

//*****************************************************************************
//
//! \brief Get the Test description of M24Cxx Function test.
//!
//! \return the desccription of the M24Cxx test.
//
//*****************************************************************************
static char* M24CxxGetTest(void)
{

    return "M24Cxx Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of M24Cxx test.
//!
//! \return None.
//
//*****************************************************************************
static void M24CxxSetup(void)
{
  
    M24CxxInit();
   
}

//*****************************************************************************
//
//! \brief something should do after the test execute of M24Cxx test.
//!
//! \return None.
//
//*****************************************************************************
static void M24CxxTearDown(void)
{
}

//*****************************************************************************
//
//! \brief M24Cxx test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void M24CxxExecute(void)
{
    unsigned long i;
    M24CxxByteWrite(ucWriteData, ucWriteAddr);
    M24CxxWaitEepromStandbyState();
    M24CxxBufferRead(ucReadData, ucReadAddr , 1);
    TestAssert((ucWriteData[0] == ucReadData[0]), 
               "M24Cxx API \"M24CxxByteWrite() and M24CxxBufferRead()\"error!");
   
    
    M24CxxBufferWrite(ucWriteData, ucWriteAddr, Length); 
    M24CxxBufferRead(ucReadData, ucReadAddr, Length);
    for(i = 0; i < Length ; i++)
    {
      TestAssert((ucWriteData[i] == ucReadData[i]), 
                 "M24Cxx API \"M24CxxBufferWrite() and M24CxxBufferRead()\"error!");
    }    
}
//
// M24Cxx Function test case struct.
//
const tTestCase sTestM24CxxFunction = {
    M24CxxGetTest,	
    M24CxxSetup,
    M24CxxTearDown,
    M24CxxExecute
};

//
// M24Cxx test suits.
//
const tTestCase * const psPatternM24CxxTest[] =
{
    &sTestM24CxxFunction,
    0
};
