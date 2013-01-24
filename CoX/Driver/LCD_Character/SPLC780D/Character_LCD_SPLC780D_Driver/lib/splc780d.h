//*****************************************************************************
//
//! \file splc780d.h
//! \brief Prototypes for Character LCD SPLC780 Driver.
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

#ifndef __SPLC780D_H__
#define __SPLC780D_H__

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
//! \addtogroup LCD_Character
//! @{
//
//*****************************************************************************    
    
//*****************************************************************************
//
//! \addtogroup SPLC780D
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SPLC780D_Config SPLC780D Driver Configurtion
//!
//! \brief Configurtions such as the GPIO Pin used should be set before using
//! this driver.
//!    
//! @{
//
//*****************************************************************************

//
//!
//
#define SPLC780_INTERFACE_I2C   SPLC780_HARDWARE_I2C

//*****************************************************************************
//
//! \addtogroup SPLC780D_Config_Pins SPLC780D Driver Pin Configurtion
//!
//! \brief Configure the LCD i2c interface.
//!    
//! @{
//
//***************************************************************************** 

//
//!
//
#define SPLC780_HARDWARE_I2C    1

//
//!
//
#define SPLC780_SOFTWARE_I2C    0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SPLC780D_Config_Pins SPLC780D Driver Pin Configurtion
//!
//! \brief GPIO Pins Configurtions that communication with the LCD should be 
//! set before using this driver.
//!    
//! @{
//
//*****************************************************************************    
#define SPLC780_I2C_Addr 0x27

#if (SPLC780_INTERFACE_I2C == SPLC780_HARDWARE_I2C)
#define ulMaster  I2C1_BASE

#else
#if(SPLC780_INTERFACE_I2C == SPLC780_SOFTWARE_I2C)
#define SPLC780_PIN_SDA
#define SPLC780_PIN_SCL
#endif
#endif  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SPLC780D_Config_Module SPLC780D Driver LCD Moudle Configurtion
//!
//! \brief Configure the LCD moudle. such as 1602, 1601, 20*2. 
//! set before using this driver.
//!    
//! @{
//
//*****************************************************************************
//
//! The LCD Display Line, can be \b 1 or \b 2.
//
#define SPLC780_DISPLAY_LINE    2

//
//! The LCD Character number, can be 8, 16, 20, 40, 80
//
#define SPLC780_DISPLAY_CHARACTER                                             \
                                40 
//*****************************************************************************
//
//! @}
//
//*****************************************************************************                                 

//*****************************************************************************
//
//! \addtogroup SPLC780D_Config_Function SPLC780D Driver Function Configurtion
//!
//! \brief Configure the LCD character font, interface data length.
//!    
//! @{
//
//*****************************************************************************
//
//! The LCD display character font.
//!
//! Can be set to:
//! - SPLC780_CHARACTER_FONT_5X8 - font is 5*8.
//! - SPLC780_CHARACTER_FONT_5X10 - font is 5*10.
//! .
//
#define SPLC780_CHARACTER_FONT  SPLC780_CHARACTER_FONT_5X8

//
//! The LCD interface data length.
//!
//! Can be set to:
//! - \ref SPLC780_INTERFACE_DATA_LEN_8 - data length is 8 bits.
//! - \ref SPLC780_INTERFACE_DATA_LEN_4 - data length is 4 bits.
//! .
//! More info refrence \ref SPLC780_Config_Interface_DL.
//
#define SPLC780_INTERFACE_DATA_LEN                                            \
                                SPLC780_INTERFACE_DATA_LEN_4

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
//! \addtogroup SPLC780D_Entry_Mode Cursor Move Direction
//!
//! \brief Directions that cursor move to. 
//!    
//! @{
//
//*****************************************************************************
//
//! Cursor move dirction is increment
//
#define SPLC780_MOVE_DIRECTION_INC                                            \
                                0x02
//
//! Cursor move dirction is decrement
//
#define SPLC780_MOVE_DIRECTION_DEC                                            \
                                0x00
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SPLC780D_Character_Font Character Font
//!
//! \brief SPLC780 Chracter Font setting. 
//!    
//! @{
//
//*****************************************************************************

//
//! Character font is 5*10
//
#define SPLC780_CHARACTER_FONT_5X10                                           \
                                0x04
//
//! Character font is 5*8
//
#define SPLC780_CHARACTER_FONT_5X8                                            \
                                0x00

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SPLC780D_Config_Interface_DL Interface Data Length
//!
//! \brief SPLC780 Interface Data Length setting. 
//!    
//! @{
//
//*****************************************************************************
//
//! Interface data length is 8 bit, use [D7-D0].
//
#define SPLC780_INTERFACE_DATA_LEN_8                                          \
                                0x10
//
//! Interface data length is 4 bit, only use [D7-D4].
//
#define SPLC780_INTERFACE_DATA_LEN_4                                          \
                                0x00
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SPLC780D_Exported_APIs  SPLC780D Driver APIs
//! \brief API Refrence of SPLC780 Driver.
//! @{
//
//*****************************************************************************
extern void SPLC780Init(void);

extern void SPLC780SetBacklight(unsigned char ucNewState);
extern void SPLC780EntryModeSet(unsigned char ucCursorMoveDirection, 
                                xtBoolean bDisplayShift);
extern void SPLC780DisplayClear(void);

extern void SPLC780DisplayOn(void);
extern void SPLC780DisplayOff(void);
extern void SPLC780CursorOn(xtBoolean bBlink);
extern void SPLC780CursorOff(void);

extern void SPLC780DisplayString(const char* pcString);
extern void SPLC780DisplayN(unsigned long n);

extern void SPLC780Home(void);
extern void SPLC780LocationSet(unsigned char x, unsigned char y);

extern void SPLC780CursorLeftMove(unsigned char n);
extern void SPLC780CursorRightMove(unsigned char n);
extern void SPLC780DisplayLeftShift(unsigned char n);
extern void SPLC780DisplayRightShift(unsigned char n);

//
// If the LCD API can not meet your need, you can use the API below operated 
// on the lowlayer.
//
extern xtBoolean SPLC780Busy(void);
extern void SPLC780WriteCmd(unsigned char ucCmd);
extern void SPLC780WriteData(unsigned char ucData);
extern unsigned long SPLC780ReadState(void);
extern unsigned long SPLC780ReadData(void);

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

#endif //__SPLC780D_H__
