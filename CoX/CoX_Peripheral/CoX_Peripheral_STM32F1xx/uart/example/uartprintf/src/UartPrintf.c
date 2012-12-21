//*****************************************************************************
//
//! \file UartPrintf.c
//! \brief Using UART0 to print some data to terminal.
//! \version 1.0
//! \date 6/29/2012
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

unsigned char ucData[] = "STM32F1xx.UART Example of CoX \r\n";

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
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);

    xSysCtlDelay(10000);

    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOD);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

      xSPinTypeUART(UART1TX,PA9);
    

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);

    xUARTConfigSet(USART1_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                         UART_CONFIG_STOP_ONE | 
                                         UART_CONFIG_PAR_NONE));

    xUARTEnable(USART1_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));

    for(i = 0; i < sizeof("STM32F1xx.UART Example of CoX \r\n"); i++)
    {
        xUARTCharPut(USART1_BASE, ucData[i]);
    }
}
