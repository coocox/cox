/******************************************************************************
 * \file    PWM_Example_Basic.c
 * \brief   Show how to configure PWM single/double mode.
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
#include "xhw_pwm.h"
#include "xpwm.h"

#define TICK_SLOW              ((unsigned long)0xFFFFF)

void PWM_Example_Basic(void);

void PWM_Example_Basic(void)
{

    /********************** Configure System clock *************************/
    SysCtlClockSet(100000000, SYSCTL_OSC_INT | SYSCTL_XTAL_12_MHZ);
    SysCtlDelay(TICK_SLOW);

    // Map PWM1 channel 1 to PC0(P2.0)
    // Map PWM1 channel 2 to PC1(P2.1)
    xSPinTypePWM(PWM2, PC1);
    xSPinTypePWM(PWM3, PC2);

    // Power PWM module on
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);

    // Configure pwm prescale value
    // 1/100 system clock frequency
    PWMPrescaleValueSet(PWM1_BASE, 99);
    PWMMatchCfg(PWM1_BASE, PWM_CH_0, PWM_MATCH_RESET_EN);

    // Configure PWM channel match value
    PWMMatchUpdate(PWM1_BASE, PWM_CH_0, 100);
    PWMMatchUpdate(PWM1_BASE, PWM_CH_1, 41);
    PWMMatchUpdate(PWM1_BASE, PWM_CH_2, 78);
    PWMMatchUpdate(PWM1_BASE, PWM_CH_3, 65);

    // Configure mode(single/double)
    // Channel 1/2 is double mode.
    // Channel 3   is single mode.
    PWMEdgeCfg(PWM1_BASE, PWM_CH_0 | PWM_CH_1 | PWM_CH_3, PWM_EDGE_SINGLE);
    PWMEdgeCfg(PWM1_BASE, PWM_CH_2 , PWM_EDGE_DOUBLE);

    // Enable PWM channel output
    PWMOutPutEnable(PWM1_BASE, PWM_CH_2 | PWM_CH_3);

    // Start PWM counter
    PWMStart(PWM1_BASE);

    while (1)
    {
        ;// DoNothing
    }
}

