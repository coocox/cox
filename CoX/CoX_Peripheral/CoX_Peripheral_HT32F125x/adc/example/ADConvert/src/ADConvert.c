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
    ADCIntClear(ADC_BASE, ADC_INT_END_CYCLE);
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
    unsigned long ulData;

    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    SysCtlDelay(10000);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    //
    // configure GPIO pin as ADC function
    //
    xSPinTypeADC(ADC0, PA0);
    //
    // Reset ADC 
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_ADC);

    //
    // Set ADC clock source
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_ADC_S_HCLK_64);

    //
    // Enable ADC clock 
    //
    SysCtlPeripheralEnable( SYSCTL_PERIPH_ADC);
    ADCReset(ADC_BASE);
    //
    // Set the length of converter
    //
    ADCConverLenSet(ADC_BASE, 1, 1);
    //
    // Test ADC configure API
    //
    ADCSequenceIndexSet(ADC_BASE, ulAdcSeqNo);
    ADCSampLenSet(ADC_BASE, 0, 128);
    //
    // A/D interrupt enable 
    //
    ADCIntEnable(ADC_BASE, ADC_INT_END_CYCLE);
    xIntEnable(INT_ADC);
    xADCIntCallbackInit(ADC_BASE, ADC0IntFucntion);
    //
    // Software trigger enable
    //
    ADCProcessorTrigger(ADC_BASE);
    //
    // A/D configure 
    //
    ADCConfigure(ADC_BASE, ADC_OP_SINGLE, ADC_TRIGGER_PROCESSOR);
    ADCDataGet(ADC_BASE, &ulData);
}
