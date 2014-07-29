//*****************************************************************************
//
//! \file hw_pwm.h
//! \brief Macros and defines used when accessing the PWM hardware.
//! \version V2.2.1.0
//! \date 11/15/2013
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
//! \addtogroup NUC4xx_PWM_Register NUC4xx PWM Register
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
//! \addtogroup NUC4xx_PWM_Register_Address_Offset PWM Register Offset(map)
//! \brief Here is the PWM register offset, users can get the register address
//! through <b>PWM_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! PWM Clock Prescale Register
//
#define PWM_CLKPSC              0x00000000

//
//! PWM Clock Divide Register
//
#define PWM_CLKDIV              0x00000004

//
//! PWM Control Register
//
#define PWM_CTL                 0x00000008

//
//! PWM Counter Enable Control Register
//
#define PWM_CNTEN               0x0000000C

//
//! PWM Period Register 0
//
#define PWM_PERIOD0             0x00000010

//
//! PWM Period Register 1
//
#define PWM_PERIOD1             0x00000014

//
//! PWM Period Register 2
//
#define PWM_PERIOD2             0x00000018

//
//! PWM Period Register 3
//
#define PWM_PERIOD3             0x0000001C

//
//! PWM Period Register 4
//
#define PWM_PERIOD4             0x00000020

//
//! PWM Period Register 5
//
#define PWM_PERIOD5             0x00000024

//
//! PPWM Comparator Register 0
//
#define PWM_CMPDAT0             0x00000028

//
//! PPWM Comparator Register 1
//
#define PWM_CMPDAT1             0x0000002C

//
//! PPWM Comparator Register 2
//
#define PWM_CMPDAT2             0x00000030

//
//! PPWM Comparator Register 3
//
#define PWM_CMPDAT3             0x00000034

//
//! PPWM Comparator Register 4
//
#define PWM_CMPDAT4             0x00000038

//
//! PPWM Comparator Register 5
//
#define PWM_CMPDAT5             0x0000003C

//
//! PWM Data Register 0
//
#define PWM_CNT0                0x00000040

//
//! PWM Data Register 1
//
#define PWM_CNT1                0x00000044

//
//! PWM Data Register 2
//
#define PWM_CNT2                0x00000048

//
//! PWM Data Register 3
//
#define PWM_CNT3                0x0000004C

//
//! PWM Data Register 4
//
#define PWM_CNT4                0x00000050

//
//! PWM Data Register 5
//
#define PWM_CNT5                0x00000054

//
//! PWM Mask Control Register
//
#define PWM_MSKEN               0x00000058

//
//! PWM Mask Data Register
//
#define PWM_MSK                 0x0000005C

//
//! PWM Dead-zone Control Register
//
#define PWM_DTCTL               0x00000060

//
//! PWM Trigger Control Register
//
#define PWM_TRGADCTL            0x00000064

//
//! PWM Trigger ADC Status Register
//
#define PWM_TRGADCSTS           0x00000068

//
//! PWM Brake Control Register
//
#define PWM_BRKCTL              0x0000006C

//
//! PWM Interrupt Control Register
//
#define PWM_INTCTL              0x00000070

//
//! PWM Interrupt Enable Control Register
//
#define PWM_INTEN               0x00000074

//
//! PWM Interrupt Flag Register
//
#define PWM_INTSTS              0x00000078

//
//! PWM Output Enable Control Register
//
#define PWM_POEN                0x0000007C

//
//! PWM Capture Control Register
//
#define PWM_CAPCTL              0x00000080

//
//! PWM Capture Input Enable Control Register
//
#define PWM_CAPINEN             0x00000084

//
//! PWM Capture Status Register
//
#define PWM_CAPSTS              0x00000088

//
//! PWM Capture Rising Latch Register 0
//
#define PWM_RCAPDAT0            0x00000090

//
//! PWM Capture Falling Latch Register 0
//
#define PWM_FCAPDAT0            0x00000094

//
//! PWM Capture Rising Latch Register 1
//
#define PWM_RCAPDAT1            0x00000098

//
//! PWM Capture Falling Latch Register 1
//
#define PWM_FCAPDAT1            0x0000009C

//
//! PWM Capture Rising Latch Register 2
//
#define PWM_RCAPDAT2            0x000000A0

//
//! PWM Capture Falling Latch Register 2
//
#define PWM_FCAPDAT2            0x000000A4

//
//! PWM Capture Rising Latch Register 3
//
#define PWM_RCAPDAT3            0x000000A8

//
//! PWM Capture Falling Latch Register 3
//
#define PWM_FCAPDAT3            0x000000AC

//
//! PWM Capture Rising Latch Register 4
//
#define PWM_RCAPDAT4            0x000000B0

//
//! PWM Capture Falling Latch Register 4
//
#define PWM_FCAPDAT4            0x000000B4

//
//! PWM Capture Rising Latch Register 5
//
#define PWM_RCAPDAT5            0x000000B8

//
//! PWM Capture Falling Latch Register 5
//
#define PWM_FCAPDAT5            0x000000BC

//
//! PWM0 Synchronous Busy Status Register
//
#define PWM_SBS0                0x000000E0

//
//! PWM1 Synchronous Busy Status Register
//
#define PWM_SBS1                0x000000E4

//
//! PWM2 Synchronous Busy Status Register
//
#define PWM_SBS2                0x000000E8

//
//! PWM3 Synchronous Busy Status Register
//
#define PWM_SBS3                0x000000EC

//
//! PWM4 Synchronous Busy Status Register
//
#define PWM_SBS4                0x000000F0

//
//! PWM5 Synchronous Busy Status Register
//
#define PWM_SBS5                0x000000F4


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

////*****************************************************************************
////
////! \addtogroup NUC4xx_PWM_Register_Channel_Address_Offset PWM Channel Address Offset Register
////! @{
////
////*****************************************************************************
//
////
////! PWM Channel 0 Group A Group offset address
////
//#define PWM_CHANNEL_0           0x0000000C
//
////
////! PWM Channel 1 Group A Group offset address
////
//#define PWM_CHANNEL_1           0x00000018
//
////
////! PWM Channel 2 Group A Group offset address
////
//#define PWM_CHANNEL_2           0x00000024
//
////
////! PWM Channel 3 Group A Group offset address
////
//#define PWM_CHANNEL_3           0x00000030
//
//#define PWM_CHANNEL_X_O_CNR     0x00000000
//#define PWM_CHANNEL_X_O_CMR     0x00000004
//#define PWM_CHANNEL_X_O_PDR     0x00000008
//
////*****************************************************************************
////
////! @}
////
////*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_PPR PWM Prescaler Register(PWM_PPR)
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
//! PWM Counter Base-Clock Prescale For PWM Pair Of Channel 4 And Channel 5 mask
//
#define PWM_PPR_CP45_M         0x00FF0000

//
//! PWM Counter Base-Clock Prescale For PWM Pair Of Channel 4 And Channel 5 shift
//
#define PWM_PPR_CP45_S         16


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_CSR PWM Clock Select Register(PWM_CSR)
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

//
//! PWM Timer 4 Clock Source Selection (PWM timer 4 for group A) mask
//
#define PWM_CSR_CSR4_M          0x00070000

//
//! Select clock input for PWM timer.Input clock divided by 2
//
#define PWM_CSR_CSR4_2          0x00000000

//
//! Select clock input for PWM timer.Input clock divided by 4
//
#define PWM_CSR_CSR4_4          0x00001000

//
//! Select clock input for PWM timer.Input clock divided by 8
//
#define PWM_CSR_CSR4_8          0x00002000

//
//! Select clock input for PWM timer.Input clock divided by 16
//
#define PWM_CSR_CSR4_16         0x00003000

//
//! Select clock input for PWM timer.Input clock divided by 1
//
#define PWM_CSR_CSR4_1          0x00004000

//
//! PWM Timer 4 Clock Source Selection (PWM timer 4 for group A) shift
//
#define PWM_CSR_CSR4_S          16

//
//! PWM Timer 4 Clock Source Selection (PWM timer 4 for group A) mask
//
#define PWM_CSR_CSR5_M          0x00700000

//
//! Select clock input for PWM timer.Input clock divided by 2
//
#define PWM_CSR_CSR5_2          0x00000000

//
//! Select clock input for PWM timer.Input clock divided by 4
//
#define PWM_CSR_CSR5_4          0x00001000

//
//! Select clock input for PWM timer.Input clock divided by 8
//
#define PWM_CSR_CSR5_8          0x00002000

//
//! Select clock input for PWM timer.Input clock divided by 16
//
#define PWM_CSR_CSR5_16         0x00003000

//
//! Select clock input for PWM timer.Input clock divided by 1
//
#define PWM_CSR_CSR5_1          0x00004000

//
//! PWM Timer 5 Clock Source Selection (PWM timer 5 for group A) shift
//
#define PWM_CSR_CSR5_S          20

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_CTL PWM Control Register(PWM_CTL)
//! @{
//
//*****************************************************************************

//
//! ICE Debug Mode Acknowledge Disable Control (Write Protect)
//
#define PWM_CTL_DBGTRIOFF       BIT_32_31

//
//! PWM Counter Operation Aligned Type
//
#define PWM_CTL_CNTTYPE_M       BIT_MASK(32,29,24)
#define PWM_CTL_CNTTYPE_S       24

//
//! PWM Counter Operation Mode
//
#define PWM_CTL_CNTMODE_M       BIT_MASK(32,21,16)
#define PWM_CTL_CNTMODE_S       16

//
//! Synchronous Mode Enable Control
//
#define PWM_CTL_SYNCEN          BIT_32_15

//
//! PWM Output Polar Inverse Enable Control
//
#define PWM_CTL_PINV_M          BIT_MASK(32,13,8)
#define PWM_CTL_PINV_S          8

//
//! Group Mode Enable Control
//
#define PWM_CTL_GROUPEN         BIT_32_7

//
//! PWM Output Mode
//
#define PWM_CTL_OUTMODE         BIT_32_6

//
//! PWM Comparator Output Inverter Enable Control
//
#define PWM_CTL_CMPINV_M        BIT_MASK(32,5,0)
#define PWM_CTL_CMPINV_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_CNTEN PWM Enable Control Register 0(PWM_CNTEN)
//! @{
//
//*****************************************************************************

//
//! PWM Counter Enable Control mask
//
#define PWM_CNTEN_CNTEN_M       0x0000003F

//
//! PWM Counter Enable Control shift
//
#define PWM_CNTEN_CNTEN_S       0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_PERIOD0 PWM Period Register 0-5(PWM_PERIOD0)
//! @{
//
//*****************************************************************************

//
//! PWM Timer Period Value mask
//
#define PWM_PERIOD_M            0x0000FFFF

//
//! PWM Timer Period Value shift
//
#define PWM_PERIOD_S            0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_CMPDAT5-0 PWM Comparator Register 0-5(PWM_CMPDAT5-0)
//! @{
//
//*****************************************************************************

//
//! PWM Timer Compare Value mask
//
#define PWM_CMPDAT_CMP_M        0x0000FFFF

//
//! PWM Timer Compare Value shift
//
#define PWM_CMPDAT_CMP_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_CNT5-0 PWM Data Register 3(PWM_CNT5-0)
//! @{
//
//*****************************************************************************

//
//! PWM Timer Data Value mask
//
#define PWM_CNT_CNT_M           0x0000FFFF

//
//! PWM Timer Data Value shift
//
#define PWM_CNT_CNT_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_MSKEN PWM Mask Control Register 0(PWM_MSKEN)
//! @{
//
//*****************************************************************************

//
//! PWM Mask Control Register mask
//
#define PWM_MSKEN_MSKEN_M       0x0000003F

//
//! PWM Mask Control Register shift
//
#define PWM_MSKEN_MSKEN_S       0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_MSK PWM Mask Data Register 1(PWM_MSK)
//! @{
//
//*****************************************************************************

//
//! PWM Mask Data Register mask
//
#define PWM_MSK_MSKDAT_M        0x0000FFFF

//
//! PWM Mask Data Register shift
//
#define PWM_MSK_MSKDAT_S        0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_DTCTL PWM Dead-zone Control Register 2(PWM_DTCTL)
//! @{
//
//*****************************************************************************

//
//! Dead-Zone Enable Control For PWM Pair Of Channel 4 And Channel 5
//
#define PWM_DTCTL_DTEN45        BIT_32_30

//
//! Dead-Zone Enable Control For PWM Pair Of Channel 2 And Channel 3
//
#define PWM_DTCTL_DTEN23        BIT_32_29

//
//! Dead-Zone Enable Control For PWM Pair Of Channel 0 And Channel 1
//
#define PWM_DTCTL_DTEN01        BIT_32_28

//
//! Dead-Zone Generator Divider
//
#define PWM_DTCTL_DTDIV_M       BIT_MASK(32,25,24)

//
//! Dead-Zone Generator Divider shift
//
#define PWM_DTCTL_DTDIV_S       24

//
//! Dead-Zone Interval For PWM Pair Of Channel 4 And Channel 5
//
#define PWM_DTCTL_DTCNT45_M     0x00FF0000

//
//! Dead-Zone Interval For PWM Pair Of Channel 4 And Channel 5 shift
//
#define PWM_DTCTL_DTCNT45_S     16

//
//! Dead-Zone Interval For PWM Pair Of Channel 2 And Channel 3
//
#define PWM_DTCTL_DTCNT23_M     0x0000FF00

//
//! Dead-Zone Interval For PWM Pair Of Channel 2 And Channel 3
//
#define PWM_DTCTL_DTCNT23_S     8

//
//! Dead-Zone Interval For PWM Pair Of Channel 0 And Channel 1
//
#define PWM_DTCTL_DTCNT01_M     0x000000FF

//
//! Dead-Zone Interval For PWM Pair Of Channel 0 And Channel 1
//
#define PWM_DTCTL_DTCNT01_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_TRGADCTL PWM Trigger Control Register 3 (PWM_TRGADCTL)
//! @{
//
//*****************************************************************************

//
//! PWM Rising Edge Point Trigger Enable Control mask
//
#define PWM_TRGADCTL_RTRGEN_M   BIT_MASK(32,29,24)

//
//! PWM Rising Edge Point Trigger Enable Control shift
//
#define PWM_TRGADCTL_RTRGEN_S   24

//
//! PWM Falling Edge Point Trigger Enable Control mask
//
#define PWM_TRGADCTL_FTRGEN_M   BIT_MASK(32,21,16)

//
//! PWM Falling Edge Point Trigger Enable Control shift
//
#define PWM_TRGADCTL_FTRGEN_S   16

//
//! PWM Center Point Trigger Enable Control mask
//
#define PWM_TRGADCTL_CTRGEN_M   BIT_MASK(32,13,8)

//
//! PWM Center Point Trigger Enable Control shift
//
#define PWM_TRGADCTL_CTRGEN_S   8

//
//! PWM Period Point Trigger Enable Control mask
//
#define PWM_TRGADCTL_PTRGEN_M   BIT_MASK(32,5,0)

//
//! PWM Period Point Trigger Enable Control shift
//
#define PWM_TRGADCTL_PTRGEN_S   0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_TRGADCSTS PWM Trigger Indicator Register (PWM_TRGADCSTS)
//! @{
//
//*****************************************************************************

//
//! PWM Rising Edge Point Trigger Indicator mask
//
#define PWM_TRGADCSTS_RTRGF_M   BIT_MASK(32,29,24)

//
//! PWM Rising Edge Point Trigger Indicator shift
//
#define PWM_TRGADCSTS_RTRGF_S   24

//
//! PWM Falling Edge Point Trigger Indicator mask
//
#define PWM_TRGADCSTS_FTRGF_M   BIT_MASK(32,21,16)

//
//! PWM Falling Edge Point Trigger Indicator shift
//
#define PWM_TRGADCSTS_FTRGF_S   16

//
//! PWM Center Point Trigger Flag mask
//
#define PWM_TRGADCSTS_CTRGF_M   BIT_MASK(32,13,8)

//
//! PWM Center Point Trigger Flag shift
//
#define PWM_TRGADCSTS_CTRGF_S   8

//
//! PWM Period Point Trigger Flag mask
//
#define PWM_TRGADCSTS_PTRGF_M   BIT_MASK(32,5,0)

//
//! PWM Period Point Trigger Flag shift
//
#define PWM_TRGADCSTS_PTRGF_S   8

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_BRKCTL PWM Brake Control Register(PWM_BRKCTL)
//! @{
//
//*****************************************************************************

//
//! PWM Brake Output Data Register mask
//
#define PWM_BRKCTL_BKOD_M       BIT_MASK(32,29,24)

//
//! PWM Brake Output Data Register shift
//
#define PWM_BRKCTL_BKOD_S       24

//
//! Low-Level Detection Trigger PWM Brake Function 1 Enable Control
//
#define PWM_BRKCTL_LVDBKEN      BIT_32_19

//
//! CPO2 Digital Output As Brake 0 Source Enable Control
//
#define PWM_BRKCTL_CPO2BKEN     BIT_32_18

//
//! CPO1 Digital Output As Brake 0 Source Enable Control
//
#define PWM_BRKCTL_CPO1BKEN     BIT_32_17

//
//! CPO0 Digital Output As Brake 0 Source Enable Control
//
#define PWM_BRKCTL_CPO0BKEN     BIT_32_16


//
//! Brake 1 (BKPx1 Pin) Edge Detector Filter Clock Selection mask
//
#define PWM_BRKCTL_BRK1NFSEL_M  BIT_MASK(32,15,14)

//
//! Brake 1 (BKPx1 Pin) Edge Detector Filter Clock Selection shift
//
#define PWM_BRKCTL_BRK1NFSEL_S  14

//
//! Brake Function 1 Source Selection mask
//
#define PWM_BRKCTL_BK1SELL_M    BIT_MASK(32,13,12)

//
//! Brake Function 1 Source Selection shift
//
#define PWM_BRKCTL_BK1SEL_S     12


//
//! Inverse BKP1 State
//
#define PWM_BRKCTL_BRK1INV      BIT_32_10

//
//! PWM Brake 1 Noise Filter Disable Control
//
#define PWM_BRKCTL_BRK1NFDIS    BIT_32_9

//
//! Brake1 Function Enable Control
//
#define PWM_BRKCTL_BRKP1EN      BIT_32_8

//
//! Brake 0 (BKPx0 Pin) Edge Detector Filter Clock Selection mask
//
#define PWM_BRKCTL_BRK0NFSEL_M  BIT_MASK(32,7,6)

//
//! Brake 0 (BKPx0 Pin) Edge Detector Filter Clock Selection shift
//
#define PWM_BRKCTL_BRK0NFSEL_S  6

//
//! Inverse BKP0 State
//
#define PWM_BRKCTL_BRK0INV      BIT_32_2

//
//! PWM Brake 0 Noise Filter Disable Control
//
#define PWM_BRKCTL_BRK0NFDIS    BIT_32_1

//
//! Brake0 Function Enable Control
//
#define PWM_BRKCTL_BRKP0EN      BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_INTCTL PWM Interrupt Control Register 2(PWM_INTCTL)
//! @{
//
//*****************************************************************************

//
//! PWM Duty Interrupt Type Selection mask
//
#define PWM_INTCTL_DINTTYPE_M   BIT_MASK(32,13,8)

//
//! PWM Duty Interrupt Type Selection shift
//
#define PWM_INTCTL_DINTTYPE_S   0

//
//! PWM Period Interrupt Type Selection mask
//
#define PWM_INTCTL_PINTTYPE_M   BIT_MASK(32,5,0)

//
//! PWM Period Interrupt Type Selection shift
//
#define PWM_INTCTL_PINTTYPE_S   0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_INTEN PWM Interrupt Enable Control Register 3(PWM_INTEN)
//! @{
//
//*****************************************************************************

//
//! Falling Latch Interrupt Enable Control mask
//
#define PWM_INTEN_FLIEN_M       BIT_MASK(32,29,24)

//
//! Falling Latch Interrupt Enable Control shift
//
#define PWM_INTEN_FLIEN_S       24


//
//! Rising Latch Interrupt Enable Control mask
//
#define PWM_INTEN_RLIEN_M       BIT_MASK(32,21,16)

//
//! Rising Latch Interrupt Enable Control shift
//
#define PWM_INTEN_RLIEN_S       16

//
//! Duty Interrupt Enable Control mask
//
#define PWM_INTEN_DIEN_M        BIT_MASK(32,13,8)

//
//! Duty  Interrupt Enable Control shift
//
#define PWM_INTEN_DIEN_S        8

//
//! Brake0 And Brak1 Interrupt Enable Control
//
#define PWM_INTEN_BRKIEN        BIT_32_6

//
//! Period Interrupt Enable Control mask
//
#define PWM_INTEN_PIEN_M        BIT_MASK(32,5,0)

//
//! Period  Interrupt Enable Control shift
//
#define PWM_INTEN_PIEN_S        0



//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_INTSTS PWM Interrupt Flag Register(PWM_INTSTS)
//! @{
//
//*****************************************************************************

//
//! Capture Falling Latch Interrupt Flag
//
#define PWM_INTSTS_CFLIF_M      BIT_MASK(32,29,24)
#define PWM_INTSTS_CFLIF_S      24

//
//! Brake 1 Status (Read Only)
//
#define PWM_INTSTS_BRKSTS1      BIT_32_23

//
//! Brake 0 Status (Read Only)
//
#define PWM_INTSTS_BRKSTS0      BIT_32_22

//
//! Capture Rising Latch Interrupt Flag
//
#define PWM_INTSTS_CRLIF_M      BIT_MASK(32,21,16)
#define PWM_INTSTS_CRLIF_S      16

//
//! PWM Brake0 Locked
//
#define PWM_INTSTS_BRKLK0       BIT_32_14

//
//! PWM Duty Interrupt Flag
//
#define PWM_INTSTS_DIF_M        BIT_MASK(32,13,8)
#define PWM_INTSTS_DIF_S        8

//
//! PWM Brake1 Flag
//
#define PWM_INTSTS_BRKIF1       BIT_32_7

//
//! PWM Brake0 Flag
//
#define PWM_INTSTS_BRKIF0       BIT_32_6

//
//! PWM Period Interrupt Flag
//
#define PWM_INTSTS_PIF_M        BIT_MASK(32,5,0)
#define PWM_INTSTS_PIF_S        0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_POEN PWM Output Enable Register(PWM_POEN)
//! @{
//
//*****************************************************************************

//
//! PWM Period Interrupt Flag
//
#define PWM_POEN_POEN_M         BIT_MASK(32,5,0)
#define PWM_POEN_POEN_S         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_CAPCTL PWM Capture Control Register(PWM_CAPCTL)
//! @{
//
//*****************************************************************************

//
//! Falling Latch Reload Enable Control
//
#define PWM_CAPCTL_FCRLDEN_M    BIT_MASK(32,29,24)
#define PWM_CAPCTL_FCRLDEN_S    24

//
//! Rising Latch Reload Enable Control
//
#define PWM_CAPCTL_RCRLDEN_M    BIT_MASK(32,21,16)
#define PWM_CAPCTL_RCRLDEN_S    16

//
//! Capture Inverter Enable Control
//
#define PWM_CAPCTL_CAPINV_M     BIT_MASK(32,13,8)
#define PWM_CAPCTL_CAPINV_S     8

//
//! Capture Function Enable Control
//
#define PWM_CAPCTL_CAPEN_M      BIT_MASK(32,5,0)
#define PWM_CAPCTL_CAPEN_S      0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_CAPINEN PWM Capture Input Enable Register 0(PWM_CAPINEN)
//! @{
//
//*****************************************************************************

//
//! Capture Input Enable Control
//
#define PWM_CAPINEN_CAPINEN_M   BIT_MASK(32,5,0)
#define PWM_CAPINEN_CAPINEN_S   0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_CAPSTS PWM Capture Status Register 2(PWM_CAPSTS)
//! @{
//
//*****************************************************************************

//
//! Rising Latch Interrupt Flag Overrun Status
//
#define PWM_CAPSTS_FLIFOV_M     BIT_MASK(32,13,8)
#define PWM_CAPSTS_FLIFOV_S     8

//
//! Rising Latch Interrupt Flag Overrun Status
//
#define PWM_CAPSTS_RLIFOV_M     BIT_MASK(32,5,0)
#define PWM_CAPSTS_RLIFOV_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_RCAPDAT5-0 PWM Capture Rising Latch Register5-0(PWM_RCAPDAT5-0)
//! @{
//
//*****************************************************************************

//
//! Capture Rising Latch Register mask
//
#define PWM_RCAPDAT_M           0x0000FFFF

//
//! Capture Rising Latch Register shift
//
#define PWM_RCAPDAT_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_PWM_FCAPDAT5-0 PWM Capture Falling Latch Register 1(PWM_FCAPDAT5-0)
//! @{
//
//*****************************************************************************

//
//! Capture Falling Latch Register mask
//
#define PWM_FCAPDAT_M           0x0000FFFF

//
//! Capture Falling Latch Register shift
//
#define PWM_FCAPDAT_S           0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_SYNCBUSY0 PWM Synchronous Busy Status status Register(PWM_SYNCBUSY0)
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
//! \addtogroup NUC4xx_PWM_Register_SYNCBUSY1 PWM Synchronous Busy Status status Register(PWM_SYNCBUSY1)
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
//! \addtogroup NUC4xx_PWM_Register_SYNCBUSY2 PWM Synchronous Busy Status status Register(PWM_SYNCBUSY2)
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
//! \addtogroup NUC4xx_PWM_Register_SYNCBUSY3 PWM Synchronous Busy Status status Register(PWM_SYNCBUSY3)
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
//! \addtogroup NUC4xx_PWM_Register_SYNCBUSY4 PWM Synchronous Busy Status status Register(PWM_SYNCBUSY4)
//! @{
//
//*****************************************************************************

//
//! PWM Synchronous Busy
//
#define PWM_SYNCBUSY4_BUSY      BIT_32_0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_PWM_Register_SYNCBUSY5 PWM Synchronous Busy Status status Register(PWM_SYNCBUSY5)
//! @{
//
//*****************************************************************************

//
//! PWM Synchronous Busy
//
#define PWM_SYNCBUSY5_BUSY      BIT_32_0

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




