//*****************************************************************************
//
//! \file wdt.h
//! \brief Prototypes for the WDT Driver.
//! \version V2.1.1.0
//! \date 1/3/2012
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

#ifndef __WDT_H__
#define __WDT_H__

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
//! \addtogroup WDT
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_WDT
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup WDT_Function_Type WDT Function Type
//! \brief Values that show WDT Function Type
//! Values that can be passed to WDTimerFunctionEnable(),WDTimerFunctionDisable 
//! ().
//! @{
//
//*****************************************************************************

//
//! Generate Interrupt when watch dog time out
//
#define WDT_INT_FUNCTION        0x00000040

//
//! Reset CPU when watch dog time out
//
#define WDT_RESET_FUNCTION      0x00000002

//
//! Watchdog timer timeout can wake-up chip from power down mode.
//
#define WDT_WAKEUP_FUNCTION     0x00000010

//
//! Watchdog Timer counter will keep going no matter ICE debug mode
//! acknowledged or not.
//
#define WDT_HOLD_IN_ICE         0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup WDT_Time_Interval_Config WDT Time Interval Configuration
//! \brief WDT Time Interval Configuration
//! Values that can be passed to WDTimerInit().
//! @{
//
//*****************************************************************************

//
//! Timeout Interval Selection is 2 4 * TWDT
//
#define WDT_INTERVAL_2_4T       0x00000000

//
//! Timeout Interval Selection is 2 6 * TWDT
//
#define WDT_INTERVAL_2_6T       0x00000100

//
//! Timeout Interval Selection is 2 8 * TWDT
//
#define WDT_INTERVAL_2_8T       0x00000200

//
//! Timeout Interval Selection is 2 10 * TWDT
//
#define WDT_INTERVAL_2_10T      0x00000300

//
//! Timeout Interval Selection is 2 12 * TWDT
//
#define WDT_INTERVAL_2_12T      0x00000400

//
//! Timeout Interval Selection is 2 14 * TWDT
//
#define WDT_INTERVAL_2_14T      0x00000500

//
//! Timeout Interval Selection is 2 16 * TWDT
//
#define WDT_INTERVAL_2_16T      0x00000600

//
//! Timeout Interval Selection is 2 18 * TWDT
//
#define WDT_INTERVAL_2_18T      0x00000700


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_WDT_Exported_APIs M051 WDT API
//! \brief M051 WDT API Reference.
//! @{
//! @{
//
//*****************************************************************************

extern void WDTimerInit(unsigned long ulConfig);
extern void WDTimerEnable(void);
extern void WDTimerDisable(void);
extern void WDTimerRestart(void);
extern void WDTimerIntCallbackInit(xtEventCallback xtWDTCallback);
extern void WDTimerFunctionEnable(unsigned long ulFunction);
extern void WDTimerFunctionDisable(unsigned long ulFunction);

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

#endif // __xWDT_H__


