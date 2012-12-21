//*****************************************************************************
//
//! \file xhw_ints.h
//! \brief Macros that define the interrupt assignment on the MCU.
//! \version V2.2.1.0
//! \date 11/20/2011
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

#define xFAULT_NMI              2           // NMI 
#define xFAULT_HARD             3           // Hard fault
#define xFAULT_MPU              4           // MPU fault
#define xFAULT_BUS              5           // Bus fault
#define xFAULT_USAGE            6           // Usage fault
#define xFAULT_SVCALL           11          // SVCall
#define xFAULT_DEBUG            12          // Debug monitor
#define xFAULT_PENDSV           14          // PendSV
#define xFAULT_SYSTICK          15          // System Tick

#define xINT_SYSCTL             INT_RCC     // System Control
#define xINT_WDT                INT_WWDG    // WDT
#define xINT_GPIOA              INT_GPIO    // GPIOA
#define xINT_GPIOB              INT_GPIO    // GPIOB
#define xINT_GPIOC              INT_GPIO    // GPIOC
#define xINT_GPIOD              INT_GPIO    // GPIOD
#define xINT_GPIOE              INT_GPIO    // GPIOE
#define xINT_GPIOF              INT_GPIO    // GPIOF
#define xINT_GPIOG              INT_GPIO    // GPIOG

#define xINT_PWMA               0           // 
#define xINT_PWMB               0           // 

#define xINT_TIMER1             INT_TIM1    // Timer 1 
#define xINT_TIMER2             INT_TIM2    // Timer 2 
#define xINT_TIMER3             INT_TIM3    // Timer 3
#define xINT_TIMER4             INT_TIM4    // Timer 4 
#define xINT_TIMER5             INT_TIM5    // Timer 5
#define xINT_TIMER6             INT_TIM6    // Timer 6 
#define xINT_TIMER7             INT_TIM7    // Timer 7

#define xINT_UART1              INT_USART1  // UART1 Rx and Tx
#define xINT_UART2              INT_USART2  // UART2 Rx and Tx
#define xINT_UART3              INT_USART3  // UART3 Rx and Tx
#define xINT_UART4              INT_UART4   // UART4 Rx and Tx
#define xINT_UART5              INT_UART5   // UART5 Rx and Tx

#define xINT_SPI1               INT_SPI1    // SPI1 Rx and Tx
#define xINT_SPI2               INT_SPI2    // SPI2 Rx and Tx
#define xINT_SPI3               INT_SPI3    // SPI3 Rx and Tx

#define xINT_I2C1               INT_I2C1    // I2C1 Master and Slave
#define xINT_I2C2               INT_I2C2    // I2C2 Master and Slave
#define xINT_ACMP0              0           // ACMP0

#define xINT_DMA1               INT_DMA1    // DMA
#define xINT_DMA2               INT_DMA2    // DMA

#define xINT_ADC0               INT_ADC12   // ADC0

#define xINT_RTC                (INT_RTC | (INT_RTCALARM << 8))

//
//! The total number of interrupts.
//
#define xNUM_INTERRUPTS         NUM_INTERRUPTS

//
//! The total number of priority levels 
//
#define xNUM_PRIORITY           NUM_PRIORITY

//
//! The Total number of priority levels (bits)
//
#define xNUM_PRIORITY_BITS      NUM_PRIORITY_BITS


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
//! \addtogroup STM32F1xx_LowLayer
//! @{
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

#define INT_WWDG                16          // Window Watchdog interrupt
#define INT_PVD                 17          // PVD through EXTI Line detection 
#define INT_TAMPER              18          // Tamper interrupt
#define INT_RTC                 19          // RTC global interrupt
#define INT_FLASH               20          // Flash global interrupt
#define INT_RCC                 21          // RCC global interrupt
#define INT_EXTI0               22          // EXTI Line0 interrupt
#define INT_EXTI1               23          // EXTI Line1 interrupt
#define INT_EXTI2               24          // EXTI Line2 interrupt 
#define INT_EXTI3               25          // EXTI Line3 interrupt
#define INT_EXTI4               26          // EXTI Line4 interrupt 
#define INT_DMA1C1              27          // DMA1 Channel1 global interrupt
#define INT_DMA1C2              28          // DMA1 Channel2 global interrupt
#define INT_DMA1C3              29          // DMA1 Channel3 global interrupt
#define INT_DMA1C4              30          // DMA1 Channel4 global interrupt
#define INT_DMA1C5              31          // DMA1 Channel5 global interrupt
#define INT_DMA1C6              32          // DMA1 Channel6 global interrupt
#define INT_DMA1C7              33          // DMA1 Channel7 global interrupt
#define INT_ADC12               34          // ADC1 and ADC2 global interrupt
#define INT_CAN1TX              35          // CAN1 TX interrupts
#define INT_CAN1RX0             36          // CAN1 RX0 interrupts
#define INT_CAN1RX1             37          // CAN1 RX1 interrupt
#define INT_CAN1SCE             38          // CAN1 SCE interrupt
#define INT_EXTI95              39          // EXTI Line[9:5] interrupts
#define INT_TIM1BRK             40          // TIM1 Break interrupt
#define INT_TIM1UP              41          // TIM1 Update interrupt
#define INT_TIM1TRGCOM          42          // TIM1 Trigger and Commutation
#define INT_TIM1CC              43          // TIM1 Capture Compare interrupt
#define INT_TIM2                44          // TIM2 global interrupt
#define INT_TIM3                45          // TIM3 global interrupt
#define INT_TIM4                46          // TIM4 global interrupt
#define INT_I2C1EV              47          // I2C1 event interrupt
#define INT_I2C1ER              48          // I2C1 error interrupt
#define INT_I2C2EV              49          // I2C2 event interrupt
#define INT_I2C2ER              50          // I2C2 error interrupt
#define INT_SPI1                51          // SPI1 global interrupt
#define INT_SPI2                52          // SPI2 global interrupt
#define INT_USART1              53          // USART1 global interrupt
#define INT_USART2              54          // USART2 global interrupt
#define INT_USART3              55          // USART3 global interrupt
#define INT_EXTI1510            56          // EXTI Line[15:10] interrupts
#define INT_RTCALARM            57          // RTC alarm through EXTI line
#define INT_OTGFSWKUP           58          // USB On-The-Go FS Wakeup
#define INT_TIM5                66          // TIM5 global interrupt
#define INT_SPI3                67          // SPI3 global interrupt
#define INT_UART4               68          // UART4 global interrupt
#define INT_UART5               69          // UART5 global interrupt
#define INT_TIM6                70          // TIM6 global interrupt
#define INT_TIM7                71          // TIM7 global interrupt
#define INT_DMA2C1              72          // DMA2 Channel1 global interrupt
#define INT_DMA2C2              73          // DMA2 Channel2 global interrupt
#define INT_DMA2C3              74          // DMA2 Channel3 global interrupt
#define INT_DMA2C4              75          // DMA2 Channel4 global interrupt
#define INT_DMA2C5              76          // DMA2 Channel5 global interrupt
#define INT_ETH                 77          // Ethernet global interrupt
#define INT_ETHWKUP             78          // Ethernet Wakeup through EXTI line
#define INT_CAN2TX              79          // CAN2 TX interrupts
#define INT_CAN2RX0             80          // CAN2 RX0 interrupts
#define INT_CAN2RX1             81          // CAN2 RX1 interrupt
#define INT_CAN2SCE             82          // CAN2 SCE interrupt
#define INT_OTGFS               83          // USB On The Go FS global interrupt

#define INT_I2C1                (INT_I2C1EV | (INT_I2C1ER << 8))
#define INT_I2C2                (INT_I2C2EV | (INT_I2C2ER << 8))

#define INT_TIM1                0x08290000  // Special "tags"
#define INT_GPIO                0x11030000  // Special "tags"
#define INT_DMA1                0x09110000  // Special "tags"
#define INT_DMA2                0x10210000  // Special "tags"


//
//! The total number of interrupts.
//
#define NUM_INTERRUPTS          84

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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

#endif // __XHW_INTS_H__

