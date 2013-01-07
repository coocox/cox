//*****************************************************************************
//
//! \file M24LCxx.h
//! \brief Prototypes for the M24LCxx Driver.
//! \version V2.1.1.0
//! \date 6/1/2012
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
//!
//*****************************************************************************
#ifndef __M24LCxx_H__
#define __M24LCxx_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif
//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Memory
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup I2C_Eeprom
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M24LCxx
//! @{
//
//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
//! \addtogroup M24LCxx_Driver_Single
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//! \addtogroup M24LCxx_User_Config
//! @{
//
//*****************************************************************************
   

//
//! User device config,it can only be M24C64 M24C32 M24C08
//! 
// 
#define M24LCxx_Device           M24LC02
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup M24LCxx_Hardware_Config
//! @{
//
//*****************************************************************************

//
//! Define IIC as a port connecting M24LCxx which can be configured
//
#define	M24LCxx_PIN_I2C_SCK	PB6
#define	M24LCxx_I2C_SCK		I2C1SCK
#define	M24LCxx_PIN_I2C_SDA	PB7
#define	M24LCxx_I2C_SDA		I2C1SDA
#define M24LCxx_PIN_I2C_PORT     I2C1_BASE  
#define M24LCxx_I2C_GPIO         SYSCTL_PERIPH_IOPB
  
//
//! Define M24LCxx I2C slave address(does not contain RW bit)
//
#define M24LCxx_ADDRESS          0x50 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup COX_M24LCxx_Exported_APIs
//! @{
//
//*****************************************************************************
extern void M24LCxxInit(void);
extern void M24LCxxByteWrite(unsigned char* pucBuffer, unsigned short usWriteAddr);
extern void M24LCxxPageWrite(unsigned char* pucBuffer, unsigned short usWriteAddr, unsigned char ucNumByteToWrite);
extern void M24LCxxBufferWrite(unsigned char* pucBuffer, unsigned short usWriteAddr, unsigned short usNumByteToWrite);
extern void M24LCxxBufferRead(unsigned char* pucBuffer, unsigned short usReadAddr,unsigned short usNumByteToWrite);
extern void M24LCxxWaitEepromStandbyState(void);
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
//! Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //__AT25FS0X_H__
