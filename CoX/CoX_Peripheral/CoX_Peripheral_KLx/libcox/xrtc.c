//*****************************************************************************
//
//! \file xrtc.c
//! \brief Driver for the RTC
//! \version V2.2.1.0
//! \date 11/11/2011
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
static xtEventCallback g_pfnRTCHandlerCallbacks[2]={0};

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
//! \brief RTC Alarm interrupt handler. Clear the RTC interrupt flag and  
//! execute the callback function.
//!
//! \param none.
//!
//! This function is the RTC Alarm interrupt handler,it will Clear the RTC 
//! Alarm interrupt flag and execute the callback function if there be one.
//!
//! \note There is only one source of this interrupt.It is RTC alarm interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
RTCAIntHandler(void)
{
    unsigned long ulEventFlags;
    
    ulEventFlags = (xHWREG(RTC_SR) & RTC_SR_TAF );

    //
    // Clear Int flags
    //
    xHWREG(RTC_TAR) = 0x00;
    
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
//! \brief RTC Seconds interrupt handler. Clear the RTC interrupt flag and  
//! execute the callback function.
//!
//! \param none.
//!
//! This function is the RTC Seconds interrupt handler,it will Clear the RTC 
//! Seconds interrupt flag and execute the callback function if there be one.
//!
//! \note There is only one source of this interrupt. 
//!       It is RTC Seconds interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
RTCSIntHandler(void)
{
    unsigned long ulEventFlags;
	
    ulEventFlags = (xHWREG(RTC_SR) & (RTC_SR_TOF | RTC_SR_TIF));
    if(ulEventFlags)
    {	
        //
        //! Clear TCE, or RTC_TSR can  not be written
        //	
        xHWREG(RTC_SR) &= ~RTC_SR_TCE;

        //
        //! Clear TOF and TIF
        //      	
        xHWREG(RTC_TSR) = 0x00000000;
    }
    
    //
    // Call Callback function
    //
    if(g_pfnRTCHandlerCallbacks[1] != 0)
    {
        g_pfnRTCHandlerCallbacks[1](0, 0, ulEventFlags, 0);
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
#define RTC_LPO 
    //
    //! Enable RTC Clock
    //    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_RTC);
    
    //
    //! When RTC is power on, write 0x01 to RTC_CR to reset all logic.
    //
    xHWREG(RTC_CR) = RTC_CR_SWR;
    xHWREG(RTC_CR) &= ~RTC_CR_SWR; 
    
    xHWREG(RTC_TCR) = 0;
    
    //
    //! Disable all the interrupt
    //
    xHWREG(RTC_IER) = 0x00000000;
    
    //
    //! Clear the SR[TIF] 
    //
    if(xHWREG(RTC_SR) & RTC_SR_TIF)
    {
        xHWREG(RTC_TSR) = 0x00;
    }   
    
    //
    //! The 32 kHz clock is not output to other peripherals.
    //
    xHWREG(RTC_CR) |= RTC_CR_CLKO;
    
#ifdef RTC_LPO    
    //
    //! select LPO(1kHz) for RTC clock 
    //
    xHWREG(SIM_SOPT1) |= ((1<<18)|(1<<19));
#endif
    
#ifdef RTC_OSC
   //
    //! select System oscillator (OSC32KCLK) for RTC clock 
    // 
    xHWREG(SIM_SOPT1) &= ~((1<<18)|(1<<19)); 
    
    //
    //! Enable the oscillator
    //
    xHWREGB(OSC0_CR) |= ((1 << 7) || (1 << 5));
    xHWREG(RTC_CR) |= RTC_CR_OSCE;
    
    //
    //! Waiting for 32K stable 
    //
    SysCtlDelay(1000);
#endif   
    
#ifdef RTC_CLKIN
    
#define PORTC_PCR1  0x4004b004
    //
    //! Ensure  PTC1 configured as RTC input clock
    //
    xHWREG(PORTC_PCR1) &= ~(0x7 << 8);
    xHWREG(PORTC_PCR1) |= (0x4 << 8);
    
    //
    //! RTC clock in
    //
    xHWREG(SIM_SOPT1) |= (0x2 << 18); 
#endif

    //
    //! Enable the RTC time counter
    //
    xHWREG(RTC_SR) |= RTC_SR_TCE;
    
    xIntEnable(INT_RTCS);
   
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
    xHWREG(RTC_SR) |= RTC_SR_TCE;
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
    xHWREG(RTC_SR) &= ~RTC_SR_TCE;
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
RTCTimeRead(tTime *tTime, unsigned long ulTimeAlarm, unsigned long ulFormat)
{
    unsigned long ulTick, ulTempDays, ulTempYear = RTC_YEAR_OFFSET;
    unsigned long  ulTempMonth = 0; 
    unsigned char ucMonthTbl[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30,
                                    31, 30, 31};
    //
    // Check the arguments.
    //
    xASSERT((ulTimeAlarm == RTC_TIME_CURRENT) ||
            (ulTimeAlarm == RTC_TIME_ALARM));
    xASSERT((ulFormat == RTC_TIME_24H) ||
            (ulFormat == RTC_TIME_12H_AM) ||
            (ulFormat == RTC_TIME_12H_PM));
			
    if(ulTimeAlarm == RTC_TIME_CURRENT)
    {
        ulTick = xHWREG(RTC_TSR);
    }
    else
    {
        ulTick = xHWREG(RTC_TAR);        
    }

    ulTempDays = ulTick / RTC_SECOND_A_DAY;
    ulTick = ulTick % RTC_SECOND_A_DAY;
    
    tTime->ulHour = ulTick / 3600;
    tTime->ulMinute = (ulTick % 3600)/60;
    tTime->ulSecond = (ulTick % 3600)%60;
    tTime->ulWDay = (ulTempDays + 6) % 7;
    
    if (ulFormat != RTC_TIME_24H)
    {
        if (tTime->ulHour > 12)
        {
            tTime->ulFormat = RTC_TIME_12H_PM;
            tTime->ulHour -= 12;
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
    
    if(ulTempDays > 0)
    {
        while(ulTempDays >= 365)
        {                          
            if(RTCIsLeapYear(ulTempYear))
            {
                if(ulTempDays >= 366)
                {
                    ulTempDays -= 366;
                }
                else 
                {
                    ulTempYear++;
                    break;
                }  
            }
            else 
            {
                ulTempDays -= 365;
            }
            ulTempYear++;  
        }   
        tTime->ulYear = ulTempYear;

        while(ulTempDays >= 28)
        {
            if(RTCIsLeapYear(ulTempYear) && ulTempMonth == 1)
            {
                if(ulTempDays >= 29)
                {
                    ulTempDays -= 29;
                }
                else 
                {
                    break;
                } 
            }
            else 
            {
                if(ulTempDays >= ucMonthTbl[ulTempMonth])
                {
                    ulTempDays -= ucMonthTbl[ulTempMonth];
                }
                else 
                {
                    break;
                }
            }
            ulTempMonth++;  
        }
        tTime->ulMonth = ulTempMonth + 1;
        tTime->ulMDay = ulTempDays + 1; 
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
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void
RTCTimeWrite(tTime *tTime, unsigned long ulTimeAlarm)
{
    unsigned long ulTempSeconds, ulTempDays = 0, ulTempHour, i;
    unsigned char ucMonthDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30,
                                    31, 30, 31};
    //
    // Check the arguments.
    //
    xASSERT((ulTimeAlarm == RTC_TIME_CURRENT) ||
            (ulTimeAlarm == RTC_TIME_ALARM));

    xASSERT((tTime->ulFormat == RTC_TIME_24H)    ||
            (tTime->ulFormat == RTC_TIME_12H_AM) ||
            (tTime->ulFormat == RTC_TIME_12H_PM));
    
    xASSERT((tTime->ulYear >= RTC_YEAR_OFFSET) &&
            (tTime->ulYear <= RTC_YEAR_OFFSET + 99));
    
    xASSERT((tTime->ulMonth >= 1) &&
            (tTime->ulMonth <= 12));
    
    xASSERT((tTime->ulMDay >= 1) &&
            (tTime->ulMDay <= 31));
    
    xASSERT((tTime->ulHour >= 0) &&
            (tTime->ulHour <= ((tTime->ulFormat == RTC_TIME_24H) ? 23 : 12)));

    ulTempHour = tTime->ulHour;
    if (tTime->ulFormat != RTC_TIME_24H)
    {
        if (tTime->ulFormat == RTC_TIME_12H_PM)
        {
            ulTempHour += 12;
        }
    }
    
    for(i = RTC_YEAR_OFFSET; i < tTime->ulYear; i++)
    {
        if(((i % 4 ==0) && (i % 100 !=0))||(i % 400 ==0))
        {
            ulTempDays += 366;
        }
        else
        {
            ulTempDays += 365;
        }
    }
    
    i = tTime->ulYear;
    if((((i % 4 ==0) && (i % 100 !=0))||(i % 400 ==0))&&(tTime->ulMonth > 2))
    {
        ulTempDays += 1;
    }
    for(i = 1; i < tTime->ulMonth; i++)
    {
        ulTempDays += ucMonthDay[i - 1];
    }
    
    ulTempDays += tTime->ulMDay - 1;
    
    ulTempSeconds = ulTempDays * RTC_SECOND_A_DAY + ulTempHour * 3600 + 
                      tTime->ulMinute * 60 + tTime->ulSecond;      
	
    if (ulTimeAlarm == RTC_TIME_CURRENT)
    {
        xHWREG(RTC_SR) &= ~RTC_SR_TCE; 
        xHWREG(RTC_TSR) = ulTempSeconds;   
    }
    else
    {
        xHWREG(RTC_TAR) = ulTempSeconds;
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
//! \b RTC_INT_TIME_TICK, \b RTC_INT_ALARM and \b RTC_INT_OVERFLOW.
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
            ((ulIntType & RTC_INT_ALARM) == RTC_INT_ALARM)         ||
            ((ulIntType & RTC_INT_OVERFLOW) == RTC_INT_OVERFLOW));

    xHWREG(RTC_IER) |= ulIntType; 
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the RTC.
//!
//! \param ulIntType is the interrupt sources.
//! \param xtPortCallback is callback for the RTC.
//!
//! Init interrupts callback for the RTC.
//!
//! The \e ulIntType parameter is the logical OR of any of the following:
//! \b RTC_INT_TIME_TICK, \b RTC_INT_ALARM and \b RTC_INT_OVERFLOW.
//!
//! \return None.
//
//*****************************************************************************
void
RTCIntCallbackInit(unsigned long ulIntType, xtEventCallback xtRTCCallback)
{
    if (ulIntType != RTC_INT_ALARM)
    {
        g_pfnRTCHandlerCallbacks[1] = xtRTCCallback;
    }
    else
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
//! \b RTC_INT_TIME_TICK, \b RTC_INT_ALARM and \b RTC_INT_OVERFLOW.
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
            ((ulIntType & RTC_INT_ALARM) == RTC_INT_ALARM)         ||
            ((ulIntType & RTC_INT_OVERFLOW) == RTC_INT_OVERFLOW));

    xHWREG(RTC_IER) &= ~ulIntType;
}

//*****************************************************************************
//
//! \brief Set Frequecy Compenation Data of RTC. 
//!
//! \param ulFreq is the RTC osillator clock X100, ex:3277365 means 32773.65.
//! \param ulFreq is the compensation interval in seconds from 1 to 256
//!
//! This function is to set Frequecy Compenation Data of RTC.
//!
//! The \e ulFreq parameter is limited by the following conditions:
//! ulFrequency must bettwen 3276100 to 3277699.
//! The \e ulSec written should be one less than the number of seconds
//! 
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void
RTCFrequencyCompensationSet(unsigned long ulFreq, unsigned long ulSec)
{
    unsigned long ulRegInt;
        
    //
    // Check the arguments.
    //
    xASSERT((ulFreq >= 3264100) && (ulFreq <= 3289699));
            
    ulRegInt = (ulFreq/100) - RTC_TCR_TCR_REFERENCE;
    if(ulRegInt < 128)
    {
        ulRegInt = 0x7F - ulRegInt;
    }
    else
    {
        ulRegInt = 0xFF - (ulRegInt - 128);
    }
    
    xHWREG(RTC_SR) &= ~RTC_SR_TCE;
    xHWREG(RTC_TCR) &= ~(RTC_TCR_CIR_M | RTC_TCR_TCR_M);
    xHWREG(RTC_TCR) |= ((ulRegInt << RTC_TCR_TCR_S) | (ulSec << RTC_TCR_CIR_S));
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
    xHWREG(RTC_CR) |= RTC_CR_WPE;
    xHWREG(RTC_IER) |= RTC_IER_WPON;	
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
    xHWREG(RTC_IER) &= ~RTC_IER_WPON;
    xHWREG(RTC_CR) &= ~RTC_CR_WPE;
}

//*****************************************************************************
//
//! \brief Get that this year is leap year or not. 
//!
//! \param ulYear is the year.
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
RTCIsLeapYear(unsigned long ulYear)
{
    if((((ulYear % 4) == 0 && (ulYear % 100) != 0)) || ((ulYear % 400) == 0))
    {
        return xtrue; 
    }
    else
    {
        return xfalse;
    }
}

//*****************************************************************************
//
//! \brief the RTC registers is Locked  and writes are ignored. 
//!
//! \param ulRegType is the RTC register type.
//!
//! This function is lock the RTC registers . 
//! 
//! The \e ulIntType parameter is the logical OR of any of the following:
//! \b RTC_LOCK_LR, \b RTC_LOCK_SR, \b RTC_LOCK_CR and \b RTC_LOCK_TR.
//!
//! \note None
//!
//! \return none
//
//*****************************************************************************
void
RTCRegisterWriteLock(unsigned long ulRegType)
{
    xASSERT(((ulRegType & RTC_LOCK_LR) == RTC_LOCK_LR) ||
            ((ulRegType & RTC_LOCK_SR) == RTC_LOCK_SR) ||
            ((ulRegType & RTC_LOCK_CR) == RTC_LOCK_CR) ||
            ((ulRegType & RTC_LOCK_TR) == RTC_LOCK_TR));
    
    xHWREG(RTC_LR) &= ~ulRegType;
}

//*****************************************************************************
//
//! \brief Enable the 32 kHz clock output to other peripherals. 
//!
//! \param none.
//!
//! This function is enable the 32 kHz clock output to other peripherals. 
//! 
//! \note None
//!
//! \return none
//
//*****************************************************************************
void 
RTCClockOutputPeripheralsEnable(void)
{
    xHWREG(RTC_CR) &= ~RTC_CR_CLKO;
}

//*****************************************************************************
//
//! \brief Disable the 32 kHz clock output to other peripherals. 
//!
//! \param none.
//!
//! This function is Disable the 32 kHz clock output to other peripherals. 
//! 
//! \note None
//!
//! \return none
//
//*****************************************************************************
void 
RTCClockOutputPeripheralsDisable(void)
{
    xHWREG(RTC_CR) |= RTC_CR_CLKO;
}

//*****************************************************************************
//
//! \brief Configure the oscillator loading capacitor. 
//!
//! \param ulCapVal is the loading capacitor value.
//!
//! This function is Disable the 32 kHz clock output to other peripherals. 
//! 
//! The \e ulIntType parameter is chosen with one of the following values:
//! \b RTC_OSC_CAP_SC2P, \b RTC_OSC_CAP_SC4P, \b RTC_OSC_CAP_SC8P and 
//! \b RTC_OSC_CAP_SC16P.
//!
//! \note None
//!
//! \return none
//
//*****************************************************************************
void 
RTCOscLoadCap(unsigned long ulCapVal)
{
    xASSERT((ulCapVal == RTC_OSC_CAP_SC2P) ||
            (ulCapVal == RTC_OSC_CAP_SC4P) ||
            (ulCapVal == RTC_OSC_CAP_SC8P) ||
            (ulCapVal == RTC_OSC_CAP_SC16P));
    
    xHWREG(RTC_CR) |= RTC_CR_CLKO;
}