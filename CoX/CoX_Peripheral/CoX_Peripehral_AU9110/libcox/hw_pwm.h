//*****************************************************************************
//
//! \file xhw_pwm.h
//! \brief Macros and defines used when accessing the PWM hardware.
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
//! \addtogroup AU9110_PWM_Register AU9110 PWM Register
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
//! \addtogroup AU9110_PWM_Register_Address_Offset PWM Register Offset(map)
//! \brief Here is the PWM register offset, users can get the register address
//! through <b>PWM_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! PWM Group A\B Pre-scale Register
//
#define PWM_PPR                 0x00000000  

//
//! PWM Group A\B Clock Select Register
//
#define PWM_CSR                 0x00000004  

//
//! PWM Group A\B Control Register
//
#define PWM_PCR                 0x00000008  

//
//! PWM Group A\B Counter Register 0
//
#define PWM_CNR0                0x0000000C  

//
//! PWM Group A\B Comparator Register 0
//
#define PWM_CMR0                0x00000010  

//
//! PWM Group A\B Data Register 0
//
#define PWM_PDR0                0x00000014  

//
//! PWM Group A\B Counter Register 1
//
#define PWM_CNR1                0x00000018  

//
//! PWM Group A\B Comparator Register 1
//
#define PWM_CMR1                0x0000001C  

//
//! PWM Group A\B Data Register 1
//
#define PWM_PDR1                0x00000020

//
//! PWM Group A\B Interrupt Enable Register
//
#define PWM_PIER                0x00000040  

//
//! PWM Group A\B Interrupt Indication Register
//
#define PWM_PIIR                0x00000044  

//
//! PWM Group A\B Capture Control Register 0
//
#define PWM_CCR0                0x00000050

//
//! PWM Group A\B Capture Rising Latch Register (Channel 0)
//
#define PWM_CRLR0               0x00000058  

//
//! PWM Group A\B Capture Falling Latch Register (Channel 0)
//
#define PWM_CFLR0               0x0000005C  

//
//! PWM Group A\B Capture Rising Latch Register (Channel 1)
//
#define PWM_CRLR1               0x00000060  

//
//! PWM Group A\B Capture Falling Latch Register (Channel 1)
//
#define PWM_CFLR1               0x00000064

//
//! PWM Group A\B Capture Input 0~3 Enable Register
//
#define PWM_CAPENR              0x00000078

//
//! PWM Group A\B Output Enable for channel 0~3
//
#define PWM_POE                 0x0000007C

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PWM_Register_Channel_Address_Offset PWM Channel Address Offset Register
//! \brief Defines for the bit fields in the PWM_Channel_Address_Offset register.
//! @{
//
//*****************************************************************************

//
//! PWM Channel 0 Group A\ Channel 4 Group offset address
//
#define PWM_CHANNEL_04          0x0000000C

//
//! PWM Channel 1 Group A\ Channel 5 Group offset address
//
#define PWM_CHANNEL_15          0x00000018

//
//! PWM Channel 2 Group A\ Channel 6 Group offset address
//
#define PWM_CHANNEL_26          0x00000024

//
//! PWM Channel 3 Group A\ Channel 7 Group offset address
//
#define PWM_CHANNEL_37          0x00000030

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
//! \addtogroup AU9110_PWM_Register_PWM_PPR PWM Prescaler Register(PWM_PPR)
//! \brief Defines for the bit fields in the PWM_Channel_Address_Offset register.
//! @{
//
//*****************************************************************************

//
//! Clock Prescaler 0 (PWM-timer 0 / 1 for group A and 
//! PWM-timer 4 5 for group B) mask
//
#define PWM_PPR_CP01_M          0x000000FF  

//
//! Clock Prescaler 0 (PWM-timer 0 / 1 for group A and 
//! PWM-timer 4 5 for group B) shift
//
#define PWM_PPR_CP01_S          0  

//
//! Clock Prescaler 2 (PWM-timer 2 / 3 for group A and 
//! PWM-timer 6 7 for group B) mask
//
#define PWM_PPR_CP23_M          0x0000FF00  

//
//! Clock Prescaler 2 (PWM-timer 2 / 3 for group A and 
//! PWM-timer 6 7 for group B) shift
//
#define PWM_PPR_CP23_S          8  


//
//! Dead Zone Interval for Pair of Channel 0 and Channel 1 (PWM0 and PWM1 
//! pair for PWM group A, PWM4 and PWM5 pair for PWM group B) mask
//
#define PWM_PPR_DZI01_M         0x00FF0000

//
//! Dead Zone Interval for Pair of Channel 0 and Channel 1 (PWM0 and PWM1 
//! pair for PWM group A, PWM4 and PWM5 pair for PWM group B) shift
//
#define PWM_PPR_DZI01_S         16

//
//! Dead Zone Interval for Pair of Channel 2 and Channel 3 (PWM2 and PWM3 
//! pair for PWM group A, PWM6 and PWM7 pair for PWM group B) mask
//
#define PWM_PPR_DZI23_M         0xFF000000

//
//! Dead Zone Interval for Pair of Channel 2 and Channel 3 (PWM2 and PWM3 
//! pair for PWM group A, PWM6 and PWM7 pair for PWM group B) shift
//
#define PWM_PPR_DZI23_S         24

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PWM_Register_PWM_CSR PWM Clock Select Register(PWM_CSR)
//! \brief Defines for the bit fields in the PWM_CSR register.
//! @{
//
//*****************************************************************************

//
//! PWM Timer 0 Clock Source Selection (PWM timer 0 for group A and PWM timer 4
//! for group B) mask
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
//! PWM Timer 0 Clock Source Selection (PWM timer 0 for group A and PWM timer 4
//! for group B) shift
//
#define PWM_CSR_CSR0_S          0

//
//! PWM Timer 1 Clock Source Selection (PWM timer 1 for group A and PWM timer 5
//! for group B) mask
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
//! PWM Timer 1 Clock Source Selection (PWM timer 1 for group A and PWM timer 5
//! for group B) shift
//
#define PWM_CSR_CSR1_S          4

//
//! PWM Timer 2 Clock Source Selection (PWM timer 2 for group A and PWM timer 6
//! for group B) mask
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
//! PWM Timer 2 Clock Source Selection (PWM timer 2 for group A and PWM timer 6
//! for group B) shift
//
#define PWM_CSR_CSR2_S          8

//
//! PWM Timer 3 Clock Source Selection (PWM timer 3 for group A and PWM timer 7
//! for group B) mask
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
//! PWM Timer 3 Clock Source Selection (PWM timer 3 for group A and PWM timer 7
//! for group B) shift
//
#define PWM_CSR_CSR3_S          12

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PWM_Register_PWM_PCR PWM Control Register(PWM_PCR)
//! \brief Defines for the bit fields in the PWM_PCR register.
//! @{
//
//*****************************************************************************

//
//! PWM-Timer 0 Enable (PWM timer 0 for group A and PWM timer 4 for group B)
//
#define PWM_PCR_CH0EN           0x00000001

//
//! PWM-Timer 0 Output Inverter Enable
//
#define PWM_PCR_CH0INV          0x00000004

//
//! PWM-Timer 0 Auto-reload/One-Shot Mode
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
//! PWM-Timer 1 Enable (PWM timer 1 for group A and PWM timer 5 for group B)
//
#define PWM_PCR_CH1EN           0x00000100

//
//! PWM-Timer 1 Output Inverter Enable
//
#define PWM_PCR_CH1INV          0x00000400

//
//! PWM-Timer 1 Auto-reload/One-Shot Mode
//
#define PWM_PCR_CH1MOD          0x00000800

//
//! PWM-Timer 2 Enable (PWM timer 2 for group A and PWM timer 6 for group B)
//
#define PWM_PCR_CH2EN           0x00010000

//
//! PWM-Timer 2 Output Inverter Enable
//
#define PWM_PCR_CH2INV          0x00040000

//
//! PWM-Timer 2 Auto-reload/One-Shot Mode
//
#define PWM_PCR_CH2MOD          0x00080000

//
//! PWM-Timer 3 Enable (PWM timer 3 for group A and PWM timer 7 for group B)
//
#define PWM_PCR_CH3EN           0x01000000

//
//! PWM-Timer 3 Output Inverter Enable
//
#define PWM_PCR_CH3INV          0x04000000

//
//! PWM-Timer 3 Auto-reload/One-Shot Mode
//
#define PWM_PCR_CH3MOD          0x08000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PWM_Register_PWM_CNR0 PWM Counter Register 0(PWM_CNR0)
//! \brief Defines for the bit fields in the PWM_CNR0 register.
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
//! \addtogroup AU9110_PWM_Register_PWM_CNR1 PWM Counter Register 1(PWM_CNR1)
//! \brief Defines for the bit fields in the PWM_CNR1 register.
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
//! \addtogroup AU9110_PWM_Register_PWM_CMR0 PWM Comparator Register 0(PWM_CMR0)
//! \brief Defines for the bit fields in the PWM_CMR0 register.
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
//! \addtogroup AU9110_PWM_Register_PWM_CMR1 PWM Comparator Register 1(PWM_CMR1)
//! \brief Defines for the bit fields in the PWM_CMR1 register.
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
//! \addtogroup AU9110_PWM_Register_PWM_PDR0 PWM Data Register 0(PWM_PDR0)
//! \brief Defines for the bit fields in the PWM_PDR0 register.
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
//! \addtogroup AU9110_PWM_Register_PWM_PDR1 PWM Data Register 1(PWM_PDR1)
//! \brief Defines for the bit fields in the PWM_PDR1 register.
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
//! \addtogroup AU9110_PWM_Register_PWM_PIER PWM Interrupt Enable Register(PWM_PIER)
//! \brief Defines for the bit fields in the PWM_PIER register.
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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PWM_Register_PWM_PIIR PWM Interrupt Indication Register(PWM_PIIR)
//! \brief Defines for the bit fields in the PWM_PIIR register.
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

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PWM_Register_PWM_CCR0 PWM Capture Control Register 0(PWM_CCR0)
//! \brief Defines for the bit fields in the PWM_CCR0 register.
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
//! \addtogroup AU9110_PWM_Register_PWM_CRLR0 PWM Capture Rising Latch Register 0(PWM_CRLR0)
//! \brief Defines for the bit fields in the PWM_CRLR0 register.
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
//! \addtogroup AU9110_PWM_Register_PWM_CRLR1 PWM Capture Rising Latch Register 1(PWM_CRLR1)
//! \brief Defines for the bit fields in the PWM_CRLR1 register.
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
//! \addtogroup AU9110_PWM_Register_PWM_CFLR0 PWM Capture Falling Latch Register 0(PWM_CFLR0)
//! \brief Defines for the bit fields in the PWM_CFLR0 register.
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
//! \addtogroup AU9110_PWM_Register_PWM_CFLR1 PWM Capture Falling Latch Register 1(PWM_CFLR1)
//! \brief Defines for the bit fields in the PWM_CFLR1 register.
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
//! \addtogroup AU9110_PWM_Register_PWM_CAPENR PWM Capture Input Enable Register(PWM_CAPENR)
//! \brief Defines for the bit fields in the PWM_CAPENR register.
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
//! Capture channel 0 is from pin PA.12(A) or PB.11(B)
//
#define PWM_CAPENR_CAPIE_0      0x00000001

//
//! Capture channel 0 is from pin PA.13(A) or PE.5(B)
//
#define PWM_CAPENR_CAPIE_1      0x00000002

//
//! Capture channel 0 is from pin PA.14(A) or PE.0(B)
//
#define PWM_CAPENR_CAPIE_2      0x00000004

//
//! Capture channel 0 is from pin PA.15(A) or PE.1(B)
//
#define PWM_CAPENR_CAPIE_3      0x00000008


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PWM_Register_PWM_POE PWM Output Enable Register(PWM_POE)
//! \brief Defines for the bit fields in the PWM_POE register.
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
