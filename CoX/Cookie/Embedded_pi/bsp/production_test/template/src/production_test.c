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
#include "xuart.h"

#define MAX_TICK 0xFFFFF
#define AFIO_DEBUG_REG (*(volatile unsigned int *)0x40010004)


static void PrintStr(const char * pStr)
{
	while(*pStr != '\0')
	{
		xUARTCharPut(USART1_BASE, *pStr++);
	}
}

void Blinky(void)
{
	volatile int i = 0;
    //
    // Initionalize system clock.
    //
    xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);

    //
    // Configure LED and USB Disc Port
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOB);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xGPIOPinConfigure(PB4(APP), PB4);

    //
    // Configure UART Pin
    // PA9-->TX   PA10-->RX
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
    xSPinTypeUART(UART1TX, PA9);
    xSPinTypeUART(UART1RX, PA10);

    //xSPinTypeUART(UART2TX, PA2);
    //xSPinTypeUART(UART2RX, PA3);

    //
    // Configure UART1 115200 8-N-1
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
    xUARTConfigSet(USART1_BASE, 115200, xUART_CONFIG_WLEN_8 |
    		                            xUART_CONFIG_STOP_1 |
    		                            xUART_CONFIG_PAR_NONE);
    xUARTEnable(USART1_BASE, xUART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX);

    PrintStr("Embedded Pi Board Test Begin\r\n");
    PrintStr("1:LED Test, Now LED will Light\r\n");

    //
    // Configure LED Port
    //
    xGPIODirModeSet( xGPIO_PORTB_BASE, xGPIO_PIN_13, xGPIO_DIR_MODE_OUT );
    xGPIOPinWrite( xGPIO_PORTB_BASE, xGPIO_PIN_13 , 1 );

    xSysCtlDelay(MAX_TICK*10);

    PrintStr("2: USB Disc Test, Now you computer will find a new device\r\n");
    PrintStr("And LED is Blinking\r\n");
    xGPIODirModeSet( xGPIO_PORTB_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_OUT );
    xGPIOPinWrite( xGPIO_PORTB_BASE, xGPIO_PIN_4 , 0 );

    //
    // Shane LED to indicate that USB Disc is PROCESSING
    //
    for(i = 0; i < 10; i++)
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

    PrintStr("Now, USB Disc test is over and led will be turned off\r\n");
    //
    // Turn off LED, USB Disc is over
    //
    xGPIOPinWrite( xGPIO_PORTB_BASE, xGPIO_PIN_4 , 1 );
    xGPIOPinWrite( xGPIO_PORTB_BASE, xGPIO_PIN_13 , 0 );

    //Configure PB4 to Jtag Mode
    AFIO_DEBUG_REG &= 0x00FFFFFF;


    //
    // Test Low Speed External crystal
    //
    PrintStr("3: Low Speed External crystal test begin\r\n");
    PrintStr("If you can't see OK later, then test is failure\r\n");
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_PWR | SYSCTL_PERIPH_BKP);
    SysCtlBackupAccessEnable();
    SysCtlLSEConfig(SYSCTL_LSE_OSC_EN);
    PrintStr("OK\r\n");

    PrintStr("Running");

    while(1)
    {
    	xGPIOPinWrite( xGPIO_PORTB_BASE, xGPIO_PIN_13 , 1 );
        PrintStr(".");
        xSysCtlDelay(10*MAX_TICK);

        xGPIOPinWrite( xGPIO_PORTB_BASE, xGPIO_PIN_13 , 0 );
        PrintStr(".");
        xSysCtlDelay(10*MAX_TICK);

        xGPIOPinWrite( xGPIO_PORTB_BASE, xGPIO_PIN_13 , 1 );
        PrintStr(".");
        xSysCtlDelay(10*MAX_TICK);

        xGPIOPinWrite( xGPIO_PORTB_BASE, xGPIO_PIN_13 , 0 );
        PrintStr(".");
        xSysCtlDelay(10*MAX_TICK);

        PrintStr("\b\b\b\b    \b\b\b\b");
    }
}
