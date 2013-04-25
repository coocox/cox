//*****************************************************************************
//
//! \file Bluetooth_SD_Example.c
//! \brief Example for TL0026 Arduino Bluetooth Bee usage.
//! \version V1.0.0.0
//! \date 3/5/2013
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
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_gpio.h"
#include "xhw_nvic.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xuart.h"
#include "xgpio.h"
#include "hw_TEL0026.h"
#include "TEL0026.h"
#include "hw_sdcard.h"
#include "sdcard.h"

#define CMD_DELAY   1000000
//*****************************************************************************
//
//! \brief Debug information output UART1 port initialization
//
//! \param ulBaudRate The baud rate of UART.
//
// This function is to get initialized for debug information output UART1
//
//! \return None.
//
//*****************************************************************************
void DebugUartInit(unsigned long ulBaudRate)
{
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(PA9));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(PA10));

	xSysCtlPeripheralEnable2(xUART1_BASE);

    xUARTConfigSet(xUART1_BASE, ulBaudRate, (xUART_CONFIG_WLEN_8 |
                   xUART_CONFIG_STOP_1 |
                   xUART_CONFIG_PAR_NONE));
    xUARTEnable(xUART1_BASE, (xUART_BLOCK_UART | xUART_BLOCK_TX | xUART_BLOCK_RX));
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xSPinTypeUART(UART1TX, PA9);
}

//*****************************************************************************
//
//! \brief Debug string output
//
//! \param pStr The string to display
//
// This function is to print string through UART
//
//! \return None.
//
//*****************************************************************************
void DebugUartPrintStr(char *pStr)
{
	while(*pStr != 0)
	{
	    xUARTCharPut(xUART1_BASE, *pStr++);
	}
}

//*****************************************************************************
//
//! \brief Debug data output
//
//! \param ulLength Specifies how many data bytes to put
//! \param pData The data buffer to display
//
// This function is to print string through UART
//
//! \return None.
//
//*****************************************************************************
void DebugUartPutData(unsigned long ulLength, unsigned char *pData)
{
	while(ulLength--)
	{
	    xUARTCharPut(xUART1_BASE, *pData++);
	}
}

#define EXAM_BUFFER_SIZE    128
//
// Data buffer
//
char Buffer[EXAM_BUFFER_SIZE];

//*****************************************************************************
//
//! \brief Bluetooth SD example
//
//! \param None
//
// This example will do the following things:
//    Initialize TEL0026 bluetooth module and get its configuration parameter.
// Then it will search for nearby bluetooth devices and connect to recently
// connected device like a PC or another bluetooth module. After connected, a
// wireless serial connection is set up. PC or another bluetooth module can
// send commands to do something like getting csd,cid register of the SD card
// or more other things which can be added to the program.
//    If SD card initialization fail, the bluetooth will enter slave mode and
// wait for connecting by other master bluetooth devices.
//
//! \return None.
//
//*****************************************************************************
void BTSDExample(void)
{
	xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
	DebugUartInit(115200);
	BTInit();

	BTUartParamGet(Buffer);
	DebugUartPrintStr("\r\nTEL0026 UART parameter:");
	DebugUartPrintStr(Buffer);

	if(BTUartParamSet(115200,0,0) != BT_ERR_OK)
	{
		DebugUartPrintStr("\r\nTEL0026 UART parameter set failed!\r\n");
	}
	else
	{
		DebugUartPrintStr("\r\nTEL0026 UART parameter set success!\r\n");
	}

	DebugUartPrintStr("\r\nTEL0026 Bluetooth Name: ");
	BTDeviceNameGet(Buffer);
	DebugUartPrintStr(Buffer);

	DebugUartPrintStr("\r\nTEL0026 Bluetooth Address: ");
	BTDeviceAddrGet(Buffer);
	DebugUartPrintStr(Buffer);

	DebugUartPrintStr("\r\nTEL0026 Bluetooth Password: ");
	BTPasswordGet(Buffer);
	DebugUartPrintStr(Buffer);

	DebugUartPrintStr("\r\nTEL0026 Bluetooth SoftWare Version: ");
	BTVersionGet(Buffer);
	DebugUartPrintStr(Buffer);

	DebugUartPrintStr("\r\nConnect to BT:...");
	//if(BTDeviceConnect("12,2,107597")==BT_ERR_OK)
	if(BTAutoConnect() == BT_ERR_OK)
	{
		DebugUartPrintStr("\r\nConnected.");

		if(SDInit()!=SD_NO_ERR)
		{
			DebugUartPrintStr("\r\nSD card initialize failed.\r\n");
			return;
		}

		while(1)
		{
			Buffer[0] = 0;
			if(BTReadLine(Buffer)!=0)
			{
				if(!StrCmp(Buffer, "get cid reg"))
				{
					DebugUartPrintStr("\r\nReading SD card CID register:\r\n");
					SDCIDRead(128, Buffer);
					DebugUartPutData(128, Buffer);
				}
				if(!StrCmp(Buffer, "get csd reg"))
				{
					DebugUartPrintStr("\r\nReading SD card CID register:\r\n");
					SDCSDRead(128, Buffer);
					DebugUartPutData(128, Buffer);
				}
				if(!StrCmp(Buffer, "get ocr reg"))
				{
					DebugUartPrintStr("\r\nReading SD card OCR register:\r\n");
					SDOCRRead(32, Buffer);
					DebugUartPutData(32, Buffer);
				}
			}
		}
	}

	else
	{
		DebugUartPrintStr("\r\nConnection Failed.");
	}

	//
	// Set Bluetooth to slave mode and wait for connection.
	//
	BTDeviceRoleSet(BT_ROLE_SLAVE);
	xSysCtlDelay(1000000);
	BTWaitForConnect();
}



