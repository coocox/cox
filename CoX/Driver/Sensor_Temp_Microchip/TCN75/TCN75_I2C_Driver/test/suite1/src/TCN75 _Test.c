//*****************************************************************************
//
//! @page TCN75_testcase TCN75 test
//!
//! File: @ref TCN75_Test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the TCN75 sub component.<br><br>
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
//! - \subpage test_TCN75
//! .
//! \file TCN75_Test.c
//! \brief TCN75 test source file
//! \brief TCN75 test header file <br>
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xi2c.h"
#include "TCN75.h"
#include "xhw_TCN75.h"
#include "test.h"
#include "testcase.h"
unsigned long uli, ulj;
unsigned long Test_CMP (void *pvCBData, 
                                   unsigned long ulEvent,
                                   unsigned long ulMsgParam,
                                   void *pvMsgData)
{
	xGPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_12, 0);

	uli = 1;

    return 0;
}
unsigned long Test_Int (void *pvCBData, 
                                   unsigned long ulEvent,
                                   unsigned long ulMsgParam,
                                   void *pvMsgData)
{
    TestEmitToken('a');
	TCN75RegRead(TCN75_TEMP);
    return 0;
}
//*****************************************************************************
//
//!\page TCN75_Test TCN75_Test
//!
//!<h2>Description</h2>
//! TCN75 Test. <br>
//!
//
//*****************************************************************************
 
//*****************************************************************************
//
//! \brief Gets the description of TCN75001 test.
//!
//! \return the desccription of the TCN75001 test.
//
//*****************************************************************************
static char* TCN75001GetTest(void)
{
    return "TCN75 configuration test";
}

//*****************************************************************************
//
//! \brief something should do before the execute of TCN75001 test.
//!
//! \return None.
//
//*****************************************************************************
static void TCN75001Setup(void)
{
    TCN75Init(10000);    
}

//*****************************************************************************
//
//! \brief something should do after the execute of TCN75001 test.
//!
//! \return None.
//
//*****************************************************************************
static void TCN75001TearDown(void)
{
    TCN75DeInit();    
}

//*****************************************************************************
//
//! \brief TCN75001 test execute main body for configuration.
//!
//! \return None.
//
//*****************************************************************************
static void TCN75001CofigExecute()
{
    unsigned char ucMode[2] = {TCN75_SHUTDOWM_ON , TCN75_SHUTDOWN_OFF};
    unsigned char ucFaultQue[4] = {TCN75_FAULTQUE_1, TCN75_FAULTQUE_2,
                                    TCN75_FAULTQUE_4, TCN75_FAULTQUE_6};	
	//
	//Tests TCN75 shutdowm mode and normal mode.
	//
	TCN75ModeSet(ucMode[0]);
	TestAssert(ucMode[0] == TCN75ModeGet(),
		  "TCN75 API \"TCN75ModeSet \"or \"TCN75ModeGet\"  error!");
	TCN75ModeSet(ucMode[1]);
	TestAssert(ucMode[1] == TCN75ModeGet(),
		  "TCN75 API \"TCN75ModeSet \"or \"TCN75ModeGet\"  error!");

    //
    // Fault Queue test
    //
	for(uli = 0; uli < 4; uli ++)
	{
	    TCN75FaultQueSet(ucFaultQue[uli]);
		TestAssert(ucFaultQue[uli] == TCN75FaultQueGet(),
		  "TCN75 API \"TCN75ModeSet \"or \"TCN75ModeGet\"  error!");
	}	
}


//
// TCN75001  test case struct.
//
const tTestCase sTestTCN75Config = {
		TCN75001GetTest,
		TCN75001Setup,
        TCN75001TearDown,
		TCN75001CofigExecute
};

//*****************************************************************************
//
//! \brief Gets the description of TCN75002 test.
//!
//! \return the desccription of the TCN75002  test.
//
//*****************************************************************************
static char* TCN75002GetTest(void)
{
    return "TCN75 temperature get and set test";
}

//*****************************************************************************
//
//! \brief something should do before the execute of TCN75002 test 
//!
//! \return None.
//
//*****************************************************************************
static void TCN75002Setup(void)
{
    TCN75Init(10000);    
}

//*****************************************************************************
//
//! \brief something should do after the execute of TCN75002 test.
//!
//! \return None.
//
//*****************************************************************************
static void TCN75002TearDown(void)
{
    TCN75DeInit();    
}

//*****************************************************************************
//
//! \brief TCN75002 execute main body for temperature get and set test.
//!
//! \return None.
//
//*****************************************************************************
static void TCN75002TempExecute()
{	
    float fTestTemper[4] = {-55, 0, 30, 125};
	float fTemper[4] = {-110, 0, 60, 250};

	for(uli = 0; uli < 4; uli ++)
	{
	    //
		// Writes a temperature value in THYS register and test.
		//
	    TCN75RegWrite(TCN75_THYS, &fTestTemper[uli]);
		TestAssert(fTestTemper[uli] == TCN75TempReadFDC(TCN75_THYS),
		  "TCN75 API \"TCN75RegWrite \"or \"TCN75TempReadFDC\"  error!");
		TestAssert(fTemper[uli] == TCN75TempGet(TCN75_THYS),
		  "TCN75 API \"TCN75RegWrite \"or \"TCN75TempGet\"  error!");

		//
		// Writes a temperature value in TSET register and test.
		//
		TCN75RegWrite(TCN75_TSET, &fTestTemper[uli]);
		TestAssert(fTestTemper[uli] == TCN75TempReadFDC(TCN75_TSET),
		  "TCN75 API \"TCN75RegWrite \"or \"TCN75TempReadFDC\"  error!");
		TestAssert(fTemper[uli] == TCN75TempGet(TCN75_TSET),
		  "TCN75 API \"TCN75RegWrite \"or \"TCN75TempGet\"  error!");
	}
}

//
// TCN75002  test case struct.
//
const tTestCase sTestTCN75Temp= {
		TCN75002GetTest,
		TCN75002Setup,
        TCN75002TearDown,
		TCN75002TempExecute
};
//*****************************************************************************
//
//! \brief Gets the description of TCN75003 test.
//!
//! \return the desccription of the TCN75003 test.
//
//*****************************************************************************
static char* TCN75003GetTest(void)
{
    return "TCN75  compare and interrupt mode test";
}

//*****************************************************************************
//
//! \brief something should do before the execute of TCN75003 test.
//!
//! \return None.
//
//*****************************************************************************
static void TCN75003Setup(void)
{
    TCN75Init(5000);    
}

//*****************************************************************************
//
//! \brief something should do after the execute of TCN75003 test.
//!
//! \return None.
//
//*****************************************************************************
static void TCN75003TearDown(void)
{
    TCN75DeInit();    
}

//*****************************************************************************
//
//! \brief TCN75003 test execute main body for compare mode.
//!
//! \return None.
//
//*****************************************************************************
static void TCN75003IntExecute()
{
    float fTemp = 25;

	TCN75RegWrite(TCN75_THYS, &fTemp);
	TCN75RegWrite(TCN75_TSET, &fTemp);

    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    xGPIODirModeSet(GPIO_PORTA_BASE, GPIO_PIN_12, GPIO_DIR_MODE_OUT);
    
	TCN75IntConfig(Test_CMP, ALERTPOL_LOW, TCN75_MODE_CMP);

    xIntEnable(xINT_GPIOB);
    xIntMasterEnable();
	
	uli = 0;

	while(!uli)
	{
	    fTemp = TCN75TempReadFDC(TCN75_TEMP);

	    for(ulj = 0; ulj < 0xfff ;ulj++);
	} 
	
	TCN75IntConfig(Test_Int, ALERTPOL_LOW, TCN75_MODE_INT);
	
	TestAssertQ("a", "TCN75 interrupt mode test fail"); 
	
	xIntDisable(xINT_GPIOB);
    xIntMasterDisable();	
}
//
// TCN75003  test case struct.
//
const tTestCase sTestTCN75Int = {
		TCN75003GetTest,
		TCN75003Setup,
		TCN75003TearDown,
		TCN75003IntExecute		
};

//
// TCN75 test suits.
//
const tTestCase * const psPatternTCN75[] =
{
    &sTestTCN75Config,
	&sTestTCN75Temp,
	&sTestTCN75Int,
    0
};
