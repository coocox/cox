//*****************************************************************************
//
//! @page xspi_testcase xspi register test
//!
//! File: @ref spitest00.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xspi sub component.<br><br>
//! - \p Board: EMSTM32V100 <br><br>
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
unsigned long ulSPI[2] = {SPI1_BASE, SPI2_BASE};

//
// SPI Transfers And Receives Data WIDTH
//
unsigned long ulDataWidth[] = {SPI_DATA_WIDTH8,
                               SPI_DATA_WIDTH16};


//
// SPI SPI_FORMAT_MODE Array
//
unsigned long ulSpiFormatMode[] = {SPI_FORMAT_MODE_1,SPI_FORMAT_MODE_0,
                                   SPI_FORMAT_MODE_3,SPI_FORMAT_MODE_4};


//*****************************************************************************
//
//! \brief Get the Test description of xspi001 register.
//!
//! \return the desccription of the xspi001 test.
//
//*****************************************************************************
const char* xSpi001GetTest(void)
{
    return "xspi, 001, xspi register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xspi001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi001Setup(void)
{
    //
    // Set SysClk 8MHz using Extern 8M oscillator
    //
    xSysCtlClockSet(16000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
   
    //
    // Enable Peripheral SPI0
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI2);
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI3);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xspi001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi001TearDown(void)
{      
    SysCtlPeripheralReset(SYSCTL_PERIPH_SPI1);   
    SysCtlPeripheralReset(SYSCTL_PERIPH_SPI2); 
 //   SysCtlPeripheralReset(SYSCTL_PERIPH_SPI3); 	
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI1); 
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI2); 
 //   SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI3); 	
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
        ulRegVal = xHWREG(ulSPI[i] + SPI_CR1) & SPI_CR1_MSTR;
        TestAssert((ulTemp == ulRegVal), "xspi API Mode set error!");
    }
    
    //
    // Test Seting MCU as Master
    //
    for(i = 0; i < 2; i++)
    {
        ulTemp = SPI_MODE_MASTER;
        SPIConfig(ulSPI[i], 18, ulTemp);
        ulRegVal = xHWREG(ulSPI[i] + SPI_CR1) & SPI_CR1_MSTR;
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
    unsigned long i,ulTemp,ulRegVal;
  
	//
	// SPI0 DataWidth Set Test
	//
    for(i = 0; i < 2; i++)
    {
        ulTemp = ulDataWidth[i];
        SPIConfig(ulSPI[0], 18, ulTemp);
        ulRegVal = xHWREG(ulSPI[0] + SPI_CR1) & SPI_CR1_DFF;
        TestAssert((ulTemp == ulRegVal), "xspi API Data Width error!");
    }
		
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
    unsigned long i,ulRegVal,ulTemp;
    for(i = 0;i < 4; i++)
    {
        ulTemp = ulSpiFormatMode[i];
        SPIConfig(ulSPI[0], 18, ulTemp);
        ulRegVal = xHWREG(ulSPI[0] + SPI_CR1) & 0x03;
        TestAssert((ulTemp == ulRegVal), "xspi API spi Protocol error!");
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
    for(i = 0;i < 2; i++)
    {
        ulTemp = SPI_LSB_FIRST;
        SPIConfig(ulSPI[i], 18, ulTemp);
        ulRegVal = xHWREG(ulSPI[i] + SPI_CR1) & SPI_CR1_LSBFIRST;
        TestAssert((ulTemp == ulRegVal), "xspi API LSB/MSB set error!");
    }
    
    //
    // Test Seting The MSB is sent first
    //
    for(i = 0;i < 2; i++)
    {
        ulTemp = SPI_MSB_FIRST;
        SPIConfig(ulSPI[i], 18, ulTemp);
        ulRegVal = xHWREG(ulSPI[i] + SPI_CR1) & SPI_CR1_LSBFIRST;
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
	      SPIConfig(ulSPI[i], 18, SPI_MODE_SLAVE);			
        xSPISSSet(ulSPI[i], xSPI_SS_SOFTWARE, 0);
        ulRegVal = xHWREG(ulSPI[i] + SPI_CR1) & SPI_CR1_SSM;
        TestAssert(( xSPI_SS_SOFTWARE == ulRegVal), 
		             "xspi API Slave select on software error!");
    }
    
    //
    // Set Slave Pin Select basing on xSPI_SS_HARDWARE
    //
    for(i = 0;i < 2;i++)
    {  
	    SPIConfig(ulSPI[i], 18, SPI_MODE_MASTER);
	    xSPISSSet(ulSPI[i], xSPI_SS_HARDWARE, 0);
      ulRegVal = xHWREG(ulSPI[i] + SPI_CR1) & SPI_CR1_SSM; 
      TestAssert(( xSPI_SS_HARDWARE == ulRegVal), 
		               "xspi API Slave select on software error!");
			
	
    }   
}

//*****************************************************************************
//
//! \brief xspi 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi001Execute(void)
{
    xspi_SpiMasterSlaveModeSelect_test();
    xspi_SpiDataWidthSet_test();
    xspi_SpiProtocolSet_test();
    xspi_SpiLsbMsbSet_test();
	  xspi_SpiSlaveSelect_test();
}

//
// xspi register test case struct.
//
const tTestCase sTestXSpi001Register = {
    xSpi001GetTest,
    xSpi001Setup,
    xSpi001TearDown,
    xSpi001Execute
};

//
// Xspi test suits.
//
const tTestCase * const psPatternXspi00[] =
{
    &sTestXSpi001Register,
    0
};
