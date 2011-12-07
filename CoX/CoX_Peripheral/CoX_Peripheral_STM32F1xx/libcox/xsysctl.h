//*****************************************************************************
//
//! \file xsysctl.h
//! \brief Prototypes for the System Manager Driver.
//! \brief Prototypes for the Clock Controller Driver.
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
//! |SysCtl Peripheral ID      |       CoX      |          STM32F1xx          |
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

#define xSYSCTL_PERIPH_ACMP0    0
#define xSYSCTL_PERIPH_ADC0     0
#define xSYSCTL_PERIPH_DMA      0
#define xSYSCTL_PERIPH_GPIOA    0
#define xSYSCTL_PERIPH_GPIOB    0
#define xSYSCTL_PERIPH_GPIOC    0
#define xSYSCTL_PERIPH_GPIOD    0
#define xSYSCTL_PERIPH_GPIOE    0
#define xSYSCTL_PERIPH_I2C0     0
#define xSYSCTL_PERIPH_I2C1     0
#define xSYSCTL_PERIPH_PWMA     0
#define xSYSCTL_PERIPH_PWMB     0
#define xSYSCTL_PERIPH_RTC      0
#define xSYSCTL_PERIPH_SPI0     0
#define xSYSCTL_PERIPH_SPI1     0
#define xSYSCTL_PERIPH_SPI2     0
#define xSYSCTL_PERIPH_SPI3     0
#define xSYSCTL_PERIPH_TIMER0   0
#define xSYSCTL_PERIPH_TIMER1   0
#define xSYSCTL_PERIPH_TIMER2   0
#define xSYSCTL_PERIPH_TIMER3   0
#define xSYSCTL_PERIPH_UART0    0
#define xSYSCTL_PERIPH_UART1    0
#define xSYSCTL_PERIPH_UART2    0
#define xSYSCTL_PERIPH_WDOG     0

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
//! |SysCtl Clock Set Configs  |       CoX      |          STM32F1xx          |
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

#define xSYSCTL_OSC_MAIN        0
#define xSYSCTL_OSC_INT         0
#define xSYSCTL_OSC_INTSL       0
#define xSYSCTL_OSC_EXTSL       0

//
//! \brief XTAL Select
//
#define xSYSCTL_XTAL_4MHZ       0
#define xSYSCTL_XTAL_5MHZ       0
#define xSYSCTL_XTAL_6MHZ       0
#define xSYSCTL_XTAL_7MHZ       0
#define xSYSCTL_XTAL_8MHZ       0
#define xSYSCTL_XTAL_9MHZ       0
#define xSYSCTL_XTAL_10MHZ      0
#define xSYSCTL_XTAL_11MHZ      0
#define xSYSCTL_XTAL_12MHZ      0
#define xSYSCTL_XTAL_13MHZ      0
#define xSYSCTL_XTAL_14MHZ      0
#define xSYSCTL_XTAL_15MHZ      0
#define xSYSCTL_XTAL_16MHZ      0
#define xSYSCTL_XTAL_17MHZ      0
#define xSYSCTL_XTAL_18MHZ      0
#define xSYSCTL_XTAL_19MHZ      0
#define xSYSCTL_XTAL_20MHZ      0
#define xSYSCTL_XTAL_21MHZ      0
#define xSYSCTL_XTAL_22MHZ      0
#define xSYSCTL_XTAL_23MHZ      0
#define xSYSCTL_XTAL_24MHZ      0

//
//! Internal main clock is 22MHz
//
#define xSYSCTL_INT_22MHZ       0  

//
//! Internal slow clock  is 10KHz.
//
#define xSYSCTL_INTSL_10KHZ     0  

//
//! External slow clock crystal is 32KHz.
//
#define xSYSCTL_XTALSL_32768HZ  0  

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
//! |Peripheral Source Clock Set|       CoX      |          STM32F1xx          |
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
//! |Peripheral Short name      |       CoX      |          STM32F1xx          |
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
//! |Peripheral Clock source    |       CoX      |          STM32F1xx          |
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
//! |xSysCtl API                     |       CoX      | STM32F1xx |
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
extern void xSysCtlPeripheralReset(unsigned long ulPeripheralID);
        
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
//! \note It takes five clock cycles after the write to enable a peripheral
//! before the the peripheral is actually enabled.  During this time, attempts
//! to access the peripheral will result in a bus fault.  Care should be taken
//! to ensure that the peripheral is not accessed during this brief time
//! period.
//!
//! \return None.
//
//*****************************************************************************
extern void xSysCtlPeripheralEnable(unsigned long ulPeripheralID);

//*****************************************************************************
//
//! \brief Disable a peripheral.
//!
//! \param ulPeripheralID is the peripheral to disable.
//! Details please Refer to \ref xSysCtl_Peripheral_ID.
//!
//! Peripherals are disabled with this function.  Once disabled, they will not
//! operate or respond to register reads/writes.
//!
//! The \e ulPeripheralID parameter must be only one of the following values:
//! Details please Refer to \ref xSysCtl_Peripheral_ID_CoX.
//!
//! \return None.
//
//*****************************************************************************
extern void xSysCtlPeripheralDisable(unsigned long ulPeripheralID);
        
//*****************************************************************************
//
//! \brief Enable a peripheral.
//!
//! \param ulPeripheralBase a Peripheral base indicate which peripheral to be 
//! enabled.Details please Refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! Details please Refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
extern void xSysCtlPeripheralEnable2(unsigned long ulPeripheralBase);
        
//*****************************************************************************
//
//! \brief Disable a peripheral.
//!
//! \param ulPeripheralBase a Peripheral base indicate which peripheral to be 
//! enabled.Details please Refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! Peripherals are disabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! Details please Refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
extern void xSysCtlPeripheralDisable2(unsigned long ulPeripheralBase);
        
//*****************************************************************************
//
//! \brief Reset a peripheral.
//!
//! \param ulPeripheralBase a Peripheral base indicate which peripheral to be 
//! Reset.Details please Refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! Peripherals are Reset with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! Details please Refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
extern void xSysCtlPeripheralReset2(unsigned long ulPeripheralBase);

//*****************************************************************************
//
//! \brief Get the peripheral interrupt number through peripheral base.
//!
//! \param ulPeripheral The peripheral's base  
//!
//! \note It's especially useful to enable the short pin's corresponding 
//! peripheral interrupt: Use the short pin to Get the GPIO base through 
//! \ref xGPIOSPinToPort function, and then use this function to enable the GPIO
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
extern unsigned long xSysCtlPeripheraIntNumGet(unsigned long ulPeripheralBase);

//*****************************************************************************
//
//! \brief Set the clocking of the device.
//!
//! \param ulConfig is the required configuration of the device clocking.
//!
//! This function configures the clocking of the device.  The input crystal
//! frequency, oscillator to be used, use of the PLL, and the system clock
//! divider are all configured with this function.
//!
//! The \e ulConfig parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The external crystal frequency is chosen with one of the following values:
//! \ref xSYSCTL_XTAL_4MHZ, \ref xSYSCTL_XTAL_5MHZ, \ref xSYSCTL_XTAL_6MHZ,
//! \ref xSYSCTL_XTAL_24MHZ.
//!
//! The oscillator source is chosen with one of the following values:
//! \ref xSYSCTL_OSC_MAIN, \ref xSYSCTL_OSC_INT, \ref xSYSCTL_OSC_INTSL,
//! \ref xSYSCTL_OSC_EXTSL.
//!
//! The internal and main oscillators and PLL are disabled with the
//! \ref xSYSCTL_INT_OSC_DIS and \ref xSYSCTL_MAIN_OSC_DIS flags, 
//! \ref xSYSCTL_PLL_PWRDN respectively.
//! The external oscillator must be enabled in order to use an external clock
//! source.  Note that attempts to disable the oscillator used to clock the
//! device will be prevented by the hardware.
//! <br />
//! Details please Refer to \ref XSysCtl_Clock_Set_Config_CoX.
//! 
//!
//! \return None.
//
//*****************************************************************************
extern void xSysCtlClockSet(unsigned long ulSysClk, unsigned long ulConfig);

//*****************************************************************************
//
//! \brief Get the processor clock rate.
//!
//! This function determines the clock rate of the processor clock.  This is
//! also the clock rate of all the peripheral modules (with the exception of
//! PWM, which has its own clock divider).
//!
//! \note This will not return accurate results if SysCtlClockSet() has not
//! been called to configure the clocking of the device, or if the device is
//! directly clocked from a crystal (or a clock source) that is not one of the
//! supported crystal frequencies.  In the later case, this function should be
//! modified to directly return the correct system clock rate.
//!
//! \return The processor clock rate.
//
//*****************************************************************************
extern unsigned long xSysCtlClockGet(void);

//*****************************************************************************
//
//! \brief Provide a small delay.
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
extern void xSysCtlDelay(unsigned long ulCount);

//*****************************************************************************
//
//! \brief Reset the device.
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
extern void xSysCtlReset(void);

//*****************************************************************************
//
//! \brief Put the processor into sleep mode.
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
extern void xSysCtlSleep(void);
        
//*****************************************************************************
//
//! \brief Enable a peripheral.
//!
//! \param ulPeripheralBase a Peripheral base indicate which peripheral to be 
//! enabled.Details please Refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! Details please Refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
extern void xSysCtlPeripheralEnable2(unsigned long ulPeripheralBase);
        
//*****************************************************************************
//
//! \brief Disable a peripheral.
//!
//! \param ulPeripheralBase a Peripheral base indicate which peripheral to be 
//! enabled.Details please Refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! Peripherals are disabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! Details please Refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
extern void xSysCtlPeripheralDisable2(unsigned long ulPeripheralBase);
        
//*****************************************************************************
//
//! \brief Reset a peripheral.
//!
//! \param ulPeripheralBase a Peripheral base indicate which peripheral to be 
//! Reset.Details please Refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! Peripherals are Reset with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! Details please Refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
extern void xSysCtlPeripheralReset2(unsigned long ulPeripheralBase);

//*****************************************************************************
//
//! \brief Set a peripheral clock source and peripheral divide.
//!
//! \param ulPeripheralSrc is the peripheral clock source to set.
//! \param ulDivide is the peripheral clock divide to set.
//!
//! Peripherals clock source are seted with this function.  At power-up, all 
//! Peripherals clock source are Peripherals clock source; they must be set in 
//! order to operate or respond to register reads/writes.
//!
//! The \e ulPeripheralSrc parameter must be only one of the following values:
//! \ref xSysCtl_Peripheral_Src_Clk.
//!
//! \return None.
//
//*****************************************************************************
extern void xSysCtlPeripheralClockSourceSet(unsigned long ulPeripheralSrc,
                                            unsigned long ulDivide);
											
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
//! |       STM32F1xx       |    ADC0                |MAIN PLL INT               |
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
#define xSysCtlPeripheralClockSourceSet2(ePeripheral, eSrc, ulDivide)


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
//! \addtogroup STM32F1xx_SysCtl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Config STM32F1xx SysCtl config
//! 
//! \section STM32F1xx_SysCtl_Config_section 1. Where to use this group
//! This is use to config APB1 and APB2 clock divide.
//! 
//! @{
//
//*****************************************************************************

//
//! STM32F1xx SysCtl config
//
#define SYSCTL_APB1CLOCK_DIV    2

#define SYSCTL_APB2CLOCK_DIV    1


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Peripheral_ID STM32F1xx SysCtl Peripheral ID
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
//! ETHMACRX (Enable Only)
//
#define SYSCTL_PERIPH_ETHMACRX  0x00100001

//
//! ETHMACTX (Enable Only)
//
#define SYSCTL_PERIPH_ETHMACRX  0x00008000

//
//! SDIO (Enable Only)
//
#define SYSCTL_PERIPH_SDIO      0x00000400

//
//! FSMC (Enable Only)
//
#define SYSCTL_PERIPH_FSMC      0x00000100

//
//! CRC (Enable Only)
//
#define SYSCTL_PERIPH_CRC       0x00000040

//
//! FLITF (Enable Only)
//
#define SYSCTL_PERIPH_FLITF     0x00000010

//
//! SRAM (Enable Only)
//
#define SYSCTL_PERIPH_SRAM      0x00000004

//
//! DMA2 (Enable Only)
//
#define SYSCTL_PERIPH_DMA2      0x00000002

//
//! DMA1 (Enable Only)
//
#define SYSCTL_PERIPH_DMA2      0x00000001


//
//! ETHMAC
//
#define SYSCTL_PERIPH_ETHMAC    0x00004000 

//
//! USB OTG FS
//
#define SYSCTL_PERIPH_USB       0x00001000 

//
//! TIM11
//
#define SYSCTL_PERIPH_TIM11     0x10100020

//
//! TIM10
//
#define SYSCTL_PERIPH_TIM10     0x10100010

//
//! TIM9
//
#define SYSCTL_PERIPH_TIM9      0x10100008

//
//! ADC3
//
#define SYSCTL_PERIPH_ADC3      0x10008000

//
//! USART1
//
#define SYSCTL_PERIPH_USART1    0x10004000

//
//! TIM8
//
#define SYSCTL_PERIPH_TIM8      0x10002000

//
//! SPI1
//
#define SYSCTL_PERIPH_SPI1      0x10001000

//
//! TIM1
//
#define SYSCTL_PERIPH_TIM1      0x10000800

//
//! ADC2
//
#define SYSCTL_PERIPH_ADC2      0x10000400

//
//! ADC1
//
#define SYSCTL_PERIPH_ADC1      0x10000200

//
//! I/O port G
//
#define SYSCTL_PERIPH_IOPG      0x10000100

//
//! I/O port F
//
#define SYSCTL_PERIPH_IOPF      0x10000080

//
//! I/O port E
//
#define SYSCTL_PERIPH_IOPE      0x10000040

//
//! I/O port D
//
#define SYSCTL_PERIPH_IOPD      0x10000020

//
//! I/O port C
//
#define SYSCTL_PERIPH_IOPC      0x10000010

//
//! I/O port B
//
#define SYSCTL_PERIPH_IOPB      0x10000008

//
//! I/O port A
//
#define SYSCTL_PERIPH_IOPA      0x10000004

//
//! AFIO
//
#define SYSCTL_PERIPH_AFIO      0x10000001

//
//! DAC
//
#define SYSCTL_PERIPH_DAC       0x20102000

//
//! PWR
//
#define SYSCTL_PERIPH_PWR       0x20101000

//
//! BKP
//
#define SYSCTL_PERIPH_BKP       0x20100800

//
//! CAN2
//
#define SYSCTL_PERIPH_CAN2      0x20100400

//
//! CAN1
//
#define SYSCTL_PERIPH_CAN2      0x20100200

//
//! USB
//
#define SYSCTL_PERIPH_USB       0x20100080

//
//! I2C2
//
#define SYSCTL_PERIPH_I2C2      0x20100040

//
//! I2C1
//
#define SYSCTL_PERIPH_I2C1      0x20100020

//
//! UART5
//
#define SYSCTL_PERIPH_UART5     0x20100010

//
//! UART4
//
#define SYSCTL_PERIPH_UART4     0x20100008

//
//! USART3
//
#define SYSCTL_PERIPH_USART3    0x20100004

//
//! USART2
//
#define SYSCTL_PERIPH_USART2    0x20100002

//
//! SPI3
//
#define SYSCTL_PERIPH_SPI3      0x20008000

//
//! SPI2
//
#define SYSCTL_PERIPH_SPI2      0x20004000

//
//! WWDG
//
#define SYSCTL_PERIPH_WWDG      0x20000800

//
//! TIM14
//
#define SYSCTL_PERIPH_TIM14     0x20000100

//
//! TIM13
//
#define SYSCTL_PERIPH_TIM13     0x20000080

//
//! TIM12
//
#define SYSCTL_PERIPH_TIM12     0x20000040

//
//! TIM7
//
#define SYSCTL_PERIPH_TIM7      0x20000020

//
//! TIM6
//
#define SYSCTL_PERIPH_TIM6      0x20000010

//
//! TIM5
//
#define SYSCTL_PERIPH_TIM5      0x20000008

//
//! TIM4
//
#define SYSCTL_PERIPH_TIM4      0x20000004

//
//! TIM3
//
#define SYSCTL_PERIPH_TIM3      0x20000002

//
//! TIM2
//
#define SYSCTL_PERIPH_TIM2      0x20000001
  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Ints STM32F1xx SysCtl Interrupt
//! \brief Values that show STM32F1xx SysCtl Interrupt Mask
//! @{
//
//*****************************************************************************

//
//! LSI ready interrupt Mask
//
#define SYSCTL_INT_LSI          0x01        

//
//! LSE ready interrupt Mask
//
#define SYSCTL_INT_LSE          0x02

//
//! HSI ready interrupt Mask
//
#define SYSCTL_INT_HSI          0x04

//
//! HSE ready interrupt Mask
//
#define SYSCTL_INT_HSE          0x08

//
//! PLL ready interrupt Mask
//
#define SYSCTL_INT_PLL          0x10

//
//! PLL2 ready interrupt Mask
//
#define SYSCTL_INT_PLL2         0x20

//
//! PLL3 ready interrupt Mask
//
#define SYSCTL_INT_PLL3         0x40

//
//! Clock security system interrupt Mask
//
#define SYSCTL_INT_CSS          0x80


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Event_Flag STM32F1xx SysCtl Event Flag
//! \brief Values that show STM32F1xx SysCtl Event Flag Mask
//! SysCtl Event/Error Flag, Used by IntHandle's Event Callback Function as 
//! ulMsgParam parmeter. User Callback function can user this to detect what 
//! event happened.
//! @{
//
//*****************************************************************************

//
//! LSI ready Event Flag Mask
//
#define SYSCTL_EVENT_LSI        0x01        

//
//! LSE ready Event Flag Mask
//
#define SYSCTL_EVENT_LSE        0x02

//
//! HSI ready Event Flag Mask
//
#define SYSCTL_EVENT_HSI        0x04

//
//! HSE ready Event Flag Mask
//
#define SYSCTL_EVENT_HSE        0x08

//
//! PLL ready Event Flag Mask
//
#define SYSCTL_EVENT_PLL        0x10

//
//! PLL2 ready Event Flag Mask
//
#define SYSCTL_EVENT_LSI        0x20

//
//! PLL3 ready Event Flag Mask
//
#define SYSCTL_EVENT_LSI        0x40

//
//! Clock security system Event Flag Mask
//
#define SYSCTL_EVENT_CSS        0x80


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Reset_Flag STM32F1xx SysCtl Reset Flag
//! \brief Values that show STM32F1xx SysCtl Reset Flag Mask
//! @{
//
//*****************************************************************************

//
//! Low-power reset flag Mask
//
#define SYSCTL_RESET_LPWR       0x80000000        

//
//! Window watchdog reset flag
//
#define SYSCTL_RESET_WWDG       0x40000000

//
//! Independent watchdog reset flag
//
#define SYSCTL_RESET_IWDG       0x20000000

//
//! Software reset flag
//
#define SYSCTL_RESET_SFT        0x10000000

//
//! POR/PDR reset flag
//
#define SYSCTL_RESET_POR        0x08000000

//
//! PIN reset flag
//
#define SYSCTL_RESET_PIN        0x04000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Peripheral_Src_Clk SysCtl Peripheral Source Clock
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
 
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Hclk_Src STM32F1xx SysCtl Hclk Source
//! brief Values that show STM32F1xx SysCtl Hclk Source
//! The following are values that can be passed to the
//! SysCtlHClockSourceSet()\ SysCtlHClockSet API as the
//! ulhclkSrcSel parameter.   
//! @{
//
//*****************************************************************************

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
//! \addtogroup STM32F1xx_SysCtl_Stclk_Src STM32F1xx SysCtl Stclk Source
//! \brief Values that show STM32F1xx SysCtl Stclk Source
//! The following are values that can be passed to the
//! SysCtlSysTickSourceSet()  API as the
//! ulstclkSrcSel parameter.   
//! @{
//
//*****************************************************************************

//
//! LSE oscillator clock used as RTC clock
//
#define SYSCTL_RTC_LSE          0x00080001

//
//! LSI oscillator clock used as RTC clock
//
#define SYSCTL_RTC_LSI          0x00080002

//
//! HSE oscillator clock divided by 128 used as RTC clock
//
#define SYSCTL_RTC_LSE_128      0x00080003

//
//! Microcontroller clock output System clock (SYSCLK) selected
//
#define SYSCTL_MCO_SYSCLK       0x00180004

//
//! Microcontroller clock output HSI clock selected
//
#define SYSCTL_MCO_HSI          0x00180005

//
//! Microcontroller clock output HSE clock selected
//
#define SYSCTL_MCO_HSE          0x00180006

//
//! Microcontroller clock output PLL clock divided by 2 selected
//
#define SYSCTL_MCO_PLL_2        0x00180007

//
//! Microcontroller clock output PLL2 clock selected
//
#define SYSCTL_MCO_PLL2         0x00180008

//
//! Microcontroller clock output PLL3 clock selected
//
#define SYSCTL_MCO_PLL3_2       0x00180009

//
//! XT1 external 3-25 MHz oscillator clock selected (for Ethernet)
//
#define SYSCTL_MCO_XT1          0x0018000A

//
//! Microcontroller clock output PLL3 clock selected (for Ethernet)
//
#define SYSCTL_MCO_PLL3         0x0018000B

//
//! System clock (SYSCLK) selected as I2S3 clock entry
//
#define SYSCTL_I2S3_SYSCLK      0x00120000

//
//! PLL3 VCO clock selected as I2S3 clock entry
//
#define SYSCTL_I2S3_PLL3        0x00120001

//
//! System clock (SYSCLK) selected as I2S2 clock entry
//
#define SYSCTL_I2S2_SYSCLK      0x00110000

//
//! PLL3 VCO clock selected as I2S2 clock entry
//
#define SYSCTL_I2S2_PLL3        0x00110001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Reset_Src STM32F1xx SysCtl Reset Source
//! \brief Values that show STM32F1xx SysCtl Reset Source
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
//! \addtogroup STM32F1xx_SysCtl_low_Clock STM32F1xx SysCtl low clock config
//! \brief Values that show STM32F1xx SysCtl low clock config
//! The following are values that can be passed to 
//! the SysCtlLSEConfig() and SysCtlLSIConfig() API.   
//! @{
//
//*****************************************************************************

//
//! Disable Low Speed Internal oscillator
//
#define SYSCTL_LSI_OSC_DIS      0x00000000

//
//! Enable Low Speed Internal oscillator
//
#define SYSCTL_LSI_OSC_EN       0x00000001

//
//! Disable Low Speed External oscillator
//
#define SYSCTL_LSE_OSC_DIS      0x00000000

//
//! Enable Low Speed External oscillator
//
#define SYSCTL_LSE_OSC_EN       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Clock_Config STM32F1xx SysCtl Clock Configuration
//! \brief STM32F1xx SysCtl Clock Configuration
//! The following are values that can be passed to the SysCtlClockSet() API as
//! the ulConfig parameter.
//! @{
//
//*****************************************************************************
  
//
//! Disable internal oscillator
//
#define SYSCTL_INT_OSC_DIS      0x00000001  

//
//! Disable main oscillator
//
#define SYSCTL_MAIN_OSC_DIS     0x00010000  

//
//! Disable PLL
//
#define SYSCTL_PLL_PWRDN        0x01000000  

//
//! HCLK source is main osc
//
#define SYSCTL_OSC_MAIN         0x00000001   

//
//! HCLK source is PLL
//
#define SYSCTL_OSC_PLL          0x00000002 

//
//! HCLK source is int. osc
//
#define SYSCTL_OSC_INT          0x00000000   

//
//! Oscillator Source
//
#define SYSCTL_OSCSRC_M         0x00010003 

//
//! PLL source is int. 12 MHz
//
#define SYSCTL_PLL_MAIN         0x00010000  

//
//! PLL source is int. 22 MHz
//
#define SYSCTL_PLL_INT          0x00000000  

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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_SysCtl_Exported_APIs STM32F1xx SysCtl APIs
//! \brief STM32F1xx SysCtl API Reference
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

