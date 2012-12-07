/**
  ***************************************************************************** 
  * @title   ADCconvert.c
  * @author  0xc0170
  * @date    30 Nov 2012
  * @brief   This example configures the ADC Channel 15 (PC15), Single cycle on
  *          Freedom board KL25. One measurement is executed and 8-bit value returned.
  *******************************************************************************
  */

#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xcore.h"
#include "xadc.h"

//*****************************************************************************
//
//! Initialize the ADC module and measure once
//!
//! \param None
//!
//! This function initializes the ADC including clock source, enables ADC.
//! Measures one sample.
//!
//! \return none
//
//*****************************************************************************
void ADCconvertNoInt(void)
{
    unsigned long ulValueLength;

    //
    // Configure System clock
    //
    xSysCtlClockSet(48000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    SysCtlDelay(1000000);
    
    //
    // Enable Peripheral ADC and GPIO PORT C
    //
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_ADC);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    
    //
    //Set clocks for ADC - bus clock without divider
    //
    xSysCtlPeripheralClockSourceSet(xSYSCTL_ADC0_MAIN,0);

    //
    // Configure pin PC1 for ADC
    //
    xSPinTypeADC(ADC15, PC1);

    //
    // ADC0, convert once, Processor trigger.
    //
    xADCConfigure(xADC0_BASE, xADC_MODE_SCAN_SINGLE_CYCLE, ADC_TRIGGER_PROCESSOR);
    
    //
    // Enable the adc, ADC channel 15
    //
    ADCSingleEndedChannelEnable(xADC0_BASE, 15);
    
    //
    // Read the converted value
    //
    ulValueLength = ADCDataGet(xADC0_BASE);
}
