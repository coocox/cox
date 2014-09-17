//*****************************************************************************
//
//! \file      hw_spi.h
//! \brief     Macros used when accessing the SPI hardware.
//! \version   V3.0.0.0
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


#ifndef __LPC17XX_HW_SPI_H__
#define __LPX17XX_HW_SPI_H__

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
//! \addtogroup LPC17xx_SSP_Register_Offsets SSP Register Offset(Map)
//! \brief      Here is the register offset, users can get the register address
//!             via <b>SPIn_BASE(n = 0, 1) + offset</b>.
//! @{
//
//*****************************************************************************

//
//! SSP Control Register 0. Selects the serial clock rate, bus type, and data size.
//
#define SSP_CR0                 0x00000000


//
//! SSP Control Register 1.  Selects master/slave and other modes.
//
#define SSP_CR1                 0x00000004

//
//! SSP Data Register.
//
#define SSP_DR                  0x00000008

//
//! SSP Status Register.
//
#define SSP_SR                  0x0000000C

//
//! SSP Clock Prescale Register.
//
#define SSP_CPSR                0x00000010

//
//! SSP Interrupt Mask Set and Clear Register.
//
#define SSP_IMSC                0x00000014

//
//! SSP Raw Interrupt Status Register
//
#define SSP_RIS                 0x00000018

//
//! SSP Masked Interrupt Status Register
//
#define SSP_MIS                 0x0000001C

//
//! SSP Interrupt Clear Register
//
#define SSP_ICR                 0x00000020

//
//! SSP DMA Control Register
//
#define SSP_DMACR               0x00000024

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SSP_Register_SSP_CR0 SSP Register SSP_CR0
//! \brief      SSP SSP_CR0 Register description.
//!
//! @{
//
//*****************************************************************************

//! Data Size Select mask.
#define SSP_CR0_DSS_M           BIT_MASK(32, 3, 0)

//! Data Size Select shift.
#define SSP_CR0_DSS_S           0

//! Frame Format Select mask.
#define SSP_CR0_FRF_M           BIT_MASK(32, 5, 4)

//! Frame Format Select shift.
#define SSP_CR0_FRF_S           4

//! Clock Polarity control
#define SSP_CR0_CPOL            BIT_32_6

//! Clock Phase control
#define SSP_CR0_CPHA            BIT_32_7

//! Serial Clock Rate mask
#define SSP_CR0_SCR_M           BIT_MASK(32, 15, 8)

//! Serial Clock Rate shift
#define SSP_CR0_SCR_S           8

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SSP_Register_SSP_CR1 SSP Register SSP_CR1
//! \brief      SSP SSP_CR1 Register description.
//!
//! @{
//
//*****************************************************************************

//! Loop Back Mode.
#define SSP_CR1_LBM             BIT_32_0

//! SSP Enable.
#define SSP_CR1_SSE             BIT_32_1

//! Master/Slave Mode.
#define SSP_CR1_MS              BIT_32_2

//! Slave Output Disable
#define SSP_CR1_SOD             BIT_32_3

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SSP_Register_SSP_DR SSP Register SSP_DR
//! \brief      SSP SSP_DR Register description.
//!
//! @{
//
//*****************************************************************************

//! SSP data mask.
#define SSP_DR_DATA_M           BIT_MASK(32, 15, 0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SSP_Register_SSP_SR SSP Register SSP_SR
//! \brief      SSP SSP_SR Register description.
//!
//! @{
//
//*****************************************************************************

//! Transmit FIFO Empty.
#define SSP_SR_TFE              BIT_32_0

//! Transmit FIFO Not Full.
#define SSP_SR_TNF              BIT_32_1

//! Receive FIFO Not Empty.
#define SSP_SR_RNE              BIT_32_2

//! Receive FIFO Full
#define SSP_SR_RFF              BIT_32_3

//! Busy Flag.
#define SSP_SR_BSY              BIT_32_4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SSP_Register_SSP_CPSR SSP Register SSP_CPSR
//! \brief      SPI SSP_CPSR Register description.
//!
//! @{
//
//*****************************************************************************

//! SSPn Clock Prescale.
#define SSP_CPSR_CPSDVSR_M      BIT_MASK(32, 7, 0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SSP_Register_SSP_IMSC SSP Register SSP_IMSC
//! \brief      SSP SSP_IMSC Register description.
//!
//! @{
//
//*****************************************************************************

//! Receive Overrun Interrupt.
#define SSP_IMSC_ROR            BIT_32_0

//! Receive Timeout Interrupt.
#define SSP_IMSC_RT             BIT_32_1

//! Rx FIFO half full Interrupt.
#define SSP_IMSC_RX             BIT_32_2

//! Tx FIFO half empty Interrupt
#define SSP_IMSC_TX             BIT_32_3

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SSP_Register_SSP_RIS SSP Register SSP_RIS
//! \brief      SSP SSP_RIS Register description.
//!
//! @{
//
//*****************************************************************************

//! Receive Overrun.
#define SSP_RIS_ROR             BIT_32_0

//! Receive Timeout.
#define SSP_RIS_RT              BIT_32_1

//! Rx FIFO half full.
#define SSP_RIS_RX              BIT_32_2

//! Tx FIFO half empty
#define SSP_RIS_TX              BIT_32_3

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SSP_Register_SSP_MIS SSP Register SSP_MIS
//! \brief      SSP SSP_MIS Register description.
//!
//! @{
//
//*****************************************************************************

//! Receive Overrun.
#define SSP_MIS_ROR             BIT_32_0

//! Receive Timeout.
#define SSP_MIS_RT              BIT_32_1

//! Rx FIFO half full.
#define SSP_MIS_RX              BIT_32_2

//! Tx FIFO half empty
#define SSP_MIS_TX              BIT_32_3

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SSP_Register_SSP_ICR SSP Register SSP_ICR
//! \brief      SSP SSP_ICR Register description.
//!
//! @{
//
//*****************************************************************************

//! Clear Receive Overrun flag.
#define SSP_ICR_ROR             BIT_32_0

//! Clear Receive Timeout flag.
#define SSP_ICR_RT              BIT_32_1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SSP_Register_SSP_DMACR SSP Register SSP_DMACR
//! \brief      SSP SSP_DMACR Register description.
//!
//! @{
//
//*****************************************************************************

//! Receive DMA Enable.
#define SSP_DMACR_RXDMAE        BIT_32_0

//! Transmit DMA Enable.
#define SSP_DMACR_TXDMAE        BIT_32_1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************



//*****************************************************************************
//
//! \addtogroup LPC175x_6x_SPI_Register_Offsets SPI Register Offset(Map)
//! \brief      Here is the register offset, users can get the register address
//!             via <b>SPI2_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//! SPI Control Register.
//! This register controls the operation of the SPI.
#define SPI_CR                  0x00000000

//! SPI Status Register.
//! This register shows the status of the SPI.
#define SPI_SR                  0x00000004

//! SPI Data Register.
//! This bi-directional register provides the transmit and receive data for the SPI.
//! Transmit data is provided to the SPI0 by writing to this register.
//! Data received by the SPI0 can be read from this register.
#define SPI_DR                  0x00000008

//! SPI Clock Counter Register.
//! This register controls the frequency of a master¡¯s SCK0.
#define SPI_CCR                 0x0000000C

//! SPI Interrupt Flag.
//! This register contains the interrupt flag for the SPI interface.
#define SPI_INT                 0x0000001C

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC175x_6x_SPI_Register_S0SPCR SPI Register S0SPCR
//! \brief      SPI SPI_CR Register description.
//!
//! @{
//
//*****************************************************************************

//! SPI BIt control.
//! When set, SPI controller send 8-->16 bit data according to other register bits.
//! When Clear, SPI data length is fixed to 8-bit.
#define SPI_CR_BIT_EN           BIT_32_2

//! Clock Phase control
#define SPI_CR_CPHA             BIT_32_3

//! Clock Polarity control
#define SPI_CR_CPOL             BIT_32_4

//! Master Mode Select
#define SPI_CR_MSTR             BIT_32_5

//! LSB First controls which direction each byte is shifted when transferred.
#define SPI_CR_LSBF             BIT_32_6

//! Enable serial peripheral interrupt
#define SPI_CR_SPIE             BIT_32_7

//! SPI data length mask
#define SPI_CR_BITS_M           BIT_MASK(32, 11, 8)

//! SPI data length shift
#define SPI_CR_BITS_S           8

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC175x_6x_SPI_Register_SPI_SR SPI Register SPI_SR
//! \brief      SPI SPI_SR Register description.
//!
//! @{
//
//*****************************************************************************

//! Slave abort
#define SPI_SR_ABRT             BIT_32_3

//! Mode Fault
#define SPI_SR_MODF             BIT_32_4

//! Read overrun
#define SPI_SR_ROVR             BIT_32_5

//! Write collision
#define SPI_SR_WCOL             BIT_32_6

//! Transfer complete
#define SPI_SR_SPIF             BIT_32_7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC175x_6x_SPI_Register_SPI_DR SPI Register SPI_DR
//! \brief      SPI SPI_DR Register description.
//!
//! @{
//
//*****************************************************************************

//! SPI data mask
#define SPI_DR_DATA_M           BIT_MASK(32, 15, 0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC175x_6x_SPI_Register_SPI_CCR SPI Register SPI_CCR
//! \brief      SPI SPI_CCR Register description.
//!
//! @{
//
//*****************************************************************************

//! SPI Clock counter setting
#define SPI_CCR_CNT_M           BIT_MASK(32, 7, 0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC175x_6x_SPI_Register_SPI_INT SPI Register SPI_INT
//! \brief      SPI SPI_INT Register description.
//!
//! @{
//
//*****************************************************************************

//! SPI interrupt flag.
#define SPI_INT_SPIF            BIT_32_0

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

#endif // __LPC17XX_HW_SPI_H__
