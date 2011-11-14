//*****************************************************************************
//
//! @page xspi_testcase xcore register test
//!
//! File: @ref spitest03.c
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
unsigned long ulSourceData[] = {0x01020304, 0x11121314, 0x21212124, 0x31323334,
                                0x41424344, 0x51525354, 0x61626364, 0x71727374, 
                                0x81828384, 0x91929394, 0xA1A2A3A4, 0xB1B2B3B4, 
                                0xC1C2C3C4, 0xD1D2D3D4, 0xE1E2E3E4, 0xF1F2F3F4};
unsigned long ulDestData[16];

unsigned long SPI0Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('a');
     return 0;
}
//*****************************************************************************
//
//! \brief Get the Test description of xspi004 register test.
//!
//! \return the desccription of the xspi001 test.
//
//*****************************************************************************
static char* xSpi004GetTest(void)
{
    return "xspi, 004, xspi loopback and interrupt test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xspi001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi004Setup(void)
{
    //
    // Set SysClk 36MHz using Extern 12M oscillator
    //
    xSysCtlClockSet(36000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    
    SysCtlPeripheralReset(SYSCTL_PERIPH_SPI0);

    //
    // Enable Peripheral SPI0,SPI1,SPI2 And SPI3
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0);  
}


//*****************************************************************************
//
//! \brief something should do after the test execute of xspi001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi004TearDown(void)
{   
    unsigned long ulTemp;
    ulTemp = SYSCTL_SYSDIV_1|SYSCTL_XTAL_12MHZ|SYSCTL_OSC_MAIN|SYSCTL_PLL_PWRDN
                                                           | SYSCTL_INT_OSC_DIS;
    SysCtlHClockSet(ulTemp);

    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
    SysCtlIPClockDividerSet(SYSCTL_PERIPH_UART_D|0);
    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI0);
}


//*****************************************************************************
//
//! \brief xspi 004 test of SPI0 initialization.
//!
//! \return None.
//
//*****************************************************************************
static void SPI0MasterInit(void)
{
    //
    // Configure Some GPIO pins as SPI Mode
    //
    GPIOPinFunctionSet(GPIO_FUNCTION_SPI, GPIO_PORTC_BASE,GPIO_PIN_2);
    GPIOPinFunctionSet(GPIO_FUNCTION_SPI, GPIO_PORTC_BASE,GPIO_PIN_3);
    GPIOPinFunctionSet(GPIO_FUNCTION_SPI, GPIO_PORTC_BASE,GPIO_PIN_0);
    GPIOPinFunctionSet(GPIO_FUNCTION_SPI, GPIO_PORTC_BASE,GPIO_PIN_1);
    
    //
    // Master Mode polarity 0,Rx latched at rising edge Tx changed at rising edge
    // 200000Hz 8Bits Data windth  SPI MSB First
    //
    SPIConfig(SPI0_BASE, 200000, SPI_FORMAT_MODE_5 | SPI_DATA_WIDTH32 | 
                                               SPI_MSB_FIRST | SPI_MODE_MASTER);
    //
    // HardWare Control Transfer Select SS0
    //
    SPISSSet(SPI0_BASE, SPI_SS0);
    
    SPISSConfig(SPI0_BASE, SPI_SS_LEVEL_TRIGGER, SPI_SS_ACTIVE_HIGH_RISING);
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0);
    
    xIntEnable(INT_SPI0);
    
    xIntPrioritySet(INT_SPI0, 1);
    
    SPIIntEnable(SPI0_BASE, SPI_INT_EOT);
    
    SPIIntCallbackInit(SPI0_BASE, SPI0Callback);
}

//*****************************************************************************
//
//! \brief xspi 004 test of SPI Loopback between SPI0MISO and SPI0MOSI.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SpiLoopbackTest_test(void)
{
    unsigned long i;
    for(i = 0; i < 16; i++)
    {
        ulDestData[i] = SPISingleDataReadWrite(SPI0_BASE, ulSourceData[i]);
        TestAssertQBreak("a", "Transfer Over Interrupy fialed!", 5000000);
    }    
    
    for(i = 0; i < 16; i++)
    {
        TestAssert((ulSourceData[i] == ulDestData[i]), "xspi API error!");
    }
}


//*****************************************************************************
//
//! \brief xspi 004 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi004Execute(void)
{
    SPI0MasterInit();
    xspi_SpiLoopbackTest_test();
}


//
// xspi register test case struct.
//
const tTestCase sTestXSpi004Register = {
    xSpi004GetTest,
    xSpi004Setup,
    xSpi004TearDown,
    xSpi004Execute
};


//
// Xspi test suits.
//
const tTestCase * const psPatternXspi03[] =
{
    &sTestXSpi004Register,
    0
};
