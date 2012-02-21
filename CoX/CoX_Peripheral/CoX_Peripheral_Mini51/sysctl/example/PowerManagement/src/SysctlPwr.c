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
#include "xsysctl.h"
#include "xhw_ints.h"
#include "xgpio.h"

static unsigned char sucFlag = 0;

//*****************************************************************************
//
//! INT0 callback function.
//!
//! \This function will set the static value 
//! \return None
//*****************************************************************************
unsigned long INT0CallbackFunction( void *pvCBData, unsigned long ulEvent, 
                                    unsigned long ulMsgParam, void *pvMsgData )
{
    sucFlag = 1;
    return 0;
}

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
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
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
    xIntEnable(INT_EINT0);
    xIntPrioritySet(INT_EINT0, 1);
    xGPIOSPinTypeGPIOInput(PD2);
    xSPinTypeEXTINT(NINT0, PD2);
    xGPIOPinIntEnable(GPIO_PORTD_BASE, GPIO_PIN_2, xGPIO_FALLING_EDGE);
    
    GPIOPinIntCallbackInit(GPIO_PORTD_BASE, GPIO_PIN_2, INT0CallbackFunction);
}
