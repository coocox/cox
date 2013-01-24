//*****************************************************************************
//
//! @page LCD1602IIC_testcase LCD1602IIC function test
//!
//! File: @ref LCD1602IICTest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the LCD1602IIC sub component.<br><br>
//! - \p Board: STM32F103VET <br><br>
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
//! - \subpage test_LCD1602IIC_Function
//! .
//! \file LCD1602IICTest.c
//! \brief LCD1602IIC test source file
//! \brief LCD1602IIC test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "LCD1602IIC.h"

unsigned long ulSysClk;
//*****************************************************************************
//
//! \brief Get the Test description of LCD1602IIC Function test.
//!
//! \return the description of the LCD1602IIC test.
//
//*****************************************************************************
static char* LCD1602IICGetTest(void)
{

    return "LCD1602IIC Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of LCD1602IIC test.
//!
//! \return None.
//
//*****************************************************************************
static void LCD1602IICSetup(void)
{
    LCD1602Init(100000);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of LCD1602IIC test.
//!
//! \return None.
//
//*****************************************************************************
static void LCD1602IICTearDown(void)
{
}

//*****************************************************************************
//
//! \brief LCD1602IIC test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void LCD1602IICExecute(void)
{
    unsigned char i=0;
    ulSysClk = xSysCtlClockGet();   

    LCD1602PrintString(0,0,"Back Light test!");
    xSysCtlDelay(ulSysClk/4);
    LCD1602BacklightOff();
    xSysCtlDelay(ulSysClk/4);
    LCD1602BacklightOn();
    LCD1602PrintString(1,5,"OK!");
    xSysCtlDelay(ulSysClk/4);
	
    LCD1602Clear();
    LCD1602PrintString(0,0,"IIC LCD1602 display test!");
    xSysCtlDelay(ulSysClk/2);
    LCD1602Clear();
	
    LCD1602PrintString(0,0,"LCD1602 Scroll  test!");
    LCD1602BlinkOn();
    while(i<16)
    {
        if(i<8)
        {
            LCD1602ScrollDisplayRight();
            xSysCtlDelay(ulSysClk/7);
            i++;
        }
        else
        {
            LCD1602ScrollDisplayLeft();
            xSysCtlDelay(ulSysClk/7);
            i++;
        }	
    }
    LCD1602Clear();
    LCD1602PrintString(0,0,"function test!");
    xSysCtlDelay(ulSysClk/4);
    LCD1602PrintString(1,3,"display off!");
    xSysCtlDelay(ulSysClk/4);
    LCD1602BlinkOff();
    LCD1602DisplayOff();
    xSysCtlDelay(ulSysClk/2);
    LCD1602DisplayOn();
    LCD1602CursorOff();
    LCD1602PrintString(1,11,"     ");
    LCD1602PrintString(1,3,"display on!");
    xSysCtlDelay(ulSysClk/4);
    LCD1602Clear();
    LCD1602PrintString(0,2,"Test over!");
}
//
// LCD1602IIC Function test case structure.
//
const tTestCase sTestLCD1602IICFunction = {
    LCD1602IICGetTest,	
    LCD1602IICSetup,
    LCD1602IICTearDown,
    LCD1602IICExecute
};

//
// LCD1602IIC test suits.
//
const tTestCase * const psPatternLCD1602IICTest[] =
{
    &sTestLCD1602IICFunction,
    0
};
