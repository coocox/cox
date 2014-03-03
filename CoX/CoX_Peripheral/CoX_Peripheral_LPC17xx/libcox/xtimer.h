//*****************************************************************************
//
//! \file      xtimer.h
//! \brief     Prototypes for the TIMER Driver.
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

#ifndef __XTIMER_H__
#define __XTIMER_H__

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
//! \brief      Values that show xTIMER Mode Type.
//!
//! \section    xTIMER_Mode_Type_Section 1. Where to use this group
//!             Values that can be passed to xTimerInitConfig() as the ulConfig
//!             parameter.
//!
//! \section    xTIMER_Mode_Type_CoX 2. CoX Port Details
//!
//! |  xTIMER Mode             |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xTIMER_MODE_ONESHOT     |    Mandatory   |            Y           |
//! |  xTIMER_MODE_PERIODIC    |    Mandatory   |            Y           |
//! |  xTIMER_MODE_TOGGLE      |    Mandatory   |            N           |
//! |  xTIMER_MODE_CONTINUOUS  |  Non-Mandatory |            Y           |
//! |  xTIMER_MODE_CAPTURE     |  Non-Mandatory |            Y           |
//!
//! @{
//
//*****************************************************************************

//
//! The timer is operating at the one-shot mode.
//
#define xTIMER_MODE_ONESHOT     BIT_32_0

//
//! The timer is operating at the periodic mode.
//
#define xTIMER_MODE_PERIODIC    BIT_32_1

//
//! The timer is operating at continuous counting mode.
//
#define xTIMER_MODE_CONTINUOUS  BIT_32_2

//
//! The timer is operating as capture.
//
#define xTIMER_MODE_CAPTURE     BIT_32_3

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_INT_Type xTIMER Interrupt
//! \brief      Values that show xTIMER Interrupt Type.
//!
//! \section    xTIMER_INT_Type_Section 1. Where to use this group
//!             Values that can be passed to
//!             - \ref xTimerIntEnable()
//!             - \ref xTimerIntDisable()
//!             - \ref xTimerIntStatus()
//!             - \ref xTimerIntClear()
//!             as ulIntFlags.
//!
//! \section    xTIMER_INT_Type_CoX 2. CoX Port Details
//!
//! |  xTIMER Interrupt        |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xTIMER_INT_MATCH        |    Mandatory   |            Y           |
//! |  xTIMER_INT_CAP_EVENT    |    Mandatory   |            Y           |
//!
//! @{
//
//*****************************************************************************

//
//! Timer match interrupt.
//
#define xTIMER_INT_MATCH        BIT_32_0

//
//! Timer External capture event interrupt.
//
#define xTIMER_INT_CAP_EVENT    BIT_32_1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_INT_Event xTIMER Interrupt Event
//! \brief      Values that show xTIMER Interrupt Events.
//!
//! \section    xTIMER_INT_Event_Type_Section 1. Where to use this group
//!             Values that can be passed to
//!             - \ref xTimerIntEnable(),
//!             - \ref xTimerIntDisable() ,
//!             - \ref xTimerIntStatus(),
//!             - \ref xTimerIntClear() as ulIntFlags.
//!
//! \section    xTIMER_INT_Event_CoX 2. CoX Port Details
//!
//! |  xTIMER Interrupt        |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xTIMER_EVENT_MATCH      |    Mandatory   |            Y           |
//! |  xTIMER_EVENT_CAP_EVENT  |    Mandatory   |            Y           |
//!
//! @{
//
//*****************************************************************************

//
//! Timer match interrupt.
//
#define xTIMER_EVENT_MATCH      BIT_32_0

//
//! Timer External capture event interrupt.
//
#define xTIMER_EVENT_CAP_EVENT  BIT_32_1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Counter_Phase_Type xTIMER Counter Phase Type
//! \brief      Values that show xTIMER Counter Phase Type.
//!
//! \section    xTIMER_Counter_Phase_Type_Section 1. Where to use this group
//!             Values that can be passed to xTimerCounterDetectPhaseSelect() as
//!             ulPhase.
//!
//! \section    xTIMER_Counter_Phase_Type_CoX     2. CoX Port Details
//!
//! |  xTIMER Counter Pase Type  |       CoX      |         LPC17xx        |
//! |----------------------------|----------------|------------------------|
//! |  xTIMER_COUNTER_RISING     |    Mandatory   |            Y           |
//! |  xTIMER_COUNTER_FALLING    |    Mandatory   |            Y           |
//!
//! @{
//
//*****************************************************************************

//
//! A rising edge of external count pin will be counted.
//
#define xTIMER_COUNTER_RISING   BIT_32_0

//
//! A falling edge of external count pin will be counted.
//
#define xTIMER_COUNTER_FALLING  BIT_32_1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Capture_Edge_Type xTIMER Capture Edge Type
//! \brief      Values that show xTIMER Capture Edge Type.
//! \n
//! \section    xTIMER_Capture_Edge_Type_Section 1. Where to use this group
//!             Values that can be passed to xTimerCaptureEdgeSelect() as ulPhase.
//! \n
//! \section    xTIMER_Capture_Edge_Type_CoX     2. CoX Port Details
//!
//! |  xTIMER Capture Edge     |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xTIMER_CAP_RISING       |    Mandatory   |            Y           |
//! |  xTIMER_CAP_FALLING      |    Mandatory   |            Y           |
//! |  xTIMER_CAP_BOTH         |  Non-Mandatory |            Y           |
//!
//! @{
//
//*****************************************************************************

//
//! a 0 to 1 transition on capture pin will be detected.
//
#define xTIMER_CAP_RISING       TIMER_CFG_CNT_CAP0_RISING

//
//! a 1 to 0 transition on capture pin will be detected.
//
#define xTIMER_CAP_FALLING      TIMER_CFG_CNT_CAP0_RISING

//
//! Any transition on capture pin will be detected.
//
#define xTIMER_CAP_BOTH         (TIMER_CFG_CNT_CAP0_RISING | TIMER_CFG_CNT_CAP0_RISING)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Capture_Mode_Type xTIMER Capture Mode Type
//! \brief      Values that show xTIMER Capture Mode Type.
//!
//! \section    xTIMER_Capture_Mode_Type_Section 1. Where to use this group
//!             Values that can be passed to \ref xTimerCaptureModeSet as ulPhase.
//!
//! \section    xTIMER_Capture_Mode_Type_CoX     2. CoX Port Details
//!
//! |  xTIMER Capture Mode   |       CoX      |         LPC17xx        |
//! |------------------------|----------------|------------------------|
//! |  xTIMER_CAP_MODE_CAP   |    Mandatory   |            Y           |
//!
//! @{
//
//*****************************************************************************

//
//! TEX transition is using as the timer capture function.
//
#define xTIMER_CAP_MODE_CAP     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Count_Direction xTIMER Count Direction
//! \brief      Values that show the count direction
//!
//! \section    xTIMER_Count_Direction_Section 1. Where to use this group
//!             Values that can be passed to xTimerInitConfig() as ulConfig.
//!
//! \section    xTIMER_Count_Direction_CoX     2. CoX Port Details
//!
//! |  xTIMER Count Direction  |       CoX       |         LPC17xx        |
//! |--------------------------|-----------------|------------------------|
//! |  xTIMER_COUNT_UP         |    Mandatory    |            Y           |
//!
//! @{
//
//*****************************************************************************

//
//! the timer counts up.
//! When overrun, timer will wrapback to 0.
//
#define xTIMER_COUNT_UP         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Count_Channel xTIMER Count Channel
//! \brief      Timer Count Channels.
//!
//! \section    xTIMER_Count_Channel_Section 1. Where to use this group
//!             Values that can be passed to all xAPI as ulChannel.
//!
//! \section    xTIMER_Count_Channel_CoX     2. CoX Port Details
//!
//! |  xTIMER Count Channel    |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xTIMER_CHANNELn         |    Mandatory   |     xTIMER_CHANNEL0    |
//! |                          |                |     xTIMER_CHANNEL1    |
//!
//! \note       For LPC17xx Timer, there is one timer unit with four match channel
//!             two input capture channel. however, you can not use four channel
//!             at the same time, so, we only use one match channel(xTIMER_CHANNEL0)
//!             and one input capture channel(xTIMER_CHANNEL1).
//!
//! @{
//
//*****************************************************************************

//
//! Channel 0 is general timer channel.
//
#define xTIMER_CHANNEL0         TIMER_MAT_CH_0

//
//! Channel 1 is input capture channel.
//
#define xTIMER_CHANNEL1         TIMER_CAP_CH_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Exported_APIs xTIMER API
//! \brief      xTIMER API Reference.
//!
//! \section    xTIMER_Exported_APIs_Port CoX Port Details
//!
//! |      xTIMER API                     |       CoX      |      LPC17xx     |
//! |-------------------------------------|----------------|------------------|
//! | \ref xTimerInitConfig               |    Mandatory   |         Y        |
//! | \ref xTimerStart                    |    Mandatory   |         Y        |
//! | \ref xTimerStop                     |    Mandatory   |         Y        |
//! | \ref xTimerCounterEnable            |    Mandatory   |         Y        |
//! | \ref xTimerCounterDisable           |    Mandatory   |         Y        |
//! | \ref xTimerPrescaleSet              |    Mandatory   |         Y        |
//! | \ref xTimerPrescaleGet              |    Mandatory   |         Y        |
//! | \ref xTimerLoadSet                  |    Mandatory   |         Y        |
//! | \ref xTimerLoadGet                  |    Mandatory   |         Y        |
//! | \ref xTimerValueGet                 |    Mandatory   |         Y        |
//! | \ref xTimerMatchSet                 |    Mandatory   |         Y        |
//! | \ref xTimerMatchGet                 |    Mandatory   |         Y        |
//! | \ref xTimerIntCallbackInit          |    Mandatory   |         Y        |
//! | \ref xTimerIntEnable                |    Mandatory   |         Y        |
//! | \ref xTimerIntDisable               |    Mandatory   |         Y        |
//! | \ref xTimerStatusGet                |    Mandatory   |         Y        |
//! | \ref xTimerCounterDetectPhaseSelect |    Mandatory   |         Y        |
//! | \ref xTimerCaptureModeSet           |    Mandatory   |         Y        |
//! | \ref xTimerCaptureEdgeSelect        |    Mandatory   |         Y        |
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief  Configurate The Timer's mode and tick frequency.
//!         This function is to configurate The Timer's mode and tick frequency.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              Can be one of the following value:
//!              - \ref xTIMER0_BASE
//!              - \ref xTIMER1_BASE
//!              - \ref xTIMER2_BASE
//!              - \ref xTIMER3_BASE
//!
//! \param  [in] ulChannel is the channel of the Timer port.
//!              Can be one of the following value:
//!              - \ref xTIMER_CHANNEL0 is timer channel.
//!              - \ref xTIMER_CHANNEL1 is capture channel.
//!
//! \param  [in] ulConfig is the mode Configuratation of the Timer port.
//!              Can be one of the following value:
//!              - Timer mode
//!                  - \ref xTIMER_MODE_ONESHOT
//!                  - \ref xTIMER_MODE_PERIODIC
//!                  - \ref xTIMER_MODE_CONTINUOUS
//!                  - \ref xTIMER_MODE_CAPTURE
//!              - Timer counter direction
//!                  - \ref xTIMER_COUNT_UP
//!
//! \param  [in] ulTickFreq is the tick frequency of the Timer port.
//!
//! \return None.
//!
//! \note   For LPC17xx, Only xTIMER_CHANNEL1 can be configure into Capture mode.
//
//*****************************************************************************
extern void TimerInitConfig(unsigned long ulBase, unsigned long ulChannel,
        unsigned long ulConfig, unsigned long ulTickFreq);

//*****************************************************************************
//
//! \brief Start The Timer counter.
//!        This function is to start The Timer counter.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE
//!             - \ref xTIMER1_BASE
//!             - \ref xTIMER2_BASE
//!             - \ref xTIMER3_BASE
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerStart(ulBase, ulChannel)                                        \
         TimerStart(ulBase)

//*****************************************************************************
//
//! \brief Stop The Timer counter.
//!        This function is to stop The Timer counter.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE
//!             - \ref xTIMER1_BASE
//!             - \ref xTIMER2_BASE
//!             - \ref xTIMER3_BASE
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerStop(ulBase, ulChannel)                                         \
         TimerStop(ulBase)

//*****************************************************************************
//
//! \brief Enable The Timer counter as a counter.
//!        This function is to start timer counter.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE
//!             - \ref xTIMER1_BASE
//!             - \ref xTIMER2_BASE
//!             - \ref xTIMER3_BASE
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerCounterEnable(ulBase, ulChannel)                                \
         TimerStart(ulBase)

//*****************************************************************************
//
//! \brief Disable The Timer counter as a counter.
//!        This function is to stop timer counter.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE
//!             - \ref xTIMER1_BASE
//!             - \ref xTIMER2_BASE
//!             - \ref xTIMER3_BASE
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerCounterDisable(ulBase, ulChannel)                               \
         TimerStop(ulBase)

//*****************************************************************************
//
//! \brief  Enable The Timer counter as a capture.
//!         This function is to enable The Timer counter as a capture.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              Can be one of the following value:
//!              - \ref xTIMER0_BASE
//!              - \ref xTIMER1_BASE
//!              - \ref xTIMER2_BASE
//!              - \ref xTIMER3_BASE
//!
//! \param  [in] ulChannel is the channel of the Timer port.
//!              This value can be one of the following value:
//!              - \ref xTIMER_CHANNEL0 is general timer channel.
//!              - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \param  [in] ulCapMode is the capture mode of the Timer port.
//!              Which can be the values:
//!              - \ref xTIMER_CAP_MODE_CAP
//!
//! \return None.
//!
//! \note   For LPC17xx, it's void function.
//
//*****************************************************************************
#define xTimerCaptureModeSet(ulBase, ulChannel, ulCapMode)                    0

//*****************************************************************************
//
//! \brief  Set The Timer counter Prescale Value.
//!         This function is to Set The Timer counter Prescale Value.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              Can be one of the following value:
//!              - \ref xTIMER0_BASE
//!              - \ref xTIMER1_BASE
//!              - \ref xTIMER2_BASE
//!              - \ref xTIMER3_BASE
//!
//! \param  [in] ulChannel is the channel of the Timer port.
//!              This value can be one of the following value:
//!              - \ref xTIMER_CHANNEL0 is general timer channel.
//!              - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \param  [in] ulValue is the Prescale Value will be set.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerPrescaleSet(ulBase, ulChannel, ulValue)                         \
         TimerPrescaleSet(ulBase, ulValue)

//*****************************************************************************
//
//! \brief  Get The Timer counter Prescale Value.
//!         This function is to get The Timer counter Prescale Value.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              Can be one of the following value:
//!              - \ref xTIMER0_BASE
//!              - \ref xTIMER1_BASE
//!              - \ref xTIMER2_BASE
//!              - \ref xTIMER3_BASE
//!
//! \param  [in] ulChannel is the channel of the Timer port.
//!              This value can be one of the following value:
//!              - \ref xTIMER_CHANNEL0 is general timer channel.
//!              - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \return the Prescale Value will be get.
//
//*****************************************************************************
#define xTimerPrescaleGet(ulBase, ulChannel)                                  \
         TimerPrescaleGet(ulBase, ulValue)

//*****************************************************************************
//
//! \brief Set The Timer counter Value.
//!        This function is to Set The Timer counter Value.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE
//!             - \ref xTIMER1_BASE
//!             - \ref xTIMER2_BASE
//!             - \ref xTIMER3_BASE
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \param [in] ulValue is the Proload Value will be set.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerLoadSet(ulBase, ulChannel, ulValue)                             \
         TimerLoadSet(ulBase, ulValue)
//*****************************************************************************
//
//! \brief Get The Timer counter Value.
//!        This function is to get The Timer counter Value.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE
//!             - \ref xTIMER1_BASE
//!             - \ref xTIMER2_BASE
//!             - \ref xTIMER3_BASE
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \return the counter Value will be get.
//
//*****************************************************************************
#define xTimerLoadGet(ulBase, ulChannel)                                      \
         TimerLoadGet(ulBase)

//*****************************************************************************
//
//! \brief Get The Timer counter current up timer or up event counter value.
//!        This function is to get The Timer counter current up timer or up event
//!        counter value.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE
//!             - \ref xTIMER1_BASE
//!             - \ref xTIMER2_BASE
//!             - \ref xTIMER3_BASE
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \return current up timer or up event counter value will be set.
//
//*****************************************************************************
#define xTimerValueGet(ulBase, ulChannel)                                     \
         TimerValueGet(ulBase)

//*****************************************************************************
//
//! \brief Set The Timer counter Compare Match Value.
//!        This function is to Set The Timer counter Compare Match Value.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE
//!             - \ref xTIMER1_BASE
//!             - \ref xTIMER2_BASE
//!             - \ref xTIMER3_BASE
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \param [in] ulValue is Timer counter Compare Match Value.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerMatchSet(ulBase, ulChannel, ulValue)                            \
         TimerMatchValueSet(ulBase, ulChannel, ulValue)

//*****************************************************************************
//
//! \brief Get The Timer counter Compare Match Value.
//!        This function is to get The Timer counter Compare Match Value.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE
//!             - \ref xTIMER1_BASE
//!             - \ref xTIMER2_BASE
//!             - \ref xTIMER3_BASE
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \return the Prescale Value will be set.
//
//*****************************************************************************
#define xTimerMatchGet(ulBase, ulChannel)                                     \
         TimerMatchValueGet(ulBase, ulChannel)

//*****************************************************************************
//
//! \brief Init interrupts callback for the timer.
//!        Init interrupts callback for the timer.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE
//!             - \ref xTIMER1_BASE
//!             - \ref xTIMER2_BASE
//!             - \ref xTIMER3_BASE
//!
//! \param [in] xtPortCallback is user's callback function for the timer.
//!
//! \return None.
//
//*****************************************************************************
#define xTimerIntCallbackInit(ulBase, xtTimerCallback)                        \
         TimerIntCallbackInit(ulBase, xtTimerCallback)

//*****************************************************************************
//
//! \brief Enable The Timer counter interrupt.
//!        This function is to enable The Timer counter interrupt.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE
//!             - \ref xTIMER1_BASE
//!             - \ref xTIMER2_BASE
//!             - \ref xTIMER3_BASE
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \param [in] ulIntFlags is the interrupt type of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_INT_MATCH
//!             - \ref xTIMER_INT_CAP_EVENT
//! \return None.
//
//*****************************************************************************
extern void xTimerIntEnable(unsigned long ulBase, unsigned long ulChannel,
        unsigned long ulIntFlags);

//*****************************************************************************
//
//! \brief Disable The Timer counter interrupt.
//!        This function is to disable The Timer counter interrupt.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE
//!             - \ref xTIMER1_BASE
//!             - \ref xTIMER2_BASE
//!             - \ref xTIMER3_BASE
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \param [in] ulIntFlags is the interrupt type of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_INT_MATCH
//!             - \ref xTIMER_INT_CAP_EVENT
//!
//! \return None.
//
//*****************************************************************************
extern void xTimerIntDisable(unsigned long ulBase, unsigned long ulChannel,
        unsigned long ulIntFlags);

//*****************************************************************************
//
//! \brief  Get The Timer counter interrupt Status.
//!         This function is to get timer interrupt status.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              Can be one of the following value:
//!              - \ref xTIMER0_BASE
//!              - \ref xTIMER1_BASE
//!              - \ref xTIMER2_BASE
//!              - \ref xTIMER3_BASE
//!
//! \param  [in] ulChannel is the channel of the Timer port.
//!              This value can be one of the following value:
//!              - \ref xTIMER_CHANNEL0 is general timer channel.
//!              - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \param  [in] ulIntFlags is the interrupt type of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_INT_MATCH
//!             - \ref xTIMER_INT_CAP_EVENT
//!
//! \return The Status of The Timer counter interrupt.
//!         - xtrue Check interrupt flag has been set.
//!         - xflase Check interrupt flag has not been set.
//
//*****************************************************************************
extern xtBoolean xTimerStatusGet(unsigned long ulBase, unsigned long ulChannel,
        unsigned long ulIntFlags);

//*****************************************************************************
//
//! \brief  Select The Timer counter detect phase.
//!         This function is to select The Timer counter detect phase.
//!
//! \param  [in] ulBase is the base address of the Timer port.
//!              Can be one of the following value:
//!              - \ref xTIMER0_BASE
//!              - \ref xTIMER1_BASE
//!              - \ref xTIMER2_BASE
//!              - \ref xTIMER3_BASE
//!
//! \param  [in] ulChannel is the channel of the Timer port.
//!              This value can be one of the following value:
//!              - \ref xTIMER_CHANNEL0 is general timer channel.
//!              - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \param  [in] ulPhase is the counter detect phase of the Timer port.
//!              This value can be one of the following value:
//!              - \ref xTIMER_COUNTER_RISING
//!              - \ref xTIMER_COUNTER_FALLING
//!
//! \return None.
//
//*****************************************************************************
extern void xTimerCounterDetectPhaseSelect(unsigned long ulBase,
        unsigned long ulChannel, unsigned long ulPhase);

//*****************************************************************************
//
//! \brief Select The Timer counter capture detect edge.
//!        This function is to select The Timer counter capture detect edge.
//!
//! \param [in] ulBase is the base address of the Timer port.
//!             Can be one of the following value:
//!             - \ref xTIMER0_BASE
//!             - \ref xTIMER1_BASE
//!             - \ref xTIMER2_BASE
//!             - \ref xTIMER3_BASE
//!
//! \param [in] ulChannel is the channel of the Timer port.
//!             This value can be one of the following value:
//!             - \ref xTIMER_CHANNEL0 is general timer channel.
//!             - \ref xTIMER_CHANNEL1 is input capture channel.
//!
//! \param [in] ulEdge is the capture detect mode and detect edge of the
//!             Timer port.
//!             This value can be logic OR of the following value:
//!             - \ref xTIMER_CAP_RISING
//!             - \ref xTIMER_CAP_FALLING
//!             - \ref xTIMER_CAP_BOTH
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
//! \addtogroup LPC17xx_TIMER_Cfg_Channels LPC17xx Configure parameters.
//! \brief      parameters for timer function.
//!             The value below can be used in any timer function
//! @{
//
//*****************************************************************************

//! Timer Match Channel 0
#define TIMER_MAT_CH_0          BIT_32_0

//! Timer Match Channel 1
#define TIMER_MAT_CH_1          BIT_32_1

//! Timer Match Channel 2
#define TIMER_MAT_CH_2          BIT_32_2

//! Timer Match Channel 3
#define TIMER_MAT_CH_3          BIT_32_3

//! Timer Capture Channel 0
#define TIMER_CAP_CH_0          BIT_32_4

//! Timer Capture Channel 1
#define TIMER_CAP_CH_1          BIT_32_5

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_TIMER_Cfg_Int LPC17xx Interrupt Configure parameters.
//! \brief      Parameters for timer interrupt function.
//!             The value below can be used in the function
//!             \ref TimerIntStatusGet
//!             \ref TimerIntStatusCheck
//!             \ref TimerIntStatusClear
//! @{
//
//*****************************************************************************

//! Match Channel 0 Interrupt
#define TIMER_INT_MAT_CH_0      BIT_32_0

//! Match Channel 1 Interrupt
#define TIMER_INT_MAT_CH_1      BIT_32_1

//! Match Channel 2 Interrupt
#define TIMER_INT_MAT_CH_2      BIT_32_2

//! Match Channel 3 Interrupt
#define TIMER_INT_MAT_CH_3      BIT_32_3

//! Capture Channel 0
#define TIMER_INT_CAP_CH_0      BIT_32_4

//! Capture Channel 1
#define TIMER_INT_CAP_CH_1      BIT_32_5

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_TIMER_Cfg_Match LPC17xx Match Configure parameters.
//! \brief      Parameters for timer match configure function.
//!             The value below can be used in the function
//!             \ref TimerMatchCfg
//! @{
//
//*****************************************************************************

//! Timer match configure mask
#define TIMER_MAT_MASK          BIT_MASK(32, 2, 0)

//! Timer match pin action
#define TIMER_MAT_PIN_MASK      BIT_MASK(32, 14, 12)

//! An interrupt is generated when MR matches the value in the TC.
#define TIMER_MAT_INT           BIT_32_0

//! The TC will be reset if MR matches it.
#define TIMER_MAT_RESET         BIT_32_1

//! The TC and PC will be stopped and TCR will be set to 0 if MR matches the TC.
#define TIMER_MAT_STOP          BIT_32_2

//! No action when Match Event occurs.
#define TIMER_MAT_PIN_NONE      BIT_32_14

//! Set pin Low when Match Event occurs.
#define TIMER_MAT_PIN_LOW       BIT_32_12

//! Set pin high when Match Event occurs.
#define TIMER_MAT_PIN_HIGH      BIT_32_13

//! Toggle pin value when Match Event occurs.
#define TIMER_MAT_PIN_TOGGLE    (BIT_32_13 | BIT_32_12)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_TIMER_Cfg_Capture LPC17xx TimerCapture Configure parameters.
//! \brief      Parameters for Timer Capture mode.
//!             The value below can be used in the function \ref TimerCaptureCfg.
//! @{
//
//*****************************************************************************

//! Rising Edge Capture.
#define TIMER_CFG_CAP_RISING    BIT_32_0

//! Falling Edge Capture.
#define TIMER_CFG_CAP_FALLING   BIT_32_1

//! Rising or Falling Edge Capture.
#define TIMER_CFG_CAP_INT       BIT_32_2

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_TIMER_Cfg_Counter LPC17xx TimerCounter Configure parameters.
//! \brief      Parameters for Timer Counter mode.
//!             The value below can be used in the function \ref TimerCounterCfg.
//! @{
//
//*****************************************************************************

//! Counter clock --> Capture Pin 0 Rising Edge pluse
#define TIMER_CFG_CNT_CAP0_RISING      (BIT_32_0)

//! Counter clock --> Capture Pin 0 Falling Edge pluse
#define TIMER_CFG_CNT_CAP0_FALLING     (BIT_32_1)

//! Counter clock --> Capture Pin 0 Rising or Falling Edge pluse
#define TIMER_CFG_CNT_CAP0_BOTH        (BIT_32_1 | BIT_32_0)

//! Counter clock --> Capture Pin 1 Rising Edge pluse
#define TIMER_CFG_CNT_CAP1_RISING      (BIT_32_2 | BIT_32_0)

//! Counter clock --> Capture Pin 1 Falling Edge pluse
#define TIMER_CFG_CNT_CAP1_FALLING     (BIT_32_2 | BIT_32_1)

//! Counter clock --> Capture Pin 1 Rising or Falling Edge pluse
#define TIMER_CFG_CNT_CAP1_BOTH        (BIT_32_2 | BIT_32_1 | BIT_32_0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_TIMER_Exported_APIs LPC17xx TIMER API
//! \brief      LPC17xx TIMER API Reference.
//! @{
//
//*****************************************************************************

extern void TimerInitConfig(unsigned long ulBase, unsigned long ulChannel,
        unsigned long ulConfig, unsigned long ulTickFreq);
extern unsigned long TimerIntStatusGet(unsigned long ulBase);
extern xtBoolean TimerIntStatusCheck(unsigned long ulBase, unsigned long ulIntFlags);
extern void TimerIntStatusClear(unsigned long ulBase, unsigned long ulIntFlags);
extern void TimerStart(unsigned long ulBase);
extern void TimerStop(unsigned long ulBase);
extern void TimerReset(unsigned long ulBase);
extern void TimerPrescaleSet(unsigned long ulBase, unsigned long ulValue);
extern unsigned long TimerPrescaleGet(unsigned long ulBase);
extern void TimerLoadSet(unsigned long ulBase, unsigned long ulValue);
extern unsigned long TimerLoadGet(unsigned long ulBase);
extern unsigned long TimerValueGet(unsigned long ulBase);
extern void TimerMatchValueSet(unsigned long ulBase, unsigned long ulChs, unsigned long ulValue);
extern unsigned long TimerMatchValueGet(unsigned long ulBase, unsigned long ulChs);
extern void TimerMatchCfg(unsigned long ulBase, unsigned long ulChs, unsigned long ulCfgs);
extern void TimerCaptureCfg(unsigned long ulBase, unsigned long ulChs, unsigned long ulCfgs);
extern unsigned long TimerCapValueGet(unsigned long ulBase, unsigned long ulChs);
extern void TimerIntCallbackInit(unsigned long ulBase, xtEventCallback pfnCallback);
extern void TimerCounterCfg(unsigned long ulBase, unsigned long ulCfg);

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

#endif // __XTIMER_H__

