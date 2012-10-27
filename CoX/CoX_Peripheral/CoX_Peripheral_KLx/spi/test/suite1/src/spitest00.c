//*****************************************************************************
//
//! @page xspi_testcase xcore register test
//!
//! File: @ref spitest00.c
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
//! \file spitest00.c
//! \brief xspi test source file
//! \brief xspi test header file <br>
//
//*****************************************************************************
#include "xhw_spi.h"
#include "test.h"
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
// SPI Group Array
//
static unsigned long ulSPI[2] = {xSPI0_BASE,xSPI1_BASE};

//
// SPI Operation Mode
//
static unsigned long ulSPIOperationMode[] = {xSPI_MODE_MASTER, xSPI_MODE_SLAVE};

//
// SPI Transfers And Receives Data WIDTH
//
static unsigned long ulShiftDirectionTable[] = {xSPI_MSB_FIRST, xSPI_LSB_FIRST};


//
// SPI SPI_FORMAT_MODE Array
//
static unsigned long ulSpiFormatMode[] = {
                        xSPI_MOTO_FORMAT_MODE_0, xSPI_MOTO_FORMAT_MODE_1, 
                        xSPI_MOTO_FORMAT_MODE_2, xSPI_MOTO_FORMAT_MODE_3};


//*****************************************************************************
//
//! \brief Get the Test description of xspi001 register.
//!
//! \return the desccription of the xspi001 test.
//
//*****************************************************************************
static char* xSpi001GetTest(void)
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
    // Enable Peripheral SPI0 and SPI1.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI1);  
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
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI0);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI1);
}

//*****************************************************************************
//
//! \brief xspi 001 test of SPI MASTER/SLAVE Mode Slect.
//!
//! \return None.
//
//*****************************************************************************
static void xspi001_SpiMasterSlaveModeSelect_test(void)
{
    unsigned long i, j,ulRegVal, ulTemp;

    //
    // Test Seting MCU as MASTER/SLAVE Mode
    //
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
        {
            ulTemp = (xSPI_MOTO_FORMAT_MODE_0 | ulSPIOperationMode[j] | xSPI_MSB_FIRST);
            xSPIConfigSet(ulSPI[i], 200000, ulTemp);
            ulRegVal = xHWREGB(ulSPI[i] + SPI_C1) & (ulSPIOperationMode[j] >> 8);
            TestAssert(ulRegVal == (ulSPIOperationMode[j] >> 8), 
                                                "xspi API error!");
        }
    }
}

//*****************************************************************************
//
//! \brief xspi 001 test of Data Shift Direction.
//!
//! \return None.
//
//*****************************************************************************
static void xspi001_SpiLsbMsbSet_test(void)
{
    unsigned long i, j, ulTemp, ulRegVal;
    
    //
    // SPI DataWidth Set Test
    // 
    for(j = 0; j < 2; j++)
    {
        for(i = 0; i < 2; i++)
        {
            ulTemp = (xSPI_MOTO_FORMAT_MODE_0 | xSPI_MODE_SLAVE | ulShiftDirectionTable[i]);
            xSPIConfigSet(ulSPI[j], 200000, ulTemp);
            ulRegVal = xHWREGB(ulSPI[j] + SPI_C1) & ulShiftDirectionTable[i];
            TestAssert(ulShiftDirectionTable[i] == ulRegVal, "xspi API error!");
        }
    }
}

//*****************************************************************************
//
//! \brief xspi 001 test of format mode of SPI Set.
//!
//! \return None.
//
//*****************************************************************************
static void xspi001_SpiFormatModeSet_test(void)
{
    unsigned long i, j, ulTemp, ulRegVal;
        
    //
    // SPI FormatMode Set Test
    // 
    for(j = 0; j < 2; j++)
    {
        for(i = 0; i < 4; i++)
        {
            ulTemp = (ulSpiFormatMode[i] | xSPI_MODE_SLAVE | xSPI_MSB_FIRST);
            xSPIConfigSet(ulSPI[j], 200000, ulTemp);
            ulRegVal = xHWREGB(ulSPI[j] + SPI_C1) & (ulSpiFormatMode[i] >> 16);                     
            TestAssert(ulRegVal == (ulSpiFormatMode[i] >> 16),"xspi API error!"); 
        }
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
    unsigned long i, ulRegVal;
        
    //
    // SPI Enable Test
    // 
    for(i = 0; i < 2; i++)
    {
        SPIEnable(ulSPI[i]);
        ulRegVal = xHWREGB(ulSPI[i] + SPI_C1) & SPI_C1_SPE;
        TestAssert(ulRegVal == SPI_C1_SPE, "xspi API error!");
    }                                                                    
    xspi001_SpiMasterSlaveModeSelect_test();
    xspi001_SpiLsbMsbSet_test();
    xspi001_SpiFormatModeSet_test();
        
    //
    // SPI Disable Test
    // 
    for(i = 0; i < 2; i++)
    {
        SPIDisable(ulSPI[i]);
        ulRegVal = xHWREGB(ulSPI[i] + SPI_C1) & SPI_C1_SPE;
        TestAssert(ulRegVal == 0, "xspi API error!");
    }    
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
