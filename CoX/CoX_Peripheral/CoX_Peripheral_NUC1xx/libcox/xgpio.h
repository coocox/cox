//*****************************************************************************
//
//! \file xgpio.h
//! \brief Prototypes for the GPIO Driver.
//! \brief Prototypes for the AFIO Driver.
//! \version V2.1.1.1
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
//! |xGPIO General Pin ID    |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xGPIO_INT_NUMBER        |    Mandatory   |   xGPIO_INT_NUMBER     |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! xGPIO intrerrupt nimber config
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
//! |xGPIO General Pin ID    |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_n             |    Mandatory   |       xGPIO_PIN_0      |
//! |                        |                |------------------------|
//! |                        |                |       xGPIO_PIN_1      |
//! |                        |                |------------------------|
//! |                        |                |       xGPIO_PIN_2      |
//! |                        |                |------------------------|
//! |                        |                |           ...          |
//! |                        |                |------------------------|
//! |                        |                |       xGPIO_PIN_8      |
//! |                        |                |------------------------|
//! |                        |                |           ...          |
//! |                        |                |------------------------|
//! |                        |                |      xGPIO_PIN_14      |
//! |                        |                |------------------------|
//! |                        |                |      xGPIO_PIN_15      |
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

//
//! GPIO pin 8
//
#define xGPIO_PIN_8             GPIO_PIN_8  

//
//! GPIO pin 9
//
#define xGPIO_PIN_9             GPIO_PIN_9  

//
//! GPIO pin 10
//
#define xGPIO_PIN_10            GPIO_PIN_10  

//
//! GPIO pin 11
//
#define xGPIO_PIN_11            GPIO_PIN_11  

//
//! GPIO pin 12
//
#define xGPIO_PIN_12            GPIO_PIN_12  

//
//! GPIO pin 13
//
#define xGPIO_PIN_13            GPIO_PIN_13  

//
//! GPIO pin 14
//
#define xGPIO_PIN_14            GPIO_PIN_14  

//
//! GPIO pin 15
//
#define xGPIO_PIN_15            GPIO_PIN_15  

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
//! |xGPIO Dir Mode          |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_IN       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_OUT      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_HW       |    Mandatory   |            Y           |
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
// Pin is a peripheral function
//
#define xGPIO_DIR_MODE_HW       GPIO_DIR_MODE_HW  

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
//! |xGPIO Int Type          |       CoX      |         NUC1xx         |
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
//! |xGPIO Pad Strength      |       CoX      |         NUC1xx         |
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
//! |xGPIO Pad Type          |       CoX      |         NUC1xx         |
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
#define GPA8                    GPIO_PORTA_BASE, GPIO_PIN_8
#define GPA9                    GPIO_PORTA_BASE, GPIO_PIN_9
#define GPA10                   GPIO_PORTA_BASE, GPIO_PIN_10
#define GPA11                   GPIO_PORTA_BASE, GPIO_PIN_11
#define GPA12                   GPIO_PORTA_BASE, GPIO_PIN_12
#define GPA13                   GPIO_PORTA_BASE, GPIO_PIN_13
#define GPA14                   GPIO_PORTA_BASE, GPIO_PIN_14
#define GPA15                   GPIO_PORTA_BASE, GPIO_PIN_15

#define GPB0                    GPIO_PORTB_BASE, GPIO_PIN_0
#define GPB1                    GPIO_PORTB_BASE, GPIO_PIN_1
#define GPB2                    GPIO_PORTB_BASE, GPIO_PIN_2
#define GPB3                    GPIO_PORTB_BASE, GPIO_PIN_3
#define GPB4                    GPIO_PORTB_BASE, GPIO_PIN_4
#define GPB5                    GPIO_PORTB_BASE, GPIO_PIN_5
#define GPB6                    GPIO_PORTB_BASE, GPIO_PIN_6
#define GPB7                    GPIO_PORTB_BASE, GPIO_PIN_7
#define GPB8                    GPIO_PORTB_BASE, GPIO_PIN_8
#define GPB9                    GPIO_PORTB_BASE, GPIO_PIN_9
#define GPB10                   GPIO_PORTB_BASE, GPIO_PIN_10
#define GPB11                   GPIO_PORTB_BASE, GPIO_PIN_11
#define GPB12                   GPIO_PORTB_BASE, GPIO_PIN_12
#define GPB13                   GPIO_PORTB_BASE, GPIO_PIN_13
#define GPB14                   GPIO_PORTB_BASE, GPIO_PIN_14
#define GPB15                   GPIO_PORTB_BASE, GPIO_PIN_15

#define GPC0                    GPIO_PORTC_BASE, GPIO_PIN_0
#define GPC1                    GPIO_PORTC_BASE, GPIO_PIN_1
#define GPC2                    GPIO_PORTC_BASE, GPIO_PIN_2
#define GPC3                    GPIO_PORTC_BASE, GPIO_PIN_3
#define GPC4                    GPIO_PORTC_BASE, GPIO_PIN_4
#define GPC5                    GPIO_PORTC_BASE, GPIO_PIN_5
#define GPC6                    GPIO_PORTC_BASE, GPIO_PIN_6
#define GPC7                    GPIO_PORTC_BASE, GPIO_PIN_7
#define GPC8                    GPIO_PORTC_BASE, GPIO_PIN_8
#define GPC9                    GPIO_PORTC_BASE, GPIO_PIN_9
#define GPC10                   GPIO_PORTC_BASE, GPIO_PIN_10
#define GPC11                   GPIO_PORTC_BASE, GPIO_PIN_11
#define GPC12                   GPIO_PORTC_BASE, GPIO_PIN_12
#define GPC13                   GPIO_PORTC_BASE, GPIO_PIN_13
#define GPC14                   GPIO_PORTC_BASE, GPIO_PIN_14
#define GPC15                   GPIO_PORTC_BASE, GPIO_PIN_15

#define GPD0                    GPIO_PORTD_BASE, GPIO_PIN_0
#define GPD1                    GPIO_PORTD_BASE, GPIO_PIN_1
#define GPD2                    GPIO_PORTD_BASE, GPIO_PIN_2
#define GPD3                    GPIO_PORTD_BASE, GPIO_PIN_3
#define GPD4                    GPIO_PORTD_BASE, GPIO_PIN_4
#define GPD5                    GPIO_PORTD_BASE, GPIO_PIN_5
#define GPD6                    GPIO_PORTD_BASE, GPIO_PIN_6
#define GPD7                    GPIO_PORTD_BASE, GPIO_PIN_7
#define GPD8                    GPIO_PORTD_BASE, GPIO_PIN_8
#define GPD9                    GPIO_PORTD_BASE, GPIO_PIN_9
#define GPD10                   GPIO_PORTD_BASE, GPIO_PIN_10
#define GPD11                   GPIO_PORTD_BASE, GPIO_PIN_11
#define GPD12                   GPIO_PORTD_BASE, GPIO_PIN_12
#define GPD13                   GPIO_PORTD_BASE, GPIO_PIN_13
#define GPD14                   GPIO_PORTD_BASE, GPIO_PIN_14
#define GPD15                   GPIO_PORTD_BASE, GPIO_PIN_15

#define GPE0                    GPIO_PORTE_BASE, GPIO_PIN_0
#define GPE1                    GPIO_PORTE_BASE, GPIO_PIN_1
#define GPE2                    GPIO_PORTE_BASE, GPIO_PIN_2
#define GPE3                    GPIO_PORTE_BASE, GPIO_PIN_3
#define GPE4                    GPIO_PORTE_BASE, GPIO_PIN_4
#define GPE5                    GPIO_PORTE_BASE, GPIO_PIN_5
#define GPE6                    GPIO_PORTE_BASE, GPIO_PIN_6
#define GPE7                    GPIO_PORTE_BASE, GPIO_PIN_7
#define GPE8                    GPIO_PORTE_BASE, GPIO_PIN_8
#define GPE9                    GPIO_PORTE_BASE, GPIO_PIN_9
#define GPE10                   GPIO_PORTE_BASE, GPIO_PIN_10
#define GPE11                   GPIO_PORTE_BASE, GPIO_PIN_11
#define GPE12                   GPIO_PORTE_BASE, GPIO_PIN_12
#define GPE13                   GPIO_PORTE_BASE, GPIO_PIN_13
#define GPE14                   GPIO_PORTE_BASE, GPIO_PIN_14
#define GPE15                   GPIO_PORTE_BASE, GPIO_PIN_15

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
//! |xGPIO Short Pin ID      |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |PXn                     |    Mandatory   |    PA0 PA1 ... PA15    |
//! |                        |                |------------------------|
//! |X is A, B, C ...        |                |    PB0 PB1 ... PB15    |
//! |                        |                |------------------------|
//! |                        |                |    PC0 PC1 ... PC15    |
//! |                        |                |------------------------|
//! |                        |                |    PD0 PD1 ... PD15    |
//! |                        |                |------------------------|
//! |                        |                |    PE0 PE1 ... PE15    |
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
#define PA8                     PA8
#define PA9                     PA9
#define PA10                    PA10
#define PA11                    PA11
#define PA12                    PA12
#define PA13                    PA13
#define PA14                    PA14
#define PA15                    PA15

#define PB0                     PB0
#define PB1                     PB1
#define PB2                     PB2
#define PB3                     PB3
#define PB4                     PB4
#define PB5                     PB5
#define PB6                     PB6
#define PB7                     PB7
#define PB8                     PB8
#define PB9                     PB9
#define PB10                    PB10
#define PB11                    PB11
#define PB12                    PB12
#define PB13                    PB13
#define PB14                    PB14
#define PB15                    PB15

#define PC0                     PC0
#define PC1                     PC1
#define PC2                     PC2
#define PC3                     PC3
#define PC4                     PC4
#define PC5                     PC5
#define PC6                     PC6
#define PC7                     PC7
#define PC8                     PC8
#define PC9                     PC9
#define PC10                    PC10
#define PC11                    PC11
#define PC12                    PC12
#define PC13                    PC13
#define PC14                    PC14
#define PC15                    PC15

#define PD0                     PD0
#define PD1                     PD1
#define PD2                     PD2
#define PD3                     PD3
#define PD4                     PD4
#define PD5                     PD5
#define PD6                     PD6
#define PD7                     PD7
#define PD8                     PD8
#define PD9                     PD9
#define PD10                    PD10
#define PD11                    PD11
#define PD12                    PD12
#define PD13                    PD13
#define PD14                    PD14
#define PD15                    PD15

#define PE0                     PE0
#define PE1                     PE1
#define PE2                     PE2
#define PE3                     PE3
#define PE4                     PE4
#define PE5                     PE5
#define PE6                     PE6
#define PE7                     PE7
#define PE8                     PE8
#define PE9                     PE9
#define PE10                    PE10
#define PE11                    PE11
#define PE12                    PE12
#define PE13                    PE13
#define PE14                    PE14
#define PE15                    PE15

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
//! |General Peripheral Pin  |       CoX      |         NUC1xx         |
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
#define SPI0MOSI                SPI0MOSI
#define SPI0MISO                SPI0MISO
#define SPI0CS                  SPI0CS
#define SPI1CLK                 SPI1CLK
#define SPI1MOSI                SPI1MOSI
#define SPI1MISO                SPI1MISO
#define SPI1CS                  SPI1CS
#define SPI2CLK                 SPI2CLK
#define SPI2MOSI                SPI2MOSI
#define SPI2MISO                SPI2MISO
#define SPI2CS                  SPI2CS
#define SPI3CLK                 SPI3CLK
#define SPI3MOSI                SPI3MOSI
#define SPI3MISO                SPI3MISO
#define SPI3CS                  SPI3CS

#define UART0RX                 UART0RX
#define UART0TX                 UART0TX
#define UART0CTS                UART0CTS
#define UART0DCD                UART0DCD
#define UART0DSR                UART0DSR
#define UART0DTR                UART0DTR
#define UART1RX                 UART1RX
#define UART1TX                 UART1TX
#define UART1CTS                UART1CTS
#define UART1DCD                UART1DCD
#define UART1DSR                UART1DSR
#define UART1DTR                UART1DTR
#define UART2RX                 UART2RX
#define UART2TX                 UART2TX
#define UART2CTS                UART2CTS
#define UART2DCD                UART2DCD
#define UART2DSR                UART2DSR
#define UART2DTR                UART2DTR

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
//! |xGPIO API                 |       CoX      |         NUC1xx         |
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
//! the following values:
//! 
//! Details please refer to \ref xGPIO_Dir_Mode_CoX.
//!
//! Where \b xGPIO_DIR_MODE_IN specifies that the pin will be programmed as
//! a software controlled input, \b xGPIO_DIR_MODE_OUT specifies that the pin
//! will be programmed as a software controlled output, and
//! \b xGPIO_DIR_MODE_HW specifies that the pin will be placed under
//! hardware control.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//! 
//! Details please refer to \ref xGPIO_General_Pin_IDs_CoX.
//!
//! \note xGPIOPadConfigSet() must also be used to configure the corresponding
//! pad(s) in order for them to propagate the signal to/from the GPIO.
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
//! the following values:
//!
//! Details please refer to \ref xGPIO_Dir_Mode_CoX.
//!
//! where \b xGPIO_DIR_MODE_IN specifies that the pin will be programmed as
//! a software controlled input, \b xGPIO_DIR_MODE_OUT specifies that the pin
//! will be programmed as a software controlled output, and
//! \b xGPIO_DIR_MODE_HW specifies that the pin will be placed under
//! hardware control.
//!
//! The pin is specified by eShortPin, which can only be one pin.
//! Details please refer to \ref xGPIO_Short_Pin_CoX.
//!
//! \note xGPIOPadConfigSet() must also be used to configure the corresponding
//! pad(s) in order for them to propagate the signal to/from the GPIO.
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
//! the following values:
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
//! Bits 31:16 should be ignored.
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
//! |       NUC1xx       |    ADC0                |    PA0                 |
//! |                    |    ADC1                |    PA1                 |
//! |                    |    ADC2                |    PA2                 |
//! |                    |    ADC3                |    PA3                 |
//! |                    |    ADC4                |    PA4                 |
//! |                    |    ADC5                |    PA5                 |
//! |                    |    ADC6                |    PA6                 |
//! |                    |    ADC7                |    PA7                 |
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
//! \brief Turn a pin to a GPIO CAN input or output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as CAN0RX. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as a CAN function and turns 
//! the pin into a GPIO CAN input or output pin.
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
//! |       NUC1xx       |    CAN0RX              |    PD6                 |
//! |                    |    CAN0TX              |    PD7                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************             
#define xSPinTypeCAN(ePeripheralPin, eShortPin)                               \
        do                                                                    \
        {                                                                     \
         GPIOSPinFunctionSet(GPIO_FUNCTION_CAN, eShortPin);                   \
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
//! |       NUC1xx       |    I2C0SCK             |    PA9                 |
//! |                    |    I2C0SDA             |    PA8                 |
//! |                    |    I2C1SCK             |    PA11                |
//! |                    |    I2C1SDA             |    PA10                |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//***************************************************************************** 
 #define xSPinTypeI2C(ePeripheralPin, eShortPin)                              \
        do                                                                    \
        {                                                                     \
         GPIOSPinFunctionSet(GPIO_FUNCTION_I2C, eShortPin);                   \
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
//! |       NUC1xx       |    I2S0RXMCLK          |    PA15                |
//! |                    |    I2S0RXSCK           |    PC1                 |
//! |                    |    I2S0RXSD            |    PC2                 |
//! |                    |    I2S0RXWS            |    PC0                 |
//! |                    |    I2S0TXMCLK          |    PA15                |
//! |                    |    I2S0TXSCK           |    PC1                 |
//! |                    |    I2S0TXSD            |    PC3                 |
//! |                    |    I2S0TXWS            |    PC0                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//***************************************************************************** 
#define xSPinTypeI2S(ePeripheralPin, eShortPin)                               \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOSPinFunctionSet(GPIO_FUNCTION_I2S, eShortPin);                   \
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
//! |       NUC1xx       |    PWM0                |    PA12                |
//! |                    |    PWM1                |    PA13                |
//! |                    |    PWM2                |    PA14                |
//! |                    |    PWM3                |    PA15                |
//! |                    |    PWM4                |    PB11                |
//! |                    |    PWM5                |    PE5                 |
//! |                    |    PWM6                |    PE0                 |
//! |                    |    PWM7                |    PE1                 |
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
//! |       NUC1xx       |    SPI0CLK             |    PC1                 |
//! |                    |    SPI0MOSI            |    PC5,PC3             |
//! |                    |    SPI0MISO            |    PC4,PC2             |
//! |                    |    SPI0CS              |    PC0,PB10            |
//! |                    |    SPI1CLK             |    PC9                 |
//! |                    |    SPI1MOSI            |    PC13,PC11           |
//! |                    |    SPI1MISO            |    PC12,PC10           |
//! |                    |    SPI1CS              |    PB9,PC8             |
//! |                    |    SPI2CLK             |    PD1                 |
//! |                    |    SPI2MOSI            |    PD3,PD5             |
//! |                    |    SPI2MISO            |    PD2,PD4             |
//! |                    |    SPI2CS              |    PA7,PD0             |
//! |                    |    SPI3CLK             |    PD9                 |
//! |                    |    SPI3MOSI            |    PD11,PD13           |
//! |                    |    SPI3MISO            |    PD10,PD12           |
//! |                    |    SPI3CS              |    PB14,PD8            |
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
//! |       NUC1xx       |    TIMCCP0             |    PB8                 |
//! |                    |    TIMCCP1             |    PB9                 |
//! |                    |    TIMCCP2             |    PB10                |
//! |                    |    TIMCCP3             |    PB11                |
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
//! |       NUC1xx       |    UART0RX             |    PB0                 |
//! |                    |    UART0TX             |    PB1                 |
//! |                    |    UART0RTS            |    PB2                 |
//! |                    |    UART0CTS            |    PB3                 |
//! |                    |    UART1CTS            |    PB7                 |
//! |                    |    UART1RTS            |    PB6                 |
//! |                    |    UART1RX             |    PB4                 |
//! |                    |    UART1TX             |    PB5                 |
//! |                    |    UART2RX             |    PD14                |
//! |                    |    UART2TX             |    PD15                |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeUART(ePeripheralPin, eShortPin)                              \
        do                                                                    \
        {                                                                     \
         GPIOSPinFunctionSet(GPIO_FUNCTION_UART, eShortPin);                  \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO ACMP input or output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as I2C0SDA. 
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
//! |       NUC1xx       |    CMP0P               |    PC6                 |
//! |                    |    CMP0N               |    PC7                 |
//! |                    |    CMP0O               |    PB12                |
//! |                    |    CMP1P               |    PC14                |
//! |                    |    CMP1N               |    PC15                |
//! |                    |    CMP1O               |    PB13                |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************            
#define xSPinTypeACMP(ePeripheralPin, eShortPin)                              \
        do                                                                    \
        {                                                                     \
         GPIOSPinFunctionSet(GPIO_FUNCTION_ACMP, eShortPin);                  \
        }                                                                     \
        while(0)

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
//! \return None.
//
//*****************************************************************************
#define xSPinTypeCLKO(ePeripheralPin, eShortPin)                              \
        do                                                                    \
        {                                                                     \
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
//! \return None.
//
//*****************************************************************************
#define xSPinTypeEXTINT(ePeripheralPin, eShortPin)                            \
        do                                                                    \
        {                                                                     \
         GPIOSPinFunctionSet(GPIO_FUNCTION_EXTINT, eShortPin);                \
        }                                                                     \
        while(0)
            
//*****************************************************************************
//
//! \brief Turn a pin to a GPIO EBI pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as I2C0SDA. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as an GPIO EBI function and  
//! turns the pin into a GPIO EBI pin.
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeEBI(ePeripheralPin, eShortPin)                               \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
         GPIOSPinFunctionSet(GPIO_FUNCTION_EBI, eShortPin);                   \
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
//! \addtogroup NUC1xx_GPIO
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_General_Pin_IDs NUC1xx GPIO General Pin ID
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

//
//! GPIO pin 8
//
#define GPIO_PIN_8              0x00000100  

//
//! GPIO pin 9
//
#define GPIO_PIN_9              0x00000200  

//
//! GPIO pin 10
//
#define GPIO_PIN_10             0x00000400  

//
//! GPIO pin 11
//
#define GPIO_PIN_11             0x00000800  

//
//! GPIO pin 12
//
#define GPIO_PIN_12             0x00001000  

//
//! GPIO pin 13
//
#define GPIO_PIN_13             0x00002000  

//
//! GPIO pin 14
//
#define GPIO_PIN_14             0x00004000  

//
//! GPIO pin 15
//
#define GPIO_PIN_15             0x00008000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_General_Pin_Bits NUC1xx GPIO General Pin Bits
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

//
//! GPIO BIT 8
//
#define GPIO_BIT_8              0x00000008  

//
//! GPIO BIT 9
//
#define GPIO_BIT_9              0x00000009  

//
//! GPIO BIT 10
//
#define GPIO_BIT_10             0x0000000A  

//
//! GPIO BIT 11
//
#define GPIO_BIT_11             0x0000000B  

//
//! GPIO BIT 12
//
#define GPIO_BIT_12             0x0000000C  

//
//! GPIO BIT 13
//
#define GPIO_BIT_13             0x0000000D  

//
//! GPIO BIT 14
//
#define GPIO_BIT_14             0x0000000E  

//
//! GPIO BIT 15
//
#define GPIO_BIT_15             0x0000000F  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Dir_Mode NUC1xx GPIO Dir Mode
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

//
//! Pin is in a peripheral function.
//
#define GPIO_DIR_MODE_HW        0x00000003 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Int_Type NUC1xx GPIO Int Type
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
//! \addtogroup NUC1xx_GPIO_DBCLK_Src NUC1xx GPIO De-bounce Clock Source
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
//! \addtogroup NUC1xx_GPIO_Function_Set NUC1xx GPIO Function Set
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
#define GPIO_FUNCTION_I2S       0x00000005   
#define GPIO_FUNCTION_PWM       0x00000006   
#define GPIO_FUNCTION_TIM       0x00000007   
#define GPIO_FUNCTION_UART      0x00000008   
#define GPIO_FUNCTION_CLKO      0x00000009   
#define GPIO_FUNCTION_CAN       0x0000000A  
#define GPIO_FUNCTION_EXTINT    0x0000000B  
#define GPIO_FUNCTION_EBI       0x0000000C  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Pin_Config NUC1xx GPIO Pin Config
//! \brief Values that can be passed to xGPIOPinConfigure as the ulPinConfig 
//! parameter.
//! @{
//
//*****************************************************************************

//
//! GPIO pin A0
//
#define GPIO_PA0_ADC0           0x00000000

//
//! GPIO pin A1
//
#define GPIO_PA1_ADC1           0x13000100
#define GPIO_PA1_AD12           0x13010101

//
//! GPIO pin A2
//
#define GPIO_PA2_ADC2           0x12000200
#define GPIO_PA2_AD11           0x12010201

//
//! GPIO pin A3
//
#define GPIO_PA3_ADC3           0x11000300
#define GPIO_PA3_AD10           0x11010301

//
//! GPIO pin A4
//
#define GPIO_PA4_ADC4           0x10000400
#define GPIO_PA4_AD9            0x10010401

//
//! GPIO pin A5
//
#define GPIO_PA5_ADC5           0x0F000500
#define GPIO_PA5_AD8            0x0F010501

//
//! GPIO pin A6
//
#define GPIO_PA6_ADC6           0x00000600
#define GPIO_PA6_AD7            0x00000601

//
//! GPIO pin A7
//
#define GPIO_PA7_ADC7           0x00000700
#define GPIO_PA7_SPI2CS         0x02010700
#define GPIO_PA7_AD6            0x02000701

//
//! GPIO pin A8
//
#define GPIO_PA8_I2C0SDA        0x00000800

//
//! GPIO pin A9
//
#define GPIO_PA9_I2C0SCK        0x00000900

//
//! GPIO pin A10
//
#define GPIO_PA10_I2C1SDA       0x00000A00
#define GPIO_PA10_EBINWR        0x00000A01

//
//! GPIO pin A11
//
#define GPIO_PA11_I2C1SCK       0x00000B00
#define GPIO_PA11_EBINRD        0x00000B01

//
//! GPIO pin A12
//
#define GPIO_PA12_PWM0          0x15000C00
#define GPIO_PA12_AD13          0x15010C01

//
//! GPIO pin A13
//
#define GPIO_PA13_PWM1          0x16000D00
#define GPIO_PA13_AD14          0x16010D01

//
//! GPIO pin A14
//
#define GPIO_PA14_PWM2          0x17000E00
#define GPIO_PA14_AD14          0x17010E01

//
//! GPIO pin A15
//
#define GPIO_PA15_PWM3          0x00000F00
#define GPIO_PA15_I2S0RXMCLK    0x09010F00
#define GPIO_PA15_I2S0TXMCLK    0x09010F00

//
//! GPIO pin B0
//
#define GPIO_PB0_UART0RX        0x00001000

//
//! GPIO pin B1
//
#define GPIO_PB1_UART0TX        0x00001100

//
//! GPIO pin B2
//
#define GPIO_PB2_UART0RTS       0x00001200
#define GPIO_PB2_NWRL           0x00001203 
#define GPIO_PB2_T2EX           0x00001210 

//
//! GPIO pin B3
//
#define GPIO_PB3_UART0CTS       0x00001300
#define GPIO_PB3_NWRH           0x00001305 
#define GPIO_PB3_T3EX           0x00001320 

//
//! GPIO pin B4
//
#define GPIO_PB4_UART1RX        0x00001400

//
//! GPIO pin B5
//
#define GPIO_PB5_UART1TX        0x00001500

//
//! GPIO pin B6
//
#define GPIO_PB6_UART1RTS       0x00001600
#define GPIO_PB6_EBIALE         0x00001601

//
//! GPIO pin B7
//
#define GPIO_PB7_UART1CTS       0x00001700
#define GPIO_PB7_EBINCS         0x00001701

//
//! GPIO pin B8
//
#define GPIO_PB8_TIMCCP0        0x00001800

//
//! GPIO pin B9
//
#define GPIO_PB9_TIMCCP1        0x01001900
#define GPIO_PB9_SPI1CS         0x01011900

//
//! GPIO pin B10
//
#define GPIO_PB10_TIMCCP2      0x00001A00
#define GPIO_PB10_SPI0CS        0x00011A00

//
//! GPIO pin B11
//
#define GPIO_PB11_TIMCCP3       0x04001B00
#define GPIO_PB11_PWM4          0x04011B00

//
//! GPIO pin B12
//
#define GPIO_PB12_CMP0O         0x0A001C00
#define GPIO_PB12_CLKO          0x0A011C00

//
//! GPIO pin B13
//
#define GPIO_PB13_CMP1O         0x00001D00
#define GPIO_PB13_AD1           0x00001D01

//
//! GPIO pin B14
//
#define GPIO_PB14_INT0          0x03001E00
#define GPIO_PB14_SPI3CS        0x03011E00

//
//! GPIO pin B15
//
#define GPIO_PB15_INT1          0x18001F00
#define GPIO_PB15_T0EX          0x18011F00

//
//! GPIO pin C0
//
#define GPIO_PC0_SPI0CS         0x05002000
#define GPIO_PC0_I2S0RXWS       0x05012000
#define GPIO_PC0_I2S0TXWS       0x05012000

//
//! GPIO pin C1
//
#define GPIO_PC1_SPI0CLK        0x06002100
#define GPIO_PC1_I2S0RXSCK      0x06012100
#define GPIO_PC1_I2S0TXSCK      0x06012100

//
//! GPIO pin C2
//
#define GPIO_PC2_SPI0MISO       0x07002200
#define GPIO_PC2_I2S0RXSD       0x07012200

//
//! GPIO pin C3
//
#define GPIO_PC3_SPI0MOSI       0x08002300
#define GPIO_PC3_I2S0TXSD       0x08012300

//
//! GPIO pin C4
//
#define GPIO_PC4_SPI0MISO       0x00002400

//
//! GPIO pin C5
//
#define GPIO_PC5_SPI0MOSI       0x00002500

//
//! GPIO pin C6
//
#define GPIO_PC6_CMP0P          0x00002600
#define GPIO_PC6_AD4            0x00002601

//
//! GPIO pin C7
//
#define GPIO_PC7_CMP0N          0x00002700
#define GPIO_PC7_AD5            0x00002701

//
//! GPIO pin C8
//
#define GPIO_PC8_SPI1CS         0x0B002800
#define GPIO_PC8_EBIMCLK        0x0B012801

//
//! GPIO pin C9
//
#define GPIO_PC9_SPI1CLK        0x00002900

//
//! GPIO pin C10
//
#define GPIO_PC10_SPI1MISO      0x00002A00

//
//! GPIO pin C11
//
#define GPIO_PC11_SPI1MOSI      0x00002B00

//
//! GPIO pin C12
//
#define GPIO_PC12_SPI1MISO      0x00002C00

//
//! GPIO pin C13
//
#define GPIO_PC13_SPI1MOSI      0x00002D00

//
//! GPIO pin C14
//
#define GPIO_PC14_CMP1P         0x00002E00
#define GPIO_PC14_AD2           0x00002E01

//
//! GPIO pin C15
//
#define GPIO_PC15_CMP1N         0x00002F00
#define GPIO_PC15_AD3           0x00002F01

//
//! GPIO pin D0
//
#define GPIO_PD0_SPI2CS         0x00003000

//
//! GPIO pin D1
//
#define GPIO_PD1_SPI2CLK        0x00003100

//
//! GPIO pin D2
//
#define GPIO_PD2_SPI2MISO       0x00003200

//
//! GPIO pin D3
//
#define GPIO_PD3_SPI2MOSI       0x00003300

//
//! GPIO pin D4
//
#define GPIO_PD4_SPI2MISO       0x00003400

//
//! GPIO pin D5
//
#define GPIO_PD5_SPI2MOSI       0x00003500

//
//! GPIO pin D6
//
#define GPIO_PD6_CAN0RX         0x00003600

//
//! GPIO pin D7
//
#define GPIO_PD7_CAN0TX         0x00003700

//
//! GPIO pin D8
//
#define GPIO_PD8_SPI3CS         0x00003800

//
//! GPIO pin D9
//
#define GPIO_PD9_SPI3CLK        0x00003900

//
//! GPIO pin D10
//
#define GPIO_PD10_SPI3MISO      0x00003A00

//
//! GPIO pin D11
//
#define GPIO_PD11_SPI3MOSI      0x00003B00

//
//! GPIO pin D12
//
#define GPIO_PD12_SPI3MISO      0x00003C00

//
//! GPIO pin D13
//
#define GPIO_PD13_SPI3MOSI      0x00003D00

//
//! GPIO pin D14
//
#define GPIO_PD14_UART2RX       0x00003E00

//
//! GPIO pin D15
//
#define GPIO_PD15_UART2TX       0x00003F00

//
//! GPIO pin E0
//
#define GPIO_PE0_PWM6           0x00004000

//
//! GPIO pin E1
//
#define GPIO_PE1_PWM7           0x00004100

//
//! GPIO pin E5
//
#define GPIO_PE5_PWM5           0x19004500
#define GPIO_PE5_T1EX           0x19014500

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NUC1xx_GPIO_Exported_APIs NUC1xx GPIO API
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


