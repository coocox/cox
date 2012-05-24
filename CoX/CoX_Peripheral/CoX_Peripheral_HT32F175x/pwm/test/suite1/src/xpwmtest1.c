//*****************************************************************************
//
//! @page xpwm_testcase xpwm register test
//!
//! File: @ref xpwmtest1.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xpwm sub component.<br><br>
//! - \p Board: HT32F125x Development Board <br><br>
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
//! - \subpage test_xpwm_register
//! .
//! \file xpwmtest1.c
//! \brief xpwm test source file
//! \brief xpwm test header file <br>
//
//*****************************************************************************

#include "test.h"

//*****************************************************************************
//
//!\page test_xpwm_register test_xpwm_register
//!
//!<h2>Description</h2>
//!Test xpwm register. <br>
//!
//
//*****************************************************************************

//
// pwm base value
//
static unsigned long PWNBase[2] = {PWMA_BASE, PWMB_BASE};

//
// pwm channel value
//
static unsigned long PWMChannel[2][4] = {{0,1,2,3}, {4,5,6,7}};

//
// PWM oneshot configure
//
static unsigned long ulPWMOneShot[2] = {PWM_ONE_SHOT_MODE, PWM_TOGGLE_MODE};

//
// PWM output mode
//
static unsigned long ulPWMOutMode[2] = {PWM_OM_1, PWM_OM_2};

//
// PWM count dir
//
static unsigned long ulPWMCountDir[2] = {PWM_CNT_MODE_UP, PWM_CNT_MODE_DOWN};

//
// PWM Frequency set value
//
static unsigned long PWMFrequency[3] = {200, 1000, 3000};

//
// PWM prescale set value
//
static unsigned long PWMPrescale[3] = {1, 50, 255};

//
// PWM Int enable
//
static unsigned long PWMIntType[2] = {PWM_INT_CHXCC, PWM_INT_UEV1};



//*****************************************************************************
//
//! \brief xpwm001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xpwm001Execute(void)
{          
  
    unsigned long ulBase;
    unsigned long ulTemp;
    
    unsigned long ulFrequency;
    
    int i, j, k;
    for(i = 0; i < 2; i++)
    {   
        ulBase = PWNBase[i];
       
        for(j = 0; j < 4; j++)
        { 
            xPWMInitConfigure(ulBase, PWMChannel[i][j], xPWM_ONE_SHOT_MODE);
            ulTemp = xHWREG(ulBase + TIMER_MDCFR) & TIMER_MDCFR_SPMSET;
            TestAssert(ulTemp == TIMER_MDCFR_SPMSET,
                       "xpwm, \" One shot mode\" error!"); 
            ulTemp = xHWREG(ulBase + TIMER_CNTCFR) & PWM_CNT_MODE_DOWN;
            TestAssert(ulTemp == PWM_CNT_MODE_DOWN,
                       "xpwm, \" PWM dir configure\" error!"); 
            ulTemp = xHWREG(ulBase + TIMER_CH0OCFR + j * 4) & 
              TIMER_CH0OCFR_CH0OM_M;
            TestAssert(ulTemp == PWM_OM_1,
                       "xpwm, \" PWM channel output mode\" error!");

            //
            // PWM output mode
            //
            for(k = 0; k < 2; k++)
            {
                PWMInitConfigure(ulBase, PWMChannel[i][j], ulPWMOneShot[0], 
                                 ulPWMOutMode[k], ulPWMCountDir[0]);
                ulTemp = xHWREG(ulBase + TIMER_CH0OCFR + j * 4) & 
                  TIMER_CH0OCFR_CH0OM_M;
                TestAssert(ulTemp == ulPWMOutMode[k],
                           "xpwm, \" PWM output mode...\" error!");
            }
            
            //
            // PWM dir configure
            //
            for(k = 0; k < 2; k++)
            {
                PWMInitConfigure(ulBase, PWMChannel[i][j], ulPWMOneShot[0], 
                                 ulPWMOutMode[0], ulPWMCountDir[k]);
                ulTemp = xHWREG(ulBase + TIMER_CNTCFR) & TIMER_CNTCFR_DIR;
                TestAssert(ulTemp == ulPWMCountDir[k],
                           "xpwm, \" PWM dir configure\" error!");
            }
            
            //
            // Channel has been configured as output
            // 
            ulTemp = xHWREG(ulBase + TIMER_CH0ICFR + PWMChannel[i][j] * 4) & TIMER_CH0ICFR_CH0CCS_M;
            TestAssert(ulTemp == TIMER_CH0ICFR_CH0CCS_O,
                       "xpwm, \" PWM dir configure\" error!");            
        }
        
        //
        // PWM frequency set test
        //        
        ulFrequency = PWMFrequencySet(ulBase, PWMFrequency[1]);
        ulTemp = PWMFrequencyGet(ulBase);
        TestAssert(ulTemp == PWMFrequency[1],
                   "xpwm, \" Frequency set/get test\" error!");             
        
        //
        // PWM frequency configure test
        //
        for(j = 0; j < 4; j++)
        {
           PWMFrequencyConfig(ulBase, 0x12341234);
           ulTemp = xHWREG(ulBase + TIMER_CRR);
           TestAssert(ulTemp == 0x1234,
                      "xpwm, \" PWM frequency configure test\" error!");
           ulTemp = xHWREG(ulBase + TIMER_PSCR);
           TestAssert(ulTemp == 0x1233,
                      "xpwm, \" PWM frequency configure test\" error!");
        }
        
        //
        // Output enable test
        //
        for(j = 0; j < 4; j++)
        {
            PWMOutputEnable(ulBase, PWMChannel[i][j]);
            ulTemp = xHWREG(ulBase + TIMER_CHCTR) & (1 << j * 2);
            TestAssert(ulTemp == (1 << j * 2),
                       "xpwm, \" Output enable test\" error!");
        }
        
        //
        // Output disable test
        //
        for(j = 0; j < 4; j++)
        {
            PWMOutputDisable(ulBase, PWMChannel[i][j]); 
            ulTemp = xHWREG(ulBase + TIMER_CHCTR) & (1 << j * 2);
            TestAssert(ulTemp == 0,
                       "xpwm, \" Output disable test\" error!");
        }
        
        //
        // PWM start test
        //
        PWMStart(ulBase);
        ulTemp = xHWREG(ulBase + TIMER_CTR) & TIMER_CTR_TME;
        TestAssert(ulTemp == TIMER_CTR_TME,
                   "xpwm, \" Output disable test\" error!");            
        
        //
        // PWM stop test
        //
        PWMStop(ulBase);
        ulTemp = xHWREG(ulBase + TIMER_CTR) & TIMER_CTR_TME;
        TestAssert(ulTemp == 0,
                   "xpwm, \" PWM stop test\" error!");  
        
        //
        // CRR set/get test
        //
        PWMCRRSet(ulBase, 10000);
        ulTemp = PWMCRRGet(ulBase);
        TestAssert(ulTemp == 10000,
                   "xpwm, \" PWM stop test\" error!");  
        
        //
        // PWM duty set/get test
        //
        for(j = 0; j < 4; j++)
        {
            PWMDutySet(ulBase, PWMChannel[i][j], 50);
            ulTemp = PWMDutyGet(ulBase, PWMChannel[i][j]);
            TestAssert(ulTemp == 50,
                       "xpwm, \" PWM duty set/get test\" error!");  
        }
        
        //
        // PWM interrupt enable test
        //
        for(j = 0; j < 4; j++)
        {
            PWMIntEnable(ulBase, PWMChannel[i][j], PWMIntType[1]);
            ulTemp = xHWREG(ulBase + TIMER_ICTR) & PWM_INT_UEV1; 
            TestAssert(ulTemp == PWM_INT_UEV1,
                       "xpwm, \" PWM interrupt enable test\" error!");
            
            PWMIntEnable(ulBase, PWMChannel[i][j], PWMIntType[0]);
            ulTemp = xHWREG(ulBase + TIMER_ICTR) & (PWM_INT_CHXCC << j);
            TestAssert(ulTemp == PWM_INT_CHXCC << j,
                       "xpwm, \" PWM interrupt enable test\" error!");            
        }
        
        //
        // PWM interrupt disable test
        //
        for(j = 0; j < 4; j++)
        {
            PWMIntDisable(ulBase, PWMChannel[i][j], PWMIntType[1]);
            ulTemp = xHWREG(ulBase + TIMER_ICTR) & PWM_INT_UEV1; 
            TestAssert(ulTemp == 0,
                       "xpwm, \" PWM interrupt disable test\" error!");
            
            PWMIntDisable(ulBase, PWMChannel[i][j], PWMIntType[0]);
            ulTemp = xHWREG(ulBase + TIMER_ICTR) & (PWM_INT_CHXCC << j);
            TestAssert(ulTemp == 0,
                       "xpwm, \" PWM interrupt disable test\" error!");         
        }        
        
    }
}

//*****************************************************************************
//
//! \brief Get the Test description of xpwm001 register test.
//!
//! \return the desccription of the xpwm001 test.
//
//*****************************************************************************
const char* xpwm001GetTest(void)
{
    static const char * const pcName = "xpwm, 001, xpwm register test";
    return pcName;
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xpwm001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xpwm001Setup(void)
{
    xSysCtlClockSet(8000000, xSYSCTL_XTAL_8MHZ | xSYSCTL_OSC_MAIN);
   
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_PWMA);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_PWMB);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xpwm001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xpwm001TearDown(void)
{
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_PWMA);
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_PWMB);
}

//
// xpwm001 register test case struct.
//
const tTestCase sTestxpwm001Register = {
    xpwm001GetTest,
    xpwm001Setup,
    xpwm001TearDown,
    xpwm001Execute
};

//
// Xpwm test suits.
//
const tTestCase * const psPatternxpwm1[] =
{
    &sTestxpwm001Register,
    0
};

