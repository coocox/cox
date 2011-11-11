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
//! \brief  adc api configure test.
//!
//! \return None.
//
//*****************************************************************************
static void adcapi_config( void )
{
    typedef struct 
    {
        unsigned long ulBase;
        unsigned long ulInputMode;
        unsigned long ulOpMode;
        unsigned long ulTrigger;
        unsigned long ulResult;
    } Test;
    Test Sample_Test[] = { { ADC_BASE, ADC_INPUT_SINGLE, ADC_OP_SINGLE,
                                                   ADC_TRIGGER_PROCESSOR, 0 },
                           { ADC_BASE, ADC_INPUT_DIFF | ADC_DIFF_2C,
                                 ADC_OP_SINGLE_CYCLE, ADC_TRIGGER_PROCESSOR,
                                                                 0x80000408 },
                           { ADC_BASE, ADC_INPUT_DIFF | ADC_DIFF_UNSIGNED,
                                   ADC_OP_CONTINUOUS, ADC_TRIGGER_EXT_PB8 |
                                          ADC_TRIGGER_EXT_LOW_LEVEL, 0x050C } 
                         };
    
    unsigned int ullength = sizeof(Sample_Test) / sizeof(Test); 
    unsigned long ultemp = 0;
    unsigned int i = 0;
    for ( ; i < ullength; i++ )
    {
        ADCConfigure( Sample_Test[i].ulBase, Sample_Test[i].ulInputMode,
                            Sample_Test[i].ulOpMode, Sample_Test[i].ulTrigger );
    
        ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CR ) & (ADC_CR_DMOF |
                           ADC_CR_DIFFEN | ADC_CR_TRGEN | ADC_CR_TRGCOND_M |
                                                                ADC_CR_ADMD_M );
        TestAssert( ultemp == Sample_Test[i].ulResult,
                                         "xadc API \"ADCConfigure()\" error!" );
     }
}

//*****************************************************************************
//
//! \brief  adc api channel 7 configure test.
//!
//! \return None.
//
//*****************************************************************************
static void adcapi_ch7config( void )
{
    typedef struct 
    {
        unsigned long ulBase;
        unsigned long ulInputSrc;
        unsigned long ulResult;
    } Test;
    Test Sample_Test[] = { { ADC_BASE, ADC_CH7_EXT, 0        },
                           { ADC_BASE, ADC_CH7_INT_BV, 0x100 },
                           { ADC_BASE, ADC_CH7_INT_TS, 0x200 }
                         };
    
    unsigned int ullength = sizeof(Sample_Test) / sizeof(Test); 
    unsigned long ultemp = 0;
    unsigned int i = 0;
    for ( ; i < ullength; i++ )
    {
        ADCChannle7Configure( Sample_Test[i].ulBase, Sample_Test[i].ulInputSrc );
        
        ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CHER ) & ADC_CHER_PRESEL_M;
        
        TestAssert( ultemp == Sample_Test[i].ulResult,
                                 "xadc API \"ADCChannle7Configure()\" error!" );
    }
}

//*****************************************************************************
//
//! \brief  adc api calibration enable and disable test.
//!
//! \return None.
//
//*****************************************************************************
static void adcapi_calibrate( void )
{
    unsigned long ultemp = 0;
    
    ADCEnable(ADC_BASE);
    
    ADCCalibrationEnable( ADC_BASE );
    
    ultemp = xHWREG( ADC_BASE + ADC_CALR ) & ADC_CALR_CALEN;
    
    TestAssert( ultemp == 1, "xadc API \"ADCCalibrationEnable()\" error!" );
    
    for ( ultemp = 0; 0 == ultemp; )
    {
        if ( xtrue == ADCCalibrationDone( ADC_BASE ) )
        {
            ultemp = 1;
            TestAssert( 0x02 == ( xHWREG( ADC_BASE + ADC_CALR ) & ADC_CALR_CALDONE ),
                                   "xadc API \"ADCCalibrationDone()\" error!" );
        } else 
        {
            TestAssert( 0 == ( xHWREG( ADC_BASE + ADC_CALR ) & ADC_CALR_CALDONE ),
                                   "xadc API \"ADCCalibrationDone()\" error!" );
        }
    }
    
    ADCCalibrationDisable( ADC_BASE );
    
    ultemp = xHWREG( ADC_BASE + ADC_CALR ) & ADC_CALR_CALEN;
    
    TestAssert( ultemp == 0, "xadc API \"ADCCalibrationDisable()\" error!" );
}

//*****************************************************************************
//
//! \brief  adc api comparator x configure test.
//!
//! \return None.
//
//*****************************************************************************
static void adcapi_cmpconfig( void )
{
    typedef struct
    {
        unsigned long ulBase;
        unsigned long ulComp;
        unsigned long ulCompChannel;
        unsigned long ulCondition;
        unsigned long ulResult;
    } Test;
    Test Sample_Test[] = { { ADC_BASE, 0, ADC_CHANNEL_0, ADC_COMP_LESS_THAN, 0        },
                           { ADC_BASE, 1, ADC_CHANNEL_7, ADC_COMP_GREATER_EQUAL, 0x3C }
                         };
    
    unsigned int ullength = sizeof(Sample_Test) / sizeof(Test); 
    unsigned long ultemp = 0;
    unsigned int i = 0;
    for ( ; i < ullength; i++ )
    {
        ADCCompConfigure( Sample_Test[i].ulBase, Sample_Test[i].ulComp,
                     Sample_Test[i].ulCompChannel, Sample_Test[i].ulCondition );
        
        ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CMPR0 + 4 * Sample_Test[i].ulComp )
                                    & ( ADC_CMPRX_CMPCH_M | ADC_CMPRX_CMPCOND );
        
        TestAssert( ultemp == Sample_Test[i].ulResult,
                                     "xadc API \"ADCCompConfigure()\" error!" );
    }
}

//*****************************************************************************
//
//! \brief  adc api comparator x data set test.
//!
//! \return None.
//
//*****************************************************************************
static void adcapi_cmpdata( void )
{
    typedef struct
    {
        unsigned long ulBase;
        unsigned long ulComp;
        unsigned long ulCompData;
        unsigned long ulMatchCnt;
        unsigned long ulResult;
    } Test;
    Test Sample_Test[] = { { ADC_BASE, 0, 0, 0x8, 0x800       },
                           { ADC_BASE, 1, 0x666, 0, 0x6660000 }
                         };
    
    unsigned int ullength = sizeof(Sample_Test) / sizeof(Test); 
    unsigned long ultemp = 0;
    unsigned int i = 0;
    for ( ; i < ullength; i++ )
    {
        ADCConfigure( ADC_BASE, ADC_INPUT_DIFF | ADC_DIFF_UNSIGNED, ADC_OP_SINGLE, 
                                                        ADC_TRIGGER_PROCESSOR );
        ADCCompDataSet( Sample_Test[i].ulBase, Sample_Test[i].ulComp,
                         Sample_Test[i].ulCompData, Sample_Test[i].ulMatchCnt );
        
        ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CMPR0 + 4 * Sample_Test[i].ulComp )
                                 & ( ADC_CMPRX_CMPD_M | ADC_CMPRX_CMPMATCNT_M );
        
        TestAssert( ultemp == Sample_Test[i].ulResult,
                                      "xadc API \"ADCCompDataSet()\" error!" );
    }
    
}

//*****************************************************************************
//
//! \brief  adc api comparator x enable/disable test.
//!
//! \return None.
//
//*****************************************************************************
static void adcapi_comparator( void )
{
    typedef struct
    {
        unsigned long ulBase;
        unsigned long ulComp;
        unsigned long ulResult_En;
        unsigned long ulResult_Dis;
    } Test;
    Test Sample_Test[] = { { ADC_BASE, 0, 1, 0 }, 
                           { ADC_BASE, 1, 1, 0 }
                         };
    
    unsigned int ullength = sizeof(Sample_Test) / sizeof(Test); 
    unsigned long ultemp = 0;
    unsigned int i = 0;
    for ( ; i < ullength; i++ )
    {
        ADCCompEnable( Sample_Test[i].ulBase, Sample_Test[i].ulComp );
        
        ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CMPR0 + 4 * Sample_Test[i].ulComp )
                                                              & ADC_CMPRX_CMPEN; 
        TestAssert( ultemp == Sample_Test[i].ulResult_En, 
                                        "xadc API \"ADCCompEnable()\" error!" );
    }
    
    for ( i = 0; i < ullength; i++)
    {
        ADCCompDisable( Sample_Test[i].ulBase, Sample_Test[i].ulComp );
        
        ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CMPR0 + 4 * Sample_Test[i].ulComp )
                                                              & ADC_CMPRX_CMPEN; 
        TestAssert( ultemp == Sample_Test[i].ulResult_Dis, 
                                       "xadc API \"ADCCompDisable()\" error!" );
    }
    
}

//*****************************************************************************
//
//! \brief  adc api ad convert enable/disable test.
//!
//! \return None.
//
//*****************************************************************************
static void adcapi_convert( void )
{
    typedef struct
    {
        unsigned long ulBase;
        unsigned long ulResult_En;
        unsigned long ulResult_Dis;
    } Test;
    Test Sample_Test[] = { { ADC_BASE, 1, 0 }, 
                           { ADC_BASE, 1, 0 }
                         };
    
    unsigned int ullength = sizeof(Sample_Test) / sizeof(Test); 
    unsigned long ultemp = 0;
    unsigned int i = 0;
    for ( ; i < ullength; i++ )
    {
        ADCEnable( Sample_Test[i].ulBase );
        
        ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CR ) & ADC_CR_ADEN;
        
        TestAssert( ultemp == Sample_Test[i].ulResult_En, 
                                            "xadc API \"ADCEnable()\" error!" );
    }
    
    for ( i = 0; i < ullength; i++)
    {
        ADCDisable( Sample_Test[i].ulBase );
        
        ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CMPR0 ) & ADC_CR_ADEN;
        
        TestAssert( ultemp == Sample_Test[i].ulResult_Dis, 
                                           "xadc API \"ADCDisable()\" error!" );
    }
    
}

//*****************************************************************************
//
//! \brief  adc api ad channel enable/disable test.
//!
//! \return None.
//
//*****************************************************************************
static void adcapi_channel( void )
{
    typedef struct
    {
        unsigned long ulBase;
        unsigned long ulChannel;
        unsigned long ulResult_En;
        unsigned long ulResult_Dis;
    } Test;
    Test Sample_Test[] = { { ADC_BASE, ADC_CHANNEL_0, 0x01, 0 },
                           { ADC_BASE, ADC_CHANNEL_1, 0x02, 0 },
                           { ADC_BASE, ADC_CHANNEL_2, 0x04, 0 },
                           { ADC_BASE, ADC_CHANNEL_3, 0x08, 0 },
                           { ADC_BASE, ADC_CHANNEL_4, 0x10, 0 },
                           { ADC_BASE, ADC_CHANNEL_5, 0x20, 0 },
                           { ADC_BASE, ADC_CHANNEL_6, 0x40, 0 },
                           { ADC_BASE, ADC_CHANNEL_7, 0x80, 0 }
                         };
    
    unsigned int ullength = sizeof(Sample_Test) / sizeof(Test); 
    unsigned long ultemp = 0;
    unsigned int i = 0;
    for ( ; i < ullength; i++ )
    {
        ADCChannelEnable( Sample_Test[i].ulBase, Sample_Test[i].ulChannel );
        
        ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CHER ) & 
                                              ( 1 << Sample_Test[i].ulChannel );
        
        TestAssert( ultemp == Sample_Test[i].ulResult_En, 
                                     "xadc API \"ADCChannelEnable()\" error!" );
    }
    
    for ( i = 0; i < ullength; i++)
    {
        ADCChannelDisable( Sample_Test[i].ulBase, Sample_Test[i].ulChannel );
        
        ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CHER ) & 
                                              ( 1 << Sample_Test[i].ulChannel );
        
        TestAssert( ultemp == Sample_Test[i].ulResult_Dis, 
                                    "xadc API \"ADCChannelDisable()\" error!" );
    }
    
}

//*****************************************************************************
//
//! \brief  adc api pdma enable/disable test.
//!
//! \return None.
//
//*****************************************************************************
static void adcapi_pdma( void )
{
    unsigned long ultemp = 0;
    
    ADCIntDisable( ADC_BASE, ADC_INT_END_CONVERSION );
    
    ADCPDMAEnable( ADC_BASE );
    
    ultemp = xHWREG( ADC_BASE + ADC_CR ) & ADC_CR_PTEN;
    
    TestAssert( ultemp == 0x0200, "xadc API \"ADCPDMAEnable()\" error!" );
    
    ADCPDMADisable( ADC_BASE );
    
    ultemp = xHWREG( ADC_BASE + ADC_CR ) & ADC_CR_PTEN;
    
    TestAssert( ultemp == 0, "xadc API \"ADCPDMADisable()\" error!" );
}

//*****************************************************************************
//
//! \brief  adc api adc start/stop test.
//!
//! \return None.
//
//*****************************************************************************
static void adcapi_adc( void )
{
    ADCProcessorTrigger( ADC_BASE );
    
    TestAssert( 0x800 == ( xHWREG( ADC_BASE + ADC_CR ) & ADC_CR_ADST ), 
                                  "xadc API \"ADCProcessorTrigger()\" error!" );
    
    TestAssert( xtrue == ADCBusy( ADC_BASE ), "xadc API \"ADCBusy()\" error!" );
    
    ADCConvertStop( ADC_BASE );
    
    TestAssert( 0 == ( xHWREG( ADC_BASE + ADC_CR ) & ADC_CR_ADST ), 
                                       "xadc API \"ADCConvertStop()\" error!" );
    
    TestAssert( xfalse == ADCBusy( ADC_BASE ), "xadc API \"ADCBusy()\" error!" );
}

//*****************************************************************************
//
//! \brief  adc api adc interrupt enable/disable test.
//!
//! \return None.
//
//*****************************************************************************
static void adcapi_adcint( void )
{
    typedef struct
    {
        unsigned long ulBase;
        unsigned long ulIntFlags;
        unsigned long ulResult_En;
        unsigned long ulResult_Dis;
    } Test;
    Test Sample_Test[] = { { ADC_BASE, ADC_INT_END_CONVERSION, 0x02, 0 }, 
                           { ADC_BASE, ADC_INT_COMP0, 0x02, 0          },
                           { ADC_BASE, ADC_INT_COMP1, 0x02, 0          }
                         };
    
    unsigned int ullength = sizeof(Sample_Test) / sizeof(Test); 
    unsigned long ultemp = 0;
    unsigned int i = 0;
    for ( ; i < ullength; i++ )
    {
        ADCIntEnable( Sample_Test[i].ulBase, Sample_Test[i].ulIntFlags );
        
        if ( ADC_INT_END_CONVERSION == Sample_Test[i].ulIntFlags )
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CR ) & ADC_CR_ADIE;
        } else if ( ADC_INT_COMP0 == Sample_Test[i].ulIntFlags )
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CMPR0 ) & ADC_CMPRX_CMPIE;
        } else
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CMPR1 ) & ADC_CMPRX_CMPIE;
        }
        
        TestAssert( ultemp == Sample_Test[i].ulResult_En, 
                                         "xadc API \"ADCIntEnable()\" error!" );
    }
    
    for ( i = 0; i < ullength; i++)
    {
        ADCIntDisable( Sample_Test[i].ulBase, Sample_Test[i].ulIntFlags );
        
        if ( ADC_INT_END_CONVERSION == Sample_Test[i].ulIntFlags )
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CR ) & ADC_CR_ADIE;
        } else if ( ADC_INT_COMP0 == Sample_Test[i].ulIntFlags )
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CMPR0 ) & ADC_CMPRX_CMPIE;
        } else
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CMPR1 ) & ADC_CMPRX_CMPIE;
        }
        
        TestAssert( ultemp == Sample_Test[i].ulResult_Dis, 
                                        "xadc API \"ADCIntDisable()\" error!" );
    }
    
}

    
//*****************************************************************************
//
//! \brief  cox adc configure test.
//!
//! \return None.
//
//*****************************************************************************
static void xadc_config( void )
{
    typedef struct
    {
        unsigned long ulBase;
        unsigned long ulMode;
        unsigned long ulTrigger;
        unsigned long ulResult;
    } Test;
    Test Sample_Test[] = { { xADC0_BASE, xADC_MODE_SCAN_SINGLE_CYCLE, 
                  xADC_TRIGGER_PROCESSOR | xADC_TRIGGER_EXT_LOW_LEVEL, 0x08   },
                           { xADC0_BASE, xADC_MODE_SCAN_CONTINUOUS, 
                  xADC_TRIGGER_PROCESSOR | xADC_TRIGGER_EXT_RISING_EDGE, 0xCC },
                           { xADC0_BASE, xADC_MODE_SCAN_SINGLE_CYCLE, 
                  xADC_TRIGGER_EXT_PB8 | xADC_TRIGGER_EXT_HIGH_LEVEL, 0x148   },
                           { xADC0_BASE, xADC_MODE_SCAN_CONTINUOUS, 
                  xADC_TRIGGER_EXT_PB8 | xADC_TRIGGER_EXT_FALLING_EDGE, 0x18C }
                         };
    
    unsigned int ullength = sizeof(Sample_Test) / sizeof(Test); 
    unsigned long ultemp = 0;
    unsigned int i = 0;
    for (; i < ullength; i++)
    {
        xADCConfigure( Sample_Test[i].ulBase, Sample_Test[i].ulMode, 
                                                     Sample_Test[i].ulTrigger );
        ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CR ) & 
                            ( ADC_CR_TRGEN | ADC_CR_TRGCOND_M | ADC_CR_ADMD_M );
        TestAssert( ultemp == Sample_Test[i].ulResult, 
                                        "xadc API \"xADCConfigure()\" error!" );
    }
    
}

//*****************************************************************************
//
//! \brief  cox adc step configure test.
//!
//! \return None.
//
//*****************************************************************************
static void xadc_stepconfig( void )
{
    typedef struct
    {
        unsigned long ulBase;
        unsigned long ulStep;
        unsigned long ulConfig;
        //
        // ulResult[3] represent the value of register ADC_CHER, ADC_CR and ADC_CMPRX.
        //
        unsigned long ulResult[3];
    } Test;
    Test Sample_Test1[] = { { xADC0_BASE, 0, xADC_CTL_CH0 | xADC_CTL_D, 0x01, 0x400, 0 },
                            { xADC0_BASE, 1, xADC_CTL_CH1 | xADC_CTL_D, 0x05, 0x400, 0 },
                            { xADC0_BASE, 2, xADC_CTL_CH2 | xADC_CTL_D, 0x15, 0x400, 0 },
                            { xADC0_BASE, 3, xADC_CTL_CH3 | xADC_CTL_D, 0x55, 0x400, 0 }
                          };
    
    Test Sample_Test2[] = { { xADC0_BASE, 0, xADC_CTL_CH0 | xADC_CTL_CMP0, 0x01, 0, 0x00 },
                            { xADC0_BASE, 1, xADC_CTL_CH1 | xADC_CTL_CMP1, 0x03, 0, 0x08 },
                            { xADC0_BASE, 2, xADC_CTL_CH7 | xADC_CTL_TS, 0x0283, 0, 0x00 }
                          };
    
    unsigned int ullength1 = sizeof(Sample_Test1) / sizeof(Test);
    unsigned int ullength2 = sizeof(Sample_Test2) / sizeof(Test);
    unsigned long ultemp[3] = { 0, 0, 0 };
    unsigned int i = 0;
    for ( ; i < ullength1; i++ )
    {
        xADCStepConfigure( Sample_Test1[i].ulBase, Sample_Test1[i].ulStep, 
                                                     Sample_Test1[i].ulConfig );
        ultemp[0] = xHWREG( Sample_Test1[i].ulBase + ADC_CHER ) & 
                                        ( ADC_CHER_CHEN_M | ADC_CHER_PRESEL_M );
        ultemp[1] = xHWREG( Sample_Test1[i].ulBase + ADC_CR ) & ADC_CR_DIFFEN;
        if ( xADC_CTL_CMP0 & Sample_Test1[i].ulConfig )
        {
            ultemp[2] = xHWREG( Sample_Test1[i].ulBase + ADC_CMPR0 ) & ADC_CMPRX_CMPCH_M;
        } else
        {
            ultemp[2] = xHWREG( Sample_Test1[i].ulBase + ADC_CMPR1 ) & ADC_CMPRX_CMPCH_M;
        }
        
        TestAssert( ( ultemp[0] == Sample_Test1[i].ulResult[0] ) && 
                    ( ultemp[1] == Sample_Test1[i].ulResult[1] ) &&
                    ( ultemp[2] == Sample_Test1[i].ulResult[2] ),
                                    "xadc API \"xADCStepConfigure()\" error!" );
    }
    
    SysCtlPeripheralReset( SYSCTL_PERIPH_ADC );
    
    for ( i = 0; i < ullength2; i++ )
    {
        xADCStepConfigure( Sample_Test2[i].ulBase, Sample_Test2[i].ulStep, 
                                                     Sample_Test2[i].ulConfig );
        ultemp[0] = xHWREG( Sample_Test2[i].ulBase + ADC_CHER ) & 
                                        ( ADC_CHER_CHEN_M | ADC_CHER_PRESEL_M );
        ultemp[1] = xHWREG( Sample_Test2[i].ulBase + ADC_CR ) & ADC_CR_DIFFEN;
        if ( xADC_CTL_CMP0 & Sample_Test2[i].ulConfig )
        {
            ultemp[2] = xHWREG( Sample_Test2[i].ulBase + ADC_CMPR0 ) & ADC_CMPRX_CMPCH_M;
        } else if ( xADC_CTL_CMP1 & Sample_Test2[i].ulConfig )
        {
            ultemp[2] = xHWREG( Sample_Test2[i].ulBase + ADC_CMPR1 ) & ADC_CMPRX_CMPCH_M;
        } else 
        {
            ultemp[2] = Sample_Test2[i].ulResult[2];
        }
        
        TestAssert( ( ultemp[0] == Sample_Test2[i].ulResult[0] ) &&
                    ( ultemp[1] == Sample_Test2[i].ulResult[1] ) &&
                    ( ultemp[2] == Sample_Test2[i].ulResult[2] ),
                                    "xadc API \"xADCStepConfigure()\" error!" );
    }
}

//*****************************************************************************
//
//! \brief  cox adc comparator condition configure test.
//!
//! \return None.
//
//*****************************************************************************
static void xadc_compcondition( void )
{
    typedef struct 
    {
        unsigned long ulBase;
        unsigned long ulCompID;
        unsigned long ulConfig;
        unsigned long ulResult;
    } Test;
    Test Sample_Test[] = { { xADC0_BASE, 0, xADC_COMP_INT_LOW, 0x00  },
                           { xADC0_BASE, 1, xADC_COMP_INT_HIGH, 0x04 }
                         };
    
    unsigned int ullength = sizeof(Sample_Test) / sizeof(Test); 
    unsigned long ultemp = 0;
    unsigned int i = 0;
    for ( ; i < ullength; i++ )
    {
        xADCCompConditionConfig( Sample_Test[i].ulBase, Sample_Test[i].ulCompID, 
                                                      Sample_Test[i].ulConfig );
        ultemp = xHWREG( Sample_Test[i].ulBase +ADC_CMPR0 +  
                          ( 4 * Sample_Test[i].ulCompID ) ) & ADC_CMPRX_CMPCOND;
        TestAssert( ultemp == Sample_Test[i].ulResult, 
                              "xadc API \"xADCCompConditionConfig()\" error!" );
    }
}

//*****************************************************************************
//
//! \brief  cox adc comparator register set test.
//!
//! \return None.
//
//*****************************************************************************
static void xadc_compregset( void )
{
    typedef struct
    {
        unsigned long ulBase;
        unsigned long ulCompID;
        unsigned long ulLowRef;
        unsigned long ulHighRef;
        unsigned long ulResult;
    } Test;
    Test Sample_Test[] = { { xADC0_BASE, 0,  0xFFF, 0xFFF, 0xFFF0100},
                           { xADC0_BASE, 1,  0x000, 0x000, 0x0000100}
                         };
    
    unsigned int ullength = sizeof(Sample_Test) / sizeof(Test);
    unsigned long ultemp = 0;
    unsigned int i = 0;
    for ( ; i < ullength; i++ )
    {
        xADCCompRegionSet( Sample_Test[i].ulBase, Sample_Test[i].ulCompID, 
                            Sample_Test[i].ulLowRef, Sample_Test[i].ulHighRef );
        ultemp = xHWREG( Sample_Test[i].ulBase + ADC_CMPR0 + ( 4 * Sample_Test[i].ulCompID ) )
                                 & ( ADC_CMPRX_CMPD_M | ADC_CMPRX_CMPMATCNT_M );
        TestAssert( ultemp == Sample_Test[i].ulResult,
                                    "xadc API \"xADCCompRegionSet()\" error!" );
    }
}

//*****************************************************************************
//
//! \brief  cox adc interrupt user callback.
//!
//! \return None.
//
//*****************************************************************************

unsigned long user_Callback( void *pvCBData, unsigned long ulEvent,
                                     unsigned long ulMsgParam, void *pvMsgData )
{
    if ( xADCOverflow( xADC0_BASE ) )
    {
        xADCOverflowClear( xADC0_BASE );
        TestAssert( 0 == ( xHWREG( xADC0_BASE + ADC_SR ) & ADC_SR_OVERRUN_M ),
                                    "xadc API \"xADCOverflowClear()\" error!" );
    }
    
    TestEmitToken( 'T' );
    
    return 0;
}

//*****************************************************************************
//
//! \brief  cox adc call back init test.
//!
//! \return None.
//
//*****************************************************************************
static void xadc_callback( void )
{
    //
    // enable ADC
    //
    xADCEnable( xADC0_BASE );
    //
    // config ADC
    //
    xADCConfigure( xADC0_BASE, xADC_MODE_SCAN_SINGLE_CYCLE, ADC_TRIGGER_PROCESSOR );
    
    xADCStepConfigure( xADC0_BASE, 0, xADC_CTL_CH0 );
    xADCStepConfigure( xADC0_BASE, 1, xADC_CTL_CH1 );
    xADCStepConfigure( xADC0_BASE, 2, xADC_CTL_CH2 | xADC_CTL_END );
    //
    // enable ADC interrupt and init call back
    //
    xADCIntCallbackInit( xADC0_BASE, user_Callback );
    xADCIntEnable( xADC0_BASE, xADC_INT_END_CONVERSION );
    xIntEnable( INT_ADC );
    //
    // start ADC convert
    //
    xADCProcessorTrigger( xADC0_BASE );
    
    TestAssertQBreak( "T", "xadc api xADCIntCallbackInit() error!", 0xFFFFFFFF );
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
    adcapi_config();
    adcapi_channel();
    adcapi_ch7config();
    adcapi_adcint();
    adcapi_calibrate();
    adcapi_pdma();
    adcapi_cmpconfig();
    adcapi_cmpdata();
    adcapi_comparator();
    adcapi_convert();  
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

//*****************************************************************************
//
//! \brief Get the Test description of xadc002 register test.
//!
//! \return the desccription of the xadc002 test.
//
//*****************************************************************************
static char* xadc002GetTest( void )
{
    return "xadc, 002, xadc register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xadc002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xadc002Setup( void )
{
    //
    // Reset ADC 
    //
    SysCtlPeripheralReset( SYSCTL_PERIPH_ADC );
    //
    // Configure ADC
    //
    ADCConfigure( ADC_BASE, ADC_INPUT_SINGLE, ADC_OP_CONTINUOUS, ADC_TRIGGER_PROCESSOR );
    //
    // Enable ADC channel 0
    //
    ADCChannelEnable(ADC_BASE, ADC_CHANNEL_0);
}

//*****************************************************************************
//
//! \brief xadc002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xadc002Execute( void )
{
    adcapi_adc( );
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xadc002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xadc002TearDown( void )
{
    
}

//
// xadc002 register test case struct.
//
const tTestCase sTestXAdc002Register = {
    xadc002GetTest,
    xadc002Setup,
    xadc002Execute,
    xadc002TearDown
};

//*****************************************************************************
//
//! \brief Get the Test description of xadc003 register test.
//!
//! \return the desccription of the xadc003 test.
//
//*****************************************************************************
static char* xadc003GetTest( void )
{
    return "xadc, 003, xadc register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xadc003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xadc003Setup( void )
{
    //
    // Reset ADC 
    //
    SysCtlPeripheralReset( SYSCTL_PERIPH_ADC );
}

//*****************************************************************************
//
//! \brief xadc003 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xadc003Execute( void )
{
    xadc_config( );
    xadc_stepconfig( );
    xadc_compcondition( );
    xadc_compregset( );
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xadc003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xadc003TearDown( void )
{
    
}

//
// xadc003 register test case struct.
//
const tTestCase sTestXAdc003Register = {
    xadc003GetTest,
    xadc003Setup,
    xadc003Execute,
    xadc003TearDown
};

//*****************************************************************************
//
//! \brief Get the Test description of xadc004 register test.
//!
//! \return the desccription of the xadc004 test.
//
//*****************************************************************************
static char* xadc004GetTest( void )
{
    return "xadc, 004, xadc register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xadc004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xadc004Setup( void )
{
    //
    // Reset ADC 
    //
    SysCtlPeripheralReset( SYSCTL_PERIPH_ADC );
}

//*****************************************************************************
//
//! \brief xadc004 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xadc004Execute( void )
{
    xadc_callback( );
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xadc004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xadc004TearDown( void )
{
    
}

//
// xadc004 register test case struct.
//
const tTestCase sTestXAdc004Register = {
    xadc004GetTest,
    xadc004Setup,
    xadc004Execute,
    xadc004TearDown
};

//
// Xgpio test suits.
//
const tTestCase * const psPatternXadc[] =
{
    &sTestXAdc001Register,
    &sTestXAdc002Register,
    &sTestXAdc003Register,
    &sTestXAdc004Register,
    0
};


