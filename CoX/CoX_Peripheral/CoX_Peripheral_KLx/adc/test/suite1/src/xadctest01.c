//*****************************************************************************
//
//! @page xadc_testcase xadc register test
//!
//! File: @ref xadctest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xadc sub component.<br><br>
//! - \p Board: FREEDOM-KL25Z <br><br>
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
//	unsigned long ulxTrigSrc[] = {xADC_TRIGGER_EXT_PIN, xADC_TRIGGER_PROCESSOR};
//	unsigned long ulxAddr[] = {xADC0_BASE, 0};
//	unsigned long i, j, ulReadVal;
	//
	// Test ADC configure API
	//
/*
	for(i=0; i<1; i++)
	{
	    for(j=0; j<2; j++)
		{
		    xADCConfigure(ulxAddr[i], xADC_MODE_SCAN_SINGLE_CYCLE, ulxTrigSrc[j]);
			ulReadVal = xHWREG(ulxAddr[i] + ADC_CR1) & xADC_MODE_SCAN_SINGLE_CYCLE;
            TestAssert(xADC_MODE_SCAN_SINGLE_CYCLE == ulReadVal, "xadc API error!" );
            
		    xADCConfigure(ulxAddr[i], xADC_MODE_SCAN_CONTINUOUS, ulxTrigSrc[j]);
			ulReadVal = xHWREG(ulxAddr[i] + ADC_CR2) & xADC_MODE_SCAN_CONTINUOUS;
            TestAssert(xADC_MODE_SCAN_CONTINUOUS == ulReadVal, "xadc API error!" );

			ulReadVal = xHWREG(ulxAddr[i] + ADC_CR2) & ulxTrigSrc[j];
			TestAssert(ulxTrigSrc[j] == ulReadVal, "xadc API error!");
		}
	}
*/
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
        xADCIntEnable(xADC0_BASE, ulxAdcIntFlags[i]);
		ulReadVal = (xHWREG(xADC0_BASE + ADC0_SC1A) & ulxAdcIntFlags[i]);
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

	//
	// Test ADC configure API
	//
	for(i=0; i<1; i++)
	{
        xADCIntDisable(xADC0_BASE, ulxAdcIntFlags[i]);
		ulReadVal = (xHWREG(xADC0_BASE + ADC0_SC1A) & ulxAdcIntFlags[i]);
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
    xADCProcessorTrigger(xADC0_BASE);
	ulReadVal = (xHWREG(xADC0_BASE + ADC0_SC2) & ADC0_SC2_ADTRG_HARD);
	TestAssert(ulReadVal == 0, "xadc API error!" );

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
static void xadc001Setup(void)
{
    //
    // Enable ADC clock 
    //
    SysCtlPeripheralEnable( SYSCTL_PERIPH_ADC);

    //
    // Enable GPIO clock 
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    //
    // configure GPIO pin as ADC function
    //
    xSPinTypeADC(ADC0, PE20);

    //
    // Set ADC clock source
    //
    xSysCtlPeripheralClockSourceSet(xSYSCTL_ADC0_MAIN, 8);
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


