//*****************************************************************************
//
//! \file Blinky.c
//! \brief Blinky test.
//! \version 1.0
//! \date 01/11/2012
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


void Blinky(void)
{
    unsigned long i;
	
    //
    // Initionalize system clock.
    //
    xSysCtlClockSet(16000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_25MHZ); 
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
	
    //
    // Set GPIO port A pin 0 , 1 output mode.
    //
    xGPIODirModeSet( xGPIO_PORTA_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_OUT );
    xGPIODirModeSet( xGPIO_PORTA_BASE, xGPIO_PIN_1, xGPIO_DIR_MODE_OUT );
	
    while (1)
    {
	    //
        // Delay some time.
        //  
        for( i = 0; i < 0x1FFFF; i++ )
		
	    //
        // Output high level.
        //  
        xGPIOPinWrite( xGPIO_PORTA_BASE, xGPIO_PIN_0 | xGPIO_PIN_1, 1 );
		
	    for( i = 0; i < 0x1FFFF; i++ )
		
	    //
        // Output low level.
        //  
        xGPIOPinWrite( xGPIO_PORTA_BASE, xGPIO_PIN_0 | xGPIO_PIN_1, 0 );
	}
	
}
