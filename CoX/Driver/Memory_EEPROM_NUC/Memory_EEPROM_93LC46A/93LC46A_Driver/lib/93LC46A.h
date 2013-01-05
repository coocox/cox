//*****************************************************************************
//
//! \file 93LC46A.h
//! \brief Prototypes for the 93LC46A Driver.
//! \version V1.0.0.0
//! \date 12/28/2012
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
//*****************************************************************************

#ifndef __93LC46A_H__
#define __93LC46A_H__

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
//! \addtogroup Memory
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup GPIO_Eeprom
//! @{
//
//*****************************************************************************

//*****************************************************************************

//*****************************************************************************
//! \addtogroup 93LC46A_Driver
//! @{
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup 93LC46A_User_Config
//! @{
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup 93LC46A_PIN_Config
//! @{
//
//*****************************************************************************
#define _93LC46A_PIN_PORT                      xGPIO_PORTB_BASE
#define _93LC46A_PERIPH_PORT                   xSYSCTL_PERIPH_GPIOB
#define _93LC46A_PIN_SEL                       xGPIO_PIN_12
#define _93LC46A_PIN_CLOCK                     xGPIO_PIN_13
#define _93LC46A_PIN_DI                        xGPIO_PIN_14
#define _93LC46A_PIN_DO                        xGPIO_PIN_15
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup 93LC46A_OP_CODE
//! @{
//
//*****************************************************************************
#define _93LC46A_WriteEnable                    0x0260
#define _93LC46A_WriteDisable                   0x0200
#define _93LC46A_EraseAll                       0x0240

#define _93LC46A_WriteAll                       0x0220
#define _93LC46A_Write                          0x0280
#define _93LC46A_Read                           0x0300
#define _93LC46A_Erase                          0x0380
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//! \addtogroup 93LC46A_DELAYTIME
//! @{
//
//*****************************************************************************

#define  DELAY_TIME_1 			50
#define  DELAY_TIME_2 			20
#define  DELAY_TIME_3 			30

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
//! \addtogroup COX_93LC46A_Exported_APIs
//! @{
//
//*****************************************************************************
void eep_93LC46A_Write(const char data, char addr);
void eep_93LC46A_Cmd(short cmd);
void eep_93LC46A_Read(char* data, unsigned char addr);
void eep_93LC46A_Init();
void eep_93LC46A_Erase(unsigned char addr);
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
//! Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //__93LC46A_H__
