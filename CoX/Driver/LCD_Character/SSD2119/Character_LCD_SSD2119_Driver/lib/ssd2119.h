//*****************************************************************************
//
//! \file SSD2119.h
//! \brief Prototypes for Character LCD SSD2119 Driver.
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

#ifndef __SSD2119_H__
#define __SSD2119_H__

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
//! \addtogroup SSD2119
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Config SSD2119 Driver Configurtion
//!
//! \brief Configurtions such as the GPIO Pin used should be set before using
//! this driver.
//!    
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Config_Interface SSD2119 Interface Configurtion.
//!
//! \brief Can be set to:
//! - \ref SSD2119_INTERFACE_8080_8BIT - data length is 8 bits, controller is 8080. 
//! - \ref SSD2119_INTERFACE_8080_9BIT - data length is 9 bits, controller is 8080.
//! - \ref SSD2119_INTERFACE_8080_16BIT - data length is 16 bits, controller is 8080.
//! - \ref SSD2119_INTERFACE_8080_18BIT - data length is 18 bits, controller is 8080.
//! - \ref SSD2119_INTERFACE_6800_8BIT - data length is 8 bits, controller is 6800. 
//! - \ref SSD2119_INTERFACE_6800_9BIT - data length is 9 bits, controller is 6800.
//! - \ref SSD2119_INTERFACE_6800_16BIT - data length is 16 bits, controller is 6800.
//! - \ref SSD2119_INTERFACE_6800_18BIT - data length is 18 bits, controller is 6800.
//! - \ref SSD2119_INTERFACE_RGB_6BIT - RGB interface, data length is 6 bits. 
//! - \ref SSD2119_INTERFACE_RGB_18BIT - RGB interface, data length is 18 bits. 
//! - \ref SSD2119_INTERFACE_3SPI - data length is 9 bits.
//! - \ref SSD2119_INTERFACE_4SPI - data length is 8 bits.
//!
//! @{
//
//*****************************************************************************    
#define SSD2119_INTERFACE_8080_8BIT   1
//#define SSD2119_INTERFACE_8080_9BIT   1
//#define SSD2119_INTERFACE_8080_16BIT  1
//#define SSD2119_INTERFACE_8080_18BIT  1
//#define SSD2119_INTERFACE_6800_8BIT   1
//#define SSD2119_INTERFACE_6800_9BIT   1
//#define SSD2119_INTERFACE_6800_16BIT  1
//#define SSD2119_INTERFACE_6800_18BIT  1
//#define SSD2119_INTERFACE_RGB_6BIT    1
//#define SSD2119_INTERFACE_RGB_18BIT   1
//#define SSD2119_INTERFACE_3SPI        1
//#define SSD2119_INTERFACE_4SPI        1
  
#if (defined SSD2119_INTERFACE_8080_8BIT) 
#define SSD2119_INTERFACE_LEN_8BIT
#define SSD2119_INTERFACE_CTL_8080
#elif (defined SSD2119_INTERFACE_8080_9BIT)
#define SSD2119_INTERFACE_LEN_9BIT
#define SSD2119_INTERFACE_CTL_8080
#elif (defined SSD2119_INTERFACE_8080_16BIT)
#define SSD2119_INTERFACE_LEN_16BIT
#define SSD2119_INTERFACE_CTL_8080
#elif (defined SSD2119_INTERFACE_8080_18BIT)
#define SSD2119_INTERFACE_LEN_18BIT
#define SSD2119_INTERFACE_CTL_8080
#elif (defined SSD2119_INTERFACE_6800_8BIT)
#define SSD2119_INTERFACE_LEN_8BIT
#define SSD2119_INTERFACE_CTL_6800
#elif (defined SSD2119_INTERFACE_6800_9BIT)
#define SSD2119_INTERFACE_LEN_9BIT
#define SSD2119_INTERFACE_CTL_6800
#elif (defined SSD2119_INTERFACE_6800_16BIT)
#define SSD2119_INTERFACE_LEN_16BIT
#define SSD2119_INTERFACE_CTL_6800 
#elif (defined SSD2119_INTERFACE_6800_18BIT)
#define SSD2119_INTERFACE_LEN_18BIT
#define SSD2119_INTERFACE_CTL_6800 
#elif (defined SSD2119_INTERFACE_RGB_6BIT) 
#define SSD2119_INTERFACE_18RGB
#define SSD2119_INTERFACE_LEN_6BIT
#elif (defined SSD2119_INTERFACE_RGB_18BIT) 
#define SSD2119_INTERFACE_18RGB
#define SSD2119_INTERFACE_LEN_18BIT
#elif (defined SSD2119_INTERFACE_3SPI)
#define SSD2119_INTERFACE_3_SPI
#elif (defined SSD2119_INTERFACE_4SPI)
#define SSD2119_INTERFACE_4_SPI  
#endif
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Config_Pins SSD2119 Driver Pin Configurtion
//!
//! \brief GPIO Pins Configurtions that communication with the LCD should be 
//! set before using this driver.
//!    
//! @{
//
//***************************************************************************** 
   
#if ((defined SSD2119_INTERFACE_LEN_8BIT) || (defined SSD2119_INTERFACE_LEN_9BIT)) 
#define SSD2119_PIN_D17         PD7
#define SSD2119_PIN_D16         PD6
#define SSD2119_PIN_D15         PD5
#define SSD2119_PIN_D14         PD4
#define SSD2119_PIN_D13         PD3
#define SSD2119_PIN_D12         PD2
#define SSD2119_PIN_D11         PD1
#define SSD2119_PIN_D10         PD0
  
#ifdef SSD2119_INTERFACE_LEN_9BIT
#define SSD2119_PIN_D9          PD0
#endif 
  
#define SSD2119_PIN_D8          PD7
#define SSD2119_PIN_D7          PD6
#define SSD2119_PIN_D6          PD5
#define SSD2119_PIN_D5          PD4
#define SSD2119_PIN_D4          PD3
#define SSD2119_PIN_D3          PD2
#define SSD2119_PIN_D2          PD1
#define SSD2119_PIN_D1          PD0
#define SSD2119_PIN_D0          PD0

#define SSD2119_PIN_DC          PH7
#define SSD2119_PIN_CS          PF3
  
#ifdef SSD2119_INTERFACE_CTL_6800
#define SSD2119_PIN_RW          PH6
#define SSD2119_PIN_E           PB5
#endif 
#ifdef SSD2119_INTERFACE_CTL_8080
#define SSD2119_PIN_WR          PH6
#define SSD2119_PIN_RD          PB5
#endif  
  
#elif ((defined SSD2119_INTERFACE_LEN_16BIT) || (defined SSD2119_INTERFAC_LEN_18BIT))
#define SSD2119_PIN_D17         PD7
#define SSD2119_PIN_D16         PD6
#define SSD2119_PIN_D15         PD5
#define SSD2119_PIN_D14         PD4
#define SSD2119_PIN_D13         PD3
#define SSD2119_PIN_D12         PD2
#define SSD2119_PIN_D11         PD1
#define SSD2119_PIN_D10         PD0
#define SSD2119_PIN_D8          PD7
#define SSD2119_PIN_D7          PD6
#define SSD2119_PIN_D6          PD5
#define SSD2119_PIN_D5          PD4
#define SSD2119_PIN_D4          PD3
#define SSD2119_PIN_D3          PD2
#define SSD2119_PIN_D2          PD1
#define SSD2119_PIN_D1          PD0

#ifdef SSD2119_INTERFAC_LEN_18BIT
#define SSD2119_PIN_D0          PD0
#define SSD2119_PIN_D0          PD0
#endif
  
#define SSD2119_PIN_DC          PH7
#define SSD2119_PIN_CS          PF3
  
#ifdef SSD2119_INTERFACE_6800
#define SSD2119_PIN_RW          PH6
#define SSD2119_PIN_E           PB5
#endif  
#ifdef SSD2119_INTERFACE_8080
#define SSD2119_PIN_WR          PH6
#define SSD2119_PIN_RD          PB5
#endif 
  
#elif (defined SSD2119_INTERFACE_18RGB)
#define SSD2119_PIN_D17         PD7
#define SSD2119_PIN_D16         PD6
#define SSD2119_PIN_D15         PD5
#define SSD2119_PIN_D14         PD4
#define SSD2119_PIN_D13         PD3
#define SSD2119_PIN_D12         PD2
#define SSD2119_PIN_D11         PD1
#define SSD2119_PIN_D10         PD0
#define SSD2119_PIN_D8          PD7
#define SSD2119_PIN_D7          PD6
#define SSD2119_PIN_D6          PD5
#define SSD2119_PIN_D5          PD4
#define SSD2119_PIN_D4          PD3
#define SSD2119_PIN_D3          PD2
#define SSD2119_PIN_D2          PD1
#define SSD2119_PIN_D1          PD0
#define SSD2119_PIN_D0          PD0
 
#define SSD2119_HSYNC
#define SSD2119_VSYNC 
#define SSD2119_DOTCLK
#define SSD2119_DEN
  
#elif (defined SSD2119_INTERFACE_3_SPI)
#define SSD2119_SPICLK          PF2
#define SSD2119_SPICS           PF3
#define SSD2119_SPIRX           PF4
#define SSD2119_SPITX           PF5
#define SSD2119_SPIBase         xSPI1_BASE
  
#elif (defined SSD2119_INTERFACE_4_SPI)
#define SSD2119_PIN_DC          PH7
#define SSD2119_SPICLK          PF2
#define SSD2119_SPICS           PF3
#define SSD2119_SPIRX           PF4
#define SSD2119_SPITX           PF5
#define SSD2119_SPIBase         xSPI1_BASE

#endif
  
#define SSD2119_PIN_RST         PB7
#define SSD2119_PIN_BACKLIGHT   PB6

//*****************************************************************************
//
//! \addtogroup SSD2119_Config_Function SSD2119 Driver Function Configurtion
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
//! - SSD2119_CHARACTER_FONT_8X16 - font is 5*8.
//! - SSD2119_CHINESE_FONT_16X16 - chinese font is 16*16.
//! - SSD2119_CHINESE_FONT_32X32 - chinese font is 32*32.
//! .
//
#define SSD2119_CHARACTER_FONT_8X16
  
#define SSD2119_CHINESE_FONT_16X16 
  
#define SSD2119_CHINESE_FONT_32X32

//
//! The LCD Display Color Mode.
//!
//! Can be set to:
//! - \ref SSD2119_COLOR_MODE_65K - 65K-color.
//! - \ref SSD2119_COLOR_MODE_262K - 262K-color.
//! .
//
#define SSD2119_COLOR_MODE      SSD2119_COLOR_MODE_65K
  
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
//! \addtogroup SSD2119_Panel_Size SSD2119 LCD panel size
//! @{
//
//*****************************************************************************

#define LCD_VERTICAL_MAX        240
#define LCD_HORIZONTAL_MAX      320

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Signals SSD2119 Signals
//! @{
//
//*****************************************************************************

#define SSD2119_CS_DISABLE      1
#define SSD2119_CS_ENABLE       0

#define SSD2119_DC_COMMAND      0
#define SSD2119_DC_DATA         1

#define SSD2119_6800_RW_WRITE   0
#define SSD2119_6800_RW_READ    1

#define SSD2119_6800_E_ENABLE   1
#define SSD2119_6800_E_DISABLE  0
 
#define SSD2119_8080_WR_ENABLE  0
#define SSD2119_8080_WR_DISABLE 1

#define SSD2119_8080_RD_ENABLE  0
#define SSD2119_8080_RD_DISABLE 1

#define SSD2119_RST_ENABLE      0
#define SSD2119_RST_DISABLE     1

#define SSD2119_NORMAL_REG      0
#define SSD2119_GRAM_REG        1 

#define SSD2119_BACKLIGHT_ON    1
#define SSD2119_BACKLIGHT_OFF   0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Config_Function SSD2119 Driver Function Configurtion
//!
//! \brief Configure the LCD screen orientations, it have four different mode.
//!    
//! @{
//
//*****************************************************************************

//
//! These can also be imagined in terms of screen rotation; if portrait mode is
//! 0 degrees of screen rotation, landscape is 90 degrees of counter-clockwise
//! rotation, portrait flip is 180 degrees of rotation, and landscape flip is
//! 270 degress of counter-clockwise rotation.
//!
//! If no screen orientation is selected, "landscape flip" mode will be used.
//
#if ! defined(PORTRAIT) && ! defined(PORTRAIT_FLIP) && \
    ! defined(LANDSCAPE) && ! defined(LANDSCAPE_FLIP)
#define LANDSCAPE_FLIP
#endif

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup SSD2119_Config_Function SSD2119 Driver Function Configurtion
//!
//! \brief Various definitions controlling coordinate space mapping and drawing
//!        direction in the four supported orientations.
//!    
//! @{
//
//*****************************************************************************
      
//
//! PORTRAIT - The screen is taller than it is wide, and the flex connector is
//!          on the left of the display.  This is selected by defining PORTRAIT.
//                    
#ifdef PORTRAIT
#define HORIZ_DIRECTION         0x28
#define VERT_DIRECTION          0x20
#define MAPPED_X(x, y)          (319 - (y))
#define MAPPED_Y(x, y)          (x)
#endif

//
//! LANDSCAPE - The screen is wider than it is tall, and the flex connector is
//!       on the bottom of the display.  This is selected by defining LANDSCAPE. 
//                   
#ifdef LANDSCAPE
#define HORIZ_DIRECTION         0x00
#define VERT_DIRECTION          0x08
#define MAPPED_X(x, y)          (319 - (x))
#define MAPPED_Y(x, y)          (239 - (y))
#endif
      
//
//! Portrait flip - The screen is taller than it is wide, and the flex
//!                   connector is on the right of the display.  This is
//!                   selected by defining PORTRAIT_FLIP.      
//
#ifdef PORTRAIT_FLIP
#define HORIZ_DIRECTION         0x18
#define VERT_DIRECTION          0x10
#define MAPPED_X(x, y)          (y)
#define MAPPED_Y(x, y)          (239 - (x))
#endif
      
//
//! Landscape flip - The screen is wider than it is tall, and the flex
//!                    connector is on the top of the display.  This is
//!                    selected by defining LANDSCAPE_FLIP.      
//
#ifdef LANDSCAPE_FLIP
#define HORIZ_DIRECTION         0x30
#define VERT_DIRECTION          0x38
#define MAPPED_X(x, y)          (x)
#define MAPPED_Y(x, y)          (y)
#endif

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Color_Mode Display Color Mode
//!
//! \brief SSD2119 Display Color Mode setting. 
//! - \ref SSD2119_COLOR_MODE_65K
//! - \ref SSD2119_COLOR_MODE_262K
//!    
//! @{
//
//*****************************************************************************

#define SSD2119_COLOR_MODE_65K  1
#define SSD2119_COLOR_MODE_262K 2 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD2119_Exported_APIs  SSD2119 Driver APIs
//! \brief API Refrence of SSD2119 Driver.
//! @{
//
//*****************************************************************************
extern void SSD2119Init(void);

extern void SSD2119EntryModeSet(unsigned long ulCursorMoveDirection,
                                unsigned long ulDisplayShift);
extern void SSD2119DisplayClear(unsigned long ulColor);
extern void SSD2119DisplayRectFill(unsigned short usStartX, unsigned short usStartY, 
                                   unsigned short usEndX, unsigned short usEndY, 
                                   unsigned long ulColor);

extern void SSD2119BacklightOn(void);
extern void SSD2119BacklightOff(void);
extern void SSD2119DrawOnePixel(unsigned short usX, unsigned short usY, 
                                  unsigned long ulValue);
extern void SSD2119PixelDrawMultiple(unsigned long lX, unsigned long lY, 
                         unsigned long lX0, unsigned long lCount,
                         unsigned long lBPP,
                         const unsigned char *pucData,
                         const unsigned char *pucPalette);
extern void SSD2119DrawHorizontalLine(unsigned short usStartX, unsigned short usEndX,
                                       unsigned short usY, unsigned long ulColor);
extern void SSD2119DrawVerticalLine(unsigned short usX, unsigned short usStartY,
                                     unsigned short usEndY, unsigned long ulColor);
extern void SSD2119PutChar8x16(unsigned short usX, unsigned short usY, char c, 
                                unsigned long fColor, unsigned long bColor);
extern void SSD2119DisplayString(unsigned short usX, unsigned short usY, const char* pcString,
                                  unsigned long fColor, unsigned long bColor);
extern void SSD2119DisplayNum(unsigned short usX, unsigned short usY, unsigned long ulNum,
                               unsigned long fColor, unsigned long bColor);
extern void SSD2119DisplayBmp(unsigned short usX, unsigned short usY, unsigned short usSizeX, 
                               unsigned short usSizeY, unsigned char const *Bmp);

extern void SSD2119EnterSleepMode(void);
extern void SSD2119ExitSleepMode(void);


//
// If the LCD API can not meet your need, you can use the API below operated 
// on the lowlayer.
//
extern void SSD2119WriteCmd(unsigned char ucCmd);
extern void SSD2119WriteData(unsigned long ucData);
extern void SSD2119WritePixelData(unsigned long ulData);
extern unsigned long SSD2119Read(unsigned char ucDC);
extern void SSD2119SetCurPos(unsigned long ulStartX, unsigned long ulEndX, 
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

#endif //__SSD2119_H__
