//*****************************************************************************
//
//! \file xhw_nvic.h
//! \brief Macros used when accessing the NVIC hardware.For M3
//! \version V2.2.1.0
//! \date 2/21/2012
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
//! \addtogroup HT32F175x/275x_NVIC_Register_Address NVIC Address Register(NVIC_Address)
//! \brief Defines for the bit fields in the NVIC_Register_Address register
//! @{
//
//*****************************************************************************
//
//! Interrupt Controller Type Reg
//
#define NVIC_INT_TYPE           0xE000E004

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
//! Interrupt -31 Set Enable
//
#define NVIC_EN0                0xE000E100

//
//! Interrupt 32-63 Set Enable
//
#define NVIC_EN1                0xE000E104

//
//! Interrupt 64-95 Set Enable
//
#define NVIC_EN2                0xE000E108

//
//! Interrupt 0-31 Clear Enable
//
#define NVIC_DIS0               0xE000E180

//
//! Interrupt 32-63 Clear Enable
//
#define NVIC_DIS1               0xE000E184

//
//! Interrupt 64-95 Clear Enable
//
#define NVIC_DIS2               0xE000E188

//
//! Interrupt 0-31 Set Pending
//
#define NVIC_PEND0              0xE000E200

//
//! Interrupt 32-63 Set Pending
//
#define NVIC_PEND1              0xE000E204

//
//! Interrupt 64-95 Set Pending
//
#define NVIC_PEND2              0xE000E208

//
//! Interrupt 0-31 Clear Pending
//
#define NVIC_UNPEND0            0xE000E280

//
//! Interrupt 32-63 Clear Pending
//
#define NVIC_UNPEND1            0xE000E284

//
//! Interrupt 64-95 Clear Pending
//
#define NVIC_UNPEND2            0xE000E288

//
//! IRQ 0-31 Active Bit Register
//
#define IABR0_31                0xE000E300

//
//! IRQ 32-63 Active Bit Register
//
#define IABR32_63               0xE000E304

//
//! IRQ 64-95 Active Bit Register
//
#define IABR64_95               0xE000E308

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
//! Interrupt 64-67 Priority
//
#define NVIC_PRI16              0xE000E440

//
//! CPU ID Base
//
#define NVIC_CPUID              0xE000ED00

//
//! Interrupt Control and State
//
#define NVIC_INT_CTRL           0xE000ED04

//
//! Vector Table Offset Register
//
#define NVIC_VTOR               0xE000ED08

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
//! Configure Fault Status Register
//
#define NVIC_CFSR               0xE000ED28

//
//! Hard Fault Status Register
//
#define NVIC_HFSR               0xE000ED2C

//
//! Debug Status Register
//
#define NVIC_DEBUG_STAT         0xE000ED30

//
//! Mem Fault Status Register
//
#define NVIC_MMFAR              0xE000ED34

//
//! Bus Fault Address Register
//
#define NVIC_BFAR               0xE000ED38

//
//! Auxiliary Fault Status Register
//
#define NVIC_AFSR               0xE000ED3C

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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_INT_TYPE NVIC Interrupt Type Register(NVIC_INT_TYPE)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_ST_CTRL NVIC Status Control Register(NVIC_ST_CTRL)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_ST_RELOAD NVIC Status Reload Register(NVIC_ST_RELOAD)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_ST_CURRENT NVIC Status Current Register(NVIC_ST_CURRENT)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_ST_CAL NVIC Status Cal Register(NVIC_ST_CAL)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_EN0 NVIC Enable0 Register(NVIC_EN0)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_EN1 NVIC Enable1 Register(NVIC_EN1)
//! \brief Defines for the bit fields in the NVIC_EN1 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Enable
//
#define NVIC_EN1_INT_M          0xFFFFFFFF

//
//! Interrupt 32 enable
//
#define NVIC_EN1_INT0           0x00000001

//
//! Interrupt 33 enable
//
#define NVIC_EN1_INT1           0x00000002

//
//! Interrupt 34 enable
//
#define NVIC_EN1_INT2           0x00000004

//
//! Interrupt 35 enable
//
#define NVIC_EN1_INT3           0x00000008

//
//! Interrupt 36 enable
//
#define NVIC_EN1_INT4           0x00000010

//
//! Interrupt 37 enable
//
#define NVIC_EN1_INT5           0x00000020

//
//! Interrupt 38 enable
//
#define NVIC_EN1_INT6           0x00000040

//
//! Interrupt 39 enable
//
#define NVIC_EN1_INT7           0x00000080

//
//! Interrupt 40 enable
//
#define NVIC_EN1_INT8           0x00000100

//
//! Interrupt 41 enable
//
#define NVIC_EN1_INT9           0x00000200

//
//! Interrupt 42 enable
//
#define NVIC_EN1_INT10          0x00000400

//
//! Interrupt 43 enable
//
#define NVIC_EN1_INT11          0x00000800

//
//! Interrupt 44 enable
//
#define NVIC_EN1_INT12          0x00001000

//
//! Interrupt 45 enable
//
#define NVIC_EN1_INT13          0x00002000

//
//! Interrupt 46 enable
//
#define NVIC_EN1_INT14          0x00004000

//
//! Interrupt 47 enable
//
#define NVIC_EN1_INT15          0x00008000

//
//! Interrupt 48 enable
//
#define NVIC_EN1_INT16          0x00010000

//
//! Interrupt 49 enable
//
#define NVIC_EN1_INT17          0x00020000

//
//! Interrupt 50 enable
//
#define NVIC_EN1_INT18          0x00040000

//
//! Interrupt 51 enable
//
#define NVIC_EN1_INT19          0x00080000

//
//! Interrupt 52 enable
//
#define NVIC_EN1_INT20          0x00100000

//
//! Interrupt 53 enable
//
#define NVIC_EN1_INT21          0x00200000

//
//! Interrupt 54 enable
//
#define NVIC_EN1_INT22          0x00400000

//
//! Interrupt 55 enable
//
#define NVIC_EN1_INT23          0x00800000

//
//! Interrupt 56 enable
//
#define NVIC_EN1_INT24          0x01000000

//
//! Interrupt 57 enable
//
#define NVIC_EN1_INT25          0x02000000
//
//! Interrupt 58 enable
//
#define NVIC_EN1_INT26          0x04000000

//
//! Interrupt 59 enable
//
#define NVIC_EN1_INT27          0x08000000

//
//! Interrupt 60 enable
//
#define NVIC_EN1_INT28          0x10000000
//
//! Interrupt 61 enable
//
#define NVIC_EN1_INT29          0x20000000

//
//! Interrupt 62 enable
//
#define NVIC_EN1_INT30          0x40000000

//
//! Interrupt 63 enable
//
#define NVIC_EN1_INT31          0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_EN2 NVIC Enable1 Register(NVIC_EN2)
//! \brief Defines for the bit fields in the NVIC_EN2 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Enable
//
#define NVIC_EN2_INT_M          0xFFFFFFFF

//
//! Interrupt 64 enable
//
#define NVIC_EN2_INT0           0x00000001

//
//! Interrupt 65 enable
//
#define NVIC_EN2_INT1           0x00000002

//
//! Interrupt 66 enable
//
#define NVIC_EN2_INT2           0x00000004

//
//! Interrupt 67 enable
//
#define NVIC_EN2_INT3           0x00000008

//
//! Interrupt 68 enable
//
#define NVIC_EN2_INT4           0x00000010

//
//! Interrupt 69 enable
//
#define NVIC_EN2_INT5           0x00000020

//
//! Interrupt 70 enable
//
#define NVIC_EN2_INT6           0x00000040

//
//! Interrupt 71 enable
//
#define NVIC_EN2_INT7           0x00000080

//
//! Interrupt 72 enable
//
#define NVIC_EN2_INT8           0x00000100

//
//! Interrupt 73 enable
//
#define NVIC_EN2_INT9           0x00000200

//
//! Interrupt 74 enable
//
#define NVIC_EN2_INT10          0x00000400

//
//! Interrupt 75 enable
//
#define NVIC_EN2_INT11          0x00000800

//
//! Interrupt 76 enable
//
#define NVIC_EN2_INT12          0x00001000

//
//! Interrupt 77 enable
//
#define NVIC_EN2_INT13          0x00002000

//
//! Interrupt 78 enable
//
#define NVIC_EN2_INT14          0x00004000

//
//! Interrupt 79 enable
//
#define NVIC_EN2_INT15          0x00008000

//
//! Interrupt 80 enable
//
#define NVIC_EN2_INT16          0x00010000

//
//! Interrupt 81 enable
//
#define NVIC_EN2_INT17          0x00020000

//
//! Interrupt 82 enable
//
#define NVIC_EN2_INT18          0x00040000

//
//! Interrupt 83 enable
//
#define NVIC_EN2_INT19          0x00080000

//
//! Interrupt 84 enable
//
#define NVIC_EN2_INT20          0x00100000

//
//! Interrupt 85 enable
//
#define NVIC_EN2_INT21          0x00200000

//
//! Interrupt 86 enable
//
#define NVIC_EN2_INT22          0x00400000

//
//! Interrupt 87 enable
//
#define NVIC_EN2_INT23          0x00800000

//
//! Interrupt 88 enable
//
#define NVIC_EN2_INT24          0x01000000

//
//! Interrupt 89 enable
//
#define NVIC_EN2_INT25          0x02000000
//
//! Interrupt 90 enable
//
#define NVIC_EN2_INT26          0x04000000

//
//! Interrupt 91 enable
//
#define NVIC_EN2_INT27          0x08000000

//
//! Interrupt 92 enable
//
#define NVIC_EN2_INT28          0x10000000
//
//! Interrupt 93 enable
//
#define NVIC_EN2_INT29          0x20000000

//
//! Interrupt 94 enable
//
#define NVIC_EN2_INT30          0x40000000

//
//! Interrupt 95 enable
//
#define NVIC_EN2_INT31          0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_DIS0 NVIC Disable0 Register(NVIC_DIS0)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_DIS1 NVIC Disable1 Register(NVIC_DIS1)
//! \brief Defines for the bit fields in the NVIC_DIS1 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Disable
//
#define NVIC_DIS1_INT_M         0xFFFFFFFF

//
//! Interrupt 32 disable
//
#define NVIC_DIS1_INT0          0x00000001

//
//! Interrupt 33 disable
//
#define NVIC_DIS1_INT1          0x00000002

//
//! Interrupt 34 disable
//
#define NVIC_DIS1_INT2          0x00000004

//
//! Interrupt 35 disable
//
#define NVIC_DIS1_INT3          0x00000008

//
//! Interrupt 36 disable
//
#define NVIC_DIS1_INT4          0x00000010

//
//! Interrupt 37 disable
//
#define NVIC_DIS1_INT5          0x00000020

//
//! Interrupt 38 disable
//
#define NVIC_DIS1_INT6          0x00000040

//
//! Interrupt 39 disable
//
#define NVIC_DIS1_INT7          0x00000080

//
//! Interrupt 40 disable
//
#define NVIC_DIS1_INT8          0x00000100

//
//! Interrupt 41 disable
//
#define NVIC_DIS1_INT9          0x00000200

//
//! Interrupt 42 disable
//
#define NVIC_DIS1_INT10         0x00000400

//
//! Interrupt 43 disable
//
#define NVIC_DIS1_INT11         0x00000800

//
//! Interrupt 44 disable
//
#define NVIC_DIS1_INT12         0x00001000

//
//! Interrupt 45 disable
//
#define NVIC_DIS1_INT13         0x00002000

//
//! Interrupt 46 disable
//
#define NVIC_DIS1_INT14         0x00004000

//
//! Interrupt 47 disable
//
#define NVIC_DIS1_INT15         0x00008000  

//
//! Interrupt 48 disable
//
#define NVIC_DIS1_INT16         0x00010000  

//
//! Interrupt 49 disable
//
#define NVIC_DIS1_INT17         0x00020000  

//
//! Interrupt 50 disable
//
#define NVIC_DIS1_INT18         0x00040000  

//
//! Interrupt 51 disable
//
#define NVIC_DIS1_INT19         0x00080000 

//
//! Interrupt 52 disable
//
#define NVIC_DIS1_INT20         0x00100000  

//
//! Interrupt 53 disable
//
#define NVIC_DIS1_INT21         0x00200000  

//
//! Interrupt 54 disable
//
#define NVIC_DIS1_INT22         0x00400000  

//
//! Interrupt 55 disable
//
#define NVIC_DIS1_INT23         0x00800000  

//
//! Interrupt 56 disable
//
#define NVIC_DIS1_INT24         0x01000000  

//
//! Interrupt 57 disable
//
#define NVIC_DIS1_INT25         0x02000000  

//
//! Interrupt 58 disable
//
#define NVIC_DIS1_INT26         0x04000000  

//
//! Interrupt 59 disable
//
#define NVIC_DIS1_INT27         0x08000000  

//
//! Interrupt 60 disable
//
#define NVIC_DIS1_INT28         0x10000000

//
//! Interrupt 61 disable
//
#define NVIC_DIS1_INT29         0x20000000

//
//! Interrupt 62 disable
//
#define NVIC_DIS1_INT30         0x40000000  

//
//! Interrupt 63 disable
//
#define NVIC_DIS1_INT31         0x80000000 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_DIS2 NVIC Disable1 Register(NVIC_DIS2)
//! \brief Defines for the bit fields in the NVIC_DIS2 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Disable
//
#define NVIC_DIS2_INT_M         0xFFFFFFFF

//
//! Interrupt 64 disable
//
#define NVIC_DIS2_INT0          0x00000001

//
//! Interrupt 65 disable
//
#define NVIC_DIS2_INT1          0x00000002

//
//! Interrupt 66 disable
//
#define NVIC_DIS2_INT2          0x00000004

//
//! Interrupt 67 disable
//
#define NVIC_DIS2_INT3          0x00000008

//
//! Interrupt 68 disable
//
#define NVIC_DIS2_INT4          0x00000010

//
//! Interrupt 69 disable
//
#define NVIC_DIS2_INT5          0x00000020

//
//! Interrupt 70 disable
//
#define NVIC_DIS2_INT6          0x00000040

//
//! Interrupt 71 disable
//
#define NVIC_DIS2_INT7          0x00000080

//
//! Interrupt 72 disable
//
#define NVIC_DIS2_INT8          0x00000100

//
//! Interrupt 73 disable
//
#define NVIC_DIS2_INT9          0x00000200

//
//! Interrupt 74 disable
//
#define NVIC_DIS2_INT10         0x00000400

//
//! Interrupt 75 disable
//
#define NVIC_DIS2_INT11         0x00000800

//
//! Interrupt 76 disable
//
#define NVIC_DIS2_INT12         0x00001000

//
//! Interrupt 77 disable
//
#define NVIC_DIS2_INT13         0x00002000

//
//! Interrupt 78 disable
//
#define NVIC_DIS2_INT14         0x00004000

//
//! Interrupt 79 disable
//
#define NVIC_DIS2_INT15         0x00008000  

//
//! Interrupt 80 disable
//
#define NVIC_DIS2_INT16         0x00010000  

//
//! Interrupt 81 disable
//
#define NVIC_DIS2_INT17         0x00020000  

//
//! Interrupt 82 disable
//
#define NVIC_DIS2_INT18         0x00040000  

//
//! Interrupt 83 disable
//
#define NVIC_DIS2_INT19         0x00080000 

//
//! Interrupt 84 disable
//
#define NVIC_DIS2_INT20         0x00100000  

//
//! Interrupt 85 disable
//
#define NVIC_DIS2_INT21         0x00200000  

//
//! Interrupt 86 disable
//
#define NVIC_DIS2_INT22         0x00400000  

//
//! Interrupt 87 disable
//
#define NVIC_DIS2_INT23         0x00800000  

//
//! Interrupt 88 disable
//
#define NVIC_DIS2_INT24         0x01000000  

//
//! Interrupt 89 disable
//
#define NVIC_DIS2_INT25         0x02000000  

//
//! Interrupt 90 disable
//
#define NVIC_DIS2_INT26         0x04000000  

//
//! Interrupt 91 disable
//
#define NVIC_DIS2_INT27         0x08000000  

//
//! Interrupt 92 disable
//
#define NVIC_DIS2_INT28         0x10000000

//
//! Interrupt 93 disable
//
#define NVIC_DIS2_INT29         0x20000000

//
//! Interrupt 94 disable
//
#define NVIC_DIS2_INT30         0x40000000  

//
//! Interrupt 95 disable
//
#define NVIC_DIS2_INT31         0x80000000 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PEND0 NVIC PEND 0 Register(NVIC_PEND0)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PEND1 NVIC PEND 1 Register(NVIC_PEND1)
//! \brief Defines for the bit fields in the NVIC_PEND1 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Set Pending
//
#define NVIC_PEND1_INT_M        0xFFFFFFFF

//
//! Interrupt 32 pend
//
#define NVIC_PEND1_INT0         0x00000001

//
//! Interrupt 33 pend
//
#define NVIC_PEND1_INT1         0x00000002

//
//! Interrupt 34 pend
//
#define NVIC_PEND1_INT2         0x00000004  

//
//! Interrupt 35 pend
//
#define NVIC_PEND1_INT3         0x00000008  

//
//! Interrupt 36 pend
//
#define NVIC_PEND1_INT4         0x00000010  

//
//! Interrupt 37 pend
//
#define NVIC_PEND1_INT5         0x00000020

//
//! Interrupt 38 pend
//
#define NVIC_PEND1_INT6         0x00000040

//
//! Interrupt 39 pend
//
#define NVIC_PEND1_INT7         0x00000080

//
//! Interrupt 40 pend
//
#define NVIC_PEND1_INT8         0x00000100  

//
//! Interrupt 41 pend
//
#define NVIC_PEND1_INT9         0x00000200

//
//! Interrupt 42 pend
//
#define NVIC_PEND1_INT10        0x00000400

//
//! Interrupt 43 pend
//
#define NVIC_PEND1_INT11        0x00000800

//
//! Interrupt 44 pend
//
#define NVIC_PEND1_INT12        0x00001000

//
//! Interrupt 45 pend
//
#define NVIC_PEND1_INT13        0x00002000

//
//! Interrupt 46 pend
//
#define NVIC_PEND1_INT14        0x00004000  

//
//! Interrupt 47 pend
//
#define NVIC_PEND1_INT15        0x00008000 

//
//! Interrupt 48 pend
//
#define NVIC_PEND1_INT16        0x00010000  

//
//! Interrupt 49 pend
//
#define NVIC_PEND1_INT17        0x00020000

//
//! Interrupt 50 pend
//
#define NVIC_PEND1_INT18        0x00040000  

//
//! Interrupt 51 pend
//
#define NVIC_PEND1_INT19        0x00080000  

//
//! Interrupt 52 pend
//
#define NVIC_PEND1_INT20        0x00100000  

//
//! Interrupt 53 pend
//
#define NVIC_PEND1_INT21        0x00200000

//
//! Interrupt 54 pend
//
#define NVIC_PEND1_INT22        0x00400000 

//
//! Interrupt 55 pend
//
#define NVIC_PEND1_INT23        0x00800000 

//
//! Interrupt 56 pend
//
#define NVIC_PEND1_INT24        0x01000000  

//
//! Interrupt 57 pend
//
#define NVIC_PEND1_INT25        0x02000000  

//
//! Interrupt 58 pend
//
#define NVIC_PEND1_INT26        0x04000000

//
//! Interrupt 59 pend
//
#define NVIC_PEND1_INT27        0x08000000

//
//! Interrupt 60 pend
//
#define NVIC_PEND1_INT28        0x10000000

//
//! Interrupt 61 pend
//
#define NVIC_PEND1_INT29        0x20000000

//
//! Interrupt 62 pend
//
#define NVIC_PEND1_INT30        0x40000000  

//
//! Interrupt 63 pend
//
#define NVIC_PEND1_INT31        0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PEND2 NVIC PEND 1 Register(NVIC_PEND2)
//! \brief Defines for the bit fields in the NVIC_PEND2 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Set Pending
//
#define NVIC_PEND2_INT_M        0xFFFFFFFF

//
//! Interrupt 64 pend
//
#define NVIC_PEND2_INT0         0x00000001

//
//! Interrupt 65 pend
//
#define NVIC_PEND2_INT1         0x00000002

//
//! Interrupt 66 pend
//
#define NVIC_PEND2_INT2         0x00000004  

//
//! Interrupt 67 pend
//
#define NVIC_PEND2_INT3         0x00000008  

//
//! Interrupt 68 pend
//
#define NVIC_PEND2_INT4         0x00000010  

//
//! Interrupt 69 pend
//
#define NVIC_PEND2_INT5         0x00000020

//
//! Interrupt 70 pend
//
#define NVIC_PEND2_INT6         0x00000040

//
//! Interrupt 71 pend
//
#define NVIC_PEND2_INT7         0x00000080

//
//! Interrupt 72 pend
//
#define NVIC_PEND2_INT8         0x00000100  

//
//! Interrupt 73 pend
//
#define NVIC_PEND2_INT9         0x00000200

//
//! Interrupt 74 pend
//
#define NVIC_PEND2_INT10        0x00000400

//
//! Interrupt 75 pend
//
#define NVIC_PEND2_INT11        0x00000800

//
//! Interrupt 76 pend
//
#define NVIC_PEND2_INT12        0x00001000

//
//! Interrupt 77 pend
//
#define NVIC_PEND2_INT13        0x00002000

//
//! Interrupt 78 pend
//
#define NVIC_PEND2_INT14        0x00004000  

//
//! Interrupt 79 pend
//
#define NVIC_PEND2_INT15        0x00008000 

//
//! Interrupt 80 pend
//
#define NVIC_PEND2_INT16        0x00010000  

//
//! Interrupt 81 pend
//
#define NVIC_PEND2_INT17        0x00020000

//
//! Interrupt 82 pend
//
#define NVIC_PEND2_INT18        0x00040000  

//
//! Interrupt 83 pend
//
#define NVIC_PEND2_INT19        0x00080000  

//
//! Interrupt 84 pend
//
#define NVIC_PEND2_INT20        0x00100000  

//
//! Interrupt 85 pend
//
#define NVIC_PEND2_INT21        0x00200000

//
//! Interrupt 86 pend
//
#define NVIC_PEND2_INT22        0x00400000 

//
//! Interrupt 87 pend
//
#define NVIC_PEND2_INT23        0x00800000 

//
//! Interrupt 88 pend
//
#define NVIC_PEND2_INT24        0x01000000  

//
//! Interrupt 89 pend
//
#define NVIC_PEND2_INT25        0x02000000  

//
//! Interrupt 90 pend
//
#define NVIC_PEND2_INT26        0x04000000

//
//! Interrupt 91 pend
//
#define NVIC_PEND2_INT27        0x08000000

//
//! Interrupt 92 pend
//
#define NVIC_PEND2_INT28        0x10000000

//
//! Interrupt 93 pend
//
#define NVIC_PEND2_INT29        0x20000000

//
//! Interrupt 94 pend
//
#define NVIC_PEND2_INT30        0x40000000  

//
//! Interrupt 95 pend
//
#define NVIC_PEND2_INT31        0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_UNPEND0 NVIC UNPEND 0 Register(NVIC_UNPEND0)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_UNPEND1 NVIC UNPEND 1 Register(NVIC_UNPEND1)
//! \brief Defines for the bit fields in the NVIC_UNPEND1 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Clear Pending
//
#define NVIC_UNPEND1_INT_M      0xFFFFFFFF  

//
//! Interrupt 32 unpend
//
#define NVIC_UNPEND1_INT0       0x00000001  

//
//! Interrupt 33 unpend
//
#define NVIC_UNPEND1_INT1       0x00000002 

//
//! Interrupt 34 unpend
//
#define NVIC_UNPEND1_INT2       0x00000004  

//
//! Interrupt 35 unpend
//
#define NVIC_UNPEND1_INT3       0x00000008  

//
//! Interrupt 36 unpend
//
#define NVIC_UNPEND1_INT4       0x00000010  

//
//! Interrupt 37 unpend
//
#define NVIC_UNPEND1_INT5       0x00000020  

//
//! Interrupt 38 unpend
//
#define NVIC_UNPEND1_INT6       0x00000040  

//
//! Interrupt 39 unpend
//
#define NVIC_UNPEND1_INT7       0x00000080  

//
//! Interrupt 40 unpend
//
#define NVIC_UNPEND1_INT8       0x00000100  
//
//! Interrupt 41 unpend
//
#define NVIC_UNPEND1_INT9       0x00000200  

//
//! Interrupt 42 unpend
//
#define NVIC_UNPEND1_INT10      0x00000400  

//
//! Interrupt 43 unpend
//
#define NVIC_UNPEND1_INT11      0x00000800  

//
//! Interrupt 44 unpend
//
#define NVIC_UNPEND1_INT12      0x00001000  

//
//! Interrupt 45 unpend
//
#define NVIC_UNPEND1_INT13      0x00002000  

//
//! Interrupt 46 unpend
//
#define NVIC_UNPEND1_INT14      0x00004000  

//
//! Interrupt 47 unpend
//
#define NVIC_UNPEND1_INT15      0x00008000  

//
//! Interrupt 48 unpend
//
#define NVIC_UNPEND1_INT16      0x00010000  

//
//! Interrupt 49 unpend
//
#define NVIC_UNPEND1_INT17      0x00020000  

//
//! Interrupt 50 unpend
//
#define NVIC_UNPEND1_INT18      0x00040000  

//
//! Interrupt 51 unpend
//
#define NVIC_UNPEND1_INT19      0x00080000  

//
//! Interrupt 52 unpend
//
#define NVIC_UNPEND1_INT20      0x00100000  

//
//! Interrupt 53 unpend
//
#define NVIC_UNPEND1_INT21      0x00200000  

//
//! Interrupt 54 unpend
//
#define NVIC_UNPEND1_INT22      0x00400000  

//
//! Interrupt 55 unpend
//
#define NVIC_UNPEND1_INT23      0x00800000  

//
//! Interrupt 56 unpend
//
#define NVIC_UNPEND1_INT24      0x01000000  

//
//! Interrupt 57 unpend
//
#define NVIC_UNPEND1_INT25      0x02000000  

//
//! Interrupt 58 unpend
//
#define NVIC_UNPEND1_INT26      0x04000000  

//
//! Interrupt 59 unpend
//
#define NVIC_UNPEND1_INT27      0x08000000  

//
//! Interrupt 60 unpend
//
#define NVIC_UNPEND1_INT28      0x10000000  

//
//! Interrupt 61 unpend
//
#define NVIC_UNPEND1_INT29      0x20000000  

//
//! Interrupt 62 unpend
//
#define NVIC_UNPEND1_INT30      0x40000000  

//
//! Interrupt 63 unpend
//
#define NVIC_UNPEND1_INT31      0x80000000 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_UNPEND2 NVIC UNPEND 1 Register(NVIC_UNPEND2)
//! \brief Defines for the bit fields in the NVIC_UNPEND2 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt Clear Pending
//
#define NVIC_UNPEND2_INT_M      0xFFFFFFFF  

//
//! Interrupt 64 unpend
//
#define NVIC_UNPEND2_INT0       0x00000001  

//
//! Interrupt 65 unpend
//
#define NVIC_UNPEND2_INT1       0x00000002 

//
//! Interrupt 66 unpend
//
#define NVIC_UNPEND2_INT2       0x00000004  

//
//! Interrupt 67 unpend
//
#define NVIC_UNPEND2_INT3       0x00000008  

//
//! Interrupt 68 unpend
//
#define NVIC_UNPEND2_INT4       0x00000010  

//
//! Interrupt 69 unpend
//
#define NVIC_UNPEND2_INT5       0x00000020  

//
//! Interrupt 70 unpend
//
#define NVIC_UNPEND2_INT6       0x00000040  

//
//! Interrupt 71 unpend
//
#define NVIC_UNPEND2_INT7       0x00000080  

//
//! Interrupt 72 unpend
//
#define NVIC_UNPEND2_INT8       0x00000100  
//
//! Interrupt 73 unpend
//
#define NVIC_UNPEND2_INT9       0x00000200  

//
//! Interrupt 74 unpend
//
#define NVIC_UNPEND2_INT10      0x00000400  

//
//! Interrupt 75 unpend
//
#define NVIC_UNPEND2_INT11      0x00000800  

//
//! Interrupt 76 unpend
//
#define NVIC_UNPEND2_INT12      0x00001000  

//
//! Interrupt 77 unpend
//
#define NVIC_UNPEND2_INT13      0x00002000  

//
//! Interrupt 78 unpend
//
#define NVIC_UNPEND2_INT14      0x00004000  

//
//! Interrupt 79 unpend
//
#define NVIC_UNPEND2_INT15      0x00008000  

//
//! Interrupt 80 unpend
//
#define NVIC_UNPEND2_INT16      0x00010000  

//
//! Interrupt 81 unpend
//
#define NVIC_UNPEND2_INT17      0x00020000  

//
//! Interrupt 82 unpend
//
#define NVIC_UNPEND2_INT18      0x00040000  

//
//! Interrupt 83 unpend
//
#define NVIC_UNPEND2_INT19      0x00080000  

//
//! Interrupt 84 unpend
//
#define NVIC_UNPEND2_INT20      0x00100000  

//
//! Interrupt 85 unpend
//
#define NVIC_UNPEND2_INT21      0x00200000  

//
//! Interrupt 86 unpend
//
#define NVIC_UNPEND2_INT22      0x00400000  

//
//! Interrupt 87 unpend
//
#define NVIC_UNPEND2_INT23      0x00800000  

//
//! Interrupt 88 unpend
//
#define NVIC_UNPEND2_INT24      0x01000000  

//
//! Interrupt 89 unpend
//
#define NVIC_UNPEND2_INT25      0x02000000  

//
//! Interrupt 90 unpend
//
#define NVIC_UNPEND2_INT26      0x04000000  

//
//! Interrupt 91 unpend
//
#define NVIC_UNPEND2_INT27      0x08000000  

//
//! Interrupt 92 unpend
//
#define NVIC_UNPEND2_INT28      0x10000000  

//
//! Interrupt 93 unpend
//
#define NVIC_UNPEND2_INT29      0x20000000  

//
//! Interrupt 94 unpend
//
#define NVIC_UNPEND2_INT30      0x40000000  

//
//! Interrupt 95 unpend
//
#define NVIC_UNPEND2_INT31      0x80000000 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI0 NVIC Priority 0 Register(NVIC_PRI0)
//! \brief Defines for the bit fields in the NVIC_PRI0 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 3 Priority Mask
//
#define NVIC_PRI0_INT3_M        0xF0000000  

//
//! Interrupt 2 Priority Mask
//
#define NVIC_PRI0_INT2_M        0x00F00000  

//
//! Interrupt 1 Priority Mask
//
#define NVIC_PRI0_INT1_M        0x0000F000  

//
//! Interrupt 0 Priority Mask
//
#define NVIC_PRI0_INT0_M        0x000000F0  
#define NVIC_PRI0_INT3_S        28
#define NVIC_PRI0_INT2_S        20
#define NVIC_PRI0_INT1_S        12
#define NVIC_PRI0_INT0_S        4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI1 NVIC Priority 1 Register(NVIC_PRI1)
//! \brief Defines for the bit fields in the NVIC_PRI1 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 7 Priority Mask
//
#define NVIC_PRI1_INT7_M        0xF0000000  

//
//! Interrupt 6 Priority Mask
//
#define NVIC_PRI1_INT6_M        0x00F00000  

//
//! Interrupt 5 Priority Mask
//
#define NVIC_PRI1_INT5_M        0x0000F000 

//
//! Interrupt 4 Priority Mask
//
#define NVIC_PRI1_INT4_M        0x000000F0  
#define NVIC_PRI1_INT7_S        28
#define NVIC_PRI1_INT6_S        20
#define NVIC_PRI1_INT5_S        12
#define NVIC_PRI1_INT4_S        4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI2 NVIC Priority 2 Register(NVIC_PRI2)
//! \brief Defines for the bit fields in the NVIC_PRI2 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 11 Priority Mask
//
#define NVIC_PRI2_INT11_M       0xF0000000  

//
//! Interrupt 10 Priority Mask
//
#define NVIC_PRI2_INT10_M       0x00F00000  

//
//! Interrupt 9 Priority Mask
//
#define NVIC_PRI2_INT9_M        0x0000F000  

//
//! Interrupt 8 Priority Mask
//
#define NVIC_PRI2_INT8_M        0x000000F0  
#define NVIC_PRI2_INT11_S       28
#define NVIC_PRI2_INT10_S       20
#define NVIC_PRI2_INT9_S        12
#define NVIC_PRI2_INT8_S        4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI3 NVIC Priority 3 Register(NVIC_PRI3)
//! \brief Defines for the bit fields in the NVIC_PRI3 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 15 Priority Mask
//
#define NVIC_PRI3_INT15_M       0xF0000000  

//
//! Interrupt 14 Priority Mask
//
#define NVIC_PRI3_INT14_M       0x00F00000  

//
//! Interrupt 13 Priority Mask
//
#define NVIC_PRI3_INT13_M       0x0000F000  

//
//! Interrupt 12 Priority Mask
//
#define NVIC_PRI3_INT12_M       0x000000F0  
#define NVIC_PRI3_INT15_S       28
#define NVIC_PRI3_INT14_S       20
#define NVIC_PRI3_INT13_S       12
#define NVIC_PRI3_INT12_S       4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI4 NVIC Priority 4 Register(NVIC_PRI4)
//! \brief Defines for the bit fields in the NVIC_PRI4 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 19 Priority Mask
//
#define NVIC_PRI4_INT19_M       0xF0000000  

//
//! Interrupt 18 Priority Mask
//
#define NVIC_PRI4_INT18_M       0x00F00000  

//
//! Interrupt 17 Priority Mask
//
#define NVIC_PRI4_INT17_M       0x0000F000  

//
//! Interrupt 16 Priority Mask
//
#define NVIC_PRI4_INT16_M       0x000000F0  
#define NVIC_PRI4_INT19_S       28
#define NVIC_PRI4_INT18_S       20
#define NVIC_PRI4_INT17_S       12
#define NVIC_PRI4_INT16_S       4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI5 NVIC Priority 5 Register(NVIC_PRI5)
//! \brief Defines for the bit fields in the NVIC_PRI5 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 23 Priority Mask
//
#define NVIC_PRI5_INT23_M       0xF0000000  

//
//! Interrupt 22 Priority Mask
//
#define NVIC_PRI5_INT22_M       0x00F00000  

//
//! Interrupt 21 Priority Mask
//
#define NVIC_PRI5_INT21_M       0x0000F000  

//
//! Interrupt 20 Priority Mask
//
#define NVIC_PRI5_INT20_M       0x000000F0  
#define NVIC_PRI5_INT23_S       28
#define NVIC_PRI5_INT22_S       20
#define NVIC_PRI5_INT21_S       12
#define NVIC_PRI5_INT20_S       4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI6 NVIC Priority 6 Register(NVIC_PRI6)
//! \brief Defines for the bit fields in the NVIC_PRI6 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 27 Priority Mask
//
#define NVIC_PRI6_INT27_M       0xF0000000  

//
//! Interrupt 26 Priority Mask
//
#define NVIC_PRI6_INT26_M       0x00F00000  

//
//! Interrupt 25 Priority Mask
//
#define NVIC_PRI6_INT25_M       0x0000F000 

//
//! Interrupt 24 Priority Mask
//
#define NVIC_PRI6_INT24_M       0x000000F0  
#define NVIC_PRI6_INT27_S       28
#define NVIC_PRI6_INT26_S       20
#define NVIC_PRI6_INT25_S       12
#define NVIC_PRI6_INT24_S       4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI7 NVIC Priority 7 Register(NVIC_PRI7)
//! \brief Defines for the bit fields in the NVIC_PRI7 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 31 Priority Mask
//
#define NVIC_PRI7_INT31_M       0xF0000000

//
//! Interrupt 30 Priority Mask
//
#define NVIC_PRI7_INT30_M       0x00F00000

//
//! Interrupt 29 Priority Mask
//
#define NVIC_PRI7_INT29_M       0x0000F000

//
//! Interrupt 28 Priority Mask
//
#define NVIC_PRI7_INT28_M       0x000000F0
#define NVIC_PRI7_INT31_S       28
#define NVIC_PRI7_INT30_S       20
#define NVIC_PRI7_INT29_S       12
#define NVIC_PRI7_INT28_S       4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI8 NVIC Priority 8 Register(NVIC_PRI8)
//! \brief Defines for the bit fields in the NVIC_PRI8 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 35 Priority Mask
//
#define NVIC_PRI8_INT35_M       0xF0000000

//
//! Interrupt 34 Priority Mask
//
#define NVIC_PRI8_INT34_M       0x00F00000

//
//! Interrupt 33 Priority Mask
//
#define NVIC_PRI8_INT33_M       0x0000F000

//
//! Interrupt 32 Priority Mask
//
#define NVIC_PRI8_INT32_M       0x000000F0
#define NVIC_PRI8_INT35_S       28
#define NVIC_PRI8_INT34_S       20
#define NVIC_PRI8_INT33_S       12
#define NVIC_PRI8_INT32_S       4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI9 NVIC Priority 9 Register(NVIC_PRI9)
//! \brief Defines for the bit fields in the NVIC_PRI9 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 39 Priority Mask
//
#define NVIC_PRI9_INT39_M       0xF0000000

//
//! Interrupt 38 Priority Mask
//
#define NVIC_PRI9_INT38_M       0x00F00000

//
//! Interrupt 37 Priority Mask
//
#define NVIC_PRI9_INT37_M       0x0000F000

//
//! Interrupt 36 Priority Mask
//
#define NVIC_PRI9_INT36_M       0x000000F0
#define NVIC_PRI9_INT39_S       28
#define NVIC_PRI9_INT38_S       20
#define NVIC_PRI9_INT37_S       12
#define NVIC_PRI9_INT36_S       4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI10 NVIC Priority 10 Register(NVIC_PRI10)
//! \brief Defines for the bit fields in the NVIC_PRI10 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 43 Priority Mask
//
#define NVIC_PRI10_INT43_M       0xF0000000

//
//! Interrupt 42 Priority Mask
//
#define NVIC_PRI10_INT42_M       0x00F00000

//
//! Interrupt 41 Priority Mask
//
#define NVIC_PRI10_INT41_M       0x0000F000

//
//! Interrupt 40 Priority Mask
//
#define NVIC_PRI10_INT40_M       0x000000F0
#define NVIC_PRI10_INT43_S       28
#define NVIC_PRI10_INT42_S       20
#define NVIC_PRI10_INT41_S       12
#define NVIC_PRI10_INT40_S       4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI11 NVIC Priority 11 Register(NVIC_PRI11)
//! \brief Defines for the bit fields in the NVIC_PRI11 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 47 Priority Mask
//
#define NVIC_PRI11_INT47_M       0xF0000000

//
//! Interrupt 46 Priority Mask
//
#define NVIC_PRI11_INT46_M       0x00F00000

//
//! Interrupt 45 Priority Mask
//
#define NVIC_PRI11_INT45_M       0x0000F000

//
//! Interrupt 44 Priority Mask
//
#define NVIC_PRI11_INT44_M       0x000000F0
#define NVIC_PRI11_INT47_S       28
#define NVIC_PRI11_INT46_S       20
#define NVIC_PRI11_INT45_S       12
#define NVIC_PRI11_INT44_S       4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI12 NVIC Priority 12 Register(NVIC_PRI12)
//! \brief Defines for the bit fields in the NVIC_PRI12 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 51 Priority Mask
//
#define NVIC_PRI12_INT51_M       0xF0000000

//
//! Interrupt 50 Priority Mask
//
#define NVIC_PRI12_INT50_M       0x00F00000

//
//! Interrupt 49 Priority Mask
//
#define NVIC_PRI12_INT49_M       0x0000F000

//
//! Interrupt 48 Priority Mask
//
#define NVIC_PRI12_INT48_M       0x000000F0
#define NVIC_PRI12_INT51_S       28
#define NVIC_PRI12_INT50_S       20
#define NVIC_PRI12_INT49_S       12
#define NVIC_PRI12_INT48_S       4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI13 NVIC Priority 13 Register(NVIC_PRI13)
//! \brief Defines for the bit fields in the NVIC_PRI13 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 55 Priority Mask
//
#define NVIC_PRI13_INT55_M       0xF0000000

//
//! Interrupt 54 Priority Mask
//
#define NVIC_PRI13_INT54_M       0x00F00000

//
//! Interrupt 53 Priority Mask
//
#define NVIC_PRI13_INT53_M       0x0000F000

//
//! Interrupt 52 Priority Mask
//
#define NVIC_PRI13_INT52_M       0x000000F0
#define NVIC_PRI13_INT55_S       28
#define NVIC_PRI13_INT54_S       20
#define NVIC_PRI13_INT53_S       12
#define NVIC_PRI13_INT52_S       4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI14 NVIC Priority 14 Register(NVIC_PRI14)
//! \brief Defines for the bit fields in the NVIC_PRI14 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 59 Priority Mask
//
#define NVIC_PRI14_INT59_M       0xF0000000

//
//! Interrupt 58 Priority Mask
//
#define NVIC_PRI14_INT58_M       0x00F00000

//
//! Interrupt 57 Priority Mask
//
#define NVIC_PRI14_INT57_M       0x0000F000

//
//! Interrupt 56 Priority Mask
//
#define NVIC_PRI14_INT56_M       0x000000F0
#define NVIC_PRI14_INT59_S       28
#define NVIC_PRI14_INT58_S       20
#define NVIC_PRI14_INT57_S       12
#define NVIC_PRI14_INT56_S       4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI15 NVIC Priority 15 Register(NVIC_PRI15)
//! \brief Defines for the bit fields in the NVIC_PRI15 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 63 Priority Mask
//
#define NVIC_PRI15_INT63_M       0xF0000000

//
//! Interrupt 62 Priority Mask
//
#define NVIC_PRI15_INT62_M       0x00F00000

//
//! Interrupt 61 Priority Mask
//
#define NVIC_PRI15_INT61_M       0x0000F000

//
//! Interrupt 60 Priority Mask
//
#define NVIC_PRI15_INT60_M       0x000000F0
#define NVIC_PRI15_INT63_S       28
#define NVIC_PRI15_INT62_S       20
#define NVIC_PRI15_INT61_S       12
#define NVIC_PRI15_INT60_S       4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_PRI16 NVIC Priority 16 Register(NVIC_PRI16)
//! \brief Defines for the bit fields in the NVIC_PRI16 register.
//! @{
//
//*****************************************************************************

//
//! Interrupt 67 Priority Mask
//
#define NVIC_PRI16_INT67_M       0xF0000000

//
//! Interrupt 66 Priority Mask
//
#define NVIC_PRI16_INT66_M       0x00F00000

//
//! Interrupt 65 Priority Mask
//
#define NVIC_PRI16_INT65_M       0x0000F000

//
//! Interrupt 64 Priority Mask
//
#define NVIC_PRI16_INT64_M       0x000000F0																								   x
#define NVIC_PRI16_INT67_S       28
#define NVIC_PRI16_INT66_S       20
#define NVIC_PRI16_INT65_S       12
#define NVIC_PRI16_INT64_S       4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_CPUID  NVIC CPUID Register(NVIC_CPUID)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_INT_CTRL NVIC Interrupt Control
//!  Register(NVIC_INT_CTRL)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_APINT NVIC APINT Register(NVIC_APINT)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_SYS_CTRL NVIC System Control 
//! Register(NVIC_SYS_CTRL)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_CFG_CTRL NVIC Cfg Control 
//! Register(NVIC_CFG_CTRL)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_SYS_PRI1 NVIC System Priority
//!  1 Register(NVIC_SYS_PRI1)
//! \brief Defines for the bit fields in the NVIC_SYS_PRI1 register.
//! @{
//
//*****************************************************************************

//
//! Memory Management Priority
//
#define NVIC_SYS_PRI1_MEM_M     0x000000F0

//
//! Bus Fault Priority
//
#define NVIC_SYS_PRI1_BUS_M     0x0000F000

//
//! Usage Fault Priority
//
#define NVIC_SYS_PRI1_USAGE_M   0x00F00000

#define NVIC_SYS_PRI1_MEM_S     4
#define NVIC_SYS_PRI1_BUS_S     12
#define NVIC_SYS_PRI1_USAGE_S   20

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_SYS_PRI2 NVIC System Priority 
//! 2 Register(NVIC_SYS_PRI2)
//! \brief Defines for the bit fields in the NVIC_SYS_PRI2 register.
//! @{
//
//*****************************************************************************

//
//! SVCall Priority
//
#define NVIC_SYS_PRI2_SVC_M     0xF0000000
#define NVIC_SYS_PRI2_SVC_S     28

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_SYS_PRI3 NVIC System Priority 
//! 3 Register(NVIC_SYS_PRI3)
//! \brief Defines for the bit fields in the NVIC_SYS_PRI3 register.
//! @{
//
//*****************************************************************************

//
//! SysTick Exception Priority
//
#define NVIC_SYS_PRI3_TICK_M    0xF0000000  

//
//! PendSV Priority
//
#define NVIC_SYS_PRI3_PENDSV_M  0x00F00000  

//
//! Debug Priority
//
#define NVIC_SYS_PRI3_DEBUG_M   0x000000F0 
#define NVIC_SYS_PRI3_TICK_S    28
#define NVIC_SYS_PRI3_PENDSV_S  20
#define NVIC_SYS_PRI3_DEBUG_S   4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_SYS_HND_CTRL NVIC HND Control
//!  Register(NVIC_SYS_HND_CTRL)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_DEBUG_STAT NVIC Debug State 
//! Register(NVIC_DEBUG_STAT)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_DEBUG_CTRL NVIC Debug Control 
//! Register(NVIC_DBG_CTRL)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_DBG_XFER NVIC XFER Register(NVIC_DBG_XFER)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_DBG_DATA NVIC Debug Data 
//! Register(NVIC_DBG_DATA)
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
//! \addtogroup HT32F175x/275x_NVIC_Register_NVIC_DBG_INT NVIC Debug Intrrupt Register(NVIC_DBG_INT)
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

