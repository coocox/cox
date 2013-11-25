//*****************************************************************************
//
//! \file HC_SR04.c
//! \brief Driver for ultrasonic distance measure module.
//! \version V2.1.1.0
//! \date 1/28/2013
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
#include "HC_SR04.h"

static unsigned char sucCaptureCnt = 0;
static unsigned long sulSysClk;
static unsigned long sulCapture1, sulCapture2;

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
//! signal from the module is captured by the timer. The function will record the
//! count value of each capture to calculate the time.
//!
//! \return zero.
//
//*****************************************************************************
unsigned long HCSR04TimerIntCallback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
    //
    // save last count value
    //
	sulCapture1 = sulCapture2;
	//
	// get current count value and clear interrupt flag
	//
	sulCapture2 = xTimerMatchGet(HCSR04_TIMER_BASE, HCSR04_TIMER_CHANNEL);
	//
	// switch capture edge to falling edge
	//
	xTimerCaptureEdgeSelect(HCSR04_TIMER_BASE, HCSR04_TIMER_CHANNEL, xTIMER_CAP_FALLING);

	//
	// capture times increase
	//
	sucCaptureCnt++;

	return 0;
}

//*****************************************************************************
//
//! \brief Get distance
//!
//! \param ucUnit specifies the unit of returned value
//!
//! This function is calculate the distance from the two count values.
//! If the distance exceeds the measure scale or hardware failed, the module 
//! doesn't give a echo pulse. The program will be overtime and return zero.
//!
//! \return Distance between the module and obstacle.
//
//*****************************************************************************
unsigned long HCSR04GetDistance(unsigned char ucUnit)
{
	unsigned long ulRetry = 0;
	unsigned long ulDistance = 0;

	//
	// clear the value of static variables
	//
	sucCaptureCnt = 0;
	sulCapture1 = 0;
	sulCapture2 = 0;

	//
	// first time set capture edge to rising edge to get the start count value
	//
	xTimerCaptureEdgeSelect(HCSR04_TIMER_BASE, HCSR04_TIMER_CHANNEL, xTIMER_CAP_RISING);

	//
	// start to count
	//
	xTimerStart(HCSR04_TIMER_BASE, HCSR04_TIMER_CHANNEL);

	//
	// send a pulse to start measure, the pulse width should be wider than 10us
	//
	xGPIOSPinWrite( HCSR04_TRIG_PIN, 1 );

	//
	// delay about 10us
	//
	xSysCtlDelay(sulSysClk/500000);
	xGPIOSPinWrite( HCSR04_TRIG_PIN, 0 );

	//
	// waiting for two edge captured, if not captured, return zero
	//
	while( sucCaptureCnt < 2 )
	{
		ulRetry++;
		if(ulRetry > 1000000)
			return 0;
	}

	//
	// calculate the time between two capture
	//
	if( sulCapture2 > sulCapture1 )
	{
		ulDistance = sulCapture2 - sulCapture1;
	}
	else
	{
		ulDistance = MAX_RELOAD_VAL + 1 + sulCapture2 - sulCapture1;
	}

	//
	// calculate the distance by specified unit
	//
	if(ucUnit == UNIT_INCH)
	{
		ulDistance = ulDistance / 148;
	}
	else
	{
		ulDistance = ulDistance / 58;
	}

	//
	// Stop the timer
	//
	xTimerStop(HCSR04_TIMER_BASE, HCSR04_TIMER_CHANNEL);

	return ulDistance;
}

//*****************************************************************************
//
//! \brief Get initialized for measuring distance
//!
//! \param None
//!
//! This function is to initialize the IO port and timer to get ready for measure
//!
//! \return None.
//
//*****************************************************************************
void HCSR04Init(void)
{
//	xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HCSR04_TRIG_PIN));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HCSR04_ECHO_PIN));
	xGPIOSPinDirModeSet(HCSR04_TRIG_PIN, xGPIO_DIR_MODE_OUT);
	xGPIOSPinWrite( HCSR04_TRIG_PIN, 0 );
	xGPIOSPinDirModeSet(HCSR04_ECHO_PIN, xGPIO_DIR_MODE_IN);
	xGPIOSPinWrite( HCSR04_ECHO_PIN, 0 );

	xSysCtlPeripheralEnable2(HCSR04_TIMER_BASE);

	sulSysClk = xSysCtlClockGet();

	//
	// Configure the timer as capture mode
	//
	xTimerInitConfig(HCSR04_TIMER_BASE, HCSR04_TIMER_CHANNEL,
			xTIMER_MODE_CAPTURE | xTIMER_COUNT_UP, 1000000);

	//
	// Capture mode: capture
	//
	xTimerCaptureModeSet(HCSR04_TIMER_BASE,
			HCSR04_TIMER_CHANNEL,
			xTIMER_CAP_MODE_CAP);

	//
	// Set reload value
	//
	xTimerLoadSet(HCSR04_TIMER_BASE, HCSR04_TIMER_CHANNEL, MAX_RELOAD_VAL);

	//
	// Set prescaler value to get 1us internal count clock
	//
	xTimerPrescaleSet(xTIMER4_BASE, HCSR04_TIMER_CHANNEL, sulSysClk / 1000000);

	//
	// Set and enable capture interrupt
	//
	xTimerIntCallbackInit(HCSR04_TIMER_BASE, HCSR04TimerIntCallback);
	xTimerIntEnable(HCSR04_TIMER_BASE, HCSR04_TIMER_CHANNEL, xTIMER_INT_CAP_EVENT);
	xIntEnable( HCSR04_TIMER_INT);
}
