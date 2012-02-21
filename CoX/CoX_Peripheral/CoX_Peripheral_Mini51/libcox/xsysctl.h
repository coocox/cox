//*****************************************************************************
//
//! \file xsysctl.h
//! \brief Prototypes for the System Manager Driver.
//! Prototypes for the Clock Controller Driver.
//! \version V2.1.1.0
//! \date 2/1/2012
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
//! 
//! \section xSysCtl_Peripheral_ID 1. Where to use this group
//! Values that can be passed to the xSysCtlPeripheralEnable(),
//! xSysCtlPeripheralDisable(), and xSysCtlPeripheralReset() APIs as the
//! ulPeripheral parameter.  
//! 
//! \section xSysCtl_Peripheral_ID_CoX 2.CoX Port Details
//! \verbatim
//! +--------------------------+----------------+--------------------------+
//! |SysCtl Peripheral ID      |       CoX      |          MINI51          |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_ACMPn      |  Non-Mandatory |   xSYSCTL_PERIPH_ACMP0   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_ADCn       |    Mandatory   |    xSYSCTL_PERIPH_ADC0   | 
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
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_GPIOF   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_I2Cn       |  Non-Mandatory |    xSYSCTL_PERIPH_I2C0   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_PWMn       |  Non-Mandatory |    xSYSCTL_PERIPH_PWM0   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_PWM1   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_PWM2   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_PWM3   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_PWM4   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_PWM5   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_RTC        |    Mandatory   |             N            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_SPIn       |    Mandatory   |    xSYSCTL_PERIPH_SPI0   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_TIMERn     |    Mandatory   |   xSYSCTL_PERIPH_TIMER0  |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_TIMER1  |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_UARTn      |    Mandatory   |   xSYSCTL_PERIPH_UART0   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_WDOG       |    Mandatory   |             Y            |
//! +--------------------------+----------------+--------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xSYSCTL_PERIPH_ACMP0    SYSCTL_PERIPH_ACMP
#define xSYSCTL_PERIPH_ADC0     SYSCTL_PERIPH_ADC
#define xSYSCTL_PERIPH_GPIOA    SYSCTL_PERIPH_GPIO
#define xSYSCTL_PERIPH_GPIOB    SYSCTL_PERIPH_GPIO
#define xSYSCTL_PERIPH_GPIOC    SYSCTL_PERIPH_GPIO
#define xSYSCTL_PERIPH_GPIOD    SYSCTL_PERIPH_GPIO
#define xSYSCTL_PERIPH_GPIOE    SYSCTL_PERIPH_GPIO
#define xSYSCTL_PERIPH_GPIOF    SYSCTL_PERIPH_GPIO
#define xSYSCTL_PERIPH_I2C0     SYSCTL_PERIPH_I2C0
#define xSYSCTL_PERIPH_PWMA     0x40105070
#define xSYSCTL_PERIPH_SPI0     SYSCTL_PERIPH_SPI0
#define xSYSCTL_PERIPH_TIMER0   SYSCTL_PERIPH_TMR0
#define xSYSCTL_PERIPH_TIMER1   SYSCTL_PERIPH_TMR1
#define xSYSCTL_PERIPH_UART0    SYSCTL_PERIPH_UART0
#define xSYSCTL_PERIPH_WDOG     SYSCTL_PERIPH_WDT

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSysCtl_Clock_Set_Config xSysCtl Clock Set Configuration
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
//! |SysCtl Clock Set Configs  |       CoX      |          MINI51          |
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
//! +--------------------------+----------------+--------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xSYSCTL_OSC_MAIN        SYSCTL_OSC_MAIN
#define xSYSCTL_OSC_INT         SYSCTL_OSC_INT
#define xSYSCTL_OSC_INTSL       SYSCTL_OSC_INTSL
#define xSYSCTL_OSC_EXTSL       SYSCTL_OSC_EXTSL

//
//! XTAL Select
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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSysCtl_Peripheral_Src_Clk xSysCtl Peripheral Source Clock
//! The following are values that can be passed to the
//! xSysCtlPeripheralClockSourceSet()  API as the
//! ulPeripheralsrc parameter.  
//!
//! \section xSysCtl_Peripheral_Src_Clk_Def SysCtl Peripheral Short Name define
//! The macros of General Peripheral Source Clock always like:
//! <b> ModuleName + n + SourceClock</b>, such as xSYSCTL_WDT_EXTSL, 
//!
//! \section xSysCtl_Peripheral_Src_Clk_CoX CoX Port Details
//! \verbatim
//! +-------------------------- +----------------+--------------------------+
//! |Peripheral Source Clock Set|       CoX      |            MINI51        |
//! |---------------------------|----------------|--------------------------|
//! |Those are all Non-Mandatory|  Non-Mandatory |             Y            |
//! | parameter,the Mandatory   |                |                          |
//! | is variable naming        |                |                          |
//! |ModuleName+n+SourceClock   |                |                          |
//! |---------------------------|----------------|--------------------------|
//! |xSYSCTL_WDT0_EXTSL         |  Non-Mandatory |             Y            |
//! |---------------------------|----------------|--------------------------|
//! |xSYSCTL_WDT0_HCLK_2048     |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! |xSYSCTL_WDT0_INTSL         |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! |......                     |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! |xSYSCTL_PWMA_INT           |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Watch Clock source from external crystal clock 12 MHz clock
//
#define xSYSCTL_WDT0_EXTSL      0x00000300 

//
//! Watch Clock source from external crystal clock 32 KHz clock
//  
#define xSYSCTL_WDT0_MAIN       0x00000300
  
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
//! ADC clock source is external 32 KHz crystal clock
//
#define xSYSCTL_ADC0_EXTSL      0x01021000
  
//
//! ADC clock source is HCLK
//
#define xSYSCTL_ADC0_HCLK       0x01021002  
                                
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
#define xSYSCTL_TIMER0_EXTSL    0x00080700 
  
//
//!  Timer0 clock source is internal 10 KHz oscillator clock
//  
#define xSYSCTL_TIMER0_INTSL    0x00080701 
                                
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
#define xSYSCTL_TIMER0_INT      0x00080707  
                                
//
//! Timer1 clock source is external 12 MHz crystal clock
//
#define xSYSCTL_TIMER1_MAIN     0x000C0700

//
//! Timer1 clock source is external 32 KHz crystal clock
//
#define xSYSCTL_TIMER1_EXTSL    0x000C0700  
  
//
//! Timer1 clock source is internal 10 KHz oscillator clock
//
#define xSYSCTL_TIMER1_INTSL    0x000C0701  
                                
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
//! UART clock source is external 12 MHz crystal clock
//
#define xSYSCTL_UART0_MAIN      0x01180800  
  
//
//! UART clock source is external 32 KHz crystal clock
//
#define xSYSCTL_UART0_EXTSL     0x01180800 
  
//
//! UART clock source is internal 22 MHz oscillator clock
//
#define xSYSCTL_UART0_INT       0x01180803  
                                
//
//! PWMA clock source is HCLK (Both PWM01, 23, 45)
//
#define xSYSCTL_PWMA_HCLK       0x00000000
  
//
//! frequency divide source is external 12 MHz crystal clock
//
#define xSYSCTL_FRQDIV_MAIN     0x10020300
 
//
//! frequency divide source is external 32 KHz crystal clock
//
#define xSYSCTL_FRQDIV_EXTSL    0x10020300
  
//
//! frequency divide source is HCLK
//
#define xSYSCTL_FRQDIV_HCLK     0x10020302
                                
//
//! frequency divide source is internal 22 MHz oscillator clock
//
#define xSYSCTL_FRQDIV_INT      0x10020303

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSysCtl_Peripheral_Short xSysCtl Peripheral Short Name
//! The following are values that can be passed to the
//! xSysCtlPeripheralClockSourceSet2()  API as the
//! ulPeripheral parameter.
//!
//! \section xSysCtl_Peripheral_Short_Def SysCtl Peripheral Short Name define
//! The macros of General Peripheral Short Name always like:
//! <b> ModuleName + n </b>, such as SPI0, UART0.
//!
//! \section xSysCtl_Peripheral_Short_CoX CoX Port Details
//! \verbatim
//! +-------------------------- +----------------+--------------------------+
//! |Peripheral Short name      |       CoX      |          MINI51          |
//! |---------------------------|----------------|--------------------------|
//! |PWMn                       |  Non-Mandatory |           PWMA           |
//! |-------------------------- |----------------|--------------------------|
//! |UARTn                      |  Non-Mandatory |           UART0          |
//! |-------------------------- |----------------|--------------------------|
//! |WDTn                       |  Non-Mandatory |           WDT0           |
//! |-------------------------- |----------------|--------------------------|
//! |TIMERn                     |  Non-Mandatory |          TIMER0          |
//! |                           |                |          TIMER1          |
//! |-------------------------- |----------------|--------------------------|
//! |I2Cn                       |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! |SPIn                       |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! |RTC                        |  Non-Mandatory |             N            |
//! |-------------------------- |----------------|--------------------------|
//! |GPIO                       |  Non-Mandatory |             N            |
//! |-------------------------- |----------------|--------------------------|
//!
//! +-------------------------- +----------------+--------------------------+
//! |Peripheral Clock source    |       CoX      |          MINI51          |
//! |---------------------------|----------------|--------------------------|
//! |INT                        |    Mandatory   |             Y            |
//! |---------------------------|----------------|--------------------------|
//! |HCLK                       |    Mandatory   |             Y            |
//! |---------------------------|----------------|--------------------------|
//! |HCLK_n                     |  Non-Mandatory |         HCLK_2048        |
//! |---------------------------|----------------|--------------------------|
//! |EXTSL                      |  Non-Mandatory |             N            |
//! |---------------------------|----------------|--------------------------|
//! |INTSL                      |    Mandatory   |             Y            |
//! |---------------------------|----------------|--------------------------|
//! |MAIN                       |    Mandatory   |             Y            |
//! |---------------------------|----------------|--------------------------|
//! |EXTTRG                     |  Non-Mandatory |             Y            |
//! |---------------------------|----------------|--------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************
#define PWMA                    PWMA
#define TIMER0                  TIMER0
#define TIMER1                  TIMER1
#define UART0                   UART0
#define WDT0                    WDT0
#define I2C0                    I2C0  
#define SPI0                    SPIO
  
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
//!
//! \section xSysCtl_Exported_APIs_Port CoX Port Details
//! \verbatim
//! +--------------------------------+----------------+--------+
//! |xSysCtl API                     |       CoX      | MINI51 |
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
//! |xSysCtlPeripheralIntNumGet      |    Mandatory   |    Y   |
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
//! \brief Perform a software reset of a peripheral.
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
//! \brief Enable a peripheral.
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
extern unsigned long xSysCtlPeripheralIntNumGet(unsigned long ulPeripheralBase);

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
//! |                    |should be:TIMERn or     |INTSL  MAIN  PLL           |
//! |                    |    UARTn.              |PLL_n  EXTTRG              |
//! |                    |n indicate the pin      |n indicate the pin         |
//! |                    |number such as          |number such as             |
//! |                    |0 1 2 3 ....            |0 1 2 3 ....               |
//! |--------------------|------------------------|---------------------------|
//! |                    |    PWMA                |HCLK                       |
//! |                    |    TIMER0              |INT EXTTRG HCLK EXTSL MAIN |
//! |                    |    TIMER1              |INT EXTTRG HCLK EXTSL MAIN |
//! |                    |    UART0               |INT MAIN                   |
//! |                    |    WDT0                |INTSL HCLK_2048 EXTSL MAIN |
//! |                    |    ADC0                |EXTSL MAIN HCLK INT        |
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
//! This function can get the clock rate of the processor clock.  This is
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
//! until the processor returns to run mode.
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
//! \addtogroup MINI51_SysCtl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Peripheral_ID MINI51 SysCtl Peripheral ID
//! \brief Values that can be passed to the SysCtlPeripheralEnable(),
//! SysCtlPeripheralDisable(), and SysCtlPeripheralReset().
//! @{
//
//*****************************************************************************

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
//! TMR0
//
#define SYSCTL_PERIPH_TMR0      0x70044004  

//
//! TMR1
//
#define SYSCTL_PERIPH_TMR1      0x70084008  

//
//! FDIV No reset
//
#define SYSCTL_PERIPH_FDIV      0x00004040 

//
//! I2C0
//
#define SYSCTL_PERIPH_I2C0      0x68024801  

//
//! SPI0
//
#define SYSCTL_PERIPH_SPI0      0x68104810 

//
//! UART0
//
#define SYSCTL_PERIPH_UART0     0x40015001

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
#define SYSCTL_PERIPH_PWM45     0x40105040

//
//! ADC
//
#define SYSCTL_PERIPH_ADC       0x48105810

//
//! ACMP
//
#define SYSCTL_PERIPH_ACMP      0x40405840

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Peripheral_Src_Clk SysCtl Peripheral Clock Source
//! \brief The following are values that can be passed to the
//! SysCtlPeripheralClockSourceSet()  API as the ulPeripheralsrc parameter.  
//! @{
//
//*****************************************************************************

//
//! Watch dog Clock source from external crystal clock.(32KHz)
//
#define SYSCTL_PERIPH_WDG_EXT32K                                              \
                                0x00000300 

//
//! Watch dog Clock source from external crystal clock.(12MHz)
//
#define SYSCTL_PERIPH_WDG_EXT12M                                              \
                                0x00000300

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
//! ADC clock source is external 32 KHz crystal clock
//
#define SYSCTL_PERIPH_ADC_S_EXT32K                                            \
                                0x00020300  

//
//! ADC clock source is HCLK
//
#define SYSCTL_PERIPH_ADC_S_HCLK                                              \
                                0x00020302 
                                
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
                                0x00080700  

//
//! Timer0 clock source is internal 10 KHz crystal clock
//
#define SYSCTL_PERIPH_TMR0_S_INTSL                                           \
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
                                0x00080707  
                                
//
//! Timer1 clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_TMR1_S_EXT12M                                           \
                                0x000C0700 

//
//! Timer1 clock source is external 32 KHz crystal clock
//
#define SYSCTL_PERIPH_TMR1_S_EXT32K                                            \
                                0x000C0700 

//
//! Timer1 clock source is internal 10 KHz crystal clock
//
#define SYSCTL_PERIPH_TMR1_S_INTSL                                            \
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
//! UART clock source is external 12 MHz crystal clock
//
#define SYSCTL_PERIPH_UART_S_EXT12M                                           \
                                0x00180300  

//
//! UART clock source is external 32 KHz crystal clock
//
#define SYSCTL_PERIPH_UART_S_EXT32K                                           \
                                0x00180300
                                
//
//! UART clock source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_UART_S_INT22M                                           \
                                0x00180303                               
                                
//
//! PWM0 and PWM1 clock source is HCLK
//
#define SYSCTL_PERIPH_PWM01_S_HCLK                                            \
                                0x001C0302   
                                                           
//
//! PWM2 and PWM3 clock source is HCLK
//
#define SYSCTL_PERIPH_PWM23_S_HCLK                                            \
                                0x001E0302  

//
//! frequency divide source is external 12 MHz oscillator clock
//
#define SYSCTL_PERIPH_FRQDIV_S_EXT12M                                           \
                                0x10020300

//
//! frequency divide source is external 32 kHz oscillator clock
//
#define SYSCTL_PERIPH_FRQDIV_S_EXT32K                                           \
                                0x10020300

//
//! frequency divide source is HCLK
//
#define SYSCTL_PERIPH_FRQDIV_S_HCLK                                           \
                                0x10020302

//
//! frequency divide source is internal 22 MHz oscillator clock
//
#define SYSCTL_PERIPH_FRQDIV_S_INT22M                                           \
                                0x10020303
                                
//
//! PWM4 and PWM5 clock source is HCLK
//
#define SYSCTL_PERIPH_PWM45_S_HCLK                                            \
                                0x10040302       
                             
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Hclk_Src MINI51 SysCtl Hclk Source
//! \brief The following are values that can be passed to the
//! SysCtlHClockSourceSet()\ SysCtlHClockSet API as the ulhclkSrcSel parameter.   
//! @{
//
//*****************************************************************************

//
//! Hclk source is external 12 MHz or 32 KHz crystal clock
//
#define SYSCTL_HLCK_S_EXT       0x00000000

//
//! Hclk source is internal 10 kHz oscillator clock
//
#define SYSCTL_HLCK_S_INT10K    0x00000003  

//
//! Hclk source is internal 22 MHz oscillator clock
//
#define SYSCTL_HLCK_S_INT22M    0x00000007  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Stclk_Src MINI51 SysCtl Stick Source
//! \brief The following are values that can be passed to the
//! SysCtlSysTickSourceSet()  API as the ulstclkSrcSel parameter.   
//! @{
//
//*****************************************************************************

//
//! Systick Clock source is external 12 MHz or 32 KHz crystal clock
//
#define SYSCTL_STCLK_S_EXT12M   0x00000000

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
//! \addtogroup MINI51_SysCtl_Reset_Src MINI51 SysCtl Reset Source
//! \brief The following are values that can be returned in the bit mask by the 
//! SysCtlResetSrcGet() API.   
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
//! \addtogroup MINI51_SysCtl_Bod_level MINI51 SysCt Bod level
//! \brief The following are values that can be passed to the
//! SysCtlBODVoltSelect()  API as the ulVoltage parameter.  
//! @{
//
//*****************************************************************************

//
//! Threshold Voltage 2.7V
//
#define SYSCTL_BOD_2_7          0x00000002  

//
//! Threshold Voltage 3.8V
//
#define SYSCTL_BOD_3_8          0x00000004  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Peripheral_ClkDiv MINI51 SysCtl Peripheral ClkDiv
//! \brief The following are values that can be passed to the
//! SysCtlIPClockDividerSet()  API as the ulConfig parameter. 
//! @{
//
//*****************************************************************************

//
//! HCLK clock divide number mask
// 
#define SYSCTL_PERIPH_HCLK_D    0x00000000

//
//! UART clock divide number mask
//
#define SYSCTL_PERIPH_UART_D    0x00080800

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
//! \addtogroup MINI51_SysCtl_Clock_Config MINI51 SysCtl Clock Configuration
//! \brief The following are values that can be passed to the SysCtlClockSet() 
//! API as the ulConfig parameter.
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
//! HCLK source is main osc
//
#define SYSCTL_OSC_MAIN         0x00000000  

//
//! HCLK source is ext. 32 KHz
//
#define SYSCTL_OSC_EXTSL        0x00000010  

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
//! External main clock crystal mask.
//
#define SYSCTL_XTAL_MASK        0x0000FF00  

//
//! External main clock crystal is 12MHz.
//
#define SYSCTL_XTAL_12MHZ       0x00000C00 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Trim_Loop MINI51 SysCtl Trim Loops Select
//! \brief The following are values that can be passed to the SysCtlHFIRCTrimEnable() 
//! API as the ulTrimLoop parameter.
//! @{
//
//*****************************************************************************

//
//! Trim value calculation is based on average difference in 4 32.768 KHz clock, 
//! trim retry count limitation is 64.
//
#define SYSCTL_TRIM_L00P_4      0x00000000

//
//! Trim value calculation is based on average difference in 8 32.768 KHz clock, 
//! trim retry count limitation is 128.
//
#define SYSCTL_TRIM_L00P_8      0x00000010

//
//! Trim value calculation is based on average difference in 16 32.768 KHz clock, 
//! trim retry count limitation is 256.
//
#define SYSCTL_TRIM_L00P_16     0x00000020

//
//! Trim value calculation is based on average difference in 32 32.768 KHz clock, 
//! trim retry count limitation is 512.
//
#define SYSCTL_TRIM_L00P_32    0x00000030

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Trim_Int MINI51 SysCtl Trim Int Enable
//! \brief The following are values that can be passed to the SysCtlHFIRCTrimIntEnable() 
//! API as the ulTrimInt parameter.
//! @{
//
//*****************************************************************************

//
//! Trim Failure Interrupt Enable
//
#define SYSCTL_TRIM_32K_FAIL_IEN                                              \
                                0x00000001

//
//! 32.768 KHz Clock Error Interrupt Enable
//
#define SYSCTL_TRIM_32K_ERR_IEN 0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Exported_APIs MINI51 SysCtl APIs
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
extern xtBoolean SysCtlBODStateGet(void);
extern void SysCtlBODRstEnable(xtBoolean bEnable);

extern void SysCtlIPClockDividerSet(unsigned long ulConfig);
extern void SysCtlFreqDividerOutputEnable(xtBoolean bEnable, unsigned char u8Divider);
extern void SysCtlPWRWUIntEnable(xtBoolean bEnable, xtBoolean bDelay);
extern void SysCtlPowerDownEnable(xtBoolean bEnable);
extern unsigned long SysCtlHClockGet(void);
extern void SysCtlHClockSet(unsigned long ulConfig);

extern void SysCtlHFIRCTrimEnable(xtBoolean bEnable, unsigned char ulTrimLoop);
extern void SysCtlHFIRCTrimIntEnable(xtBoolean bEnable, unsigned char ulTrimInt);
extern unsigned long SysCtlHFIRCTrimIntStatusGet(void);

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

