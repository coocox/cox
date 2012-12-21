//*****************************************************************************
//
//! \file one_second_clock.c
//! \brief Use the timer to make a one second clock.
//! \date 9/20/2011
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
    SysCtlHClockSet(SYSCTL_XTAL_12MHZ | SYSCTL_OSC_MAIN);    
    //
    // Set the timer clock
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR0_S_EXT12M);
    
    // 
    // Enable tiemr0
    // 
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TMR0);  
    
    //
    // Clear the flag first
    //
    TimerIntClear(TIMER0_BASE, TIMER_INT_MATCH);
    while(TimerIntStatus(TIMER0_BASE, TIMER_INT_MATCH));
    
    // 
    // Config as One shot mode
    //        
    TimerInitConfig(TIMER0_BASE, TIMER_MODE_PERIODIC, 1000);
    TimerPrescaleSet(TIMER0_BASE, 91);
    TimerMatchSet(TIMER0_BASE, 0x1ffff);
    TimerIntEnable(TIMER0_BASE, TIMER_INT_MATCH);
    
    //
    // Start the timer
    //
    TimerStart(TIMER0_BASE);
        
    //
    // One shot mode test.
    //
    while(1)
    {       
        //
        // wait until the timer data register reach equel to compare register
        //
        while(!TimerIntStatus(TIMER0_BASE, TIMER_INT_MATCH));
        TimerIntClear(TIMER0_BASE, TIMER_INT_MATCH);
    }  
}