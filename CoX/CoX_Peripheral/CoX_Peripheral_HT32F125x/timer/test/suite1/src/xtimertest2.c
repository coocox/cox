//*****************************************************************************
//
//! @page xtimer_testcase xtimer mode test
//!
//! File: @ref xtimertest2.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xtimer sub component.<br><br>
//! - \p Board: HT32F125x Development board <br><br>
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
//! - \subpage test_xtimer_mode
//! .
//! \file xtimertest2.c
//! \brief xtimer test source file
//! \brief xtimer test header file <br>
//
//*****************************************************************************

#include "test.h"

//*****************************************************************************
//
//!\page test_xtimer_register test_xtimer_mode
//!
//!<h2>Description</h2>
//!Test xtimer mode. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
// Define The 2 timer base address array, and Peripheral ID array.
//
//*****************************************************************************

//
// Timer base array
//
static unsigned long ulTimerBase[2] = {TIMER0_BASE, TIMER1_BASE};

//
// Timer ID array
//
static unsigned long ulTimerID[2] = {xSYSCTL_PERIPH_TIMER0,
                                     xSYSCTL_PERIPH_TIMER1};

//
// Timer interrupt ID
//
static unsigned long ulTimerIntID[2] = {xINT_TIMER0, xINT_TIMER1};

//
// Install callback function
//
unsigned long Timer0Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     xIntDisable(ulTimerIntID[0]);
	 xHWREG(TIMER0_BASE + TIMER_ICTR) &= ~TIMER_CHCTR_UEVIE;
     TestEmitToken('b');
     return 0;
}
unsigned long Timer1Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     xIntDisable(ulTimerIntID[1]);
	 xHWREG(TIMER1_BASE + TIMER_ICTR) &= ~TIMER_CHCTR_UEVIE;
     TestEmitToken('b');
     return 0;
}

//
// Callback function
//
xtEventCallback TimerCallbackFunc[2] = {Timer0Callback,
                                        Timer1Callback};

//*****************************************************************************
//
//! \brief Get the Test description of xtimer002 int test.
//!
//! \return the desccription of the xtimer002 test.
//
//*****************************************************************************
static char* xTimer002GetTest(void)
{
    return "xTimer [002]: xtimer counter interrupt test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xTimer002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer002Setup(void)
{
    int i;
    
    //
    //Set the external 8MHZ clock as system clock 
    //
    xSysCtlClockSet(8000000, xSYSCTL_XTAL_8MHZ | xSYSCTL_OSC_MAIN);
    
    //
    // Enable the tiemr0-3 peripheral
    //
    for(i = 0; i < 2; i++)
    {   
        
        xSysCtlPeripheralEnable(ulTimerID[i]);  
       
    }
    
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xtimer002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer002TearDown(void)
{
    int i;
    //
    // Enable the tiemr0-3 peripheral
    //
    for(i = 0; i < 2; i++)
    {
        xSysCtlPeripheralDisable(ulTimerID[i]);  
    }
}

//*****************************************************************************
//
//! \brief xtimer 002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer002Execute(void)
{
    unsigned long ulTemp;
    unsigned long ulBase;
    int i;

    //
    // Periodic mode
    //
    for(i = 0; i < 2; i++)
    {
        ulBase = ulTimerBase[i];
        ulTemp = 0;
        
        //
        // Clear the flag first
        //
        TimerIntClear(ulBase, TIMER_INT_UEV1);
        
        //
        // Config as periodic mode
        //
        xTimerInitConfig(ulBase, xTIMER_CHANNEL0, xTIMER_MODE_PERIODIC | xTIMER_COUNT_UP, 1000); 
		xTimerMatchSet(ulBase, xTIMER_CHANNEL0, 1000);
		xTimerPrescaleSet(ulBase, xTIMER_CHANNEL0, 8);
		   
        xTimerIntCallbackInit(ulBase, TimerCallbackFunc[i]);
        xTimerIntEnable(ulBase, xTIMER_CHANNEL0, xTIMER_INT_MATCH);
        xIntEnable(ulTimerIntID[i]);

        xTimerStart(ulBase, xTIMER_CHANNEL0);
        

        TestAssertQBreak("b","Intterrupt test not happen", 0xfffffffe);
        xTimerStop(ulBase, xTIMER_CHANNEL0);       
    }
    
}

//
// xtimer Int test case struct.
//
const tTestCase sTestxTimer002Int = {
		xTimer002GetTest,
		xTimer002Setup,
		xTimer002TearDown,
		xTimer002Execute
};

//
// xtimer test suits.
//
const tTestCase * const psPatternXtimer002[] =
{
    &sTestxTimer002Int,
    0
};

