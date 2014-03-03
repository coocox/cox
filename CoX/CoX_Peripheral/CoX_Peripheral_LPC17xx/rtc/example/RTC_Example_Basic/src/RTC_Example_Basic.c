/******************************************************************************
 * \file    RTC_Example_Basic.c
 * \brief   RTC basic operate example.
 * This example shows how to configure RTC and alarm interrupt.
 * 
 * First, we configure rtc second interrupt and alarm interrupt, so LED(PC3) will
 * blink interval 1s, when run to 1 minutes,  led will fast blink 3 times.
 * 
******************************************************************************/

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xdebug.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_rtc.h"
#include "xrtc.h"

#define TICK_SLOW              ((unsigned long)0xFFFFF)

void RTC_Example_Basic(void);

// Toggle LED
static void ToggleLed(void)
{
    static unsigned long LedStatus = 0;

    if (LedStatus)
    {
        LedStatus = 0;
        // LED OFF
        GPIOPinClr(GPIOC_BASE, GPIO_PIN_3);
    }
    else
    {
        LedStatus = 1;
        // LED ON
        GPIOPinSet(GPIOC_BASE, GPIO_PIN_3);
    }
}


unsigned long RTCHandler(void *pvCBData, unsigned long ulEvent,
                              unsigned long ulMsgParam, void *pvMsgData)
{

    // RTC increment interrupt
    if(RTCIntFlagCheck(RTC_INT_INC))
    {
        //Clear second increment interrupt
        RTCIntFlagClear(RTC_INT_INC);
        ToggleLed();
    }

    // RTC alarm match interrupt
    if(RTCIntFlagCheck(RTC_INT_ALARM))
    {
        //Clear alarm interrupt then reset counter.
        RTCIntFlagClear(RTC_INT_ALARM);
        RTCCounterReset();
        RTCTimeSet(RTC_TIMETYPE_SECOND,      0);
        RTCTimeSet(RTC_TIMETYPE_MINUTE,      0);
        RTCTimeSet(RTC_TIMETYPE_HOUR,        0);
        RTCTimeSet(RTC_TIMETYPE_DAYOFWEEK,   0);
        RTCTimeSet(RTC_TIMETYPE_DAYOFMONTH,  0);
        RTCTimeSet(RTC_TIMETYPE_DAYOFYEAR,   0);
        RTCTimeSet(RTC_TIMETYPE_MONTH,       0);
        RTCTimeSet(RTC_TIMETYPE_YEAR,        0);
        
        RTCAlarmSet(RTC_TIMETYPE_SECOND,     0);
        RTCAlarmSet(RTC_TIMETYPE_MINUTE,     1);
        RTCAlarmSet(RTC_TIMETYPE_HOUR,       0);
        RTCAlarmSet(RTC_TIMETYPE_DAYOFWEEK,  0);
        RTCAlarmSet(RTC_TIMETYPE_DAYOFMONTH, 0);
        RTCAlarmSet(RTC_TIMETYPE_DAYOFYEAR,  0);
        RTCAlarmSet(RTC_TIMETYPE_MONTH,      0);
        RTCAlarmSet(RTC_TIMETYPE_YEAR,       0);
    
        // Fast blink LED
        SysCtlDelay(TICK_SLOW);
        ToggleLed();

        SysCtlDelay(TICK_SLOW);
        ToggleLed();

        SysCtlDelay(TICK_SLOW);
        ToggleLed();
        
        SysCtlDelay(TICK_SLOW);
        ToggleLed();

        SysCtlDelay(TICK_SLOW);
        ToggleLed();

    }

    return (0);
}

void RTC_Example_Basic(void)
{ 
    //unsigned long ulTmp = 0;

    /********************** Configure System clock *************************/
    SysCtlClockSet(100000000, SYSCTL_OSC_INT | SYSCTL_XTAL_12_MHZ);
    SysCtlDelay(TICK_SLOW);

    // Configure LED(PC3) pin
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    xGPIOSPinTypeGPIOOutput(PC3);

    // Turn off LED
    GPIOPinClr(GPIOC_BASE, GPIO_PIN_3);

    // Disable NVIC RTC interrupt
    xIntDisable(xINT_RTC);
    RTCDisable();
    RTCIntCallbackInit(RTCHandler);

    // Enable RTC second increment interrupt.
    // Enable RTC minute interrupt.
    RTCIntCfg( INT_SEC_EN          |   INT_MIN_DIS         |
               INT_HOUR_DIS        |   INT_DOM_DIS         |
               INT_DOW_DIS         |   INT_DOY_DIS         |
               INT_MON_DIS         |   INT_YEAR_DIS        |
               INT_ALARM_SEC_DIS   |   INT_ALARM_MIN_EN    |
               INT_ALARM_HOUR_DIS  |   INT_ALARM_DOM_DIS   |
               INT_ALARM_DOW_DIS   |   INT_ALARM_DOY_DIS   |
               INT_ALARM_MON_DIS   |   INT_ALARM_YEAR_DIS  );

    RTCTimeSet(RTC_TIMETYPE_SECOND,      0);
    RTCTimeSet(RTC_TIMETYPE_MINUTE,      0);
    RTCTimeSet(RTC_TIMETYPE_HOUR,        0);
    RTCTimeSet(RTC_TIMETYPE_DAYOFWEEK,   0);
    RTCTimeSet(RTC_TIMETYPE_DAYOFMONTH,  0);
    RTCTimeSet(RTC_TIMETYPE_DAYOFYEAR,   0);
    RTCTimeSet(RTC_TIMETYPE_MONTH,       0);
    RTCTimeSet(RTC_TIMETYPE_YEAR,        0);

    RTCAlarmSet(RTC_TIMETYPE_SECOND,     0);
    RTCAlarmSet(RTC_TIMETYPE_MINUTE,     1);
    RTCAlarmSet(RTC_TIMETYPE_HOUR,       0);
    RTCAlarmSet(RTC_TIMETYPE_DAYOFWEEK,  0);
    RTCAlarmSet(RTC_TIMETYPE_DAYOFMONTH, 0);
    RTCAlarmSet(RTC_TIMETYPE_DAYOFYEAR,  0);
    RTCAlarmSet(RTC_TIMETYPE_MONTH,      0);
    RTCAlarmSet(RTC_TIMETYPE_YEAR,       0);

    RTCEnable();
    RTCCounterReset();
    xIntEnable(xINT_RTC);

    while (1)
    {
        ; // DoNothing
    }
}

