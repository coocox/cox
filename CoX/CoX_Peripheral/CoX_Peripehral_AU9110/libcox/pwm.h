#ifndef _AU9110_PWM_H_
#define _AU9110_PWM_H_

#include "hw_pwm.h"

//*****************************************************************************
//
//! \addtogroup AU9110_PWM
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PWM_Int_Type  AU9110 PWM Interrupt Type
//! \brief Values that show AU9110 PWM Interrupt Type
//! Values that can be passed to PWMIntEnable(),PWMIntDisable().
//! @{
//
//*****************************************************************************

//
//! PWM channels Interrupt 
//
#define PWM_INT_PWM             0x00000000

//
//! Capture Channels Falling Latch Interrupt 
//
#define PWM_INT_CAP_FALL        0x00000004

//
//! Capture Channels Rising Latch Interrupt 
//
#define PWM_INT_CAP_RISE        0x00000002

//
//! Capture Channels Rising and Falling Latch Interrupt 
//
#define PWM_INT_CAP_BOTH        0x00000006

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PWM_Event_Type AU9110 PWM Event Type
//! \brief Values that show AU9110 PWM Event Type
//! Values that can be passed to PWMIntEnable(),PWMIntDisable().
//! @{
//
//*****************************************************************************

//
//! The Interrupt event is PWM
//
#define PWM_EVENT_PWM           0x00000000

//
//! The Interrupt event is Capture  
//
#define PWM_EVENT_CAP           0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PWM_Channel AU9110 PWM Channel
//! \brief Values that show AU9110 PWM Channel
//! Values that can be passed to all the function in xpwm.c.
//! @{
//
//*****************************************************************************

//
//! Channel 0
//
#define PWM_CHANNEL0            0x00000000

//
//! Channel 1
//
#define PWM_CHANNEL1            0x00000001

//
//! Channel 2
//
#define PWM_CHANNEL2            0x00000002

//
//! Channel 3
//
#define PWM_CHANNEL3            0x00000003

//
//! Channel 4
//
#define PWM_CHANNEL4            0x00000004

//
//! Channel 5
//
#define PWM_CHANNEL5            0x00000005

//
//! Channel 6
//
#define PWM_CHANNEL6            0x00000006

//
//! Channel 7
//
#define PWM_CHANNEL7            0x00000007

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PWM_Clock_div AU9110 PWM Clock Divide
//! \brief Values that show AU9110 PWM Clock Divide
//! Values that can be passed to all the function in xpwm.c.
//! @{
//
//*****************************************************************************

//
//! Input clock divided by 1
//
#define PWM_CLOCK_DIV_1         0x00000004

//
//! Input clock divided by 2
//
#define PWM_CLOCK_DIV_2         0x00000000

//
//! Input clock divided by 4
//
#define PWM_CLOCK_DIV_4         0x00000001

//
//! Input clock divided by 8
//
#define PWM_CLOCK_DIV_8         0x00000002

//
//! Input clock divided by 16
//
#define PWM_CLOCK_DIV_16        0x00000003


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PWM_Config AU9110 PWM Configuration
//! \brief Values that show AU9110 PWM Configuration
//! Values that can be passed to PWMConfigure().
//! @{
//
//*****************************************************************************

//
//! One-Shot Mode
//
#define PWM_ONE_SHOT_MODE       0x00000000

//
//! Auto-reload Mode
//
#define PWM_TOGGLE_MODE         0x00000008

//
//! Inverter enable
//
#define PWM_OUTPUT_INVERTER_EN  0x00000004

//
//! Inverter disable
//
#define PWM_OUTPUT_INVERTER_DIS 0x00000000

//
//! Dead-Zone 0 Generator enable
//
#define PWM_DEAD_ZONE_EN        0x00000010

//
//! Dead-Zone 0 Generator enable
//
#define PWM_DEAD_ZONE_DIS       0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PWM_Freq_Config AU9110 PWM Frequency Configuration
//! \brief Values that show AU9110 PWM Frequency Configuration
//! Values that can be passed to PWMFrequencyConfig() as ulConfig.
//! @{
//
//*****************************************************************************

#define PWM_FREQ_CONFIG(a,b,c)  (( a<<24 ) | ( b<<16 ) | c)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PWM_Exported_APIs AU9110 PWM API
//! \brief AU9110 PWM API Reference.
//! @{
//
//*****************************************************************************

extern void PWMIntFlagClear(unsigned long ulBase, unsigned long ulChannel,
                            unsigned long ulIntType);

extern void PWMCAPEnable(unsigned long ulBase, unsigned long ulChannel);
extern void PWMCAPDisable(unsigned long ulBase, unsigned long ulChannel);
extern void PWMCAPInputEnable(unsigned long ulBase, unsigned long ulChannel);
extern void PWMCAPInputDisable(unsigned long ulBase, unsigned long ulChannel);
extern unsigned long PWMCAPRisingCounterGet(unsigned long ulBase, 
                                            unsigned long ulChannel);
extern unsigned long PWMCAPFallingCounterGet(unsigned long ulBase, 
                                             unsigned long ulChannel); 

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
