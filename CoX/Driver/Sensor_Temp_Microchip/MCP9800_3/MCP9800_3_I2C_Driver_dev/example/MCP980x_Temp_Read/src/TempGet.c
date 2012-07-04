#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xcore.h"
#include "xi2c.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xgpio.h"
#include "xhw_ints.h"
#include "MCP9800_3.h"

volatile  unsigned char Event_mode = 0;

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

MCP9800Dev dev = {I2C0_BASE, 0x48,xGPIOSPinToPortPin(PB13), 
                        xINT_GPIOB, pinSet};

unsigned long test_led()
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


int TempGet()
{
    float f = 0.0;

    //
    // Initialize MCP90x
    //
    MCP980xInit(&dev, 50000);

    //
    // Set the UPPER temperature.
    //
    f = 25.0;
    MCP980xLimitSet(&dev, &f , MCP9800_LIMIT);

    //
    // Set the HYSTERESIS temperature.
    //
    f = 24.5;
    MCP980xLimitSet(&dev, &f , MCP9800_HYSTERESIS);

    //
    // Set RESOLUTION: 0.125¡æ
    //
    MCP980xConfig(&dev, MCP9800_RESOL_125);

    Event_mode = MCP9800_EVENT_COMP; 
    //Event_mode = MCP9800_EVENT_INT;

    //
    // Configure the Interrupt.
    // 1. Specify the device
    // 2. Initialize the callback funtion
    // 3. Event Alert Polarity: Low Level
    // 4. Event Mode: Comparator
    //  
    MCP980xIntConfig(&dev, test_Sen_Event, MCP9800_ALERTPOL_LOW, Event_mode);

    //
    // Configure PC12 for Int Mode, PC13 for Comparator Mode.
    //
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    xGPIODirModeSet(GPIO_PORTC_BASE, GPIO_PIN_12, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_12, 1);
    xGPIODirModeSet(GPIO_PORTC_BASE, GPIO_PIN_13, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_13, 1);

    //
    // Enable Interrupt of GPIO Pin connected with Event Pin.
    //
    xIntEnable(dev.EventIntVec);
    xIntMasterEnable();

    while(1) 
    { 
        if(Event_mode == MCP9800_EVENT_COMP)
            MCP980xTempGet(&dev, &f, MCP_FLOAT);
        for(f=0;f<10000;f++);
    }
}
