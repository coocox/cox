//*****************************************************************************
//
//! @page xpwm_testcase xpwm register test
//!
//! File: @ref xpwmtest1.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xpwm sub component.<br><br>
//! - \p Board: KLx25Z128 Development Board <br><br>
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
#include "xhw_tpm.h"
#include "xpwm.h"
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
// PWM channel
//
static unsigned long PWMChannel[5] = {xPWM_CHANNEL0, xPWM_CHANNEL1, 
                                      xPWM_CHANNEL2, xPWM_CHANNEL3,
                                      xPWM_CHANNEL5};

//
// pwm output mode
//
static unsigned long PWMOutputMode[4] = {PWM_MODE_EDGE_ALIGNED1, 
                                         PWM_MODE_EDGE_ALIGNED2,
                                         PWM_MODE_CENTER_ALIGNED1,
                                         PWM_MODE_CENTER_ALIGNED2};                                       

//
// MOD value 
//
static unsigned long ulMODValue[3] = {1, 1000, 65534};

//
// PWM Frequency set value
//
static unsigned long PWMFrequency[3] = {200, 1000, 3000};

//
// PWM prescale set value
//
//static unsigned long PWMPrescale[3] = {1, 50, 255};

//
// PWM Int enable
//
static unsigned long PWMIntType[2] = {PWM_INT_CHXF, PWM_INT_TOF};

//
// PWM trigger source select
//
static unsigned long PWMClkSrc[10] = { 
 PWM_TRGSEL_EXTRGIN, PWM_TRGSEL_HSCMP0, PWM_TRGSEL_PITRG0, PWM_TRGSEL_PITRG1, 
 PWM_TRGSEL_TPM0OF, PWM_TRGSEL_TPM1OF, PWM_TRGSEL_TPM2OF, PWM_TRGSEL_RTCALARM, 
 PWM_TRGSEL_RTCSECONDS, PWM_TRGSEL_LPTMR};

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
    unsigned long ulChannel;
    unsigned long ulTemp;
    
    int j;
    ulBase = PWMA_BASE;
     
    for(j = 0; j < 5; j++)
    { 
        ulChannel = PWMChannel[j];
        xPWMInitConfigure(ulBase, ulChannel, xPWM_ONE_SHOT_MODE);
        ulTemp = xHWREG(ulBase + TPM_CONF) & TPM_CONF_CSOO;;
        TestAssert(ulTemp == TPM_CONF_CSOO,
                   "xpwm, \" One shot mode\" error!"); 
        xPWMInitConfigure(ulBase, PWMChannel[j], xPWM_TOGGLE_MODE);
        ulTemp = xHWREG(ulBase + TPM_CONF) & TPM_CONF_CSOO;;
        TestAssert(ulTemp == 0, "xpwm, \" toggle mode\" error!");            
        
        ulTemp = xHWREG(ulBase + TPM_C0SC + ulChannel * 8) & 
                                            (TPM_CNSC_MSB | TPM_CNSC_MSA);
        TestAssert(ulTemp == TPM_CNSC_MSB,
                   "xpwm, \" MSnB:MSnA 10£¬output pwm\" error!"); 
        
        ulTemp = xHWREG(ulBase + TPM_C0SC + ulChannel * 8) & 
                                            (TPM_CNSC_ELSB | TPM_CNSC_ELSA);
        TestAssert(ulTemp == TPM_CNSC_ELSB,
     "xpwm, \" ELSnB:ELSnA 10£¬Edge-aligned PWM High-true pulses\" error!");             
    }      
   
    for(j = 0; j < 5; j++)
    { 
        //
        // Edge-aligned PWM
        //
        PWMInitConfigure(ulBase, PWMChannel[j], PWMOutputMode[0]);
        ulTemp = xHWREG(ulBase + TPM_SC) & TPM_SC_CPWMS; 
        TestAssert(ulTemp == 0, 
                   "pwm, \" Edge-aligned PWM\" error!");
        ulTemp = xHWREG(ulBase + TPM_C0SC + PWMChannel[j] * 8) & TPM_CNSC_ELSB;
        TestAssert(ulTemp == TPM_CNSC_ELSB, 
                   "pwm, \" High-true pulses\" error!");
        
        //
        // Center-aligned PWM
        //
        PWMInitConfigure(ulBase, PWMChannel[j], PWMOutputMode[3]);
        ulTemp = xHWREG(ulBase + TPM_SC) & TPM_SC_CPWMS; 
        TestAssert(ulTemp == TPM_SC_CPWMS, 
                   "pwm, \" Center-aligned PWM\" error!");
        ulTemp = xHWREG(ulBase + TPM_C0SC + PWMChannel[j] * 8) & TPM_CNSC_ELSA;
        TestAssert(ulTemp == TPM_CNSC_ELSA, 
                   "pwm, \" Low-true pulses\" error!");            
    }
    
    //
    // Output enable test
    //
    for(j = 0; j < 5; j++)
    {
        PWMOutputEnable(ulBase, PWMChannel[j], PWMOutputMode[1]);
        ulTemp = xHWREG(ulBase + TPM_C0SC + PWMChannel[j] * 8) & TPM_CNSC_ELSA;
        TestAssert(ulTemp == TPM_CNSC_ELSA, 
                   "pwm, \" High-true pulses\" error!");
        PWMOutputEnable(ulBase, PWMChannel[j], PWMOutputMode[2]);
        ulTemp = xHWREG(ulBase + TPM_C0SC + PWMChannel[j] * 8) & TPM_CNSC_ELSB;
        TestAssert(ulTemp == TPM_CNSC_ELSB, 
                   "pwm, \" High-true pulses\" error!");                        
    }
    
    //
    // Output disable test
    //
    for(j = 0; j < 5; j++)
    {
        PWMOutputDisable(ulBase, PWMChannel[j]); 
        ulTemp = xHWREG(ulBase + TPM_C0SC + PWMChannel[j] * 8) & 
                                            (TPM_CNSC_ELSB | TPM_CNSC_ELSA);
        TestAssert(ulTemp == 0,
                   "xpwm, \" Output disable test\" error!");
    }
 
    //
    // PWM frequency set test
    // 
    for(j = 0; j < 3; j++)
    {       
        PWMFrequencySet(ulBase, PWMFrequency[j]);
        ulTemp = PWMFrequencyGet(ulBase);
        TestAssert(ulTemp == PWMFrequency[j],
                   "xpwm, \" Frequency set/get test\" error!");             
    }
    
    //
    // PWM frequency configure test
    //
    for(j = 0; j < 4; j++)
    {
       PWMFrequencyConfig(ulBase, 0x12340003);
       ulTemp = xHWREG(ulBase + TPM_SC) & TPM_SC_PS_M;
       TestAssert(ulTemp == 0x3,
                  "xpwm, \" PWM frequency configure test\" error!");
       ulTemp = xHWREG(ulBase + TPM_MOD);
       TestAssert(ulTemp == 0x1234,
                  "xpwm, \" PWM frequency configure test\" error!");
    }
        
    //
    // PWM duty set/get test
    //
    for(j = 0; j < 5; j++)
    {
        PWMDutySet(ulBase, PWMChannel[j], 50);
        ulTemp = PWMDutyGet(ulBase, PWMChannel[j]);
        TestAssert(ulTemp == 50, "xpwm, \" PWM duty set/get test\" error!"); 
                    
    }
    
    //
    // PWM interrupt enable test
    //
    for(j = 0; j < 5; j++)
    {
        PWMIntEnable(ulBase, PWMChannel[j], PWMIntType[1]);
        ulTemp = xHWREG(ulBase + TPM_SC) & TPM_SC_TOIE; 
        TestAssert(ulTemp == TPM_SC_TOIE,
                   "xpwm, \" PWM interrupt enable test\" error!");
        
        PWMIntEnable(ulBase, PWMChannel[j], PWMIntType[0]);
        ulTemp = xHWREG(ulBase + TPM_C0SC + 8 * PWMChannel[j]) & TPM_CNSC_CHIE;
        TestAssert(ulTemp == TPM_CNSC_CHIE,
                   "xpwm, \" PWM interrupt enable test\" error!");            
    }
    
    //
    // PWM interrupt disable test
    //
    for(j = 0; j < 5; j++)
    {
        PWMIntDisable(ulBase, PWMChannel[j], PWMIntType[1]);
        ulTemp = xHWREG(ulBase + TPM_SC) & TPM_SC_TOIE; 
        TestAssert(ulTemp == 0,"xpwm, \" PWM interrupt disable test\" error!");
                    
        PWMIntDisable(ulBase, PWMChannel[j], PWMIntType[0]);
        ulTemp = xHWREG(ulBase + TPM_C0SC + 8 * PWMChannel[j]) & TPM_CNSC_CHIE;
        TestAssert(ulTemp == 0,"xpwm, \" PWM interrupt disable test\" error!"); 
                           
    }        

    //
    // MOD set test
    //
    for(j = 0; j < 3; j++)
    {
        PWMMODSet(ulBase, ulMODValue[j]);
        ulTemp = PWMMODGet(ulBase);  
        TestAssert(ulTemp == ulMODValue[j], "xpwm, \" PWMMODSet\" error!");                                  
    }   

    //
    // PWM start test
    //
    PWMStart(ulBase);
    ulTemp = xHWREG(ulBase + TPM_SC) & TPM_SC_CMOD_CLK;
    TestAssert(ulTemp == TPM_SC_CMOD_CLK, "xpwm, \" PWM start test\" error!");                         
    
    //
    // PWM stop test
    //
    PWMStop(ulBase);
    j = 10;
    while(j--);
    ulTemp = xHWREG(ulBase + TPM_SC) & TPM_SC_CMOD_M;
    TestAssert(ulTemp == 0, "xpwm, \" PWM stop test\" error!");   

   //
   // Trigger source select
   //
   for(j = 0; j < 10; j++)
   {
       PWMTriggerSelect(ulBase, PWMClkSrc[j]); 
       ulTemp = xHWREG(ulBase + TPM_CONF) & TPM_CONF_TRGSEL_M; 
       TestAssert(ulTemp == PWMClkSrc[j],
                  "xpwm, \" Trigger source select\" error!");     
   }
   
   //
   // Counter Reload On Trigger configure.
   //
   PWMCROTConfigure(ulBase, PWM_CROT_EN);
   ulTemp = xHWREG(ulBase + TPM_CONF) & TPM_CONF_CROT;
   TestAssert(ulTemp == TPM_CONF_CROT, "xpwm, \" PWMCROTConfigure \" error!"); 
                
   PWMCROTConfigure(ulBase, PWM_CROT_DIS);
   ulTemp = xHWREG(ulBase + TPM_CONF) & TPM_CONF_CROT;
   TestAssert(ulTemp == 0, "xpwm, \" PWMCROTConfigure \" error!"); 

   //
   // Counter Stop On Overflow.
   //
   PWMCSOOConfigure(ulBase, PWM_CSOO_EN);  
   ulTemp = xHWREG(ulBase + TPM_CONF) & TPM_CONF_CSOO;  
   TestAssert(ulTemp == TPM_CONF_CSOO, "xpwm, \" PWMCSOOConfigure \" error!"); 
               
   PWMCSOOConfigure(ulBase, PWM_CSOO_DIS);  
   ulTemp = xHWREG(ulBase + TPM_CONF) & TPM_CONF_CSOO;  
   TestAssert(ulTemp == 0, "xpwm, \" PWMCSOOConfigure \" error!");                 
   
   //
   // Counter Stop On Overflow.
   //
   PWMCSOTConfigure(ulBase, PWM_CSOT_EN);  
   ulTemp = xHWREG(ulBase + TPM_CONF) & TPM_CONF_CSOT;  
   TestAssert(ulTemp == TPM_CONF_CSOT, "xpwm, \" PWMCSOTConfigure \" error!"); 
               
   PWMCSOTConfigure(ulBase, PWM_CSOT_DIS);  
   ulTemp = xHWREG(ulBase + TPM_CONF) & TPM_CONF_CSOT;  
   TestAssert(ulTemp == 0, "xpwm, \" PWMCSOTConfigure \" error!");                     
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
    //
    // Select the peripheral clock source
    //
    xSysCtlPeripheralClockSourceSet(xSYSCTL_PWMA_MAIN, 1);   
    
    //
    // Enable the peripheral clock
    //
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_PWMA);
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
const tTestCase * const psPatternxpwm00[] =
{
    &sTestxpwm001Register,
    0
};
