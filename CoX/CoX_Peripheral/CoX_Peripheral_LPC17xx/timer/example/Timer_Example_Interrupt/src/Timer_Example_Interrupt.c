/******************************************************************************
 * \file    Timer_Example_Interrupt.c
 * \brief   Show how to configure timer match interrupt mode.
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

void Timer_Example_Interrupt(void);

unsigned long TimerHandler(void *pvCBData, unsigned long ulEvent,
                              unsigned long ulMsgParam, void *pvMsgData)
{
    // Clear Channel 0 capture/match interrtup flag.
    TimerIntStatusClear(TIMER0_BASE, TIMER_INT_CAP_CH_0 | TIMER_INT_MAT_CH_0);

    return (0);
}

void Timer_Example_Interrupt(void)
{ 
    unsigned long i = 0;

    /********************** Configure System clock *************************/
    SysCtlClockSet(100000000, SYSCTL_OSC_INT | SYSCTL_XTAL_12_MHZ);
    SysCtlDelay(TICK_SLOW);

    /************** Timer Interrupt **************************************/
    GPIOPinFunCfg(GPIOB_BASE, GPIO_PIN_28,  GPIO_PB28_TIM_MAT0_0);

    // Enable NVIC timer interrupt then register user's ISR.
    xIntEnable(xINT_TIMER0);
    TimerIntCallbackInit(TIMER0_BASE, TimerHandler);

    // Configure Timer prescale
    // 1/1000 system clock.
    TimerPrescaleSet(TIMER0_BASE, 1000-1);

    // Match reset and pin toggle mode.
    // A pluse will product on the Pin PB28.
    TimerMatchCfg(TIMER0_BASE, TIMER_MAT_CH_0, TIMER_MAT_RESET | TIMER_MAT_INT | TIMER_MAT_PIN_TOGGLE);
    TimerMatchValueSet(TIMER0_BASE, TIMER_MAT_CH_0, 5000);
    TimerReset(TIMER0_BASE);
    TimerStart(TIMER0_BASE);

    while(1);
}

