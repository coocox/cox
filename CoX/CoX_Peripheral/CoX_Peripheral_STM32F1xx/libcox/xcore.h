//*****************************************************************************
//
//! \file xcore.h
//! \brief Prototypes for the CPU instruction wrapper functions.
//! Prototypes for the NVIC Interrupt Controller Driver.
//! Prototypes for the SysTick driver.
//! \version V2.2.1.0
//! \date 11/20/2011
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

#ifndef __XCORE_H__
#define __XCORE_H__

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
//! \addtogroup CORE
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xCORE
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xCORE_Exported_Macros
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Macro to generate an interrupt priority mask based on the number of bits
//! of priority supported by the hardware.
//
//*****************************************************************************
#define xINT_PRIORITY_MASK       ((0xFF << (8 - NUM_PRIORITY_BITS)) & 0xFF)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xCORE_Exported_APIs
//! @{
//
//*****************************************************************************

extern unsigned long xCPUcpsid(void);
extern unsigned long xCPUcpsie(void);
extern unsigned long xCPUprimask(void);
extern void xCPUwfi(void);
extern void xCPUwfe(void);
extern unsigned long xCPUbasepriGet(void);
extern void xCPUbasepriSet(unsigned long ulNewBasepri);
extern void xCPUpspSet(unsigned long ulNewPspStack);
extern unsigned long xCPUpspGet(void);
extern void xCPUmspSet(unsigned long ulNewMspStack);
extern unsigned long xCPUmspGet(void);

extern xtBoolean xIntMasterEnable(void);
extern xtBoolean xIntMasterDisable(void);
extern void xIntPriorityGroupingSet(unsigned long ulBits);
extern unsigned long xIntPriorityGroupingGet(void);
extern void xIntPrioritySet(unsigned long ulInterrupt,
                           unsigned char ucPriority);
extern long xIntPriorityGet(unsigned long ulInterrupt);
extern void xIntEnable(unsigned long ulInterrupt);
extern void xIntDisable(unsigned long ulInterrupt);
extern void xIntPendSet(unsigned long ulInterrupt);
extern void xIntPendClear(unsigned long ulInterrupt);
extern void xIntPriorityMaskSet(unsigned long ulPriorityMask);
extern unsigned long xIntPriorityMaskGet(void);

extern void xSysTickEnable(void);
extern void xSysTickDisable(void);
extern void xSysTickIntEnable(void);
extern void xSysTickIntDisable(void);
extern void xSysTickPeriodSet(unsigned long ulPeriod);
extern unsigned long xSysTickPeriodGet(void);
extern unsigned long xSysTickValueGet(void);

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

#endif // __XCORE_H__
