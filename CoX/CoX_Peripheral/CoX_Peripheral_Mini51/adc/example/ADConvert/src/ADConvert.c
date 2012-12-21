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
#include "xadc.h"

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
    // add your own code
    //
    //...
  
    return 0;
}

//*****************************************************************************
//
//! Ininite the ADC 
//!
//! \param None
//!
//! This function ininite the ADC including clock source and enable ADC 
//!
//! \return none
//
//*****************************************************************************
void ADConvert(void)
{
  
    unsigned long ulValueLength;
    unsigned long ulData[10];
    //
    // Set SysClk 36MHz using Extern 12M oscillator
    //
    xSysCtlClockSet(12000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    
    //
    // Enable Peripheral SPI0
    //
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_ADC);
    
    //
    // Configure Some GPIO pins as SPI Mode
    //
    xSPinTypeADC(ADC0, PF3);
    
    //
    // ADC Channel0 convert once, Software tirgger.
    //
    xADCConfigure(xADC0_BASE, xADC_MODE_SCAN_SINGLE_CYCLE, ADC_TRIGGER_PROCESSOR);
    
    //
    // Enable the channel0
    //
    xADCStepConfigure(xADC0_BASE, 1, xADC_CTL_CH0); 
      
    //
    // Enable the ADC end of conversion interrupt
    //  
    xADCIntEnable(xADC0_BASE, xADC_INT_END_CONVERSION);  
    
    //
    // install the call back interrupt
    //
    xADCIntCallbackInit(xADC0_BASE, ADCCallback);
    
    //
    // Enable the NVIC ADC interrupt
    //
    xIntEnable(xINT_ADC0);
    
    //
    // Enable the adc
    //
    xADCEnable(xADC0_BASE);
    
    //
    // Trigger to convert
    //
    xADCProcessorTrigger(xADC0_BASE);
    
    //
    // Read the convert value
    //
    ulValueLength = xADCDataGet(xADC0_BASE, ulData);
    while(1);

}
