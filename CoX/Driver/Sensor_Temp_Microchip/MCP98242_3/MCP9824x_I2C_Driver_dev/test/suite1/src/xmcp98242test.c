//*****************************************************************************
//
//! @page mcp98242 test
//!  
//! File: @ref xmcp98242test.c
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
//! \file xmcp98242test.c
//! \brief mcp98242 test source file
//! \file xmcp98242test.h
//! \brief mcp98242 test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "testcase.h"
#include "MCP98242_3.h"

//*****************************************************************************
//
//!\page xmcp98242test xmcp98242test
//!
//!<h2>Description</h2>
//!Test MCP98242 Driver. <br>
//!
//
//*****************************************************************************

volatile  unsigned char Event_mode = 0;

volatile  unsigned char Int_Status = 0;

//
// 0x0004, 0x0000, 0x0080, 0x0000, 0x0040, 0x0000
//
unsigned long ulConfig[] = {EVENT_SEL_CRIT, EVENT_SEL_ALL, 
                            CRIT_LOCK, CRIT_UNLOCK,
                            WIN_LOCK, WIN_UNLOCK};

unsigned long ulConfigTemp[] = {0x0404, 0x0004, 0x8080, 
                                0x8080, 0x4040, 0x4040};

unsigned long ulRes[] = {RESOLUTION_5, RESOLUTION_25, RESOLUTION_125, 
                         RESOLUTION_0625};

unsigned long ulHys[] = {HYSTERESIS_6, HYSTERESIS_1_5, HYSTERESIS_3,
                         HYSTERESIS_0};

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

MCP98242Dev dev = {I2C0_BASE, 0x1C, 0x54, 0x37,xGPIOSPinToPortPin(PB13), 
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
    return "MCP98242: Temperature Sensor Test.";
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
    MCP98242SensorInit(&dev, 10000);
}

void TempSensor_RegTest()
{
    short s=0;
    float f = 0;
    short config;
    MCP98242_ID id;
    int i;
    
    s = MCP98242CapGet(&dev);
    TestAssert((s&0x07) == 0x07,
             "xuart API \"MCP98242CapSet\" or \"MCP98242CapGet\" error!");  

    //
    // UPPER, LOWER, CRITICAL Limit registers
    //
    f = 24.0;
    MCP98242LimitSet(&dev, &f, T_UPPER);
    MCP98242RegGet(&dev, &s, MCP98242_UPPER, I2C_TRANSFER_POLLING);
    TestAssert((s>>4) == 24,
            "xuart API \"MCP98242LimitSet\" or \"MCP98242RegGet\" error!"); 

    f = -8.5;
    MCP98242LimitSet(&dev, &f, T_LOWER); 
    MCP98242RegGet(&dev, &s, MCP98242_LOWER, I2C_TRANSFER_POLLING);
    s = s<<3;
    s = s>>3;
    f = s * 0.0625;
    TestAssert((-f-8.5)<0.0001,
            "xuart API \"MCP98242LimitSet\" or \"MCP98242RegGet\" error!");             

    f = 26.0;
    MCP98242LimitSet(&dev, &f, T_CRITICAL);
    MCP98242RegGet(&dev, &s, MCP98242_CRITICAL, I2C_TRANSFER_POLLING);
    TestAssert((s>>4) == 26,
            "xuart API \"MCP98242LimitSet\" or \"MCP98242RegGet\" error!"); 
    
    //
    // Event output enable/disable
    //
    MCP98242IntEnable(&dev);
    MCP98242RegGet(&dev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING);
    TestAssert((config & MCP98242_CONF_EN) == MCP98242_CONF_EN,
            "xuart API \"MCP98242IntEnable\" error!"); 

    MCP98242IntDisable(&dev);
    MCP98242RegGet(&dev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING);
    TestAssert((config & MCP98242_CONF_EN) == 0,
            "xuart API \"MCP98242EventDisable\" error!"); 

    //
    // Set Temperatrue Sensor Mode
    //
    MCP98242SHDNEnable(&dev); 
    MCP98242RegGet(&dev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING);    
    TestAssert((config | MCP98242_CONF_SHDN) == MCP98242_CONF_SHDN,
            "xuart API \"MCP98242SHDNEnable\" error!");


    MCP98242SHDNDisable(&dev);     
    MCP98242RegGet(&dev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING);    
    TestAssert((config & MCP98242_CONF_SHDN) == 0,
            "xuart API \"MCP98242SHDNDisable\" error!");

    //
    // Set Resolution of Temperature Sensor
    //
    for(i=0; i<4; i++)
    {
        MCP98242Config(&dev, 0, ulRes[i], HYSTERESIS_0);
        s = MCP98242CapGet(&dev);
        TestAssert(ulRes[i] == (s>>3),
            "xuart API \"MCP98242Config\" or \"MCP98242CapGet\" error!"); 
    }

    //
    // Set hysteresis
    //
    for(i=0; i<4; i++)
    {
        MCP98242Config(&dev, 0, ulRes[1], ulHys[i]);
        MCP98242RegGet(&dev, &config, MCP98242_CONFIG, I2C_TRANSFER_POLLING);
        TestAssert(ulHys[i] == (HYSTERESIS_M & config),
            "xuart API \"MCP98242Config\" or \"MCP98242RegGet\" error!"); 
    }
    
    //
    // Get MCP98242 Manufacture ID, Device ID, and Revision
    //
    MCP98242GetID(&dev, &id);
    TestAssert((id.MANU_ID == 0x54) && (id.REVISION == 0) && 
            (id.DEV_ID == 0x20), "xuart API \"MCP98242GetID\" error!");

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
        MCP98242IntClear(&dev);
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

    MCP98242SensorInit(&dev, 50000);

    MCP98242Config(&dev, 0, RESOLUTION_125, HYSTERESIS_0);

    for(f=0;f<1000;f++);
    f = 27.0;
    MCP98242LimitSet(&dev, &f, T_UPPER);
    for(f=0;f<1000;f++);
    f = 25.0;
    MCP98242LimitSet(&dev, &f, T_LOWER);
    for(f=0;f<1000;f++);
    f = 32.0;
    MCP98242LimitSet(&dev, &f, T_CRITICAL);
    for(f=0;f<1000;f++);

    Event_mode = EVENT_COMP; 
    //Event_mode = EVENT_INT;                
    MCP98242IntConfig(&dev, test_Sen_Event, EVENT_LOW_LEVEL, Event_mode);
    for(f=0;f<100000;f++);
    MCP98242IntEnable(&dev);

    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    xGPIODirModeSet(GPIO_PORTA_BASE, GPIO_BIT_12, GPIO_DIR_MODE_OUT);
    xGPIODirModeSet(GPIO_PORTC_BASE, GPIO_BIT_12, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_12, 1);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_12, 1);

    while(1) 
    { 
        MCP98242TempGet(&dev, &f, T_FLOAT);
        for(f=0;f<10000;f++);

        if(Int_Status)
        {
            Int_Status = 0;
            s = MCP98242EvnCondGet(&dev);
            if(s == EVENT_COND_3)
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
	TempSensor_RegTest();

    //
    // Event output test in compare mode
    //
    //TempSensor_EventTest();
    
}

//
// mcp98242 temperature sensor test case struct.
//
const tTestCase TempSensor = {
    TempSensor_GetTest,
    TempSensor_Setup,
    TempSensor_TearDown,
    TempSensor_Execute
};


//*****************************************************************************
//
//! \brief Get the Test description of XCore001 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* MemWR_GetTest(void)
{
    return "MCP98242: EEPROM Test.";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xcore001 test.
//!
//! \return None.
//
//*****************************************************************************
static void MemWR_Setup(void)
{
    MCP98242EEPROMInit(&dev, 80000);
}

//*****************************************************************************
//
//! \brief xcore001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void MemWR_Execute(void)
{
    unsigned char multWrite[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    unsigned char page_addr_data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
                                        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    unsigned char addr, *value;
    int i;

    
    addr = 0xA0;
    value = multWrite;
    for(i=0; i<8; i++, addr++)
    {
        MCP98242ByteWrite(&dev, addr, multWrite[i]);
        xSysCtlDelay(10000);
    }

    addr = 0xA0;
    value[0]=value[1]=value[2]=0x55;
    SysCtlDelay(10000);
    MCP98242MemRead(&dev, addr, value, sizeof(multWrite));
    TestAssert(multWrite[2] == 0x02, 
         "xuart API \"MCP98242MutiByteWrite\" or \"MCP98242MemRead\" error!");
    
    SysCtlDelay(10000);
    addr = 0xB0;
    value = page_addr_data;
    MCP98242PageWrite(&dev, addr, value);

    value[0]=value[1]=value[2]=value[15]=value[14]=value[13]=0x55;
    SysCtlDelay(50000);
    MCP98242MemRead(&dev, addr, value, sizeof(page_addr_data));
    TestAssert(page_addr_data[13] == 0x0D, 
         "xuart API \"MCP98242PageWrite\" or \"MCP98242MemRead\" error!");

    value[0]=value[1]=value[2]=value[13]=value[14]=0x55;
    
    //
    // Sequential Read Test
    //
    MCP98242MemRead(&dev, addr, value, 15);
    TestAssert(page_addr_data[13] == 0x0D, 
         "xuart API \"MCP98242PageWrite\" or \"MCP98242MemRead\" error!");

    //
    // Current Address Read.
    //
    MCP98242MemRead(&dev, 0, value, 0);
    TestAssert(*value == 0x0F, 
         "xuart API \"MCP98242PageWrite\" or \"MCP98242MemRead\" error!");
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xcore001 test.
//!
//! \return None.
//
//*****************************************************************************
static void MemWR_TearDown(void)
{

}

//
// mcp98242 EEPROM test case struct.
//
const tTestCase MemWR = {
    MemWR_GetTest,
    MemWR_Setup,
    MemWR_TearDown,
    MemWR_Execute
};

//
// mcp98242 test suits.
//
const tTestCase * const psPatternXmcp[] =
{
    &TempSensor,
    &MemWR,
    0
};

