//*****************************************************************************
//
//! \file xhw_memmap.h
//! \brief Macros defining the memory map of the MCU.
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

#ifndef __XHW_MEMMAP_H__
#define __XHW_MEMMAP_H__

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
//! \addtogroup xLowLayer_Peripheral_Memmap xLowLayer Peripheral Memmap
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

#define xFLASH_BASE             0           // Flash memory
#define xSRAM_BASE              0x20000000  // SRAM memory
#define xWDT_BASE               WWDG_BASE   // WatchDog
#define xGPIO_PORTA_BASE        GPIOA_BASE  // GPIOA
#define xGPIO_PORTB_BASE        GPIOB_BASE  // GPIOB
#define xGPIO_PORTC_BASE        GPIOC_BASE  // GPIOC
#define xGPIO_PORTD_BASE        GPIOD_BASE  // GPIOD  
#define xGPIO_PORTE_BASE        GPIOE_BASE  // GPIOE
#define xGPIO_PORTF_BASE        GPIOF_BASE  // GPIOF
#define xGPIO_PORTG_BASE        GPIOG_BASE  // GPIOG

#define xUART1_BASE             USART1_BASE // UART0
#define xUART2_BASE             USART2_BASE // UART1
#define xUART3_BASE             USART3_BASE // UART2
#define xUART4_BASE             USART4_BASE // UART3
#define xUART5_BASE             USART5_BASE // UART4

#define xTIMER1_BASE            TIM1_BASE   // Timer0
#define xTIMER2_BASE            TIM2_BASE   // Timer1
#define xTIMER3_BASE            TIM3_BASE   // Timer2
#define xTIMER4_BASE            TIM4_BASE   // Timer3
#define xTIMER5_BASE            TIM5_BASE   // Timer4
#define xTIMER6_BASE            TIM6_BASE   // Timer5
#define xTIMER7_BASE            TIM7_BASE   // Timer6
#define xTIMER8_BASE            TIM8_BASE   // Timer7
#define xTIMER9_BASE            TIM9_BASE   // Timer8
#define xTIMER10_BASE           TIM10_BASE  // Timer9
#define xTIMER11_BASE           TIM11_BASE  // Timer10
#define xTIMER12_BASE           TIM12_BASE  // Timer11
#define xTIMER13_BASE           TIM13_BASE  // Timer12
#define xTIMER14_BASE           TIM14_BASE  // Timer13

#define xSPI1_BASE              SPI1_BASE   // SPI0
#define xSPI2_BASE              SPI2_BASE   // SPI1
#define xSPI3_BASE              SPI3_BASE   // SPI2

#define xI2C1_BASE              I2C1_BASE   // I2C1 
#define xI2C2_BASE              I2C2_BASE   // I2C2 

#define xADC1_BASE              ADC1_BASE   // ADC0
#define xADC2_BASE              ADC2_BASE   // ADC1

#define xACMP0_BASE             0           // ACMP
#define xPWMA_BASE              TIM1_BASE   // PWMA
#define xPWMB_BASE              TIM8_BASE   // PWMB
#define xPWMC_BASE              TIM2_BASE   // PWMC
#define xPWMD_BASE              TIM3_BASE   // PWMD
#define xPWME_BASE              TIM4_BASE   // PWME
#define xPWMF_BASE              TIM5_BASE   // PWMF
#define xPWMG_BASE              TIM9_BASE   // PWMG
#define xPWMH_BASE              TIM12_BASE  // PWMH
#define xPWMI_BASE              TIM10_BASE  // PWMI
#define xPWMJ_BASE              TIM11_BASE  // PWMJ
#define xPWMK_BASE              TIM13_BASE  // PWMK
#define xPWML_BASE              TIM14_BASE  // PWML

#define xDMA1_BASE              DMA1_BASE   // DMA

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
//! \addtogroup STM32F1xx_owLayer_Peripheral_Memmap STM32F1xx Peripheral Memmap
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
#define TIM2_BASE               0x40000000  // TIM2 timer
#define TIM3_BASE               0x40000400  // TIM3 timer
#define TIM4_BASE               0x40000800  // TIM4 timer
#define TIM5_BASE               0x40000C00  // TIM5 timer
#define TIM6_BASE               0x40001000  // TIM6 timer
#define TIM7_BASE               0x40001400  // TIM7 timer
#define TIM12_BASE              0x40001800  // TIM12 timer
#define TIM13_BASE              0x40001C00  // TIM13 timer
#define TIM14_BASE              0x40002000  // TIM14 timer
#define RTC_BASE                0x40002800  // RTC
#define WWDG_BASE               0x40002C00  // Window watchdog (WWDG)
#define IWDG_BASE               0x40003000  // Independent watchdog (IWDG)
#define SPI2_BASE               0x40003800  // SPI2/I2S
#define SPI3_BASE               0x40003C00  // SPI3/I2S
#define USART2_BASE             0x40004400  // USART2
#define USART3_BASE             0x40004800  // USART3
#define USART4_BASE             0x40004C00  // USART4
#define USART5_BASE             0x40005000  // USART5
#define I2C1_BASE               0x40005400  // I2C1
#define I2C2_BASE               0x40005800  // I2C2
#define USB_BASE                0x40005C00  // USB device FS registers
#define USBSRAM_BASE            0x40006000  // Shared USB/CAN SRAM 512 bytes
#define CAN1_BASE               0x40006400  // bxCAN1
#define CAN2_BASE               0x40006800  // bxCAN2
#define BKP_BASE                0x40006C00  // Backup registers (BKP)
#define PWR_BASE                0x40007000  // Power control PWR
#define DAC_BASE                0x40007400  // DAC

#define AFIO_BASE               0x40010000  // AFIO
#define EXTI_BASE               0x40010400  // EXTI
#define GPIOA_BASE              0x40010800  // GPIO Port A
#define GPIOB_BASE              0x40010C00  // GPIO Port B
#define GPIOC_BASE              0x40011000  // GPIO Port C
#define GPIOD_BASE              0x40011400  // GPIO Port D
#define GPIOE_BASE              0x40011800  // GPIO Port E
#define GPIOF_BASE              0x40011C00  // GPIO Port F
#define GPIOG_BASE              0x40012000  // GPIO Port G
#define ADC1_BASE               0x40012400  // ADC1
#define ADC2_BASE               0x40012800  // ADC2
#define TIM1_BASE               0x40012C00  // TIM1
#define SPI1_BASE               0x40013000  // SPI1
#define TIM8_BASE               0x40013400  // TIM8
#define USART1_BASE             0x40013800  // USART1
#define ADC3_BASE               0x40013C00  // ADC3
#define TIM9_BASE               0x40014C00  // TIM9
#define TIM10_BASE              0x40015000  // TIM10
#define TIM11_BASE              0x40015400  // TIM11

#define SDIO_BASE               0x40018000  // SDIO
#define DMA1_BASE               0x40020000  // DMA1
#define DMA2_BASE               0x40020400  // DMA2
#define RCC_BASE                0x40021000  // Reset and clock control RCC
#define FMI_BASE                0x40022000  // Flash memory interface
#define CRC_BASE                0x40023000  // CRC
#define ETH_BASE                0x40028000  // Ethernet
#define USBOTG_BASE             0x50000000  // USB OTG FS
#define FSMC_BASE               0xA0000000  // FSMC


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

#endif // __XHW_MEMMAP_H__

