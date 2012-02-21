//*****************************************************************************
//
//! @page xpwm_testcase xpwm register test
//!
//! File: @ref xpwmtest1.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xpwm sub component.<br><br>
//! - \p Board: Mini51 <br><br>
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
static unsigned long PWMBase[1] = {PWMA_BASE};

//
// pwm channel value
//
static unsigned long PWMChannel[6] = {0,1,2,3,4,5};

//
// pwm inveter enable mask value
//
static unsigned long PWNInveterMask[6] = {0x00000004,0x00000040,0x00000400, 
                                          0x00004000,0x00040000,0x00400000};

//
// pwm Dead-zone set value 
//
static unsigned long PWMDeadZone[3] = {0x01000000, 0x02000000, 0x04000000};

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
static unsigned long PWMDuty[3] = {99, 30, 1};

//
// pwm interrupt type
//
static unsigned long PWMIntType[3] = {PWM_INT_PWM, PWM_INT_BRAKE, PWM_INT_DUTY};
//
// pwm operation type
//
static unsigned long PWMOperationMode[3] = {PWM_INDEPENDENT_MODE, 
                                            PWM_COMPLEMENTARY_MODE, 
                                            PWM_SYNCHRONIZED_MODE};
//
// pwm fault break source
//
static unsigned long FaultBreakSource[3] = {PWM_FB_EINT0, PWM_FB_CPO0, 
                                                         PWM_FB_EINT1};
//
// PWM Fault Break Output Level
//
static unsigned long PWMFaultBreakOutputLevel[2] = {1, 0};
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
    for(i = 0; i < 1; i++)
    {   
        ulBase = PWMBase[i];
        
        //
        // Output inverter enable
        //
        for(j = 0; j < 6; j++)
        {
            PWMInitConfigure(ulBase, PWMChannel[j], PWM_OUTPUT_INVERTER_EN);
            ulTemp = xHWREG( ulBase + PWM_PCR) & PWNInveterMask[j];
            TestAssert(ulTemp == PWNInveterMask[j], "xpwm, error!");
        }
        //
        // Group mode enable
        //
        for(j = 0; j < 6; j++)
        {
            PWMInitConfigure(ulBase, PWMChannel[j], PWM_GROUP_MODE);
            ulTemp = xHWREG( ulBase + PWM_PCR) & PWM_GROUP_MODE;
            TestAssert(ulTemp == PWM_GROUP_MODE, "xpwm, error!");
        }
        //
        // Center alligened enable
        //
        for(j = 0; j < 6; j++)
        {
            PWMInitConfigure(ulBase, PWMChannel[j], PWM_CENTER_ALLIGNED_TYPE);
            ulTemp = xHWREG( ulBase + PWM_PCR) & PWM_CENTER_ALLIGNED_TYPE;
            TestAssert(ulTemp == PWM_CENTER_ALLIGNED_TYPE, "xpwm, error!");
        }
        //
        // Edge alligened enable
        //
        for(j = 0; j < 6; j++)
        {
            PWMInitConfigure(ulBase, PWMChannel[j], PWM_EDGE_ALLIGNED_TYPE);
            ulTemp = xHWREG( ulBase + PWM_PCR) & PWM_EDGE_ALLIGNED_TYPE;
            TestAssert(ulTemp == PWM_EDGE_ALLIGNED_TYPE, "xpwm, error!");
        }
        //
        // PWM operation mode set test
        //
        for(j = 0; j < 6; j++)
        {
            for(k = 0; k < 3; k++)
            {
                PWMInitConfigure(ulBase, PWMChannel[j], PWMOperationMode[k]);
                ulTemp = xHWREG(ulBase + PWM_PCR) & PWMOperationMode[k];
                TestAssert(ulTemp == PWMOperationMode[k], "xpwm, error!");     
            }
        }
        //
        // Reload mode set test
        //
        for(j = 0; j < 6; j++)
        {
            PWMInitConfigure(ulBase, PWMChannel[j], PWM_TOGGLE_MODE);
            ulTemp = xHWREG( ulBase + PWM_PCR) & (PWM_PCR_CH0MOD << (j * 4));
            TestAssert(ulTemp == PWM_TOGGLE_MODE << (j * 4), "xpwm, error!");            
        }
        
        //
        // Dead-Zone enable test
        //
        for(j = 0; j < 6; j++)
        {
            PWMInitConfigure(ulBase, PWMChannel[j], PWM_DEAD_ZONE_EN);
            ulTemp = xHWREG( ulBase + PWM_PCR) & (PWM_DEAD_ZONE_EN << (j >> 1));
            TestAssert(ulTemp == PWMDeadZone[j>>1], "xpwm, error!");        
        }
       
        //
        // Dead-Zone length set test
        //
        for(j = 0; j < 6; j++)
        {
            for(k = 0; k < 3; k++)
            {
                PWMInitConfigure(ulBase, PWMChannel[j], 
                                 PWMDeadZoneLength[k] << 16 | PWM_DEAD_ZONE_EN);
                
                ulTemp = xHWREG(ulBase + PWM_PDZIR) & 
                                             (PWM_PDZIR_DZI01_M << (j / 2) * 8);
                
                ulTemp = ulTemp >> ((j / 2) * 8); 
                TestAssert(ulTemp == PWMDeadZoneLength[k], "xpwm, error!");     
            }
        }
      
        //
        // PWM frequency set test
        //        
        for(j = 0; j < 6; j++)
        {
            //
            // PWM_EDGE_ALLIGNED_TYPE
            //
            PWMInitConfigure(ulBase, PWMChannel[j], PWM_EDGE_ALLIGNED_TYPE);
            for(k = 0; k < 3; k++)
            {
                ulFrequency = PWMFrequencySet(ulBase, PWMChannel[j], PWMFrequency[k]);
                ulTemp = PWMFrequencyGet(ulBase, PWMChannel[j]);
                TestAssert(ulTemp == ulFrequency, "xpwm, error!");             
            }
            
            //
            // PWM_CENTER_ALLIGNED_TYPE
            //
            PWMInitConfigure(ulBase, PWMChannel[j], PWM_CENTER_ALLIGNED_TYPE);
            for(k = 0; k < 3; k++)
            {
                ulFrequency = PWMFrequencySet(ulBase, PWMChannel[j], 
                                              PWMFrequency[k]);
                ulTemp = PWMFrequencyGet(ulBase, PWMChannel[j]);
                TestAssert(ulTemp == ulFrequency,
                           "xpwm, \" Frequency set test\" error!");             
            }
        }
         
        //
        // PWM frequency configure test
        //
        for(j = 0; j < 6; j++)
        {
            //
            // Prescale set test
            //           
            for(k = 0; k < 3; k++)
           {
               PWMFrequencyConfig(ulBase, PWMChannel[j], PWMPrescale[k] << 16);
               if((j/2)==0)
               {
                   ulTemp = ( xHWREG(ulBase + PWM_PPR) & PWM_PPR_CP01_M) >> PWM_PPR_CP01_S;
                   TestAssert(PWMPrescale[k] == ulTemp, "xpwm  error!");
               }
               else if((j/2)==1)
               {
                   ulTemp = (xHWREG(ulBase + PWM_PPR) & PWM_PPR_CP23_M) >> PWM_PPR_CP23_S;
                   TestAssert(PWMPrescale[k] == ulTemp, "xpwm  error!");
               }
               else
               {
                   ulTemp = (xHWREG( ulBase + PWM_PPR) & PWM_PPR_CP45_M) >> PWM_PPR_CP45_S;
                   TestAssert(PWMPrescale[k] == ulTemp, "xpwm  error!");
               }            
           }
           
          //
          // Frequency Divide set test
          //
          for(k = 0; k < 3; k++)
          {
              PWMFrequencyConfig(ulBase, PWMChannel[j], PWMDivide[k] << 24);
              switch(j)
              {
              case 0:
                  ulTemp = (xHWREG(ulBase + PWM_CSR) & PWM_CSR_CSR0_M) >> PWM_CSR_CSR0_S;
                  break;
              case 1:
                  ulTemp = (xHWREG(ulBase + PWM_CSR) & PWM_CSR_CSR1_M) >> PWM_CSR_CSR1_S;
                  break;
              case 2:
                  ulTemp = (xHWREG(ulBase + PWM_CSR) & PWM_CSR_CSR2_M) >> PWM_CSR_CSR2_S;
                  break;
              case 3:
                  ulTemp = (xHWREG(ulBase + PWM_CSR) & PWM_CSR_CSR3_M) >> PWM_CSR_CSR3_S;
                  break;
              case 4:
                  ulTemp = (xHWREG(ulBase + PWM_CSR) & PWM_CSR_CSR4_M) >> PWM_CSR_CSR4_S;
                  break;
              case 5:
                  ulTemp = (xHWREG(ulBase + PWM_CSR) & PWM_CSR_CSR5_M) >> PWM_CSR_CSR5_S;
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
              PWMFrequencyConfig(ulBase, PWMChannel[j], PWMCounter[k]);            
              switch(j)
              {
              case 0:
                  ulTemp = (xHWREG(ulBase + PWM_CNR0) & PWM_CNR0_CNR0_M) >> PWM_CNR0_CNR0_S;
                  break;
              case 1:
                  ulTemp = (xHWREG(ulBase + PWM_CNR1) & PWM_CNR1_CNR1_M) >> PWM_CNR1_CNR1_S;
                  break;
              case 2:
                  ulTemp = (xHWREG(ulBase + PWM_CNR2) & PWM_CNR2_CNR2_M) >> PWM_CNR2_CNR2_S;
                  break;
              case 3:
                  ulTemp = (xHWREG(ulBase + PWM_CNR3) & PWM_CNR3_CNR3_M) >> PWM_CNR3_CNR3_S;
                  break;
              case 4:
                  ulTemp = (xHWREG(ulBase + PWM_CNR4) & PWM_CNR4_CNR4_M) >> PWM_CNR4_CNR4_S;
                  break;
              case 5:
                  ulTemp = (xHWREG(ulBase + PWM_CNR5) & PWM_CNR5_CNR5_M) >> PWM_CNR5_CNR5_S;
              }
              TestAssert(PWMCounter[k] == ulTemp,
                         "xpwm, \" Counter set test \" error!");              
          }           
        }
        
        //
        // Output enable test
        //
        for(j = 0; j < 6; j++)
        {
            PWMOutputEnable(ulBase, PWMChannel[j]);
            ulTemp = xHWREG(ulBase + PWM_POE) & (PWM_POE_PWM0 << j);
            TestAssert(ulTemp == (PWM_POE_PWM0 << j), 
                       "xpwm, \"Output enable test \" error!");          
        }
        
        //
        // Output disable test
        //
        for(j = 0; j < 6; j++)
        {
            PWMOutputDisable(ulBase, PWMChannel[j]);
            ulTemp = xHWREG(ulBase + PWM_POE) & (PWM_POE_PWM0 << j);
            TestAssert(ulTemp == 0, 
                       "xpwm, \"Output disable test \" error!");          
        }
        
        //
        // PWM start test
        //
        for(j = 0; j < 6; j++)
        {
            PWMStart(ulBase, PWMChannel[j]);
            ulTemp = xHWREG(ulBase + PWM_PCR) & (PWM_PCR_CH0EN << (j << 2));
            TestAssert(ulTemp == (PWM_PCR_CH0EN << (j << 2)),
                       "xpwm, \"PWM start test\" error!");
        }
        
        //
        // PWM stop test
        //
        for(j = 0; j < 6; j++)
        {
            PWMStop(ulBase, PWMChannel[j]);
            ulTemp = xHWREG(ulBase + PWM_PCR) & (PWM_PCR_CH0EN << (j << 2));
            TestAssert(ulTemp == 0,
                       "xpwm, \"PWM stop test\" error!");
        }
       
        //
        // PWM duty set test
        //
        for(j = 0; j < 6; j++)
        {    
            //
            // PWM_EDGE_ALLIGNED_TYPE
            //
            PWMInitConfigure(ulBase, PWMChannel[j], PWM_EDGE_ALLIGNED_TYPE);
            for(k = 0; k < 3; k++)
            {
                PWMFrequencyConfig(ulBase, PWMChannel[j], 10000);
                PWMDutySet(ulBase, PWMChannel[j], PWMDuty[k]);
                ulTemp = PWMDutyGet(ulBase, PWMChannel[j]);
                TestAssert(PWMDuty[k] == ulTemp,"xpwm, \"duty set\"error!");
            }
            //
            // PWM_CENTER_ALLIGNED_TYPE
            //
            PWMInitConfigure(ulBase, PWMChannel[j], PWM_CENTER_ALLIGNED_TYPE);
            for(k = 0; k < 3; k++)
            {
                PWMFrequencyConfig(ulBase, PWMChannel[j], 10000);
                PWMDutySet(ulBase, PWMChannel[j], PWMDuty[k]);
                ulTemp = PWMDutyGet(ulBase, PWMChannel[j]);
                TestAssert(PWMDuty[k] == ulTemp + 1,"xpwm, \"duty set\"error!");
            }
        }
        
        //
        // PWM interrupt enable test
        //
        for(j = 0; j < 6; j++)
        {
            for(k = 0; k < 3; k++)
            {  
                PWMIntEnable(ulBase, PWMChannel[j], PWMIntType[k]);
                if (PWMIntType[k] == PWM_INT_PWM)
                {
                    ulTemp = xHWREG(ulBase + PWM_PIER) & (PWM_PIER_PWMPIE0 << j);
                    TestAssert(ulTemp == (PWM_PIER_PWMPIE0 << j) | PWM_INT_PWM , 
                                         "xpwm, error!"); 
                }
                else if(PWMIntType[k] == PWM_INT_DUTY)
                {
                    ulTemp = xHWREG(ulBase + PWM_PIER) & (PWM_PIER_PWMDIE0 << j);
                    TestAssert(ulTemp == (PWM_PIER_PWMDIE0 << j)|PWM_INT_DUTY , 
                                         "xpwm, error!"); 
                }
                else
                {
                    ulTemp = xHWREG(ulBase + PWM_PIER) & PWM_PIER_BRKIE;
                    TestAssert(ulTemp == PWM_PIER_BRKIE, "xpwm, error!");      
                }
            }
        }
        
        //
        // PWM interrupt disable test
        //
        for(j = 0; j < 6; j++)
        {
            for(k = 0; k < 3; k++)
            {  
                PWMIntDisable(ulBase, PWMChannel[j], PWMIntType[k]);
                if (PWMIntType[k] == PWM_INT_PWM)
                {
                    ulTemp = xHWREG(ulBase + PWM_PIER) & (PWM_PIER_PWMPIE0 << j);
                    TestAssert(ulTemp == 0, "xpwm, error!"); 
                }
                else if(PWMIntType[k] == PWM_INT_DUTY)
                {
                    ulTemp = xHWREG(ulBase + PWM_PIER) & (PWM_PIER_PWMDIE0 << j);
                    TestAssert(ulTemp == 0, "xpwm, error!"); 
                }
                else
                {
                    ulTemp = xHWREG(ulBase + PWM_PIER) & PWM_PIER_BRKIE;
                    TestAssert(ulTemp == 0, "xpwm, error!");      
                }
            }
        }
        //
        // Fault break enable test.
        //
        for(k = 0; k < 3; k++)
        {  
            PWMFaultBreakEnable(ulBase, FaultBreakSource[k]);
            ulTemp = xHWREG(ulBase + PWM_PFBCON) & FaultBreakSource[k];
            TestAssert(ulTemp == FaultBreakSource[k], "xpwm, error!"); 
        }
        //
        // Fault break disable test.
        //
        for(k = 0; k < 3; k++)
        {  
            PWMFaultBreakDisable(ulBase, FaultBreakSource[k]);
            ulTemp = xHWREG(ulBase + PWM_PFBCON) & FaultBreakSource[k];
            TestAssert(ulTemp == 0, "xpwm, error!"); 
        }
        //
        // PWM fault break output level set test
        //
        for(j = 0; j < 6; j++)
        {
            for(k = 0; k < 2; k++)
            {  
                PWMFaultBreakOutputLevelSet(ulBase, PWMChannel[j], PWMFaultBreakOutputLevel[k]);
                ulTemp = xHWREG(ulBase + PWM_PFBCON);
                TestAssert(ulTemp == (PWMFaultBreakOutputLevel[k] << (24 + j)), 
                                      "xpwm, error!"); 
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
// xpwm test suits.
//
const tTestCase * const psPatternxpwm1[] =
{
    &sTestxpwm001Register,
    0
};

