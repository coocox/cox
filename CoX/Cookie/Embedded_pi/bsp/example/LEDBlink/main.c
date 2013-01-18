#include "cookie.h"
#include "xgpio.h"
#include "xuart.h"
#include "xsysctl.h"
#define MAX_TICK 0xFFFFF

int main()
{
    //
    // Initionalize system clock.
    //
    xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    xSysCtlDelay(1000);
	
    //
    // Configure LED Port
    //
    xGPIODirModeSet( xGPIO_PORTB_BASE, xGPIO_PIN_13, xGPIO_DIR_MODE_OUT );
    xGPIOPinWrite( xGPIO_PORTB_BASE, xGPIO_PIN_13 , 1 );

    while(1)
    {
    	//
    	// Turn on LED
    	//
        xGPIOPinWrite( xGPIO_PORTB_BASE, xGPIO_PIN_13 , 1 );
        xSysCtlDelay(MAX_TICK);

    	//
    	// Turn off LED
    	//
        xGPIOPinWrite( xGPIO_PORTB_BASE, xGPIO_PIN_13 , 0 );
        xSysCtlDelay(MAX_TICK);
    }
}
