//*****************************************************************************
//
//! \file T000060.h
//! \brief Prototypes for the GPIO Driver.
//! \version V2.1.1.0
//! \date 11/28/2012
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
#include "xadc.h"
#include "xtimer.h"
#include "T00006x.h"

unsigned char g_ucCount = 3;
unsigned char g_ucDelayms = 40;

//*****************************************************************************
//
//! \brief Init the ADC with the corresponding configuration in the
//! LPR5150AL_Configure gorup.
//!
//! \return None.
//
//*****************************************************************************
void
LPR5150ALInit()
{
	//
	// Select the ADC clock source
	//
    xSysCtlPeripheralClockSourceSet(xSYSCTL_ADC0_HCLK, 3);

    //
    // Enable Peripheral ADC0
    //
    xSysCtlPeripheralEnable2(LPR5150AL_ADC_BASE);

    //
    // Configure Some GPIO pins as ADC Mode
    //
    XAXIS_PIN_IN_CFG();
    YAXIS_PIN_IN_CFG();

    //
    // Enable the ADC
    //
    xADCEnable(LPR5150AL_ADC_BASE);

    //
    // ADC Channel0 convert once, Software tirgger.
    //
    xADCConfigure(LPR5150AL_ADC_BASE, xADC_MODE_SCAN_CONTINUOUS, ADC_TRIGGER_PROCESSOR);

    //
    // Enable the channel2/3
    //
    xADCStepConfigure(LPR5150AL_ADC_BASE, 0, xADC_CTL_CH2);
    xADCStepConfigure(LPR5150AL_ADC_BASE, 1, xADC_CTL_CH3);

    //
    // ADC start Convert
    //
    xADCProcessorTrigger(LPR5150AL_ADC_BASE);
}

//*****************************************************************************
//
//! \brief Get the current channel voltage which is connected to the XYAxis.
//!
//! \param None.
//!
//! \return The data of channel Current voltage.
//
//*****************************************************************************
tLPR5150ALData
LPR5150ALXYAxisCurVoltageGet()
{

	tLPR5150ALData XYAxisCurVoltage = {0, 0};
	unsigned long ulXYADCData[2] = {0, 0};

	//
	// Read the XAxis, YAxis ADC data
	//
	xADCDataGet(LPR5150AL_ADC_BASE, ulXYADCData);
	ulXYADCData[0] = ulXYADCData[0] & 0x00000FFF;
	ulXYADCData[1] = ulXYADCData[1] & 0x00000FFF;

	//
	// Convert ADC data to voltage
	//
	XYAxisCurVoltage.fXAxisData = (float)(ulXYADCData[0] * LPR5150AL_ADC_RESVOL);
	XYAxisCurVoltage.fYAxisData = (float)(ulXYADCData[1] * LPR5150AL_ADC_RESVOL);

	return XYAxisCurVoltage;

}

//*****************************************************************************
//
//! \brief Get the XYAxis Null voltage.
//!
//! \param None.
//!
//! \return The data of channel Current voltage.
//
//*****************************************************************************
tLPR5150ALData
LPR5150ALXYAxisNullVoltageGet()
{
	tLPR5150ALData XYAxisCurVoltage = {0, 0};
	tLPR5150ALData XYAxisNullVoltage = {0, 0};

	float fXAxisDataTemp = 0, fYAxisDataTemp = 0;
	unsigned char i;

	for(i = 0; i < 50; i++)
	{
		XYAxisCurVoltage = LPR5150ALXYAxisCurVoltageGet();
		fXAxisDataTemp += XYAxisCurVoltage.fXAxisData;
		fYAxisDataTemp += XYAxisCurVoltage.fYAxisData;

		//
		// delay a little time
		//
		xSysCtlDelay(10);
	}

	//
	// Get the Null voltage.
	//
	XYAxisNullVoltage.fXAxisData = fXAxisDataTemp / 50;
	XYAxisNullVoltage.fYAxisData = fYAxisDataTemp / 50;

	return XYAxisNullVoltage;

}

//*****************************************************************************
//
//! \brief Get the XYAxis angular velocity.
//!
//! \param None.
//!
//! \return The data of XYAxis angular velocity.
//
//*****************************************************************************
tLPR5150ALData
LPR5150ALXYAxisRateGet()
{
	unsigned char i;
	unsigned char ucCount = LPR5150AL_N;
	unsigned char ucDelayms = LPR5150AL_T;
	tLPR5150ALData XYAxisVoltage[LPR5150AL_N] = {(0, 0), (0, 0), (0, 0)};
	tLPR5150ALData XYAxisNullVoltage = {0,0};
	tLPR5150ALData XYAxisVoltageTemp = {0,0};
	tLPR5150ALData XYAxisVoltageAverage = {0,0};

	tLPR5150ALData XYAxisRate = {0,0};

	XYAxisNullVoltage = LPR5150ALXYAxisNullVoltageGet();

	//
	// take a sample in every 40ms
	//
	while(ucCount--)
	{
		DelayMS(ucDelayms);
		XYAxisVoltage[ucCount] = LPR5150ALXYAxisCurVoltageGet();
	}

	//
	// Calculate the average voltage
	//
	for(i = 0; i < 3; i++)
	{
		XYAxisVoltageTemp.fXAxisData += XYAxisVoltage[i].fXAxisData;
		XYAxisVoltageTemp.fYAxisData += XYAxisVoltage[i].fYAxisData;
	}
	XYAxisVoltageAverage.fXAxisData = XYAxisVoltageTemp.fXAxisData/LPR5150AL_N;
	XYAxisVoltageAverage.fYAxisData = XYAxisVoltageTemp.fYAxisData/LPR5150AL_N;

    //
	// Transform the raw data into an angular velocity
	//
	XYAxisRate.fXAxisData = (XYAxisVoltageAverage.fXAxisData -
			                 XYAxisNullVoltage.fXAxisData) * LPR5150AL_k;
	XYAxisRate.fYAxisData = (XYAxisVoltageAverage.fYAxisData -
			                 XYAxisNullVoltage.fYAxisData) * LPR5150AL_k;

    return XYAxisRate;

}

//*****************************************************************************
//
//! \brief Get the XYAxis angular.
//!
//! \param None.
//!
//! \return The data of XYAxis angular.
//
//*****************************************************************************
tLPR5150ALData
LPR5150ALXYAxisAngleGet()
{
	tLPR5150ALData XYAxisRate;
	tLPR5150ALData XYAxisAngle;

	float fDeltaT = ((float)LPR5150AL_N * LPR5150AL_T) / 1000;

	XYAxisRate = LPR5150ALXYAxisRateGet();
	XYAxisAngle.fXAxisData = XYAxisRate.fXAxisData * fDeltaT;
	XYAxisAngle.fYAxisData = XYAxisRate.fYAxisData * fDeltaT;

	if(XYAxisAngle.fXAxisData < 0)
	{
		XYAxisAngle.fXAxisData += 360;
	}
	else if(XYAxisAngle.fXAxisData > 359)
	{
		XYAxisAngle.fXAxisData -= 360;
	}

	if(XYAxisAngle.fYAxisData < 0)
	{
		XYAxisAngle.fYAxisData += 360;
	}
	else if(XYAxisAngle.fYAxisData > 359)
	{
		XYAxisAngle.fYAxisData -= 360;
	}

	return XYAxisAngle;

}

//*****************************************************************************
//
//! \brief Dalay some time in ms.
//!
//! \param ulDelay is the delay number of ms.
//!
//! \return None.
//
//*****************************************************************************
void
DelayMS(unsigned long ulDelay)
{
    //
    // Set the timer clock
    //
    xSysCtlPeripheralClockSourceSet(LPR5150AL_TIMER_CLK, 1);

    xSysCtlPeripheralEnable2(LPR5150AL_TIMER_BASE);

	//
	// Clear the status first
	//
	xTimerStatueClear(LPR5150AL_TIMER_BASE, xTIMER_CHANNEL0, xTIMER_INT_MATCH);

    //
    // Config as periodic mode
    //
    xTimerInitConfig(LPR5150AL_TIMER_BASE, xTIMER_CHANNEL0, xTIMER_MODE_PERIODIC, 1000);
    xTimerIntEnable(LPR5150AL_TIMER_BASE, xTIMER_CHANNEL0, xTIMER_INT_MATCH);
    xTimerStart(LPR5150AL_TIMER_BASE, xTIMER_CHANNEL0);

    //
    // Delay ulDelay cycles, one cycle delay is 1ms.
    //
    while(ulDelay)
	{
	    while(!xTimerStatusGet(LPR5150AL_TIMER_BASE, xTIMER_CHANNEL0, xTIMER_INT_MATCH));
		xTimerStatueClear(LPR5150AL_TIMER_BASE, xTIMER_CHANNEL0, xTIMER_INT_MATCH);
		ulDelay--;
	}

    //
    // Stop the timer
    //
	xTimerStop(LPR5150AL_TIMER_BASE, xTIMER_CHANNEL0);
	xSysCtlPeripheralDisable2(LPR5150AL_TIMER_BASE);

}

