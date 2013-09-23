/******************************************************************************
 * \file    Timer_Example_Capture.c
 * \brief   Show how to configure timer Capture mode.
 * 
******************************************************************************/

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xdebug.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_timer.h"
#include "xtimer.h"

#define TICK_SLOW              ((unsigned long)0xFFFFF)

void Timer_Example_Capture(void);

unsigned long TimerHandler(void *pvCBData, unsigned long ulEvent,
                              unsigned long ulMsgParam, void *pvMsgData)
{
    TimerIntStatusClear(TIMER0_BASE, TIMER_INT_CAP_CH_0 | TIMER_INT_MAT_CH_0);
    return (0);
}

void Timer_Example_Capture(void)
{ 

    /********************** Configure System clock *************************/
    SysCtlClockSet(100000000, SYSCTL_OSC_INT | SYSCTL_XTAL_12_MHZ);
    SysCtlDelay(TICK_SLOW);

    /************** Timer Capture Interrupt **************************************/
    GPIOPinFunCfg(GPIOB_BASE, GPIO_PIN_26,  GPIO_PB26_TIMCCP0);

    TimerPrescaleSet(TIMER0_BASE, 1);
    TimerCaptureCfg(TIMER0_BASE, TIMER_CAP_CH_0, TIMER_CFG_CAP_RISING | TIMER_CFG_CAP_INT);
    TimerReset(TIMER0_BASE);
    TimerStart(TIMER0_BASE);

    // Regeister user's ISR then enable NVIC timer interrupt. 
    TimerIntCallbackInit(TIMER0_BASE, TimerHandler);
    xIntEnable(xINT_TIMER0);

    while(1);
}

