//*****************************************************************************
//
//! \file xhw_spi.h
//! \brief Macros used when accessing the SPI hardware.
//! \version V2.2.1.0
//! \date 01/05/2012
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
//! \addtogroup STM32F1xx_SPI_Register  STM32F1xx SPI Register
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
//! \addtogroup STM32F1xx_SPI_Register_Offsets SPI Register Offsets(Map)
//! \brief Here is the SPI register offset, users can get the register address
//! through <b>SPI_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! SPI control register 1 (SPI_CR1) (not used in I2S mode).
//
#define SPI_CR1                 0x00000000 

//
//! SPI control register 2 (SPI_CR2).
//
#define SPI_CR2                 0x00000004

//
//! SPI status register (SPI_SR).
//
#define SPI_SR                  0x00000008

//
//! SPI data register (SPI_DR).
//
#define SPI_DR                  0x0000000C

//
//! SPI CRC polynomial register (SPI_CRCPR) (not used in I2S mode).
//
#define SPI_CRCPR               0x00000010

//
//! SPI RX CRC register (SPI_RXCRCR) (not used in I2S mode).
//
#define SPI_RXCRCR              0x00000014

//
//! SPI TX CRC register (SPI_TXCRCR) (not used in I2S mode).
//
#define SPI_TXCRCR              0x00000018

//
//! SPI_I2S configuration register (SPI_I2SCFGR).
//
#define SPI_I2SCFGR             0x0000001C

//
//! SPI_I2S prescaler register (SPI_I2SPR).
//
#define SPI_I2SPR               0x00000020

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SPI_Register_SPI_CR1 SPI Control Register(SPI_CR1) 
//! \brief Defines for the bit fields in the SPI_CR1 register.
//! @{
//
//*****************************************************************************

//
//! Bidirectional data mode enable
//
#define SPI_CR1_BIDIMODE        0x00008000

//
//! Output enable in bidirectional mode
//
#define SPI_CR1_BIDIOE          0x00004000

//
//! Hardware CRC calculation enable
//
#define SPI_CR1_CRCEN           0x00002000

//
//! CRC transfer next
//
#define SPI_CR1_CRCNEXT         0x00001000

//
//! Data frame format
//
#define SPI_CR1_DFF             0x00000800

//
//! Receive only
//
#define SPI_CR1_RXONLY          0x00000400

//
//! Software slave management
//
#define SPI_CR1_SSM             0x00000200

//
//! Internal slave select
//
#define SPI_CR1_SSI             0x00000100

//
//! Frame format
//
#define SPI_CR1_LSBFIRST        0x00000080

//
//! SPI enable
//
#define SPI_CR1_SPE             0x00000040

//
//! Baud rate control mask
//
#define SPI_CR1_BR_M            0x00000038

//
//! Baud rate control shift
//
#define SPI_CR1_BR_S            3

//
//! Master selection
//
#define SPI_CR1_MSTR            0x00000004

//
//! Clock polarity
//
#define SPI_CR1_CPOL            0x00000002

//
//! Clock phase
//
#define SPI_CR1_CPHA            0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SPI_Register_SPI_CR2 SPI Control Register(SPI_CR2) 
//! \brief Defines for the bit fields in the SPI_CR2 register.
//! @{
//
//*****************************************************************************

//
//! Tx buffer empty interrupt enable
//
#define SPI_CR2_TXEIE           0x00000080

//
//! RX buffer not empty interrupt enable
//
#define SPI_CR2_RXNEIE          0x00000040

//
//! Error interrupt enable
//
#define SPI_CR2_ERRIE           0x00000020

//
//! SS output enable
//
#define SPI_CR2_SSOE            0x00000004

//
//! Tx buffer DMA enable
//
#define SPI_CR2_TXDMAEN         0x00000002

//
//! Rx buffer DMA enable
//
#define SPI_CR2_RXDMAEN         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SPI_Register_SPI_SR SPI status Register(SPI_SR) 
//! \brief Defines for the bit fields in the SPI_SR register.
//! @{
//
//*****************************************************************************

//
//! Busy flag
//
#define SPI_SR_BSY              0x00000080

//
//! Overrun flag
//
#define SPI_SR_OVR              0x00000040

//
//! Mode fault
//
#define SPI_SR_MODF             0x00000020

//
//! CRC error flag
//
#define SPI_SR_CRCERR           0x00000010

//
//! Underrun flag
//
#define SPI_SR_UDR              0x00000008

//
//! Underrun flag
//
#define SPI_SR_CHSIDE           0x00000004

//
//! Underrun flag
//
#define SPI_SR_TXE              0x00000002

//
//! Underrun flag
//
#define SPI_SR_RXNE             0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SPI_Register_SPI_DR SPI data Register(SPI_DR) 
//! \brief Defines for the bit fields in the SPI_DR register.
//! @{
//
//*****************************************************************************

//
//! Data register mask
//
#define SPI_DR_DR_M             0x0000FFFF

//
//! Data register shift
//
#define SPI_DR_DR_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SPI_Register_SPI_CRCPR SPI CRC polynomial register  
//! \brief Defines for the bit fields in the SPI_CRCPR register.
//! @{
//
//*****************************************************************************

//
//! CRC polynomial register mask
//
#define SPI_CRCPR_CRCPOLY_M     0x0000FFFF

//
//! CRC polynomial register shift
//
#define SPI_CRCPR_CRCPOLY_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SPI_Register_SPI_RXCRCR SPI SPI RX CRC register   
//! \brief Defines for the bit fields in the SPI_RXCRCR register.
//! @{
//
//*****************************************************************************

//
//! Rx CRC register mask
//
#define SPI_RXCRCR_RXCRC_M      0x0000FFFF

//
//! Rx CRC register shift
//
#define SPI_RXCRCR_RXCRC_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SPI_Register_SPI_TXCRCR SPI SPI TX CRC register   
//! \brief Defines for the bit fields in the SPI_TXCRCR register.
//! @{
//
//*****************************************************************************

//
//! Tx CRC register mask
//
#define SPI_TXCRCR_TXCRC_M      0x0000FFFF

//
//! Tx CRC register shift
//
#define SPI_TXCRCR_TXCRC_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SPI_Register_SPI_I2SCFGR SPI_I2S configuration register   
//! \brief Defines for the bit fields in the SPI_I2SCFGR register.
//! @{
//
//*****************************************************************************

//
//! I2S mode selection
//
#define SPI_I2SCFGR_I2SMOD      0x00000800

//
//! I2S Enable
//
#define SPI_I2SCFGR_I2SE        0x00000400

//
//! I2S configuration mode mask
//
#define SPI_I2SCFGR_I2SCFG_M    0x00000300

//
//! I2S configuration mode shift
//
#define SPI_I2SCFGR_I2SCFG_S    8

//
//! PCM frame synchronization
//
#define SPI_I2SCFGR_PCMSYNC     0x00000080

//
//! I2S standard selection mask
//
#define SPI_I2SCFGR_I2SSTD_M    0x00000030

//
//! I2S standard selection shift
//
#define SPI_I2SCFGR_I2SSTD_S    4

//
//! Steady state clock polarity
//
#define SPI_I2SCFGR_CKPOL       0x00000008

//
//! Data length to be transferred mask
//
#define SPI_I2SCFGR_DATLEN_M    0x00000006

//
//! Data length to be transferred shift
//
#define SPI_I2SCFGR_DATLEN_S    1

//
//! Channel length (number of bits per audio channel)
//
#define SPI_I2SCFGR_CHLEN       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SPI_Register_SPI_I2SPR SPI_I2S prescaler register  
//! \brief Defines for the bit fields in the SPI_I2SPR register.
//! @{
//
//*****************************************************************************

//
//! Master clock output enable
//
#define SPI_I2SPR_MCKOE         0x00000200

//
//! Odd factor for the prescaler
//
#define SPI_I2SPR_ODD           0x00000100

//
//! I2S configuration mode mask
//
#define SPI_I2SPR_I2SDIV_M      0x000000FF

//
//! I2S configuration mode shift
//
#define SPI_I2SPR_I2SDIV_S      0

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



