//*****************************************************************************
//
//! @page MCP980x test
//!  
//! File: @ref xmcp980xtest.c
//! 
//! <h2>Description</h2>
//! This module implements the test sequence for the Xcore sub component.<br><br>
//! - \p Board: NUC140 <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the VCOM UART. <br><br>
//! .
//! 
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define: 
//! <br>(1)None.<br><br>
//! - \p Option-hardware: 
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:
//! <br>None.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//! 
//! \file xMCP980xtest.c
//! \brief MCP980x test source file
//
//*****************************************************************************

#include "test.h"
#include "testcase.h"
#include "MCP9800_3.h"

//*****************************************************************************
//
//!\page xmcp980xtest
//!
//!<h2>Description</h2>
//!Test MCP980x Driver. <br>
//!
//
//*****************************************************************************

volatile  unsigned char Event_mode = 0;

char cResol[4] = {MCP9800_RESOL_5, MCP9800_RESOL_25, MCP9800_RESOL_125, MCP9800_RESOL_0625};
char cFaulque[4] = {MCP9800_FAULTQUE_1, MCP9800_FAULTQUE_2, MCP9800_FAULTQUE_4, MCP9800_FAULTQUE_6};

void TempSensor_RegTest(void);

void test_GPIOInit(void);

unsigned long test_Sen_Event (void *pvCBData, 
                                   unsigned long ulEvent,
                                   unsigned long ulMsgParam,
                                   void *pvMsgData);

int test_led(void);

void TempSensor_EventTest(void);

void pinSet()
{
    //
    // Enable GPIO Clock
    //
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(PA8));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(PA9));

    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(PB13));

    xSPinTypeI2C(I2C0SDA, PA8);
    xSPinTypeI2C(I2C0SCK, PA9);
}

MCP9800Dev dev = {I2C0_BASE, 0x48, xGPIOSPinToPortPin(PB13), 
                        xINT_GPIOB, pinSet};

//*****************************************************************************
//
//! \brief Get the Test description of MCP9800 test.
//!                                     
//! \return the desccription of the MCP9800 test.
//
//*****************************************************************************
static char* TempSensor_GetTest(void)
{
    return "MCP9800: Temperature Sensor Test.";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xcore001 test.
//!
//! \return None.
//
//*****************************************************************************
static void TempSensor_Setup()
{
    MCP980xInit(&dev, 50000);
}

void TempSensor_RegTest()
{
    char cTemp;
    int i;

    //
    // shut down mode test
    //    
    MCP980xModeSet(&dev, MCP9800_SHDN);
    MCP980xRegGet(&dev, &cTemp, MCP9800_CONFIG, 0);
    TestAssert((cTemp & 0x01) == 1,
       "MCP9800 API \"MCP980xModeSet\" error!");

    //
    // one-shot mode test
    //
    MCP980xModeSet(&dev, MCP9800_ONESHOT);
    MCP980xRegGet(&dev, &cTemp, MCP9800_CONFIG, 0);
    TestAssert((cTemp & 0x81) == 0x81,
       "MCP9800 API \"MCP980xModeSet\" error!");

    //
    // continuous mode test
    //
    MCP980xModeSet(&dev, MCP9800_CONTI);
    MCP980xRegGet(&dev, &cTemp, MCP9800_CONFIG, 0);
    TestAssert((cTemp & 0x01) == 0,
       "MCP9800 API \"MCP980xModeSet\" error!");

    //
    // MCP9800_RESOL test
    //
    for(i=0; i<4; i++)
    {
        MCP980xConfig(&dev, cResol[i]);
        MCP980xRegGet(&dev, &cTemp, MCP9800_CONFIG, 0);
        TestAssert((cTemp & MCP9800_RESOL_M) == cResol[i],
           "MCP9800 API \"MCP980xConfig\" error!");
    }

    //
    // Fault Queue test
    //
    for(i=0; i<4; i++)
    {
        MCP980xConfig(&dev, cFaulque[i]);
        MCP980xRegGet(&dev, &cTemp, MCP9800_CONFIG, 0);
        TestAssert((cTemp & MCP9800_FAULTQUE_M) == cFaulque[i],
           "MCP9800 API \"MCP980xConfig\" error!");
    }

}

int test_led()
{
    int i;
    for(i=0; i<10000; i++);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_12, 
        !((GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_12) & GPIO_PIN_12)>>12));
    return 0;
}

unsigned long test_Sen_Event (void *pvCBData, 
                                   unsigned long ulEvent,
                                   unsigned long ulMsgParam,
                                   void *pvMsgData)
{
    if(Event_mode == MCP9800_EVENT_INT)
    {
        MCP980xIntClear(&dev);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_13, 
                !((GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_13) & GPIO_PIN_13)>>13));
    }
    else
        test_led();
    return 0;
}


void TempSensor_EventTest(void)
{
    float f;     

    //
    // Initialize the temperature sensor.
    //
    MCP980xInit(&dev, 50000);

    f = 27.0;
    MCP980xLimitSet(&dev, &f , MCP9800_LIMIT);

    f = 26.5;
    MCP980xLimitSet(&dev, &f , MCP9800_HYSTERESIS);

    
    Event_mode = MCP9800_EVENT_COMP; 
    //Event_mode = MCP9800_EVENT_INT;                
    MCP980xIntConfig(&dev, test_Sen_Event, MCP9800_ALERTPOL_LOW, Event_mode);

    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    xGPIODirModeSet(GPIO_PORTC_BASE, GPIO_PIN_12, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_12, 1);
    xGPIODirModeSet(GPIO_PORTC_BASE, GPIO_PIN_13, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_13, 1);

    xIntEnable(dev.EventIntVec);
    xIntMasterEnable();

    while(1) 
    { 
        if(Event_mode == MCP9800_EVENT_COMP)
            MCP980xTempGet(&dev, &f, MCP_FLOAT);
        for(f=0;f<10000;f++);
    }    
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xcore001 test.
//!
//! \return None.
//
//*****************************************************************************
static void TempSensor_TearDown(void)
{
    MCP980xDeInit(&dev);
}

//*****************************************************************************
//
//! \brief xcore001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void TempSensor_Execute(void)
{
    //
    // Registers write and read test.
    //
	//TempSensor_RegTest();

    //
    // Event output test in compare mode
    //
    TempSensor_EventTest();
    
}

//
// MCP9800 temperature sensor test case struct.
//
const tTestCase TempSensor = {
    TempSensor_GetTest,
    TempSensor_Setup,
    TempSensor_TearDown,
    TempSensor_Execute
};

//
// MCP9800 test suits.
//
const tTestCase * const psPatternXmcp[] =
{
    &TempSensor,
    0
};

