/******************************************************************************
 * \file    GPIO_Example_LED_Blink.c
 * \brief   GPIO LED Blink example.
 * This example shows how to blink led(PC3).
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


#define TICK_SLOW               ((unsigned long)0xFFFFF)

void GPIO_Example_LED_Blink(void);

void GPIO_Example_LED_Blink(void)
{ 

    /********************** Configure System clock *************************/
    SysCtlClockSet(100000000, SYSCTL_OSC_INT | SYSCTL_XTAL_12_MHZ);
    SysCtlDelay(TICK_SLOW);

    // Enable LED PORT
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    // Configure LED(PC3) pin into output mode.
    xGPIOSPinTypeGPIOOutput(PC3);

    while(1)
    {
        // LED ON
        GPIOPinClr(GPIOC_BASE, GPIO_PIN_3);
        SysCtlDelay(10*TICK_SLOW);

        // LED OFF
        GPIOPinSet(GPIOC_BASE, GPIO_PIN_3);
        SysCtlDelay(10*TICK_SLOW);
    }
}

