//*****************************************************************************
//
//! @page di_adt75_testcase di_adt75 compare and int mode test
//!
//! File: @ref ADT75test2.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the di_adt75 sub component.<br><br>
//! - \p Board: NUC140 & ADT75ARZ board <br><br>
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
//! - \subpage test_di_adt75_Comod
//! .
//! \file ADT75test2.c
//! \brief di_adt75 test source file
//! \brief di_adt75 test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_adt75.h"
#include "adt75.h"

//*****************************************************************************
//
//!\page test_di_adt75_Comod test_di_adt75_Comod
//!
//!<h2>Description</h2>
//!Test di_adt75 compare and int mode. <br>
//!
//
//*****************************************************************************

//
// Callback funciton
//
static unsigned long ReadOperation(void *pvCBData, unsigned long ulEvent,
                                   unsigned long ulMsgParam, void *pvMsgData)
{
    //
    // A read operation make the OS pin inactive
    //
    ADT75TempReadLDC();
    TestEmitToken('a');
    return 0;
}

//*****************************************************************************
//
//! \brief Get the Test description of di_adt75001 compare mode test.
//!
//! \return the desccription of the di_adt75001 test.
//
//*****************************************************************************
static char* di_adt75001GetTest(void)
{
    return "adt75 [001]: adt75 compare and int mode test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of di_adt75001 test.
//!
//! \return None.
//
//*****************************************************************************
static void di_adt75001Setup(void)
{
    //
    //Set the external 12MHZ clock as system clock 
    //
	xSysCtlClockSet(12000000, xSYSCTL_XTAL_12MHZ | xSYSCTL_OSC_MAIN);
    
    ADT75Init(10000, ADT75_POWER_NORMAL); 
    
    //
    // OS Int mode configure
    //
    ADT75IntModeConfig(ADT75_OPEMODE_CMP);
    
    //
    // OS pin active level is low, a pull-up register should add on this pin.
    //
    ADT75OSActiveLevelConfig(ADT75_OSALERT_LEVEL_LOW);
    
    //
    // Set the Faultqueue is 1
    //
    ADT75FaultQueueConfig(ADT75_FAULTQUE_1);
    
    //
    // Enable the one-shot mode
    //
    ADT75OneShotEnable();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of di_adt75001 test.
//!
//! \return None.
//
//*****************************************************************************
static void di_adt75001TearDown(void)
{
    ADT75IntDisable();
    ADT75DeInit();
}

//*****************************************************************************
//
//! \brief adt75 001 test execute main body.
//!
//! First set the OTI as compare output mode ,then turned to Int mode.When the 
//! temperature up to 30 centigrade, the OTI pin will be low level ,then clear 
//! the ucFlag to end of the while and set the OTI as Int mode. 
//!
//! \return None.
//
//*****************************************************************************
static void di_adt75001Execute(void)
{
    long lTemp;
    unsigned char ucPinValue;
    unsigned char ucFlag;
 
    
    //
    // Configure the setpoint register
    //
    ADT75LowLimitSetLong(25);
    ADT75UpLimitSetLong(28);
    //
    // Config the OTI connected pin as input pin
    //
    xGPIOSPinTypeGPIOInput(ADT75_PIN_OS);
    ucFlag = ADT75RegRead(ADT75_REGISTER_CFG);
    
    ucFlag = 1;
    while(ucFlag)
    {
        ADT75OneShotConvst();
        lTemp = ADT75TempReadLDC();
        ucPinValue = xGPIOSPinRead(ADT75_PIN_OS);
        if(!ucPinValue)
        {
            ucFlag = 0;
            
            //
            // Wait untile the temperature lower than THYST,
            // so the OS pin will return inactive.
            //
            while(lTemp >= 25)
            {
                ADT75OneShotConvst();    
                lTemp = ADT75TempReadLDC();
            }
            
            //
            // Change the mode to int mode,the 
            //
            ADT75IntModeConfig(ADT75_OPEMODE_INT);
            
            // 
            // A read function to clear the OTI pin
            //
            lTemp = ADT75TempReadLDC();
            
        }  
    }

    //
    // Enable the OS connected pin interrupt
    //
    ADT75IntEnable();
    
    //
    // Install the interrupt callback function
    //
    ADT75IntCallbackInit(ReadOperation);
    
    //
    // Wait the temperature up to 28¡æ£¬ so the OS pin will active again
    //
    while(lTemp <= 28)
    {
        ADT75OneShotConvst();  
        
        //
        // Delay some time for the interrupt happen before OS active has been
        // clear
        // 
        xSysCtlDelay(100);
        lTemp = ADT75TempReadLDC();
    } 
    
    xSysCtlDelay(10000);
    TestAssertQ("a", "OTI INT mode test fail");   
}

//
// di_adt75 register test case struct.
//
const tTestCase sTestdi_adt75_Comod = {
    di_adt75001GetTest,
    di_adt75001Setup,
    di_adt75001TearDown,
    di_adt75001Execute
};

//
// xi2c test suits.
//
const tTestCase * const psPatternDI_ADT75002[] =
{
    &sTestdi_adt75_Comod,
    0
};
