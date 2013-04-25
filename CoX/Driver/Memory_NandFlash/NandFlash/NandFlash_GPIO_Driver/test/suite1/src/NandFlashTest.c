//*****************************************************************************
//
//! @page NandFlash_testcase NandFlash function test
//!
//! File: @ref NandFlashTest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the NandFlash sub component.<br><br>
//! - \p Board: STM32F103 <br><br>
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
//! - \subpage test_NandFlash_Function
//! .
//! \file NandFlashTest.c
//! \brief NandFlash test source file
//! \brief NandFlash test header file <br>
//! \brief Tested NandFlash Type is K9F1G08U0B
//
//*****************************************************************************

#include "test.h"
#include "NandFlash.h"

#define Length 2048
unsigned char ucBuffer[Length];;
unsigned long ulPageAddr = 3 + 10 * NF_BLOCK_SIZE / NF_PAGE_SIZE;
unsigned long ulByteAddress = 3 * NF_PAGE_SIZE + 10 * NF_BLOCK_SIZE + 256;

//*****************************************************************************
//
//! \brief Get the Test description of NandFlash Function test.
//!
//! \return the desccription of the NandFlash test.
//
//*****************************************************************************
static char* NandFlashGetTest(void)
{

    return "NandFlash Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of NandFlash test.
//!
//! \return None.
//
//*****************************************************************************
static void NandFlashSetup(void)
{
    NFInit();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of NandFlash test.
//!
//! \return None.
//
//*****************************************************************************
static void NandFlashTearDown(void)
{
}

//*****************************************************************************
//
//! \brief NandFlash test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void NandFlashExecute(void)
{
    unsigned long i;
    NFBlockErase(10);
    NFPageRead(ulPageAddr, ucBuffer);
    for(i=0;i<Length;i++)
    TestAssert((ucBuffer[i] == 0xFF), 
               "NandFlash API \"NFBlockErase() or NFPageRead()\"error!");
			   
    for(i=0;i<Length;i++)
	    ucBuffer[i] = i % 256;
    NFPageWrite(ulPageAddr, ucBuffer);
	for(i=0;i<Length;i++)
	    ucBuffer[i] = 0;
	NFPageRead(ulPageAddr, ucBuffer);
    for(i=0;i<Length;i++)
    TestAssert((ucBuffer[i] == (i%256)), 
               "NandFlash API \"NFPageWrite()\"error!");
			   
    for(i=0;i<Length;i++)
	    ucBuffer[i] = 0;
    NFBytesRead(ulByteAddress, ucBuffer, 256);
    for(i=0;i<256;i++)
    TestAssert((ucBuffer[i] == (i%256)), 
               "NandFlash API \"NFBytesRead()\"error!");	

    NFPageCopy(ulPageAddr, ulPageAddr+2);
	for(i=0;i<Length;i++)
	    ucBuffer[i] = 0;
	NFPageRead(ulPageAddr+2, ucBuffer);
    for(i=0;i<Length;i++)
    TestAssert((ucBuffer[i] == (i%256)), 
               "NandFlash API \"NFPageCopy()\"error!");
}
//
// NandFlash Function test case structure.
//
const tTestCase sTestNandFlashFunction = {
    NandFlashGetTest,	
    NandFlashSetup,
    NandFlashTearDown,
    NandFlashExecute
};

//
// NandFlash test suits.
//
const tTestCase * const psPatternNandFlashTest[] =
{
    &sTestNandFlashFunction,
    0
};
