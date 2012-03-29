//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: NUC140 <br><br>
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
//! - \subpage test_xsysctl_register
//! .
//! \file xsysctltest.c
//! \brief xsysctl test source file
//! \brief xsysctl test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_memmap.h"
//*****************************************************************************
//
//!\page test_xsysctl_register test_xsysctl_register
//!
//!<h2>Description</h2>
//!Test xsysctl register. <br>
//!
//
//*****************************************************************************

unsigned long ulSlave = I2C1_BASE;
unsigned long ulMaster = I2C2_BASE;
unsigned char ucTempData[5];
unsigned char ucTemp[5];
unsigned char ucTempCount = 0;
unsigned char ucTempCount1 = 0;

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
        ucTempData[ucTempCount] = I2CDataGet(ulSlave);
        ucTempCount++;
    }
    else if (ulMsgParam == xI2C_SLAVE_EVENT_TREQ)
    {
        I2CDataPut(ulSlave, ucTempData[ucTempCount1]);
        ucTempCount1++;
        if(ucTempCount1 == 4)
        {
            I2CIntDisable(ulSlave, I2C_INT_BUF | I2C_INT_EVT | I2C_INT_ERR);
        }
    }
    return 0;
}

//*****************************************************************************
//
//! \brief Get the Test description of xsysctl002 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* xI2C001GetTest(void)
{
    return "xI2C, 001, I2C Peripheral Clock Source Set test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C001Setup(void)
{    
    xSysCtlPeripheralEnable2(ulSlave);
    xSysCtlPeripheralReset2(ulSlave);
    
    xSysCtlPeripheralEnable2(ulMaster);
    xSysCtlPeripheralReset2(ulMaster);
    
    xSysCtlPeripheralEnable2(GPIOB_BASE);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    
    xSPinTypeI2C(I2C1SCK, PB6);
    xSPinTypeI2C(I2C1SDA, PB7);
    //xSPinTypeI2C(I2C1SCK, PB8);
    //xSPinTypeI2C(I2C1SDA, PB9);
    
    xSPinTypeI2C(I2C2SCK, PB10);
    xSPinTypeI2C(I2C2SDA, PB11);
    
    I2CSlaveInit(ulSlave, I2C_ADDR_7BIT, 0x12, I2C_GENERAL_CALL_DIS);
    I2CEnable(ulSlave);
    I2CIntEnable(ulSlave, I2C_INT_BUF | I2C_INT_EVT | I2C_INT_ERR);
    xIntEnable(xSysCtlPeripheraIntNumGet(ulSlave));
    I2CIntCallbackInit(ulSlave, I2CSlaveCallback);
    
    I2CMasterInit(ulMaster, SysCtlAPB1ClockGet(), xfalse, xtrue);
    I2CEnable(ulMaster);
    I2CMasterWriteS1(ulMaster, 0x12, 'a', xfalse);
    I2CMasterWriteS2(ulMaster, 'b', xfalse);
    I2CMasterWriteS2(ulMaster, 'c', xfalse);
    I2CMasterWriteS2(ulMaster, 'd', xfalse);
    I2CMasterReadS1(ulMaster, 0x12, ucTemp, xfalse);
    I2CMasterReadS2(ulMaster, &ucTemp[1], xfalse);
    I2CMasterReadS2(ulMaster, &ucTemp[2], xfalse);
    I2CMasterReadS2(ulMaster, &ucTemp[3], xtrue);
}


//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C001TearDown(void)
{   

}



//*****************************************************************************
//
//! \brief xsysctl 002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C001Execute(void)
{
 
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXi2c001Register = {
		xI2C001GetTest,
		xI2C001Setup,
		xI2C001TearDown,
		xI2C001Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXi2c01[] =
{
    &sTestXi2c001Register,
    0
};