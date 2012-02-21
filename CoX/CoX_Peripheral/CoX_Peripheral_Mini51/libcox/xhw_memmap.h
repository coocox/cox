//*****************************************************************************
//
//! \file xhw_memmap.h
//! \brief Macros defining the memory map of MINI51.
//! \version V2.1.1.0
//! \date 1/18/2012
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
//! format as $Namen$_BASE, e.g. UART0_BASE.
//!
//! @{
//
//*****************************************************************************

#define xFLASH_BASE             FLASH_BASE  // Flash memory
#define xSRAM_BASE              SRAM_BASE   // SRAM memory
#define xWDT_BASE               WDT_BASE    // WatchDog
#define xGPIO_PORTA_BASE        GPIO_PORTA_BASE
                                            // GPIOA
#define xGPIO_PORTB_BASE        GPIO_PORTB_BASE
                                            // GPIOB
#define xGPIO_PORTC_BASE        GPIO_PORTC_BASE
                                            // GPIOC
#define xGPIO_PORTD_BASE        GPIO_PORTD_BASE
                                            // GPIOD
#define xGPIO_PORTE_BASE        GPIO_PORTE_BASE
                                            // GPIOE 
#define xGPIO_PORTF_BASE        GPIO_PORTF_BASE
                                            // GPIOF 
#define xUART0_BASE             UART0_BASE  // UART0
#define xTIMER0_BASE            TIMER0_BASE // Timer0
#define xTIMER1_BASE            TIMER1_BASE // Timer1
#define xSPI0_BASE              SPI0_BASE   // SPI0
#define xI2C0_BASE              I2C0_BASE   // I2C0
#define xADC0_BASE              ADC_BASE    // ADC
#define xACMP0_BASE             ACMP_BASE   // ACMP
#define xPWMA_BASE              PWMA_BASE   // PWMA

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
//! \addtogroup MINI51_LowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_LowLayer_Peripheral_Memmap MINI51 LowLayer Peripheral Memmap
//! The following are defines for the base address of the memories and
//! peripherals.
//!
//! This is always used as ulBase parameter in the peripheral library.
//! @{
//
//*****************************************************************************

#define FLASH_BASE              0x00000000  // FLASH memory
#define SRAM_BASE               0x20000000  // SRAM memory
#define WDT_BASE                0x40004000  // Watchdog0
#define GPIO_PORTA_BASE         0x50004000  // GPIO Port A
#define GPIO_PORTB_BASE         0x50004040  // GPIO Port B
#define GPIO_PORTC_BASE         0x50004080  // GPIO Port C
#define GPIO_PORTD_BASE         0x500040C0  // GPIO Port D
#define GPIO_PORTE_BASE         0x50004100  // GPIO Port E
#define GPIO_PORTF_BASE         0x50004140  // GPIO Port F
#define GPIO_DBNCECON_BASE      0x50004180  // GPIO Port DBNCECON
#define UART0_BASE              0x40050000  // UART0
#define TIMER0_BASE             0x40010000  // Timer0
#define TIMER1_BASE             0x40010020  // Timer1
#define SPI0_BASE               0x40030000  // SPI0
#define I2C0_BASE               0x40020000  // I2C
#define ADC_BASE                0x400E0000  // ADC
#define ACMP_BASE               0x400D0000  // ACMP
#define PWMA_BASE               0x40040000  // PWMA

#define SYSCLK_BASE             0x50000200  // SYSTEM CLOCK
#define GCR_BASE                0x50000000  // GCR
#define INT_BASE                0x50000300  // INT
#define FMC_BASE                0x5000C000  // FMC

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


