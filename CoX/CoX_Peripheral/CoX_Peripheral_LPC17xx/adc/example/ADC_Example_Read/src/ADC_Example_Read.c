/******************************************************************************
 * \file    ADC_Example_Read.c
 * \brief   ADC read data example
 * This example show how to use adc module to read channel2 analog data.
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
#include "xhw_adc.h"
#include "xadc.h"

#define TICK_SLOW              ((unsigned long)0xFFFFF)   //!< Slow Tick
#define BUF_SIZE               30                         //!< ADC Data Buf size

unsigned long ADCDataBuf[BUF_SIZE];

void ADC_Example_Read(void);

void ADC_Example_Read(void)
{
    unsigned long i = 0;

    /********************** Configure System clock *************************/
    SysCtlClockSet(100000000, SYSCTL_OSC_INT | SYSCTL_XTAL_12_MHZ);
    SysCtlDelay(TICK_SLOW);

    // Power ADC Module on
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC);

    // Map ADC Channel 2
    // P0.25 ---> Ch_2
    GPIOPinFunCfg(GPIOA_BASE, GPIO_PIN_25, GPIO_PA25_ADC2);
    GPIOPinModeCfg(GPIOA_BASE, GPIO_PIN_25, PIN_MODE_NONE);

    // 200K convert frequency.
    ADCInit(ADC_BASE, 200000);

    for(i = 0; i < BUF_SIZE; i++)
    {
        // Start ADC Channel 2, convert now.
        ADCStart(ADC_BASE, ADC_CH_2, ADC_START_MODE_NOW);

        // Wait Convert over.
        while(!ADCStatusCheck(ADC_BASE, ADC_CH_2, ADC_DONE));

        // Get Data
        ADCDataBuf[i] = ADCDataRead(ADC_BASE, ADC_CH_2);
    }

    while (1)
    {
        // DoNothing
    }
}

