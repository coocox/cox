//*****************************************************************************
//
//! \file      xgpio.h
//! \brief     Prototypes for the GPIO Driver.
//! \version   V2.2.1.0
//! \date      $CURRENTTIME$
//! \author    CooCox
//! \copyright
//!
//! Copyright (c)  2011, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
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
//! \section    xGPIO_General_Pin_IDs 1. Where to use this group
//!             The following values define the bit field for the ulPins argument
//!             to several of the APIs. So all the API which have a ulPins
//!             argument must use this group.
//!
//! \section    xGPIO_General_Pin_IDs_CoX 2.CoX Port Details
//!
//! |  xGPIO General Pin ID    |       CoX      |          LPC17xx       |
//! |--------------------------|----------------|------------------------|
//! |  xGPIO_PIN_n             |    Mandatory   |       xGPIO_PIN_0      |
//! |                          |                |       xGPIO_PIN_1      |
//! |                          |                |         ...            |
//! |                          |                |      xGPIO_PIN_30      |
//! |                          |                |      xGPIO_PIN_31      |
//!
//! @{
//
//*****************************************************************************

//! GPIO Pin 0
#define xGPIO_PIN_0             GPIO_PIN_0

//! GPIO Pin 1
#define xGPIO_PIN_1             GPIO_PIN_1

//! GPIO Pin 2
#define xGPIO_PIN_2             GPIO_PIN_2

//! GPIO Pin 3
#define xGPIO_PIN_3             GPIO_PIN_3

//! GPIO Pin 4
#define xGPIO_PIN_4             GPIO_PIN_4

//! GPIO Pin 5
#define xGPIO_PIN_5             GPIO_PIN_5

//! GPIO Pin 6
#define xGPIO_PIN_6             GPIO_PIN_6

//! GPIO Pin 7
#define xGPIO_PIN_7             GPIO_PIN_7

//! GPIO Pin 8
#define xGPIO_PIN_8             GPIO_PIN_8

//! GPIO Pin 9
#define xGPIO_PIN_9             GPIO_PIN_9

//! GPIO Pin 10
#define xGPIO_PIN_10            GPIO_PIN_10

//! GPIO Pin 11
#define xGPIO_PIN_11            GPIO_PIN_11

//! GPIO Pin 12
#define xGPIO_PIN_12            GPIO_PIN_12

//! GPIO Pin 13
#define xGPIO_PIN_13            GPIO_PIN_13

//! GPIO Pin 14
#define xGPIO_PIN_14            GPIO_PIN_14

//! GPIO Pin 15
#define xGPIO_PIN_15            GPIO_PIN_15

//! GPIO Pin 16
#define xGPIO_PIN_16            GPIO_PIN_16

//! GPIO Pin 17
#define xGPIO_PIN_17            GPIO_PIN_17

//! GPIO Pin 18
#define xGPIO_PIN_18            GPIO_PIN_18

//! GPIO Pin 19
#define xGPIO_PIN_19            GPIO_PIN_19

//! GPIO Pin 20
#define xGPIO_PIN_20            GPIO_PIN_20

//! GPIO Pin 21
#define xGPIO_PIN_21            GPIO_PIN_21

//! GPIO Pin 22
#define xGPIO_PIN_22            GPIO_PIN_22

//! GPIO Pin 23
#define xGPIO_PIN_23            GPIO_PIN_23

//! GPIO Pin 24
#define xGPIO_PIN_24            GPIO_PIN_24

//! GPIO Pin 25
#define xGPIO_PIN_25            GPIO_PIN_25

//! GPIO Pin 26
#define xGPIO_PIN_26            GPIO_PIN_26

//! GPIO Pin 27
#define xGPIO_PIN_27            GPIO_PIN_27

//! GPIO Pin 28
#define xGPIO_PIN_28            GPIO_PIN_28

//! GPIO Pin 29
#define xGPIO_PIN_29            GPIO_PIN_29

//! GPIO Pin 30
#define xGPIO_PIN_30            GPIO_PIN_30

//! GPIO Pin 31
#define xGPIO_PIN_31            GPIO_PIN_31

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Dir_Mode xGPIO Dir Mode
//!
//! \section    xGPIO_Dir_Mode_S1 1. Where to use this group
//!             Values that can be passed to xGPIODirModeSet as the ulPinIO
//!             parameter, and returned from xGPIODirModeGet.
//!
//! \section    xGPIO_Dir_Mode_CoX 2.CoX Port Details
//!
//! |  xGPIO Dir Mode       |       CoX       |          LPC17xx       |
//! |-----------------------|-----------------|------------------------|
//! |  xGPIO_DIR_MODE_IN    |    Mandatory    |            Y           |
//! |  xGPIO_DIR_MODE_OUT   |    Mandatory    |            Y           |
//! |  xGPIO_DIR_MODE_HW    |    Mandatory    |            N           |
//! |  xGPIO_DIR_MODE_QB    |  Non-Mandatory  |            N           |
//! |  xGPIO_DIR_MODE_OD    |  Non-Mandatory  |            Y           |
//!
//! @{
//
//*****************************************************************************

//
//! Pin is a GPIO input
//
#define xGPIO_DIR_MODE_IN       PIN_MODE_INPUT

//
//! Pin is a GPIO output
//
#define xGPIO_DIR_MODE_OUT      PIN_MODE_OUTPUT

//
//! Pin is a peripheral function
//
#define xGPIO_DIR_MODE_HW       0

//
//! Pin is in Quasi-bidirectional mode
//
#define xGPIO_DIR_MODE_QB       0

//
//! Pin is in Open-Drain mode.
//
#define xGPIO_DIR_MODE_OD       PIN_MODE_OD_EN

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Int_Type xGPIO Int Type
//!
//! \section    xGPIO_Int_Type_S1 1. Where to use this group
//!             Values that can be passed to xGPIOIntTypeSet as the ulIntType
//!             parameter, and returned from xGPIOIntTypeGet.
//!
//! \section xGPIO_Int_Type_CoX 2.CoX Port Details
//!
//! |  xGPIO Int Type       |       CoX      |          LPC17xx       |
//! |-----------------------|----------------|------------------------|
//! |  xGPIO_FALLING_EDGE   |    Mandatory   |            Y           |
//! |  xGPIO_RISING_EDGE    |    Mandatory   |            Y           |
//! |  xGPIO_LOW_LEVEL      |    Mandatory   |            N           |
//! |  xGPIO_HIGH_LEVEL     |    Mandatory   |            N           |
//! |  xGPIO_BOTH_LEVEL     |  Non-Mandatory |            N           |
//! |  xGPIO_BOTH_EDGES     |  Non-Mandatory |            Y           |
//!
//! @{
//
//*****************************************************************************

//
//! Interrupt on falling edge
//
#define xGPIO_FALLING_EDGE      INT_TYPE_FALLING

//
//! Interrupt on rising edge
//
#define xGPIO_RISING_EDGE       INT_TYPE_RISING

//
//! Interrupt on low level
//
#define xGPIO_LOW_LEVEL         0

//
//! Interrupt on high level
//
#define xGPIO_HIGH_LEVEL        0

//
//! Interrupt on both edge
//
#define xGPIO_BOTH_EDGES        (INT_TYPE_RISING | INT_TYPE_FALLING)

//
//! Interrupt on both level
//
#define xGPIO_BOTH_LEVEL        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Pad_Config_Strength xGPIO Pad Config Strength
//!
//! \section    xGPIO_Pad_Config_Strength_S1 1. Where to use this group
//!             Values that can be passed to xGPIOPadConfigSet as the ulStrength
//!             parameter, and returned by xGPIOPadConfigGet in the pulStrength
//!             parameter.
//!
//! \section    xGPIO_Pad_Config_Strength_CoX 2.CoX Port Details
//!
//! |  xGPIO Pad Strength   |       CoX      |          LPC17xx       |
//! |-----------------------|----------------|------------------------|
//! |  xGPIO_STRENGTH_nMA   | Non-Mandatory  |            N           |
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
//! \addtogroup xGPIO_GP_Short_Pin xGPIO General Purpose Short Pin
//! @{
//
//*****************************************************************************

//! PortA
//! For LPC17xx mcu, Port A is equal to Port 0
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
#define GPA16                   GPIOA_BASE, GPIO_PIN_16
#define GPA17                   GPIOA_BASE, GPIO_PIN_17
#define GPA18                   GPIOA_BASE, GPIO_PIN_18
#define GPA19                   GPIOA_BASE, GPIO_PIN_19
#define GPA20                   GPIOA_BASE, GPIO_PIN_20
#define GPA21                   GPIOA_BASE, GPIO_PIN_21
#define GPA22                   GPIOA_BASE, GPIO_PIN_22
#define GPA23                   GPIOA_BASE, GPIO_PIN_23
#define GPA24                   GPIOA_BASE, GPIO_PIN_24
#define GPA25                   GPIOA_BASE, GPIO_PIN_25
#define GPA26                   GPIOA_BASE, GPIO_PIN_26
#define GPA27                   GPIOA_BASE, GPIO_PIN_27
#define GPA28                   GPIOA_BASE, GPIO_PIN_28
#define GPA29                   GPIOA_BASE, GPIO_PIN_29
#define GPA30                   GPIOA_BASE, GPIO_PIN_30
#define GPA31                   GPIOA_BASE, GPIO_PIN_31

//! PortB
//! For LPC17xx mcu, Port B is equal to Port 1
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
#define GPB16                   GPIOB_BASE, GPIO_PIN_16
#define GPB17                   GPIOB_BASE, GPIO_PIN_17
#define GPB18                   GPIOB_BASE, GPIO_PIN_18
#define GPB19                   GPIOB_BASE, GPIO_PIN_19
#define GPB20                   GPIOB_BASE, GPIO_PIN_20
#define GPB21                   GPIOB_BASE, GPIO_PIN_21
#define GPB22                   GPIOB_BASE, GPIO_PIN_22
#define GPB23                   GPIOB_BASE, GPIO_PIN_23
#define GPB24                   GPIOB_BASE, GPIO_PIN_24
#define GPB25                   GPIOB_BASE, GPIO_PIN_25
#define GPB26                   GPIOB_BASE, GPIO_PIN_26
#define GPB27                   GPIOB_BASE, GPIO_PIN_27
#define GPB28                   GPIOB_BASE, GPIO_PIN_28
#define GPB29                   GPIOB_BASE, GPIO_PIN_29
#define GPB30                   GPIOB_BASE, GPIO_PIN_30
#define GPB31                   GPIOB_BASE, GPIO_PIN_31

//! PortC
//! For LPC17xx mcu, Port C is equal to Port 2
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
#define GPC16                   GPIOC_BASE, GPIO_PIN_16
#define GPC17                   GPIOC_BASE, GPIO_PIN_17
#define GPC18                   GPIOC_BASE, GPIO_PIN_18
#define GPC19                   GPIOC_BASE, GPIO_PIN_19
#define GPC20                   GPIOC_BASE, GPIO_PIN_20
#define GPC21                   GPIOC_BASE, GPIO_PIN_21
#define GPC22                   GPIOC_BASE, GPIO_PIN_22
#define GPC23                   GPIOC_BASE, GPIO_PIN_23
#define GPC24                   GPIOC_BASE, GPIO_PIN_24
#define GPC25                   GPIOC_BASE, GPIO_PIN_25
#define GPC26                   GPIOC_BASE, GPIO_PIN_26
#define GPC27                   GPIOC_BASE, GPIO_PIN_27
#define GPC28                   GPIOC_BASE, GPIO_PIN_28
#define GPC29                   GPIOC_BASE, GPIO_PIN_29
#define GPC30                   GPIOC_BASE, GPIO_PIN_30
#define GPC31                   GPIOC_BASE, GPIO_PIN_31

//! PortD
//! For LPC17xx mcu, Port D is equal to Port 3
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
#define GPD16                   GPIOD_BASE, GPIO_PIN_16
#define GPD17                   GPIOD_BASE, GPIO_PIN_17
#define GPD18                   GPIOD_BASE, GPIO_PIN_18
#define GPD19                   GPIOD_BASE, GPIO_PIN_19
#define GPD20                   GPIOD_BASE, GPIO_PIN_20
#define GPD21                   GPIOD_BASE, GPIO_PIN_21
#define GPD22                   GPIOD_BASE, GPIO_PIN_22
#define GPD23                   GPIOD_BASE, GPIO_PIN_23
#define GPD24                   GPIOD_BASE, GPIO_PIN_24
#define GPD25                   GPIOD_BASE, GPIO_PIN_25
#define GPD26                   GPIOD_BASE, GPIO_PIN_26
#define GPD27                   GPIOD_BASE, GPIO_PIN_27
#define GPD28                   GPIOD_BASE, GPIO_PIN_28
#define GPD29                   GPIOD_BASE, GPIO_PIN_29
#define GPD30                   GPIOD_BASE, GPIO_PIN_30
#define GPD31                   GPIOD_BASE, GPIO_PIN_31

//! PortE
//! For LPC17xx mcu, Port E is equal to Port 4
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
#define GPE16                   GPIOE_BASE, GPIO_PIN_16
#define GPE17                   GPIOE_BASE, GPIO_PIN_17
#define GPE18                   GPIOE_BASE, GPIO_PIN_18
#define GPE19                   GPIOE_BASE, GPIO_PIN_19
#define GPE20                   GPIOE_BASE, GPIO_PIN_20
#define GPE21                   GPIOE_BASE, GPIO_PIN_21
#define GPE22                   GPIOE_BASE, GPIO_PIN_22
#define GPE23                   GPIOE_BASE, GPIO_PIN_23
#define GPE24                   GPIOE_BASE, GPIO_PIN_24
#define GPE25                   GPIOE_BASE, GPIO_PIN_25
#define GPE26                   GPIOE_BASE, GPIO_PIN_26
#define GPE27                   GPIOE_BASE, GPIO_PIN_27
#define GPE28                   GPIOE_BASE, GPIO_PIN_28
#define GPE29                   GPIOE_BASE, GPIO_PIN_29
#define GPE30                   GPIOE_BASE, GPIO_PIN_30
#define GPE31                   GPIOE_BASE, GPIO_PIN_31

//! PortF
//! For LPC17xx mcu, Port E is equal to Port 5
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
#define GPF16                   GPIOF_BASE, GPIO_PIN_16
#define GPF17                   GPIOF_BASE, GPIO_PIN_17
#define GPF18                   GPIOF_BASE, GPIO_PIN_18
#define GPF19                   GPIOF_BASE, GPIO_PIN_19
#define GPF20                   GPIOF_BASE, GPIO_PIN_20
#define GPF21                   GPIOF_BASE, GPIO_PIN_21
#define GPF22                   GPIOF_BASE, GPIO_PIN_22
#define GPF23                   GPIOF_BASE, GPIO_PIN_23
#define GPF24                   GPIOF_BASE, GPIO_PIN_24
#define GPF25                   GPIOF_BASE, GPIO_PIN_25
#define GPF26                   GPIOF_BASE, GPIO_PIN_26
#define GPF27                   GPIOF_BASE, GPIO_PIN_27
#define GPF28                   GPIOF_BASE, GPIO_PIN_28
#define GPF29                   GPIOF_BASE, GPIO_PIN_29
#define GPF30                   GPIOF_BASE, GPIO_PIN_30
#define GPF31                   GPIOF_BASE, GPIO_PIN_31

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Short_Pin xGPIO Short Pin ID
//!
//! \section    xGPIO_Short_Pin_S1 1. Where to use this group
//!             The following values define the short pin argument(dShortPin)
//!             to several of the \b XPinTypexxx APIs and all the API which have
//!             a eShortPin argument.
//!             Such as
//!             \ref xGPIOSPinRead()
//!             \ref xGPIOSPinWrite()
//!
//! \section    xGPIO_Short_Pin_CoX 2.CoX Port Details
//! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//! +-------------------------+----------------+------------------------+
//! |  xGPIO Short Pin ID     |       CoX      |          LPC17xx       |
//! |-------------------------|----------------|------------------------|
//! |  PXn                    |    Mandatory   |    PA0 PA1 ... PA31    |
//! |   (X = A/B/...)         |                |------------------------|
//! |   (n = 0/1/...)         |                |    PB0 PB1 ... PB31    |
//! |                         |                |------------------------|
//! |                         |                |     ...                |
//! |                         |                |------------------------|
//! |                         |                |    PE0 PE1 ... PE31    |
//! +-------------------------+----------------+------------------------+
//! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//! @{
//
//*****************************************************************************

//! PortA
//! For LPC17xx mcu, Port A is equal to Port 0
#define PA0                      PA0
#define PA1                      PA1
#define PA2                      PA2
#define PA3                      PA3
#define PA4                      PA4
#define PA5                      PA5
#define PA6                      PA6
#define PA7                      PA7
#define PA8                      PA8
#define PA9                      PA9
#define PA10                     PA10
#define PA11                     PA11
#define PA12                     PA12
#define PA13                     PA13
#define PA14                     PA14
#define PA15                     PA15
#define PA16                     PA16
#define PA17                     PA17
#define PA18                     PA18
#define PA19                     PA19
#define PA20                     PA20
#define PA21                     PA21
#define PA22                     PA22
#define PA23                     PA23
#define PA24                     PA24
#define PA25                     PA25
#define PA26                     PA26
#define PA27                     PA27
#define PA28                     PA28
#define PA29                     PA29
#define PA30                     PA30
#define PA31                     PA31

//! PortB
//! For LPC17xx mcu, Port B is equal to Port 1
#define PB0                      PB0
#define PB1                      PB1
#define PB2                      PB2
#define PB3                      PB3
#define PB4                      PB4
#define PB5                      PB5
#define PB6                      PB6
#define PB7                      PB7
#define PB8                      PB8
#define PB9                      PB9
#define PB10                     PB10
#define PB11                     PB11
#define PB12                     PB12
#define PB13                     PB13
#define PB14                     PB14
#define PB15                     PB15
#define PB16                     PB16
#define PB17                     PB17
#define PB18                     PB18
#define PB19                     PB19
#define PB20                     PB20
#define PB21                     PB21
#define PB22                     PB22
#define PB23                     PB23
#define PB24                     PB24
#define PB25                     PB25
#define PB26                     PB26
#define PB27                     PB27
#define PB28                     PB28
#define PB29                     PB29
#define PB30                     PB30
#define PB31                     PB31

//! PortC
//! For LPC17xx mcu, Port C is equal to Port 2
#define PC0                      PC0
#define PC1                      PC1
#define PC2                      PC2
#define PC3                      PC3
#define PC4                      PC4
#define PC5                      PC5
#define PC6                      PC6
#define PC7                      PC7
#define PC8                      PC8
#define PC9                      PC9
#define PC10                     PC10
#define PC11                     PC11
#define PC12                     PC12
#define PC13                     PC13
#define PC14                     PC14
#define PC15                     PC15
#define PC16                     PC16
#define PC17                     PC17
#define PC18                     PC18
#define PC19                     PC19
#define PC20                     PC20
#define PC21                     PC21
#define PC22                     PC22
#define PC23                     PC23
#define PC24                     PC24
#define PC25                     PC25
#define PC26                     PC26
#define PC27                     PC27
#define PC28                     PC28
#define PC29                     PC29
#define PC30                     PC30
#define PC31                     PC31

//! PortD
//! For LPC17xx mcu, Port D is equal to Port 3
#define PD0                      PD0
#define PD1                      PD1
#define PD2                      PD2
#define PD3                      PD3
#define PD4                      PD4
#define PD5                      PD5
#define PD6                      PD6
#define PD7                      PD7
#define PD8                      PD8
#define PD9                      PD9
#define PD10                     PD10
#define PD11                     PD11
#define PD12                     PD12
#define PD13                     PD13
#define PD14                     PD14
#define PD15                     PD15
#define PD16                     PD16
#define PD17                     PD17
#define PD18                     PD18
#define PD19                     PD19
#define PD20                     PD20
#define PD21                     PD21
#define PD22                     PD22
#define PD23                     PD23
#define PD24                     PD24
#define PD25                     PD25
#define PD26                     PD26
#define PD27                     PD27
#define PD28                     PD28
#define PD29                     PD29
#define PD30                     PD30
#define PD31                     PD31

//! PortE
//! For LPC17xx mcu, Port E is equal to Port 4
#define PE0                      PE0
#define PE1                      PE1
#define PE2                      PE2
#define PE3                      PE3
#define PE4                      PE4
#define PE5                      PE5
#define PE6                      PE6
#define PE7                      PE7
#define PE8                      PE8
#define PE9                      PE9
#define PE10                     PE10
#define PE11                     PE11
#define PE12                     PE12
#define PE13                     PE13
#define PE14                     PE14
#define PE15                     PE15
#define PE16                     PE16
#define PE17                     PE17
#define PE18                     PE18
#define PE19                     PE19
#define PE20                     PE20
#define PE21                     PE21
#define PE22                     PE22
#define PE23                     PE23
#define PE24                     PE24
#define PE25                     PE25
#define PE26                     PE26
#define PE27                     PE27
#define PE28                     PE28
#define PE29                     PE29
#define PE30                     PE30
#define PE31                     PE31

//! PortE
//! For LPC17xx mcu, Port E is equal to Port 4
#define PF0                      PF0
#define PF1                      PF1
#define PF2                      PF2
#define PF3                      PF3
#define PF4                      PF4
#define PF5                      PF5
#define PF6                      PF6
#define PF7                      PF7
#define PF8                      PF8
#define PF9                      PF9
#define PF10                     PF10
#define PF11                     PF11
#define PF12                     PF12
#define PF13                     PF13
#define PF14                     PF14
#define PF15                     PF15
#define PF16                     PF16
#define PF17                     PF17
#define PF18                     PF18
#define PF19                     PF19
#define PF20                     PF20
#define PF21                     PF21
#define PF22                     PF22
#define PF23                     PF23
#define PF24                     PF24
#define PF25                     PF25
#define PF26                     PF26
#define PF27                     PF27
#define PF28                     PF28
#define PF29                     PF29
#define PF30                     PF30
#define PF31                     PF31

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup xGPIO_Peripheral_Pin xGPIO General Peripheral Pin
//! \brief      General Peripheral Pin Name.
//!
//! \section    xGPIO_Peripheral_Pin_define xGPIO Peripheral Pin define
//!             The macros of General Peripheral Pin Name always like:
//!             <b> ModuleName + n + PinName </b>, such as CAN0RX, SPI1CLK.
//!
//! \section    xGPIO_Peripheral_Pin_Port CoX Port Details.
//!
//! | General Peripheral Pin  |       CoX      |          LPC17xx                |
//! |-------------------------|----------------|---------------------------------|
//! | ADCn                    |    Mandatory   | ADC0 ADC1 ... ADC7              |
//! | I2CnSCK                 |    Mandatory   | I2C0SCK I2C1SCK I2C2SCK         |
//! | I2CnSDA                 |    Mandatory   | I2C0SDA I2C1SDA I2C2SDA         |
//! | SPInCLK                 |    Mandatory   | SPI0CLK                         |
//! | SPInMOSI                |    Mandatory   | SPI0MOSI                        |
//! | SPInMISO                |    Mandatory   | SPI0MISO                        |
//! | SPInCS                  |    Mandatory   | SPI0CS                          |
//! | UARTnRX                 |    Mandatory   | UART0RX UART1RX UART2RX UART3RX |
//! | UARTnTX                 |    Mandatory   | UART0TX UART1TX UART2TX UART3TX |
//! | UARTnCTS                |    Mandatory   | UART1CTS                        |
//! | UARTnDCD                |    Mandatory   | UART1DCD                        |
//! | UARTnDSR                |    Mandatory   | UART1DSR                        |
//! | UARTnDTR                |    Mandatory   | UART1DTR                        |
//! | PWMn                    |    Mandatory   | PWM0 ... PWM6                   |
//! | TIMCCPn                 |    Mandatory   | TIMCCP0 ... TIMCCP7             |
//! | DACOUTn                 |    Mandatory   | DACOUT0                         |
//! | CANnRX                  |    Mandatory   | CAN0RX  CAN1RX                  |
//! | CANnTX                  |    Mandatory   | CAN0TX  CAN1TX                  |
//!
//! @{
//
//*****************************************************************************

//! PWM Pin Type
#define PWM1                    PWM1
#define PWM2                    PWM2
#define PWM3                    PWM3
#define PWM4                    PWM4
#define PWM5                    PWM5
#define PWM6                    PWM6
#define PWM_CAP_CH0             PWM_CAP_CH0
#define PWM_CAP_CH1             PWM_CAP_CH1

//! UART Pin Type
#define UART0TX                 UART0TX
#define UART0RX                 UART0RX
#define UART1TX                 UART1TX
#define UART1RX                 UART1RX
#define UART1RI                 UART1RI
#define UART1CTS                UART1CTS
#define UART1DCD                UART1DCD
#define UART1DSR                UART1DSR
#define UART1DTR                UART1DTR
#define UART1RTS                UART1RTS
#define UART2TX                 UART2TX
#define UART2RX                 UART2RX
#define UART3TX                 UART3TX
#define UART3RX                 UART3RX
#define UART4TX                 UART4TX
#define UART4RX                 UART4RX

//! I2C Pin Type
#define I2C0SDA                 I2C0SDA
#define I2C0SCL                 I2C0SCL
#define I2C1SDA                 I2C1SDA
#define I2C1SCL                 I2C1SCL
#define I2C2SDA                 I2C2SDA
#define I2C2SCL                 I2C2SCL

//! ADC Pin Type
#define AD0                     AD0
#define AD1                     AD1
#define AD2                     AD2
#define AD3                     AD3
#define AD4                     AD4
#define AD5                     AD5
#define AD6                     AD6
#define AD7                     AD7

//! \todo How to deal timer capture pin
//! Timer Pin Type
#define TIMCCP0                 TIMCCP0
#define TIMCCP1                 TIMCCP1
#define TIM_MAT0                TIM_MAT0
#define TIM_MAT1                TIM_MAT1
#define TIM_MAT2                TIM_MAT2
#define TIM_MAT3                TIM_MAT3

//! SPI Pin Type
#define SPI0CLK                 SPI0CLK
#define SPI0MOSI                SPI0MOSI
#define SPI0MISO                SPI0MISO
#define SPI0CS                  SPI0CS
#define SPI1CLK                 SPI1CLK
#define SPI1MOSI                SPI1MOSI
#define SPI1MISO                SPI1MISO
#define SPI1CS                  SPI1CS

//! DAC Pin Type
#define DACOUT1                 DACOUT1

//! CAN Pin Type
#define CAN1RX                  CAN1RX
#define CAN1TX                  CAN1TX
#define CAN2RX                  CAN2RX
#define CAN2TX                  CAN2TX

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xGPIO_Exported_APIs xGPIO API
//! \brief      xGPIO API Reference.
//!
//! \section    xGPIO_Exported_APIs_Port CoX Port Details
//!
//! |       xGPIO API                 |       CoX      |          LPC17xx       |
//! |---------------------------------|----------------|------------------------|
//! |  \ref xGPIODirModeSet           |    Mandatory   |            Y           |
//! |  \ref xGPIOSPinToPeripheralId   |    Mandatory   |            Y           |
//! |  \ref xGPIOSPinToPort           |    Mandatory   |            Y           |
//! |  \ref xGPIOSPinToPin            |    Mandatory   |            Y           |
//! |  \ref xGPIOSPinDirModeSet       |    Mandatory   |            Y           |
//! |  \ref xGPIODirModeGet           |    Mandatory   |            Y           |
//! |  \ref xGPIOPinIntCallbackInit   |    Mandatory   |            Y           |
//! |  \ref xGPIOPinIntEnable         |    Mandatory   |            Y           |
//! |  \ref xGPIOSPinIntEnable        |    Mandatory   |            Y           |
//! |  \ref xGPIOPinIntDisable        |    Mandatory   |            Y           |
//! |  \ref xGPIOSPinIntDisable       |    Mandatory   |            Y           |
//! |  \ref xGPIOPinIntStatus         |    Mandatory   |            Y           |
//! |  \ref xGPIOPinIntClear          |    Mandatory   |            Y           |
//! |  \ref xGPIOSPinIntClear         |    Mandatory   |            Y           |
//! |  \ref xGPIOPinRead              |    Mandatory   |            Y           |
//! |  \ref xGPIOSPinRead             |    Mandatory   |            Y           |
//! |  \ref xGPIOPinWrite             |    Mandatory   |            Y           |
//! |  \ref xGPIOSPinWrite            |    Mandatory   |            Y           |
//! |  \ref xGPIOPinConfigure         |    Mandatory   |            Y           |
//! |  \ref xGPIOSPinTypeGPIOInput    |    Mandatory   |            Y           |
//! |  \ref xGPIOSPinTypeGPIOOutput   |    Mandatory   |            Y           |
//! |  \ref xGPIOSPinTypeGPIOOutputOD |  Non-Mandatory |            Y           |
//! |  \ref xGPIOSPinTypeGPIOOutputQB |  Non-Mandatory |            Y           |
//! |  \ref xSPinTypeADC              |    Mandatory   |            Y           |
//! |  \ref xSPinTypeDAC              |    Mandatory   |            Y           |
//! |  \ref xSPinTypeCAN              |    Mandatory   |            Y           |
//! |  \ref xSPinTypeI2C              |    Mandatory   |            Y           |
//! |  \ref xSPinTypePWM              |  Non-Mandatory |            Y           |
//! |  \ref xSPinTypeSPI              |    Mandatory   |            Y           |
//! |  \ref xSPinTypeTimer            |    Mandatory   |            Y           |
//! |  \ref xSPinTypeUART             |    Mandatory   |            Y           |
//! |  \ref xSPinTypeACMP             |    Mandatory   |            N           |
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief  Set the direction and mode of the specified pin(s).
//!         This function will set the specified pin(s) on the selected GPIO
//!         port as either an input or output under software control, or it
//!         will set the pin to be under hardware control.
//!
//! \param  [in] ulPort is the base address of the GPIO port, this value can
//!              be one of the following value:
//!              - \ref GPIOA_BASE
//!              - \ref GPIOB_BASE
//!              - ...
//!              More Information, please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//!              elemnt can be one of the following value:
//!              - \ref GPIO_PIN0
//!              - \ref GPIO_PIN1
//!              - \ref ...
//!              More Information, please refer to \ref xGPIO_General_Pin_IDs.
//!
//! \param  [in] ulPinIO is the pin direction and/or mode.
//!              This parameter can be one of the following value:
//!              Where \ref xGPIO_DIR_MODE_IN specifies that the pin will be
//!              programmed a software controlled input, \ref xGPIO_DIR_MODE_OUT
//!              specifies that the pin will be programmed as a software
//!              controlled output, and \ref xGPIO_DIR_MODE_HW specifies that
//!              the pin will be placed under hardware control.
//!
//! \return None.
//!
//! \note   \ref xGPIOPadConfigSet() must also be used to configure the corresponding
//!         pad(s) in order for them to propagate the signal to/from the GPIO.
//
//*****************************************************************************
extern void xGPIODirModeSet(unsigned long ulPort, unsigned long ulPins,
                            unsigned long ulPinIO);

//*****************************************************************************
//
//! \brief  Get the GPIO port from a Pin.
//!
//! \param  [in] eShortPin is the base address of the GPIO port
//!
//! \return GPIO port code, which is one of the following value:
//!             - \ref xSYSCTL_PERIPH_GPIOC
//!             - \ref xSYSCTL_PERIPH_I2C1
//!             -      ...
//!             - \ref xSYSCTL_PERIPH_TIMER2
//!             - \ref xSYSCTL_PERIPH_TIMER3
//!
//!         which can be used in those functions:
//!             - \ref xSysCtlPeripheralEnable
//!             - \ref xSysCtlPeripheralDisable
//!             - \ref xSysCtlPeripheralReset
//
//*****************************************************************************
#define xGPIOSPinToPeripheralId(eShortPin)                                    \
        GPIOPinToPeripheralId(G##eShortPin)

//*****************************************************************************
//
//! \brief  Get the GPIO port from a short Pin.
//!
//! \param  [in] eShortPin is the base address of the GPIO port
//!
//! \return GPIO port address which is used by GPIO API.
//
//*****************************************************************************
#define xGPIOSPinToPort(eShortPin)                                            \
        GPIOPinToPort(G##eShortPin)


//*****************************************************************************
//
//! \brief  Get the GPIO port and Pin number from a short Pin.
//!
//! \param  [in] eShortPin is the base address of the GPIO port
//!
//! \return GPIO port address which is used by GPIO API.
//
//*****************************************************************************
#define xGPIOSPinToPortPin(eShortPin)                                         \
        GPIOSPinToPortPin(eShortPin)

//*****************************************************************************
//
//! \brief  Get the GPIO pin number from a short Pin.
//!
//! \param  [in] eShortPin is the base address of the GPIO port
//!
//! \return GPIO pin number which is used by GPIO API.
//
//*****************************************************************************
#define xGPIOSPinToPin(eShortPin)                                             \
        GPIOPinToPin(G##eShortPin)

//*****************************************************************************
//
//! \brief  Set the direction and mode of the specified pin(s).
//!         This function will set the specified pin(s) on the selected GPIO port
//!         as either an input or output under software control, or it will set
//!         the pin to be under hardware control.
//!
//! \param  [in] eShortPin Specified port and pin.
//!              The pin is specified by eShortPin, which can only be one pin.
//!
//! \param  [in] ulPinIO is the pin direction and/or mode.
//!              This parameter can be one of the following value:
//!              Where \ref xGPIO_DIR_MODE_IN specifies that the pin will be
//!              programmed a software controlled input, \ref xGPIO_DIR_MODE_OUT
//!              specifies that the pin will be programmed as a software
//!              controlled output, and \ref xGPIO_DIR_MODE_HW specifies that
//!              the pin will be placed under hardware control.
//!
//! \return None.
//!
//! \note   \ref xGPIOPadConfigSet() must also be used to configure the corresponding
//!         pad(s) in order for them to propagate the signal to/from the GPIO.
//
//*****************************************************************************
#define xGPIOSPinDirModeSet(eShortPin, ulPinIO)                               \
        xGPIODirModeSet(G##eShortPin, ulPinIO)

//*****************************************************************************
//
//! \brief  Get the direction and mode of a pin.
//!         This function gets the direction and control mode for a specified
//!         pin on the selected GPIO port.  The pin can be configured as either
//!         an input or output under software control, or it can be under
//!         hardware control. The type of control and direction are returned
//!         as an enumerated data type.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPin is the bit-packed representation of the pin.
//!
//! \return Returns one of the enumerated data types
//!         - \ref xGPIO_DIR_MODE_IN
//!         - \ref xGPIO_DIR_MODE_OUT
//!         - \ref xGPIO_DIR_MODE_HW
//!         - \ref xGPIO_DIR_MODE_QB
//!         - \ref xGPIO_DIR_MODE_OD
//
//*****************************************************************************
extern unsigned long xGPIODirModeGet(unsigned long ulPort, unsigned long ulPin);

//*****************************************************************************
//
//! \brief  Register user's gpio interrupt function.
//!
//! \param  [in] ulPort is the base address of the GPIO port.
//! \param  [in] ulPin is the bit-packed representation of the pin.
//! \param  [in] pfnCallback is the callback function.
//!
//! \return None.
//
//*****************************************************************************
extern void xGPIOPinIntCallbackInit(unsigned long ulPort, unsigned long ulPin,
                                   xtEventCallback xtPortCallback);

//*****************************************************************************
//
//! \brief  Set the interrupt type and Enable interrupt for the specified pin(s).
//!         This function sets up the various interrupt trigger mechanisms for the
//!         specified pin(s) on the selected GPIO port.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//! \param  [in] ulIntType specifies the type of interrupt trigger mechanism.
//!
//! \return None.
//!
//! \note   In order to avoid any spurious interrupts, the user must ensure that
//!         the GPIO inputs remain stable for the duration of this function.
//
//*****************************************************************************
extern void xGPIOPinIntEnable(unsigned long ulPort, unsigned long ulPins,
        unsigned long ulIntType);

//*****************************************************************************
//
//! \brief  Set the interrupt type and Enable interrupt for the specified pin(s).
//!
//! \param  [in] eShortPin Specified port and pin.
//! \param  [in] ulIntType specifies the type of interrupt trigger mechanism.
//!
//! \return None.
//!
//! \note   In order to avoid any spurious interrupts, the user must ensure that
//!         the GPIO inputs remain stable for the duration of this function.
//
//*****************************************************************************
#define xGPIOSPinIntEnable(eShortPin, ulIntType)                              \
        xGPIOPinIntEnable(G##eShortPin, ulIntType)

//*****************************************************************************
//
//! \brief  Disables interrupts for the specified pin(s).
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//!
//! \return None.
//
//*****************************************************************************
extern void xGPIOPinIntDisable(unsigned long ulPort, unsigned long ulPins);

//*****************************************************************************
//
//! \brief  Disables interrupts for the specified pin.
//!
//! \param  [in] eShortPin Specified port and pin.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinIntDisable(eShortPin)                                        \
        xGPIOPinIntDisable(G##eShortPin)

//*****************************************************************************
//
//! \brief  Get interrupt status for the specified GPIO port.
//!
//! \param  [in] ulPort is the base address of the GPIO port.
//!
//! \return Returns a bit-packed byte, where each bit that is set identifie
//!         an active masked or raw interrupt, and where bit 0 of the byte
//!         represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and
//!         so on.
//
//*****************************************************************************
#define xGPIOPinIntStatus(ulPort)

//*****************************************************************************
//
//! \brief  Clear the interrupt for the specified pin(s).
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//!
//! \return None.
//!
//! \note   Because there is a write buffer in the Cortex-M0 processor, it may
//!         take several clock cycles before the interrupt source is actually
//!         cleared. Therefore, it is recommended that the interrupt source
//!         be cleared early in the interrupt handler (as opposed to the very
//!         last action) to avoid returning from the interrupt handler before
//!         the interrupt source i actually cleared.  Failure to do so may
//!         result in the interrupt handler being immediately reentered (because
//!         the interrupt controller still see the interrupt source asserted).
//
//*****************************************************************************
extern void xGPIOPinIntClear(unsigned long ulPort, unsigned long ulPins);

//*****************************************************************************
//
//! \brief  Clear the interrupt for the specified pin.
//!
//! \param  [in] eShortPin Specified port and pin.
//!
//! \return None.
//!
//! \note   Because there is a write buffer in the Cortex-M0 processor, it may
//!         take several clock cycles before the interrupt source is actually
//!         cleared. Therefore, it is recommended that the interrupt source
//!         be cleared early in the interrupt handler (as opposed to the very
//!         last action) to avoid returning from the interrupt handler before
//!         the interrupt source i actually cleared.  Failure to do so may
//!         result in the interrupt handler being immediately reentered (because
//!         the interrupt controller still see the interrupt source asserted).
//
//*****************************************************************************
#define xGPIOSPinIntClear(eShortPin)                                          \
        xGPIOPinIntClear(G##eShortPin)

//*****************************************************************************
//
//! \brief  Reads the values present of the specified pin(s).
//!         The values at the specified pin(s) are read, as specified by \e ucPins.
//!         Values are returned for both input and output pin(s), and the value
//!         for pin(s) that are not specified by \e ucPins are set to 0.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//!
//! \return Returns a bit-packed byte, where each bit that is set identifie
//!         an active masked or raw interrupt, and where bit 0 of the byte
//!         represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and
//!         so on.
//
//*****************************************************************************
extern unsigned long xGPIOPinRead(unsigned long ulPort, unsigned long ulPins);

//*****************************************************************************
//
//! \brief  Reads the values present of the specified Port.
//!
//! \param  [in] ulPort is the base address of the GPIO port.
//!
//! \return Returns a bit-packed byte providing the state of the specified Port
//
//*****************************************************************************
#define xGPIOPortRead(ulPort)                                                 \
        GPIOPortRead(ulPort)

//*****************************************************************************
//
//! \brief Reads the values present of the specified pin.
//!        The values at the specified pin are read, as specified by \e eShortPin.
//!        Values are returned for both input and output pin(s), and the value
//!        for pin(s) that are not specified by \e eShortPin are set to 0.
//!
//! \param eShortPin Specified port and pin.
//!
//! \return Returns the value of specified port and pin.
//
//*****************************************************************************
#define xGPIOSPinRead(eShortPin)                                              \
        GPIOPinRead(G##eShortPin)

//*****************************************************************************
//
//! \brief Write a value to the specified pin(s).
//!        Write the corresponding bit values to the output pin(s) specified by
//!        \e ucPins.  Writing to a pin configured as an input pin has no effect.
//!
//! \param [in] ulPort is the base address of the GPIO port
//! \param [in] ulPins is the bit-packed representation of the pin(s).
//! \param [in] ucVal is the value to write to the pin(s), 0 or 1.
//!
//! \return None.
//
//*****************************************************************************
extern void xGPIOPinWrite(unsigned long ulPort, unsigned long ulPins,
        unsigned char ucVal);

//*****************************************************************************
//
//! \brief  Writes a value to the specified Port.
//!         Writes the corresponding bit values to the output Port
//!
//! \param  [in] ulPort is the base address of the GPIO port.
//! \param  [in] ucVal is the value to write to the Port.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOPortWrite(ulPort, ulVal)                                         \
        GPIOPortWrite(ulPort, ulVal)

//*****************************************************************************
//
//! \brief  Write a value to the specified pin.
//!         Write the corresponding bit values to the output pin specified by
//!         \e eShortPin. Writing to a pin configured as an input pin has no effect.
//!
//! \param  [in] eShortPin Specified port and pin.
//! \param  [in] ucVal is the value to write to the pin(s), 0 or 1.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinWrite(eShortPin, ulVal)                                      \
        GPIOPinWrite(G##eShortPin, ulVal)

//*****************************************************************************
//
//! \brief  Configure the alternate function of a GPIO pin.
//!         This function configures the pin mux that selects the peripheral
//!         function associated with a particular GPIO pin. Only one peripheral
//!         function at a time can be associated with a GPIO pin, and each
//!         peripheral function should only be associated with a single GPIO pin
//!         at a time (despite the fact that many of them can be associated with
//!         more than one GPIO pin).
//!
//! \param  [in] eShortPin Specified port and pin.
//! \param  [in] ulPinConfig is the pin configuration value, specified as only
//!              one of the \b GPIO_P??_??? values.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOPinConfigure(eShortPin, ulPinConfig)                             \
        GPIOPinFunCfg(G##eShortPin, ulPinConfig)

//*****************************************************************************
//
//! \brief  Turn a pin to a GPIO Input pin.
//!         This function configures a pin for use as an GPIO Input pin device
//!         and turns the pin into a GPIO input pin.
//!
//! \param  [in] eShortPin Specified port and pin.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinTypeGPIOInput(eShortPin)                                     \
        do                                                                    \
        {                                                                     \
            GPIOPinFunCfg(G##eShortPin, GPIO_##eShortPin##_##eShortPin);      \
            GPIOPinModeCfg(G##eShortPin, PIN_MODE_INPUT);                     \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief  Turn a pin to a GPIO Output(push-pull) pin.
//!         This function configures a pin for use as an GPIO Output pin device
//!         and turns the pin into a GPIO Output pin.
//!
//! \param  [in] eShortPin Specified port and pin.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinTypeGPIOOutput(eShortPin)                                    \
        do                                                                    \
        {                                                                     \
            GPIOPinFunCfg(G##eShortPin, GPIO_##eShortPin##_##eShortPin);      \
            GPIOPinModeCfg(G##eShortPin, PIN_MODE_OUTPUT);                    \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief  Turn a pin to a GPIO Output(open drain) pin.
//!         This function configures a pin for use as an GPIO Output pin device
//!         and turns the pin into a GPIO Output(open drain) pin.
//!
//! \param  [in] eShortPin is the GPIO short pin name such as PA0.
//!
//! \return None.
//
//*****************************************************************************
#define xGPIOSPinTypeGPIOOutputOD(eShortPin)                                  \
        do                                                                    \
        {                                                                     \
            GPIOPinFunCfg(G##eShortPin, GPIO_##eShortPin##_eShortPin);        \
            GPIOPinModeCfg(G##eShortPin, PIN_MODE_OD_EN);                     \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief  Turn a pin to a GPIO ADC input pin.
//!         This function configures a pin for use as an ADC function device
//!         and turns the pin into a GPIO ADC input pin.
//!
//! \param  [in] ePeripheralPin is the GPIO Peripheral name such as ADC0.
//!
//! \param  [in] eShortPin is the GPIO short pin name such as PA0.
//!
//! \return None.
//!
//! \note
//!         Table shows what the ePeripheralPin and eShortPin should be, only
//!         the argument which are in the same line can be combined.
//!         For eaxmple(TI):
//! \note
//!             xSPinTypeADC(ADC0, PE7)  --> Correct
//!             xSPinTypeADC(ADC1, PE6)  --> Correct
//! \note
//!             xSPinTypeADC(ADC0, PE6)  --> Error
//!             xSPinTypeADC(ADC0, PE5)  --> Error
//!
//!     +-----------------+-------------------------+--------------------------+
//!     |  manufacturer   | ePeripheralPin          | eShortPin                |
//!     |-----------------|-------------------------|--------------------------|
//!     |  CoX            | This parameter is a     | This parameter is a      |
//!     |                 | mandatory.The mandatory | mandatory. the mandatory |
//!     |                 | is the format of        | is the format of         |
//!     |                 | Variable naming.So it   | Variable naming.So it    |
//!     |                 | should be: ADCn         | should be: PXn           |
//!     |                 | n indicate the pin      | XX indicate the GPIO     |
//!     |                 | number such as          | PORT,Such as             |
//!     |                 | 0 1 2 3 ....            | A B C D E ...            |
//!     |                 |                         | n indicate the pin       |
//!     |                 |                         | number such as           |
//!     |                 |                         | 0 1 2 3 ....             |
//!     |-----------------|-------------------------|--------------------------|
//!     |     LPC17xx     |     ADC0                |         PA23             |
//!     |                 |     ADC1                |         PA24             |
//!     |                 |     ADC2                |         PA25             |
//!     |                 |     ADC3                |         PA26             |
//!     |                 |     ADC4                |         PB30             |
//!     |                 |     ADC5                |         PB31             |
//!     |                 |     ADC6                |         PA3              |
//!     |                 |     ADC7                |         PA2              |
//!     +-----------------+-------------------------+--------------------------+
//!
//!
//
//*****************************************************************************
#define xSPinTypeADC(ePeripheralPin, eShortPin)                               \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)

//*****************************************************************************
//
//! \brief  Turn a pin to a GPIO CAN input or output pin.
//!         This function configures a pin for use as a CAN function and turns
//!         the pin into a GPIO CAN input or output pin.
//!
//! \param  [in] ePeripheralPin is the GPIO Peripheral name such as CAN0RX.
//!
//! \param  [in] eShortPin is the GPIO short pin name such as PA0.
//!
//! \return None.
//!
//!         Table shows what the ePeripheralPin and eShortPin should be, only the
//!         argument which are in the same line can be combined.
//!
//!     +--------------------+-------------------------+--------------------------+
//!     |    manufacturer    | ePeripheralPin          | eShortPin                |
//!     |--------------------|-------------------------|--------------------------|
//!     |    CoX             | This parameter is a     | This parameter is a      |
//!     |                    | mandatory.The mandatory | mandatory. the mandatory |
//!     |                    | is the format of        | is the format of         |
//!     |                    | Variable naming.So it   | Variable naming.So it    |
//!     |                    | should be: CANnRX       | should be: PXn           |
//!     |                    | or CANnTX               | XX indicate the GPIO     |
//!     |                    | n indicate the pin      | PORT,Such as             |
//!     |                    | number such as          | A B C D E ...            |
//!     |                    | 0 1 2 3 ....            | n indicate the pin       |
//!     |                    |                         | number such as           |
//!     |                    |                         | 0 1 2 3 ....             |
//!     |--------------------|-------------------------|--------------------------|
//!     |       LPC17xx      |     CAN1RX              |     PA0   PA21           |
//!     |                    |     CAN1TX              |     PA1   PA22           |
//!     |                    |     CAN2RX              |     PA4   PC7            |
//!     |                    |     CAN2TX              |     PA5   PC8            |
//!     +--------------------+-------------------------+--------------------------+
//!
//!
//
//*****************************************************************************
#define xSPinTypeCAN(ePeripheralPin, eShortPin)                               \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)

//*****************************************************************************
//
//! \brief  Turn a pin to a GPIO I2C input or output pin.
//!         This function configures a pin for use as an I2C function device and
//!         turns the pin into a GPIO I2C input or output pin.
//!
//! \param  [in] ePeripheralPin is the GPIO Peripheral name such as I2C0SDA.
//!
//! \param  [in] eShortPin is the GPIO short pin name such as PA0.
//!
//! \return None.
//!
//!     +--------------------+-------------------------+--------------------------+
//!     |    manufacturer    | ePeripheralPin          | eShortPin                |
//!     |--------------------|-------------------------|--------------------------|
//!     |    CoX             | This parameter is a     | This parameter is a      |
//!     |                    | mandatory.The mandatory | mandatory. the mandatory |
//!     |                    | is the format of        | is the format of         |
//!     |                    | Variable naming.So it   | Variable naming.So it    |
//!     |                    | should be: I2CnSCK      | should be: PXn           |
//!     |                    | or I2CnSDA              | XX indicate the GPIO     |
//!     |                    | n indicate the pin      | PORT,Such as             |
//!     |                    | number such as          | A B C D E ...            |
//!     |                    | 0 1 2 3 ....            | n indicate the pin       |
//!     |                    |                         | number such as           |
//!     |                    |                         | 0 1 2 3 ....             |
//!     |--------------------|-------------------------|--------------------------|
//!     |       LPC17xx      |     I2C0SDA             |     PA27                 |
//!     |                    |     I2C0SCK             |     PA28                 |
//!     |                    |     I2C1SDA             |     PA0  PA19            |
//!     |                    |     I2C1SCK             |     PA1  PA20            |
//!     |                    |     I2C2SDA             |     PA10                 |
//!     |                    |     I2C2SCK             |     PA11                 |
//!     |--------------------|-------------------------|--------------------------|
//!
//!
//
//*****************************************************************************
 #define xSPinTypeI2C(ePeripheralPin, eShortPin)                              \
         GPIOSPinConfigure(ePeripheralPin, eShortPin)

//*****************************************************************************
//
//! \brief  Turn a pin to pwm function pin.
//!         This function configures a pin for use as a PWM function and turns
//!         the pin into a PWM function pin.
//!
//! \param  [in] ePeripheralPin is the PWM Peripheral channel such as PWM0.
//!
//! \param  [in] eShortPin is the GPIO short pin name such as PA0.
//!
//! \return None.
//!
//!     +--------------------+-------------------------+--------------------------+
//!     |    manufacturer    | ePeripheralPin          | eShortPin                |
//!     |--------------------|-------------------------|--------------------------|
//!     |    CoX             | This parameter is a     | This parameter is a      |
//!     |                    | mandatory.The mandatory | mandatory. the mandatory |
//!     |                    | is the format of        | is the format of         |
//!     |                    | Variable naming.So it   | Variable naming.So it    |
//!     |                    | should be: SPInCLK,     | should be: PXn           |
//!     |                    | SPInMISO, SPInMOSI,     | XX indicate the GPIO     |
//!     |                    | or SPInCS,              | PORT,Such as             |
//!     |                    | n indicate the pin      | A B C D E ...            |
//!     |                    | number such as          | n indicate the pin       |
//!     |                    | 0 1 2 3 ....            | number such as           |
//!     |                    |                         | 0 1 2 3 ....             |
//!     |--------------------|-------------------------|--------------------------|
//!     |                    |          PWM1           |     PB18/PC0             |
//!     |                    |          PWM2           |     PB20/PD25/PC1        |
//!     |     LPC17xx        |          PWM3           |     PB21/PC2/PD26        |
//!     |                    |          PWM4           |     PB23/PC3             |
//!     |                    |          PWM5           |     PB24/PC4             |
//!     |                    |          PWM6           |     PB26/PC5             |
//!     +--------------------+-------------------------+--------------------------+
//!
//
//*****************************************************************************
#define xSPinTypePWM(ePeripheralPin, eShortPin)                               \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)

//*****************************************************************************
//
//! \brief  Turn a pin to a GPIO SPI input or output pin.
//!         This function configures a pin for use as a SPI function and turns
//!         the pin into a GPIO SPI input or output pin.
//!
//! \param  [in] ePeripheralPin is the GPIO Peripheral name such as I2C0SDA.
//!
//! \param  [in] eShortPin is the GPIO short pin name such as PA0.
//!
//! \return None.
//!
//! \note
//!         Table shows what the ePeripheralPin and eShortPin should be, only
//!         the argument which are in the same line can be combined.
//!         For eaxmple(TI):
//!
//!             xSPinTypeSPI(SPI0CLK, PA2)  --> Correct
//!             xSPinTypeSPI(SPI0MOSI, PA5) --> Correct
//!
//!             xSPinTypeSPI(SPI0CLK, PA5)  --> Error
//!             xSPinTypeSPI(SPI0CLK, PA4)  --> Error
//!
//!     +--------------------+-------------------------+--------------------------+
//!     |    manufacturer    | ePeripheralPin          | eShortPin                |
//!     |--------------------|-------------------------|--------------------------|
//!     |    CoX             | This parameter is a     | This parameter is a      |
//!     |                    | mandatory.The mandatory | mandatory. the mandatory |
//!     |                    | is the format of        | is the format of         |
//!     |                    | Variable naming.So it   | Variable naming.So it    |
//!     |                    | should be: SPInCLK,     | should be: PXn           |
//!     |                    | SPInMISO, SPInMOSI,     | XX indicate the GPIO     |
//!     |                    | or SPInCS,              | PORT,Such as             |
//!     |                    | n indicate the pin      | A B C D E ...            |
//!     |                    | number such as          | n indicate the pin       |
//!     |                    | 0 1 2 3 ....            | number such as           |
//!     |                    |                         | 0 1 2 3 ....             |
//!     |--------------------|-------------------------|--------------------------|
//!     |       LPC17xx      |     SPI0CLK             |     PA15                 |
//!     |                    |     SPI0CS              |     PA16                 |
//!     |                    |     SPI0MISO            |     PA17                 |
//!     |                    |     SPI0MOSI            |     PA18                 |
//!     +--------------------+-------------------------+--------------------------+
//!
//
//*****************************************************************************
#define xSPinTypeSPI(ePeripheralPin, eShortPin)                               \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)

//*****************************************************************************
//
//! \brief  Turn a pin to a GPIO Timer input or output pin.
//!         This function configures a pin for use as a Timer function and turns
//!         the pin into a GPIO Timer input or output pin.
//!
//! \param  [in] ePeripheralPin is the GPIO Peripheral name such as I2C0SDA.
//!
//! \param  [in] eShortPin is the GPIO short pin name such as PA0.
//!
//! \return None.
//!
//! \note
//!         Table shows what the ePeripheralPin and eShortPin should be, only the
//!         argument which are in the same line can be combined.
//!         For eaxmple(TI):
//!
//!             xSPinTypeTimer(TIMCCP0, PD3)  --> Correct
//!             xSPinTypeTimer(TIMCCP0, PJ7)  --> Correct
//!
//!             xSPinTypeTimer(TIMCCP0, PC5)  --> Error
//!             xSPinTypeTimer(TIMCCP0, PB6)  --> Error
//!
//!     +--------------------+-------------------------+--------------------------+
//!     |    manufacturer    | ePeripheralPin          | eShortPin                |
//!     |--------------------|-------------------------|--------------------------|
//!     |    CoX             | This parameter is a     | This parameter is a      |
//!     |                    | mandatory.The mandatory | mandatory. the mandatory |
//!     |                    | is the format of        | is the format of         |
//!     |                    | Variable naming.So it   | Variable naming.So it    |
//!     |                    | should be: TIMCCPn,     | should be: PXn           |
//!     |                    | n indicate the pin      | XX indicate the GPIO     |
//!     |                    | number such as          | PORT,Such as             |
//!     |                    | 0 1 2 3 ....            | A B C D E ...            |
//!     |                    |                         | n indicate the pin       |
//!     |                    |                         | number such as           |
//!     |                    |                         | 0 1 2 3 ....             |
//!     |--------------------|-------------------------|--------------------------|
//!     |       LPC17xx      |                         |                          |
//!     |--------------------|-------------------------|--------------------------|
//!
//! \todo Finish Cox Timer Pin map
//
//*****************************************************************************
#define xSPinTypeTimer(ePeripheralPin, eShortPin)                             \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)

//*****************************************************************************
//
//! \brief  Turn a pin to a GPIO UART input or output pin.
//!         This function configures a pin for use as a UART function and turns
//!         the pin into a GPIO UART input or output pin.
//!
//! \param  [in] ePeripheralPin is the GPIO Peripheral name such as I2C0SDA.
//!
//! \param  [in] eShortPin is the GPIO short pin name such as PA0.
//!
//! \return None.
//!
//! \note
//!         Table shows what the ePeripheralPin and eShortPin should be, only the
//!         argument which are in the same line can be combined.
//!         For eaxmple(TI):
//!
//!             xSPinTypeUART(UART0RX, PA0)  --> Correct
//!             xSPinTypeUART(UART0TX, PA1)  --> Correct
//!
//!             xSPinTypeUART(UART0RX, PE6)  --> Error
//!             xSPinTypeUART(UART0RX, PA1)  --> Error
//!
//!     +--------------------+-------------------------+--------------------------+
//!     |    manufacturer    | ePeripheralPin          | eShortPin                |
//!     |--------------------|-------------------------|--------------------------|
//!     |    CoX             | This parameter is a     | This parameter is a      |
//!     |                    | mandatory.The mandatory | mandatory. the mandatory |
//!     |                    | is the format of        | is the format of         |
//!     |                    | Variable naming.So it   | Variable naming.So it    |
//!     |                    | should be: UARTnRX,     | should be: PXn           |
//!     |                    | UARTnTX, UARTnCTS,      | XX indicate the GPIO     |
//!     |                    | ......,                 | PORT,Such as             |
//!     |                    | n indicate the pin      | A B C D E ...            |
//!     |                    | number such as          | n indicate the pin       |
//!     |                    | 0 1 2 3 ....            | number such as           |
//!     |                    |                         | 0 1 2 3 ....             |
//!     |--------------------|-------------------------|--------------------------|
//!     |                    |     UART0TX             |     PA2                  |
//!     |                    |     UART0RX             |     PA3                  |
//!     |                    | ------------------------- ------------------------ |
//!     |                    |     UART1TX             |     PA15  PC0            |
//!     |                    |     UART1RX             |     PA16  PC1            |
//!     |                    |     UART1CTS            |     PA17  PC2            |
//!     |                    |     UART1DCD            |     PA18  PC3            |
//!     |                    |     UART1DSR            |     PA19  PC4            |
//!     |      LPC17xx       |     UART1DTR            |     PA20  PC5            |
//!     |                    |     UART1RI             |     PA21  PC6            |
//!     |                    |     UART1RTS            |     PA22  PC7            |
//!     |                    | ------------------------- ------------------------ |
//!     |                    |     UART2TX             |     PA10  PC8            |
//!     |                    |     UART2RX             |     PA11  PC9            |
//!     |                    | ------------------------- ------------------------ |
//!     |                    |     UART3TX             |     PA0   PA25  PE28     |
//!     |                    |     UART3RX             |     PA1   PA26  PE29     |
//!     |-------------------------------------------------------------------------|
//!
//
//*****************************************************************************
#define xSPinTypeUART(ePeripheralPin, eShortPin)                              \
        GPIOSPinConfigure(ePeripheralPin, eShortPin)

//*****************************************************************************
//
//! \brief  Turn a pin to a GPIO DAC output pin.
//!         This function configures a pin for use as an GPIO DAC function and
//!         turns the pin into a GPIO DAC output pin.
//!
//! \param  ePeripheralPin is the GPIO Peripheral name such as I2C0SDA.
//!
//! \param eShortPin is the GPIO short pin name such as PA0.
//!
//! \return None.
//!
//! \note
//!     +--------------------+-------------------------+--------------------------+
//!     |    manufacturer    | ePeripheralPin          | eShortPin                |
//!     |--------------------|-------------------------|--------------------------|
//!     |    CoX             | This parameter is a     | This parameter is a      |
//!     |                    | mandatory.The mandatory | mandatory. the mandatory |
//!     |                    | is the format of        | is the format of         |
//!     |                    | Variable naming.So it   | Variable naming.So it    |
//!     |                    | should be: DACOUTn,     | should be: PXn           |
//!     |                    |                         | X  indicate the GPIO     |
//!     |                    | n x indicate the pin    | PORT,Such as             |
//!     |                    | number such as          | A B C D E ...            |
//!     |                    | 0 1 2 3 ....            | n indicate the pin       |
//!     |                    |                         | number such as           |
//!     |                    |                         | 0 1 2 3 ....             |
//!     |--------------------|-------------------------|--------------------------|
//!     |       LPC17xx      |     DACOUT1             |     PA26                 |
//!     |--------------------|-------------------------|--------------------------|
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeDAC(ePeripheralPin, eShortPin)                               \
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
//! \addtogroup GPIO
//! @{
//
//*****************************************************************************

//! Auxiliary function.
#define GPIOSPinConfigure(ePeripheralPin, eShortPin)                          \
        GPIOPinFunCfg(G##eShortPin, GPIO_##eShortPin##_##ePeripheralPin)

//*****************************************************************************
//
//! \addtogroup  LPC17xx_GPIO_General_Pin_IDs  LPC17xx GPIO General Pin ID
//! \brief       The following values define the bit field for the ucPins argument
//!              to several of the APIs.
//! @{
//
//*****************************************************************************

//! GPIO Pin 0
#define GPIO_PIN_0              BIT_32_0

//! GPIO Pin 1
#define GPIO_PIN_1              BIT_32_1

//! GPIO Pin 2
#define GPIO_PIN_2              BIT_32_2

//! GPIO Pin 3
#define GPIO_PIN_3              BIT_32_3

//! GPIO Pin 4
#define GPIO_PIN_4              BIT_32_4

//! GPIO Pin 5
#define GPIO_PIN_5              BIT_32_5

//! GPIO Pin 6
#define GPIO_PIN_6              BIT_32_6

//! GPIO Pin 7
#define GPIO_PIN_7              BIT_32_7

//! GPIO Pin 8
#define GPIO_PIN_8              BIT_32_8

//! GPIO Pin 9
#define GPIO_PIN_9              BIT_32_9

//! GPIO Pin 10
#define GPIO_PIN_10             BIT_32_10

//! GPIO Pin 11
#define GPIO_PIN_11             BIT_32_11

//! GPIO Pin 12
#define GPIO_PIN_12             BIT_32_12

//! GPIO Pin 13
#define GPIO_PIN_13             BIT_32_13

//! GPIO Pin 14
#define GPIO_PIN_14             BIT_32_14

//! GPIO Pin 15
#define GPIO_PIN_15             BIT_32_15

//! GPIO Pin 16
#define GPIO_PIN_16             BIT_32_16

//! GPIO Pin 17
#define GPIO_PIN_17             BIT_32_17

//! GPIO Pin 18
#define GPIO_PIN_18             BIT_32_18

//! GPIO Pin 19
#define GPIO_PIN_19             BIT_32_19

//! GPIO Pin 20
#define GPIO_PIN_20             BIT_32_20

//! GPIO Pin 21
#define GPIO_PIN_21             BIT_32_21

//! GPIO Pin 22
#define GPIO_PIN_22             BIT_32_22

//! GPIO Pin 23
#define GPIO_PIN_23             BIT_32_23

//! GPIO Pin 24
#define GPIO_PIN_24             BIT_32_24

//! GPIO Pin 25
#define GPIO_PIN_25             BIT_32_25

//! GPIO Pin 26
#define GPIO_PIN_26             BIT_32_26

//! GPIO Pin 27
#define GPIO_PIN_27             BIT_32_27

//! GPIO Pin 28
#define GPIO_PIN_28             BIT_32_28

//! GPIO Pin 29
#define GPIO_PIN_29             BIT_32_29

//! GPIO Pin 30
#define GPIO_PIN_30             BIT_32_30

//! GPIO Pin 31
#define GPIO_PIN_31             BIT_32_31

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup  LPC17xx_GPIO_General_Pin_IDs  LPC17xx GPIO General Pin ID
//! \brief       The following values define the bit field for the ucPins argument
//!              to several of the APIs.
//! @{
//
//*****************************************************************************
#if defined(LPC_175x) && defined (LPC_176x)
#define GPIO_PA0_PA0            ((unsigned long)0x00 << 0 )
#define GPIO_PA0_CAN1RX         ((unsigned long)0x01 << 0 )
#define GPIO_PA0_UART3TX        ((unsigned long)0x02 << 0 )
#define GPIO_PA0_I2C1SDA        ((unsigned long)0x03 << 0 )
#define GPIO_PA1_PA1            ((unsigned long)0x00 << 2 )
#define GPIO_PA1_CAN1TX         ((unsigned long)0x01 << 2 )
#define GPIO_PA1_UART3RX        ((unsigned long)0x02 << 2 )
#define GPIO_PA1_I2C1SCK        ((unsigned long)0x03 << 2 )
#define GPIO_PA2_PA2            ((unsigned long)0x00 << 4 )
#define GPIO_PA2_UART0TX        ((unsigned long)0x01 << 4 )
#define GPIO_PA2_ADC7           ((unsigned long)0x02 << 4 )
#define GPIO_PA3_PA3            ((unsigned long)0x00 << 6 )
#define GPIO_PA3_UART0RX        ((unsigned long)0x01 << 6 )
#define GPIO_PA3_ADC6           ((unsigned long)0x02 << 6 )
#define GPIO_PA4_PA4            ((unsigned long)0x00 << 8 )
#define GPIO_PA4_I2SRX_CLK      ((unsigned long)0x01 << 8 )
#define GPIO_PA4_CAN2RX         ((unsigned long)0x02 << 8 )
#define GPIO_PA4_TIMCCP0        ((unsigned long)0x03 << 8 )
#define GPIO_PA5_PA5            ((unsigned long)0x00 << 10)
#define GPIO_PA5_I2SRX_WS       ((unsigned long)0x01 << 10)
#define GPIO_PA5_CAN2TX         ((unsigned long)0x02 << 10)
#define GPIO_PA5_TIMCCP1        ((unsigned long)0x03 << 10)
#define GPIO_PA6_PA6            ((unsigned long)0x00 << 12)
#define GPIO_PA6_I2SRX_SDA      ((unsigned long)0x01 << 12)
#define GPIO_PA6_SSEL1          ((unsigned long)0x02 << 12)
#define GPIO_PA6_TIM_MAT0       ((unsigned long)0x03 << 12)
#define GPIO_PA7_PA7            ((unsigned long)0x00 << 14)
#define GPIO_PA7_I2STX_CLK      ((unsigned long)0x01 << 14)
#define GPIO_PA7_SCK1           ((unsigned long)0x02 << 14)
#define GPIO_PA7_TIM_MAT1       ((unsigned long)0x03 << 14)
#define GPIO_PA8_PA8            ((unsigned long)0x00 << 16)
#define GPIO_PA8_I2STX_WS       ((unsigned long)0x01 << 16)
#define GPIO_PA8_MISO1          ((unsigned long)0x02 << 16)
#define GPIO_PA8_TIM_MAT2       ((unsigned long)0x03 << 16)
#define GPIO_PA9_PA9            ((unsigned long)0x00 << 18)
#define GPIO_PA9_I2STX_SDA      ((unsigned long)0x01 << 18)
#define GPIO_PA9_MOSI1          ((unsigned long)0x02 << 18)
#define GPIO_PA9_TIM_MAT3       ((unsigned long)0x03 << 18)
#define GPIO_PA10_PA10          ((unsigned long)0x00 << 20)
#define GPIO_PA10_UART2TX       ((unsigned long)0x01 << 20)
#define GPIO_PA10_I2C2SDA       ((unsigned long)0x02 << 20)
#define GPIO_PA10_TIM_MAT0      ((unsigned long)0x03 << 20)
#define GPIO_PA11_PA11          ((unsigned long)0x00 << 22)
#define GPIO_PA11_UART2RX       ((unsigned long)0x01 << 22)
#define GPIO_PA11_I2C2SCK       ((unsigned long)0x02 << 22)
#define GPIO_PA11_TIM_MAT1      ((unsigned long)0x03 << 22)
#define GPIO_PA15_PA15          ((unsigned long)0x00 << 30)
#define GPIO_PA15_UART1TX       ((unsigned long)0x01 << 30)
#define GPIO_PA15_SCK0          ((unsigned long)0x02 << 30)
#define GPIO_PA15_SPI0CLK       ((unsigned long)0x03 << 30)
#define GPIO_PA16_PA16          ((unsigned long)0x00 << 0 )
#define GPIO_PA16_UART1RX       ((unsigned long)0x01 << 0 )
#define GPIO_PA16_SSEL0         ((unsigned long)0x02 << 0 )
#define GPIO_PA16_SPI0CS        ((unsigned long)0x03 << 0 )
#define GPIO_PA17_PA17          ((unsigned long)0x00 << 2 )
#define GPIO_PA17_UART1CTS      ((unsigned long)0x01 << 2 )
#define GPIO_PA17_MISO0         ((unsigned long)0x02 << 2 )
#define GPIO_PA17_SPI0MISO      ((unsigned long)0x03 << 2 )
#define GPIO_PA18_PA18          ((unsigned long)0x00 << 4 )
#define GPIO_PA18_UART1DCD      ((unsigned long)0x01 << 4 )
#define GPIO_PA18_MOSI0         ((unsigned long)0x02 << 4 )
#define GPIO_PA18_SPI0MOSI      ((unsigned long)0x03 << 4 )
#define GPIO_PA19_PA19          ((unsigned long)0x00 << 6 )
#define GPIO_PA19_UART1DSR      ((unsigned long)0x01 << 6 )
#define GPIO_PA19_I2C1SDA       ((unsigned long)0x03 << 6 )
#define GPIO_PA20_PA20          ((unsigned long)0x00 << 8 )
#define GPIO_PA20_UART1DTR      ((unsigned long)0x01 << 8 )
#define GPIO_PA20_I2C1SCK       ((unsigned long)0x03 << 8 )
#define GPIO_PA21_PA21          ((unsigned long)0x00 << 10)
#define GPIO_PA21_UART1RI       ((unsigned long)0x01 << 10)
#define GPIO_PA21_CAN1RX        ((unsigned long)0x03 << 10)
#define GPIO_PA22_PA22          ((unsigned long)0x00 << 12)
#define GPIO_PA22_UART1RTS      ((unsigned long)0x01 << 12)
#define GPIO_PA22_CAN1TX        ((unsigned long)0x03 << 12)
#define GPIO_PA23_PA23          ((unsigned long)0x00 << 14)
#define GPIO_PA23_ADC0          ((unsigned long)0x01 << 14)
#define GPIO_PA23_I2SRX_CLK     ((unsigned long)0x02 << 14)
#define GPIO_PA23_TIMCCP0       ((unsigned long)0x03 << 14)
#define GPIO_PA24_PA24          ((unsigned long)0x00 << 16)
#define GPIO_PA24_ADC1          ((unsigned long)0x01 << 16)
#define GPIO_PA24_I2SRX_WS      ((unsigned long)0x02 << 16)
#define GPIO_PA24_TIMCCP1       ((unsigned long)0x03 << 16)
#define GPIO_PA25_PA25          ((unsigned long)0x00 << 18)
#define GPIO_PA25_ADC2          ((unsigned long)0x01 << 18)
#define GPIO_PA25_I2SRX_SDA     ((unsigned long)0x02 << 18)
#define GPIO_PA25_UART3TX       ((unsigned long)0x03 << 18)
#define GPIO_PA26_PA26          ((unsigned long)0x00 << 20)
#define GPIO_PA26_ADC3          ((unsigned long)0x01 << 20)
#define GPIO_PA26_DACOUT1       ((unsigned long)0x02 << 20)
#define GPIO_PA26_UART3RX       ((unsigned long)0x03 << 20)
#define GPIO_PA27_PA27          ((unsigned long)0x00 << 22)
#define GPIO_PA27_I2C0SDA       ((unsigned long)0x01 << 22)
#define GPIO_PA27_USB_SDA       ((unsigned long)0x02 << 22)
#define GPIO_PA28_PA28          ((unsigned long)0x00 << 24)
#define GPIO_PA28_I2C0SCK       ((unsigned long)0x01 << 24)
#define GPIO_PA28_USB_SCL       ((unsigned long)0x02 << 24)
#define GPIO_PA29_PA29          ((unsigned long)0x00 << 26)
#define GPIO_PA29_USB_D_P       ((unsigned long)0x01 << 26)
#define GPIO_PA30_PA30          ((unsigned long)0x00 << 28)
#define GPIO_PA30_USB_D_N       ((unsigned long)0x01 << 28)
#define GPIO_PB0_PB0            ((unsigned long)0x00 << 0 )
#define GPIO_PB0_ETH_TXD0       ((unsigned long)0x01 << 0 )
#define GPIO_PB1_PB1            ((unsigned long)0x00 << 2 )
#define GPIO_PB1_ETH_TXD1       ((unsigned long)0x01 << 2 )
#define GPIO_PB4_PB4            ((unsigned long)0x00 << 8 )
#define GPIO_PB4_ETH_TX_EN      ((unsigned long)0x01 << 8 )
#define GPIO_PB8_PB8            ((unsigned long)0x00 << 16)
#define GPIO_PB8_ETH_CRS        ((unsigned long)0x01 << 16)
#define GPIO_PB9_PB9            ((unsigned long)0x00 << 18)
#define GPIO_PB9_ETH_RXD0       ((unsigned long)0x01 << 18)
#define GPIO_PB10_PB10          ((unsigned long)0x00 << 20)
#define GPIO_PB10_ETH_RXD1      ((unsigned long)0x01 << 20)
#define GPIO_PB14_PB14          ((unsigned long)0x00 << 28)
#define GPIO_PB14_ETH_RX_ER     ((unsigned long)0x01 << 28)
#define GPIO_PB15_PB15          ((unsigned long)0x00 << 30)
#define GPIO_PB15_ETH_REF_CLK   ((unsigned long)0x01 << 30)
#define GPIO_PB16_PB16          ((unsigned long)0x00 << 0 )
#define GPIO_PB16_ENET_MDC      ((unsigned long)0x01 << 0 )
#define GPIO_PB17_PB17          ((unsigned long)0x00 << 2 )
#define GPIO_PB17_ENET_MDIO     ((unsigned long)0x01 << 2 )
#define GPIO_PB18_PB18          ((unsigned long)0x00 << 4 )
#define GPIO_PB18_USB_UP_LED    ((unsigned long)0x01 << 4 )
#define GPIO_PB18_PWM1          ((unsigned long)0x02 << 4 )
#define GPIO_PB18_TIMCCP0       ((unsigned long)0x03 << 4 )
#define GPIO_PB19_PB19          ((unsigned long)0x00 << 6 )
#define GPIO_PB19_MCOA0         ((unsigned long)0x01 << 6 )
#define GPIO_PB19_USB_PPWR      ((unsigned long)0x02 << 6 )
#define GPIO_PB19_TIMCCP1       ((unsigned long)0x03 << 6 )
#define GPIO_PB20_PB20          ((unsigned long)0x00 << 8 )
#define GPIO_PB20_MCI0          ((unsigned long)0x01 << 8 )
#define GPIO_PB20_PWM2          ((unsigned long)0x02 << 8 )
#define GPIO_PB20_SCK0          ((unsigned long)0x03 << 8 )
#define GPIO_PB21_PB21          ((unsigned long)0x00 << 10)
#define GPIO_PB21_MCABORT       ((unsigned long)0x01 << 10)
#define GPIO_PB21_PWM3          ((unsigned long)0x02 << 10)
#define GPIO_PB21_SSEL0         ((unsigned long)0x03 << 10)
#define GPIO_PB22_PB22          ((unsigned long)0x00 << 12)
#define GPIO_PB22_MCOB0         ((unsigned long)0x01 << 12)
#define GPIO_PB22_USB_PWRD      ((unsigned long)0x02 << 12)
#define GPIO_PB22_TIM_MAT0      ((unsigned long)0x03 << 12)
#define GPIO_PB23_PB23          ((unsigned long)0x00 << 14)
#define GPIO_PB23_MCI1          ((unsigned long)0x01 << 14)
#define GPIO_PB23_PWM4          ((unsigned long)0x02 << 14)
#define GPIO_PB23_MISO0         ((unsigned long)0x03 << 14)
#define GPIO_PB24_PB24          ((unsigned long)0x00 << 16)
#define GPIO_PB24_MCI2          ((unsigned long)0x01 << 16)
#define GPIO_PB24_PWM5          ((unsigned long)0x02 << 16)
#define GPIO_PB24_MOSI0         ((unsigned long)0x03 << 16)
#define GPIO_PB25_PB25          ((unsigned long)0x00 << 18)
#define GPIO_PB25_MCOA1         ((unsigned long)0x01 << 18)
#define GPIO_PB25_TIM_MAT1      ((unsigned long)0x03 << 18)
#define GPIO_PB26_PB26          ((unsigned long)0x00 << 20)
#define GPIO_PB26_MCOB1         ((unsigned long)0x01 << 20)
#define GPIO_PB26_PWM6          ((unsigned long)0x02 << 20)
#define GPIO_PB26_TIMCCP0       ((unsigned long)0x03 << 20)
#define GPIO_PB27_PB27          ((unsigned long)0x00 << 22)
#define GPIO_PB27_CLKOUT        ((unsigned long)0x01 << 22)
#define GPIO_PB27_USB_OVRCR     ((unsigned long)0x02 << 22)
#define GPIO_PB27_TIMCCP1       ((unsigned long)0x03 << 22)
#define GPIO_PB28_PB28          ((unsigned long)0x00 << 24)
#define GPIO_PB28_MCOA2         ((unsigned long)0x01 << 24)
#define GPIO_PB28_PWM_CAP_CH0   ((unsigned long)0x02 << 24)
#define GPIO_PB28_TIM_MAT0      ((unsigned long)0x03 << 24)
#define GPIO_PB29_PB29          ((unsigned long)0x00 << 26)
#define GPIO_PB29_MCOB2         ((unsigned long)0x01 << 26)
#define GPIO_PB29_PWM_CAP_CH1   ((unsigned long)0x02 << 26)
#define GPIO_PB29_TIM_MAT1      ((unsigned long)0x03 << 26)
#define GPIO_PB30_PB30          ((unsigned long)0x00 << 28)
#define GPIO_PB30_VBUS          ((unsigned long)0x02 << 28)
#define GPIO_PB30_ADC4          ((unsigned long)0x03 << 28)
#define GPIO_PB31_PB31          ((unsigned long)0x00 << 30)
#define GPIO_PB31_SCK1          ((unsigned long)0x02 << 30)
#define GPIO_PB31_ADC5          ((unsigned long)0x03 << 30)
#define GPIO_PC0_PC0            ((unsigned long)0x00 << 0 )
#define GPIO_PC0_PWM1           ((unsigned long)0x01 << 0 )
#define GPIO_PC0_UART1TX        ((unsigned long)0x02 << 0 )
#define GPIO_PC1_PC1            ((unsigned long)0x00 << 2 )
#define GPIO_PC1_PWM2           ((unsigned long)0x01 << 2 )
#define GPIO_PC1_UART1RX        ((unsigned long)0x02 << 2 )
#define GPIO_PC2_PC2            ((unsigned long)0x00 << 4 )
#define GPIO_PC2_PWM3           ((unsigned long)0x01 << 4 )
#define GPIO_PC2_UART1CTS       ((unsigned long)0x02 << 4 )
#define GPIO_PC3_PC3            ((unsigned long)0x00 << 6 )
#define GPIO_PC3_PWM4           ((unsigned long)0x01 << 6 )
#define GPIO_PC3_UART1DCD       ((unsigned long)0x02 << 6 )
#define GPIO_PC4_PC4            ((unsigned long)0x00 << 8 )
#define GPIO_PC4_PWM5           ((unsigned long)0x01 << 8 )
#define GPIO_PC4_UART1DSR       ((unsigned long)0x02 << 8 )
#define GPIO_PC5_PC5            ((unsigned long)0x00 << 10)
#define GPIO_PC5_PWM6           ((unsigned long)0x01 << 10)
#define GPIO_PC5_UART1DTR       ((unsigned long)0x02 << 10)
#define GPIO_PC6_PC6            ((unsigned long)0x00 << 12)
#define GPIO_PC6_PWM_CAP_CH0    ((unsigned long)0x01 << 12)
#define GPIO_PC6_UART1RI        ((unsigned long)0x02 << 12)
#define GPIO_PC7_PC7            ((unsigned long)0x00 << 14)
#define GPIO_PC7_CAN2RX         ((unsigned long)0x01 << 14)
#define GPIO_PC7_UART1RTS       ((unsigned long)0x02 << 14)
#define GPIO_PC8_PC8            ((unsigned long)0x00 << 16)
#define GPIO_PC8_CAN2TX         ((unsigned long)0x01 << 16)
#define GPIO_PC8_UART2TX        ((unsigned long)0x02 << 16)
#define GPIO_PC8_ENET_MDC       ((unsigned long)0x03 << 16)
#define GPIO_PC9_PC9            ((unsigned long)0x00 << 18)
#define GPIO_PC9_USB_CONNECT    ((unsigned long)0x01 << 18)
#define GPIO_PC9_UART2RX        ((unsigned long)0x02 << 18)
#define GPIO_PC9_ENET_MDIO      ((unsigned long)0x03 << 18)
#define GPIO_PC10_PC10          ((unsigned long)0x00 << 20)
#define GPIO_PC10_EINT0         ((unsigned long)0x01 << 20)
#define GPIO_PC10_NMI           ((unsigned long)0x02 << 20)
#define GPIO_PC11_PC11          ((unsigned long)0x00 << 22)
#define GPIO_PC11_EINT1         ((unsigned long)0x01 << 22)
#define GPIO_PC11_I2STX_CLK     ((unsigned long)0x03 << 22)
#define GPIO_PC12_PC12          ((unsigned long)0x00 << 24)
#define GPIO_PC12_EINT2         ((unsigned long)0x01 << 24)
#define GPIO_PC12_I2STX_WS      ((unsigned long)0x03 << 24)
#define GPIO_PC13_PC13          ((unsigned long)0x00 << 26)
#define GPIO_PC13_EINT3         ((unsigned long)0x01 << 26)
#define GPIO_PC13_I2STX_SDA     ((unsigned long)0x03 << 26)
#define GPIO_PD25_PD25          ((unsigned long)0x00 << 18)
#define GPIO_PD25_TIM_MAT0      ((unsigned long)0x02 << 18)
#define GPIO_PD25_PWM2          ((unsigned long)0x03 << 18)
#define GPIO_PD26_PD26          ((unsigned long)0x00 << 20)
#define GPIO_PD26_STCLK         ((unsigned long)0x01 << 20)
#define GPIO_PD26_TIM_MAT1      ((unsigned long)0x02 << 20)
#define GPIO_PD26_PWM3          ((unsigned long)0x03 << 20)
#define GPIO_PE28_PE28          ((unsigned long)0x00 << 24)
#define GPIO_PE28_RX_MCLK       ((unsigned long)0x01 << 24)
#define GPIO_PE28_TIM_MAT0      ((unsigned long)0x02 << 24)
#define GPIO_PE28_UART3TX       ((unsigned long)0x03 << 24)
#define GPIO_PE29_PE29          ((unsigned long)0x00 << 26)
#define GPIO_PE29_TX_MCLK       ((unsigned long)0x01 << 26)
#define GPIO_PE29_TIM_MAT1      ((unsigned long)0x02 << 26)
#define GPIO_PE29_UART3RX       ((unsigned long)0x03 << 26)

#elif defined(LPC_177x) && defined (LPC_178x)

#define GPIO_PA0_PA0            0x00
#define GPIO_PA0_CAN1RX         0x01
#define GPIO_PA0_UART3TX        0x02
#define GPIO_PA0_I2C1SDA        0x03
#define GPIO_PA0_UART0TX        0x04
#define GPIO_PA1_PA1            0x00
#define GPIO_PA1_CAN1TX         0x01
#define GPIO_PA1_UART3RX        0x02
#define GPIO_PA1_I2C1SCK        0x03
#define GPIO_PA1_UART0RX        0x04
#define GPIO_PA2_PA2            0x00
#define GPIO_PA2_UART0TX        0x01
#define GPIO_PA2_UART3TX        0x02
#define GPIO_PA3_PA3            0x00
#define GPIO_PA3_UART0RX        0x01
#define GPIO_PA3_UART3RX        0x02
#define GPIO_PA4_PA4            0x00
#define GPIO_PA4_I2SRX_CLK      0x01
#define GPIO_PA4_CAN2RX         0x02
#define GPIO_PA4_TIMCCP0        0x03
#define GPIO_PA5_PA5            0x00
#define GPIO_PA5_I2SRX_WS       0x01
#define GPIO_PA5_CAN2TX         0x02
#define GPIO_PA5_TIMCCP1        0x03
#define GPIO_PA6_PA6            0x00
#define GPIO_PA6_I2SRX_SDA      0x01
#define GPIO_PA6_SPI1CS         0x02
#define GPIO_PA6_TIM_MAT0       0x03
#define GPIO_PA6_UART1RTS       0x04
#define GPIO_PA10_PA10          0x00
#define GPIO_PA10_UART2TX       0x01
#define GPIO_PA10_I2C2SDA       0x02
#define GPIO_PA10_TIM_MAT0      0x03
#define GPIO_PA11_PA11          0x00
#define GPIO_PA11_UART2RX       0x01
#define GPIO_PA11_I2C2SCK       0x02
#define GPIO_PA11_TIM_MAT1      0x03
#define GPIO_PA14_PA14          0x00
#define GPIO_PA14_USBHST2       0x01
#define GPIO_PA14_SPI1CS        0x02
#define GPIO_PA14_USBCNT2       0x03
#define GPIO_PA15_PA15          0x00
#define GPIO_PA15_UART1TX       0x01
#define GPIO_PA15_SCK0          0x02
#define GPIO_PA15_SPI0CLK       0x03
#define GPIO_PA16_PA16          0x00
#define GPIO_PA16_UART1RX       0x01
#define GPIO_PA16_SPI0CS        0x02
#define GPIO_PA16_SPI0CS        0x03
#define GPIO_PA17_PA17          0x00
#define GPIO_PA17_UART1CTS      0x01
#define GPIO_PA17_MISO0         0x02
#define GPIO_PA17_SPI0MISO      0x03
#define GPIO_PA18_PA18          0x00
#define GPIO_PA18_UART1DCD      0x01
#define GPIO_PA18_MOSI0         0x02
#define GPIO_PA18_SPI0MOSI      0x03
#define GPIO_PA19_PA19          0x00
#define GPIO_PA19_UART1DSR      0x01
#define GPIO_PA19_SDCLK         0x02
#define GPIO_PA19_I2C1SDA       0x03
#define GPIO_PA20_PA20          0x00
#define GPIO_PA20_UART1DTR      0x01
#define GPIO_PA20_I2C1SCK       0x03
#define GPIO_PA21_PA21          0x00
#define GPIO_PA21_UART1RI       0x01
#define GPIO_PA21_CAN1RX        0x03
#define GPIO_PA22_PA22          0x00
#define GPIO_PA22_UART1RTS      0x01
#define GPIO_PA22_CAN1TX        0x03
#define GPIO_PB0_PB0            0x00
#define GPIO_PB0_ETH_TXD0       0x01
#define GPIO_PB1_PB1            0x00
#define GPIO_PB1_ETH_TXD1       0x01
#define GPIO_PB1_PWM1           0x03
#define GPIO_PB2_PB2            0x00
#define GPIO_PB2_ETH_TXD2       0x01
#define GPIO_PB2_PWM2           0x03
#define GPIO_PB3_PB3            0x00
#define GPIO_PB3_ETH_TXD3       0x01
#define GPIO_PB4_PB4            0x00
#define GPIO_PB4_ETH_TX_EN      0x01
#define GPIO_PB4_TIM_MAT2       0x03
#define GPIO_PB4_SPI2MISO       0x04
#define GPIO_PB5_PB5            0x00
#define GPIO_PB5_ETH_TX_ER      0x01
#define GPIO_PB5_PWM3           0x03
#define GPIO_PB6_PB6            0x00
#define GPIO_PB6_ETH_TX_CLK     0x01
#define GPIO_PB6_PWM4           0x03
#define GPIO_PB7_PB7            0x00
#define GPIO_PB7_ETH_COL        0x01
#define GPIO_PB7_PWM5           0x03
#define GPIO_PB8_PB8            0x00
#define GPIO_PB8_ETH_CRS        0x01
#define GPIO_PB8_TIM_MAT1       0x03
#define GPIO_PB8_SPI2CS         0x04
#define GPIO_PB9_PB9            0x00
#define GPIO_PB9_ETH_RXD0       0x01
#define GPIO_PB8_TIM_MAT0       0x03
#define GPIO_PB10_PB10          0x00
#define GPIO_PB10_ETH_RXD1      0x01
#define GPIO_PB10_TIMCCP        0x03
#define GPIO_PB11_PB11          0x00
#define GPIO_PB11_ETH_RXD2      0x01
#define GPIO_PB11_PWM6          0x03
#define GPIO_PB12_PB12          0x00
#define GPIO_PB12_ETH_RXD3      0x01
#define GPIO_PB12_PWM7          0x03
#define GPIO_PB13_PB13          0x00
#define GPIO_PB13_ETH_RX_DV     0x01
#define GPIO_PB14_PB14          0x00
#define GPIO_PB14_ETH_RX_ER     0x01
#define GPIO_PB14_TIMCCP        0x03
#define GPIO_PB15_PB15          0x00
#define GPIO_PB15_ETH_REF_CLK   0x01
#define GPIO_PB15_I2C2SDA       0x03
#define GPIO_PB16_PB16          0x00
#define GPIO_PB16_ENET_MDC      0x01
#define GPIO_PB16_I2S_TX_MCLK   0x02
#define GPIO_PB17_PB17          0x00
#define GPIO_PB17_ENET_MDIO     0x01
#define GPIO_PB17_I2S_RX_MCLK   0x02
#define GPIO_PB18_PB18          0x00
#define GPIO_PB18_USB_UP_LED    0x01
#define GPIO_PB18_PWM1          0x02
#define GPIO_PB18_TIMCCP0       0x03
#define GPIO_PB19_PB19          0x00
#define GPIO_PB19_USB_TX_E      0x01
#define GPIO_PB19_USB_PPWR      0x02
#define GPIO_PB19_TIMCCP1       0x03
#define GPIO_PB19_MCOA0         0x04
#define GPIO_PB19_SPI1SCK       0x05
#define GPIO_PB20_PB20          0x00
#define GPIO_PB20_USB_TX_DP     0x01
#define GPIO_PB20_PWM2          0x02
#define GPIO_PB20_SPI0CLK       0x03
#define GPIO_PB21_PB21          0x00
#define GPIO_PB21_USB_TX_DM     0x01
#define GPIO_PB21_PWM3          0x02
#define GPIO_PB21_SPI0CS        0x03
#define GPIO_PB22_PB22          0x00
#define GPIO_PB22_USB_RCV       0x01
#define GPIO_PB22_USB_PWRD      0x02
#define GPIO_PB22_TIM_MAT0      0x03
#define GPIO_PB22_SPI1MOSI      0x05
#define GPIO_PB23_PB23          0x00
#define GPIO_PB23_USB_RX_DP     0x01
#define GPIO_PB23_PWM4          0x02
#define GPIO_PB23_SPI0MISO      0x05
#define GPIO_PB24_PB24          0x00
#define GPIO_PB24_USB_RX_DM     0x01
#define GPIO_PB24_PWM5          0x02
#define GPIO_PB24_SPI0MOSI      0x05
#define GPIO_PB25_PB25          0x00
#define GPIO_PB25_USB_LS        0x01
#define GPIO_PB25_USB_HST       0x02
#define GPIO_PB25_TIM_MAT1      0x03
#define GPIO_PB26_PB26          0x00
#define GPIO_PB26_USB_SSPND     0x01
#define GPIO_PB26_PWM6          0x02
#define GPIO_PB26_TIMCCP0       0x03
#define GPIO_PB26_SPI1CS        0x05
#define GPIO_PB27_PB27          0x00
#define GPIO_PB27_USB_INT       0x01
#define GPIO_PB27_USB_OVRCR     0x02
#define GPIO_PB27_TIMCCP1       0x03
#define GPIO_PB28_PB28          0x00
#define GPIO_PB28_USB_SCL       0x01
#define GPIO_PB28_PWM_CAP_CH0   0x02
#define GPIO_PB28_TIM_MAT0      0x03
#define GPIO_PB28_SPI0CS        0x05
#define GPIO_PB29_PB29          0x00
#define GPIO_PB29_USB_SDA       0x01
#define GPIO_PB29_PWM_CAP_CH1   0x02
#define GPIO_PB29_TIM_MAT1      0x03
#define GPIO_PB29_UART4TX       0x05
#define GPIO_PC0_PC0            0x00
#define GPIO_PC0_PWM1           0x01
#define GPIO_PC0_UART1TX        0x02
#define GPIO_PC1_PC1            0x00
#define GPIO_PC1_PWM2           0x01
#define GPIO_PC1_UART1RX        0x02
#define GPIO_PC2_PC2            0x00
#define GPIO_PC2_PWM3           0x01
#define GPIO_PC2_UART1CTS       0x02
#define GPIO_PC2_TIM_MAT3       0x03
#define GPIO_PC3_PC3            0x00
#define GPIO_PC3_PWM4           0x01
#define GPIO_PC3_UART1DCD       0x02
#define GPIO_PC3_TIM_MAT2       0x03
#define GPIO_PC4_PC4            0x00
#define GPIO_PC4_PWM5           0x01
#define GPIO_PC4_UART1DSR       0x02
#define GPIO_PC4_TIM_MAT1       0x03
#define GPIO_PC5_PC5            0x00
#define GPIO_PC5_PWM6           0x01
#define GPIO_PC5_UART1DTR       0x02
#define GPIO_PC5_TIM_MAT0       0x03
#define GPIO_PC6_PC6            0x00
#define GPIO_PC6_PWM_CAP_CH0    0x01
#define GPIO_PC6_UART1RI        0x02
#define GPIO_PC2_TIMCCP0        0x03
#define GPIO_PC7_PC7            0x00
#define GPIO_PC7_CAN2RX         0x01
#define GPIO_PC7_UART1RTS       0x02
#define GPIO_PC8_PC8            0x00
#define GPIO_PC8_CAN2TX         0x01
#define GPIO_PC8_UART2TX        0x02
#define GPIO_PC8_UART1CTS       0x03
#define GPIO_PC8_ENET_MDC       0x04
#define GPIO_PC9_PC9            0x00
#define GPIO_PC9_USB_CONNECT    0x01
#define GPIO_PC9_UART2RX        0x02
#define GPIO_PC9_UART4RX        0x03
#define GPIO_PC9_ENET_MDIO      0x04
#define GPIO_PC10_PC10          0x00
#define GPIO_PC10_EINT0         0x01
#define GPIO_PC10_NMI           0x02
#define GPIO_PC11_PC11          0x00
#define GPIO_PC11_EINT1         0x01
#define GPIO_PC11_I2STX_CLK     0x03
#define GPIO_PC12_PC12          0x00
#define GPIO_PC12_EINT2         0x01
#define GPIO_PC12_I2STX_WS      0x03
#define GPIO_PC13_PC13          0x00
#define GPIO_PC13_EINT3         0x01
#define GPIO_PC13_I2STX_SDA     0x03
#define GPIO_PC14_PC14          0x00
#define GPIO_PC14_EMCCS2        0x01
#define GPIO_PC14_I2C1SDA       0x02
#define GPIO_PC14_TIMCCP0       0x03
#define GPIO_PC15_PC15          0x00
#define GPIO_PC15_EMCCS3        0x01
#define GPIO_PC15_I2C1SCL       0x02
#define GPIO_PC15_TIMCCP1       0x03
#define GPIO_PC16_PC16          0x00
#define GPIO_PC16_EMCCAS        0x01
#define GPIO_PC17_PC17          0x00
#define GPIO_PC17_EMCRAS        0x01
#define GPIO_PC18_PC18          0x00
#define GPIO_PC18_CLK           0x01
#define GPIO_PC19_PC19          0x00
#define GPIO_PC19_CLK           0x01
#define GPIO_PC20_PC20          0x00
#define GPIO_PC20_EMCDYCS       0x01
#define GPIO_PC21_PC21          0x00
#define GPIO_PC21_EMCDYCS       0x01
#define GPIO_PC22_PC22          0x00
#define GPIO_PC22_EMCDYCS       0x01
#define GPIO_PC22_SPI0CLK       0x02
#define GPIO_PC22_TIM_CAP       0x03
#define GPIO_PC23_PC23          0x00
#define GPIO_PC23_EMCDYCS       0x01
#define GPIO_PC23_SPI0CS        0x02
#define GPIO_PC23_TIM_CAP       0x03
#define GPIO_PC24_PC24          0x00
#define GPIO_PC24_EMCCKE        0x01
#define GPIO_PC25_PC25          0x00
#define GPIO_PC25_EMCCKE        0x01
#define GPIO_PC26_PC26          0x00
#define GPIO_PC26_EMCCKE        0x01
#define GPIO_PC26_SPI0MISO      0x02
#define GPIO_PC26_TIM_MAT0      0x03
#define GPIO_PC27_PC27          0x00
#define GPIO_PC27_EMCCKE        0x01
#define GPIO_PC27_SPI0MOSI      0x02
#define GPIO_PC27_TIM_MAT1      0x03
#define GPIO_PC28_PC28          0x00
#define GPIO_PC28_EMCDQM        0x01
#define GPIO_PC29_PC29          0x00
#define GPIO_PC29_EMCDQM        0x01
#define GPIO_PC30_PC30          0x00
#define GPIO_PC30_EMCDQM        0x01
#define GPIO_PC30_I2C2SDA       0x02
#define GPIO_PC30_TIM_MAT2      0x03
#define GPIO_PC31_PC31          0x00
#define GPIO_PC31_EMCDQM        0x01
#define GPIO_PC31_I2C2SCK       0x02
#define GPIO_PC31_TIM_MAT3      0x03
#define GPIO_PD0_PD0            0x00
#define GPIO_PD1_PD1            0x00
#define GPIO_PD2_PD2            0x00
#define GPIO_PD3_PD3            0x00
#define GPIO_PD4_PD4            0x00
#define GPIO_PD5_PD5            0x00
#define GPIO_PD6_PD6            0x00
#define GPIO_PD7_PD7            0x00
#define GPIO_PD8_PD8            0x00
#define GPIO_PD9_PD9            0x00
#define GPIO_PD10_PD10          0x00
#define GPIO_PD11_PD11          0x00
#define GPIO_PD12_PD12          0x00
#define GPIO_PD13_PD13          0x00
#define GPIO_PD14_PD14          0x00
#define GPIO_PD15_PD15          0x00
#define GPIO_PD16_PD16          0x00
#define GPIO_PD16_PWM1          0x02
#define GPIO_PD16_UART1TX       0x03
#define GPIO_PD17_PD17          0x00
#define GPIO_PD17_PWM2          0x02
#define GPIO_PD17_UART1RX       0x03
#define GPIO_PD18_PD18          0x00
#define GPIO_PD18_PWM3          0x02
#define GPIO_PD18_UART1CTS      0x03
#define GPIO_PD19_PD19          0x00
#define GPIO_PD19_PWM4          0x02
#define GPIO_PD19_UART1DCD      0x03
#define GPIO_PD20_PD20          0x00
#define GPIO_PD20_PWM5          0x02
#define GPIO_PD20_UART1DSR      0x03
#define GPIO_PD21_PD21          0x00
#define GPIO_PD21_PWM7          0x02
#define GPIO_PD21_UART1DSR      0x03


#define GPIO_PD25_PD25          0x00
#define GPIO_PD25_TIM_MAT0      0x02
#define GPIO_PD25_PWM2          0x03
#define GPIO_PD26_PD26          0x00
#define GPIO_PD26_STCLK         0x01
#define GPIO_PD26_TIM_MAT1      0x02
#define GPIO_PD26_PWM3          0x03
#define GPIO_PE28_PE28          0x00
#define GPIO_PE28_RX_MCLK       0x01
#define GPIO_PE28_TIM_MAT0      0x02
#define GPIO_PE28_UART3TX       0x03
#define GPIO_PE29_PE29          0x00
#define GPIO_PE29_TX_MCLK       0x01
#define GPIO_PE29_TIM_MAT1      0x02
#define GPIO_PE29_UART3RX       0x03

#endif

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup  LPC17xx_GPIO_Cfg  LPC17xx GPIO Configure parameters.
//! \brief
//! @{
//
//*****************************************************************************

//! Disable Open-Drain function.
#define PIN_MODE_OD_DIS         (BIT_32_6                       )

//! Enable Open-Drain function.
#define PIN_MODE_OD_EN          (BIT_32_6 | BIT_32_5            )

//! Enable pull-up function.
#define PIN_MODE_PULL_UP        (BIT_32_4                       )

//! Enable repeater function.
#define PIN_MODE_REPEATER       (BIT_32_4 | BIT_32_2            )

//! No pull-up, No pull-down.
#define PIN_MODE_NONE           (BIT_32_4 | BIT_32_3            )

//! Enable pull-down function.
#define PIN_MODE_PULL_DOWN      (BIT_32_4 | BIT_32_3 | BIT_32_2 )

//! Input mode.
#define PIN_MODE_INPUT          (BIT_32_1                       )

//! Output mode.
#define PIN_MODE_OUTPUT         (BIT_32_1 | BIT_32_0            )

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup  LPC17xx_GPIO_Int_Types  LPC17xx GPIO Interrupt types
//! \brief
//! @{
//
//*****************************************************************************

//! GPIO Interrupt Type: Rising edge
#define INT_TYPE_RISING         BIT_32_0

//! GPIO Interrupt Type: Falling edge
#define INT_TYPE_FALLING        BIT_32_1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_GPIO_Exported_APIs LPC17xx GPIO API
//! \brief      LPC17xx GPIO APIs Reference.
//! @{
//
//*****************************************************************************

extern unsigned long GPIOPinToPeripheralId(unsigned long ulPort, unsigned long ulPin);
extern unsigned long GPIOPinToPort(unsigned long ulPort, unsigned long ulPin);
extern unsigned long GPIOPinToPin(unsigned long ulPort, unsigned long ulPin);

extern void          GPIOPinFunCfg(unsigned long ulPort, unsigned long ulPin, unsigned long ulCfg);
extern void          GPIOPinModeCfg(unsigned long ulPort, unsigned long ulPin, unsigned long ulCfg);
extern void          GPIOPinSet(unsigned long ulPort, unsigned long ulPins);
extern void          GPIOPinClr(unsigned long ulPort, unsigned long ulPins);
extern void          GPIOPinWrite(unsigned long ulPort, unsigned long ulPins, unsigned long ulVal);
extern unsigned long GPIOPinRead(unsigned long ulPort, unsigned long ulPin);
extern unsigned long GPIOPortRead(unsigned long ulPort);
extern void          GPIOPortWrite(unsigned long ulPort, unsigned long ulVal);
extern void          GPIOPinIntCfg(unsigned long ulPort, unsigned long ulPin, unsigned long ulCfg);
extern unsigned long GPIOPinIntFlagGet(unsigned long ulPort, unsigned long ulPin);
extern void          GPIOPinIntFlagClear(unsigned long ulPort, unsigned long ulPin);
extern void          GPIOPinIntEnable(unsigned long ulPort, unsigned long ulPin);
extern void          GPIOPinIntDisable(unsigned long ulPort, unsigned long ulPin);

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

#endif // __XGPIO_H__

