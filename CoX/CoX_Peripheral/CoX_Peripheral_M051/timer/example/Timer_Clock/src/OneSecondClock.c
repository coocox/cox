//*****************************************************************************
//
//! \file OneSecondClock.c
//! \brief Use the timer to make a one second clock.
//! \date 1/11/2012
//! \author CooCox
//! 
//! The timer source select external 12M hz crystal oscillator, the TCMP register
//! set to oxffff, the prescale register value is 12M/0x1ffff = 92
//! 
//! \copy
//
//*****************************************************************************
#include "xhw_types.h"
#include "xcore.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xgpio.h"
#include "xsysctl.h"
#include "xtimer.h"

//*****************************************************************************
//
//! \biref The main example function
//!
//! \return  none
//
//*****************************************************************************
void OneSecondClock(void)
{    
    //
    // Set System clock
    //
    xSysCtlClockSet(50000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);    
    //
    // Set the timer clock
    //
    xSysCtlPeripheralClockSourceSet(xSYSCTL_TIMER0_MAIN, 1);
    
    // 
    // Enable tiemr0
    // 
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_TIMER0);  
    
    //
    // Clear the flag first
    //
    TimerIntClear(TIMER0_BASE, xTIMER_INT_MATCH);
    while(xTimerStatusGet(TIMER0_BASE, xTIMER_CHANNEL0, xTIMER_INT_MATCH));
    
    // 
    // Config as periodic mode
    //        
    xTimerInitConfig(TIMER0_BASE, xTIMER_CHANNEL0, xTIMER_MODE_PERIODIC, 1000);
    xTimerPrescaleSet(TIMER0_BASE, xTIMER_CHANNEL0, 91);
    xTimerMatchSet(TIMER0_BASE, xTIMER_CHANNEL0, 0x1ffff);
    xTimerIntEnable(TIMER0_BASE, xTIMER_CHANNEL0, xTIMER_INT_MATCH);
    
    //
    // Start the timer
    //
    xTimerStart(TIMER0_BASE, xTIMER_CHANNEL0);
        
    while(1)
    {       
        //
        // wait until the timer data register reach equel to compare register
        //
        while(!xTimerStatusGet(TIMER0_BASE, xTIMER_CHANNEL0, xTIMER_INT_MATCH));
        TimerIntClear(TIMER0_BASE, xTIMER_INT_MATCH);
    }  
}