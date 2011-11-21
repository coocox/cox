//*****************************************************************************
//
//! @page M25Pxx_testcase M25Pxx function test
//!
//! File: @ref M25PxxTest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the M25Pxx sub component.<br><br>
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
//! - \subpage test_M25Pxx_Function
//! .
//! \file M25PxxTest.c
//! \brief M25Pxx test source file
//! \brief M25Pxx test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "M25Pxx.h"

#define Length 4096
unsigned char ucWriteData[Length];
unsigned char ucReadData[Length];

//*****************************************************************************
//
//! \brief Get the Test description of M25Pxx Function test.
//!
//! \return the desccription of the M25Pxx test.
//
//*****************************************************************************
static char* M25PxxGetTest(void)
{

    return "M25Pxx Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of M25Pxx test.
//!
//! \return None.
//
//*****************************************************************************
static void M25PxxSetup(void)
{
    unsigned long i;
    //
    // Set SysClk 50MHz using Extern 12M oscillator
    //

    //xSysCtlClockSet(50000000, xSYSCTL_OSC_MAIN|xSYSCTL_XTAL_12MHZ);

    M25PxxInit(2000000);
    for(i=0;i<Length;i++)
    {
        ucWriteData[i] = (unsigned char)(i+3); 
    }
}

//*****************************************************************************
//
//! \brief something should do after the test execute of M25Pxx test.
//!
//! \return None.
//
//*****************************************************************************
static void M25PxxTearDown(void)
{
     M25PxxDisable();
}

//*****************************************************************************
//
//! \brief M25Pxx test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void M25PxxExecute(void)
{
    unsigned long i;
    unsigned long ulID;
    unsigned char ulStatusVal;
       
    ulID = M25PxxIDcodeGet();
    TestAssert((ulID == 0x3fffff), 
                 "M25Pxx API \"W25XxxReadIDTest()\"error!");
    M25PxxChipErase();
    M25PxxDataRead(ucReadData, 0, Length);
    for(i = 0; i < Length; i++)
    {
        TestAssert((255 == (unsigned long)ucReadData[i]), 
                 "M25Pxx API \"EraseChipTest()\"error!");
    } 
    for(i = 0; i < Length; i++)
    {    
        M25PxxPageWrite(&ucWriteData[i], i, 1);
        M25PxxDataRead(&ucReadData[i], i, 1);
    }
    
    for(i = 0; i < Length; i++)
    {
        TestAssert((ucWriteData[i] == ucReadData[i]), 
                 "M25Pxx API \"M25PxxWrite() and M25PxxDataRead()\"error!");
    };
        
    //
    // Test M25Pxx Read and write Status Register
    //
    M25PxxStatusRegWrite(0x1f);
    ulStatusVal = M25PxxStatusRegRead();
    TestAssert((ulStatusVal == 0x1f), 
                 "M25Pxx API \"M25PxxRWSRTest()\"error!");
    
}
//
// M25Pxx Function test case struct.
//
const tTestCase sTestM25PxxFunction = {
        M25PxxGetTest,	
        M25PxxSetup,
        M25PxxTearDown,
        M25PxxExecute
};

//
// M25Pxx test suits.
//
const tTestCase * const psPatternM25PxxTest[] =
{
    &sTestM25PxxFunction,
    0
};
