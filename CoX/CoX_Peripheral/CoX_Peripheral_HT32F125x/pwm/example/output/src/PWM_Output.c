//*****************************************************************************
//
//! \file PWM_Output.c
//! \brief PWM output function test.
//! \version 2.1.1.0
//! \date 4/11/2012
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
#include "xpwm.h"

//*****************************************************************************
//
//! \brief PWM output function example. 
//! Configure the pwm channel0 as output toggle mode, the duty is 40. This code
//! is tested on the HT32F125x Development Board.
//!
//! \return None.
//
//*****************************************************************************
void PWM_Output()
{
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMA);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    
    //
    // Set GPIO Pin as PWM and enable PWM
    //
    xSPinTypePWM(TIMCCP0, PA3);
                                             
    //
    // Set invert, dead zone and mode
    //
    xPWMInitConfigure(xPWMA_BASE, xPWM_CHANNEL0, xPWM_TOGGLE_MODE);
	
    // Set CNR, Prescale and Divider
    xPWMFrequencyConfig( xPWMA_BASE, xPWM_CHANNEL0, 0x3FF1111 );
	
    //    
    // Set CMR
    //
    xPWMDutySet(xPWMA_BASE, xPWM_CHANNEL0, 40);
	
	//    
    // Set output enable
    //
    xPWMOutputEnable(xPWMA_BASE, xPWM_CHANNEL0);   
	
    //    
    // start pwm
    //
    xPWMStart(xPWMA_BASE, xPWM_CHANNEL0);
}

