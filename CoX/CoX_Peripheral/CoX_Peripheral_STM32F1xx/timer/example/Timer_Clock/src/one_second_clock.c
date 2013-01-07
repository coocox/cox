//*****************************************************************************
//
//! \file one_second_clock.c
//! \brief Use the timer to make a one second clock.
//! \date 9/20/2011
//! \author CooCox
//! 
//! \copy
//
//*****************************************************************************
#include "xhw_types.h"
#include "xcore.h"
#include "xhw_gpio.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_timer.h"
#include "xgpio.h"
#include "xsysctl.h"
#include "xtimer.h"

unsigned long Timer0Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData);

//*****************************************************************************
//
//! \biref The main example function
//! Enable the timer0, and it's interrupt, the overfolw interrupt will happen 
//! every 1 second. It is tested on the HT32F125x Development board.
//! \return  none
//
//*****************************************************************************
void OneSecondClock(void)
{   
    //
    // Clear the flag first
    //
    TimerIntClear(xTIMER1_BASE, TIMER_INT_UEV);
    
    //
    // Config as periodic mode
    //
    xTimerInitConfig(xTIMER1_BASE, xTIMER_CHANNEL0, xTIMER_MODE_PERIODIC | xTIMER_COUNT_UP, 1000); 
    xTimerMatchSet(xTIMER1_BASE, xTIMER_CHANNEL0, 1000);
    xTimerPrescaleSet(xTIMER1_BASE, xTIMER_CHANNEL0, 8);
       
    xTimerIntCallbackInit(xTIMER1_BASE, Timer0Callback);
    xTimerIntEnable(xTIMER1_BASE, xTIMER_CHANNEL0, xTIMER_INT_MATCH);
    xIntEnable(xTIMER1_BASE);

    xTimerStart(xTIMER1_BASE, xTIMER_CHANNEL0);
    
    while(1); 

}
//
// Install callback function
//
unsigned long Timer0Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     //
     // Clear the status
     //
     TimerFlagStatusClear(xTIMER1_BASE, TIMER_FLAG_UPDATE);
     return 0;
}
