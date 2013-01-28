//*****************************************************************************
//
//! \file xled_1.h
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
#ifndef  __IO_seven_segment_xled_1_H
#define __IO_seven_segment_xled_1_H

#include "hw_xled_1.h"

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
//! \addtogroup  Seven_Segment_Led1_Driver
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
//         +-----------------------------------------------------------+  \n
//	        +   G  F     A  B
//	        +  _|__|__|__|__|_    _________   _________   ________
//pin_a A       +   |  _______    |  |        |  |        |  |	      |
//pin_b B       +   | |	  A   |   |  |        |  |	  |  |	      |
//pin_c C       +   | |F          |B  |  |        |  |	  |  |	      |
//pin_d D	   +   | |_______|   |  |        |  |	  |  |	      |
//pin_e E	       +   | |   G      |   |  |        |  |        |  |	      |
//pin_f F	       +   | |E          |C  |  |        |  |	  |  |	      |
//pin_g G	   +   | |_______|.H |  |        |  |        |  |	      |
//pin_h H	   +   |	   D      |  |        |  |        |  |        |
//pin_com0 Com0 +   |_____________|
//                                     |  |  |   |  |  |           | 	     |
//                                    E  D COM0 C  H
//	   +-----------------------------------------------------------+  \n
//					\n
//
// -A-H 	: 	 The seven_segment working pins
//
// -COM0 :	Pins control seven_segment to be work
//*****************************************************************************

//
// Configure the common polar, 1: VCC, 0: GND.
//
#define LED_COMMON_POLAR	1

#define LEDn                               8
#define CHIP_SEL_NUM            1

//
// Seven_Segment
//
#define LED_A_PIN            xGPIO_PIN_8
#define LED_A_PORT         xGPIO_PORTB_BASE
#define LED_B_PIN             xGPIO_PIN_9
#define LED_B_PORT         xGPIO_PORTB_BASE
#define LED_C_PIN             xGPIO_PIN_10
#define LED_C_PORT         xGPIO_PORTB_BASE
#define LED_D_PIN             xGPIO_PIN_11
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

//Number count
#define xLED_NUMBER_COUNT  10
#define xLED_DOT 0x80

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
extern void xled1_Init (void);
extern void xled1_Clear (void);
extern void xled1_Off(void);
extern xtBoolean xled1_Show (unsigned char ucData);

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
