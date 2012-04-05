//*****************************************************************************
//
//! @page xadc_testcase xadc register test
//!
//! File: @ref xadctest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xadc sub component.<br><br>
//! - \p Board: HT32F125x <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. <br><br>
//! .
//!
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define:
//! <br>(1)None.<br><br>
//! - \p Option-hardware:
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:
//! <br>Connect an COM cable to the development board.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//!
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_xadc_register
//! .
//! \file xadctest.c
//! \brief xadc test source file
//! \brief xadc test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_adc.h"
#include "xadc.h"

//*****************************************************************************
//
//!\page test_xadc_register test_xadc_interrupt
//!
//!<h2>Description</h2>
//!Test xadc interrupt. <br>
//!
//
//*****************************************************************************


//*****************************************************************************
//
//! \brief Get the Test description of xadc001 register test.
//!
//! \return the desccription of the xadc001 test.
//
//*****************************************************************************
static char* xadc001GetTest( void )
{
    return "xadc, 003, xadc interrupt test";
}


//*****************************************************************************
//
//! \brief something should do before the test execute of xadc001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xadc001Setup( void )
{
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
}
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
    TestEmitToken('T');
	return 0;
}

//*****************************************************************************
//
//! \brief  adc api interrupt state and data get test.
//!
//! \return None.
//
//*****************************************************************************
static void adcIntTest(void)
{
	unsigned long ulAdcSeqNo[] = {0};
	unsigned long ulData;

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
	TestIOPut(ulData);
    TestAssertQBreak("T", "xadc interrupt function error!", 0xFFFFFFFF);
}
//*****************************************************************************
//
//! \brief xadc001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xadc001Execute( void )
{
    adcIntTest();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xadc001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xadc001TearDown( void )
{
    
}

//
// xadc001 register test case struct.
//
const tTestCase sTestXAdc003Register = {
    xadc001GetTest,
    xadc001Setup,
    xadc001Execute,
    xadc001TearDown
};

//
// ADC test suits.
//
const tTestCase * const psPatternXadc02[] =
{
    &sTestXAdc003Register,
    0
};


