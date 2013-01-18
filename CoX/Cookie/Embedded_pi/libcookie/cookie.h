//*****************************************************************************
//
//! \file cookie.h
//! \brief Defines and Macros for Embeded pi Board.
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

#ifndef __COOKIE_H__
#define __COOKIE_H__

#include "cookie_cfg.h"
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
//! \addtogroup Cookie Embeded pi
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_Board_Res Embeded pi Board Resource
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_Compatible Embeded pi Arduino Compatible Part
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_Digital Embeded pi Arduino Compatible Digital Part
//! @{
//
//*****************************************************************************

#define sD0                     PC11
#define sD1                     PC10
#define sD2                     PC12
#define sD3                     PC6
#define sD4                     PC7
#define sD5                     PC8
#define sD6                     PC9
#define sD7                     PD2
#define sD8                     PA15
#define sD9                     PA8
#define sD10                    PB12
#define sD11                    PB15
#define sD12                    PB14
#define sD13                    PB13
#define sD14                    PB7
#define sD15                    PB6

#define sSDA                    PB7
#define sSCL                    PB6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_ANALOG Embeded pi Arduino Compatible ANALOG Part
//! @{
//
//*****************************************************************************

#define sA0                     PC0
#define sA1                     PC1
#define sA2                     PC2
#define sA3                     PC3
#define sA4                     PC4
#define sA5                     PC5


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_ICSP Embeded pi Arduino Compatible ICSP Part
//! @{
//
//*****************************************************************************

#define sICSP_1_MISO            PB14
#define sICSP_3_SCK             PB13
#define sICSP_4_MOSI            PB15

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_Communication Embeded pi Arduino Compatible Communication Part
//! @{
//
//*****************************************************************************

#define sSPI_BASE               xSPI2_BASE
#define sICSP_SPI_BASE          xSPI2_BASE
#define sI2C_BASE               xI2C1_BASE
#define sADC_BASE               xADC1_BASE
#define sUART_BASE              xUART3_BASE
#define sUART_DBG_BASE          xUART2_BASE

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
//! \addtogroup CS_B_Arduino_Extended Embeded pi Arduino Extended Part
//! @{
//
//*****************************************************************************

#define sD16                    PC0
#define sD17                    PC1
#define sD18                    PC2
#define sD19                    PC3
#define sD20                    sD20
#define sD21                    sD21
#define sD22                    PA3
#define sD23                    PA2
#define sD24                    PA1
#define sD25                    PA0
#define sD26                    PA9
#define sD27                    PB0
#define sD28                    PA10
#define sD29                    PB1
#define sD30                    PB8
#define sD31                    PB9
#define sD32                    PA4
#define sD33                    PA7
#define sD34                    PA6
#define sD35                    PA5
#define sD36                    PC13
#define sD37                    PB5
#define sD38                    PB11
#define sD39                    PB10
#define sD40                    PC0
#define sD41                    PC1
#define sD42                    PC2
#define sD43                    PC3
#define sD44                    PC4
#define sD45                    PC5

#define sFUART_RX               PA3
#define sFUART_TX               PA2
#define sFUART_RTS              PA1
#define sFUART_CTS              PA0

#define sCAN_TX                 PB8
#define sCAN_RX                 PB9

#define sSPI_SS                 PA4
#define sSPI_MOSI               PA7
#define sSPI_MISO               PA6
#define sSPI_SCK                PA5

#define sI2C_SDA                PB11
#define sI2C_SCk                PB10

#define sPWM_PWM0_P             PA9
#define sPWM_PWM0_N             PB0
#define sPWM_PWM1_P             PA10
#define sPWM_PWM1_N             PB1

#define sUART_EXT_BASE          xUART2_BASE
#define sSPI_EXT_BASE           xSPI1_BASE
#define sI2C_EXT_BASE           xI2C2_BASE


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_B_Arduino_UserDefine Embeded pi Arduino UserDefine Part
//! @{
//
//*****************************************************************************
#define sSTM_BOOT0              sSTM_BOOT0
#define sSTM_BOOT1              sSTM_BOOT1
#define sSTM_RESET              sSTM_RESET

#define sSTM_UART_TX            PA9
#define sSTM_UART_RX            PA10

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CS_Exported_APIs Embeded pi API
//! \brief Embeded pi Pin Configuration API
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
           xSPinTypeUART(UART3RX, sD0);                                       \
           xSPinTypeUART(UART3TX, sD1);                                       \
         }                                                                    \
         else if(ulBase == sUART_DBG_BASE)                                    \
         {                                                                    \
           xSPinTypeUART(UART2TX, sD23);                                      \
           xSPinTypeUART(UART2RX, sD22);                                      \
         }                                                                    \
        }while(0)
        
#define sPinTypeSPI(ulBase)                                                   \
        do                                                                    \
        {                                                                     \
         if(ulBase == sSPI_BASE)                                              \
         { 	                                                                  \
           xSPinTypeSPI(SPI2CS(APP),  sD10);                                       \
           xSPinTypeSPI(SPI2MOSI(APP),sD11);                                       \
           xSPinTypeSPI(SPI2MISO(APP),sD12);                                       \
           xSPinTypeSPI(SPI2CLK(APP), sD13);                                       \
         }                                                                    \
         else if(ulBase == sSPI_EXT_BASE)                                     \
         {                                                                    \
           xSPinTypeSPI(SPI1CS(APP),  sD32);                                       \
           xSPinTypeSPI(SPI1MOSI(APP),sD33);                                       \
           xSPinTypeSPI(SPI1MISO(APP),sD34);                                       \
           xSPinTypeSPI(SPI1CLK(APP), sD35);                                       \
         }                                                                    \
        }while(0) 
            

#define sPinTypeI2C(ulBase)                                                   \
        do                                                                    \
        {                                                                     \
         xASSERT(ulBase == sI2C_BASE || ulBase == sI2C_EXT_BASE);             \
                                                                              \
         if(ulBase == sI2C_BASE)                                              \
         { 	                                                                  \
           xSPinTypeI2C(I2C1SDA, sD14);                                       \
           xSPinTypeI2C(I2C1SCK, sD15);                                       \
         }                                                                    \
         else if(ulBase == sI2C_EXT_BASE)                                     \
         {                                                                    \
           xSPinTypeI2C(I2C2SDA, sD38);                                       \
           xSPinTypeI2C(I2C2SCK, sD39);                                       \
         }                                                                    \
        }while(0)


#define sA0PinTypeADC()         xSPinTypeADC(ADC10, sA0)
#define sA1PinTypeADC()         xSPinTypeADC(ADC11, sA1)
#define sA2PinTypeADC()         xSPinTypeADC(ADC12, sA2)
#define sA3PinTypeADC()         xSPinTypeADC(ADC13, sA3)
#define sA4PinTypeADC()         xSPinTypeADC(ADC14, sA4)
#define sA5PinTypeADC()         xSPinTypeADC(ADC15, sA5)

#define sD3PinTypePWM()         xSPinTypePWM(PWM4, sD3)
#define sD5PinTypePWM()         xSPinTypePWM(PWM2, sD5)
#define sD6PinTypePWM()         xSPinTypePWM(PWM4, sD6)
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

#endif // __COOKIE_H__  
