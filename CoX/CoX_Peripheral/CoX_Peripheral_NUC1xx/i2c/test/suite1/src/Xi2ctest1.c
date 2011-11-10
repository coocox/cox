//*****************************************************************************
//
//! @page xi2c_testcase xi2c register test
//!
//! File: @ref xi2ctest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xi2c sub component.<br><br>
//! - \p Board: NUC140VE3CN board <br><br>
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
//! \file xi2ctest1.c
//! \brief xi2c test source file
//! \brief xi2c test header file <br>
//
//*****************************************************************************

#include "test.h"

//*****************************************************************************
//
//!\page test_xi2c_register test_xi2c_register
//!
//!<h2>Description</h2>
//!Test xi2c register. <br>
//!
//
//*****************************************************************************

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

//*****************************************************************************
//
//! Static values
//
//*****************************************************************************

//
// I2C Device base 
//
static unsigned long ulDevice[2] = {I2C0_BASE, I2C1_BASE};

//
// Slave address set value
//
static unsigned char ucSlaveAddr[4] = {10, 20, 30, 40};

//
// Slave address mask set value
//
static unsigned char ucSlaveAddrMask[4] = {4, 6, 8, 10};

//
// I2C baud -> I2Clk value 
//
static ClkBaud tsClkBaud[3] = {{3000000, 0}, {100000, 29}, {15000, 199}};

//
// Slave address set value
//
static unsigned long ulTemp0[4] = {0x04, 0x18, 0x1C, 0x20};

//
// Slave address mask set value
//
static unsigned long ulTemp1[4] = {0x24, 0x28, 0x2C, 0x30}; 

//*****************************************************************************
//
//! \brief Get the Test description of xi2c001 register test.
//!
//! \return the desccription of the xi2c001 test.
//
//*****************************************************************************
static char* xI2C001GetTest(void) 
{
    return "xI2C [001]: xi2c register test";
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
    SysCtlKeyAddrUnlock();
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
      
    //
    // Enable the i2c peripheral
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_I2C0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_I2C1);
    
    //
    // Congigure the i2c0 pin
    //
    xSPinTypeI2C(I2C0SCL, PA9);
    xSPinTypeI2C(I2C0DATA, PA8);
    
    //
    // Configure the i2c1 pin
    //
    xSPinTypeI2C(I2C1SCL, PA11);
    xSPinTypeI2C(I2C1DATA, PA10);
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
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_I2C0);
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_I2C1);
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
        ulTemp = xHWREG(ulBase + I2C_O_CON) & I2C_CON_ENS1;
        TestAssert(I2C_CON_ENS1 == ulTemp, 
                   "xi2c API \"I2CEnable\" error!");    
        
        /*
        //
        // Assert AA bit test
        //
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
        ulTemp =  xHWREG(ulBase + I2C_O_CON) & I2C_CON_AA;
        TestAssert(I2C_CON_AA ==  ulTemp,
                   "xi2c API \"Assert AA bit test\" error!");
        */
        
        //
        // SI bit test
        //
        I2CIntFlagClear(ulBase);
        ulTemp =  xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI;
        TestAssert(0 ==  ulTemp,
                   "xi2c API \"SI bit clear test\" error!");
         
        //
        // Clock divider test
        //
        for(i = 0; i < 3; i++)
        {
            I2CMasterInit(ulBase, tsClkBaud[i].Baud);
            ulTemp = xHWREG(ulBase + I2C_O_CLK) & I2C_CLK_CLK_M;
            TestAssert(tsClkBaud[i].I2Clk == ulTemp,
                       "xi2c API \"Clock divider test \"error!");    
        } 
        
        //
        // INT Enable bit test
        //
        xI2CMasterIntEnable(ulBase, xI2C_INT_FUNCTION);
        ulTemp = xHWREG(ulBase + I2C_O_CON) & I2C_CON_EI;
        TestAssert(I2C_CON_EI == ulTemp,
                   "xi2c, API \"xI2CMasterIntEnable\" error!");
           
        I2CIntDisable(ulBase);
        ulTemp = xHWREG(ulBase + I2C_O_CON) & I2C_CON_EI;
        TestAssert(0 == ulTemp,
                   "xi2c API \"I2CIntDisable \"error!");  
        
        //
        // Slave address set test
        //
        for(i = 0; i < 4; i++)
        {
            xI2CSlaveOwnAddressSet(ulBase, i, ucSlaveAddr[i], I2C_GENERAL_CALL_DIS);
            ulTemp = xHWREG(ulBase + ulTemp0[i]) >> 1; 
            TestAssert(ucSlaveAddr[i] == ulTemp,
                       "xi2c, \"xI2CSlaveOwnAddressSet\" error!");
        }
        
        //
        // Slave general call set test
        //
        for(i = 0; i < 4; i++)
        {
            xI2CSlaveOwnAddressSet(ulBase, i, ucSlaveAddr[i], I2C_GENERAL_CALL_EN);
            ulTemp = xHWREG(ulBase + ulTemp0[i]) & 0x01; 
            TestAssert(1 == ulTemp,
                       "xi2c, \" Slave general call enable\" error!");
        }  
        
        //
        // Slave address mask set test
        //
        for(i = 0; i < 4; i++)
        {
            xI2CSlaveOwnAddressMaskSet(ulBase, i, ucSlaveAddrMask[i]);
            ulTemp = xHWREG(ulBase + ulTemp1[i])>>1;
            TestAssert(ulTemp == ucSlaveAddrMask[i],
                       "xi2c, \"xI2CSlaveOwnAddressMaskSet\" error!");
        }
        
        //
        // Slave int enable
        //
        xI2CSlaveIntEnable(ulBase, xI2C_INT_FUNCTION);
        ulTemp = xHWREG(ulBase + I2C_O_CON) & I2C_CON_EI;
        TestAssert(I2C_CON_EI == ulTemp,
                   "xi2c, API \"xI2CSlaveIntEnable\" error!");
        
        //
        // Slave int disable
        //
        xI2CSlaveIntDisable(ulBase, xI2C_INT_FUNCTION);
        ulTemp = xHWREG(ulBase + I2C_O_CON) & I2C_CON_EI;
        TestAssert(0 == ulTemp,
                   "xi2c, API \"xI2CSlaveIntDisable\" error!");        
       
        //
        // Timerout counter enable test
        //
        I2CTimeoutCounterSet(ulBase, I2C_TIMEOUT_EN, I2C_TIMEOUT_DIV_NO); 
        ulTemp = xHWREG(ulBase + I2C_O_TOC) & I2C_TIMEOUT_EN;
        TestAssert(I2C_TIMEOUT_EN == ulTemp,
                   "xi2c API \"I2CTimeoutCounterSet \" error!");
           
        //
        // I2C disable test
        //
        I2CDisable(ulBase);
        ulTemp = xHWREG(ulBase + I2C_O_CON) & I2C_CON_EI;
        TestAssert(0 == ulTemp, 
                   "xi2c API \"I2CDisable\" error!");    
    }
}

//
// xi2c register test case struct.
//
const tTestCase sTestxI2C001Register = {
    xI2C001GetTest,
    xI2C001Setup,
    xI2C001TearDown,
    xI2C001Execute
};

//
// Xi2c test suits.
//
const tTestCase * const psPatternXi2c001[] =
{
    &sTestxI2C001Register,
    0
};

