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
#define DMA0_BASE               0x40008000  // PDMA
#define UHC_BASE                0x40009000  // USB Host
#define EMAC_BASE               0x4000B000  // Ethernet
#define FMC_BASE                0x4000C000  // FMC
#define SDHOST_BASE             0x4000D000  // SD HOST
#define EBI_BASE                0x40010000  // External Bus Interface
#define UDC_BASE                0x40019000  // USB device
#define CAP_BASE                0x40030000  // Image Capture  interface
#define CRC_BASE                0x40031000  // CRC

#define WWDT_BASE               0x40040C00  // Window watchdog (WWDG)
#define IWDT_BASE               0x40040000  // Independent watchdog (IWDG)
#define RTC_BASE                0x40041000  // RTC
#define ADC0_BASE               0x40043000  // ADC0
#define ADC1_BASE               0x40043000  // Enhance ADC1
#define ACMP_BASE               0x40045000  // ACMP
#define OPA_BASE                0x40046000  // OP Amplifier
#define I2S0_BASE               0x40048000  // I2S0
#define I2S1_BASE               0x40049000  // I2S1
#define USBD_BASE               0x4004D000  // USB device FS registers
#define TIMER0_BASE             0x40050000  // TIM0
#define TIMER1_BASE             0x40050020  // TIM1
#define TIMER2_BASE             0x40051000  // TIM2
#define TIMER3_BASE             0x40051020  // TIM3
#define PWMA_BASE               0x40058000  // PWMA
#define PWMB_BASE               0x40059000  // PWMB
#define EPWMA_BASE              0x4005C000  // Enhanced PWMA
#define EPWMB_BASE              0x4005D000  // Enhanced PWMB
#define SPI0_BASE               0x40060000  // SPI0
#define SPI1_BASE               0x40061000  // SPI1
#define SPI2_BASE               0x40062000  // SPI2
#define SPI3_BASE               0x40063000  // SPI3
#define UART0_BASE              0x40070000  // USART1
#define UART1_BASE              0x40071000  // USART1
#define UART2_BASE              0x40072000  // USART2
#define UART3_BASE              0x40073000  // USART3
#define UART4_BASE              0x40074000  // USART4
#define UART5_BASE              0x40075000  // USART5
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

#define INT_BOD                 16          // Brown Out detection interrupt
#define INT_IRC                 17          // Internal RC
#define INT_PWRWU               18          // Power Down Wake Up interrupt
#define INT_SRAMF               19          // SRAM Parity Check Failed interrupt
#define INT_CLKF                20          // Clock Detection Failed interrupt

#define INT_RTC                 22          // Real Time Clock interrupt
#define INT_TAMPER              23          // Tamper detection
#define INT_EXTI0               24          // EXTI Line0 interrupt
#define INT_EXTI1               25          // EXTI Line1 interrupt
#define INT_EXTI2               26          // EXTI Line2 interrupt
#define INT_EXTI3               27          // EXTI Line3 interrupt
#define INT_EXTI4               28          // EXTI Line4 interrupt
#define INT_EXTI5               29          // EXTI Line5 interrupt
#define INT_EXTI6               30          // EXTI Line6 interrupt
#define INT_EXTI7               31          // EXTI Line7 interrupt
#define INT_GPIOA               32          // GPIOA interrupt
#define INT_GPIOB               33          // GPIOB interrupt
#define INT_GPIOC               34          // GPIOC interrupt
#define INT_GPIOD               35          // GPIOD interrupt
#define INT_GPIOE               36          // GPIOE interrupt
#define INT_GPIOF               37          // GPIOF interrupt
#define INT_GPIOG               38          // GPIOG interrupt
#define INT_GPIOH               39          // GPIOH interrupt
#define INT_GPIOI               40          // GPIOI interrupt
#define INT_GPIOJ               41          // GPIOJ interrupt
#define INT_TIMER0              48          // TIM0 global interrupt
#define INT_TIMER1              49          // TIM1 global interrupt
#define INT_TIMER2              50          // TIM2 global interrupt
#define INT_TIMER3              51          // TIM3 global interrupt
#define INT_DMA0                56          // Peripheral DMA interrupt
#define INT_ADC0                58          // ADC interrupt
#define INT_WDT                 62          // Watchdog interrupt
#define INT_WWDT                63          // Window Watch Dog Timer interrupt
#define INT_EADC0               64          // Enhanced ADC 0 interrupt
#define INT_EADC1               65          // Enhanced ADC 1 interrupt
#define INT_EADC2               66          // Enhanced ADC 2 interrupt
#define INT_EADC3               67          // Enhanced ADC 3 interrupt
#define INT_ACMP                72          // Analog Comparator Interrupt
#define INT_OP0                 76          // Analog OP0 interrupt
#define INT_OP1                 77          // Analog OP1 interrupt
#define INT_ICAP0               78          // Internal Capture 0 interrupt
#define INT_ICAP1               79          // Internal Capture 1 interrupt
#define INT_PWMA_0              80          // PWMA Channel 0  interrupt
#define INT_PWMA_1              81          // PWMA Channel 1  interrupt
#define INT_PWMA_2              82          // PWMA Channel 2  interrupt
#define INT_PWMA_3              83          // PWMA Channel 3  interrupt
#define INT_PWMA_4              84          // PWMA Channel 4  interrupt
#define INT_PWMA_5              85          // PWMA Channel 5  interrupt
#define INT_PWMABRK             86          // PWMA Break interrupt
#define INT_QEI0                87          // QEI 0  Interrupt
#define INT_PWMB_0              88          // PWMB Channel 0  interrupt
#define INT_PWMB_1              89          // PWMB Channel 1  interrupt
#define INT_PWMB_2              90          // PWMB Channel 2  interrupt
#define INT_PWMB_3              91          // PWMB Channel 3  interrupt
#define INT_PWMB_4              92          // PWMB Channel 4  interrupt
#define INT_PWMB_5              93          // PWMB Channel 5  interrupt
#define INT_PWMBBRK             94          // PWMB Break interrupt
#define INT_QEI1                95          // QEI 1  Interrupt
#define INT_EPWMA               96          // EPWMA interrupt
#define INT_EPWMABRK            97          // EPWMA Break interrupt
#define INT_EPWMB               98          // EPWMB interrupt
#define INT_EPWMBBRK            99          // EPWMB Break interrupt
#define INT_UDC                 104         // USB device interrupt
#define INT_UHC                 105         // USB Host interrupt
#define INT_USBOTG              106         // USB OTG interrupt
#define INT_EMAC_TX             108         // Ethernet MAC TX Interrupt
#define INT_EMAC_RX             109         // Ethernet MAC RX Interrupt
#define INT_SPI0                112         // SPI0 global interrupt
#define INT_SPI1                113         // SPI1 global interrupt
#define INT_SPI2                114         // SPI2 global interrupt
#define INT_SPI3                115         // SPI3 global interrupt
#define INT_UART0               120         // USART0 global interrupt
#define INT_UART1               121         // USART1 global interrupt
#define INT_UART2               122         // USART2 global interrupt
#define INT_UART3               123         // USART3 global interrupt
#define INT_UART4               124         // USART3 global interrupt
#define INT_UART5               125         // USART3 global interrupt
#define INT_I2C0                128         // I2C0 global interrupt
#define INT_I2C1                129         // I2C1 global interrupt
#define INT_I2C2                130         // I2C2 global interrupt
#define INT_I2C3                131         // I2C3 global interrupt
#define INT_I2C4                132         // I2C4 global interrupt
#define INT_SC0                 136         // Smartcard 0 interrupt
#define INT_SC1                 137         // Smartcard 1 interrupt
#define INT_SC2                 138         // Smartcard 2 interrupt
#define INT_SC3                 139         // Smartcard 3 interrupt
#define INT_SC4                 140         // Smartcard 4 interrupt
#define INT_SC5                 141         // Smartcard 5 interrupt
#define INT_CAN0                144         // CAN0 interrupts
#define INT_CAN1                145         // CAN1 interrupts
#define INT_I2S0                148         // I2S0 interrupt
#define INT_I2S1                149         // I2S1 interrupt
#define INT_SDHOST              152         // SD Host interrupt
#define INT_PS2                 154         // PS/2 device interrupt
#define INT_CAP                 155         // Image capture interrupt
#define INT_CRYPTO              156         // CRYPTO interrupt
#define INT_CRC                 157         // CRC Interrupt

#define INT_ADC1                (INT_EADC0 | INT_EADC1 | INT_EADC2 | INT_EADC3)
#define INT_PWMA                (INT_PWMA_0|INT_PWMA_1|INT_PWMA_2|INT_PWMA_3|INT_PWMA_4|INT_PWMA_5|INT_PWMABRK)
#define INT_PWMB                (INT_PWMB_0|INT_PWMB_1|INT_PWMB_2|INT_PWMB_3|INT_PWMB_4|INT_PWMB_5|INT_PWMBBRK)

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
