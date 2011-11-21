//*****************************************************************************
//
//! @page TC72 test
//!
//! File: @ref tc72test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for TC72 Driver.<br><br>
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
//! - \subpage TC72
//! .
//! \file tc72test.c
//! \brief TC72 test source file
//! \brief TC72 test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "hw_tc72.h"
#include "tc72.h"

//*****************************************************************************
//
//! \brief Prints a decimal unsigned number.
//!
//! \param n is the number to be printed
//!
//! \details Prints a decimal unsigned number.
//!
//! \return None.
//
//*****************************************************************************
static 
void PrintN(unsigned long n)
{
    char buf[16], *p;

    if (n == 0)
    {
        TestIOPut('0');
    }
    else
    {
        p = buf;
        while (n != 0)
        {
            *p++ = (n % 10) + '0';
            n /= 10;
        }

        while (p > buf)
            TestIOPut(*--p);
    }
}


//*****************************************************************************
//
//! \brief Get the Test description of TC72  test.
//!
//! \return the desccription of the TC72 test.
//
//*****************************************************************************
static char* TC72001GetTest(void)
{
    return "TC72, 001, TC72 test";
}


//*****************************************************************************
//
//! \brief something should do before the test execute of TC72 test.
//!
//! \return None.
//
//*****************************************************************************
static void TC72001Setup(void)
{
    TC72Init(2000000);
}


//*****************************************************************************
//
//! \brief something should do after the test execute of TC72 test.
//!
//! \return None.
//
//*****************************************************************************
static void TC72001TearDown(void)
{   
    TC72DeInit();
}


//*****************************************************************************
//
//! \brief TC72 001 test of TC72 TC72_MODE_CONTINUOUS.
//!
//! \return None.
//
//*****************************************************************************
static void TC72ContiousModeTest(void)
{
    unsigned char ucControlRegVal;
    short sTemValue;
    
    TC72Configure(TC72_MODE_CONTINUOUS);
    
    sTemValue = TC72TemperReadDec();
    
    PrintN(sTemValue);
    
    TestIOPut('\n');
    TestIOPut('\r');
    
    ucControlRegVal = TC72ControlRegValGet();
    TestAssert((0x04 == ucControlRegVal), "TC72 API error!");
}


//*****************************************************************************
//
//! \brief TC72 001 test of TC72 read ID.
//!
//! \return None.
//
//*****************************************************************************
static void TC72ReadIDTest(void)
{
    unsigned char ucIDcode;
    
    ucIDcode = TC72IDcodeGet();
    
    TestAssert((0x54 == ucIDcode), "TC72 API error!");
}


//*****************************************************************************
//
//! \brief TC72 001 test of TC72 One-shot mode.
//!
//! \return None.
//
//*****************************************************************************
static void TC72OneShotModeTest(void)
{
    unsigned char ucControlRegVal;
    short sTemValue;
    
    TC72Configure(TC72_MODE_ONESHOT);

    ucControlRegVal = TC72ControlRegValGet();
    TestAssert((0x15 == ucControlRegVal), "TC72 API error!");
    
    sTemValue = TC72TemperRead();
    PrintN(sTemValue);
    TestIOPut('\n');
    TestIOPut('\r');
}


//*****************************************************************************
//
//! \brief TC72 001 test of TC72 ShutDown mode test .
//!
//! \return None.
//
//*****************************************************************************
static void TC72ShutDownModeTest(void)
{
    unsigned char ucControlRegVal;
    
    TC72Configure(TC72_MODE_SHUTDOWN);

    ucControlRegVal = TC72ControlRegValGet();
    TestAssert((0x05 == ucControlRegVal), "TC72 API error!");
}


//*****************************************************************************
//
//! \brief TC72 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void TC72001Execute(void)
{
    TC72ReadIDTest();
    TC72ContiousModeTest();
    TC72ShutDownModeTest();
    TC72OneShotModeTest();
}

//
// TC72 test case struct.
//
const tTestCase sTestTC72 = {
    TC72001GetTest,
    TC72001Setup,
    TC72001TearDown,
    TC72001Execute
};

//
// TC72 test suits.
//
const tTestCase * const psPatternTC72[] =
{
    &sTestTC72,
    0
};
