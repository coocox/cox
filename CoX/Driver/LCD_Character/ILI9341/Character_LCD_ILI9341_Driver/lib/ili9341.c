//*****************************************************************************
//
//! \file ili9341.c
//! \brief Driver for Character LCD ILI9341.
//! \version 2.1.1.0
//! \date 10/18/2011
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

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xdebug.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "hw_ili9341.h"
#include "ili9341.h"

#define DPYCOLORTRANSLATE(c)    ((((c) & 0x00f80000) >> 8) |               \
                                 (((c) & 0x0000fc00) >> 5) |               \
                                 (((c) & 0x000000f8) >> 3))

//*****************************************************************************
//
//! \brief Write data or command to the ILI9341.
//!
//! \param ucRS determines if the IR or DR to select.
//!
//! The parameter of ucRS can be:
//! - ILI9341_RS_COMMAND - select the IR.
//! - ILI9341_RS_DATA - select the DR.
//!
//! \return None.
//
//*****************************************************************************
void 
ILI9341Write(unsigned char ucRS, unsigned long ulInstruction)
{
    //
    // Check Arguments.
    //
    xASSERT((ucRS == ILI9341_RS_COMMAND) || (ucDC == ILI9341_RS_DATA));
    //
    // DC:Command, CS:Select
    //
    xGPIOSPinWrite(ILI9341_PIN_CS, ILI9341_CS_ENABLE);
    xGPIOSPinWrite(ILI9341_PIN_RS, ucRS);
    xGPIOSPinWrite(ILI9341_PIN_RD, ILI9341_RD_WRITE);
	
    xGPIOSPinWrite(ILI9341_PIN_D7, (ulInstruction >> 15) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D6, (ulInstruction >> 14) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D5, (ulInstruction >> 13) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D4, (ulInstruction >> 12) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D3, (ulInstruction >> 11) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D2, (ulInstruction >> 10) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D1, (ulInstruction >> 9) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D0, (ulInstruction >> 8) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_WR, ILI9341_WR_LOW);
    xGPIOSPinWrite(ILI9341_PIN_WR, ILI9341_WR_HIGH);
	
    xGPIOSPinWrite(ILI9341_PIN_D7, (ulInstruction >> 7) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D6, (ulInstruction >> 6) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D5, (ulInstruction >> 5) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D4, (ulInstruction >> 4) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D3, (ulInstruction >> 3) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D2, (ulInstruction >> 2) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D1, (ulInstruction >> 1) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D0, ulInstruction & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_WR, ILI9341_WR_LOW);
    xGPIOSPinWrite(ILI9341_PIN_WR, ILI9341_WR_HIGH);
	
    xGPIOSPinWrite(ILI9341_PIN_CS, ILI9341_CS_DISABLE);
}

//*****************************************************************************
//
//! \brief Write a byte to the ILI9341.
//!
//! \param ucData determines which data will to be write.
//!
//! \return None.
//
//*****************************************************************************
void 
ILI9341Write8Bit(unsigned char ucData)
{
    xGPIOSPinWrite(ILI9341_PIN_CS, ILI9341_CS_ENABLE);
    xGPIOSPinWrite(ILI9341_PIN_RS, ILI9341_RS_DATA);
    xGPIOSPinWrite(ILI9341_PIN_RD, ILI9341_RD_WRITE);

    xGPIOSPinWrite(ILI9341_PIN_D7, (ucData >> 7) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D6, (ucData >> 6) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D5, (ucData >> 5) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D4, (ucData >> 4) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D3, (ucData >> 3) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D2, (ucData >> 2) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D1, (ucData >> 1) & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_D0, ucData & 0x01);
    xGPIOSPinWrite(ILI9341_PIN_WR, ILI9341_WR_LOW);
    xGPIOSPinWrite(ILI9341_PIN_WR, ILI9341_WR_HIGH);
    xGPIOSPinWrite(ILI9341_PIN_CS, ILI9341_CS_DISABLE);
}

//*****************************************************************************
//
//! \brief Read the state or data from the ILI9341.
//!
//! \param ucRS determines if the IR or DR to select.
//!
//! The parameter of ucDC can be:
//! - ILI9341_RS_COMMAND - select the IR.
//! - ILI9341_RS_DATA - select the DR.
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
ILI9341Read(unsigned char ucRS)
{
    unsigned long ulData = 0;

    //
    // Set D7 - D0 direction to GPIO Input
    //      
    xGPIOSPinTypeGPIOInput(ILI9341_PIN_D7);
    xGPIOSPinTypeGPIOInput(ILI9341_PIN_D6);
    xGPIOSPinTypeGPIOInput(ILI9341_PIN_D5);
    xGPIOSPinTypeGPIOInput(ILI9341_PIN_D4);
    xGPIOSPinTypeGPIOInput(ILI9341_PIN_D3);
    xGPIOSPinTypeGPIOInput(ILI9341_PIN_D2);
    xGPIOSPinTypeGPIOInput(ILI9341_PIN_D1);
    xGPIOSPinTypeGPIOInput(ILI9341_PIN_D0);       

    //
    // DC:Command, RD:Write/Read, CS:Enable
    //
    xGPIOSPinWrite(ILI9341_PIN_RS, ucRS);
    xGPIOSPinWrite(ILI9341_PIN_WR, ILI9341_WR_HIGH);	
    xGPIOSPinWrite(ILI9341_PIN_CS, ILI9341_CS_ENABLE);

    xSysCtlDelay(100);
    
    //
    // Read the Data
    //
		xGPIOSPinWrite(ILI9341_PIN_RD, ILI9341_RD_LOW);
    xSysCtlDelay(100);
    xGPIOSPinWrite(ILI9341_PIN_RD, ILI9341_RD_HIGH);
    ulData |= xGPIOSPinRead(ILI9341_PIN_D7) << 7;
    ulData |= xGPIOSPinRead(ILI9341_PIN_D6) << 6;
    ulData |= xGPIOSPinRead(ILI9341_PIN_D5) << 5;
    ulData |= xGPIOSPinRead(ILI9341_PIN_D4) << 4;
    ulData |= xGPIOSPinRead(ILI9341_PIN_D3) << 3;
    ulData |= xGPIOSPinRead(ILI9341_PIN_D2) << 2;
    ulData |= xGPIOSPinRead(ILI9341_PIN_D1) << 1;
    ulData |= xGPIOSPinRead(ILI9341_PIN_D0) << 0;
    
    xGPIOSPinWrite(ILI9341_PIN_CS, ILI9341_CS_DISABLE); 

    //
    // At the End, set D7 - D0 direction to GPIO OutPut
    //  
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D7);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D6);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D5);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D4);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D3);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D2);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D1);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D0);   
    
    return ulData;
}

void 
ILI9341WriteCmd(unsigned char ucCmd)
{
    ILI9341Write(ILI9341_RS_COMMAND, ucCmd);
}

void 
ILI9341WriteData(unsigned long ulData)
{
    ILI9341Write(ILI9341_RS_DATA, ulData);
}

//*****************************************************************************
//
//! \brief Set the cursor location.
//!
//! \param ulStartX is the character index.
//! \param ulEndX is the line number.
//!
//! The default location is (0,0). After set the location, the strings will
//! display at the (ulCol, ulRow).
//!
//! \return None.
//
//*****************************************************************************
void
ILI9341SetCurPos(unsigned long ulStartX, unsigned long ulEndX, 
                  unsigned long ulStartY, unsigned long ulEndY)
{
    //
    // Check Arguments.
    //
    xASSERT((ulStartX < ulEndX) && (ulStartY < ulEndY));
    xASSERT((ulEndX < LCD_HORIZONTAL_MAX) && (ulEndY < LCD_VERTICAL_MAX));
  
    //
    // Tell the controller we are about to write data into its RAM.
    //
    ILI9341WriteCmd(ILI9341_COLADDRSET_REG);
    ILI9341WriteData(ulStartX);
    ILI9341WriteData(ulEndX);
    ILI9341WriteCmd(ILI9341_PAGEADDRSET_REG);
    ILI9341WriteData(ulStartY);
    ILI9341WriteData(ulEndY);
    ILI9341WriteCmd(ILI9341_MEMORYWRITE_REG);
}

//*****************************************************************************
//
//! \brief Init the ILI9341 LCD Device.
//!
//! \param None.
//!
//! This function is used to Init the ILI9341 Device. It must be call before 
//! any other LCD function use.
//!
//! It Open the pins's GPIO peripheral port, and config the pins type to GPIO 
//! output. Then config the LCD into the default state, clear the LCD and 
//! Open the display. Default A Blink cursor is set on. The LCD cursor move 
//! direction is config as increment default.
//!
//! The ILI9341 Initial state can be determined by the \ref ILI9341_Config.
//! - Pins that used is determined by \ref ILI9341_Config_Pins.
//! - The LCD display line is determined by \ref ILI9341_DISPLAY_LINE.
//! - The LCD character font is determined by \ref ILI9341_CHARACTER_FONT.
//! .
//! 
//! \return None.
//
//*****************************************************************************
void 
ILI9341Init(void)
{
    unsigned long ulCount;
    
    //
    // Enable GPIO Port that used
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ILI9341_PIN_D7));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ILI9341_PIN_D6));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ILI9341_PIN_D5));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ILI9341_PIN_D4));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ILI9341_PIN_D3));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ILI9341_PIN_D2));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ILI9341_PIN_D1));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ILI9341_PIN_D0)); 
 
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ILI9341_PIN_RD));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ILI9341_PIN_WR));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ILI9341_PIN_CS));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ILI9341_PIN_RS)); 
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ILI9341_PIN_RST));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ILI9341_PIN_BACKLIGHT)); 
    //
    // Set Pins Type to GPIO Output
    //
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D7);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D6);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D5);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D4);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D3);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D2);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D1);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_D0);
  
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_RD);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_WR);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_CS);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_RS);  
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_RST);
    xGPIOSPinTypeGPIOOutput(ILI9341_PIN_BACKLIGHT);   
    //
    // Turn on the backlight.
    //
    xGPIOSPinWrite(ILI9341_PIN_BACKLIGHT, ILI9341_BACKLIGHT_ON);

    xGPIOSPinWrite(ILI9341_PIN_RST, ILI9341_RST_DISABLE);
    xSysCtlDelay(100);
    xGPIOSPinWrite(ILI9341_PIN_RST, ILI9341_RST_ENABLE);
    xSysCtlDelay(100);
    xGPIOSPinWrite(ILI9341_PIN_RST, ILI9341_RST_DISABLE);
    xSysCtlDelay(100);
   
    ILI9341WriteCmd(ILI9341_POWERCTLB_REG);      // 0xCF
    ILI9341WriteData(0x81);	
    ILI9341WriteData(0x30);
   
    ILI9341WriteCmd(ILI9341_POWONSEQCTL_REG);    // 0xED 
    ILI9341WriteData(0x6403);	
    ILI9341WriteData(0x1281);
   
    ILI9341WriteCmd(ILI9341_DIVTIMCTL_A_REG);    // 0xE8
    ILI9341WriteData(0x8500);	
    ILI9341WriteData(0x79); 

    ILI9341WriteCmd(ILI9341_POWERCTLA_REG);      // 0xC8 
    ILI9341WriteData(0x392c);
    ILI9341WriteData(0x34);	
    ILI9341WriteData(0x02);
   
    ILI9341WriteCmd(ILI9341_PUMPRATIOCTL_REG);   // 0xF7 
    ILI9341Write8Bit(0x20);

    ILI9341WriteCmd(ILI9341_DIVTIMCTL_B_REG);    // 0xEA set VCL,VGH,VGL,AVDD 
    ILI9341WriteData(0x00);
		
    ILI9341WriteCmd(ILI9341_FRAMECTL_NOR_REG);   // 0xb1 set VCL,VGH,VGL,AVDD 
    ILI9341WriteData(0x1b);
   
    ILI9341WriteCmd(ILI9341_POWERCTL1_REG);      // 0xC0 
    ILI9341Write8Bit(0x2e);//26
   
    ILI9341WriteCmd(ILI9341_POWERCTL2_REG);      // 0xC1
    ILI9341Write8Bit(0x12);	
   
    ILI9341WriteCmd(ILI9341_VCOMCTL1_REG);       // 0xC5 
    ILI9341WriteData(0x5019); //2b
   
    ILI9341WriteCmd(ILI9341_VCOMCTL2_REG);       // 0xC7 
    ILI9341Write8Bit(0x90); //c4
	
    ILI9341WriteCmd(ILI9341_MEMACCESS_REG);      // 0x36
    ILI9341Write8Bit(0xa8);

    ILI9341WriteCmd(ILI9341_FUNCTONCTL_REG);     // 0xB6
    ILI9341WriteData(0x0AA2);
    
    ILI9341WriteCmd(ILI9341_ENABLE_3G_REG);      // 0xF2
    ILI9341Write8Bit(0x00);
    ILI9341WriteCmd(ILI9341_GAMMASET_REG);       // 0x26
    ILI9341Write8Bit(0x01);
	
    ILI9341WriteCmd(ILI9341_POSGAMMACORRECTION_REG);  // 0xE0
    ILI9341WriteData(0x0F27);
    ILI9341WriteData(0x230B);
    ILI9341WriteData(0x0F05);
    ILI9341WriteData(0x5474);
    ILI9341WriteData(0x450A);
    ILI9341WriteData(0x170A);
    ILI9341WriteData(0x1C0E);
    ILI9341WriteData(0x08);//00

    //===== gamma"-"polarity correction characteristic setting =================== 
    ILI9341WriteCmd(ILI9341_NEGGAMMACORRECTION_REG);   //0xE1
    ILI9341WriteData(0x081A);
    ILI9341WriteData(0x1E03);
    ILI9341WriteData(0x0F05);
    ILI9341WriteData(0x2E25);
    ILI9341WriteData(0x3B01);
    ILI9341WriteData(0x0605);
    ILI9341WriteData(0x2533);
    ILI9341WriteData(0x0F);
		
    ILI9341WriteCmd(ILI9341_PIXFORMATSET_REG);   // 0x3A
    ILI9341Write8Bit(0x55);                      // 16-bit
    ILI9341WriteCmd(ILI9341_MEMACCESS_REG);      // 0x36
    ILI9341Write8Bit(0x00);
    ILI9341WriteCmd(ILI9341_INTERFCTL_REG);      // 0xF6
    ILI9341WriteData(0x130);
 
    ILI9341WriteCmd(ILI9341_DISPLAYON_REG);      // 0x29 Exit Sleep   
    ILI9341WriteCmd(ILI9341_SLEEP_OUT_REG);	     // 0x11
    xSysCtlDelay(500); 		
		
    //
    // Set the display size and ensure that the GRAM window is set to allow
    // access to the full display buffer.
    //
    ILI9341WriteCmd(ILI9341_COLADDRSET_REG);     // 0x2A
    ILI9341WriteData(0);
    ILI9341WriteData(LCD_HORIZONTAL_MAX - 1);
    ILI9341WriteCmd(ILI9341_PAGEADDRSET_REG);    // 0x2B
    ILI9341WriteData(0);
    ILI9341WriteData(LCD_VERTICAL_MAX - 1);

    //
    // Clear the contents of the display buffer.
    // 
    ILI9341WriteCmd(ILI9341_MEMORYWRITE_REG);    // 0x2C
    for(ulCount = 0; ulCount < (LCD_HORIZONTAL_MAX * LCD_VERTICAL_MAX); ulCount++)
    {
        ILI9341WriteData(0xFFFF);
    } 
}

//*****************************************************************************
//
//! \brief Enter the the LCD sleep mode.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void
ILI9341EnterSleepMode(void)
{
    //
    // Sleep set
    //
    ILI9341WriteCmd(ILI9341_SLEEP_ENTER_REG);		
}

//*****************************************************************************
//
//! \brief Exit the the LCD sleep mode.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void
ILI9341ExitSleepMode(void)
{
    ILI9341WriteCmd(ILI9341_SLEEP_OUT_REG);		
    xSysCtlDelay(500); 
}

//*****************************************************************************
//
//! \brief Fills a rectangle (direct LCD access mode).
//!
//! \param ulStartX is the starting address of X.
//! \param ulStartY is the starting address of Y.
//! \param ulEndX is the ending address of X.
//! \param ulEndY is the ending address of Y.
//! \param ulColor is the color.
//!
//! This function fills a rectangle on the display.  The coordinates of the
//! rectangle are assumed to be within the extents of the display, and the
//! rectangle specification is fully inclusive (in other words, both ulStartX and
//! ulEndX are drawn, along with ulStartY and ulEndY).
//!
//! \return None.
//
//*****************************************************************************
void 
ILI9341DisplayRectFill(unsigned short usStartX, unsigned short usEndX, 
                        unsigned short usStartY, unsigned short usEndY, unsigned long ulColor)
{
    unsigned long ulTemp;
	
    //
    // Check Arguments.
    //
    xASSERT((usStartX <= ulEndX)                &&
            (usStartY <= ulEndY)                &&
            ((usStartX >= 0) || (usEndX < LCD_HORIZONTAL_MAX)) &&
            ((usStartY >= 0) || (usEndY < LCD_VERTICAL_MAX)));            
	
    //
    // Clear LCD
    //
    ILI9341SetCurPos(usStartX, usEndX, usStartY, usEndY); 
	
    for(ulTemp = 0; ulTemp <= (usEndX - usStartX + 1) * (usEndY - usStartY + 1); ulTemp++)
    {
        ILI9341WriteData(ulColor);
    }
}

//*****************************************************************************
//
//! \brief Clears all the LCD display with the specified colour.
//!
//! \param ulColor is the specified colour.
//!
//! It clears all the LCD display with the specified colour.
//!
//! \return None.
//
//*****************************************************************************
void 
ILI9341DisplayClear(unsigned long ulColor)
{
    ILI9341DisplayRectFill(0, LCD_HORIZONTAL_MAX - 1, 0, LCD_VERTICAL_MAX - 1, ulColor);
}

//*****************************************************************************
//
//! \brief Enter into display inversion mode.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void 
ILI9341DisplayInversionOn(void)
{
    ILI9341WriteCmd(ILI9341_INVERSIONON_REG);   
}

//*****************************************************************************
//
//! \brief Recover from display inversion mode.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void 
ILI9341DisplayInversionOff(void)
{
    ILI9341WriteCmd(ILI9341_INVERSIONOFF_REG);      
}

//*****************************************************************************
//
//! \brief Enter into display inversion mode.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void 
ILI9341DisplayOn(void)
{
    ILI9341WriteCmd(ILI9341_DISPLAYON_REG);   
}

//*****************************************************************************
//
//! \brief Recover from display inversion mode.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void 
ILI9341DisplayOff(void)
{
    ILI9341WriteCmd(ILI9341_DISPLAYOFF_REG);      
}

//*****************************************************************************
//
//! \brief Turn on the entire LCD backlight display.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void 
ILI9341BackLightOn(void)
{
    xGPIOSPinWrite(ILI9341_PIN_BACKLIGHT, ILI9341_BACKLIGHT_ON);   
}

//*****************************************************************************
//
//! \brief Turn off the entire LCD backlight display.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void 
ILI9341BackLightOff(void)
{
    xGPIOSPinWrite(ILI9341_PIN_BACKLIGHT, ILI9341_BACKLIGHT_OFF);    
}

//*****************************************************************************
//
//! \brief Draws a pixel on the screen.
//!
//! \param ulX is the X coordinate of the pixel.
//! \param ulY is the Y coordinate of the pixel.
//! \param ulValue is the color of the pixel.
//!
//! This function sets the given pixel to a particular color.  The coordinates
//! of the pixel are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
void
ILI9341DrawOnePixel(unsigned short usX, unsigned short usY, unsigned long ulColor)                                 
{
    //
    // Write the pixel value.
    //
    ILI9341SetCurPos(usX, usX, usY, usY);
    ILI9341WriteData(ulColor);
}

//*****************************************************************************
//
//! \brief Draws a horizontal line.
//!
//! \param usStartX is the X coordinate of the start of the line.
//! \param usEndX is the X coordinate of the end of the line.
//! \param usY is the Y coordinate of the line.
//! \param usColor is the color of the line.
//!
//! This function draws a horizontal line on the display.  The coordinates of
//! the line are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
void
ILI9341DrawHorizontalLine(unsigned short usStartX, unsigned short usEndX,
                          unsigned short usY, unsigned long ulColor)
{
    xASSERT((usStartX <= usEndX) && (usEndX <= LCD_HORIZONTAL_MAX) && (usStartX >= 0));
    
    while(usStartX++ <= usEndX)
    {
        ILI9341DrawOnePixel(usStartX, usY, ulColor);
    }
}

//*****************************************************************************
//
//! \brief Draws a vertical line.
//!
//! \param ulX is the X coordinate of the line.
//! \param ulStartY is the Y coordinate of the start of the line.
//! \param ulEndY is the Y coordinate of the end of the line.
//! \param ulColor is the color of the line.
//!
//! This function draws a vertical line on the display.  The coordinates of the
//! line are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
void
ILI9341DrawVerticalLine(unsigned short usX, unsigned short usStartY,
                        unsigned short usEndY, unsigned long ulColor)
{
    xASSERT((usStartY <= usEndY) && (usEndY <= LCD_VERTICAL_MAX) && (usStartY >= 0));
    
    while(usStartY++ <= usEndY)
    {
        ILI9341DrawOnePixel(usX, usStartY, ulColor);
    }
}

//*****************************************************************************
//
//! \brief Display a char on the LCD.
//!
//! \param pcString is a non-terminated string that to display.
//!
//! Display a string on the cursor location.
//!
//! \return None.
//
//*****************************************************************************
#ifdef ILI9341_CHARACTER_FONT_8X16
#include "8X16.h"
void ILI9341PutChar8x16(unsigned short usX, unsigned short usY, char c, 
                         unsigned long fColor, unsigned long bColor)
{
    unsigned int i, j;
    
    xASSERT((usX <= LCD_HORIZONTAL_MAX) && (usY <= LCD_VERTICAL_MAX));
    
    ILI9341SetCurPos(usX, usX + 8 - 1, usY, usY + 16 - 1);
	
    for(i = 0; i < 16; i++) 
    {
        unsigned char m = Font8x16[(c - 0x20) * 16 + i];
        for(j = 0; j < 8; j++) 
        {
            if((m & 0x80) == 0x80) 
            {
                ILI9341WriteData(fColor);
            }
            else 
            {
                ILI9341WriteData(bColor);
            }
            m <<= 1;
        }
    }
}
#endif

//*****************************************************************************
//
//! \brief Display a 16*16 chinese on the LCD.
//!
//! \param pcString is a non-terminated string that to display.
//!
//! Display a chinese on the cursor location.
//!
//! \return None.
//
//*****************************************************************************
#ifdef ILI9341_CHINESE_FONT_16X16
#include "GB1616.h"
void ILI9341PutGB1616(unsigned short usX, unsigned short usY, unsigned char ucChinese[2], 
                       unsigned long fColor,unsigned long bColor)
{
    unsigned char i,j,k;
    
    xASSERT((usX <= LCD_HORIZONTAL_MAX) && (usY <= LCD_VERTICAL_MAX));
    
    ILI9341SetCurPos(usX,  usX + 16 - 1, usY, usY + 16 - 1);
	
    for (k = 0; k < 64; k++) 
    { 
        if ((codeGB_16[k].Index[0] == ucChinese[0])&&(codeGB_16[k].Index[1] == ucChinese[1]))
        { 
            for(i = 0; i < 32; i++) 
            {
                unsigned short m = codeGB_16[k].Msk[i];
                for(j = 0; j < 8; j++) 
                {
                    if((m & 0x80) == 0x80) 
                    {
                        ILI9341WriteData(fColor);
                    }
                    else 
                    {
                        ILI9341WriteData(bColor);
                    }
                    m <<= 1;
                } 
            }
        }  
    }	
}
#endif

//*****************************************************************************
//
//! \brief Display a 32*32 chinese on the LCD.
//!
//! \param pcString is a non-terminated string that to display.
//!
//! Display a chinese on the cursor location.
//!
//! \return None.
//
//*****************************************************************************
#ifdef ILI9341_CHINESE_FONT_32X32
#include "GB3232.h"	
void ILI9341PutGB3232(unsigned short usX, unsigned short  usY, unsigned char ucChinese[2], 
                       unsigned long fColor,unsigned long bColor)
{
    unsigned char i, j, k;

    xASSERT((usX < LCD_HORIZONTAL_MAX) && (usY < LCD_VERTICAL_MAX));
    
    ILI9341SetCurPos(usX,  usX + 32 - 1, usY, usY + 32 - 1);
	
    for (k = 0; k < 5; k++) 
    { 
        if ((codeGB_32[k].Index[0] == ucChinese[0])&&(codeGB_32[k].Index[1] == ucChinese[1]))
        { 
            for(i = 0; i < 128; i++) 
            {
                unsigned short m = codeGB_32[k].Msk[i];
                for(j = 0; j < 8; j++) 
                {
                    if((m & 0x80) == 0x80) 
                    {
                        ILI9341WriteData(fColor);
                    }
                    else 
                    {
                        ILI9341WriteData(bColor);
                    }
                    m <<= 1;
                } 
            }
        }  
    }	
}
#endif

//*****************************************************************************
//
//! \brief Display a string on the LCD.
//!
//! \param pcString is a non-terminated string that to display.
//!
//! Display a string on the cursor location.
//!
//! \return None.
//
//*****************************************************************************
#if ((defined ILI9341_CHARACTER_FONT_8X16)||(defined ILI9341_CHINESE_FONT_16X16))
void 
ILI9341DisplayString(unsigned short usX, unsigned short usY, const char* pcString,
                     unsigned long fColor, unsigned long bColor)
{
    unsigned char ucl = 0;
    
    xASSERT(pcString != 0);
    
    while(*pcString) 
    {
        if( *pcString < 0x80) 
        {
            ILI9341PutChar8x16(usX + ucl * 8, usY, *pcString, fColor, bColor);
            pcString++; ucl++;
        }
        else
        {
            ILI9341PutGB1616(usX + ucl * 8, usY, (unsigned char*)pcString, fColor, bColor);
            pcString += 2; ucl += 2;
        }
    }
}
#endif

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
void 
ILI9341DisplayNum(unsigned short usX, unsigned short usY, unsigned long ulNum,
                   unsigned long fColor, unsigned long bColor)
{
    unsigned char ucFigures = 0;
    unsigned long ulTemp = ulNum;  
    
    if(ulNum)
    {
        while (ulTemp)
        {
            ulTemp /= 10;
            ucFigures++;
        }
    
        while (ulNum)
        {
            ILI9341PutChar8x16(usX + (ucFigures--) * 8 - 8, usY, ulNum%10 + '0', fColor, bColor);
            ulNum /= 10;
        }
    }
    else
    {
        ILI9341PutChar8x16(usX, usY, '0', fColor, bColor);
    }
}

//*****************************************************************************
//
//! \brief Display a bmp picture on the LCD.
//!
//! \param n is the number that to display.
//!
//! Display a decimal number on the cursor location.
//!
//! \return None.
//
//*****************************************************************************
void 
ILI9341DisplayBmp(unsigned short usX, unsigned short usY, unsigned short usSizeX, 
                   unsigned short usSizeY, unsigned char const *Bmp)
{
    unsigned short i,j;
    unsigned long ulBmpData;
    
    xASSERT((usX < LCD_HORIZONTAL_MAX) && (usY < LCD_VERTICAL_MAX));
    
    ILI9341SetCurPos(usX, usX + usSizeX, usY, usY + usSizeY); 
	
    for( i = usY; i <= usY + usSizeY; i++ ) 
    {
        for( j = usX ; j <= usX + usSizeX; j++)
        {
            ulBmpData = *Bmp++;
            ulBmpData |= (*Bmp++) << 8;
            ILI9341WriteData(ulBmpData);  
        }
    }
}
