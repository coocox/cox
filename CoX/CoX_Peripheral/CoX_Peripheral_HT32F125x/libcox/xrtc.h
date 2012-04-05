//*****************************************************************************
//
//! \file xrtc.h
//! \brief Prototypes for the RTC Driver.
//! \version V2.1.1.0
//! \date 3/27/2012
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

#ifndef __xRTC_H__
#define __xRTC_H__

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
//! \n
//! \section xRTC_INT_Type_Section 1. Where to use this group
//! Values that can be passed to xRTCIntEnable(),xRTCIntDisable() and 
//! xRTCIntClear() as the ulIntFlags parameter. 
//! \n
//! \section xRTC_INT_Type_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xRTC Interrupts         |       CoX      |         HT32F125x      |
//! |------------------------|----------------|------------------------|
//! |xRTC_INT_SECOND         |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTC_INT_ALARM          |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTC_INT_OVERFLOW       |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************
#define xRTC_INT_SECOND         RTC_INT_TIME_TICK
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
//! \n
//! \section xRTC_INT_Event_Section 1. Where to use this group
//! RTC Event/Error Flag, Used by IntHandle's Event Callback Function as 
//! ulMsgParam parmeter. User Callback function can user this to detect what 
//! event happened.  
//! \n
//! \section xRTC_INT_Event_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xRTC Interrupts         |       CoX      |         HT32F125x      |
//! |------------------------|----------------|------------------------|
//! |xRTC_EVENT_SECOND       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTC_EVENT_ALARM        |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTC_EVENT_OVERFLOW     |  Non-Mandatory |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************
#define xRTC_EVENT_SECOND       RTC_INT_TIME_TICK
#define xRTC_EVENT_ALARM        RTC_INT_ALARM
#define xRTC_EVENT_OVERFLOW     RTC_INT_OVERFLOW
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xRTC_Day_Week xRTC Day Week
//! \n
//! \section xRTC_Day_Week_Section 1. Where to use this group
//! Values that can be passed to xRTCTimeRead(),xRTCTimeWrite() 
//! as the tTime.ulWDay parameter. 
//! \n
//! \section xRTC_Day_Week_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |tTime.ulWDay            |       CoX      |         HT32F125x      |
//! |------------------------|----------------|------------------------|
//! |xRTC_WEEK_SUNDAY        |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTC_WEEK_MONDAY        |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTC_WEEK_TUESDAY       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTC_WEEK_WEDNESDAY     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTC_WEEK_THURSDAY      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTC_WEEK_FRIDAY        |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTC_WEEK_SATURDAY      |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
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
//! \n
//! \section xRTC_Year_Offset_Section 1. Where to use this group
//! Values that is the offset of the year. 
//! \n
//! \section xRTC_Year_Offset_CoX 2.CoX Port Details 
//! \verbatim

//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Initiative time is 00:00:00 1/1 / 2000
//
#define xRTC_YEAR_OFFSET        RTC_YEAR_OFFSET

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xRTC_Time_Type xRTC Time Type
//! \brief Values that show xRTC Time Type
//! \n
//! \section xRTC_Year_Offset_Section 1. Where to use this group
//! Values that can be passed to RTCTimeRead() and RTCTimeWrite()
//! as the ulTimeAlarm parameter. 
//! \n
//! \section xRTC_Year_Offset_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |ulTimeAlarm             |       CoX      |         HT32F125x      |
//! |------------------------|----------------|------------------------|
//! |xRTC_TIME_CURRENT       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTC_TIME_ALARM         |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! \endverbatim
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

//*****************************************************************************
//
//! xRTC Time and Calendar Definition definitions
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
} xtTime;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xRTC_Exported_APIs xRTC API
//! \brief xRTC API Reference.
//!
//! \section xRTC_Exported_APIs_Port CoX Port Details
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xRTC API                |       CoX      |         HT32F125x      |
//! |------------------------|----------------|------------------------|
//! |xRTCTimeInit            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTCTimeRead            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTCTimeWrite           |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTCIntEnable           |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTCIntCallbackInit     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTCIntDisable          |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTCStart               |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTCStop                |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Initializes the RTC peripheral. 
//!
//! \param None.
//!
//! This function is to initializes the RTC peripheral.
//!
//! \return xtrue if initializes the RTC peripheral sucessfully or return 
//! xfalse .
//
//*****************************************************************************

#define xRTCTimeInit()                                                        \
        RTCTimeInit()

//*****************************************************************************
//
//! \brief Read current date/time or alarm date/time from RTC setting. 
//!
//! \param xtTime specifies the point of time and data.
//! \param ulTimeAlarm specifies which will be read current time or alarm time.
//! Details please refer to \ref xRTC_Time_Type.
//!
//! This function is to Read current date/time or alarm date/time from RTC
//! setting.
//!
//! The \e ulTimeAlarm parameter is the one of any of the following:
//! \b xRTC_TIME_CURRENT,and \b xRTC_TIME_ALARM.
//! Details please refer to \ref xRTC_Time_Type_CoX.
//!
//! \return None.
//
//*****************************************************************************
#define xRTCTimeRead(xtTime, ulTimeAlarm)                                     \
        do                                                                    \
        {                                                                     \
         RTCTimeRead((tTime *)xtTime, ulTimeAlarm)                            \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief Write current date/time or alarm date/time to RTC setting. 
//!
//! \param tTime specifies the point of time and data.
//! \param ulTimeAlarm specifies which will be write current time or alarm timr.
//! Details please refer to \ref xRTC_Time_Type.
//!
//! This function is to write current date/time or alarm date/time to RTC
//! setting.
//!
//! The \e ulTimeAlarm parameter is the one of any of the following:
//! \b xRTC_TIME_CURRENT,and \b xRTC_TIME_ALARM.
//! Details please refer to \ref xRTC_Time_Type_CoX.
//!
//! \return None.
//
//*****************************************************************************
#define xRTCTimeWrite(xtTime, ulTimeAlarm)                                    \
        do                                                                    \
        {                                                                     \
         RTCTimeWrite((tTime *)xtTime, ulTimeAlarm)                           \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief Enable the time tick or alarm interrupt of RTC. 
//!
//! \param ulIntType is the bit mask of the interrupt sources to be enabled.
//! Details please refer to \ref xRTC_INT_Type.
//!
//! This function is to enable the time tick or alarm interrupt of RTC.
//!
//! The \e ulIntType parameter is the logical OR of any of the following:
//! \b xRTC_INT_TIME_TICK,and \b xRTC_INT_ALARM.
//! Details please refer to \ref xRTC_INT_Type_CoX.
//!
//! \return None.
//
//*****************************************************************************        
#define xRTCIntEnable(ulIntType)                                              \
        RTCIntEnable(ulIntType)

//*****************************************************************************
//
//! \brief Init interrupts callback for the RTC.
//!
//! \param xtPortCallback is callback for the RTC.
//!
//! Init interrupts callback for the RTC.
//!
//! \return None.
//
//*****************************************************************************
#define xRTCIntCallbackInit(xtRTCCallback)                                    \
        RTCIntCallbackInit(xtRTCCallback) 

//*****************************************************************************
//
//! \brief Disable the time tick or alarm interrupt of RTC. 
//!
//! \param ulIntType is the bit mask of the interrupt sources to be disable.
//! Details please refer to \ref xRTC_INT_Type.
//!
//! This function is to disable the time tick or alarm interrupt of RTC.
//!
//! The \e ulIntType parameter is the logical OR of any of the following:
//! \b xRTC_INT_SECOND,and \b xRTC_INT_ALARM.
//! Details please refer to \ref xRTC_INT_Type_CoX.
//!
//! \return None.
//
//*****************************************************************************
#define xRTCIntDisable(ulIntType)                                             \
        RTCIntDisable(ulIntType)

//*****************************************************************************
//
//! \brief Start the RTC timer. 
//!
//! \param None.
//!
//! This function is to start the RTC timer.
//!
//! \return None.
//
//*****************************************************************************
#define xRTCStart()                                                           \
        RTCStart()

//*****************************************************************************
//
//! \brief Stop the RTC timer. 
//!
//! \param None.
//!
//! This function is to stop the RTC timer.
//!
//! \return None.
//
//*****************************************************************************
#define xRTCStop()                                                            \
        RTCStop()

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
//! \addtogroup HT32F125x_RTC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup RTC_INT_Type RTC Interrupt Type
//! Values that can be passed to RTCIntEnable(),RTCIntDisable() and 
//! RTCIntClear().
//! @{
//
//*****************************************************************************

//
//! Time Tick Interrupt
//
#define RTC_INT_TIME_TICK       0x00000001

//
//! Alarm Interrupt 
//
#define RTC_INT_ALARM           0x00000002

//
//! Counter Overflow Interrupt
//
#define RTC_INT_OVERFLOW        0x00000004


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup RTC_Wakeup_Type RTC Wakeup Source Type
//! Values that can be passed to RTCWakeupEnable() and RTCWakeupDisable().
//! @{
//
//*****************************************************************************

//
//! Time Tick Wakeup
//
#define RTC_WAKEUP_TIME_TICK    0x00000100

//
//! Alarm Wakeup 
//
#define RTC_WAKEUP_ALARM        0x00000200

//
//! Counter Overflow Wakeup
//
#define RTC_WAKEUP_OVERFLOW     0x00000400


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup RTC_Year_Offset RTC Year Offset
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
//! \addtogroup RTC_Init_Config RTC initializes config
//! Values that can be passed to RTCTimeInit().
//! @{
//
//*****************************************************************************

//
//! RTC Clock Source is LSI.
//
#define RTC_CLOCK_SRC_LSI       0x00000000

//
//! RTC Clock Source is LSE.
//
#define RTC_CLOCK_SRC_LSE       0x00000002

//
//! 32-bit RTC counter not affected when compare match condition occurs.
//
#define RTC_CMPCLR_DIS          0x00000000

//
//! 32-bit RTC counter cleared when compare match condition occurs.
//
#define RTC_CMPCLR_EN           0x00000010

//
//! Normal startup and requires less operating power.
//
#define RTC_LSE_MODE_NORMAL     0x00000000

//
//! 3Fast startup but requires higher operating power.
//
#define RTC_LSE_MODE_FAST       0x00000020

//
//! RTC Clock Prescaler is 1.
//
#define RTC_TIME_PRESCA_1       0x00000000

//
//! RTC Clock Prescaler is 2.
//
#define RTC_TIME_PRESCA_2       0x00000100

//
//! RTC Clock Prescaler is 4.
//
#define RTC_TIME_PRESCA_4       0x00000200

//
//! RTC Clock Prescaler is 8.
//
#define RTC_TIME_PRESCA_8       0x00000300

//
//! RTC Clock Prescaler is 16.
//
#define RTC_TIME_PRESCA_16      0x00000400

//
//! RTC Clock Prescaler is 32.
//
#define RTC_TIME_PRESCA_32      0x00000500

//
//! RTC Clock Prescaler is 64.
//
#define RTC_TIME_PRESCA_64      0x00000600

//
//! RTC Clock Prescaler is 128.
//
#define RTC_TIME_PRESCA_128     0x00000700

//
//! RTC Clock Prescaler is 256.
//
#define RTC_TIME_PRESCA_256     0x00000800

//
//! RTC Clock Prescaler is 512.
//
#define RTC_TIME_PRESCA_512     0x00000900

//
//! RTC Clock Prescaler is 1024.
//
#define RTC_TIME_PRESCA_1024    0x00000A00

//
//! RTC Clock Prescaler is 2048.
//
#define RTC_TIME_PRESCA_2048    0x00000B00

//
//! RTC Clock Prescaler is 4096.
//
#define RTC_TIME_PRESCA_4096    0x00000C00

//
//! RTC Clock Prescaler is 8192.
//
#define RTC_TIME_PRESCA_8192    0x00000D00

//
//! RTC Clock Prescaler is 16384.
//
#define RTC_TIME_PRESCA_16384   0x00000E00

//
//! RTC Clock Prescaler is 32768.
//
#define RTC_TIME_PRESCA_32768   0x00000F00


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup RTC_Wakeup_Config RTC wakeup config
//! Values that can be passed to RTCWakeupConfig().
//! @{
//
//*****************************************************************************

//
//! Counter overflow wakeup enabled
//
#define RTC_OVERFLOW_WAKE_EN    0x00000400

//
//! Counter overflow wakeup disabled
//
#define RTC_OVERFLOW_WAKE_DIS   0x00000000

//
//! Counter Clock CK_SECOND wakeup enabled
//
#define RTC_SECOND_WAKE_EN      0x00000100

//
//! Counter Clock CK_SECOND wakeup disabled
//
#define RTC_SECOND_WAKE_DIS     0x00000000

//
//! Compare match wakeup enabled
//
#define RTC_COMPMATCH_WAKE_EN   0x00000200

//
//! Compare match wakeup didabled
//
#define RTC_COMPMATCH_WAKE_DIS  0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup RTC_Output_Config RTC Output config
//! Values that can be passed to RTCOutputConfig().
//! @{
//
//*****************************************************************************

//
//! Active level is high.
//
#define RTC_RTCOUT_ACTIVE_HIGH  0x00000000

//
//! Active level is low.
//
#define RTC_RTCOUT_ACTIVE_LOW   0x00080000

//
//! Pulse mode.
//
#define RTC_RTCOUT_WAVEFORM_PULSE                                             \
                                0x00000000

//
//! Level mode.
//
#define RTC_RTCOUT_WAVEFORM_LEVEL                                             \
                                0x00040000

//
//! RTC compare match event selected
//
#define RTC_RTCOUT_COMPARE      0x00000000

//
//! RTC second clock (CK_SECOND) event is selected
//
#define RTC_RTCOUT_SECOND       0x00020000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_RTC_Exported_Types
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

} tTime;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup HT32F125x_RTC_Exported_APIs HT32F125x API
//! @{
//
//*****************************************************************************

extern void RTCTimeInit(unsigned long ulConfig);
extern void RTCTimeRead(tTime *tTime, unsigned long ulTimeAlarm);
extern void RTCTimeWrite(tTime *tTime, unsigned long ulTimeAlarm);
extern void RTCIntEnable(unsigned long ulIntType);
extern void RTCIntDisable(unsigned long ulIntType);
extern void RTCIntCallbackInit(xtEventCallback xtRTCCallback);
extern void RTCStart(void);
extern void RTCStop(void);

extern void RTCOutputConfig(unsigned long ulConfig);
extern void RTCOutputEnable(void);
extern void RTCOutputDisable(void);
extern void RTCWakeupEnable(unsigned long ulWakeupType);
extern void RTCWakeupDisable(unsigned long ulWakeupType);
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

#endif // __xRTC_H__

