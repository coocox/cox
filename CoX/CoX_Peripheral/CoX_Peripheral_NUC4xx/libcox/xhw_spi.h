//*****************************************************************************
//
//! \file xhw_spi.h
//! \brief Macros used when accessing the SPI hardware.
//! \version V2.2.1.0
//! \date 6/15/2014
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


#ifndef __XHW_SPI_H__
#define __XHW_SPI_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SPI
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_Register  NUC4xx SPI Register
//! \brief Here are the detailed info of SPI registers.  
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
//! \addtogroup NUC4xx_SPI_Register_Offsets SPI Register Offsets(Map)
//! \brief Here is the SPI register offset, users can get the register address
//! through <b>SPI_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! SPI Control and Status Register.
//
#define SPI_CNTRL               0x00000000 

//
//! SPI Divider Register.
//
#define SPI_DIVIDER             0x00000004

//
//! SPI Slave Select Register.
//
#define SPI_SSR                 0x00000008

//
//! DMA Control Register.
//
#define SPI_DMACTL              0x0000000C

//
//! SPI FIFO Control Register.
//
#define SPI_FIFOCTL             0x00000010

//
//! SPI Status Register.
//
#define SPI_STATUS              0x00000014

//
//! SPI Data Transmit Register.
//
#define SPI_TX                  0x00000020

//
//! SPI Data Receive Register.
//
#define SPI_RX                  0x00000030

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_Register_SPI_CNTRL SPI Control Register(SPI_CNTRL)
//! \brief Defines for the bit fields in the SPI_CNTRL register.
//! @{
//
//*****************************************************************************

//
//! Go and Busy Status
//
#define SPI_CNTRL_SPIEN         BIT_32_0

//
//! Receive At Negative Edge
//
#define SPI_CNTRL_RX_NEG        BIT_32_1 

//
//! Transmit At Negative Edge
//
#define SPI_CNTRL_TX_NEG        BIT_32_2

//
//! Clock Polarity
//
#define SPI_CNTRL_CLKP          BIT_32_3

//
//! Suspend Interval (Master Only)
//
#define SPI_CNTRL_SP_CYCLE_M    0x000000F0
#define SPI_CNTRL_SP_CYCLE_S    4

//
//! Transmit Bit Length
//
#define SPI_CNTRL_TX_BIT_LEN_M  0x00000F00

//
//! Numbers of Transmit/Receive Word
//
#define SPI_CNTRL_TX_BIT_LEN_S  8

//
//! LSB First
//
#define SPI_CNTRL_LSB           BIT_32_13

//
//! 2-bit Mode Enable Control
//
#define SPI_CNTRL_TWOB          BIT_32_16

//
//! Interrupt Enable
//
#define SPI_CNTRL_IE            BIT_32_17

//
//! Slave Mode Indication
//
#define SPI_CNTRL_SLVSEL        BIT_32_18 

//
//! Reorder Mode Select
//
#define SPI_CNTRL_REORDER       BIT_32_19

//
//! Quad or Dual I/O Mode Direction Control
//
#define SPI_CNTRL_QD_IO_DIR     BIT_32_20

//
//! Dual I/O Mode Enable Control
//
#define SPI_CNTRL_QUAL_IO_EN    BIT_32_21

//
//! Quad I/O Mode Enable Control
//
#define SPI_CNTRL_QUAD_IO_EN    BIT_32_22

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_Register_SPI_DIVIDER SPI DIVIDER Register(SPI_DIVIDER)
//! \brief Defines for the bit fields in the SPI_DIVIDER register.
//! @{
//
//*****************************************************************************

//
//! Clock Divider Register (master only)
//
#define SPI_DIVIDER_DIVIDER_M   0x000000FF
#define SPI_DIVIDER_DIVIDER_S   0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_Register_SPI_SSR SPI SSR Register(SPI_SSR)
//! \brief efines for the bit fields in the SPI_SSR register.
//! @{
//
//*****************************************************************************

//
//! Slave Select Register (Master only)
//
#define SPI_SSR_SSR_M           0x00000003  
#define SPI_SSR_SSR_S           0

//
//! Slave Select Active Level
//
#define SPI_SSR_SS_LVL          BIT_32_2

//
//! Automatic Slave Select (Master only)
//
#define SPI_SSR_AUTOSS          BIT_32_3

//
//! Slave 3-Wire Mode Enable Control
//
#define SPI_SSR_SLV3WIRE        BIT_32_4

//
//! Slave Mode Time-out Interrupt Enable Control
//
#define SPI_SSR_SLVTO_INTEN     BIT_32_5

//
//! Slave Mode Time-out FIFO Clear
//
#define SPI_SSR_SLVTO_FFCLR     BIT_32_6

//
//! Slave Mode Error 0 Interrupt Enable Control
//
#define SPI_SSR_SLVER0_INTEN    BIT_32_8

//
//! Slave Mode Error 1 Interrupt Enable Control
//
#define SPI_SSR_SLVER1_INTEN    BIT_32_9

//
//! Slave Select Active Interrupt Enable Control
//
#define SPI_SSR_SSACT_INTEN     BIT_32_12

//
//! Slave Select Inactive Interrupt Enable Control 
//
#define SPI_SSR_SSINA_INTEN     BIT_32_13

//
//! Slave Mode Time-out Period
//
#define SPI_SSR_SLVTOPRD_M       0xFFFF0000
#define SPI_SSR_SLVTOPRD_S       16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_Register_SPI_DMACTL SPI DMACTL Register(SPI_DMACTL)
//! \brief Defines for the bit fields in the SPI_DMACTL register.
//! @{
//
//*****************************************************************************

//
//! PDMA Reset
//
#define SPI_DMACTL_PDMA_RST     BIT_32_2

//
//! Receive PDMA Enable Control
//
#define SPI_DMACTL_RX_EN        BIT_32_1

//
//! Transmit DMA Enable Control
//
#define SPI_DMACTL_TX_EN        BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_Register_SPI_FIFOCTL SPI FIFOCTL Register(SPI_FIFOCTL)
//! \brief Defines for the bit fields in the SPI_FIFOCTL register.
//! @{
//
//*****************************************************************************

//
//! Clear Rx FIFO
//
#define SPI_FIFOCTL_RX_CLR      BIT_32_0

//
//! Clear Tx FIFO
//
#define SPI_FIFOCTL_TX_CLR      BIT_32_1

//
//! Receive Threshold Interrupt Enable
//
#define SPI_FIFOCTL_RX_INTEN    BIT_32_2

//
//! Transmit Threshold Interrupt Enable
//
#define SPI_FIFOCTL_TX_INTEN    BIT_32_3

//
//! Slave Receive Time-out Interrupt Enable Control (Slave Only)
//
#define SPI_FIFOCTL_RXTO_INTEN  BIT_32_4

//
//! Receive FIFO Overrun Interrupt Enable
//
#define SPI_FIFOCTL_RXOV_INTEN  BIT_32_5

//
//! Transmit Under-run Data Out (Slave Only)
//
#define SPI_FIFOCTL_TXUDR_DO    BIT_32_6

//
//! Slave Transmit Under Run Interrupt Enable Control (Slave Only)
//
#define SPI_FIFOCTL_TXUDR_INTEN BIT_32_7

//
//! Receive FIFO Threshold
//
#define SPI_FIFOCTL_RX_THRESHOLD_M BIT_MASK(32,26,24)
#define SPI_FIFOCTL_RX_THRESHOLD_S 24

//
//! Receive FIFO Threshold
//
#define SPI_FIFOCTL_TX_THRESHOLD_M BIT_MASK(32,30,28)
#define SPI_FIFOCTL_TX_THRESHOLD_S 28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_Register_STATUS SPI Status Register (SPI_STATUS)
//! @{
//
//*****************************************************************************

//
//! Busy Status (Read Only)
//
#define SPI_STATUS_BUSY         BIT_32_0

//
//! Unit Transfer Interrupt Status
//
#define SPI_STATUS_UNIT_INTSTS  BIT_32_1

//
//! Slave Select Active Interrupt Status
//
#define SPI_STATUS_SSACT_INTSTS BIT_32_2

//
//! Slave Select Inactive Interrupt Status
//
#define SPI_STATUS_SSINA_INTSTS BIT_32_3

//
//! Slave Select Line Bus Status (Read Only)
//
#define SPI_STATUS_SS_LINE      BIT_32_4

//
//! Slave Time-out Interrupt Status
//
#define SPI_STATUS_SLVTO_INTSTS BIT_32_5

//
//! Slave Mode Error 0 Interrupt Status
//
#define SPI_STATUS_SLVER0_INTSTS BIT_32_6
//
//! Slave Mode Error 1 Interrupt Status
//
#define SPI_STATUS_SLVER1_INTSTS BIT_32_7
//
//! Receive FIFO Buffer Empty Indicator (Read Only)
//
#define SPI_STATUS_RX_EMPTY     BIT_32_8

//
//! Receive FIFO Buffer Empty Indicator (Read Only)
//
#define SPI_STATUS_RX_FULL      BIT_32_9

//
//! Receive FIFO Threshold Interrupt Status (Read Only)
//
#define SPI_STATUS_RXTH_INTSTS  BIT_32_10

//
//! Receive FIFO Overrun Status
//
#define SPI_STATUS_RXOVR_INTSTS BIT_32_11

//
//! Receive Time-out Interrupt Status
//
#define SPI_STATUS_RXTO_INTSTS  BIT_32_12

//
//! SPI Enable Bit Status (Read Only)
//
#define SPI_STATUS_SPIEN_STS    BIT_32_15

//
//! Transmit FIFO Buffer Empty Indicator (Read Only)
//
#define SPI_STATUS_TX_EMPTY     BIT_32_16

//
//! Transmit FIFO Buffer Full Indicator (Read Only)
//
#define SPI_STATUS_TX_FULL      BIT_32_17

//
//! Transmit FIFO Threshold Interrupt Status (Read Only)
//
#define SPI_STATUS_TXTH_INTSTS  BIT_32_18

//
//! Slave Transmit FIFO Under-Run Interrupt Status
//
#define SPI_STATUS_TXUDR_INTSTS BIT_32_19

//
//! FIFO CLR Status (Read Only)
//
#define SPI_STATUS_FFCLR_STS    BIT_32_23

//
//! Receive FIFO Data Count (Read Only)
//
#define SPI_STATUS_RX_FIFO_COUNT_M BIT_MASK(32,27,24)
#define SPI_STATUS_RX_FIFO_COUNT_S 24

//
//! Transmit FIFO Data Count (Read Only)
//
#define SPI_STATUS_TX_FIFO_COUNT_M BIT_MASK(32,31,28)
#define SPI_STATUS_TX_FIFO_COUNT_S 28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_Register_SPI_RX SPI RX Register(SPI_RX)
//! \brief Defines for the bit fields in the SPI_RX register.
//! @{
//
//*****************************************************************************

//
//! Data Receive Register
//
#define SPI_RX_RX_M             0xFFFFFFFF
#define SPI_RX_RX_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_Register_SPI_TX SPI TX Register(SPI_TX)
//! \brief Defines for the bit fields in the SPI_TX register.
//! @{
//
//*****************************************************************************

//
//£¡Data Transmit Register
// 
#define SPI_TX_TX_M             0xFFFFFFFF
#define SPI_TX_TX_S             0

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
#endif // __XHW_SPI_H__


