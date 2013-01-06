//*****************************************************************************
//
//! @page DotMatrix_testcase DotMatrix function test
//!
//! File: @ref DotMatrix_Test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the DotMatrix sub component.<br><br>
//! - \p Board: Cookie M0516 <br><br>
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
//! - \subpage test_DM163_Function
//! .
//! \file DotMatrix_Test.c
//! \brief Dot Matrix test source file
//! \brief Dot Matrix test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "Dot_Matrix.h"

#define delay 0x1fffff

//*****************************************************************************
//
//! \brief Get the Test description of DotMatrix Function test.
//!
//! \return the description of the DotMatrix test.
//
//*****************************************************************************
static char* DotMatrixGetTest(void)
{
    return "8*8 Color Shield Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of DotMatrix test.
//!
//! \return None.
//
//*****************************************************************************
static void DotMatrixSetup(void)
{
    DM163PinInit();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of DotMatrix test.
//!
//! \return None.
//
//*****************************************************************************
static void DotMatrixTearDown(void)
{
}

//*****************************************************************************
//
//! \brief DotMatrix test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void DotMatrixExecute(void)
{
    long j;
    DotMatrixSetGamma();
    DotMatrixOpenLine(9);
    DotMatrixScanTimerInit(12000000, 100);

    while(1)
    {
    	DotMatrixShowChar('A', 255, 0, 0, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('B', 0, 255, 0, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('C', 0, 0, 255, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('D', 255, 255, 255, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('E', 0, 255, 255, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('F', 255, 255, 0, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('G', 255, 0, 255, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('H', 255, 127, 0, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('I', 127, 255, 0, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('J', 127, 0, 255, 0);
        xSysCtlDelay(delay);
        DotMatrixShowChar('K', 255, 127, 127,0);
        xSysCtlDelay(delay);

        //
        //! Move left
        //
        for(j = -7; j < 8; j++)
        {
            DotMatrixShowChar('S', 255, 0, 0, j);
            xSysCtlDelay(0x1ffff);
        }

        //
        //! Move right
        //
        for(j = 7; j > -8; j--)
        {
            DotMatrixShowChar('M', 0, 0, 255, j);
            xSysCtlDelay(0x1ffff);
        }
    }
}

//
// DotMatrix Function test case struct.
//
const tTestCase sTestDotMatrixFunction = {
    DotMatrixGetTest,	
    DotMatrixSetup,
    DotMatrixTearDown,
    DotMatrixExecute
};

//
// DotMatrix test suits.
//
const tTestCase * const psPatternDotMatrixTest[] =
{
    &sTestDotMatrixFunction,
    0
};

