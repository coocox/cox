//*****************************************************************************
//
//! \file xgpio.h
//! \brief Prototypes for the GPIO Driver.
//! \brief Prototypes for the AFIO Driver.
//! \version V2.2.1.0
//! \date 7/31/2012
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
//! |xGPIO General Pin ID    |       CoX      |            KLx         |
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
//! \section xGPIO_General_Pin_SIDs 1. Where to use this group
//! The following values define the bit field for the ulPins argument to several
//! of the APIs. So all the API which have a ulPins argument must use this group.
//! 
//! \section xGPIO_General_Pin_IDs_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO General Pin ID    |       CoX      |         KLx            |
//! |------------------------|----------------|------------------------|
//! |xGPIO_PIN_n             |    Mandatory   |       xGPIO_PIN_0      |
//! |                        |                |------------------------|
//! |                        |                |       xGPIO_PIN_1      |
//! |                        |                |------------------------|
//! |                        |                |       xGPIO_PIN_2      |
//! |                        |                |------------------------|
//! |                        |                |           ...          |
//! |                        |                |------------------------|
//! |                        |                |      xGPIO_PIN_15      |
//! |                        |                |------------------------|
//! |                        |                |           ...          |
//! |                        |                |------------------------|
//! |                        |                |      xGPIO_PIN_30      |
//! |                        |                |------------------------|
//! |                        |                |      xGPIO_PIN_31      |
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

//
//! GPIO pin 16
//
#define xGPIO_PIN_16            GPIO_PIN_16

//
//! GPIO pin 17
//
#define xGPIO_PIN_17            GPIO_PIN_17

//
//! GPIO pin 18
//
#define xGPIO_PIN_18            GPIO_PIN_18

//
//! GPIO pin 19
//
#define xGPIO_PIN_19            GPIO_PIN_19

//
//! GPIO pin 20
//
#define xGPIO_PIN_20            GPIO_PIN_20

//
//! GPIO pin 21
//
#define xGPIO_PIN_21            GPIO_PIN_21

//
//! GPIO pin 22
//
#define xGPIO_PIN_22            GPIO_PIN_22

//
//! GPIO pin 23
//
#define xGPIO_PIN_23            GPIO_PIN_23

//
//! GPIO pin 24
//
#define xGPIO_PIN_24            GPIO_PIN_24

//
//! GPIO pin 25
//
#define xGPIO_PIN_25            GPIO_PIN_25

//
//! GPIO pin 26
//
#define xGPIO_PIN_26            GPIO_PIN_26

//
//! GPIO pin 23
//
#define xGPIO_PIN_27            GPIO_PIN_27

//
//! GPIO pin 28
//
#define xGPIO_PIN_28            GPIO_PIN_28

//
//! GPIO pin 29
//
#define xGPIO_PIN_29            GPIO_PIN_29

//
//! GPIO pin 30
//
#define xGPIO_PIN_30            GPIO_PIN_30

//
//! GPIO pin 31
//
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
//! \section xGPIO_Dir_Mode_S1 1. Where to use this group
//! Values that can be passed to xGPIODirModeSet as the ulPinIO parameter, and
//! returned from xGPIODirModeGet.
//! 
//! \section xGPIO_Dir_Mode_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO Dir Mode          |       CoX      |           KLx          |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_IN       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_OUT      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xGPIO_DIR_MODE_HW       |    Mandatory   |            N           |
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
#define xGPIO_DIR_MODE_OD       0

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
//! |xGPIO Int Type          |       CoX      |           KLx          |
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
// Interrupt on both levels
//
#define xGPIO_BOTH_LEVEL        0

//
// Interrupt on low level
//
#define xGPIO_LOW_LEVEL         GPIO_LEVEL_LOW  

//
// Interrupt on high level
//
#define xGPIO_HIGH_LEVEL        GPIO_LEVEL_HIGH 

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
//! |xGPIO Pad Strength      |       CoX      |           KLx          |
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
//! |xGPIO Pad Type          |       CoX      |           KLx          |
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

//
//! GPIO pin type standard
//
#define	xGPIO_PIN_TYPE_STD      0

//
//! GPIO pin type standard with pull up
//
#define xGPIO_PIN_TYPE_STD_WPU  0

//
//! GPIO pin type open drain
//
#define xGPIO_PIN_TYPE_OD       0

//
//! GPIO pin type open drain with pull up
//
#define xGPIO_PIN_TYPE_OD_WPU   0

//
//! GPIO pin type open drain with pull down
//
#define xGPIO_PIN_TYPE_OD_WPD   0

//
//! GPIO pin type analog
//
#define xGPIO_PIN_TYPE_ANALOG   0

//
//! GPIO pin type with pull down
//
#define xGPIO_PIN_TYPE_STD_WPD  0

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
//! |xGPIO Short Pin ID      |       CoX      |           KLx          |
//! |------------------------|----------------|------------------------|
//! |PXn                     |    Mandatory   |    PA0 PA1 ... PA31    |
//! |                        |                |------------------------|
//! |X is A, B, C ...        |                |    PB0 PB1 ... PB31    |
//! |                        |                |------------------------|
//! |                        |                |    PC0 PC1 ... PC31    |
//! |                        |                |------------------------|
//! |                        |                |    PD0 PD1 ... PD31    |
//! |                        |                |------------------------|
//! |                        |                |    PE0 PE1 ... PE31    |
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
#define PA16                    PA16
#define PA17                    PA17
#define PA18                    PA18
#define PA19                    PA19
#define PA20                    PA20
#define PA21                    PA21
#define PA22                    PA22
#define PA23                    PA23
#define PA24                    PA24
#define PA25                    PA25
#define PA26                    PA26
#define PA27                    PA27
#define PA28                    PA28
#define PA29                    PA29
#define PA30                    PA30
#define PA31                    PA31

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
#define PB16                    PB16
#define PB17                    PB17
#define PB18                    PB18
#define PB19                    PB19
#define PB20                    PB20
#define PB21                    PB21
#define PB22                    PB22
#define PB23                    PB23
#define PB24                    PB24
#define PB25                    PB25
#define PB26                    PB26
#define PB27                    PB27
#define PB28                    PB28
#define PB29                    PB29
#define PB30                    PB30
#define PB31                    PB31

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
#define PC16                    PC16
#define PC17                    PC17
#define PC18                    PC18
#define PC19                    PC19
#define PC20                    PC20
#define PC21                    PC21
#define PC22                    PC22
#define PC23                    PC23
#define PC24                    PC24
#define PC25                    PC25
#define PC26                    PC26
#define PC27                    PC27
#define PC28                    PC28
#define PC29                    PC29
#define PC30                    PC30
#define PC31                    PC31

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
#define PD16                    PD16
#define PD17                    PD17
#define PD18                    PD18
#define PD19                    PD19
#define PD20                    PD20
#define PD21                    PD21
#define PD22                    PD22
#define PD23                    PD23
#define PD24                    PD24
#define PD25                    PD25
#define PD26                    PD26
#define PD27                    PD27
#define PD28                    PD28
#define PD29                    PD29
#define PD30                    PD30
#define PD31                    PD31

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
#define PE16                    PE16
#define PE17                    PE17
#define PE18                    PE18
#define PE19                    PE19
#define PE20                    PE20
#define PE21                    PE21
#define PE22                    PE22
#define PE23                    PE23
#define PE24                    PE24
#define PE25                    PE25
#define PE26                    PE26
#define PE27                    PE27
#define PE28                    PE28
#define PE29                    PE29
#define PE30                    PE30
#define PE31                    PE31

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
//! |General Peripheral Pin  |       CoX      |           KLx          |
//! |------------------------|----------------|------------------------|
//! |ADCn                    |    Mandatory   |   ADC0 ADC1 ... ADC23  |
//! |                        |                |------------------------|
//! |                        |                |   ADCDP0.......ADCDP3  |
//! |                        |                |------------------------|
//! |                        |                |   ADCDM0.......ADCDM3  |
//! |------------------------|----------------|------------------------|
//! |I2CnSCK                 |    Mandatory   |     I2C0SCK I2C1SCK    |
//! |------------------------|----------------|------------------------|
//! |I2CnSDA                 |    Mandatory   |     I2C0SDA I2C1SDA    |
//! |------------------------|----------------|------------------------|
//! |SPInCLK                 |    Mandatory   |     SPI0CLK SPI1CLK    |
//! |------------------------|----------------|------------------------|
//! |SPInMOSI                |    Mandatory   |    SPI0MOSI SPI1MOSI   |
//! |------------------------|----------------|------------------------|
//! |SPInMISO                |    Mandatory   |    SPI0MISO SPI1MISO   |
//! |------------------------|----------------|------------------------|
//! |SPInCS                  |    Mandatory   |      SPI0CS SPI1CS     |
//! |------------------------|----------------|------------------------|
//! |UARTnRX                 |    Mandatory   |     UART0RX UART1RX    |
//! |                        |                |------------------------|
//! |                        |                |     UART2RX            |
//! |------------------------|----------------|------------------------|
//! |UARTnTX                 |    Mandatory   |     UART0TX UART1TX    |
//! |                        |                |------------------------|
//! |                        |                |     UART2TX            |
//! |------------------------|----------------|------------------------|
//! |CMPnN                   |    Mandatory   |       CMP0N CMP1N      |
//! |------------------------|----------------|------------------------|
//! |CMPnP                   |    Mandatory   |       CMP0P CMP1P      |
//! |------------------------|----------------|------------------------|
//! |CMPnO                   |    Mandatory   |       CMP0O CMP1O      |
//! |------------------------|----------------|------------------------|
//! |PWMn                    |    Mandatory   |      PWM0 ... PWM5     |
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
#define ADC16                   ADC16
#define ADC17                   ADC17
#define ADC18                   ADC18
#define ADC19                   ADC19
#define ADC20                   ADC20
#define ADC21                   ADC21
#define ADC22                   ADC22
#define ADC23                   ADC23
#define ADCDP0                  ADCDP0
#define ADCDP1                  ADCDP1
#define ADCDP2                  ADCDP2
#define ADCDP3                  ADCDP3
#define ADCDM0                  ADCDM0
#define ADCDM1                  ADCDM1
#define ADCDM2                  ADCDM2
#define ADCDM3                  ADCDM3

#define I2C0SCK                 I2C0SCK
#define I2C0SDA                 I2C0SDA
#define I2C1SCK                 I2C1SCK
#define I2C1SDA                 I2C1SDA
 
#define SPI0CLK                 SPI0CLK
#define SPI0MOSI                SPI0MOSI
#define SPI0MISO                SPI0MISO
#define SPI0CS                  SPI0CS
#define SPI1CLK                 SPI1CLK
#define SPI1MOSI                SPI1MOSI
#define SPI1MISO                SPI1MISO
#define SPI1CS                  SPI1CS
 
#define UART0RX                 UART0RX
#define UART0TX                 UART0TX
#define UART1RX                 UART1RX
#define UART1TX                 UART1TX
#define UART2RX                 UART2RX
#define UART2TX                 UART2TX

#define DACOUT1                 DACOUT1

#define CMP0IN0                 CMP0IN0
#define CMP0IN1                 CMP0IN1
#define CMP0IN2                 CMP0IN2
#define CMP0IN3                 CMP0IN3
#define CMP0IN4                 CMP0IN4
#define CMP0IN5                 CMP0IN5
#define CMP0O                   CMP0O

#define TIM0CH0                 TIM0CH0
#define TIM0CH1                 TIM0CH1
#define TIM0CH2                 TIM0CH2
#define TIM0CH3                 TIM0CH3
#define TIM0CH4                 TIM0CH4
#define TIM0CH5                 TIM0CH5
#define TIM0CLKIN               TIM0CLKIN

#define TIM1CH0                 TIM1CH0
#define TIM1CH1                 TIM1CH1
#define TIM1CH2                 TIM1CH2
#define TIM1CH3                 TIM1CH3
#define TIM1CH4                 TIM1CH4
#define TIM1CH5                 TIM1CH5
#define TIM1CLKIN               TIM1CLKIN

#define TIM2CH0                 TIM2CH0
#define TIM2CH1                 TIM2CH1
#define TIM2CH2                 TIM2CH2
#define TIM2CH3                 TIM2CH3
#define TIM2CH4                 TIM2CH4
#define TIM2CH5                 TIM2CH5

#define LPTMR0ALT1              LPTMR0ALT1
#define LPTMR0ALT2              LPTMR0ALT2


#define TSI0CH1                 TSI0CH1
#define TSI0CH2                 TSI0CH2
#define TSI0CH3                 TSI0CH3
#define TSI0CH4                 TSI0CH4
#define TSI0CH5                 TSI0CH5
#define TSI0CH6                 TSI0CH6
#define TSI0CH7                 TSI0CH7
#define TSI0CH8                 TSI0CH8
#define TSI0CH9                 TSI0CH9
#define TSI0CH10                TSI0CH10
#define TSI0CH11                TSI0CH11
#define TSI0CH12                TSI0CH12
#define TSI0CH13                TSI0CH13
#define TSI0CH14                TSI0CH14
#define TSI0CH15                TSI0CH15

#define NMIB                    NMIB

#define EXTAL0                  EXTAL0
#define XTAL0                   XTAL0

#define EXTRGIN                 EXTRGIN
#define LLWUP6                  LLWUP6
#define LLWUP7                  LLWUP7
#define LLWUP8                  LLWUP8
#define LLWUP14                 LLWUP14

#define RTCCLKIN                RTCCLKIN

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
//! |xGPIO API                 |       CoX      |           KLx          |
//! |--------------------------|----------------|------------------------|
//! |xGPIODirModeSet           |    Mandatory   |            Y           |
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
//! |xSPinTypeCAN              |    Mandatory   |            N           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypeI2C              |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xSPinTypeI2S              |  Non-Mandatory |            N           |
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
         GPIOSPinConfigure(eShortPin, eShortPin);                             \
         xGPIOSDirModeSet(eShortPin, xGPIO_DIR_MODE_IN);                      \
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
         GPIOSPinConfigure(eShortPin, eShortPin);                             \
         xGPIOSDirModeSet(eShortPin, xGPIO_DIR_MODE_OUT);                     \
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
#define xGPIOSPinTypeGPIOOutputOD(eShortPin)

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
//! |        KLx         |    ADC0                |    PE20                |
//! |                    |    ADC1                |    PC2                 |
//! |                    |    ADC2                |                        |
//! |                    |    ADC3                |    PE22                |
//! |                    |    ADC4                |                        |
//! |                    |    ADC5                |                        |
//! |                    |    ADC6                |    PD5                 |
//! |                    |    ADC7                |    PD6,PE23            |
//! |                    |    ADC8                |    PB0                 |
//! |                    |    ADC9                |    PB1                 |
//! |                    |    ADC10               |                        |
//! |                    |    ADC11               |    PC2                 |
//! |                    |    ADC12               |    PB2                 |
//! |                    |    ADC13               |    PB3                 |
//! |                    |    ADC14               |    PC0                 |
//! |                    |    ADC15               |    PC1                 |
//! |                    |    ADC16               |                        |
//! |                    |    ADC17               |                        |
//! |                    |    ADC18               |                        |
//! |                    |    ADC19               |                        |
//! |                    |    ADC20               |                        |
//! |                    |    ADC21               |                        |
//! |                    |    ADC22               |                        |
//! |                    |    ADC23               |    PE30                |
//! |                    |    ADCDP0              |    PE20                |
//! |                    |    ADCDP1              |                        |
//! |                    |    ADCDP2              |                        |
//! |                    |    ADCDP3              |    PE22                |
//! |                    |    ADCDM0              |    PE21                |
//! |                    |    ADCDM1              |                        |
//! |                    |    ADCDM2              |                        |
//! |                    |    ADCDM3              |    PE23                |
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
//! |       KLx          |    CMP0IN0             |    PC6                 |
//! |                    |    CMP0IN1             |    PC7                 |
//! |                    |    CMP0IN2             |    PC8                 |
//! |                    |    CMP0IN3             |    PC9                 |
//! |                    |    CMP0IN4             |    PE29                |
//! |                    |    CMP0IN5             |    PE30                |
//! |                    |    CMP0O               |    PC0                 |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSPinTypeACMP(ePeripheralPin, eShortPin)                               \
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
//! |    KLx             |    CAN0RX              |                        |
//! |                    |    CAN0TX              |                        |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************             
#define xSPinTypeCAN(ePeripheralPin, eShortPin)

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
//! |    KLx             |    I2C0SCK             |    PB0,PB2,PC8,PE24    |
//! |                    |    I2C0SDA             |    PB1,PB3,PC9,PE25    |
//! |                    |    I2C1SCK             |    PA3,PC1,PE1,PC10    |
//! |                    |    I2C1SDA             |    PA4,PC2,PE0,PC11    |
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
//! |    KLx             |                        |                        |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//***************************************************************************** 
#define xSPinTypeI2S(ePeripheralPin, eShortPin)                              

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
//! |    KLx             |    SPI0CLK             |    PA15,PC5,PD1        |
//! |                    |    SPI0MOSI            |    PA16,PA17,PC6,PC7   |
//! |                    |                        |    PD2 PD3             |
//! |                    |    SPI0MISO            |    PA16,PA17,PC6,PC7   |
//! |                    |                        |    PD2 PD3             |
//! |                    |    SPI0CS              |    PA14,PC4,PD0        |
//! |                    |    SPI1CLK             |    PB11,PE2,PD5        |
//! |                    |    SPI1MOSI            |    PB16,PB17,PD6,PD7   |
//! |                    |                        |	   PE1,PE3 	   |
//! |                    |    SPI1MISO            |    PB16,PB17,PD6,PD7   |
//! |                    |                        |	   PE1,PE3 	   |
//! |                    |    SPI1CS              |    PB10,PD4,PE4        |
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
//! |    KLx             |    TIM0CH0             |    PA3,PC1,PD0,PE24    |
//! |                    |    TIM0CH1             |    PA4,PC2,PD1,PE25    |
//! |                    |    TIM0CH2             |    PA5,PC3,PD2,PE29    |
//! |                    |    TIM0CH3             |    PC4,PD3,PE30        |
//! |                    |    TIM0CH4             |    PC8,PD4,PE31        |
//! |                    |    TIM0CH5             |    PC9,PD5             |
//! |                    |    TIM0CLKIN           |    PA18,PB16,PC12,PE29 |
//! |                    |    TIM1CH0             |    PA12 PB0 PE20       |
//! |                    |    TIM1CH1             |    PA13 PB1 PE21       |
//! |                    |    TIM1CH2             |                        |
//! |                    |    TIM1CH3             |                        |
//! |                    |    TIM1CH4             |                        |
//! |                    |    TIM1CH5             |                        |
//! |                    |    TIM1CLKIN           |    PA19,PB17,PC13,PE30 |
//! |                    |    TIM2CH0             |    PA1,PB2,PB18,PE22   |
//! |                    |    TIM2CH1             |    PA2,PB3,PB19,PE23   |
//! |                    |    TIM2CH2             |                        |
//! |                    |    TIM2CH3             |                        |
//! |                    |    TIM2CH4             |                        |
//! |                    |    TIM2CH5             |                        |
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
//! xSPinTypePWM(PWM0, PC0) or xSPinTypePWM(PWM1, PC1) is correct;<br/>
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
//! |    KLx             |    TIM0CH0             |    PA3,PC1,PD0,PE24    |
//! |                    |    TIM0CH1             |    PA4,PC2,PD1,PE25    |
//! |                    |    TIM0CH2             |    PA5,PC3,PD2,PE29    |
//! |                    |    TIM0CH3             |    PC4,PD3,PE30        |
//! |                    |    TIM0CH4             |    PC8,PD4,PE31        |
//! |                    |    TIM0CH5             |    PC9,PD5             |
//! |                    |    TIM0CLKIN           |    PA18,PB16,PC12,PE29 |
//! |                    |    TIM1CH0             |    PA12 PB0 PE20       |
//! |                    |    TIM1CH1             |    PA13 PB1 PE21       |
//! |                    |    TIM1CH2             |                        |
//! |                    |    TIM1CH3             |                        |
//! |                    |    TIM1CH4             |                        |
//! |                    |    TIM1CH5             |                        |
//! |                    |    TIM1CLKIN           |    PA19,PB17,PC13,PE30 |
//! |                    |    TIM2CH0             |    PA1,PB2,PB18,PE22   |
//! |                    |    TIM2CH1             |    PA2,PB3,PB19,PE23   |
//! |                    |    TIM2CH2             |                        |
//! |                    |    TIM2CH3             |                        |
//! |                    |    TIM2CH4             |                        |
//! |                    |    TIM2CH5             |                        |
//! |--------------------|------------------------|------------------------|
//! \endverbatim
//!
//! \return None.
//
//***************************************************************************** 
#define xSPinTypePWM(ePeripheralPin, eShortPin)                               \
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
//! |    KLx             |    UART0RX             |    PA15,PB16,PD6,PE21  |
//! |                    |    UART0TX             |    PA2,PA14,PB17,PD7   |
//! |                    |                        |    PE20		   |
//! |                    |    UART1RX             |    PA18,PC3,PE1        |
//! |                    |    UART1TX             |    PA19,PC4,PE0        |
//! |                    |    UART2RX             |    PD2,PD4,PE23        |
//! |                    |    UART2TX             |    PD3,PD5,PE22        |
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
//! |    KLx             |    MCO                 |    PA8                 |
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
//! |    KLx             |    DACOUT1             |  PE30                  |
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
//! \addtogroup KLx_GPIO
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_GPIO_General_Pin_IDs KLx GPIO General Pin ID
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

//
//! GPIO pin 16
//
#define GPIO_PIN_16             0x00010000 

//
//! GPIO pin 17
//
#define GPIO_PIN_17             0x00020000 

//
//! GPIO pin 18
//
#define GPIO_PIN_18             0x00040000 

//
//! GPIO pin 19
//
#define GPIO_PIN_19             0x00080000 

//
//! GPIO pin 20
//
#define GPIO_PIN_20             0x00100000

//
//! GPIO pin 21
//
#define GPIO_PIN_21             0x00200000

//
//! GPIO pin 22
//
#define GPIO_PIN_22             0x00400000

//
//! GPIO pin 23
//
#define GPIO_PIN_23             0x00800000

//
//! GPIO pin 24
//
#define GPIO_PIN_24             0x01000000

//
//! GPIO pin 25
//
#define GPIO_PIN_25             0x02000000

//
//! GPIO pin 26
//
#define GPIO_PIN_26             0x04000000

//
//! GPIO pin 27
//
#define GPIO_PIN_27             0x08000000

//
//! GPIO pin 28
//
#define GPIO_PIN_28             0x10000000

//
//! GPIO pin 29
//
#define GPIO_PIN_29             0x20000000

//
//! GPIO pin 30
//
#define GPIO_PIN_30             0x40000000

//
//! GPIO pin 31
//
#define GPIO_PIN_31             0x80000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_GPIO_General_Pin_Bits KLx GPIO General Pin Bits
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

//
//! GPIO BIT 16
//
#define GPIO_BIT_16             0x00000010  

//
//! GPIO BIT 17
//
#define GPIO_BIT_17             0x00000011  

//
//! GPIO BIT 18
//
#define GPIO_BIT_18             0x00000012  

//
//! GPIO BIT 19
//
#define GPIO_BIT_19             0x00000013  

//
//! GPIO BIT 20
//
#define GPIO_BIT_20             0x00000014  

//
//! GPIO BIT 21
//
#define GPIO_BIT_21             0x00000015  

//
//! GPIO BIT 22
//
#define GPIO_BIT_22             0x00000016  

//
//! GPIO BIT 23
//
#define GPIO_BIT_23             0x00000017  

//
//! GPIO BIT 24
//
#define GPIO_BIT_24             0x00000018  

//
//! GPIO BIT 25
//
#define GPIO_BIT_25             0x00000019

//
//! GPIO BIT 26
//
#define GPIO_BIT_26             0x0000001A  

//
//! GPIO BIT 27
//
#define GPIO_BIT_27             0x0000001B  

//
//! GPIO BIT 28
//
#define GPIO_BIT_28             0x0000001C  

//
//! GPIO BIT 29
//
#define GPIO_BIT_29             0x0000001D  

//
//! GPIO BIT 30
//
#define GPIO_BIT_30             0x0000001E  

//
//! GPIO BIT 31
//
#define GPIO_BIT_31             0x0000001F     

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_GPIO_Dir_Mode KLx GPIO Dir Mode
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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_GPIO_Pad_Config_Type
//! Values that can be passed to GPIOPadConfigSet as the ulPadType parameter,
//! and returned by GPIOPadConfigGet in the *pulPadType parameter.
//! @{
//
//*****************************************************************************

//
//! Drive Strength Disable
//
#define PORT_TYPE_DSE_LOW       0x00000000

//
//! Drive Strength Enable
//
#define PORT_TYPE_DSE_HIGH      0x00000040

//
//! Passive Filter Disable 
//
#define PORT_TYPE_PEF_DIS       0x00000000

//
//! Passive Filter Enable 
//
#define PORT_TYPE_PEF_ENA       0x00000010

//
//! Slew Rate Enable
//
#define PORT_TYPE_SRE_FAST      0x00000000

//
//! Slew Rate Disable
//
#define PORT_TYPE_SRE_SLOW      0x00000004    

//
//! Pull Disable
//
#define PORT_TYPE_PE_DIS        0x00000000

//
//! Pull Enable
//
#define PORT_TYPE_PE_ENA        0x00000002

//
//! Alternate function output Push-pull
//
#define PORT_TYPE_PS_DOWN       0x00000000

//
//! Alternate function output Push-down
//
#define PORT_TYPE_PS_UP         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_GPIO_Int_Type KLx GPIO Int Type
//! \brief Values that can be passed to GPIOIntTypeSet as the ulIntType parameter, 
//! and returned from GPIOIntTypeGet.
//! @{
//
//*****************************************************************************

//
//! Interrupt when logic zero.
//
#define GPIO_LEVEL_LOW          0x00080000

//
//! Interrupt on rising edge
//
#define GPIO_RISING_EDGE        0x00090000    

//
//! Interrupt on falling edge
//
#define GPIO_FALLING_EDGE       0x000A0000 

//
//! Interrupt on both edges
//
#define GPIO_BOTH_EDGES         0x000B0000

//
//! Interrupt when logic one
//
#define GPIO_LEVEL_HIGH         0x000C0000  


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_GPIO_DMA_Edge KLx GPIO DMA Edge
//! \brief Values that can be passed to GPIODMAEdgeSet as the ulDMAEdge parameter.
//! @{
//
//*****************************************************************************

//
//! Interrupt/DMA request disabled.
//
#define GPIO_DMA_DIS            0x00000000

//
//! DMA request on rising edge.
//
#define GPIO_DMA_RISE           0x00010000 

//
//! DMA request on falling edge.
//
#define GPIO_DMA_FALL           0x00020000

//
//! DMA request on either edge.
//
#define GPIO_DMA_BOTH           0x00030000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_PORT_Drive_Strength KLx PORT Drive Strength
//! \brief Values that can be passed to GPIOPadConfigSet as the ulStrength
//!        parameter.
//! @{
//
//*****************************************************************************

//
//! Drive Strength Low
//
#define GPIO_DRIVER_STR_DIS     0x00000000

//
//! Drive Strength high
//
#define GPIO_DRIVER_STR_ENA     0x00000040 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_PORT_Pull_Enable KLx PORT Pull Enable
//! \brief Values that can be passed to GPIOPadConfigSet as the ulPadType
//!        parameter.
//! @{
//
//*****************************************************************************

//
//! Drive Strength Low
//
#define GPIO_PULL_ENABLE        0x00000002

//
//! Drive Strength high
//
#define GPIO_PULL_DISABLE       0x00000000 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_PORT_Pull_Select KLx PORT Pull Select
//! \brief Values that can be passed to GPIOPadConfigSet as the ulPadType
//!        parameter.
//! @{
//
//*****************************************************************************

//
//! Drive Strength Low
//
#define GPIO_PULL_DOWN        0x00000000

//
//! Drive Strength high
//
#define GPIO_PULL_UP          0x00000001 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_PORT_Slew_Rate_Enable KLx PORT Slew Rate Enable
//! \brief Values that can be passed to GPIOPadConfigSet as the ulPadType
//!        parameter.
//! @{
//
//*****************************************************************************

//
//! Fast slew rate 
//
#define GPIO_SLEW_RATE_FAST   0x00000000

//
//! Slow slew rate 
//
#define GPIO_SLEW_RATE_SLOW   0x00000004 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_PORT_Passive_Filter_Enable KLx PORT Passive Filter Enable
//! \brief Values that can be passed to GPIOPadConfigSet as the ulPadType
//!        parameter.
//! @{
//
//*****************************************************************************

//
//! Passive input filter is disabled
//
#define GPIO_PASSIVE_FILTER_DIS 0x00000000

//
//! Passive input filter is enabled 
//
#define GPIO_PASSIVE_FILTER_ENA 0x00000010 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_GPIO_Function_Set KLx GPIO Function Set
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
#define GPIO_FUNCTION_CLKO      0x00000008   
#define GPIO_FUNCTION_EXTINT    0x00000009  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_GPIO_Pin_Config KLx GPIO Pin Config
//! \brief Values that can be passed to xGPIOPinConfigure as the ulPinConfig 
//! parameter.
//! @{
//
//*****************************************************************************

//
//! GPIO pin A0
//
#define GPIO_PA0_TSI0CH1        0x00000000
#define GPIO_PA0_PA0            0x00000001
#define GPIO_PA0_TIM0CH5        0x00000003
#define GPIO_PA0_SWDCLK         0x00000007

//
//! GPIO pin A1
//
#define GPIO_PA1_TSI0CH2        0x00000010
#define GPIO_PA1_PA1            0x00000011
#define GPIO_PA1_UART0RX        0x00000012
#define GPIO_PA1_TIM2CH0        0x00000013

//
//! GPIO pin A2
//
#define GPIO_PA2_TSI0CH2        0x00000020
#define GPIO_PA2_PA2            0x00000021
#define GPIO_PA2_UART0TX        0x00000022
#define GPIO_PA2_TIM2CH1        0x00000023

//
//! GPIO pin A3
//
#define GPIO_PA3_TSI0CH4        0x00000030
#define GPIO_PA3_PA3            0x00000031
#define GPIO_PA3_I2C1SCK        0x00000032
#define GPIO_PA3_TIM0CH0        0x00000033
#define GPIO_PA3_SWDDIO         0x00000037

//
//! GPIO pin A4
//
#define GPIO_PA4_TSI0CH5        0x00000040
#define GPIO_PA4_I2C1SDA        0x00000042
#define GPIO_PA4_TIM0CH1        0x00000043
#define GPIO_PA4_NMIB           0x00000047

//
//! GPIO pin A5
//
#define GPIO_PA5_PA5            0x00000051
#define GPIO_PA5_USBCLK         0x00000052
#define GPIO_PA5_TIM0CH2        0x00000053

//
//! GPIO pin A12
//
#define GPIO_PA12_PA12          0x000000C1
#define GPIO_PA12_TIM1CH0       0x000000C3

//
//! GPIO pin A13
//
#define GPIO_PA13_PA13          0x000000D1
#define GPIO_PA13_TIM1CH1       0x000000D3

//
//! GPIO pin A14
//
#define GPIO_PA14_PA14          0x000000E1
#define GPIO_PA14_SPI0CS        0x000000E2
#define GPIO_PA14_UART0TX       0x000000E3

//
//! GPIO pin A15
//
#define GPIO_PA15_PA15          0x000000F1
#define GPIO_PA15_SPI0CLK       0x000000F2
#define GPIO_PA15_UART0RX       0x000000F3

//
//! GPIO pin A16
//
#define GPIO_PA16_PA16          0x00000101
#define GPIO_PA16_SPI0MOSI      0x00000102
#define GPIO_PA16_SPI0MISO      0x00000105

//
//! GPIO pin A17
//
#define GPIO_PA17_PA17          0x00000111
#define GPIO_PA17_SPI0MISO      0x00000112
#define GPIO_PA17_SPI0MOSI      0x00000115

//
//! GPIO pin A18
//
#define GPIO_PA18_EXTAL0        0x00000120
#define GPIO_PA18_PA18          0x00000121
#define GPIO_PA18_UART1RX       0x00000123
#define GPIO_PA18_TIM0CLKIN     0x00000124

//
//! GPIO pin A19
//
#define GPIO_PA19_XTAL0         0x00000130
#define GPIO_PA19_PA19          0x00000131
#define GPIO_PA19_UART1TX       0x00000133
#define GPIO_PA19_TIM1CLKIN     0x00000134
#define GPIO_PA19_LPTMR0ALT1    0x00000136

//
//! GPIO pin A20
//
#define GPIO_PA20_PA20          0x00000141
#define GPIO_PA20_RESETB        0x00000147

//
//! GPIO pin B0
//
#define GPIO_PB0_ADC8           0x00001000
#define GPIO_PB0_TSI0CH0        0x00001000
#define GPIO_PB0_PB0            0x00001001
#define GPIO_PB0_LLWUP5         0x00001001
#define GPIO_PB0_I2C0SCK        0x00001002
#define GPIO_PB0_TIM1CH0        0x00001003

//
//! GPIO pin B1
//
#define GPIO_PB1_ADC9           0x00001010
#define GPIO_PB1_TSI0CH6        0x00001010
#define GPIO_PB1_PB1            0x00001011
#define GPIO_PB1_I2C0SDA        0x00001012
#define GPIO_PB1_TIM1CH1        0x00001013

//
//! GPIO pin B2
//
#define GPIO_PB2_ADC12          0x00001020
#define GPIO_PB2_TSI0CH7        0x00001020
#define GPIO_PB2_PB2            0x00001021
#define GPIO_PB2_I2C0SCK        0x00001022
#define GPIO_PB2_TIM2CH0        0x00001023

//
//! GPIO pin B3
//
#define GPIO_PB3_ADC13          0x00001030
#define GPIO_PB3_TSI0CH8        0x00001030
#define GPIO_PB3_PB3            0x00001031
#define GPIO_PB3_I2C0SDA        0x00001032
#define GPIO_PB3_TIM2CH1        0x00001033

//
//! GPIO pin B8
//
#define GPIO_PB8_PB8            0x00001081
#define GPIO_PB8_EXTRGIN        0x00001083

//
//! GPIO pin B9
//
#define GPIO_PB9_PB9            0x00001091

//
//! GPIO pin B10
//
#define GPIO_PB10_PB10          0x000010A1
#define GPIO_PB10_SPI1CS        0x000010A2

//
//! GPIO pin B11
//
#define GPIO_PB11_PB11          0x000010B1
#define GPIO_PB11_SPI1CLK       0x000010B2

//
//! GPIO pin B16
//
#define GPIO_PB16_TSI0CH9       0x00001100
#define GPIO_PB16_PB16          0x00001101
#define GPIO_PB16_SPI1MOSI      0x00001102
#define GPIO_PB16_UART0RX       0x00001103
#define GPIO_PB16_TIM0CLKIN     0x00001104
#define GPIO_PB16_SPI1MISO      0x00001105

//
//! GPIO pin B17
//
#define GPIO_PB17_TSI0CH10      0x00001110
#define GPIO_PB17_PB17          0x00001111
#define GPIO_PB17_SPI1MISO      0x00001112
#define GPIO_PB17_UART0TX       0x00001113
#define GPIO_PB17_TIM1CLKIN     0x00001114
#define GPIO_PB17_SPI1MOSI      0x00001115

//
//! GPIO pin B18
//
#define GPIO_PB18_TSI0CH11      0x00001120
#define GPIO_PB18_PB18          0x00001121
#define GPIO_PB18_TIM2CH0       0x00001123

//
//! GPIO pin B19
//
#define GPIO_PB19_TSI0CH12      0x00001130
#define GPIO_PB19_PB19          0x00001131
#define GPIO_PB19_TIM2CH1       0x00001133

//
//! GPIO pin C0
//
#define GPIO_PC0_ADC14          0x00002000
#define GPIO_PC0_TSI0CH13       0x00002000
#define GPIO_PC0_PC0            0x00002001
#define GPIO_PC0_EXTRGIN        0x00002003
#define GPIO_PC0_CMP0O          0x00002005

//
//! GPIO pin C1
//
#define GPIO_PC1_ADC15          0x00002010
#define GPIO_PC1_TSI0CH14       0x00002010
#define GPIO_PC1_PC1            0x00002011
#define GPIO_PC1_LLWUP6         0x00002011
#define GPIO_PC1_RTCCLKIN       0x00002011
#define GPIO_PC1_I2C1SCK        0x00002012
#define GPIO_PC1_TIM0CH0        0x00002014

//
//! GPIO pin C2
//
#define GPIO_PC2_ADC11          0x00002020
#define GPIO_PC2_TSI0CH15       0x00002020
#define GPIO_PC2_PC2            0x00002021
#define GPIO_PC2_I2C1SDA        0x00002022
#define GPIO_PC2_TIM0CH1        0x00002024

//
//! GPIO pin C3
//
#define GPIO_PC3_PC3            0x00002031
#define GPIO_PC3_LLWUP7         0x00002031
#define GPIO_PC3_UART1RX        0x00002033
#define GPIO_PC3_TIM0CH2        0x00002034
#define GPIO_PC3_CLKOUT         0x00002035

//
//! GPIO pin C4
//
#define GPIO_PC4_PC4            0x00002041
#define GPIO_PC4_LLWUP8         0x00002041
#define GPIO_PC4_SPI0CS         0x00002042
#define GPIO_PC4_UART1TX        0x00002043
#define GPIO_PC4_TIM0CH3        0x00002044

//
//! GPIO pin C5
//
#define GPIO_PC5_PC5            0x00002051
#define GPIO_PC5_LLWUP9         0x00002051
#define GPIO_PC5_SPI0CLK        0x00002052
#define GPIO_PC5_LPTMR0ALT2     0x00002053
#define GPIO_PC5_CMP0O          0x00002054

//
//! GPIO pin C6
//
#define GPIO_PC6_CMP0IN0        0x00002060
#define GPIO_PC6_PC6            0x00002061
#define GPIO_PC6_LLWUP10        0x00002061
#define GPIO_PC6_SPI0MOSI       0x00002062
#define GPIO_PC6_EXTRGIN        0x00002063
#define GPIO_PC6_SPI0MISO       0x00002065

//
//! GPIO pin C7
//
#define GPIO_PC7_CMP0IN1        0x00002070
#define GPIO_PC7_PC7            0x00002071
#define GPIO_PC7_SPI0MISO       0x00002072
#define GPIO_PC7_SPI0MOSI       0x00002075

//
//! GPIO pin C8
//
#define GPIO_PC8_CMP0IN2        0x00002080
#define GPIO_PC8_PC8            0x00002081
#define GPIO_PC8_I2C0SCK        0x00002082
#define GPIO_PC8_TIM0CH4        0x00002083

//
//! GPIO pin C9
//
#define GPIO_PC9_CMP0IN3        0x00002090
#define GPIO_PC9_PC9            0x00002091
#define GPIO_PC9_I2C0SDA        0x00002092
#define GPIO_PC9_TIM0CH5        0x00002093

//
//! GPIO pin C10
//
#define GPIO_PC10_PC10           0x000020A1
#define GPIO_PC10_I2C1SCK        0x000020A2

//
//! GPIO pin C11
//
#define GPIO_PC11_PC11           0x000020B1
#define GPIO_PC11_I2C1SDA        0x000020B2

//
//! GPIO pin C12
//
#define GPIO_PC12_PC12           0x000020C1
#define GPIO_PC12_TIM0CLKIN      0x000020C4

//
//! GPIO pin C13
//
#define GPIO_PC13_PC13           0x000020D1
#define GPIO_PC13_TIM1CLKIN      0x000020D4

//
//! GPIO pin C16
//
#define GPIO_PC16_PC16           0x00002101

//
//! GPIO pin C17
//
#define GPIO_PC17_PC17           0x00002111

//
//! GPIO pin D0
//
#define GPIO_PD0_PD0            0x00003001
#define GPIO_PD0_SPI0CS         0x00003002
#define GPIO_PD0_TIM0CH0        0x00003004

//
//! GPIO pin D1
//
#define GPIO_PD1_ADC5           0x00003010
#define GPIO_PD1_PD1            0x00003011
#define GPIO_PD1_SPI0CLK        0x00003012
#define GPIO_PD1_TIM0CH1        0x00003014

//
//! GPIO pin D2
//
#define GPIO_PD2_PD2            0x00003021
#define GPIO_PD2_SPI0MOSI       0x00003022
#define GPIO_PD2_UART2RX        0x00003023
#define GPIO_PD2_TIM0CH2        0x00003024
#define GPIO_PD2_SPI0MISO       0x00003025

//
//! GPIO pin D3
//
#define GPIO_PD3_PD3            0x00003031
#define GPIO_PD3_SPI0MISO       0x00003032
#define GPIO_PD3_UART2TX        0x00003033
#define GPIO_PD3_TIM0CH3        0x00003034
#define GPIO_PD3_SPI0MOSI       0x00003035

//
//! GPIO pin D4
//
#define GPIO_PD4_PD4            0x00003041
#define GPIO_PD4_LLWUP14        0x00003041
#define GPIO_PD4_SPI1CS         0x00003042
#define GPIO_PD4_UART2RX        0x00003043
#define GPIO_PD4_TIM0CH4        0x00003044

//
//! GPIO pin D5
//
#define GPIO_PD5_ADC6           0x00003050
#define GPIO_PD5_PD5            0x00003051
#define GPIO_PD5_SPI1CLK        0x00003052
#define GPIO_PD5_UART2TX        0x00003053
#define GPIO_PD5_TIM0CH5        0x00003054

//
//! GPIO pin D6
//
#define GPIO_PD6_ADC7           0x00003060
#define GPIO_PD6_PD6            0x00003061
#define GPIO_PD6_LLWUP15        0x00003061
#define GPIO_PD6_SPI1MOSI       0x00003062
#define GPIO_PD6_UART0RX        0x00003063
#define GPIO_PD6_SPI1MISO       0x00003065

//
//! GPIO pin D7
//
#define GPIO_PD7_PD7            0x00003071
#define GPIO_PD7_SPI1MISO       0x00003072
#define GPIO_PD7_UART0TX        0x00003073
#define GPIO_PD7_SPI1MOSI       0x00003075

//
//! GPIO pin E0
//
#define GPIO_PE0_PE0            0x00004001
#define GPIO_PE0_UART1TX        0x00004003
#define GPIO_PE0_RTCCLKOUT      0x00004004
#define GPIO_PE0_CMP0O          0x00004005
#define GPIO_PE0_I2C1SDA        0x00004006

//
//! GPIO pin E1
//
#define GPIO_PE1_PE1            0x00004011
#define GPIO_PE1_SPI1MOSI       0x00004012
#define GPIO_PE1_UART1RX        0x00004013
#define GPIO_PE1_SPI1MISO       0x00004015
#define GPIO_PE1_I2C1SCK        0x00004016

//
//! GPIO pin E2
//
#define GPIO_PE2_PE2            0x00004021
#define GPIO_PE2_SPI1CLK        0x00004022

//
//! GPIO pin E3
//
#define GPIO_PE3_PE3            0x00004031
#define GPIO_PE3_SPI1MISO       0x00004032
#define GPIO_PE3_SPI1MOSI       0x00004035

//
//! GPIO pin E4
//
#define GPIO_PE4_PE4            0x00004041
#define GPIO_PE4_SPI1CS         0x00004042

//
//! GPIO pin E5
//
#define GPIO_PE5_PE5            0x00004051

//
//! GPIO pin E20
//
#define GPIO_PE20_ADCDP0        0x00004140
#define GPIO_PE20_ADC0          0x00004140
#define GPIO_PE20_PE20          0x00004141
#define GPIO_PE20_TIM1CH0       0x00004143
#define GPIO_PE20_UART0TX       0x00004144

//
//! GPIO pin E21
//
#define GPIO_PE21_ADCDM0        0x00004150
#define GPIO_PE21_ADC4          0x00004150
#define GPIO_PE21_PE21          0x00004151
#define GPIO_PE21_TIM1CH1       0x00004153
#define GPIO_PE21_UART0RX       0x00004154

//
//! GPIO pin E22
//
#define GPIO_PE22_ADCDP3        0x00004160
#define GPIO_PE22_ADC3          0x00004160
#define GPIO_PE22_PE22          0x00004161
#define GPIO_PE22_TIM2CH0       0x00004163
#define GPIO_PE22_UART2TX       0x00004164

//
//! GPIO pin E23
//
#define GPIO_PE23_ADCDM3        0x00004170
#define GPIO_PE23_ADC7          0x00004170
#define GPIO_PE23_PE23          0x00004171
#define GPIO_PE23_TIM2CH1       0x00004173
#define GPIO_PE23_UART2RX       0x00004174

//
//! GPIO pin E24
//
#define GPIO_PE24_PE24          0x00004181
#define GPIO_PE24_TIM0CH0       0x00004183
#define GPIO_PE24_I2C0SCK       0x00004185

//
//! GPIO pin E25
//
#define GPIO_PE25_PE25          0x00004191
#define GPIO_PE25_TIM0CH1       0x00004193
#define GPIO_PE25_I2C0SDA       0x00004195

//
//! GPIO pin E29
//
#define GPIO_PE29_CMP0IN5       0x000041D0
#define GPIO_PE29_ADC4          0x000041D0
#define GPIO_PE29_PE29          0x000041D1
#define GPIO_PE29_TIM0CH2       0x000041D3
#define GPIO_PE29_TIM0CLKIN     0x000041D4

//
//! GPIO pin E30
//
#define GPIO_PE30_DAC0OUT       0x000041E0
#define GPIO_PE30_ADC23         0x000041E0
#define GPIO_PE30_CMP0IN4       0x000041E0
#define GPIO_PE30_PE30          0x000041E1
#define GPIO_PE30_TIM0CH3       0x000041E3
#define GPIO_PE30_TIM1CLKIN     0x000041E4

//
//! GPIO pin E31
//
#define GPIO_PE31_PE31          0x000041F1
#define GPIO_PE31_TIM0CH4       0x000041F3

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup KLx_GPIO_Exported_APIs KLx GPIO API
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
extern void GPIODMAEdgeSet(unsigned long ulPort, unsigned long ulPin,
                           unsigned long ulDMAEdge);
extern unsigned long GPIOPinIntStatus(unsigned long ulPort);
extern void GPIOPinIntClear(unsigned long ulPort, unsigned long ulPins);
extern long GPIOPinRead(unsigned long ulPort, unsigned long ulPins);
extern void GPIOPinWrite(unsigned long ulPort, unsigned long ulPins,
		                 unsigned char ucVal);
extern void GPIOPinSet(unsigned long ulPort, unsigned long ulPins);	
extern void GPIOPinReset(unsigned long ulPort, unsigned long ulPins);

extern void GPIOPinMaskSet(unsigned long ulPort, unsigned long ulPins);
extern long GPIOPortMaskGet(unsigned long ulPort);
extern long GPIOPinPortDoutGet(unsigned long ulPort);

extern void GPIOPadConfigSet(unsigned long ulPort, unsigned long ulPins, 
                        unsigned long ulStrength);
extern void GPIOPullConfigure(unsigned long ulPort, unsigned long ulPins, 
                           unsigned long ulPullType, unsigned long ulPullCfg);
extern void GPIOPassiveConfigure(unsigned long ulPort, unsigned long ulPins, 
                                    unsigned long ulPassiveCfg);
extern void GPIOSlewRataConfigure(unsigned long ulPort, unsigned long ulPins,
                                                  unsigned long ulSlewRateCfg);

extern void GPIOPinFunctionSet(unsigned long ulFunction, unsigned long ulPort, 
                               unsigned long ulPins);
extern void GPIOPinConfigure(unsigned long ulPinConfig);
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


