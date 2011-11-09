//*****************************************************************************
//
//! \file SlaveReceivePoll.c
//! \brief Slave receive poll mode.
//! \version 1.0
//! \date 8/1/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xdebug.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_uart.h"
#include "xuart.h"
#include "xgpio.h"
#include "xhw_gpio.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xhw_nvic.h"
#include "xhw_i2c.h"
#include "xi2c.h"
#include "xcore.h"

//*****************************************************************************
//
//!
//! i2c transfer and recevice data config
//!
//
//*****************************************************************************
static tI2CSlaveTransferCfg I2CSlaveRcCfg;
static unsigned char ReceiveBuf[11] = "";
static unsigned long ReceiveLength = 10;
static unsigned char SlaveAddress[4] = {0x05, 0x50, 0x7f, 0};

//*****************************************************************************
//
//! The main function of the i2c slave receive with poll mode
//
//! return none
//
//*****************************************************************************
void SlaveMultipleAddress(void)
{
    int i;
    //
    //Set the external 12MHZ clock as system clock 
    //
    SysCtlKeyAddrUnlock();
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
    
    //
    // Congigure the i2c0 pin
    //
    xSPinTypeI2C(I2C0SCK, PA9);
    xSPinTypeI2C(I2C0DATA, PA8);
    
    //
    // Enable the i2c peripheral
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_I2C0);
    
    //
    // Init the I2C as slave 
    //
    xI2CSlaveInit(I2C0_BASE, SlaveAddress[0], I2C_GENERAL_CALL_DIS);
    
    //
    // I2C master transfer config
    //
    I2CSlaveRcCfg.pvWBuf = 0;
    I2CSlaveRcCfg.ulWLen = 0;
    I2CSlaveRcCfg.ulWCount = 0;
    I2CSlaveRcCfg.pvRBuf = ReceiveBuf;
    I2CSlaveRcCfg.ulRLen = ReceiveLength;
    I2CSlaveRcCfg.ulRCount = 0;
   
    //
    // Set multiple slave address
    //
    xI2CSlaveOwnAddressSet(I2C0_BASE, 1, SlaveAddress[1], I2C_GENERAL_CALL_DIS);
    xI2CSlaveOwnAddressSet(I2C0_BASE, 2, SlaveAddress[2], I2C_GENERAL_CALL_DIS);
    xI2CSlaveOwnAddressMaskSet(I2C0_BASE, 2, 0xf0);
    
    for(i = 0; i < 4; i++)
    {
        if(i == 3)
        {
             xI2CSlaveInit(I2C0_BASE, SlaveAddress[i], I2C_GENERAL_CALL_EN);
        }
        //
        // I2C salve receive wiht polling mode
        //
        xI2CSlaveTransfer(I2C0_BASE, &I2CSlaveRcCfg, I2C_TRANSFER_POLLING);
        xSysCtlDelay(100);
    }
}