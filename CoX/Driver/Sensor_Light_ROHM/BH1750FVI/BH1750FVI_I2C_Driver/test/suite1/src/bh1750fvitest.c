//*****************************************************************************
//
//! @page BH1750FVI test
//!
//! File: @ref BH1750FVItest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for BH1750FVI Driver.<br><br>
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
//! - \subpage BH1750FVI
//! .
//! \file BH1750FVItest.c
//! \brief BH1750FVI test source file
//! \brief BH1750FVI test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "hw_BH1750FVI.h"
#include "BH1750FVI.h"

//*****************************************************************************
//
//! \brief Prints a decimal unsigned number.
//!
//! \param n is the number to be printed
//!
//! \details Prints a decimal unsigned number.
//!
//! \return None.
//
//*****************************************************************************
static 
void PrintN(unsigned long n)
{
    char buf[16], *p;

    if (n == 0)
    {
        TestIOPut('0');
    }
    else
    {
        p = buf;
        while (n != 0)
        {
            *p++ = (n % 10) + '0';
            n /= 10;
        }

        while (p > buf)
            TestIOPut(*--p);
    }
}


//*****************************************************************************
//
//! \brief Get the Test description of BH1750FVI  test.
//!
//! \return the desccription of the BH1750FVI test.
//
//*****************************************************************************
static char* BH1750FVI001GetTest(void)
{
    return "BH1750FVI, 001, BH1750FVI test";
}


//*****************************************************************************
//
//! \brief something should do before the test execute of BH1750FVI test.
//!
//! \return None.
//
//*****************************************************************************
static void BH1750FVI001Setup(void)
{

}


//*****************************************************************************
//
//! \brief something should do after the test execute of BH1750FVI test.
//!
//! \return None.
//
//*****************************************************************************
static void BH1750FVI001TearDown(void)
{   

}

//*****************************************************************************
//
//! \brief BH1750FVI 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void BH1750FVI001Execute(void)
{

}

//
// BH1750FVI test case struct.
//
const tTestCase sTestBH1750FVI = {
    BH1750FVI001GetTest,
    BH1750FVI001Setup,
    BH1750FVI001TearDown,
    BH1750FVI001Execute
};

//
// BH1750FVI test suits.
//
const tTestCase * const psPatternBH1750FVI[] =
{
    &sTestBH1750FVI,
    0
};
