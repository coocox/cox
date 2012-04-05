//*****************************************************************************
//
//! @page xi2c_testcase xi2c register test
//!
//! File: @ref xi2ctest02.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: HT32F125x <br><br>
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
//! \file xi2ctest02.c
//! \brief xi2c test source file
//! \brief xi2c test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_memmap.h"
#include "xhw_i2c.h"
//*****************************************************************************
//
//!\page test_xi2c_register test_xi2c_register
//!
//!<h2>Description</h2>
//!Test xi2c register. <br>
//!
//
//*****************************************************************************

unsigned long ulBase = I2C0_BASE;

//
// The I2Clk register value corresponding to Baud value
//
typedef struct
{
  //
  // I2C Baud value
  //
  unsigned long Baud;
  
  //
  // I2Clk value
  //
  unsigned long I2Clk;
  
}ClkBaud;

//
// I2C baud -> I2Clk value 
//
static ClkBaud tsClkBaud[3] = {{400000, 0}, {100000, 29}, {15000, 199}};
unsigned long ulIntTemp[10] = {I2C_INT_STA, I2C_INT_STO, I2C_INT_ADRS, 
                               I2C_INT_GCS, I2C_INT_ARBLOS, I2C_INT_RXNACK,
                               I2C_INT_BUSERR, I2C_INT_RXDNE, I2C_INT_TXDE,
                               I2C_INT_RXBF};

unsigned long SlaveInitRe[4] = {(I2C_ADDR_7BIT | I2C_GENERAL_CALL_DIS),
                                (I2C_ADDR_7BIT | I2C_GENERAL_CALL_EN),
                                (I2C_ADDR_10BIT | I2C_GENERAL_CALL_DIS),
                                (I2C_ADDR_10BIT | I2C_GENERAL_CALL_EN)};

//*****************************************************************************
//
//! \breif i2c slave interrupt install function
//! 
//! \return none
//
//*****************************************************************************
unsigned long I2CSlaveCallback1(void *pvCBData, 
                               unsigned long ulEvent,
                               unsigned long ulMsgParam,
                               void *pvMsgData)
{
    if(ulMsgParam == xI2C_SLAVE_EVENT_RREQ)
    {

    }
    else if (ulMsgParam == xI2C_SLAVE_EVENT_TREQ)
    {

    }
    return 0;
}

//*****************************************************************************
//
//! \brief Get the Test description of xi2c002 register test.
//!
//! \return the desccription of the xi2c002 test.
//
//*****************************************************************************
static char* xI2C002GetTest(void)
{
    return "xI2C, 002, I2C Peripheral Clock Source Set test";
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
    xSysCtlPeripheralEnable2(ulBase);
    xSysCtlPeripheralReset2(ulBase);
    
    xSysCtlPeripheralEnable2(ulBase);
    xSysCtlPeripheralReset2(ulBase);
    
    xSysCtlPeripheralEnable2(xGPIO_PORTB_BASE);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    
    xSPinTypeI2C(I2C0SCK, PA11);
    xSPinTypeI2C(I2C0SDA, PA12);
    

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
    
}



//*****************************************************************************
//
//! \brief xi2c002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C002Execute(void)
{
    int i;
    unsigned long ulTemp;
    unsigned long ulTemp1;
    //
    // I2C enable test
    //
    I2CEnable(ulBase);
    ulTemp = xHWREG(ulBase + I2C_CR) & I2C_CR_I2CEN;
    TestAssert(I2C_CR_I2CEN == ulTemp, 
               "xi2c API \"I2CEnable\" error!"); 
    
    //
    // Clock divider test
    //
    for(i = 0; i < 3; i++)
    {
        I2CMasterInit(ulBase, tsClkBaud[i].Baud);
        ulTemp = xHWREG(ulBase + I2C_SHPGR) & I2C_SHPGR_SHPG_M;
        ulTemp1 = xHWREG(ulBase + I2C_SLPGR) & I2C_SLPGR_SLPG_M;
        ulTemp += ulTemp1 + 14;
        ulTemp1 = 72000000/ulTemp;
        TestAssert(tsClkBaud[i].Baud == ulTemp1,
                   "xi2c API \"Clock divider test \"error!"); 
       
    } 
    
    //
    // int enable
    //
    for(i = 0; i < 10; i++)
    {
        I2CIntEnable(ulBase, ulIntTemp[i]);
        ulTemp = xHWREG(ulBase + I2C_IER) & ulIntTemp[i];
        TestAssert(ulTemp == ulIntTemp[i],
                   "xi2c, \"I2CIntEnable\" error!");
    }
    //
    // int disable
    //
    for(i = 0; i < 10; i++)
    {
        I2CIntDisable(ulBase, ulIntTemp[i]);
        ulTemp = xHWREG(ulBase + I2C_IER) & ulIntTemp[i];
        TestAssert(ulTemp == 0,
                   "xi2c, \"I2CIntEnable\" error!");
    }
    
    //
    // I2CSlaveInit test
    //
    for(i = 0; i < 3; i++)
    {
      I2CSlaveInit(ulBase, i/2 ? I2C_ADDR_10BIT:I2C_ADDR_7BIT, 0x34, 
                           i%2 ? I2C_GENERAL_CALL_EN:I2C_GENERAL_CALL_DIS);
        ulTemp = xHWREG(ulBase + I2C_CR) & (I2C_CR_GCEN | I2C_CR_ADRM);
        ulTemp1 = xHWREG(ulBase + I2C_ADDR) & I2C_ADDR_ADDR_M;
        TestAssert(SlaveInitRe[i] == ulTemp,
                   "xi2c API \"Clock divider test \"error!"); 
    } 
    
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXi2c002Register = {
		xI2C002GetTest,
		xI2C002Setup,
		xI2C002TearDown,
		xI2C002Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXi2c02[] =
{
    &sTestXi2c002Register,
    0
};