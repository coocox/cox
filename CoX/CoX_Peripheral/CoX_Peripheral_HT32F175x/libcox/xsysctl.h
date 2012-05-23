//*****************************************************************************
//
//! \file xsysctl.h
//! \brief Prototypes for the System Manager Driver.
//! Prototypes for the Clock Controller Driver.
//! \version V2.2.1.0
//! \date 4/26/2012
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
//! |SysCtl Peripheral ID      |       CoX      |     HT32F175x/275x       |
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
//! |xSYSCTL_PERIPH_RTC        |    Mandatory   |    xSYSCTL_PERIPH_RTC    |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_SPIn       |    Mandatory   |    xSYSCTL_PERIPH_SPI0   |
//! |                          |                |--------------------------|
//! |                          |                |    xSYSCTL_PERIPH_SPI1   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_TIMERn     |    Mandatory   |   xSYSCTL_PERIPH_TIMER0  |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_TIMER1  |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_UARTn      |    Mandatory   |   xSYSCTL_PERIPH_UART0   |
//! |                          |                |--------------------------|
//! |                          |                |   xSYSCTL_PERIPH_UART1   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_WDOG       |    Mandatory   |             Y            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_ACMPn      |    Mandatory   |   xSYSCTL_PERIPH_ACMP0   |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_ADCn       |  Non-Mandatory |   xSYSCTL_PERIPH_ADC0    |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_PERIPH_DMA        |  Non-Mandatory |             Y            |
//! +--------------------------+----------------+--------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xSYSCTL_PERIPH_ADC0     SYSCTL_PERIPH_ADC
#define xSYSCTL_PERIPH_DMA      SYSCTL_PERIPH_PDMA
#define xSYSCTL_PERIPH_GPIOA    SYSCTL_PERIPH_GPIOA
#define xSYSCTL_PERIPH_GPIOB    SYSCTL_PERIPH_GPIOB
#define xSYSCTL_PERIPH_GPIOC    SYSCTL_PERIPH_GPIOC
#define xSYSCTL_PERIPH_GPIOD    SYSCTL_PERIPH_GPIOD
#define xSYSCTL_PERIPH_GPIOE    SYSCTL_PERIPH_GPIOE
#define xSYSCTL_PERIPH_I2C0     SYSCTL_PERIPH_I2C0
#define xSYSCTL_PERIPH_I2C1     SYSCTL_PERIPH_I2C1
#define xSYSCTL_PERIPH_SPI0     SYSCTL_PERIPH_SPI0
#define xSYSCTL_PERIPH_SPI1     SYSCTL_PERIPH_SPI1
#define xSYSCTL_PERIPH_ACMP0    SYSCTL_PERIPH_OPA0
#define xSYSCTL_PERIPH_TIMER0   SYSCTL_PERIPH_TMR0
#define xSYSCTL_PERIPH_TIMER1   SYSCTL_PERIPH_TMR1
#define xSYSCTL_PERIPH_UART0    SYSCTL_PERIPH_UART0
#define xSYSCTL_PERIPH_UART1    SYSCTL_PERIPH_UART1
#define xSYSCTL_PERIPH_WDOG     SYSCTL_PERIPH_WDT
#define xSYSCTL_PERIPH_RTC      SYSCTL_PERIPH_RTC

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
//! |SysCtl Clock Set Configs  |       CoX      |     HT32F175x/275x       |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_OSC_MAIN          |    Mandatory   |             Y            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_OSC_INT           |    Mandatory   |             Y            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_OSC_INTSL         |  Non-Mandatory |             N            |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_OSC_EXTSL         |  Non-Mandatory |             N            |
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
//! |                          |                |    xSYSCTL_XTAL_16MHZ    |
//! |--------------------------|----------------|--------------------------|
//! |xSYSCTL_INT_nMHZ          |  Non-Mandatory |     xSYSCTL_INT_8MHZ     |
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

#define xSYSCTL_OSC_MAIN        (SYSCTL_PLL_MAIN | SYSCTL_OSC_PLL)
#define xSYSCTL_OSC_INT         (SYSCTL_PLL_INT | SYSCTL_OSC_PLL)
#define xSYSCTL_OSC_INTSL       0
#define xSYSCTL_OSC_EXTSL       0

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

//
//! Internal main clock is 8MHz
//
#define xSYSCTL_INT_8MHZ        0x00000000

//
//! Internal slow clock is 10KHz.
//
#define xSYSCTL_INTSL_32KHZ     0x00000000

//
//! Disable internal oscillator
//
#define xSYSCTL_INT_OSC_DIS     0x00000000

//
//! Disable main oscillator
//
#define xSYSCTL_MAIN_OSC_DIS    0x00000000

//
//! Disable PLL
//
#define xSYSCTL_PLL_PWRDN       0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSysCtl_Peripheral_Src_Clk xSysCtl Peripheral Source Clock
//! The following are values that can be passed to the
//! xSysCtlPeripheralClockSourceSet()  API as the ulPeripheralsrc parameter.  
//!
//! \section xSysCtl_Peripheral_Src_Clk_Def SysCtl Peripheral Short Name define
//! The macros of General Peripheral Source Clock always like:
//! <b> ModuleName + n + SourceClock</b>, such as xSYSCTL_WDT_EXTSL, 
//!
//! \section xSysCtl_Peripheral_Src_Clk_CoX CoX Port Details
//! \verbatim
//! +-------------------------- +----------------+--------------------------+
//! |Peripheral Source Clock Set|       CoX      |     HT32F175x/275x       |
//! |---------------------------|----------------|--------------------------|
//! |Those are all Non-Mandatory|  Non-Mandatory |             Y            |
//! | parameter,the Mandatory   |                |                          |
//! | is variable naming        |                |                          |
//! |ModuleName+n+SourceClock   |                |                          |
//! |---------------------------|----------------|--------------------------|
//! |xSYSCTL_WDT0_EXTSL         |  Non-Mandatory |             Y            |
//! |---------------------------|----------------|--------------------------|
//! |xSYSCTL_WDT0_INTSL         |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! |......                     |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! |xSYSCTL_ADC_HCLK_n         |  Non-Mandatory |             Y            |
//! |-------------------------- |----------------|--------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Watch dog clock source is external 32.768 kHz crystal clock.
//
#define xSYSCTL_WDT0_EXTSL      0x00000008

//
//! Watch dog clock source is internal 32 kHz oscillator clock
//
#define xSYSCTL_WDT0_INTSL      0x00000001

//
//! ADC clock source is HCLK
//
#define xSYSCTL_ADC0_HCLK       0x00000018

//
//! UART0 clock source is HCLK
//
#define xSYSCTL_UART0_HCLK      0x00000002

//
//! RTC clock source is LSE
//
#define xSYSCTL_RTC_EXTSL       0x00000004

//
//! RTC clock source is LSI
//
#define xSYSCTL_RTC_INTSL       0x00000000
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
//! |Peripheral Short name      |       CoX      |      HT32F175x/275x      |
//! |---------------------------|----------------|--------------------------|
//! |ADCn                       |  Non-Mandatory |           ADC0           |
//! |-------------------------- |----------------|--------------------------|
//! |UARTn                      |  Non-Mandatory |           UART0          |
//! |                           |                |           UART1          |
//! |-------------------------- |----------------|--------------------------|
//! |WDTn                       |  Non-Mandatory |           WDT0           |
//! |-------------------------- |----------------|--------------------------|
//! |TIMERn                     |  Non-Mandatory |          TIMER0          |
//! |                           |                |          TIMER1          |
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
//! |Peripheral Clock source    |       CoX      |       HT32F175x/275x     |
//! |---------------------------|----------------|--------------------------|
//! |INT                        |    Mandatory   |             Y            |
//! |---------------------------|----------------|--------------------------|
//! |HCLK                       |    Mandatory   |             Y            |
//! |---------------------------|----------------|--------------------------|
//! |HCLK_n                     |  Non-Mandatory |           HCLK_2         |
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
#define TIMER0                  TIMER0
#define TIMER1                  TIMER1
#define UART0                   UART0
#define UART1                   UART1
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
#define PLL_n                   PLL_n

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
//! +--------------------------------+----------------+--------------+
//! |xSysCtl API                     |       CoX      |HT32F175x/275x|
//! |--------------------------------|----------------|--------------|
//! |xSysCtlPeripheralReset          |    Mandatory   |       Y      |
//! |--------------------------------|----------------|--------------|
//! |xSysCtlPeripheralEnable         |    Mandatory   |       Y      |
//! |--------------------------------|----------------|--------------|
//! |xSysCtlPeripheralDisable        |    Mandatory   |       Y      |
//! |--------------------------------|----------------|--------------|
//! |xSysCtlPeripheralReset2         |    Mandatory   |       Y      |
//! |--------------------------------|----------------|--------------|
//! |xSysCtlPeripheralEnable2        |    Mandatory   |       Y      |
//! |--------------------------------|----------------|--------------|
//! |xSysCtlPeripheralDisable2       |    Mandatory   |       Y      |
//! |--------------------------------|----------------|--------------|
//! |xSysCtlPeripheralIntNumGet      |    Mandatory   |       Y      |
//! |--------------------------------|----------------|--------------|
//! |xSysCtlClockSet                 |    Mandatory   |       Y      |
//! |--------------------------------|----------------|--------------|
//! |xSysCtlClockGet                 |    Mandatory   |       Y      |
//! |--------------------------------|----------------|--------------|
//! |xSysCtlDelay                    |    Mandatory   |       Y      |
//! |--------------------------------|----------------|--------------|
//! |xSysCtlReset                    |    Mandatory   |       Y      |
//! |--------------------------------|----------------|--------------|
//! |xSysCtlSleep                    |    Mandatory   |       Y      |
//! |--------------------------------|----------------|--------------|
//! |xSysCtlPeripheralClockSourceSet |    Mandatory   |       Y      |
//! |--------------------------------|----------------|--------------|
//! |xSysCtlPeripheralClockSourceSet2|    Mandatory   |       Y      |
//! |--------------------------------|----------------|--------------|
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
//! \brief Set clock source for a peripheral and divide.
//!
//! \param ulPeripheralSrc is the peripheral clock source to set.
//!
//! Peripherals clock source are seted with this function.  At power-up, all 
//! Peripherals clock source are Peripherals clock source; they must be set in 
//! order to operate or respond to register reads/writes.
//!
//! The \e ulPeripheralSrc parameter must be only one of the following values:
//! \b xSYSCTL_ADC_HCLK, \b xSYSCTL_ADC_HCLK_2,	\b xSYSCTL_ADC_HCLK_4,
//! \b xSYSCTL_ADC_HCLK_6, \b xSYSCTL_ADC_HCLK_8, \b xSYSCTL_ADC_HCLK_16,
//! \b xSYSCTL_ADC_HCLK_32,	\b xSYSCTL_ADC_HCLK_64,	\b xSYSCTL_UART0_HCLK,
//! \b xSYSCTL_WDT0_EXTSL, \b xSYSCTL_PERIPH_WDG_S_INTSL, \b xSYSCTL_UART0_HCLK_2.
//!
//! \return None.
//
//*****************************************************************************
extern void xSysCtlPeripheralClockSourceSet(unsigned long ulPeripheralSrc,
									                          unsigned long ulDivide);

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
//! |                    |    I2C0                |                           |
//! |                    |    TIMER0              |             N             |
//! |    HT32F175x_275x  |    TIMER1              |                           | 
//! |                    |    UART0               |                           |
//! |                    |    WDT0                |                           |
//! |--------------------|------------------------|---------------------------|
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
#define xSysCtlPeripheralClockSourceSet2(ePeripheral, eSrc, ulDivide)         0

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
extern unsigned long xSysCtlClockGet(void);

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
#define xSysCtlReset()                                                        0

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
//! \addtogroup HT32F175x_275x_SysCtl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Peripheral_ID HT32F175x_275x SysCtl Peripheral ID
//! \brief Values that can be passed to the SysCtlPeripheralEnable(),
//! SysCtlPeripheralDisable(), and SysCtlPeripheralReset().
//! @{
//
//*****************************************************************************

//
//! FMC No reset
//
#define SYSCTL_PERIPH_FMC       0x00000001

//
//! SRAM No reset
//
#define SYSCTL_PERIPH_SRAM      0x00000004

//
//! DMA
//
#define SYSCTL_PERIPH_DMA       0x10010010

//
//! CSIF
//
#define SYSCTL_PERIPH_CSIF      0x10100801

//
//! I2C0
//
#define SYSCTL_PERIPH_I2C0      0x50014001

//
//! I2C1
//
#define SYSCTL_PERIPH_I2C1      0x50024002

//
//! SPI0
//
#define SYSCTL_PERIPH_SPI0      0x50104010

//
//! SPI1
//
#define SYSCTL_PERIPH_SPI1      0x50204020

//
//! UART0
//
#define SYSCTL_PERIPH_UART0     0x58014801

//
//! UART1
//
#define SYSCTL_PERIPH_UART1     0x58024802

//
//! AFIO
//
#define SYSCTL_PERIPH_AFIO      0x59404840

//
//! EXTI
//
#define SYSCTL_PERIPH_EXTI      0x59804880

//
//! GPIOA
//
#define SYSCTL_PERIPH_GPIOA     0x50015001

//
//! GPIOB
//
#define SYSCTL_PERIPH_GPIOB     0x50025002

//
//! GPIOC
//
#define SYSCTL_PERIPH_GPIOC     0x50045004

//
//! GPIOD
//
#define SYSCTL_PERIPH_GPIOD     0x50085008

//
//! GPIOE
//
#define SYSCTL_PERIPH_GPIOE     0x52045204

//
//! SCI
//
#define SYSCTL_PERIPH_SCI       0x10025801

//
//! MCTM
//
#define SYSCTL_PERIPH_MCTM      0x80108001

//
//! WDT
//
#define SYSCTL_PERIPH_WDT       0x80108010

//
//! RTC No Reset
//
#define SYSCTL_PERIPH_RTC       0x70088040

//
//! TMR0
//
#define SYSCTL_PERIPH_TMR0      0x88018801

//
//! TMR1
//
#define SYSCTL_PERIPH_TMR1      0x88028802

//! PWMA
//
#define SYSCTL_PERIPH_PWMA      0x48018801

//
//! PWMB
//
#define SYSCTL_PERIPH_PWMB      0x48028802

//
//! USB
//
#define SYSCTL_PERIPH_USB       0x88028840

//
//! BFTM0
//
#define SYSCTL_PERIPH_BFTM0     0x88029001

//
//! BFTM1
//
#define SYSCTL_PERIPH_BFTM1     0x88029002

//
//! OPA0
//
#define SYSCTL_PERIPH_OPA0      0x80409601

//
//! OPA1
//
#define SYSCTL_PERIPH_OPA1      0x80809602

//
//! ADC
//
#define SYSCTL_PERIPH_ADC       0x88019604

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Clock_Config HT32F175x_275x SysCtl Clock Configuration
//! \brief The following are values that can be passed to the SysCtlClockSet() 
//! API as the ulConfig parameter.
//! @{
//
//*****************************************************************************

#define SYSCTL_OSC_HSE         (SYSCTL_PLL_MAIN | SYSCTL_OSC_PLL)

#define SYSCTL_OSC_HSI         (SYSCTL_PLL_INT | SYSCTL_OSC_PLL)
//
//! Oscillator Source
//
#define SYSCTL_OSCSRC_M         0x00000103

//
//! System clock source is main osc
//
#define SYSCTL_OSC_MAIN         0x00000002

//
//! HCLK source is PLL
//
#define SYSCTL_OSC_PLL          0x00000001

//
//! HCLK source is int. osc
//
#define SYSCTL_OSC_INT          0x00000003

//
//! PLL source is HSE (4~12 MHz)
//
#define SYSCTL_PLL_MAIN         0x00000000

//
//! PLL source is int. 8 MHz
//
#define SYSCTL_PLL_INT          0x00000100

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
//! \addtogroup HT32F175x_275x_SysCtl_Peripheral_Src_Clk SysCtl Peripheral Clock Source
//! \brief The following are values that can be passed to the
//! SysCtlPeripheralClockSourceSet()  API as the ulPeripheralsrc parameter.
//! @{
//
//*****************************************************************************

//
//! Watch dog 00 = Clock source from external crystal clock.(32.768KHz)
//
#define SYSCTL_PERIPH_WDG_S_EXTSL                                             \
                                0x00000008

//
//! Watch dog clock source is internal 32 kHz oscillator clock
//
#define SYSCTL_PERIPH_WDG_S_INTER                                             \
                                0x00000001

//
//! ADC clock source is HCLK
//
#define SYSCTL_PERIPH_ADC_S_HCLK                                              \
                                0x00000000

//
//! ADC clock source is HCLK/2
//
#define SYSCTL_PERIPH_ADC_S_HCLK_2                                            \
                                0x00010000

//
//! ADC clock source is HCLK/4
//
#define SYSCTL_PERIPH_ADC_S_HCLK_4                                            \
                                0x00020000

//
//! ADC clock source is HCLK/6
//
#define SYSCTL_PERIPH_ADC_S_HCLK_6                                            \
                                0x00070000

//
//! ADC clock source is HCLK/8
//
#define SYSCTL_PERIPH_ADC_S_HCLK_8                                            \
                                0x00030000

//
//! ADC clock source is HCLK/16
//
#define SYSCTL_PERIPH_ADC_S_HCLK_16                                           \
                                0x00040000

//
//! ADC clock source is HCLK/32
//
#define SYSCTL_PERIPH_ADC_S_HCLK_32                                           \
                                0x00050000

//
//! ADC clock source is HCLK/64
//
#define SYSCTL_PERIPH_ADC_S_HCLK_64                                           \
                                0x00060000
//
//! UART clock source is HCLK
//
#define SYSCTL_PERIPH_UART_S_HCLK                                             \
                                0x00000002

//
//! UART clock source is HCLK/2
//
#define SYSCTL_PERIPH_UART_S_HCLK_2                                           \
                                0x00200000
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Enter_Sleep_Mode HT32F175x_275x SysCtl Enter Sleep Mode
//! \brief The following are values that can be passed to the SysCtlSleep() and
//! SysCtlDeepSleep1(), SysCtlDeepSleep2(), SysCtlPowerDown()API as the ulConfig
//! parameter. 
//! @{
//
//*****************************************************************************

//
//! Enters SLEEP mode via WFI instruction.
// 
#define SYSCTL_SLEEP_WFI_MOD    0x00000001

//
//! Enters SLEEP mode via WFE instruction.
// 
#define SYSCTL_SLEEP_WFE_MOD    0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_USB_Prescaler USB Clock Prescaler Selection
//! \brief The following are values that can be passed to USBClockSet().
//! @{
//
//*****************************************************************************

//
//! CK_USB = CK_PLL.
// 
#define SYSCTL_USB_PLL_1        0x00000000

//
//! CK_USB = CK_PLL/2.
// 
#define SYSCTL_USB_PLL_2        0x00400000

//
//! CK_USB = CK_PLL/2.
// 
#define SYSCTL_USB_PLL_3        0x00800000


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Backup_Test_Value HT32F175x_275x SysCtl Backup Test Value
//! @{
//
//*****************************************************************************

//
//! A constant value of 0x27 will be  read when the Backup Domain is ready.
// 
#define SYSCTL_BACKUP_TEST_VALUE                                              \
                                0x00000027
//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Exported_APIs HT32F175x_275x SysCtl APIs
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Set the clock of the device(HCLK).
//!
//! \param ulSysClk is the clock rate that you will set.
//! \param ulConfig is the required configuration of the device clock.
//!
//! This function configures the clock of the device.The input crystal frequency,
//! oscillator to be used, use of the PLL, and the system clock divider are all
//! configured with this function.
//!
//! The \e ulConfig parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The external crystal frequency is chosen with one of the following values:
//! \ref SYSCTL_XTAL_4MHZ, \ref SYSCTL_XTAL_5MHZ, \ref SYSCTL_XTAL_6MHZ, ...
//! \ref SYSCTL_XTAL_16MHZ.
//!
//! The oscillator source is chosen with one of the following values:
//! \ref SYSCTL_OSC_HSE, \ref SYSCTL_OSC_HSI.
//!
//! The external oscillator must be enabled in order to use an external clock
//! source.
//! <br />
//! Details please refer to \ref SysCtl_Clock_Set_Config_CoX.
//!
//! \return None.
//
//*****************************************************************************
#define     SysCtlClockSet(ulSysClk, ulConfig)                                \
            xSysCtlClockSet(ulSysClk, ulConfig)

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
#define SysCtlClockGet()                                                      \
        xSysCtlClockGet()
extern void SysCtlDelay(unsigned long ulCount);

extern void SysCtlPeripheralReset(unsigned long ulPeripheral);
extern void SysCtlPeripheralEnable(unsigned long ulPeripheral);
extern void SysCtlPeripheralDisable(unsigned long ulPeripheral);

extern void CKRDYIntHandler(void);
extern void LVDIntHandler(void);
extern void BODIntHandler(void);
extern void CKRDYIntCallbackInit(xtEventCallback pfnCallback);
extern void LVDIntCallbackInit(xtEventCallback pfnCallback);
extern void BODIntCallbackInit(xtEventCallback pfnCallback);

extern void SysCtlClockSet(unsigned long ulSysClk, unsigned long ulConfig);

extern void SysCtlSleep(unsigned long ulEnterMode);
extern void SysCtlDeepSleep1(unsigned long ulEnterMode);
extern void SysCtlDeepSleep2(unsigned long ulEnterMode);
extern void SysCtlPowerDown(unsigned long ulEnterMode);
extern unsigned long SysCtlLowerPowerModeGet(void);

extern unsigned long SysCtlResetSrcGet(void);
extern void SysCtlResetSrcClear(unsigned long ulSrc);

extern void SysCtlPeripheralClockSourceSet(unsigned long ulPeripheralSrc);
extern void SysCtlClkOututSrcSet(unsigned long ulClkOutSrc);

extern void SysCtlBODEnable(xtBoolean bEnable);
extern void SysCtlLVDEnable(xtBoolean bEnable);
extern void SysCtlDMOSEnable(xtBoolean bEnable);
extern void SysCtlLVDIntEnable(xtBoolean bEnable);
extern xtBoolean SysCtlLVDStateGet(void);
extern xtBoolean SysCtlBODStateGet(void);
extern xtBoolean SysCtlDMOSStateGet(void);
extern void SysCtlBODFunctionSelect(unsigned long ulBodFunction);
extern void SysCtlLVDVoltSelect(unsigned long ulVoltage);
extern void SysCtlWakeUpPinEnable(xtBoolean bEnable);
extern void SysCtlWakeUpIntEnable(xtBoolean bEnable);
extern void SysCtlBackupDomainReset(void);
extern xtBoolean SysCtlBackupReadyStateGet(void);
extern void SysCtlBackupRegWrite(unsigned long ulIndex, unsigned long ulData);
extern unsigned long SysCtlBackupRegRead(unsigned long ulIndex);

extern void SysCtlHSIReadyCounterBitLengthSet(unsigned long ulBitLength);

extern void SysCtlClockReadyIntEnable(unsigned long ulIntFlags);
extern xtBoolean SysCtlClockReadyIntGet(unsigned long ulIntFlags);

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

