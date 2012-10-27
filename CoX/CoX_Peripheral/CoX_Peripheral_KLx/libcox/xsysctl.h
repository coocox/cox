//*****************************************************************************
//
//! \file xsysctl.h
//! \brief Prototypes for the System Manager Driver.
//! Prototypes for the Clock Controller Driver.
//! \version V2.2.1.0
//! \date 8/2/2012
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

#ifndef __xSYSCTL_H__
#define __xSYSCTL_H__

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
//! \brief Values that show xSysCtl Peripheral ID
//! 
//! \section xSysCtl_Peripheral_SID 1. Where to use this group
//! Values that can be passed to the
//! xSysCtlPeripheralPresent(), xSysCtlPeripheralEnable(),
//! xSysCtlPeripheralDisable(), and xSysCtlPeripheralReset() APIs as the
//! ulPeripheral parameter.  
//! 
//! \section xSysCtl_Peripheral_ID_CoX 2.CoX Port Details
//! \verbatim
//! +--------------------------+----------------+--------------------------+
//! |SysCtl Peripheral ID      |       CoX      |          KLx             |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_ACMPn      |  Non-Mandatory |   xSYSCTL_PERIPH_ACMP0   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_ADCn       |    Mandatory   |    xSYSCTL_PERIPH_ADC0   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_DMA        |  Non-Mandatory |             Y            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_GPIOn      |    Mandatory   |   xSYSCTL_PERIPH_GPIOA   |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_GPIOB   |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_GPIOC   |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_GPIOD   |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_GPIOE   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_I2Cn       |  Non-Mandatory |    xSYSCTL_PERIPH_I2C0   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_I2C1   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_PWMn       |  Non-Mandatory |    xSYSCTL_PERIPH_PWMA   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_PWMB   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_PWMC   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_RTC        |    Mandatory   |             Y            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_SPIn       |    Mandatory   |    xSYSCTL_PERIPH_SPI0   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_SPI1   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_TIMERn     |    Mandatory   |   xSYSCTL_PERIPH_TIMER0  |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_TIMER1  |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_TIMER2  |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_UARTn      |    Mandatory   |   xSYSCTL_PERIPH_UART0   |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_UART1   |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_UART2   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_WDOG       | Non-Mandatory  |             N            |
//! +--------------------------+----------------+--------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xSYSCTL_PERIPH_ACMP0    SYSCTL_PERIPH_ACMP
#define xSYSCTL_PERIPH_ADC0     SYSCTL_PERIPH_ADC
#define xSYSCTL_PERIPH_DMA      SYSCTL_PERIPH_DMA
#define xSYSCTL_PERIPH_GPIOA    SYSCTL_PERIPH_GPIOA
#define xSYSCTL_PERIPH_GPIOB    SYSCTL_PERIPH_GPIOB
#define xSYSCTL_PERIPH_GPIOC    SYSCTL_PERIPH_GPIOC
#define xSYSCTL_PERIPH_GPIOD    SYSCTL_PERIPH_GPIOD
#define xSYSCTL_PERIPH_GPIOE    SYSCTL_PERIPH_GPIOE
#define xSYSCTL_PERIPH_I2C0     SYSCTL_PERIPH_I2C0
#define xSYSCTL_PERIPH_I2C1     SYSCTL_PERIPH_I2C1
#define xSYSCTL_PERIPH_PWMA     SYSCTL_PERIPH_TMR0
#define xSYSCTL_PERIPH_PWMB     SYSCTL_PERIPH_TMR1
#define xSYSCTL_PERIPH_PWMC     SYSCTL_PERIPH_TMR2
#define xSYSCTL_PERIPH_RTC      SYSCTL_PERIPH_RTC
#define xSYSCTL_PERIPH_SPI0     SYSCTL_PERIPH_SPI0
#define xSYSCTL_PERIPH_SPI1     SYSCTL_PERIPH_SPI1
#define xSYSCTL_PERIPH_TIMER0   SYSCTL_PERIPH_TMR0
#define xSYSCTL_PERIPH_TIMER1   SYSCTL_PERIPH_TMR1
#define xSYSCTL_PERIPH_TIMER2   SYSCTL_PERIPH_TMR2
#define xSYSCTL_PERIPH_UART0    SYSCTL_PERIPH_UART0
#define xSYSCTL_PERIPH_UART1    SYSCTL_PERIPH_UART1
#define xSYSCTL_PERIPH_UART2    SYSCTL_PERIPH_UART2

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSysCtl_Clock_Set_Config xSysCtl Clock Set Configuration
//! \brief Values that show xSysCtl Clock Set Configuration
//!
//! \section xSysCtl_Clock_Set_SConfig 1. Where to use this group
//! Values that can be passed to the xSysCtlClockSet() API as the
//! \b ulConfig parameter.
//!
//! \section xSysCtl_Clock_Set_SConfig 2. ulConfig parameter description
//! The ulConfig parameter is the logical OR of several different values, 
//! many of which are grouped into sets where only one can be chosen. 
//! ulConfig contains the external and internal crystal, main oscillators 
//! and PLL disabled options.
//!
//! \section xSysCtl_Clock_Set_Config_CoX 3.CoX Port Details
//! \verbatim
//! +--------------------------+----------------+--------------------------+
//! |SysCtl Clock Set Configs  |       CoX      |            KLx           |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_OSC_MAIN          |    Mandatory   |             Y            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_OSC_INT           |  Non-Mandatory |             N            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_OSC_INTSL         |  Non-Mandatory |             Y            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_OSC_EXTSL         |  Non-Mandatory |             N            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_XTAL_nMHZ         |  Non-Mandatory |     xSYSCTL_XTAL_3MHZ    |
//! |                          |                |--------------------------|
//! |                          |                |            ...           |
//! |                          |                |--------------------------|
//! |                          |                |     xSYSCTL_XTAL_8MHZ    |
//! |                          |                |--------------------------|
//! |                          |                |            ...           |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_XTAL_12MHZ    |
//! |                          |                |--------------------------|
//! |                          |                |            ...           |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_XTAL_32MHZ    |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_INT_nMHZ          |  Non-Mandatory |     xSYSCTL_INT_4MHZ     |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_INTSL_nKHZ/HZ     |  Non-Mandatory |    xSYSCTL_INTSL_32KHZ   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_XTALSL_nHZ        |  Non-Mandatory |  xSYSCTL_XTALSL_32768HZ  |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_INT_OSC_DIS       |  Non-Mandatory |             N            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_MAIN_OSC_DIS      |  Non-Mandatory |             N            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PLL_PWRDN         |  Non-Mandatory |             N            |
//! +--------------------------+----------------+--------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xSYSCTL_OSC_MAIN        (SYSCTL_OSC_MAIN | SYSCTL_PLL_MAIN)
#define xSYSCTL_OSC_INTSL       SYSCTL_OSC_INT
#define xSYSCTL_OSC_EXTSL       SYSCTL_OSC_MAIN

//
//! \brief XTAL Select
//
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
#define xSYSCTL_XTAL_26MHZ      SYSCTL_XTAL_26MHZ
#define xSYSCTL_XTAL_27MHZ      SYSCTL_XTAL_27MHZ
#define xSYSCTL_XTAL_28MHZ      SYSCTL_XTAL_28MHZ
#define xSYSCTL_XTAL_29MHZ      SYSCTL_XTAL_29MHZ
#define xSYSCTL_XTAL_30MHZ      SYSCTL_XTAL_30MHZ
#define xSYSCTL_XTAL_31MHZ      SYSCTL_XTAL_31MHZ
#define xSYSCTL_XTAL_32MHZ      SYSCTL_XTAL_32MHZ

//
//! Internal main clock is 4MHz
//
#define xSYSCTL_INT_4MHZ        0x00000000  

//
//! Internal slow clock  is 10KHz.
//
#define xSYSCTL_INTSL_32KHZ     0x00000000  

//
//! External slow clock crystal is 32KHz.
//
#define xSYSCTL_XTALSL_32768HZ  0x00000000  

//
//! Disable internal oscillator
//
#define xSYSCTL_INT_OSC_DIS     0  

//
//! Disable main oscillator
//
#define xSYSCTL_MAIN_OSC_DIS    0  

//
//! Disable PLL
//
#define xSYSCTL_PLL_PWRDN       0  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSysCtl_Peripheral_Src_Clk SysCtl Peripheral Source Clock
//! \brief Values that show SysCtl Peripheral Source Clock
//! The following are values that can be passed to the
//! xSysCtlPeripheralClockSourceSet()  API as the
//! ulPeripheralsrc parameter.  
//!
//! \section xSysCtl_Peripheral_Src_Clk_Def SysCtl Peripheral Short Name define
//! The macros of General Peripheral Source Clock always like:
//! <b> ModuleName + n + SourceClock</b>, such as xSYSCTL_WDT_EXTSL, 
//! xSYSCTL_ADC0_MAIN.
//!
//! \section xSysCtl_Peripheral_Src_Clk_CoX CoX Port Details
//! \verbatim
//! +-------------------------- +----------------+--------------------------+
//! |Peripheral Source Clock Set|       CoX      |           KLx            |
//! |---------------------------|----------------|--------------------------|
//! |Those are all Non-Mandatory|  Non-Mandatory |             Y            |
//! | parameter,the Mandatory   |                |                          |
//! | is variable naming        |                |                          |
//! |ModuleName+n+SourceClock   |                |                          |
//! |---------------------------|----------------|--------------------------|
//! |xSYSCTL_WDT_EXTSL          |  Non-Mandatory |             N            |
//! |-------------------------- |----------------|--------------------------|
//! |xSYSCTL_WDT_HCLK_2048      |  Non-Mandatory |             N            |
//! |-------------------------- |----------------|--------------------------|
//! |xSYSCTL_WDT_INTSL          |  Non-Mandatory |             N            |
//! |-------------------------- |----------------|--------------------------|
//! |xSYSCTL_ADC0_MAIN          |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! |xSYSCTL_ADC0_PLL           |  Non-Mandatory |             N            |
//! |-------------------------- |----------------|--------------------------|
//! |......                     |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! |xSYSCTL_PWMB_INT           |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! ADC clock source is HCLK
//
#define xSYSCTL_ADC0_MAIN       SYSCTL_PERIPH_ADC_S_BUSCLK 

//
//! Watch dog clock source is HCLK/x clock
//
#define xSYSCTL_WDT0_HCLK_2     SYSCTL_PERIPH_WDG_S_BUS     
                                
//
//! Watch dog clock source is internal 1kHz oscillator clock
//
#define xSYSCTL_WDT0_INTSL      SYSCTL_PERIPH_WDG_S_1K
                           
//
//! Timer0 clock source is external 12 MHz crystal clock
//
#define xSYSCTL_TIMER0_MAIN     SYSCTL_PERIPH_TPM_S_OSCERCLK  
                                
//
//! Timer0 clock source is HCLK
//
#define xSYSCTL_TIMER0_HCLK     SYSCTL_PERIPH_TPM_S_MCGFLLCLK 
                                
//
//! Timer0 clock source is internal 4 MHz oscillator clock
//
#define xSYSCTL_TIMER0_INT      SYSCTL_PERIPH_TPM_S_MCGIRCLK  
                                
//
//! Timer1 clock source is external 12 MHz crystal clock
//
#define xSYSCTL_TIMER1_MAIN     SYSCTL_PERIPH_TPM_S_OSCERCLK
                                
//
//! Timer1 clock source is HCLK
//
#define xSYSCTL_TIMER1_HCLK     SYSCTL_PERIPH_TPM_S_MCGFLLCLK
                                
//
//! Timer1 clock source is internal 4 MHz oscillator clock
//
#define xSYSCTL_TIMER1_INT      SYSCTL_PERIPH_TPM_S_MCGIRCLK  
                                
//
//! Timer2 clock source is external 12 MHz crystal clock
//
#define xSYSCTL_TIMER2_MAIN     SYSCTL_PERIPH_TPM_S_OSCERCLK
                                
//
//! Timer2 clock source is HCLK
//
#define xSYSCTL_TIMER2_HCLK     SYSCTL_PERIPH_TPM_S_MCGFLLCLK  
                                
//
//! Timer2 clock source is internal 4 MHz oscillator clock
//
#define xSYSCTL_TIMER2_INT      SYSCTL_PERIPH_TPM_S_MCGIRCLK
                                
//
//! UART clock source is external 12 MHz crystal clock
//
#define xSYSCTL_UART0_MAIN      SYSCTL_PERIPH_UART0_S_OSCERCLK  
                                
//
//! UART clock source is PLL clock
//
#define xSYSCTL_UART0_PLL       SYSCTL_PERIPH_UART0_S_MCGPLLCLK_2  
                                
//
//! UART clock source is internal 4 MHz oscillator clock
//
#define xSYSCTL_UART0_INT       SYSCTL_PERIPH_UART0_S_MCGIRCLK 
                                
//
//! PWMA clock source is external 12 MHz crystal clock
//
#define xSYSCTL_PWMA_MAIN       SYSCTL_PERIPH_TPM_S_OSCERCLK                         
                                
//
//! PWMA clock source is HCLK
//
#define xSYSCTL_PWMA_HCLK       SYSCTL_PERIPH_TPM_S_MCGFLLCLK   
                                
//
//! PWMA clock source is internal 4 MHz oscillator clock
//
#define xSYSCTL_PWMA_INT        SYSCTL_PERIPH_TPM_S_MCGIRCLK
                                
//
//! PWMB clock source is external 12 MHz crystal clock
//
#define xSYSCTL_PWMB_MAIN       SYSCTL_PERIPH_TPM_S_OSCERCLK   
                                
// 
//! PWMB clock source is HCLK
//
#define xSYSCTL_PWMB_HCLK       SYSCTL_PERIPH_TPM_S_MCGFLLCLK       
                                
//
//! PWMB clock source is internal 4 MHz oscillator clock
//
#define xSYSCTL_PWMB_INT        SYSCTL_PERIPH_TPM_S_MCGIRCLK  

//
//! PWMC clock source is external 12 MHz crystal clock
//
#define xSYSCTL_PWMC_MAIN       SYSCTL_PERIPH_TPM_S_OSCERCLK   
                                
// 
//! PWMC clock source is HCLK
//
#define xSYSCTL_PWMC_HCLK       SYSCTL_PERIPH_TPM_S_MCGFLLCLK       
                                
//
//! PWMC clock source is internal 4 MHz oscillator clock
//
#define xSYSCTL_PWMC_INT        SYSCTL_PERIPH_TPM_S_MCGIRCLK 
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSysCtl_Peripheral_Short SysCtl Peripheral Short Name
//! \brief Values that show SysCtl Peripheral Source Clock
//! The following are values that can be passed to the
//! xSysCtlPeripheralClockSourceSet2()  API as the
//! ulPeripheral parameter.
//!
//! \section xSysCtl_Peripheral_Short_Def SysCtl Peripheral Short Name define
//! The macros of General Peripheral Short Name always like:
//! <b> ModuleName + n </b>, such as ADC0.
//!
//! \section xSysCtl_Peripheral_Short_CoX CoX Port Details
//! \verbatim
//! +-------------------------- +----------------+--------------------------+
//! |Peripheral Short name      |       CoX      |           KLx            |
//! |---------------------------|----------------|--------------------------|
//! |ADCn                       |  Non-Mandatory |           ADC0           |
//! |---------------------------|----------------|--------------------------|
//! |PWMn                       |  Non-Mandatory |           PWMA           |
//! |                           |                |           PWMB           |
//! |                           |                |           PWMC           |
//! |-------------------------- |----------------|--------------------------|
//! |UARTn                      |  Non-Mandatory |           UART0          |
//! |                           |                |           UART1          |
//! |                           |                |           UART2          |
//! |-------------------------- |----------------|--------------------------|
//! |WDTn                       |  Non-Mandatory |             N            |
//! |-------------------------- |----------------|--------------------------|
//! |TIMERn                     |  Non-Mandatory |          TIMER0          |
//! |                           |                |          TIMER1          |
//! |                           |                |          TIMER2          |
//! |                           |                |          TIMER3          |
//! |-------------------------- |----------------|--------------------------|
//! |I2Cn                       |  Non-Mandatory |             N            |
//! |-------------------------- |----------------|--------------------------|
//! |SPIn                       |  Non-Mandatory |             N            |
//! |-------------------------- |----------------|--------------------------|
//! |ACMPn                      |  Non-Mandatory |             N            |
//! |-------------------------- |----------------|--------------------------|
//! |RTC                        |  Non-Mandatory |             N            |
//! |-------------------------- |----------------|--------------------------|
//! |GPIO                       |  Non-Mandatory |             N            |
//! |-------------------------- |----------------|--------------------------|
//!
//! +-------------------------- +----------------+--------------------------+
//! |Peripheral Clock source    |       CoX      |           KLx            |
//! |---------------------------|----------------|--------------------------|
//! |INT                        |    Mandatory   |             Y            |
//! |---------------------------|----------------|--------------------------|
//! |HCLK                       |    Mandatory   |             Y            |
//! |---------------------------|----------------|--------------------------|
//! |HCLK_n                     |  Non-Mandatory |         HCLK_2048        |
//! |---------------------------|----------------|--------------------------|
//! |EXTSL                      |    Mandatory   |             Y            |
//! |---------------------------|----------------|--------------------------|
//! |INTSL                      |    Mandatory   |             Y            |
//! |---------------------------|----------------|--------------------------|
//! |MAIN                       |    Mandatory   |             Y            |
//! |---------------------------|----------------|--------------------------|
//! |PLL                        |    Mandatory   |             Y            |
//! |---------------------------|----------------|--------------------------|
//! |PLL_n                      |  Non-Mandatory |           PLL_2          |
//! |---------------------------|----------------|--------------------------|
//! |EXTTRG                     |  Non-Mandatory |             Y            |
//! |---------------------------|----------------|--------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************
#define ADC0                    ADC0
#define PWMC                    PWMC
#define PWMB                    PWMB
#define PWMA                    PWMA
#define TIMER0                  TIMER0
#define TIMER1                  TIMER1
#define TIMER2                  TIMER2
#define UART0                   UART0
#define UART1                   UART1
#define UART2                   UART2
#define CAN0                    CAN0

//
//! internal high speed oscillator
//
#define INT                     INT

//
//! The system clock
//
#define HCLK                    HCLK

//
//! The system clock divide by 2048
//
#define HCLK_2048               HCLK_2048

//
//! external low speed crystal
//
#define EXTSL                   EXTSL

//
//! internal low speed oscillator
//
#define INTSL                   INTSL

//
//! external high speed oscillator
//
#define MAIN                    MAIN

//
//! PLL output
//
#define PLL                     PLL

//
//! PLL output divide by 2
//
#define PLL_2                   PLL_2

//
//! external clock input
//
#define EXTTRG                  EXTTRG
 
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSysCtl_Exported_APIs xSysCtl API
//! \brief xSysCtl API Reference
//!
//! \section xSysCtl_Exported_APIs_Port CoX Port Details
//! \verbatim
//! +--------------------------------+----------------+--------+
//! |xSysCtl API                     |       CoX      |   KLx  |
//! |--------------------------------|----------------|--------|
//! |xSysCtlPeripheralReset          |  Non-Mandatory |    N   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlPeripheralEnable         |    Mandatory   |    Y   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlPeripheralDisable        |    Mandatory   |    Y   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlPeripheralReset2         |  Non-Mandatory |    N   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlPeripheralEnable2        |    Mandatory   |    Y   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlPeripheralDisable2       |    Mandatory   |    Y   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlPeripheraIntNumGet       |    Mandatory   |    Y   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlClockSet                 |    Mandatory   |    Y   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlClockGet                 |    Mandatory   |    Y   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlDelay                    |    Mandatory   |    Y   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlReset                    |    Mandatory   |    Y   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlSleep                    |    Mandatory   |    Y   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlPeripheralClockSourceSet |    Mandatory   |    Y   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlPeripheralClockSourceSet2|    Mandatory   |    Y   |
//! |--------------------------------|----------------|--------|
//! \endverbatim
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Performs a software reset of a peripheral.
//!
//! \param ulPeripheralID is the peripheral to reset. 
//! Details please refer to \ref xSysCtl_Peripheral_ID.
//!
//! This function performs a software reset of the specified peripheral.  An
//! individual peripheral reset signal is asserted for a brief period and then
//! deasserted, returning the internal state of the peripheral to its reset
//! condition.
//!
//! The \e ulPeripheralID parameter must be only one of the following values:
//! Details please refer to \ref xSysCtl_Peripheral_ID_CoX.
//!
//! \return None.
//
//*****************************************************************************       
#define xSysCtlPeripheralReset(ulPeripheralID)                                0
        
//*****************************************************************************
//
//! \brief Enables a peripheral.
//!
//! \param ulPeripheralID is the peripheral to enable.
//! Details please refer to \ref xSysCtl_Peripheral_ID.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheralID parameter must be only one of the following values:
//! Details please refer to \ref xSysCtl_Peripheral_ID_CoX.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
#define xSysCtlPeripheralEnable(ulPeripheralID)                               \
        SysCtlPeripheralEnable(ulPeripheralID)
        
extern void xSysCtlPeripheralEnable2(unsigned long ulPeripheralBase);
extern void xSysCtlPeripheralDisable2(unsigned long ulPeripheralBase);
extern void xSysCtlPeripheralClockSourceSet(unsigned long ulPeripheralSrc,
                                            unsigned long ulDivide);
extern unsigned long xSysCtlPeripheraIntNumGet(unsigned long ulPeripheralBase);

//*****************************************************************************
//
//! \brief Set a peripheral clock source and peripheral divide.
//!
//! \param ePeripheral is the peripheral which's clock source will be set.
//! \param eSrc is the clock source will be set.
//! \param ulDivide is the peripheral clock divide to set.
//!
//! Peripherals clock source are seted with this function.  At power-up, all 
//! Peripherals clock source are Peripherals clock source; they must be set in 
//! order to operate or respond to register reads/writes.
//!
//! The \e ulPeripheralSrc parameter must be only one of the following values:
//! \ref xSysCtl_Peripheral_Src_Clk_CoX.
//! \verbatim
//! +--------------------+------------------------+---------------------------+
//! |    manufacturer    |ePeripheral             |eSrc                       |
//! |--------------------|------------------------|---------------------------|
//! |    CoX Common &    |This parameter is a     |This parameter is a        |
//! |      Mandatory     |mandatory.Mandatory     |mandatory. So it           |
//! |                    |is the format of        |should be: INT             |
//! |                    |Variable naming.So it   |HCLK  HCLK_n EXTSL         |
//! |                    |should be: ADCn,        |INTSL  MAIN  PLL           |
//! |                    |TIMERn or UARTn         |PLL_n  EXTTRG              |
//! |                    |n indicate the pin      |n indicate the pin         |
//! |                    |number such as          |number such as             |
//! |                    |0 1 2 3 ....            |0 1 2 3 ....               |
//! |--------------------|------------------------|---------------------------|
//! |       KLx          |    ADC0                |MAIN PLL INT               |
//! |                    |    PWMB                |INT HCLK EXTSL MAIN        |
//! |                    |    PWMA                |INT HCLK EXTSL MAIN        |
//! |                    |    TIMER0              |INT EXTTRG HCLK EXTSL MAIN |
//! |                    |    TIMER1              |INT EXTTRG HCLK EXTSL MAIN |
//! |                    |    TIMER2              |INT EXTTRG HCLK EXTSL MAIN |
//! |                    |    UART0               |INT PLL MAIN               |
//! |                    |    UART1               |INT PLL MAIN               |
//! |                    |    UART2               |INT PLL MAIN               |
//! |--------------------|------------------------|---------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSysCtlPeripheralClockSourceSet2(ePeripheral, eSrc, ulDivide)         \
        SysCtlIPClockSourceSetConvert(ePeripheral, eSrc, ulDivide)

//*****************************************************************************
//
//! \brief Disables a peripheral.
//!
//! \param ulPeripheralID is the peripheral to disable.
//! Details please reference to \ref xSysCtl_Peripheral_ID.
//!
//! Peripherals are disabled with this function.  Once disabled, they will not
//! operate or respond to register reads/writes.
//!
//! The \e ulPeripheralID parameter must be only one of the following values:
//! Details please refer to \ref xSysCtl_Peripheral_ID_CoX.
//!
//! \return None.
//
//*****************************************************************************
#define xSysCtlPeripheralDisable(ulPeripheralID)                              \
        SysCtlPeripheralDisable(ulPeripheralID)

extern void xSysCtlClockSet(unsigned long ulSysClk, unsigned long ulConfig);

//*****************************************************************************
//
//! \brief Gets the processor clock rate.
//!
//! This function determines the clock rate of the processor clock.  This is
//! also the clock rate of all the peripheral modules (with the exception of
//! PWM, which has its own clock divider).
//!
//! \note This will not return accurate results if SysCtlClockSet() has not
//! been called to configure the clock of the device, or if the device is
//! directly clocked from a crystal (or a clock source) that is not one of the
//! supported crystal frequencies.  In the later case, this function should be
//! modified to directly return the correct system clock rate.
//!
//! \return The processor clock rate.
//
//*****************************************************************************
#define xSysCtlClockGet()                                                     \
        SysCtlHClockGet()

//*****************************************************************************
//
//! \brief Provides a small delay.
//!
//! \param ulCount is the number of delay loop iterations to perform.
//!
//! This function provides a means of generating a constant length delay.  It
//! is written in assembly to keep the delay consistent across tool chains,
//! avoiding the need to tune the delay based on the tool chain in use.
//!
//! The loop takes 3 cycles/loop.
//!
//! \return None.
//
//*****************************************************************************
#define xSysCtlDelay(ulCount)                                                 \
        SysCtlDelay(ulCount)

//*****************************************************************************
//
//! \brief Resets the device.
//!
//! This function will perform a software reset of the entire device.  The
//! processor and all peripherals will be reset and all device registers will
//! return to their default values (with the exception of the reset cause
//! register, which will maintain its current value but have the software reset
//! bit set as well).
//!
//! \return This function does not return.
//
//*****************************************************************************
#define xSysCtlReset()                                                        \
        SysCtlReset()

//*****************************************************************************
//
//! \brief Puts the processor into sleep mode.
//!
//! This function places the processor into sleep mode; it will not return
//! until the processor returns to run mode.  The peripherals that are enabled
//! via SysCtlPeripheralSleepEnable() continue to operate and can wake up the
//! processor (if automatic clock gating is enabled with
//! SysCtlPeripheralClockGating(), otherwise all peripherals continue to
//! operate).
//!
//! \return None.
//
//*****************************************************************************
#define xSysCtlSleep()                                                        \
        SysCtlSleep()

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
//! \addtogroup KLx_SysCtl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Peripheral_ID KLx SysCtl Peripheral ID
//! \brief Values that show SysCtl Peripheral ID
//! Values that can be passed to the SysCtlPeripheralEnable(),
//! SysCtlPeripheralDisable(), APIs as the ulPeripheral parameter. 
//! @{
//
//*****************************************************************************

//
//! I2C0
//
#define SYSCTL_PERIPH_I2C0      0x0040  

//
//! I2C1
//
#define SYSCTL_PERIPH_I2C1      0x0080 

//
//! UART0
//
#define SYSCTL_PERIPH_UART0     0x0A01  

//
//! UART1
//
#define SYSCTL_PERIPH_UART1     0x0A02  

//
//! UART2
//
#define SYSCTL_PERIPH_UART2     0x0A04 

//
//! USB
//
#define SYSCTL_PERIPH_USB       0x0F08

//
//! ACMP
//
#define SYSCTL_PERIPH_ACMP      0x0F10

//
//! SPI0
//
#define SYSCTL_PERIPH_SPI0      0x1601 

//
//! SPI1
//
#define SYSCTL_PERIPH_SPI1      0x1602 

//
//! LPTMR
//
#define SYSCTL_PERIPH_LPTMR     0x4001

//
//! TSI
//
#define SYSCTL_PERIPH_TSI       0x4020 

//
//! GPIOA
//
#define SYSCTL_PERIPH_GPIOA     0x4802 

//
//! GPIOB
//
#define SYSCTL_PERIPH_GPIOB     0x4804

//
//! GPIOC
//
#define SYSCTL_PERIPH_GPIOC     0x4808 

//
//! GPIOD
//
#define SYSCTL_PERIPH_GPIOD     0x4810

//
//! GPIOE
//
#define SYSCTL_PERIPH_GPIOE     0x4820

//
//! FLASH
//
#define SYSCTL_PERIPH_FLASH     0x8001 

//
//! DMAMUX
//
#define SYSCTL_PERIPH_DMAMUX    0x8002

//
//! PIT
//
#define SYSCTL_PERIPH_PIT       0x9080

//
//! TMR0
//
#define SYSCTL_PERIPH_TMR0      0x9180  

//
//! TMR1
//
#define SYSCTL_PERIPH_TMR1      0x9280  

//
//! TMR2
//
#define SYSCTL_PERIPH_TMR2      0x9380 

//
//! ADC
//
#define SYSCTL_PERIPH_ADC       0x9480 

//
//! RTC
//
#define SYSCTL_PERIPH_RTC       0x9680   

//
//! DAC
//
#define SYSCTL_PERIPH_DAC       0x9880  

//
//! PWMA
//
#define SYSCTL_PERIPH_PWMA      0x9180  

//
//! PWMB
//
#define SYSCTL_PERIPH_PWMB      0x9280  

//
//! PWMC
//
#define SYSCTL_PERIPH_PWMC      0x9380

//
//! DMA
//
#define SYSCTL_PERIPH_DMA       0xC180  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Peripheral_Src_Clk SysCtl Peripheral Source Clock
//! \brief Values that show SysCtl Peripheral Source Clock
//! The following are values that can be passed to the
//! SysCtlPeripheralClockSourceSet()  API as the
//! ulPeripheralsrc parameter.  
//! @{
//
//*****************************************************************************

//
//! ADC clock source is Bus Clock
//
#define SYSCTL_PERIPH_ADC_S_BUSCLK                                            \
                                0xCC000000

//
//! ADC clock source is (Bus clock)/2
//
#define SYSCTL_PERIPH_ADC_S_BUSCLK_2                                          \
                                0xCD000000

//
//! ADC clock source is Alternate clock (ALTCLK)
//
#define SYSCTL_PERIPH_ADC_S_ATCLK                                             \
                                0xCE000000

//
//! ADC clock source is Asynchronous clock (ADACK)
//
#define SYSCTL_PERIPH_ADC_S_ADACK                                             \
                                0xCF000000

//
//! RTC clock source is System oscillator(OSC32KCLK)
//
#define SYSCTL_PERIPH_RTC_S_OSC32KCLK                                         \
                                0x00000000  
                                
//
//! RTC clock source is RTC_CLKIN
//
#define SYSCTL_PERIPH_RTC_S_RTC_CLKIN                                         \
                                0x00010000   
                                
//
//! RTC clock source is LPO 1kHz
//
#define SYSCTL_PERIPH_RTC_S_LPO 0x000C0000  

//
//! LPTMR clock source is System oscillator(OSC32KCLK)
//
#define SYSCTL_PERIPH_LPTMR_S_OSC32KCLK                                       \
                                0xA0000000  
                                
//
//! LPTMR clock source is RTC_CLKIN
//
#define SYSCTL_PERIPH_LPTMR_S_RTC_CLKIN                                       \
                                0xA0010000   
                                
//
//! LPTMR clock source is LPO 1kHz
//
#define SYSCTL_PERIPH_LPTMR_S_LPO                                             \
                                0xA00C0000 
     
//
//! TPM clock source is MCGFLLCLK
//
#define SYSCTL_PERIPH_TPM_S_MCGFLLCLK                                         \
                                0x01000000
                                
//
//! TPM clock source is MCGPLLCLK/2
//
#define SYSCTL_PERIPH_TPM_S_MCGPLLCLK_2                                       \
                                0xA1000000  
                                
//
//! TPM clock source is OSCERCLK clock
//
#define SYSCTL_PERIPH_TPM_S_OSCERCLK                                          \
                                0x02000000   
                                
//
//! TPM clock source is MCGIRCLK clock
//
#define SYSCTL_PERIPH_TPM_S_MCGIRCLK                                          \
                                0x03000000  

//
//! UART0 clock source is MCGFLLCLK
//
#define SYSCTL_PERIPH_UART0_S_MCGFLLCLK                                       \
                                0x04000000
                                
//
//! UART0 clock source is MCGPLLCLK/2
//
#define SYSCTL_PERIPH_UART0_S_MCGPLLCLK_2                                     \
                                0xA4000000  
                                
//
//! UART0 clock source is OSCERCLK clock
//
#define SYSCTL_PERIPH_UART0_S_OSCERCLK                                        \
                                0x08000000   
                                
//
//! UART0 clock source is MCGIRCLK clock
//
#define SYSCTL_PERIPH_UART0_S_MCGIRCLK                                        \
                                0x0C000000
                            
//
//! USB clock source is External bypass clock (USB_CLKIN)
//
#define SYSCTL_PERIPH_USB_S_USB_CLKIN                                         \
                                0xB0000000  
                                
//
//! USB clock source is MCGPLLCLK/2
//
#define SYSCTL_PERIPH_USB_S_MCGPLLCLK_2                                       \
                                0x00080704  
                                
//
//! USB clock source is MCGFLLCLK
//
#define SYSCTL_PERIPH_USB_S_MCGFLLCLK                                         \
                                0x000C0700  
                                
//
//! WDG clock source is Internal 1 kHz clock
//
#define SYSCTL_PERIPH_WDG_S_1K  0x000C0701  
                                
//
//! WDG clock source is Bus clock
//
#define SYSCTL_PERIPH_WDG_S_BUS 0x000C0702 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Hclk_Src KLx SysCtl Hclk Source
//! \brief Values that show KLx SysCtl Hclk Source
//! The following are values that can be passed to the SysCtlHClockSourceSet()/
//! SysCtlHClockSet API as the ulHclkSrcSel parameter.   
//! @{
//
//*****************************************************************************

//
//! HCLK source is PLL clock
//
#define SYSCTL_HLCK_S_PLL       0x00

//
//! HCLK source is internal reference oscillator clock
//
#define SYSCTL_HLCK_S_INT       0x40  

//
//! HCLK source is external 12M crystal clock
//
#define SYSCTL_HLCK_S_MAIN      0x80 
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_WakeupPin_Edge KLx SysCtl Wakeup pin edge Mode
//! The following are values that can be passed to the SysCtlWakeupPinConfig()
//! API as the ulEdge parameter.   
//! @{
//
//*****************************************************************************

//
//! External input pin disabled as wakeup input.
//
#define SYSCTL_WAKEUP_PIN_DIS   0x00

//
//! External input pin enabled with rising edge detection.
//
#define SYSCTL_WAKEUP_PIN_RISING                                              \
                                0x01

//
//! External input pin enabled with falling edge detection.
//
#define SYSCTL_WAKEUP_PIN_FALLING                                             \
                                0x02

//
//! External input pin enabled with any change detection.
//
#define SYSCTL_WAKEUP_PIN_ANY   0x03

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Wakeup_Filter_Edge KLx SysCtl Wakeup Filter edge Mode
//! The following are values that can be passed to the SysCtlWakeupFilterConfig()
//! API as the ulEdge parameter.   
//! @{
//
//*****************************************************************************

//
//! Filter disabled.
//
#define SYSCTL_WAKEUP_FILTER_DIS                                              \
                                0x00

//
//! Filter posedge detect enabled.
//
#define SYSCTL_WAKEUP_FILTER_RISING                                          \
                                0x20

//
//! Filter negedge detect enabled.
//
#define SYSCTL_WAKEUP_FILTER_FALLING                                         \
                                0x40

//
//! Filter any edge detect enabled.
//
#define SYSCTL_WAKEUP_FILTER_ANY                                             \
                                0x60

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Stop_Mode KLx SysCtl Stop Mode
//! \brief Values that show KLx SysCtl Stop Mode
//! The following are values that can be passed to the SysCtlStopModeSet().   
//! @{
//
//*****************************************************************************

//
//! Very-Low-Power Stop
//
#define SYSCTL_STOP_MODE_VLPS   0x00000000

//
//! Low-Leakage Stop (LLS) mode
//
#define SYSCTL_STOP_MODE_LLS    0x00000001  

//
//! Very-Low-Leakage Stop (VLLS0) modes
//
#define SYSCTL_STOP_MODE_VLLS0  0x00000002

//
//! Very-Low-Leakage Stop (VLLS1) modes
//
#define SYSCTL_STOP_MODE_VLLS1  0x00000003  

//
//! Very-Low-Leakage Stop (VLLS2) modes
//
#define SYSCTL_STOP_MODE_VLLS2  0x00000004

//
//! Very-Low-Leakage Stop (VLLS3) modes
//
#define SYSCTL_STOP_MODE_VLLS3  0x00000005

//
//! Normal Stop
//
#define SYSCTL_STOP_MODE_NORMAL 0x00000006
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_FLL_Src KLx SysCtl FLL Source
//! \brief Values that show KLx SysCtl FLL Source 
//! @{
//
//*****************************************************************************

//
//! FLL Clock source is external reference clock is selected.
//
#define SYSCTL_FLL_S_EXT12M     0x00000000  

//
//! FLL Clock source is the slow internal reference clock.
//
#define SYSCTL_FLL_S_INT32K     0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Reset_Src KLx SysCtl Reset Source
//! \brief Values that show KLx SysCtl Reset Source
//! The following are values that can be returned in the bit mask
//! by the SysCtlResetSrcGet() API.   
//! @{
//
//*****************************************************************************

//
//! "reset signal" from Power-On Reset
//
#define SYSCTL_RSTSRC_POR       0x80  

//
//! "reset signal" from the /RESET pin
//
#define SYSCTL_RSTSRC_PAD       0x40 

//
//! "reset signal" from the Watch-Dog
//
#define SYSCTL_RSTSRC_WDG       0x20  

//
//! "reset signal" from Loss-of-Lock
//
#define SYSCTL_RSTSRC_LOL       0x08  

//
//! "reset signal" from Loss-of-Clock
//
#define SYSCTL_RSTSRC_LOC       0x04  

//
//! "reset signal" from MCU Cortex_M0 kernel
//
#define SYSCTL_RSTSRC_LVD       0x02  

//
//! "reset signal" from Low Leakage Wakeup
//
#define SYSCTL_RSTSRC_WAKEUP    0x01  

//
//! "reset signal" from Stop Mode Acknowledge Error
//
#define SYSCTL_RSTSRC_SACKERR   0x20  

//
//! "reset signal" from MDM-AP System
//
#define SYSCTL_RSTSRC_MDM_AP    0x08  

//
//! "reset signal" from Software
//
#define SYSCTL_RSTSRC_SW        0x04  

//
//! "reset signal" from Core Lockup
//
#define SYSCTL_RSTSRC_LOCKUP    0x02
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Reset_Pin_Filter_Run Reset Pin Filter Select in Run and Wait Modes
//! The following are values that can be passed to the
//! SysCtlResetPinFilterRunModeSelect()  API as the
//! ulFilter parameter. 
//! @{
//
//*****************************************************************************

//
//! All filtering disabled
// 
#define SYSCTL_RESET_PIN_FILTER_RUN_DIS                                       \
                                0x00

//
//! Bus clock filter enabled for normal operation
// 
#define SYSCTL_RESET_PIN_FILTER_RUN_BUS                                       \
                                0x01

//
//! LPO clock filter enabled for normal operation
// 
#define SYSCTL_RESET_PIN_FILTER_RUN_LPO                                       \
                                0x02    

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_POWER_MODE Current power mode
//! The following are values that can be returned in the bit mask
//! by the SysCtlPowerModeGet() API. 
//! @{
//
//*****************************************************************************

//
//! Current power mode is RUN
// 
#define SYSCTL_POWER_MODE_RUN   0x01

//
//! Current power mode is STOP
// 
#define SYSCTL_POWER_MODE_STOP  0x02    

//
//! Current power mode is VLPR
// 
#define SYSCTL_POWER_MODE_VLPR  0x04

//
//! Current power mode is VLPW
// 
#define SYSCTL_POWER_MODE_VLPW  0x08

//
//! Current power mode is VLPS
// 
#define SYSCTL_POWER_MODE_VLPS  0x10    

//
//! Current power mode is VLPR
// 
#define SYSCTL_POWER_MODE_LLS   0x20

//
//! Current power mode is VLLS
// 
#define SYSCTL_POWER_MODE_VLLS  0x40
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Output_Src KLx SysCtl output Clock source
//! \brief Values that show KLx SysCtl Output clock source
//! The following are values that can be passed to the SysCtlClkOututSrcSet()
//! API as the ulClkOutSrc parameter. 
//! @{
//
//*****************************************************************************

//
//! The clock to output on the CLKOUT pin is Bus clock
// 
#define SYSCTL_OUTPUT_CLKSRC_BUS                                              \
                                0x40  

//
//! The clock to output on the CLKOUT pin is LPO clock(1kHz)
//
#define SYSCTL_OUTPUT_CLKSRC_LPO                                              \
                                0x60  

//
//! The clock to output on the CLKOUT pin is MCGIRCLK
//
#define SYSCTL_OUTPUT_CLKSRC_MCGIRCLK                                         \
                                0x80  

//
//! The clock to output on the CLKOUT pin is OSCERCLK
//
#define SYSCTL_OUTPUT_CLKSRC_OSCERCLK                                         \
                                0xC0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_LVD_Voltage KLx SysCtl Low-Voltage Detect Voltage
//! \brief Values that show KLx SysCtl Low-Voltage Detect Voltage Select
//! The following are values that can be passed to the SysCtlLVDVolSet()
//! API as the ulVoltage parameter. 
//! @{
//
//*****************************************************************************

//
//! Low trip point selected (VLVD = VLVDL)
// 
#define SYSCTL_LVD_DET_LOW      0x00  

//
//! High trip point selected (VLVD = VLVDH)
// 
#define SYSCTL_LVD_DET_HIGH     0x01 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_LVD_Warning_Voltage KLx SysCtl Low-Voltage Warning Voltage
//! \brief Values that show KLx SysCtl Low-Voltage Warning Voltage Select
//! The following are values that can be passed to the SysCtlLVDWarningVolSet()
//! API as the ulVoltage parameter. 
//! @{
//
//*****************************************************************************

//
//! Low trip point selected
// 
#define SYSCTL_LVD_WARNING_LOW  0x00

//
//! Mid 1 trip point selected
// 
#define SYSCTL_LVD_WARNING_MID1 0x01   

//
//! Mid 2 trip point selected
// 
#define SYSCTL_LVD_WARNING_MID2 0x02

//
//! High trip point selected
// 
#define SYSCTL_LVD_WARNING_HIGH 0x03 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
 
//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Clock_Config KLx SysCtl Clock Configuration
//! \brief KLx SysCtl Clock Configuration
//! The following are values that can be passed to the SysCtlClockSet() API as
//! the ulConfig parameter.
//! @{
//
//*****************************************************************************

//
//! HCLK source is main osc
//
#define SYSCTL_OSC_MAIN         0x80

//
//! HCLK source is PLL
//
#define SYSCTL_OSC_PLL          0x20

//
//! HCLK source is FLL(32K)
//
#define SYSCTL_OSC_FLL_INT      0x01

//
//! HCLK source is FLL(12M)
//
#define SYSCTL_OSC_FLL_MAIN     0x08

//
//! HCLK source is int. osc(32K)
//
#define SYSCTL_OSC_INT          0x40

//
//! HCLK source is int. osc(4M)
//
#define SYSCTL_OSC_INT_FAST     0x04 

//
//! Oscillator Source
//
#define SYSCTL_OSCSRC_M         0xC0 

//
//! PLL source is int. 12 MHz
//
#define SYSCTL_PLL_MAIN         0x00

//
//! External main clock crystal mask.
//
#define SYSCTL_XTAL_MASK        0x0000FF00  

//
//! External main clock crystal is 3MHz.
//
#define SYSCTL_XTAL_3MHZ        0x00000300  

//
//! External main clock crystal is 4MHz.
//
#define SYSCTL_XTAL_4MHZ        0x00000400  

//
//! External main clock crystal is 5MHz.
//
#define SYSCTL_XTAL_5MHZ        0x00000500  

//
//! External main clock crystal is 6MHz.
//
#define SYSCTL_XTAL_6MHZ        0x00000600  

//
//! External main clock crystal is 7MHz.
//
#define SYSCTL_XTAL_7MHZ        0x00000700  

//
//! External main clock crystal is 8MHz.
//
#define SYSCTL_XTAL_8MHZ        0x00000800  

//
//! External main clock crystal is 9MHz.
//
#define SYSCTL_XTAL_9MHZ        0x00000900  

//
//! External main clock crystal is 10MHz.
//
#define SYSCTL_XTAL_10MHZ       0x00000A00  

//
//! External main clock crystal is 11MHz.
//
#define SYSCTL_XTAL_11MHZ       0x00000B00  

//
//! External main clock crystal is 12MHz.
//
#define SYSCTL_XTAL_12MHZ       0x00000C00 

//
//! External main clock crystal is 13MHz.
//
#define SYSCTL_XTAL_13MHZ       0x00000D00  

//
//! External main clock crystal is 14MHz.
//
#define SYSCTL_XTAL_14MHZ       0x00000E00  

//
//! External main clock crystal is 15MHz.
//
#define SYSCTL_XTAL_15MHZ       0x00000F00  

//
//! External main clock crystal is 16MHz.
//
#define SYSCTL_XTAL_16MHZ       0x00001000  

//
//! External main clock crystal is 17MHz.
//
#define SYSCTL_XTAL_17MHZ       0x00001100  

//
//! External main clock crystal is 18MHz.
//
#define SYSCTL_XTAL_18MHZ       0x00001200  

//
//! External main clock crystal is 19MHz.
//
#define SYSCTL_XTAL_19MHZ       0x00001300  

//
//! External main clock crystal is 20MHz.
//
#define SYSCTL_XTAL_20MHZ       0x00001400  

//
//! External main clock crystal is 21MHz.
//
#define SYSCTL_XTAL_21MHZ       0x00001500 

//
//! External main clock crystal is 22MHz.
//
#define SYSCTL_XTAL_22MHZ       0x00001600  

//
//! External main clock crystal is 23MHz.
//
#define SYSCTL_XTAL_23MHZ       0x00001700  

//
//! External main clock crystal is 24MHz.
//
#define SYSCTL_XTAL_24MHZ       0x00001800  

//
//! External main clock crystal is 25MHz.
//
#define SYSCTL_XTAL_25MHZ       0x00001900  

//
//! External main clock crystal is 26MHz.
//
#define SYSCTL_XTAL_26MHZ       0x00001A00  

//
//! External main clock crystal is 27MHz.
//
#define SYSCTL_XTAL_27MHZ       0x00001B00  

//
//! External main clock crystal is 28MHz.
//
#define SYSCTL_XTAL_28MHZ       0x00001C00  

//
//! External main clock crystal is 29MHz.
//
#define SYSCTL_XTAL_29MHZ       0x00001D00  

//
//! External main clock crystal is 30MHz.
//
#define SYSCTL_XTAL_30MHZ       0x00001E00  

//
//! External main clock crystal is 31MHz.
//
#define SYSCTL_XTAL_31MHZ       0x00001F00  

//
//! External main clock crystal is 32MHz.
//
#define SYSCTL_XTAL_32MHZ       0x00002000 
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Exported_APIs KLx SysCtl APIs
//! \brief KLx SysCtl API Reference
//! @{
//
//*****************************************************************************
#define SysCtlIPClockSourceSetConvert(ulPeripheral, ulSrc, ulDivide)          \
        xSysCtlPeripheralClockSourceSet(xSYSCTL_##ulPeripheral##_##ulSrc,     \
        ulDivide);
        
extern void SysCtlDelay(unsigned long ulCount);
extern void SysCtlPeripheralEnable(unsigned long ulPeripheral);
extern void SysCtlPeripheralDisable(unsigned long ulPeripheral);

extern void SysCtlSleep(void);
extern void SysCtlDeepSleep(void);
extern void SysCtlWakeupModuleEnable(xtBoolean bEnable, unsigned long ulModuleIndex);
extern xtBoolean SysCtlWakeupModuleFlagGet(unsigned long ulModuleIndex);
extern xtBoolean SysCtlWakeupPinFilterFlagGet(unsigned long ulFilterIndex);
extern xtBoolean SysCtlWakeupPinFlagGet(unsigned long ulPinIndex);
extern void SysCtlWakeupFilterConfig(unsigned long ulFilterIndex, 
                                     unsigned long ulPinIndex,
                                     unsigned long ulEdge);
extern void SysCtlWakeupPinConfig(xtBoolean bEnable, unsigned long ulPinIndex,
                                  unsigned long ulEdge);
extern unsigned long SysCtlResetSrcGet(void);
extern unsigned long SysCtlPowerModeGet(void);
extern void SysCtlResetPinFilterStopModeEnable(xtBoolean bEnable);
extern void SysCtlResetPinFilterBusClkWidthSet(unsigned char ulBusClkWidth);
extern void SysCtlResetPinFilterRunModeSelect(unsigned long ulFilter);
extern void SysCtlVeryLowPowerRunModeEnable(xtBoolean bEnable);
extern void SysCtlStopModeSet(unsigned long ulStopMode);
extern void SysCtlLVDWarningVolSet(unsigned long ulVoltage);
extern void SysCtlLVDVolSet(unsigned long ulVoltage);
extern void SysCtlLVDIntEnable(xtBoolean bEnable);
extern void SysCtlLVDWarningIntEnable(xtBoolean bEnable);
extern void SysCtlLVDResetEnable(xtBoolean bEnable);
extern xtBoolean SysCtlLVDEventFlagGet(void);
extern void SysCtlLVDEventFlagClear(void);
extern xtBoolean SysCtlLVDWaringFlagGet(void);
extern void SysCtlLVDWarningFlagClear(void);
extern void SysCtlBandgapEnable(xtBoolean bEnable);
extern void SysCtlBandgapBufferEnable(xtBoolean bEnable);
extern xtBoolean SysCtlRegulatorStatusGet(void);
extern void SysCtlPeripheralClockSourceSet(unsigned long ulPeripheralSrc);
extern void SysCtlHClockSourceSet(unsigned char ucHclkSrcSel);
extern void SysCtlBusClkSet(unsigned long ulBusClk);
extern unsigned long SysCtlBusClkGet(void);
extern unsigned long SysCtlHClockGet(void);
extern void SysCtlHClockSet(unsigned long ulSysClk, unsigned long ulConfig);
extern void SysCtlClkOututSrcSet(unsigned long ulClkOutSrc);
extern unsigned long SysCtlPWMAndUART0ClkGet(void);

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

#endif // __xSYSCTL_H__

