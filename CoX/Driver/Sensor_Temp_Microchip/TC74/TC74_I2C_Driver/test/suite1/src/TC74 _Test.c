//*****************************************************************************
//
//! @page TC74_testcase TC74 test
//!
//! File: @ref TC74_Test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the TC74 sub component.<br><br>
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
//! - \subpage test_TC74
//! .
//! \file TC74_Test.c
//! \brief TC74 test source file
//! \brief TC74 test header file <br>
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xi2c.h"
#include "TC74.h"
#include "xhw_TC74.h"
#include "test.h"
#include "testcase.h"

unsigned char ucMode, ucStatus, ucTemp;
//*****************************************************************************
//
//!\page TC74_Test TC74_Test
//!
//!<h2>Description</h2>
//! TC74 Test. <br>
//!
//
//*****************************************************************************
 
//*****************************************************************************
//
//! \brief Get the Test description of TC74001 test.
//!
//! \return the desccription of the TC74001 test.
//
//*****************************************************************************
static char* TC74001GetTest(void)
{
    return "TC74 mode test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of TC74001 test.
//!
//! \return None.
//
//*****************************************************************************
static void TC74001Setup(void)
{
    TC74Init(5000);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of TC74001 test.
//!
//! \return None.
//
//*****************************************************************************
static void TC74001TearDown(void)
{
	TC74DeInit();	
}

//*****************************************************************************
//
//! \brief tc74001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void TC74001ModeExecute()
{   
    //
    // Sets TC74 as standby mode.
    //
    TC74ModeSet(TC74_MODE_STANDBY);
    
    //
    // Gets the mode of TC74.
    //
    ucMode = TC74ModeGet();
    
    TestAssert(ucMode == 0x01,
		  "TC74 API \"TC74ModeSet \"or \"TC74ModeGet\"  error!");
    //
    // Sets TC74 as normal mode.
    //
    TC74ModeSet(TC74_MODE_NORMAL);

    //
    // Gets the mode of TC74.
    //
    ucMode = TC74ModeGet();

    TestAssert(ucMode == 0,
		  "TC74 API \"TC74ModeSet \"or \"TC74ModeGet\"  error!");
}


//
// TC74  test case struct.
//
const tTestCase sTestTC74Mode = {
		TC74001GetTest,
		TC74001Setup,
		TC74001TearDown,
		TC74001ModeExecute
};

//*****************************************************************************
//
//! \brief Get the Test description of TC74002 test.
//!
//! \return the desccription of the TC74002 test.
//
//*****************************************************************************
static char* TC74002GetTest(void)
{
    return "TC74 data ready test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of TC74002 test.
//!
//! \return None.
//
//*****************************************************************************
static void TC74002Setup(void)
{
    TC74Init(5000);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of TC74002 test.
//!
//! \return None.
//
//*****************************************************************************
static void TC74002TearDown(void)
{
	TC74DeInit();	
}

//*****************************************************************************
//
//! \brief tc74002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void TC74002DataReadyExecute()
{   
    //
    // Sets TC74 as standby mode.
    //
    TC74ModeSet(TC74_MODE_STANDBY);   
    TestAssert(TC74DATAReady() == 0,
		  "TC74 API \"TC74DATAReady \" error!");
    
	//
    // Sets TC74 as normal mode.
    //
    TC74ModeSet(TC74_MODE_NORMAL);
    TestAssert(TC74DATAReady() == 1,
		  "TC74 API \"TC74DATAReady \" error!");
}

//
// TC74  test case struct.
//
const tTestCase sTestTC74DataReady = {
		TC74002GetTest,
		TC74002Setup,
		TC74002TearDown,
		TC74002DataReadyExecute
};
//
// TC74 test suits.
//
const tTestCase * const psPatternTC74[] =
{
    &sTestTC74Mode,
	&sTestTC74DataReady,
    0
};
