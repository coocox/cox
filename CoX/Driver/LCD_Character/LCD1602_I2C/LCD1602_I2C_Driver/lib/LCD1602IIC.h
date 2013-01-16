//*****************************************************************************
//
//! \file LCD1602IIC.h
//! \brief Prototypes for Character LCD HD44780 Driver.
//! \version 2.1.1.0
//! \date 1/15/2013
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox
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

#ifndef __LCD1602IIC_H__
#define __LCD1602IIC_H__

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
//! \addtogroup LCD
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LCD_Character
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LCD1602_With_PCA8574_I2C
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LCD1602_I2C_Config LCD1602_I2C Driver Configuration
//!
//! \brief Configurations such as the GPIO Pin used should be set before using
//! this driver.
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LCD1602_I2C_Config_Pins LCD1602_I2C Driver Pin Configuration
//!
//! \brief GPIO Pins Configurations that communication with the LCD should be
//! set before using this driver.
//!
//! @{
//
//*****************************************************************************

//
//! Select hardware IIC or software IIC
//
#define USE_SOFTWARE_IIC
//#define USE_HARDWARE_IIC

#define LCD1602_IIC_PIN_SCL     PB6
#define LCD1602_IIC_PIN_SDA     PB7

#ifdef USE_HARDWARE_IIC
#define LCD1602_IIC_SCL I2C1SCK
#define LCD1602_IIC_SDA I2C1SDA
#define LCD1602_IIC_PORT I2C1_BASE
#endif
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LCD1602_I2C_Config_Module LCD1602_I2C Configuration structure
//!
//! \brief Configure the LCD module. such as 1602, 1601, 20*2.
//! set before using this driver.
//!
//! @{
//
//*****************************************************************************
typedef struct LCD1602
{
    unsigned char ucDevAddr;            //device address
    unsigned char ucDispalyFunction;    //display function configuration data
    unsigned char ucDisplayControl;     //display control configuration data
    unsigned char ucDisplayMode;        //display mode configuration data
    unsigned char ucNumCols;            //characters one line can display
    unsigned char ucNumRows;            //lines LCD can display
    unsigned char ucBackLightEn;        //LCD back light configuration data
}LCD1602Conf;
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LCD1602_I2C_Exported_APIs  LCD1602_I2C Driver APIs
//! \brief API Refrence of LCD1602IIC Driver.
//! @{
//
//*****************************************************************************
extern void LCD1602Clear(void);
extern void LCD1602Home(void);
extern void LCD1602DisplayOff(void);
extern void LCD1602DisplayOn(void);
extern void LCD1602BlinkOff(void);
extern void LCD1602BlinkOn(void);
extern void LCD1602CursorOff(void);
extern void LCD1602CursorOn(void);
extern void LCD1602ScrollDisplayLeft(void);
extern void LCD1602ScrollDisplayRight(void);
extern void LCD1602BacklightOff(void);
extern void LCD1602BacklightOn(void);
extern void LCD1602AutoScrollOff(void);
extern void LCD1602AutoScrollOn(void);
extern void LCD1602CreateChar(unsigned char ucLocation, unsigned char ucCharMap[]);
extern void LCD1602Init(unsigned long ulCLK);
extern void LCD1602SetCursor(unsigned char ucRow, unsigned char ucCol);
extern void LCD1602ShowChar(unsigned char ucRow, unsigned char ucCol, char ch);
extern void LCD1602PrintString(unsigned char ucRow, unsigned char ucCol, char *pStr);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! @}
//! @}
//! @}
//! @}
//! @}
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //__HD44780_H__
