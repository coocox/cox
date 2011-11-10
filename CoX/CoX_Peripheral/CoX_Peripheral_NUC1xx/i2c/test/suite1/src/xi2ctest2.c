//*****************************************************************************
//
//! @page xi2c_testcase xi2c function test
//!
//! File: @ref xi2ctest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xi2c sub component.<br><br>
//! - \p Board: NUC140 board <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. <br><br>
//! .
//!
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define:
//! <br>(1)None.<br><br>
//! - \p Option-hardware:
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:
//! <br>Connect an COM cable to the development board.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//!
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_xi2c_register
//! .
//! \file xi2ctest.c
//! \brief xi2c test source file
//! \brief xi2c test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "string.h"

//*****************************************************************************
//
//!\page test_xi2c_master_send test_xi2c_master_send
//!
//!<h2>Description</h2>
//!Test xi2c master send. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
//!
//! i2c transfer and recevice data config
//!
//
//*****************************************************************************
static tI2CMasterTransferCfg I2CMasterTrCfg;

static unsigned char SendBuf[] = "helloi2c";
static unsigned long SendLength =  9;
static unsigned char SlaveAddress = 0x05;

static unsigned char ReceiveBuf[] = "\r\n";
static unsigned char ReceiveLength = 9;

//
// I2C Device base 
//
static unsigned long ulDevice[2] = {I2C0_BASE, I2C1_BASE};

//*****************************************************************************
//
//! \brief Get the Test description of xi2c002 MasterSend test.
//!
//! \return the desccription of the xi2c002 test.
//
//*****************************************************************************
static char* xI2C002GetTest(void)
{
    return "xI2C [002]:Master send Slave receive test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xi2c002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C002Setup(void)
{
    
    SysCtlKeyAddrUnlock();
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);   
    //
    // Congigure the i2c pin
    //
    xSPinTypeI2C(I2C0SCK, PA9);
    xSPinTypeI2C(I2C0DATA, PA8);
    
    xSPinTypeI2C(I2C1SCK, PA11);
    xSPinTypeI2C(I2C1DATA, PA10);
    
    //
    // Enable the i2c peripheral
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_I2C0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_I2C1);
    
    SendBuf[8] = '\0';
    
    //
    // I2C master transfer config
    //
    I2CMasterTrCfg.ulSlave = SlaveAddress;
    I2CMasterTrCfg.pvWBuf = SendBuf;
    I2CMasterTrCfg.ulWLen = SendLength;
   // I2CMasterTrCfg.pvWBuf = 0;
   // I2CMasterTrCfg.ulWLen = 0;
    I2CMasterTrCfg.ulWCount = 0;
   // I2CMasterTrCfg.pvRBuf = ReceiveBuf;
   // I2CMasterTrCfg.ulRLen = ReceiveLength;
    I2CMasterTrCfg.pvRBuf = 0;
    I2CMasterTrCfg.ulRLen = 0;
    I2CMasterTrCfg.ulRCount = 0;      
  
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xi2c002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C002TearDown(void)
{
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_I2C0);
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_I2C1);
}

//*****************************************************************************
//
//! \brief xi2c 002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C002Execute(void)
{
    unsigned long ulBase;
    xtBoolean bFlag;
    int i;
    
    for(i = 0; i < 1; i++)
    {      
        ulBase = ulDevice[i];
        
        //
        // Init the I2C as master
        //    
        I2CMasterInit(ulBase, 100000);
        
        //
        // master transfer with polling mode
        //
        bFlag = I2CMasterTransfer(ulBase, &I2CMasterTrCfg, I2C_TRANSFER_POLLING);   
        TestAssert(xtrue == bFlag,
           "xi2c API \"I2CMasterTransfer with poll mode \"error!");        
    }
}

//
// xi2c master send and receive with polling mode test case struct.
//
const tTestCase sTestxI2C002MasterSend = {
    xI2C002GetTest,
    xI2C002Setup,
    xI2C002TearDown,
    xI2C002Execute
};

//
// Xi2c test suits.
//
const tTestCase * const psPatternXi2c002[] =
{
    &sTestxI2C002MasterSend,
    0
};

