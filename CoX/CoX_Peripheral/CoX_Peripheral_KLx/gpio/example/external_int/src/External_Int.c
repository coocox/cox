//*****************************************************************************
//
//! \file External_Int.c
//! \brief External interrupt test.
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
#include "xsysctl.h"
#include "xgpio.h"
#include "xuart.h"

//
// Global variable value
//
volatile char cIntCount;

//
// GPIO base value
//
static unsigned long ulGPIO[2] = {xGPIO_PORTA_BASE,xGPIO_PORTD_BASE};

//
// GPIO interrupt ID  
//
static unsigned long ulGPIOInt[2] = {xINT_GPIOA, xINT_GPIOD};

unsigned long user_Callback(void *pvCBData, unsigned long ulEvent, 
                            unsigned long ulMsgParam, void *pvMsgData);

//*****************************************************************************
//
//! \brief xgpio002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
void External_Int(void)
{
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOD);    
    
    //
    // Level trigger interrupt
    //
    xGPIOSPinTypeGPIOInput(PD7);
    
    //
    // Set GPIO pin interrupt callback.
    //
    xGPIOPinIntCallbackInit(ulGPIO[1], xGPIO_PIN_7, user_Callback);
    
    //
    // Enable GPIO pin interrupt.
    //
    xGPIOPinIntEnable(ulGPIO[1], xGPIO_PIN_7, xGPIO_FALLING_EDGE);
    
    xIntEnable(ulGPIOInt[1]);
    while(1); 
}   

//*****************************************************************************
//! \breif External interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long user_Callback(void *pvCBData, unsigned long ulEvent, 
                                     unsigned long ulMsgParam, void *pvMsgData)                                        
{
    xIntDisable(ulGPIOInt[1]);
    cIntCount++;
    return 0;
}


