//*****************************************************************************
//
//! \file sysctlpwr.c
//! \brief An Example Of powerdown and wake up.
//! \version 1.0
//! \date 1/11/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_ints.h"
#include "xgpio.h"
#include "xhw_nvic.h"
#include "xhw_gpio.h"

//*****************************************************************************
//
//! Enter Sleep Mode function.
//!
//! \This function will force the processor enter sleep mode,after operating 
//! the action,some clocks will be closed except "Internal 10 kHz low speed 
//! oscillator clock".
//!  
//! \return None
//*****************************************************************************
void PWRCtlStandby(void)
{
    xSysCtlClockSet(50000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
    xSysCtlSleep();
}
 
//*****************************************************************************
//
//! Wake up mcu from sleep mode function.
//!
//! \This function use extern interrupt to wake up mcu from sleep mode 
//!  
//! \return None
//*****************************************************************************
void WakeUpFromPowerDown(void)
{	 
    xIntEnable(INT_EINT1);
    xIntPrioritySet(INT_EINT1, 1);
    xGPIOSPinTypeGPIOInput(PD3);
    xSPinTypeEXTINT(NINT1, PD3);
    xGPIOPinIntEnable(GPIO_PORTD_BASE, GPIO_PIN_3, xGPIO_FALLING_EDGE);
}
