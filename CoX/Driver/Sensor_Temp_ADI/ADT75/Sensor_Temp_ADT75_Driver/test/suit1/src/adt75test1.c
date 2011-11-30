//*****************************************************************************
//
//! @page di_adt75_testcase di_adt75 register test
//!
//! File: @ref ADT75test1.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the di_adt75 sub component.<br><br>
//! - \p Board: NUC140 & ADT75ARZ board <br><br>
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
//! - \subpage test_adt75_register
//! .
//! \file ADT75test1.c
//! \brief adt75 test source file
//! \brief adt75 test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_adt75.h"
#include "adt75.h"

//*****************************************************************************
//
//!\page test_di_adt75_register test_di_adt75_register
//!
//!<h2>Description</h2>
//!Test di_adt75 register. <br>
//!
//
//*****************************************************************************

//
// Register read write value
//
static long ulRegisterValue[2] = {10, -10};

//
// Power mode set value
//
static unsigned long ulPowerMode[2] = {ADT75_POWER_SHOTDOWN, ADT75_POWER_NORMAL};

//
// Int mode set value
//
static unsigned long ulIntMode[2] = {ADT75_OPEMODE_CMP, ADT75_OPEMODE_INT};

//
// OS level set value
//
static unsigned long ulOSLevel[2] = {ADT75_OSALERT_LEVEL_LOW, ADT75_OSALERT_LEVEL_HIGH};

//
// Fault Queue set value
//
static unsigned long ulFaultQueue[4] = {ADT75_FAULTQUE_1,
                                        ADT75_FAULTQUE_2,
                                        ADT75_FAULTQUE_4,
                                        ADT75_FAULTQUE_6};
//
// Alert configure value
//
static unsigned long ulAlertConfig[2] = {ADT75_ALERT_ENABLE, ADT75_ALERT_DISABLE};

//
// Up limit set data in float
//
static float fUpLimit[3] = {-10.5, 0, 20.5};

//
// Up limit set data in long
//
static long lUpLimit[3] = {-10, 0, 20};

//
// Low limit set data in float
//
static float fLowLimit[3] = {-10.5, 0, 20.5};

//
// Low limit set data in long
//
static long lLowLimit[3] = {-10, 0, 20};

//*****************************************************************************
//
//! \brief Get the Test description of di_adt75001 register test.
//!
//! \return the desccription of the di_adt75001 test.
//
//*****************************************************************************
static char* adt75001GetTest(void)
{
    return "di_adt75 [001]: adt75 register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of di_adt75001 test.
//!
//! \return None.
//
//*****************************************************************************
static void adt75001Setup(void)
{
    //
    //Set the external 12MHZ clock as system clock 
    //
	xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
    
    ADT75Init(500, ADT75_POWER_SHOTDOWN); 
    
}

//*****************************************************************************
//
//! \brief something should do after the test execute of di_adt75001 test.
//!
//! \return None.
//
//*****************************************************************************
static void adt75001TearDown(void)
{
    ADT75DeInit();
}

//*****************************************************************************
//
//! \brief adt75 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void adt75001Execute(void)
{
    long lTemp;
    float fTemp; 
    unsigned long i;
    
    //
    // Test register read and write function
    //
    for(i = 0; i < 2; i++)
    {
        ADT75RegWrite(ADT75_REGISTER_THYS, ulRegisterValue[i]);
        lTemp = ADT75RegRead(ADT75_REGISTER_THYS);
        TestAssert(ulRegisterValue[i] == lTemp,
               "adt75 API \"ADT75RegWrite(),ADT75RegRead() \" error! ");
    }
    
    //
    // Init function power mode set test
    //
    for(i = 0; i < 2; i++)
    {
        ADT75Init(100000, ulPowerMode[i]);
        lTemp = ADT75RegRead(ADT75_REGISTER_CFG) & ADT75_CFG_POWER_SHOTDOWN;
        TestAssert(ulPowerMode[i] == lTemp,
               "adt75 API \"ADT75Init power config\" error! "); 
    }
    
    //
    // Int mode configure test
    //
    for(i = 0; i < 2; i++)
    {
        ADT75IntModeConfig(ulIntMode[i]);
        lTemp = ADT75RegRead(ADT75_REGISTER_CFG) & ADT75_CFG_OPEMODE_INT;
        TestAssert(ulIntMode[i] == lTemp,
               "adt75 API \"ADT75IntModeConfig()\" error! ");         
    }
    
    //
    // OS level set test
    //
    for(i = 0; i < 2; i++)
    {
        ADT75OSActiveLevelConfig(ulOSLevel[i]);
        lTemp = ADT75RegRead(ADT75_REGISTER_CFG) & ADT75_CFG_OSALERT_HIGH;
        TestAssert(ulOSLevel[i] == lTemp,
               "adt75 API \"ADT75OSActiveLevelConfig()\" error! ");  
    }
    
    //
    // Fault Queue set test
    //
    for(i = 0; i < 4; i++)
    {
        ADT75FaultQueueConfig(ulFaultQueue[i]);
        lTemp = ADT75RegRead(ADT75_REGISTER_CFG) & ADT75_CFG_FAULTQUE_MASK;
        TestAssert(ulFaultQueue[i] == lTemp,
               "adt75 API \"ADT75FaultQueueConfig()\" error! ");  
    }
    
    //
    // Shut down set test
    //
    ADT75ShutDown();
    lTemp = ADT75RegRead(ADT75_REGISTER_CFG) & ADT75_CFG_POWER_SHOTDOWN;
    TestAssert(ADT75_POWER_SHOTDOWN == lTemp,
           "adt75 API \"ADT75ShutDown()\" error! "); 
    
    //
    // Wake up set test
    //
    ADT75WakeUp();
    lTemp = ADT75RegRead(ADT75_REGISTER_CFG) & ADT75_CFG_POWER_SHOTDOWN;
    TestAssert(ADT75_POWER_NORMAL == lTemp,
           "adt75 API \"ADT75WakeUp()\" error! "); 
    
    //
    // Alert configure test
    //
    for(i = 0; i < 2; i++)
    {
        ADT75AlertConfig(ulAlertConfig[i]);
        lTemp = ADT75RegRead(ADT75_REGISTER_CFG) & ADT75_CFG_ALERT_ENABLE;
        TestAssert(ulAlertConfig[i] == lTemp,
               "adt75 API \"ADT75AlertConfig()\" error! "); 
    }
    
    //
    // One shot mode enable test
    //
    ADT75OneShotEnable();
    lTemp = ADT75RegRead(ADT75_REGISTER_CFG) & ADT75_CFG_MODE_ONTSHOT;
    TestAssert(ADT75_CFG_MODE_ONTSHOT == lTemp,
           "adt75 API \"ADT75OneShotEnable()\" error! "); 
    
    //
    // One shot mode disable test
    //
    ADT75OneShotDisable();
    lTemp = ADT75RegRead(ADT75_REGISTER_CFG) & ADT75_CFG_MODE_ONTSHOT;
    TestAssert(0 == lTemp,
           "adt75 API \"ADT75OneShotDisable()\" error! "); 
   
    //
    // Up limit set in float test
    //
    for(i = 0; i < 3; i++)
    {
        ADT75UpLimitSetFloat(fUpLimit[i]);
        fTemp = ADT75RegRead(ADT75_REGISTER_TOS) * 0.0625;
        TestAssert(fUpLimit[i] == fTemp,
               "adt75 API \"ADT75UpLimitSetFloat()\" error! "); 
    }
    
    //
    // Up limit set in long test
    //
    for(i = 0; i < 3; i++)
    {
        ADT75UpLimitSetLong(lUpLimit[i]);
        lTemp = ADT75RegRead(ADT75_REGISTER_TOS) * 0.0625;
        TestAssert(lUpLimit[i] == lTemp,
               "adt75 API \"ADT75UpLimitSetFloat()\" error! "); 
    }
    
    //
    // Low limit set in float test
    //
    for(i = 0; i < 3; i++)
    {
        ADT75LowLimitSetFloat(fLowLimit[i]);
        fTemp = ADT75RegRead(ADT75_REGISTER_THYS) * 0.0625;
        TestAssert(fLowLimit[i] == fTemp,
               "adt75 API \"ADT75LowLimitSetFloat()\" error! "); 
    }

    //
    // Low limit set in long test
    //
    for(i = 0; i < 3; i++)
    {
        ADT75LowLimitSetLong(lLowLimit[i]);
        lTemp = ADT75RegRead(ADT75_REGISTER_THYS) * 0.0625;
        TestAssert(lLowLimit[i] == lTemp,
               "adt75 API \"ADT75LowLimitSetLong()\" error! "); 
    }
}

//
// di_adt75 register test case struct.
//
const tTestCase sTest_adt75001Register = {
    adt75001GetTest,
    adt75001Setup,
    adt75001TearDown,
    adt75001Execute
};

//
// Xi2c test suits.
//
const tTestCase * const psPatternDI_ADT75001[] =
{
    &sTest_adt75001Register,
    0
};

