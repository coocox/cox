#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xcore.h"
#include "xi2c.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xgpio.h"
#include "xhw_ints.h"
#include "MCP98242_3.h"

volatile  unsigned char Event_mode = 0;

volatile  unsigned char Int_Status = 0;

unsigned long test_Sen_Event (void *pvCBData, 
                                   unsigned long ulEvent,
                                   unsigned long ulMsgParam,
                                   void *pvMsgData);

int test_led(void);

//
// Enable I2C, GPIO clock
// Set pins to I2C funciton
//
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

//
// Set MCP98242_3Dev struct:
// 1. I2C Base
// 2. Temperature Sensor Slave Address
// 3. EEPROM Slave Address
// 4. PWP Slave Address
// 5. Event Pin
// 6. Event Interrupt ID
// 7. Function to configure the GPIO Pins. 
//
MCP98242Dev dev = {I2C0_BASE, 0x1C, 0x54, 0x37,xGPIOSPinToPortPin(PB13), 
                        xINT_GPIOB, pinSet};

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
    //
    // Int Mode
    //
    if(Event_mode)
    {
        MCP98242IntClear(&dev);
        Int_Status = 1;
    }
    //
    // Comparator Mode
    //
    else
        test_led();

    return 0;
}

void TempSensor_Event()
{
    unsigned short s;
    float f;   
    
    //
    // Initialize the temperature sensor.
    //  
    MCP98242SensorInit(&dev, 50000);

    //
    // Set RESOLUTION: 0.125¡æ, HYSTERESIS: 0¡æ
    //
    //
    MCP98242Config(&dev, 0, RESOLUTION_125, HYSTERESIS_0);

    for(f=0;f<1000;f++);

    //
    // Set the UPPER temperature.
    //
    f = 27.0;
    MCP98242LimitSet(&dev, &f, T_UPPER);
    for(f=0;f<1000;f++);

    //
    // Set the LOWER temperature.
    //
    f = 25.0;
    MCP98242LimitSet(&dev, &f, T_LOWER);
    for(f=0;f<1000;f++);

    //
    // Set the CRITICAL temperature.
    //
    f = 32.0;
    MCP98242LimitSet(&dev, &f, T_CRITICAL);
    for(f=0;f<1000;f++);

    //
    // Set the Event Output to be Comparator mode.
    //
    Event_mode = EVENT_COMP; 
    //Event_mode = EVENT_INT;   //You can change to Int Mode.
     
    //
    // Configure the Interrupt.
    // 1. Specify the device
    // 2. Initialize the callback funtion
    // 3. Event Alert Polarity: Low Level
    // 4. Event Mode: Comparator
    //               
    MCP98242IntConfig(&dev, test_Sen_Event, EVENT_LOW_LEVEL, Event_mode);
    for(f=0;f<100000;f++);

    //
    // Enable MCP98242_3 Interrupt.
    //
    MCP98242IntEnable(&dev);

    //
    // Configure PA12 for Int Mode, PC12 for Comparator Mode.
    //
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    xGPIODirModeSet(GPIO_PORTA_BASE, GPIO_BIT_12, GPIO_DIR_MODE_OUT);
    xGPIODirModeSet(GPIO_PORTC_BASE, GPIO_BIT_12, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_12, 1);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_12, 1);

    while(1) 
    { 
        //
        // Get Ambient temperature
        //
        MCP98242TempGet(&dev, &f, T_FLOAT);
        for(f=0;f<10000;f++);

        //
        // For Interrupt mode.
        // If the T_A is above the T_UPPER , a interrupt will
        // happen and the Blue LED turns on.
        // If the T_A is below the T_UPPER - T_HYST, a interrupt will
        // happen and the Blue LED turns off. 
        //
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
