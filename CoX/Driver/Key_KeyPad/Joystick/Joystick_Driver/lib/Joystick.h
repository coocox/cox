//*****************************************************************************
//
//! \file Joystick.h
//! \brief header file of  driver for Joystick
//!        Configure this file to apply this driver to your application
//! \version V1.0.0
//! \date 1/23/2013
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2012, CooCoX All rights reserved.
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
#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

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
//! \addtogroup Other
//! @{
//! \addtogroup Keys
//! @{
//! \addtogroup Joystick
//! @{
//! \addtogroup Joystick_Driver_Single
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Joystick_User_Config
//! Joystick Interface Configure
//! @{
//
//*****************************************************************************

//
//! Configure the pin connection of joystick
//
#define JOYSTICK_PIN_SELECT       PD0
#define JOYSTICK_PIN_RIGHT        PD1
#define JOYSTICK_PIN_DOWN         PD2
#define JOYSTICK_PIN_UP           PD3
#define JOYSTICK_PIN_LEFT         PD4

//
//! Set the effective output level of joystick when key is pressed down
//
#define JOYSTICK_KEY_EFFECTIVE_LEVEL 0
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//
//! The code of each key. 0 stands for none key pressed
//
#define JOYSTICK_KEY_SELECT       1
#define JOYSTICK_KEY_UP           2
#define JOYSTICK_KEY_DOWN         3
#define JOYSTICK_KEY_LEFT         4
#define JOYSTICK_KEY_RIGHT        5

//*****************************************************************************
//
//! \addtogroup Joystick_Driver_API
//! Exported Joystick Driver APIs
//! @{
//
//*****************************************************************************
extern void JoystickInit(void);
extern unsigned char JoystickKeyRead(void);
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
//! @}
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif


#endif
