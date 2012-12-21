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
#define xTIMER_MODE_ONESHOT     0x00000010

//
//! The timer is operating at the periodic mode.
//
#define xTIMER_MODE_PERIODIC    0x00000020

//
//! The timer is operating at the toggle mode.
//
#define xTIMER_MODE_TOGGLE      0x00000030

//
//! The timer is operating at continuous counting mode.
//
#define xTIMER_MODE_CONTINUOUS  0x00000000

//
//! The timer is operating as capture.
//
#define xTIMER_MODE_CAPTURE     0x00000040

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
#define xTIMER_INT_MATCH        TIMER_INT_UEV

//
//! Timer External capture event interrupt.
//
#define xTIMER_INT_CAP_EVENT    TIMER_INT_CH1CC | TIMER_INT_CH2CC |           \
                                TIMER_INT_CH3CC | TIMER_INT_CH4CC

//
//! Timer External capture compare interrupt.
//
#define xTIMER_INT_CAP_MATCH    TIMER_INT_CH1CC | TIMER_INT_CH2CC |           \
                                TIMER_INT_CH3CC | TIMER_INT_CH4CC

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
#define xTIMER_EVENT_MATCH

//
//! Timer External capture event interrupt.
//
#define xTIMER_EVENT_CAP_EVENT

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
#define xTIMER_COUNTER_RISING   TIMER_ICPOL_RISING

//
//! A falling edge of external count pin will be counted.
//
#define xTIMER_COUNTER_FALLING  TIMER_ICPOL_FALLING

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
#define xTIMER_CAP_RISING       TIMER_ICPOL_RISING

//
//! a 1 to 0 transition on TEX will be detected.
//
#define xTIMER_CAP_FALLING      TIMER_ICPOL_FALLING

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
#define xTIMER_CAP_MODE_CAP     0x00000001

//
//! TEX transition is using as the timer reset function.
//
#define xTIMER_CAP_MODE_RST     0x00000002

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
#define xTIMER_COUNT_UP         0x00000001

//
//! The timer counts down.
//
#define xTIMER_COUNT_DOWN       0x00000002


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
#define xTIMER_CHANNEL0         TIMER_CH_1
  
//
//! Channel 1.
//
#define xTIMER_CHANNEL1         TIMER_CH_2
  
//
//! Channel 2.
//
#define xTIMER_CHANNEL2         TIMER_CH_3
  
//
//! Channel 3.
//
#define xTIMER_CHANNEL3         TIMER_CH_4

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
extern void xTimerInitConfig(unsigned long ulBase, 
     unsigned long ulChannel, unsigned long ulConfig, unsigned long ulTickFreq);

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
#define xTimerPrescaleSet(ulBase, ulChannel, ulValue)                         \
        TimerPrescalerConfigure(ulBase, ulValue, TIMER_PSC_RLD_UPDATE)

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
        TimerPerscalerGet(ulBase)

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
#define xTimerLoadSet(ulBase, ulChannel, ulValue)                             \
        TimerAutoReloadSet(ulBase, ulValue)

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
        TimerARRReloadGet(ulBase); 

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
        TimerCounterGet(ulBase)

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
extern void xTimerMatchSet(unsigned long ulBase, unsigned long ulChannel, 
                           unsigned long ulValue);

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
extern unsigned long xTimerMatchGet(unsigned long ulBase, 
                                    unsigned long ulChannel);

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
//! \addtogroup STM32F1xx_TIMER
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup TIMER_Channel TIMER Channel
//! @{
//
//***************************************************************************** 
  
//
//! Timer channel 1
// 
#define TIMER_CH_1              1

//
//! Timer channel 2
// 
#define TIMER_CH_2              2

//
//! Timer channel 3
// 
#define TIMER_CH_3              3 
  
//
//! Timer channel 4
// 
#define TIMER_CH_4              4  
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup TIM_Capture_Compare_state Timer Capture Compare state
//! @{
//
//***************************************************************************** 
  
//
//! Capture/compare channel enable
// 
#define TIMER_CH_ENABLE         0x00000001

//
//! Capture/compare channel disable
// 
#define TIMER_CH_DISABLE        0x00000000
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIM_Capture_CompareN_state Timer Capture CompareN state
//! @{
//
//***************************************************************************** 
  
//
//! Capture/compareN channel enable
// 
#define TIMER_CHN_ENABLE        0x00000004

//
//! Capture/compareN channel disable
// 
#define TIMER_CHN_DISABLE       0x00000000
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Counter_Mode_Type TIMER counter mode
//! \brief Values that show TIMER Counter Mode Type
//! Values that can be passed to TimerBaseConfigure().
//! @{
//
//***************************************************************************** 

//
//! Edge up-counting mode
// 
#define TIMER_CNT_MODE_UP       0x00000000 
  
//
//! Center-align mode 1
// 
#define TIMER_CNT_MODE_CA1      0x00000020

//
//! Center-align mode 2
//
#define TIMER_CNT_MODE_CA2      0x00000040

//
//! Center-align mode 3
//  
#define TIMER_CNT_MODE_CA3      0x00000060
  
//
//!  Edge down-counting mode
//  
#define TIMER_CNT_MODE_DOWN     0x00000010 
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
 
//*****************************************************************************
//
//! \addtogroup TIMER_Clock_Division TIMER Clock Division
//! This bit-field indicates the division ratio between the timer clock (CK_INT) 
//! frequency and sampling clock used by the digital filters (ETR, TIx).
//! 
//! Values that can be passed to TimerCKDivConfigure().
//! @{
//
//***************************************************************************** 
  
//
//! tDTS=tCK_INT
// 
#define TIMER_CLKDIV_0          0x00000000

//
//! tDTS=2*tCK_INT
// 
#define TIMER_CLKDIV_2          0x00000100

//
//! tDTS=4*tCK_INT
// 
#define TIMER_CLKDIV_4          0x00000200
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Prescaler_Reload_Time TIMER prescaler reload time.
//! Values that can be passed to TimerBaseConfigure(), TimerPrescalerConfigure().
//! @{
//
//*****************************************************************************

//
//! Reload prescaler at next update event
// 
#define TIMER_PSC_RLD_UPDATE    0x00000000

//
//! Reload prescaler immediately 
// 
#define TIMER_PSC_RLD_IMMEDIATE 0x00000001  
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Input_Capture_Polarity TIMER Input Capture Polarity
//! Values that can be passed to TimerTIxConfigure().
//! @{
//
//*****************************************************************************

//
//! Input Capture Polarity Rising
//
#define TIMER_ICPOL_RISING      0x00000000

//
//! Input Capture Polarity Falling
//
#define TIMER_ICPOL_FALLING     0x00000002

//
//! Input Capture Polarity Both Edge
//
#define TIMER_ICPOL_BOTHEDGE    0x0000000A

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Input_Capture_Selection TIMER Input Capture Selection
//! Values that can be passed to TimerTIxConfigure().
//! @{
//
//*****************************************************************************

//
//! Input Capture Selection Direction TI
//
#define TIMER_ICSEL_DIRTI       0x00000001

//
//! Input Capture Selection InDirection TI
//
#define TIMER_ICSEL_INDIRTI     0x00000002

//
//! Input Capture Selection TRC
//
#define TIMER_ICSEL_TRC         0x00000003

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Input_Capture_Prescaler TIMER Input Capture Prescaler
//! Values that can be passed to TimerIC1PrescalerSet().
//! @{
//
//*****************************************************************************

//
//! Input Capture Prescaler1
//
#define TIMER_ICPSC_DIV1        0x00000000

//
//! Input Capture Prescaler2
//
#define TIMER_ICPSC_DIV2        0x00000004

//
//! Input Capture Prescaler4
//
#define TIMER_ICPSC_DIV4        0x00000008

//
//! Input Capture Prescaler8
//
#define TIMER_ICPSC_DIV8        0x0000000C

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Output_Compare_modes TIMER Output Compare modes
//! Values that can be passed to TimerOCxConfigure().
//! @{
//
//***************************************************************************** 
  
//
//! This mode is used to generate a timing base
// 
#define TIMER_OCMODE_TIMING     0x00000000

//
//! Active on match
// 
#define TIMER_OCMODE_ACTIVE     0x00000010

//
//! Inactive on match
// 
#define TIMER_OCMODE_INACTIVE   0x00000020

//
//! Toggle on match
//
#define TIMER_OCMODE_TOGGLE     0x00000030
 
//
//! Force Inactive
//
#define TIMER_OCMODE_FINACTIVE  0x00000040

//
//! Force active
//
#define TIMER_OCMODE_FACTIVE    0x00000050

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Output_Compare_state Output Compare/complementary Output state
//! Values that can be passed to TimerOCxConfigure().
//! @{
//
//***************************************************************************** 
  
//
//! Timer output compare state disable
// 
#define TIMER_OP_STATE_DIS      0x00000000

//
//! Timer output compare state enable
// 
#define TIMER_OP_STATE_EN       0x00000100

//
//! Timer output compare N state disable
// 
#define TIMER_OP_N_STATE_DIS    0x00000000

//
//! Timer output compare N state enable
// 
#define TIMER_OP_N_STATE_EN     0x00000400
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Output_Compare_Polarity Output Compare/complementary Output Polarity
//! Values that can be passed to TimerOCxConfigure().
//! @{
//
//***************************************************************************** 
  
//
//! Timer output compare polority high
// 
#define TIMER_OP_POL_HIGH       0x00000000

//
//! Timer output compare polority low
// 
#define TIMER_OP_POL_LOW        0x00000002

//
//! Timer output compare N polority high
// 
#define TIMER_OP_N_POL_HIGH     0x00000000

//
//! Timer output compare N polority low
// 
#define TIMER_OP_N_POL_LOW      0x00000008
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Output_Compare_Idle_State TIMER Output Compare Idle State
//! Values that can be passed to TimerOCxConfigure().
//! @{
//
//*****************************************************************************

//
//! Output Compare pin state Set during ilde state
//  
#define TIMER_OCIDLESTATE_SET   0x00000100
  
//
//! Output Compare pin state Reset during ilde state
//
#define TIMER_OCIDLESTATE_RESET 0x00000000  
    
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Output_Compare_N_Idle_State TIMER Output Compare N Idle State
//! Values that can be passed to TimerOCxConfigure().
//! @{
//
//*****************************************************************************

//
//! Output Compare N pin state Set during ilde state
//  
#define TIMER_OCNIDLESTATE_SET  0x00000200
  
//
//! Output Compare N pin state Reset during ilde state
//
#define TIMER_OCNIDLESTATE_RESET                                             \
                                0x00000000
    
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup OSSR_Off_State_Selection_for_Run_mode OSSR Off State Selection for Run mode
//! Values that can be passed to TimerBDTRConfigure().
//! @{
//
//*****************************************************************************

//
//! Off-state selection for Run mode enable
//  
#define TIMER_OSSRSTATE_ENABLE  0x00000800
  
//
//! Off-state selection for Run mode disable
//
#define TIMER_OSSRSTATE_DISABLE 0x00000000
    
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup OSSI_Off_State_Selection_for_Idle_mode_state OSSR Off State Selection for Idle mode
//! Values that can be passed to TimerBDTRConfigure().
//! @{
//
//*****************************************************************************

//
//! Off-state selection for Idle mode enable
//  
#define TIMER_OSSISTATE_ENABLE  0x00000800
  
//
//! Off-state selection for Idle mode disable
//
#define TIMER_OSSISTATE_DISABLE 0x00000000
    
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Lock_level Lock level
//! Values that can be passed to TimerBDTRConfigure().
//! @{
//
//*****************************************************************************

//
//! Timer lock lovel off
//  
#define TIMER_LOCKLEVEL_OFF     0x00000000
  
//
//! Timer lock lovel 1
//  
#define TIMER_LOCKLEVEL_1       0x00000100

//
//! Timer lock lovel 2
//  
#define TIMER_LOCKLEVEL_2       0x00000200

//
//! Timer lock lovel 3
//  
#define TIMER_LOCKLEVEL_3       0x00000300
    
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Break_Input_enable_disable Break Input enable disable
//! Values that can be passed to TimerBDTRConfigure().
//! @{
//
//*****************************************************************************

//
//! Timer break enable
//  
#define TIMER_BREAK_ENABLE      0x00001000
  
//
//! Timer break disable
//  
#define TIMER_BREAK_DISABLE     0x00000000
    
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Break_Polarity Break Polarity
//! Values that can be passed to TimerBDTRConfigure().
//! @{
//
//*****************************************************************************

//
//! Timer break polarity low
//  
#define TIMER_BREAKPOL_LOW      0x00000000
  
//
//! Timer break polarity high
//  
#define TIMER_BREAKPOL_HIGH     0x00002000
    
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup TIMER_AOE_Bit_Set_Reset TIMER AOE Bit Set Reset
//! Values that can be passed to TimerBDTRConfigure().
//! @{
//
//*****************************************************************************

//
//! TIMER AOE Bit Set enable
//  
#define TIMER_AUTOOUTPUT_ENABLE 0x00004000
  
//
//! TIMER AOE Bit Set disable
//  
#define TIMER_AUTOOUTPUT_DISABLE                                              \
                                0x00000000
    
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIM_DMA_Base_address TIMER DMA Base address
//! Values that can be passed to TimerDMAConfigure().
//! @{
//
//*****************************************************************************

//
//! Timer DMA base
//  
#define TIMER_DMABASE_CR1       0x00000000
#define TIMER_DMABASE_CR2       0x00000001
#define TIMER_DMABASE_SMCR      0x00000002
#define TIMER_DMABASE_DIER      0x00000003
#define TIMER_DMABASE_SR        0x00000004
#define TIMER_DMABASE_EGR       0x00000005
#define TIMER_DMABASE_CCMR1     0x00000006
#define TIMER_DMABASE_CCMR2     0x00000007
#define TIMER_DMABASE_CCER      0x00000008
#define TIMER_DMABASE_CNT       0x00000009
#define TIMER_DMABASE_PSC       0x0000000A
#define TIMER_DMABASE_ARR       0x0000000B
#define TIMER_DMABASE_RCR       0x0000000C
#define TIMER_DMABASE_CCR1      0x0000000D
#define TIMER_DMABASE_CCR2      0x0000000E
#define TIMER_DMABASE_CCR3      0x0000000F
#define TIMER_DMABASE_CCR4      0x00000010
#define TIMER_DMABASE_BDTR      0x00000011
#define TIMER_DMABASE_DCR       0x00000012
    
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIM_DMA_Burst_Length TIMER DMA Burst Length
//! Values that can be passed to TimerDMAConfigure().
//! @{
//
//*****************************************************************************

//
//! Timer DMA burst length
//  
#define TIMER_DMABURSTLEN_1     0x00000000
#define TIMER_DMABURSTLEN_2     0x00000100
#define TIMER_DMABURSTLEN_3     0x00000200
#define TIMER_DMABURSTLEN_4     0x00000300
#define TIMER_DMABURSTLEN_5     0x00000400
#define TIMER_DMABURSTLEN_6     0x00000500
#define TIMER_DMABURSTLEN_7     0x00000600
#define TIMER_DMABURSTLEN_8     0x00000700
#define TIMER_DMABURSTLEN_9     0x00000800
#define TIMER_DMABURSTLEN_10    0x00000900
#define TIMER_DMABURSTLEN_11    0x00000A00
#define TIMER_DMABURSTLEN_12    0x00000B00
#define TIMER_DMABURSTLEN_13    0x00000C00
#define TIMER_DMABURSTLEN_14    0x00000D00
#define TIMER_DMABURSTLEN_15    0x00000E00
#define TIMER_DMABURSTLEN_16    0x00000F00
#define TIMER_DMABURSTLEN_17    0x00001000
#define TIMER_DMABURSTLEN_18    0x00001100
    
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIM_DMA_sources TIMER DMA Source
//! Values that can be passed to TimerDMAEnable(), TimerDMADisable().
//! @{
//
//*****************************************************************************

//
//! Timer DMA burst length
//  
#define TIMER_DMA_UPDATA        0x00000100
#define TIMER_DMA_CH1CC         0x00000200
#define TIMER_DMA_CH2CC         0x00000400
#define TIMER_DMA_CH3CC         0x00000800
#define TIMER_DMA_CH4CC         0x00001000
#define TIMER_DMA_COM           0x00002000
#define TIMER_DMA_TRIGGER       0x00004000
    
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIM_External_Trigger_Prescaler Timer External Trigger Prescaler
//! Values that can be passed to TimerETRClockMode1Configure().
//! @{
//
//*****************************************************************************

//
//! Timer External Trigger Prescaler
//  
#define TIMER_EXTTRGPSC_OFF     0x00000000
#define TIMER_EXTTRGPSC_DIV2    0x00001000
#define TIMER_EXTTRGPSC_DIV4    0x00002000
#define TIMER_EXTTRGPSC_DIV8    0x00003000
    
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIM_External_Trigger_Polarity Timer External Trigger Polarity
//! Values that can be passed to TimerETRClockMode1Configure() .
//! @{
//
//*****************************************************************************

//
//! External trigger polarity inverted
//
#define TIMER_EXTTRGPOL_INVERTED                                              \
                                0x00008000

//
//! External trigger polarity Noninverted
//
#define TIMER_EXTTRGPOL_NONINVERTED                                           \
                                0x00000000  
    
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************   

//*****************************************************************************
//
//! \addtogroup TIMER_Main_output_config TIMER Main output config
//! Values that can be passed to TimerMainOutputConfigure().
//! @{
//
//*****************************************************************************

//
//! TIMER Main output enable
//  
#define TIMER_MAINOUTPUT_ENABLE 0x00000001
  
//
//! TIMER Main output disable
//  
#define TIMER_MAINOUTPUT_DISABLE                                              \
                                0x00000000
    
//*****************************************************************************
//
//! @}
//
//*****************************************************************************   
  
//*****************************************************************************
//
//! \addtogroup TIM_Forced_Action Timer Forced Action
//! Values that can be passed to TimerForcedOCxConfigure().
//! @{
//
//*****************************************************************************
  
//
//! Forced active
//
#define TIMER_FORCED_ACTIVE     0x00000050

//
//! Forced inactive
//
#define TIMER_FORCED_INACTIVE   0x00000040

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup TIMER_Slave_Trigger_Input slave trigger input selection.
//! Values that can be passed to TimerITRxExternalClockConfigure(), 
//! TimerTIxExternalClockConfigure() .
//! @{
//
//*****************************************************************************

//
//!  Internal Trigger 0 (ITR0) 
//
#define TIMER_TRSEL_ITR0        0x00000000

//
//!  Internal Trigger 1 (ITR1) 
//
#define TIMER_TRSEL_ITR1        0x00000010

//
//!  Internal Trigger 2 (ITR2) 
//
#define TIMER_TRSEL_ITR2        0x00000020

//
//!  Internal Trigger 3 (ITR3) 
//
#define TIMER_TRSEL_ITR3        0x00000030

//
//!  TI1 Edge Detector (TI1F_ED) 
//
#define TIMER_TRSEL_TI1FED      0x00000040

//
//!  Filtered Timer Input 1 (TI1FP1) 
//
#define TIMER_TRSEL_TI1FP1      0x00000050

//
//!  Filtered Timer Input 2 (TI1FP2) 
//
#define TIMER_TRSEL_TI2FP2      0x00000060

//
//!  External Trigger input (ETRF)
//
#define TIMER_TRSEL_ETRF        0x00000070  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Slave_Mode_Selection  Timer slave mode selection.
//! Values that can be passed to TimerDecoderConfig() .
//! @{
//
//*****************************************************************************

//
//! The prescaler is clocked directly by the internal clock
//
#define TIMER_SMSEL_DISABLE     0x00000000

//
//! Counter counts up/down on TI2FP2 edge depending on TI1FP1 level
//
#define TIMER_SMSEL_ENCODER1    0x00000001

//
//! Counter counts up/down on TI1FP1 edge depending on TI2FP2 level
//
#define TIMER_SMSEL_ENCODER2    0x00000002
  
//
//! Counter counts up/down on both TI1FP1 and TI2FP2 edges, depending on the level of the other input
//
#define TIMER_SMSEL_ENCODER3    0x00000003

//
//! Slave Reset Mode
//
#define TIMER_SMSEL_RESET       0x00000004

//
//! Slave Gated Mode
//
#define TIEMR_SMSEL_GATED       0x00000005

//
//! Slave trigger mode
//
#define TIMER_SMSEL_TRIGGER     0x00000006

//
//! Rising edges of the selected trigger (TRGI) clock the counter.
//  
#define TIMER_SMSEL_EXTERNAL1   0x00000007
  
//*****************************************************************************
//
//! @}
//
//***************************************************************************** 
  
//*****************************************************************************
//
//! \addtogroup TIMER_Trigger_Output_Source  Timer Trigger Output Source.
//! Values that can be passed to TimerOutputSrcSelect() .
//! @{
//
//*****************************************************************************

//
//! The UG bit in the TIM_EGR register is used as the trigger output
//  
#define TIMER_TRGOSRC_RESET     0x00000000
  
//
//! The counter enable signal is used as trigger output
//
#define TIMER_TRGOSRC_ENABLE    0x00000010

//
//! The update event is used as trigger output
//
#define TIMER_TRGOSRC_UPDATE    0x00000020 
  
//
//! Channel 0 capture or compare match occurred as trigger output
//
#define TIMER_TRGOSRC_CH1CC     0x00000030

//
//! The CH0OREF signal is used as trigger output
//								 
#define TIMER_TRGOSRC_CH1OREF   0x00000040

//
//! The CH1OREF signal is used as trigger output
//
#define TIMER_TRGOSRC_CH2OREF   0x00000050
  
//
//! The CH2OREF signal is used as trigger output
//
#define TIMER_TRGOSRC_CH3OREF   0x00000060
  
//
//! The CH3OREF signal is used as trigger output
//
#define TIMER_TRGOSRC_CH4OREF   0x00000070    
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************  
  
//*****************************************************************************
//
//! \addtogroup Auto_Reload_Preload_Enable  Auto-reload preload enable
//! Values that can be passed to TimerARRPreloadConfigure().
//! @{
//
//*****************************************************************************

//
//! Auto-reload preload enable
//
#define TIMER_ARPE_ENABLE       0x00000001

//
//! Auto-reload preload disable
//
#define TIMER_ARPE_DISABLE      0x00000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Capture_Compare_Control_Update_Selection Capture/Compare Control Update Selection
//! Values that can be passed to TimerCCUSelect().
//! @{
//
//*****************************************************************************

//
//! Auto-reload preload enable
//
#define TIMER_CCUS_ENABLE       0x00000001

//
//! Auto-reload preload disable
//
#define TIMER_CCUS_DISABLE      0x00000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Capture_Compare_DMA_Selection Capture/compare DMA selection
//! Values that can be passed to TimerCCDSelection().
//! @{
//
//*****************************************************************************

//
//! Auto-reload preload enable
//
#define TIMER_CCDS_ENABLE       0x00000001

//
//! Auto-reload preload disable
//
#define TIMER_CCDS_DISABLE      0x00000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Capture_Compare_Preloaded_Control Capture/compare preloaded control
//! Values that can be passed to TimerCCPreloadControl().
//! @{
//
//*****************************************************************************

//
//! Capture/compare preloaded control set
//
#define TIMER_CCPC_SET          0x00000001

//
//!  Capture/compare preloaded control reset
//
#define TIMER_CCPC_RESET        0x00000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIM_Output_Compare_Preload_State Timer Output Compare Preload State
//! Values that can be passed to TimerOCxPreloadConfigure().
//! @{
//
//*****************************************************************************

//
//! Output Compare preload enable
//
#define TIMER_OCPROLOAD_ENABLE  0x00000008

//
//! Output Compare preload disable
//
#define TIMER_OCPROLOAD_DISABLE 0x00000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIM_Output_Compare_Fast_State Timer Output Compare Fast State
//! Values that can be passed to TimerOCxFastConfigure().
//! @{
//
//*****************************************************************************

//
//! Output Compare preload enable
//
#define TIMER_OCFAST_ENABLE     0x00000004

//
//! Output Compare preload disable
//
#define TIMER_OCFAST_DISABLE    0x00000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIM_Output_Compare_Clear_State Timer Output Compare Clear State
//! Values that can be passed to TimerOCxRefClear().
//! @{
//
//*****************************************************************************

//
//! Output Compare Clear enable
//
#define TIMER_OCCLEAR_ENABLE    0x00000080

//
//! Output Compare Clear disable
//
#define TIMER_OCCLEAR_DISABLE   0x00000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_OREF_Clear_Configure  Timer Chx Reference Output Clear Configure
//! Values that can be passed to TimerOREFClrConfigure().
//! @{
//
//*****************************************************************************
  
//
//! CH0OREF performed normally and is not affected by the ETIF signal
// 
#define TIMER_OREF_CLEAR_DIS    0x00000000

//
//! CH0OREF is forced to 0 on the high level of the ETIF signal
// 
#define TIMER_OREF_CLEAR_EN     0x00000008  
  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIM_UpdateSource_Regular  Timer Update Source Regular
//! Values that can be passed to TimerOREFClrConfigure().
//! @{
//
//*****************************************************************************
  
//
//! Source of update is not counter overflow/underflow. 
// 
#define TIMER_UPDATESOURCE_GLOBAL                                            \
                                0x00000000

//
//! Source of update is counter overflow/underflow.
// 
#define TIMER_UPDATESOURCE_REGULAR                                           \
                                0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Update_Event_Configure  Timer Update Event Configure
//! Values that can be passed to TimerUpdateConfigure().
//! @{
//
//*****************************************************************************

//
//! Enable the update request event
// 
#define TIMER_UPDATE_EVENT_EN   0x00000000

//
//! Disable the update request event
// 
#define TIMER_UPDATE_EVENT_DIS  0x00000001
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Hall_Interface_Configure  Timer Hall Interface Configure.
//! Values that can be passed to TimerHallSensorSelect().
//! @{
//
//*****************************************************************************  

//
//! Hall interface Enable
//  
#define TIMER_HALL_INTERFACE_EN 0x00000001

//
//! Hall interface Disable
//  
#define TIMER_HALL_INTERFACE_DIS                                              \
                                0x00000000
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup TIMER_One_Pulse_Mode_Configure  Timer One Pulse Mode Configure.
//! Values that can be passed to TimerOnePulseModeConfigure().
//! @{
//
//***************************************************************************** 

//
//! Enable one pulse mode
//
#define TIMER_OPMODE_SINGLE     0x00000008

//
//! Disable one pulse mode
//
#define TIMER_OPMODE_REPETIVE   0x00000000  
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup TIMER_Sync_Configure  Timer Synchronise Configure.
//! Values that can be passed to TimerSyncConfigure().
//! @{
//
//*****************************************************************************

//
//! Timer Synchronization Enable
//  
#define TIMER_SYNC_ENABLE       0x00000080
  
//
//! Timer Synchronization Disable
//
#define TIMER_SYNC_DISABLE      0x00000000  
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Int_Definition Timer Int Definition.
//! Values that can be passed to TimerIntEnable(), TimerIntDisable().
//! @{
//
//*****************************************************************************
  
//
//! Update interrupt
//
#define TIMER_INT_UEV           0x00000001

//
//! Channel 0 capture/compare interrupt
//
#define TIMER_INT_CH1CC         0x00000002

//
//! Channel 1 capture/compare interrupt
//
#define TIMER_INT_CH2CC         0x00000004

//
//! Channel 2 capture/compare interrupt
//
#define TIMER_INT_CH3CC         0x00000008

//
//! Channel 3 capture/compare interrupt
//
#define TIMER_INT_CH4CC         0x00000010

//
//! COM interrupt 
//
#define TIMER_INT_COM           0x00000020

//
//! Trigger interrupt
//
#define TIMER_INT_TEV           0x00000040
  
//
//! Break interrupt
//
#define TIMER_INT_BRK           0x00000080
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************  
  
//*****************************************************************************
//
//! \addtogroup TIMER_Event_Source Timer Event Source.
//! Values that can be passed to TimerEventGenerate().
//! @{
//
//*****************************************************************************

//
//! Update event
//
#define TIMER_EVENT_UEV         0x00000001

//
//! Channel 1 capture/compare event
//
#define TIMER_EVENT_CH1CC       0x00000002
  
//
//! Channel 2 capture/compare event
//
#define TIMER_EVENT_CH2CC       0x00000004
  
//
//! Channel 3 capture/compare event
//
#define TIMER_EVENT_CH3CC       0x00000008

//
//! Channel 4 capture/compare event
//
#define TIMER_EVENT_CH4CC       0x00000010

//
//! COM event
//
#define TIMER_EVENT_COM         0x00000020  

//
//! Trigger event
//
#define TIMER_EVENT_TEV         0x00000040  

//
//! Break event
//
#define TIMER_EVENT_BRK         0x00000080
 
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Flag_Status Timer FLAG Definitions.
//! Values that can be passed to TimerFlagStatusGet().
//! @{
//
//*****************************************************************************

//
//! Update flag
//
#define TIMER_FLAG_UPDATE       0x00000001

//
//! Channel 1 capture/compare flag
//
#define TIMER_FLAG_CH1CC        0x00000002

//
//! Channel 2 capture/compare flag
//
#define TIMER_FLAG_CH2CC        0x00000004

//
//! Channel 3 capture/compare flag
//
#define TIMER_FLAG_CH3CC        0x00000008

//
//! Channel 4 capture/compare flag
//
#define TIMER_FLAG_CH4CC        0x00000010

//
//!  COM flag
//
#define TIMER_FLAG_COM          0x00000020  

//
//! Trigger flag
//
#define TIMER_FLAG_TRIGGER      0x00000040

//
//! Break flag
//
#define TIMER_FLAG_BREAK        0x00000080  

//
//! Channel 1 over capture flag
//
#define TIMER_FLAG_CH1OF        0x00000200

//
//! Channel 2 over capture flag
//
#define TIMER_FLAG_CH2OF        0x00000400
  
//
//! Channel 3 over capture flag
//
#define TIMER_FLAG_CH3OF        0x00000800
  
//
//! Channel 4 over capture flag
//
#define TIMER_FLAG_CH4OF        0x00001000
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************  
  
//*****************************************************************************
//
//! \addtogroup STM32F1xx_TIMER_Exported_APIs STM32F1xx TIMER API
//! \brief STM32F1xx TIMER API Reference.
//! @{
//
//*****************************************************************************

extern void TimerBaseConfigure(unsigned long ulBase, unsigned long ulCountMode, 
                              unsigned long ulCRRValue, unsigned long ulPrescaler, 
					          unsigned long ulCLKDiv, unsigned long ulRepCnt);
extern void TimerOC1Configure(unsigned long ulBase, unsigned long ulOutputMode, 
                              unsigned long ulOCompare,unsigned long ulOCCfg, 
				              unsigned long ulOCNCfg, unsigned long ulOCIdleCfg);
extern void TimerOC2Configure(unsigned long ulBase, unsigned long ulOutputMode, 
                              unsigned long ulOCompare,unsigned long ulOCCfg, 
		                      unsigned long ulOCNCfg, unsigned long ulOCIdleCfg);
extern void TimerOC3Configure(unsigned long ulBase, unsigned long ulOutputMode, 
                              unsigned long ulOCompare,unsigned long ulOCCfg, 
					          unsigned long ulOCNCfg, unsigned long ulOCIdleCfg);
extern void TimerOC4Configure(unsigned long ulBase, unsigned long ulOutputMode, 
                              unsigned long ulOCompare,unsigned long ulOCCfg, 
		                      unsigned long ulOCNCfg, unsigned long ulOCIdleCfg);
extern void TimerIC1PrescalerSet(unsigned long ulBase, unsigned long ulPrescaler);
extern void TimerIC2PrescalerSet(unsigned long ulBase, unsigned long ulPrescaler);
extern void TimerIC3PrescalerSet(unsigned long ulBase, unsigned long ulPrescaler);
extern void TimerIC4PrescalerSet(unsigned long ulBase, unsigned long ulPrescaler);
extern void TimerICConfigure(unsigned long ulBase, unsigned long ulChannel, 
                             unsigned long ulICPolarity, unsigned long ulICSelection, 
				             unsigned long ulPrescaler, unsigned long ulICFilter);
extern void TimerBDTRConfigure(unsigned long ulBase, unsigned long ulBDTRConfig);
extern void TimerMainOutputConfigure(unsigned long ulBase, unsigned long ulMOConfigure);

extern void TimerStart(unsigned long ulBase);
extern void TimerStop(unsigned long ulBase);
extern void TimerDMAEnable(unsigned long ulBase, unsigned long ulDMASource);
extern void TimerDMADisable(unsigned long ulBase, unsigned long ulDMASource);

extern void TimerInternalClkConfigure(unsigned long ulBase);
extern void TimerInputTriggerSelect(unsigned long ulBase, 
                                    unsigned long ulInputTriggerSource);
extern void TimerTIxExternalClockConfigure(unsigned long ulBase, unsigned long ulExtClkSource,
                         unsigned long ulICPolarity, unsigned long ulICFilter);
extern void TimerETRClockMode1Configure(unsigned long ulBase, 
                            unsigned long ulExtTRGPrescaler,
                            unsigned long ulExtTRGPloarity, 
							unsigned long ulExtTRGFilter);
extern void TimerETRClockMode2Configure(unsigned long ulBase, 
                            unsigned long ulExtTRGPrescaler,
                            unsigned long ulExtTRGPloarity, 
							unsigned long ulExtTRGFilter);
extern void TimerETRConfigure(unsigned long ulBase, unsigned long ulExtTRGPrescaler, 
                      unsigned long ulExtTRGPolarity, unsigned long ulExtTRGFilter);

extern void TimerCNTModeConfigure(unsigned long ulBase, unsigned long ulCountMode);
extern void TimerEncoderInterfaceConfigure(unsigned long ulBase, unsigned long ulEncoderMode,
                              unsigned long ulIC1Polarity, unsigned long ulIC2Polarity);
extern void TimerForcedOC1Configure(unsigned long ulBase, unsigned long ulForcedAction);
extern void TimerForcedOC2Configure(unsigned long ulBase, unsigned long ulForcedAction);
extern void TimerForcedOC3Configure(unsigned long ulBase, unsigned long ulForcedAction);
extern void TimerForcedOC4Configure(unsigned long ulBase, unsigned long ulForcedAction);

extern void TimerCCUSelect(unsigned long ulBase, unsigned long ulCCUSelect);
extern void TimerCCDSelect(unsigned long ulBase, unsigned long ulCCDSelect);
extern void TimerCCPreloadControl(unsigned long ulBase, unsigned long ulCCPreload);
extern void TimerOC1PreloadConfigure(unsigned long ulBase, unsigned long ulOCPreload);
extern void TimerOC2PreloadConfigure(unsigned long ulBase, unsigned long ulOCPreload);
extern void TimerOC3PreloadConfigure(unsigned long ulBase, unsigned long ulOCPreload);
extern void TimerOC4PreloadConfigure(unsigned long ulBase, unsigned long ulOCPreload);

extern void TimerOC1FastConfigure(unsigned long ulBase, unsigned long ulOCFast);
extern void TimerOC2FastConfigure(unsigned long ulBase, unsigned long ulOCFast);
extern void TimerOC3FastConfigure(unsigned long ulBase, unsigned long ulOCFast);
extern void TimerOC4FastConfigure(unsigned long ulBase, unsigned long ulOCFast);

extern void TimerOCxRefClear(unsigned long ulBase, unsigned long ulChannel, 
                             unsigned long ulOCClear);
extern void TimerOC1PolarityConfigure(unsigned long ulBase, unsigned long ulPolarity);
extern void TimerOC1NPolarityConfigure(unsigned long ulBase, unsigned long ulPolarity);
extern void TimerOC2PolarityConfigure(unsigned long ulBase, unsigned long ulPolarity);
extern void TimerOC2NPolarityConfigure(unsigned long ulBase, unsigned long ulPolarity);
extern void TimerOC3PolarityConfigure(unsigned long ulBase, unsigned long ulPolarity);
extern void TimerOC3NPolarityConfigure(unsigned long ulBase, unsigned long ulPolarity);
extern void TimerOC4PolarityConfigure(unsigned long ulBase, unsigned long ulPolarity);

extern void TimerCHConfigure(unsigned long ulBase, unsigned long ulChannel, 
                             unsigned long ulCCx);
extern void TimerCHNConfigure(unsigned long ulBase, unsigned long ulChannel, 
                              unsigned long ulCCxN);

extern void TimerOCxModeSelect(unsigned long ulBase, unsigned long ulChannel, 
                             unsigned long ulOutputMode);
extern void TimerUpdateConfigure(unsigned long ulBase, unsigned long ulUpdate);
extern void TimerUpdateRequestConfigure(unsigned long ulBase, unsigned long ulUpdateSource);
extern void TimerOnePulseModeConfigure(unsigned long ulBase, unsigned long ulOPMode);
extern void TimerOutputSrcSelect(unsigned long ulBase, unsigned long ulSelect);
extern void TimerSlaveModeConfigure(unsigned long ulBase, unsigned long ulSelect);
extern void TimerSyncConfigure(unsigned long ulBase, unsigned long ulConfigure);

extern void TimerPrescalerConfigure(unsigned long ulBase, unsigned long ulPrescale,
                                    unsigned long ulPSCReloadTime);
extern unsigned long TimerPerscalerGet(unsigned long ulBase);
extern void TimerCounterSet(unsigned long ulBase, unsigned long ulCounter);
extern unsigned long TimerCounterGet(unsigned long ulBase);
extern void TimerARRPreloadConfigure(unsigned long ulBase, unsigned long ulARRProload);
extern void TimerAutoReloadSet(unsigned long ulBase, unsigned long ulARRValue);
extern unsigned long TimerARRReloadGet(unsigned long ulBase);

extern void TimerCompare1Set(unsigned long ulBase, unsigned long ulCompare1);
extern void TimerCompare2Set(unsigned long ulBase, unsigned long ulCompare2);
extern void TimerCompare3Set(unsigned long ulBase, unsigned long ulCompare3);
extern void TimerCompare4Set(unsigned long ulBase, unsigned long ulCompare4);
extern unsigned long TimerCapture1Get(unsigned long ulBase);
extern unsigned long TimerCapture2Get(unsigned long ulBase);
extern unsigned long TimerCapture3Get(unsigned long ulBase);
extern unsigned long TimerCapture4Get(unsigned long ulBase);

extern void TimerCKDivConfigure(unsigned long ulBase, unsigned long ulDiv);
extern xtBoolean TimerFlagStatusGet(unsigned long ulBase, unsigned long ulFlag);
extern void TimerFlagStatusClear(unsigned long ulBase, unsigned long ulFlag);
extern void TimerIntCallbackInit(unsigned long ulBase, unsigned long ulIntType,
                     xtEventCallback xtTimerCallback);

extern void TimerEventGenerate(unsigned long ulBase, unsigned long ulEvent);
extern void TimerIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void TimerIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern xtBoolean TimerIntStatus(unsigned long ulBase, unsigned long ulIntFlags);
extern void TimerIntClear(unsigned long ulBase, unsigned long ulIntFlags);

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



