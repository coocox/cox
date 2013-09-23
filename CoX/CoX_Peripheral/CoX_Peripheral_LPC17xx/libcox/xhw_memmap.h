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
#define xDMA0_BASE              DMA_BASE
#define xUSB_BASE               USB_BASE
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
#define xI2S_BASE               I2S_BASE
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

#define FLASH_BASE              ((unsigned long)0x00000000)
#define SRAM_BASE               ((unsigned long)0x20000000)
#define ETH_BASE                ((unsigned long)0x50000000)
#define DMA_BASE                ((unsigned long)0x50004000)
#define USB_BASE                ((unsigned long)0x5000C000)

#define GPIOA_BASE              ((unsigned long)0x2009C000)
#define GPIOB_BASE              ((unsigned long)0x2009C020)
#define GPIOC_BASE              ((unsigned long)0x2009C040)
#define GPIOD_BASE              ((unsigned long)0x2009C060)
#define GPIOE_BASE              ((unsigned long)0x2009C080)

//LPC17nx APB0 (n = 5/6)
#define WDT_BASE                ((unsigned long)0x40000000)
#define TIMER0_BASE             ((unsigned long)0x40004000)
#define TIMER1_BASE             ((unsigned long)0x40008000)
#define UART0_BASE              ((unsigned long)0x4000C000)
#define UART1_BASE              ((unsigned long)0x40010000)
#define PWM1_BASE               ((unsigned long)0x40018000)
#define I2C0_BASE               ((unsigned long)0x4001C000)
#define SPI0_BASE               ((unsigned long)0x40020000)
#define RTC_BASE                ((unsigned long)0x40024000)
#define GPIO_INT_BASE           ((unsigned long)0x40028000)
#define PIN_CON_BASE            ((unsigned long)0x4002C000)
#define SSP1_BASE               ((unsigned long)0x40030000)
#define ADC_BASE                ((unsigned long)0x40034000)
#define CAN_AF_RAM_BASE         ((unsigned long)0x40038000)
#define CAN_AF_REG_BASE         ((unsigned long)0x4003C000)
#define CAN_COMM_BASE           ((unsigned long)0x40040000)
#define CAN1_BASE               ((unsigned long)0x40044000)
#define CAN2_BASE               ((unsigned long)0x40048000)
#define I2C1_BASE               ((unsigned long)0x4005C000)

//LPC17nx APB1 (n = 5/6)
#define SSP0_BASE               ((unsigned long)0x40088000)
#define DAC_BASE                ((unsigned long)0x4008C000)
#define TIMER2_BASE             ((unsigned long)0x40090000)
#define TIMER3_BASE             ((unsigned long)0x40094000)
#define UART2_BASE              ((unsigned long)0x40098000)
#define UART3_BASE              ((unsigned long)0x4009C000)
#define I2C2_BASE               ((unsigned long)0x400A0000)
#define I2S_BASE                ((unsigned long)0x400A8000)
#define RIT_BASE                ((unsigned long)0x400B0000)
#define MCPWM_BASE              ((unsigned long)0x400B8000)
#define QEI_BASE                ((unsigned long)0x400BC000)
#define SYSCTL_BASE             ((unsigned long)0x400FC000)

//Core components
#define ITM_BASE                ((unsigned long)0xE0000000)
#define DWT_BASE                ((unsigned long)0xE0001000)
#define FPB_BASE                ((unsigned long)0xE0002000)
#define NVIC_BASE               ((unsigned long)0xE000E000)
#define TPIU_BASE               ((unsigned long)0xE0040000)
#define COREDEBUG_BASE          ((unsigned long)0xE000EDF0)

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

