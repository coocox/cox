//*****************************************************************************
//
//! \file xrtc.c
//! \brief Driver for the RTC
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
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_rtc.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xrtc.h"

//*****************************************************************************
//
// An array is RTC Callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnRTCHandlerCallbacks[1]={0};

#define xRTC_COUNTER            1
#define xRTC_AUTO			    1

#ifdef xRTC_COUNTER
static xtTime xtBaseTime;
static unsigned long ulBaseDay;
#define xRTC_SECOND_A_DAY       0x00015180
static unsigned char ucMonthNumber[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30,
                                          31, 30, 31};
#ifdef xRTC_AUTO
static unsigned char ucLeapYear[136] = {
    1, // 2000 is leap year
    0, // 2001 not leap year
    0, // 2002 not leap year
    0, // 2003 not leap year
    1, // 2004 is leap year
    0, // 2005 not leap year
    0, // 2006 not leap year
    0, // 2007 not leap year
    1, // 2008 is leap year
    0, // 2009 not leap year
    0, // 2010 not leap year
    0, // 2011 not leap year
    1, // 2012 is leap year
    0, // 2013 not leap year
    0, // 2014 not leap year
    0, // 2015 not leap year
    1, // 2016 is leap year
    0, // 2017 not leap year
    0, // 2018 not leap year
    0, // 2019 not leap year
    1, // 2020 is leap year
    0, // 2021 not leap year
    0, // 2022 not leap year
    0, // 2023 not leap year
    1, // 2024 is leap year
    0, // 2025 not leap year
    0, // 2026 not leap year
    0, // 2027 not leap year
    1, // 2028 is leap year
    0, // 2029 not leap year
    0, // 2030 not leap year
    0, // 2031 not leap year
    1, // 2032 is leap year
    0, // 2033 not leap year
    0, // 2034 not leap year
    0, // 2035 not leap year
    1, // 2036 is leap year
};
#endif

//*****************************************************************************
//
//! \internal
//! \brief Get current counter from xtTime struct. 
//!
//! \param tTime specifies the point of time and data.
//!
//! This function is to get current counter from xtTime struct.
//!
//! \return the current counter.
//
//*****************************************************************************
static unsigned long 
xRTCConvertTimeToCounter(xtTime *xtTime)
{
    unsigned long i;
    unsigned long ulTempDay = 0;
    for(i=0; i<(xtTime->ulYear -2000); i++)
    {
#ifdef xRTC_AUTO
        ulTempDay += (ucLeapYear[i] ? 366 : 365 );
#else
        ulTempDay += (((((2000 + i) % 4) == 0 && 
                        ((2000 + i) % 100) != 0)) ||
                       (((2000 + i) % 400) == 0)
                       ? 366 : 365 );
#endif

    }
    for(i=0; i<(xtTime->ulMonth -1); i++)
    {

        ulTempDay += (ucMonthNumber[i]);

    }
    ulTempDay += (xtTime->ulMDay-1);
    if(xtTime->ulMonth > 2)
    {
#ifdef xRTC_AUTO
        if(ucLeapYear[xtTime->ulYear -2000])
#else
        if((((xtTime->ulYear % 4) == 0 && (xtTime->ulYear % 100) != 0)) ||
           ((xtTime->ulYear % 400) == 0))
#endif
        {
            ulTempDay++;
        }
    }
    
    //
    // Check the week is in accordance with day or not.
    //
    xASSERT(xtTime->ulWDay == ((6+ulTempDay)%7));

    //
    // Set the base time.
    //
    xtBaseTime.ulHour = xtTime->ulHour;
    xtBaseTime.ulMDay= xtTime->ulMDay;
    xtBaseTime.ulMinute= xtTime->ulMinute;
    xtBaseTime.ulMonth= xtTime->ulMonth;
    xtBaseTime.ulSecond= xtTime->ulSecond;
    xtBaseTime.ulWDay= xtTime->ulWDay;
    xtBaseTime.ulYear= xtTime->ulYear;

    ulBaseDay = ulTempDay;
    
    return (ulTempDay * xRTC_SECOND_A_DAY + xtTime->ulHour * 3600 +
            xtTime->ulMinute * 60 + xtTime->ulSecond) ;
}


//*****************************************************************************
//
//! \internal
//! \brief Convert current counter to xtTime struct. 
//!
//! \param tTime specifies the point of time and data.
//! \param ultimeCounter specifies the current counter of RTC.
//!
//! This function is to Convert current counter to xtTime struct.
//!
//! The \e ultimeCounter parameter is the value witch is read from RTC register.
//!
//! \return None.
//
//*****************************************************************************
static void 
xRTCConvertCounterToTime(xtTime *xtTime, unsigned long ultimeCounter)
{
    unsigned long ulTempTime = 0;
    unsigned long ulTempDay = 0;

    ulTempTime = ultimeCounter % xRTC_SECOND_A_DAY;
    ulTempDay = ultimeCounter / xRTC_SECOND_A_DAY;
    
    xtTime->ulHour = ulTempTime / 3600;
    xtTime->ulMinute = (ulTempTime % 3600)/60;
    xtTime->ulSecond = (ulTempTime % 3600)%60;
    xtTime->ulWDay = (ulTempDay + 6) % 7;

    while(ulTempDay > ulBaseDay)
    {
        ulBaseDay++;
        xtBaseTime.ulMDay++;
        if (xtBaseTime.ulMonth == 2)   
        {
#ifdef xRTC_AUTO        
            if(ucLeapYear[xtBaseTime.ulYear - 2000])
            {
#else
            if(((xtBaseTime.ulYear % 4 ==0) && (xtBaseTime.ulYear % 100 !=0))
              || (xtBaseTime.ulYear % 400 ==0))
            {
#endif
                if (xtBaseTime.ulMDay > 29)
                {
                    xtBaseTime.ulMDay = 1;
                    xtBaseTime.ulMonth++;
                }
            }
            else
            {
                if (xtBaseTime.ulMDay > 28)
                {
                    xtBaseTime.ulMDay = 1;
                    xtBaseTime.ulMonth++;
                }
            }

        }
        else if(xtBaseTime.ulMDay > ucMonthNumber[xtBaseTime.ulMonth - 1])
        {
            xtBaseTime.ulMDay = 1;
            xtBaseTime.ulMonth++;
            if (xtBaseTime.ulMonth > 12)
            {
                xtBaseTime.ulMonth = 1;
                xtBaseTime.ulYear++;
            } 
        }
	}

    xtTime->ulMDay = xtBaseTime.ulMDay;
    xtTime->ulMonth = xtBaseTime.ulMonth;
    xtTime->ulYear = xtBaseTime.ulYear;
}
#endif

//*****************************************************************************
//
//! \brief RTC interrupt handler. Clear the RTC interrupt flag and execute the 
//! callback function.
//!
//! \param none.
//!
//! This function is the RTC interrupt handler,it will Clear the RTC 
//! interrupt flag and execute the callback function if there be one.
//!
//! \note There are two source of this interrupt.One is RTC tick interrupt
//! and one is RTC alarm interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
RTCIntHandler(void)
{
    unsigned long ulEventFlags;
    
    ulEventFlags = xHWREG(RTC_SR);
    
    //
    // Call Callback function
    //
    if(g_pfnRTCHandlerCallbacks[0] != 0)
    {
        g_pfnRTCHandlerCallbacks[0](0, 0, ulEventFlags, 0);
    }
}

//*****************************************************************************
//
//! \brief Initializes the RTC peripheral. 
//!
//! \param None.
//!
//! This function is to initializes the RTC peripheral.
//!
//! \return None.
//
//*****************************************************************************
void
RTCTimeInit(unsigned long ulConfig)
{
    
    while(!SysCtlBackupReadyStateGet());

    SysCtlBackupDomainReset();

    xHWREG(RTC_CR) = 0;
    xHWREG(RTC_CR) |= ulConfig;
}

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
void
RTCStart(void)
{
    //
    // Start RTC Timer.
    //  
    xHWREG(RTC_CR) |= RTC_CR_RTCEN;
}

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
void
RTCStop(void)
{
    //
    // Stop RTC Timer.
    //  
    xHWREG(RTC_CR) &= ~RTC_CR_RTCEN;
}


//*****************************************************************************
//
//! \brief Read current date/time or alarm date/time from RTC setting. 
//!
//! \param tTime specifies the point of time and data.
//! \param ulTimeAlarm specifies which will be read current time or alarm timr.
//!
//! This function is to Read current date/time or alarm date/time from RTC
//! setting.
//!
//! The \e ulTimeAlarm parameter is the one of any of the following:
//! \b RTC_TIME_CURRENT,and \b RTC_TIME_ALARM.
//!
//! \return None.
//
//*****************************************************************************
void
RTCTimeRead(tTime *tTime, unsigned long ulTimeAlarm)
{
    unsigned long ulTemp;
    //
    // Check the arguments.
    //
    xASSERT((ulTimeAlarm == RTC_TIME_CURRENT) ||
            (ulTimeAlarm == RTC_TIME_ALARM));

    if(ulTimeAlarm == RTC_TIME_CURRENT)
    {
        ulTemp = xHWREG(RTC_CNT);
        ulTemp += SysCtlBackupRegRead(0);
        xRTCConvertCounterToTime((xtTime *)tTime, ulTemp);
    }
    else
    {
        ulTemp = xHWREG(RTC_CMP);
        ulTemp += SysCtlBackupRegRead(1);
        xRTCConvertCounterToTime((xtTime *)tTime, ulTemp);       
    }
}

//*****************************************************************************
//
//! \brief Write current date/time or alarm date/time to RTC setting. 
//!
//! \param tTime specifies the point of time and data.
//! \param ulTimeAlarm specifies which will be write current time or alarm timr.
//!
//! This function is to write current date/time or alarm date/time to RTC
//! setting.
//!
//! The \e ulTimeAlarm parameter is the one of any of the following:
//! \b RTC_TIME_CURRENT,and \b RTC_TIME_ALARM.
//!
//! \return None.
//
//*****************************************************************************
void
RTCTimeWrite(tTime *tTime, unsigned long ulTimeAlarm)
{
    unsigned long ulTemp;
    //
    // Check the arguments.
    //
    xASSERT((ulTimeAlarm == RTC_TIME_CURRENT) ||
            (ulTimeAlarm == RTC_TIME_ALARM));
    
    xASSERT((tTime->ulYear >= RTC_YEAR_OFFSET) &&
            (tTime->ulYear <= RTC_YEAR_OFFSET + 99));
    
    xASSERT((tTime->ulMonth >= 1) && 
            (tTime->ulMonth <= 12));
    
    xASSERT((tTime->ulMDay >= 1) &&
            (tTime->ulMDay <= 31));
    
    xASSERT((tTime->ulHour >= 0) &&
            (tTime->ulHour <=  23));

    RTCStop();
    ulTemp = xRTCConvertTimeToCounter((xtTime *)tTime);

    if (ulTimeAlarm == RTC_TIME_CURRENT)
    {
        SysCtlBackupRegWrite(0, ulTemp);
    }
    else
    {
        SysCtlBackupRegWrite(1, ulTemp);
    }
    RTCStart();
}

//*****************************************************************************
//
//! \brief Enable the time tick or alarm interrupt of RTC. 
//!
//! \param ulIntType is the bit mask of the interrupt sources to be enabled.
//!
//! This function is to enable the time tick or alarm interrupt of RTC.
//!
//! The \e ulIntType parameter is the logical OR of any of the following:
//! \b RTC_INT_TIME_TICK,\b RTC_INT_ALARM and RTC_INT_OVERFLOW.
//!
//! \return None.
//
//*****************************************************************************
void
RTCIntEnable(unsigned long ulIntType)
{
    //
    // Check the arguments.
    //
    xASSERT(((ulIntType & RTC_INT_TIME_TICK) == RTC_INT_TIME_TICK) ||
            ((ulIntType & RTC_INT_ALARM) == RTC_INT_ALARM) ||
            ((ulIntType & RTC_INT_OVERFLOW) == RTC_INT_OVERFLOW));

    xHWREG(RTC_IWEN) |= ulIntType; 
}

//*****************************************************************************
//
//! \brief Disable the time tick or alarm interrupt of RTC. 
//!
//! \param ulIntType is the bit mask of the interrupt sources to be enabled.
//!
//! This function is to Disable the time tick or alarm interrupt of RTC.
//!
//! The \e ulIntType parameter is the logical OR of any of the following:
//! \b RTC_INT_TIME_TICK,\b RTC_INT_ALARM and RTC_INT_OVERFLOW.
//!
//! \return None.
//
//*****************************************************************************
void
RTCIntDisable(unsigned long ulIntType)
{
    //
    // Check the arguments.
    //
    xASSERT(((ulIntType & RTC_INT_TIME_TICK) == RTC_INT_TIME_TICK) ||
            ((ulIntType & RTC_INT_ALARM) == RTC_INT_ALARM) ||
            ((ulIntType & RTC_INT_OVERFLOW) == RTC_INT_OVERFLOW));

    xHWREG(RTC_IWEN) &= ~ulIntType; 
}

//*****************************************************************************
//
//! \brief Enable the RTC function of wakeup. 
//!
//! \param ulWakeupType is the bit mask of the wakeup sources to be enabled.
//!
//! This function is to enable the RTC function of wakeup.
//!
//! The \e ulIntType parameter is the logical OR of any of the following:
//! \b RTC_WAKEUP_TIME_TICK, \b RTC_WAKEUP_OVERFLOW, and \b RTC_WAKEUP_ALARM.
//!
//! \return None.
//
//*****************************************************************************
void
RTCWakeupEnable(unsigned long ulWakeupType)
{
    //
    // Check the arguments.
    //
    xASSERT(((ulIntType & RTC_WAKEUP_TIME_TICK) == RTC_WAKEUP_TIME_TICK) ||
            ((ulIntType & RTC_WAKEUP_ALARM) == RTC_WAKEUP_ALARM) ||
            ((ulIntType & RTC_WAKEUP_OVERFLOW) == RTC_WAKEUP_OVERFLOW));

    xHWREG(RTC_IWEN) |= ulWakeupType; 
}

//*****************************************************************************
//
//! \brief Disable the RTC function of wakeup. 
//!
//! \param ulWakeupType is the bit mask of the wakeup sources to be disbled.
//!
//! This function is to disable the RTC function of wakeup.
//!
//! The \e ulIntType parameter is the logical OR of any of the following:
//! \b RTC_WAKEUP_TIME_TICK, \b RTC_WAKEUP_OVERFLOW, and \b RTC_WAKEUP_ALARM.
//!
//! \return None.
//
//*****************************************************************************
void
RTCWakeupDisable(unsigned long ulWakeupType)
{
    //
    // Check the arguments.
    //
    xASSERT(((ulIntType & RTC_WAKEUP_TIME_TICK) == RTC_WAKEUP_TIME_TICK) ||
            ((ulIntType & RTC_WAKEUP_ALARM) == RTC_WAKEUP_ALARM) ||
            ((ulIntType & RTC_WAKEUP_OVERFLOW) == RTC_WAKEUP_OVERFLOW));

    xHWREG(RTC_IWEN) &= ~ulWakeupType; 
}

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
void
RTCIntCallbackInit(xtEventCallback xtRTCCallback)
{
    if (xtRTCCallback != 0)
    {
        g_pfnRTCHandlerCallbacks[0] = xtRTCCallback;
    }
}

//*****************************************************************************
//
//! \brief Config the RTC output.
//!
//! \param ulConfig is the configuration for the RTC output.
//!
//! This function is to config the RTC output.
//!
//! \return None.
//
//*****************************************************************************
void 
RTCOutputConfig(unsigned long ulConfig)
{

    xHWREG(RTC_CR) &= ~(RTC_CR_ROAP | RTC_CR_ROWM | RTC_CR_ROES);
    xHWREG(RTC_CR) |= ulConfig;
}

//*****************************************************************************
//
//! \brief Enable the RTC output.
//!
//! \param None.
//!
//! This function is to enable the RTC output.
//!
//! \return None.
//
//*****************************************************************************
void 
RTCOutputEnable(void)
{
    xHWREG(RTC_CR) |= RTC_CR_ROEN;
}

//*****************************************************************************
//
//! \brief Disable the RTC output.
//!
//! \param None.
//!
//! This function is to disable the RTC output.
//!
//! \return None.
//
//*****************************************************************************
void 
RTCOutputDisable(void)
{
    xHWREG(RTC_CR) &= ~RTC_CR_ROEN;
}
