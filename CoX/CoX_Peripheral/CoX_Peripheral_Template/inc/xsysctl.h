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

#include "sysctl.h"
#include "xPort.h"

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
//! \addtogroup CoX_Peripheral_Interface
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
//! +---------------------------+----------------+-----------+
//! | SysCtl Peripheral ID      |       CoX      |  LPC17xx  |
//! |---------------------------|----------------|-----------|
//! | xSYSCTL_PERIPH_ACMPn      |  Non-Mandatory |    N      |
//! |---------------------------|----------------|-----------|
//! | xSYSCTL_PERIPH_ADCn       |    Mandatory   |   ADC0    |
//! |---------------------------|----------------|-----------|
//! | xSYSCTL_PERIPH_DMAn       |  Non-Mandatory |   DMA0    |
//! |---------------------------|----------------|-----------|
//! | xSYSCTL_PERIPH_GPIOn      |    Mandatory   |GPIOA~GPIOE|
//! |---------------------------|----------------|-----------|.
//! | xSYSCTL_PERIPH_I2Cn       |  Non-Mandatory | I2C0~I2C2 |
//! |---------------------------|----------------|-----------|
//! | xSYSCTL_PERIPH_PWMn       |  Non-Mandatory |   PWMA    |
//! |                           |                |           |
//! |                           |                |           |
//! |---------------------------|----------------|-----------|
//! | xSYSCTL_PERIPH_RTC        |    Mandatory   |     Y     |
//! |---------------------------|----------------|-----------|
//! | xSYSCTL_PERIPH_SPIn       |    Mandatory   |   SPI0    |
//! |                           |                |   SPI1    |
//! |                           |                |   SPI2    |
//! |---------------------------|----------------|-----------|
//! | xSYSCTL_PERIPH_TIMERn     |    Mandatory   |   TIMER0  |
//! |                           |                |    ...    |
//! |                           |                |   TIMER3  |
//! |---------------------------|----------------|-----------|
//! | xSYSCTL_PERIPH_UARTn      |    Mandatory   |   UART0   |
//! |                           |                |    ...    |
//! |                           |                |   UART3   |
//! |---------------------------|----------------|-----------|
//! | xSYSCTL_PERIPH_CANn       | Non-Mandatory  |   CAN1    |
//! |                           |                |   CAN2    |
//! |---------------------------|----------------|-----------|
//! | xSYSCTL_PERIPH_I2Sn       | Non-Mandatory  |   I2S0    |
//! |                           |                |    ...    |
//! |                           |                |   I2S2    |
//! |---------------------------|----------------|-----------|
//! | xSYSCTL_PERIPH_ETH        | Non-Mandatory  |     Y     |
//! |---------------------------|----------------|-----------|
//! | xSYSCTL_PERIPH_USB        | Non-Mandatory  |     Y     |
//! |---------------------------|----------------|-----------|
//! | xSYSCTL_PERIPH_WDOG       |    Mandatory   |     Y     |
//! +---------------------------+----------------+-----------+
//! More please refer to [xSysctl Defineds in MD file](
//!     @ref xSystcl_ACMP_md 
//!     @ref xSystcl_ADC_md ).
//! @{
//
//*****************************************************************************

#define xSYSCTL_PERIPH_ACMP     SYSCTL_PERIPH_ACMP
#define xSYSCTL_PERIPH_ADC0     SYSCTL_PERIPH_ADC0
#define xSYSCTL_PERIPH_ADC1     SYSCTL_PERIPH_ADC1
#define xSYSCTL_PERIPH_ADC2     SYSCTL_PERIPH_ADC2
#define xSYSCTL_PERIPH_DMA0     SYSCTL_PERIPH_DMA0
#define xSYSCTL_PERIPH_DMA1     SYSCTL_PERIPH_DMA1
#define xSYSCTL_PERIPH_DMA2     SYSCTL_PERIPH_DMA2
#define xSYSCTL_PERIPH_GPIOA    SYSCTL_PERIPH_IOPA
#define xSYSCTL_PERIPH_GPIOB    SYSCTL_PERIPH_IOPB
#define xSYSCTL_PERIPH_GPIOC    SYSCTL_PERIPH_IOPC
#define xSYSCTL_PERIPH_GPIOD    SYSCTL_PERIPH_IOPD
#define xSYSCTL_PERIPH_GPIOE    SYSCTL_PERIPH_IOPE
#define xSYSCTL_PERIPH_GPIOF    SYSCTL_PERIPH_IOPF
#define xSYSCTL_PERIPH_GPIOG    SYSCTL_PERIPH_IOPG
#define xSYSCTL_PERIPH_GPIOH    SYSCTL_PERIPH_IOPH
#define xSYSCTL_PERIPH_GPIOI    SYSCTL_PERIPH_IOPI
#define xSYSCTL_PERIPH_I2C0     SYSCTL_PERIPH_I2C0
#define xSYSCTL_PERIPH_I2C1     SYSCTL_PERIPH_I2C1
#define xSYSCTL_PERIPH_I2C2     SYSCTL_PERIPH_I2C2
#define xSYSCTL_PERIPH_I2C3     SYSCTL_PERIPH_I2C3
#define xSYSCTL_PERIPH_I2C4     SYSCTL_PERIPH_I2C4
#define xSYSCTL_PERIPH_PWMA     SYSCTL_PERIPH_PWMA
#define xSYSCTL_PERIPH_PWMB     SYSCTL_PERIPH_PWMB
#define xSYSCTL_PERIPH_PWMC     SYSCTL_PERIPH_PWMC
#define xSYSCTL_PERIPH_PWMD     SYSCTL_PERIPH_PWMD
#define xSYSCTL_PERIPH_PWME     SYSCTL_PERIPH_PWME
#define xSYSCTL_PERIPH_PWMF     SYSCTL_PERIPH_PWMF
#define xSYSCTL_PERIPH_PWMG     SYSCTL_PERIPH_PWMG
#define xSYSCTL_PERIPH_PWMH     SYSCTL_PERIPH_PWMH
#define xSYSCTL_PERIPH_PWMI     SYSCTL_PERIPH_PWMI
#define xSYSCTL_PERIPH_PWMJ     SYSCTL_PERIPH_PWMJ
#define xSYSCTL_PERIPH_PWMK     SYSCTL_PERIPH_PWMK
#define xSYSCTL_PERIPH_PWML     SYSCTL_PERIPH_PWML
#define xSYSCTL_PERIPH_RTC      SYSCTL_PERIPH_RTC
#define xSYSCTL_PERIPH_SPI0     SYSCTL_PERIPH_SPI0
#define xSYSCTL_PERIPH_SPI1     SYSCTL_PERIPH_SPI1
#define xSYSCTL_PERIPH_SPI2     SYSCTL_PERIPH_SPI2
#define xSYSCTL_PERIPH_SPI3     SYSCTL_PERIPH_SPI3
#define xSYSCTL_PERIPH_TIMER0   SYSCTL_PERIPH_TIMER0
#define xSYSCTL_PERIPH_TIMER1   SYSCTL_PERIPH_TIMER1
#define xSYSCTL_PERIPH_TIMER2   SYSCTL_PERIPH_TIMER2
#define xSYSCTL_PERIPH_TIMER3   SYSCTL_PERIPH_TIMER3
#define xSYSCTL_PERIPH_TIMER4   SYSCTL_PERIPH_TIMER4
#define xSYSCTL_PERIPH_TIMER5   SYSCTL_PERIPH_TIMER5
#define xSYSCTL_PERIPH_TIMER6   SYSCTL_PERIPH_TIMER6
#define xSYSCTL_PERIPH_TIMER7   SYSCTL_PERIPH_TIMER7
#define xSYSCTL_PERIPH_TIMER8   SYSCTL_PERIPH_TIMER8
#define xSYSCTL_PERIPH_TIMER9   SYSCTL_PERIPH_TIMER9
#define xSYSCTL_PERIPH_TIMER10  SYSCTL_PERIPH_TIMER10
#define xSYSCTL_PERIPH_TIMER11  SYSCTL_PERIPH_TIMER11
#define xSYSCTL_PERIPH_TIMER12  SYSCTL_PERIPH_TIMER12
#define xSYSCTL_PERIPH_TIMER13  SYSCTL_PERIPH_TIMER13
#define xSYSCTL_PERIPH_TIMER14  SYSCTL_PERIPH_TIMER14
#define xSYSCTL_PERIPH_UART0    SYSCTL_PERIPH_UART0
#define xSYSCTL_PERIPH_UART1    SYSCTL_PERIPH_UART1
#define xSYSCTL_PERIPH_UART2    SYSCTL_PERIPH_UART2
#define xSYSCTL_PERIPH_UART3    SYSCTL_PERIPH_UART3
#define xSYSCTL_PERIPH_UART4    SYSCTL_PERIPH_UART4
#define xSYSCTL_PERIPH_UART5    SYSCTL_PERIPH_UART5
#define xSYSCTL_PERIPH_CAN0     SYSCTL_PERIPH_CAN0
#define xSYSCTL_PERIPH_CAN1     SYSCTL_PERIPH_CAN1
#define xSYSCTL_PERIPH_CAN2     SYSCTL_PERIPH_CAN2
#define xSYSCTL_PERIPH_I2S0     SYSCTL_PERIPH_I2S0
#define xSYSCTL_PERIPH_I2S1     SYSCTL_PERIPH_I2S1
#define xSYSCTL_PERIPH_USB      SYSCTL_PERIPH_USB
#define xSYSCTL_PERIPH_WDOG     SYSCTL_PERIPH_WDT

//
//! Ethernet MAC Controller
//
#define xSYSCTL_PERIPH_ETH      SYSCTL_PERIPH_ETH

//
//! Repetitive Interrupt Timer
//
#define xSYSCTL_PERIPH_RIT      SYSCTL_PERIPH_RIT

//
//! Motor Control PWM power/clock
//
#define xSYSCTL_PERIPH_MCPWM    SYSCTL_PERIPH_MCPWM

//
//! Quadrature Encoder Interface 0
//
#define xSYSCTL_PERIPH_QEI0     SYSCTL_PERIPH_QEI0

//
//! Quadrature Encoder Interface 0
//
#define xSYSCTL_PERIPH_QEI1     SYSCTL_PERIPH_QEI1

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
//! | xSYSCTL_OSC_INTSL         |  Non-Mandatory |             N            |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_OSC_EXTSL         |  Non-Mandatory |             N            |
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
//! |xSYSCTL_INT_nMHZ           |  Non-Mandatory |     xSYSCTL_INT_22MHZ    |
//! |-------------------------- |----------------|--------------------------|
//! |xSYSCTL_INTSL_nKHZ/HZ      |  Non-Mandatory |    xSYSCTL_INTSL_10KHZ   |
//! |-------------------------- |----------------|--------------------------|
//! |xSYSCTL_XTALSL_nHZ         |  Non-Mandatory |  xSYSCTL_XTALSL_32768HZ  |
//! |-------------------------- |----------------|--------------------------|
//! | xSYSCTL_INT_OSC_DIS       |  Non-Mandatory |             Y            |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_MAIN_OSC_DIS      |  Non-Mandatory |             Y            |
//! |---------------------------|----------------|--------------------------|
//! | xSYSCTL_PLL_PWRDN         |  Non-Mandatory |             Y            |
//! +---------------------------+----------------+--------------------------+
//! More please refer to [xSysctl Defineds in MD file](@ref xSystcl_ClockSelect).
//! @{
//
//*****************************************************************************

//! Main Osc
#define xSYSCTL_OSC_MAIN        (SYSCTL_OSC_MAIN | SYSCTL_PLL_MAIN)

//! Internal RC
#define xSYSCTL_OSC_INT         (SYSCTL_OSC_INT | SYSCTL_PLL_INT)

//! Internal 10K RC
#define xSYSCTL_OSC_INTSL       SYSCTL_OSC_INTSL

//! External Oscillator 32.768K
#define xSYSCTL_OSC_EXTSL       SYSCTL_OSC_EXTSL

//
//! \brief XTAL Select
//
#define xSYSCTL_XTAL_1MHZ       SYSCTL_XTAL_1MHZ
#define xSYSCTL_XTAL_2MHZ       SYSCTL_XTAL_2MHZ
#define xSYSCTL_XTAL_3MHZ       SYSCTL_XTAL_3MHZ
#define xSYSCTL_XTAL_4MHZ       SYSCTL_XTAL_4MHZ
#define xSYSCTL_XTAL_5MHZ       SYSCTL_XTAL_5MHZ
#define xSYSCTL_XTAL_6MHZ       SYSCTL_XTAL_6MHZ
#define xSYSCTL_XTAL_7MHZ       SYSCTL_XTAL_7MHZ
#define xSYSCTL_XTAL_8MHZ       SYSCTL_XTAL_8MHZ
#define xSYSCTL_XTAL_9MHZ       SYSCTL_XTAL_9MHZ
#define xSYSCTL_XTAL_10MHZ      SYSCTL_XTAL_10MHZ
#define xSYSCTL_XTAL_11MHZ      SYSCTL_XTAL_11MHZ
#define xSYSCTL_XTAL_12MHZ      SYSCTL_XTAL_12MHZ
#define xSYSCTL_XTAL_13MHZ      SYSCTL_XTAL_13MHZ
#define xSYSCTL_XTAL_14MHZ      SYSCTL_XTAL_14MHZ
#define xSYSCTL_XTAL_15MHZ      SYSCTL_XTAL_15MHZ
#define xSYSCTL_XTAL_16MHZ      SYSCTL_XTAL_16MHZ
#define xSYSCTL_XTAL_17MHZ      SYSCTL_XTAL_17MHZ
#define xSYSCTL_XTAL_18MHZ      SYSCTL_XTAL_18MHZ
#define xSYSCTL_XTAL_19MHZ      SYSCTL_XTAL_19MHZ
#define xSYSCTL_XTAL_20MHZ      SYSCTL_XTAL_20MHZ
#define xSYSCTL_XTAL_21MHZ      SYSCTL_XTAL_21MHZ
#define xSYSCTL_XTAL_22MHZ      SYSCTL_XTAL_22MHZ
#define xSYSCTL_XTAL_23MHZ      SYSCTL_XTAL_23MHZ
#define xSYSCTL_XTAL_24MHZ      SYSCTL_XTAL_24MHZ
#define xSYSCTL_XTAL_25MHZ      SYSCTL_XTAL_25MHZ

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
extern void xSysCtlPeripheralReset(unsigned long ulPeripheralID);
 
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
extern void xSysCtlPeripheralEnable(unsigned long ulPeripheralID);
	
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
extern void xSysCtlPeripheralDisable(unsigned long ulPeripheralID);
	
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
extern void xSysCtlPeripheralEnable2(unsigned long ulPeripheralBase);
 
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
extern void xSysCtlPeripheralDisable2(unsigned long ulPeripheralBase);
 
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
extern void xSysCtlPeripheralReset2(unsigned long ulPeripheralBase);

//*****************************************************************************
//
//! \brief  Get the peripheral interrupt number through peripheral base.
//!
//! \param  [in] ulPeripheral The peripheral's base
//!
//! \return The peripheral's interrupt number.
//!
//! \note   It's especially useful to enable the short pin's corresponding
//!         peripheral interrupt: Use the short pin to Get the GPIO base through
//!         \ref xGPIOSPinToPort function, and then use this function to enable
//!         the GPIO interrupt.
//
//*****************************************************************************
extern unsigned long xSysCtlPeripheralIntNumGet(unsigned long ulPeripheralBase);
 
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
extern void xSysCtlClockSet(unsigned long ulSysClk, unsigned long ulConfig);
 
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
extern unsigned long xSysCtlClockGet(void);
 
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
extern void xSysCtlDelay(unsigned long ulCount);
 
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
extern void xSysCtlReset(void);

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
extern void xSysCtlSleep(void);


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
