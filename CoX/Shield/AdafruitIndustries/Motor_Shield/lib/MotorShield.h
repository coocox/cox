//*****************************************************************************
//
//! \file MotorShield.h
//! \brief Adafruit MShield driver.
//! \version V2.1.1.0
//! \date 7/24/2012
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

#ifndef __MOTORSHIELD_H__
#define __MOTORSHIELD_H__

//*****************************************************************************
//
//! \addtogroup CoX_Shield_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MShield 
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MShield_StepMotor_StepperNum MShield Step motor Stepper NUM 
//!  Values that can be passed to MSStepMotorInit().
//! @{
//
//*****************************************************************************

//
//! Step motor stepper number 1 
//
#define MS_STEPPER_NUM1          0x00000000

//
//! Step motor stepper number 2
//
#define MS_STEPPER_NUM2          0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MShield_StepMotor_Dir MShield Step motor direction 
//!  Values that can be passed to MSStepMotorRun().
//! @{
//
//*****************************************************************************

//
//! Step motor run forward
//
#define MS_RUN_FORWARD          0x00000000

//
//! Step motor run baskward
//
#define MS_RUN_BACKWARD         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MShield_DCMotorPWM_Channel MShield DC Motor PWM Channel. 
//!  Values that can be passed to MSDCMotorPWMInit().
//! @{
//
//*****************************************************************************

//
//! PWM Channel PWM0A
//
#define MS_CHANNEL_PWM0A        xPWM_CHANNEL4

//
//! PWM Channel PWM2A
//
#define MS_CHANNEL_PWM2A        xPWM_CHANNEL7

//
//! PWM Channel PWM0B
//
#define MS_CHANNEL_PWM0B        xPWM_CHANNEL3

//
//! PWM Channel PWM2B
//
#define MS_CHANNEL_PWM2B        xPWM_CHANNEL1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MShield_Software_Cfg MShield Softeware Configure 
//! @{
//
//*****************************************************************************

//
//! Config the PWM divider value
//
#define MS_PWMDIV_VALUE         16

//
//! Config the PWM prescaler value
//
#define MS_PWMPSR_VALUE         150

//
//! Config the PWM c value
//
#define MS_PWMCNT_VALUE         5000

//
//! Configure the timer which is used for delay
//
#define MS_DELAY_TIMER          xTIMER0_BASE

//
//! Configure timer's corresponding channel
//
#define MS_DELAY_CHANNEL        xTIMER_CHANNEL0

//
//! Configure the timer delay clock source
//
#define MS_DELAY_CLKSRC         xSYSCTL_TIMER0_MAIN

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MShield_Exported_APIs MShied API
//! @{
//
//*****************************************************************************

extern void MS74HC595PinInit(void);
extern void MS74HC595DataSend(unsigned char ucData);

extern void MSDCMotorPWMInit(unsigned long ulBase, unsigned long ulChannel);
extern void MSDCMotorRun(unsigned long ulChannel, unsigned long ulDir);
extern void MSDCMotorSpeedSet(unsigned long ulBase, unsigned long ulChannel, 
                                        unsigned long ulSpeed);
extern void MSDCMotorStop(unsigned long ulChannel);

extern void MSStepMotorInit(unsigned long ulStepperNum);
extern void MSStepsDelaySet(unsigned long ulDelay);
extern void MSStepMotorRun(unsigned long ulDir, unsigned long ulSteps);
extern void MSStepMotorStop(void);

extern void MSDelay(unsigned long ulDelay);

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

#endif // __MOTORSHIELD_H__
