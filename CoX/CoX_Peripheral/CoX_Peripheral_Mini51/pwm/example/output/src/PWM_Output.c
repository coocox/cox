//*****************************************************************************
//
//! \file PWM_Output.c
//! \brief PWM output function test.
//! \version 1.0
//! \date 2/17/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xpwm.h"

//*****************************************************************************
//
// Function protype.
//
//*****************************************************************************
unsigned long PWMCallback( void *pvCBData, unsigned long ulEvent, 
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
    // Set System clock
    //
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
    
    //
    // Set the timer clock
    //
    xSysCtlPeripheralClockSourceSet(xSYSCTL_PWMA_HCLK, 1);
    
    //
    // Set GPIO Pin as PWM and enable PWM
    //
    xSPinTypePWM(PWM5, PA4);
	xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMA);
                                             
    //
    // Set invert, dead zone and mode
    //
    xPWMInitConfigure(xPWMA_BASE, xPWM_CHANNEL5, xPWM_TOGGLE_MODE | 
	                                             xPWM_OUTPUT_INVERTER_DIS | 
                                                 xPWM_DEAD_ZONE_DIS);
	
    // Set CNR, Prescale and Divider
    xPWMFrequencyConfig(xPWMA_BASE, xPWM_CHANNEL5, 0x3FF1111);
	
    //    
    // Set CMR
    //
    xPWMDutySet(xPWMA_BASE, xPWM_CHANNEL5, 40);
	
	//    
    // Set output enable
    //
    xPWMOutputEnable(xPWMA_BASE, xPWM_CHANNEL5);   
	
    // Set interrupt call back 
    xPWMIntCallbackInit(xPWMA_BASE, PWMCallback);
	
    //
    // PWM output interrupt enable
    //
    xPWMIntEnable(xPWMA_BASE, xPWM_CHANNEL5, xPWM_INT_PWM);
	
    //
    // NVIC interrupt enable
    //
    xIntEnable(xINT_PWMA);
	
    //    
    // start pwm
    //
    xPWMStart(xPWMA_BASE, xPWM_CHANNEL5);
}

//*****************************************************************************
//! \breif PWM interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long PWMCallback( void *pvCBData, unsigned long ulEvent, 
							         unsigned long ulMsgParam, void *pvMsgData )                                        
{
    //
    // Change the PWM's duty
    //
    static unsigned long ulTemp = 0;
    ulTemp += 5;
    if ( ulTemp > 100 )
         ulTemp = 10;
    xPWMDutySet(xPWMA_BASE, xPWM_CHANNEL5, ulTemp);    
    
    return 0;
}
