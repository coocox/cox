//*****************************************************************************
//
//! \file UartPrintf.c
//! \brief Using UART0 to print some data to terminal.
//! \version 1.0
//! \date 1/11/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xuart.h"

unsigned char ucData[] = "M051.UART Example of CoX \r\n";

//*****************************************************************************
//
//! \brief print some data to terminal.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void UartPrintf(void)
{
    unsigned long i;
    //
    //Set System Clock
    //
    xSysCtlClockSet(50000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
 
    xSysCtlDelay(10000);

    xSPinTypeUART(UART0RX, PD0);
    xSPinTypeUART(UART0TX, PD1);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    //
    // Set UART0 clock source.
    //
    xSysCtlPeripheralClockSourceSet(xSYSCTL_UART0_MAIN, 1);

    //
    // Configure 8 bit word length, 1 stop bit, 
    // and none parity bit, receive FIFO 1 byte.
    //
    xUARTConfigSet(UART0_BASE, 115200, (xUART_CONFIG_WLEN_8 | 
                                        xUART_CONFIG_STOP_1 | 
                                        xUART_CONFIG_PAR_NONE));

    xUARTEnable(UART0_BASE, (UART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX));
    
    for(i = 0; i < sizeof("M051.UART Example of CoX \r\n"); i++)
    {
        xUARTCharPut(UART0_BASE, ucData[i]);
    }
}
