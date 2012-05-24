//*****************************************************************************
//
//! \file xhw_sysctl.h
//! \brief Macros used when accessing the system control hardware.
//! \version V2.2.1.0
//! \date 4/25/2012
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
//! \addtogroup HT32F175x_275x_SysCtl_Register HT32F175x_275x SysCtl Register
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
//! \addtogroup HT32F175x_275x_SysCtl_Register_Offsets HT32F175x_275x SysCtl Register Offsets(Map)
//! \brief Defines for the system control register addresses.
//! @{
//
//*****************************************************************************

//
//! Backup Domain Status Register
//
#define PWRCU_BAKSR             0x4006A100

//
//! Backup Domain Control Register
//
#define PWRCU_BAKCR             0x4006A104

//
//! Backup Domain Test Register
//
#define PWRCU_BAKTEST           0x4006A108

//
//! HSI Ready Counter Control Register
//
#define PWRCU_HSIRCR            0x4006A10C

//
//! Low Voltage/Brown Out Detect Control and Status Register
//
#define PWRCU_LVDCSR            0x4006A110

//
//! Backup Register 0
//
#define PWRCU_BAKREG0           0x4006A200

//
//! Backup Register 1
//
#define PWRCU_BAKREG1           0x4006A204

//
//! Backup Register 2
//
#define PWRCU_BAKREG2           0x4006A208

//
//! Backup Register 3
//
#define PWRCU_BAKREG3           0x4006A20C

//
//! Backup Register 4
//
#define PWRCU_BAKREG4           0x4006A210

//
//! Backup Register 5
//
#define PWRCU_BAKREG5           0x4006A214

//
//! Backup Register 6
//
#define PWRCU_BAKREG6           0x4006A218

//
//! Backup Register 7
//
#define PWRCU_BAKREG7           0x4006A21C

//
//! Backup Register 8
//
#define PWRCU_BAKREG8           0x4006A220

//
//! Backup Register 9
//
#define PWRCU_BAKREG9           0x4006A224

//
//! Global Clock Configuration Register
//
#define SYSCLK_GCFGR            0x40088000

//
//! Global Clock Control Register
//
#define SYSCLK_GCCR             0x40088004

//
//! Global Clock Status Register
//
#define SYSCLK_GCSR             0x40088008

//
//! Global Clock Interrupt Register
//
#define SYSCLK_GCIR             0x4008800C

//
//! PLL Configuration Register
//
#define SYSCLK_PLLCFGR          0x40088018

//
//! PLL Control Register
//
#define SYSCLK_PLLCR            0x4008801C

//
//! AHB Configuration Register
//
#define SYSCLK_AHBCFGR          0x40088020

//
//! AHB Clock Control Register
//
#define SYSCLK_AHBCCR           0x40088024

//
//! APB Configuration Register
//
#define SYSCLK_APBCFGR          0x40088028

//
//! APB Clock Control Register 0
//
#define SYSCLK_APBCCR0          0x4008802C

//
//! APB Clock Control Register 1
//
#define SYSCLK_APBCCR1          0x40088030

//
//! Clock Source Status Register
//
#define SYSCLK_CKST             0x40088034

//
//! Low Power Control Register
//
#define SYSCLK_LPCR             0x40088300

//
//! MCU Debug Control Register
//
#define SYSCLK_DBGCR            0x40088304

//
//! Global Reset Status Register
//
#define RSTCU_GRSR              0x40088100

//
//! AHB Peripheral Reset Register
//
#define RSTCU_AHBPRSTR          0x40088104

//
//! APB Peripheral Reset Register 0
//
#define RSTCU_APBPRSTR0         0x40088108

//
//! APB Peripheral Reset Register 1
//
#define RSTCU_APBPRSTR1         0x4008810C

//
//! Flash Cache and Pre-fetch Control Register 
//
#define FLASH_CFCR              0x40080200

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_PWRCU_BAKSR SysCtl Register PWRCU BAKSR(SysCtl_PWRCU_BAKSR)
//! @{
//
//*****************************************************************************

//
//! Backup Domain Reset Flag
//
#define PWRCU_BAKSR_BAKPORF     0x00000001

//
//! Power Down Flag
//
#define PWRCU_BAKSR_PDF         0x00000002
 
//
//! External WAKEUP Pin Flag
//
#define PWRCU_BAKSR_WUPF        0x00000010

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_PWRCU_BAKCR SysCtl Register PWRCU BAKCR(SysCtl_PWRCU_BAKCR)
//! @{
//
//*****************************************************************************

//
//! Backup Domain Software Reset
//
#define PWRCU_BAKCR_BAKRST      0x00000001

//
//! LDO Operating Mode Control
//
#define PWRCU_BAKCR_LDOOFF      0x00000004
 
//
//! DMOS Control
//
#define PWRCU_BAKCR_DMOSON      0x00000080

//
//! External WAKEUP Pin Enable
//
#define PWRCU_BAKCR_WUPEN       0x00000100

//
//! External WAKEUP Pin Interrupt Enable
//
#define PWRCU_BAKCR_WUPIEN      0x00000200

//
//! VDD18 Ready Source Selection.
//
#define PWRCU_BAKCR_V18RDYSC    0x00001000

//
//! DMOS Status
//
#define PWRCU_BAKCR_DMOSSTS     0x00008000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_PWRCU_BAKTEST SysCtl Register PWRCU BAKTEST(SysCtl_PWRCU_BAKTEST)
//! @{
//
//*****************************************************************************

//
//! Backup Domain Test Bits Mask
//
#define PWRCU_BAKTEST_M         0x000000FF

//
//! Backup Domain Test Bits Shift
//
#define PWRCU_BAKTEST_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_PWRCU_HSIRCR SysCtl Register PWRCU HSIRCR(SysCtl_PWRCU_HSIRCR)
//! @{
//
//*****************************************************************************

//
//! HSI Ready Counter Bit Length Mask
//
#define PWRCU_HSIRCR_HSIRCBL_M  0x00000003

//
//! HSI Ready Counter Bit Length Shift
//
#define PWRCU_HSIRCR_HSIRCBL_S  0

//
//! HSI Ready Counter Bit Length is 4 bits
//
#define PWRCU_HSIRCR_HSIRCBL_4  0x00000000

//
//! HSI Ready Counter Bit Length is 5 bits
//
#define PWRCU_HSIRCR_HSIRCBL_5  0x00000001

//
//! HSI Ready Counter Bit Length is 6 bits
//
#define PWRCU_HSIRCR_HSIRCBL_6  0x00000002

//
//! HSI Ready Counter Bit Length is 7 bits
//
#define PWRCU_HSIRCR_HSIRCBL_7  0x00000003

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_PWRCU_LVDCSR SysCtl Register PWRCU LVDCSR(SysCtl_PWRCU_LVDCSR)
//! @{
//
//*****************************************************************************

//
//! Brown Out Detect Enable
//
#define PWRCU_LVDCSR_BODEN      0x00000001

//
//! BOD Reset Selection
//
#define PWRCU_LVDCSR_BODRST     0x00000000

//
//! BOD Interrupt Selection
//
#define PWRCU_LVDCSR_BODINT     0x00000002
 
//
//! Brow Out Detection Flag
//
#define PWRCU_LVDCSR_BODF       0x00000004

//
//! Low Voltage Detect Enable
//
#define PWRCU_LVDCSR_LVDEN      0x00010000

//
//! Low Voltage Detect Level Selection Mask
//
#define PWRCU_LVDCSR_LVDS_M     0x00060000

//
//! Low Voltage Detect Level Selection Shift
//
#define PWRCU_LVDCSR_LVDS_S     17

//
//! Low Voltage Detect Level is 2.7V
//
#define PWRCU_LVDCSR_LVDS_2V7   0x00000000

//
//! Low Voltage Detect Level is 2.8V
//
#define PWRCU_LVDCSR_LVDS_2V8   0x00020000

//
//! Low Voltage Detect Level is 2.9V
//
#define PWRCU_LVDCSR_LVDS_2V9   0x00040000

//
//! Low Voltage Detect Level is 3.0V
//
#define PWRCU_LVDCSR_LVDS_3V0   0x00060000

//
//! Low Voltage Detect Status Flag
//
#define PWRCU_LVDCSR_LVDF       0x00080000

//
//! LVD Interrupt Wakeup Enable
//
#define PWRCU_LVDCSR_LVDIWEN    0x00100000

//
//! LVD Event Wakeup Enable
//
#define PWRCU_LVDCSR_LVDEWEN    0x00200000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_SYSCLK_GCFGR SysCtl Register SYSCLK GCFGR(SysCtl_SYSCLK_GCFGR)
//! @{
//
//*****************************************************************************

//
//! CKOUT Clock Source Selection Mask 
//
#define SYSCLK_GCFGR_CKOUTSRC_M                                               \
                                0x00000007

//
//! CKOUT Clock Source Selection Shift
//
#define SYSCLK_GCFGR_CKOUTSRC_S 0

//
//! CKOUT Clock Source is CK_PLL / 16
//
#define SYSCLK_GCFGR_CKOUTSRC_PLL_16                                          \
                                0x00000000

//
//! CKOUT Clock Source is CSIFMPRE / 2
//
#define SYSCLK_GCFGR_CKOUTSRC_CSIFMPRE_2                                          \
                                0x00000000

//
//! CKOUT Clock Source is CK_AHB / 16
//
#define SYSCLK_GCFGR_CKOUTSRC_AHB_16                                          \
                                0x00000001

//
//! CKOUT Clock Source is CK_SYS / 16
//
#define SYSCLK_GCFGR_CKOUTSRC_SYS_16                                          \
                                0x00000002

//
//! CKOUT Clock Source is CK_HSE / 16
//
#define SYSCLK_GCFGR_CKOUTSRC_HSE_16                                          \
                                0x00000003

//
//! CKOUT Clock Source is CK_HSI / 16
//
#define SYSCLK_GCFGR_CKOUTSRC_HSI_16                                          \
                                0x00000004

//
//! CKOUT Clock Source is CK_LSE
//
#define SYSCLK_GCFGR_CKOUTSRC_LSE                                             \
                                0x00000005

//
//! CKOUT Clock Source is CK_LSI
//
#define SYSCLK_GCFGR_CKOUTSRC_LSI                                             \
                                0x00000006

//
//! Watchdog Timer Clock Source Mask.
//
#define SYSCLK_GCFGR_WDTSRC_M   0x00000008

//
//! Watchdog Timer Clock Source is internal 32 kHz crystal.
//
#define SYSCLK_GCFGR_WDTSRC_LSI 0x00000000

//
//! Watchdog Timer Clock Source is external LSE 32768 Hz crystal.
//
#define SYSCLK_GCFGR_WDTSRC_LSE 0x00000008

//
//! USART Clock Source Selection is AHB/APB Bus Clock (CK_AHB).
//
#define SYSCLK_GCFGR_URSRC_CKAHB                                             \
                                0x00000000
//
//! PLL Clock Source Mask.
//
#define SYSCLK_GCFGR_PLLSRC_M   0x00000100

//
//! PLL Clock Source is internal 8 MHz crystal.
//
#define SYSCLK_GCFGR_PLLSRC_HSI 0x00000100

//
//! PLL Clock Source is external 4~16 MHz crystal.
//
#define SYSCLK_GCFGR_PLLSRC_HSE 0x00000000

//
//! USART Clock Prescaler Mask
//
#define SYSCLK_GCFGR_URPRE_M    0x00300000

//
//! USART Clock Prescaler Shift
//
#define SYSCLK_GCFGR_URPRE_S    20

//
//! USART Clock Prescaler is CKUR
//
#define SYSCLK_GCFGR_URPRE      0x00000000

//
//! USART Clock Prescaler is CKUR/2
//
#define SYSCLK_GCFGR_URPRE_2    0x00100000

//
//! USB Clock Prescaler Selection Mask
//
#define SYSCLK_GCFGR_USBPRE_M   0x00C00000

//
//! USB Clock Prescaler Selection Shift
//
#define SYSCLK_GCFGR_USBPRE_S   22

//
//! USB Clock Prescaler is CK_PLL
//
#define SYSCLK_GCFGR_USBPRE     0x00000000

//
//! USB Clock Prescaler is CK_PLL/2
//
#define SYSCLK_GCFGR_USBPRE_2   0x00400000

//
//! USB Clock Prescaler is CK_PLL/3
//
#define SYSCLK_GCFGR_USBPRE_3   0x00800000

//
//! CSIF_MCK Clock Prescaler Selection Mask
//
#define SYSCLK_GCFGR_CSIFPRE_M  0x1F000000

//
//! CSIF_MCK Clock Prescaler Selection Shift
//
#define SYSCLK_GCFGR_CSIFPRE_S  24

//
//! CSIF_MCK Clock Prescaler is CK_PLL/2
//
#define SYSCLK_GCFGR_CSIFPRE_2  0x00000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/4
//
#define SYSCLK_GCFGR_CSIFPRE_4  0x01000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/6
//
#define SYSCLK_GCFGR_CSIFPRE_6  0x02000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/8
//
#define SYSCLK_GCFGR_CSIFPRE_8  0x03000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/10
//
#define SYSCLK_GCFGR_CSIFPRE_10 0x04000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/12
//
#define SYSCLK_GCFGR_CSIFPRE_12 0x05000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/14
//
#define SYSCLK_GCFGR_CSIFPRE_14 0x06000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/16
//
#define SYSCLK_GCFGR_CSIFPRE_16 0x07000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/18
//
#define SYSCLK_GCFGR_CSIFPRE_18 0x08000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/20
//
#define SYSCLK_GCFGR_CSIFPRE_20 0x09000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/22
//
#define SYSCLK_GCFGR_CSIFPRE_22 0x0A000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/24
//
#define SYSCLK_GCFGR_CSIFPRE_24 0x0B000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/26
//
#define SYSCLK_GCFGR_CSIFPRE_26 0x0C000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/28
//
#define SYSCLK_GCFGR_CSIFPRE_28 0x0D000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/30
//
#define SYSCLK_GCFGR_CSIFPRE_30 0x0E000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/32
//
#define SYSCLK_GCFGR_CSIFPRE_32 0x0F000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/34
//
#define SYSCLK_GCFGR_CSIFPRE_34 0x10000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/36
//
#define SYSCLK_GCFGR_CSIFPRE_36 0x11000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/38
//
#define SYSCLK_GCFGR_CSIFPRE_38 0x12000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/40
//
#define SYSCLK_GCFGR_CSIFPRE_40 0x13000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/42
//
#define SYSCLK_GCFGR_CSIFPRE_42 0x14000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/44
//
#define SYSCLK_GCFGR_CSIFPRE_44 0x15000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/46
//
#define SYSCLK_GCFGR_CSIFPRE_46 0x16000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/48
//
#define SYSCLK_GCFGR_CSIFPRE_48 0x17000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/50
//
#define SYSCLK_GCFGR_CSIFPRE_50 0x18000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/52
//
#define SYSCLK_GCFGR_CSIFPRE_52 0x19000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/54
//
#define SYSCLK_GCFGR_CSIFPRE_54 0x1A000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/56
//
#define SYSCLK_GCFGR_CSIFPRE_56 0x1B000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/58
//
#define SYSCLK_GCFGR_CSIFPRE_58 0x1C000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/60
//
#define SYSCLK_GCFGR_CSIFPRE_60 0x1D000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/62
//
#define SYSCLK_GCFGR_CSIFPRE_62 0x1E000000

//
//! CSIF_MCK Clock Prescaler is CK_PLL/64
//
#define SYSCLK_GCFGR_CSIFPRE_64 0x1F000000

//
//! Lower Power Mode Status Mask
//
#define SYSCLK_GCFGR_LPMOD_M    0xE0000000

//
//! Lower Power Mode Status Shift
//
#define SYSCLK_GCFGR_LPMOD_S    29

//
//! Device in running mode
//
#define SYSCLK_GCFGR_LPMOD_RUN  0x00000000

//
//! Device wants to enter Sleep mode
//
#define SYSCLK_GCFGR_LPMOD_SLEEP                                              \
                                0x20000000

//
//! Device wants to enter Deep Sleep mode1
//
#define SYSCLK_GCFGR_LPMOD_DEEPSLEEP1                                         \
                                0x40000000

//
//! Device wants to enter Deep Sleep mode2
//
#define SYSCLK_GCFGR_LPMOD_DEEPSLEEP2                                         \
                                0x60000000

//
//! Device wants to enter Power Down mode
//
#define SYSCLK_GCFGR_LPMOD_POWERDOWN                                         \
                                0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_SYSCLK_GCCR SysCtl Register SYSCLK GCCR(SysCtl_SYSCLK_GCCR)
//! @{
//
//*****************************************************************************

//
//! System Clock Source Mask
//
#define SYSCLK_GCCR_SW_M        0x00000003

//
//! System Clock Source Shift
//
#define SYSCLK_GCCR_SW_S        0

//
//! System Clock Source is PLL
//
#define SYSCLK_GCCR_SYSSRC_PLL  0x00000000

//
//! System Clock Source is HSE
//
#define SYSCLK_GCCR_SYSSRC_HSE  0x00000002

//
//! System Clock Source is HSI
//
#define SYSCLK_GCCR_SYSSRC_HSI  0x00000003

//
//! PLL Enable
//
#define SYSCLK_GCCR_PLLEN       0x00000200

//
//! External High Speed oscillator Enable
//
#define SYSCLK_GCCR_HSEEN       0x00000400

//
//! Internal High Speed oscillator Enable
//
#define SYSCLK_GCCR_HSIEN       0x00000800

//
//! HSE Clock Monitor Enable
//
#define SYSCLK_GCCR_CKMEN       0x00010000

//
//! Power Saving Wakeup RC Clock Enable
//
#define SYSCLK_GCCR_PSRCEN      0x00020000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_SYSCLK_GCSR SysCtl Register SYSCLK GCSR(SysCtl_SYSCLK_GCSR)
//! @{
//
//*****************************************************************************

//
//! PLL Clock Ready Flag
//
#define SYSCLK_GCSR_PLLRDY      0x00000002

//
//! HSE High Speed External Clock Ready Flag
//
#define SYSCLK_GCSR_HSERDY      0x00000004

//
//! HSI High Speed Internal Oscillator Ready Flag
//
#define SYSCLK_GCSR_HSIRDY      0x00000008

//
//! LSE External Low Speed Oscillator Ready Flag
//
#define SYSCLK_GCSR_LSERDY      0x00000010

//
//! LSI Internal Low Speed Oscillator Ready Flag
//
#define SYSCLK_GCSR_LSIRDY      0x00000020

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_SYSCLK_GCIR SysCtl Register SYSCLK GCIR(SysCtl_SYSCLK_GCIR)
//! @{
//
//*****************************************************************************

//
//! HSE Clock Stuck Interrupt Flag
//
#define SYSCLK_GCIR_CKSF        0x00000001

//
//! PLL Ready Interrupt Flag
//
#define SYSCLK_GCIR_PLLRDYF     0x00000004

//
//! HSE Ready Interrupt Flag
//
#define SYSCLK_GCIR_HSERDYF     0x00000008

//
//! HSI Ready Interrupt Flag
//
#define SYSCLK_GCIR_HSIRDYF     0x00000010

//
//! LSE Ready Interrupt Flag
//
#define SYSCLK_GCIR_LSERDYF     0x00000020

//
//! LSI Ready Interrupt Flag
//
#define SYSCLK_GCIR_LSIRDYF     0x00000040

//
//! Clock Stuck Interrupt Enable
//
#define SYSCLK_GCIR_CKSIE       0x00010000

//
//! PLL Ready Interrupt Enable
//
#define SYSCLK_GCIR_PLLRDYIE    0x00040000

//
//! HSE Ready Interrupt Enable
//
#define SYSCLK_GCIR_HSERDYIE    0x00080000

//
//! HSI Ready Interrupt Enable
//
#define SYSCLK_GCIR_HSIRDYIE    0x00100000

//
//! LSE Ready Interrupt Enable
//
#define SYSCLK_GCIR_LSERDYIE    0x00200000

//
//! LSI Ready Interrupt Enable
//
#define SYSCLK_GCIR_LSIRDYIE    0x00400000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_SYSCLK_PLLCFGR SysCtl Register SYSCLK PLLCFGR(SysCtl_SYSCLK_PLLCFGR)
//! @{
//
//*****************************************************************************

//
//! PLL Output Clock Divider Mask
//
#define SYSCLK_PLLCFGR_POTD_M   0x00600000

//
//! PLL Output Clock Divider Shift
//
#define SYSCLK_PLLCFGR_POTD_S   21

//
//! PLL VCO Output Clock Feedback Divider Mask
//
#define SYSCLK_PLLCFGR_PFBD_M   0x1F800000

//
//! PLL VCO Output Clock Feedback Divider Shift
//
#define SYSCLK_PLLCFGR_PFBD_S   23

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_SYSCLK_PLLCR SysCtl Register SYSCLK PLLCR(SysCtl_SYSCLK_PLLCR)
//! @{
//
//*****************************************************************************

//
//! PLL Bypass Mode Enable
//
#define SYSCLK_PLLCR_PLLBPS_EN  0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_SYSCLK_AHBCFGR SysCtl Register SYSCLK AHBCFGR(SysCtl_SYSCLK_AHBCFGR)
//! @{
//
//*****************************************************************************

//
//! AHB Pre-Scaler Mask
//
#define SYSCLK_AHBCFGR_AHBPRE_M 0x00000003

//
//! AHB Pre-Scaler Mask
//
#define SYSCLK_AHBCFGR_AHBPRE_S 0

//
//! AHB Pre-Scaler is 1
//
#define SYSCLK_AHBCFGR_AHBPRE_CKSYS_1                                          \
                                0x00000000

//
//! AHB Pre-Scaler is 2
//
#define SYSCLK_AHBCFGR_AHBPRE_CKSYS_2                                          \
                                0x00000001

//
//! AHB Pre-Scaler is 4
//
#define SYSCLK_AHBCFGR_AHBPRE_CKSYS_4                                          \
                                0x00000002

//
//! AHB Pre-Scaler is 8
//
#define SYSCLK_AHBCFGR_AHBPRE_CKSYS_8                                          \
                                0x00000003

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_SYSCLK_AHBCCR SysCtl Register SYSCLK AHBCCR(SysCtl_SYSCLK_AHBCCR)
//! @{
//
//*****************************************************************************

//
//! Flash Memory Controller Clock Enable
//
#define SYSCLK_AHBCCR_FMC_EN    0x00000001

//
//! SRAM Clock Enable
//
#define SYSCLK_AHBCCR_SRAM_EN   0x00000004

//
//! Peripheral DMA Clock Enable
//
#define SYSCLK_AHBCCR_DMA_EN    0x00000010

//
//! Bus Matrix Clock Enable
//
#define SYSCLK_AHBCCR_BM_EN     0x00000020

//
//! APB0 bridge Clock Enable
//
#define SYSCLK_AHBCCR_APB0_EN   0x00000010

//
//! APB1 bridge Clock Enable
//
#define SYSCLK_AHBCCR_APB1_EN   0x00000020

//
//! CSIF Clock Enable
//
#define SYSCLK_AHBCCR_CSIF_EN   0x00000100

//
//! CSIF_MCK Clock Enable
//
#define SYSCLK_AHBCCR_CSIFM_EN  0x00000200

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_SYSCLK_APBCFGR SysCtl Register SYSCLK APBCFGR(SysCtl_SYSCLK_APBCFGR)
//! @{
//
//*****************************************************************************

//
//! ADC Clock Frequency Division Mask
//
#define SYSCLK_APBCFGR_ADCDIV_M 0x00070000

//
//! ADC Clock Frequency Division Shift
//
#define SYSCLK_APBCFGR_ADCDIV_S 16

//
//! ADC Clock Frequency Division is 1
//
#define SYSCLK_APBCFGR_ADCDIV_CKAHB_1                                         \
                                0x00000000

//
//! ADC Clock Frequency Division is 2
//
#define SYSCLK_APBCFGR_ADCDIV_CKAHB_2                                         \
                                0x00010000

//
//! ADC Clock Frequency Division is 4
//
#define SYSCLK_APBCFGR_ADCDIV_CKAHB_4                                         \
                                0x00020000

//
//! ADC Clock Frequency Division is 8
//
#define SYSCLK_APBCFGR_ADCDIV_CKAHB_8                                         \
                                0x00030000

//
//! ADC Clock Frequency Division is 16
//
#define SYSCLK_APBCFGR_ADCDIV_CKAHB_16                                        \
                                0x00040000

//
//! ADC Clock Frequency Division is 32
//
#define SYSCLK_APBCFGR_ADCDIV_CKAHB_32                                        \
                                0x00050000

//
//! ADC Clock Frequency Division is 64
//
#define SYSCLK_APBCFGR_ADCDIV_CKAHB_64                                        \
                                0x00060000

//
//! ADC Clock Frequency Division is 1
//
#define SYSCLK_APBCFGR_ADCDIV_CKAHB_6                                         \
                                0x00070000
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_SYSCLK_APBCCR0 SysCtl Register SYSCLK APBCCR0(SysCtl_SYSCLK_APBCCR0)
//! @{
//
//*****************************************************************************

//
//! Peripheral I2C0 Clock Enable
//
#define SYSCLK_APBCCR0_I2C0_EN  0x00000001

//
//! Peripheral I2C1 Clock Enable
//
#define SYSCLK_APBCCR0_I2C1_EN  0x00000002

//
//! Peripheral SPI0 Clock Enable
//
#define SYSCLK_APBCCR0_SPI0_EN  0x00000010

//
//! Peripheral SPI1 Clock Enable
//
#define SYSCLK_APBCCR0_SPI1_EN  0x00000020

//
//! Peripheral UART0 Clock Enable
//
#define SYSCLK_APBCCR0_UART0_EN 0x00000100

//
//! Peripheral UART1 Clock Enable
//
#define SYSCLK_APBCCR0_UART1_EN 0x00000200

//
//! Peripheral AFIO Clock Enable
//
#define SYSCLK_APBCCR0_AFIO_EN  0x00004000

//
//! Peripheral EXTI Clock Enable
//
#define SYSCLK_APBCCR0_EXTI_EN  0x00008000

//
//! Peripheral GPIOA Clock Enable
//
#define SYSCLK_APBCCR0_GPIOA_EN 0x00010000

//
//! Peripheral GPIOB Clock Enable
//
#define SYSCLK_APBCCR0_GPIOB_EN 0x00020000

//
//! Peripheral GPIOC Clock Enable
//
#define SYSCLK_APBCCR0_GPIOC_EN 0x00040000

//
//! Peripheral GPIOD Clock Enable
//
#define SYSCLK_APBCCR0_GPIOD_EN 0x00080000

//
//! Peripheral GPIOE Clock Enable
//
#define SYSCLK_APBCCR0_GPIOE_EN 0x00100000

//
//! Peripheral SCI Clock Enable
//
#define SYSCLK_APBCCR0_SCI_EN   0x01000000
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_SYSCLK_APBCCR1 SysCtl Register SYSCLK APBCCR1(SysCtl_SYSCLK_APBCCR1)
//! @{
//
//*****************************************************************************

//
//! MCTM Clock Enable
//
#define SYSCLK_APBCCR1_MCTM_EN  0x00000001

//
//! Watchdog Timer Clock Enable
//
#define SYSCLK_APBCCR1_WDT_EN   0x00000010

//
//! RTC Clock Enable
//
#define SYSCLK_APBCCR1_RTC_EN   0x00000040

//
//! Peripheral TIME0 Clock Enable
//
#define SYSCLK_APBCCR1_TIM0_EN  0x00000100

//
//! Peripheral TIME1 Clock Enable
//
#define SYSCLK_APBCCR1_TIM1_EN  0x00000200

//
//! USB Clock Enable
//
#define SYSCLK_APBCCR1_USB_EN   0x00004000

//
//! Peripheral BFTM0 Clock Enable
//
#define SYSCLK_APBCCR1_BFTM0_EN  0x00010000

//
//! Peripheral BFTM1 Clock Enable
//
#define SYSCLK_APBCCR1_BFTM1_EN  0x00020000

//
//! OPA/CMP 0 Clock Enable
//
#define SYSCLK_APBCCR1_OPA0_EN  0x00400000

//
//! OPA/CMP 1 Clock Enable
//
#define SYSCLK_APBCCR1_OPA1_EN  0x00800000

//
//! Peripheral ADC0 Clock Enable
//
#define SYSCLK_APBCCR1_ADC0_EN  0x01000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_SYSCLK_CKST SysCtl Register SYSCLK CKST(SysCtl_SYSCLK_CKST)
//! @{
//
//*****************************************************************************

//
//! PLL Clock Occupation Status Mask
//
#define SYSCLK_CKST_PLLST_M     0x00000F00

//
//! PLL Clock Occupation Status Shift
//
#define SYSCLK_CKST_PLLST_S     16

//
//! PLL used by System Clock
//
#define SYSCLK_CKST_PLLST_CK    0x00000100

//
//! PLL used by USART
//
#define SYSCLK_CKST_PLLST_USART 0x00000200

//
//! PLL used by USB
//
#define SYSCLK_CKST_PLLST_USB   0x00000400

//
//! PLL used by CSIF
//
#define SYSCLK_CKST_PLLST_CSIF  0x00000800

//
//! High Speed External Clock Occupation Status Mask
//
#define SYSCLK_CKST_HSEST_M     0x00030000

//
//! High Speed External Clock Occupation Status Shift
//
#define SYSCLK_CKST_HSEST_S     16

//
//! HSE used by System Clock (CK_SYS) (SW = 0x02)
//
#define SYSCLK_CKST_HSEST_CKSYS 0x00010000

//
//! HSE used by PLL
//
#define SYSCLK_CKST_HSEST_PLL   0x00020000

//
//! High Speed Internal Clock Occupation Status (CK_HSI) Mask
//
#define SYSCLK_CKST_HSIST_M     0x07000000

//
//! High Speed Internal Clock Occupation Status (CK_HSI) Shift
//
#define SYSCLK_CKST_HSIST_S     24

//
//! HSI used by System Clock (CK_SYS) (SW = 0x03)
//
#define SYSCLK_CKST_HSIST_CKSYS 0x01000000

//
//! HSI used by PLL
//
#define SYSCLK_CKST_HSIST_PLL   0x02000000

//
//! HSI used by Clock Monitor
//
#define SYSCLK_CKST_HSIST_MONITOR                                             \
                                0x04000000

//
//! Clock Switch Status Mask
//
#define SYSCLK_CKST_CKSWST_M    0xC0000000

//
//! Clock Switch Status Shift
//
#define SYSCLK_CKST_CKSWST_S    30

//
//! CK_PLL clock out as system clock
//
#define SYSCLK_CKST_CKSWST_PLL  0x40000000

//
//! CK_HSE as system clock
//
#define SYSCLK_CKST_CKSWST_HSE  0x80000000

//
//! CK_HSI as system clock
//
#define SYSCLK_CKST_CKSWST_HSI  0xC0000000

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_SYSCLK_LPCR SysCtl Register SYSCLK LPCR(SysCtl_SYSCLK_LPCR)
//! @{
//
//*****************************************************************************

//
//! Backup domain accessible by other power domains
//
#define SYSCLK_LPCR_BKISO_EN    0x00000001

//
//! USB Sleep Software Control Enable
//
#define SYSCLK_LPCR_USBSLEEP_EN 0x00000100

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_SYSCLK_DBGCR SysCtl Register SYSCLK DBGCR(SysCtl_SYSCLK_DBGCR)
//! @{
//
//*****************************************************************************

//
//! Debug Sleep Mode(LDO = On and FCLK = On and HCLK = On in Sleep mode)
//
#define SYSCLK_DBGCR_DBSLP      0x00000001

//
//! Debug Deep-Sleep mode 1(LDO = On and FCLK = On and HCLK = On in Deep-Sleep mode 1)
//
#define SYSCLK_DBGCR_DBDSLP1    0x00000002

//
//! Debug Power-Down Mode(LDO = On and FCLK = On and HCLK = On in Power-Down mode)
//
#define SYSCLK_DBGCR_DBPD       0x00000004

//
//! Watchdog Timer Debug Mode Enable
//
#define SYSCLK_DBGCR_DBWDT_EN   0x00000008

//
//! MCTM Debug Mode Enable
//
#define SYSCLK_DBGCR_MCTM_EN    0x00000010

//
//! GPTM0 Debug Mode Enable
//
#define SYSCLK_DBGCR_DBGPTM0_EN 0x00000040

//
//! GPTM1 Debug Mode Enable
//
#define SYSCLK_DBGCR_DBGPTM1_EN 0x00000080

//
//! USART0 Debug Mode Enable
//
#define SYSCLK_DBGCR_DBUSART0_EN                                               \
                                0x00000100
//
//! USART1 Debug Mode Enable
//
#define SYSCLK_DBGCR_DBUSART1_EN                                               \
                                0x00000200                             
//
//! SPI0 Debug Mode Enable
//
#define SYSCLK_DBGCR_DBGSPI0_EN 0x00000400

//
//! SPI1 Debug Mode Enable
//
#define SYSCLK_DBGCR_DBGSPI1_EN 0x00000800

//
//! I2C0 Debug Mode Enable
//
#define SYSCLK_DBGCR_DBGI2C0_EN 0x00001000

//
//! I2C1 Debug Mode Enable
//
#define SYSCLK_DBGCR_DBGI2C1_EN 0x00002000

//
//! Debug Deep-Sleep mode 2(LDO = On, FCLK = On and HCLK = On in Deep-Sleep mode 2)
//
#define SYSCLK_DBGCR_DBSLP2_EN  0x00004000

//
//! SCI Debug Mode Enable
//
#define SYSCLK_DBGCR_DBGSCI_EN  0x00008000

//
//! BFTM0 Debug Mode Enable
//
#define SYSCLK_DBGCR_DBGBFTM0_EN                                              \
                                0x00010000

//
//! BFTM1 Debug Mode Enable
//
#define SYSCLK_DBGCR_DBGBFTM1_EN                                              \
                                0x00020000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_RSTCU_GRSR SysCtl GRSR Register(SysCtl_RSTCU_GRSR)
//! @{
//
//*****************************************************************************
 
//
//! Core 1.8V Power On Reset Flag.
//
#define RSTCU_GRSR_PORSTF       0x00000008
 
//
//! Watchdog Timer Reset Flag.
//
#define RSTCU_GRSR_WDTRSTF      0x00000004

//
//! External Pin Reset Flag.
//
#define RSTCU_GRSR_EXTRSTF      0x00000002

//
//! System Reset Flag.
//
#define RSTCU_GRSR_SYSRSTF      0x00000001
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_SysCtl_Register_RSTCU_AHBPRSTR SysCtl AHBPRSTR Register(SysCtl_RSTCU_AHBPRSTR)
//! @{
//
//*****************************************************************************
 
//
//! DMA Reset.
//
#define RSTCU_AHBPRSTR_DMARST   0x00000001
 
//
//! CSIF Reset.
//
#define RSTCU_AHBPRSTR_CSIFRST  0x00000010
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_RSTCU_APBPRSTR0 SysCtl APBPRSTR0 Register(SysCtl_RSTCU_APBPRSTR0)
//! @{
//
//*****************************************************************************

//
//! I20C Reset.
//
#define RSTCU_APBPRSTR0_I2C0RST 0x00000001

//
//! I21C Reset.
//
#define RSTCU_APBPRSTR0_I2C1RST 0x00000002
 
//
//! SPI0 Reset.
//
#define RSTCU_APBPRSTR0_SPI0RST 0x00000010

//
//! SPI1 Reset.
//
#define RSTCU_APBPRSTR0_SPI1RST 0x00000020

//
//! USART0 Reset.
//
#define RSTCU_APBPRSTR0_UART0RST                                               \
                                0x00000100

//
//! USART1 Reset.
//
#define RSTCU_APBPRSTR1_UART1RST                                               \
                                0x00000200

//
//! Alternate Function I/O Reset.
//
#define RSTCU_APBPRSTR0_AFIORST 0x00004000

//
//! External Interrupt Controller Reset.
//
#define RSTCU_APBPRSTR0_EXTIRST 0x00008000

//
//! GPIO Port A Reset.
//
#define RSTCU_APBPRSTR0_GPIOARST                                               \
                                0x00010000

//
//! GPIO Port B Reset.
//
#define RSTCU_APBPRSTR0_GPIOBRST                                               \
                                0x00020000

//
//! GPIO Port C Reset.
//
#define RSTCU_APBPRSTR0_GPIOCRST                                               \
                                0x00040000

//
//! GPIO Port D Reset.
//
#define RSTCU_APBPRSTR0_GPIODRST                                               \
                                0x00080000

//
//! GPIO Port E Reset.
//
#define RSTCU_APBPRSTR0_GPIOERST                                               \
                                0x00100000
                                
//
//! Smart Card Reset.
//
#define RSTCU_APBPRSTR0_SCIRST                                                 \
                                0x01000000                               
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x_275x_SysCtl_Register_RSTCU_APBPRSTR1 SysCtl APBPRSTR1 Register(SysCtl_RSTCU_APBPRSTR1)
//! @{
//
//*****************************************************************************

//
//! MCTM Reset.
//
#define RSTCU_APBPRSTR1_MCTMRST 0x00000001

//
//! Watchdog Timer Reset.
//
#define RSTCU_APBPRSTR1_WDTRST  0x00000010
 
//
//! Timer0 Reset.
//
#define RSTCU_APBPRSTR1_TIM0RST 0x00000100

//
//! Timer1 Reset.
//
#define RSTCU_APBPRSTR1_TIM1RST 0x00000200

//
//! USB Reset.
//
#define RSTCU_APBPRSTR1_USBRST  0x00004000

//
//! BFTM0 Reset.
//
#define RSTCU_APBPRSTR1_BFTM0RST                                              \
                                0x00010000

//
//! BFTM1 Reset.
//
#define RSTCU_APBPRSTR1_BFTM1RST                                              \
                                0x00020000
                                
//
//! Comparator/OPA 0 Controller Reset.
//
#define RSTCU_APBPRSTR1_OPA0RST 0x00400000

//
//! Comparator/OPA 1 Controller Reset.
//
#define RSTCU_APBPRSTR1_OPA1RST 0x00800000

//
//! ADC Reset.
//
#define RSTCU_APBPRSTR1_ADCRST  0x01000000
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



