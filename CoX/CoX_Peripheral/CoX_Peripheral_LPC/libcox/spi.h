//*****************************************************************************
//
//! \file      spi.h
//! \brief     Prototypes for the SPI Driver.
//! \version   V3.0.0.0
//! \date      $CURRENTTIME$
//! \author    CooCox
//! \copyright
//!
//! Copyright (c)  2014, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
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
//! THE POSPIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

#ifndef _LPC17XX_SPI_H_
#define _LPC17XX_SPI_H_

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
//! \addtogroup LPC17xx_SPI
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SPI_Ints SPI Interrupts
//! \brief Values show that LPC17xx SPI Interrupts
//! Values that can be passed to xSPIIntEnable, xSPIIntDisable
//! as the ulIntFlags parameter.
//! @{
//
//*****************************************************************************

//
//! All Interrupt Mask
//
#define SPI_INT_EOT             0x00000001
#define SPI_INT_RX              0x00000004
#define SPI_INT_TX              0x00000008
#define SPI_INT_ERROR           0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SPI_Config LPC17xx SPI Configure
//! \brief Values show that LPC17xx SPI Configure
//! Values that can be passed to xSPIConfigSet.
//! @{
//
//*****************************************************************************

//
//! polarity 0,
//! Tx changed at rising edge
//! Rx latched at rising edge
//
#define SPI_FORMAT_MODE_0       0x00000000

//
//! Moto Format, polarity 0, phase 0  M0
//! Tx changed at falling edge
//! Rx latched at rising edge
//
#define SPI_FORMAT_MODE_1       0x00000800

//
//! Moto Format, polarity 0, phase 1  M1
//! Tx changed at rising edge
//! Rx latched at falling edge
//
#define SPI_FORMAT_MODE_2       0x00000400

//
//! polarity 0
//! Tx changed at falling edge
//! Rx latched at falling edge
//
#define SPI_FORMAT_MODE_3       0x00000C00

//
//!  TI frame format
//
#define SPI_TI_FORMAT_MODE      0x00000100

//
//! National MicroWire frame format
//
#define SPI_NMW_FORMAT_MODE     0x00000200

//
//£¡ SPI master
//
#define SPI_MODE_MASTER         0x00000000

//
//! SPI slave
//
#define SPI_MODE_SLAVE          0x00010000

//
//! SPI MSB First
//
#define SPI_MSB_FIRST           0x00000000

//
//! SPI LSB First
//
#define SPI_LSB_FIRST           0x00100000

//
//! data width 4 bit
//
#define SPI_DATA_WIDTH4         0x00000003

//
//! data width 5 bit
//
#define SPI_DATA_WIDTH5         0x00000004

//
//! data width 6 bit
//
#define SPI_DATA_WIDTH6         0x00000005

//
//! data width 7 bit
//
#define SPI_DATA_WIDTH7         0x00000006

//
//! data width 8 bit
//
#define SPI_DATA_WIDTH8         0x00000007

//
//! data width 9 bit
//
#define SPI_DATA_WIDTH9         0x00000008

//
//! data width 10 bit
//
#define SPI_DATA_WIDTH10        0x00000009

//
//! data width 11 bit
//
#define SPI_DATA_WIDTH11        0x0000000A

//
//! data width 12 bit
//
#define SPI_DATA_WIDTH12        0x0000000B

//
//! data width 13 bit
//
#define SPI_DATA_WIDTH13        0x0000000C

//
//! data width 14 bit
//
#define SPI_DATA_WIDTH14        0x0000000D

//
//! data width 15 bit
//
#define SPI_DATA_WIDTH15        0x0000000E

//
//! data width 16 bit
//
#define SPI_DATA_WIDTH16        0x0000000F

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SPI_SlaveSel_Config LPC17xx SPI Slave Select Configure
//! \brief Values that show LPC17xx SPI Slave Select Configure
//! Values that can be passed to SPIAutoSSEnable() SPISSSet()  SPISSClear()
//! SPISSConfig().
//! @{
//
//*****************************************************************************

#define SPI_SS_HARDWARE         0x00000001
#define SPI_SS_SOFTWARE         0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SPI_DMA SPI DMA
//! \brief      Values that show LPC17xx SPI DMA
//!
//! \note For LPC17xx, There is only one SPI module and not support DMA operation.
//!
//! @{
//
//*****************************************************************************

//
//! Enable DMA for transmit
//
#define SPI_DMA_TX              0x00000002

//
//! Enable DMA for receive
//
#define SPI_DMA_RX              0x00000001

//
//! Enable DMA for transfer and receive
//
#define SPI_DMA_BOTH            0x00000003

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

#endif  // _LPC17XX_SPI_H_
