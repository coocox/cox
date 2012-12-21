//*****************************************************************************
//
//! \file bh1750fvi.h
//! \brief Prototypes for the BH1750FVI Driver.
//! \version V2.2.1.0
//! \date 7/17/2012
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
#ifndef __BH1750FVI_H__
#define __BH1750FVI_H__

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
//! \addtogroup Light_Sensor
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup BH1750FVI
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup BH1750FVI_I2C_Set BH1750FVI I2C and Pin Configuration
//! \brief Values can be used in BH1750Init(),Define I2Cx as a port connecting 
//! BH1750FVI which can be configured,when you use a different I2C port you must
//!  configure them again.
//! @{
//
//*****************************************************************************

#define BH1750_PIN_I2C_CLK      PD5
#define BH1750_I2C_CLK          I2C0SCK

#define BH1750_PIN_I2C_SDA      PD4
#define BH1750_I2C_SDA          I2C0SDA

#define BH1750_PIN_ADDR         PC3
#define BH1750_PIN_DVI          PC0
  
#define BH1750_PIN_I2C_PORT     I2C0_BASE

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup BH1750FVI_Exported_APIs  BH1750FVI Driver APIs
//! \brief API Refrence of BH1750FVI Driver.
//! @{
//
//*****************************************************************************

extern void BH1750Init(unsigned long ulI2cClock);
extern void BH1750DeInit(void);
extern void BH1750Configure(unsigned char ucMode);
extern short BH1750LightRead(void);
extern void BH1750SensitivityAdjust(unsigned char ucMeasurementTime);

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

#endif //__BH1750FVI_H__
