//*****************************************************************************
//
//! @page xspi_testcase xcore register test
//!
//! File: @ref spitest02.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
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
unsigned long ulSPIAddr[4] = {SPI0_BASE,SPI1_BASE,SPI2_BASE,SPI3_BASE};
unsigned long ulSPIDmaMode[3] = {SPI_DMA_RX, SPI_DMA_TX, SPI_DMA_BOTH};


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
    // xSysCtlClockSet(36000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    //
    // Enable Peripheral SPI0,SPI1,SPI2 And SPI3
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI2);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI3);    
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
    ulTemp = SYSCTL_SYSDIV_1|SYSCTL_XTAL_12MHZ|SYSCTL_OSC_MAIN|SYSCTL_PLL_PWRDN
                                                           | SYSCTL_INT_OSC_DIS;
    SysCtlHClockSet(ulTemp);

    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
    SysCtlIPClockDividerSet(SYSCTL_PERIPH_UART_D|0);
    
    SysCtlPeripheralReset(SYSCTL_PERIPH_SPI0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_SPI1);
    SysCtlPeripheralReset(SYSCTL_PERIPH_SPI2);
    SysCtlPeripheralReset(SYSCTL_PERIPH_SPI3);
    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI0);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI1);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI2);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI3); 
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
    unsigned long i,ulRegVal,ulTempMode;

    for(i = 0;i < 4;i++)
    {
        xHWREG(ulSPIAddr[i] + SPI_CNTRL2) &= 0x0000;
        ulTempMode = SPI_MODE_SLAVE;
        SPIConfig(ulSPIAddr[i],18,ulTempMode);
        SPI3WireFunction(ulSPIAddr[i], xtrue);
        ulRegVal =xHWREG(ulSPIAddr[i] + SPI_CNTRL2);
        TestAssert((SPI_CNTRL2_NOSLVSEL == ulRegVal), "xspi API error!");
    }
    
    for(i = 0;i < 4;i++)
    {
        xHWREG(ulSPIAddr[i] + SPI_CNTRL2) &= 0x0000;
        ulTempMode = SPI_MODE_SLAVE;
        SPIConfig(ulSPIAddr[i],18,ulTempMode);
        SPI3WireFunction(ulSPIAddr[i], xfalse);
        ulRegVal =xHWREG(ulSPIAddr[i] + SPI_CNTRL2);
        TestAssert((0x0000 == ulRegVal), "xspi API error!");
    }
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
    unsigned long i,ulRegVal;
    
    for(i = 0; i < 4; i++)
    {
        xHWREG(ulSPIAddr[i] + SPI_CNTRL2) &= 0x0000;      
        SPI3WireAbort(ulSPIAddr[i]);
        ulRegVal =xHWREG(ulSPIAddr[i] + SPI_CNTRL2);
        TestAssert((SPI_CNTRL2_SLV_ABORT == ulRegVal), "xspi API error!");
    }
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
    unsigned long i,ulRegVal;
    
    for(i = 0; i < 4; i++)
    {
        xHWREG(ulSPIAddr[i] + SPI_CNTRL2) &= 0x0000;
        SPI3WireStartIntEnable(ulSPIAddr[i]);
        ulRegVal =xHWREG(ulSPIAddr[i] + SPI_CNTRL2);
        TestAssert((SPI_CNTRL2_SSTA_INTEN == ulRegVal), "xspi API error!");
    }
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
    unsigned long i,ulRegVal;
    
    for(i = 0; i < 4; i++)
    {
        xHWREG(ulSPIAddr[i] + SPI_CNTRL2) &= 0x0000;
        SPI3WireStartIntDisable(ulSPIAddr[i]);
        ulRegVal =xHWREG(ulSPIAddr[i] + SPI_CNTRL2);
        TestAssert((0x0000 == ulRegVal), "xspi API error!");

    }
}


//*****************************************************************************
//
//! \brief xspi 003 test of Protocol of SPI PDMA enable.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SPI3PDMAEnable_test(void)
{
    unsigned long i,ulRegVal,ulTemp;
    
    for(i = 0;i < 3; i++)
    {
        ulTemp = ulSPIDmaMode[i];
        SPI3PDMAEnable(ulSPIAddr[0], ulTemp);
        ulRegVal = xHWREG(ulSPIAddr[0] + SPI_DMACTL);
        TestAssert((ulTemp == ulRegVal), "xspi API error!");
        xHWREG(ulSPIAddr[0] + SPI_DMACTL) &= 0x0000;
    }

    for(i = 0;i < 3; i++)
    {
        ulTemp = ulSPIDmaMode[i];
        SPI3PDMAEnable(ulSPIAddr[1], ulTemp);
        ulRegVal = xHWREG(ulSPIAddr[1] + SPI_DMACTL);
        TestAssert((ulTemp == ulRegVal), "xspi API error!");
        xHWREG(ulSPIAddr[1] + SPI_DMACTL) &= 0x0000;
    }
    
    for(i = 0;i < 3; i++)
    {
        ulTemp = ulSPIDmaMode[i];
        SPI3PDMAEnable(ulSPIAddr[2], ulTemp);
        ulRegVal = xHWREG(ulSPIAddr[2] + SPI_DMACTL);
        TestAssert((ulTemp == ulRegVal), "xspi API error!");
        xHWREG(ulSPIAddr[2] + SPI_DMACTL) &= 0x0000;
    }
    
    for(i = 0;i < 3; i++)
    {
        ulTemp = ulSPIDmaMode[i];
        SPI3PDMAEnable(ulSPIAddr[3], ulTemp);
        ulRegVal = xHWREG(ulSPIAddr[3] + SPI_DMACTL);
        TestAssert((ulTemp == ulRegVal), "xspi API error!");
        xHWREG(ulSPIAddr[3] + SPI_DMACTL) &= 0x0000;
    }
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
    xspi_SPI3PDMAEnable_test();
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
