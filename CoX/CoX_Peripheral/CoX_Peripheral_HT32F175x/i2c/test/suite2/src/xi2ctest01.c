//*****************************************************************************
//
//! @page xi2c_testcase xcore register test
//!
//! File: @ref xi2c.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: HT32F175x <br><br>
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
//! \file xi2c.c
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

unsigned long ulMaster = I2C0_BASE;
unsigned char ucTempData[5] = "abcd";
unsigned char ucTemp[5];
unsigned char ucTempCount = 0;
unsigned char ucTempCount1 = 0;

//*****************************************************************************
//
//! \brief Get the Test description of xi2c001 register test.
//!
//! \return the desccription of the xi2c001 test.
//
//*****************************************************************************
static char* xI2C001GetTest(void)
{
    return "xI2C, 001, I2C test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xi2c001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C001Setup(void)
{      
    xSysCtlPeripheralEnable2(ulMaster);

    xSysCtlPeripheralEnable2(xGPIO_PORTD_BASE);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    
    xSPinTypeI2C(I2C0SCK, PD12);
    xSPinTypeI2C(I2C0SDA, PD13);
    
}


//*****************************************************************************
//
//! \brief something should do after the test execute of xi2c001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C001TearDown(void)
{   

}



//*****************************************************************************
//
//! \brief xi2c 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C001Execute(void)
{
    I2CMasterInit(ulMaster, 400000);
    I2CEnable(ulMaster);
    
    I2CMasterWriteS1(ulMaster, 0x12, 'a', xfalse);
    I2CMasterWriteS2(ulMaster, 'b', xfalse);
    I2CMasterWriteS2(ulMaster, 'c', xfalse);
    I2CMasterWriteS2(ulMaster, 'd', xfalse);
    
    I2CMasterReadBufS1(ulMaster, 0x12, ucTemp, 5, xtrue);
    TestAssert(ucTemp[0] == 'a',
                   "xi2c, \"I2C send or receive\" error!");
    TestAssert(ucTemp[1] == 'b',
                   "xi2c, \"I2C send or receive\" error!");
    TestAssert(ucTemp[2] == 'c',
                   "xi2c, \"I2C send or receive\" error!");
    TestAssert(ucTemp[3] == 'd',
                   "xi2c, \"I2C send or receive\" error!");
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
    return "xI2C, 002, I2C Send and Receive Interrupt test";
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
    I2CMasterInit(ulMaster, 400000);
    I2CEnable(ulMaster);
    
    I2CMasterWriteBufS1(ulMaster, 0x12, ucTempData, 4, xfalse);
    
    I2CMasterReadS1(ulMaster, 0x12, ucTemp, xfalse);
    
    I2CMasterReadS2(ulMaster, &ucTemp[1], xfalse);
    I2CMasterReadS2(ulMaster, &ucTemp[2], xfalse);
    I2CMasterReadS2(ulMaster, &ucTemp[3], xfalse);
    
    I2CMasterReadBufS1(ulMaster, 0x12, ucTemp, 5, xtrue);

    TestAssert(ucTemp[0] == 'a',
                   "xi2c, \"I2C send or receive\" error!");
    TestAssert(ucTemp[1] == 'b',
                   "xi2c, \"I2C send or receive\" error!");
    TestAssert(ucTemp[2] == 'c',
                   "xi2c, \"I2C send or receive\" error!");
    TestAssert(ucTemp[3] == 'd',
                   "xi2c, \"I2C send or receive\" error!");

}

//
// xi2c register test case struct.
//
const tTestCase sTestXi2c001Register = {
		xI2C001GetTest,
		xI2C001Setup,
		xI2C001TearDown,
		xI2C001Execute
};

//
// xi2c register test case struct.
//
const tTestCase sTestXi2c003Register = {
		xI2C002GetTest,
		xI2C001Setup,
		xI2C001TearDown,
		xI2C002Execute
};


//
// xi2c test suits.
//
const tTestCase * const psPatternXi2c01[] =
{
    &sTestXi2c001Register,
//    &sTestXi2c003Register,
    0
};