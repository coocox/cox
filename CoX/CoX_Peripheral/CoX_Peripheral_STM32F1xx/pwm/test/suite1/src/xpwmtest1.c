//*****************************************************************************
//
//! @page xpwm_testcase xpwm register test
//!
//! File: @ref xpwmtest1.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xpwm sub component.<br><br>
//! - \p Board: STM32F1xx Development Board <br><br>
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
static unsigned long PWNBase[4] = {xPWMA_BASE, xPWMC_BASE, xPWMD_BASE, xPWME_BASE};

//
// pwm channel value
//
static unsigned long PWMChannel[4] = {0,1,2,3};

//
// PWM output mode
//
static unsigned long ulPWMOutMode[2] = {PWM_OM_1, PWM_OM_2};

//
// PWM count dir
//
static unsigned long ulPWMCountDir[5] = {PWM_CNT_MODE_UP, PWM_CNT_MODE_DOWN,
                                         PWM_CNT_MODE_CENTER_1, PWM_CNT_MODE_CENTER_2,
                                         PWM_CNT_MODE_CENTER_3};

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
    for(i = 0; i < 5; i++)
    {   
        ulBase = PWNBase[i];
        
        if(i==0)
        {
            for(j = 0; j < 3; j++)
            { 

                xPWMInitConfigure(ulBase, PWMChannel[j], (PWM_TOGGLE_MODE|xPWM_OUTPUT_INVERTER_EN | PWM_DEAD_ZONE_EN));

                ulTemp = xHWREG(ulBase + TIMER_CCMR1 + (PWMChannel[j]/2)*4) & (TIMER_CCMR1_OC1M_PWMM2 <<
                                                                               (PWMChannel[j]%2)*8);
        
                TestAssert(ulTemp == (TIMER_CCMR1_OC1M_PWMM2 << (PWMChannel[j]%2)*8),
                           "xpwm, \" PWM Mode\" error!");

                ulTemp = xHWREG(ulBase + TIMER_CCER) & (PWM_DEAD_ZONE_EN << (PWMChannel[j]*4));
            
                TestAssert(ulTemp == (PWM_DEAD_ZONE_EN << (PWMChannel[j]*4)),
                           "xpwm, \" PWM PWM_DEAD_ZONE_EN configure\" error!");
            }
        }
        for(j = 0; j < 4; j++)
        { 
            //
            // PWM output mode
            //
            for(k = 0; k < 2; k++)
            {
                PWMInitConfigure(ulBase, PWMChannel[j], ulPWMOutMode[k], ulPWMCountDir[0]);
                ulTemp = xHWREG(ulBase + TIMER_CCMR1 + (PWMChannel[j]/2)*4) & (ulPWMOutMode[k]<<(PWMChannel[j]%2)*8);
                TestAssert(ulTemp == (ulPWMOutMode[k]<<(PWMChannel[j]%2)*8),
                           "xpwm, \" PWM output mode...\" error!");
            }
            
            //
            // PWM dir configure
            //
            for(k = 0; k < 5; k++)
            {
                PWMInitConfigure(ulBase, PWMChannel[j], ulPWMOutMode[0], ulPWMCountDir[k]);
                ulTemp = xHWREG(ulBase + TIMER_CR1) & (PWM_CNT_MODE_DOWN|PWM_CNT_MODE_CENTER_3);
                TestAssert(ulTemp == ulPWMCountDir[k],
                           "xpwm, \" PWM dir configure\" error!");
            }  
        }
        
        //
        // PWM frequency set test
        //
        ulFrequency = PWMFrequencySet(ulBase, PWMFrequency[0]);
        ulTemp = PWMFrequencyGet(ulBase);
        TestAssert(ulTemp == PWMFrequency[0],
                   "xpwm, \" Frequency set/get test\" error!");

        ulFrequency = PWMFrequencySet(ulBase, PWMFrequency[1]);
        ulTemp = PWMFrequencyGet(ulBase);
        TestAssert(ulTemp == PWMFrequency[1],
                   "xpwm, \" Frequency set/get test\" error!");             

        ulFrequency = PWMFrequencySet(ulBase, PWMFrequency[2]);
        ulTemp = PWMFrequencyGet(ulBase);
        TestAssert(ulTemp == PWMFrequency[2],
                   "xpwm, \" Frequency set/get test\" error!");

        //
        // PWM frequency configure test
        //
        PWMFrequencyConfig(ulBase, 0x12341234);
        ulTemp = xHWREG(ulBase + TIMER_ARR);
        TestAssert(ulTemp == 0x1234,
                   "xpwm, \" PWM frequency configure test\" error!");
        ulTemp = xHWREG(ulBase + TIMER_PSC);
        TestAssert(ulTemp == 0x1233,
                   "xpwm, \" PWM frequency configure test\" error!");

        
        //
        // Output enable test
        //
        for(j = 0; j < 4; j++)
        {
            PWMOutputEnable(ulBase, PWMChannel[j]);
            ulTemp = xHWREG(ulBase + TIMER_CCMR1 + (PWMChannel[j]/2)*4) & (TIMER_CCMR1_OC1PE << (PWMChannel[j]%2) * 8);
            TestAssert(ulTemp == (TIMER_CCMR1_OC1PE << (PWMChannel[j]%2) * 8),
                       "xpwm, \" Output enable test\" error!");
        }
        
        //
        // Output disable test
        //
        for(j = 0; j < 4; j++)
        {
            PWMOutputDisable(ulBase, PWMChannel[j]); 
            ulTemp = xHWREG(ulBase + TIMER_CCMR1 + (PWMChannel[j]/2)*4) & (TIMER_CCMR1_OC1PE << (PWMChannel[j]%2) * 8);
            TestAssert(ulTemp == 0,
                       "xpwm, \" Output disable test\" error!");
        }
        
        //
        // PWM start test
        //
        PWMStart(ulBase);
        ulTemp = xHWREG(ulBase + TIMER_CR1) & TIMER_CR1_CEN;
        TestAssert(ulTemp == TIMER_CR1_CEN,
                   "xpwm, \" Output disable test\" error!");            
        
        //
        // PWM stop test
        //
        PWMStop(ulBase);
        ulTemp = xHWREG(ulBase + TIMER_CR1) & TIMER_CR1_CEN;
        TestAssert(ulTemp == 0,
                   "xpwm, \" PWM stop test\" error!");  
        
        //
        // CRR set/get test
        //
        PWMARRSet(ulBase, 10000);
        ulTemp = PWMARRGet(ulBase) & TIMER_ARR_CH3IMAE_M;
        TestAssert(ulTemp == 10000,
                   "xpwm, \" PWM stop test\" error!");  
        
        //
        // PWM duty set/get test
        //
        for(j = 0; j < 4; j++)
        {
            PWMDutySet(ulBase, PWMChannel[j], 50);
            ulTemp = PWMDutyGet(ulBase, PWMChannel[j]);
            TestAssert(ulTemp == 50,
                       "xpwm, \" PWM duty set/get test\" error!");  
        }
        
        //
        // PWM interrupt enable test
        //
        for(j = 0; j < 4; j++)
        {
            PWMIntEnable(ulBase, PWMChannel[j], PWMIntType[1]);
            ulTemp = xHWREG(ulBase + TIMER_DIER) & PWM_INT_UEV1; 
            TestAssert(ulTemp == PWM_INT_UEV1,
                       "xpwm, \" PWM interrupt enable test\" error!");
            
            PWMIntEnable(ulBase, PWMChannel[j], PWMIntType[0]);
            ulTemp = xHWREG(ulBase + TIMER_DIER) & (PWM_INT_CHXCC << PWMChannel[j]);
            TestAssert(ulTemp == (PWM_INT_CHXCC << PWMChannel[j]),
                       "xpwm, \" PWM interrupt enable test\" error!");            
        }
        
        //
        // PWM interrupt disable test
        //
        for(j = 0; j < 4; j++)
        {
            PWMIntDisable(ulBase, PWMChannel[j], PWMIntType[1]);
            ulTemp = xHWREG(ulBase + TIMER_DIER) & PWM_INT_UEV1; 
            TestAssert(ulTemp == 0,
                       "xpwm, \" PWM interrupt disable test\" error!");
            
            PWMIntDisable(ulBase, PWMChannel[j], PWMIntType[0]);
            ulTemp = xHWREG(ulBase + TIMER_DIER) & (PWM_INT_CHXCC << PWMChannel[j]);
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
static char* xpwm001GetTest( void )
{
    return "xpwm, 001, xpwm register test";
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
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMA);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMC);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMB);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMD);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWME);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_PWMF);
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
    xSysCtlPeripheralDisable(xSYSCTL_PERIPH_PWMA);
    xSysCtlPeripheralDisable(xSYSCTL_PERIPH_PWMB);
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
