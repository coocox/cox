#ifndef _NUC1XX_TIMER_H_
#define _NUC1XX_TIMER_H_

//*****************************************************************************
//
//! \addtogroup NUC1xx_TIMER
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Mode_Type TIMER Mode Type
//! \brief Values that show TIMER Mode Type
//! Values that can be passed to TimerInitConfig(),TimerCounterInitConfig
//! ().
//! @{
//
//*****************************************************************************

//
//! The timer is operating at the one-shot mode.
//
#define TIMER_MODE_ONESHOT      0x00000000

//
//! The timer is operating at the periodic mode.
//
#define TIMER_MODE_PERIODIC     0x08000000

//
//! The timer is operating at the toggle mode.
//
#define TIMER_MODE_TOGGLE       0x10000000

//
//! The timer is operating at continuous counting mode.
//
#define TIMER_MODE_CONTINUOUS   0x18000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Capture_Mode_Type TIMER Capture Mode Type
//! \brief Values that show TIMER Capture Mode Type
//! Values that can be passed to TimerCaptureModeSet() as ulCapMode .
//! @{
//
//*****************************************************************************

//
//! TEX transition is using as the timer counter reset function.
//
#define TIMER_CAP_MODE_RST      0x00000010

//
//! TEX transition is using as the timer capture function.
//
#define TIMER_CAP_MODE_CAP      0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup TIMER_INT_Type TIMER INT Type
//! \brief Values that show TIMER INT Type
//! Values that can be passed to TimerIntEnable(), TimerIntEnable() ,
//! TimerIntStatus(),TimerIntClear() as ulIntFlags .
//! @{
//
//*****************************************************************************

//
//! Timer match interrupt.
//
#define TIMER_INT_MATCH         0x20000000

//
//! Timer External capture interrupt.
//
#define TIMER_INT_CAP           0x00000020

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Counter_Pase_Type TIMER Counter Pase Type
//! \brief Values that show TIMER Counter Pase Type
//! Values that can be passed to TimerCounterDetectPhaseSelect() as ulPhase.
//! @{
//
//*****************************************************************************

//
//! A rising edge of external count pin will be counted.
//
#define TIMER_COUNTER_RISING    0x00000001

//
//! A falling edge of external count pin will be counted.
//
#define TIMER_COUNTER_FALLING   0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER_Capture_Edge_Type TIMER Capture Edge Type
//! \brief Values that show TIMER Capture Edge Type
//! Values that can be passed to TimerCaptureEdgeSelect() as ulPhase.
//! @{
//
//*****************************************************************************

//
//! a 0 to 1 transition on TEX will be detected.
//
#define TIMER_CAP_RISING        0x00000002

//
//! a 1 to 0 transition on TEX will be detected.
//
#define TIMER_CAP_FALLING       0x00000000

//
//! either 1 to 0 or 0 to 1 transition on TEX will be detected.
//
#define TIMER_CAP_BOTH          0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_TIMER_Exported_APIs NUC1xx TIMER API
//! \brief NUC1xx TIMER API Reference.
//! @{
//
//*****************************************************************************


extern void TimerCounterInitConfig(unsigned long ulBase, unsigned long ulConfig,
                       unsigned long ulCounterBound);

extern void TimerCaptureEnable(unsigned long ulBase);
extern void TimerCaptureDisable(unsigned long ulBase);

extern void TimerIntClear(unsigned long ulBase, unsigned long ulChannel,
                           unsigned long ulIntFlags);

extern void TimerCounterDebounceEnable(unsigned long ulBase);
extern void TimerCounterDebounceDisable(unsigned long ulBase);
extern void TimerCaptureDebounceEnable(unsigned long ulBase);
extern void TimerCaptureDebounceDisable(unsigned long ulBase);
extern void TimerExtClockFreqSet(unsigned long ulClockFreq);

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
