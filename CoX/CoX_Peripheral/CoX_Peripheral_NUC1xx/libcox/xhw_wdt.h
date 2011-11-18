//*****************************************************************************
//
//! \file xhw_wdt.h
//! \brief Macros and defines used when accessing the WATCHDOG hardware.
//! \version V2.1.1.1
//! \date 11/14/2011
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
//! \addtogroup NUC1xx_WDT_Register NUC1xx WDT Register
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
//! \addtogroup NUC1xx_WDT_Register_Address WDT Address Register(WDT_Address)
//! \brief Defines for the bit fields in the WDT_Register_Address register
//! @{
//
//*****************************************************************************

//
//! Watchdog Timer Control Register (WTCR)
//
#define WDT_WTCR                0x40004000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_WDT_Register_WDT_WTCR WDT WTCR Register(WDT_WTCR)
//! \brief Defines for the bit fields in the WDT_Register_Address register
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



