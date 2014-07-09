#ifndef _NUC1XX_RTC_H_
#define _NUC1XX_RTC_H_

//*****************************************************************************
//
//! \addtogroup NUC1xx_RTC
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
//! \addtogroup NUC1xx_RTC_Exported_APIs NUC1xx API
//! \brief NUC1xx RTC API Reference.
//! @{
//
//*****************************************************************************

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


#endif
