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
//!\page test_xadc_register test_xadc_register
//!
//!<h2>Description</h2>
//!Test xadc register. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief  adc api configure test.
//!
//! \return None.
//
//*****************************************************************************
static void xadcConfigTest(void)
{
    unsigned long ulxAdcMode[] = {xADC_MODE_SCAN_SINGLE_CYCLE, xADC_MODE_SCAN_CONTINUOUS};
	unsigned long ulxTrigSrc[] = {xADC_TRIGGER_EXT_PB2};
	unsigned long i, j, ulReadVal;
	//
	// Test ADC configure API
	//
	for(i=0; i<2; i++)
	{
	    for(j=0; j<1; j++)
		{
		    xADCConfigure(ADC_BASE, ulxAdcMode[i], ulxTrigSrc[j]);
			ulReadVal = xHWREG(ADC_BASE + ADC_CONV) & ADC_CONV_MODE_M;
            TestAssert(ulxAdcMode[i] == ulReadVal, "xadc API error!" );

			ulReadVal = xHWREG(ADC_BASE + ADC_TSR);
			TestAssert(ulxTrigSrc[j] == ulReadVal, "xadc API error!" );
		}
	}
}

//*****************************************************************************
//
//! \brief  adc api configure test of Interrupt enable.
//!
//! \return None.
//
//*****************************************************************************
static void xadcIntEnableTest(void)
{
    unsigned long ulxAdcIntFlags[] = {xADC_INT_END_CONVERSION};
    unsigned long i, ulReadVal, ulTemp;


	//
	// Test ADC configure API
	//
	for(i=0; i<1; i++)
	{
        xADCIntEnable(ADC_BASE, ulxAdcIntFlags[i]);
		ulReadVal = (xHWREG(ADC_BASE + ADC_IMR) & ulxAdcIntFlags[i]);
		ulTemp =  ulxAdcIntFlags[i] | ulReadVal;
		TestAssert(ulReadVal == ulTemp, "xadc API error!" );
	}
}

//*****************************************************************************
//
//! \brief  adc api configure test of Interrupt disable.
//!
//! \return None.
//
//*****************************************************************************
static void xadcIntDisableTest(void)
{
    unsigned long ulxAdcIntFlags[] = {xADC_INT_END_CONVERSION};
    unsigned long i, ulReadVal;

	ADCReset(ADC_BASE);
	//
	// Test ADC configure API
	//
	for(i=0; i<1; i++)
	{
        xADCIntDisable(ADC_BASE, ulxAdcIntFlags[i]);
		ulReadVal = (xHWREG(ADC_BASE + ADC_IMR) & ulxAdcIntFlags[i]);
		TestAssert(ulReadVal == 0, "xadc API error!" );
	}
}

//*****************************************************************************
//
//! \brief  adc api configure test of trigger Enable.
//!
//! \return None.
//
//*****************************************************************************
static void xadcTriggerEnTest(void)
{
    unsigned long ulReadVal;

	//
	// Software trigger
	//
    xADCProcessorTrigger(ADC_BASE);
	ulReadVal = (xHWREG(ADC_BASE + ADC_TCR) & ADC_TCR_ADSW_EN);
	TestAssert(ulReadVal == ADC_TCR_ADSW_EN, "xadc API error!" );

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
    return "xadc, 002, xadc register test";
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
    xSPinTypeADC(ADC1, PA1);
    xSPinTypeADC(ADC2, PA2);
	xSPinTypeADC(ADC3, PA3);
    xSPinTypeADC(ADC4, PA4);
    xSPinTypeADC(ADC5, PA5);
    xSPinTypeADC(ADC6, PA6);
	xSPinTypeADC(ADC7, PA7);
    //
    // Reset ADC 
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_ADC);

    //
    // Set ADC clock source
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_ADC_S_HCLK_8);

    //
    // Enable ADC clock 
    //
    SysCtlPeripheralEnable( SYSCTL_PERIPH_ADC);
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
    xadcConfigTest();
    xadcIntEnableTest();
    xadcIntDisableTest();
    xadcTriggerEnTest();
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
const tTestCase sTestXAdc002Register = {
    xadc001GetTest,
    xadc001Setup,
    xadc001TearDown,
    xadc001Execute
};

//
// ADC test suits.
//
const tTestCase * const psPatternXadc01[] =
{
    &sTestXAdc002Register,
    0
};


