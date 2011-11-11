//*****************************************************************************
//
//! @page xtimer_testcase xtimer mode test
//!
//! File: @ref xtimertest2.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xtimer sub component.<br><br>
//! - \p Board: NUC140VE3CN board <br><br>
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
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_timer.h"
#include "xtimer.h"

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
// Define The 4 timer base address array, and Peripheral ID array.
//
//*****************************************************************************

//
// Timer base array
//
static unsigned long ulTimerBase[4] = {TIMER0_BASE, TIMER1_BASE,
                                       TIMER2_BASE, TIMER3_BASE};

//
// Timer ID array
//
static unsigned long ulTimerID[4] = {xSYSCTL_PERIPH_TIMER0,
                                     xSYSCTL_PERIPH_TIMER1,
                                     xSYSCTL_PERIPH_TIMER2,
                                     xSYSCTL_PERIPH_TIMER3};

//
// Timer interrupt ID
//
static unsigned long ulTimerIntID[4] = {xINT_TIMER0, xINT_TIMER1,
                                        xINT_TIMER2, xINT_TIMER3};
//
// Global variable
//
static unsigned long ulTimerIntFlag[4] = {0, 0, 0, 0};

//
// Install callback function
//
unsigned long Timer0Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('a');
     return 0;
}
unsigned long Timer1Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('a');
     return 0;
}
unsigned long Timer2Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('a');
     return 0;
}
unsigned long Timer3Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('a');
     return 0;
}

//
// Callback function
//
xtEventCallback TimerCallbackFunc[4] = {Timer0Callback,
                                        Timer1Callback,
                                        Timer2Callback,
                                        Timer3Callback};

//*****************************************************************************
//
//! \brief Get the Test description of xtimer001 register test.
//!
//! \return the desccription of the xtimer001 test.
//
//*****************************************************************************
static char* xTimer001GetTest(void)
{
    return "xTimer [001]: xtimer mode test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xtimer001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer001Setup(void)
{
    int i;
    //
    //Set the external 12MHZ clock as system clock 
    //
    SysCtlKeyAddrUnlock();
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_6MHZ | xSYSCTL_OSC_MAIN);
    
    //
    // Set the timer clock
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR0_S_EXT12M);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR1_S_EXT12M);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR2_S_EXT12M);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR3_S_EXT12M);
    
    //
    // Enable the tiemr0-3 peripheral
    //
    for(i = 0; i < 4; i++)
    {   
        
        xSysCtlPeripheralEnable(ulTimerID[i]);  
       
    }
    
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xtimer001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer001TearDown(void)
{
    int i;
    //
    // Enable the tiemr0-3 peripheral
    //
    for(i = 0; i < 4; i++)
    {
        xSysCtlPeripheralDisable(ulTimerID[i]);  
    }
}

//*****************************************************************************
//
//! \brief xtimer 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer001Execute(void)
{
    unsigned long ulTemp;
    unsigned long ulBase;
    int i, j ;
    
    //
    // One shot mode test.
    //
    for(i = 0; i < 4; i++)
    {
        ulBase = ulTimerBase[i];
        
        //
        // Clear the flag first
        //
        TimerIntClear(ulBase, TIMER_INT_MATCH);
        while(TimerIntStatus(ulBase, TIMER_INT_MATCH));  
        
        // 
        // Config as One shot mode
        //        
        TimerInitConfig(ulBase, TIMER_MODE_ONESHOT, 1000);
        
        TimerIntEnable(ulBase, TIMER_INT_MATCH);
        xIntEnable(ulTimerIntID[i]);
        xTimerIntCallbackInit(ulBase, TimerCallbackFunc[i]); 
        TimerStart(ulBase);
        
        //
        // wait until the timer data register reach equel to compare register
        //
        TestAssertQBreak("a","One shot mode Intterrupt test fail", 0);
        xIntDisable(ulTimerIntID[i]);
    }  
    
    //
    // Periodic mode
    //
    for(i = 0; i < 4; i++)
    {
        ulBase = ulTimerBase[i];
        ulTemp = 0;
        
        //
        // Clear the flag first
        //
        TimerIntClear(ulBase, TIMER_INT_MATCH);
        
        //
        // Config as periodic mode
        //
        TimerInitConfig(ulBase, TIMER_MODE_PERIODIC, 1000);    
        TimerIntEnable(ulBase, TIMER_INT_MATCH);
        TimerStart(ulBase);
        
        // 
        // wait the periodic repeat 5 times 
        //
        for (j = 0; j < 5; j++)
        {
            while(!TimerIntStatus(ulBase, TIMER_INT_MATCH));      
            ulTemp++;
            if(ulTemp == 5)
            {
                break;
            }
            TimerIntClear(ulBase, TIMER_INT_MATCH);
        }
        TestAssert(ulTemp == 5,
                   "xtimer mode \" periodic test\" error!");
        TimerStop(ulBase);       
    }
    
    //
    // Toggle mode test
    //
    for(i = 0; i < 4; i++)
    {
        ulBase = ulTimerBase[i];
        ulTemp = 0;
        
        //
        // Clear the Int flag first
        //
        TimerIntClear(ulBase, TIMER_INT_MATCH);
        
        //
        // Config as toggle mode
        //
        TimerInitConfig(ulBase, TIMER_MODE_PERIODIC, 1000);    
        TimerIntEnable(ulBase, TIMER_INT_MATCH);
        TimerStart(ulBase);
        
        // 
        // wait the toggle repeat 5 times 
        //
        for (j = 0; j < 5; j++)
        {
            while(!TimerIntStatus(ulBase, TIMER_INT_MATCH));      
            ulTemp++;
            if(ulTemp == 5)
            {
                break;
            }
            TimerIntClear(ulBase, TIMER_INT_MATCH);
        }
        TestAssert(ulTemp == 5,
                   "xtimer mode \" Toggle mode test\" error!");
        TimerStop(ulBase);       
    }
    
    //
    // Continuous mode test.
    //
    for(i = 0; i < 4; i++)
    {
        ulBase = ulTimerBase[i];
        ulTemp = 0;
        
        //
        // Clear the flag first
        //
        TimerIntClear(ulBase, TIMER_INT_MATCH);
        while(TimerIntStatus(ulBase, TIMER_INT_MATCH));  
        
        // 
        // Config as One shot mode
        //        
        TimerInitConfig(ulBase, TIMER_MODE_CONTINUOUS, 10000);
        TimerMatchSet(ulBase, 10);
        TimerIntEnable(ulBase, TIMER_INT_MATCH);
        TimerStart(ulBase);
        
        //
        // Delay some time to wait the count register reach to 200.
        //
        xSysCtlDelay(100);
        if(TimerIntStatus(ulBase, TIMER_INT_MATCH) == xtrue)
        {
            ulTemp++;
        }
        TimerIntClear(ulBase, TIMER_INT_MATCH);
        TimerMatchSet(ulBase, 2000);
        
        //
        // Wait until reach the 1000
        //
        //while(!TimerIntStatus(ulBase, TIMER_INT_MATCH));       
        xSysCtlDelay(100000);
        if(TimerIntStatus(ulBase, TIMER_INT_MATCH) == xtrue)
        {
            ulTemp++;
        }
        TimerIntClear(ulBase, TIMER_INT_MATCH);
        
        TestAssert(ulTemp == 2,
           "xtimer mode \" Continuous mode test\" error!");
        TimerStop(ulBase);     
        xIntDisable(ulTimerIntID[i]);
   
    }  
    
}

//
// xtimer register test case struct.
//
const tTestCase sTestxTimer001Mode = {
		xTimer001GetTest,
		xTimer001Setup,
		xTimer001TearDown,
		xTimer001Execute
};

//
// xtimer test suits.
//
const tTestCase * const psPatternXtimer002[] =
{
    &sTestxTimer001Mode,
    0
};

