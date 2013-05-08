//*****************************************************************************
//
//! \file MotorStep.c
//! \brief Shield used for drive motors..
//! \version 1.0
//! \date 01/11/2013
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2013 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xsysctl.h"
#include "xtimer.h"
#include "cookie_cfg.h"
#include "cookie.h"
#include "MotorShield.h"

void MotorStep(void)
{
    unsigned long i, j;

    xSysCtlClockSet(72000000, (xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ));
    xSysCtlDelay(100000);
/*
	xGPIOSPinTypeGPIOOutput(sD3);   
    //
	// MSDelay() test
	//
	while(1)
	{
	    xGPIOSPinWrite(sD3, 1);
		MSDelay(xTIMER0_BASE, xTIMER_CHANNEL0, 1);
	    xGPIOSPinWrite(sD3, 0);
	    MSDelay(xTIMER0_BASE, xTIMER_CHANNEL0, 1);
    }
*/

	MSStepMotorInit(MS_STEPPER_NUM2);
	MSStepsDelaySet(1);
	for(i = 0; i < 50; i++)
	{
		MSStepMotorRun(MS_RUN_FORWARD, 50);
		MSStepMotorStop();
	}
}			  	
