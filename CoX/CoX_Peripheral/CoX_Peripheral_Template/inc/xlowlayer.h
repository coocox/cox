//*****************************************************************************
//
//! \file      xlowlayer.h
//! \brief     Macros defining of Peripehral Base and interrupt assignments.
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

#ifndef __xLOWLAYER__
#define __xLOWLAYER__

#include "lowlayer.h"
#include "xPort.h"

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Interface
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
//! \addtogroup xLowLayer_Peripheral_Memmap xLowLayer Peripheral Memmap
//! \brief      The following are definitions for the base addresses of the
//!             emories and peripherals.
//!
//! They are always used as ulBase parameters in the peripheral library.
//! The name of a macro for the base address of a peripheral is in  general
//! format as x$Namen$_BASE, e.g. xUART0_BASE.
//!
//! 各个系列的GPIO外设请查看 [GPIO base list](@ref GPIOBaseTemplate) \n
//! 各个系列的TIMER外设请查看 [Timer Base Table](@ref TIMERBaseTemplate) \n
//! 各个系列的PWM外设请查看 [PWM Base Table](@ref PWMBaseTemplate) \n
//! 各个系列的DMA外设请查看 [DMA Base Table](@ref DMABaseTemplate) \n
//! 各个系列的RTC外设请查看 [RTC Base Table](@ref RTCBaseTemplate) \n
//! 各个系列的WDT外设请查看 [WDT Base Table](@ref WDTBaseTemplate) \n
//! 各个系列的UART外设请查看 [UART Base Table](@ref UARTBaseTemplate) \n
//! 各个系列的I2C外设请查看 [I2C Base Table](@ref I2CBaseTemplate) \n
//! 各个系列的SPI外设请查看 [SPI Base Table](@ref SPIBaseTemplate) \n
//! 各个系列的I2S外设请查看 [I2S Base Table](@ref I2SBaseTemplate) \n
//! 各个系列的USB外设请查看 [USB Base Table](@ref USBBaseTemplate) \n
//! 各个系列的CAN外设请查看 [CAN Base Table](@ref CANBaseTemplate) \n
//! 各个系列的WDT外设请查看 [WDT Base Table](@ref WDTBasTemplate) \n
//! 各个系列的ETH外设请查看 [ETH Base Table](@ref ETHBaseTemplate) \n
//! 各个系列的WDT外设请查看 [WDT Base Table](@ref WDTBaseTemplate) \n
//! 各个系列的ADC外设请查看 [ADC Base Table](@ref ADCBaseTemplate) \n
//! 各个系列的DAC外设请查看 [DAC Base Table](@ref DACBaseTemplate) \n
//! 各个系列的ACMP外设请查看 [ACMP Base Table](@ref ACMPBaseTemplate) \n
//!
//! @{
//
//*****************************************************************************

#define xFLASH_BASE             FLASH_BASE
#define xSRAM_BASE              SRAM_BASE
#define xGPIO_PORTA_BASE        GPIOA_BASE
#define xGPIO_PORTB_BASE        GPIOB_BASE
#define xGPIO_PORTC_BASE        GPIOC_BASE
#define xGPIO_PORTD_BASE        GPIOD_BASE
#define xGPIO_PORTE_BASE        GPIOE_BASE
#define xGPIO_PORTF_BASE        GPIOF_BASE
#define xGPIO_PORTG_BASE        GPIOG_BASE
#define xGPIO_PORTH_BASE        GPIOH_BASE
#define xGPIO_PORTI_BASE        GPIOI_BASE
#define xTIMER0_BASE            TIMER0_BASE
#define xTIMER1_BASE            TIMER1_BASE
#define xTIMER2_BASE            TIMER2_BASE
#define xTIMER3_BASE            TIMER3_BASE
#define xTIMER4_BASE            TIMER4_BASE
#define xTIMER5_BASE            TIMER5_BASE
#define xTIMER6_BASE            TIMER6_BASE
#define xTIMER7_BASE            TIMER7_BASE
#define xTIMER8_BASE            TIMER8_BASE
#define xTIMER9_BASE            TIMER9_BASE
#define xTIMER10_BASE           TIMER10_BASE
#define xTIMER11_BASE           TIMER11_BASE
#define xTIMER12_BASE           TIMER12_BASE
#define xTIMER13_BASE           TIMER13_BASE
#define xTIMER14_BASE           TIMER14_BASE
#define xPWMA_BASE              PWMA_BASE
#define xPWMB_BASE              PWMB_BASE
#define xPWMC_BASE              PWMC_BASE
#define xPWMD_BASE              PWMD_BASE
#define xPWME_BASE              PWME_BASE
#define xPWMF_BASE              PWMF_BASE
#define xPWMG_BASE              PWMG_BASE
#define xPWMH_BASE              PWMH_BASE
#define xPWMI_BASE              PWMI_BASE
#define xPWMJ_BASE              PWMJ_BASE
#define xPWMK_BASE              PWMK_BASE
#define xPWML_BASE              PWML_BASE
#define xDMA0_BASE              DMA0_BASE
#define xDMA1_BASE              DMA1_BASE
#define xDMA2_BASE              DMA2_BASE
#define xDMA3_BASE              DMA3_BASE
#define xDMA4_BASE              DMA4_BASE
#define xDMA5_BASE              DMA5_BASE
#define xDMA6_BASE              DMA6_BASE
#define xDMA7_BASE              DMA7_BASE
#define xDMA8_BASE              DMA8_BASE
#define xRTC_BASE               RTC_BASE
#define xWDT_BASE               WWDT_BASE

#define xUART0_BASE             UART0_BASE
#define xUART1_BASE             UART1_BASE
#define xUART2_BASE             UART2_BASE
#define xUART3_BASE             UART3_BASE
#define xUART4_BASE             UART4_BASE
#define xUART5_BASE             UART5_BASE
#define xI2C0_BASE              I2C0_BASE
#define xI2C1_BASE              I2C1_BASE
#define xI2C2_BASE              I2C2_BASE
#define xI2C3_BASE              I2C3_BASE
#define xI2C4_BASE              I2C4_BASE
#define xSPI0_BASE              SPI0_BASE
#define xSPI1_BASE              SPI1_BASE
#define xSPI2_BASE              SPI2_BASE
#define xSPI3_BASE              SPI3_BASE
#define xSPI4_BASE              SPI4_BASE
#define xI2S0_BASE              I2S0_BASE
#define xCAN0_BASE              CAN0_BASE
#define xCAN1_BASE              CAN1_BASE
#define xCAN2_BASE              CAN2_BASE
#define xETH_BASE               ETH_BASE
#define xUSBH_BASE              USBH_BASE
#define xUSBD_BASE              USBD_BASE
#define xQEI_BASE               QEI_BASE

#define xADC0_BASE              ADC0_BASE
#define xADC1_BASE              ADC1_BASE
#define xDAC0_BASE              DAC0_BASE
#define xACMP_BASE              ACMP_BASE

//*****************************************************************************
//
//! @}
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
//! 各个系列的GPIO中断请查看 [GPIO Int list](@ref GPIOIntTemplate) \n
//! 各个系列的TIMER中断请查看 [Timer Base Table](@ref TimerIntTemplate) \n
//! 各个系列的PWM中断请查看 [PWM Base Table](@ref PWMIntTemplate) \n
//! 各个系列的DMA中断请查看 [DMA Base Table](@ref DMAIntTemplate) \n
//! 各个系列的RTC中断请查看 [RTC Base Table](@ref RTCIntTemplate) \n
//! 各个系列的WDT中断请查看 [WDT Base Table](@ref WDTIntTemplate) \n
//! 各个系列的UART中断请查看 [UART Base Table](@ref UARTIntTemplate) \n
//! 各个系列的I2C中断请查看 [I2C Base Table](@ref I2CIntTemplate) \n
//! 各个系列的SPI中断请查看 [SPI Base Table](@ref SPIIntTemplate) \n
//! 各个系列的I2S中断请查看 [I2S Base Table](@ref I2SIntTemplate) \n
//! 各个系列的USB中断请查看 [USB Base Table](@ref USBIntTemplate) \n
//! 各个系列的CAN中断请查看 [CAN Base Table](@ref CANIntTemplate) \n
//! 各个系列的WDT中断请查看 [WDT Base Table](@ref WDTIntTemplate) \n
//! 各个系列的ETH中断请查看 [ETH Base Table](@ref ETHIntTemplate) \n
//! 各个系列的WDT中断请查看 [WDT Base Table](@ref WDTIntTemplate) \n
//! 各个系列的ADC中断请查看 [ADC Base Table](@ref ADCIntTemplate) \n
//! 各个系列的DAC中断请查看 [DAC Base Table](@ref DACIntTemplate) \n
//! 各个系列的ACMP中断请查看 [ACMP Base Table](@ref ACMPIntTemplate) \n
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

#define xINT_SYSCTL             INT_SYSCTL
#define xINT_WDT                INT_WWDT
#define xINT_RTC                INT_RTC
#define xINT_FMC                INT_FMC

#define xINT_GPIOA              INT_GPIOA
#define xINT_GPIOB              INT_GPIOB
#define xINT_GPIOC              INT_GPIOC
#define xINT_GPIOD              INT_GPIOD
#define xINT_GPIOE              INT_GPIOE
#define xINT_GPIOF              INT_GPIOF
#define xINT_GPIOG              INT_GPIOG
#define xINT_GPIOH              INT_GPIOH
#define xINT_GPIOI              INT_GPIOI
#define xINT_GPIOJ              INT_GPIOJ
#define xINT_EINT0              INT_EINT0
#define xINT_EINT1              INT_EINT1
#define xINT_EINT2              INT_EINT2
#define xINT_EINT3              INT_EINT3
#define xINT_EINT4              INT_EINT4
#define xINT_EINT5              INT_EINT5
#define xINT_EINT6              INT_EINT6
#define xINT_EINT7              INT_EINT7
#define xINT_EINT8              INT_EINT8
#define xINT_EINT9              INT_EINT9
#define xINT_EINT10             INT_EINT10
#define xINT_EINT11             INT_EINT11
#define xINT_EINT12             INT_EINT12
#define xINT_EINT13             INT_EINT13
#define xINT_EINT14             INT_EINT14
#define xINT_EINT15             INT_EINT15
#define xINT_TIMER0             INT_TIMER0
#define xINT_TIMER1             INT_TIMER1
#define xINT_TIMER2             INT_TIMER2
#define xINT_TIMER3             INT_TIMER3
#define xINT_TIMER4             INT_TIMER0
#define xINT_TIMER5             INT_TIMER1
#define xINT_TIMER6             INT_TIMER2
#define xINT_TIMER7             INT_TIMER3
#define xINT_PWMA               INT_PWMA
#define xINT_PWMB               INT_PWMB
#define xINT_PWMC               INT_PWMC
#define xINT_DMA0               INT_DMA0
#define xINT_DMA1               INT_DMA1
#define xINT_DMA2               INT_DMA2
#define xINT_QEI                INT_QEI

#define xINT_UART0              INT_UART0
#define xINT_UART1              INT_UART1
#define xINT_UART2              INT_UART2
#define xINT_UART3              INT_UART3
#define xINT_UART4              INT_UART4
#define xINT_UART5              INT_UART5
#define xINT_I2C0               INT_I2C0
#define xINT_I2C1               INT_I2C1
#define xINT_I2C2               INT_I2C2
#define xINT_I2C3               INT_I2C3
#define xINT_I2C4               INT_I2C4
#define xINT_SPI0               INT_SPI0
#define xINT_SPI1               INT_SPI1
#define xINT_SPI2               INT_SPI2
#define xINT_SPI3               INT_SPI3
#define xINT_CAN0               INT_CAN0        
#define xINT_CAN1               INT_CAN1   
#define xINT_I2S0               INT_I2S0
#define xINT_I2S1               INT_I2S1
#define xINT_USBD               INT_USBD
#define xINT_USBH               INT_USBH
#define xINT_ETH                INT_ETH

#define xINT_ADC0               INT_ADC0
#define xINT_ADC1               INT_ADC1
#define xINT_DAC0               INT_DAC0
#define xINT_ACMP               INT_ACMP

//*****************************************************************************
//
//! \brief Defines for the total number of interrupts.
//
//*****************************************************************************
#define xNUM_INTERRUPTS         NUM_INTERRUPTS

//*****************************************************************************
//
//! \brief Defines for the total number of priority levels.
//
//*****************************************************************************
#define xNUM_PRIORITY           NUM_PRIORITY

//*****************************************************************************
//
//! \brief Defines for the total number bits  of priority levels.
//
//*****************************************************************************
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
//! @}
//
//*****************************************************************************

#endif // __xLOWLAYER__
