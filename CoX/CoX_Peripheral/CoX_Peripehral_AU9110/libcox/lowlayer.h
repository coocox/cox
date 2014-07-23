//*****************************************************************************
//
//! \file      lowlayer.h
//! \brief     Macros defining of Peripehral Base and interrupt assignments for AU9110.
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
//! \addtogroup AU9110_LowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_LowLayer_Peripheral_Memmap AU9110 Peripheral Memmap
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

/* Peripheral and SRAM base address */
#define FLASH_BA          ((unsigned long)0x00000000)
#define SRAM_BA           ((unsigned long)0x20000000)
#define AHB_BA            ((unsigned long)0x50000000)
#define APB1_BA           ((unsigned long)0x40000000)

/* Peripheral memory map */

#define WDT_BASE       	   (APB1_BA      + 0x04000)
#define RTC_BASE           (APB1_BA      + 0x08000)
#define TIMER0_BASE        (APB1_BA      + 0x10000)
#define TIMER1_BASE        (APB1_BA      + 0x10020)
#define I2C0_BASE          (APB1_BA      + 0x20000)
#define SPI0_BASE          (APB1_BA      + 0x30000)
#define PWMA_BASE          (APB1_BA      + 0x40000)
#define UART0_BASE         (APB1_BA      + 0x50000)
#define DPWM_BASE          (APB1_BA      + 0x70000)
#define ANA_BASE           (APB1_BA      + 0x80000)
#define BOD_BASE           (APB1_BA      + 0x84000)
#define CRC_BASE           (APB1_BA      + 0x90000)
#define I2S_BASE           (APB1_BA      + 0xA0000)
#define BIQ_BASE           (APB1_BA      + 0xB0000)
#define ALC_BASE           (APB1_BA      + 0xB0048)  
#define ACMP_BASE          (APB1_BA      + 0xD0000)
#define ADC_BASE           (APB1_BA      + 0xE0000)
#define SBRAM_BASE         (APB1_BA      + 0xF0000)   

#define GCR_BASE           (AHB_BA       + 0x00000)
#define CLK_BASE           (AHB_BA       + 0x00200)
#define INT_BASE           (AHB_BA       + 0x00300)
//#define GPIO_MAP_BASE      (AHB_BA       + 0x00400)
#define GPIOA_BASE         (AHB_BA       + 0x4000)
#define GPIOB_BASE         (AHB_BA       + 0x4040)
#define GPIO_DBNCECON_BASE (AHB_BA       + 0x4180)

#define PDMA0_BASE         (AHB_BA       + 0x08000)
#define PDMA1_BASE         (AHB_BA       + 0x08100)
#define PDMA2_BASE         (AHB_BA       + 0x08200)
#define PDMA3_BASE         (AHB_BA       + 0x08300)
#define PDMA_GCR_BASE      (AHB_BA       + 0x08F00)

#define FMC_BASE           (AHB_BA       + 0x0C000)



//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_Interrupt_Assignments AU9110 Interrupt Assignments
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
#define FAULT_SVCALL            11          // SVCall
#define FAULT_PENDSV            14          // PendSV
#define FAULT_SYSTICK           15          // System Tick

#define INT_BOD                 16          // Brown Out detection interrupt
#define INT_WDT                 17          // Watchdog interrupt
#define INT_EINT0               18          // External signal interrupt form PB.0 pin
#define INT_EINT1               19          // External signal interrupt form PB.1 pin
#define INT_GPIOAB              20          // External signal interrupt form PA[15:0]/PB[7:2]
#define INT_ALC                 21          // Automatic Level Control interrupt
#define INT_PWMA                22          // PWM0,PWM1 interrupt
#define INT_TIMER0              24          // Timer 0 interrupt
#define INT_TIMER1              25          // Timer 1 interrupt
#define INT_UART0               28          // USART0 interrupt
#define INT_SPI0                30          // SPI0 interrupt
#define INT_I2C0                34          // I2C0 interrupt
#define INT_TALARM              37          // Temperature Alarm interrupt
#define INT_ACMP                41          // Analog Comparator0 or Comaprator1 Interrupt
#define INT_PDMA                42          // PDMA interrupt
#define INT_I2S                 43          // I2S interrupt
#define INT_CAPS                44          // Capacitive Touch Sensing Relaxation Oscillator Interrupt
#define INT_ADC                 45          // Audio ADC interrupt
#define INT_RTC                 47          // Real time clock interrupt


//
//! The total number of interrupts.
//

#define NUM_INTERRUPTS          47

//
//! The total number of priority levels.
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
