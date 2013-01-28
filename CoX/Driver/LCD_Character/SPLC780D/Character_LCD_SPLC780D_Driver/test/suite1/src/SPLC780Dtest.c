//*****************************************************************************
//
//! @page splc780d_testcase splc780d test
//!
//! File: @ref splc780dtest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the lcd sub component.<br><br>
//! - xx
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
//! - \subpage Test001
//! .
//
//*****************************************************************************

#include "test.h"
#include "hw_splc780d.h"
#include "splc780d.h"

//*****************************************************************************
//
//!\page Test001 Test001
//!
//!<h2>Description</h2>
//!Test 001. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Get the Test description of the test.
//!
//! \return the desccription of the test.
//
//*****************************************************************************
static char* Test001GetTest(void)
{
    return "Test [001]: ";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of the test.
//!
//! \return None.
//
//*****************************************************************************
static void Test001Setup(void)
{
    SPLC780Init();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of the test.
//!
//! \return None.
//
//*****************************************************************************
static void Test001TearDown(void)
{

}

//*****************************************************************************
//
//! \brief 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void Test001Execute(void)
{
    int i , j;
	  
	  SPLC780SetBacklight(SPLC780_BL_CLOSE);
	  SPLC780SetBacklight(SPLC780_BL_OPEN);
	  SPLC780SetBacklight(SPLC780_BL_CLOSE);
	  SPLC780SetBacklight(SPLC780_BL_OPEN);
    
    //
    // Location Set & Display string, number Test
    //
    SPLC780LocationSet(0, 0);
    SPLC780DisplayString("Hello SPLC780!");
    SPLC780LocationSet(0, 1);
    SPLC780DisplayString("Number:");
    SPLC780DisplayN(10086);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    SPLC780LocationSet(0,1);
    SPLC780DisplayString("Display off/on");
    xSysCtlDelay(xSysCtlClockGet() / 4);
    SPLC780DisplayOff();    
    xSysCtlDelay(xSysCtlClockGet() / 4 );
    SPLC780DisplayOn();
    xSysCtlDelay(xSysCtlClockGet() / 4);
    //
    // Cursor style
    //
    SPLC780DisplayClear();
    SPLC780DisplayString("Cursor Test");
    SPLC780CursorOn(xfalse);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    SPLC780CursorOff();
    xSysCtlDelay(xSysCtlClockGet() / 4);
    
    //
    // Cursor will blink at the end of line
    //
    SPLC780CursorOn(xtrue);
    SPLC780CursorRightMove(1);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    SPLC780CursorRightMove(5);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    SPLC780CursorLeftMove(4);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    
    for(i = 0; i < 10; i++)
    {
        SPLC780CursorRightMove(1);
        xSysCtlDelay(xSysCtlClockGet() / 10);     
    }
    
    for(i = 0; i < 10; i++)
    {
        SPLC780CursorLeftMove(1);
        xSysCtlDelay(xSysCtlClockGet() / 10);     
    }    

    SPLC780LocationSet(0, 1);
    SPLC780DisplayString("Cursor Home");
    xSysCtlDelay(xSysCtlClockGet() / 4);
    
    SPLC780Home();
    
    //
    // Display Right shift
    //
    SPLC780DisplayClear();
    SPLC780DisplayString("Right scrolling string");
    SPLC780LocationSet(0, 1);
    SPLC780DisplayString("        Line 2         ");
    for(i = 0; i < 20; i++)
    {
        SPLC780DisplayRightShift(1);
        xSysCtlDelay(xSysCtlClockGet() / 10);
    }
    
    //
    // Display Left shift
    //
    SPLC780DisplayClear();
    SPLC780DisplayString("Left scrolling string");
    SPLC780LocationSet(0, 1);
    SPLC780DisplayString("        Line 2         ");
    for(i = 0; i < 20; i++)
    {
        SPLC780DisplayLeftShift(1);
        xSysCtlDelay(xSysCtlClockGet() / 10);
    }
    
    //
    // Display Right Left shift    
    //
    SPLC780DisplayClear();
    SPLC780DisplayString("Left Right scrolling string");
    SPLC780LocationSet(0, 1);
    SPLC780DisplayString("        Line 2         ");    
    for(j = 0; j < 2; j++)
    {  
        for(i = 0; i < 10; i++)
        {
            SPLC780DisplayRightShift(1);
            xSysCtlDelay(xSysCtlClockGet() / 10);
        }
        for(i = 0; i < 10; i++)
        {
            SPLC780DisplayLeftShift(1);
            xSysCtlDelay(xSysCtlClockGet() / 10);
        } 
    }
    SPLC780Home();
    xSysCtlDelay(xSysCtlClockGet() / 4);
    
    //
    // Cursor Move Direction
    //
    SPLC780DisplayClear();
    SPLC780LocationSet(10, 1);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    SPLC780EntryModeSet(SPLC780_MOVE_DIRECTION_DEC, xfalse);
    SPLC780DisplayString("DEC");
    
    SPLC780LocationSet(10, 2);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    SPLC780EntryModeSet(SPLC780_MOVE_DIRECTION_DEC, xtrue);
    SPLC780DisplayString("DEC shift");
    
    SPLC780DisplayClear();
    SPLC780LocationSet(10, 1);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    SPLC780EntryModeSet(SPLC780_MOVE_DIRECTION_INC, xfalse);
    SPLC780DisplayString("INC");
    
    SPLC780LocationSet(10, 2);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    SPLC780EntryModeSet(SPLC780_MOVE_DIRECTION_INC, xtrue);
    SPLC780DisplayString("INC shift");
    xSysCtlDelay(xSysCtlClockGet() / 4);
    
    SPLC780DisplayClear();
    SPLC780EntryModeSet(SPLC780_MOVE_DIRECTION_INC, xfalse);
    SPLC780DisplayString("Complete");
}

//
// test case 001 struct.
//
const tTestCase sTest001 = {
		Test001GetTest,
		Test001Setup,
		Test001TearDown,
		Test001Execute
};

//
// Xi2c test suits.
//
const tTestCase * const psPattern001[] =
{
    &sTest001,
    0
};

