//*****************************************************************************
//
//! @page xspi_testcase xspi register test
//!
//! File: @ref spitest00.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xspi sub component.<br><br>
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
// SPI Group Array
//
unsigned long ulSPI[2] = {SPI0_BASE, SPI1_BASE};

//
// SPI Transfers And Receives Data WIDTH
//
unsigned long ulDataWidth[] = { 
 SPI_DATA_WIDTH1,SPI_DATA_WIDTH2,SPI_DATA_WIDTH3,SPI_DATA_WIDTH4,
 SPI_DATA_WIDTH5,SPI_DATA_WIDTH6,SPI_DATA_WIDTH7,SPI_DATA_WIDTH8,
 SPI_DATA_WIDTH9,SPI_DATA_WIDTH10,SPI_DATA_WIDTH11,SPI_DATA_WIDTH12,
 SPI_DATA_WIDTH13,SPI_DATA_WIDTH14,SPI_DATA_WIDTH15,SPI_DATA_WIDTH16};


//
// SPI SPI_FORMAT_MODE Array
//
unsigned long ulSpiFormatMode[] = {SPI_FORMAT_MODE_1,SPI_FORMAT_MODE_2,
                                   SPI_FORMAT_MODE_5,SPI_FORMAT_MODE_6};

//
// Slave select level
//
unsigned long ulSelectLevel[2] = {SPI_SS_ACTIVE_LOW, SPI_SS_ACTIVE_HIGH};

//
// DMA Mode 
//
unsigned long ulDMAMode[2] = {SPI_DMA_RX, SPI_DMA_TX};

//*****************************************************************************
//
//! \brief Get the Test description of xspi001 register.
//!
//! \return the desccription of the xspi001 test.
//
//*****************************************************************************
const char* xSpi000GetTest(void)
{
    static const char * const pcName = "xspi, 001, xspi register test";
    return pcName;
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xspi001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi000Setup(void)
{
    //
    // Set SysClk 8MHz using Extern 8M oscillator
    //
   
    //
    // Enable Peripheral SPI0
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0);  
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI1); 
	SysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xspi001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi000TearDown(void)
{      
    SysCtlPeripheralReset(SYSCTL_PERIPH_SPI0);   
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI0); 
	SysCtlPeripheralReset(SYSCTL_PERIPH_SPI1);   
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI1);
}

//*****************************************************************************
//
//! \brief xspi 001 test of SPI MASTER/SLAVE Mode Slect.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SpiMasterSlaveModeSelect_test(void)
{
    unsigned long i,ulTemp,ulRegVal;

    //
    // Test Seting MCU as Slave
    //
    for(i = 0; i < 2; i++)
    {
        ulTemp = SPI_MODE_SLAVE;
        SPIConfig(ulSPI[i], 18, ulTemp);
        ulRegVal = xHWREG(ulSPI[i] + SPI_CNTRL1) & SPI_CNTRL1_MODE;
        TestAssert((ulTemp == ulRegVal), "xspi API Mode set error!");
    }
    
    //
    // Test Seting MCU as Master
    //
    for(i = 0; i < 1; i++)
    {
        ulTemp = SPI_MODE_MASTER;
        SPIConfig(ulSPI[i], 18, ulTemp);
        ulRegVal = xHWREG(ulSPI[i] + SPI_CNTRL1) & SPI_CNTRL1_MODE;
        TestAssert((ulTemp == ulRegVal), "xspi API Mode set error!");
    }
}

//*****************************************************************************
//
//! \brief xspi 001 test of Data Width.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SpiDataWidthSet_test(void)
{
    unsigned long i, j, ulTemp, ulRegVal;
 /*   
	//
	// SPI0 DataWidth Set Test
	//
    for(i = 0; i < 16; i++)
    {
	    for(j = 0; j < 2; j++)
		{
	        ulTemp = ulDataWidth[i];
	        SPIConfig(ulSPI[j], 18,ulTemp);
	        ulRegVal = SPIBitLengthGet(ulSPI[j]);
	        TestAssert((ulTemp == ulRegVal), "xspi API Data Width error!");
        }	
	}
*/	    
}

//*****************************************************************************
//
//! \brief xspi 001 test of Protocol of SPI Set.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SpiProtocolSet_test(void)
{
    unsigned long i, j, ulRegVal, ulTemp;
    for(i = 0;i < 4; i++)
    {
	    for(j = 0; j < 2; j++)
		{
	        ulTemp = ulSpiFormatMode[i];
	        SPIConfig(ulSPI[j], 18, ulTemp);
	        ulRegVal = xHWREG(ulSPI[j] + SPI_CNTRL1) & SPI_CNTRL1_FORMAT_M;
	        TestAssert((ulTemp == ulRegVal), "xspi API spi Protocol error!");
		}
    }
}

//*****************************************************************************
//
//! \brief xspi 001 test of LSB/MSB SPI Transfer And Receive Set.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SpiLsbMsbSet_test(void)
{
    unsigned long i,ulTemp,ulRegVal;
    
    //
    // Test Seting The LSB is sent first
    //
    for(i = 0;i < 2;i++)
    {
        ulTemp = SPI_LSB_FIRST;
        SPIConfig(ulSPI[i], 18, ulTemp);
        ulRegVal = xHWREG(ulSPI[i] + SPI_CNTRL1) & SPI_CNTRL1_FIRSTBIT;
        TestAssert((ulTemp == ulRegVal), "xspi API LSB/MSB set error!");
    }
    
    //
    // Test Seting The MSB is sent first
    //
    for(i = 0;i < 2;i++)
    {
        ulTemp = SPI_MSB_FIRST;
        SPIConfig(ulSPI[i], 18, ulTemp);
        ulRegVal = xHWREG(ulSPI[i] + SPI_CNTRL1) & SPI_CNTRL1_FIRSTBIT;
        TestAssert((ulTemp == ulRegVal), "xspi API LSB/MSB set error!");
    }
}

//*****************************************************************************
//
//! \brief xspi 001 test of Setting the slave select pins of the specified SPI port .
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SpiSlaveSelect_test(void)
{
    unsigned long i,ulRegVal;
    
    ulRegVal = 0;
    
    //
    // Set Slave Pin Select basing on xSPI_SS_SOFTWARE
    //
    for(i = 0; i < 2; i++)
    {  
        xSPISSSet(ulSPI[i], xSPI_SS_SOFTWARE, 0);
        ulRegVal = xHWREG(ulSPI[i] + SPI_CNTRL1) & SPI_CNTRL1_SELM;
        TestAssert(( xSPI_SS_SOFTWARE == ulRegVal), 
		             "xspi API Slave select on software error!");
    }
    
    //
    // Set Slave Pin Select basing on xSPI_SS_HARDWARE
    //
    for(i = 0;i < 2; i++)
    {  
	    SPIConfig(ulSPI[i], 18, SPI_MODE_MASTER);
	   // xHWREG(ulSPI[0] + SPI_CNTRL1) |= xSPI_SS_HARDWARE |	SPI_MODE_MASTER;
	    xSPISSSet(ulSPI[i], xSPI_SS_HARDWARE, 0);
        ulRegVal = xHWREG(ulSPI[i] + SPI_CNTRL1) & SPI_CNTRL1_SELM;

        TestAssert(( xSPI_SS_HARDWARE == ulRegVal), 
		             "xspi API Slave select on software error!");
	
    }   
}

//*****************************************************************************
//
//! \brief xspi 001 test of Config the slave select pins.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SPISSConfig_test(void)
{
    unsigned long i, ulRegVal;
    
    for(i = 0; i < 2; i++)
    {
        SPISSConfig(ulSPI[i], ulSelectLevel[i]);
        ulRegVal = xHWREG(ulSPI[i] + SPI_CNTRL1) & SPI_CNTRL1_SELAP;
        TestAssert((ulSelectLevel[i] == ulRegVal), "xspi API error!");
    }   
}

//*****************************************************************************
//
//! \brief xspi 001 test of Config the slave DMA.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SPIDMACondif_test(void)
{
    unsigned long i, j, ulRegVal;
    //
	// SPI DMA Enable test
	//
	for(i = 0; i < 2; i++)
	{
	    for(j = 0; j < 2; j++)
		{
	        SPIDMAEnable(ulSPI[i], ulDMAMode[j]);
			ulRegVal = xHWREG(ulSPI[i] + SPI_CNTRL0) & ulDMAMode[j];
			TestAssert((ulDMAMode[j] == ulRegVal), "xspi DMA Enable API error!");
		}
	}

    //
	// SPI DMA Disable test
	//
	for(i = 0; i < 2; i++)
	{
	    for(j = 0; j < 2; j++)
		{
	        SPIDMADisable(ulSPI[i], ulDMAMode[j]);
			ulRegVal = xHWREG(ulSPI[i] + SPI_CNTRL0) & ulDMAMode[j];
			TestAssert((0 == ulRegVal), "xspi DMA Disable API error!");
		}
	}
}

//*****************************************************************************
//
//! \brief xspi 001 test of SPI loopback enable and disable test.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SPILoopback_test()
{
    unsigned long i, ulRegVal;
    //
	// SPI loopback enable test
	//
	for(i = 0; i < 2; i++)
	{
	    SPILoopBackEnable(ulSPI[i]);
		ulRegVal = xHWREG(ulSPI[i] + SPI_CNTRL0) & SPI_CNTRL0_LOOPBACK_EN;
		TestAssert((SPI_CNTRL0_LOOPBACK_EN == ulRegVal), 
		            "xspi loopback enable and disable test!");
	}

    //
	// SPI loopback disable test
	//
	for(i = 0; i < 2; i++)
	{
	    SPILoopBackDisable(ulSPI[i]);
		ulRegVal = xHWREG(ulSPI[i] + SPI_CNTRL0) & SPI_CNTRL0_LOOPBACK_EN;
		TestAssert((0 == ulRegVal), 
		            "xspi loopback enable and disable test!");
	}
}


//*****************************************************************************
//
//! \brief xspi 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi000Execute(void)
{
    xspi_SpiMasterSlaveModeSelect_test();
    xspi_SpiDataWidthSet_test();
    xspi_SpiProtocolSet_test();
    xspi_SpiLsbMsbSet_test();
	xspi_SpiSlaveSelect_test();
	xspi_SPISSConfig_test();
	xspi_SPIDMACondif_test();
	xspi_SPILoopback_test();
}

//
// xspi register test case struct.
//
const tTestCase sTestXSpi000Register = {
    xSpi000GetTest,
    xSpi000Setup,
    xSpi000TearDown,
    xSpi000Execute
};

//
// Xspi test suits.
//
const tTestCase * const psPatternXspi00[] =
{
    &sTestXSpi000Register,
    0
};
