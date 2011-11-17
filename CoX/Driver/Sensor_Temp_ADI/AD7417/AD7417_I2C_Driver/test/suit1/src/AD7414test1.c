//*****************************************************************************
//
//! @page di_ad7417arz_testcase di_ad7417arz register test
//!
//! File: @ref AD7417test1.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the di_ad7417arz sub component.<br><br>
//! - \p Board: NUC140 & AD7417ARZ board <br><br>
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
//! - \subpage test_di_ad7417_register
//! .
//! \file AD7417test1.c
//! \brief di_ad7417 test source file
//! \brief di_ad7417 test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_ad7417.h"
#include "ad7417.h"

//*****************************************************************************
//
//!\page test_di_ad7417arz_register test_di_ad7417arz_register
//!
//!<h2>Description</h2>
//!Test di_ad7417arz register. <br>
//!
//
//*****************************************************************************

//
// Uplimit set value in float
//
static float fUplimit[3] = {-15.5, 20.5, 50};

//
// Uplimit set value in long
//
static long lUplimit[3] = {-15, 20, 50};

//
// Lowlimit set value in float
//
static float fLowlimit[3] = {-15.5, 20.5, 50};

//
// Lowlimit set value in long
//
static long lLowlimit[3] = {-15, 20, 100};

//
// AD Channel select
//
static unsigned long ulADChannel[4] = {AD7417_ADC_Channel1, AD7417_ADC_Channel2,
                                       AD7417_ADC_Channel3, AD7417_ADC_Channel4};

//
// OTI mode set value
//
static unsigned long ulOTIMode[2] = {AD7417_OTI_INT, AD7417_OTI_CMP};

//
// OTI active level set test
//
static unsigned long ulOTIActiveLevel[2] = {AD7417_OTI_ACTIVE_HIGH, 
                                            AD7417_OTI_ACTIVE_LOW};

//
// Fault Queue value set test
//
static unsigned long ulFaultQueue[4] = {AD7417_FAULTQUE_1, AD7417_FAULTQUE_2,
                                        AD7417_FAULTQUE_4, AD7417_FAULTQUE_6};

//*****************************************************************************
//
//! \brief Get the Test description of di_ad7417arz001 register test.
//!
//! \return the desccription of the di_ad7417arz001 test.
//
//*****************************************************************************
static char* di_ad7417arz001GetTest(void)
{
    return "di_ad7417arz [001]: di_ad7417arz register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of di_ad7417arz001 test.
//!
//! \return None.
//
//*****************************************************************************
static void di_ad7417arz001Setup(void)
{
    //
    //Set the external 12MHZ clock as system clock 
    //
    xSysCtlClockSet(12000000, SYSCLK_PWRCON_XTL12M_EN | xSYSCTL_OSC_MAIN);
    
    //
    // AD7417 device init
    //
    AD7417Init(10000, AD7417_ShutDown_Disable | AD7417_Triger_Disable); 
}

//*****************************************************************************
//
//! \brief something should do after the test execute of di_ad7417arz001 test.
//!
//! \return None.
//
//*****************************************************************************
static void di_ad7417arz001TearDown(void)
{
    AD7417Reset();
    AD7417DeInit();
}

//*****************************************************************************
//
//! \brief di_ad7417arz 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void di_ad7417arz001Execute(void)
{
    short ulTemp;
    int i;
    
    //
    // Shutdown mode enable test in init
    //
    AD7417Init(10000, AD7417_ShutDown_Enable);
    ulTemp = AD7417RegRead(AD7417_CFG1) & AD7417_ShutDown_Enable;
    TestAssert(AD7417_ShutDown_Enable == ulTemp,
               "ad7417arz API \" Shutdown mode enable test \" error");
    
    //
    // Shutdown mode disable test in init
    //
    AD7417Init(10000, AD7417_ShutDown_Disable);
    ulTemp = AD7417RegRead(AD7417_CFG1) & AD7417_ShutDown_Enable;
    TestAssert(0 == ulTemp,
               "ad7417arz API \" Shutdown mode disable test \" error");
    
    //
    // Triger mode enable test in init
    //
    AD7417Init(10000, AD7417_Triger_Enable);
    ulTemp = AD7417RegRead(AD7417_CFG2) & AD7417_Triger_Enable;
    TestAssert(AD7417_Triger_Enable == ulTemp,
               "ad7417arz API \" Triger mode enable test \" error");
    
    //
    // Triger mode disable test in init
    //
    AD7417Init(10000, AD7417_Triger_Disable);
    ulTemp = AD7417RegRead(AD7417_CFG2) & AD7417_Triger_Enable;
    TestAssert(0 == ulTemp,
               "ad7417arz API \" Triger mode enable test \" error");    
    
    //
    // Shut down mode enable test
    //
    AD7417ShutdownEnable();
    ulTemp = AD7417RegRead(AD7417_CFG1) & AD7417_ShutDown_Enable;
    TestAssert(AD7417_ShutDown_Enable == ulTemp,
               "ad7417arz API \" Shutdown mode enable test \" error");
    
    //
    // Shut down mode disable test
    //
    AD7417ShutdownDisable();
    ulTemp = AD7417RegRead(AD7417_CFG1) & AD7417_ShutDown_Enable;
    TestAssert(0 == ulTemp,
               "ad7417arz API \" Shutdown mode disable test \" error");
    
    //
    // Trigger mode enable test
    //
    AD7417TriggerEnable();
    ulTemp = AD7417RegRead(AD7417_CFG2) & AD7417_Triger_Enable;
    TestAssert(AD7417_Triger_Enable == ulTemp,
               "ad7417arz API \" Triger mode enable test \" error");    
    
    //
    // Trigger mode disable test
    //
    AD7417TriggerDisable();
    ulTemp = AD7417RegRead(AD7417_CFG2) & AD7417_Triger_Enable;
    TestAssert(0 == ulTemp,
               "ad7417arz API \" Triger mode disable test \" error");    
     
    //
    // OTI compare mode set test
    //
    for(i= 0; i < 2; i++)
    {
        AD7417TempConfig(ulOTIMode[i]);
        ulTemp = AD7417RegRead(AD7417_CFG1) & AD7417_OTI_INT;
        TestAssert(ulOTIMode[i] == ulTemp,
               "ad7417arz API \" OTI compare mode set test \" error");              
    }
    
    //
    // OTI active level set test
    //
    for(i = 0; i < 2; i++)
    { 
        AD7417TempConfig(ulOTIActiveLevel[i]);
        ulTemp = AD7417RegRead(AD7417_CFG1) & AD7417_CFG1_OTIPOLAR_HIGH;
        TestAssert(ulOTIActiveLevel[i] == ulTemp,
               "ad7417arz API \" OTI active level set test \" error");                  
    }
    
    //
    // Temperature channel set test
    //
    AD7417TempConfig(AD7417_TEMP_CHANNEL);
    ulTemp = AD7417RegRead(AD7417_CFG1) & AD7417_CFG1_CHNSEL_M;
    TestAssert(AD7417_TEMP_CHANNEL == ulTemp,
           "ad7417arz API \" Temperature channel set test \" error");   
    
    //
    // ADC channel select test
    //
    for(i = 0; i < 4; i++)
    {
        AD7417ADConfig(ulADChannel[i]);
        ulTemp = AD7417RegRead(AD7417_CFG1) & AD7417_CFG1_CHNSEL_M;
        TestAssert(ulADChannel[i] == ulTemp,
               "ad7417arz API \" ADC channel select test \" error"); 
    }
    
    //
    // Fault Queue value set test
    //
    for(i = 0; i < 4; i++)
    {
        AD7417TempConfig(ulFaultQueue[i]);
        ulTemp = AD7417RegRead(AD7417_CFG1) & AD7417_CFG1_FAULTQUE_M;
        TestAssert(ulFaultQueue[i] == ulTemp,
               "ad7417arz API \" OTI active level set test \" error");          
    }
    
    //
    // Configure the UpLimit register in float 
    //
    for(i = 0; i < 3; i++)
    {
        AD7417UpLimitSetFloat(fUplimit[i]);
        ulTemp = AD7417RegRead(AD7417_TOTI);
        TestAssert(ulTemp == fUplimit[i] * 2,
                   "ad7417arz API \"AD7417UpLimitSetFloat\" error! ");
    }
    
    //
    // Configure the UpLimit register in long 
    //
    for(i = 0; i < 3; i++)
    {
        AD7417UpLimitSetLong(lUplimit[i]);
        ulTemp = AD7417RegRead(AD7417_TOTI);
        TestAssert(ulTemp == lUplimit[i] * 2,
                   "ad7417arz API \"AD7417UpLimitSetFloat\" error! ");
    }
    
    //
    // Configure the UpLimit register in float 
    //
    for(i = 0; i < 3; i++)
    {
        AD7417LowLimitSetFloat(fLowlimit[i]);
        ulTemp = AD7417RegRead(AD7417_THYS);
        TestAssert(ulTemp  == fLowlimit[i] * 2,
                   "ad7417arz API \"AD7417LowLimitSetFloat\" error! ");
    }
    
    //
    // Configure the UpLimit register in long 
    //
    for(i = 0; i < 3; i++)
    {
        AD7417LowLimitSetLong(lLowlimit[i]);
        ulTemp = AD7417RegRead(AD7417_THYS);
        TestAssert(ulTemp == lLowlimit[i] * 2,
                   "ad7417arz API \"AD7417LowLimitSetFloat\" error! ");
    }
    
    //
    // ADC Configure test
    //
    for(i = 0; i < 4; i++)
    {
        AD7417ADConfig(ulADChannel[i]);
        ulTemp = AD7417RegRead(AD7417_CFG1) & AD7417_CFG1_CHNSEL_M;
        TestAssert(ulADChannel[i] == ulTemp,
               "di_ad7417arz API \"AD7417ADConfig\" error!");
    }
     
    
    //
    // I2C filter cofigure
    //
    AD7417I2CFilterConfig(AD7417_FILTER_DISABLE);
    ulTemp = AD7417RegRead(AD7417_CFG2) & AD7417_CFG2_TEST_1;
    TestAssert(AD7417_CFG2_TEST_1 == ulTemp,
           "di_ad7417arz API \"AD7417I2CFilter\" error!");    
}

//
// di_ad7417arz register test case struct.
//
const tTestCase sTestdi_ad7417arz001Register = {
    di_ad7417arz001GetTest,
    di_ad7417arz001Setup,
    di_ad7417arz001TearDown,
    di_ad7417arz001Execute
};

//
// Xi2c test suits.
//
const tTestCase * const psPatternDI_AD7417ARZ001[] =
{
    &sTestdi_ad7417arz001Register,
    0
};

