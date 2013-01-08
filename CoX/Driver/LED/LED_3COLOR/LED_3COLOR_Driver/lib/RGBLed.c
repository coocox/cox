//*****************************************************************************
//
//! \file RGBLed.c
//! \brief source file of Driver for RGB Led
//! \version 1.0.0.0
//! \date 12/28/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox All rights reserved.
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
#include "xcore.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "RGBLed.h"

//*****************************************************************************
//
//! \brief Initialize RGB Led.
//!
//! \return None.
//
//*****************************************************************************
void rgbled_init()
{
    xSysCtlPeripheralEnable2(RGBLED_PIN_PORT);
    xGPIODirModeSet(RGBLED_PIN_PORT,
            RGBLED_PIN_R | RGBLED_PIN_G | RGBLED_PIN_B,
                xGPIO_DIR_MODE_OUT);
}

//*****************************************************************************
//
//! \brief Turn on the specific RGB Led(s).
//!
//! \param num the num of led, it can be any combination of RGBLED_R,
//!  RGBLED_G, RGBLED_B.
//!
//! \return None.
//
//*****************************************************************************
void rgbled_turnOn(char num)
{
    if(num & 1)
        xGPIOPinWrite(RGBLED_PIN_PORT, RGBLED_PIN_R, 0);
    if(num & 2)
        xGPIOPinWrite(RGBLED_PIN_PORT, RGBLED_PIN_G, 0);
    if(num & 4)
        xGPIOPinWrite(RGBLED_PIN_PORT, RGBLED_PIN_G, 0);
}

//*****************************************************************************
//
//! \brief Turn off the specific RGB Led(s).
//!
//! \param num the num of led, it can be any combination of RGBLED_R,
//!  RGBLED_G, RGBLED_B.
//!
//! \return None.
//
//*****************************************************************************
void rgbled_turnOff(char num)
{
    if(num & 1)
        xGPIOPinWrite(RGBLED_PIN_PORT, RGBLED_PIN_R, 1);
    if(num & 2)
        xGPIOPinWrite(RGBLED_PIN_PORT, RGBLED_PIN_G, 1);
    if(num & 4)
        xGPIOPinWrite(RGBLED_PIN_PORT, RGBLED_PIN_G, 1);
}
