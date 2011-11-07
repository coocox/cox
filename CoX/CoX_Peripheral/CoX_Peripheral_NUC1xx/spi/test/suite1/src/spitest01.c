//*****************************************************************************
//
//! @page xspi_testcase xcore register test
//!
//! File: @ref spitest01.c
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
unsigned long ulSPIBaseAddr[4] = {SPI0_BASE,SPI1_BASE,SPI2_BASE,SPI3_BASE};

//
// SPI Slave Pin Select Array
//
unsigned long ulSPISlavePin[4] = {SPI_SS_NONE,SPI_SS0,SPI_SS1,SPI_SS0_SS1};

//
// SPI SPI_FORMAT_MODE Array
//
unsigned long ulSPIBaseAddrFormatMode[] = {
 SPI_FORMAT_MODE_0,SPI_FORMAT_MODE_1,SPI_FORMAT_MODE_2,
 SPI_FORMAT_MODE_3,SPI_FORMAT_MODE_4,SPI_FORMAT_MODE_5, 
 SPI_FORMAT_MODE_6,SPI_FORMAT_MODE_7};

//
// SPI SPI_BYTEREORDER Array
//
unsigned long ulByteReorder[] = {
  SPI_BYTE_REORDER_SUSPEND_DISABLE, 
  SPI_BYTE_REORDER_SUSPEND, 
  SPI_BYTE_REORDER, SPI_BYTE_SUSPEND};
//*****************************************************************************
//
//! \brief Get the Test description of xspi001 register test.
//!
//! \return the desccription of the xspi001 test.
//
//*****************************************************************************
static char* xSpi002GetTest(void)
{
    return "xspi, 002, spi register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xspi001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi002Setup(void)
{
    //
    // Set SysClk 36MHz using Extern 12M oscillator
    //
    //xSysCtlClockSet(36000000, xSYSCTL_OSC_MAIN|xSYSCTL_XTAL_12MHZ);
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
static void xSpi002TearDown(void)
{   
    unsigned long ulTemp;
    ulTemp = SYSCTL_SYSDIV_1|SYSCTL_XTAL_12MHZ|SYSCTL_OSC_MAIN| SYSCTL_PLL_PWRDN
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
//! \brief xspi 001 test of Setting the slave select pins of the specified SPI port .
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SpiSlavePinSelect_test(void)
{
    unsigned long i,ulRegVal,ulTemp;
    
    ulRegVal = 0;
    
    //
    // Set Slave Pin Select basing on xSPI_SS_SOFTWARE
    //
    for(i = 0;i < 4;i++)
    {  
        ulTemp = ulSPISlavePin[i];
        xSPISSSet(ulSPIBaseAddr[0], xSPI_SS_SOFTWARE, ulTemp);
        ulRegVal = xHWREG(ulSPIBaseAddr[0] + SPI_SSR);
        TestAssert(( ulTemp == ulRegVal), "xspi API error!");
    }
    
    for(i = 0;i < 4;i++)
    {  
        ulTemp = ulSPISlavePin[i];
        xSPISSSet(ulSPIBaseAddr[1],xSPI_SS_SOFTWARE,ulTemp);
        ulRegVal = xHWREG(ulSPIBaseAddr[1]+SPI_SSR);
        TestAssert(( ulTemp == ulRegVal), "xspi API error!");
    }
    
    for(i = 0;i < 4;i++)
    {  
        ulTemp = ulSPISlavePin[i];
        xSPISSSet(ulSPIBaseAddr[2],xSPI_SS_SOFTWARE,ulTemp);
        ulRegVal = xHWREG(ulSPIBaseAddr[2]+SPI_SSR);
        TestAssert(( ulTemp == ulRegVal), "xspi API error!");
    }
    
    for(i = 0;i < 4;i++)
    {  
        ulTemp = ulSPISlavePin[i];
        xSPISSSet(ulSPIBaseAddr[3],xSPI_SS_SOFTWARE,ulTemp);
        ulRegVal = xHWREG(ulSPIBaseAddr[3]+SPI_SSR);
        TestAssert(( ulTemp == ulRegVal), "xspi API error!");
    }
    
    //
    // Set Slave Pin Select basing on xSPI_SS_HARDWARE
    //
    for(i = 0;i < 4;i++)
    {  
        xSPISSSet(ulSPIBaseAddr[0],xSPI_SS_HARDWARE, ulSPISlavePin[i]);
        ulRegVal = xHWREG(ulSPIBaseAddr[0]+SPI_SSR);
        ulTemp = ulSPISlavePin[i] | xSPI_SS_HARDWARE;
        TestAssert(( ulTemp == ulRegVal), "xspi API error!");
    }
    
    for(i = 0;i < 4;i++)
    {  
        xSPISSSet(ulSPIBaseAddr[1],xSPI_SS_HARDWARE,ulSPISlavePin[i]);
        ulRegVal = xHWREG(ulSPIBaseAddr[1]+SPI_SSR);
        ulTemp = ulSPISlavePin[i] | xSPI_SS_HARDWARE;
        TestAssert(( ulTemp == ulRegVal), "xspi API error!");
    }
    
    for(i = 0;i < 4;i++)
    {  
        xSPISSSet(ulSPIBaseAddr[2],xSPI_SS_HARDWARE,ulSPISlavePin[i]);
        ulRegVal = xHWREG(ulSPIBaseAddr[2]+SPI_SSR);
        ulTemp = ulSPISlavePin[i] | xSPI_SS_HARDWARE;
        TestAssert(( ulTemp == ulRegVal), "xspi API error!");
    }
    
    for(i = 0;i < 4;i++)
    {  
        xSPISSSet(ulSPIBaseAddr[3],xSPI_SS_HARDWARE,ulSPISlavePin[i]);
        ulRegVal = xHWREG(ulSPIBaseAddr[3]+SPI_SSR);
        ulTemp = ulSPISlavePin[i] | xSPI_SS_HARDWARE;
        TestAssert(( ulTemp == ulRegVal), "xspi API error!");
    }  
}

//*****************************************************************************
//
//! \brief xspi 001 test of enable SPI auto slave select function .
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SPIAutoSSEnable_test(void)
{
    unsigned long i,ulRegVal,ulTemp;
    
    ulRegVal = 0;
    
    for(i = 0;i < 4;i++)
    {  
        ulTemp = ulSPISlavePin[i];
        SPIAutoSSEnable(ulSPIBaseAddr[0], ulSPISlavePin[i]);
        ulRegVal = xHWREG(ulSPIBaseAddr[0] + SPI_SSR);
        TestAssert(((ulTemp | SPI_AUTOSS)== ulRegVal), "xspi API error!");
    }
    
    for(i = 0;i < 4;i++)
    {  
        ulTemp = ulSPISlavePin[i];
        SPIAutoSSEnable(ulSPIBaseAddr[1], ulSPISlavePin[i]);
        ulRegVal = xHWREG(ulSPIBaseAddr[1]+SPI_SSR);
        TestAssert(((ulTemp | SPI_AUTOSS) == ulRegVal), "xspi API error!");
    }
    
    for(i = 0;i < 4;i++)
    {  
        ulTemp = ulSPISlavePin[i];
        SPIAutoSSEnable(ulSPIBaseAddr[2], ulSPISlavePin[i]);
        ulRegVal = xHWREG(ulSPIBaseAddr[2]+SPI_SSR);
        TestAssert(((ulTemp | SPI_AUTOSS) == ulRegVal), "xspi API error!");
    }
    
    for(i = 0;i < 4;i++)
    {  
        ulTemp = ulSPISlavePin[i];
        SPIAutoSSEnable(ulSPIBaseAddr[3], ulSPISlavePin[i]);
        ulRegVal = xHWREG(ulSPIBaseAddr[3]+SPI_SSR);
        TestAssert(((ulTemp | SPI_AUTOSS)== ulRegVal), "xspi API error!");
    }
}

//*****************************************************************************
//
//! \brief xspi 001 test of SPI ByteReorder Set.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SpiByteReorderSet_test(void)
{
    unsigned long i,ulTempVal,ulRegVal;
    
//
// SPI0 Byte Reorder Set Test
//
    
    for(i = 0;i < 4;i++)
    {
        SPIByteReorderSet(ulSPIBaseAddr[0],ulByteReorder[i]);
        ulRegVal = xHWREG(ulSPIBaseAddr[0] + SPI_CNTRL);
        ulTempVal = (ulByteReorder[i] << SPI_CNTRL_REORDER_S);
        TestAssert(((ulTempVal | 0x05000000) == ulRegVal), "xspi API error!");
        xHWREG(ulSPIBaseAddr[0] + SPI_CNTRL) &= 0x0000;
    }
    
//
// SPI1 Byte Reorder Set Test
//   
    for(i = 0;i < 4;i++)
    {
        SPIByteReorderSet(ulSPIBaseAddr[1],ulByteReorder[i]);
        ulRegVal = xHWREG(ulSPIBaseAddr[1] + SPI_CNTRL);
        ulTempVal = (ulByteReorder[i] << SPI_CNTRL_REORDER_S);
        TestAssert(((ulTempVal | 0x05000000) == ulRegVal), "xspi API error!");
        xHWREG(ulSPIBaseAddr[1] + SPI_CNTRL) &= 0x0000;
    }
    
//
// SPI2 Byte Reorder Set Test
//    
    for(i = 0;i < 4;i++)
    {
        SPIByteReorderSet(ulSPIBaseAddr[2],ulByteReorder[i]);
        ulRegVal = xHWREG(ulSPIBaseAddr[2] + SPI_CNTRL);
        ulTempVal = (ulByteReorder[i] << SPI_CNTRL_REORDER_S);
        TestAssert(((ulTempVal | 0x05000000) == ulRegVal), "xspi API error!");
        xHWREG(ulSPIBaseAddr[2] + SPI_CNTRL) &= 0x0000;
    }
    
//
// SPI3 Byte Reorder Set Test
//
    for(i = 0;i < 4;i++)
    {
        SPIByteReorderSet(ulSPIBaseAddr[3],ulByteReorder[i]);
        ulRegVal = xHWREG(ulSPIBaseAddr[3] + SPI_CNTRL);
        ulTempVal = (ulByteReorder[i] << SPI_CNTRL_REORDER_S);
        TestAssert(((ulTempVal | 0x05000000) == ulRegVal), "xspi API error!");
        xHWREG(ulSPIBaseAddr[3] + SPI_CNTRL) &= 0x0000;
    }
    
}
//*****************************************************************************
//
//! \brief xspi 001 test of enable/disable the DIV_ONE feature .
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SpiDivOneFunctonSet_test(void)
{
    unsigned long i,ulRegVal;
    
    //
    // Test Spi Clock DivOne Mode Functon
    //
    for(i = 0;i < 4;i++)
    {
        SPIDivOneFunction(ulSPIBaseAddr[i], xtrue);
        ulRegVal = xHWREG(ulSPIBaseAddr[i] + SPI_CNTRL2);
        TestAssert(( SPI_CNTRL2_DIV_ONE == ulRegVal), "xspi API error!");
    }
}

//*****************************************************************************
//
//! \brief xspi 001 test of disable SPI auto slave select function .
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SPIAutoSSDisable_test(void)
{
    unsigned long i,ulRegVal;
    
    for(i = 0; i < 4; i++)
    {
        xHWREG(ulSPIBaseAddr[i] + SPI_SSR) &=0x0000;
        SPIAutoSSDisable(ulSPIBaseAddr[i]);
        ulRegVal = xHWREG(ulSPIBaseAddr[i] + SPI_SSR);
        TestAssert(( 0x0000 == ulRegVal), "xspi API error!");
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
    unsigned long i,ulTempVal,ulRegVal;
    
    for(i = 0; i < 4; i++)
    {
        ulTempVal = SPI_SS_EDGE_TRIGGER | SPI_SS_ACTIVE_LOW_FALLING;
        SPISSConfig(ulSPIBaseAddr[i], SPI_SS_EDGE_TRIGGER, SPI_SS_ACTIVE_LOW_FALLING);
        ulRegVal = xHWREG(ulSPIBaseAddr[i] + SPI_SSR);
        TestAssert((ulTempVal == ulRegVal), "xspi API error!");
        xHWREG(ulSPIBaseAddr[i] + SPI_SSR) &= 0x0000;
    }
    
    for(i = 0; i < 4; i++)
    {
        ulTempVal = SPI_SS_EDGE_TRIGGER | SPI_SS_ACTIVE_HIGH_RISING;
        SPISSConfig(ulSPIBaseAddr[i], SPI_SS_EDGE_TRIGGER, SPI_SS_ACTIVE_HIGH_RISING);
        ulRegVal = xHWREG(ulSPIBaseAddr[i] + SPI_SSR);
        TestAssert((ulTempVal == ulRegVal), "xspi API error!");
        xHWREG(ulSPIBaseAddr[i] + SPI_SSR) &= 0x0000;
    }
    
    for(i = 0; i < 4; i++)
    {
        ulTempVal = SPI_SS_LEVEL_TRIGGER | SPI_SS_ACTIVE_LOW_FALLING;
        SPISSConfig(ulSPIBaseAddr[i], SPI_SS_LEVEL_TRIGGER, SPI_SS_ACTIVE_LOW_FALLING);
        ulRegVal = xHWREG(ulSPIBaseAddr[i] + SPI_SSR);
        TestAssert((ulTempVal == ulRegVal), "xspi API error!");
        xHWREG(ulSPIBaseAddr[i] + SPI_SSR) &= 0x0000;
    }
    
    for(i = 0; i < 4; i++)
    {
        ulTempVal = SPI_SS_LEVEL_TRIGGER | SPI_SS_ACTIVE_HIGH_RISING;
        SPISSConfig(ulSPIBaseAddr[i], SPI_SS_LEVEL_TRIGGER, SPI_SS_ACTIVE_HIGH_RISING);
        ulRegVal = xHWREG(ulSPIBaseAddr[i] + SPI_SSR);
        TestAssert((ulTempVal == ulRegVal), "xspi API error!");
        xHWREG(ulSPIBaseAddr[i] + SPI_SSR) &= 0x0000;
    }
    
}

//*****************************************************************************
//
//! \brief xspi 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi002Execute(void)
{
    xspi_SpiSlavePinSelect_test();
    xspi_SpiByteReorderSet_test();
    xspi_SpiDivOneFunctonSet_test();
    xspi_SPIAutoSSEnable_test();
    xspi_SPIAutoSSDisable_test();
    xspi_SPISSConfig_test();
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
const tTestCase * const psPatternXspi01[] =
{
    &sTestXSpi002Register,
    0
};
