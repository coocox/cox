//*****************************************************************************
//
//! \file xgpio.h
//! \brief Prototypes for the GPIO Driver.
//! \brief Prototypes for the AFIO Driver.
//! \version V2.1.1.0
//! \date 2/25/2012
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
//! |xGPIO General Pin ID    |       CoX      |       HT32F125x        |
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
//! |xGPIO General Pin ID    |       CoX      |        HT32F125x       |
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
//! |xGPIO Dir Mode          |       CoX      |        HT32F125x       |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_IN       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_OUT      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_HW       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_QB       |  Non-Mandatory |            N           |
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
//! |xGPIO Int Type          |       CoX      |         HT32F125x      |
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
//! |xGPIO Pad Strength      |       CoX      |         HT32F125x      |
//! |------------------------|----------------|------------------------|
//! |xGPIO_STRENGTH_nMA      | Non-Mandatory  |   xGPIO_STRENGTH_4MA   |
//! |                        |                |------------------------|
//! |                        |                |   xGPIO_STRENGTH_8MA   |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************
  
//
//! Output Current Drive (4mA source/sink current)
//
#define xGPIO_STRENGTH_4MA      GPIO_STRENGTH_4MA
  
//
//! Output Current Drive (8mA source/sink current)
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
//! <br />
//! \section xGPIO_Pad_Config_Type_S1 1. Where to use this group
//! Values that can be passed to xGPIOPadConfigSet as the ulPadType parameter,
//! and returned by xGPIOPadConfigGet in the *pulPadType parameter.
//! <br />
//! \section xGPIO_Pad_Config_Type_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO Pad Type          |       CoX      |         HT32F125x      |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_STD      |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_STD_WPU  |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_OD       |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_OD_WPU   |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_OD_WPD   |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_ANALOG   |  Non-Mandatory |            N           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_TYPE_STD_WPD  |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Push-pull with weak pull-up
//
#define XGPIO_PIN_TYPE_STD_WPU  GPIO_PIN_TYPE_STD_WPU  

//
//! Push-pull with weak pull-down
//
#define XGPIO_PIN_TYPE_STD_WPD  GPIO_PIN_TYPE_STD_WPD 

//
//! Open-drain
//
#define XGPIO_PIN_TYPE_OD       GPIO_PIN_TYPE_OD
  

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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Short_Pin xGPIO Pin ID
//! 
//! \section xGPIO_Short_Pin_S1 1. Where to use this group
//! The following values define the short pin argument(dShortPin) to several
//! of the \b XPinTypexxx APIs and all the API which have a eShortPin argument.
//! Such as \ref xGPIOSPinRead(),\ref xGPIOSPinWrite().
//! 
//! \section xGPIO_Short_Pin_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO Short Pin ID      |       CoX      |         HT32F125x      |
//! |------------------------|----------------|------------------------|
//! |PXn                     |    Mandatory   |    PA0 PA1 ... PA15    |
//! |                        |                |------------------------|
//! |X is A, B, C ...        |                |    PB0 PB1 ... PB15    |
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
//! |General Peripheral Pin  |       CoX      |         HT32F125x      |
//! |------------------------|----------------|------------------------|
//! |ADCn                    |    Mandatory   |   ADC0 ADC1 ... ADC7   |
//! |------------------------|----------------|------------------------|
//! |I2CnSCK                 |    Mandatory   |         I2C0SCK        |
//! |------------------------|----------------|------------------------|
//! |I2CnSDA                 |    Mandatory   |         I2C0SDA        |
//! |------------------------|----------------|------------------------|
//! |SPInCLK                 |    Mandatory   |         SPI0CLK        |
//! |------------------------|----------------|------------------------|
//! |SPInMOSI                |    Mandatory   |         SPI0MOSI       |
//! |------------------------|----------------|------------------------|
//! |SPInMISO                |    Mandatory   |         SPI0MISO       |
//! |------------------------|----------------|------------------------|
//! |SPInCS                  |    Mandatory   |         SPI0CS         |
//! |------------------------|----------------|------------------------|
//! |UARTnRX                 |    Mandatory   |         UART0RX        |
//! |------------------------|----------------|------------------------|
//! |UARTnTX                 |    Mandatory   |         UART0TX        |
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

#define I2C0SCK                 I2C0SCK
#define I2C0SDA                 I2C0SDA

#define SPI0CLK                 SPI0CLK
#define SPI0MOSI                SPI0MOSI
#define SPI0MISO                SPI0MISO
#define SPI0CS                  SPI0CS

#define UART0RX                 UART0RX
#define UART0TX                 UART0TX
#define UART0CTS                UART0CTS
#define UART0DCD                UART0DCD
#define UART0DSR                UART0DSR
#define UART0DTR                UART0DTR
#define UART0RI                 UART0RI

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
#define T0EX                    T0EX
#define T1EX                    T1EX  
  
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
//! |xGPIO API                 |       CoX      |         HT32F125x      |
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
//! |xGPIOSPinTypeGPIOOutputQB |  Non-Mandatory |            N           |
//! |--------------------------|----------------|------------------------|
//! |xGPIOPadConfigSet         |  Non-Mandatory |            Y           |
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
//! \b xGPIO_DIR_MODE_HW, \b xGPIO_DIR_MODE_OD. 
//! 
//! Details please refer to \ref xGPIO_Dir_Mode_CoX.
//!
//! Where \b xGPIO_DIR_MODE_IN specifies that the pin will be programmed as
//! a software controlled input, \b xGPIO_DIR_MODE_OUT specifies that the pin
//! will be programmed as a software controlled output, specifies that the pin 
//! will be programmed as a Open-Drain.
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
#define xGPIODirModeSet(ulPort, ulPins, ulPinIO)                              \
        GPIODirModeSet(ulPort, ulPins, ulPinIO) 

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
//! \b xGPIO_DIR_MODE_OD specifies that the pin will be placed under
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
        GPIOSDirModeSet(eShortPin, ulPinIO)

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
//! \param ulPort is the base address of the EXTI.
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
        EXTIIntEdgeStatusGet();  

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
//! \note Because there is a write buffer in the Cortex-M3 processor, it may
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
        EXTIIntEdgeClear(ulPins)

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
//! \note Because there is a write buffer in the Cortex-M3 processor, it may
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
        EXTIIntEdgeClear2(eShortPin)

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
//! \brief Selects the driving current of specified GPIO pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//! \param ulDrive is Selection of output driving current.it can be selected one
//! of the following values:
//! 
//! - \ref xGPIO_DV_4MA
//! - \ref xGPIO_DV_8MA
//!
//! \param ulPadType is the logical OR of several different values, many of 
//!  which are grouped into sets where only one can be chosen.
//!
//£¡The open drain mode is chosen with one of the following values:
//! - \ref xGPIO_DIR_MODE_OD_EN
//! - \ref xGPIO_DIR_MODE_OD_DIS
//!
//! The pull resistor configure is chosen with one of the following values:
//! - \ref xGPIO_PIN_TYPE_STD_WPU
//! - \ref xGPIO_PIN_TYPE_STD_WPD
//! - \ref xGPIO_PR_DISABLE
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
#define XGPIOPadConfigSet(ulPort, ulPins, ulStrength, ulPadType)               \
        GPIOPadConfigSet(ulPort, (unsigned char)ulPins, ulStrength, ulPadType)

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
//! xSPinTypeADC(ADC0, PA0) or xSPinTypeADC(ADC1, PA1) is correct;<br/>
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
//! |                    |0 1 2 3 ....            |A B ...                 |
//! |                    |                        |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |       HT32F125x    |    ADC0                |    PA0                 |
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
//! |                    |number such as          |A B ...                 |
//! |                    |0 1 2 3 ....            |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |       HT32F125x    |    I2C0SCK             |    PA11                |
//! |                    |    I2C0SDA             |    PA12                |
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
//! xSPinTypePWM(PWM0, PA3) or xSPinTypePWM(PWM0, PA15) is correct;<br/>
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
//! |                    |0 1 2 3 ....            |A B ...                 |
//! |                    |                        |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |       HT32F125x    |    TIMCCP0             |    PA3,PA15            |
//! |                    |    TIMCCP1             |    PA2,PA14            |
//! |                    |    TIMCCP2             |    PA1,PA13            |
//! |                    |    TIMCCP3             |    PA0,PB11            |
//! |                    |    TIMCCP4             |    PB2,PB15            |
//! |                    |    TIMCCP5             |    PB3,PB14            |
//! |                    |    TIMCCP6             |    PB4,PB13            |
//! |                    |    TIMCCP7             |    PB5,PB12            |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//***************************************************************************** 
#define xSPinTypePWM(ePeripheralPin, eShortPin)                               \
        xSPinTypeTimer(ePeripheralPin, eShortPin)

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
//! xSPinTypeSPI(SPI0CLK, PA6) or xSPinTypeSPI(SPI0MOSI, PA4) is correct;<br/>
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
//! |                    |n indicate the pin      |A B ...                 |
//! |                    |number such as          |n indicate the pin      |
//! |                    |0 1 2 3 ....            |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |       HT32F125x    |    SPI0CLK             |    PA6,PB13            |
//! |                    |    SPI0MOSI            |    PA4,PB15            |
//! |                    |    SPI0MISO            |    PA5,PB14            |
//! |                    |    SPI0CS              |    PA7,PB12            |
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
//! |                    |0 1 2 3 ....            |A B ...                 |
//! |                    |                        |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |       HT32F125x    |    TIMCCP0             |    PA3,PA15            |
//! |                    |    TIMCCP1             |    PA2,PA14            |
//! |                    |    TIMCCP2             |    PA1,PA13            |
//! |                    |    TIMCCP3             |    PA0,PB11            |
//! |                    |    TIMCCP4             |    PB2,PB15            |
//! |                    |    TIMCCP5             |    PB3,PB14            |
//! |                    |    TIMCCP6             |    PB4,PB13            |
//! |                    |    TIMCCP7             |    PB5,PB12            |
//! |                    |    T0EX                |    PB10,PB7            |
//! |                    |    T1EX                |    PA0,PB6             |
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
//! xSPinTypeUART(UART0RX, PA8) or xSPinTypeUART(UART0TX, PA9) is correct;<br/>
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
//! |                    |n indicate the pin      |A B ...                 |
//! |                    |number such as          |n indicate the pin      |
//! |                    |0 1 2 3 ....            |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |       HT32F125x    |    UART0RX             |    PA8                 |
//! |                    |    UART0TX             |    PA9                 |
//! |                    |    UART0RTS            |    PA6, PB4            |
//! |                    |    UART0CTS            |    PA7, PB7            |
//! |                    |    UART0DCD            |    PA2, PB12           |
//! |                    |    UART0DSR            |    PA3, PB13           |
//! |                    |    UART0DTR            |    PA4, PB14           |
//! |                    |    UART0RI             |    PA5, PB15           |
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
//! |                    |number such as          |A B ...                 |
//! |                    |0 1 2 3 ....            |n indicate the pin      |
//! |                    |                        |number such as          |
//! |                    |                        |0 1 2 3 ....            |
//! |--------------------|------------------------|------------------------|
//! |       HT32F125x    |    CMP0P               |    PB3                 |
//! |                    |    CMP0N               |    PB2                 |
//! |                    |    CMP0O               |    PB4                 |
//! |                    |    CMP1P               |    PB6                 |
//! |                    |    CMP1N               |    PB5                 |
//! |                    |    CMP1O               |    PB7                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************            
#define xSPinTypeACMP(ePeripheralPin, eShortPin)                              \
        do                                                                    \
        {                                                                     \
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
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
         GPIOSPinConfigure(ePeripheralPin, eShortPin);                        \
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
//! \addtogroup HT32F125x_GPIO
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_General_Pin_IDs HT32F125x GPIO General Pin ID
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
//! \addtogroup HT32F125x_GPIO_General_Pin_Bits HT32F125x GPIO General Pin Bits
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
//! \addtogroup HT32F125x_GPIO_Dir_Mode HT32F125x GPIO Dir Mode
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
//! Pin is in hardware control mode
//          
#define GPIO_DIR_MODE_HW        0x00000003
          
//
//! Pin is in open drain mode (use in GPIODirModeGet function only)
//
#define GPIO_DIR_MODE_OD        0x00000004               
          
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
          
//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_IN_ENABLE HT32F125x GPIO Input Enable.
//! \brief Values that can be passed to GPIOInputConfigure as the ulPinIO ulEnable.
//! @{
//
//*****************************************************************************
   
//
//! Input function is enable
//          
#define GPIO_INPUT_ENABLE       0x00000001

//
//! Input function is disable
//          
#define GPIO_INPUT_DISABLE      0x00000000        
          
//*****************************************************************************
//
//! @}
//
//*****************************************************************************          

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Int_Type HT32F125x GPIO Int Type
//! \brief Values that can be passed to GPIOIntTypeSet as the ulIntType parameter, 
//! and returned from GPIOIntTypeGet.
//! @{
//
//*****************************************************************************

//
//! Interrupt on falling edge
//
#define GPIO_FALLING_EDGE       0x20000000  

//
//! Interrupt on rising edge
//
#define GPIO_RISING_EDGE        0x30000000

//
//! Interrupt on both edges
//
#define GPIO_BOTH_EDGES         0x40000000

//
//! Interrupt on low level
//
#define GPIO_LOW_LEVEL          0x00000000  

//
//! Interrupt on high level
//
#define GPIO_HIGH_LEVEL         0x10000000 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup HT32F125x_PULLRESISTOR_CONFIG HT32F125x Pull Resistor Configure
//! \brief Values that can be passed to XGPIOPadConfigSet  as the ulPadType  
//!  parameter.
//! @{
//
//***************************************************************************** 

//
//! weak pull-up resistor Enable
//         
#define GPIO_PIN_TYPE_STD_WPU   0x00000000
          
//
//! weak pull-down resistor Enable
//          
#define GPIO_PIN_TYPE_STD_WPD   0x00000001
          
//
//! Tri-state
//          
#define GPIO_PR_DISABLE         0x00000002          
                 
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
          
//*****************************************************************************
//
//! \addtogroup HT32F125x_OPEN_DRAIN_CFG HT32F125x Open Drain Mode Configure.
//! \brief Values that can be passed to XGPIOPadConfigSet as the ulPadType parameter.
//! @{
//
//*****************************************************************************
          
//
//! Pin Open-Drain mode enable.
//
#define GPIO_DIR_MODE_OD_EN      0x00000010
          
//
//! Pin Open-Drain mode disable 
//  
#define GPIO_DIR_MODE_OD_DIS     0x00000000          

//*****************************************************************************
//
//! @}
//
//*****************************************************************************   
          
//*****************************************************************************
//
//! \addtogroup HT32F125x_OUTPUT_DRIVING HT32F125x output driving current.
//! \brief Values that can be passed to XGPIOPadConfigSet as the ulStrength parameter.
//! @{
//
//*****************************************************************************

//
//! Output driving current as 4 mA
//
#define GPIO_STRENGTH_4MA       0x00000000
#define GPIO_STRENGTH_8MA       0x00000001          
          
//*****************************************************************************
//
//! @}
//
//*****************************************************************************           
          
//*****************************************************************************
//
//! \addtogroup HT32F125x_EXTI_LINES HT32F125x EXTI LINE
//! \brief Values that can be passed to EXTILineDebounceEnable as the ulClockSource
//! parameter.
//! @{
//
//***************************************************************************** 

//
//! EXTI Lines
//
#define EXTI_LINE_0             0x00000001
#define EXTI_LINE_1             0x00000002
#define EXTI_LINE_2             0x00000004
#define EXTI_LINE_3             0x00000008
#define EXTI_LINE_4             0x00000010
#define EXTI_LINE_5             0x00000020
#define EXTI_LINE_6             0x00000040
#define EXTI_LINE_7             0x00000080
#define EXTI_LINE_8             0x00000100
#define EXTI_LINE_9             0x00000200
#define EXTI_LINE_10            0x00000400
#define EXTI_LINE_11            0x00000800
#define EXTI_LINE_12            0x00001000
#define EXTI_LINE_13            0x00002000
#define EXTI_LINE_14            0x00004000  
#define EXTI_LINE_15            0x00008000
          
//*****************************************************************************
//
//! @}
//
//***************************************************************************** 
          
//*****************************************************************************
//
//! \addtogroup HT32F125x_EXTI_WAKEUP_INT HT32F125x EXTI Wake Up Int
//! \brief Values that can be passed to EXTIWakeUpIntConfigure as the ulWakeUpInt
//! parameter.
//! @{
//
//***************************************************************************** 

//
//! Enable the wake up  interrupt
//          
#define EXTI_WAKEUP_INT_ENABLE  0x00000000 

//
//! Disable the wake up  interrupt
//          
#define EXTI_WAKEUP_INT_DISABLE 0x00000001           
          
//*****************************************************************************
//
//! @}
//
//*****************************************************************************  
          
//*****************************************************************************
//
//! \addtogroup HT32F125x_EXTILINE_WAKEUP HT32F125x EXTI Line Wake Up Configure
//! \brief Values that can be passed to EXTILineWakeUpConfigure as the ulLevel
//! and ulEnable parameter.
//! @{
//
//***************************************************************************** 

//
//! EXTI Line wake up level
//          
#define EXTI_LINE_WAKEUP_LOW    0x00000001
#define EXTI_LINE_WAKEUP_HIGH   0x00000000

//
//! EXTI Lines wake up enable
//
#define EXTI_LINES_WAKEUP_ENABLE                                               \
                                0x00000001
#define EXTI_LINES_WAKEUP_DISABLE                                              \
                                0x00000000          
          
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
          
//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Function_Set HT32F125x GPIO Function Set
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
#define GPIO_FUNCTION_PWM       0x00000006   
#define GPIO_FUNCTION_TIM       0x00000007   
#define GPIO_FUNCTION_UART      0x00000008   

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Pin_Config HT32F125x GPIO Pin Config
//! \brief Values that can be passed to xGPIOPinConfigure as the ulPinConfig 
//! parameter.
//! @{
//
//*****************************************************************************

//
//! GPIO pin A0
//
#define GPIO_PA0_ADC0           0x00000001
#define GPIO_PA0_T1EX           0x00000002
#define GPIO_PA0_TIMCCP3        0x00000003

//
//! GPIO pin A1
//
#define GPIO_PA1_ADC1           0x00000101
#define GPIO_PA1_TIMCCP2        0x00000103

//
//! GPIO pin A2
//
#define GPIO_PA2_ADC2           0x00000201
#define GPIO_PA2_UART0DCD       0x00000202
#define GPIO_PA2_TIMCCP1        0x00000203

//
//! GPIO pin A3
//
#define GPIO_PA3_ADC3           0x00000301
#define GPIO_PA3_UART0DSR       0x00000302
#define GPIO_PA3_TIMCCP0        0x00000303

//
//! GPIO pin A4
//
#define GPIO_PA4_ADC4           0x00000401
#define GPIO_PA4_UART0DTR       0x00000402
#define GPIO_PA4_SPI0MOSI       0x00000403

//
//! GPIO pin A5
//
#define GPIO_PA5_ADC5           0x00000501
#define GPIO_PA5_UART0RI        0x00000502
#define GPIO_PA5_SPI0MISO       0x00000503

//
//! GPIO pin A6
//
#define GPIO_PA6_ADC6           0x00000601
#define GPIO_PA6_UART0RTS       0x00000602
#define GPIO_PA6_SPI0CLK        0x00000603

//
//! GPIO pin A7
//
#define GPIO_PA7_ADC7           0x00000701
#define GPIO_PA7_UART0CTS       0x00000702
#define GPIO_PA7_SPI0CS         0x00000703

//
//! GPIO pin A8
//
#define GPIO_PA8_UART0RX        0x00000802

//
//! GPIO pin A9
//
#define GPIO_PA9_BOOT0          0x00000900
#define GPIO_PA9_UART0TX        0x00000902

//
//! GPIO pin A10
//
#define GPIO_PA10_BOOT1         0x00000A00

//
//! GPIO pin A11
//
#define GPIO_PA11_I2C0SCK       0x00000B01

//
//! GPIO pin A12
//
#define GPIO_PA12_I2C0SDA       0x00000C01

//
//! GPIO pin A13
//
#define GPIO_PA13_SWDIO         0x00000D00
#define GPIO_PA13_TIMCCP2       0x00000D03

//
//! GPIO pin A14
//
#define GPIO_PA14_SWCLK         0x00000E00
#define GPIO_PA14_TIMCCP1       0x00000E03

//
//! GPIO pin A15
//
#define GPIO_PA15_TRACESWO      0x00000F00
#define GPIO_PA15_TIMCCP0       0x00000F03

//
//! GPIO pin B0
//
#define GPIO_PB0_XTALIN         0x00001000

//
//! GPIO pin B1
//
#define GPIO_PB1_XTALOUT        0x00001100

//
//! GPIO pin B2
//
#define GPIO_PB2_CMP0N          0x00001201
#define GPIO_PB2_TIMCCP4        0x00001203

//
//! GPIO pin B3
//
#define GPIO_PB3_CMP0P          0x00001301
#define GPIO_PB3_TIMCCP5        0x00001303 

//
//! GPIO pin B4
//
#define GPIO_PB4_CMP0O          0x00001401
#define GPIO_PB4_UART0RTS       0x00001402
#define GPIO_PB4_TIMCCP6        0x00001403

//
//! GPIO pin B5
//
#define GPIO_PB5_CMP1N          0x00001501
#define GPIO_PB5_TIMCCP7        0x00001503

//
//! GPIO pin B6
//
#define GPIO_PB6_CMP1P          0x00001601
#define GPIO_PB6_T1EX           0x00001603

//
//! GPIO pin B7
//
#define GPIO_PB7_CMP1O          0x00001701
#define GPIO_PB7_UART0CTS       0x00001702
#define GPIO_PB7_T0EX           0x00001703

//
//! GPIO pin B8
//
#define GPIO_PB8_XTAL32KIN      0x00001800

//
//! GPIO pin B9
//
#define GPIO_PB9_XTAL32KOUT     0x00001900

//
//! GPIO pin B10
//
#define GPIO_PB10_RTCOUT        0x00001A00
#define GPIO_PB10_WAKEUP        0x00001A01
#define GPIO_PB10_T0EX          0x00001A03

//
//! GPIO pin B11
//
#define GPIO_PB11_CKOUT         0x00001B01
#define GPIO_PB11_TIMCCP3       0x00001B03

//
//! GPIO pin B12
//
#define GPIO_PB12_SPI0CS        0x00001C01
#define GPIO_PB12_UART0DCD      0x00001C02
#define GPIO_PB12_TIMCCP7       0x00001C03

//
//! GPIO pin B13
//
#define GPIO_PB13_SPI0CLK       0x00001D01
#define GPIO_PB13_UART0DSR      0x00001D02
#define GPIO_PB13_TIMCCP6       0x00001D03

//
//! GPIO pin B14
//
#define GPIO_PB14_SPI0MISO      0x00001E01
#define GPIO_PB14_UART0DTR      0x00001E02
#define GPIO_PB14_TIMCCP5       0x00001E03

//
//! GPIO pin B15
//
#define GPIO_PB15_SPI0MOSI      0x00001F01
#define GPIO_PB15_UART0RI       0x00001F02
#define GPIO_PB15_TIMCCP4       0x00001F03

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Exported_APIs HT32F125x GPIO API
//! \brief GPIO API Reference.
//! @{
//
//*****************************************************************************

#define GPIOSPinFunctionSet(ulFunction, eShortPin)                            \
        GPIOPinFunctionSet(ulFunction, G##eShortPin)

#define GPIOSPinIntEnable(eShortPin, ulIntType)                               \
        GPIOPinIntEnable(G##eShortPin, ulIntType)

#define GPIOSDirModeSet(eShortPin, ulPinIO)                                  \
        GPIODirModeSet(G##eShortPin, ulPinIO)

#define GPIOSPinIntDisable(eShortPin)                                         \
        GPIOPinIntDisable(G##eShortPin)
          
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

extern void GPIODirModeSet(unsigned long ulPort, unsigned long ulPins, 
                           unsigned long ulPinIO);
extern unsigned long GPIODirModeGet(unsigned long ulPort, unsigned long ulBit);
extern void GPIOInputConfigure(unsigned long ulPort, unsigned long ulPins, 
                               unsigned long ulEnable);
extern long GPIOPinRead(unsigned long ulPort, unsigned long ulPins);
extern void GPIOPinWrite(unsigned long ulPort, unsigned long ulPins,
		                 unsigned char ucVal);
extern void GPIOPortWrite(unsigned long ulPort, unsigned long ulVal);
extern long GPIOPinPortDoutGet(unsigned long ulPort);

extern void GPIOPadConfigSet(unsigned long ulPort, unsigned long ulPins, 
                             unsigned long ulStrength, unsigned long ulPadType);

extern void GPIOPinFunctionSet(unsigned long ulFunction, unsigned long ulPort, 
                               unsigned long ulPins);
extern void GPIOPinConfigure(unsigned long ulPinConfig);

extern void GPIOPinIntEnable(unsigned long ulPort, unsigned long ulPins,
                             unsigned long ulIntType);
extern void GPIOPinIntDisable(unsigned long ulPort, unsigned long ulPins);
extern void GPIOPinIntCallbackInit(unsigned long ulPort, unsigned long ulPin, 
                                   xtEventCallback xtPortCallback);
extern unsigned long EXTIIntEdgeFlagGet(void);
extern void EXTIIntEdgeClear(unsigned long ulEXTILines);
extern void EXTIIntEdgeClear2(unsigned long ulBase, unsigned long ulEXTILines);
extern void EXTILineWakeUpConfigure(unsigned long ulEXTILines, unsigned long ulLevel,
                                    unsigned long ulEnable);

extern void EXTILineSourceSelect(unsigned long ulEXTILines, unsigned long ulPort);

extern void EXTIWakeUpIntConfigure(unsigned long ulEnable);
extern unsigned long EXTIWakeUpStatusGet(void);
extern void EXTIWakeUpStatusClear(unsigned long ulEXTILines);

extern void EXTILineSoftwareTrigger(unsigned long ulEXTILine);
extern void EXTILineSoftwareClear(unsigned long ulEXTILine);

extern void EXTILineDebounceEnable(unsigned long ulEXTILines);
extern void EXTILineDebounceDisable(unsigned long ulEXTILines);
extern void EXTIDebounceTimeSet(unsigned long ulEXTILines, unsigned long ulDebounceClk);
extern long EXTIDebounceTimeGet(unsigned long ulEXTILines);

extern void GPIOPinLockSet(unsigned long ulPort, unsigned long ulPins);
extern xtBoolean GPIOPinLockGet(unsigned long ulPort, unsigned long ulPin);

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


