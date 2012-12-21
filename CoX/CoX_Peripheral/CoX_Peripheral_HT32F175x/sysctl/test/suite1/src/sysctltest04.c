//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
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
//! - \subpage test_xsysctl_register
//! .
//! \file xsysctltest.c
//! \brief xsysctl test source file
//! \brief xsysctl test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_memmap.h"

//*****************************************************************************
//
//!\page test_xsysctl_register test_xsysctl_register
//!
//!<h2>Description</h2>
//!Test xsysctl register. <br>
//!
//
//*****************************************************************************

unsigned long ulLVDVoltage[] = {PWRCU_LVDCSR_LVDS_2V7, PWRCU_LVDCSR_LVDS_2V8, 
                                PWRCU_LVDCSR_LVDS_2V9, PWRCU_LVDCSR_LVDS_3V0};
unsigned long ulHSIWaitLength[] = {PWRCU_HSIRCR_HSIRCBL_4, PWRCU_HSIRCR_HSIRCBL_5, 
                                   PWRCU_HSIRCR_HSIRCBL_6, PWRCU_HSIRCR_HSIRCBL_7};

unsigned long ulClkReadyFlag[] = {SYSCLK_GCIR_CKSIE, SYSCLK_GCIR_PLLRDYIE,
                                  SYSCLK_GCIR_HSERDYIE, SYSCLK_GCIR_HSIRDYIE,
                                  SYSCLK_GCIR_LSERDYIE, SYSCLK_GCIR_LSIRDYIE,
                                 };

//*****************************************************************************
//
//! \brief Get the Test description of xsysctl004 register test.
//!
//! \return the desccription of the xcore004 test.
//
//*****************************************************************************
static char* xSysctl005GetTest(void)
{
  return "xsysctl, 005, xsysctl api test:Power and BOD.";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl005Setup(void)
{

}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl005TearDown(void)
{   

}


//*****************************************************************************
//
//! \brief xsysctl 002 test of SysCtl Power Manage test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPowerManage_test(void)
{
    unsigned long ulTemp, i;

    while(!SysCtlBackupReadyStateGet());

    SysCtlBackupDomainReset();
    //
	// BOD Enable Test
	//
    SysCtlBODEnable(xtrue);
    ulTemp = xHWREG(PWRCU_LVDCSR);
    TestAssert((PWRCU_LVDCSR_BODEN == (ulTemp & PWRCU_LVDCSR_BODEN)),
                                                         "xsysctl API error!");
	//
	// LVD Enable Test
	//

    SysCtlLVDEnable(xtrue);
    ulTemp = xHWREG(PWRCU_LVDCSR);
    TestAssert(PWRCU_LVDCSR_LVDEN == (ulTemp & PWRCU_LVDCSR_LVDEN), 
	                                                "xsysctl API  error!");

    SysCtlLVDEnable(xfalse);
    ulTemp = xHWREG(PWRCU_LVDCSR);
    TestAssert((0 == (ulTemp & PWRCU_LVDCSR_LVDEN)), "xsysctl API error!");

	//
	// LVD Interrupt Enable Test
	//
    SysCtlLVDIntEnable(xtrue);
    ulTemp = xHWREG(PWRCU_LVDCSR);
    TestAssert(PWRCU_LVDCSR_LVDIWEN == (ulTemp & PWRCU_LVDCSR_LVDIWEN),
	                                                  "xsysctl API  error!");

    SysCtlLVDIntEnable(xfalse);
    ulTemp = xHWREG(PWRCU_LVDCSR);
    TestAssert((0 == (ulTemp & PWRCU_LVDCSR_LVDIWEN)), "xsysctl API error!");

 
    SysCtlBODEnable(xfalse);
    ulTemp = xHWREG(PWRCU_LVDCSR);
    TestAssert((0 == (ulTemp & PWRCU_LVDCSR_BODEN)), "xsysctl API error!");

	//
	// DMOS Enable Test
	//
    SysCtlDMOSEnable(xtrue);
    ulTemp = xHWREG(PWRCU_BAKCR);
    TestAssert(PWRCU_BAKCR_DMOSON == (ulTemp & PWRCU_BAKCR_DMOSON), 
	                                                   "xsysctl API  error!");

    SysCtlDMOSEnable(xfalse);
    ulTemp = xHWREG(PWRCU_BAKCR);
    TestAssert((0 == (ulTemp & PWRCU_BAKCR_DMOSON)), "xsysctl API error!");

    //
	// BOD Function select Test
	//
    SysCtlBODFunctionSelect(PWRCU_LVDCSR_BODRST);
    ulTemp = xHWREG(PWRCU_LVDCSR);
    TestAssert((PWRCU_LVDCSR_BODRST == (ulTemp & PWRCU_LVDCSR_BODRST)),
                                                        "xsysctl API error!");
 
    SysCtlBODFunctionSelect(PWRCU_LVDCSR_BODINT);
    ulTemp = xHWREG(PWRCU_LVDCSR);
    TestAssert((PWRCU_LVDCSR_BODINT == (ulTemp & PWRCU_LVDCSR_BODINT)),
                                                        "xsysctl API error!");

    //
	// WakeUp Pin Enable Test
	//
    SysCtlWakeUpPinEnable(xtrue);
    ulTemp = xHWREG(PWRCU_BAKCR);
    TestAssert((PWRCU_BAKCR_WUPEN == (ulTemp & PWRCU_BAKCR_WUPEN)),
                                                        "xsysctl API error!");
 
    SysCtlWakeUpPinEnable(xfalse);
    ulTemp = xHWREG(PWRCU_BAKCR);
    TestAssert((0 == (ulTemp & PWRCU_BAKCR_WUPEN)), "xsysctl API error!");

    //
	// WakeUp Pin Interrupt Enable Test
	//
    SysCtlWakeUpIntEnable(xtrue);
    ulTemp = xHWREG(PWRCU_BAKCR);
    TestAssert((PWRCU_BAKCR_WUPIEN == (ulTemp & PWRCU_BAKCR_WUPIEN)),
                                                        "xsysctl API error!");
 
    SysCtlWakeUpIntEnable(xfalse);
    ulTemp = xHWREG(PWRCU_BAKCR);
    TestAssert((0 == (ulTemp & PWRCU_BAKCR_WUPIEN)), "xsysctl API error!");

    //
    // LVD Voltage Select Test
    //
    for(i = 0; i < 4; i++)
    {
        SysCtlLVDVoltSelect(ulLVDVoltage[i]);
        ulTemp = ((xHWREG(PWRCU_LVDCSR) & PWRCU_LVDCSR_LVDS_M)>>PWRCU_LVDCSR_LVDS_S);
        TestAssert(i == ulTemp , "xsysctl API error!");
    }
}



//*****************************************************************************
//
//! \brief xsysctl 005 test of clock ready Register test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_ClkReady_test(void)
{
    unsigned long ulTemp,i; 
    
	//
    // HSI ready counter bit length Test
	//
    for(i = 0; i < 4; i++)
    {
        SysCtlHSIReadyCounterBitLengthSet(ulHSIWaitLength[i]);
        ulTemp = xHWREG(PWRCU_HSIRCR);
        TestAssert((i == (ulTemp & PWRCU_HSIRCR_HSIRCBL_M)),
                                                         "xsysctl API error!");
    }

	//
	// Enable individual Clock Ready interrupt Test
	//

    for(i = 0; i < 6; i++)
    {
        SysCtlClockReadyIntEnable(ulClkReadyFlag[i]);
        ulTemp = xHWREG(SYSCLK_GCIR);
        TestAssert((ulClkReadyFlag[i] == (ulTemp & ulClkReadyFlag[i])),
                                                         "xsysctl API error!");
    }

}


//*****************************************************************************
//
//! \brief xsysctl 005 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl005Execute(void)
{
    xsysctl_SysCtlPowerManage_test();
    xsysctl_ClkReady_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl005Register = {
    xSysctl005GetTest,
    xSysctl005Setup,
    xSysctl005TearDown,
    xSysctl005Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl04[] =
{
    &sTestXSysctl005Register,
    0
};
