//*****************************************************************************
//
//! \file hd44780.c
//! \brief Driver for Character LCD HD44780.
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
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "hw_hd44780.h"
#include "hd44780.h"
#include "cookie_cfg.h"
#include "cookie.h"

//*****************************************************************************
//
//! \brief Write data or command to the HD44780.
//!
//! \param ucRS determines if the IR or DR to select.
//!
//! The parameter of ucRS can be:
//! - HD44780_RS_COMMAND - select the IR.
//! - HD44780_RS_DATA - select the DR.
//!
//! \return None.
//
//*****************************************************************************
void 
HD44780Write(unsigned char ucRS, unsigned char ucInstruction)
{
    //
    // Check Arguments.
    //
    xASSERT((ucRS == HD44780_RS_COMMAND) || (ucRS == HD44780_RS_DATA));

    //
    // RS:Command, RW:Write, E:Enable
    //
    xGPIOSPinWrite(HD44780_PIN_RS, ucRS);
    xGPIOSPinWrite(HD44780_PIN_RW, HD44780_RW_WRITE);
    xGPIOSPinWrite(HD44780_PIN_E, HD44780_E_ENABLE);

    //
    // Output Data
    //
#if (HD44780_INTERFACE_DATA_LEN == HD44780_INTERFACE_DATA_LEN_8)    
    xGPIOSPinWrite(HD44780_PIN_D7, (ucInstruction >> 7) & 0x01);
    xGPIOSPinWrite(HD44780_PIN_D6, (ucInstruction >> 6) & 0x01);
    xGPIOSPinWrite(HD44780_PIN_D5, (ucInstruction >> 5) & 0x01);
    xGPIOSPinWrite(HD44780_PIN_D4, (ucInstruction >> 4) & 0x01);
    xGPIOSPinWrite(HD44780_PIN_D3, (ucInstruction >> 3) & 0x01);
    xGPIOSPinWrite(HD44780_PIN_D2, (ucInstruction >> 2) & 0x01);
    xGPIOSPinWrite(HD44780_PIN_D1, (ucInstruction >> 1) & 0x01);
    xGPIOSPinWrite(HD44780_PIN_D0, ucInstruction & 0x01);
#else
#if (HD44780_INTERFACE_DATA_LEN == HD44780_INTERFACE_DATA_LEN_4)  
    xGPIOSPinWrite(HD44780_PIN_D7, (ucInstruction >> 7) & 0x01);
    xGPIOSPinWrite(HD44780_PIN_D6, (ucInstruction >> 6) & 0x01);
    xGPIOSPinWrite(HD44780_PIN_D5, (ucInstruction >> 5) & 0x01);
    xGPIOSPinWrite(HD44780_PIN_D4, (ucInstruction >> 4) & 0x01);
    
    xGPIOSPinWrite(HD44780_PIN_E, HD44780_E_DISABLE);
    xSysCtlDelay(10);
    xGPIOSPinWrite(HD44780_PIN_E, HD44780_E_ENABLE);
     
    xGPIOSPinWrite(HD44780_PIN_D7, (ucInstruction >> 3) & 0x01);
    xGPIOSPinWrite(HD44780_PIN_D6, (ucInstruction >> 2) & 0x01);
    xGPIOSPinWrite(HD44780_PIN_D5, (ucInstruction >> 1) & 0x01);
    xGPIOSPinWrite(HD44780_PIN_D4, ucInstruction & 0x01);    
#endif    
#endif
    
    xSysCtlDelay(10);
    
    //
    // E:Disable
    //
    xGPIOSPinWrite(HD44780_PIN_E, HD44780_E_DISABLE);
}

//*****************************************************************************
//
//! \brief Read the state or data from the HD44780.
//!
//! \param ucRS determines if the IR or DR to select.
//!
//! The parameter of ucRS can be:
//! - HD44780_RS_COMMAND - select the IR.
//! - HD44780_RS_DATA - select the DR.
//!
//! \return None.
//
//*****************************************************************************
unsigned char 
HD44780Read(unsigned char ucRS)
{
    unsigned char ucData = 0;

    //
    // Check Arguments.
    //
    xASSERT((ucRS == HD44780_RS_COMMAND) || (ucRS == HD44780_RS_DATA));

    //
    // Set D7 - D0 direction to GPIO Input
    //
#if (HD44780_INTERFACE_DATA_LEN == HD44780_INTERFACE_DATA_LEN_8)        
    xGPIOSPinTypeGPIOInput(HD44780_PIN_D7);
    xGPIOSPinTypeGPIOInput(HD44780_PIN_D6);
    xGPIOSPinTypeGPIOInput(HD44780_PIN_D5);
    xGPIOSPinTypeGPIOInput(HD44780_PIN_D4);
    xGPIOSPinTypeGPIOInput(HD44780_PIN_D3);
    xGPIOSPinTypeGPIOInput(HD44780_PIN_D2);
    xGPIOSPinTypeGPIOInput(HD44780_PIN_D1);
    xGPIOSPinTypeGPIOInput(HD44780_PIN_D0);
#else
#if (HD44780_INTERFACE_DATA_LEN == HD44780_INTERFACE_DATA_LEN_4)        
    xGPIOSPinTypeGPIOInput(HD44780_PIN_D7);
    xGPIOSPinTypeGPIOInput(HD44780_PIN_D6);
    xGPIOSPinTypeGPIOInput(HD44780_PIN_D5);
    xGPIOSPinTypeGPIOInput(HD44780_PIN_D4);    
#endif    
#endif    

    //
    // RS:Command, RW:Write, E:Enable
    //
    xGPIOSPinWrite(HD44780_PIN_RS, ucRS);
    xGPIOSPinWrite(HD44780_PIN_RW, HD44780_RW_READ);
    xGPIOSPinWrite(HD44780_PIN_E, HD44780_E_DISABLE);
    xSysCtlDelay(10);
    xGPIOSPinWrite(HD44780_PIN_E, HD44780_E_ENABLE);

    //
    // Read the Data
    //
#if (HD44780_INTERFACE_DATA_LEN == HD44780_INTERFACE_DATA_LEN_8)    
    ucData |= xGPIOSPinRead(HD44780_PIN_D7) << 7;
    ucData |= xGPIOSPinRead(HD44780_PIN_D6) << 6;
    ucData |= xGPIOSPinRead(HD44780_PIN_D5) << 5;
    ucData |= xGPIOSPinRead(HD44780_PIN_D4) << 4;
    ucData |= xGPIOSPinRead(HD44780_PIN_D3) << 3;
    ucData |= xGPIOSPinRead(HD44780_PIN_D2) << 2;
    ucData |= xGPIOSPinRead(HD44780_PIN_D1) << 1;
    ucData |= xGPIOSPinRead(HD44780_PIN_D0) << 0;
#else
#if (HD44780_INTERFACE_DATA_LEN == HD44780_INTERFACE_DATA_LEN_4) 
    ucData |= xGPIOSPinRead(HD44780_PIN_D7) << 7;
    ucData |= xGPIOSPinRead(HD44780_PIN_D6) << 6;
    ucData |= xGPIOSPinRead(HD44780_PIN_D5) << 5;
    ucData |= xGPIOSPinRead(HD44780_PIN_D4) << 4;
    
    xGPIOSPinWrite(HD44780_PIN_E, HD44780_E_DISABLE);
    xSysCtlDelay(10);
    xGPIOSPinWrite(HD44780_PIN_E, HD44780_E_ENABLE);
    
    ucData |= xGPIOSPinRead(HD44780_PIN_D7) << 3;
    ucData |= xGPIOSPinRead(HD44780_PIN_D6) << 2;
    ucData |= xGPIOSPinRead(HD44780_PIN_D5) << 1;
    ucData |= xGPIOSPinRead(HD44780_PIN_D4) << 0;    
#endif    
#endif    
    //
    // E:Disable
    //
    xGPIOSPinWrite(HD44780_PIN_E, HD44780_E_DISABLE);

    //
    // At the End, set D7 - D0 direction to GPIO OutPut
    //
#if (HD44780_INTERFACE_DATA_LEN == HD44780_INTERFACE_DATA_LEN_8)        
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D7);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D6);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D5);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D4);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D3);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D2);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D1);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D0);
#else
#if (HD44780_INTERFACE_DATA_LEN == HD44780_INTERFACE_DATA_LEN_4)
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D7);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D6);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D5);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D4);    
#endif    
#endif
    return ucData;
}

void 
HD44780WriteCmd(unsigned char ucCmd)
{
    HD44780Write(HD44780_RS_COMMAND, ucCmd);
}

void 
HD44780WriteData(unsigned char ucData)
{
    HD44780Write(HD44780_RS_DATA, ucData);
}

//*****************************************************************************
//
//! \brief Read the state of the HD44780.
//!
//! \param None.
//!
//! The state info contains the busy flag and address count.
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
HD44780ReadState(void)
{
    return HD44780Read(HD44780_RS_COMMAND);
}

//*****************************************************************************
//
//! \brief determine if the HD44780 is busy.
//!
//! \param None.
//!
//! \return xtrue if the HD44780 is busy, xfalse if the HD44780 is idle.
//
//*****************************************************************************
xtBoolean 
HD44780Busy(void)
{
    unsigned ucState;

    //ucState = HD44780ReadState();
	  xSysCtlDelay(1000);

    return xfalse;
}

//*****************************************************************************
//
//! \brief Read data from the HD44780 DDRAM.
//!
//! \param None.
//!
//! \return data that have been read.
//
//*****************************************************************************
unsigned long 
HD44780ReadData(void)
{
    return HD44780Read(HD44780_RS_DATA);
}

//*****************************************************************************
//
//! \brief Init the HD44780 LCD Device.
//!
//! \param None.
//!
//! This function is used to Init the HD44780 Device. It must be call before 
//! any other LCD function use.
//!
//! It Open the pins's GPIO peripheral port, and config the pins type to GPIO 
//! output. Then config the LCD into the default state, clear the LCD and 
//! Open the display. Default A Blink cursor is set on. The LCD cursor move 
//! direction is config as increment default.
//!
//! The HD44780 Initial state can be determined by the \ref HD44780_Config.
//! - Pins that used is determined by \ref HD44780_Config_Pins.
//! - The inteface data length is determined by \ref HD44780_INTERFACE_DATA_LEN.
//! - The LCD display line is determined by \ref HD44780_DISPLAY_LINE.
//! - The LCD character font is determined by \ref HD44780_CHARACTER_FONT.
//! .
//! 
//! \return None.
//
//*****************************************************************************
void 
HD44780Init(void)
{   
    //
    // Enable GPIO Port that used
    //
#if (HD44780_INTERFACE_DATA_LEN == HD44780_INTERFACE_DATA_LEN_8)    
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HD44780_PIN_D7));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HD44780_PIN_D6));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HD44780_PIN_D5));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HD44780_PIN_D4));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HD44780_PIN_D3));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HD44780_PIN_D2));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HD44780_PIN_D1));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HD44780_PIN_D0));
#else
#if (HD44780_INTERFACE_DATA_LEN == HD44780_INTERFACE_DATA_LEN_4)    
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HD44780_PIN_D7));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HD44780_PIN_D6));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HD44780_PIN_D5));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HD44780_PIN_D4)); 
#endif
#endif    
    
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HD44780_PIN_E));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HD44780_PIN_RS));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(HD44780_PIN_RW)); 
     
    //
    // Set Pins Type to GPIO Output
    //
#if (HD44780_INTERFACE_DATA_LEN == HD44780_INTERFACE_DATA_LEN_8)        
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D7);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D6);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D5);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D4);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D3);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D2);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D1);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D0);
#else
#if (HD44780_INTERFACE_DATA_LEN == HD44780_INTERFACE_DATA_LEN_4)   
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D7);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D6);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D5);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_D4);    
#endif    
#endif 
    
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_E);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_RS);
    xGPIOSPinTypeGPIOOutput(HD44780_PIN_RW);

    //
    // Output default value : E disable
    //
    xGPIOSPinWrite(HD44780_PIN_E, HD44780_E_DISABLE);

    //
    // Set Entry Mode: Interface Data Length, Character Font, Display Line
    //
    while(HD44780Busy()); 
#if (defined(HD44780_DISPLAY_LINE) && (HD44780_DISPLAY_LINE == 2))
    HD44780WriteCmd(HD44780_CMD_FUNCTION_SET(HD44780_INTERFACE_DATA_LEN | 
                                             HD44780_FUNCTION_SET_N_2 |
                                             HD44780_CHARACTER_FONT));
#endif
    
#if (defined(HD44780_DISPLAY_LINE) && (HD44780_DISPLAY_LINE == 1))    
    HD44780WriteCmd(HD44780_CMD_FUNCTION_SET(HD44780_INTERFACE_DATA_LEN | 
                                             HD44780_FUNCTION_SET_N_1 |
                                             HD44780_CHARACTER_FONT));
#endif    
    
    //
    // Display on & Cursor Blink
    //
    while(HD44780Busy());
    HD44780WriteCmd(HD44780_CMD_DISPLAY_CTRL(HD44780_DISPLAY_CTRL_D |
                                             0 |
                                             HD44780_DISPLAY_CTRL_B));

    //
    // Clear LCD
    //    
    while(HD44780Busy());
    HD44780WriteCmd(HD44780_CMD_CLS);

    //
    // Cursor Move Mode: Increment
    //
    while(HD44780Busy());
    HD44780WriteCmd(HD44780_CMD_ENTRY_MODE_SET(HD44780_ENTRY_MODE_SET_ID_INC | 
                                               0));
    
}

//*****************************************************************************
//
//! \brief Set the the LCD entry mode.
//!
//! \param ucCursorMoveDirection is the cursor move dirction.
//! \param bDisplayShift determines if the entire LCD shift when display a char.
//!
//! In the HD44780Init() function, it has set a default entry mode. The cursor
//! move direction is increment and no shift when display. You can change the 
//! setting with this function.
//!
//! The parameter of ucCursorMoveDirection can be:
//! - \ref HD44780_MOVE_DIRECTION_INC - increment
//! - \ref HD44780_MOVE_DIRECTION_DEC - decrment.
//! .
//! The parameter of bDisplayShift cab be:
//! - xtrue - display with shift.
//! - xfalse - no shift wen display.
//! .
//!
//! \return None.
//
//*****************************************************************************
void 
HD44780EntryModeSet(unsigned char ucCursorMoveDirection, 
                    xtBoolean bDisplayShift)
{
    unsigned char ucDisplayShiftCmd;
    
    xASSERT((ucCursorMoveDirection == HD44780_MOVE_DIRECTION_INC) || 
            (ucCursorMoveDirection == HD44780_MOVE_DIRECTION_DEC));
    
    ucDisplayShiftCmd = (bDisplayShift ? HD44780_ENTRY_MODE_SET_S : 0);
    
    while(HD44780Busy());
    HD44780WriteCmd(HD44780_CMD_ENTRY_MODE_SET(ucCursorMoveDirection | 
                                               ucDisplayShiftCmd));    
}

//*****************************************************************************
//
//! \brief Clears the LCD display.
//!
//! \param None.
//!
//! It clears the entire display, and set cursor to (0,0).
//!
//! \return None.
//
//*****************************************************************************
void 
HD44780DisplayClear(void)
{
    while(HD44780Busy());
    //
    // Clear LCD
    //
    HD44780WriteCmd(HD44780_CMD_CLS); 
    
	  xSysCtlDelay(10000);
}

//*****************************************************************************
//
//! \brief Sets the entire LCD display on.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void 
HD44780DisplayOn(void)
{
    while(HD44780Busy());
    HD44780WriteCmd(HD44780_CMD_DISPLAY_CTRL(HD44780_DISPLAY_CTRL_D));    
}

//*****************************************************************************
//
//! \brief Sets the entire LCD display off.
//!
//! \param None.
//! 
//! It set the entire display to blank without changing the data that have been
//! written into the LCD DDRAM.
//!
//! \return None.
//
//*****************************************************************************
void 
HD44780DisplayOff(void)
{
    while(HD44780Busy());
    HD44780WriteCmd(HD44780_CMD_DISPLAY_CTRL(0));     
}

//*****************************************************************************
//
//! \brief Sets cursor on.
//!
//! \param bBlink determines the cursor style. xtrue is an blinking style, 
//! xfalse is an underline style.
//!
//! \return None.
//
//*****************************************************************************
void 
HD44780CursorOn(xtBoolean bBlink)
{
    unsigned char ucBlink = (bBlink ? HD44780_DISPLAY_CTRL_B : 0);
    
    while(HD44780Busy());
    HD44780WriteCmd(HD44780_CMD_DISPLAY_CTRL(HD44780_DISPLAY_CTRL_D |
                                             HD44780_DISPLAY_CTRL_C |
                                             ucBlink));        
}

//*****************************************************************************
//
//! \brief Sets cursor off.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void 
HD44780CursorOff(void)
{
    while(HD44780Busy());
    HD44780WriteCmd(HD44780_CMD_DISPLAY_CTRL(HD44780_DISPLAY_CTRL_D |
                                             ~HD44780_DISPLAY_CTRL_C |
                                             ~HD44780_DISPLAY_CTRL_B));        
}

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
void 
HD44780DisplayString(const char* pcString)
{
    int i = 0;
    
    xASSERT(pcString != 0);
    
    while(i < 80 && pcString[i] != 0)
    {
        while(HD44780Busy());
        HD44780WriteData(pcString[i]);
        i++;
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
void 
HD44780DisplayN(unsigned long n)
{
    char pcBuf[16], *p;

    if (n == 0)
    {
        while(HD44780Busy());
        HD44780WriteData('0');
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
            while(HD44780Busy());
            HD44780WriteData(*--p);   
        }
    }
}

//*****************************************************************************
//
//! \brief Cursor back to Home.
//!
//! \param None.
//!
//! Sets Location at (0, 0). Also returns display from being
//! shifted to original position. DDRAM contents remain unchanged.
//!
//! \return None.
//
//*****************************************************************************
void 
HD44780Home(void)
{
    while(HD44780Busy());    
    HD44780WriteCmd(HD44780_CMD_RETURN_HOME);    
}

//*****************************************************************************
//
//! \brief Set the cursor location.
//!
//! \param x is the character index.
//! \param y is the line number.
//!
//! The default location is (0,0). After set the location, the strings will
//! display at the (x, y).
//!
//! \return None.
//
//*****************************************************************************
void 
HD44780LocationSet(unsigned char x, unsigned char y)
{
    unsigned char ulAddr = 0;
     
    xASSERT(x < HD44780_DISPLAY_CHARACTER);
    xASSERT(y < HD44780_DISPLAY_LINE);    

#if (defined(HD44780_DISPLAY_LINE) && HD44780_DISPLAY_LINE == 1)
    ulAddr = x;
#endif
    
#if (defined(HD44780_DISPLAY_LINE) && HD44780_DISPLAY_LINE == 2)
    ulAddr = 0x40 * y + x;  
#endif
    
    xASSERT(ulAddr < 80);

    //
    // Set the DDRAM address.
    //    
    while(HD44780Busy());    
    HD44780WriteCmd(HD44780_CMD_DDRAM_ADDR_SET(ulAddr));
}

//*****************************************************************************
//
//! \brief Move the cursor n unit to the left.
//!
//! \param n is the unit number to move.
//!
//! \return None.
//
//*****************************************************************************
void 
HD44780CursorLeftMove(unsigned char n)
{
    int i = n;
    
    while(i--)
    {
        //
        // Move the cursor 1 unit left 
        //
        while(HD44780Busy());
        HD44780WriteCmd(HD44780_CMD_CURSOR_DISPLAY_SHIFT(
                                        HD44780_CURSOR_DISPLAY_SHIFT_SC_C |
                                        HD44780_CURSOR_DISPLAY_SHIFT_RL_L));
    }
}


//*****************************************************************************
//
//! \brief Move the cursor n unit to the right.
//!
//! \param n is the unit number to move.
//!
//! \return None.
//
//*****************************************************************************
void 
HD44780CursorRightMove(unsigned char n)
{
    int i = n;
    
    while(i--)
    {
        //
        // Move the cursor 1 unit right 
        //
        while(HD44780Busy());
        HD44780WriteCmd(HD44780_CMD_CURSOR_DISPLAY_SHIFT(
                                        HD44780_CURSOR_DISPLAY_SHIFT_SC_C |
                                        HD44780_CURSOR_DISPLAY_SHIFT_RL_R));
    }
}

//*****************************************************************************
//
//! \brief Shift the entire display  n unit to the left.
//!
//! \param n is the unit number to shift.
//!
//! \return None.
//
//*****************************************************************************
void 
HD44780DisplayLeftShift(unsigned char n)
{
    int i = n;
    
    while(i--)
    {
        while(HD44780Busy());
        HD44780WriteCmd(HD44780_CMD_CURSOR_DISPLAY_SHIFT(
                                        HD44780_CURSOR_DISPLAY_SHIFT_SC_S |
                                        HD44780_CURSOR_DISPLAY_SHIFT_RL_L));
    }    
}

//*****************************************************************************
//
//! \brief Shift the entire display  n unit to the right.
//!
//! \param n is the unit number to shift.
//!
//! \return None.
//
//*****************************************************************************
void 
HD44780DisplayRightShift(unsigned char n)
{
    int i = n;
    
    while(i--)
    {
        while(HD44780Busy());
        HD44780WriteCmd(HD44780_CMD_CURSOR_DISPLAY_SHIFT(
                                        HD44780_CURSOR_DISPLAY_SHIFT_SC_S |
                                        HD44780_CURSOR_DISPLAY_SHIFT_RL_R));
    }    
}
