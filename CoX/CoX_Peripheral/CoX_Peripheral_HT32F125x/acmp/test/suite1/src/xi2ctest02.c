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
//*****************************************************************************
//
//!\page test_xi2c_register test_xi2c_register
//!
//!<h2>Description</h2>
//!Test xi2c register. <br>
//!
//
//*****************************************************************************

unsigned long ulI2C = I2C0_BASE;

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
    xSysCtlPeripheralEnable2(ulI2C);
    xSysCtlPeripheralReset2(ulI2C);
    
    xSysCtlPeripheralEnable2(ulI2C);
    xSysCtlPeripheralReset2(ulI2C);
    
    xSysCtlPeripheralEnable2(xGPIO_PORTA_BASE);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    
    xSPinTypeI2C(I2C0SCK, PA11);
    xSPinTypeI2C(I2C0SDA, PA12);
    
    I2CSlaveInit(ulI2C, I2C_ADDR_7BIT, 0x12, I2C_GENERAL_CALL_DIS);
    I2CEnable(ulI2C);
    I2CIntEnable(ulI2C, 0);
    xIntEnable(xSysCtlPeripheralIntNumGet(ulI2C));
    I2CIntCallbackInit(ulI2C, I2CSlaveCallback1);

    //I2CMasterInit(ulI2C, SysCtlClockGet());
    //I2CEnable(ulI2C);
    //I2CMasterWriteS1(ulI2C, 0x12, 'a', xfalse);
    //I2CMasterWriteS2(ulI2C, 'b', xfalse);
    //I2CMasterWriteS2(ulI2C, 'c', xfalse);
    //I2CMasterWriteS2(ulI2C, 'd', xfalse);

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