//*****************************************************************************
//
//! \file ST7735.h
//! \brief Prototypes for Character LCD ST7735 Driver.
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

#ifndef __ST7735_H__
#define __ST7735_H__

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
//! \addtogroup ST7735S
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ST7735S_Config ST7735S Driver Configurtion
//!
//! \brief Configurtions such as the GPIO Pin used should be set before using
//! this driver.
//!    
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ST7735S_Config_Pins ST7735S Driver Pin Configurtion
//!
//! \brief GPIO Pins Configurtions that communication with the LCD should be 
//! set before using this driver.
//!    
//! @{
//
//***************************************************************************** 
   

#define ST7735_PIN_D7           PA7
#define ST7735_PIN_D6           PA6
#define ST7735_PIN_D5           PA5
#define ST7735_PIN_D4           PA4
#define ST7735_PIN_D3           PA3
#define ST7735_PIN_D2           PA2
#define ST7735_PIN_D1           PA1
#define ST7735_PIN_D0           PA0

#define ST7735_PIN_CS           PC0
#define ST7735_PIN_RS           PC1
#define ST7735_PIN_WR           PC2
#define ST7735_PIN_RD           PC3
#define ST7735_PIN_RST          PC4
#define ST7735_PIN_BACKLIGHT    PE0

//*****************************************************************************
//
//! \addtogroup ST7735S_Config_Function ST7735 Driver Function Configurtion
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
//! - ST7735_CHARACTER_FONT_8X16 - font is 5*8.
//! - ST7735_CHINESE_FONT_16X16 - chinese font is 16*16.
//! - ST7735_CHINESE_FONT_32X32 - chinese font is 32*32.
//! .
//
#define ST7735_CHARACTER_FONT_8X16
  
#define ST7735_CHINESE_FONT_16X16 
  
#define ST7735_CHINESE_FONT_32X32
  
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
//! \addtogroup ST7735S_Panel_Size ST7735S LCD panel size
//! @{
//
//*****************************************************************************

#define LCD_VERTICAL_MAX        160
#define LCD_HORIZONTAL_MAX      128

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ST7735S_Signals ST7735 Signals
//! @{
//
//*****************************************************************************

#define ST7735_CS_DISABLE      1
#define ST7735_CS_ENABLE       0

#define ST7735_RS_COMMAND      0
#define ST7735_RS_DATA         1
 
#define ST7735_WR_LOW          0
#define ST7735_WR_HIGH         1

#define ST7735_RD_READ         0
#define ST7735_RD_WRITE        1

#define ST7735_RD_LOW          0
#define ST7735_RD_HIGH         1

#define ST7735_RST_ENABLE      0
#define ST7735_RST_DISABLE     1

#define ST7735_BACKLIGHT_ON    1
#define ST7735_BACKLIGHT_OFF   0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ST7735S_Exported_APIs  ST7735S Driver APIs
//! \brief API Refrence of ST7735S Driver.
//! @{
//
//*****************************************************************************
extern void ST7735Init(void);

extern void ST7735EntryModeSet(unsigned long ulCursorMoveDirection,
                                unsigned long ulDisplayShift);
extern void ST7735DisplayClear(unsigned long ulColor);
extern void ST7735DisplayRectFill(unsigned short usStartX, unsigned short usStartY, 
                                   unsigned short usEndX, unsigned short usEndY, 
                                   unsigned long ulColor);
extern void ST7735DisplayInversionOn(void);
extern void ST7735DisplayInversionOff(void);
extern void ST7735DisplayOn(void);
extern void ST7735DisplayOff(void);
extern void ST7735BackLightOn(void);
extern void ST7735BackLightOff(void);
extern void ST7735DrawOnePixel(unsigned short usX, unsigned short usY, 
                                  unsigned long ulValue);
extern void ST7735DrawHorizontalLine(unsigned short usStartX, unsigned short usEndX,
                                       unsigned short usY, unsigned long ulColor);
extern void ST7735DrawVerticalLine(unsigned short usX, unsigned short usStartY,
                                     unsigned short usEndY, unsigned long ulColor);
extern void ST7735PutChar8x16(unsigned short usX, unsigned short usY, char c, 
                                unsigned long fColor, unsigned long bColor);
extern void ST7735DisplayString(unsigned short usX, unsigned short usY, const char* pcString,
                                  unsigned long fColor, unsigned long bColor);
extern void ST7735DisplayNum(unsigned short usX, unsigned short usY, unsigned long ulNum,
                               unsigned long fColor, unsigned long bColor);
extern void ST7735DisplayBmp(unsigned short usX, unsigned short usY, unsigned short usSizeX, 
                               unsigned short usSizeY, unsigned char const *Bmp);

extern void ST7735EnterSleepMode(void);
extern void ST7735ExitSleepMode(void);


//
// If the LCD API can not meet your need, you can use the API below operated 
// on the lowlayer.
//
extern void ST7735WriteCmd(unsigned char ucCmd);
extern void ST7735WriteData(unsigned long ucData);
extern void ST7735WritePixelData(unsigned long ulData);
extern unsigned long ST7735Read(unsigned char ucRS);
extern void ST7735SetCurPos(unsigned long ulStartX, unsigned long ulEndX, 
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

#endif //__ST7735_H__
