//*****************************************************************************
//
//! \file xgpio.h
//! \brief Prototypes for the GPIO Driver.
//! \brief Prototypes for the AFIO Driver.
//! \version V2.2.1.0
//! \date 11/20/2011
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
//! \addtogroup xGPIO_General_Pin_IDs xGPIO General Pin ID
//! 
//! \section xGPIO_General_Pin_SIDs 1. Where to use this group
//! The following values define the bit field for the ulPins argument to several
//! of the APIs. So all the API which have a ulPins argument must use this group.
//! 
//! \section xGPIO_General_Pin_IDs_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO General Pin ID    |       CoX      |         STM32F1xx      |
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
//! |xGPIO Dir Mode          |       CoX      |         STM32F1xx      |
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
#define xGPIO_DIR_MODE_HW       0

//
// Pin is in Quasi-bidirectional mode
//
#define xGPIO_DIR_MODE_QB       0  

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
//! |xGPIO Int Type          |       CoX      |         STM32F1xx      |
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
#define xGPIO_BOTH_LEVEL        0

//
// Interrupt on low level
//
#define xGPIO_LOW_LEVEL         0  

//
// Interrupt on high level
//
#define xGPIO_HIGH_LEVEL        0 

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
//! |xGPIO Pad Strength      |       CoX      |         STM32F1xx      |
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
//! |xGPIO Pad Type          |       CoX      |         STM32F1xx      |
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
#define GPA0                    GPIOA_BASE, GPIO_PIN_0
#define GPA1                    GPIOA_BASE, GPIO_PIN_1
#define GPA2                    GPIOA_BASE, GPIO_PIN_2
#define GPA3                    GPIOA_BASE, GPIO_PIN_3
#define GPA4                    GPIOA_BASE, GPIO_PIN_4
#define GPA5                    GPIOA_BASE, GPIO_PIN_5
#define GPA6                    GPIOA_BASE, GPIO_PIN_6
#define GPA7                    GPIOA_BASE, GPIO_PIN_7
#define GPA8                    GPIOA_BASE, GPIO_PIN_8
#define GPA9                    GPIOA_BASE, GPIO_PIN_9
#define GPA10                   GPIOA_BASE, GPIO_PIN_10
#define GPA11                   GPIOA_BASE, GPIO_PIN_11
#define GPA12                   GPIOA_BASE, GPIO_PIN_12
#define GPA13                   GPIOA_BASE, GPIO_PIN_13
#define GPA14                   GPIOA_BASE, GPIO_PIN_14
#define GPA15                   GPIOA_BASE, GPIO_PIN_15

#define GPB0                    GPIOB_BASE, GPIO_PIN_0
#define GPB1                    GPIOB_BASE, GPIO_PIN_1
#define GPB2                    GPIOB_BASE, GPIO_PIN_2
#define GPB3                    GPIOB_BASE, GPIO_PIN_3
#define GPB4                    GPIOB_BASE, GPIO_PIN_4
#define GPB5                    GPIOB_BASE, GPIO_PIN_5
#define GPB6                    GPIOB_BASE, GPIO_PIN_6
#define GPB7                    GPIOB_BASE, GPIO_PIN_7
#define GPB8                    GPIOB_BASE, GPIO_PIN_8
#define GPB9                    GPIOB_BASE, GPIO_PIN_9
#define GPB10                   GPIOB_BASE, GPIO_PIN_10
#define GPB11                   GPIOB_BASE, GPIO_PIN_11
#define GPB12                   GPIOB_BASE, GPIO_PIN_12
#define GPB13                   GPIOB_BASE, GPIO_PIN_13
#define GPB14                   GPIOB_BASE, GPIO_PIN_14
#define GPB15                   GPIOB_BASE, GPIO_PIN_15

#define GPC0                    GPIOC_BASE, GPIO_PIN_0
#define GPC1                    GPIOC_BASE, GPIO_PIN_1
#define GPC2                    GPIOC_BASE, GPIO_PIN_2
#define GPC3                    GPIOC_BASE, GPIO_PIN_3
#define GPC4                    GPIOC_BASE, GPIO_PIN_4
#define GPC5                    GPIOC_BASE, GPIO_PIN_5
#define GPC6                    GPIOC_BASE, GPIO_PIN_6
#define GPC7                    GPIOC_BASE, GPIO_PIN_7
#define GPC8                    GPIOC_BASE, GPIO_PIN_8
#define GPC9                    GPIOC_BASE, GPIO_PIN_9
#define GPC10                   GPIOC_BASE, GPIO_PIN_10
#define GPC11                   GPIOC_BASE, GPIO_PIN_11
#define GPC12                   GPIOC_BASE, GPIO_PIN_12
#define GPC13                   GPIOC_BASE, GPIO_PIN_13
#define GPC14                   GPIOC_BASE, GPIO_PIN_14
#define GPC15                   GPIOC_BASE, GPIO_PIN_15

#define GPD0                    GPIOD_BASE, GPIO_PIN_0
#define GPD1                    GPIOD_BASE, GPIO_PIN_1
#define GPD2                    GPIOD_BASE, GPIO_PIN_2
#define GPD3                    GPIOD_BASE, GPIO_PIN_3
#define GPD4                    GPIOD_BASE, GPIO_PIN_4
#define GPD5                    GPIOD_BASE, GPIO_PIN_5
#define GPD6                    GPIOD_BASE, GPIO_PIN_6
#define GPD7                    GPIOD_BASE, GPIO_PIN_7
#define GPD8                    GPIOD_BASE, GPIO_PIN_8
#define GPD9                    GPIOD_BASE, GPIO_PIN_9
#define GPD10                   GPIOD_BASE, GPIO_PIN_10
#define GPD11                   GPIOD_BASE, GPIO_PIN_11
#define GPD12                   GPIOD_BASE, GPIO_PIN_12
#define GPD13                   GPIOD_BASE, GPIO_PIN_13
#define GPD14                   GPIOD_BASE, GPIO_PIN_14
#define GPD15                   GPIOD_BASE, GPIO_PIN_15

#define GPE0                    GPIOE_BASE, GPIO_PIN_0
#define GPE1                    GPIOE_BASE, GPIO_PIN_1
#define GPE2                    GPIOE_BASE, GPIO_PIN_2
#define GPE3                    GPIOE_BASE, GPIO_PIN_3
#define GPE4                    GPIOE_BASE, GPIO_PIN_4
#define GPE5                    GPIOE_BASE, GPIO_PIN_5
#define GPE6                    GPIOE_BASE, GPIO_PIN_6
#define GPE7                    GPIOE_BASE, GPIO_PIN_7
#define GPE8                    GPIOE_BASE, GPIO_PIN_8
#define GPE9                    GPIOE_BASE, GPIO_PIN_9
#define GPE10                   GPIOE_BASE, GPIO_PIN_10
#define GPE11                   GPIOE_BASE, GPIO_PIN_11
#define GPE12                   GPIOE_BASE, GPIO_PIN_12
#define GPE13                   GPIOE_BASE, GPIO_PIN_13
#define GPE14                   GPIOE_BASE, GPIO_PIN_14
#define GPE15                   GPIOE_BASE, GPIO_PIN_15

#define GPF0                    GPIOF_BASE, GPIO_PIN_0
#define GPF1                    GPIOF_BASE, GPIO_PIN_1
#define GPF2                    GPIOF_BASE, GPIO_PIN_2
#define GPF3                    GPIOF_BASE, GPIO_PIN_3
#define GPF4                    GPIOF_BASE, GPIO_PIN_4
#define GPF5                    GPIOF_BASE, GPIO_PIN_5
#define GPF6                    GPIOF_BASE, GPIO_PIN_6
#define GPF7                    GPIOF_BASE, GPIO_PIN_7
#define GPF8                    GPIOF_BASE, GPIO_PIN_8
#define GPF9                    GPIOF_BASE, GPIO_PIN_9
#define GPF10                   GPIOF_BASE, GPIO_PIN_10
#define GPF11                   GPIOF_BASE, GPIO_PIN_11
#define GPF12                   GPIOF_BASE, GPIO_PIN_12
#define GPF13                   GPIOF_BASE, GPIO_PIN_13
#define GPF14                   GPIOF_BASE, GPIO_PIN_14
#define GPF15                   GPIOF_BASE, GPIO_PIN_15

#define GPG0                    GPIOG_BASE, GPIO_PIN_0
#define GPG1                    GPIOG_BASE, GPIO_PIN_1
#define GPG2                    GPIOG_BASE, GPIO_PIN_2
#define GPG3                    GPIOG_BASE, GPIO_PIN_3
#define GPG4                    GPIOG_BASE, GPIO_PIN_4
#define GPG5                    GPIOG_BASE, GPIO_PIN_5
#define GPG6                    GPIOG_BASE, GPIO_PIN_6
#define GPG7                    GPIOG_BASE, GPIO_PIN_7
#define GPG8                    GPIOG_BASE, GPIO_PIN_8
#define GPG9                    GPIOG_BASE, GPIO_PIN_9
#define GPG10                   GPIOG_BASE, GPIO_PIN_10
#define GPG11                   GPIOG_BASE, GPIO_PIN_11
#define GPG12                   GPIOG_BASE, GPIO_PIN_12
#define GPG13                   GPIOG_BASE, GPIO_PIN_13
#define GPG14                   GPIOG_BASE, GPIO_PIN_14
#define GPG15                   GPIOG_BASE, GPIO_PIN_15

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
//! |xGPIO Short Pin ID      |       CoX      |         STM32F1xx      |
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
//! |                        |                |------------------------|
//! |                        |                |    PF0 PF1 ... PF15    |
//! |                        |                |------------------------|
//! |                        |                |    PG0 PG1 ... PG15    |  
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

#define PF0                     PF0
#define PF1                     PF1
#define PF2                     PF2
#define PF3                     PF3
#define PF4                     PF4
#define PF5                     PF5
#define PF6                     PF6
#define PF7                     PF7
#define PF8                     PF8
#define PF9                     PF9
#define PF10                    PF10
#define PF11                    PF11
#define PF12                    PF12
#define PF13                    PF13
#define PF14                    PF14
#define PF15                    PF15

#define PG0                     PG0
#define PG1                     PG1
#define PG2                     PG2
#define PG3                     PG3
#define PG4                     PG4
#define PG5                     PG5
#define PG6                     PG6
#define PG7                     PG7
#define PG8                     PG8
#define PG9                     PG9
#define PG10                    PG10
#define PG11                    PG11
#define PG12                    PG12
#define PG13                    PG13
#define PG14                    PG14
#define PG15                    PG15

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
//! |General Peripheral Pin  |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |ADCn                    |    Mandatory   |   ADC0 ADC1 ... ADC15  |
//! |------------------------|----------------|------------------------|
//! |CANnRX                  |    Mandatory   |      CAN0RX CAN1RX     |
//! |------------------------|----------------|------------------------|
//! |CANnTX                  |    Mandatory   |      CAN0TX CAN1TX     |
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

#define AIN                     0
#define FIN                     1
#define PIN                     2
#define APP                     3
#define AOD                     4


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
#define I2C1SMBA                I2C1SMBA
#define I2C2SCK                 I2C2SCK
#define I2C2SDA                 I2C2SDA
#define I2C2SMBA                I2C2SMBA  

#define I2S2RXSCK               I2S2RXSCK
#define I2S2RXMCLK              I2S2RXMCLK
#define I2S2RXSD(a)             I2S2RXSD(a)
#define I2S2RXWS(a)             I2S2RXWS(a)
#define I2S2TXSCK               I2S2TXSCK
#define I2S2TXMCLK              I2S2TXMCLK
#define I2S2TXSD(a)             I2S2TXSD(a)
#define I2S2TXWS(a)             I2S2TXWS(a)
#define I2S3RXSCK               I2S3RXSCK
#define I2S3RXMCLK              I2S3RXMCLK
#define I2S3RXSD(a)             I2S3RXSD(a)
#define I2S3RXWS(a)             I2S3RXWS(a)
#define I2S3TXSCK               I2S3TXSCK
#define I2S3TXMCLK              I2S3TXMCLK
#define I2S3TXSD(a)             I2S3TXSD(a)
#define I2S3TXWS(a)             I2S3TXWS(a)
 
#define SPI1CLK(a)              SPI1CLK(a)
#define SPI1MOSI(a)             SPI1MOSI(a)
#define SPI1MISO(a)             SPI1MISO(a)
#define SPI1CS(a)               SPI1CS(a)
#define SPI2CLK(a)              SPI2CLK(a)
#define SPI2MOSI(a)             SPI2MOSI(a)
#define SPI2MISO(a)             SPI2MISO(a)
#define SPI2CS(a)               SPI2CS(a)
#define SPI3CLK(a)              SPI3CLK(a)
#define SPI3MOSI(a)             SPI3MOSI(a)
#define SPI3MISO(a)             SPI3MISO(a)
#define SPI3CS(a)               SPI3CS(a)
 
#define UART1RX                 UART1RX
#define UART1TX                 UART1TX
#define UART1CK                 UART1CK
#define UART1CTS                UART1CTS
#define UART1RTS                UART1RTS
#define UART2RX                 UART2RX
#define UART2TX                 UART2TX
#define UART2CK                 UART2CK
#define UART2CTS                UART2CTS
#define UART2RTS                UART2RTS
#define UART3RX                 UART3RX
#define UART3TX                 UART3TX
#define UART3CK                 UART3CK
#define UART3CTS                UART3CTS
#define UART3RTS                UART3RTS
#define UART4RX                 UART4RX
#define UART4TX                 UART4TX
#define UART4CK                 UART4CK
#define UART4CTS                UART4CTS
#define UART4RTS                UART4RTS
#define UART5RX                 UART5RX
#define UART5TX                 UART5TX
#define UART5CK                 UART5CK
#define UART5CTS                UART5CTS
#define UART5RTS                UART5RTS

#define DACOUT1                 DACOUT1
#define DACOUT2                 DACOUT2

#define CMP0N                   CMP0N
#define CMP0P                   CMP0P
#define CMP0O                   CMP0O
#define CMP1N                   CMP1N
#define CMP1P                   CMP1P
#define CMP1O                   CMP1O

#define TIM1ETR                 TIM1ETR
#define TIM1CH1(a)              TIM1CH1(a)
#define TIM1CH1N                TIM1CH1N
#define TIM1CH2(a)              TIM1CH2(a)
#define TIM1CH2N                TIM1CH2N
#define TIM1CH3(a)              TIM1CH3(a)
#define TIM1CH3N                TIM1CH3N
#define TIM1CH4(a)              TIM1CH4(a)
#define TIM1CH4N                TIM1CH4N
#define TIM1BKIN                TIM1BKIN
#define TIM8ETR                 TIM8ETR
#define TIM8CH1(a)              TIM8CH1(a)
#define TIM8CH1N                TIM8CH1N
#define TIM8CH2(a)              TIM8CH2(a)
#define TIM8CH2N                TIM8CH2N
#define TIM8CH3(a)              TIM8CH3(a)
#define TIM8CH3N                TIM8CH3N
#define TIM8CH4(a)              TIM8CH4(a)
#define TIM8CH4N                TIM8CH4N
#define TIM8BKIN                TIM8BKIN

#define TIM2ETR                 TIM2ETR
#define TIM2CH1(a)              TIM2CH1(a)
#define TIM2CH2(a)              TIM2CH2(a)
#define TIM2CH3(a)              TIM2CH3(a)
#define TIM2CH4(a)              TIM2CH4(a)
#define TIM3ETR                 TIM3ETR
#define TIM3CH1(a)              TIM3CH1(a)
#define TIM3CH2(a)              TIM3CH2(a)
#define TIM3CH3(a)              TIM3CH3(a)
#define TIM3CH4(a)              TIM3CH4(a)
#define TIM4ETR                 TIM4ETR
#define TIM4CH1(a)              TIM4CH1(a)
#define TIM4CH2(a)              TIM4CH2(a)
#define TIM4CH3(a)              TIM4CH3(a)
#define TIM4CH4(a)              TIM4CH4(a)
#define TIM5ETR                 TIM5ETR
#define TIM5CH1(a)              TIM5CH1(a)
#define TIM5CH2(a)              TIM5CH2(a)
#define TIM5CH3(a)              TIM5CH3(a)
#define TIM5CH4(a)              TIM5CH4(a)

#define TIM9CH1(a)              TIM9CH1(a)
#define TIM9CH2(a)              TIM9CH2(a)
#define TIM10CH1(a)             TIM10CH1(a)
#define TIM10CH2(a)             TIM10CH2(a)
#define TIM11CH1(a)             TIM11CH1(a)
#define TIM11CH2(a)             TIM11CH2(a)
#define TIM12CH1(a)             TIM12CH1(a)
#define TIM12CH2(a)             TIM12CH2(a)
#define TIM13CH1(a)             TIM13CH1(a)
#define TIM13CH2(a)             TIM13CH2(a)
#define TIM14CH1(a)             TIM14CH1(a)
#define TIM14CH2(a)             TIM14CH2(a)

#define SDIO1D0                 SDIO1D0
#define SDIO1D1                 SDIO1D1
#define SDIO1D2                 SDIO1D2
#define SDIO1D3                 SDIO1D3
#define SDIO1D4                 SDIO1D4
#define SDIO1D5                 SDIO1D5
#define SDIO1D6                 SDIO1D6
#define SDIO1D7                 SDIO1D7
#define SDIO1CK                 SDIO1CK
#define SDIO1CMD                SDIO1CMD

#define FSMC1NE1                FSMC1NE1
#define FSMC1NE2                FSMC1NE2
#define FSMC1NE3                FSMC1NE3
#define FSMC1NE4                FSMC1NE4
#define FSMC1NADV               FSMC1NADV
#define FSMC1NBL1               FSMC1NBL1
#define FSMC1NBL2               FSMC1NBL2
#define FSMC1CLK                FSMC1CLK
#define FSMC1A0                 FSMC1A0
#define FSMC1A1                 FSMC1A1
#define FSMC1A2                 FSMC1A2
#define FSMC1A3                 FSMC1A3
#define FSMC1A4                 FSMC1A4
#define FSMC1A5                 FSMC1A5
#define FSMC1A6                 FSMC1A6
#define FSMC1A7                 FSMC1A7
#define FSMC1A8                 FSMC1A8
#define FSMC1A9                 FSMC1A9
#define FSMC1A10                FSMC1A10
#define FSMC1A11                FSMC1A11
#define FSMC1A12                FSMC1A12
#define FSMC1A13                FSMC1A13
#define FSMC1A14                FSMC1A14
#define FSMC1A15                FSMC1A15
#define FSMC1A16                FSMC1A16
#define FSMC1A17                FSMC1A17
#define FSMC1A18                FSMC1A18
#define FSMC1A19                FSMC1A19
#define FSMC1A20                FSMC1A20
#define FSMC1A21                FSMC1A21
#define FSMC1A22                FSMC1A22
#define FSMC1A23                FSMC1A23
#define FSMC1A24                FSMC1A24
#define FSMC1A25                FSMC1A25
#define FSMC1D0                 FSMC1D0
#define FSMC1D1                 FSMC1D1
#define FSMC1D2                 FSMC1D2
#define FSMC1D3                 FSMC1D3
#define FSMC1D4                 FSMC1D4
#define FSMC1D5                 FSMC1D5
#define FSMC1D6                 FSMC1D6
#define FSMC1D7                 FSMC1D7
#define FSMC1D8                 FSMC1D8
#define FSMC1D9                 FSMC1D9
#define FSMC1D10                FSMC1D10
#define FSMC1D11                FSMC1D11
#define FSMC1D12                FSMC1D12
#define FSMC1D13                FSMC1D13
#define FSMC1D14                FSMC1D14
#define FSMC1D15                FSMC1D15
#define FSMC1NOE                FSMC1NOE
#define FSMC1NWE                FSMC1NWE
#define FSMC1NWAIT              FSMC1NWAIT
#define FSMC1NCE3               FSMC1NCE3
#define FSMC1NCE2               FSMC1NCE2
#define FSMC1INT3               FSMC1INT3
#define FSMC1INT2               FSMC1INT2

#define FSMC1INTR               FSMC1INTR
#define FSMC1NCE4_1             FSMC1NCE4_1
#define FSMC1NCE4_2             FSMC1NCE4_2
#define FSMC1NIORD              FSMC1NIORD
#define FSMC1NIOWR              FSMC1NIOWR
#define FSMC1NIOS16             FSMC1NIOS16
#define FSMC1NREG               FSMC1NREG
#define FSMC1CD                 FSMC1CD


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
//! |xGPIO API                 |       CoX      |         STM32F1xx      |
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
#define xGPIOPinIntCallbackInit(ulPort, ulPin, pfnCallback)                   \
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
        GPIOPinIntStatus()  

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
//! \brief Reads the values present of the specified Port.
//!
//! \param ulPort is the base address of the GPIO port.
//!
//! The values at the specified Port are read
//!
//! \return Returns a bit-packed byte providing the state of the specified
//! Port
//
//*****************************************************************************
#define xGPIOPortRead(ulPort)                                                 \
        GPIOPortRead(ulPort)

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
//! \brief Writes a value to the specified Port.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucVal is the value to write to the Port.
//!
//! Writes the corresponding bit values to the output Port
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOPortWrite(ulPort, ulVal)                                         \
        GPIOPortWrite(ulPort, ulVal)

		
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
#define xGPIOPinConfigure(eShortPin, ulPinConfig)                             \
        GPIOSPinConfigure(eShortPin, ulPinConfig)

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
#define xGPIOSPinTypeGPIOInput(eShortPin)                                     \
        do                                                                    \
        {                                                                     \
         xGPIOSDirModeSet(eShortPin, GPIO_DIR_MODE_IN);                       \
        }                                                                     \
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
#define xGPIOSPinTypeGPIOOutput(eShortPin)                                    \
        do                                                                    \
        {                                                                     \
         xGPIOSDirModeSet(eShortPin, GPIO_DIR_MODE_OUT);                      \
        }                                                                     \
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
#define xGPIOSPinTypeGPIOOutputOD(eShortPin)                                  \
        do                                                                    \
        {                                                                     \
         xGPIOSDirModeSet(eShortPin, GPIO_DIR_MODE_OD);                       \
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
//! |      STM32F1xx     |    ADC0                |    PA0 (ADC123)        |
//! |                    |    ADC1                |    PA1 (ADC123)        |
//! |                    |    ADC2                |    PA2 (ADC123)        |
//! |                    |    ADC3                |    PA3 (ADC123)        |
//! |                    |    ADC4                | PA4(ADC12)  PF6(ADC3)  |
//! |                    |    ADC5                | PA5(ADC12)  PF7(ADC3)  |
//! |                    |    ADC6                | PA6(ADC12)  PF8(ADC3)  |
//! |                    |    ADC7                | PA7(ADC12)  PF9(ADC3)  |
//! |                    |    ADC8                | PB0(ADC12)  PF10(ADC3) |
//! |                    |    ADC9                |    PB1 (ADC12)         |
//! |                    |    ADC10               |    PC0 (ADC123)        |
//! |                    |    ADC11               |    PC1 (ADC123)        |
//! |                    |    ADC12               |    PC2 (ADC123)        |
//! |                    |    ADC13               |    PC3 (ADC123)        |
//! |                    |    ADC14               |    PC4 (ADC12)         |
//! |                    |    ADC15               |    PC5 (ADC12)         |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeADC(ePeripheralPin, eShortPin)                               \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)  

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
//! |      STM32F1xx     |    CAN0RX              |    PA11  PD0  PB8      |
//! |                    |    CAN0TX              |    PA12  PD1  PB9      |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************             
#define xSPinTypeCAN(ePeripheralPin, eShortPin)                               \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)

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
//! |      STM32F1xx     |    I2C1SCK             |    PB6   PB8           |
//! |                    |    I2C1SDA             |    PB7   PB9           |
//! |                    |    I2C1SMBA            |    PB5                 |
//! |                    |    I2C2SCK             |    PB10                |
//! |                    |    I2C2SDA             |    PB11                |
//! |                    |    I2C2SMBA            |    PB12                |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//***************************************************************************** 
 #define xSPinTypeI2C(ePeripheralPin, eShortPin)                              \
         GPIOSPinConfigure(ePeripheralPin, eShortPin)

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
//! |      STM32F1xx     |    I2S2RXMCLK          |    PC6                 |
//! |                    |    I2S2RXSCK           |    PB13                |
//! |                    |    I2S2RXSD            |    PB15                |
//! |                    |    I2S2RXWS            |    PB12                |
//! |                    |    I2S2TXMCLK          |    PC6                 |
//! |                    |    I2S2TXSCK           |    PB13                |
//! |                    |    I2S2TXSD            |    PB15                |
//! |                    |    I2S2TXWS            |    PB12                |
//! |                    |    I2S3RXMCLK          |    PC7                 |
//! |                    |    I2S3RXSCK           |    PB3                 |
//! |                    |    I2S3RXSD            |    PB5                 |
//! |                    |    I2S3RXWS            |    PA15                |
//! |                    |    I2S3TXMCLK          |    PC7                 |
//! |                    |    I2S3TXSCK           |    PB3                 |
//! |                    |    I2S3TXSD            |    PB5                 |
//! |                    |    I2S3TXWS            |    PA15                |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//***************************************************************************** 
#define xSPinTypeI2S(ePeripheralPin, eShortPin)                               \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)

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
//! |      STM32F1xx     |    SPI1CLK             |    PA5 PB3             |
//! |                    |    SPI1MOSI            |    PA7,PB5             |
//! |                    |    SPI1MISO            |    PA6,PB4             |
//! |                    |    SPI1CS              |    PA4,PA15            |
//! |                    |    SPI2CLK             |    PB13                |
//! |                    |    SPI2MOSI            |    PB15                |
//! |                    |    SPI2MISO            |    PB14                |
//! |                    |    SPI2CS              |    PB12                |
//! |                    |    SPI3CLK             |    PB3                 |
//! |                    |    SPI3MOSI            |    PB5                 |
//! |                    |    SPI3MISO            |    PB4                 |
//! |                    |    SPI3CS              |    PA15                |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeSPI(ePeripheralPin, eShortPin)                               \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)

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
//! |      STM32F1xx     |    TIM1ETR             |    PA12 PE7            |
//! |                    |    TIM1CH1             |    PA8  PE9            |
//! |                    |    TIM1CH1N            |    PA7  PB13   PE8     |
//! |                    |    TIM1CH2             |    PA9  PE11           |
//! |                    |    TIM1CH2N            |    PB14 PB0   PE10     |
//! |                    |    TIM1CH3             |    PA10 PE13           |
//! |                    |    TIM1CH3N            |    PB15 PB1   PE12     |
//! |                    |    TIM1CH4             |    PA11 PE14           |
//! |                    |    TIM1CH4N            |                        |
//! |                    |    TIM1BKIN            |    PB12 PA6   PE15     |
//! |                    |    TIM8ETR             |    PA0                 |
//! |                    |    TIM8CH1             |    PC6                 |
//! |                    |    TIM8CH1N            |    PA7                 |
//! |                    |    TIM8CH2             |    PC7                 |
//! |                    |    TIM8CH2N            |    PB0                 |
//! |                    |    TIM8CH3             |    PC8                 |
//! |                    |    TIM8CH3N            |    PB1                 |
//! |                    |    TIM8CH4             |    PC9                 |
//! |                    |    TIM8CH4N            |                        |
//! |                    |    TIM8BKIN            |    PA6                 |
//! |                    |    TIM2ETR             |    PA0  PA15           |
//! |                    |    TIM2CH1             |    PA0  PA15           |
//! |                    |    TIM2CH2             |    PA1  PB3            |
//! |                    |    TIM2CH3             |    PA2  PB10           |
//! |                    |    TIM2CH4             |    PA3  PB11           |
//! |                    |    TIM3ETR             |    PD2                 |
//! |                    |    TIM3CH1             |    PA6  PB4   PC6  PF8 |
//! |                    |    TIM3CH2             |    PA7  PB5   PC7      |
//! |                    |    TIM3CH3             |    PB0  PC8            |
//! |                    |    TIM3CH4             |    PB1  PC9            |
//! |                    |    TIM4ETR             |    PE0                 |
//! |                    |    TIM4CH1             |    PB6  PD12           |
//! |                    |    TIM4CH2             |    PB7  PD13           |
//! |                    |    TIM4CH3             |    PB8  PD14           |
//! |                    |    TIM4CH4             |    PB9  PD15           |
//! |                    |    TIM5ETR             |                        |
//! |                    |    TIM5CH1             |    PA0                 |
//! |                    |    TIM5CH2             |    PA1                 |
//! |                    |    TIM5CH3             |    PA2                 |
//! |                    |    TIM5CH4             |    PA3                 |
//! |                    |    TIM9CH1             |    PE5  PA2            |
//! |                    |    TIM9CH2             |    PE6  PA3            |
//! |                    |    TIM10CH1            |    PF6                 |
//! |                    |    TIM10CH2            |                        |
//! |                    |    TIM11CH1            |    PF7                 |
//! |                    |    TIM11CH2            |                        |
//! |                    |    TIM12CH1            |    PB14                |
//! |                    |    TIM12CH2            |    PB15                |
//! |                    |    TIM13CH1            |    PA6                 |
//! |                    |    TIM13CH2            |                        |
//! |                    |    TIM14CH1            |    PA7  PF9            |
//! |                    |    TIM14CH2            |                        |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************            
#define xSPinTypeTimer(ePeripheralPin, eShortPin)                             \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)

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
//! |      STM32F1xx     |    UART3RX             |    PB11  PD9  PC11     |
//! |                    |    UART3TX             |    PB10  PD8  PC10     |
//! |                    |    UART3CK             |    PB12  PD10 PC12     |
//! |                    |    UART3RTS            |    PB14  PD12          |
//! |                    |    UART3CTS            |    PB13  PD11          |
//! |                    |    UART1CTS            |    PA11                |
//! |                    |    UART1RTS            |    PA12                |
//! |                    |    UART1CK             |    PA8                 |
//! |                    |    UART1RX             |    PA10  PB7           |
//! |                    |    UART1TX             |    PA9   PB6           |
//! |                    |    UART2RX             |    PA3   PD6           |
//! |                    |    UART2TX             |    PA2   PD5           |
//! |                    |    UART2CTS            |    PA0   PD3           |
//! |                    |    UART2RTS            |    PA1   PD4           |
//! |                    |    UART2CK             |    PA4   PD7           |
//! |                    |    UART4RX             |    PC11                |
//! |                    |    UART4TX             |    PC10                |
//! |                    |    UART5RX             |    PD2                 |
//! |                    |    UART5TX             |    PC12                |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeUART(ePeripheralPin, eShortPin)                              \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO SDIO input or output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as I2C0SDA. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as an SDIO function and turns 
//!  the pin into a GPIO SDIO input or output pin.
//!
//! \verbatim
//! +--------------------+------------------------+------------------------+
//! |    manufacturer    |ePeripheralPin          |eShortPin               |
//! |--------------------|------------------------|------------------------|
//! |    CoX             |This parameter is a     |This parameter is a     |
//! |                    |mandatory.The mandatory |mandatory. the mandatory|
//! |                    |is the format of        |is the format of        |
//! |                    |Variable naming.So it   |Variable naming.So it   |
//! |                    |should be: SDIOnDx,     |should be: PXn          |
//! |                    |SDIOnCK or SDIOnCMD     |X  indicate the GPIO    |
//! |                    |n x indicate the pin    |PORT,Such as            |
//! |                    |number such as          |A B C D E ...           |
//! |                    |0 1 2 3 ....            |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |      STM32F1xx     |    SDIO1D0             |    PC8                 |
//! |                    |    SDIO1D1             |    PC9                 |
//! |                    |    SDIO1D2             |    PC10                |
//! |                    |    SDIO1D3             |    PC11                |
//! |                    |    SDIO1D4             |    PB8                 |
//! |                    |    SDIO1D5             |    PB9                 |
//! |                    |    SDIO1D6             |    PC6                 |
//! |                    |    SDIO1D7             |    PC7                 |
//! |                    |    SDIO1CK             |    PC12                |
//! |                    |    SDIO1CMD            |    PD2                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************            
#define xSPinTypeSDIO(ePeripheralPin, eShortPin)                              \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)

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
//! \verbatim
//! +--------------------+------------------------+------------------------+
//! |    manufacturer    |ePeripheralPin          |eShortPin               |
//! |--------------------|------------------------|------------------------|
//! |    CoX             |This parameter is a     |This parameter is a     |
//! |                    |mandatory.The mandatory |mandatory. the mandatory|
//! |                    |is the format of        |is the format of        |
//! |                    |Variable naming.So it   |Variable naming.So it   |
//! |                    |should be: MCO ,        |should be: PXn          |
//! |                    |                        |X  indicate the GPIO    |
//! |                    |                        |PORT,Such as            |
//! |                    |                        |A B C D E ...           |
//! |                    |                        |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |      STM32F1xx     |    MCO                 |    PA8                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeCLKO(ePeripheralPin, eShortPin)                              \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)
            
//*****************************************************************************
//
//! \brief Turn a pin to a GPIO DAC output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as I2C0SDA. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as an GPIO DAC function and  
//! turns the pin into a GPIO DAC output  pin.
//!
//! \verbatim
//! +--------------------+------------------------+------------------------+
//! |    manufacturer    |ePeripheralPin          |eShortPin               |
//! |--------------------|------------------------|------------------------|
//! |    CoX             |This parameter is a     |This parameter is a     |
//! |                    |mandatory.The mandatory |mandatory. the mandatory|
//! |                    |is the format of        |is the format of        |
//! |                    |Variable naming.So it   |Variable naming.So it   |
//! |                    |should be: DACOUTn,     |should be: PXn          |
//! |                    |                        |X  indicate the GPIO    |
//! |                    |n x indicate the pin    |PORT,Such as            |
//! |                    |number such as          |A B C D E ...           |
//! |                    |0 1 2 3 ....            |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |      STM32F1xx     |    DACOUT1             |    PA4                 |
//! |                    |    DACOUT2             |    PA5                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeDAC(ePeripheralPin, eShortPin)                               \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)

//*****************************************************************************
//
//! \brief Turn a pin to a GPIO FSMC input or output pin.
//!
//! \param ePeripheralPin is the GPIO Peripheral name such as I2C0SDA. 
//! Details please refer to \ref xGPIO_Pin_Config.
//! \param eShortPin is the GPIO short pin name such as PA0. 
//! Details please refer to \ref xGPIO_Short_Pin. 
//!
//! This function configures a pin for use as an FSMC function and turns 
//!  the pin into a GPIO FSMC input or output pin.
//!
//! \verbatim
//! +--------------------+------------------------+------------------------+
//! |    manufacturer    |ePeripheralPin          |eShortPin               |
//! |--------------------|------------------------|------------------------|
//! |    CoX             |This parameter is a     |This parameter is a     |
//! |                    |mandatory.The mandatory |mandatory. the mandatory|
//! |                    |is the format of        |is the format of        |
//! |                    |Variable naming.So it   |Variable naming.So it   |
//! |                    |should be: FSMC1An,     |should be: PXn          |
//! |                    |FSMC1Dn or ........     |X  indicate the GPIO    |
//! |                    |n x indicate the pin    |PORT,Such as            |
//! |                    |number such as          |A B C D E ...           |
//! |                    |0 1 2 3 ....            |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |      STM32F1xx     |    FSMC1NE1            |    PD7                 |
//! |                    |    FSMC1NE2            |    PG9                 |
//! |                    |    FSMC1NE3            |    PG10                |
//! |                    |    FSMC1NE4            |    PG12                |
//! |                    |    FSMC1NADV           |    PB7                 |
//! |                    |    FSMC1NBL0           |    PE0                 |
//! |                    |    FSMC1NBL1           |    PE1                 |
//! |                    |    FSMC1CLK            |    PD3                 |
//! |                    |    FSMC1A0             |    PF0                 |
//! |                    |    FSMC1A1             |    PF1                 |
//! |                    |    FSMC1A2             |    PF2                 |
//! |                    |    FSMC1A3             |    PF3                 |
//! |                    |    FSMC1A4             |    PF4                 |
//! |                    |    FSMC1A5             |    PF5                 |
//! |                    |    FSMC1A6             |    PF12                |
//! |                    |    FSMC1A7             |    PF13                |
//! |                    |    FSMC1A8             |    PF14                |
//! |                    |    FSMC1A9             |    PF15                |
//! |                    |    FSMC1A10            |    PG0                 |
//! |                    |    FSMC1A11            |    PG1                 |
//! |                    |    FSMC1A12            |    PG2                 |
//! |                    |    FSMC1A13            |    PG3                 |
//! |                    |    FSMC1A14            |    PG4                 |
//! |                    |    FSMC1A15            |    PG5                 |
//! |                    |    FSMC1A16            |    PD11                |
//! |                    |    FSMC1A17            |    PD12                |
//! |                    |    FSMC1A18            |    PD13                |
//! |                    |    FSMC1A19            |    PE3                 |
//! |                    |    FSMC1A20            |    PE4                 |
//! |                    |    FSMC1A21            |    PE5                 |
//! |                    |    FSMC1A22            |    PE6                 |
//! |                    |    FSMC1A23            |    PE2                 |
//! |                    |    FSMC1A24            |    PG13                |
//! |                    |    FSMC1A25            |    PG14                |
//! |                    |    FSMC1D0             |    PD14                |
//! |                    |    FSMC1D1             |    PD14                |
//! |                    |    FSMC1D2             |    PD0                 |
//! |                    |    FSMC1D3             |    PD1                 |
//! |                    |    FSMC1D4             |    PE7                 |
//! |                    |    FSMC1D5             |    PE8                 |
//! |                    |    FSMC1D6             |    PE9                 |
//! |                    |    FSMC1D7             |    PE10                |
//! |                    |    FSMC1D8             |    PE11                |
//! |                    |    FSMC1D9             |    PE12                |
//! |                    |    FSMC1D10            |    PE13                |
//! |                    |    FSMC1D11            |    PE14                |
//! |                    |    FSMC1D12            |    PE15                |
//! |                    |    FSMC1D13            |    PD8                 |
//! |                    |    FSMC1D14            |    PD9                 |
//! |                    |    FSMC1D15            |    PD10                |
//! |                    |    FSMC1NOE            |    PD4                 |
//! |                    |    FSMC1NWE            |    PD5                 |
//! |                    |    FSMC1NWAIT          |    PD6                 |
//! |                    |    FSMC1NCE3           |    PG9                 |
//! |                    |    FSMC1NCE2           |    PD7                 |
//! |                    |    FSMC1INT3           |    PG7                 |
//! |                    |    FSMC1INT2           |    PG6                 |
//! |                    |    FSMC1INTR           |    PF10                |
//! |                    |    FSMC1NCE4_1         |    PG10                |
//! |                    |    FSMC1NCE4_2         |    PG11                |
//! |                    |    FSMC1NIORD          |    PF6                 |
//! |                    |    FSMC1NIOWR          |    PF8                 |
//! |                    |    FSMC1NIOS16         |    PF11                |
//! |                    |    FSMC1NREG           |    PF7                 |
//! |                    |    FSMC1CD             |    PF9                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************            
#define xSPinTypeFSMC(ePeripheralPin, eShortPin)                              \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)



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
//! \addtogroup STM32F1xx_GPIO
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_General_Pin_IDs STM32F1xx GPIO General Pin ID
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
//! \addtogroup STM32F1xx_GPIO_General_Pin_Bits STM32F1xx GPIO General Pin Bits
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
//! \addtogroup STM32F1xx_GPIO_Dir_Mode STM32F1xx GPIO Dir Mode
//! \brief Values that can be passed to GPIODirModeSet as the ulPinIO parameter, 
//! and returned from GPIODirModeGet.
//! @{
//
//*****************************************************************************

//
//! Pin is a GPIO input
//
#define GPIO_DIR_MODE_IN        GPIO_TYPE_IN_WPU_WPD | GPIO_IN_SPEED_FIXED  

//
//! Pin is a GPIO output
//
#define GPIO_DIR_MODE_OUT       GPIO_OUT_SPEED_50M | GPIO_TYPE_OUT_STD

//
//! Pin is in Open-Drain mode.
//
#define GPIO_DIR_MODE_OD        GPIO_OUT_SPEED_50M | GPIO_TYPE_OUT_OD

//
//! Pin is in a peripheral function.
//
#define GPIO_DIR_MODE_HWSTD     GPIO_OUT_SPEED_50M | GPIO_TYPE_AFOUT_STD 
#define GPIO_DIR_MODE_HWOD      GPIO_OUT_SPEED_50M | GPIO_TYPE_AFOUT_OD

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Out_Speed STM32F1xx GPIO output speed
//! \brief Values that can be passed to GPIOPadConfigSet as the ulSpeed parameter, 
//! and returned from GPIOPadConfigGet.
//! @{
//
//*****************************************************************************

//
//! Input mode, max speed fixed MHz.
//
#define GPIO_IN_SPEED_FIXED     0x00000000

//
//! Output mode, max speed 10 MHz.
//
#define GPIO_OUT_SPEED_10M      0x00000001  

//
//! Output mode, max speed 2 MHz.
//
#define GPIO_OUT_SPEED_2M       0x00000002 

//
//! Output mode, max speed 50 MHz.
//
#define GPIO_OUT_SPEED_50M      0x00000003  

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

//
//! Input Analog mode.
//
#define GPIO_TYPE_IN_ANALOG     0x00000000

//
//! Floating input (reset state)
//
#define GPIO_TYPE_IN_FLOATING   0x00000004

//
//! Input with pull-up / pull-down
//
#define GPIO_TYPE_IN_WPU_WPD    0x00000008

//
//! General purpose output push-pull.
//
#define GPIO_TYPE_OUT_STD       0x00000000  

//
//! General purpose output Open-drain.
//
#define GPIO_TYPE_OUT_OD        0x00000004

//
//! Alternate function output Push-pull.
//
#define GPIO_TYPE_AFOUT_STD     0x00000008

//
//! Alternate function output Open-drain.
//
#define GPIO_TYPE_AFOUT_OD      0x0000000C

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Int_Type STM32F1xx GPIO Int Type
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


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Function_Set STM32F1xx GPIO Function Set
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
//! \addtogroup STM32F1xx_GPIO_Pin_Config STM32F1xx GPIO Pin Config
//! \brief Values that can be passed to xGPIOPinConfigure as the ulPinConfig 
//! parameter.
//! @{
//
//*****************************************************************************

//
//! GPIO pin A0
//
#define GPIO_PA0_WKUP           0x20000000
#define GPIO_PA0_UART2CTS       0x20000000
#define GPIO_PA0_ADC0           0x00000000
#define GPIO_PA0_TIM2CH1(a)     (0x00000000 | (a << 29))
#define GPIO_PA0_TIM2ETR        0x20000000
#define GPIO_PA0_TIM5CH1(a)     (0x00000000 | (a << 29))
#define GPIO_PA0_TIM8ETR        0x20000000

//
//! GPIO pin A1
//
#define GPIO_PA1_UART2RTS       0x60000000
#define GPIO_PA1_ADC1           0x00000000
#define GPIO_PA1_TIM5CH2(a)     (0x00000000 | (a << 29))
#define GPIO_PA1_TIM2CH2(a)     (0x00000000 | (a << 29))

//
//! GPIO pin A2
//
#define GPIO_PA2_UART2TX        0x60000000
#define GPIO_PA2_TIM5CH3(a)     (0x00000000 | (a << 29))
#define GPIO_PA2_ADC2           0x00000000
#define GPIO_PA2_TIM9CH1(a)     (0x00000000 | (a << 29))
#define GPIO_PA2_TIM2CH3(a)     (0x00000000 | (a << 29))

//
//! GPIO pin A3
//
#define GPIO_PA3_UART2RX        0x20000000
#define GPIO_PA3_TIM5CH4(a)     (0x00000000 | (a << 29))
#define GPIO_PA3_ADC3           0x00000000
#define GPIO_PA3_TIM2CH4(a)     (0x00000000 | (a << 29))
#define GPIO_PA3_TIM9CH2(a)     (0x00000000 | (a << 29))

//
//! GPIO pin A4
//
#define GPIO_PA4_SPI1CS(a)      (0x00000000 | (a << 29))
#define GPIO_PA4_UART2CK        0x60000000
#define GPIO_PA4_DACOUT1        0x00000000
#define GPIO_PA4_ADC4           0x00000000

//
//! GPIO pin A5
//
#define GPIO_PA5_SPI1CLK(a)     (0x00000000 | (a << 29))
#define GPIO_PA5_DACOUT2        0x00000000
#define GPIO_PA5_ADC5           0x00000000

//
//! GPIO pin A6
//
#define GPIO_PA6_SPI1MISO(a)    (0x00000000 | (a << 29))
#define GPIO_PA6_TIM8BKIN       0x20000000
#define GPIO_PA6_ADC6           0x00000000
#define GPIO_PA6_TIM3CH1(a)     (0x00000000 | (a << 29))
#define GPIO_PA6_TIM13CH1(a)    (0x00000000 | (a << 29))
#define GPIO_PA6_TIM1BKIN       0x20000040

//
//! GPIO pin A7
//
#define GPIO_PA7_SPI1MOSI(a)    (0x00000000 | (a << 29))
#define GPIO_PA7_TIM8CH1N       0x60000000
#define GPIO_PA7_ADC7           0x00000000
#define GPIO_PA7_TIM3CH2(a)     (0x00000000 | (a << 29))
#define GPIO_PA7_TIM14CH1(a)    (0x00000000 | (a << 29))
#define GPIO_PA7_TIM1CH1N       0x60000040

//
//! GPIO pin A8
//
#define GPIO_PA8_UART1CK        0x60000000
#define GPIO_PA8_TIM1CH1(a)     (0x00000040 | (a << 29))
#define GPIO_PA8_MCO            0x60000000

//
//! GPIO pin A9
//
#define GPIO_PA9_UART1TX        0x60000000
#define GPIO_PA9_TIM1CH2(a)     (0x00000040 | (a << 29))

//
//! GPIO pin A10
//
#define GPIO_PA10_UART1RX       0x20000000
#define GPIO_PA10_TIM1CH3(a)     (0x00000040 | (a << 29))

//
//! GPIO pin A11
//
#define GPIO_PA11_UART1CTS      0x20000000
#define GPIO_PA11_USBDM         0x00000000
#define GPIO_PA11_CAN0RX        0x20000000
#define GPIO_PA11_TIM1CH4(a)    (0x00000040 | (a << 29))

//
//! GPIO pin A12
//
#define GPIO_PA12_UART1RTS      0x60000000
#define GPIO_PA12_USBDP         0x00000000
#define GPIO_PA12_CAN0TX        0x60000000
#define GPIO_PA12_TIM1ETR       0x20000040

//
//! GPIO pin A13
//
#define GPIO_PA13_PA13(a)       (0x04000000 | (a << 29))

//
//! GPIO pin A14
//
#define GPIO_PA14_PA14(a)       (0x02000000 | (a << 29))

//
//! GPIO pin A15
//
#define GPIO_PA15_SPI3CS(a)     (0x00000000 | (a << 29))
#define GPIO_PA15_I2S3RXWS(a)   (0x00000000 | (a << 29))
#define GPIO_PA15_I2S3TXWS(a)   (0x00000000 | (a << 29))
#define GPIO_PA15_TIM2ETR       0x20000100
#define GPIO_PA15_TIM2CH1(a)    (0x00000100 | (a << 29))
#define GPIO_PA15_PA15(a)       (0x02000000 | (a << 29))
#define GPIO_PA15_SPI1CS(a)     (0x00000001 | (a << 29))

//
//! GPIO pin B0
//
#define GPIO_PB0_ADC8           0x00000000
#define GPIO_PB0_TIM3CH3(a)     (0x00000000 | (a << 29))
#define GPIO_PB0_TIM8CH2N       0x60000000
#define GPIO_PB0_TIM1CH2N       0x60000040

//
//! GPIO pin B1
//
#define GPIO_PB1_ADC9           0x00000000
#define GPIO_PB1_TIM3CH4(a)     (0x00000000 | (a << 29))
#define GPIO_PB1_TIM8CH3N       0x60000000
#define GPIO_PB1_TIM1CH3N       0x60000040

//
//! GPIO pin B2
//


//
//! GPIO pin B3
//
#define GPIO_PB3_SPI3CLK(a)     (0x00000000 | (a << 29))
#define GPIO_PB3_I2S3RXSCK      0x60000000 
#define GPIO_PB3_I2S3TXSCK      0x60000000
#define GPIO_PB3_PB3(a)         (0x01000000 | (a << 29))
#define GPIO_PB3_TRACESWO       0x00000000
#define GPIO_PB3_TIM2CH2(a)     (0x00000100 | (a << 29))
#define GPIO_PB3_SPI1CLK(a)     (0x00000001 | (a << 29))

//
//! GPIO pin B4
//
#define GPIO_PB4_SPI3MISO(a)    (0x00000000 | (a << 29))
#define GPIO_PB4_PB4(a)         (0x01000000 | (a << 29))
#define GPIO_PB4_TIM3CH1(a)     (0x00000800 | (a << 29))
#define GPIO_PB4_SPI1MISO(a)    (0x00000001 | (a << 29))

//
//! GPIO pin B5
//
#define GPIO_PB5_I2C1SMBA       0x80000000
#define GPIO_PB5_SPI3MOSI(a)    (0x00000000 | (a << 29))
#define GPIO_PB5_I2S3RXSD(a)    (0x00000000 | (a << 29))
#define GPIO_PB5_I2S3TXSD(a)    (0x00000000 | (a << 29))
#define GPIO_PB5_TIM3CH2(a)     (0x00000800 | (a << 29))
#define GPIO_PB5_SPI1MOSI(a)    (0x00000001 | (a << 29))

//
//! GPIO pin B6
//
#define GPIO_PB6_I2C1SCK        0x80000000
#define GPIO_PB6_TIM4CH1(a)     (0x00000000 | (a << 29))
#define GPIO_PB6_UART1TX        0x60000004

//
//! GPIO pin B7
//
#define GPIO_PB7_I2C1SDA        0x80000000
#define GPIO_PB7_FSMC1NADV      0x60000000
#define GPIO_PB7_TIM4CH2(a)     (0x00000000 | (a << 29))
#define GPIO_PB7_UART1RX        0x20000004

//
//! GPIO pin B8
//
#define GPIO_PB8_TIM4CH3(a)     (0x00000000 | (a << 29))
#define GPIO_PB8_SDIO1D4        0x60000000
#define GPIO_PB8_I2C1SCK        0x80000002
#define GPIO_PB8_CAN0RX         0x20004000

//
//! GPIO pin B9
//
#define GPIO_PB9_TIM4CH4(a)     (0x00000000 | (a << 29))
#define GPIO_PB9_SDIO1D5        0x60000000
#define GPIO_PB9_I2C1SDA        0x80000002
#define GPIO_PB9_CAN0TX         0x60004000

//
//! GPIO pin B10
//
#define GPIO_PB10_I2C2SCK       0x80000000
#define GPIO_PB10_UART3TX       0x60000000
#define GPIO_PB10_TIM2CH3(a)    (0x00000200 | (a << 29))

//
//! GPIO pin B11
//
#define GPIO_PB11_I2C2SDA       0x80000000
#define GPIO_PB11_UART3RX       0x20000000
#define GPIO_PB11_TIM2CH4(a)    (0x00000200 | (a << 29))

//
//! GPIO pin B12
//
#define GPIO_PB12_SPI2CS(a)     (0x00000000 | (a << 29))
#define GPIO_PB12_I2S2TXWS(a)   (0x00000000 | (a << 29))
#define GPIO_PB12_I2S2RXWS(a)   (0x00000000 | (a << 29))
#define GPIO_PB12_I2C2SMBA      0x80000000
#define GPIO_PB12_UART3CK       0x60000000
#define GPIO_PB12_TIM1BKIN      0x20000000

//
//! GPIO pin B13
//
#define GPIO_PB13_SPI2CLK(a)    (0x00000000 | (a << 29))
#define GPIO_PB13_I2S2RXSCK(a)  (0x00000000 | (a << 29))
#define GPIO_PB13_I2S2TXSCK(a)  (0x00000000 | (a << 29))
#define GPIO_PB13_UART3CTS      0x20000000
#define GPIO_PB13_TIM1CH1N      0x60000000

//
//! GPIO pin B14
//
#define GPIO_PB14_SPI2MISO(a)   (0x00000000 | (a << 29))
#define GPIO_PB14_TIM1CH2N      0x60000000
#define GPIO_PB14_UART3RTS      0x60000000
#define GPIO_PB14_TIM12CH1(a)   (0x00000000 | (a << 29))

//
//! GPIO pin B15
//
#define GPIO_PB15_SPI2MOSI(a)   (0x00000000 | (a << 29))
#define GPIO_PB15_I2S2RXSD(a)   (0x00000000 | (a << 29))
#define GPIO_PB15_I2S2TXSD(a)   (0x00000000 | (a << 29))
#define GPIO_PB15_TIM1CH3N      0x00000000
#define GPIO_PB15_TIM12CH2(a)   (0x00000000 | (a << 29))

//
//! GPIO pin C0
//
#define GPIO_PC0_ADC10          0x00000000

//
//! GPIO pin C1
//
#define GPIO_PC1_ADC11          0x00000000

//
//! GPIO pin C2
//
#define GPIO_PC2_ADC12          0x00000000

//
//! GPIO pin C3
//
#define GPIO_PC3_ADC13          0x00000000

//
//! GPIO pin C4
//
#define GPIO_PC4_ADC14          0x00000000

//
//! GPIO pin C5
//
#define GPIO_PC5_ADC15          0x00000000

//
//! GPIO pin C6
//
#define GPIO_PC6_I2S2RXMCLK     0x60000000
#define GPIO_PC6_I2S2TXMCLK     0x60000000
#define GPIO_PC6_TIM8CH1(a)     (0x00000000 | (a << 29))
#define GPIO_PC6_SDIO1D6        0x60000000
#define GPIO_PC6_TIM3CH1(a)     (0x00000C00 | (a << 29))

//
//! GPIO pin C7
//
#define GPIO_PC7_I2S3RXMCLK     0x60000000
#define GPIO_PC7_I2S3TXMCLK     0x60000000
#define GPIO_PC7_TIM8CH2(a)     (0x00000000 | (a << 29))
#define GPIO_PC7_SDIO1D7        0x60000000
#define GPIO_PC7_TIM3CH2(a)     (0x00000C00 | (a << 29))

//
//! GPIO pin C8
//
#define GPIO_PC8_TIM8CH3(a)     (0x00000000 | (a << 29))
#define GPIO_PC8_SDIO1D0        0x60000000
#define GPIO_PC8_TIM3CH3(a)     (0x00000C00 | (a << 29))

//
//! GPIO pin C9
//
#define GPIO_PC9_TIM8CH4(a)     (0x00000000 | (a << 29))
#define GPIO_PC9_SDIO1D1        0x60000000
#define GPIO_PC9_TIM3CH4(a)     (0x00000C00 | (a << 29))

//
//! GPIO pin C10
//
#define GPIO_PC10_UART4TX       0x60000000
#define GPIO_PC10_SDIO1D2       0x60000000
#define GPIO_PC10_UART3TX       0x60000010

//
//! GPIO pin C11
//
#define GPIO_PC11_UART4RX       0x20000000
#define GPIO_PC11_SDIO1D3       0x60000000
#define GPIO_PC11_UART3RX       0x20000010

//
//! GPIO pin C12
//
#define GPIO_PC12_UART5TX       0x60000000
#define GPIO_PC12_SDIO1CK       0x60000000
#define GPIO_PC12_UART3CK       0x60000010

//
//! GPIO pin C13
//
#define GPIO_PC13_TAMPER_RTC    0x00000000

//
//! GPIO pin C14
//
#define GPIO_PC14_OSC32_IN      0x20000000

//
//! GPIO pin C15
//
#define GPIO_PC15_OSC32_OUT     0x60000000

//
//! GPIO pin D0
//
#define GPIO_PD0_FSMC1D2        0x60000000
#define GPIO_PD0_OSC_IN         0x20008000
#define GPIO_PD0_CAN0RX         0x20006000

//
//! GPIO pin D1
//
#define GPIO_PD1_FSMC1D3        0x60000000
#define GPIO_PD1_OSC_OUT        0x60008000
#define GPIO_PD1_CAN0TX         0x60006000

//
//! GPIO pin D2
//
#define GPIO_PD2_TIM3ETR        0x20000000
#define GPIO_PD2_UART5RX        0x20000000
#define GPIO_PD2_SDIO1CMD       0x60000000

//
//! GPIO pin D3
//
#define GPIO_PD3_FSMC1CLK       0x60000000
#define GPIO_PD3_UART2CTS       0x20000008

//
//! GPIO pin D4
//
#define GPIO_PD4_FSMC1NOE       0x60000000
#define GPIO_PD4_UART2RTS       0x60000008

//
//! GPIO pin D5
//
#define GPIO_PD5_FSMC1NWE       0x60000000
#define GPIO_PD5_UART2TX        0x60000008

//
//! GPIO pin D6
//
#define GPIO_PD6_FSMC1NWAIT     0x20000000
#define GPIO_PD6_UART2RX        0x20000008

//
//! GPIO pin D7
//
#define GPIO_PD7_FSMC1NE1       0x60000000
#define GPIO_PD7_FSMC1NCE2      0x60000000
#define GPIO_PD7_UART2CK        0x60000008

//
//! GPIO pin D8
//
#define GPIO_PD8_FSMC1D13       0x60000000
#define GPIO_PD8_UART3TX        0x60000030

//
//! GPIO pin D9
//
#define GPIO_PD9_FSMC1D14       0x60000000
#define GPIO_PD9_UART3RX        0x20000030

//
//! GPIO pin D10
//
#define GPIO_PD10_FSMC1D15      0x60000000
#define GPIO_PD10_UART3CK       0x60000030

//
//! GPIO pin D11
//
#define GPIO_PD11_FSMC1A16      0x60000000
#define GPIO_PD11_UART3CTS      0x20000030

//
//! GPIO pin D12
//
#define GPIO_PD12_FSMC1A17      0x60000000
#define GPIO_PD12_TIM4CH1(a)    (0x00001000 | (a << 29))
#define GPIO_PD12_UART3RTS      0x60000030

//
//! GPIO pin D13
//
#define GPIO_PD13_FSMC1A18      0x60000000
#define GPIO_PD13_TIM4CH2(a)    (0x00001000 | (a << 29))

//
//! GPIO pin D14
//
#define GPIO_PD14_FSMC1D0       0x60000000
#define GPIO_PD14_TIM4CH3(a)    (0x00001000 | (a << 29))

//
//! GPIO pin D15
//
#define GPIO_PD15_FSMC1D1       0x60000000
#define GPIO_PD15_TIM4CH4(a)    (0x00001000 | (a << 29))

//
//! GPIO pin E0
//
#define GPIO_PE0_TIM4ETR        0x20000000
#define GPIO_PE0_FSMC1NBL0      0x60000000

//
//! GPIO pin E1
//
#define GPIO_PE1_FSMC1NBL1      0x60000000

//
//! GPIO pin E2
//
#define GPIO_PE2_TRACECK        0x00000000
#define GPIO_PE2_FSMC1A23       0x60000000

//
//! GPIO pin E3
//
#define GPIO_PE3_TRACED0        0x00000000
#define GPIO_PE3_FSMC1A19       0x60000000

//
//! GPIO pin E4
//
#define GPIO_PE4_TRACED1        0x00000000
#define GPIO_PE4_FSMC1A20       0x60000000

//
//! GPIO pin E5
//
#define GPIO_PE5_TRACED2        0x00000000
#define GPIO_PE5_FSMC121        0x60000000
#define GPIO_PE5_TIM9CH1(a)     (0x10000020 | (a << 29))

//
//! GPIO pin E6
//
#define GPIO_PE6_TRACED3        0x00000000
#define GPIO_PE6_FSMC122        0x60000000
#define GPIO_PE6_TIM9CH2        0x10000020

//
//! GPIO pin E7
//
#define GPIO_PE7_FSMC1D4        0x60000000
#define GPIO_PE7_TIM1ETR        0x200000C0

//
//! GPIO pin E8
//
#define GPIO_PE8_FSMC1D5        0x60000000
#define GPIO_PE8_TIM1CH1N       0x600000C0

//
//! GPIO pin E9
//
#define GPIO_PE9_FSMC1D6        0x60000000
#define GPIO_PE9_TIM1CH1(a)     (0x000000C0 | (a << 29))

//
//! GPIO pin E10
//
#define GPIO_PE10_FSMC1D7       0x60000000
#define GPIO_PE10_TIM1CH2N      0x600000C0

//
//! GPIO pin E11
//
#define GPIO_PE11_FSMC1D8       0x60000000
#define GPIO_PE11_TIM1CH2(a)    (0x000000C0 | (a << 29))

//
//! GPIO pin E12
//
#define GPIO_PE12_FSMC1D9       0x60000000
#define GPIO_PE12_TIM1CH3N      0x600000C0

//
//! GPIO pin E13
//
#define GPIO_PE13_FSMC1D10      0x60000000
#define GPIO_PE13_TIM1CH3(a)    (0x000000C0 | (a << 29))

//
//! GPIO pin E14
//
#define GPIO_PE14_FSMC1D11      0x60000000
#define GPIO_PE14_TIM1CH4(a)    (0x000000C0 | (a << 29))

//
//! GPIO pin E15
//
#define GPIO_PE15_FSMC1D12      0x60000000
#define GPIO_PE15_TIM1BKIN      0x200000C0


//
//! GPIO pin F0
//
#define GPIO_PF0_FSMC1A0        0x60000000

//
//! GPIO pin F1
//
#define GPIO_PF1_FSMC1A1        0x60000000

//
//! GPIO pin F2
//
#define GPIO_PF2_FSMC1A2        0x60000000

//
//! GPIO pin F3
//
#define GPIO_PF3_FSMC1A3        0x60000000

//
//! GPIO pin F4
//
#define GPIO_PF4_FSMC1A4        0x60000000

//
//! GPIO pin F5
//
#define GPIO_PF5_FSMC1A5        0x60000000

//
//! GPIO pin F6
//
#define GPIO_PF6_ADC4           0x00000000
#define GPIO_PF6_FSMC1NIORD     0x60000000
#define GPIO_PF6_TIM10CH1(a)    (0x10000040 | (a << 29))

//
//! GPIO pin F7
//
#define GPIO_PF7_ADC5           0x00000000
#define GPIO_PF7_FSMC1NREG      0x60000000
#define GPIO_PF7_TIM11CH1(a)    (0x10000080 | (a << 29))

//
//! GPIO pin F8
//
#define GPIO_PF8_ADC6           0x00000000
#define GPIO_PF8_FSMC1NIOWR     0x60000000
#define GPIO_PF8_TIM3CH1(a)     (0x10000100 | (a << 29))

//
//! GPIO pin F9
//
#define GPIO_PF9_ADC7           0x00000000
#define GPIO_PF9_FSMC1CD        0x20000000
#define GPIO_PF9_TIM14CH1(a)    (0x10000200 | (a << 29))

//
//! GPIO pin F10
//
#define GPIO_PF10_ADC8          0x00000000
#define GPIO_PF10_FSMC1INTR     0x20000000

//
//! GPIO pin F11
//
#define GPIO_PF11_FSMC1NIOS16   0x20000000

//
//! GPIO pin F12
//
#define GPIO_PF12_FSMC1A6       0x60000000

//
//! GPIO pin F13
//
#define GPIO_PF13_FSMC1A7       0x60000000

//
//! GPIO pin F14
//
#define GPIO_PF14_FSMC1A8       0x60000000

//
//! GPIO pin F15
//
#define GPIO_PF15_FSMC1A9       0x60000000


//
//! GPIO pin G0
//
#define GPIO_PG0_FSMC1A10       0x60000000

//
//! GPIO pin G1
//
#define GPIO_PG1_FSMC1A11       0x60000000

//
//! GPIO pin G2
//
#define GPIO_PG2_FSMC1A12       0x60000000

//
//! GPIO pin G3
//
#define GPIO_PG3_FSMC1A13       0x60000000

//
//! GPIO pin G4
//
#define GPIO_PG4_FSMC1A14       0x60000000

//
//! GPIO pin G5
//
#define GPIO_PG5_FSMC1A15       0x60000000

//
//! GPIO pin G6
//
#define GPIO_PG6_FSMC1INT2      0x20000000

//
//! GPIO pin G7
//
#define GPIO_PG7_FSMC1INT3      0x20000000

//
//! GPIO pin G8
//

//
//! GPIO pin G9
//
#define GPIO_PG9_FSMC1NE2       0x60000000
#define GPIO_PG9_FSMC1NCE3      0x60000000

//
//! GPIO pin G10
//
#define GPIO_PG10_FSMC1NCE4_1   0x60000000
#define GPIO_PG10_FSMC1NE3      0x60000000

//
//! GPIO pin G11
//
#define GPIO_PG11_FSMC1NCE4_2   0x60000000

//
//! GPIO pin G12
//
#define GPIO_PG12_FSMC1NE4      0x60000000

//
//! GPIO pin G13
//
#define GPIO_PG13_FSMC1A24      0x60000000

//
//! GPIO pin G14
//
#define GPIO_PG14_FSMC1A25      0x60000000

//
//! GPIO pin G15
//

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup STM32F1xx_GPIO_Exported_APIs STM32F1xx GPIO API
//! \brief GPIO API Reference.
//! @{
//
//*****************************************************************************

#define GPIOSPinFunctionSet(ulFunction, eShortPin)                            \
        GPIOPinFunctionSet(ulFunction, G##eShortPin)

#define GPIOSPinIntEnable(eShortPin, ulIntType)                               \
        GPIOPinIntEnable(G##eShortPin, ulIntType)

#define xGPIOSDirModeSet(eShortPin, ulPinIO)                                  \
        xGPIODirModeSet1(eShortPin, ulPinIO)

#define xGPIODirModeSet1(eShortPin, ulPinIO)                                  \
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
        GPIOPinConfigure(G##eShortPin, GPIO_##eShortPin##_##ePeripheralPin)

extern void GPIODirModeSet(unsigned long ulPort, unsigned long ulBit,
                           unsigned long ulPinType, unsigned long ulPinSpeed);
extern unsigned long GPIODirModeGet(unsigned long ulPort, unsigned long ulBit);
extern void GPIOPinIntEnable(unsigned long ulPort, unsigned long ulPins,
                             unsigned long ulIntType);
extern void GPIOPinIntDisable(unsigned long ulPort, unsigned long ulPins);
extern void GPIOPinIntCallbackInit(unsigned long ulPort, unsigned long ulPin, 
                                   xtEventCallback xtPortCallback);
extern unsigned long GPIOPinIntStatus(void);
extern void GPIOPinIntClear(unsigned long ulPort, unsigned long ulPins);
extern long GPIOPinRead(unsigned long ulPort, unsigned long ulPins);
extern void GPIOPinWrite(unsigned long ulPort, unsigned long ulPins,
		                 unsigned char ucVal);
extern void GPIOPinSet(unsigned long ulPort, unsigned long ulPins);	
extern void GPIOPinReset(unsigned long ulPort, unsigned long ulPins);
extern void GPIOPinLockConfig(unsigned long ulPort, unsigned long ulPins);

extern void GPIOPinMaskSet(unsigned long ulPort, unsigned long ulPins);
extern long GPIOPortMaskGet(unsigned long ulPort);
extern long GPIOPinPortDoutGet(unsigned long ulPort);
extern void GPIOPinFunctionSet(unsigned long ulFunction, unsigned long ulPort, 
                               unsigned long ulPins);
extern void GPIOPinConfigure(unsigned long ulPort, unsigned long ulPins, 
                             unsigned long ulPinConfig);
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

