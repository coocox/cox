//*****************************************************************************
//
//! \file xhw_spi.h
//! \brief Macros used when accessing the SPI hardware.
//! \version V2.2.1.0
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

#ifndef __xHW_SPI_H__
#define __xHW_SPI_H__

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
//! \addtogroup KLx_SPI_Register
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SPI_Register_Map SPI Register Map(Offset)
//! @{
//
//*****************************************************************************

//
//! SPI Control Register 1
//
#define SPI_C1               	0x00000000  

//
//! SPI Control Register 2
//
#define SPI_C2               	0x00000001  

//
//! SPI Baud Rate Register
//
#define SPI_BR                	0x00000002 

//
//! SPI Status Register
// 
#define SPI_S                   0x00000003 

//
//! SPI Data Register
// 
#define SPI_D                   0x00000005  

//
//! SPI Match Register
//
#define SPI_M                   0x00000007  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_Register_SPI_C1 SPI_C1
//! @{
//
//*****************************************************************************

//
//! SPI interrupt for SPRF and MODF enable 
//
#define SPI_C1_SPIE             0x80 

//
//! SPI system enable
//
#define SPI_C1_SPE              0x40 

//
//! SPI transmit interrupt enable
//
#define SPI_C1_SPTIE            0x20 

//
//! Master/slave mode select
//
#define SPI_C1_MSTR             0x10 

//
//! Clock polarity
//
#define SPI_C1_CPOL             0x08 

//
//! Clock phase
//
#define SPI_C1_CPHA             0x04 

//
//! Slave select output enable
//
#define SPI_C1_SSOE             0x02 

//
//! LSB first (shifter direction)
//
#define SPI_C1_LSBFE            0x01 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_Register_SPI_C2 SPI_C2
//! @{
//
//*****************************************************************************

//
//! SPI match interrupt enable
//
#define SPI_C2_SPMIE            0x80 

//
//! SPI low power interrupt enable
//
#define SPI_C2_SPLPIE           0x40 

//
//! Transmit DMA enable
//
#define SPI_C2_TXDMAE           0x20 

//
//! Master mode-fault function enable
//
#define SPI_C2_MODFEN           0x10

//
//! Bidirectional mode output enable
// 
#define SPI_C2_BIDIROE          0x08 

//
//! Receive DMA enable
//
#define SPI_C2_RXDMAE           0x04 

//
//! SPI stop in wait mode
//
#define SPI_C2_SPISWAI          0x02 

//
//! SPI pin control 0
//
#define SPI_C2_SPC0             0x01 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_Register_SPI_BR SPI_BR
//! @{
//
//*****************************************************************************

//
//! SPI baud rate prescale divisor select
//
#define SPI_BR_SPPR_M           0x70 

//
//! Baud rate prescaler divisor is 1
//
#define SPI_BR_SPPR_1           0x00 

//
//! Baud rate prescaler divisor is 2
//
#define SPI_BR_SPPR_2           0x10 

//
//! Baud rate prescaler divisor is 3
//
#define SPI_BR_SPPR_3           0x20 

//
//! Baud rate prescaler divisor is 4
//
#define SPI_BR_SPPR_4           0x30 

//
//! Baud rate prescaler divisor is 5
//
#define SPI_BR_SPPR_5           0x40 

//
//! Baud rate prescaler divisor is 6
//
#define SPI_BR_SPPR_6           0x50 

//
//! Baud rate prescaler divisor is 7
//
#define SPI_BR_SPPR_7           0x60 

//
//! Baud rate prescaler divisor is 8
//
#define SPI_BR_SPPR_8           0x70 

#define SPI_BR_SPPR_S           4	 

//
//! SPI baud rate divisor select
//
#define SPI_BR_SPR_M            0x0F 

//
//! Baud rate divisor is 2
//
#define SPI_BR_SPR_2            0x00 

//
//! Baud rate divisor is 4
//
#define SPI_BR_SPR_4            0x01 

//
//! Baud rate divisor is 8
//
#define SPI_BR_SPR_8            0x02 

//
//! Baud rate divisor is 16
//
#define SPI_BR_SPR_16           0x03 

//
//! Baud rate divisor is 32
//
#define SPI_BR_SPR_32           0x04 

//
//! Baud rate divisor is 64
//
#define SPI_BR_SPR_64           0x05 

//
//! Baud rate divisor is 128
//
#define SPI_BR_SPR_128          0x06

//
//! Baud rate divisor is 256
// 
#define SPI_BR_SPR_256          0x07

//
//! Baud rate divisor is 512
//
#define SPI_BR_SPR_512          0x08 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_Register_SPI_S SPI_S
//! @{
//
//*****************************************************************************

#define SPI_S_M                 0xF0

//
//! SPI read buffer full flag
//
#define SPI_S_SPRF              0x80

//
//! SPI match flag
//
#define SPI_S_SPMF              0x40 

//
//! SPI transmit buffer empty flag
//
#define SPI_S_SPTEF             0x20 

//
//! Master mode fault flag
//
#define SPI_S_MODF              0x10 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_Register_SPI_D SPI_D
//! @{
//
//*****************************************************************************

//
//! SPI Receive/Transmit Data
//
#define SPI_D_M                 0xFF 

#define SPI_D_S                 0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_Register_SPI_M SPI_M
//! @{
//
//*****************************************************************************

//
//! SPI hardware compare value
//
#define SPI_M_M                 0xFF 

#define SPI_M_S                 0

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
#endif // __HW_SPI_H__
