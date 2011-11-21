//*****************************************************************************
//
//! @page TC77 test
//!
//! File: @ref tc77test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for Tc77 Driver.<br><br>
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
//! - \subpage Tc77
//! .
//! \file tc77test.c
//! \brief tc77 test source file
//! \brief tc77 test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "tc77.h"

//*****************************************************************************
//
//! \brief Get the Test description of TC77  test.
//!
//! \return the desccription of the TC77 test.
//
//*****************************************************************************
static char* TC77001GetTest(void)
{
    return "Tc77, 001, Tc77 test";
}


//*****************************************************************************
//
//! \brief something should do before the test execute of TC77 test.
//!
//! \return None.
//
//*****************************************************************************
static void TC77001Setup(void)
{
    TC77Init(100000);
}

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
//! \brief something should do after the test execute of TC77 test.
//!
//! \return None.
//
//*****************************************************************************
static void TC77001TearDown(void)
{   
	SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
    
    //
    // Disable SPI
    //    
    TC77DeInit();
}


//*****************************************************************************
//
//! \brief Tc77 001 test of TC77 OverFlow test .
//!
//! \return None.
//
//*****************************************************************************
static void TC77OverFlowTest(void)
{
    xtBoolean xtTempOk;
    short sTemperValue;
    
    TC77Configure(TC77_MODE_CONTINUOUS);
    
    sTemperValue = TC77TemperRead();
    
    xtTempOk = TC77Overflow();
    
    TestAssert((xtTempOk == xfalse), "TC77 API error!");

}


//*****************************************************************************
//
//! \brief Tc77 001 test of TC77 read ID test .
//!
//! \return None.
//
//*****************************************************************************
static void TC77ReadIDTest(void)
{
    xtBoolean xtIDOk;
    
    xtIDOk = TC77IDCheck();
    
    TestAssert((xtrue == xtIDOk), "TC77 API error!");
}

//*****************************************************************************
//
//! \brief Tc77 001 test of TC77 read temperature value test .
//!
//! \return None.
//
//*****************************************************************************
static void TC77ReadTemperValueTest(void)
{
    short sTempInDec,i; 
    
    TC77Configure(TC77_MODE_CONTINUOUS);

//
// Continuous mode read
//  
    for(i=0; i<16; i++)
    {
        sTempInDec = TC77TemperReadDec();
        
        PrintN(sTempInDec);
        
        TestIOPut('\r');
        TestIOPut('\n');
    }  
}

//*****************************************************************************
//
//! \brief TC77 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void TC77001Execute(void)
{
    TC77ReadTemperValueTest();
    TC77ReadIDTest();
    TC77OverFlowTest();
}


//
// TC77 test case struct.
//
const tTestCase sTestTC77 = {
    TC77001GetTest,
    TC77001Setup,
    TC77001TearDown,
    TC77001Execute
};

//
// TC77 test suits.
//
const tTestCase * const psPatternTC77[] =
{
    &sTestTC77,
    0
};