//*****************************************************************************
//
//! \file xhw_adc.h
//! \brief Macros used when accessing the ADC hardware.
//! \version V2.2.1.0
//! \date 5/4/2012
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

#ifndef __XHW_ADC_H__
#define __XHW_ADC_H__

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
//! \addtogroup HT32F175x_275x_ADC_Register HT32F175x_275x ADC Register
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
//! \addtogroup HT32F175x_275x_ADC_Register_Offset ADC Register Offset(Map)
//! \brief Here is the ADC register offset, users can get the register address
//! through <b>ADC_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! ADC Reset Register
//
#define ADC_RST                 0x00000004

//
//! ADC Regular Conversion Mode Register
//
#define ADC_CONV                0x00000008

//
//! ADC Regular Conversion List Register 0
//
#define ADC_LST0                0x00000010

//
//! ADC Regular Conversion List Register 1
//
#define ADC_LST1                0x00000014

//
//! ADC Regular Conversion List Register 2
//
#define ADC_LST2                0x00000018

//
//! ADC Regular Conversion List Register 3
//
#define ADC_LST3                0x0000001C

//
//! ADC Input 0 Offset Register 
//
#define ADC_OFR0                0x00000030

//
//! ADC Input 1 Offset Register 
//
#define ADC_OFR1                0x00000034

//
//! ADC Input 2 Offset Register 
//
#define ADC_OFR2                0x00000038

//
//! ADC Input 3 Offset Register 
//
#define ADC_OFR3                0x0000003C

//
//! ADC Input 4 Offset Register 
//
#define ADC_OFR4                0x00000040

//
//! ADC Input 5 Offset Register 
//
#define ADC_OFR5                0x00000044

//
//! ADC Input 6 Offset Register 
//
#define ADC_OFR6                0x00000048

//
//! ADC Input 7 Offset Register 
//
#define ADC_OFR7                0x0000004C

//
//! ADC Input 0 Sampling Time Register
//
#define ADC_STR0                0x00000070

//
//! ADC Input 1 Sampling Time Register
//
#define ADC_STR1                0x00000074

//
//! ADC Input 2 Sampling Time Register
//
#define ADC_STR2                0x00000078

//
//! ADC Input 3 Sampling Time Register
//
#define ADC_STR3                0x0000007C

//
//! ADC Input 4 Sampling Time Register
//
#define ADC_STR4                0x00000080

//
//! ADC Input 5 Sampling Time Register
//
#define ADC_STR5                0x00000084

//
//! ADC Input 6 Sampling Time Register
//
#define ADC_STR6                0x00000088

//
//! ADC Input 7 Sampling Time Register
//
#define ADC_STR7                0x0000008C

//
//! A/D Data Register 0
//
#define ADC_DR0                 0x000000B0

//
//! A/D Data Register 1
//
#define ADC_DR1                 0x000000B4

//
//! A/D Data Register 2
//
#define ADC_DR2                 0x000000B8

//
//! A/D Data Register 3
//
#define ADC_DR3                 0x000000BC

//
//! A/D Data Register 4
//
#define ADC_DR4                 0x000000C0

//
//! A/D Data Register 5
//
#define ADC_DR5                 0x000000C4

//
//! A/D Data Register 6
//
#define ADC_DR6                 0x000000C8

//
//! A/D Data Register 7
//
#define ADC_DR7                 0x000000CC

//
//! A/D Data Register 8
//
#define ADC_DR8                 0x000000D0

//
//! A/D Data Register 9
//
#define ADC_DR9                 0x000000D4

//
//! A/D Data Register 10
//
#define ADC_DR10                0x000000D8

//
//! A/D Data Register 11
//
#define ADC_DR11                0x000000DC

//
//! A/D Data Register 12
//
#define ADC_DR12                0x000000E0

//
//! A/D Data Register 13
//
#define ADC_DR13                0x000000E4

//
//! A/D Data Register 14
//
#define ADC_DR14                0x000000E8

//
//! A/D Data Register 15
//
#define ADC_DR15                0x000000EC

//
//! ADC Regular Trigger Control Register
//
#define ADC_TCR                 0x00000100

//
//! ADC Regular Trigger Source Register
//
#define ADC_TSR                 0x00000104

//
//! ADC Watchdog Control Register
//
#define ADC_WCR                 0x00000120

//
//! ADC Watchdog Lower Threshold Register
//
#define ADC_LTR                 0x00000124

//
//! ADC Watchdog Upper Threshold Register
//
#define ADC_UTR                 0x00000128

//
//! ADC Interrupt Mask Enable register
//
#define ADC_IMR                 0x00000130

//
//! ADC Interrupt Raw Status Register
//
#define ADC_IRAW                 0x00000134

//
//! ADC Interrupt Masked Status Register
//
#define ADC_IMASK                0x00000138

//
//! ADC Interrupt Clear Register
//
#define ADC_ICLR                 0x0000013C

//
//! ADC DMA Request Register
//
#define ADC_DMAR                 0x00000140
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_RST A/D Reset Registers (ADC_RST)
//! \brief Defines for the bit fields in the ADC_RST register.
//! @{
//
//*****************************************************************************

//
//! ADC Software Reset
//
#define ADC_ADCRST_ADRST        0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCCONV A/D Conversion Mode Register (ADC_CONV)
//! \brief Defines for the bit fields in the \ref ADC_CONV register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Subgroup Length Mask
//
#define ADC_CONV_SUBL_M         0x000F0000

//
//! A/D Converter Regular Conversion Subgroup Length Shift
//
#define ADC_CONV_SUBL_S         16

//
//! A/D Converter Regular Conversion Sequence Length Mask
//
#define ADC_CONV_SEQL_M         0x00000F00

//
//! A/D Converter Regular Conversion Sequence Length Shift
//
#define ADC_CONV_SEQL_S         8

//
//! A/D Converter Regular Conversion Mode Mask
//
#define ADC_CONV_MODE_M         0x00000003

//
//! A/D Converter Regular Conversion Mode Shift
//
#define ADC_CONV_MODE_S         0

//
//! ADC Discontinuous mode
//
#define ADC_CONV_MODE_DISCONTI  0x00000003

//
//! ADC continuous mode
//
#define ADC_CONV_MODE_CONTI     0x00000002

//
//! ADC one shot mode
//
#define ADC_CONV_MODE_ONESHOT   0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_LST0 A/D Regular Conversion List Register 0 (ADC_LST0)
//! \brief Defines for the bit fields in the \ref ADC_LST0 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Sequence No.0 Mask
//
#define ADC_LST0_ADSEQ0_M       0x0000001F

//
//! A/D Converter Regular Conversion Sequence No.0 (shift)
//
#define ADC_LST0_ADSEQ0_S       0

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.0
//
#define ADC_LST0_ADSEQ0_IN0     0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.0
//
#define ADC_LST0_ADSEQ0_IN1     0x00000001

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.0
//
#define ADC_LST0_ADSEQ0_IN2     0x00000002

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.0
//
#define ADC_LST0_ADSEQ0_IN3     0x00000003

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.0
//
#define ADC_LST0_ADSEQ0_IN4     0x00000004

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.0
//
#define ADC_LST0_ADSEQ0_IN5     0x00000005

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.0
//
#define ADC_LST0_ADSEQ0_IN6     0x00000006

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.0
//
#define ADC_LST0_ADSEQ0_IN7     0x00000007

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.0
//
#define ADC_LST0_ADSEQ0_AGND    0x00000010

//
//! Analog power of A/D Converter Regular Conversion Sequence No.0
//
#define ADC_LST0_ADSEQ0_AVCC    0x00000011

//
//! A/D Converter Regular Conversion Sequence No.1 Mask
//
#define ADC_LST0_ADSEQ1_M       0x00001F00

//
//! A/D Converter Regular Conversion Sequence No.1 (shift)
//
#define ADC_LST0_ADSEQ1_S       8

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_LST0_ADSEQ1_IN0     0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_LST0_ADSEQ1_IN1     0x00000100

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_LST0_ADSEQ1_IN2     0x00000200

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_LST0_ADSEQ1_IN3     0x00000300

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_LST0_ADSEQ1_IN4     0x00000400

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_LST0_ADSEQ1_IN5     0x00000500

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_LST0_ADSEQ1_IN6     0x00000600

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_LST0_ADSEQ1_IN7     0x00000700

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_LST0_ADSEQ1_AGND    0x00001000

//
//! Analog power of A/D Converter Regular Conversion Sequence No.1
//
#define ADC_LST0_ADSEQ1_AVCC    0x00001100

//
//! A/D Converter Regular Conversion Sequence No.2 Mask
//
#define ADC_LST0_ADSEQ2_M       0x001F0000

//
//! A/D Converter Regular Conversion Sequence No.2 (shift)
//
#define ADC_LST0_ADSEQ2_S       16

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.2
//
#define ADC_LST0_ADSEQ2_IN0     0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.2
//
#define ADC_LST0_ADSEQ2_IN1     0x00010000

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.2
//
#define ADC_LST0_ADSEQ2_IN2     0x00020000

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.2
//
#define ADC_LST0_ADSEQ2_IN3     0x00030000

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.2
//
#define ADC_LST0_ADSEQ2_IN4     0x00040000

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.2
//
#define ADC_LST0_ADSEQ2_IN5     0x00050000

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.2
//
#define ADC_LST0_ADSEQ2_IN6     0x00060000

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.2
//
#define ADC_LST0_ADSEQ2_IN7     0x00070000

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.2
//
#define ADC_LST0_ADSEQ2_AGND    0x00100000

//
//! Analog power of A/D Converter Regular Conversion Sequence No.2
//
#define ADC_LST0_ADSEQ2_AVCC    0x00110000

//
//! A/D Converter Regular Conversion Sequence No.3 Mask
//
#define ADC_LST0_ADSEQ3_M       0x1F000000

//
//! A/D Converter Regular Conversion Sequence No.3 (shift)
//
#define ADC_LST0_ADSEQ3_S       28

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.3
//
#define ADC_LST0_ADSEQ3_IN0     0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.3
//
#define ADC_LST0_ADSEQ3_IN1     0x01000000

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.3
//
#define ADC_LST0_ADSEQ3_IN2     0x02000000

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.3
//
#define ADC_LST0_ADSEQ3_IN3     0x03000000

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.3
//
#define ADC_LST0_ADSEQ3_IN4     0x04000000

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.3
//
#define ADC_LST0_ADSEQ3_IN5     0x05000000

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.3
//
#define ADC_LST0_ADSEQ3_IN6     0x06000000

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.3
//
#define ADC_LST0_ADSEQ3_IN7     0x07000000

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.3
//
#define ADC_LST0_ADSEQ3_AGND    0x10000000

//
//! Analog power of A/D Converter Regular Conversion Sequence No.3
//
#define ADC_LST0_ADSEQ3_AVCC    0x11000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_LST1 A/D Regular Conversion List Register 1 (ADC_LST1)
//! \brief Defines for the bit fields in the \ref ADC_LST1 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Sequence No.4 Mask
//
#define ADC_LST1_ADSEQ4_M       0x0000001F

//
//! A/D Converter Regular Conversion Sequence No.4 (shift)
//
#define ADC_LST1_ADSEQ4_S       0

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.4
//
#define ADC_LST1_ADSEQ4_IN0     0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.4
//
#define ADC_LST1_ADSEQ4_IN1     0x00000001

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.4
//
#define ADC_LST1_ADSEQ4_IN2     0x00000002

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.4
//
#define ADC_LST1_ADSEQ4_IN3     0x00000003

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.4
//
#define ADC_LST1_ADSEQ4_IN4     0x00000004

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.4
//
#define ADC_LST1_ADSEQ4_IN5     0x00000005

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.4
//
#define ADC_LST1_ADSEQ4_IN6     0x00000006

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.4
//
#define ADC_LST1_ADSEQ4_IN7     0x00000007

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.4
//
#define ADC_LST1_ADSEQ4_AGND    0x00000010

//
//! Analog power of A/D Converter Regular Conversion Sequence No.4
//
#define ADC_LST1_ADSEQ4_AVCC    0x00000011

//
//! A/D Converter Regular Conversion Sequence No.5 Mask
//
#define ADC_LST1_ADSEQ5_M       0x00001F00

//
//! A/D Converter Regular Conversion Sequence No.5 (shift)
//
#define ADC_LST1_ADSEQ5_S       8

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.5
//
#define ADC_LST1_ADSEQ5_IN0     0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.5
//
#define ADC_LST1_ADSEQ5_IN1     0x00000100

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.5
//
#define ADC_LST1_ADSEQ5_IN2     0x00000200

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.5
//
#define ADC_LST1_ADSEQ5_IN3     0x00000300

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.5
//
#define ADC_LST1_ADSEQ5_IN4     0x00000400

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.5
//
#define ADC_LST1_ADSEQ5_IN5     0x00000500

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.5
//
#define ADC_LST1_ADSEQ5_IN6     0x00000600

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.5
//
#define ADC_LST1_ADSEQ5_IN7     0x00000700

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.5
//
#define ADC_LST1_ADSEQ5_AGND    0x00001000

//
//! Analog power of A/D Converter Regular Conversion Sequence No.5
//
#define ADC_LST1_ADSEQ5_AVCC    0x00001100

//
//! A/D Converter Regular Conversion Sequence No.6 Mask
//
#define ADC_LST1_ADSEQ6_M       0x001F0000

//
//! A/D Converter Regular Conversion Sequence No.6 (shift)
//
#define ADC_LST1_ADSEQ6_S       16

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.6
//
#define ADC_LST1_ADSEQ6_IN0     0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.6
//
#define ADC_LST1_ADSEQ6_IN1     0x00010000

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.6
//
#define ADC_LST1_ADSEQ6_IN2     0x00020000

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.6
//
#define ADC_LST1_ADSEQ6_IN3     0x00030000

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.6
//
#define ADC_LST1_ADSEQ6_IN4     0x00040000

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.6
//
#define ADC_LST1_ADSEQ6_IN5     0x00050000

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.6
//
#define ADC_LST1_ADSEQ6_IN6     0x00060000

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.6
//
#define ADC_LST1_ADSEQ6_IN7     0x00070000

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.6
//
#define ADC_LST1_ADSEQ6_AGND    0x00100000

//
//! Analog power of A/D Converter Regular Conversion Sequence No.6
//
#define ADC_LST1_ADSEQ6_AVCC    0x00110000

//
//! A/D Converter Regular Conversion Sequence No.7 Mask
//
#define ADC_LST1_ADSEQ7_M       0x1F000000

//
//! A/D Converter Regular Conversion Sequence No.7 (shift)
//
#define ADC_LST1_ADSEQ7_S       28

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_LST1_ADSEQ7_IN0     0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_LST1_ADSEQ7_IN1     0x01000000

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_LST1_ADSEQ7_IN2     0x02000000

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_LST1_ADSEQ7_IN3     0x03000000

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_LST1_ADSEQ7_IN4     0x04000000

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_LST1_ADSEQ7_IN5     0x05000000

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_LST1_ADSEQ7_IN6     0x06000000

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_LST1_ADSEQ7_IN7     0x07000000

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_LST1_ADSEQ7_AGND    0x10000000

//
//! Analog power of A/D Converter Regular Conversion Sequence No.7
//
#define ADC_LST1_ADSEQ7_AVCC    0x11000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_LST2 A/D Regular Conversion List Register 2 (ADC_LST2)
//! \brief Defines for the bit fields in the \ref ADC_LST2 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Sequence No.8 Mask
//
#define ADC_LST2_ADSEQ8_M       0x0000001F

//
//! A/D Converter Regular Conversion Sequence No.8 (shift)
//
#define ADC_LST2_ADSEQ8_S       0

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.8
//
#define ADC_LST2_ADSEQ8_IN0     0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.8
//
#define ADC_LST2_ADSEQ8_IN1     0x00000001

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.8
//
#define ADC_LST2_ADSEQ8_IN2     0x00000002

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.8
//
#define ADC_LST2_ADSEQ8_IN3     0x00000003

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.8
//
#define ADC_LST2_ADSEQ8_IN4     0x00000004

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.8
//
#define ADC_LST2_ADSEQ8_IN5     0x00000005

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.8
//
#define ADC_LST2_ADSEQ8_IN6     0x00000006

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.8
//
#define ADC_LST2_ADSEQ8_IN7     0x00000007

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.8
//
#define ADC_LST2_ADSEQ8_AGND    0x00000010

//
//! Analog power of A/D Converter Regular Conversion Sequence No.8
//
#define ADC_LST2_ADSEQ8_AVCC    0x00000011

//
//! A/D Converter Regular Conversion Sequence No.9 Mask
//
#define ADC_LST2_ADSEQ9_M       0x00001F00

//
//! A/D Converter Regular Conversion Sequence No.9 (shift)
//
#define ADC_LST2_ADSEQ9_S       8

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.9
//
#define ADC_LST2_ADSEQ9_IN0     0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.9
//
#define ADC_LST2_ADSEQ9_IN1     0x00000100

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.9
//
#define ADC_LST2_ADSEQ9_IN2     0x00000200

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.9
//
#define ADC_LST2_ADSEQ9_IN3     0x00000300

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.9
//
#define ADC_LST2_ADSEQ9_IN4     0x00000400

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.9
//
#define ADC_LST2_ADSEQ9_IN5     0x00000500

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.9
//
#define ADC_LST2_ADSEQ9_IN6     0x00000600

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.9
//
#define ADC_LST2_ADSEQ9_IN7     0x00000700

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.9
//
#define ADC_LST2_ADSEQ9_AGND    0x00001000

//
//! Analog power of A/D Converter Regular Conversion Sequence No.9
//
#define ADC_LST2_ADSEQ9_AVCC    0x00001100

//
//! A/D Converter Regular Conversion Sequence No.10 Mask
//
#define ADC_LST2_ADSEQ10_M      0x001F0000

//
//! A/D Converter Regular Conversion Sequence No.10 (shift)
//
#define ADC_LST2_ADSEQ10_S      16

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.10
//
#define ADC_LST2_ADSEQ10_IN0    0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.10
//
#define ADC_LST2_ADSEQ10_IN1    0x00010000

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.10
//
#define ADC_LST2_ADSEQ10_IN2    0x00020000

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.10
//
#define ADC_LST2_ADSEQ10_IN3    0x00030000

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.10
//
#define ADC_LST2_ADSEQ10_IN4    0x00040000

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.10
//
#define ADC_LST2_ADSEQ10_IN5    0x00050000

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.10
//
#define ADC_LST2_ADSEQ10_IN6     0x00060000

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.10
//
#define ADC_LST2_ADSEQ10_IN7     0x00070000

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.10
//
#define ADC_LST2_ADSEQ10_AGND    0x00100000

//
//! Analog power of A/D Converter Regular Conversion Sequence No.10
//
#define ADC_LST2_ADSEQ10_AVCC    0x00110000

//
//! A/D Converter Regular Conversion Sequence No.11 Mask
//
#define ADC_LST2_ADSEQ11_M      0x1F000000

//
//! A/D Converter Regular Conversion Sequence No.11 (shift)
//
#define ADC_LST2_ADSEQ11_S      28

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.11
//
#define ADC_LST2_ADSEQ11_IN0    0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.11
//
#define ADC_LST2_ADSEQ11_IN1    0x01000000

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.11
//
#define ADC_LST2_ADSEQ11_IN2    0x02000000

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.11
//
#define ADC_LST2_ADSEQ11_IN3    0x03000000

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.11
//
#define ADC_LST2_ADSEQ11_IN4    0x04000000

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.11
//
#define ADC_LST2_ADSEQ11_IN5    0x05000000

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.11
//
#define ADC_LST2_ADSEQ11_IN6    0x06000000

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.11
//
#define ADC_LST2_ADSEQ11_IN7    0x07000000

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.11
//
#define ADC_LST2_ADSEQ11_AGND   0x10000000

//
//! Analog power of A/D Converter Regular Conversion Sequence No.11
//
#define ADC_LST2_ADSEQ11_AVCC   0x11000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_LST3 A/D Regular Conversion List Register 3 (ADC_LST3)
//! \brief Defines for the bit fields in the \ref ADC_LST3 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Sequence No.12 Mask
//
#define ADC_LST3_ADSEQ12_M      0x0000001F

//
//! A/D Converter Regular Conversion Sequence No.12 (shift)
//
#define ADC_LST3_ADSEQ12_S      0

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.12
//
#define ADC_LST3_ADSEQ12_IN0    0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.12
//
#define ADC_LST3_ADSEQ12_IN1    0x00000001

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.12
//
#define ADC_LST3_ADSEQ12_IN2    0x00000002

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.12
//
#define ADC_LST3_ADSEQ12_IN3    0x00000003

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.12
//
#define ADC_LST3_ADSEQ12_IN4    0x00000004

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.12
//
#define ADC_LST3_ADSEQ12_IN5    0x00000005

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.12
//
#define ADC_LST3_ADSEQ12_IN6    0x00000006

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.12
//
#define ADC_LST3_ADSEQ12_IN7    0x00000007

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.12
//
#define ADC_LST3_ADSEQ12_AGND   0x00000010

//
//! Analog power of A/D Converter Regular Conversion Sequence No.12
//
#define ADC_LST3_ADSEQ12_AVCC   0x00000011

//
//! A/D Converter Regular Conversion Sequence No.13 Mask
//
#define ADC_LST3_ADSEQ13_M      0x00001F00

//
//! A/D Converter Regular Conversion Sequence No.13 (shift)
//
#define ADC_LST3_ADSEQ13_S      8

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_LST3_ADSEQ13_IN0    0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_LST3_ADSEQ13_IN1    0x00000100

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_LST3_ADSEQ13_IN2    0x00000200

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_LST3_ADSEQ13_IN3    0x00000300

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_LST3_ADSEQ13_IN4    0x00000400

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_LST3_ADSEQ13_IN5    0x00000500

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_LST3_ADSEQ13_IN6    0x00000600

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_LST3_ADSEQ13_IN7    0x00000700

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_LST3_ADSEQ13_AGND   0x00001000

//
//! Analog power of A/D Converter Regular Conversion Sequence No.13
//
#define ADC_LST3_ADSEQ13_AVCC   0x00001100

//
//! A/D Converter Regular Conversion Sequence No.14 Mask
//
#define ADC_LST3_ADSEQ14_M      0x001F0000

//
//! A/D Converter Regular Conversion Sequence No.14 (shift)
//
#define ADC_LST3_ADSEQ14_S      16

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.14
//
#define ADC_LST3_ADSEQ14_IN0    0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.14
//
#define ADC_LST3_ADSEQ14_IN1    0x00010000

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.14
//
#define ADC_LST3_ADSEQ14_IN2    0x00020000

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.14
//
#define ADC_LST3_ADSEQ14_IN3    0x00030000

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.14
//
#define ADC_LST3_ADSEQ14_IN4    0x00040000

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.14
//
#define ADC_LST3_ADSEQ14_IN5    0x00050000

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.14
//
#define ADC_LST3_ADSEQ14_IN6     0x00060000

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.14
//
#define ADC_LST3_ADSEQ14_IN7     0x00070000

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.14
//
#define ADC_LST3_ADSEQ14_AGND    0x00100000

//
//! Analog power of A/D Converter Regular Conversion Sequence No.14
//
#define ADC_LST3_ADSEQ14_AVCC    0x00110000

//
//! A/D Converter Regular Conversion Sequence No.15 Mask
//
#define ADC_LST3_ADSEQ15_M      0x1F000000

//
//! A/D Converter Regular Conversion Sequence No.15 (shift)
//
#define ADC_LST3_ADSEQ15_S      28

//
//! Input channel 0 of A/D Converter Regular Conversion Sequence No.15
//
#define ADC_LST3_ADSEQ15_IN0    0x00000000

//
//! Input channel 1 of A/D Converter Regular Conversion Sequence No.15
//
#define ADC_LST3_ADSEQ15_IN1    0x01000000

//
//! Input channel 2 of A/D Converter Regular Conversion Sequence No.15
//
#define ADC_LST3_ADSEQ15_IN2    0x02000000

//
//! Input channel 3 of A/D Converter Regular Conversion Sequence No.15
//
#define ADC_LST3_ADSEQ15_IN3    0x03000000

//
//! Input channel 4 of A/D Converter Regular Conversion Sequence No.15
//
#define ADC_LST3_ADSEQ15_IN4    0x04000000

//
//! Input channel 5 of A/D Converter Regular Conversion Sequence No.15
//
#define ADC_LST3_ADSEQ15_IN5    0x05000000

//
//! Input channel 6 of A/D Converter Regular Conversion Sequence No.15
//
#define ADC_LST3_ADSEQ15_IN6    0x06000000

//
//! Input channel 7 of A/D Converter Regular Conversion Sequence No.15
//
#define ADC_LST3_ADSEQ15_IN7    0x07000000

//
//! Analog ground of A/D Converter Regular Conversion Sequence No.15
//
#define ADC_LST3_ADSEQ15_AGND   0x10000000

//
//! Analog power of A/D Converter Regular Conversion Sequence No.15
//
#define ADC_LST3_ADSEQ15_AVCC   0x11000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCOFR0 ADC Input Offset Register 0(ADCOFR0)
//! \brief Defines for the bit fields in the ADCOFR0 register.
//! @{
//
//*****************************************************************************

//
//!ADC Input Channel 0 Offset Cancellation Enable
//
#define ADC_ADOF0_EN            0x00008000

//
//! ADC Input Channel 0 Offset Value mask
//
#define ADC_ADOF0_M             0x00000FFF

//
//! ADC Input Channel 0 Offset Value Shift
//
#define ADC_ADOF0_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCOFR1 ADC Input Offset Register 1(ADCOFR1)
//! \brief Defines for the bit fields in the ADCOFR1 register.
//! @{
//
//*****************************************************************************

//
//!ADC Input Channel 1 Offset Cancellation Enable
//
#define ADC_ADOF1_EN            0x00008000

//
//! ADC Input Channel 1 Offset Value mask
//
#define ADC_ADOF1_M             0x00000FFF

//
//! ADC Input Channel 1 Offset Value Shift
//
#define ADC_ADOF1_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCOFR2 ADC Input Offset Register 2(ADCOFR2)
//! \brief Defines for the bit fields in the ADCOFR2 register.
//! @{
//
//*****************************************************************************

//
//!ADC Input Channel 2 Offset Cancellation Enable
//
#define ADC_ADOF2_EN            0x00008000

//
//! ADC Input Channel 2 Offset Value mask
//
#define ADC_ADOF2_M             0x00000FFF

//
//! ADC Input Channel 2 Offset Value Shift
//
#define ADC_ADOF2_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCOFR2 ADC Input Offset Register 2(ADCOFR2)
//! \brief Defines for the bit fields in the ADCOFR2 register.
//! @{
//
//*****************************************************************************

//
//!ADC Input Channel 2 Offset Cancellation Enable
//
#define ADC_ADOF2_EN            0x00008000

//
//! ADC Input Channel 2 Offset Value mask
//
#define ADC_ADOF2_M             0x00000FFF

//
//! ADC Input Channel 2 Offset Value Shift
//
#define ADC_ADOF2_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCOFR3 ADC Input Offset Register 3(ADCOFR3)
//! \brief Defines for the bit fields in the ADCOFR3 register.
//! @{
//
//*****************************************************************************

//
//!ADC Input Channel 3 Offset Cancellation Enable
//
#define ADC_ADOF3_EN            0x00008000

//
//! ADC Input Channel 3 Offset Value mask
//
#define ADC_ADOF3_M             0x00000FFF

//
//! ADC Input Channel 3 Offset Value Shift
//
#define ADC_ADOF3_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCOFR4 ADC Input Offset Register 4(ADCOFR4)
//! \brief Defines for the bit fields in the ADCOFR4 register.
//! @{
//
//*****************************************************************************

//
//!ADC Input Channel 4 Offset Cancellation Enable
//
#define ADC_ADOF4_EN            0x00008000

//
//! ADC Input Channel 4 Offset Value mask
//
#define ADC_ADOF4_M             0x00000FFF

//
//! ADC Input Channel 4 Offset Value Shift
//
#define ADC_ADOF4_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCOFR5 ADC Input Offset Register 5(ADCOFR5)
//! \brief Defines for the bit fields in the ADCOFR5 register.
//! @{
//
//*****************************************************************************

//
//!ADC Input Channel 5 Offset Cancellation Enable
//
#define ADC_ADOF5_EN            0x00008000

//
//! ADC Input Channel 5 Offset Value mask
//
#define ADC_ADOF5_M             0x00000FFF

//
//! ADC Input Channel 5 Offset Value Shift
//
#define ADC_ADOF5_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCOFR6 ADC Input Offset Register 6(ADCOFR6)
//! \brief Defines for the bit fields in the ADCOFR6 register.
//! @{
//
//*****************************************************************************

//
//!ADC Input Channel 6 Offset Cancellation Enable
//
#define ADC_ADOF6_EN            0x00008000

//
//! ADC Input Channel 6 Offset Value mask
//
#define ADC_ADOF6_M             0x00000FFF

//
//! ADC Input Channel 6 Offset Value Shift
//
#define ADC_ADOF6_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCOFR7 ADC Input Offset Register 7(ADCOFR7)
//! \brief Defines for the bit fields in the ADCOFR7 register.
//! @{
//
//*****************************************************************************

//
//!ADC Input Channel 7 Offset Cancellation Enable
//
#define ADC_ADOF7_EN            0x00008000

//
//! ADC Input Channel 7 Offset Value mask
//
#define ADC_ADOF7_M             0x00000FFF

//
//! ADC Input Channel 7 Offset Value Shift
//
#define ADC_ADOF7_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCSTR0 A/D Input Sampling Time Register(ADC_ADCSTR0)
//! \brief Defines for the bit fields in the ADC_ADCSTR0 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Input Channel 0 Sampling Time mask
//
#define ADC_STR0_M              0x000000FF

//
//! A/D Converter Input Channel 0 Sampling Time shift
//
#define ADC_STR0_S              0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCSTR1 A/D Input Sampling Time Register(ADC_ADCSTR1)
//! \brief Defines for the bit fields in the ADC_ADCSTR1 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Input Channel 1 Sampling Time mask
//
#define ADC_STR1_M              0x000000FF

//
//! A/D Converter Input Channel 1 Sampling Time shift
//
#define ADC_STR1_S              0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCSTR2 A/D Input Sampling Time Register(ADC_ADCSTR2)
//! \brief Defines for the bit fields in the ADC_ADCSTR2 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Input Channel 2 Sampling Time mask
//
#define ADC_STR2_M              0x000000FF

//
//! A/D Converter Input Channel 2 Sampling Time shift
//
#define ADC_STR2_S              0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCSTR3 A/D Input Sampling Time Register(ADC_ADCSTR3)
//! \brief Defines for the bit fields in the ADC_ADCSTR3 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Input Channel 3 Sampling Time mask
//
#define ADC_STR3_M              0x000000FF

//
//! A/D Converter Input Channel 3 Sampling Time shift
//
#define ADC_STR3_S              0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCSTR4 A/D Input Sampling Time Register(ADC_ADCSTR4)
//! \brief Defines for the bit fields in the ADC_ADCSTR4 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Input Channel 4 Sampling Time mask
//
#define ADC_STR4_M              0x000000FF

//
//! A/D Converter Input Channel 4 Sampling Time shift
//
#define ADC_STR4_S              0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCSTR5 A/D Input Sampling Time Register(ADC_ADCSTR5)
//! \brief Defines for the bit fields in the ADC_ADCSTR5 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Input Channel 5 Sampling Time mask
//
#define ADC_STR5_M              0x000000FF

//
//! A/D Converter Input Channel 5 Sampling Time shift
//
#define ADC_STR5_S              0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCSTR6 A/D Input Sampling Time Register(ADC_ADCSTR6)
//! \brief Defines for the bit fields in the ADC_ADCSTR6 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Input Channel 6 Sampling Time mask
//
#define ADC_STR6_M              0x000000FF

//
//! A/D Converter Input Channel 6 Sampling Time shift
//
#define ADC_STR6_S              0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCSTR7 A/D Input Sampling Time Register(ADC_ADCSTR7)
//! \brief Defines for the bit fields in the ADC_ADCSTR7 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Input Channel 7 Sampling Time mask
//
#define ADC_STR7_M              0x000000FF

//
//! A/D Converter Input Channel 7 Sampling Time shift
//
#define ADC_STR7_S              0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR0 A/D Regular Conversion Data Register (ADC_DR0)
//! \brief Defines for the bit fields in the ADC_DR0 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.0 Valid Bit 
//
#define ADC_DR0_ADVLD           0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.0 Mask
//
#define ADC_DR0_ADD0_M          0x00000FFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.0 Shift
//
#define ADC_DR0_ADD0_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR1 A/D Regular Conversion Data Register (ADC_DR1)
//! \brief Defines for the bit fields in the ADC_DR1 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.1 Valid Bit 
//
#define ADC_DR1_ADVLD           0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.1 Mask
//
#define ADC_DR1_ADD1_M          0x0000FFFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.1 Shift
//
#define ADC_DR1_ADD1_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR2 A/D Regular Conversion Data Register (ADC_DR2)
//! \brief Defines for the bit fields in the ADC_DR2 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.2 Valid Bit 
//
#define ADC_DR2_ADVLD           0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.2 Mask
//
#define ADC_DR2_ADD2_M          0x0000FFFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.2 Shift
//
#define ADC_DR2_ADD2_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR3 A/D Regular Conversion Data Register (ADC_DR3)
//! \brief Defines for the bit fields in the ADC_DR3 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.3 Valid Bit 
//
#define ADC_DR3_ADVLD           0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.3 Mask
//
#define ADC_DR3_ADD3_M          0x0000FFFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.3 Shift
//
#define ADC_DR3_ADD3_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR4 A/D Regular Conversion Data Register (ADC_DR4)
//! \brief Defines for the bit fields in the ADC_DR4 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.4 Valid Bit 
//
#define ADC_DR4_ADVLD           0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.4 Mask
//
#define ADC_DR4_ADD4_M          0x0000FFFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.4 Shift
//
#define ADC_DR4_ADD4_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR5 A/D Regular Conversion Data Register (ADC_DR5)
//! \brief Defines for the bit fields in the ADC_DR5 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.5 Valid Bit 
//
#define ADC_DR5_ADVLD           0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.5 Mask
//
#define ADC_DR5_ADD5_M          0x0000FFFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.5 Shift
//
#define ADC_DR5_ADD5_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR6 A/D Regular Conversion Data Register (ADC_DR6)
//! \brief Defines for the bit fields in the ADC_DR6 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.6 Valid Bit 
//
#define ADC_DR6_ADVLD           0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.6 Mask
//
#define ADC_DR6_ADD6_M          0x0000FFFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.6 Shift
//
#define ADC_DR6_ADD6_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR7 A/D Regular Conversion Data Register (ADC_DR7)
//! \brief Defines for the bit fields in the ADC_DR7 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.7 Valid Bit 
//
#define ADC_DR7_ADVLD           0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.7 Mask
//
#define ADC_DR7_ADD7_M          0x0000FFFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.7 Shift
//
#define ADC_DR7_ADD7_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR8 A/D Regular Conversion Data Register (ADC_DR8)
//! \brief Defines for the bit fields in the ADC_DR8 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.8 Valid Bit 
//
#define ADC_DR8_ADVLD           0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.8 Mask
//
#define ADC_DR8_ADD8_M          0x0000FFFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.8 Shift
//
#define ADC_DR8_ADD8_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR9 A/D Regular Conversion Data Register (ADC_DR9)
//! \brief Defines for the bit fields in the ADC_DR9 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.9 Valid Bit 
//
#define ADC_DR9_ADVLD           0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.9 Mask
//
#define ADC_DR9_ADD9_M          0x0000FFFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.9 Shift
//
#define ADC_DR9_ADD9_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR10 A/D Regular Conversion Data Register (ADC_DR10)
//! \brief Defines for the bit fields in the ADC_DR10 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.10 Valid Bit 
//
#define ADC_DR10_ADVLD          0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.10 Mask
//
#define ADC_DR10_ADD10_M        0x0000FFFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.10 Shift
//
#define ADC_DR10_ADD10_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR11 A/D Regular Conversion Data Register (ADC_DR11)
//! \brief Defines for the bit fields in the ADC_DR11 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.11 Valid Bit 
//
#define ADC_DR11_ADVLD          0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.11 Mask
//
#define ADC_DR11_ADD11_M        0x0000FFFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.11 Shift
//
#define ADC_DR11_ADD11_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR12 A/D Regular Conversion Data Register (ADC_DR12)
//! \brief Defines for the bit fields in the ADC_DR12 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.12 Valid Bit 
//
#define ADC_DR12_ADVLD          0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.12 Mask
//
#define ADC_DR12_ADD12_M        0x0000FFFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.12 Shift
//
#define ADC_DR12_ADD12_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR13 A/D Regular Conversion Data Register (ADC_DR13)
//! \brief Defines for the bit fields in the ADC_DR13 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.13 Valid Bit 
//
#define ADC_DR13_ADVLD          0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.13 Mask
//
#define ADC_DR13_ADD13_M        0x0000FFFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.13 Shift
//
#define ADC_DR13_ADD13_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR14 A/D Regular Conversion Data Register (ADC_DR14)
//! \brief Defines for the bit fields in the ADC_DR14 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.14 Valid Bit 
//
#define ADC_DR14_ADVLD          0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.14 Mask
//
#define ADC_DR14_ADD14_M        0x0000FFFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.14 Shift
//
#define ADC_DR14_ADD14_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_DR15 A/D Regular Conversion Data Register (ADC_DR15)
//! \brief Defines for the bit fields in the ADC_DR15 register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Data of the sequence No.15 Valid Bit 
//
#define ADC_DR15_ADVLD          0x80000000

//
//! A/D Converter Regular Conversion Data of the sequence N0.15 Mask
//
#define ADC_DR15_ADD15_M        0x0000FFFF

//
//! A/D Converter Regular Conversion Data of the sequence N0.15 Shift
//
#define ADC_DR15_ADD15_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCTCR A/D Regular Trigger Register (ADC_ADCTCR)
//! \brief Defines for the bit fields in the ADC_ADCTCR register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Software Trigger Enbale control
//
#define ADC_TCR_ADSW_EN         0x00000001

//
//! A/D Converter Regular Conversion EXTI Event Trigger Enbale control
//
#define ADC_TCR_ADEXTI_EN       0x00000002

//
//! A/D Converter Regular Conversion GPTM Event Trigger Enbale control
//
#define ADC_TCR_ADTM_EN         0x00000004

//
//! A/D Converter Regular Conversion BFTM Event Trigger Enbale control
//
#define ADC_TCR_BFTM_EN         0x00000008

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCTSR A/D Regular Trigger Register (ADC_ADCTSR)
//! \brief Defines for the bit fields in the ADC_ADCTSR register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Regular Conversion Software Trigger Bit
//
#define ADC_TSR_ADSC            0x00000001

//
//! A/D Converter Regular Conversion EXTI lin0 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI0   0x00000000

//
//! A/D Converter Regular Conversion EXTI lin1 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI1   0x00000100

//
//! A/D Converter Regular Conversion EXTI lin2 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI2   0x00000200

//
//! A/D Converter Regular Conversion EXTI lin3 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI3   0x00000300

//
//! A/D Converter Regular Conversion EXTI lin4 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI4   0x00000400

//
//! A/D Converter Regular Conversion EXTI lin5 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI5   0x00000500

//
//! A/D Converter Regular Conversion EXTI lin6 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI6   0x00000600

//
//! A/D Converter Regular Conversion EXTI lin7 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI7   0x00000700

//
//! A/D Converter Regular Conversion EXTI lin8 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI8   0x00000800

//
//! A/D Converter Regular Conversion EXTI lin9 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI9   0x00000900

//
//! A/D Converter Regular Conversion EXTI lin10 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI10  0x00000A00

//
//! A/D Converter Regular Conversion EXTI lin11 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI11  0x00000B00

//
//! A/D Converter Regular Conversion EXTI lin12 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI12  0x00000C00

//
//! A/D Converter Regular Conversion EXTI lin13 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI13  0x00000D00

//
//! A/D Converter Regular Conversion EXTI lin14 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI14  0x00000E00

//
//! A/D Converter Regular Conversion EXTI lin15 rising edge
//
#define ADC_TSR_ADEXTIS_EXTI15  0x00000F00

//
//! MCTM Trigger
//
#define ADC_TSR_GPTMS_MCTM      0x00000000

//
//! GPTM0 Trigger
//
#define ADC_TSR_GPTMS_TM0       0x00020000

//
//! GPTM1 Trigger
//
#define ADC_TSR_GPTMS_TM1       0x00030000

//
//! BFTM0 Trigger
//
#define ADC_TSR_GPTMS_BFTM0     0x00000000

//
//! BFTM1 Trigger
//
#define ADC_TSR_GPTMS_BFTM1     0x00080000

//
//!  GPTM MTO or GPTM Trigger Event selection
//
#define ADC_TSR_GPTME_MT0       0x00000000

//
//! GPTM or MCTM CH0O Event selection 
//
#define ADC_TSR_GPTME_CH0       0x01000000

//
//! GPTM or MCTM CH1O Event selection
//
#define ADC_TSR_GPTME_CH1       0x0200000

//
//! GPTM or MCTM CH2O Event selection
//
#define ADC_TSR_GPTME_CH2       0x03000000

//
//! GPTM or MCTM CH3O Event selection
//
#define ADC_TSR_GPTME_CH3       0x04000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCWCR A/D Watchdog Control Register (ADC_WCR)
//! \brief Defines for the bit fields in the ADC_WCR register.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Watchdog Lower Threshold Monitor Enable Bit
//
#define ADC_WCR_ADWLE           0x00000001

//
//! A/D Converter Watchdog Upper Threshold Monitor Enable Bit
//
#define ADC_WCR_ADWUE           0x00000002

//
//! A/D Converter all channels are monitored.
//
#define ADC_WCR_ADWALL          0x00000004

//
//! A/D Converter Specific channel is monitored.
//
#define ADC_WCR_ADSPEC          0x00000000

//
//! ADC channel monitor Mask
//
#define ADC_WCR_ADWCH_M         0x00000F00

//
//! ADC channel monitor Shift
//
#define ADC_WCR_ADWCH_S         8

//
//! ADC_IN0 is monitored
//
#define ADC_WCR_ADWCH_IN0       0x00000000

//
//! ADC_IN1 is monitored
//
#define ADC_WCR_ADWCH_IN1       0x00000100

//
//! ADC_IN2 is monitored
//
#define ADC_WCR_ADWCH_IN2       0x00000200

//
//! ADC_IN3 is monitored
//
#define ADC_WCR_ADWCH_IN3       0x00000300

//
//! ADC_IN4 is monitored
//
#define ADC_WCR_ADWCH_IN4       0x00000400

//
//! ADC_IN5 is monitored
//
#define ADC_WCR_ADWCH_IN5       0x00000500

//
//! ADC_IN6 is monitored
//
#define ADC_WCR_ADWCH_IN6       0x00000600

//
//! ADC_IN7 is monitored
//
#define ADC_WCR_ADWCH_IN7       0x00000700

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCLTR A/D Watchdog Lower Threshold Register (ADC_LTR)
//! \brief Defines for the bit fields in the ADC_LTR register.
//! @{
//
//*****************************************************************************


//
//! A/D Converter Watchdog Lower Threshold Value Mask
//
#define ADC_ADCLTR_ADLT_M       0x00000FFF

//
//! A/D Converter Watchdog Lower Threshold Value Shift
//
#define ADC_ADCLTR_ADLT_S       0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCUTR A/D Watchdog Upper Threshold Register (ADC_UTR)
//! \brief Defines for the bit fields in the ADC_UTR register.
//! @{
//
//*****************************************************************************


//
//! A/D Converter Watchdog Upper Threshold Value Mask
//
#define ADC_ADCUTR_ADUT_M       0x00000FFF

//
//! A/D Converter Watchdog Upper Threshold Value Shift
//
#define ADC_ADCUTR_ADUT_S       0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCIMR A/D Interrupt Mask Enable Register (ADC_IMR)
//! \brief Defines for the bit fields in the ADC_IMR register.
//! @{
//
//*****************************************************************************


//
//! A/D Converter Regular Single EOC Interrupt Mask
//
#define ADC_ADCIMR_ADIMS_EN     0x00000001

//
//! A/D Converter Regular Subgroup EOC Interrupt Mask
//
#define ADC_ADCIMR_ADIMG_EN     0x00000002

//
//! A/D Converter Regular Cycle EOC Interrupt Mask
//
#define ADC_ADCIMR_ADIMC_EN     0x00000004

//
//! A/D Converter Watchdog Lower Threshold Interrupt Mask
//
#define ADC_ADCIMR_ADIML_EN     0x00010000

//
//! A/D Converter Watchdog Upper Threshold Interrupt Mask
//
#define ADC_ADCIMR_ADIMU_EN     0x00020000

//
//! A/D Converter Regular Data Register Overwrite Interrupt Mask
//
#define ADC_ADCIMR_ADIMO_EN     0x01000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCIRAW A/D Interrupt Raw Status Register (ADC_IRAW)
//! \brief Defines for the bit fields in the ADC_IRAW register.
//! @{
//
//*****************************************************************************


//
//! A/D Converter Regular Single EOC Interrupt Raw Status
//
#define ADC_ADCIRAW_ADIRAWS     0x00000001

//
//! A/D Converter Regular Subgroup EOC Interrupt Raw Status
//
#define ADC_ADCIRAW_ADIRAWG     0x00000002

//
//! A/D Converter Regular Cycle EOC Interrupt Raw Status
//
#define ADC_ADCIRAW_ADIRAWC     0x00000004

//
//! A/D Converter Watchdog Lower Threshold Interrupt Raw Status
//
#define ADC_ADCIRAW_ADIRAWL     0x00010000

//
//! A/D Converter Watchdog Upper Threshold Interrupt Raw Status
//
#define ADC_ADCIRAW_ADIRAWU     0x00020000

//
//! A/D Converter Regular Data Register Overwrite Interrupt Raw Status
//
#define ADC_ADCIRAW_ADIRAWO     0x01000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCIMASK A/D Interrupt Masked Status Register (ADC_IMASK)
//! \brief Defines for the bit fields in the ADC_IMASK register.
//! @{
//
//*****************************************************************************


//
//! A/D Converter Regular Single EOC Interrupt Masked Status
//
#define ADC_ADCIMASK_ADIMASKS   0x00000001

//
//! A/D Converter Regular Subgroup EOC Interrupt Masked Status
//
#define ADC_ADCIMASK_ADIMASKG   0x00000002

//
//! A/D Converter Regular Cycle EOC Interrupt Masked Status
//
#define ADC_ADCIMASK_ADIMASKC   0x00000004

//
//! A/D Converter Watchdog Lower Threshold Interrupt Masked Status
//
#define ADC_ADCIMASK_ADIMASKL   0x00010000

//
//! A/D Converter Watchdog Upper Threshold Interrupt Masked Status
//
#define ADC_ADCIMASK_ADIMASKU   0x00020000

//
//! A/D Converter Regular Data Register Overwrite Interrupt Masked Status
//
#define ADC_ADCIMASK_ADIMASKO   0x01000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCICLR A/D Interrupt Clear Register (ADC_ICLR)
//! \brief Defines for the bit fields in the ADC_ICLR register.
//! @{
//
//*****************************************************************************


//
//! A/D Converter Regular Single EOC Interrupt Clear Bit
//
#define ADC_ADCICLR_ADICLRS     0x00000001

//
//! A/D Converter Regular Subgroup EOC Interrupt Clear Bit
//
#define ADC_ADCICLR_ADICLRG     0x00000002

//
//! A/D Converter Regular Cycle EOC Interrupt Clear Bit
//
#define ADC_ADCICLR_ADICLRC     0x00000004

//
//! A/D Converter Watchdog Lower Threshold Interrupt Clear Bit
//
#define ADC_ADCICLR_ADICLRL     0x00010000

//
//! A/D Converter Watchdog Upper Threshold Interrupt Clear Bit
//
#define ADC_ADCICLR_ADICLRU     0x00020000

//
//! A/D Converter Regular Data Register Overwrite InterruptClear Bit
//
#define ADC_ADCICLR_ADICLRO     0x01000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_ADC_Register_ADCDMAR ADC DMA Request Register(ADCDMAR)
//! \brief Defines for the bit fields in the ADC_DMAR register.
//! @{
//
//*****************************************************************************

//
//! ADC Regular Single EOC DMA Request Enable Bit
//
#define ADC_ADCDMAR_ADDMAS      0x00000001

//
//! ADC Regular Subgroup EOC DMA Request Enable Bit
//
#define ADC_ADCDMAR_ADDMAG      0x00000002

//
//! ADC Regular Cycle EOC DMA Request Enable Bit
//
#define ADC_ADCDMAR_ADDMAC      0x00000004

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

