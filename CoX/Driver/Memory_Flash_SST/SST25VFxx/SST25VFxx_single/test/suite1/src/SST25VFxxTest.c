//*****************************************************************************
//
//! @page SST25VFxx_testcase SST25VFxx function test
//!
//! File: @ref SST25VFxxTest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the SST25VFxx sub component.<br><br>
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
//! - \subpage test_SST25VFxx_Function
//! .
//! \file SST25VFxxTest.c
//! \brief SST25VFxx test source file
//! \brief SST25VFxx test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "SST25VFxx.h"

unsigned long ucIDcode;
#define BUFFER_LEN     21
unsigned char ucBuffer[BUFFER_LEN];

//*****************************************************************************
//
//! \brief Get the Test description of SST25VFxx Function test.
//!
//! \return the desccription of the SST25VFxx test.
//
//*****************************************************************************
static char* SST25VFxxGetTest(void)
{

    return "SST25VFxx Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of SST25VFxx test.
//!
//! \return None.
//
//*****************************************************************************
static void SST25VFxxSetup(void)
{
    unsigned long i;
    //
    // Set SysClk 50MHz using Extern 12M oscillator
    //

    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

    SST25VFxxInit(2000000);
    for(i=0;i<BUFFER_LEN;i++)
    {
        ucBuffer[i] = i;
    }
}

//*****************************************************************************
//
//! \brief something should do after the test execute of SST25VFxx test.
//!
//! \return None.
//
//*****************************************************************************
static void SST25VFxxTearDown(void)
{
     SST25VFxxDisable();
}

//*****************************************************************************
//
//! \brief SST25VFxx test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void SST25VFxxExecute(void)
{
    unsigned long i;
    SST25VFxxInit(20000000);
	ucIDcode = 0xAB;
	ucIDcode = SST25VFxxIDGet(0x10);
	TestAssert((ucIDcode == 0xBF41),"\"error!");
//	printf("ucIDcode = 0x%X\r\n",ucIDcode);
	ucIDcode = SST25VFxxJedecIDGet();
	TestAssert((ucIDcode == 0xBF2541),"\"error!");
//	printf("ucIDcode = 0x%X\r\n",ucIDcode);
	ucIDcode = SST25VFxxStatusRegRead();
	TestAssert((ucIDcode == 0x1C),"\"error!");
//	printf("ucIDcode = 0x%X\r\n",ucIDcode);
	SST25VFxxWaitNotBusy();
//	printf("Not Busy\r\n");

	SST25VFxxWriteEnable();
	ucIDcode = SST25VFxxStatusRegRead();
	TestAssert((ucIDcode == 0x1E),"\"error!");
//	printf("ucIDcode = 0x%X\r\n",ucIDcode);

	SST25VFxxWriteDisable();
	ucIDcode = SST25VFxxStatusRegRead();
	TestAssert((ucIDcode == 0x1C),"\"error!");
//	printf("ucIDcode = 0x%X\r\n",ucIDcode);

	SST25VFxxChipErase();
//	printf("SST25VFxxChipErase \r\n");

	SST25VFxxWrite(ucBuffer, 0, BUFFER_LEN);
//	printf("SST25VFxxWrite(ucBuffer, 0, BUFFER_LEN) \r\n");

	for(i=0;i<BUFFER_LEN;i++)
	{
		ucBuffer[i] = 0;
	}
//	printf("ucBuffer clear \r\n");
	for(i=0;i<BUFFER_LEN;i++)
	{
		TestAssert((ucBuffer[i] == 0),"\"error!");
//		printf("ucBuffer[%d] = 0x%X\r\n",i,ucBuffer[i]);
	}

	SST25VFxxDataRead(ucBuffer, 0, BUFFER_LEN);
//	printf("SST25VFxxDataRead(ucBuffer, 0, BUFFER_LEN) \r\n");

	for(i=0;i<BUFFER_LEN;i++)
	{
		TestAssert((ucBuffer[i] == i),"\"error!");
//		printf("ucBuffer[%d] = 0x%X\r\n",i,ucBuffer[i]);
	}
//	printf("float=%10.9f\r\n",3.1415926);

    
}
//
// SST25VFxx Function test case struct.
//
const tTestCase sTestSST25VFxxFunction = {
        SST25VFxxGetTest,
        SST25VFxxSetup,
        SST25VFxxTearDown,
        SST25VFxxExecute
};

//
// SST25VFxx test suits.
//
const tTestCase * const psPatternSST25VFxxTest[] =
{
    &sTestSST25VFxxFunction,
    0
};
