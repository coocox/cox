//*****************************************************************************
//
//! \file hw_LCD1602IIC.h
//! \brief Character LCD LCD1602 IIC Command definition.
//! \version 2.1.1.0
//! \date 1/15/2012
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
#ifndef __XHW_LCD1602IIC_H__
#define __XHW_LCD1602IIC_H__

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
//! \addtogroup LCD1602_With_PCA8574_I2C
//! @{
//
//*****************************************************************************
//*****************************************************************************
//
//! \addtogroup LCD1602_I2C LCD1602_IIC Signals
//! @{
//
//*****************************************************************************

#define EN 4  // Enable bit
#define RW 2  // Read/Write bit
#define RS 1  // Register select bit
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LCD1602_I2C_Instructions LCD1602_IIC Instructions
//! @{
//
//*****************************************************************************
#define LCD1602IIC_CLEARDISPLAY 0x01
#define LCD1602IIC_RETURNHOME 0x02
#define LCD1602IIC_ENTRYMODESET 0x04
#define LCD1602IIC_DISPLAYCONTROL 0x08
#define LCD1602IIC_CURSORSHIFT 0x10
#define LCD1602IIC_FUNCTIONSET 0x20
#define LCD1602IIC_SETCGRAMADDR 0x40
#define LCD1602IIC_SETDDRAMADDR 0x80
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LCD1602_I2C_Entry_Mode LCD1602_IIC Flags For Display Entry Mode
//! @{
//
//*****************************************************************************
#define LCD1602IIC_ENTRYRIGHT 0x00
#define LCD1602IIC_ENTRYLEFT 0x02
#define LCD1602IIC_ENTRYSHIFTINC 0x01
#define LCD1602IIC_ENTRYSHIFTDEC 0x00
#define LCD1602IIC_8BITMODE 0x10
#define LCD1602IIC_4BITMODE 0x00
#define LCD1602IIC_2LINE 0x08
#define LCD1602IIC_1LINE 0x00
#define LCD1602IIC_5x10DOTS 0x04
#define LCD1602IIC_5x8DOTS 0x00
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LCD1602_I2C_Display_Control LCD1602_IIC Flags For Display On/Off Control
//! @{
//
//*****************************************************************************
#define LCD1602IIC_DISPLAYON 0x04
#define LCD1602IIC_DISPLAYOFF 0x00
#define LCD1602IIC_CURSORON 0x02
#define LCD1602IIC_CURSOROFF 0x00
#define LCD1602IIC_BLINKON 0x01
#define LCD1602IIC_BLINKOFF 0x00
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LCD1602_I2C_Cursor_Move LCD1602_IIC Flags For Display/Cursor Shift
//! @{
//
//*****************************************************************************
#define LCD1602IIC_DISPLAYMOVE 0x08
#define LCD1602IIC_CURSORMOVE 0x00
#define LCD1602IIC_MOVERIGHT 0x04
#define LCD1602IIC_MOVELEFT 0x00
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LCD1602_I2C_BackLight LCD1602_IIC Flags For Back Light Control
//! @{
//
//*****************************************************************************
#define LCD1602IIC_BACKLIGHTON 0x08
#define LCD1602IIC_BACKLIGHTOFF 0x00
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//! @}
//! @}
//! @}
//
//*****************************************************************************
#endif
