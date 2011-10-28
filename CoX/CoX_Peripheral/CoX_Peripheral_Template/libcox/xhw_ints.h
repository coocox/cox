//*****************************************************************************
//
//! \file xhw_ints.h
//! \brief Macros that define the interrupt assignment on the MCU.
//! \version 2.0.0.$Rev: 243 $
//! \date 9/30/2011
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
//! \addtogroup COX_Peripheral_Lib
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
//! \brief Macros defines for the fault/interrupt assignments.
//!
//! They can be used as ulInterrupt parameter with xIntEnable(), xIntDisable()
//! to enable/disable the interrupt at the core/NVIC level. 
//!
//! @{
//
//*****************************************************************************

#define xFAULT_NMI              2           // NMI 
#define xFAULT_HARD             3           // Hard fault
#define xFAULT_MPU              4           // MPU fault
#define xFAULT_BUS              5           // Bus fault
#define xFAULT_USAGE            6           // Usage fault
#define xFAULT_SVCALL           11          // SVCall
#define xFAULT_DEBUG            12          // Debug monitor
#define xFAULT_PENDSV           14          // PendSV
#define xFAULT_SYSTICK          15          // System Tick
#define xINT_SYSCTL             0           // System Control
#define xINT_WDT                0           // WDT
#define xINT_GPIOA              0           // GPIOA
#define xINT_GPIOB              0           // GPIOB
#define xINT_GPIOC              0           // GPIOC
#define xINT_GPIOD              0           // GPIOD
#define xINT_PWMA               0           // PWM Generator A
#define xINT_PWMB               0           // PWM Generator B
#define xINT_TIMER0             0           // Timer 0 
#define xINT_TIMER1             0           // Timer 1 
#define xINT_UART0              0           // UART0 Rx and Tx
#define xINT_UART1              0           // UART1 Rx and Tx
#define xINT_SPI0               0           // SPI0 Rx and Tx
#define xINT_SPI1               0           // SPI1 Rx and Tx
#define xINT_I2C0               0           // I2C0 Master and Slave
#define xINT_I2C1               0           // I2C1 Master and Slave
#define xINT_ACMP0              0           // ACMP0
#define xINT_DMA                0           // DMA
#define xINT_ADC0               0           // ADC0
#define xINT_RTC                0           // RTC

//
//! The total number of interrupts.
//
#define xNUM_INTERRUPTS         16

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
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

#endif // __XHW_INTS_H__

