//*****************************************************************************
//
//! \file BMP085Example.c
//! \brief Example file to demostrate how to use BMP085.
//! \version 0.0.1
//! \date 4/23/2013
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
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_uart.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xuart.h"
#include "stdio.h"
#include "BMP085.h"

//*****************************************************************************
//
//! \brief BMP085 Example.
//!
//! \param None
//!
//! This function gives an example of how to use BMP085 driver in your application
//! The function print temperature, pressure and altitude value to UART1.
//!
//! \return None.
//
//*****************************************************************************
void BMP085Exam(void)
{
	int a1,a2,a3;

	//  System clock initialization
	xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
	xSysCtlDelay(10000);

	// Configure the UART1 as print port
	xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
	xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
	xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
	xUARTConfigSet(xUART1_BASE, 115200, (xUART_CONFIG_WLEN_8 |
										 xUART_CONFIG_STOP_1 |
										 xUART_CONFIG_PAR_NONE));
	xUARTEnable(xUART1_BASE, (xUART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX));
	xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
	xSPinTypeUART(UART1TX, PA9);

	//  BMP085 initialization
	BMP085Init(400000);
	while(1)
	{
		a1=BMP085GetTemperature();
		a2=BMP085GetPressure(BMP085_OSS_0);
		a3=BMP085GetAltitude();
		printf("-------------------------------\n\r");
		printf("Temperature: %d.%d\n\r", a1/10, a1%10);
		printf("Barometric pressure: %d Pa\n\r", a2);
		printf("Approximate altitude: %d m\n\r", a3);
		xSysCtlDelay(1000000);
	}
}
