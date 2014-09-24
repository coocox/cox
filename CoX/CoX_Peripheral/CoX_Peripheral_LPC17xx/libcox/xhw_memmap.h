//*****************************************************************************
//
//! \file      xhw_memmap.h
//! \brief     Macros defining the memory map of NXP LPC17xx.
//! \version   V2.1.1.0
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

#ifndef __xHW_MEMMAP_H__
#define __xHW_MEMMAP_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xLowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xLowLayer_Peripheral_Memmap xLowLayer Peripheral Memmap
//! \brief      The following are definitions for the base addresses of the memories
//!             and peripherals.
//!
//! They are always used as ulBase parameters in the peripheral library.
//! The name of a macro for the base address of a peripheral is in  general
//! format as x$Namen$_BASE, e.g. xUART0_BASE.
//!
//! @{
//
//*****************************************************************************
#define xETH_BASE               ETH_BASE
#define xDMA0_BASE              DMA0_BASE
#define xUSB_BASE               USBD_BASE
#define xGPIO_PORTA_BASE        GPIOA_BASE
#define xGPIO_PORTB_BASE        GPIOB_BASE
#define xGPIO_PORTC_BASE        GPIOC_BASE
#define xGPIO_PORTD_BASE        GPIOD_BASE
#define xGPIO_PORTE_BASE        GPIOE_BASE
#define xWDT_BASE               WDT_BASE
#define xTIMER0_BASE            TIMER0_BASE
#define xTIMER1_BASE            TIMER1_BASE
#define xUART0_BASE             UART0_BASE
#define xUART1_BASE             UART1_BASE
#define xPWM0_BASE              PWM0_BASE
#define xPWM1_BASE              PWM1_BASE
#define xI2C0_BASE              I2C0_BASE
#define xSPI0_BASE              SPI0_BASE
#define xRTC_BASE               RTC_BASE
#define xSSP1_BASE              SSP1_BASE
#define xADC0_BASE              ADC_BASE
#define xCAN1_BASE              CAN1_BASE
#define xCAN2_BASE              CAN2_BASE
#define xI2C1_BASE              I2C1_BASE
#define xSSP0_BASE              SSP0_BASE
#define xDAC0_BASE              DAC_BASE
#define xTIMER2_BASE            TIMER2_BASE
#define xTIMER3_BASE            TIMER3_BASE
#define xUART2_BASE             UART2_BASE
#define xUART3_BASE             UART3_BASE
#define xI2C2_BASE              I2C2_BASE
#define xUART4_BASE             UART4_BASE
#define xCAN1_BASE              CAN1_BASE
#define xCAN2_BASE              CAN2_BASE
#define xI2S_BASE               I2S_BASE
#define xSSP2_BASE              SSP2_BASE
#define xRIT_BASE               RIT_BASE
#define xMCPWM_BASE             MCPWM_BASE
#define xQEI_BASE               QEI_BASE

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
//! \addtogroup LPC17xx_LowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_LowLayer_Peripheral_Memmap LPC17xx LowLayer Peripheral Memmap
//! \brief      The following are defines for the base address of the memories
//!             and peripherals.
//!
//! \note       This is always used as ulBase parameter in the peripheral library.
//! @{
//
//*****************************************************************************

#define FLASH_BASE              0x00000000
#define SRAM_BASE               0x20000000

#if defined(LPC_175x) || defined (LPC_176x)
//LPC17nx AHB (n = 5/6)
#define ETH_BASE                0x50000000  // Ethernet MAC
#define DMA0_BASE               0x50004000  // General Purpose DMA
#define USBD_BASE               0x5000C000  // USB interface
#define GPIOA_BASE              0x2009C000  // GPIOA
#define GPIOB_BASE              0x2009C020  // GPIOB
#define GPIOC_BASE              0x2009C040  // GPIOC
#define GPIOD_BASE              0x2009C060  // GPIOD
#define GPIOE_BASE              0x2009C080  // GPIOE

//LPC17nx AHB (n = 7/8)
#elif defined(LPC_177x) || defined (LPC_178x)
#define DMA0_BASE               0x20080000  // General Purpose DMA
#define ETH_BASE                0x20084000  // Ethernet MAC
#define LCD_BASE                0x20088000  // LCD controller
#define USBD_BASE               0x2008C000  // USB interface
#define CRC_BASE                0x20090000  // CRC engine
#define GPIOA_BASE              0x20098000  // GPIOA
#define GPIOB_BASE              0x20098020  // GPIOB
#define GPIOC_BASE              0x20098040  // GPIOC
#define GPIOD_BASE              0x20098060  // GPIOD
#define GPIOE_BASE              0x20098080  // GPIOE
#define GPIOF_BASE              0x200980A0  // GPIOF
#define EMC_BASE                0x2009C000  // External Memory Controller
#endif

//LPC17nx APB0 (n = 5/6/7/8)
#define WDT_BASE                0x40000000  // Watchdog Timer
#define TIMER0_BASE             0x40004000  // Timer 0
#define TIMER1_BASE             0x40008000  // Timer 1
#define UART0_BASE              0x4000C000  // UART0
#define UART1_BASE              0x40010000  // UART1
#define PWM0_BASE               0x40014000  // PWM0
#define PWM1_BASE               0x40018000  // PWM1
#define I2C0_BASE               0x4001C000  // I2C0
#define SPI0_BASE               0x40020000  // SPI
#define RTC_BASE                0x40024000  // RTC and Event Monitor/Recorder
#define GPIO_INT_BASE           0x40028000  // GPIO interrupts
#define PIN_CON_BASE            0x4002C000  // Pin Connect Block
#define SSP1_BASE               0x40030000  // SSP1
#define ADC_BASE                0x40034000  // ADC
#define CAN_AF_RAM_BASE         0x40038000  // CAN Acceptance Filter RAM
#define CAN_AF_REG_BASE         0x4003C000  // CAN Acceptance Filter Registers
#define CAN_COMM_BASE           0x40040000  // CAN Common Registers
#define CAN1_BASE               0x40044000  // CAN Controller 1
#define CAN2_BASE               0x40048000  // CAN Controller 2
#define I2C1_BASE               0x4005C000  // I2C1

//LPC17nx APB1 (n = 5/6/7/8)
#define SSP0_BASE               0x40088000  // SSP0
#define DAC_BASE                0x4008C000  // DAC
#define TIMER2_BASE             0x40090000  // Timer 2
#define TIMER3_BASE             0x40094000  // Timer 3
#define UART2_BASE              0x40098000  // UART2
#define UART3_BASE              0x4009C000  // UART3
#define I2C2_BASE               0x400A0000  // I2C2
#define UART4_BASE              0x400A4000  // UART4
#define I2S_BASE                0x400A8000  // I2S
#define SSP2_BASE               0x400AC000  // SSP2
#define RIT_BASE                0x400B0000  // Repetitive interrupt timer
#define MCPWM_BASE              0x400B8000  // Motor control PWM
#define QEI_BASE                0x400BC000  // Quadrature Encoder Interface
#define SDC_BASE                0x400C0000  // SD card interface
#define SYSCTL_BASE             0x400FC000  // System control

//Core components
#define ITM_BASE                0xE0000000
#define DWT_BASE                0xE0001000
#define FPB_BASE                0xE0002000
#define NVIC_BASE               0xE000E000
#define TPIU_BASE               0xE0040000
#define COREDEBUG_BASE          0xE000EDF0

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

#endif // __xHW_MEMMAP_H__

