//*****************************************************************************
//
//! @page xadc_testcase xadc register test
//!
//! File: @ref xadctest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xadc sub component.<br><br>
//! - \p Board: NUC140 <br><br>
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
//!\page test_xadc_register test_xadc_register
//!
//!<h2>Description</h2>
//!Test xadc register. <br>
//!
//
//*****************************************************************************

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
void
ADC0_IRQHandler(void)
{
    TestAssert( 1 == ADCIntStatus( ADC_BASE ), 
                                         "xadc API \"ADCIntStatus()\" error!" );
    ADCIntClear( ADC_BASE, 0 );
    
    TestEmitToken( 'T' );
}
//*****************************************************************************
//
//! \brief  adc api interrupt state and data get test.
//!
//! \return None.
//
//*****************************************************************************
static void adcapi_exp( void )
{
    //
    // A/D convert enable 
    //
    ADCEnable( ADC_BASE );
    //
    // A/D configure 
    //
    ADCConfigure( ADC_BASE, ADC_INPUT_DIFF | ADC_DIFF_UNSIGNED, ADC_OP_SINGLE, 
                                                        ADC_TRIGGER_PROCESSOR );
    //
    // A/D channel enable 
    //
    ADCChannelEnable( ADC_BASE, ADC_CHANNEL_0 );
    //
    // A/D interrupt enable 
    //
    ADCIntEnable( ADC_BASE, ADC_INT_END_CONVERSION );
    xIntEnable( INT_ADC );
    
    if ( 1 == ADCIntStatus( ADC_BASE ) )
    {
        ADCIntClear( ADC_BASE, ADC_INT_END_CONVERSION );
        TestAssert( 1 == ADCIntStatus( ADC_BASE ), 
                                          "xadc API \"ADCIntClear()\" error!" );
    }
    
    //
    // A/D convert start 
    //
    ADCProcessorTrigger( ADC_BASE );
    
    TestAssertQBreak( "T", "xadc interrupt function error!", 0xFFFFFFFF );
}

//*****************************************************************************
//
//! \brief Get the Test description of xadc001 register test.
//!
//! \return the desccription of the xadc001 test.
//
//*****************************************************************************
static char* xadc001GetTest( void )
{
    return "xadc, 001, xadc register test";
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
    xSPinTypeADC( ADC0, PA0 );
    xSPinTypeADC( ADC1, PA1 );
    xSPinTypeADC( ADC2, PA2 );
    //
    // Reset ADC 
    //
    SysCtlPeripheralReset( SYSCTL_PERIPH_ADC );
    //
    // Set ADC clock source
    //
    SysCtlPeripheralClockSourceSet( SYSCTL_PERIPH_ADC_S_EXT12M );
    //
    // Set ADC clock divider
    //
    SysCtlIPClockDividerSet( 31 );
    //
    // Enable ADC clock 
    //
    SysCtlPeripheralEnable( SYSCTL_PERIPH_ADC );
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
    adcapi_exp( );
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
const tTestCase sTestXAdc001Register = {
    xadc001GetTest,
    xadc001Setup,
    xadc001Execute,
    xadc001TearDown
};

//
// Xgpio test suits.
//
const tTestCase * const psPatternXadc[] =
{
    &sTestXAdc001Register,
    0
};


