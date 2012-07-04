//*****************************************************************************
//
//! @page xtimer_testcase xtimer register test
//!
//! File: @ref xtimertest1.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xtimer sub component.<br><br>
//! - \p Board: HT32F125x Development board <br><br>
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
//! - \subpage test_xtimer_register
//! .
//! \file xtimertest1.c
//! \brief xtimer test source file
//! \brief xtimer test header file <br>
//
//*****************************************************************************

#include "test.h"


//*****************************************************************************
//
//!\page test_xtimer_register test_xtimer_register
//!
//!<h2>Description</h2>
//!Test xtimer register. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
// Define The 4 timer base address array, and Peripheral ID array.
//
//*****************************************************************************

//
// Timer base array
//
static unsigned long ulTimerBase[2] = {TIMER0_BASE, TIMER1_BASE};

//
// Timer ID array
//
static unsigned long ulTimerID[2] = {xSYSCTL_PERIPH_TIMER0,
                                     xSYSCTL_PERIPH_TIMER1};

//
// Timer mode
//
static unsigned long ulTimerMode[5] = {TIMER_CNT_MODE_UP,
                                       TIMER_CNT_MODE_CA1,
                                       TIMER_CNT_MODE_CA2,
                                       TIMER_CNT_MODE_CA3,
                                       TIMER_CNT_MODE_DOWN};

//
// Timer counter reload data
//
static unsigned long ulTimerCRRData[3] = {1, 100, 65535};

//
// Timer prescale data
//
static unsigned long ulTimerPrescaleData[3] = {1, 100, 65535};

//
// Timer reload mode
//
static unsigned long ulTimerReloadMode[2] = {TIMER_PSC_RLD_UPDATE, 
                                             TIMER_PSC_RLD_IMMEDIATE};

//
// Timer channel
//
static unsigned long ulTimerChannel[4] = {TIMER_CH_0, TIMER_CH_1, 
                                          TIMER_CH_2, TIMER_CH_3};

//
// Timer output enable
//
static unsigned long ulTimerOutputEnable[2] = {TIMER_CHCTL_DISABLE, 
                                               TIMER_CHCTL_ENABLE};

//
// Timer channel polarity
//
static unsigned long ulTimeCHPolarity[2] = {TIMER_CHP_NONINVERTED, 
                                            TIMER_CHP_INVERTED};

//
// Timer channel Output mode
//
static unsigned long ulTimerOutputMode[6] = {TIMER_OM_MATCH_NOCHANGE, 
                                            TIMER_OM_MATCH_INACTIVE, 
                                            TIMER_OM_MATCH_ACTIVE, 
                                            TIMER_OM_MATCH_TOGGLE, 
                                            TIMER_OM_FORCED_INACTIVE,
                                            TIMER_OM_FORCED_ACTIVE};

//
// Timer compare value
//
static unsigned long ulTimerCmpValue[3] = {1, 100, 65535};

//
// Timer capture source select
//
static unsigned long ulSelect[3] = {TIMER_CHCCS_DIRECT, TIMER_CHCCS_INDIRECT, 
                                    TIMER_CHCCS_TRCED};

//
// Timer prescaler select
//
static unsigned long ulPrescaler[4] = {TIMER_CHPSC_OFF, TIMER_CHPSC_2,
                                       TIMER_CHPSC_4, TIMER_CHPSC_8};

//
// Filter set 
//
static unsigned char ucFilter[3] = {0, 1, 15};

//
// EXT prascaler
//
static unsigned long ulEXIPrescaleValue[4] = {TIMER_ETIPSC_OFF, TIMER_ETIPSC_2, 
                                         TIMER_ETIPSC_4, TIMER_ETIPSC_8};

//
// EXT Polarity inverted
//
static unsigned long ulEXIPolarity[2] = {TIMER_ETIPOL_NONINVERTED,
                                         TIMER_ETIPOL_INVERTED};

//
// Prescaler reload time
//
static unsigned long ulPSCReloadTime[2] = {TIMER_PSC_RLD_UPDATE, 
                                           TIMER_PSC_RLD_IMMEDIATE};

//
// Decode mode set test
//
static unsigned long ulDecodeMode[3] = {TIMER_SMSEL_DECODER1, TIMER_SMSEL_DECODER2,
                                     TIMER_SMSEL_DECODER3};

//
// CHxOREF waveform to active or inactive
//
static unsigned long ulForcedAction[2] = {TIMER_OM_FORCED_INACTIVE, 
                                          TIMER_OM_FORCED_ACTIVE};

//
// CRR reload time configure
//
static unsigned long ulProload[2] = {TIMER_CRR_PROLOAD_IMM, 
                                     TIMER_CRR_PROLOAD_UD};

//
// Timer one pulse active configure
//
static unsigned long ulActive[2] = {TIMER_ONE_PULSE_ACTIVE_DIS,
                                    TIMER_ONE_PULSE_ACTIVE_EN};

//
// Timer channel enable
//
static unsigned long ulControl[2] = {TIMER_CHCTL_DISABLE, 
                                     TIMER_CHCTL_ENABLE};

//
// Timer one pulse mode 
//
static unsigned long ulOnepulseMode[2] = {TIMER_ONE_PULSE_MODE_EN, 
                                          TIMER_ONE_PULSE_MODE_DIS};

//
// Timer output source 
//
static unsigned long ulMasterOutputSrc[8] = {TIMER_MMSEL_RESET,
                                            TIMER_MMSEL_ENABLE,
                                            TIMER_MMSEL_UPDATE,
                                            TIMER_MMSEL_CH0CC,
                                            TIMER_MMSEL_CH0OREF,
                                            TIMER_MMSEL_CH1OREF,
                                            TIMER_MMSEL_CH2OREF,
                                            TIMER_MMSEL_CH3OREF};

//
// Timer slave mode select
//
static unsigned long ulSlaveMode[4] = {TIMER_SMSEL_RESTART, TIEMR_SMSEL_PAUSE,
                                       TIMER_SMSEL_TRIGGER, TIMER_SMSEL_STIED};

//
// Timer counter set value
//
static unsigned long ulTimerCounter[3] = {1, 1000, 65535};

//
// Event generate
//
static unsigned long ulEvent[6] = {TIMER_EVENT_CHOCC, TIMER_EVENT_CH1CC, 
                                   TIMER_EVENT_CH2CC, TIMER_EVENT_CH3CC,
                                   TIMER_EVENT_UEV1, TIMER_EVENT_TEV};

//
// Int Status
//
static unsigned long ulInt[6] = {TIMER_INT_CH0CC, TIMER_INT_CH1CC, 
                                 TIMER_INT_CH2CC, TIMER_INT_CH3CC,
                                 TIMER_INT_UEV1, TIMER_INT_TEV};

//*****************************************************************************
//
//! \brief Get the Test description of xtimer001 register test.
//!
//! \return the desccription of the xtimer001 test.
//
//*****************************************************************************
static char* xTimer001GetTest(void)
{
    return "xTimer [001]: xtimer register read and write test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xtimer001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer001Setup(void)
{
    int i;
    
    //
    //Set the external 8MHZ clock as system clock 
    //
    xSysCtlClockSet(8000000, xSYSCTL_XTAL_8MHZ | xSYSCTL_OSC_MAIN);
    
    //
    // Enable the tiemr0-3 peripheral
    //
    for(i = 0; i < 2; i++)
    {   
        
        xSysCtlPeripheralEnable(ulTimerID[i]);  
       
    }
    
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xtimer001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer001TearDown(void)
{
    int i;
    //
    // Enable the tiemr0-3 peripheral
    //
    for(i = 0; i < 2; i++)
    {
        xSysCtlPeripheralDisable(ulTimerID[i]);  
    }
}

//*****************************************************************************
//
//! \brief xtimer 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer001Execute(void)
{
    unsigned long ulTemp;
    unsigned long ulBase;
    int i, j, k;

   
    //
    // Test the register write and read.
    //
    for(i = 0; i < 2; i++)
    {
        ulBase = ulTimerBase[i];

        for(j = 0; j < 4; j++)
        {
            xTimerInitConfig(ulBase, ulTimerChannel[j], xTIMER_MODE_PERIODIC |
                             xTIMER_COUNT_UP, 100);
            ulTemp = xHWREG(ulBase + TIMER_PSCR);
            TestAssert(ulTemp == 2, 
                       "xtimer API \"xTimerInitConfig- prescale \" error");            
            ulTemp = xHWREG(ulBase + TIMER_CRR);
            TestAssert(ulTemp == 40000, 
                       "xtimer API \"xTimerInitConfig- CRR \" error");
            ulTemp = xHWREG(ulBase + TIMER_CNTCFR) & TIMER_CNTCFR_DIR;
            TestAssert(ulTemp == xTIMER_COUNT_UP, 
                       "xtimer API \"xTimerInitConfig- DIR \" error");
            
            xTimerInitConfig(ulBase, ulTimerChannel[j], xTIMER_MODE_TOGGLE |
                             xTIMER_COUNT_UP, 100);
            ulTemp = xHWREG(ulBase + TIMER_CH0OCFR + ulTimerChannel[j] * 4) & 
              TIMER_CH0OCFR_CH0OM_M;
            TestAssert(ulTemp == TIMER_CH0OCFR_CH0OM_TOGGLE, 
                       "xtimer API \"xTimerInitConfig- DIR \" error");
            ulTemp = xHWREG(ulBase + TIMER_CH0CCR + ulTimerChannel[j] * 4);
            TestAssert(ulTemp == 20000, 
                       "xtimer API \"xTimerInitConfig- DIR \" error");   
            
            //
            // Prescale set and get test
            //
            xTimerPrescaleSet(ulBase, ulTimerChannel[j], 1000);
            ulTemp = xTimerPrescaleGet(ulBase, ulTimerChannel[j]);
            TestAssert(ulTemp == 1000, 
                       "xtimer API \"Prescale set and get test \" error"); 
            
            //
            // Match set and get test
            //
            xTimerMatchSet(ulBase, ulTimerChannel[j], 1000);
            ulTemp = xTimerMatchGet(ulBase, ulTimerChannel[j]);
            TestAssert(ulTemp == 1000, 
                       "xtimer API \"Match set and get test \" error"); 
            
            //
            // xINT enable test
            //
            xTimerIntEnable(ulBase, ulTimerChannel[j], xTIMER_INT_CAP_EVENT);
            ulTemp = xHWREG(ulBase + TIMER_ICTR) & (TIMER_CHCTR_CH0CCIE << ulTimerChannel[j]);
            TestAssert(ulTemp == TIMER_CHCTR_CH0CCIE << ulTimerChannel[j], 
                       "xtimer API \"xINT enable test \" error"); 
            
            //
            // xINT disable test
            //
            xTimerIntDisable(ulBase, ulTimerChannel[j], xTIMER_INT_CAP_EVENT);
            ulTemp = xHWREG(ulBase + TIMER_ICTR) & (TIMER_CHCTR_CH0CCIE << ulTimerChannel[j]);
            TestAssert(ulTemp == 0, 
                       "xtimer API \"xINT disable test \" error"); 
        }
        
        //
        // xTimer start test
        //
        xTimerStart(ulBase, ulTimerChannel[0]);
        ulTemp = xHWREG(ulBase + TIMER_CTR) & TIMER_CTR_TME;
        TestAssert(ulTemp == TIMER_CTR_TME, 
                   "xtimer API \"xTimer start test \" error");
        
        //
        // xTimer stop test
        //
        xTimerStop(ulBase, ulTimerChannel[0]);
        ulTemp = xHWREG(ulBase + TIMER_CTR) & TIMER_CTR_TME;
        TestAssert(ulTemp == 0, 
                   "xtimer API \"xTimer stop test \" error");    
        
    
        //*********************************************************************
        // Timer base configure test
        //*********************************************************************
        
        //
        // Counter mode test
        //
        for(j = 0; j < 5; j++)
        {
            TimeBaseConfigure(ulBase, ulTimerMode[j], 100, 100, ulTimerReloadMode[0]);
            ulTemp = xHWREG(ulBase + TIMER_CNTCFR) & 0xFFFF0000;
            TestAssert(ulTemp == ulTimerMode[j], 
                       "xtimer API \"Timer base configure -counter mode \" error");
        }
        
        //
        // Counter reload set test
        //
        for(j = 0; j < 3; j++)
        {
            TimeBaseConfigure(ulBase, ulTimerMode[0], ulTimerCRRData[j], 
                              100, ulTimerReloadMode[0]);
            ulTemp = TimerCRRGet(ulBase);
            TestAssert(ulTemp == ulTimerCRRData[j], 
                       "xtimer API \"Timer base configure -CRR set \" error");
        } 
        
        //
        // Counter prescale set test
        //
        for(j = 0; j < 3; j++)
        {
            TimeBaseConfigure(ulBase, ulTimerMode[0], ulTimerCRRData[0], 
                              ulTimerPrescaleData[j], ulTimerReloadMode[0]);
            ulTemp = TimerPerscalerGet(ulBase);
            TestAssert(ulTemp == ulTimerPrescaleData[j], 
                       "xtimer API \"Timer base configure -PSC set \" error");
        }
        
        //
        // Counter reload mode test
        //
		/*
        for(j = 0; j < 2; j++)        
        {
            TimeBaseConfigure(ulBase, ulTimerMode[0], ulTimerCRRData[0], 
                              ulTimerPrescaleData[j], ulTimerReloadMode[j]);
            ulTemp = xHWREG(ulBase + TIMER_EVGR) & TIMER_EVGR_UEVG;
            TestAssert(ulTemp == ulTimerReloadMode[j], 
                       "xtimer API \"Timer base configure -RM set \" error");
        }
		*/
        
        for(j = 0; j < 4; j++)
        {
            //
            // Output enable test
            //
            for(k = 0; k < 2; k++)
            {
                TimerOutputConfigure(ulBase, ulTimerChannel[j], ulTimerOutputEnable[k],
                                     ulTimeCHPolarity[0], ulTimerOutputMode[0], 
                                     ulTimerCmpValue[0]);
                ulTemp = xHWREG(ulBase + TIMER_CHCTR) & (1 << (ulTimerChannel[j] * 2));
                TestAssert(ulTemp == (ulTimerOutputEnable[k] << (ulTimerChannel[j] * 2)), 
                           "xtimer API \"Output enable set test\" error");        
            }
            
            //
            // Channel polarity
            //
            for(k = 0; k < 2; k++)
            {
                TimerOutputConfigure(ulBase, ulTimerChannel[j], ulTimerOutputEnable[0],
                                     ulTimeCHPolarity[k], ulTimerOutputMode[0], 
                                     ulTimerCmpValue[0]);
                ulTemp = xHWREG(ulBase + TIMER_CHPOLR) & (1 << (ulTimerChannel[j] * 2));
                TestAssert(ulTemp == ulTimeCHPolarity[k] << (ulTimerChannel[j] * 2), 
                           "xtimer API \"Channel polarity set test\" error"); 
            }
            
            //
            // Output Mode test
            //
            for(k = 0; k < 6; k++)
            {
                TimerOutputConfigure(ulBase, ulTimerChannel[j], ulTimerOutputEnable[0],
                                     ulTimeCHPolarity[0], ulTimerOutputMode[k], 
                                     ulTimerCmpValue[0]);
                ulTemp = xHWREG(ulBase + TIMER_CH0OCFR + ulTimerChannel[j] * 4) & 
                  TIMER_CH0OCFR_CH0OM_M;
                TestAssert(ulTemp == ulTimerOutputMode[k], 
                           "xtimer API \"Output Mode set test\" error"); 
            }
            
            //
            // Compare value set test
            //
            for(k = 0; k < 3; k++)
            {
                TimerOutputConfigure(ulBase, ulTimerChannel[j], ulTimerOutputEnable[0],
                                     ulTimeCHPolarity[0], ulTimerOutputMode[0], 
                                     ulTimerCmpValue[k]);
                ulTemp =  TimerCaptureCompareGet(ulBase, ulTimerChannel[j]);
                TestAssert(ulTemp == ulTimerCmpValue[k], 
                           "xtimer API \"Compare value set test\" error");
            }
            
            //
            // Capture source select test
            //
            for(k = 0; k < 3; k++)
            {
                TimerCaptureConfigure(ulBase, ulTimerChannel[j], ulTimeCHPolarity[0],
                                      ulSelect[k], ulPrescaler[0], ucFilter[0]);
                ulTemp =  xHWREG(ulBase + TIMER_CH0ICFR + ulTimerChannel[j] * 4) & 
                  TIMER_CH0ICFR_CH0CCS_M;
                TestAssert(ulTemp == ulSelect[k], 
                           "xtimer API \"Capture source select test\" error");
            }
            
            //
            // Capture prescale select test
            //
            for(k = 0; k < 4; k++)
            {
                TimerCaptureConfigure(ulBase, ulTimerChannel[j], ulTimeCHPolarity[0],
                                      ulSelect[0], ulPrescaler[k], ucFilter[0]);
                ulTemp =  xHWREG(ulBase + TIMER_CH0ICFR +  ulTimerChannel[j] * 4) & 
                  TIMER_CH0ICFR_CH0PSC_M;
                TestAssert(ulTemp == ulPrescaler[k], 
                           "xtimer API \"Capture prescale select test\" error");
            }     
            
            //
            // Capture filter select test
            //
            for(k = 0; k < 3; k++)
            {
                TimerCaptureConfigure(ulBase, ulTimerChannel[j], ulTimeCHPolarity[0],
                                      ulSelect[0], ulPrescaler[0], ucFilter[k]);
                ulTemp =  xHWREG(ulBase + TIMER_CH0ICFR +  ulTimerChannel[j] * 4) & 
                  TIMER_CH0ICFR_TI0F_M;
                TestAssert(ulTemp == ucFilter[k], 
                           "xtimer API \"Capture filter select test\" error");
            }
            
            //
            // Forces CHxOREF waveform to active or inactive
            //
            for(k = 0; k < 2; k++)
            {
                TimerForcedOREF(ulBase, ulTimerChannel[j], ulForcedAction[k]);
                ulTemp = xHWREG(ulBase + TIMER_CH0OCFR  + ulTimerChannel[j] * 4)
                  & TIMER_CH0OCFR_CH0OM_M;
                TestAssert(ulTemp == ulForcedAction[k], 
                           "xtimer API \"Forces CHxOREF waveform set test\" error");
            }
            
            //
            // Timer one pulse active configure
            //
			/*
            for(k = 0; k < 2; k++)
            {
                Timer1PulseActiveConfigure(ulBase, ulTimerChannel[j], ulActive[k]);
                ulTemp = xHWREG(ulBase + TIMER_CH0OCFR + ulTimerChannel[j] * 4) & 
                  TIMER_CH0OCFR_CH0IMAE;
                TestAssert(ulTemp == ulActive[k], 
                           "xtimer API \" Timer one pulse active configure\" error");
            }
			*/
            
            //
            // Channel enable test
            //
            for(k = 0; k < 2; k++)
            {
                 TimerCHConfigure(ulBase, ulTimerChannel[j], ulControl[k]);
                 ulTemp = xHWREG(ulBase + TIMER_CHCTR) & (1 << (ulTimerChannel[j] * 2));
                 TestAssert(ulTemp == (ulControl[k] << (ulTimerChannel[j] * 2)), 
                           "xtimer API \" Channel enable test\" error");
            }
        }
        
        //
        // Timer start test
        //
        TimerStart(ulBase);
        ulTemp =  xHWREG(ulBase + TIMER_CTR) & TIMER_CTR_TME;
        TestAssert(ulTemp == TIMER_CTR_TME, 
                   "xtimer API \"Timer start test \" error");     
        
        //
        // Timer stop test
        //
        TimerStop(ulBase);
        ulTemp =  xHWREG(ulBase + TIMER_CTR) & TIMER_CTR_TME;
        TestAssert(ulTemp == 0, 
                   "xtimer API \"Timer stop test \" error"); 
        
        //
        // ITI0 as the clock source test
        //
        TimerITIExtClkConfigure(ulBase, TIMER_TRSEL_ITI0);
        ulTemp = xHWREG(ulBase + TIMER_TRCFR) & TIMER_TRCFR_TRSEL_M;
        TestAssert(ulTemp == TIMER_TRSEL_ITI0, 
                   "xtimer API \"Timer stop test \" error"); 
        ulTemp = xHWREG(ulBase + TIMER_MDCFR) & TIMER_MDCFR_SMSEL_STIED;
        TestAssert(ulTemp == TIMER_MDCFR_SMSEL_STIED, 
                   "xtimer API \"Timer stop test \" error"); 
        
        //
        // ETI prescaler set test
        //
        for(k = 0; k < 4; k++)
        {
            TimerETIExtClkConfigure(ulBase, ulEXIPrescaleValue[k],
                                    ulEXIPolarity[0], ucFilter[0]);
            ulTemp = xHWREG(ulBase + TIMER_TRCFR) & TIMER_TRCFR_ETIPSC_M;
            TestAssert(ulTemp == ulEXIPrescaleValue[k], 
                       "xtimer API \"ETI prescaler set test \" error"); 
        }
        
        //
        // ETI polarity set test
        //
        for(k = 0; k < 2; k++)
        {
            TimerETIExtClkConfigure(ulBase, ulEXIPrescaleValue[0],
                                    ulEXIPolarity[k], ucFilter[0]);
            ulTemp = xHWREG(ulBase + TIMER_TRCFR) & TIMER_TRCFR_ETIPOL;
            TestAssert(ulTemp == ulEXIPolarity[k], 
                       "xtimer API \"ETI polarity set test \" error"); 
        }
        
        //
        // ETI filter set test
        //
        for(k = 0; k < 3; k++)
        {
            TimerETIExtClkConfigure(ulBase, ulEXIPrescaleValue[0],
                                    ulEXIPolarity[0], ucFilter[k]);
            ulTemp = xHWREG(ulBase + TIMER_TRCFR) & TIMER_TRCFR_ETF_M;
            TestAssert(ulTemp == (ucFilter[k] << 8), 
                       "xtimer API \"ETI filter set test \" error"); 
        }  
        
        //
        // ETI enable set test
        //
        ulTemp = xHWREG(ulBase + TIMER_TRCFR) & TIMER_TRCFR_ECME ;
        TestAssert(ulTemp == TIMER_TRCFR_ECME, 
                   "xtimer API \" ETI enable set test \" error");
        
        //
        // Prescaler update configure
        //
		/*
        for(k = 0; k < 2; k++)
        {
            TimerPrescalerConfigure(ulBase, ulTimerPrescaleData[0], ulPSCReloadTime[k]);
            ulTemp = xHWREG(ulBase + TIMER_EVGR) & TIMER_EVGR_UEVG;
            TestAssert(ulTemp == ulPSCReloadTime[k], 
                       "xtimer API \" Prescaler update configure \" error");
        }
		*/
        
        //
        // Decode mode set test
        //
        for(k = 0; k < 3; k++)
        {
            TimerDecoderConfigure(ulBase, ulDecodeMode[k], TIMER_CHP_NONINVERTED, 
                                  TIMER_CHP_NONINVERTED);
            ulTemp = xHWREG(ulBase + TIMER_MDCFR) & TIMER_MDCFR_SMSEL_M;
            TestAssert(ulTemp == ulDecodeMode[k], 
                       "xtimer API \" Decode mode set test \" error"); 
        }
        
        //
        // CRR preload configure
        //
		/*
        for(k = 0; k < 2; k++)
        {
            TimerCRRPreloadConfigure(ulBase, ulProload[k]);
            ulTemp = xHWREG(ulBase + TIMER_CTR) & TIMER_CTR_CRBE;
            TestAssert(ulTemp == ulProload[k], 
                       "xtimer API \" CRR preload configure \" error");             
        }
		*/
        
        //
        // One pulse mode test
        //
        for(k = 0; k < 2; k++)
        {
            TimerOnePulseModeConfigure(ulBase, ulOnepulseMode[k]);
            ulTemp = xHWREG(ulBase + TIMER_MDCFR) & TIMER_MDCFR_SPMSET;
            TestAssert(ulTemp == ulOnepulseMode[k], 
                       "xtimer API \" One pulse mode test \" error");
        }
        
        //
        //  Timer master output source select
        //
        for(k = 0; k < 8; k++)
        {
            TimerMasterOutputSrcSelect(ulBase, ulMasterOutputSrc[k]);
            ulTemp = xHWREG(ulBase + TIMER_MDCFR) & TIMER_MDCFR_MMSEL_M;
            TestAssert(ulTemp == ulMasterOutputSrc[k], 
                       "xtimer API \" Timer master output source select \" error");
        }
        
        //
        // Slave mode set configure
        //
        for(k = 0; k < 4; k++)
        {
            TimerSlaveModeConfigure(ulBase, ulSlaveMode[k]);
            ulTemp = xHWREG(ulBase + TIMER_MDCFR) & TIMER_MDCFR_SMSEL_M;
            TestAssert(ulTemp == ulSlaveMode[k], 
                       "xtimer API \" Slave mode set configure \" error");
        }
        
        //
        // Counter set and get test
        //
        for(k = 0; k < 3; k++)
        {
            TimerCounterSet(ulBase, ulTimerCounter[k]);
            ulTemp = TimerCounterGet(ulBase);
            TestAssert(ulTemp == ulTimerCounter[k], 
                       "xtimer API \" Counter set and get test \" error");
        }
        
        //
        // Event generate test
        //
        for(k = 0; k < 6; k++)
        {
            TimerEventGenerate(ulBase, ulEvent[k]);
            ulTemp = TimerFlagStatusGet(ulBase, ulEvent[k]);
            TestAssert(ulTemp == xtrue, 
                       "xtimer API \" Event generate test \" error");
        }
        
        //
        // Int enable test
        //
        for(k = 0; k < 6; k++)
        {
            TimerIntEnable(ulBase, ulInt[k]);
            ulTemp = xHWREG(ulBase + TIMER_ICTR) & ulInt[k];
            TestAssert(ulTemp == ulInt[k], 
                       "xtimer API \" Int enable test \" error");
        }
        
        //
        // Int disable test
        //
        for(k = 0; k < 6; k++)
        {
            TimerIntDisable(ulBase, ulInt[k]);
            ulTemp = xHWREG(ulBase + TIMER_ICTR) & ulInt[k];
            TestAssert(ulTemp == 0, 
                       "xtimer API \" Int disable test \" error");
        }
    }       
  
}

//
// xtimer register test case struct.
//
const tTestCase sTestxTimer001Register = {
		xTimer001GetTest,
		xTimer001Setup,
		xTimer001TearDown,
		xTimer001Execute
};

//
// xtimer test suits.
//
const tTestCase * const psPatternXtimer001[] =
{
    &sTestxTimer001Register,
    0
};

