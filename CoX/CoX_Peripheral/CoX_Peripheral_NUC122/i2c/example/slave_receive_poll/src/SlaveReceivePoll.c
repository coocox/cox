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
static unsigned char SlaveAddress = 0x05;

static unsigned char WriteBuf[] = "helloi2c";
static unsigned long WriteLength = 9;
  
//*****************************************************************************
//
//! Declaration  functions
//
//*****************************************************************************
void UART0Configuration(void);
void Print(char *pcMsg);
unsigned long SlavaRecvFunc(void *pvCBData, 
                                   unsigned long ulEvent,
                                   unsigned long ulMsgParam,
                                   void *pvMsgData);

//*****************************************************************************
//
//! The main function of the i2c slave receive with poll mode
//
//! return none
//
//*****************************************************************************
void SlaveReceivePoll(void)
{
    
    //
    // Congigure the i2c pin
    //
     xSPinTypeI2C(I2C0SCK, PA11);
     xSPinTypeI2C(I2C0DATA, PA10);
    
    //
    // Enable the i2c peripheral
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_I2C0);
    
    //
    // Init the I2C as slave 
    //
    I2CSlaveInit(I2C0_BASE, SlaveAddress, I2C_GENERAL_CALL_DIS);
    
    //
    // Install the i2c0 interrupt service function
    //
   // I2CIntCallbackInit(I2C0_BASE, ( xtEventCallback)SlavaRecvFunc);
    
    WriteBuf[8] = '\0';
    //
    // I2C master transfer config
    //
    I2CSlaveRcCfg.pvWBuf = WriteBuf;
    I2CSlaveRcCfg.ulWLen = WriteLength;
    I2CSlaveRcCfg.ulWCount = 0;
    I2CSlaveRcCfg.pvRBuf = ReceiveBuf;
    I2CSlaveRcCfg.ulRLen = ReceiveLength;
    //I2CSlaveRcCfg.pvRBuf = 0;
    //I2CSlaveRcCfg.ulRLen = 0;
    I2CSlaveRcCfg.ulRCount = 0;
    
    //
    // UART initialize
    //
    UART0Configuration();    
    xI2CIntCallbackInit(I2C0_BASE, SlavaRecvFunc);
    
    //
    // I2C salve receive wiht pollint mode
    //
    I2CSlaveTransfer(I2C0_BASE, &I2CSlaveRcCfg, I2C_TRANSFER_POLLING);
    
    //
    // Print the receive data form the master
    //
    while(1)
    {

    }
    
}

//*****************************************************************************
//
//! \biref uart0 configre 
//!
//! \return  none
//
//*****************************************************************************
void UART0Configuration(void)
{
  
	xSPinTypeUART(U0RX,PB0);
	xSPinTypeUART(U0TX,PB1);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);


    xHWREG(UART0_BASE + UART_FCR) |= 0x6;
    xHWREG(UART0_BASE + UART_FCR) &= ~(0xF0);
    xHWREG(UART0_BASE + UART_FCR) |= 0;

    xHWREG(UART0_BASE + UART_LCR) = 3;
    xHWREG(UART0_BASE + UART_BAUD) = 0x3F000066;

	SysCtlDelay(10000);
}

//*****************************************************************************
//
//! \breif uart send function
//
//! \return none
//
//*****************************************************************************
void Print(char *pcMsg)
{
    unsigned char ch;
    while (*pcMsg != '\0')
    {
        //
        // Put a character in the output buffer.
        //
        ch = *pcMsg++;

        while((xHWREG(UART0_BASE + UART_FSR) & (0x400000))!=0x400000);
	    //
	   // Write this character to the transmit FIFO.
	    //
	    xHWREG(UART0_BASE + UART_THR) = ch;
    }
}

//*****************************************************************************
//
//! \breif i2c salve recevive interrupt install function
//! 
//¡ê?\return none
//
//*****************************************************************************
unsigned long SlavaRecvFunc(void *pvCBData, 
                                   unsigned long ulEvent,
                                   unsigned long ulMsgParam,
                                   void *pvMsgData)
{
    
    return 0;
}