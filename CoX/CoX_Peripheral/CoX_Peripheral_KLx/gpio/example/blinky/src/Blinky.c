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
#include "xsysctl.h"
#include "xgpio.h"


void Blinky(void)
{
    unsigned long uli;
	
    //
    // Initionalize system clock.
    //
    xSysCtlClockSet(8000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    
    //
    // Enable PORT
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOD);
    xGPIOSPinTypeGPIOOutput(PD6);
	
    while (1)
    {
	//
        // Delay some time.
        //  
        for( uli = 0; uli < 0x1FFFF; uli++ );
		
	//
        // Output high level.
        //  
        xGPIOPinWrite( xGPIO_PORTD_BASE, xGPIO_PIN_6, 1 );
		
	for( uli = 0; uli < 0x1FFFF; uli++ );
		
	//
        // Output low level.
        //  
        xGPIOPinWrite( xGPIO_PORTD_BASE, xGPIO_PIN_6, 0 );
	}
	
}
