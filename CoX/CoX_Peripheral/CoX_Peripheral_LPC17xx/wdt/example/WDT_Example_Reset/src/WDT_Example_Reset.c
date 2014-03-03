/******************************************************************************
 * \file    WDT_Example_Reset.c
 * \brief   Watchdog reset example.
 * 
 * This example show how to use wdt reset mode.
 * First Enable WDT/GPIO power, then configure wdt into reset mode, then start
 * Watchdog counter, you will see led blink slowly now. when LED blink 50 times,
 * we stop feed the watchdog, so mcu will reset when watchdog counter timeout.
 * This time, our check reset source, if watchdog reset, it will set led on.
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
#include "xhw_wdt.h"
#include "xwdt.h"

#define TICK_SLOW               ((unsigned long)0xFFFF)

void WDT_Example_Reset(void);

void WDT_Example_Reset(void)
{ 
    unsigned long i = 0;

    /********************** Configure System clock *************************/
    SysCtlClockSet(100000000, SYSCTL_OSC_INT | SYSCTL_XTAL_12_MHZ);
    SysCtlDelay(TICK_SLOW);

    // Power WDT/GPIO on
    // Note: For LPC17xx, Watchdog module is always enabled.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    // Configure LED pin PC3
    xGPIOSPinTypeGPIOOutput(PC3);

    // Reset source is watchdog ?
    if(xtrue == WDTStatusFlagCheck(WDT_FLAG_TIMEOUT))    // Watchdog has reset mcu
    {
        // Clear Watchdog timeout flag
        WDTStatusFlagClear(WDT_FLAG_TIMEOUT);

        // Turn off the LED        
        GPIOPinClr(GPIOC_BASE, GPIO_PIN_3);
        while(1);
    }                                                    // First configure watchdog
    else
    {
        // Configure watchdog into reset mode.
        WDTCfg(WDT_CFG_RESET_MODE | WDT_CFG_CLKSRC_IRC, 0xFFFFF);
        WDTEnable();

        // Feed Watchdog and blink LED 50 times.
        for(i = 0; i < 50; i++)
        {
            WDTFeed();

            // LED ON
            GPIOPinClr(GPIOC_BASE, GPIO_PIN_3);
            SysCtlDelay(20*TICK_SLOW);

            // LED OFF
            GPIOPinSet(GPIOC_BASE, GPIO_PIN_3);
            SysCtlDelay(20*TICK_SLOW);
        }

        // Stop Feed watchdog and wait for mcu reset.
        while(1);
    }
}

