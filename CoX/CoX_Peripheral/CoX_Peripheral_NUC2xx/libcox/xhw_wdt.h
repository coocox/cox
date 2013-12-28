//*****************************************************************************
//
//! \file xhw_wdt.h
//! \brief Macros and defines used when accessing the WATCHDOG hardware.
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
//****************************************************************************
#ifndef __XHW_WDT_H__
#define __XHW_WDT_H__

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
//! \addtogroup NUC2xx_WDT_Register NUC2xx WDT Register
//! \brief Here are the detailed info of WDT registers. 
//!
//! it contains:
//! - Register offset.
//! - detailed bit-field of the registers.
//! - Enum and mask of the registers.
//! .
//! Users can read or write the registers through xHWREG().
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC2xx_WDT_Register_Address WDT Address Register(WDT_Address)
//! @{
//
//*****************************************************************************

//
//! Watchdog Timer Control Register (WTCR)
//
#define WDT_WTCR                0x40004000

//
//! Watchdog Timer Alternative Control Register
//
#define WDT_WTCRALT             0x40004004

//
//! Window Watchdog Timer Reload Counter Register
//
#define WDT_WWDTRLD             0x40004100

//
//! Window Watchdog Timer Control Register
//
#define WDT_WWDTCR              0x40004104

//
//! Window Watchdog Timer Status Register
//
#define WDT_WWDTSTS             0x40004108

//
//! Window Watchdog Counter Value Register
//
#define WDT_WWDTCVR             0x4000410C


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC2xx_WDT_Register_WDT_WTCR WDT WTCR Register(WDT_WTCR)
//! @{
//
//*****************************************************************************

//
//! ICE debug mode acknowledge Disable (write-protection bit)
//
#define WDT_WTCR_DBGACK         0x80000000  

//
//! Watchdog Timer Interval Select mask(write-protection bits)
//
#define WDT_WTCR_WTIS_M         0x00000700  

//
//! Watchdog Timer Interval Select shift(write-protection bits)
//
#define WDT_WTCR_WTIS_S         8  

//
//! Watchdog Timer Enable (write-protection bit)
//
#define WDT_WTCR_WTE            0x00000080  

//
//! Watchdog Timer Interrupt Enable (write-protection bit)
//
#define WDT_WTCR_WTIE           0x00000040  

//
//! Watchdog Timer Wake-up Flag
//
#define WDT_WTCR_WTWKF          0x00000020

//
//! Watchdog Timer Wake-up Function Enable bit (write-protection bit)
//
#define WDT_WTCR_WTWKE          0x00000010

//
//! Watchdog Timer Interrupt Flag
//
#define WDT_WTCR_WTIF           0x00000008

//
//! Watchdog Timer Reset Flag
//
#define WDT_WTCR_WTRF           0x00000004

//
//! Watchdog Timer Reset Enable (write-protection bit)
//
#define WDT_WTCR_WTRE           0x00000002

//
//! Clear Watchdog Timer (write-protection bit)
//
#define WDT_WTCR_WTR            0x00000001


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC2xx_WDT_Register_WTCRALT Watchdog Timer Alternative Control Register(WDT_WTCRALT)
//! @{
//
//*****************************************************************************

//
//! Watchdog Timer Reset Delay Select (Write-protection Bits)
//
#define WDT_WTCRALT_WTRDSEL_M   BIT_MASK(32,1,0)
#define WDT_WTCRALT_WTRDSEL_S   0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC2xx_WDT_Register_WWDTRLD WWDT Reload Counter Register(WDT_WWDTRLD)
//! @{
//
//*****************************************************************************

//
//! WWDT Reload Counter Register
//
#define WDT_WWDTRLD_WWDTRLD_M   BIT_MASK(32,31,0)
#define WDT_WWDTRLD_WWDTRLD_S   0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC2xx_WDT_Register_WWDTCR WWDT Control Register(WDT_WWDTCR)
//! @{
//
//*****************************************************************************

//
//! ICE debug mode acknowledge Disable
//
#define WDT_WWDTCR_DBGACK       BIT_32_31

//
//! WWDT Window Compare Register
//
#define WDT_WWDTCR_WINCMP_M     BIT_MASK(32,21,16)
#define WDT_WWDTCR_WINCMP_S     16

//
//! WWDT Pre-scale Period Select
//
#define WDT_WWDTCR_PERIODSEL_M  BIT_MASK(32,11,8)
#define WDT_WWDTCR_PERIODSEL_S  8

//
//! WWDT Interrupt Enable
//
#define WDT_WWDTCR_WWDTIE       BIT_32_1

//
//! WWDT Enable
//
#define WDT_WWDTCR_WWDTEN       BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC2xx_WDT_Register_WWDTSR WWDT Status Register(WDT_WWDTSR)
//! @{
//
//*****************************************************************************

//
//! WWDT Reset Flag
//
#define WDT_WWDTSR_WWDTRF       BIT_32_1

//
//! WWDT Compare Match Interrupt Flag
//
#define WDT_WWDTSR_WWDTIF       BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC2xx_WDT_Register_WWDTCVR WWDT Counter Value Register(WDT_WWDTCVR)
//! @{
//
//*****************************************************************************

//
//! WWDT Counter Value
//
#define WDT_WWDTCVR_WWDTCVAL_M  BIT_MASK(32,5,0)
#define WDT_WWDTCVR_WWDTCVAL_S  0

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

#endif // __XHW_WADT_H__



