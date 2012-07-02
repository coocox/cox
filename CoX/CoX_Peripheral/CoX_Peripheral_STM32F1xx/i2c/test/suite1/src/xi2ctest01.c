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
#include "xhw_i2c.h"
//*****************************************************************************
//
//!\page test_xsysctl_register test_xsysctl_register
//!
//!<h2>Description</h2>
//!Test xsysctl register. <br>
//!
//
//*****************************************************************************


//
// I2C Device base 
//
static unsigned long ulDevice[2] = {I2C1_BASE, I2C2_BASE};

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
    xSysCtlPeripheralEnable2(I2C1_BASE);
    xSysCtlPeripheralReset2(I2C1_BASE);
    
    xSysCtlPeripheralEnable2(I2C2_BASE);
    xSysCtlPeripheralReset2(I2C2_BASE);
    
    xSysCtlPeripheralEnable2(GPIOB_BASE);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    
    xSPinTypeI2C(I2C1SCK, PB6);
    xSPinTypeI2C(I2C1SDA, PB7);
    //xSPinTypeI2C(I2C1SCK, PB8);
    //xSPinTypeI2C(I2C1SDA, PB9);
    
    xSPinTypeI2C(I2C2SCK, PB10);
    xSPinTypeI2C(I2C2SDA, PB11);
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
    unsigned long ulBase;
    unsigned long ulTemp;
    unsigned long i;
    unsigned long j;
    
    for(j = 0; j < 2; j++)
    {
        ulBase = ulDevice[j];
        //
        // I2C enable test
        //
        I2CEnable(ulBase);
        ulTemp = xHWREG(ulBase + I2C_CR1) & I2C_CR1_PE;
        TestAssert(I2C_CR1_PE == ulTemp, 
                   "xi2c API \"I2CEnable\" error!");
        
        I2CDisable(ulBase);
        ulTemp = xHWREG(ulBase + I2C_CR1) & I2C_CR1_PE;
        TestAssert(0 == ulTemp,
                   "xi2c API \"I2CIntDisable \"error!"); 
        
        I2CIntEnable(ulBase, I2C_INT_BUF | I2C_INT_EVT | I2C_INT_ERR);
        ulTemp = xHWREG(ulBase + I2C_CR2) & (I2C_CR2_ITBUFEN | I2C_CR2_ITEVTEN | 
                                             I2C_CR2_ITERREN);
        TestAssert((I2C_CR2_ITBUFEN | I2C_CR2_ITEVTEN | I2C_CR2_ITERREN)== ulTemp,
                   "xi2c API \"I2CIntEnable \"error!"); 
        
        I2CIntDisable(ulBase, I2C_INT_BUF | I2C_INT_EVT | I2C_INT_ERR);
        ulTemp = xHWREG(ulBase + I2C_CR2) & (I2C_CR2_ITBUFEN | I2C_CR2_ITEVTEN | 
                                             I2C_CR2_ITERREN);
        TestAssert((0)== ulTemp,
                   "xi2c API \"I2CIntEnable \"error!");
        
        I2CDMAEnable(ulBase, I2C_DMA_LAST_EN);  
        ulTemp = xHWREG(ulBase + I2C_CR2) & (I2C_CR2_LAST | I2C_CR2_DMAEN);
        TestAssert((I2C_CR2_LAST | I2C_CR2_DMAEN) == ulTemp,
                   "xi2c API \"I2CDMAEnable \"error!");
        
        I2CDMADisable(ulBase);  
        ulTemp = xHWREG(ulBase + I2C_CR2) & (I2C_CR2_LAST | I2C_CR2_DMAEN);
        TestAssert((0) == ulTemp,
                   "xi2c API \"I2CDMAEnable \"error!");
        
        I2COwnAddress2Config(ulBase, I2C_DUAL_ADD_EN, 0x12);  
        ulTemp = xHWREG(ulBase + I2C_OAR2);
        TestAssert(((0x12 << 1) | 1) == ulTemp,
                   "xi2c API \"I2COwnAddress2Config \"error!");
    }
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