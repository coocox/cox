//*****************************************************************************
//
//! \file xpwm.h
//! \brief Prototypes for the PWM Driver.
//! \version V2.1.1.1
//! \date 11/14/2011
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

#ifndef __xPWM_H__
#define __xPWM_H__

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
//! \brief Values that show xPWM Interrupt Type
//! \n
//! \section xPWM_Int_Type_Section 1. Where to use this group
//! Values that can be passed to xPWMIntEnable(),xPWMIntDisable()
//! as the ulIntType parameter. 
//! \n
//! \section xPWM_Int_Type_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +------------------------+----------------+--------+
//! |xPWM Interrupt Source   |       CoX      | NUC1xx |
//! |------------------------|----------------|--------|
//! |xPWM_INT_PWM            |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! PWM channels Interrupt 
//
#define xPWM_INT_PWM            PWM_INT_PWM

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Event_Type xPWM Event Type
//! \brief Values that show xPWM Event Type
//! \n
//! \section xPWM_Event_Type_Section 1. Where to use this group
//! PWM Event/Error Flag, Used by IntHandle's Event Callback Function as 
//! ulEvent parmeter. User Callback function can user this to detect what 
//! event happened. 
//! \n
//! \section xPWM_Event_Type_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +------------------------+----------------+--------+
//! |xPWM Event Source       |       CoX      | NUC1xx |
//! |------------------------|----------------|--------|
//! |xPWM_EVENT_PWM          |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWM_EVENT_CAP          |  non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! The Interrupt event is PWM
//
#define xPWM_EVENT_PWM          PWM_EVENT_PWM

//
//! The Interrupt event is Capture  
//
#define xPWM_EVENT_CAP          PWM_EVENT_CAP


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Freq_Config xPWM Frequency Configure
//! \brief xPWM Frequency Configure
//! \n
//! \section xPWM_Event_Type_Section 1. Where to use this group
//! Values that can be passed to xPWMFrequencyConfig() as ulConfig parameter. 
//! \n
//! \section xPWM_Event_Type_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +------------------------+----------------+--------+
//! |xPWM Freq Config        |       CoX      | NUC1xx |
//! |------------------------|----------------|--------|
//! |xPWM_FREQ_CONFIG(a,b,c) |    Mandatory   |    Y   |
//! |a is The Divider value  |                |        |
//! |b is The PreScale value |                |        |
//! |c is PWM Counter value  |                |        |
//! |------------------------|----------------|--------|
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xPWM_FREQ_CONFIG(a,b,c) (( a<<24 ) | ( b<<16 ) | c)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Channel xPWM Channel
//! \brief Values that show xPWM Channel
//! \n
//! \section xPWM_Channel_Section 1. Where to use this group
//! Values that can be passed to all the function in xpwm.c
//! as the ulChannel parameter. 
//!
//! PWM Event Channel Flag, Used by IntHandle's Event Callback Function as 
//! ulMsgParam parmeter. User Callback function can user this to detect what 
//! Channel event happened. 
//! \n
//! \section xPWM_Channel_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +------------------------+----------------+-------------+
//! |xPWM Channel Number     |       CoX      |   NUC1xx    |
//! |------------------------|----------------|-------------|
//! |xPWM_CHANNEL$x$         |  Non-Mandatory |xPWM_CHANNEL0|
//! |                        |                |-------------|
//! |                        |                |xPWM_CHANNEL1|
//! |                        |                |-------------|
//! |                        |                |xPWM_CHANNEL2|
//! |                        |                |-------------|
//! |                        |                |xPWM_CHANNEL3|
//! |                        |                |-------------|
//! |                        |                |xPWM_CHANNEL4|
//! |                        |                |-------------|
//! |                        |                |xPWM_CHANNEL5|
//! |                        |                |-------------|
//! |                        |                |xPWM_CHANNEL6|
//! |                        |                |-------------|
//! |                        |                |xPWM_CHANNEL7|
//! |------------------------|----------------|-------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Channel 0
//
#define xPWM_CHANNEL0           PWM_CHANNEL0

//
//! Channel 1
//
#define xPWM_CHANNEL1           PWM_CHANNEL1

//
//! Channel 2
//
#define xPWM_CHANNEL2           PWM_CHANNEL2

//
//! Channel 3
//
#define xPWM_CHANNEL3           PWM_CHANNEL3

//
//! Channel 4
//
#define xPWM_CHANNEL4           PWM_CHANNEL4

//
//! Channel 5
//
#define xPWM_CHANNEL5           PWM_CHANNEL5

//
//! Channel 6
//
#define xPWM_CHANNEL6           PWM_CHANNEL6

//
//! Channel 7
//
#define xPWM_CHANNEL7           PWM_CHANNEL7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Config xPWM Configuration
//! \brief Values that show xPWM Configuration
//! Values that can be passed to PWMConfigure().
//! \n
//! \section xPWM_Config_Section 1. Where to use this group
//! Values that can be passed to xPWMInitConfigure()
//! as the ulConfig parameter. 
//! \n
//! \section xPWM_Config_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +------------------------+----------------+--------+
//! |xPWM Config             |       CoX      | NUC1xx |
//! |------------------------|----------------|--------|
//! |xPWM_ONE_SHOT_MODE      |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWM_TOGGLE_MODE        |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWM_OUTPUT_INVERTER_EN |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xPWM_OUTPUT_INVERTER_DIS|  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xPWM_DEAD_ZONE_EN       |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! |xPWM_DEAD_ZONE_DIS      |  Non-Mandatory |    Y   |
//! |------------------------|----------------|--------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! One-Shot Mode
//
#define xPWM_ONE_SHOT_MODE      PWM_ONE_SHOT_MODE

//
//! Auto-reload Mode
//
#define xPWM_TOGGLE_MODE        PWM_TOGGLE_MODE

//
//! Inverter enable
//
#define xPWM_OUTPUT_INVERTER_EN PWM_OUTPUT_INVERTER_EN

//
//! Inverter enable
//
#define xPWM_OUTPUT_INVERTER_DIS PWM_OUTPUT_INVERTER_DIS

//
//! Dead-Zone 0 Generator enable
//
#define xPWM_DEAD_ZONE_EN       PWM_DEAD_ZONE_EN

//
//! Dead-Zone 0 Generator enable
//
#define xPWM_DEAD_ZONE_DIS      PWM_DEAD_ZONE_DIS

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Exported_APIs xPWM APIs
//! \brief xPWM API Reference.
//! \verbatim
//! +------------------------+----------------+--------+
//! |xPWM API                |       CoX      | NUC1xx |
//! |------------------------|----------------|--------|
//! |xPWMInitConfigure       |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWMFrequencySet        |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWMFrequencyConfig     |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWMFrequencyGet        |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWMOutputEnable        |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWMOutputDisable       |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWMStart               |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWMStop                |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWMDutySet             |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWMDutyGet             |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWMIntEnable           |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWMIntDisable          |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWMIntFlagGet          |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! |xPWMIntCallbackInit     |    Mandatory   |    Y   |
//! |------------------------|----------------|--------|
//! \endverbatim
//! @{
//
//*****************************************************************************


//*****************************************************************************
//
//! \brief Initialize and configure the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulConfig is the configuration of PWM channel.
//! Details please refer to \ref xPWM_Config.
//!
//! This function is to initialize and configure channel of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulConfig parameter is the logical OR of four values: The PWM mode,
//! Inverter or not,and use dead zero or not and dead zone length. 
//! \b xPWM_ONE_SHOT_MODE,\b xPWM_TOGGLE_MODE is the mode selecet.
//! \b xPWM_OUTPUT_INVERTER_EN,
//! \b xPWM_OUTPUT_INVERTER_DIS is to enable Inverter or not.
//! \b xPWM_DEAD_ZONE_EN
//! \b xPWM_DEAD_ZONE_DIS is to enable dead zone Generator or not.
//! The dead zone length will be set at the 16~23 bits of the ulConfig.
//! Details please refer to \ref xPWM_Config_CoX.
//!
//! \note When Dead-Zone Generator is enabled, the pair of PWM0 and PWM1 
//! becomes a complementary pair for PWM group A and the pair of PWM4 and 
//! PWM5 becomes a complementary pair for PWM group B.
//!
//! \return None.
//
//*****************************************************************************
#define xPWMInitConfigure(ulBase, ulChannel, ulConfig)                        \
        PWMInitConfigure(ulBase, ulChannel, ulConfig)                                          

//*****************************************************************************
//
//! \brief Set the PWM frequency of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulFrequency is the PWM frequency of PWM channel.
//!
//! This function is to set the PWM frequency of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulFrequency parameter can be values: Any values ,ulFrequency > 0 &&
//! ulFrequency < PWM module input clock.
//!
//! \note 
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
#define xPWMFrequencySet(ulBase, ulChannel, ulFrequency)                      \
        PWMFrequencySet(ulBase, ulChannel, ulFrequency)

//*****************************************************************************
//
//! \brief Set the PWM frequency of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulConfig is the configuration of PWM channel' frequency.
//! Details please refer to \ref xPWM_Freq_Config.
//!
//! This function is to set the PWM frequency of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulConfig parameter is the logical OR of three values: The PreScale
//! value, The Divider value and the PWM Counter Register value.
//! Details please refer to \ref xPWM_Freq_Config_CoX.
//!
//! \note Config will not the same since diff manu,but for NUC1xx is the above
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
#define xPWMFrequencyConfig(ulBase, ulChannel, ulConfig)                      \
        PWMFrequencyConfig(ulBase, ulChannel, ulConfig)  

//*****************************************************************************
//
//! \brief get the PWM frequency of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to get the PWM frequency of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
#define xPWMFrequencyGet(ulBase, ulChannel)                                   \
        PWMFrequencyGet(ulBase, ulChannel)

//*****************************************************************************
//
//! \brief Enable the PWM output of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to enable the PWM output of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xPWMOutputEnable(ulBase, ulChannel)                                   \
        PWMOutputEnable(ulBase, ulChannel)

//*****************************************************************************
//
//! \brief Disable the PWM output of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to disable the PWM output of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xPWMOutputDisable(ulBase, ulChannel)                                  \
        PWMOutputDisable(ulBase, ulChannel) 

//*****************************************************************************
//
//! \brief Start the PWM of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to start the PWM of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xPWMStart(ulBase, ulChannel)                                          \
        PWMStart(ulBase, ulChannel)

//*****************************************************************************
//
//! \brief Stop the PWM of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to stop the PWM of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xPWMStop(ulBase, ulChannel)                                           \
        PWMStop(ulBase, ulChannel)

//*****************************************************************************
//
//! \brief Set the PWM duty of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulDuty is the duty of PWM channel.
//!
//! This function is to set the PWM duty of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulDuty parameter can be values:  duty > 0 && duty <= 100. 
//!
//! \note Duty should not be 0;
//!
//! \return None.
//
//*****************************************************************************
#define xPWMDutySet(ulBase, ulChannel, ulDuty)                                \
        PWMDutySet(ulBase, ulChannel, ulDuty)

//*****************************************************************************
//
//! \brief Get the PWM duty of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to get the PWM duty of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
//!
//! \return the Actual duty of PWM.
//
//*****************************************************************************
#define xPWMDutyGet(ulBase, ulChannel)                                        \
        PWMDutyGet(ulBase, ulChannel)

//*****************************************************************************
//
//! \brief Enable the PWM interrupt of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//! Details please refer to \ref xPWM_Int_Type.
//!
//! This function is to enable the PWM interrupt of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulIntType parameter can be values:
//! \b xPWM_INT_PWM.
//! Details please refer to \ref xPWM_Int_Type_CoX.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xPWMIntEnable(ulBase, ulChannel, ulIntType)                           \
        PWMIntEnable(ulBase, ulChannel, ulIntType)

//*****************************************************************************
//
//! \brief Disable the PWM interrupt of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//! Details please refer to \ref xPWM_Int_Type.
//!
//! This function is to disable the PWM interrupt of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulIntType parameter can be values:
//! \b xPWM_INT_PWM.
//! Details please refer to \ref xPWM_Int_Type_CoX.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xPWMIntDisable(ulBase, ulChannel, ulIntType)                          \
        PWMIntDisable(ulBase, ulChannel, ulIntType)

//*****************************************************************************
//
//! \brief Get the PWM interrupt flag of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//! Details please refer to \ref xPWM_Int_Type.
//!
//! This function is to get the PWM interrupt flag of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulIntType parameter can be values:
//! \b xPWM_INT_PWM.
//! Details please refer to \ref xPWM_Int_Type_CoX
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xPWMIntFlagGet(ulBase, ulChannel, ulIntType)                          \
        PWMIntFlagGet(ulBase, ulChannel, ulIntType)

//*****************************************************************************
//
//! \brief Init interrupts callback for the PWM timer.
//!
//! \param xtPortCallback is callback for the PWM timer.
//!
//! This function is to init interrupts callback for the PWM timer.
//!
//! \return None.
//
//*****************************************************************************
#define xPWMIntCallbackInit(ulBase, xtPWMCallback)                            \
        PWMIntCallbackInit(ulBase, xtPWMCallback)
        
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
//! \addtogroup NUC1xx_PWM
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_PWM_Int_Type  NUC1xx PWM Interrupt Type
//! \brief Values that show NUC1xx PWM Interrupt Type
//! Values that can be passed to PWMIntEnable(),PWMIntDisable().
//! @{
//
//*****************************************************************************

//
//! PWM channels Interrupt 
//
#define PWM_INT_PWM             0x00000000

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
//! \addtogroup NUC1xx_PWM_Event_Type NUC1xx PWM Event Type
//! \brief Values that show NUC1xx PWM Event Type
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
//! \addtogroup NUC1xx_PWM_Channel NUC1xx PWM Channel
//! \brief Values that show NUC1xx PWM Channel
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
//! \addtogroup NUC1xx_PWM_Clock_div NUC1xx PWM Clock Divide
//! \brief Values that show NUC1xx PWM Clock Divide
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
//! \addtogroup NUC1xx_PWM_Config NUC1xx PWM Configuration
//! \brief Values that show NUC1xx PWM Configuration
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
//! \addtogroup NUC1xx_PWM_Freq_Config NUC1xx PWM Frequency Configuration
//! \brief Values that show NUC1xx PWM Frequency Configuration
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
//! \addtogroup NUC1xx_PWM_Exported_APIs NUC1xx PWM API
//! \brief NUC1xx PWM API Reference.
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

extern xtBoolean PWMCAPClearLatchFlagOptionSelect(unsigned long ulBase,
                                                  unsigned char ucOption);
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

