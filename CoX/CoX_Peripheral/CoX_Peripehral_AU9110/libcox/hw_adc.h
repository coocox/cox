//*****************************************************************************
//
//! \file hw_adc.h
//! \brief Macros used when accessing the ADC hardware.
//! \version V2.1.1.0
//! \date 7/16/2014
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

#ifndef __HW_ADC_H__
#define __HW_ADC_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ADC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_ADC_Register AU9110 ADC Register
//! \brief Here are the detailed info of ADC registers. 
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
//! \addtogroup AU9110_ADC_Register_Offset ADC Register Offset(Map)
//! \brief Here is the ADC register offset, users can get the register address
//! through <b>ADC_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! FIFO Data Out
//
#define ADC_OUT                 0x00000000

//
//! ADC Enable register
//
#define ADC_EN                  0x00000004

//
//! A/D clock divider register
//
#define ADC_DIV                 0x00000008

//
//! A/D Decimation control register
//
#define ADC_DEC                 0x0000000C

//
//! A/D interrupt control register
//
#define ADC_INT                 0x00000010

//
//! A/D PDMA Control register
//
#define ADC_PDMA                0x00000014

//
//! A/D Comparator0 control register
//
#define ADC_CMPR0               0x00000018

//
//! A/D Comparator1 control register
//
#define ADC_CMPR1               0x0000001C

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_ADC_Register_OUT A/D FIFO Data out (ADC_OUT)
//! \brief FIFO Data Out.
//! @{
//
//*****************************************************************************

//
//! ADC Audio Data FIFO read mask
//
#define ADC_OUT_M               0xFFFFFFFF

//
//! ADC Audio Data FIFO read shift
//
#define ADC_OUT_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_ADC_Register_EN A/D Enable Register (ADC_EN)
//! \brief ADC Enable register.
//! @{
//
//*****************************************************************************

//
//! A/D Conversion enable
//
#define ADC_EN_CREN             0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_ADC_Register_CLKDIV A/D Converter Clock Divider (ADC_DIV)
//! \brief ADC Clock Division Register.
//! @{
//
//*****************************************************************************

//
//! ADC Clock Divider mask
//
#define ADC_DIV_CLKDIV_M        0x000000FF

//
//! ADC Clock Divider shift
//
#define ADC_DIV_CLKDIV_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_ADC_Decimation_Control A/D Decimation Control Register(ADC_DEC)
//! \brief Decimation control register.
//! register.
//! @{
//
//*****************************************************************************

//
//! CIC Filter additional Gain mask
//
#define ADC_DEC_GAIN_M          0x000F0000

//
//! CIC Filter additional Gain shift
//
#define ADC_DEC_GAIN_S          16

//
//! Decimation over-sampling ratio mask
//
#define ADC_DEC_OSR_M           0x000000F

//
//! Decimation over-sampling ratio shift
//
#define ADC_DEC_OSR_S           0

//
//! Decimation over-sampling ratio ,OSR = 64
//
#define ADC_DEC_OSR_64          0x0000000

//
//! Decimation over-sampling ratio ,OSR = 128
//
#define ADC_DEC_OSR_128         0x0000001

//
//! Decimation over-sampling ratio ,OSR = 192
//
#define ADC_DEC_OSR_192         0x0000002

//
//! Decimation over-sampling ratio ,OSR = 384
//
#define ADC_DEC_OSR_384         0x0000003

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_ADC_Interrupt_Control_R A/D interrupt Control Register (ADC_INT)
//! \brief ADC Interrupt Control Register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Enable
//
#define ADC_INT_IE              0x80000000

//
//! FIFO Interrupt Level mask
//
#define ADC_INT_FIFO_IE_LEV_M   0x00000007

//
//! FIFO Interrupt Level shift
//
#define ADC_INT_FIFO_IE_LEV_S   0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_ADC_Register_PDMA A/D PDMA control register (ADC_PDMA)
//! \brief ADC PDMA Control Register.
//! @{
//
//*****************************************************************************

//
//! Enable ADC PDMA Receive Channel
//
#define ADC_PDMA_RXDMAEN        0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_ADC_Register_CMPR01 A/D Compare Register 0/1 (ADC_CMPR01)
//! \brief ADC Comparator control register.
//! @{
//
//*****************************************************************************

//
//! Comparison Data mask
//
#define ADC_CMPR01_CMPD_M       0xFFFF0000

//
//! Comparison Data shift
//
#define ADC_CMPR01_CMPD_S       16

//
//! Compare Match Count mask
//
#define ADC_CMPR01_CMPMATCNT_M  0x00000F00

//
//! Compare Match Count shift
//
#define ADC_CMPR01_CMPMATCNT_S  8

//
//! Compare Flag
//
#define ADC_CMPR01_CMPF         0x00000080

//
//! Compara Condition
//
#define ADC_CMPR01_CMPCOND      0x00000004

//
//! Compara Interrupt Enable
//
#define ADC_CMPR01_CMPIE        0x00000002

//
//! Comparre Enable
//
#define ADC_CMPR01_CMPEN        0x00000001

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

#endif // __XHW_ADC_H__ 

