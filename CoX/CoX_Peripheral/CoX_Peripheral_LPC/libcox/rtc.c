//*****************************************************************************
//
//! \file rtc.c
//! \brief Driver for the RTC
//! \version V2.2.1.0
//! \date 8/15/2014
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2014, CooCox 
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
#include "CoX.h"
#include "sysctl.h"
#include "hw_rtc.h"

//*****************************************************************************
//
// An array is RTC callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnRTCHandlerCallbacks = 0;

// RTC Mask code
// Note: Only for internal use!
#define SEC_MASK                BIT_MASK(32, 5, 0)
#define MIN_MASK                BIT_MASK(32, 5, 0)
#define HOUR_MASK               BIT_MASK(32, 4, 0)
#define DOM_MASK                BIT_MASK(32, 4, 0)
#define DOW_MASK                BIT_MASK(32, 2, 0)
#define DOY_MASK                BIT_MASK(32, 8, 0)
#define MONTH_MASK              BIT_MASK(32, 3, 0)
#define YEAR_MASK               BIT_MASK(32, 11, 0)

//*****************************************************************************
//
//! \brief  RTC interrupt handler.
//!
//!         This function is the RTC interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//! \return None.
//!
//
//*****************************************************************************
void RTCIntHandler(void)
{
    if(g_pfnRTCHandlerCallbacks != 0)
    {
        g_pfnRTCHandlerCallbacks(0, 0, 0, 0);
    }
    else
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief  Register user's interrupt callback function for the RTC.
//!
//! \param  [in] xtPortCallback is user callback for the RTC.
//!
//! \return None.
//
//*****************************************************************************
void xRTCIntCallbackInit(xtEventCallback pfnCallback)
{
    // Check the parameters.
    xASSERT(pfnCallback != 0);

    g_pfnRTCHandlerCallbacks = pfnCallback;
}

//*****************************************************************************
//
//! \brief  Get RTC Interrupt status.
//!         This function is used to get RTC interrupt status.
//!
//! \param  None.
//!
//! \return The status of RTC interrupt, which contains of the OR of following value:
//!         - \ref RTC_INT_INC
//!         - \ref RTC_INT_ALARM
//!
//
//*****************************************************************************
unsigned long RTCIntFlagGet(void)
{
    return xHWREG(RTC_BASE + RTC_ILR);
}

//*****************************************************************************
//
//! \brief  Check RTC status flag.
//!         This function is used to check whether special flag is set or not.
//!
//! \param  [in] ulFlags is the flag you want to check
//!         This value is the OR of the following value:
//!              - \ref RTC_INT_INC
//!              - \ref RTC_INT_ALARM
//!
//! \return The status of special flag.
//!         - xtrue The check flag has been set.
//!         - xflase The check flag has not been set.
//!
//
//*****************************************************************************
xtBoolean RTCIntFlagCheck(unsigned long ulFlags)
{
    xASSERT( !(ulFlags & ~( RTC_INT_INC | RTC_INT_ALARM )));

    if(xHWREG(RTC_BASE + RTC_ILR) & ulFlags)
    {
        return (xtrue);
    }
    else
    {
        return (xfalse);
    }
}

//*****************************************************************************
//
//! \brief  Clear RTC interrupt status flag.
//!         This function can be used to clear special RTC interrupt status flag.
//!
//! \param  [in] ulFlags is RTC interrupt status flag.
//!              This parameter can be OR of the following value:
//!              - \ref RTC_INT_INC
//!              - \ref RTC_INT_ALARM
//!
//! \return None.
//!
//
//*****************************************************************************
void RTCIntFlagClear(unsigned long ulFlags)
{
    xASSERT( !(ulFlags & ~( RTC_INT_INC | RTC_INT_ALARM )));
    xHWREG(RTC_BASE + RTC_ILR) |= ulFlags;
}

//*****************************************************************************
//
//! \brief  Enable RTC function and start counter.
//!
//! \param  None.
//!
//! \return None.
//
//*****************************************************************************
void xRTCStart(void)
{
    xHWREG(RTC_BASE + RTC_CCR) |= CCR_CLKEN;
}

//*****************************************************************************
//
//! \brief  Disable RTC function and start counter.
//!
//! \param  None.
//!
//! \return None.
//
//*****************************************************************************
void xRTCStop(void)
{
    xHWREG(RTC_BASE + RTC_CCR) &= ~CCR_CLKEN;
}

//*****************************************************************************
//
//! \brief  Reset and Initializes RTC counter and time value.
//!
//! \param  None.
//!
//! \return None.
//
//*****************************************************************************
void xRTCTimeInit(void)
{
    xHWREG(RTC_BASE + RTC_CCR) |= CCR_CTCRST;
    xHWREG(RTC_BASE + RTC_CCR) &= ~CCR_CTCRST;
}

//*****************************************************************************
//
//! \brief  Configure RTC interrupt mode.
//!         This function can be used to enable/disable rtc time/alarm interrupt.
//!
//! \param  [in] ulCfg is interrupt configure parameters.
//!              This value can be the logical OR of the following value:
//!              - \ref INT_SEC_EN         Enable second       interrupt
//!              - \ref INT_MIN_EN         Enable minute       interrupt
//!              - \ref INT_HOUR_EN        Enable hour         interrupt
//!              - \ref INT_DOM_EN         Enable day of month interrupt
//!              - \ref INT_DOW_EN         Enable day of week  interrupt
//!              - \ref INT_DOY_EN         Enable day of year  interrupt
//!              - \ref INT_MON_EN         Enable month        interrupt
//!              - \ref INT_YEAR_EN        Enable year         interrupt
//!              - \ref INT_SEC_DIS        Disable second       interrupt
//!              - \ref INT_MIN_DIS        Disable minute       interrupt
//!              - \ref INT_HOUR_DIS       Disable hour         interrupt
//!              - \ref INT_DOM_DIS        Disable day of month interrupt
//!              - \ref INT_DOW_DIS        Disable day of week  interrupt
//!              - \ref INT_DOY_DIS        Disable day of year  interrupt
//!              - \ref INT_MON_DIS        Disable month        interrupt
//!              - \ref INT_YEAR_DIS       Disable year         interrupt
//!              - \ref INT_ALARM_SEC_EN   Enable second       alarm interrupt
//!              - \ref INT_ALARM_MIN_EN   Enable minute       alarm interrupt
//!              - \ref INT_ALARM_HOUR_EN  Enable hour         alarm interrupt
//!              - \ref INT_ALARM_DOM_EN   Enable day of month alarm interrupt
//!              - \ref INT_ALARM_DOW_EN   Enable day of week  alarm interrupt
//!              - \ref INT_ALARM_DOY_EN   Enable day of year  alarm interrupt
//!              - \ref INT_ALARM_MON_EN   Enable month        alarm interrupt
//!              - \ref INT_ALARM_YEAR_EN  Enable year         alarm interrupt
//!              - \ref INT_ALARM_SEC_DIS  Disable second       alarm interrupt
//!              - \ref INT_ALARM_MIN_DIS  Disable minute       alarm interrupt
//!              - \ref INT_ALARM_HOUR_DIS Disable hour         alarm interrupt
//!              - \ref INT_ALARM_DOM_DIS  Disable day of month alarm interrupt
//!              - \ref INT_ALARM_DOW_DIS  Disable day of week  alarm interrupt
//!              - \ref INT_ALARM_DOY_DIS  Disable day of year  alarm interrupt
//!              - \ref INT_ALARM_MON_DIS  Disable month        alarm interrupt
//!              - \ref INT_ALARM_YEAR_DIS Disable year         alarm interrupt
//!
//! \return None.
//
//*****************************************************************************
void RTCIntCfg(unsigned long ulCfg)
{
    unsigned long ulTmpReg = 0;

    // Check the parameters.
    xASSERT(ulCfg != 0);

    // Configure Increment Interrupt.
    if(ulCfg & 0x0000FFFF)
    {
        ulTmpReg = xHWREG(RTC_BASE + RTC_CIIR);
        ulTmpReg &= ~((ulCfg >> 8) & 0xFF);
        ulTmpReg |=  ((ulCfg >> 0) & 0xFF);
        xHWREG(RTC_BASE + RTC_CIIR) = ulTmpReg;
    }

    // Configure Alarm Interrupt.
    if(ulCfg & 0xFFFF0000)
    {
        ulTmpReg = xHWREG(RTC_BASE + RTC_AMR);
        ulTmpReg &= ~((ulCfg >> 24) & 0xFF);
        ulTmpReg |=  ((ulCfg >> 16) & 0xFF);
        xHWREG(RTC_BASE + RTC_AMR) = ulTmpReg;
    }
}

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
void xRTCIntEnable(unsigned long ulIntType)
{
    // Check parameters valid.
    xASSERT(( ulIntType == xRTC_INT_SECOND ) ||
            ( ulIntType == xRTC_INT_ALARM  ) ||
            ( ulIntType == (xRTC_INT_SECOND | xRTC_INT_ALARM) ));

    // Enable RTC second interrupt.
    if(ulIntType & xRTC_INT_SECOND)
    {
        RTCIntCfg((INT_SEC_EN  | INT_MIN_DIS | INT_HOUR_DIS | INT_DOM_DIS  |
                   INT_DOW_DIS | INT_DOY_DIS | INT_MON_DIS  | INT_YEAR_DIS ));
    }

    // Enable RTC alarm interrupt.
    if(ulIntType & xRTC_INT_ALARM)
    {
        RTCIntCfg((INT_ALARM_SEC_EN  | INT_ALARM_MIN_EN  |
                   INT_ALARM_HOUR_EN | INT_ALARM_DOM_EN  |
                   INT_ALARM_DOW_EN  | INT_ALARM_DOY_EN  |
                   INT_ALARM_MON_EN  | INT_ALARM_YEAR_EN ));
    }
}

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
void xRTCIntDisable(unsigned long ulIntType)
{
    // Check parameters valid.
    xASSERT(( ulIntType == xRTC_INT_SECOND ) ||
            ( ulIntType == xRTC_INT_ALARM  ) ||
            ( ulIntType == (xRTC_INT_SECOND | xRTC_INT_ALARM) ));

    // Disable RTC second interrupt.
    if(ulIntType & xRTC_INT_SECOND)
    {
        RTCIntCfg((INT_SEC_DIS | INT_MIN_DIS | INT_HOUR_DIS | INT_DOM_DIS  |
                   INT_DOW_DIS | INT_DOY_DIS | INT_MON_DIS  | INT_YEAR_DIS ));
    }

    // Disable RTC alarm interrupt.
    if(ulIntType & xRTC_INT_ALARM)
    {
        RTCIntCfg((INT_ALARM_SEC_DIS  | INT_ALARM_MIN_DIS  |
                   INT_ALARM_HOUR_DIS | INT_ALARM_DOM_DIS  |
                   INT_ALARM_DOW_DIS  | INT_ALARM_DOY_DIS  |
                   INT_ALARM_MON_DIS  | INT_ALARM_YEAR_DIS ));
    }
}

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
//! \todo   Finish this function.
//
//*****************************************************************************
void xRTCTimeRead(xtTime * pxtTime, unsigned long ulTimeAlarm)
{
    // Check parameters valid.
    xASSERT(pxtTime != 0);
    xASSERT((ulTimeAlarm == xRTC_TIME_CURRENT) || (ulTimeAlarm == xRTC_TIME_ALARM));

    switch(ulTimeAlarm)
    {
        case xRTC_TIME_CURRENT:
        {
            pxtTime->ulSecond = xHWREG(RTC_BASE + RTC_SEC) & SEC_MASK;;
            pxtTime->ulMinute = xHWREG(RTC_BASE + RTC_MIN) & MIN_MASK;
            pxtTime->ulHour   = xHWREG(RTC_BASE + RTC_HOUR) & HOUR_MASK;
            pxtTime->ulWDay   = xHWREG(RTC_BASE + RTC_DOW) & DOW_MASK;
            pxtTime->ulMDay   = xHWREG(RTC_BASE + RTC_DOM) & DOM_MASK;
            //pxtTime->ulYear   = xHWREG(RTC_BASE + RTC_DOY) & DOY_MASK;
            pxtTime->ulMonth  = xHWREG(RTC_BASE + RTC_MONTH) & MONTH_MASK;
            pxtTime->ulYear   = xHWREG(RTC_BASE + RTC_YEAR) & YEAR_MASK;
            break;
        }

        case  xRTC_TIME_ALARM:
        {
            pxtTime->ulSecond = xHWREG(RTC_BASE + RTC_ALSEC) & SEC_MASK;;
            pxtTime->ulMinute = xHWREG(RTC_BASE + RTC_ALMIN) & MIN_MASK;
            pxtTime->ulHour   = xHWREG(RTC_BASE + RTC_ALHOUR) & HOUR_MASK;
            pxtTime->ulWDay   = xHWREG(RTC_BASE + RTC_ALDOW) & DOW_MASK;
            pxtTime->ulMDay   = xHWREG(RTC_BASE + RTC_ALDOM) & DOM_MASK;
            //pxtTime->ulYear   = xHWREG(RTC_BASE + RTC_ALDOY) & DOY_MASK;
            pxtTime->ulMonth  = xHWREG(RTC_BASE + RTC_ALMONTH) & MONTH_MASK;
            pxtTime->ulYear   = xHWREG(RTC_BASE + RTC_ALYEAR) & YEAR_MASK;
            break;
        }
        default:                                      // Error
        {
            while(1);
        }
    }
}

//*****************************************************************************
//
//! \brief  Write current date/time or alarm date/time to RTC Module.
//!         This function is to configure current date/time or alarm date/time.
//!
//! \param  [out] xtTime specifies the point of time and data.
//! \param  [in]  ulTimeAlarm specifies which will be read current time or alarm time.
//!               This parameter is the one of any of the following:
//!               - \ref xRTC_TIME_CURRENT  Get Current time.
//!               - \ref xRTC_TIME_ALARM    Get System Alarm.
//!
//! \return None.
//! \todo   Finish this function.
//
//*****************************************************************************
void xRTCTimeWrite(xtTime * pxtTime, unsigned long ulTimeAlarm)
{
    // Check parameters valid.
    xASSERT(pxtTime != 0);
    xASSERT((ulTimeAlarm == xRTC_TIME_CURRENT) || (ulTimeAlarm == xRTC_TIME_ALARM));

    if(pxtTime->ulSecond > 59) pxtTime->ulSecond = 59;
    if(pxtTime->ulMinute > 59) pxtTime->ulMinute = 59;
    if(pxtTime->ulHour > 23)   pxtTime->ulHour   = 23;
    if(pxtTime->ulWDay > 6)    pxtTime->ulWDay = 6;
    if(pxtTime->ulMDay > 31)   pxtTime->ulMDay = 31;
    //if(pxtTime->ulYear > 59) pxtTime->ulYear = 59;
    if(pxtTime->RTC_MONTH > 12) pxtTime->RTC_MONTH = 12;
	
    switch(ulTimeAlarm)
    {
        case xRTC_TIME_CURRENT:
        {
            xHWREG(RTC_BASE + RTC_SEC)   = pxtTime->ulSecond;
            xHWREG(RTC_BASE + RTC_MIN)   = pxtTime->ulMinute;
            xHWREG(RTC_BASE + RTC_HOUR)  = pxtTime->ulHour;
            xHWREG(RTC_BASE + RTC_DOW)   = pxtTime->ulWDay;
            xHWREG(RTC_BASE + RTC_DOM)   = pxtTime->ulMDay;
            //xHWREG(RTC_BASE + RTC_DOY)   = pxtTime->ulYear;
            xHWREG(RTC_BASE + RTC_MONTH) = pxtTime->ulMonth;
            xHWREG(RTC_BASE + RTC_YEAR)  = pxtTime->ulYear;
			break;
        }

        case xRTC_TIME_ALARM:
        {
            xHWREG(RTC_BASE + RTC_ALSEC)   = pxtTime->ulSecond;
            xHWREG(RTC_BASE + RTC_ALMIN)   = pxtTime->ulMinute;
            xHWREG(RTC_BASE + RTC_ALHOUR)  = pxtTime->ulHour;
            xHWREG(RTC_BASE + RTC_ALDOW)   = pxtTime->ulWDay;
            xHWREG(RTC_BASE + RTC_ALDOM)   = pxtTime->ulMDay;
            //xHWREG(RTC_BASE + RTC_ALDOY)   = pxtTime->ulYear;
            xHWREG(RTC_BASE + RTC_ALMONTH) = pxtTime->ulMonth;
            xHWREG(RTC_BASE + RTC_ALYEAR)  = pxtTime->ulYear;
            break;
        }
        default:                                      // Error
        {
            while(1);
        }
    }
}
