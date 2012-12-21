//*****************************************************************************
//
//! \file xhw_memmap.h
//! \brief Macros defining the memory map of KLx.
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

#ifndef __XHW_MEMMAP_H__
#define __XHW_MEMMAP_H__

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
//! \brief The following are definitions for the base addresses of the memories
//! and peripherals.
//!
//! They are always used as ulBase parameters in the peripheral library.
//! The name of a macro for the base address of a peripheral is in  general
//! format as $Name$_BASE, e.g. UART0_BASE.
//!
//! @{
//
//*****************************************************************************

#define xFLASH_BASE             FLASH_BASE  // Flash memory
#define xSRAM_BASE              SRAM_BASE   // SRAM memory
#define xWDT_BASE               WDT_BASE    // WatchDog
#define xGPIO_PORTA_BASE        GPIOA_BASE
                                            // GPIOA
#define xGPIO_PORTB_BASE        GPIOB_BASE
                                            // GPIOB
#define xGPIO_PORTC_BASE        GPIOC_BASE
                                            // GPIOC
#define xGPIO_PORTD_BASE        GPIOD_BASE
                                            // GPIOD
#define xGPIO_PORTE_BASE        GPIOE_BASE
                                            // GPIOE     
#define xUART0_BASE             UART0_BASE  // UART0
#define xUART1_BASE             UART1_BASE  // UART1
#define xUART2_BASE             UART2_BASE  // UART2
#define xTIMER0_BASE            TPM0_BASE   // Timer0
#define xTIMER1_BASE            TPM1_BASE   // Timer1
#define xTIMER2_BASE            TPM2_BASE   // Timer2
#define xSPI0_BASE              SPI0_BASE   // SPI0
#define xSPI1_BASE              SPI1_BASE   // SPI1
#define xI2C0_BASE              I2C0_BASE   // I2C0 
#define xI2C1_BASE              I2C1_BASE   // I2C1 
#define xADC0_BASE              ADC_BASE    // ADC
#define xACMP0_BASE             ACMP_BASE   // ACMP
#define xPWMA_BASE              PWMA_BASE   // PWMA
#define xPWMB_BASE              PWMB_BASE   // PWMB
#define xPWMC_BASE              PWMC_BASE   // PWMC

#define xAFIO_BASE              0           // AFIO

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
//! \addtogroup KLx_LowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_LowLayer_Peripheral_Memmap KLx LowLayer Peripheral Memmap
//! The following are defines for the base address of the memories and
//! peripherals.
//!
//! This is always used as ulBase parameter in the peripheral library.
//! @{
//
//*****************************************************************************

#define FLASH_BASE              0x00000000  // FLASH memory
#define SRAM_L_BASE             0x1FFFF000  // Low SRAM
#define SRAM_H_BASE             0x20000000  // Upper SRAM
#define DMA0_BASE               0x40008100  // DMA0 controller
#define DMA1_BASE               0x40008110  // DMA1 controller
#define DMA2_BASE               0x40008120  // DMA2 controller
#define DMA3_BASE               0x40008130  // DMA3 controller
#define GPIO_BASE               0x4000F000  // GPIO controller
#define FMC_BASE                0x40020000  // Flash memory
#define FTFA_BASE               0x40020000  // 
#define DMAMUX0_BASE            0x40021000  // DMA channel mutiplexer 0
#define PIT_BASE                0x40037000  // Periodic interrupt timers (PIT)
#define TPM0_BASE               0x40038000  // Timer'/PWM (TPM) 0
#define TPM1_BASE               0x40039000  // Timer'/PWM (TPM) 1
#define TPM2_BASE               0x4003A000  // Timer'/PWM (TPM) 2
#define PWMA_BASE               0x40038000  // Timer'/PWM (PWM) A
#define PWMB_BASE               0x40039000  // Timer'/PWM (PWM) B
#define PWMC_BASE               0x4003A000  // Timer'/PWM (PWM) C
#define ADC_BASE                0x4003B000  // Analog-to-digital converter (ADC) 0
#define RTC_BASE                0x4003D000  // Real-time clock (RTC)
#define DAC_BASE                0x4003F000  // DAC0
#define LPTMR_BASE              0x40040000  // Low-power timer (LPTMR)
#define TSI_BASE                0x40045000  // Touch sense interface (TSI)
#define SIMLPL_BASE             0x40047000  // SIM low-power logic
#define SIM_BASE                0x40048000  // System integration module (SIM)
#define PORTA_BASE              0x40049000  // Port A multiplexing control
#define PORTB_BASE              0x4004A000  // Port B multiplexing control
#define PORTC_BASE              0x4004B000  // Port C multiplexing control
#define PORTD_BASE              0x4004C000  // Port D multiplexing control
#define PORTE_BASE              0x4004D000  // Port E multiplexing control
#define MCG_BASE                0x40064000  // Multi-purpose Clock Generator (MCG)
#define OSC_BASE                0x40065000  // System oscillator (OSC)
#define I2C0_BASE               0x40066000  // I2C 0 
#define I2C1_BASE               0x40067000  // I2C 1 
#define UART0_BASE              0x4006A000  // UART0
#define UART1_BASE              0x4006B000  // UART1
#define UART2_BASE              0x4006C000  // UART2
#define USBOTG_BASE             0x40072000  // USB OTG FS/LS
#define ACMP_BASE               0x40073000  // Analog comparator (CMP) / 6-bit 
                                            // digital-to-analog converter (DAC)
#define SPI0_BASE               0x40076000  // SPI 0
#define SPI1_BASE               0x40077000  // SPI 1
#define LLWU_BASE               0x4007C000  // Low-leakage wakeup unit (LLWU)
#define PMC_BASE                0x4007D000  // Power management controller (PMC)
#define SMC_BASE                0x4007E000  // System Mode controller (SMC)
#define RCM_BASE                0x4007F000  // Reset Control Module (RCM)
#define GPIOA_BASE              0x400FF000  // GPI0 A
#define GPIOB_BASE              0x400FF040  // GPI0 B
#define GPIOC_BASE              0x400FF080  // GPI0 C
#define GPIOD_BASE              0x400FF0C0  // GPI0 D
#define GPIOE_BASE              0x400FF100  // GPI0 E

#define BME_BASE                0x44000000  // Bit Manipulation Engine (BME) access to 
                                            // AIPS Peripherals for slots 0-127
#define MTB_BASE                0xF0000000  // Micro Trace Buffer (MTB) registers
#define MTBDWT_BASE             0xF0001000  // MTB Data Watchpoint and Trace (MTBDWT) registers
#define ROM_BASE                0xF0002000  // ROM table
#define MCM_BASE                0xF0003000  // ROM table

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

#endif // __XHW_MEMMAP_H__


