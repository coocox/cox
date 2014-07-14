//*****************************************************************************
//
//! \file xhw_spi.h
//! \brief Macros used when accessing the SPI hardware.
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
//! \addtogroup AU9110_SPI_Register  AU9110 SPI Register
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
//! \addtogroup AU9110_SPI_Register_Offsets SPI Register Offsets(Map)
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
//! SPI Data Receive Register 0.
//
#define SPI_RX0                 0x00000010

//
//! SPI Data Receive Register 1.
//
#define SPI_RX1                 0x00000014 

//
//! SSPI Data Transmit Register 0.
//
#define SPI_TX0                 0x00000020

//
//! SSPI Data Transmit Register 1.
//
#define SPI_TX1                 0x00000024

//
//! SPI Variable Clock Pattern Register.
//
#define SPI_VARCLK              0x00000034 

//
//! DMA Control Register.
//
#define SPI_DMA                 0x00000038 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SPI_Register_SPI_CNTRL SPI Control Register(SPI_CNTRL) 
//! \brief Defines for the bit fields in the SPI_CNTRL register.
//! @{
//
//*****************************************************************************

//
//! Go and Busy Status
//
#define SPI_CNTRL_GO_BUSY       0x00000001

//
//! Receive At Negative Edge
//
#define SPI_CNTRL_RX_NEG        0x00000002 

//
//! Transmit At Negative Edge
//
#define SPI_CNTRL_TX_NEG        0x00000004

//
//! Transmit Bit Length
//
#define SPI_CNTRL_TX_BIT_LEN_M  0x000000F8

//
//! Numbers of Transmit/Receive Word
//
#define SPI_CNTRL_TX_BIT_LEN_S  3

//
//!
//
#define SPI_CNTRL_TX_NUM_M      0x00000300 

//
//!
//
#define SPI_CNTRL_TX_NUM_1      0x00000000

//
//!
//
#define SPI_CNTRL_TX_NUM_2      0x00000100

//
//!
//
#define SPI_CNTRL_TX_NUM_S      8

//
//! LSB First
//
#define SPI_CNTRL_LSB           0x00000400

//
//! Clock Polarity
//
#define SPI_CNTRL_CLKP          0x00000800

//
//! Suspend Interval (Master Only)
//
#define SPI_CNTRL_SP_CYCLE_M    0x0000F000

//
//!
//
#define SPI_CNTRL_SP_CYCLE_S    12

//
//! Interrupt Flag
//
#define SPI_CNTRL_IF            0x00010000

//
//! Interrupt Enable
//
#define SPI_CNTRL_IE            0x00020000

//
//! Slave Mode Indication
//
#define SPI_CNTRL_SLAVE         0x00040000 

//
//! Insert Sleep interval between Bytes
//
#define SPI_CNTRL_BYTE_SLEEP    0x00080000

//
//! Byte Endian Reorder Function
//
#define SPI_CNTRL_BYTE_ENDIAN   0x00100000

//
//! Enable FIFO Mode
//
#define SPI_CNTRL_FIFO          0x00200000

//
//! Two Bits Transfer Mode Active
//
#define SPI_CNTRL_TWOB          0x00400000 

//
//! Variable Clock Enable (Master Only)
//
#define SPI_CNTRL_VARCLK_EN     0x00800000 

//
//! Received FIFO_EMPTY STATUS (read only)
//
#define SPI_CNTRL_RX_EMPTY      0x01000000 

//
//! Received FIFO_FULL STATUS (read only)
//
#define SPI_CNTRL_RX_FULL       0x02000000 

//
//! Transmitted FIFO_EMPTY STATUS (read only)
//
#define SPI_CNTRL_TX_EMPTY      0x04000000 

//
//! Transmitted FIFO_FULL STATUS (read only)
//
#define SPI_CNTRL_TX_FULL       0x08000000

//
//! Enable DMA Automatic SS function
//
#define SPI_CNTRL_DMA_ASS_BURST 0x10000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SPI_Register_SPI_DIVIDER SPI DIVIDER Register(SPI_DIVIDER)
//! \brief Defines for the bit fields in the SPI_DIVIDER register.
//! @{
//
//*****************************************************************************

//
//! Clock Divider Register (master only)
//
#define SPI_DIVIDER_DIVIDER_M   0x0000FFFF  
#define SPI_DIVIDER_DIVIDER_S   0

//
//! Clock Divider Register (master only)
//
#define SPI_DIVIDER_DIVIDER2_M  0xFFFF0000  
#define SPI_DIVIDER_DIVIDER2_S  16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SPI_Register_SPI_SSR SPI SSR Register(SPI_SSR)
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
#define SPI_SSR_SS_LVL          0x00000004

//
//! Automatic Slave Select (Master only)
//
#define SPI_SSR_AUTOSS          0x00000008

//
//! Slave Select Level Trigger (Slave only)
//
#define SPI_SS_LTRIG            0x00000010

//
//! Level Trigger Flag
//
#define SPI_LTRIG_FLAG          0x00000020

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SPI_Register_SPI_RX0 SPI RX0 Register(SPI_RX0)
//! \brief Defines for the bit fields in the SPI_RX0 register.
//! @{
//
//*****************************************************************************

//
//! Data Receive Register
//
#define SPI_RX0_RX_M            0xFFFFFFFF
#define SPI_RX0_RX_S            0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SPI_Register_SPI_RX1 SPI RX1 Register(SPI_RX1)
//! \brief Defines for the bit fields in the SPI_RX1 register.
//! @{
//
//*****************************************************************************

//
//! Data Receive Register
//
#define SPI_RX1_RX_M            0xFFFFFFFF
#define SPI_RX1_RX_S            0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SPI_Register_SPI_TX0 SPI TX0 Register(SPI_TX0)
//! \brief Defines for the bit fields in the SPI_TX0 register.
//! @{
//
//*****************************************************************************

//
//£¡Data Transmit Register
// 
#define SPI_TX0_RX_M            0xFFFFFFFF
#define SPI_TX0_RX_S            0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SPI_Register_SPI_TX1 SPI TX1 Register(SPI_TX1)
//! \brief Defines for the bit fields in the SPI_TX1 register.
//! @{
//
//*****************************************************************************

//
//! Data Transmit Register
//
#define SPI_TX1_RX_M            0xFFFFFFFF
#define SPI_TX1_RX_S            0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SPI_Register_SPI_VARCLK SPI VARCLK Register(SPI_VARCLK)
//! \brief Defines for the bit fields in the SPI_VARCLK register.
//! @{
//
//*****************************************************************************

//
//! Variable Clock Pattern
//
#define SPI_VARCLK_M            0xFFFFFFFF
#define SPI_VARCLK_S            0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_SPI_Register_SPI_DMA SPI DMA Register(SPI_DMA) 
//! \brief Defines for the bit fields in the SPI_DMA register.
//! @{
//
//*****************************************************************************

//
//! Receive DMA Start
//
#define SPI_DMA_RX_DMA_GO       0x00000001

//
//! Transmit DMA Start
//
#define SPI_DMA_TX_DMA_GO       0x00000002

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


