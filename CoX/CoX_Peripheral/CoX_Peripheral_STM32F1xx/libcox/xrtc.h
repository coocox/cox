//*****************************************************************************
//
//! \file xrtc.h
//! \brief Prototypes for the RTC Driver.
//! \version V2.2.1.0
//! \date 06/01/2012
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
//! \brief Values that show xRTC Interrupt Type
//! \n
//! \section xRTC_INT_Type_Section 1. Where to use this group
//! Values that can be passed to xRTCIntEnable(),xRTCIntDisable() and 
//! xRTCIntClear() as the ulIntFlags parameter. 
//! \n
//! \section xRTC_INT_Type_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xRTC Interrupts         |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xRTC_INT_SECOND         |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTC_INT_ALARM          |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTC_INT_OVERFLOW       |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************
#define xRTC_INT_SECOND         RTC_INT_TIME_TICK
#define xRTC_INT_ALARM          RTC_INT_ALARM

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xRTC_INT_Event xRTC Interrupt Event
//! \brief Values that show xRTC Interrupt Event
//! \n
//! \section xRTC_INT_Event_Section 1. Where to use this group
//! RTC Event/Error Flag, Used by IntHandle's Event Callback Function as 
//! ulMsgParam parmeter. User Callback function can user this to detect what 
//! event happened.  
//! \n
//! \section xRTC_INT_Event_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xRTC Interrupts         |       CoX      |         STM32F1xx      |
//! |------------------------|----------------|------------------------|
//! |xRTC_EVENT_SECOND       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTC_EVENT_ALARM        |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! |xRTC_EVENT_OVERFLOW     |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************
#define xRTC_EVENT_SECOND       RTC_INT_TIME_TICK
#define xRTC_EVENT_ALARM        RTC_INT_ALARM

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xRTC_Day_Week xRTC Day Week
//! \brief Values that show xRTC Day Week
//! \n
//! \section xRTC_Day_Week_Section 1. Where to use this group
//! Values that can be passed to xRTCTimeRead(),xRTCTimeWrite() 
//! as the tTime.ulWDay parameter. 
//! \n
//! \section xRTC_Day_Week_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |tTime.ulWDay            |       CoX      |         STM32F1xx      |
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
#define xRTC_WEEK_SUNDAY        RTC_WEEK_SUNDAY

//
//! Monday
//
#define xRTC_WEEK_MONDAY        RTC_WEEK_MONDAY

//
//! Tuesday
//
#define xRTC_WEEK_TUESDAY       RTC_WEEK_TUESDAY

//
//! Wednesday
//
#define xRTC_WEEK_WEDNESDAY     RTC_WEEK_WEDNESDAY

//
//! Thursday
//
#define xRTC_WEEK_THURSDAY      RTC_WEEK_THURSDAY

//
//! Friday
//
#define xRTC_WEEK_FRIDAY        RTC_WEEK_FRIDAY

//
//! Saturday
//
#define xRTC_WEEK_SATURDAY      RTC_WEEK_SATURDAY

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup xRTC_Year_Offset xRTC Year Offset
//! \Values that show xRTC Year Offset
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
//! |ulTimeAlarm             |       CoX      |         STM32F1xx      |
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
//! |xRTC API                |       CoX      |         STM32F1xx      |
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
//! \addtogroup STM32F1xx_RTC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup RTC_INT_Type RTC Interrupt Type
//! \brief Values that show RTC Interrupt Type
//! Values that can be passed to RTCIntEnable(),RTCIntDisable().
//! @{
//
//*****************************************************************************

//
//! Overflow interrupt
//
#define RTC_INT_OVERFLOW        0x00000004

//
//! Time Tick Interrupt
//
#define RTC_INT_TIME_TICK       0x00000001

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
//! \addtogroup RTC_FLAG_Type RTC Flag Type
//! \brief Values that show RTC Flag Type
//! Values that can be passed to RTCIntClear().
//! @{
//
//*****************************************************************************

//
//! Overflow flag
//
#define RTC_FLAG_OVERFLOW       0x00000004

//
//! Time Tick flag
//
#define RTC_FLAG_TIME_TICK      0x00000001

//
//! Alarm flag 
//
#define RTC_FLAG_ALARM          0x00000002

//
//! Registers synchronized flag
//
#define RTC_FLAG_RSF            0x00000008

//
//! RTC operation OFF flag 
//
#define RTC_FLAG_RTOFF          0x00000020


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
//! \addtogroup STM32F1xx_RTC_Exported_Types
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
//! \addtogroup STM32F1xx_RTC_Exported_APIs STM32F1xx API
//! \brief STM32F1xx RTC API Reference.
//! @{
//
//*****************************************************************************

extern xtBoolean RTCTimeInit(unsigned long ulConfig);
extern void RTCTimeRead(tTime *tTime, unsigned long ulTimeAlarm);
extern void RTCTimeWrite(tTime *tTime, unsigned long ulTimeAlarm);
extern void RTCIntEnable(unsigned long ulIntType);
extern void RTCIntDisable(unsigned long ulIntType);
extern void RTCIntCallbackInit(xtEventCallback xtRTCCallback);

extern unsigned long RTCFlagStatusGet(void);
extern void RTCFlagClear(unsigned long ulFlag);
extern unsigned long RTCIntStatusGet(void);
extern void RTCIntClear(unsigned long ulIntType);

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

