//*****************************************************************************
//
//! \file touch.c
//! \brief the Touch Driver.
//! \version V2.1.1.0
//! \date 7/5/2012
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
#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xgpio.h"
#include "touch.h"

xtBoolean TouchDetect = xfalse;

//*****************************************************************************
//! \breif External interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long TouchIntCallback(void *pvCBData, unsigned long ulEvent,
                        unsigned long ulMsgParam,void *pvMsgData)
{
    //
    // add you code
    //
    return 0;
}

//*****************************************************************************
//
//! \brief Initialize touch GPIO.  
//!
//! \param None
//! 
//! \return None.
//
//*****************************************************************************
void CapTouchInit(void)
{
    //
    // Enable the GPIO which is connected with Capacitive Touch.
    //  
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(CAP_TOUCH_PIN));
    
    //
    // Set INT pin.
    //  
    xGPIOSPinTypeGPIOInput(CAP_TOUCH_PIN);

    //
    // Set GPIO pin interrupt callback.
    //
    //xGPIOPinIntCallbackInit(CAP_TOUCH_PORT, CAP_TOUCH_PinNum, TouchIntCallback);
    
    //
    //  Enable GPIO pin interrupt.
    //
    //xGPIOPinIntEnable(CAP_TOUCH_PORT, CAP_TOUCH_PinNum, xGPIO_RISING_EDGE);  
    //xIntEnable(INT_GPIO);
   
    //
    // Delay for 0.5 sec
    // 
    xSysCtlDelay(xSysCtlClockGet()/4);   
}

//*****************************************************************************
//
//! \brief read data from touch controller.
//!
//! \param ucReg Register to be read.
//! \param ucNum number of bytes to read.
//! \param pucBuffer specifies the location data which will be store.
//!
//! This function is to read data from touchscreen register.
//!
//! \return None.
//
//*****************************************************************************
unsigned char
CapTouchRead(void)
{
   return xGPIOSPinRead(CAP_TOUCH_PIN); 
}