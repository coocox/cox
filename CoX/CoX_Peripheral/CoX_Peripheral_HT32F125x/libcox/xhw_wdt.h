//*****************************************************************************
//
//! \file xhw_wdt.h
//! \brief Macros and defines used when accessing the WATCHDOG hardware.
//! \version V2.1.1.0
//! \date 3/26/2012
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
//! \addtogroup HT32F125x_WDT_Register HT32F125x WDT Register
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
//! \addtogroup HT32F125x_WDT_Register_Address WDT Address Register(WDT_Address)
//! \brief Defines for the bit fields in the WDT_Register_Address register
//! @{
//
//*****************************************************************************

//
//! Watchdog Timer Control Register (WDTCR)
//
#define WDT_CR                  0x40068000

//
//! Watchdog Timer Mode Register 0 (WDTMR0)
//
#define WDT_MR0                 0x40068004

//
//! Watchdog Timer Mode Register 1 (WDTMR1)
//
#define WDT_MR1                 0x40068008

//
//! Watchdog Timer Status Register (WDTSR)
//
#define WDT_SR                  0x4006800C

//
//! Watchdog Timer Protection Register (WDTPR)
//
#define WDT_PR                  0x40068010

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_WDT_Register_WDT_CR WDT WTCR Register(WDT_CR)
//! \brief Defines for the bit fields in the WDT_CR register
//! @{
//
//*****************************************************************************

//
//! Watchdog Timer Reload 
//
#define WDT_CR_WDTRS            0x00000001  

//
//! Watchdog Timer Reload Lock Key mask
//
#define WDT_CR_RSKEY_M          0xFFFF0000 

//
//! Watchdog Timer Reload Lock Key 
//
#define WDT_CR_RSKEY            0x5FA00000 

//
//! Watchdog Timer Reload Lock Key shift
//
#define WDT_CR_RSKEY_S          16  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_WDT_Register_WDT_MR0 WDT Timer Mode Register(WDT_MR0)
//! \brief Defines for the bit fields in the WDT_MR0 register
//! @{
//
//*****************************************************************************

//
//! Watchdog Timer Reset Enable
//
#define WDT_MR0_RSTEN           0x00002000  

//
//! Watchdog Timer Fault Interrupt Enable
//
#define WDT_MR0_FIEN            0x00001000  

//
//! Watchdog Timer Counter Value mask
//
#define WDT_MR0_WDTV_M          0x00000FFF

//
//! Watchdog Timer Counter Value shift
//
#define WDT_MR0_WDTV_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_WDT_Register_WDT_MR1 WDT Timer Mode Register(WDT_MR1)
//! \brief Defines for the bit fields in the WDT_MR1 register
//! @{
//
//*****************************************************************************

//
//! Watchdog Timer Prescaler Selection mask
//
#define WDT_MR1_WPSC_M          0x00007000  

//
//! Watchdog Timer Prescaler Selection shift
//
#define WDT_MR1_WPSC_S          12  

//
//! Watchdog Timer Delta Value mask
//
#define WDT_MR1_WDTD_M          0x00000FFF

//
//! Watchdog Timer Delta Value shift
//
#define WDT_MR1_WDTD_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_WDT_Register_WDT_SR WDT Timer Status Register(WDT_SR)
//! \brief Defines for the bit fields in the WDT_SR register
//! @{
//
//*****************************************************************************

//
//! Watchdog Timer Error
//
#define WDT_SR_ERR              0x00000002  

//
//! Watchdog Timer Underflow
//
#define WDT_SR_WDTUF            0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_WDT_Register_WDT_PR WDT Timer Protection Register(WDT_PR)
//! \brief Defines for the bit fields in the WDT_PR register
//! @{
//
//*****************************************************************************

//
//! Watchdog Timer Register Write Protection mask
//
#define WDT_PR_PROTECT_M        0x0000FFFF  

//
//! Watchdog Timer Register Write Protection disable
//
#define WDT_PR_PROTECT_DIS      0x000035CA 

//
//! Watchdog Timer Register Write Protection enable
//
#define WDT_PR_PROTECT_EN       0x0000CA35

//
//! Watchdog Timer Register Write Protection shift
//
#define WDT_PR_PROTECT_S        0  

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



