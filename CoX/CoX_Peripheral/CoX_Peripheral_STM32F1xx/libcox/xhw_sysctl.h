//*****************************************************************************
//
//! \file xhw_sysctl.h
//! \brief Macros used when accessing the system control hardware.
//! \version V2.1.1.0
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


#ifndef __XHW_SYSCTL_H__
#define __XHW_SYSCTL_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SysCtl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Register STM32F1xx SysCtl Register
//! \brief Here are the detailed info of SysCtl registers. 
//!
//! it contains:
//! - Register offset.
//! - detailed bit-field of the registers.
//! - Enum and mask of the registers.
//! .
//! Users can read or write the registers through xHWREG().
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Register_Offsets STM32F1xx SysCtl Register Offsets(Map)
//! \brief Defines for the system control register addresses.through 
//! <b>SysCtl_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! Clock control register
//
#define RCC_CR                  0x40021000

//
//! Clock configuration register
//
#define RCC_CFGR                0x40021004

//
//! Clock interrupt register
//
#define RCC_CIR                 0x40021008

//
//! APB2 peripheral reset register
//
#define RCC_APB2RSTR            0x4002100C

//
//! APB1 peripheral reset register
//
#define RCC_APB1RSTR            0x40021010

//
//! AHB Peripheral Clock enable register
//
#define RCC_AHBENR              0x40021014

//
//! APB2 peripheral clock enable register
//
#define RCC_APB2ENR             0x40021018

//
//! APB1 peripheral clock enable register
//
#define RCC_APB1ENR             0x4002101C

//
//! Backup domain control register
//
#define RCC_BDCR                0x40021020

//
//! Control/status register
//
#define RCC_CSR                 0x40021024

//
//! AHB peripheral clock reset register
//
#define RCC_AHBRSTR             0x40021028

//
//! Clock configuration register2
//
#define RCC_CFGR2               0x4002102C



//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Register_RCC_CR SysCtl Register RCC_CR
//! \brief Defines for the bit fields in the GCR_PDID register.
//! @{
//
//*****************************************************************************

//
//! PLL3 clock ready flag
//
#define RCC_CR_PLL3RDY          0x20000000

//
//! PLL3 enable
//
#define RCC_CR_PLL3ON           0x10000000

//
//! PLL2 clock ready flag
//
#define RCC_CR_PLL2RDY          0x08000000

//
//! PLL2 enable
//
#define RCC_CR_PLL2ON           0x04000000

//
//! PLL clock ready flag
//
#define RCC_CR_PLLRDY           0x02000000

//
//! PLL enable
//
#define RCC_CR_PLLON            0x01000000

//
//! Clock security system enable
//
#define RCC_CR_CSSON            0x00080000

//
//! External high-speed clock bypass
//
#define RCC_CR_HSEBYP           0x00040000

//
//! External high-speed clock ready flag
//
#define RCC_CR_HSERDY           0x00020000

//
//! HSE clock enable
//
#define RCC_CR_HSEON            0x00010000

//
//! Internal high-speed clock calibration mask
//
#define RCC_CR_HSICAL_M         0x0000FF00

//
//! Internal high-speed clock calibration shift
//
#define RCC_CR_HSICAL_S         8

//
//! Internal high-speed clock trimming mask
//
#define RCC_CR_HSICAL_M         0x000000F8

//
//! Internal high-speed clock trimming shift
//
#define RCC_CR_HSICAL_S         3

//
//! Internal high-speed clock ready flag
//
#define RCC_CR_HSIRDY           0x00000002

//
//! Internal high-speed clock enable
//
#define RCC_CR_HSION            0x00000001


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Register_RCC_CFGR SysCtl Register RCC_CFGR
//! \brief Defines for the bit fields in the RCC_CFGR register.
//! @{
//
//*****************************************************************************

//
//! Microcontroller clock output mask
//
#define RCC_CFGR_MCO_M          0x0F000000

//
//! Microcontroller clock output shift
//
#define RCC_CFGR_MCO_S          24

//
//! USB OTG FS prescaler/USB prescaler
//
#define RCC_CFGR_OTGFSPRE       0x00400000

//
//! PLL multiplication factor mask
//
#define RCC_CFGR_PLLMUL_M       0x003C0000

//
//! PLL multiplication factor shift
//
#define RCC_CFGR_PLLMUL_S       18

//
//! LSB of division factor PREDIV1
//
#define RCC_CFGR_PLLXTPRE       0x00020000

//
//! PLL entry clock source
//
#define RCC_CFGR_PLLSRC         0x00010000

//
//! ADC prescaler mask
//
#define RCC_CFGR_ADCPRE_M       0x0000C000

//
//! ADC prescaler shift
//
#define RCC_CFGR_ADCPRE_S       14

//
//! APB high-speed prescaler (APB2) mask
//
#define RCC_CFGR_PPRE2_M        0x00003800

//
//! APB high-speed prescaler (APB2) shift
//
#define RCC_CFGR_PPRE2_S        11

//
//! APB Low-speed prescaler (APB1) mask
//
#define RCC_CFGR_PPRE1_M        0x00000700

//
//! APB Low-speed prescaler (APB1) shift
//
#define RCC_CFGR_PPRE1_S        8

//
//! AHB prescaler mask
//
#define RCC_CFGR_HPRE_M         0x000000F0

//
//! AHB prescaler shift
//
#define RCC_CFGR_HPRE_S         4

//
//! System clock switch status mask
//
#define RCC_CFGR_SWS_M          0x0000000C

//
//! System clock switch status shift
//
#define RCC_CFGR_SWS_S          2

//
//! System clock switch mask
//
#define RCC_CFGR_SW_M           0x00000003

//
//! System clock switch shift
//
#define RCC_CFGR_SW_S           0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Register_RCC_CIR SysCtl Register RCC_CIR
//! \brief Defines for the bit fields in the RCC_CIR register.
//! @{
//
//*****************************************************************************

//
//! Clock security system interrupt clear
//
#define RCC_CIR_CSSC            0x00800000

//
//! PLL3 Ready Interrupt Clear
//
#define RCC_CIR_PLL3RDYC        0x00400000

//
//! PLL2 Ready Interrupt Clear
//
#define RCC_CIR_PLL2RDYC        0x00200000

//
//! PLL ready interrupt clear
//
#define RCC_CIR_PLLRDYC         0x00100000

//
//! HSE ready interrupt clear
//
#define RCC_CIR_HSERDYC         0x00080000

//
//! HSI ready interrupt clear
//
#define RCC_CIR_HSIRDYC         0x00040000

//
//! LSE ready interrupt clear
//
#define RCC_CIR_LSERDYC         0x00020000

//
//! LSI ready interrupt clear
//
#define RCC_CIR_LSIRDYC         0x00010000

//
//! PLL3 Ready Interrupt Enable
//
#define RCC_CIR_PLL3RDYIE       0x00004000

//
//! PLL2 Ready Interrupt Enable
//
#define RCC_CIR_PLL2RDYIE       0x00002000

//
//! PLL Ready Interrupt Enable
//
#define RCC_CIR_PLLRDYIE        0x00001000

//
//! HSE ready interrupt enable
//
#define RCC_CIR_HSERDYIE        0x00000800

//
//! HSI ready interrupt enable
//
#define RCC_CIR_HSIRDYIE        0x00000400

//
//! LSE ready interrupt enable
//
#define RCC_CIR_LSERDYIE        0x00000200

//
//! LSI ready interrupt enable
//
#define RCC_CIR_LSIRDYIE        0x00000100

//
//! Clock security system interrupt flag
//
#define RCC_CIR_CSSF            0x00000080

//
//! PLL3 Ready Interrupt flag
//
#define RCC_CIR_PLL3RDYF        0x00000040

//
//! PLL2 Ready Interrupt flag
//
#define RCC_CIR_PLL2RDYF        0x00000020

//
//! PLL Ready Interrupt flag
//
#define RCC_CIR_PLLRDYF         0x00000010

//
//! HSE ready interrupt flag
//
#define RCC_CIR_HSERDYF         0x00000008

//
//! HSI ready interrupt flag
//
#define RCC_CIR_HSIRDYF         0x00000004

//
//! LSE ready interrupt flag
//
#define RCC_CIR_LSERDYF         0x00000002

//
//! LSI ready interrupt flag
//
#define RCC_CIR_LSIRDYF         0x00000001


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Register_RCC_APB2RSTR SysCtl Register RCC_APB2RSTR
//! \brief Defines for the bit fields in the RCC_APB2RSTR register.
//! @{
//
//*****************************************************************************

//
//! TIM11 timer reset
//
#define RCC_APB2RSTR_TIM11RST   0x00200000

//
//! TIM10 timer reset
//
#define RCC_APB2RSTR_TIM10RST   0x00100000

//
//! TIM9 timer reset
//
#define RCC_APB2RSTR_TIM9RST    0x00080000

//
//! ADC3 interface reset
//
#define RCC_APB2RSTR_ADC3RST    0x00008000

//
//! USART1 reset
//
#define RCC_APB2RSTR_USART1RST  0x00004000

//
//! TIM8 timer reset
//
#define RCC_APB2RSTR_TIM8RST    0x00002000

//
//! SPI 1 reset
//
#define RCC_APB2RSTR_SPI1RST    0x00001000

//
//! TIM1 timer reset
//
#define RCC_APB2RSTR_TIM1RST    0x00000800

//
//! ADC 2 interface reset
//
#define RCC_APB2RSTR_ADC2RST    0x00000400

//
//! ADC 1 interface reset
//
#define RCC_APB2RSTR_ADC1RST    0x00000200

//
//! I/O port G reset
//
#define RCC_APB2RSTR_IOPGRST    0x00000100

//
//! I/O port F reset
//
#define RCC_APB2RSTR_IOPFRST    0x00000080

//
//! I/O port E reset
//
#define RCC_APB2RSTR_IOPERST    0x00000040

//
//! I/O port D reset
//
#define RCC_APB2RSTR_IOPDRST    0x00000020

//
//! I/O port C reset
//
#define RCC_APB2RSTR_IOPCRST    0x00000010

//
//! I/O port B reset
//
#define RCC_APB2RSTR_IOPBRST    0x00000008

//
//! I/O port A reset
//
#define RCC_APB2RSTR_IOPARST    0x00000004

//
//! Alternate function I/O reset
//
#define RCC_APB2RSTR_AFIORST    0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Register_RCC_APB1RSTR SysCtl Register RCC_APB1RSTR
//! \brief Defines for the bit fields in the RCC_APB1RSTR register.
//! @{
//
//*****************************************************************************

//
//! DAC interface reset
//
#define RCC_APB1RSTR_DACRST     0x20000000

//
//! Power interface reset
//
#define RCC_APB1RSTR_PWRRST     0x10000000

//
//! Backup interface reset
//
#define RCC_APB1RSTR_BKPRST     0x08000000

//
//! CAN2 reset
//
#define RCC_APB1RSTR_CAN2RST    0x04000000

//
//! CAN1 reset
//
#define RCC_APB1RSTR_CAN1RST    0x02000000

//
//! USB reset
//
#define RCC_APB1RSTR_USBRST     0x01000000

//
//! I2C 2 reset
//
#define RCC_APB1RSTR_I2C2RST    0x00400000

//
//! I2C 1 reset
//
#define RCC_APB1RSTR_I2C1RST    0x00200000

//
//! USART 5 reset
//
#define RCC_APB1RSTR_UART5RST   0x00100000

//
//! USART 4 reset
//
#define RCC_APB1RSTR_UART4RST   0x00080000

//
//! USART 3 reset
//
#define RCC_APB1RSTR_USART3RST  0x00040000

//
//! USART 2 reset
//
#define RCC_APB1RSTR_USART2RST  0x00020000

//
//! SPI3 reset
//
#define RCC_APB1RSTR_SPI3RST    0x00008000

//
//! SPI2 reset
//
#define RCC_APB1RSTR_SPI2RST    0x00004000

//
//! Window watchdog reset
//
#define RCC_APB1RSTR_WWDGRST    0x00000800

//
//! Timer 14 reset
//
#define RCC_APB1RSTR_TIM14RST   0x00000100

//
//! Timer 13 reset
//
#define RCC_APB1RSTR_TIM13RST   0x00000080

//
//! Timer 12 reset
//
#define RCC_APB1RSTR_TIM12RST   0x00000040

//
//! Timer 7 reset
//
#define RCC_APB1RSTR_TIM7RST    0x00000020

//
//! Timer 6 reset
//
#define RCC_APB1RSTR_TIM6RST    0x00000010

//
//! Timer 5 reset
//
#define RCC_APB1RSTR_TIM5RST    0x00000008

//
//! Timer 4 reset
//
#define RCC_APB1RSTR_TIM4RST    0x00000004

//
//! Timer 3 reset
//
#define RCC_APB1RSTR_TIM3RST    0x00000002

//
//! Timer 2 reset
//
#define RCC_APB1RSTR_TIM2RST    0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Register_RCC_AHBENR SysCtl Register RCC_AHBENR
//! \brief Defines for the bit fields in the RCC_AHBENR register.
//! @{
//
//*****************************************************************************

//
//! Ethernet MAC RX clock enable
//
#define RCC_AHBENR_ETHMACRXEN 0x00010000

//
//! Ethernet MAC TX clock enable
//
#define RCC_AHBENR_ETHMACTXEN 0x00008000

//
//! Ethernet MAC clock enable
//
#define RCC_AHBENR_ETHMACEN   0x00004000

//
//! USB OTG FS clock enable
//
#define RCC_AHBENR_OTGFSEN    0x00001000

//
//! SDIOclock enable
//
#define RCC_AHBENR_SDIOEN     0x00000400

//
//! FSMC clock enable
//
#define RCC_AHBENR_FSMCEN     0x00000100

//
//! CRC clock enable
//
#define RCC_AHBENR_CRCEN      0x00000040

//
//! FLITF clock enable
//
#define RCC_AHBENR_FLITFEN    0x00000010

//
//! SRAM interface clock enable
//
#define RCC_AHBENR_SRAMEN     0x00000004

//
//! DMA2 clock enable
//
#define RCC_AHBENR_DMA2EN     0x00000002

//
//! DMA1 clock enable
//
#define RCC_AHBENR_DMA1EN     0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Register_RCC_APB2ENR SysCtl Register RCC_APB2ENR
//! \brief Defines for the bit fields in the RCC_APB2ENR register.
//! @{
//
//*****************************************************************************

//
//! TIM11 clock enable
//
#define RCC_APB2ENR_TIM11EN     0x00200000

//
//! TIM10 clock enable
//
#define RCC_APB2ENR_TIM10EN     0x00100000

//
//! TIM9 clock enable
//
#define RCC_APB2ENR_TIM9EN      0x00080000

//
//! ADC3 clock enable
//
#define RCC_APB2ENR_ADC3EN      0x00008000

//
//! USART1 clock enable
//
#define RCC_APB2ENR_USART1EN    0x00004000

//
//! TIM8 clock enable
//
#define RCC_APB2ENR_TIM8EN      0x00002000

//
//! SPI 1 clock enable
//
#define RCC_APB2ENR_SPI1EN      0x00001000

//
//! TIM1 Timer clock enable
//
#define RCC_APB2ENR_TIM1EN      0x00000800

//
//! ADC 2 interface clock enable
//
#define RCC_APB2ENR_ADC2EN      0x00000400

//
//! ADC 1 interface clock enable
//
#define RCC_APB2ENR_ADC1EN      0x00000200

//
//! I/O port G clock enable
//
#define RCC_APB2ENR_IOPGEN      0x00000100

//
//! I/O port F clock enable
//
#define RCC_APB2ENR_IOPFEN      0x00000080

//
//! I/O port E clock enable
//
#define RCC_APB2ENR_IOPEEN      0x00000040

//
//! I/O port D clock enable
//
#define RCC_APB2ENR_IOPDEN      0x00000020

//
//! I/O port C clock enable
//
#define RCC_APB2ENR_IOPCEN      0x00000010

//
//! I/O port B clock enable
//
#define RCC_APB2ENR_IOPBEN      0x00000008

//
//! I/O port A clock enable
//
#define RCC_APB2ENR_IOPAEN      0x00000004

//
//! Alternate function I/O clock enable
//
#define RCC_APB2ENR_AFIOEN      0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Register_RCC_APB1ENR SysCtl Register RCC_APB1ENR
//! \brief Defines for the bit fields in the RCC_APB1ENR register.
//! @{
//
//*****************************************************************************

//
//! DAC interface clock enable
//
#define RCC_APB1ENR_DACEN       0x20000000

//
//! Power interface clock enable
//
#define RCC_APB1ENR_PWREN       0x10000000

//
//! Backup interface clock enable
//
#define RCC_APB1ENR_BKPEN       0x08000000

//
//! CAN2 clock enable
//
#define RCC_APB1ENR_CAN2EN      0x04000000

//
//! CAN1 clock enable
//
#define RCC_APB1ENR_CAN1EN      0x02000000

//
//! USB clock enable
//
#define RCC_APB1ENR_USBEN       0x00800000

//
//! I2C 2 clock enable
//
#define RCC_APB1ENR_I2C2EN      0x00400000

//
//! I2C 1 clock enable
//
#define RCC_APB1ENR_I2C1EN      0x00200000

//
//! USART 5 clock enable
//
#define RCC_APB1ENR_UART5EN     0x00100000

//
//! USART 4 clock enable
//
#define RCC_APB1ENR_UART4EN     0x00080000

//
//! USART 3 clock enable
//
#define RCC_APB1ENR_USART3EN    0x00040000

//
//! USART 2 clock enable
//
#define RCC_APB1ENR_USART2EN    0x00020000

//
//! SPI 3 clock enable
//
#define RCC_APB1ENR_SPI3EN      0x00008000

//
//! SPI 2 clock enable
//
#define RCC_APB1ENR_SPI2EN      0x00004000

//
//! Window watchdog clock enable
//
#define RCC_APB1ENR_WWDGEN      0x00000800

//
//! Timer 14 clock enable
//
#define RCC_APB1ENR_TIM14EN     0x00000100

//
//! Timer 13 clock enable
//
#define RCC_APB1ENR_TIM13EN     0x00000080

//
//! Timer 12 clock enable
//
#define RCC_APB1ENR_TIM12EN     0x00000040

//
//! Timer 7 clock enable
//
#define RCC_APB1ENR_TIM7EN      0x00000020

//
//! Timer 6 clock enable
//
#define RCC_APB1ENR_TIM6EN      0x00000010

//
//! Timer 5 clock enable
//
#define RCC_APB1ENR_TIM5EN      0x00000008

//
//! Timer 4 clock enable
//
#define RCC_APB1ENR_TIM4EN      0x00000004

//
//! Timer 3 clock enable
//
#define RCC_APB1ENR_TIM3EN      0x00000002

//
//! Timer 2 clock enable
//
#define RCC_APB1ENR_TIM2EN      0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Register_RCC_BDCR SysCtl Register RCC_BDCR
//! \brief Defines for the bit fields in the RCC_BDCR register.
//! @{
//
//*****************************************************************************

//
//! Backup domain software reset
//
#define RCC_BDCR_BDRST          0x00010000

//
//! RTC clock enable
//
#define RCC_BDCR_RTCEN          0x00008000

//
//! RTC clock source selection mask
//
#define RCC_BDCR_RTCSEL_M       0x00000300

//
//! RTC clock source selection shift
//
#define RCC_BDCR_RTCSEL_S       8

//
//! External Low Speed oscillator bypass
//
#define RCC_BDCR_LSEBYP         0x00000004

//
//! External Low Speed oscillator ready
//
#define RCC_BDCR_LSERDY         0x00000002

//
//! External Low Speed oscillator enable
//
#define RCC_BDCR_LSEON          0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Register_RCC_CSR SysCtl Register RCC_CSR
//! \brief Defines for the bit fields in the RCC_CSR register.
//! @{
//
//*****************************************************************************

//
//! Low-power reset flag
//
#define RCC_CSR_LPWRRSTF        0x80000000

//
//! Window watchdog reset flag
//
#define RCC_CSR_WWDGRSTF        0x40000000

//
//! Independent watchdog reset flag
//
#define RCC_CSR_IWDGRSTF        0x20000000

//
//! Software reset flag
//
#define RCC_CSR_SFTRSTF         0x10000000

//
//! POR/PDR reset flag
//
#define RCC_CSR_PORRSTF         0x08000000

//
//! PIN reset flag
//
#define RCC_CSR_PINRSTF         0x04000000

//
//! Remove reset flag
//
#define RCC_CSR_RMVF            0x01000000

//
//! Internal low speed oscillator ready
//
#define RCC_CSR_LSIRDY          0x00000002

//
//! Internal low speed oscillator enable
//
#define RCC_CSR_LSION           0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Register_RCC_AHBRSTR SysCtl Register RCC_AHBRSTR
//! \brief Defines for the bit fields in the RCC_AHBRSTR register.
//! @{
//
//*****************************************************************************

//
//! Ethernet MAC reset
//
#define RCC_AHBRSTR_ETHMACRST   0x00004000

//
//! USB OTG FS reset
//
#define RCC_AHBRSTR_OTGFSRST    0x00001000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Register_RCC_CFGR2 SysCtl Register RCC_CFGR2
//! \brief Defines for the bit fields in the RCC_CFGR2 register.
//! @{
//
//*****************************************************************************

//
//! I2S3 clock source
//
#define RCC_CFGR2_I2S3SRC       0x00040000

//
//! I2S2 clock source
//
#define RCC_CFGR2_I2S2SRC       0x00020000

//
//! PREDIV1 entry clock source
//
#define RCC_CFGR2_PREDIV1SRC    0x00010000

//
//! PLL3 Multiplication Factor mask
//
#define RCC_CFGR2_PLL3MUL       0x0000F000

//
//! PLL3 Multiplication Factor shift
//
#define RCC_CFGR2_PLL3MUL       12

//
//! PLL2 Multiplication Factor mask
//
#define RCC_CFGR2_PLL2MUL       0x00000F00

//
//! PLL2 Multiplication Factor shift
//
#define RCC_CFGR2_PLL2MUL       8

//
//! PREDIV2 division factor mask
//
#define RCC_CFGR2_PREDIV2       0x000000F0

//
//! PREDIV2 division factor shift
//
#define RCC_CFGR2_PREDIV2       4

//
//! PREDIV1 division factor mask
//
#define RCC_CFGR2_PREDIV1       0x0000000F

//
//! PREDIV1 division factor shift
//
#define RCC_CFGR2_PREDIV1       0

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

#endif // __XHW_SYSCTL_H__


