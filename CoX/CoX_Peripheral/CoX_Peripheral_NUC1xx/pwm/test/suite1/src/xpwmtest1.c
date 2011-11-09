//*****************************************************************************
//
//! @page xpwm_testcase xpwm register test
//!
//! File: @ref xpwmtest1.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xpwm sub component.<br><br>
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
//! - \subpage test_xpwm_register
//! .
//! \file xpwmtest1.c
//! \brief xpwm test source file
//! \brief xpwm test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xpwm.h"
#include "xhw_pwm.h"

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
// pwm inveter enable mask value
//
static unsigned long PWNInveterMask[4] = {0x00000004, 0x00000400, 
                                          0x00040000, 0x04000000};

//
// pwm Dead-zone set value 
//
static unsigned long PWMDeadZone[2] = {0x10, 0x20};

//
// pwm Dead-zone length value
//
static unsigned long PWMDeadZoneLength[3] = {5, 50, 255};

//
// pwm Frequency set value
//
static unsigned long PWMFrequency[3] = {200, 1000, 3000};

//
// pwm prescale set value
//
static unsigned long PWMPrescale[3] = {1, 50, 255};

//
// pwm divide set value
//
static unsigned long PWMDivide[3] = {PWM_CLOCK_DIV_1, 
                                     PWM_CLOCK_DIV_4,
                                     PWM_CLOCK_DIV_16};

//
// pwm counter set value 
//
static unsigned long PWMCounter[3] = {1, 1000, 65535};

//
// pwm duty set value
//
static unsigned long PWMDuty[3] = {1, 30, 99};

//
// pwm interrupt type
//
static unsigned long PWMIntType[4] = {PWM_INT_PWM, PWM_INT_CAP_FALL,
                                      PWM_INT_CAP_RISE, PWM_INT_CAP_BOTH};

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
        
        //
        // Output inverter enable
        //
        for(j = 0; j < 4; j++)
        {
            PWMInitConfigure(ulBase, PWMChannel[i][j], PWM_OUTPUT_INVERTER_EN);
            ulTemp = xHWREG( ulBase + PWM_PCR) & PWNInveterMask[j];
            TestAssert(ulTemp == PWNInveterMask[j],
                       "xpwm, \" Enable Inverter bit\" error!");
        }
        
        //
        // Reload mode set test
        //
        for(j = 0; j < 4; j++)
        {
            PWMInitConfigure(ulBase, PWMChannel[i][j], PWM_TOGGLE_MODE);
            ulTemp = xHWREG( ulBase + PWM_PCR) & (PWM_PCR_CH0MOD << (j * 8));
            TestAssert(ulTemp == PWM_TOGGLE_MODE << (j * 8),
                       "xpwm, \" Reload mode set\" error!");            
        }
        
        //
        // Dead-Zone enable test
        //
        for(j = 0; j < 4; j++)
        {
            PWMInitConfigure(ulBase, PWMChannel[i][j], PWM_DEAD_ZONE_EN);
            ulTemp = xHWREG( ulBase + PWM_PCR) & (PWM_DEAD_ZONE_EN << (j >> 1));
            TestAssert(ulTemp == PWMDeadZone[j>>1],
                       "xpwm, \" Dead-Zone enable test\" error!");        
        }
        
        //
        // Dead-Zone length set test
        //
        for(j = 0; j < 4; j++)
        {
            for(k = 0; k < 3; k++)
            {
                PWMInitConfigure(ulBase, PWMChannel[i][j], PWMDeadZoneLength[k] << 16 | PWM_DEAD_ZONE_EN);
                ulTemp = xHWREG(ulBase + PWM_PPR) & ( PWM_PPR_DZI01_M << 
                                    (j >> 1) * 8);
               // ulTemp = xHWREG(ulBase + PWM_PPR);
                ulTemp = ulTemp >> (16 + (j >> 1) * 8); 
                TestAssert(ulTemp == PWMDeadZoneLength[k],
                           "xpwm, \" Dead-Zone length set test\" error!");     
            }
        }
        
        //
        // PWM frequency set test
        //        
        for(j = 0; j < 4; j++)
        {
            for(k = 0; k < 3; k++)
            {
                ulFrequency = PWMFrequencySet(ulBase, PWMChannel[i][j], 
                                              PWMFrequency[k]);
                ulTemp = PWMFrequencyGet(ulBase, PWMChannel[i][j]);
                TestAssert(ulTemp == ulFrequency,
                           "xpwm, \" Frequency set test\" error!");             
            }
        }
        
        //
        // PWM frequency configure test
        //
        for(j = 0; j < 4; j++)
        {
            //
            // Prescale set test
            //           
            for(k = 0; k < 3; k++)
           {
               PWMFrequencyConfig(ulBase, PWMChannel[i][j], PWMPrescale[k] << 16);
               if(j < 2)
               {
                   ulTemp = ( xHWREG( ulBase + PWM_PPR ) & PWM_PPR_CP01_M ) >> PWM_PPR_CP01_S;
                   TestAssert(PWMPrescale[k] == ulTemp,
                              "xpwm, \" PWMPrescale set test \" error!");
               }
               else
               {
                   ulTemp = ( xHWREG( ulBase + PWM_PPR ) & PWM_PPR_CP23_M ) >> PWM_PPR_CP23_S;
                   TestAssert(PWMPrescale[k] == ulTemp,
                              "xpwm, \" PWMPrescale set test \" error!");
               }
           }
           
          //
          // Frequency Divide set test
          //
          for(k = 0; k < 3; k++)
          {
              PWMFrequencyConfig(ulBase, PWMChannel[i][j], PWMDivide[k] << 24);
              switch(j)
              {
              case 0:
                  ulTemp = ( xHWREG( ulBase + PWM_CSR ) & PWM_CSR_CSR0_M ) >> PWM_CSR_CSR0_S;
                  break;
              case 1:
                  ulTemp = ( xHWREG( ulBase + PWM_CSR ) & PWM_CSR_CSR1_M ) >> PWM_CSR_CSR1_S;
                  break;
              case 2:
                  ulTemp = ( xHWREG( ulBase + PWM_CSR ) & PWM_CSR_CSR2_M ) >> PWM_CSR_CSR2_S;
                  break;
              case 3:
                  ulTemp = ( xHWREG( ulBase + PWM_CSR ) & PWM_CSR_CSR3_M ) >> PWM_CSR_CSR3_S;
                  break;   
              }
              TestAssert(PWMDivide[k] == ulTemp,
                         "xpwm, \" Divide set test \" error!");
          }
          
          //
          // Counter set test
          //
          for(k = 0; k < 3; k++)
          {
              PWMFrequencyConfig(ulBase, PWMChannel[i][j], PWMCounter[k]);            
              switch(j)
              {
              case 0:
                  ulTemp = ( xHWREG( ulBase+PWM_CNR0 ) & PWM_CNR0_CNR0_M ) >> PWM_CNR0_CNR0_S;
                  break;
              case 1:
                  ulTemp = ( xHWREG( ulBase + PWM_CNR1 ) & PWM_CNR1_CNR1_M ) >> PWM_CNR1_CNR1_S;
                  break;
              case 2:
                  ulTemp = ( xHWREG( ulBase + PWM_CNR2 ) & PWM_CNR2_CNR2_M ) >> PWM_CNR2_CNR2_S;
                  break;
              case 3:
                  ulTemp = ( xHWREG( ulBase + PWM_CNR3 ) & PWM_CNR3_CNR3_M ) >> PWM_CNR3_CNR3_S;
                  break;   
              }
              TestAssert(PWMCounter[k] == ulTemp,
                         "xpwm, \" Counter set test \" error!");              
          }           
        }
        
        //
        // Output enable test
        //
        for(j = 0; j < 4; j++)
        {
            PWMOutputEnable(ulBase, PWMChannel[i][j]);
            ulTemp = xHWREG(ulBase + PWM_POE) & (PWM_POE_PWM0 << j);
            TestAssert(ulTemp == (PWM_POE_PWM0 << j), 
                       "xpwm, \"Output enable test \" error!");          
        }
        
        //
        // Output disable test
        //
        for(j = 0; j < 4; j++)
        {
            PWMOutputDisable(ulBase, PWMChannel[i][j]);
            ulTemp = xHWREG(ulBase + PWM_POE) & (PWM_POE_PWM0 << j);
            TestAssert(ulTemp == 0, 
                       "xpwm, \"Output disable test \" error!");          
        }
        
        //
        // PWM start test
        //
        for(j = 0; j < 4; j++)
        {
            PWMStart(ulBase, PWMChannel[i][j]);
            ulTemp = xHWREG(ulBase + PWM_PCR) & (PWM_PCR_CH0EN << (j << 3));
            TestAssert(ulTemp == (PWM_PCR_CH0EN << (j << 3)),
                       "xpwm, \"PWM start test\" error!");
        }
        
        //
        // PWM stop test
        //
        for(j = 0; j < 4; j++)
        {
            PWMStop(ulBase, PWMChannel[i][j]);
            ulTemp = xHWREG(ulBase + PWM_PCR) & (PWM_PCR_CH0EN << (j << 3));
            TestAssert(ulTemp == 0,
                       "xpwm, \"PWM stop test\" error!");
        }
       
        //
        // PWM duty set test
        //
        for(j = 0; j < 4; j++)
        {
             for(k = 0; k < 3; k++)
             {
                 PWMFrequencyConfig(ulBase, PWMChannel[i][j], 10000);
                 PWMDutySet(ulBase, PWMChannel[i][j], PWMDuty[k]);
                 ulTemp = PWMDutyGet(ulBase, PWMChannel[i][j]);
                 TestAssert(PWMDuty[k] == ulTemp + 1,
                            "xpwm, \"PWM duty set \" error!");
             }
        }
       
        //
        // PWM capture enable test
        // 
        for(j = 0; j < 4; j++)
        {
            PWMCAPEnable(ulBase, PWMChannel[i][j]);
            ulTemp = xHWREG(ulBase + PWM_CCR0 + (j >> 1)*4) & 
                          (PWM_CCR0_CAPCH0EN << ((j % 2) ? 16 : 0));
            TestAssert(ulTemp == (PWM_CCR0_CAPCH0EN << ((j % 2) ? 16 : 0)),
                       "xpwm, \"Capture enable test\" error!");            
        }
        
        //
        // PWM capture disable test
        //
        for(j = 0; j < 4; j++)
        {
            PWMCAPDisable(ulBase, PWMChannel[i][j]);
            ulTemp = xHWREG(ulBase + PWM_CCR0 + (j >> 1)*4) & 
                          (PWM_CCR0_CAPCH0EN << ((j % 2) ? 16 : 0));
            TestAssert(ulTemp == 0,
                       "xpwm, \"Capture disable test\" error!");             
        }
        
        //
        // PWM input enable test
        //
        for(j = 0; j < 4; j++)
        {
            PWMCAPInputEnable(ulBase, PWMChannel[i][j]);
            ulTemp = xHWREG(ulBase + PWM_CAPENR) & (PWM_CAPENR_CAPIE_0 << j);
            TestAssert(ulTemp == PWM_CAPENR_CAPIE_0 << j,
                       "xpwm, \"PWM input enable test\" error!");   
        }
        
        //
        // PWM input disable test
        //
        for(j = 0; j < 4; j++)
        {
            PWMCAPInputDisable(ulBase, PWMChannel[i][j]);
            ulTemp = xHWREG(ulBase + PWM_CAPENR) & (PWM_CAPENR_CAPIE_0 << j);
            TestAssert(ulTemp == 0,
                       "xpwm, \"PWM input disable test\" error!");   
        }
        
        //
        // PWM interrupt enable test
        //
        for(j = 0; j < 4; j++)
        {
            for(k = 0; k < 3; k++)
            {  
                PWMIntEnable(ulBase, PWMChannel[i][j], PWMIntType[k]);
                if (PWMIntType[k] == PWM_INT_PWM)
                {
                    ulTemp = xHWREG(ulBase + PWM_PIER) & (PWM_PIER_PWMIE0 << j);
                    TestAssert(ulTemp == (PWM_PIER_PWMIE0 << j),
                               "xpwm, \"PWM interrupt enable test\" error!"); 
                }
                else
                {
                    ulTemp = xHWREG(ulBase + PWM_CCR0 + (j >> 1)*4) & (PWMIntType[k] << ((j % 2) ? 16 : 0));
                    TestAssert(ulTemp == (PWMIntType[k] << ((j % 2) ? 16 : 0)),
                               "xpwm, \"PWM interrupt enable test\" error!"); 
                }
            }
        }
        
        //
        // PWM interrupt disable test
        //
        for(j = 0; j < 4; j++)
        {
            for(k = 0; k < 3; k++)
            {  
                PWMIntDisable(ulBase, PWMChannel[i][j], PWMIntType[k]);
                if (PWMIntType[k] == PWM_INT_PWM)
                {
                    ulTemp = xHWREG(ulBase + PWM_PIER) & (PWM_PIER_PWMIE0 << j);
                    TestAssert(ulTemp == 0,
                               "xpwm, \"PWM interrupt disable test\" error!"); 
                }
                else
                {
                    ulTemp = xHWREG(ulBase + PWM_CCR0 + (j >> 1)*4) & (PWMIntType[k] << ((j % 2) ? 16 : 0));
                    TestAssert(ulTemp == 0,"xpwm, \"PWM interrupt disable test\" error!"); 
                }
            }
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
static char* xpwm001GetTest(void)
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
    SysCtlKeyAddrUnlock();  
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
   
    xSysCtlPeripheralEnable( SYSCTL_PERIPH_PWM01 );
    xSysCtlPeripheralEnable( SYSCTL_PERIPH_PWM23 );
    xSysCtlPeripheralEnable( SYSCTL_PERIPH_PWM45 );
    xSysCtlPeripheralEnable( SYSCTL_PERIPH_PWM67 );
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
    xSysCtlPeripheralDisable( SYSCTL_PERIPH_PWM01 );
    xSysCtlPeripheralDisable( SYSCTL_PERIPH_PWM23 );
    xSysCtlPeripheralDisable( SYSCTL_PERIPH_PWM45 );
    xSysCtlPeripheralDisable( SYSCTL_PERIPH_PWM67 );
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

