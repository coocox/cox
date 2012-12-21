//*****************************************************************************
//
//! \file xhw_sysctl.h
//! \brief Macros used when accessing the system control hardware.
//! \version V2.2.1.0
//! \date 8/1/2012
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
//! \addtogroup KLx_SysCtl_Register KLx SysCtl Register
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
//! \addtogroup KLx_SysCtl_Register_Offsets KLx SysCtl Register Offsets(Map)
//! \brief Defines for the system control register addresses.
//! @{
//
//*****************************************************************************

//
//! OSC Control Register
//
#define OSC0_CR                 0x40065000  

//
//! System Options Register 1
//
#define SIM_SOPT1               0x40047000  

//
//! SOPT1 Configuration Register
//
#define SIM_SOPT1CFG            0x40047004  

//
//! System Options Register 2
//
#define SIM_SOPT2               0x40048004  

//
//! System Options Register 4
//
#define SIM_SOPT4               0x4004800C  

//
//! System Options Register 5
//
#define SIM_SOPT5               0x40048010  

//
//! System Options Register 7
//
#define SIM_SOPT7               0x40048018  

//
//! System Device Identification Register
//
#define SIM_SDID                0x40048024  

//
//! System Clock Gating Control Register 4
//
#define SIM_SCGC4               0x40048034

//
//! System Clock Gating Control Register 5
//
#define SIM_SCGC5               0x40048038

//
//! System Clock Gating Control Register 6
//
#define SIM_SCGC6               0x4004803C

//
//! System Clock Gating Control Register 7
//
#define SIM_SCGC7               0x40048040    

//
//! System Clock Divider Register 1
//
#define SIM_CLKDIV1             0x40048044  

//
//! Flash Configuration Register 1
//
#define SIM_FCFG1               0x4004804C  

//
//! Flash Configuration Register 2
//
#define SIM_FCFG2               0x40048050  

//
//! Unique Identification Register Mid-High
//
#define SIM_UIDMH               0x40048058  
                                            
//
//! Unique Identification Register Mid Low
//
#define SIM_UIDML               0x4004805C  

//
//! Unique Identification Register Low
//
#define SIM_UIDL                0x40048060  

//
//! COP Control Register
//
#define SIM_COPC                0x40048100  

//
//! Service COP Register
//
#define SIM_SRVCOP              0x40048104  

//
//! MCG Control 1 Register
//
#define MCG_C1                  0x40064000  

//
//! MCG Control 2 Register
//
#define MCG_C2                  0x40064001 

//
//! MCG Control 3 Register
//
#define MCG_C3                  0x40064002 

//
//! MCG Control 4 Register
//
#define MCG_C4                  0x40064003 

//
//! MCG Control 5 Register
//
#define MCG_C5                  0x40064004

//
//! MCG Control 6 Register
//
#define MCG_C6                  0x40064005

//
//! MCG Status Register
//
#define MCG_S                   0x40064006

//
//! MCG Status and Control Register
//
#define MCG_SC                  0x40064008 

//
//! MCG Auto Trim Compare Value High Register
//
#define MCG_ATCVH               0x4006400A  

//
//! MCG Auto Trim Compare Value Low Register
//
#define MCG_ATCVL               0x4006400B  

//
//! MCG Control 7 Register
//
#define MCG_C7                  0x4006400C 

//
//! MCG Control 8 Register
//
#define MCG_C8                  0x4006400D 

//
//! MCG Control 9 Register
//
#define MCG_C9                  0x4006400E

//
//! MCG Control 10 Register
//
#define MCG_C10                 0x4006400F

//
//! Low Voltage Detect Status And Control 1 register
//
#define PMC_LVDSC1              0x4007D000 

//
//! Low Voltage Detect Status And Control 2 register
//
#define PMC_LVDSC2              0x4007D001

//
//! Regulator Status And Control register
//
#define PMC_REGSC               0x4007D002

//
//! LLWU Pin Enable 1 register
//
#define LLWU_PE1                0x4007C000

//
//! LLWU Pin Enable 2 register
//
#define LLWU_PE2                0x4007C001

//
//! LLWU Pin Enable 3 register
//
#define LLWU_PE3                0x4007C002

//
//! LLWU Pin Enable 4 register
//
#define LLWU_PE4                0x4007C003

//
//! LLWU Module Enable register
//
#define LLWU_ME                 0x4007C004

//
//! LLWU Flag 1 register
//
#define LLWU_F1                 0x4007C005

//
//! LLWU Flag 2 register
//
#define LLWU_F2                 0x4007C006

//
//! LLWU Flag register
//
#define LLWU_F3                 0x4007C007

//
//! LLWU Pin Filter 1 register
//
#define LLWU_FILT1              0x4007C008

//
//! LLWU Pin Filter 2 register 
//
#define LLWU_FILT2              0x4007C009

//
//! System Reset Status Register 0  
//
#define RCM_SRS0                0x4007F000

//
//! System Reset Status Register 1  
//
#define RCM_SRS1                0x4007F001

//
//! Reset Pin Filter Control register  
//
#define RCM_RPFC                0x4007F004

//
//! Reset Pin Filter Width register  
//
#define RCM_RPFW                0x4007F005

//
//! Power Mode Protection register  
//
#define SMC_PMPROT              0x4007E000

//
//! Power Mode Control register  
//
#define SMC_PMCTRL              0x4007E001

//
//! Stop Control Register  
//
#define SMC_STOPCTRL            0x4007E002

//
//! Power Mode Status register  
//
#define SMC_PMSTAT              0x4007E003

#define SCB_SCR                 0xE000E000
#define SCB_SCR_SLEEPDEEP       0x00000004
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_OSC0_CR SysCtl Register OSC0_CR(SysCtl_OSC0_CR)
//! \brief Defines for the bit fields in the OSC0_CR register.
//! @{
//
//*****************************************************************************

//
//! Add 16 pF capacitor to the oscillator load
//
#define OSC0_CR_SC16P           0x01 

//
//! Add 8 pF capacitor to the oscillator load
//
#define OSC0_CR_SC8P            0x02

//
//! Add 4 pF capacitor to the oscillator load
//
#define OSC0_CR_SC4P            0x04

//
//! Add 2 pF capacitor to the oscillator load
//
#define OSC0_CR_SC2P            0x08

//
//! External Reference Stop Enable
//
#define OSC0_CR_EREFSTEN        0x20

//
//! External Reference Enable
//
#define OSC0_CR_ERCLKEN         0x80

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_SOPT1 SysCtl SIM SIM_SOPT1 Register(SysCtl_SIM_SOPT1)
//! \brief Defines for the bit fields in the SIM_SOPT1 register.
//! @{
//
//*****************************************************************************

//
//! 32K oscillator clock select Mask
//
#define SIM_SOPT1_OSC32KSEL_M   0x000C0000  

//
//! 32K oscillator clock select Shift
//
#define SIM_SOPT1_OSC32KSEL_S   18  

//
//! 32K oscillator clock is System oscillator (OSC32KCLK)
//
#define SIM_SOPT1_OSC32KSEL_OSC32KCLK 0x00000000 

//
//! 32K oscillator clock is RTC_CLKIN
//
#define SIM_SOPT1_OSC32KSEL_RTC_CLKIN 0x00080000    

//
//! 32K oscillator clock is LPO 1kHz
//
#define SIM_SOPT1_OSC32KSEL_LPO 0x000C0000 

//
//! USB voltage regulator in standby mode during VLPR and VLPW modes
//
#define SIM_SOPT1_USBVSTBY      0x20000000 

//
//! USB voltage regulator in standby mode during Stop, VLPS, LLS and VLLS modes.
//
#define SIM_SOPT1_USBSSTBY      0x40000000   

//
//! USB voltage regulator enable.
//
#define SIM_SOPT1_USBREGEN      0x80000000    

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_SOPT1CFG SysCtl SIM SIM_SOPT1CFG Register(SysCtl_SIM_SOPT1CFG)
//! \brief Defines for the bit fields in the SIM_SOPT1CFG register.
//! @{
//
//*****************************************************************************

//
//! USB voltage regulator enable write enable
//
#define SIM_SOPT1CFG_URWE       0x01000000  

//
//! USB voltage regulator VLP standby write enable
//
#define SIM_SOPT1CFG_UVSWE      0x02000000    

//
//! USB voltage regulator stop standby write enable
//
#define SIM_SOPT1CFG_USSWE      0x04000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_SOPT4 SysCtl SIM SIM_SOPT2 Register(SysCtl_SIM_SOPT2)
//! \brief Defines for the bit fields in the SIM_SOPT2 register.
//! @{
//
//*****************************************************************************

//
//! RTC clock out select is OSCERCLK.
//
#define SIM_SOPT2_RTCCLKOUTSEL  0x00000010  

//
//! Selects the clock to output on the CLKOUT pin Mask
//
#define SIM_SOPT2_CLKOUTSEL_M   0x000000E0    

//
//! Selects the clock to output on the CLKOUT pin Shift
//
#define SIM_SOPT2_CLKOUTSEL_S   5

//
//! Selects the clock to output on the CLKOUT pin is Bus clock
//
#define SIM_SOPT2_CLKOUTSEL_BUS 0x00000040 

//
//! Selects the clock to output on the CLKOUT pin is LPO clock (1 kHz)
//
#define SIM_SOPT2_CLKOUTSEL_LPO 0x00000060

//
//! Selects the clock to output on the CLKOUT pin is MCGIRCLK
//
#define SIM_SOPT2_CLKOUTSEL_MCGIRCLK                                         \
                                0x00000080 

//
//! Selects the clock to output on the CLKOUT pin is OSCERCLK
//
#define SIM_SOPT2_CLKOUTSEL_OSCERCLK                                         \
                                0x000000C0 

//
//! PLL/FLL clock is MCGPLLCLK clock with fixed divide by two
//
#define SIM_SOPT2_PLLFLLSEL     0x00010000 

//
//! USB clock source is MCGPLLCLK/2 or MCGFLLCLK clock
//
#define SIM_SOPT2_USBSRC        0x00040000 
                                                   
//
//! TPM clock source select Mask
//
#define SIM_SOPT2_TPMSRC_M      0x03000000    

//
//! TPM clock source select Shift
//
#define SIM_SOPT2_TPMSRC_S      24

//
//! TPM clock source disabled
//
#define SIM_SOPT2_TPMSRC_DIS    0x00000000

//
//! TPM clock source is MCGFLLCLK clock or MCGPLLCLK/2
//
#define SIM_SOPT2_TPMSRC_MCGXLL 0x01000000

//
//! TPM clock source is OSCERCLK clock
//
#define SIM_SOPT2_TPMSRC_OSCERCLK                                             \
                                0x02000000

//
//! TPM clock source is MCGIRCLK clock
//
#define SIM_SOPT2_TPMSRC_MCGIRCLK                                             \
                                0x03000000

//
//! UART0 clock source select Mask
//
#define SIM_SOPT2_UART0SRC_M    0x0C000000    

//
//! UART0 clock source select Shift
//
#define SIM_SOPT2_UART0SRC_S    26

//
//! UART0 clock source disabled
//
#define SIM_SOPT2_UART0SRC_DIS  0x00000000

//
//! UART0 clock source is MCGFLLCLK clock or MCGPLLCLK/2
//
#define SIM_SOPT2_UART0SRC_MCGXLL                                             \
                                0x04000000

//
//! UART0 clock source is OSCERCLK clock
//
#define SIM_SOPT2_UART0SRC_OSCERCLK                                           \
                                0x08000000

//
//! UART0 clock source is MCGIRCLK clock
//
#define SIM_SOPT2_UART0SRC_MCGIRCLK                                           \
                                0x0C000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_SOPT4 SysCtl SIM SIM_SOPT1 Register(SysCtl_SIM_SOPT4)
//! \brief Defines for the bit fields in the SIM_SOPT4 register.
//! @{
//
//*****************************************************************************

//
//! TPM1 channel 0 input capture source select
//! (0:TPM1_CH0 signal, 1:CMP0 output)
//
#define SIM_SOPT4_TPM1CH0SRC    0x00040000

//
//! TPM2 channel 0 input capture source select
//! (0:TPM2_CH0 signal, 1:CMP0 output)
//
#define SIM_SOPT4_TPM2CH0SRC    0x00080000  

//
//! TPM0 External Clock Pin Select
//! (0:TPM0 external clock driven by TPM_CLKIN0 pin)
//! (1:TPM0 external clock driven by TPM_CLKIN1 pin)
//
#define SIM_SOPT4_TPM0CLKSEL    0x01000000

//
//! TPM1 External Clock Pin Select
//! (0:TPM1 external clock driven by TPM_CLKIN0 pin)
//! (1:TPM1 external clock driven by TPM_CLKIN1 pin)
//
#define SIM_SOPT4_TPM1CLKSEL    0x02000000

//
//! TPM2 External Clock Pin Select
//! (0:TPM2 external clock driven by TPM_CLKIN0 pin)
//! (1:TPM2 external clock driven by TPM_CLKIN1 pin)
//
#define SIM_SOPT4_TPM2CLKSEL    0x04000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_SOPT5 SysCtl SIM SIM_SOPT5 Register(SysCtl_SIM_SOPT5)
//! \brief Defines for the bit fields in the SIM_SOPT5 register.
//! @{
//
//*****************************************************************************

//
//! UART0 transmit data source select Mask
//
#define SIM_SOPT5_UART0TXSRC_M  0x00000003    

//
//! UART0 transmit data source select Shift
//
#define SIM_SOPT5_UART0TXSRC_S  0 

//
//! UART0 transmit data source is UART0_TX pin
//
#define SIM_SOPT5_UART0TXSRC_UART0_TX                                          \
                                0x00000000

//
//! UART0_TX pin modulated with TPM1 channel 0 output
//
#define SIM_SOPT5_UART0TXSRC_TPM1_CH0                                          \
                                0x00000001

//
//! UART0_TX pin modulated with TPM2 channel 0 output
//
#define SIM_SOPT5_UART0TXSRC_TPM2_CH0                                          \
                                0x00000002
           
//
//! UART0 receive data source select
//! (0:UART0_RX pin, 1:CMP0 output)
//
#define SIM_SOPT5_UART0RXSRC    0x00000004 

//
//! UART1 transmit data source select Mask
//
#define SIM_SOPT5_UART1TXSRC_M  0x00000030    

//
//! UART1 transmit data source select Mask
//
#define SIM_SOPT5_UART1TXSRC_S  4 

//
//! UART1 transmit data source is UART1_TX pin
//
#define SIM_SOPT5_UART1TXSRC_UART1_TX                                          \
                                0x00000000

//
//! UART1_TX pin modulated with TPM1 channel 0 output
//
#define SIM_SOPT5_UART1TXSRC_TPM1_CH0                                          \
                                0x00000010

//
//! UART1_TX pin modulated with TPM2 channel 0 output
//
#define SIM_SOPT5_UART1TXSRC_TPM2_CH0                                          \
                                0x00000020

//
//! UART1 receive data source select
//! (0:UART1_RX pin, 1:CMP0 output)
//
#define SIM_SOPT5_UART1RXSRC    0x00000040

//
//! UART0 Open Drain Enable
//
#define SIM_SOPT5_UART0ODE      0x00010000

//
//! UART1 Open Drain Enable
//
#define SIM_SOPT5_UART1ODE      0x00020000

//
//! UART2 Open Drain Enable
//
#define SIM_SOPT5_UART2ODE      0x00040000
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_SOPT7 SysCtl SIM SIM_SOPT7 Register(SysCtl_SIM_SOPT7)
//! \brief Defines for the bit fields in the SIM_SOPT7 register.
//! @{
//
//*****************************************************************************

//
//! ADC0 trigger select Mask
//
#define SIM_SOPT7_ADC0TRGSEL_M  0x0000000F    

//
//! ADC0 trigger select Shift
//
#define SIM_SOPT7_ADC0TRGSEL_S  0

//
//! ADC0 trigger is External trigger pin input (EXTRG_IN)
//
#define SIM_SOPT7_ADC0TRGSEL_EXTRG_IN                                         \
                                0x00000000

//
//! ADC0 trigger is HSCMP0 output
//
#define SIM_SOPT7_ADC0TRGSEL_HSCMP0                                           \
                                0x00000001

//
//! ADC0 trigger is PIT trigger 0
//
#define SIM_SOPT7_ADC0TRGSEL_PIT0                                             \
                                0x00000004

//
//! ADC0 trigger is PIT trigger 1
//
#define SIM_SOPT7_ADC0TRGSEL_PIT1                                             \
                                0x00000005

//
//! ADC0 trigger is TPM0 overflow
//
#define SIM_SOPT7_ADC0TRGSEL_TPM0                                             \
                                0x00000008

//
//! ADC0 trigger is TPM1 overflow
//
#define SIM_SOPT7_ADC0TRGSEL_TPM1                                             \
                                0x00000009

//
//! ADC0 trigger is TPM2 overflow
//
#define SIM_SOPT7_ADC0TRGSEL_TPM2                                             \
                                0x0000000A

//
//! ADC0 trigger is RTC alarm
//
#define SIM_SOPT7_ADC0TRGSEL_RTC_AlARM                                        \
                                0x0000000C

//
//! ADC0 trigger is RTC Seconds
//
#define SIM_SOPT7_ADC0TRGSEL_RTC_SECOND                                       \
                                0x0000000D

//
//! ADC0 trigger is LPTMR0 trigger
//
#define SIM_SOPT7_ADC0TRGSEL_LPTMR0                                           \
                                0x0000000E
                                
//
//! ADC0 trigger is LPTMR0 trigger
//
#define SIM_SOPT7_ADC0TRGSEL_LPTMR0                                           \
                                0x0000000E
//
//! ADC0 pretrigger select(0:Pre-trigger A,1:Pre-trigger B)
//
#define SIM_SOPT7_ADC0PRETRGSEL 0x00000010

//
//! ADC0 alternate trigger enable
//! (1:Alternate trigger selected for ADC0)
//! (0:TPM1 channel 0 (A) and channel 1 (B) triggers selected for ADC0)
//
#define SIM_SOPT7_ADC0ALTTRGEN  0x00000080
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_SCGC4 SysCtl SIM SCGC4 Register(SysCtl_SIM_SCGC4)
//! \brief Defines for the bit fields in the SIM_SCGC4 register.
//! @{
//
//*****************************************************************************

//
//! I2C0 Clock enabled
//
#define SIM_SCGC4_I2C0_EN       0x00000040  

//
//! I2C1 Clock enabled
//
#define SIM_SCGC4_I2C1_EN       0x00000080

//
//! UART0 Clock enabled
//
#define SIM_SCGC4_UART0_EN      0x00000400

//
//! UART1 Clock enabled
//
#define SIM_SCGC4_UART1_EN      0x00000800

//
//! UART2 Clock enabled
//
#define SIM_SCGC4_UART2_EN      0x00001000

//
//! USB Clock enabled
//
#define SIM_SCGC4_USBOTG_EN     0x00040000

//
//! Comparator Clock enabled
//
#define SIM_SCGC4_CMP_EN        0x00080000

//
//! SPI0 Clock enabled
//
#define SIM_SCGC4_SPI0_EN       0x00400000

//
//! SPI1 Clock enabled
//
#define SIM_SCGC4_SPI1_EN       0x00800000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_SCGC5 SysCtl SIM SCGC5 Register(SysCtl_SIM_SCGC5)
//! \brief Defines for the bit fields in the SIM_SCGC5 register.
//! @{
//
//*****************************************************************************

//
//! Low Power Timer Clock enabled
//
#define SIM_SCGC5_LPTMR_EN      0x00000001  

//
//! TSI Clock enabled
//
#define SIM_SCGC5_TSI_EN        0x00000020

//
//! PORTA Clock enabled
//
#define SIM_SCGC5_PORTA_EN      0x00000200

//
//! PORTB Clock enabled
//
#define SIM_SCGC5_PORTB_EN      0x00000400

//
//! PORTC Clock enabled
//
#define SIM_SCGC5_PORTC_EN      0x00000800

//
//! PORTD Clock enabled
//
#define SIM_SCGC5_PORTD_EN      0x00001000

//
//! PORTE Clock enabled
//
#define SIM_SCGC5_PORTE_EN      0x00002000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_SCGC6 SysCtl SIM SCGC6 Register(SysCtl_SIM_SCGC6)
//! \brief Defines for the bit fields in the SIM_SCGC6 register.
//! @{
//
//*****************************************************************************

//
//! Flash Memory Clock enabled
//
#define SIM_SCGC6_FTF_EN        0x00000001  

//
//! DMA Mux Clock enabled
//
#define SIM_SCGC6_DMAMUX_EN     0x00000002

//
//! PIT Clock enabled
//
#define SIM_SCGC6_PIT_EN        0x00800000

//
//! TPM0 Clock enabled
//
#define SIM_SCGC6_TPM0_EN       0x01000000

//
//! TPM1 Clock enabled
//
#define SIM_SCGC6_TPM1_EN       0x02000000

//
//! TPM2 Clock enabled
//
#define SIM_SCGC6_TPM2_EN       0x04000000

//
//! ADC0 Clock enabled
//
#define SIM_SCGC6_ADC0_EN       0x08000000

//
//! RTC Clock enabled
//
#define SIM_SCGC6_RTC_EN        0x20000000

//
//! DAC0 Clock enabled
//
#define SIM_SCGC6_DAC0_EN       0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_SCGC7 SysCtl SIM SCGC6 Register(SysCtl_SIM_SCGC7)
//! \brief Defines for the bit fields in the SIM_SCGC7 register.
//! @{
//
//*****************************************************************************

//
//! DMA Clock enabled
//
#define SIM_SCGC7_DMA_EN        0x00000100  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_CLKDIV1 SysCtl SIM_CLKDIV1 Register(SysCtl_SIM_CLKDIV1)
//! \brief Defines for the bit fields in the SIM_CLKDIV1 register.
//! @{
//
//*****************************************************************************

//
//! Clock 4 output divider value Mask
//
#define SIM_CLKDIV1_OUTDIV4_M   0x00070000  

//
//! Clock 4 output divider value Shift
//
#define SIM_CLKDIV1_OUTDIV4_S   16

//
//! Clock 4 output divider value is 1
//
#define SIM_CLKDIV1_OUTDIV4_1   0x00000000

//
//! Clock 4 output divider value is 2
//
#define SIM_CLKDIV1_OUTDIV4_2   0x00010000

//
//! Clock 4 output divider value is 3
//
#define SIM_CLKDIV1_OUTDIV4_3   0x00020000

//
//! Clock 4 output divider value is 4
//
#define SIM_CLKDIV1_OUTDIV4_4   0x00030000

//
//! Clock 4 output divider value is 5
//
#define SIM_CLKDIV1_OUTDIV4_5   0x00040000

//
//! Clock 4 output divider value is 6
//
#define SIM_CLKDIV1_OUTDIV4_6   0x00050000

//
//! Clock 4 output divider value is 7
//
#define SIM_CLKDIV1_OUTDIV4_7   0x00060000

//
//! Clock 4 output divider value is 8
//
#define SIM_CLKDIV1_OUTDIV4_8   0x00070000

//
//! Clock 1 output divider value Mask
//
#define SIM_CLKDIV1_OUTDIV1_M   0xF0000000  

//
//! Clock 1 output divider value Shift
//
#define SIM_CLKDIV1_OUTDIV1_S   28

//
//! Clock 1 output divider value is 1
//
#define SIM_CLKDIV1_OUTDIV4_1   0x00000000

//
//! Clock 1 output divider value is 2
//
#define SIM_CLKDIV1_OUTDIV1_2   0x10000000

//
//! Clock 1 output divider value is 3
//
#define SIM_CLKDIV1_OUTDIV1_3   0x20000000

//
//! Clock 1 output divider value is 4
//
#define SIM_CLKDIV1_OUTDIV1_4   0x30000000

//
//! Clock 1 output divider value is 5
//
#define SIM_CLKDIV1_OUTDIV1_5   0x40000000

//
//! Clock 1 output divider value is 6
//
#define SIM_CLKDIV1_OUTDIV1_6   0x50000000

//
//! Clock 1 output divider value is 7
//
#define SIM_CLKDIV1_OUTDIV1_7   0x60000000

//
//! Clock 1 output divider value is 8
//
#define SIM_CLKDIV1_OUTDIV1_8   0x70000000

//
//! Clock 1 output divider value is 9
//
#define SIM_CLKDIV1_OUTDIV4_9   0x80000000

//
//! Clock 1 output divider value is 9
//
#define SIM_CLKDIV1_OUTDIV1_10  0x90000000

//
//! Clock 1 output divider value is 11
//
#define SIM_CLKDIV1_OUTDIV1_11  0xA0000000

//
//! Clock 1 output divider value is 12
//
#define SIM_CLKDIV1_OUTDIV1_12  0xB0000000

//
//! Clock 1 output divider value is 13
//
#define SIM_CLKDIV1_OUTDIV1_13  0xC0000000

//
//! Clock 1 output divider value is 14
//
#define SIM_CLKDIV1_OUTDIV1_14  0xD0000000

//
//! Clock 1 output divider value is 15
//
#define SIM_CLKDIV1_OUTDIV1_15  0xE0000000

//
//! Clock 1 output divider value is 16
//
#define SIM_CLKDIV1_OUTDIV1_16  0xF0000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_FCFG1 SysCtl SIM FCFG1 Register(SysCtl_SIM_FCFG1)
//! \brief Defines for the bit fields in the SIM_FCFG1 register.
//! @{
//
//*****************************************************************************

//
//! Flash Disable(0:Flash is enabled,1:Flash is disabled)
//
#define SIM_FCFG1_FLASHDIS      0x00000001  

//
//! Flash Doze
//
#define SIM_FCFG1_FLASHDOZE     0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_FCFG2 SysCtl SIM FCFG2 Register(SysCtl_SIM_FCFG2)
//! \brief Defines for the bit fields in the SIM_FCFG2 register.
//! @{
//
//*****************************************************************************

//
//! Max address block Mask
//
#define SIM_FCFG2_MAXADDR_M     0x7F000000  

//
//! Max address block Shift
//
#define SIM_FCFG2_MAXADDR_S     24  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_UIDMH SysCtl SIM UIDMH Register(SysCtl_SIM_UIDMH)
//! \brief Defines for the bit fields in the SIM_UIDMH register.
//! @{
//
//*****************************************************************************

//
//! Unique Identification Mask
//
#define SIM_UIDMH_UID_M         0x0000FFFF
  
//
//! Unique Identification Shift
//
#define SIM_UIDMH_UID_S         0   

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_UIDML SysCtl SIM UIDML Register(SysCtl_SIM_UIDML)
//! \brief Defines for the bit fields in the SIM_UIDML register.
//! @{
//
//*****************************************************************************

//
//! Unique Identification Mask
//
#define SIM_UIDML_UID_M         0xFFFFFFFF
  
//
//! Unique Identification Shift
//
#define SIM_UIDML_UID_S         0   

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_UIDL SysCtl SIM UIDL Register(SysCtl_SIM_UIDL)
//! \brief Defines for the bit fields in the SIM_UIDL register.
//! @{
//
//*****************************************************************************

//
//! Unique Identification Mask
//
#define SIM_UIDL_UID_M         0xFFFFFFFF
  
//
//! Unique Identification Shift
//
#define SIM_UIDL_UID_S         0   

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_COPC SysCtl SIM COPC Register(SysCtl_SIM_COPC)
//! \brief Defines for the bit fields in the SIM_COPC register.
//! @{
//
//*****************************************************************************

//
//! COP windowed mode(0:Normal mode,1:Windowed mode)
//
#define SIM_COPC_COPW           0x00000001  

//
//! COP Clock Select
//!(0:Internal 1 kHz clock is source to COP)
//!(1:Bus clock is source to COP)
//
#define SIM_COPC_COPCLKS        0x00000002

//
//! COP Watchdog Timeout Mask
//
#define SIM_COPC_COPT_M         0x0000000C

//
//! COP Watchdog Timeout Shift
//
#define SIM_COPC_COPT_S         2

//
//! COP Watchdog Timeout disable
//
#define SIM_COPC_COPT_0         0x00000000

//
//! COP timeout after 2^5 LPO cycles or 2^13 bus clock cycles
//
#define SIM_COPC_COPT_2_5_13    0x00000004

//
//! COP timeout after 2^8 LPO cycles or 2^16 bus clock cycles
//
#define SIM_COPC_COPT_2_8_16    0x00000008

//
//! COP timeout after 2^10 LPO cycles or 2^18 bus clock cycles
//
#define SIM_COPC_COPT_2_10_18   0x0000000C

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SIM_SRVCOP SysCtl SIM_SRVCOP Register(SysCtl_SIM_SRVCOP)
//! \brief Defines for the bit fields in the SIM_SRVCOP register.
//! @{
//
//****************************************************************************

//
//! Sevice COP Register Mask
//
#define SIM_SRVCOP_SRVCOP_M     0x000000FF

//
//! Sevice COP Register Shift
//
#define SIM_SRVCOP_SRVCOP_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_MCG_C1 SysCtl MCG C1 Register(SysCtl_MCG_C1)
//! \brief Defines for the bit fields in the MCG_C1 register.
//! @{
//
//*****************************************************************************

//
//! Internal Reference Stop Enable
//
#define MCG_C1_IREFSTEN         0x01  

//
//! Internal Reference Clock Enable
//
#define MCG_C1_IRCLKEN          0x02  

//
//! Internal Reference Select
//
#define MCG_C1_IREFS            0x04

//
//! FLL External Reference Divider Mask
//
#define MCG_C1_FRDIV_M          0x38

//
//! FLL External Reference Divider Shift
//
#define MCG_C1_FRDIV_S          3

//
//! If RANGE0=0 , Divide Factor is 1; for all other RANGE 0 values, Divide Factor is 32.
//
#define MCG_C1_FRDIV_32         0x00

//
//! If RANGE0=0,Divide Factor is 2; for all other RANGE 0 values, Divide Factor is 64.
//
#define MCG_C1_FRDIV_64         0x08

//
//! If RANGE0=0,Divide Factor is 4; for all other RANGE 0 values, Divide Factor is 128
//
#define MCG_C1_FRDIV_128        0x10

//
//! If RANGE0=0,Divide Factor is 8; for all other RANGE 0 values, Divide Factor is 256.
//
#define MCG_C1_FRDIV_256        0x18

//
//! If RANGE0=0,Divide Factor is 16;for all other RANGE 0 values,Divide Factor is 512
//
#define MCG_C1_FRDIV_512        0x20

//
//! If RANGE0=0,Divide Factor is 32;for all other RANGE 0 values,Divide Factor is 1024
//
#define MCG_C1_FRDIV_1024       0x28

//
//! If RANGE0=0,Divide Factor is 64;for all other RANGE 0 values,Divide Factor is 1280
//
#define MCG_C1_FRDIV_1280       0x30

//
//! If RANGE0=0,Divide Factor is 128;for all other RANGE 0 values,Divide Factor is 1536 
//
#define MCG_C1_FRDIV_1536       0x38

//
//! Clock source for MCGOUTCLK Mask
//
#define MCG_C1_SRC_MCGOUTCLK_M  0xC0

//
//! Clock source for MCGOUTCLK Shift
//
#define MCG_C1_SRC_MCGOUTCLK_S  6

//
//! Clock source for MCGOUTCLK is Output of FLL or PLL
//
#define MCG_C1_SRC_MCGOUTCLK_XLL                                              \
                                0x00
                                
//
//! Clock source for MCGOUTCLK is Internal reference clock
//
#define MCG_C1_SRC_MCGOUTCLK_INTERAL                                          \
                                0x40
                                
//
//! Clock source for MCGOUTCLK is External reference clock
//
#define MCG_C1_SRC_MCGOUTCLK_EXTERAL                                          \
                                0x80
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_MCG_C2 SysCtl MCG C2 Register(SysCtl_MCG_C2)
//! \brief Defines for the bit fields in the MCG_C2 register.
//! @{
//
//*****************************************************************************

//
//! Internal Reference Clock Select
//
#define MCG_C2_IRCS             0x01  

//
//! Low Power Select
//
#define MCG_C2_LP               0x02  

//
//! External Reference Select
//! (0:External reference clock requested}
//! (1:Oscillator requested)
//
#define MCG_C2_EREFS0           0x04  

//
//! High Gain Oscillator Select
//! (0:Configure crystal oscillator for low-power operation}
//! (1:Configure crystal oscillator for high-gain operation)
//
#define MCG_C2_HGO0             0x08
                                
//
//! Frequency Range Select Mask
//
#define MCG_C2_RANGE0_M         0x30

//
//! Frequency Range Select Shift
//
#define MCG_C2_RANGE0_S         4

//
//! Encoding 0 ！ Low frequency range selected for the crystal oscillator 
//
#define MCG_C2_RANGE0_LOW       0x00

//
//! Encoding 1 ！ High frequency range selected for the crystal oscillator 
//
#define MCG_C2_RANGE0_HIGH      0x10

//
//! Encoding 2 ！ Very high frequency range selected for the crystal oscillator 
//
#define MCG_C2_RANGE0_VERY_HIGH 0x20

//
//! Loss of Clock Reset Enable
//
#define MCG_C2_LOCRE0           0x80
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_MCG_C3 SysCtl MCG C3 Register(SysCtl_MCG_C3)
//! \brief Defines for the bit fields in the MCG_C3 register.
//! @{
//
//*****************************************************************************
                                
//
//! Slow Internal Reference Clock Trim Setting Mask
//
#define MCG_C3_SCTRIM_M         0xFF

//
//! Slow Internal Reference Clock Trim Setting Shift
//
#define MCG_C3_SCTRIM_S         0
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_MCG_C4 SysCtl MCG C4 Register(SysCtl_MCG_C4)
//! \brief Defines for the bit fields in the MCG_C4 register.
//! @{
//
//*****************************************************************************

//
//! Slow Internal Reference Clock Fine Trim
//
#define MCG_C4_SCFTRIM          0x01  

//
//! Fast Internal Reference Clock Trim Setting Mask
//
#define MCG_C4_FCTRIM_M         0x1E  

//
//! Fast Internal Reference Clock Trim Setting Shift
//
#define MCG_C4_FCTRIM_S         1
                                
//
//! DCO Range Select Mask
//
#define MCG_C4_DRST_DRS_M       0x60

//
//! DCO Range Select Shift
//
#define MCG_C4_DRST_DRS_S       4

//
//! Encoding 0 ！  Low range (reset default) 
//
#define MCG_C4_DRST_DRS_LOW     0x00

//
//! Encoding 1 ！ Mid range 
//
#define MCG_C4_DRST_DRS_MID     0x20

//
//! Encoding 2 ！  Mid-high range 
//
#define MCG_C4_DRST_DRS_MID_HIGH                                              \
                                0x40

//
//! Encoding 3 ！  High range 
//
#define MCG_C4_DRST_DRS_HIGH    0x60
//
//! DCO Maximum Frequency with 32.768 kHz Reference
//! (0:DCO has a default range of 25%}
//! (1:DCO is fine-tuned for maximum frequency with 32.768 kHz reference)
//
#define MCG_C4_DMX32            0x80
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_MCG_C5 SysCtl MCG C5 Register(SysCtl_MCG_C5)
//! \brief Defines for the bit fields in the MCG_C5 register.
//! @{
//
//*****************************************************************************

//
//! PLL External Reference Divider Mask
//
#define MCG_C5_PRDIV0_M         0x1F  

//
//! PLL External Reference Divider Shift
//
#define MCG_C5_PRDIV0_S         0 

//
//! PLL External Reference Divider is 1
//
#define MCG_C5_PRDIV0_1         0x00 

//
//! PLL External Reference Divider is 2
//
#define MCG_C5_PRDIV0_2         0x01

//
//! PLL External Reference Divider is 3
//
#define MCG_C5_PRDIV0_3         0x02 

//
//! PLL External Reference Divider is 4
//
#define MCG_C5_PRDIV0_4         0x03

//
//! PLL External Reference Divider is 5
//
#define MCG_C5_PRDIV0_5         0x04 

//
//! PLL External Reference Divider is 6
//
#define MCG_C5_PRDIV0_6         0x05

//
//! PLL External Reference Divider is 7
//
#define MCG_C5_PRDIV0_7         0x06 

//
//! PLL External Reference Divider is 8
//
#define MCG_C5_PRDIV0_8         0x07

//
//! PLL External Reference Divider is 9
//
#define MCG_C5_PRDIV0_9         0x08 

//
//! PLL External Reference Divider is 10
//
#define MCG_C5_PRDIV0_10        0x09

//
//! PLL External Reference Divider is 11
//
#define MCG_C5_PRDIV0_11        0x0A 

//
//! PLL External Reference Divider is 12
//
#define MCG_C5_PRDIV0_12        0x0B

//
//! PLL External Reference Divider is 13
//
#define MCG_C5_PRDIV0_13        0x0C 

//
//! PLL External Reference Divider is 14
//
#define MCG_C5_PRDIV0_14        0x0D

//
//! PLL External Reference Divider is 15
//
#define MCG_C5_PRDIV0_15        0x0E 

//
//! PLL External Reference Divider is 16
//
#define MCG_C5_PRDIV0_16        0x0F

//
//! PLL External Reference Divider is 17
//
#define MCG_C5_PRDIV0_17        0x10

//
//! PLL External Reference Divider is 18
//
#define MCG_C5_PRDIV0_18        0x11 

//
//! PLL External Reference Divider is 19
//
#define MCG_C5_PRDIV0_19        0x12

//
//! PLL External Reference Divider is 20
//
#define MCG_C5_PRDIV0_20        0x13 

//
//! PLL External Reference Divider is 21
//
#define MCG_C5_PRDIV0_21        0x14

//
//! PLL External Reference Divider is 22
//
#define MCG_C5_PRDIV0_22        0x15 

//
//! PLL External Reference Divider is 23
//
#define MCG_C5_PRDIV0_23        0x16

//
//! PLL External Reference Divider is 24
//
#define MCG_C5_PRDIV0_24        0x17 

//
//! PLL External Reference Divider is 25
//
#define MCG_C5_PRDIV0_25        0x18

//
//! PLL Stop Enable
//
#define MCG_C5_PLLSTEN0         0x20
                                
//
//! PLL Clock Enable
//
#define MCG_C5_PLLCLKEN0        0x40

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_MCG_C6 SysCtl MCG C6 Register(SysCtl_MCG_C6)
//! \brief Defines for the bit fields in the MCG_C6 register.
//! @{
//
//*****************************************************************************

//
//! VCO 0 Divider Mask
//
#define MCG_C6_VDIV0_M          0x1F  

//
//! VCO 0 Divider Shift
//
#define MCG_C6_VDIV0_S          0  

//
//! VCO 0 Divider is 24
//
#define MCG_C6_VDIV0_24         0x00 

//
//! VCO 0 Divider is 25
//
#define MCG_C6_VDIV0_25         0x01

//
//! VCO 0 Divider is 26
//
#define MCG_C6_VDIV0_26         0x02 

//
//! VCO 0 Divider is 27
//
#define MCG_C6_VDIV0_27         0x03

//
//! VCO 0 Divider is 28
//
#define MCG_C6_VDIV0_28         0x04 

//
//! VCO 0 Divider is 29
//
#define MCG_C6_VDIV0_29         0x05

//
//! VCO 0 Divider is 30
//
#define MCG_C6_VDIV0_30         0x06 

//
//! VCO 0 Divider is 31
//
#define MCG_C6_VDIV0_31         0x07

//
//! VCO 0 Divider is 32
//
#define MCG_C6_VDIV0_32         0x08 

//
//! VCO 0 Divider is 33
//
#define MCG_C6_VDIV0_33         0x09

//
//! VCO 0 Divider is 34
//
#define MCG_C6_VDIV0_34         0x0A 

//
//! VCO 0 Divider is 35
//
#define MCG_C6_VDIV0_35         0x0B

//
//! VCO 0 Divider is 36
//
#define MCG_C6_VDIV0_36         0x0C 

//
//! VCO 0 Divider is 37
//
#define MCG_C6_VDIV0_37         0x0D

//
//! VCO 0 Divider is 38
//
#define MCG_C6_VDIV0_38         0x0E 

//
//! VCO 0 Divider is 39
//
#define MCG_C6_VDIV0_39         0x0F

//
//! VCO 0 Divider is 40
//
#define MCG_C6_VDIV0_40         0x10

//
//! VCO 0 Divider is 41
//
#define MCG_C6_VDIV0_41         0x11 

//
//! VCO 0 Divider is 42
//
#define MCG_C6_VDIV0_42         0x12

//
//! VCO 0 Divider is 43
//
#define MCG_C6_VDIV0_43         0x13 

//
//! VCO 0 Divider is 44
//
#define MCG_C6_VDIV0_44         0x14

//
//! VCO 0 Divider is 45
//
#define MCG_C6_VDIV0_45         0x15 

//
//! VCO 0 Divider is 46
//
#define MCG_C6_VDIV0_46         0x16

//
//! VCO 0 Divider is 47
//
#define MCG_C6_VDIV0_47         0x17

//
//! VCO 0 Divider is 48
//
#define MCG_C6_VDIV0_48         0x18 

//
//! VCO 0 Divider is 49
//
#define MCG_C6_VDIV0_49         0x19

//
//! VCO 0 Divider is 50
//
#define MCG_C6_VDIV0_50         0x1A 

//
//! VCO 0 Divider is 51
//
#define MCG_C6_VDIV0_51         0x1B

//
//! VCO 0 Divider is 52
//
#define MCG_C6_VDIV0_52         0x1C 

//
//! VCO 0 Divider is 53
//
#define MCG_C6_VDIV0_53         0x1D

//
//! VCO 0 Divider is 54
//
#define MCG_C6_VDIV0_54         0x1E 

//
//! VCO 0 Divider is 55
//
#define MCG_C6_VDIV0_55         0x1F

//
//! Clock Monitor Enable
//
#define MCG_C6_CME0             0x20
                                
//
//! PLL Select
//
#define MCG_C6_PLLS             0x40

//
//! Loss of Lock Interrrupt Enable
//
#define MCG_C6_LOLIE0           0x80

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_MCG_S SysCtl MCG Status Register(SysCtl_MCG_S)
//! \brief Defines for the bit fields in the MCG_S register.
//! @{
//
//*****************************************************************************

//
//! Internal Reference Clock Status
//
#define MCG_S_IRCST             0x01 

//
//! OSC Initialization
//
#define MCG_S_OSCINIT0          0x02

//
//! Clock Mode Status Mask
//
#define MCG_S_CLKST_M           0x0C  

//
//! Clock Mode Status Shift
//
#define MCG_S_CLKST_S           2  

//
//! Encoding 0 ！ Output of the FLL is selected (reset default).
//
#define MCG_S_CLKST_FLL         0x00

//
//! Encoding 1 ！ Internal reference clock is selected.
//
#define MCG_S_CLKST_INT         0x04

//
//! Encoding 2 ！ External reference clock is selected.
//
#define MCG_S_CLKST_EXT         0x08

//
//! Encoding 3 ！ Output of the PLL is selected.
//
#define MCG_S_CLKST_PLL         0x0C

//
//! Internal Reference Status
//
#define MCG_S_IREFST            0x10

//
//! PLL Select Status
//
#define MCG_S_PLLST             0x20

//
//! Lock Status
//
#define MCG_S_LOCK0             0x40

//
//! Loss of Lock Status
//
#define MCG_S_LOLS              0x80

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_MCG_SC SysCtl MCG Status and Control Register(SysCtl_MCG_SC)
//! \brief Defines for the bit fields in the MCG_SC register.
//! @{
//
//*****************************************************************************

//
//! OSC0 Loss of Clock Status
//
#define MCG_SC_LOCS0            0x01 

//
//! Fast Clock Internal Reference Divider Mask
//
#define MCG_SC_FCRDIV_M         0x0E  

//
//! Fast Clock Internal Reference Divider Shift
//
#define MCG_SC_FCRDIV_S         1  

//
//! Fast Clock Internal Reference Divider is 1
//
#define MCG_SC_FCRDIV_1         0x00

//
//! Fast Clock Internal Reference Divider is 2
//
#define MCG_SC_FCRDIV_2         0x01

//
//! Fast Clock Internal Reference Divider is 4
//
#define MCG_SC_FCRDIV_4         0x02

//
//! Fast Clock Internal Reference Divider is 8
//
#define MCG_SC_FCRDIV_8         0x03

//
//! Fast Clock Internal Reference Divider is 16
//
#define MCG_SC_FCRDIV_16        0x04

//
//! Fast Clock Internal Reference Divider is 32
//
#define MCG_SC_FCRDIV_32        0x05

//
//! Fast Clock Internal Reference Divider is 64
//
#define MCG_SC_FCRDIV_64        0x06

//
//! Fast Clock Internal Reference Divider is 128
//
#define MCG_SC_FCRDIV_128       0x07

//
//! FLL Filter Preserve Enable
//
#define MCG_SC_FLTPRSRV         0x10

//
//! Automatic Trim Machine Fail Flag
//
#define MCG_SC_ATMF             0x20

//
//! Automatic Trim Machine Select
//
#define MCG_SC_ATMS             0x40

//
//! Automatic Trim Machine Enable
//
#define MCG_SC_ATME             0x80

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_MCG_ATCVH SysCtl MCG Auto Trim Compare Value High Register(MCG_ATCVH)
//! \brief Defines for the bit fields in the MCG_ATCVH register.
//! @{
//
//*****************************************************************************

//
//! ATM Compare Value High Mask
//
#define MCG_ATCVH_ATCVH_M       0xFF  

//
//! ATM Compare Value High Shift
//
#define MCG_ATCVH_ATCVH_S       0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_MCG_ATCVL SysCtl MCG Auto Trim Compare Value Low Register(MCG_ATCVL)
//! \brief Defines for the bit fields in the MCG_ATCVL register.
//! @{
//
//*****************************************************************************

//
//! ATM Compare Value Low Mask
//
#define MCG_ATCVL_ATCVL_M       0xFF  

//
//! ATM Compare Value Low Shift
//
#define MCG_ATCVL_ATCVL_S       0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_MCG_C7 SysCtl MCG C7 Register(SysCtl_MCG_C7)
//! \brief Defines for the bit fields in the MCG_C7 register.
//! @{
//
//*****************************************************************************
                                


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_MCG_C8 SysCtl MCG C8 Register(SysCtl_MCG_C8)
//! \brief Defines for the bit fields in the MCG_C8 register.
//! @{
//
//*****************************************************************************

//
//! PLL Loss of Lock Reset Enable
//                       
#define MCG_C8_LOLRE            0x40

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_MCG_C9 SysCtl MCG C9 Register(SysCtl_MCG_C9)
//! \brief Defines for the bit fields in the MCG_C9 register.
//! @{
//
//*****************************************************************************
                                


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_MCG_C9 SysCtl MCG C9 Register(SysCtl_MCG_C9)
//! \brief Defines for the bit fields in the MCG_C9 register.
//! @{
//
//*****************************************************************************
                                


//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_PMC_LVDSC1 SysCtl PMC LVDSC1 Register(SysCtl_PMC_LVDSC1)
//! \brief Defines for the bit fields in the PMC_LVDSC1 register.
//! @{
//
//*****************************************************************************

//
//! Low-Voltage Detect Voltage Mask
//
#define PMC_LVDSC1_LVDV_M       0x03  

//
//! Low-Voltage Detect Voltage Shift
//
#define PMC_LVDSC1_LVDV_S       0   

//
//! Low-Voltage Detect Voltage is Low trip point selected (V LVD = V LVDL)
//
#define PMC_LVDSC1_LVDV_LOW     0x00

//
//! Low-Voltage Detect Voltage is High trip point selected (V LVD = V LVDH)
//
#define PMC_LVDSC1_LVDV_HIGH    0x01

//
//! Low-Voltage Detect Reset Enable
//
#define PMC_LVDSC1_LVDRE        0x10

//
//! Low-Voltage Detect Interrupt Enable
//
#define PMC_LVDSC1_LVDIE        0x20

//
//! Low-Voltage Detect Acknowledge
//
#define PMC_LVDSC1_LVDACK       0x40

//
//! Low-Voltage Detect Flag
//
#define PMC_LVDSC1_LVDF         0x80

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_PMC_LVDSC2 SysCtl PMC LVDSC2 Register(SysCtl_PMC_LVDSC2)
//! \brief Defines for the bit fields in the PMC_LVDSC2 register.
//! @{
//
//*****************************************************************************

//
//! Low-Voltage Warning Voltage Select Mask
//
#define PMC_LVDSC2_LVWV_M       0x03  

//
//! Low-Voltage Warning Voltage Select Shift
//
#define PMC_LVDSC2_LVWV_S       0   

//
//! Low-Voltage Warning Voltage is Low trip point selected (VLVW = VLVW1)
//
#define PMC_LVDSC2_LVWV_LOW     0x00

//
//! Low-Voltage Warning Voltage is Mid 1 trip point selected (VLVW = VLVW2)
//
#define PMC_LVDSC2_LVWV_MID1    0x01

//
//! Low-Voltage Warning Voltage is Mid 2 trip point selected (VLVW = VLVW3)
//
#define PMC_LVDSC2_LVWV_MID2    0x02

//
//! Low-Voltage Warning Voltage is High trip point selected (VLVW = VLVW4)
//
#define PMC_LVDSC2_LVWV_HIGH    0x03

//
//! Low-Voltage Warning Interrupt Enable
//
#define PMC_LVDSC2_LVDRE        0x20

//
//! Low-Voltage Warning Acknowledge
//
#define PMC_LVDSC2_LVWACK       0x40

//
//! Low-Voltage Warning Flag
//
#define PMC_LVDSC2_LVWF         0x80

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_PMC_REGSC SysCtl PMC REGSC Register(SysCtl_PMC_REGSC)
//! \brief Defines for the bit fields in the PMC_REGSC register.
//! @{
//
//*****************************************************************************

//
//! Bandgap Buffer Enable
//
#define PMC_REGSC_BGBE          0x01  

//
//! Regulator In Run Regulation Status
//
#define PMC_REGSC_REGONS        0x04  

//
//! Acknowledge Isolation
//
#define PMC_REGSC_ACKISO        0x08  

//
//! Bandgap Enable In VLPx Operation
//
#define PMC_REGSC_BGEN          0x10

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_LLWU_PE1 SysCtl LLWU_PE1 Register(SysCtl_LLWU_PE1)
//! \brief Defines for the bit fields in the LLWU_PE1 register.
//! @{
//
//*****************************************************************************

//
//! Wakeup Pin Enable For LLWU_P0 Mask
//
#define LLWU_PE1_WUPE0_M        0x03  

//
//! Wakeup Pin Enable For LLWU_P0 Shift
//
#define LLWU_PE1_WUPE0_S        0

//
//! Wakeup Pin Enable For LLWU_P0 is External input pin disabled as wakeup input
//
#define LLWU_PE1_WUPE0_DIS      0x00

//
//! Wakeup Pin Enable For LLWU_P0 is External input pin enabled with rising edge detection
//
#define LLWU_PE1_WUPE0_RISING   0x01

//
//! Wakeup Pin Enable For LLWU_P0 is External input pin enabled with falling edge detection
//
#define LLWU_PE1_WUPE0_FALLING  0x02

//
//! Wakeup Pin Enable For LLWU_P0 is External input pin enabled with any change detection
//
#define LLWU_PE1_WUPE0_ANY      0x03


//
//! Wakeup Pin Enable For LLWU_P1 Mask
//
#define LLWU_PE1_WUPE1_M        0x0C  

//
//! Wakeup Pin Enable For LLWU_P1 Shift
//
#define LLWU_PE1_WUPE1_S        2

//
//! Wakeup Pin Enable For LLWU_P1 is External input pin disabled as wakeup input
//
#define LLWU_PE1_WUPE1_DIS      0x00

//
//! Wakeup Pin Enable For LLWU_P1 is External input pin enabled with rising edge detection
//
#define LLWU_PE1_WUPE1_RISING   0x04

//
//! Wakeup Pin Enable For LLWU_P1 is External input pin enabled with falling edge detection
//
#define LLWU_PE1_WUPE1_FALLING  0x08

//
//! Wakeup Pin Enable For LLWU_P1 is External input pin enabled with any change detection
//
#define LLWU_PE1_WUPE1_ANY      0x0C


//
//! Wakeup Pin Enable For LLWU_P2 Mask
//
#define LLWU_PE1_WUPE2_M        0x30  

//
//! Wakeup Pin Enable For LLWU_P2 Shift
//
#define LLWU_PE1_WUPE2_S        4

//
//! Wakeup Pin Enable For LLWU_P2 is External input pin disabled as wakeup input
//
#define LLWU_PE1_WUPE2_DIS      0x00

//
//! Wakeup Pin Enable For LLWU_P2 is External input pin enabled with rising edge detection
//
#define LLWU_PE1_WUPE2_RISING   0x01

//
//! Wakeup Pin Enable For LLWU_P2 is External input pin enabled with falling edge detection
//
#define LLWU_PE1_WUPE2_FALLING  0x20

//
//! Wakeup Pin Enable For LLWU_P2 is External input pin enabled with any change detection
//
#define LLWU_PE1_WUPE2_ANY      0x30


//
//! Wakeup Pin Enable For LLWU_P3 Mask
//
#define LLWU_PE1_WUPE3_M        0xC0  

//
//! Wakeup Pin Enable For LLWU_P3 Shift
//
#define LLWU_PE1_WUPE3_S        6

//
//! Wakeup Pin Enable For LLWU_P3 is External input pin disabled as wakeup input
//
#define LLWU_PE1_WUPE3_DIS      0x00

//
//! Wakeup Pin Enable For LLWU_P3 is External input pin enabled with rising edge detection
//
#define LLWU_PE1_WUPE3_RISING   0x40

//
//! Wakeup Pin Enable For LLWU_P3 is External input pin enabled with falling edge detection
//
#define LLWU_PE1_WUPE3_FALLING  0x80

//
//! Wakeup Pin Enable For LLWU_P3 is External input pin enabled with any change detection
//
#define LLWU_PE1_WUPE3_ANY      0xC0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_LLWU_PE2 SysCtl LLWU_PE2 Register(SysCtl_LLWU_PE2)
//! \brief Defines for the bit fields in the LLWU_PE2 register.
//! @{
//
//*****************************************************************************

//
//! Wakeup Pin Enable For LLWU_P4 Mask
//
#define LLWU_PE2_WUPE4_M        0x03  

//
//! Wakeup Pin Enable For LLWU_P4 Shift
//
#define LLWU_PE2_WUPE4_S        0

//
//! Wakeup Pin Enable For LLWU_P4 is External input pin disabled as wakeup input
//
#define LLWU_PE2_WUPE4_DIS      0x00

//
//! Wakeup Pin Enable For LLWU_P4 is External input pin enabled with rising edge detection
//
#define LLWU_PE2_WUPE4_RISING   0x01

//
//! Wakeup Pin Enable For LLWU_P4 is External input pin enabled with falling edge detection
//
#define LLWU_PE2_WUPE4_FALLING  0x02

//
//! Wakeup Pin Enable For LLWU_P4 is External input pin enabled with any change detection
//
#define LLWU_PE2_WUPE4_ANY      0x03


//
//! Wakeup Pin Enable For LLWU_P5 Mask
//
#define LLWU_PE2_WUPE5_M        0x0C  

//
//! Wakeup Pin Enable For LLWU_P5 Shift
//
#define LLWU_PE2_WUPE5_S        2

//
//! Wakeup Pin Enable For LLWU_P5 is External input pin disabled as wakeup input
//
#define LLWU_PE2_WUPE5_DIS      0x00

//
//! Wakeup Pin Enable For LLWU_P5 is External input pin enabled with rising edge detection
//
#define LLWU_PE2_WUPE5_RISING   0x04

//
//! Wakeup Pin Enable For LLWU_P5 is External input pin enabled with falling edge detection
//
#define LLWU_PE2_WUPE5_FALLING  0x08

//
//! Wakeup Pin Enable For LLWU_P5 is External input pin enabled with any change detection
//
#define LLWU_PE2_WUPE5_ANY      0x0C


//
//! Wakeup Pin Enable For LLWU_P6 Mask
//
#define LLWU_PE2_WUPE6_M        0x30  

//
//! Wakeup Pin Enable For LLWU_P6 Shift
//
#define LLWU_PE2_WUPE6_S        4

//
//! Wakeup Pin Enable For LLWU_P6 is External input pin disabled as wakeup input
//
#define LLWU_PE2_WUPE6_DIS      0x00

//
//! Wakeup Pin Enable For LLWU_P6 is External input pin enabled with rising edge detection
//
#define LLWU_PE2_WUPE6_RISING   0x01

//
//! Wakeup Pin Enable For LLWU_P6 is External input pin enabled with falling edge detection
//
#define LLWU_PE2_WUPE6_FALLING  0x20

//
//! Wakeup Pin Enable For LLWU_P6 is External input pin enabled with any change detection
//
#define LLWU_PE2_WUPE6_ANY      0x30


//
//! Wakeup Pin Enable For LLWU_P7 Mask
//
#define LLWU_PE2_WUPE7_M        0xC0  

//
//! Wakeup Pin Enable For LLWU_P7 Shift
//
#define LLWU_PE2_WUPE7_S        6

//
//! Wakeup Pin Enable For LLWU_P7 is External input pin disabled as wakeup input
//
#define LLWU_PE2_WUPE7_DIS      0x00

//
//! Wakeup Pin Enable For LLWU_P7 is External input pin enabled with rising edge detection
//
#define LLWU_PE2_WUPE7_RISING   0x40

//
//! Wakeup Pin Enable For LLWU_P7 is External input pin enabled with falling edge detection
//
#define LLWU_PE2_WUPE7_FALLING  0x80

//
//! Wakeup Pin Enable For LLWU_P7 is External input pin enabled with any change detection
//
#define LLWU_PE2_WUPE7_ANY      0xC0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_LLWU_PE3 SysCtl LLWU_PE3 Register(SysCtl_LLWU_PE3)
//! \brief Defines for the bit fields in the LLWU_PE3 register.
//! @{
//
//*****************************************************************************

//
//! Wakeup Pin Enable For LLWU_P8 Mask
//
#define LLWU_PE3_WUPE8_M        0x03  

//
//! Wakeup Pin Enable For LLWU_P8 Shift
//
#define LLWU_PE3_WUPE8_S        0

//
//! Wakeup Pin Enable For LLWU_P8 is External input pin disabled as wakeup input
//
#define LLWU_PE3_WUPE8_DIS      0x00

//
//! Wakeup Pin Enable For LLWU_P8 is External input pin enabled with rising edge detection
//
#define LLWU_PE3_WUPE8_RISING   0x01

//
//! Wakeup Pin Enable For LLWU_P8 is External input pin enabled with falling edge detection
//
#define LLWU_PE3_WUPE8_FALLING  0x02

//
//! Wakeup Pin Enable For LLWU_P8 is External input pin enabled with any change detection
//
#define LLWU_PE3_WUPE8_ANY      0x03


//
//! Wakeup Pin Enable For LLWU_P9 Mask
//
#define LLWU_PE3_WUPE9_M        0x0C  

//
//! Wakeup Pin Enable For LLWU_P9 Shift
//
#define LLWU_PE3_WUPE9_S        2

//
//! Wakeup Pin Enable For LLWU_P9 is External input pin disabled as wakeup input
//
#define LLWU_PE3_WUPE9_DIS      0x00

//
//! Wakeup Pin Enable For LLWU_P9 is External input pin enabled with rising edge detection
//
#define LLWU_PE3_WUPE9_RISING   0x04

//
//! Wakeup Pin Enable For LLWU_P9 is External input pin enabled with falling edge detection
//
#define LLWU_PE3_WUPE9_FALLING  0x08

//
//! Wakeup Pin Enable For LLWU_P9 is External input pin enabled with any change detection
//
#define LLWU_PE3_WUPE9_ANY      0x0C


//
//! Wakeup Pin Enable For LLWU_P10 Mask
//
#define LLWU_PE3_WUPE10_M       0x30  

//
//! Wakeup Pin Enable For LLWU_P10 Shift
//
#define LLWU_PE3_WUPE10_S       4

//
//! Wakeup Pin Enable For LLWU_P10 is External input pin disabled as wakeup input
//
#define LLWU_PE3_WUPE10_DIS     0x00

//
//! Wakeup Pin Enable For LLWU_P10 is External input pin enabled with rising edge detection
//
#define LLWU_PE3_WUPE10_RISING  0x01

//
//! Wakeup Pin Enable For LLWU_P10 is External input pin enabled with falling edge detection
//
#define LLWU_PE3_WUPE10_FALLING 0x20

//
//! Wakeup Pin Enable For LLWU_P10 is External input pin enabled with any change detection
//
#define LLWU_PE3_WUPE10_ANY     0x30


//
//! Wakeup Pin Enable For LLWU_P11 Mask
//
#define LLWU_PE3_WUPE11_M       0xC0  

//
//! Wakeup Pin Enable For LLWU_P11 Shift
//
#define LLWU_PE3_WUPE11_S       6

//
//! Wakeup Pin Enable For LLWU_P11 is External input pin disabled as wakeup input
//
#define LLWU_PE3_WUPE11_DIS     0x00

//
//! Wakeup Pin Enable For LLWU_P11 is External input pin enabled with rising edge detection
//
#define LLWU_PE3_WUPE11_RISING  0x40

//
//! Wakeup Pin Enable For LLWU_P11 is External input pin enabled with falling edge detection
//
#define LLWU_PE3_WUPE11_FALLING 0x80

//
//! Wakeup Pin Enable For LLWU_P11 is External input pin enabled with any change detection
//
#define LLWU_PE3_WUPE11_ANY     0xC0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_LLWU_PE4 SysCtl LLWU_PE3 Register(SysCtl_LLWU_PE4)
//! \brief Defines for the bit fields in the LLWU_PE4 register.
//! @{
//
//*****************************************************************************

//
//! Wakeup Pin Enable For LLWU_P11 Mask
//
#define LLWU_PE4_WUPE11_M       0x03  

//
//! Wakeup Pin Enable For LLWU_P11 Shift
//
#define LLWU_PE4_WUPE11_S       0

//
//! Wakeup Pin Enable For LLWU_P11 is External input pin disabled as wakeup input
//
#define LLWU_PE4_WUPE11_DIS     0x00

//
//! Wakeup Pin Enable For LLWU_P11 is External input pin enabled with rising edge detection
//
#define LLWU_PE4_WUPE11_RISING  0x01

//
//! Wakeup Pin Enable For LLWU_P11 is External input pin enabled with falling edge detection
//
#define LLWU_PE4_WUPE11_FALLING 0x02

//
//! Wakeup Pin Enable For LLWU_P8 is External input pin enabled with any change detection
//
#define LLWU_PE4_WUPE11_ANY     0x03


//
//! Wakeup Pin Enable For LLWU_P12 Mask
//
#define LLWU_PE4_WUPE12_M       0x0C  

//
//! Wakeup Pin Enable For LLWU_P12 Shift
//
#define LLWU_PE4_WUPE12_S       2

//
//! Wakeup Pin Enable For LLWU_P12 is External input pin disabled as wakeup input
//
#define LLWU_PE4_WUPE12_DIS     0x00

//
//! Wakeup Pin Enable For LLWU_P13 is External input pin enabled with rising edge detection
//
#define LLWU_PE4_WUPE13_RISING  0x04

//
//! Wakeup Pin Enable For LLWU_P9 is External input pin enabled with falling edge detection
//
#define LLWU_PE4_WUPE13_FALLING 0x08

//
//! Wakeup Pin Enable For LLWU_P13 is External input pin enabled with any change detection
//
#define LLWU_PE4_WUPE13_ANY     0x0C


//
//! Wakeup Pin Enable For LLWU_P14 Mask
//
#define LLWU_PE4_WUPE14_M       0x30  

//
//! Wakeup Pin Enable For LLWU_P14 Shift
//
#define LLWU_PE4_WUPE14_S       4

//
//! Wakeup Pin Enable For LLWU_P14 is External input pin disabled as wakeup input
//
#define LLWU_PE4_WUPE14_DIS     0x00

//
//! Wakeup Pin Enable For LLWU_P14 is External input pin enabled with rising edge detection
//
#define LLWU_PE4_WUPE14_RISING  0x01

//
//! Wakeup Pin Enable For LLWU_P14 is External input pin enabled with falling edge detection
//
#define LLWU_PE4_WUPE14_FALLING 0x20

//
//! Wakeup Pin Enable For LLWU_P14 is External input pin enabled with any change detection
//
#define LLWU_PE4_WUPE14_ANY     0x30


//
//! Wakeup Pin Enable For LLWU_P15 Mask
//
#define LLWU_PE4_WUPE15_M       0xC0  

//
//! Wakeup Pin Enable For LLWU_P15 Shift
//
#define LLWU_PE4_WUPE15_S       6

//
//! Wakeup Pin Enable For LLWU_P15 is External input pin disabled as wakeup input
//
#define LLWU_PE4_WUPE15_DIS     0x00

//
//! Wakeup Pin Enable For LLWU_P15 is External input pin enabled with rising edge detection
//
#define LLWU_PE4_WUPE15_RISING  0x40

//
//! Wakeup Pin Enable For LLWU_P15 is External input pin enabled with falling edge detection
//
#define LLWU_PE4_WUPE15_FALLING 0x80

//
//! Wakeup Pin Enable For LLWU_P15 is External input pin enabled with any change detection
//
#define LLWU_PE4_WUPE15_ANY     0xC0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_LLWU_ME SysCtl LLWU ME Register(SysCtl_LLWU_ME)
//! \brief Defines for the bit fields in the LLWU_ME register.
//! @{
//
//*****************************************************************************

//
//! Wakeup Module Enable For Module 0
//
#define LLWU_ME_WUME0           0x01   

//
//! Wakeup Module Enable For Module 1
//
#define LLWU_ME_WUME1           0x02

//
//! Wakeup Module Enable For Module 2
//
#define LLWU_ME_WUME2           0x04   

//
//! Wakeup Module Enable For Module 3
//
#define LLWU_ME_WUME3           0x08

//
//! Wakeup Module Enable For Module 4
//
#define LLWU_ME_WUME4           0x10   

//
//! Wakeup Module Enable For Module 5
//
#define LLWU_ME_WUME5           0x20

//
//! Wakeup Module Enable For Module 6
//
#define LLWU_ME_WUME6           0x40   

//
//! Wakeup Module Enable For Module 7
//
#define LLWU_ME_WUME7           0x80

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_LLWU_F1 SysCtl LLWU F1 Register(SysCtl_LLWU_F1)
//! \brief Defines for the bit fields in the LLWU_F1 register.
//! @{
//
//*****************************************************************************

//
//! Wakeup Flag For LLWU_P0
//
#define LLWU_F1_WUF0            0x01   

//
//! Wakeup Flag For LLWU_P1
//
#define LLWU_F1_WUF1            0x02

//
//! Wakeup Flag For LLWU_P2
//
#define LLWU_F1_WUF2            0x04   

//
//! Wakeup Flag For LLWU_P3
//
#define LLWU_F1_WUF3            0x08

//
//! Wakeup Flag For LLWU_P4
//
#define LLWU_F1_WUF4            0x10   

//
//! Wakeup Flag For LLWU_P5
//
#define LLWU_F1_WUF5            0x20

//
//! Wakeup Flag For LLWU_P6
//
#define LLWU_F1_WUF6            0x40   

//
//! Wakeup Flag For LLWU_P7
//
#define LLWU_F1_WUF7            0x80

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_LLWU_F2 SysCtl LLWU F2 Register(SysCtl_LLWU_F2)
//! \brief Defines for the bit fields in the LLWU_F2 register.
//! @{
//
//*****************************************************************************

//
//! Wakeup Flag For LLWU_P8
//
#define LLWU_F2_WUF8            0x01   

//
//! Wakeup Flag For LLWU_P9
//
#define LLWU_F2_WUF9            0x02

//
//! Wakeup Flag For LLWU_P10
//
#define LLWU_F2_WUF10           0x04   

//
//! Wakeup Flag For LLWU_P11
//
#define LLWU_F2_WUF11           0x08

//
//! Wakeup Flag For LLWU_P12
//
#define LLWU_F2_WUF12           0x10   

//
//! Wakeup Flag For LLWU_P13
//
#define LLWU_F2_WUF13           0x20

//
//! Wakeup Flag For LLWU_P14
//
#define LLWU_F2_WUF14           0x40   

//
//! Wakeup Flag For LLWU_P15
//
#define LLWU_F2_WUF15           0x80

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_LLWU_F3 SysCtl LLWU F3 Register(SysCtl_LLWU_F3)
//! \brief Defines for the bit fields in the LLWU_F3 register.
//! @{
//
//*****************************************************************************

//
//! Wakeup flag For module 0
//
#define LLWU_F3_MWUF0           0x01   

//
//! Wakeup flag For module  1
//
#define LLWU_F3_MWUF1           0x02

//
//! Wakeup flag For module  2
//
#define LLWU_F3_MWUF2           0x04   

//
//! Wakeup flag For module  3
//
#define LLWU_F3_MWUF3           0x08

//
//! Wakeup flag For module  4
//
#define LLWU_F3_MWUF4           0x10   

//
//! Wakeup flag For module  5
//
#define LLWU_F3_MWUF5           0x20

//
//! Wakeup flag For module  6
//
#define LLWU_F3_MWUF6           0x40   

//
//! Wakeup flag For module  7
//
#define LLWU_F3_MWUF7           0x80

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_LLWU_FILT1 SysCtl LLWU FILT1 Register(SysCtl_LLWU_FILT1)
//! \brief Defines for the bit fields in the LLWU_FILT1 register.
//! @{
//
//*****************************************************************************

//
//! Filter Pin Select Mask
//
#define LLWU_FILT1_FILTSEL_M    0x0F  

//
//! Filter Pin Select Shift
//
#define LLWU_FILT1_FILTSEL_S    0  

//
//! Filter Pin is LLWU_P0
//
#define LLWU_FILT1_FILTSEL_LLWU_P0                                           \
                                0x00  
//
//! Filter Pin is LLWU_P1
//
#define LLWU_FILT1_FILTSEL_LLWU_P1                                           \
                                0x01
//
//! Filter Pin is LLWU_P2
//
#define LLWU_FILT1_FILTSEL_LLWU_P2                                           \
                                0x02  
//
//! Filter Pin is LLWU_P3
//
#define LLWU_FILT1_FILTSEL_LLWU_P3                                           \
                                0x03
//
//! Filter Pin is LLWU_P4
//
#define LLWU_FILT1_FILTSEL_LLWU_P4                                           \
                                0x04  
//
//! Filter Pin is LLWU_P5
//
#define LLWU_FILT1_FILTSEL_LLWU_P5                                           \
                                0x05
//
//! Filter Pin is LLWU_P6
//
#define LLWU_FILT1_FILTSEL_LLWU_P6                                           \
                                0x06  
//
//! Filter Pin is LLWU_P7
//
#define LLWU_FILT1_FILTSEL_LLWU_P7                                           \
                                0x07
//
//! Filter Pin is LLWU_P8
//
#define LLWU_FILT1_FILTSEL_LLWU_P8                                           \
                                0x08  
//
//! Filter Pin is LLWU_P9
//
#define LLWU_FILT1_FILTSEL_LLWU_P9                                           \
                                0x09
//
//! Filter Pin is LLWU_P10
//
#define LLWU_FILT1_FILTSEL_LLWU_P10                                          \
                                0x0A  
//
//! Filter Pin is LLWU_P11
//
#define LLWU_FILT1_FILTSEL_LLWU_P11                                          \
                                0x0B
//
//! Filter Pin is LLWU_P12
//
#define LLWU_FILT1_FILTSEL_LLWU_P12                                          \
                                0x0C  
//
//! Filter Pin is LLWU_P13
//
#define LLWU_FILT1_FILTSEL_LLWU_P13                                          \
                                0x0D
//
//! Filter Pin is LLWU_P14
//
#define LLWU_FILT1_FILTSEL_LLWU_P14                                          \
                                0x0E  
//
//! Filter Pin is LLWU_P15
//
#define LLWU_FILT1_FILTSEL_LLWU_P15                                          \
                                0x0F            

//
//! Digital Filter On External Pin Mask
//
#define LLWU_FILT1_FILTE_M      0x60  

//
//! Digital Filter On External Pin Shift
//
#define LLWU_FILT1_FILTE_S      5 

//
//! Digital Filter On External Pin is Filter disabled
//
#define LLWU_FILT1_FILTE_DIS    0x00

//
//! Digital Filter On External Pin is posedge detect enabled
//
#define LLWU_FILT1_FILTE_RISING 0x20

//
//! Digital Filter On External Pin is  negedge detect enabled
//
#define LLWU_FILT1_FILTE_FALLING                                             \
                                0x40

//
//! Digital Filter On External Pin is ny edge detect enabled
//
#define LLWU_FILT1_FILTE_ANY    0x60

//
//! Filter Detect Flag
//
#define LLWU_FILT1_FILTSEL_FILTF                                             \
                                0x80 
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_LLWU_FILT2 SysCtl LLWU FILT2 Register(SysCtl_LLWU_FILT2)
//! \brief Defines for the bit fields in the LLWU_FILT2 register.
//! @{
//
//*****************************************************************************

//
//! Filter Pin Select Mask
//
#define LLWU_FILT2_FILTSEL_M    0x0F  

//
//! Filter Pin Select Shift
//
#define LLWU_FILT2_FILTSEL_S    0  

//
//! Filter Pin is LLWU_P0
//
#define LLWU_FILT2_FILTSEL_LLWU_P0                                           \
                                0x00  
//
//! Filter Pin is LLWU_P1
//
#define LLWU_FILT2_FILTSEL_LLWU_P1                                           \
                                0x01
//
//! Filter Pin is LLWU_P2
//
#define LLWU_FILT2_FILTSEL_LLWU_P2                                           \
                                0x02  
//
//! Filter Pin is LLWU_P3
//
#define LLWU_FILT2_FILTSEL_LLWU_P3                                           \
                                0x03
//
//! Filter Pin is LLWU_P4
//
#define LLWU_FILT2_FILTSEL_LLWU_P4                                           \
                                0x04  
//
//! Filter Pin is LLWU_P5
//
#define LLWU_FILT2_FILTSEL_LLWU_P5                                           \
                                0x05
//
//! Filter Pin is LLWU_P6
//
#define LLWU_FILT2_FILTSEL_LLWU_P6                                           \
                                0x06  
//
//! Filter Pin is LLWU_P7
//
#define LLWU_FILT2_FILTSEL_LLWU_P7                                           \
                                0x07
//
//! Filter Pin is LLWU_P8
//
#define LLWU_FILT2_FILTSEL_LLWU_P8                                           \
                                0x08  
//
//! Filter Pin is LLWU_P9
//
#define LLWU_FILT2_FILTSEL_LLWU_P9                                           \
                                0x09
//
//! Filter Pin is LLWU_P10
//
#define LLWU_FILT2_FILTSEL_LLWU_P10                                          \
                                0x0A  
//
//! Filter Pin is LLWU_P11
//
#define LLWU_FILT2_FILTSEL_LLWU_P11                                          \
                                0x0B
//
//! Filter Pin is LLWU_P12
//
#define LLWU_FILT2_FILTSEL_LLWU_P12                                          \
                                0x0C  
//
//! Filter Pin is LLWU_P13
//
#define LLWU_FILT2_FILTSEL_LLWU_P13                                          \
                                0x0D
//
//! Filter Pin is LLWU_P14
//
#define LLWU_FILT2_FILTSEL_LLWU_P14                                          \
                                0x0E  
//
//! Filter Pin is LLWU_P15
//
#define LLWU_FILT2_FILTSEL_LLWU_P15                                          \
                                0x0F            

//
//! Digital Filter On External Pin Mask
//
#define LLWU_FILT2_FILTE_M      0x60  

//
//! Digital Filter On External Pin Shift
//
#define LLWU_FILT2_FILTE_S      5 

//
//! Digital Filter On External Pin is Filter disabled
//
#define LLWU_FILT2_FILTE_DIS    0x00

//
//! Digital Filter On External Pin is posedge detect enabled
//
#define LLWU_FILT2_FILTE_RISING 0x20

//
//! Digital Filter On External Pin is  negedge detect enabled
//
#define LLWU_FILT2_FILTE_FALLING                                             \
                                0x40

//
//! Digital Filter On External Pin is ny edge detect enabled
//
#define LLWU_FILT2_FILTE_ANY    0x60

//
//! Filter Detect Flag
//
#define LLWU_FILT2_FILTSEL_FILTF                                             \
                                0x80 
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_RCM_SRS0 SysCtl RCM SRS0 Register(SysCtl_RCM_SRS0)
//! 
//! \brief Defines for the bit fields in the RCM_SRS0 register.
//! @{
//
//*****************************************************************************

//
//! Low Leakage Wakeup Reset
//
#define RCM_SRS0_WAKEUP         0x01  

//
//! Low-Voltage Detect Reset
//
#define RCM_SRS0_LVD            0x02

//
//! Loss-of-Clock Reset
//
#define RCM_SRS0_LOL            0x04 

//
//! Watchdog
//
#define RCM_SRS0_WDOG           0x20

//
//! External Reset Pin
//
#define RCM_SRS0_PIN            0x40

//
//! Power-On Reset
//
#define RCM_SRS0_POR            0x80

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_RCM_SRS1 SysCtl RCM SRS1 Register(SysCtl_RCM_SRS1)
//! 
//! \brief Defines for the bit fields in the RCM_SRS1 register.
//! @{
//
//*****************************************************************************

//
//! Core Lockup
//
#define RCM_SRS1_LOCKUP         0x02

//
//! Software
//
#define RCM_SRS1_SW             0x04 

//
//! MDM-AP System Reset Request
//
#define RCM_SRS1_MDM_AP         0x80

//
//! Stop Mode Acknowledge Error Reset
//
#define RCM_SRS1_SACKERR        0x40

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_RCM_RPFC SysCtl RCM RPFC Register(SysCtl_RCM_RPFC)
//! \brief Defines for the bit fields in the RCM_RPFC register.
//! @{
//
//*****************************************************************************

//
//! Reset Pin Filter Select in Run and Wait Modes Mask
//
#define RCM_RPFC_RSTFLTSRW_M    0x03  

//
//! Reset Pin Filter Select in Run and Wait Modes Shift
//
#define RCM_RPFC_RSTFLTSRW_S    0 

//
//! Reset Pin Filter Select in Run and Wait Modes is disabled
//
#define RCM_RPFC_RSTFLTSRW_DIS  0x00 

//
//! Bus clock filter enabled for normal operation
//
#define RCM_RPFC_RSTFLTSRW_BUS  0x01

//
//! LPO clock filter enabled for normal operation
//
#define RCM_RPFC_RSTFLTSRW_LPO  0x02

//
//! Reset Pin Filter Select in Stop Mode
//
#define RCM_RPFC_RSTFLTSS       0x04

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_RCM_RPFW SysCtl RCM RPFW(SysCtl_RCM_RPFW)
//! \brief Defines for the bit fields in the RCM_RPFW register.
//! @{
//
//*****************************************************************************

//
//! Reset Pin Filter Bus Clock Select Mask
//
#define RCM_RPFW_RSTFLTSEL_M    0x1F  

//
//! Reset Pin Filter Bus Clock Select Shift
//
#define RCM_RPFW_RSTFLTSEL_S    0  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SMC_PMPROT SysCtl SMC PMPROT(SysCtl_SMC_PMPROT)
//! \brief Defines for the bit fields in the SMC_PMPROT register.
//! @{
//
//*****************************************************************************

//
//! Allow Very-Low-Leakage Stop Mode
//
#define SMC_PMPROT_AVLLS        0x02  

//
//! Allow Low-Leakage Stop Mode
//
#define SMC_PMPROT_ALLS         0x08  

//
//! Allow Very-Low-Power Modes
//
#define SMC_PMPROT_AVLP         0x20 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SMC_PMCTRL SysCtl SMC PMCTRL(SysCtl_SMC_PMCTRL)
//! \brief Defines for the bit fields in the SMC_PMCTRL register.
//! @{
//
//*****************************************************************************

//
//! Stop Mode Control Mask
//
#define SMC_PMCTRL_STOPM_M      0x07  

//
//! Stop Mode Control Shift
//
#define SMC_PMCTRL_STOPM_S      0    

//
//! Normal Stop (STOP)
//
#define SMC_PMCTRL_STOPM_NORMAL 0x00

//
//! Very-Low-Power Stop (VLPS)
//
#define SMC_PMCTRL_STOPM_VLPS   0x01

//
//! Low-Leakage Stop (LLS)
//
#define SMC_PMCTRL_STOPM_LLS    0x03

//
//! Very-Low-Leakage Stop (VLLSx)
//
#define SMC_PMCTRL_STOPM_VLLS   0x04

//
//! Stop Aborted
//
#define SMC_PMCTRL_STOPM_STOPA  0x08

//
//! Run Mode Control Mask
//
#define SMC_PMCTRL_RUNM_M       0x60  

//
//! Run Mode Control Shift
//
#define SMC_PMCTRL_RUNM_S       5    

//
//! Normal Run mode (RUN)
//
#define SMC_PMCTRL_RUNM_NORMAL  0x00

//
//! Very-Low-Power Run mode (VLPR)
//
#define SMC_PMCTRL_RUNM_VLPR    0x40
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SMC_STOPCTRL SysCtl SMC STOPCTRL(SysCtl_SMC_STOPCTRL)
//! \brief Defines for the bit fields in the SMC_STOPCTRL register.
//! @{
//
//*****************************************************************************

//
//! VLLS Mode Control Mask
//
#define SMC_STOPCTRL_VLLSM_M    0x07  

//
//! VLLS Mode Control Shift
//
#define SMC_STOPCTRL_VLLSM_S    0    

//
//! VLLS0
//
#define SMC_STOPCTRL_VLLSM_VLLS0                                              \
                                0x00

//
//! VLLS1
//
#define SMC_STOPCTRL_VLLSM_VLLS1                                              \
                                0x01

//
//! VLLS2
//
#define SMC_STOPCTRL_VLLSM_VLLS2                                              \
                                0x02

//
//! VLLS3
//
#define SMC_STOPCTRL_VLLSM_VLLS3                                              \
                                0x03

//
//! POR Power Option
//
#define SMC_STOPCTRL_PORPO      0x20

//
//! Partial Stop Option Mask
//
#define SMC_STOPCTRL_PSTOPO_M   0xC0  

//
//! Partial Stop Option Shift
//
#define SMC_STOPCTRL_PSTOPO_S   6    

//
//! STOP - Normal Stop mode
//
#define SMC_STOPCTRL_PSTOPO_SPOP                                              \
                                0x00

//
//! PSTOP1 - Partial Stop with both system and bus clocks disabled
//
#define SMC_STOPCTRL_PSTOPO_PSTOP1                                            \
                                0x40

//
//! PSTOP2 - Partial Stop with system clock disabled and bus clock enabled
//
#define SMC_STOPCTRL_PSTOPO_PSTOP2                                            \
                                0x80

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup KLx_SysCtl_Register_SMC_PMSTAT SysCtl SMC PMSTAT(SysCtl_SMC_PMSTAT)
//! \brief Defines for the bit fields in the SMC_PMSTAT register.
//! @{
//
//*****************************************************************************

//
//! PMSTAT Mask
//
#define SMC_PMSTAT_PMSTAT_M     0x7F  

//
//! PMSTAT Shift
//
#define SMC_PMSTAT_PMSTAT_S     0    

//
//! Current power mode is RUN
//
#define SMC_PMSTAT_PMSTAT_RUN   0x10

//
//! Current power mode is STOP
//
#define SMC_PMSTAT_PMSTAT_STOP  0x02

//
//! Current power mode is VLPR
//
#define SMC_PMSTAT_PMSTAT_VLPR  0x04

//
//! Current power mode is VLPW
//
#define SMC_PMSTAT_PMSTAT_VLPW  0x08

//
//! Current power mode is VLPS
//
#define SMC_PMSTAT_PMSTAT_VLPS  0x10

//
//! Current power mode is LLS
//
#define SMC_PMSTAT_PMSTAT_LLS   0x20  

//
//! Current power mode is VLLS
//
#define SMC_PMSTAT_PMSTAT_VLLS  0x40 

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

#endif // __XHW_SYSCTL_H_

