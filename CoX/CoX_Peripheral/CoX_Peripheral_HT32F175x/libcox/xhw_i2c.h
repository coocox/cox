//*****************************************************************************
//
//! \file xhw_i2c.h
//! \brief Macros and defines used when accessing the I2C hardware.
//! \version V2.2.1.0
//! \date 05/02/2012
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
//! \addtogroup HT32F175x_275x_I2C_Register HT32F175x_275x I2C Register
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
//! \addtogroup HT32F175x_275x_I2C_Register_Offsets I2C Register Offset(Map)
//! \brief Here is the I2C register offset, users can get the register address
//! through <b>I2C_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! I2C Control Register
//
#define I2C_CR                  0x00000000  

//
//! I2C Interrupt Enable Register
//
#define I2C_IER                 0x00000004  

//
//! I2C Device Address Register
//
#define I2C_ADDR                0x00000008  

//
//! I2C Status Register
//
#define I2C_CSR                 0x0000000C  

//
//! I2C SCL High Period Generation Register
//
#define I2C_SHPGR               0x00000010  

//
//! I2C SCL Low Period Generation Register
//
#define I2C_SLPGR               0x00000014  

//
//! I2C Data Register
//
#define I2C_DR                  0x00000018  

//
//! I2C Target Address Register
//
#define I2C_TAR                 0x0000001C

//
//! I2C Address Mask Register
//
#define I2C_ADDMR               0x00000020  

//
//! I2C Address Snoop Register
//
#define I2C_ADDSR               0x00000024  

//
//! I2C Timeout Register
//
#define I2C_TOUT                0x00000028   

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_I2C_Register_I2C_CR I2C Control Register(I2C_CR)
//! @{
//
//*****************************************************************************

//
//! Timeout counter enable bit
//
#define I2C_CR_TOUTEN           0x00001000 

//
//! DMA mode send NACK signal automatically
//
#define I2C_CR_DMANACKEN        0x00000400

//
//! Rx DMA request enable bit
//
#define I2C_CR_RXDMAEN          0x00000200 

//
//! Tx DMA request enable bit
//
#define I2C_CR_TXDMAEN          0x00000100

//
//! Addressing Mode
//
#define I2C_CR_ADRM             0x00000080 

//
//! I2C Interface Enable
//
#define I2C_CR_I2CEN            0x00000008

//
//! General Call Enable
//
#define I2C_CR_GCEN             0x00000004 

//
//! STOP Condition control
//
#define I2C_CR_STOP             0x00000002 

//
//! Acknowledge Bit
//
#define I2C_CR_AA               0x00000001 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_I2C_Register_I2C_IER I2C Interrupt Enable Register(I2C_IER)
//! @{
//
//*****************************************************************************

//
//! RX Buffer Full Interrupt Enable Bit
//
#define I2C_IER_RXBFIE          0x00040000

//
//! Data Register Empty Interrupt Enable Bit in Transmitter Mode
//
#define I2C_IER_TXDEIE          0x00020000

//
//! Data Register Not Empty Interrupt Enable Bit in Receiver Mode
//
#define I2C_IER_RXDNEIE         0x00010000

//
//! Timeout Interrupt Enable Bit
//
#define I2C_IER_TOUTIE          0x00000800 

//
//! Bus Error Interrupt Enable Bit
//
#define I2C_IER_BUSERRIE        0x00000400 

//
//! Received Not Acknowledge Interrupt Enable Bit
//
#define I2C_IER_RXNACKIE        0x00000200 

//
//! Arbitration Loss Interrupt Enable Bit in I2C multi-master mode
//
#define I2C_IER_ARBLOSIE        0x00000100 

//
//! General Call Slave Interrupt Enable Bit
//
#define I2C_IER_GCSIE           0x00000008 

//
//! Slave Address Match Interrupt Enable Bit
//
#define I2C_IER_ADRSIE          0x00000004 

//
//! STOP Condition Detected Interrupt Enable Bit
//
#define I2C_IER_STOIE           0x00000002 

//
//! START Condition Transmit Interrupt Enable Bit
//
#define I2C_IER_STAIE           0x00000001 


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_I2C_Register_I2C_ADDR I2C Address Register(I2C_ADDR)
//! @{
//
//*****************************************************************************

//
//! I2C Data Register
//
#define I2C_ADDR_ADDR_M         0x000003FF  

//
//! I2C Data Register
//
#define I2C_ADDR_ADDR_S         0  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_I2C_Register_I2C_CSR I2C Status Register(I2C_CSR)
//! @{
//
//*****************************************************************************

//
//! Transmitter / Receiver Mode
//
#define I2C_CSR_TXNRX           0x00200000  

//
//! Master Mode
//
#define I2C_CSR_MASTER          0x00100000  

//
//! Bus Busy
//
#define I2C_CSR_BUSBUSY         0x00080000

//
//! Buffer Full Flag in Receiver Mode
//
#define I2C_CSR_RXBF            0x00040000

//
//! Data Register Empty in Transmitter Mode
//
#define I2C_CSR_TXDE            0x00020000

//
//! Data Register Not Empty in Receiver Mode
//
#define I2C_CSR_RXDNE           0x00010000

//
//! Timeout Counter overflow Flag
//
#define I2C_CSR_TOUTF           0x00000800

//
//! Bus Error Flag
//
#define I2C_CSR_BUSERR          0x00000400

//
//! Received Not Acknowledge Flag
//
#define I2C_CSR_RXNACK          0x00000200

//
//! Arbitration Loss Flag
//
#define I2C_CSR_ARBLOS          0x00000100

//
//! General Call Slave Flag
//
#define I2C_CSR_GCS             0x00000008

//
//! Address Transmit (master mode) / Address Receive (slave mode) Flag
//
#define I2C_CSR_ADRS            0x00000004

//
//! STOP Condition Detected Flag
//
#define I2C_CSR_STO             0x00000002

//
//! START Condition Transmit
//
#define I2C_CSR_STA             0x00000001


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_I2C_Register_I2C_SHPGR I2C SCL High Period Generation
//! Register(I2C_SHPGR)
//! @{
//
//*****************************************************************************

//
//! SCL Clock High Period Generation
//
#define I2C_SHPGR_SHPG_M        0x0000FFFF  

//
//! SCL Clock High Period Generation
//
#define I2C_SHPGR_SHPG_S        0  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_I2C_Register_I2C_SLPGR I2C SCL Low Period Generation
//! Register(I2C_SLPGR)
//! @{
//
//*****************************************************************************

//
//! SCL Clock low Period Generation
//
#define I2C_SLPGR_SLPG_M        0x0000FFFF  

//
//! SCL Clock low Period Generation
//
#define I2C_SLPGR_SLPG_S        0  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_I2C_Register_I2C_DR I2C 0 data Register(I2C_DR)
//! \brief Defines for the bit fields in the I2C_DR register.
//! @{
//
//*****************************************************************************

//
//! I2C Data Register
//
#define I2C_DR_DATA_M           0x000000FF  

//
//! I2C Data Register
//
#define I2C_DR_DATA_S           0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_I2C_Register_I2C_TAR I2C Target Address Register(I2C_TAR)
//! @{
//
//*****************************************************************************

//
//! Read or Write Direction
//
#define I2C_TAR_RWD             0x00000400  

//
//! Target Slave Address
//
#define I2C_TAR_TSA_M           0x000003FF  

//
//! Target Slave Address
//
#define I2C_ADDR1_ADDR_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_I2C_Register_I2C_ADDMR I2C Address Mask Register (I2CADDMR)
//! @{
//
//*****************************************************************************

//
//! Address Mask Control Bit Mask
//
#define I2C_ADDMR_M             0x000003FF  

//
//! Address Mask Control Bit Shift
//
#define I2C_ADDMR_S             0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_I2C_Register_I2C_TOUT I2C Timeout Register (I2CTOUT)
//! @{
//
//*****************************************************************************

//
//! Prescaler clock base Bit Mask
//
#define I2C_TOUT_PSC_M          0x00070000

//
//! Prescaler clock base Bit Shift
//
#define I2C_TOUT_PSC_S          16  

//
//! Timeout Counter Bit Mask
//
#define I2C_TOUT_TOUT_M         0x0000FFFF

//
//! Timeout Counter Bit Shift
//
#define I2C_TOUT_TOUT_S         0

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
