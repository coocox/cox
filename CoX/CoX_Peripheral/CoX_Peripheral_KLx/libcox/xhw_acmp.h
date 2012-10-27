//*****************************************************************************
//
//! \file xhw_acmp.h
//! \brief Macros used when accessing the comparator hardware.
//! \version V2.2.1.1
//! \date 8/23/2012
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
//! \addtogroup KLx_ACMP_Register KLx Analog Comparator Register
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
//! \addtogroup KLx_ACMP_Register_Offset ACMP Register Offset(Map)
//! \brief Here is the ACMP register offset, users can get the register address
//! through <b>ACMP_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! CMP Control Register 0
//
#define CMP0_CR0                0x00000000

//
//! CMP Control Register 1
//
#define CMP0_CR1                0x00000001

//
//! CMP Filter Period Register 
//
#define CMP0_FPR                0x00000002

//
//! CMP Status and Control Register
//
#define CMP0_SCR                0x00000003

//
//! DAC Control Register 
//
#define CMP0_DACCR              0x00000004

//
//! MUX Control Register
//
#define CMP0_MUXCR              0x00000005

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ACMP_Register_CR0 Comparator Control Register 0(CMP0_CR0)
//! \brief Definition for the bit fields in the CMP0_CR0 register.
//! @{
//
//*****************************************************************************

//
//! Comparator hard block programmable hysteresis level Mask
//
#define CMP0_CR0_HYSTCTR_M      0x03

//
//! Comparator hard block programmable hysteresis level Shift
//
#define CMP0_CR0_HYSTCTR_S      0

//
//! Filter Sample Count Mask
//
#define CMP0_CR0_FILTER_CNT_M   0x70

//
//! Filter Sample Count Shift
//
#define CMP0_CR0_FILTER_CNT_S   4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ACMP_Register_CR1 Comparator Control Register 1(CMP0_CR1)
//! \brief Definition for the bit fields in the CMP0_CR1 register.
//! @{
//
//*****************************************************************************

//
//! Comparator Module Enable
//
#define CMP0_CR1_EN             0x01

//
//! Comparator Output Pin Enable
//
#define CMP0_CR1_OPE            0x02

//
//! Set the unfiltered comparator output (CMPO) to equal COUTA
//
#define CMP0_CR1_COS            0x04

//
//! Inverts the comparator output
//
#define CMP0_CR1_INV            0x08

//
//! Power Mode Select(High-Speed (HS) Comparison mode selected)
//
#define CMP0_CR1_PMODE          0x10

//
//! Trigger Mode Enable
//
#define CMP0_CR1_TRIGM          0x20

//
//! Windowing Enable
//
#define CMP0_CR1_WE             0x40

//
//! Sample Enable
//
#define CMP0_CR1_SE             0x80
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ACMP_Register_FILT_PER Comparator Filter Period Register(CMP0_FILT_PER)
//! \brief Definition for the bit fields in the CMP0_FILT_PER register.
//! @{
//
//*****************************************************************************

//
//! Filter Sample Period Mask
//
#define CMP0_FPR_FILT_PER_M     0xFF

//
//! Filter Sample Period Shift
//
#define CMP0_FPR_FILT_PER_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ACMP_Register_SCR Comparator Status and Control Register 1(CMP0_SCR)
//! \brief Definition for the bit fields in the CMP0_SCR register.
//! @{
//
//*****************************************************************************

//
//! Analog Comparator Output
//
#define CMP0_SCR_COUT           0x01

//
//! Analog Comparator Flag Falling(Falling-edge on COUT has occurred)
//
#define CMP0_SCR_CFF            0x02

//
//! Analog Comparator Flag Rising(Rising-edge on COUT has occurred)
//
#define CMP0_SCR_CFR            0x04

//
//! Comparator Interrupt Enable Falling
//
#define CMP0_SCR_IEF            0x08

//
//!Comparator Interrupt Enable Rising
//
#define CMP0_SCR_IER            0x10

//
//! DMA Enable Control
//
#define CMP0_SCR_DMAEN          0x40
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ACMP_Register_DACCR Comparator DAC Control Register(CMP0_DACCR)
//! \brief Definition for the bit fields in the CMP0_DACCR register.
//! @{
//
//*****************************************************************************

//
//! DAC Output Voltage Select Mask
//
#define CMP0_DACCR_VOSEL_M      0x3F

//
//! DAC Output Voltage Select Shift
//
#define CMP0_DACCR_VOSEL_S      0

//
//! Supply Voltage Reference Source Select
//
#define CMP0_DACCR_VRSEL        0x40

//
//! Comparator1 Flag
//
#define CMP0_DACCR_DACEN        0x80

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_ACMP_Register_MUXCR Comparator MUX Control Register(CMP0_MUXCR)
//! \brief Definition for the bit fields in the CMP0_MUXCR register.
//! @{
//
//*****************************************************************************

//
//! Minus Input Mux Control Mask
//
#define CMP0_MUXCR_MSEL_M       0x07

//
//! Minus Input Mux Control Shift
//
#define CMP0_MUXCR_MSEL_S       0

//
//! Plus Input Mux Control Mask
//
#define CMP0_MUXCR_PSEL_M       0x38

//
//! Plus Input Mux Control Shift
//
#define CMP0_MUXCR_PSEL_S       3

//
//!Pass Through Mode Enable
//
#define CMP0_MUXCR_PSTM         0x40

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

