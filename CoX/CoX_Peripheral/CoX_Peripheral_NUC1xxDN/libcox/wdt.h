#ifndef _NUC1XX_WDT_H_
#define _NUC1XX_WDT_H_

//*****************************************************************************
//
//! \addtogroup NUC1xx_WDT
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup WDT_Function_Type WDT Function Type
//! \brief Values that show WDT Function Type
//! Values that can be passed to WDTimerFunctionEnable(),WDTimerFunctionDisable
//! ().
//! @{
//
//*****************************************************************************

//
//! Generate Interrupt when watch dog time out
//
#define WDT_INT_FUNCTION        0x00000040

//
//! Reset CPU when watch dog time out
//
#define WDT_RESET_FUNCTION      0x00000002

//
//! Watchdog timer timeout can wake-up chip from power down mode.
//
#define WDT_WAKEUP_FUNCTION     0x00000010

//
//! Watchdog Timer counter will keep going no matter ICE debug mode
//! acknowledged or not.
//
#define WDT_HOLD_IN_ICE         0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup WDT_Time_Interval_Config WDT Time Interval Configuration
//! \brief WDT Time Interval Configuration
//! Values that can be passed to WDTimerInit().
//! @{
//
//*****************************************************************************

//
//! Timeout Interval Selection is 2 4 * TWDT
//
#define WDT_INTERVAL_2_4T       0x00000000

//
//! Timeout Interval Selection is 2 6 * TWDT
//
#define WDT_INTERVAL_2_6T       0x00000100

//
//! Timeout Interval Selection is 2 8 * TWDT
//
#define WDT_INTERVAL_2_8T       0x00000200

//
//! Timeout Interval Selection is 2 10 * TWDT
//
#define WDT_INTERVAL_2_10T      0x00000300

//
//! Timeout Interval Selection is 2 12 * TWDT
//
#define WDT_INTERVAL_2_12T      0x00000400

//
//! Timeout Interval Selection is 2 14 * TWDT
//
#define WDT_INTERVAL_2_14T      0x00000500

//
//! Timeout Interval Selection is 2 16 * TWDT
//
#define WDT_INTERVAL_2_16T      0x00000600

//
//! Timeout Interval Selection is 2 18 * TWDT
//
#define WDT_INTERVAL_2_18T      0x00000700


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_WDT_Exported_APIs NUC1xx WDT API
//! \brief NUC1xx WDT API Reference.
//! @{
//! @{
//
//*****************************************************************************

extern void WDTRestartDelayPeriod(unsigned long ulBase, unsigned long ulPeriod);

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
