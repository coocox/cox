//*****************************************************************************
//
//! \file Example.c
//! \brief the LCD1602_I2C Example.
//! \version 1.0
//! \date 1/15/2013
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
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "hd44780.h"

//#include "LCD1602IIC.h"
//
void LCD1602IICExample(void)
{
	int i,j;
    xSysCtlClockSet(8000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);

	HD44780Init();
	HD44780Init();
	HD44780BackLightOn();
	HD44780DisplayClear();
	HD44780Home();


	//
	// Location Set & Display string, number Test
	//
	HD44780LocationSet(0, 0);
	HD44780DisplayString("Hello HD44780!");
	HD44780LocationSet(0, 1);
	HD44780DisplayString("Number:");
	HD44780DisplayN(10086);
	xSysCtlDelay(xSysCtlClockGet() / 4);
	HD44780LocationSet(0,1);
	HD44780DisplayString("Display off/on");
	xSysCtlDelay(xSysCtlClockGet() / 4);
	HD44780DisplayOff();
	xSysCtlDelay(xSysCtlClockGet() / 4 );
	HD44780DisplayOn();
	xSysCtlDelay(xSysCtlClockGet() / 4);
	//
	// Cursor style
	//
	HD44780DisplayClear();
	HD44780DisplayString("Cursor Test");
	HD44780CursorOn(xfalse);
	xSysCtlDelay(xSysCtlClockGet() / 4);
	HD44780CursorOff();
	xSysCtlDelay(xSysCtlClockGet() / 4);

	//
	// Cursor will blink at the end of line
	//
	HD44780CursorOn(xtrue);
	HD44780CursorRightMove(1);
	xSysCtlDelay(xSysCtlClockGet() / 4);
	HD44780CursorRightMove(5);
	xSysCtlDelay(xSysCtlClockGet() / 4);
	HD44780CursorLeftMove(4);
	xSysCtlDelay(xSysCtlClockGet() / 4);

	for(i = 0; i < 10; i++)
	{
		HD44780CursorRightMove(1);
		xSysCtlDelay(xSysCtlClockGet() / 10);
	}

	for(i = 0; i < 10; i++)
	{
		HD44780CursorLeftMove(1);
		xSysCtlDelay(xSysCtlClockGet() / 10);
	}

	HD44780LocationSet(0, 1);
	HD44780DisplayString("Cursor Home");
	xSysCtlDelay(xSysCtlClockGet() / 4);

	HD44780Home();

	//
	// Display Right shift
	//
	HD44780DisplayClear();
	HD44780DisplayString("Right scrolling string");
	HD44780LocationSet(0, 1);
	HD44780DisplayString("        Line 2         ");
	for(i = 0; i < 20; i++)
	{
		HD44780DisplayRightShift(1);
		xSysCtlDelay(xSysCtlClockGet() / 10);
	}

	//
	// Display Left shift
	//
	HD44780DisplayClear();
	HD44780DisplayString("Left scrolling string");
	HD44780LocationSet(0, 1);
	HD44780DisplayString("        Line 2         ");
	for(i = 0; i < 20; i++)
	{
		HD44780DisplayLeftShift(1);
		xSysCtlDelay(xSysCtlClockGet() / 10);
	}

	//
	// Display Right Left shift
	//
	HD44780DisplayClear();
	HD44780DisplayString("Left Right scrolling string");
	HD44780LocationSet(0, 1);
	HD44780DisplayString("        Line 2         ");
	for(j = 0; j < 2; j++)
	{
		for(i = 0; i < 10; i++)
		{
			HD44780DisplayRightShift(1);
			xSysCtlDelay(xSysCtlClockGet() / 10);
		}
		for(i = 0; i < 10; i++)
		{
			HD44780DisplayLeftShift(1);
			xSysCtlDelay(xSysCtlClockGet() / 10);
		}
	}
	HD44780Home();
	xSysCtlDelay(xSysCtlClockGet() / 4);

	//
	// Cursor Move Direction
	//
	HD44780DisplayClear();
	HD44780LocationSet(10, 1);
	xSysCtlDelay(xSysCtlClockGet() / 4);
	HD44780EntryModeSet(HD44780_MOVE_DIRECTION_DEC, xfalse);
	HD44780DisplayString("DEC");

	HD44780LocationSet(10, 2);
	xSysCtlDelay(xSysCtlClockGet() / 4);
	HD44780EntryModeSet(HD44780_MOVE_DIRECTION_DEC, xtrue);
	HD44780DisplayString("DEC shift");

	HD44780DisplayClear();
	HD44780LocationSet(10, 1);
	xSysCtlDelay(xSysCtlClockGet() / 4);
	HD44780EntryModeSet(HD44780_MOVE_DIRECTION_INC, xfalse);
	HD44780DisplayString("INC");

	HD44780LocationSet(10, 2);
	xSysCtlDelay(xSysCtlClockGet() / 4);
	HD44780EntryModeSet(HD44780_MOVE_DIRECTION_INC, xtrue);
	HD44780DisplayString("INC shift");
	xSysCtlDelay(xSysCtlClockGet() / 4);

	HD44780DisplayClear();
	HD44780EntryModeSet(HD44780_MOVE_DIRECTION_INC, xfalse);
	HD44780DisplayString("Complete");



}
