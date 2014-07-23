//*****************************************************************************
//
//! \file xtimer.h
//! \brief Prototypes for the TIMER Driver.
//! \version V2.1.1.0
//! \date 15/7/2014
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
//! \addtogroup AU9110_TIMER
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
//! Values that can be passed to TimerIntEnable(), TimerIntDisable(),
//! TimerIntStatus(), TimerIntClear() as ulIntFlags.
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
//! \addtogroup AU9110_TIMER_Exported_APIs AU9110 TIMER API
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



