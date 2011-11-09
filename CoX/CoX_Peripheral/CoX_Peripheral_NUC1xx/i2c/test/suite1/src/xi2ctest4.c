//*****************************************************************************
//
//! @page xi2c_testcase xi2c multiple slave address and  address mask test
//!
//! File: @ref xi2ctest4.c
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
//! - \subpage test_multiple_slave_address
//! .
//! \file xi2ctest4.c
//! \brief xi2c test source file
//! \brief xi2c test header file <br>
//
//*****************************************************************************

#include "test.h"

//*****************************************************************************
//
//!\page test_multiple_slave_address test_multiple_slave_address
//!
//!<h2>Description</h2>
//!Test multiple slave address. <br>
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
static tI2CMasterTransferCfg I2C0MasterTrCfg;

static unsigned char I2CSendBuf[] = "Helloi2c";
static unsigned long SendLength = 8;
static unsigned char SlaveAddress[4] = {0x05, 0x50, 0x0f, 0};


//*****************************************************************************
//
//! \brief Get the Test description of xi2c004 multiple slave address test.
//!
//! \return the desccription of the xi2c004 test.
//
//*****************************************************************************
static char* xI2C004GetTest(void)
{
    return "xI2C [004]: xi2c multiple slave address test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xi2c004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C004Setup(void)
{
    //
    // Enable the i2c peripheral
    //
    SysCtlKeyAddrUnlock();  
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
    
    //
    // Congigure the i2c pin
    //
    xSPinTypeI2C(I2C0SCK, PA9);
    xSPinTypeI2C(I2C0DATA, PA8);
    
    //
    // Enable the i2c peripheral
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_I2C0);
    
    //
    // I2C0 master transfer config
    //
    I2C0MasterTrCfg.pvWBuf = I2CSendBuf;
    I2C0MasterTrCfg.ulWLen = SendLength;
    I2C0MasterTrCfg.ulWCount = 0;
    I2C0MasterTrCfg.pvRBuf = 0;
    I2C0MasterTrCfg.ulRLen = 0;
    I2C0MasterTrCfg.ulRCount = 0;   
    
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xi2c004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C004TearDown(void)
{
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_I2C0);
}

//*****************************************************************************
//
//! \brief xi2c 004 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C004Execute(void)
{
    int i;
    unsigned char ucFlag;
    
    //
    // Init the I2C as master
    //    
    I2CMasterInit(I2C0_BASE, 100000);
    
    //
    // First slave address 0x05
    // Second slave address 0x50
    // Third slave address 0x0f
    // Fourth slave adress 0x00, in general call mode
    //
    for(i = 0; i < 4; i++)
    {
        I2C0MasterTrCfg.ulSlave = SlaveAddress[i];
         
        //
        // master transfer with polling mode
        //
        ucFlag = I2CMasterTransfer(I2C0_BASE, &I2C0MasterTrCfg, I2C_TRANSFER_POLLING);    
        ucFlag &= ucFlag;
    }
    TestAssert(ucFlag == xtrue,
               "xi2c, \"Slave multiple address test\" error!");
      
}

//
// xi2c register test case struct.
//
const tTestCase sTestxI2C004MultipleSlaveAddress = {
    xI2C004GetTest,
    xI2C004Setup,
    xI2C004TearDown,
    xI2C004Execute
};

//
// xi2c test suits.
//
const tTestCase * const psPatternXi2c004[] =
{
    &sTestxI2C004MultipleSlaveAddress,
    0
};

