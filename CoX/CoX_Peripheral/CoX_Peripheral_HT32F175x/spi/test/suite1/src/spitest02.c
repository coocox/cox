//*****************************************************************************
//
//! @page xspi_testcase spi FIFO test
//!
//! File: @ref spitest02.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: HT32F125x Development Board <br><br>
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
//! - \subpage test_xspi_FIFO
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
// FIFO Enable and disable test
//
static unsigned long ulFIFOEnable[2] = {SPI_FIFO_ENABLE, SPI_FIFO_DISABLE};

//
// FIFO Level set
//
static unsigned long ulFIFOLevel[3] = {0, 5, 8};

//
// TXRX
//
static unsigned long ulTxRx[2] = {SPI_FSR_RX, SPI_FSR_TX};

//*****************************************************************************
//
//! \brief Get the Test description of xspi003 register test.
//!
//! \return the desccription of the xspi003 test.
//
//*****************************************************************************
const char* xSpi002GetTest(void)
{
    static const char * const pcName = "xspi, 003, xspi FIFO register test";
    return pcName;
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xspi003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi002Setup(void)
{    
    //
    // Set SysClk 8MHz using Extern 8M oscillator
    //

    //
    // Enable Peripheral SPI0
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0);  
	SysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO); 
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); 
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);  
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xspi003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi002TearDown(void)
{       
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI0);
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
    unsigned long i,ulTemp;

    SPIFIFOModeSet(SPI0_BASE, ulFIFOEnable[0]);
    ulTemp = xHWREG(SPI0_BASE + SPI_FCR) & SPI_FCR_FIFOEN;
	TestAssert((ulTemp == SPI_FCR_FIFOEN), "xspi FIFO mode enable error!");

	SPIFIFOModeSet(SPI0_BASE, ulFIFOEnable[1]);
    ulTemp = xHWREG(SPI0_BASE + SPI_FCR) & SPI_FCR_FIFOEN;
	TestAssert((ulTemp == 0), "xspi FIFO mode disable error!");

	for(i = 0; i < 3; i++)
	{
	    SPIFIFOLevelSet(SPI0_BASE, ulTxRx[0], ulFIFOLevel[i]);
		ulTemp = (xHWREG(SPI0_BASE + SPI_FCR) >> SPI_FCR_RXFTLS_S) & SPI_FCR_TXFTLS_M;
	    TestAssert((ulTemp == ulFIFOLevel[i]), "xspi FIFO Level set error!");
	}
	
	for(i = 0; i < 3; i++)
	{
	    SPIFIFOLevelSet(SPI0_BASE, ulTxRx[1], ulFIFOLevel[i]);
		ulTemp = (xHWREG(SPI0_BASE + SPI_FCR) >> SPI_FCR_TXFTLS_S) & SPI_FCR_TXFTLS_M;
	    TestAssert((ulTemp == ulFIFOLevel[i]), "xspi FIFO Level set error!");
	}

}


//*****************************************************************************
//
//! \brief xspi 003 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi002Execute(void)
{
    xspi_SPIFIFOModeSet_test();
}

//
// xspi register test case struct.
//
const tTestCase sTestXSpi002Register = {
    xSpi002GetTest,
    xSpi002Setup,
    xSpi002TearDown,
    xSpi002Execute
};

//
// Xspi test suits.
//
const tTestCase * const psPatternXspi02[] =
{
    &sTestXSpi002Register,
    0
};
