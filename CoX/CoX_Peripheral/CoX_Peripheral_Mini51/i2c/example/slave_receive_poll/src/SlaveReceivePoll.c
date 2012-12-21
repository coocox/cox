//*****************************************************************************
//
//! \file SlaveReceivePoll.c
//! \brief Slave receive poll mode.
//! \version 1.0
//! \date 2/18/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xgpio.h"
#include "xsysctl.h"
#include "xi2c.h"

//*****************************************************************************
//
//! i2c transfer and recevice data configure
//
//*****************************************************************************
static tI2CSlaveTransferCfg I2CSlaveRcCfg;
static unsigned char ReceiveBuf[11] = "";
static unsigned long ReceiveLength = 10;
static unsigned char SlaveAddress = 0x05;

static unsigned char WriteBuf[] = "helloi2c";
static unsigned long WriteLength = 9;
  
//*****************************************************************************
//
//! Declaration  functions
//
//*****************************************************************************
void Print(char *pcMsg);
unsigned long SlavaRecvFunc(void *pvCBData, 
                                   unsigned long ulEvent,
                                   unsigned long ulMsgParam,
                                   void *pvMsgData);

//*****************************************************************************
//
//! The function is to set the i2c slave receive with poll mode
//
//! return none
//
//*****************************************************************************
void SlaveReceivePoll(void)
{
    //
    // Set system clock 
    //
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
    
    //
    // Congigure the i2c pin
    //
    xSPinTypeI2C(I2C0SCK, PD5);
    xSPinTypeI2C(I2C0SDA, PD4);
    
    //
    // Enable the i2c peripheral
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_I2C0);
    
    //
    // Init the I2C as slave 
    //
    xI2CSlaveInit(I2C0_BASE, SlaveAddress, I2C_GENERAL_CALL_DIS);
    
    WriteBuf[8] = '\0';
    
    //
    // I2C master transfer config
    //
    I2CSlaveRcCfg.pvWBuf = WriteBuf;
    I2CSlaveRcCfg.ulWLen = WriteLength;
    I2CSlaveRcCfg.ulWCount = 0;
    I2CSlaveRcCfg.pvRBuf = ReceiveBuf;
    I2CSlaveRcCfg.ulRLen = ReceiveLength;
    I2CSlaveRcCfg.ulRCount = 0;
    
    xI2CIntCallbackInit(I2C0_BASE, SlavaRecvFunc);
    
    //
    // I2C salve receive wiht polling mode
    //
    xI2CSlaveTransfer(I2C0_BASE, &I2CSlaveRcCfg, xI2C_TRANSFER_POLLING);
}

//*****************************************************************************
//
//! breif i2c salve recevive interrupt install function
//! 
//! return none
//
//*****************************************************************************
unsigned long SlavaRecvFunc(void *pvCBData, unsigned long ulEvent,
                            unsigned long ulMsgParam, void *pvMsgData)
{
    
    return 0;
}