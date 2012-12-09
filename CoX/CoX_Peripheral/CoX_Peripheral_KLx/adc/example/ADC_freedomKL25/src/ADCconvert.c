/**
  ***************************************************************************** 
  * @title   ADConvert.c
  * @author  0xc0170
  * @date    7 Dec 2012
  * @brief   This example configures the ADC Channel 15 (PC15), Single cycle on
  * 		 Freedom board KL25. One measurement is executed and 8-bit value returned.
  *******************************************************************************
  */

#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xhw_adc.h"
#include "xcore.h"
#include "xadc.h"

//
// ADC result and flag
//
unsigned long ulData;
xtBoolean ADCmeasured;

unsigned long ADCCallback(void *pvCBData, unsigned long ulEvent, unsigned long ulMsgParam, void *pvMsgData);

//*****************************************************************************
//
//! Initialize the ADC module and measure once
//!
//! \param None
//!
//! This function initializes the ADC including clock source, enables ADC.
//!	Measures one sample.
//!
//! \return none
//
//*****************************************************************************
void ADCconvertNoInt(void)
{
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
    // ADC0, convert once, software trigger
    //
    xADCConfigure(xADC0_BASE, xADC_MODE_SCAN_SINGLE_CYCLE, ADC_TRIGGER_PROCESSOR);
    
    //
    // Enable the adc, ADC channel 15
    //
    ADCSingleEndedChannelEnable(xADC0_BASE, xADC_CTL_CH15);
    
    //
    // Read the converted value
    //
    ulData = ADCDataGet(xADC0_BASE);
}

//*****************************************************************************
//
//! Initialize the ADC module and interrupts
//!
//! \param None
//!
//! This function initializes the ADC including clock source, enables ADC
//!	and interrupts. It measures once then disables interrupts.
//!
//! \return none
//
//*****************************************************************************
void ADCconvertInt(void)
{
	xtBoolean ReturnValue;

    //
    // Disable processor interrupts
    //
    ReturnValue = xIntMasterDisable();

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
    // Set clocks for ADC - bus clock without divider
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
    // Enable the ADC end of conversion interrupt
    //
    xADCIntEnable(xADC0_BASE, xADC_INT_END_CONVERSION);

    //
    // Install the callback interrupt
    //
    xADCIntCallbackInit(xADC0_BASE, ADCCallback);

    //
    // Enable the NVIC ADC interrupt
    //
    xIntEnable(xINT_ADC0);

    //
    // Enable interrupts
    //
    ReturnValue = xIntMasterEnable();

    //
    // Enable the adc, ADC channel 15, wait for interrupt to read a value
    //
    ADCSingleEndedChannelEnable(xADC0_BASE, xADC_CTL_CH15);

    while(1)
    {
    	if (ADCmeasured)
    	{
    		//
    		// Disable interrupts in ADC register
    		//
    		xADCIntDisable(xADC0_BASE, xADC_INT_END_CONVERSION);
        
    		//
    		//Zero result and flag
    		//
    		ADCmeasured = xfalse;
    		ulData = 0;
    	}
    }
}

//*****************************************************************************
//
//! \brief ADC callback interrupt
//!
//! \param None
//!
//! \return none
//
//*****************************************************************************
unsigned long ADCCallback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,void *pvMsgData)
{
    //
    // Read data from result register
    //
    ulData = xHWREG(xADC0_BASE + ADC0_RA);
    ADCmeasured = xtrue;

    return 0;
}
