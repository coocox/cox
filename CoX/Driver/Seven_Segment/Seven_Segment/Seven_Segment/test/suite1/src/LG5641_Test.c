//*****************************************************************************
//
//! @page LG5641_testcase LG5641 function test
//!
//! File: @ref LG5641Test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the LG5641 sub component.<br><br>
//! - \p Board: STM32F107 <br><br>
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
//! - \subpage test_LG5641_Function
//! .
//! \file LG5641_Test.c
//! \brief LG5641 test source file
//! \brief LG5641 test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "Seven_Segment.h"

//*****************************************************************************
//
//! \brief Get the Test description of LG5641 Function test.
//!
//! \return the desccription of the LG5641 test.
//
//*****************************************************************************
static char* LG5641GetTest(void)
{
    return "LG5641 Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of LG5641 test.
//!
//! \return None.
//
//*****************************************************************************
static void LG5641Setup(void)
{
    SevenSegmentInit();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of LG5641 test.
//!
//! \return None.
//
//*****************************************************************************
static void LG5641TearDown(void)
{
}

//*****************************************************************************
//
//! \brief LG5641 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void LG5641Execute(void)
{
    unsigned long i;
    while(1)
    {
      for(i = 200; i > 0; i--)
      {
        SevenSegmentScan(1234,DECIMAL);
      }
      for(i = 200; i > 0; i--)
      {
        SevenSegmentScan(5678,DECIMAL);
      }
      for(i = 200; i > 0; i--)
      {
        SevenSegmentScan(0x90aab,HEXADECIMAL);
      }
      for(i = 200; i > 0; i--)
      {
        SevenSegmentScan(0xcdef,HEXADECIMAL);
      }
    }
}

//
// LG5641 Function test case struct.
//
const tTestCase sTestLG5641Function = {
    LG5641GetTest,	
    LG5641Setup,
    LG5641TearDown,
    LG5641Execute
};

//
// LG5641 test suits.
//
const tTestCase * const psPatternLG5641Test[] =
{
    &sTestLG5641Function,
    0
};

