//*****************************************************************************
//
//! \file      lowlayer.h
//! \brief     Macros defining of Peripehral Base and interrupt assignments for LPC17xx.
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

#ifndef __LPC17XX_LOWLAYER__
#define __LPC17XX_LOWLAYER__


//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
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
//! \addtogroup LPC17xx_owLayer_Peripheral_Memmap LPC17xx Peripheral Memmap
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

#define FLASH_BASE              0x08000000  // Flash memory
#define SRAM_BASE               0x20000000  // SRAM memory

//LPC17nx AHB (n = 5/6)
#define ETH_BASE                0x50000000  // Ethernet MAC
#define DMA0_BASE               0x50004000  // General Purpose DMA controller
#define USBD_BASE               0x5000C000  // USB interface

#define GPIOA_BASE              0x2009C000  // GPIO Port A
#define GPIOB_BASE              0x2009C020  // GPIO Port B
#define GPIOC_BASE              0x2009C040  // GPIO Port C
#define GPIOD_BASE              0x2009C060  // GPIO Port D
#define GPIOE_BASE              0x2009C080  // GPIO Port E

// LPC17nx AHB (n = 7/8)
#define DMA0_BASE               0x20080000  // General Purpose DMA controller
#define ETH_BASE                0x20084000  // Ethernet MAC
#define LCD_BASE                0x20088000  // LCD controller
#define USBD_BASE               0x2008C000  // USB interface
#define CRC_BASE                0x20090000  // CRC engine

#define EMC_BASE                0x2009C000  // External Memory Controller

//APB0
#define WDT_BASE                0x40000000  // Watchdog Timer
#define TIMER0_BASE             0x40004000  // Timer 0
#define TIMER1_BASE             0x40008000  // Timer 1
#define UART0_BASE              0x4000C000  // UART0
#define UART1_BASE              0x40010000  // UART1
#define PWM0_BASE               0x40014000  // PWM0
#define PWM1_BASE               0x40018000  // PWM1
#define I2C0_BASE               0x4001C000  // I2C0
#define SPI_BASE                0x40020000  // SPI
#define RTC_BASE                0x40024000  // RTC and Event Monitor/Recorder
#define GPIO_INT_BASE           0x40028000  // GPIO interrupts
#define PIN_CON_BASE            0x4002C000  // Pin Connect Block
#define SSP1_BASE               0x40030000  // SSP1
#define ADC0_BASE               0x40034000  // ADC
#define CAN_AF_RAM_BASE         0x40038000  // CAN Acceptance Filter RAM
#define CAN_AF_REG_BASE         0x4003C000  // CAN Acceptance Filter Registers
#define CAN_COMM_BASE           0x40040000  // CAN Common Registers
#define CAN1_BASE               0x40044000  // CAN Controller 1
#define CAN2_BASE               0x40048000  // CAN Controller 2
#define I2C1_BASE               0x4005C000  // I2C1

//APB1
#define SSP0_BASE               0x40088000  // SSP0
#define DAC0_BASE               0x4008C000  // DAC
#define TIMER2_BASE             0x40090000  // Timer 2
#define TIMER3_BASE             0x40094000  // Timer 3
#define UART2_BASE              0x40098000  // UART2
#define UART3_BASE              0x4009C000  // UART3
#define I2C2_BASE               0x400A0000  // I2C2
#define UART4_BASE              0x400A4000  // UART4
#define I2S0_BASE               0x400A8000  // I2S
#define SSP2_BASE               0x400AC000  // SSP2
#define RIT_BASE                0x400B0000  // Repetitive interrupt timer
#define MCPWM_BASE              0x400B8000  // Motor control PWM
#define QEI_BASE                0x400BC000  // Quadrature Encoder Interface
#define SDC_BASE                0x400C0000  // SD card interface
#define SYSCTL_BASE             0x400FC000  // System control

//Core components
#define ITM_BASE                0xE0000000  // 
#define DWT_BASE                0xE0001000  // 
#define FPB_BASE                0xE0002000  // 
#define NVIC_BASE               0xE000E000  // 
#define TPIU_BASE               0xE0040000  // 
#define COREDEBUG_BASE          0xE000EDF0  // 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_Interrupt_Assignments LPC17xx Interrupt Assignments
//! \brief Macro definitions for the fault/interrupt assignments.
//!
//! They can be used as ulInterrupt parameters with xIntEnable(), xIntDisable()
//! to enable/disable the interrupt at the core/NVIC level.
//!
//! @{
//
//*****************************************************************************

#define FAULT_NMI               2   // NMI fault
#define FAULT_HARD              3   // Hard fault
#define FAULT_MPU               4   // MPU fault
#define FAULT_BUS               5   // Bus fault
#define FAULT_USAGE             6   // Usage fault
#define FAULT_SVCALL            11  // SVCall
#define FAULT_DEBUG             12  // Debug monitor
#define FAULT_PENDSV            14  // PendSV
#define FAULT_SYSTICK           15  // System Tick

#define INT_WDT                 16  // Watchdog timer
#define INT_TIMER0              17  // Timer 0
#define INT_TIMER1              18  // Timer 1
#define INT_TIMER2              19  // Timer 2
#define INT_TIMER3              20  // Timer 3
#define INT_UART0               21  // UART0 Rx and Tx
#define INT_UART1               22  // UART1 Rx and Tx
#define INT_UART2               23  // UART2 Rx and Tx
#define INT_UART3               24  // UART3 Rx and Tx
#define INT_PWM1                25  // PWM Generator 1
#define INT_I2C0                26  // I2C0 Master and Slave
#define INT_I2C1                27  // I2C1 Master and Slave
#define INT_I2C2                28  // I2C2 Master and Slave
#define INT_SPI                 29  // SPI
#define INT_SSP0                30  // SSP0 Rx and Tx
#define INT_SSP1                31  // SSP1 Rx and Tx
#define INT_PLL0                32  // PLL0 Lock (PLOCK0)
#define INT_RTC                 33  // RTC & EV0, EV1, EV2
#define INT_EINT0               34  // External Line0 Interrupt
#define INT_EINT1               35  // External Line1 Interrupt
#define INT_EINT2               36  // External Line2 Interrupt
#define INT_EINT3               37  // External Line3 Interrupt
#define INT_ADC0                38  // ADC
#define INT_BOD                 39  // Brown Out detect
#define INT_USB                 40  // USB Controller
#define INT_CAN                 41  // CAN 0 Interrupts
#define INT_DMA                 42  // DMA controller
#define INT_I2S                 43  // I2S
#define INT_ETH                 44  // Ethernet
#define INT_RIT                 45  // RIT
#define INT_MCPWM               46  // Motor Control PWM
#define INT_QEI                 47  // Quadrature Encoder Interface
#define INT_PLL1                48  // PLL1 Lock (Alt PLL)
#define INT_USBACT              49  // USB Activity Interrupt
#define INT_CANWAKE             50  // CAN Activity Interrupt
#define INT_UART4               51  // UART4 Rx and Tx
#define INT_SSP2                52  // SSP1 Rx and Tx
#define INT_LCD                 53  // LCD controller
#define INT_GPIO                54  // GPIO interrupts
#define INT_PWM0                55  // PWM0
#define INT_EEPROM              56  // EEPROM

//
//! The total number of interrupts.
//
#define NUM_INTERRUPTS          58

//
//! The total number of priority levels
//
#define NUM_PRIORITY            8

//
//! The Total number of priority levels (bits)
//
#define NUM_PRIORITY_BITS       5


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

#endif // __LPC17XX_LOWLAYER__
