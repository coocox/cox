//*****************************************************************************
//
//! @page xi2c_testcase xi2c register test
//!
//! File: @ref xi2ctest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the lcd sub component.<br><br>
//! - xx
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
//! - \subpage Test001
//! .
//
//*****************************************************************************

#include "test.h"
#include "STLM75.h"
#include "hw_STLM75.h"

//
//! STLM75 Init callback.
//
void Dev1GPIOInit(void);

//
//! STLM75 Device' OS/INT pin callback.
//
unsigned long UserCallback(void *pvCBData, unsigned long ulEvent, 
                           unsigned long ulMsgParam, void *pvMsgData);

//
//! Redefined the STLM75 Device's I2C pins.
//
#define STLM75_Dev1_SDA         PA8
#define STLM75_Dev1_SCK         PA9

//
//! STLM75 Device.
//
tSTLM75Dev Dev1={
    //
    // DQ is GPIO 
    //
    xGPIOSPinToPortPin(STLM75_Dev1_SCK),
    xGPIOSPinToPortPin(STLM75_Dev1_SDA),
    xGPIOSPinToPortPin(PA0),
    xI2C0_BASE,
    
    //
    // GPIO A.0 Init
    //
    Dev1GPIOInit,
    UserCallback,
    STLM75_ADDRESS_MASK,
};

//
// STLM75 Config value
//
static unsigned long ulConfig[7] = {0x00,0x01,0x02,0x00,0x08,0x10,0x18};

//
// STLM75 Thys value
//
static float fThys[4] = {74.0,74.5,75.5,75.0};

//
// STLM75 Tos value
//
static float fTos[4] = {79.0,79.5,80.5,80.0};

//*****************************************************************************
//
//! \breif STLM75 Init callback.
//!
//! \return None
//
//*****************************************************************************
void Dev1GPIOInit(void)                                        
{
    //
    // Congigure the i2c pin
    //
    xSPinTypeI2C(I2C0SCL, STLM75_Dev1_SCK);
    xSPinTypeI2C(I2C0DATA, STLM75_Dev1_SDA); 
}
//*****************************************************************************
//! \breif GPIO External interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long UserCallback(void *pvCBData, unsigned long ulEvent, 
                           unsigned long ulMsgParam, void *pvMsgData)                                        
{
    float fTemp,fTos,fThys;
    fTemp = STLM75TempRead(&Dev1);
    fTos = STLM75LimitRead(&Dev1, 1);
    fThys = STLM75LimitRead(&Dev1, 0);

    if(fTemp > fTos)
    {
        TestEmitToken('a');
        
        //
        // Other user code
        //
    }
    else if(fTemp < fThys)
    {
        TestEmitToken('b');
        
        //
        // Other user code
        //
    } 
    
    return 0;
}

//*****************************************************************************
//
//!\page Test001 Test001
//!
//!<h2>Description</h2>
//!Test 001. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Get the Test description of the test.
//!
//! \return the desccription of the test.
//
//*****************************************************************************
static char* Test001GetTest(void)
{
    return "Test [001]: ";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of the test.
//!
//! \return None.
//
//*****************************************************************************
static void Test001Setup(void)
{
    STLM75Init(&Dev1, 100000);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of the test.
//!
//! \return None.
//
//*****************************************************************************
static void Test001TearDown(void)
{
    
}

//*****************************************************************************
//
//! \brief 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void Test001Execute(void)
{
    float fTemp;
    unsigned char ucvalue;
    int i;
    for(i=0; i<7; i++)
    {
        STLM75ConfigSet(&Dev1, ulConfig[i]);
        ucvalue = STLM75ConfigRead(&Dev1);
        TestAssert((ucvalue == ulConfig[i]), 
                   "test1, \" STLM75ConfigSet or STLM75ConfigRead()\" error");
    }
    
    for(i=0; i<4; i++)
    {
        STLM75LimitSet(&Dev1, fThys[i], 0);
        fTemp = STLM75LimitRead(&Dev1, 0);
        TestAssert((fTemp == fThys[i]), 
                   "test1, \" STLM75LimitSet or STLM75LimitRead()\" error");
    }
    for(i=0; i<4; i++)
    {
        STLM75LimitSet(&Dev1, fTos[i], 1);
        fTemp = STLM75LimitRead(&Dev1, 1);
        TestAssert((fTemp == fTos[i]), 
                   "test1, \" STLM75LimitSet or STLM75LimitRead()\" error");
    }
    fTemp = STLM75TempRead(&Dev1);
    TestAssert((fTemp >= 10 && fTemp <= 30), 
               "test1, \" STLM75LimitSet or STLM75LimitRead()\" error");
    
    STLM75Init(&Dev1, 100000);
    
    STLM75ConfigSet(&Dev1, STLM75_CFG_SHUTDOWN_OFF | STLM75_CFG_MODE_INT |
                           STLM75_CFG_POL_LOW | STLM75_CFG_FT1);
    STLM75LimitSet(&Dev1, 25, 0);
    STLM75LimitSet(&Dev1, 27, 1);
    SysCtlDelay(100000);  
    TestAssertQBreak("ab", "STLM75 interrupt teset fail", (unsigned long)-1); 
}
//
// test case 001 struct.
//
const tTestCase sTest001 = {
        Test001GetTest,
        Test001Setup,
        Test001TearDown,
        Test001Execute
};

//
// Xi2c test suits.
//
const tTestCase * const psPattern001[] =
{
    &sTest001,
    0
};

