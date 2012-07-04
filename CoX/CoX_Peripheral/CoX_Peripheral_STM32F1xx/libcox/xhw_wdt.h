//*****************************************************************************
//
//! \file xhw_wdt.h
//! \brief Macros and defines used when accessing the WATCHDOG hardware.
//! \version V2.2.1.0
//! \date 6/14/2012
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
//! \addtogroup STM32F1xx_WDT_Register STM32F1xx WDT Register
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
//! \addtogroup STM32F1xx_WDT_Register_Address WDT Address Register(WDT_Address)
//! \brief Defines for the bit fields in the WDT_Register_Address register
//! @{
//
//*****************************************************************************

//
//! Independent watchdog Key register(IWDG_KR)
//
#define IWDG_KR                 0x40003000

//
//! Independent watchdog Prescaler register(IWDG_PR)
//
#define IWDG_PR                 0x40003004

//
//! Independent watchdog Reload register(IWDG_RLR)
//
#define IWDG_RLR                0x40003008

//
//! Independent watchdog Status register(IWDG_SR)
//
#define IWDG_SR                 0x4000300C


//
//! Window watchdog Control register(WWDG_CR)
//
#define WWDG_CR                 0x40002C00

//
//! Window watchdog Configuration register(WWDG_CFR)
//
#define WWDG_CFR                0x40002C04

//
//! Window watchdog Status register(WWDG_SR)
//
#define WWDG_SR                 0x40003008

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_WDT_Register_IWDG_KR IWDG IWDG_KR Register(IWDG_KR)
//! \brief Defines for the bit fields in the IWDG_KR register
//! @{
//
//*****************************************************************************

//
//! Independent watchdog start Bits 
//
#define IWDG_KR_START           0x0000CCCC  

//
//! Independent watchdog Reload Bits 
//
#define IWDG_KR_RELOAD          0x0000AAAA 

//
//! Independent watchdog Register Write Protection disable
//
#define IWDG_KR_PROTECT_DIS     0x00005555 

//
//! Independent watchdog Register Write Protection enable
//
#define IWDG_KR_PROTECT_EN      0x0000CA35

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_WDT_Register_IWDG_PR IWDG Prescaler Register(IWDG_PR)
//! \brief Defines for the bit fields in the IWDG_PR register
//! @{
//
//*****************************************************************************

//
//! Independent watchdog Prescaler Selection mask
//
#define IWDG_PR_PR_M            0x00000007  

//
//! Independent watchdog Prescaler Selection shift
//
#define IWDG_PR_PR_S            0  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_WDT_Register_IWDG_RLR IWDG Reload Register(IWDG_RLR)
//! \brief Defines for the bit fields in the IWDG_RLR register
//! @{
//
//*****************************************************************************

//
//! Independent watchdog counter reload mask
//
#define IWDG_RLR_RL_M           0x00000FFF  

//
//! Independent watchdog counter reload shift
//
#define IWDG_RLR_RL_S           0  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_WDT_Register_IWDG_RLR IWDG Status Register(IWDG_SR)
//! \brief Defines for the bit fields in the IWDG_SR register
//! @{
//
//*****************************************************************************

//
//! Independent Watchdog counter reload value update
//
#define IWDG_SR_RVU             0x00000002  

//
//! Independent Watchdog prescaler value update
//
#define IWDG_SR_PUV             0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup STM32F1xx_WDT_Register_WWDG_CR WWDG Control Register(WWDG_CR)
//! \brief Defines for the bit fields in the WWDG_CR register
//! @{
//
//*****************************************************************************

//
//! Window watchdog counter mask
//
#define WWDG_CR_CT_M            0x0000007F  

//
//! Window watchdog counter shift
//
#define WWDG_CR_CT_S            0

//
//! Window watchdog Enable
//
#define WWDG_CR_WDT_EN          0x00000080    

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_WDT_Register_WWDG_CFR WWDG Configuration Register(WWDG_CR)
//! \brief Defines for the bit fields in the WWDG_CFR register
//! @{
//
//*****************************************************************************

//
//! Window watchdog Configuration 7-bit window value mask
//
#define WWDG_CFR_W_M            0x0000007F  

//
//! Window watchdog Configuration 7-bit window value shift
//
#define WWDG_CFR_W_S            0

//
//! Window watchdog Configuration Time Base mask
//
#define WWDG_CFR_WDGTB_M        0x00000180  

//
//! Window watchdog Configuration Time Base shift
//
#define WWDG_CFR_WDGTB_S        7

//
//! Window watchdog Early interrupt Enable
//
#define WWDG_CFR_EWI_EN         0x00000200 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_WDT_Register_WWDG_SR WWDG Status Register(WWDG_SR)
//! \brief Defines for the bit fields in the WWDG_SR register
//! @{
//
//*****************************************************************************

//
//! Window watchdog Early wakeup interrupt flag
//
#define WWDG_SR_EWIF            0x00000001

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



