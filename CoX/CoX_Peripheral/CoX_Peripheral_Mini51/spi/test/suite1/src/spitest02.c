//*****************************************************************************
//
//! @page xspi_testcase xcore register test
//!
//! File: @ref spitest02.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: NuTiny-LB-Mini51 v2.0 <br><br>
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
//! - \subpage test_xspi_register
//! .
//! \file spitest.c
//! \brief xspi test source file
//! \brief xspi test header file <br>
//
//*****************************************************************************
#include "xhw_memmap.h"
#include "test.h"
#include "xspi.h"
#include "xhw_spi.h"
#include "xsysctl.h"

//*****************************************************************************
//
//!\page test_xspi_register test_xsysctl_register
//!
//!<h2>Description</h2>
//!Test xspi register. <br>
//!
//
//*****************************************************************************
//
// SPI Base Address Group Array
//
unsigned long ulSPIAddr[2] = {SPI0_BASE};

//
// SPI SPI_FORMAT_MODE Array
//
unsigned long ulSPIAddrFormatMode[] = {
 SPI_FORMAT_MODE_0,SPI_FORMAT_MODE_1,SPI_FORMAT_MODE_2,
 SPI_FORMAT_MODE_3,SPI_FORMAT_MODE_4,SPI_FORMAT_MODE_5,
 SPI_FORMAT_MODE_6,SPI_FORMAT_MODE_7};


//*****************************************************************************
//
//! \brief Get the Test description of xspi003 register test.
//!
//! \return the desccription of the xspi003 test.
//
//*****************************************************************************
static char* xSpi003GetTest(void)
{
    return "xspi, 003, xspi 3 wire set and configuration test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xspi003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi003Setup(void)
{
    //
    // Set SysClk 36MHz using Extern 12M oscillator
    //
     xSysCtlClockSet(12000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    
    //
    // Enable Peripheral SPI0
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xspi003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi003TearDown(void)
{   
    unsigned long ulTemp;
    ulTemp = SYSCTL_SYSDIV_1|SYSCTL_XTAL_12MHZ|SYSCTL_OSC_MAIN||SYSCTL_INT_OSC_DIS;
    SysCtlHClockSet(ulTemp);

    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
    SysCtlIPClockDividerSet(SYSCTL_PERIPH_UART_D|0);
    
    SysCtlPeripheralReset(SYSCTL_PERIPH_SPI0);
    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI0);
}

//*****************************************************************************
//
//! \brief xspi 003 test of SPI 3 Wire Function enable.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SPI3WireFunction_test(void)
{
    unsigned long ulRegVal,ulTempMode;

    xHWREG(SPI0_BASE + SPI_CNTRL2) &= 0x0000;
    ulTempMode = SPI_MODE_SLAVE;
    SPIConfig(SPI0_BASE,18,ulTempMode);
    SPI3WireFunction(SPI0_BASE, xtrue);
    ulRegVal =xHWREG(SPI0_BASE + SPI_CNTRL2);
    TestAssert((SPI_CNTRL2_NOSLVSEL == ulRegVal), "xspi API error!");
    
    xHWREG(SPI0_BASE + SPI_CNTRL2) &= 0x0000;
    ulTempMode = SPI_MODE_SLAVE;
    SPIConfig(SPI0_BASE,18,ulTempMode);
    SPI3WireFunction(SPI0_BASE, xfalse);
    ulRegVal =xHWREG(SPI0_BASE + SPI_CNTRL2);
    TestAssert((0x0000 == ulRegVal), "xspi API error!");
}

//*****************************************************************************
//
//! \brief xspi 003 test of SPI 3 Wire Abort .
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SPI3WireAbort_test(void)
{
    unsigned long ulRegVal;
    
    xHWREG(SPI0_BASE + SPI_CNTRL2) &= 0x0000;      
    SPI3WireAbort(SPI0_BASE);
    ulRegVal =xHWREG(SPI0_BASE + SPI_CNTRL2);
    TestAssert((SPI_CNTRL2_SLV_ABORT == ulRegVal), "xspi API error!");
}

//*****************************************************************************
//
//! \brief xspi 003 test of SPI 3 wire start intterrupt enable.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SPI3WireStartIntEnable_test(void)
{
    unsigned long ulRegVal;
    
    xHWREG(SPI0_BASE + SPI_CNTRL2) &= 0x0000;
    SPI3WireStartIntEnable(SPI0_BASE);
    ulRegVal =xHWREG(SPI0_BASE + SPI_CNTRL2);
    TestAssert((SPI_CNTRL2_SSTA_INTEN == ulRegVal), "xspi API error!");
}

//*****************************************************************************
//
//! \brief xspi 003 test of SPI 3 wire wtart intterrupt disable.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SPI3WireStartIntDisable_test(void)
{
    unsigned long ulRegVal;
    
    xHWREG(SPI0_BASE + SPI_CNTRL2) &= 0x0000;
    SPI3WireStartIntDisable(SPI0_BASE);
    ulRegVal =xHWREG(SPI0_BASE + SPI_CNTRL2);
    TestAssert((0x0000 == ulRegVal), "xspi API error!");
}

//*****************************************************************************
//
//! \brief xspi 003 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi003Execute(void)
{
    xspi_SPI3WireFunction_test();
    xspi_SPI3WireStartIntEnable_test();
    xspi_SPI3WireAbort_test();
    xspi_SPI3WireStartIntDisable_test();
}

//
// xspi register test case struct.
//
const tTestCase sTestXSpi003Register = {
    xSpi003GetTest,
    xSpi003Setup,
    xSpi003TearDown,
    xSpi003Execute
};

//
// Xspi test suits.
//
const tTestCase * const psPatternXspi02[] =
{
    &sTestXSpi003Register,
    0
};
