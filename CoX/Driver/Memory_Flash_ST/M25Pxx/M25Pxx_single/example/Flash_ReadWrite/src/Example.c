//*****************************************************************************
//
//! \file Example.c
//! \brief the M25Pxx Example.
//! \version 1.0
//! \date 10/15/2011
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
#include "M25Pxx.h"
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
unsigned char ucWriteData[];
//
//! Get the Length of data will be oparated
//
#define Length 256

unsigned char ucReadData[Length];


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
    xSPinTypeUART(UART0RX,PB0);
    xSPinTypeUART(UART0TX,PB1);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    
    xSysCtlPeripheralClockSourceSet(xSYSCTL_UART0_MAIN, 1);

    xUARTConfigSet(UART0_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                        UART_CONFIG_STOP_ONE | 
                                        UART_CONFIG_PAR_NONE));
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
    while(!xUARTSpaceAvail(xUART0_BASE));
    
    //
    // Write this character to the transmit FIFO.
    //
    xUARTCharPut(xUART0_BASE, c);
}

//*****************************************************************************
//
//! \brief Prints a decimal unsigned number.
//!
//! \param n is the number to be printed
//!
//! \details Prints a decimal unsigned number.
//!
//! \return None.
//
//*****************************************************************************
static 
void UartPrintfNumber(unsigned long n)
{
    char buf[16], *p;

    if (n == 0)
    {
        UartPrintfChar('0');
    }
    else
    {
        p = buf;
        while (n != 0)
        {
            *p++ = (n % 10) + '0';
            n /= 10;
        }

        while (p > buf)
            UartPrintfChar(*--p);
    }
}

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
void M25PxxReadWrite(void)
{
    unsigned long i;
    unsigned short ulID; 
    //
    // Set SysClk 50MHz using Extern 12M oscillator
    //
    xSysCtlClockSet(50000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    UartInit(); 
    M25PxxInit(10000000);
    
    ulID = M25PxxIDcodeGet();
    i = ulID;
    UartPrintfNumber(ulID);
    UartPrintfChar('\n');
    UartPrintfChar('\r');
    
    for(i = 0; i < Length; i++)
    {
        ucWriteData[i] = i;      
    }

    //
    // Erase all chip
    //
    M25PxxChipErase();
    //
    // write data to W25Xxx
    //
    M25PxxWrite(ucWriteData, 100, Length);
    SysCtlDelay(50000000);
    M25PxxDataRead(ucReadData, 100, Length);
    for(i = 0; i < Length; i++)
    {
        UartPrintfChar(ucReadData[i]);      
    }
}