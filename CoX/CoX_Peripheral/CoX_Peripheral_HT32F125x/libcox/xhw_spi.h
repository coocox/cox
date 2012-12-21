//*****************************************************************************
//
//! \file xhw_spi.h
//! \brief Macros used when accessing the SPI hardware.
//! \version V2.1.1.0
//! \date 3/6/2012
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
//! \addtogroup HT32F125x_SPI_Register  HT32F125x SPI Register
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
//! \addtogroup HT32F125x_SPI_Register_Offsets SPI Register Offsets(Map)
//! \brief Here is the SPI register offset, users can get the register address
//! through <b>SPI_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! SPI Control Register0.
//
#define SPI_CNTRL0              0x00000000 

//
//! SPI Control Register1.
//
#define SPI_CNTRL1              0x00000004 

//
//! SPI Interrupt Enable Register.
//
#define SPI_IIER                0x00000008

//
//! SPI Clock Prescaler Register.
//
#define SPI_CPR                 0x0000000C

//
//! SPI Data Register.
//
#define SPI_DR                  0x00000010

//
//! SPI Status Register.
//
#define SPI_SR                  0x00000014 

//
//! SPI FIFO Control Register.
//
#define SPI_FCR                 0x00000018

//
//! SPI FIFO Status Register.
//
#define SPI_FSR                 0x0000002C

//
//! SPI FIFO Time Out Counter Register.
//
#define SPI_FTOCR               0x00000034 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_SPI_Register_SPI_CNTRL0 SPI Control0 Register(SPI_CNTRL0) 
//! \brief Defines for the bit fields in the SPI_CNTRL0 register.
//! @{
//
//*****************************************************************************

//
//! SPI Enable
//
#define SPI_CNTRL0_EN           0x00000001

//
//! Slave Select Output Enable
//
#define SPI_CNTRL0_SELOEN       0x00000008 

//
//! Software Slave Select Control
//
#define SPI_CNTRL0_SSELC        0x00000010

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_SPI_Register_SPI_CNTRL1 SPI Control1 Register(SPI_CNTRL1) 
//! \brief Defines for the bit fields in the SPI_CNTRL1 register.
//! @{
//
//*****************************************************************************

//
//! Data Frame Length mask
//
#define SPI_CNTRL1_DFL_M        0x0000000F

//
//! Data Frame Length shift
//
#define SPI_CNTRL1_DFL_S        0

//
//! SPI Data Transfer Format mask
//
#define SPI_CNTRL1_FORMAT_M     0x00000700 

//
//! SPI Data Transfer Format 0
//! CPOL 0, CPHA 0
//
#define SPI_CNTRL1_FORMAT_0     0x00000100 

//
//! SPI Data Transfer Format 1
//! CPOL 0, CPHA 1
//
#define SPI_CNTRL1_FORMAT_1     0x00000200 

//
//! SPI Data Transfer Format 2
//! CPOL 1, CPHA 0
//
#define SPI_CNTRL1_FORMAT_2     0x00000600 

//
//! SPI Data Transfer Format 0
//! CPOL 1, CPHA 1
//
#define SPI_CNTRL1_FORMAT_3     0x00000500 

//
//! Slave Select Active Polarity
//
#define SPI_CNTRL1_SELAP        0x00000800

//
//! LSB or MSB Transmitted First
//
#define SPI_CNTRL1_FIRSTBIT     0x00001000

//
//! Slave Select Mode
//
#define SPI_CNTRL1_SELM         0x00002000

//
//! Master or Slave Mode
//
#define SPI_CNTRL1_MODE         0x00004000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_SPI_Register_SPI_IER SPI Interrupt Enable Register(SPI_IER)
//! \brief Defines for the bit fields in the SPI_IER register.
//! @{
//
//*****************************************************************************

//
//! TX Buffer Empty Interrupt Enable
//
#define SPI_IER_TXBEIEN         0x00000001

//
//! TX Register Empty Interrupt Enable
//
#define SPI_IER_TXEIEN          0x00000002

//
//! RX Buffer Not Empty Interrupt Enable
//
#define SPI_IER_RXBNEIEN        0x00000004

//
//! Write Collision Interrupt Enable
//
#define SPI_IER_WCIEN           0x00000008

//
//! Read Overrun Interrupt Enable
//
#define SPI_IER_ROIEN           0x00000010

//
//! Mode Fault Interrupt Enable
//
#define SPI_IER_MFIEN           0x00000020

//
//! Slave Abort Interrupt Enable
//
#define SPI_IER_SAIEN           0x00000040

//
//! Time Out Interrupt Enable
//
#define SPI_IER_TOIEN           0x00000080

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_SPI_Register_SPI_DR SPIreceived or transmitted Data
//! Register(SPI_CPR)
//! \brief efines for the bit fields in the SPI_CPR register.
//! @{
//
//*****************************************************************************

//
//! Data Register mask
//! 
//
#define SPI_DR_DR_M             0x0000FFFF  

//
//! Data Register shift
//
#define SPI_DR_DR_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_SPI_Register_SPI_SR SPI relevant status Register(SPI_RX0)
//! \brief Defines for the bit fields in the SPI_SR register.
//! @{
//
//*****************************************************************************

//
//! Transmit Buffer Empty flag
//
#define SPI_SR_TXBE             0x00000001

//
//! Transmission Register Empty flag
//
#define SPI_SR_TXE              0x00000002

//
//! Receive Buffer Not Empty flag
//
#define SPI_SR_RXBNE            0x00000004

//
//! Write Collision flag
//
#define SPI_SR_WC               0x00000008

//
//! Read Overrun flag
//
#define SPI_SR_RO               0x00000010

//
//! Mode Fault flag
//
#define SPI_SR_MF               0x00000020

//
//! Slave Abort flag
//
#define SPI_SR_SA               0x00000040

//
//! Time Out flag
//
#define SPI_SR_TO               0x00000080

//
//! SPI Busy flag
//
#define SPI_SR_BUSY             0x00000100

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_SPI_Register_SPI_FCR SPI FIFO Control Register(SPI_FCR)
//! \brief Defines for the bit fields in the SPI_FCR register.
//! @{
//
//*****************************************************************************

//
//! TX FIFO Trigger Level Select mask
//
#define SPI_FCR_TXFTLS_M        0x0000000F

//
//! TX FIFO Trigger Level Select shift
//
#define SPI_FCR_TXFTLS_S        0

//
//! RX FIFO Trigger Level Select mask
//
#define SPI_FCR_RXFTLS_M        0x000000F0

//
//! RX FIFO Trigger Level Select shift
//
#define SPI_FCR_RXFTLS_S        4

//
//! TX FIFO Pointer Reset
//
#define SPI_FCR_TFPR            0x00000100

//
//! RX FIFO Pointer Reset
//
#define SPI_FCR_RFPR            0x00000200

//
//! FIFO Enable
//
#define SPI_FCR_FIFOEN          0x00000400       

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_SPI_Register_SPI_FSR SPI SPI FIFO status Register(SPI_SPIFSR)
//! \brief Defines for the bit fields in the SPI_FSR register.
//! @{
//
//*****************************************************************************

//
//£¡TX FIFO Status mask
// 
#define SPI_FSR_TXFS_M          0x0000000F

//
//! TX FIFO Status shift
//
#define SPI_FSR_TXFS_S          0

//
//! RX FIFO Status mask
//
#define SPI_FSR_RXFS_M          0x000000F0

//
//! RX FIFO Status shift
//
#define SPI_FSR_RXFS_S          4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_SPI_Register_SPI_FTOCR SPI FIFO Time Out Counter 
//! Register(SPI_TX1)
//! \brief Defines for the bit fields in the SPI_FTOCR register.
//! @{
//
//*****************************************************************************

//
//! Data Transmit Register
//
#define SPI_FTOCR_TOC_M         0xFFFFFFFF
#define SPI_FTOCR_TOC_S         0

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


