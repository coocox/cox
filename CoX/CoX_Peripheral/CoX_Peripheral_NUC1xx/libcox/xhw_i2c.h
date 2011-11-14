//*****************************************************************************
//
//! \file xhw_i2c.h
//! \brief Macros and defines used when accessing the I2C hardware.
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
//! \addtogroup NUC1xx_I2C_Register NUC1xx I2C Register
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
//! \addtogroup NUC1xx_I2C_Register_Offsets I2C Register Offset(Map)
//! \brief Here is the I2C register offset, users can get the register address
//! through <b>I2C_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! I2C Control Register
//
#define I2C_O_CON               0x00000000  

//
//! I2C Slave Address Register0
//
#define I2C_O_ADDR0             0x00000004  

//
//! I2C DATA Register
//
#define I2C_O_DAT               0x00000008  

//
//! I2C Status Register
//
#define I2C_O_STATUS            0x0000000C  

//
//! I2C Clock Divided Register
//
#define I2C_O_CLK               0x00000010  

//
//! I2C Time Out Control Register
//
#define I2C_O_TOC               0x00000014  

//
//! I2C Slave Address Register1
//
#define I2C_O_ADDR1             0x00000018  

//
//! I2C Slave Address Register2
//
#define I2C_O_ADDR2             0x0000001C  

//
//! I2C Slave Address Register3
//
#define I2C_O_ADDR3             0x00000020  

//
//! I2C Slave Address Mask Register0
//
#define I2C_O_ADM0              0x00000024  

//
//! I2C Slave Address Mask Register1
//
#define I2C_O_ADM1              0x00000028  

//
//! I2C Slave Address Mask Register2
//
#define I2C_O_ADM2              0x0000002C  

//
//! I2C Slave Address Mask Register3
//
#define I2C_O_ADM3              0x00000030   

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_I2C_Register_I2C_0_CON I2C 0 Control Register(I2C_0_CON)
//! \brief Defines for the bit fields in the I2C0_CNTRL register.
//! @{
//
//*****************************************************************************

//
//! Enable I2C interrupt
//
#define I2C_CON_EI              0x00000080  

//
//! I2C Controller Enable Bit
//
#define I2C_CON_ENS1            0x00000040  

//
//! I2C START Control Bit
//
#define I2C_CON_STA             0x00000020  

//
//! I2C STOP Control Bit
//
#define I2C_CON_STO             0x00000010  

//
//! I2C Interrupt Flag
//
#define I2C_CON_SI              0x00000008  

//
//! Assert Acknowledge Control Bit
//
#define I2C_CON_AA              0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_I2C_Register_I2C_0_ADDR0 I2C 0 Address 0 Register(I2C_0_ADDR0)
//! \brief Defines for the bit fields in the I2C_0_ADDR0 register.
//! @{
//
//*****************************************************************************

//
//! I2C Address Register
//
#define I2C_ADDR0_ADDR_M        0x000000FE  

//
//! I2C Address Register
//
#define I2C_ADDR0_ADDR_S        1

//
//! I2C General Call Function
//
#define I2C_ADDR0_GC            0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_I2C_Register_I2C_0_DAT I2C 0 Data Register(I2C_0_DAT)
//! \brief Defines for the bit fields in the I2C_0_DAT register.
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
//! \addtogroup NUC1xx_I2C_Register_I2C_0_STATUS I2C 0 Status Register(I2C_0_STATUS)
//! \brief Defines for the bit fields in the I2C_0_STATUS register.
//! @{
//
//*****************************************************************************

//
//! The status register of I2C
//
#define I2C_STATUS_M            0x000000FF  

//
//! The status register of I2C
//
#define I2C_STATUS_S            0  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_I2C_Register_I2C_0_CLK I2C 0 CLK Register(I2C_0_CLK)
//! \brief Defines for the bit fields in the I2C_0_CLK register.
//! @{
//
//*****************************************************************************

//
//! I2C clock divided Register
//
#define I2C_CLK_CLK_M           0x000000FF  

//
//! I2C clock divided Register
//
#define I2C_CLK_CLK_S           0  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_I2C_Register_I2C_0_TOC I2C 0 Time-out Register counter(I2C_0_TOC)
//! \brief Defines for the bit fields in the I2C_0_TOC register.
//! @{
//
//*****************************************************************************

//
//! Time-out counter is enabled/disable
//
#define I2C_TOC_ENTI            0x00000004  

//
//! Time-Out counter input clock is divided by 4
//
#define I2C_TOC_DIV4            0x00000002  

//
//! Time-Out Flag
//
#define I2C_TOC_TIF             0x0000001 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_I2C_Register_I2C_0_ADDR1 I2C 0 Address 1 Register(I2C_0_ADDR1)
//! \brief Defines for the bit fields in the I2C_0_ADDR1 register.
//! @{
//
//*****************************************************************************

//
//! I2C Address Register 1
//
#define I2C_ADDR1_ADDR_M        0x000000FE  

//
//! I2C Address Register 1
//
#define I2C_ADDR1_ADDR_S        1

//
//! I2C General Call Function
//
#define I2C_ADDR1_GC            0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_I2C_Register_I2C_0_ADDR2 I2C 0 Address 2 Register(I2C_0_ADDR2)
//! \brief Defines for the bit fields in the I2C_0_ADDR2 register.
//! @{
//
//*****************************************************************************

//
//! I2C Address Register 2
//
#define I2C_ADDR2_ADDR_M        0x000000FE  

//
//! I2C Address Register 2
//
#define I2C_ADDR2_ADDR_S        1

//
//! I2C General Call Function
//
#define I2C_ADDR2_GC            0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_I2C_Register_I2C_0_ADDR3 I2C 0 Address 3 Register(I2C_0_ADDR3)
//! \brief Defines for the bit fields in the I2C_0_ADDR3 register.
//! @{
//
//*****************************************************************************

//
//! I2C Address Register 3
//
#define I2C_ADDR3_ADDR_M        0x000000FE  

//
//! I2C Address Register 3
//
#define I2C_ADDR3_ADDR_S        1

//
//! I2C General Call Function
//
#define I2C_ADDR3_GC            0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_I2C_Register_I2C_0_ADM0 I2C 0 Address Mask register 0(I2C_0_ADM0)
//! \brief Defines for the bit fields in the I2C_0_ADM0 register.
//! @{
//
//*****************************************************************************

//
//! I2C Address Mask register 0
//
#define I2C_ADM0_ADM_M          0x000000FE  

//
//! I2C Address Mask register 0
//
#define I2C_ADM0_ADM_S          1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_I2C_Register_I2C_0_ADM1 I2C 0 Address Mask register 1(I2C_0_ADM1)
//! \brief Defines for the bit fields in the I2C_0_ADM1 register.
//! @{
//
//*****************************************************************************

//
//! I2C Address Mask register 1
//
#define I2C_ADM1_ADM_M          0x000000FE  

//
//! I2C Address Mask register 1
//
#define I2C_ADM1_ADM_S          1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_I2C_Register_I2C_0_ADM2 I2C 0 Address Mask register 2(I2C_0_ADM2)
//! \brief Defines for the bit fields in the I2C_0_ADM2 register.
//! @{
//
//*****************************************************************************

//
//! I2C Address Mask register 2
//
#define I2C_ADM2_ADM_M          0x000000FE  

//
//! I2C Address Mask register 2
//
#define I2C_ADM2_ADM_S          1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_I2C_Register_I2C_0_ADM3 I2C 0 Address Mask register 3(I2C_0_ADM3)
//! \brief Defines for the bit fields in the I2C_0_ADM3 register.
//! @{
//
//*****************************************************************************

//
//! I2C Address Mask register 3
//
#define I2C_ADM3_ADM_M          0x000000FE  

//
//! I2C Address Mask register 3
//
#define I2C_ADM3_ADM_S          1

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

