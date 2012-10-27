//*****************************************************************************
//
//! \file xpwm.h
//! \brief Prototypes for the PWM Driver.
//! \version V2.2.1.0
//! \date 8/21/2012
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
//! +------------------------+----------------+-----------+
//! |xPWM Interrupt Source   |       CoX      |    KLx    |
//! |------------------------|----------------|-----------|
//! |xPWM_INT_PWM            |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! PWM channels Interrupt 
//
#define xPWM_INT_PWM            PWM_INT_CHXF    

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
//! ulEvent parameter. User Callback function can use this to detect what 
//! event happened. 
//! \n
//! \section xPWM_Event_Type_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +------------------------+----------------+-----------+
//! |xPWM Event Source       |       CoX      |    KLx    |
//! |------------------------|----------------|-----------|
//! |xPWM_EVENT_PWM          |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWM_EVENT_CAP          |  non-Mandatory |     N     |
//! |------------------------|----------------|-----------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! The Interrupt event is PWM
//
#define xPWM_EVENT_PWM          PWM_INT_CHXF 


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
//! +------------------------+----------------+-----------+
//! |xPWM Freq Config        |       CoX      |    KLx    |
//! |------------------------|----------------|-----------|
//! |xPWM_FREQ_CONFIG(a,b,c) |    Mandatory   |     Y     |
//! |a is The Divider value  |                |           |
//! |b is The PreScale value |                |           |
//! |c is PWM Counter value  |                |           |
//! |------------------------|----------------|-----------|
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xPWM_FREQ_CONFIG(a,b,c) 0

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
//! ulMsgParam parmeter. User Callback function can use this to detect what 
//! Channel event happened. 
//! \n
//! \section xPWM_Channel_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +------------------------+----------------+-------------+
//! |xPWM Channel Number     |       CoX      |     KLx     |
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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xPWM_Config xPWM Configuration
//! Values that can be passed to PWMConfigure().
//! \n
//! \section xPWM_Config_Section 1. Where to use this group
//! Values that can be passed to xPWMInitConfigure()
//! as the ulConfig parameter. 
//! \n
//! \section xPWM_Config_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +------------------------+----------------+-----------+
//! |xPWM Config             |       CoX      |    KLx    |
//! |------------------------|----------------|-----------|
//! |xPWM_ONE_SHOT_MODE      |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWM_TOGGLE_MODE        |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWM_OUTPUT_INVERTER_EN |  Non-Mandatory |     N     |
//! |------------------------|----------------|-----------|
//! |xPWM_OUTPUT_INVERTER_DIS|  Non-Mandatory |     N     |
//! |------------------------|----------------|-----------|
//! |xPWM_DEAD_ZONE_EN       |  Non-Mandatory |     N     |
//! |------------------------|----------------|-----------|
//! |xPWM_DEAD_ZONE_DIS      |  Non-Mandatory |     N     |
//! |------------------------|----------------|-----------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! One-Shot Mode
//
#define xPWM_ONE_SHOT_MODE      PWM_CSOO_EN

//
//! Auto-reload Mode
//
#define xPWM_TOGGLE_MODE        PWM_CSOO_DIS

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
//! +------------------------+----------------+-----------+
//! |xPWM API                |       CoX      |    KLx    |
//! |------------------------|----------------|-----------|
//! |xPWMInitConfigure       |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWMFrequencySet        |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWMFrequencyConfig     |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWMFrequencyGet        |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWMOutputEnable        |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWMOutputDisable       |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWMStart               |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWMStop                |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWMDutySet             |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWMDutyGet             |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWMIntEnable           |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWMIntDisable          |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWMIntFlagGet          |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
//! |xPWMIntCallbackInit     |    Mandatory   |     Y     |
//! |------------------------|----------------|-----------|
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
//! \b xPWM_CHANNEL0, \b xPWM_CHANNEL1, \b xPWM_CHANNEL2, \b xPWM_CHANNEL3,
//! \b xPWM_CHANNEL4, \b xPWM_CHANNEL5.  
//!
//! The \e ulConfig parameter is the logical OR of four values: The PWM mode. 
//! \b xPWM_ONE_SHOT_MODE,\b xPWM_TOGGLE_MODE is the mode selecet.
//!
//! \note When Dead-Zone Generator is enabled, the pair of PWM0 and PWM1 
//! becomes a complementary pair for PWM group A and the pair of PWM4 and 
//! PWM5 becomes a complementary pair for PWM group B.
//!
//! \return None.
//
//*****************************************************************************
extern void xPWMInitConfigure(unsigned long ulBase, unsigned long ulChannel, 
                              unsigned long ulConfig);
  
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
//! \b xPWM_CHANNEL0, \b xPWM_CHANNEL1, \b xPWM_CHANNEL2, \b xPWM_CHANNEL3,
//! \b xPWM_CHANNEL4, \b xPWM_CHANNEL5. 
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
         PWMFrequencySet(ulBase, ulFrequency)

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
//! \b xPWM_CHANNEL0, \b xPWM_CHANNEL1, \b xPWM_CHANNEL2, \b xPWM_CHANNEL3,
//! \b xPWM_CHANNEL4, \b xPWM_CHANNEL5. 
//!
//! The \e ulConfig parameter is the logical OR of three values: The PreScale
//! value, The Divider value and the PWM Counter Register value.
//! Details please refer to \ref xPWM_Freq_Config_CoX.
//!
//! \note Config will not the same since diff manu,but for KLxis the above
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
#define xPWMFrequencyConfig(ulBase, ulChannel, ulConfig)                      \
        PWMFrequencyConfig(ulBase, ulConfig)  

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
//! \b xPWM_CHANNEL0, \b xPWM_CHANNEL1, \b xPWM_CHANNEL2, \b xPWM_CHANNEL3,
//! \b xPWM_CHANNEL4, \b xPWM_CHANNEL5. 
//!
//! \note None
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
#define xPWMFrequencyGet(ulBase, ulChannel)                                   \
        PWMFrequencyGet(ulBase)

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
//! \b xPWM_CHANNEL0, \b xPWM_CHANNEL1, \b xPWM_CHANNEL2, \b xPWM_CHANNEL3,
//! \b xPWM_CHANNEL4, \b xPWM_CHANNEL5. 
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xPWMOutputEnable(ulBase, ulChannel)                                   \
        PWMOutputEnable(ulBase, ulChannel, PWM_MODE_EDGE_ALIGNED1)

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
//! \b xPWM_CHANNEL0, \b xPWM_CHANNEL1, \b xPWM_CHANNEL2, \b xPWM_CHANNEL3,
//! \b xPWM_CHANNEL4, \b xPWM_CHANNEL5. 
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
//! \b xPWM_CHANNEL0, \b xPWM_CHANNEL1, \b xPWM_CHANNEL2, \b xPWM_CHANNEL3,
//! \b xPWM_CHANNEL4, \b xPWM_CHANNEL5. 
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xPWMStart(ulBase, ulChannel)                                          \
        PWMStart(ulBase)

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
//! \b xPWM_CHANNEL0, \b xPWM_CHANNEL1, \b xPWM_CHANNEL2, \b xPWM_CHANNEL3,
//! \b xPWM_CHANNEL4, \b xPWM_CHANNEL5. 
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xPWMStop(ulBase, ulChannel)                                           \
        PWMStop(ulBase)

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
//! \b xPWM_CHANNEL0, \b xPWM_CHANNEL1, \b xPWM_CHANNEL2, \b xPWM_CHANNEL3,
//! \b xPWM_CHANNEL4, \b xPWM_CHANNEL5. 
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
//! \b xPWM_CHANNEL0, \b xPWM_CHANNEL1, \b xPWM_CHANNEL2, \b xPWM_CHANNEL3,
//! \b xPWM_CHANNEL4, \b xPWM_CHANNEL5. 
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
//! \b xPWM_CHANNEL0, \b xPWM_CHANNEL1, \b xPWM_CHANNEL2, \b xPWM_CHANNEL3,
//! \b xPWM_CHANNEL4, \b xPWM_CHANNEL5. 
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
#define xPWMIntEnable(ulBase, ulChannel, ulIntType)                            \
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
//! \b xPWM_CHANNEL0, \b xPWM_CHANNEL1, \b xPWM_CHANNEL2, \b xPWM_CHANNEL3,
//! \b xPWM_CHANNEL4, \b xPWM_CHANNEL5. 
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
//! \b xPWM_CHANNEL0, \b xPWM_CHANNEL1, \b xPWM_CHANNEL2, \b xPWM_CHANNEL3,
//! \b xPWM_CHANNEL4, \b xPWM_CHANNEL5. 
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
#define xPWMIntCallbackInit(ulBase, xtPWMCallback)
        
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
//! \addtogroup KLx_PWM
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_PWM_Channel KLx PWM Channel
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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_PWM_Config KLx PWM Configuration
//! Values that can be passed to PWMInitConfigure() as the ulMode parameter.
//! @{
//
//*****************************************************************************

//
//! Edge-aligned PWM High-true pulses
//
#define PWM_MODE_EDGE_ALIGNED1  0x00000000
          
//
//! Edge-aligned PWM Low-true pulses 
//
#define PWM_MODE_EDGE_ALIGNED2  0x00000001

//
//! Center-aligned PWM High-true pulses
//
#define PWM_MODE_CENTER_ALIGNED1                                              \
                                0x00000002
                                 
//
//! Center-aligned PWM Low-true pulses
//
#define PWM_MODE_CENTER_ALIGNED2                                              \
                                0x00000003

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
                                  
//*****************************************************************************
//
//! \addtogroup KLx_PWM_Prescale KLx PWM Prescale
//! Values that can be passed to PWMFrequencyConfig() as the ulConfig parameter.
//! @{
//
//*****************************************************************************

//
//! Divide by 1
//
#define PWM_FREQUENCY_DIV1      0x00000000
          
//
//! Divide by 2
//
#define PWM_FREQUENCY_DIV2      0x00000001

//
//! Divide by 4
//
#define PWM_FREQUENCY_DIV4      0x00000002
                                 
//
//! Divide by 8
//
#define PWM_FREQUENCY_DIV8      0x00000003
                                  
//
//! Divide by 16
//
#define PWM_FREQUENCY_DIV16     0x00000004
                                  
//
//! Divide by 32
//
#define PWM_FREQUENCY_DIV32     0x00000005
                                  
//
//! Divide by 64
//
#define PWM_FREQUENCY_DIV64     0x00000006

//
//! Divide by 128
//
#define PWM_FREQUENCY_DIV128    0x00000007
                                  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_PWM_Int_Type KLx PWM Interrupt Type
//! Values that can be passed to PWMIntEnable(), PWMIntDisable(), PWMIntFlagGet(),
//! PWMIntFlagClear().
//! @{
//
//*****************************************************************************

//
//! PWM Channel x compare interrupt
//
#define PWM_INT_CHXF            0x00000001

//
//! Timer Overflow interrupt
//
#define PWM_INT_TOF             0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
                                  
//*****************************************************************************
//
//! \addtogroup KLx_PWM_Trigger_Select KLx PWM Trigger Select
//! Values that can be passed to PWMTriggerSelect().
//! @{
//
//*****************************************************************************

//
//! External trigger pin input (EXTRG_IN)
//
#define PWM_TRGSEL_EXTRGIN      0x00000000

//
//! HSCMP0 output
//
#define PWM_TRGSEL_HSCMP0       0x01000000

//
//! PIT trigger 0
//
#define PWM_TRGSEL_PITRG0       0x04000000

//
//! PIT trigger 1
//
#define PWM_TRGSEL_PITRG1       0x05000000

//
//! TPM0 overflow
//
#define PWM_TRGSEL_TPM0OF       0x08000000

//
//! TPM1 overflow
//
#define PWM_TRGSEL_TPM1OF       0x09000000

//
//! TPM2 overflow
//
#define PWM_TRGSEL_TPM2OF       0x0A000000

//
//! RTC alarm
//
#define PWM_TRGSEL_RTCALARM     0x0C000000

//
//! RTC seconds
//
#define PWM_TRGSEL_RTCSECONDS   0x0D000000

//
//! LPTMR trigger
//
#define PWM_TRGSEL_LPTMR        0x0E000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
                                  
//*****************************************************************************
//
//! \addtogroup KLx_PWM_Counter_Reload_On_Trigger  KLx PWM Counter Reload On Trigger
//! Values that can be passed to PWMCROTConfigure().
//! @{
//
//*****************************************************************************

//
//! Counter reloaded on trigger
//
#define PWM_CROT_EN             0x00040000

//
//! Counter not reloaded on trigger
//
#define PWM_CROT_DIS            0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
                                  
//*****************************************************************************
//
//! \addtogroup KLx_PWM_Counter_Stop_On_Trigger  KLx PWM Counter Stop On Trigger
//! Values that can be passed to PWMCSOOConfigure().
//! @{
//
//*****************************************************************************

//
//! Counter stop on overflow
//
#define PWM_CSOO_EN             0x00020000

//
//! Counter continues on overflow
//
#define PWM_CSOO_DIS            0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
                                  
//*****************************************************************************
//
//! \addtogroup KLx_PWM_Counter_Start_On_Trigger  KLx PWM Counter Start On Trigger
//! Values that can be passed to PWMCSOTConfigure().
//! @{
//
//*****************************************************************************

//
//! Counter start on trigger 
//
#define PWM_CSOT_EN             0x00010000

//
//! Counter start once it is enabled  
//
#define PWM_CSOT_DIS            0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************                               

//*****************************************************************************
//
//! \addtogroup KLx_PWM_Exported_APIs KLx PWM API
//! \brief KLx PWM API Reference.
//! @{
//
//*****************************************************************************
  
extern void PWMInitConfigure(unsigned long ulBase, unsigned long ulChannel, 
                                                   unsigned long ulMode);
extern void PWMStart(unsigned long ulBase);
extern void PWMStop(unsigned long ulBase);

extern unsigned long PWMFrequencySet(unsigned long ulBase, 
                                     unsigned long ulFrequency);
extern unsigned long PWMFrequencyGet(unsigned long ulBase);
extern unsigned long PWMFrequencyConfig(unsigned long ulBase, 
                                        unsigned long ulConfig);
extern void PWMOutputEnable(unsigned long ulBase, unsigned long ulChannel, 
                                      unsigned long ulMode);
extern void PWMOutputDisable(unsigned long ulBase, unsigned long ulChannel);

extern void PWMMODSet(unsigned long ulBase, unsigned long ulMODValue);
extern unsigned long PWMMODGet(unsigned long ulBase);
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

extern void PWMTriggerSelect(unsigned long ulBase, unsigned long ulTrigger);
extern void PWMCROTConfigure(unsigned long ulBase, unsigned long ulTrigger);
extern void PWMCSOOConfigure(unsigned long ulBase, unsigned long ulTrigger);
extern void PWMCSOTConfigure(unsigned long ulBase, unsigned long ulTrigger);

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

