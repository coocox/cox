//*****************************************************************************
//
//! \file      xhw_wdt.h
//! \brief     Macros used when accessing the WDT hardware.
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

#ifndef __XHW_WDT_H__
#define __XHW_WDT_H__

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"

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
//! \addtogroup LPC17xx_WDT_Register WDT Register Hardware Layer.
//! \brief      Here are detail register information.
//!             it contains:
//!                 - Register offset.
//!                 - detailed bit-field of the registers.
//!                 - Enum and mask of the registers.
//!
//! \note       Users can read or write the registers via xHWREG().
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_Wdt_Register_Offsets Wdt Register Offset(Map)
//! \brief      Here is the register offset, users can get the register address
//!             via <b>WDT_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//! Watchdog mode register.
//! This register contains the basic mode and status of the Watchdog Timer.
#define WDT_MOD                 ((unsigned long)0x00000000)

//! Watchdog timer constant register.
//! This register determines the time-out value.
#define WDT_TC                  ((unsigned long)0x00000004)

//! Watchdog feed sequence register.
//! Writing 0xAA followed by 0x55 to this register reloads the Watchdog timer
//! with the value contained in WDTC.
#define WDT_FEED                ((unsigned long)0x00000008)

//! Watchdog timer value register.
//! This register reads out the current value of the Watchdog timer.
#define WDT_TV                  ((unsigned long)0x0000000C)

//! Watchdog clock source selection register.
#define WDT_CLKSEL              ((unsigned long)0x00000010)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_WDT_Register_WDMOD WDMOD Register CLKSEL
//! \brief      WDT WDMOD Register description.
//!
//! @{
//
//*****************************************************************************

//! Enable Watchdog
#define WDMOD_EN                BIT_32_0

//! Reset Mode.
#define WDMOD_RESET             BIT_32_1

//! Watchdog time-out flag.
#define WDMOD_TOF               BIT_32_2

//! Watchdog interrupt flag.
#define WDMOD_INT               BIT_32_3

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_WDT_Register_CLKSEL WDT Register CLKSEL
//! \brief      WDT CLKSEL Register description.
//!
//! @{
//
//*****************************************************************************

//! Watchdog clock source.
#define WDCLKSEL_WDSEL_M        BIT_MASK(32, 1, 0)

//! Use internal RC clock as wdt clock source.
#define WDCLKSEL_WDSEL_IRC      BIT_32_ALL_0

//! Use APB clock as wdt clock source.
#define WDCLKSEL_WDSEL_APB      BIT_32_0

//! Use RTC clock as wdt clock source.
#define WDCLKSEL_WDSEL_RTC      BIT_32_1

//! Lock watchdog register.
#define WDCLKSEL_WDLOCK         BIT_32_31

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

#endif // __XHW_WDT_H__

