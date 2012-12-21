//*****************************************************************************
//
//! @page xspi_testcase xcore register test
//!
//! File: @ref spitest01.c
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
//! \file spitest01.c
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
// SPI Group Array
//
//static unsigned long ulSPI[2] = {xSPI0_BASE,xSPI1_BASE};


//static unsigned char *pcChars = "SSI Master send data.";

#define W25X80_SELECT()         GPIOPinSet(GPIOC_BASE, 1<<3)
#define W25X80_DESELECT()       GPIOPinSet(GPIOC_BASE, 0<<3)

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
    // Enable Peripheral SPI0 and SPI1.
    //
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
static void xSpi002TearDown(void)
{      
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI0);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI1);
}

//*****************************************************************************
//
//! \brief xspi 002 ssi normal mode init.
//!
//! \return None.
//
//*****************************************************************************
void xspi002_SpiNormalModeInit_test(void)
{
    unsigned long ulTemp;
        
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    xGPIODirModeSet(GPIOC_BASE, GPIO_PIN_3, xGPIO_DIR_MODE_OUT);
    
    ulTemp = (xSPI_MOTO_FORMAT_MODE_0 | xSPI_MODE_MASTER | xSPI_MSB_FIRST);
    xSPIConfigSet(xSPI0_BASE, 2000000, ulTemp);
        
    xSPinTypeSPI(SPI0CLK, PC5);
    xSPinTypeSPI(SPI0CS, PC4);
    xSPinTypeSPI(SPI0MISO, PC7);
    xSPinTypeSPI(SPI0MOSI, PC6);    
    
    SPIEnable(xSPI0_BASE);
}

void W25X80ReadJID(unsigned char cmd, unsigned char* data, unsigned char len)
{
    W25X80_SELECT();
    SPISingleDataReadWrite(xSPI0_BASE, cmd); 
    for(;len>0;len--)
    {
        *data++=SPISingleDataReadWrite(xSPI0_BASE, 0xff);
    }
    W25X80_DESELECT();
}

void W25X80ReadMID(unsigned char cmd, unsigned long addr,
                   unsigned char* data, unsigned char len)
{
    W25X80_SELECT();
    SPISingleDataReadWrite(xSPI0_BASE, cmd); 
    SPISingleDataReadWrite(xSPI0_BASE, (addr >> 16) & 0xff);
    SPISingleDataReadWrite(xSPI0_BASE, (addr >> 8) & 0xff);
    SPISingleDataReadWrite(xSPI0_BASE, addr & 0xff);
    for(;len>0;len--)
    {
        *data++=SPISingleDataReadWrite(xSPI0_BASE, 0xff);
    }
    W25X80_DESELECT();
}

//*****************************************************************************
//
//! \brief xspi 002 ssi normal mode write and read test. read the manufacturer
//!                ID of W25X80A spiflash
//!
//! \return None.
//
//*****************************************************************************
void xspi002_SpiNormalModeRW_test(void)
{
    unsigned char MID[2] = {0};
    unsigned char JID[3] = {0};

    W25X80ReadMID(0x90, 0x000000, MID, 2);
    TestAssert((MID[0] == 0xEF) && (MID[1] == 0x13), "xspi API error!");

    W25X80ReadJID(0x9F, JID, 3);
    //TestAssert((JID[0] == 0xEF) && (JID[1] == 0x30) && (JID[2] == 0x14), 
    //                        "xspi API error!");
                                                
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
    xspi002_SpiNormalModeInit_test();
    //xspi002_SpiNormalModeRW_test();
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
