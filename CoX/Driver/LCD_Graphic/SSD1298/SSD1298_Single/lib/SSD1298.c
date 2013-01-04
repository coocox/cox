//*****************************************************************************
//
//! \file SSD1298.c
//! \brief 240 RGB x 320 TFT LCD Controller SSD1298 driver source file.
//! \version 2.1.1.0
//! \date 12/20/2012
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2012, CooCoX
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

#include "hw_SSD1298.h"
#include "SSD1298.h"
#include "FONT.h"
#include "colors.h"
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_gpio.h"
#include "xhw_nvic.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xgpio.h"

//
//! LCD structure
//
LCD_Info tLcd;

//
//! global point color and back color variables
//
unsigned short g_usPointColor = 0x0000;
unsigned short g_usBackColor = 0xFFFF;


//*****************************************************************************
//
//! \brief delay function for LCD initialization use.
//!
//! \param t specifies how long to delay.
//!
//! This function approximately delay for t millisecond.
//!
//! \return None.
//
//*****************************************************************************
void LCD_DelayMs(unsigned long t)
{
    while(t--)
    {
        xSysCtlDelay(35000);
    }
}

//*****************************************************************************
//
//! \brief Write command to LCD.
//!
//! \param usData The command data you want to write.
//!
//! This function write command to LCD through 16bit data line.
//!
//! \return None.
//
//*****************************************************************************
__inline void LCD_WriteCMD(unsigned short usData)
{
    LCD_RS_CLR;
    LCD_CS_CLR;
    LCD_DATAOUT(usData);
    LCD_WR_CLR;
    LCD_WR_SET;
    LCD_CS_SET;
}

//*****************************************************************************
//
//! \brief Write Data to LCD.
//!
//! \param usData The data you want to write.
//!
//! This function write data to LCD register or GRAM through 16bit data line.
//!
//! \return None.
//
//*****************************************************************************
__inline void LCD_WriteData(unsigned short usData)
{
    LCD_RS_SET;
    LCD_CS_CLR;
    LCD_DATAOUT(usData);
    LCD_WR_CLR;
    LCD_WR_SET;
    LCD_CS_SET;
}

//*****************************************************************************
//
//! \brief Write Data to LCD register.
//!
//! \param usCmd specifies the command/register you want to write.
//! \param usValue register value
//!
//! This function write data to LCD register.
//!
//! \return None.
//
//*****************************************************************************
void LCD_WriteReg(unsigned short usCmd, unsigned short usValue)
{
    LCD_WriteCMD(usCmd);
    LCD_WriteData(usValue);
}

//*****************************************************************************
//
//! \brief Read register value.
//!
//! \param usCmd specifies the register you want to read.
//!
//! This function is to read register value.
//!
//! \return specified register value.
//
//*****************************************************************************
unsigned short LCD_ReadReg(unsigned short usReg)
{
    unsigned short usRes;

    LCD_WriteCMD(usReg);
    xGPIODirModeSet( LCD_DATA_PORT, 0xFFFF, xGPIO_DIR_MODE_IN );

    LCD_RS_SET;
    LCD_CS_CLR;

    LCD_RD_CLR;
    LCD_RD_SET;
    usRes = LCD_DATAIN();
    LCD_CS_SET;
    xGPIODirModeSet( LCD_DATA_PORT, 0xFFFF, xGPIO_DIR_MODE_OUT );

    return usRes;
}

//*****************************************************************************
//
//! \brief BGR color format transform to RGB color format.
//!
//! \param usColor BGR format color data.
//!
//! This function is to transform BGR color format to RGB color format.
//! This is only used for read color data from GRAM because the color data
//! read out form GRAM is BGR color format.
//!
//! \return RGB format color data.
//
//*****************************************************************************
unsigned short LCD_BGR2RGB(unsigned short usColor)
{
    unsigned short r, g, b, rgb;

    b = (usColor >> 0) & 0x001F;
    g = (usColor >> 5) & 0x003F;
    r = (usColor >> 11) & 0x001F;
    rgb = (b << 11) + (g << 5) + (r << 0);

    return(rgb);
}

//*****************************************************************************
//
//! \brief Set cursor to a point.
//!
//! \param usXpos the x position of the point(0~239 in vertical mode, 0~319 in horizontal mode)
//! \param usYpos the y position of the point(0~319 in vertical mode, 0~239 in horizontal mode)
//!
//! This function is to set cursor to a specified point(actually set internal
//! GDDRAM X,Y address in the address counter)to write data.
//!
//! \return None.
//
//*****************************************************************************
void LCD_SetCursor(unsigned short usXpos, unsigned short usYpos)
{
    if(usXpos >= tLcd.usWidth || usYpos >= tLcd.usHeight) return;

    if(tLcd.ucOrientation == 0)
    {
        LCD_WriteReg(R4Eh, usXpos);
        LCD_WriteReg(R4Fh, usYpos);
    }
    else if(tLcd.ucOrientation == 1)
    {
        LCD_WriteReg(R4Eh, usYpos);
        LCD_WriteReg(R4Fh, 319 - usXpos);
    }
    else if(tLcd.ucOrientation == 2)
    {
        LCD_WriteReg(R4Eh, 239 - usXpos);
        LCD_WriteReg(R4Fh, usYpos);
    }
    else if(tLcd.ucOrientation == 3)
    {
        LCD_WriteReg(R4Eh, 239 - usYpos);
        LCD_WriteReg(R4Fh, usXpos);
    }
}

//*****************************************************************************
//
//! \brief Read the color data of a point
//!
//! \param x X coordinate of the point
//! \param y Y coordinate of the point
//!
//! This function is to read the color data of a point
//!
//! \return RGB format color data.
//
//*****************************************************************************
unsigned short LCD_ReadPiont(unsigned short x, unsigned short y)
{
    unsigned short usRes;

    LCD_SetCursor(x, y);
    LCD_WriteCMD(R22h);
    xGPIODirModeSet( LCD_DATA_PORT, 0xFFFF, xGPIO_DIR_MODE_IN );
    LCD_RS_SET;
    LCD_CS_CLR;
    LCD_RD_CLR;
    LCD_RD_SET;
    //
    //dummy READ
    //
    LCD_RD_CLR;
    LCD_RD_SET;
    usRes = LCD_DATAIN();
    LCD_CS_SET;
    xGPIODirModeSet( LCD_DATA_PORT, 0xFFFF, xGPIO_DIR_MODE_OUT );
    return LCD_BGR2RGB(usRes);
}

//*****************************************************************************
//
//! \brief LCD display on
//!
//! \param None
//!
//! This function is to turn on display
//!
//! \return None
//
//*****************************************************************************
void LCD_DisplayOn(void)
{
    LCD_WriteReg(R07h, 0x0173);
    LCD_BL_ON;
}

//*****************************************************************************
//
//! \brief LCD display off
//!
//! \param None
//!
//! This function is to turn off display
//!
//! \return None
//
//*****************************************************************************
void LCD_DisplayOff(void)
{
    LCD_WriteReg(R07h, 0x0);
    LCD_BL_OFF;
}

//*****************************************************************************
//
//! \brief LCD Set Window Size
//!
//! \param usXsta the x coordinate of the start point in the window
//! \param usYsta the y coordinate of the start point in the window
//! \param usXend the x coordinate of the last point in the window
//! \param usYend the y coordinate of the last point in the window
//!
//! This function is to limit GDDRAM X,Y address to a specified rectangular window.
//! In vertical mode x varies from 0 to 239,y varies from 0 to 319
//! In horizontal mode x varies from 0 to 319,y varies from 0 to 239
//!
//! \return None
//
//*****************************************************************************
void LCD_SetWindow(unsigned short usXsta, unsigned short usYsta, unsigned short usXend, unsigned short usYend)
{
    if(usXend >= tLcd.usWidth) usXend = tLcd.usWidth - 1;
    if(usYend >= tLcd.usHeight) usYend = tLcd.usHeight - 1;
    if(tLcd.ucOrientation == 0)
    {
        LCD_WriteReg(R44h, usXsta | ((usXend) << 8));
        LCD_WriteReg(R45h, usYsta);
        LCD_WriteReg(R46h, usYend);
    }
    else if(tLcd.ucOrientation == 1)
    {
        LCD_WriteReg(R44h, (239 - usYsta) | ((239 - usYend) << 8));
        LCD_WriteReg(R45h, 319 - usXend);
        LCD_WriteReg(R46h, 319 - usXsta);
    }
    else if(tLcd.ucOrientation == 2)
    {
        LCD_WriteReg(R44h, (239 - usXend) | ((239 - usXsta) << 8));
        LCD_WriteReg(R45h, usYsta);
        LCD_WriteReg(R46h, usYend);
    }
    else if(tLcd.ucOrientation == 3)
    {
        LCD_WriteReg(R44h, (239 - usYend) | ((239 - usYsta) << 8));
        LCD_WriteReg(R45h, usXsta);
        LCD_WriteReg(R46h, usXend);
    }
}

//*****************************************************************************
//
//! \brief Draw a dot on screen
//!
//! \param x the x coordinate of the dot
//! \param y the y coordinate of the dot
//!
//! This function is to draw a dot on screen.
//! The dot's color is determined by g_usPointColor
//!
//! \return None
//
//*****************************************************************************
void LCD_DrawDot(unsigned short x, unsigned short y)
{
    LCD_SetCursor(x, y);
    LCD_WriteCMD(R22h);
    LCD_WriteData(g_usPointColor);
}

//*****************************************************************************
//
//! \brief LCD initialization function
//!
//! \param None
//!
//! This function is to initialize the IO port and configure the LCD register
//!
//!
//! \return None
//
//*****************************************************************************
void LCD_Init(void)
{
    xSysCtlPeripheralEnable2(LCD_DATA_PORT);
    xSysCtlPeripheralEnable2(LCD_WR_PORT);
    xSysCtlPeripheralEnable2(LCD_CS_PORT);
    xSysCtlPeripheralEnable2(LCD_RS_PORT);
    xSysCtlPeripheralEnable2(LCD_RD_PORT);
    xSysCtlPeripheralEnable2(LCD_BL_PORT);

    xGPIOSPinTypeGPIOOutput(LCD_PIN_CS);
    xGPIOSPinTypeGPIOOutput(LCD_PIN_RS);
    xGPIOSPinTypeGPIOOutput(LCD_PIN_WR);
    xGPIOSPinTypeGPIOOutput(LCD_PIN_RD);
    xGPIOSPinTypeGPIOOutput(LCD_PIN_BL);

    xGPIODirModeSet( LCD_DATA_PORT, 0xFFFF, xGPIO_DIR_MODE_OUT );
    LCD_DelayMs(50);
    LCD_WriteReg(0x0000, 0x0001);
    LCD_DelayMs(50);
    //
    //! Get LCD Controller ID
    //
    tLcd.usID = LCD_ReadReg(0x0000);
    if(tLcd.usID == 0x8999)
    {
        tLcd.usHeight = 320;
        tLcd.usWidth = 240;
        tLcd.ucOrientation = 0;
    }

    //------------- Start Initial Sequence -------------//
    LCD_WriteReg(R00h, 0x0001); // Start internal OSC.
    LCD_WriteReg(R01h, 0x3B3F); // Driver output control, RL=0;REV=1;GD=1;BGR=0;SM=0;TB=1
    LCD_WriteReg(R02h, 0x0600); // set 1 line inversion
    //------------- Power control setup ----------------//
    LCD_WriteReg(R0Ch, 0x0007); // Adjust VCIX2 output voltage
    LCD_WriteReg(R0Dh, 0x0006); // Set amplitude magnification of VLCD63
    LCD_WriteReg(R0Eh, 0x3200); // Set alternating amplitude of VCOM
    LCD_WriteReg(0x1E, 0x00BB); // Set VcomH voltage
    LCD_WriteReg(0x03, 0x6A64); // Step-up factor/cycle setting
    //------------- RAM position control ---------------//
    LCD_WriteReg(R0Fh, 0x0000); // Gate scan position start at G0.
    LCD_WriteReg(R44h, 0xEF00); // Horizontal RAM address position
    LCD_WriteReg(R45h, 0x0000); // Vertical RAM address start position
    LCD_WriteReg(R46h, 0x013F); // Vertical RAM address end position
    // ----------- Adjust the Gamma Curve ----------//
    LCD_WriteReg(R30h, 0x0000);
    LCD_WriteReg(R31h, 0x0706);
    LCD_WriteReg(R32h, 0x0206);
    LCD_WriteReg(R33h, 0x0300);
    LCD_WriteReg(R34h, 0x0002);
    LCD_WriteReg(R35h, 0x0000);
    LCD_WriteReg(R36h, 0x0707);
    LCD_WriteReg(R37h, 0x0200);
    LCD_WriteReg(R3Ah, 0x0908);
    LCD_WriteReg(R3Bh, 0x0F0D);
    //----------------- Set VCOM OTP ---------------//
    LCD_WriteReg(R28h, 0x0006);
    //---------------- Turn On display -------------//
    LCD_WriteReg(R10h, 0x0000); // Sleep mode off.
    LCD_DelayMs(50);; // Wait 50mS
    LCD_WriteReg(R11h, 0x6070); // Entry mode setup. 262K type B,16-bit data bus only
    LCD_WriteReg(R07h, 0x0033); // Display ON

    LCD_DelayMs(100);
    LCD_BL_ON;
    LCD_Clear(COLOR_WHITE);
}

//*****************************************************************************
//
//! \brief Rotate Screen
//!
//! \param ucDegree specifies the degree to rotate.
//!  default 0 stands for 0бу(vertical)гм1 stands for 90бу,
//!  2 stands for 180бу, 3 stands for 270бу
//!
//! This function is to rotate screen
//!
//! \return None
//
//*****************************************************************************
void LCD_RotateScreen(unsigned char ucDegree)
{
    tLcd.ucOrientation = ucDegree;
    if((ucDegree % 2) != 0)
    {
        LCD_WriteReg(R01h, 0x3B3F);
        tLcd.usHeight = 240;
        tLcd.usWidth = 320;
        if(ucDegree == 1)
            LCD_WriteReg(R11h, 0x6098);
        else
            LCD_WriteReg(R11h, 0x60A8);
    }
    else
    {
        tLcd.usHeight = 320;
        tLcd.usWidth = 240;
        if(ucDegree == 0)
        {
            LCD_WriteReg(R01h, 0x3B3F);
            LCD_WriteReg(R11h, 0x6070);
        }
        else
        {
            LCD_WriteReg(R11h, 0x6060);
            LCD_WriteReg(R01h, 0x393F);
        }
    }
}

//*****************************************************************************
//
//! \brief Clear Screen
//!
//! \param usColor specifies the screen color after clear screen
//!
//! This function is to clear screen to a specified color
//!
//! \return None
//
//*****************************************************************************
void LCD_Clear(unsigned short usColor)
{
    unsigned long i;

    i = tLcd.usHeight * tLcd.usWidth;
    LCD_WriteReg(R44h, 0 | (239 << 8));
    LCD_WriteReg(R45h, 0);
    LCD_WriteReg(R46h, 319);
    LCD_WriteReg(R4Eh, 0);
    LCD_WriteReg(R4Fh, 0);

    //
    //! Start writing GRAM
    //
    LCD_WriteCMD(R22h);
    while(i--)
    {
        LCD_WriteData(usColor);
    }
}

//*****************************************************************************
//
//! \brief Fill a rectangular area with specified color
//!
//! \param usXsta the x coordinate of the start point in the rectangular
//! \param usYsta the y coordinate of the start point in the rectangular
//! \param usXend the x coordinate of the last point in the rectangular
//! \param usYend the y coordinate of the last point in the rectangular
//! \param usColor specifies the color filled in the rectangular
//!
//! This function is to fill a rectangular area with specified color
//!
//! \return None
//
//*****************************************************************************
void LCD_Fill(unsigned short usXsta, unsigned short usYsta,
              unsigned short usXend, unsigned short usYend, unsigned short usColor)
{
    unsigned long ulTmp;

    if(usXend >= tLcd.usWidth) usXend = tLcd.usWidth - 1;
    if(usYend >= tLcd.usHeight) usYend = tLcd.usHeight - 1;

    LCD_SetWindow(usXsta, usXsta, usXend, usYend);
    LCD_SetCursor(usXsta, usYsta);
    LCD_WriteCMD(R22h);
    ulTmp = (unsigned long)(usYend - usYsta + 1) * (usXend - usXsta + 1);
    while(ulTmp--)
    {
        LCD_WriteData(usColor);
    }
    LCD_WriteReg(R44h, 0x00EF);
    LCD_WriteReg(R45h, 0);
    LCD_WriteReg(R46h, 0x013F);
    LCD_SetWindow(0, 0, tLcd.usWidth, tLcd.usHeight);
}

//*****************************************************************************
//
//! \brief Draw line on the screen
//!
//! \param x1 the x coordinate of the start point
//! \param y1 the y coordinate of the start point
//! \param x2 the x coordinate of the end point
//! \param y2 the y coordinate of the end point
//!
//! This function is to draw a line between two specified points
//!
//! \return None
//
//*****************************************************************************
void LCD_DrawLine(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2)
{
    unsigned short i;
    short sIncX, sIncY, sDeltaX, sDeltaY;
    unsigned short usXerr = 0, usYerr = 0, usRow, usCol, usDistance;

    sDeltaX = x2 - x1;
    sDeltaY = y2 - y1;
    usRow = x1;
    usCol = y1;
    if(sDeltaX > 0)
    {
        sIncX = 1;
    }
    else if(sDeltaX == 0)
    {
        sIncX = 0;
    }
    else
    {
        sIncX = -1;
        sDeltaX = -sDeltaX;
    }

    if(sDeltaY > 0)
    {
        sIncY = 1;
    }
    else if(sDeltaY == 0)
    {
        sIncY = 0;
    }
    else
    {
        sIncY = -1;
        sDeltaY = -sDeltaY;
    }

    if(sDeltaX > sDeltaY)
    {
        usDistance = sDeltaX;
    }
    else
    {
        usDistance = sDeltaY;
    }

    for(i = 0; i <= usDistance + 1; i++ )
    {
        LCD_DrawDot(usRow, usCol);
        usXerr += sDeltaX;
        usYerr += sDeltaY ;
        if(usXerr > usDistance)
        {
            usXerr -= usDistance;
            usRow += sIncX;
        }
        if(usYerr > usDistance)
        {
            usYerr -= usDistance;
            usCol += sIncY;
        }
    }
}

//*****************************************************************************
//
//! \brief Fill a rectangular area with specified color
//!
//! \param x the x coordinate of the circle center
//! \param y the y coordinate of the circle center
//! \param r the radius of the circle
//!
//! This function is to draw a circle centered at (x,y) with r radius
//!
//! \return None
//
//*****************************************************************************
void LCD_DrawCircle(unsigned short x, unsigned short y, unsigned short r)
{
    unsigned short a, b;
    short di;

    a = 0;
    b = r;
    di = 3 - (r << 1);
    while(a <= b)
    {
        LCD_DrawDot(x + b, y - a);
        LCD_DrawDot(x - a, y + b);
        LCD_DrawDot(x - b, y - a);
        LCD_DrawDot(x - a, y - b);
        LCD_DrawDot(x + b, y + a);
        LCD_DrawDot(x + a, y - b);
        LCD_DrawDot(x + a, y + b);
        LCD_DrawDot(x - b, y + a);
        a++;
        if(di < 0)di += 4 * a + 6;
        else
        {
            di += 10 + 4 * (a - b);
            b--;
        }
        LCD_DrawDot(x + a, y + b);
    }
}

//*****************************************************************************
//
//! \brief Show a ASCII character on screen
//!
//! \param x the start point's x coordinate of the character
//! \param y the start point's y coordinate of the character
//! \param ucChar the ASCII character to be displayed
//! \param ucFontSize the character's size(12 stands for 12*6 size, 16 stands for 16*8 size)
//! \param ucMode determine whether to overwrite the back color of the character or not(0: overwrite back color, other: remain back color)
//!
//! This function is to Show a ASCII character on screen. Character color is
//! determined by g_usPointColor
//!
//! \return None
//
//*****************************************************************************
void LCD_ShowChar(unsigned short x, unsigned short y, unsigned char ucChar,
                  unsigned char ucFontSize, unsigned char ucMode)
{

    unsigned char ucTemp, ucRow, t;

    if(x > (tLcd.usWidth - ucFontSize / 2) || y > (tLcd.usHeight - ucFontSize))return;

    LCD_SetWindow(x, y, x + ucFontSize / 2 - 1, y + ucFontSize - 1);
    LCD_SetCursor(x, y);
    LCD_WriteCMD(R22h);
    ucChar = ucChar - ' ';

    if(!ucMode)
    {
        for(ucRow = 0; ucRow < ucFontSize; ucRow++)
        {
            if(ucFontSize == 12)ucTemp = ASCII_1206[ucChar][ucRow];
            else ucTemp = ASCII_1608[ucChar][ucRow];
            for(t = 0; t < ucFontSize / 2; t++)
            {
                if(ucTemp & 0x01)
                {
                    LCD_WriteData(g_usPointColor);
                }
                else LCD_WriteData(g_usBackColor);
                ucTemp >>= 1;
            }
        }
    }
    else
    {
        for(ucRow = 0; ucRow < ucFontSize; ucRow++)
        {
            if(ucFontSize == 12)ucTemp = ASCII_1206[ucChar][ucRow];
            else ucTemp = ASCII_1608[ucChar][ucRow];
            for(t = 0; t < ucFontSize / 2; t++)
            {
                if(ucTemp & 0x01)LCD_DrawDot(x + t, y + ucRow);
                ucTemp >>= 1;
            }
        }
    }

    //
    //! recover window size
    //
    LCD_SetWindow(0x0, 0x0, tLcd.usWidth - 1, tLcd.usHeight - 1);
}

//*****************************************************************************
//
//! \brief Show a ASCII character string on screen
//!
//! \param x the start point's x coordinate of the string
//! \param y the start point's y coordinate of the string
//! \param Str the ASCII character string to be displayed
//! \param ucFontSize the character's size(12 stands for 12*6 size, 16 stands for 16*8 size)
//!
//! This function is to show string on screen.
//! Auto change line and some format character like "\n","\r","\t" are supported
//!
//! \return None
//
//*****************************************************************************
void LCD_ShowString(unsigned short x, unsigned short y,
                    char *Str, unsigned char ucFontSize)
{
    char *p = Str;

    while(*p != '\0')
    {
        if(x > (tLcd.usWidth - (ucFontSize >> 2)))
        {
            x = 0;
            y += 16;
        }
        if(y > tLcd.usHeight - ucFontSize)
        {
            y =  0;
            x = 0;
        }
        if(*p == '\n')
        {
            y += 16;
        }
        else if(*p == '\r')
        {
            x = 0;
        }
        else if(*p == '\t')
        {
            x += ucFontSize << 1;
        }
        else LCD_ShowChar(x, y, *p, ucFontSize, 0);
        x += 8;
        p++;
    }
}

//*****************************************************************************
//
//! \brief Show a integer number on screen
//!
//! \param x the start point's x coordinate of the number
//! \param y the start point's y coordinate of the number
//! \param lNum the number to be displayed
//! \param ucFormat the format of number(2:binary, 8:octal, 10:decimal, 16:hex)
//! \param ucFontSize the character's size(12 stands for 12*6 size, 16 stands for 16*8 size)
//!
//! This function is to show number on screen. The scope of the number is -2147483648~2147483647
//! If ucFormat is hex, the minus number will display in complement type.
//!
//! \return None
//
//*****************************************************************************
void LCD_ShowNumber(unsigned short x, unsigned short y, long lNum,
                    unsigned char ucFormat, unsigned char ucFontSize)
{
    unsigned long ulTmp;
    char cBuf[11] = {0};
    unsigned char i;

    if(lNum == 0)
    {
        LCD_ShowChar(x, y, '0', ucFontSize, 0);
        return;
    }
    ulTmp = lNum;
    if((lNum < 0) && (ucFormat != 16))
    {
        LCD_ShowChar(x, y, '-', ucFontSize, 0);
        ulTmp = -lNum;
        x += ucFontSize / 2;
    }
    if(ucFormat == 16)
    {
        LCD_ShowString(x, y, "0x", ucFontSize);
        x += ucFontSize;
    }
    for(i = 10; i > 0; i--)
    {
        cBuf[i-1] = ulTmp % ucFormat;
        if(cBuf[i-1] > 9)
        {
            cBuf[i-1] = cBuf[i-1] - 10 + 'A';
        }
        else
        {
            cBuf[i-1] += '0';
        }
        ulTmp /= ucFormat;
        if(ulTmp == 0)break;
    }
    LCD_ShowString(x, y, &cBuf[i-1], ucFontSize);
}




