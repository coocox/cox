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
//! \brief ADC0 Interrupt Handler.
//!
//! If users want to user the ADC0 Callback feature, Users should promise 
//! that the ADC0 Handle in the vector table is ADCIntHandler.
//!
//! \return None.
//
//*****************************************************************************
unsigned long ADC0IntFucntion(void *pvCBData,
                                       unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
    ADCIntClear(ADC1_BASE, ADC_INT_END_CONVERSION);
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
  
    unsigned long ulAdcSeqNo[] = {0};

    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    xSysCtlDelay(10000);

    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
    //
    // configure GPIO pin as ADC function
    //
    xSPinTypeADC(ADC0, PA0);
    //
    // Reset ADC 
    //
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_ADC1);

    //
    // Set ADC clock source
    //
    xSysCtlPeripheralClockSourceSet(xSYSCTL_ADC0_MAIN, 4);

    //
    // Enable ADC clock 
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_ADC1);
 
    //
    // Set the length of converter
    //
    ADCConverLenSet(ADC1_BASE, 1, 1);

    //
    // Set the Index of converter Sequence
    //
    ADCSequenceIndexSet(ADC1_BASE, ulAdcSeqNo, ulAdcSeqNo);

    ADCSampLenSet(ADC1_BASE, 0, 128);

    //
    // A/D interrupt enable 
    //
    ADCIntEnable(ADC1_BASE, ADC_INT_END_CONVERSION);
    xIntEnable(xINT_ADC0);
    xADCIntCallbackInit(ADC1_BASE, ADC0IntFucntion);
    //
    // Software trigger enable
    //
    ADCProcessorTrigger(ADC1_BASE);
    //
    // A/D configure 
    //
    ADCRegularConfigure(ADC1_BASE, ADC_OP_SINGLE, ADC_TRIGGER_PROCESSOR);
    ADCDataRegularGet(ADC1_BASE, ADC_MODE_NORMAL);
}
