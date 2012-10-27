//*****************************************************************************
//
//! \file xhw_i2c.h
//! \brief Macros and defines used when accessing the I2C hardware.
//! \version V2.2.1.0
//! \date 08/16/2012
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
//! \addtogroup KLx_I2C_Register KLx I2C Register
//! \brief Here are the detailed info of SPI registers. 
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
//! \addtogroup KLx_I2C_Register_Offsets I2C Register Offset(Map)
//! \brief Here is the I2C register offset, users can get the register address
//! through <b>I2C_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! I2C Address Register 1
//
#define I2C_A1                  0x00000000  

//
//! I2C Frequency Divider register
//
#define I2C_FREQ                0x00000001  

//
//! I2C Control Register 1
//
#define I2C_CON1                0x00000002  

//
//! I2C Status Register
//
#define I2C_STATUS              0x00000003  

//
//! I2C Data I/O register
//
#define I2C_DAT                 0x00000004  

//
//! I2C Control Register 2
//
#define I2C_CON2                0x00000005  

//
//! I2C Programmable Input Glitch Filter register
//
#define I2C_FLT                 0x00000006  

//
//! I2C Range Address register
//
#define I2C_RA                  0x00000007  

//
//! I2C SMBus Control and Status register
//  
#define I2C_SMB                 0x00000008  

//
//! I2C Address Register 2
//
#define I2C_A2                  0x00000009  

//
//! I2C SCL Low Timeout Register High
//
#define I2C_SLTH                0x0000000A  

//
//! I2C SCL Low Timeout Register Low
//
#define I2C_SLTL                0x0000000B    

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_I2C_Register_I2C_A1 I2C Address Register 1(I2C_A1)
//! \brief Defines for the bit fields in the I2C_A1 register.
//! @{
//
//*****************************************************************************

//
//! I2C Address mask
//
#define I2C_A1_AD_M             0x000000FE  

//
//! I2C Address shift
//
#define I2C_A1_AD_S             1   

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_I2C_Register_I2C_FREQ I2C Frequency Divider register(I2C_FREQ)
//! \brief Defines for the bit fields in the I2C_FREQ register.
//! @{
//
//*****************************************************************************

//
//! The MULT bits define the multiplier factor mul.
//
#define I2C_FREQ_MULT_M         0x000000C0  

//
//! The MULT bits define the multiplier factor mul.
//
#define I2C_FREQ_MULT_S         6

//
//! ClockRate.
//
#define I2C_FREQ_ICR_M          0x0000003F  

//
//! ClockRate.
//
#define I2C_FREQ_ICR_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_I2C_Register_I2C_CON1 I2C Control Register 1(I2C_CON1)
//! \brief Defines for the bit fields in the I2C_CON1 register.
//! @{
//
//*****************************************************************************

//
//! I2C Enable
//
#define I2C_CON1_EN             0x00000080

//
//! I2C Interrupt Enable
//
#define I2C_CON1_IE             0x00000040

//
//! I2C Master Mode Select
//
#define I2C_CON1_MST            0x00000020

//
//! I2C Transmit Mode Select
//
#define I2C_CON1_TX             0x00000010

//
//! I2C Transmit Acknowledge Enable
//
#define I2C_CON1_TXAK           0x00000008

//
//! I2C Repeat START
//
#define I2C_CON1_RSTA           0x00000004

//
//! I2C Wakeup Enable
//
#define I2C_CON1_WUEN           0x00000002

//
//! I2C DMA Enable
//
#define I2C_CON1_DMAEN          0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_I2C_Register_I2C_STATUS I2C Status Register(I2C_STATUS)
//! \brief Defines for the bit fields in the I2C_STATUS register.
//! @{
//
//*****************************************************************************

//
//! I2C Transfer Complete Flag
//
#define I2C_STATUS_TCF          0x00000080

//
//! I2C Addressed As A Slave
//
#define I2C_STATUS_IAAS         0x00000040

//
//! I2C Bus Busy
//
#define I2C_STATUS_BUSY         0x00000020

//
//! I2C Arbitration Lost
//
#define I2C_STATUS_ARBL         0x00000010

//
//! I2C Range Address Match
//
#define I2C_STATUS_RAM          0x00000008

//
//! I2C Slave Read/Write
//
#define I2C_STATUS_SRW          0x00000004

//
//! I2C Interrupt Flag
//
#define I2C_STATUS_IF           0x00000002

//
//! Receive Acknowledge
//
#define I2C_STATUS_RXAK         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_I2C_Register_I2C_DAT I2C Data I/O register(I2C_DAT)
//! \brief Defines for the bit fields in the I2C_DAT register.
//! @{
//
//*****************************************************************************

//
//! I2C Data Register
//
#define I2C_DAT_DATA_M          0x000000FF  

//
//! I2C Data Register
//
#define I2C_DAT_DATA_S          0  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_I2C_Register_I2C_CON2 I2C Control Register 2(I2C_CON2)
//! \brief Defines for the bit fields in the I2C_CON2 register.
//! @{
//
//*****************************************************************************

//
//! General Call Address Enable
//
#define I2C_CON2_GCAEN          0x00000080

//
//! Address Extension
//
#define I2C_CON2_ADEXT          0x00000040

//
//! High Drive Select
//
#define I2C_CON2_HDRS           0x00000020

//
//! Slave Baud Rate Control
//
#define I2C_CON2_SBRC           0x00000010

//
//! Range Address Matching Enable
//
#define I2C_CON2_RMEN           0x00000008

//
//! Slave Address
//
#define I2C_CON2_AD10B_M        0x00000007

//
//! Slave Address
//
#define I2C_CON2_AD10B_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_I2C_Register_I2C_FLY I2C Programmable Input Glitch Filter register(I2C_FLY)
//! \brief Defines for the bit fields in the I2C_FLY register.
//! @{
//
//*****************************************************************************

//
//! I2C Stop Hold Enable
//
#define I2C_FLT_SHEN            0x00000080  

//
//! I2C Bus Stop Detect Flag
//
#define I2C_FLT_STOPF           0x00000040

//
//! I2C Bus Stop Interrupt Enable
//
#define I2C_FLT_STOPIE          0x00000020

//
//! I2C Programmable Filter Factor
//
#define I2C_FLT_FLT_M           0x0000001F

//
//! I2C Programmable Filter Factor
//
#define I2C_FLT_FLT_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_I2C_Register_I2C_RA I2C Range Address register(I2C_RA)
//! \brief Defines for the bit fields in the I2C_RA register.
//! @{
//
//*****************************************************************************

//
//! I2C Range Slave Address
//
#define I2C_RA_ADDR_M           0x000000FE  

//
//! I2C Range Slave Address
//
#define I2C_RA_ADDR_S           1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_I2C_Register_I2C_SMB I2C SMBus Control and Status register(I2C_SMB)
//! \brief Defines for the bit fields in the I2C_SMB register.
//! @{
//
//*****************************************************************************

//
//! I2C Fast NACK/ACK Enable
//
#define I2C_SMB_FACK            0x00000080

//
//! I2C SMBus Alert Response Address Enable
//
#define I2C_SMB_ALERTEN         0x00000040

//
//! I2C Second I2C Address Enable
//
#define I2C_SMB_SIICAEN         0x00000020


//
//! I2C Timeout Counter Clock Select
//
#define I2C_SMB_TCKSEL          0x00000010


//
//! SCL Low Timeout Flag
//
#define I2C_SMB_SLTF            0x00000008

//
//! SCL High Timeout Flag 1
//
#define I2C_SMB_SHTF1           0x00000004

//
//! I2C SCL High Timeout Flag 2
//
#define I2C_SMB_SHTF2           0x00000002

//
//! SHTF2 Interrupt Enable
//
#define I2C_SMB_SHTF2IE         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_I2C_Register_I2C_A2 I2C Address Register 2(I2C_A2)
//! \brief Defines for the bit fields in the I2C_A2 register.
//! @{
//
//*****************************************************************************

//
//! I2C SMBus Address
//
#define I2C_A2_SAD_M            0x000000FE  

//
//! I2C SMBus Address
//
#define I2C_A2_SAD_S            1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_I2C_Register_I2C_SLTH I2C SCL Low Timeout Register High(I2C_SLTH)
//! \brief Defines for the bit fields in the I2C_SLTH register.
//! @{
//
//*****************************************************************************

//
//! I2C Address Mask register 1
//
#define I2C_SLTH_SSLT_M         0x000000FF  

//
//! I2C Address Mask register 1
//
#define I2C_SLTH_SSLT_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_I2C_Register_I2C_SLTL I2C SCL Low Timeout Register Low(I2C_SLTL)
//! \brief Defines for the bit fields in the I2C_SLTL register.
//! @{
//
//*****************************************************************************

//
//! I2C Address Mask register 2
//
#define I2C_SLTL_SSLT_M         0x000000FF 

//
//! I2C Address Mask register 2
//
#define I2C_SLTL_SSLT_S         0

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

