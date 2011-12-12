//*****************************************************************************
//
//! \file xgpio.h
//! \brief Defines and Macros for GPIO API.
//! \version V2.1.1.0
//! \date 11/14/2011
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
//extern "C"
//{
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
//! \addtogroup xGPIO_Config xGPIO Config
//! 
//! \section xGPIO_Config_section 1. Where to use this group
//! This is use to config xGPIO intrerrupt number.
//! 
//! \section xGPIO_Config_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO General Pin ID    |       CoX      |         Stellaris      |
//! |------------------------|----------------|------------------------|
//! |xGPIO_INT_NUMBER        |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Total number of interrupt pins used in the application
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
//! \section xGPIO_General_Pin_SIDs 1. Where to use this group
//! The following values define the bit field for the ulPins argument to several
//! of the APIs. So all the API which have a ulPins argument must use this group.
//! 
//! \section xGPIO_General_Pin_IDs_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO General Pin ID    |       CoX      |        Stellaris       |
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
//! |xGPIO Dir Mode          |       CoX      |        Stellaris       |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_IN       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_OUT      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_HW       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_QB       |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_OD       |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Pin is a GPIO input
//
#define xGPIO_DIR_MODE_IN       GPIO_DIR_MODE_IN  

//
//! Pin is a GPIO output
//
#define xGPIO_DIR_MODE_OUT      GPIO_DIR_MODE_OUT 

//
//! Pin is a peripheral function
//
#define xGPIO_DIR_MODE_HW       GPIO_DIR_MODE_HW  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Int_Type xGPIO Intterupt Type
//! 
//! \section xGPIO_Int_Type_S1 1. Where to use this group
//! Values that can be passed to xGPIOIntTypeSet as the ulIntType parameter, and
//! returned from xGPIOIntTypeGet.
//! 
//! \section xGPIO_Int_Type_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO Int Type          |       CoX      |        Stellaris       |
//! |------------------------|----------------|------------------------|
//! |xGPIO_FALLING_EDGE      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_RISING_EDGE       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_LOW_LEVEL         |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_HIGH_LEVEL        |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_BOTH_LEVEL        |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_BOTH_EDGES        |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Interrupt on falling edge
//
#define xGPIO_FALLING_EDGE      GPIO_FALLING_EDGE 

//
//! Interrupt on rising edge
//
#define xGPIO_RISING_EDGE       GPIO_RISING_EDGE 

//
//! Interrupt on both edges
//
#define xGPIO_BOTH_EDGES        GPIO_BOTH_EDGES 

//
//! Interrupt on low level
//
#define xGPIO_LOW_LEVEL         GPIO_LOW_LEVEL  

//
//! Interrupt on high level
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
//! |xGPIO Pad Strength      |       CoX      |        Stellaris       |
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

//
//! 2mA drive strength
//
#define xGPIO_STRENGTH_2MA      GPIO_STRENGTH_2MA  

//
//! 4mA drive strength
//
#define xGPIO_STRENGTH_4MA      GPIO_STRENGTH_4MA

//
//! 8mA drive strength
//
#define xGPIO_STRENGTH_8MA      GPIO_STRENGTH_8MA

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Pad_Config_Type xGPIO Pad Config Type
//! \n
//! \section xGPIO_Pad_Config_Type_S1 1. Where to use this group
//! Values that can be passed to xGPIOPadConfigSet as the ulPadType parameter,
//! and returned by xGPIOPadConfigGet in the *pulPadType parameter.
//! \n
//! \section xGPIO_Pad_Config_Type_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO Pad Type          |       CoX      |        Stellaris       |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_STD      |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_STD_WPU  |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_OD       |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_OD_WPU   |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_OD_WPD   |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_ANALOG   |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_STD_WPD  |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Push-pull
//
#define xGPIO_PIN_TYPE_STD      GPIO_PIN_TYPE_STD  

//
//! Push-pull with weak pull-up
//
#define xGPIO_PIN_TYPE_STD_WPU  GPIO_PIN_TYPE_STD_WPU  

//
//! Push-pull with weak pull-down
//
#define xGPIO_PIN_TYPE_STD_WPD  GPIO_PIN_TYPE_STD_WPD 

//
//! Open-drain
//
#define xGPIO_PIN_TYPE_OD       GPIO_PIN_TYPE_OD

//
//! Open-drain with weak pull-up
//
#define xGPIO_PIN_TYPE_OD_WPU   GPIO_PIN_TYPE_OD_WPU  

//
//! Open-drain with weak pull-down
//
#define xGPIO_PIN_TYPE_OD_WPD   GPIO_PIN_TYPE_OD_WPD 

//
//! Analog(ADC/ACMP Input)
//
#define xGPIO_PIN_TYPE_ANALOG   GPIO_PIN_TYPE_ANALOG

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

#define GPA0                    GPIO_PORTA_BASE, GPIO_PIN_1
#define GPA2                    GPIO_PORTA_BASE, GPIO_PIN_2
#define GPA3                    GPIO_PORTA_BASE, GPIO_PIN_3
#define GPA4                    GPIO_PORTA_BASE, GPIO_PIN_4
#define GPA5                    GPIO_PORTA_BASE, GPIO_PIN_5
#define GPA6                    GPIO_PORTA_BASE, GPIO_PIN_6
#define GPA7                    GPIO_PORTA_BASE, GPIO_PIN_7

#define GPB0                    GPIO_PORTB_BASE, GPIO_PIN_1
#define GPB2                    GPIO_PORTB_BASE, GPIO_PIN_2
#define GPB3                    GPIO_PORTB_BASE, GPIO_PIN_3
#define GPB4                    GPIO_PORTB_BASE, GPIO_PIN_4
#define GPB5                    GPIO_PORTB_BASE, GPIO_PIN_5
#define GPB6                    GPIO_PORTB_BASE, GPIO_PIN_6
#define GPB7                    GPIO_PORTB_BASE, GPIO_PIN_7

#define GPC0                    GPIO_PORTC_BASE, GPIO_PIN_1
#define GPC2                    GPIO_PORTC_BASE, GPIO_PIN_2
#define GPC3                    GPIO_PORTC_BASE, GPIO_PIN_3
#define GPC4                    GPIO_PORTC_BASE, GPIO_PIN_4
#define GPC5                    GPIO_PORTC_BASE, GPIO_PIN_5
#define GPC6                    GPIO_PORTC_BASE, GPIO_PIN_6
#define GPC7                    GPIO_PORTC_BASE, GPIO_PIN_7

#define GPD0                    GPIO_PORTD_BASE, GPIO_PIN_1
#define GPD2                    GPIO_PORTD_BASE, GPIO_PIN_2
#define GPD3                    GPIO_PORTD_BASE, GPIO_PIN_3
#define GPD4                    GPIO_PORTD_BASE, GPIO_PIN_4
#define GPD5                    GPIO_PORTD_BASE, GPIO_PIN_5
#define GPD6                    GPIO_PORTD_BASE, GPIO_PIN_6
#define GPD7                    GPIO_PORTD_BASE, GPIO_PIN_7

#define GPE0                    GPIO_PORTE_BASE, GPIO_PIN_1
#define GPE2                    GPIO_PORTE_BASE, GPIO_PIN_2
#define GPE3                    GPIO_PORTE_BASE, GPIO_PIN_3
#define GPE4                    GPIO_PORTE_BASE, GPIO_PIN_4
#define GPE5                    GPIO_PORTE_BASE, GPIO_PIN_5
#define GPE6                    GPIO_PORTE_BASE, GPIO_PIN_6
#define GPE7                    GPIO_PORTE_BASE, GPIO_PIN_7

#define GPF0                    GPIO_PORTF_BASE, GPIO_PIN_1
#define GPF2                    GPIO_PORTF_BASE, GPIO_PIN_2
#define GPF3                    GPIO_PORTF_BASE, GPIO_PIN_3
#define GPF4                    GPIO_PORTF_BASE, GPIO_PIN_4
#define GPF5                    GPIO_PORTF_BASE, GPIO_PIN_5
#define GPF6                    GPIO_PORTF_BASE, GPIO_PIN_6
#define GPF7                    GPIO_PORTF_BASE, GPIO_PIN_7

#define GPG0                    GPIO_PORTG_BASE, GPIO_PIN_1
#define GPG2                    GPIO_PORTG_BASE, GPIO_PIN_2
#define GPG3                    GPIO_PORTG_BASE, GPIO_PIN_3
#define GPG4                    GPIO_PORTG_BASE, GPIO_PIN_4
#define GPG5                    GPIO_PORTG_BASE, GPIO_PIN_5
#define GPG6                    GPIO_PORTG_BASE, GPIO_PIN_6
#define GPG7                    GPIO_PORTG_BASE, GPIO_PIN_7

#define GPH0                    GPIO_PORTH_BASE, GPIO_PIN_1
#define GPH2                    GPIO_PORTH_BASE, GPIO_PIN_2
#define GPH3                    GPIO_PORTH_BASE, GPIO_PIN_3
#define GPH4                    GPIO_PORTH_BASE, GPIO_PIN_4
#define GPH5                    GPIO_PORTH_BASE, GPIO_PIN_5
#define GPH6                    GPIO_PORTH_BASE, GPIO_PIN_6
#define GPH7                    GPIO_PORTH_BASE, GPIO_PIN_7

#define GPJ0                    GPIO_PORTJ_BASE, GPIO_PIN_1
#define GPJ2                    GPIO_PORTJ_BASE, GPIO_PIN_2
#define GPJ3                    GPIO_PORTJ_BASE, GPIO_PIN_3
#define GPJ4                    GPIO_PORTJ_BASE, GPIO_PIN_4
#define GPJ5                    GPIO_PORTJ_BASE, GPIO_PIN_5
#define GPJ6                    GPIO_PORTJ_BASE, GPIO_PIN_6
#define GPJ7                    GPIO_PORTJ_BASE, GPIO_PIN_7

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
//! of the \b XPinTypexxx APIs and all the API which have a eShortPin argument.
//! Such as \ref xGPIOSPinRead(),\ref xGPIOSPinWrite().
//! 
//! \section xGPIO_Short_Pin_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO Short Pin ID      |       CoX      |        Stellaris       |
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
//! |                        |                |------------------------|
//! |                        |                |    PG0 PG1 ... PG7     |
//! |                        |                |------------------------|
//! |                        |                |    PH0 PH1 ... PH7     |
//! |                        |                |------------------------|
//! |                        |                |    PJ0 PJ1 ... PJ7     |
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

#define PE0                     PE0
#define PE1                     PE1
#define PE2                     PE2
#define PE3                     PE3
#define PE4                     PE4
#define PE5                     PE5
#define PE6                     PE6
#define PE7                     PE7

#define PF0                     PF0
#define PF1                     PF1
#define PF2                     PF2
#define PF3                     PF3
#define PF4                     PF4
#define PF5                     PF5
#define PF6                     PF6
#define PF7                     PF7

#define PG0                     PG0
#define PG1                     PG1
#define PG2                     PG2
#define PG3                     PG3
#define PG4                     PG4
#define PG5                     PG5
#define PG6                     PG6
#define PG7                     PG7

#define PH0                     PH0
#define PH1                     PH1
#define PH2                     PH2
#define PH3                     PH3
#define PH4                     PH4
#define PH5                     PH5
#define PH6                     PH6
#define PH7                     PH7

#define PJ0                     PJ0
#define PJ1                     PJ1
#define PJ2                     PJ2
#define PJ3                     PJ3
#define PJ4                     PJ4
#define PJ5                     PJ5
#define PJ6                     PJ6
#define PJ7                     PJ7
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Peripheral_Pin xGPIO General Peripheral Pin
//! \brief General Peripheral Pin Name.
//!
//! \section xGPIO_Peripheral_Pin_define xGPIO Peripheral Pin define?
//! The macros of General Peripheral Pin Name always like:
//! <b> ModuleName + n + PinName </b>, such as CAN0RX, SPI1CLK.
//!
//! \section xGPIO_Peripheral_Pin_Port CoX Port Details
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |General Peripheral Pin  |       CoX      |        Stellaris       |
//! |------------------------|----------------|------------------------|
//! |ADCn                    |    Mandatory   |   ADC0 ADC1 ... ADC15  |
//! |------------------------|----------------|------------------------|
//! |CANnRX                  |    Mandatory   |      CAN0RX CAN1RX     |
//! |------------------------|----------------|------------------------|
//! |CANnTX                  |    Mandatory   |      CAN0TX CAN1TX     |
//! |------------------------|----------------|------------------------|
//! |CANnRX                  |    Mandatory   |      CAN0RX CAN1RX     |
//! |------------------------|----------------|------------------------|
//! |CANnRX                  |    Mandatory   |      CAN0RX CAN1RX     |
//! |------------------------|----------------|------------------------|
//! |I2CnSCK                 |    Mandatory   | I2C0SCK I2C1SCK I2C2SCK|
//! |------------------------|----------------|------------------------|
//! |I2CnSDA                 |    Mandatory   | I2C0SDA I2C1SDA I2C2SDA|
//! |------------------------|----------------|------------------------|
//! |I2SnRXSCK               |    Mandatory   |        I2S0RXSCK       |
//! |------------------------|----------------|------------------------|
//! |I2SnRXMCLK              |    Mandatory   |       I2S0RXMCLK       |
//! |------------------------|----------------|------------------------|
//! |I2SnRXSD                |    Mandatory   |        I2S0RXSD        |
//! |------------------------|----------------|------------------------|
//! |I2SnRXWS                |    Mandatory   |        I2S0RXWS        |
//! |------------------------|----------------|------------------------|
//! |I2SnTXSCK               |    Mandatory   |        I2S0TXSCK       |
//! |------------------------|----------------|------------------------|
//! |I2SnTXMCLK              |    Mandatory   |       I2S0TXMCLK       |
//! |------------------------|----------------|------------------------|
//! |I2SnTXSD                |    Mandatory   |        I2S0TXSD        |
//! |------------------------|----------------|------------------------|
//! |I2SnTXWS                |    Mandatory   |        I2S0TXWS        |
//! |------------------------|----------------|------------------------|
//! |SPInCLK                 |    Mandatory   |     SPI0CLK SPI1CLK    |
//! |                        |                |------------------------|
//! |                        |                |     SPI2CLK SPI3CLK    |
//! |------------------------|----------------|------------------------|
//! |SPInMOSI                |    Mandatory   |    SPI0MOSI SPI1MOSI   |
//! |                        |                |------------------------|
//! |                        |                |    SPI2MOSI SPI3MOSI   |
//! |------------------------|----------------|------------------------|
//! |SPInMISO                |    Mandatory   |    SPI0MISO SPI1MISO   |
//! |                        |                |------------------------|
//! |                        |                |    SPI2MISO SPI3MISO   |
//! |------------------------|----------------|------------------------|
//! |SPInCS                  |    Mandatory   |      SPI0CS SPI1CS     |
//! |                        |                |------------------------|
//! |                        |                |      SPI2CS SPI3CS     |
//! |------------------------|----------------|------------------------|
//! |UARTnRX                 |    Mandatory   |     UART0RX UART1RX    |
//! |                        |                |------------------------|
//! |                        |                |     UART2RX            |
//! |------------------------|----------------|------------------------|
//! |UARTnTX                 |    Mandatory   |     UART0TX UART1TX    |
//! |                        |                |------------------------|
//! |                        |                |     UART2TX            |
//! |------------------------|----------------|------------------------|
//! |UARTnCTS                |    Mandatory   |    UART0CTS UART1CTS   |
//! |                        |                |------------------------|
//! |                        |                |    UART2CTS            |
//! |------------------------|----------------|------------------------|
//! |UARTnDCD                |    Mandatory   |    UART0DCD UART1DCD   |
//! |                        |                |------------------------|
//! |                        |                |    UART2DCD            |
//! |------------------------|----------------|------------------------|
//! |UARTnDSR                |    Mandatory   |    UART0DSR UART1DSR   |
//! |                        |                |------------------------|
//! |                        |                |    UART2DSR            |
//! |------------------------|----------------|------------------------|
//! |UARTnDTR                |    Mandatory   |    UART0DTR UART1DTR   |
//! |                        |                |------------------------|
//! |                        |                |    UART2DTR            |
//! |------------------------|----------------|------------------------|
//! |CMPnN                   |    Mandatory   |       CMP0N CMP1N      |
//! |------------------------|----------------|------------------------|
//! |CMPnP                   |    Mandatory   |       CMP0P CMP1P      |
//! |------------------------|----------------|------------------------|
//! |CMPnO                   |    Mandatory   |       CMP0O CMP1O      |
//! |------------------------|----------------|------------------------|
//! |PWMn                    |    Mandatory   |      PWM0 ... PWM7     |
//! |------------------------|----------------|------------------------|
//! |TIMCCPn                 |    Mandatory   |   TIMCCP0 ... TIMCCP7  |
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
#define ADC8                    ADC8
#define ADC9                    ADC9
#define ADC10                   ADC10
#define ADC11                   ADC11
#define ADC12                   ADC12
#define ADC13                   ADC13
#define ADC14                   ADC14
#define ADC15                   ADC15

#define CAN0RX                  CAN0RX
#define CAN0TX                  CAN0TX
#define CAN1RX                  CAN1RX
#define CAN1TX                  CAN1TX

#define I2C0SCK                 I2C0SCK
#define I2C0SDA                 I2C0SDA
#define I2C1SCK                 I2C1SCK
#define I2C1SDA                 I2C1SDA
#define I2C2SCK                 I2C2SCK
#define I2C2SDA                 I2C2SDA

#define I2S0RXSCK               I2S0RXSCK
#define I2S0RXMCLK              I2S0RXMCLK
#define I2S0RXSD                I2S0RXSD
#define I2S0RXWS                I2S0RXWS
#define I2S0TXSCK               I2S0TXSCK
#define I2S0TXMCLK              I2S0TXMCLK
#define I2S0TXSD                I2S0TXSD
#define I2S0TXWS                I2S0TXWS

#define SPI0CLK                 SPI0CLK
#define SPI0CS                  SPI0CS
#define SPI0TX                  SPI0TX
#define SPI0RX                  SPI0RX
#define SPI1CLK                 SPI1CLK
#define SPI1CS                  SPI1CS
#define SPI1TX                  SPI1TX
#define SPI1RX                  SPI1RX

#define UART0RX                 UART0RX
#define UART0TX                 UART0TX

#define UART1RX                 UART1RX
#define UART1TX                 UART1TX
#define UART1CTS                UART1CTS
#define UART1DCD                UART1DCD
#define UART1DSR                UART1DSR
#define UART1DTR                UART1DTR
#define UART1RI                 UART1RI
#define UART1RTS                UART1RTS
#define UART2RX                 UART2RX
#define UART2TX                 UART2TX

#define CMP0N                   CMP0N
#define CMP0P                   CMP0P
#define CMP0O                   CMP0O
#define CMP1N                   CMP1N
#define CMP1P                   CMP1P
#define CMP1O                   CMP1O
#define CMP2N                   CMP2N
#define CMP2P                   CMP2P
#define CMP2O                   CMP2O

#define PWM0                    PWM0
#define PWM1                    PWM1
#define PWM2                    PWM2
#define PWM3                    PWM3
#define PWM4                    PWM4
#define PWM5                    PWM5
#define PWM6                    PWM6
#define PWM7                    PWM7

#define TIMCCP0                 TIMCCP0
#define TIMCCP1                 TIMCCP1
#define TIMCCP2                 TIMCCP2
#define TIMCCP3                 TIMCCP3
#define TIMCCP4                 TIMCCP4
#define TIMCCP5                 TIMCCP5
#define TIMCCP6                 TIMCCP6
#define TIMCCP7                 TIMCCP7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Pin_Config xGPIO Pin Config
//! \brief Pins alternate function configs
//!
//! Values that can be passed to xGPIOPinConfigure as the ulPinConfig 
//! parameter. More reference \ref Stellaris_GPIO_Pin_Config.
//!
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
//! |xGPIO API                 |       CoX      |        Stellaris       |
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
//! |xGPIOSPinTypeGPIOOutputOD |  Non-Mandatory |            N           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOSPinTypeGPIOOutputQB |  Non-Mandatory |            N           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypeADC              |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypeCAN              |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypeI2C              |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypeI2S              |  Non-Mandatory |            Y           |
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
//! |xSPinTypeCLKO             |  Non-Mandatory |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypeEXTINT           |        N       |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypeEBI              |  Non-Mandatory |            Y           |
//! +--------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_APIs_internal xGPIO Short Pin API dependence lowlayer API
//! 
//! Users don't need to care about these API.
//! @{
//
//*****************************************************************************

extern unsigned long GPIOPinToPeripheralId(unsigned long ulPort, 
                                           unsigned long ulPin);
extern unsigned long GPIOPinToPort(unsigned long ulPort, unsigned long ulPin);
extern unsigned long GPIOPinToPin(unsigned long ulPort, unsigned long ulPin);   

#define GPIOSPinToPeripheralId(eShortPin)                                     \
        GPIOPinToPeripheralId(G##eShortPin)
        
#define GPIOSPinToPort(eShortPin)                                             \
        GPIOPinToPort(G##eShortPin)

#define GPIOSPinToPortPin(eShortPin)                                          \
        G##eShortPin
        
#define GPIOSPinToPin(eShortPin)                                              \
        GPIOPinToPin(G##eShortPin)

#define GPIOSPinIntEnable(eShortPin, ulIntType)                               \
        GPIOPinIntEnable(G##eShortPin, ulIntType)

#define GPIOSPinIntDisable(eShortPin)                                         \
        GPIOPinIntDisable(G##eShortPin)

#define GPIOSPinIntClear(eShortPin)                                           \
        GPIOPinIntClear(G##eShortPin)

#define GPIOSDirModeSet(eShortPin, ulPinIO)                                   \
        GPIODirModeSet(G##eShortPin, ulPinIO)

#define GPIOSPinRead(eShortPin)                                               \
        (GPIOPinRead(G##eShortPin) ? 1: 0)

#define GPIOSPinWrite(eShortPin, ucVal)                                       \
        GPIOPinWrite(G##eShortPin, ucVal)

#define GPIOSPinConfigure(ePeripheralPin, eShortPin)                          \
        GPIOPinConfigure(GPIO_##eShortPin##_##ePeripheralPin)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

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
#define xGPIOSPinToPortPin(eShortPin)                                         \
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
//! \brief Sets the direction and mode of the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port
//! \param ucPins is the bit-packed representation of the pin(s).
//! \param ulPinIO is the pin direction and/or mode.
//!
//! This function will set the specified pin(s) on the selected GPIO port
//! as either an input or output under software control, or it will set the
//! pin to be under hardware control.
//!
//! The parameter \e ulPinIO is an enumerated data type that can be one of
//! the following values:
//!
//! - \b xGPIO_DIR_MODE_IN
//! - \b xGPIO_DIR_MODE_OUT
//! - \b xGPIO_DIR_MODE_HW
//!
//! where \b xGPIO_DIR_MODE_IN specifies that the pin will be programmed as
//! a software controlled input, \b xGPIO_DIR_MODE_OUT specifies that the pin
//! will be programmed as a software controlled output, and
//! \b xGPIO_DIR_MODE_HW specifies that the pin will be placed under
//! hardware control.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note xGPIOPadConfigSet() must also be used to configure the corresponding
//! pad(s) in order for them to propagate the signal to/from the GPIO.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIODirModeSet(ulPort, ulPins, ulPinIO)                              \
        GPIODirModeSet(ulPort, (unsigned char)ulPins, ulPinIO)

//*****************************************************************************
//
//! \brief Gets the direction and mode of a pin.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPin is the pin number.
//!
//! This function gets the direction and control mode for a specified pin on
//! the selected GPIO port.  The pin can be configured as either an input or
//! output under software control, or it can be under hardware control.  The
//! type of control and direction are returned as an enumerated data type.
//!
//! \return Returns one of the enumerated data types described for
//! xGPIODirModeSet().
//
//*****************************************************************************
#define xGPIODirModeGet(ulPort, ulPin)                                        \
        GPIODirModeGet(ulPort, (unsigned char)ulPin) 

//*****************************************************************************
//
//! \brief Sets the pad configuration for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//! \param ulStrength specifies the output drive strength.
//! \param ulPinType specifies the pin type.
//!
//! This function sets the drive strength and type for the specified pin(s)
//! on the selected GPIO port.  For pin(s) configured as input ports, the
//! pad is configured as requested, but the only real effect on the input
//! is the configuration of the pull-up or pull-down termination.
//!
//! The parameter \e ulStrength can be one of the following values:
//!
//! - \b xGPIO_STRENGTH_2MA
//! - \b xGPIO_STRENGTH_4MA
//! - \b xGPIO_STRENGTH_8MA
//!
//! where \b xGPIO_STRENGTH_xMA specifies either 2, 4, or 8 mA output drive
//! strength, and \b xGPIO_OUT_STRENGTH_8MA_SC specifies 8 mA output drive with
//! slew control.
//!
//! The parameter \e ulPinType can be one of the following values:
//!
//! - \b xGPIO_PIN_TYPE_STD
//! - \b xGPIO_PIN_TYPE_STD_WPU
//! - \b xGPIO_PIN_TYPE_STD_WPD
//! - \b xGPIO_PIN_TYPE_OD
//! - \b xGPIO_PIN_TYPE_OD_WPU
//! - \b xGPIO_PIN_TYPE_OD_WPD
//! - \b xGPIO_PIN_TYPE_ANALOG
//!
//! where \b xGPIO_PIN_TYPE_STD* specifies a push-pull pin, \b xGPIO_PIN_TYPE_OD*
//! specifies an open-drain pin, \b *_WPU specifies a weak pull-up, \b *_WPD
//! specifies a weak pull-down, and \b xGPIO_PIN_TYPE_ANALOG specifies an
//! analog input (for the comparators).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOPadConfigSet(ulPort, ulPins, ulStrength, ulPadType)              \
        GPIOPadConfigSet(ulPort, (unsigned char)ulPins, ulStrength, ulPadType)

//*****************************************************************************
//
//! \brief Gets the pad configuration for a pin.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPin is the pin number.
//! \param pulStrength is a pointer to storage for the output drive strength.
//! \param pulPinType is a pointer to storage for the output drive type.
//!
//! This function gets the pad configuration for a specified pin on the
//! selected GPIO port.  The values returned in \e pulStrength and
//! \e pulPinType correspond to the values used in xGPIOPadConfigSet().  This
//! function also works for pin(s) configured as input pin(s); however, the
//! only meaningful data returned is whether the pin is terminated with a
//! pull-up or down resistor.
//!
//! \return None.
//
//*****************************************************************************        
#define xGPIOPadConfigGet(ulPort, ulPin, pulStrength, pulPadType)             \
        GPIOPadConfigGet(ulPort, (unsigned char)ulPin, pulStrength, pulPadType)

//*****************************************************************************
//
//! \brief Configures the alternate function of a GPIO pin.
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
//! Reference \ref xGPIO_Pin_Config.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOPinConfigure(ulPinConfig)                                        \
        GPIOPinConfigure(ulPinConfig)


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
//! - ulMsgParam not used, always 0.
//! - pvMsgData not used, always 0.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOPinIntCallbackInit(ulPort, ulPin, pfnCallback)                   \
        GPIOPinIntCallbackInit(ulPort, ulPin, pfnCallback)

//*****************************************************************************
//
//! \brief Sets the interrupt type for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//! \param ulIntType specifies the type of interrupt trigger mechanism.
//!
//! \details This function sets up the various interrupt trigger mechanisms for the
//! specified pin(s) on the selected GPIO port.
//!
//! The parameter \e ulIntType is an enumerated data type that can be one of
//! the following values:
//!
//! - \b xGPIO_FALLING_EDGE
//! - \b xGPIO_RISING_EDGE
//! - \b xGPIO_BOTH_EDGES
//! - \b xGPIO_LOW_LEVEL
//! - \b xGPIO_HIGH_LEVEL
//!
//! where the different values describe the interrupt detection mechanism
//! (edge or level) and the particular triggering event (falling, rising,
//! or both edges for edge detect, low or high for level detect).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note In order to avoid any spurious interrupts, the user must
//! ensure that the GPIO inputs remain stable for the duration of
//! this function.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOIntTypeSet(ulPort, ucPins, ulIntType)                            \
        GPIOIntTypeSet(ulPort, ucPins, ulIntType)


//*****************************************************************************
//
//! \brief Gets the interrupt type for a pin.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPin is the pin number.
//!
//! This function gets the interrupt type for a specified pin on the selected
//! GPIO port.  The pin can be configured as a falling edge, rising edge, or
//! both edge detected interrupt, or it can be configured as a low level or
//! high level detected interrupt.  The type of interrupt detection mechanism
//! is returned as an enumerated data type.
//!
//! \return Returns one of the enumerated data types described for
//! xGPIOIntTypeSet().
//
//*****************************************************************************
#define xGPIOIntTypeGet(ulPort, ucPins)                                       \
        GPIOIntTypeGet(ulPort, ucPins)


//*****************************************************************************
//
//! \brief Sets the interrupt type and Enable interrupt for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//! \param ulIntType specifies the type of interrupt trigger mechanism.
//!
//! This function sets up the various interrupt trigger mechanisms for the
//! specified pin(s) on the selected GPIO port.
//!
//! The parameter \e ulIntType is an enumerated data type that can be one of
//! the following values:
//!
//! - \b xGPIO_FALLING_EDGE
//! - \b xGPIO_RISING_EDGE
//! - \b xGPIO_BOTH_EDGES
//! - \b xGPIO_LOW_LEVEL
//! - \b xGPIO_HIGH_LEVEL
//!
//! where the different values describe the interrupt detection mechanism
//! (edge or level) and the particular triggering event (falling, rising,
//! or both edges for edge detect, low or high for level detect).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note In order to avoid any spurious interrupts, the user must
//! ensure that the GPIO inputs remain stable for the duration of
//! this function.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOPinIntEnable(ulPort, ulPins, ulIntType)                          \
        do                                                                    \
        {                                                                     \
         GPIOIntTypeSet(ulPort, (unsigned char)ulPins, ulIntType);            \
         GPIOPinIntEnable(ulPort, (unsigned char)ulPins);                     \
        }                                                                     \
        while(0)

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
//! the following values:
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
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! Masks the interrupt for the specified pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOPinIntDisable(ulPort, ulPins)                                    \
        GPIOPinIntDisable(ulPort, (unsigned char)ulPins)

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
//! \brief Reads the values present of the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The values at the specified pin(s) are read, as specified by \e ucPins.
//! Values are returned for both input and output pin(s), and the value
//! for pin(s) that are not specified by \e ucPins are set to 0.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return Returns a bit-packed byte providing the state of the specified
//! pin, where bit 0 of the byte represents GPIO port pin 0, bit 1 represents
//! GPIO port pin 1, and so on.  Any bit that is not specified by \e ucPins
//! is returned as a 0.  Bits 31:8 should be ignored.
//
//*****************************************************************************
#define xGPIOPinRead(ulPort, ulPins)                                          \
        GPIOPinRead(ulPort, (unsigned char)ulPins)

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
//! \brief Writes a value to the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//! \param ucVal is the value to write to the pin(s).
//!
//! Writes the corresponding bit values to the output pin(s) specified by
//! \e ucPins.  Writing to a pin configured as an input pin has no effect.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOPinWrite(ulPort, ulPins, ucVal)                                  \
        GPIOPinWrite(ulPort, (unsigned char)ulPins, ucVal)

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
//! \brief Turn a pin to an GPIO Input pin.
//!
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin.
//!
//! This function configures a pin for use as an GPIO Input pin device and turn 
//!  the pin into a GPIO input pin.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinTypeGPIOInput(eShortPin)                                     \
        do                                                                    \
        {                                                                     \
         GPIOPinTypeGPIOInput(GPIOSPinToPortPin(eShortPin));                  \
        }                                                                     \
        while(0)


//*****************************************************************************
//
//! \brief Turn a pin to an GPIO Output(push-pull) pin.
//!
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin.
//!
//! This function configures a pin for use as an GPIO Output pin device and turn 
//!  the pin into a GPIO Output pin.
//!
//! \return None.
//
//*****************************************************************************

#define xGPIOSPinTypeGPIOOutput(eShortPin)                                    \
        do                                                                    \
        {                                                                     \
         GPIOPinTypeGPIOOutput(GPIOSPinToPortPin(eShortPin));                 \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief Turn a pin to an GPIO Output(open drain) pin.
//!
//! \param eShortPin is the GPIO short pin name such as PA0.
//! Details please refer to \ref xGPIO_Short_Pin.
//!
//! This function configures a pin for use as an GPIO Output pin device and turn 
//!  the pin into a GPIO Output(open drain) pin.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinTypeGPIOOutputOD(eShortPin)                                  \
        do                                                                    \
        {                                                                     \
         GPIOPinTypeGPIOOutputOD(GPIOSPinToPortPin(eShortPin));               \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO ACMP analog input.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as CMP0N. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as an ACMP function and turns 
//!  the pin into an ACMP analog input.
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
//! |    Stellaris       |    CMP0P               |    PB6                 |
//! |                    |    CMP0N               |    PB4                 |
//! |                    |    CMP1P               |    PC5                 |
//! |                    |    CMP1N               |    PB5                 |
//! |                    |    CMP2P               |    PC6                 |
//! |                    |    CMP2N               |    PC7                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************            
#define xSPinTypeACMPAnalog(ePeripheralPin, eShortPin)                        \
        do                                                                    \
        {                                                                     \
         GPIOPinTypeACMPAnalog(GPIOSPinToPortPin(eShortPin));                 \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO ACMP analog input.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as CMP0N. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as an ACMP function and turns 
//!  the pin into an ACMP analog input.
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
//! |    Stellaris       |    CMP0O               |PC5  PF4  PB6  PB5  PD7 |
//! |                    |    CMP1O               |PE6  PC7  PC5  PF5  PH2 |
//! |                    |    CMP2O               |PE7  PC6                |
//! +--------------------+------------------------+------------------------+
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************            
#define xSPinTypeACMPDigital(ePeripheralPin, eShortPin)                       \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOPinTypeACMPDigital(GPIOSPinToPortPin(eShortPin));                \
        }                                                                     \
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
//! the pin into an ADC input pin.
//!
//! Table shows what the ePeripheralPin and eShortPin should be, only the 
//! argument which are in the same line can be combined. For eaxmple(TI):<br/>
//! xSPinTypeADC(ADC0, PE7) or xSPinTypeADC(ADC1, PE6) is correct;<br/>
//! But xSPinTypeADC(ADC0, PE6) or xSPinTypeADC(ADC0, PE5) is error.
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
//! |    Stellaris       |    ADC0                |    PE7                 |
//! |                    |    ADC1                |    PE6                 |
//! |                    |    ADC2                |    PE5                 |
//! |                    |    ADC3                |    PE4                 |
//! |                    |    ADC4                |    PD7                 |
//! |                    |    ADC5                |    PD6                 |
//! |                    |    ADC6                |    PD5                 |
//! |                    |    ADC7                |    PD4                 |
//! |                    |    ADC8                |    PE3                 |
//! |                    |    ADC9                |    PE2                 |
//! |                    |    ADC10               |    PB4                 |
//! |                    |    ADC11               |    PB5                 |
//! |                    |    ADC12               |    PD3                 |
//! |                    |    ADC13               |    PD2                 |
//! |                    |    ADC14               |    PD1                 |
//! |                    |    ADC15               |    PD0                 |
//! |                    |    VREFA               |    PB6                 |
//! +--------------------+------------------------+------------------------+
//! \endverbatim
//!
//! \return None.
//
//***************************************************************************** 
#define xSPinTypeADC(ePeripheralPin, eShortPin)                               \
        do                                                                    \
        {                                                                     \
         GPIOPinTypeADC(GPIOSPinToPortPin(eShortPin));                        \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO CAN input or output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as CAN0RX. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as a CAN function and turns 
//! the pin into an CAN input or output pin.
//!
//! Table shows what the ePeripheralPin and eShortPin should be,only the 
//! argument which are in the same line can be combined.For eaxmple(TI):<br/>
//! xSPinTypeCAN(CAN0RX, PA4) or xSPinTypeCAN(CAN0RX, PB4) is correct;<br/>
//! But xSPinTypeCAN(CAN0RX, PA5) or xSPinTypeCAN(CAN0RX, PF0) is error.
//! \verbatim
//! +--------------------+------------------------+------------------------+
//! |    manufacturer    |ePeripheralPin          |eShortPin               |
//! |--------------------|------------------------|------------------------|
//! |    CoX             |This parameter is a     |This parameter is a     |
//! |                    |mandatory.The mandatory |mandatory. the mandatory|
//! |                    |is the format of        |is the format of        |
//! |                    |Variable naming.So it   |Variable naming.So it   |
//! |                    |should be: CANnRX       |should be: PXn          |
//! |                    |or CANnTX               |XX indicate the GPIO    |
//! |                    |n indicate the pin      |PORT,Such as            |
//! |                    |number such as          |A B C D E ...           |
//! |                    |0 1 2 3 ....            |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |    Stellaris       |    CAN0RX              |PD0  PA4  PA6  PB4      |
//! |                    |    CAN0TX              |PD1  PA5  PA7  PB5      |
//! |                    |    CAN1RX              |PF0                     |
//! |                    |    CAN1TX              |PF1                     |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeCAN(ePeripheralPin, eShortPin)                               \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOPinTypeCAN(GPIOSPinToPortPin(eShortPin));                        \
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
//! the pin into an I2C input or output pin.
//!
//! Table shows what the ePeripheralPin and eShortPin should be,only the 
//! argument which are in the same line can be combined.For eaxmple(TI):<br/>
//! xSPinTypeI2C(CAN0RX, PA4) or xSPinTypeI2C(CAN0RX, PB4) is correct;<br/>
//! But xSPinTypeI2C(CAN0RX, PA5) or xSPinTypeI2C(CAN0RX, PF0) is error.
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
//! |    Stellaris       |    I2C0SCK             |PB2                     |
//! |                    |    I2C0SDA             |PB3                     |
//! |                    |    I2C1SCK             |PJ0  PG0  PA0  PA6      |
//! |                    |    I2C1SDA             |PJ1  PG1  PA1  PA7      |
//! +--------------------+------------------------+------------------------+
//! \endverbatim
//!
//! \return None.
//
//***************************************************************************** 
#define xSPinTypeI2C(ePeripheralPin, eShortPin)                               \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOPinTypeI2C(GPIOSPinToPortPin(eShortPin));                        \
        }                                                                     \
        while(0)


//*****************************************************************************
//
//! \brief Turn a pin to a GPIO I2S input or output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as I2C0SDA. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as an I2S function device and turns 
//!  the pin into a GPIO I2S input or output pin.
//!
//! Table shows what the ePeripheralPin and eShortPin should be,only the 
//! argument which are in the same line can be combined.For eaxmple(TI):<br/>
//! xSPinTypeI2S(I2S0RXSD, PA2) or xSPinTypeI2S(I2S0RXSD, PD4) is correct;<br/>
//! But xSPinTypeI2S(I2S0RXSD, PD1) or xSPinTypeI2S(I2S0RXWS, PA2) is error.
//! \verbatim
//! +--------------------+------------------------+------------------------+
//! |    manufacturer    |ePeripheralPin          |eShortPin               |
//! |--------------------|------------------------|------------------------|
//! |    CoX             |This parameter is a     |This parameter is a     |
//! |                    |mandatory.The mandatory |mandatory. the mandatory|
//! |                    |is the format of        |is the format of        |
//! |                    |Variable naming.So it   |Variable naming.So it   |
//! |                    |should be: I2SnRXSCK,   |should be: PXn          |
//! |                    |I2SnRXMCLK,I2S0RXSD,    |XX indicate the GPIO    |
//! |                    |I2S0RXWS,I2S0TXSCK,     |PORT,Such as            |
//! |                    |I2S0TXMCLK,I2S0TXSD,    |A B C D E ...           |
//! |                    |or I2S0TXWS.            |n indicate the pin      |
//! |                    |n indicate the pin      |number such as          |
//! |                    |number such as          |0 1 2 3 ....            |
//! |                    |0 1 2 3 ....            |                        |
//! |--------------------|------------------------|------------------------|
//! |    Stellaris       |    I2S0RXMCLK          |PA3  PD5                |
//! |                    |    I2S0RXSCK           |PD0                     |
//! |                    |    I2S0RXSD            |PA2  PD4                |
//! |                    |    I2S0RXWS            |PD1                     |
//! |                    |    I2S0TXMCLK          |PF1                     |
//! |                    |    I2S0TXSCK           |PA4  PB6  PD6           |
//! |                    |    I2S0TXSD            |PE5  PF0                |
//! |                    |    I2S0TXWS            |PE4  PA5  PD7           |
//! +--------------------+------------------------+------------------------+
//! \endverbatim
//!
//! \return None.
//
//***************************************************************************** 
#define xSPinTypeI2S(ePeripheralPin, eShortPin)                               \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOPinTypeI2S(GPIOSPinToPortPin(eShortPin));                        \
        }                                                                     \
        while(0)
                    
//*****************************************************************************
//
//! \brief Turn a pin to a GPIO PWM input or output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as I2C0SDA. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as a PWM function and turns 
//!  the pin into a GPIO PWM input or output pin.
//!
//! Table shows what the ePeripheralPin and eShortPin should be,only the 
//! argument which are in the same line can be combined.For eaxmple(TI):<br/>
//! xSPinTypePWM(PWM0, PD0) or xSPinTypePWM(PWM0, PJ0) is correct;<br/>
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
//! |    Stellaris       |    PWM0                |PD0  PJ0  PG0  PA6  PF0 |
//! |                    |    PWM1                |PD1  PJ1  PG1  PA7  PF1 |
//! |                    |    PWM2                |PD2  PF2  PB0  PH0      |
//! |                    |    PWM3                |PD3  PF3  PB1  PH1      |
//! |                    |    PWM4                |PE6  PG0  PA2  PA6  PF2 |
//! |                    |                        |PH6  PE0  PH0           |
//! |                    |    PWM5                |PE7  PH7  PG1  PA3  PA7 |
//! |                    |                        |PF3  PE1  PH1           |
//! |                    |    PWM6                |PC4  PA4                |
//! |                    |    PWM7                |PC6  PA5  PG7           |
//! +--------------------+------------------------+------------------------+
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************         
#define xSPinTypePWM(ePeripheralPin, eShortPin)                               \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOPinTypePWM(GPIOSPinToPortPin(eShortPin));                        \
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
//! xSPinTypeSPI(SPI0CLK, PA2) or xSPinTypeSPI(SPI0MOSI, PA5) is correct;<br/>
//! But xSPinTypeSPI(SPI0CLK, PA5) or xSPinTypeSPI(SPI0CLK, PA4) is error.
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
//! |    Stellaris       |    SPI0CLK             |PA2                     |
//! |                    |    SPI0TX              |PA5                     |
//! |                    |    SPI0RX              |PA4                     |
//! |                    |    SPI0CS              |PA3                     |
//! |                    |    SPI1CLK             |PF2  PE0  PH4           |
//! |                    |    SPI1TX              |PH7  PF5  PE3           |
//! |                    |    SPI1RX              |PF4  PH6  PE2           |
//! |                    |    SPI1CS              |PF3  PH5  PE1           |
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
         GPIOPinTypeSPI(GPIOSPinToPortPin(eShortPin));                        \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO Timer input or output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as I2C0SDA. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as a Timer function and turns 
//!  the pin into a GPIO Timer input or output pin.
//!
//! Table shows what the ePeripheralPin and eShortPin should be,only the 
//! argument which are in the same line can be combined.For eaxmple(TI):<br/>
//! xSPinTypeTimer(TIMCCP0, PD3) or xSPinTypeTimer(TIMCCP0, PJ7) is correct;<br/>
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
//! |    Stellaris       |TIMCCP0                 |PD3  PC7  PC6  PJ2  PF4 |  
//! |                    |                        |PJ7  PB0  PB2  PB5  PD4 |
//! |                    |TIMCCP1                 |PC5  PC4  PA6  PJ6  PB1 | 
//! |                    |                        |PB6  PE3  PD7           |
//! |                    |TIMCCP2                 |PE4  PD1  PC4  PF5  PJ5 | 
//! |                    |                        |PB1  PE1  PB5  PE2  PD5 |
//! |                    |TIMCCP3                 |PE4  PC6  PC5  PA7  PF1 | 
//! |                    |                        |PB2  PE0  PD4           |
//! |                    |TIMCCP4                 |PC7  PC4  PA7  PJ4  PE2 |
//! |                    |                        |PD5                     |
//! |                    |TIMCCP5                 |PE5  PD2  PC4  PG7  PB6 | 
//! |                    |                        |PB5                     |
//! |                    |TIMCCP6                 |PD0  PD2  PJ3  PE1  PH0 | 
//! |                    |                        |PB5                     |
//! |                    |TIMCCP7                 |PD1  PD3  PH1  PB6  PE3 | 
//! +--------------------+------------------------+------------------------+
//! \endverbatim
//!
//! \return None.
//
//***************************************************************************** 
#define xSPinTypeTimer(ePeripheralPin, eShortPin)                             \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOPinTypeTimer(GPIOSPinToPortPin(eShortPin));                      \
        }                                                                     \
        while(0)
                    
//*****************************************************************************
//
//! \brief Turn a pin to a GPIO UART input or output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as I2C0SDA. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as a UART function and turns 
//!  the pin into a GPIO UART input or output pin.
//!
//! Table shows what the ePeripheralPin and eShortPin should be,only the 
//! argument which are in the same line can be combined.For eaxmple(TI):<br/>
//! xSPinTypeUART(UART0RX, PA0) or xSPinTypeUART(UART0TX, PA1) is correct;<br/>
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
//! |       Stellaris    |    UART0RX             |PA0                     |
//! |                    |    UART0TX             |PA1                     |
//! |                    |    UART1CTS            |PE6  PD0  PA6  PJ3      |
//! |                    |    UART1DCD            |PE7  PD1  PA7  PJ4      |
//! |                    |    UART1DSR            |PF0  PJ5                |
//! |                    |    UART1DTR            |PJ7  PD7                |
//! |                    |    UART1RI             |PD4                     |
//! |                    |    UART1RTS            |PJ6  PF1                |
//! |                    |    UART1RX             |PD0  PD2  PC6  PA0  PB0 |
//! |                    |                        |PB4                     |
//! |                    |    UART1TX             |PD1  PD3  C7   PA1  PB1 | 
//! |                    |                        |PB5                     |
//! |                    |    UART2RX             |PD0  PG0  PB4  PB5      |
//! |                    |    UART2TX             |PE4  PD1  PG1  PD6      | 
//! +--------------------+------------------------+------------------------+
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************        
#define xSPinTypeUART(ePeripheralPin, eShortPin)                              \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOPinTypeUART(GPIOSPinToPortPin(eShortPin));                       \
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
//! \addtogroup Stellaris_GPIO
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_GPIO_General_Pin_IDs
//! The following values define the bit field for the ucPins argument to several
//! of the APIs.
//! @{
//
//*****************************************************************************

#define GPIO_PIN_0              0x00000001  // GPIO pin 0
#define GPIO_PIN_1              0x00000002  // GPIO pin 1
#define GPIO_PIN_2              0x00000004  // GPIO pin 2
#define GPIO_PIN_3              0x00000008  // GPIO pin 3
#define GPIO_PIN_4              0x00000010  // GPIO pin 4
#define GPIO_PIN_5              0x00000020  // GPIO pin 5
#define GPIO_PIN_6              0x00000040  // GPIO pin 6
#define GPIO_PIN_7              0x00000080  // GPIO pin 7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_GPIO_Dir_Mode
//! Values that can be passed to GPIODirModeSet as the ulPinIO parameter, and
//! returned from GPIODirModeGet.
//! @{
//
//*****************************************************************************

#define GPIO_DIR_MODE_IN        0x00000000  // Pin is a GPIO input
#define GPIO_DIR_MODE_OUT       0x00000001  // Pin is a GPIO output
#define GPIO_DIR_MODE_HW        0x00000002  // Pin is a peripheral function

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_GPIO_Int_Type
//! Values that can be passed to GPIOIntTypeSet as the ulIntType parameter, and
//! returned from GPIOIntTypeGet.
//! @{
//
//*****************************************************************************

#define GPIO_FALLING_EDGE       0x00000000  // Interrupt on falling edge
#define GPIO_RISING_EDGE        0x00000004  // Interrupt on rising edge
#define GPIO_BOTH_EDGES         0x00000001  // Interrupt on both edges
#define GPIO_LOW_LEVEL          0x00000002  // Interrupt on low level
#define GPIO_HIGH_LEVEL         0x00000007  // Interrupt on high level

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_GPIO_Pad_Config_Strength
//! Values that can be passed to GPIOPadConfigSet as the ulStrength parameter,
//! and returned by GPIOPadConfigGet in the *pulStrength parameter.
//! @{
//
//*****************************************************************************

#define GPIO_STRENGTH_2MA       0x00000001  // 2mA drive strength
#define GPIO_STRENGTH_4MA       0x00000002  // 4mA drive strength
#define GPIO_STRENGTH_8MA       0x00000004  // 8mA drive strength
#define GPIO_STRENGTH_8MA_SC    0x0000000C  // 8mA drive with slew rate control

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_GPIO_Pad_Config_Type
//! Values that can be passed to GPIOPadConfigSet as the ulPadType parameter,
//! and returned by GPIOPadConfigGet in the *pulPadType parameter.
//! @{
//
//*****************************************************************************

#define GPIO_PIN_TYPE_STD       0x00000008  // Push-pull
#define GPIO_PIN_TYPE_STD_WPU   0x0000000A  // Push-pull with weak pull-up
#define GPIO_PIN_TYPE_STD_WPD   0x0000000C  // Push-pull with weak pull-down
#define GPIO_PIN_TYPE_OD        0x00000009  // Open-drain
#define GPIO_PIN_TYPE_OD_WPU    0x0000000B  // Open-drain with weak pull-up
#define GPIO_PIN_TYPE_OD_WPD    0x0000000D  // Open-drain with weak pull-down
#define GPIO_PIN_TYPE_ANALOG    0x00000000  // Analog comparator

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_GPIO_Pin_Config
//! Values that can be passed to xGPIOPinConfigure as the ulPinConfig parameter.
//! @{
//
//*****************************************************************************

//
// GPIO pin A0
//
#define GPIO_PA0_UART0RX        0x00000001
#define GPIO_PA0_I2C1SCK        0x00000008
#define GPIO_PA0_UART1RX        0x00000009

//
// GPIO pin A1
//
#define GPIO_PA1_UART0TX        0x00000401
#define GPIO_PA1_I2C1SDA        0x00000408
#define GPIO_PA1_UART1TX        0x00000409

//
// GPIO pin A2
//
#define GPIO_PA2_SPI0CLK        0x00000801
#define GPIO_PA2_PWM4           0x00000804
#define GPIO_PA2_I2S0RXSD       0x00000809

//
// GPIO pin A3
//
#define GPIO_PA3_SPI0CS         0x00000c01
#define GPIO_PA3_PWM5           0x00000c04
#define GPIO_PA3_I2S0RXMCLK     0x00000c09

//
// GPIO pin A4
//
#define GPIO_PA4_SPI0RX         0x00001001
#define GPIO_PA4_PWM6           0x00001004
#define GPIO_PA4_CAN0RX         0x00001005
#define GPIO_PA4_I2S0TXSCK      0x00001009

//
// GPIO pin A5
//
#define GPIO_PA5_SPI0TX         0x00001401
#define GPIO_PA5_PWM7           0x00001404
#define GPIO_PA5_CAN0TX         0x00001405
#define GPIO_PA5_I2S0TXWS       0x00001409

//
// GPIO pin A6
//
#define GPIO_PA6_I2C1SCK        0x00001801
#define GPIO_PA6_TIMCCP1        0x00001802
#define GPIO_PA6_PWM0           0x00001804
#define GPIO_PA6_PWM4           0x00001805
#define GPIO_PA6_CAN0RX         0x00001806
#define GPIO_PA6_USB0EPEN       0x00001808
#define GPIO_PA6_UART1CTS       0x00001809

//
// GPIO pin A7
//
#define GPIO_PA7_I2C1SDA        0x00001c01
#define GPIO_PA7_TIMCCP4        0x00001c02
#define GPIO_PA7_PWM1           0x00001c04
#define GPIO_PA7_PWM5           0x00001c05
#define GPIO_PA7_CAN0TX         0x00001c06
#define GPIO_PA7_TIMCCP3        0x00001c07
#define GPIO_PA7_USB0PFLT       0x00001c08
#define GPIO_PA7_UART1DCD       0x00001c09

//
// GPIO pin B0
//
#define GPIO_PB0_TIMCCP0        0x00010001
#define GPIO_PB0_PWM2           0x00010002
#define GPIO_PB0_UART1RX        0x00010005

//
// GPIO pin B1
//
#define GPIO_PB1_TIMCCP2        0x00010401
#define GPIO_PB1_PWM3           0x00010402
#define GPIO_PB1_TIMCCP1        0x00010404
#define GPIO_PB1_UART1TX        0x00010405

//
// GPIO pin B2
//
#define GPIO_PB2_I2C0SCK        0x00010801
#define GPIO_PB2_IDX0           0x00010802
#define GPIO_PB2_TIMCCP3        0x00010804
#define GPIO_PB2_TIMCCP0        0x00010805
#define GPIO_PB2_USB0EPEN       0x00010808

//
// GPIO pin B3
//
#define GPIO_PB3_I2C0SDA        0x00010c01
#define GPIO_PB3_FAULT0         0x00010c02
#define GPIO_PB3_FAULT3         0x00010c04
#define GPIO_PB3_USB0PFLT       0x00010c08

//
// GPIO pin B4
//
#define GPIO_PB4_UART2RX        0x00011004
#define GPIO_PB4_CAN0RX         0x00011005
#define GPIO_PB4_IDX0           0x00011006
#define GPIO_PB4_UART1RX        0x00011007
#define GPIO_PB4_EPI0S23        0x00011008

//
// GPIO pin B5
//
#define GPIO_PB5_CMP0O          0x00011401
#define GPIO_PB5_TIMCCP5        0x00011402
#define GPIO_PB5_TIMCCP6        0x00011403
#define GPIO_PB5_TIMCCP0        0x00011404
#define GPIO_PB5_CAN0TX         0x00011405
#define GPIO_PB5_TIMCCP2        0x00011406
#define GPIO_PB5_UART1TX        0x00011407
#define GPIO_PB5_EPI0S22        0x00011408

//
// GPIO pin B6
//
#define GPIO_PB6_TIMCCP1        0x00011801
#define GPIO_PB6_TIMCCP7        0x00011802
#define GPIO_PB6_CMP0O          0x00011803
#define GPIO_PB6_FAULT1         0x00011804
#define GPIO_PB6_IDX0           0x00011805
#define GPIO_PB6_TIMCCP5        0x00011806
#define GPIO_PB6_I2S0TXSCK      0x00011809

//
// GPIO pin B7
//
#define GPIO_PB7_NMI            0x00011c04

//
// GPIO pin C0
//
#define GPIO_PC0_TCK            0x00020003

//
// GPIO pin C1
//
#define GPIO_PC1_TMS            0x00020403

//
// GPIO pin C2
//
#define GPIO_PC2_TDI            0x00020803

//
// GPIO pin C3
//
#define GPIO_PC3_TDO            0x00020c03

//
// GPIO pin C4
//
#define GPIO_PC4_TIMCCP5        0x00021001
#define GPIO_PC4_PHA0           0x00021002
#define GPIO_PC4_PWM6           0x00021004
#define GPIO_PC4_TIMCCP2        0x00021005
#define GPIO_PC4_TIMCCP4        0x00021006
#define GPIO_PC4_EPI0S2         0x00021008
#define GPIO_PC4_TIMCCP1        0x00021009

//
// GPIO pin C5
//
#define GPIO_PC5_TIMCCP1        0x00021401
#define GPIO_PC5_CMP1O          0x00021402
#define GPIO_PC5_CMP0O          0x00021403
#define GPIO_PC5_FAULT2         0x00021404
#define GPIO_PC5_TIMCCP3        0x00021405
#define GPIO_PC5_USB0EPEN       0x00021406
#define GPIO_PC5_EPI0S3         0x00021408

//
// GPIO pin C6
//
#define GPIO_PC6_TIMCCP3        0x00021801
#define GPIO_PC6_PHB0           0x00021802
#define GPIO_PC6_CMP2O          0x00021803
#define GPIO_PC6_PWM7           0x00021804
#define GPIO_PC6_UART1RX        0x00021805
#define GPIO_PC6_TIMCCP0        0x00021806
#define GPIO_PC6_USB0PFLT       0x00021807
#define GPIO_PC6_EPI0S4         0x00021808

//
// GPIO pin C7
//
#define GPIO_PC7_TIMCCP4        0x00021c01
#define GPIO_PC7_PHB0           0x00021c02
#define GPIO_PC7_TIMCCP0        0x00021c04
#define GPIO_PC7_UART1TX        0x00021c05
#define GPIO_PC7_USB0PFLT       0x00021c06
#define GPIO_PC7_CMP1O          0x00021c07
#define GPIO_PC7_EPI0S5         0x00021c08

//
// GPIO pin D0
//
#define GPIO_PD0_PWM0           0x00030001
#define GPIO_PD0_CAN0RX         0x00030002
#define GPIO_PD0_IDX0           0x00030003
#define GPIO_PD0_UART2RX        0x00030004
#define GPIO_PD0_UART1RX        0x00030005
#define GPIO_PD0_TIMCCP6        0x00030006
#define GPIO_PD0_I2S0RXSCK      0x00030008
#define GPIO_PD0_UART1CTS       0x00030009

//
// GPIO pin D1
//
#define GPIO_PD1_PWM1           0x00030401
#define GPIO_PD1_CAN0TX         0x00030402
#define GPIO_PD1_PHA0           0x00030403
#define GPIO_PD1_UART2TX        0x00030404
#define GPIO_PD1_UART1TX        0x00030405
#define GPIO_PD1_TIMCCP7        0x00030406
#define GPIO_PD1_I2S0RXWS       0x00030408
#define GPIO_PD1_UART1DCD       0x00030409
#define GPIO_PD1_TIMCCP2        0x0003040a
#define GPIO_PD1_PHB1           0x0003040b

//
// GPIO pin D2
//
#define GPIO_PD2_UART1RX        0x00030801
#define GPIO_PD2_TIMCCP6        0x00030802
#define GPIO_PD2_PWM2           0x00030803
#define GPIO_PD2_TIMCCP5        0x00030804
#define GPIO_PD2_EPI0S20        0x00030808

//
// GPIO pin D3
//
#define GPIO_PD3_UART1TX        0x00030c01
#define GPIO_PD3_TIMCCP7        0x00030c02
#define GPIO_PD3_PWM3           0x00030c03
#define GPIO_PD3_TIMCCP0        0x00030c04
#define GPIO_PD3_EPI0S21        0x00030c08

//
// GPIO pin D4
//
#define GPIO_PD4_TIMCCP0        0x00031001
#define GPIO_PD4_TIMCCP3        0x00031002
#define GPIO_PD4_I2S0RXSD       0x00031008
#define GPIO_PD4_UART1RI        0x00031009
#define GPIO_PD4_EPI0S19        0x0003100a

//
// GPIO pin D5
//
#define GPIO_PD5_TIMCCP2        0x00031401
#define GPIO_PD5_TIMCCP4        0x00031402
#define GPIO_PD5_I2S0RXMCLK     0x00031408
#define GPIO_PD5_UART2RX        0x00031409
#define GPIO_PD5_EPI0S28        0x0003140a

//
// GPIO pin D6
//
#define GPIO_PD6_FAULT0         0x00031801
#define GPIO_PD6_I2S0TXSCK      0x00031808
#define GPIO_PD6_UART2TX        0x00031809
#define GPIO_PD6_EPI0S29        0x0003180a

//
// GPIO pin D7
//
#define GPIO_PD7_IDX0           0x00031c01
#define GPIO_PD7_CMP0O          0x00031c02
#define GPIO_PD7_TIMCCP1        0x00031c03
#define GPIO_PD7_I2S0TXWS       0x00031c08
#define GPIO_PD7_UART1DTR       0x00031c09
#define GPIO_PD7_EPI0S30        0x00031c0a

//
// GPIO pin E0
//
#define GPIO_PE0_PWM4           0x00040001
#define GPIO_PE0_SPI1CLK        0x00040002
#define GPIO_PE0_TIMCCP3        0x00040003
#define GPIO_PE0_EPI0S8         0x00040008
#define GPIO_PE0_USB0PFLT       0x00040009

//
// GPIO pin E1
//
#define GPIO_PE1_PWM5           0x00040401
#define GPIO_PE1_SPI1CS         0x00040402
#define GPIO_PE1_FAULT0         0x00040403
#define GPIO_PE1_TIMCCP2        0x00040404
#define GPIO_PE1_TIMCCP6        0x00040405
#define GPIO_PE1_EPI0S9         0x00040408

//
// GPIO pin E2
//
#define GPIO_PE2_TIMCCP4        0x00040801
#define GPIO_PE2_SPI1RX         0x00040802
#define GPIO_PE2_PHB1           0x00040803
#define GPIO_PE2_PHA0           0x00040804
#define GPIO_PE2_TIMCCP2        0x00040805
#define GPIO_PE2_EPI0S24        0x00040808

//
// GPIO pin E3
//
#define GPIO_PE3_TIMCCP1        0x00040c01
#define GPIO_PE3_SPI1TX         0x00040c02
#define GPIO_PE3_PHA1           0x00040c03
#define GPIO_PE3_PHB0           0x00040c04
#define GPIO_PE3_TIMCCP7        0x00040c05
#define GPIO_PE3_EPI0S25        0x00040c08

//
// GPIO pin E4
//
#define GPIO_PE4_TIMCCP3        0x00041001
#define GPIO_PE4_FAULT0         0x00041004
#define GPIO_PE4_UART2TX        0x00041005
#define GPIO_PE4_TIMCCP2        0x00041006
#define GPIO_PE4_I2S0TXWS       0x00041009

//
// GPIO pin E5
//
#define GPIO_PE5_TIMCCP5        0x00041401
#define GPIO_PE5_I2S0TXSD       0x00041409

//
// GPIO pin E6
//
#define GPIO_PE6_PWM4           0x00041801
#define GPIO_PE6_CMP1O          0x00041802
#define GPIO_PE6_UART1CTS       0x00041809

//
// GPIO pin E7
//
#define GPIO_PE7_PWM5           0x00041c01
#define GPIO_PE7_CMP2O          0x00041c02
#define GPIO_PE7_UART1DCD       0x00041c09

//
// GPIO pin F0
//
#define GPIO_PF0_CAN1RX         0x00050001
#define GPIO_PF0_PHB0           0x00050002
#define GPIO_PF0_PWM0           0x00050003
#define GPIO_PF0_I2S0TXSD       0x00050008
#define GPIO_PF0_UART1DSR       0x00050009

//
// GPIO pin F1
//
#define GPIO_PF1_CAN1TX         0x00050401
#define GPIO_PF1_IDX1           0x00050402
#define GPIO_PF1_PWM1           0x00050403
#define GPIO_PF1_I2S0TXMCLK     0x00050408
#define GPIO_PF1_UART1RTS       0x00050409
#define GPIO_PF1_TIMCCP3        0x0005040a

//
// GPIO pin F2
//
#define GPIO_PF2_LED1           0x00050801
#define GPIO_PF2_PWM4           0x00050802
#define GPIO_PF2_PWM2           0x00050804
#define GPIO_PF2_SPI1CLK        0x00050809

//
// GPIO pin F3
//
#define GPIO_PF3_LED0           0x00050c01
#define GPIO_PF3_PWM5           0x00050c02
#define GPIO_PF3_PWM3           0x00050c04
#define GPIO_PF3_SPI1CS         0x00050c09

//
// GPIO pin F4
//
#define GPIO_PF4_TIMCCP0        0x00051001
#define GPIO_PF4_CMP0O          0x00051002
#define GPIO_PF4_FAULT0         0x00051004
#define GPIO_PF4_EPI0S12        0x00051008
#define GPIO_PF4_SPI1RX         0x00051009

//
// GPIO pin F5
//
#define GPIO_PF5_TIMCCP2        0x00051401
#define GPIO_PF5_CMP1O          0x00051402
#define GPIO_PF5_EPI0S15        0x00051408
#define GPIO_PF5_SPI1TX         0x00051409

//
// GPIO pin F6
//
#define GPIO_PF6_TIMCCP1        0x00051801
#define GPIO_PF6_CMP2O          0x00051802
#define GPIO_PF6_PHA0           0x00051804
#define GPIO_PF6_I2S0TXMCLK     0x00051809
#define GPIO_PF6_UART1RTS       0x0005180a

//
// GPIO pin F7
//
#define GPIO_PF7_TIMCCP4        0x00051c01
#define GPIO_PF7_PHB0           0x00051c04
#define GPIO_PF7_EPI0S12        0x00051c08
#define GPIO_PF7_FAULT1         0x00051c09

//
// GPIO pin G0
//
#define GPIO_PG0_UART2RX        0x00060001
#define GPIO_PG0_PWM0           0x00060002
#define GPIO_PG0_I2C1SCK        0x00060003
#define GPIO_PG0_PWM4           0x00060004
#define GPIO_PG0_USB0EPEN       0x00060007
#define GPIO_PG0_EPI0S13        0x00060008

//
// GPIO pin G1
//
#define GPIO_PG1_UART2TX        0x00060401
#define GPIO_PG1_PWM1           0x00060402
#define GPIO_PG1_I2C1SDA        0x00060403
#define GPIO_PG1_PWM5           0x00060404
#define GPIO_PG1_EPI0S14        0x00060408

//
// GPIO pin G2
//
#define GPIO_PG2_PWM0           0x00060801
#define GPIO_PG2_FAULT0         0x00060804
#define GPIO_PG2_IDX1           0x00060808
#define GPIO_PG2_I2S0RXSD       0x00060809

//
// GPIO pin G3
//
#define GPIO_PG3_PWM1           0x00060c01
#define GPIO_PG3_FAULT2         0x00060c04
#define GPIO_PG3_FAULT0         0x00060c08
#define GPIO_PG3_I2S0RXMCLK     0x00060c09

//
// GPIO pin G4
//
#define GPIO_PG4_TIMCCP3        0x00061001
#define GPIO_PG4_FAULT1         0x00061004
#define GPIO_PG4_EPI0S15        0x00061008
#define GPIO_PG4_PWM6           0x00061009
#define GPIO_PG4_UART1RI        0x0006100a

//
// GPIO pin G5
//
#define GPIO_PG5_TIMCCP5        0x00061401
#define GPIO_PG5_IDX0           0x00061404
#define GPIO_PG5_FAULT1         0x00061405
#define GPIO_PG5_PWM7           0x00061408
#define GPIO_PG5_I2S0RXSCK      0x00061409
#define GPIO_PG5_UART1DTR       0x0006140a

//
// GPIO pin G6
//
#define GPIO_PG6_PHA1           0x00061801
#define GPIO_PG6_PWM6           0x00061804
#define GPIO_PG6_FAULT1         0x00061808
#define GPIO_PG6_I2S0RXWS       0x00061809
#define GPIO_PG6_UART1RI        0x0006180a

//
// GPIO pin G7
//
#define GPIO_PG7_PHB1           0x00061c01
#define GPIO_PG7_PWM7           0x00061c04
#define GPIO_PG7_TIMCCP5        0x00061c08
#define GPIO_PG7_EPI0S31        0x00061c09

//
// GPIO pin H0
//
#define GPIO_PH0_TIMCCP6        0x00070001
#define GPIO_PH0_PWM2           0x00070002
#define GPIO_PH0_EPI0S6         0x00070008
#define GPIO_PH0_PWM4           0x00070009

//
// GPIO pin H1
//
#define GPIO_PH1_TIMCCP7        0x00070401
#define GPIO_PH1_PWM3           0x00070402
#define GPIO_PH1_EPI0S7         0x00070408
#define GPIO_PH1_PWM5           0x00070409

//
// GPIO pin H2
//
#define GPIO_PH2_IDX1           0x00070801
#define GPIO_PH2_CMP1O          0x00070802
#define GPIO_PH2_FAULT3         0x00070804
#define GPIO_PH2_EPI0S1         0x00070808

//
// GPIO pin H3
//
#define GPIO_PH3_PHB0           0x00070c01
#define GPIO_PH3_FAULT0         0x00070c02
#define GPIO_PH3_USB0EPEN       0x00070c04
#define GPIO_PH3_EPI0S0         0x00070c08

//
// GPIO pin H4
//
#define GPIO_PH4_USB0PFLT       0x00071004
#define GPIO_PH4_EPI0S10        0x00071008
#define GPIO_PH4_SPI1CLK        0x0007100b

//
// GPIO pin H5
//
#define GPIO_PH5_EPI0S11        0x00071408
#define GPIO_PH5_FAULT2         0x0007140a
#define GPIO_PH5_SPI1CS         0x0007140b

//
// GPIO pin H6
//
#define GPIO_PH6_EPI0S26        0x00071808
#define GPIO_PH6_PWM4           0x0007180a
#define GPIO_PH6_SPI1RX         0x0007180b

//
// GPIO pin H7
//
#define GPIO_PH7_EPI0S27        0x00071c08
#define GPIO_PH7_PWM5           0x00071c0a
#define GPIO_PH7_SPI1TX         0x00071c0b

//
// GPIO pin J0
//
#define GPIO_PJ0_EPI0S16        0x00080008
#define GPIO_PJ0_PWM0           0x0008000a
#define GPIO_PJ0_I2C1SCK        0x0008000b

//
// GPIO pin J1
//
#define GPIO_PJ1_EPI0S17        0x00080408
#define GPIO_PJ1_USB0PFLT       0x00080409
#define GPIO_PJ1_PWM1           0x0008040a
#define GPIO_PJ1_I2C1SDA        0x0008040b

//
// GPIO pin J2
//
#define GPIO_PJ2_EPI0S18        0x00080808
#define GPIO_PJ2_TIMCCP0        0x00080809
#define GPIO_PJ2_FAULT0         0x0008080a

//
// GPIO pin J3
//
#define GPIO_PJ3_EPI0S19        0x00080c08
#define GPIO_PJ3_UART1CTS       0x00080c09
#define GPIO_PJ3_TIMCCP6        0x00080c0a

//
// GPIO pin J4
//
#define GPIO_PJ4_EPI0S28        0x00081008
#define GPIO_PJ4_UART1DCD       0x00081009
#define GPIO_PJ4_TIMCCP4        0x0008100a

//
// GPIO pin J5
//
#define GPIO_PJ5_EPI0S29        0x00081408
#define GPIO_PJ5_UART1DSR       0x00081409
#define GPIO_PJ5_TIMCCP2        0x0008140a

//
// GPIO pin J6
//
#define GPIO_PJ6_EPI0S30        0x00081808
#define GPIO_PJ6_UART1RTS       0x00081809
#define GPIO_PJ6_TIMCCP1        0x0008180a

//
// GPIO pin J7
//
#define GPIO_PJ7_UART1DTR       0x00081c09
#define GPIO_PJ7_TIMCCP0        0x00081c0a

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_GPIO_Exported_APIs
//! @{
//
//*****************************************************************************

extern void GPIODirModeSet(unsigned long ulPort, unsigned char ucPins,
                           unsigned long ulPinIO);
extern unsigned long GPIODirModeGet(unsigned long ulPort, unsigned char ucPin);
extern void GPIOIntTypeSet(unsigned long ulPort, unsigned char ucPins,
                           unsigned long ulIntType);
extern unsigned long GPIOIntTypeGet(unsigned long ulPort, unsigned char ucPin);
extern void GPIOPadConfigSet(unsigned long ulPort, unsigned char ucPins,
                             unsigned long ulStrength,
                             unsigned long ulPadType);
extern void GPIOPadConfigGet(unsigned long ulPort, unsigned char ucPin,
                             unsigned long *pulStrength,
                             unsigned long *pulPadType);

extern void GPIOPinIntCallbackInit(unsigned long ulPort, 
                                   unsigned long ulPin,
                                   xtEventCallback xtPortCallback);

extern void GPIOPinIntEnable(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinIntDisable(unsigned long ulPort, unsigned char ucPins);
extern long GPIOPinIntStatus(unsigned long ulPort, xtBoolean bMasked);
extern void GPIOPinIntClear(unsigned long ulPort, unsigned char ucPins);
extern long GPIOPinRead(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinWrite(unsigned long ulPort, unsigned char ucPins,
                         unsigned char ucVal);
extern void GPIOPinConfigure(unsigned long ulPinConfig);
extern void GPIOPinTypeADC(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypeCAN(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypeACMPAnalog(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypeACMPDigital(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypeEPI(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypeEthernetLED(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypeGPIOInput(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypeGPIOOutput(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypeGPIOOutputOD(unsigned long ulPort,
                                    unsigned char ucPins);
extern void GPIOPinTypeI2C(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypeI2S(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypePWM(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypeQEI(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypeSPI(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypeTimer(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypeUART(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypeUSBAnalog(unsigned long ulPort, unsigned char ucPins);
extern void GPIOPinTypeUSBDigital(unsigned long ulPort, unsigned char ucPins);

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
//}
#endif

#endif //  __xGPIO_H__
