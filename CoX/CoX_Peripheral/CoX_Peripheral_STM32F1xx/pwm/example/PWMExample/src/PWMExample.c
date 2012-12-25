//*****************************************************************************
//
//! \file SPI_loop.c
//! \brief Test SPI.
//! \version 1.0
//! \date 8/2/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xcore.h"
#include "xpwm.h"

//*****************************************************************************
//
//! \brief ADC0 Interrupt Handler.
//!
//! If users want to user the ADC0 Callback feature, Users should promise 
//! that the ADC0 Handle in the vector table is ADCIntHandler.
//!
//! \return None.
//
//*****************************************************************************
/*unsigned long ADC0IntFucntion(void *pvCBData,
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
    ADCIntClear(ADC_BASE, ADC_INT_END_CYCLE);
    return 0;
}
*/
//*****************************************************************************
//
//! Using PWM to control Led 
//!
//! \param None
//!
//! This function use the PWM to control Led 
//!
//! \return none
//
//*****************************************************************************
void PWMLedControl(void)
{
    //
    // Set System Clock
    //
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    SysCtlDelay(10000);

    //
    // Enable PWM
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMA);

    //
    // Configure Channel
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xSPinTypeTimer(TIM1CH1(APP), PA8);
    
    //
    // Configure PWM 
    //
    xPWMInitConfigure(xPWMA_BASE, xPWM_CHANNEL0, xPWM_OUTPUT_INVERTER_DIS|xPWM_DEAD_ZONE_DIS);

    //
    // Set PWM Frequency(1000Hz)
    //
    xPWMFrequencyConfig(xPWMA_BASE, xPWM_CHANNEL0, xPWM_FREQ_CONFIG(1,0x48,0x3E8));

    //
    // Set Channel0 Duty 
    //
    xPWMDutySet(xPWMA_BASE, xPWM_CHANNEL0, 10);

    //
    // Enable PWM Output
    //
    xPWMOutputEnable(xPWMA_BASE, xPWM_CHANNEL0);

    //
    // Start PWM
    //
    xPWMStart(xPWMA_BASE, xPWM_CHANNEL0);
}
