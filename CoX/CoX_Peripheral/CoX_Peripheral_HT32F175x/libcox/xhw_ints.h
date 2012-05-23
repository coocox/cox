//*****************************************************************************
//
//! \file xhw_ints.h
//! \brief Macros that define the interrupt assignment on HT32F175x_275x.
//! \version V2.2.1.0
//! \date 4/25/2012
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

#define xINT_CLKRDY             INT_CLKRDY  // CLK Ready interrupt
#define xINT_LVD                INT_LVD     // Low voltage detection
#define xINT_BOD                INT_BOD     // BOD interrupt event
#define xINT_WDT                INT_WDT     // WDT
#define xINT_RTC                INT_RTC     // RTC
#define xINT_FMC                INT_FMC     // FMC
#define xINT_EVWUP              INT_EVWUP   // EXTI Event wakeup interrupt
#define xINT_LPWUP              INT_LPWUP   // WAKEUP pin interrupt
#define xINT_GPIOA              INT_GPIOA   // GPIOA
#define xINT_GPIOB              INT_GPIOB   // GPIOB
#define xINT_GPIOC              INT_GPIOC   // GPIOC
#define xINT_GPIOD              INT_GPIOD   // GPIOD
#define xINT_GPIOE              INT_GPIOE   // GPIOE
#define xINT_TIMER0             INT_TIMER0  // Timer 0 
#define xINT_TIMER1             INT_TIMER1  // Timer 1 
#define xINT_UART0              INT_UART0   // UART0 Rx and Tx
#define xINT_SPI0               INT_SPI0    // SPI0 Rx and Tx
#define xINT_SPI1               INT_SPI1    // SPI1 Rx and Tx
#define xINT_I2C0               INT_I2C0    // I2C0 Master and Slave
#define xINT_ACMP0              INT_ACMP    // ACMP0
#define xINT_ADC0               INT_ADC     // ADC0

//
//! The total number of interrupts.
//
#define xNUM_INTERRUPTS         83

//
//! The total number of priority levels 
//
#define xNUM_PRIORITY           16

//
//! The Total number of priority levels (bits)
//
#define xNUM_PRIORITY_BITS      4


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
//! \addtogroup HT32F175x_275x_LowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup  HT32F175x_275x_LowLayer_Interrupt_Assignments HT32F175x_275x 
//! Interrupt Assignments
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

#define INT_CLKRDY              16          // CLK Ready interrupt
#define INT_LVD                 17          // Low voltage detection
#define INT_BOD                 18          // BOD interrupt event
#define INT_WDT                 19          // WDT timer global interrupt
#define INT_RTC                 20          // RTC global interrupt
#define INT_FMC                 21          // FMC global interrupt
#define INT_EVWUP               22          // EXTI Event wakeup interrupt
#define INT_LPWUP               23          // WAKEUP pin interrupt

#define INT_EINT0               24          // EXTI Line 0 interrupt
#define INT_EINT1               25          // EXTI Line 1 interrupt
#define INT_EINT2               26          // EXTI Line 2 interrupt
#define INT_EINT3               27          // EXTI Line 3 interrupt
#define INT_EINT4               28          // EXTI Line 4 interrupt
#define INT_EINT5               29          // EXTI Line 5 interrupt
#define INT_EINT6               30          // EXTI Line 6 interrupt
#define INT_EINT7               31          // EXTI Line 7 interrupt
#define INT_EINT8               32          // EXTI Line 8 interrupt
#define INT_EINT9               33          // EXTI Line 9 interrupt
#define INT_EINT10              34          // EXTI Line 10 interrupt
#define INT_EINT11              35          // EXTI Line 11 interrupt
#define INT_EINT12              36          // EXTI Line 12 interrupt
#define INT_EINT13              37          // EXTI Line 13 interrupt
#define INT_EINT14              38          // EXTI Line 14 interrupt
#define INT_EINT15              39          // EXTI Line 15 interrupt

#define INT_ACMP                40          // Comparator global interrupt
#define INT_ADC                 41          // ADC interrupt
#define INT_MCTMBRK             43          // MCTM break interrupt
#define INT_MCTMUP              44          // MCTM update interrupt
#define INT_MCTMTRUP2           45          // MCTM trigger/update event2 interrupt
#define INT_MCTMCC              46          // MCTM capture/compare interrupt
#define INT_TIMER0              51          // Timer 0 
#define INT_TIMER1              52          // Timer 1 
#define INT_BFTM0               57          // BFTM0 global interrupt
#define INT_BFTM1               58          // BFTM1 global interrupt
#define INT_I2C0                59          // I2C0 global interrupt
#define INT_I2C1                60          // I2C1 global interrupt
#define INT_SPI0                61          // SPI0 global interrupt
#define INT_SPI1                62          // SPI1 global interrupt
#define INT_UART0               63          // UART0 global interrupt
#define INT_UART1               64          // UART1 global interrupt

#define INT_SCI                 67          // SCI global interrupt
#define INT_USB                 69          // USB global interrupt
#define INT_PDMACH0             71          // PDMA CH0 global interrupt
#define INT_PDMACH1             72          // PDMA CH1 global interrupt
#define INT_PDMACH2             73          // PDMA CH2 global interrupt
#define INT_PDMACH3             74          // PDMA CH3 global interrupt
#define INT_PDMACH4             75          // PDMA CH4 global interrupt
#define INT_PDMACH5             76          // PDMA CH5 global interrupt
#define INT_PDMACH6             77          // PDMA CH6 global interrupt
#define INT_PDMACH7             78          // PDMA CH7 global interrupt
#define INT_PDMACH8             79          // PDMA CH8 global interrupt
#define INT_PDMACH9             80          // PDMA CH9 global interrupt
#define INT_PDMACH10            81          // PDMA CH10 global interrupt
#define INT_PDMACH11            82          // PDMA CH11 global interrupt
#define INT_CSIF				83          // CSIF	global interrupt

#define INT_GPIOA               0x00010000  // Special "tags"
#define INT_GPIOB               0x00020000  // Special "tags"
#define INT_GPIOC               0x00030000  // Special "tags"
#define INT_GPIOD               0x00040000  // Special "tags"
#define INT_GPIOE               0x00050000  // Special "tags"

//
//! The total number of interrupts.
//

#define NUM_INTERRUPTS          83

//
//! The total number of priority levels.
//
#define NUM_PRIORITY            16

//
//! The total number of priority levels (bits).
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

