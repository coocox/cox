//*****************************************************************************
//
//! \file infrared.c
//! \brief driver file for the infrared decode driver.
//! \version V0.0.0.1
//! \date 2/27/2013
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
//*****************************************************************************
#include "xhw_gpio.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_timer.h"
#include "xhw_types.h"
#include "xcore.h"
#include "xgpio.h"
#include "xsysctl.h"
#include "xtimer.h"
#include "infrared.h"

//
// Capture count
//
static unsigned char sucCaptureCnt = 1;

static unsigned long sulSysClk;
static unsigned short usCapture1, usCapture2;
static unsigned short usPulseWidth;
//
// Decode status
//
unsigned char g_ucIRDecodeOK = 0;
//
// Decode value
//
unsigned long sulIRKeyValue = 0;

//*****************************************************************************
//
//! \brief Timer capture interrupt service function
//!
//! \param pvCBData not used
//! \param ulEvent not used
//! \param ulMsgParam not used
//! \param pvMsgData not used
//!
//! This function is entered when the rising edge or falling edge of the feedback
//! signal from the module which is captured by the timer. The function will record the
//! count value of each capture to calculate the pulse width. Then decode the pulse according
//! to the pulse width.
//!
//! \return zero.
//
//*****************************************************************************
unsigned long IRTimerIntCallback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
    //
    // save last count value
    //
	usCapture1 = usCapture2;
	//
	// get current count value and clear interrupt flag
	//
	usCapture2 = xTimerMatchGet(VS1838B_TIMER_BASE, VS1838B_TIMER_CHANNEL);
	//
	// switch capture edge
	//
	if((sucCaptureCnt & 0x01) == 0)
	{
		// to get low level time of one cycle
		xTimerCaptureEdgeSelect(VS1838B_TIMER_BASE, VS1838B_TIMER_CHANNEL, xTIMER_CAP_RISING);

		if((usCapture1 < usCapture2)&&(sucCaptureCnt>1))
		{
			usPulseWidth = usCapture2 - usCapture1;
		}
		else
		{
			usPulseWidth = MAX_RELOAD_VAL - usCapture1 + usCapture2 + 1;
		}
		if((usPulseWidth <= (INFRARED_CODE_START + INFRARED_TIME_ERROR))&&
			(usPulseWidth >= (INFRARED_CODE_START - INFRARED_TIME_ERROR)))
		{
			//
			// If receive start signal
			//
			g_ucIRDecodeOK = 0;
			sucCaptureCnt = 3;
			return 0;
		}
		else
		{
			if(sucCaptureCnt <= 66)
			{
				//
				// (1 bit start signal + 32 data bit) * 2 edge per pulse = 66
				//
				if((usPulseWidth <= (INFRARED_CODE_1 + INFRARED_TIME_ERROR))&&
					(usPulseWidth >= (INFRARED_CODE_1 - INFRARED_TIME_ERROR)))
				{
					// Received 1
					sulIRKeyValue >>= 1;
					sulIRKeyValue += 0x80000000;
				}
				else
				{
					// Received 0
					sulIRKeyValue >>= 1;
				}
			}
			else
			{
				//Decode over
				g_ucIRDecodeOK = 1;
				sucCaptureCnt = 0;
			}
		}
	}
	else
	{
		//
		// change capture edge to falling edge to get high level pulse width
		//
		xTimerCaptureEdgeSelect(VS1838B_TIMER_BASE, VS1838B_TIMER_CHANNEL, xTIMER_CAP_FALLING);
	}

	//
	// capture times increase
	//
	sucCaptureCnt++;

	return 0;
}

//*****************************************************************************
//
//! \brief Get key code
//!
//! \param None
//!
//! This function is to get the key code after decoding
//!
//! \return ((8 bit)user code << 8) | (8 bit)key code.
//
//*****************************************************************************
unsigned short IRKeyValueGet(void)
{
	unsigned long ulCode1, ulCode2;

	if(g_ucIRDecodeOK)
	{
		g_ucIRDecodeOK = 0;
		ulCode1 = (sulIRKeyValue >> 24) & 0x00FF;
		ulCode2 = (sulIRKeyValue >> 16) & 0x00FF;
		if(ulCode1==((~ulCode2)&0x00FF))
		{
			ulCode1 = sulIRKeyValue & 0x000000FF;
			ulCode2 = (ulCode1 << 8) | ulCode2;
			return ((unsigned char)ulCode2);
		}
	}
	return 0;
}

//*****************************************************************************
//
//! \brief Get initialized for infrared remote controller receiver
//!
//! \param None
//!
//! This function is to initialize the IO port and timer to get ready for decoding
//!
//! \return None.
//
//*****************************************************************************
void IRInit(void)
{
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(VS1838B_RECEIVER_PIN));

	xGPIOSPinDirModeSet(VS1838B_RECEIVER_PIN, xGPIO_DIR_MODE_IN);
	xGPIOSPinWrite( VS1838B_RECEIVER_PIN, 1 );

	xSysCtlPeripheralEnable2(VS1838B_TIMER_BASE);

	sulSysClk = xSysCtlClockGet();

	//
	// Configure the timer as capture mode
	//
	xTimerInitConfig(VS1838B_TIMER_BASE, VS1838B_TIMER_CHANNEL,
			xTIMER_MODE_CAPTURE | xTIMER_COUNT_UP, 1000000);

	//
	// Capture mode: capture
	//
	xTimerCaptureModeSet(VS1838B_TIMER_BASE,VS1838B_TIMER_CHANNEL,
			xTIMER_CAP_MODE_CAP);

	xTimerCaptureEdgeSelect(VS1838B_TIMER_BASE, VS1838B_TIMER_CHANNEL, xTIMER_CAP_RISING);

	//
	// Set reload value
	//
	xTimerLoadSet(VS1838B_TIMER_BASE, VS1838B_TIMER_CHANNEL, MAX_RELOAD_VAL);

	//
	// Set prescaler value to get 1us internal count clock
	//
	xTimerPrescaleSet(VS1838B_TIMER_BASE, VS1838B_TIMER_CHANNEL, sulSysClk / 1000000);

	//
	// Set and enable capture interrupt
	//
	xTimerIntCallbackInit(VS1838B_TIMER_BASE, IRTimerIntCallback);
	xTimerIntEnable(VS1838B_TIMER_BASE, VS1838B_TIMER_CHANNEL, xTIMER_INT_CAP_EVENT);
	xIntEnable( VS1838B_TIMER_INT);
	//
	// start to count
	//
	xTimerStart(VS1838B_TIMER_BASE, VS1838B_TIMER_CHANNEL);
}
