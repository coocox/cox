//*****************************************************************************
//
//! \file T000060.h
//! \brief Prototypes for the LPR5150AL Driver.
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

#ifndef __T00006X_H__
#define __T00006X_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup GYROSCOPE
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup GYROSCOPE_2AXIS GYROSCOPE 2AXIS
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPR5150AL
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPR5150AL_OUT_AMPLIFY LPR5150AL Out Amplify
//!
//! @{
//
//*****************************************************************************

//
//! define output amplify, to the T000062 it is 4, to the T000060 it is 1
//
#define LPR5150AL_OUT_AMPLIFY   4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup LPR5150AL_Data_Types LPR5150AL Data Types
//! @{
//
//*****************************************************************************

typedef struct LPR5150ALData
{
	float fXAxisData;
	float fYAxisData;

}tLPR5150ALData;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPR5150AL_Configure_ADC LPR5150AL Configure ADC
//! Here is configured for ADC
//! @{
//
//*****************************************************************************

//
//! define the ADC reference voltage(mv) and
//
#define LPR5150AL_ADC_REFVOL    3300

//
//! define the ADC resolution: for 10 bit 1024, 12bit 4096
//
#define LPR5150AL_ADC_RES       4096

//
//! define the ADC resolution voltage(mv)
//
#define LPR5150AL_ADC_RESVOL    ((float) LPR5150AL_ADC_REFVOL / LPR5150AL_ADC_RES)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPR5150AL_Mechanica_Characteristics LPR5150AL Mechanica Characteristics
//! Do not modify this section
//! @{
//
//*****************************************************************************

//
//! define the LPR5150AL sensitivity, [mV/dps] sensitivity of the sensor, took from datasheet
//
#if (LPR5150AL_OUT_AMPLIFY == 4)
#define LPR5150AL_SENSITIVITY   0.67
#elif (LPR5150AL_OUT_AMPLIFY == 1)
#define LPR5150AL_SENSITIVITY   0.167
#else
#error "Please select a correct out amplify"
#endif

//
//! Conversion coefficient, we do here because is a constant! so we'll not
//! do the calculation every loop
//
#define LPR5150AL_k             ((float)LPR5150AL_ADC_RESVOL/LPR5150AL_SENSITIVITY)

//
//! Number of samples that we take for each measure
//
#define LPR5150AL_N             3

//
//! Every LPR5150AL_T (ms) take a sample from gyro
//
#define LPR5150AL_T             40

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPR5150AL_Configure LPR5150AL Configure
//! Here is configured for port
//! @{
//
//*****************************************************************************

//
//! select the ADC base
//
#define LPR5150AL_ADC_BASE      xADC0_BASE

//
//! select the ADC channel of XAxis
//
#define LPR5150AL_IN_CHANNALX   xADC_CTL_CH2

//
//! select the ADC channel of YAxis
//
#define LPR5150AL_IN_CHANNALY   xADC_CTL_CH3

//
//! XAxis in pin configure
//
#define XAXIS_PIN_IN_CFG()      xSPinTypeADC(ADC2, PB2)

//
//! YAxis in pin configure
//
#define YAXIS_PIN_IN_CFG()      xSPinTypeADC(ADC3, PB3)

//
//! Timer select, used for delay.
//
#define LPR5150AL_TIMER_BASE    xTIMER0_BASE

//
//! Timer clock source select
//
#define LPR5150AL_TIMER_CLK     xSYSCTL_TIMER0_MAIN

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup LPR5150AL_Exported_APIs  LPR5150AL Driver APIs
//! \brief API Refrence of LPR5150AL Driver.
//! @{
//
//*****************************************************************************
extern void LPR5150ALInit();
extern tLPR5150ALData LPR5150ALXYAxisCurVoltageGet();
extern tLPR5150ALData LPR5150ALXYAxisNullVoltageGet();
extern tLPR5150ALData LPR5150ALXYAxisRateGet();
extern tLPR5150ALData LPR5150ALXYAxisAngleGet();
extern void DelayMS(unsigned long ulDelay);
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __T00006X_H__
