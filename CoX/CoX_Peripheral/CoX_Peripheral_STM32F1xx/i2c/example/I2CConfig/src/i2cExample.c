#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xhw_types.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_i2c.h"
#include "xi2c.h"
#include "xhw_dma.h"
#include "xdma.h"

//This Example Show how to use I2C to read ADXL345 3-axis XYZ data
unsigned char RecvBuf[20];

#define I2C_SLAVE_ADDR  0x53

void main(void)
{
    //Set System clock to 72MHz
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    SysCtlDelay(10000);
    xSysCtlPeripheralEnable2(I2C1_BASE);

    xSysCtlPeripheralEnable2(xGPIO_PORTB_BASE);    

    //Map I2C1 Pin
    //SCK --> PB6
    //SDA --> PB7
    xSPinTypeI2C(I2C1SCK, PB6);
    xSPinTypeI2C(I2C1SDA, PB7);    

    //Initialize I2C Module 100K
    I2CInit(I2C1_BASE, 100000);
    I2CEnable(I2C1_BASE);
        
    //Enable ADXL345 Measure Function
    I2CMasterWriteS1(I2C1_BASE, I2C_SLAVE_ADDR, 0x2D, xfalse); 
    I2CMasterWriteS2(I2C1_BASE, 0x08, xtrue);
    
    SysCtlDelay(100000);
    
    //Read Accelerometer XYZ data in continue mode
    I2CMasterWriteS1(I2C1_BASE, I2C_SLAVE_ADDR, 0x32, xfalse);    
    I2CMasterReadBufS1(I2C1_BASE, I2C_SLAVE_ADDR, RecvBuf, 6, xtrue);

    while(1);
}
