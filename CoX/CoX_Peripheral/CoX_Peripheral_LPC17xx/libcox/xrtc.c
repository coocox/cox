#include "xhw_types.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xhw_rtc.h"
#include "xrtc.h"

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
void RTCIntCallbackInit(xtEventCallback pfnCallback)
{
    // Check the parameters.
    xASSERT(pfnCallback != 0);

    g_pfnRTCHandlerCallbacks = pfnCallback;
}

//*****************************************************************************
//
//! \brief Set RTC Time value.
//!        This function can be used to configure time value,
//!        for exampe, second/minute/hour/day and so on.
//!
//! \param [in] ulType is the type of time.
//!             This value can be one of the following value:
//!             - \ref RTC_TIMETYPE_SECOND
//!             - \ref RTC_TIMETYPE_MINUTE
//!             - \ref RTC_TIMETYPE_HOUR
//!             - \ref RTC_TIMETYPE_DAYOFWEEK
//!             - \ref RTC_TIMETYPE_DAYOFMONTH
//!             - \ref RTC_TIMETYPE_DAYOFYEAR
//!             - \ref RTC_TIMETYPE_MONTH
//!             - \ref RTC_TIMETYPE_YEAR
//!
//! \param [in] ulValue is the value of time, for different type of time, you
//!             must satisfied those condition.
//!             - \ref RTC_TIMETYPE_SECOND        0 <= ulValue <= 59
//!             - \ref RTC_TIMETYPE_MINUTE        0 <= ulValue <= 59
//!             - \ref RTC_TIMETYPE_HOUR          0 <= ulValue <= 23
//!             - \ref RTC_TIMETYPE_DAYOFWEEK     0 <= ulValue <= 6
//!             - \ref RTC_TIMETYPE_DAYOFMONTH    1 <= ulValue <= 31
//!             - \ref RTC_TIMETYPE_DAYOFYEAR     1 <= ulValue <= 366
//!             - \ref RTC_TIMETYPE_MONTH         1 <= ulValue <= 12
//!             - \ref RTC_TIMETYPE_YEAR          0 <= ulValue <= 4095
//!
//! \return None.
//
//*****************************************************************************
void RTCTimeSet(unsigned long ulType, unsigned long ulValue)
{
    switch(ulType)
    {
        case RTC_TIMETYPE_SECOND:          // Second
            {
                if(ulValue > 59)
                {
                    ulValue = 59;
                }
                xHWREG(RTC_BASE + RTC_SEC) = ulValue;
                break;
            }
        case RTC_TIMETYPE_MINUTE:          // Minute
            {
                if(ulValue > 59)
                {
                    ulValue = 59;
                }
                xHWREG(RTC_BASE + RTC_MIN) = ulValue;
                break;
            }
        case RTC_TIMETYPE_HOUR:            // Hour
            {
                if(ulValue > 23)
                {
                    ulValue = 23;
                }
                xHWREG(RTC_BASE + RTC_HOUR) = ulValue;
                break;
            }
        case RTC_TIMETYPE_DAYOFWEEK:       // Day of week
            {
                if(ulValue > 6)
                {
                    ulValue = 6;
                }
                xHWREG(RTC_BASE + RTC_DOW) = ulValue;
                break;
            }
        case RTC_TIMETYPE_DAYOFMONTH:      // Day of month
            {
                if(ulValue < 1)
                {
                    ulValue = 1;
                }
                if(ulValue > 31)
                {
                    ulValue = 31;
                }
                xHWREG(RTC_BASE + RTC_DOM) = ulValue;
                break;
            }
        case RTC_TIMETYPE_DAYOFYEAR:       // Day of year
            {
                if(ulValue < 1)
                {
                    ulValue = 1;
                }

                if(ulValue > 366)
                {
                    ulValue = 366;
                }
                xHWREG(RTC_BASE + RTC_DOY) = ulValue;
                break;
            }
        case RTC_TIMETYPE_MONTH:           // Month
            {
                if(ulValue < 1)
                {
                    ulValue = 1;
                }

                if(ulValue > 12)
                {
                    ulValue = 12;
                }
                xHWREG(RTC_BASE + RTC_MONTH) = ulValue;
                break;
            }
        case RTC_TIMETYPE_YEAR:            // Year
            {
                if(ulValue > 4095)
                {
                    ulValue = 4095;
                }
                xHWREG(RTC_BASE + RTC_YEAR) = ulValue;
                break;
            }
        default:
            {
                while(1);
            }
    }
}

//*****************************************************************************
//
//! \brief Get RTC Time
//!        This function can be used to get rtc time value,
//!        for exampe, second/minute/hour/day and so on.
//!
//! \param [in] ulType is the type of time.
//!             This value can be one of the following value:
//!             - \ref RTC_TIMETYPE_SECOND
//!             - \ref RTC_TIMETYPE_MINUTE
//!             - \ref RTC_TIMETYPE_HOUR
//!             - \ref RTC_TIMETYPE_DAYOFWEEK
//!             - \ref RTC_TIMETYPE_DAYOFMONTH
//!             - \ref RTC_TIMETYPE_DAYOFYEAR
//!             - \ref RTC_TIMETYPE_MONTH
//!             - \ref RTC_TIMETYPE_YEAR
//!
//! \return The value of time, for different type of time, value
//!             satisfied different range condition.
//!             - \ref RTC_TIMETYPE_SECOND        0 <= ulValue <= 59
//!             - \ref RTC_TIMETYPE_MINUTE        0 <= ulValue <= 59
//!             - \ref RTC_TIMETYPE_HOUR          0 <= ulValue <= 23
//!             - \ref RTC_TIMETYPE_DAYOFWEEK     0 <= ulValue <= 6
//!             - \ref RTC_TIMETYPE_DAYOFMONTH    1 <= ulValue <= 31
//!             - \ref RTC_TIMETYPE_DAYOFYEAR     1 <= ulValue <= 366
//!             - \ref RTC_TIMETYPE_MONTH         1 <= ulValue <= 12
//!             - \ref RTC_TIMETYPE_YEAR          0 <= ulValue <= 4095
//!
//
//*****************************************************************************
unsigned long RTCTimeGet(unsigned long ulType)
{
    switch(ulType)
    {
        case RTC_TIMETYPE_SECOND:          // Second
            {
                return xHWREG(RTC_BASE + RTC_SEC) & SEC_MASK;
                break;
            }
        case RTC_TIMETYPE_MINUTE:          // Minute
            {
                return xHWREG(RTC_BASE + RTC_MIN) & MIN_MASK;
                break;
            }
        case RTC_TIMETYPE_HOUR:            // Hour
            {
                return xHWREG(RTC_BASE + RTC_HOUR) & HOUR_MASK;
                break;
            }
        case RTC_TIMETYPE_DAYOFWEEK:       // Day of week
            {
                return xHWREG(RTC_BASE + RTC_DOW) & DOW_MASK;
                break;
            }
        case RTC_TIMETYPE_DAYOFMONTH:      // Day of month
            {
                return xHWREG(RTC_BASE + RTC_DOM) & DOM_MASK;
                break;
            }
        case RTC_TIMETYPE_DAYOFYEAR:       // Day of year
            {
                return xHWREG(RTC_BASE + RTC_DOY) & DOY_MASK;
                break;
            }
        case RTC_TIMETYPE_MONTH:           // Month
            {
                return xHWREG(RTC_BASE + RTC_MONTH) & MONTH_MASK;
                break;
            }
        case RTC_TIMETYPE_YEAR:            // Year
            {
                return xHWREG(RTC_BASE + RTC_YEAR) & YEAR_MASK;
                break;
            }
        default:
            {
                while(1);
            }
    }
}

//*****************************************************************************
//
//! \brief Set RTC alarm value.
//!        This function can be used to configure rtc alarm value,
//!        for exampe, second/minute/hour/day and so on.
//!
//! \param [in] ulType is the type of time.
//!             This value can be one of the following value:
//!             - \ref RTC_TIMETYPE_SECOND
//!             - \ref RTC_TIMETYPE_MINUTE
//!             - \ref RTC_TIMETYPE_HOUR
//!             - \ref RTC_TIMETYPE_DAYOFWEEK
//!             - \ref RTC_TIMETYPE_DAYOFMONTH
//!             - \ref RTC_TIMETYPE_DAYOFYEAR
//!             - \ref RTC_TIMETYPE_MONTH
//!             - \ref RTC_TIMETYPE_YEAR
//!
//! \param [in] ulValue is the value of time, for different type of time, you
//!             must satisfied those condition.
//!             - \ref RTC_TIMETYPE_SECOND        0 <= ulValue <= 59
//!             - \ref RTC_TIMETYPE_MINUTE        0 <= ulValue <= 59
//!             - \ref RTC_TIMETYPE_HOUR          0 <= ulValue <= 23
//!             - \ref RTC_TIMETYPE_DAYOFWEEK     0 <= ulValue <= 6
//!             - \ref RTC_TIMETYPE_DAYOFMONTH    1 <= ulValue <= 31
//!             - \ref RTC_TIMETYPE_DAYOFYEAR     1 <= ulValue <= 366
//!             - \ref RTC_TIMETYPE_MONTH         1 <= ulValue <= 12
//!             - \ref RTC_TIMETYPE_YEAR          0 <= ulValue <= 4095
//!
//! \return None.
//
//*****************************************************************************
void RTCAlarmSet(unsigned long ulType, unsigned long ulValue)
{
     switch(ulType)
    {
        case RTC_TIMETYPE_SECOND:          // Second
            {
                if(ulValue > 59)
                {
                    ulValue = 59;
                }
                xHWREG(RTC_BASE + RTC_ALSEC) = ulValue;
                break;
            }
        case RTC_TIMETYPE_MINUTE:          // Minute
            {
                if(ulValue > 59)
                {
                    ulValue = 59;
                }
                xHWREG(RTC_BASE + RTC_ALMIN) = ulValue;
                break;
            }
        case RTC_TIMETYPE_HOUR:            // Hour
            {
                if(ulValue > 23)
                {
                    ulValue = 23;
                }
                xHWREG(RTC_BASE + RTC_ALHOUR) = ulValue;
                break;
            }
        case RTC_TIMETYPE_DAYOFWEEK:       // Day of week
            {
                if(ulValue > 6)
                {
                    ulValue = 6;
                }
                xHWREG(RTC_BASE + RTC_ALDOW) = ulValue;
                break;
            }
        case RTC_TIMETYPE_DAYOFMONTH:      // Day of month
            {
                if(ulValue < 1)
                {
                    ulValue = 1;
                }
                if(ulValue > 31)
                {
                    ulValue = 31;
                }
                xHWREG(RTC_BASE + RTC_ALDOM) = ulValue;
                break;
            }
        case RTC_TIMETYPE_DAYOFYEAR:       // Day of year
            {
                if(ulValue < 1)
                {
                    ulValue = 1;
                }

                if(ulValue > 366)
                {
                    ulValue = 366;
                }

                xHWREG(RTC_BASE + RTC_ALDOY) = ulValue;
                break;
            }
        case RTC_TIMETYPE_MONTH:           // Month
            {
                if(ulValue < 1)
                {
                    ulValue = 1;
                }

                if(ulValue > 12)
                {
                    ulValue = 12;
                }
                xHWREG(RTC_BASE + RTC_ALMONTH) = ulValue;
                break;
            }
        case RTC_TIMETYPE_YEAR:            // Year
            {
                if(ulValue > 4095)
                {
                    ulValue = 4095;
                }
                xHWREG(RTC_BASE + RTC_ALYEAR) = ulValue;
                break;
            }
        default:
            {
                while(1);
            }
    }
}

//*****************************************************************************
//
//! \brief Get RTC alarm value.
//!        This function can be used to get rtc alarm time value,
//!        for exampe, second/minute/hour/day and so on.
//!
//! \param [in] ulType is the type of time.
//!             This value can be one of the following value:
//!             - \ref RTC_TIMETYPE_SECOND
//!             - \ref RTC_TIMETYPE_MINUTE
//!             - \ref RTC_TIMETYPE_HOUR
//!             - \ref RTC_TIMETYPE_DAYOFWEEK
//!             - \ref RTC_TIMETYPE_DAYOFMONTH
//!             - \ref RTC_TIMETYPE_DAYOFYEAR
//!             - \ref RTC_TIMETYPE_MONTH
//!             - \ref RTC_TIMETYPE_YEAR
//!
//! \return The value of time, for different type of time, value
//!             satisfied different range condition.
//!             - \ref RTC_TIMETYPE_SECOND        0 <= ulValue <= 59
//!             - \ref RTC_TIMETYPE_MINUTE        0 <= ulValue <= 59
//!             - \ref RTC_TIMETYPE_HOUR          0 <= ulValue <= 23
//!             - \ref RTC_TIMETYPE_DAYOFWEEK     0 <= ulValue <= 6
//!             - \ref RTC_TIMETYPE_DAYOFMONTH    1 <= ulValue <= 31
//!             - \ref RTC_TIMETYPE_DAYOFYEAR     1 <= ulValue <= 366
//!             - \ref RTC_TIMETYPE_MONTH         1 <= ulValue <= 12
//!             - \ref RTC_TIMETYPE_YEAR          0 <= ulValue <= 4095
//!
//
//*****************************************************************************
unsigned long RTCAlarmGet(unsigned long ulType)
{
     switch(ulType)
    {
        case RTC_TIMETYPE_SECOND:          // Second
            {
                return xHWREG(RTC_BASE + RTC_ALSEC) & SEC_MASK;
                break;
            }
        case RTC_TIMETYPE_MINUTE:          // Minute
            {
                return xHWREG(RTC_BASE + RTC_ALMIN) & MIN_MASK;
                break;
            }
        case RTC_TIMETYPE_HOUR:            // Hour
            {
                return xHWREG(RTC_BASE + RTC_ALHOUR) & HOUR_MASK;
                break;
            }
        case RTC_TIMETYPE_DAYOFWEEK:       // Day of week
            {
                return xHWREG(RTC_BASE + RTC_ALDOW) & DOW_MASK;
                break;
            }
        case RTC_TIMETYPE_DAYOFMONTH:      // Day of month
            {
                return xHWREG(RTC_BASE + RTC_ALDOM) & DOM_MASK;
                break;
            }
        case RTC_TIMETYPE_DAYOFYEAR:       // Day of year
            {
                return xHWREG(RTC_BASE + RTC_ALDOY) & DOY_MASK;
                break;
            }
        case RTC_TIMETYPE_MONTH:           // Month
            {
                return xHWREG(RTC_BASE + RTC_ALMONTH) & MONTH_MASK;
                break;
            }
        case RTC_TIMETYPE_YEAR:            // Year
            {
                return xHWREG(RTC_BASE + RTC_ALYEAR) & YEAR_MASK;
                break;
            }
        default:
            {
                while(1);
            }
    }
}

//*****************************************************************************
//
//! \brief  Write value to RTC general registers.
//!
//! \param  [in] ulID is the order of rtc general register.
//!              ulID can be one of the following value:
//!              - \ref RTC_REG_0
//!              - \ref RTC_REG_1
//!              - \ref RTC_REG_2
//!              - \ref RTC_REG_3
//!              - \ref RTC_REG_4
//!
//! \param  [in] ulValue is the data going to store into general register.
//!              0 <= ulValue <= 0xFFFFFFFF
//!
//! \return None.
//
//*****************************************************************************
void RTCGenRegWrite(unsigned long ulID, unsigned long ulValue)
{
    xHWREG(RTC_BASE + ulID) = ulValue;
}

//*****************************************************************************
//
//! \brief  Read value from RTC general registers.
//!
//! \param  [in] ulID is the order of rtc general register.
//!              ulID can be one of the following value:
//!              - \ref RTC_REG_0
//!              - \ref RTC_REG_1
//!              - \ref RTC_REG_2
//!              - \ref RTC_REG_3
//!              - \ref RTC_REG_4
//!
//! \return The value stored in general register.
//!              0 <= ulValue <= 0xFFFFFFFF
//!
//
//*****************************************************************************
unsigned long RTCGenRegRead(unsigned long ulID)
{
    return xHWREG(RTC_BASE + ulID);
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
void RTCEnable(void)
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
void RTCDisable(void)
{
    xHWREG(RTC_BASE + RTC_CCR) &= ~CCR_CLKEN;
}

//*****************************************************************************
//
//! \brief  Reset RTC counter and time value.
//!
//! \param  None.
//!
//! \return None.
//
//*****************************************************************************
void RTCCounterReset(void)
{
    xHWREG(RTC_BASE + RTC_CCR) |= CCR_CTCRST;
    xHWREG(RTC_BASE + RTC_CCR) &= ~CCR_CTCRST;
}

//*****************************************************************************
//
//! \brief  Enable RTC calibration function.
//!
//! \param  None.
//!
//! \return None.
//
//*****************************************************************************
void RTCCaliEnable(void)
{
    xHWREG(RTC_BASE + RTC_CCR) |= CCR_CCALEN;
}

//*****************************************************************************
//
//! \brief  Disable RTC calibration function.
//!
//! \param  None.
//!
//! \return None.
//
//*****************************************************************************
void RTCCaliDisable(void)
{
    xHWREG(RTC_BASE + RTC_CCR) &= ~CCR_CCALEN;
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
                break;
            }

        case  xRTC_TIME_ALARM:
            {
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

    switch(ulTimeAlarm)
    {
        case xRTC_TIME_CURRENT:
            {
                break;
            }

        case  xRTC_TIME_ALARM:
            {
                break;
            }
        default:                                      // Error
            {
                while(1);
            }
    }
}

