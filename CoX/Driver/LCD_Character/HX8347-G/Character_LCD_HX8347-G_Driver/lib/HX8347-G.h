//*****************************************************************************
//
//! \file HX8347-G.h
//! \brief Prototypes for Character LCD HX8347-G Driver.
//! \version 1.0.0
//! \date 6/26/2012
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
//
//*****************************************************************************

#ifndef __HX8347_H__
#define __HX8347_H__

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
//! \addtogroup LCD_Graphic
//! @{
//
//*****************************************************************************    
    
//*****************************************************************************
//
//! \addtogroup HX8347-G
//! @{
//
//*****************************************************************************
//*****************************************************************************
//! \addtogroup HX8347-G_Driver_Single
//! @{
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup HX8347_Color_coded HX8347 Color coded
//!
//! \brief GLCD is coded:   15..11 red, 10..5 green, 4..0 blue  (unsigned short)   
//! GLCD_R5, GLCD_G6, GLCD_B5. 
//!    
//! @{
//
//*****************************************************************************    
#define Black                   0x0000      
#define Navy                    0x000F
#define DarkGreen               0x03E0
#define DarkCyan                0x03EF
#define Maroon                  0x7800
#define Purple                  0x780F
#define Olive                   0x7BE0
#define LightGrey               0xC618
#define DarkGrey                0x7BEF
#define Blue                    0x001F
#define Green                   0x07E0
#define Cyan                    0x07FF
#define Red                     0xF800
#define Magenta                 0xF81F
#define Yellow                  0xFFE0
#define White                   0xFFFF
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
//*****************************************************************************
//
//! \addtogroup HX8347_Character_Setting HX8347 Character setting
//!
//! \brief set character size(in pixels).   
//!    
//! @{
//
//*****************************************************************************    
#define CHAR_H                  24
#define CHAR_W                  16
//*****************************************************************************
//
//! @}
//
//*****************************************************************************  
//*****************************************************************************
//! \addtogroup HX8347_Hardware_Config
//! @{
//
//*****************************************************************************

//
//! Define SPI3 as a port connecting HX8347 which can be configured
//
#define	HX8347_PIN_SPI_SCK	PC10
#define	HX8347_SPI_SCK		SPI3SCK
#define	HX8347_PIN_SPI_MISO	PC11
#define	HX8347_SPI_MISO		SPI3MISO
#define	HX8347_PIN_SPI_MOSI	PC12
#define	HX8347_SPI_MOSI		SPI3MOSI
#define HX8347_PIN_SPI_PORT     SPI3_BASE  
#define HX8347_SPI_GPIO         SYSCTL_PERIPH_IOPC 
#define HX8347_SPI_GPIO_CS      SYSCTL_PERIPH_IOPB
//*****************************************************************************
//
//! @}
//
//*****************************************************************************  
//*****************************************************************************
//
//! \addtogroup HX8347_Config_Module HX8347 Driver LCD Moudle Configurtion
//!
//! \brief Configure the LCD moudle.  
//! set before using this driver.
//!    
//! @{
//
//*****************************************************************************
//
//! The Screen Width.
//
#define HX8347_DISPLAY_WIDTH    320

//
//! The Screen Hight.
// 
#define HX8347_DISPLAY_HEIGHT   240
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup HX8347_Config_Pins HX8347 Driver Pin Configurtion
//!
//! \brief GPIO Pins Configurtions that communication with the LCD should be 
//! set before using this driver.
//!    
//! @{
//
//*****************************************************************************    
#define HX8347_PIN_CS           PB2
#define HX8347_GPIO_PIN_CS      GPIO_PIN_2
#define HX8347_PIN_BL_CN        PB0
#define HX8347_GPIO_BL_CN       GPIO_PIN_0
#define HX8347_PIN_PORT         GPIOB_BASE
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

  //*****************************************************************************
//
//! \addtogroup HX8347_Signals HX8347 Signals
//! @{
//
//*****************************************************************************
#define HX8347_CS_DISABLE       0
#define HX8347_CS_ENABLE        1

#define HX8347_BL_CN_ENABLE     1
#define HX8347_BL_CN_DISABLE    1



//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup HX8347_Config_Interface_ Interface start byte setting
//!
//! \brief HX8347 Interface start byte setting. 
//!    
//! @{
//
//*****************************************************************************
//
//! The six upper bits of interface start byte is device ID code,it must be set
//! to "011100"
//
#define HX8347_SPI_START        (0x70)
//
//! WR bit 1 within start
//
#define HX8347_SPI_RD           (0x01)   
//
//! WR bit 0 within start
// 
#define HX8347_SPI_WR           (0x00)
//
//! RS bit 1 within start byte
// 
#define HX8347_SPI_DATA         (0x02)
//
//! RS bit 0 within start byte
// 
#define HX8347_SPI_INDEX        (0x00)
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
//*****************************************************************************
//
//! \addtogroup COX_HX8347_Exported_APIs
//! @{
//
//*****************************************************************************
extern void HX8347Init(unsigned long ulSpiClock);
extern void HX8347WriteCmd(unsigned char ucReg);
extern void HX8347WriteDat(unsigned short ucVal);
extern void HX8347WriteReg(unsigned char ucReg, unsigned short ucVal);
extern void HX8347SetWindow(unsigned long ulX, unsigned long ulY, unsigned long ulW, unsigned long ulH);
extern void HX8347SetWindowMax(void);
extern void HX8347LCDClear(unsigned short usColor);
extern void HX8347WriteDataStart(void);
extern void HX8347WriteDataOnly(unsigned short usC);
extern void HX8347WriteDataStop(void);
extern void HX8347DisplayBmp (unsigned long ulX, unsigned long ulY, 
                                                 unsigned long ulW,
                                                 unsigned long ulH,
                                                 unsigned char *pucBmp);
extern void HX8347Bargraph(unsigned long ulX, unsigned long ulY, 
                                              unsigned long ulW,
                                              unsigned long ulH,
                                              unsigned long ulVal);
extern void HX8347SetTextColor(unsigned short usColor);
extern void HX8347SetBackColor(unsigned short usColor);
extern void HX8347DrawChar(unsigned long ulX, unsigned long ulY, 
                                               unsigned short *psC);
extern void HX8347DisplayChar(unsigned long ulLine, unsigned long ulCol, 
                              unsigned char ucC);
extern void HX8347DisplayString(unsigned long ulLine, unsigned long ulCol, 
                                          unsigned char *pucStr);
extern void HX8347ClearLine(unsigned long ulLine);
extern unsigned short HX8347ReadReg(unsigned char ucReg);
extern unsigned short HX8347ReadData(void);
extern void HX8347DrawPixel(unsigned long ulX, unsigned long ulY);
extern void HX8347DisplayN(unsigned char ucLine, unsigned char ulCol, 
                     unsigned long n);
extern void HX8347DisplayOn(void);
extern void HX8347DisplayOff(void);
extern void HX8347DrawChinese(unsigned long ulX, unsigned long ulY, 
                                   unsigned char *pcC);
extern void HX8347DisplayChinese(unsigned char ucLine, unsigned char ucCol,
                     unsigned char ucLen,
                     unsigned char *pucStr);
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
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //__HD44780_H__
