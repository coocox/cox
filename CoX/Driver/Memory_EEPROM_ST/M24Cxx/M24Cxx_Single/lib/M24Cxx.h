//*****************************************************************************
//
//! \file M24Cxx.h
//! \brief Prototypes for the M24Cxx Driver.
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
#ifndef __M24Cxx_H__
#define __M24Cxx_H__

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
//! \addtogroup M24Cxx
//! @{
//
//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
//! \addtogroup M24Cxx_Driver_Single
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//! \addtogroup M24Cxx_User_Config
//! @{
//
//*****************************************************************************
   

//
//! User device config,it can only be M24C64 M24C32 M24C08
//! 
// 
#define M24Cxx_Device           M24C64 
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup M24Cxx_Hardware_Config
//! @{
//
//*****************************************************************************

//
//! Define IIC as a port connecting M24Cxx which can be configured
//
#define	M24Cxx_PIN_I2C_SCK	PB8
#define	M24Cxx_I2C_SCK		I2C1SCK
#define	M24Cxx_PIN_I2C_SDA	PB9
#define	M24Cxx_I2C_SDA		I2C1SDA
#define M24Cxx_PIN_I2C_PORT     I2C1_BASE  
#define M24Cxx_I2C_GPIO         SYSCTL_PERIPH_IOPB
  
//
//! Define M24Cxx I2C slave address
//
#define M24Cxx_ADDRESS          0x50 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup COX_M24Cxx_Exported_APIs
//! @{
//
//*****************************************************************************
extern void M24CxxInit(void);
extern void M24CxxByteWrite(unsigned char* pucBuffer, unsigned short usWriteAddr);
extern void M24CxxPageWrite(unsigned char* pucBuffer, unsigned short usWriteAddr, unsigned char ucNumByteToWrite);
extern void M24CxxBufferWrite(unsigned char* pucBuffer, unsigned short usWriteAddr, unsigned short usNumByteToWrite);
extern void M24CxxBufferRead(unsigned char* pucBuffer, unsigned short usReadAddr,unsigned short usNumByteToWrite);
extern void M24CxxWaitEepromStandbyState(void);
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