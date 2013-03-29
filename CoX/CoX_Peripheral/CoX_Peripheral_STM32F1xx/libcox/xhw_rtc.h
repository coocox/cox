//*****************************************************************************
//
//! \file xhw_rtc.h
//! \brief Macros used when accessing the RTC hardware.
//! \version V2.2.1.0
//! \date 05/31/2012
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
//! \addtogroup STM32F1xx_RTC_Register  STM32F1xx RTC Register
//! \brief Here are the detailed info of RTC registers.  
//!
//! it contains:
//! - Register offset.
//! - Detailed bit-field of the registers.
//! - Enum and mask of the registers.
//! .
//! Users can read or write the registers through xHWREG().
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_RTC_Register_Offsets RTC Register Offsets(Map)
//! \brief Here is the RTC register offset, users can get the register address
//! through <b>RTC_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! RTC control register high (RTC_CRH) .
//
#define RTC_CRH                 RTC_BASE+0x00000000 

//
//! RTC control register low (RTC_CRL).
//
#define RTC_CRL                 RTC_BASE+0x00000004

//
//! RTC prescaler load register high (RTC_PRLH).
//
#define RTC_PRLH                RTC_BASE+0x00000008

//
//! RTC prescaler load register low (RTC_PRLL).
//
#define RTC_PRLL                RTC_BASE+0x0000000C

//
//! RTC prescaler divider register high (RTC_DIVH).
//
#define RTC_DIVH                RTC_BASE+0x00000010

//
//! RTC prescaler divider register low (RTC_DIVL).
//
#define RTC_DIVL               RTC_BASE+0x00000014

//
//! RTC counter register high (RTC_CNTH).
//
#define RTC_CNTH                RTC_BASE+0x00000018

//
//! RTC counter register low (RTC_CNTL).
//
#define RTC_CNTL                RTC_BASE+0x0000001C

//
//! RTC alarm register high (RTC_ALRH).
//
#define RTC_ALRH                RTC_BASE+0x00000020

//
//! RTC alarm register low (RTC_ALRL).
//
#define RTC_ALRL                RTC_BASE+0x00000024

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_RTC_Register_RTC_CRH RTC control register high(RTC_CRH) 
//! \brief Defines for the bit fields in the RTC_CRH register.
//! @{
//
//*****************************************************************************

//
//! Overflow interrupt enable
//
#define RTC_CRH_OWIE            0x00000004

//
//! Alarm interrupt enable
//
#define RTC_CRH_ALRIE           0x00000002

//
//! Second interrupt enable
//
#define RTC_CRH_SECIE           0x00000001


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_RTC_Register_RTC_CRL RTC Control Register(RTC_CRL) 
//! \brief Defines for the bit fields in the RTC_CRL register.
//! @{
//
//*****************************************************************************

//
//! RTC operation OFF
//
#define RTC_CRL_RTOFF           0x00000020

//
//! Configuration flag
//
#define RTC_CRL_CNF             0x00000010

//
//! Registers synchronized flag
//
#define RTC_CRL_RSF             0x00000008

//
//! Overflow flag
//
#define RTC_CRL_OWF             0x00000004

//
//! Alarm flag
//
#define RTC_CRL_ALRF            0x00000002

//
//! Second flag
//
#define RTC_CRL_SECF            0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_RTC_Register_RTC_PRLH RTC prescaler load register high(RTC_PRLH) 
//! \brief Defines for the bit fields in the RTC_PRLH register.
//! @{
//
//*****************************************************************************

//
//! RTC prescaler reload value high mask
//
#define RTC_PRLH_PRLH_M         0x000F0000

//
//! RTC prescaler reload value high shift
//
#define RTC_PRLH_PRLH_S         16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_RTC_Register_RTC_PRLL RTC prescaler load register low(RTC_PRLL) 
//! \brief Defines for the bit fields in the RTC_PRLL register.
//! @{
//
//*****************************************************************************


//
//! RTC prescaler reload value low mask
//
#define RTC_PRLL_PRLL_M         0x0000FFFF

//
//! RTC prescaler reload value low shift
//
#define RTC_PRLL_PRLL_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_RTC_Register_RTC_DIVH RTC prescaler divider register high  
//! \brief Defines for the bit fields in the RTC_DIVH register.
//! @{
//
//*****************************************************************************

//
//! RTC prescaler divider register high mask
//
#define RTC_DIVH_DIV_M          0x000F0000

//
//! RTC prescaler divider register high shift
//
#define RTC_DIVH_DIV_S          16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_RTC_Register_RTC_DIVL RTC prescaler divider register low   
//! \brief Defines for the bit fields in the RTC_DIVL register.
//! @{
//
//*****************************************************************************

//
//! RTC prescaler divider register low mask
//
#define RTC_DIVL_DIV_M          0x0000FFFF

//
//! RTC prescaler divider register low shift
//
#define RTC_DIVL_DIV_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_RTC_Register_RTC_CNTH RTC counter register high   
//! \brief Defines for the bit fields in the RTC_CNTH register.
//! @{
//
//*****************************************************************************

//
//! RTC counter register high mask
//
#define RTC_CNTH_CNT_M          0xFFFF0000

//
//! RTC counter register high shift
//
#define RTC_CNTH_CNT_S          16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_RTC_Register_RTC_CNTL RTC counter register low  
//! \brief Defines for the bit fields in the RTC_CNTL register.
//! @{
//
//*****************************************************************************

//
//! RTC counter register low mask
//
#define RTC_CNTL_CNT_M          0x0000FFFF

//
//! RTC counter register low shift
//
#define RTC_CNTL_CNT_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_RTC_Register_RTC_ALRH RTC alarm register high  
//! \brief Defines for the bit fields in the RTC_ALRH register.
//! @{
//
//*****************************************************************************

//
//! RTC alarm register high mask
//
#define RTC_ALRH_CNT_M          0xFFFF0000

//
//! RTC alarm register high shift
//
#define RTC_ALRH_CNT_S          16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_RTC_Register_RTC_ALRL RTC alarm register low  
//! \brief Defines for the bit fields in the RTC_ALRL register.
//! @{
//
//*****************************************************************************

//
//! RTC alarm register low mask
//
#define RTC_ALRL_CNT_M          0x0000FFFF

//
//! RTC alarm register low shift
//
#define RTC_ALRL_CNT_S          0

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



