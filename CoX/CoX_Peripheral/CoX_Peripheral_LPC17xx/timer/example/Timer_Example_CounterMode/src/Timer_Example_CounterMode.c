/******************************************************************************
 * \file    Timer_Example_CounterMode.c
 * \brief   Show how to configure timer into counter mode.
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

void Timer_Example_CounterMode(void);

void Timer_Example_CounterMode(void)
{ 

    unsigned long Status = 0;

    /********************** Configure System clock *************************/
    SysCtlClockSet(100000000, SYSCTL_OSC_INT | SYSCTL_XTAL_12_MHZ);
    SysCtlDelay(TICK_SLOW);

    // Enable LED PORT
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    // Configure LED(PC3) pin into output mode.
    xGPIOSPinTypeGPIOOutput(PC3);

    // Configure Timer Capture pin(PB26)
    GPIOPinFunCfg(GPIOB_BASE, GPIO_PIN_26,  GPIO_PB26_TIMCCP0);

    TimerCounterCfg(TIMER0_BASE, TIMER_CFG_CNT_CAP0_BOTH);
    TimerReset(TIMER0_BASE);
    TimerStart(TIMER0_BASE);

    while (1)
    {

        if( (TimerValueGet(TIMER0_BASE) % 10) == 0)
        {
            if(Status)
            {
                // Turn on LED
                Status = 0;
                GPIOPinSet(GPIOC_BASE, GPIO_PIN_3);
            }
            else
            {
                // Turn off LED
                Status = 1;
                GPIOPinClr(GPIOC_BASE, GPIO_PIN_3);
            }
        }
    }

    while(1);
}

