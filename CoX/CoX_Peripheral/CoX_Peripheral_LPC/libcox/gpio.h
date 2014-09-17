//*****************************************************************************
//
//! \file      gpio.h
//! \brief     Prototypes for the GPIO Driver.
//! \version   V3.0.0.0
//! \date      $CURRENTTIME$
//! \author    CooCox
//! \copyright
//!
//! Copyright (c)  2014, CooCox
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

#ifndef _LPC17XX_GPIO_H__
#define _LPC17XX_GPIO_H__

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

///////////////////////////////////////////////////////////////////////////////
// define for port to cox 'x' prefixed interface
///////////////////////////////////////////////////////////////////////////////
#define GPIO_DIR_MODE_IN        PIN_MODE_INPUT
#define GPIO_DIR_MODE_OUT       PIN_MODE_OUTPUT
#define GPIO_DIR_MODE_HW        0
#define GPIO_DIR_MODE_QB        0
#define GPIO_DIR_MODE_OD        PIN_MODE_OD_EN

#define GPIO_PIN_TYPE_PU        PIN_MODE_PULL_UP
#define GPIO_PIN_TYPE_PD        PIN_MODE_PULL_DOWN
#define GPIO_PIN_TYPE_NP        PIN_MODE_NONE

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

///////////////////////////////////////////////////////////////////////////////
// define for port to cox 'x' prefixed interface
///////////////////////////////////////////////////////////////////////////////
#define GPIO_FALLING_EDGE       INT_TYPE_FALLING
#define GPIO_RISING_EDGE        INT_TYPE_RISING
#define GPIO_LOW_LEVEL          0
#define GPIO_HIGH_LEVEL         0
#define GPIO_BOTH_EDGES         INT_TYPE_FALLING | INT_TYPE_RISING
#define GPIO_BOTH_LEVEL         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_GPIO_Pad_Config_Strength LPC17xx xGPIO Pad Config Strength
//
//*****************************************************************************
#define GPIO_STRENGTH_2MA       0
#define GPIO_STRENGTH_4MA       0
#define GPIO_STRENGTH_8MA       0

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

#endif // _LPC17XX_GPIO_H__
