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
static void adcConfigTest(void)
{
    unsigned long ulAdcMode[] = {ADC_OP_SINGLE, ADC_OP_CONTINUOUS, ADC_OP_DISCONTINUOUS};
	unsigned long ulTrigSrc[] = {ADC_TRIGGER_GPTM0, ADC_TRIGGER_GPTM1, ADC_TRIGGER_EXT_PB0,
	             ADC_TRIGGER_EXT_PB1, ADC_TRIGGER_EXT_PB2, ADC_TRIGGER_EXT_PB3,
                 ADC_TRIGGER_EXT_PB4, ADC_TRIGGER_EXT_PB5, ADC_TRIGGER_EXT_PB6,
				 ADC_TRIGGER_EXT_PB7, ADC_TRIGGER_EXT_PB8, ADC_TRIGGER_EXT_PB9,
			  ADC_TRIGGER_EXT_PB10, ADC_TRIGGER_EXT_PB11, ADC_TRIGGER_EXT_PB12,
			  ADC_TRIGGER_EXT_PB13, ADC_TRIGGER_EXT_PB14, ADC_TRIGGER_EXT_PB15,
		    ADC_TRIGGER_GPTME_MT0, ADC_TRIGGER_GPTME_CH0, ADC_TRIGGER_GPTME_CH1,
		    ADC_TRIGGER_GPTME_CH2,ADC_TRIGGER_GPTME_CH3};
	unsigned long i, j, ulReadVal;
	//
	// Test ADC configure API
	//
	for(i=0; i<3; i++)
	{
	    for(j=0; j<24; j++)
		{
		    ADCConfigure(ADC_BASE, ulAdcMode[i], ulTrigSrc[j]);
			ulReadVal = xHWREG(ADC_BASE + ADC_CONV) & ADC_CONV_MODE_M;
            TestAssert(ulAdcMode[i] == ulReadVal, "xadc API error!" );

			ulReadVal = xHWREG(ADC_BASE + ADC_TSR);
			TestAssert(ulTrigSrc[j] == ulReadVal, "xadc API error!" );
		}
	}
}

//*****************************************************************************
//
//! \brief  adc api configure test.
//!
//! \return None.
//
//*****************************************************************************
static void adcSeqNoTest(void)
{
    unsigned long ulAdcSeqNo[] = {0, 1, 2, 3, 4, 5, 6, 7};
    unsigned long i;
	unsigned long ulChannelNo[8];

	ADCConverLenSet(ADC_BASE, 8, 3);
	//
	// Test ADC configure API
	//
    ADCSequenceIndexSet(ADC_BASE, ulAdcSeqNo);
	for(i=0; i<8; i++)
	{
        ulChannelNo[i] = (xHWREG(ADC_BASE + ADC_LST0 + (i/4)*4) & (0x07<<(8*(i%4))))
                                                                      >> (8*(i%4));
		TestAssert(ulAdcSeqNo[i] == ulChannelNo[i], "xadc API error!" );
	}
}

//*****************************************************************************
//
//! \brief  adc api configure test.
//!
//! \return None.
//
//*****************************************************************************
static void adcSeqLenTest(void)
{
    unsigned long i, j, ulSeqLength, ulSubLength;
	//
	// Test ADC configure API
	//
	for(i=1; i<17; i++)
	{
	    for(j=1; j<17; j++)
        {
			ADCConverLenSet(ADC_BASE, i, j);
			ulSeqLength = ((xHWREG(ADC_BASE + ADC_CONV) & ADC_CONV_SEQL_M) >> ADC_CONV_SEQL_S) + 1;
            TestAssert(i == ulSeqLength, "xadc API error!" );
			ulSubLength = ((xHWREG(ADC_BASE + ADC_CONV) & ADC_CONV_SUBL_M) >> ADC_CONV_SUBL_S) + 1;
            TestAssert(j == ulSubLength, "xadc API error!" );
		}
	}
}

//*****************************************************************************
//
//! \brief  adc api configure test of sampling time.
//!
//! \return None.
//
//*****************************************************************************
static void adcSampTimeTest(void)
{
    unsigned long ulAdcSampTime[] = {19, 11, 2, 39, 254, 75, 96, 127};
    unsigned long i, j, ulSamTime;


	//
	// Test ADC configure API
	//
	for(i=0; i<8; i++)
	{
        for(j=0; j<8; j++)
		{
		    ADCSampLenSet(ADC_BASE, i, ulAdcSampTime[j]);
			ulSamTime = xHWREG(ADC_BASE + ADC_STR0 + i*4);
			TestAssert(ulSamTime == ulAdcSampTime[j], "xadc API error!" );
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
static void adcIntEnableTest(void)
{
    unsigned long ulAdcIntFlags[] = {ADC_INT_END_CONVERSION, ADC_INT_END_SUBGROUP,
	                                 ADC_INT_END_CYCLE, ADC_INT_MONIL, ADC_INT_MONIU,
									 ADC_INT_OVERW};
    unsigned long i, ulReadVal, ulTemp;


	//
	// Test ADC configure API
	//
	for(i=0; i<6; i++)
	{
        ADCIntEnable(ADC_BASE, ulAdcIntFlags[i]);
		ulReadVal = (xHWREG(ADC_BASE + ADC_IMR) & ulAdcIntFlags[i]);
		ulTemp =  ulAdcIntFlags[i] | ulReadVal;
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
static void adcIntDisableTest(void)
{
    unsigned long ulAdcIntFlags[] = {ADC_INT_END_CONVERSION, ADC_INT_END_SUBGROUP,
	                                 ADC_INT_END_CYCLE, ADC_INT_MONIL, ADC_INT_MONIU,
									 ADC_INT_OVERW};
    unsigned long i, ulReadVal;


	//
	// Test ADC configure API
	//
	for(i=0; i<6; i++)
	{
        ADCIntDisable(ADC_BASE, ulAdcIntFlags[i]);
		ulReadVal = (xHWREG(ADC_BASE + ADC_IMR) & ulAdcIntFlags[i]);
		TestAssert(ulReadVal == 0, "xadc API error!" );
	}
}

//*****************************************************************************
//
//! \brief  adc api configure test of watchdog monitor enable.
//!
//! \return None.
//
//*****************************************************************************
static void adcMonitorEnTest(void)
{
    unsigned long ulAdcMoniID[] = {ADC_MONI_U, ADC_MONI_L};
    unsigned long i, ulReadVal;


	//
	// Test ADC configure API
	//
	for(i=0; i<2; i++)
	{
        ADCMoniEnable(ADC_BASE, ulAdcMoniID[i]);
		ulReadVal = (xHWREG(ADC_BASE + ADC_WCR) & ulAdcMoniID[i]);
		TestAssert(ulReadVal == ulAdcMoniID[i], "xadc API error!" );
	}
}

//*****************************************************************************
//
//! \brief  adc api configure test of watchdog monitor disable.
//!
//! \return None.
//
//*****************************************************************************
static void adcMonitorDisTest(void)
{
    unsigned long ulAdcMoniID[] = {ADC_MONI_U, ADC_MONI_L};
    unsigned long i, ulReadVal;


	//
	// Test ADC configure API
	//
	for(i=0; i<2; i++)
	{
        ADCMoniDisable(ADC_BASE, ulAdcMoniID[i]);
		ulReadVal = (xHWREG(ADC_BASE + ADC_WCR) & ulAdcMoniID[i]);
		TestAssert(ulReadVal == 0, "xadc API error!" );
	}
}

//*****************************************************************************
//
//! \brief  adc api configure test of watchdog monitor setting.
//!
//! \return None.
//
//*****************************************************************************
static void adcMonitorSetTest(void)
{
	unsigned long ulAdcThreshold[] = {12,489,523,4095,45,687,1,324};
    unsigned long i, ulReadVal;


	//
	// Test ADC configure API
	//
	for(i=0; i<8; i++)
	{
        ADCMonitorSet(ADC_BASE, ADC_MONI_U, ulAdcThreshold[i], i);

		ulReadVal = (xHWREG(ADC_BASE + ADC_UTR) & ADC_ADCUTR_ADUT_M);
		TestAssert(ulAdcThreshold[i] == ulReadVal, "xadc API error!");
		ulReadVal = ((xHWREG(ADC_BASE + ADC_WCR) & ADC_WCR_ADWCH_M) >> ADC_WCR_ADWCH_S);
		TestAssert(i == ulReadVal, "xadc API error!");
	}

	for(i=0; i<8; i++)
	{
        ADCMonitorSet(ADC_BASE, ADC_MONI_L, ulAdcThreshold[i], i);

		ulReadVal = (xHWREG(ADC_BASE + ADC_LTR) & ADC_ADCUTR_ADUT_M);
		TestAssert(ulAdcThreshold[i] == ulReadVal, "xadc API error!");
		ulReadVal = ((xHWREG(ADC_BASE + ADC_WCR) & ADC_WCR_ADWCH_M) >> ADC_WCR_ADWCH_S);
		TestAssert(i == ulReadVal, "xadc API error!");
	}

	for(i=0; i<8; i++)
	{
        ADCMonitorSet(ADC_BASE, ADC_MONI_L, ulAdcThreshold[i], ADC_MONITOR_ADWALL);

		ulReadVal = (xHWREG(ADC_BASE + ADC_LTR) & ADC_ADCUTR_ADUT_M);
		TestAssert(ulAdcThreshold[i] == ulReadVal, "xadc API error!");
		ulReadVal = xHWREG(ADC_BASE + ADC_WCR) & 0x00000004;
		TestAssert(ulReadVal == 0x00000004, "xadc API error!");
	}
}

//*****************************************************************************
//
//! \brief  adc api configure test of trigger Enable.
//!
//! \return None.
//
//*****************************************************************************
static void adcTriggerEnTest(void)
{
    unsigned long ulReadVal;

	//
	// Test ADC configure API
	//

    ADCGptmEventTrigger(ADC_BASE);
	ulReadVal = (xHWREG(ADC_BASE + ADC_TCR) & ADC_TCR_ADTM_EN);
	TestAssert(ulReadVal == ADC_TCR_ADTM_EN, "xadc API error!" );

    //
	// EXTI Event trigger
	//
    ADCExtiEventTrigger(ADC_BASE);
	ulReadVal = (xHWREG(ADC_BASE + ADC_TCR) & ADC_TCR_ADEXTI_EN);
	TestAssert(ulReadVal == ADC_TCR_ADEXTI_EN, "xadc API error!" );

	//
	// Software trigger
	//
    ADCProcessorTrigger(ADC_BASE);
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
    return "xadc, 001, adc register test";
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
    adcConfigTest();
    adcSeqNoTest();
    adcSeqLenTest();
    adcSampTimeTest();
    adcIntEnableTest();
    adcIntDisableTest();
    adcMonitorEnTest();
    adcMonitorDisTest();
    adcMonitorSetTest();
    adcTriggerEnTest();
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
// ADC test suits.
//
const tTestCase * const psPatternXadc00[] =
{
    &sTestXAdc001Register,
    0
};


