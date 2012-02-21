//*****************************************************************************
//
//! \file Wakeup.c
//! \brief WDT wakeup function test.
//! \version 1.0
//! \date 2/18/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xwdt.h"

//*****************************************************************************
//
// Function protype.
//
//*****************************************************************************
unsigned long WdtCallback( void *pvCBData, unsigned long ulEvent, 
                                    unsigned long ulMsgParam, void *pvMsgData );

//*****************************************************************************
//
//! \brief  Wdt wakeup example.
//!
//! \return None.
//
//*****************************************************************************
void Wakeup(void)
{
    //
    // Set system clock
    //
    xSysCtlClockSet(12000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    
    //
    // Enable WDT
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDT);
    
    //
    // Set WDT clock and interval time.
    //
    xWDTInit(xWDT_BASE, SYSCTL_PERIPH_WDG_S_INT10K, xWDT_INTERVAL_2_10T);

    //
    // Set WDT interrupt and initionalize callback.
    //
    xWDTIntCallbackInit(xWDT_BASE, WdtCallback);
    
    //
    // Enable WDT wake up function.
    //
    xWDTFunctionEnable(xWDT_BASE, xWDT_WAKEUP_FUNCTION | xWDT_INT_FUNCTION);
    xIntEnable(xINT_WDT);
    
    //
    // Start WDT timer.
    //
    xWDTEnable(xWDT_BASE);
   
    //
    // Make chip enter into sleep state.
    //
    xSysCtlSleep();
    
    //
    // Interrupt wake up cpu.
    //
    xCPUwfi();

}
 
//*****************************************************************************
//! \breif Wdt interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long WdtCallback( void *pvCBData, unsigned long ulEvent, 
                                     unsigned long ulMsgParam, void *pvMsgData )                                        
{ 
    //
    // Restart wdt timer.
    //
    xWDTRestart();
   
    return 0;
}