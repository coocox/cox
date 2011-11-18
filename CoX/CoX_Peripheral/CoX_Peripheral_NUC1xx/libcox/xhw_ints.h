//*****************************************************************************
//
//! \file xhw_ints.h
//! \brief Macros that define the interrupt assignment on NUC1xx.
//! \version V2.1.1.1
//! \date 11/14/2011
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

#ifndef __XHW_INTS_H__
#define __XHW_INTS_H__

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
//! \addtogroup xLowLayer_Interrupt_Assignments xLowLayer Interrupt Assignments
//! \brief Macro definitions for the fault/interrupt assignments. 
//!
//! They can be used as ulInterrupt parameters with xIntEnable(), xIntDisable()
//! to enable/disable the interrupt at the core/NVIC level. 
//!
//! @{
//
//*****************************************************************************

#define xFAULT_NMI              FAULT_NMI   // NMI 
#define xFAULT_HARD             FAULT_HARD  // Hard fault
#define xFAULT_MPU              FAULT_MPU   // MPU fault
#define xFAULT_BUS              FAULT_BUS   // Bus fault
#define xFAULT_USAGE            FAULT_USAGE // Usage fault
#define xFAULT_SVCALL           FAULT_SVCALL
                                            // SVCall
#define xFAULT_DEBUG            FAULT_DEBUG // Debug monitor
#define xFAULT_PENDSV           FAULT_PENDSV
                                            // PendSV
#define xFAULT_SYSTICK          FAULT_SYSTICK
                                            // System Tick
#define xINT_SYSCTL             INT_BOD     // System Control
#define xINT_WDT                INT_WDT     // WDT
#define xINT_GPIOA              INT_GPAB    // GPIOA
#define xINT_GPIOB              INT_GPAB    // GPIOB
#define xINT_GPIOC              INT_GPCDE   // GPIOC
#define xINT_GPIOD              INT_GPCDE   // GPIOD
#define xINT_GPIOE              INT_GPCDE   // GPIOE
#define xINT_PWMA               INT_PWMA    // PWM Generator A
#define xINT_PWMB               INT_PWMB    // PWM Generator B
#define xINT_TIMER0             INT_TIMER0  // Timer 0 
#define xINT_TIMER1             INT_TIMER1  // Timer 1 
#define xINT_TIMER2             INT_TIMER2  // Timer 2 
#define xINT_TIMER3             INT_TIMER3  // Timer 3 
#define xINT_UART0              INT_UART02  // UART0 Rx and Tx
#define xINT_UART2              INT_UART02  // UART2 Rx and Tx
#define xINT_UART1              INT_UART1   // UART1 Rx and Tx
#define xINT_SPI0               INT_SPI0    // SPI0 Rx and Tx
#define xINT_SPI1               INT_SPI1    // SPI1 Rx and Tx
#define xINT_SPI2               INT_SPI2    // SPI2 Rx and Tx
#define xINT_SPI3               INT_SPI3    // SPI3 Rx and Tx
#define xINT_I2C0               INT_I2C0    // I2C0 Master and Slave
#define xINT_I2C1               INT_I2C1    // I2C1 Master and Slave
#define xINT_ACMP0              INT_ACMP    // ACMP0
#define xINT_DMA                INT_PDMA    // DMA
#define xINT_ADC0               INT_ADC     // ADC0
#define xINT_RTC                INT_RTC     // RTC

//
//! The total number of interrupts.
//
#define xNUM_INTERRUPTS         47

//
//! The total number of priority levels 
//
#define xNUM_PRIORITY           4

//
//! The Total number of priority levels (bits)
//
#define xNUM_PRIORITY_BITS      2


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
//! \addtogroup NUC1xx_LowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup  NUC1xx_LowLayer_Interrupt_Assignments NUC1xx Interrupt Assignments
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
#define FAULT_MPU               4           // MPU fault
#define FAULT_BUS               5           // Bus fault
#define FAULT_USAGE             6           // Usage fault
#define FAULT_SVCALL            11          // SVCall
#define FAULT_DEBUG             12          // Debug monitor
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
#define INT_UART02              28          // UART0 and UART2 Rx and Tx
#define INT_UART1               29          // UART1 Rx and Tx
#define INT_SPI0                30          // SPI0 Rx and Tx
#define INT_SPI1                31          // SPI1 Rx and Tx
#define INT_SPI2                32          // SPI2 Rx and Tx
#define INT_SPI3                33          // SPI3 Rx and Tx
#define INT_I2C0                34          // I2C0 Master and Slave
#define INT_I2C1                35          // I2C1 Master and Slave
#define INT_CAN0                36          // CAN0
#define INT_USBD                39          // USBD
#define INT_PS2                 40          // PS2
#define INT_ACMP                41          // ACMP
#define INT_PDMA                42          // PDMA
#define INT_I2S                 43          // I2S
#define INT_PWRWU               44          // PWRWU
#define INT_ADC                 45          // ADC
#define INT_RTC                 47          // RTC

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

#endif // __XHW_INTS_H__

