//*****************************************************************************
//
//! \file xrtc.c
//! \brief Driver for the RTC
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

static unsigned long g_ulCalendar,g_ulTime;

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
//! \note None
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
//! \note None
//!
//! \return None.
//
//*****************************************************************************
static void 
xRTCConvertCounterToTime(xtTime *xtTime, unsigned long ultimeCounter)
{
    unsigned long i;
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
    
    ulEventFlags = (xHWREG(RTC_RIIR) & (RTC_RIIR_TIF | RTC_RIIR_AIF));

    //
    // Clear Int flags
    //
    xHWREG(RTC_RIIR) = ulEventFlags;
    
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
//! \note None
//!
//! \return xtrue if initializes the RTC peripheral sucessfully or return 
//! xfalse .
//
//*****************************************************************************
xtBoolean
RTCTimeInit(void)
{
    unsigned long i;
    SysCtlKeyAddrUnlock();
    xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL32K_EN;

    //
    //! Waiting for 32K stable 
    //
    SysCtlDelay(1000);

    //
    //! Enable RTC Clock
    //    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_RTC);
    SysCtlKeyAddrLock();

    //
    //! When RTC is power on, write 0xa5eb1357 to RTC_INIR to reset all logic.
    //  
    xHWREG(RTC_INIR) = RTC_INIR_KEY;

    for(i=0; i<0xFFFFFFFF; i++)
    {
        //
        //!  Check RTC_INIR[0] to find out RTC reset signal
        // 
        if(xHWREG(RTC_INIR) == 0x01)
        {
            break;
        }
    }
    if (i == 0xFFFFFFFF)
	{
		return xfalse;
	}
	xIntEnable(INT_RTC);

	return xtrue;
}

//*****************************************************************************
//
//! \brief Start the RTC timer. 
//!
//! \param None.
//!
//! This function is to start the RTC timer.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void
RTCStart(void)
{
    //
    //! Start RTC Timer.
    //  
    xHWREG(RTC_INIR) |= RTC_INIR_ACTIVE;
}

//*****************************************************************************
//
//! \brief Stop the RTC timer. 
//!
//! \param None.
//!
//! This function is to stop the RTC timer.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void
RTCStop(void)
{
    //
    //! Stop RTC Timer.
    //  
    xHWREG(RTC_INIR) &= ~RTC_INIR_ACTIVE;
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
//! \note None
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
        g_ulCalendar = xHWREG(RTC_CLR);
        g_ulTime = xHWREG(RTC_TLR);
    }
    else
    {
        g_ulCalendar = xHWREG(RTC_CAR);
        g_ulTime = xHWREG(RTC_TAR);        
    }

    ulTemp = ((g_ulCalendar & RTC_CLR_10YEAR_M) >> RTC_CLR_10YEAR_S)*10 +
             ((g_ulCalendar & RTC_CLR_1YEAR_M) >> RTC_CLR_1YEAR_S);
    tTime->ulYear = ulTemp + RTC_YEAR_OFFSET;

    ulTemp = ((g_ulCalendar & RTC_CLR_10MON_M) >> RTC_CLR_10MON_S)*10 +
             ((g_ulCalendar & RTC_CLR_1MON_M) >> RTC_CLR_1MON_S);
    tTime->ulMonth = ulTemp;

    ulTemp = ((g_ulCalendar & RTC_CLR_10DAY_M) >> RTC_CLR_10DAY_S)*10 +
             ((g_ulCalendar & RTC_CLR_1DAY_M) >> RTC_CLR_1DAY_S);
    tTime->ulMDay = ulTemp;
    
    ulTemp = ((g_ulTime & RTC_TLR_10HR_M) >> RTC_TLR_10HR_S)*10 +
             ((g_ulTime & RTC_TLR_1HR_M) >> RTC_TLR_1HR_S);
    if ((xHWREG(RTC_TSSR) & RTC_TSSR_24H_12H) == 0)
    {
        if (ulTemp > 20)
        {
            tTime->ulFormat = RTC_TIME_12H_PM;
            ulTemp -= 20;
        }
        else
        {
            tTime->ulFormat = RTC_TIME_12H_AM;
        }
    }
    else
    {
        tTime->ulFormat = RTC_TIME_24H;
    }
    tTime->ulHour = ulTemp;

    ulTemp = ((g_ulTime & RTC_TLR_10MIN_M) >> RTC_TLR_10MIN_S)*10 +
             ((g_ulTime & RTC_TLR_1MIN_M) >> RTC_TLR_1MIN_S);
    tTime->ulMinute = ulTemp;

    ulTemp = ((g_ulTime & RTC_TLR_10SEC_M) >> RTC_TLR_10SEC_S)*10 +
             ((g_ulTime & RTC_TLR_1SEC_M) >> RTC_TLR_1SEC_S);
    tTime->ulSecond = ulTemp;

    tTime->ulWDay = xHWREG(RTC_DWR);
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
//! \note None
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

    xASSERT((tTime->ulFormat == RTC_TIME_24H) ||
            (tTime->ulFormat == RTC_TIME_12H_AM) ||
            (tTime->ulFormat == RTC_TIME_12H_PM));
    
    xASSERT((tTime->ulYear >= RTC_YEAR_OFFSET) &&
            (tTime->ulYear <= RTC_YEAR_OFFSET + 99));
    
    xASSERT((tTime->ulMonth >= 1) &&
            (tTime->ulMonth <= 12));
    
    xASSERT((tTime->ulMDay >= 1) &&
            (tTime->ulMDay <= 31));
    
    xASSERT((tTime->ulHour >= 0) &&
            (tTime->ulHour <= ((tTime->ulFormat == RTC_TIME_24H) ? 23:12)));

    ulTemp = RTCWriteEnable();
    if((xtBoolean)ulTemp != xtrue)
    {
        return;
    }
    if ((tTime->ulFormat & RTC_TSSR_24H_12H) == 0)
    {
        xHWREG(RTC_TSSR) &= ~RTC_TSSR_24H_12H;
        if (tTime->ulFormat == RTC_TIME_12H_PM)
        {
            tTime->ulHour += 20;
        }
    }
    else
    {
        xHWREG(RTC_TSSR) |= RTC_TSSR_24H_12H;
    }
    
    ulTemp = ((tTime->ulYear- RTC_YEAR_OFFSET) / 10) << 20;
    ulTemp |= (((tTime->ulYear - RTC_YEAR_OFFSET) % 10) << 16);
    ulTemp |= ((tTime->ulMonth / 10) << 12);
    ulTemp |= ((tTime->ulMonth % 10) << 8);
    ulTemp |= ((tTime->ulMDay / 10) << 4);
    ulTemp |= (tTime->ulMDay % 10);

    RTCWriteEnable();
    if (ulTimeAlarm == RTC_TIME_CURRENT)
    {
        xHWREG(RTC_CLR) = ulTemp;
        xHWREG(RTC_DWR) = tTime->ulWDay;
    }
    else
    {
        xHWREG(RTC_CAR) = ulTemp;
    }
    
    
    ulTemp = ((tTime->ulHour) / 10) << 20;
    ulTemp |= (((tTime->ulHour) % 10) << 16);
    ulTemp |= ((tTime->ulMinute / 10) << 12);
    ulTemp |= ((tTime->ulMinute % 10) << 8);
    ulTemp |= ((tTime->ulSecond / 10) << 4);
    ulTemp |= (tTime->ulSecond % 10);

    RTCWriteEnable();
    if (ulTimeAlarm == RTC_TIME_CURRENT)
    {
        xHWREG(RTC_TLR) = ulTemp;   
    }
    else
    {
        xHWREG(RTC_TAR) = ulTemp;
    }
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
//! \b RTC_INT_TIME_TICK,and \b RTC_INT_ALARM.
//! 
//! \note None
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
            ((ulIntType & RTC_INT_ALARM) == RTC_INT_ALARM));

    xHWREG(RTC_RIER) |= ulIntType; 
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
//! \brief Disable the time tick or alarm interrupt of RTC. 
//!
//! \param ulIntType is the bit mask of the interrupt sources to be disable.
//!
//! This function is to disable the time tick or alarm interrupt of RTC.
//!
//! The \e ulIntType parameter is the logical OR of any of the following:
//! \b RTC_INT_TIME_TICK,and \b RTC_INT_ALARM.
//! 
//! \note None
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
            ((ulIntType & RTC_INT_ALARM) == RTC_INT_ALARM));

    xHWREG(RTC_RIER) &= ~ulIntType;
}


//*****************************************************************************
//
//! \brief Set Frequecy Compenation Data of RTC. 
//!
//! \param ulFrequency is the RTC osillator clock X100, ex:3277365 means 32773.65.
//!
//! This function is to set Frequecy Compenation Data of RTC.
//!
//! The \e ulFrequency parameter is limited by the following conditions:
//! ulFrequency must bettwen 3276100 to 3277699.
//! 
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void
RTCFrequencyCompensationSet(unsigned long ulFrequency)
{
    unsigned long ulRegInt,ulRegFra;
        
    //
    // Check the arguments.
    //
    xASSERT(((ulFrequency) >= 3276100) &&
            ((ulFrequency) <= 3277699));

    ulRegInt = (ulFrequency/100) - RTC_FCR_REFERENCE;
    ulRegFra = (((ulFrequency%100)) * 60) / 100;
    RTCWriteEnable();
    xHWREG(RTC_FCR) = (ulRegInt << RTC_FCR_INTEGER_S) | ulRegFra;
}


//*****************************************************************************
//
//! \brief Set the tick mode of the RTC tick interrupt. 
//!
//! \param ulTickMode specifies the tick mode.
//!
//! This function is to set the tick mode of the RTC tick interrupt.
//!
//! The \e ulTickMode parameter is the one of any of the following:
//! \b RTC_TIME_TICK_1,     \b RTC_TIME_TICK_1_2,  \b RTC_TIME_TICK_1_4,
//! \b RTC_TIME_TICK_1_8,   \b RTC_TIME_TICK_1_16, \b RTC_TIME_TICK_1_32,
//! \b RTC_TIME_TICK_64,and \b RTC_TIME_TICK_1_128.
//! 
//! \note The tick mode can be read back after the RTC register access enable 
//! bit ENF (AER[16]) is active.
//!
//! \return None.
//
//*****************************************************************************
void 
RTCTickModeSet(unsigned long ulTickMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulTickMode == RTC_TIME_TICK_1) ||
            (ulTickMode == RTC_TIME_TICK_1_2) ||
            (ulTickMode == RTC_TIME_TICK_1_4) ||
            (ulTickMode == RTC_TIME_TICK_1_8) ||
            (ulTickMode == RTC_TIME_TICK_1_16) ||
            (ulTickMode == RTC_TIME_TICK_1_32) ||
            (ulTickMode == RTC_TIME_TICK_1_64) ||
            (ulTickMode == RTC_TIME_TICK_1_128));

    RTCWriteEnable();
    xHWREG(RTC_TTR) = ulTickMode;
}

//*****************************************************************************
//
//! \brief Get that this year is leap year or not. 
//!
//! \param None.
//!
//! This function is to get that this year is leap year or not. 
//! 
//! \note None
//!
//! \return xtBoolean value \b xtrue indicate that this year is leap year
//! \b xfalse indicate that this year is not a leap year.
//
//*****************************************************************************
xtBoolean
RTCIsLeapYear(void)
{
    return (xHWREG(RTC_LIR) == 0x1) ? xtrue : xfalse;
}


//*****************************************************************************
//
//! \brief Access Password to AER to make access other register enable. 
//!
//! \param None.
//!
//! This function is to access Password to AER to make access other register
//! enable.
//! 
//! \note None
//!
//! \return xtBoolean value \b xtrue write enabled \b xtrue enable write failed.
//
//*****************************************************************************
xtBoolean
RTCWriteEnable(void)
{
    unsigned long i = 0;
    unsigned long ulRetry = 100;
    
    //
    // After 200ms, Access enable wiil auto-clear. As soon as possible to do 
    // your setting
    //
RETRY:
    i = 0;
    xHWREG(RTC_AER) = 0xA965;
    for (i = 0 ; i < 0xFFFFFFFF ; i++)
    {
        //
        // check RTC_AER[16] to find out RTC write enable
        //
        xHWREG(RTC_AER) = 0xA965;
		
        if (xHWREG(RTC_AER) & RTC_AER_ENF)	
            break;
    }
    if (i == 0xFFFFFFFF)
    {
        ulRetry--;
        if(!ulRetry)
            return xfalse;
						
        goto RETRY;
    }
    return xtrue;
}

//*****************************************************************************
//
//! \brief Enable RTC Timer wake-up function that chip can be waken up from 
//! power down mode by Time Tick or Alarm Match.
//!
//! \param None.
//!
//! This function is to Enable RTC Timer wake-up function that chip can be  
//! waken up from power down mode by Time Tick or Alarm Match.
//! 
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
RTCWakeupEnable(void)
{
    RTCWriteEnable();
    xHWREG(RTC_TTR) |= RTC_TTR_TWKE;
}

//*****************************************************************************
//
//! \brief Disable RTC Timer wake-up function that chip can be waken up from 
//! power down mode by Time Tick or Alarm Match.
//!
//! \param None.
//!
//! This function is to disable RTC Timer wake-up function that chip can be  
//! waken up from power down mode by Time Tick or Alarm Match.
//! 
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
RTCWakeupDisable(void)
{
    RTCWriteEnable();
    xHWREG(RTC_TTR) &= ~RTC_TTR_TWKE;
}


