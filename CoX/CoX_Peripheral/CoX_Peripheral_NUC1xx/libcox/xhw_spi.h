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
//! \addtogroup NUC1xx_SPI_Register  NUC1xx SPI Register
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
//! \addtogroup NUC1xx_SPI_Register_Offsets SPI Register Offsets(Map)
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
#define SPI_DMACTL              0x00000038 

//
//! SPI Control and Status Register 2.
//
#define SPI_CNTRL2              0x0000003C

//
//! SPI FIFO Control Register.
//
#define SPI_FIFOCTL             0x00000040

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SPI_Register_SPI_CNTRL SPI Control Register(SPI_CNTRL) 
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
//! Reorder Mode Select
//
#define SPI_CNTRL_REORDER_M     0x00180000  
//#define SPI_CNTRL_REORDER_M     0x00180000
//#define SPI_CNTRL_REORDER_M     0x00180000
//#define SPI_CNTRL_REORDER_M     0x00180000
//#define SPI_CNTRL_REORDER_M     0x00180000

//
//!
//
#define SPI_CNTRL_REORDER_S     19

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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SPI_Register_SPI_DIVIDER SPI DIVIDER Register(SPI_DIVIDER)
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
//! \addtogroup NUC1xx_SPI_Register_SPI_SSR SPI SSR Register(SPI_SSR)
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
#define SPI_SS_LVL              0x00000004

//
//! Automatic Slave Select (Master only)
//
#define SPI_AUTOSS              0x00000008

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
//! \addtogroup NUC1xx_SPI_Register_SPI_RX0 SPI RX0 Register(SPI_RX0)
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
//! \addtogroup NUC1xx_SPI_Register_SPI_RX1 SPI RX1 Register(SPI_RX1)
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
//! \addtogroup NUC1xx_SPI_Register_SPI_TX0 SPI TX0 Register(SPI_TX0)
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
//! \addtogroup NUC1xx_SPI_Register_SPI_TX1 SPI TX1 Register(SPI_TX1)
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
//! \addtogroup NUC1xx_SPI_Register_SPI_VARCLK SPI VARCLK Register(SPI_VARCLK)
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
//! \addtogroup NUC1xx_SPI_Register_SPI_DMACTL SPI DMACTL Register(SPI_DMACTL) 
//! \brief Defines for the bit fields in the SPI_DMACTL register.
//! @{
//
//*****************************************************************************

//
//! Receive DMA Start
//
#define SPI_DMACTL_RX_DMA_GO    0x00000001

//
//! Transmit DMA Start
//
#define SPI_DMACTL_TX_DMA_GO    0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SPI_Register_SPI_CNTRL2 SPI CNTRL2 Register(SPI_CNTRL2)
//! \brief Defines for the bit fields in the SPI_CNTRL2 register.
//! @{
//
//*****************************************************************************

//
//! SPI clock divider control
//
#define SPI_CNTRL2_DIV_ONE      0x00000001 

//
//! No Slave Select in Slave Mode
//
#define SPI_CNTRL2_NOSLVSEL     0x00000100

//
//! Slave Start Interrupt Enable
//
#define SPI_CNTRL2_SSTA_INTEN   0x00000100

//
//! Slave Start Interrupt Status
//
#define SPI_CNTRL2_SLV_START_INTSTS                                            \
                                0x00000100

//
//! Abort in Slave Mode with No Slave Select
//
#define SPI_CNTRL2_SLV_ABORT    0x00000200

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SPI_Register_SPI_FIFOCTL SPI FIFOCTL Register(SPI_FIFOCTL)
//! \brief Defines for the bit fields in the SPI_FIFOCTL register.
//! @{
//
//*****************************************************************************

//
//! Clear Rx FIFO
//
#define SPI_FIFOCTL_RX_CLR      0x00000001

//
//! Clear Tx FIFO
//
#define SPI_FIFOCTL_TX_CLR      0x00000002

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


