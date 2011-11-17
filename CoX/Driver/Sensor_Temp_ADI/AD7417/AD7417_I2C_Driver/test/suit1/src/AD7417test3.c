//*****************************************************************************
//
//! @page di_ad7417arz_testcase di_ad7417arz triger mode test
//!
//! File: @ref AD7417test3.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the di_ad7417arz sub component.<br><br>
//! - \p Board: NUC140 & AD7417ARZ board <br><br>
//! - \p Last-Time(about): 60s <br><br>
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
//! - \subpage test_di_ad7417_triggermode
//! .
//! \file AD7417test3.c
//! \brief ad7417 test source file
//! \brief ad7417 test header file <br>
//
//*****************************************************************************
#include "test.h"
#include "xhw_ad7417.h"
#include "ad7417.h"

//*****************************************************************************
//
//!\page test_di_ad7417arz_trigermode test_di_ad7417arz_trigermode
//!
//!<h2>Description</h2>
//!Test di_ad7417arz triger mode. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Get the Test description of ad7417arz001 compare mode test.
//!
//! \return the desccription of the ad7417arz001 test.
//
//*****************************************************************************
static char* di_ad7417arz001GetTest(void)
{
    return "di_ad7417arz [001]: di_ad7417 triger mode test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of di_ad7417arz001 test.
//!
//! \return None.
//
//*****************************************************************************
static void di_ad7417arz001Setup(void)
{
    //
    //Set the external 12MHZ clock as system clock 
    //
    xSysCtlClockSet(12000000, SYSCLK_PWRCON_XTL12M_EN | xSYSCTL_OSC_MAIN);
    
    //
    // AD7417 device init
    //
    AD7417Init(10000, AD7417_Triger_Enable); 
   
}

//*****************************************************************************
//
//! \brief something should do after the test execute of di_ad7417arz001 test.
//!
//! \return None.
//
//*****************************************************************************
static void di_ad7417arz001TearDown(void)
{
    AD7417DeInit();
}

//*****************************************************************************
//
//! \brief di_ad7417arz 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void di_ad7417arz001Execute(void)
{
    unsigned long ulTemp;
    unsigned char ucFlag = 1;
	int i;
    
    //
    // Configure the setpoint register
    //
    AD7417LowLimitSetLong(31);
    AD7417UpLimitSetLong(35);
    
    //
    // Set the PC4 as /convst pin ,out put, low level
    //
    
    xGPIOSPinTypeGPIOOutput(AD7417_CONVST_PIN);
    xGPIOSPinWrite(AD7417_CONVST_PIN, 0);
    
    while(ucFlag)
    {
        //
        // Triger to CONVST
        //  
        AD7417TriggerConvst();
        
        ulTemp = AD7417TempReadLDC();
        for(i = 0; i < 10000; i++);
        if(ulTemp >= 35)
        {
            // end of the while
            ucFlag = 0;
        } 
    }    
}

//
// di_ad7417arz register test case struct.
//
const tTestCase sTestdi_ad7417arz_triggermode = {
            di_ad7417arz001GetTest,
            di_ad7417arz001Setup,
            di_ad7417arz001TearDown,
            di_ad7417arz001Execute
};

//
// xi2c test suits.
//
const tTestCase * const psPatternDI_AD7417ARZ003[] =
{
    &sTestdi_ad7417arz_triggermode,
    0
};


