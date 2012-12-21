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
#include "xhw_sysctl.h"
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
unsigned long ulAdcAddress[] = {ADC_BASE};
unsigned long ulTrigSrcReg[] = {ADC_TRIGGER_EXT_PIN, ADC_TRIGGER_HSCMP0, 0, 0,
ADC_TRIGGER_PIT0,ADC_TRIGGER_PIT1, 0, 0, ADC_TRIGGER_TPM0, ADC_TRIGGER_TPM1,
ADC_TRIGGER_TPM2, 0, ADC_TRIGGER_RTC_ALARM, ADC_TRIGGER_RTC_SECONDS,
ADC_TRIGGER_LPTMR0, 0};

unsigned long i, j, ulReadVal, ulTemp;
//*****************************************************************************
//
//! \brief  adc api configure test.
//!
//! \return None.
//
//*****************************************************************************
static void adcConfigTest(void)
{
    
	//
	// Test ADC configure API
	//
	for(i=0; i<1; i++)
	{
	    for(j=0; j<16; j++)
		{
            if((j==2)||(j==3)||(j==6)||(j==7)||(j==11)||(j==15))
            {
                continue;
            }
		    ADCConfigure(ulAdcAddress[i], ADC_INPUT_SINGLE, ADC_OP_SINGLE, ulTrigSrcReg[j]);
			ulReadVal = xHWREG(SIM_SOPT7) & ulTrigSrcReg[j];
            TestAssert(j == ulReadVal, "xadc API error!" );
		}
	}

	//
	// Test ADC configure API
	//
	for(i=0; i<1; i++)
	{
        ADCDMAEnable(ulAdcAddress[i]);
	    ulReadVal = xHWREG(ulAdcAddress[i] + ADC0_SC2) & ADC0_SC2_DMAEN;
        TestAssert(ADC0_SC2_DMAEN == ulReadVal, "xadc API error!" );
	}
    
	for(i=0; i<1; i++)
	{
        ADCDMADisable(ulAdcAddress[i]);
	    ulReadVal = xHWREG(ulAdcAddress[i] + ADC0_SC2) & ADC0_SC2_DMAEN;
        TestAssert(0 == ulReadVal, "xadc API error!" );
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
    unsigned long ulAdcSampTime[] = {ADC_LONG_SAMPLE_TIME_24,
                                     ADC_LONG_SAMPLE_TIME_16,
                                     ADC_LONG_SAMPLE_TIME_10,
                                     ADC_LONG_SAMPLE_TIME_6};
    unsigned long j, ulSamTime;


    for(j=0; j<4; j++)
    {
        ADCLongSampleTimeSet(ADC_BASE, ulAdcSampTime[j]);
        ulSamTime = xHWREG(ADC_BASE + ADC0_CFG2) & ulAdcSampTime[j];
        TestAssert(ulSamTime == ulAdcSampTime[j], "xadc API error!" );
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
    unsigned long ulAdcIntFlags[] = {ADC_INT_END_CONVERSION, ADC_INT_COMP0};
    unsigned long i, ulReadVal, ulTemp;


	//
	// Test ADC1 configure API
	//
	for(i=0; i<2; i++)
	{
        ADCIntEnable(ADC_BASE, ulAdcIntFlags[i]);
		ulReadVal = (xHWREG(ADC_BASE + ADC0_SC1A) & ulAdcIntFlags[i]);
		ulTemp =  ulAdcIntFlags[i] & ulReadVal;
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
    unsigned long ulAdcIntFlags[] = {ADC_INT_END_CONVERSION, ADC_INT_COMP0};
    unsigned long i, ulReadVal;


	//
	// Test ADC1 configure API
	//
	for(i=0; i<2; i++)
	{
        ADCIntEnable(ADC_BASE, ulAdcIntFlags[i]);
		ulReadVal = (xHWREG(ADC_BASE + ADC0_SC1A) & ulAdcIntFlags[i]);
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
    unsigned long ulAdcMoniID[] = {0, 1};
    unsigned long i, ulReadVal;


	//
	// Test ADC1 configure API
	//
	for(i=0; i<1; i++)
	{
        ADCCompEnable(ADC_BASE, ulAdcMoniID[i]);
		ulReadVal = (xHWREG(ADC_BASE + ADC0_SC2) & ADC0_SC2_ACFE);
		TestAssert(ulReadVal == ADC0_SC2_ACFE, "xadc API error!" );
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
    unsigned long ulAdcMoniID[] = {0, 1};
    unsigned long i, ulReadVal;


	//
	// Test ADC1 configure API
	//
	for(i=0; i<1; i++)
	{
        ADCCompDisable(ADC_BASE, ulAdcMoniID[i]);
		ulReadVal = (xHWREG(ADC_BASE + ADC0_SC2) & ADC0_SC2_ACFE);
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
static void adcChannelEnableTest(void)
{
	//
	// Test single-ended channel
	//
	for(i=0; i<24; i++)
	{
        ADCSingleEndedChannelEnable(ADC_BASE, i);

		ulReadVal = (xHWREG(ADC_BASE + ADC0_SC1A) & ADC0_SC1A_ADCH_M);
		TestAssert(i == ulReadVal, "xadc API error!");
	}
    
	//
	// Test differential channel
	//
	for(i=0; i<4; i++)
	{
        ADCDiffChannelEnable(ADC_BASE, i);

		ulReadVal = (xHWREG(ADC_BASE + ADC0_SC1A) & ADC0_SC1A_ADCH_M);
		TestAssert(i == ulReadVal, "xadc API error!");
	}
}

//*****************************************************************************
//
//! \brief  adc api configure test of Resolution Set.
//!
//! \return None.
//
//*****************************************************************************
static void adcResolutionSetTest(void)
{
    unsigned long ulReadVal;
	unsigned long ulAdcThreshold[] = {12,489,523,4095,45,687,1,324,1254,598,5986,54,55555,58,47,58,15,65534};
	//
	// Test ADC Self Calibration Enable
	//
    ADCCalibrationEnable(ADC_BASE);
	ulReadVal = (xHWREG(ADC_BASE + ADC0_SC3) & ADC0_SC3_CAL);
	TestAssert(ADC0_SC3_CAL == ulReadVal, "xadc API error!" );

	//
	// Test ADC Self Calibration Disable
	//
    ADCCalibrationDisable(ADC_BASE);
	ulReadVal = (xHWREG(ADC_BASE + ADC0_SC3) & ADC0_SC3_CAL);
	TestAssert(0 == ulReadVal, "xadc API error!" );

	//
	// Test single-ended resolution mode
	//
	for(i=0; i<4; i++)
	{
        ADCDiffChannelEnable(ADC_BASE, i);

		ulReadVal = (xHWREG(ADC_BASE + ADC0_SC1A) & ADC0_SC1A_ADCH_M);
		TestAssert(i == ulReadVal, "xadc API error!");
	}

	//
	// Test differential resolution mode
	//
	for(i=0; i<4; i++)
	{
        ADCDifferentialResolutionSet(ADC_BASE, i);

		ulReadVal = (xHWREG(ADC_BASE + ADC0_SC1A) & ADC0_SC1A_ADCH_M);
		TestAssert(i == ulReadVal, "xadc API error!");
	}

	//
	// Test Long Sample Time Set
	//
	for(i=0; i<4; i++)
	{
        ADCLongSampleTimeSet(ADC_BASE, i);

		ulReadVal = (xHWREG(ADC_BASE + ADC0_CFG2) & ADC0_CFG2_ADLSTS_M);
		TestAssert(i == ulReadVal, "xadc API error!");
	}

    for(i=0; i<18; i++)
    {
        ADCGainSet(ADC_BASE, ulAdcThreshold[i], ulAdcThreshold[i]);
		ulReadVal = (xHWREG(ADC_BASE + ADC0_MG) & ADC0_MG_M);
		TestAssert(ulAdcThreshold[i] == ulReadVal, "xadc API error!");
		ulReadVal = (xHWREG(ADC_BASE + ADC0_PG) & ADC0_PG_M);
		TestAssert(ulAdcThreshold[i] == ulReadVal, "xadc API error!");
    }
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
    adcConfigTest();
    adcResolutionSetTest();
    adcSampTimeTest();
    adcIntEnableTest();
    adcIntDisableTest();
    adcChannelEnableTest();
    adcMonitorDisTest();
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
    xadc001TearDown,
    xadc001Execute

};

//
// ADC test suits.
//
const tTestCase * const psPatternXadc00[] =
{
    &sTestXAdc001Register,
    0
};


