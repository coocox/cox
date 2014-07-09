//*****************************************************************************
//
//! \file LOWLAYER.h
//! \brief Macros defining the memory map of M051.
//! \version V2.1.1.0
//! \date 12/20/2011
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

#ifndef __LOWLAYER_H__
#define __LOWLAYER_H__

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
//! \addtogroup M051_LowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_LowLayer_Peripheral_Memmap M051 LowLayer Peripheral Memmap
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
#define GPIO_DBNCECON_BASE      0x50004180  // GPIO Port DBNCECON
#define UART0_BASE              0x40050000  // UART0
#define UART1_BASE              0x40150000  // UART1
#define TIMER0_BASE             0x40010000  // Timer0
#define TIMER1_BASE             0x40010020  // Timer1
#define TIMER2_BASE             0x40110000  // Timer2
#define TIMER3_BASE             0x40110020  // Timer3
#define SPI0_BASE               0x40030000  // SPI0
#define SPI1_BASE               0x40034000  // SPI1
#define I2C0_BASE               0x40020000  // I2C0
#define I2C1_BASE               0x40120000  // I2C1
#define ADC_BASE                0x400E0000  // ADC
#define ACMP01_BASE             0x400D0000  // ACMP01
#define ACMP23_BASE             0x401D0000  // ACMP23
#define SYSCLK_BASE             0x50000200  // SYSTEM CLOCK
#define GCR_BASE                0x50000000  // GCR
#define INT_BASE                0x50000300  // INT
#define FMC_BASE                0x5000C000  // FMC
#define PWMA_BASE               0x40040000  // PWMA
#define PWMB_BASE               0x40140000  // PWMB
#define NVIC_BASE               0xE000E000  // Nested Vectored Interrupt Ctrl

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup  M051_LowLayer_Interrupt_Assignments M051 Interrupt Assignments
//! \brief Macros defines for the fault/interrupt assignments.
//!
//! They can be used as ulInterrupt parameter with xIntEnable(), xIntDisable()
//! to enable/disable the interrupt at the core/NVIC level.
//!
//! @{
//
//*****************************************************************************

#define FAULT_NMI               2           // NMI fault
#define FAULT_HARD              3           // Hard fault
#define FAULT_SVCALL            11          // SVCall
#define FAULT_PENDSV            14          // PendSV
#define FAULT_SYSTICK           15          // System Tick

#define INT_BOD                 16          // BOD interrupt event
#define INT_WDT                 17          // WDT
#define INT_EINT0               18          // EINT0
#define INT_EINT1               19          // EINT1
#define INT_GPAB                20          // GPIO Port A B
#define INT_GPCDE               21          // GPIO Port C D E
#define INT_PWMA                22          // PWM Generator A
#define INT_PWMB                23          // PWM Generator B
#define INT_TIMER0              24          // Timer 0
#define INT_TIMER1              25          // Timer 1
#define INT_TIMER2              26          // Timer 2
#define INT_TIMER3              27          // Timer 3
#define INT_UART0               28          // UART0 Rx and Tx
#define INT_UART1               29          // UART1 Rx and Tx
#define INT_SPI0                30          // SPI0 Rx and Tx
#define INT_SPI1                31          // SPI1 Rx and Tx
#define INT_I2C0                34          // I2C0 Master and Slave
#define INT_I2C1                35          // I2C1 Master and Slave
#define INT_ACMP01              41          // ACMP01
#define INT_ACMP23              42          // ACMP23
#define INT_PWRWU               44          // PWRWU
#define INT_ADC                 45          // ADC

//
//! The total number of interrupts.
//

#define NUM_INTERRUPTS          47

//
//! The total number of priority levels.
//
#define NUM_PRIORITY            4

//
//! The total number of priority levels (bits).
//
#define NUM_PRIORITY_BITS       2

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

#endif // __LOWLAYER_H__


