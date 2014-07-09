//*****************************************************************************
//
//! \file gpio.h
//! \brief Prototypes for the GPIO Driver.
//! \brief Prototypes for the AFIO Driver.
//! \version V2.1.1.0
//! \date 12/23/2011
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
//! \addtogroup M051_GPIO
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_GPIO_General_Pin_IDs M051 GPIO General Pin ID
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
//! \addtogroup M051_GPIO_General_Pin_Bits M051 GPIO General Pin Bits
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
//! \addtogroup M051_GPIO_Dir_Mode M051 GPIO Dir Mode
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
//! \addtogroup M051_GPIO_Int_Type M051 GPIO Int Type
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
//! \addtogroup M051_GPIO_DBCLK_Src M051 GPIO De-bounce Clock Source
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
//! \addtogroup M051_GPIO_Function_Set M051 GPIO Function Set
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
#define GPIO_FUNCTION_EBI       0x00000009
#define GPIO_FUNCTION_CLKO      0x0000000A

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_GPIO_Pin_Config M051 GPIO Pin Config
//! \brief Values that can be passed to xGPIOPinConfigure as the ulPinConfig 
//! parameter.
//! @{
//
//*****************************************************************************

//
//! GPIO pin A0
//
#define GPIO_PA0_AD0            0x00000001
#define GPIO_PA0_UART1CTS       0x00000010
#define GPIO_PA0_UART1TX        0x00000011
#define GPIO_PA0_CMP3P          0x10000011

//
//! GPIO pin A1
//
#define GPIO_PA1_AD1            0x00000101
#define GPIO_PA1_UART1RTS       0x00000110
#define GPIO_PA1_UART1RX        0x00000111
#define GPIO_PA1_CMP3N          0x10000111

//
//! GPIO pin A2
//
#define GPIO_PA2_AD2            0x00000201
#define GPIO_PA2_UART0CTS       0x00000210
#define GPIO_PA2_UART0TX        0x00000211

//
//! GPIO pin A3
//
#define GPIO_PA3_AD3            0x00000301
#define GPIO_PA3_UART0RTS       0x00000310
#define GPIO_PA3_UART0RX        0x00000311

//
//! GPIO pin A4
//
#define GPIO_PA4_AD4            0x00000401
#define GPIO_PA4_SPI1CS         0x00000410

//
//! GPIO pin A5
//
#define GPIO_PA5_AD5            0x00000501
#define GPIO_PA5_SPI1MOSI       0x00000510

//
//! GPIO pin A6
//
#define GPIO_PA6_AD6            0x00000601
#define GPIO_PA6_SPI1MISO       0x00000610

//
//! GPIO pin A7
//
#define GPIO_PA7_AD7            0x00000701
#define GPIO_PA7_SPI1CLK        0x00000710

//
//! GPIO pin B0
//
#define GPIO_PB0_ADC0           0x00001001
#define GPIO_PB0_TIMCCP2        0x00001010
#define GPIO_PB0_EBINWRL        0x00001011

//
//! GPIO pin B1
//
#define GPIO_PB1_ADC1           0x00001101
#define GPIO_PB1_TIMCCP3        0x00001110
#define GPIO_PB1_EBINWRH        0x00001111

//
//! GPIO pin B2
//
#define GPIO_PB2_ADC2           0x00001201
#define GPIO_PB2_UART1RX        0x00001210

//
//! GPIO pin B3
//
#define GPIO_PB3_ADC3           0x00001301
#define GPIO_PB3_UART1TX        0x00001310

//
//! GPIO pin B4
//
#define GPIO_PB4_ADC4           0x00001401
#define GPIO_PB4_SPI0CS         0x00001410
#define GPIO_PB4_CMP0N          0x00001411

//
//! GPIO pin B5
//
#define GPIO_PB5_ADC5           0x00001501
#define GPIO_PB5_SPI0MOSI       0x00001510
#define GPIO_PB5_CMP0P          0x00001511

//
//! GPIO pin B6
//
#define GPIO_PB6_ADC6           0x00001601
#define GPIO_PB6_SPI0MISO       0x00001610
#define GPIO_PB6_CMP2N          0x00001611

//
//! GPIO pin B7
//
#define GPIO_PB7_ADC7           0x00001701
#define GPIO_PB7_SPI0CLK        0x00001710
#define GPIO_PB7_CMP2P          0x00001711

//
//! GPIO pin C0
//
#define GPIO_PC0_AD8            0x00002001
#define GPIO_PC0_PWM0           0x00002010

//
//! GPIO pin C1
//
#define GPIO_PC1_AD9            0x00002101
#define GPIO_PC1_PWM1           0x00002110

//
//! GPIO pin C2
//
#define GPIO_PC2_AD10           0x00002201
#define GPIO_PC2_PWM2           0x00002210

//
//! GPIO pin C3
//
#define GPIO_PC3_AD11           0x00002301
#define GPIO_PC3_PWM3           0x00002310

//
//! GPIO pin C4
//
#define GPIO_PC4_AD12           0x00002401
#define GPIO_PC4_PWM4           0x00002410
#define GPIO_PC4_I2C1SCL        0x00002411

//
//! GPIO pin C5
//
#define GPIO_PC5_AD13           0x00002501
#define GPIO_PC5_PWM5           0x00002510
#define GPIO_PC5_I2C1SDA        0x00002511

//
//! GPIO pin C6
//
#define GPIO_PC6_AD14           0x00002601
#define GPIO_PC6_PWM6           0x00002610
#define GPIO_PC6_CMP1O          0x00002611

//
//! GPIO pin C7
//
#define GPIO_PC7_AD15           0x00002701
#define GPIO_PC7_PWM7           0x00002710

//
//! GPIO pin D0
//
#define GPIO_PD0_UART0RX        0x00003001
#define GPIO_PD0_CMP1N          0x00003010

//
//! GPIO pin D1
//
#define GPIO_PD1_UART0TX        0x00003101
#define GPIO_PD1_CMP1P          0x00003110

//
//! GPIO pin D2
//
#define GPIO_PD2_NINT0          0x00003201
#define GPIO_PD2_T0EX           0x00003210

//
//! GPIO pin D3
//
#define GPIO_PD3_NINT1          0x00003301
#define GPIO_PD3_EBIMCLK        0x00003310
#define GPIO_PD3_T1EX           0x00003311

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
#define GPIO_PD5_CLKO           0x00003511

//
//! GPIO pin D6
//
#define GPIO_PD6_EBINWR         0x00003601
#define GPIO_PD6_CLK0           0x00003610
#define GPIO_PD6_CMP0O          0x00003611

//
//! GPIO pin D7
//
#define GPIO_PD7_EBINRD         0x00003701

//
//! GPIO pin E0
//
#define GPIO_PE0_PWM0           0x00004001
#define GPIO_PE0_T2EX           0x00004010

//
//! GPIO pin E1
//
#define GPIO_PE1_PWM1           0x00004101
#define GPIO_PE1_T3EX           0x00004110

//
//! GPIO pin E2
//
#define GPIO_PE2_PWM2           0x00004201

//
//! GPIO pin E3
//
#define GPIO_PE3_PWM3           0x00004301

//
//! GPIO pin E4
//
#define GPIO_PE4_EBINCS         0x00004401
#define GPIO_PE4_I2C1SCL        0x00004410

//
//! GPIO pin E5
//
#define GPIO_PE5_EBIALE         0x00004501
#define GPIO_PE5_I2C1SDA        0x00004510

//
//! GPIO pin E6
//
#define GPIO_PE6_ICECLK         0x00004601

//
//! GPIO pin E7
//
#define GPIO_PE7_ICEDAT         0x00004701

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup M051_GPIO_Exported_APIs M051 GPIO API
//! \brief GPIO API Reference.
//! @{
//
//*****************************************************************************

#define GPIOSPinIntCallbackInit(eShortPin, pfnCallback)                       \
		GPIOPinIntCallbackInit(G##eShortPin, pfnCallback)

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


