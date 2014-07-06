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

#ifndef __RTC_H__
#define __RTC_H__

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
//! \addtogroup NUC4xx_RTC
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
#define RTC_INT_TIME_TICK       0x00000002

//
//! Alarm Interrupt
//
#define RTC_INT_ALARM           0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup RTC_Day_Week RTC Day Week
//! \brief Values that show RTC Day Week
//! Values that can be passed to .
//! @{
//
//*****************************************************************************

//
//! Sunday
//
#define RTC_WEEK_SUNDAY         0x00000000

//
//! Monday
//
#define RTC_WEEK_MONDAY         0x00000001

//
//! Tuesday
//
#define RTC_WEEK_TUESDAY        0x00000002

//
//! Wednesday
//
#define RTC_WEEK_WEDNESDAY      0x00000003

//
//! Thursday
//
#define RTC_WEEK_THURSDAY       0x00000004

//
//! Friday
//
#define RTC_WEEK_FRIDAY         0x00000005

//
//! Saturday
//
#define RTC_WEEK_SATURDAY       0x00000006

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup RTC_Year_Offset RTC Year Offset
//! \brief Values that show RTC Year Offset
//! Values that is the offset of the year.
//! @{
//
//*****************************************************************************

//
//! Initiative time is 00:00:00 1/1 / 2000
//
#define RTC_YEAR_OFFSET         0x000007D0

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
#define RTC_TIME_CURRENT        0x00000000

//
//! Read or write alarm time and date
//
#define RTC_TIME_ALARM          0x00000001

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
//! \addtogroup RTC_Tick_Mode RTC Tick Mode
//! \brief Values that show RTC Tick Mode
//! Values that can be passed to RTCTickModeSet().
//! @{
//
//*****************************************************************************

//
//! 1 second for Periodic Time Tick Interrupt request.
//
#define RTC_TIME_TICK_1         0x00000000

//
//! 1/2 second for Periodic Time Tick Interrupt request.
//
#define RTC_TIME_TICK_1_2       0x00000001

//
//! 1/4 second for Periodic Time Tick Interrupt request.
//
#define RTC_TIME_TICK_1_4       0x00000002

//
//! 1/8 second for Periodic Time Tick Interrupt request.
//
#define RTC_TIME_TICK_1_8       0x00000003

//
//! 1/16 second for Periodic Time Tick Interrupt request.
//
#define RTC_TIME_TICK_1_16      0x00000004

//
//! 1/32 second for Periodic Time Tick Interrupt request.
//
#define RTC_TIME_TICK_1_32      0x00000005

//
//! 1/64 second for Periodic Time Tick Interrupt request.
//
#define RTC_TIME_TICK_1_64      0x00000006

//
//! 1/128 second for Periodic Time Tick Interrupt request.
//
#define RTC_TIME_TICK_1_128     0x00000007

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_RTC_Exported_Types
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! RTC Time and Calendar Definition definitions
//
//*****************************************************************************
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
} tTime;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_RTC_Exported_APIs NUC4xx API
//! \brief NUC4xx RTC API Reference.
//! @{
//
//*****************************************************************************

extern xtBoolean RTCTimeInit(void);
extern void RTCTimeRead(tTime *tTime, unsigned long ulTimeAlarm);
extern void RTCTimeWrite(tTime *tTime, unsigned long ulTimeAlarm);
extern void RTCIntEnable(unsigned long ulIntType);
extern void RTCIntDisable(unsigned long ulIntType);
extern void RTCIntCallbackInit(xtEventCallback xtRTCCallback);
extern void RTCStart(void);
extern void RTCStop(void);


extern void RTCFrequencyCompensationSet(unsigned long ulFrequency);
extern void RTCTickModeSet(unsigned long ulTickMode);
extern xtBoolean RTCIsLeapYear(void);
extern xtBoolean RTCWriteEnable(void);
extern void RTCWakeupEnable(void);
extern void RTCWakeupDisable(void);

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

#endif // __RTC_H__

