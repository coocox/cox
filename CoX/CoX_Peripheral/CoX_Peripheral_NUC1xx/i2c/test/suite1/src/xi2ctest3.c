//*****************************************************************************
//
//! @page xi2c_testcase xi2c function test
//!
//! File: @ref xi2ctest3.c
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

//*****************************************************************************
//
//!\page test_xi2c_master_send test_xi2c_master_send
//!
//!<h2>Description</h2>
//!Test xi2c master send. <br>
//!
//
//*****************************************************************************
static xtBoolean StringCmp(unsigned char *ucStr1, unsigned char *ucStr2)
{
    //unsigned char *cp = ucStr1;
    
    while(*ucStr1++ == *ucStr2++)
    {
        if(*ucStr1 == '\0' && *ucStr2 == '\0')
        {
            return xtrue;
        }
    }
    
    return xfalse;  
}

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
//! \breif i2c master interrupt install function
//! 
//! \return none
//
//*****************************************************************************
unsigned long MasterSend(void *pvCBData, 
                                   unsigned long ulEvent,
                                   unsigned long ulMsgParam,
                                   void *pvMsgData)
{
    TestEmitToken('a');
    return 0;
}

//*****************************************************************************
//
//! \brief Get the Test description of xi2c003 MasterSend test.
//!
//! \return the desccription of the xi2c003 test.
//
//*****************************************************************************
static char* xI2C003GetTest(void)
{
    return "xI2C [003]: Master send and receive with interrupt mode";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xi2c003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C003Setup(void)
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
    
    //
    // I2C master transfer config
    //
    I2CMasterTrCfg.ulSlave = SlaveAddress;
    I2CMasterTrCfg.pvWBuf = SendBuf;
    I2CMasterTrCfg.ulWLen = SendLength;
    I2CMasterTrCfg.ulWCount = 0;
    I2CMasterTrCfg.pvRBuf = ReceiveBuf;
    I2CMasterTrCfg.ulRLen = ReceiveLength;
    I2CMasterTrCfg.ulRCount = 0;      
  
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xi2c003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C003TearDown(void)
{
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_I2C0);
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_I2C1);
}

//*****************************************************************************
//
//! \brief xi2c 003 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C003Execute(void)
{
    unsigned char ucFlag;
    xtBoolean bFlag;
  
    //
    // Init the I2C as master, change the rata form 0 to 2000000
    //     
    I2CMasterInit(I2C0_BASE, 1000000);
    
    //
    // Install the i2c0 interrupt service function
    //
    I2CIntCallbackInit(I2C0_BASE, (xtEventCallback)MasterSend);
    
    //
    // master transfer with polling mode
    //
    ucFlag = xI2CMasterTransfer(I2C0_BASE, &I2CMasterTrCfg, I2C_TRANSFER_INTERRUPT);
    TestAssert(xtrue == ucFlag,
               "xi2c, \"I2C MasterTransfer\" error!");
    TestAssertQBreak("a","i2c master interrupt fail", 1000000);  
}

//
// xi2c master send and receive with polling mode test case struct.
//
const tTestCase sTestxI2C003MasterSend = {
    xI2C003GetTest,
    xI2C003Setup,
    xI2C003TearDown,
    xI2C003Execute
};

//
// Xi2c test suits.
//
const tTestCase * const psPatternXi2c003[] =
{
    &sTestxI2C003MasterSend,
    0
};

