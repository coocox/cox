//*****************************************************************************
//
//! \file 93LC46A.c
//! \brief the 93LC46A Driver.
//! \version V1.0.0.0
//! \date 12/28/2012
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

#include "xhw_memmap.h"
#include "xhw_types.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xgpio.h"
#include "93LC46A.h"

static void delay(int n)
{
    int i;
    for(i=0; i<n; i++);
}

//*****************************************************************************
//
//! \brief Write one byte to  93LC46A
//!
//! \param byte Specify the byte to write.
//!
//! \return None.
//
//*****************************************************************************
static void eep_93LC46A_WriteByte(char byte)
{
	int i;
	char bit;
	for(i=7; i>=0; i--)
	{
		bit = byte>>i;
		xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_CLOCK, 0);
		if(bit & 0x01)
			xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_DO, 1);
		else
			xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_DO, 0);
		delay(DELAY_TIME_1);
		xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_CLOCK, 1);
		delay(DELAY_TIME_1);
	}

}

//*****************************************************************************
//
//! \brief Wait until the end of writing.
//!
//! \return None.
//
//*****************************************************************************
static void eep_93LC46A_WaitForWriteEnd()
{
	unsigned char Status = 0;
	xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_CLOCK, 1);
	delay(DELAY_TIME_1);
	xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_CLOCK, 0);

	xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_SEL, 1);
	do
	{
		delay(DELAY_TIME_1);
		xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_CLOCK, 1);
		delay(DELAY_TIME_2);
//		Status = GPIOSPinRead(PB14);
		Status = (xGPIOPinRead(_93LC46A_PIN_PORT, _93LC46A_PIN_DI)? 1: 0);
		delay(DELAY_TIME_3);
		xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_CLOCK, 0);
	} while(Status == 0);
	xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_SEL, 0);
	delay(DELAY_TIME_1);
}

//*****************************************************************************
//
//! \brief Initialize 93LC46A.
//!
//! \return None.
//
//*****************************************************************************
void eep_93LC46A_Init()
{
	//
	// Clock and GPIO Configure
	//
	xSysCtlClockSet(8000000, xSYSCTL_XTAL_8MHZ | xSYSCTL_OSC_MAIN);
	xSysCtlPeripheralEnable(_93LC46A_PERIPH_PORT);

	xGPIODirModeSet(_93LC46A_PIN_PORT, _93LC46A_PIN_SEL, GPIO_DIR_MODE_OUT);
	xGPIODirModeSet(_93LC46A_PIN_PORT, _93LC46A_PIN_CLOCK, GPIO_DIR_MODE_OUT);
	xGPIODirModeSet(_93LC46A_PIN_PORT, _93LC46A_PIN_DI, GPIO_DIR_MODE_IN);
	xGPIODirModeSet(_93LC46A_PIN_PORT, _93LC46A_PIN_DO, GPIO_DIR_MODE_OUT);

	xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_SEL, 0);
	xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_CLOCK, 0);
	xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_DO, 0);

	//
	// Enable Write
	//
	eep_93LC46A_Cmd(_93LC46A_WriteEnable);
}

//*****************************************************************************
//
//! \brief Send command to  93LC46A
//!
//! \param cmd Specify the command to send. It can be one of
//! the following values:
//!
//! - \b _93LC46A_WriteEnable
//! - \b _93LC46A_WriteDisable
//! - \b _93LC46A_EraseAll
//!
//! \return None.
//
//*****************************************************************************
void eep_93LC46A_Cmd(short cmd)
{
	xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_SEL, 1);
	delay(DELAY_TIME_1);
	eep_93LC46A_WriteByte(cmd>>8);
	eep_93LC46A_WriteByte(cmd);
	xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_SEL, 0);
	delay(DELAY_TIME_1);

	//
	// If the command is "erase all", we need to check the
	// ready status.
	//
	if(cmd == _93LC46A_EraseAll)
	{
		eep_93LC46A_WaitForWriteEnd();
	}
}

//*****************************************************************************
//
//! \brief Write one byte to 93LC46A in the specific address.
//!
//! \param data Specify the byte to write.
//! \param addr Specify the address to write.
//!
//! \return None.
//
//*****************************************************************************
void eep_93LC46A_Write(const char data, char addr)
{
	xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_SEL, 1);
	delay(DELAY_TIME_1);

//	unsigned int op = 0x00028000 | (addr<<8) | data;
	unsigned int op;
	if(addr != (char)-1)
		op = ((_93LC46A_Write | addr)<<8) | data;
	else
		op = (_93LC46A_WriteAll<<8) | data;
	int i;
	char byte;
	for(i=2; i>=0; i--)
	{
		byte = op>>(i*8) & 0xff;
		eep_93LC46A_WriteByte(byte);
	}

	xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_SEL, 0);
	delay(DELAY_TIME_1);

	eep_93LC46A_WaitForWriteEnd();
}

//*****************************************************************************
//
//! \brief Read one byte from 93LC46A in the specific address.
//!
//! \param *data Specify the byte to read.
//! \param addr Specify the address to read.
//!
//! \return None.
//
//*****************************************************************************
void eep_93LC46A_Read(char* data, unsigned char addr)
{
	xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_SEL, 1);
	delay(DELAY_TIME_1);

	short op = _93LC46A_Read | addr;
	int i;
	char byte;
	for(i=1; i>=0; i--)
	{
		byte = op>>(i*8) & 0xff;
		eep_93LC46A_WriteByte(byte);
	}

	unsigned char bit;
	byte = 0;
	for(i=7; i>=0; i--)
	{
		xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_CLOCK, 0);
		delay(DELAY_TIME_1);
		xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_CLOCK, 1);
		delay(DELAY_TIME_2);
//		bit = GPIOSPinRead(PB14);
		bit =  (xGPIOPinRead(_93LC46A_PIN_PORT, _93LC46A_PIN_DI)? 1: 0);
		delay(DELAY_TIME_3);
		byte = byte | (bit<<i);
	}
	*data = byte;

	xGPIOPinWrite(_93LC46A_PIN_PORT, _93LC46A_PIN_SEL, 0);
	delay(DELAY_TIME_1);
}

//*****************************************************************************
//
//! \brief Erase one byte of 93LC46A in the specific address.
//!
//! \param addr Specify the address to erase.
//!
//! \return None.
//
//*****************************************************************************
void eep_93LC46A_Erase(unsigned char addr)
{
	short cmd = _93LC46A_Erase | addr;
	eep_93LC46A_Cmd(cmd);
	eep_93LC46A_WaitForWriteEnd();
}
