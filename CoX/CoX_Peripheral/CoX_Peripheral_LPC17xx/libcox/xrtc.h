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
#define xRTC_INT_SECOND         RTC_INT_INC
#define xRTC_INT_ALARM          RTC_INT_ALARM

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
//! |  xRTC Interrupts         |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xRTC_EVENT_SECOND       |    Mandatory   |            Y           |
//! |  xRTC_EVENT_ALARM        |  Non-Mandatory |            Y           |
//!
//! @{
//
//*****************************************************************************
#define xRTC_EVENT_SECOND       BIT_32_0
#define xRTC_EVENT_ALARM        BIT_32_1

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
#define xRTC_YEAR_OFFSET

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
#define xRTC_TIME_CURRENT       BIT_32_0

//
//! Read or write alarm time and date
//
#define xRTC_TIME_ALARM         BIT_32_1

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
#define xRTCTimeInit()          RTCCounterReset()

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
#define xRTCIntCallbackInit(xtRTCCallback)                                    \
         RTCIntCallbackInit(xtRTCCallback)

//*****************************************************************************
//
//! \brief  Start the RTC timer.
//!
//! \param  None.
//!
//! \return None.
//
//*****************************************************************************
#define xRTCStart()             RTCEnable()

//*****************************************************************************
//
//! \brief  Stop the RTC timer.
//!
//! \param  None.
//!
//! \return None.
//
//*****************************************************************************
#define xRTCStop()              RTCDisable()

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
//! \addtogroup LPC17xx_RTC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_RTC_TIME_TYPE   The type of the RTC time.
//! @{
//
//*****************************************************************************

//! Second
#define RTC_TIMETYPE_SECOND     BIT_32_0

//! Minute
#define RTC_TIMETYPE_MINUTE     BIT_32_1

//! Hour
#define RTC_TIMETYPE_HOUR       BIT_32_2

//! Day of week
#define RTC_TIMETYPE_DAYOFWEEK  BIT_32_3

//! Day of month
#define RTC_TIMETYPE_DAYOFMONTH BIT_32_4

//! Day of year
#define RTC_TIMETYPE_DAYOFYEAR  BIT_32_5

//! Month
#define RTC_TIMETYPE_MONTH      BIT_32_6

//! Year
#define RTC_TIMETYPE_YEAR       BIT_32_7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_RTC_INT_TYPE RTC interrupt type.
//! @{
//
//*****************************************************************************

//! RTC increment interrupt.
#define RTC_INT_INC             ILR_CIF

//! RTC alarm interrupt.
#define RTC_INT_ALARM           ILR_CALF

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup LPC17xx_RTC_INT_CFG  RTC interrupt configure mode.
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
//! \addtogroup LPC17xx_RTC_GEN_REG  RTC general register ID
//! @{
//
//*****************************************************************************

//! RTC general register 0
#define RTC_REG_0               RTC_GPREG0

//! RTC general register 1
#define RTC_REG_1               RTC_GPREG1

//! RTC general register 2
#define RTC_REG_2               RTC_GPREG2

//! RTC general register 3
#define RTC_REG_3               RTC_GPREG3

//! RTC general register 4
#define RTC_REG_4               RTC_GPREG4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup LPC17xx_RTC_Exported_APIs LPC17xx RTC API
//! \brief LPC17xx RTC API Reference.
//! @{
//
//*****************************************************************************

extern void RTCTimeSet(unsigned long ulType, unsigned long ulValue);
extern unsigned long RTCTimeGet(unsigned long ulType);
extern void RTCAlarmSet(unsigned long ulType, unsigned long ulValue);
extern unsigned long RTCAlarmGet(unsigned long ulType);
extern void RTCGenRegWrite(unsigned long ulID, unsigned long ulValue);
extern unsigned long RTCGenRegRead(unsigned long ulID);
extern unsigned long RTCIntFlagGet(void);
extern xtBoolean RTCIntFlagCheck(unsigned long ulFlags);
extern void RTCIntFlagClear(unsigned long ulFlags);
extern void RTCEnable(void);
extern void RTCDisable(void);
extern void RTCCounterReset(void);
extern void RTCCaliEnable(void);
extern void RTCCaliDisable(void);
extern void RTCIntCfg(unsigned long ulCfg);
extern void RTCIntCallbackInit(xtEventCallback pfnCallback);

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

#endif // __XRTC_H__

