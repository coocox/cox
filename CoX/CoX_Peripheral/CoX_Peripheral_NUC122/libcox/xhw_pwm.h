//*****************************************************************************
//
//! \file xhw_pwm.h
//! \brief Macros and defines used when accessing the PWM hardware.
//! \version V2.1.1.0
//! \date 12/7/2011
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
//****************************************************************************
#ifndef __XHW_PWM_H__
#define __XHW_PWM_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup PWM
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register NUC123 PWM Register
//!
//! it contains:
//! - Register offset.
//! - Detailed bit-field of the registers.
//! - Enum and mask of the registers.
//! .
//! Users can read or write the registers through xHWREG().
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_Address_Offset PWM Register Offset(map)
//! \brief Here is the PWM register offset, users can get the register address
//! through <b>PWM_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! PWM Group A Pre-scale Register
//
#define PWM_PPR                 0x00000000  

//
//! PWM Group A Clock Select Register
//
#define PWM_CSR                 0x00000004  

//
//! PWM Group A Control Register
//
#define PWM_PCR                 0x00000008  

//
//! PWM Group A Counter Register 0
//
#define PWM_CNR0                0x0000000C  

//
//! PWM Group A Comparator Register 0
//
#define PWM_CMR0                0x00000010  

//
//! PWM Group A Data Register 0
//
#define PWM_PDR0                0x00000014  

//
//! PWM Group A Counter Register 1
//
#define PWM_CNR1                0x00000018  

//
//! PWM Group A Comparator Register 1
//
#define PWM_CMR1                0x0000001C  

//
//! PWM Group A Data Register 1
//
#define PWM_PDR1                0x00000020

//
//! PWM Group A Counter Register 2
//
#define PWM_CNR2                0x00000024  

//
//! PWM Group A Comparator Register 2
//
#define PWM_CMR2                0x00000028  

//
//! PWM Group A Data Register 2
//
#define PWM_PDR2                0x0000002C

//
//! PWM Group A Counter Register 3
//
#define PWM_CNR3                0x00000030  

//
//! PWM Group A Comparator Register 3
//
#define PWM_CMR3                0x00000034  

//
//! PWM Group A Data Register 3
//
#define PWM_PDR3                0x00000038

//
//! PWM Group A Interrupt Enable Register
//
#define PWM_PIER                0x00000040  

//
//! PWM Group A Interrupt Indication Register
//
#define PWM_PIIR                0x00000044  

//
//! PWM Group A Capture Control Register 0
//
#define PWM_CCR0                0x00000050  

//
//! PWM Group A Capture Control Register 2
//
#define PWM_CCR2                0x00000054 

//
//! PWM Group A Capture Rising Latch Register (Channel 0)
//
#define PWM_CRLR0               0x00000058  

//
//! PWM Group A Capture Falling Latch Register (Channel 0)
//
#define PWM_CFLR0               0x0000005C  

//
//! PWM Group A Capture Rising Latch Register (Channel 1)
//
#define PWM_CRLR1               0x00000060  

//
//! PWM Group A Capture Falling Latch Register (Channel 1)
//
#define PWM_CFLR1               0x00000064

//
//! PWM Group A Capture Rising Latch Register (Channel 2)
//
#define PWM_CRLR2               0x00000068  

//
//! PWM Group A Capture Falling Latch Register (Channel 2)
//
#define PWM_CFLR2               0x0000006C

//
//! PWM Group A Capture Rising Latch Register (Channel 3)
//
#define PWM_CRLR3               0x00000070  

//
//! PWM Group A Capture Falling Latch Register (Channel 3)
//
#define PWM_CFLR3               0x00000074

//
//! PWM Group A Capture Input 0~3 Enable Register
//
#define PWM_CAPENR              0x00000078

//
//! PWM Group A Output Enable for channel 0~3
//
#define PWM_POE                 0x0000007C

//
//! PWM Group A Trigger Control Register
//
#define PWM_TCON                0x00000080

//
//! PWM Group A Trigger Status Register
//
#define PWM_TSTATUS             0x00000084

//
//! PWM Group A Synchronous Busy Status Register
//
#define PWM_SYNCBUSY0           0x00000088
#define PWM_SYNCBUSY1           0x0000008C
#define PWM_SYNCBUSY2           0x00000090
#define PWM_SYNCBUSY3           0x00000094

//
//! PWM Group A PDMA control register
//
#define PWM_DMACTL              0x000000C0

//
//! PWM Group A channel0-3 data register
//
#define PWM_CAP0PDMA            0x000000C4
#define PWM_CAP1PDMA            0x000000C8
#define PWM_CAP2PDMA            0x000000CC
#define PWM_CAP3PDMA            0x000000D0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_Channel_Address_Offset PWM Channel Address Offset Register
//! @{
//
//*****************************************************************************

//
//! PWM Channel 0 Group A Group offset address
//
#define PWM_CHANNEL_0           0x0000000C

//
//! PWM Channel 1 Group A Group offset address
//
#define PWM_CHANNEL_1           0x00000018

//
//! PWM Channel 2 Group A Group offset address
//
#define PWM_CHANNEL_2           0x00000024

//
//! PWM Channel 3 Group A Group offset address
//
#define PWM_CHANNEL_3           0x00000030

#define PWM_CHANNEL_X_O_CNR     0x00000000
#define PWM_CHANNEL_X_O_CMR     0x00000004
#define PWM_CHANNEL_X_O_PDR     0x00000008

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_PPR PWM Prescaler Register(PWM_PPR)
//! @{
//
//*****************************************************************************

//
//! Clock Prescaler 0 (PWM-timer 0 / 1 for group A and mask
//
#define PWM_PPR_CP01_M          0x000000FF  

//
//! Clock Prescaler 0 (PWM-timer 0 / 1 for group A and shift
//
#define PWM_PPR_CP01_S          0  

//
//! Clock Prescaler 2 (PWM-timer 2 / 3 for group A and mask
//
#define PWM_PPR_CP23_M          0x0000FF00  

//
//! Clock Prescaler 2 (PWM-timer 2 / 3 for group A and shift
//
#define PWM_PPR_CP23_S          8  


//
//! Dead Zone Interval for Pair of Channel 0 and Channel 1 mask
//
#define PWM_PPR_DZI01_M         0x00FF0000

//
//! Dead Zone Interval for Pair of Channel 0 and Channel 1 shift
//
#define PWM_PPR_DZI01_S         16

//
//! Dead Zone Interval for Pair of Channel 2 and Channel 3 mask
//
#define PWM_PPR_DZI23_M         0xFF000000

//
//! Dead Zone Interval for Pair of Channel 2 and Channel 3 shift
//
#define PWM_PPR_DZI23_S         24

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CSR PWM Clock Select Register(PWM_CSR)
//! @{
//
//*****************************************************************************

//
//! PWM Timer 0 Clock Source Selection mask
//
#define PWM_CSR_CSR0_M          0x00000007

//
//! Select clock input for PWM timer.Input clock divided by 2
//
#define PWM_CSR_CSR0_2          0x00000000

//
//! Select clock input for PWM timer.Input clock divided by 4
//
#define PWM_CSR_CSR0_4          0x00000001

//
//! Select clock input for PWM timer.Input clock divided by 8
//
#define PWM_CSR_CSR0_8          0x00000002

//
//! Select clock input for PWM timer.Input clock divided by 16
//
#define PWM_CSR_CSR0_16         0x00000003

//
//! Select clock input for PWM timer.Input clock divided by 1
//
#define PWM_CSR_CSR0_1          0x00000004

//
//! PWM Timer 0 Clock Source Selection shift
//
#define PWM_CSR_CSR0_S          0

//
//! PWM Timer 1 Clock Source Selection mask
//
#define PWM_CSR_CSR1_M          0x00000070

//
//! Select clock input for PWM timer.Input clock divided by 2
//
#define PWM_CSR_CSR1_2          0x00000000

//
//! Select clock input for PWM timer.Input clock divided by 4
//
#define PWM_CSR_CSR1_4          0x00000010

//
//! Select clock input for PWM timer.Input clock divided by 8
//
#define PWM_CSR_CSR1_8          0x00000020

//
//! Select clock input for PWM timer.Input clock divided by 16
//
#define PWM_CSR_CSR1_16         0x00000030

//
//! Select clock input for PWM timer.Input clock divided by 1
//
#define PWM_CSR_CSR1_1          0x00000040

//
//! PWM Timer 1 Clock Source Selection (PWM timer 1 for group A) shift
//
#define PWM_CSR_CSR1_S          4

//
//! PWM Timer 2 Clock Source Selection (PWM timer 2 for group A) mask
//
#define PWM_CSR_CSR2_M          0x00000700

//
//! Select clock input for PWM timer.Input clock divided by 2
//
#define PWM_CSR_CSR2_2          0x00000000

//
//! Select clock input for PWM timer.Input clock divided by 4
//
#define PWM_CSR_CSR2_4          0x00000100

//
//! Select clock input for PWM timer.Input clock divided by 8
//
#define PWM_CSR_CSR2_8          0x00000200

//
//! Select clock input for PWM timer.Input clock divided by 16
//
#define PWM_CSR_CSR2_16         0x00000300

//
//! Select clock input for PWM timer.Input clock divided by 1
//
#define PWM_CSR_CSR2_1          0x00000400

//
//! PWM Timer 2 Clock Source Selection (PWM timer 2 for group A) shift
//
#define PWM_CSR_CSR2_S          8

//
//! PWM Timer 3 Clock Source Selection (PWM timer 3 for group A) mask
//
#define PWM_CSR_CSR3_M          0x00007000

//
//! Select clock input for PWM timer.Input clock divided by 2
//
#define PWM_CSR_CSR3_2          0x00000000

//
//! Select clock input for PWM timer.Input clock divided by 4
//
#define PWM_CSR_CSR3_4          0x00001000

//
//! Select clock input for PWM timer.Input clock divided by 8
//
#define PWM_CSR_CSR3_8          0x00002000

//
//! Select clock input for PWM timer.Input clock divided by 16
//
#define PWM_CSR_CSR3_16         0x00003000

//
//! Select clock input for PWM timer.Input clock divided by 1
//
#define PWM_CSR_CSR3_1          0x00004000

//
//! PWM Timer 3 Clock Source Selection (PWM timer 3 for group A) shift
//
#define PWM_CSR_CSR3_S          12

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_PCR PWM Control Register(PWM_PCR)
//! @{
//
//*****************************************************************************

//
//! PWM-Timer 0 Enable (PWM timer 0 for group A)
//
#define PWM_PCR_CH0EN           0x00000001

//
//! PWM-Timer 0 Output Inverter Enable
//
#define PWM_PCR_CH0INV          0x00000004

//
//! PWM-Timer 0 Auto-reload Mode
//
#define PWM_PCR_CH0MOD          0x00000008

//
//! Dead-Zone 0 Generator Enable
//
#define PWM_PCR_DZEN01          0x00000010

//
//! Dead-Zone 2 Generator Enable
//
#define PWM_PCR_DZEN23          0x00000020

//
//! PWM-Timer 1 Enable (PWM timer 1 for group A)
//
#define PWM_PCR_CH1EN           0x00000100

//
//! PWM-Timer 1 Output Inverter Enable
//
#define PWM_PCR_CH1INV          0x00000400

//
//! PWM-Timer 1 Auto-reload Mode
//
#define PWM_PCR_CH1MOD          0x00000800

//
//! PWM-Timer 2 Enable (PWM timer 2 for group A)
//
#define PWM_PCR_CH2EN           0x00010000

//
//! PWM-Timer 2 Output Inverter Enable
//
#define PWM_PCR_CH2INV          0x00040000

//
//! PWM-Timer 2 Auto-reload Mode
//
#define PWM_PCR_CH2MOD          0x00080000

//
//! PWM-Timer 3 Enable (PWM timer 3 for group A)
//
#define PWM_PCR_CH3EN           0x01000000

//
//! PWM-Timer 3 Output Inverter Enable
//
#define PWM_PCR_CH3INV          0x04000000

//
//! PWM-Timer 3 Auto-reload Mode
//
#define PWM_PCR_CH3MOD          0x08000000

//
//! PWM01 Aligned Type Selection Bit (PWM0 and PWM1 Pair for PWM Group A)
//
#define PWM_PCR_PWMTYPE01       BIT_32_30

//
//! PWM23 Aligned Type Selection Bit (PWM2 and PWM3 Pair for PWM Group A)
//
#define PWM_PCR_PWMTYPE23       BIT_32_31


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CNR0 PWM Counter Register 0(PWM_CNR0)
//! @{
//
//*****************************************************************************

//
//! PWM Timer Loaded Value mask
//
#define PWM_CNR0_CNR0_M         0x0000FFFF

//
//! PWM Timer Loaded Value shift
//
#define PWM_CNR0_CNR0_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CNR1 PWM Counter Register 1(PWM_CNR1)
//! @{
//
//*****************************************************************************

//
//! PWM Timer Loaded Value mask
//
#define PWM_CNR1_CNR1_M         0x0000FFFF

//
//! PWM Timer Loaded Value shift
//
#define PWM_CNR1_CNR1_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CNR2 PWM Counter Register 2(PWM_CNR2)
//! @{
//
//*****************************************************************************

//
//! PWM Timer Loaded Value mask
//
#define PWM_CNR2_CNR2_M         0x0000FFFF

//
//! PWM Timer Loaded Value shift
//
#define PWM_CNR2_CNR2_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CNR3 PWM Counter Register 3(PWM_CNR3)
//! @{
//
//*****************************************************************************

//
//! PWM Timer Loaded Value mask
//
#define PWM_CNR3_CNR3_M         0x0000FFFF

//
//! PWM Timer Loaded Value shift
//
#define PWM_CNR3_CNR3_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CMR0 PWM Comparator Register 0(PWM_CMR0
//! @{
//
//*****************************************************************************

//
//! PWM Comparator Register mask
//
#define PWM_CMR0_CMR0_M         0x0000FFFF

//
//! PWM Comparator Register shift
//
#define PWM_CMR0_CMR0_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CMR1 PWM Comparator Register 1(PWM_CMR1)
//! @{
//
//*****************************************************************************

//
//! PWM Comparator Register mask
//
#define PWM_CMR1_CMR1_M         0x0000FFFF

//
//! PWM Comparator Register shift
//
#define PWM_CMR1_CMR1_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CMR2 PWM Comparator Register 2(PWM_CMR2)
//! @{
//
//*****************************************************************************

//
//! PWM Comparator Register mask
//
#define PWM_CMR2_CMR2_M         0x0000FFFF

//
//! PWM Comparator Register shift
//
#define PWM_CMR2_CMR2_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CMR3 PWM Comparator Register 3 (PWM_CMR3)
//! @{
//
//*****************************************************************************

//
//! PWM Comparator Register mask
//
#define PWM_CMR3_CMR3_M         0x0000FFFF

//
//! PWM Comparator Register shift
//
#define PWM_CMR3_CMR3_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_PDR0 PWM Data Register 0(PWM_PDR0)
//! @{
//
//*****************************************************************************

//
//! PWM Data Register mask
//
#define PWM_PDR0_PDR0_M         0x0000FFFF

//
//! PWM Data Register shift
//
#define PWM_PDR0_PDR0_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_PDR1 PWM Data Register 1(PWM_PDR1)
//! @{
//
//*****************************************************************************

//
//! PWM Data Register mask
//
#define PWM_PDR1_PDR1_M         0x0000FFFF

//
//! PWM Data Register shift
//
#define PWM_PDR1_PDR1_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_PDR2 PWM Data Register 2(PWM_PDR2)
//! @{
//
//*****************************************************************************

//
//! PWM Data Register mask
//
#define PWM_PDR2_PDR2_M         0x0000FFFF

//
//! PWM Data Register shift
//
#define PWM_PDR2_PDR2_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_PDR3 PWM Data Register 3(PWM_PDR3)
//! @{
//
//*****************************************************************************

//
//! PWM Data Register mask
//
#define PWM_PDR3_PDR3_M         0x0000FFFF

//
//! PWM Data Register shift
//
#define PWM_PDR3_PDR3_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_PIER PWM Interrupt Enable Register(PWM_PIER)
//! @{
//
//*****************************************************************************

//
//! PWM channel 0 Interrupt Enable
//
#define PWM_PIER_PWMIE0         0x00000001

//
//! PWM channel 1 Interrupt Enable
//
#define PWM_PIER_PWMIE1         0x00000002

//
//! PWM channel 2 Interrupt Enable
//
#define PWM_PIER_PWMIE2         0x00000004

//
//! PWM channel 3 Interrupt Enable
//
#define PWM_PIER_PWMIE3         0x00000008

//
//! PWM Channel 0 Duty Interrupt Enable
//
#define PWM_PIER_PWMDIE0        BIT_32_8

//
//! PWM Channel 1 Duty Interrupt Enable
//
#define PWM_PIER_PWMDIE1        BIT_32_9

//
//! PWM Channel 2 Duty Interrupt Enable
//
#define PWM_PIER_PWMDIE2        BIT_32_10

//
//! PWM Channel 3 Duty Interrupt Enable
//
#define PWM_PIER_PWMDIE3        BIT_32_11

//
//! PWM01 Interrupt Type Selection Bit (PWM0 and PWM1 Pair for PWM Group A)
//
#define PWM_PIER_INTTYPE01      BIT_32_16

//
//! PWM01 Interrupt Type Selection Bit (PWM2 and PWM3 Pair for PWM Group A)
//
#define PWM_PIER_INTTYPE23      BIT_32_17

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_PIIR PWM Interrupt Indication Register(PWM_PIIR)
//! @{
//
//*****************************************************************************

//
//! PWM channel 0 Interrupt Status
//
#define PWM_PIIR_PWMIF0         0x00000001

//
//! PWM channel 1 Interrupt Status
//
#define PWM_PIIR_PWMIF1         0x00000002

//
//! PWM channel 2 Interrupt Status
//
#define PWM_PIIR_PWMIF2         0x00000004

//
//! PWM channel 3 Interrupt Status
//
#define PWM_PIIR_PWMIF3         0x00000008

//
//! PWM channel 0 Duty Interrupt Flag
//
#define PWM_PIIR_PWMDIF0        BIT_32_8

//
//! PWM channel 1 Duty Interrupt Flag
//
#define PWM_PIIR_PWMDIF1        BIT_32_9

//
//! PWM channel 2 Duty Interrupt Flag
//
#define PWM_PIIR_PWMDIF2        BIT_32_10

//
//! PWM channel 3 Duty Interrupt Flag
//
#define PWM_PIIR_PWMDIF3        BIT_32_11

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CCR0 PWM Capture Control Register 0(PWM_CCR0)
//! @{
//
//*****************************************************************************

//
//! Channel 0 Inverter Enable
//
#define PWM_CCR0_INV0           0x00000001

//
//! Channel 0 Rising Latch Interrupt Enable
//
#define PWM_CCR0_CRL_IE0        0x00000002

//
//! Channel 0 Falling Latch Interrupt Enable
//
#define PWM_CCR0_CFL_IE0        0x00000004

//
//! Channel 0 Capture Function Enable
//
#define PWM_CCR0_CAPCH0EN       0x00000008

//
//! Channel 0 Capture Interrupt Indication Flag
//
#define PWM_CCR0_CAPIF0         0x00000010

//
//! CRLR0 Latched Indicator Bit
//
#define PWM_CCR0_CRLRI0         0x00000040

//
//! CFLR0 Latched Indicator Bit
//
#define PWM_CCR0_CFLRI0         0x00000080

//
//! Channel 1 Inverter Enable
//
#define PWM_CCR0_INV1           0x00010000

//
//! Channel 1 Rising Latch Interrupt Enable
//
#define PWM_CCR0_CRL_IE1        0x00020000

//
//! Channel 1 Falling Latch Interrupt Enable
//
#define PWM_CCR0_CFL_IE1        0x00040000

//
//! Channel 1 Capture Function Enable
//
#define PWM_CCR0_CAPCH1EN       0x00080000

//
//! Channel 1 Capture Interrupt Indication Flag
//
#define PWM_CCR0_CAPIF1         0x00100000

//
//! CRLR1 Latched Indicator Bit
//
#define PWM_CCR0_CRLRI1         0x00400000

//
//! CFLR1 Latched Indicator Bit
//
#define PWM_CCR0_CFLRI1         0x00800000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CCR2 PWM Capture Control Register 2(PWM_CCR2)
//! @{
//
//*****************************************************************************

//
//! Channel 2 Inverter Enable
//
#define PWM_CCR2_INV2           0x00000001

//
//! Channel 2 Rising Latch Interrupt Enable
//
#define PWM_CCR2_CRL_IE2        0x00000002

//
//! Channel 2 Falling Latch Interrupt Enable
//
#define PWM_CCR2_CFL_IE2        0x00000004

//
//! Channel 2 Capture Function Enable
//
#define PWM_CCR2_CAPCH2EN       0x00000008

//
//! Channel 2 Capture Interrupt Indication Flag
//
#define PWM_CCR2_CAPIF2         0x00000010

//
//! CRLR2 Latched Indicator Bit
//
#define PWM_CCR2_CRLRI2         0x00000040

//
//! CFLR2 Latched Indicator Bit
//
#define PWM_CCR2_CFLRI2         0x00000080

//
//! Channel 3 Inverter Enable
//
#define PWM_CCR2_INV3           0x00010000

//
//! Channel 3 Rising Latch Interrupt Enable
//
#define PWM_CCR2_CRL_IE3        0x00020000

//
//! Channel 3 Falling Latch Interrupt Enable
//
#define PWM_CCR2_CFL_IE3        0x00040000

//
//! Channel 3 Capture Function Enable
//
#define PWM_CCR2_CAPCH3EN       0x00080000

//
//! Channel 3 Capture Interrupt Indication Flag
//
#define PWM_CCR2_CAPIF3         0x00100000

//
//! CRLR3 Latched Indicator Bit
//
#define PWM_CCR2_CRLRI3         0x00400000

//
//! CFLR3 Latched Indicator Bit
//
#define PWM_CCR2_CFLRI3         0x00800000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CRLR0 PWM Capture Rising Latch Register 0(PWM_CRLR0)
//! @{
//
//*****************************************************************************

//
//! Capture Rising Latch Register mask
//
#define PWM_CRLR0_CRLR_M        0x0000FFFF

//
//! Capture Rising Latch Register shift
//
#define PWM_CRLR0_CRLR_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CRLR1 PWM Capture Rising Latch Register 1(PWM_CRLR1)
//! @{
//
//*****************************************************************************

//
//! Capture Rising Latch Register mask
//
#define PWM_CRLR1_CRLR_M        0x0000FFFF

//
//! Capture Rising Latch Register shift
//
#define PWM_CRLR1_CRLR_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CRLR2 PWM Capture Rising Latch Register 2(PWM_CRLR2)
//! @{
//
//*****************************************************************************

//
//! Capture Rising Latch Register mask
//
#define PWM_CRLR2_CRLR_M        0x0000FFFF

//
//! Capture Rising Latch Register shift
//
#define PWM_CRLR2_CRLR_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CRLR3 PWM Capture Rising Latch Register 3(PWM_CRLR3)
//! @{
//
//*****************************************************************************

//
//! Capture Rising Latch Register mask
//
#define PWM_CRLR3_CRLR_M        0x0000FFFF

//
//! Capture Rising Latch Register shift
//
#define PWM_CRLR3_CRLR_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CFLR0 PWM Capture Falling Latch Register 0(PWM_CFLR0)
//! @{
//
//*****************************************************************************

//
//! Capture Falling Latch Register mask
//
#define PWM_CFLR0_CFLR_M        0x0000FFFF

//
//! Capture Falling Latch Register shift
//
#define PWM_CFLR0_CFLR_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CFLR1 PWM Capture Falling Latch Register 1(PWM_CFLR1)
//! @{
//
//*****************************************************************************

//
//! Capture Falling Latch Register mask
//
#define PWM_CFLR1_CFLR_M        0x0000FFFF

//
//! Capture Falling Latch Register shift
//
#define PWM_CFLR1_CFLR_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CFLR2 PWM Capture Falling Latch Register 2(PWM_CFLR2)
//! @{
//
//*****************************************************************************

//
//! Capture Falling Latch Register mask
//
#define PWM_CFLR2_CFLR_M        0x0000FFFF

//
//! Capture Falling Latch Register shift
//
#define PWM_CFLR2_CFLR_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CFLR3 PWM Capture Falling Latch Register 3(PWM_CFLR3)
//! @{
//
//*****************************************************************************

//
//! Capture Falling Latch Register mask
//
#define PWM_CFLR3_CFLR_M        0x0000FFFF

//
//! Capture Falling Latch Register shift
//
#define PWM_CFLR3_CFLR_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_CAPENR PWM Capture Input Enable Register(PWM_CAPENR)
//! @{
//
//*****************************************************************************

//
//! Capture Input Enable Register mask
//
#define PWM_CAPENR_CAPIE_M      0x0000000F

//
//! Capture Input Enable Register shift
//
#define PWM_CAPENR_CAPIE_S      0

//
//! Capture channel 0 is from pin PA.12(A)
//
#define PWM_CAPENR_CAPIE_0      0x00000001

//
//! Capture channel 0 is from pin PA.13(A)
//
#define PWM_CAPENR_CAPIE_1      0x00000002

//
//! Capture channel 0 is from pin PA.14(A)
//
#define PWM_CAPENR_CAPIE_2      0x00000004

//
//! Capture channel 0 is from pin PA.15(A)
//
#define PWM_CAPENR_CAPIE_3      0x00000008


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_POE PWM Output Enable Register(PWM_POE)
//! @{
//
//*****************************************************************************

//
//! Channel 0 Output Enable Register
//
#define PWM_POE_PWM0            0x00000001

//
//! Channel 1 Output Enable Register
//
#define PWM_POE_PWM1            0x00000002

//
//! Channel 2 Output Enable Register
//
#define PWM_POE_PWM2            0x00000004

//
//! Channel 3 Output Enable Register
//
#define PWM_POE_PWM3            0x00000008

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_TCON PWM Trigger Control Register(PWM_TCON)
//! @{
//
//*****************************************************************************

//
//! Channel 0 Center-Aligned Trigger Enable Register
//
#define PWM_TCON_PWM0TEN        BIT_32_0

//
//! Channel 1 Center-Aligned Trigger Enable Register
//
#define PWM_TCON_PWM1TEN        BIT_32_1

//
//! Channel 2 Center-Aligned Trigger Enable Register
//
#define PWM_TCON_PWM2TEN        BIT_32_2

//
//! Channel 3 Center-Aligned Trigger Enable Register
//
#define PWM_TCON_PWM3TEN        BIT_32_3


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_PWM_TSTATUS PWM Trigger status Register(PWM_TSTAUTS)
//! @{
//
//*****************************************************************************

//
//! Channel 0 Center-aligned Trigger Flag
//
#define PWM_TSTAUTS_PWM0TF      BIT_32_0

//
//! Channel 1 Center-aligned Trigger Flag
//
#define PWM_TSTAUTS_PWM1TF      BIT_32_1

//
//! Channel 2 Center-aligned Trigger Flag
//
#define PWM_TSTAUTS_PWM2TF      BIT_32_2

//
//! Channel 3 Center-aligned Trigger Flag
//
#define PWM_TSTAUTS_PWM3TF      BIT_32_3


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_SYNCBUSY0 PWM Synchronous Busy Status status Register(PWM_SYNCBUSY0)
//! @{
//
//*****************************************************************************

//
//! PWM Synchronous Busy
//
#define PWM_SYNCBUSY0_BUSY      BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_SYNCBUSY1 PWM Synchronous Busy Status status Register(PWM_SYNCBUSY1)
//! @{
//
//*****************************************************************************

//
//! PWM Synchronous Busy
//
#define PWM_SYNCBUSY1_BUSY      BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_SYNCBUSY2 PWM Synchronous Busy Status status Register(PWM_SYNCBUSY2)
//! @{
//
//*****************************************************************************

//
//! PWM Synchronous Busy
//
#define PWM_SYNCBUSY2_BUSY      BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_SYNCBUSY3 PWM Synchronous Busy Status status Register(PWM_SYNCBUSY3)
//! @{
//
//*****************************************************************************

//
//! PWM Synchronous Busy
//
#define PWM_SYNCBUSY3_BUSY      BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_DMACTL PWM PDMA control Register(PWM_DMACTL)
//! @{
//
//*****************************************************************************

//
//! Channel 0 PDMA Enable
//
#define PWM_DMACTL_CAP0PDMAEN   BIT_32_0

//
//! Select CRLR0 or CFLR0 to Transfer PDMA mask
//
#define PWM_DMACTL_CAP0DMAMOD_M BIT_MASK(32,2,1)

//
//! Select CRLR0 or CFLR0 to Transfer PDMA shift
//
#define PWM_DMACTL_CAP0DMAMOD_S 1

//
//! CRLR0
//
#define PWM_DMACTL_CAP0DMAMOD_1 BIT_32_1

//
//! CFLR0
//
#define PWM_DMACTL_CAP0DMAMOD_2 BIT_32_2

//
//! Both CRLR0 and CFLR0
//
#define PWM_DMACTL_CAP0DMAMOD_3 (BIT_32_1 | BIT_32_2)

//
//! Set this bit to determine whether the CRLR0 or CFLR0 is the first captured
//! data transferred to memory through PDMA when CAP0PDMAMOD =11
//
#define PWM_DMACTL_CAP0RFORDER  BIT_32_3

//
//! Channel 1 PDMA Enable
//
#define PWM_DMACTL_CAP1PDMAEN   BIT_32_8

//
//! Select CRLR1 or CFLR1 to Transfer PDMA mask
//
#define PWM_DMACTL_CAP1DMAMOD_M BIT_MASK(32,10,9)

//
//! Select CRLR1 or CFLR1 to Transfer PDMA shift
//
#define PWM_DMACTL_CAP1DMAMOD_S 9

//
//! CRLR1
//
#define PWM_DMACTL_CAP1DMAMOD_1 BIT_32_9

//
//! CFLR1
//
#define PWM_DMACTL_CAP1DMAMOD_2 BIT_32_10

//
//! Both CRLR1 and CFLR1
//
#define PWM_DMACTL_CAP1DMAMOD_3 (BIT_32_10 | BIT_32_9)

//
//! Set this bit to determine whether the CRLR1 or CFLR1 is the first captured
//! data transferred to memory through PDMA when CAP0PDMAMOD =11
//
#define PWM_DMACTL_CAP1RFORDER  BIT_32_11

//
//! Channel 2 PDMA Enable
//
#define PWM_DMACTL_CAP2PDMAEN   BIT_32_16

//
//! Select CRLR2 or CFLR2 to Transfer PDMA mask
//
#define PWM_DMACTL_CAP2DMAMOD_M BIT_MASK(32,18,17)

//
//! Select CRLR2 or CFLR2 to Transfer PDMA shift
//
#define PWM_DMACTL_CAP2DMAMOD_S 17

//
//! CRLR2
//
#define PWM_DMACTL_CAP2DMAMOD_1 BIT_32_17

//
//! CFLR2
//
#define PWM_DMACTL_CAP2DMAMOD_2 BIT_32_18

//
//! Both CRLR2 and CFLR2
//
#define PWM_DMACTL_CAP2DMAMOD_3 (BIT_32_18 | BIT_32_17)

//
//! Set this bit to determine whether the CRLR2 or CFLR2 is the first captured
//! data transferred to memory through PDMA when CAP0PDMAMOD =11
//
#define PWM_DMACTL_CAP2RFORDER  BIT_32_19

//
//! Channel 3 PDMA Enable
//
#define PWM_DMACTL_CAP3PDMAEN   BIT_32_24

//
//! Select CRLR3 or CFLR3 to Transfer PDMA mask
//
#define PWM_DMACTL_CAP3DMAMOD_M BIT_MASK(32,26,25)

//
//! Select CRLR3 or CFLR3 to Transfer PDMA shift
//
#define PWM_DMACTL_CAP3DMAMOD_S 25

//
//! CRLR3
//
#define PWM_DMACTL_CAP3DMAMOD_1 BIT_32_25

//
//! CFLR3
//
#define PWM_DMACTL_CAP3DMAMOD_2 BIT_32_26

//
//! Both CRLR3 and CFLR3
//
#define PWM_DMACTL_CAP3DMAMOD_3 (BIT_32_26 | BIT_32_25)

//
//! Set this bit to determine whether the CRLR3 or CFLR3 is the first captured
//! data transferred to memory through PDMA when CAP0PDMAMOD =11
//
#define PWM_DMACTL_CAP3RFORDER  BIT_32_27

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_CAP0PDMA PWM PDMA DATA Register(PWM_CAP0PDMA)
//! @{
//
//*****************************************************************************

//
//! PDMA data register for channel 0 mask
//
#define PWM_CAP0PDMA_DATA_M     BIT_MASK(32,15,0)

//
//! PDMA data register for channel 0 shift
//
#define PWM_CAP0PDMA_DATA_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_CAP1PDMA PWM PDMA DATA Register(PWM_CAP1PDMA)
//! @{
//
//*****************************************************************************

//
//! PDMA data register for channel 1 mask
//
#define PWM_CAP1PDMA_DATA_M     BIT_MASK(32,15,0)

//
//! PDMA data register for channel 1 shift
//
#define PWM_CAP1PDMA_DATA_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_CAP2PDMA PWM PDMA DATA Register(PWM_CAP2PDMA)
//! @{
//
//*****************************************************************************

//
//! PDMA data register for channel 2 mask
//
#define PWM_CAP2PDMA_DATA_M     BIT_MASK(32,15,0)

//
//! PDMA data register for channel 2 shift
//
#define PWM_CAP2PDMA_DATA_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC123_PWM_Register_CAP3PDMA PWM PDMA DATA Register(PWM_CAP3PDMA)
//! @{
//
//*****************************************************************************

//
//! PDMA data register for channel 3 mask
//
#define PWM_CAP3PDMA_DATA_M     BIT_MASK(32,15,0)

//
//! PDMA data register for channel 3 shift
//
#define PWM_CAP3PDMA_DATA_S     0

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

#endif // __XHW_PWM_H__




