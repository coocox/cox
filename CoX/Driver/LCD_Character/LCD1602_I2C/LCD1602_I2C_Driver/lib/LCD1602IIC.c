//*****************************************************************************
//
//! \file LCD1602IIC.c
//! \brief Driver for Character LCD HD44780 which controlled by remote 8-bit I/O expander for I2C-bus PCA8574.
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
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_gpio.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xgpio.h"
#include "hw_LCD1602IIC.h"
#include "LCD1602IIC.h"

#ifdef USE_HARDWARE_IIC
#include "xhw_i2c.h"
#include "xi2c.h"
#endif


//**************************************************************
//
//! \internal
//! \brief software IIC SCL and SDA I/O control define
//
//***************************************************************
#ifdef USE_SOFTWARE_IIC
#define IIC_SDA_SET     xGPIOSPinWrite(LCD1602_IIC_PIN_SDA,1)
#define IIC_SDA_CLR     xGPIOSPinWrite(LCD1602_IIC_PIN_SDA,0)
#define IIC_SCL_SET     xGPIOSPinWrite(LCD1602_IIC_PIN_SCL,1)
#define IIC_SCL_CLR     xGPIOSPinWrite(LCD1602_IIC_PIN_SCL,0)
#define IIC_SDA_DDR_OUT xGPIOSDirModeSet(LCD1602_IIC_PIN_SDA, xGPIO_DIR_MODE_OD);
#define IIC_SDA_DDR_IN  xGPIOSDirModeSet(LCD1602_IIC_PIN_SDA, xGPIO_DIR_MODE_IN);
#endif

//**************************************************************
//
//! \internal
//! LCD1602 control parameters configure structure
//
//***************************************************************
static LCD1602Conf LCD1602Dev;

//*****************************************************************************
//
//! \internal
//! \brief IIC delay for software IIC communication.
//!
//! \param t specifies the time to delay.
//!
//! This function is to delay some time to reduce IIC clock, and other needed delay.
//! The exact delay time is affected by MCU system clock. Most IIC bus can only work
//! at lower than 400kHz. This program is tested at 72MHz system clock. It's important
//! to modify the delay time in your application if your system clock is faster.
//!
//! \return None.
//
//*****************************************************************************
static
void IICDelay(unsigned long t)
{
    xSysCtlDelay(t);
}

#ifdef USE_SOFTWARE_IIC

//*****************************************************************************
//
//! \internal
//! \brief Generate a start condition on I2C bus.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
static
void IICStart(void)
{
    IIC_SDA_SET;
    IIC_SCL_SET;
    IICDelay(100);
    //
    //Start condition:when SCL is high,SDA change form high to low
    //
    IIC_SDA_CLR;
    IICDelay(100);
    IIC_SCL_CLR;
    IICDelay(100);
}
//*****************************************************************************
//
//! \internal
//! \brief Generate a stop condition on I2C bus.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
static
void IICStop(void)
{
    IIC_SCL_CLR;
    IIC_SDA_CLR;
    //
    //Stop Condition:when SCL is high SDA change form low to high
    //
    IICDelay(100);
    IIC_SCL_SET;
    IICDelay(100);
    IIC_SDA_SET;
    IICDelay(100);
}

//*****************************************************************************
//
//! \internal
//! \brief Wait acknowledge signal.
//!
//! \param None
//!
//! Wait acknowledge signal from slave device after write data or address.
//!
//! \return 1:if not receive ack;  0:if receive ack.
//
//*****************************************************************************
static
unsigned char IICWaitAck(void)
{
    unsigned char ucOverTime = 0;
    IIC_SCL_SET;
    IICDelay(500);
    IIC_SDA_DDR_IN;
    IIC_SDA_SET;
    IICDelay(500);

    while(xGPIOSPinRead(LCD1602_IIC_PIN_SDA))
    {
        ucOverTime++;
        if(ucOverTime > 250)
        {
            IICStop();
            IIC_SDA_DDR_OUT;
            return 1;
        }
    }
    IIC_SCL_CLR;
    IIC_SDA_DDR_OUT;
    return 0;
}

//*****************************************************************************
//
//! \internal
//! \brief Send acknowledge signal.
//!
//! \param None
//!
//! Generate an acknowledge signal after read data through IIC Bus.
//!
//! \return None.
//
//*****************************************************************************
static
void IICAck(void)
{
    IIC_SCL_CLR;
    IIC_SDA_CLR;
    IICDelay(100);
    IIC_SCL_SET;
    IICDelay(100);
    IIC_SCL_CLR;
}

//*****************************************************************************
//
//! \internal
//! \brief No acknowledge signal.
//!
//! \param None
//!
//! Do not generate an acknowledge signal after read data through IIC Bus.
//!
//! \return None.
//
//*****************************************************************************
static
void IICNAck(void)
{
    IIC_SCL_CLR;
    IIC_SDA_SET;
    IICDelay(100);
    IIC_SCL_SET;
    IICDelay(100);
    IIC_SCL_CLR;
}

//*****************************************************************************
//
//! \internal
//! \brief Send a byte through IIC.
//!
//! \param ucSendData The data to be sent.
//!
//! This function is to send a byte of data through I2C BUS.
//!
//! \return None.
//
//*****************************************************************************
static
void IICSendByte(unsigned char ucSendData)
{
    unsigned char i, tmp;

    IIC_SCL_CLR;
    tmp = ucSendData;
    for(i = 0; i < 8; i++)
    {
        (tmp & 0x80) ? IIC_SDA_SET : IIC_SDA_CLR;
        tmp <<= 1;
        IICDelay(100);
        IIC_SCL_SET;
        IICDelay(100);
        IIC_SCL_CLR;
        IICDelay(100);
    }
}

//*****************************************************************************
//
//! \internal
//! \brief Read a byte through IIC.
//!
//! \param ucAck specifies whether to send an acknowledge signal.
//!
//! This function is to read a byte of data from I2C BUS.
//!
//! \return Read out data.
//
//*****************************************************************************
static
unsigned char IICReadByte(unsigned char ucAck)
{
    unsigned char i, ucRecDat = 0;
    IIC_SDA_DDR_IN;
    for(i = 0; i < 8; i++ )
    {
        IIC_SCL_CLR;
        IICDelay(100);
        IIC_SCL_SET;
        ucRecDat <<= 1;
        if(xGPIOSPinRead(LCD1602_IIC_PIN_SDA))
        {
            ucRecDat++;
        }
        IICDelay(100);
    }
    if (!ucAck)
        IICNAck();
    else
        IICAck();
    IIC_SDA_DDR_OUT;
    return ucRecDat;
}
#endif  //end of #ifdef USE_SOFTWARE_IIC

//*****************************************************************************
//
//! \internal
//! \brief Write address and data to IIC Bus.
//!
//! \param ucValue Data to be sent.
//!
//! This function firstly write device address to slave device, after receive
//! acknowledge signal, the data byte will be sent, then stop transmission.
//!
//! \return None.
//
//*****************************************************************************
static
void LCD1602IICExpandWrite(unsigned char ucValue)
{
#ifdef USE_HARDWARE_IIC
    xI2CMasterWriteRequestS1(LCD1602_IIC_PORT, LCD1602Dev.ucDevAddr,
            (ucValue | LCD1602Dev.ucBackLightEn), xtrue);
#else
    IICStop();
    IICStart();
    IICSendByte(LCD1602Dev.ucDevAddr<<1);
    IICWaitAck();
    IICSendByte(ucValue | LCD1602Dev.ucBackLightEn);
    IICWaitAck();
    IICStop();
#endif
}

//*****************************************************************************
//
//! \internal
//! \brief Data enable.
//!
//! \param ucValue Data to be sent.
//!
//! This function is to generate a data enable signal to LCD1602 to lock in
//! the higher four bits of ucValue to LCD1602.Data is locked in when EN pin
//! level of LCD1602 change from 1 to 0;
//!
//! \return None.
//
//*****************************************************************************
static
void LCD1602IICPulseEnable(unsigned char ucValue)
{
    LCD1602IICExpandWrite(ucValue | EN);
    IICDelay(50);
    LCD1602IICExpandWrite(ucValue & ~EN);
    IICDelay(50);
}

//*****************************************************************************
//
//! \internal
//! \brief Write 4 bits to LCD1602.
//!
//! \param ucValue Data to be sent.
//!
//! This function is to write 4 bit to LCD1602. Since we only use 4 bits data bus
//! of LCD1602, each time of write can only write 4 bits data. The higher 4 bits
//! are data bits to be written in LCD1602 and the lower 4 bits are control bits
//! to control the read/write time sequence and back light
//!
//! \return None.
//
//*****************************************************************************
static
void LCD1602IICWrite4Bits(unsigned char ucValue)
{
    LCD1602IICExpandWrite(ucValue);
    LCD1602IICPulseEnable(ucValue);
}

//*****************************************************************************
//
//! \internal
//! \brief Write command to LCD1602.
//!
//! \param ucValue command to be sent.
//!
//! This function is to write command to LCD1602 to configure the display mode.
//!
//! \return None.
//
//*****************************************************************************
static
void LCD1602IICWriteCmd(unsigned char ucValue)
{
    unsigned char tmp;
    tmp=ucValue&0xF0;
    LCD1602IICWrite4Bits(tmp);
    tmp=ucValue<<4;
    LCD1602IICWrite4Bits(tmp);
}

//*****************************************************************************
//
//! \internal
//! \brief Write data to DDRAM or CGRAM of LCD1602.
//!
//! \param ucValue data to be sent.
//!
//! This function is to write data to DDRAM or CGRAM of LCD1602.
//!
//! \return None.
//
//*****************************************************************************
static
void LCD1602IICWriteData(unsigned char ucValue)
{
    unsigned char tmp;
    tmp=ucValue&0xF0;
    LCD1602IICWrite4Bits(tmp | RS);
    tmp=ucValue<<4;
    LCD1602IICWrite4Bits(tmp | RS);
}

//*****************************************************************************
//
//! \brief LCD1602 Clear function.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void LCD1602Clear(void)
{
    LCD1602IICWriteCmd(LCD1602IIC_CLEARDISPLAY);
    IICDelay(50000);
}

//*****************************************************************************
//
//! \brief Set the cursor, the display and address counter to zero.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void LCD1602Home(void)
{
    LCD1602IICWriteCmd(LCD1602IIC_RETURNHOME);
    IICDelay(50000);
}

//*****************************************************************************
//
//! \brief Set the start address of display to specified address
//!
//! \param ucRow specify which row to display(for LCD1602 it can only be 0 or 1).
//! \param ucCol specify which col to display(for LCD1602 it can only be 0 or 1).
//!
//! \return None.
//
//*****************************************************************************
void LCD1602SetCursor(unsigned char ucRow, unsigned char ucCol)
{
    unsigned char ucRowOffset[] = { 0x00, 0x40, 0x14, 0x54 };
    if(ucCol<LCD1602Dev.ucNumCols&&ucRow<LCD1602Dev.ucNumRows)
    {
        LCD1602IICWriteCmd(LCD1602IIC_SETDDRAMADDR | (ucCol + ucRowOffset[ucRow]));
    }
}

//*****************************************************************************
//
//! \brief Turn off the display of LCD1602.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void LCD1602DisplayOff(void)
{
    LCD1602Dev.ucDisplayControl &= ~LCD1602IIC_DISPLAYON;
    LCD1602IICWriteCmd(LCD1602IIC_DISPLAYCONTROL | LCD1602Dev.ucDisplayControl);
}

//*****************************************************************************
//
//! \brief Turn on the display of LCD1602.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void LCD1602DisplayOn(void)
{
    LCD1602Dev.ucDisplayControl |= LCD1602IIC_DISPLAYON;
    LCD1602IICWriteCmd(LCD1602IIC_DISPLAYCONTROL | LCD1602Dev.ucDisplayControl);
}

//*****************************************************************************
//
//! \brief Do not show the cursor.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void LCD1602CursorOff(void)
{
    LCD1602Dev.ucDisplayControl &= ~LCD1602IIC_CURSORON;
    LCD1602IICWriteCmd(LCD1602IIC_DISPLAYCONTROL | LCD1602Dev.ucDisplayControl);
}

//*****************************************************************************
//
//! \brief Show the cursor.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void LCD1602CursorOn(void)
{
    LCD1602Dev.ucDisplayControl |= LCD1602IIC_CURSORON;
    LCD1602IICWriteCmd(LCD1602IIC_DISPLAYCONTROL | LCD1602Dev.ucDisplayControl);
}

//*****************************************************************************
//
//! \brief Turn off blink.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void LCD1602BlinkOff(void)
{
    LCD1602Dev.ucDisplayControl &= ~LCD1602IIC_BLINKON;
    LCD1602IICWriteCmd(LCD1602IIC_DISPLAYCONTROL | LCD1602Dev.ucDisplayControl);
}

//*****************************************************************************
//
//! \brief Turn on blink.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void LCD1602BlinkOn(void)
{
    LCD1602Dev.ucDisplayControl |= LCD1602IIC_BLINKON;
    LCD1602IICWriteCmd(LCD1602IIC_DISPLAYCONTROL | LCD1602Dev.ucDisplayControl);
}

//*****************************************************************************
//
//! \brief Scroll display content to left by one character width.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void LCD1602ScrollDisplayLeft(void)
{
    LCD1602IICWriteCmd(LCD1602IIC_DISPLAYMOVE | LCD1602IIC_CURSORSHIFT | LCD1602IIC_MOVELEFT);
}

//*****************************************************************************
//
//! \brief Scroll display content to right by one character width.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void LCD1602ScrollDisplayRight(void)
{
    LCD1602IICWriteCmd(LCD1602IIC_DISPLAYMOVE | LCD1602IIC_CURSORSHIFT | LCD1602IIC_MOVERIGHT);
}

//*****************************************************************************
//
//! \brief Turn on auto scroll.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************

void LCD1602AutoScrollOn(void)
{
    LCD1602Dev.ucDisplayMode |= LCD1602IIC_ENTRYSHIFTINC;
    LCD1602IICWriteCmd(LCD1602IIC_ENTRYMODESET | LCD1602Dev.ucDisplayMode);
}

//*****************************************************************************
//
//! \brief Turn off auto scroll.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void LCD1602AutoScrollOff(void)
{
    LCD1602Dev.ucDisplayMode &= ~LCD1602IIC_ENTRYSHIFTINC;
    LCD1602IICWriteCmd(LCD1602IIC_ENTRYMODESET | LCD1602Dev.ucDisplayMode);
}

//*****************************************************************************
//
//! \brief Turn off back light.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void LCD1602BacklightOff(void)
{
    LCD1602Dev.ucBackLightEn=LCD1602IIC_BACKLIGHTOFF;
    LCD1602IICExpandWrite(0);
}

//*****************************************************************************
//
//! \brief Turn on back light.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void LCD1602BacklightOn(void)
{
    LCD1602Dev.ucBackLightEn=LCD1602IIC_BACKLIGHTON;
    LCD1602IICExpandWrite(0);
}

//*****************************************************************************
//
//! \brief Create a user defined character.
//!
//! \param ucLocation specify where should the new character be stored in the CGRAM.
//! \param ucCharMap The dot matrix array of the character.
//!
//! \return None.
//
//*****************************************************************************
void LCD1602CreateChar(unsigned char ucLocation, unsigned char ucCharMap[])
{
    unsigned char i;
    ucLocation&=0x7;
    LCD1602IICWriteCmd(LCD1602IIC_SETCGRAMADDR | ucLocation<<3);
    for(i=0;i<8;i++)
    {
        LCD1602IICWriteData(ucCharMap[i]);
    }
}

//*****************************************************************************
//
//! \brief Show a character.
//!
//! \param ucRow Specify the row location of the character.
//! \param ucCol Specify the col location of the character.
//! \param ch The character need to be displayed
//!
//! \return None.
//
//*****************************************************************************
void LCD1602ShowChar(unsigned char ucRow, unsigned char ucCol, char ch)
{
    if(ucCol<LCD1602Dev.ucNumCols&&ucRow<LCD1602Dev.ucNumRows)
    {
        LCD1602SetCursor(ucRow,ucCol);
        LCD1602IICWriteData(ch);
    }
}

//*****************************************************************************
//
//! \brief Show a string.
//!
//! \param ucRow Specify the row location of the character.
//! \param ucCol Specify the col location of the character.
//! \param pStr The string's start address
//!
//! If the length of the string exceed one line,it will continue displaying
//! in next line and previous display will be covered.
//!
//! \return None.
//
//*****************************************************************************
void LCD1602PrintString(unsigned char ucRow, unsigned char ucCol, char *pStr)
{
    char *p;
    p=pStr;
    if(ucCol<LCD1602Dev.ucNumCols&&ucRow<LCD1602Dev.ucNumRows)
    {
        while(*p)
        {
            LCD1602ShowChar(ucRow,ucCol,*p);
            p++;
            ucCol++;
            if(ucCol>=16)
            {
            	ucCol=0;
            	ucRow++;
            }
            if(ucRow>1)
            {
                ucRow=0;
            }
        }
    }
}

//*****************************************************************************
//
//! \brief IIC interface initialization.
//!
//! \param ulCLK specify the IIC clock frequency, only effective in hardware IIC mode.
//!
//! \return None.
//
//*****************************************************************************
void IICInit(unsigned long ulCLK)
{
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(LCD1602_IIC_PIN_SCL));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(LCD1602_IIC_PIN_SDA));
#ifdef USE_HARDWARE_IIC
    xSPinTypeI2C(LCD1602_IIC_SCL, LCD1602_IIC_PIN_SCL);
    xSPinTypeI2C(LCD1602_IIC_SDA, LCD1602_IIC_PIN_SDA);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xSysCtlPeripheralEnable2(LCD1602_IIC_PORT);
    xI2CMasterInit(LCD1602_IIC_PORT, ulCLK);
    I2CMasterInit(LCD1602_IIC_PORT, xSysCtlClockGet()/2, xfalse, xtrue);
    xI2CMasterEnable(LCD1602_IIC_PORT);
#else
    xGPIOSDirModeSet(LCD1602_IIC_PIN_SCL, xGPIO_DIR_MODE_OD);
    xGPIOSDirModeSet(LCD1602_IIC_PIN_SDA, xGPIO_DIR_MODE_OD);
    xGPIOSPinWrite(LCD1602_IIC_PIN_SDA,1);
    xGPIOSPinWrite(LCD1602_IIC_PIN_SCL,1);
#endif
}

//*****************************************************************************
//
//! \brief LCD1602 initialization.
//!
//! \param ulCLK specify the IIC clock frequency, only effective in hardware IIC mode.
//!
//! The LCD1602 will be initialized as follows:
//! Device address(write) 0x20, 4bit data line, display on, back light on, cursor on,
//! double line display, auto scroll off, address counter teturn home(0).
//!
//! \return None.
//
//*****************************************************************************
void LCD1602Init(unsigned long ulCLK)
{
    IICInit(ulCLK);

    LCD1602Dev.ucDevAddr=0x27;
    LCD1602Dev.ucNumRows=2;
    LCD1602Dev.ucNumCols=16;
    IICDelay(50000);
    LCD1602IICExpandWrite(LCD1602Dev.ucBackLightEn);
    LCD1602Dev.ucBackLightEn=LCD1602IIC_BACKLIGHTON;
    LCD1602Dev.ucDispalyFunction |= LCD1602IIC_2LINE;
    IICDelay(5000);
    //
    // we start in 8bit mode, try to set 4 bit mode
    //
    LCD1602IICWrite4Bits(0x30);
    IICDelay(50000);
    LCD1602IICWrite4Bits(0x30);
    IICDelay(50000);
    LCD1602IICWrite4Bits(0x30);
    IICDelay(50000);
    //
    // set 4bit mode
    //
    LCD1602IICWrite4Bits(0x20);
    IICDelay(50000);

    LCD1602IICWriteCmd(LCD1602IIC_FUNCTIONSET | LCD1602Dev.ucDispalyFunction);
    LCD1602DisplayOn();
    LCD1602CursorOn();
    LCD1602Clear();
    LCD1602AutoScrollOff();
    LCD1602Home();
}
