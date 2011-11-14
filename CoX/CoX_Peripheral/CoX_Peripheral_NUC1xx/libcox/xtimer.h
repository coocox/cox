//*****************************************************************************
//
//! \file xtimer.h
//! \brief Prototypes for the TIMER Driver.
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

#ifndef __xTIMER_H__
#define __xTIMER_H__

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
//! \addtogroup TIMER
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Mode_Type xTIMER Mode Type 
//! \brief Values that show xTIMER Mode Type.
//! \n
//! \section xTIMER_Mode_Type_Section 1. Where to use this group
//! Values that can be passed to xTimerInitConfig() as the ulConfig parameter 
//! \n
//! \section xTIMER_Mode_Type_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Mode             |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_ONESHOT     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_PERIODIC    |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_TOGGLE      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_CONTINUOUS  |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_CAPTURE     |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_PWM         |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! The timer is operating at the one-shot mode.
//
#define xTIMER_MODE_ONESHOT     TIMER_MODE_ONESHOT

//
//! The timer is operating at the periodic mode.
//
#define xTIMER_MODE_PERIODIC    TIMER_MODE_PERIODIC

//
//! The timer is operating at the toggle mode.
//
#define xTIMER_MODE_TOGGLE      TIMER_MODE_TOGGLE

//
//! The timer is operating at continuous counting mode.
//
#define xTIMER_MODE_CONTINUOUS  TIMER_MODE_CONTINUOUS

//
//! The timer is operating as capture.
//
#define xTIMER_MODE_CAPTURE     0

//
//! The timer is operating at PWM mode.
//
#define xTIMER_MODE_PWM         0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_INT_Type xTIMER Interrupt
//! \brief Values that show xTIMER Interrupt Type.
//! \n
//! \section xTIMER_INT_Type_Section 1. Where to use this group
//! Values that can be passed to xTimerIntEnable(), xTimerIntEnable() ,
//! xTimerIntStatus(),xTimerIntClear() as ulIntFlags . 
//! \n
//! \section xTIMER_INT_Type_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Interrupt        |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xTIMER_INT_MATCH        |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_INT_CAP_EVENT    |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_INT_CAP_MATCH    |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_INT_OVERFLOW     |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_INT_PWM          |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Timer match interrupt.
//
#define xTIMER_INT_MATCH        TIMER_INT_MATCH

//
//! Timer External capture event interrupt.
//
#define xTIMER_INT_CAP_EVENT    TIMER_INT_CAP


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_INT_Event xTIMER Interrupt Event
//! \brief Values that show xTIMER Interrupt Events.
//! \n
//! \section xTIMER_INT_Event_Section 1. Where to use this group
//! Values that can be passed to xTimerIntEnable(), xTimerIntEnable() ,
//! xTimerIntStatus(),xTimerIntClear() as ulIntFlags . 
//! \n
//! \section xTIMER_INT_Event_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Interrupt        |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xTIMER_EVENT_MATCH      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_EVENT_CAP_EVENT  |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_EVENT_CAP_MATCH  |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_EVENT_OVERFLOW   |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_EVENT_PWM        |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Timer match interrupt.
//
#define xTIMER_EVENT_MATCH       0x00000001

//
//! Timer External capture event interrupt.
//
#define xTIMER_EVENT_CAP_EVENT   0x00000002


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Counter_Pase_Type xTIMER Counter Pase Type
//! \brief Values that show xTIMER Counter Pase Type.
//! \n
//! \section xTIMER_Counter_Pase_Type_Section 1. Where to use this group
//! Values that can be passed to xTimerCounterDetectPhaseSelect() as ulPhase. 
//! \n
//! \section xTIMER_Counter_Pase_Type_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Counter Pase Type|       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xTIMER_COUNTER_RISING   |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_COUNTER_FALLING  |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! A rising edge of external count pin will be counted.
//
#define xTIMER_COUNTER_RISING   TIMER_COUNTER_RISING

//
//! A falling edge of external count pin will be counted.
//
#define xTIMER_COUNTER_FALLING  TIMER_COUNTER_FALLING

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Capture_Edge_Type xTIMER Capture Edge Type
//! \brief Values that show xTIMER Capture Edge Type.
//! \n
//! \section xTIMER_Capture_Edge_Type_Section 1. Where to use this group
//! Values that can be passed to xTimerCaptureEdgeSelect() as ulPhase.
//! \n
//! \section xTIMER_Capture_Edge_Type_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Capture Edge     |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xTIMER_CAP_RISING       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_CAP_FALLING      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_CAP_BOTH         |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! a 0 to 1 transition on TEX will be detected.
//
#define xTIMER_CAP_RISING       TIMER_CAP_RISING

//
//! a 1 to 0 transition on TEX will be detected.
//
#define xTIMER_CAP_FALLING      TIMER_CAP_FALLING

//
//! either 1 to 0 or 0 to 1 transition on TEX will be detected.
//
#define xTIMER_CAP_BOTH         TIMER_CAP_BOTH

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Capture_Mode_Type xTIMER Capture Mode Type
//! \brief Values that show xTIMER Capture Mode Type.
//! \n
//! \section xTIMER_Capture_Mode_Type_Section 1. Where to use this group
//! Values that can be passed to xTimerCaptureEdgeSelect() as ulPhase.
//! \n
//! \section xTIMER_Capture_Mode_Type_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Capture Mode     |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xTIMER_CAP_MODE_CAP     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_CAP_MODE_RST     |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! TEX transition is using as the timer capture function.
//
#define xTIMER_CAP_MODE_CAP     TIMER_CAP_MODE_CAP

//
//! TEX transition is using as the timer counter reset function.
//
#define xTIMER_CAP_MODE_RST     TIMER_CAP_MODE_RST


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Count_Direction xTIMER Count Direction
//! \brief Values that show the count direction
//! \n
//! \section xTIMER_Count_Direction_Section 1. Where to use this group
//! Values that can be passed to xTimerInitConfig() as ulConfig.
//! \n
//! \section xTIMER_Count_Direction_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Count Direction  |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xTIMER_COUNT_UP         |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_COUNT_DOWN       |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! the timer counts up.
//
#define xTIMER_COUNT_UP         0

//
//! The timer counts down.
//
#define xTIMER_COUNT_DOWN       0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Count_Channel xTIMER Count Channel
//! \brief Timer Count Channels.
//! \n
//! \section xTIMER_Count_Channel_Section 1. Where to use this group
//! Values that can be passed to all XAPI as ulChannel.
//! \n
//! \section xTIMER_Count_Channel_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Count Channel    |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xTIMER_CHANNELn         |    Mandatory   |     xTIMER_CHANNEL0    |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Channel 0.
//
#define xTIMER_CHANNEL0         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Exported_APIs xTIMER API
//! \brief xTIMER API Reference.
//!
//! \section xTIMER_Exported_APIs_Port CoX Port Details
//! \verbatim
//! +------------------------------+----------------+------------------+
//! |xTIMER API                    |       CoX      |      NUC1xx      |
//! |------------------------------|----------------|------------------|
//! |xTimerInitConfig              |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerStart                   |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerStop                    |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerCounterEnable           |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerCounterDisable          |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerCaptureModeSet          |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerPrescaleSet             |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerPrescaleGet             |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerLoadSet                 |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerLoadGet                 |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerValueGet                |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerMatchSet                |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerMatchGet                |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerIntCallbackInit         |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerIntEnable               |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerIntDisable              |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerStatusGet               |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerCounterDetectPhaseSelect|    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerCaptureEdgeSelect       |    Mandatory   |         Y        |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Configurate The Timer's mode and tick frequency. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//! \param ulConfig is the mode Configuratation of the Timer port.
//! Details please refer to \ref xTIMER_Count_Direction and 
//! \ref xTIMER_Mode_Type
//! \param ulTickFreq is the tick frequency of the Timer port.
//!
//! This function is to configurate The Timer's mode and tick frequency.
//!
//! The \e ulConfig parameter is the OR value of two values:
//! - Timer's mode
//! Details please refer to \ref xTIMER_Count_Direction_CoX
//! - Timer's direction
//! Details please refer to \ref xTIMER_Mode_Type_CoX
//!
//! \b xTIMER_MODE_ONESHOT, \b xTIMER_MODE_PERIODIC, \b xTIMER_MODE_TOGGLE and
//! \b xTIMER_MODE_CONTINUOUS is the Timer's mode
//! 
//! \b xTIMER_COUNT_UP, \b xTIMER_COUNT_DOWN is the Timer's direction.
//!
//! The \e ulTickFreq parameter is the the timer tick frequency.It can be any
//! values but ulTickFreq > 0 and ulTickFreq < timer clock source.
//!
//! \note For nuc1xx,each timer only one channel.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerInitConfig(ulBase, ulChannel, ulConfig, ulTickFreq)             \
        TimerInitConfig(ulBase, ulConfig, ulTickFreq)

//*****************************************************************************
//
//! \brief Start The Timer counter. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//!
//! This function is to start The Timer counter.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerStart(ulBase, ulChannel)                                        \
        TimerStart(ulBase)

//*****************************************************************************
//
//! \brief Stop The Timer counter. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//!
//! This function is to stop The Timer counter.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerStop(ulBase, ulChannel)                                         \
        TimerStop(ulBase)

//*****************************************************************************
//
//! \brief Enable The Timer counter as a counter. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//!
//! This function is to enable The Timer counter as a counter.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerCounterEnable(ulBase, ulChannel)                                \
        TimerCounterEnable(ulBase)

//*****************************************************************************
//
//! \brief Disable The Timer counter as a counter. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//!
//! This function is to disable The Timer counter as a counter.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerCounterDisable(ulBase, ulChannel)                               \
        TimerCounterDisable(ulBase)

//*****************************************************************************
//
//! \brief Enable The Timer counter as a capture. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//! \param ulCapMode is the capture mode of the Timer port.Which can be the 
//! values: \b TIMER_CAP_MODE_CAP, \b TIMER_CAP_MODE_RST.
//! Details please refer to \ref xTIMER_Capture_Mode_Type
//!
//! This function is to enable The Timer counter as a capture.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerCaptureModeSet(ulBase, ulChannel, ulCapMode)                    \
        TimerCaptureModeSet(ulBase, ulCapMode)

//*****************************************************************************
//
//! \brief Set The Timer counter Prescale Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//! \param ulValue is the Prescale Value will be set.
//!
//! This function is to Set The Timer counter Prescale Value.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerPrescaleSet(ulBase, ulChannel, ulValue)                         \
        TimerPrescaleSet(ulBase, ulValue)

//*****************************************************************************
//
//! \brief Get The Timer counter Prescale Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//!
//! This function is to get The Timer counter Prescale Value.
//!
//! \return the Prescale Value will be get.
//
//*****************************************************************************
#define xTimerPrescaleGet(ulBase, ulChannel)                                  \
        TimerPrescaleGet(ulBase)

//*****************************************************************************
//
//! \brief Set The Timer counter Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//! \param ulValue is the Prescale Value will be set.
//!
//! This function is to Set The Timer counter Value.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerLoadSet(ulBase, ulChannel, ulValue)                             \
        0

//*****************************************************************************
//
//! \brief Get The Timer counter Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//!
//! This function is to get The Timer counter Prescale Value.
//!
//! \return the counter Value will be get.
//
//*****************************************************************************
#define xTimerLoadGet(ulBase, ulChannel)                                      \
        0

//*****************************************************************************
//
//! \brief Get The Timer counter current up timer or up event counter value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//!
//! This function is to get The Timer counter current up timer or up event
//! counter value.
//!
//! \return current up timer or up event counter value will be set.
//
//*****************************************************************************
#define xTimerValueGet(ulBase, ulChannel)                                     \
        TimerValueGet(ulBase)

//*****************************************************************************
//
//! \brief Set The Timer counter Compare Match Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//! \param ulValue is Timer counter Compare Match Value.
//!
//! This function is to Set The Timer counter Compare Match Value.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerMatchSet(ulBase, ulChannel, ulValue)                            \
        TimerMatchSet(ulBase, ulValue)

//*****************************************************************************
//
//! \brief Get The Timer counter Compare Match Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//!
//! This function is to get The Timer counter Compare Match Value.
//!
//! \return the Prescale Value will be set.
//
//*****************************************************************************
#define xTimerMatchGet(ulBase, ulChannel)                                     \
        TimerMatchGet(ulBase)

//*****************************************************************************
//
//! \brief Init interrupts callback for the timer.
//!
//! \param ulBase is the base address of the Timer port.
//! \param xtPortCallback is callback for the timer.
//!
//! Init interrupts callback for the timer.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerIntCallbackInit(ulBase, xtTimerCallback)                        \
        TimerIntCallbackInit(ulBase, xtTimerCallback)

//*****************************************************************************
//
//! \brief Enable The Timer counter interrupt. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//! \param ulIntFlags is the interrupt type of the Timer port.
//! Details please refer to \ref xTIMER_INT_Type
//!
//! This function is to enable The Timer counter interrupt.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! \b xTIMER_INT_MATCH, \b xTIMER_INT_CAP_EVENT.
//! Details please refer to \ref xTIMER_INT_Type_CoX
//!
//! \return None.
//
//*****************************************************************************
#define xTimerIntEnable(ulBase, ulChannel, ulIntFlags)                        \
        TimerIntEnable(ulBase, ulIntFlags)

//*****************************************************************************
//
//! \brief Disable The Timer counter interrupt. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//! \param ulIntFlags is the interrupt type of the Timer port.
//! Details please refer to \ref xTIMER_INT_Type.
//!
//! This function is to disable The Timer counter interrupt.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! \b xTIMER_INT_MATCH, \b xTIMER_INT_CAP_EVENT.
//! Details please refer to \ref xTIMER_INT_Type_CoX.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xTimerIntDisable(ulBase, ulChannel, ulIntFlags)                       \
        TimerIntDisable(ulBase, ulIntFlags)

//*****************************************************************************
//
//! \brief Get The Timer counter interrupt Status. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//! \param ulIntFlags is the interrupt type of the Timer port.
//! Details please refer to \ref xTIMER_INT_Type.
//!
//! This function is to disable The Timer counter interrupt.
//! 
//! The \e ulIntFlags parameter can be one of the values:
//! \b xTIMER_INT_MATCH, \b xTIMER_INT_CAP_EVENT.
//! Details please refer to \ref xTIMER_INT_Type_CoX.
//!
//! \note When use this API ,the ulIntFlags parameter one of the interrupt event
//!
//! \return the Status of The Timer counter interrupt.
//
//*****************************************************************************
#define xTimerStatusGet(ulBase, ulChannel, ulIntFlags)                        \
        TimerIntStatus(ulBase, ulIntFlags)

//*****************************************************************************
//
//! \brief Select The Timer counter detect phase. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulPhase is the counter detect phase of the Timer port.
//! Details please refer to \ref xTIMER_Counter_Pase_Type.
//! 
//! This function is to select The Timer counter detect phase.
//! 
//! The \e ulPhase parameter can be one of the values:
//! \b xTIMER_COUNTER_RISING, \b xTIMER_COUNTER_FALLING.
//! Details please refer to \ref xTIMER_Counter_Pase_Type_CoX.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xTimerCounterDetectPhaseSelect(ulBase, ulChannel, ulPhase)            \
        TimerCounterDetectPhaseSelect(ulBase, ulPhase)

//*****************************************************************************
//
//! \brief Select The Timer counter capture detect edge. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulEdge is the capture detect edge of the Timer port.
//! Details please refer to \ref xTIMER_Capture_Edge_Type.
//!
//! This function is to select The Timer counter capture detect edge.
//! 
//! The \e ulPhase parameter can be one of the values:
//! \b xTIMER_CAP_RISING, \b xTIMER_CAP_FALLING, \b xTIMER_CAP_BOTH.
//! Details please refer to \ref xTIMER_Capture_Edge_Type_CoX.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xTimerCaptureEdgeSelect(ulBase, ulChannel, ulEdge)                    \
        TimerCaptureEdgeSelect(ulBase, ulEdge)

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
//! \addtogroup NUC1xx_TIMER
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Mode_Type TIMER Mode Type
//! \brief Values that show TIMER Mode Type
//! Values that can be passed to TimerInitConfig(),TimerCounterInitConfig 
//! ().
//! @{
//
//*****************************************************************************

//
//! The timer is operating at the one-shot mode.
//
#define TIMER_MODE_ONESHOT      0x00000000

//
//! The timer is operating at the periodic mode.
//
#define TIMER_MODE_PERIODIC     0x08000000

//
//! The timer is operating at the toggle mode.
//
#define TIMER_MODE_TOGGLE       0x10000000

//
//! The timer is operating at continuous counting mode.
//
#define TIMER_MODE_CONTINUOUS   0x18000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Capture_Mode_Type TIMER Capture Mode Type
//! \brief Values that show TIMER Capture Mode Type
//! Values that can be passed to TimerCaptureModeSet() as ulCapMode .
//! @{
//
//*****************************************************************************

//
//! TEX transition is using as the timer counter reset function.
//
#define TIMER_CAP_MODE_RST      0x00000010

//
//! TEX transition is using as the timer capture function.
//
#define TIMER_CAP_MODE_CAP      0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup TIMER_INT_Type TIMER INT Type
//! \brief Values that show TIMER INT Type
//! Values that can be passed to TimerIntEnable(), TimerIntEnable() ,
//! TimerIntStatus(),TimerIntClear() as ulIntFlags .
//! @{
//
//*****************************************************************************

//
//! Timer match interrupt.
//
#define TIMER_INT_MATCH         0x20000000

//
//! Timer External capture interrupt.
//
#define TIMER_INT_CAP           0x00000020

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Counter_Pase_Type TIMER Counter Pase Type
//! \brief Values that show TIMER Counter Pase Type
//! Values that can be passed to TimerCounterDetectPhaseSelect() as ulPhase.
//! @{
//
//*****************************************************************************

//
//! A rising edge of external count pin will be counted.
//
#define TIMER_COUNTER_RISING    0x00000001

//
//! A falling edge of external count pin will be counted.
//
#define TIMER_COUNTER_FALLING   0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Capture_Edge_Type TIMER Capture Edge Type
//! \brief Values that show TIMER Capture Edge Type
//! Values that can be passed to TimerCaptureEdgeSelect() as ulPhase.
//! @{
//
//*****************************************************************************

//
//! a 0 to 1 transition on TEX will be detected.
//
#define TIMER_CAP_RISING        0x00000002

//
//! a 1 to 0 transition on TEX will be detected.
//
#define TIMER_CAP_FALLING       0x00000000

//
//! either 1 to 0 or 0 to 1 transition on TEX will be detected.
//
#define TIMER_CAP_BOTH          0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_TIMER_Exported_APIs NUC1xx TIMER API
//! \brief NUC1xx TIMER API Reference.
//! @{
//
//*****************************************************************************

extern void TimerInitConfig(unsigned long ulBase, unsigned long ulConfig,
                            unsigned long ulTickFreq);
extern void TimerCounterInitConfig(unsigned long ulBase, unsigned long ulConfig,
                       unsigned long ulCounterBound);
extern void TimerStart(unsigned long ulBase);
extern void TimerStop(unsigned long ulBase);
extern void TimerCounterEnable(unsigned long ulBase);
extern void TimerCaptureEnable(unsigned long ulBase);
extern void TimerCounterDisable(unsigned long ulBase);
extern void TimerCaptureDisable(unsigned long ulBase);
extern void TimerCaptureModeSet(unsigned long ulBase, unsigned long ulCapMode);

extern void TimerPrescaleSet(unsigned long ulBase, unsigned long ulValue);
extern unsigned long TimerPrescaleGet(unsigned long ulBase);

extern void TimerLoadSet(unsigned long ulBase, unsigned long ulValue);
extern unsigned long TimerLoadGet(unsigned long ulBase);

extern unsigned long TimerValueGet(unsigned long ulBase);
extern void TimerMatchSet(unsigned long ulBase, unsigned long ulValue);
extern unsigned long TimerMatchGet(unsigned long ulBase);

extern void TimerIntCallbackInit(unsigned long ulBase, 
                                 xtEventCallback xtTimerCallback);

extern void TimerIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void TimerIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern xtBoolean TimerIntStatus(unsigned long ulBase, 
                                unsigned long ulIntFlags);
extern void TimerIntClear(unsigned long ulBase, unsigned long ulIntFlags);
extern void TimerCounterDetectPhaseSelect(unsigned long ulBase, 
                                          unsigned long ulPhase);
extern void TimerCaptureEdgeSelect(unsigned long ulBase, unsigned long ulEdge);
extern void TimerCounterDebounceEnable(unsigned long ulBase);
extern void TimerCounterDebounceDisable(unsigned long ulBase);
extern void TimerCaptureDebounceEnable(unsigned long ulBase);
extern void TimerCaptureDebounceDisable(unsigned long ulBase);
extern void TimerExtClockFreqSet(unsigned long ulClockFreq);

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

#endif // __xTIMER_H__



