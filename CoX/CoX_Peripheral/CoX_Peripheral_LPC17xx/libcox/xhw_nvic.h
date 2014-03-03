//*****************************************************************************
//
//! \file      xhw_nvic.h
//! \brief     Macros used when accessing the Cortex-M NVIC.
//! \version   V2.2.1.0
//! \date      $CURRENTTIME$
//! \author    CooCox
//! \copyright
//!
//! Copyright (c)  2011, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
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
//! \addtogroup NVIC_Register_Address NVIC Address Register(NVIC_Address)
//! \brief Defines for the bit fields in the NVIC_Register_Address register
//! @{
//
//*****************************************************************************
//
//! Interrupt Controller Type Reg
//
#define NVIC_INT_TYPE                  ((unsigned long)0xE000E004)

//
//! Auxiliary Control
//
#define NVIC_ACTLR                     ((unsigned long)0xE000E008)

//
//! SysTick Control and Status Register
//
#define NVIC_ST_CTRL                   ((unsigned long)0xE000E010)

//
//! SysTick Reload Value Register
//
#define NVIC_ST_RELOAD                 ((unsigned long)0xE000E014)

//
//! SysTick Current Value Register
//
#define NVIC_ST_CURRENT                ((unsigned long)0xE000E018)

//
//! SysTick Calibration Value Reg
//
#define NVIC_ST_CAL                    ((unsigned long)0xE000E01C)


////////////////////////////// Int enable register ////////////////////////////
//! Int Enable Register 0   --> 31
#define NVIC_EN0                       ((unsigned long)0xE000E100)

//! Int Enable Register 32  --> 63
#define NVIC_EN1                       ((unsigned long)0xE000E104)

//! Int Enable Register 64  --> 95
#define NVIC_EN2                       ((unsigned long)0xE000E108)

//! Int Enable Register 96  --> 127
#define NVIC_EN3                       ((unsigned long)0xE000E10C)

//! Int Enable Register 128 --> 159
#define NVIC_EN4                       ((unsigned long)0xE000E110)

//! Int Enable Register 160 --> 191
#define NVIC_EN5                       ((unsigned long)0xE000E114)

//! Int Enable Register 192 --> 223
#define NVIC_EN6                       ((unsigned long)0xE000E118)

//! Int Enable Register 224 --> 239
#define NVIC_EN7                       ((unsigned long)0xE000E11C)

////////////////////////////// Int disable register ////////////////////////////
//! Int Disable Register 0   --> 31
#define NVIC_DIS0                      ((unsigned long)0xE000E180)

//! Int Disable Register 32  --> 63
#define NVIC_DIS1                      ((unsigned long)0xE000E184)

//! Int Disable Register 64  --> 95
#define NVIC_DIS2                      ((unsigned long)0xE000E188)

//! Int Disable Register 96  --> 127
#define NVIC_DIS3                      ((unsigned long)0xE000E18C)

//! Int Disable Register 128 --> 159
#define NVIC_DIS4                      ((unsigned long)0xE000E190)

//! Int Disable Register 160 --> 191
#define NVIC_DIS5                      ((unsigned long)0xE000E194)

//! Int Disable Register 192 --> 223
#define NVIC_DIS6                      ((unsigned long)0xE000E198)

//! Int Disable Register 224 --> 239
#define NVIC_DIS7                      ((unsigned long)0xE000E19C)

////////////////////////////// Int set pending register ////////////////////////////
//! Int Set Pending Register 0   --> 31
#define NVIC_SET_PEND0                 ((unsigned long)0xE000E200)

//! Int Set Pending Register 32  --> 63
#define NVIC_SET_PEND1                 ((unsigned long)0xE000E204)

//! Int Set Pending Register 64  --> 95
#define NVIC_SET_PEND2                 ((unsigned long)0xE000E208)

//! Int Set Pending Register 96  --> 127
#define NVIC_SET_PEND3                 ((unsigned long)0xE000E20C)

//! Int Set Pending Register 128 --> 159
#define NVIC_SET_PEND4                 ((unsigned long)0xE000E210)

//! Int Set Pending Register 160 --> 191
#define NVIC_SET_PEND5                 ((unsigned long)0xE000E214)

//! Int Set Pending Register 192 --> 223
#define NVIC_SET_PEND6                 ((unsigned long)0xE000E218)

//! Int Set Pending Register 224 --> 239
#define NVIC_SET_PEND7                 ((unsigned long)0xE000E21C)

////////////////////////////// Int clear pending register ////////////////////////////
//! Int Clear Pending Register 0   --> 31
#define NVIC_CLR_PEND0                 ((unsigned long)0xE000E280)

//! Int Clear Pending Register 32  --> 63
#define NVIC_CLR_PEND1                 ((unsigned long)0xE000E284)

//! Int Clear Pending Register 64  --> 95
#define NVIC_CLR_PEND2                 ((unsigned long)0xE000E288)

//! Int Clear Pending Register 96  --> 127
#define NVIC_CLR_PEND3                 ((unsigned long)0xE000E28C)

//! Int Clear Pending Register 128 --> 159
#define NVIC_CLR_PEND4                 ((unsigned long)0xE000E290)

//! Int Clear Pending Register 160 --> 191
#define NVIC_CLR_PEND5                 ((unsigned long)0xE000E294)

//! Int Clear Pending Register 192 --> 223
#define NVIC_CLR_PEND6                 ((unsigned long)0xE000E298)

//! Int Clear Pending Register 224 --> 239
#define NVIC_CLR_PEND7                 ((unsigned long)0xE000E29C)

////////////////////////////// Int Active bit register ////////////////////////////
//! Int Active Bit Register 0   --> 31
#define NVIC_ACT_BIT0                  ((unsigned long)0xE000E300)

//! Int Active Bit Register 32  --> 63
#define NVIC_ACT_BIT1                  ((unsigned long)0xE000E304)

//! Int Active Bit Register 64  --> 95
#define NVIC_ACT_BIT2                  ((unsigned long)0xE000E308)

//! Int Active Bit Register 96  --> 127
#define NVIC_ACT_BIT3                  ((unsigned long)0xE000E30C)

//! Int Active Bit Register 128 --> 159
#define NVIC_ACT_BIT4                  ((unsigned long)0xE000E310)

//! Int Active Bit Register 160 --> 191
#define NVIC_ACT_BIT5                  ((unsigned long)0xE000E314)

//! Int Active Bit Register 192 --> 223
#define NVIC_ACT_BIT6                  ((unsigned long)0xE000E318)

//! Int Active Bit Register 224 --> 239
#define NVIC_ACT_BIT7                  ((unsigned long)0xE000E31C)

////////////////////////// Int Priority Register ///////////////////////////////

//! Only suit for Int priority
//! NOT for system falut
#define NVIC_PRI0                      ((unsigned long)0XE000E400)
#define NVIC_PRI1                      ((unsigned long)0XE000E404)
#define NVIC_PRI2                      ((unsigned long)0XE000E408)
#define NVIC_PRI3                      ((unsigned long)0XE000E40C)
#define NVIC_PRI4                      ((unsigned long)0XE000E410)
#define NVIC_PRI5                      ((unsigned long)0XE000E414)
#define NVIC_PRI6                      ((unsigned long)0XE000E418)
#define NVIC_PRI7                      ((unsigned long)0XE000E41C)
#define NVIC_PRI8                      ((unsigned long)0XE000E420)
#define NVIC_PRI9                      ((unsigned long)0XE000E424)
#define NVIC_PRI10                     ((unsigned long)0XE000E428)
#define NVIC_PRI11                     ((unsigned long)0XE000E42C)
#define NVIC_PRI12                     ((unsigned long)0XE000E430)
#define NVIC_PRI13                     ((unsigned long)0XE000E434)
#define NVIC_PRI14                     ((unsigned long)0XE000E438)
#define NVIC_PRI15                     ((unsigned long)0XE000E43C)
#define NVIC_PRI16                     ((unsigned long)0XE000E440)
#define NVIC_PRI17                     ((unsigned long)0XE000E444)
#define NVIC_PRI18                     ((unsigned long)0XE000E448)
#define NVIC_PRI19                     ((unsigned long)0XE000E44C)
#define NVIC_PRI20                     ((unsigned long)0XE000E450)
#define NVIC_PRI21                     ((unsigned long)0XE000E454)
#define NVIC_PRI22                     ((unsigned long)0XE000E458)
#define NVIC_PRI23                     ((unsigned long)0XE000E45C)
#define NVIC_PRI24                     ((unsigned long)0XE000E460)
#define NVIC_PRI25                     ((unsigned long)0XE000E464)
#define NVIC_PRI26                     ((unsigned long)0XE000E468)
#define NVIC_PRI27                     ((unsigned long)0XE000E46C)
#define NVIC_PRI28                     ((unsigned long)0XE000E470)
#define NVIC_PRI29                     ((unsigned long)0XE000E474)
#define NVIC_PRI30                     ((unsigned long)0XE000E478)
#define NVIC_PRI31                     ((unsigned long)0XE000E47C)
#define NVIC_PRI32                     ((unsigned long)0XE000E480)
#define NVIC_PRI33                     ((unsigned long)0XE000E484)
#define NVIC_PRI34                     ((unsigned long)0XE000E488)
#define NVIC_PRI35                     ((unsigned long)0XE000E48C)
#define NVIC_PRI36                     ((unsigned long)0XE000E490)
#define NVIC_PRI37                     ((unsigned long)0XE000E494)
#define NVIC_PRI38                     ((unsigned long)0XE000E498)
#define NVIC_PRI39                     ((unsigned long)0XE000E49C)
#define NVIC_PRI40                     ((unsigned long)0XE000E4A0)
#define NVIC_PRI41                     ((unsigned long)0XE000E4A4)
#define NVIC_PRI42                     ((unsigned long)0XE000E4A8)
#define NVIC_PRI43                     ((unsigned long)0XE000E4AC)
#define NVIC_PRI44                     ((unsigned long)0XE000E4B0)
#define NVIC_PRI45                     ((unsigned long)0XE000E4B4)
#define NVIC_PRI46                     ((unsigned long)0XE000E4B8)
#define NVIC_PRI47                     ((unsigned long)0XE000E4BC)
#define NVIC_PRI48                     ((unsigned long)0XE000E4C0)
#define NVIC_PRI49                     ((unsigned long)0XE000E4C4)
#define NVIC_PRI50                     ((unsigned long)0XE000E4C8)
#define NVIC_PRI51                     ((unsigned long)0XE000E4CC)
#define NVIC_PRI52                     ((unsigned long)0XE000E4D0)
#define NVIC_PRI53                     ((unsigned long)0XE000E4D4)
#define NVIC_PRI54                     ((unsigned long)0XE000E4D8)
#define NVIC_PRI55                     ((unsigned long)0XE000E4DC)
#define NVIC_PRI56                     ((unsigned long)0XE000E4E0)
#define NVIC_PRI57                     ((unsigned long)0XE000E4E4)
#define NVIC_PRI58                     ((unsigned long)0XE000E4E8)
#define NVIC_PRI59                     ((unsigned long)0XE000E4EC)

//
//! CPU ID Base
//
#define NVIC_CPUID                     ((unsigned long)0xE000ED00)

//
//! Interrupt Control and State
//
#define NVIC_INT_CTRL                  ((unsigned long)0xE000ED04)

//
//! Vector Table Offset Register
//
#define NVIC_VTOR                      ((unsigned long)0xE000ED08)

//
//! Application Interrupt and Reset Control
//
#define NVIC_APINT                     ((unsigned long)0xE000ED0C)
//
//! System Control
//
#define NVIC_SYS_CTRL                  ((unsigned long)0xE000ED10)

//
//! Configuration and Control
//
#define NVIC_CFG_CTRL                  ((unsigned long)0xE000ED14)

//
//! System Handler 4-7 Priority Register
//
#define NVIC_SYS_PRI1                  ((unsigned long)0xE000ED18)

//
//! System Handler 8-11 Priority Register
//
#define NVIC_SYS_PRI2                  ((unsigned long)0xE000ED1C)

//
//! System Handler 12-15 Priority Register
//
#define NVIC_SYS_PRI3                  ((unsigned long)0xE000ED20)

//
//! System Handler Control and State
//
#define NVIC_SHCSR                     ((unsigned long)0xE000ED24)

//
//! Configure Fault Status Registers
//
#define NVIC_CFSR                      ((unsigned long)0xE000ED28)

//
//! Hard Fault Status Register
//
#define NVIC_HFSR                      ((unsigned long)0xE000ED2C)

//
//! Debug Status Register
//
#define NVIC_DEBUG_STAT                ((unsigned long)0xE000ED30)

//
//! Debug Control and Status Reg
//
#define NVIC_DBG_CTRL                  ((unsigned long)0xE000EDF0)

//
//! Debug Core Reg. Transfer Select
//
#define NVIC_DBG_XFER                  ((unsigned long)0xE000EDF4)

//
//! Debug Core Register Data
//
#define NVIC_DBG_DATA                  ((unsigned long)0xE000EDF8)

//
//! Debug Reset Interrupt Control
//
#define NVIC_DBG_INT                   ((unsigned long)0xE000EDFC)

//
//! Software Trigger Interrupt
//
#define NVIC_SW_TRIG                   ((unsigned long)0xE000EF00)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_INT_TYPE NVIC Interrupt Type Register(NVIC_INT_TYPE)
//! \brief Defines for the bit fields in the NVIC_INT_TYPE register.
//! @{
//
//*****************************************************************************

//
//! Number of interrupt lines (x32)
//
#define NVIC_INT_TYPE_LINES_M          ((unsigned long)0x0000001F)
#define NVIC_INT_TYPE_LINES_S          0

//! Total number of interrupt lines in groups of 32
#define NVIC_INT_LINE_0_32             ((unsigned long)0x00000000)
#define NVIC_INT_LINE_33_64            ((unsigned long)0x00000001)
#define NVIC_INT_LINE_65_96            ((unsigned long)0x00000002)
#define NVIC_INT_LINE_97_128           ((unsigned long)0x00000003)
#define NVIC_INT_LINE_129_160          ((unsigned long)0x00000004)
#define NVIC_INT_LINE_161_192          ((unsigned long)0x00000005)
#define NVIC_INT_LINE_193_224          ((unsigned long)0x00000006)
#define NVIC_INT_LINE_224_256          ((unsigned long)0x00000007)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_ACTLR NVIC ACTLR Register(NVIC_ACTLR)
//! \brief Defines for the bit fields in the NVIC_ACTLR register.
//! @{
//
//*****************************************************************************

//
//! Disable IT Folding
//
#define NVIC_ACTLR_DISFOLD             ((unsigned long)0x00000004)

//
//! Disable Write Buffer
//
#define NVIC_ACTLR_DISWBUF             ((unsigned long)0x00000002)

//
//! Disable Interrupts of Multiple Cycle Instructions
//
#define NVIC_ACTLR_DISMCYC             ((unsigned long)0x00000001)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_ST_CTRL NVIC Status Control Register(NVIC_ST_CTRL)
//! \brief Defines for the bit fields in the NVIC_ST_CTRL register.
//! @{
//
//*****************************************************************************

//
//! Count Flag
//
#define NVIC_ST_CTRL_COUNT             ((unsigned long)0x00010000)

//
//! Clock Source
//
#define NVIC_ST_CTRL_CLK_SRC           ((unsigned long)0x00000004)

//
//! System tick clock souce: exteranl reference clock
//
#define SYSTICK_SRC_EXT                ((unsigned long)0x00000000)

//
//! System tick clock souce: core clock
//
#define SYSTICK_SRC_CORE               ((unsigned long)0x00000004)

//
//! Interrupt Enable
//
#define NVIC_ST_CTRL_INTEN             ((unsigned long)0x00000002)

//
//! Enable
//
#define NVIC_ST_CTRL_ENABLE            ((unsigned long)0x00000001)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_ST_RELOAD NVIC Status Reload Register(NVIC_ST_RELOAD)
//! \brief Defines for the bit fields in the NVIC_ST_RELOAD register.
//! @{
//
//*****************************************************************************

//
//! Reload Value
//
#define NVIC_ST_RELOAD_M               ((unsigned long)0x00FFFFFF)
#define NVIC_ST_RELOAD_S               0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_ST_CURRENT NVIC Status Current Register(NVIC_ST_CURRENT)
//! \brief Defines for the bit fields in the NVIC_ST_CURRENT register.
//! @{
//
//*****************************************************************************

//
//! Current Value
//
#define NVIC_ST_CURRENT_M              ((unsigned long)0x00FFFFFF)
#define NVIC_ST_CURRENT_S              0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_ST_CAL NVIC Status Cal Register(NVIC_ST_CAL)
//! \brief Defines for the bit fields in the NVIC_ST_CAL register.
//! @{
//
//*****************************************************************************

//
//! No reference clock
//
#define NVIC_ST_CAL_NOREF              ((unsigned long)0x80000000)

//
//! Clock skew
//
#define NVIC_ST_CAL_SKEW               ((unsigned long)0x40000000)

//
//! 10ms reference value
//
#define NVIC_ST_CAL_TNEMS_M            ((unsigned long)0x00FFFFFF)
#define NVIC_ST_CAL_TNEMS_S            0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_EN0 NVIC Ebanle0 Register(NVIC_EN0)
//! \brief Defines for the bit fields in the NVIC_EN0 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Enable
//
#define NVIC_EN0_INT_M                 ((unsigned long)0xFFFFFFFF)

//
//! Interrupt 0 enable
//
#define NVIC_EN0_INT0                  ((unsigned long)0x00000001)

//
//! Interrupt 1 enable
//
#define NVIC_EN0_INT1                  ((unsigned long)0x00000002)

//
//! Interrupt 2 enable
//
#define NVIC_EN0_INT2                  ((unsigned long)0x00000004)

//
//! Interrupt 3 enable
//
#define NVIC_EN0_INT3                  ((unsigned long)0x00000008)

//
//! Interrupt 4 enable
//
#define NVIC_EN0_INT4                  ((unsigned long)0x00000010)

//
//! Interrupt 5 enable
//
#define NVIC_EN0_INT5                  ((unsigned long)0x00000020)

//
//! Interrupt 6 enable
//
#define NVIC_EN0_INT6                  ((unsigned long)0x00000040)

//
//! Interrupt 7 enable
//
#define NVIC_EN0_INT7                  ((unsigned long)0x00000080)

//
//! Interrupt 8 enable
//
#define NVIC_EN0_INT8                  ((unsigned long)0x00000100)

//
//! Interrupt 9 enable
//
#define NVIC_EN0_INT9                  ((unsigned long)0x00000200)

//
//! Interrupt 10 enable
//
#define NVIC_EN0_INT10                 ((unsigned long)0x00000400)

//
//! Interrupt 11 enable
//
#define NVIC_EN0_INT11                 ((unsigned long)0x00000800)

//
//! Interrupt 12 enable
//
#define NVIC_EN0_INT12                 ((unsigned long)0x00001000)

//
//! Interrupt 13 enable
//
#define NVIC_EN0_INT13                 ((unsigned long)0x00002000)

//
//! Interrupt 14 enable
//
#define NVIC_EN0_INT14                 ((unsigned long)0x00004000)

//
//! Interrupt 15 enable
//
#define NVIC_EN0_INT15                 ((unsigned long)0x00008000)

//
//! Interrupt 16 enable
//
#define NVIC_EN0_INT16                 ((unsigned long)0x00010000)

//
//! Interrupt 17 enable
//
#define NVIC_EN0_INT17                 ((unsigned long)0x00020000)

//
//! Interrupt 18 enable
//
#define NVIC_EN0_INT18                 ((unsigned long)0x00040000)

//
//! Interrupt 19 enable
//
#define NVIC_EN0_INT19                 ((unsigned long)0x00080000)

//
//! Interrupt 20 enable
//
#define NVIC_EN0_INT20                 ((unsigned long)0x00100000)

//
//! Interrupt 21 enable
//
#define NVIC_EN0_INT21                 ((unsigned long)0x00200000)

//
//! Interrupt 22 enable
//
#define NVIC_EN0_INT22                 ((unsigned long)0x00400000)

//
//! Interrupt 23 enable
//
#define NVIC_EN0_INT23                 ((unsigned long)0x00800000)

//
//! Interrupt 24 enable
//
#define NVIC_EN0_INT24                 ((unsigned long)0x01000000)

//
//! Interrupt 25 enable
//
#define NVIC_EN0_INT25                 ((unsigned long)0x02000000)
//
//! Interrupt 26 enable
//
#define NVIC_EN0_INT26                 ((unsigned long)0x04000000)

//
//! Interrupt 27 enable
//
#define NVIC_EN0_INT27                 ((unsigned long)0x08000000)

//
//! Interrupt 28 enable
//
#define NVIC_EN0_INT28                 ((unsigned long)0x10000000)
//
//! Interrupt 29 enable
//
#define NVIC_EN0_INT29                 ((unsigned long)0x20000000)

//
//! Interrupt 30 enable
//
#define NVIC_EN0_INT30                 ((unsigned long)0x40000000)

//
//! Interrupt 31 enable
//
#define NVIC_EN0_INT31                 ((unsigned long)0x80000000)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_DIS0 NVIC Disable0 Register(NVIC_DIS0)
//! \brief Defines for the bit fields in the NVIC_DIS0 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Disable
//
#define NVIC_DIS0_INT_M                ((unsigned long)0xFFFFFFFF)

//
//! Interrupt 0 disable
//
#define NVIC_DIS0_INT0                 ((unsigned long)0x00000001)

//
//! Interrupt 1 disable
//
#define NVIC_DIS0_INT1                 ((unsigned long)0x00000002)

//
//! Interrupt 2 disable
//
#define NVIC_DIS0_INT2                 ((unsigned long)0x00000004)

//
//! Interrupt 3 disable
//
#define NVIC_DIS0_INT3                 ((unsigned long)0x00000008)

//
//! Interrupt 4 disable
//
#define NVIC_DIS0_INT4                 ((unsigned long)0x00000010)

//
//! Interrupt 5 disable
//
#define NVIC_DIS0_INT5                 ((unsigned long)0x00000020)

//
//! Interrupt 6 disable
//
#define NVIC_DIS0_INT6                 ((unsigned long)0x00000040)

//
//! Interrupt 7 disable
//
#define NVIC_DIS0_INT7                 ((unsigned long)0x00000080)

//
//! Interrupt 8 disable
//
#define NVIC_DIS0_INT8                 ((unsigned long)0x00000100)

//
//! Interrupt 9 disable
//
#define NVIC_DIS0_INT9                 ((unsigned long)0x00000200)

//
//! Interrupt 10 disable
//
#define NVIC_DIS0_INT10                ((unsigned long)0x00000400)

//
//! Interrupt 11 disable
//
#define NVIC_DIS0_INT11                ((unsigned long)0x00000800)

//
//! Interrupt 12 disable
//
#define NVIC_DIS0_INT12                ((unsigned long)0x00001000)

//
//! Interrupt 13 disable
//
#define NVIC_DIS0_INT13                ((unsigned long)0x00002000)

//
//! Interrupt 14 disable
//
#define NVIC_DIS0_INT14                ((unsigned long)0x00004000)

//
//! Interrupt 15 disable
//
#define NVIC_DIS0_INT15                ((unsigned long)0x00008000)

//
//! Interrupt 16 disable
//
#define NVIC_DIS0_INT16                ((unsigned long)0x00010000)

//
//! Interrupt 17 disable
//
#define NVIC_DIS0_INT17                ((unsigned long)0x00020000)

//
//! Interrupt 18 disable
//
#define NVIC_DIS0_INT18                ((unsigned long)0x00040000)

//
//! Interrupt 19 disable
//
#define NVIC_DIS0_INT19                ((unsigned long)0x00080000)

//
//! Interrupt 20 disable
//
#define NVIC_DIS0_INT20                ((unsigned long)0x00100000)

//
//! Interrupt 21 disable
//
#define NVIC_DIS0_INT21                ((unsigned long)0x00200000)

//
//! Interrupt 22 disable
//
#define NVIC_DIS0_INT22                ((unsigned long)0x00400000)

//
//! Interrupt 23 disable
//
#define NVIC_DIS0_INT23                ((unsigned long)0x00800000)

//
//! Interrupt 24 disable
//
#define NVIC_DIS0_INT24                ((unsigned long)0x01000000)

//
//! Interrupt 25 disable
//
#define NVIC_DIS0_INT25                ((unsigned long)0x02000000)

//
//! Interrupt 26 disable
//
#define NVIC_DIS0_INT26                ((unsigned long)0x04000000)

//
//! Interrupt 27 disable
//
#define NVIC_DIS0_INT27                ((unsigned long)0x08000000)

//
//! Interrupt 28 disable
//
#define NVIC_DIS0_INT28                ((unsigned long)0x10000000)

//
//! Interrupt 29 disable
//
#define NVIC_DIS0_INT29                ((unsigned long)0x20000000)

//
// Interrupt 30 disable
//
#define NVIC_DIS0_INT30                ((unsigned long)0x40000000)

//
//! Interrupt 31 disable
//
#define NVIC_DIS0_INT31                ((unsigned long)0x80000000)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_PEND0 NVIC PEND 0 Register(NVIC_PEND0)
//! \brief Defines for the bit fields in the NVIC_PEND0 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Set Pending
//
#define NVIC_PEND0_INT_M               ((unsigned long)0xFFFFFFFF)

//
//! Interrupt 0 pend
//
#define NVIC_PEND0_INT0                ((unsigned long)0x00000001)

//
//! Interrupt 1 pend
//
#define NVIC_PEND0_INT1                ((unsigned long)0x00000002)

//
//! Interrupt 2 pend
//
#define NVIC_PEND0_INT2                ((unsigned long)0x00000004)

//
//! Interrupt 3 pend
//
#define NVIC_PEND0_INT3                ((unsigned long)0x00000008)

//
//! Interrupt 4 pend
//
#define NVIC_PEND0_INT4                ((unsigned long)0x00000010)

//
//! Interrupt 5 pend
//
#define NVIC_PEND0_INT5                ((unsigned long)0x00000020)

//
//! Interrupt 6 pend
//
#define NVIC_PEND0_INT6                ((unsigned long)0x00000040)

//
//! Interrupt 7 pend
//
#define NVIC_PEND0_INT7                ((unsigned long)0x00000080)

//
//! Interrupt 8 pend
//
#define NVIC_PEND0_INT8                ((unsigned long)0x00000100)

//
//! Interrupt 9 pend
//
#define NVIC_PEND0_INT9                ((unsigned long)0x00000200)

//
//! Interrupt 10 pend
//
#define NVIC_PEND0_INT10               ((unsigned long)0x00000400)

//
//! Interrupt 11 pend
//
#define NVIC_PEND0_INT11               ((unsigned long)0x00000800)

//
//! Interrupt 12 pend
//
#define NVIC_PEND0_INT12               ((unsigned long)0x00001000)

//
//! Interrupt 13 pend
//
#define NVIC_PEND0_INT13               ((unsigned long)0x00002000)

//
//! Interrupt 14 pend
//
#define NVIC_PEND0_INT14               ((unsigned long)0x00004000)

//
//! Interrupt 15 pend
//
#define NVIC_PEND0_INT15               ((unsigned long)0x00008000)

//
//! Interrupt 16 pend
//
#define NVIC_PEND0_INT16               ((unsigned long)0x00010000)

//
//! Interrupt 17 pend
//
#define NVIC_PEND0_INT17               ((unsigned long)0x00020000)

//
//! Interrupt 18 pend
//
#define NVIC_PEND0_INT18               ((unsigned long)0x00040000)

//
//! Interrupt 19 pend
//
#define NVIC_PEND0_INT19               ((unsigned long)0x00080000)

//
//! Interrupt 20 pend
//
#define NVIC_PEND0_INT20               ((unsigned long)0x00100000)

//
//! Interrupt 21 pend
//
#define NVIC_PEND0_INT21               ((unsigned long)0x00200000)

//
//! Interrupt 22 pend
//
#define NVIC_PEND0_INT22               ((unsigned long)0x00400000)

//
//! Interrupt 23 pend
//
#define NVIC_PEND0_INT23               ((unsigned long)0x00800000)

//
//! Interrupt 24 pend
//
#define NVIC_PEND0_INT24               ((unsigned long)0x01000000)

//
//! Interrupt 25 pend
//
#define NVIC_PEND0_INT25               ((unsigned long)0x02000000)

//
//! Interrupt 26 pend
//
#define NVIC_PEND0_INT26               ((unsigned long)0x04000000)

//
//! Interrupt 27 pend
//
#define NVIC_PEND0_INT27               ((unsigned long)0x08000000)

//
//! Interrupt 28 pend
//
#define NVIC_PEND0_INT28               ((unsigned long)0x10000000)

//
//! Interrupt 29 pend
//
#define NVIC_PEND0_INT29               ((unsigned long)0x20000000)

//
//! Interrupt 30 pend
//
#define NVIC_PEND0_INT30               ((unsigned long)0x40000000)

//
//! Interrupt 31 pend
//
#define NVIC_PEND0_INT31               ((unsigned long)0x80000000)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_UNPEND0 NVIC UNPEND 0 Register(NVIC_UNPEND0)
//! \brief Defines for the bit fields in the NVIC_UNPEND0 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Clear Pending
//
#define NVIC_UNPEND0_INT_M             ((unsigned long)0xFFFFFFFF)

//
//! Interrupt 0 unpend
//
#define NVIC_UNPEND0_INT0              ((unsigned long)0x00000001)

//
//! Interrupt 1 unpend
//
#define NVIC_UNPEND0_INT1              ((unsigned long)0x00000002)

//
//! Interrupt 2 unpend
//
#define NVIC_UNPEND0_INT2              ((unsigned long)0x00000004)

//
//! Interrupt 3 unpend
//
#define NVIC_UNPEND0_INT3              ((unsigned long)0x00000008)

//
//! Interrupt 4 unpend
//
#define NVIC_UNPEND0_INT4              ((unsigned long)0x00000010)

//
//! Interrupt 5 unpend
//
#define NVIC_UNPEND0_INT5              ((unsigned long)0x00000020)

//
//! Interrupt 6 unpend
//
#define NVIC_UNPEND0_INT6              ((unsigned long)0x00000040)

//
//! Interrupt 7 unpend
//
#define NVIC_UNPEND0_INT7              ((unsigned long)0x00000080)

//
//! Interrupt 8 unpend
//
#define NVIC_UNPEND0_INT8              ((unsigned long)0x00000100)
//
//! Interrupt 9 unpend
//
#define NVIC_UNPEND0_INT9              ((unsigned long)0x00000200)

//
//! Interrupt 10 unpend
//
#define NVIC_UNPEND0_INT10             ((unsigned long)0x00000400)

//
//! Interrupt 11 unpend
//
#define NVIC_UNPEND0_INT11             ((unsigned long)0x00000800)

//
//! Interrupt 12 unpend
//
#define NVIC_UNPEND0_INT12             ((unsigned long)0x00001000)

//
//! Interrupt 13 unpend
//
#define NVIC_UNPEND0_INT13             ((unsigned long)0x00002000)

//
//! Interrupt 14 unpend
//
#define NVIC_UNPEND0_INT14             ((unsigned long)0x00004000)

//
//! Interrupt 15 unpend
//
#define NVIC_UNPEND0_INT15             ((unsigned long)0x00008000)

//
//! Interrupt 16 unpend
//
#define NVIC_UNPEND0_INT16             ((unsigned long)0x00010000)

//
//! Interrupt 17 unpend
//
#define NVIC_UNPEND0_INT17             ((unsigned long)0x00020000)

//
//! Interrupt 18 unpend
//
#define NVIC_UNPEND0_INT18             ((unsigned long)0x00040000)

//
//! Interrupt 19 unpend
//
#define NVIC_UNPEND0_INT19             ((unsigned long)0x00080000)

//
//! Interrupt 20 unpend
//
#define NVIC_UNPEND0_INT20             ((unsigned long)0x00100000)

//
//! Interrupt 21 unpend
//
#define NVIC_UNPEND0_INT21             ((unsigned long)0x00200000)

//
//! Interrupt 22 unpend
//
#define NVIC_UNPEND0_INT22             ((unsigned long)0x00400000)

//
//! Interrupt 23 unpend
//
#define NVIC_UNPEND0_INT23             ((unsigned long)0x00800000)

//
//! Interrupt 24 unpend
//
#define NVIC_UNPEND0_INT24             ((unsigned long)0x01000000)

//
//! Interrupt 25 unpend
//
#define NVIC_UNPEND0_INT25             ((unsigned long)0x02000000)

//
//! Interrupt 26 unpend
//
#define NVIC_UNPEND0_INT26             ((unsigned long)0x04000000)

//
//! Interrupt 27 unpend
//
#define NVIC_UNPEND0_INT27             ((unsigned long)0x08000000)

//
//! Interrupt 28 unpend
//
#define NVIC_UNPEND0_INT28             ((unsigned long)0x10000000)

//
//! Interrupt 29 unpend
//
#define NVIC_UNPEND0_INT29             ((unsigned long)0x20000000)

//
//! Interrupt 30 unpend
//
#define NVIC_UNPEND0_INT30             ((unsigned long)0x40000000)

//
//! Interrupt 31 unpend
//
#define NVIC_UNPEND0_INT31             ((unsigned long)0x80000000)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_PRI0 NVIC Priority 0 Register(NVIC_PRI0)
//! \brief Defines for the bit fields in the NVIC_PRI0 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 3 Priority Mask
//
#define NVIC_PRI0_INT3_M               ((unsigned long)0xC0000000)

//
//! Interrupt 2 Priority Mask
//
#define NVIC_PRI0_INT2_M               ((unsigned long)0x00C00000)

//
//! Interrupt 1 Priority Mask
//
#define NVIC_PRI0_INT1_M               ((unsigned long)0x0000C000)

//
//! Interrupt 0 Priority Mask
//
#define NVIC_PRI0_INT0_M               ((unsigned long)0x000000C0)
#define NVIC_PRI0_INT3_S               30
#define NVIC_PRI0_INT2_S               22
#define NVIC_PRI0_INT1_S               14
#define NVIC_PRI0_INT0_S               6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_PRI1 NVIC Priority 1 Register(NVIC_PRI1)
//! \brief Defines for the bit fields in the NVIC_PRI1 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 7 Priority Mask
//
#define NVIC_PRI1_INT7_M               ((unsigned long)0xC0000000)

//
//! Interrupt 6 Priority Mask
//
#define NVIC_PRI1_INT6_M               ((unsigned long)0x00C00000)

//
//! Interrupt 5 Priority Mask
//
#define NVIC_PRI1_INT5_M               ((unsigned long)0x0000C000)

//
//! Interrupt 4 Priority Mask
//
#define NVIC_PRI1_INT4_M               ((unsigned long)0x000000C0)
#define NVIC_PRI1_INT7_S               30
#define NVIC_PRI1_INT6_S               22
#define NVIC_PRI1_INT5_S               14
#define NVIC_PRI1_INT4_S               6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_PRI2 NVIC Priority 2 Register(NVIC_PRI2)
//! \brief Defines for the bit fields in the NVIC_PRI2 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 11 Priority Mask
//
#define NVIC_PRI2_INT11_M              ((unsigned long)0xC0000000)

//
//! Interrupt 10 Priority Mask
//
#define NVIC_PRI2_INT10_M              ((unsigned long)0x00C00000)

//
//! Interrupt 9 Priority Mask
//
#define NVIC_PRI2_INT9_M               ((unsigned long)0x0000C000)

//
//! Interrupt 8 Priority Mask
//
#define NVIC_PRI2_INT8_M               ((unsigned long)0x000000C0)
#define NVIC_PRI2_INT11_S              30
#define NVIC_PRI2_INT10_S              22
#define NVIC_PRI2_INT9_S               14
#define NVIC_PRI2_INT8_S               6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_PRI3 NVIC Priority 3 Register(NVIC_PRI3)
//! \brief Defines for the bit fields in the NVIC_PRI3 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 15 Priority Mask
//
#define NVIC_PRI3_INT15_M              ((unsigned long)0xC0000000)

//
//! Interrupt 14 Priority Mask
//
#define NVIC_PRI3_INT14_M              ((unsigned long)0x00C00000)

//
//! Interrupt 13 Priority Mask
//
#define NVIC_PRI3_INT13_M              ((unsigned long)0x0000C000)

//
//! Interrupt 12 Priority Mask
//
#define NVIC_PRI3_INT12_M              ((unsigned long)0x000000C0)
#define NVIC_PRI3_INT15_S              30
#define NVIC_PRI3_INT14_S              22
#define NVIC_PRI3_INT13_S              14
#define NVIC_PRI3_INT12_S              6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_PRI4 NVIC Priority 4 Register(NVIC_PRI4)
//! \brief Defines for the bit fields in the NVIC_PRI4 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 19 Priority Mask
//
#define NVIC_PRI4_INT19_M              ((unsigned long)0xC0000000)

//
//! Interrupt 18 Priority Mask
//
#define NVIC_PRI4_INT18_M              ((unsigned long)0x00C00000)

//
//! Interrupt 17 Priority Mask
//
#define NVIC_PRI4_INT17_M              ((unsigned long)0x0000C000)

//
//! Interrupt 16 Priority Mask
//
#define NVIC_PRI4_INT16_M              ((unsigned long)0x000000C0)
#define NVIC_PRI4_INT19_S              30
#define NVIC_PRI4_INT18_S              22
#define NVIC_PRI4_INT17_S              14
#define NVIC_PRI4_INT16_S              6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_PRI5 NVIC Priority 5 Register(NVIC_PRI5)
//! \brief Defines for the bit fields in the NVIC_PRI5 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 23 Priority Mask
//
#define NVIC_PRI5_INT23_M              ((unsigned long)0xC0000000)

//
//! Interrupt 22 Priority Mask
//
#define NVIC_PRI5_INT22_M              ((unsigned long)0x00C00000)

//
//! Interrupt 21 Priority Mask
//
#define NVIC_PRI5_INT21_M              ((unsigned long)0x0000C000)

//
//! Interrupt 20 Priority Mask
//
#define NVIC_PRI5_INT20_M              ((unsigned long)0x000000C0)
#define NVIC_PRI5_INT23_S              30
#define NVIC_PRI5_INT22_S              22
#define NVIC_PRI5_INT21_S              14
#define NVIC_PRI5_INT20_S              6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_PRI6 NVIC Priority 6 Register(NVIC_PRI6)
//! \brief Defines for the bit fields in the NVIC_PRI6 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 27 Priority Mask
//
#define NVIC_PRI6_INT27_M              ((unsigned long)0xC0000000)

//
//! Interrupt 26 Priority Mask
//
#define NVIC_PRI6_INT26_M              ((unsigned long)0x00C00000)

//
//! Interrupt 25 Priority Mask
//
#define NVIC_PRI6_INT25_M              ((unsigned long)0x0000C000)

//
//! Interrupt 24 Priority Mask
//
#define NVIC_PRI6_INT24_M              ((unsigned long)0x000000C0)
#define NVIC_PRI6_INT27_S              30
#define NVIC_PRI6_INT26_S              22
#define NVIC_PRI6_INT25_S              14
#define NVIC_PRI6_INT24_S              6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_PRI7 NVIC Priority 7 Register(NVIC_PRI7)
//! \brief Defines for the bit fields in the NVIC_PRI7 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 31 Priority Mask
//
#define NVIC_PRI7_INT31_M              ((unsigned long)0xC0000000)

//
//! Interrupt 30 Priority Mask
//
#define NVIC_PRI7_INT30_M              ((unsigned long)0x00C00000)

//
//! Interrupt 29 Priority Mask
//
#define NVIC_PRI7_INT29_M              ((unsigned long)0x0000C000)

//
//! Interrupt 28 Priority Mask
//
#define NVIC_PRI7_INT28_M              ((unsigned long)0x000000C0)
#define NVIC_PRI7_INT31_S              30
#define NVIC_PRI7_INT30_S              22
#define NVIC_PRI7_INT29_S              14
#define NVIC_PRI7_INT28_S              6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_CPUID  NVIC CPUID Register(NVIC_CPUID)
//! \brief Defines for the bit fields in the NVIC_CPUID register.
//! @{
//
//*****************************************************************************

//
//! Implementer Code
//
#define NVIC_CPUID_IMP_M               ((unsigned long)0xFF000000)

//
//! ARM
//
#define NVIC_CPUID_IMP_ARM             ((unsigned long)0x41000000)

//
//! Variant Number
//
#define NVIC_CPUID_VAR_M               ((unsigned long)0x00F00000)

//
//! Constant
//
#define NVIC_CPUID_CON_M               ((unsigned long)0x000F0000)

//
//! Part Number
//
#define NVIC_CPUID_PARTNO_M            ((unsigned long)0x0000FFF0)

//
//! Cortex-M3 processor
//
#define NVIC_CPUID_PARTNO_CM3          ((unsigned long)0x0000C230)

//
//! Revision Number
//
#define NVIC_CPUID_REV_M               ((unsigned long)0x0000000F)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_INT_CTRL NVIC Interrupt Control Register(NVIC_INT_CTRL)
//! \brief Defines for the bit fields in the NVIC_INT_CTRL register.
//! @{
//
//*****************************************************************************

//
//! NMI Set Pending
//
#define NVIC_INT_CTRL_NMI_PEND_SET     ((unsigned long)0x80000000)

//
//! PendSV Set Pending
//
#define NVIC_INT_CTRL_SV_PEND_SET      ((unsigned long)0x10000000)

//
//! PendSV Clear Pending
//
#define NVIC_INT_CTRL_SV_PEND_CLR      ((unsigned long)0x08000000)

//
//! SysTick Set Pending
//
#define NVIC_INT_CTRL_ST_PEND_SET      ((unsigned long)0x04000000)

//
//! SysTick Clear Pending
//
#define NVIC_INT_CTRL_ST_PEND_CLR      ((unsigned long)0x02000000)

//
//! Debug Interrupt Handling
//
#define NVIC_INT_CTRL_ISR_PRE          ((unsigned long)0x00800000)

//
//! Interrupt Pending
//
#define NVIC_INT_CTRL_ISR_PENDING      ((unsigned long)0x00400000)

//
//! Interrupt Pending Vector Number
//
#define NVIC_INT_CTRL_VEC_PEN_M        ((unsigned long)0x0007F000)

#define NVIC_INT_CTRL_VEC_PEN_S        12

//
//! NMI
//
#define NVIC_INT_CTRL_VEC_PEN_NMI      ((unsigned long)0x00002000)

//
//! Hard fault
//
#define NVIC_INT_CTRL_VEC_PEN_HARD     ((unsigned long)0x00003000)

//
//! Memory management fault
//
#define NVIC_INT_CTRL_VEC_PEN_MEM      ((unsigned long)0x00004000)

//
//! Bus fault
//
#define NVIC_INT_CTRL_VEC_PEN_BUS      ((unsigned long)0x00005000)

//
//! Usage fault
//
#define NVIC_INT_CTRL_VEC_PEN_USG      ((unsigned long)0x00006000)

//
//! SVCall
//
#define NVIC_INT_CTRL_VEC_PEN_SVC      ((unsigned long)0x0000B000)

//
//! PendSV
//
#define NVIC_INT_CTRL_VEC_PEN_PNDSV    ((unsigned long)0x0000C000)

//
//! SysTick
//
#define NVIC_INT_CTRL_VEC_PEN_TICK     ((unsigned long)0x0000F000)

//
//! Return to Base
//
#define NVIC_INT_CTRL_RET_BASE         ((unsigned long)0x00000800)

//
//! Interrupt Pending Vector Number
//
#define NVIC_INT_CTRL_VEC_ACT_M        ((unsigned long)0x000001FF)
#define NVIC_INT_CTRL_VEC_ACT_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_VTOR NVIC Vector Table Offset Register.
//! \brief Defines for the bit fields in the NVIC_VTOR register.
//! @{
//
//*****************************************************************************

//
//! Table base is in Code(0) or RAM(1)
//
#define NVIC_CTOR_TBLBASE              ((unsigned long)0x20000000)

//
//!  Vector table base offset field. Contains the offset of the table base from
//!  the bottom of the SRAM or CODE space.
//
#define NVIC_CTOR_TBLOFF_M             ((unsigned long)0x1FFFFF80)
#define NVIC_CTOR_TBLOFF_S             6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************



//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_APINT NVIC APINT Register(NVIC_APINT)
//! \brief Defines for the bit fields in the NVIC_APINT register.
//! @{
//
//*****************************************************************************

//
//! Register Key
//
#define NVIC_APINT_VECTKEY_M           ((unsigned long)0xFFFF0000)

//
//! Vector key
//
#define NVIC_APINT_VECTKEY             ((unsigned long)0x05FA0000)

//
//! Data Endianess
//
#define NVIC_APINT_ENDIANESS           ((unsigned long)0x00008000)

//
//! Interrupt Priority Grouping
//
#define NVIC_APINT_PRIGROUP_M          ((unsigned long)0x00000700)

//
//! Priority group 7.1 split
//
#define NVIC_APINT_PRIGROUP_7_1        ((unsigned long)0x00000000)

//
//! Priority group 6.2 split
//
#define NVIC_APINT_PRIGROUP_6_2        ((unsigned long)0x00000100)

//
//! Priority group 5.3 split
//
#define NVIC_APINT_PRIGROUP_5_3        ((unsigned long)0x00000200)

//
//! Priority group 4.4 split
//
#define NVIC_APINT_PRIGROUP_4_4        ((unsigned long)0x00000300)

//
//! Priority group 3.5 split
//
#define NVIC_APINT_PRIGROUP_3_5        ((unsigned long)0x00000400)

//
//! Priority group 2.6 split
//
#define NVIC_APINT_PRIGROUP_2_6        ((unsigned long)0x00000500)

//
//! Priority group 1.7 split
//
#define NVIC_APINT_PRIGROUP_1_7        ((unsigned long)0x00000600)

//
//! Priority group 0.8 split
//
#define NVIC_APINT_PRIGROUP_0_8        ((unsigned long)0x00000700)

//
//! System Reset Request
//
#define NVIC_APINT_SYSRESETREQ         ((unsigned long)0x00000004)

//
//! Clear Active NMI / Fault
//
#define NVIC_APINT_VECT_CLR_ACT        ((unsigned long)0x00000002)

//
//! System Reset
//
#define NVIC_APINT_VECT_RESET          ((unsigned long)0x00000001)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_SYS_CTRL NVIC System Control Register(NVIC_SYS_CTRL)
//! \brief Defines for the bit fields in the NVIC_SYS_CTRL register.
//! @{
//
//*****************************************************************************

//
//! Wake Up on Pending
//
#define NVIC_SYS_CTRL_SEVONPEND        ((unsigned long)0x00000010)

//
//! Deep Sleep Enable
//
#define NVIC_SYS_CTRL_SLEEPDEEP        ((unsigned long)0x00000004)

//
//! Sleep on ISR Exit
//
#define NVIC_SYS_CTRL_SLEEPEXIT        ((unsigned long)0x00000002)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_CFG_CTRL NVIC Cfg Control Register(NVIC_CFG_CTRL)
//! \brief Defines for the bit fields in the NVIC_CFG_CTRL register.
//! @{
//
//*****************************************************************************

//
//! Stack Alignment on Exception Entry
//
#define NVIC_CFG_CTRL_STKALIGN         ((unsigned long)0x00000200)

//
//! Ignore Bus Fault in NMI and Fault
//
#define NVIC_CFG_CTRL_BFHFNMIGN        ((unsigned long)0x00000100)

//
//! Trap on Divide by 0
//
#define NVIC_CFG_CTRL_DIV0             ((unsigned long)0x00000010)

//
//! Trap on Unaligned Access
//
#define NVIC_CFG_CTRL_UNALIGNED        ((unsigned long)0x00000008)

//
//! Allow Main Interrupt Trigger
//
#define NVIC_CFG_CTRL_MAIN_PEND        ((unsigned long)0x00000002)

//
//! Thread State Control
//
#define NVIC_CFG_CTRL_BASE_THR         ((unsigned long)0x00000001)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_SYS_PRI2 NVIC System Priority 2 Register(NVIC_SYS_PRI2)
//! \brief Defines for the bit fields in the NVIC_SYS_PRI2 register.
//! @{
//
//*****************************************************************************

//
//! SVCall Priority
//
#define NVIC_SYS_PRI2_SVC_M            ((unsigned long)0xC0000000)
#define NVIC_SYS_PRI2_SVC_S            29

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_SYS_PRI3 NVIC System Priority 3 Register(NVIC_SYS_PRI3)
//! \brief Defines for the bit fields in the NVIC_SYS_PRI3 register.
//! @{
//
//*****************************************************************************

//
//! SysTick Exception Priority
//
#define NVIC_SYS_PRI3_TICK_M           ((unsigned long)0xC0000000)

//
//! PendSV Priority
//
#define NVIC_SYS_PRI3_PENDSV_M         ((unsigned long)0x00C00000)

//
//! Debug Priority
//
#define NVIC_SYS_PRI3_DEBUG_M          ((unsigned long)0x000000C0)
#define NVIC_SYS_PRI3_TICK_S           29
#define NVIC_SYS_PRI3_PENDSV_S         21
#define NVIC_SYS_PRI3_DEBUG_S          5

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_SYS_HND_CTRL NVIC HND Control Register(NVIC_SYS_HND_CTRL)
//! \brief Defines for the bit fields in the NVIC_SYS_HND_CTRL register.
//! @{
//
//*****************************************************************************

//
//! Usage Fault Enable
//
#define NVIC_SHCSR_USG_FAULT_EN        ((unsigned long)0x00040000)

//
//! Bus Fault Enable
//
#define NVIC_SHCSR_BUS_FAULT_EN        ((unsigned long)0x00020000)

//
//! Memory Management Fault Enable
//
#define NVIC_SHCSR_MEM_FAULT_EN        ((unsigned long)0x00010000)

//
//! SVC Call Pending
//
#define NVIC_SHCSR_SVC_PENDED          ((unsigned long)0x00008000)

//
//! Bus Fault Pending
//
#define NVIC_SHCSR_BUS_FAULT_PENDED    ((unsigned long)0x00004000)

//
//! Memory Management Fault Pending
//
#define NVIC_SHCSR_MEM_FAULT_PENDED    ((unsigned long)0x00002000)

//
//! Usage Fault Pending
//
#define NVIC_SHCSR_USG_FAULT_PENDED    ((unsigned long)0x00001000)

//
//! SysTick Exception Active
//
#define NVIC_SHCSR_ST_ACT              ((unsigned long)0x00000800)

//
//! PendSV Exception Active
//
#define NVIC_SHCSR_PENDSV_ACT          ((unsigned long)0x00000400)

//
//! Debug Monitor Active
//
#define NVIC_SHCSR_MONITOR_ACT         ((unsigned long)0x00000100)

//
//! SVC Call Active
//
#define NVIC_SHCSR_SVC_ACT             ((unsigned long)0x00000080)

//
//! Usage Fault Active
//
#define NVIC_SHCSR_USG_FAULT_ACT       ((unsigned long)0x00000008)

//
//! Bus Fault Active
//
#define NVIC_SHCSR_BUS_FAULT_ACT       ((unsigned long)0x00000002)

//
//! Memory Management Fault Active
//
#define NVIC_SHCSR_MEM_FAULT_ACT       ((unsigned long)0x00000001)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_DEBUG_STAT NVIC Debug State Register(NVIC_DEBUG_STAT)
//! \brief Defines for the bit fields in the NVIC_DEBUG_STAT register.
//! @{
//
//*****************************************************************************

//
//! EDBGRQ asserted
//
#define NVIC_DEBUG_STAT_EXTRNL         ((unsigned long)0x00000010)

//
//! Vector catch
//
#define NVIC_DEBUG_STAT_VCATCH         ((unsigned long)0x00000008)

//
//! DWT match
//
#define NVIC_DEBUG_STAT_DWTTRAP        ((unsigned long)0x00000004)

//
//! Breakpoint instruction
//
#define NVIC_DEBUG_STAT_BKPT           ((unsigned long)0x00000002)

//
//! Halt request
//
#define NVIC_DEBUG_STAT_HALTED         ((unsigned long)0x00000001)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_DEBUG_CTRL NVIC Debug Control Register(NVIC_DBG_CTRL)
//! \brief Defines for the bit fields in the NVIC_DBG_CTRL register.
//! @{
//
//*****************************************************************************

//
//! Debug key mask
//
#define NVIC_DBG_CTRL_DBGKEY_M         ((unsigned long)0xFFFF0000)

//
//! Debug key
//
#define NVIC_DBG_CTRL_DBGKEY           ((unsigned long)0xA05F0000)

//
//! Core has reset since last read
//
#define NVIC_DBG_CTRL_S_RESET_ST       ((unsigned long)0x02000000)

//
//! Core has executed insruction since last read
//
#define NVIC_DBG_CTRL_S_RETIRE_ST      ((unsigned long)0x01000000)

//
//! Core is locked up
//
#define NVIC_DBG_CTRL_S_LOCKUP         ((unsigned long)0x00080000)

//
//! Core is sleeping
//
#define NVIC_DBG_CTRL_S_SLEEP          ((unsigned long)0x00040000)

//
//! Core status on halt
//
#define NVIC_DBG_CTRL_S_HALT           ((unsigned long)0x00020000)

//
//! Register read/write available
//
#define NVIC_DBG_CTRL_S_REGRDY         ((unsigned long)0x00010000)

//
//! Breaks a stalled load/store
//
#define NVIC_DBG_CTRL_C_SNAPSTALL      ((unsigned long)0x00000020)

//
//! Mask interrupts when stepping
//
#define NVIC_DBG_CTRL_C_MASKINT        ((unsigned long)0x00000008)

//
//! Step the core
//
#define NVIC_DBG_CTRL_C_STEP           ((unsigned long)0x00000004)

//
//! Halt the core
//
#define NVIC_DBG_CTRL_C_HALT           ((unsigned long)0x00000002)

//
//! Enable debug
//
#define NVIC_DBG_CTRL_C_DEBUGEN        ((unsigned long)0x00000001)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_DBG_XFER NVIC XFER Register(NVIC_DBG_XFER)
//! \brief Defines for the bit fields in the NVIC_DBG_XFER register.
//! @{
//
//*****************************************************************************

//
//! Write or not read
//
#define NVIC_DBG_XFER_REG_WNR          ((unsigned long)0x00010000)

//
//! Register
//
#define NVIC_DBG_XFER_REG_SEL_M        ((unsigned long)0x0000001F)

//
//! Register R0
//
#define NVIC_DBG_XFER_REG_R0           ((unsigned long)0x00000000)

//
//! Register R1
//
#define NVIC_DBG_XFER_REG_R1           ((unsigned long)0x00000001)

//
//! Register R2
//
#define NVIC_DBG_XFER_REG_R2           ((unsigned long)0x00000002)

//
//! Register R3
//
#define NVIC_DBG_XFER_REG_R3           ((unsigned long)0x00000003)

//
//! Register R4
//
#define NVIC_DBG_XFER_REG_R4           ((unsigned long)0x00000004)

//
//! Register R5
//
#define NVIC_DBG_XFER_REG_R5           ((unsigned long)0x00000005)

//
//! Register R6
//
#define NVIC_DBG_XFER_REG_R6           ((unsigned long)0x00000006)

//
//! Register R7
//
#define NVIC_DBG_XFER_REG_R7           ((unsigned long)0x00000007)

//
//! Register R8
//
#define NVIC_DBG_XFER_REG_R8           ((unsigned long)0x00000008)

//
//! Register R9
//
#define NVIC_DBG_XFER_REG_R9           ((unsigned long)0x00000009)

//
//! Register R10
//
#define NVIC_DBG_XFER_REG_R10          ((unsigned long)0x0000000A)

//
//! Register R11
//
#define NVIC_DBG_XFER_REG_R11          ((unsigned long)0x0000000B)

//
//! Register R12
//
#define NVIC_DBG_XFER_REG_R12          ((unsigned long)0x0000000C)

//
//! Register R13
//
#define NVIC_DBG_XFER_REG_R13          ((unsigned long)0x0000000D)

//
//! Register R14
//
#define NVIC_DBG_XFER_REG_R14          ((unsigned long)0x0000000E)

//
//! Register R15
//
#define NVIC_DBG_XFER_REG_R15          ((unsigned long)0x0000000F)

//
//! xPSR/Flags register
//
#define NVIC_DBG_XFER_REG_FLAGS        ((unsigned long)0x00000010)

//
//! Main SP
//
#define NVIC_DBG_XFER_REG_MSP          ((unsigned long)0x00000011)

//
//! Process SP
//
#define NVIC_DBG_XFER_REG_PSP          ((unsigned long)0x00000012)

//
//! Deep SP
//
#define NVIC_DBG_XFER_REG_DSP          ((unsigned long)0x00000013)

//
//! Control/Fault/BasePri/PriMask
//
#define NVIC_DBG_XFER_REG_CFBP         ((unsigned long)0x00000014)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_DBG_DATA NVIC Debug Data Register       (NVIC_DBG_DATA)
//! \brief Defines for the bit fields in the NVIC_DBG_DATA register.
//! @{
//
//*****************************************************************************

//
//! Data temporary cache
//
#define NVIC_DBG_DATA_M                ((unsigned long)0xFFFFFFFF)
#define NVIC_DBG_DATA_S                0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NVIC_Register_NVIC_DBG_INT NVIC Debug Intrrupt Register(NVIC_DBG_INT)
//! \brief Defines for the bit fields in the NVIC_DBG_INT register.
//! @{
//
//*****************************************************************************

//
//! Debug trap on hard fault
//
#define NVIC_DBG_INT_HARDERR           ((unsigned long)0x00000400)

//
//! Debug trap on interrupt errors
//
#define NVIC_DBG_INT_INTERR            ((unsigned long)0x00000200)

//
//! Debug trap on bus error
//
#define NVIC_DBG_INT_BUSERR            ((unsigned long)0x00000100)

//
//! Debug trap on usage fault state
//
#define NVIC_DBG_INT_STATERR           ((unsigned long)0x00000080)

//
//! Debug trap on usage fault check
//
#define NVIC_DBG_INT_CHKERR            ((unsigned long)0x00000040)

//
//! Debug trap on coprocessor error
//
#define NVIC_DBG_INT_NOCPERR           ((unsigned long)0x00000020)

//
//! Debug trap on mem manage fault
//
#define NVIC_DBG_INT_MMERR             ((unsigned long)0x00000010)

//
//! Core reset status
//
#define NVIC_DBG_INT_RESET             ((unsigned long)0x00000008)

//
//! Clear pending core reset
//
#define NVIC_DBG_INT_RSTPENDCLR        ((unsigned long)0x00000004)

//
//! Core reset is pending
//
#define NVIC_DBG_INT_RSTPENDING        ((unsigned long)0x00000002)

//
//! Reset vector catch
//
#define NVIC_DBG_INT_RSTVCATCH         ((unsigned long)0x00000001)

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

