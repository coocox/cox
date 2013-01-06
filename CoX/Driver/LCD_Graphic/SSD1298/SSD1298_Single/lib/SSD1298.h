//*****************************************************************************
//
//! \file SSD1298.h
//! \brief 240 RGB x 320 TFT LCD Controller SSD1298 driver head file.
//! \version 2.1.1.0
//! \date 12/20/2012
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
#ifndef __SSD1298_H__
#define __SSD1298_H__
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
//! \addtogroup SSD1298
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD1298_Driver_Single
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD1298_Config SSD1298 Driver Configuration
//!
//! \brief Configurations such as the GPIO Pin used should be set before using
//! this driver.
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SSD1298_Config_Pins SSD1298 Driver Pin Configuration
//!
//! \brief GPIO Pins Configurations that communication with the LCD should be
//! set before using this driver.
//!
//! @{
//
//*****************************************************************************

//
//! 16 bit data input output port
//
#define LCD_DATA_PORT	xGPIO_PORTE_BASE

//
//! chip select port
//
#define LCD_PIN_CS		PD12
#define LCD_CS_PORT		xGPIO_PORTD_BASE

//
//! register/data select port
//
#define LCD_PIN_RS		PD13
#define LCD_RS_PORT		xGPIO_PORTD_BASE

//
//! write strobe signal port
//
#define LCD_PIN_WR		PD14
#define LCD_WR_PORT		xGPIO_PORTD_BASE

//
//! read strobe signal port
//
#define	LCD_PIN_RD		PD15
#define LCD_RD_PORT		xGPIO_PORTD_BASE

#define LCD_PIN_BL		PD10
#define LCD_BL_PORT		xGPIO_PORTD_BASE

//
//! LCD control pins set and clear
//
#define  LCD_CS_SET 	xHWREGBITW(GPIO_BSRR+LCD_CS_PORT, GPIO_BIT_12)=1
#define  LCD_CS_CLR 	xHWREGBITW(GPIO_BRR+LCD_CS_PORT, GPIO_BIT_12)=1

#define  LCD_RS_SET 	xHWREGBITW(GPIO_BSRR+LCD_RS_PORT, GPIO_BIT_13)=1
#define  LCD_RS_CLR 	xHWREGBITW(GPIO_BRR+LCD_RS_PORT, GPIO_BIT_13)=1

#define  LCD_WR_SET 	xHWREGBITW(GPIO_BSRR+LCD_WR_PORT, GPIO_BIT_14)=1
#define  LCD_WR_CLR 	xHWREGBITW(GPIO_BRR+LCD_WR_PORT, GPIO_BIT_14)=1

#define  LCD_RD_SET 	xHWREGBITW(GPIO_BSRR+LCD_RD_PORT, GPIO_BIT_15)=1
#define  LCD_RD_CLR		xHWREGBITW(GPIO_BRR+LCD_RD_PORT, GPIO_BIT_15)=1

#define  LCD_BL_ON		xHWREGBITW(GPIO_BSRR+LCD_BL_PORT, GPIO_BIT_10)=1
#define  LCD_BL_OFF		xHWREGBITW(GPIO_BRR+LCD_BL_PORT, GPIO_BIT_10)=1

#define LCD_DATAOUT(dat) 	xHWREG(LCD_DATA_PORT + GPIO_ODR) = dat
#define LCD_DATAIN()     	xHWREG(LCD_DATA_PORT +GPIO_IDR )

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//
//! LCD rotate screen degree define
//
#define LCD_ROT_0		0
#define LCD_ROT_90		1
#define LCD_ROT_180		2
#define LCD_ROT_270		3
//
//! global variable of PointColor and BackColor
//
extern unsigned short g_usPointColor;
extern unsigned short g_usBackColor;

//
//! Default LCD information structure
//
typedef struct
{
	unsigned short usWidth;
	unsigned short usHeight;
	unsigned short usID;
	unsigned char ucOrientation;
} LCD_Info;


//*****************************************************************************
//
//! \addtogroup COX_SSD1298_Exported_APIs
//! @{
//
//*****************************************************************************
void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(unsigned short usColor);
void LCD_RotateScreen(unsigned char ucDegree);

extern unsigned short LCD_BGR2RGB(unsigned short usColor);
extern void LCD_SetCursor(unsigned short usXpos, unsigned short usYpos);
extern unsigned short LCD_ReadPiont(unsigned short x, unsigned short y);
extern void LCD_SetWindow(unsigned short usX, unsigned short usY, unsigned short usXend, unsigned short usYend);
extern void LCD_DrawDot(unsigned short x, unsigned short y);
extern void LCD_Fill(unsigned short usXsta, unsigned short usYsta,
					 unsigned short usXend, unsigned short usYend, unsigned short usColor);
extern void LCD_DrawLine(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2);
extern void LCD_DrawCircle(unsigned short x, unsigned short y, unsigned short r);
extern void LCD_ShowChar(unsigned short x, unsigned short y, unsigned char ucChar,
						 unsigned char ucFontSize, unsigned char ucMode);
extern void LCD_ShowString(unsigned short x, unsigned short y,
						   char *Str, unsigned char ucFontSize);
extern void LCD_ShowNumber(unsigned short x, unsigned short y, long lNum,
						   unsigned char ucFormat, unsigned char ucFontSize);
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
