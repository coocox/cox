//*****************************************************************************
//
//! \file rtc.h
//! \brief Prototypes for the RTC Driver.
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
//*****************************************************************************

#ifndef __LPC17XX_RTC_H__
#define __LPC17XX_RTC_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

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
//! \addtogroup LPC17xx_RTC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup RTC_INT_Type RTC Interrupt Type
//! \brief Values that show RTC Interrupt Type
//! Values that can be passed to RTCIntEnable(),RTCIntDisable() and
//! RTCIntClear().
//! @{
//
//*****************************************************************************

//
//! Time Tick Interrupt
//
#define RTC_INT_SECOND          0x00000001

//
//! Alarm Interrupt
//
#define RTC_INT_ALARM           0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup RTC_Time_Type RTC Time Type
//! \brief Values that show RTC Time Type
//! Values that can be passed to RTCTimeRead() and RTCTimeWrite().
//! @{
//
//*****************************************************************************

//
//! Read or write current time and date
//
#define RTC_TIME_CURRENT        0x00000001

//
//! Read or write alarm time and date
//
#define RTC_TIME_ALARM          0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup RTC_Time_Format RTC Time Format
//! \brief Values that show RTC Time Format
//! Values that can be passed to RTCTimeRead() and RTCTimeWrite().
//! @{
//
//*****************************************************************************

//
//! 24-hour time scale
//
#define RTC_TIME_24H            0x00000001

//
//! 12-hour time scale am
//
#define RTC_TIME_12H_AM         0x00000000

//
//! 12-hour time scale pm
//
#define RTC_TIME_12H_PM         0x00000010

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_RTC_INT_CFG  RTC interrupt configure mode.
//! \brief Values that show RTC Interrupt Status
//! Values that can be passed to RTCIntCfg() .
//! @{
//
//*****************************************************************************

//! Enable second increment interrupt.
#define INT_SEC_EN              BIT_32_0

//! Enable minute increment interrupt.
#define INT_MIN_EN              BIT_32_1

//! Enable hour increment interrupt.
#define INT_HOUR_EN             BIT_32_2

//! Enable day of month increment interrupt.
#define INT_DOM_EN              BIT_32_3

//! Enable day of week increment interrupt.
#define INT_DOW_EN              BIT_32_4

//! Enable day of year increment interrupt.
#define INT_DOY_EN              BIT_32_5

//! Enable month increment interrupt.
#define INT_MON_EN              BIT_32_6

//! Enable year increment interrupt.
#define INT_YEAR_EN             BIT_32_7

//! Disable second increment interrupt.
#define INT_SEC_DIS             BIT_32_8

//! Disable minute increment interrupt.
#define INT_MIN_DIS             BIT_32_9

//! Disable hour increment interrupt.
#define INT_HOUR_DIS            BIT_32_10

//! Disable day of month increment interrupt.
#define INT_DOM_DIS             BIT_32_11

//! Disable day of week increment interrupt.
#define INT_DOW_DIS             BIT_32_12

//! Disable day of year increment interrupt.
#define INT_DOY_DIS             BIT_32_13

//! Disable month increment interrupt.
#define INT_MON_DIS             BIT_32_14

//! Disable year increment interrupt.
#define INT_YEAR_DIS            BIT_32_15


//! Enable second alarm match interrupt.
#define INT_ALARM_SEC_EN        BIT_32_24

//! Enable minute alarm match interrupt.
#define INT_ALARM_MIN_EN        BIT_32_25

//! Enable hour alarm match interrupt.
#define INT_ALARM_HOUR_EN       BIT_32_26

//! Enable day of month alarm match interrupt.
#define INT_ALARM_DOM_EN        BIT_32_27

//! Enable day of week alarm match interrupt.
#define INT_ALARM_DOW_EN        BIT_32_28

//! Enable day of year alarm match interrupt.
#define INT_ALARM_DOY_EN        BIT_32_29

//! Enable month alarm match interrupt.
#define INT_ALARM_MON_EN        BIT_32_30

//! Enable year alarm match interrupt.
#define INT_ALARM_YEAR_EN       BIT_32_31


//! Disable second alarm match interrupt.
#define INT_ALARM_SEC_DIS       BIT_32_16

//! Disable minute alarm match interrupt.
#define INT_ALARM_MIN_DIS       BIT_32_17

//! Disable hour alarm match interrupt.
#define INT_ALARM_HOUR_DIS      BIT_32_18

//! Disable day of month alarm match interrupt.
#define INT_ALARM_DOM_DIS       BIT_32_19

//! Disable day of week alarm match interrupt.
#define INT_ALARM_DOW_DIS       BIT_32_20

//! Disable day of year alarm match interrupt.
#define INT_ALARM_DOY_DIS       BIT_32_21

//! Disable month alarm match interrupt.
#define INT_ALARM_MON_DIS       BIT_32_22

//! Disable year alarm match interrupt.
#define INT_ALARM_YEAR_DIS      BIT_32_23

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

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __LPC17XX_RTC_H__
