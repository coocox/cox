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
#include "DS18B20.h"
#include "hw_DS18B20.h"

void Dev1GPIOInit(void);
#define DS18B20_Dev1_DQ         PB15
//
//! \DS18B20 Device.
//
tDS18B20Dev Dev1={
    //
    // DQ is GPIO A.0
    //
    xGPIOSPinToPortPin(DS18B20_Dev1_DQ),
    
    //
    // GPIO A.0 Init
    //
    Dev1GPIOInit,
};


//*****************************************************************************
//
//! \breif DS18B20 Init callback.
//!
//! \return None
//
//*****************************************************************************
void Dev1GPIOInit(void)                                        
{
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(DS18B20_Dev1_DQ));
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
    DS18B20Init(&Dev1);
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
    int i;
    xtBoolean xtTemp;
    float fTemp;
    unsigned char ucROM[8];
    unsigned char ucMem[8];
      
    //
    // test DS18B20Reset.
    //
    xtTemp = DS18B20Reset(&Dev1); 
    //TestAssert(( xtrue == xtTemp), "DS18B20 API error!");
    
    //
    // test DS18B20ROMRead.
    //
    DS18B20Reset(&Dev1);
    DS18B20ROMRead(&Dev1);
    TestAssert(( DS18B20_FAMILY_NUM == Dev1.ucROM[0]), "DS18B20 API error!");
    
    //
    // test DS18B20ROMMatch.
    //
    DS18B20Reset(&Dev1);
    DS18B20ROMMatch(&Dev1);
    DS18B20TempConvert(&Dev1);
    xSysCtlDelay(3000000);
    DS18B20Reset(&Dev1);
    DS18B20ROMMatch(&Dev1);
    DS18B20TempRead(&Dev1, &fTemp);
    TestAssert(( 85 != fTemp), "DS18B20 API error!");  
    
    //
    // test DS18B20ROMSearch.
    //
    DS18B20Reset(&Dev1);
    xtTemp = DS18B20ROMSearch(&Dev1);
    TestAssert(( xtrue == xtTemp), "DS18B20 API error!"); 
    DS18B20Reset(&Dev1);
    DS18B20ROMRead(&Dev1);
    for(i=0; i<8; i++)
    {
        ucROM[i] = Dev1.ucROM[i];
    }
    DS18B20Init(&Dev1);
    DS18B20ROMSearch(&Dev1);
    TestAssert(( ucROM[0] = Dev1.ucROM[0]) &&
               ( ucROM[1] = Dev1.ucROM[1]) &&
               ( ucROM[2] = Dev1.ucROM[2]) &&
               ( ucROM[3] = Dev1.ucROM[3]) &&
               ( ucROM[4] = Dev1.ucROM[4]) &&
               ( ucROM[5] = Dev1.ucROM[5]) &&
               ( ucROM[6] = Dev1.ucROM[6]) &&
               ( ucROM[7] = Dev1.ucROM[7]) 
               , "DS18B20 API error!"); 
    //
    // test DS18B20ScratchpadSet.
    //
    ucMem[0] = 0x55;
    ucMem[1] = 0xFF;
    ucMem[2] = DS18B20_11BIT;
    DS18B20Reset(&Dev1);
    DS18B20ROMMatch(&Dev1);
    DS18B20ScratchpadSet(&Dev1, ucMem[0], ucMem[1], ucMem[2]);
    DS18B20Reset(&Dev1);
    DS18B20ROMMatch(&Dev1);
    DS18B20ScratchpadRead(&Dev1, &ucROM[0]);
    TestAssert(( ucROM[2] = ucMem[0]) &&
               ( ucROM[3] = ucMem[1]) &&
               ( ucROM[4] = ucMem[2]),  
               "DS18B20 API error!");  
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

