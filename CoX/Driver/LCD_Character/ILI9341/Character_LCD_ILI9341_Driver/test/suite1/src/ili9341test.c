//*****************************************************************************
//
//! @page ili9341_testcase ili9341 driver test
//!
//! File: @ref ili9341test.c
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
#include "hw_ili9341.h"
#include "ili9341.h"

//*****************************************************************************
//
//!\page Test001 Test001
//!
//!<h2>Description</h2>
//!Test 001. <br>
//!
//
//*****************************************************************************

//
//! Color Definitions
//
#define	BLACK	                  0x0000
#define	BLUE	                  0x001F
#define BLUE2                     0x051F
#define	RED 	                  0xF800
#define	GREEN	                  0x07E0
#define CYAN	                  0x07FF
#define MAGENTA                   0xF81F
#define YELLOW                    0xFFE0
#define WHITE	                  0xFFFF

//*****************************************************************************
//
//! \brief Get the Test description of the test.
//!
//! \return the desccription of the test.
//
//*****************************************************************************
static char* Test001GetTest(void)
{
    return "Test [001]: ILI9341 LCD Driver";
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
    ILI9341Init();
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
    unsigned long ulDat;  
    //
    // Location Set & Display string, number Test
    //
    ILI9341DisplayClear(0x07E0);
    ILI9341DisplayString(15, 15, "Hello ILI9341!", MAGENTA, GREEN);
    ILI9341DisplayString(15, 31, "Number: ", BLUE, WHITE);
    ILI9341DisplayNum(79, 31, 10086, BLUE, WHITE);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    
    ILI9341DisplayString(7, 47, "BL Leds off/on", BLUE, WHITE);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    ILI9341BackLightOff();   
    xSysCtlDelay(xSysCtlClockGet() / 4 );
    ILI9341BackLightOn();
    xSysCtlDelay(xSysCtlClockGet() / 4);
	   
    ILI9341DisplayString(0, 63, "Display sleep off/on", BLUE, WHITE);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    ILI9341EnterSleepMode();    
    xSysCtlDelay(xSysCtlClockGet() / 4 );
    ILI9341ExitSleepMode();
    xSysCtlDelay(xSysCtlClockGet() / 4);
		
    ILI9341DisplayString(7, 79, "Display off/on", BLUE, WHITE);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    ILI9341DisplayOff();    
    xSysCtlDelay(xSysCtlClockGet() / 4 );
    ILI9341DisplayOn();
    xSysCtlDelay(xSysCtlClockGet() / 4);
		
    ILI9341DisplayString(7, 95, "Display Inversion", BLUE, WHITE);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    ILI9341DisplayInversionOn();    
    xSysCtlDelay(xSysCtlClockGet() / 4 );
    ILI9341DisplayInversionOff();
    xSysCtlDelay(xSysCtlClockGet() / 4);
		
    ILI9341DisplayString(7, 111, "Read test", BLUE, WHITE);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    ILI9341SetCurPos(1, 1, 158,158);
    ILI9341WriteData(BLUE);    
    xSysCtlDelay(xSysCtlClockGet() / 4 );
    ulDat = ILI9341Read(ILI9341_RS_DATA);
    if(ulDat == BLUE)
    {
        ILI9341DisplayString(95, 111, "OK!", BLUE, WHITE);
    }
    else
    {
        ILI9341DisplayString(95, 111, "NO!", BLUE, WHITE);
    }
    xSysCtlDelay(xSysCtlClockGet() / 4);
  
    ILI9341DisplayString(31, 127, "Complete", BLUE, WHITE);
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

