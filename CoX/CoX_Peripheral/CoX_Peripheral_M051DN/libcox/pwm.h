//*****************************************************************************
//
//! \file pwm.h
//! \brief Prototypes for the PWM Driver.
//! \version V2.1.1.0
//! \date 12/28/2011
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

#ifndef __PWM_H__
#define __PWM_H__

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
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup PWM
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_PWM
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_PWM_Int_Type  M051 PWM Interrupt Type
//! Values that can be passed to PWMIntEnable(),PWMIntDisable().
//! @{
//
//*****************************************************************************

//
//! PWM channels Interrupt 
//
#define PWM_INT_PWM             0x00000008
#define PWM_INT_DUTY            0x00000001

//
//! Capture Channels Falling Latch Interrupt 
//
#define PWM_INT_CAP_FALL        0x00000004

//
//! Capture Channels Rising Latch Interrupt 
//
#define PWM_INT_CAP_RISE        0x00000002

//
//! Capture Channels Rising and Falling Latch Interrupt 
//
#define PWM_INT_CAP_BOTH        0x00000006



//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_PWM_Event_Type M051 PWM Event Type
//! Values that can be passed to PWMIntEnable(),PWMIntDisable().
//! @{
//
//*****************************************************************************

//
//! The Interrupt event is PWM
//
#define PWM_EVENT_PWM           0x00000000

//
//! The Interrupt event is Capture  
//
#define PWM_EVENT_CAP           0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_PWM_Channel M051 PWM Channel
//! Values that can be passed to all the function in xpwm.c.
//! @{
//
//*****************************************************************************

//
//! Channel 0
//
#define PWM_CHANNEL0            0x00000000

//
//! Channel 1
//
#define PWM_CHANNEL1            0x00000001

//
//! Channel 2
//
#define PWM_CHANNEL2            0x00000002

//
//! Channel 3
//
#define PWM_CHANNEL3            0x00000003

//
//! Channel 4
//
#define PWM_CHANNEL4            0x00000004

//
//! Channel 5
//
#define PWM_CHANNEL5            0x00000005

//
//! Channel 6
//
#define PWM_CHANNEL6            0x00000006

//
//! Channel 7
//
#define PWM_CHANNEL7            0x00000007

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_PWM_Clock_div M051 PWM Clock Divide
//! Values that can be passed to all the function in xpwm.c.
//! @{
//
//*****************************************************************************

//
//! Input clock divided by 1
//
#define PWM_CLOCK_DIV_1         0x00000004

//
//! Input clock divided by 2
//
#define PWM_CLOCK_DIV_2         0x00000000

//
//! Input clock divided by 4
//
#define PWM_CLOCK_DIV_4         0x00000001

//
//! Input clock divided by 8
//
#define PWM_CLOCK_DIV_8         0x00000002

//
//! Input clock divided by 16
//
#define PWM_CLOCK_DIV_16        0x00000003


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_PWM_Config M051 PWM Configuration
//! Values that can be passed to PWMConfigure().
//! @{
//
//*****************************************************************************

//
//! One-Shot Mode
//
#define PWM_ONE_SHOT_MODE       0x00000000

//
//! Auto-reload Mode
//
#define PWM_TOGGLE_MODE         0x00000008

//
//! Inverter enable
//
#define PWM_OUTPUT_INVERTER_EN  0x00000004

//
//! Inverter disable
//
#define PWM_OUTPUT_INVERTER_DIS 0x00000000

//
//! Dead-Zone 0 Generator enable
//
#define PWM_DEAD_ZONE_EN        0x00000010

//
//! Dead-Zone 0 Generator enable
//
#define PWM_DEAD_ZONE_DIS       0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_PWM_Freq_Config M051 PWM Frequency Configuration
//! Values that can be passed to PWMFrequencyConfig() as ulConfig.
//! @{
//
//*****************************************************************************

#define PWM_FREQ_CONFIG(a,b,c)  (( a<<24 ) | ( b<<16 ) | c)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_PWM_Exported_APIs M051 PWM API
//! \brief M051 PWM API Reference.
//! @{
//
//*****************************************************************************
extern void PWMInitConfigure(unsigned long ulBase, unsigned long ulChannel,
                             unsigned long ulConfig);
extern unsigned long PWMFrequencySet(unsigned long ulBase, 
                                     unsigned long ulChannel,
                                     unsigned long ulFrequency);
extern unsigned long PWMFrequencyConfig(unsigned long ulBase, 
                                        unsigned long ulChannel,
                                        unsigned long ulConfig);
extern unsigned long PWMFrequencyGet(unsigned long ulBase,
                                     unsigned long ulChannel);

extern void PWMOutputEnable(unsigned long ulBase, unsigned long ulChannel);
extern void PWMOutputDisable(unsigned long ulBase, unsigned long ulChannel);

extern void PWMStart(unsigned long ulBase, unsigned long ulChannel);
extern void PWMStop(unsigned long ulBase, unsigned long ulChannel);

extern void PWMDutySet(unsigned long ulBase, unsigned long ulChannel,
                       unsigned char ulDuty);
extern unsigned long PWMDutyGet(unsigned long ulBase, unsigned long ulChannel);

extern void PWMIntEnable(unsigned long ulBase, unsigned long ulChannel,
                         unsigned long ulIntType);
extern void PWMIntDisable(unsigned long ulBase, unsigned long ulChannel,
                          unsigned long ulIntType);
extern xtBoolean PWMIntFlagGet(unsigned long ulBase, unsigned long ulChannel,
                               unsigned long ulIntType);
extern void PWMIntFlagClear(unsigned long ulBase, unsigned long ulChannel,
                            unsigned long ulIntType);

extern void PWMIntCallbackInit(unsigned long ulBase, 
                               xtEventCallback xtPWMCallback);

extern void PWMCAPEnable(unsigned long ulBase, unsigned long ulChannel);
extern void PWMCAPDisable(unsigned long ulBase, unsigned long ulChannel);
extern void PWMCAPInputEnable(unsigned long ulBase, unsigned long ulChannel);
extern void PWMCAPInputDisable(unsigned long ulBase, unsigned long ulChannel);
extern unsigned long PWMCAPRisingCounterGet(unsigned long ulBase, 
                                            unsigned long ulChannel);
extern unsigned long PWMCAPFallingCounterGet(unsigned long ulBase, 
                                             unsigned long ulChannel); 
extern void PWMCAPLatchFlagClear(unsigned long ulBase, 
                                 unsigned long ulChannel); 


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

#endif // __xPWM_H__

