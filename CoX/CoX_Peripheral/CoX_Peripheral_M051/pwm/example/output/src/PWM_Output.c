//*****************************************************************************
//
//! \file PWM_Output.c
//! \brief PWM output function test.
//! \version 1.0
//! \date 10/27/2011
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
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xuart.h"
#include "xpwm.h"

//*****************************************************************************
//
// Function protype.
//
//*****************************************************************************
unsigned long user_Callback( void *pvCBData, unsigned long ulEvent, 
                                    unsigned long ulMsgParam, void *pvMsgData );

//*****************************************************************************
//
//! \brief PWM output function example. 
//!
//! \return None.
//
//*****************************************************************************
void PWM_Output()
{
    //
    // Set GPIO Pin as PWM and enable PWM
    //
    xSPinTypePWM( PWM5, PC5 );
	xSysCtlPeripheralEnable( xSYSCTL_PERIPH_PWMB );
                                             
    //
    // Set invert, dead zone and mode
    //
    xPWMInitConfigure( xPWMB_BASE, xPWM_CHANNEL5, xPWM_TOGGLE_MODE | 
	                            xPWM_OUTPUT_INVERTER_DIS | xPWM_DEAD_ZONE_DIS );
	
    // Set CNR, Prescale and Divider
    xPWMFrequencyConfig( xPWMB_BASE, xPWM_CHANNEL5, 0x3FF1111 );
	
    //    
    // Set CMR
    //
    xPWMDutySet( xPWMB_BASE, xPWM_CHANNEL5, 40 );
	
	//    
    // Set output enable
    //
    xPWMOutputEnable( xPWMB_BASE, xPWM_CHANNEL5 );   
	
    // Set interrupt call back 
    xPWMIntCallbackInit( xPWMB_BASE, user_Callback );
	
    //
    // PWM output interrupt enable
    //
    xPWMIntEnable( xPWMB_BASE, xPWM_CHANNEL5, xPWM_INT_PWM );
	
    //
    // NVIC interrupt enable
    //
    xIntEnable( xINT_PWMB );
	
    //    
    // start pwm
    //
    xPWMStart( xPWMB_BASE, xPWM_CHANNEL5 );
}

//*****************************************************************************
//! \breif PWM interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long user_Callback( void *pvCBData, unsigned long ulEvent, 
							         unsigned long ulMsgParam, void *pvMsgData )                                        
{
    //
    // Change the PWM's duty
    //
    static unsigned long ultemp = 0;
    ultemp += 5;
    if ( ultemp > 100 )
         ultemp = 10;
	
    xPWMDutySet( xPWMB_BASE, xPWM_CHANNEL5, ultemp );    
    
    return 0;
}
