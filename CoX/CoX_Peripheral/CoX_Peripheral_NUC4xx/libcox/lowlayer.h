//*****************************************************************************
//
//! \file      lowlayer.h
//! \brief     Macros defining of Peripehral Base and interrupt assignments for NUC4xx.
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

#ifndef __LOWLAYER__
#define __LOWLAYER__


//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_LowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_owLayer_Peripheral_Memmap NUC4xx Peripheral Memmap
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
#define GCR_BASE                0x40000000  // System Global Control
#define CLK_BASE                0x40000200  // Clock Control
#define NVIC_BASE               0x40000300  // Interrupt Multiplexer
#define GPIOA_BASE              0x40004000  // GPIO Port A
#define GPIOB_BASE              0x40004040  // GPIO Port B
#define GPIOC_BASE              0x40004080  // GPIO Port C
#define GPIOD_BASE              0x400040C0  // GPIO Port D
#define GPIOE_BASE              0x40004100  // GPIO Port E
#define GPIOF_BASE              0x40004140  // GPIO Port F
#define GPIOG_BASE              0x40004180  // GPIO Port G
#define GPIOH_BASE              0x400041C0  // GPIO Port H
#define GPIOI_BASE              0x40004200  // GPIO Port I
#define PDMA_BASE               0x40008000  // DMA
#define UHC_BASE                0x40009000  // USB Host
#define EMAC_BASE               0x4000B000  // Ethernet
#define FMC_BASE                0x4000C000  // FMC
#define SDHOST_BASE             0x4000D000  // SD HOST
#define EBI_BASE                0x40010000  // External Bus Interface
#define UDC_BASE                0x40019000  // USB device
#define CAP_BASE                0x40030000  // Image Capture  interface
#define CRC_BASE                0x40031000  // CRC

#define WWDG_BASE               0x40040C00  // Window watchdog (WWDG)
#define IWDG_BASE               0x40040000  // Independent watchdog (IWDG)
#define RTC_BASE                0x40041000  // RTC
#define ADC0_BASE               0x40043000  // ADC0
#define ADC1_BASE               0x40043000  // Enhance ADC1
#define ACMP_BASE               0x40045000  // ACMP
#define OPA_BASE                0x40046000  // OP Amplifier
#define I2S0_BASE               0x40048000  // I2S0
#define I2S1_BASE               0x40049000  // I2S1
#define USBD_BASE               0x4004D000  // USB device FS registers
#define TIM0_BASE               0x40050000  // TIM0
#define TIM1_BASE               0x40050020  // TIM1
#define TIM2_BASE               0x40051000  // TIM2
#define TIM3_BASE               0x40051020  // TIM3
#define PWMA_BASE               0x40058000  // PWMA
#define PWMB_BASE               0x40059000  // PWMB
#define EPWMA_BASE              0x4005C000  // Enhanced PWMA
#define EPWMB_BASE              0x4005D000  // Enhanced PWMB
#define SPI0_BASE               0x40060000  // SPI0
#define SPI1_BASE               0x40061000  // SPI1
#define SPI2_BASE               0x40062000  // SPI2
#define SPI3_BASE               0x40063000  // SPI3
#define USART0_BASE             0x40070000  // USART1
#define USART1_BASE             0x40071000  // USART1
#define USART2_BASE             0x40072000  // USART2
#define USART3_BASE             0x40073000  // USART3
#define USART4_BASE             0x40074000  // USART4
#define USART5_BASE             0x40075000  // USART5
#define I2C0_BASE               0x40080000  // I2C1
#define I2C1_BASE               0x40081000  // I2C1
#define I2C2_BASE               0x40082000  // I2C2
#define I2C3_BASE               0x40083000  // I2C1
#define I2C4_BASE               0x40084000  // I2C2
#define SC0_BASE                0x40090000  // SmartCard0
#define SC1_BASE                0x40091000  // SmartCard0
#define SC2_BASE                0x40092000  // SmartCard0
#define SC3_BASE                0x40093000  // SmartCard0
#define SC4_BASE                0x40094000  // SmartCard0
#define SC5_BASE                0x40095000  // SmartCard0
#define CAN0_BASE               0x400A0000  // bxCAN1
#define CAN1_BASE               0x400A1000  // bxCAN2
#define QEI0_BASE               0x400B0000  // Quadrature Encoder 0 Interface
#define QEI1_BASE               0x400B1000  // Quadrature Encoder 1 Interface
#define ECAP0_BASE              0x400C0000  // Capture Engine 0
#define ECAP1_BASE              0x400C1000  // Capture Engine 1
#define PS2_BASE                0x400E0000  // PS/2

#define CRYP_BASE               0x50008000  // Cryptographic Accelerator


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_Interrupt_Assignments STM32F1xx Interrupt Assignments
//! \brief Macro definitions for the fault/interrupt assignments.
//!
//! They can be used as ulInterrupt parameters with xIntEnable(), xIntDisable()
//! to enable/disable the interrupt at the core/NVIC level.
//!
//! @{
//
//*****************************************************************************

#define FAULT_NMI               2           // NMI fault
#define FAULT_HARD              3           // Hard fault
#define FAULT_MPU               4           // MPU fault
#define FAULT_BUS               5           // Bus fault
#define FAULT_USAGE             6           // Usage fault
#define FAULT_SVCALL            11          // SVCall
#define FAULT_DEBUG             12          // Debug monitor
#define FAULT_PENDSV            14          // PendSV
#define FAULT_SYSTICK           15          // System Tick


//
//! The total number of interrupts.
//
#define NUM_INTERRUPTS          158

//
//! The total number of priority levels
//
#define NUM_PRIORITY            16

//
//! The Total number of priority levels (bits)
//
#define NUM_PRIORITY_BITS       4


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

#endif // __xLOWLAYER__
