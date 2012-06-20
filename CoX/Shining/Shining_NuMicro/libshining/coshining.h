//*****************************************************************************
//
//! \file coshining.h
//! \brief Defines and Macros for Co-Shining Board.
//! \version V2.1.1.0
//! \date 12/29/2011
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

#ifndef __CO_SHINING_H__
#define __CO_SHINING_H__

#include "coshining_cfg.h"
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xgpio.h"
#include "xdebug.h"

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
//extern "C"
//{
#endif

//*****************************************************************************
//
//! \addtogroup Co-Shining Co-Shining
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_Board_Res Co-Shining Board Resource
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_Compatible Co-Shining Arduino Compatible Part
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_Digital Co-Shining Arduino Compatible Digital Part
//! @{
//
//*****************************************************************************

#define sD0                     PA1
#define sD1                     PA0
#define sD2                     PE0
#define sD3                     PE1
#define sD4                     PE2
#define sD5                     PE3
#define sD6                     PC4
#define sD7                     PD2
#define sD8                     PD3
#define sD9                     PC5

#if defined(sD10_FUNC_MAP)
#if (sD10_FUNC_MAP == sD10_FUNC_SPI_SS)
#define sD10                    PA4
#elif (sD10_FUNC_MAP == sD10_FUNC_PWM)
#define sD10                    PC6
#endif
#else
#error "Please set D10 peripheral function first"
#endif

#if defined(sD11_FUNC_MAP)
#if (sD11_FUNC_MAP == sD11_FUNC_SPI_MOSI)
#define sD11                    PA5
#elif (sD11_FUNC_MAP == sD11_FUNC_PWM)
#define sD11                    PC7
#endif
#else 
#error "Please set D11 peripheral function first"
#endif

#define sD12                    PA6
#define sD13                    PA7

#define sSDA                    PD4
#define sSCL                    PD5

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_ANALOG Co-Shining Arduino Compatible ANALOG Part
//! @{
//
//*****************************************************************************

#define sA0                     PB0
#define sA1                     PB1
#define sA2                     PB2
#define sA3                     PB3

#if defined(sA4_FUNC_MAP)
#if (sA4_FUNC_MAP == sA4_FUNC_AIN)
#define sA4                     PB4
#elif (sA4_FUNC_MAP == sA4_FUNC_I2C_SDA)
#define sA4                     PD4
#endif
#else 
#error "Please set A4 peripheral function first"
#endif


#if defined(sA5_FUNC_MAP)
#if (sA5_FUNC_MAP == sA5_FUNC_AIN)
#define sA5                     PB5
#elif (sA5_FUNC_MAP == sA5_FUNC_I2C_SCL)
#define sA5                     PD5
#endif
#else 
#error "Please set A4 peripheral function first"
#endif

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_ICSP Co-Shining Arduino Compatible ICSP Part
//! @{
//
//*****************************************************************************

#define sICSP_1_MISO            PB6
#define sICSP_3_SCK             PB7
#define sICSP_4_MOSI            PB5

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_Communication Co-Shining Arduino Compatible Communication Part
//! @{
//
//*****************************************************************************

#define sSPI_BASE               xSPI1_BASE
#define sICSP_SPI_BASE          xSPI0_BASE
#define sI2C_BASE               xI2C0_BASE
#define sADC_BASE               xADC0_BASE
#define sUART_BASE              xUART1_BASE
#define sUART_DBG_BASE          xUART0_BASE 

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
//! \addtogroup CS_Exported_APIs Co-Shining API
//! \brief Co-Shining Pin Configuration API
//!
//! @{
//
//*****************************************************************************
#define sPinTypeUART(ulBase)                                                  \
        do                                                                    \
        {                                                                     \
         xASSERT(ulBase == sUART_BASE || ulBase == sUART_DBG_BASE);           \
                                                                              \
         if(ulBase == sUART_BASE)                                             \
         {                                                                    \
           xSPinTypeUART(UART1RX, sD0);                                       \
           xSPinTypeUART(UART1TX, sD1);                                       \
         }                                                                    \
         else if(ulBase == sUART_DBG_BASE)                                    \
         {                                                                    \
           xSPinTypeUART(UART0TX, PA2);                                       \
           xSPinTypeUART(UART0RX, PA3);                                       \
         }                                                                    \
        }while(0)
        
#define sPinTypeSPI(ulBase)                                                   \
        do                                                                    \
        {                                                                     \
         xASSERT(ulBase == sSPI_BASE || ulBase == sICSP_SPI_BASE);            \
                                                                              \
         if(ulBase == sSPI_BASE)                                              \
         {                                                                    \
           xASSERT(sD10_FUNC_MAP == sD10_FUNC_SPI_SS);                        \
           xASSERT(sD11_FUNC_MAP == sD11_FUNC_SPI_MOSI);                      \
           xSPinTypeSPI(SPI1CS,  sD10);                                       \
           xSPinTypeSPI(SPI1MISO,sD12);                                       \
           xSPinTypeSPI(SPI1CLK, sD13);                                       \
         }                                                                    \
         else if(ulBase == sICSP_SPI_BASE)                                    \
         {                                                                    \
           xSPinTypeSPI(SPI0MOSI, sICSP_4_MOSI);                              \
           xSPinTypeSPI(SPI0MISO, sICSP_1_MISO);                              \
           xSPinTypeSPI(SPI0CLK,  sICSP_3_SCK);                               \
         }                                                                    \
        }while(0) 
            

#define sPinTypeI2C(ulBase)                                                   \
        do                                                                    \
        {                                                                     \
         xASSERT(ulBase == sI2C_BASE);                                        \
                                                                              \
         xSPinTypeI2C(I2C0SDA, sSDA);                                         \
         xSPinTypeI2C(I2C0SCK, sSCL);                                         \
        }while(0)


#define sA0PinTypeADC()         xSPinTypeADC(ADC0, sA0)
#define sA1PinTypeADC()         xSPinTypeADC(ADC1, sA1)
#define sA2PinTypeADC()         xSPinTypeADC(ADC2, sA2)
#define sA3PinTypeADC()         xSPinTypeADC(ADC3, sA3)
#define sA4PinTypeADC()         xSPinTypeADC(ADC4, sA4)
#define sA5PinTypeADC()         xSPinTypeADC(ADC5, sA5)
#define sA6PinTypeADC()         xSPinTypeADC(ADC6, sA6)

#define sD3PinTypePWM()         xSPinTypePWM(PWM1, sD3)
#define sD5PinTypePWM()         xSPinTypePWM(PWM3, sD5)
#define sD9PinTypePWM()         xSPinTypePWM(PWM5, sD9)
#define sD10PinTypePWM()        xSPinTypePWM(PWM6, sD10)
#define sD11PinTypePWM()        xSPinTypePWM(PWM7, sD11)

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
//}
#endif

#endif // __CO_SHINING_H__  
