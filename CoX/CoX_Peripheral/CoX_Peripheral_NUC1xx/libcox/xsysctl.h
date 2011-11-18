//*****************************************************************************
//
//! \file xsysctl.h
//! \brief Prototypes for the System Manager Driver.
//! Prototypes for the Clock Controller Driver.
//! \version V2.1.1.1
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
//! |SysCtl Peripheral ID      |       CoX      |          NUC1xx          |
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
//! |xSYSCTL_PERIPH_PWMn       |  Non-Mandatory |    xSYSCTL_PERIPH_PWM0   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_PWM1   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_PWM2   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_PWM3   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_RTC        |    Mandatory   |             Y            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_SPIn       |    Mandatory   |    xSYSCTL_PERIPH_SSI0   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_SPI1   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_SPI2   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_SPI3   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_TIMERn     |    Mandatory   |   xSYSCTL_PERIPH_TIMER0  |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_TIMER1  |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_TIMER2  |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_TIMER3  |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_UARTn      |    Mandatory   |   xSYSCTL_PERIPH_UART0   |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_UART1   |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_UART2   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_WDOG       |    Mandatory   |             Y            |
//! +--------------------------+----------------+--------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xSYSCTL_PERIPH_ACMP0    SYSCTL_PERIPH_ACMP
#define xSYSCTL_PERIPH_ADC0     SYSCTL_PERIPH_ADC
#define xSYSCTL_PERIPH_DMA      SYSCTL_PERIPH_PDMA
#define xSYSCTL_PERIPH_GPIOA    SYSCTL_PERIPH_GPIO
#define xSYSCTL_PERIPH_GPIOB    SYSCTL_PERIPH_GPIO
#define xSYSCTL_PERIPH_GPIOC    SYSCTL_PERIPH_GPIO
#define xSYSCTL_PERIPH_GPIOD    SYSCTL_PERIPH_GPIO
#define xSYSCTL_PERIPH_GPIOE    SYSCTL_PERIPH_GPIO
#define xSYSCTL_PERIPH_I2C0     SYSCTL_PERIPH_I2C0
#define xSYSCTL_PERIPH_I2C1     SYSCTL_PERIPH_I2C1
#define xSYSCTL_PERIPH_PWMA     0x40105030
#define xSYSCTL_PERIPH_PWMB     0x401050C0
#define xSYSCTL_PERIPH_RTC      SYSCTL_PERIPH_RTC
#define xSYSCTL_PERIPH_SPI0     SYSCTL_PERIPH_SPI0
#define xSYSCTL_PERIPH_SPI1     SYSCTL_PERIPH_SPI1
#define xSYSCTL_PERIPH_SPI2     SYSCTL_PERIPH_SPI2
#define xSYSCTL_PERIPH_SPI3     SYSCTL_PERIPH_SPI3
#define xSYSCTL_PERIPH_TIMER0   SYSCTL_PERIPH_TMR0
#define xSYSCTL_PERIPH_TIMER1   SYSCTL_PERIPH_TMR1
#define xSYSCTL_PERIPH_TIMER2   SYSCTL_PERIPH_TMR2
#define xSYSCTL_PERIPH_TIMER3   SYSCTL_PERIPH_TMR3
#define xSYSCTL_PERIPH_UART0    SYSCTL_PERIPH_UART0
#define xSYSCTL_PERIPH_UART1    SYSCTL_PERIPH_UART1
#define xSYSCTL_PERIPH_UART2    SYSCTL_PERIPH_UART2
#define xSYSCTL_PERIPH_WDOG     SYSCTL_PERIPH_WDT

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
//! |SysCtl Clock Set Configs  |       CoX      |          NUC1xx          |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_OSC_MAIN          |    Mandatory   |             Y            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_OSC_INT           |    Mandatory   |             Y            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_OSC_INTSL         |  Non-Mandatory |             Y            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_OSC_EXTSL         |  Non-Mandatory |             Y            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_XTAL_nMHZ         |  Non-Mandatory |     xSYSCTL_XTAL_4MHZ    |
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
//! |                          |                |    xSYSCTL_XTAL_24MHZ    |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_INT_nMHZ          |  Non-Mandatory |     xSYSCTL_INT_22MHZ    |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_INTSL_nKHZ/HZ     |  Non-Mandatory |    xSYSCTL_INTSL_10KHZ   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_XTALSL_nHZ        |  Non-Mandatory |  xSYSCTL_XTALSL_32768HZ  |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_INT_OSC_DIS       |  Non-Mandatory |             Y            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_MAIN_OSC_DIS      |  Non-Mandatory |             Y            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PLL_PWRDN         |  Non-Mandatory |             Y            |
//! +--------------------------+----------------+--------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xSYSCTL_OSC_MAIN        (SYSCTL_OSC_MAIN | SYSCTL_PLL_MAIN)
#define xSYSCTL_OSC_INT         (SYSCTL_OSC_INT | SYSCTL_PLL_INT)
#define xSYSCTL_OSC_INTSL       SYSCTL_OSC_INTSL
#define xSYSCTL_OSC_EXTSL       SYSCTL_OSC_EXTSL

//
//! \brief XTAL Select
//
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

//
//! Internal main clock is 22MHz
//
#define xSYSCTL_INT_22MHZ       0x00000000  

//
//! Internal slow clock  is 10KHz.
//
#define xSYSCTL_INTSL_10KHZ     0x00000000  

//
//! External slow clock crystal is 32KHz.
//
#define xSYSCTL_XTALSL_32768HZ  0x00000000  

//
//! Disable internal oscillator
//
#define xSYSCTL_INT_OSC_DIS     0x00000004  

//
//! Disable main oscillator
//
#define xSYSCTL_MAIN_OSC_DIS    0x00000001  

//
//! Disable PLL
//
#define xSYSCTL_PLL_PWRDN       0x00010000  

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
//! |Peripheral Source Clock Set|       CoX      |          NUC1xx          |
//! |---------------------------|----------------|--------------------------|
//! |Those are all Non-Mandatory|  Non-Mandatory |             Y            |
//! | parameter,the Mandatory   |                |                          |
//! | is variable naming        |                |                          |
//! |ModuleName+n+SourceClock   |                |                          |
//! |---------------------------|----------------|--------------------------|
//! |xSYSCTL_WDT_EXTSL          |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! |xSYSCTL_WDT_HCLK_2048      |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! |xSYSCTL_WDT_INTSL          |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! |xSYSCTL_ADC0_MAIN          |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! |xSYSCTL_ADC0_PLL           |  Non-Mandatory |             Y            |
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
//! Watch dog clock source is external xxkHz crystal clock
//
#define xSYSCTL_WDT0_EXTSL      0x00000301  
                                
//
//! Watch dog clock source is HCLK/x clock
//
#define xSYSCTL_WDT0_HCLK_2048  0x00000302     
                                
//
//! Watch dog clock source is internal 10 kHz oscillator clock
//
#define xSYSCTL_WDT0_INTSL      0x00000303  
                                
//
//! ADC clock source is external 12 MHz crystal clock
//
#define xSYSCTL_ADC0_MAIN       0x01021000  
                                
//
//! ADC clock source is PLL clock
//
#define xSYSCTL_ADC0_PLL        0x01021001   
                                
//
//! ADC clock source is internal 22 MHz oscillator clock
//
#define xSYSCTL_ADC0_INT        0x01021003  
                                
//
//! Timer0 clock source is external 12 MHz crystal clock
//
#define xSYSCTL_TIMER0_MAIN     0x00080700  
                                
//
//! Timer0 clock source is external 32 KHz crystal clock
//
#define xSYSCTL_TIMER0_EXTSL    0x00080701   
                                
//
//! Timer0 clock source is HCLK
//
#define xSYSCTL_TIMER0_HCLK     0x00080702   
                                
//
//! Timer0 clock source is external trigger
//
#define xSYSCTL_TIMER0_EXTTRG   0x00080703  
                                
//
//! Timer0 clock source is internal 22 MHz oscillator clock
//
#define xSYSCTL_TIMER0_INT      0x00080704  
                                
//
//! Timer1 clock source is external 12 MHz crystal clock
//
#define xSYSCTL_TIMER1_MAIN     0x000C0700  
                                
//
//! Timer1 clock source is external 32kHz crystal clock
//
#define xSYSCTL_TIMER1_EXTSL    0x000C0701  
                                
//
//! Timer1 clock source is HCLK
//
#define xSYSCTL_TIMER1_HCLK     0x000C0702    
                                
//
//! Timer1 clock source is external trigger
//
#define xSYSCTL_TIMER1_EXTTRG   0x000C0703  
                                
//
//! Timer1 clock source is internal 22 MHz oscillator clock
//
#define xSYSCTL_TIMER1_INT      0x000C0707  
                                
//
//! Timer2 clock source is external 12 MHz crystal clock
//
#define xSYSCTL_TIMER2_MAIN     0x00100700  
                                
//
//! Timer2 clock source is external 32kHz crystal clock
//
#define xSYSCTL_TIMER2_EXTSL    0x00100701   
                                
//
//! Timer2 clock source is HCLK
//
#define xSYSCTL_TIMER2_HCLK     0x00100702  
                                
//
//! Timer2 clock source is external trigger
//
#define xSYSCTL_TIMER2_EXTTRG   0x00100703  
                                
//
//! Timer2 clock source is internal 22 MHz oscillator clock
//
#define xSYSCTL_TIMER2_INT      0x00100707
                                
//
//! Timer3 clock source is external 12 MHz crystal clock
//
#define xSYSCTL_TIMER3_MAIN     0x00140700  
                                
//
//! Timer3 clock source is external 32 KHz crystal clock
//
#define xSYSCTL_TIMER3_EXTSL    0x00140701   
                                
//
//! Timer3 clock source is HCLK
//
#define xSYSCTL_TIMER3_HCLK     0x00140702    
                                
//
//! Timer3 clock source is external trigger
//
#define xSYSCTL_TIMER3_EXTTRG   0x00140703  
                                
//
//! Timer3 clock source is internal 22 MHz oscillator clock
//
#define xSYSCTL_TIMER3_INT      0x00140707  
                                
//
//! UART clock source is external 12 MHz crystal clock
//
#define xSYSCTL_UART0_MAIN      0x01180800  
                                
//
//! UART clock source is PLL clock
//
#define xSYSCTL_UART0_PLL       0x01180801  
                                
//
//! UART clock source is internal 22 MHz oscillator clock
//
#define xSYSCTL_UART0_INT       0x01180803  
                                
//
//! UART clock source is external 12 MHz crystal clock
//
#define xSYSCTL_UART1_MAIN      0x01180800  
                                
//
//! UART clock source is PLL clock
//
#define xSYSCTL_UART1_PLL       0x01180801  
                                
//
//! UART clock source is internal 22 MHz oscillator clock
//
#define xSYSCTL_UART1_INT       0x01180803 
                                
//
//! UART clock source is external 12 MHz crystal clock
//
#define xSYSCTL_UART2_MAIN      0x01180800  
                                
//
//! UART clock source is PLL clock
//
#define xSYSCTL_UART2_PLL       0x01180801  
                                
//
//! UART clock source is internal 22 MHz oscillator clock
//
#define xSYSCTL_UART2_INT       0x01180803 
                                
//
//! CAN clock source is external 12 MHz crystal clock
//
#define xSYSCTL_CAN0_MAIN       0x011A0C00  
                                
//
//! CAN clock source is PLL clock 
//
#define xSYSCTL_CAN0_PLL        0x011A0C01   
                                
//
//! CAN clock source is internal 22 MHz oscillator clock
//
#define xSYSCTL_CAN0_INT        0x011A0C02  
                                
//
//! PWMA clock source is external 12 MHz crystal clock
//
#define xSYSCTL_PWMA_MAIN       0x001C0300 
                                
//
//! PWMA clock source is external 32kHz crystal clock
//
#define xSYSCTL_PWMA_EXTSL      0x001C0301   
                                
//
//! PWMA clock source is HCLK
//
#define xSYSCTL_PWMA_HCLK       0x001C0302   
                                
//
//! PWM0 and PWM1 clock source is internal 22 MHz oscillator clock
//
#define xSYSCTL_PWMA_INT        0x001C0303  
                                
//
//! I2S clock source is external 12 MHz crystal clock
//
#define xSYSCTL_I2S0_MAIN       0x10000300  
                                
//
//! I2S clock source is PLL
//
#define xSYSCTL_I2S0_PLL        0x10000301   
                                
//
//! I2S clock source is HCLK
//
#define xSYSCTL_I2S0_HCLK       0x10000302     
                                
//
//! I2S clock source is internal 22 MHz oscillator clock
//
#define xSYSCTL_I2S0_INT        0x10000303  
                                
//
//! frequency divide source is external 12 MHz crystal clock
//
#define xSYSCTL_FRQDIV_MAIN     0x10020300  
                                
//
//! frequency divide source is external 32kHz crystal clock
//
#define xSYSCTL_FRQDIV_EXTSL    0x10020301  
                                
//
//! frequency divide source is HCLK
//
#define xSYSCTL_FRQDIV_HCLK     0x10020302          
                                
//
//! frequency divide source is internal 22 MHz oscillator clock
//
#define xSYSCTL_FRQDIV_INT      0x10020303  
                                
//
//! PWMB clock source is external 12 MHz crystal clock
//
#define xSYSCTL_PWMB_MAIN       0x10040300  
                                
//
//! PWMB clock source is external 32 KHz crystal clock
//
#define xSYSCTL_PWMB_EXTSL      0x10040301  
                                
// 
//! PWMB clock source is HCLK
//
#define xSYSCTL_PWMB_HCLK       0x10040302       
                                
//
//! PWMB clock source is internal 22 MHz oscillator clock
//
#define xSYSCTL_PWMB_INT        0x10040303  

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
//! <b> ModuleName + n </b>, such as CAN0, ADC0.
//!
//! \section xSysCtl_Peripheral_Short_CoX CoX Port Details
//! \verbatim
//! +-------------------------- +----------------+--------------------------+
//! |Peripheral Short name      |       CoX      |          NUC1xx          |
//! |---------------------------|----------------|--------------------------|
//! |ADCn                       |  Non-Mandatory |           ADC0           |
//! |---------------------------|----------------|--------------------------|
//! |PWMn                       |  Non-Mandatory |           PWMA           |
//! |                           |                |           PWMB           |
//! |-------------------------- |----------------|--------------------------|
//! |CANn                       |  Non-Mandatory |           CAN0           |
//! |-------------------------- |----------------|--------------------------|
//! |UARTn                      |  Non-Mandatory |           UART0          |
//! |                           |                |           UART1          |
//! |                           |                |           UART2          |
//! |-------------------------- |----------------|--------------------------|
//! |I2Sn                       |  Non-Mandatory |           I2S0           |
//! |-------------------------- |----------------|--------------------------|
//! |WDTn                       |  Non-Mandatory |           WDT0           |
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
//! |Peripheral Clock source    |       CoX      |          NUC1xx          |
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
#define PWMB                    PWMB
#define PWMA                    PWMA
#define FRQDIV                  FRQDIV
#define I2S0                    I2S0
#define TIMER0                  TIMER0
#define TIMER1                  TIMER1
#define TIMER2                  TIMER2
#define TIMER3                  TIMER3
#define UART0                   UART0
#define UART1                   UART1
#define UART2                   UART2
#define CAN0                    CAN0
#define WDT0                    WDT0

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
//! |xSysCtl API                     |       CoX      | NUC1xx |
//! |--------------------------------|----------------|--------|
//! |xSysCtlPeripheralReset          |    Mandatory   |    Y   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlPeripheralEnable         |    Mandatory   |    Y   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlPeripheralDisable        |    Mandatory   |    Y   |
//! |--------------------------------|----------------|--------|
//! |xSysCtlPeripheralReset2         |    Mandatory   |    Y   |
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
#define xSysCtlPeripheralReset(ulPeripheralID)                                \
        SysCtlPeripheralReset(ulPeripheralID)
        
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
extern void xSysCtlPeripheralReset2(unsigned long ulPeripheralBase);
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
//! |       NUC1xx       |    ADC0                |MAIN PLL INT               |
//! |                    |    PWMB                |INT HCLK EXTSL MAIN        |
//! |                    |    PWMA                |INT HCLK EXTSL MAIN        |
//! |                    |    FRQDIV              |INT HCLK EXTSL MAIN        |
//! |                    |    I2S0                |INT HCLK PLL MAIN          |
//! |                    |    TIMER0              |INT EXTTRG HCLK EXTSL MAIN |
//! |                    |    TIMER1              |INT EXTTRG HCLK EXTSL MAIN |
//! |                    |    TIMER2              |INT EXTTRG HCLK EXTSL MAIN |
//! |                    |    TIMER3              |INT EXTTRG HCLK EXTSL MAIN |
//! |                    |    UART0               |INT PLL MAIN               |
//! |                    |    UART1               |INT PLL MAIN               |
//! |                    |    UART2               |INT PLL MAIN               |
//! |                    |    CAN0                |INT PLL MAIN               |
//! |                    |    WDT0                |INTSL HCLK_2048 EXTSL      |
//! |--------------------|------------------------|---------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************                                          unsigned long ulDivide);
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
//! \addtogroup NUC1xx_SysCtl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Peripheral_ID NUC1xx SysCtl Peripheral ID
//! \brief Values that show SysCtl Peripheral ID
//! Values that can be passed to the
//! SysCtlPeripheralPresent(), SysCtlPeripheralEnable(),
//! SysCtlPeripheralDisable(), and SysCtlPeripheralReset() APIs as the
//! ulPeripheral parameter.  The peripherals in the fourth group (upper nibble
//! is 3) can only be used with the SysCtlPeripheralPresent() API.
//! @{
//
//*****************************************************************************

//
//! PDMA
//
#define SYSCTL_PERIPH_PDMA      0x30040002  

//
//! EBI
//
#define SYSCTL_PERIPH_EBI       0x30080000 

//
//! ISP No reset
//
#define SYSCTL_PERIPH_ISP       0x00000004  

//
//! WDT No reset
//
#define SYSCTL_PERIPH_WDT       0x00004001  

//
//! GPIO No enable
//
#define SYSCTL_PERIPH_GPIO      0x70020000  

//
//! RTC No reset
//
#define SYSCTL_PERIPH_RTC       0x00004002  

//
//! TMR0
//
#define SYSCTL_PERIPH_TMR0      0x70044004  

//
//! TMR1
//
#define SYSCTL_PERIPH_TMR1      0x70084008  

//
//! TMR2
//
#define SYSCTL_PERIPH_TMR2      0x70104010  

//
//! TMR3
//
#define SYSCTL_PERIPH_TMR3      0x70204020  

//
//! FDIV No reset
//
#define SYSCTL_PERIPH_FDIV      0x00004040  

//
//! I2C0
//
#define SYSCTL_PERIPH_I2C0      0x68014801  

//
//! I2C1
//
#define SYSCTL_PERIPH_I2C1      0x68024802  

//
//! SPI0
//
#define SYSCTL_PERIPH_SPI0      0x68104810 

//
//! SPI1
//
#define SYSCTL_PERIPH_SPI1      0x68204820  

//
//! SPI2
//
#define SYSCTL_PERIPH_SPI2      0x68404840  

//
//! SPI3
//
#define SYSCTL_PERIPH_SPI3      0x68804880  

//
//! UART0
//
#define SYSCTL_PERIPH_UART0     0x40015001  

//
//! UART1
//
#define SYSCTL_PERIPH_UART1     0x40025002  

//
//! UART2
//
#define SYSCTL_PERIPH_UART2     0x40045004  

//
//! PWM01
//
#define SYSCTL_PERIPH_PWM01     0x40105010  

//
//! PWM23
//
#define SYSCTL_PERIPH_PWM23     0x40105020  

//
//! PWM45
//
#define SYSCTL_PERIPH_PWM45     0x40205040  

//
//! PWM67
//
#define SYSCTL_PERIPH_PWM67     0x40205080  

//
//! CAN0
//
#define SYSCTL_PERIPH_CAN0      0x48015801  

//
//! USBD
//
#define SYSCTL_PERIPH_USBD      0x48085808  

//
//! ADC
//
#define SYSCTL_PERIPH_ADC       0x48105810  

//
//! I2S
//
#define SYSCTL_PERIPH_I2S       0x48205820  

//
//! ACMP
//
#define SYSCTL_PERIPH_ACMP      0x40405840  

//
//! PS2
//
#define SYSCTL_PERIPH_PS2       0x40805880  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Peripheral_Src_Clk SysCtl Peripheral Source Clock
//! \brief Values that show SysCtl Peripheral Source Clock
//! The following are values that can be passed to the
//! SysCtlPeripheralClockSourceSet()  API as the
//! ulPeripheralsrc parameter.  
//! @{
//
//*****************************************************************************

//
//! Watch dog clock source is external 32kHz crystal clock
//
#define SYSCTL_PERIPH_WDG_S_EXT32K                                            \
                                0x00000301  
                                
//
//! Watch dog clock source is HCLK/2048 clock
//
#define SYSCTL_PERIPH_WDG_S_HCLK_2048                                         \
                                0x00000302     
                                
//
//! Watch dog clock source is internal 10 kHz oscillator clock
//
#define SYSCTL_PERIPH_WDG_S_INT10K                                            \
                                0x00000303  
                                
//
//! ADC clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_ADC_S_EXT12M                                            \
                                0x00020300  
                                
//
//! ADC clock source is PLL clock
//
#define SYSCTL_PERIPH_ADC_S_PLL                                               \
                                0x00020301   
                                
//
//! ADC clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_ADC_S_INT22M                                            \
                                0x00020303  
                                
//
//! Timer0 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_TMR0_S_EXT12M                                           \
                                0x00080700  
                                
//
//! Timer0 clock source is external 32 KHz crystal clock
//
#define SYSCTL_PERIPH_TMR0_S_EXT32K                                           \
                                0x00080701   
                                
//
//! Timer0 clock source is HCLK
//
#define SYSCTL_PERIPH_TMR0_S_HCLK                                             \
                                0x00080702   
                                
//
//! Timer0 clock source is external trigger
//
#define SYSCTL_PERIPH_TMR0_S_EXTTRG                                           \
                                0x00080703  
                                
//
//! Timer0 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_TMR0_S_INT22M                                           \
                                0x00080704  
                                
//
//! Timer1 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_TMR1_S_EXT12M                                           \
                                0x000C0700  
                                
//
//! Timer1 clock source is external 32kHz crystal clock
//
#define SYSCTL_PERIPH_TMR1_S_EXT32K                                           \
                                0x000C0701  
                                
//
//! Timer1 clock source is HCLK
//
#define SYSCTL_PERIPH_TMR1_S_HCLK                                             \
                                0x000C0702    
                                
//
//! Timer1 clock source is external trigger
//
#define SYSCTL_PERIPH_TMR1_S_EXTTRG                                           \
                                0x000C0703  
                                
//
//! Timer1 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_TMR1_S_INT22M                                           \
                                0x000C0707  
                                
//
//! Timer2 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_TMR2_S_EXT12M                                           \
                                0x00100700  
                                
//
//! Timer2 clock source is external 32kHz crystal clock
//
#define SYSCTL_PERIPH_TMR2_S_EXT32K                                           \
                                0x00100701   
                                
//
//! Timer2 clock source is HCLK
//
#define SYSCTL_PERIPH_TMR2_S_HCLK                                             \
                                0x00100702  
                                
//
//! Timer2 clock source is external trigger
//
#define SYSCTL_PERIPH_TMR2_S_EXTTRG                                           \
                                0x00100703  
                                
//
//! Timer2 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_TMR2_S_INT22M                                           \
                                0x00100707
                                
//
//! Timer3 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_TMR3_S_EXT12M                                           \
                                0x00140700  
                                
//
//! Timer3 clock source is external 32 KHz crystal clock
//
#define SYSCTL_PERIPH_TMR3_S_EXT32K                                           \
                                0x00140701   
                                
//
//! Timer3 clock source is HCLK
//
#define SYSCTL_PERIPH_TMR3_S_HCLK                                             \
                                0x00140702    
                                
//
//! Timer3 clock source is external trigger
//
#define SYSCTL_PERIPH_TMR3_S_EXTTRG                                           \
                                0x00140703  
                                
//
//! Timer3 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_TMR3_S_INT22M                                           \
                                0x00140707  
                                
//
//! UART clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_UART_S_EXT12M                                           \
                                0x00180300  
                                
//
//! UART clock source is PLL clock
//
#define SYSCTL_PERIPH_UART_S_PLL                                              \
                                0x00180301  
                                
//
//! UART clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_UART_S_INT22M                                           \
                                0x00180303  
                                
//
//! CAN clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_CAN_S_EXT12M                                            \
                                0x001A0300  
                                
//
//! CAN clock source is PLL clock 
//
#define SYSCTL_PERIPH_CAN_S_PLL                                               \
                                0x001A0301   
                                
//
//! CAN clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_CAN_S_INT22M                                            \
                                0x001A0302  
                                
//
//! PWM0 and PWM1 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_PWM01_S_EXT12M                                          \
                                0x001C0300 
                                
//
//! PWM0 and PWM1 clock source is external 32kHz crystal clock
//
#define SYSCTL_PERIPH_PWM01_S_EXT32K                                          \
                                0x001C0301   
                                
//
//! PWM0 and PWM1 clock source is HCLK
//
#define SYSCTL_PERIPH_PWM01_S_HCLK                                            \
                                0x001C0302   
                                
//
//! PWM0 and PWM1 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_PWM01_S_INT22M                                          \
                                0x001C0303  
                                
//
//! PWM2 and PWM3 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_PWM23_S_EXT12M                                          \
                                0x001E0300  
                                
//
//! PWM2 and PWM3 clock source is external 32kHz crystal clock
//
#define SYSCTL_PERIPH_PWM23_S_EXT32K                                          \
                                0x001E0301    
                                
//
//! PWM2 and PWM3 clock source is HCLK
//
#define SYSCTL_PERIPH_PWM23_S_HCLK                                            \
                                0x001E0302  
                                
//
//! PWM2 and PWM3 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_PWM23_S_INT22M                                          \
                                0x001E0303  
                                
//
//! I2S clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_I2S_S_EXT12M                                            \
                                0x10000300  
                                
//
//! I2S clock source is PLL
//
#define SYSCTL_PERIPH_I2S_S_PLL                                               \
                                0x10000301   
                                
//
//! I2S clock source is HCLK
//
#define SYSCTL_PERIPH_I2S_S_HCLK                                              \
                                0x10000302     
                                
//
//! I2S clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_I2S_S_INT22M                                            \
                                0x10000303  
                                
//
//! frequency divide source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_FRQDIV_S_EXT12M                                         \
                                0x10020300  
                                
//
//! frequency divide source is external 32kHz crystal clock
//
#define SYSCTL_PERIPH_FRQDIV_S_EXT32K                                         \
                                0x10020301  
                                
//
//! frequency divide source is HCLK
//
#define SYSCTL_PERIPH_FRQDIV_S_HCLK                                           \
                                0x10020302          
                                
//
//! frequency divide source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_FRQDIV_S_INT22M                                         \
                                0x10020303  
                                
//
//! PWM4 and PWM5 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_PWM45_S_EXT12M                                          \
                                0x10040300  
                                
//
//! PWM4 and PWM5 clock source is external 32 KHz crystal clock
//
#define SYSCTL_PERIPH_PWM45_S_EXT32K                                          \
                                0x10040301  
                                
//
//! PWM4 and PWM5 clock source is HCLK
//
#define SYSCTL_PERIPH_PWM45_S_HCLK                                            \
                                0x10040302       
                                
//
//! PWM4 and PWM5 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_PWM45_S_INT22M                                          \
                                0x10040303  
                                
//
//! PWM6 and PWM7 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_PWM67_S_EXT12M                                          \
                                0x10060300  
                                
//
//! PWM6 and PWM7 clock source is external 32 KHz crystal clock
//
#define SYSCTL_PERIPH_PWM67_S_EXT32K                                          \
                                0x10060301   
                                
//
//! PWM6 and PWM7 clock source is HCLK 
//
#define SYSCTL_PERIPH_PWM67_S_HCLK                                            \
                                0x10060302   
                                
//
//! PWM6 and PWM7 clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_PWM67_S_INT22M                                          \
                                0x10060303  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Hclk_Src NUC1xx SysCtl Hclk Source
//! brief Values that show NUC1xx SysCtl Hclk Source
//! The following are values that can be passed to the
//! SysCtlHClockSourceSet()\ SysCtlHClockSet API as the
//! ulhclkSrcSel parameter.   
//! @{
//
//*****************************************************************************

//
//! Systick Clock source is external 12 MHz crystal clock
//
#define SYSCTL_HLCK_S_EXT12M    0x00000000 

//
//! Systick Clock source is external 32 KHz crystal clock
//
#define SYSCTL_HLCK_S_EXT32K    0x00000001  

//
//! Systick Clock source is PLL clock
//
#define SYSCTL_HLCK_S_PLL       0x00000002  

//
//! Systick Clock source is internal 10 kHz oscillator clock
//
#define SYSCTL_HLCK_S_INT10K    0x00000003  

//
//! Systick Clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_HLCK_S_INT22M    0x00000007  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Stclk_Src NUC1xx SysCtl Stclk Source
//! \brief Values that show NUC1xx SysCtl Stclk Source
//! The following are values that can be passed to the
//! SysCtlSysTickSourceSet()  API as the
//! ulstclkSrcSel parameter.   
//! @{
//
//*****************************************************************************

//
//! Systick Clock source is external 12 MHz crystal clock
//
#define SYSCTL_STCLK_S_EXT12M   0x00000000  

//
//! Systick Clock source is external 32 KHz crystal clock
//
#define SYSCTL_STCLK_S_EXT32K   0x00000008  

//
//! Systick Clock source is 12 MHz crystal clock/2
//
#define SYSCTL_STCLK_S_EXT12M_2 0x00000010  

//
//! Systick Clock source is HCLK/2
//
#define SYSCTL_STCLK_S_HCLK_2   0x00000018  

//
//! Systick Clock source is internal 22 MHz oscillator clock/2
//
#define SYSCTL_STCLK_S_INT22M_2 0x00000038  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Reset_Src NUC1xx SysCtl Reset Source
//! \brief Values that show NUC1xx SysCtl Reset Source
//! The following are values that can be returned in the bit mask
//! by the SysCtlResetSrcGet() API.   
//! @{
//
//*****************************************************************************

//
//! "reset signal" from Power-On Reset
//
#define SYSCTL_RSTSRC_POR       0x00000001  

//
//! "reset signal" from the /RESET pin
//
#define SYSCTL_RSTSRC_PAD       0x00000002 

//
//! "reset signal" from the Watch-Dog
//
#define SYSCTL_RSTSRC_WDG       0x00000004  

//
//! "reset signal" from Low-Voltage-Reset
//
#define SYSCTL_RSTSRC_LVR       0x00000008  

//
//! "reset signal" from Brown-Out-Detected
//
#define SYSCTL_RSTSRC_BOD       0x00000010  

//
//! "reset signal" from MCU Cortex_M0 kernel
//
#define SYSCTL_RSTSRC_SYS       0x00000020  

//
//! "reset signal" from CPU_RST (IPRSTCR1[1])
//
#define SYSCTL_RSTSRC_CPU       0x00000080  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Bod_level NUC1xx SysCt Bod level
//! \brief Values that show NUC1xx SysCt Bod level
//! The following are values that can be passed to the
//! SysCtlSelectBODVolt()  API as the
//! ulVoltage parameter.  
//! @{
//
//*****************************************************************************

//
//! Threshold Voltage 2.2V
//
#define SYSCTL_BOD_2_2          0x00000000  

//
//! Threshold Voltage 2.6V
//
#define SYSCTL_BOD_2_6          0x00000002  

//
//! Threshold Voltage 3.8V
//
#define SYSCTL_BOD_3_8          0x00000004  

//
//! Threshold Voltage 4.5V
//
#define SYSCTL_BOD_4_5          0x00000006  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Peripheral_ClkDiv NUC1xx SysCtl Peripheral ClkDiv
//! \brief Values that show NUC1xx SysCtl Peripheral ClkDiv
//! The following are values that can be passed to the
//! SysCtlIPClockDividerSet()  API as the
//! ulConfig parameter. 
//! @{
//
//*****************************************************************************

//
//! HCLK clock divide number mask
// 
#define SYSCTL_PERIPH_HCLK_D    0x00000000  

//
//! USB clock divide number mask
//
#define SYSCTL_PERIPH_USB_D     0x00040800  

//
//! UART clock divide number mask
//
#define SYSCTL_PERIPH_UART_D    0x00080800  

//
//! CAN clock divide number mask
//
#define SYSCTL_PERIPH_CAN_D     0x000C0C00  

//
//! ADC clock divide number mask
//
#define SYSCTL_PERIPH_ADC_D     0x00101000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Clock_Config NUC1xx SysCtl Clock Configuration
//! \brief NUC1xx SysCtl Clock Configuration
//! The following are values that can be passed to the SysCtlClockSet() API as
//! the ulConfig parameter.
//! @{
//
//*****************************************************************************

//
//! Processor clock is osc/pll /1
//
#define SYSCTL_SYSDIV_1         0x00000000  

//
//! Processor clock is osc/pll /2
//
#define SYSCTL_SYSDIV_2         0x01000000  

//
//! Processor clock is osc/pll /3
//
#define SYSCTL_SYSDIV_3         0x02000000  

//
//! Processor clock is osc/pll /4
//
#define SYSCTL_SYSDIV_4         0x03000000  

//
//! Processor clock is osc/pll /5
//
#define SYSCTL_SYSDIV_5         0x04000000  

//
//! Processor clock is osc/pll /6
//
#define SYSCTL_SYSDIV_6         0x05000000  

//
//! Processor clock is osc/pll /7
//
#define SYSCTL_SYSDIV_7         0x06000000  

//
//! Processor clock is osc/pll /8
//
#define SYSCTL_SYSDIV_8         0x07000000  

//
//! Processor clock is osc/pll /9
//
#define SYSCTL_SYSDIV_9         0x08000000  

//
//! Processor clock is osc/pll /10
//
#define SYSCTL_SYSDIV_10        0x09000000  

//
//! Processor clock is osc/pll /11
//
#define SYSCTL_SYSDIV_11        0x0A000000  

//
//! Processor clock is osc/pll /12
//
#define SYSCTL_SYSDIV_12        0x0B000000  

//
//! Processor clock is osc/pll /13
//
#define SYSCTL_SYSDIV_13        0x0C000000  

//
//! Processor clock is osc/pll /14
//
#define SYSCTL_SYSDIV_14        0x0D000000  

//
//! Processor clock is osc/pll /15
//
#define SYSCTL_SYSDIV_15        0x0E000000  

//
//! Processor clock is osc/pll /16
//
#define SYSCTL_SYSDIV_16        0x0F000000  

//
//! Disable internal oscillator
//
#define SYSCTL_INT_OSC_DIS      0x00000004  

//
//! Disable main oscillator
//
#define SYSCTL_MAIN_OSC_DIS     0x00000001  

//
//! Disable PLL
//
#define SYSCTL_PLL_PWRDN        0x00010000  

//
//! HCLK source is main osc
//
#define SYSCTL_OSC_MAIN         0x00000000  

//
//! HCLK source is ext. 32 KHz
//
#define SYSCTL_OSC_EXTSL        0x00000010  

//
//! HCLK source is PLL
//
#define SYSCTL_OSC_PLL          0x00000020  

//
//! HCLK source is int. osc
//
#define SYSCTL_OSC_INT          0x00000040  

//
//! HCLK source is int. 10 KHz
//
#define SYSCTL_OSC_INTSL        0x00000030  

//
//! Oscillator Source
//
#define SYSCTL_OSCSRC_M         0x00080070 

//
//! PLL source is int. 12 MHz
//
#define SYSCTL_PLL_MAIN         0x00000000  

//
//! PLL source is int. 22 MHz
//
#define SYSCTL_PLL_INT          0x00080000  

//
//! External main clock crystal mask.
//
#define SYSCTL_XTAL_MASK        0x0000FF00  

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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Exported_APIs NUC1xx SysCtl APIs
//! \brief NUC1xx SysCtl API Reference
//! @{
//
//*****************************************************************************
#define SysCtlIPClockSourceSetConvert(ulPeripheral, ulSrc, ulDivide)          \
        xSysCtlPeripheralClockSourceSet(xSYSCTL_##ulPeripheral##_##ulSrc,     \
        ulDivide);
        
extern void SysCtlDelay(unsigned long ulCount);

extern void SysCtlPeripheralReset(unsigned long ulPeripheral);
extern void SysCtlPeripheralEnable(unsigned long ulPeripheral);
extern void SysCtlPeripheralDisable(unsigned long ulPeripheral);
extern void SysCtlPeripheralClockSourceSet(unsigned long ulPeripheralSrc);
extern void SysCtlHClockSourceSet(unsigned long ulHclkSrcSel);
extern void SysCtlSysTickSourceSet(unsigned long ulStclkSrcSel);

extern void SysCtlCPUReset(void);
extern void SysCtlChipReset(void);
extern void SysCtlSleep(void);
extern void SysCtlReset(void);
extern void SysCtlDeepSleep(void);

extern xtBoolean  SysCtlKeyAddrUnlock(void);
extern xtBoolean  SysCtlKeyAddrLock(void);

extern unsigned long SysCtlResetSrcGet(void);
extern void SysCtlResetSrcClear(unsigned long ulSrc);

extern void SysCtlBODEnable(xtBoolean bEnable);
extern void SysCtlBODVoltSelect(unsigned char ulVoltage);
extern void SysCtlBODLowPowerModeEnable(xtBoolean bEnable);
extern void SysCtlLowVoltRstEnable(xtBoolean bEnable);
extern void SysCtlTempatureSensorEnable(xtBoolean bEnable);

extern xtBoolean SysCtlBODStateGet(void);
extern void SysCtlBODRstEnable(xtBoolean bEnable);
extern void SysCtlRCAdjValueSet(unsigned long ulAdjValue);

extern void SysCtlIPClockDividerSet(unsigned long ulConfig);
extern void SysCtlFreqDividerOutputEnable(xtBoolean bEnable, unsigned char u8Divider);
extern void SysCtlPWRWUIntEnable(xtBoolean bEnable, xtBoolean bDelay);
extern void SysCtlPowerDownEnable(xtBoolean bEnable);
extern void SysCtlPowerDownWaitCPUSet(xtBoolean bEnable);
extern unsigned long SysCtlHClockGet(void);
extern void SysCtlHClockSet(unsigned long ulConfig);

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

