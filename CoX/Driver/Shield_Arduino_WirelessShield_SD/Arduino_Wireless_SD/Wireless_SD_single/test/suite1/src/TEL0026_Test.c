//*****************************************************************************
//
//! @page TEL0026_testcase TEL0026 function test
//!
//! File: @ref TEL0026.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the TEL0026 sub component.<br><br>
//! - \p Board: STM32 <br><br>
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
//! - \subpage test_TEL0026_Function
//! .
//! \file TEL0026.c
//! \file hw_TEL0026.h
//! \brief TEL0026 test source file
//! \file TEL0026.h
//! \brief TEL0026 test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "hw_TEL0026.h"
#include "TEL0026.h"

#define Length 64
unsigned char ucDataBuf[Length];

//*****************************************************************************
//
//! \brief Get the Test description of TEL0026 Function test.
//!
//! \return the desccription of the TEL0026 test.
//
//*****************************************************************************
static char* TEL0026GetTest(void)
{

    return "TEL0026 Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of TEL0026 test.
//!
//! \return None.
//
//*****************************************************************************
static void TEL0026Setup(void)
{

}

//*****************************************************************************
//
//! \brief something should do after the test execute of TEL0026 test.
//!
//! \return None.
//
//*****************************************************************************
static void TEL0026TearDown(void)
{

}

//*****************************************************************************
//
//! \brief TEL0026 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void TEL0026Execute(void)
{
	unsigned char ucRes;

	ucRes = BTInit();
    TestAssert((ucRes == BT_ERR_OK),
                 "TEL0026 API \"BTInit()\"error!");
    
    ucRes = BTUartParamGet(ucDataBuf);
    TestAssert((ucRes == BT_ERR_OK),
                  "TEL0026 API \"BTUartParamGet()\"error!");

    ucRes = BTUartParamSet(115200, 0, 1);
    TestAssert((ucRes == BT_ERR_OK),
                   "TEL0026 API \"BTUartParamSet()\"error!");

    ucRes = BTPasswordGet(ucDataBuf);
    TestAssert((ucRes == BT_ERR_OK),
                   "TEL0026 API \"BTPasswordGet()\"error!");

    ucRes = BTPasswordSet("3333");
    TestAssert((ucRes == BT_ERR_OK),
                   "TEL0026 API \"BTPasswordSet()\"error!");

    ucRes = BTDeviceNameGet(ucDataBuf);
    TestAssert((ucRes == BT_ERR_OK),
                   "TEL0026 API \"BTDeviceNameGet()\"error!");

    ucRes = BTDeviceNameSet("Bluetooth_Bee");
    TestAssert((ucRes == BT_ERR_OK),
                   "TEL0026 API \"BTDeviceNameSet()\"error!");

    ucRes = BTVersionGet(ucDataBuf);
    TestAssert((ucRes == BT_ERR_OK),
                   "TEL0026 API \"BTVersionGet()\"error!");

    ucRes = BTDeviceRoleSet(BT_ROLE_SLAVE_LOOP);
    TestAssert((ucRes == BT_ERR_OK),
                   "TEL0026 API \"BTDeviceRoleSet()\"error!");

    ucRes = BTDeviceRoleGet();
    TestAssert((ucRes > 33),
                   "TEL0026 API \"BTDeviceRoleSet()\"error!");

    ucRes = BTInqModeSet(1, 10, 30);
    TestAssert((ucRes == BT_ERR_OK),
                   "TEL0026 API \"BTInqModeSet()\"error!");

    ucRes = BTInqModeGet(ucDataBuf);
    TestAssert((ucRes == BT_ERR_OK),
                   "TEL0026 API \"BTInqModeGet()\"error!");
    
}
//
// TEL0026 Function test case struct.
//
const tTestCase sTestTEL0026Function = {
        TEL0026GetTest,
        TEL0026Setup,
        TEL0026TearDown,
        TEL0026Execute
};

//
// TEL0026 test suits.
//
const tTestCase * const psPatternTEL0026Test[] =
{
    &sTestTEL0026Function,
    0
};
