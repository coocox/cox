//*****************************************************************************
//
//! @page VS1838B_testcase VS1838B function test
//!
//! File: @ref VS1838BTest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the VS1838B sub component.<br><br>
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
//! - \subpage test_VS1838B_Function
//! .
//! \file VS1838BTest.c
//! \brief VS1838B test source file
//! \brief VS1838B test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "infrared.h"
#include "xuart.h"

#define MAXCOUNT    10000000

//*****************************************************************************
//
//! \brief Print a string through UART.
//
//*****************************************************************************
static void xUARTPutString(char *str)
{
    char *s = str;
    while(*s != 0)
    {
        xUARTCharPut(xUART1_BASE, *s++);
    }
}

//*****************************************************************************
//
//! \brief Get the Test description of VS1838B Function test.
//!
//! \return the desccription of the VS1838B test.
//
//*****************************************************************************
static char* VS1838BGetTest(void)
{
    return "VS1838B Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of VS1838B test.
//!
//! \return None.
//
//*****************************************************************************
static void VS1838BSetup(void)
{
    //
    // Set SysClk 72MHz using Extern 8M oscillator
    //
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN|xSYSCTL_XTAL_8MHZ);
    IRInit();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of VS1838B test.
//!
//! \return None.
//
//*****************************************************************************
static void VS1838BTearDown(void)
{

}

//*****************************************************************************
//
//! \brief VS1838B test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void VS1838BExecute(void)
{
    unsigned long i = 0;
	unsigned char ucCode[2]={0};
    
    xUARTPutString("\n\n\rPlease press a button of the remote-control....\n\n\r");
	while(ucCode[0]==0)
	{
	    *(unsigned short *)ucCode = IRKeyValueGet();
        if(++i > MAXCOUNT) break;
    };
    
	if(i > MAXCOUNT) xUARTPutString("\n\rNo key pressed or API error!\n\r");
    TestAssert((ucCode[0] != 0),
                 "VS1838B API \"IRKeyValueGet()\"error!");
}
//
// VS1838B Function test case struct.
//
const tTestCase sTestVS1838BFunction = {
        VS1838BGetTest,	
        VS1838BSetup,
        VS1838BTearDown,
        VS1838BExecute
};

//
// VS1838B test suits.
//
const tTestCase * const psPatternVS1838BTest[] =
{
    &sTestVS1838BFunction,
    0
};
