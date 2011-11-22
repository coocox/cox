//*****************************************************************************
//
//! @page W25Xxx test
//!
//! File: @ref w25xxTest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for W25Xxx Driver.<br><br>
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
//! - \subpage W25Xxx
//! .
//! \file w25xxTest.c
//! \brief w25xxTest test source file
//! \brief w25xxTest test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "w25x.h"

unsigned char ucWriteData[] = "I stand on this rostrum with a sense of deep hum \
humility in the weight of those great American architects of our history who ha \
pride in the reflection that this home of legislative debate represents human l \
the purest form yet devised. Here are centered the hopes and aspirations and fa \
entire human race. I do not stand here as advocate for any partisan cause, for  \
are fundamental and reach quite beyond the realm of partisan consideration. The \
resolved on the highest plane of national interest if our course is to prove so \
our future protected. I trust, therefore, that you will do me the justice of re \
that which I have to say as solely expressing the considered viewpoint of a fel \
humility in the weight of those great American architects of our history who ha \
pride in the reflection that this home of legislative debate represents human l \
Do you love it,Put all eggs in one basket?Fall in love at first sight!";

#define Length sizeof(ucWriteData)

unsigned char ucReadData[Length];
unsigned long i;

//*****************************************************************************
//
//! \brief Get the Test description of W25Xxx test.
//!
//! \return the desccription of the W25Xxx test.
//
//*****************************************************************************
static char* W25X001GetTest(void)
{
    return "W25Xxx, 001, W25Xxx test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of W25Xxx test.
//!
//! \return None.
//
//*****************************************************************************
static void W25X001Setup(void)
{

    W25XInit(2000000);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of W25Xxx test.
//!
//! \return None.
//
//*****************************************************************************
static void W25X001TearDown(void)
{   

    //
    // Disable SPI
    //    
    W25XDeInit();;  
}

//*****************************************************************************
//
//! \brief W25Xxx 001 test of W25Xxx Read and Write test .
//!
//! \return None.
//
//*****************************************************************************
static void W25XRWTest(void)
{
    W25XChipErase();
    W25XWrite(ucWriteData, 0, Length);
    xSysCtlDelay(500000);
    W25XRead(ucReadData, 0, Length);
    for(i = 0; i < Length; i++)
    {
        TestAssert((ucWriteData[i] == ucReadData[i]), "w25xxx API error!");
    }

}

//*****************************************************************************
//
//! \brief W25Xxx 001 test of W25Xxx erase chip test .
//!
//! \return None.
//
//*****************************************************************************
static void W25XEraseChipTest(void)
{
    //
    // Erase all chip
    //
    W25XChipErase();
    W25XRead(ucReadData, 0, Length);
    for(i = 0; i < Length; i++)
    {
        TestAssert((0xFF == ucReadData[i]), "w25xxx API error!");
    }   
}

//*****************************************************************************
//
//! \brief W25Xxx 001 test of W25Xxx read ID test .
//!
//! \return None.
//
//*****************************************************************************
static void W25XReadIDTest(void)
{
    unsigned short usID;
    usID = W25XIDcodeGet();
    TestAssert((usID == 0xEF14), "w25xxx API error!");
}


//*****************************************************************************
//
//! \brief W25Xxx 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void W25X001Execute(void)
{
    W25XReadIDTest();
    W25XRWTest();
    W25XEraseChipTest();
}

//
// W25Xxx test case struct.
//
const tTestCase sTestW25X = {
    W25X001GetTest,
    W25X001Setup,
    W25X001TearDown,
    W25X001Execute
};

//
// W25Xxx test suits.
//
const tTestCase * const psPatternW25Xxx[] =
{
    &sTestW25X,
    0
};
