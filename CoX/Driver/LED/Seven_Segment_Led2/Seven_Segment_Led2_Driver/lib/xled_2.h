//*****************************************************************************
//
//! \file xled_2.h
//! \brief Prototypes for the seven segment digital tubes Driver.
//! \version V2.1.1.0
//! \date 1/6/2013
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
//!
//*****************************************************************************
#ifndef  __IO_seven_segment_xled_2_H
#define __IO_seven_segment_xled_2_H

#include "hw_xled_2.h"

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
//! \addtogroup LED
//! @{
//! \addtogroup Seven_Segment_LED
//! @{
//! \addtogroup  Seven_Segment_Led2_Driver
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Seven_Segment_Config Seven Segment Digital Tubes Driver Configurtion
//!
//! \brief Configurtions such as the GPIO Pin used should be set before using
//! this driver.
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//Up Pins:      COM1, B, C, E, D
//Down Pins: G, H, A, F ,COM2
//*****************************************************************************

//
// Configure the common polar, 1: VCC, 0: GND.
//
#define LED_COMMON_POLAR	0

#define LEDn                               8
#define CHIP_SEL_NUM            2

//Number count
#define xLED_NUMBER_COUNT  10
#define xLED_DOT                          0x80

//
// Seven_Segment
//
#define LED_A_PIN            xGPIO_PIN_8
#define LED_A_PORT         xGPIO_PORTB_BASE
#define LED_B_PIN             xGPIO_PIN_9
#define LED_B_PORT         xGPIO_PORTB_BASE
#define LED_C_PIN             xGPIO_PIN_10
#define LED_C_PORT         xGPIO_PORTB_BASE
#define LED_D_PIN             xGPIO_PIN_7
#define LED_D_PORT         xGPIO_PORTB_BASE
#define LED_E_PIN              xGPIO_PIN_12
#define LED_E_PORT          xGPIO_PORTB_BASE
#define LED_F_PIN              xGPIO_PIN_13
#define LED_F_PORT          xGPIO_PORTB_BASE
#define LED_G_PIN             xGPIO_PIN_14
#define LED_G_PORT         xGPIO_PORTB_BASE
#define LED_DP_PIN           xGPIO_PIN_15
#define LED_DP_PORT       xGPIO_PORTB_BASE

#define CHIP_SEL_1_PIN        xGPIO_PIN_2
#define CHIP_SEL_1_PORT    xGPIO_PORTB_BASE
#define CHIP_SEL_2_PIN        xGPIO_PIN_3
#define CHIP_SEL_2_PORT    xGPIO_PORTB_BASE

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Seven_Segment_API Seven Segment Digital Tubes API
//!
//! @{
//
//*****************************************************************************
extern void xled2_Init (void);
extern void xled2_Clear (void);
extern void xled2_Off(void);
extern xtBoolean xled2_ShowSingle (unsigned char ucSel,
		unsigned char ucData);
extern xtBoolean xled2_Scan (unsigned long ulData,
		unsigned char ucDotPos);

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

#endif //__IO_seven_segment_H
