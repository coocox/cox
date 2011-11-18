//*****************************************************************************
// 
//! \file di_ad7415.h
//! \brief Temperature Sensor (AD7416) and Four Single-Channel ADC drver
//! \version V2.1.1.0
//! \date 25. Aug. 2011
//! \author CooCox
//!
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

#ifndef __I2C_TEMP_AD7415_H__
#define __I2C_TEMP_AD7415_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this heADer
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
//! \addtogroup Sensor
//! @{  
//! \addtogroup Temperature_Sensor
//! @{
//! \addtogroup AD7415
//! @{  
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup AD7415_Application_Configs AD7415 Application Configs
//!  
//! \brief It is Static preach, the 4 macros must be define with the right value
//! according your application before use the APIS.  
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! AD7415 Device config, here must be configured before use the API.
//
//*****************************************************************************

//
//! Config the device i2c Address
//
#define AD7415_I2C_ADDRESS      0x48

//
//! Config the devide i2c bus master
//
#define AD7415_MASTER_BASE      xI2C0_BASE

//
//! Config the i2c SDA pin
//
#define AD7415_PIN_I2CSDA       PA8

//
//! Config the i2c SCL pin
//
#define AD7415_PIN_I2CSCK       PA9

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
 
//*****************************************************************************
//
//! \addtogroup AD7415_Power_Down AD7415 Power Down
//! The value can be pass AD7415Init().
//! @{
//  
//*****************************************************************************
  
#define AD7415_MODE_POWER_DOWN  0x80
#define AD7415_MODE_NORMAL      0 
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************  
  
//*****************************************************************************
//
//! \addtogroup AD7415_APIs AD7415 APIs
//! @{
//
//*****************************************************************************

extern void AD7415Init(unsigned long ulRate, unsigned long ulPDEnable);

extern short AD7415TempReadLDC(void);
extern short AD7415TempReadMSB10Bit(void);
extern float AD7415TempReadFDC(void);

extern void AD7415PowerDown(void);
extern void AD7415WakeUp(void);
extern void AD7415OneShotConvert(void);

extern void AD7415FilterEnable(void);
extern void AD7415FilterDisable(void);

extern void AD7415DeInit(void);

//
// If the AD7417 API can not meet your need, you can use the API below operated 
// on the lowlayer.
//
extern short AD7415RegRead(unsigned char ucReg);  
extern void AD7415RegWrite(unsigned char ucReg, short ulValue);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//! @}
//! @}
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif

