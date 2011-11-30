//*****************************************************************************
//
//! \file DrvGPIO.h
//! \brief Defines and Macros for GPIO API.
//! \version v1.02.002
//! \date 09/05/2011
//! \author Nuvoton
//! \copy
//!
//! Copyright (c)  2011, Nuvoton 
//! All rights reserved.
//*****************************************************************************
#ifndef DRVGPIO_H
#define DRVGPIO_H

//*****************************************************************************
//
//! Include related headers
//
//*****************************************************************************
#include "MINI51.h"

//*****************************************************************************
//
//!  Define Version number 
//
//*****************************************************************************
#define DRVGPIO_MAJOR_NUM       1
#define DRVGPIO_MINOR_NUM       00
#define DRVGPIO_BUILD_NUM       001

//*****************************************************************************
//
//!  Version define with SysInfra 
//
//*****************************************************************************
#define DRVGPIO_VERSION_NUM     _SYSINFRA_VERSION(DRVGPIO_MAJOR_NUM, DRVGPIO_MINOR_NUM, DRVGPIO_BUILD_NUM)

//*****************************************************************************                            
//
//!  Define Error Code 
//
//*****************************************************************************
#define E_DRVGPIO_ARGUMENT      _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVGPIO, 1)
#define E_DRVGPIO_GROUP_PIN     _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVGPIO, 2)
#define E_DRVGPIO_BUSY          _SYSINFRA_ERRCODE(TRUE, MODULE_ID_DRVGPIO, 3)   

//*****************************************************************************
//
//! Define GPIO[n] Pin I/O Bit Output Control.
//
//*****************************************************************************
#define _PORT_DOUT(PortNum, PinNum)      (*((__IO uint32_t *) ((GPIOBIT0_BASE+(0x20*PortNum)) + (0x4*PinNum))))    
#define P00_DOUT                _PORT_DOUT(0, 0)
#define P01_DOUT                _PORT_DOUT(0, 1)
#define P02_DOUT                _PORT_DOUT(0, 2)
#define P03_DOUT                _PORT_DOUT(0, 3)
#define P04_DOUT                _PORT_DOUT(0, 4)
#define P05_DOUT                _PORT_DOUT(0, 5)
#define P06_DOUT                _PORT_DOUT(0, 6)
#define P07_DOUT                _PORT_DOUT(0, 7)
#define P10_DOUT                _PORT_DOUT(1, 0)
#define P11_DOUT                _PORT_DOUT(1, 1)
#define P12_DOUT                _PORT_DOUT(1, 2)
#define P13_DOUT                _PORT_DOUT(1, 3)
#define P14_DOUT                _PORT_DOUT(1, 4)
#define P15_DOUT                _PORT_DOUT(1, 5)
#define P16_DOUT                _PORT_DOUT(1, 6)
#define P17_DOUT                _PORT_DOUT(1, 7)
#define P20_DOUT                _PORT_DOUT(2, 0)
#define P21_DOUT                _PORT_DOUT(2, 1)
#define P22_DOUT                _PORT_DOUT(2, 2)
#define P23_DOUT                _PORT_DOUT(2, 3)
#define P24_DOUT                _PORT_DOUT(2, 4)
#define P25_DOUT                _PORT_DOUT(2, 5)
#define P26_DOUT                _PORT_DOUT(2, 6)
#define P27_DOUT                _PORT_DOUT(2, 7)
#define P30_DOUT                _PORT_DOUT(3, 0)
#define P31_DOUT                _PORT_DOUT(3, 1)
#define P32_DOUT                _PORT_DOUT(3, 2)
#define P33_DOUT                _PORT_DOUT(3, 3)
#define P34_DOUT                _PORT_DOUT(3, 4)
#define P35_DOUT                _PORT_DOUT(3, 5)
#define P36_DOUT                _PORT_DOUT(3, 6)
#define P37_DOUT                _PORT_DOUT(3, 7)
#define P40_DOUT                _PORT_DOUT(4, 0)
#define P41_DOUT                _PORT_DOUT(4, 1)
#define P42_DOUT                _PORT_DOUT(4, 2)
#define P43_DOUT                _PORT_DOUT(4, 3)
#define P44_DOUT                _PORT_DOUT(4, 4)
#define P45_DOUT                _PORT_DOUT(4, 5)
#define P46_DOUT                _PORT_DOUT(4, 6)
#define P47_DOUT                _PORT_DOUT(4, 7)
#define P50_DOUT                _PORT_DOUT(5, 0)
#define P51_DOUT                _PORT_DOUT(5, 1)
#define P52_DOUT                _PORT_DOUT(5, 2)
#define P53_DOUT                _PORT_DOUT(5, 3)
#define P54_DOUT                _PORT_DOUT(5, 4)
#define P55_DOUT                _PORT_DOUT(5, 5)


typedef void (*P0P1_CALLBACK)(uint32_t u32P0Status, uint32_t u32P1Status);
typedef void (*P2P3P4_CALLBACK)(uint32_t u32P2Status, uint32_t u32P3Status, uint32_t u32P4Status);
typedef void (*P5_CALLBACK)(uint32_t u32P5Status);
typedef void (*EINT_CALLBACK)(void);

#define CHECK_GPIO_PORT(port)	((port==E_PORT0)||(port==E_PORT1)||(port==E_PORT2)||(port==E_PORT3)||(port==E_PORT4)||(port==E_PORT5))
#define CHECK_GPIO_DEBCYCLE(u32CycleSelection) (u32CycleSelection < 15)
#define CHECK_GPIO_EINT0(port, pin)	((port != E_PORT3) || (pin != 2))
#define CHECK_GPIO_EINT1(port, pin)	((port != E_PORT5) || (pin != 2))

#define GPIO_PORT_OFFSET		0x40
#define	get_port_base(port)		(GPIO0_BASE + (port * GPIO_PORT_OFFSET))



typedef enum 
{
    E_PORT0 = 0,
    E_PORT1, 
    E_PORT2, 
    E_PORT3, 
    E_PORT4,
    E_PORT5
} E_DRVGPIO_PORT;

typedef enum 
{
    E_PIN0  = 0,
    E_PIN1,
    E_PIN2,
    E_PIN3,
    E_PIN4,
    E_PIN5,
    E_PIN6,
    E_PIN7
} E_DRVGPIO_PIN;

typedef enum 
{
    E_EINT0_PIN = 2,
    E_EINT1_PIN = 3
} E_DRVGPIO_EXT_INT_PIN;       

typedef enum 
{
    E_IO_INPUT = 0,
    E_IO_OUTPUT,
    E_IO_OPENDRAIN,
    E_IO_QUASI
} E_DRVGPIO_IO;

typedef enum 
{
    E_IO_RISING,
    E_IO_FALLING,
    E_IO_BOTH_EDGE
} E_DRVGPIO_INT_TYPE;

typedef enum
{
    E_MODE_EDGE,
    E_MODE_LEVEL
} E_DRVGPIO_INT_MODE;

typedef enum
{
    E_DBCLKSRC_HCLK = 0, 
    E_DBCLKSRC_10K = 1
} E_DRVGPIO_DBCLKSRC;      


//*****************************************************************************
//
//  Define Multi-function pin  
//            Byte3 : [31:28] port1; [27:24] port0 
//            Byte2 : [23:20] shift1; [19:16] shift0 
//            Byte1 : [15:12] mask1; [11:8] 
//            Byte0 : [7:6] alt1; [5:4] mfp1; [3:2] alt0; [1:0] 
//
//*****************************************************************************
#define FUNC_GPIO			0xFFFFFFFF
#define FUNC_I2C			0xF3040304
#define FUNC_SPI			0xF0040F04
#define FUNC_ADC0			0xF5030101
#define FUNC_ADC1			0xF1000101
#define FUNC_ADC2			0xF1020101
#define FUNC_ADC3			0xF1030101
#define FUNC_ADC4			0xF1040101
#define FUNC_ADC5			0xF1050101
#define FUNC_ADC6			0xF3000105
#define FUNC_ADC7			0xF3010105
#define FUNC_EXTINT0		0xF3020101
#define FUNC_EXTINT1		0xF5020101
#define FUNC_TMR0			0xF3040101
#define FUNC_TMR1			0xF3050101
#define FUNC_UART			0xF0000305
#define FUNC_UART_FULL		0x10203344
#define FUNC_PWM0			0xF2020104
#define FUNC_PWM1			0xF2030104
#define FUNC_PWM2			0xF2040104
#define FUNC_PWM3			0xF2050104
#define FUNC_PWM4			0xF2060104
#define FUNC_PWM5			0xF0040105
#define FUNC_ICE			0xF4060301
#define FUNC_ACMP0			0x31641355
#define FUNC_ACMP1			0x23601354
#define FUNC_T0EX			0xF3020104
#define FUNC_T1EX			0xF3060101

//*****************************************************************************
//  Define Select multi-function pin  
//            Byte3 : [31:28] port1; [27:24] port0   
//            Byte2 : [23:20] shift1; [19:16] shift0                                                       
//            Byte1 : [15:12] mask1; [11:8] mask0   													   
//            Byte0 : [7:6] alt1; [5:4] mfp1; [3:2] alt0; [1:0] mfp0                                       
//
//*****************************************************************************
#define FUNC_GPIO_P0		0xF0FFFFF0
#define FUNC_GPIO_P1		0xF1FFFFF0
#define FUNC_GPIO_P2		0xF2FFFFF0
#define FUNC_GPIO_P3		0xF3FFFFF0
#define FUNC_GPIO_P4		0xF4FFFFF0
#define FUNC_GPIO_P5		0xF5FFFFF0
#define FUNC_UART_TX_P00	0xF0000105
#define FUNC_UART_RX_P01	0xF0010105
#define FUNC_UART_CTS_P00	0xF0000104
#define FUNC_UART_RTS_P01	0xF0010104
#define FUNC_UART_RX_P12	0xF1020104
#define FUNC_UART_TX_P13	0xF1030104
#define FUNC_SPI_SS_P04		0xF0040104
#define FUNC_SPI_SS_P01		0xF0010101

              
//*****************************************************************************
//
// Define GPIO functions prototype    
//
//*****************************************************************************
void DrvGPIO_Open(E_DRVGPIO_PORT port, uint32_t pin, E_DRVGPIO_IO mode);
void DrvGPIO_Close(E_DRVGPIO_PORT port, uint32_t pin);
int32_t DrvGPIO_SetBit(E_DRVGPIO_PORT port, uint32_t pin);
int32_t DrvGPIO_GetBit(E_DRVGPIO_PORT port, uint32_t pin);
int32_t DrvGPIO_ClrBit(E_DRVGPIO_PORT port, uint32_t pin);
int32_t DrvGPIO_SetPortBits(E_DRVGPIO_PORT port, int32_t i32PortValue);
int32_t DrvGPIO_GetPortBits(E_DRVGPIO_PORT port);
int32_t DrvGPIO_GetDoutBit(E_DRVGPIO_PORT port, uint32_t pin);
int32_t DrvGPIO_GetPortDoutBits(E_DRVGPIO_PORT port);
int32_t DrvGPIO_SetBitMask(E_DRVGPIO_PORT port, uint32_t pin);
int32_t DrvGPIO_GetBitMask(E_DRVGPIO_PORT port, uint32_t pin);
int32_t DrvGPIO_ClrBitMask(E_DRVGPIO_PORT port, uint32_t pin);
int32_t DrvGPIO_SetPortMask(E_DRVGPIO_PORT port, int32_t i32PortValue);
int32_t DrvGPIO_GetPortMask(E_DRVGPIO_PORT port);
int32_t DrvGPIO_ClrPortMask(E_DRVGPIO_PORT port, int32_t i32PortValue);
int32_t DrvGPIO_EnableDebounce(E_DRVGPIO_PORT port, uint32_t pin);
int32_t DrvGPIO_DisableDebounce(E_DRVGPIO_PORT port, uint32_t pin);
int32_t DrvGPIO_SetDebounceTime(uint32_t u32CycleSelection, E_DRVGPIO_DBCLKSRC ClockSource);
int32_t DrvGPIO_GetDebounceSampleCycle(void);
int32_t DrvGPIO_EnableInt(E_DRVGPIO_PORT port, uint32_t pin, E_DRVGPIO_INT_TYPE Type, E_DRVGPIO_INT_MODE Mode);
int32_t DrvGPIO_DisableInt(E_DRVGPIO_PORT port, uint32_t pin);
void DrvGPIO_SetIntCallback(P0P1_CALLBACK pfP0P1Callback, P2P3P4_CALLBACK pfP2P3P4Callback, P5_CALLBACK pfP5Callback);
int32_t DrvGPIO_EnableEINT(E_DRVGPIO_EXT_INT_PIN pin, E_DRVGPIO_INT_TYPE Type, E_DRVGPIO_INT_MODE Mode, EINT_CALLBACK pfEINTCallback);
int32_t DrvGPIO_DisableEINT(E_DRVGPIO_EXT_INT_PIN pin);
int32_t DrvGPIO_GetIntStatus(E_DRVGPIO_PORT port);
int32_t DrvGPIO_InitFunction(uint32_t function);
int32_t DrvGPIO_SelectFunction(uint32_t function);
int32_t DrvGPIO_GetVersion(void);

#endif








