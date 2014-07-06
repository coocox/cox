//*****************************************************************************
//
//! \file timer.h
//! \brief Prototypes for the TIMER Driver.
//! \version V2.2.1.0
//! \date 11/15/2013
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

#ifndef __TIMER_H__
#define __TIMER_H__

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
//! \addtogroup NUC4xx_TIMER
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

//
//! Timer Timer Wakeup Flag
//
#define TIMER_INT_WAKEUP        0x00800000

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
//! \addtogroup NUC4xx_TIMER_Exported_APIs NUC4xx TIMER API
//! \brief NUC4xx TIMER API Reference.
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
//extern void TimerWakeupEnable(unsigned long ulBase);
//extern void TimerWakeupDisable(unsigned long ulBase);
//extern int TimerWakeupStatusGet(unsigned long ulBase);

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

#endif // __TIMER_H__



