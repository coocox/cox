//*****************************************************************************
//
//! @page xtimer_testcase xtimer event counting and input capture function test
//!
//! File: @ref xtimertest3.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xtimer sub component.<br><br>
//! - \p Board: Mini51 board <br><br>
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
//! - \subpage test_xtimer_EventCount_InputCapture_test
//! .
//! \file xtimertest3.c
//! \brief xtimer test source file
//! \brief xtimer test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_timer.h"
#include "xtimer.h"

//*****************************************************************************
//
//!\page test_xtimer_EventCount_InputCapture_test test_xtimer_EventCount_InputCapture_test
//!
//!<h2>Description</h2>
//!Test xtimer event counting and input capture test. <br>
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
static unsigned long Timer0Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('b'); 
     xIntDisable(xINT_TIMER0);
     return 0;
}
static unsigned long Timer1Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('b'); 
     xIntDisable(xINT_TIMER1);
     return 0;
}

//
// Callback function
//
static xtEventCallback TimerCallbackFunc[2] = {Timer0Callback,
                                               Timer1Callback};


//*****************************************************************************
//
//! \breif This function is used to generate a falling edge, as the of
//! Timer counting source.
//!
//! \return
//
//*****************************************************************************
void EdgeGenerate(void)                                       
{
    int i;
    
    //
    // Set the  pin to high
    //
    xGPIOSPinWrite(PA5, 0);
    
    //
    // Add a small delay
    //
    for(i = 0; i < 5; i++);
    
    //
    // Set the  pin to low
    //
    xGPIOSPinWrite(PA5, 1);
    
    for(i = 0; i < 5; i++);
    
}


//*****************************************************************************
//
//! \brief Get the Test description of xtimer003 event counting and input capture test.
//!
//! \return the desccription of the xtimer003 test.
//
//*****************************************************************************
static char* xTimer003GetTest(void)
{
    return "xTimer [003]: xtimer count and capture mode test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xtimer003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer003Setup(void)
{
    int i;
    
    SysCtlPeripheralReset(SYSCTL_PERIPH_TMR0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_TMR1);

    //
    // Enable the tiemr0-1 peripheral
    //
    for(i = 0; i < 2; i++)
    {   
        xSysCtlPeripheralEnable(ulTimerID[i]);  
    }
    //
    // Set the timer clock, in event counting mode, the timer source clock should
    // be HCLK.
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR0_S_HCLK);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR1_S_HCLK);
    
    //
    // Turn a pin to an GPIO Timer event counting function pin.
    //
    xSPinTypeTimer(TIMCCP0, PD4);
    xSPinTypeTimer(TIMCCP1, PD5);
    
    //
    // PA5 used to output rising edge as the timer count source.
    //
    xGPIODirModeSet(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_DIR_MODE_OUT);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xtimer003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer003TearDown(void)
{
    int i;
    
    //
    // Disable the tiemr0-1 peripheral
    //
    for(i = 0; i < 2; i++)
    {
        xSysCtlPeripheralDisable(ulTimerID[i]);  
    }
}

//*****************************************************************************
//
//! \brief xtimer 003 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer003Execute(void)
{
    unsigned long ulBase;
    int i;
    //
    // Test the event count function test. You should connect the PA5 to the
    // corresponding TM pin as the count source.
    //  

    for(i = 0; i < 2; i++)
    {
        ulBase = ulTimerBase[i];
        
        // 
        // Mode set test
        //
        TimerCounterInitConfig(ulBase, TIMER_MODE_PERIODIC, 10000);
        
        TimerMatchSet(ulBase, 5);
        
        //
        // Set prescale value 0
        //
        TimerPrescaleSet(ulBase, 0);
        
        //
        // Select the falling event count phase
        //
        TimerCounterDetectPhaseSelect(ulBase, TIMER_COUNTER_RISING);
        
        TimerIntEnable(ulBase, TIMER_INT_MATCH);
        
        TimerCounterEnable(ulBase);
        
        //
        // Enable event count mode
        //
        TimerStart(ulBase);
        
        while(!TimerIntStatus(ulBase, TIMER_INT_MATCH))
        {
            EdgeGenerate();
        }
        TimerIntClear(ulBase, TIMER_INT_MATCH);
        
        TimerCounterDisable(ulBase);
    }
      
    xSPinTypeTimer(T0EX, PD2);
    xSPinTypeTimer(T1EX, PD6);
    
    //
    // Input capture function test
    //    
    for (i = 0; i< 2; i++)
    {
        ulBase = ulTimerBase[i];
        //
        // Clear the flag first
        //
        TimerIntClear(ulBase, TIMER_INT_CAP);
        while(TimerIntStatus(ulBase, TIMER_INT_CAP));
        //
        // Timer capture function 
        //
        xTimerCaptureModeSet(ulBase, i, TIMER_CAP_MODE_CAP);
        
        //
        // Capture detect edge set both
        //
        xTimerCaptureEdgeSelect(ulBase, i, TIMER_CAP_BOTH);
        
        //
        // Enable the capture Int
        //
        xTimerIntEnable(ulBase, i, TIMER_INT_CAP);
        xIntEnable(ulTimerIntID[i]);
        xTimerIntCallbackInit(ulBase, TimerCallbackFunc[i]); 
        
        //
        // Enable the capture mode, Start the timer.
        //
        TimerCaptureEnable(ulBase);
        xTimerStart(ulBase, i);
             
        //
        // wait until the timer data register reach equel to compare register
        //
        TestAssertQBreak("b","One shot mode Intterrupt test fail", 0xffffffff);
        
        xtBoolean xbTimerIntStatus = TimerIntStatus(ulBase, TIMER_INT_CAP);
        TimerIntClear(ulBase, TIMER_INT_CAP);
        TimerCaptureDisable(ulBase);
        xIntDisable(ulTimerIntID[i]);
    }
   
}

//
// xtimer register test case struct.
//
const tTestCase sTestxTimer003Function = {
		xTimer003GetTest,
		xTimer003Setup,
		xTimer003TearDown,
		xTimer003Execute
};

//
// xtimer test suits.
//
const tTestCase * const psPatternXtimer003[] =
{
    &sTestxTimer003Function,
    0
};

