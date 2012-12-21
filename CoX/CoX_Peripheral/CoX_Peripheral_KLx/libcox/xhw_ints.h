//*****************************************************************************
//
//! \file xhw_ints.h
//! \brief Macros that define the interrupt assignment on KLx.
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
#define xFAULT_SVCALL           FAULT_SVCALL
                                            // SVCall
#define xFAULT_PENDSV           FAULT_PENDSV
                                            // PendSV
#define xFAULT_SYSTICK          FAULT_SYSTICK
                                            // System Tick


#define xINT_SYSCTL             (INT_LVD | (INT_LLWU << 8))
                                            // System Control, special tag

#define xINT_GPIOA              INT_PORTA     // GPIOA
#define xINT_GPIOD              INT_PORTD     // GPIOD

#define xINT_PWMA               INT_FTM0    // PWM Generator A
#define xINT_PWMB               INT_FTM1    // PWM Generator B
#define xINT_PWMC               INT_FTM2    // PWM Generator C

#define xINT_TIMER0             INT_FTM0    // Timer 0 
#define xINT_TIMER1             INT_FTM1    // Timer 1 
#define xINT_TIMER2             INT_FTM2    // Timer 2 

#define xINT_UART0              INT_UART0   // UART0 Rx and Tx
#define xINT_UART1              INT_UART1   // UART1 Rx and Tx
#define xINT_UART2              INT_UART2   // UART2 Rx and Tx

#define xINT_SPI0               INT_SPI0    // SPI0 Rx and Tx
#define xINT_SPI1               INT_SPI1    // SPI1 Rx and Tx

#define xINT_I2C0               INT_I2C0    // I2C0 Master and Slave
#define xINT_I2C1               INT_I2C1    // I2C1 Master and Slave

#define xINT_ACMP0              INT_ACMP    // ACMP0

#define xINT_DMA1               INT_DMA0    // DMA channel 0 transfer complete and error
#define xINT_DMA2               INT_DMA1    // DMA channel 1 transfer complete and error
#define xINT_DMA3               INT_DMA2    // DMA channel 2 transfer complete and error
#define xINT_DMA4               INT_DMA3    // DMA channel 3 transfer complete and error

#define xINT_ADC0               INT_ADC     // ADC0

#define xINT_RTC                (INT_RTCA | (INT_RTCS << 8))
                                            // RTC 

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
//! \addtogroup KLx_LowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup  KLx_LowLayer_Interrupt_Assignments KLx Interrupt Assignments
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

#define INT_DMA0                16          // DMA channel 0 transfer complete and error
#define INT_DMA1                17          // DMA channel 1 transfer complete and error
#define INT_DMA2                18          // DMA channel 2 transfer complete and error
#define INT_DMA3                19          // DMA channel 3 transfer complete and error
#define INT_FTFA                21          // Command complete and read collision
#define INT_LVD                 22          // Low-voltage detect, low-voltage warning
#define INT_LLWU                23          // Low Leakage Wakeup
#define INT_I2C0                24          // I2C0
#define INT_I2C1                25          // I2C1
#define INT_SPI0                26          // Single interrupt vector for all sources
#define INT_SPI1                27          // Single interrupt vector for all sources
#define INT_UART0SE             28          // UART0 Status and error
#define INT_UART1SE             29          // UART1 Status and error
#define INT_UART2SE             30          // UART2 Status and error
#define INT_ADC                 31          // ADC
#define INT_ACMP                32          // ACMP
#define INT_FTM0                33          // Timer 0 
#define INT_FTM1                34          // Timer 1 
#define INT_FTM2                35          // Timer 2 
#define INT_RTCA                36          // Alarm interrupt
#define INT_RTCS                37          // Seconds interrupt
#define INT_PIT                 38          // Single interrupt vector for all channels
#define INT_USBOTG              40          // USBOTG
#define INT_DAC                 41          // DAC
#define INT_TSI                 42          // TSI
#define INT_MCG                 43          // MCG
#define INT_LPTMR               44          // LPTMR
#define INT_PORTA               46          // PORTA
#define INT_PORTD               47          // PORTD

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

