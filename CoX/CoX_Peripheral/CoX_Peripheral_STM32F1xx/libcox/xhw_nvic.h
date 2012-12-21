//*****************************************************************************
//
//! \file xhw_nvic.h
//! \brief Macros used when accessing the NVIC hardware.For M0
//! \version V2.2.1.0
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


#ifndef __XHW_NVIC_H__
#define __XHW_NVIC_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xCORE
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup CORE_NVIC_Register  NVIC Register
//! \brief Here are the detailed info of NVIC registers. 
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
//! \addtogroup STM32F1xx_NVIC_Register_Address NVIC Address Register(NVIC_Address)
//! \brief Defines for the bit fields in the NVIC_Register_Address register
//! @{
//
//*****************************************************************************
//
//! Interrupt Controller Type Reg
//
#define NVIC_INT_TYPE           0xE000E004

//
//! Auxiliary Control
//
#define NVIC_ACTLR              0xE000E008

//
//! SysTick Control and Status Register
//
#define NVIC_ST_CTRL            0xE000E010

//
//! SysTick Reload Value Register
//
#define NVIC_ST_RELOAD          0xE000E014

//
//! SysTick Current Value Register
//
#define NVIC_ST_CURRENT         0xE000E018

//
//! SysTick Calibration Value Reg
//
#define NVIC_ST_CAL             0xE000E01C

//
//! Interrupt 0-31 Set Enable
//
#define NVIC_EN0                0xE000E100
#define NVIC_EN1                0xE000E104
#define NVIC_EN2                0xE000E108

//
//! Interrupt 0-31 Clear Enable
//
#define NVIC_DIS0               0xE000E180
#define NVIC_DIS1               0xE000E184
#define NVIC_DIS2               0xE000E188

//
//! Interrupt 0-31 Set Pending
//
#define NVIC_PEND0              0xE000E200
#define NVIC_PEND1              0xE000E204
#define NVIC_PEND2              0xE000E208

//
//! Interrupt 0-31 Clear Pending
//
#define NVIC_UNPEND0            0xE000E280
#define NVIC_UNPEND1            0xE000E284
#define NVIC_UNPEND2            0xE000E288

//
//! Interrupt 0-3 Priority
//
#define NVIC_PRI0               0xE000E400

//
//! Interrupt 4-7 Priority
//
#define NVIC_PRI1               0xE000E404

//
//! Interrupt 8-11 Priority
//
#define NVIC_PRI2               0xE000E408

//
//! Interrupt 12-15 Priority
//
#define NVIC_PRI3               0xE000E40C

//
//! Interrupt 16-19 Priority
//
#define NVIC_PRI4               0xE000E410

//
//! Interrupt 20-23 Priority
//
#define NVIC_PRI5               0xE000E414

//
//! Interrupt 24-27 Priority
//
#define NVIC_PRI6               0xE000E418

//
//! Interrupt 28-31 Priority
//
#define NVIC_PRI7               0xE000E41C

//
//! Interrupt 32-35 Priority
//
#define NVIC_PRI8               0xE000E420

//
//! Interrupt 36-39 Priority
//
#define NVIC_PRI9               0xE000E424

//
//! Interrupt 40-43 Priority
//
#define NVIC_PRI10              0xE000E428

//
//! Interrupt 44-47 Priority
//
#define NVIC_PRI11              0xE000E42C

//
//! Interrupt 48-51 Priority
//
#define NVIC_PRI12              0xE000E430

//
//! Interrupt 52-55 Priority
//
#define NVIC_PRI13              0xE000E434

//
//! Interrupt 56-59 Priority
//
#define NVIC_PRI14              0xE000E438

//
//! Interrupt 60-63 Priority
//
#define NVIC_PRI15              0xE000E43C

//
//! Interrupt 64-68 Priority
//
#define NVIC_PRI16              0xE000E440
#define NVIC_PRI17              0xE000E444
#define NVIC_PRI18              0xE000E448
#define NVIC_PRI19              0xE000E44C
#define NVIC_PRI20              0xE000E450

//
//! CPU ID Base
//
#define NVIC_CPUID              0xE000ED00

//
//! Interrupt Control and State
//
#define NVIC_INT_CTRL           0xE000ED04

//
//! Application Interrupt and Reset Control
//
#define NVIC_APINT              0xE000ED0C  
//
//! System Control
//
#define NVIC_SYS_CTRL           0xE000ED10  

//
//! Configuration and Control
//
#define NVIC_CFG_CTRL           0xE000ED14

//
//! System Handler Priority 1
//
#define NVIC_SYS_PRI1           0xE000ED18

//
//! System Handler Priority 2
//
#define NVIC_SYS_PRI2           0xE000ED1C

//
//! System Handler Priority 3
//
#define NVIC_SYS_PRI3           0xE000ED20

//
//! System Handler Control and State
//
#define NVIC_SYS_HND_CTRL       0xE000ED24

//
//! Debug Status Register
//
#define NVIC_DEBUG_STAT         0xE000ED30

//
//! Debug Control and Status Reg
//
#define NVIC_DBG_CTRL           0xE000EDF0

//
//! Debug Core Reg. Transfer Select
//
#define NVIC_DBG_XFER           0xE000EDF4

//
//! Debug Core Register Data
//
#define NVIC_DBG_DATA           0xE000EDF8  

//
//! Debug Reset Interrupt Control
//
#define NVIC_DBG_INT            0xE000EDFC

//
//! Software Trigger Interrupt
//
#define NVIC_SW_TRIG            0xE000EF00

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_INT_TYPE NVIC Interrupt Type Register(NVIC_INT_TYPE)
//! \brief Defines for the bit fields in the NVIC_INT_TYPE register.
//! @{
//
//*****************************************************************************

//
//! Number of interrupt lines (x32)
//
#define NVIC_INT_TYPE_LINES_M   0x0000001F
#define NVIC_INT_TYPE_LINES_S   0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_ACTLR NVIC ACTLR Register(NVIC_ACTLR)
//! \brief Defines for the bit fields in the NVIC_ACTLR register.
//! @{
//
//*****************************************************************************

//
//! Disable IT Folding
//
#define NVIC_ACTLR_DISFOLD      0x00000004

//
//! Disable Write Buffer
//
#define NVIC_ACTLR_DISWBUF      0x00000002

//
//! Disable Interrupts of Multiple Cycle Instructions
//
#define NVIC_ACTLR_DISMCYC      0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_ST_CTRL NVIC Status Control Register(NVIC_ST_CTRL)
//! \brief Defines for the bit fields in the NVIC_ST_CTRL register.
//! @{
//
//*****************************************************************************

//
//! Count Flag
//
#define NVIC_ST_CTRL_COUNT      0x00010000

//
//! Clock Source
//
#define NVIC_ST_CTRL_CLK_SRC    0x00000004

//
//! Interrupt Enable
//
#define NVIC_ST_CTRL_INTEN      0x00000002

//
//! Enable
//
#define NVIC_ST_CTRL_ENABLE     0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_ST_RELOAD NVIC Status Reload Register(NVIC_ST_RELOAD)
//! \brief Defines for the bit fields in the NVIC_ST_RELOAD register.
//! @{
//
//*****************************************************************************

//
//! Reload Value
//
#define NVIC_ST_RELOAD_M        0x00FFFFFF
#define NVIC_ST_RELOAD_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_ST_CURRENT NVIC Status Current Register(NVIC_ST_CURRENT)
//! \brief Defines for the bit fields in the NVIC_ST_CURRENT register.
//! @{
//
//*****************************************************************************

//
//! Current Value
//
#define NVIC_ST_CURRENT_M       0x00FFFFFF
#define NVIC_ST_CURRENT_S       0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_ST_CAL NVIC Status Cal Register(NVIC_ST_CAL)
//! \brief Defines for the bit fields in the NVIC_ST_CAL register.
//! @{
//
//*****************************************************************************

//
//! No reference clock
//
#define NVIC_ST_CAL_NOREF       0x80000000

//
//! Clock skew
//
#define NVIC_ST_CAL_SKEW        0x40000000

//
//! 1ms reference value
//
#define NVIC_ST_CAL_ONEMS_M     0x00FFFFFF
#define NVIC_ST_CAL_ONEMS_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_EN0 NVIC Ebanle0 Register(NVIC_EN0)
//! \brief Defines for the bit fields in the NVIC_EN0 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Enable
//
#define NVIC_EN0_INT_M          0xFFFFFFFF

//
//! Interrupt 0 enable
//
#define NVIC_EN0_INT0           0x00000001

//
//! Interrupt 1 enable
//
#define NVIC_EN0_INT1           0x00000002

//
//! Interrupt 2 enable
//
#define NVIC_EN0_INT2           0x00000004

//
//! Interrupt 3 enable
//
#define NVIC_EN0_INT3           0x00000008

//
//! Interrupt 4 enable
//
#define NVIC_EN0_INT4           0x00000010

//
//! Interrupt 5 enable
//
#define NVIC_EN0_INT5           0x00000020

//
//! Interrupt 6 enable
//
#define NVIC_EN0_INT6           0x00000040

//
//! Interrupt 7 enable
//
#define NVIC_EN0_INT7           0x00000080

//
//! Interrupt 8 enable
//
#define NVIC_EN0_INT8           0x00000100

//
//! Interrupt 9 enable
//
#define NVIC_EN0_INT9           0x00000200

//
//! Interrupt 10 enable
//
#define NVIC_EN0_INT10          0x00000400

//
//! Interrupt 11 enable
//
#define NVIC_EN0_INT11          0x00000800

//
//! Interrupt 12 enable
//
#define NVIC_EN0_INT12          0x00001000

//
//! Interrupt 13 enable
//
#define NVIC_EN0_INT13          0x00002000

//
//! Interrupt 14 enable
//
#define NVIC_EN0_INT14          0x00004000

//
//! Interrupt 15 enable
//
#define NVIC_EN0_INT15          0x00008000

//
//! Interrupt 16 enable
//
#define NVIC_EN0_INT16          0x00010000

//
//! Interrupt 17 enable
//
#define NVIC_EN0_INT17          0x00020000

//
//! Interrupt 18 enable
//
#define NVIC_EN0_INT18          0x00040000

//
//! Interrupt 19 enable
//
#define NVIC_EN0_INT19          0x00080000

//
//! Interrupt 20 enable
//
#define NVIC_EN0_INT20          0x00100000

//
//! Interrupt 21 enable
//
#define NVIC_EN0_INT21          0x00200000

//
//! Interrupt 22 enable
//
#define NVIC_EN0_INT22          0x00400000

//
//! Interrupt 23 enable
//
#define NVIC_EN0_INT23          0x00800000

//
//! Interrupt 24 enable
//
#define NVIC_EN0_INT24          0x01000000

//
//! Interrupt 25 enable
//
#define NVIC_EN0_INT25          0x02000000
//
//! Interrupt 26 enable
//
#define NVIC_EN0_INT26          0x04000000

//
//! Interrupt 27 enable
//
#define NVIC_EN0_INT27          0x08000000

//
//! Interrupt 28 enable
//
#define NVIC_EN0_INT28          0x10000000
//
//! Interrupt 29 enable
//
#define NVIC_EN0_INT29          0x20000000

//
//! Interrupt 30 enable
//
#define NVIC_EN0_INT30          0x40000000

//
//! Interrupt 31 enable
//
#define NVIC_EN0_INT31          0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_DIS0 NVIC Disable0 Register(NVIC_DIS0)
//! \brief Defines for the bit fields in the NVIC_DIS0 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Disable
//
#define NVIC_DIS0_INT_M         0xFFFFFFFF

//
//! Interrupt 0 disable
//
#define NVIC_DIS0_INT0          0x00000001

//
//! Interrupt 1 disable
//
#define NVIC_DIS0_INT1          0x00000002

//
//! Interrupt 2 disable
//
#define NVIC_DIS0_INT2          0x00000004

//
//! Interrupt 3 disable
//
#define NVIC_DIS0_INT3          0x00000008

//
//! Interrupt 4 disable
//
#define NVIC_DIS0_INT4          0x00000010

//
//! Interrupt 5 disable
//
#define NVIC_DIS0_INT5          0x00000020

//
//! Interrupt 6 disable
//
#define NVIC_DIS0_INT6          0x00000040

//
//! Interrupt 7 disable
//
#define NVIC_DIS0_INT7          0x00000080

//
//! Interrupt 8 disable
//
#define NVIC_DIS0_INT8          0x00000100

//
//! Interrupt 9 disable
//
#define NVIC_DIS0_INT9          0x00000200

//
//! Interrupt 10 disable
//
#define NVIC_DIS0_INT10         0x00000400

//
//! Interrupt 11 disable
//
#define NVIC_DIS0_INT11         0x00000800

//
//! Interrupt 12 disable
//
#define NVIC_DIS0_INT12         0x00001000

//
//! Interrupt 13 disable
//
#define NVIC_DIS0_INT13         0x00002000

//
//! Interrupt 14 disable
//
#define NVIC_DIS0_INT14         0x00004000

//
//! Interrupt 15 disable
//
#define NVIC_DIS0_INT15         0x00008000  

//
//! Interrupt 16 disable
//
#define NVIC_DIS0_INT16         0x00010000  

//
//! Interrupt 17 disable
//
#define NVIC_DIS0_INT17         0x00020000  

//
//! Interrupt 18 disable
//
#define NVIC_DIS0_INT18         0x00040000  

//
//! Interrupt 19 disable
//
#define NVIC_DIS0_INT19         0x00080000 

//
//! Interrupt 20 disable
//
#define NVIC_DIS0_INT20         0x00100000  

//
//! Interrupt 21 disable
//
#define NVIC_DIS0_INT21         0x00200000  

//
//! Interrupt 22 disable
//
#define NVIC_DIS0_INT22         0x00400000  

//
//! Interrupt 23 disable
//
#define NVIC_DIS0_INT23         0x00800000  

//
//! Interrupt 24 disable
//
#define NVIC_DIS0_INT24         0x01000000  

//
//! Interrupt 25 disable
//
#define NVIC_DIS0_INT25         0x02000000  

//
//! Interrupt 26 disable
//
#define NVIC_DIS0_INT26         0x04000000  

//
//! Interrupt 27 disable
//
#define NVIC_DIS0_INT27         0x08000000  

//
//! Interrupt 28 disable
//
#define NVIC_DIS0_INT28         0x10000000

//
//! Interrupt 29 disable
//
#define NVIC_DIS0_INT29         0x20000000

//
// Interrupt 30 disable
//
#define NVIC_DIS0_INT30         0x40000000  

//
//! Interrupt 31 disable
//
#define NVIC_DIS0_INT31         0x80000000 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_PEND0 NVIC PEND 0 Register(NVIC_PEND0)
//! \brief Defines for the bit fields in the NVIC_PEND0 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Set Pending
//
#define NVIC_PEND0_INT_M        0xFFFFFFFF

//
//! Interrupt 0 pend
//
#define NVIC_PEND0_INT0         0x00000001

//
//! Interrupt 1 pend
//
#define NVIC_PEND0_INT1         0x00000002

//
//! Interrupt 2 pend
//
#define NVIC_PEND0_INT2         0x00000004  

//
//! Interrupt 3 pend
//
#define NVIC_PEND0_INT3         0x00000008  

//
//! Interrupt 4 pend
//
#define NVIC_PEND0_INT4         0x00000010  

//
//! Interrupt 5 pend
//
#define NVIC_PEND0_INT5         0x00000020

//
//! Interrupt 6 pend
//
#define NVIC_PEND0_INT6         0x00000040

//
//! Interrupt 7 pend
//
#define NVIC_PEND0_INT7         0x00000080

//
//! Interrupt 8 pend
//
#define NVIC_PEND0_INT8         0x00000100  

//
//! Interrupt 9 pend
//
#define NVIC_PEND0_INT9         0x00000200

//
//! Interrupt 10 pend
//
#define NVIC_PEND0_INT10        0x00000400

//
//! Interrupt 11 pend
//
#define NVIC_PEND0_INT11        0x00000800

//
//! Interrupt 12 pend
//
#define NVIC_PEND0_INT12        0x00001000

//
//! Interrupt 13 pend
//
#define NVIC_PEND0_INT13        0x00002000

//
//! Interrupt 14 pend
//
#define NVIC_PEND0_INT14        0x00004000  

//
//! Interrupt 15 pend
//
#define NVIC_PEND0_INT15        0x00008000 

//
//! Interrupt 16 pend
//
#define NVIC_PEND0_INT16        0x00010000  

//
//! Interrupt 17 pend
//
#define NVIC_PEND0_INT17        0x00020000

//
//! Interrupt 18 pend
//
#define NVIC_PEND0_INT18        0x00040000  

//
//! Interrupt 19 pend
//
#define NVIC_PEND0_INT19        0x00080000  

//
//! Interrupt 20 pend
//
#define NVIC_PEND0_INT20        0x00100000  

//
//! Interrupt 21 pend
//
#define NVIC_PEND0_INT21        0x00200000

//
//! Interrupt 22 pend
//
#define NVIC_PEND0_INT22        0x00400000 

//
//! Interrupt 23 pend
//
#define NVIC_PEND0_INT23        0x00800000 

//
//! Interrupt 24 pend
//
#define NVIC_PEND0_INT24        0x01000000  

//
//! Interrupt 25 pend
//
#define NVIC_PEND0_INT25        0x02000000  

//
//! Interrupt 26 pend
//
#define NVIC_PEND0_INT26        0x04000000

//
//! Interrupt 27 pend
//
#define NVIC_PEND0_INT27        0x08000000

//
//! Interrupt 28 pend
//
#define NVIC_PEND0_INT28        0x10000000

//
//! Interrupt 29 pend
//
#define NVIC_PEND0_INT29        0x20000000

//
//! Interrupt 30 pend
//
#define NVIC_PEND0_INT30        0x40000000  

//
//! Interrupt 31 pend
//
#define NVIC_PEND0_INT31        0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_UNPEND0 NVIC UNPEND 0 Register(NVIC_UNPEND0)
//! \brief Defines for the bit fields in the NVIC_UNPEND0 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Clear Pending
//
#define NVIC_UNPEND0_INT_M      0xFFFFFFFF  

//
//! Interrupt 0 unpend
//
#define NVIC_UNPEND0_INT0       0x00000001  

//
//! Interrupt 1 unpend
//
#define NVIC_UNPEND0_INT1       0x00000002 

//
//! Interrupt 2 unpend
//
#define NVIC_UNPEND0_INT2       0x00000004  

//
//! Interrupt 3 unpend
//
#define NVIC_UNPEND0_INT3       0x00000008  

//
//! Interrupt 4 unpend
//
#define NVIC_UNPEND0_INT4       0x00000010  

//
//! Interrupt 5 unpend
//
#define NVIC_UNPEND0_INT5       0x00000020  

//
//! Interrupt 6 unpend
//
#define NVIC_UNPEND0_INT6       0x00000040  

//
//! Interrupt 7 unpend
//
#define NVIC_UNPEND0_INT7       0x00000080  

//
//! Interrupt 8 unpend
//
#define NVIC_UNPEND0_INT8       0x00000100  
//
//! Interrupt 9 unpend
//
#define NVIC_UNPEND0_INT9       0x00000200  

//
//! Interrupt 10 unpend
//
#define NVIC_UNPEND0_INT10      0x00000400  

//
//! Interrupt 11 unpend
//
#define NVIC_UNPEND0_INT11      0x00000800  

//
//! Interrupt 12 unpend
//
#define NVIC_UNPEND0_INT12      0x00001000  

//
//! Interrupt 13 unpend
//
#define NVIC_UNPEND0_INT13      0x00002000  

//
//! Interrupt 14 unpend
//
#define NVIC_UNPEND0_INT14      0x00004000  

//
//! Interrupt 15 unpend
//
#define NVIC_UNPEND0_INT15      0x00008000  

//
//! Interrupt 16 unpend
//
#define NVIC_UNPEND0_INT16      0x00010000  

//
//! Interrupt 17 unpend
//
#define NVIC_UNPEND0_INT17      0x00020000  

//
//! Interrupt 18 unpend
//
#define NVIC_UNPEND0_INT18      0x00040000  

//
//! Interrupt 19 unpend
//
#define NVIC_UNPEND0_INT19      0x00080000  

//
//! Interrupt 20 unpend
//
#define NVIC_UNPEND0_INT20      0x00100000  

//
//! Interrupt 21 unpend
//
#define NVIC_UNPEND0_INT21      0x00200000  

//
//! Interrupt 22 unpend
//
#define NVIC_UNPEND0_INT22      0x00400000  

//
//! Interrupt 23 unpend
//
#define NVIC_UNPEND0_INT23      0x00800000  

//
//! Interrupt 24 unpend
//
#define NVIC_UNPEND0_INT24      0x01000000  

//
//! Interrupt 25 unpend
//
#define NVIC_UNPEND0_INT25      0x02000000  

//
//! Interrupt 26 unpend
//
#define NVIC_UNPEND0_INT26      0x04000000  

//
//! Interrupt 27 unpend
//
#define NVIC_UNPEND0_INT27      0x08000000  

//
//! Interrupt 28 unpend
//
#define NVIC_UNPEND0_INT28      0x10000000  

//
//! Interrupt 29 unpend
//
#define NVIC_UNPEND0_INT29      0x20000000  

//
//! Interrupt 30 unpend
//
#define NVIC_UNPEND0_INT30      0x40000000  

//
//! Interrupt 31 unpend
//
#define NVIC_UNPEND0_INT31      0x80000000 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_PRI0 NVIC Priority 0 Register(NVIC_PRI0)
//! \brief Defines for the bit fields in the NVIC_PRI0 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 3 Priority Mask
//
#define NVIC_PRI0_INT3_M        0xC0000000  

//
//! Interrupt 2 Priority Mask
//
#define NVIC_PRI0_INT2_M        0x00C00000  

//
//! Interrupt 1 Priority Mask
//
#define NVIC_PRI0_INT1_M        0x0000C000  

//
//! Interrupt 0 Priority Mask
//
#define NVIC_PRI0_INT0_M        0x000000C0  
#define NVIC_PRI0_INT3_S        30
#define NVIC_PRI0_INT2_S        22
#define NVIC_PRI0_INT1_S        14
#define NVIC_PRI0_INT0_S        6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_PRI1 NVIC Priority 1 Register(NVIC_PRI1)
//! \brief Defines for the bit fields in the NVIC_PRI1 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 7 Priority Mask
//
#define NVIC_PRI1_INT7_M        0xC0000000  

//
//! Interrupt 6 Priority Mask
//
#define NVIC_PRI1_INT6_M        0x00C00000  

//
//! Interrupt 5 Priority Mask
//
#define NVIC_PRI1_INT5_M        0x0000C000 

//
//! Interrupt 4 Priority Mask
//
#define NVIC_PRI1_INT4_M        0x000000C0  
#define NVIC_PRI1_INT7_S        30
#define NVIC_PRI1_INT6_S        22
#define NVIC_PRI1_INT5_S        14
#define NVIC_PRI1_INT4_S        6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_PRI2 NVIC Priority 2 Register(NVIC_PRI2)
//! \brief Defines for the bit fields in the NVIC_PRI2 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 11 Priority Mask
//
#define NVIC_PRI2_INT11_M       0xC0000000  

//
//! Interrupt 10 Priority Mask
//
#define NVIC_PRI2_INT10_M       0x00C00000  

//
//! Interrupt 9 Priority Mask
//
#define NVIC_PRI2_INT9_M        0x0000C000  

//
//! Interrupt 8 Priority Mask
//
#define NVIC_PRI2_INT8_M        0x000000C0  
#define NVIC_PRI2_INT11_S       30
#define NVIC_PRI2_INT10_S       22
#define NVIC_PRI2_INT9_S        14
#define NVIC_PRI2_INT8_S        6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_PRI3 NVIC Priority 3 Register(NVIC_PRI3)
//! \brief Defines for the bit fields in the NVIC_PRI3 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 15 Priority Mask
//
#define NVIC_PRI3_INT15_M       0xC0000000  

//
//! Interrupt 14 Priority Mask
//
#define NVIC_PRI3_INT14_M       0x00C00000  

//
//! Interrupt 13 Priority Mask
//
#define NVIC_PRI3_INT13_M       0x0000C000  

//
//! Interrupt 12 Priority Mask
//
#define NVIC_PRI3_INT12_M       0x000000C0  
#define NVIC_PRI3_INT15_S       30
#define NVIC_PRI3_INT14_S       22
#define NVIC_PRI3_INT13_S       14
#define NVIC_PRI3_INT12_S       6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_PRI4 NVIC Priority 4 Register(NVIC_PRI4)
//! \brief Defines for the bit fields in the NVIC_PRI4 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 19 Priority Mask
//
#define NVIC_PRI4_INT19_M       0xC0000000  

//
//! Interrupt 18 Priority Mask
//
#define NVIC_PRI4_INT18_M       0x00C00000  

//
//! Interrupt 17 Priority Mask
//
#define NVIC_PRI4_INT17_M       0x0000C000  

//
//! Interrupt 16 Priority Mask
//
#define NVIC_PRI4_INT16_M       0x000000C0  
#define NVIC_PRI4_INT19_S       30
#define NVIC_PRI4_INT18_S       22
#define NVIC_PRI4_INT17_S       14
#define NVIC_PRI4_INT16_S       6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_PRI5 NVIC Priority 5 Register(NVIC_PRI5)
//! \brief Defines for the bit fields in the NVIC_PRI5 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 23 Priority Mask
//
#define NVIC_PRI5_INT23_M       0xC0000000  

//
//! Interrupt 22 Priority Mask
//
#define NVIC_PRI5_INT22_M       0x00C00000  

//
//! Interrupt 21 Priority Mask
//
#define NVIC_PRI5_INT21_M       0x0000C000  

//
//! Interrupt 20 Priority Mask
//
#define NVIC_PRI5_INT20_M       0x000000C0  
#define NVIC_PRI5_INT23_S       30
#define NVIC_PRI5_INT22_S       22
#define NVIC_PRI5_INT21_S       14
#define NVIC_PRI5_INT20_S       6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_PRI6 NVIC Priority 6 Register(NVIC_PRI6)
//! \brief Defines for the bit fields in the NVIC_PRI6 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 27 Priority Mask
//
#define NVIC_PRI6_INT27_M       0xC0000000  

//
//! Interrupt 26 Priority Mask
//
#define NVIC_PRI6_INT26_M       0x00C00000  

//
//! Interrupt 25 Priority Mask
//
#define NVIC_PRI6_INT25_M       0x0000C000 

//
//! Interrupt 24 Priority Mask
//
#define NVIC_PRI6_INT24_M       0x000000C0  
#define NVIC_PRI6_INT27_S       30
#define NVIC_PRI6_INT26_S       22
#define NVIC_PRI6_INT25_S       14
#define NVIC_PRI6_INT24_S       6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_PRI7 NVIC Priority 7 Register(NVIC_PRI7)
//! \brief Defines for the bit fields in the NVIC_PRI7 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 31 Priority Mask
//
#define NVIC_PRI7_INT31_M       0xC0000000

//
//! Interrupt 30 Priority Mask
//
#define NVIC_PRI7_INT30_M       0x00C00000

//
//! Interrupt 29 Priority Mask
//
#define NVIC_PRI7_INT29_M       0x0000C000

//
//! Interrupt 28 Priority Mask
//
#define NVIC_PRI7_INT28_M       0x000000C0
#define NVIC_PRI7_INT31_S       30
#define NVIC_PRI7_INT30_S       22
#define NVIC_PRI7_INT29_S       14
#define NVIC_PRI7_INT28_S       6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_CPUID  NVIC CPUID Register(NVIC_CPUID)
//! \brief Defines for the bit fields in the NVIC_CPUID register.
//! @{
//
//*****************************************************************************

//
//! Implementer Code
//
#define NVIC_CPUID_IMP_M        0xFF000000

//
//! ARM
//
#define NVIC_CPUID_IMP_ARM      0x41000000  

//
//! Variant Number
//
#define NVIC_CPUID_VAR_M        0x00F00000  

//
//! Constant
//
#define NVIC_CPUID_CON_M        0x000F0000  

//
//! Part Number
//
#define NVIC_CPUID_PARTNO_M     0x0000FFF0  

//
//! Cortex-M3 processor
//
#define NVIC_CPUID_PARTNO_CM3   0x0000C230  

//
//! Revision Number
//
#define NVIC_CPUID_REV_M        0x0000000F  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_INT_CTRL NVIC Interrupt Control Register(NVIC_INT_CTRL)
//! \brief Defines for the bit fields in the NVIC_INT_CTRL register.
//! @{
//
//*****************************************************************************

//
//! NMI Set Pending
//
#define NVIC_INT_CTRL_NMI_SET   0x80000000  

//
//! PendSV Set Pending
//
#define NVIC_INT_CTRL_PEND_SV   0x10000000  

//
//! PendSV Clear Pending
//
#define NVIC_INT_CTRL_UNPEND_SV 0x08000000  

//
//! SysTick Set Pending
//
#define NVIC_INT_CTRL_PENDSTSET 0x04000000  

//
//! SysTick Clear Pending
//
#define NVIC_INT_CTRL_PENDSTCLR 0x02000000  

//
//! Debug Interrupt Handling
//
#define NVIC_INT_CTRL_ISR_PRE   0x00800000  

//
//! Interrupt Pending
//
#define NVIC_INT_CTRL_ISR_PEND  0x00400000  

//
//! Interrupt Pending Vector Number
//
#define NVIC_INT_CTRL_VEC_PEN_M 0x0007F000  

//
//! NMI
//
#define NVIC_INT_CTRL_VEC_PEN_NMI \
                                0x00002000 

//
//! Hard fault
//
#define NVIC_INT_CTRL_VEC_PEN_HARD \
                                0x00003000

//
//! Memory management fault
//
#define NVIC_INT_CTRL_VEC_PEN_MEM \
                                0x00004000  

//
//! Bus fault
//
#define NVIC_INT_CTRL_VEC_PEN_BUS \
                                0x00005000  

//
//! Usage fault
//
#define NVIC_INT_CTRL_VEC_PEN_USG \
                                0x00006000  

//
//! SVCall
//
#define NVIC_INT_CTRL_VEC_PEN_SVC \
                                0x0000B000  

//
//! PendSV
//
#define NVIC_INT_CTRL_VEC_PEN_PNDSV \
                                0x0000C000  

//
//! SysTick
//
#define NVIC_INT_CTRL_VEC_PEN_TICK \
                                0x0000F000  

//
//! Return to Base
//
#define NVIC_INT_CTRL_RET_BASE  0x00000800  

//
//! Interrupt Pending Vector Number
//
#define NVIC_INT_CTRL_VEC_ACT_M 0x0000007F  
#define NVIC_INT_CTRL_VEC_PEN_S 12
#define NVIC_INT_CTRL_VEC_ACT_S 0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_APINT NVIC APINT Register(NVIC_APINT)
//! \brief Defines for the bit fields in the NVIC_APINT register.
//! @{
//
//*****************************************************************************

//
//! Register Key
//
#define NVIC_APINT_VECTKEY_M    0xFFFF0000  

//
//! Vector key
//
#define NVIC_APINT_VECTKEY      0x05FA0000  

//
//! Data Endianess
//
#define NVIC_APINT_ENDIANESS    0x00008000  

//
//! Interrupt Priority Grouping
//
#define NVIC_APINT_PRIGROUP_M   0x00000700  

//
//! Priority group 7.1 split
//
#define NVIC_APINT_PRIGROUP_7_1 0x00000000  

//
//! Priority group 6.2 split
//
#define NVIC_APINT_PRIGROUP_6_2 0x00000100

//
//! Priority group 5.3 split
//
#define NVIC_APINT_PRIGROUP_5_3 0x00000200 

//
//! Priority group 4.4 split
//
#define NVIC_APINT_PRIGROUP_4_4 0x00000300  

//
//! Priority group 3.5 split
//
#define NVIC_APINT_PRIGROUP_3_5 0x00000400  

//
//! Priority group 2.6 split
//
#define NVIC_APINT_PRIGROUP_2_6 0x00000500  

//
//! Priority group 1.7 split
//
#define NVIC_APINT_PRIGROUP_1_7 0x00000600  

//
//! Priority group 0.8 split
//
#define NVIC_APINT_PRIGROUP_0_8 0x00000700  

//
//! System Reset Request
//
#define NVIC_APINT_SYSRESETREQ  0x00000004  

//
//! Clear Active NMI / Fault
//
#define NVIC_APINT_VECT_CLR_ACT 0x00000002  

//
//! System Reset
//
#define NVIC_APINT_VECT_RESET   0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_SYS_CTRL NVIC System Control Register(NVIC_SYS_CTRL)
//! \brief Defines for the bit fields in the NVIC_SYS_CTRL register.
//! @{
//
//*****************************************************************************

//
//! Wake Up on Pending
//
#define NVIC_SYS_CTRL_SEVONPEND 0x00000010 

//
//! Deep Sleep Enable
//
#define NVIC_SYS_CTRL_SLEEPDEEP 0x00000004  

//
//! Sleep on ISR Exit
//
#define NVIC_SYS_CTRL_SLEEPEXIT 0x00000002  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_CFG_CTRL NVIC Cfg Control Register(NVIC_CFG_CTRL)
//! \brief Defines for the bit fields in the NVIC_CFG_CTRL register.
//! @{
//
//*****************************************************************************

//
//! Stack Alignment on Exception Entry
//
#define NVIC_CFG_CTRL_STKALIGN  0x00000200  

//
//! Ignore Bus Fault in NMI and Fault
//
#define NVIC_CFG_CTRL_BFHFNMIGN 0x00000100  

//
//! Trap on Divide by 0
//
#define NVIC_CFG_CTRL_DIV0      0x00000010  

//
//! Trap on Unaligned Access
//
#define NVIC_CFG_CTRL_UNALIGNED 0x00000008  

//
//! Allow Main Interrupt Trigger
//
#define NVIC_CFG_CTRL_MAIN_PEND 0x00000002  

//
//! Thread State Control
//
#define NVIC_CFG_CTRL_BASE_THR  0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_SYS_PRI2 NVIC System Priority 2 Register(NVIC_SYS_PRI2)
//! \brief Defines for the bit fields in the NVIC_SYS_PRI2 register.
//! @{
//
//*****************************************************************************

//
//! SVCall Priority
//
#define NVIC_SYS_PRI2_SVC_M     0xC0000000
#define NVIC_SYS_PRI2_SVC_S     29

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_SYS_PRI3 NVIC System Priority 3 Register(NVIC_SYS_PRI3)
//! \brief Defines for the bit fields in the NVIC_SYS_PRI3 register.
//! @{
//
//*****************************************************************************

//
//! SysTick Exception Priority
//
#define NVIC_SYS_PRI3_TICK_M    0xC0000000  

//
//! PendSV Priority
//
#define NVIC_SYS_PRI3_PENDSV_M  0x00C00000  

//
//! Debug Priority
//
#define NVIC_SYS_PRI3_DEBUG_M   0x000000C0 
#define NVIC_SYS_PRI3_TICK_S    29
#define NVIC_SYS_PRI3_PENDSV_S  21
#define NVIC_SYS_PRI3_DEBUG_S   5

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_SYS_HND_CTRL NVIC HND Control Register(NVIC_SYS_HND_CTRL)
//! \brief Defines for the bit fields in the NVIC_SYS_HND_CTRL register.
//! @{
//
//*****************************************************************************

//
//! Usage Fault Enable
//
#define NVIC_SYS_HND_CTRL_USAGE 0x00040000  

//
//! Bus Fault Enable
//
#define NVIC_SYS_HND_CTRL_BUS   0x00020000

//
//! Memory Management Fault Enable
//
#define NVIC_SYS_HND_CTRL_MEM   0x00010000  

//
//! SVC Call Pending
//
#define NVIC_SYS_HND_CTRL_SVC   0x00008000  

//
//! Bus Fault Pending
//
#define NVIC_SYS_HND_CTRL_BUSP  0x00004000 

//
//! Memory Management Fault Pending
//
#define NVIC_SYS_HND_CTRL_MEMP  0x00002000  

//
//! Usage Fault Pending
//
#define NVIC_SYS_HND_CTRL_USAGEP \
                                0x00001000  

//
//! SysTick Exception Active
//
#define NVIC_SYS_HND_CTRL_TICK  0x00000800  

//
//! PendSV Exception Active
//
#define NVIC_SYS_HND_CTRL_PNDSV 0x00000400  

//
//! Debug Monitor Active
//
#define NVIC_SYS_HND_CTRL_MON   0x00000100  

//
//! SVC Call Active
//
#define NVIC_SYS_HND_CTRL_SVCA  0x00000080  

//
//! Usage Fault Active
//
#define NVIC_SYS_HND_CTRL_USGA  0x00000008

//
//! Bus Fault Active
//
#define NVIC_SYS_HND_CTRL_BUSA  0x00000002  

//
//! Memory Management Fault Active
//
#define NVIC_SYS_HND_CTRL_MEMA  0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_DEBUG_STAT NVIC Debug State Register(NVIC_DEBUG_STAT)
//! \brief Defines for the bit fields in the NVIC_DEBUG_STAT register.
//! @{
//
//*****************************************************************************

//
//! EDBGRQ asserted
//
#define NVIC_DEBUG_STAT_EXTRNL  0x00000010  

//
//! Vector catch
//
#define NVIC_DEBUG_STAT_VCATCH  0x00000008 

//
//! DWT match
//
#define NVIC_DEBUG_STAT_DWTTRAP 0x00000004  

//
//! Breakpoint instruction
//
#define NVIC_DEBUG_STAT_BKPT    0x00000002  

//
//! Halt request
//
#define NVIC_DEBUG_STAT_HALTED  0x00000001  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_DEBUG_CTRL NVIC Debug Control Register(NVIC_DBG_CTRL)
//! \brief Defines for the bit fields in the NVIC_DBG_CTRL register.
//! @{
//
//*****************************************************************************

//
//! Debug key mask
//
#define NVIC_DBG_CTRL_DBGKEY_M  0xFFFF0000  

//
//! Debug key
//
#define NVIC_DBG_CTRL_DBGKEY    0xA05F0000  

//
//! Core has reset since last read
//
#define NVIC_DBG_CTRL_S_RESET_ST \
                                0x02000000  

//
//! Core has executed insruction since last read
//
#define NVIC_DBG_CTRL_S_RETIRE_ST \
                                0x01000000  

//
//! Core is locked up
//
#define NVIC_DBG_CTRL_S_LOCKUP  0x00080000  

//
//! Core is sleeping
//
#define NVIC_DBG_CTRL_S_SLEEP   0x00040000  

//
//! Core status on halt
//
#define NVIC_DBG_CTRL_S_HALT    0x00020000  

//
//! Register read/write available
//
#define NVIC_DBG_CTRL_S_REGRDY  0x00010000  

//
//! Breaks a stalled load/store
//
#define NVIC_DBG_CTRL_C_SNAPSTALL \
                                0x00000020 

//
//! Mask interrupts when stepping
//
#define NVIC_DBG_CTRL_C_MASKINT 0x00000008  

//
//! Step the core
//
#define NVIC_DBG_CTRL_C_STEP    0x00000004  

//
//! Halt the core
//
#define NVIC_DBG_CTRL_C_HALT    0x00000002  

//
//! Enable debug
//
#define NVIC_DBG_CTRL_C_DEBUGEN 0x00000001 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_DBG_XFER NVIC XFER Register(NVIC_DBG_XFER)
//! \brief Defines for the bit fields in the NVIC_DBG_XFER register.
//! @{
//
//*****************************************************************************

//
//! Write or not read
//
#define NVIC_DBG_XFER_REG_WNR   0x00010000  

//
//! Register
//
#define NVIC_DBG_XFER_REG_SEL_M 0x0000001F  

//
//! Register R0
//
#define NVIC_DBG_XFER_REG_R0    0x00000000

//
//! Register R1
//
#define NVIC_DBG_XFER_REG_R1    0x00000001 

//
//! Register R2
//
#define NVIC_DBG_XFER_REG_R2    0x00000002  

//
//! Register R3
//
#define NVIC_DBG_XFER_REG_R3    0x00000003  

//
//! Register R4
//
#define NVIC_DBG_XFER_REG_R4    0x00000004  

//
//! Register R5
//
#define NVIC_DBG_XFER_REG_R5    0x00000005  

//
//! Register R6
//
#define NVIC_DBG_XFER_REG_R6    0x00000006  

//
//! Register R7
//
#define NVIC_DBG_XFER_REG_R7    0x00000007  

//
//! Register R8
//
#define NVIC_DBG_XFER_REG_R8    0x00000008  

//
//! Register R9
//
#define NVIC_DBG_XFER_REG_R9    0x00000009  

//
//! Register R10
//
#define NVIC_DBG_XFER_REG_R10   0x0000000A  

//
//! Register R11
//
#define NVIC_DBG_XFER_REG_R11   0x0000000B  

//
//! Register R12
//
#define NVIC_DBG_XFER_REG_R12   0x0000000C  

//
//! Register R13
//
#define NVIC_DBG_XFER_REG_R13   0x0000000D  

//
//! Register R14
//
#define NVIC_DBG_XFER_REG_R14   0x0000000E  

//
//! Register R15
//
#define NVIC_DBG_XFER_REG_R15   0x0000000F  

//
//! xPSR/Flags register
//
#define NVIC_DBG_XFER_REG_FLAGS 0x00000010  

//
//! Main SP
//
#define NVIC_DBG_XFER_REG_MSP   0x00000011  

//
//! Process SP
//
#define NVIC_DBG_XFER_REG_PSP   0x00000012  

//
//! Deep SP
//
#define NVIC_DBG_XFER_REG_DSP   0x00000013  

//
//! Control/Fault/BasePri/PriMask
//
#define NVIC_DBG_XFER_REG_CFBP  0x00000014  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_DBG_DATA NVIC Debug Data Register(NVIC_DBG_DATA)
//! \brief Defines for the bit fields in the NVIC_DBG_DATA register.
//! @{
//
//*****************************************************************************

//
//! Data temporary cache
//
#define NVIC_DBG_DATA_M         0xFFFFFFFF
#define NVIC_DBG_DATA_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_NVIC_Register_NVIC_DBG_INT NVIC Debug Intrrupt Register(NVIC_DBG_INT)
//! \brief Defines for the bit fields in the NVIC_DBG_INT register.
//! @{
//
//*****************************************************************************

//
//! Debug trap on hard fault
//
#define NVIC_DBG_INT_HARDERR    0x00000400  

//
//! Debug trap on interrupt errors
//
#define NVIC_DBG_INT_INTERR     0x00000200  

//
//! Debug trap on bus error
//
#define NVIC_DBG_INT_BUSERR     0x00000100  

//
//! Debug trap on usage fault state
//
#define NVIC_DBG_INT_STATERR    0x00000080  

//
//! Debug trap on usage fault check
//
#define NVIC_DBG_INT_CHKERR     0x00000040  

//
//! Debug trap on coprocessor error
//
#define NVIC_DBG_INT_NOCPERR    0x00000020  

//
//! Debug trap on mem manage fault
//
#define NVIC_DBG_INT_MMERR      0x00000010  

//
//! Core reset status
//
#define NVIC_DBG_INT_RESET      0x00000008  

//
//! Clear pending core reset
//
#define NVIC_DBG_INT_RSTPENDCLR 0x00000004  

//
//! Core reset is pending
//
#define NVIC_DBG_INT_RSTPENDING 0x00000002  

//
//! Reset vector catch
//
#define NVIC_DBG_INT_RSTVCATCH  0x00000001  

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

#endif // __XHW_NVIC_H__

