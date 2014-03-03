//*****************************************************************************
//
//! \file      xsysctl.h
//! \brief     Prototypes for the System Control Driver.
//! \version   V2.2.1.0
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

#ifndef __XSYSCTL_H__
#define __XSYSCTL_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

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
//! \addtogroup xSysCtl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSysCtl_Peripheral_ID xSysCtl Peripheral ID
//! \brief      Values that show xSysCtl Peripheral ID
//!
//! \section    xSysCtl_Peripheral_ID 1. Where to use this group
//!             Values that can be passed to the
//!             \ref xSysCtlPeripheralEnable()
//!             \ref xSysCtlPeripheralDisable()
//!             \ref xSysCtlPeripheralReset()
//!             APIs as the ulPeripheral parameter.
//!
//! \section    xSysCtl_Peripheral_ID_CoX 2.CoX Port Details
//! +---------------------------+----------------+--------------------------+
//! | SysCtl Peripheral ID      |       CoX      |       LPC17xx            |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_PERIPH_ACMPn      |  Non-Mandatory |           N              |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_PERIPH_ADCn       |    Mandatory   |   xSYSCTL_PERIPH_ADC0    |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_PERIPH_DMA        |  Non-Mandatory |    xSYSCTL_PERIPH_DMA    |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_PERIPH_GPIOn      |    Mandatory   |   xSYSCTL_PERIPH_GPIOA   |
//! |                           |                |--------------------------|
//! |                           |                |   xSYSCTL_PERIPH_GPIOB   |
//! |                           |                |--------------------------|
//! |                           |                |   xSYSCTL_PERIPH_GPIOC   |
//! |                           |                |--------------------------|
//! |                           |                |   xSYSCTL_PERIPH_GPIOD   |
//! |                           |                |--------------------------|
//! |                           |                |   xSYSCTL_PERIPH_GPIOE   |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_PERIPH_I2Cn       |  Non-Mandatory |   xSYSCTL_PERIPH_I2C0    |
//! |                           |                |--------------------------|
//! |                           |                |   xSYSCTL_PERIPH_I2C1    |
//! |                           |                |--------------------------|
//! |                           |                |   xSYSCTL_PERIPH_I2C2    |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_PERIPH_PWMn       |  Non-Mandatory |   xSYSCTL_PERIPH_PWM1    |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_PERIPH_RTC        |    Mandatory   |   xSYSCTL_PERIPH_RTC     |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_PERIPH_SPIn       |    Mandatory   |   xSYSCTL_PERIPH_SPI     |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_PERIPH_TIMERn     |    Mandatory   |   xSYSCTL_PERIPH_TIMER0  |
//! |                           |                |--------------------------|
//! |                           |                |   xSYSCTL_PERIPH_TIMER1  |
//! |                           |                |--------------------------|
//! |                           |                |   xSYSCTL_PERIPH_TIMER2  |
//! |                           |                |--------------------------|
//! |                           |                |   xSYSCTL_PERIPH_TIMER3  |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_PERIPH_UARTn      |    Mandatory   |   xSYSCTL_PERIPH_UART0   |
//! |                           |                |--------------------------|
//! |                           |                |   xSYSCTL_PERIPH_UART1   |
//! |                           |                |--------------------------|
//! |                           |                |   xSYSCTL_PERIPH_UART2   |
//! |                           |                |--------------------------|
//! |                           |                |   xSYSCTL_PERIPH_UART3   |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_PERIPH_WDOG       |    Mandatory   |           N              |
//! +---------------------------+----------------+--------------------------+
//! @{
//
//*****************************************************************************

//! Watchdog
#define xSYSCTL_PERIPH_WDOG             0

//! Timer 0
#define xSYSCTL_PERIPH_TIMER0            SYSCTL_PERIPH_TIMER0

//! Timer 1
#define xSYSCTL_PERIPH_TIMER1            SYSCTL_PERIPH_TIMER1

//! UART 0
#define xSYSCTL_PERIPH_UART0             SYSCTL_PERIPH_UART0

//! UART 1
#define xSYSCTL_PERIPH_UART1             SYSCTL_PERIPH_UART1

//! PWM 1
#define xSYSCTL_PERIPH_PWM1              SYSCTL_PERIPH_PWM1

//! I2C 0
#define xSYSCTL_PERIPH_I2C0              SYSCTL_PERIPH_I2C0

//! The SPI
#define xSYSCTL_PERIPH_SPI               SYSCTL_PERIPH_SPI

//! RTC
#define xSYSCTL_PERIPH_RTC               SYSCTL_PERIPH_RTC

//! SSP 1
#define xSYSCTL_PERIPH_SSP1              SYSCTL_PERIPH_SSP1

//! ADC
#define xSYSCTL_PERIPH_ADC0              SYSCTL_PERIPH_ADC

//! CAN 1
#define xSYSCTL_PERIPH_CAN1              SYSCTL_PERIPH_CAN1

//! CAN 2
#define xSYSCTL_PERIPH_CAN2              SYSCTL_PERIPH_CAN2

//! GPIO A --> P0
#define xSYSCTL_PERIPH_GPIOA             SYSCTL_PERIPH_GPIOA

//! GPIO B --> P1
#define xSYSCTL_PERIPH_GPIOB             SYSCTL_PERIPH_GPIOB

//! GPIO C --> P2
#define xSYSCTL_PERIPH_GPIOC             SYSCTL_PERIPH_GPIOC

//! GPIO D --> P3
#define xSYSCTL_PERIPH_GPIOD             SYSCTL_PERIPH_GPIOD

//! GPIO E --> P4
#define xSYSCTL_PERIPH_GPIOE             SYSCTL_PERIPH_GPIOE

//! Repetitive Interrupt Timer
#define xSYSCTL_PERIPH_RIT               SYSCTL_PERIPH_RIT

//! Motor Control PWM power/clock
#define xSYSCTL_PERIPH_MCPWM             SYSCTL_PERIPH_MCPWM

//! Quadrature Encoder Interface
#define xSYSCTL_PERIPH_QEI               SYSCTL_PERIPH_QEI

//! I2C 1
#define xSYSCTL_PERIPH_I2C1              SYSCTL_PERIPH_I2C1

//! SSP 0
#define xSYSCTL_PERIPH_SSP0              SYSCTL_PERIPH_SSP0

//! Timer 2
#define xSYSCTL_PERIPH_TIMER2            SYSCTL_PERIPH_TIMER2

//! Timer 3
#define xSYSCTL_PERIPH_TIMER3            SYSCTL_PERIPH_TIMER3

//! UART 2
#define xSYSCTL_PERIPH_UART2             SYSCTL_PERIPH_UART2

//! UART 3
#define xSYSCTL_PERIPH_UART3             SYSCTL_PERIPH_UART3

//! I2C 2
#define xSYSCTL_PERIPH_I2C2              SYSCTL_PERIPH_I2C2

//! I2S
#define xSYSCTL_PERIPH_I2S               SYSCTL_PERIPH_I2S

//! General Purpose DMA
#define xSYSCTL_PERIPH_DMA               SYSCTL_PERIPH_GPDMA

//! Ethernet
#define xSYSCTL_PERIPH_ETH               SYSCTL_PERIPH_ETH

//! USB
#define xSYSCTL_PERIPH_USB               SYSCTL_PERIPH_USB

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSysCtl_Clock_Set_Config xSysCtl Clock Set Configuration
//! \brief      Values that show xSysCtl Clock Set Configuration
//!
//! \section    xSysCtl_Clock_Set_Config 1. Where to use this group
//!             Values that can be passed to the xSysCtlClockSet() API as the
//!             ulConfig parameter.
//!
//! \section    xSysCtl_Clock_Set_Config 2. ulConfig parameter description
//!             The ulConfig parameter is the logical OR of several different
//!             values, many of which are grouped into sets where only one can
//!             be chosen. ulConfig contains the external and internal crystal,
//!             main oscillators and PLL disabled options.
//!
//! \section    xSysCtl_Clock_Set_Config_CoX 3.CoX Port Details
//! +---------------------------+----------------+--------------------------+
//! | SysCtl Clock Set Configs  |       CoX      |         LPC17xx          |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_OSC_MAIN          |    Mandatory   |             Y            |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_OSC_INT           |    Mandatory   |             Y            |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_XTAL_nMHZ         |  Non-Mandatory |     xSYSCTL_XTAL_1MHZ    |
//! |                           |                |--------------------------|
//! |                           |                |            ...           |
//! |                           |                |--------------------------|
//! |                           |                |     xSYSCTL_XTAL_8MHZ    |
//! |                           |                |--------------------------|
//! |                           |                |            ...           |
//! |                           |                |--------------------------|
//! |                           |                |    xSYSCTL_XTAL_12MHZ    |
//! |                           |                |--------------------------|
//! |                           |                |            ...           |
//! |                           |                |--------------------------|
//! |                           |                |    xSYSCTL_XTAL_25MHZ    |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_INT_OSC_DIS       |  Non-Mandatory |             Y            |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_MAIN_OSC_DIS      |  Non-Mandatory |             Y            |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_PLL_PWRDN         |  Non-Mandatory |             Y            |
//! +---------------------------+----------------+--------------------------+
//! @{
//
//*****************************************************************************

//! Main Osc
#define xSYSCTL_OSC_MAIN        SYSCTL_OSC_MAIN

//! Internal RC
#define xSYSCTL_OSC_INT         SYSCTL_OSC_INT

//
//! \brief XTAL Select
//
#define xSYSCTL_XTAL_1MHZ       SYSCTL_XTAL_1_MHZ
#define xSYSCTL_XTAL_2MHZ       SYSCTL_XTAL_2_MHZ
#define xSYSCTL_XTAL_3MHZ       SYSCTL_XTAL_3_MHZ
#define xSYSCTL_XTAL_4MHZ       SYSCTL_XTAL_4_MHZ
#define xSYSCTL_XTAL_5MHZ       SYSCTL_XTAL_5_MHZ
#define xSYSCTL_XTAL_6MHZ       SYSCTL_XTAL_6_MHZ
#define xSYSCTL_XTAL_7MHZ       SYSCTL_XTAL_7_MHZ
#define xSYSCTL_XTAL_8MHZ       SYSCTL_XTAL_8_MHZ
#define xSYSCTL_XTAL_9MHZ       SYSCTL_XTAL_9_MHZ
#define xSYSCTL_XTAL_10MHZ      SYSCTL_XTAL_10_MHZ
#define xSYSCTL_XTAL_11MHZ      SYSCTL_XTAL_11_MHZ
#define xSYSCTL_XTAL_12MHZ      SYSCTL_XTAL_12_MHZ
#define xSYSCTL_XTAL_13MHZ      SYSCTL_XTAL_13_MHZ
#define xSYSCTL_XTAL_14MHZ      SYSCTL_XTAL_14_MHZ
#define xSYSCTL_XTAL_15MHZ      SYSCTL_XTAL_15_MHZ
#define xSYSCTL_XTAL_16MHZ      SYSCTL_XTAL_16_MHZ
#define xSYSCTL_XTAL_17MHZ      SYSCTL_XTAL_17_MHZ
#define xSYSCTL_XTAL_18MHZ      SYSCTL_XTAL_18_MHZ
#define xSYSCTL_XTAL_19MHZ      SYSCTL_XTAL_19_MHZ
#define xSYSCTL_XTAL_20MHZ      SYSCTL_XTAL_20_MHZ
#define xSYSCTL_XTAL_21MHZ      SYSCTL_XTAL_21_MHZ
#define xSYSCTL_XTAL_22MHZ      SYSCTL_XTAL_22_MHZ
#define xSYSCTL_XTAL_23MHZ      SYSCTL_XTAL_23_MHZ
#define xSYSCTL_XTAL_24MHZ      SYSCTL_XTAL_24_MHZ
#define xSYSCTL_XTAL_25MHZ      SYSCTL_XTAL_25_MHZ

//
//! Disable internal oscillator
//
#define xSYSCTL_INT_OSC_DIS     SYSCTL_INT_OSC_DIS

//
//! Disable main oscillator
//
#define xSYSCTL_MAIN_OSC_DIS    SYSCTL_MAIN_OSC_DIS

//
//! Disable PLL
//
#define xSYSCTL_PLL_PWRDN       SYSCTL_PLL_PWRDN

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSysCtl_Peripheral_Src_Clk SysCtl Peripheral Source Clock
//! \brief      Values that show SysCtl Peripheral Source Clock
//!             The following are values that can be passed to the
//!             \ref xSysCtlPeripheralClockSourceSet()  API as the ulPeripheralsrc
//!             parameter.
//!
//! \section    xSysCtl_Peripheral_Src_Clk_Def SysCtl Peripheral Short Name define
//!             The macros of General Peripheral Source Clock always like:
//!             <b> ModuleName + n + SourceClock</b>
//!             such as \ref xSYSCTL_WDT_EXTSL, \ref xSYSCTL_ADC0_MAIN.
//!
//! \section    xSysCtl_Peripheral_Src_Clk_CoX CoX Port Details
//! +------------------------------+-----------------+--------------------------+
//! | Peripheral Source Clock Set  |       CoX       |         LPC17xx          |
//! |------------------------------|-----------------|--------------------------|
//! | Those are all Non-Mandatory  |                 |                          |
//! |  parameter,the Mandatory     |                 |                          |
//! |  is variable naming          |  Non-Mandatory  |             Y            |
//! | ModuleName+n+SourceClock     |                 |                          |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_WDT_HCLK             |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_WDT_HCLK             |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_TIMER0_HCLK          |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_TIMER1_HCLK          |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_UART0_HCLK           |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_UART1_HCLK           |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_PWM1_HCLK            |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_I2C0_HCLK            |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_SPI_HCLK             |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_SSP1_HCLK            |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_DAC_HCLK             |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_ADC_HCLK             |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_CAN1_HCLK            |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_CAN2_HCLK            |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_ACF_HCLK             |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_QEI_HCLK             |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_GPIOINT_HCLK         |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_PCB_HCLK             |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_I2C1_HCLK            |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_SSP0_HCLK            |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_TIMER2_HCLK          |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_TIMER3_HCLK          |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_UART2_HCLK           |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_UART3_HCLK           |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_I2C2_HCLK            |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_I2S_HCLK             |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_RIT_HCLK             |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_SYSCON_HCLK          |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//! | xSYSCTL_MC_HCLK              |  Non-Mandatory  |             Y            |
//! |------------------------------|-----------------|--------------------------|
//!
//! @{
//
//*****************************************************************************

//! Watch
#define xSYSCTL_WDT_HCLK               PCLKSEL_WDT

//! Timer 0
#define xSYSCTL_TIMER0_HCLK            PCLKSEL_TIMER0

//! Timer 1
#define xSYSCTL_TIMER1_HCLK            PCLKSEL_TIMER1

//! UART 0
#define xSYSCTL_UART0_HCLK             PCLKSEL_UART0

//! UART 1
#define xSYSCTL_UART1_HCLK             PCLKSEL_UART1

//! PWM 1
#define xSYSCTL_PWM1_HCLK              PCLKSEL_PWM1

//! I2C 0
#define xSYSCTL_I2C0_HCLK              PCLKSEL_I2C0

//! SPI
#define xSYSCTL_SPI_HCLK               PCLKSEL_SPI

//! SSP1
#define xSYSCTL_SSP1_HCLK              PCLKSEL_SSP1

//! DAC
#define xSYSCTL_DAC_HCLK               PCLKSEL_DAC

//! ADC
#define xSYSCTL_ADC_HCLK               PCLKSEL_ADC

//! CAN1
#define xSYSCTL_CAN1_HCLK              PCLKSEL_CAN1

//! CAN2
#define xSYSCTL_CAN2_HCLK              PCLKSEL_CAN2

//! ACF
#define xSYSCTL_ACF_HCLK               PCLKSEL_ACF

//!  Quadrature Encoder Interface
#define xSYSCTL_QEI_HCLK               PCLKSEL_QEI

//! GPIO Interrupt
#define xSYSCTL_GPIOINT_HCLK           PCLKSEL_GPIOINT

//! Pin Connect block
#define xSYSCTL_PCB_HCLK               PCLKSEL_PCB

//! I2C1
#define xSYSCTL_I2C1_HCLK              PCLKSEL_I2C1

//! SSP0
#define xSYSCTL_SSP0_HCLK              PCLKSEL_SSP0

//! Timer 2
#define xSYSCTL_TIMER2_HCLK            PCLKSEL_TIMER2

//! Timer 2
#define xSYSCTL_TIMER3_HCLK            PCLKSEL_TIMER3

//! UART 2
#define xSYSCTL_UART2_HCLK             PCLKSEL_UART2

//! UART 3
#define xSYSCTL_UART3_HCLK             PCLKSEL_UART3

//! I2C 2
#define xSYSCTL_I2C2_HCLK              PCLKSEL_I2C2

//! I2S
#define xSYSCTL_I2S_HCLK               PCLKSEL_I2S

//! Repetitive Interrupt Timer
#define xSYSCTL_RIT_HCLK               PCLKSEL_RIT

//! System Control block
#define xSYSCTL_SYSCON_HCLK            PCLKSEL_SYSCON

//! Motor Control PWM
#define xSYSCTL_MC_HCLK                PCLKSEL_MC

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSysCtl_Peripheral_Short SysCtl Peripheral Short Name
//! \brief      Values that show SysCtl Peripheral Source Clock
//!             The following are values that can be passed to the
//!             xSysCtlPeripheralClockSourceSet2()  API as the ulPeripheral parameter.
//!
//! \section    xSysCtl_Peripheral_Short_Def SysCtl Peripheral Short Name define
//!             The macros of General Peripheral Short Name always like:
//!             <b> ModuleName + n </b>, such as CAN0, ADC0.
//!
//! \section    xSysCtl_Peripheral_Short_CoX CoX Port Details
//! +---------------------------+----------------+--------------------------+
//! | Peripheral Short name     |       CoX      |         LPC17xx          |
//! |---------------------------|----------------|--------------------------|
//! | ADCn                      |  Non-Mandatory |            N             |
//! |---------------------------|----------------|--------------------------|
//! | PWMn                      |  Non-Mandatory |            N             |
//! |---------------------------|----------------|--------------------------|
//! | CANn                      |  Non-Mandatory |            N             |
//! |---------------------------|----------------|--------------------------|
//! | UARTn                     |  Non-Mandatory |            N             |
//! |---------------------------|----------------|--------------------------|
//! | I2Sn                      |  Non-Mandatory |            N             |
//! |---------------------------|----------------|--------------------------|
//! | WDTn                      |  Non-Mandatory |            N             |
//! |---------------------------|----------------|--------------------------|
//! | TIMERn                    |  Non-Mandatory |            N             |
//! |---------------------------|----------------|--------------------------|
//! | I2Cn                      |  Non-Mandatory |            N             |
//! |---------------------------|----------------|--------------------------|
//! | SPIn                      |  Non-Mandatory |            N             |
//! |---------------------------|----------------|--------------------------|
//! | SPIn                      |  Non-Mandatory |            N             |
//! |---------------------------|----------------|--------------------------|
//! | ACMPn                     |  Non-Mandatory |            N             |
//! |---------------------------|----------------|--------------------------|
//! | RTC                       |  Non-Mandatory |            N             |
//! |---------------------------|----------------|--------------------------|
//! | GPIO                      |  Non-Mandatory |            N             |
//! +---------------------------+----------------+--------------------------+
//!
//! +---------------------------+----------------+--------------------------+
//! | Peripheral Clock source   |       CoX      |         LPC17xx          |
//! |---------------------------|----------------|--------------------------|
//! | INT                       |    Mandatory   |             N            |
//! |---------------------------|----------------|--------------------------|
//! | HCLK                      |    Mandatory   |             N            |
//! |---------------------------|----------------|--------------------------|
//! | HCLK_n                    |  Non-Mandatory |             N            |
//! |---------------------------|----------------|--------------------------|
//! | EXTSL                     |    Mandatory   |             N            |
//! |---------------------------|----------------|--------------------------|
//! | INTSL                     |    Mandatory   |             N            |
//! |---------------------------|----------------|--------------------------|
//! | MAIN                      |    Mandatory   |             N            |
//! |---------------------------|----------------|--------------------------|
//! | PLL                       |    Mandatory   |             N            |
//! |---------------------------|----------------|--------------------------|
//! | PLL_n                     |  Non-Mandatory |             N            |
//! |---------------------------|----------------|--------------------------|
//! | EXTTRG                    |  Non-Mandatory |             N            |
//! |---------------------------|----------------|--------------------------|
//! @{
//
//*****************************************************************************

#define MCO                     0
#define I2S2                    0
#define I2S3                    0
#define RTC                     0


//
//! internal high speed oscillator
//
#define INT                     0

//
//! The system clock
//
#define HCLK                    0

//
//! The system clock divide by 2048
//
#define HCLK_2048               0

//
//! external low speed crystal
//
#define EXTSL                   0

//
//! internal low speed oscillator
//
#define INTSL                   0

//
//! external high speed oscillator
//
#define MAIN                    0

//
//! PLL output
//
#define PLL                     0

//
//! PLL output divide by 2
//
#define PLL_2                   0

//
//! external clock input
//
#define EXTTRG                  0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSysCtl_Exported_APIs xSysCtl API
//! \brief      xSysCtl API Reference
//!
//! \section    xSysCtl_Exported_APIs_Port CoX Port Details
//! +----------------------------------+----------------+-----------+
//! | xSysCtl API                      |       CoX      |  LPC17xx  |
//! |----------------------------------|----------------|-----------|
//! | xSysCtlPeripheralReset           |    Mandatory   |     Y     |
//! |----------------------------------|----------------|-----------|
//! | xSysCtlPeripheralEnable          |    Mandatory   |     Y     |
//! |----------------------------------|----------------|-----------|
//! | xSysCtlPeripheralDisable         |    Mandatory   |     Y     |
//! |----------------------------------|----------------|-----------|
//! | xSysCtlPeripheralReset2          |    Mandatory   |     Y     |
//! |----------------------------------|----------------|-----------|
//! | xSysCtlPeripheralEnable2         |    Mandatory   |     Y     |
//! |----------------------------------|----------------|-----------|
//! | xSysCtlPeripheralDisable2        |    Mandatory   |     Y     |
//! |----------------------------------|----------------|-----------|
//! | xSysCtlPeripheraIntNumGet        |    Mandatory   |     Y     |
//! |----------------------------------|----------------|-----------|
//! | xSysCtlClockSet                  |    Mandatory   |     Y     |
//! |----------------------------------|----------------|-----------|
//! | xSysCtlClockGet                  |    Mandatory   |     Y     |
//! |----------------------------------|----------------|-----------|
//! | xSysCtlDelay                     |    Mandatory   |     Y     |
//! |----------------------------------|----------------|-----------|
//! | xSysCtlReset                     |    Mandatory   |     Y     |
//! |----------------------------------|----------------|-----------|
//! | xSysCtlSleep                     |    Mandatory   |     Y     |
//! |----------------------------------|----------------|-----------|
//! | xSysCtlPeripheralClockSourceSet  |    Mandatory   |     Y     |
//! |----------------------------------|----------------|-----------|
//! | xSysCtlPeripheralClockSourceSet2 |    Mandatory   |     N     |
//! |----------------------------------|----------------|-----------|
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Performs a software reset of a peripheral.
//!        This function performs a software reset of the specified peripheral.
//!        An individual peripheral reset signal is asserted for a brief period
//!        and then deasserted, returning the internal state of the peripheral
//!        to its reset condition.
//!
//! \param [in] ulPeripheralID is the peripheral to reset.
//!             This value can be one of the following value:
//!             \ref xSYSCTL_PERIPH_GPIOA
//!             \ref xSYSCTL_PERIPH_I2C0
//!             \ref xSYSCTL_PERIPH_RTC
//!                  ...
//!             \ref xSYSCTL_PERIPH_SPI0
//!             \ref xSYSCTL_PERIPH_TIMER0
//!             \ref xSYSCTL_PERIPH_UART0
//!             More information, please refer to \ref xSysCtl_Peripheral_ID.
//!
//! \return None.
//
//*****************************************************************************
#define xSysCtlPeripheralReset(ulPeripheralID)                                \
        SysCtlPeripheralReset(ulPeripheralID)

//*****************************************************************************
//
//! \brief  Enables a peripheral.
//!         Peripherals are enabled with this function.  At power-up, all
//!         peripherals are disabled; they must be enabled in order to operate
//!         or respond to register reads/writes.
//!
//! \param  [in] ulPeripheralID is the peripheral to enable.
//!              This value can be one of the following value:
//!              \ref xSYSCTL_PERIPH_GPIOA
//!              \ref xSYSCTL_PERIPH_I2C0
//!              \ref xSYSCTL_PERIPH_RTC
//!                   ...
//!              \ref xSYSCTL_PERIPH_SPI0
//!              \ref xSYSCTL_PERIPH_TIMER0
//!              \ref xSYSCTL_PERIPH_UART0
//!              More information, please refer to \ref xSysCtl_Peripheral_ID.
//!
//! \return None.
//!
//! \note   It takes five clock cycles after the write to enable a peripheral
//!         before the the peripheral is actually enabled.  During this time,
//!         attempts to access the peripheral will result in a bus fault.
//!         Care should be taken to ensure that the peripheral is not accessed
//!         during this brief time period.
//
//*****************************************************************************
#define xSysCtlPeripheralEnable(ulPeripheralID)                               \
        SysCtlPeripheralEnable(ulPeripheralID)

//*****************************************************************************
//
//! \brief Disable a peripheral.
//!        Peripherals are disabled with this function.  Once disabled, they
//!        will not operate or respond to register reads/writes.
//!
//! \param [in] ulPeripheralID is the peripheral to disable.
//!             This value can be one of the following value:
//!             \ref xSYSCTL_PERIPH_GPIOA
//!             \ref xSYSCTL_PERIPH_I2C0
//!             \ref xSYSCTL_PERIPH_RTC
//!                  ...
//!             \ref xSYSCTL_PERIPH_SPI0
//!             \ref xSYSCTL_PERIPH_TIMER0
//!             \ref xSYSCTL_PERIPH_UART0
//!             More information, please refer to \ref xSysCtl_Peripheral_ID.
//!
//! \return None.
//
//*****************************************************************************
#define xSysCtlPeripheralDisable(ulPeripheralID)                              \
        SysCtlPeripheralDisable(ulPeripheralID)

//*****************************************************************************
//
//! \brief Enable a peripheral.
//!        Peripherals are enabled with this function.  At power-up, all
//!        peripherals are disabled; they must be enabled in order to operate
//!        or respond to register reads/writes.
//!
//! \param ulPeripheralBase a Peripheral base indicate which peripheral to be enabled.
//!        The \e ulPeripheral parameter must be only one of the following values:
//!        \ref xETH_BASE
//!        \ref xDMA0_BASE
//!        \ref xUSB_BASE
//!        \ref xGPIO_PORTA_BASE
//!        \ref xGPIO_PORTB_BASE
//!        \ref xGPIO_PORTC_BASE
//!        \ref xGPIO_PORTD_BASE
//!        \ref xGPIO_PORTE_BASE
//!        \ref xWDT_BASE
//!        \ref xTIMER0_BASE
//!        \ref xTIMER1_BASE
//!        \ref xUART0_BASE
//!        \ref xUART1_BASE
//!        \ref xPWM0_BASE
//!        \ref xI2C0_BASE
//!        \ref xSPI0_BASE
//!        \ref xRTC_BASE
//!        \ref xSSP1_BASE
//!        \ref xADC0_BASE
//!        \ref xCAN1_BASE
//!        \ref xCAN2_BASE
//!        \ref xI2C1_BASE
//!        \ref xSSP0_BASE
//!        \ref xDAC0_BASE
//!        \ref xTIMER2_BASE
//!        \ref xTIMER3_BASE
//!        \ref xUART2_BASE
//!        \ref xUART3_BASE
//!        \ref xI2C2_BASE
//!        \ref xI2S_BASE
//!        \ref xRIT_BASE
//!        \ref xMCPWM_BASE
//!        \ref xQEI_BASE
//!             ...
//!        More information, please Refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \return None.
//
//*****************************************************************************
#define xSysCtlPeripheralEnable2(ulPeripheralBase)                            \
         SysCtlPeripheralEnable2(ulPeripheralBase)

//*****************************************************************************
//
//! \brief Disable a peripheral.
//!        Peripherals are disabled with this function. At power-up, all
//!        peripherals are disabled; they must be enabled in order to operate
//!        or respond to register reads/writes.
//!
//! \param  [in] ulPeripheralBase a Peripheral base indicate which peripheral
//!              to be enabled. The \e ulPeripheral parameter must be only one
//!              of the following values:
//!              \ref xETH_BASE
//!              \ref xDMA0_BASE
//!              \ref xUSB_BASE
//!              \ref xGPIO_PORTA_BASE
//!              \ref xGPIO_PORTB_BASE
//!              \ref xGPIO_PORTC_BASE
//!              \ref xGPIO_PORTD_BASE
//!              \ref xGPIO_PORTE_BASE
//!              \ref xWDT_BASE
//!              \ref xTIMER0_BASE
//!              \ref xTIMER1_BASE
//!              \ref xUART0_BASE
//!              \ref xUART1_BASE
//!              \ref xPWM0_BASE
//!              \ref xI2C0_BASE
//!              \ref xSPI0_BASE
//!              \ref xRTC_BASE
//!              \ref xSSP1_BASE
//!              \ref xADC0_BASE
//!              \ref xCAN1_BASE
//!              \ref xCAN2_BASE
//!              \ref xI2C1_BASE
//!              \ref xSSP0_BASE
//!              \ref xDAC0_BASE
//!              \ref xTIMER2_BASE
//!              \ref xTIMER3_BASE
//!              \ref xUART2_BASE
//!              \ref xUART3_BASE
//!              \ref xI2C2_BASE
//!              \ref xI2S_BASE
//!              \ref xRIT_BASE
//!              \ref xMCPWM_BASE
//!              \ref xQEI_BASE
//!                   ...
//!              More information, please Refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \return None.
//
//*****************************************************************************
#define xSysCtlPeripheralDisable2(ulPeripheralBase)                           \
         SysCtlPeripheralDisable2(ulPeripheralBase)

//*****************************************************************************
//
//! \brief  Reset a peripheral.
//!         Peripherals are Reset with this function. At power-up, all peripherals
//!         are disabled; they must be enabled in order to operate or respond to
//!         register reads/writes.
//!
//! \param  [in] ulPeripheralBase a Peripheral base indicate which peripheral to
//!              be Reset. Details please Refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \return None.
//
//*****************************************************************************
#define xSysCtlPeripheralReset2(ulPeripheralBase)                             \
         SysCtlPeripheralReset2(ulPeripheralBase)

//*****************************************************************************
//
//! \brief  Get the peripheral interrupt number through peripheral base.
//!
//! \param  [in] ulPeripheral The peripheral's base
//!
//! \return None.
//!
//! \note   It's especially useful to enable the short pin's corresponding
//!         peripheral interrupt: Use the short pin to Get the GPIO base through
//!         \ref xGPIOSPinToPort function, and then use this function to enable
//!         the GPIO interrupt.
//
//*****************************************************************************
#define xSysCtlPeripheraIntNumGet(ulPeripheralBase)                           \
         SysCtlPeripheraIntNumGet(ulPeripheralBase)

//*****************************************************************************
//
//! \brief  Set the clocking of the device.
//!         This function configures the clocking of the device.  The input
//!         crystal frequency, oscillator to be used, use of the PLL, and the
//!         system clock divider are all configured with this function.
//!
//! \param  [in] ulSysClk is target system clock frequency.
//! \param  [in] ulConfig is the required configuration of the device clocking.
//!
//!              The \e ulConfig parameter is the logical OR of several different
//!              values, many of which are grouped into sets where only one can
//!              be chosen.
//!
//!              The external crystal frequency is chosen with one of the
//!              following values:
//!                  \ref xSYSCTL_XTAL_4MHZ
//!                  \ref xSYSCTL_XTAL_5MHZ
//!                  \ref xSYSCTL_XTAL_6MHZ
//!                       ...
//!                  \ref xSYSCTL_XTAL_50MHZ
//!
//!              The oscillator source is chosen with one of the following values:
//!                  \ref xSYSCTL_OSC_MAIN
//!                  \ref xSYSCTL_OSC_INT
//!                  \ref xSYSCTL_OSC_INTSL
//!                  \ref xSYSCTL_OSC_EXTSL
//!
//!              The internal and main oscillators and PLL are disabled with the
//!                  \ref xSYSCTL_INT_OSC_DIS
//!                  \ref xSYSCTL_MAIN_OSC_DIS
//!                  \ref xSYSCTL_PLL_PWRDN
//!
//! \return None.
//!
//! \note   The external oscillator must be enabled in order to use an external
//!         clock source. Note that attempts to disable the oscillator used to
//!         clock the device will be prevented by the hardware.
//
//*****************************************************************************
#define xSysCtlClockSet(ulSysClk, ulConfig)                                   \
        SysCtlClockSet(ulSysClk, ulConfig)

//*****************************************************************************
//
//! \brief  Get the processor clock rate.
//!         This function determines the clock rate of the processor clock.
//!         This is also the clock rate of all the peripheral modules (with the
//!         exception of PWM, which has its own clock divider).
//!
//! \param  None.
//!
//! \return The processor clock rate.
//!
//! \note   This will not return accurate results if SysCtlClockSet() has not
//!         been called to configure the clocking of the device, or if the
//!         device is directly clocked from a crystal (or a clock source) that
//!         is not one of the supported crystal frequencies. In the later case,
//!         this function should be modified to directly return the correct
//!         system clock rate.
//
//*****************************************************************************
#define xSysCtlClockGet()                                                     \
         SysCtlClockGet()

//*****************************************************************************
//
//! \brief  Provide a small delay.
//!         This function provides a means of generating a constant length delay.
//!         It is written in assembly to keep the delay consistent across tool
//!         chains, avoiding the need to tune the delay based on the tool chain
//!         in use. The loop takes 3 cycles/loop.
//!
//! \param  ulCount is the number of delay loop iterations to perform.
//!
//!
//! \return None.
//
//*****************************************************************************
#define xSysCtlDelay(ulCount)                                                 \
         SysCtlDelay(ulCount)

//*****************************************************************************
//
//! \brief  Reset the device.
//!         This function will perform a software reset of the entire device.
//!         The processor and all peripherals will be reset and all device
//!         registers will return to their default values (with the exception
//!         of the reset cause register, which will maintain its current value
//!         but have the software reset bit set as well).
//!
//! \return This function does not return.
//
//*****************************************************************************
#define xSysCtlReset()                                                        \
        SysCtlReset()

//*****************************************************************************
//
//! \brief  Put the processor into sleep mode.
//!         This function places the processor into sleep mode; it will not return
//!         until the processor returns to run mode.  The peripherals that are
//!         enabled via SysCtlPeripheralSleepEnable() continue to operate and
//!         can wake up the processor (if automatic clock gating is enabled with
//!         SysCtlPeripheralClockGating(), otherwise all peripherals continue to
//!         operate).
//!
//! \return None.
//
//*****************************************************************************
#define xSysCtlSleep()                                                        \
        SysCtlSleep()

//*****************************************************************************
//
//! \brief  Set a peripheral clock source and peripheral divide.
//!
//! \param  [in] ulPeripheralSrc is the peripheral clock source to set.
//! \param  [in] ulDivide is the peripheral clock divide to set.
//!
//! \return None.
//!
//! \note   Peripherals clock source are seted with this function.  At power-up,
//!         all Peripherals clock source are Peripherals clock source; they must
//!         be set in order to operate or respond to register reads/writes.
//
//*****************************************************************************
#define xSysCtlPeripheralClockSourceSet(ulPeripheralSrc, ulDivide)            \
        SysCtlPeripheralClockSourceSet(ulPeripheralSrc, ulDivide)

//*****************************************************************************
//
//! \brief  Set a peripheral clock source and peripheral divide.
//!
//! \param  [in] ePeripheral is the peripheral which's clock source will be set.
//! \param  [in] ulPeripheralSrc is the clock source will be set.
//! \param  [in] ulDivide is the peripheral clock divide to set.
//!
//!         The \e ulPeripheralSrc parameter must be only one of the following values:
//!         \ref xSysCtl_Peripheral_Src_Clk_CoX.
//!
//! +--------------------+-------------------------+-----------------------------+
//! |    manufacturer    | ePeripheral             | eSrc                        |
//! |--------------------|-------------------------|-----------------------------|
//! |    CoX Common &    | This parameter is a     | This parameter is a         |
//! |      Mandatory     | mandatory.Mandatory     | mandatory. So it            |
//! |                    | is the format of        | should be: INT              |
//! |                    | Variable naming.So it   | HCLK  HCLK_n EXTSL          |
//! |                    | should be: ADCn,        | INTSL  MAIN  PLL            |
//! |                    | TIMERn or UARTn         | PLL_n  EXTTRG               |
//! |                    | n indicate the pin      | n indicate the pin          |
//! |                    | number such as          | number such as              |
//! |                    | 0 1 2 3 ....            | 0 1 2 3 ....                |
//! |--------------------|-------------------------|-----------------------------|
//! |       LPC17xx      |     ADC0                | MAIN PLL INT                |
//! |                    |     PWMB                | INT HCLK EXTSL MAIN         |
//! |--------------------|-------------------------|-----------------------------|
//!
//! \return None.
//!
//! \note   Peripherals clock source are seted with this function.  At power-up,
//!         all Peripherals clock source are Peripherals clock source; they must
//!         be set in order to operate or respond to register reads/writes.
//
//*****************************************************************************
#define xSysCtlPeripheralClockSourceSet2(ePeripheral, ulPeripheralSrc, ulDivide)


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
//! \addtogroup LPC17xx_SysCtl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SysCtl_Clock_Config LPC17xx SysCtl Clock Configuration
//! \brief LPC17xx SysCtl Clock Configuration
//! The following are values that can be passed to the \ref SysCtlClockSet()
//! API as the ulConfig parameter.
//! @{
//
//*****************************************************************************

// Clock Frequency bit[4:0] mask.
// \note This macro is used for \ref SysCtlClockSet function.
#define SYSCTL_XTAL_nMHZ_MASK          BIT_MASK(32, 4, 0)

//! Main Oscillator 1 Mhz.
#define SYSCTL_XTAL_1_MHZ              1

//! Main Oscillator 2 Mhz
#define SYSCTL_XTAL_2_MHZ              2

//! Main Oscillator 3 Mhz
#define SYSCTL_XTAL_3_MHZ              3

//! Main Oscillator 4 Mhz
#define SYSCTL_XTAL_4_MHZ              4

//! Main Oscillator 5 Mhz
#define SYSCTL_XTAL_5_MHZ              5

//! Main Oscillator 6 Mhz
#define SYSCTL_XTAL_6_MHZ              6

//! Main Oscillator 7 Mhz
#define SYSCTL_XTAL_7_MHZ              7

//! Main Oscillator 8 Mhz
#define SYSCTL_XTAL_8_MHZ              8

//! Main Oscillator 9 Mhz
#define SYSCTL_XTAL_9_MHZ              9

//! Main Oscillator 10 Mhz
#define SYSCTL_XTAL_10_MHZ             10

//! Main Oscillator 11 Mhz
#define SYSCTL_XTAL_11_MHZ             11

//! Main Oscillator 12 Mhz
#define SYSCTL_XTAL_12_MHZ             12

//! Main Oscillator 13 Mhz
#define SYSCTL_XTAL_13_MHZ             13

//! Main Oscillator 14 Mhz
#define SYSCTL_XTAL_14_MHZ             14

//! Main Oscillator 15 Mhz
#define SYSCTL_XTAL_15_MHZ             15

//! Main Oscillator 16 Mhz
#define SYSCTL_XTAL_16_MHZ             16

//! Main Oscillator 17 Mhz
#define SYSCTL_XTAL_17_MHZ             17

//! Main Oscillator 18 Mhz
#define SYSCTL_XTAL_18_MHZ             18

//! Main Oscillator 19 Mhz
#define SYSCTL_XTAL_19_MHZ             19

//! Main Oscillator 20 Mhz
#define SYSCTL_XTAL_20_MHZ             20

//! Main Oscillator 21 Mhz
#define SYSCTL_XTAL_21_MHZ             21

//! Main Oscillator 22 Mhz
#define SYSCTL_XTAL_22_MHZ             22

//! Main Oscillator 23 Mhz
#define SYSCTL_XTAL_23_MHZ             23

//! Main Oscillator 24 Mhz
#define SYSCTL_XTAL_24_MHZ             24

//! Main Oscillator 25Mhz
#define SYSCTL_XTAL_25_MHZ             25

//! Device Maximum Clock Speed,120Mhz for LPC1759/LPC1759, 100MHz for others Device.
#define SYSTEM_CLOCK_MAX               ((unsigned long)120000000)

//! Use Main Oscillator as input clock source.
#define SYSCTL_OSC_MAIN                BIT_32_5

//! Use Internal Oscillator as input clock source.
#define SYSCTL_OSC_INT                 BIT_32_6

//! Disable Internal Oscillator.
#define SYSCTL_INT_OSC_DIS             BIT_32_7

//! Disable Main Oscillator.
#define SYSCTL_MAIN_OSC_DIS            BIT_32_8

//! Power Down PLL Module.
#define SYSCTL_PLL_PWRDN               BIT_32_9

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SysCtl_ExtInt_Config LPC17xx SysCtl External Interrupt
//!             Configure.
//! \brief LPC17xx SysCtl External Interrupt Configuration.
//!
//! The following are values that can be passed to the following function:
//!     - \ref SysCtlExtIntCfg
//!     - \ref SysCtlExtIntFlagGet
//!     - \ref SysCtlExtIntFlagCheck
//!     - \ref SysCtlExtIntFlagClear
//! As the input/output parameter.
//! @{
//
//*****************************************************************************

//! External Interrupt channel 0
#define EXT_INT_0                      BIT_32_0

//! External Interrupt channel 0
#define EXT_INT_1                      BIT_32_1

//! External Interrupt channel 0
#define EXT_INT_2                      BIT_32_2

//! External Interrupt channel 0
#define EXT_INT_3                      BIT_32_3

//! \internal
//! External Interrupt channel mask
#define EXT_INT_MASK                   BIT_MASK(32, 3, 0)

//! External Interrupt type: High level trigger
#define EXT_INT_LV_H                   BIT_32_0

//! External Interrupt type: Low level trigger
#define EXT_INT_LV_L                   BIT_32_1

//! External Interrupt type: Rising edge trigger
#define EXT_INT_EG_R                   BIT_32_2

//! External Interrupt type: Falling edge trigger
#define EXT_INT_EG_F                   BIT_32_3

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SysCtl_Reset_Config LPC17xx Sysctl Reset Configure.
//! \brief      LPC17xx SysCtl Reset source configuration.
//!
//! Those macro can be used in the following functions:
//!     - \ref SysCtlResetFlagGet
//!     - \ref SysCtlResetFlagCheck
//! @{
//
//*****************************************************************************

//! Power on reset
#define RESET_FLAG_POR                 RSID_POR

//! External reset signal
#define RESET_FLAG_EXTR                RSID_EXTR

//! Watchdog Timer reset
#define RESET_FLAG_WDTR                RSID_WDTR

//! Brown-out reset
#define RESET_FLAG_BODR                RSID_BODR

//! System reset requet reset
#define RESET_FLAG_SYSRESET            RSID_SYSRESET

//! Lockup reset
#define RESET_FLAG_LOCKUP              RSID_LOCKUP

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SysCtl_PeripheralClock_Config LPC17xx Sysctl Peripheral
//!             Clock Configure.
//! \brief      LPC17xx SysCtl Peripheral Clock Configure configuration.
//!
//! Those macro can be used in the following functions:
//!     - \ref SysCtlPeripheralClockCfg
//! @{
//
//*****************************************************************************

//! Peripheral Clock for WatchDog.
#define PCLKSEL_WDT                    PCLKSEL0_WDT_S

//! Peripheral Clock for Timer0.
#define PCLKSEL_TIMER0                 PCLKSEL0_TIMER0_S

//! Peripheral Clock for Timer1.
#define PCLKSEL_TIMER1                 PCLKSEL0_TIMER1_S

//! Peripheral Clock for UART0.
#define PCLKSEL_UART0                  PCLKSEL0_UART0_S

//! Peripheral Clock for UART1.
#define PCLKSEL_UART1                  PCLKSEL0_UART1_S

//! Peripheral Clock for PWM1.
#define PCLKSEL_PWM1                   PCLKSEL0_PWM1_S

//! Peripheral Clock for I2C0.
#define PCLKSEL_I2C0                   PCLKSEL0_I2C0_S

//! Peripheral Clock for SPI.
#define PCLKSEL_SPI                    PCLKSEL0_SPI_S

//! Peripheral Clock for SSP1.
#define PCLKSEL_SSP1                   PCLKSEL0_SSP1_S

//! Peripheral Clock for DAC.
#define PCLKSEL_DAC                    PCLKSEL0_DAC_S

//! Peripheral Clock for ADC.
#define PCLKSEL_ADC                    PCLKSEL0_ADC_S

//! Peripheral Clock for CAN1.
#define PCLKSEL_CAN1                   PCLKSEL0_CAN1_S

//! Peripheral Clock for CAN2.
#define PCLKSEL_CAN2                   PCLKSEL0_CAN2_S

//! Peripheral Clock for ACF.
#define PCLKSEL_ACF                    PCLKSEL0_ACF_S

//! Peripheral Clock for QEI.
#define PCLKSEL_QEI                    (PCLKSEL1_QEI_S     + 32)

//! Peripheral Clock for GPIOINT.
#define PCLKSEL_GPIOINT                (PCLKSEL1_GPIOINT_S + 32)

//! Peripheral Clock for PCB.
#define PCLKSEL_PCB                    (PCLKSEL1_PCB_S     + 32)

//! Peripheral Clock for I2C1.
#define PCLKSEL_I2C1                   (PCLKSEL1_I2C1_S    + 32)

//! Peripheral Clock for SSP0.
#define PCLKSEL_SSP0                   (PCLKSEL1_SSP0_S    + 32)

//! Peripheral Clock for Timer2.
#define PCLKSEL_TIMER2                 (PCLKSEL1_TIMER2_S  + 32)

//! Peripheral Clock for Timer3.
#define PCLKSEL_TIMER3                 (PCLKSEL1_TIMER3_S  + 32)

//! Peripheral Clock for UART2.
#define PCLKSEL_UART2                  (PCLKSEL1_UART2_S   + 32)

//! Peripheral Clock for UART3.
#define PCLKSEL_UART3                  (PCLKSEL1_UART3_S   + 32)

//! Peripheral Clock for I2C2.
#define PCLKSEL_I2C2                   (PCLKSEL1_I2C2_S    + 32)

//! Peripheral Clock for I2S.
#define PCLKSEL_I2S                    (PCLKSEL1_I2S_S     + 32)

//! Peripheral Clock for RIT.
#define PCLKSEL_RIT                    (PCLKSEL1_RIT_S     + 32)

//! Peripheral Clock for System Control.
#define PCLKSEL_SYSCON                 (PCLKSEL1_SYSCON_S  + 32)

//! Peripheral Clock for Motor Control PWM.
#define PCLKSEL_MC                     (PCLKSEL1_MC_S      + 32)

//! Peripheral clock Divider = Cclk/1
#define PCLK_CCLK_DIV_1                BIT_32_0

//! Peripheral clock Divider = Cclk/2
#define PCLK_CCLK_DIV_2                BIT_32_1

//! Peripheral clock Divider = Cclk/4
#define PCLK_CCLK_DIV_4                BIT_32_ALL_0

//! \brief Peripheral clock Divider = Cclk/6
//! \note  This macro is only suit for CAN1/CAN2.
#define PCLK_CCLK_DIV_6                (BIT_32_1 | BIT_32_0)

//! Peripheral clock Divider = Cclk/8
#define PCLK_CCLK_DIV_8                (BIT_32_1 | BIT_32_0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SysCtl_Peripheral_Config LPC17xx Sysctl Peripheral
//!             Configure.
//! \brief      LPC17xx SysCtl Peripheral Configure.
//!
//! Those macro can be used in the following functions:
//!     - \ref SysCtlPeripheralReset
//!     - \ref SysCtlPeripheralEnable
//!     - \ref SysCtlPeripheralDisable
//! @{
//
//*****************************************************************************

//! Timer 0
#define SYSCTL_PERIPH_TIMER0           1

//! Timer 1
#define SYSCTL_PERIPH_TIMER1           2

//! UART 0
#define SYSCTL_PERIPH_UART0            3

//! UART 1
#define SYSCTL_PERIPH_UART1            4

//! PWM 1
#define SYSCTL_PERIPH_PWM1             6

//! I2C 0
#define SYSCTL_PERIPH_I2C0             7

//! The SPI
#define SYSCTL_PERIPH_SPI              8

//! RTC
#define SYSCTL_PERIPH_RTC              9

//! SSP 1
#define SYSCTL_PERIPH_SSP1             10

//! ADC
#define SYSCTL_PERIPH_ADC              12

//! CAN 1
#define SYSCTL_PERIPH_CAN1             13

//! CAN 2
#define SYSCTL_PERIPH_CAN2             14

//! GPIO A --> P0
//#define SYSCTL_PERIPH_GPIOA            15

//! GPIO B --> P1
//#define SYSCTL_PERIPH_GPIOB            15

//! GPIO C --> P2
//#define SYSCTL_PERIPH_GPIOC            15

//! GPIO D --> P3
//#define SYSCTL_PERIPH_GPIOD            15

//! GPIO E --> P4
//#define SYSCTL_PERIPH_GPIOE            15

//! Repetitive Interrupt Timer
#define SYSCTL_PERIPH_RIT              16

//! Motor Control PWM power/clock
#define SYSCTL_PERIPH_MCPWM            17

//! Quadrature Encoder Interface
#define SYSCTL_PERIPH_QEI              18

//! I2C 1
#define SYSCTL_PERIPH_I2C1             19

//! SSP 0
#define SYSCTL_PERIPH_SSP0             21

//! Timer 2
#define SYSCTL_PERIPH_TIMER2           22

//! Timer 3
#define SYSCTL_PERIPH_TIMER3           23

//! UART 2
#define SYSCTL_PERIPH_UART2            24

//! UART 3
#define SYSCTL_PERIPH_UART3            25

//! I2C 2
#define SYSCTL_PERIPH_I2C2             26

//! I2S
#define SYSCTL_PERIPH_I2S              27

//! General Purpose DMA
#define SYSCTL_PERIPH_GPDMA            29

//! Ethernet
#define SYSCTL_PERIPH_ETH              30

//! USB
#define SYSCTL_PERIPH_USB              31

//! GPIO A --> P0
#define SYSCTL_PERIPH_GPIOA            32

//! GPIO B --> P1
#define SYSCTL_PERIPH_GPIOB            33

//! GPIO C --> P2
#define SYSCTL_PERIPH_GPIOC            34

//! GPIO D --> P3
#define SYSCTL_PERIPH_GPIOD            35

//! GPIO E --> P4
#define SYSCTL_PERIPH_GPIOE            36
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SysCtl_PowerManager LPC17xx Sysctl PowerManager.
//!
//! \brief      LPC17xx SysCtl PowerManager configuration.
//!
//! Those macro can be used in the following functions:
//!     - \ref SysCtlPwrCfg
//!     - \ref SysCtlPwrFlagCheck
//!     - \ref SysCtlPwrFlagClear
//! @{
//
//*****************************************************************************

//! Sleep Mode
#define PWR_MODE_SLEEP                 BIT_32_0

//! Deep Sleep Mode
#define PWR_MODE_SLEEP_D               BIT_32_1

//! PowerDown Mode
#define PWR_MODE_PWRDOWN               BIT_32_2

//! Deep PowerDown Mode
#define PWR_MODE_PWRDOWN_D             BIT_32_3

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SysCtl_BrownOut_Config LPC17xx Sysctl BrownOut Configure.
//!
//! \brief      LPC17xx SysCtl BrownOut configuration.
//!
//! Those macro can be used in the following functions:
//!     - \ref SysCtlBODCfg
//! @{
//
//*****************************************************************************

//! Enable Brown-Out Reduced Power Mode.
#define BOD_REDUCE_PWR_EN              BIT_32_18

//! Disable Brown-Out Reduced Power Mode.
#define BOD_REDUCE_PWR_DIS             BIT_32_2

//! Enable Global Brown-Out.
#define BOD_GLOBAL_EN                  BIT_32_19

//! Disable Global Brown-Out.
#define BOD_GLOBAL_DIS                 BIT_32_3

//! Enable Brown-Out Reset.
#define BOD_RESET_EN                   BIT_32_20

//! Enable Brown-Out Reset.
#define BOD_RESET_DIS                  BIT_32_4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup LPC17xx_SysCtl_MCO_Config LPC17xx Sysctl MCO Configure.
//!
//! \brief      LPC17xx SysCtl MCO configuration.
//!
//! Those macro can be used in the following functions:
//!     - \ref SysCtlMCOCfg
//! @{
//
//*****************************************************************************
//! Selects the CPU clock as the CLKOUT source.
#define MCO_CLKSRC_CPU               ((unsigned long)0x00)

//! Selects the main oscillator as the CLKOUT source.
#define MCO_CLKSRC_MAIN_OSC          ((unsigned long)0x01)

//! Selects the Internal RC oscillator as the CLKOUT source.
#define MCO_CLKSRC_IRC               ((unsigned long)0x02)

//! Selects the USB clock as the CLKOUT source.
#define MCO_CLKSRC_USB               ((unsigned long)0x03)

//! Selects the RTC oscillator as the CLKOUT source.
#define MCO_CLKSRC_RTC               ((unsigned long)0x04)

//! Clock is divided by 1
#define MCO_CLKDIV_1                 ((unsigned long)0x00)

//! Clock is divided by 2
#define MCO_CLKDIV_2                 ((unsigned long)0x10)

//! Clock is divided by 3
#define MCO_CLKDIV_3                 ((unsigned long)0x20)

//! Clock is divided by 4
#define MCO_CLKDIV_4                 ((unsigned long)0x30)

//! Clock is divided by 5
#define MCO_CLKDIV_5                 ((unsigned long)0x40)

//! Clock is divided by 6
#define MCO_CLKDIV_6                 ((unsigned long)0x50)

//! Clock is divided by 7
#define MCO_CLKDIV_7                 ((unsigned long)0x60)

//! Clock is divided by 8
#define MCO_CLKDIV_8                 ((unsigned long)0x70)

//! Clock is divided by 9
#define MCO_CLKDIV_9                 ((unsigned long)0x80)

//! Clock is divided by 10
#define MCO_CLKDIV_10                ((unsigned long)0x90)

//! Clock is divided by 11
#define MCO_CLKDIV_11                ((unsigned long)0xA0)

//! Clock is divided by 12
#define MCO_CLKDIV_12                ((unsigned long)0xB0)

//! Clock is divided by 13
#define MCO_CLKDIV_13                ((unsigned long)0xC0)

//! Clock is divided by 14
#define MCO_CLKDIV_14                ((unsigned long)0xD0)

//! Clock is divided by 15
#define MCO_CLKDIV_15                ((unsigned long)0xE0)

//! Clock is divided by 16
#define MCO_CLKDIV_16                ((unsigned long)0xF0)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_SysCtl_Exported_APIs LPC17xx SysCtl APIs
//! \brief LPC17xx SysCtl API Reference
//! @{
//
//*****************************************************************************

extern void SysCtlDelay(unsigned long ulCount);
extern void SysCtlClockSet(unsigned long ulSysClk, unsigned long ulConfig);

extern void SysCtlExtIntCfg(unsigned long ulPin, unsigned long ulCfg);
extern unsigned long SysCtlExtIntFlagGet(void);
extern xtBoolean SysCtlExtIntFlagCheck(unsigned long ulFlag);
extern void SysCtlExtIntFlagClear(unsigned long ulFlag);

extern void SysCtlReset(void);
extern unsigned long SysCtlResetFlagGet(void);
extern xtBoolean SysCtlResetFlagCheck(unsigned long ulFlag);
extern void SysCtlResetFlagClear(unsigned long ulFlag);

extern void SysCtlPeripheralClockSourceSet(unsigned long ulPeri, unsigned long ulCfg);
extern unsigned long SysCtlPeripheralClockGet(unsigned long ulPeri);
extern void SysCtlPeripheralReset(unsigned long ulPeripheral);
extern void SysCtlPeripheralEnable(unsigned long ulPeripheral);
extern void SysCtlPeripheralDisable(unsigned long ulPeripheral);

extern unsigned long SysCtlClockGet(void);
extern unsigned long SysCtlHClockGet(void);
//extern unsigned long SysCtlAPB1ClockGet(void);
//extern unsigned long SysCtlAPB2ClockGet(void);

extern unsigned long SysCtlPwrCfg(unsigned long ulMode);
extern void SysCtlBODCfg(unsigned long ulCfg);
extern xtBoolean SysCtlPwrFlagCheck(unsigned long ulFlag);
extern void SysCtlPwrFlagClear(unsigned long ulFlag);

extern void SysCtlMCOCfg(unsigned long ulCfg);
extern void SysCtlMCOEnable(void);
extern void SysCtlMCODisable(void);
extern xtBoolean SysCtlMCOStatusGet(void);

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

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __XSYSCTL_H__

