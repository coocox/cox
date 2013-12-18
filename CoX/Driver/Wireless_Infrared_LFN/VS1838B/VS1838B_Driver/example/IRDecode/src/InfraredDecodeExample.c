//*****************************************************************************
//
//! \file InfraredDecodeExample
//! \brief Example of VS1838B decode.
//! \version V0.0.0.1
//! \date 2/27/2013
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2013, CooCox
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
#include "xhw_types.h"
#include "xcore.h"
#include "xhw_gpio.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xuart.h"
#include "xgpio.h"
#include "xsysctl.h"
#include "infrared.h"

//*****************************************************************************
//
//! \brief UART1 initialize.
//!
//! \param sulBaudRate is the BaudRate of UART1
//!
//! \details UART1 initialize.
//!
//! \return None.
//
//*****************************************************************************
void MyUartInit(unsigned long ulBaudRate)
{
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
    xUARTConfigSet(xUART1_BASE, ulBaudRate, (xUART_CONFIG_WLEN_8 |
                   xUART_CONFIG_STOP_1 |
                   xUART_CONFIG_PAR_NONE));

    xUARTEnable(xUART1_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xSPinTypeUART(UART1TX, PA9);
}

//*****************************************************************************
//
//! \brief Print string through UART1.
//!
//! \param str is the string to be printed
//!
//! \details Print string through UART1.
//!
//! \return None.
//
//*****************************************************************************
static void xUARTPutString(char *str)
{
    char *s = str;
    while(*s != 0)
    {
        xUARTCharPut(xUART1_BASE, *s++);
    }
}

//*****************************************************************************
//
//! \brief Print hex number through UART1.
//!
//! \param ucHex is the hex byte to be printed
//!
//! \details Print hex number through UART1.
//!
//! \return None.
//
//*****************************************************************************
static void UartPrintHex(unsigned char ucHex)
{
	unsigned char tmp;
	xUARTCharPut(xUART1_BASE, '0');
	xUARTCharPut(xUART1_BASE, 'x');
	tmp = ucHex >> 4;
	if(tmp<10)
	{
		tmp += '0';
	}
	else
	{
		tmp += 'A' - 10;
	}
	xUARTCharPut(xUART1_BASE, tmp);
	tmp = ucHex & 0x0F;
	if(tmp<10)
	{
		tmp += '0';
	}
	else
	{
		tmp += 'A' - 10;
	}
	xUARTCharPut(xUART1_BASE, tmp);
}

//*****************************************************************************
//
//! \brief Infrared remote controller decode test function.
//!
//! \param None
//!
//! \details Print hex number through UART1.
//!
//! \return None.
//
//*****************************************************************************
void IRDecodeExample(void)
{
	unsigned char ucData[2] = {0};

	xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);

	MyUartInit(115200);

	IRInit();

	xUARTPutString("Infrared remote controller decode test\n\r");
	while(1)
	{
		*(unsigned short *)ucData = IRKeyValueGet();
		if(ucData[0]!=0)
		{
			xUARTPutString("User code is:  ");
			UartPrintHex(ucData[1]);
			xUARTPutString("\t");
			xUARTPutString("The decode data is:  ");
			UartPrintHex(ucData[0]);
			xUARTPutString("\n\r");
		}
		xSysCtlDelay(10000);
	}
}
