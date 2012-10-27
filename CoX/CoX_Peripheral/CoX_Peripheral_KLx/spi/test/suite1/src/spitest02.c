//*****************************************************************************
//
//! @page xspi_testcase xcore register test
//!
//! File: @ref spitest02.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: KL25Z128 <br><br>
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
//! \file spitest02.c
//! \brief xspi test source file
//! \brief xspi test header file <br>
//
//*****************************************************************************
#include "test.h"
#include "xhw_spi.h"
#include "xspi.h"

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
static unsigned long ulSPI[2] = {xSPI0_BASE, xSPI1_BASE};

//
// SPI DMA Array
//
static unsigned long ulDMAFlags[] = {SPI_DMA_RX, SPI_DMA_TX};

static unsigned long ulSSetFlags[] = {SPI_SS_MODEFAULT, SPI_SS_OUTPUT};

static unsigned long ulClkMode[] = {SPI_CLK_STOP, SPI_CLK_CONTINUE};
//
// SPI Operation Mode
//
//static unsigned long ulSPIOperationMode[] = {SPI_MODE_MASTER, SPI_MODE_SLAVE};

//*****************************************************************************
//
//! \brief Get the Test description of xspi003 register test.
//!
//! \return the desccription of the xspi003 test.
//
//*****************************************************************************
static char* xSpi003GetTest(void)
{
    return "xspi, 003, xspi DMA and SS Set  test";
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
    // Enable Peripheral SPI0 and SPI1.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI1);
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
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI0);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI1); 
}

//*****************************************************************************
//
//! \brief xspi 003 test of SPI DMA enable or disable.
//!
//! \return None.
//
//*****************************************************************************
static void xspi003_SPIDMA_test(void)
{
    unsigned long i, j, ulRegVal;
    for(i = 0; i < 2; i ++)
    {
        for(j = 0; j < 2; j ++)
         {
            SPIDMAEnable(ulSPI[i], ulDMAFlags[j]);
            ulRegVal = xHWREGB(ulSPI[i] + SPI_C2) & ulDMAFlags[j];
            TestAssert(ulRegVal == ulDMAFlags[j], "xspi API error!");                                                

            SPIDMADisable(ulSPI[i], ulDMAFlags[j]);
            ulRegVal = xHWREGB(ulSPI[i] + SPI_C2) & ulDMAFlags[j];
            TestAssert(ulRegVal == 0, "xspi API error!");    
        }
    }
}

//*****************************************************************************
//
//! \brief xspi 003 test of SPI Slave select output status .
//!
//! \return None.
//
//*****************************************************************************
static void xspi003_SPISSet_test(void)
{
    unsigned long i, j, ulRegVal;
    
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
         {
            SPISSSet(ulSPI[i], ulSSetFlags[j]);
            ulRegVal = xHWREGB(ulSPI[i] + SPI_C1) & ulSSetFlags[j];
            TestAssert(ulRegVal == ulSSetFlags[j], "xspi API error!");                                                

            SPISSClear(ulSPI[i]);
            ulRegVal = xHWREGB(ulSPI[i] + SPI_C2) & SPI_C2_MODFEN;
            TestAssert(ulRegVal == 0, "xspi API error!");    
        }
    }
}

//*****************************************************************************
//
//! \brief xspi 003 test of SPI 3 Wire function .
//!
//! \return None.
//
//*****************************************************************************
static void xspi003_SPI3Wire_test(void)
{
    unsigned long i, ulRegVal;
    
    for(i = 0; i < 2; i++)
    {
        SPI3WireEnable(ulSPI[i], SPI_MODE_MASTER);
	ulRegVal = xHWREGB(ulSPI[i] + SPI_C2) & (SPI_C2_BIDIROE | SPI_C2_SPC0);
        TestAssert(ulRegVal == (SPI_C2_BIDIROE | SPI_C2_SPC0), 
                                                 "xspi API error!");                                                
            
	SPI3WireEnable(ulSPI[i], SPI_MODE_SLAVE);
	ulRegVal = xHWREGB(ulSPI[i] + SPI_C2) & (SPI_C2_BIDIROE | SPI_C2_SPC0);
        TestAssert(ulRegVal == SPI_C2_SPC0, "xspi API error!");   
			
        SPI3WireDisable(ulSPI[i]);
        ulRegVal = xHWREGB(ulSPI[i] + SPI_C2) & (SPI_C2_BIDIROE | SPI_C2_SPC0) ;
        TestAssert(ulRegVal == 0, "xspi API error!");    
    }
}

//*****************************************************************************
//
//! \brief xspi 003 test of SPI clk status when MCU enters wait mode.
//!
//! \return None.
//
//*****************************************************************************
static void xspi003_SPIWaitMode_test(void)
{
    unsigned long i, j, ulRegVal;
    
    for(i = 0; i < 2; i ++)
    {
        for(j = 0; j < 2; j ++)
        {
            SPIClkStatusForWaitMode(ulSPI[i], ulClkMode[j]);
	    ulRegVal = xHWREGB(ulSPI[i] + SPI_C2) & ulClkMode[j];
	    TestAssert(ulRegVal == ulClkMode[j], "xspi API error!");  
        }
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
    xspi003_SPIDMA_test(); 
    xspi003_SPISSet_test();
    xspi003_SPI3Wire_test();
    xspi003_SPIWaitMode_test();	
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
