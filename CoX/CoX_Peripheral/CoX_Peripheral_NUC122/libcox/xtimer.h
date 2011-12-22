//*****************************************************************************
//
//! \file xtimer.h
//! \brief Prototypes for the TIMER Driver.
//! \version V2.1.1.0
//! \date 12/10/2011
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
//! \n
//! \section xTIMER_Mode_Type_Section 1. Where to use this group
//! Values that can be passed to xTimerInitConfig() as the ulConfig parameter 
//! \n
//! \section xTIMER_Mode_Type_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Mode             |       CoX      |         NUC122         |
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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_INT_Type xTIMER Interrupt
//! \n
//! \section xTIMER_INT_Type_Section 1. Where to use this group
//! Values that can be passed to xTimerIntEnable(), xTimerIntDisable() ,
//! xTimerStatusGet() as ulIntFlags . 
//! \n
//! \section xTIMER_INT_Type_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Interrupt        |       CoX      |         NUC122         |
//! |------------------------|----------------|------------------------|
//! |xTIMER_INT_MATCH        |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_INT_CAP_EVENT    |  Non-Mandatory |            N           |
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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_INT_Event xTIMER Interrupt Event
//! \n
//! \section xTIMER_INT_Event_Section 1. Where to use this group
//! Values that can be passed to xTimerIntEnable(), xTimerIntDisable() ,
//! xTimerIntStatus(),xTimerIntClear() as ulIntFlags . 
//! \n
//! \section xTIMER_INT_Event_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Interrupt        |       CoX      |         NUC122         |
//! |------------------------|----------------|------------------------|
//! |xTIMER_EVENT_MATCH      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_EVENT_CAP_EVENT  |  Non-Mandatory |            N           |
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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Counter_Pase_Type xTIMER Counter Pase Type
//! \n
//! \section xTIMER_Counter_Pase_Type_Section 1. Where to use this group
//! Values that can be passed to xTimerCounterDetectPhaseSelect() as ulPhase. 
//! \n
//! \section xTIMER_Counter_Pase_Type_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Counter Pase Type|       CoX      |         NUC122         |
//! |------------------------|----------------|------------------------|
//! |xTIMER_COUNTER_RISING   |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xTIMER_COUNTER_FALLING  |  NON_Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! A rising edge of external count pin will be counted.
//
#define xTIMER_COUNTER_RISING

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Count_Direction xTIMER Count Direction
//! \n
//! \section xTIMER_Count_Direction_Section 1. Where to use this group
//! Values that can be passed to xTimerInitConfig() as ulConfig.
//! \n
//! \section xTIMER_Count_Direction_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Count Direction  |       CoX      |         NUC122         |
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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xTIMER_Count_Channel xTIMER Count Channel
//! \n
//! \section xTIMER_Count_Channel_Section 1. Where to use this group
//! Values that can be passed to all XAPI as ulChannel.
//! \n
//! \section xTIMER_Count_Channel_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xTIMER Count Channel    |       CoX      |         NUC122         |
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
//! |xTIMER API                    |       CoX      |      NUC122      |
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
//! \b xTIMER_INT_MATCH
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
//! \b xTIMER_INT_MATCH.
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
//! \addtogroup NUC122_TIMER
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Mode_Type TIMER Mode Type
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
//! \addtogroup TIMER_INT_Type TIMER INT Type
//! Values that can be passed to TimerIntEnable(), TimerIntEnable() ,
//! TimerIntStatus(),TimerIntClear() as ulIntFlags .
//! @{
//
//*****************************************************************************

//
//! Timer match interrupt.
//
#define TIMER_INT_MATCH         0x20000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC122_TIMER_Exported_APIs NUC122 TIMER API
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
extern void TimerCounterDisable(unsigned long ulBase);

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



