//*****************************************************************************
//
//! \file uc1601.c
//! \brief the uc1601 Driver.
//! \version V2.1.1.0
//! \date 9/1/2011
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
//*****************************************************************************
#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xspi.h"
#include "xi2c.h"
#include "Xhw_spi.h"
#include "xgpio.h"
#include "uc1601.h"
#include "hw_uc1601.h"

unsigned char Ascii[];
unsigned char Ascii[]={
/*   */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,
/* ! */
0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* " */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,
/* # */
0x00,0x00,0x00,0xC0,0x30,0xC0,0x30,0x00,0xC8,0x39,0xCF,0x39,0x0F,0x09,0x01,0x00,
/* $ */
0xE0,0x10,0x10,0xF8,0x10,0x10,0x60,0x00,0x30,0x41,0x42,0xFF,0x42,0x44,0x38,0x00,
/* % */
0xC0,0x20,0x10,0xE0,0x20,0xE0,0x18,0x00,0x01,0xC2,0x31,0x0C,0x73,0x88,0x44,0x38
,
/* & */
0x00,0xE0,0x10,0x10,0xE0,0x00,0x00,0x00,0x78,0x85,0x82,0x8D,0x70,0xA2,0x9E,0x42
,
/* ' */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,
/* ( */
0xC0,0x30,0x08,0x04,0x00,0x00,0x00,0x00,0x1F,0x60,0x80,0x00,0x00,0x00,0x00,0x00
,
/* ) */
0x04,0x08,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x1F,0x00,0x00,0x00,0x00
,
/* * */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x28,0xFE,0x28,0x44,0x00,0x00,0x00
,
/* + */
0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0xFF,0x08,0x08,0x08,0x00,
/* , */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,0x00
,
/* - */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00
,
/* . */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00
,
/* / */
0x00,0x00,0x80,0x70,0x00,0x00,0x00,0x00,0xE0,0x1C,0x03,0x00,0x00,0x00,0x00,0x00
,
/* 0 */
0xC0,0x20,0x10,0x10,0x20,0xC0,0x00,0x00,0x3F,0x40,0x80,0x80,0x40,0x3F,0x00,0x00,
/* 1 */
0x20,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,
/* 2 */
0x60,0x10,0x10,0x10,0x20,0xC0,0x00,0x00,0xC0,0xA0,0x90,0x88,0x86,0xC1,0x00,0x00
,
/* 3 */
0x20,0x10,0x10,0x10,0xE0,0x00,0x00,0x00,0x80,0x80,0x82,0x83,0x44,0x38,0x00,0x00
,
/* 4 */
0x00,0x00,0x80,0x60,0xF0,0x00,0x00,0x00,0x18,0x16,0x11,0x10,0xFF,0x10,0x00,0x00,
/* 5 */
0x00,0xF0,0x10,0x10,0x10,0x10,0x00,0x00,0x80,0x81,0x81,0x81,0x42,0x3C,0x00,0x00
,
/* 6 */
0x80,0x40,0x20,0x10,0x10,0x10,0x00,0x00,0x3F,0x42,0x81,0x81,0x42,0x3C,0x00,0x00
,
/* 7 */
0x70,0x10,0x10,0x10,0x90,0x70,0x00,0x00,0x00,0x00,0xE0,0x1C,0x03,0x00,0x00,0x00
,
/* 8 */
0xC0,0x20,0x10,0x10,0x20,0xC0,0x00,0x00,0x38,0x45,0x82,0x82,0x45,0x38,0x00,0x00
,
/* 9 */
0xC0,0x20,0x10,0x10,0x20,0xC0,0x00,0x00,0x83,0x84,0x88,0x48,0x24,0x1F,0x00,0x00
,
/* : */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC3,0xC3,0x00,0x00,0x00,0x00,0x00,0x00
,
/* ; */
0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,0x00
,
/* < */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x28,0x28,0x44,0x44,0x82,0x00,0x00
,
/* = */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88
,
/* > */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x82,0x44,0x44,0x28,0x28,0x10,0x00,0x00
,
/* ? */
0xE0,0x10,0x10,0x10,0x20,0xC0,0x00,0x00,0x00,0x00,0xD8,0x06,0x01,0x00,0x00,0x00
,
/* @ */
0xC0,0x20,0x10,0x90,0x90,0x10,0xA0,0xC0,0x3F,0x40,0x8F,0x90,0x90,0x8F,0x50,0x5F,
/* A */
0x00,0x00,0x80,0x70,0x80,0x00,0x00,0x00,0x80,0xF0,0x8F,0x08,0x8F,0xF0,0x80,0x00,
/* B */
0x10,0xF0,0x10,0x10,0x10,0x20,0xC0,0x00,0x80,0xFF,0x82,0x82,0x82,0x45,0x38,0x00,
/* C */
0xC0,0x20,0x10,0x10,0x10,0x20,0x70,0x00,0x3F,0x40,0x80,0x80,0x80,0x80,0x40,0x00
,
/* D */
0x10,0xF0,0x10,0x10,0x10,0x60,0x80,0x00,0x80,0xFF,0x80,0x80,0x80,0x60,0x1F,0x00,
/* E */
0x10,0xF0,0x10,0x10,0x10,0x10,0x70,0x00,0x80,0xFF,0x82,0x82,0x82,0x87,0xE0,0x00,
/* F */
0x10,0xF0,0x10,0x10,0x10,0x10,0x70,0x00,0x80,0xFF,0x82,0x02,0x02,0x07,0x00,0x00,
/* G */
0xC0,0x20,0x10,0x10,0x20,0x70,0x00,0x00,0x3F,0x40,0x80,0x80,0x84,0x7C,0x04,0x00
,
/* H */
0x10,0xF0,0x10,0x00,0x10,0xF0,0x10,0x00,0x80,0xFF,0x82,0x02,0x82,0xFF,0x80,0x00,
/* I */
0x10,0xF0,0x10,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,
/* J */
0x00,0x00,0x10,0xF0,0x10,0x00,0x00,0x00,0x40,0x80,0x80,0x7F,0x00,0x00,0x00,0x00,
/* K */
0x10,0xF0,0x10,0x80,0x50,0x30,0x10,0x00,0x80,0xFF,0x83,0x0C,0xB0,0xC0,0x80,0x00,
/* L */
0x10,0xF0,0x10,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0x80,0x80,0x80,0xC0,0x20,0x00,
/* M */
0x10,0xF0,0x80,0x00,0x80,0xF0,0x10,0x00,0x80,0xFF,0x83,0x3C,0x83,0xFF,0x80,0x00,
/* N */
0x10,0xF0,0xC0,0x00,0x10,0xF0,0x10,0x00,0x80,0xFF,0x80,0x0F,0x30,0xFF,0x00,0x00,
/* O */
0x80,0x60,0x10,0x10,0x10,0x60,0x80,0x00,0x1F,0x60,0x80,0x80,0x80,0x60,0x1F,0x00,
/* P */
0x10,0xF0,0x10,0x10,0x10,0x20,0xC0,0x00,0x80,0xFF,0x84,0x04,0x04,0x02,0x01,0x00,
/* Q */
0xE0,0x18,0x04,0x04,0x04,0x18,0xE0,0x00,0x07,0x18,0x20,0x20,0x60,0x98,0x87,0x00
,
/* R */
0x10,0xF0,0x10,0x10,0x10,0x20,0xC0,0x00,0x80,0xFF,0x84,0x0C,0x34,0xC2,0x81,0x00,
/* S */
0xC0,0x20,0x10,0x10,0x10,0x20,0x70,0x00,0xE0,0x41,0x82,0x82,0x84,0x48,0x30,0x00
,
/* T */
0x30,0x10,0x10,0xF0,0x10,0x10,0x30,0x00,0x00,0x00,0x80,0xFF,0x80,0x00,0x00,0x00,
/* U */
0x10,0xF0,0x10,0x00,0x10,0xF0,0x10,0x00,0x00,0x7F,0x80,0x80,0x80,0x7F,0x00,0x00,
/* V */
0x10,0xF0,0x10,0x00,0x10,0xF0,0x10,0x00,0x00,0x01,0x1E,0xE0,0x1E,0x01,0x00,0x00,
/* W */
0x10,0xF0,0x10,0xC0,0x10,0xF0,0x10,0x00,0x00,0x0F,0xF0,0x0F,0xF0,0x0F,0x00,0x00,
/* X */
0x10,0x70,0x90,0x00,0x90,0x70,0x10,0x00,0x80,0xE0,0x99,0x06,0x99,0xE0,0x80,0x00
,
/* Y */
0x10,0x70,0x90,0x00,0x90,0x70,0x10,0x00,0x00,0x00,0x83,0xFC,0x83,0x00,0x00,0x00
,
/* Z */
0x70,0x10,0x10,0x10,0x10,0xD0,0x30,0x00,0xC0,0xB0,0x88,0x86,0x81,0x80,0xE0,0x00
,
/* [ */
0xFC,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0xFF,0x80,0x80,0x00,0x00,0x00,0x00,0x00,
/* \ */
0x70,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x1C,0xE0,0x00,0x00,0x00,0x00
,
/* ] */
0x04,0x04,0xFC,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xFF,0x00,0x00,0x00,0x00,0x00,
/* ^ */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x06,0x18,0x60,0x80,0x00
,
/* _ */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80
,
/* ` */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x60,0x40,0x80,0x00,0x00,0x00,0x00
,
/* a */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x91,0x89,0x49,0xFE,0x80,0x00,0x00
,
/* b */
0x10,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x81,0x81,0x42,0x3C,0x00,0x00,
/* c */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x81,0x81,0x81,0x42,0x00,0x00
,
/* d */
0x00,0x00,0x00,0x10,0xF0,0x00,0x00,0x00,0x3C,0x42,0x81,0x81,0x7F,0x80,0x00,0x00,
/* e */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x4A,0x89,0x89,0x8A,0x4C,0x00,0x00
,
/* f */
0x00,0x00,0xE0,0x10,0x10,0x20,0x00,0x00,0x01,0x81,0xFF,0x81,0x01,0x00,0x00,0x00,
/* g */
0x80,0x40,0x40,0x40,0x80,0x40,0x00,0x00,0x53,0xAC,0xA4,0xA4,0xA3,0x40,0x00,0x00,
/* h */
0x10,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0x01,0x01,0xFE,0x80,0x00,0x00,
/* i */
0x00,0xB0,0x00,0x00,0x00,0x00,0x00,0x00,0x81,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,
/* j */
0x00,0x00,0x80,0xCC,0x00,0x00,0x00,0x00,0x40,0x80,0x80,0x7F,0x00,0x00,0x00,0x00
,
/* k */
0x10,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0x98,0x25,0xC3,0x81,0x00,0x00,
/* l */
0x10,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,
/* m */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x81,0xFE,0x01,0xFE,0x01,0xFE,0x80,0x00,
/* n */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x81,0xFE,0x01,0x01,0xFE,0x80,0x00,0x00,
/* o */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x81,0x81,0x42,0x3C,0x00,0x00
,
/* p */
0x40,0x80,0x40,0x40,0x80,0x00,0x00,0x00,0x80,0xFF,0xA0,0x20,0x10,0x0F,0x00,0x00,
/* q */
0x00,0x80,0x40,0x40,0x80,0x40,0x00,0x00,0x0F,0x10,0x20,0xA0,0xFF,0x80,0x00,0x00,
/* r */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x81,0xFF,0x82,0x01,0x01,0x00,0x00,0x00,
/* s */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE6,0x49,0x89,0x91,0x92,0x67,0x00,0x00
,
/* t */
0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x7F,0x81,0x81,0x40,0x00,0x00
,
/* u */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x7F,0x80,0x81,0x7F,0x80,0x00,0x00,
/* v */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x39,0xC0,0x39,0x07,0x01,0x00
,
/* w */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x1F,0xE1,0x1C,0xE1,0x1F,0x01,0x00,
/* x */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x81,0xE7,0x18,0x18,0xE7,0x81,0x00,0x00
,
/* y */
0x40,0xC0,0x40,0x00,0x40,0xC0,0x40,0x00,0x80,0x81,0x46,0x38,0x06,0x01,0x00,0x00
,
/* z */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC3,0xA1,0x91,0x89,0x85,0xC3,0x00,0x00
,
/* { */
0x00,0xF0,0x08,0x00,0x00,0x00,0x00,0x00,0x02,0x7D,0x80,0x00,0x00,0x00,0x00,0x00
,
/* | */
0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* } */
0x08,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x7D,0x02,0x00,0x00,0x00,0x00,0x00
,
/* ~ */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x20,0x20,0x60,0xC0,0x80,0x80,0x60
};


//*****************************************************************************
//
//! \brief Init the UC1601 LCD.
//!
//! \param ulSpiClock SPI clock to select.
//!
//! This function initialize the mcu SPI as master and specified SPI port.
//!
//! \return None.
//
//*****************************************************************************
void UC1601Init(unsigned long ulSpiClock)
{
#if (UC1601_INTERFACE == UC1601_SPI_9BIT)
    //
    // Enable the GPIOx port which is connected with UC1601 
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_SPI_CLK));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_SPI_CS));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_SPI_MOSI));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_RST));
    
    //
    // Enable the SPIx which is connected with UC1601
    //
    xSysCtlPeripheralEnable2(LCD_PIN_SPI_PORT);
    xSysCtlPeripheralReset2(LCD_PIN_SPI_PORT);
    //
    // Set the chip select pin as OUT_MODE
    //
    xGPIOSPinDirModeSet(LCD_PIN_SPI_CS, xGPIO_DIR_MODE_OUT);
    //
    // Set the chip reset pin as OUT_MODE
    //
    xGPIOSPinDirModeSet(LCD_PIN_RST, xGPIO_DIR_MODE_OUT);
    
    xSPinTypeSPI(SPI_CLK, LCD_PIN_SPI_CLK);
    xSPinTypeSPI(SPI_MOSI, LCD_PIN_SPI_MOSI);
    
    //
    // Configure MCU as a master device , 9 bits data width ,MSB first,Mode_0
    //
    xSPIConfigSet(LCD_PIN_SPI_PORT, ulSpiClock, xSPI_MOTO_FORMAT_MODE_1 |
                                                xSPI_MODE_MASTER | 
                                                xSPI_MSB_FIRST |
                                                xSPI_DATA_WIDTH9);
    //
    // Disable UC1601 when Power up
    //
    xGPIOSPinWrite(LCD_PIN_SPI_CS, 1);
    
#elif (UC1601_INTERFACE == UC1601_SPI_8BIT)
    //
    // Enable the GPIOx port which is connected with UC1601 
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_SPI_CLK));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_SPI_CS));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_SPI_MOSI));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_CD));
    
    //
    // Enable the SPIx which is connected with UC1601
    //
    xSysCtlPeripheralEnable2(LCD_PIN_SPI_PORT);
    xSysCtlPeripheralReset2(LCD_PIN_SPI_PORT);
    //
    // Set the chip select pin as OUT_MODE
    //
    xGPIOSPinDirModeSet(LCD_PIN_SPI_CS, xGPIO_DIR_MODE_OUT);
    //
    // Set the chip reset pin as OUT_MODE
    //
    xGPIOSPinDirModeSet(LCD_PIN_CD, xGPIO_DIR_MODE_OUT);
    
    xSPinTypeSPI(SPI_CLK, LCD_PIN_SPI_CLK);
    xSPinTypeSPI(SPI_MOSI, LCD_PIN_SPI_MOSI);
    
    //
    // Configure MCU as a master device , 8 bits data width ,MSB first,Mode_0
    //
    xSPIConfigSet(LCD_PIN_SPI_PORT, ulSpiClock, xSPI_MOTO_FORMAT_MODE_1 |
                                                xSPI_MODE_MASTER | 
                                                xSPI_MSB_FIRST |
                                                xSPI_DATA_WIDTH8);
    //
    // Disable UC1601 when Power up
    //
    xGPIOSPinWrite(LCD_PIN_SPI_CS, 1);

#elif (UC1601_INTERFACE == UC1601_I2C)
    //
    // Enable the GPIOx port which is connected with UC1601 
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_I2C_SCK));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_I2C_SDA));
    
    //
    // Enable the SPIx which is connected with UC1601
    //
    xSysCtlPeripheralEnable2(LCD_PIN_I2C_PORT);
    xSysCtlPeripheralReset2(LCD_PIN_I2C_PORT);
    
    xSPinTypeI2C(I2C_SCK, LCD_PIN_I2C_SCK);
    xSPinTypeI2C(I2C_SDA, LCD_PIN_I2C_SDA);
    
    //
    // Configure MCU as a master device 
    //
    I2CMasterInit(LCD_PIN_I2C_PORT, ulSpiClock);

#elif (UC1601_INTERFACE == UC1601_8080)
    //
    // Enable the GPIOx port which is connected with UC1601 
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA0));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA1));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA2));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA3));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA4));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA5));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA6));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA7));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_CD));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_WR));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_RD));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_CS));
    
    LCD_PIN_DATA_OUT;
    xGPIOSPinDirModeSet(LCD_PIN_CD, xGPIO_DIR_MODE_OUT);
    xGPIOSPinDirModeSet(LCD_PIN_WR, xGPIO_DIR_MODE_OUT);
    xGPIOSPinDirModeSet(LCD_PIN_RD, xGPIO_DIR_MODE_OUT);

    xGPIOSPinDirModeSet(LCD_PIN_CS, xGPIO_DIR_MODE_OUT);
    
    //
    // Disable UC1601 when Power up
    //
    xGPIOSPinWrite(LCD_PIN_CS, 1);
    xGPIOSPinWrite(LCD_PIN_RD, 1);
    xGPIOSPinWrite(LCD_PIN_WR, 1);

#elif (UC1601_INTERFACE == UC1601_6800)
    //
    // Enable the GPIOx port which is connected with UC1601 
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA0));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA1));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA2));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA3));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA4));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA5));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA6));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_DATA7));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_CD));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_RW));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_E));
    xSysCtlPeripheralEnable(xGPIOSPinToPort(LCD_PIN_CS));
    
    LCD_PIN_DATA_OUT;
    xGPIOSPinDirModeSet(LCD_PIN_CD, xGPIO_DIR_MODE_OUT);
    xGPIOSPinDirModeSet(LCD_PIN_RW, xGPIO_DIR_MODE_OUT);
    xGPIOSPinDirModeSet(LCD_PIN_E, xGPIO_DIR_MODE_OUT);

    xGPIOSPinDirModeSet(LCD_PIN_CS, xGPIO_DIR_MODE_OUT);
    
    //
    // Disable UC1601 when Power up
    //
    xGPIOSPinWrite(LCD_PIN_CS, 1);
    xGPIOSPinWrite(LCD_PIN_RW, 1);
    xGPIOSPinWrite(LCD_PIN_E, 1);
#endif 
    
    //
    //Step 1 Set BR
    //    
    UC1601CmdWrite(UC1601_SET_BR_9);
    
    //
    //Step 2 Set PM
    //
    UC1601DoubleCmdWrite(UC1601_SET_PM, 0xA0);
    
    //
    //Step 3 set LCD Mapping Control
    //    
    UC1601CmdWrite(UC1601_SET_LC21);
    
    //
    //Step 4 Set Display Enable
    //    
    UC1601CmdWrite(UC1601_SET_DC2_EN);
     
}


//*****************************************************************************
//
//! \brief Send a data to the device.
//!
//! \param ucData The data to send.
//!
//! This function is to send a data to the device.
//!
//! \return None.
//
//*****************************************************************************
void UC1601DataWrite(unsigned char ucData)
{
    unsigned long ulTemp; 
#if (UC1601_INTERFACE == UC1601_SPI_9BIT)
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(LCD_PIN_SPI_CS, 0);
    
    //
    //Step 2 Set Display Enable
    //
    ulTemp = ucData | 0x100;
    xSPIDataWrite(LCD_PIN_SPI_PORT, &ulTemp, 1);
    
    //
    //Step 3 Disable chip select
    // 
    xGPIOSPinWrite(LCD_PIN_SPI_CS, 1); 
#elif (UC1601_INTERFACE == UC1601_SPI_8BIT)
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(LCD_PIN_SPI_CS, 0);
    
    //
    //Step 2 Set Display Enable
    //
    ulTemp = ucData;
    xGPIOSPinWrite(LCD_PIN_CD, 1);
    xSPIDataWrite(LCD_PIN_SPI_PORT, &ulTemp, 1);
    
    //
    //Step 3 Disable chip select
    // 
    xGPIOSPinWrite(LCD_PIN_SPI_CS, 1);
#elif (UC1601_INTERFACE == UC1601_I2C)
    xtI2CMasterTransferCfg cfg;
    ulTemp = ucData;
    cfg.ulSlave = UC1601DataAddr;
    cfg.pvWBuf = &ulTemp;
    cfg.ulWLen = 1;
    cfg.ulRLen = 0;
    cfg.pvRBuf = 0; 
    xI2CMasterTransfer(LCD_PIN_I2C_PORT, &cfg, I2C_TRANSFER_POLLING);
#elif (UC1601_INTERFACE == UC1601_8080)
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(LCD_PIN_CS, 0);
    
    //
    //Step 2 Set Display Enable
    //
    ulTemp = ucData;
    xGPIOSPinWrite(LCD_PIN_CD, 1);
    xGPIOSPinWrite(LCD_PIN_RD, 1);
    xGPIOSPinWrite(LCD_PIN_WR, 0);
    LCD_DATA_OUT(ulTemp);
    xGPIOSPinWrite(LCD_PIN_WR, 1);
    xSysCtlDelay(10);
    
    //
    //Step 3 Disable chip select
    // 
    xGPIOSPinWrite(LCD_PIN_CS, 1);
    
#elif (UC1601_INTERFACE == UC1601_6800)
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(LCD_PIN_CS, 0);
    
    //
    //Step 2 Set Display Enable
    //
    ulTemp = ucData;
    xGPIOSPinWrite(LCD_PIN_CD, 1);
    xGPIOSPinWrite(LCD_PIN_RW, 0);
    xGPIOSPinWrite(LCD_PIN_E, 1);
    LCD_DATA_OUT(ulTemp);
    xGPIOSPinWrite(LCD_PIN_RW, 1);
    xSysCtlDelay(10);
    xGPIOSPinWrite(LCD_PIN_E, 0);
    //
    //Step 3 Disable chip select
    // 
    xGPIOSPinWrite(LCD_PIN_CS, 1);  
#endif
}

//*****************************************************************************
//
//! \brief Send a command to the device.
//!
//! \param ucCmd The command to send.
//!
//! This function is to send a command to the device.
//!
//! \return None.
//
//*****************************************************************************
void UC1601CmdWrite(unsigned char ucCmd)
{
#if (UC1601_INTERFACE == UC1601_SPI_9BIT)
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(LCD_PIN_SPI_CS, 0);
    
    //
    //Step 2 Send a command
    //
    xSPIDataWrite(LCD_PIN_SPI_PORT, &ucCmd, 1);
    
    //
    //Step 3 Disable chip select
    // 
    xGPIOSPinWrite(LCD_PIN_SPI_CS, 1); 
#elif (UC1601_INTERFACE == UC1601_SPI_8BIT)
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(LCD_PIN_SPI_CS, 0);
    
    //
    //Step 2 Send a command
    //
    xGPIOSPinWrite(LCD_PIN_CD, 0);
    xSPIDataWrite(LCD_PIN_SPI_PORT, &ucCmd, 1);
    
    //
    //Step 3 Disable chip select
    // 
    xGPIOSPinWrite(LCD_PIN_SPI_CS, 1);
#elif (UC1601_INTERFACE == UC1601_I2C)
    xtI2CMasterTransferCfg cfg;
    cfg.ulSlave = UC1601CmdAddr;
    cfg.pvWBuf = &ucCmd;
    cfg.ulWLen = 1;
    cfg.ulRLen = 0;
    cfg.pvRBuf = 0; 
    xI2CMasterTransfer(LCD_PIN_I2C_PORT, &cfg, I2C_TRANSFER_POLLING);
#elif (UC1601_INTERFACE == UC1601_8080)
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(LCD_PIN_CS, 0);
    
    //
    //Step 2 Set Display Enable
    //
    xGPIOSPinWrite(LCD_PIN_CD, 0);
    xGPIOSPinWrite(LCD_PIN_RD, 1);
    xGPIOSPinWrite(LCD_PIN_WR, 0);
    LCD_DATA_OUT(ucCmd);
    xGPIOSPinWrite(LCD_PIN_WR, 1);
    xSysCtlDelay(10);
    
    //
    //Step 3 Disable chip select
    // 
    xGPIOSPinWrite(LCD_PIN_CS, 1);
    
#elif (UC1601_INTERFACE == UC1601_6800)
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(LCD_PIN_CS, 0);
    
    //
    //Step 2 Set Display Enable
    //
    xGPIOSPinWrite(LCD_PIN_CD, 0);
    xGPIOSPinWrite(LCD_PIN_RW, 0);
    xGPIOSPinWrite(LCD_PIN_E, 1);
    LCD_DATA_OUT(ucCmd);
    xGPIOSPinWrite(LCD_PIN_RW, 1);
    xSysCtlDelay(10);
    xGPIOSPinWrite(LCD_PIN_E, 0);
    //
    //Step 3 Disable chip select
    // 
    xGPIOSPinWrite(LCD_PIN_CS, 1);
#endif
}

//*****************************************************************************
//
//! \brief Send a double-byte command to the device.
//!
//! \param ucCmd The command to send.
//! \param ucData The data to send.
//!
//! This function is to send a double-byte command to the device.
//!
//! \return None.
//
//*****************************************************************************
void UC1601DoubleCmdWrite(unsigned char ucCmd, unsigned char ucData)
{
#if (UC1601_INTERFACE == UC1601_SPI_9BIT)
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(LCD_PIN_SPI_CS, 0);
    
    //
    //Step 2 Set command
    //
    xSPIDataWrite(LCD_PIN_SPI_PORT, &ucCmd, 1);
    xSPIDataWrite(LCD_PIN_SPI_PORT, &ucData, 1);
    
    //
    //Step 3 Disable chip select
    // 
    xGPIOSPinWrite(LCD_PIN_SPI_CS, 1); 
#elif (UC1601_INTERFACE == UC1601_SPI_8BIT)
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(LCD_PIN_SPI_CS, 0);
    
    //
    //Step 2 Set command
    //
    xGPIOSPinWrite(LCD_PIN_CD, 0);
    xSPIDataWrite(LCD_PIN_SPI_PORT, &ucCmd, 1);
    xSPIDataWrite(LCD_PIN_SPI_PORT, &ucData, 1);
    
    //
    //Step 3 Disable chip select
    // 
    xGPIOSPinWrite(LCD_PIN_SPI_CS, 1); 
#elif (UC1601_INTERFACE == UC1601_I2C)
    xtI2CMasterTransferCfg cfg;
    unsigned char ucTemp[]={ucCmd, ucData};
    cfg.ulSlave = UC1601CmdAddr;
    cfg.pvWBuf = ucTemp;
    cfg.ulWLen = 2;
    cfg.ulRLen = 0;
    cfg.pvRBuf = 0; 
    xI2CMasterTransfer(LCD_PIN_I2C_PORT, &cfg, I2C_TRANSFER_POLLING);
#elif (UC1601_INTERFACE == UC1601_8080)
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(LCD_PIN_CS, 0);
    
    //
    //Step 2 Set Display Enable
    //
    xGPIOSPinWrite(LCD_PIN_CD, 0);
    xGPIOSPinWrite(LCD_PIN_RD, 1);
    xGPIOSPinWrite(LCD_PIN_WR, 0);
    LCD_DATA_OUT(ucCmd);
    xGPIOSPinWrite(LCD_PIN_WR, 1);
    xSysCtlDelay(10);
    xGPIOSPinWrite(LCD_PIN_WR, 0);
    LCD_DATA_OUT(ucData);
    xGPIOSPinWrite(LCD_PIN_WR, 1);
    xSysCtlDelay(10);
    
    //
    //Step 3 Disable chip select
    // 
    xGPIOSPinWrite(LCD_PIN_CS, 1);
    
#elif (UC1601_INTERFACE == UC1601_6800)
    //
    //Step 1 Select Chip
    //
    xGPIOSPinWrite(LCD_PIN_CS, 0);
    
    //
    //Step 2 Set Display Enable
    //
    xGPIOSPinWrite(LCD_PIN_CD, 0);
    xGPIOSPinWrite(LCD_PIN_RW, 0);
    xGPIOSPinWrite(LCD_PIN_E, 1);
    LCD_DATA_OUT(ucCmd);
    xGPIOSPinWrite(LCD_PIN_RW, 1);
    xSysCtlDelay(10);
    xGPIOSPinWrite(LCD_PIN_RW, 0);
    LCD_DATA_OUT(ucData);
    xGPIOSPinWrite(LCD_PIN_RW, 1);
    xGPIOSPinWrite(LCD_PIN_E, 0);
    //
    //Step 3 Disable chip select
    // 
    xGPIOSPinWrite(LCD_PIN_CS, 1);
#endif
}

//*****************************************************************************
//
//! \brief Set the start address.
//!
//! \param ucPA The line of the data write in.
//! \param ucCA The address of the data write in.
//!
//! This function is to set the start address.
//!
//! \return None.
//
//*****************************************************************************
void UC1601AddressSet(unsigned char ucPA, unsigned char ucCA)
{
  
    //
    //Step 1 Set Page Address
    //
    UC1601CmdWrite((ucPA & UC1601_SET_PA_MASK) | UC1601_SET_PA);
    
    //
    //Step 2 Set Column Address MSB
    //
    UC1601CmdWrite(((ucCA>>4) & UC1601_SET_CA_MASK) | UC1601_SET_CA_MSB);

    //
    //Step 3 Set Column Address LSB
    //
    UC1601CmdWrite(((ucCA) & UC1601_SET_CA_MASK) | UC1601_SET_CA_LSB); 
}


//*****************************************************************************
//
//! \brief Send the data to the address.
//!
//! \param ucPA The line of the char show on.
//! \param ucCA The position of the line.
//! \param ucAsciiWord The word's ascii data.
//!
//! This function is to send the data to the address.
//!
//! \return None.
//
//*****************************************************************************
void UC1601Dispaly(unsigned char ucLine, unsigned char ucRow, 
                   unsigned char ucAsciiWord)
{
    int i=0,k=0;
    unsigned char uctemp;
    k=(ucAsciiWord-32)*16;
    
    for(i=0;i<8;i++)
    {
        UC1601AddressSet((ucLine*2),(129-(ucRow*8)-i));
        uctemp=Ascii[k+i];
        UC1601DataWrite(uctemp);
    }  
    for(i=0;i<8;i++)
    {
        UC1601AddressSet((ucLine*2)+1,(129-(ucRow*8)-i));
        uctemp=Ascii[k+i+8];
        UC1601DataWrite(uctemp);
    }  
}

//*****************************************************************************
//
//! \brief inverse display a char.
//!
//! \param ucPA The line of the char show on.
//! \param ucCA The position of the line.
//! \param ucAsciiWord The word's ascii data.
//!
//! This function is to inverse display a char.
//!
//! \return None.
//
//*****************************************************************************
void UC1601InverseDispaly(unsigned char ucLine, unsigned char ucRow, 
                          unsigned char ucAsciiWord)
{
    int i=0,k=0;
    unsigned char uctemp;
    k=(ucAsciiWord-32)*16;
    
    for(i=0;i<8;i++)
    {
        UC1601AddressSet((ucLine*2),(129-(ucRow*8)-i));
        uctemp=~Ascii[k+i];
        UC1601DataWrite(uctemp);
    }  
    for(i=0;i<8;i++)
    {
        UC1601AddressSet((ucLine*2)+1,(129-(ucRow*8)-i));
        uctemp=~Ascii[k+i+8];
        UC1601DataWrite(uctemp);
    } 
}

//*****************************************************************************
//
//! \brief show the words on LCD.
//!
//! \param ucPA The line of the char show on.
//! \param ucCA The position of the line.
//! \param pcChar the pointer of the words.
//!
//! This function is to show the words on LCD.
//!
//! \return None.
//
//*****************************************************************************
void UC1601CharDispaly(unsigned char ucLine, unsigned char ucRow, 
                       char *pcChar)
{
    xASSERT((ucLine <= 3) && (ucRow <= 15));
    
    do
    {
        UC1601Dispaly(ucLine,ucRow,*pcChar++);
        ucRow++;
        if(ucRow>15)
        {
            ucLine++;
            ucRow=0;
            if(ucLine>3)
                break;
        }
    }
    while(*pcChar!='\0');  
}

//*****************************************************************************
//
//! \brief show the words on LCD.
//!
//! \param ucPA The line of the char show on.
//! \param ucCA The position of the line.
//! \param ucLength The length of the Chinese.
//! \param pcChar the pointer of the words.
//!
//! This function is to show the words on LCD.
//!
//! \return None.
//
//*****************************************************************************
void UC1601ChineseDispaly(unsigned char ucLine, unsigned char ucRow, 
                          unsigned char ucLength, char *pcChar)
{
    int i,j=0;
    xASSERT((ucLine <= 3) && (ucRow <= 15));
    
    for(j=0;j<ucLength;j++)
    {
        for(i=0;i<16;i++)
        {
            UC1601AddressSet((ucLine*2),(129-(ucRow*8)-i));
            UC1601DataWrite(pcChar[j*32+i]);
        }  
        for(i=0;i<16;i++)
        {
            UC1601AddressSet((ucLine*2)+1,(129-(ucRow*8)-i));
            UC1601DataWrite(pcChar[j*32+16+i]);
        }  
        ucRow = ucRow +2;
        if (ucRow > 14)
        {
            ucLine++;
            if(ucLine > 3)
            {
                break;
            }
        }
    }    
}
//*****************************************************************************
//
//! \brief Display a decimal number on the LCD.
//!
//! \param n is the number that to display.
//!
//! Display a decimal number on the cursor location.
//!
//! \return None.
//
//*****************************************************************************
void HD44780DisplayN(unsigned char ucLine, unsigned char ucRow, 
                     unsigned long n)
{
    char pcBuf[16], *p;

    if (n == 0)
    {
        UC1601Dispaly(ucLine, ucRow, '0');
    }
    else
    {
        p = pcBuf;
        while (n != 0)
        {
            *p++ = (n % 10) + '0';
            n /= 10;
        }

        while (p > pcBuf)
        {
            UC1601Dispaly(ucLine, ucRow, *--p);  
            ucRow++;
            if (ucRow > 14)
            {
                ucLine++;
                if(ucLine > 3)
                {
                    break;
                }
            }
        }
    }
}

//*****************************************************************************
//
//! \brief clear all pannal.
//!
//! \param None
//!
//! This function is to clear all pannal.
//!
//! \return None.
//
//*****************************************************************************
void UC1601Clear(void)
{
    int i=0;

    UC1601AddressSet(0x0, 0x0);  /*CLEAR ALL PANNAL*/

    for (i = 0; i < 132 *8; i++)
    {
        UC1601DataWrite(0x00);
    }

    UC1601DataWrite(0x0f); 
}

//*****************************************************************************
//
//! \brief Enable inverse display.
//!
//! \param None
//!
//! This function is to enable inverse display.
//!
//! \return None.
//
//*****************************************************************************
void UC1601InverseEnable(void)
{
    UC1601CmdWrite(UC1601_SET_DC0_EN); 
}

//*****************************************************************************
//
//! \brief Disable inverse display.
//!
//! \param None
//!
//! This function is to disable inverse display.
//!
//! \return None.
//
//*****************************************************************************
void UC1601InverseDisable(void)
{
    UC1601CmdWrite(UC1601_SET_DC0);
}

//*****************************************************************************
//
//! \brief Enable All-Pixel-ON.
//!
//! \param None
//!
//! This function is to enable All-Pixel-ON.
//!
//! \return None.
//
//*****************************************************************************
void UC1601AllPixelOnEnable(void)
{
    UC1601CmdWrite(UC1601_SET_DC1_EN);
}

//*****************************************************************************
//
//! \brief Disable All-Pixel-ON.
//!
//! \param None
//!
//! This function is to disable All-Pixel-ON.
//!
//! \return None.
//
//*****************************************************************************
void UC1601AllPixelOnDisable(void)
{
    UC1601CmdWrite(UC1601_SET_DC1);
}

//*****************************************************************************
//
//! \brief Enable uc1601 diaplay.
//!
//! \param None
//!
//! This function is to enable uc1601 diaplay.
//!
//! \return None.
//
//*****************************************************************************
void UC1601DisplayOn(void)
{
    UC1601CmdWrite(UC1601_SET_DC2_EN);
}

//*****************************************************************************
//
//! \brief Disable uc1601 diaplay.
//!
//! \param None
//!
//! This function is to disable uc1601 diaplay.
//!
//! \return None.
//
//*****************************************************************************
void UC1601DisplayOff(void)
{
    UC1601CmdWrite(UC1601_SET_DC2);
}

//*****************************************************************************
//
//! \brief Set the scroll line number.
//!
//! \param ucLine the scroll line number.
//!
//! This function is to set the scroll line number.
//!
//! \return None.
//
//*****************************************************************************
void UC1601ScrollLineSet(unsigned char ucLine)
{
    xASSERT((ucLine <= 63) && (ucLine >= 0));
    UC1601CmdWrite(UC1601_SET_SL | (ucLine & UC1601_SET_SL_MASK));
}

//*****************************************************************************
//
//! \brief Set VBIAS Potentiometer.
//!
//! \param ucPM the VBIAS Potentiometer.
//!
//! This function is to set VBIAS Potentiometer.
//!
//! \return None.
//
//*****************************************************************************
void UC1601PMSet(unsigned char ucPM)
{
    xASSERT((ucLine <= 255) && (ucLine >= 0));
    UC1601DoubleCmdWrite(UC1601_SET_PM, ucPM);
}

//*****************************************************************************
//
//! \brief This command programs the ending COM electrode.
//!
//! \param ucCEN the ending COM electrode.
//!
//! This function is to programs the ending COM electrode.
//!
//! \return None.
//
//*****************************************************************************
void UC1601CENSet(unsigned char ucCEN)
{
    xASSERT((ucCEN <= 65) && (ucCEN >= 1));
    UC1601DoubleCmdWrite(UC1601_SET_CEN, ucCEN & UC1601_SET_CEN_MASK);
}

//*****************************************************************************
//
//! \brief This command programs the starting COM electrode.
//!
//! \param ucDST the starting COM electrode.
//!
//! This function is to programs the starting COM electrode.
//!
//! \return None.
//
//*****************************************************************************
void UC1601DSTSet(unsigned char ucDST)
{
    xASSERT((ucDST <= 65) && (ucDST >= 1));
    UC1601DoubleCmdWrite(UC1601_SET_DST, ucDST & UC1601_SET_DST_MASK);
}

//*****************************************************************************
//
//! \brief This command programs the ending COM electrode.
//!
//! \param ucDEN the ending COM electrode.
//!
//! This function is to programs the ending COM electrode.
//!
//! \return None.
//
//*****************************************************************************
void UC1601DENSet(unsigned char ucDEN)
{
    xASSERT((ucDEN <= 65) && (ucDEN >= 1));
    UC1601DoubleCmdWrite(UC1601_SET_DEN, ucDEN & UC1601_SET_DEN_MASK);
}
