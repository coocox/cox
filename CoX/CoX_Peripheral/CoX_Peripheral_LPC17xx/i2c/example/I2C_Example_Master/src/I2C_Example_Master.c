/******************************************************************************
 * \file    I2C_Example_Master.c
 * \brief   I2C master example
 * This example shows how to configure I2C into master mode.
 * 
******************************************************************************/
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xdebug.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_i2c.h"
#include "xi2c.h"

#define TICK_SLOW              ((unsigned long)0xFFFFF)

unsigned long Tmp = 0;
unsigned char I2CData[] = {0x00, 0x00, 0x12, 0x34, 0x56};
unsigned char I2CTmp[]  = {0x00, 0x00, 0x00, 0x00, 0x00};

void I2C_Example_Master(void);

void I2C_Example_Master(void)
{ 
    //unsigned long ulTmp = 0;

    /********************** Configure System clock *************************/
    SysCtlClockSet(100000000, SYSCTL_OSC_INT | SYSCTL_XTAL_12_MHZ);
    SysCtlDelay(TICK_SLOW);

    /********************** Configure I2C Port *****************************/
    GPIOPinFunCfg(GPIOA_BASE, GPIO_PIN_19, GPIO_PA19_I2C1SDA);
    GPIOPinFunCfg(GPIOA_BASE, GPIO_PIN_20, GPIO_PA20_I2C1SCK);

    GPIOPinModeCfg(GPIOA_BASE, GPIO_PIN_19, PIN_MODE_OD_EN | PIN_MODE_PULL_UP);
    GPIOPinModeCfg(GPIOA_BASE, GPIO_PIN_20, PIN_MODE_OD_EN | PIN_MODE_PULL_UP);

    // Initialize I2C module clock 100KHz
    I2CMasterInit(I2C1_BASE, 100000);
    I2CEnable(I2C1_BASE);
    I2CIntEnable(I2C1_BASE);

    // Write data to I2C slave
    I2CMasterWriteBufS1(I2C1_BASE, 0xA0, I2CData, sizeof(I2CData), xtrue);
    
    //Slave need time to deal data.
    SysCtlDelay(0xFFFFF);
    I2CMasterWriteS1(I2C1_BASE, 0xA0, 0x00, xfalse);
    I2CMasterWriteS2(I2C1_BASE, 0x00, xfalse);

    // Read data from i2C slave
    I2CTmp[0] = I2CMasterReadRequestS1(I2C1_BASE, 0xA0, xfalse);
    I2CTmp[1] = I2CMasterReadRequestS2(I2C1_BASE, xfalse);
    I2CTmp[2] = I2CMasterReadRequestS2(I2C1_BASE, xfalse);
    I2CTmp[3] = I2CMasterReadRequestS2(I2C1_BASE, xfalse);
    I2CTmp[4] = I2CMasterReadRequestS2(I2C1_BASE, xtrue);

    while (1)
    {
        ; // DoNothing
    }
}

