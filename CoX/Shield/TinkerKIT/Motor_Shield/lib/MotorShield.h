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
//! \addtogroup ULN2003_Config_Interface ULN2003 Interface Configurtion.
//!
//! \brief Can be set to:
//! - \ref ULN2003_PIN_IN1  
//! - \ref ULN2003_PIN_IN2 
//! - \ref ULN2003_PIN_IN3 
//! - \ref ULN2003_PIN_IN4 
//! - \ref ULN2003_PIN_IN5  
//! - \ref ULN2003_PIN_IN6 
//! - \ref ULN2003_PIN_IN7 
//!
//! @{
//
//*****************************************************************************

#define ULN2003_PIN_IN1         PA4
#define ULN2003_PIN_IN2         PA5
#define ULN2003_PIN_IN3         PA6
#define ULN2003_PIN_IN4         PA7

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
//! \addtogroup MShield_Software_Cfg MShield Softeware Configure 
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
//! \addtogroup MShield_Exported_APIs MShied API
//! @{
//
//*****************************************************************************

extern void MSStepMotorInit(void);
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
