//*****************************************************************************
//
//! @page ADT7301 test
//!
//! File: @ref adt7301test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for ADT7301 Driver.<br><br>
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
//! - \subpage ADT7301
//! .
//! \file adt7301test.c
//! \brief ADT7301 test source file
//! \brief ADT7301 test header file <br>
//
//*****************************************************************************

#include "adt7301.h"
#include "test.h"

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
//! \brief Get the Test description of ADT7301  test.
//!
//! \return the desccription of the ADT7301 test.
//
//*****************************************************************************
static char* ADT7301001GetTest(void)
{
    return "ADT7301, 001, ADT7301 test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of ADT7301.
//!
//! \return None.
//
//*****************************************************************************
static void ADT7301001Setup(void)
{
    ADT7301Init(200000);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of ADT7301.
//!
//! \return None.
//
//*****************************************************************************
static void ADT7301001TearDown(void)
{   
 
    ADT7301DeInit();
}

//*****************************************************************************
//
//! \brief ADT7301 001 test of ADT7301 Normal mode test .
//!
//! \return None.
//
//*****************************************************************************
static void ADT7301NormalModeTest(void)
{
    short sTemperValue,i;
    
    ADT7301Configure(ADT7301_MODE_NORMAL);
    
    for(i = 0; i < 20; i++)
    {
        sTemperValue = ADT7301TemperReadDec();
        PrintN(sTemperValue);
        TestIOPut('\n');
        TestIOPut('\r');
    }	      
}

//*****************************************************************************
//
//! \brief ADT7301 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void ADT7301001Execute(void)
{
    ADT7301NormalModeTest();
}

//
// ADT7301 test case struct.
//
const tTestCase sTestADT7301 = {
    ADT7301001GetTest,
    ADT7301001Setup,
    ADT7301001TearDown,
    ADT7301001Execute
};

//
// ADT7301 test suits.
//
const tTestCase * const psPatternADT7301[] =
{
    &sTestADT7301,
    0
};
