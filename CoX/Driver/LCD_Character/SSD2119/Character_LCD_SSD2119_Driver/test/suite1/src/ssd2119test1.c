//*****************************************************************************
//
//! @page ssd2119_testcase ssd2119 driver test
//!
//! File: @ref ssd2119test1.c
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
#include "hw_ssd2119.h"
#include "ssd2119.h"

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
#define	BLACK	0x0000
#define	BLUE	0x001F
#define BLUE2   0x051F
#define	RED 	0xF800
#define	GREEN	0x07E0
#define CYAN	0x07FF
#define MAGENTA	0xF81F
#define YELLOW	0xFFE0
#define WHITE	0xFFFF

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
    SSD2119Init();
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
    //
    // Location Set & Display string, number Test
    //
    SSD2119DisplayClear(0x07E0);
    SSD2119DisplayString(60, 20, "Hello SSD2119!", MAGENTA, GREEN);
    SSD2119DisplayString(60, 60, "Number: ", BLUE, WHITE);
    SSD2119DisplayNum(124, 60, 10086, BLUE, WHITE);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    
    SSD2119DisplayString(60, 80, "Backlight Leds off/on", BLUE, WHITE);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    SSD2119EnterSleepMode();    
    xSysCtlDelay(xSysCtlClockGet() / 4 );
    SSD2119ExitSleepMode();
    xSysCtlDelay(xSysCtlClockGet() / 4);
    
    SSD2119DisplayString(60, 120, "Display off/on", BLUE, WHITE);
    xSysCtlDelay(xSysCtlClockGet() / 4);
    SSD2119EnterSleepMode();    
    xSysCtlDelay(xSysCtlClockGet() / 4 );
    SSD2119ExitSleepMode();
    xSysCtlDelay(xSysCtlClockGet() / 4);
    
    SSD2119DisplayString(60, 180, "Complete", BLUE, WHITE);
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

