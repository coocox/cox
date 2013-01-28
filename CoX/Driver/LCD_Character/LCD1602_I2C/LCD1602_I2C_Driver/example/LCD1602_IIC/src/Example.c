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

#include "LCD1602IIC.h"

void LCD1602IICExample(void)
{
    unsigned long ulSysClk;
    unsigned char i=0;
    xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    xSysCtlDelay(10000);
    LCD1602Init(100000);
    ulSysClk = xSysCtlClockGet();
    LCD1602PrintString(0,0,"Back Light test!");
    xSysCtlDelay(ulSysClk/4);
    LCD1602BacklightOff();
    xSysCtlDelay(ulSysClk/4);
    LCD1602BacklightOn();
    LCD1602PrintString(1,5,"OK!");
    xSysCtlDelay(ulSysClk/4);
	
    LCD1602Clear();
    LCD1602PrintString(0,0,"IIC LCD1602 display test!");
    xSysCtlDelay(ulSysClk/2);
    LCD1602Clear();
	
    LCD1602PrintString(0,0,"LCD1602 Scroll  test!");
    LCD1602BlinkOn();
    while(i<16)
    {
        if(i<8)
        {
            LCD1602ScrollDisplayRight();
            xSysCtlDelay(ulSysClk/7);
            i++;
        }
        else
        {
            LCD1602ScrollDisplayLeft();
            xSysCtlDelay(ulSysClk/7);
            i++;
        }	
    }
    LCD1602Clear();
    LCD1602PrintString(0,0,"function test!");
    xSysCtlDelay(ulSysClk/4);
    LCD1602PrintString(1,3,"display off!");
    xSysCtlDelay(ulSysClk/4);
    LCD1602BlinkOff();
    LCD1602DisplayOff();
    xSysCtlDelay(ulSysClk/2);
    LCD1602DisplayOn();
    LCD1602CursorOff();
    LCD1602PrintString(1,11,"     ");
    LCD1602PrintString(1,3,"display on!");
}
