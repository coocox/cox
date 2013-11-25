//*****************************************************************************
//
//! \file HC_SR04Example.c
//! \brief Example of using HC-SR04.
//! \version V2.1.1.0
//! \date 1/28/2013
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox
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
#include "stdio.h"
#include "HC_SR04.h"

void HCSR04Example(void)
{
	unsigned short usDist;

	xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);

	//
	// Initialize UART1 as printf output port
	//
	xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
	xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
	xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
	xUARTConfigSet(xUART1_BASE, 115200, (xUART_CONFIG_WLEN_8 |
			    						 xUART_CONFIG_STOP_1 |
			    						 xUART_CONFIG_PAR_NONE));
	xUARTEnable(xUART1_BASE, (xUART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX));
	xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
	xSPinTypeUART(UART1TX, PA9);

	HCSR04Init();

	while(1)
	{
		usDist = HCSR04GetDistance(UNIT_CM);
		printf("The distance is: %d cm\n\r", usDist);
		xSysCtlDelay(5000000);
	}
}
