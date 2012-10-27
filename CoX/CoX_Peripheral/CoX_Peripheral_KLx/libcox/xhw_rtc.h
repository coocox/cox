//*****************************************************************************
//
//! \file xhw_rtc.h
//! \brief Macros and defines used when accessing the RTC hardware.
//! \version V2.0.1
//! \date 11/11/2011
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
#ifndef __XHW_RTC_H__
#define __XHW_RTC_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup RTC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_RTC_Register KLx RTC Register
//! \brief Here are the detailed info of RTC registers. 
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
//! \addtogroup KLx_RTC_Register_RTC_Address RTC Address Register(RTC_Register_Address)
//! \brief Defines for the bit fields in the RTC_Register_Address register.
//! @{
//
//*****************************************************************************

//
//! RTC Time Seconds Register (TSR)
//
#define RTC_TSR                 0x4003D000  

//
//! RTC Time Prescaler Register (TPR)
//
#define RTC_TPR                 0x4003D004

//
//! RTC Time Alarm Register (TAR)
//
#define RTC_TAR                 0x4003D008

//
//! RTC Time Compensation Register (TCR)
//
#define RTC_TCR                 0x4003D00C

//
//! RTC Control Register (CR)
//
#define RTC_CR                  0x4003D010

//
//! RTC Status Register (SR)
//
#define RTC_SR                  0x4003D014

//
//! RTC Lock Register (LR)
//
#define RTC_LR                  0x4003D018

//
//! RTC Interrupt Enable Register (IER)
//
#define RTC_IER                 0x4003D01C

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_RTC_Register_RTC_TSR RTC Time Seconds Register(RTC_TSR)
//! \brief Defines for the bit fields in the RTC_TSR register.
//! @{
//
//*****************************************************************************

//
//! RTC Time Seconds mask
//
#define RTC_TSR_M               0xFFFFFFFF  

//
//! RTC Time Seconds shift
//
#define RTC_TSR_S               0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_RTC_Register_RTC_TPR RTC Time Prescaler Register(RTC_TPR)
//! \brief Defines for the bit fields in the RTC_TPR register.
//! @{
//
//*****************************************************************************

//
//! RTC Time Prescaler mask
//
#define RTC_TPR_M               0x0000FFFF  

//
//! RTC Time Prescaler shift
//
#define RTC_TPR_S               0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_RTC_Register_RTC_TAR RTC Time Alarm Register(RTC_TAR)
//! \brief Defines for the bit fields in the RTC_TAR register.
//! @{
//
//*****************************************************************************

//
//! RTC Time Prescaler mask
//
#define RTC_TAR_M               0xFFFFFFFF  

//
//! RTC Time Prescaler shift
//
#define RTC_TAR_S               0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_RTC_Register_RTC_TCR RTC Time Compensation Register(RTC_TCR)
//! \brief Defines for the bit fields in the RTC_TCR register.
//! @{
//
//*****************************************************************************

//
//! Compensation Interval Counter mask
//
#define RTC_TCR_CIC_M           0xFF000000  

//
//! Compensation Interval Counter shift
//
#define RTC_TCR_CIC_S           24 

//
//! Time Compensation Value mask
//
#define RTC_TCR_TCV_M           0x00FF0000  

//
//! Time Compensation Value shift
//
#define RTC_TCR_TCV_S           16 

//
//! Compensation Interval Register mask
//
#define RTC_TCR_CIR_M           0x0000FF00  

//
//! Compensation Interval Register shift
//
#define RTC_TCR_CIR_S           8 

//
//! Time Compensation Register mask
//
#define RTC_TCR_TCR_M           0x000000FF  

//
//! Compensation integer reference
//
#define RTC_TCR_TCR_REFERENCE	32641

//
//! Time Compensation Register shift
//
#define RTC_TCR_TCR_S           0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_RTC_Register_RTC_CR RTC Control Register(RTC_CR)
//! \brief Defines for the bit fields in the RTC_CR register.
//! @{
//
//*****************************************************************************

//
//! Oscillator 2pF Load Configure Enable
//
#define RTC_CR_SC2P             0x00002000  

//
//! Oscillator 4pF Load Configure Enable
//
#define RTC_CR_SC4P             0x00001000

//
//! Oscillator 8pF Load Configure Enable
//
#define RTC_CR_SC8P             0x00000800

//
//! Oscillator 16pF Load Configure Enable
//
#define RTC_CR_SC16P            0x00000400

//
//! Clock Output Disable
//
#define RTC_CR_CLKO             0x00000200

//
//! Oscillator Output Enable
//
#define RTC_CR_OSCE             0x00000100

//
//! Update Mode (Registers can be written when locked)
//
#define RTC_CR_UM               0x00000008

//
//! Supervisor Access
//
#define RTC_CR_SUP              0x00000004

//
//! Wakeup Pin Enable
//
#define RTC_CR_WPE              0x00000002

//
//! Sofeware Reset 
//
#define RTC_CR_SWR              0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_RTC_Register_RTC_SR RTC Status Register(RTC_SR)
//! \brief Defines for the bit fields in the RTC_SR register
//! @{
//
//*****************************************************************************

//
//! RTC Time Counter Enable
//
#define RTC_SR_TCE              0x00000010

//
//! RTC Time Alarm Flag
//
#define RTC_SR_TAF              0x00000004

//
//! RTC Time Overflow Flag
//
#define RTC_SR_TOF              0x00000002

//
//! RTC Time Invalid Flag
//
#define RTC_SR_TIF              0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_RTC_Register_RTC_LR RTC Lock Register(RTC_LR)
//! \brief Defines for the bit fields in the RTC_LR register
//! @{
//
//*****************************************************************************

//
//! RTC Lock Register is not locked
//
#define RTC_LR_LRL              0x00000040

//
//! RTC Status Register is not locked
//
#define RTC_LR_SRL              0x00000020

//
//! RTC Control Register is not locked
//
#define RTC_LR_CRL              0x00000010

//
//! RTC Time Compensation Register is not locked
//
#define RTC_LR_TCL              0x00000008

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_RTC_Register_RTC_IER RTC Interrupt Enable Register(RTC_IER)
//! \brief Defines for the bit fields in the RTC_IER register
//! @{
//
//*****************************************************************************

//
//! Wakeup Pin On
//
#define RTC_IER_WPON            0x00000080

//
//! Time Seconds Interrupt Enable
//
#define RTC_IER_TSIE            0x00000010

//
//! Time Alarm Interrupt Enable
//
#define RTC_IER_TAIE            0x00000004

//
//! Time Overflow Interrupt Enable
//
#define RTC_IER_TOIE            0x00000002

//
//! Time Invalid Interrupt Enable
//
#define RTC_IER_TIIE            0x00000001

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

#endif // __XHW_RTC_H__