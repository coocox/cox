//*****************************************************************************
//
//! \file ST7735.c
//! \brief Driver for Character LCD ST7735.
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
#include "xhw_spi.h"
#include "xspi.h"
#include "hw_st7735.h"
#include "st7735.h"

#define DPYCOLORTRANSLATE(c)    ((((c) & 0x00f80000) >> 8) |               \
                                 (((c) & 0x0000fc00) >> 5) |               \
                                 (((c) & 0x000000f8) >> 3))

//*****************************************************************************
//
//! \brief Write data or command to the ST7735.
//!
//! \param ucRS determines if the IR or DR to select.
//!
//! The parameter of ucRS can be:
//! - ST7735_RS_COMMAND - select the IR.
//! - ST7735_RS_DATA - select the DR.
//!
//! \return None.
//
//*****************************************************************************
void 
ST7735Write(unsigned char ucRS, unsigned long ulInstruction)
{
    //
    // Check Arguments.
    //
    xASSERT((ucRS == ST7735_RS_COMMAND) || (ucDC == ST7735_RS_DATA));
    //
    // DC:Command, CS:Select
    //
    xGPIOSPinWrite(ST7735_PIN_CS, ST7735_CS_ENABLE);
    xGPIOSPinWrite(ST7735_PIN_RS, ucRS);
    xGPIOSPinWrite(ST7735_PIN_RD, ST7735_RD_WRITE);
	
    xGPIOSPinWrite(ST7735_PIN_D7, (ulInstruction >> 15) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D6, (ulInstruction >> 14) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D5, (ulInstruction >> 13) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D4, (ulInstruction >> 12) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D3, (ulInstruction >> 11) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D2, (ulInstruction >> 10) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D1, (ulInstruction >> 9) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D0, (ulInstruction >> 8) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_WR, ST7735_WR_LOW);
    xGPIOSPinWrite(ST7735_PIN_WR, ST7735_WR_HIGH);
	
    xGPIOSPinWrite(ST7735_PIN_D7, (ulInstruction >> 7) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D6, (ulInstruction >> 6) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D5, (ulInstruction >> 5) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D4, (ulInstruction >> 4) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D3, (ulInstruction >> 3) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D2, (ulInstruction >> 2) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D1, (ulInstruction >> 1) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D0, ulInstruction & 0x01);
    xGPIOSPinWrite(ST7735_PIN_WR, ST7735_WR_LOW);
    xGPIOSPinWrite(ST7735_PIN_WR, ST7735_WR_HIGH);
	
    xGPIOSPinWrite(ST7735_PIN_CS, ST7735_CS_DISABLE);
}
void write_data(unsigned char ulInstruction)
{
    xGPIOSPinWrite(ST7735_PIN_CS, ST7735_CS_ENABLE);
    xGPIOSPinWrite(ST7735_PIN_RS, ST7735_RS_DATA);
    xGPIOSPinWrite(ST7735_PIN_RD, ST7735_RD_WRITE);

    xGPIOSPinWrite(ST7735_PIN_D7, (ulInstruction >> 7) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D6, (ulInstruction >> 6) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D5, (ulInstruction >> 5) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D4, (ulInstruction >> 4) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D3, (ulInstruction >> 3) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D2, (ulInstruction >> 2) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D1, (ulInstruction >> 1) & 0x01);
    xGPIOSPinWrite(ST7735_PIN_D0, ulInstruction & 0x01);
    xGPIOSPinWrite(ST7735_PIN_WR, ST7735_WR_LOW);
    xGPIOSPinWrite(ST7735_PIN_WR, ST7735_WR_HIGH);
    xGPIOSPinWrite(ST7735_PIN_CS, ST7735_CS_DISABLE);
}

//*****************************************************************************
//
//! \brief Read the state or data from the ST7735.
//!
//! \param ucRS determines if the IR or DR to select.
//!
//! The parameter of ucDC can be:
//! - ST7735_RS_COMMAND - select the IR.
//! - ST7735_RS_DATA - select the DR.
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
ST7735Read(unsigned char ucRS)
{
    unsigned long ulData = 0;

    //
    // Set D7 - D0 direction to GPIO Input
    //      
    xGPIOSPinTypeGPIOInput(ST7735_PIN_D7);
    xGPIOSPinTypeGPIOInput(ST7735_PIN_D6);
    xGPIOSPinTypeGPIOInput(ST7735_PIN_D5);
    xGPIOSPinTypeGPIOInput(ST7735_PIN_D4);
    xGPIOSPinTypeGPIOInput(ST7735_PIN_D3);
    xGPIOSPinTypeGPIOInput(ST7735_PIN_D2);
    xGPIOSPinTypeGPIOInput(ST7735_PIN_D1);
    xGPIOSPinTypeGPIOInput(ST7735_PIN_D0);       

    //
    // DC:Command, RD:Write/Read, CS:Enable
    //
    xGPIOSPinWrite(ST7735_PIN_RS, ucRS);
    xGPIOSPinWrite(ST7735_PIN_WR, ST7735_WR_HIGH);	
    xGPIOSPinWrite(ST7735_PIN_CS, ST7735_CS_ENABLE);

    xSysCtlDelay(100);
    
    //
    // Read the Data
    //
		xGPIOSPinWrite(ST7735_PIN_RD, ST7735_RD_LOW);
    xSysCtlDelay(100);
    xGPIOSPinWrite(ST7735_PIN_RD, ST7735_RD_HIGH);
    ulData |= xGPIOSPinRead(ST7735_PIN_D7) << 7;
    ulData |= xGPIOSPinRead(ST7735_PIN_D6) << 6;
    ulData |= xGPIOSPinRead(ST7735_PIN_D5) << 5;
    ulData |= xGPIOSPinRead(ST7735_PIN_D4) << 4;
    ulData |= xGPIOSPinRead(ST7735_PIN_D3) << 3;
    ulData |= xGPIOSPinRead(ST7735_PIN_D2) << 2;
    ulData |= xGPIOSPinRead(ST7735_PIN_D1) << 1;
    ulData |= xGPIOSPinRead(ST7735_PIN_D0) << 0;
    
    xGPIOSPinWrite(ST7735_PIN_CS, ST7735_CS_DISABLE); 

    //
    // At the End, set D7 - D0 direction to GPIO OutPut
    //  
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D7);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D6);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D5);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D4);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D3);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D2);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D1);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D0);   
    
    return ulData;
}

void 
ST7735WriteCmd(unsigned char ucCmd)
{
    ST7735Write(ST7735_RS_COMMAND, ucCmd);
}

void 
ST7735WriteData(unsigned long ulData)
{
    ST7735Write(ST7735_RS_DATA, ulData);
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
ST7735SetCurPos(unsigned long ulStartX, unsigned long ulEndX, 
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
    ST7735WriteCmd(ST7735_CASET_REG);
    ST7735WriteData(ulStartX);
    ST7735WriteData(ulEndX);
    ST7735WriteCmd(ST7735_RASET_REG);
    ST7735WriteData(ulStartY);
    ST7735WriteData(ulEndY);
    ST7735WriteCmd(ST7735_RAMWR_REG);
}

//*****************************************************************************
//
//! \brief Init the ST7735 LCD Device.
//!
//! \param None.
//!
//! This function is used to Init the ST7735 Device. It must be call before 
//! any other LCD function use.
//!
//! It Open the pins's GPIO peripheral port, and config the pins type to GPIO 
//! output. Then config the LCD into the default state, clear the LCD and 
//! Open the display. Default A Blink cursor is set on. The LCD cursor move 
//! direction is config as increment default.
//!
//! The ST7735 Initial state can be determined by the \ref ST7735_Config.
//! - Pins that used is determined by \ref ST7735_Config_Pins.
//! - The LCD display line is determined by \ref ST7735_DISPLAY_LINE.
//! - The LCD character font is determined by \ref ST7735_CHARACTER_FONT.
//! .
//! 
//! \return None.
//
//*****************************************************************************
void 
ST7735Init(void)
{
    unsigned long ulCount;
    
    //
    // Enable GPIO Port that used
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ST7735_PIN_D7));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ST7735_PIN_D6));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ST7735_PIN_D5));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ST7735_PIN_D4));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ST7735_PIN_D3));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ST7735_PIN_D2));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ST7735_PIN_D1));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ST7735_PIN_D0)); 
 
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ST7735_PIN_RD));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ST7735_PIN_WR));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ST7735_PIN_CS));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ST7735_PIN_RS)); 
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ST7735_PIN_RST));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(ST7735_PIN_BACKLIGHT)); 
    //
    // Set Pins Type to GPIO Output
    //
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D7);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D6);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D5);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D4);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D3);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D2);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D1);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_D0);
  
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_RD);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_WR);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_CS);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_RS);  
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_RST);
    xGPIOSPinTypeGPIOOutput(ST7735_PIN_BACKLIGHT);   
    //
    // Turn on the backlight.
    //
    xGPIOSPinWrite(ST7735_PIN_BACKLIGHT, ST7735_BACKLIGHT_ON);

    xGPIOSPinWrite(ST7735_PIN_RST, ST7735_RST_ENABLE);
    xSysCtlDelay(100);
    xGPIOSPinWrite(ST7735_PIN_RST, ST7735_RST_DISABLE);
    xSysCtlDelay(100);

    ST7735WriteCmd(ST7735_SLPOUT_REG);    //sleep out and booter on 
    xSysCtlDelay(5000); 
   
    ST7735WriteCmd(ST7735_FRMCTR1_REG);    //
    ST7735WriteData(0x12C);	
    ST7735WriteData(0x2D00);
   
    ST7735WriteCmd(ST7735_FRMCTR2_REG);    // 
    ST7735WriteData(0x12C);	
    ST7735WriteData(0x2D00);
   
    ST7735WriteCmd(ST7735_FRMCTR3_REG);    //
    ST7735WriteData(0x12C);	
    ST7735WriteData(0x2D01);
    ST7735WriteData(0x2C2D);	

    ST7735WriteCmd(ST7735_INVCTR_REG);    // 
    ST7735WriteData(0x07); 
   
  //============ power control setting ========================== 
    ST7735WriteCmd(ST7735_PWCTR1_REG);     // 
    ST7735WriteData(0xA202);
    ST7735WriteData(0x84);

    ST7735WriteCmd(ST7735_PWCTR2_REG);     // set VCL,VGH,VGL,AVDD 
    ST7735WriteData(0xC5);
   
    ST7735WriteCmd(ST7735_PWCTR3_REG);     // 
    ST7735WriteData(0x0A00);
   
    ST7735WriteCmd(ST7735_PWCTR4_REG);     //
    ST7735WriteData(0x8A2A);	
   
    ST7735WriteCmd(ST7735_PWCTR5_REG);     // 
    ST7735WriteData(0x8AEE);
   
    ST7735WriteCmd(ST7735_VMCTR1_REG);     // 
    ST7735WriteData(0x0E);
   
    ST7735WriteCmd(ST7735_MADCTL_REG);    //set VCOMH,VCOML voltage 
    ST7735WriteData(0xC8);                //VCOMH=3.275V   
    ST7735WriteCmd(ST7735_INVOFF_REG); 
    ST7735WriteCmd(ST7735_INVON_REG);

    //===== gamma"+"polarity correction characteristic setting =================== 
    ST7735WriteCmd(ST7735_GAMCTRP1_REG); 
    ST7735WriteData(0x21C);
    ST7735WriteData(0x712);
    ST7735WriteData(0x3732);
    ST7735WriteData(0x292D);
    ST7735WriteData(0x2925);
    ST7735WriteData(0x2B39);
    ST7735WriteData(0x1);
    ST7735WriteData(0x310);

    //===== gamma"-"polarity correction characteristic setting =================== 
    ST7735WriteCmd(ST7735_GAMCTRN1_REG); 
    ST7735WriteData(0x31D);
    ST7735WriteData(0x706);
    ST7735WriteData(0x2E2C);
    ST7735WriteData(0x292D);
    ST7735WriteData(0x2E2E);
    ST7735WriteData(0x373F);
    ST7735WriteData(0x0);
    ST7735WriteData(0x210);
 
    ST7735WriteCmd(ST7735_INVOFF_REG);    //   
    ST7735WriteCmd(ST7735_MADCTL_REG);    // memory  access   control 
    write_data(0xcc); 
    ST7735WriteCmd(ST7735_COLMOD_REG);    // E0H or E1 Register enable or disabl 
    write_data(0x05);                     // E0H or E1 Register enable 
    ST7735WriteCmd(ST7735_DISPON_REG);    // display on 
	
    //
    // Set the display size and ensure that the GRAM window is set to allow
    // access to the full display buffer.
    //
    ST7735WriteCmd(ST7735_CASET_REG);
    ST7735WriteData(0);
    ST7735WriteData(LCD_HORIZONTAL_MAX - 1);
    ST7735WriteCmd(ST7735_RASET_REG);
    ST7735WriteData(0);
    ST7735WriteData(LCD_VERTICAL_MAX - 1);
 
    //
    // Clear the contents of the display buffer.
    // 
    ST7735WriteCmd(ST7735_RAMWR_REG);  
    for(ulCount = 0; ulCount < (LCD_HORIZONTAL_MAX * LCD_VERTICAL_MAX); ulCount++)
    {
        ST7735WriteData(0xFFFF);
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
ST7735EnterSleepMode(void)
{
    //
    // Sleep set
    //
    ST7735WriteCmd(ST7735_SLPIN_REG);		
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
ST7735ExitSleepMode(void)
{
    ST7735WriteCmd(ST7735_SLPOUT_REG);		
    xSysCtlDelay(50000); 
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
ST7735DisplayRectFill(unsigned short usStartX, unsigned short usEndX, 
                        unsigned short usStartY, unsigned short usEndY, unsigned long ulColor)
{
    unsigned short usTemp;
	
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
    ST7735SetCurPos(usStartX, usEndX, usStartY, usEndY); 
	
    for(usTemp = 0; usTemp <= (usEndX - usStartX + 1) * (usEndY - usStartY + 1); usTemp++)
    {
        ST7735WriteData(ulColor);
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
ST7735DisplayClear(unsigned long ulColor)
{
    ST7735DisplayRectFill(0, 127, 0, 159, ulColor);
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
ST7735DisplayInversionOn(void)
{
    ST7735WriteCmd(ST7735_INVON_REG);   
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
ST7735DisplayInversionOff(void)
{
    ST7735WriteCmd(ST7735_INVOFF_REG);      
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
ST7735DisplayOn(void)
{
    ST7735WriteCmd(ST7735_DISPON_REG);   
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
ST7735DisplayOff(void)
{
    ST7735WriteCmd(ST7735_DISPOFF_REG);      
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
ST7735BackLightOn(void)
{
    xGPIOSPinWrite(ST7735_PIN_BACKLIGHT, ST7735_BACKLIGHT_ON);   
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
ST7735BackLightOff(void)
{
    xGPIOSPinWrite(ST7735_PIN_BACKLIGHT, ST7735_BACKLIGHT_OFF);    
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
ST7735DrawOnePixel(unsigned short usX, unsigned short usY, unsigned long ulColor)                                 
{
    //
    // Write the pixel value.
    //
    ST7735SetCurPos(usX, usX, usY, usY);
    ST7735WriteData(ulColor);
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
ST7735DrawHorizontalLine(unsigned short usStartX, unsigned short usEndX,
                          unsigned short usY, unsigned long ulColor)
{
    xASSERT((usStartX <= usEndX) && (usEndX <= LCD_HORIZONTAL_MAX) && (usStartX >= 0));
    
    while(usStartX++ <= usEndX)
    {
        ST7735DrawOnePixel(usStartX, usY, ulColor);
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
ST7735DrawVerticalLine(unsigned short usX, unsigned short usStartY,
                        unsigned short usEndY, unsigned long ulColor)
{
    xASSERT((usStartY <= usEndY) && (usEndY <= LCD_VERTICAL_MAX) && (usStartY >= 0));
    
    while(usStartY++ <= usEndY)
    {
        ST7735DrawOnePixel(usX, usStartY, ulColor);
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
#ifdef ST7735_CHARACTER_FONT_8X16
#include "8X16.h"
void ST7735PutChar8x16(unsigned short usX, unsigned short usY, char c, 
                         unsigned long fColor, unsigned long bColor)
{
    unsigned int i, j;
    
    xASSERT((usX <= LCD_HORIZONTAL_MAX) && (usY <= LCD_VERTICAL_MAX));
    
    ST7735SetCurPos(usX, usX + 8 - 1, usY, usY + 16 - 1);
	
    for(i = 0; i < 16; i++) 
    {
        unsigned char m = Font8x16[(c - 0x20) * 16 + i];
        for(j = 0; j < 8; j++) 
        {
            if((m & 0x80) == 0x80) 
            {
                ST7735WriteData(fColor);
            }
            else 
            {
                ST7735WriteData(bColor);
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
#ifdef ST7735_CHINESE_FONT_16X16
#include "GB1616.h"
void ST7735PutGB1616(unsigned short usX, unsigned short usY, unsigned char ucChinese[2], 
                       unsigned long fColor,unsigned long bColor)
{
    unsigned char i,j,k;
    
    xASSERT((usX <= LCD_HORIZONTAL_MAX) && (usY <= LCD_VERTICAL_MAX));
    
    ST7735SetCurPos(usX,  usX + 16 - 1, usY, usY + 16 - 1);
	
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
                        ST7735WriteData(fColor);
                    }
                    else 
                    {
                        ST7735WriteData(bColor);
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
#ifdef ST7735_CHINESE_FONT_32X32
#include "GB3232.h"	
void ST7735PutGB3232(unsigned short usX, unsigned short  usY, unsigned char ucChinese[2], 
                       unsigned long fColor,unsigned long bColor)
{
    unsigned char i, j, k;

    xASSERT((usX < LCD_HORIZONTAL_MAX) && (usY < LCD_VERTICAL_MAX));
    
    ST7735SetCurPos(usX,  usX + 32 - 1, usY, usY + 32 - 1);
	
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
                        ST7735WriteData(fColor);
                    }
                    else 
                    {
                        ST7735WriteData(bColor);
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
#if ((defined ST7735_CHARACTER_FONT_8X16)||(defined ST7735_CHINESE_FONT_16X16))
void 
ST7735DisplayString(unsigned short usX, unsigned short usY, const char* pcString,
                     unsigned long fColor, unsigned long bColor)
{
    unsigned char ucl = 0;
    
    xASSERT(pcString != 0);
    
    while(*pcString) 
    {
        if( *pcString < 0x80) 
        {
            ST7735PutChar8x16(usX + ucl * 8, usY, *pcString, fColor, bColor);
            pcString++; ucl++;
        }
        else
        {
            ST7735PutGB1616(usX + ucl * 8, usY, (unsigned char*)pcString, fColor, bColor);
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
ST7735DisplayNum(unsigned short usX, unsigned short usY, unsigned long ulNum,
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
            ST7735PutChar8x16(usX + (ucFigures--) * 8 - 8, usY, ulNum%10 + '0', fColor, bColor);
            ulNum /= 10;
        }
    }
    else
    {
        ST7735PutChar8x16(usX, usY, '0', fColor, bColor);
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
ST7735DisplayBmp(unsigned short usX, unsigned short usY, unsigned short usSizeX, 
                   unsigned short usSizeY, unsigned char const *Bmp)
{
    unsigned short i,j;
    unsigned long ulBmpData;
    
    xASSERT((usX < LCD_HORIZONTAL_MAX) && (usY < LCD_VERTICAL_MAX));
    
    ST7735SetCurPos(usX, usX + usSizeX, usY, usY + usSizeY); 
	
    for( i = usY; i <= usY + usSizeY; i++ ) 
    {
        for( j = usX ; j <= usX + usSizeX; j++)
        {
            ulBmpData = *Bmp++;
            ulBmpData |= (*Bmp++) << 8;
            ST7735WriteData(ulBmpData);  
        }
    }
}
