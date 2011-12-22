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

//*****************************************************************************
//
// Global variable.
//
//*****************************************************************************
static unsigned char ucflag = 0;

//*****************************************************************************
//! \breif External interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long user_Callback( void *pvCBData, unsigned long ulEvent, 
                                     unsigned long ulMsgParam, void *pvMsgData )    
{
    xGPIOPinWrite( xGPIO_PORTC_BASE, xGPIO_PIN_8 | xGPIO_PIN_9, 0 );
    ucflag = 1;
    
    return 0;
}

void External_Int( void )
{
    //
    // Set GPIO port B pin 10 mode.
    //
    xGPIODirModeSet( xGPIO_PORTB_BASE, xGPIO_PIN_10, xGPIO_DIR_MODE_IN );
    
    //
    // Set GPIO port C pin 12, 13 mode.
    //
    xGPIODirModeSet( xGPIO_PORTC_BASE, xGPIO_PIN_8 | xGPIO_PIN_9, 
                                                      xGPIO_DIR_MODE_OUT );
	
    //
    // Set GPIO pin interrupt callback.
    //
    xGPIOPinIntCallbackInit( xGPIO_PORTB_BASE, xGPIO_PIN_10, user_Callback );
    
    //
    // Enable GPIO pin interrupt.
    //
    xGPIOPinIntEnable( xGPIO_PORTB_BASE, xGPIO_PIN_10, xGPIO_BOTH_EDGES );
    xIntEnable( xINT_GPIOB );
    
    ucflag = 0;
    while (ucflag == 0);
}