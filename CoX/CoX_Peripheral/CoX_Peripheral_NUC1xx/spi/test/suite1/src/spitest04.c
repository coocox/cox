//*****************************************************************************
//
//! @page xspi_testcase xcore register test
//!
//! File: @ref spitest04.c
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
unsigned long ulSPIAddrTemp[4] = {SPI0_BASE,SPI1_BASE,SPI2_BASE,SPI3_BASE};

unsigned long ulSuspendInterval[14] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15};

//*****************************************************************************
//
//! \brief Get the Test description of xspi003 register test.
//!
//! \return the desccription of the xspi003 test.
//
//*****************************************************************************
static char* xSpi005GetTest(void)
{
    return "xspi, 005, xspi FIFO Set test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xspi003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi005Setup(void)
{
    //
    // Set SysClk 36MHz using Extern 12M oscillator
    //
    xSysCtlClockSet(36000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    
    SysCtlPeripheralReset(SYSCTL_PERIPH_SPI0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_SPI1);
    SysCtlPeripheralReset(SYSCTL_PERIPH_SPI2);
    SysCtlPeripheralReset(SYSCTL_PERIPH_SPI3);
    //
    // Enable Peripheral SPI0,SPI1,SPI2 And SPI3
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_SPI0);
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
static void xSpi005TearDown(void)
{   
    unsigned long ulTemp;
    ulTemp = SYSCTL_SYSDIV_1|SYSCTL_XTAL_12MHZ|SYSCTL_OSC_MAIN|SYSCTL_PLL_PWRDN
                                                           | SYSCTL_INT_OSC_DIS;
    SysCtlHClockSet(ulTemp);

    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
    SysCtlIPClockDividerSet(SYSCTL_PERIPH_UART_D|0);
    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI0);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI1);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI2);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI3); 
}

//*****************************************************************************
//
//! \brief xspi 004 test of SPI 3 Wire Function enable.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SPIFIFOModeSet_test(void)
{
    unsigned long i,ulRegVal,ulTemp,j;

    for(i = 0;i < 4;i++)
    {
        for(j = 0; j < 14; j++ )
        {
            xHWREG(ulSPIAddrTemp[i] + SPI_CNTRL) &= 0x0000;
            SPIFIFOModeSet(ulSPIAddrTemp[i], xtrue, ulSuspendInterval[j]);
            ulRegVal =xHWREG(ulSPIAddrTemp[i] + SPI_CNTRL);
            ulTemp = (ulSuspendInterval[j] << SPI_CNTRL_SP_CYCLE_S) | 0x05000000
                                                               | SPI_CNTRL_FIFO; 
            TestAssert((ulTemp == ulRegVal), "xspi API error!");
        }
    }
    
    for(i = 0; i < 4; i++)
    {

        xHWREG(ulSPIAddrTemp[i] + SPI_CNTRL) &= 0x0000;
        SPIFIFOModeSet(ulSPIAddrTemp[i], xtrue, 0);
        ulRegVal =xHWREG(ulSPIAddrTemp[i] + SPI_CNTRL);
        ulTemp = SPI_CNTRL_FIFO | (0 << SPI_CNTRL_SP_CYCLE_S) | 0x05000000; 
        TestAssert((ulTemp == ulRegVal), "xspi API error!");
    }
}


//*****************************************************************************
//
//! \brief xspi 003 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi005Execute(void)
{
    xspi_SPIFIFOModeSet_test();
}

//
// xspi register test case struct.
//
const tTestCase sTestXSpi005Register = {
    xSpi005GetTest,
    xSpi005Setup,
    xSpi005TearDown,
    xSpi005Execute
};

//
// Xspi test suits.
//
const tTestCase * const psPatternXspi04[] =
{
    &sTestXSpi005Register,
    0
};
