//*****************************************************************************
//
//! \file ReadAccData.c
//! \brief Show how to read accelerometer data.
//! \version V2.1.1.0
//! \date 4/1/2013
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

#include <stdio.h>

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
#include "xhw_i2c.h"
#include "xi2c.h"
#include "xuart.h"
#include "PCF8574.h"

#define TICK_S 0xFFFFF
#define TICK_L 0x2FFFFF

//*****************************************************************************
//
//! Internal Function (Used in this file only!)
//
//*****************************************************************************

static void SysInit(void);

void ReadWritePort(void)
{
    uint8_t PortVal = 0;
    Result retv = SUCCESS;

    //Initialize the system clock
    SysInit();
    
    retv = PCF8574_Init();
    if(retv != SUCCESS)
    {
        return;
    }

    /**
     * Write Port Example
     */
    //Configure bit IO mode
    //Write 1: output
    //Write 0: input
    //Here, we set
    // -------------------------
    // |   Pin     Mode        |
    // |-----------------------|
    // |   PIO_7 | INPUT       |
    // |   PIO_6 | INPUT       |
    // |   PIO_5 | INPUT       |
    // |   PIO_4 | INPUT       |
    // |   PIO_3 | OUTPUT      |
    // |   PIO_2 | OUTPUT      |
    // |   PIO_1 | OUTPUT      |
    // |   PIO_0 | OUTPUT      |
    // -------------------------
    retv = PCF8574_WriteByte(0x0F);
    if(retv != SUCCESS)
    {
        return;
    }

    //Now, you can write value to the special bits(0..3)
    //PIO_0 0
    //PIO_1 1
    //PIO_2 0
    //PIO_3 1
    retv = PCF8574_WriteByte(0x0A);
    if(retv != SUCCESS)
    {
        return;
    }

    //Now, you can read value from the special bits(4..7)
    retv = PCF8574_ReadByte(&PortVal);
    if(retv != SUCCESS)
    {
        return;
    }

    //Also, you can use Function: WriteBits/ReadBits
    //to write/read special bits.

    //Read bit 7 value
    retv = PCF8574_ReadBits(0x80, &PortVal);
    if(retv != SUCCESS)
    {
        return;
    }


    //Set Bit 2, 3 to high
    retv = PCF8574_WriteBits(0x0C, 0xFF);
    if(retv != SUCCESS)
    {
        return;
    }

    return;
}

////////////////////////////////////////////////////////////////////////////////
static void SysInit(void)
{
    xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    SysCtlDelay(10000);
}

