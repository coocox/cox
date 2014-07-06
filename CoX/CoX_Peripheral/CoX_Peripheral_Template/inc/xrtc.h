//*****************************************************************************
//
//! \file      xrtc.h
//! \brief     Prototypes for the RTC Driver.
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

#ifndef __XRTC_H__
#define __XRTC_H__

#include "rtc.h"
#include "CoX_base.h"

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
//! \addtogroup CoX_Peripheral_Interface
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xRTC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xRTC_INT_Type xRTC Interrupt Type
//! \brief      Values that show xRTC Interrupt Type
//!
//! \section    xRTC_INT_Type_Section 1. Where to use this group
//!             Values that can be passed to xRTCIntEnable(),xRTCIntDisable()
//!             and xRTCIntClear() as the ulIntFlags parameter.
//!
//! \section    xRTC_INT_Type_CoX     2. CoX Port Details
//!
//! |  xRTC Interrupts         |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xRTC_INT_SECOND         |    Mandatory   |            Y           |
//! |  xRTC_INT_ALARM          |  Non-Mandatory |            Y           |
//!
//! @{
//
//*****************************************************************************
#define xRTC_INT_SECOND         RTC_INT_SECOND
#define xRTC_INT_ALARM          RTC_INT_ALARM
#define xRTC_INT_OVERFLOW       RTC_INT_OVERFLOW



//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xRTC_INT_Event xRTC Interrupt Event
//! \brief      Values that show xRTC Interrupt Event
//!
//! \section    xRTC_INT_Event_Section 1. Where to use this group
//!             RTC Event/Error Flag, Used by IntHandle's Event Callback
//!             Function as ulMsgParam parmeter. User Callback function can
//!             user this to detect what event happened.
//!
//! \section    xRTC_INT_Event_CoX     2. CoX Port Details
//!
//! |  xRTC Event              |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xRTC_EVENT_SECOND       |    Mandatory   |            Y           |
//! |  xRTC_EVENT_ALARM        |  Non-Mandatory |            Y           |
//!
//! @{
//
//*****************************************************************************
#define xRTC_EVENT_SECOND       RTC_EVENT_SECOND
#define xRTC_EVENT_ALARM        RTC_EVENT_ALARM
#define xRTC_EVENT_OVERFLOW     RTC_EVENT_OVERFLOW

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xRTC_Day_Week xRTC Day Week
//! \brief      Values that show xRTC Day Week
//!
//! \section    xRTC_Day_Week_Section 1. Where to use this group
//!             Values that can be passed to xRTCTimeRead(),xRTCTimeWrite()
//!             as the tTime.ulWDay parameter.
//!
//! \section    xRTC_Day_Week_CoX     2. CoX Port Details
//!
//! |  tTime.ulWDay            |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xRTC_WEEK_SUNDAY        |    Mandatory   |            Y           |
//! |  xRTC_WEEK_MONDAY        |    Mandatory   |            Y           |
//! |  xRTC_WEEK_TUESDAY       |    Mandatory   |            Y           |
//! |  xRTC_WEEK_WEDNESDAY     |    Mandatory   |            Y           |
//! |  xRTC_WEEK_THURSDAY      |    Mandatory   |            Y           |
//! |  xRTC_WEEK_FRIDAY        |    Mandatory   |            Y           |
//! |  xRTC_WEEK_SATURDAY      |    Mandatory   |            Y           |
//!
//! @{
//
//*****************************************************************************

//
//! Sunday
//
#define xRTC_WEEK_SUNDAY        0

//
//! Monday
//
#define xRTC_WEEK_MONDAY        1

//
//! Tuesday
//
#define xRTC_WEEK_TUESDAY       2

//
//! Wednesday
//
#define xRTC_WEEK_WEDNESDAY     3

//
//! Thursday
//
#define xRTC_WEEK_THURSDAY      4

//
//! Friday
//
#define xRTC_WEEK_FRIDAY        5

//
//! Saturday
//
#define xRTC_WEEK_SATURDAY      6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup xRTC_Year_Offset xRTC Year Offset
//! \brief      Values that show xRTC Year Offset
//!
//! \section    xRTC_Year_Offset_Section 1. Where to use this group
//!             Values that is the offset of the year.
//!
//! \section    xRTC_Year_Offset_CoX     2. CoX Port Details
//! @{
//
//*****************************************************************************

//
//! Initiative time is 00:00:00 1/1 / 2000
//
#define xRTC_YEAR_OFFSET        0x000007D0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xRTC_Time_Type xRTC Time Type
//! \brief      Values that show xRTC Time Type
//!
//! \section    xRTC_Year_Offset_Section 1. Where to use this group
//!             Values that can be passed to RTCTimeRead() and RTCTimeWrite()
//!             as the ulTimeAlarm parameter.
//!
//! \section    xRTC_Year_Offset_CoX     2. CoX Port Details
//!
//! |  ulTimeAlarm             |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xRTC_TIME_CURRENT       |    Mandatory   |            Y           |
//! |  xRTC_TIME_ALARM         |  Non-Mandatory |            Y           |
//!
//! @{
//
//*****************************************************************************

//
//! Read or write current time and date
//
#define xRTC_TIME_CURRENT       RTC_TIME_CURRENT

//
//! Read or write alarm time and date
//
#define xRTC_TIME_ALARM         RTC_TIME_ALARM

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xRTC_Exported_Types xRTC Exported Types
//! @{
//
//*****************************************************************************

//! xRTC Time and Calendar Definition definitions
typedef struct
{
    //
    //! Seconds of time
    //
    unsigned long ulSecond;

    //
    //! Minutes of time
    //
    unsigned long ulMinute;

    //
    //! Hours of time
    //
    unsigned long ulHour;

    //
    //! Day of Month
    //
    unsigned long ulMDay;

    //
    //! Month
    //
    unsigned long ulMonth;

    //
    //! Years
    //
    unsigned long ulYear;

    //
    //! Day of Week
    //
    unsigned long ulWDay;

    //
    //! Time format 24 hour or 12 hour
    //
    unsigned long ulFormat;
} xtTime;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xRTC_Exported_APIs xRTC API
//! \brief      xRTC API Reference.
//!
//! \section    xRTC_Exported_APIs_Port CoX Port Details
//!
//! |      xRTC API            |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! | \ref xRTCTimeInit        |    Mandatory   |            Y           |
//! | \ref xRTCTimeRead        |    Mandatory   |            Y           |
//! | \ref xRTCTimeWrite       |    Mandatory   |            Y           |
//! | \ref xRTCIntEnable       |    Mandatory   |            Y           |
//! | \ref xRTCIntCallbackInit |    Mandatory   |            Y           |
//! | \ref xRTCIntDisable      |    Mandatory   |            Y           |
//! | \ref xRTCStart           |    Mandatory   |            Y           |
//! | \ref xRTCStop            |    Mandatory   |            Y           |
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief  Initializes the RTC peripheral.
//!         This function is to initializes the RTC peripheral.
//!
//! \param  None.
//!
//! \return The result of operation.
//!         - xtrue  Initializes successfully
//!         - xfalse Initializes fail
//
//*****************************************************************************
extern xtBoolean xRTCTimeInit();


//*****************************************************************************
//
//! \brief  Read current date/time or alarm date/time from RTC setting.
//!         This function is to Read current date/time or alarm date/time from RTC
//!         setting.
//!
//! \param  [out] xtTime specifies the point of time and data.
//! \param  [in]  ulTimeAlarm specifies which will be read current time or alarm time.
//!               This parameter is the one of any of the following:
//!               - \ref xRTC_TIME_CURRENT  Get Current time.
//!               - \ref xRTC_TIME_ALARM    Get System Alarm.
//!
//! \return None.
//
//*****************************************************************************
extern void xRTCTimeRead(xtTime * pxtTime, unsigned long ulTimeAlarm);

//*****************************************************************************
//
//! \brief  Write current date/time or alarm date/time to RTC Module.
//!         This function is to configure current date/time or alarm date/time.
//!
//! \param  [in] xtTime specifies the point of time and data.
//! \param  [in]  ulTimeAlarm specifies which will be read current time or alarm time.
//!               This parameter is the one of any of the following:
//!               - \ref xRTC_TIME_CURRENT  Get Current time.
//!               - \ref xRTC_TIME_ALARM    Get System Alarm.
//!
//! \return None.
//
//*****************************************************************************
extern void xRTCTimeWrite(xtTime * pxtTime, unsigned long ulTimeAlarm);

//*****************************************************************************
//
//! \brief  Enable the time tick or alarm interrupt of RTC.
//!         This function is to enable the time tick or alarm interrupt of RTC.
//!
//! \param  [in] ulIntType is the bit mask of the interrupt sources to be enabled.
//!              This value can be the logical OR of the following value:
//!              - \ref xRTC_INT_SECOND      Tick interrupt
//!              - \ref xRTC_INT_ALARM       Alarm interrupt
//!
//! \return None.
//
//*****************************************************************************
extern void xRTCIntEnable(unsigned long ulIntType);

//*****************************************************************************
//
//! \brief  Disable the time tick or alarm interrupt of RTC.
//!         This function is to disable the time tick or alarm interrupt of RTC.
//!
//! \param  [in] ulIntType is the bit mask of the interrupt sources to be enabled.
//!              This value can be the logical OR of the following value:
//!              - \ref xRTC_INT_SECOND      Tick interrupt
//!              - \ref xRTC_INT_ALARM       Alarm interrupt
//!
//! \return None.
//
//*****************************************************************************
extern void xRTCIntDisable(unsigned long ulIntType);

//*****************************************************************************
//
//! \brief  Register user ISR callback function for the RTC.
//!
//! \param  [in] xtPortCallback is user ISR callback function for the RTC.
//!
//! \return None.
//
//*****************************************************************************
extern void xRTCIntCallbackInit(xtEventCallback xtRTCCallback);


//*****************************************************************************
//
//! \brief  Start the RTC timer.
//!
//! \param  None.
//!
//! \return None.
//
//*****************************************************************************
extern void xRTCStart();


//*****************************************************************************
//
//! \brief  Stop the RTC timer.
//!
//! \param  None.
//!
//! \return None.
//
//*****************************************************************************
extern void xRTCStop();


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

#endif // __XRTC_H__

