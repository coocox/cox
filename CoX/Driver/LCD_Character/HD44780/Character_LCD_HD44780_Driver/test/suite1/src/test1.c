//*****************************************************************************
//
//! @page xi2c_testcase xi2c register test
//!
//! File: @ref xi2ctest.c
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
#include "hd44780.h"

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
    HD44780Init();
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
    
    //
    // Location Set & Display string, number Test
    //
    HD44780LocationSet(0, 0);
    HD44780DisplayString("Hello HD44780!");
    HD44780LocationSet(0, 1);
    HD44780DisplayString("Number:");
    HD44780DisplayN(10086);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    HD44780LocationSet(0,1);
    HD44780DisplayString("Display off/on");
    xSysCtlDelay(xSysCtlClockGet() / 4);
    HD44780DisplayOff();    
    xSysCtlDelay(xSysCtlClockGet() / 4 );
    HD44780DisplayOn();
    xSysCtlDelay(xSysCtlClockGet() / 4);
    //
    // Cursor style
    //
    HD44780DisplayClear();
    HD44780DisplayString("Cursor Test");
    HD44780CursorOn(xfalse);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    HD44780CursorOff();
    xSysCtlDelay(xSysCtlClockGet() / 4);
    
    //
    // Cursor will blink at the end of line
    //
    HD44780CursorOn(xtrue);
    HD44780CursorRightMove(1);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    HD44780CursorRightMove(5);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    HD44780CursorLeftMove(4);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    
    for(i = 0; i < 10; i++)
    {
        HD44780CursorRightMove(1);
        xSysCtlDelay(xSysCtlClockGet() / 10);     
    }
    
    for(i = 0; i < 10; i++)
    {
        HD44780CursorLeftMove(1);
        xSysCtlDelay(xSysCtlClockGet() / 10);     
    }    

    HD44780LocationSet(0, 1);
    HD44780DisplayString("Cursor Home");
    xSysCtlDelay(xSysCtlClockGet() / 4);
    
    HD44780Home();
    
    //
    // Display Right shift
    //
    HD44780DisplayClear();
    HD44780DisplayString("Right scrolling string");
    HD44780LocationSet(0, 1);
    HD44780DisplayString("        Line 2         ");
    for(i = 0; i < 20; i++)
    {
        HD44780DisplayRightShift(1);
        xSysCtlDelay(xSysCtlClockGet() / 10);
    }
    
    //
    // Display Left shift
    //
    HD44780DisplayClear();
    HD44780DisplayString("Left scrolling string");
    HD44780LocationSet(0, 1);
    HD44780DisplayString("        Line 2         ");
    for(i = 0; i < 20; i++)
    {
        HD44780DisplayLeftShift(1);
        xSysCtlDelay(xSysCtlClockGet() / 10);
    }
    
    //
    // Display Right Left shift    
    //
    HD44780DisplayClear();
    HD44780DisplayString("Left Right scrolling string");
    HD44780LocationSet(0, 1);
    HD44780DisplayString("        Line 2         ");    
    for(j = 0; j < 2; j++)
    {  
        for(i = 0; i < 10; i++)
        {
            HD44780DisplayRightShift(1);
            xSysCtlDelay(xSysCtlClockGet() / 10);
        }
        for(i = 0; i < 10; i++)
        {
            HD44780DisplayLeftShift(1);
            xSysCtlDelay(xSysCtlClockGet() / 10);
        } 
    }
    HD44780Home();
    xSysCtlDelay(xSysCtlClockGet() / 4);
    
    //
    // Cursor Move Direction
    //
    HD44780DisplayClear();
    HD44780LocationSet(10, 1);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    HD44780EntryModeSet(HD44780_MOVE_DIRECTION_DEC, xfalse);
    HD44780DisplayString("DEC");
    
    HD44780LocationSet(10, 2);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    HD44780EntryModeSet(HD44780_MOVE_DIRECTION_DEC, xtrue);
    HD44780DisplayString("DEC shift");
    
    HD44780DisplayClear();
    HD44780LocationSet(10, 1);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    HD44780EntryModeSet(HD44780_MOVE_DIRECTION_INC, xfalse);
    HD44780DisplayString("INC");
    
    HD44780LocationSet(10, 2);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    HD44780EntryModeSet(HD44780_MOVE_DIRECTION_INC, xtrue);
    HD44780DisplayString("INC shift");
    xSysCtlDelay(xSysCtlClockGet() / 4);
    
    HD44780DisplayClear();
    HD44780EntryModeSet(HD44780_MOVE_DIRECTION_INC, xfalse);
    HD44780DisplayString("Complete");
     
    
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

