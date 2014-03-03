//*****************************************************************************
//
//! \file      xhw_spi.h
//! \brief     Macros used when accessing the SPI hardware.
//! \version   V2.2.1.0
//! \date      $CURRENTTIME$
//! \author    CooCox
//! \copyright
//!
//! Copyright (c)  2011, CooCox
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
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************


#ifndef __XHW_SPI_H__
#define __XHW_SPI_H__

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"


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
//! \addtogroup LPC17xx_SPI_Register SPI Register Hardware Layer.
//! \brief      Here are detail register information.
//!             it contains:
//!                 - Register offset.
//!                 - detailed bit-field of the registers.
//!                 - Enum and mask of the registers.
//!
//! \note       Users can read or write the registers via xHWREG().
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SPI_Register_Offsets SPI Register Offset(Map)
//! \brief      Here is the register offset, users can get the register address
//!             via <b>SPI0_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//! SPI Control Register.
//! This register controls the operation of the SPI.
#define S0SPCR                  0x00000000

//! SPI Status Register.
//! This register shows the status of the SPI.
#define S0SPSR                  0x00000004

//! SPI Data Register.
//! This bi-directional register provides the transmit and receive data for the SPI.
//! Transmit data is provided to the SPI0 by writing to this register.
//! Data received by the SPI0 can be read from this register.
#define S0SPDR                  0x00000008

//! SPI Clock Counter Register.
//! This register controls the frequency of a master¡¯s SCK0.
#define S0SPCCR                 0x0000000C

//! SPI Interrupt Flag.
//! This register contains the interrupt flag for the SPI interface.
#define S0SPINT                 0x0000001C

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SPI_Register_CTCR SPI Register CTCR
//! \brief      SPI CTCR Register description.
//!
//! @{
//
//*****************************************************************************

//! Counter/Timer Mode.
#define CTCR_MODE_M             BIT_MASK(32, 1, 0)
#define CTCR_MODE_S             0

//! Count input select.
#define CTCR_CNT_INPUT_SEL_M    BIT_MASK(32, 3, 2)
#define CTCR_CNT_INPUT_SEL_S    2

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SPI_Register_S0SPCR SPI Register S0SPCR
//! \brief      SPI S0SPCR Register description.
//!
//! @{
//
//*****************************************************************************

//! SPI BIt control.
//! When set, SPI controller send 8-->16 bit data according to other register bits.
//! When Clear, SPI data length is fixed to 8-bit.
#define S0SPCR_BIT_EN           BIT_32_2

//! Clock Phase control
#define S0SPCR_CPHA             BIT_32_3

//! Clock Polarity control
#define S0SPCR_CPOL             BIT_32_4

//! Master Mode Select
#define S0SPCR_MSTR             BIT_32_5

//! LSB First controls which direction each byte is shifted when transferred.
#define S0SPCR_LSBF             BIT_32_6

//! Enable serial peripheral interrupt
#define S0SPCR_SPIE             BIT_32_7

//! SPI data length mask
#define S0SPCR_BITS_M           BIT_MASK(32, 11, 8)

//! SPI data length shift
#define S0SPCR_BITS_S           8

//! SPI 8-bit per transfer
#define S0SPCR_BITS_8           (BIT_32_11)

//! SPI 9-bit per transfer
#define S0SPCR_BITS_9           (BIT_32_11 | BIT_32_8)

//! SPI 10-bit per transfer
#define S0SPCR_BITS_10          (BIT_32_11 | BIT_32_9)

//! SPI 11-bit per transfer)
#define S0SPCR_BITS_11          (BIT_32_11 | BIT_32_9 | BIT_32_8)

//! SPI 12-bit per transfer)
#define S0SPCR_BITS_12          (BIT_32_11 | BIT_32_10)

//! SPI 13-bit per transfer)
#define S0SPCR_BITS_13          (BIT_32_11 | BIT_32_10 | BIT_32_8)

//! SPI 14-bit per transfer)
#define S0SPCR_BITS_14          (BIT_32_11 | BIT_32_10 | BIT_32_9)

//! SPI 15-bit per transfer)
#define S0SPCR_BITS_15          (BIT_32_11 | BIT_32_10 | BIT_32_9 | BIT_32_8)

//! SPI 16-bit per transfer)
#define S0SPCR_BITS_16          (BIT_32_ALL_0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SPI_Register_S0SPSR SPI Register S0SPSR
//! \brief      SPI S0SPSR Register description.
//!
//! @{
//
//*****************************************************************************

//! Slave abort
#define S0SPSR_ABRT             BIT_32_3

//! Mode Fault
#define S0SPSR_MODF             BIT_32_4

//! Read overrun
#define S0SPSR_ROVR             BIT_32_5

//! Write collision
#define S0SPSR_WCOL             BIT_32_6

//! Transfer complete
#define S0SPSR_SPIF             BIT_32_7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SPI_Register_S0SPDR SPI Register S0SPDR
//! \brief      SPI S0SPDR Register description.
//!
//! @{
//
//*****************************************************************************

//! SPI data mask
#define S0SPDR_DATA_M           BIT_MASK(32, 15, 0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SPI_Register_S0SPCCR SPI Register S0SPCCR
//! \brief      SPI S0SPCCR Register description.
//!
//! @{
//
//*****************************************************************************

//! SPI0 Clock counter setting
#define S0SPCCR_CNT_M           BIT_MASK(32, 7, 0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SPI_Register_S0SPINT SPI Register S0SPINT
//! \brief      SPI S0SPINT Register description.
//!
//! @{
//
//*****************************************************************************

//! SPI interrupt flag.
#define S0SPINT_SPIF            BIT_32_0

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

