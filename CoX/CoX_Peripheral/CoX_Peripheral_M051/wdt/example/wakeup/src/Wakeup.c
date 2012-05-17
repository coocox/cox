//*****************************************************************************
//
//! \file Wakeup.c
//! \brief WDT wakeup function test.
//! \version 1.0
//! \date 10/21/2011
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
#include "xsysctl.h"
#include "xgpio.h"
#include "xuart.h"
#include "xwdt.h"

//*****************************************************************************
//
// Function protype.
//
//*****************************************************************************
unsigned long user_Callback( void *pvCBData, unsigned long ulEvent, 
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
    // Set WDT clock and interval time.
    //
    xWDTInit(xWDT_BASE, SYSCTL_PERIPH_WDG_S_INT10K, xWDT_INTERVAL_2_10T);

    //
    // Set WDT interrupt and initionalize callback.
    //
    xWDTIntCallbackInit(xWDT_BASE, user_Callback);
    
    //
    // Enable WDT wake up function.
    //
    xWDTFunctionEnable(xWDT_BASE, xWDT_WAKEUP_FUNCTION | xWDT_INT_FUNCTION);
    xIntEnable( xINT_WDT );
    
    //
    // Start WDT timer.
    //
    xWDTEnable( xWDT_BASE );
   
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
unsigned long user_Callback( void *pvCBData, unsigned long ulEvent, 
                                     unsigned long ulMsgParam, void *pvMsgData )                                        
{ 
    //
    // Restart wdt timer.
    //
    xWDTRestart();
   
    return 0;
}