//*****************************************************************************
//
//! \file hd44780.h
//! \brief Prototypes for Character LCD HD44780 Driver.
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

#ifndef __LCDSHIELD_H__
#define __LCDSHIELD_H__

#include "hd44780.h"

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
//! \addtogroup CoX_Shield_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LCD Shield
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LCD_Shield_Exported_APIs  LCD Shield Driver APIs
//! \brief API Refrence of LCD Shield Driver.
//! @{
//
//*****************************************************************************
#define LCDShieldInit()                                                       \
        do                                                                    \
        {                                                                     \
         HD44780Init();                                                       \
         KeypadButtonInit();                                                        \
        }                                                                     \
        while(0)

#define LCDShieldEntryModeSet(ucCursorMoveDirection, bDisplayShift)           \
				HD44780EntryModeSet(ucCursorMoveDirection, bDisplayShift)

#define LCDShieldDisplayClear()                                               \
				HD44780DisplayClear()				

#define LCDShieldDisplayOn()                                                  \
				HD44780DisplayOn()

#define LCDShieldDisplayOff()                                                 \
				HD44780DisplayOff()

#define LCDShieldCursorOn(bBlink)                                             \
				HD44780CursorOn(bBlink)

#define LCDShieldCursorOff()                                                  \
				HD44780CursorOff()

#define LCDShieldDisplayString(pcString)                                      \
				HD44780DisplayString(pcString)

#define LCDShieldDisplayN(n)                                                  \
				HD44780DisplayN(n)

#define LCDShieldHome()                                                       \
				HD44780Home()				

#define LCDShieldLocationSet(x, y)                                            \
				HD44780LocationSet(x, y)

#define LCDShieldCursorLeftMove(n)                                            \
				HD44780CursorLeftMove(n)

#define LCDShieldCursorRightMove(n)                                           \
				HD44780CursorRightMove(n)

#define LCDShieldDisplayLeftShift(n)                                          \
				HD44780DisplayLeftShift(n)

#define LCDShieldDisplayRightShift(n)                                         \
				HD44780DisplayRightShift(n)

#define LCDShieldButtonGet()                                                  \
				KeypadButtonGet()

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

#endif //__LCDSHIELD_H__
