//*****************************************************************************
//
//! @page sdcard_testcase sdcard register test
//!
//! File: \ref test1.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the lcd sub component.<br><br>
//! - xx
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
//! - \subpage Test001
//! .
//
//*****************************************************************************

#include "test.h"
#include "sdcard.h"

//*****************************************************************************
//
//!\page Test001 Test001
//!
//!<h2>Description</h2>
//!Test 001. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Get the Test description of the test.
//!
//! \return the desccription of the test.
//
//*****************************************************************************
static char* Test001GetTest(void)
{
    return "Test [001]: ";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of the test.
//!
//! \return None.
//
//*****************************************************************************
static void Test001Setup(void)
{

}

//*****************************************************************************
//
//! \brief something should do after the test execute of the test.
//!
//! \return None.
//
//*****************************************************************************
static void Test001TearDown(void)
{

}

//*****************************************************************************
//
//! \brief 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void Test001Execute(void)
{   
    unsigned long i;
    unsigned char ucRet = 0;
    static unsigned char pucBuf[1024] = {0};
    
    //
    // SD Card Init
    //
    ucRet = SDInit();
    TestAssert(ucRet == SD_NO_ERR, "SDCard Init Error");
    
    //
    // Fill the test buffer(1 block)
    //
    for(i = 0; i < 512; i++)
    {
        pucBuf[i] = i % 256;
    }
    
    //
    // write a block to the card 
    //
    ucRet = SDBlockWrite(pucBuf, 0);
    TestAssert(ucRet == SD_NO_ERR, "Error in Block Write");
    
    //
    // Re-init the test buffer to 0
    //
    for(i = 0; i < 512; i++)
    {
        pucBuf[i] = 0;
    }
    //
    // Read 1 block from the card
    //    
    ucRet = SDBlockRead(pucBuf, 0);
    TestAssert(ucRet == SD_NO_ERR, "Block Read Error");
    
    //
    // Check Write == Read?
    //
    for(i = 0; i < 512; i++)
    {
        TestAssert(pucBuf[i] == i % 256, " Write != Read");
    }  
  
    //
    // Fill the buffer
    //    
    for(i = 0; i < 1024; i++)
    {
        pucBuf[i] = (255 - (i % 256));
    }      
    
    //
    // Write 2 block to the card
    //
    ucRet = SDMultiBlockWrite(pucBuf, 1, 2);
    TestAssert(ucRet == SD_NO_ERR, "Multi Block Write Error");
    
    //
    // Clear the test buffer
    //
    for(i = 0; i < 1024; i++)
    {
        pucBuf[i] = 0;
    }
    
    //
    // Read 2 block from the card
    //
    ucRet = SDMultiBlockRead(pucBuf, 1, 2);
    TestAssert(ucRet == SD_NO_ERR, "Multi Block Read Error");
    
    //
    // Check Multi Write == Multi Read?
    //
    for(i = 0; i < 1024; i++)
    {
        TestAssert(pucBuf[i] == (255 - (i % 256)), "Multi Read != Write");
    } 

    for(i = 0; i < 512; i++)
    {
        pucBuf[i] = i % 256;    
    }
    
    for(i = 512; i < 1024; i++)
    {
        pucBuf[i] = 0xFF;   
    }
    //
    // Erase EraseUnit * N
    //
    ucRet = SDBlockWrite(pucBuf, 0);
    TestAssert(ucRet == SD_NO_ERR, "");
    
    ucRet = SDBlockWrite(pucBuf, 65);
    TestAssert(ucRet == SD_NO_ERR, "");
    
    ucRet = SDBlockErase(0, 65);
    TestAssert(ucRet == SD_NO_ERR, "Erase Error");
    
    //
    // Check block 0 if has been erased
    //
    ucRet = SDBlockRead(&pucBuf[512], 0);
    for(i = 0; i < 512; i++)
    {
        TestAssert(pucBuf[512 + i] == 0x00, "");
    }

    //
    // Check block 64 if has been erased
    //    
    ucRet = SDBlockRead(&pucBuf[512], 64);
    for(i = 0; i < 512; i++)
    {
        TestAssert(pucBuf[512 + i] == 0x00, "");
    }
    
    //
    // Check block 65 if has been error erased
    //     
    ucRet = SDBlockRead(&pucBuf[512], 65);
    for(i = 0; i < 512; i++)
    {
        TestAssert(pucBuf[512 + i] == pucBuf[i], "");
    }
    
}

//
// test case 001 struct.
//
const tTestCase sTest001 = {
		Test001GetTest,
		Test001Setup,
		Test001TearDown,
		Test001Execute
};

//
// sdcard test suits.
//
const tTestCase * const psPattern001[] =
{
    &sTest001,
    0
};

