//*****************************************************************************
//
//! \file hw_hd44780.h
//! \brief Character LCD HD44780 Command definition.
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

#ifndef __HW_HD44780_H__
#define __HW_HD44780_H__

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
//! \addtogroup HD44780
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HD44780_Signals HD44780 Signals
//! @{
//
//*****************************************************************************

#define HD44780_E_DISABLE       0
#define HD44780_E_ENABLE        1

#define HD44780_RS_COMMAND      0
#define HD44780_RS_DATA         1

#define HD44780_RW_WRITE        0
#define HD44780_RW_READ         1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HD44780_Instructions HD44780 Instructions
//! @{
//
//*****************************************************************************

#define HD44780_CMD_CLS         0x01

#define HD44780_CMD_RETURN_HOME 0x02

//*****************************************************************************
//
//! \addtogroup HD44780_Instruction_EMS Entry Mode Set
//! @{
//
//*****************************************************************************
#define HD44780_CMD_ENTRY_MODE_SET(ucConfig)                                  \
                                (0x04 | ucConfig )

//
// Specifies cursor move direction
//
#define HD44780_ENTRY_MODE_SET_ID                                             \
                                0x02
//
//! Cursor move direction : Increment
//
#define HD44780_ENTRY_MODE_SET_ID_INC                                         \
                                0x02

//
//! Cursor move direction : Decrement
//
#define HD44780_ENTRY_MODE_SET_ID_DEC                                         \
                                0x00

//
//! Display shift.
//
#define HD44780_ENTRY_MODE_SET_S                                              \
                                0x01

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HD44780_Instruction_DS Display On/Off Control
//! @{
//
//*****************************************************************************

#define HD44780_CMD_DISPLAY_CTRL(ucConfig)                                    \
                                (0x08 | ucConfig)

//
//! Display (D) on/off
//
#define HD44780_DISPLAY_CTRL_D  0x04

//
//! Cursor on/off (C)
//
#define HD44780_DISPLAY_CTRL_C  0x02

//
//! Blinking of cursor position character (B)
//
#define HD44780_DISPLAY_CTRL_B  0x01

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HD44780_Instruction_CDS Cursor or Display Shift
//! Moves cursor and shifts display without changing DDRAM contents.
//! @{
//
//*****************************************************************************
#define HD44780_CMD_CURSOR_DISPLAY_SHIFT(ucConfig)                            \
                                (0x10 | ucConfig)

//
//! Speicifies if display shift or cursor move
//
#define HD44780_CURSOR_DISPLAY_SHIFT_SC                                       \
                                0x08

//
//! Display shift
//
#define HD44780_CURSOR_DISPLAY_SHIFT_SC_S                                     \
                                0x08

//
//! Cursor move
//
#define HD44780_CURSOR_DISPLAY_SHIFT_SC_C                                     \
                                0x00

//
//! Specifies shift direction
//
#define HD44780_CURSOR_DISPLAY_SHIFT_RL                                       \
                                0x04

//
//! Shift to the right
//
#define HD44780_CURSOR_DISPLAY_SHIFT_RL_R                                     \
                                0x04

//
//! Shift to the left
//
#define HD44780_CURSOR_DISPLAY_SHIFT_RL_L                                     \
                                0x00


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HD44780_Instruction_FS Function Set
//! Sets interface data length (DL), number of display lines (N), and character
//!  font (F).
//! @{
//
//*****************************************************************************
#define HD44780_CMD_FUNCTION_SET(ucConfig)                                    \
                                (0x20 | ucConfig)

//
//! Interface data length
//
#define HD44780_FUNCTION_SET_DL 0x10

//
//! Interface data length is 8 bits
//
#define HD44780_FUNCTION_SET_DL_8                                             \
                                0x10

//
//! Interface data length is 4 bits
//
#define HD44780_FUNCTION_SET_DL_4                                             \
                                0x00


//
//! Display lines
//
#define HD44780_FUNCTION_SET_N  0x08

//
//! Display 2 lines
//
#define HD44780_FUNCTION_SET_N_2                                              \
                                0x08

//
//! Display 1 lines
//
#define HD44780_FUNCTION_SET_N_1                                              \
                                0x00

//
//! Character font
//
#define HD44780_FUNCTION_SET_F  0x04

//
//! Character font is 5*10
//
#define HD44780_FUNCTION_SET_F_5X10                                           \
                                0x04

//
//! Character font is 5*8
//
#define HD44780_FUNCTION_SET_F_5X8                                            \
                                0x00

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HD44780_Instruction_CGRAM_ADDR Set CGRAM Address
//! Sets CGRAM address. CGRAM data is sent and received after this setting.
//! @{
//
//*****************************************************************************
#define HD44780_CMD_CGRAM_ADDR_SET(ucAddr)                                    \
                                (0x40 | ucAddr)
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HD44780_Instruction_DDRAM_ADDR Set DDRAM Address
//! Sets DDRAM address. DDRAM data is sent and received after this setting.
//! @{
//
//*****************************************************************************
#define HD44780_CMD_DDRAM_ADDR_SET(ucAddr)                                    \
                                (0x80 | ucAddr)
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HD44780_Instruction_RD_State Read Busy Flag & Address
//! @{
//
//*****************************************************************************
#define HD44780_READ_STATE_BUSY 0x80

#define HD44780_READ_STATE_AC_M 0x4F
#define HD44780_READ_STATE_AC_S 0
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HD44780_Instruction_WR_DATA Write Data to CGRAM or DDRAM
//! @{
//
//*****************************************************************************
#define HD44780_CMD_WRITE_DATA(ucData)                                        \
                                (ucData)
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HD44780_Instruction_RD_Data Read Data from CGRAM or DDRAM
//! @{
//
//*****************************************************************************
#define HD44780_READ_DATA_M 0xFF
#define HD44780_READ_DATA_S 0
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


#endif // __HW_HD44780_H__
