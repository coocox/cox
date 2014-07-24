#ifndef _NUC1XX_GPIO_H_
#define _NUC1XX_GPIO_H_

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
//! \addtogroup NUC1xx_GPIO_GP_Short_Pin NUC1xx General Purpose Short Pin
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

#endif
