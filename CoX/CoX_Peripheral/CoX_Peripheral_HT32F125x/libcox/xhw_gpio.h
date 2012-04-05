//*****************************************************************************
//
//! \file xhw_gpio.h
//! \brief Macros used when accessing the GPIO control hardware.
//! \version V2.1.1.0
//! \date 2/24/2012
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


#ifndef __XHW_GPIO_H__
#define __XHW_GPIO_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup GPIO
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register HT32F125x GPIO Register
//! \brief Here are the detailed info of GPIO registers. 
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
//! \addtogroup HT32F125x_GPIO_Register_Offsets GPIO Register Offset(Map)
//! \brief Here is the GPIO register offset, users can get the register address
//! through <b>GPIO_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! GPIO Data Direction Control
//
#define GPIO_DIRCR              0x00000000  

//
//! GPIO Input Function Enable Control
//
#define GPIO_INER               0x00000004  

//
//! GPIO Pull-Up Selection
//
#define GPIO_PUR                0x00000008

//
//! GPIO Pull-Down Selection
//
#define GPIO_PDR                0x0000000C

//
//! GPIO Open Drain Selection
//
#define GPIO_ODR                0x00000010   

//
//! GPIO Drive Current Selection
//
#define GPIO_DRVR               0x00000014  

//
//! GPIO Lock
//
#define GPIO_LOCKER             0x00000018  

//
//! GPIO Data Input
//
#define GPIO_INR                0x0000001C  

//
//! GPIO Data Output
//
#define GPIO_OUTR               0x00000020  

//
//! GPIO Output Set and Reset Control
//
#define GPIO_SRR                0x00000024  

//
//! GPIO Output Reset Control
//
#define GPIO_RR                 0x00000028 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_AFIO_Register_Offsets AFIO Register Offset(Map)
//! \brief Here is the AFIO register offset, users can get the register address
//! through <b>GPIO_AFIO_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! EXTI Source Selection Register 0 
//
#define AFIO_ESSRO              0x00000000

//
//! EXTI Source Selection Register 1 
//
#define AFIO_ESSR1              0x00000004

//
//! GPIO PortA Configuration 
//
#define AFIO_GPACFGR            0x00000008

//
//! GPIO PortB Configuration
//
#define AFIO_GPBCFGR            0x0000000C

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_EXTI_Register_Offsets EXTI Register Offset(Map)
//! \brief Here is the EXTI register offset, users can get the register address
//! through <b>GPIO_EXTI_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! EXTI Interrupt 0 Configuration
//
#define EXTI_CFGR0              0x00000000

//
//! EXTI Interrupt 1 Configuration
//
#define EXTI_CFGR1              0x00000004

//
//! EXTI Interrupt 2 Configuration
//
#define EXTI_CFGR2              0x00000008

//
//! EXTI Interrupt 3 Configuration
//
#define EXTI_CFGR3              0x0000000C

//
//! EXTI Interrupt 4 Configuration
//
#define EXTI_CFGR4              0x00000010

//
//! EXTI Interrupt 5 Configuration
//
#define EXTI_CFGR5              0x00000014

//
//! EXTI Interrupt 6 Configuration
//
#define EXTI_CFGR6              0x00000018

//
//! EXTI Interrupt 7 Configuration
//
#define EXTI_CFGR7              0x0000001C

//
//! EXTI Interrupt 8 Configuration
//
#define EXTI_CFGR8              0x00000020

//
//! EXTI Interrupt 9 Configuration
//
#define EXTI_CFGR9              0x00000024

//
//! EXTI Interrupt 10 Configuration
//
#define EXTI_CFGR10             0x00000028

//
//! EXTI Interrupt 11 Configuration
//
#define EXTI_CFGR11             0x0000002C

//
//! EXTI Interrupt 12 Configuration
//
#define EXTI_CFGR12             0x00000030

//
//! EXTI Interrupt 13 Configuration
//
#define EXTI_CFGR13             0x00000034

//
//! EXTI Interrupt 14 Configuration
//
#define EXTI_CFGR14             0x00000038

//
//! EXTI Interrupt 15 Configuration
//
#define EXTI_CFGR15             0x0000003C

//
//! EXTI Interrupt Control
//
#define EXTI_ICR                0x00000040

//
//! EXTI Interrupt Edge Flag
//
#define EXTI_EDGEFLGR           0x00000044

//
//! EXTI Interrupt Edge Status
//
#define EXTI_EDGESR             0x00000048

//
//! EXTI Interrupt Software Set Command
//
#define EXTI_SSCR               0x0000004C

//
//! EXTI Interrupt Wakeup Control
//
#define EXTI_WAKUPCR            0x00000050

//
//! EXTI Interrupt Wakeup Polarity
//
#define EXTI_WAKUPPOLR          0x00000054

//
//! EXTI Interrupt Wakeup Flag
//
#define EXTI_WAKUPFLG           0x00000058

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_GPIO_DIRCR GPIO DIRCR Control Register(GPIO_DIRCR) 
//! \brief Defines for the bit fields in the GPIO_DIRCR register.
//! @{
//
//*****************************************************************************

//
//! Data Direction Selection mask
//
#define GPIO_DIRCR_PADIR_M      0x0000FFFF

//
//! Data Direction Selection shift
//
#define GPIO_DIRCR_PADIR_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_GPIO_INER GPIO Input Enable or Disable 
//!  Register(GPIO_INER)
//! \brief Defines for the bit fields in the GPIO_INER register.
//! @{
//
//*****************************************************************************

//
//! Input Function Enable mask
//
#define GPIO_INER_PAINEN_M      0x0000FFFF

//
//! Input Function Enable shift
//
#define GPIO_INER_PAINEN_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_GPIO_PUR GPIO Pull-up Selection Control
//!  Register(GPIO_PUR)
//! \brief Defines for the bit fields in the GPIO_PUR register.
//! @{
//
//*****************************************************************************

//
//! Pull-Up Selection mask
//
#define GPIO_PUR_PAPU_M         0x0000FFFF  

//
//! Pull-Up Selection shift
//
#define GPIO_PUR_PAPU_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_GPIO_PDR GPIO Pull-down Selection Control
//!  Register(GPIO_PDR)
//! \brief Defines for the bit fields in the GPIO_PDR register.
//! @{
//
//*****************************************************************************

//
//! Pull-Down Selection mask
//
#define GPIO_PDR_PAPD_M         0x0000FFFF  

//
//! Pull-Down Selection shift
//
#define GPIO_PDR_PAPD_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_GPIO_ODR GPIO open drain Selection Control
//!  Register(GPIO_ODR)
//! \brief Defines for the bit fields in the GPIO_ODR register.
//! @{
//
//*****************************************************************************

//
//! open drain Selection mask
//
#define GPIO_ODR_PAOD_M         0x0000FFFF  

//
//! open drain Selection shift
//
#define GPIO_ODR_PAOD_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_GPIO_DRVR GPIO Current Drive Selection Control
//!  Register(GPIO_DRVR)
//! \brief Defines for the bit fields in the GPIO_DRVR register.
//! @{
//
//*****************************************************************************

//
//! Current Drive Selection mask
//
#define GPIO_DRVR_PADV_M        0x000000FF  

//
//! Current Drive Selection shift
//
#define GPIO_DRVR_PADV_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_GPIO_LOCKER GPIO Lock Register(GPIO_LOCKER)
//! \brief Defines for the bit fields in the GPIO_LOCKER register.
//! @{
//
//*****************************************************************************

//
//! GPIO Port Lock Key
//
#define GPIO_LOCKER_PALKEY      0x5FA00000  

//
//! GPIO Port Pin Lock Control Bits mask
//
#define GPIO_LOCKER_PALOCK_M    0x0000FFFF

//
//! GPIO Port Pin Lock Control Bits shift
//
#define GPIO_LOCKER_PALOCK_S    0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_GPIO_INR GPIO Data Input Register(GPIO_INR)
//! \brief Defines for the bit fields in the GPIO_INR register.
//! @{
//
//*****************************************************************************

//
//! GPIO Port Pin Data Input Bits mask
//
#define GPIO_INR_PADIN_M        0x0000FFFF

//
//! GPIO Port Pin Data Input Bits shift
//
#define GPIO_INR_PADIN_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_GPIO_OUTR GPIO Data Output Register(GPIO_OUTR)
//! \brief Defines for the bit fields in the GPIO_OUTR register.
//! @{
//
//*****************************************************************************

//
//! GPIO Port Pin Data Output Bits mask
//
#define GPIO_OUTR_PADOUT_M      0x0000FFFF

//
//! GPIO Port Pin Data Output Bits shift
//
#define GPIO_OUTR_PADOUT_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_GPIO_SRR GPIO Output Set/Reset Control
//!  Register(GPIO_SRR)
//! \brief Defines for the bit fields in the GPIO_SRR register.
//! @{
//
//*****************************************************************************

//
//! Output Reset Control Bits mask
//
#define GPIO_SRR_PARST_M        0xFFFF0000

//
//! Output Reset Control Bits shift
//
#define GPIO_SRR_PARST_S        16

//
//! Output Set Control Bits mask
//
#define GPIO_SRR_PASET_M        0x0000FFFF

//
//! Output Set Control Bits shift
//
#define GPIO_SRR_PASET_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_GPIO_RR GPIO Output Reset Control
//!  Register(GPIO_RR)
//! \brief Defines for the bit fields in the GPIO_RR register.
//! @{
//
//*****************************************************************************

//
//! Output Set Control Bits mask
//
#define GPIO_RR_PASET_M        0x0000FFFF

//
//! Output Set Control Bits shift
//
#define GPIO_RR_PASET_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_AFIO_ESSRO EXTI Source Selection 
//!  Register0(AFIO_ESSRO)
//! \brief Defines for the bit fields in the AFIO_ESSRO register.
//! @{
//
//*****************************************************************************

//
//! EXTIn Pin Selection PB
//
#define AFIO_ESSRO_EXTINPIN_B   0x00000001

//
//! EXTIn Pin Selection PA
//
#define AFIO_ESSRO_EXTINPIN_A   0x00000000

//
//! EXTIn Pin Selection shift
//
#define AFIO_ESSRO_EXTI0PIN_S   0
#define AFIO_ESSRO_EXTI1PIN_S   4
#define AFIO_ESSRO_EXTI2PIN_S   8
#define AFIO_ESSRO_EXTI3PIN_S   12
#define AFIO_ESSRO_EXTI4PIN_S   16
#define AFIO_ESSRO_EXTI5PIN_S   20
#define AFIO_ESSRO_EXTI6PIN_S   24
#define AFIO_ESSRO_EXTI7PIN_S   28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_AFIO_ESSR1 EXTI Source Selection 
//!  Register1(AFIO_ESSR1)
//! \brief Defines for the bit fields in the AFIO_ESSR1 register.
//! @{
//
//*****************************************************************************

//
//! EXTIn Pin Selection PB
//
#define AFIO_ESSR1_EXTINPIN_B   0x00000001

//
//! EXTIn Pin Selection PA
//
#define AFIO_ESSR1_EXTINPIN_A   0x00000000

//
//! EXTIn Pin Selection shift
//
#define AFIO_ESSR1_EXTI8PIN_S   0
#define AFIO_ESSR1_EXTI9PIN_S   4
#define AFIO_ESSR1_EXTI10PIN_S  8
#define AFIO_ESSR1_EXTI11PIN_S  12
#define AFIO_ESSR1_EXTI12PIN_S  16
#define AFIO_ESSR1_EXTI13PIN_S  20
#define AFIO_ESSR1_EXTI14PIN_S  24
#define AFIO_ESSR1_EXTI15PIN_S  28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_AFIO_GPACFGR alternative function Selection 
//!  Register(AFIO_GPACFGR)
//! \brief Defines for the bit fields in the AFIO_GPACFGR register.
//! @{
//
//*****************************************************************************

//
//! Port bit AFIO Configuration mask
//
#define AFIO_GPACFGR_FUN_M      0x00000003

//
//! Port bit AFIO Configuration
//
#define AFIO_GPACFGR_FUN0       0x00000000
#define AFIO_GPACFGR_FUN1       0x00000001
#define AFIO_GPACFGR_FUN2       0x00000002

#define AFIO_GPACFGR_FUN3       0x00000003

//
//! Port bit AFIO bit0 Configuration shift
//
#define AFIO_GPACFGR_BIT0_S     0

//
//! Port bit AFIO bit1 Configuration shift
//
#define AFIO_GPACFGR_BIT1_S     2

//
//! Port bit AFIO bit2 Configuration shift
//
#define AFIO_GPACFGR_BIT2_S     4

//
//! Port bit AFIO bit3 Configuration shift
//
#define AFIO_GPACFGR_BIT3_S     6

//
//! Port bit AFIO bit4 Configuration shift
//
#define AFIO_GPACFGR_BIT4_S     8

//
//! Port bit AFIO bit5 Configuration shift
//
#define AFIO_GPACFGR_BIT5_S     10

//
//! Port bit AFIO bit6 Configuration shift
//
#define AFIO_GPACFGR_BIT6_S     12

//
//! Port bit AFIO bit7 Configuration shift
//
#define AFIO_GPACFGR_BIT7_S     14

//
//! Port bit AFIO bit8 Configuration shift
//
#define AFIO_GPACFGR_BIT8_S     16

//
//! Port bit AFIO bit9 Configuration shift
//
#define AFIO_GPACFGR_BIT9_S     18

//
//! Port bit AFIO bit10 Configuration shift
//
#define AFIO_GPACFGR_BIT10_S    20

//
//! Port bit AFIO bit11 Configuration shift
//
#define AFIO_GPACFGR_BIT11_S    22

//
//! Port bit AFIO bit12 Configuration shift
//
#define AFIO_GPACFGR_BIT12_S    24

//
//! Port bit AFIO bit13 Configuration shift
//
#define AFIO_GPACFGR_BIT13_S    26

//
//! Port bit AFIO bit14 Configuration shift
//
#define AFIO_GPACFGR_BIT14_S    28

//
//! Port bit AFIO bit15 Configuration shift
//
#define AFIO_GPACFGR_BIT15_S    30

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_AFIO_GPBCFGR alternative function Selection 
//!  Register(AFIO_GPBCFGR)
//! \brief Defines for the bit fields in the AFIO_GPBCFGR register.
//! @{
//
//*****************************************************************************

//
//! Port bit AFIO Configuration mask
//
#define AFIO_GPBCFGR_FUN_M      0x00000003

//
//! Port bit AFIO Configuration
//
#define AFIO_GPBCFGR_FUN0       0x00000000
#define AFIO_GPBCFGR_FUN1       0x00000001
#define AFIO_GPBCFGR_FUN2       0x00000002

#define AFIO_GPBCFGR_FUN3       0x00000003

//
//! Port bit AFIO bit0 Configuration shift
//
#define AFIO_GPBCFGR_BIT0_S     0

//
//! Port bit AFIO bit1 Configuration shift
//
#define AFIO_GPBCFGR_BIT1_S     2

//
//! Port bit AFIO bit2 Configuration shift
//
#define AFIO_GPBCFGR_BIT2_S     4

//
//! Port bit AFIO bit3 Configuration shift
//
#define AFIO_GPBCFGR_BIT3_S     6

//
//! Port bit AFIO bit4 Configuration shift
//
#define AFIO_GPBCFGR_BIT4_S     8

//
//! Port bit AFIO bit5 Configuration shift
//
#define AFIO_GPBCFGR_BIT5_S     10

//
//! Port bit AFIO bit6 Configuration shift
//
#define AFIO_GPBCFGR_BIT6_S     12

//
//! Port bit AFIO bit7 Configuration shift
//
#define AFIO_GPBCFGR_BIT7_S     14

//
//! Port bit AFIO bit8 Configuration shift
//
#define AFIO_GPBCFGR_BIT8_S     16

//
//! Port bit AFIO bit9 Configuration shift
//
#define AFIO_GPBCFGR_BIT9_S     18

//
//! Port bit AFIO bit10 Configuration shift
//
#define AFIO_GPBCFGR_BIT10_S    20

//
//! Port bit AFIO bit11 Configuration shift
//
#define AFIO_GPBCFGR_BIT11_S    22

//
//! Port bit AFIO bit12 Configuration shift
//
#define AFIO_GPBCFGR_BIT12_S    24

//
//! Port bit AFIO bit13 Configuration shift
//
#define AFIO_GPBCFGR_BIT13_S    26

//
//! Port bit AFIO bit14 Configuration shift
//
#define AFIO_GPBCFGR_BIT14_S    28

//
//! Port bit AFIO bit15 Configuration shift
//
#define AFIO_GPBCFGR_BIT15_S    30

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR0 EXTI Interrupt0 Configuration 
//!  Register(EXTI_CFGR0)
//! \brief Defines for the bit fields in the EXTI_CFGR0 register.
//! @{
//
//*****************************************************************************

//
//! EXTI0 De-bounce Circuit Enable
//
#define EXTI_CFGR0_DBEN         0x80000000

//
//! EXTI0 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR0_SRCTYPE_M    0x70000000

//
//! EXTI0 Interrupt Low-level Sensitive
//
#define EXTI_CFGR0_SRCTYPE_LOW  0x00000000

//
//! EXTI0 Interrupt How-level Sensitive
//
#define EXTI_CFGR0_SRCTYPE_HIGH 0x10000000

//
//! EXTI0 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR0_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI0 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR0_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI0 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR0_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI0 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR0_SRCTYPE_S    28

//
//! EXTI0 De-bounce Counter mask
//
#define EXTI_CFGR0_DBCNT_M      0x0FFFFFFF

//
//! EXTI0 De-bounce Counter shift
//
#define EXTI_CFGR0_DBCNT_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR1 EXTI Interrupt1 Configuration 
//!  Register(EXTI_CFGR1)
//! \brief Defines for the bit fields in the EXTI_CFGR1 register.
//! @{
//
//*****************************************************************************

//
//! EXTI1 De-bounce Circuit Enable
//
#define EXTI_CFGR1_DBEN         0x80000000

//
//! EXTI1 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR1_SRCTYPE_M    0x70000000

//
//! EXTI1 Interrupt Low-level Sensitive
//
#define EXTI_CFGR1_SRCTYPE_LOW  0x00000000

//
//! EXTI1 Interrupt How-level Sensitive
//
#define EXTI_CFGR1_SRCTYPE_HIGH 0x10000000

//
//! EXTI1 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR1_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI1 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR1_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI1 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR1_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI1 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR1_SRCTYPE_S    28

//
//! EXTI1 De-bounce Counter mask
//
#define EXTI_CFGR1_DBCNT_M      0x0FFFFFFF

//
//! EXTI1 De-bounce Counter shift
//
#define EXTI_CFGR1_DBCNT_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR2 EXTI Interrupt1 Configuration 
//!  Register(EXTI_CFGR2)
//! \brief Defines for the bit fields in the EXTI_CFGR2 register.
//! @{
//
//*****************************************************************************

//
//! EXTI2 De-bounce Circuit Enable
//
#define EXTI_CFGR2_DBEN         0x80000000

//
//! EXTI2 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR2_SRCTYPE_M    0x70000000

//
//! EXTI2 Interrupt Low-level Sensitive
//
#define EXTI_CFGR2_SRCTYPE_LOW  0x00000000

//
//! EXTI2 Interrupt How-level Sensitive
//
#define EXTI_CFGR2_SRCTYPE_HIGH 0x10000000

//
//! EXTI2 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR2_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI2 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR2_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI2 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR2_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI2 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR2_SRCTYPE_S    28

//
//! EXTI2 De-bounce Counter mask
//
#define EXTI_CFGR2_DBCNT_M      0x0FFFFFFF

//
//! EXTI2 De-bounce Counter shift
//
#define EXTI_CFGR2_DBCNT_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR3 EXTI Interrupt3 Configuration 
//!  Register(EXTI_CFGR3)
//! \brief Defines for the bit fields in the EXTI_CFGR3 register.
//! @{
//
//*****************************************************************************

//
//! EXTI3 De-bounce Circuit Enable
//
#define EXTI_CFGR3_DBEN         0x80000000

//
//! EXTI3 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR3_SRCTYPE_M    0x70000000

//
//! EXTI3 Interrupt Low-level Sensitive
//
#define EXTI_CFGR3_SRCTYPE_LOW  0x00000000

//
//! EXTI3 Interrupt How-level Sensitive
//
#define EXTI_CFGR3_SRCTYPE_HIGH 0x10000000

//
//! EXTI3 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR3_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI3 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR3_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI3 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR3_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI3 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR3_SRCTYPE_S    28

//
//! EXTI3 De-bounce Counter mask
//
#define EXTI_CFGR3_DBCNT_M      0x0FFFFFFF

//
//! EXTI3 De-bounce Counter shift
//
#define EXTI_CFGR3_DBCNT_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR4 EXTI Interrupt4 Configuration 
//!  Register(EXTI_CFGR4)
//! \brief Defines for the bit fields in the EXTI_CFGR4 register.
//! @{
//
//*****************************************************************************

//
//! EXTI4 De-bounce Circuit Enable
//
#define EXTI_CFGR4_DBEN         0x80000000

//
//! EXTI4 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR4_SRCTYPE_M    0x70000000

//
//! EXTI4 Interrupt Low-level Sensitive
//
#define EXTI_CFGR4_SRCTYPE_LOW  0x00000000

//
//! EXTI4 Interrupt How-level Sensitive
//
#define EXTI_CFGR4_SRCTYPE_HIGH 0x10000000

//
//! EXTI4 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR4_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI4 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR4_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI4 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR4_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI4 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR4_SRCTYPE_S    28

//
//! EXTI4 De-bounce Counter mask
//
#define EXTI_CFGR4_DBCNT_M      0x0FFFFFFF

//
//! EXTI4 De-bounce Counter shift
//
#define EXTI_CFGR4_DBCNT_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR5 EXTI Interrupt5 Configuration 
//!  Register(EXTI_CFGR5)
//! \brief Defines for the bit fields in the EXTI_CFGR5 register.
//! @{
//
//*****************************************************************************

//
//! EXTI5 De-bounce Circuit Enable
//
#define EXTI_CFGR5_DBEN         0x80000000

//
//! EXTI5 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR5_SRCTYPE_M    0x70000000

//
//! EXTI5 Interrupt Low-level Sensitive
//
#define EXTI_CFGR5_SRCTYPE_LOW  0x00000000

//
//! EXTI5 Interrupt How-level Sensitive
//
#define EXTI_CFGR5_SRCTYPE_HIGH 0x10000000

//
//! EXTI5 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR5_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI5 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR5_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI5 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR5_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI5 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR5_SRCTYPE_S    28

//
//! EXTI5 De-bounce Counter mask
//
#define EXTI_CFGR5_DBCNT_M      0x0FFFFFFF

//
//! EXTI5 De-bounce Counter shift
//
#define EXTI_CFGR5_DBCNT_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR6 EXTI Interrupt6 Configuration 
//!  Register(EXTI_CFGR6)
//! \brief Defines for the bit fields in the EXTI_CFGR6 register.
//! @{
//
//*****************************************************************************

//
//! EXTI6 De-bounce Circuit Enable
//
#define EXTI_CFGR6_DBEN         0x80000000

//
//! EXTI6 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR6_SRCTYPE_M    0x70000000

//
//! EXTI6 Interrupt Low-level Sensitive
//
#define EXTI_CFGR6_SRCTYPE_LOW  0x00000000

//
//! EXTI6 Interrupt How-level Sensitive
//
#define EXTI_CFGR6_SRCTYPE_HIGH 0x10000000

//
//! EXTI6 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR6_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI6 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR6_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI6 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR6_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI6 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR6_SRCTYPE_S    28

//
//! EXTI6 De-bounce Counter mask
//
#define EXTI_CFGR6_DBCNT_M      0x0FFFFFFF

//
//! EXTI6 De-bounce Counter shift
//
#define EXTI_CFGR6_DBCNT_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR7 EXTI Interrupt7 Configuration 
//!  Register(EXTI_CFGR7)
//! \brief Defines for the bit fields in the EXTI_CFGR7 register.
//! @{
//
//*****************************************************************************

//
//! EXTI7 De-bounce Circuit Enable
//
#define EXTI_CFGR7_DBEN         0x80000000

//
//! EXTI7 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR7_SRCTYPE_M    0x70000000

//
//! EXTI7 Interrupt Low-level Sensitive
//
#define EXTI_CFGR7_SRCTYPE_LOW  0x00000000

//
//! EXTI7 Interrupt How-level Sensitive
//
#define EXTI_CFGR7_SRCTYPE_HIGH 0x10000000

//
//! EXTI7 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR7_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI7 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR7_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI7 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR7_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI7 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR7_SRCTYPE_S    28

//
//! EXTI7 De-bounce Counter mask
//
#define EXTI_CFGR7_DBCNT_M      0x0FFFFFFF

//
//! EXTI7 De-bounce Counter shift
//
#define EXTI_CFGR7_DBCNT_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR8 EXTI Interrupt8 Configuration 
//!  Register(EXTI_CFGR8)
//! \brief Defines for the bit fields in the EXTI_CFGR8 register.
//! @{
//
//*****************************************************************************

//
//! EXTI8 De-bounce Circuit Enable
//
#define EXTI_CFGR8_DBEN         0x80000000

//
//! EXTI8 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR8_SRCTYPE_M    0x70000000

//
//! EXTI8 Interrupt Low-level Sensitive
//
#define EXTI_CFGR8_SRCTYPE_LOW  0x00000000

//
//! EXTI8 Interrupt How-level Sensitive
//
#define EXTI_CFGR8_SRCTYPE_HIGH 0x10000000

//
//! EXTI8 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR8_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI8 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR8_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI8 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR8_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI8 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR8_SRCTYPE_S    28

//
//! EXTI8 De-bounce Counter mask
//
#define EXTI_CFGR8_DBCNT_M      0x0FFFFFFF

//
//! EXTI8 De-bounce Counter shift
//
#define EXTI_CFGR8_DBCNT_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR9 EXTI Interrupt9 Configuration 
//!  Register(EXTI_CFGR9)
//! \brief Defines for the bit fields in the EXTI_CFGR9 register.
//! @{
//
//*****************************************************************************

//
//! EXTI9 De-bounce Circuit Enable
//
#define EXTI_CFGR9_DBEN         0x80000000

//
//! EXTI9 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR9_SRCTYPE_M    0x70000000

//
//! EXTI9 Interrupt Low-level Sensitive
//
#define EXTI_CFGR9_SRCTYPE_LOW  0x00000000

//
//! EXTI9 Interrupt How-level Sensitive
//
#define EXTI_CFGR9_SRCTYPE_HIGH 0x10000000

//
//! EXTI9 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR9_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI9 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR9_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI9 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR9_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI9 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR9_SRCTYPE_S    28

//
//! EXTI9 De-bounce Counter mask
//
#define EXTI_CFGR9_DBCNT_M      0x0FFFFFFF

//
//! EXTI9 De-bounce Counter shift
//
#define EXTI_CFGR9_DBCNT_S      0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR10 EXTI Interrupt10 Configuration 
//!  Register(EXTI_CFGR10)
//! \brief Defines for the bit fields in the EXTI_CFGR10 register.
//! @{
//
//*****************************************************************************

//
//! EXTI10 De-bounce Circuit Enable
//
#define EXTI_CFGR10_DBEN        0x80000000

//
//! EXTI10 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR10_SRCTYPE_M   0x70000000

//
//! EXTI10 Interrupt Low-level Sensitive
//
#define EXTI_CFGR10_SRCTYPE_LOW 0x00000000

//
//! EXTI10 Interrupt How-level Sensitive
//
#define EXTI_CFGR10_SRCTYPE_HIGH                                               \
                                0x10000000

//
//! EXTI10 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR10_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI10 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR10_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI10 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR10_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI10 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR10_SRCTYPE_S   28

//
//! EXTI10 De-bounce Counter mask
//
#define EXTI_CFGR10_DBCNT_M     0x0FFFFFFF

//
//! EXTI10 De-bounce Counter shift
//
#define EXTI_CFGR10_DBCNT_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR11 EXTI Interrupt11 Configuration 
//!  Register(EXTI_CFGR11)
//! \brief Defines for the bit fields in the EXTI_CFGR11 register.
//! @{
//
//*****************************************************************************

//
//! EXTI11 De-bounce Circuit Enable
//
#define EXTI_CFGR11_DBEN        0x80000000

//
//! EXTI11 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR11_SRCTYPE_M   0x70000000

//
//! EXTI11 Interrupt Low-level Sensitive
//
#define EXTI_CFGR11_SRCTYPE_LOW 0x00000000

//
//! EXTI11 Interrupt How-level Sensitive
//
#define EXTI_CFGR11_SRCTYPE_HIGH                                               \
                                0x10000000

//
//! EXTI11 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR11_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI11 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR11_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI11 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR11_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI11 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR11_SRCTYPE_S   28

//
//! EXTI11 De-bounce Counter mask
//
#define EXTI_CFGR11_DBCNT_M     0x0FFFFFFF

//
//! EXTI11 De-bounce Counter shift
//
#define EXTI_CFGR11_DBCNT_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR12 EXTI Interrupt12 Configuration 
//!  Register(EXTI_CFGR12)
//! \brief Defines for the bit fields in the EXTI_CFGR12 register.
//! @{
//
//*****************************************************************************

//
//! EXTI12 De-bounce Circuit Enable
//
#define EXTI_CFGR12_DBEN        0x80000000

//
//! EXTI12 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR12_SRCTYPE_M   0x70000000

//
//! EXTI12 Interrupt Low-level Sensitive
//
#define EXTI_CFGR12_SRCTYPE_LOW 0x00000000

//
//! EXTI12 Interrupt How-level Sensitive
//
#define EXTI_CFGR12_SRCTYPE_HIGH                                               \
                                0x10000000

//
//! EXTI12 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR12_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI12 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR12_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI12 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR12_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI12 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR12_SRCTYPE_S   28

//
//! EXTI12 De-bounce Counter mask
//
#define EXTI_CFGR12_DBCNT_M     0x0FFFFFFF

//
//! EXTI12 De-bounce Counter shift
//
#define EXTI_CFGR12_DBCNT_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR13 EXTI Interrupt13 Configuration 
//!  Register(EXTI_CFGR13)
//! \brief Defines for the bit fields in the EXTI_CFGR13 register.
//! @{
//
//*****************************************************************************

//
//! EXTI13 De-bounce Circuit Enable
//
#define EXTI_CFGR13_DBEN        0x80000000

//
//! EXTI13 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR13_SRCTYPE_M   0x70000000

//
//! EXTI13 Interrupt Low-level Sensitive
//
#define EXTI_CFGR13_SRCTYPE_LOW 0x00000000

//
//! EXTI13 Interrupt How-level Sensitive
//
#define EXTI_CFGR13_SRCTYPE_HIGH                                               \
                                0x10000000

//
//! EXTI13 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR13_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI13 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR13_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI13 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR13_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI13 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR13_SRCTYPE_S   28

//
//! EXTI13 De-bounce Counter mask
//
#define EXTI_CFGR13_DBCNT_M     0x0FFFFFFF

//
//! EXTI13 De-bounce Counter shift
//
#define EXTI_CFGR13_DBCNT_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR14 EXTI Interrupt14 Configuration 
//!  Register(EXTI_CFGR14)
//! \brief Defines for the bit fields in the EXTI_CFGR14 register.
//! @{
//
//*****************************************************************************

//
//! EXTI14 De-bounce Circuit Enable
//
#define EXTI_CFGR14_DBEN        0x80000000

//
//! EXTI14 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR14_SRCTYPE_M   0x70000000

//
//! EXTI14 Interrupt Low-level Sensitive
//
#define EXTI_CFGR14_SRCTYPE_LOW 0x00000000

//
//! EXTI14 Interrupt How-level Sensitive
//
#define EXTI_CFGR14_SRCTYPE_HIGH                                               \
                                0x10000000

//
//! EXTI14 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR14_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI14 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR14_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI14 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR14_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI14 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR14_SRCTYPE_S   28

//
//! EXTI14 De-bounce Counter mask
//
#define EXTI_CFGR14_DBCNT_M     0x0FFFFFFF

//
//! EXTI14 De-bounce Counter shift
//
#define EXTI_CFGR14_DBCNT_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_CFGR15 EXTI Interrupt15 Configuration 
//!  Register(EXTI_CFGR15)
//! \brief Defines for the bit fields in the EXTI_CFGR15 register.
//! @{
//
//*****************************************************************************

//
//! EXTI15 De-bounce Circuit Enable
//
#define EXTI_CFGR15_DBEN        0x80000000

//
//! EXTI15 Interrupt Source Trigger Type mask
//
#define EXTI_CFGR15_SRCTYPE_M   0x70000000

//
//! EXTI15 Interrupt Low-level Sensitive
//
#define EXTI_CFGR15_SRCTYPE_LOW 0x00000000

//
//! EXTI15 Interrupt How-level Sensitive
//
#define EXTI_CFGR15_SRCTYPE_HIGH                                               \
                                0x10000000

//
//! EXTI15 Interrupt Negative-edge Sensitive
//
#define EXTI_CFGR15_SRCTYPE_NEDGE                                              \
                                0x20000000

//
//! EXTI15 Interrupt Positive-edge Sensitive
//
#define EXTI_CFGR15_SRCTYPE_PEDGE                                              \
                                0x30000000

//
//! EXTI15 Interrupt Both-edge Sensitive
//
#define EXTI_CFGR15_SRCTYPE_BEDGE                                              \
                                0x40000000

//
//! EXTI15 Interrupt Source Trigger Type shift
//
#define EXTI_CFGR15_SRCTYPE_S   28

//
//! EXTI15 De-bounce Counter mask
//
#define EXTI_CFGR15_DBCNT_M     0x0FFFFFFF

//
//! EXTI15 De-bounce Counter shift
//
#define EXTI_CFGR15_DBCNT_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_ICR EXTI Interrupt Control 
//!  Register(EXTI_ICR)
//! \brief Defines for the bit fields in the EXTI_ICR register.
//! @{
//
//*****************************************************************************

//
//! EXTI0 Interrupt Enable
//
#define EXTI_ICR_EXTI0EN        0x00000001

//
//! EXTI1 Interrupt Enable
//
#define EXTI_ICR_EXTI1EN        0x00000002

//
//! EXTI2 Interrupt Enable
//
#define EXTI_ICR_EXTI2EN        0x00000004

//
//! EXTI3 Interrupt Enable
//
#define EXTI_ICR_EXTI3EN        0x00000008

//
//! EXTI4 Interrupt Enable
//
#define EXTI_ICR_EXTI4EN        0x00000010

//
//! EXTI5 Interrupt Enable
//
#define EXTI_ICR_EXTI5EN        0x00000020

//
//! EXTI6 Interrupt Enable
//
#define EXTI_ICR_EXTI6EN        0x00000040

//
//! EXTI7 Interrupt Enable
//
#define EXTI_ICR_EXTI7EN        0x00000080

//
//! EXTI8 Interrupt Enable
//
#define EXTI_ICR_EXTI8EN        0x00000100

//
//! EXTI9 Interrupt Enable
//
#define EXTI_ICR_EXTI9EN        0x00000200

//
//! EXTI10 Interrupt Enable
//
#define EXTI_ICR_EXTI10EN       0x00000400

//
//! EXTI11 Interrupt Enable
//
#define EXTI_ICR_EXTI11EN       0x00000800

//
//! EXTI12 Interrupt Enable
//
#define EXTI_ICR_EXTI12EN       0x00001000

//
//! EXTI13 Interrupt Enable
//
#define EXTI_ICR_EXTI13EN       0x00002000

//
//! EXTI14 Interrupt Enable
//
#define EXTI_ICR_EXTI14EN       0x00004000

//
//! EXTI125 Interrupt Enable
//
#define EXTI_ICR_EXTI15EN       0x00008000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_EDGEFLGR EXTI Edge Detection Flag 
//!  Register(EXTI_EDGEFLGR)
//! \brief Defines for the bit fields in the EXTI_EDGEFLGR register.
//! @{
//
//*****************************************************************************

//
//! EXTI0 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI0EDF  0x00000001

//
//! EXTI1 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI1EDF  0x00000002

//
//! EXTI2 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI2EDF  0x00000004

//
//! EXTI3 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI3EDF  0x00000008

//
//! EXTI4 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI4EDF  0x00000010

//
//! EXTI5 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI5EDF  0x00000020

//
//! EXTI6 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI6EDF  0x00000040

//
//! EXTI7 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI7EDF  0x00000080

//
//! EXTI8 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI8EDF  0x00000100

//
//! EXTI9 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI9EDF  0x00000200

//
//! EXTI10 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI10EDF 0x00000400

//
//! EXTI11 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI11EDF 0x00000800

//
//! EXTI12 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI12EDF 0x00001000

//
//! EXTI13 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI13EDF 0x00002000

//
//! EXTI14 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI14EDF 0x00004000

//
//! EXTI15 Edge Detection Flag
//
#define EXTI_EDGEFLGR_EXTI15EDF 0x00008000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_EDGESR EXTI Edge Detection Status 
//!  Register(EXTI_EDGESR)
//! \brief Defines for the bit fields in the EXTI_EDGESR register.
//! @{
//
//*****************************************************************************

//
//! EXTI0 Edge Detection Status
//
#define EXTI_EDGESR_EXTI0EDS_P  0x00000001

//
//! EXTI1 Edge Detection Status
//
#define EXTI_EDGESR_EXTI1EDS_P  0x00000002

//
//! EXTI2 Edge Detection Status
//
#define EXTI_EDGESR_EXTI2EDS_P  0x00000004

//
//! EXTI3 Edge Detection Status
//
#define EXTI_EDGESR_EXTI3EDS_P  0x00000008

//
//! EXTI4 Edge Detection Status
//
#define EXTI_EDGESR_EXTI4EDS_P  0x00000010

//
//! EXTI5 Edge Detection Status
//
#define EXTI_EDGESR_EXTI5EDS_P  0x00000020

//
//! EXTI6 Edge Detection Status
//
#define EXTI_EDGESR_EXTI6EDS_P  0x00000040

//
//! EXTI7 Edge Detection Status
//
#define EXTI_EDGESR_EXTI7EDS_P  0x00000080

//
//! EXTI8 Edge Detection Status
//
#define EXTI_EDGESR_EXTI8EDS_P  0x00000100

//
//! EXTI9 Edge Detection Status
//
#define EXTI_EDGESR_EXTI9EDS_P  0x00000200

//
//! EXTI10 Edge Detection Status
//
#define EXTI_EDGESR_EXTI10EDS_P 0x00000400

//
//! EXTI11 Edge Detection Status
//
#define EXTI_EDGESR_EXTI11EDS_P 0x00000800

//
//! EXTI12 Edge Detection Status
//
#define EXTI_EDGESR_EXTI12EDS_P 0x00001000

//
//! EXTI13 Edge Detection Status
//
#define EXTI_EDGESR_EXTI13EDS_P 0x00002000

//
//! EXTI14 Edge Detection Status
//
#define EXTI_EDGESR_EXTI14EDS_P 0x00004000

//
//! EXTI15 Edge Detection Status
//
#define EXTI_EDGESR_EXTI15EDS_P 0x00008000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_SSCR EXTI Software Set Command 
//!  Register(EXTI_SSCR)
//! \brief Defines for the bit fields in the EXTI_SSCR register.
//! @{
//
//*****************************************************************************

//
//! EXTI0 Software Set Command
//
#define EXTI_SSCR_EXTI0SC       0x00000001

//
//! EXTI1 Software Set Command
//
#define EXTI_SSCR_EXTI1SC       0x00000002

//
//! EXTI2 Software Set Command
//
#define EXTI_SSCR_EXTI2SC       0x00000004

//
//! EXTI3 Software Set Command
//
#define EXTI_SSCR_EXTI3SC       0x00000008

//
//! EXTI4 Software Set Command
//
#define EXTI_SSCR_EXTI4SC       0x00000010

//
//! EXTI5 Software Set Command
//
#define EXTI_SSCR_EXTI5SC       0x00000020

//
//! EXTI6 Software Set Command
//
#define EXTI_SSCR_EXTI6SC       0x00000040

//
//! EXTI7 Software Set Command
//
#define EXTI_SSCR_EXTI7SC       0x00000080

//
//! EXTI8 Software Set Command
//
#define EXTI_SSCR_EXTI8SC       0x00000100

//
//! EXTI9 Software Set Command
//
#define EXTI_SSCR_EXTI9SC       0x00000200

//
//! EXTI10 Software Set Command
//
#define EXTI_SSCR_EXTI10SC      0x00000400

//
//! EXTI11 Software Set Command
//
#define EXTI_SSCR_EXTI11SC      0x00000800

//
//! EXTI12 Software Set Command
//
#define EXTI_SSCR_EXTI12SC      0x00001000

//
//! EXTI13 Software Set Command
//
#define EXTI_SSCR_EXTI13SC      0x00002000

//
//! EXTI14 Software Set Command
//
#define EXTI_SSCR_EXTI14SC      0x00004000

//
//! EXTI15 Software Set Command
//
#define EXTI_SSCR_EXTI15SC      0x00008000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_SSCR EXTI Software Set Command 
//!  Register(EXTI_SSCR)
//! \brief Defines for the bit fields in the EXTI_SSCR register.
//! @{
//
//*****************************************************************************

//
//! EXTI Event Wakeup Interrupt Enable
//
#define EXTI_WAKUPCR_EVWUPIEN   0x80000000

//
//! EXTI0 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI0WEN   0x00000001

//
//! EXTI1 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI1WEN   0x00000002

//
//! EXTI2 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI2WEN   0x00000004

//
//! EXTI3 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI3WEN   0x00000008

//
//! EXTI4 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI4WEN   0x00000010

//
//! EXTI5 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI5WEN   0x00000020

//
//! EXTI6 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI6WEN   0x00000040

//
//! EXTI7 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI7WEN   0x00000080

//
//! EXTI8 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI8WEN   0x00000100

//
//! EXTI9 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI9WEN   0x00000200

//
//! EXTI10 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI10WEN  0x00000400

//
//! EXTI11 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI11WEN  0x00000800

//
//! EXTI12 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI12WEN  0x00001000

//
//! EXTI13 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI13WEN  0x00002000

//
//! EXTI14 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI14WEN  0x00004000

//
//! EXTI15 Wakeup Enable
//
#define EXTI_WAKUPCR_EXTI15WEN  0x00008000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_WAKUPPOLR EXTI line interrupt wakeup polarity 
//!  Register(EXTI_WAKUPPOLR)
//! \brief Defines for the bit fields in the EXTI_WAKUPPOLR register.
//! @{
//
//*****************************************************************************

//
//! EXTI0 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI0POL 0x00000001

//
//! EXTI1 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI1POL 0x00000002

//
//! EXTI2 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI2POL 0x00000004

//
//! EXTI3 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI3POL 0x00000008

//
//! EXTI4 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI4POL 0x00000010

//
//! EXTI5 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI5POL 0x00000020

//
//! EXTI6 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI6POL 0x00000040

//
//! EXTI7 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI7POL 0x00000080

//
//! EXTI8 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI8POL 0x00000100

//
//! EXTI9 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI9POL 0x00000200

//
//! EXTI10 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI10POL                                              \
                                0x00000400

//
//! EXTI11 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI11POL                                              \
                                0x00000800

//
//! EXTI12 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI12POL                                              \
                                0x00001000

//
//! EXTI13 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI13POL                                              \
                                0x00002000

//
//! EXTI14 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI14POL                                              \
                                0x00004000

//
//! EXTI15 Wakeup Polarity
//
#define EXTI_WAKUPPOLR_EXTI15POL                                              \
                                0x00008000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_GPIO_Register_EXTI_WAKUPFLG EXTI Interrupt Wakeup Flag 
//!  Register(EXTI_WAKUPFLG)
//! \brief Defines for the bit fields in the EXTI_WAKUPFLG register.
//! @{
//
//*****************************************************************************

//
//! EXTI0 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI0WFL  0x00000001

//
//! EXTI1 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI1WFL  0x00000002

//
//! EXTI2 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI2WFL  0x00000004

//
//! EXTI3 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI3WFL  0x00000008

//
//! EXTI4 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI4WFL  0x00000010

//
//! EXTI5 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI5WFL  0x00000020

//
//! EXTI6 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI6WFL  0x00000040

//
//! EXTI7 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI7WFL  0x00000080

//
//! EXTI8 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI8WFL  0x00000100

//
//! EXTI9 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI9WFL  0x00000200

//
//! EXTI10 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI10WFL 0x00000400

//
//! EXTI11 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI11WFL  0x00000800

//
//! EXTI12 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI12WFL  0x00001000

//
//! EXTI13 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI13WFL  0x00002000

//
//! EXTI14 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI14WFL  0x00004000

//
//! EXTI15 Wakeup Polarity
//
#define EXTI_WAKUPFLG_EXTI15WFL  0x00008000

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
#endif // __XHW_GPIO_H__
