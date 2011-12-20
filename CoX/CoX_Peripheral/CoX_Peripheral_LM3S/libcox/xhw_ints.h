//*****************************************************************************
//
//! \file xhw_ints.h
//! \brief Macros that define the interrupt assignment on Stellaris.
//! \version V2.1.1.0
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

#ifndef __xHW_INTS_H__
#define __xHW_INTS_H__

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

#define xFAULT_NMI              TPIU_BASE
#define xFAULT_HARD             FAULT_HARD
#define xFAULT_MPU              FAULT_MPU
#define xFAULT_BUS              FAULT_BUS
#define xFAULT_USAGE            FAULT_USAGE
#define xFAULT_SVCALL           FAULT_SVCALL
#define xFAULT_DEBUG            FAULT_DEBUG
#define xFAULT_PENDSV           FAULT_PENDSV
#define xFAULT_SYSTICK          FAULT_SYSTICK

#define xINT_ACMP0              (NUM_INTERRUPTS + 1)
#define xINT_ADC0               INT_ADC0SS0
#define xINT_ADC1               INT_ADC1SS0
#define xINT_DMA                (NUM_INTERRUPTS + 2)
#define xINT_GPIOA              INT_GPIOA
#define xINT_GPIOB              INT_GPIOB
#define xINT_GPIOC              INT_GPIOC
#define xINT_GPIOD              INT_GPIOD
#define xINT_GPIOE              INT_GPIOE
#define xINT_SYSCTL             INT_SYSCTL
#define xINT_GPIOF              INT_GPIOF
#define xINT_GPIOG              INT_GPIOG
#define xINT_GPIOH              INT_GPIOH
#define xINT_GPIOJ              INT_GPIOJ

//*****************************************************************************
//
//! \brief Defines for the total number of interrupts.
//
//*****************************************************************************
#define xNUM_INTERRUPTS         71

//*****************************************************************************
//
//! \brief Defines for the total number of priority levels.
//
//*****************************************************************************
#define xNUM_PRIORITY           8

//*****************************************************************************
//
//! \brief Defines for the total number bits  of priority levels.
//
//*****************************************************************************
#define xNUM_PRIORITY_BITS      3

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
//! \addtogroup Stellaris_LowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_LowLayer_Interrupt_Assignments Stellaris Interrupt Assignments
//! \brief Macros defines for the fault/interrupt assignments.
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

#define INT_GPIOA               16          // GPIO Port A
#define INT_GPIOB               17          // GPIO Port B
#define INT_GPIOC               18          // GPIO Port C
#define INT_GPIOD               19          // GPIO Port D
#define INT_GPIOE               20          // GPIO Port E
#define INT_UART0               21          // UART0 Rx and Tx
#define INT_UART1               22          // UART1 Rx and Tx
#define INT_SSI0                23          // SSI0 Rx and Tx
#define INT_I2C0                24          // I2C0 Master and Slave
#define INT_PWM_FAULT           25          // PWM Fault
#define INT_PWM0                26          // PWM Generator 0
#define INT_PWM1                27          // PWM Generator 1
#define INT_PWM2                28          // PWM Generator 2
#define INT_QEI0                29          // Quadrature Encoder 0
#define INT_ADC0SS0             30          // ADC0 Sequence 0
#define INT_ADC0SS1             31          // ADC0 Sequence 1
#define INT_ADC0SS2             32          // ADC0 Sequence 2
#define INT_ADC0SS3             33          // ADC0 Sequence 3
#define INT_WATCHDOG            34          // Watchdog timer
#define INT_TIMER0A             35          // Timer 0 subtimer A
#define INT_TIMER0B             36          // Timer 0 subtimer B
#define INT_TIMER1A             37          // Timer 1 subtimer A
#define INT_TIMER1B             38          // Timer 1 subtimer B
#define INT_TIMER2A             39          // Timer 2 subtimer A
#define INT_TIMER2B             40          // Timer 2 subtimer B
#define INT_COMP0               41          // Analog Comparator 0
#define INT_COMP1               42          // Analog Comparator 1
#define INT_COMP2               43          // Analog Comparator 2
#define INT_SYSCTL              44          // System Control (PLL, OSC, BO)
#define INT_FLASH               45          // FLASH Control
#define INT_GPIOF               46          // GPIO Port F
#define INT_GPIOG               47          // GPIO Port G
#define INT_GPIOH               48          // GPIO Port H
#define INT_UART2               49          // UART2 Rx and Tx
#define INT_SSI1                50          // SSI1 Rx and Tx
#define INT_TIMER3A             51          // Timer 3 subtimer A
#define INT_TIMER3B             52          // Timer 3 subtimer B
#define INT_I2C1                53          // I2C1 Master and Slave
#define INT_QEI1                54          // Quadrature Encoder 1
#define INT_CAN0                55          // CAN0
#define INT_CAN1                56          // CAN1
#define INT_CAN2                57          // CAN2
#define INT_ETH                 58          // Ethernet
#define INT_HIBERNATE           59          // Hibernation module
#define INT_USB0                60          // USB 0 Controller
#define INT_PWM3                61          // PWM Generator 3
#define INT_UDMA                62          // uDMA controller
#define INT_UDMAERR             63          // uDMA Error
#define INT_ADC1SS0             64          // ADC1 Sequence 0
#define INT_ADC1SS1             65          // ADC1 Sequence 1
#define INT_ADC1SS2             66          // ADC1 Sequence 2
#define INT_ADC1SS3             67          // ADC1 Sequence 3
#define INT_I2S0                68          // I2S0
#define INT_EPI0                69          // EPI0
#define INT_GPIOJ               70          // GPIO Port J

//*****************************************************************************
//
//! \brief Defines for the total number of interrupts.
//
//*****************************************************************************
#define NUM_INTERRUPTS          71

//*****************************************************************************
//
//! \brief Defines for the total number of priority levels.
//
//*****************************************************************************
#define NUM_PRIORITY            8

//*****************************************************************************
//
//! \brief Defines for the total number bit of priority levels.
//
//*****************************************************************************
#define NUM_PRIORITY_BITS       3

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

