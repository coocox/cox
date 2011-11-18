//*****************************************************************************
//
//! \file xhw_sysctl.h
//! \brief Macros used when accessing the system control hardware.
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
//! \addtogroup NUC1xx_SysCtl_Register NUC1xx SysCtl Register
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
//! \addtogroup NUC1xx_SysCtl_Register_Offsets NUC1xx SysCtl Register Offsets(Map)
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
//! Power-On-Reset Control Register
//
#define GCR_PORCR               0x50000024  

//
//! Temperature Sensor Control Register
//
#define GCR_TEMPCR              0x5000001C  

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
//! Alternative Multiple Function Pin Control Register
//
#define GCR_ALTMFP              0x50000050  
                                            
//
//! Register Lock Key Address Register
//
#define GCR_REGLOCK             0x50000100  

//
//! RC Adjustment Control Register
//
#define GCR_RCADJ               0x50000110  

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
//! Clock Source Select Control Register 0
//
#define SYSCLK_CLKSEL0          0x50000210 

//
//! Clock Source Select Control Register 1
//
#define SYSCLK_CLKSEL1          0x50000214  

//
//! Clock Source Select Control Register 2
//
#define SYSCLK_CLKSEL2          0x5000021C  

//
//! Clock Divider Number Register
//
#define SYSCLK_CLKDIV           0x50000218  

//
//! PLL Control Register
//
#define SYSCLK_PLLCON           0x50000220  

//
//! Frequency Divider Control Register
//
#define SYSCLK_FRQDIV           0x50000224  

//
//! IRQ0 (BOD) interrupt source identify
//
#define GCR_INT_INT0SRC         0x50000300  

//
//! IRQ1 (WDG) interrupt source identify
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
//! IRQ6 (PWM0/2) interrupt source identify
//
#define GCR_INT_INT6SRC         0x50000318  

//
//! IRQ7 (PWM1/3) interrupt source identify
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
//! IRQ10 (TMR2)) interrupt source identify
//
#define GCR_INT_INT10SRC        0x50000328  

//
//! IRQ11 (TMR3)) interrupt source identify
//
#define GCR_INT_INT11SRC        0x5000032C  

//
//! IRQ12 (URT02) interrupt source identify
//
#define GCR_INT_INT12SRC        0x50000330  

//
//! IRQ13 (URT1) interrupt source identify
//
#define GCR_INT_INT13SRC        0x50000334  

//
//! IRQ14 (SPI0) interrupt source identify
//
#define GCR_INT_INT14SRC        0x50000338  

//
//! IRQ15 (SPI1) interrupt source identify
//
#define GCR_INT_INT15SRC        0x5000033C  

//
//! IRQ16 (SPI2) interrupt source identify
//
#define GCR_INT_INT16SRC        0x50000340  

//
//! IRQ17 (SPI3) interrupt source identify
//
#define GCR_INT_INT17SRC        0x50000344  

//
//! IRQ18 (I2C0) interrupt source identify
//
#define GCR_INT_INT18SRC        0x50000348  

//
//! IRQ19 (I2C1) interrupt source identify
//
#define GCR_INT_INT19SRC        0x5000034C  

//
//! IRQ20 (CAN0) interrupt source identify
//
#define GCR_INT_INT20SRC        0x50000350  

//
//! IRQ21 (Reserved) interrupt source identify
//
#define GCR_INT_INT21SRC        0x50000354  

//
//! IRQ22 (Reserved) interrupt source identify
//
#define GCR_INT_INT22SRC        0x50000358  

//
//! IRQ23 (USBD) interrupt source identify
//
#define GCR_INT_INT23SRC        0x5000035C  

//
//! IRQ24 (PS2) interrupt source identify
//
#define GCR_INT_INT24SRC        0x50000360  

//
//! IRQ25 (ACMP) interrupt source identify
//
#define GCR_INT_INT25SRC        0x50000364  

//
//! IRQ26 (PDMA) interrupt source identify
//
#define GCR_INT_INT26SRC        0x50000368  

//
//! IRQ27 (Reserved) interrupt source identify
//
#define GCR_INT_INT27SRC        0x5000036C  

//
//! IRQ28 (PWRWU) interrupt source identify
//
#define GCR_INT_INT28SRC        0x50000370  

//
//! IRQ29 (ADC) interrupt source identify
//
#define GCR_INT_INT29SRC        0x50000374  

//
//! IRQ30 (Reserved) interrupt source identify
//
#define GCR_INT_INT30SRC        0x50000378  

//
//! IRQ31 (RTC) interrupt source identify
//
#define GCR_INT_INT31SRC        0x5000037C  

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
//! \addtogroup NUC1xx_SysCtl_Register_GCR_PDID SysCtl Register GCR PDID(SysCtl_GCR_PDID)
//! \brief Defines for the bit fields in the GCR_PDID register.
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
//! \addtogroup NUC1xx_SysCtl_Register_GCR_RSTSRC SysCtl Register GCR RSTSRC(SysCtl_GCR_RSTSRC) 
//! \brief Defines for the bit fields in the GCR_RSTSRC register.
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
//! "reset signal" from Low-Voltage-Reset
//
#define GCR_RSTSRC_LVR          0x00000008  

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
//! \addtogroup NUC1xx_SysCtl_Register_GCR_IPRSTC1 SysCtl GCR IPRSTC1 Register(SysCtl_GCR_IPRSTC1)
//! \brief Defines for the bit fields in the GCR_IPRSTC1 register.
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

//
//! PDMA Controller Reset
//
#define GCR_IPRSTC1_PDMA        0x00000004  

//
//! EBI Controller Reset
//
#define GCR_IPRSTC1_EBI         0x00000008  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_IPRSTC2 SysCtl GCR IPRSTC2 Register(SysCtl_GCR_IPRSTC2)
//! \brief Defines for the bit fields in the GCR_IPRSTC2 register.
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
//! TMR2 controller Reset
//
#define GCR_IPRSTC2_TMR2        0x00000010  

//
//! TMR3 controller Reset
//
#define GCR_IPRSTC2_TMR3        0x00000020  

//
//! I2C2 controller Reset
//
#define GCR_IPRSTC2_I2C0        0x00000100  

//
//! I2C1 controller Reset
//
#define GCR_IPRSTC2_I2C1        0x00000200  

//
//! SPI0 controller Reset
//
#define GCR_IPRSTC2_SPI0        0x00001000  

//
//! SPI1 controller Reset
//
#define GCR_IPRSTC2_SPI1        0x00002000  

//
//! SPI2 controller Reset
//
#define GCR_IPRSTC2_SPI2        0x00004000  

//
//! SPI3 controller Reset
//
#define GCR_IPRSTC2_SPI3        0x00008000  

//
//! UART0 controller Reset
//
#define GCR_IPRSTC2_UART0       0x00010000  

//
//! UART1 controller Reset
//
#define GCR_IPRSTC2_UART1       0x00020000  

//
//! UART2 controller Reset
//
#define GCR_IPRSTC2_UART2       0x00040000  

//
//! PWM47 controller Reset
//
#define GCR_IPRSTC2_PWM03       0x00100000  

//
//! PWM03 controller Reset
//
#define GCR_IPRSTC2_PWM47       0x00200000  

//
//! ACMP controller Reset
//
#define GCR_IPRSTC2_ACMP        0x00400000  

//
//! PS2 controller Reset
//
#define GCR_IPRSTC2_PS2         0x00800000  

//
//! CAN0 controller Reset
//
#define GCR_IPRSTC2_CAN0        0x01000000  

//
//! USBD controller Reset
//
#define GCR_IPRSTC2_USBD        0x08000000  

//
//! ADC controller Reset
//
#define GCR_IPRSTC2_ADC         0x10000000  

//
//! I2S controller Reset
//
#define GCR_IPRSTC2_I2S         0x20000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_BODCR SysCtl GCR BODCR Register(SysCtl_GCR_BODCR)
//! \brief Defines for the bit fields in the GCR_BODCR register.
//! @{
//
//*****************************************************************************

//
//! Brown Out Detector Enable
//
#define GCR_BODCR_BOD_EN        0x00000001  

//
//! Brown Out Detector Threshold Voltage Selection mask
//
#define GCR_BODCR_BOD_VL_M      0x00000006  
                                            
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
//! Brown Out Detector Low power Mode
//
#define GCR_BODCR_BOD_LPM       0x00000020  

//
//! The status for Brown Out Detector output state
//
#define GCR_BODCR_BOD_OUT       0x00000040  
                                            
//
//! Low Voltage Reset Enable
//
#define GCR_BODCR_LVR_EN        0x00000080  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_PORCR SysCtl GCR PORCR Register(SysCtl_GCR_PORCR)
//! \brief Defines for the bit fields in the GCR_PORCR register.
//! @{
//
//*****************************************************************************

//
//! POR_DIS_CODE mask
//
#define GCR_PORCR_DIS_CODE_M    0x0000FFFF  

//
//! POR_DIS_CODE shift
//
#define GCR_PORCR_DIS_CODE_S    0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_TEMPCR SysCtl GCR TEMPCR Register(SysCtl_GCR_TEMPCR)
//! \brief Defines for the bit fields in the GCR_TEMPCR register.
//! @{
//
//****************************************************************************

//
//! Temperature sensor Enable
//
#define GCR_TEMPCR_VTEMP_EN     0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_GPAMFP SysCtl GCR GPAMFP Register(SysCtl_GCR_GPAMFP)
//! \brief Defines for the bit fields in the GCR_GPAMFP register.
//! @{
//
//*****************************************************************************

//
//! PA.0 Pin Function Selection
//
#define GCR_GPAMFP_MFP0         0x00000001  

//
//! PA.1 Pin Function Selection
//
#define GCR_GPAMFP_MFP1         0x00000002  

//
//! PA.2 Pin Function Selection
//
#define GCR_GPAMFP_MFP2         0x00000004  

//
//! PA.3 Pin Function Selection
//
#define GCR_GPAMFP_MFP3         0x00000008  

//
//! PA.4 Pin Function Selection
//
#define GCR_GPAMFP_MFP4         0x00000010  

//
//! PA.5 Pin Function Selection
//
#define GCR_GPAMFP_MFP5         0x00000020  

//
//! PA.6 Pin Function Selection
//
#define GCR_GPAMFP_MFP6         0x00000040  

//
//! PA.7 Pin Function Selection
//
#define GCR_GPAMFP_MFP7         0x00000080  

//
//! PA.8 Pin Function Selection
//
#define GCR_GPAMFP_MFP8         0x00000100  

//
//! PA.9 Pin Function Selection
//
#define GCR_GPAMFP_MFP9         0x00000200  

//
//! PA.10 Pin Function Selection
//
#define GCR_GPAMFP_MFP10        0x00000400  

//
//! PA.11 Pin Function Selection
//
#define GCR_GPAMFP_MFP11        0x00000800  

//
//! PA.12 Pin Function Selection
//
#define GCR_GPAMFP_MFP12        0x00001000  

//
//! PA.13 Pin Function Selection
//
#define GCR_GPAMFP_MFP13        0x00002000  

//
//! PA.14 Pin Function Selection
//
#define GCR_GPAMFP_MFP14        0x00004000  

//
//! PA.15 Pin Function Selection
//
#define GCR_GPAMFP_MFP15        0x00008000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_GPBMFP SysCtl GCR GPBMFP Register(SysCtl_GCR_GPBMFP)
//! \brief Defines for the bit fields in the GCR_GPBMFP register.
//! @{
//
//*****************************************************************************

//
//! PB.0 Pin Function Selection
//
#define GCR_GPBMFP_MFP0         0x00000001  

//
//! PB.1 Pin Function Selection
//
#define GCR_GPBMFP_MFP1         0x00000002  

//
//! PB.2 Pin Function Selection
//
#define GCR_GPBMFP_MFP2         0x00000004  

//
//! PB.3 Pin Function Selection
//
#define GCR_GPBMFP_MFP3         0x00000008  

//
//! PB.4 Pin Function Selection
//
#define GCR_GPBMFP_MFP4         0x00000010  

//
//! PB.5 Pin Function Selection
//
#define GCR_GPBMFP_MFP5         0x00000020  

//
//! PB.6 Pin Function Selection
//
#define GCR_GPBMFP_MFP6         0x00000040  

//
//! PB.7 Pin Function Selection
//
#define GCR_GPBMFP_MFP7         0x00000080  

//
//! PB.8 Pin Function Selection
//
#define GCR_GPBMFP_MFP8         0x00000100  

//
//! PB.9 Pin Function Selection
//
#define GCR_GPBMFP_MFP9         0x00000200  

//
//! PB.10 Pin Function Selection
//
#define GCR_GPBMFP_MFP10        0x00000400  

//
//! PB.11 Pin Function Selection
//
#define GCR_GPBMFP_MFP11        0x00000800  

//
//! PB.12 Pin Function Selection
//
#define GCR_GPBMFP_MFP12        0x00001000  

//
//! PB.13 Pin Function Selection
//
#define GCR_GPBMFP_MFP13        0x00002000  

//
//! PB.14 Pin Function Selection
//
#define GCR_GPBMFP_MFP14        0x00004000  

//
//! PB.15 Pin Function Selection
//
#define GCR_GPBMFP_MFP15        0x00008000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_GPCMFP SysCtl GCR GPCMFP Register(SysCtl_GCR_GPCMFP)
//! \brief Defines for the bit fields in the GCR_GPCMFP register.
//! @{
//
//*****************************************************************************

//
//! PC.0 Pin Function Selection
//
#define GCR_GPCMFP_MFP0         0x00000001  

//
//! PC.1 Pin Function Selection
//
#define GCR_GPCMFP_MFP1         0x00000002  

//
//! PC.2 Pin Function Selection
//
#define GCR_GPCMFP_MFP2         0x00000004  

//
//! PC.3 Pin Function Selection
//
#define GCR_GPCMFP_MFP3         0x00000008  

//
//! PC.4 Pin Function Selection
//
#define GCR_GPCMFP_MFP4         0x00000010  

//
//! PC.5 Pin Function Selection
//
#define GCR_GPCMFP_MFP5         0x00000020  

//
//! PC.6 Pin Function Selection
//
#define GCR_GPCMFP_MFP6         0x00000040  

//
//! PC.7 Pin Function Selection
//
#define GCR_GPCMFP_MFP7         0x00000080  

//
//! PC.8 Pin Function Selection
//
#define GCR_GPCMFP_MFP8         0x00000100  

//
//! PC.9 Pin Function Selection
//
#define GCR_GPCMFP_MFP9         0x00000200  

//
//! PC.10 Pin Function Selection
//
#define GCR_GPCMFP_MFP10        0x00000400  

//
//! PC.11 Pin Function Selection
//
#define GCR_GPCMFP_MFP11        0x00000800  

//
//! PC.12 Pin Function Selection
//
#define GCR_GPCMFP_MFP12        0x00001000  

//
//! PC.13 Pin Function Selection
//
#define GCR_GPCMFP_MFP13        0x00002000  

//
//! PC.14 Pin Function Selection
//
#define GCR_GPCMFP_MFP14        0x00004000  

//
//! PC.15 Pin Function Selection
//
#define GCR_GPCMFP_MFP15        0x00008000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_GPDMFP SysCtl GCR GPDMFP Register(SysCtl_GCR_GPDMFP)
//! \brief Defines for the bit fields in the GCR_GPDMFP register.
//! @{
//
//*****************************************************************************

//
//! PD.0 Pin Function Selection
//
#define GCR_GPDMFP_MFP0         0x00000001  

//
//! PD.1 Pin Function Selection
//
#define GCR_GPDMFP_MFP1         0x00000002  

//
//! PD.2 Pin Function Selection
//
#define GCR_GPDMFP_MFP2         0x00000004  

//
//! PD.3 Pin Function Selection
//
#define GCR_GPDMFP_MFP3         0x00000008  

//
//! PD.4 Pin Function Selection
//
#define GCR_GPDMFP_MFP4         0x00000010  

//
//! PD.5 Pin Function Selection
//
#define GCR_GPDMFP_MFP5         0x00000020  

//
//! PD.6 Pin Function Selection
//
#define GCR_GPDMFP_MFP6         0x00000040  

//
//! PD.7 Pin Function Selection
//
#define GCR_GPDMFP_MFP7         0x00000080  

//
//! PD.8 Pin Function Selection
//
#define GCR_GPDMFP_MFP8         0x00000100  

//
//! PD.9 Pin Function Selection
//
#define GCR_GPDMFP_MFP9         0x00000200  

//
//! PD.10 Pin Function Selection
//
#define GCR_GPDMFP_MFP10        0x00000400  

//
//! PD.11 Pin Function Selection
//
#define GCR_GPDMFP_MFP11        0x00000800  

//
//! PD.12 Pin Function Selection
//
#define GCR_GPDMFP_MFP12        0x00001000  

//
//! PD.13 Pin Function Selection
//
#define GCR_GPDMFP_MFP13        0x00002000  

//
//! PD.14 Pin Function Selection
//
#define GCR_GPDMFP_MFP14        0x00004000  

//
//! PD.15 Pin Function Selection
//
#define GCR_GPDMFP_MFP15        0x00008000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_GPEMFP SysCtl GCR GPEMFP Register(SysCtl_GCR_GPEMFP)
//! \brief Defines for the bit fields in the GCR_GPEMFP register.
//! @{
//
//*****************************************************************************

//
//! PE.0 Pin Function Selection
//
#define GCR_GPEMFP_MFP0         0x00000001  

//
//! PE.1 Pin Function Selection
//
#define GCR_GPEMFP_MFP1         0x00000002  

//
//! PE.2 Pin Function Selection
//
#define GCR_GPEMFP_MFP2         0x00000004  

//
//! PE.3 Pin Function Selection
//
#define GCR_GPEMFP_MFP3         0x00000008  

//
//! PE.4 Pin Function Selection
//
#define GCR_GPEMFP_MFP4         0x00000010  

//
//! PE.5 Pin Function Selection
//
#define GCR_GPEMFP_MFP5         0x00000020  

//
//! PE.6 Pin Function Selection
//
#define GCR_GPEMFP_MFP6         0x00000040  

//
//! PE.7 Pin Function Selection
//
#define GCR_GPEMFP_MFP7         0x00000080  

//
//! PE.8 Pin Function Selection
//
#define GCR_GPEMFP_MFP8         0x00000100  

//
//! PE.9 Pin Function Selection
//
#define GCR_GPEMFP_MFP9         0x00000200  

//
//! PE.10 Pin Function Selection
//
#define GCR_GPEMFP_MFP10        0x00000400  

//
//! PE.11 Pin Function Selection
//
#define GCR_GPEMFP_MFP11        0x00000800  

//
//! PE.12 Pin Function Selection
//
#define GCR_GPEMFP_MFP12        0x00001000  

//
//! PE.13 Pin Function Selection
//
#define GCR_GPEMFP_MFP13        0x00002000  

//
//! PE.`4 Pin Function Selection
//
#define GCR_GPEMFP_MFP14        0x00004000  

//
//! PE.15 Pin Function Selection
//
#define GCR_GPEMFP_MFP15        0x00008000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_ALTMFP SysCtl GCR ALTMFP Register(SysCtl_GCR_ALTMFP)
//! \brief Defines for the bit fields in the GCR_ALTMFP register.
//! @{
//
//*****************************************************************************

//
//! PB.10 Pin Function Selection
//
#define GCR_ALTMFP_PB10_S01     0x00000001  

//
//! PB.9 Pin Function Selection
//
#define GCR_ALTMFP_PB9_S11      0x00000002  

//
//! PA.7 Pin Function Selection
//
#define GCR_ALTMFP_PA7_S21      0x00000004  

//
//! PB.14 Pin Function Selection
//
#define GCR_ALTMFP_PB14_S31     0x00000008  

//
//! PB.11 Pin Function Selection
//
#define GCR_ALTMFP_PB11_PWM4    0x00000010  

//
//! PC.0 Pin Function Selection
//
#define GCR_ALTMFP_PC0_I2SLRCLK 0x00000020  

//
//! PC.1 Pin Function Selection
//
#define GCR_ALTMFP_PC1_I2SBCLK  0x00000040  

//
//! PC.2 Pin Function Selection
//
#define GCR_ALTMFP_PC2_I2SDI    0x00000080  

//
//! PC.3 Pin Function Selection
//
#define GCR_ALTMFP_PC3_I2SDO    0x00000100  

//
//! PA.15 Pin Function Selection
//
#define GCR_ALTMFP_PA15_I2SMCLK 0x00000200  

//
//! PB.12 Pin Function Selection
//
#define GCR_ALTMFP_PB12_CLKO    0x00000400

//
//! EBI_EN is use to switch GPIO function to EBI function (AD[15:0], ALE, RE,
//! WE, CS,MCLK), it need additional registers EBI_EN[7:0] and EBI_MCLK_EN for
//! some GPIO to switch to EBI function(AD[15:8], MCLK)
//
#define GCR_ALTMFP_EBI_EN       0x00000800 

//
//! Bits EBI_MCLK_EN, EBI_EN and GPC_MFP[8] determine the PC.8 function.
//
#define GCR_ALTMFP_EBI_MCLK_EN  0x00001000

//
//! Bits EBI_nWRL_EN, EBI_EN and GPB_MFP[2] determine the PB.2 function.
//
#define GCR_ALTMFP_EBI_nWRL_EN  0x00002000

//
//! Bits EBI_nWRH_EN, EBI_EN and GPB_MFP[3] determine the PB.3 function.
//
#define GCR_ALTMFP_EBI_nWRH_EN  0x00004000

//
//! Bits EBI_HB_EN[0], EBI_EN and GPA_MFP[5] determine the PA.5 function.
//
#define GCR_ALTMFP_EBI_HB_EN_0 0x00010000

//
//! Bits EBI_HB_EN[1], EBI_EN and GPA_MFP[4] determine the PA.4 function.
//
#define GCR_ALTMFP_EBI_HB_EN_1 0x00020000

//
//! Bits EBI_HB_EN[2], EBI_EN and GPA_MFP[3] determine the PA.3 function.
//
#define GCR_ALTMFP_EBI_HB_EN_2 0x00040000

//
//! Bits EBI_HB_EN[3], EBI_EN and GPA_MFP[2] determine the PA.2 function.
//
#define GCR_ALTMFP_EBI_HB_EN_3 0x00080000

//
//! Bits EBI_HB_EN[4], EBI_EN and GPA_MFP[1] determine the PA.1 function.
//
#define GCR_ALTMFP_EBI_HB_EN_4 0x00100000

//
//! Bits EBI_HB_EN[5], EBI_EN and GPA_MFP[12] determine the PA.12 function.
//
#define GCR_ALTMFP_EBI_HB_EN_5 0x00200000

//
//! Bits EBI_HB_EN[6], EBI_EN and GPA_MFP[13] determine the PA.13 function.
//
#define GCR_ALTMFP_EBI_HB_EN_6 0x00400000

//
//! Bits EBI_HB_EN[7], EBI_EN and GPA_MFP[14] determine the PA.14 function.
//
#define GCR_ALTMFP_EBI_HB_EN_7 0x00800000

//
//! Bits GPB_MFP15 and PB15_T0EX (ALT_MFP[24]) determine the PB.15 function.
//
#define GCR_ALTMFP_PB15_T0EX    0x01000000

//
//! Bits GPE_MFP5 and PE5_T1EX (ALT_MFP[25]) determine the PE.5 function.
//
#define GCR_ALTMFP_PE5_T1EX     0x02000000

//
//! Bits GPB_MFP2 and EBI_nWRL_EN (ALT_MFP[13]) and EBI_EN (ALT_MFP[11]) and
//! PB2_T2EX (ALT_MFP[26]) determine the PB.2 function.
//
#define GCR_ALTMFP_PB2_T2EX     0x04000000

//
//! Bits GPB_MFP3 and EBI_nWRH_EN (ALT_MFP[14]) and EBI_EN (ALT_MFP[11]) and
//! PB3_T3EX (ALT_MFP[27]) determine the PB.3 function.
//
#define GCR_ALTMFP_PB3_T3EX     0x08000000


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_GCR_REGLOCK SysCtl GCR_REGLOCK Register(SysCtl_GCR_REGLOCK)
//! \brief Defines for the bit fields in the GCR_REGLOCK register.
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
//! \addtogroup NUC1xx_SysCtl_Register_GCR_RCADJ SysCtl GCR_RCADJ Register(SysCtl_GCR_RCADJ)
//! \brief Defines for the bit fields in the GCR_RCADJ register.
//! @{
//
//*****************************************************************************

//
//! RC Adjustment control value mask
//
#define GCR_RCADJ_RCADJ_M       0x0000003F   

//
//! RC Adjustment control value shift
//
#define GCR_RCADJ_RCADJ_S       0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_SYSCLK_PWRCON SysCtl PWRCON Register(SysCtl_SYSCLK_PWRCON)
//! \brief Defines for the bit fields in the SYSCLK_PWRCON register.
//! @{
//
//*****************************************************************************

//
//! External 12 MHz Crystal Oscillator Control
//
#define SYSCLK_PWRCON_XTL12M_EN 0x00000001  

//
//! External 32.768 kHz Crystal Control
//
#define SYSCLK_PWRCON_XTL32K_EN 0x00000002  

//
//! Internal 22 MHz Oscillator Control
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
//! control the power down entry condition
//
#define SYSCLK_PWRCON_PD_WAIT_CPU                                             \
                                0x00000100  

                                
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_SYSCLK_AHBCLK SysCtl AHBCLK Register(SysCtl_SYSCLK_AHBCLK)
//! 
//! \brief Defines for the bit fields in the SYSCLK_AHBCLK register.
//! @{
//
//*****************************************************************************

//
//! PDMA Controller Clock Enable Control.
//
#define SYSCLK_AHBCLK_PDMA_EN   0x00000002  

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
//! \addtogroup NUC1xx_SysCtl_Register_SYSCLK_APBCLK SysCtl SYSCLK APBCLK Register
//! (SysCtl_SYSCLK_APBCLK)
//! \brief Defines for the bit fields in the SYSCLK_APBCLK register.
//! @{
//
//*****************************************************************************

//
//! Watch Dog Clock Enable.
//
#define SYSCLK_APBCLK_WDCLK_EN  0x00000001  

//
//! Real-Time-Clock APB interface Clock Control.
//
#define SYSCLK_APBCLK_RTC_EN    0x00000002  

//
//! Timer0 Clock Enable Control
//
#define SYSCLK_APBCLK_TMR0_EN   0x00000004  

//
//! Timer1 Clock Enable Control
//
#define SYSCLK_APBCLK_TMR1_EN   0x00000008  

//
//! Timer2 Clock Enable Control
//
#define SYSCLK_APBCLK_TMR2_EN   0x00000010  

//
//! Timer3 Clock Enable Control
//
#define SYSCLK_APBCLK_TMR3_EN   0x00000020  

//
//! Frequency Divider Output Clock Enable Control
//
#define SYSCLK_APBCLK_FDIV_EN   0x00000040  

//
//! I2C0 Clock Enable Control.
//
#define SYSCLK_APBCLK_I2C0_EN   0x00000100  

//
//! I2C1 Clock Enable Control.
//
#define SYSCLK_APBCLK_I2C1_EN   0x00000200  

//
//! SPI0 Clock Enable Control.
//
#define SYSCLK_APBCLK_SPI0_EN   0x00001000  

//
//! SPI1 Clock Enable Control.
//
#define SYSCLK_APBCLK_SPI1_EN   0x00002000  

//
//! SPI2 Clock Enable Control.
//
#define SYSCLK_APBCLK_SPI2_EN   0x00004000  

//
//! SPI3 Clock Enable Control.
//
#define SYSCLK_APBCLK_SPI3_EN   0x00008000  

//
//! UART0 Clock Enable Control.
//
#define SYSCLK_APBCLK_UART0_EN  0x00010000  

//
//! UART1 Clock Enable Control.
//
#define SYSCLK_APBCLK_UART1_EN  0x00020000  

//
//! UART2 Clock Enable Control.
//
#define SYSCLK_APBCLK_UART2_EN  0x00040000  

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
//! PWM_67 Clock Enable Control.
//
#define SYSCLK_APBCLK_PWM67_EN  0x00800000  

//
//! CAN Bus 0 Clock Enable Control
//
#define SYSCLK_APBCLK_CAN0_EN   0x01000000  

//
//! USB FS Device Controller Clock Enable Control
//
#define SYSCLK_APBCLK_USBD_EN   0x08000000  

//
//! (ADC) Clock Enable Control.
//
#define SYSCLK_APBCLK_ADC_EN    0x10000000  

//
//! I2S Clock Enable Control.
//
#define SYSCLK_APBCLK_I2S_EN    0x20000000  

//
//! Analog Comparator Clock Enable Control.
//
#define SYSCLK_APBCLK_ACMP_EN   0x40000000  

//
//! PS2 Clock Enable Control.
//
#define SYSCLK_APBCLK_PS2_EN    0x80000000  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_SYSCLK_CLKSEL0 SysCtl CLKSEL0(SysCtl_SYSCLK_CLKSEL0)
//! \brief Defines for the bit fields in the SYSCLK_CLKSEL0 register.
//! @{
//
//*****************************************************************************

//
//! HCLK clock source select mask.
//
#define SYSCLK_CLKSEL0_HCLK_M   0x00000007  

//
//! HCLK clock source is external 12 MHz crystal clock
//
#define SYSCLK_CLKSEL0_HCLK12M  0x00000000  

//
//! PHCLK clock source is external 32 KHz crystal clock.
//
#define SYSCLK_CLKSEL0_HCLK32K  0x00000001  

//
//! HCLK clock source is PLL clock.
//
#define SYSCLK_CLKSEL0_HCLKPLL  0x00000002  

//
//! HCLK clock source is internal 10 kHz oscillator clock.
//
#define SYSCLK_CLKSEL0_HCLK10K  0x00000003  

//
//! HCLK clock source is internal 22 MHz oscillator clock.
//
#define SYSCLK_CLKSEL0_HCLK22M  0x00000007  

//
//! MCU Cortex_M0 SysTick clock source select mask.
//
#define SYSCLK_CLKSEL0_STCLK_M  0x00000038 

//
//! MCU Cortex_M0 SysTick clock source is 12 MHz crystal clock .
//
#define SYSCLK_CLKSEL0_STCLK12M 0x00000000  

//
//! MCU Cortex_M0 SysTick clock source is external 32kHz crystal clock.
//
#define SYSCLK_CLKSEL0_STCLK32K 0x00000008  

//
//! MCU Cortex_M0 SysTick clock source is 12 MHz crystal clock/2.
//
#define SYSCLK_CLKSEL0_STCLK12M_2                                             \
                                0x00000010  
                                
//
//! MCU Cortex_M0 SysTick clock source is HCLK/2.
//
#define SYSCLK_CLKSEL0_STCLKHCLK_2                                            \
                                0x00000018  
                                
//
//! MCU Cortex_M0 SysTick clock source is internal 22 MHz oscillator clock/2.
//
#define SYSCLK_CLKSEL0_STCLKiNT22M_2                                          \
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
//! \addtogroup NUC1xx_SysCtl_Register_SYSCLK_CLKSEL1 SysCtl CLKSEL1 Register(SysCtl_SYSCLK_CLKSEL1)
//! \brief Defines for the bit fields in the SYSCLK_CLKSEL1 register.
//! @{
//
//*****************************************************************************
 
//
//! WDG CLK clock source select mask.
//  
#define SYSCLK_CLKSEL1_WDG_M    0x00000003 
 
//
//! WDG CLK clock source is 12M.
//  
//#define SYSCLK_CLKSEL1_WDG12M   0x00000000  
 
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
//! TIMER2 clock source select mask.
//  
#define SYSCLK_CLKSEL1_TMR2_M   0x00070000  

//
//! TIMER3 clock source select mask.
//  
#define SYSCLK_CLKSEL1_TMR3_M   0x00700000  
 
//
//! UART clock source select mask.
//  
#define SYSCLK_CLKSEL1_UART_M   0x03000000  
 
//
//! CAN clock source select mask.
//  
#define SYSCLK_CLKSEL1_CAN_M    0x0C000000  
 
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
//! ADC clock source select shift.
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
//! TIMER3 clock source select shift.
// 
#define SYSCLK_CLKSEL1_TMR3_S   20
 
//
//! UART clock source select shift.
// 
#define SYSCLK_CLKSEL1_UART_S   24
 
//
//! CAN clock source select shift.
// 
#define SYSCLK_CLKSEL1_CAN_S    26
 
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
//! \addtogroup NUC1xx_SysCtl_Register_SYSCLK_CLKSEL2 SysCtl CLKSEL2 Register(SysCtl_SYSCLK_CLKSEL2)
//! \brief Defines for the bit fields in the SYSCLK_CLKSEL2 register.
//! @{
//
//*****************************************************************************
 
//
//! I2S Clock Source Select mask.
//
#define SYSCLK_CLKSEL2_I2S_M    0x00000003  
 
//
//! Clock Divider Clock Source Select mask.
//
#define SYSCLK_CLKSEL2_FRQDIV_M 0x0000000C  
 
//
//! PWM4 and PWM5 clock source select mask.
//
#define SYSCLK_CLKSEL2_PWM45_M  0x00000030  
 
//
//! PWM6 and PWM7 clock source select mask.
//
#define SYSCLK_CLKSEL2_PWM67_M  0x000000C0  
 
//
//! I2S Clock Source Select shift.
//
#define SYSCLK_CLKSEL2_I2S_S    0
 
//
//! Clock Divider Clock Source Select shift.
//
#define SYSCLK_CLKSEL2_FRQDIV_S 2
 
//
//! PWM4 and PWM5 clock source select shift.
//
#define SYSCLK_CLKSEL2_PWM45_S  4
 
//
//! PWM6 and PWM7 clock source select shift.
//
#define SYSCLK_CLKSEL2_PWM67_S  6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_SYSCLK_CLKDIV SysCtl CLKDIV Register(SysCtl_SYSCLK_CLKDIV)
//! \brief Defines for the bit fields in the SYSCLK_CLKDIV register.
//! @{
//
//*****************************************************************************
 
//
//! HCLK clock divide number mask.
//
#define SYSCLK_CLKDIV_HCLK_M    0x0000000F  
 
//
//! USB clock divide number mask.
//
#define SYSCLK_CLKDIV_USB_M     0x000000F0  
 
//
//! UART clock divide number mask.
//
#define SYSCLK_CLKDIV_UART_M    0x00000F00  
 
//
//! CAN clock divide number mask.
//
#define SYSCLK_CLKDIV_CAN_M     0x0000F000 
 
//
//! ADC clock divide number mask.
//
#define SYSCLK_CLKDIV_ADC_M     0x00FF0000  
 
//
//! HCLK clock divide number shift.
//
#define SYSCLK_CLKDIV_HCLK_S    0
 
//
//! USB clock divide number shift.
//
#define SYSCLK_CLKDIV_USB_S     4
 
//
//! UART clock divide number shift.
//
#define SYSCLK_CLKDIV_UART_S    8
 
//
//! CAN clock divide number shift.
//
#define SYSCLK_CLKDIV_CAN_S     12
 
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
//! \addtogroup NUC1xx_SysCtl_Register_SYSCLK_PLLCON SysCtl PLLCON Register(SysCtl_SYSCLK_PLLCON)
//! \brief Defines for the bit fields in the SYSCLK_PLLCON register.
//! @{
//
//*****************************************************************************
 
//
//! PLL Feedback Divider Control Pins mask.
//
#define SYSCLK_PLLCON_FB_DV_M   0x000001FF  
 
//
//! PLL Input Divider Control Pins mask.
//
#define SYSCLK_PLLCON_IN_DV_M   0x00003E00  
 
//
//! PLL Output Divider Control Pins mask.
//
#define SYSCLK_PLLCON_OUT_DV_M  0x0000C000  
 
//
//! Power Down Mode.
//
#define SYSCLK_PLLCON_PD        0x00010000  
 
//
//! PLL Bypass Control.
//
#define SYSCLK_PLLCON_BP        0x00020000  
 
//
//! PLL OE (FOUT enable) pin Control.
//
#define SYSCLK_PLLCON_OE        0x00040000  
 
//
//! PLL Source Clock Select.
//
#define SYSCLK_PLLCON_PLL_SRC   0x00080000  
 
//
//! PLL Feedback Divider Control Pins shift.
//
#define SYSCLK_PLLCON_FB_DV_S   0
 
//
//! PLL Input Divider Control Pins shift.
//
#define SYSCLK_PLLCON_IN_DV_S   9
 
//
//! PLL Output Divider Control Pins shift.
//
#define SYSCLK_PLLCON_OUT_DV_S  14

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SysCtl_Register_SYSCLK_FRQDIV SysCtl FRQDIV Register(SysCtl_SYSCLK_FRQDIV)
//! \brief Defines for the bit fields in the SYSCLK_FRQDIV register.
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

