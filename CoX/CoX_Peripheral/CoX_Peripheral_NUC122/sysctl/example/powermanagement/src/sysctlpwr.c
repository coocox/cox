//*****************************************************************************
//
//! \file sysctlpwr.c
//! \brief An Example Of powerdown and wake up.
//! \version 1.0
//! \date 12/16/2011
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
#include "sysctlpwr.h"

//*****************************************************************************
//
//! Enter Sleep Mode function.
//!
//! \This function will force the processor enter sleep mode,after operating 
//! the action,some clocks will be closed except "Internal 10 kHz low speed 
//! oscillator clock"and "External 32.768 kHz low speed crystal clock ".
//!  
//! \return None
//*****************************************************************************
void PWRCtlStandby(void)
{
    SysCtlDeepSleep();
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
    GPIODirModeSet(GPIO_PORTB_BASE, GPIO_PIN_15,GPIO_DIR_MODE_IN);
    GPIOPinIntEnable(GPIO_PORTB_BASE, GPIO_PIN_15,GPIO_FALLING_EDGE);
}

