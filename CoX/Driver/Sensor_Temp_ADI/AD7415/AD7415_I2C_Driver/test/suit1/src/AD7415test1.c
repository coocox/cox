//*****************************************************************************
//
//! @page di_ad7415arz_testcase di_ad7415arz register test
//!
//! File: @ref AD7415test1.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the di_ad7415arz sub component.<br><br>
//! - \p Board: NUC140 & AD7415ARZ board <br><br>
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
//! - \subpage test_di_ad7415arz_register
//! .
//! \file AD7415test1.c
//! \brief di_ad7415arz test source file
//! \brief di_ad7415arz test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "hw_ad7415.h"
#include "ad7415.h"

//*****************************************************************************
//
//!\page test_di_ad7415arz_register test_di_ad7415arz_register
//!
//!<h2>Description</h2>
//!Test di_ad7415arz register. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Get the Test description of di_ad7415arz001 register test.
//!
//! \return the desccription of the di_ad7415arz001 test.
//
//*****************************************************************************
static char* di_ad7415arz001GetTest(void)
{
    return "di_ad7415arz [001]: di_ad7415arz register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of di_ad7415arz001 test.
//!
//! \return None.
//
//*****************************************************************************
static void di_ad7415arz001Setup(void)
{
    //
    // Set the external 12MHZ clock as system clock 
    //
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
      
    //
    // AD7415 device init
    // 
    AD7415Init(1000, AD7415_PowerDown_Quit);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of di_ad7415arz001 test.
//!
//! \return None.
//
//*****************************************************************************
static void di_ad7415arz001TearDown(void)
{
    AD7415DeInit();
}

//*****************************************************************************
//
//! \brief di_ad7415arz 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void di_ad7415arz001Execute(void)
{
    short ulTemp;
    
    //
    // Power down enter in Init funciton
    //
    AD7415Init(1000, AD7415_PowerDown_Enter);
    ulTemp = AD7415RegRead(AD7415_CFG) & AD7415_CFG_PD_ENABLE;
    TestAssert(AD7415_CFG_PD_ENABLE == ulTemp,
               "xAPI, \" Power bit configure test\" error! ");
    //
    // Power down quit in Init function
    //
    AD7415Init(1000, AD7415_PowerDown_Quit);
    ulTemp = AD7415RegRead(AD7415_CFG) & AD7415_CFG_PD_ENABLE;
    TestAssert(0 == ulTemp,
               "xAPI, \" Power bit configure test\" error! ");    
    
    //
    // Power down enter
    //
    AD7415PowerDownEnter();
    ulTemp = AD7415RegRead(AD7415_CFG) & AD7415_CFG_PD_ENABLE;
    TestAssert(AD7415_CFG_PD_ENABLE == ulTemp,
               "xAPI, \" Power bit configure test\" error! ");
    
    //
    // Power down quit
    //
    AD7415PowerDownQuit();
    ulTemp = AD7415RegRead(AD7415_CFG) & AD7415_CFG_PD_ENABLE;
    TestAssert(0 == ulTemp,
               "xAPI, \" Power bit configure test\" error! ");    
    
   
    //
    // I2C Filter Enable 
    //
    AD7415FilterEnable();    
    ulTemp = AD7415RegRead(AD7415_CFG) & 0x40;
    TestAssert(0x40 == ulTemp,
               "xAPI, \"AD7415FilterEnable\" error!");      
    
    //
    // Power on reset cfg value test
    //
    ulTemp = AD7415RegRead(AD7415_CFG);
    TestAssert(0x40 == ulTemp,
               "xAPI, \"Power on reset value test\" error!");    
    
    //
    // I2C Filter disable
    //
    AD7415FilterDisable();    
    ulTemp = AD7415RegRead(AD7415_CFG) & 0x40;
    TestAssert(0 == ulTemp,
               "xAPI, \"AD7415FilterDisable\" error!");  
   
}

//*****************************************************************************
//
//! \brief Get the Test description of di_ad7415arz002 register test.
//!
//! \return the desccription of the di_ad7415arz002 test.
//
//*****************************************************************************
static char* di_ad7415arz002GetTest(void)
{
    return "di_ad7415arz [002]: di_ad7415arz power mode test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of di_ad7415arz002 test.
//!
//! \return none.
//
//*****************************************************************************
static void di_ad7415arz002Setup(void)
{
    //
    //Set the external 12MHZ clock as system clock 
    //
    xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
    
    //
    // AD7415 device init
    //
    AD7415Init(10000, AD7415_PowerDown_Enter); 
}

//*****************************************************************************
//
//! \brief something should do after the test execute of di_ad7415arz002 test.
//!
//! \return none.
//
//*****************************************************************************
static void di_ad7415arz002TearDown(void)
{
    AD7415DeInit();
}

//*****************************************************************************
//
//! \brief di_ad7415arz 002 test execute main body.
//!
//! \return none.
//
//*****************************************************************************
static void di_ad7415arz002Execute(void)
{
    unsigned long  ulTemp;
    int i;     

    for(i = 0; i < 10; i++)
    {
        if(i == 3)
        {
            AD7415PowerDownConvert();
        }
        ulTemp = AD7415TempReadLDC();
        ulTemp = ulTemp + 1;
        for(ulTemp = 0; ulTemp < 1000; ulTemp++);
    }
    
}

//
// di_ad7415arz register test case struct.
//
const tTestCase sTestdi_ad7415arz001Register = {
    di_ad7415arz001GetTest,
    di_ad7415arz001Setup,
    di_ad7415arz001TearDown,
    di_ad7415arz001Execute
};

//
// di_ad7415arz power mode test
//
const tTestCase sTestdi_ad7415arz002PD = {
    di_ad7415arz002GetTest,
    di_ad7415arz002Setup,
    di_ad7415arz002TearDown,
    di_ad7415arz002Execute
};

//
// Xi2c test suits.
//
const tTestCase * const psPatternDI_AD7415ARZ001[] =
{
    &sTestdi_ad7415arz001Register,
    &sTestdi_ad7415arz002PD,
    0
};

