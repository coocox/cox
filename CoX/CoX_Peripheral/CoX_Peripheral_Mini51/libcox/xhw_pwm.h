//*****************************************************************************
//
//! \file xhw_pwm.h
//! \brief Macros and defines used when accessing the PWM hardware.
//! \version V2.1.1.0
//! \date 1/31/2012
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
//! \addtogroup Mini51_PWM_Register Mini51 PWM Register
//! \brief Here are the detailed info of PWM registers.  
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
//! \addtogroup Mini51_PWM_Register_Address_Offset PWM Register Offset(map)
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
//! PWM Group A Counter Register 1
//
#define PWM_CNR1                0x00000010

//
//! PWM Group A Counter Register 2
//
#define PWM_CNR2                0x00000014

//
//! PWM Group A Counter Register 3
//
#define PWM_CNR3                0x00000018

//
//! PWM Group A Counter Register 4
//
#define PWM_CNR4                0x0000001C

//
//! PWM Group A Counter Register 5
//
#define PWM_CNR5                0x00000020

//
//! PWM Group A Comparator Register 0
//
#define PWM_CMR0                0x00000024

//
//! PWM Group A Comparator Register 1
//
#define PWM_CMR1                0x00000028

//
//! PWM Group A Comparator Register 2
//
#define PWM_CMR2                0x0000002C

//
//! PWM Group A Comparator Register 3
//
#define PWM_CMR3                0x00000030

//
//! PWM Group A Comparator Register 4
//
#define PWM_CMR4                0x00000034

//
//! PWM Group A Comparator Register 5
//
#define PWM_PMR5                0x00000038

//
//! PWM Group A Interrupt Enable Register
//
#define PWM_PIER                0x00000054

//
//! PWM Group A Interrupt Indication Register
//
#define PWM_PIIR                0x00000058

//
//! PWM Output Enable for channel 0~5
//
#define PWM_POE                 0x0000005C

//
//! PWM Fault Brake control Register
//
#define PWM_PFBCON              0x00000060

//
//! PWM dead-zone interval register
//
#define PWM_PDZIR               0x00000064

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup Mini51_PWM_Register_PWM_PPR PWM Prescaler Register(PWM_PPR)
//! @{
//
//*****************************************************************************

//
//! Clock Prescaler 0 (PWM-timer 0 / 1) mask
//
#define PWM_PPR_CP01_M          0x000000FF

//
//! Clock Prescaler 0 (PWM-timer 0 / 1) shift
//
#define PWM_PPR_CP01_S          0

//
//! Clock Prescaler 2 (PWM-timer 2 / 3) mask
//
#define PWM_PPR_CP23_M          0x0000FF00

//
//! Clock Prescaler 2 (PWM-timer 2 / 3) shift
//
#define PWM_PPR_CP23_S          8

//
//! Clock Prescaler 4 (PWM-timer 4 / 5) mask
//
#define PWM_PPR_CP45_M         0x00FF0000

//
//! Clock Prescaler 4 (PWM-timer 4 / 5) shift
//
#define PWM_PPR_CP45_S          16

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Mini51_PWM_Register_PWM_CSR PWM Clock Select Register(PWM_CSR)
//! @{
//
//*****************************************************************************

//
//! PWM Timer 0 Clock Source Selection (PWM timer 0) mask
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
//! PWM Timer 0 Clock Source Selection (PWM timer 0) shift
//
#define PWM_CSR_CSR0_S          0

//
//! PWM Timer 1 Clock Source Selection (PWM timer 1) mask
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
//! PWM Timer 1 Clock Source Selection (PWM timer 1) shift
//
#define PWM_CSR_CSR1_S          4

//
//! PWM Timer 2 Clock Source Selection (PWM timer 2) mask
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
//! PWM Timer 2 Clock Source Selection (PWM timer 2) shift
//
#define PWM_CSR_CSR2_S          8

//
//! PWM Timer 3 Clock Source Selection (PWM timer 3) mask
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
//! PWM Timer 3 Clock Source Selection (PWM timer 3) shift
//
#define PWM_CSR_CSR3_S          12

//
//! PWM Timer 4 Clock Source Selection (PWM timer 4) mask
//
#define PWM_CSR_CSR4_M          0x00070000

//
//! Select clock input for PWM timer.Input clock divided by 2
//
#define PWM_CSR_CSR4_2          0x00000000

//
//! Select clock input for PWM timer.Input clock divided by 4
//
#define PWM_CSR_CSR4_4          0x00010000

//
//! Select clock input for PWM timer.Input clock divided by 8
//
#define PWM_CSR_CSR4_8          0x00020000

//
//! Select clock input for PWM timer.Input clock divided by 16
//
#define PWM_CSR_CSR4_16         0x00030000

//
//! Select clock input for PWM timer.Input clock divided by 1
//
#define PWM_CSR_CSR4_1          0x00040000

//
//! PWM Timer 4 Clock Source Selection (PWM timer 4) shift
//
#define PWM_CSR_CSR4_S          16

//
//! PWM Timer 5 Clock Source Selection (PWM timer 5) mask
//
#define PWM_CSR_CSR5_M          0x00700000

//
//! Select clock input for PWM timer.Input clock divided by 2
//
#define PWM_CSR_CSR5_2          0x00000000

//
//! Select clock input for PWM timer.Input clock divided by 4
//
#define PWM_CSR_CSR5_4          0x00100000

//
//! Select clock input for PWM timer.Input clock divided by 8
//
#define PWM_CSR_CSR5_8          0x00200000

//
//! Select clock input for PWM timer.Input clock divided by 16
//
#define PWM_CSR_CSR5_16         0x00300000

//
//! Select clock input for PWM timer.Input clock divided by 1
//
#define PWM_CSR_CSR5_1          0x00400000

//
//! PWM Timer 5 Clock Source Selection (PWM timer 5) shift
//
#define PWM_CSR_CSR5_S          20

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Mini51_PWM_Register_PWM_PCR PWM Control Register(PWM_PCR)
//! @{
//
//*****************************************************************************

//
//! PWM-Timer 0 Enable (PWM timer 0)
//
#define PWM_PCR_CH0EN           0x00000001

//
//! PWM Debug mode configuration bit (Available in DEBUG mode only)
//
#define PWM_PCR_DB_MODE         0x00000002

//
//! PWM-Timer 0 Output Inverter Enable
//
#define PWM_PCR_CH0INV          0x00000004

//
//! PWM-Timer 0 Auto-reload/One-Shot Mode
//
#define PWM_PCR_CH0MOD          0x00000008

//
//! PWM-Timer 1 Enable (PWM timer 1)
//
#define PWM_PCR_CH1EN           0x00000010

//
//! PWM-Timer 1 Output Inverter Enable
//
#define PWM_PCR_CH1INV          0x00000040

//
//! PWM-Timer 1 Auto-reload/One-Shot Mode
//
#define PWM_PCR_CH1MOD          0x00000080

//
//! PWM-Timer 2 Enable (PWM timer 2)
//
#define PWM_PCR_CH2EN           0x00000100

//
//! PWM-Timer 2 Output Inverter Enable
//
#define PWM_PCR_CH2INV          0x00000400

//
//! PWM-Timer 2 Auto-reload/One-Shot Mode
//
#define PWM_PCR_CH2MOD          0x00000800

//
//! PWM-Timer 3 Enable (PWM timer 3)
//
#define PWM_PCR_CH3EN           0x00001000

//
//! PWM-Timer 3 Output Inverter Enable
//
#define PWM_PCR_CH3INV          0x00004000

//
//! PWM-Timer 3 Auto-reload/One-Shot Mode
//
#define PWM_PCR_CH3MOD          0x00008000

//
//! PWM-Timer 4 Enable (PWM timer 4)
//
#define PWM_PCR_CH4EN           0x00001000

//
//! PWM-Timer 4 Output Inverter Enable
//
#define PWM_PCR_CH4INV          0x00040000

//
//! PWM-Timer 4 Auto-reload/One-Shot Mode
//
#define PWM_PCR_CH4MOD          0x00080000

//
//! PWM-Timer 5 Enable (PWM timer 5)
//
#define PWM_PCR_CH5EN           0x00100000

//
//! PWM-Timer 5 Output Inverter Enable
//
#define PWM_PCR_CH5INV          0x00400000

//
//! PWM-Timer 4 Auto-reload/One-Shot Mode
//
#define PWM_PCR_CH5MOD          0x00800000

//
//! Dead-Zone 0 Generator Enable
//
#define PWM_PCR_DZEN01          0x01000000

//
//! Dead-Zone 2 Generator Enable
//
#define PWM_PCR_DZEN23          0x02000000

//
//! Dead-Zone 4 Generator Enable
//
#define PWM_PCR_DZEN45          0x04000000

//
//! Clear PWM Counter Control Bit
//
#define PWM_PCR_CLRPWM          0x08000000

//
//! PWM Operating Mode Selection mask
//
#define PWM_PCR_PWMMOD_M        0x30000000

//
//! Independent mode
//
#define PWM_PCR_INDEPENDENT_MOD 0x00000000

//
//! Complementary mode
//
#define PWM_PCR_COMPLEMENTARY_MOD                                             \
                                0x10000000

//
//! Synchronized mode
//
#define PWM_PCR_SYNCHRONIZED_MOD                                              \
                                0x20000000

//
//! PWM Operating Mode Selection shift
//
#define PWM_PCR_PWMMOD_S        28

//
//! Group bit
//
#define PWM_PCR_GRP             0x40000000

//
//! PWM Centre-aligned type Bit
//
#define PWM_PCR_PWMTYPE         0x80000000
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Mini51_PWM_Register_PWM_CNR0 PWM Counter Register 0(PWM_CNR0)
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
//! \addtogroup Mini51_PWM_Register_PWM_CNR1 PWM Counter Register 1(PWM_CNR1)
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
//! \addtogroup Mini51_PWM_Register_PWM_CNR2 PWM Counter Register 2(PWM_CNR2)
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
//! \addtogroup Mini51_PWM_Register_PWM_CNR3 PWM Counter Register 3(PWM_CNR3)
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
//! \addtogroup Mini51_PWM_Register_PWM_CNR4 PWM Counter Register 4(PWM_CNR4)
//! @{
//
//*****************************************************************************

//
//! PWM Timer Loaded Value mask
//
#define PWM_CNR4_CNR4_M         0x0000FFFF

//
//! PWM Timer Loaded Value shift
//
#define PWM_CNR4_CNR4_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Mini51_PWM_Register_PWM_CNR5 PWM Counter Register 5(PWM_CNR5)
//! @{
//
//*****************************************************************************

//
//! PWM Timer Loaded Value mask
//
#define PWM_CNR5_CNR5_M         0x0000FFFF

//
//! PWM Timer Loaded Value shift
//
#define PWM_CNR5_CNR5_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Mini51_PWM_Register_PWM_CMR0 PWM Comparator Register 0(PWM_CMR0)
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
//! \addtogroup Mini51_PWM_Register_PWM_CMR1 PWM Comparator Register 1(PWM_CMR1)
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
//! \addtogroup Mini51_PWM_Register_PWM_CMR2 PWM Comparator Register 2(PWM_CMR2)
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
//! \addtogroup Mini51_PWM_Register_PWM_CMR3 PWM Comparator Register 3 (PWM_CMR3)
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
//! \addtogroup Mini51_PWM_Register_PWM_CMR4 PWM Comparator Register 4 (PWM_CMR4)
//! @{
//
//*****************************************************************************

//
//! PWM Comparator Register mask
//
#define PWM_CMR4_CMR4_M         0x0000FFFF

//
//! PWM Comparator Register shift
//
#define PWM_CMR4_CMR4_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Mini51_PWM_Register_PWM_CMR5 PWM Comparator Register 5 (PWM_CMR5)
//! @{
//
//*****************************************************************************

//
//! PWM Comparator Register mask
//
#define PWM_CMR5_CMR5_M         0x0000FFFF

//
//! PWM Comparator Register shift
//
#define PWM_CMR5_CMR5_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Mini51_PWM_Register_PWM_PIER PWM Interrupt Enable Register(PWM_PIER)
//! @{
//
//*****************************************************************************

//
//! PWM channel 0 Period Interrupt Enable 
//
#define PWM_PIER_PWMPIE0        0x00000001

//
//! PWM channel 1 Period Interrupt Enable
//
#define PWM_PIER_PWMPIE1        0x00000002

//
//! PWM channel 2 Period Interrupt Enable
//
#define PWM_PIER_PWMPIE2        0x00000004

//
//! PWM channel 3 Period Interrupt Enable
//
#define PWM_PIER_PWMPIE3        0x00000008

//
//! PWM channel 4 Period Interrupt Enable
//
#define PWM_PIER_PWMPIE4        0x00000010

//
//! PWM channel 5 Period Interrupt Enable
//
#define PWM_PIER_PWMPIE5        0x00000020

//
//! PWM channel 0 Duty Interrupt Enable
//
#define PWM_PIER_PWMDIE0        0x00000100

//
//! PWM channel 1 Duty Interrupt Enable
//
#define PWM_PIER_PWMDIE1        0x00000200

//
//! PWM channel 2 Duty Interrupt Enable
//
#define PWM_PIER_PWMDIE2        0x00000400

//
//! PWM channel 3 Duty Interrupt Enable
//
#define PWM_PIER_PWMDIE3        0x00000800

//
//! PWM channel 4 Duty Interrupt Enable
//
#define PWM_PIER_PWMDIE4        0x00001000

//
//! PWM channel 5 Duty Interrupt Enable
//
#define PWM_PIER_PWMDIE5        0x00002000

//
//! Enable Fault brake0 and 1 interrupt 
//
#define PWM_PIER_BRKIE          0x00010000

//
//! PWMPIFn will be set if PWM counter matches CNRn register
//
#define PWM_PIER_INT_TYPE       0x00020000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Mini51_PWM_Register_PWM_PIIR PWM Interrupt Indication Register(PWM_PIIR)
//! @{
//
//*****************************************************************************


//
//! PWM channel 0 Period Interrupt Flag 
//
#define PWM_PIER_PWMPIF0        0x00000001

//
//! PWM channel 1 Period Interrupt Flag
//
#define PWM_PIER_PWMPIF1        0x00000002

//
//! PWM channel 2 Period Interrupt Flag
//
#define PWM_PIER_PWMPIF2        0x00000004

//
//! PWM channel 3 Period Interrupt Flag
//
#define PWM_PIER_PWMPIF3        0x00000008

//
//! PWM channel 4 Period Interrupt Flag
//
#define PWM_PIER_PWMPIF4        0x00000010

//
//! PWM channel 5 Period Interrupt Flag
//
#define PWM_PIER_PWMPIF5        0x00000020

//
//! PWM channel 0 Duty Interrupt Flag
//
#define PWM_PIER_PWMDIF0        0x00000100

//
//! PWM channel 1 Duty Interrupt Flag
//
#define PWM_PIER_PWMDIF1        0x00000200

//
//! PWM channel 2 Duty Interrupt Flag
//
#define PWM_PIER_PWMDIF2        0x00000400

//
//! PWM channel 3 Duty Interrupt Flag
//
#define PWM_PIER_PWMDIF3        0x00000800

//
//! PWM channel 4 Duty Interrupt Flag
//
#define PWM_PIER_PWMDIF4        0x00001000

//
//! PWM channel 5 Duty Interrupt Flag
//
#define PWM_PIER_PWMDIF5        0x00002000

//
//! PWM Brake0 Flag 
//
#define PWM_PIER_BKF0           0x00010000

//
//! PWM Brake1 Flag
//
#define PWM_PIER_BKF1           0x00020000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Mini51_PWM_Register_PWM_POE PWM Output Enable Register(PWM_POE)
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

//
//! Channel 4 Output Enable Register
//
#define PWM_POE_PWM4            0x00000010

//
//! Channel 5 Output Enable Register
//
#define PWM_POE_PWM5            0x00000020

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Mini51_PWM_Register_PWM_PFBCON  Fault Brake Control Register(PFBCON)
//! @{
//
//*****************************************************************************

//
//! Enable BKP0 Pin Trigger Fault Brake Function 0
//
#define PWM_PFBCON_BKEN0        0x00000001

//
//! Enable BKP1 Pin Trigger Fault Brake Function 1
//
#define PWM_PFBCON_BKEN1        0x00000002

//
//! BKP1 Fault Brake Function Source Selection
//
#define PWM_PFBCON_CPO0BKEN     0x00000004

//
//! PWM Fault Brake Event Flag (write ¡°1¡± clear)
//
#define PWM_PFBCON_BKF          0x00000080

//
//! PWM Channel 0 Brake Output Select Register
//
#define PWM_PFBCON_PWMBKO0      0x01000000

//
//! PWM Channel 1 Brake Output Select Register
//
#define PWM_PFBCON_PWMBKO1      0x02000000

//
//! PWM Channel 2 Brake Output Select Register
//
#define PWM_PFBCON_PWMBKO2      0x04000000

//
//! PWM Channel 3 Brake Output Select Register
//
#define PWM_PFBCON_PWMBKO3      0x08000000

//
//! PWM Channel 4 Brake Output Select Register
//
#define PWM_PFBCON_PWMBKO4      0x10000000

//
//! PWM Channel 5 Brake Output Select Register
//
#define PWM_PFBCON_PWMBKO5      0x20000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Mini51_PWM_Register_PWM_PDZIR PWM Dead-Zone Interval Register (PDZIR)
//! @{
//
//*****************************************************************************

//
//! Dead-zone interval register for pair of PWM0 and PWM1 pair mask. 
//
#define PWM_PDZIR_DZI01_M       0x000000FF

//
//! Dead-zone interval register for pair of PWM0 and PWM1 pair shift.
//
#define PWM_PDZIR_DZI01_S       0

//
//! Dead-zone interval register for pair of PWM2 and PWM3 pair mask. 
//
#define PWM_PDZIR_DZI23_M       0x0000FF00

//
//! Dead-zone interval register for pair of PWM2 and PWM3 pair shift.
//
#define PWM_PDZIR_DZI23_S       8

//
//! Dead-zone interval register for pair of PWM4 and PWM5 pair mask. 
//
#define PWM_PDZIR_DZI45_M       0x00FF0000

//
//! Dead-zone interval register for pair of PWM4 and PWM5 pair shift.
//
#define PWM_PDZIR_DZI45_S       16

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
