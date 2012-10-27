#include <stdint.h>
#include <stdio.h>
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_wdt.h"
#include "xwdt.h"


//
// Show how to configure watchdog in Freescale KLxx serial MCU
//

void main(void)
{
    //
    // Configure System clock
    //
    xSysCtlClockSet(48000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);

    //
    // Configure watchdog
    // MODE    : Normal Mode
    // CLOCK   : Bus clock
    // TIMEOUT : 2**16 Tick
    //
    WDTimerInit(WDT_MODE_NORMAL | WDT_INTERVAL_BUS_2_16T);

    //
    // Start the Watchdog Timer.
    //
    WDTimerEnable();

    //
    // Feed watchdog, unless watchdog will reset MCU
    //
    while(1)
    {
       //
       // Delay
       //
       SysCtlDelay(0xFFF); 

       //
       // Feed watchdog
       //
       WDTimerRestart();
    }
}
