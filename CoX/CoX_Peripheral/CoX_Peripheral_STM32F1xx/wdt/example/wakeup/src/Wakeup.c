//*****************************************************************************
//
//! \file Wakeup.c
//! \brief WDT wakeup function.
//! \version 1.0
//! \date 3/31/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xcore.h"
#include "xdebug.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xhw_wdt.h"
#include "xsysctl.h"
#include "xwdt.h"

//*****************************************************************************
//
// Function protype.
//
//*****************************************************************************

unsigned long WdtCallback(void *pvCBData, unsigned long ulEvent, 
                                    unsigned long ulMsgParam, void *pvMsgData);

//*****************************************************************************
//
//! \brief Wdt wakeup example.
//!
//! \return None.
//
//*****************************************************************************
void Wakeup(void) 
{
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    SysCtlDelay(10000);
    //
    // Enable WDT wake up function.
    //
    xWDTFunctionEnable(xWDT_BASE, xWDT_INT_FUNCTION);

    //
    // Set WDT clock and interval time.
    //
    xWDTInit(xWDT_BASE, SYSCTL_PERIPH_WDG_S_EXTSL, 512);

    //
    // Set WDT interrupt and initionalize callback.
    //
    xWDTIntCallbackInit(xWDT_BASE, WdtCallback);
    xIntEnable(xINT_WDT);
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
