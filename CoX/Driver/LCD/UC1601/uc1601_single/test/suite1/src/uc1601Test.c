//*****************************************************************************
//
//! @page uc1601_testcase uc1601 function test
//!
//! File: @ref uc1601Test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the uc1601 sub component.<br><br>
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
//! - \subpage test_uc1601_Function
//! .
//! \file uc1601Test.c
//! \brief uc1601 test source file
//! \brief uc1601 test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "uc1601.h"

#define Length 4096

/*  ÐÂÄê¿ìÀÖ(16x16,Z)*/
char HZ[]={
0x20,0x24,0x2C,0x35,0xE6,0x34,0x2C,0x24,0x00,0xFC,0x24,0x24,0xE2,0x22,0x22,0x00,
0x21,0x11,0x4D,0x81,0x7F,0x05,0x59,0x21,0x18,0x07,0x00,0x00,0xFF,0x00,0x00,0x00,
0x40,0x20,0x10,0x0C,0xE3,0x22,0x22,0x22,0xFE,0x22,0x22,0x22,0x22,0x02,0x00,0x00,
0x04,0x04,0x04,0x04,0x07,0x04,0x04,0x04,0xFF,0x04,0x04,0x04,0x04,0x04,0x04,0x00,
0x70,0x00,0xFF,0x08,0xB0,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0xF8,0x80,0x80,0x00,
0x00,0x00,0xFF,0x00,0x80,0x40,0x30,0x0E,0x01,0x06,0x08,0x30,0x60,0xC0,0x40,0x00,
0x00,0x00,0x40,0xFC,0x44,0x44,0x44,0x46,0xFA,0x42,0x43,0x43,0x42,0x40,0x00,0x00,
0x00,0x20,0x18,0x0C,0x07,0x12,0x20,0x40,0x3F,0x00,0x00,0x02,0x0C,0x38,0x10,0x00};


//*****************************************************************************
//
//! \brief Get the Test description of uc1601 Function test.
//!
//! \return the desccription of the uc1601 test.
//
//*****************************************************************************
static char* uc1601GetTest(void)
{

    return "uc1601 Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of uc1601 test.
//!
//! \return None.
//
//*****************************************************************************
static void uc1601Setup(void)
{
    //
    // Set SysClk 50MHz using Extern 12M oscillator
    //

    //xSysCtlClockSet(50000000, xSYSCTL_OSC_MAIN|xSYSCTL_XTAL_12MHZ);

    UC1601Init(1500000);
    UC1601Clear();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of uc1601 test.
//!
//! \return None.
//
//*****************************************************************************
static void uc1601TearDown(void)
{
    UC1601Clear();
    UC1601CENSet(63);
    UC1601DSTSet(0);
    UC1601DENSet(63);
    UC1601ScrollLineSet(0);
    UC1601CharDispaly(0, 0, "Test Complete");
}

//*****************************************************************************
//
//! \brief uc1601 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void uc1601Execute(void)
{
    int i;
    UC1601CharDispaly(0, 0, "I love twd?");
    UC1601CharDispaly(1, 0, "Yes,I love!");
    UC1601ChineseDispaly(3, 0, 4, (char *)&HZ);
    HD44780DisplayN(2,0,5201314);
    xSysCtlDelay(1000000);
    UC1601Clear();
    UC1601CharDispaly(0, 0, "Inverse Dispaly start");
    UC1601InverseEnable();
    xSysCtlDelay(1000000);
    UC1601CharDispaly(0, 0, "Inverse Dispaly stop,then All Pixel On will start");
    UC1601InverseDisable();
    xSysCtlDelay(1000000);
    UC1601AllPixelOnEnable();
    xSysCtlDelay(1000000);
    UC1601Clear();
    UC1601CharDispaly(0, 0, "All Pixel On will stop");
    UC1601AllPixelOnDisable();
    xSysCtlDelay(1000000);
    UC1601Clear();
    UC1601CharDispaly(0, 0, "Display will Off");
    xSysCtlDelay(1000000);
    UC1601DisplayOff();
    xSysCtlDelay(1000000);
    UC1601Clear();
    UC1601CharDispaly(0, 0, "Display On");
    UC1601DisplayOn();
    xSysCtlDelay(1000000);
    UC1601CharDispaly(0, 0, "all display will clear");
    xSysCtlDelay(1000000);
    UC1601Clear();
    UC1601CharDispaly(0, 0, "Blink Display Test");
    for (i=0;i<10;i++)
    {
        UC1601Dispaly(1,3,'0');
        xSysCtlDelay(100000);
        UC1601InverseDispaly(1,3,'0');
        xSysCtlDelay(100000);
    }
    for (i=0;i<63;i=i+1)
    {
        UC1601ScrollLineSet(i);
        //xSysCtlDelay(1000000);
    }
    
    
}
//
// uc1601 Function test case struct.
//
const tTestCase sTestuc1601Function = {
        uc1601GetTest,	
        uc1601Setup,
        uc1601TearDown,
        uc1601Execute
};

//
// uc1601 test suits.
//
const tTestCase * const psPatternuc1601Test[] =
{
    &sTestuc1601Function,
    0
};
