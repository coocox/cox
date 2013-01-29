//*****************************************************************************
//
//! \file Joystick.c
//! \brief basic driver for Joystick
//!
//! \version V1.0.0
//! \date 1/23/2013
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2012, CooCoX All rights reserved.
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
#include "xhw_nvic.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "Joystick.h"

//*****************************************************************************
//
//! \brief joystick interface initialization.
//!
//! \param None.
//!
//! This function is to initialize joystick interface.
//!
//! \return None.
//
//*****************************************************************************
void JoystickInit(void)
{
	//
	// Enable peripheral clock
	//
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(JOYSTICK_PIN_SELECT));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(JOYSTICK_PIN_UP));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(JOYSTICK_PIN_DOWN));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(JOYSTICK_PIN_LEFT));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(JOYSTICK_PIN_RIGHT));
	//
	// Set pin's I/O direction
	//
	xGPIOSPinDirModeSet(JOYSTICK_PIN_SELECT, xGPIO_DIR_MODE_IN);
	xGPIOSPinDirModeSet(JOYSTICK_PIN_UP, xGPIO_DIR_MODE_IN);
	xGPIOSPinDirModeSet(JOYSTICK_PIN_DOWN, xGPIO_DIR_MODE_IN);
	xGPIOSPinDirModeSet(JOYSTICK_PIN_LEFT, xGPIO_DIR_MODE_IN);
	xGPIOSPinDirModeSet(JOYSTICK_PIN_RIGHT, xGPIO_DIR_MODE_IN);

#if(JOYSTICK_KEY_EFFECTIVE_LEVEL==1)
	//
	// Input pin pull down
	//
	xGPIOSPinWrite( JOYSTICK_PIN_SELECT, 0 );
	xGPIOSPinWrite( JOYSTICK_PIN_UP, 0 );
	xGPIOSPinWrite( JOYSTICK_PIN_DOWN, 0 );
	xGPIOSPinWrite( JOYSTICK_PIN_LEFT, 0 );
	xGPIOSPinWrite( JOYSTICK_PIN_RIGHT, 0 );
#else
	//
	// Input pin pull up
	//
	xGPIOSPinWrite( JOYSTICK_PIN_SELECT, 1 );
	xGPIOSPinWrite( JOYSTICK_PIN_UP, 1 );
	xGPIOSPinWrite( JOYSTICK_PIN_DOWN, 1 );
	xGPIOSPinWrite( JOYSTICK_PIN_LEFT, 1 );
	xGPIOSPinWrite( JOYSTICK_PIN_RIGHT, 1 );
#endif
}

//*****************************************************************************
//
//! \brief Read joystick key status.
//!
//! \param None.
//!
//! This function is to read joystick key status and return corresponding predefined key code
//! If no key pressed down, the function will return 0.
//!
//! \return key code.
//
//*****************************************************************************
unsigned char JoystickKeyRead(void)
{
	static unsigned char sucKeyUp = 1;
	if( (sucKeyUp==1) && ((xGPIOSPinRead(JOYSTICK_PIN_SELECT)==JOYSTICK_KEY_EFFECTIVE_LEVEL)
					  || (xGPIOSPinRead(JOYSTICK_PIN_UP)==JOYSTICK_KEY_EFFECTIVE_LEVEL)
					  || (xGPIOSPinRead(JOYSTICK_PIN_DOWN)==JOYSTICK_KEY_EFFECTIVE_LEVEL)
					  || (xGPIOSPinRead(JOYSTICK_PIN_LEFT)==JOYSTICK_KEY_EFFECTIVE_LEVEL)
					  || (xGPIOSPinRead(JOYSTICK_PIN_RIGHT)==JOYSTICK_KEY_EFFECTIVE_LEVEL)))
	{
		xSysCtlDelay(100000);
		if(xGPIOSPinRead(JOYSTICK_PIN_SELECT)==JOYSTICK_KEY_EFFECTIVE_LEVEL)
		{
			sucKeyUp=0;
			return JOYSTICK_KEY_SELECT;
		}
		if(xGPIOSPinRead(JOYSTICK_PIN_UP)==JOYSTICK_KEY_EFFECTIVE_LEVEL)
		{
			sucKeyUp=0;
			return JOYSTICK_KEY_UP;
		}
		if(xGPIOSPinRead(JOYSTICK_PIN_DOWN)==JOYSTICK_KEY_EFFECTIVE_LEVEL)
		{
			sucKeyUp=0;
			return JOYSTICK_KEY_DOWN;
		}
		if(xGPIOSPinRead(JOYSTICK_PIN_LEFT)==JOYSTICK_KEY_EFFECTIVE_LEVEL)
		{
			sucKeyUp=0;
			return JOYSTICK_KEY_LEFT;
		}

		if(xGPIOSPinRead(JOYSTICK_PIN_RIGHT)==JOYSTICK_KEY_EFFECTIVE_LEVEL)
		{
			sucKeyUp=0;
			return JOYSTICK_KEY_RIGHT;
		}
	}
	else if(((xGPIOSPinRead(JOYSTICK_PIN_SELECT)!=JOYSTICK_KEY_EFFECTIVE_LEVEL)
			  && (xGPIOSPinRead(JOYSTICK_PIN_UP)!=JOYSTICK_KEY_EFFECTIVE_LEVEL)
			  && (xGPIOSPinRead(JOYSTICK_PIN_DOWN)!=JOYSTICK_KEY_EFFECTIVE_LEVEL)
			  && (xGPIOSPinRead(JOYSTICK_PIN_LEFT)!=JOYSTICK_KEY_EFFECTIVE_LEVEL)
			  && (xGPIOSPinRead(JOYSTICK_PIN_RIGHT)!=JOYSTICK_KEY_EFFECTIVE_LEVEL)))
	{
		sucKeyUp=1;
	}
	return 0;
}
