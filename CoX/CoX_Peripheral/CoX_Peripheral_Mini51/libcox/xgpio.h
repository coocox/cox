//*****************************************************************************
//
//! \file xgpio.h
//! \brief Prototypes for the GPIO Driver.
//! \brief Prototypes for the AFIO Driver.
//! \version V2.1.1.0
//! \date 2/6/2012
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

#ifndef __xGPIO_H__
#define __xGPIO_H__

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
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup GPIO
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Config xGPIO intrerrupt number config
//! 
//! \section xGPIO_Config_section 1. Where to use this group
//! This is use to config xGPIO intrerrupt number.
//! 
//! \section xGPIO_Config_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO INT Number        |       CoX      |         MINI51         |
//! |------------------------|----------------|------------------------|
//! |xGPIO_INT_NUMBER        |    Mandatory   |   xGPIO_INT_NUMBER     |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************
  
//
//! xGPIO intrerrupt number config
//
#define xGPIO_INT_NUMBER        8

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_General_Pin_IDs xGPIO General Pin ID
//! 
//! \section xGPIO_General_Pin_IDs 1. Where to use this group
//! The following values define the bit field for the ulPins argument to several
//! of the APIs. So all the API which have a ulPins argument must use this group.
//! 
//! \section xGPIO_General_Pin_IDs_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO General Pin ID    |       CoX      |         MINI51           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_n             |    Mandatory   |       xGPIO_PIN_0      |
//! |                        |                |------------------------|
//! |                        |                |       xGPIO_PIN_1      |
//! |                        |                |------------------------|
//! |                        |                |       xGPIO_PIN_2      |
//! |                        |                |------------------------|
//! |                        |                |           ...          |
//! |                        |                |------------------------|
//! |                        |                |       xGPIO_PIN_7      |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! GPIO pin 0
//
#define xGPIO_PIN_0             GPIO_PIN_0

//
//! GPIO pin 1
//
#define xGPIO_PIN_1             GPIO_PIN_1

//
//! GPIO pin 2
//
#define xGPIO_PIN_2             GPIO_PIN_2

//
//! GPIO pin 3
//
#define xGPIO_PIN_3             GPIO_PIN_3

//
//! GPIO pin 4
//
#define xGPIO_PIN_4             GPIO_PIN_4

//
//! GPIO pin 5
//
#define xGPIO_PIN_5             GPIO_PIN_5

//
//! GPIO pin 6
//
#define xGPIO_PIN_6             GPIO_PIN_6

//
//! GPIO pin 7
//
#define xGPIO_PIN_7             GPIO_PIN_7
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Dir_Mode xGPIO Dir Mode
//! 
//! \section xGPIO_Dir_Mode_S1 1. Where to use this group
//! Values that can be passed to xGPIODirModeSet as the ulPinIO parameter, and
//! returned from xGPIODirModeGet.
//! 
//! \section xGPIO_Dir_Mode_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO Dir Mode          |       CoX      |         MINI51           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_IN       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_OUT      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_HW       |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_QB       |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_OD       |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
// Pin is a GPIO input
//
#define xGPIO_DIR_MODE_IN       GPIO_DIR_MODE_IN

//
// Pin is a GPIO output
//
#define xGPIO_DIR_MODE_OUT      GPIO_DIR_MODE_OUT

//
// Pin is in Quasi-bidirectional mode
//
#define xGPIO_DIR_MODE_QB       GPIO_DIR_MODE_QB

//
// Pin is in Open-Drain mode.
//
#define xGPIO_DIR_MODE_OD       GPIO_DIR_MODE_OD

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Int_Type xGPIO Int Type
//! 
//! \section xGPIO_Int_Type_S1 1. Where to use this group
//! Values that can be passed to xGPIOIntTypeSet as the ulIntType parameter, and
//! returned from xGPIOIntTypeGet.
//! 
//! \section xGPIO_Int_Type_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO Int Type          |       CoX      |         MINI51         |
//! |------------------------|----------------|------------------------|
//! |xGPIO_FALLING_EDGE      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_RISING_EDGE       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_LOW_LEVEL         |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_HIGH_LEVEL        |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_BOTH_LEVEL        |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_BOTH_EDGES        |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
// Interrupt on falling edge
//
#define xGPIO_FALLING_EDGE      GPIO_FALLING_EDGE

//
// Interrupt on rising edge
//
#define xGPIO_RISING_EDGE       GPIO_RISING_EDGE

//
// Interrupt on both edges
//
#define xGPIO_BOTH_EDGES        GPIO_BOTH_EDGES

//
// Interrupt on both levels
//
#define xGPIO_BOTH_LEVEL        GPIO_BOTH_LEVEL

//
// Interrupt on low level
//
#define xGPIO_LOW_LEVEL         GPIO_LOW_LEVEL

//
// Interrupt on high level
//
#define xGPIO_HIGH_LEVEL        GPIO_HIGH_LEVEL 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Pad_Config_Strength xGPIO Pad Config Strength
//! 
//! \section xGPIO_Pad_Config_Strength_S1 1. Where to use this group
//! Values that can be passed to xGPIOPadConfigSet as the ulStrength parameter,
//! and returned by xGPIOPadConfigGet in the *pulStrength parameter.
//! 
//! \section xGPIO_Pad_Config_Strength_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO Pad Strength      |       CoX      |         MINI51         |
//! |------------------------|----------------|------------------------|
//! |xGPIO_STRENGTH_nMA      | Non-Mandatory  |   xGPIO_STRENGTH_2MA   |
//! |                        |                |------------------------|
//! |                        |                |   xGPIO_STRENGTH_4MA   |
//! |                        |                |------------------------|
//! |                        |                |   xGPIO_STRENGTH_8MA   |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Pad_Config_Type xGPIO Pad Config Type
//! <br />
//! \section xGPIO_Pad_Config_Type_S1 1. Where to use this group
//! Values that can be passed to xGPIOPadConfigSet as the ulPadType parameter,
//! and returned by xGPIOPadConfigGet in the *pulPadType parameter.
//! <br />
//! \section xGPIO_Pad_Config_Type_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO Pad Type          |       CoX      |         MINI51         |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_STD      |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_STD_WPU  |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_OD       |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_OD_WPU   |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_OD_WPD   |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_ANALOG   |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_STD_WPD  |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_GP_Short_Pin xGPIO General Purpose Short Pin
//! @{
//
//*****************************************************************************
#define GPA0                    GPIO_PORTA_BASE, GPIO_PIN_0
#define GPA1                    GPIO_PORTA_BASE, GPIO_PIN_1
#define GPA2                    GPIO_PORTA_BASE, GPIO_PIN_2
#define GPA3                    GPIO_PORTA_BASE, GPIO_PIN_3
#define GPA4                    GPIO_PORTA_BASE, GPIO_PIN_4
#define GPA5                    GPIO_PORTA_BASE, GPIO_PIN_5
#define GPA6                    GPIO_PORTA_BASE, GPIO_PIN_6
#define GPA7                    GPIO_PORTA_BASE, GPIO_PIN_7

#define GPB0                    GPIO_PORTB_BASE, GPIO_PIN_0
#define GPB1                    GPIO_PORTB_BASE, GPIO_PIN_1
#define GPB2                    GPIO_PORTB_BASE, GPIO_PIN_2
#define GPB3                    GPIO_PORTB_BASE, GPIO_PIN_3
#define GPB4                    GPIO_PORTB_BASE, GPIO_PIN_4
#define GPB5                    GPIO_PORTB_BASE, GPIO_PIN_5
#define GPB6                    GPIO_PORTB_BASE, GPIO_PIN_6
#define GPB7                    GPIO_PORTB_BASE, GPIO_PIN_7

#define GPC0                    GPIO_PORTC_BASE, GPIO_PIN_0
#define GPC1                    GPIO_PORTC_BASE, GPIO_PIN_1
#define GPC2                    GPIO_PORTC_BASE, GPIO_PIN_2
#define GPC3                    GPIO_PORTC_BASE, GPIO_PIN_3
#define GPC4                    GPIO_PORTC_BASE, GPIO_PIN_4
#define GPC5                    GPIO_PORTC_BASE, GPIO_PIN_5
#define GPC6                    GPIO_PORTC_BASE, GPIO_PIN_6
#define GPC7                    GPIO_PORTC_BASE, GPIO_PIN_7

#define GPD0                    GPIO_PORTD_BASE, GPIO_PIN_0
#define GPD1                    GPIO_PORTD_BASE, GPIO_PIN_1
#define GPD2                    GPIO_PORTD_BASE, GPIO_PIN_2
#define GPD3                    GPIO_PORTD_BASE, GPIO_PIN_3
#define GPD4                    GPIO_PORTD_BASE, GPIO_PIN_4
#define GPD5                    GPIO_PORTD_BASE, GPIO_PIN_5
#define GPD6                    GPIO_PORTD_BASE, GPIO_PIN_6
#define GPD7                    GPIO_PORTD_BASE, GPIO_PIN_7

#define GPE0                    GPIO_PORTE_BASE, GPIO_PIN_0
#define GPE1                    GPIO_PORTE_BASE, GPIO_PIN_1
#define GPE2                    GPIO_PORTE_BASE, GPIO_PIN_2
#define GPE3                    GPIO_PORTE_BASE, GPIO_PIN_3
#define GPE4                    GPIO_PORTE_BASE, GPIO_PIN_4
#define GPE5                    GPIO_PORTE_BASE, GPIO_PIN_5
#define GPE6                    GPIO_PORTE_BASE, GPIO_PIN_6
#define GPE7                    GPIO_PORTE_BASE, GPIO_PIN_7
  
#define GPF0                    GPIO_PORTF_BASE, GPIO_PIN_0
#define GPF1                    GPIO_PORTF_BASE, GPIO_PIN_1
#define GPF2                    GPIO_PORTF_BASE, GPIO_PIN_2
#define GPF3                    GPIO_PORTF_BASE, GPIO_PIN_3
#define GPF4                    GPIO_PORTF_BASE, GPIO_PIN_4
#define GPF5                    GPIO_PORTF_BASE, GPIO_PIN_5
#define GPF6                    GPIO_PORTF_BASE, GPIO_PIN_6
#define GPF7                    GPIO_PORTF_BASE, GPIO_PIN_7  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Short_Pin xGPIO Short Pin ID
//! 
//! \section xGPIO_Short_Pin_S1 1. Where to use this group
//! The following values define the short pin argument(dShortPin) to several
//! of the \b xPinTypexxx APIs and all the API which have a eShortPin argument.
//! Such as \ref xGPIOSPinRead(),\ref xGPIOSPinWrite().
//! 
//! \section xGPIO_Short_Pin_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO Short Pin ID      |       CoX      |         MINI51         |
//! |------------------------|----------------|------------------------|
//! |PXn                     |    Mandatory   |    PA0 PA1 ... PA7     |
//! |                        |                |------------------------|
//! |X is A, B, C ...        |                |    PB0 PB1 ... PB7     |
//! |                        |                |------------------------|
//! |                        |                |    PC0 PC1 ... PC7     |
//! |                        |                |------------------------|
//! |                        |                |    PD0 PD1 ... PD7     |
//! |                        |                |------------------------|
//! |                        |                |    PE0 PE1 ... PE7     |
//! |                        |                |------------------------|
//! |                        |                |    PF0 PF1 ... PF7     |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define PA0                     PA0
#define PA1                     PA1
#define PA2                     PA2
#define PA3                     PA3
#define PA4                     PA4
#define PA5                     PA5
#define PA6                     PA6
#define PA7                     PA7

#define PB0                     PB0
#define PB1                     PB1
#define PB2                     PB2
#define PB3                     PB3
#define PB4                     PB4
#define PB5                     PB5
#define PB6                     PB6
#define PB7                     PB7

#define PC0                     PC0
#define PC1                     PC1
#define PC2                     PC2
#define PC3                     PC3
#define PC4                     PC4
#define PC5                     PC5
#define PC6                     PC6
#define PC7                     PC7

#define PD0                     PD0
#define PD1                     PD1
#define PD2                     PD2
#define PD3                     PD3
#define PD4                     PD4
#define PD5                     PD5
#define PD6                     PD6
#define PD7                     PD7

#define PF0                     PF0
#define PF1                     PF1
#define PF2                     PF2
#define PF3                     PF3
#define PF4                     PF4
#define PF5                     PF5
#define PF6                     PF6
#define PF7                     PF7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Peripheral_Pin xGPIO General Peripheral Pin
//!
//! \section xGPIO_Peripheral_Pin_define xGPIO Peripheral Pin define?
//! The macros of General Peripheral Pin Name always like:
//! <b> ModuleName + n + PinName </b>, such as I2C0SCK, SPI1CLK.
//!
//! \section xGPIO_Peripheral_Pin_Port CoX Port Details
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |General Peripheral Pin  |       CoX      |         MINI51         |
//! |------------------------|----------------|------------------------|
//! |ADCn                    |    Mandatory   |   ADC0 ADC1 ... ADC7   |
//! |                        |                |       STADC            |    
//! |------------------------|----------------|------------------------|
//! |I2CnSCK                 |    Mandatory   |        I2C0SCK         |
//! |------------------------|----------------|------------------------|
//! |I2CnSDA                 |    Mandatory   |        I2C0SDA         |
//! |------------------------|----------------|------------------------|
//! |SPInCLK                 |    Mandatory   |        SPI0CLK         |
//! |------------------------|----------------|------------------------|
//! |SPInMOSI                |    Mandatory   |        SPI0MOSI        |
//! |------------------------|----------------|------------------------|
//! |SPInMISO                |    Mandatory   |        SPI0MISO        |
//! |------------------------|----------------|------------------------|
//! |SPInCS                  |    Mandatory   |        SPI0CS          |
//! |------------------------|----------------|------------------------|
//! |UARTnRX                 |    Mandatory   |        UART0RX         |
//! |------------------------|----------------|------------------------|
//! |UARTnTX                 |    Mandatory   |        UART0TX         |
//! |------------------------|----------------|------------------------|
//! |UARTnCTS                |    Mandatory   |        UART0CTS        |
//! |------------------------|----------------|------------------------|
//! |UARTnRTS                |    Mandatory   |        UART0RTS        |
//! |------------------------|----------------|------------------------|
//! |CMPnN                   |    Mandatory   |       CMP0N CMP1N      |
//! |------------------------|----------------|------------------------|
//! |CMPnP                   |    Mandatory   |       CMP0P CMP1P      |
//! |------------------------|----------------|------------------------|
//! |CMPnO                   |    Mandatory   |       CMP0O CMP1O      |
//! |------------------------|----------------|------------------------|
//! |PWMn                    |    Mandatory   |      PWM0 ... PWM5     |
//! |------------------------|----------------|------------------------|
//! |TIMCCPn                 |    Mandatory   |     TIMCCP0  TIMCCP1   |
//! |------------------------|----------------|------------------------|
//! |TnEX                    |    Mandatory   |       T0EX  T1EX       |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//!
//!  
//! @{
//
//*****************************************************************************

#define ADC0                    ADC0
#define ADC1                    ADC1
#define ADC2                    ADC2
#define ADC3                    ADC3
#define ADC4                    ADC4
#define ADC5                    ADC5
#define ADC6                    ADC6
#define ADC7                    ADC7

#define I2C0SCK                 I2C0SCK
#define I2C0SDA                 I2C0SDA

#define SPI0CLK                 SPI0CLK
#define SPI0MOSI                SPI0MOSI
#define SPI0MISO                SPI0MISO
#define SPI0CS                  SPI0CS

#define UART0RX                 UART0RX
#define UART0TX                 UART0TX
#define UART0CTS                UART0CTS
#define UART0RTS                UART0RTS

#define CMP0N                   CMP0N
#define CMP0P                   CMP0P
#define CMP0O                   CMP0O
#define CMP1N                   CMP1N
#define CMP1P                   CMP1P
#define CMP1O                   CMP1O

#define PWM0                    PWM0
#define PWM1                    PWM1
#define PWM2                    PWM2
#define PWM3                    PWM3
#define PWM4                    PWM4
#define PWM5                    PWM5

#define TIMCCP0                 TIMCCP0
#define TIMCCP1                 TIMCCP1
  
#define NINT0                   NINT0
#define NINT1                   NINT1  
  
#define T0EX                    T0EX
#define T1EX                    T1EX 
 
#define XTAL0                   XTAL0   
#define XTAL1                   XTAL1 
  
#define ICECLK                  ICECLK 
#define ICEDAT                  ICEDAT  
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Pin_Config xGPIO Pin Config
//! \brief Values that can be passed to xGPIOPinConfigure as the ulPinConfig 
//! parameter.
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Exported_APIs xGPIO API
//! \brief xGPIO API Reference.
//!
//! \section xGPIO_Exported_APIs_Port CoX Port Details
//!
//! \verbatim
//! +--------------------------+----------------+------------------------+
//! |xGPIO API                 |       CoX      |         MINI51         |
//! |--------------------------|----------------|------------------------|
//! |xGPIODirModeSet           |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOSPinToPeripheralId   |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOSPinToPort           |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOSPinToPin            |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOSPinDirModeSet       |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIODirModeGet           |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOPinIntCallbackInit   |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOPinIntEnable         |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOSPinIntEnable        |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOPinIntDisable        |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOSPinIntDisable       |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOPinIntStatus         |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOPinIntClear          |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOSPinIntClear         |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOPinRead              |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOSPinRead             |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOPinWrite             |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOSPinWrite            |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOPinConfigure         |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOSPinTypeGPIOInput    |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOSPinTypeGPIOOutput   |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOSPinTypeGPIOOutputOD |  Non-Mandatory |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOSPinTypeGPIOOutputQB |  Non-Mandatory |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypeADC              |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypeI2C              |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypePWM              |  Non-Mandatory |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypeSPI              |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypeTimer            |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypeUART             |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypeACMP             |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypeEXTINT           |  Non-Mandatory |            Y           |
//! +--------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Set the direction and mode of the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//! \param ulPins is the bit-packed representation of the pin(s).
//! Details please refer to \ref xGPIO_General_Pin_IDs.
//! \param ulPinIO is the pin direction and/or mode.
//! Details please refer to \ref xGPIO_Dir_Mode.
//!
//! This function will set the specified pin(s) on the selected GPIO port
//! as either an input or output under software control, or it will set the
//! pin to be under hardware control.
//!
//! The parameter \e ulPinIO is an enumerated data type that can be one of
//! the following values: \b xGPIO_DIR_MODE_IN, \b xGPIO_DIR_MODE_OUT,
//!                       \b GPIO_DIR_MODE_OD, \b GPIO_DIR_MODE_QB  
//! 
//! Details please refer to \ref xGPIO_Dir_Mode_CoX.
//!
//! Where \b xGPIO_DIR_MODE_IN specifies that the pin will be programmed as
//! a software controlled input, \b xGPIO_DIR_MODE_OUT specifies that the pin
//! will be programmed as a software controlled output, \b GPIO_DIR_MODE_OD 
//! specifies that the pin will be programmed as a open drain mode, 
//! \b GPIO_DIR_MODE_QB specifies that the pin will be programmed as a Quasi
//!  bidirectional mode. 
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//! 
//! Details please refer to \ref xGPIO_General_Pin_IDs_CoX.
//!
//! \return None.
//
//*****************************************************************************
extern void xGPIODirModeSet(unsigned long ulPort, unsigned long ulPins,
                            unsigned long ulPinIO);   

//*****************************************************************************
//
//! \brief Get the GPIO port from a Pin.
//!
//! \param eShortPin is the base address of the GPIO port
//! 
//! \return GPIO port code which is used by \ref xSysCtlPeripheralEnable,
//! \ref xSysCtlPeripheralDisable, \ref xSysCtlPeripheralReset.
//! Details please refer to \ref xSysCtl_Peripheral_ID.
//
//*****************************************************************************
#define xGPIOSPinToPeripheralId(eShortPin)                                    \
        GPIOSPinToPeripheralId(eShortPin)

//*****************************************************************************
//
//! \brief Get the GPIO port from a short Pin.
//!
//! \param eShortPin is the base address of the GPIO port
//!
//! \note None.
//! 
//! \return GPIO port address which is used by GPIO API.
//
//*****************************************************************************
#define xGPIOSPinToPort(eShortPin)                                            \
        GPIOSPinToPort(eShortPin)


//*****************************************************************************
//
//! \brief Get the GPIO port and Pin number from a short Pin.
//!
//! \param eShortPin is the base address of the GPIO port
//!
//! \note None.
//! 
//! \return GPIO port address which is used by GPIO API.
//
//*****************************************************************************
#define xGPIOSPinToPortPin(eShortPin)                                            \
        GPIOSPinToPortPin(eShortPin)
        
//*****************************************************************************
//
//! \brief Get the GPIO pin number from a short Pin.
//!
//! \param eShortPin is the base address of the GPIO port
//!
//! \note None.
//! 
//! \return GPIO pin number which is used by GPIO API.
//
//*****************************************************************************
#define xGPIOSPinToPin(eShortPin)                                             \
        GPIOSPinToPin(eShortPin)

//*****************************************************************************
//
//! \brief Set the direction and mode of the specified pin(s).
//!
//! \param eShortPin Specified port and pin.
//! Details please refer to \ref xGPIO_Short_Pin.
//! \param ulPinIO is the pin direction and/or mode.
//! Details please refer to \ref xGPIO_Dir_Mode.
//!
//! This function will set the specified pin(s) on the selected GPIO port
//! as either an input or output under software control, or it will set the
//! pin to be under hardware control.
//!
//! The parameter \e ulPinIO is an enumerated data type that can be one of
//! the following values: \b xGPIO_DIR_MODE_IN, \b xGPIO_DIR_MODE_OUT,
//!                       \b xGPIO_DIR_MODE_OD, \b xGPIO_DIR_MODE_QB  
//! 
//! Details please refer to \ref xGPIO_Dir_Mode_CoX.
//!
//! Where \b xGPIO_DIR_MODE_IN specifies that the pin will be programmed as
//! a software controlled input, \b xGPIO_DIR_MODE_OUT specifies that the pin
//! will be programmed as a software controlled output, \b GPIO_DIR_MODE_OD 
//! specifies that the pin will be programmed as a open drain mode, 
//! \b GPIO_DIR_MODE_QB specifies that the pin will be programmed as a open 
//! drain mode. 
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinDirModeSet(eShortPin, ulPinIO)                               \
        xGPIOSDirModeSet(eShortPin, ulPinIO)

//*****************************************************************************
//
//! \brief Get the direction and mode of a pin.
//!
//! \param ulPort is the base address of the GPIO port
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//! \param ulPin is the bit-packed representation of the pin.
//! Details please refer to \ref xGPIO_General_Pin_IDs.
//!
//! This function gets the direction and control mode for a specified pin on
//! the selected GPIO port.  The pin can be configured as either an input or
//! output under software control, or it can be under hardware control.  The
//! type of control and direction are returned as an enumerated data type.
//!
//! The pin are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//! 
//! Details please refer to \ref xGPIO_General_Pin_IDs_CoX.
//!
//! \return Returns one of the enumerated data types described for
//! \ref xGPIODirModeSet().Details please refer to \ref xGPIO_Dir_Mode_CoX.
//
//*****************************************************************************
extern unsigned long xGPIODirModeGet(unsigned long ulPort, 
                                     unsigned long ulPin);

//*****************************************************************************
//
//! \brief Init the GPIO Port X Interrupt Callback function.
//!
//! \param ulPort is the base address of the GPIO port.
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//! \param ulPin is the bit-packed representation of the pin.
//! Details please refer to \ref xGPIO_General_Pin_IDs.
//! \param pfnCallback is the callback function.
//! Details please refer to \ref xLowLayer_Exported_Types.
//!
//! When there is any pins interrupt occrus, Interrupt Handler will 
//! call the callback function. 
//! 
//! param of pfnCallback
//! - pvCBData not used, always 0.
//! - ulEvent not used, always 0.
//! - ulMsgParam is pins which have an event.
//! Details please refer to \ref xGPIO_General_Pin_IDs_CoX.
//! - pvMsgData not used, always 0.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOPinIntCallbackInit(ulPort, ulPin, pfnCallback)                    \
        GPIOPinIntCallbackInit(ulPort, ulPin, pfnCallback)
        
//*****************************************************************************
//
//! \brief Set the interrupt type and Enable interrupt for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//! \param ulPins is the bit-packed representation of the pin(s).
//! Details please refer to \ref xGPIO_General_Pin_IDs.
//! \param ulIntType specifies the type of interrupt trigger mechanism.
//! Details please refer to \ref xGPIO_Int_Type.
//!
//! This function sets up the various interrupt trigger mechanisms for the
//! specified pin(s) on the selected GPIO port.
//!
//! The parameter \e ulIntType is an enumerated data type that can be one of
//! the following values: \b xGPIO_FALLING_EDGE, \b xGPIO_RISING_EDGE, 
//! \b xGPIO_BOTH_EDGES, \b xGPIO_BOTH_LEVEL, \b xGPIO_LOW_LEVEL, 
//! \b xGPIO_HIGH_LEVEL.
//!
//! Details please refer to \ref xGPIO_Int_Type_CoX.
//!
//! Where the different values describe the interrupt detection mechanism
//! (edge or level) and the particular triggering event (falling, rising,
//! or both edges for edge detect, low or high for level detect).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//! 
//! Details please refer to \ref xGPIO_General_Pin_IDs_CoX.
//!
//! \note In order to avoid any spurious interrupts, the user must
//! ensure that the GPIO inputs remain stable for the duration of
//! this function.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOPinIntEnable(ulPort, ulPins, ulIntType)                          \
        GPIOPinIntEnable(ulPort, ulPins, ulIntType) 
         
//*****************************************************************************
//
//! \brief Set the interrupt type and Enable interrupt for the specified pin(s).
//!
//! \param eShortPin Specified port and pin.
//! Details please refer to \ref xGPIO_Short_Pin.
//! \param ulIntType specifies the type of interrupt trigger mechanism.
//! Details please refer to \ref xGPIO_Int_Type.
//!
//! This function sets up the various interrupt trigger mechanisms for the
//! specified pin(s) on the selected GPIO port.
//!
//! The parameter \e ulIntType is an enumerated data type that can be one of
//! the following values: \b xGPIO_FALLING_EDGE, \b xGPIO_RISING_EDGE, 
//! \b xGPIO_BOTH_EDGES, \b xGPIO_BOTH_LEVEL, \b xGPIO_LOW_LEVEL, 
//! \b xGPIO_HIGH_LEVEL.
//!
//! Details please refer to \ref xGPIO_Int_Type_CoX.
//!
//! Where the different values describe the interrupt detection mechanism
//! (edge or level) and the particular triggering event (falling, rising,
//! or both edges for edge detect, low or high for level detect).
//!
//! The pin is specified by eShortPin, which can only be one pin.
//! Details please refer to \ref xGPIO_Short_Pin_CoX.
//!
//! \note In order to avoid any spurious interrupts, the user must
//! ensure that the GPIO inputs remain stable for the duration of
//! this function.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinIntEnable(eShortPin, ulIntType)                              \
        GPIOSPinIntEnable(eShortPin, ulIntType)

//*****************************************************************************
//
//! \brief Disables interrupts for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//! \param ulPins is the bit-packed representation of the pin(s).
//! Details please refer to \ref xGPIO_General_Pin_IDs.
//!
//! Mask the interrupt for the specified pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! Details please refer to \ref xGPIO_General_Pin_IDs_CoX.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOPinIntDisable(ulPort, ulPins)                                    \
        GPIOPinIntDisable(ulPort, ulPins)

//*****************************************************************************
//
//! \brief Disables interrupts for the specified pin.
//!
//! \param eShortPin Specified port and pin.
//! Details please refer to \ref xGPIO_Short_Pin.
//!
//! Mask the interrupt for the specified pin(s).
//!
//! The pin is specified by eShortPin, which can only be one pin.
//! Details please refer to \ref xGPIO_Short_Pin_CoX.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinIntDisable(eShortPin)                                        \
        GPIOSPinIntDisable(eShortPin)

//*****************************************************************************
//
//! \brief Get interrupt status for the specified GPIO port.
//!
//! \param ulPort is the base address of the GPIO port.
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//! 
//! \return Returns a bit-packed byte, where each bit that is set identifies
//! an active masked or raw interrupt, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//! Bits 31:8 should be ignored.
//
//*****************************************************************************
#define xGPIOPinIntStatus(ulPort)                                             \
        GPIOPinIntStatus(ulPort)  

//*****************************************************************************
//
//! \brief Clear the interrupt for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//! \param ulPins is the bit-packed representation of the pin(s).
//! Details please refer to \ref xGPIO_General_Pin_IDs.
//!
//! Clear the interrupt for the specified pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! Details please refer to \ref xGPIO_General_Pin_IDs_CoX.
//!
//! \note Because there is a write buffer in the Cortex-M0 processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOPinIntClear(ulPort, ulPins)                                      \
        GPIOPinIntClear(ulPort, ulPins)

//*****************************************************************************
//
//! \brief Clear the interrupt for the specified pin.
//!
//! \param eShortPin Specified port and pin.
//! Details please refer to \ref xGPIO_Short_Pin.
//!
//! Clear the interrupt for the specified pin.
//!
//! The pin is specified by eShortPin, which can only be one pin.
//! Details please refer to \ref xGPIO_Short_Pin_CoX.
//!
//! \note Because there is a write buffer in the Cortex-M0 processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinIntClear(eShortPin)                                          \
        GPIOSPinIntClear(eShortPin)

//*****************************************************************************
//
//! \brief Reads the values present of the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//! \param ulPins is the bit-packed representation of the pin(s).
//! Details please refer to \ref xGPIO_General_Pin_IDs.
//!
//! The values at the specified pin(s) are read, as specified by \e ucPins.
//! Values are returned for both input and output pin(s), and the value
//! for pin(s) that are not specified by \e ucPins are set to 0.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! Details please refer to \ref xGPIO_General_Pin_IDs_CoX.
//!
//! \return Returns a bit-packed byte providing the state of the specified
//! pin, where bit 0 of the byte represents GPIO port pin 0, bit 1 represents
//! GPIO port pin 1, and so on.  Any bit that is not specified by \e ucPins
//! is returned as a 0.  Bits 31:8 should be ignored.
//
//*****************************************************************************
#define xGPIOPinRead(ulPort, ulPins)                                          \
        GPIOPinRead(ulPort, ulPins)


//*****************************************************************************
//
//! \brief Reads the values present of the specified pin.
//!
//! \param eShortPin Specified port and pin.
//! Details please refer to \ref xGPIO_Short_Pin.
//!
//! The values at the specified pin are read, as specified by \e eShortPin.
//! Values are returned for both input and output pin(s), and the value
//! for pin(s) that are not specified by \e eShortPin are set to 0.
//!
//! The pin is specified by eShortPin, which can only be one pin.
//! Details please refer to \ref xGPIO_Short_Pin_CoX.
//!
//! \return Returns the value of specified port and pin.
//
//*****************************************************************************
#define xGPIOSPinRead(eShortPin)                                              \
        GPIOSPinRead(eShortPin)

//*****************************************************************************
//
//! \brief Write a value to the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//! \param ulPins is the bit-packed representation of the pin(s).
//! Details please refer to \ref xGPIO_General_Pin_IDs.
//! \param ucVal is the value to write to the pin(s), 0 or 1.
//!
//! Write the corresponding bit values to the output pin(s) specified by
//! \e ucPins.  Writing to a pin configured as an input pin has no effect.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! Details please refer to \ref xGPIO_General_Pin_IDs_CoX.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOPinWrite(ulPort, ulPins, ucVal)                                  \
        GPIOPinWrite(ulPort, ulPins, ucVal)

//*****************************************************************************
//
//! \brief Write a value to the specified pin.
//!
//! \param eShortPin Specified port and pin.
//! Details please refer to \ref xGPIO_Short_Pin.
//! \param ucVal is the value to write to the pin(s), 0 or 1.
//!
//! Write the corresponding bit values to the output pin specified by
//! \e eShortPin.  Writing to a pin configured as an input pin has no effect.
//!
//! The pin is specified by eShortPin, which can only be one pin.
//! Details please refer to \ref xGPIO_Short_Pin_CoX.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinWrite(eShortPin, ucVal)                                      \
        GPIOSPinWrite(eShortPin, ucVal)

//*****************************************************************************
//
//! \brief Configure the alternate function of a GPIO pin.
//!
//! \param ulPinConfig is the pin configuration value, specified as only one of
//! the \b GPIO_P??_??? values.
//!
//! This function configures the pin mux that selects the peripheral function
//! associated with a particular GPIO pin.  Only one peripheral function at a
//! time can be associated with a GPIO pin, and each peripheral function should
//! only be associated with a single GPIO pin at a time (despite the fact that
//! many of them can be associated with more than one GPIO pin).
//!
//! \note This function is only valid on Tempest-class devices.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOPinConfigure(ulPinConfig)                                        \
        GPIOPinConfigure(ulPinConfig)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO Input pin.
//!
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin.
//!
//! This function configures a pin for use as an GPIO Input pin device and turns 
//! the pin into a GPIO input pin.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinTypeGPIOInput(eShortPin)                                      \
        do                                                                     \
        {                                                                      \
         xGPIOSDirModeSet(eShortPin, GPIO_DIR_MODE_IN);                        \
         GPIOSPinFunctionSet(GPIO_FUNCTION_GPIO,eShortPin);                    \
        }                                                                      \
        while(0)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO Output(push-pull) pin.
//!
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin.
//!
//! This function configures a pin for use as an GPIO Output pin device and  
//! turns the pin into a GPIO Output pin.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinTypeGPIOOutput(eShortPin)                                     \
        do                                                                     \
        {                                                                      \
         xGPIOSDirModeSet(eShortPin, GPIO_DIR_MODE_OUT);                       \
         GPIOSPinFunctionSet(GPIO_FUNCTION_GPIO,eShortPin);                    \
        }                                                                      \
        while(0)
            
//*****************************************************************************
//
//! \brief Turn a pin to a GPIO Output(open drain) pin.
//!
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin.
//!
//! This function configures a pin for use as an GPIO Output pin device and turns 
//! the pin into a GPIO Output(open drain) pin.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinTypeGPIOOutputOD(eShortPin)                                   \
        do                                                                     \
        {                                                                      \
         xGPIOSDirModeSet(eShortPin, GPIO_DIR_MODE_OD);                        \
         GPIOSPinFunctionSet(GPIO_FUNCTION_GPIO,eShortPin);                    \
        }                                                                      \
        while(0)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO Output(oQuasi-bidirectional) pin.
//!
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin.
//!
//! This function configures a pin for use as an GPIO Output pin device and turns 
//!  the pin into a GPIO Output(Quasi-bidirectional) pin.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinTypeGPIOOutputQB(eShortPin)                                   \
        do                                                                     \
        {                                                                      \
         xGPIOSDirModeSet(eShortPin, GPIO_DIR_MODE_QB);                        \
         GPIOSPinFunctionSet(GPIO_FUNCTION_GPIO,eShortPin);                    \
        }                                                                      \
        while(0)  

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO ADC input pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as ADC0. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin.
//!
//! This function configures a pin for use as an ADC function device and turns 
//! the pin into a GPIO ADC input pin.
//!
//! Table shows what the ePeripheralPin and eShortPin should be, only the 
//! argument which are in the same line can be combined. For eaxmple(MINI51):<br/>
//! xSPinTypeADC(ADC0, PF3) or xSPinTypeADC(ADC1, PB0) is correct;<br/>
//! But xSPinTypeADC(ADC0, PB1) or xSPinTypeADC(ADC0, PB2) is error.
//! \verbatim
//! +--------------------+------------------------+------------------------+
//! |    manufacturer    |ePeripheralPin          |eShortPin               |
//! |--------------------|------------------------|------------------------|
//! |    CoX             |This parameter is a     |This parameter is a     |
//! |                    |mandatory.The mandatory |mandatory. the mandatory|
//! |                    |is the format of        |is the format of        |
//! |                    |Variable naming.So it   |Variable naming.So it   |
//! |                    |should be: ADCn         |should be: PXn          |
//! |                    |n indicate the pin      |XX indicate the GPIO    |
//! |                    |number such as          |PORT,Such as            |
//! |                    |0 1 2 3 ....            |A B C D E ...           |
//! |                    |                        |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |       MINI51       |    ADC0                |    PF3                 |
//! |                    |    ADC1                |    PB0                 |
//! |                    |    ADC2                |    PB2                 |
//! |                    |    ADC3                |    PB3                 |
//! |                    |    ADC4                |    PB4                 |
//! |                    |    ADC5                |    PB5                 |
//! |                    |    ADC6                |    PD0                 |
//! |                    |    ADC7                |    PD1                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeADC(ePeripheralPin, eShortPin)                               \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOSPinFunctionSet(GPIO_FUNCTION_ADC, eShortPin);                   \
        }                                                                     \
        while(0)  

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO I2C input or output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as I2C0SDA. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin.  
//!
//! This function configures a pin for use as an I2C function device and turns 
//! the pin into a GPIO I2C input or output pin.
//!
//! Table shows what the ePeripheralPin and eShortPin should be,only the 
//! argument which are in the same line can be combined.For eaxmple(TI):<br/>
//! xSPinTypeI2C(I2C0SCK, PD4) or xSPinTypeI2C(I2C0SDA, PD5) is correct;<br/>
//! But xSPinTypeI2C(I2C0SCK, PD8) or xSPinTypeI2C(I2C0SCK, PD9) is error.
//! \verbatim
//! +--------------------+------------------------+------------------------+
//! |    manufacturer    |ePeripheralPin          |eShortPin               |
//! |--------------------|------------------------|------------------------|
//! |    CoX             |This parameter is a     |This parameter is a     |
//! |                    |mandatory.The mandatory |mandatory. the mandatory|
//! |                    |is the format of        |is the format of        |
//! |                    |Variable naming.So it   |Variable naming.So it   |
//! |                    |should be: I2CnSCK      |should be: PXn          |
//! |                    |or I2CnSDA              |XX indicate the GPIO    |
//! |                    |n indicate the pin      |PORT,Such as            |
//! |                    |number such as          |A B C D E ...           |
//! |                    |0 1 2 3 ....            |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |       MINI51       |    I2C0SCK             |    PD5                 |
//! |                    |    I2C0SDA             |    PD4                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//***************************************************************************** 
 #define xSPinTypeI2C(ePeripheralPin, eShortPin)                              \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOSPinFunctionSet(GPIO_FUNCTION_I2C, eShortPin);                   \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO PWM input or output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as PWM0. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as a PWM function and turns 
//! the pin into a GPIO PWM input or output pin.
//!
//! Table shows what the ePeripheralPin and eShortPin should be,only the 
//! argument which are in the same line can be combined.For eaxmple(TI):<br/>
//! xSPinTypePWM(PWM0, PC2) or xSPinTypePWM(PWM1, PC3) is correct;<br/>
//! But xSPinTypePWM(PWM0, PD1) or xSPinTypePWM(PWM0, PD2) is error.
//! \verbatim
//! +--------------------+------------------------+------------------------+
//! |    manufacturer    |ePeripheralPin          |eShortPin               |
//! |--------------------|------------------------|------------------------|
//! |    CoX             |This parameter is a     |This parameter is a     |
//! |                    |mandatory.The mandatory |mandatory. the mandatory|
//! |                    |is the format of        |is the format of        |
//! |                    |Variable naming.So it   |Variable naming.So it   |
//! |                    |should be: PWMn,        |should be: PXn          |
//! |                    |n indicate the pin      |XX indicate the GPIO    |
//! |                    |number such as          |PORT,Such as            |
//! |                    |0 1 2 3 ....            |A B C D E ...           |
//! |                    |                        |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |       MINI51       |    PWM0                |    PC2                 |
//! |                    |    PWM1                |    PC3                 |
//! |                    |    PWM2                |    PC4                 |
//! |                    |    PWM3                |    PC5                 |
//! |                    |    PWM4                |    PC6                 |
//! |                    |    PWM5                |    PA4                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//***************************************************************************** 
#define xSPinTypePWM(ePeripheralPin, eShortPin)                               \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOSPinFunctionSet(GPIO_FUNCTION_PWM, eShortPin);                   \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO SPI input or output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as I2C0SDA. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin.
//!
//! This function configures a pin for use as a SPI function and turns 
//!  the pin into a GPIO SPI input or output pin.
//!
//! Table shows what the ePeripheralPin and eShortPin should be,only the 
//! argument which are in the same line can be combined.For eaxmple(TI):<br/>
//! xSPinTypeSPI(SPI0CLK, PB7) or xSPinTypeSPI(SPI0MOSI, PB5) is correct;<br/>
//! But xSPinTypeSPI(SPI0CLK, PA7) or xSPinTypeSPI(SPI0CLK, PA4) is error.
//! \verbatim
//! +--------------------+------------------------+------------------------+
//! |    manufacturer    |ePeripheralPin          |eShortPin               |
//! |--------------------|------------------------|------------------------|
//! |    CoX             |This parameter is a     |This parameter is a     |
//! |                    |mandatory.The mandatory |mandatory. the mandatory|
//! |                    |is the format of        |is the format of        |
//! |                    |Variable naming.So it   |Variable naming.So it   |
//! |                    |should be: SPInCLK,     |should be: PXn          |
//! |                    |SPInMISO, SPInMOSI,     |XX indicate the GPIO    |
//! |                    |or SPInCS,              |PORT,Such as            |
//! |                    |n indicate the pin      |A B C D E ...           |
//! |                    |number such as          |n indicate the pin      |
//! |                    |0 1 2 3 ....            |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |       MINI51       |    SPI0CLK             |    PA7                 |
//! |                    |    SPI0MOSI            |    PA5                 |
//! |                    |    SPI0MISO            |    PA6                 |
//! |                    |    SPI0CS              |    PA4 PA1             |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeSPI(ePeripheralPin, eShortPin)                               \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOSPinFunctionSet(GPIO_FUNCTION_SPI, eShortPin);                   \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO Timer input or output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as TIMCCP0. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as a Timer function and turns 
//!  the pin into a GPIO Timer input or output pin.
//!
//! Table shows what the ePeripheralPin and eShortPin should be,only the 
//! argument which are in the same line can be combined.For eaxmple(TI):<br/>
//! xSPinTypeTimer(TIMCCP0, PD4) or xSPinTypeTimer(TIMCCP0, PD5) is correct;<br/>
//! But xSPinTypeTimer(TIMCCP0, PC5) or xSPinTypeTimer(TIMCCP0, PB6) is error.
//! \verbatim
//! +--------------------+------------------------+------------------------+
//! |    manufacturer    |ePeripheralPin          |eShortPin               |
//! |--------------------|------------------------|------------------------|
//! |    CoX             |This parameter is a     |This parameter is a     |
//! |                    |mandatory.The mandatory |mandatory. the mandatory|
//! |                    |is the format of        |is the format of        |
//! |                    |Variable naming.So it   |Variable naming.So it   |
//! |                    |should be: TIMCCPn,     |should be: PXn          |
//! |                    |n indicate the pin      |XX indicate the GPIO    |
//! |                    |number such as          |PORT,Such as            |
//! |                    |0 1 2 3 ....            |A B C D E ...           |
//! |                    |                        |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |       MINI51       |    TIMCCP0             |    PD4                 |
//! |                    |    TIMCCP1             |    PD5                 |
//! |                    |    T0EX                |    PD2                 |
//! |                    |    T1EX                |    PD6                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeTimer(ePeripheralPin, eShortPin)                             \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOSPinFunctionSet(GPIO_FUNCTION_TIM, eShortPin);                   \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO UART input or output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as UART0RX. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as a UART function and turns 
//!  the pin into a GPIO UART input or output pin.
//!
//! Table shows what the ePeripheralPin and eShortPin should be,only the 
//! argument which are in the same line can be combined.For eaxmple(TI):<br/>
//! xSPinTypeUART(UART0RX, PD0) or xSPinTypeUART(UART0TX, PD1) is correct;<br/>
//! But xSPinTypeUART(UART0RX, PA1) or xSPinTypeUART(UART0RX, PE6) is error.
//! \verbatim
//! +--------------------+------------------------+------------------------+
//! |    manufacturer    |ePeripheralPin          |eShortPin               |
//! |--------------------|------------------------|------------------------|
//! |    CoX             |This parameter is a     |This parameter is a     |
//! |                    |mandatory.The mandatory |mandatory. the mandatory|
//! |                    |is the format of        |is the format of        |
//! |                    |Variable naming.So it   |Variable naming.So it   |
//! |                    |should be: UARTnRX,     |should be: PXn          |
//! |                    |UARTnTX, UARTnCTS,      |XX indicate the GPIO    |
//! |                    |......,                 |PORT,Such as            |
//! |                    |n indicate the pin      |A B C D E ...           |
//! |                    |number such as          |n indicate the pin      |
//! |                    |0 1 2 3 ....            |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |       MINI51       |    UART0RX             |    PB2, PA1            |
//! |                    |    UART0TX             |    PB3, PA0            |
//! |                    |    UART0RTS            |    PA1                 |
//! |                    |    UART0CTS            |    PA0                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeUART(ePeripheralPin, eShortPin)                              \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOSPinFunctionSet(GPIO_FUNCTION_UART, eShortPin);                  \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO ACMP input or output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as CMP0P. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as an ACMP function and turns 
//!  the pin into a GPIO ACMP input or output pin.
//!
//! \verbatim
//! +--------------------+------------------------+------------------------+
//! |    manufacturer    |ePeripheralPin          |eShortPin               |
//! |--------------------|------------------------|------------------------|
//! |    CoX             |This parameter is a     |This parameter is a     |
//! |                    |mandatory.The mandatory |mandatory. the mandatory|
//! |                    |is the format of        |is the format of        |
//! |                    |Variable naming.So it   |Variable naming.So it   |
//! |                    |should be: CMPnN,       |should be: PXn          |
//! |                    |CMPnO or CMPnP          |XX indicate the GPIO    |
//! |                    |n indicate the pin      |PORT,Such as            |
//! |                    |number such as          |A B C D E ...           |
//! |                    |0 1 2 3 ....            |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |       MINI51       |    CMP0P               |    PB5                 |
//! |                    |    CMP0N               |    PB4                 |
//! |                    |    CMP0O               |    PD6                 |
//! |                    |    CMP1P               |    PD1                 |
//! |                    |    CMP1N               |    PD0                 |
//! |                    |    CMP1O               |    PC6                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeACMP(ePeripheralPin, eShortPin)                              \
        do                                                                    \
        {                                                                     \
          GPIOSPinConfigure(ePeripheralPin, eShortPin);                       \
          GPIOSPinFunctionSet(GPIO_FUNCTION_ACMP, eShortPin);                 \
        }while(0)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO CLKO output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as I2C0SDA. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as a CLKO function and turns 
//!  the pin into a GPIO CLKO output pin.
//!
//! +--------------------+------------------------+------------------------+
//! |    manufacturer    |ePeripheralPin          |eShortPin               |
//! |--------------------|------------------------|------------------------|
//! |    CoX             |This parameter is a     |This parameter is a     |
//! |                    |mandatory.The mandatory |mandatory. the mandatory|
//! |                    |is the format of        |is the format of        |
//! |                    |Variable naming.        |Variable naming.        |
//! |--------------------|------------------------|------------------------|
//! |       MINI51       |    CLK0                |    PD6                 |
//! |--------------------|------------------------|------------------------|
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeCLKO(ePeripheralPin, eShortPin)                              \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOSPinFunctionSet(GPIO_FUNCTION_CLKO, eShortPin);                  \
        }                                                                     \
        while(0)
            
//*****************************************************************************
//
//! \brief Turn a pin to a GPIO external interrupt pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as I2C0SDA. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as an GPIO interrupt function and  
//! turns the pin into a GPIO external interrupt pin.
//!
//! \verbatim
//! +--------------------+------------------------+------------------------+
//! |    manufacturer    |ePeripheralPin          |eShortPin               |
//! |--------------------|------------------------|------------------------|
//! |    CoX             |This parameter is a     |This parameter is a     |
//! |                    |mandatory.The mandatory |mandatory. the mandatory|
//! |                    |is the format of        |is the format of        |
//! |                    |Variable naming.So it   |Variable naming.So it   |
//! |                    |should be: INTn         |should be: PXn          |
//! |                    |where n is 0 1 2 3 ...  |XX indicate the GPIO    |
//! |                    |                        |PORT,Such as            |
//! |                    |                        |A B C D E ...           |
//! |                    |                        |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |       MINI51       |    NINT0               |    PD2                 |
//! |                    |    NINT1               |    PF2                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeEXTINT(ePeripheralPin, eShortPin)                            \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOSPinFunctionSet(GPIO_FUNCTION_EXTINT, eShortPin);                \
        }                                                                     \
        while(0)

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
//! \addtogroup MINI51_GPIO
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_General_Pin_IDs MINI51 GPIO General Pin ID
//! \brief The following values define the bit field for the ucPins argument 
//! to several of the APIs.
//! @{
//
//*****************************************************************************

//
//! GPIO pin 0
//
#define GPIO_PIN_0              0x00000001  

//
//! GPIO pin 1
//
#define GPIO_PIN_1              0x00000002  

//
//! GPIO pin 2
//
#define GPIO_PIN_2              0x00000004  

//
//! GPIO pin 3
//
#define GPIO_PIN_3              0x00000008  

//
//! GPIO pin 4
//
#define GPIO_PIN_4              0x00000010  

//
//! GPIO pin 5
//
#define GPIO_PIN_5              0x00000020  

//
//! GPIO pin 6
//
#define GPIO_PIN_6              0x00000040  

//
//! GPIO pin 7
//
#define GPIO_PIN_7              0x00000080  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_General_Pin_Bits MINI51 GPIO General Pin Bits
//! \brief The following values define the bit field for the ucBit argument to 
//! GPIODirModeSet() API.
//! @{
//
//*****************************************************************************

//
//! GPIO BIT 0
//
#define GPIO_BIT_0              0x00000000  

//
//! GPIO BIT 1
//
#define GPIO_BIT_1              0x00000001  

//
//! GPIO BIT 2
//
#define GPIO_BIT_2              0x00000002  

//
//! GPIO BIT 3
//
#define GPIO_BIT_3              0x00000003  

//
//! GPIO BIT 4
//
#define GPIO_BIT_4              0x00000004  

//
//! GPIO BIT 5
//
#define GPIO_BIT_5              0x00000005  

//
//! GPIO BIT 6
//
#define GPIO_BIT_6              0x00000006  

//
//! GPIO BIT 7
//
#define GPIO_BIT_7              0x00000007  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_Dir_Mode MINI51 GPIO Dir Mode
//! \brief Values that can be passed to GPIODirModeSet as the ulPinIO parameter, 
//! and returned from GPIODirModeGet.
//! @{
//
//*****************************************************************************

//
//! Pin is a GPIO input
//
#define GPIO_DIR_MODE_IN        0x00000000  

//
//! Pin is a GPIO output
//
#define GPIO_DIR_MODE_OUT       0x00000001 

//
//! Pin is in Open-Drain mode.
//
#define GPIO_DIR_MODE_OD        0x00000002 

//
//! Pin is in Quasi-bidirectional mode.
//
#define GPIO_DIR_MODE_QB        0x00000003 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_Int_Type MINI51 GPIO Int Type
//! \brief Values that can be passed to GPIOIntTypeSet as the ulIntType parameter, 
//! and returned from GPIOIntTypeGet.
//! @{
//
//*****************************************************************************

//
//! Interrupt on falling edge
//
#define GPIO_FALLING_EDGE       0x00000001  

//
//! Interrupt on rising edge
//
#define GPIO_RISING_EDGE        0x00000002  

//
//! Interrupt on both edges
//
#define GPIO_BOTH_EDGES         0x00000003  

//
//! Interrupt on both level
//
#define GPIO_BOTH_LEVEL         0x00000013  

//
//! Interrupt on low level
//
#define GPIO_LOW_LEVEL          0x00000011  

//
//! Interrupt on high level
//
#define GPIO_HIGH_LEVEL         0x00000012 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_DBCLK_Src MINI51 GPIO De-bounce Clock Source
//! \brief Values that can be passed to GPIODebounceTimeSet as the ulClockSource
//! parameter.
//! @{
//
//*****************************************************************************

//
//! De-bounce counter clock source is the HCLK
//
#define GPIO_DBCLKSRC_HCLK      0x00000000  

//
//! De-bounce counter clock source is the internal 10 kHz low speed oscillator
//
#define GPIO_DBCLKSRC_10K       0x00000001   

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_Function_Set MINI51 GPIO Function Set
//! \brief Values that can be passed to GPIOPinFunctionSet as the ulFunction
//! parameter.
//! @{
//
//*****************************************************************************

#define GPIO_FUNCTION_GPIO      0x00000000
#define GPIO_FUNCTION_SPI       0x00000001
#define GPIO_FUNCTION_ADC       0x00000002
#define GPIO_FUNCTION_ACMP      0x00000003
#define GPIO_FUNCTION_I2C       0x00000004
#define GPIO_FUNCTION_PWM       0x00000005
#define GPIO_FUNCTION_TIM       0x00000006
#define GPIO_FUNCTION_UART      0x00000007
#define GPIO_FUNCTION_EXTINT    0x00000008
#define GPIO_FUNCTION_CLKO      0x00000009
#define GPIO_FUNCTION_XTAL      0x0000000A
#define GPIO_FUNCTION_ICE       0x0000000B

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_Pin_Config MINI51 GPIO Pin Config
//! \brief Values that can be passed to xGPIOPinConfigure as the ulPinConfig 
//! parameter.
//! @{
//
//*****************************************************************************

//
//! GPIO pin A0
//
#define GPIO_PA0_UART0CTS       0x00000010
#define GPIO_PA0_UART0TX        0x00000011

//
//! GPIO pin A1
//
#define GPIO_PA1_SPI0CS         0x00000101
#define GPIO_PA1_UART0RTS       0x00000110
#define GPIO_PA1_UART0RX        0x00000111

//
//! GPIO pin A4
//
#define GPIO_PA4_SPI0CS         0x00000410
#define GPIO_PA4_PWM5           0x00000411

//
//! GPIO pin A5
//
#define GPIO_PA5_SPI0MOSI       0x00000510

//
//! GPIO pin A6
//
#define GPIO_PA6_SPI0MISO       0x00000610

//
//! GPIO pin A7
//
#define GPIO_PA7_SPI0CLK        0x00000710

//
//! GPIO pin B0
//
#define GPIO_PB0_ADC1           0x00001001

//
//! GPIO pin B2
//
#define GPIO_PB2_ADC2           0x00001201
#define GPIO_PB2_UART0RX        0x00001210

//
//! GPIO pin B3
//
#define GPIO_PB3_ADC3           0x00001301
#define GPIO_PB3_UART0TX        0x00001310

//
//! GPIO pin B4
//
#define GPIO_PB4_ADC4           0x00001401
#define GPIO_PB4_CMP0N          0x00001411

//
//! GPIO pin B5
//
#define GPIO_PB5_ADC5           0x00001501
#define GPIO_PB5_CMP0P          0x00001511

//
//! GPIO pin C2
//
#define GPIO_PC2_PWM0           0x00002210

//
//! GPIO pin C3
//
#define GPIO_PC3_PWM1           0x00002310

//
//! GPIO pin C4
//
#define GPIO_PC4_PWM2           0x00002410

//
//! GPIO pin C5
//
#define GPIO_PC5_PWM3           0x00002510

//
//! GPIO pin C6
//
#define GPIO_PC6_PWM4           0x00002610
#define GPIO_PC6_CMP1O          0x00002611

//
//! GPIO pin D0
//
#define GPIO_PD0_CMP1N          0x00003010
#define GPIO_PD0_ADC6           0x00003011

//
//! GPIO pin D1
//
#define GPIO_PD1_CMP1P          0x00003110
#define GPIO_PD1_ADC7           0x00003111

//
//! GPIO pin D2
//
#define GPIO_PD2_NINT0          0x00003201
#define GPIO_PD2_T0EX           0x00003210
#define GPIO_PD2_STADC          0x00003211

//
//! GPIO pin D4
//
#define GPIO_PD4_TIMCCP0        0x00003401
#define GPIO_PD4_I2C0SDA        0x00003410

//
//! GPIO pin D5
//
#define GPIO_PD5_TIMCCP1        0x00003501
#define GPIO_PD5_I2C0SCK        0x00003510

//
//! GPIO pin D6
//
#define GPIO_PD6_T1EX           0x00003601
#define GPIO_PD6_CLK0           0x00003610
#define GPIO_PD6_CMP0O          0x00003611

//
//! GPIO pin E6
//
#define GPIO_PE6_ICECLK         0x00004601

//
//! GPIO pin E7
//
#define GPIO_PE7_ICEDAT         0x00004701

//
//! GPIO pin F0
//
#define GPIO_PF0_XTAL0          0x00004001

//
//! GPIO pin F1
//
#define GPIO_PF1_XTAL1          0x00005101

//
//! GPIO pin F2
//
#define GPIO_PF2_NINT1          0x00005201

//
//! GPIO pin F3
//
#define GPIO_PF3_ADC0           0x00005301

//
//! GPIO pin F4
//
#define GPIO_PF4_EBINCS         0x00005401

//
//! GPIO pin F5
//
#define GPIO_PF5_EBIALE         0x00005501

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup MINI51_GPIO_Exported_APIs MINI51 GPIO API
//! \brief GPIO API Reference.
//! @{
//
//*****************************************************************************

#define GPIOSPinFunctionSet(ulFunction, eShortPin)                            \
        GPIOPinFunctionSet(ulFunction, G##eShortPin)

#define GPIOSPinIntEnable(eShortPin, ulIntType)                               \
        GPIOPinIntEnable(G##eShortPin, ulIntType)

#define xGPIOSDirModeSet(eShortPin, ulPinIO)                                  \
        xGPIODirModeSet(G##eShortPin, ulPinIO)

#define GPIOSPinIntDisable(eShortPin)                                         \
        GPIOPinIntDisable(G##eShortPin)

#define GPIOSPinIntClear(eShortPin)                                           \
        GPIOPinIntClear(G##eShortPin)

#define GPIOSPinRead(eShortPin)                                               \
        (GPIOPinRead(G##eShortPin) ? 1: 0)

#define GPIOSPinWrite(eShortPin, ucVal)                                       \
        GPIOPinWrite(G##eShortPin, ucVal)

#define GPIOSPinToPeripheralId(eShortPin)                                     \
        GPIOPinToPeripheralId(G##eShortPin)
        
#define GPIOSPinToPort(eShortPin)                                             \
        GPIOPinToPort(G##eShortPin)

#define GPIOSPinToPortPin(eShortPin)                                          \
        G##eShortPin
        
#define GPIOSPinToPin(eShortPin)                                              \
        GPIOPinToPin(G##eShortPin)
        
#define GPIOSPinConfigure(ePeripheralPin, eShortPin)                          \
        GPIOPinConfigure(GPIO_##eShortPin##_##ePeripheralPin)

extern void GPIODirModeSet(unsigned long ulPort, unsigned long ulBit,
                           unsigned long ulPinIO);
extern unsigned long GPIODirModeGet(unsigned long ulPort, unsigned long ulBit);
extern void GPIOPinIntEnable(unsigned long ulPort, unsigned long ulPins,
                             unsigned long ulIntType);
extern void GPIOPinIntDisable(unsigned long ulPort, unsigned long ulPins);
extern void GPIOPinIntCallbackInit(unsigned long ulPort, unsigned long ulPin, 
                                   xtEventCallback xtPortCallback);
extern unsigned long GPIOPinIntStatus(unsigned long ulPort);
extern void GPIOPinIntClear(unsigned long ulPort, unsigned long ulPins);
extern long GPIOPinRead(unsigned long ulPort, unsigned long ulPins);
extern void GPIOPinWrite(unsigned long ulPort, unsigned long ulPins,
		                 unsigned char ucVal);
extern void GPIOPinDebounceEnable(unsigned long ulPort, 
                                  unsigned long ulPins);
extern void GPIOPinDebounceDisable(unsigned long ulPort, 
                                   unsigned long ulPins);
extern void GPIOPinMaskSet(unsigned long ulPort, unsigned long ulPins);
extern void GPIODebounceTimeSet(unsigned long ulClockSource,
                                unsigned long ulDebounceClk);
extern long GPIODebounceTimeGet(void);
extern long GPIOPortMaskGet(unsigned long ulPort);
extern long GPIOPinPortDoutGet(unsigned long ulPort);
extern void GPIOPinFunctionSet(unsigned long ulFunction, unsigned long ulPort, 
                               unsigned long ulPins);
extern void GPIOPinConfigure(unsigned long ulPinConfig);
extern unsigned long  GPIOPinToPeripheralId(unsigned long ulPort, 
                                            unsigned long ulPin);
extern unsigned long  GPIOPinToPort(unsigned long ulPort, 
                                    unsigned long ulPin);
extern unsigned long  GPIOPinToPin(unsigned long ulPort, 
                                   unsigned long ulPin);

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

#endif //  __xGPIO_H__


