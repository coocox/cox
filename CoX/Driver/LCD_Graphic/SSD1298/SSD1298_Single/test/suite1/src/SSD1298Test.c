//*****************************************************************************
//
//! @page SSD1298_testcase SSD1298 function test
//!
//! File: @ref SSD1298Test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the SSD1298 sub component.<br><br>
//! - \p Board: STM32 Fire Bull Develop Board <br><br>
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
//! - \subpage test_SSD1298_Function
//! .
//! \file SSD1298Test.c
//! \brief SSD1298 test source file
//! \brief SSD1298 test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "colors.h"
#include "SSD1298.h"


//*****************************************************************************
//
//! \brief Get the Test description of SSD1298 Function test.
//!
//! \return the description of the SSD1298 test.
//
//*****************************************************************************
static char* SSD1298GetTest(void)
{

    return "SSD1298 Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of SSD1298 test.
//!
//! \return None.
//
//*****************************************************************************
static void SSD1298Setup(void)
{
    //
    // Set SysClk 72MHz using External 8M oscillator
    //

    //xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN|xSYSCTL_XTAL_8MHZ);

    LCD_Init();
    LCD_Clear(COLOR_WHITE);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of SSD1298 test.
//!
//! \return None.
//
//*****************************************************************************
static void SSD1298TearDown(void)
{
    LCD_Clear(COLOR_WHITE);
    g_usPointColor = COLOR_RED;
    LCD_ShowString(40, 10, "Test Complete!!", 16);
    xSysCtlDelay(30000000);
}

//*****************************************************************************
//
//! \brief SSD1298 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void SSD1298Execute(void)
{
    g_usPointColor = COLOR_GREEN;
    LCD_Fill(150, 250, 230, 300, COLOR_RED);
    LCD_DrawLine(0, 0, 200, 300);
    LCD_DrawLine(200, 50, 10, 300);
    LCD_DrawCircle(100, 100, 30);
    LCD_DrawCircle(100, 100, 40);
    LCD_DrawCircle(100, 100, 50);
    LCD_DrawCircle(100, 100, 60);
    LCD_DrawCircle(100, 100, 70);
    LCD_ShowString(10, 0, "0xjdsfhuiwefN\n\rIUOHJ@&(*$!$&*2184\n78412454346214", 16);
    xSysCtlDelay(30000000);

    LCD_Clear(COLOR_WHITE);
    g_usPointColor = COLOR_RED;
    LCD_RotateScreen(LCD_ROT_90);
    LCD_Fill(250, 150, 300, 230, COLOR_BLUE);
    LCD_DrawLine(0, 0, 300, 200);
    LCD_DrawLine(200, 50, 10, 200);
    LCD_DrawCircle(100, 100, 30);
    LCD_DrawCircle(100, 100, 40);
    LCD_DrawCircle(100, 100, 50);
    LCD_DrawCircle(100, 100, 60);
    LCD_DrawCircle(100, 100, 70);
    LCD_ShowString(10, 0, "0xjdsfhuiwefNIUOHJ@&(*$!$&*218478412454346214", 16);
    xSysCtlDelay(30000000);

    LCD_Clear(COLOR_WHITE);
    g_usPointColor = COLOR_BLUE;
    LCD_RotateScreen(LCD_ROT_180);
    LCD_Fill(150, 250, 230, 300, COLOR_BLACK);
    LCD_DrawLine(0, 0, 200, 300);
    LCD_DrawLine(200, 50, 10, 300);
    LCD_DrawCircle(100, 100, 30);
    LCD_DrawCircle(100, 100, 40);
    LCD_DrawCircle(100, 100, 50);
    LCD_DrawCircle(100, 100, 60);
    LCD_DrawCircle(100, 100, 70);
    LCD_ShowString(10, 0, "0xjdsfhuiwefNIUOHJ@&(*$!$&*218478412454346214", 16);
    xSysCtlDelay(30000000);

    LCD_Clear(COLOR_WHITE);
    g_usPointColor = COLOR_RED;
    LCD_RotateScreen(LCD_ROT_270);
    LCD_Fill(250, 150, 300, 230, COLOR_BLUE);
    LCD_DrawLine(0, 0, 300, 200);
    LCD_DrawLine(200, 50, 10, 200);
    LCD_DrawCircle(100, 100, 30);
    LCD_DrawCircle(100, 100, 40);
    LCD_DrawCircle(100, 100, 50);
    LCD_DrawCircle(100, 100, 60);
    LCD_DrawCircle(100, 100, 70);
    LCD_ShowString(10, 0, "0xjdsfhuiwefNIUOHJ@&(*$!$&*218478412454346214", 16);
    xSysCtlDelay(30000000);

    LCD_Clear(COLOR_WHITE);
    LCD_RotateScreen(LCD_ROT_0);
    g_usPointColor = COLOR_GREEN;
    LCD_Fill(150, 250, 230, 300, COLOR_RED);
    LCD_DrawLine(0, 0, 200, 300);
    LCD_DrawLine(200, 50, 10, 300);
    LCD_DrawCircle(100, 100, 30);
    LCD_DrawCircle(100, 100, 40);
    LCD_DrawCircle(100, 100, 50);
    LCD_DrawCircle(100, 100, 60);
    LCD_DrawCircle(100, 100, 70);
    LCD_ShowString(10, 0, "0xjdsfhuiwefN\n\rIUOHJ@&(*$!$&*2184\n78412454346214", 16);
    g_usPointColor = COLOR_RED;
    LCD_ShowNumber(20, 200, -1234562, 16, 16);
    xSysCtlDelay(30000000);
    LCD_DisplayOff();
    xSysCtlDelay(30000000);
    LCD_DisplayOn();
    xSysCtlDelay(30000000);
    g_usPointColor = LCD_ReadPiont(0,0);
    LCD_Clear(g_usPointColor); 
    xSysCtlDelay(30000000);  
}
//
// SSD1298 Function test case structure.
//
const tTestCase sTestSSD1298Function = {
        SSD1298GetTest,	
        SSD1298Setup,
        SSD1298TearDown,
        SSD1298Execute
};

//
// SSD1298 test suits.
//
const tTestCase * const psPatternSSD1298Test[] =
{
    &sTestSSD1298Function,
    0
};
