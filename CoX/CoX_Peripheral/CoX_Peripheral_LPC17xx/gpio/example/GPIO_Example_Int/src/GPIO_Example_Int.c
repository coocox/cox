/******************************************************************************
 * \file    GPIO_Example_Int.c
 * \brief   GPIO int triggle example.
 * This example shows how to configure gpio int triggle mode.
 * When detect a rising edge on PC10(P2.10) pin, mcu will run into
 * INT3 interrrupt handler, in this function, we will toggle LED(PC3).
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


void GPIO_Example_Int(void);


unsigned long GpioTriHandler(void *pvCBData, unsigned long ulEvent,
                              unsigned long ulMsgParam, void *pvMsgData)
{
    static unsigned long LedStatus = 0;

    // Clear interrupt flag
    if(GPIOPinIntFlagGet(GPIOC_BASE, GPIO_PIN_10) & INT_TYPE_RISING)
    {
        GPIOPinIntFlagClear(GPIOC_BASE, GPIO_PIN_10);
    }
    else
    {
        while(1);
    }

    // Toggle LED
    if (LedStatus)
    {
        LedStatus = 0;
        // LED ON
        GPIOPinClr(GPIOC_BASE, GPIO_PIN_3);
    }
    else
    {
        LedStatus = 1;
        // LED OFF
        GPIOPinSet(GPIOC_BASE, GPIO_PIN_3);
    }

    return (0);
}

void GPIO_Example_Int(void)
{ 

    /********************** Configure System clock *************************/
    SysCtlClockSet(100000000, SYSCTL_OSC_INT | SYSCTL_XTAL_12_MHZ);
    SysCtlDelay(TICK_SLOW);

    // Enable LED PORT, Triggle PORT
    // PC3 PC10
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    // Configure LED(PC3) pin into output mode.
    xGPIOSPinTypeGPIOOutput(PC3);

    // Configure PC10 into input mode.    
    GPIOPinFunCfg(GPIOC_BASE, GPIO_PIN_10, GPIO_PC10_PC10);
    GPIOPinModeCfg(GPIOC_BASE, GPIO_PIN_10, PIN_MODE_INPUT | PIN_MODE_NONE);

    // Configure rising edge triggler on PC10
    GPIOPinIntCfg(GPIOC_BASE, GPIO_PIN_10, INT_TYPE_RISING);

    // Register user isr function.
    xGPIOPinIntCallbackInit(GPIOC_BASE, GPIO_PIN_10, GpioTriHandler);

    // Enable NVIC GPIOC Port interrupt
    xIntEnable(xINT_GPIOC);

    while(1)
    {
        // Dothing
    }
}


