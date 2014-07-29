//*****************************************************************************
//
//! \file hw_dma.h
//! \brief Macros and defines used when accessing the DMA hardware.
//! \version V2.1.1.1
//! \date 7/1/2014
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2014, CooCox
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
#ifndef __XHW_DMA_H__
#define __XHW_DMA_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup DMA
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register NUC4xx DMA Register
//! \brief Here are the detailed info of DMA registers. 
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
//! \addtogroup NUC4xx_DMA_Register_Offset DMA Register Offset(Map)
//! \brief Here is the DMA register offset, users can get the register address
//! through <b>DMA_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! DMA Control and Status Register
//
#define DMA_CTRL                0x00000000

//
//! DMA Transfer Source Address Register
//
#define DMA_SAR                 0x00000004

//
//! DMA Destination Address Register
//
#define DMA_DAR                 0x00000008

//
//! DMA Scatter-Gather Descriptor Table Offset Address
//
#define DMA_NEXT                0x0000000C

//
//! DMA Current Scatter-Gather Descriptor Table Address
//
#define DMA_CURSCAT             0x00000100

//
//! DMA Channel Control Register
//
#define DMA_CHCON               0x00000400

//
//! DMA Stop Transfer Register
//
#define DMA_STOP                0x00000404

//
//! DMA Software Request Register
//
#define DMA_SWREQ               0x00000408

//
//! DMA Request Active Flag Register
//
#define DMA_REQACTF             0x0000040C

//
//! DMA Fixed Priority Setting Register
//
#define DMA_FPSET               0x00000410

//
//! DMA Fixed Priority Clear Register
//
#define DMA_FPCLR               0x00000414

//
//! DMA Interrupt Enable Control Register
//
#define DMA_IER                 0x00000418

//
//! DMA Interrupt Status Register
//
#define DMA_ISR                 0x0000041C

//
//! DMA Read/Write Target Abort Flag Register
//
#define DMA_ABTF                0x00000420

//
//! DMA Transfer Done Flag Register
//
#define DMA_TDF                 0x00000424

//
//! DMA Scatter-Gather Transfer Done Flag Register
//
#define DMA_SCATDF              0x00000428

//
//! DMA Transfer on Active Flag Register
//
#define DMA_ACTF                0x0000042C

//
//! DMA  Scatter-Gather  Descriptor  Table   Base  Address Register
//
#define DMA_SCATBA              0x0000043C

//
//! DMA Time-out Period Counter Ch1 and Ch0 Register
//
#define DMA_TOC0                0x00000440

//
//! DMA Time-out Period Counter Ch3 and Ch2 Register
//
#define DMA_TOC1                0x00000444

//
//! DMA Time-out Period Counter Ch5 and Ch4 Register
//
#define DMA_TOC2                0x00000448

//
//! DMA Time-out Period Counter Ch7 and Ch6 Register
//
#define DMA_TOC3                0x0000044C

//
//! DMA Time-out Period Counter Ch9 and Ch8 Register
//
#define DMA_TOC4                0x00000450

//
//! DMA Time-out Period Counter Ch11 and Ch10 Register
//
#define DMA_TOC5                0x00000454

//
//! DMA Time-out Period Counter Ch13 and Ch12 Register
//
#define DMA_TOC6                0x00000458

//
//! DMA Time-out Period Counter Ch15 and Ch14 Register
//
#define DMA_TOC7                0x0000045C

//
//! DMA Source Module Select Register 0
//
#define DMA_SMSEL0              0x00000480

//
//! DMA Source Module Select Register 1
//
#define DMA_SMSEL1              0x00000484

//
//! DMA Source Module Select Register 2
//
#define DMA_SMSEL2              0x00000488

//
//! DMA Source Module Select Register 3
//
#define DMA_SMSEL3              0x0000048C

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_CSR DMA Control Register(DMA_CTRL)
//! \brief Defines for the bit fields in the DMA_CTRL register.
//! @{
//
//*****************************************************************************

//
//! DMA Operation Mode Selection
//
#define DMA_CTRL_DMA_MODE_M     0x00000003
#define DMA_CTRL_DMA_MODE_S     0

//
//! Request Type
//
#define DMA_CTRL_REQ_TYPE       BIT_32_2

//
//! Burst Size
//
#define DMA_CTRL_BUR_SIZE_M     BIT_MASK(32,6,4)
#define DMA_CTRL_BUR_SIZE_S     4

//
//! Table Interrupt Disable Control
//
#define DMA_CTRL_TABINT_DIS    BIT_32_7

//
//! Source Address Increment
//
#define DMA_CTRL_SAR_INC_M      BIT_MASK(32, 9, 8)
#define DMA_CTRL_SAR_INC_S      8

//
//! Destination Address Increment
//
#define DMA_CTRL_DAR_INC_M      BIT_MASK(32, 11, 10)
#define DMA_CTRL_DAR_INC_S      10

//
//! Transfer Width Selection
//
#define DMA_CTRL_TWS_M          BIT_MASK(32, 13, 12)
#define DMA_CTRL_TWS_S          12

//
//! Transfer Count
//
#define DMA_CTRL_TFR_CNT_M      BIT_MASK(32, 29, 16)
#define DMA_CTRL_TFR_CNT_S      16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_SAR DMA Source Address Register(DMA_SAR)
//! \brief Defines for the bit fields in the DMA_SAR register.
//! @{
//
//*****************************************************************************

//
//! DMA Transfer Ending Source Address Bits Mark
//
#define DMA_SAR_DMA_ENDSAR_M    0xFFFFFFFF

//
//! DMA Transfer Ending Source Address Bits Shift
//
#define DMA_SAR_DMA_ENDSAR_S    0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_DAR DMA Destination Register(DMA_DAR)
//! \brief Defines for the bit fields in the DMA_DAR register.
//! @{
//
//*****************************************************************************

//
//! DMA Transfer Ending Destination Address Bits Mark
//
#define DMA_DAR_DMA_ENDDAR_M    0xFFFFFFFF

//
//! DMA Transfer Ending Destination Address Bits Shift
//
#define DMA_DAR_DMA_ENDDAR_S    0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_NEXT DMA Scatter-Gather Descriptor Table Offset Register(DMA_NEXT)
//! \brief Defines for the bit fields in the DMA_NEXT register.
//! @{
//
//*****************************************************************************

//
//! DMA Next Description Table Offset Address Bits Mark
//
#define DMA_NEXT_NTAAR_OFFSET_M 0x0000FFFC

//
//! DMA Next Description Table Offset Address Bits Shift
//
#define DMA_NEXT_NTAAR_OFFSET_S 2

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_SCATBA DMA Scatter-Gather Descriptor Table Base Address Register(DMA_SCATBA)
//! \brief Defines for the bit fields in the DMA_SCATBA register.
//! @{
//
//*****************************************************************************

//
//! DMA Scatter-Gather Descriptor Table Base Address Bits Mask
//
#define DMA_SCATBA_ETADDR_M     0xFFFF0000

//
//! DMA Scatter-Gather Descriptor Table Base Address Bits shift
//
#define DMA_SCATBA_ETADDR_S     16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_TOC0 DMA Time-out Period Counter Register(DMA_TOC0)
//! \brief Defines for the bit fields in the DMA_TOC0 register.
//! @{
//
//*****************************************************************************

//
//! Time-out Period Counter for Channel 0 Mask
//
#define DMA_TOC0_TmOut0_M       0x0000FFFF

//
//! Time-out Period Counter for Channel 0 Shift
//
#define DMA_TOC0_TmOut0_S       0

//
//! Time-out Period Counter for Channel 1 Mask
//
#define DMA_TOC0_TmOut1_M       0xFFFF0000

//
//! Time-out Period Counter for Channel 1 Shift
//
#define DMA_TOC0_TmOut1_S       16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_TOC1 DMA Time-out Period Counter Register(DMA_TOC1)
//! \brief Defines for the bit fields in the DMA_TOC1 register.
//! @{
//
//*****************************************************************************

//
//! Time-out Period Counter for Channel 2 Mask
//
#define DMA_TOC1_TmOut2_M       0x0000FFFF

//
//! Time-out Period Counter for Channel 2 Shift
//
#define DMA_TOC1_TmOut2_S       0

//
//! Time-out Period Counter for Channel 3 Mask
//
#define DMA_TOC1_TmOut3_M       0xFFFF0000

//
//! Time-out Period Counter for Channel 3 Shift
//
#define DMA_TOC1_TmOut3_S       16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_TOC2 DMA Time-out Period Counter Register(DMA_TOC2)
//! \brief Defines for the bit fields in the DMA_TOC2 register.
//! @{
//
//*****************************************************************************

//
//! Time-out Period Counter for Channel 4 Mask
//
#define DMA_TOC2_TmOut4_M       0x0000FFFF

//
//! Time-out Period Counter for Channel 4 Shift
//
#define DMA_TOC2_TmOut4_S       0

//
//! Time-out Period Counter for Channel 5 Mask
//
#define DMA_TOC2_TmOut5_M       0xFFFF0000

//
//! Time-out Period Counter for Channel 5 Shift
//
#define DMA_TOC2_TmOut5_S       16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_TOC3 DMA Time-out Period Counter Register(DMA_TOC3)
//! \brief Defines for the bit fields in the DMA_TOC3 register.
//! @{
//
//*****************************************************************************

//
//! Time-out Period Counter for Channel 6 Mask
//
#define DMA_TOC3_TmOut6_M       0x0000FFFF

//
//! Time-out Period Counter for Channel 6 Shift
//
#define DMA_TOC3_TmOut6_S       0

//
//! Time-out Period Counter for Channel 7 Mask
//
#define DMA_TOC3_TmOut7_M       0xFFFF0000

//
//! Time-out Period Counter for Channel 7 Shift
//
#define DMA_TOC3_TmOut7_S       16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_TOC4 DMA Time-out Period Counter Register(DMA_TOC4)
//! \brief Defines for the bit fields in the DMA_TOC4 register.
//! @{
//
//*****************************************************************************

//
//! Time-out Period Counter for Channel 8 Mask
//
#define DMA_TOC4_TmOut8_M       0x0000FFFF

//
//! Time-out Period Counter for Channel 8 Shift
//
#define DMA_TOC4_TmOut8_S       0

//
//! Time-out Period Counter for Channel 9 Mask
//
#define DMA_TOC4_TmOut9_M       0xFFFF0000

//
//! Time-out Period Counter for Channel 9 Shift
//
#define DMA_TOC4_TmOut9_S       16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_TOC5 DMA Time-out Period Counter Register(DMA_TOC5)
//! \brief Defines for the bit fields in the DMA_TOC5 register.
//! @{
//
//*****************************************************************************

//
//! Time-out Period Counter for Channel 10 Mask
//
#define DMA_TOC5_TmOut10_M      0x0000FFFF

//
//! Time-out Period Counter for Channel 10 Shift
//
#define DMA_TOC5_TmOut10_S      0

//
//! Time-out Period Counter for Channel 11 Mask
//
#define DMA_TOC5_TmOut11_M      0xFFFF0000

//
//! Time-out Period Counter for Channel 11 Shift
//
#define DMA_TOC5_TmOut11_S      16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_TOC6 DMA Time-out Period Counter Register(DMA_TOC6)
//! \brief Defines for the bit fields in the DMA_TOC6 register.
//! @{
//
//*****************************************************************************

//
//! Time-out Period Counter for Channel 12 Mask
//
#define DMA_TOC6_TmOut12_M      0x0000FFFF

//
//! Time-out Period Counter for Channel 12 Shift
//
#define DMA_TOC6_TmOut12_S      0

//
//! Time-out Period Counter for Channel 13 Mask
//
#define DMA_TOC6_TmOut13_M      0xFFFF0000

//
//! Time-out Period Counter for Channel 13 Shift
//
#define DMA_TOC6_TmOut13_S      16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_TOC7 DMA Time-out Period Counter Register(DMA_TOC7)
//! \brief Defines for the bit fields in the DMA_TOC7 register.
//! @{
//
//*****************************************************************************

//
//! Time-out Period Counter for Channel 14 Mask
//
#define DMA_TOC7_TmOut14_M      0x0000FFFF

//
//! Time-out Period Counter for Channel 14 Shift
//
#define DMA_TOC7_TmOut14_S      0

//
//! Time-out Period Counter for Channel 15 Mask
//
#define DMA_TOC7_TmOut15_M      0xFFFF0000

//
//! Time-out Period Counter for Channel 15 Shift
//
#define DMA_TOC7_TmOut15_S      16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_SMSEL0 Source Module Select Register Register(DMA_SMSEL0)
//! \brief Defines for the bit fields in the DMA_SMSEL0 register.
//! @{
//
//*****************************************************************************

//
//! Channel 0 Selection Mask
//
#define DMA_SMSEL0_CH0_SEL_M    0x0000001F

//
//! Channel 0 Selection Shift
//
#define DMA_SMSEL0_CH0_SEL_S    0

//
//! Channel 1 Selection Mask
//
#define DMA_SMSEL0_CH1_SEL_M    0x00001F00

//
//! Channel 1 Selection Shift
//
#define DMA_SMSEL0_CH1_SEL_S    8

//
//! Channel 2 Selection Mask
//
#define DMA_SMSEL0_CH2_SEL_M    0x001F0000

//
//! Channel 2 Selection Shift
//
#define DMA_SMSEL0_CH2_SEL_S    16

//
//! Channel 3 Selection Mask
//
#define DMA_SMSEL0_CH3_SEL_M    0x1F000000

//
//! Channel 3 Selection Shift
//
#define DMA_SMSEL0_CH3_SEL_S    24

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_SMSEL1 Source Module Select Register Register(DMA_SMSEL1)
//! \brief Defines for the bit fields in the DMA_SMSEL1 register.
//! @{
//
//*****************************************************************************

//
//! Channel 4 Selection Mask
//
#define DMA_SMSEL1_CH4_SEL_M    0x0000001F

//
//! Channel 4 Selection Shift
//
#define DMA_SMSEL1_CH4_SEL_S    0

//
//! Channel 5 Selection Mask
//
#define DMA_SMSEL1_CH5_SEL_M    0x00001F00

//
//! Channel 5 Selection Shift
//
#define DMA_SMSEL1_CH5_SEL_S    8

//
//! Channel 6 Selection Mask
//
#define DMA_SMSEL1_CH6_SEL_M    0x001F0000

//
//! Channel 6 Selection Shift
//
#define DMA_SMSEL1_CH6_SEL_S    16

//
//! Channel 7 Selection Mask
//
#define DMA_SMSEL1_CH7_SEL_M    0x1F000000

//
//! Channel 7 Selection Shift
//
#define DMA_SMSEL1_CH7_SEL_S    24

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_SMSEL2 Source Module Select Register Register(DMA_SMSEL2)
//! \brief Defines for the bit fields in the DMA_SMSEL2 register.
//! @{
//
//*****************************************************************************

//
//! Channel 8 Selection Mask
//
#define DMA_SMSEL2_CH8_SEL_M    0x0000001F

//
//! Channel 8 Selection Shift
//
#define DMA_SMSEL2_CH8_SEL_S    0

//
//! Channel 9 Selection Mask
//
#define DMA_SMSEL2_CH9_SEL_M    0x00001F00

//
//! Channel 9 Selection Shift
//
#define DMA_SMSEL2_CH9_SEL_S    8

//
//! Channel 10 Selection Mask
//
#define DMA_SMSEL2_CH10_SEL_M   0x001F0000

//
//! Channel 10 Selection Shift
//
#define DMA_SMSEL2_CH10_SEL_S   16

//
//! Channel 11 Selection Mask
//
#define DMA_SMSEL2_CH11_SEL_M   0x1F000000

//
//! Channel 11 Selection Shift
//
#define DMA_SMSEL2_CH11_SEL_S   24

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Register_DMA_SMSEL3 Source Module Select Register Register(DMA_SMSEL3)
//! \brief Defines for the bit fields in the DMA_SMSEL3 register.
//! @{
//
//*****************************************************************************

//
//! Channel 12 Selection Mask
//
#define DMA_SMSEL3_CH12_SEL_M   0x0000001F

//
//! Channel 12 Selection Shift
//
#define DMA_SMSEL3_CH12_SEL_S   0

//
//! Channel 13 Selection Mask
//
#define DMA_SMSEL3_CH13_SEL_M   0x00001F00

//
//! Channel 13 Selection Shift
//
#define DMA_SMSEL3_CH13_SEL_S   8

//
//! Channel 14 Selection Mask
//
#define DMA_SMSEL3_CH14_SEL_M   0x001F0000

//
//! Channel 14 Selection Shift
//
#define DMA_SMSEL3_CH14_SEL_S   16

//
//! Channel 15 Selection Mask
//
#define DMA_SMSEL3_CH15_SEL_M   0x1F000000

//
//! Channel 15 Selection Shift
//
#define DMA_SMSEL3_CH15_SEL_S   24

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
#endif // __XHW_DMA_H__

