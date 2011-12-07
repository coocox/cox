//*****************************************************************************
//
//! @page MCP9804 test
//!  
//! File: @ref xmcp9804test.c
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
//! \file xmcp9804test.c
//! \brief mcp9804 test source file
//
//*****************************************************************************

#include "test.h"
#include "testcase.h"
#include "MCP9804_5.h"

//*****************************************************************************
//
//!\page xMCP9804test xMCP9804test
//!
//!<h2>Description</h2>
//!Test MCP9804 Driver. <br>
//!
//
//*****************************************************************************

volatile  unsigned char Event_mode = 0;

volatile  unsigned char Int_Status = 0;

//
// 0x0004, 0x0000, 0x0080, 0x0000, 0x0040, 0x0000
//
unsigned long ulConfig[] = {MCP_EVENT_SEL_CRIT, MCP_EVENT_SEL_ALL, 
                            MCP_CRIT_LOCK, MCP_CRIT_UNLOCK,
                            MCP_WIN_LOCK, MCP_WIN_UNLOCK};

unsigned long ulConfigTemp[] = {0x0404, 0x0004, 0x8080, 
                                0x8080, 0x4040, 0x4040};

unsigned long ulRes[] = {MCP_RESOLUTION_5, MCP_RESOLUTION_25, MCP_RESOLUTION_125, 
                         MCP_RESOLUTION_0625};

unsigned long ulHys[] = {MCP_HYSTERESIS_6, MCP_HYSTERESIS_1_5, MCP_HYSTERESIS_3,
                         MCP_HYSTERESIS_0};

void TempSensor_RegTest(void);

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

MCP9804Dev dev = {I2C0_BASE, 0x1C, xGPIOSPinToPortPin(PB13), 
                        xINT_GPIOB, pinSet};

//*****************************************************************************
//
//! \brief Get the Test description of XCore001 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* TempSensor_GetTest(void)
{
    return "MCP9804: Temperature Sensor Test.";
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
    MCP9804Init(&dev, 10000);
}

void TempSensor_RegTest()
{
    short s=0;
    float f = 0;
    short config;
    MCP9804_ID id;
    int i;
    
    s = MCP9804CapGet(&dev);
    TestAssert((s&0x07) == 0x07,
             "xuart API \"MCP9804CapSet\" or \"MCP9804CapGet\" error!");  

    //
    // UPPER, LOWER, CRITICAL Limit registers
    //
    f = 24.0;
    MCP9804LimitSet(&dev, &f, MCP_UPPER);
    MCP9804RegGet(&dev, &s, MCP9804_UPPER, I2C_TRANSFER_POLLING);
    TestAssert((s>>4) == 24,
            "xuart API \"MCP9804LimitSet\" or \"MCP9804RegGet\" error!"); 

    f = -8.5;
    MCP9804LimitSet(&dev, &f, MCP_LOWER); 
    MCP9804RegGet(&dev, &s, MCP9804_LOWER, I2C_TRANSFER_POLLING);
    s = s<<3;
    s = s>>3;
    f = s * 0.0625;
    TestAssert((-f-8.5)<0.0001,
            "xuart API \"MCP9804LimitSet\" or \"MCP9804RegGet\" error!");             

    f = 26.0;
    MCP9804LimitSet(&dev, &f, MCP_CRITICAL);
    MCP9804RegGet(&dev, &s, MCP9804_CRITICAL, I2C_TRANSFER_POLLING);
    TestAssert((s>>4) == 26,
            "xuart API \"MCP9804LimitSet\" or \"MCP9804RegGet\" error!"); 
    
    //
    // Event output enable/disable
    //
    MCP9804IntEnable(&dev);
    MCP9804RegGet(&dev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING);
    TestAssert((config & MCP9804_CONF_EN) == MCP9804_CONF_EN,
            "xuart API \"MCP9804IntEnable\" error!"); 

    MCP9804IntDisable(&dev);
    MCP9804RegGet(&dev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING);
    TestAssert((config & MCP9804_CONF_EN) == 0,
            "xuart API \"MCP9804EventDisable\" error!"); 

    //
    // Set Temperatrue Sensor Mode
    //
    MCP9804SHDNEnable(&dev); 
    MCP9804RegGet(&dev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING);    
    TestAssert((config | MCP9804_CONF_SHDN) == MCP9804_CONF_SHDN,
            "xuart API \"MCP9804SHDNEnable\" error!");


    MCP9804SHDNDisable(&dev);     
    MCP9804RegGet(&dev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING);    
    TestAssert((config & MCP9804_CONF_SHDN) == 0,
            "xuart API \"MCP9804SHDNDisable\" error!");

    //
    // Set Resolution of Temperature Sensor
    //
    for(i=0; i<4; i++)
    {
        MCP9804Config(&dev, 0, ulRes[i], MCP_HYSTERESIS_0);
        s = MCP9804CapGet(&dev);
        TestAssert(ulRes[i] == (s>>3),
            "xuart API \"MCP9804Config\" or \"MCP9804CapGet\" error!"); 
    }

    //
    // Set hysteresis
    //
    for(i=0; i<4; i++)
    {
        MCP9804Config(&dev, 0, ulRes[1], ulHys[i]);
        MCP9804RegGet(&dev, &config, MCP9804_CONFIG, I2C_TRANSFER_POLLING);
        TestAssert(ulHys[i] == (MCP_HYSTERESIS_M & config),
            "xuart API \"MCP9804Config\" or \"MCP9804RegGet\" error!"); 
    }
    
    //
    // Get MCP9804 Manufacture ID, Device ID, and Revision
    //
    MCP9804GetID(&dev, &id);
    TestAssert((id.MANU_ID == 0x54) && (id.REVISION == 0) && 
            (id.DEV_ID == 0x00), "xuart API \"MCP9804GetID\" error!");

}

int test_led()
{
    int i;
    for(i=0; i<100000; i++);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_12, 
        !((GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_12) & GPIO_PIN_12)>>12));
    return 0;
}

unsigned long test_Sen_Event (void *pvCBData, 
                                   unsigned long ulEvent,
                                   unsigned long ulMsgParam,
                                   void *pvMsgData)
{
    if(Event_mode)
    {
        MCP9804IntClear(&dev);
        Int_Status = 1;
    }
    else
        test_led();
    return 0;
}


void TempSensor_EventTest(void)
{
    unsigned short s;
    float f;     

    MCP9804Init(&dev, 50000);

    MCP9804Config(&dev, 0, MCP_RESOLUTION_125, MCP_HYSTERESIS_0);

    for(f=0;f<1000;f++);
    f = 27.0;
    MCP9804LimitSet(&dev, &f, MCP_UPPER);
    for(f=0;f<1000;f++);
    f = 15.0;
    MCP9804LimitSet(&dev, &f, MCP_LOWER);
    for(f=0;f<1000;f++);
    f = 32.0;
    MCP9804LimitSet(&dev, &f, MCP_CRITICAL);
    for(f=0;f<1000;f++);

    Event_mode = MCP_EVENT_COMP; 
    //Event_mode = MCP_EVENT_INT;                
    MCP9804IntConfig(&dev, test_Sen_Event, MCP_EVENT_LOW_LEVEL, Event_mode);
    for(f=0;f<100000;f++);
    MCP9804IntEnable(&dev);

    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    xGPIODirModeSet(GPIO_PORTA_BASE, GPIO_BIT_12, GPIO_DIR_MODE_OUT);
    xGPIODirModeSet(GPIO_PORTC_BASE, GPIO_BIT_12, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_12, 1);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_12, 1);

    while(1) 
    { 
        MCP9804TempGet(&dev, &f, MCP_FLOAT);
        for(f=0;f<10000;f++);

        if(Int_Status)
        {
            Int_Status = 0;
            s = MCP9804EvnCondGet(&dev);
            if(s == MCP_EVENT_COND_3)
                GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_12, 0);
            else
                GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_12, 1);
        }
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
// MCP9804 temperature sensor test case struct.
//
const tTestCase TempSensor = {
    TempSensor_GetTest,
    TempSensor_Setup,
    TempSensor_TearDown,
    TempSensor_Execute
};

//
// MCP9804 test suits.
//
const tTestCase * const psPatternXmcp[] =
{
    &TempSensor,
    0
};

