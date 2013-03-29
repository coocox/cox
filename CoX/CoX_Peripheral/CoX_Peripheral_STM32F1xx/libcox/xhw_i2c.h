//*****************************************************************************
//
//! \file xhw_i2c.h
//! \brief Macros and defines used when accessing the I2C hardware.
//! \version V2.2.1.0
//! \date 02/03/2012
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
#ifndef __XHW_I2C_H__
#define __XHW_I2C_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup I2C
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Register STM32F1xx I2C Register
//! \brief Here are the detailed info of I2C registers. 
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
//! \addtogroup STM32F1xx_I2C_Register_Offsets I2C Register Offset(Map)
//! \brief Here is the I2C register offset, users can get the register address
//! through <b>I2C_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! I2C Control register 1
//
#define I2C_CR1                 0x00000000  

//
//! I2C Control register 2
//
#define I2C_CR2                 0x00000004

//
//! I2C Own address register 1
//
#define I2C_OAR1                0x00000008  

//
//! I2C Own address register 2
//
#define I2C_OAR2                0x0000000C  

//
//! I2C Data register
//
#define I2C_DR                  0x00000010  

//
//! I2C Status register 1
//
#define I2C_SR1                 0x00000014  

//
//! I2C Status register 2
//
#define I2C_SR2                 0x00000018  

//
//! I2C Clock control register
//
#define I2C_CCR                 0x0000001C  

//
//! I2C TRISE register
//
#define I2C_TRISE               0x00000020  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Register_I2C_CR1 I2C Control Register 1(I2C_CR1)
//! \brief Defines for the bit fields in the I2C_CR1 register.
//! @{
//
//*****************************************************************************

//
//! Software reset
//
#define I2C_CR1_SWRST           0x00008000  

//
//! SMBus alert
//
#define I2C_CR1_ALERT           0x00002000 

//
//! Packet error checking
//
#define I2C_CR1_PEC             0x00001000 

//
//! Acknowledge/PEC Position (for data reception)
//
#define I2C_CR1_POS             0x00000800

//
//! Acknowledge enable
//
#define I2C_CR1_ACK             0x00000400

//
//! Stop generation
//
#define I2C_CR1_STOP            0x00000200

//
//! Start generation
//
#define I2C_CR1_START           0x00000100

//
//! Clock stretching disable (Slave mode)
//
#define I2C_CR1_NOSTRETCH       0x00000080

//
//! General call enable
//
#define I2C_CR1_ENGC            0x00000040

//
//! PEC enable
//
#define I2C_CR1_ENPEC           0x00000020

//
//! ARP enable
//
#define I2C_CR1_ENARP           0x00000010

//
//! SMBus type
//
#define I2C_CR1_SMBTYPE         0x00000008

//
//! SMBus mode
//
#define I2C_CR1_SMBUS           0x00000002 

//
//! Peripheral enable
//
#define I2C_CR1_PE              0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Register_I2C_CR2 I2C Control register 2(I2C_CR2)
//! \brief Defines for the bit fields in the I2C_CR2 register.
//! @{
//
//*****************************************************************************

//
//! DMA last transfer
//
#define I2C_CR2_LAST            0x00001000

//
//! DMA requests enable
//
#define I2C_CR2_DMAEN           0x00000800

//
//! Buffer interrupt enable
//
#define I2C_CR2_ITBUFEN         0x00000400

//
//! Event interrupt enable
//
#define I2C_CR2_ITEVTEN         0x00000200

//
//! Error interrupt enable
//
#define I2C_CR2_ITERREN         0x00000100

//
//! Peripheral clock frequency mask
//
#define I2C_CR2_FREQ_M          0x0000003F

//
//! Peripheral clock frequency shift
//
#define I2C_CR2_FREQ_S          0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Register_I2C_OAR1 I2C Own address register 1(I2C_OAR1)
//! \brief Defines for the bit fields in the I2C_OAR1 register.
//! @{
//
//*****************************************************************************

//
//! Addressing mode (slave mode)
//
#define I2C_OAR1_ADDMODE        0x00008000

//
//! Interface address mask
//
#define I2C_OAR1_ADD98_M        0x00000300  

//
//! Interface address mask shift
//
#define I2C_OAR1_ADD98_S        8  

//                                                                                            
//! Interface address mask
//
#define I2C_OAR1_ADD71_M        0x000000FE  

//
//! Interface address mask shift
//
#define I2C_OAR1_ADD71_S        1 

//
//! Interface address
//
#define I2C_OAR1_ADD0           0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Register_I2C_OAR2 I2C Own address register 2(I2C_OAR2)
//! \brief Defines for the bit fields in the I2C_OAR2 register.
//! @{
//
//*****************************************************************************

//                                                                                            
//! Interface address mask
//
#define I2C_OAR2_ADD71_M        0x000000FE  

//
//! Interface address mask shift
//
#define I2C_OAR2_ADD71_S        1 

//
//! Interface address
//
#define I2C_OAR1_ENDUAL         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Register_I2C_DR I2C Data register(I2C_DR)
//! \brief Defines for the bit fields in the I2C_DR register.
//! @{
//
//*****************************************************************************

//
//! 8-bit data register mask
//
#define I2C_DR_DR_M             0x000000FF  

//
//! 8-bit data register shift
//
#define I2C_DR_DR_S             0  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Register_I2C_SR1 I2C Status register 1(I2C_SR1)
//! \brief Defines for the bit fields in the I2C_SR1 register.
//! @{
//
//*****************************************************************************

//
//! SMBus alert
//
#define I2C_SR1_SMBALERT        0x00008000  

//
//! Timeout or Tlow error
//
#define I2C_SR1_TIMEOUT         0x00004000  

//
//! PEC Error in reception
//
#define I2C_SR1_PECERR          0x00001000

//
//! Overrun/Underrun
//
#define I2C_SR1_OVR             0x00000800

//
//! Acknowledge failure
//
#define I2C_SR1_AF              0x00000400

//
//! Arbitration lost (master mode)
//
#define I2C_SR1_ARLO            0x00000200

//
//! Bus error
//
#define I2C_SR1_BERR            0x00000100

//
//! Data register empty (transmitters)
//
#define I2C_SR1_TXE             0x00000080

//
//! Data register not empty (receivers)
//
#define I2C_SR1_RXNE            0x00000040

//
//! Stop detection (slave mode)
//
#define I2C_SR1_STOPF           0x00000010

//
//! 10-bit header sent (Master mode)
//
#define I2C_SR1_ADD10           0x00000008

//
//! Byte transfer finished
//
#define I2C_SR1_BTF             0x00000004

//
//! Address sent (master mode)/matched (slave mode)
//
#define I2C_SR1_ADDR            0x00000002

//
//! Start bit (Master mode)
//
#define I2C_SR1_SB              0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Register_I2C_SR2 I2C Status register 2(I2C_SR2)
//! \brief Defines for the bit fields in the I2C_SR2 register.
//! @{
//
//*****************************************************************************

//
//! Packet error checking register mask
//
#define I2C_SR2_PEC_M           0x0000FF00  

//
//! Packet error checking register shift
//
#define I2C_SR2_PEC_S           8

//
//! Dual flag (Slave mode)
//
#define I2C_SR2_DUALF           0x00000080

//
//! SMBus host header (Slave mode)
//
#define I2C_SR2_SMBHOST         0x00000040

//
//! SMBus device default address (Slave mode)
//
#define I2C_SR2_SMBDEFAULT      0x00000020

//
//! General call address (Slave mode)
//
#define I2C_SR2_GENCALL         0x00000010

//
//! Transmitter/receiver
//
#define I2C_SR2_TRA             0x00000004

//
//! Bus busy
//
#define I2C_SR2_BUSY            0x00000002

//
//! Master/slave
//
#define I2C_SR2_MSL             0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Register_I2C_CCR I2C Clock control register(I2C_CCR)
//! \brief Defines for the bit fields in the I2C_CCR register.
//! @{
//
//*****************************************************************************

//
//! I2C master mode selection
//
#define I2C_CCR_F_S             0x00008000 

//
//! Fast mode duty cycle
//
#define I2C_CCR_DUTY            0x00004000

//
//! Clock control register in Fast/Standard mode (Master mode)
//
#define I2C_CCR_CCR_M           0x00000FFF

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Register_I2C_TRISE I2C TRISE register(I2C_TRISE)
//! \brief Defines for the bit fields in the I2C_TRISE register.
//! @{
//
//*****************************************************************************

//
//! Maximum rise time in Fast/Standard mode (Master mode)
//
#define I2C_TRISE_TRISE_M       0x0000003F  

//
//! Maximum rise time in Fast/Standard mode (Master mode)
//
#define I2C_TRISE_TRISE_S       0

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

#endif // __XHW_I2C_H__


