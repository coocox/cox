//*****************************************************************************
//
//! \file splc780d.c
//! \brief Driver for Character LCD SPLC780D.
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
#include "xhw_i2c.h"
#include "xi2c.h"
#include "hw_splc780d.h"
#include "splc780d.h"

static unsigned char ucBacklightState = SPLC780_BL_OPEN;

//*****************************************************************************
//
//! \brief Write 4-bit data or command to the SPLC780D through PCA8574.
//!
//! \param ucRS determines if the IR or DR to select.
//!
//! \return None.
//
//*****************************************************************************
void 
SPLC780Write4Bit(unsigned char ucDat)
{
    ucDat = ucDat | ucBacklightState | SPLC780_RW_WRITE;

    //
    //! input the 4-bit data 
    //
    xI2CMasterWriteS1(ulMaster, SPLC780_I2C_Addr, ucDat, xfalse);
	
    //
    //! latch the 4-bit data
    //
    xI2CMasterWriteS2(ulMaster, (ucDat | SPLC780_E_ENABLE), xfalse);
    xSysCtlDelay(200);
    xI2CMasterWriteS2(ulMaster, (ucDat | SPLC780_E_DISABLE), xtrue); 
}
//*****************************************************************************
//
//! \brief Write data or command to the SPLC780D.
//!
//! \param ucRS determines if the IR or DR to select.
//!
//! The parameter of ucRS can be:
//! - \ref SPLC780_RS_COMMAND - select the IR.
//! - \ref SPLC780_RS_DATA - select the DR.
//!
//! \return None.
//
//*****************************************************************************
void 
SPLC780Write(unsigned char ucRS, unsigned char ucInstruction)
{
    //
    // Check Arguments.
    //
    xASSERT((ucRS == SPLC780_RS_COMMAND) || (ucRS == SPLC780_RS_DATA));

    SPLC780Write4Bit((ucInstruction & 0xf0) | ucRS);
    SPLC780Write4Bit(((ucInstruction << 4) & 0xf0) | ucRS);
}

//*****************************************************************************
//
//! \brief Read the state or data from the SPLC780D.
//!
//! \param ucRS determines if the IR or DR to select.
//!
//! The parameter of ucRS can be:
//! - \ref SPLC780_RS_COMMAND - select the IR.
//! - \ref SPLC780_RS_DATA - select the DR.
//!
//! \return None.
//
//*****************************************************************************
unsigned char 
SPLC780Read(unsigned char ucRS)
{
    unsigned char ucTemp, ucData = 0;

    //
    // Check Arguments.
    //
    xASSERT((ucRS == SPLC780_RS_COMMAND) || (ucRS == SPLC780_RS_DATA));

    //
    // RS:Command, RW:Write, E:Enable
    //
    ucTemp = (ucRS | SPLC780_RW_READ | SPLC780_E_DISABLE | ucBacklightState);
    xI2CMasterWriteS1(ulMaster, SPLC780_I2C_Addr, ucTemp, xfalse);
    xSysCtlDelay(20);
    ucTemp = (ucRS | SPLC780_RW_READ | SPLC780_E_ENABLE | ucBacklightState);
    xI2CMasterWriteS2(ulMaster, ucTemp, xfalse);

    //
    // Read the Data
    //
    xI2CMasterReadS2(ulMaster, &ucData, xfalse);

	
    ucTemp = (ucRS | SPLC780_RW_READ | SPLC780_E_DISABLE | ucBacklightState);
    xI2CMasterWriteS2(ulMaster, ucTemp, xfalse);
    xSysCtlDelay(20);
    ucTemp = (ucRS | SPLC780_RW_READ | SPLC780_E_ENABLE | ucBacklightState);
    xI2CMasterWriteS2(ulMaster, ucTemp, xfalse);

    //
    // Read the Data
    //
    xI2CMasterReadS2(ulMaster, &ucTemp, xtrue);
    
    ucData = ((ucData << 4) & 0xf0) | (ucTemp & 0x0f);
	
    return ucData;
}

void 
SPLC780WriteCmd(unsigned char ucCmd)
{
    SPLC780Write(SPLC780_RS_COMMAND, ucCmd);
}

void 
SPLC780WriteData(unsigned char ucData)
{
    SPLC780Write(SPLC780_RS_DATA, ucData);
}

//*****************************************************************************
//
//! \brief Read the state of the SPLC780D.
//!
//! \param None.
//!
//! The state info contains the busy flag and address count.
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
SPLC780ReadState(void)
{
    return SPLC780Read(SPLC780_RS_COMMAND);
}

//*****************************************************************************
//
//! \brief determine if the SPLC780D is busy.
//!
//! \param None.
//!
//! \return xtrue if the SPLC780D is busy, xfalse if the SPLC780D is idle.
//
//*****************************************************************************
xtBoolean 
SPLC780Busy(void)
{
    unsigned char ucState = 0;

    ucState = SPLC780ReadState();

    return (ucState & SPLC780_READ_STATE_BUSY) ? xtrue : xfalse;
}

//*****************************************************************************
//
//! \brief Read data from the SPLC780 DDRAM.
//!
//! \param None.
//!
//! \return data that have been read.
//
//*****************************************************************************
unsigned long 
SPLC780ReadData(void)
{
    return SPLC780Read(SPLC780_RS_DATA);
}

//*****************************************************************************
//
//! \brief Open or Close the backlight light.
//!
//! \param ucNewState is the backlight's state.
//!  - \ref SPLC780_BL_CLOSE  -turn off the backlight
//!  - \ref SPLC780_BL_OPEN   -turn on the backlight
//!
//! \return None.
//
//*****************************************************************************
void 
SPLC780SetBacklight(unsigned char ucNewState)
{
    xASSERT((ucNewState == SPLC780_BL_CLOSE) || (ucNewState == SPLC780_BL_OPEN));
	
    ucBacklightState = ucNewState;
    xI2CMasterWriteS1(ulMaster, SPLC780_I2C_Addr, ucNewState, xtrue);
}

//*****************************************************************************
//
//! \brief Init the SPLC780D LCD Device.
//!
//! \param None.
//!
//! This function is used to Init the SPLC780 Device. It must be call before 
//! any other LCD function use.
//!
//! It Open the pins's GPIO peripheral port, and config the pins type to GPIO 
//! output. Then config the LCD into the default state, clear the LCD and 
//! Open the display. Default A Blink cursor is set on. The LCD cursor move 
//! direction is config as increment default.
//!
//! The SPLC780 Initial state can be determined by the \ref SPLC780_Config.
//! - Pins that used is determined by \ref SPLC780D_Config_Pins.
//! - The inteface data length is determined by \ref SPLC780D_INTERFACE_DATA_LEN.
//! - The LCD display line is determined by \ref SPLC780D_DISPLAY_LINE.
//! - The LCD character font is determined by \ref SPLC780D_CHARACTER_FONT.
//! .
//! 
//! \return None.
//
//*****************************************************************************
void 
SPLC780Init(void)
{ 
    //
    // Enable and Configure I2C that used
    //
    xSysCtlPeripheralEnable2(ulMaster);

    xSysCtlPeripheralEnable2(GPIOB_BASE);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    
    xSPinTypeI2C(I2C1SCK, PB6);
    xSPinTypeI2C(I2C1SDA, PB7);

    xI2CMasterInit(ulMaster, 400000);
    //
    // I2C enable
    //
    xI2CMasterEnable(ulMaster); 

    SPLC780Write4Bit(0x30);
    xSysCtlDelay(720000);    // Wait time > 4.1 ms
    SPLC780Write4Bit(0x30);
    xSysCtlDelay(200);       // Wait time > 100 us
    SPLC780Write4Bit(0x30);
    xSysCtlDelay(200);
		
		while(SPLC780Busy());    // BF can be checked after the following instructions
    SPLC780Write4Bit(0x20);
		
    //
    // Set Entry Mode: Interface Data Length, Character Font, Display Line
    //
    while(SPLC780Busy()); 
#if (defined(SPLC780_DISPLAY_LINE) && (SPLC780_DISPLAY_LINE == 2))
    SPLC780WriteCmd(SPLC780_CMD_FUNCTION_SET(SPLC780_INTERFACE_DATA_LEN | 
                                             SPLC780_FUNCTION_SET_N_2 |
                                             SPLC780_CHARACTER_FONT)); // 0x28
#endif
    
#if (defined(SPLC780_DISPLAY_LINE) && (SPLC780_DISPLAY_LINE == 1))    
    SPLC780WriteCmd(SPLC780_CMD_FUNCTION_SET(SPLC780_INTERFACE_DATA_LEN | 
                                             SPLC780_FUNCTION_SET_N_1 |
                                             SPLC780_CHARACTER_FONT)); // 0x20
#endif    
    
    //
    // Display on & Cursor Blink
    //
    while(SPLC780Busy());
    SPLC780WriteCmd(SPLC780_CMD_DISPLAY_CTRL(SPLC780_DISPLAY_CTRL_D |
                                             0 |
                                             SPLC780_DISPLAY_CTRL_B)); //0x0d

    //
    // Clear LCD
    //    
    while(SPLC780Busy());
    SPLC780WriteCmd(SPLC780_CMD_CLS); //0x01

    //
    // Cursor Move Mode: Increment
    //
    while(SPLC780Busy());
    SPLC780WriteCmd(SPLC780_CMD_ENTRY_MODE_SET(SPLC780_ENTRY_MODE_SET_ID_INC | 0)); //0x06  
}

//*****************************************************************************
//
//! \brief Set the the LCD entry mode.
//!
//! \param ucCursorMoveDirection is the cursor move dirction.
//! \param bDisplayShift determines if the entire LCD shift when display a char.
//!
//! In the SPLC780Init() function, it has set a default entry mode. The cursor
//! move direction is increment and no shift when display. You can change the 
//! setting with this function.
//!
//! The parameter of ucCursorMoveDirection can be:
//! - \ref SPLC780_MOVE_DIRECTION_INC - increment
//! - \ref SPLC780_MOVE_DIRECTION_DEC - decrment.
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
SPLC780EntryModeSet(unsigned char ucCursorMoveDirection, 
                    xtBoolean bDisplayShift)
{
    unsigned char ucDisplayShiftCmd;
    
    xASSERT((ucCursorMoveDirection == SPLC780_MOVE_DIRECTION_INC) || 
            (ucCursorMoveDirection == SPLC780_MOVE_DIRECTION_DEC));
    
    ucDisplayShiftCmd = (bDisplayShift ? SPLC780_ENTRY_MODE_SET_S : 0);
    
    while(SPLC780Busy());
    SPLC780WriteCmd(SPLC780_CMD_ENTRY_MODE_SET(ucCursorMoveDirection | 
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
SPLC780DisplayClear(void)
{
    while(SPLC780Busy());
    //
    // Clear LCD
    //
    SPLC780WriteCmd(SPLC780_CMD_CLS);  
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
SPLC780DisplayOn(void)
{
    while(SPLC780Busy());
    SPLC780WriteCmd(SPLC780_CMD_DISPLAY_CTRL(SPLC780_DISPLAY_CTRL_D));    
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
SPLC780DisplayOff(void)
{
    while(SPLC780Busy());
    SPLC780WriteCmd(SPLC780_CMD_DISPLAY_CTRL(0));     
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
SPLC780CursorOn(xtBoolean bBlink)
{
    unsigned char ucBlink = (bBlink ? SPLC780_DISPLAY_CTRL_B : 0);
    
    while(SPLC780Busy());
    SPLC780WriteCmd(SPLC780_CMD_DISPLAY_CTRL(SPLC780_DISPLAY_CTRL_D |
                                             SPLC780_DISPLAY_CTRL_C |
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
SPLC780CursorOff(void)
{
    while(SPLC780Busy());
    SPLC780WriteCmd(SPLC780_CMD_DISPLAY_CTRL(SPLC780_DISPLAY_CTRL_D |
                                             ~SPLC780_DISPLAY_CTRL_C |
                                             ~SPLC780_DISPLAY_CTRL_B));        
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
SPLC780DisplayString(const char* pcString)
{
    int i = 0;
    
    xASSERT(pcString != 0);
    
    while(i < 80 && pcString[i] != 0)
    {
        while(SPLC780Busy());
        SPLC780WriteData(pcString[i]);
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
SPLC780DisplayN(unsigned long n)
{
    char pcBuf[16], *p;

    if (n == 0)
    {
        while(SPLC780Busy());
        SPLC780WriteData('0');
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
            while(SPLC780Busy());
            SPLC780WriteData(*--p);   
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
SPLC780Home(void)
{
    while(SPLC780Busy());    
    SPLC780WriteCmd(SPLC780_CMD_RETURN_HOME);    
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
SPLC780LocationSet(unsigned char x, unsigned char y)
{
    unsigned char ulAddr = 0;
     
    xASSERT(x < SPLC780_DISPLAY_CHARACTER);
    xASSERT(y < SPLC780_DISPLAY_LINE);    

#if (defined(SPLC780_DISPLAY_LINE) && SPLC780_DISPLAY_LINE == 1)
    ulAddr = x;
#endif
    
#if (defined(SPLC780_DISPLAY_LINE) && SPLC780_DISPLAY_LINE == 2)
    ulAddr = 0x40 * y + x;  
#endif
    
    xASSERT(ulAddr < 80);

    //
    // Set the DDRAM address.
    //    
    while(SPLC780Busy());    
    SPLC780WriteCmd(SPLC780_CMD_DDRAM_ADDR_SET(ulAddr));
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
SPLC780CursorLeftMove(unsigned char n)
{
    int i = n;
    
    while(i--)
    {
        //
        // Move the cursor 1 unit left 
        //
        while(SPLC780Busy());
        SPLC780WriteCmd(SPLC780_CMD_CURSOR_DISPLAY_SHIFT(
                                        SPLC780_CURSOR_DISPLAY_SHIFT_SC_C |
                                        SPLC780_CURSOR_DISPLAY_SHIFT_RL_L));
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
SPLC780CursorRightMove(unsigned char n)
{
    int i = n;
    
    while(i--)
    {
        //
        // Move the cursor 1 unit right 
        //
        while(SPLC780Busy());
        SPLC780WriteCmd(SPLC780_CMD_CURSOR_DISPLAY_SHIFT(
                                        SPLC780_CURSOR_DISPLAY_SHIFT_SC_C |
                                        SPLC780_CURSOR_DISPLAY_SHIFT_RL_R));
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
SPLC780DisplayLeftShift(unsigned char n)
{
    int i = n;
    
    while(i--)
    {
        while(SPLC780Busy());
        SPLC780WriteCmd(SPLC780_CMD_CURSOR_DISPLAY_SHIFT(
                                        SPLC780_CURSOR_DISPLAY_SHIFT_SC_S |
                                        SPLC780_CURSOR_DISPLAY_SHIFT_RL_L));
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
SPLC780DisplayRightShift(unsigned char n)
{
    int i = n;
    
    while(i--)
    {
        while(SPLC780Busy());
        SPLC780WriteCmd(SPLC780_CMD_CURSOR_DISPLAY_SHIFT(
                                        SPLC780_CURSOR_DISPLAY_SHIFT_SC_S |
                                        SPLC780_CURSOR_DISPLAY_SHIFT_RL_R));
    }    
}
