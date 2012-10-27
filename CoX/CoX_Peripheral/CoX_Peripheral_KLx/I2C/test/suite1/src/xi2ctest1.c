//*****************************************************************************
//
//! @page xi2c_testcase xi2c register test
//!
//! File: @ref xi2ctest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xi2c sub component.<br><br>
//! - \p Board: M051 board <br><br>
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
#include "xhw_i2c.h"
#include "xi2c.h"
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
static unsigned long ulDevice[2] = {I2C0_BASE,I2C1_BASE};

//
// I2C baud -> I2Clk value 
//
static ClkBaud tsClkBaud[3] = {{3000000, 0x80}, {100000, 0x80}, {15000, 0x80}};

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
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
      
    //
    // Enable the i2c peripheral
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_I2C0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_I2C1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOB);

    //
    // Congigure the i2c0 pin
    //
    xSPinTypeI2C(I2C0SCK, PB0);
    xSPinTypeI2C(I2C0SDA, PB1);
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
        ulTemp = xHWREGB(ulBase + I2C_CON1) & I2C_CON1_EN;
        TestAssert(I2C_CON1_EN == ulTemp, 
                   "xi2c API \"I2CEnable\" error!");    
        
        //
        // SI bit test
        //
        I2CIntFlagClear(ulBase);
        ulTemp =  xHWREGB(ulBase + I2C_STATUS) & I2C_STATUS_IF;
        TestAssert(0 ==  ulTemp,
                   "xi2c API \"SI bit clear test\" error!");
        
        //
        // TIME OUT test
        //
        I2CTimeoutFlagClear(ulBase, I2C_TIMEOUT_SCL_LOW);
        ulTemp =  xHWREGB(ulBase + I2C_SMB) & I2C_SMB_SLTF;
        TestAssert(0 ==  ulTemp, "xi2c API error!");
        I2CTimeoutFlagClear(ulBase, I2C_TIMEOUT_SCL_HIGH2);
        ulTemp =  xHWREGB(ulBase + I2C_SMB) & I2C_SMB_SHTF2;
        TestAssert(0 ==  ulTemp, "xi2c API error!");
         
        //
        // Clock divider test
        //
        for(i = 0; i < 3; i++)
        {
            I2CMasterInit(ulBase, tsClkBaud[i].Baud);
            ulTemp = xHWREGB(ulBase + I2C_FREQ) & 0xFF;
            TestAssert(tsClkBaud[i].I2Clk == ulTemp,
                       "xi2c API \"Clock divider test \"error!");    
        } 
        
        //
        // INT Enable bit test 
        //
        xI2CMasterIntEnable(ulBase, xI2C_MASTER_INT_DATA);
        ulTemp = xHWREGB(ulBase + I2C_CON1) & I2C_CON1_IE;
        TestAssert(I2C_CON1_IE == ulTemp,
                   "xi2c, API \"xI2CMasterIntEnable\" error!");
        
        xI2CMasterIntEnable(ulBase, I2C_INT_BUS_STOP);
        ulTemp = xHWREGB(ulBase + I2C_FLT) & I2C_FLT_STOPIE;
        TestAssert(I2C_FLT_STOPIE == ulTemp,
                   "xi2c, API \"xI2CMasterIntEnable\" error!");
        
        xI2CMasterIntEnable(ulBase, I2C_INT_TIMEOUT);
        ulTemp = xHWREGB(ulBase + I2C_SMB) & I2C_SMB_SHTF2IE;
        TestAssert(I2C_SMB_SHTF2IE == ulTemp,
                   "xi2c, API \"xI2CMasterIntEnable\" error!");
           
        I2CIntDisable(ulBase, xI2C_MASTER_INT_DATA);
        ulTemp = xHWREGB(ulBase + I2C_CON1) & I2C_CON1_IE;
        TestAssert(0 == ulTemp,
                   "xi2c API \"I2CIntDisable \"error!");  
        
        I2CIntDisable(ulBase, I2C_INT_BUS_STOP);
        ulTemp = xHWREGB(ulBase + I2C_FLT) & I2C_FLT_STOPIE;
        TestAssert(0 == ulTemp, "xi2c, API error!");
        
        I2CIntDisable(ulBase, I2C_INT_TIMEOUT);
        ulTemp = xHWREGB(ulBase + I2C_SMB) & I2C_SMB_SHTF2IE;
        TestAssert(0 == ulTemp, "xi2c, API  error!");
        
        I2CSlaveSecondAddressSet(ulBase, 0x25);
        ulTemp = xHWREGB(ulBase + I2C_SMB) & I2C_SMB_SIICAEN;
        TestAssert(I2C_SMB_SIICAEN == ulTemp, "xi2c, API  error!");
        ulTemp = xHWREGB(ulBase + I2C_A2);
        TestAssert((0x25<<1) == ulTemp, "xi2c, API  error!");
        
        I2CSecondAddressDisable(ulBase);
        ulTemp = xHWREGB(ulBase + I2C_SMB) & I2C_SMB_SIICAEN;
        TestAssert(0 == ulTemp, "xi2c, API  error!");
        
        I2CHighDriverEnable(ulBase);
        ulTemp = xHWREGB(ulBase + I2C_CON2) & I2C_CON2_HDRS;
        TestAssert(I2C_CON2_HDRS == ulTemp, "xi2c, API  error!");
        
        I2CHighDriverDisable(ulBase);
        ulTemp = xHWREGB(ulBase + I2C_CON2) & I2C_CON2_HDRS;
        TestAssert(0 == ulTemp, "xi2c, API  error!");
        
        I2CSlaveBaudEnable(ulBase);
        ulTemp = xHWREGB(ulBase + I2C_CON2) & I2C_CON2_SBRC;
        TestAssert(I2C_CON2_SBRC == ulTemp, "xi2c, API  error!");
        
        I2CSlaveBaudDisable(ulBase);
        ulTemp = xHWREGB(ulBase + I2C_CON2) & I2C_CON2_SBRC;
        TestAssert(0 == ulTemp, "xi2c, API  error!");
        
        I2CWakeupEnable(ulBase);
        ulTemp = xHWREGB(ulBase + I2C_CON1) & I2C_CON1_WUEN;
        TestAssert(I2C_CON1_WUEN == ulTemp, "xi2c, API  error!");
        
        I2CWakeupDisable(ulBase);
        ulTemp = xHWREGB(ulBase + I2C_CON1) & I2C_CON1_WUEN;
        TestAssert(0 == ulTemp, "xi2c, API  error!");
        
        I2CDMAEnable(ulBase);
        ulTemp = xHWREGB(ulBase + I2C_CON1) & I2C_CON1_DMAEN;
        TestAssert(I2C_CON1_DMAEN == ulTemp, "xi2c, API  error!");
        
        I2CDMADisable(ulBase);
        ulTemp = xHWREGB(ulBase + I2C_CON1) & I2C_CON1_DMAEN;
        TestAssert(0 == ulTemp, "xi2c, API  error!");
        
        I2CRangeAddrEnable(ulBase, 0x33);
        ulTemp = xHWREGB(ulBase + I2C_CON2) & I2C_CON2_RMEN;
        TestAssert(I2C_CON2_RMEN == ulTemp, "xi2c, API  error!");
        ulTemp = xHWREGB(ulBase + I2C_RA);
        TestAssert((0x33<<1) == ulTemp, "xi2c, API  error!");  
        
        I2CRangeAddrDisable(ulBase);
        ulTemp = xHWREGB(ulBase + I2C_CON2) & I2C_CON2_RMEN;
        TestAssert(0 == ulTemp, "xi2c, API  error!");
        
        I2CGlitchFilterSet(ulBase, 21);
        ulTemp = xHWREGB(ulBase + I2C_FLT) & I2C_FLT_FLT_M;
        TestAssert(21 == ulTemp, "xi2c, API  error!");
        
        //
        // Slave int enable
        //
        xI2CSlaveIntEnable(ulBase, xI2C_SLAVE_INT_DATA);
        ulTemp = xHWREGB(ulBase + I2C_CON1) & I2C_CON1_IE;
        TestAssert(I2C_CON1_IE == ulTemp,
                   "xi2c, API \"xI2CSlaveIntEnable\" error!");
        
        //
        // Slave int disable
        //
        xI2CSlaveIntDisable(ulBase, xI2C_SLAVE_INT_DATA);
        ulTemp = xHWREGB(ulBase + I2C_CON1) & I2C_CON1_IE;
        TestAssert(0 == ulTemp,
                   "xi2c, API \"xI2CSlaveIntDisable\" error!");        
       
        //
        // Timerout counter enable test
        //
        I2CTimeoutCounterSet(ulBase, I2C_TIMEOUT_DIV64, 0x1234); 
        ulTemp = (unsigned long)(xHWREGB(ulBase + I2C_SLTH));
        ulTemp = (ulTemp << 8)| xHWREGB(ulBase + I2C_SLTL);
        TestAssert(0x1234 == ulTemp,
                   "xi2c API \"I2CTimeoutCounterSet \" error!");
           
        //
        // I2C disable test
        //
        I2CDisable(ulBase);
        ulTemp = xHWREGB(ulBase + I2C_CON1) & I2C_CON1_EN;
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

