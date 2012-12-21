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
#include "PTC08.h"
//*****************************************************************************
//
//!\page Test001 Test001
//!
//!<h2>Description</h2>
//!Test 001. <br>
//!
//
//*****************************************************************************

unsigned char* pucbaudrate[5] ={PTC08_BAUDRATE_9600, PTC08_BAUDRATE_19200,
                                PTC08_BAUDRATE_38400, PTC08_BAUDRATE_57600,
                                PTC08_BAUDRATE_115200};
unsigned long ulPhotoLen = 0;   
unsigned char ucPhotoBuf[20];    
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
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralClockSourceSet(xSYSCTL_UART1_MAIN, 1);
    
    xSPinTypeUART(UART1RX, PA1);                                       
    xSPinTypeUART(UART1TX, PA0);

    xUARTConfigSet(PTC08_UART, 38400, (UART_CONFIG_WLEN_8 | 
                                       UART_CONFIG_STOP_ONE | 
                                       UART_CONFIG_PAR_NONE));

    xUARTEnable(PTC08_UART, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
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
    xtBoolean xtResult;
    int i;
    xtResult = PTC08Init();
    TestAssert( xtResult == xtrue, "PTC08 test error" );
    
    xtResult = PTC08SavePowerSet(PTC08_SAVE_POWER_EN);
    TestAssert( xtResult == xtrue, "PTC08 test error" );
    
    xtResult = PTC08SavePowerSet(PTC08_SAVE_POWER_DIS);
    TestAssert( xtResult == xtrue, "PTC08 test error" );
    
    xtResult = PTC08PhotoSizeSet(PTC08_SIZE_320_240);
    TestAssert( xtResult == xtrue, "PTC08 test error" );
    
    xtResult = PTC08PhotoSizeSet(PTC08_SIZE_640_480);
    TestAssert( xtResult == xtrue, "PTC08 test error" );
    
    for(i = 0;i<256;i++)
    {
        xtResult = PTC08ZipRateSet(i);
        TestAssert( xtResult == xtrue, "PTC08 test error" );
    }
    for(i = 0;i<5;i++)
    {
        xtResult = PTC08BaudRateSet(pucbaudrate[i]);
        TestAssert( xtResult == xtrue, "PTC08 test error" );
    }
     
    xtResult = PTC08PhotoStop();
    TestAssert( xtResult == xtrue, "PTC08 test error" );
    
    xtResult = PTC08PhotoReset();
    TestAssert( xtResult == xtrue, "PTC08 test error" );
    
    xtResult = PTC08PhotoStart();
    TestAssert( xtResult == xtrue, "PTC08 test error" );
    
    xtResult = PTC08PhotoLenGet(&ulPhotoLen);
    TestAssert( xtResult == xtrue, "PTC08 test error" );
    TestAssert( xtResult != 0, "PTC08 test error" );
    
    xtResult = PTC08PhotoDataGet(ucPhotoBuf, 0, 20);
    TestAssert( xtResult == xtrue, "PTC08 test error" );
    TestAssert( ucPhotoBuf[5] == 0xFF && ucPhotoBuf[6] == 0xD8 
               , "PTC08 test error" );
   
    xtResult = PTC08PhotoDataGet(ucPhotoBuf, ulPhotoLen-8, 20);
    TestAssert( xtResult == xtrue, "PTC08 test error" );
    TestAssert( ucPhotoBuf[13] == 0xFF && ucPhotoBuf[14] == 0xD9 
               , "PTC08 test error" );
    
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

