//*****************************************************************************
//
//! \file Blinky.c
//! \brief Blinky test.
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
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xsysctl.h"
#include "xgpio.h"


void Blinky(void)
{
    unsigned long uli;
	
    //
    // Initionalize system clock.
    //
    xSysCtlPeripheralClockSourceSet( 10000000,  xSYSCTL_XTAL_6MHZ );
	
    //
    // Set GPIO port c pin 12, 13, 14, 15 output mode.
    //
    xGPIODirModeSet( xGPIO_PORTC_BASE, xGPIO_PIN_12, xGPIO_DIR_MODE_OUT );
    xGPIODirModeSet( xGPIO_PORTC_BASE, xGPIO_PIN_13, xGPIO_DIR_MODE_OUT );
    xGPIODirModeSet( xGPIO_PORTC_BASE, xGPIO_PIN_14, xGPIO_DIR_MODE_OUT );
    xGPIODirModeSet( xGPIO_PORTC_BASE, xGPIO_PIN_15, xGPIO_DIR_MODE_OUT );
	
    while (1)
    {
	//
        // Delay some time.
        //  
        for( uli = 0; uli < 0x1FFFF; uli++ )
		
	//
        // Output high level.
        //  
        xGPIOPinWrite( xGPIO_PORTC_BASE, xGPIO_PIN_12 | xGPIO_PIN_13 | 
		                               xGPIO_PIN_14 | xGPIO_PIN_15, 1 );
		
	for( uli = 0; uli < 0x1FFFF; uli++ )
		
	//
        // Output low level.
        //  
        xGPIOPinWrite( xGPIO_PORTC_BASE, xGPIO_PIN_12 | xGPIO_PIN_13 | 
		                               xGPIO_PIN_14 | xGPIO_PIN_15, 0 );
	}
	
}
