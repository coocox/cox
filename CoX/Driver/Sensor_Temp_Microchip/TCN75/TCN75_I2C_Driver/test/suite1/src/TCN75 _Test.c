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
#include "hw_TCN75.h"
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
    unsigned char ucTemp;
	unsigned char ucMode[2] = {TCN75_MODE_INT, TCN75_MODE_CMP};
	unsigned char ucPolarity[2] = {TCN75_POLARITY_HIGH, TCN75_POLARITY_LOW};
    unsigned char ucFaultQue[4] = {TCN75_FAULTQUE_1, TCN75_FAULTQUE_2,
                                    TCN75_FAULTQUE_4, TCN75_FAULTQUE_6};	
	//
	//Test TCN75 shutdowm mode and normal mode.
	//
	TCN75Shutdown();
	ucTemp = TCN75RegRead(TCN75_CONFIG) & 0x01;
	TestAssert(ucTemp == TCN75_SHUTDOWM_ON,
		  "TCN75 API \"TCN75Shutdown\" error!");
	
	TCN75WakeUp();
	ucTemp = TCN75RegRead(TCN75_CONFIG) & 0x01;
	TestAssert(ucTemp == 0,
		  "TCN75 API \"TCN75WakeUp \" error!");

	//
	// Test TCN75 interrupt and compare mode.
	//
	TCN75Config(ucMode[0]);
	ucTemp = TCN75RegRead(TCN75_CONFIG) & 0x02;
	TestAssert(ucTemp == ucMode[0],
		  "TCN75 API \"TCN75Config\" error!");

    TCN75Config(ucMode[1]);
	ucTemp = TCN75RegRead(TCN75_CONFIG) & 0x02;
	TestAssert(ucTemp == ucMode[1],
		  "TCN75 API \"TCN75Config\" error!");

	//
	// Test TCN75 polarity.
	//
    TCN75Config(ucPolarity[0]);
	ucTemp = TCN75RegRead(TCN75_CONFIG) & 0x04;
	TestAssert(ucTemp == ucPolarity[0],
		  "TCN75 API \"TCN75Config\" error!");
    
	TCN75Config(ucPolarity[1]);
	ucTemp = TCN75RegRead(TCN75_CONFIG) & 0x04;
	TestAssert(ucTemp == ucPolarity[1],
		  "TCN75 API \"TCN75Config\" error!");

    //
    // Test TCN75 Fault Queue.
    //
	for(uli = 0; uli < 4; uli ++)
	{
	    TCN75Config(ucFaultQue[uli]);
		ucTemp = TCN75RegRead(TCN75_CONFIG) & 0x18;
		TestAssert(ucTemp == ucFaultQue[uli],
		    "TCN75 API \"TCN75Config \" error!");
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
	for(uli = 0; uli < 4; uli ++)
	{
	    TCN75LowLimitSet(fTestTemper[uli]);
		TestAssert(fTestTemper[uli] == TCN75LowLimitGet(),
		  "TCN75 API \"TCN75LowLimitSet \"or \"TCN75LowLimitGet\"  error!");
	

		TCN75UpLimitSet(fTestTemper[uli]);
		TestAssert(fTestTemper[uli] == TCN75UpLimitGet(),
		  "TCN75 API \"TCN75UpLimitSet \"or \"TCN75UpLimitGet\"  error!");
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
    return "TCN75  compare  mode test";
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
//! \brief TCN75003 test execute main body for  compare mode.
//!
//! \return None.
//
//*****************************************************************************
static void TCN75003CMPExecute()
{
    float fTemp = 25;

	TCN75LowLimitSet(fTemp);
	TCN75UpLimitSet(fTemp);

    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    xGPIODirModeSet(GPIO_PORTA_BASE, GPIO_PIN_12, GPIO_DIR_MODE_OUT);

	//
	// Test TCN75 compare mode.
	//
	TCN75Config(TCN75_MODE_CMP);
    
	TCN75IntConfig(Test_CMP);

    xIntEnable(xINT_GPIOB);
    xIntMasterEnable();
	
	uli = 0;

	while(!uli)
	{
	    fTemp = TCN75TempReadFDC();
		
	    for(ulj = 0; ulj < 0xfff ;ulj++);
	}  
	
	xIntDisable(xINT_GPIOB);
    xIntMasterDisable();	
}
//
// TCN75003  test case struct.
//
const tTestCase sTestTCN75CMP = {
		TCN75003GetTest,
		TCN75003Setup,
		TCN75003TearDown,
		TCN75003CMPExecute		
};

//*****************************************************************************
//
//! \brief Gets the description of TCN75004 test.
//!
//! \return the desccription of the TCN75004 test.
//
//*****************************************************************************
static char* TCN75004GetTest(void)
{
    return "TCN75  interrupt  mode test";
}

//*****************************************************************************
//
//! \brief something should do before the execute of TCN75004 test.
//!
//! \return None.
//
//*****************************************************************************
static void TCN75004Setup(void)
{
    TCN75Init(5000);    
}

//*****************************************************************************
//
//! \brief something should do after the execute of TCN75004 test.
//!
//! \return None.
//
//*****************************************************************************
static void TCN75004TearDown(void)
{
    TCN75DeInit();    
}

//*****************************************************************************
//
//! \brief TCN75004 test execute main body for  interrupt mode.
//!
//! \return None.
//
//*****************************************************************************
static void TCN75004IntExecute()
{
	//
	// Test TCN75 interrupt mode.
	//
	TCN75Config(TCN75_MODE_INT);
    
	TCN75IntConfig(Test_Int);

    xIntEnable(xINT_GPIOB);
    xIntMasterEnable();
	
	TestAssertQ("a", "TCN75 interrupt mode test fail"); 
	
	xIntDisable(xINT_GPIOB);
    xIntMasterDisable();	
}
//
// TCN75002  test case struct.
//
const tTestCase sTestTCN75Int = {
		TCN75004GetTest,
		TCN75004Setup,
		TCN75004TearDown,
		TCN75004IntExecute		
};
//
// TCN75 test suits.
//
const tTestCase * const psPatternTCN75[] =
{
    &sTestTCN75Config,
	&sTestTCN75Temp,
	&sTestTCN75CMP,
	&sTestTCN75Int,
    0
};
