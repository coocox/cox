//*****************************************************************************
//
//! \file xtimer.h
//! \brief Prototypes for the TIMER Driver.
//! \version V2.2.1.0
//! \date 5/2/2012
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
//! |xTIMER Mode             |       CoX      |      HT32F175x/275x    |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_ONESHOT     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_PERIODIC    |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_TOGGLE      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_MODE_CONTINUOUS  |  Non-Mandatory |            Y           |
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
//! |xTIMER Interrupt        |       CoX      |      HT32F175x/275x    |
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
#define xTIMER_INT_MATCH        TIMER_INT_UEV1

//
//! Timer External capture event interrupt.
//
#define xTIMER_INT_CAP_EVENT    TIMER_INT_CH0CC | TIMER_INT_CH1CC |           \
                                TIMER_INT_CH2CC | TIMER_INT_CH3CC
  
  

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
//! Values that can be passed to xTimerIntEnable(), xTimerIntEnable(),
//! xTimerIntStatus(),xTimerIntClear() as ulIntFlags . 
//! \n
//! \section xTIMER_INT_Event_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Interrupt        |       CoX      |      HT32F175x/275x    |
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
#define xTIMER_EVENT_MATCH       TIMER_INT_UEV1

//
//! Timer External capture event interrupt.
//
#define xTIMER_EVENT_CAP_EVENT   TIMER_INT_CH0CC | TIMER_INT_CH1CC |           \
                                 TIMER_INT_CH2CC | TIMER_INT_CH3CC


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
//! |xTIMER Counter Pase Type|       CoX      |      HT32F175x/275x    |
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
#define xTIMER_COUNTER_RISING   0

//
//! A falling edge of external count pin will be counted.
//
#define xTIMER_COUNTER_FALLING  0

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
//! |xTIMER Capture Edge     |       CoX      |     HT32F175x/275x     |
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
#define xTIMER_CAP_RISING       TIMER_CHP_NONINVERTED

//
//! a 1 to 0 transition on TEX will be detected.
//
#define xTIMER_CAP_FALLING      TIMER_CHP_INVERTED

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
//! |xTIMER Capture Mode     |       CoX      |     HT32F175x/275x     |
//! |------------------------|----------------|------------------------|
//! |xTIMER_CAP_MODE_CAP     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_CAP_MODE_RST     |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! TEX transition is using as the timer capture function.
//
#define xTIMER_CAP_MODE_CAP     0x00000001

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
//! |xTIMER Count Direction  |       CoX      |     HT32F175x/275x     |
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
#define xTIMER_COUNT_UP         TIMER_CNT_MODE_UP

//
//! The timer counts down.
//
#define xTIMER_COUNT_DOWN       TIMER_CNT_MODE_DOWN


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
//! |xTIMER Count Channel    |       CoX      |     HT32F175x/275x     |
//! |------------------------|----------------|------------------------|
//! |xTIMER_CHANNELn         |    Mandatory   |     xTIMER_CHANNEL0    |
//! |                        |                |     xTIMER_CHANNEL1    |
//! |                        |                |     xTIMER_CHANNEL1    |
//! |                        |                |     xTIMER_CHANNEL1    |  
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Channel 0.
//
#define xTIMER_CHANNEL0         TIMER_CH_0
  
//
//! Channel 1.
//
#define xTIMER_CHANNEL1         TIMER_CH_1
  
//
//! Channel 2.
//
#define xTIMER_CHANNEL2         TIMER_CH_2
  
//
//! Channel 3.
//
#define xTIMER_CHANNEL3         TIMER_CH_3

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
//! |xTIMER API                    |       CoX      |   HT32F175x/275x |
//! |------------------------------|----------------|------------------|
//! |xTimerInitConfig              |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerStart                   |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerStop                    |    Mandatory   |         Y        |
//! |------------------------------|----------------|------------------|
//! |xTimerCounterEnable           |    Mandatory   |         N        |
//! |------------------------------|----------------|------------------|
//! |xTimerCounterDisable          |    Mandatory   |         N        |
//! |------------------------------|----------------|------------------|
//! |xTimerCaptureModeSet          |    Mandatory   |         N        |
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
//! |xTimerCounterDetectPhaseSelect|    Mandatory   |         N        |
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
//! \b xTIMER_MODE_CONTINUOUS is the Timer's mode
//! 
//! \b xTIMER_COUNT_UP, \b xTIMER_COUNT_DOWN is the Timer's direction.
//!
//! The \e ulTickFreq parameter is the the timer tick frequency.It can be any
//! values but ulTickFreq > 0 and ulTickFreq < timer clock source.
//!
//! \note For HT32F175x_275x,each timer only one channel.
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
#define xTimerCounterEnable(ulBase, ulChannel)

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
#define xTimerCounterDisable(ulBase, ulChannel)

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
#define xTimerCaptureModeSet(ulBase, ulChannel, ulCapMode)

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
        TimerPrescalerConfigure(ulBase, ulValue, TIMER_PSC_RLD_IMMEDIATE)

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
#define xTimerLoadGet(ulBase, ulChannel) 

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
#define xTimerMatchSet(ulBase, ulChannel, ulValue)                            \
        TimerCRRSet(ulBase, ulValue)

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
        TimerCRRGet(ulBase)

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
#define xTimerCounterDetectPhaseSelect(ulBase, ulChannel, ulPhase)

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
//! \addtogroup HT32F175x_275x_TIMER
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup TIMER_Counter_Mode_Type TIMER counter mode
//! \brief Values that show TIMER Counter Mode Type
//! Values that can be passed to TimerBaseConfig().
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
#define TIMER_CNT_MODE_CA1      0x00010000

//
//! Center-align mode 2
//
#define TIMER_CNT_MODE_CA2      0x00020000

//
//! Center-align mode 3
//  
#define TIMER_CNT_MODE_CA3      0x00030000
  
//
//!  Edge down-counting mode
//  
#define TIMER_CNT_MODE_DOWN     0x01000000 
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup TIMER_Prescaler_Reload_Time TIMER prescaler reload time.
//! \brief Values that show TIMER Counter Mode Type
//! Values that can be passed to TimerBaseConfig().
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
#define TIMER_PSC_RLD_IMMEDIATE 0x00000100  
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************  
  
//*****************************************************************************
//
//! \addtogroup TIMER_Channel TIMER Channel
//! @{
//
//***************************************************************************** 
  
//
//! Timer channel 0
// 
#define TIMER_CH_0              0

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
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup TIMER_Channel_OutPut_Mode TIMER channel output mode
//! Values that can be passed to TimerOutpurConfigure() as ulCapMode .
//! @{
//
//*****************************************************************************

//
//! Timer channel output no change on match
//
#define TIMER_OM_MATCH_NOCHANGE 0

//
//! Timer channel output inactive level on match
//
#define TIMER_OM_MATCH_INACTIVE 1

//
//! Timer channel output active level on match
//
#define TIMER_OM_MATCH_ACTIVE   2  
  
//
//! Timer channel output toggle on match
//
#define TIMER_OM_MATCH_TOGGLE   3
  
//
//! Timer channel output forced inactive level
//
#define TIMER_OM_FORCED_INACTIVE                                              \
                                4

//
//! Timer channel output forced active level
//
#define TIMER_OM_FORCED_ACTIVE  5
  
  
//*****************************************************************************
//
//! @}
//
//***************************************************************************** 
  
//*****************************************************************************
//
//! \addtogroup TIMER_Channel_control TIMER channel control
//! Values that can be passed to TimerOutpurConfigure() .
//! @{
//
//*****************************************************************************

//
//! Timer channel disable
//  
#define TIMER_CHCTL_DISABLE     0
  
//
//! Timer channel enable
//
#define TIMER_CHCTL_ENABLE      1  
    
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup TIMER_Channel_OutPut_Mode TIMER channel output mode
//! Values that can be passed to TimerOutpurConfigure() .
//! @{
//
//*****************************************************************************
 
//
//! Channel polarity is active high or rising edge
// 
#define TIMER_CHP_NONINVERTED   0

//
//! Channel polarity is active low or falling edge
// 
#define TIMER_CHP_INVERTED      1  
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Channel_Capture_Src_Selection TIMER channel capture source
//! selection
//! Values that can be passed to TimerChannelConfigure() .
//! @{
//
//*****************************************************************************
  
//
//! Channel capture selection direct input
//
#define TIMER_CHCCS_DIRECT      0x00010000

//
//! Channel capture selection indirect input
//
#define TIMER_CHCCS_INDIRECT    0x00020000

//
//! Channel capture selection TRCED of trigger control block
//
#define TIMER_CHCCS_TRCED       0x00030000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************  
  
//*****************************************************************************
//
//! \addtogroup TIMER_Channel_Capture_Prescaler TIMER channel capture prescaler
//! Values that can be passed to TimerCaptureConfigure() .
//! @{
//
//*****************************************************************************

//
//! Channel capture no prescaler, capture is done each event
//
#define TIMER_CHPSC_OFF         0x00000000

//
//! Channel capture is done once every 2 event
//
#define TIMER_CHPSC_2           0x00040000

//
//! Channel capture is done once every 4 event
//
#define TIMER_CHPSC_4           0x00080000 
  
//
//! Channel capture is done once every 8 event
//
#define TIMER_CHPSC_8           0x000C0000    
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup TIMER_fDTS_Clk_Divider TIMER fDTS clock divider
//! Values that can be passed to TimerCKDivConfigure().
//! @{
//
//*****************************************************************************
  
//
//! fDTS = fCLKIN
//
#define TIMER_CKDIV_OFF         0x00000000

//
//! fDTS = fCLKIN / 2
//
#define TIMER_CKDIV_2           0x00000100

//
//! fDTS = fCLKIN / 4
//
#define TIMER_CKDIV_4           0x00000200  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************  
  
//*****************************************************************************
//
//! \addtogroup TIMER_Ext_Input_Prescaler TIMER ETI input prescaler.
//! Values that can be passed to ETIExtClkConfigure() .
//! @{
//
//*****************************************************************************

//
//! ETI prescaler off 
//
#define TIMER_ETIPSC_OFF        0x00000000

//
//! ETIP frequency divided by 2
//
#define TIMER_ETIPSC_2          0x00001000

//
//! ETIP frequency divided by 4
//
#define TIMER_ETIPSC_4          0x00002000  

//
//! ETIP frequency divided by 8
//
#define TIMER_ETIPSC_8          0x00003000   

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 
  
//*****************************************************************************
//
//! \addtogroup TIMER_Input_Polarity TIMER ETI input polarity.
//! Values that can be passed to ETIExtClkConfigure() .
//! @{
//
//*****************************************************************************

//
//! ETI polarity is active high or rising edge
//
#define TIMER_ETIPOL_NONINVERTED                                              \
                                0x00000000

//
//! ETI polarity is active low or falling edge
//
#define TIMER_ETIPOL_INVERTED   0x00010000  
    
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************   
  
//*****************************************************************************
//
//! \addtogroup TIMER_Slave_Trigger_Input slave trigger input selection.
//! Values that can be passed to TimerITIExtClkConfigure() .
//! @{
//
//*****************************************************************************

//
//! Software trigger by seting UEV1G
//
#define TIMER_TRSEL_UEV1G       0x00000000

//
//! Filtered channel 0 input
//
#define TIMER_TRSEL_TI0S0       0x00000001
  
//
//! Filtered channel 1 input
//
#define TIMER_TRSEL_TI1S1       0x00000002
  
//
//! Filtered external trigger input
//
#define TIMER_TRSEL_ETIF        0x00000003

//
//! Triger input 0 both edge detector
//
#define TIMER_TRSEL_TI0BED      0x00000008
  
//
//! Internal trigger input 0
//
#define TIMER_TRSEL_ITI0        0x00000009  
  
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
//! Counter counts up/down on CH0 edge depending on CH1 level
//
#define TIMER_SMSEL_DECODER1    0x00000100

//
//! Counter counts up/down on CH1 edge depending on CH0 level
//
#define TIMER_SMSEL_DECODER2    0x00000200
  
//
//!  Counter counts up/down on both CH0 & CH1 edges depending on the level of the other input
//
#define TIMER_SMSEL_DECODER3    0x00000300

//
//! Slave restart mode
//
#define TIMER_SMSEL_RESTART     0x00000400

//
//! Slave pause mode
//
#define TIEMR_SMSEL_PAUSE       0x00000500

//
//! Slave trigger mode
//
#define TIMER_SMSEL_TRIGGER     0x00000600

//
//! Rising edge of the selected trigger(STI) clock the counter
//  
#define TIMER_SMSEL_STIED       0x00000700
  
//*****************************************************************************
//
//! @}
//
//***************************************************************************** 
  
//*****************************************************************************
//
//! \addtogroup TIMER_Master_Output_Source  Timer Master Mode Output Source.
//! Values that can be passed to TimerMasterOutputSrcSelect() .
//! @{
//
//*****************************************************************************

//
//! Send trigger signal when S/W setting UEV1G or slave restart
//  
#define TIMER_MMSEL_RESET       0x00000000
  
//
//! The counter enable signal is used as trigger output
//
#define TIMER_MMSEL_ENABLE      0x00010000

//
//! The update event 1 is used as trigger output
//
#define TIMER_MMSEL_UPDATE      0x00020000  
  
//
//! Channel 0 capture or compare match occurred as trigger output
//
#define TIMER_MMSEL_CH0CC       0x00030000

//
//! The CH0OREF signal is used as trigger output
//
#define TIMER_MMSEL_CH0OREF     0x00040000

//
//! The CH1OREF signal is used as trigger output
//
#define TIMER_MMSEL_CH1OREF     0x00050000
  
//
//! The CH2OREF signal is used as trigger output
//
#define TIMER_MMSEL_CH2OREF     0x00060000
  
//
//! The CH3OREF signal is used as trigger output
//
#define TIMER_MMSEL_CH3OREF     0x00070000    
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************  
  
//*****************************************************************************
//
//! \addtogroup TIMER_CRR_Configure  Timer Counter-Reload register Buffer Enable.
//! Values that can be passed to TimerCRRPreloadConfigure(), TimerCHCRRPreloadConfigure().
//! @{
//
//*****************************************************************************

//
//! Counter reload can be updated immediately
//
#define TIMER_CRR_PROLOAD_IMM   0x00000001

//
//! Counter can not updated until the update event occurs
//
#define TIMER_CRR_PROLOAD_UD    0x00000000  
  
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
//! \addtogroup TIMER_One_Pulse_Active_Configure  Timer One Pulse Active Configure
//! Values that can be passed to Timer1PulseActiveConfigure().
//! @{
//
//*****************************************************************************

//
//! One pulse immediate active disable  
//
#define TIMER_ONE_PULSE_ACTIVE_DIS                                            \
                                0x00000000

//
//! One pulse immediate active enable
//
#define TIMER_ONE_PULSE_ACTIVE_EN                                             \
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
//! Values that can be passed to TimerHallInterfaceConfigure().
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
#define TIMER_ONE_PULSE_MODE_EN 0x01000000

//
//! Disable one pulse mode
//
#define TIMER_ONE_PULSE_MODE_DIS                                              \
                                0x00000000  
  
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
#define TIMER_SYNC_ENABLE       0x00000001
  
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
//! Channel 0 capture/compare interrupt
//
#define TIMER_INT_CH0CC         0x00000001

//
//! Channel 1 capture/compare interrupt
//
#define TIMER_INT_CH1CC         0x00000002

//
//! Channel 2 capture/compare interrupt
//
#define TIMER_INT_CH2CC         0x00000004

//
//! Channel 3 capture/compare interrupt
//
#define TIMER_INT_CH3CC         0x00000008

//
//! Update interrupt
//
#define TIMER_INT_UEV1          0x00000100

//
//! Trigger interrupt
//
#define TIMER_INT_TEV           0x00000400  
  
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
//! Channel 0 capture/compare event
//
#define TIMER_EVENT_CHOCC       0x00000001
  
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
//! Update event
//
#define TIMER_EVENT_UEV1        0x00000100

//
//! Trigger event
//
#define TIMER_EVENT_TEV         0x00000400  
 
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
//! Channel 0 capture/compare flag
//
#define TIMER_FLAG_CH0CC        0x00000001

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
//! Channel 0 over capture flag
//
#define TIMER_FLAG_CH0OC        0x00000010

//
//! Channel 1 over capture flag
//
#define TIMER_FLAG_CH1OC        0x00000020
  
//
//! Channel 2 over capture flag
//
#define TIMER_FLAG_CH2OC        0x00000040
  
//
//! Channel 3 over capture flag
//
#define TIMER_FLAG_CH3OC        0x00000080
  
//
//! Update flag
//
#define TIMER_FLAG_UEV1         0x00000100
  
//
//! Trigger flag
//
#define TIMER_FLAG_TEV          0x00000400    
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_PDMA_Request Timer PDMA Request.
//! Values that can be passed to TimerPDMARequestEnable(), TimerPDMARequestDisable()
//! @{
//
//*****************************************************************************

//
//! Channel 0 PDMA Request
//
#define TIMER_PDMA_CH0CCDE      0x00010000

//
//! Channel 1 PDMA Request
//
#define TIMER_PDMA_CH1CCDE      0x00020000

//
//! Channel 2 PDMA Request
//
#define TIMER_PDMA_CH2CCDE      0x00040000

//
//! Channel 3 PDMA Request
//
#define TIMER_PDMA_CH3CCDE      0x00080000

//
//! Update event PDMA Request Enable
//
#define TIMER_PDMA_UEVDE        0x01000000

//
//! Trigger event PDMA Request Enable
//
#define TIMER_PDMA_TEVDE        0x02000000
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_PDMA_Request Timer PDMA Request.
//! Values that can be passed to TimerPDMARequestEventSet().
//! @{
//
//*****************************************************************************

//
//! Timer PDMA capture/compare event
//
#define TIMER_CHCCDS_CHCCEV     0x00000000

//
//! Timer PDMA update event
//
#define TIMER_CHCCDS_UEV        0x00000001
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************    
  
//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_TIMER_Exported_APIs HT32F175x_275x TIMER API
//! \brief HT32F175x_275x TIMER API Reference.
//! @{
//
//*****************************************************************************

extern void TimeBaseConfigure(unsigned long ulBase, unsigned long ulCountMode, 
         unsigned long ulCRR, unsigned long ulPrescaler, unsigned long ulReMode);
extern void TimerOutputConfigure(unsigned long ulBase, unsigned long ulChannel, 
                     unsigned long ulOutEnable, unsigned long ulPolarity, 
                     unsigned long ulOutputMode, unsigned long ulOutCompare);
extern void TimerCaptureConfigure(unsigned long ulBase, unsigned long ulChannel, 
                      unsigned long ulPolarity, unsigned long ulSelect, 
                      unsigned long ulPrescaler, unsigned char ucFilter);
extern void TimerCHPSCConfigure(unsigned long ulBase, unsigned long ulChannel, 
                                unsigned long ulPrescaler);
extern void TimerStart(unsigned long ulBase);
extern void TimerStop(unsigned long ulBase);
extern void TimerITIExtClkConfigure(unsigned long ulBase, 
                                    unsigned long ulTriggerSource);
extern void TimerCHExtClkConfigure(unsigned long ulBase, unsigned long ulSelect,
                              unsigned long ulPolarity, unsigned char ucFilter);
extern void TimerSTIConfigure(unsigned long ulBase, 
                              unsigned long ulTriggerSource);
extern void TimerETIExtClkConfigure(unsigned long ulBase, unsigned long ulEXIPrescale,
                               unsigned long ulEXIPolarity, unsigned char ucFilter);
extern void TimerETIConfigure(unsigned long ulBase, unsigned long ulEXIPrescale, 
                         unsigned long ulEXIPolarity, unsigned char ucFilter);
extern void TimerPrescalerConfigure(unsigned long ulBase, unsigned long ulPrescale,
                                    unsigned long ulPSCReloadTime);
extern void TimerCNTModeConfigure(unsigned long ulBase, unsigned long ulCountMode);
extern void TimerDecoderConfigure(unsigned long ulBase, unsigned long ulDecodeMode,
                               unsigned long ulCH0P, unsigned long ulCH1P);
extern void TimerForcedOREF(unsigned long ulBase, unsigned long ulChannel, 
                            unsigned long ForcedAction);
extern void TimerCRRPreloadConfigure(unsigned long ulBase, unsigned long ulProload);
extern void TimerCHCRRPreloadConfigure(unsigned long ulBase, unsigned long ulChannel,
                                       unsigned long ulProload);
extern void TimerOREFClrConfigure(unsigned long ulBase, unsigned long ulChannel,
                                  unsigned long ulOREFClear);
extern void TimerCHPolarityConfigure(unsigned long ulBase, unsigned long ulChannel,
                                     unsigned long ulPolarity);
extern void Timer1PulseActiveConfigure(unsigned long ulBase, unsigned long ulChannel,
                                       unsigned long ulActive);
extern void TimerCHConfigure(unsigned long ulBase, unsigned long ulChannel, 
                             unsigned long ulControl);
extern void TimerUpdateConfigure(unsigned long ulBase, unsigned long ulUpdate);
extern void TimerUpdateIntEnable(unsigned long ulBase);
extern void TimerUpdateIntDisable(unsigned long ulBase);
extern void TimerHallInterfaceConfigure(unsigned long ulBase, 
                                        unsigned long ulConfigure);
extern void TimerOnePulseModeConfigure(unsigned long ulBase, unsigned long ulConfigure);
extern void TimerMasterOutputSrcSelect(unsigned long ulBase, unsigned long ulSelect);
extern void TimerSlaveModeConfigure(unsigned long ulBase, unsigned long ulSelect);
extern void TimerSyncConfigure(unsigned long ulBase, unsigned long ulConfigure);
extern void TimerCounterSet(unsigned long ulBase, unsigned long ulCounter);
extern void TimerCRRSet(unsigned long ulBase, unsigned long ulCRRValue);
extern unsigned long TimerCRRGet(unsigned long ulBase);
extern void TimerCaptureCompareSet(unsigned long ulBase, unsigned long ulChannel, 
                                   unsigned long ulCCValue);
extern void TimerCKDivConfigure(unsigned long ulBase, unsigned long ulDiv);
extern unsigned long TimerCaptureCompareGet(unsigned long ulBase, 
                                            unsigned long ulChannel);
extern unsigned long TimerCounterGet(unsigned long ulBase);
extern unsigned long TimerPerscalerGet(unsigned long ulBase);
extern void TimerEventGenerate(unsigned long ulBase, unsigned long ulEvent);
extern xtBoolean TimerFlagStatusGet(unsigned long ulBase, unsigned long ulFlag);
extern void TimerFlagStatusClear(unsigned long ulBase, unsigned long ulFlag);
extern void TimerIntCallbackInit(unsigned long ulBase, 
                                 xtEventCallback xtTimerCallback);
extern void TimerIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void TimerIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern xtBoolean TimerIntStatus(unsigned long ulBase, unsigned long ulIntFlags);
extern void TimerIntClear(unsigned long ulBase, unsigned long ulIntFlags);
extern void TimerInternalClkConfigure(unsigned long ulBase);

extern void TimerPDMARequestEnable(unsigned long ulBase, unsigned long ulPDMAReqs);
extern void TimerPDMARequestDisable(unsigned long ulBase, unsigned long ulPDMAReqs);
extern void TimerPDMARequestEventSet(unsigned long ulBase, unsigned long ulPDMAReqsEvent);

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



