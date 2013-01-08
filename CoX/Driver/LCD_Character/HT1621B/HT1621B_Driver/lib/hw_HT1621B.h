//*****************************************************************************
//
//! \file hw_HT1621B.h
//! \brief header file of Driver for HT1621B
//! \version 1.0.0.0
//! \date 12/20/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox All rights reserved.
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
#ifndef  __HW_HT1621B_H__
#define  __HW_HT1621B_H__


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
//! \addtogroup LCD
//! @{
//! \addtogroup LCD_Character 
//! @{
//! \addtogroup HT1621B_LCD_Driver
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT1621B_Register_Config HT1621B Register Configuration
//! define the register bits of HT1621B,0~127
//! @{
//
//*****************************************************************************
#define            _lcd_BUSY                 0
#define            _lcd_AC                   1
#define            _lcd_PLUS                 2
#define            _lcd_F1                   3
#define            _lcd_ERROR                4
#define            _lcd_DC                   5
#define            _lcd_MINUS                6
#define            _lcd_F2                   7
#define            _lcd_DOT0                 12
#define            _lcd_AUTO                 20
#define            _lcd_RUN                  24
#define            _lcd_PAUSE                25
#define            _lcd_DOT1                 26
#define            _lcd_COLON0               27
#define            _lcd_DOT2                 32
#define            _lcd_STOP                 40
#define            _lcd_KPA                  44
#define            _lcd_SETUP                45
#define            _lcd_DOT3                 46
#define            _lcd_COLON1               47
#define            _lcd_DOT4                 52
#define            _lcd_KG                   60
#define            _lcd_MM                   64
#define            _lcd_KM                   65
#define            _lcd_L                    66
#define            _lcd_M3                   67
#define            _lcd_DB                   68
#define            _lcd_PERCENT              69
#define            _lcd_OHOM                 70
#define            _lcd_DEGREE               71
#define            _lcd_A                    72
#define            _lcd_V                    73
#define            _lcd_MHZ                  74
#define            _lcd_KW                   75
#define            _lcd_MA                   76
#define            _lcd_MV                   77
#define            _lcd_KHZ                  78
#define            _lcd_W                    79
#define            _lcd_NG                   80
#define            _lcd_OK                   81
#define            _lcd_RX                   82
#define            _lcd_TX                   83
#define            _lcd_FM                   84
#define            _lcd_PM                   85
#define            _lcd_AM                   86
#define            _lcd_CARD                 87
#define            _lcd_AT3                  88
#define            _lcd_AT2                  89
#define            _lcd_AT1                  90
#define            _lcd_AT0                  91
#define            _lcd_LOCK                 95
#define            _lcd_BELL                 103
#define            _lcd_COLON2               111
#define            _lcd_BAT                  119
#define            _lcd_MAX                  124
#define            _lcd_MIN                  125
#define            _lcd_CH                   126
#define            _lcd_FAULT                127
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


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
