//*****************************************************************************
//
//! \file xhw_acmp.h
//! \brief Macros used when accessing the comparator hardware.
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
//*****************************************************************************

#ifndef __XHW_ACMP_H__
#define __XHW_ACMP_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ACMP
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_ACMP_Register HT32F125x Analog Comparator Register
//! \brief Here are the detailed info of ACMP registers. 
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
//! \addtogroup HT32F125x_ACMP_Register_Offset ACMP Register Offset(Map)
//! \brief Here is the ACMP register offset, users can get the register address
//! through <b>ACMP_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! Operational Amplifier Control Register
//
#define ACMP_OPACR            0x00000000

//
//! Comparator Input Offset Voltage Cancellation Register
//
#define ACMP_OFVCR            0x00000004

//
//! Comparator Interrupt Enable Register
//
#define ACMP_IER              0x00000008

//
//! Comparator Raw Status Register
//
#define ACMP_RSR              0x0000000C

//
//! Comparator Interrupt Status Register
//
#define ACMP_ISR              0x00000010

//
//! Comparator Interrupt Clear Register
//
#define ACMP_ICLR             0x00000014

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_ACMP_OPACR Comparator Control Register(ACMP_OPACR)
//! \brief Definition for the bit fields in the ACMP_OPACR register.
//! @{
//
//*****************************************************************************

//
//! Comparator Digital Output Status
//
#define ACMP_OPACR_CMPS         0x00000100

//
//! Operational Amplifier Input Offset Cancellation Reference Voltage
//! Selection Bit
//
#define ACMP_OPACR_ARS          0x00000008

//
//! Operational Amplifier / Comparator Mode or Input Offset Voltage 
//! Cancellation Mode Selection
//
#define ACMP_OPACR_AOFM         0x00000004

//
//! Operational Amplifier or Comparator Mode Selection
//
#define ACMP_OPACR_CMS          0x00000002

//
//! Operational Amplifier / Comparator Enable Control Bit
//
#define ACMP_OPACR_EN           0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_ACMP_OFVCR Comparator Input Offset Voltage 
//! Cancellation(ACMP_OFVCR)
//! \brief Definition for the bit fields in the ACMP_OFVCR register.
//! @{
//
//*****************************************************************************

//
//! Operational Amplifier / Comparator Input Offset Voltage Cancellation
//! Control Bit mask
//
#define ACMP_OFVCR_AOF_M        0x0000003F

//
//! Operational Amplifier / Comparator Input Offset Voltage Cancellation
//! Control Bit shift
//
#define ACMP_OFVCR_AOF_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_ACMP_IER Comparator Interrupt Enable Register(ACMP_IER)
//! \brief Definition for the bit fields in the ACMP_IER register.
//! @{
//
//*****************************************************************************

//
//! Comparator Output Rising Edge Interrupt Enable Control Bit
//
#define ACMP_IER_CRIEN          0x00000002

//
//! Comparator Output Falling Edge Interrupt Enable Control Bit
//
#define ACMP_IER_CFIEN          0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_ACMP_RSR Comparator Raw Status Register(ACMP_RSR)
//! \brief Definition for the bit fields in the ACMP_RSR register.
//! @{
//
//*****************************************************************************

//
//! Comparator Output Rising Edge Raw Flag Bit.
//
#define ACMP_RSR_CRRAW          0x00000002

//
//! Comparator Output Falling Edge Interrupt Raw Flag Bit.
//
#define ACMP_RSR_CFRAW          0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_ACMP_ISR Comparator Masked Interrupt Status
//! Register(ACMP_ISR)
//! \brief Definition for the bit fields in the ACMP_ISR register.
//! @{
//
//*****************************************************************************

//
//! Comparator Output Rising Edge Masked Interrupt Flag Bit.
//
#define ACMP_ISR_CRIS           0x00000002

//
//! Comparator Output Falling Edge Masked Interrupt Flag Bit.
//
#define ACMP_ISR_CFIS           0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_ACMP_ICLR Comparator Interrupt Clear
//! Register(ACMP_ICLR)
//! \brief Definition for the bit fields in the ACMP_ICLR register.
//! @{
//
//*****************************************************************************

//
//! Comparator Output Rising Edge Interrupt status Clear Control Bit.
//
#define ACMP_ICLR_CRILCR        0x00000002

//
//! Comparator Output Falling Edge Interrupt status Clear Control Bit.
//
#define ACMP_ICLR_CFILCR        0x00000001

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

#endif // __XHW_ACMP_H__

