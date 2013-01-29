//*****************************************************************************
//
//! \file ArduinoMotorShield.h
//! \brief Arduino MShield driver.
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
//! \addtogroup ArduinoMShield
//! @{
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup AMShield_StepMotor_Dir Arduino MShield Step motor direction
//!  Values that can be passed to MSStepMotorRun().
//! @{
//
//*****************************************************************************

//
//! Step motor run forward
//
#define AMS_RUN_FORWARD         0x00000000

//
//! Step motor run baskward
//
#define AMS_RUN_BACKWARD        0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ArduinoMShield_DCMotor ArduinoMShield DC Motor PWM Channel.
//!  Values that can be passed to MSDCMotorPWMInit().
//! @{
//
//*****************************************************************************

//
//! motor A
//
#define AMS_MOTOR_A             0x00000001

//
//! motor B
//
#define AMS_MOTOR_B             0x00000002


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ArduinoMShield_Software_Cfg ArduinoMShield Softeware Configure
//! @{
//
//*****************************************************************************

//
//! Configure the timer which is used for delay
//
#define MS_DELAY_TIMER          xTIMER2_BASE

//
//! Configure timer's corresponding channel
//
#define MS_DELAY_CHANNEL        xTIMER_CHANNEL0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ArduinoMShield_Exported_APIs MShied API
//! @{
//
//*****************************************************************************


extern void AMSDCMotorPWMInit(unsigned long ulMotor, unsigned long ulFrequency,
                              unsigned long ulDuty);
extern void AMSDCMotorRun(unsigned long ulMotor, unsigned long ulDir);
extern void AMSDCMotorSpeedSet(unsigned long ulMotor, unsigned long ulSpeed);
extern void AMSDCMotorStop(unsigned long ulMotor);

extern void AMSStepMotorInit(void);
extern void AMSStepsDelaySet(unsigned long ulDelay);
extern void AMSStepMotorRun(unsigned long ulDir, unsigned long ulSteps);
extern void AMSStepMotorStop(void);

extern void AMSMotorADCInit(void);
extern unsigned long AMSMotorCurrentGet(unsigned long ulMotor);

extern void AMSDelay(unsigned long ulDelay);

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
