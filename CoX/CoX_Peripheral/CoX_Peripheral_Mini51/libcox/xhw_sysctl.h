//*****************************************************************************
//
//! \file xhw_sysctl.h
//! \brief Macros used when accessing the system control hardware.
//! \version V2.1.1.0
//! \date 12/26/2011
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
//! \addtogroup MINI51_SysCtl_Register MINI51 SysCtl Register
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
//! \addtogroup MINI51_SysCtl_Register_Offsets MINI51 SysCtl Register Offsets(Map)
//! \brief Defines for the system control register addresses.through 
//! <b>SysCtl_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! Product ID register
//
#define GCR_PDID                0x50000000

//
//! System Reset Source Register
//
#define GCR_RSTSRC              0x50000004

//
//! IP Reset Control Register1
//
#define GCR_IPRSTC1             0x50000008

//
//! IP Reset Control Register2
//
#define GCR_IPRSTC2             0x5000000C

//
//! Brown-Out Detector Control Register
//
#define GCR_BODCR               0x50000018

//
//! Multiple Function Pin GPIOA Control Register
//
#define GCR_GPAMFP              0x50000030

//
//! Multiple Function Pin GPIOB Control Register
//
#define GCR_GPBMFP              0x50000034

//
//! Multiple Function Pin GPIOC Control Register
//
#define GCR_GPCMFP              0x50000038

//
//! Multiple Function Pin GPIOD Control Register
//
#define GCR_GPDMFP              0x5000003C

//
//! Multiple Function Pin GPIOE Control Register
//
#define GCR_GPEMFP              0x50000040
    
//
//! Multiple Function Pin GPIOF Control Register
//
#define GCR_GPFMFP              0x50000044

//
//! HIRC Trim Control Register 
//
#define GCR_IRCTRIMCTL          0x50000080

//
//! HIRC Trim Interrupt Enable Register 
//
#define GCR_IRCTRIMIEN          0x50000084

//
//! HIRC Trim Interrupt Status Register
// 
#define GCR_IRCTRIMINT          0x50000088 

//
//! Register Lock Key Address Register
//
#define GCR_REGLOCK             0x50000100  

//
//! System Power Down Control Register
//
#define SYSCLK_PWRCON           0x50000200  

//
//! AHB Devices Clock Enable Control Register
//
#define SYSCLK_AHBCLK           0x50000204  

//
//! APB Devices Clock Enable Control Register
//
#define SYSCLK_APBCLK           0x50000208

//
//! Clock Status Monitor Register
//
#define SYSCLK_CLKSTATUS        0x5000020C

//
//! Clock Source Select Control Register 0
//
#define SYSCLK_CLKSEL0          0x50000210

//
//! Clock Source Select Control Register 1
//
#define SYSCLK_CLKSEL1          0x50000214

//
//! Clock Divider Number Register
//
#define SYSCLK_CLKDIV           0x50000218

//
//! Clock Source Select Control Register 2
//
#define SYSCLK_CLKSEL2          0x5000021C

//
//! Frequency Divider Control Register
//
#define SYSCLK_FRQDIV           0x50000224 

//
//! IRQ0 (BOD) interrupt source identify
//
#define GCR_INT_INT0SRC         0x50000300 

//
//! IRQ1 (WDT) interrupt source identify
//
#define GCR_INT_INT1SRC         0x50000304

//
//! IRQ2 (EINT0) interrupt source identify
//
#define GCR_INT_INT2SRC         0x50000308

//
//! IRQ3 (EINT1) interrupt source identify
//
#define GCR_INT_INT3SRC         0x5000030C

//
//! IRQ4 (GPA/B) interrupt source identify
//
#define GCR_INT_INT4SRC         0x50000310

//
//! IRQ5 (GPC/D/E) interrupt source identify
//
#define GCR_INT_INT5SRC         0x50000314

//
//! IRQ6 (PWM) interrupt source identify
//
#define GCR_INT_INT6SRC         0x50000318

//
//! IRQ7 (BREAK) interrupt source identify
//
#define GCR_INT_INT7SRC         0x5000031C

//
//! IRQ8 (TMR0)) interrupt source identify
//
#define GCR_INT_INT8SRC         0x50000320

//
//! IRQ9 (TMR1)) interrupt source identify
//
#define GCR_INT_INT9SRC         0x50000324

//
//! IRQ12 (URT0) interrupt source identify
//
#define GCR_INT_INT12SRC        0x50000330

//
//! IRQ14 (SPI) interrupt source identify
//
#define GCR_INT_INT14SRC        0x50000338

//
//! IRQ16 (GP5) interrupt source identify
//
#define GCR_INT_INT16SRC        0x50000340

//
//! IRQ17 (HFIRC) interrupt source identify
//
#define GCR_INT_INT17SRC        0x50000344

//
//! IRQ18 (I2C) interrupt source identify
//
#define GCR_INT_INT18SRC        0x50000348

//
//! IRQ25 (ACMP) interrupt source identify
//
#define GCR_INT_INT25SRC        0x50000364 

//
//! IRQ28 (PWRWU) interrupt source identify
//
#define GCR_INT_INT28SRC        0x50000370  

//
//! IRQ29 (ADC) interrupt source identify
//
#define GCR_INT_INT29SRC        0x50000374

//
//! NMI Interrupt Source Select Control Register
//
#define GCR_INT_NMISEL          0x50000380  

//
//! Interrupt Request Source Register
//
#define GCR_INT_MCUIRQ          0x50000384  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_GCR_PDID SysCtl Register GCR PDID(SysCtl_GCR_PDID)
//! @{
//
//*****************************************************************************

//
//! Product ID
//
#define GCR_PDID_ID_M           0xFFFFFFFF  
#define GCR_PDID_ID_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_GCR_RSTSRC SysCtl Register GCR RSTSRC(SysCtl_GCR_RSTSRC) 
//! @{
//
//*****************************************************************************

//
//! "reset signal" from Power-On Reset
//
#define GCR_RSTSRC_POR          0x00000001  

//
//! "reset signal" from the /RESET pin
//
#define GCR_RSTSRC_PAD          0x00000002  

//
//! "reset signal" from the Watch-Dog
//
#define GCR_RSTSRC_WDG          0x00000004 

//
//! "reset signal" from Brown-Out-Detected
//
#define GCR_RSTSRC_BOD          0x00000010  

//
//! "reset signal" from MCU Cortex_M0 kernel
//
#define GCR_RSTSRC_SYS          0x00000020  

//
//! "reset signal" from CPU_RST (IPRSTCR1[1])
//
#define GCR_RSTSRC_CPU          0x00000080  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_GCR_IPRSTC1 SysCtl GCR IPRSTC1 Register(SysCtl_GCR_IPRSTC1)
//! @{
//
//*****************************************************************************

//
//! CHIP one shot reset
//
#define GCR_IPRSTC1_CHIP        0x00000001  

//
//! CPU kernel one shot reset.
//
#define GCR_IPRSTC1_CPU         0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_GCR_IPRSTC2 SysCtl GCR IPRSTC2 Register(SysCtl_GCR_IPRSTC2)
//! @{
//
//*****************************************************************************

//
//! GPIO controller Reset
//
#define GCR_IPRSTC2_GPIO        0x00000002  

//
//! TMR0 controller Reset
//
#define GCR_IPRSTC2_TMR0        0x00000004  

//
//! TMR1 controller Reset
//
#define GCR_IPRSTC2_TMR1        0x00000008  

//
//! I2C1 controller Reset
//
#define GCR_IPRSTC2_I2C0        0x00000100  

//
//! SPI0 controller Reset
//
#define GCR_IPRSTC2_SPI0        0x00001000  

//
//! UART0 controller Reset
//
#define GCR_IPRSTC2_UART0       0x00010000

//
//! PWM03 controller Reset
//
#define GCR_IPRSTC2_PWM         0x00100000

//
//! ACMP controller Reset
//
#define GCR_IPRSTC2_ACMP        0x00400000

//
//! ADC controller Reset
//
#define GCR_IPRSTC2_ADC        0x10000000 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_GCR_BODCR SysCtl GCR BODCR Register(SysCtl_GCR_BODCR)
//! @{
//
//*****************************************************************************

//
//! Brown Out Detector Threshold Voltage Selection mask
//
#define GCR_BODCR_BOD_VL_M      0x00000006  

//
//! Brown Out Detector Threshold Voltage is 2.7V
//
#define GCR_BODCR_BOD_VL_2_7V   0x00000001
    
//
//! Brown Out Detector Threshold Voltage is 3.8V
//
#define GCR_BODCR_BOD_VL_3_8V   0x00000002

//
//£¡ Disable the Threshold Voltage 2.7V and 3.8V
//
#define GCR_BODCR_BOD_VL_DIS    0x00000006

//
//! Brown Out Detector Threshold Voltage Selection shift
//
#define GCR_BODCR_BOD_VL_S      1

//
//! Brown Out Reset Enable
//
#define GCR_BODCR_BOD_RSTEN     0x00000008  

//
//! Brown Out Detector Interrupt Flag
//
#define GCR_BODCR_BOD_INTF      0x00000010  

//
//! The status for Brown Out Detector output state
//
#define GCR_BODCR_BOD_OUT       0x00000040  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_GCR_HFIRC SysCtl GCR HFIRC Register(SysCtl_GCR_IRCTRIMCTL)
//! @{
//
//****************************************************************************

//
//! Trim Frequency Selection
//
#define GCR_IRCTRIMCTL_TRIM_SEL                                               \
                                0x00000001

//
//! Trim Calculation Loop mask
//
#define GCR_IRCTRIMCTL_TRIM_LOOP_M                                            \
                                0x00000030

//
//! Trim Calculation Loop shift
//
#define GCR_IRCTRIMCTL_TRIM_LOOP_S                                            \
                                4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_GCR_IRCTRIMIEN SysCtl GCR HFIRC Int En Register(SysCtl_GCR_IRCTRIMIEN)
//! @{
//
//****************************************************************************

//
//! Trim Failure Interrupt Enable
//
#define GCR_IRCTRIMIEN_TRIM_FAIL_IEN                                          \
                                0x00000002

//
//! 32.768 KHz Clock Error Interrupt Enable 
//
#define GCR_IRCTRIMIEN_32K_ERR_IEN                                            \
                                0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_GCR_IRCTRIMINT SysCtl GCR HFIRC Int Status Register(SysCtl_GCR_IRCTRIMINT)
//! @{
//
//****************************************************************************

//
//! HIRC Frequency Lock Status
//
#define GCR_IRCTRIMINT_FREQ_LOCK                                              \
                                0x00000001

//
//! Trim Failure Interrupt Status
//
#define GCR_IRCTRIMINT_TRIM_FAIL_INT                                          \
                                0x00000002

//
//! 32.768 KHz Clock Error Interrupt Status
//
#define GCR_IRCTRIMINT_32K_ERR_INT                                            \
                                0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_GCR_REGLOCK SysCtl GCR_REGLOCK Register(SysCtl_GCR_REGLOCK)
//! @{
//
//*****************************************************************************

//
//! Protected registers are lock FLAG
//
#define GCR_REGLOCK_REGUNLOCK   0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_SYSCLK_PWRCON SysCtl PWRCON Register(SysCtl_SYSCLK_PWRCON)
//! @{
//
//*****************************************************************************

//
//! External 12 MHz or 32 KHz Crystal Oscillator Control mask
//
#define SYSCLK_PWRCON_XTLCLK_EN_M                                             \
                                0x00000003

//
//! External 12 MHz or 32 KHz Crystal Oscillator Control shift
//
#define SYSCLK_PWRCON_XTLCLK_EN_S                                             \
                                0

//
//! External 12 MHz Crystal Oscillator Enable
//
#define SYSCLK_PWRCON_XTL12M_EN 0x00000001

//
//! External 32 KHz Crystal Oscillator Enable
//
#define SYSCLK_PWRCON_XTL32K_EN 0x00000010

//
//! XTAL1 is external clock input pin, XTAL2 is GPIO
//
#define SYSCTL_PWRCON_XTAL1     0x00000011

//
//! Internal 22.1184 MHz Oscillator Control
//
#define SYSCLK_PWRCON_OSC22M_EN 0x00000004  

//
//! Internal 10 kHz Oscillator Control
//
#define SYSCLK_PWRCON_OSC10K_EN 0x00000008  

//
//! Enable the wake up delay counter.
//
#define SYSCLK_PWRCON_WU_DLY    0x00000010  

//
//! Power down mode wake Up Interrupt Enable
//
#define SYSCLK_PWRCON_PD_INT_EN 0x00000020  

//
//! Chip power down wake up status flag
//
#define SYSCLK_PWRCON_PD_WU_STS 0x00000040  

//
//! System power down active or enable
//
#define SYSCLK_PWRCON_PWR_DO_EN 0x00000080 

//
//! control the crystal oscillator active or not in power down mode
//
#define SYSCLK_PWRCON_32K                                                     \
                                0x00000200  
                                
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_SYSCLK_AHBCLK SysCtl AHBCLK Register(SysCtl_SYSCLK_AHBCLK)
//! @{
//
//*****************************************************************************

//
//! Flash ISP Controller Clock Enable Control.
//
#define SYSCLK_AHBCLK_ISP_EN    0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_SYSCLK_APBCLK SysCtl SYSCLK APBCLK Register(SysCtl_SYSCLK_APBCLK)
//! @{
//
//*****************************************************************************

//
//! Watch Dog Clock Enable.
//
#define SYSCLK_APBCLK_WDCLK_EN  0x00000001 

//
//! Timer0 Clock Enable Control
//
#define SYSCLK_APBCLK_TMR0_EN   0x00000004  

//
//! Timer1 Clock Enable Control
//
#define SYSCLK_APBCLK_TMR1_EN   0x00000008  

//
//! Clock Divider Clock Enable
//
#define SYSCLK_APBCLK_FDIV_EN   0x00000040

//
//! I2C0 Clock Enable Control.
//
#define SYSCLK_APBCLK_I2C0_EN   0x00000100  

//
//! SPI0 Clock Enable Control.
//
#define SYSCLK_APBCLK_SPI0_EN   0x00001000  

//
//! UART0 Clock Enable Control.
//
#define SYSCLK_APBCLK_UART0_EN  0x00010000  

//
//! PWM_01 Clock Enable Control.
//
#define SYSCLK_APBCLK_PWM01_EN  0x00100000  

//
//! PWM_23 Clock Enable Control.
//
#define SYSCLK_APBCLK_PWM23_EN  0x00200000

//
//! PWM_45 Clock Enable Control.
//
#define SYSCLK_APBCLK_PWM45_EN  0x00400000  

//
//! Analog-Digital-Converter (ADC) Clock Enable
//
#define SYSCLK_APBCLK_ADC_EN    0x10000000  

//
//! Analog Comparator Clock Enable.
//
#define SYSCLK_APBCLK_ACMP_EN   0x40000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_SYSCLK_CLKSTATUS SysCtl CLKSTATUS(SysCtl_SYSCLK_CLKSTATUS)
//! @{
//
//*****************************************************************************

//
//! Clock switch fail flag.
//
#define SYSCLK_CLKSTATUS_CLKSWFAIL                                            \
                                0x00000080  
//
//! OSC22M (Internal 22.1184 MHz) clock source stable flag (Read Only)
//
#define SYSCLK_CLKSTATUS_OSC22M_STB                                           \
                                0x00000010  
//
//! OSC10K clock source stable flag (Read Only).
//
#define SYSCLK_CLKSTATUS_OSC10K_STB                                           \
                                0x00000008  
//
//! External Crystal clock source stable flag (Read Only).
//
#define SYSCLK_CLKSTATUS_XTL_STB                                           \
                                0x00000001
                                
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_SYSCLK_CLKSEL0 SysCtl CLKSEL0(SysCtl_SYSCLK_CLKSEL0)
//! @{
//
//*****************************************************************************

//
//! HCLK clock source select mask.
//
#define SYSCLK_CLKSEL0_HCLK_M   0x00000007  

//
//! HCLK clock source is external 12 MHz or 32 KHz crystal clock
//
#define SYSCLK_CLKSEL0_HCLK12M  0x00000000   

//
//! HCLK clock source is internal 10 kHz oscillator clock.
//
#define SYSCLK_CLKSEL0_HCLK10K  0x00000003  

//
//! HCLK clock source is internal 22.1184 MHz oscillator clock.
//
#define SYSCLK_CLKSEL0_HCLK22M  0x00000007  

//
//! MCU Cortex_M0 SysTick clock source select mask.
//
#define SYSCLK_CLKSEL0_STCLK_M  0x00000038 

//
//! MCU Cortex_M0 SysTick clock source is 12 MHz or 32 KHz crystal clock.
//
#define SYSCLK_CLKSEL0_STCLK12M 0x00000000  

//
//! MCU Cortex_M0 SysTick clock source is 12 MHz or 32 KHz crystal clock/2.
//
#define SYSCLK_CLKSEL0_STCLK12M_2                                             \
                                0x00000010  
                                
//
//! MCU Cortex_M0 SysTick clock source is HCLK/2.
//
#define SYSCLK_CLKSEL0_STCLKHCLK_2                                            \
                                0x00000018  
                                
//
//! MCU Cortex_M0 SysTick clock source is internal 22.1148 MHz oscillator clock/2.
//
#define SYSCLK_CLKSEL0_STCLKINT22M_2                                          \
                                0x00000038  
 
//
//! HCLK clock source select shift.
//                               
#define SYSCLK_CLKSEL0_HCLK_S   0
 
//
//! MCU Cortex_M0 SysTick clock source select shift.
//   
#define SYSCLK_CLKSEL0_STCLK_S  3

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_SYSCLK_CLKSEL1 SysCtl CLKSEL1 Register(SysCtl_SYSCLK_CLKSEL1)
//! @{
//
//*****************************************************************************
 
//
//! WDG CLK clock source select mask.
//  
#define SYSCLK_CLKSEL1_WDG_M    0x00000003

//
//! ADC clock source select mask.
//  
#define SYSCLK_CLKSEL1_ADC_M    0x0000000C
 
//
//! TIMER0 clock source select mask.
//  
#define SYSCLK_CLKSEL1_TMR0_M   0x00000700  
 
//
//! TIMER1 clock source select mask.
//  
#define SYSCLK_CLKSEL1_TMR1_M   0x00007000  
 
//
//! UART clock source select mask.
//  
#define SYSCLK_CLKSEL1_UART_M   0x03000000
 
//
//! PWM0 and PWM1 clock source select mask.
//  
#define SYSCLK_CLKSEL1_PWM01_M  0x30000000  
 
//
//! PWM2 and PWM3 clock source select mask.
//  
#define SYSCLK_CLKSEL1_PWM23_M  0xC0000000  
 
//
//! WDG CLK clock source select shift.
// 
#define SYSCLK_CLKSEL1_WDG_S    0

//
//! ADC CLK clock source select shift.
// 
#define SYSCLK_CLKSEL1_ADC_S    2
 
//
//! TIMER0 clock source select shift.
// 
#define SYSCLK_CLKSEL1_TMR0_S   8
 
//
//! TIMER1 clock source select shift.
// 
#define SYSCLK_CLKSEL1_TMR1_S   12
 
//
//! TIMER2 clock source select shift.
// 
#define SYSCLK_CLKSEL1_TMR2_S   16
 
//
//! UART clock source select shift.
// 
#define SYSCLK_CLKSEL1_UART_S   24
 
//
//! PWM0 and PWM1 clock source select shift.
//  
#define SYSCLK_CLKSEL1_PWM01_S  28
 
//
//! PWM2 and PWM3 clock source select shift.
//  
#define SYSCLK_CLKSEL1_PWM23_S  30

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_SYSCLK_CLKSEL2 SysCtl CLKSEL2 Register(SysCtl_SYSCLK_CLKSEL2)
//! @{
//
//***************************************************************************** 
 
//
//! Clock Divider Clock Source Select mask.
//
#define SYSCLK_CLKSEL2_FRQDIV_M 0x0000000C  
 
//
//! PWM4 and PWM5 clock source select mask.
//
#define SYSCLK_CLKSEL2_PWM45_M  0x00000030
 
//
//! Clock Divider Clock Source Select shift.
//
#define SYSCLK_CLKSEL2_FRQDIV_S 2
 
//
//! PWM4 and PWM5 clock source select shift.
//
#define SYSCLK_CLKSEL2_PWM45_S  4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_SYSCLK_CLKDIV SysCtl CLKDIV Register(SysCtl_SYSCLK_CLKDIV)
//! @{
//
//*****************************************************************************
 
//
//! HCLK clock divide number mask.
//
#define SYSCLK_CLKDIV_HCLK_M    0x0000000F 
 
//
//! UART clock divide number mask.
//
#define SYSCLK_CLKDIV_UART_M    0x00000F00

//
//! ADC clock divide number mask.
//
#define SYSCLK_CLKDIV_ADC_M     0x00FF0000 

//
//! HCLK clock divide number shift.
//
#define SYSCLK_CLKDIV_HCLK_S    0
 
//
//! UART clock divide number shift.
//
#define SYSCLK_CLKDIV_UART_S    8

//
//! ADC clock divide number shift.
//
#define SYSCLK_CLKDIV_ADC_S     16
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MINI51_SysCtl_Register_SYSCLK_FRQDIV SysCtl FRQDIV Register(SysCtl_SYSCLK_FRQDIV)
//! @{
//
//*****************************************************************************
 
//
//! Divider Output Frequency Selection Bits mask.
//
#define SYSCLK_FRQDIV_FSEL_M    0x0000000F  
 
//
//! Divider Output Frequency Selection Bits shift.
//
#define SYSCLK_FRQDIV_FSEL_S    0
 
//
//! Frequency Divider Enable Bit.
//
#define SYSCLK_FRQDIV_FDIV_EN   0x00000010  

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



