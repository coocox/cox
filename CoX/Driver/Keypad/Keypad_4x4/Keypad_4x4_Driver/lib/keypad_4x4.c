//*****************************************************************************
//
//! \file hd44780.c
//! \brief Driver for Character LCD HD44780.
//! \version 2.1.1.0
//! \date 10/18/2011
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
//
//*****************************************************************************

#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "keypad_4x4.h"

//*****************************************************************************
//
//! \brief Configure the pad pin 0~3 as output, pad pin 4~7 as input.
//!
//! \return None.
//
//*****************************************************************************
void 
Keypad4x4Init(void)
{

	//
	// Enable the corresponding pin port
	//
	xSysCtlPeripheralEnable2(xGPIOSPinToPort(KEYPAD_PIN_0));
	xSysCtlPeripheralEnable2(xGPIOSPinToPort(KEYPAD_PIN_1));
	xSysCtlPeripheralEnable2(xGPIOSPinToPort(KEYPAD_PIN_2));
	xSysCtlPeripheralEnable2(xGPIOSPinToPort(KEYPAD_PIN_3));
	xSysCtlPeripheralEnable2(xGPIOSPinToPort(KEYPAD_PIN_4));
	xSysCtlPeripheralEnable2(xGPIOSPinToPort(KEYPAD_PIN_5));
	xSysCtlPeripheralEnable2(xGPIOSPinToPort(KEYPAD_PIN_6));
	xSysCtlPeripheralEnable2(xGPIOSPinToPort(KEYPAD_PIN_7));

	//
	// Configure pad pin 0~3 as output, set high
	//
	xGPIOSPinTypeGPIOOutput(KEYPAD_PIN_0);
	xGPIOSPinWrite(KEYPAD_PIN_0, 1);
	xGPIOSPinTypeGPIOOutput(KEYPAD_PIN_1);
	xGPIOSPinWrite(KEYPAD_PIN_1, 1);
	xGPIOSPinTypeGPIOOutput(KEYPAD_PIN_2);
	xGPIOSPinWrite(KEYPAD_PIN_2, 1);
	xGPIOSPinTypeGPIOOutput(KEYPAD_PIN_3);
	xGPIOSPinWrite(KEYPAD_PIN_3, 1);

    //
	// Before set the pin 4~7 as input, set them output with 0 first, otherwise
	// the input float data will not sure.
	//

	//
	// Configure pad pin 4~7 as input
	//
	xGPIOSPinTypeGPIOInput(KEYPAD_PIN_4);
	xGPIOSPinTypeGPIOInput(KEYPAD_PIN_5);
	xGPIOSPinTypeGPIOInput(KEYPAD_PIN_6);
	xGPIOSPinTypeGPIOInput(KEYPAD_PIN_7);

}

//*****************************************************************************
//
//! \brief Scan the keypad, Get the number of which pad has beed pressed.
//!
//! \return The number of pressed keypad.
//
//*****************************************************************************
unsigned char
Keypad4x4Scan(void)
{
	unsigned char ucPadIn = 0, ucPadPress = 0;
    unsigned char ucPadData = 0;

	Keypad4x4Pad03Wirte(0x01);
	ucPadIn = Keypad4x4Pad47Read();
	ucPadData = ucPadIn | (0x01 << 4);
	switch(ucPadData)
	{
        case 0x10:
        	break;
	    case 0x11:
	    	ucPadPress = 13;
	    	break;
	    case 0x12:
	    	ucPadPress = 14;
	    	break;
	    case 0x14:
	    	ucPadPress = 15;
	    	break;
	    case 0x18:
	    	ucPadPress = 16;
	    	break;
	}

	Keypad4x4Pad03Wirte(0x02);
	ucPadIn = Keypad4x4Pad47Read();
	ucPadData = ucPadIn | (0x02 << 4);
	switch(ucPadData)
	{
        case 0x20:
        	break;
	    case 0x21:
	    	ucPadPress = 9;
	    	break;
	    case 0x22:
	    	ucPadPress = 10;
	    	break;
	    case 0x24:
	    	ucPadPress = 11;
	    	break;
	    case 0x28:
	    	ucPadPress = 12;
	    	break;
	}

	Keypad4x4Pad03Wirte(0x04);
	ucPadIn = Keypad4x4Pad47Read();
	ucPadData = ucPadIn | (0x04 << 4);
	switch(ucPadData)
	{
        case 0x40:
        	break;
	    case 0x41:
	    	ucPadPress = 5;
	    	break;
	    case 0x42:
	    	ucPadPress = 6;
	    	break;
	    case 0x44:
	    	ucPadPress = 7;
	    	break;
	    case 0x48:
	    	ucPadPress = 8;
	    	break;
	}

	Keypad4x4Pad03Wirte(0x08);
	ucPadIn = Keypad4x4Pad47Read();
	ucPadData = ucPadIn | (0x08 << 4);
	switch(ucPadData)
	{
        case 0x80:
        	break;
	    case 0x81:
	    	ucPadPress = 1;
	    	break;
	    case 0x82:
	    	ucPadPress = 2;
	    	break;
	    case 0x84:
	    	ucPadPress = 3;
	    	break;
	    case 0x88:
	    	ucPadPress = 4;
	    	break;
	}

	return ucPadPress;
}

//*****************************************************************************
//
//! \brief Write the data to the pad 0~3.
//!
//! \param The data wirte to the pad 0~3.which should be Ox0e, 0x0d, 0x0b, 0x07
//!
//! \return None.
//
//*****************************************************************************
void
Keypad4x4Pad03Wirte(unsigned char ucPadData)
{
    unsigned char ucBit = 0;

    ucBit = (ucPadData >> 0) & 0x01;
    xGPIOSPinWrite(KEYPAD_PIN_0, ucBit);
    ucBit = (ucPadData >> 1) & 0x01;
    xGPIOSPinWrite(KEYPAD_PIN_1, ucBit);
    ucBit = (ucPadData >> 2) & 0x01;
    xGPIOSPinWrite(KEYPAD_PIN_2, ucBit);
    ucBit = (ucPadData >> 3) & 0x01;
    xGPIOSPinWrite(KEYPAD_PIN_3, ucBit);

}

//*****************************************************************************
//
//! \brief Read the data to the pad 4~7.
//!
//! \return None.
//
//*****************************************************************************
unsigned char
Keypad4x4Pad47Read(void)
{
    unsigned char ucData = 0, ucBit = 0;

	xGPIOSPinTypeGPIOOutput(KEYPAD_PIN_4);
	xGPIOSPinWrite(KEYPAD_PIN_4, 0);
	xGPIOSPinTypeGPIOInput(KEYPAD_PIN_4);
	ucBit = xGPIOSPinRead(KEYPAD_PIN_4);
	ucData = ucData | (ucBit << 0);

	xGPIOSPinTypeGPIOOutput(KEYPAD_PIN_5);
	xGPIOSPinWrite(KEYPAD_PIN_5, 0);
	xGPIOSPinTypeGPIOInput(KEYPAD_PIN_5);
	ucBit = xGPIOSPinRead(KEYPAD_PIN_5);
	ucData = ucData | (ucBit << 1);

	xGPIOSPinTypeGPIOOutput(KEYPAD_PIN_6);
	xGPIOSPinWrite(KEYPAD_PIN_6, 0);
	xGPIOSPinTypeGPIOInput(KEYPAD_PIN_6);
	ucBit = xGPIOSPinRead(KEYPAD_PIN_6);
	ucData = ucData | (ucBit << 2);

	xGPIOSPinTypeGPIOOutput(KEYPAD_PIN_7);
	xGPIOSPinWrite(KEYPAD_PIN_7, 0);
	xGPIOSPinTypeGPIOInput(KEYPAD_PIN_7);
	ucBit = xGPIOSPinRead(KEYPAD_PIN_7);
	ucData = ucData | (ucBit << 3);
	return ucData;
}


