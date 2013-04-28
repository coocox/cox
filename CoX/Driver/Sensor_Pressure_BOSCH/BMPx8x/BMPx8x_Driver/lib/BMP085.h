//*****************************************************************************
//
//! \file BMP085.h
//! \brief Prototypes for the BMP085/BMP180 Driver.
//! \version 0.0.1
//! \date 4/24/2013
//! \author  CooCox
//!
//! \copy
//!
//! Copyright (c)  2013, CooCox
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
#ifndef __BMP085_H__
#define __BMP085_H__

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
//! \addtogroup Pressure_Sensor
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup BMP085_and_BMP180
//! @{
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup BMP085_Driver_Single
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup BMP085_Config BMP085 Driver Predefines
//! \brief This part defines the slave address and register address of BMP085.
//! @{
//
//*****************************************************************************

//! BMP085 slave address. Do not contain W/R bit
#define BMP085_ADDR                    0x77

#define BMP085_ID                      0x55

//! BMP085 EEPROM registers
#define BMP085_REG_AC1                 0xAA
#define BMP085_REG_AC2                 0xAC
#define BMP085_REG_AC3                 0xAE
#define BMP085_REG_AC4                 0xB0
#define BMP085_REG_AC5                 0xB2
#define BMP085_REG_AC6                 0xB4
#define BMP085_REG_B1                  0xB6
#define BMP085_REG_B2                  0xB8
#define BMP085_REG_MB                  0xBA
#define BMP085_REG_MC                  0xBC
#define BMP085_REG_MD                  0xBE
#define BMP085_REG_ID                  0xD0
//! BMP085 read control register
#define BMP085_REG_READ                0xF6
//! BMP085 temperature register
#define BMP085_REG_TEMP                0x2E
//! BMP085 pressure over-sample register
#define BMP085_REG_PRES_OS0            0x34
#define BMP085_REG_PRES_OS1            0x74
#define BMP085_REG_PRES_OS2            0xB4
#define BMP085_REG_PRES_OS3            0xF4
//! BMP085 over-sample level
#define BMP085_OSS_0                   0
#define BMP085_OSS_1                   1
#define BMP085_OSS_2                   2
#define BMP085_OSS_3                   3
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup BMP085_User_Config
//! \brief User modify filed(according to the hardware connection)
//! @{
//
//*****************************************************************************

//! Define this macro to enable hardware I2C or the driver will use software I2C
//! (GPIO simulation). If you don't use hardware I2C disable this define
#define BMP085_USE_HARDWARE_I2C

//! I2C pins define
#define BMP085_I2C_PIN_SCL             PB6
#define BMP085_I2C_PIN_SDA             PB7

#ifdef BMP085_USE_HARDWARE_I2C
#define BMP085_I2C_SCL                 I2C1SCK
#define BMP085_I2C_SDA                 I2C1SDA
#define BMP085_I2C_PORT                I2C1_BASE
#endif
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup BMP085_Calibratation_Struct
//! @{
//
//*****************************************************************************
typedef struct
{
	short ac1;
	short ac2;
	short ac3;
	unsigned short ac4;
	unsigned short ac5;
	unsigned short ac6;
	short b1;
	short b2;
	short mb;
	short mc;
	short md;
}BMP085CalibratationStruct;
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup BMP085_Exported_APIs
//! @{
//
//*****************************************************************************

//
//! BMP085 Initialization function
//! ulBitRate specifies the I2C communication bit rate
//
extern unsigned long BMP085Init(unsigned long ulBitRate);

extern long BMP085GetTemperature(void);

//
//! Get pressure
//! oss specifies the over-sample rate (BMP085_OSS_0 ~ BMP085_OSS_3)
//
extern long BMP085GetPressure(unsigned char oss);
extern long BMP085GetAltitude(void);
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
