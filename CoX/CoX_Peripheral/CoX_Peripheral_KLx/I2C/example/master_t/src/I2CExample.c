//*****************************************************************************
//
//! \file I2CExample.c
//! \brief I2C example.
//! \version 1.0
//! \date 10/8/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_memmap.h"
#include "xhw_i2c.h"
#include "xi2c.h"

unsigned long ulSlave = I2C1_BASE;
unsigned long ulMaster = I2C0_BASE;
unsigned char ucTempData[5] = "rong";
unsigned char ucTemp[5];
unsigned char ucTempCount = 0;
unsigned char ucTempCount1 = 0;
unsigned long I2CSlaveCallback(void *pvCBData, 
                               unsigned long ulEvent,
                               unsigned long ulMsgParam,
                               void *pvMsgData);


void I2CExample(void)
{
    //
    // Do the main test
    //
    (*((volatile unsigned long *)(0x40048100))) = 0x00;
    
    //
    // Enable the i2c peripheral
    //
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOE);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOC);
    
    //
    // Congigure the i2c pin
    //
    xSPinTypeI2C(I2C0SCK, PC8);
    xSPinTypeI2C(I2C0SDA, PC9);
    
    //
    // Enable the i2c peripheral
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_I2C0);
    
    //
    // Congigure the i2c pin
    //
    xSPinTypeI2C(I2C1SCK, PC1);
    xSPinTypeI2C(I2C1SDA, PC2);
    
    //
    // Enable the i2c peripheral
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_I2C1);
    
    I2CSlaveInit(ulSlave, 0x12, I2C_GENERAL_CALL_EN, I2C_ADDRESS_7BIT);
    I2CEnable(ulSlave);
    I2CIntEnable(ulSlave, I2C_INT_FUNCTION);
    xIntEnable(xSysCtlPeripheraIntNumGet(ulSlave));
    I2CIntCallbackInit(ulSlave, I2CSlaveCallback);
    
    I2CMasterInit(ulMaster, 400000);
    I2CEnable(ulMaster);
    
    xI2CMasterWriteBufS1(ulMaster, 0x12, ucTempData, 4, xfalse);
    
    xI2CMasterReadS1(ulMaster, 0x12, ucTemp, xfalse);    
    xI2CMasterReadS2(ulMaster, &ucTemp[1], xfalse);
    xI2CMasterReadS2(ulMaster, &ucTemp[2], xfalse);
    xI2CMasterReadS2(ulMaster, &ucTemp[3], xtrue);
    
    xI2CMasterReadBufS1(ulMaster, 0x12, ucTemp, 4, xtrue);
    
    xI2CMasterWriteBufS1(ulMaster, 0x12, ucTempData, 4, xfalse);
    xI2CMasterReadBufS1(ulMaster, 0x12, ucTemp, 4, xtrue);
    
    xI2CMasterReadS1(ulMaster, 0x12, ucTemp, xfalse);
    xI2CMasterReadS2(ulMaster, &ucTemp[1], xfalse);
    xI2CMasterReadS2(ulMaster, &ucTemp[2], xfalse);
    xI2CMasterReadS2(ulMaster, &ucTemp[3], xtrue);
    
    while(1)
    {
    }
}

//*****************************************************************************
//
//! \breif i2c slave interrupt install function
//! 
//! \return none
//
//*****************************************************************************
unsigned long I2CSlaveCallback(void *pvCBData, 
                               unsigned long ulEvent,
                               unsigned long ulMsgParam,
                               void *pvMsgData)
{
    if(ulMsgParam == xI2C_SLAVE_EVENT_RREQ)
    {
        ucTempData[ucTempCount] = xI2CSlaveDataGet(ulSlave);
        ucTempCount++;
    }
    else if (ulMsgParam == xI2C_SLAVE_EVENT_TREQ)
    {
        xI2CSlaveDataPut(ulSlave, 'a' + ucTempCount1);
        ucTempCount1++;
        if(ucTempCount1 == 26)
        {
            ucTempCount1 = 0;
        }
    }
    return 0;
}
