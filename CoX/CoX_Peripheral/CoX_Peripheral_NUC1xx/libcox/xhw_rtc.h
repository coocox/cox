//*****************************************************************************
//
//! \file xhw_rtc.h
//! \brief Macros and defines used when accessing the RTC hardware.
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
#ifndef __XHW_RTC_H__
#define __XHW_RTC_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup RTC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_RTC_Register NUC1xx RTC Register
//! \brief Here are the detailed info of RTC registers. 
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
//! \addtogroup NUC1xx_RTC_Register_RTC_Address RTC Address Register(RTC_Register_Address)
//! \brief Defines for the bit fields in the RTC_Register_Address register.
//! @{
//
//*****************************************************************************

//
//! RTC Initiation Register (INIR)
//
#define RTC_INIR                0x40008000  

//
//! RTC Access Enable Register (AER)
//
#define RTC_AER                 0x40008004

//
//! RTC Frequency Compensation Register (FCR)
//
#define RTC_FCR                 0x40008008

//
//! RTC Time Loading Register (TLR)
//
#define RTC_TLR                 0x4000800C

//
//! RTC Calendar Loading Register (CLR)
//
#define RTC_CLR                 0x40008010

//
//! RTC Time Scale Selection Register (TSSR)
//
#define RTC_TSSR                0x40008014

//
//! RTC Day of the Week Register (DWR)
//
#define RTC_DWR                 0x40008018

//
//! RTC Time Alarm Register (TAR)
//
#define RTC_TAR                 0x4000801C

//
//! RTC Calendar Alarm Register (CAR)
//
#define RTC_CAR                 0x40008020

//
//! RTC Leap year Indication Register (LIR)
//
#define RTC_LIR                 0x40008024

//
//! RTC Interrupt Enable Register (RIER)
//
#define RTC_RIER                0x40008028

//
//! RTC Interrupt Indication Register (RIIR)
//
#define RTC_RIIR                0x4000802C
 
//
//! RTC Time Tick Register (TTR)
//
#define RTC_TTR                 0x40008030

 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_RTC_Register_RTC_INIR RTC Initiation Register(RTC_INIR)
//! \brief Defines for the bit fields in the RTC_INIR register.
//! @{
//
//*****************************************************************************

//
//! RTC Initiation mask
//
#define RTC_INIR_M              0xFFFFFFFF  

//
//! RTC Initiation shift
//
#define RTC_INIR_S              0  

//
//! RTC Active Status (Read only)
//
#define RTC_INIR_ACTIVE         0x00000001  

//
//! RTC INIT Keys
//
#define RTC_INIR_KEY            0xA5EB1357


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_RTC_Register_RTC_AER RTC Access Enable Register(RTC_AER)
//! \brief Defines for the bit fields in the RTC_AER register.
//! @{
//
//*****************************************************************************

//
//! RTC Register Access Enable Flag (Read only)
//
#define RTC_AER_ENF             0x00010000  

//
//! RTC Register Access Enable Password mask(Write only)
//
#define RTC_AER_PASSWORD_M      0x0000FFFF  

//
//! RTC Register Access Enable Password shift(Write only)
//
#define RTC_AER_PASSWORD_S      0  


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_RTC_Register_RTC_FCR RTC Frequency Compensation Register(RTC_FCR)
//! \brief Defines for the bit fields in the RTC_FCR register.
//! @{
//
//*****************************************************************************

//
//! Integer Part mask
//
#define RTC_FCR_INTEGER_M       0x00000F00  

//
//! Integer Part reference
//
#define RTC_FCR_REFERENCE       32761  

//
//! Integer Part shift
//
#define RTC_FCR_INTEGER_S       8 

//
//! Fraction Part mask
//
#define RTC_FCR_FRACTION_M      0x0000003F  

//
//! Fraction Part shift
//
#define RTC_FCR_FRACTION_S      0   


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_RTC_Register_RTC_TLR RTC Time Loading Register(RTC_TLR)
//! \brief Defines for the bit fields in the RTC_TLR register
//! @{
//
//*****************************************************************************

//
//! 10-Hour Time Digit (0~2) mask
//
#define RTC_TLR_10HR_M          0x00700000  

//
//! 10-Hour Time Digit (0~2) shift
//
#define RTC_TLR_10HR_S          20 

//
//! 1-Hour Time Digit (0~9) mask
//
#define RTC_TLR_1HR_M           0x000F0000  

//
//! 1-Hour Time Digit (0~9) shift
//
#define RTC_TLR_1HR_S           16

//
//! 10-Min Time Digit (0~5) mask
//
#define RTC_TLR_10MIN_M         0x00007000  

//
//! 10-Min Time Digit (0~5) shift
//
#define RTC_TLR_10MIN_S         12

//
//! 1-Min Time Digit (0~9) mask
//
#define RTC_TLR_1MIN_M          0x00000F00  

//
//! 1-Min Time Digit (0~9) shift
//
#define RTC_TLR_1MIN_S          8

//
//! 10-Sec Time Digit (0~5) mask
//
#define RTC_TLR_10SEC_M         0x00000070  

//
//! 10-Sec Time Digit (0~5) shift
//
#define RTC_TLR_10SEC_S         4

//
//! 1-Sec Time Digit (0~9) mask
//
#define RTC_TLR_1SEC_M          0x0000000F  

//
//! 1-Sec Time Digit (0~9) shift
//
#define RTC_TLR_1SEC_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_RTC_Register_RTC_ClR RTC Calendar Loading Register(RTC_ClR)
//! \brief Defines for the bit fields in the RTC_CLR register
//! @{
//
//*****************************************************************************

//
//! 10-Year Calendar Digit (0~9)
//
#define RTC_CLR_10YEAR_M        0x00F00000

//
//! 10-Year Calendar Digit (0~9)
//
#define RTC_CLR_10YEAR_S        20

//
//! 1-Year Calendar Digit (0~9)
//
#define RTC_CLR_1YEAR_M         0x000F0000

//
//! 1-Year Calendar Digit (0~9)
//
#define RTC_CLR_1YEAR_S         16

//
//! 10-Month Calendar Digit (0~9)
//
#define RTC_CLR_10MON_M         0x00001000

//
//! 10-Month Calendar Digit (0~9)
//
#define RTC_CLR_10MON_S         12

//
//! 1-Month Calendar Digit (0~9)
//
#define RTC_CLR_1MON_M          0x00000F00

//
//! 1-Month Calendar Digit (0~9)
//
#define RTC_CLR_1MON_S          8

//
//! 10-Day Calendar Digit (0~3)
//
#define RTC_CLR_10DAY_M         0x00000030

//
//! 10-Day Calendar Digit (0~3)
//
#define RTC_CLR_10DAY_S         4

//
//! 1-Day Calendar Digit (0~9)
//
#define RTC_CLR_1DAY_M          0x0000000F

//
//! 1-Day Calendar Digit (0~9)
//
#define RTC_CLR_1DAY_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_RTC_Register_RTC_TSSR RTC Time Scale Selection Register(RTC_TSSR)
//! \brief Defines for the bit fields in the RTC_TSSR register
//! @{
//
//*****************************************************************************
//
//! 24-Hour / 12-Hour Time Scale Selection
//
#define RTC_TSSR_24H_12H        0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_RTC_Register_RTC_O_DWR RTC Day of the Week Register(RTC_O_DWR)
//! \brief Defines for the bit fields in the RTC_0_DWR register
//! @{
//
//*****************************************************************************

//
//! Day of the Week Register
//
#define RTC_DWR_DW_M            0x00000007

//
//! Sunday of the Week Register
//
#define RTC_DWR_DW_SUNDAY       0x00000000

//
//! Monday of the Week Register
//
#define RTC_DWR_DW_MONDAY       0x00000001

//
//! Tuesday of the Week Register
//
#define RTC_DWR_DW_TUESDAY      0x00000002

//
//! Wednesday of the Week Register
//
#define RTC_DWR_DW_WEDNESDAY    0x00000003

//
//! Thursday of the Week Register
//
#define RTC_DWR_DW_THURSDAY     0x00000004

//
//! Friday of the Week Register
//
#define RTC_DWR_DW_FRIDAY       0x00000005

//
//! Saturday of the Week Register
//
#define RTC_DWR_DW_SATURDAY     0x00000006

//
//! Day of the Week Register
//
#define RTC_DWR_DW_S            0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_RTC_Register_RTC_TAR RTC Time Alarm Register(RTC_TAR)
//! \brief Defines for the bit fields in the RTC_TAR register
//! @{
//
//*****************************************************************************

//
//! 10-Hour Time Digit of Alarm Setting (0~2)
//
#define RTC_TAR_10HR_M          0x00700000

//
//! 10-Hour Time Digit of Alarm Setting (0~2)
//
#define RTC_TAR_10HR_S          20

//
//! 1-Hour Time Digit of Alarm Setting (0~9)
//
#define RTC_TAR_1HR_M           0x000F0000

//
//! 1-Hour Time Digit of Alarm Setting (0~9)
//
#define RTC_TAR_1HR_S           16

//
//! 10-Min Time Digit of Alarm Setting (0~5)
//
#define RTC_TAR_10MIN_M         0x00007000

//
//! 10-Min Time Digit of Alarm Setting (0~5)
//
#define RTC_TAR_10MIN_S         12

//
//! 1-Min Time Digit of Alarm Setting (0~9)
//
#define RTC_TAR_1MIN_M          0x0000F00

//
//! 1-Min Time Digit of Alarm Setting (0~9)
//
#define RTC_TAR_1MIN_S          8

//
//! 10-SEC Time Digit of Alarm Setting (0~5)
//
#define RTC_TAR_10SEC_M         0x00000070

//
//! 10-SEC Time Digit of Alarm Setting (0~5)
//
#define RTC_TAR_10SEC_S         12

//
//! 1-SEC Time Digit of Alarm Setting (0~9)
//
#define RTC_TAR_1SEC_M          0x000000F

//
//! 1-SEC Time Digit of Alarm Setting (0~9)
//
#define RTC_TAR_1SEC_S          0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_RTC_Register_RTC_CAR RTC Calendar Alarm Register(RTC_CAR)
//! \brief Defines for the bit fields in the RTC_CAR register
//! @{
//
//*****************************************************************************

//
//! 10-Year Calendar Digit of Alarm Setting (0~9)
//
#define RTC_CAR_10YEAR_M        0x00F00000

//
//! 10-Year Calendar Digit of Alarm Setting (0~9)
//
#define RTC_CAR_10YEAR_S        20

//
//! 1-Year Calendar Digit of Alarm Setting (0~9)
//
#define RTC_CAR_1YEAR_M         0x000F0000

//
//! 1-Year Calendar Digit of Alarm Setting (0~9)
//
#define RTC_CAR_1YEAR_S         16

//
//! 10-Month Calendar Digit of Alarm Setting (0~1)
//
#define RTC_CAR_10MON_M         0x00001000

//
//! 10-Month Calendar Digit of Alarm Setting (0~1)
//
#define RTC_CAR_10MON_S         12

//
//! 1-Month Calendar Digit of Alarm Setting (0~9)
//
#define RTC_CAR_1MON_M          0x00000F00

//
//! 1-Month Calendar Digit of Alarm Setting (0~9)
//
#define RTC_CAR_1MON_S          8

//
//! 10-Day Calendar Digit of Alarm Setting (0~3)
//
#define RTC_CAR_10DAY_M         0x00000030

//
//! 10-Day Calendar Digit of Alarm Setting (0~3)
//
#define RTC_CAR_10DAY_S         4

//
//! 1-Day Calendar Digit of Alarm Setting (0~9)
//
#define RTC_CAR_1DAY_M          0x0000000F

//
//! 1-Day Calendar Digit of Alarm Setting (0~9)
//
#define RTC_CAR_1DAY_S          0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_RTC_Register_RTC_LIR RTC Leap year Indicator Register(RTC_LIR)
//! \brief Defines for the bit fields in the RTC_LIR register
//! @{
//
//*****************************************************************************

//
//! Leap Year Indication REGISTER (Real only).
//
#define RTC_LIR_LEAP_YEAR       0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_RTC_Register_RTC_RIER RTC Interrupt Enable Register(RTC_RIER)
//! \brief Defines for the bit fields in the RTC_RIER register
//! @{
//
//*****************************************************************************

//
//! Time Tick Interrupt Enable
//
#define RTC_RIER_TIER           0x00000002

//
//! Alarm Interrupt Enable
//
#define RTC_RIER_AIER           0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_RTC_Register_RTC_RIIR RTC Interrupt Indicator Register(RTC_RIIR)
//! \brief Defines for the bit fields in the RTC_RIIR register
//! @{
//
//*****************************************************************************

//
//! RTC Time Tick Interrupt Flag
//
#define RTC_RIIR_TIF            0x00000002

//
//! RTC Alarm Interrupt Flag
//
#define RTC_RIIR_AIF            0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_RTC_Register_RTC_TTR RTC Time Tick Register(RTC_TTR)
//! \brief Defines for the bit fields in the RTC_TTR register
//! @{
//
//*****************************************************************************

//
//! RTC Timer Wake-up Function Enable
//
#define RTC_TTR_TWKE            0x00000008

//
//! The RTC time tick period for Periodic Time Tick Interrupt request.
//
#define RTC_TTR_TICK_M          0x00000007

//
//! 1 second for Periodic Time Tick Interrupt request.
//
#define RTC_TTR_TICK_1          0x00000000

//
//! 1/2 second for Periodic Time Tick Interrupt request.
//
#define RTC_TTR_TICK_1_2        0x00000001

//
//! 1/4 second for Periodic Time Tick Interrupt request.
//
#define RTC_TTR_TICK_1_4        0x00000002

//
//! 1/8 second for Periodic Time Tick Interrupt request.
//
#define RTC_TTR_TICK_1_8        0x00000003

//
//! 1/16 second for Periodic Time Tick Interrupt request.
//
#define RTC_TTR_TICK_1_16       0x00000004

//
//! 1/32 second for Periodic Time Tick Interrupt request.
//
#define RTC_TTR_TICK_1_32       0x00000005

//
//! 1/64 second for Periodic Time Tick Interrupt request.
//
#define RTC_TTR_TICK_1_64       0x00000006

//
//! 1/128 second for Periodic Time Tick Interrupt request.
//
#define RTC_TTR_TICK_1_128      0x00000007

//
//! The RTC time tick period for Periodic Time Tick Interrupt request.
//
#define RTC_TTR_TICK_S          0

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

#endif // __XHW_RTC_H__


