//*****************************************************************************
//
//! \file xtimer.h
//! \brief Prototypes for the TIMER Driver.
//! \version V2.2.1.0
//! \date 6/12/2012
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

#include "timer.h"
#include "CoX_base.h"

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
//! \addtogroup CoX_Peripheral_Interface
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
//! |xTIMER Mode             |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_ONESHOT     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_PERIODIC    |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_TOGGLE      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_CONTINUOUS  |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_CAPTURE     |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_PWM         |  Non-Mandatory |            Y           |
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
#define xTIMER_MODE_CAPTURE     TIMER_MODE_CAPTURE

//
//! The timer is operating at PWM mode.
//
#define xTIMER_MODE_PWM         TIMER_MODE_PWM


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
//! Values that can be passed to xTimerIntEnable(), xTimerIntDisable() ,
//! xTimerIntStatus(),xTimerIntClear() as ulIntFlags . 
//! \n
//! \section xTIMER_INT_Type_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Interrupt        |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xTIMER_INT_MATCH        |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_INT_CAP_EVENT    |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_INT_CAP_MATCH    |  Non-Mandatory |            Y           |
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
#define xTIMER_INT_CAP_EVENT    TIMER_INT_CAP_EVENT

//
//! Timer External capture compare interrupt.
//
#define xTIMER_INT_CAP_MATCH    TIMER_INT_CAP_MATCH

//
//! Timer overflow interrupt.
//
#define xTIMER_INT_OVERFLOW     TIMER_INT_OVERFLOW

//
//! Timer PWM interrupt.
//
#define xTIMER_INT_PWM          TIMER_INT_PWM

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
//! Values that can be passed to xTimerIntEnable(), xTimerIntDisable(),
//! xTimerIntStatus(),xTimerIntClear() as ulIntFlags . 
//! \n
//! \section xTIMER_INT_Event_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Interrupt        |       CoX      |         STM32F1xx      |
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
#define xTIMER_EVENT_MATCH      TIMER_EVENT_MATCH

//
//! Timer External capture event interrupt.
//
#define xTIMER_EVENT_CAP_EVENT  TIMER_EVENT_CAP_EVENT

//
//! Timer External capture match interrupt.
//
#define xTIMER_EVENT_CAP_MATCH  TIMER_EVENT_CAP_MATCH

//
//! Timer External capture event interrupt.
//
#define xTIMER_EVENT_OVERFLOW   TIMER_EVENT_OVERFLOW

//
//! Timer PWM interrupt.
//
#define xTIMER_EVENT_PWM        TIMER_EVENT_PWM

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
//! |xTIMER Counter Pase Type|       CoX      |         STM32F1xx      |
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
//! |xTIMER Capture Edge     |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xTIMER_CAP_RISING       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_CAP_FALLING      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_CAP_BOTH         |  Non-Mandatory |            N           |
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
//! a 1 to 0 transition on TEX will be detected.
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
//! |xTIMER Capture Mode     |       CoX      |         STM32F1xx      |
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
//! TEX transition is using as the timer reset function.
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
//! |xTIMER Count Direction  |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xTIMER_COUNT_UP         |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_COUNT_DOWN       |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! the timer counts up.
//
#define xTIMER_COUNT_UP         TIMER_COUNT_UP

//
//! The timer counts down.
//
#define xTIMER_COUNT_DOWN       TIMER_COUNT_DOWN


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
//! Values that can be passed to all xAPI as ulChannel.
//! \n
//! \section xTIMER_Count_Channel_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Count Channel    |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xTIMER_CHANNELn         |    Mandatory   |     xTIMER_CHANNEL0    |
//! |                        |                |     xTIMER_CHANNEL1    |
//! |                        |                |     xTIMER_CHANNEL2    |
//! |                        |                |     xTIMER_CHANNEL3    |  
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Channel 0.
//
#define xTIMER_CHANNEL0         TIMER_CHANNEL0
  
//
//! Channel 1.
//
#define xTIMER_CHANNEL1         TIMER_CHANNEL1
  
//
//! Channel 2.
//
#define xTIMER_CHANNEL2         TIMER_CHANNEL2
  
//
//! Channel 3.
//
#define xTIMER_CHANNEL3         TIMER_CHANNEL3 

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
//! |xTIMER API                    |       CoX      |      STM32F1xx   |
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
//! +------------------------------+----------------+------------------+
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
//! \b xTIMER_MODE_CONTINUOUS , \b xTIMER_MODE_CAPTURE is the Timer's mode
//! 
//! \b xTIMER_COUNT_UP, \b xTIMER_COUNT_DOWN is the Timer's direction.
//!
//! The \e ulTickFreq parameter is the the timer tick frequency.It can be any
//! values but ulTickFreq > 0 and ulTickFreq < timer clock source.
//!
//! \note For STM32F1xx,each timer only one channel.
//!
//! \return None.
//
//*****************************************************************************
extern void xTimerInitConfig(unsigned long ulBase,  unsigned long ulChannel,
                       unsigned long ulConfig, unsigned long ulTickFreq);

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
extern void xTimerStart(unsigned long ulBase, unsigned long ulChannel);

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
extern void xTimerStop(unsigned long ulBase, unsigned long ulChannel);

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
extern void xTimerCounterEnable(unsigned long ulBase, unsigned long ulChannel);

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
extern void xTimerCounterDisable(unsigned long ulBase, unsigned long ulChannel);

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
extern void xTimerCaptureModeSet(unsigned long ulBase, unsigned long ulChannel,
		                         unsigned long ulCapMode);

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
extern void xTimerPrescaleSet(unsigned long ulBase, unsigned long ulChannel,
		                      unsigned long ulValue);

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
extern void xTimerPrescaleGet(unsigned long ulBase, unsigned long ulChannel);

//*****************************************************************************
//
//! \brief Set The Timer counter Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//! \param ulValue is the Proload Value will be set.
//!
//! This function is to Set The Timer counter Value.
//!
//! \return None.
//
//*****************************************************************************
extern void xTimerLoadSet(unsigned long ulBase, unsigned long ulChannel,
		                  unsigned long ulValue);

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
extern void xTimerLoadGet(unsigned long ulBase, unsigned long ulChannel);

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
extern unsigned long xTimerValueGet(unsigned long ulBase, unsigned long ulChannel);

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
extern void xTimerMatchSet(unsigned long ulBase, unsigned long ulChannel, unsigned long ulValue);

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
extern unsigned long xTimerMatchGet(unsigned long ulBase, unsigned long ulChannel);

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
extern void xTimerIntCallbackInit(unsigned long ulBase, 
                                  xtEventCallback xtTimerCallback);

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
extern void xTimerIntEnable(unsigned long ulBase, unsigned long ulChannel,
                            unsigned long ulIntFlags);

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
extern void xTimerIntDisable(unsigned long ulBase, unsigned long ulChannel,
                              unsigned long ulIntFlags);

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
extern xtBoolean xTimerStatusGet(unsigned long ulBase, unsigned long ulChannel,
                                 unsigned long ulIntFlags);

//*****************************************************************************
//
//! \brief Select The Timer counter detect phase. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
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
extern void xTimerCounterDetectPhaseSelect(unsigned long ulBase, 
                               unsigned long ulChannel, unsigned long ulPhase);

//*****************************************************************************
//
//! \brief Select The Timer counter capture detect edge. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! \param ulEdge is the capture detect edge of the Timer port.
//! Details please refer to \ref xTIMER_Capture_Edge_Type.
//!
//! This function is to select The Timer counter capture detect edge.
//! 
//! The \e ulPhase parameter can be one of the values:
//! \b xTIMER_CAP_RISING, \b xTIMER_CAP_FALLING.
//! Details please refer to \ref xTIMER_Capture_Edge_Type_CoX.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
extern void xTimerCaptureEdgeSelect(unsigned long ulBase, unsigned long ulChannel,
                                    unsigned long ulEdge);

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
