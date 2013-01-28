//*****************************************************************************
//
//! \file ili9341.h
//! \brief Prototypes for Character LCD ILI9341 Driver.
//! \version 2.1.1.0
//! \date 10/18/2011
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2011, CooCoX 
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

#ifndef __ILI9341_H__
#define __ILI9341_H__

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
//! \addtogroup ILI9341S
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ILI9341S_Config ILI9341S Driver Configurtion
//!
//! \brief Configurtions such as the GPIO Pin used should be set before using
//! this driver.
//!    
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ILI9341S_Config_Pins ILI9341S Driver Pin Configurtion
//!
//! \brief GPIO Pins Configurtions that communication with the LCD should be 
//! set before using this driver.
//!    
//! @{
//
//***************************************************************************** 
   

#define ILI9341_PIN_D7          PA7
#define ILI9341_PIN_D6          PA6
#define ILI9341_PIN_D5          PA5
#define ILI9341_PIN_D4          PA4
#define ILI9341_PIN_D3          PA3
#define ILI9341_PIN_D2          PA2
#define ILI9341_PIN_D1          PA1
#define ILI9341_PIN_D0          PA0

#define ILI9341_PIN_CS          PC0
#define ILI9341_PIN_RS          PC1
#define ILI9341_PIN_WR          PC2
#define ILI9341_PIN_RD          PC3
#define ILI9341_PIN_RST         PC4
#define ILI9341_PIN_BACKLIGHT   PC5

//*****************************************************************************
//
//! \addtogroup ILI9341S_Config_Function ILI9341 Driver Function Configurtion
//!
//! \brief Configure the TFT character font, interface data length.
//!    
//! @{
//
//*****************************************************************************
//
//! The TFT display character font.
//!
//! Can be set to:
//! - ILI9341_CHARACTER_FONT_8X16 - font is 5*8.
//! - ILI9341_CHINESE_FONT_16X16 - chinese font is 16*16.
//! - ILI9341_CHINESE_FONT_32X32 - chinese font is 32*32.
//! .
//
#define ILI9341_CHARACTER_FONT_8X16
  
#define ILI9341_CHINESE_FONT_16X16 
  
#define ILI9341_CHINESE_FONT_32X32
  
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
//! \addtogroup ILI9341S_Panel_Size ILI9341S LCD panel size
//! @{
//
//*****************************************************************************

#define LCD_VERTICAL_MAX        320
#define LCD_HORIZONTAL_MAX      240

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ILI9341S_Signals ILI9341 Signals
//! @{
//
//*****************************************************************************

#define ILI9341_CS_DISABLE      1
#define ILI9341_CS_ENABLE       0

#define ILI9341_RS_COMMAND      0
#define ILI9341_RS_DATA         1
 
#define ILI9341_WR_LOW          0
#define ILI9341_WR_HIGH         1

#define ILI9341_RD_READ         0
#define ILI9341_RD_WRITE        1

#define ILI9341_RD_LOW          0
#define ILI9341_RD_HIGH         1

#define ILI9341_RST_ENABLE      0
#define ILI9341_RST_DISABLE     1

#define ILI9341_BACKLIGHT_ON    1
#define ILI9341_BACKLIGHT_OFF   0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ILI9341S_Exported_APIs  ILI9341S Driver APIs
//! \brief API Refrence of ILI9341S Driver.
//! @{
//
//*****************************************************************************
extern void ILI9341Init(void);

extern void ILI9341EntryModeSet(unsigned long ulCursorMoveDirection,
                                unsigned long ulDisplayShift);
extern void ILI9341DisplayClear(unsigned long ulColor);
extern void ILI9341DisplayRectFill(unsigned short usStartX, unsigned short usStartY, 
                                   unsigned short usEndX, unsigned short usEndY, 
                                   unsigned long ulColor);
extern void ILI9341DisplayInversionOn(void);
extern void ILI9341DisplayInversionOff(void);
extern void ILI9341DisplayOn(void);
extern void ILI9341DisplayOff(void);
extern void ILI9341BackLightOn(void);
extern void ILI9341BackLightOff(void);
extern void ILI9341DrawOnePixel(unsigned short usX, unsigned short usY, 
                                  unsigned long ulValue);
extern void ILI9341DrawHorizontalLine(unsigned short usStartX, unsigned short usEndX,
                                       unsigned short usY, unsigned long ulColor);
extern void ILI9341DrawVerticalLine(unsigned short usX, unsigned short usStartY,
                                     unsigned short usEndY, unsigned long ulColor);
extern void ILI9341PutChar8x16(unsigned short usX, unsigned short usY, char c, 
                                unsigned long fColor, unsigned long bColor);
extern void ILI9341DisplayString(unsigned short usX, unsigned short usY, const char* pcString,
                                  unsigned long fColor, unsigned long bColor);
extern void ILI9341DisplayNum(unsigned short usX, unsigned short usY, unsigned long ulNum,
                               unsigned long fColor, unsigned long bColor);
extern void ILI9341DisplayBmp(unsigned short usX, unsigned short usY, unsigned short usSizeX, 
                               unsigned short usSizeY, unsigned char const *Bmp);

extern void ILI9341EnterSleepMode(void);
extern void ILI9341ExitSleepMode(void);


//
// If the LCD API can not meet your need, you can use the API below operated 
// on the lowlayer.
//
extern void ILI9341WriteCmd(unsigned char ucCmd);
extern void ILI9341WriteData(unsigned long ucData);
extern void ILI9341Write8Bit(unsigned char ucData);
extern void ILI9341WritePixelData(unsigned long ulData);
extern unsigned long ILI9341Read(unsigned char ucRS);
extern void ILI9341SetCurPos(unsigned long ulStartX, unsigned long ulEndX, 
                  unsigned long ulStartY, unsigned long ulEndY);

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
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //__ILI9341_H__
