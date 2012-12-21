//*****************************************************************************
//
//! \file STMPE811.h
//! \brief Prototypes for the M24Cxx Driver.
//! \version V2.1.1.0
//! \date 7/5/2012
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
#ifndef __STMPE811_H__
#define __STMPE811_H__

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
//! \addtogroup Sensor
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup I2C_TouchSensor
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STMPE811
//! @{
//
//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
//! \addtogroup STMPE811_Driver
//! @{
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup STMPE811_Hardware_Config
//! @{
//
//*****************************************************************************

//
//! Define IIC as a port connecting STMPE811 which can be configured
//
#define	STMPE811_PIN_I2C_SCK	PB8
#define	STMPE811_I2C_SCK	I2C1SCK
#define	STMPE811_PIN_I2C_SDA	PB9
#define	STMPE811_I2C_SDA	I2C1SDA
#define STMPE811_PIN_I2C_PORT   I2C1_BASE  
#define STMPE811_I2C_GPIO       SYSCTL_PERIPH_IOPB
  
//
//! Define INT pin.
//
#define STMPE811_INT_PORT       GPIOB_BASE
#define STMPE811_INT_GPIO       xGPIO_PIN_1
  
//
//! Define STMPE811 I2C slave address
//
#define STMPE811_ADDRESS        0x82
//#define STMPE811_ADDRESS        0x88

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup COX_STMPE811_Exported_APIs
//! @{
//
//*****************************************************************************
extern void STMPE811Init(void);
extern void STMPE811Write(unsigned char ucReg, unsigned char ucNum, 
                          unsigned long ulVal);
extern void STMPE811Read(unsigned char ucReg, unsigned char ucNum, 
                         unsigned char* pucBuffer);
extern void STMPE811InitConfig(void);
extern unsigned long STMPE811IntCallback(void *pvCBData, unsigned long ulEvent,
                        unsigned long ulMsgParam,void *pvMsgData);
extern void STMPE811SetOperatingMode(unsigned long ulMode);
extern unsigned STMPE811GetINTStatus(void);
extern void STMPE811INTClear(unsigned char ucVal);
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