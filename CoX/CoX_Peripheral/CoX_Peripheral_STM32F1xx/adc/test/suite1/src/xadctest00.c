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
unsigned long ulAdcAddress[] = {ADC1_BASE, ADC2_BASE};
unsigned long ulTrigSrcReg[] = {ADC_TRIGGER_TIME1_CC1, ADC_TRIGGER_TIME1_CC2, ADC_TRIGGER_TIME1_CC3,
             ADC_TRIGGER_TIME2_CC2, ADC_TRIGGER_TIME3_TRGO, ADC_TRIGGER_TIME4_CC4,
             ADC_TRIGGER_TIME8_TRGO, ADC_TRIGGER_EXT_INT11, ADC_TRIGGER_PROCESSOR};

unsigned long ulTrigSrcInject[] = {ADC_TRIGGER_TIME1_TRGO, ADC_TRIGGER_TIME1_CC4, ADC_TRIGGER_TIME2_TRGO,
             ADC_TRIGGER_TIME2_CC1, ADC_TRIGGER_TIME3_CC4, ADC_TRIGGER_TIME4_TRGO,
             ADC_TRIGGER_TIME8_CC4, ADC_TRIGGER_EXT_INT15, ADC_TRIGGER_PROCESSORIN};

unsigned long ulDualMode[] = {ADC_MODE_REGINJECSIMULT, ADC_MODE_REGSIMULT_ALTERTRIG, ADC_MODE_INJECSIMULT_FASTINTERL,
             ADC_MODE_INJECSIMULT_SLOWINTERL, ADC_MODE_INJECSIMULT, ADC_MODE_REGSIMULT,
             ADC_MODE_FASTINTERL, ADC_MODE_SLOWINTERL, ADC_MODE_ALTERTRIG};

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
	for(i=0; i<2; i++)
	{
	    for(j=0; j<9; j++)
		{
		    ADCRegularConfigure(ulAdcAddress[i], ADC_OP_SINGLE, ulTrigSrcReg[j]);
			ulReadVal = xHWREG(ulAdcAddress[i] + ADC_CR2) & ADC_OP_SINGLE;
			ulTemp = xHWREG(ulAdcAddress[i] + ADC_CR2) & ulTrigSrcReg[j];
            TestAssert(0 == ulReadVal, "xadc API error!" );

			TestAssert(ulTrigSrcReg[j] == ulTemp, "xadc API error!" );
            
		    ADCRegularConfigure(ulAdcAddress[i], ADC_OP_REGULAR_DISCONTINUOUS, ulTrigSrcReg[j]);
			ulReadVal = xHWREG(ulAdcAddress[i] + ADC_CR1) & ADC_OP_REGULAR_DISCONTINUOUS;
            TestAssert(ADC_OP_REGULAR_DISCONTINUOUS == ulReadVal, "xadc API error!" );

		    ADCRegularConfigure(ulAdcAddress[i], ADC_OP_CONTINUOUS, ulTrigSrcReg[j]);
			ulReadVal = xHWREG(ulAdcAddress[i] + ADC_CR2) & ADC_OP_CONTINUOUS;
            TestAssert(ADC_OP_CONTINUOUS == ulReadVal, "xadc API error!" );
            
		    ADCRegularConfigure(ulAdcAddress[i], ADC_OP_SCAN, ulTrigSrcReg[j]);
			ulReadVal = xHWREG(ulAdcAddress[i] + ADC_CR1) & ADC_OP_SCAN;
            TestAssert(ADC_OP_SCAN == ulReadVal, "xadc API error!" );
       
		}
	}
    
	for(i=0; i<2; i++)
	{
	    for(j=0; j<9; j++)
		{
		    ADCInjectedConfigure(ulAdcAddress[i], ADC_OP_SINGLE, ulTrigSrcInject[j]);
			ulReadVal = xHWREG(ulAdcAddress[i] + ADC_CR2) & ADC_OP_SINGLE;
			ulTemp = xHWREG(ulAdcAddress[i] + ADC_CR2) & ulTrigSrcInject[j];
            TestAssert(0 == ulReadVal, "xadc API error!" );

			TestAssert(ulTrigSrcInject[j] == ulTemp, "xadc API error!" );
            
		    ADCInjectedConfigure(ulAdcAddress[i], ADC_OP_INJECT_DISCONTINUOUS, ulTrigSrcInject[j]);
			ulReadVal = xHWREG(ulAdcAddress[i] + ADC_CR1) & ADC_OP_INJECT_DISCONTINUOUS;
            TestAssert(ADC_OP_INJECT_DISCONTINUOUS == ulReadVal, "xadc API error!" );

		    ADCInjectedConfigure(ulAdcAddress[i], ADC_OP_CONTINUOUS, ulTrigSrcInject[j]);
			ulReadVal = xHWREG(ulAdcAddress[i] + ADC_CR2) & ADC_OP_CONTINUOUS;
            TestAssert(ADC_OP_CONTINUOUS == ulReadVal, "xadc API error!" );
            
		    ADCInjectedConfigure(ulAdcAddress[i], ADC_OP_SCAN, ulTrigSrcInject[j]);
			ulReadVal = xHWREG(ulAdcAddress[i] + ADC_CR1) & ADC_OP_SCAN;
            TestAssert(ADC_OP_SCAN == ulReadVal, "xadc API error!" );
       
		}
	}
	//
	// Test ADC configure API
	//
	for(i=0; i<2; i++)
	{
        ADCTemperatureRefVolEnable(ulAdcAddress[i]);
	    ulReadVal = xHWREG(ulAdcAddress[i] + ADC_CR2) & ADC_CR2_TSVREFE;
        TestAssert(ADC_CR2_TSVREFE == ulReadVal, "xadc API error!" );
	}
    
	for(i=0; i<2; i++)
	{
        ADCTemperatureRefVolDisable(ulAdcAddress[i]);
	    ulReadVal = xHWREG(ulAdcAddress[i] + ADC_CR2) & ADC_CR2_TSVREFE;
        TestAssert(0 == ulReadVal, "xadc API error!" );
	}

	//
	// Test ADC configure API
	//
	for(i=0; i<2; i++)
	{
        ADCDMAEnable(ulAdcAddress[i]);
	    ulReadVal = xHWREG(ulAdcAddress[i] + ADC_CR2) & ADC_CR2_DMA_EN;
        TestAssert(ADC_CR2_DMA_EN == ulReadVal, "xadc API error!" );
	}
    
	for(i=0; i<2; i++)
	{
        ADCDMADisable(ulAdcAddress[i]);
	    ulReadVal = xHWREG(ulAdcAddress[i] + ADC_CR2) & ADC_CR2_DMA_EN;
        TestAssert(0 == ulReadVal, "xadc API error!" );
	}
    

    for(j=0; j<9; j++)
    {
        ADCDualModeSet(ulDualMode[i]);
        ulReadVal = xHWREG(ADC1_BASE+ ADC_CR1) & ulDualMode[i];
        TestAssert(ulDualMode[i] == ulReadVal, "xadc API error!" );
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
    unsigned long ulAdcSeqNoReg[] = {0, 1, 2, 3, 4, 5, 6, 7};
    unsigned long ulAdcSeqNoInject[] = {0, 1, 2, 3, 4, 5, 6, 7};
    unsigned long i;
	unsigned long ulChannelNo[8];

	ADCConverLenSet(ADC1_BASE, 8, 3);
	//
	// Test ADC configure API
	//
    ADCSequenceIndexSet(ADC1_BASE, ulAdcSeqNoReg, ulAdcSeqNoInject);
	for(i=0; i<8; i++)
	{
        ulChannelNo[i] = (xHWREG(ADC1_BASE + ADC_SRQ3 - (i/6)*4) & (0x1F<<(5*(i%6))))
                                                                      >> (5*(i%6));
		TestAssert(ulAdcSeqNoReg[i] == ulChannelNo[i], "xadc API error!" );
	}
    
	ADCConverLenSet(ADC2_BASE, 8, 3);
	//
	// Test ADC configure API
	//
    ADCSequenceIndexSet(ADC2_BASE, ulAdcSeqNoReg, ulAdcSeqNoInject);
	for(i=0; i<8; i++)
	{
        ulChannelNo[i] = (xHWREG(ADC2_BASE + ADC_SRQ3 - (i/6)*4) & (0x1F<<(5*(i%6))))
                                                                      >> (5*(i%6));
		TestAssert(ulAdcSeqNoReg[i] == ulChannelNo[i], "xadc API error!" );
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
	    for(j=1; j<5; j++)
        {
			ADCConverLenSet(ADC1_BASE, i, j);
			ulSeqLength = ((xHWREG(ADC1_BASE + ADC_SRQ1) & ADC_SQR1_LEN_M) >> ADC_SQR1_LEN_S) + 1;
            TestAssert(i == ulSeqLength, "xadc API error!" );
			ulSubLength = ((xHWREG(ADC1_BASE + ADC_JSQR) & ADC_JSQR_LEN_M) >> ADC_JSQR_LEN_S) + 1;
            TestAssert(j == ulSubLength, "xadc API error!" );
		}
	}
    
	for(i=1; i<17; i++)
	{
	    for(j=1; j<5; j++)
        {
			ADCConverLenSet(ADC2_BASE, i, j);
			ulSeqLength = ((xHWREG(ADC2_BASE + ADC_SRQ1) & ADC_SQR1_LEN_M) >> ADC_SQR1_LEN_S) + 1;
            TestAssert(i == ulSeqLength, "xadc API error!" );
			ulSubLength = ((xHWREG(ADC2_BASE + ADC_JSQR) & ADC_JSQR_LEN_M) >> ADC_JSQR_LEN_S) + 1;
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
    unsigned long ulAdcSampTime[] = {ADC_SAMPTIME_1_5_CYCLE, ADC_SAMPTIME_7_5_CYCLE,
                                     ADC_SAMPTIME_13_5_CYCLE, ADC_SAMPTIME_28_5_CYCLE,
                                     ADC_SAMPTIME_41_5_CYCLE, ADC_SAMPTIME_55_5_CYCLE,
                                     ADC_SAMPTIME_71_5_CYCLE, ADC_SAMPTIME_239_5_CYCLE};
    unsigned long i, j, ulSamTime;


	//
	// Test ADC1 configure API
	//
	for(i=0; i<18; i++)
	{
        for(j=0; j<8; j++)
		{
		    ADCSampLenSet(ADC1_BASE, i, ulAdcSampTime[j]);
			ulSamTime = (xHWREG(ADC1_BASE + ADC_SMPR2 - (i/10)*4) >> ((i%10)*3)) & ulAdcSampTime[j];
			TestAssert(ulSamTime == ulAdcSampTime[j], "xadc API error!" );
		}
	}
    
	//
	// Test ADC2 configure API
	//
	for(i=0; i<18; i++)
	{
        for(j=0; j<8; j++)
		{
		    ADCSampLenSet(ADC2_BASE, i, ulAdcSampTime[j]);
			ulSamTime = (xHWREG(ADC2_BASE + ADC_SMPR2 - (i/10)*4) >> ((i%10)*3)) & ulAdcSampTime[j];
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
    unsigned long ulAdcIntFlags[] = {ADC_INT_END_CONVERSION, ADC_INT_END_JEOC, 
	                                 ADC_INT_AWD};
    unsigned long i, ulReadVal, ulTemp;


	//
	// Test ADC1 configure API
	//
	for(i=0; i<3; i++)
	{
        ADCIntEnable(ADC1_BASE, ulAdcIntFlags[i]);
		ulReadVal = (xHWREG(ADC1_BASE + ADC_CR1) & ulAdcIntFlags[i]);
		ulTemp =  ulAdcIntFlags[i] & ulReadVal;
		TestAssert(ulReadVal == ulTemp, "xadc API error!" );
	}
    
	//
	// Test ADC2 configure API
	//
	for(i=0; i<3; i++)
	{
        ADCIntEnable(ADC1_BASE, ulAdcIntFlags[i]);
		ulReadVal = (xHWREG(ADC2_BASE + ADC_CR1) & ulAdcIntFlags[i]);
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
    unsigned long ulAdcIntFlags[] = {ADC_INT_END_CONVERSION, ADC_INT_END_JEOC, 
	                                 ADC_INT_AWD};
    unsigned long i, ulReadVal;


	//
	// Test ADC1 configure API
	//
	for(i=0; i<3; i++)
	{
        ADCIntDisable(ADC1_BASE, ulAdcIntFlags[i]);
		ulReadVal = (xHWREG(ADC1_BASE + ADC_CR1) & ulAdcIntFlags[i]);
		TestAssert(ulReadVal == 0, "xadc API error!" );
	}
    
	//
	// Test ADC2 configure API
	//
	for(i=0; i<3; i++)
	{
        ADCIntDisable(ADC2_BASE, ulAdcIntFlags[i]);
		ulReadVal = (xHWREG(ADC2_BASE + ADC_CR1) & ulAdcIntFlags[i]);
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
    unsigned long ulAdcMoniID[] = {ADC_TYPE_REGULAR, ADC_TYPE_INJECTED};
    unsigned long i, ulReadVal;


	//
	// Test ADC1 configure API
	//
	for(i=0; i<2; i++)
	{
        ADCMoniEnable(ADC1_BASE, ulAdcMoniID[i]);
		ulReadVal = (xHWREG(ADC1_BASE + ADC_CR1) & ulAdcMoniID[i]);
		TestAssert(ulReadVal == ulAdcMoniID[i], "xadc API error!" );
	}
    
	//
	// Test ADC2 configure API
	//
	for(i=0; i<2; i++)
	{
        ADCMoniEnable(ADC2_BASE, ulAdcMoniID[i]);
		ulReadVal = (xHWREG(ADC2_BASE + ADC_CR1) & ulAdcMoniID[i]);
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
    unsigned long ulAdcMoniID[] = {ADC_TYPE_REGULAR, ADC_TYPE_INJECTED};
    unsigned long i, ulReadVal;


	//
	// Test ADC1 configure API
	//
	for(i=0; i<2; i++)
	{
        ADCMoniDisable(ADC1_BASE, ulAdcMoniID[i]);
		ulReadVal = (xHWREG(ADC1_BASE + ADC_CR1) & ulAdcMoniID[i]);
		TestAssert(ulReadVal == 0, "xadc API error!" );
	}
    
	//
	// Test ADC2 configure API
	//
	for(i=0; i<2; i++)
	{
        ADCMoniDisable(ADC2_BASE, ulAdcMoniID[i]);
		ulReadVal = (xHWREG(ADC2_BASE + ADC_CR1) & ulAdcMoniID[i]);
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
	unsigned long ulAdcThreshold[] = {12,489,523,4095,45,687,1,324,1254,598,0,54,89,58,47,58,15,98};
    unsigned long i, ulReadVal;


	//
	// Test ADC1 configure API
	//
	for(i=0; i<18; i++)
	{
        ADCMonitorSet(ADC1_BASE, ulAdcThreshold[i], ulAdcThreshold[i], i);

		ulReadVal = (xHWREG(ADC1_BASE + ADC_HTR) & ADC_HTR_M);
		TestAssert(ulAdcThreshold[i] == ulReadVal, "xadc API error!");
		ulReadVal = ((xHWREG(ADC1_BASE + ADC_LTR) & ADC_LTR_M) >> ADC_LTR_S);
		TestAssert(ulAdcThreshold[i] == ulReadVal, "xadc API error!");
		ulReadVal = (xHWREG(ADC1_BASE + ADC_CR1) & 0x0000001F);
		TestAssert(i == ulReadVal, "xadc API error!");
	}
    
	//
	// Test ADC2 configure API
	//
	for(i=0; i<18; i++)
	{
        ADCMonitorSet(ADC2_BASE, ulAdcThreshold[i], ulAdcThreshold[i], i);

		ulReadVal = (xHWREG(ADC2_BASE + ADC_HTR) & ADC_HTR_M);
		TestAssert(ulAdcThreshold[i] == ulReadVal, "xadc API error!");
		ulReadVal = ((xHWREG(ADC2_BASE + ADC_LTR) & ADC_LTR_M) >> ADC_LTR_S);
		TestAssert(ulAdcThreshold[i] == ulReadVal, "xadc API error!");
		ulReadVal = (xHWREG(ADC2_BASE + ADC_CR1) & 0x0000001F);
		TestAssert(i == ulReadVal, "xadc API error!");
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

    ADCProcessorTrigger(ADC1_BASE);
	ulReadVal = (xHWREG(ADC1_BASE + ADC_CR2) & ADC_CR2_SWSTART);
	TestAssert(0 == ulReadVal, "xadc API error!" );

    //
	// EXTI Event trigger
	//
    ADCProcessorInjectedTrigger(ADC1_BASE);
	ulReadVal = (xHWREG(ADC1_BASE + ADC_CR2) & ADC_CR2_JSWSTART);
	TestAssert(0 == ulReadVal, "xadc API error!" );

    //
	// EXTI Event trigger
	//
    ADCExtiEventInjecTrigger(ADC1_BASE);
	ulReadVal = (xHWREG(ADC1_BASE + ADC_CR2) & ADC_CR2_JEXTTRIG);
	TestAssert(ulReadVal == ADC_CR2_JEXTTRIG, "xadc API error!" );

	//
	// Software trigger
	//
    ADCExtiEventReguTrigger(ADC1_BASE);
	ulReadVal = (xHWREG(ADC1_BASE + ADC_CR2) & ADC_CR2_EXTTRIG);
	TestAssert(ulReadVal == ADC_CR2_EXTTRIG, "xadc API error!" );
    
	//
	// Test ADC configure API
	//

    ADCProcessorTrigger(ADC2_BASE);
	ulReadVal = (xHWREG(ADC2_BASE + ADC_CR2) & ADC_CR2_SWSTART);
	TestAssert(0 == ulReadVal, "xadc API error!" );

    //
	// EXTI Event trigger
	//
    ADCProcessorInjectedTrigger(ADC2_BASE);
	ulReadVal = (xHWREG(ADC2_BASE + ADC_CR2) & ADC_CR2_JSWSTART);
	TestAssert(0 == ulReadVal, "xadc API error!" );

    //
	// EXTI Event trigger
	//
    ADCExtiEventInjecTrigger(ADC2_BASE);
	ulReadVal = (xHWREG(ADC2_BASE + ADC_CR2) & ADC_CR2_JEXTTRIG);
	TestAssert(ulReadVal == ADC_CR2_JEXTTRIG, "xadc API error!" );

	//
	// Software trigger
	//
    ADCExtiEventReguTrigger(ADC2_BASE);
	ulReadVal = (xHWREG(ADC2_BASE + ADC_CR2) & ADC_CR2_EXTTRIG);
	TestAssert(ulReadVal == ADC_CR2_EXTTRIG, "xadc API error!" );

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
    SysCtlPeripheralReset(SYSCTL_PERIPH_ADC1);
    SysCtlPeripheralReset(SYSCTL_PERIPH_ADC1);

    //
    // Set ADC clock source
    //
//    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_ADC_S_HCLK_8);

    //
    // Enable ADC clock 
    //
    SysCtlPeripheralEnable( SYSCTL_PERIPH_ADC1);
    SysCtlPeripheralEnable( SYSCTL_PERIPH_ADC2);
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


