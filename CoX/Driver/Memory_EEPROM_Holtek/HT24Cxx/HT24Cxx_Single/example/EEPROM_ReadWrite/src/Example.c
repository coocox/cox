//*****************************************************************************
//
//! \file Example.c
//! \brief the M24Cxx Example.
//! \version 1.0
//! \date 6/15/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox 
//! All rights reserved.
//! 
//! Redistribution and use in source and binary forms, with or without 
//! modification, are permitted provided that the following conditions 
//! are met: 
//! 
//!     * Redistributions of source code must retain the above copyright 
//! notice, this list of conditions and the following disclaimer. 
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution. 
//!     * Neither the name of the <ORGANIZATION> nor the names of its 
//! contributors may be used to endorse or promote products derived 
//! from this software without specific prior written permission. 
//! 
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
//! THE POSSIBILITY OF SUCH DAMAGE.
//*****************************************************************************
#include "HT24Cxx.h"
#include "hw_HT24Cxx.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xhw_types.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_uart.h"
#include "xuart.h"
unsigned char ucWriteData[]="STM32F107 M24Cxx Example";
//
//! Get the Length of data will be oparated
//
#define Length                 32
#define WriteAddress           0x20

unsigned char ucReadData[Length];

static void UartInit(void);
void UartPrintfChar(char ch);

//*****************************************************************************
//
//! \brief The example of the function of read and write.
//!
//! \param None
//!
//! \details The example of the function of read and write.
//! \return None.
//
//*****************************************************************************
void M24CxxReadWrite(void)
{

    unsigned long i;

    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    UartInit();
    HT24CxxInit();

    UartPrintfChar('\r');
    UartPrintfChar('\n');
    //
    // write data to M24Cxx
    //
    HT24CxxBufferWrite(ucWriteData, WriteAddress, Length);
    //
    // Read data from M24Cxx
    //
    HT24CxxBufferRead(ucReadData, WriteAddress, Length);

    for(i = 0; i < Length; i++)
    {
        UartPrintfChar(ucReadData[i]);
    }
}

//*****************************************************************************
//
//! \brief Init uart to print.
//!
//! \param None
//!
//! \details uart config as (115200, 8 data bit, 1 stop bit , no partiy)
//!
//! \return None.
//
//*****************************************************************************
static 
void UartInit(void)
{

    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

    xSPinTypeUART(UART0RX, PC10);
    xSPinTypeUART(UART0TX, PC8);
    

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    //
    // Set UART0 clock source.
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_HCLK);

    //
    // Configure 8 bit word length, 1 stop bit,
    // and none parity bit, receive FIFO 1 byte.
    //
    xUARTConfigSet(UART0_BASE, 115200, (xUART_CONFIG_WLEN_8 |
                                        xUART_CONFIG_STOP_1 |
                                        xUART_CONFIG_PAR_NONE));

    xUARTEnable(UART0_BASE, (UART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX));
}

//*****************************************************************************
//
//! \brief print a char.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void 
UartPrintfChar(char ch)
{
   
    unsigned char c;
    c = ch;
    
    //
    // Write this character to the transmit FIFO.
    //
    xUARTCharPut(UART0_BASE, c);
}

