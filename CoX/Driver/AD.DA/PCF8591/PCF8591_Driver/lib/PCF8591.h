//*****************************************************************************
//
//! \file PCF8591.h
//! \brief header file of Driver for PCF8591
//! \version V2.1.1.0
//! \date 1/9/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox All rights reserved.
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

#ifndef  __PCF8591_H__
#define __PCF8591_H__

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//! \addtogroup ADDA
//! @{
//! \addtogroup ADDA_I2C
//! @{
//! \addtogroup PCF8591
//! @{
//! \addtogroup PCF8591_Driver
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup PCF8591_PIN_CONFIG
//! PCF8591  PIN Configuration
//! @{
//
//*****************************************************************************
#define PCF8591_ADDRESS                     0x48

#define PCF8591_I2C_PORT                    I2C0_BASE
#define I2C_SDA                             I2C0SDA
#define I2C_SCK                             I2C0SCK
#define PCF8591_SDA_PIN                     PA8
#define PCF8591_SCL_PIN                     PA9

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup PCF8591_CONTROL_CONFIG
//! PCF8591  control byte configuration
//! @{
//
//*****************************************************************************

#define PCF8591_ANALOG_OUTPUT_ENABLE	0x40
#define PCF8591_ANALOG_OUTPUT_DISABLE	0x00

#define PCF8591_INPUT_FOUR_SINGLE               0x00
#define PCF8591_INPUT_THREE_DIF			0x10
#define PCF8591_INPUT_MIXED                     0x20
#define PCF8591_INPUT_TWO_DIF                   0x30

#define PCF8591__INPUT_INC_ENABLE		0x04
#define PCF8591__INPUT_INC_DISABLE		0x00

#define PCF8591_CHANNEL_0                       0x00
#define PCF8591_CHANNEL_1                       0x01
#define PCF8591_CHANNEL_2                       0x02
#define PCF8591_CHANNEL_3                       0x03

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup COX_PCF8591_Exported_APIs
//! @{
//
//*****************************************************************************
extern void PCF8591_Init(unsigned long ulRate);
extern unsigned char  PCF8591_DA_OUT(unsigned char* data,
				unsigned long data_len);
extern void  PCF8591_AD_Trans(char* data, unsigned long data_len,
				unsigned char mode);
extern void  PCF8591_AD_Vol(float* vol, char* data,
				unsigned long data_len );
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



#endif // __HW_PCF8591_H__
