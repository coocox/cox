//*****************************************************************************
//
//! \file Example.c
//! \brief the uc1601 Example.
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
#include "uc1601.h"
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

/*  ÐÂÄê¿ìÀÖ(16x16,Z)*/
char HZ[]={
0x20,0x24,0x2C,0x35,0xE6,0x34,0x2C,0x24,0x00,0xFC,0x24,0x24,0xE2,0x22,0x22,0x00,
0x21,0x11,0x4D,0x81,0x7F,0x05,0x59,0x21,0x18,0x07,0x00,0x00,0xFF,0x00,0x00,0x00,
0x40,0x20,0x10,0x0C,0xE3,0x22,0x22,0x22,0xFE,0x22,0x22,0x22,0x22,0x02,0x00,0x00,
0x04,0x04,0x04,0x04,0x07,0x04,0x04,0x04,0xFF,0x04,0x04,0x04,0x04,0x04,0x04,0x00,
0x70,0x00,0xFF,0x08,0xB0,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0xF8,0x80,0x80,0x00,
0x00,0x00,0xFF,0x00,0x80,0x40,0x30,0x0E,0x01,0x06,0x08,0x30,0x60,0xC0,0x40,0x00,
0x00,0x00,0x40,0xFC,0x44,0x44,0x44,0x46,0xFA,0x42,0x43,0x43,0x42,0x40,0x00,0x00,
0x00,0x20,0x18,0x0C,0x07,0x12,0x20,0x40,0x3F,0x00,0x00,0x02,0x0C,0x38,0x10,0x00};

//*****************************************************************************
//
//! \brief The example of the function of Dispaly.
//!
//! \param None
//!
//! \details The example of the function of Dispaly.
//! \return None.
//
//*****************************************************************************
void UC1601DispalyExample(void)
{
    //
    // Set SysClk 50MHz using Extern 12M oscillator
    //
    xSysCtlClockSet(50000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    UC1601Init(1500000);
    UC1601Clear();
    UC1601CharDispaly(0, 0, "I love google?");
    UC1601CharDispaly(1, 0, "Yes,I love!");
    UC1601ChineseDispaly(3, 0, 4, (char *)&HZ);
    HD44780DisplayN(2,0,5201314);
    xSysCtlDelay(1000000);
}