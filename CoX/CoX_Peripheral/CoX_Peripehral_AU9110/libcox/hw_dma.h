//*****************************************************************************
//
//! \file xhw_dma.h
//! \brief Macros and defines used when accessing the DMA hardware.
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
//! \addtogroup NUC1xx_DMA_Register NUC1xx DMA Register
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
//! \addtogroup NUC1xx_DMA_Register_Offset DMA Register Offset(Map) 
//! \brief Here is the DMA register offset, users can get the register address
//! through <b>DMA_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! PDMA Control and Status Register
//
#define PDMA_CSR                0x00000000  

//
//! PDMA Transfer Source Address Register
//
#define PDMA_SAR                0x00000004  

//
//! PDMA Destination Address Register
//
#define PDMA_DAR                0x00000008  

//
//! PDMA Transfer Byte Count Register
//
#define PDMA_BCR                0x0000000C  

//
//! PDMA Internal buffer pointer
//
#define PDMA_POINT              0x00000010  

//
//! PDMA Current Source Address Register
//
#define PDMA_CSAR               0x00000014  

//
//! PDMA Current Destination Address Register
//
#define PDMA_CDAR               0x00000018  

//
//! PDMA Current Transfer Byte Count Register
//
#define PDMA_CBCR               0x0000001C  

//
//! PDMA Interrupt Enable Register
//
#define PDMA_IER                0x00000020  

//
//! PDMA Interrupt Status Register
//
#define PDMA_ISR                0x00000024  

//
//! PDMA Shared Buffer FIFO 0
//
#define PDMA_SBUF0              0x00000080  

//
//! PDMA Global Control Register
//
#define PDMA_GCRCSR             0x50008F00  

//
//! Service Selection Control Register 0
//
#define PDMA_PDSSR0             0x50008F04  

//
//! Service Selection Control Register 1
//
#define PDMA_PDSSR1             0x50008F08  

//
//! PDMA Global Interrupt Register
//
#define PDMA_GCRISR             0x50008F0C  

//
//! Service Selection Control Register 2
//
#define PDMA_PDSSR2             0x50008F10  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_CSR DMA Control Register(PDMA_CSRx)
//! \brief Defines for the bit fields in the PDMA_CSR register.
//! @{
//
//*****************************************************************************

//
//! PDMA Channel Enable
//
#define PDMA_CSR_CEN            0x00000001  

//
//! Software Engine Reset
//
#define PDMA_CSR_RST            0x00000002  

//
//! PDMA Mode Select mask
//
#define PDMA_CSR_MODE_M         0x0000000C  

//
//! PDMA Mode Select Memory-to-Memory
//
#define PDMA_CSR_MODE_MTOM      0x00000000

//
//! PDMA Mode Select Peripheral-to-Memory
//
#define PDMA_CSR_MODE_PTOM      0x00000004

//
//! PDMA Mode Select Memory-to-Peripheral
//
#define PDMA_CSR_MODE_MTOP      0x00000008

//
//! PDMA Mode Select shift
//
#define PDMA_CSR_MODE_S         2

//
//! Transfer Source Address Direction Select mask
//
#define PDMA_CSR_SDA_M          0x00000030 

//
//! Transfer Source Address Direction Select shift
//
#define PDMA_CSR_SDA_S          4

//
//! Transfer Destination Address Direction Select mask
//
#define PDMA_CSR_DAD_M          0x000000C0  

//
//! Transfer Destination Address Direction Select shift
//
#define PDMA_CSR_DAD_S          6

//
//! Peripheral transfer Width Select mask
//
#define PDMA_CSR_TWS_M          0x00180000  

//
//! Peripheral transfer Width Select shift
//
#define PDMA_CSR_TWS_S          19

//
//! Enable PDMA data read or write transfer.
//
#define PDMA_CSR_TEN            0x00800000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_SAR DMA Source Address Register(PDMA_SARx)
//! \brief Defines for the bit fields in the PDMA_SAR register.
//! @{
//
//*****************************************************************************

//
//! PDMA Transfer Source Address.
//
#define PDMA_SAR_M              0xFFFFFFFF  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_DAR DMA Destination Address Register(PDMA_DARx)
//! \brief Defines for the bit fields in the PDMA_DAR register.
//! @{
//
//*****************************************************************************

//
//! PDMA Transfer Destination Address.
//
#define PDMA_DAR_M              0xFFFFFFFF  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_BCR DMA Transfer Byte Count Register(PDMA_BCRx)
//! \brief Defines for the bit fields in the PDMA_BCR register.
//! @{
//
//*****************************************************************************

//
//! PDMA Transfer Byte Count.
//
#define PDMA_BCR_M              0x0000FFFF  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_POINT DMA Internal buffer pointer(PDMA_POINT)
//! \brief Defines for the bit fields in the PDMA_POINT register.
//! @{
//
//*****************************************************************************

//
//! Indicates the internal buffer pointer.
//
#define PDMA_POINT_M            0x00000003  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_CSAR DMA Current Source Address Register(PDMA_CSAR)
//! \brief Defines for the bit fields in the PDMA_CSAR register.
//! @{
//
//*****************************************************************************

//
//! PDMA Current Source Address.
//
#define PDMA_CSAR_M             0xFFFFFFFF  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_CDAR DMA Current Destination Address Register(PDMA_CDAR)
//! \brief Defines for the bit fields in the PDMA_CDAR register.
//! @{
//
//*****************************************************************************

//
//! PDMA Current Destination Address.
//
#define PDMA_CDAR_M             0xFFFFFFFF  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_CBCR DMA Current Transfer Byte Count Register(PDMA_CBCR)
//! \brief Defines for the bit fields in the PDMA_CBCR register.
//! @{
//
//*****************************************************************************

//
//! PDMA Current Byte Count.
//
#define PDMA_CBCR_M             0x0000FFFF  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_IER DMA Interrupt Enable Register(PDMA_IER)
//! \brief Defines for the bit fields in the PDMA_IER register.
//! @{
//
//*****************************************************************************

//
//! Read/Write Target Abort Interrupt Enable.
//
#define PDMA_IER_TABORT         0x00000001  

//
//! PDMA Transfer Done Interrupt Enable.
//
#define PDMA_IER_BLKD           0x00000002  

//
//! Wrap Around Interrupt Enable.
//
#define PDMA_IER_WAR            0x00000004  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_ISR DMA Interrupt Status Register(PDMA_ISR)
//! \brief Defines for the bit fields in the PDMA_ISR register.
//! @{
//
//*****************************************************************************

//
//! Read/Write Target Abort Interrupt Flag.
//
#define PDMA_ISR_TABORT         0x00000001  

//
//! Block Transfer Done Interrupt Flag.
//
#define PDMA_ISR_BLKD           0x00000002  

//
//! Wrap around transfer byte count interrupt flag mask.
//
#define PDMA_ISR_WAR_BCR_M      0x00000F00  

//
//! Wrap around transfer byte count interrupt flag shift.
//
#define PDMA_ISR_WAR_BCR_S      8

//
//! PDMA Transfer is in Progress.
//
#define PDMA_ISR_BUSY           0x00008000  

//
//! Interrupt Pin Status.
//
#define PDMA_ISR_INTR           0x80000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_SBUF0 DMA Shared Buffer FIFO 0(PDMA_SBUF0) 
//! \brief Defines for the bit fields in the PDMA_SBUF0 register.
//! @{
//
//*****************************************************************************

//
//! PDMA Shared Buffer FIFO 0.
//
#define PDMA_SBUF0_M            0xFFFFFFFF  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_GCRCSR PDMA Global Control Register(DMA_GCRCSR)
//! \brief Defines for the bit fields in the PDMA_GCRCSR register.
//! @{
//
//*****************************************************************************

//
//! PDMA Software Reset.
//
#define PDMA_GCRCSR_RST         0x00000001  

//
//! PDMA Channel 0 Clock Enable Control.
//
#define PDMA_GCRCSR_HCLK0_EN    0x00000100  

//
//! PDMA Channel 1 Clock Enable Control.
//
#define PDMA_GCRCSR_HCLK1_EN    0x00000200  

//
//! PDMA Channel 2 Clock Enable Control.
//
#define PDMA_GCRCSR_HCLK2_EN    0x00000400  

//
//! PDMA Channel 3 Clock Enable Control.
//
#define PDMA_GCRCSR_HCLK3_EN    0x00000800  

//
//! PDMA Channel 4 Clock Enable Control.
//
#define PDMA_GCRCSR_HCLK4_EN    0x00001000  

//
//! PDMA Channel 5 Clock Enable Control.
//
#define PDMA_GCRCSR_HCLK5_EN    0x00002000  

//
//! PDMA Channel 6 Clock Enable Control.
//
#define PDMA_GCRCSR_HCLK6_EN    0x00004000  

//
//! PDMA Channel 7 Clock Enable Control.
//
#define PDMA_GCRCSR_HCLK7_EN    0x00008000  

//
//! PDMA Channel 8 Clock Enable Control.
//
#define PDMA_GCRCSR_HCLK8_EN    0x00010000 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_PDSSR0 PDMA Service Selection Control Register 0(DMA_PDSSR0)
//! \brief Defines for the bit fields in the PDMA_PDSSR0 register.
//! @{
//
//*****************************************************************************

//
//! PDMA SPI0 Rx Selection mask.
//
#define PDMA_PDSSR0_SPI0_RX_M   0x0000000F  

//
//! PDMA SPI0 Rx Selection shift.
//
#define PDMA_PDSSR0_SPI0_RX_S   0

//
//! PDMA SPI0 Tx Selection mask.
//
#define PDMA_PDSSR0_SPI0_TX_M   0x000000F0  

//
//! PDMA SPI0 Tx Selection shift.
//
#define PDMA_PDSSR0_SPI0_TX_S   4

//
//! PDMA SPI1 Rx Selection mask.
//
#define PDMA_PDSSR0_SPI1_RX_M   0x00000F00  

//
//! PDMA SPI1 Rx Selection shift.
//
#define PDMA_PDSSR0_SPI1_RX_S   8

//
//! PDMA SPI1 Tx Selection mask.
//
#define PDMA_PDSSR0_SPI1_TX_M   0x0000F000  

//
//! PDMA SPI1 Tx Selection shift.
//
#define PDMA_PDSSR0_SPI1_TX_S   12

//
//! PDMA SPI2 Rx Selection mask.
//
#define PDMA_PDSSR0_SPI2_RX_M   0x000F0000  

//
//! PDMA SPI2 Rx Selection shift.
//
#define PDMA_PDSSR0_SPI2_RX_S   16

//
//! PDMA SPI2 Tx Selection mask.
//
#define PDMA_PDSSR0_SPI2_TX_M   0x00F00000  

//
//! PDMA SPI2 Tx Selection shift.
//
#define PDMA_PDSSR0_SPI2_TX_S   20

//
//! PDMA SPI3 Rx Selection mask.
//
#define PDMA_PDSSR0_SPI3_RX_M   0x0F000000  

//
//! PDMA SPI3 Rx Selection shift.
//
#define PDMA_PDSSR0_SPI3_RX_S   24

//
//! PDMA SPI3 Tx Selection mask.
//
#define PDMA_PDSSR0_SPI3_TX_M   0xF0000000  

//
//! PDMA SPI3 Tx Selection shift.
//
#define PDMA_PDSSR0_SPI3_TX_S   28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_PDSSR1 DMA Service Selection Control Register 1(PDMA_PDSSR1)
//! 
//! \brief Defines for the bit fields in the PDMA_PDSSR1 register.
//! @{
//
//*****************************************************************************

//
//! PDMA UART0 Rx Selection mask.
//
#define PDMA_PDSSR1_UART0_RX_M  0x0000000F  

//
//! PDMA UART0 Rx Selection shift.
//
#define PDMA_PDSSR1_UART0_RX_S  0

//
//! PDMA UART0 Tx Selection mask.
//
#define PDMA_PDSSR1_UART0_TX_M  0x000000F0  

//
//! PDMA UART0 Tx Selection shift.
//
#define PDMA_PDSSR1_UART0_TX_S  4

//
//! PDMA UART1 Rx Selection mask.
//
#define PDMA_PDSSR1_UART1_RX_M  0x00000F00  

//
//! PDMA UART1 Rx Selection shift.
//
#define PDMA_PDSSR1_UART1_RX_S  8

//
//! PDMA UART1 Tx Selection mask.
//
#define PDMA_PDSSR1_UART1_TX_M  0x0000F000  

//
//! PDMA UART1 Tx Selection shift.
//
#define PDMA_PDSSR1_UART1_TX_S  12

//
//! PDMA USB Rx Selection mask.
//
#define PDMA_PDSSR1_USB_RX_M    0x000F0000  

//
//! PDMA USB Rx Selection shift.
//
#define PDMA_PDSSR1_USB_RX_S    16

//
//! PDMA USB Tx Selection mask.
//
#define PDMA_PDSSR1_USB_TX_M    0x00F00000 

//
//! PDMA USB Tx Selection shift.
//
#define PDMA_PDSSR1_USB_TX_S    20

//
//! PDMA ADC Rx Selection mask.
//
#define PDMA_PDSSR1_ADC_RX_M    0x0F000000 

//
//! PDMA ADC Rx Selection shift.
//
#define PDMA_PDSSR1_ADC_RX_S    24

//
//! PDMA ADC Tx Selection mask.
//
#define PDMA_PDSSR1_ADC_TX_M    0x0F000000  

//
//! PDMA ADC Tx Selection shift.
//
#define PDMA_PDSSR1_ADC_TX_S    24

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_PDSSR2 DMA Service Selection Control Register 2(PDMA_PDSSR2)
//! \brief Defines for the bit fields in the PDMA_PDSSR2 register.
//! @{
//
//*****************************************************************************

//
//! PDMA I2S Rx Selection mask.
//
#define PDMA_PDSSR2_I2S_RX_M    0x0000000F  

//
//! PDMA I2S Rx Selection shift.
//
#define PDMA_PDSSR2_I2S_RX_S    0

//
//! PDMA I2S Tx Selection mask.
//
#define PDMA_PDSSR2_I2S_TX_M    0x000000F0  

//
//! PDMA I2S Tx Selection shift.
//
#define PDMA_PDSSR2_I2S_TX_S    4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_DMA_Register_PDMA_GCRISR DMA Global Interrupt Register(DMA_GCRISR)
//! \brief Defines for the bit fields in the PDMA_GCRISR register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Pin Status of Channel 0.
//
#define PDMA_GCRISR_INTR0       0x00000001  

//
//! Interrupt Pin Status of Channel 1.
//
#define PDMA_GCRISR_INTR1       0x00000002  

//
//! Interrupt Pin Status of Channel 2.
//
#define PDMA_GCRISR_INTR2       0x00000004  

//
//! Interrupt Pin Status of Channel 3.
//
#define PDMA_GCRISR_INTR3       0x00000008  

//
//! Interrupt Pin Status of Channel 4.
//
#define PDMA_GCRISR_INTR4       0x00000010  

//
//! Interrupt Pin Status of Channel 5.
//
#define PDMA_GCRISR_INTR5       0x00000020  

//
//! Interrupt Pin Status of Channel 6.
//
#define PDMA_GCRISR_INTR6       0x00000040  

//
//! Interrupt Pin Status of Channel 7.
//
#define PDMA_GCRISR_INTR7       0x00000080  

//
//! Interrupt Pin Status of Channel 8.
//
#define PDMA_GCRISR_INTR8       0x00000100  

//
//! IInterrupt Pin Status.
//
#define PDMA_GCRISR_INTR        0x80000000  

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

