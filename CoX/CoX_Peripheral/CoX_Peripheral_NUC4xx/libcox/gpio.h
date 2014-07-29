//*****************************************************************************
//
//! \file gpio.h
//! \brief Prototypes for the GPIO Driver.
//! \brief Prototypes for the AFIO Driver.
//! \version V2.2.1.0
//! \date 11/15/2013
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

#ifndef __GPIO_H__
#define __GPIO_H__

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
//! \addtogroup NUC4xx_GPIO
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_General_Pin_IDs NUC4xx GPIO General Pin ID
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
//! \addtogroup NUC4xx_GPIO_General_Pin_Bits NUC4xx GPIO General Pin Bits
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
//! \addtogroup NUC4xx_GPIO_Dir_Mode NUC4xx GPIO Dir Mode
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
//! \addtogroup NUC4xx_GPIO_Int_Type NUC4xx GPIO Int Type
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
//! \addtogroup NUC4xx_GPIO_DBCLK_Src NUC4xx GPIO De-bounce Clock Source
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
//! \addtogroup NUC4xx_GPIO_Function_Set NUC4xx GPIO Function Set
//! \brief Values that can be passed to GPIOPinFunctionSet as the ulFunction
//! parameter.
//! @{
//
//*****************************************************************************

#define GPIO_FUNCTION_GPIO      0x00000000 
#define GPIO_FUNCTION_SPI       0x00000001   
#define GPIO_FUNCTION_I2C       0x00000004  
#define GPIO_FUNCTION_PWM       0x00000006   
#define GPIO_FUNCTION_TIM       0x00000007   
#define GPIO_FUNCTION_UART      0x00000008   
#define GPIO_FUNCTION_EXTINT    0x0000000B

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup GPIO_GP_Short_Pin NUC4xx General Purpose Short Pin
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

#define GPF0                    GPIO_PORTF_BASE, GPIO_PIN_0
#define GPF1                    GPIO_PORTF_BASE, GPIO_PIN_1
#define GPF2                    GPIO_PORTF_BASE, GPIO_PIN_2
#define GPF3                    GPIO_PORTF_BASE, GPIO_PIN_3
#define GPF4                    GPIO_PORTF_BASE, GPIO_PIN_4
#define GPF5                    GPIO_PORTF_BASE, GPIO_PIN_5
#define GPF6                    GPIO_PORTF_BASE, GPIO_PIN_6
#define GPF7                    GPIO_PORTF_BASE, GPIO_PIN_7
#define GPF8                    GPIO_PORTF_BASE, GPIO_PIN_8
#define GPF9                    GPIO_PORTF_BASE, GPIO_PIN_9
#define GPF10                   GPIO_PORTF_BASE, GPIO_PIN_10
#define GPF11                   GPIO_PORTF_BASE, GPIO_PIN_11
#define GPF12                   GPIO_PORTF_BASE, GPIO_PIN_12
#define GPF13                   GPIO_PORTF_BASE, GPIO_PIN_13
#define GPF14                   GPIO_PORTF_BASE, GPIO_PIN_14
#define GPF15                   GPIO_PORTF_BASE, GPIO_PIN_15

#define GPG0                    GPIO_PORTG_BASE, GPIO_PIN_0
#define GPG1                    GPIO_PORTG_BASE, GPIO_PIN_1
#define GPG2                    GPIO_PORTG_BASE, GPIO_PIN_2
#define GPG3                    GPIO_PORTG_BASE, GPIO_PIN_3
#define GPG4                    GPIO_PORTG_BASE, GPIO_PIN_4
#define GPG5                    GPIO_PORTG_BASE, GPIO_PIN_5
#define GPG6                    GPIO_PORTG_BASE, GPIO_PIN_6
#define GPG7                    GPIO_PORTG_BASE, GPIO_PIN_7
#define GPG8                    GPIO_PORTG_BASE, GPIO_PIN_8
#define GPG9                    GPIO_PORTG_BASE, GPIO_PIN_9
#define GPG10                   GPIO_PORTG_BASE, GPIO_PIN_10
#define GPG11                   GPIO_PORTG_BASE, GPIO_PIN_11
#define GPG12                   GPIO_PORTG_BASE, GPIO_PIN_12
#define GPG13                   GPIO_PORTG_BASE, GPIO_PIN_13
#define GPG14                   GPIO_PORTG_BASE, GPIO_PIN_14
#define GPG15                   GPIO_PORTG_BASE, GPIO_PIN_15

#define GPH0                    GPIO_PORTH_BASE, GPIO_PIN_0
#define GPH1                    GPIO_PORTH_BASE, GPIO_PIN_1
#define GPH2                    GPIO_PORTH_BASE, GPIO_PIN_2
#define GPH3                    GPIO_PORTH_BASE, GPIO_PIN_3
#define GPH4                    GPIO_PORTH_BASE, GPIO_PIN_4
#define GPH5                    GPIO_PORTH_BASE, GPIO_PIN_5
#define GPH6                    GPIO_PORTH_BASE, GPIO_PIN_6
#define GPH7                    GPIO_PORTH_BASE, GPIO_PIN_7
#define GPH8                    GPIO_PORTH_BASE, GPIO_PIN_8
#define GPH9                    GPIO_PORTH_BASE, GPIO_PIN_9
#define GPH10                   GPIO_PORTH_BASE, GPIO_PIN_10
#define GPH11                   GPIO_PORTH_BASE, GPIO_PIN_11
#define GPH12                   GPIO_PORTH_BASE, GPIO_PIN_12
#define GPH13                   GPIO_PORTH_BASE, GPIO_PIN_13
#define GPH14                   GPIO_PORTH_BASE, GPIO_PIN_14
#define GPH15                   GPIO_PORTH_BASE, GPIO_PIN_15

#define GPI0                    GPIO_PORTI_BASE, GPIO_PIN_0
#define GPI1                    GPIO_PORTI_BASE, GPIO_PIN_1
#define GPI2                    GPIO_PORTI_BASE, GPIO_PIN_2
#define GPI3                    GPIO_PORTI_BASE, GPIO_PIN_3
#define GPI4                    GPIO_PORTI_BASE, GPIO_PIN_4
#define GPI5                    GPIO_PORTI_BASE, GPIO_PIN_5
#define GPI6                    GPIO_PORTI_BASE, GPIO_PIN_6
#define GPI7                    GPIO_PORTI_BASE, GPIO_PIN_7
#define GPI8                    GPIO_PORTI_BASE, GPIO_PIN_8
#define GPI9                    GPIO_PORTI_BASE, GPIO_PIN_9
#define GPI10                   GPIO_PORTI_BASE, GPIO_PIN_10
#define GPI11                   GPIO_PORTI_BASE, GPIO_PIN_11
#define GPI12                   GPIO_PORTI_BASE, GPIO_PIN_12
#define GPI13                   GPIO_PORTI_BASE, GPIO_PIN_13
#define GPI14                   GPIO_PORTI_BASE, GPIO_PIN_14
#define GPI15                   GPIO_PORTI_BASE, GPIO_PIN_15

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_Pin_Config NUC4xx GPIO Pin Config
//! \brief Values that can be passed to xGPIOPinConfigure as the ulPinConfig 
//! parameter.
//! |31 ... 29| 28... 24| 23 -- 21|19....16| 15....12 | 11... 8 | 7-6  | 5-4  | 3-- 0       |
//! |A2 status|A2 shift |A1 status|A1 shift|port index|pin index|A2 sel|A1 sel| GPIO statues|
//! @{
//
//*****************************************************************************

//
//! GPIO pin A0
//
#define GPIO_PA0_GPIO           0x00000000
#define GPIO_PA0_TAMPER0        0x00000001
#define GPIO_PA0_SC0CD          0x00000002
#define GPIO_PA0_CAN1RX         0x00000003
#define GPIO_PA0_INT0           0x00000008

//
//! GPIO pin A1
//
#define GPIO_PA1_GPIO           0x00000100
#define GPIO_PA1_TAMPER0        0x00000101
#define GPIO_PA1_SC5CD          0x00000102
#define GPIO_PA1_CAN1TX         0x00000103
#define GPIO_PA1_EBIA22         0x00000107

//
//! GPIO pin A2
//
#define GPIO_PA2_GPIO           0x00000210
#define GPIO_PA2_SC2DAT         0x00000211
#define GPIO_PA2_SPI3MISO       0x00000212
#define GPIO_PA2_I2S0RXMCLK     0x00000213
#define GPIO_PA2_I2S0TXMCLK     0x00000213
#define GPIO_PA2_BRAKE11        0x00000214
#define GPIO_PA2_CAPSFILED      0x00000215
#define GPIO_PA2_EBIA12         0x00000217

//
//! GPIO pin A3
//
#define GPIO_PA3_GPIO           0x00000310
#define GPIO_PA3_SC2CLK         0x00000311
#define GPIO_PA3_SPI3MOSI       0x00000312
#define GPIO_PA3_I2S0TXSD       0x00000313
#define GPIO_PA3_BRAKE10        0x00000314
#define GPIO_PA3_EBIA13         0x00000317

//
//! GPIO pin A4
//
#define GPIO_PA4_GPIO           0x00000410
#define GPIO_PA4_SC2PWR         0x00000411
#define GPIO_PA4_SPI3CLK        0x00000412
#define GPIO_PA4_I2S0RXSD       0x00000413
#define GPIO_PA4_QEI1Z          0x00000415
#define GPIO_PA4_EBIA14         0x00000417
#define GPIO_PA4_ECAP1IC2       0x00000418

//
//! GPIO pin A5
//
#define GPIO_PA5_GPIO           0x00000510
#define GPIO_PA5_SC2RST         0x00000511
#define GPIO_PA5_SPI3CS         0x00000512
#define GPIO_PA5_I2S0RXSCK      0x00000513
#define GPIO_PA5_I2S0TXSCK      0x00000513
#define GPIO_PA5_PWM0           0x00000514
#define GPIO_PA5_QEI1B          0x00000515
#define GPIO_PA5_EBIA15         0x00000517
#define GPIO_PA5_ECAP1IC1       0x00000518

//
//! GPIO pin A6
//
#define GPIO_PA6_GPIO           0x00000610
#define GPIO_PA6_SC2CD          0x00000611
#define GPIO_PA6_I2S0RXWS       0x00000613
#define GPIO_PA6_I2S0TXWS       0x00000613
#define GPIO_PA6_PWM1           0x00000614
#define GPIO_PA6_QEI1A          0x00000615
#define GPIO_PA6_CAN1TX         0x00000616
#define GPIO_PA6_EBIA16         0x00000617
#define GPIO_PA6_ECAP1IC0       0x00000618

//
//! GPIO pin A7
//
#define GPIO_PA7_GPIO           0x00000710
#define GPIO_PA7_SC0CLK         0x00000712
#define GPIO_PA7_SPI3CS         0x00000713
#define GPIO_PA7_PWM9           0x00000714
#define GPIO_PA7_EPWM5          0x00000715
#define GPIO_PA7_EBIA17         0x00000717


//
//! GPIO pin A8
//
#define GPIO_PA8_GPIO           0x00001010
#define GPIO_PA8_SC0RST         0x00001012
#define GPIO_PA8_SPI3CLK        0x00001013
#define GPIO_PA8_PWM8           0x00001014
#define GPIO_PA8_EPWM4          0x00001015
#define GPIO_PA8_EBIA18         0x00001017

//
//! GPIO pin A9
//
#define GPIO_PA9_GPIO           0x00001110
#define GPIO_PA9_SC0PWR         0x00001112
#define GPIO_PA9_SPI3MISO       0x00001113
#define GPIO_PA9_PWM7           0x00001114
#define GPIO_PA9_EPWM3          0x00001115
#define GPIO_PA9_EBIA19         0x00001117

//
//! GPIO pin A10
//
#define GPIO_PA10_GPIO          0x00001210
#define GPIO_PA10_SC0DAT        0x00001212
#define GPIO_PA10_SPI3MOSI      0x00001213
#define GPIO_PA10_PWM6          0x00001214
#define GPIO_PA10_EPWM2         0x00001215
#define GPIO_PA10_EBIA20        0x00001217

//
//! GPIO pin A11
//
#define GPIO_PA11_GPIO          0x00001310
#define GPIO_PA11_UART0RTS      0x00001311
#define GPIO_PA11_SPI3MISO      0x00001313
#define GPIO_PA11_PWM5          0x00001314
#define GPIO_PA11_EPWM1         0x00001315
#define GPIO_PA11_EBIAD0        0x00001317

//
//! GPIO pin A12
//
#define GPIO_PA12_GPIO          0x00001410
#define GPIO_PA12_UART0CTS      0x00001410
#define GPIO_PA12_SPI3MOSI      0x00001410
#define GPIO_PA12_PWM4          0x00001410
#define GPIO_PA12_EPWM0         0x00001410
#define GPIO_PA12_EBIAD1        0x00001410

//
//! GPIO pin A13
//
#define GPIO_PA13_GPIO          0x00001510
#define GPIO_PA13_UART0RX       0x00001511
#define GPIO_PA13_SC3DAT        0x00001513
#define GPIO_PA13_PWM10         0x00001514
#define GPIO_PA13_EBIAD2        0x00001517

//
//! GPIO pin A14
//
#define GPIO_PA14_GPIO          0x00001610
#define GPIO_PA14_UART0TX       0x00001611
#define GPIO_PA14_SC3CLK        0x00001613
#define GPIO_PA14_PWM11         0x00001614
#define GPIO_PA14_EBIAD3        0x00001617

//
//! GPIO pin A15
//
#define GPIO_PA15_GPIO          0x00001710
#define GPIO_PA15_SC3PWR        0x00001711
#define GPIO_PA15_UART2RTS      0x00001712
#define GPIO_PA15_I2C0SCL       0x00001714
#define GPIO_PA15_EBIA21        0x00001717

//
//! GPIO pin B0
//
#define GPIO_PB0_GPIO           0x00002000
#define GPIO_PB0_USB0VBUSST     0x00002001
#define GPIO_PB0_I2C4SCL        0x00002002
#define GPIO_PB0_INT1           0x00002008

//
//! GPIO pin B1
//
#define GPIO_PB1_GPIO           0x00002100
#define GPIO_PB1_USBVBUSEN      0x00002101
#define GPIO_PB1_I2C4SDA        0x00002102
#define GPIO_PB1_TIMCCP1        0x00002103

//
//! GPIO pin B2
//
#define GPIO_PB2_GPIO           0x00002210
#define GPIO_PB2_UART1RX        0x00002211
#define GPIO_PB2_SPI2CS         0x00002212
#define GPIO_PB2_USB1DN         0x00002213
#define GPIO_PB2_EBIAD4         0x00002217

//
//! GPIO pin B3
//
#define GPIO_PB3_GPIO           0x00002310
#define GPIO_PB3_UART1TX        0x00002311
#define GPIO_PB3_SPI2CLK        0x00002312
#define GPIO_PB3_USB1DP         0x00002313
#define GPIO_PB3_EBIAD5         0x00002317

//
//! GPIO pin B4
//
#define GPIO_PB4_GPIO           0x00002410
#define GPIO_PB4_UART1RTS       0x00002411
#define GPIO_PB4_SPI2MISO       0x00002412
#define GPIO_PB4_UART4RX        0x00002413
#define GPIO_PB4_TIMCCP1        0x00002414
#define GPIO_PB4_EBIAD6         0x00002417

//
//! GPIO pin B5
//
#define GPIO_PB5_GPIO           0x00002510
#define GPIO_PB5_UART1CTS       0x00002511
#define GPIO_PB5_SPI2MOSI       0x00002512
#define GPIO_PB5_UART4TX        0x00002513
#define GPIO_PB5_EBIAD7         0x00002517

//
//! GPIO pin B6
//
#define GPIO_PB6_GPIO           0x00002610
#define GPIO_PB6_I2C2SCL        0x00002611
#define GPIO_PB6_BRAKE01        0x00002612
#define GPIO_PB6_UART4RTS       0x00002613
#define GPIO_PB6_PWM10          0x00002614
#define GPIO_PB6_EPWM6          0x00002615
#define GPIO_PB6_EBIAD8         0x00002617

//
//! GPIO pin B7
//
#define GPIO_PB7_GPIO           0x00002710
#define GPIO_PB7_I2C2SDA        0x00002711
#define GPIO_PB7_BRAKE00        0x00002712
#define GPIO_PB7_UART4CTS       0x00002713
#define GPIO_PB7_PWM11          0x00002714
#define GPIO_PB7_EPWM7          0x00002715
#define GPIO_PB7_EBIAD9         0x00002717

//
//! GPIO pin B8
//
#define GPIO_PB8_GPIO           0x00003010
#define GPIO_PB8_UART5CTS       0x00003011
#define GPIO_PB8_EPWM8          0x00003015
#define GPIO_PB8_EBIAD10        0x00003017

//
//! GPIO pin B9
//
#define GPIO_PB9_GPIO           0x00003110
#define GPIO_PB9_UART5RTS       0x00003111
#define GPIO_PB9_EPWM9          0x00003115
#define GPIO_PB9_EBIAD11        0x00003117

//
//! GPIO pin B10
//
#define GPIO_PB10_GPIO          0x00003210
#define GPIO_PB10_UART5TX       0x00003211
#define GPIO_PB10_EPWM10        0x00003215
#define GPIO_PB10_EBIAD12       0x00003217

//
//! GPIO pin B11
//
#define GPIO_PB11_GPIO          0x00003310
#define GPIO_PB11_UART5RX       0x00003311
#define GPIO_PB11_EPWM11        0x00003315
#define GPIO_PB11_EBIAD13       0x00003317

//
//! GPIO pin B12
//
#define GPIO_PB12_GPIO          0x00003410
#define GPIO_PB12_UART4RTS      0x00003411
#define GPIO_PB12_SPI2MISO      0x00003412
#define GPIO_PB12_CAN0RX        0x00003413
#define GPIO_PB12_EMAC_MII_MDC  0x00003416
#define GPIO_PB12_EBIAD14       0x00003417

//
//! GPIO pin B13
//
#define GPIO_PB13_GPIO          0x00003510
#define GPIO_PB13_UART4CTS      0x00003511
#define GPIO_PB13_SPI2MOSI      0x00003512
#define GPIO_PB13_CAN0TX        0x00003513
#define GPIO_PB13_EMAC_MII_MDIO 0x00003516
#define GPIO_PB13_EBIAD15       0x00003517


//
//! GPIO pin B14
//
#define GPIO_PB14_GPIO          0x00003610
#define GPIO_PB14_I2S0TXMCLK    0x00003611
#define GPIO_PB14_I2S0RXMCLK    0x00003611
#define GPIO_PB14_SC1RST        0x00003612
#define GPIO_PB14_BRAKE01       0x00003614
#define GPIO_PB14_EMAC_MII_MDC  0x00003616

//
//! GPIO pin B15
//
#define GPIO_PB15_GPIO          0x00003710
#define GPIO_PB15_I2S1TXSD      0x00003711
#define GPIO_PB15_SC1DAT        0x00003712
#define GPIO_PB15_BRAKE00       0x00003714
#define GPIO_PB15_EMAC_MII_MDIO 0x00003716

//
//! GPIO pin C0
//
#define GPIO_PC0_GPIO           0x00004010
#define GPIO_PC0_I2S1RXSD       0x00004011
#define GPIO_PC0_SC1_DAT        0x00004012
#define GPIO_PC0_UART4RX        0x00004013
#define GPIO_PC0_EMAC_REFCLK    0x00004016
#define GPIO_PC0_INT2           0x00004018
#define GPIO_PC0_EBIMCLK        0x00004017

//
//! GPIO pin C1
//
#define GPIO_PC1_GPIO           0x00004110
#define GPIO_PC1_I2S1RXSCK      0x00004111
#define GPIO_PC1_I2S1TXSCK      0x00004111
#define GPIO_PC1_SC1CLK         0x00004112
#define GPIO_PC1_UART4TX        0x00004113
#define GPIO_PC1_TIMCCP3        0x00004115
#define GPIO_PC1_EMAC_MII_RXERR 0x00004116
#define GPIO_PC1_EBIAD13        0x00004117

//
//! GPIO pin C2
//
#define GPIO_PC2_GPIO           0x00004210
#define GPIO_PC2_I2S1RXWS       0x00004211
#define GPIO_PC2_I2S1TXWS       0x00004211
#define GPIO_PC2_SC1PWR         0x00004212
#define GPIO_PC2_UART4RTS       0x00004213
#define GPIO_PC2_SPI0CS         0x00004214
#define GPIO_PC2_EMAC_MII_RXDV  0x00004216
#define GPIO_PC2_EBIAD12        0x00004217


//
//! GPIO pin C3
//
#define GPIO_PC3_GPIO           0x00004310
#define GPIO_PC3_I2S1TXMCLK     0x00004311
#define GPIO_PC3_I2S1RXMCLK     0x00004311
#define GPIO_PC3_SC1CD          0x00004312
#define GPIO_PC3_UART4CTS       0x00004313
#define GPIO_PC3_SPI0MISO       0x00004314
#define GPIO_PC3_QEI0Z          0x00004315
#define GPIO_PC3_EMAC_MII_RXD1  0x00004316
#define GPIO_PC3_EBIAD11        0x00004317
#define GPIO_PC3_ECAP0IC2       0x00004318

//
//! GPIO pin C4
//
#define GPIO_PC4_GPIO           0x00004410
#define GPIO_PC4_I2S1TXSD       0x00004411
#define GPIO_PC4_SC1RST         0x00004412
#define GPIO_PC4_SPI0MOSI       0x00004414
#define GPIO_PC4_QEI0B          0x00004415
#define GPIO_PC4_EMAC_MII_RXD0  0x00004416
#define GPIO_PC4_EBIAD10        0x00004417
#define GPIO_PC4_ECAP0IC1       0x00004418

//
//! GPIO pin C5
//
#define GPIO_PC5_GPIO           0x00004510
#define GPIO_PC5_CLKO           0x00004511
#define GPIO_PC5_QEI0A          0x00004515
#define GPIO_PC5_EMAC_MII_RXCLK 0x00004516
#define GPIO_PC5_EBIMCLK        0x00004516
#define GPIO_PC5_ECAP0IC0       0x00004518


//
//! GPIO pin C6
//
#define GPIO_PC6_GPIO           0x00004610
#define GPIO_PC6_TM2EXT         0x00004611
#define GPIO_PC6_SPI0MISO       0x00004614
#define GPIO_PC6_TIMCCP2        0x00004615
#define GPIO_PC6_EMAC_MII_TXD0  0x00004616
#define GPIO_PC6_EBIAD9         0x00004617


//
//! GPIO pin C7
//
#define GPIO_PC7_GPIO           0x00004710
#define GPIO_PC7_TM1EXT         0x00004711
#define GPIO_PC7_SPI0MOSI       0x00004714
#define GPIO_PC7_EMAC_MII_TXD1  0x00004716
#define GPIO_PC7_EBIAD8         0x00004717

//
//! GPIO pin C8
//
#define GPIO_PC8_GPIO           0x00005010
#define GPIO_PC8_TM0EXT         0x00005011
#define GPIO_PC8_SPI0CLK        0x00005014
#define GPIO_PC8_EMAC_MII_TXEN  0x00005016

//
//! GPIO pin C9
//
#define GPIO_PC9_GPIO           0x00005110
#define GPIO_PC9_STADC          0x00005111
#define GPIO_PC9_UART2CTS       0x00005112
#define GPIO_PC9_SC3RST         0x00005113
#define GPIO_PC9_I2C0SDA        0x00005114
#define GPIO_PC9_CAPDATA1       0x00005115
#define GPIO_PC9_I2C3SCL        0x00005116
#define GPIO_PC9_EBIA22         0x00005117
#define GPIO_PC9_SD1DAT0        0x00005118
#define GPIO_PC9_EBIA6          0x00005119

//
//! GPIO pin C10
//
#define GPIO_PC10_GPIO          0x00005210
#define GPIO_PC10_SC3CD         0x00005211
#define GPIO_PC10_UART2RX       0x00005212
#define GPIO_PC10_PWM2          0x00005214
#define GPIO_PC10_EBIA23        0x00005216
#define GPIO_PC10_EBIAD2        0x00005217


//
//! GPIO pin C11
//
#define GPIO_PC11_GPIO          0x00005310
#define GPIO_PC11_UART2TX       0x00005312
#define GPIO_PC11_PWM3          0x00005314
#define GPIO_PC11_EBIA24        0x00005316
#define GPIO_PC11_EBIAD3        0x00005317

//
//! GPIO pin C12
//
#define GPIO_PC12_GPIO          0x00005410
#define GPIO_PC12_SPI1CS        0x00005411
#define GPIO_PC12_SC4CD         0x00005412
#define GPIO_PC12_SD1CDN        0x00005414
#define GPIO_PC12_CAPDATA7      0x00005415
#define GPIO_PC12_EBIA0         0x00005417

//
//! GPIO pin C13
//
#define GPIO_PC13_GPIO          0x00005510
#define GPIO_PC13_SPI1MOSI      0x00005511
#define GPIO_PC13_SC4RST        0x00005512
#define GPIO_PC13_SD1CMD        0x00005514
#define GPIO_PC13_CAPDATA6      0x00005515
#define GPIO_PC13_EBIA1         0x00005517

//
//! GPIO pin C14
//
#define GPIO_PC14_GPIO          0x00005610
#define GPIO_PC14_SPI1MOSI      0x00005611
#define GPIO_PC14_SC4RST        0x00005612
#define GPIO_PC14_TM3EXT        0x00005613
#define GPIO_PC14_SD1CLK        0x00005614
#define GPIO_PC14_CAPDATA5      0x00005615
#define GPIO_PC14_EBIA2         0x00005617

//
//! GPIO pin C15
//
#define GPIO_PC15_GPIO          0x00005710
#define GPIO_PC15_SPI1MOSI      0x00005711
#define GPIO_PC15_SC4DAT        0x00005712
#define GPIO_PC15_SD1DAT3       0x00005714
#define GPIO_PC15_CAPDATA4      0x00005715
#define GPIO_PC15_EBIA3         0x00005717

//
//! GPIO pin D0
//
#define GPIO_PD0_GPIO           0x00006010
#define GPIO_PD0_SPI1MISO       0x00006011
#define GPIO_PD0_SC4CLK         0x00006012
#define GPIO_PD0_SD1DAT2        0x00006014
#define GPIO_PD0_CAPDATA3       0x00006015
#define GPIO_PD0_EBIA4          0x00006017
#define GPIO_PD0_INT3           0x00006018

//
//! GPIO pin D1
//
#define GPIO_PD1_GPIO           0x00006110
#define GPIO_PD1_SPI1CLK        0x00006111
#define GPIO_PD1_TIMCCP0        0x00006113
#define GPIO_PD1_SD1DAT1        0x00006114
#define GPIO_PD1_CAPDATA2       0x00006115
#define GPIO_PD1_EBIA5          0x00006117

//
//! GPIO pin D2
//
#define GPIO_PD2_GPIO           0x00006210
#define GPIO_PD2_STADC          0x00006211
#define GPIO_PD2_I2C3SCL        0x00006212
#define GPIO_PD2_SD1DAT0        0x00006214
#define GPIO_PD2_CAPDATA1       0x00006215
#define GPIO_PD2_EBIA6          0x00006217

//
//! GPIO pin D3
//
#define GPIO_PD3_GPIO           0x00006310
#define GPIO_PD3_SC5CLK         0x00006311
#define GPIO_PD3_I2C3SDA        0x00006312
#define GPIO_PD3_CMP2O          0x00006313
#define GPIO_PD3_SD0CDN         0x00006314
#define GPIO_PD3_CAPDATA0       0x00006315
#define GPIO_PD3_EBIA7          0x00006317

//
//! GPIO pin D4
//
#define GPIO_PD4_GPIO           0x00006410
#define GPIO_PD4_SC5CD          0x00006411
#define GPIO_PD4_UART3RX        0x00006412
#define GPIO_PD4_CMP1O          0x00006413
#define GPIO_PD4_CAPSCLK        0x00006415
#define GPIO_PD4_EBIA8          0x00006417

//
//! GPIO pin D5
//
#define GPIO_PD5_GPIO           0x00006510
#define GPIO_PD5_SC5RST         0x00006510
#define GPIO_PD5_UART3TX        0x00006510
#define GPIO_PD5_CAPVSYNC       0x00006510
#define GPIO_PD5_EBIA9          0x00006510

//
//! GPIO pin D6
//
#define GPIO_PD6_GPIO           0x00006610
#define GPIO_PD6_SC5PWR         0x00006611
#define GPIO_PD6_UART3RTS       0x00006612
#define GPIO_PD6_SD0CMD         0x00006614
#define GPIO_PD6_CAPHSYNC       0x00006615
#define GPIO_PD6_EBIA10         0x00006617

//
//! GPIO pin D7
//
#define GPIO_PD7_GPIO           0x00006710
#define GPIO_PD7_SC5DAT         0x00006711
#define GPIO_PD7_UART3CTS       0x00006712
#define GPIO_PD7_SD0CLK         0x00006714
#define GPIO_PD7_CAPPIXCLK      0x00006715
#define GPIO_PD7_EBIA11         0x00006717

//
//! GPIO pin D8
//
#define GPIO_PD8_GPIO           0x00007010
#define GPIO_PD8_SPI3MISO       0x00007011
#define GPIO_PD8_I2C0SCL        0x00007012

//
//! GPIO pin D9
//
#define GPIO_PD9_GPIO           0x00007110
#define GPIO_PD9_SPI3MOSI       0x00007111
#define GPIO_PD9_I2C0SDA        0x00007112

//
//! GPIO pin D10
//
#define GPIO_PD10_GPIO          0x00007210
#define GPIO_PD10_SC3DA         0x00007211
#define GPIO_PD10_I2C4SCL       0x00007212

//
//! GPIO pin D11
//
#define GPIO_PD11_GPIO          0x00007310
#define GPIO_PD11_SC3RST        0x00007311
#define GPIO_PD11_TIMCCP3       0x00007313

//
//! GPIO pin D12
//
#define GPIO_PD12_GPIO          0x00007410
#define GPIO_PD12_SC3CLK        0x00007411
#define GPIO_PD12_I2C4SDA       0x00007412

//
//! GPIO pin D13
//
#define GPIO_PD13_GPIO          0x00007510
#define GPIO_PD13_SPI1CS        0x00007511
#define GPIO_PD13_UART5CTS      0x00007512
#define GPIO_PD13_ECAP0IC2      0x00007513

//
//! GPIO pin D14
//
#define GPIO_PD14_GPIO          0x00007610
#define GPIO_PD14_SPI1CLK       0x00007611
#define GPIO_PD14_UART5RTS      0x00007612
#define GPIO_PD14_ECAP0IC1      0x00007613

//
//! GPIO pin D15
//
#define GPIO_PD15_GPIO          0x00007710
#define GPIO_PD15_SPI1MISO      0x00007711
#define GPIO_PD15_UART5TX       0x00007712
#define GPIO_PD15_ECAP0IC0      0x00007713

//
//! GPIO pin E0
//
#define GPIO_PE0_GPIO           0x00008000
#define GPIO_PE0_ADC0           0x00008001
#define GPIO_PE0_INT4           0x00008008

//
//! GPIO pin E1
//
#define GPIO_PE1_GPIO           0x00008100
#define GPIO_PE1_ADC1           0x00008101
#define GPIO_PE1_TIMCCP2        0x00008103


//
//! GPIO pin E2
//
#define GPIO_PE2_GPIO           0x00008210
#define GPIO_PE2_ADC2           0x00008211
#define GPIO_PE2_CMP0O          0x00008212
#define GPIO_PE2_SPI0MISO       0x00008213

//
//! GPIO pin E3
//
#define GPIO_PE3_GPIO           0x00008310
#define GPIO_PE3_ADC3           0x00008311
#define GPIO_PE3_CMP0P          0x00008312
#define GPIO_PE3_SPI0MOSI       0x00008313

//
//! GPIO pin E4
//
#define GPIO_PE4_GPIO           0x00008410
#define GPIO_PE4_ADC4           0x00008411
#define GPIO_PE4_CMP0P          0x00008412
#define GPIO_PE4_SPI0CS         0x00008413

//
//! GPIO pin E5
//
#define GPIO_PE5_GPIO           0x00008510
#define GPIO_PE5_ADC5           0x00008511
#define GPIO_PE5_CMP0P          0x00008512
#define GPIO_PE5_SPI0CLK        0x00008513
#define GPIO_PE5_SD0CDN         0x00008514

//
//! GPIO pin E6
//
#define GPIO_PE6_GPIO           0x00008610
#define GPIO_PE6_ADC6           0x00008611
#define GPIO_PE6_CMP0P          0x00008612
#define GPIO_PE6_SPI0MISO       0x00008613
#define GPIO_PE6_SD0CMD         0x00008614
#define GPIO_PE6_EBINWR         0x00008617

//
//! GPIO pin E7
//
#define GPIO_PE7_GPIO           0x00008710
#define GPIO_PE7_ADC7           0x00008711
#define GPIO_PE7_CMP0N          0x00008712
#define GPIO_PE7_SPI0MOSI       0x00008713
#define GPIO_PE7_SD0CLK         0x00008714
#define GPIO_PE7_EBINRD         0x00008717

//
//! GPIO pin E8
//
#define GPIO_PE8_GPIO           0x00009010
#define GPIO_PE8_ADC8           0x00009011
#define GPIO_PE8_ADC12          0x00009011
#define GPIO_PE8_CMP1N          0x00009012
#define GPIO_PE8_TIMCCP1        0x00009013
#define GPIO_PE8_SD0DAT3        0x00009014
#define GPIO_PE8_EBIALE         0x00009017

//
//! GPIO pin E9
//
#define GPIO_PE9_GPIO           0x00009110
#define GPIO_PE9_ADC9           0x00009111
#define GPIO_PE9_ADC13          0x00009111
#define GPIO_PE9_CMP1P          0x00009112
#define GPIO_PE9_SD0DAT2        0x00009114
#define GPIO_PE9_EBINWRH        0x00009117

//
//! GPIO pin E10
//
#define GPIO_PE10_GPIO          0x00009210
#define GPIO_PE10_ADC10         0x00009211
#define GPIO_PE10_ADC14         0x00009211
#define GPIO_PE10_CMP1P         0x00009212
#define GPIO_PE10_SPI0MISO      0x00009213
#define GPIO_PE10_SD0DAT1       0x00009214
#define GPIO_PE10_EBINWRL       0x00009217

//
//! GPIO pin E11
//
#define GPIO_PE11_GPIO          0x00009310
#define GPIO_PE11_ADC11         0x00009311
#define GPIO_PE11_ADC15         0x00009311
#define GPIO_PE11_CMP1P         0x00009312
#define GPIO_PE11_SPI0MOSI      0x00009313
#define GPIO_PE11_SD0DAT0       0x00009314
#define GPIO_PE11_CMP2P         0x00009315
#define GPIO_PE11_EBINCS0       0x00009317

//
//! GPIO pin E12
//
#define GPIO_PE12_GPIO          0x00009410
#define GPIO_PE12_ADC16         0x00009411
#define GPIO_PE12_CMP1P         0x00009412
#define GPIO_PE12_CMP2P         0x00009413
#define GPIO_PE12_EBINCS1       0x00009417

//
//! GPIO pin E13
//
#define GPIO_PE13_GPIO          0x00009510
#define GPIO_PE13_ADC17         0x00009511
#define GPIO_PE13_CMP2P         0x00009513
#define GPIO_PE13_EBINCS2       0x00009517

//
//! GPIO pin E14
//
#define GPIO_PE14_GPIO          0x00009610
#define GPIO_PE14_ADC18         0x00009611
#define GPIO_PE14_CMP2P         0x00009613
#define GPIO_PE14_EBINCS3       0x00009617

//
//! GPIO pin E15
//
#define GPIO_PE15_GPIO          0x00009700
#define GPIO_PE15_ADC19         0x00009701
#define GPIO_PE15_CMP2N         0x00009703

//
//! GPIO pin F0
//
#define GPIO_PF0_GPIO           0x0000A010
#define GPIO_PF0_SPI1MOSI       0x0000A011
#define GPIO_PF0_UART5RX        0x0000A012
#define GPIO_PF0_INT5           0x0000A018

//
//! GPIO pin F1
//
#define GPIO_PF1_GPIO           0x0000A110
#define GPIO_PF1_SPI2MOSI       0x0000A111

//
//! GPIO pin F2
//
#define GPIO_PF2_GPIO           0x0000A210
#define GPIO_PF2_SPI3CS         0x0000A211
#define GPIO_PF2_SD0DAT3        0x0000A214
#define GPIO_PF2_EMAC_MII_RXD3  0x0000A216

//
//! GPIO pin F3
//
#define GPIO_PF3_GPIO           0x0000A310
#define GPIO_PF3_SPI3CLK        0x0000A311
#define GPIO_PF3_SD0DAT2        0x0000A314
#define GPIO_PF3_EMAC_MII_RXD2  0x0000A316

//
//! GPIO pin F4
//
#define GPIO_PF4_GPIO           0x0000A410
#define GPIO_PF4_SPI3MISO       0x0000A411
#define GPIO_PF4_SD0DAT1        0x0000A414
#define GPIO_PF4_EMAC_MII_COL0  0x0000A416

//
//! GPIO pin F5
//
#define GPIO_PF5_GPIO           0x0000A510
#define GPIO_PF5_SPI3MOSI       0x0000A511
#define GPIO_PF5_SD0DAT0        0x0000A514
#define GPIO_PF5_EMAC_MII_CRS   0x0000A516

//
//! GPIO pin F6
//
#define GPIO_PF6_GPIO           0x0000A610
#define GPIO_PF6_UART2RX        0x0000A611
#define GPIO_PF6_SD0CDN         0x0000A614
#define GPIO_PF6_EMAC_MII_TXCLK 0x0000A616

//
//! GPIO pin F7
//
#define GPIO_PF7_GPIO           0x0000A710
#define GPIO_PF7_UART2TX        0x0000A711
#define GPIO_PF7_SD0CMD         0x0000A714
#define GPIO_PF7_EMAC_MII_TXD3  0x0000A716

//
//! GPIO pin F8
//
#define GPIO_PF8_GPIO           0x0000B010
#define GPIO_PF8_UART2RTS       0x0000B011
#define GPIO_PF8_SD0CLK         0x0000B014
#define GPIO_PF8_EMAC_MII_TXD2  0x0000B016

//
//! GPIO pin F9
//
#define GPIO_PF9_GPIO           0x0000B110
#define GPIO_PF9_OPA0INP        0x0000B111
#define GPIO_PF9_PWM0           0x0000B114

//
//! GPIO pin F10
//
#define GPIO_PF10_GPIO          0x0000B210
#define GPIO_PF10_OPA0INN       0x0000B211
#define GPIO_PF10_PWM1          0x0000B214

//
//! GPIO pin F11
//
#define GPIO_PF11_GPIO          0x0000B300
#define GPIO_PF11_OPA0O         0x0000B301
#define GPIO_PF11_UART1RTS      0x0000B302

//
//! GPIO pin F12
//
#define GPIO_PF12_GPIO          0x0000B400
#define GPIO_PF12_OPA0INP       0x0000B401
#define GPIO_PF12_UART1CTS      0x0000B402

//
//! GPIO pin F13
//
#define GPIO_PF13_GPIO          0x0000B500
#define GPIO_PF13_OPA0INN       0x0000B501
#define GPIO_PF13_UART1TX       0x0000B502

//
//! GPIO pin F14
//
#define GPIO_PF14_GPIO          0x0000B600
#define GPIO_PF14_OPA0O         0x0000B601
#define GPIO_PF14_UART1RX       0x0000B602

//
//! GPIO pin F15
//
#define GPIO_PF15_GPIO          0x0000B700
#define GPIO_PF15_UART0RTS      0x0000B701


//
//! GPIO pin G0
//
#define GPIO_PG0_GPIO           0x0000C000
#define GPIO_PG0_UART0CTS       0x0000C001
#define GPIO_PG0_INT6           0x0000C008

//
//! GPIO pin G1
//
#define GPIO_PG1_GPIO           0x0000C100
#define GPIO_PG1_UART0RX        0x0000C101

//
//! GPIO pin G2
//
#define GPIO_PG2_GPIO           0x0000C200
#define GPIO_PG2_UART0TX        0x0000C201

//
//! GPIO pin G3
//
#define GPIO_PG3_GPIO           0x0000C300
#define GPIO_PG3_PS2CLK         0x0000C301
#define GPIO_PG3_I2S1TXSD       0x0000C302
#define GPIO_PG3_SC1RST         0x0000C303

//
//! GPIO pin G4
//
#define GPIO_PG4_GPIO           0x0000C400
#define GPIO_PG4_PS2DAT         0x0000C401
#define GPIO_PG4_I2S1RXSD       0x0000C402
#define GPIO_PG4_SC1PWR         0x0000C403

//
//! GPIO pin G5
//
#define GPIO_PG5_GPIO           0x0000C500
#define GPIO_PG5_I2S1RXSCLK     0x0000C502
#define GPIO_PG5_I2S1TXSCLK     0x0000C502
#define GPIO_PG5_SC1DAT         0x0000C503

//
//! GPIO pin G6
//
#define GPIO_PG6_GPIO           0x0000C600
#define GPIO_PG6_I2S1RXWS       0x0000C602
#define GPIO_PG6_I2S1TXWS       0x0000C602
#define GPIO_PG6_SC1CLK         0x0000C603

//
//! GPIO pin G7
//
#define GPIO_PG7_GPIO           0x0000C710
#define GPIO_PG7_SPI2MISO       0x0000C711
#define GPIO_PG7_I2S1RXMCLK     0x0000C712
#define GPIO_PG7_I2S1TXMCLK     0x0000C712
#define GPIO_PG7_SC1CD          0x0000C713
#define GPIO_PG7_SC3RST         0x0000C714

//
//! GPIO pin G8
//
#define GPIO_PG8_GPIO           0x0000D010
#define GPIO_PG8_SPI2MOSI       0x0000D011
#define GPIO_PG8_I2S1TXSD       0x0000D012
#define GPIO_PG8_UART4RTS       0x0000D013
#define GPIO_PG8_SC3DAT         0x0000D014

//
//! GPIO pin G9
//
#define GPIO_PG9_GPIO           0x0000D110
#define GPIO_PG9_SPI2CLK        0x0000D111
#define GPIO_PG9_I2S1RXSD       0x0000D112
#define GPIO_PG9_UART4CTS       0x0000D113
#define GPIO_PG9_SC3CLK         0x0000D114

//
//! GPIO pin G10
//
#define GPIO_PG10_GPIO          0x0000D200
#define GPIO_PG10_ICE_CLK       0x0000D201

//
//! GPIO pin G11
//
#define GPIO_PG11_GPIO          0x0000D300
#define GPIO_PG11_ICE_DAT       0x0000D301

//
//! GPIO pin G12
//
#define GPIO_PG12_GPIO          0x0000D400
#define GPIO_PG12_XT1_OUT       0x0000D401

//
//! GPIO pin G13
//
#define GPIO_PG13_GPIO          0x0000D500
#define GPIO_PG13_XT1_IN        0x0000D501

//
//! GPIO pin G14
//
#define GPIO_PG14_GPIO          0x0000D600
#define GPIO_PG14_X32K_OUT      0x0000D601
#define GPIO_PG14_I2C1SDA       0x0000D603

//
//! GPIO pin G15
//
#define GPIO_PG15_GPIO          0x0000D700
#define GPIO_PG15_X32K_IN       0x0000D701
#define GPIO_PG15_I2C1SCL       0x0000D703

//
//! GPIO pin H0
//
#define GPIO_PH0_GPIO           0x0000E000
#define GPIO_PH0_I2C1SCL        0x0000E001
#define GPIO_PH0_UART4RX        0x0000E002
#define GPIO_PH0_CAN1RX         0x0000E003
#define GPIO_PH0_INT7           0x0000E008

//
//! GPIO pin H1
//
#define GPIO_PH1_GPIO           0x0000E100
#define GPIO_PH1_UART4TX        0x0000E101
#define GPIO_PH1_I2C1SDA        0x0000E102
#define GPIO_PH1_CAN1TX         0x0000E103

//
//! GPIO pin H2
//
#define GPIO_PH2_GPIO           0x0000E200
#define GPIO_PH2_UART4CTS       0x0000E201

//
//! GPIO pin H3
//
#define GPIO_PH3_GPIO           0x0000E300
#define GPIO_PH3_I2C3SCL        0x0000E301

//
//! GPIO pin H4
//
#define GPIO_PH4_GPIO           0x0000E400
#define GPIO_PH4_I2C3SDA        0x0000E401

//
//! GPIO pin H5
//
#define GPIO_PH5_GPIO           0x0000E510
#define GPIO_PH5_SPI2CS         0x0000E511

//
//! GPIO pin H6
//
#define GPIO_PH6_GPIO           0x0000E610
#define GPIO_PH6_SPI2CLK        0x0000E611

//
//! GPIO pin H7
//
#define GPIO_PH7_GPIO           0x0000E710
#define GPIO_PH7_SPI2MISO       0x0000E711

//
//! GPIO pin H8
//
#define GPIO_PH8_GPIO           0x0000F010
#define GPIO_PH8_SPI2MOSI       0x0000F011

//
//! GPIO pin H9
//
#define GPIO_PH9_GPIO           0x0000F110
#define GPIO_PH9_SPI2MISO       0x0000F111

//
//! GPIO pin H10
//
#define GPIO_PH10_GPIO          0x0000F210
#define GPIO_PH10_SPI2MOSI      0x0000F211

//
//! GPIO pin H11
//
#define GPIO_PH11_GPIO          0x0000F300
#define GPIO_PH11_UART3RX       0x0000F301

//
//! GPIO pin H12
//
#define GPIO_PH12_GPIO          0x0000F400
#define GPIO_PH12_UART3TX       0x0000F401

//
//! GPIO pin H13
//
#define GPIO_PH13_GPIO          0x0000F500
#define GPIO_PH13_UART3RTS      0x0000F501

//
//! GPIO pin H14
//
#define GPIO_PH14_GPIO          0x0000F600
#define GPIO_PH14_UART3CTS      0x0000F601

//
//! GPIO pin H15
//
#define GPIO_PH15_GPIO          0x0000F700
#define GPIO_PH15_SC5CLK        0x0000F702

//
//! GPIO pin I0
//
#define GPIO_PI0_GPIO           0x00010000
#define GPIO_PI0_SC5RST         0x00010002

//
//! GPIO pin I1
//
#define GPIO_PI1_GPIO           0x00010100
#define GPIO_PI1_SC5PWR         0x00010102

//
//! GPIO pin I2
//
#define GPIO_PI2_GPIO           0x00010210
#define GPIO_PI2_SC5DAT         0x00010211

//
//! GPIO pin I3
//
#define GPIO_PI3_GPIO           0x00010310
#define GPIO_PI3_SPI3CS         0x00010311

//
//! GPIO pin I4
//
#define GPIO_PI4_GPIO           0x00010410
#define GPIO_PI4_SPI3CLK        0x00010411

//
//! GPIO pin I5
//
#define GPIO_PI5_GPIO           0x00010510
#define GPIO_PI5_SPI3MISO       0x00010511

//
//! GPIO pin I6
//
#define GPIO_PI6_GPIO           0x00010610
#define GPIO_PI6_SPI3MOSI       0x00010611

//
//! GPIO pin I7
//
#define GPIO_PI7_GPIO           0x00010710
#define GPIO_PI7_I2C2SCL        0x00010711
#define GPIO_PI7_SPI3MISO       0x00010712

//
//! GPIO pin I8
//
#define GPIO_PI8_GPIO           0x00011010
#define GPIO_PI8_I2C2SDA        0x00011011
#define GPIO_PI8_SPI3MOSI       0x00011012

//
//! GPIO pin I9
//
#define GPIO_PI9_GPIO           0x00011100
#define GPIO_PI9_I2C4SCL        0x00011104

//
//! GPIO pin I10
//
#define GPIO_PI10_GPIO          0x00011200

//
//! GPIO pin I11
//
#define GPIO_PI11_GPIO          0x00011310
#define GPIO_PI11_SPI2CS        0x00011311
#define GPIO_PI11_I2S1TXSCK     0x00011312
#define GPIO_PI11_I2S1RXSCK     0x00011312
#define GPIO_PI11_I2C4SCL       0x00011313
#define GPIO_PI11_SC3PWR        0x00011314

//
//! GPIO pin I12
//
#define GPIO_PI12_GPIO          0x00011400
#define GPIO_PI12_SPI2MISO      0x00011401
#define GPIO_PI12_I2S1TXWS      0x00011402
#define GPIO_PI12_I2S1RXWS      0x00011402
#define GPIO_PI12_I2C4SDA       0x00011403
#define GPIO_PI12_SC3CD         0x00011404

//
//! GPIO pin I13
//
#define GPIO_PI13_GPIO          0x00011500

//
//! GPIO pin I14
//
#define GPIO_PI14_GPIO          0x00011600

//
//! GPIO pin I15
//
#define GPIO_PI15_GPIO          0x00011700


//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NUC4xx_GPIO_Exported_APIs NUC4xx GPIO API
//! \brief GPIO API Reference.
//! @{
//
//*****************************************************************************

#define GPIOSPinFunctionSet(ulFunction, eShortPin)                            \
        GPIOPinFunctionSet(ulFunction, G##eShortPin)

#define GPIOSPinIntEnable(eShortPin, ulIntType)                               \
        GPIOPinIntEnable(G##eShortPin, ulIntType)

#define GPIOSDirModeSet(eShortPin, ulPinIO)                                  \
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

#define GPIOSPinIntCallbackInit(eShortPin, xtPortCallback)                 \
		GPIOPinIntCallbackInit(G##eShortPin, xtPortCallback)
        
#define GPIOSPinConfigure(ePeripheralPin, eShortPin)    \
		GPIOPinConfigure(G##eShortPin, GPIO_##eShortPin##_##ePeripheralPin)

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
extern void GPIOBitWrite(unsigned long ulPort, unsigned long ulBit,
		                 unsigned char ucVal);
extern void GPIODigitalInputEnable(unsigned long ulPort, unsigned long ulPins);
extern void GPIODigitalInputDisable(unsigned long ulPort, unsigned long ulPins);
extern void GPIOStrongDrivingEnable(unsigned long ulPort, unsigned long ulPins);
extern void GPIOStrongDrivingDisable(unsigned long ulPort, unsigned long ulPins);
extern long GPIOConflictStatusGet(void);
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
//extern void GPIOPinFunctionSet(unsigned long ulFunction, unsigned long ulPort,
//                               unsigned long ulPins);
extern void GPIOPinConfigure(unsigned long ulPort,
        unsigned long ulPin, unsigned long ulPinConfig);
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


