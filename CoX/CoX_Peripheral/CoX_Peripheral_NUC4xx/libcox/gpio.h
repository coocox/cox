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
//! \addtogroup NUC2xx_GPIO
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC2xx_GPIO_General_Pin_IDs NUC2xx GPIO General Pin ID
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
//! \addtogroup NUC2xx_GPIO_General_Pin_Bits NUC2xx GPIO General Pin Bits
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
//! \addtogroup NUC2xx_GPIO_Dir_Mode NUC2xx GPIO Dir Mode
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
//! \addtogroup NUC2xx_GPIO_Int_Type NUC2xx GPIO Int Type
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
//! \addtogroup NUC2xx_GPIO_DBCLK_Src NUC2xx GPIO De-bounce Clock Source
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
//! \addtogroup NUC2xx_GPIO_Function_Set NUC2xx GPIO Function Set
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
//! \addtogroup NUC2xx_GPIO_Pin_Config NUC2xx GPIO Pin Config
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
#define GPIO_PA0_GPIO           0x00020020
#define GPIO_PA0_ADC0           0x00020021
#define GPIO_PA0_SC0PWR         0x00220021

//
//! GPIO pin A1
//
#define GPIO_PA1_GPIO           0x00030120
#define GPIO_PA1_ADC1           0x00030121
#define GPIO_PA1_SC0RST         0x00230121

//
//! GPIO pin A2
//
#define GPIO_PA2_GPIO           0x00000220
#define GPIO_PA2_ADC2           0x00000221
#define GPIO_PA2_SC0CLK         0x00200221

//
//! GPIO pin A3
//
#define GPIO_PA3_GPIO           0x00010320
#define GPIO_PA3_ADC3           0x00010321
#define GPIO_PA3_SC0DAT         0x00210321

//
//! GPIO pin A4
//
#define GPIO_PA4_GPIO           0x00070420
#define GPIO_PA4_ADC4           0x00070421
#define GPIO_PA4_SC1PWR         0x00270421

//
//! GPIO pin A5
//
#define GPIO_PA5_GPIO           0x00080520
#define GPIO_PA5_ADC5           0x00080521
#define GPIO_PA5_SC1RST         0x00280521

//
//! GPIO pin A6
//
#define GPIO_PA6_GPIO           0x00050620
#define GPIO_PA6_ADC6           0x00050621
#define GPIO_PA6_SC1CLK         0x00250621

//
//! GPIO pin A7
//
#define GPIO_PA7_GPIO           0x02060760
#define GPIO_PA7_ADC7           0x02060761
#define GPIO_PA7_SC1DAT         0x02260761
#define GPIO_PA7_SPI2CS         0x22060761

//
//! GPIO pin A8
//
#define GPIO_PA8_GPIO           0x00000800
#define GPIO_PA8_I2C0SDA        0x00000801

//
//! GPIO pin A9
//
#define GPIO_PA9_GPIO           0x00000900
#define GPIO_PA9_I2C0SCK        0x00000901

//
//! GPIO pin A10
//
#define GPIO_PA10_GPIO          0x00000A00
#define GPIO_PA10_I2C1SDA       0x00000A01

//
//! GPIO pin A11
//
#define GPIO_PA11_GPIO          0x00000B00
#define GPIO_PA11_I2C1SCK       0x00000B01

//
//! GPIO pin A12
//
#define GPIO_PA12_GPIO          0x000B0C20
#define GPIO_PA12_PWM0          0x000B0C21
#define GPIO_PA12_SC2DAT        0x002B0C21

//
//! GPIO pin A13
//
#define GPIO_PA13_GPIO          0x000A0D20
#define GPIO_PA13_PWM1          0x000A0D21
#define GPIO_PA13_SC2CLK        0x002A0D21

//
//! GPIO pin A14
//
#define GPIO_PA14_GPIO          0x000D0E20
#define GPIO_PA14_PWM2          0x000D0E21
#define GPIO_PA14_SC2RST        0x002D0E21

//
//! GPIO pin A15
//
#define GPIO_PA15_GPIO          0x090C0F60
#define GPIO_PA15_PWM3          0x090C0F61
#define GPIO_PA15_I2S0TXMCLK    0x290C0F61
#define GPIO_PA15_I2S0RXMCLK    0x290C0F61
#define GPIO_PA15_SC2PWR        0x092C0F61

//
//! GPIO pin B0
//
#define GPIO_PB0_GPIO           0x00001000
#define GPIO_PB0_UART0RX        0x00001001

//
//! GPIO pin B1
//
#define GPIO_PB1_GPIO           0x00001100
#define GPIO_PB1_UART0TX        0x00001101

//
//! GPIO pin B2
//
#define GPIO_PB2_GPIO           0x1A1E1250
#define GPIO_PB2_UART0RTS       0x1A1E1251
#define GPIO_PB2_TIM2EX         0x3A1E1251
#define GPIO_PB2_CMP0O          0x3A1E1251

//
//! GPIO pin B3
//
#define GPIO_PB3_GPIO           0x1B0E1360
#define GPIO_PB3_UART0CTS       0x1B0E1361
#define GPIO_PB3_TIM3EX         0x3B0E1361
#define GPIO_PB3_SC2CD          0x1B2E1361

//
//! GPIO pin B4
//
#define GPIO_PB4_GPIO           0x00001400
#define GPIO_PB4_UART1RX        0x00001401

//
//! GPIO pin B5
//
#define GPIO_PB5_GPIO           0x00001500
#define GPIO_PB5_UART1TX        0x00001501

//
//! GPIO pin B6
//
#define GPIO_PB6_GPIO           0x00001600
#define GPIO_PB6_UART1RTS       0x00001601

//
//! GPIO pin B7
//
#define GPIO_PB7_GPIO           0x00001700
#define GPIO_PB7_UART1CTS       0x00001701

//
//! GPIO pin B8
//
#define GPIO_PB8_GPIO           0x001D1810
#define GPIO_PB8_TIMCCP0        0x001D1811
#define GPIO_PB8_CLKO           0x003D1811

//
//! GPIO pin B9
//
#define GPIO_PB9_GPIO           0x00011910
#define GPIO_PB9_TIMCCP1        0x00011911
#define GPIO_PB9_SPI1CS         0x00211911

//
//! GPIO pin B10
//
#define GPIO_PB10_GPIO          0x00001A10
#define GPIO_PB10_TIMCCP2       0x00001A11
#define GPIO_PB10_SPI0CS        0x00201A11

//
//! GPIO pin B10
//
#define GPIO_PB11_GPIO          0x00041B10
#define GPIO_PB11_TIMCCP3       0x00041B11
#define GPIO_PB11_PWM4          0x00241B11

//
//! GPIO pin B12
//
//#define GPIO_PB12_GPIO          0x0A001C10
//#define GPIO_PB12_SPI1CS        0x0A001C11
//#define GPIO_PB12_CLKO          0x0A011C10

//
//! GPIO pin B13
//
#define GPIO_PB13_GPIO          0x00001D00
#define GPIO_PB13_CMP1O         0x00001D01

//
//! GPIO pin B14
//
#define GPIO_PB14_INT0          0x00031E11
#define GPIO_PB14_GPIO          0x00031E10
#define GPIO_PB14_SPI3CS        0x00231E11

//
//! GPIO pin B15
//
#define GPIO_PB15_GPIO          0x00181F10
#define GPIO_PB15_INT1          0x00181F11
#define GPIO_PB15_TIM0EX        0x00381F11

//
//! GPIO pin C0
//
#define GPIO_PC0_GPIO           0x00052010
#define GPIO_PC0_SPI0CS         0x00052011
#define GPIO_PC0_I2S0LRCLK      0x00252011

//
//! GPIO pin C1
//
#define GPIO_PC1_GPIO           0x00062110
#define GPIO_PC1_SPI0CLK        0x00062111
#define GPIO_PC1_I2S0RXSCK      0x00262111
#define GPIO_PC1_I2S0TXSCK      0x00262111

//
//! GPIO pin C2
//
#define GPIO_PC2_GPIO           0x07002210
#define GPIO_PC2_SPI0MISO       0x07002211
#define GPIO_PC2_I2S0RXSD       0x07012211

//
//! GPIO pin C3
//
#define GPIO_PC3_GPIO           0x00082310
#define GPIO_PC3_SPI0MOSI       0x00082311
#define GPIO_PC3_I2S0TXSD       0x00282311

//
//! GPIO pin C4
//
#define GPIO_PC4_GPIO           0x00002400
#define GPIO_PC4_SPI0MISO       0x00002401

//
//! GPIO pin C5
//
#define GPIO_PC5_GPIO           0x00002500
#define GPIO_PC5_SPI0MOSI       0x00002501

//
//! GPIO pin C6
//
#define GPIO_PC6_GPIO           0x00042620
#define GPIO_PC6_CMP0P          0x00042621
#define GPIO_PC6_SC0CD          0x00242621

//
//! GPIO pin C7
//
#define GPIO_PC7_GPIO           0x00092720
#define GPIO_PC7_CMP0N          0x00092721
#define GPIO_PC7_SC1CD          0x00292721


//
//! GPIO pin C8
//
#define GPIO_PC8_GPIO           0x00002800
#define GPIO_PC8_SPI1CS         0x00002801

//
//! GPIO pin C9
//
#define GPIO_PC9_GPIO           0x00002900
#define GPIO_PC9_SPI1CLK        0x00002901

//
//! GPIO pin C10
//
#define GPIO_PC10_GPIO          0x00002A00
#define GPIO_PC10_SPI1MISO      0x00002A01

//
//! GPIO pin C11
//
#define GPIO_PC11_GPIO          0x00002B00
#define GPIO_PC11_SPI1MOSI      0x00002B01

//
//! GPIO pin C12
//
#define GPIO_PC12_GPIO          0x00002C00
#define GPIO_PC12_SPI1MISO      0x00002C01

//
//! GPIO pin C13
//
#define GPIO_PC13_GPIO          0x00002D00
#define GPIO_PC13_SPI1MOSI      0x00002D01

//
//! GPIO pin C14
//
#define GPIO_PC14_GPIO          0x00002E00
#define GPIO_PC14_CMP1P         0x00002E01

//
//! GPIO pin C15
//
#define GPIO_PC15_GPIO          0x00002F00
#define GPIO_PC15_CMP1N         0x00002F01

//
//! GPIO pin D0
//
#define GPIO_PD0_GPIO           0x00003000
#define GPIO_PD0_SPI2CS         0x00003001

//
//! GPIO pin D1
//
#define GPIO_PD1_GPIO           0x00003100
#define GPIO_PD1_SPI2CLK        0x00003101

//
//! GPIO pin D2
//
#define GPIO_PD2_GPIO           0x00003200
#define GPIO_PD2_SPI2MISO       0x00003201

//
//! GPIO pin D3
//
#define GPIO_PD3_GPIO           0x00003300
#define GPIO_PD3_SPI2MOSI       0x00003301

//
//! GPIO pin D4
//
#define GPIO_PD4_GPIO           0x00003400
#define GPIO_PD4_SPI2MISO       0x00003401

//
//! GPIO pin D5
//
#define GPIO_PD5_GPIO           0x00003510
#define GPIO_PD5_SPI2MOSI       0x00003511

//
//! GPIO pin D8
//
#define GPIO_PD8_GPIO           0x00003800
#define GPIO_PD8_SPI3CS         0x00003801

//
//! GPIO pin D9
//
#define GPIO_PD9_GPIO           0x00003900
#define GPIO_PD9_SPI3CLK        0x00003901

//
//! GPIO pin D10
//
#define GPIO_PD10_GPIO          0x00003A00
#define GPIO_PD10_SPI3MISO      0x00003A01

//
//! GPIO pin D11
//
#define GPIO_PD11_GPIO          0x00003B00
#define GPIO_PD11_SPI3MOSI      0x00003B01

//
//! GPIO pin D12
//
#define GPIO_PD12_GPIO          0x00003C00
#define GPIO_PD12_SPI3MISO      0x00003C01

//
//! GPIO pin D13
//
#define GPIO_PD13_GPIO          0x00003D00
#define GPIO_PD13_SPI3MOSI      0x00003D01

//
//! GPIO pin D14
//
#define GPIO_PD14_GPIO          0x00003E00
#define GPIO_PD14_UART2RX       0x00003E01

//
//! GPIO pin D15
//
#define GPIO_PD15_GPIO          0x00003F00
#define GPIO_PD15_UART2TX       0x00003F01

//
//! GPIO pin E0
//
#define GPIO_PE0_GPIO           0x00004000
#define GPIO_PE0_PWM6           0x00004001

//
//! GPIO pin E1
//
#define GPIO_PE1_GPIO           0x00004100
#define GPIO_PE1_PWM7           0x00004101

//
//! GPIO pin E5
//
#define GPIO_PE5_GPIO           0x00194510
#define GPIO_PE5_PWM5           0x00194511
#define GPIO_PE5_TIM1EXT        0x00394511

//
//! GPIO pin F0
//
#define GPIO_PF0_GPIO           0x00005000
#define GPIO_PF0_XT1OUT         0x00005001

//
//! GPIO pin F1
//
#define GPIO_PF1_GPIO           0x00005100
#define GPIO_PF1_XT1IN          0x00005101

//
//! GPIO pin F2
//
#define GPIO_PF2_GPIO           0x00005200
#define GPIO_PF2_PS2DAT         0x00005201

//
//! GPIO pin F3
//
#define GPIO_PF3_GPIO           0x00005300
#define GPIO_PF3_PS2CLK         0x00005301


//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NUC2xx_GPIO_Exported_APIs NUC2xx GPIO API
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


