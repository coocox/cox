//*****************************************************************************
//
//! \file      xpwm.h
//! \brief     Prototypes for the PWM Driver.
//! \version   V2.2.1.0
//! \date      $CURRENTTIME$
//! \author    CooCox
//! \copyright
//!
//! Copyright (c)  2011, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
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

#ifndef __XPWM_H__
#define __XPWM_H__

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
//! \addtogroup xPWM
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Int_Type xPWM Interrupt Type
//! \brief      Values that show xPWM Interrupt Type
//!
//! \section    xPWM_Int_Type_Section 1. Where to use this group
//!             Values that can be passed to
//!             \ref xPWMIntEnable()
//!             \ref xPWMIntDisable()
//!             as the ulIntType parameter.
//!
//! \section    xPWM_Int_Type_CoX     2. CoX Mandatory and CoX Non-mandatory
//!
//! |  xPWM Interrupt Source   |       CoX      |  LPC17xx  |
//! |--------------------------|----------------|-----------|
//! |  xPWM_INT_PWM            |    Mandatory   |     Y     |
//!
//! @{
//
//*****************************************************************************

//
//! PWM channels Interrupt
//! \note For LPC17xx, it's pwm channel match interrupt
//
#define xPWM_INT_PWM            BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Event_Type xPWM Event Type
//! \brief      Values that show xPWM Event Type
//! \n
//! \section    xPWM_Event_Type_Section 1. Where to use this group
//!             PWM Event/Error Flag, Used by IntHandle's Event Callback
//!             Function as ulEvent parameter. User Callback function can
//!             use this to detect what event happened.
//!
//! \section    xPWM_Event_Type_CoX     2. CoX Mandatory and CoX Non-mandatory
//!
//! |  xPWM Event Source       |       CoX      |  LPC17xx  |
//! |--------------------------|----------------|-----------|
//! |  xPWM_EVENT_PWM          |    Mandatory   |     Y     |
//! |  xPWM_EVENT_CAP          |  non-Mandatory |     Y     |
//!
//! @{
//
//*****************************************************************************

//
//! The Interrupt event is PWM
//
#define xPWM_EVENT_PWM          BIT_32_0

//
//! The Interrupt event is input capture.
//
#define xPWM_EVENT_CAP          BIT_32_1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Freq_Config xPWM Frequency Configure
//! \brief      xPWM Frequency Configure
//! \n
//! \section    xPWM_Event_Type_Section 1. Where to use this group
//!             Values that can be passed to xPWMFrequencyConfig() as
//!             ulConfig parameter.
//!
//! \section    xPWM_Event_Type_CoX     2. CoX Mandatory and CoX Non-mandatory
//! \verbatim
//! +--------------------------+----------------+-----------+
//! |  xPWM Freq Config        |       CoX      |  LPC17xx  |
//! |--------------------------|----------------|-----------|
//! |  xPWM_FREQ_CONFIG(a,b,c) |    Mandatory   |     Y     |
//! |  a is The Divider value  |                |           |
//! |  b is The PreScale value |                |           |
//! |  c is PWM Counter value  |                |           |
//! |--------------------------|----------------|-----------|
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xPWM_FREQ_CONFIG(a,b,c) (a*b)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Channel xPWM Channel
//! \brief      Values that show xPWM Channel
//!
//! \section    xPWM_Channel_Section 1. Where to use this group
//!             Values that can be passed to all the function in xpwm.c as the
//!             ulChannel parameter.
//!
//!             PWM Event Channel Flag, Used by IntHandle's Event Callback
//!             Function as ulMsgParam parmeter. User Callback function can
//!             use this to detect what Channel event happened.
//!
//! \section    xPWM_Channel_CoX 2.CoX Mandatory and CoX Non-mandatory
//! \verbatim
//! +-----------------------+----------------+---------------+
//! | xPWM Channel Number   |       CoX      |     LPC17xx   |
//! |-----------------------|----------------|---------------|
//! | xPWM_CHANNEL$x$       |  Non-Mandatory | xPWM_CHANNEL0 |
//! |                       |                | ------------- |
//! |                       |                | xPWM_CHANNEL1 |
//! |                       |                | ------------- |
//! |                       |                | xPWM_CHANNEL2 |
//! |                       |                | ------------- |
//! |                       |                | xPWM_CHANNEL3 |
//! |                       |                | ------------- |
//! |                       |                | xPWM_CHANNEL4 |
//! |                       |                | ------------- |
//! |                       |                | xPWM_CHANNEL5 |
//! |                       |                | ------------- |
//! |                       |                | xPWM_CHANNEL6 |
//! |-----------------------|----------------|---------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Channel 0
//
#define xPWM_CHANNEL0           PWM_CH_0

//
//! Channel 1
//
#define xPWM_CHANNEL1           PWM_CH_1

//
//! Channel 2
//
#define xPWM_CHANNEL2           PWM_CH_2

//
//! Channel 3
//
#define xPWM_CHANNEL3           PWM_CH_3

//
//! Channel 4
//
#define xPWM_CHANNEL4           PWM_CH_4

//
//! Channel 5
//
#define xPWM_CHANNEL5           PWM_CH_5

//
//! Channel 6
//
#define xPWM_CHANNEL6           PWM_CH_6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Config xPWM Configuration
//! \brief      Values that show xPWM Configuration
//!             Values that can be passed to PWMConfigure().
//!
//! \section    xPWM_Config_Section 1. Where to use this group
//!             Values that can be passed to xPWMInitConfigure() as the ulConfig
//!             parameter.
//!
//! \section    xPWM_Config_CoX 2.CoX Mandatory and CoX Non-mandatory
//!
//! | xPWM Config              |       CoX      |  LPC17xx  |
//! |--------------------------|----------------|-----------|
//! | xPWM_ONE_SHOT_MODE       |    Mandatory   |     Y     |
//! | xPWM_TOGGLE_MODE         |    Mandatory   |     Y     |
//!
//! @{
//
//*****************************************************************************

//
//! One-Shot Mode
//
#define xPWM_ONE_SHOT_MODE      BIT_32_30

//
//! Auto-reload Mode
//
#define xPWM_TOGGLE_MODE        BIT_32_31

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Exported_APIs xPWM APIs
//! \brief      xPWM API Reference.
//!
//! |      xPWM API                |       CoX      |  LPC17xx  |
//! |------------------------------|----------------|-----------|
//! | \ref xPWMInitConfigure       |    Mandatory   |     Y     |
//! | \ref xPWMFrequencySet        |    Mandatory   |     Y     |
//! | \ref xPWMFrequencyConfig     |    Mandatory   |     Y     |
//! | \ref xPWMFrequencyGet        |    Mandatory   |     Y     |
//! | \ref xPWMOutputEnable        |    Mandatory   |     Y     |
//! | \ref xPWMOutputDisable       |    Mandatory   |     Y     |
//! | \ref xPWMStart               |    Mandatory   |     Y     |
//! | \ref xPWMStop                |    Mandatory   |     Y     |
//! | \ref xPWMDutySet             |    Mandatory   |     Y     |
//! | \ref xPWMDutyGet             |    Mandatory   |     Y     |
//! | \ref xPWMIntEnable           |    Mandatory   |     Y     |
//! | \ref xPWMIntDisable          |    Mandatory   |     Y     |
//! | \ref xPWMIntFlagGet          |    Mandatory   |     Y     |
//! | \ref xPWMIntCallbackInit     |    Mandatory   |     Y     |
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief  Initialize and configure the PWM module.
//!         This function is to initialize and configure channel of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \param  [in] ulConfig is the configuration of PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_ONE_SHOT_MODE     
//!              - \ref xPWM_TOGGLE_MODE        
//!              More information, please reference macro define section.
//!
//! \return None.
//
//*****************************************************************************
extern void xPWMInitConfigure(unsigned long ulBase, unsigned long ulChannel,
        unsigned long ulConfig);

//*****************************************************************************
//
//! \brief  Set the PWM frequency of the PWM module.
//!         This function is to set the PWM frequency of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \param  [in] ulFrequency is the PWM frequency of PWM channel.
//!              The ulFrequency parameter can be values: Any values,
//!              ulFrequency > 0 && ulFrequency < PWM module input clock.
//!
//! \return The Actual Frequency of PWM Module.
//
//*****************************************************************************
extern unsigned long xPWMFrequencySet(unsigned long ulBase,unsigned long ulChannel,
        unsigned long ulFrequency);

//*****************************************************************************
//
//! \brief  Set the PWM frequency of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \param  [in] ulConfig is the configuration of PWM channel's frequency.
//!              - \ref xPWM_FREQ_CONFIG(a,b,c) 
//!              \b a is The Divider value, \b b is The PreScale value
//!              \b c is PWM Counter value
//!
//! \return the Actual Frequency of PWM.
//! 
//
//*****************************************************************************
extern unsigned long xPWMFrequencyConfig(unsigned long ulBase, unsigned long ulChannel,
        unsigned long ulConfig);

//*****************************************************************************
//
//! \brief  Get the PWM frequency of the PWM module.
//!         This function is to get the PWM frequency of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \return The Actual Frequency of PWM.
//
//*****************************************************************************
extern unsigned long xPWMFrequencyGet(unsigned long ulBase, unsigned long ulChannel);

//*****************************************************************************
//
//! \brief  Enable the PWM output of the PWM module.
//!         This function is to enable the PWM output of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \return None.
//
//*****************************************************************************
#define xPWMOutputEnable(ulBase, ulChannel)                                   \
         PWMOutPutEnable(ulBase, ulChannel)
//*****************************************************************************
//
//! \brief  Disable the PWM output of the PWM module.
//!         This function is to disable the PWM output of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \return None.
//
//*****************************************************************************
#define xPWMOutputDisable(ulBase, ulChannel)                                  \
         PWMOutPutDisable(ulBase, ulChannel)

//*****************************************************************************
//
//! \brief  Start the PWM of the PWM module.
//!         This function is to start the PWM of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \return None.
//
//*****************************************************************************
extern void xPWMStart(unsigned long ulBase, unsigned long ulChannel);

//*****************************************************************************
//
//! \brief  Stop the PWM of the PWM module.
//!         This function is to stop the PWM of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \return None.
//
//*****************************************************************************
extern void xPWMStop(unsigned long ulBase, unsigned long ulChannel);

//*****************************************************************************
//
//! \brief  Set the PWM duty of the PWM module.
//!         This function is to set the PWM duty of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \param  [in] ulDuty is the duty of PWM channel.
//!
//! \return None.
//!
//! \note   Duty should not be 0;
//
//*****************************************************************************
#define xPWMDutySet(ulBase, ulChannel, ulDuty)

//*****************************************************************************
//
//! \brief  Get the PWM duty of the PWM module.
//!
//!         This function is to get the PWM duty of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \return the Actual duty of PWM.
//
//*****************************************************************************
#define xPWMDutyGet(ulBase, ulChannel)

//*****************************************************************************
//
//! \brief  Enable the PWM interrupt of the PWM module.
//!         This function is to enable the PWM interrupt of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \param  [in] ulIntType is the PWM channel interrupt type.
//!              This value can be:
//!              - \ref xPWM_INT_PWM
//!
//! \return None.
//
//*****************************************************************************
extern void xPWMIntEnable(unsigned long ulBase, unsigned long ulChannel,
        unsigned long ulIntType);

//*****************************************************************************
//
//! \brief  Disable the PWM interrupt of the PWM module.
//!         This function is to disable the PWM interrupt of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \param  [in] ulIntType is the PWM channel interrupt type.
//!              This value can be:
//!              - \ref xPWM_INT_PWM
//!
//! \return None.
//
//*****************************************************************************
extern void xPWMIntDisable(unsigned long ulBase, unsigned long ulChannel,
        unsigned long ulIntType);

//*****************************************************************************
//
//! \brief  Get the PWM interrupt flag of the PWM module.
//!         This function is to get the PWM interrupt flag of the PWM module.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] ulChannel is the PWM channel.
//!              This value can be one of the following value:
//!              - \ref xPWM_CHANNEL0
//!              - \ref xPWM_CHANNEL1
//!              - \ref xPWM_CHANNEL2
//!              - \ref xPWM_CHANNEL3
//!              - \ref xPWM_CHANNEL4
//!              - \ref xPWM_CHANNEL5
//!              - \ref xPWM_CHANNEL6
//!
//! \param  [in] ulIntType is the PWM channel interrupt type.
//!
//! \return None.
//
//*****************************************************************************
#define xPWMIntFlagGet(ulBase, ulChannel, ulIntType)

//*****************************************************************************
//
//! \brief  Init interrupts callback for the PWM timer.
//!         This function is to init interrupts callback for the PWM timer.
//!
//! \param  [in] ulBase is the base address of the PWM port.
//!              For LPC17xx, This value can must be \ref xPWM1_BASE.
//!
//! \param  [in] xtPortCallback is callback for the PWM timer.
//!
//! \return None.
//
//*****************************************************************************
extern void xPWMIntCallbackInit(unsigned long ulBase, xtEventCallback pfnCallback);

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
//! \addtogroup  LPC17xx_PWM
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup  LPC17xx_PWM_Parameters
//! @{
//
//*****************************************************************************

//! PWM Channel 0
#define PWM_CH_0                BIT_32_0

//! PWM Channel 1
#define PWM_CH_1                BIT_32_1

//! PWM Channel 2
#define PWM_CH_2                BIT_32_2

//! PWM Channel 3
#define PWM_CH_3                BIT_32_3

//! PWM Channel 4
#define PWM_CH_4                BIT_32_4

//! PWM Channel 5
#define PWM_CH_5                BIT_32_5

//! PWM Channel 6
#define PWM_CH_6                BIT_32_6

//! PWM capture Channel 0
#define PWM_CAP_0               BIT_32_7

//! PWM capture Channel 1
#define PWM_CAP_1               BIT_32_8

//! PWM interrupt channel 0
#define PWM_INT_CH_0            BIT_32_0

//! PWM interrupt channel 1
#define PWM_INT_CH_1            BIT_32_1

//! PWM interrupt channel 2
#define PWM_INT_CH_2            BIT_32_2

//! PWM interrupt channel 3
#define PWM_INT_CH_3            BIT_32_3

//! PWM interrupt channel 4
#define PWM_INT_CH_4            BIT_32_8

//! PWM interrupt channel 5
#define PWM_INT_CH_5            BIT_32_9

//! PWM interrupt channel 6
#define PWM_INT_CH_6            BIT_32_10

//! PWM interrupt capture channel 0
#define PWM_INT_CAP_0           BIT_32_4

//! PWM interrupt capture channel 1
#define PWM_INT_CAP_1           BIT_32_5

//! PWM interrupt flag mask
#define PWM_INT_FLAG_MASK       (PWM_INT_CH_0 | PWM_INT_CH_1  | PWM_INT_CH_2 |       \
                                 PWM_INT_CH_3 | PWM_INT_CH_4  | PWM_INT_CH_5 |       \
                                 PWM_INT_CH_6 | PWM_INT_CAP_0 | PWM_INT_CAP_1)

//! Enable PWM match interrupt
#define PWM_MATCH_INT_EN        BIT_32_0

//! Disable PWM match interrupt
#define PWM_MATCH_INT_DIS       BIT_32_8

//! Reset counter when PWM match event occurs
#define PWM_MATCH_RESET_EN      BIT_32_1

//! Don't reset counter when PWM match event occurs
#define PWM_MATCH_RESET_DIS     BIT_32_9

//! Stop counter when PWM match event occurs
#define PWM_MATCH_STOP_EN       BIT_32_2

//! Don's stop counter when PWM match event occurs
#define PWM_MATCH_STOP_DIS      BIT_32_10

//! Enable Double edge mode
#define PWM_EDGE_DOUBLE         BIT_32_0

//! Enable single edge mode
#define PWM_EDGE_SINGLE         BIT_32_1

//! Enable PWM capture channel 0 falling sample.
#define CH0_FALLING_SAMPLE_EN   BIT_32_0

//! Disable PWM capture channel 0 falling sample.
#define CH0_FALLING_SAMPLE_DIS  BIT_32_8

//! Enable PWM capture channel 0 rising sample.
#define CH0_RISING_SAMPLE_EN    BIT_32_1

//! Disable PWM capture channel 0 rising sample.
#define CH0_RISING_SAMPLE_DIS   BIT_32_9

//! Enable PWM capture channel 0 event interrupt.
#define CH0_EDGE_EVENT_INT_EN   BIT_32_2

//! Disable PWM capture channel 0 event interrupt.
#define CH0_EDGE_EVENT_INT_DIS  BIT_32_10

//! Enable PWM capture channel 1 falling sample.
#define CH1_FALLING_SAMPLE_EN   BIT_32_3

//! Disable PWM capture channel 1 falling sample.
#define CH1_FALLING_SAMPLE_DIS  BIT_32_11

//! Enable PWM capture channel 1 rising sample.
#define CH1_RISING_SAMPLE_EN    BIT_32_4

//! Disable PWM capture channel 1 rising sample.
#define CH1_RISING_SAMPLE_DIS   BIT_32_12

//! Enable PWM capture channel 1 event interrupt.
#define CH1_EDGE_EVENT_INT_EN   BIT_32_5

//! Disable PWM capture channel 1 event interrupt.
#define CH1_EDGE_EVENT_INT_DIS  BIT_32_13

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup  LPC17xx_PWM_Exported_APIs  LPC17xx PWM API
//! \brief  LPC17xx PWM API Reference.
//! @{
//
//*****************************************************************************

extern void PWMPrescaleValueSet(unsigned long ulBase, unsigned long ulValue);
extern void PWMIntStatusClear(unsigned long ulBase, unsigned long ulIntFlags);
extern unsigned long PWMIntStatusGet(unsigned long ulBase);
extern xtBoolean PWMIntStatusCheck(unsigned long ulBase, unsigned long ulIntFlags);
extern void PWMCounterEnable(unsigned long ulBase);
extern void PWMCounterDisable(unsigned long ulBase);
extern void PWMCounterReset(unsigned long ulBase);
extern void PWMStart(unsigned long ulBase);
extern void PWMStop(unsigned long ulBase);
extern void PWMMatchCfg(unsigned long ulBase, unsigned long ulCh, unsigned long ulCfg);
extern void PWMMatchUpdate(unsigned long ulBase, unsigned long ulCh, unsigned long ulValue);
extern void PWMOutPutEnable(unsigned long ulBase, unsigned long ulChs);
extern void PWMOutPutDisable(unsigned long ulBase, unsigned long ulChs);
extern void PWMEdgeCfg(unsigned long ulBase, unsigned long ulChs, unsigned long ulCfg);
extern void PWMCapCfg(unsigned long ulBase, unsigned long ulCfg);
extern unsigned long PWMCapValueGet(unsigned long ulBase, unsigned long ulCh);

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

#endif // __XPWM_H__
