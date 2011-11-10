//*****************************************************************************
//
//! @page xspi_testcase xcore register test
//!
//! File: @ref spitest00.c
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
// SPI Group Array
//
unsigned long ulSPI[4] = {SPI0_BASE,SPI1_BASE,SPI2_BASE,SPI3_BASE};

//
// SPI Transfers And Receives Data WIDTH
//
unsigned long ulDataWidth[] = { 
 SPI_DATA_WIDTH1,SPI_DATA_WIDTH2,SPI_DATA_WIDTH3,SPI_DATA_WIDTH4,
 SPI_DATA_WIDTH5,SPI_DATA_WIDTH6,SPI_DATA_WIDTH7,SPI_DATA_WIDTH8,
 SPI_DATA_WIDTH9,SPI_DATA_WIDTH10,SPI_DATA_WIDTH11,SPI_DATA_WIDTH12,
 SPI_DATA_WIDTH13,SPI_DATA_WIDTH11,SPI_DATA_WIDTH15,SPI_DATA_WIDTH16,
 SPI_DATA_WIDTH17,SPI_DATA_WIDTH18,SPI_DATA_WIDTH19,SPI_DATA_WIDTH20,
 SPI_DATA_WIDTH21,SPI_DATA_WIDTH22,SPI_DATA_WIDTH23,SPI_DATA_WIDTH24,
 SPI_DATA_WIDTH25,SPI_DATA_WIDTH26,SPI_DATA_WIDTH27,SPI_DATA_WIDTH28,
 SPI_DATA_WIDTH29,SPI_DATA_WIDTH30,SPI_DATA_WIDTH31,SPI_DATA_WIDTH32};


//
// SPI SPI_FORMAT_MODE Array
//
unsigned long ulSpiFormatMode[] = {
 SPI_FORMAT_MODE_0,SPI_FORMAT_MODE_1,SPI_FORMAT_MODE_2,
 SPI_FORMAT_MODE_3,SPI_FORMAT_MODE_4,SPI_FORMAT_MODE_5, 
 SPI_FORMAT_MODE_6,SPI_FORMAT_MODE_7};


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
//! \brief something should do after the test execute of xspi001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi001TearDown(void)
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
    for(i = 0; i < 4; i++)
    {
        ulTemp = SPI_MODE_SLAVE;
        SPIConfig(ulSPI[i], 18, ulTemp);
        ulRegVal = xHWREG(ulSPI[i] + SPI_CNTRL);
        TestAssert(((ulTemp | 0x05000004) == ulRegVal), "xspi API error!");
        xHWREG(ulSPI[i] + SPI_CNTRL) &= 0x0000;
    }
    
    //
    // Test Seting MCU as Master
    //
    for(i = 0; i < 4; i++)
    {
        ulTemp = SPI_MODE_MASTER;
        SPIConfig(ulSPI[i], 18, ulTemp);
        ulRegVal = xHWREG(ulSPI[i] + SPI_CNTRL);
        TestAssert(((ulTemp | 0x05000000) == ulRegVal), "xspi API error!");
        xHWREG(ulSPI[i] + SPI_CNTRL) &= 0x0000;
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
    
    for(i = 0; i < 32; i++)
    {
        unsigned long ulReturnWidth;
        ulTemp = ulDataWidth[i];
        SPIConfig(ulSPI[0], 18,ulTemp);
        ulReturnWidth = SPIBitLengthGet(ulSPI[0]);
        ulRegVal = ulReturnWidth << 3;
        TestAssert((ulTemp == ulRegVal), "xspi API error!");
        xHWREG(ulSPI[0] + SPI_CNTRL) &= 0x0000;
    }
    
//
// SPI1 DataWidth Set Test
//   
    for(i = 0; i < 32; i++)
    {
        unsigned long ulReturnWidth;
        ulTemp = ulDataWidth[i];
        SPIConfig(ulSPI[1], 18,ulTemp);
        ulReturnWidth = SPIBitLengthGet(ulSPI[1]);
        ulRegVal = ulReturnWidth << 3;
        TestAssert(( ulTemp == ulRegVal), "xspi API error!");
        xHWREG(ulSPI[1] + SPI_CNTRL) &= 0x0000;
        
    }
    
//
// SPI2 DataWidth Set Test
//    
    for(i = 0;i < 32;i++)
    {
        unsigned long ulReturnWidth;
        ulTemp = ulDataWidth[i];
        SPIConfig(ulSPI[2], 18,ulTemp);
        ulReturnWidth = SPIBitLengthGet(ulSPI[2]);
        ulRegVal = ulReturnWidth << 3;
        TestAssert(( ulTemp == ulRegVal), "xspi API error!");
        xHWREG(ulSPI[2] + SPI_CNTRL) &= 0x0000;
    }
    
//
// SPI3 DataWidth Set Test
//
    for(i = 0;i < 32;i++)
    {
        unsigned long ulReturnWidth;
        ulTemp = ulDataWidth[i];
        SPIConfig(ulSPI[3], 18,ulTemp);
        ulReturnWidth = SPIBitLengthGet(ulSPI[3]);
        ulRegVal = ulReturnWidth << 3;
        TestAssert(( ulTemp == ulRegVal), "xspi API error!");
        xHWREG(ulSPI[3] + SPI_CNTRL) &= 0x0000;
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
    for(i = 0;i < 8; i++)
    {
        ulTemp = ulSpiFormatMode[i];
        SPIConfig(ulSPI[0], 18,ulTemp);
        ulRegVal = xHWREG(ulSPI[0] + SPI_CNTRL);
        TestAssert(((ulTemp | 0x05000000) == ulRegVal), "xspi API error!");
        xHWREG(ulSPI[0] + SPI_CNTRL) &= 0x0000;
    }

    for(i = 0;i < 8; i++)
    {
        xHWREG(ulSPI[1] + SPI_CNTRL) &= 0x0000;
        ulTemp = ulSpiFormatMode[i];
        SPIConfig(ulSPI[1], 18,ulTemp);
        ulRegVal = xHWREG(ulSPI[1] + SPI_CNTRL);
        TestAssert(((ulTemp | 0x05000000) == ulRegVal), "xspi API error!");
    }
    
    for(i = 0;i < 8; i++)
    {
        xHWREG(ulSPI[2] + SPI_CNTRL) &= 0x0000;
        ulTemp = ulSpiFormatMode[i];
        SPIConfig(ulSPI[2], 18,ulTemp);
        ulRegVal = xHWREG(ulSPI[2] + SPI_CNTRL);
        TestAssert(((ulTemp | 0x05000000) == ulRegVal), "xspi API error!");
    }
    
    for(i = 0;i < 8; i++)
    {
        xHWREG(ulSPI[3] + SPI_CNTRL) &= 0x0000;
        ulTemp = ulSpiFormatMode[i];
        SPIConfig(ulSPI[3], 18,ulTemp);
        ulRegVal = xHWREG(ulSPI[3] + SPI_CNTRL);
        TestAssert(((ulTemp | 0x05000000) == ulRegVal), "xspi API error!");

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
    for(i = 0;i < 4;i++)
    {
        xHWREG(ulSPI[i] + SPI_CNTRL) &= 0x0000;
        ulTemp = SPI_LSB_FIRST;
        SPIConfig(ulSPI[i],18,ulTemp);
        ulRegVal = xHWREG(ulSPI[i] + SPI_CNTRL);
        TestAssert(((ulTemp | 0x05000000) == ulRegVal), "xspi API error!");
    }
    
    //
    // Test Seting The MSB is sent first
    //
    for(i = 0;i < 4;i++)
    {
        xHWREG(ulSPI[i] + SPI_CNTRL) &= 0x0000;
        ulTemp = SPI_MSB_FIRST;
        SPIConfig(ulSPI[i],18,ulTemp);
        ulRegVal = xHWREG(ulSPI[i] + SPI_CNTRL);
        TestAssert(((ulTemp | 0x05000000) == ulRegVal), "xspi API error!");
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
