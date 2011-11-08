//*****************************************************************************
//
//! @page xdma_testcase xcore api test
//!
//! File: @ref xdmaAPItest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xdma sub component.<br><br>
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
//! - \subpage test_xdma_api
//! .
//! \file xdmaAPItest.c
//! \brief xdma test source file
//! \brief xdma test header file <br>
//*****************************************************************************

#include "xhw_types.h"
#include "Xsysctl.h"
#include "Xhw_sysctl.h"
#include "xhw_dma.h"
#include "xdma.h"
#include "test.h"
#include "xspi.h"
#include "xhw_spi.h"

unsigned long ulSrcMem[28] = {0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
                              0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
                              0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
                              0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
                              0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
                              0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
                              0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80};

unsigned long ulDestSPI[28];

unsigned long ulAssignChannelNum;

unsigned long ulDMAChannel[] = 
{
    PDMA_CHANNEL_0,
    PDMA_CHANNEL_1,
    PDMA_CHANNEL_2,
    PDMA_CHANNEL_3,
    PDMA_CHANNEL_4,
    PDMA_CHANNEL_5,
    PDMA_CHANNEL_6,
    PDMA_CHANNEL_7,
    PDMA_CHANNEL_8,
};


//*****************************************************************************
//
//! \brief Get the Test description of xdma003 register test.
//!
//! \return the desccription of the xdma003 test.
//
//*****************************************************************************
static char* xDma005GetTest(void)
{
    return "xdma, 005, xdma memory to SPI";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xdma005 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma005Setup(void)
{
    //
    // Enable Peripheral PDMA
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PDMA);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xdma003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma005TearDown(void)
{   
    //
    // Disable Peripheral PDMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_PDMA);  
}

//*****************************************************************************
//
//! \brief Ininite the PDMA case which is needed
//!
//! \param None
//!
//! \details This function is to ininite the PDMA including clock source and 
//!  enable PDMA 
//!
//! \return none
//
//*****************************************************************************
void PDMAChannel0Init(void)
{
    unsigned long i;
    //
    // Enable Peripheral PDMA
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_PDMA);
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PDMA);
    
    for(i = 0; i < 9; i++)
    {
        PDMAChannelDeAssign(ulDMAChannel[i]);
        PDMAEnable(ulDMAChannel[i]);
    }
    
    ulAssignChannelNum = PDMAChannelDynamicAssign(PDMA_REQUEST_MEM, 
                                                          PDMA_REQUEST_SPI0_TX);

}

//*****************************************************************************
//
//! \brief xdma 005 test of SPI0 initialization.
//!
//! \return None.
//
//*****************************************************************************
static void SPI0Init(void)
{
    //
    // Configure Some GPIO pins as SPI Mode
    //
    GPIOPinFunctionSet(GPIO_FUNCTION_SPI, GPIO_PORTC_BASE,GPIO_PIN_2);
    GPIOPinFunctionSet(GPIO_FUNCTION_SPI, GPIO_PORTC_BASE,GPIO_PIN_3);
    GPIOPinFunctionSet(GPIO_FUNCTION_SPI, GPIO_PORTC_BASE,GPIO_PIN_0);
    GPIOPinFunctionSet(GPIO_FUNCTION_SPI, GPIO_PORTC_BASE,GPIO_PIN_1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0);
    
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
    
    SPI3PDMAEnable(SPI0_BASE, SPI_DMA_BOTH);
}
//*****************************************************************************
//
//! \brief PDMA Configure and Trig transfer
//!
//! \param None
//!
//! \details This function is to configure PDMA and Trig transfer.
//!
//! \return None
//
//*****************************************************************************
static void xdmaTransferMtoPTest(void)
{
    unsigned long i,ulTemp;
    
    ulTemp = SPI0_BASE + SPI_TX0;
    
    PDMAChannel0Init();
    SPI0Init();
    
    //
    // Set Channel control  parameter
    //
    PDMAChannelControlSet(ulAssignChannelNum, PDMA_WIDTH_32BIT | PDMA_SRC_DIR_INC 
                                                          | PDMA_DST_DIR_FIXED);
    //
    // Trig DMA Transfer
    //
    for(i = 0; i < 28; i++)
    {
        PDMAChannelTransferSet(ulAssignChannelNum, ulSrcMem, (void *)ulTemp, 16);
        SPIBitGoBusySet(SPI0_BASE);
        SPIRxRegisterGet(SPI0_BASE, &ulDestSPI[i], 1);
    }

    for(i = 0;i < 28;i++)
    {
        TestAssert((0x00 != ulDestSPI[i]), "dma API error!");
    }
}

//*****************************************************************************
//
//! \brief xdma 005 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xDma005Execute(void)
{
    xdmaTransferMtoPTest();
}

//
// xdma register test case struct.
//
const tTestCase sTestXDma004 = {
    xDma005GetTest,
    xDma005Setup,
    xDma005TearDown,
    xDma005Execute
};

//
// Xdma test suits.
//
const tTestCase * const psPatternXdma04[] =
{
    &sTestXDma004,
    0
};