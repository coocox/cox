//*****************************************************************************
//
//! @page xwdt_testcase xwdt register test
//!
//! File: @ref wdttest00.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xwdt sub component.<br><br>
//! - \p Board: HT32F175x <br><br>
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
//! - \subpage test_xgpio_register
//! .
//! \file wdttest00.c
//! \brief xwdt test source file
//! \brief xwdt test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_wdt.h"
#include "xwdt.h"

//*****************************************************************************
//
//!\page test_xwdt_register test_xwdt_register
//!
//!<h2>Description</h2>
//!Test xwdt register. <br>
//!
//
//*****************************************************************************
unsigned long ulWDTInterval[] = {64, 65, 66, 78, 96, 110, 116, 127};
unsigned long ulIWDTInterval[] = {0xFFE, 65, 125, 242, 587, 1024, 5874, 8191};

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
//! \brief Get the Test description of xwdt001 register test.
//!
//! \return the desccription of the xwdt001 test.
//
//*****************************************************************************
static char* xwdt001GetTest(void)
{
    return "wdt, 001, wdt register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xwdt001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt001Setup(void)
{
    //
    // Enable WDT
    //
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_WWDG);
    SysCtlPeripheralClockSourceSet(SYSCTL_IWDG_LSI, 1);
}


//*****************************************************************************
//
//! \brief  Wdt api wdt's timer interval configure test.
//!
//! \return None.
//
//*****************************************************************************
static void wdt_WDTimerInit_test(void)
{
    unsigned long i,ulTemp;

    WDTimerInit(0x7F);
/*
    for(i=0; i<8; i++)
    {
        WDTimerWindowValueSet(ulWDTInterval[i]);
        ulTemp = xHWREG(WWDG_CFR) & WWDG_CFR_W_M;
        TestAssert(( ulWDTInterval[i] == ulTemp), "WDT API error!");
    }
*/
    IWDGTimerPrescalerSet(IWDT_PRESCALER_256);
            IWDGTimerInit(0x8FE);
        IWDGTimerRestart();
        IWDGTimerStart();
    for(i=0; i<8; i++)
    {

        IWDGTimerRestart();
        ulTemp = xHWREG(IWDG_RLR) & IWDG_RLR_RL_M;
        PrintN(ulTemp);
//        TestAssert(( 0xFFE == ulTemp), "WDT API error!");
    }
    //
    // Enable WWDG
    //
//    WWDGEnable(WWDG_BASE);
}

//*****************************************************************************
//
//! \brief  Wdt api wdt interrupt enable test.
//!
//! \return None.
//
//*****************************************************************************
static void wdt_WDTimerIntEnable_test(void)
{
    unsigned long ulRegVal;
    
    WDTimerIntEnable();
    
    ulRegVal = xHWREG(WWDG_CFR);
    
    TestAssert(WWDG_CFR_EWI_EN == (ulRegVal & WWDG_CFR_EWI_EN), "WDT API error!");
}

//*****************************************************************************
//
//! \brief  Wdt api wdt Prescaler Set test.
//!
//! \return None.
//
//*****************************************************************************
static void wdt_WDTimerPrescalerSetEnable_test(void)
{
    unsigned long ulPreArray[] = {WDT_PRESCALER_1, WDT_PRESCALER_2, 
                                  WDT_PRESCALER_4, WDT_PRESCALER_8};
    unsigned long ulRegVal, i;
    
    for(i=0; i<4; i++)
    {
        WDTimerPrescalerSet(ulPreArray[i]);
        ulRegVal = xHWREG(WWDG_CFR);
        TestAssert(ulPreArray[i] == (ulRegVal&WWDG_CFR_WDGTB_M), "WDT API error!");
    }
}

//*****************************************************************************
//
//! \brief xwdt001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt001Execute(void)
{
    wdt_WDTimerInit_test();
//    wdt_WDTimerIntEnable_test();
//    wdt_WDTimerPrescalerSetEnable_test();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xwdt001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt001TearDown(void)
{

    SysCtlPeripheralDisable(SYSCTL_PERIPH_WWDG);
}

//
// wdt001 register test case struct.
//
const tTestCase sTestXWdt001Register = {
    xwdt001GetTest,	
    xwdt001Setup,
    xwdt001TearDown,
    xwdt001Execute
};

//
// wdt test suits.
//
const tTestCase * const psPatternXwdt00[] =
{
    &sTestXWdt001Register,
    0
};
