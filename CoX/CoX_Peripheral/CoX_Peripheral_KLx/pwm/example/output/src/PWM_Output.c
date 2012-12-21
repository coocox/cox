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
//! \brief PWM output function example. 
//!
//! \return None.
//
//*****************************************************************************
void PWM_Output()
{
    //
    // Disable the watchdog
    //
    xHWREG(SIM_COPC) = 0x00;
	
	//
    // Configure System clock
    //
    xSysCtlClockSet(48000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
	
	//
    // Select the peripheral clock source
    //
    xSysCtlPeripheralClockSourceSet(xSYSCTL_PWMA_MAIN, 1);
    
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_PWMA);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	
    //
    // Enable PWM and set GPIO Pin as PWM
    //
    xSPinTypePWM(TIM0CH2, PE29); 
                                             
    //
    // Set invert, dead zone and mode
    //
    xPWMInitConfigure(xPWMA_BASE, xPWM_CHANNEL2, xPWM_TOGGLE_MODE);
	
    //
    // Set CNR, Prescale and Divider. FHz = 100k
    //
    xPWMFrequencySet(xPWMA_BASE, xPWM_CHANNEL2, 100000);
	
    //    
    // Set CMR
    //
    xPWMDutySet(xPWMA_BASE, xPWM_CHANNEL2, 40);
	
    //    
    // Set output enable
    //
    xPWMOutputEnable(xPWMA_BASE, xPWM_CHANNEL2);   
	
    //    
    // start pwm
    //
    xPWMStart(xPWMA_BASE, xPWM_CHANNEL2);
}
