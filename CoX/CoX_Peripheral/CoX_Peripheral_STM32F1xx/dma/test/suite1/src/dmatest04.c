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
    DMA1_CHANNEL_1,
    DMA1_CHANNEL_2,
    DMA1_CHANNEL_3,
    DMA1_CHANNEL_4,
    DMA1_CHANNEL_5,
    DMA1_CHANNEL_6,
    DMA1_CHANNEL_7,
    DMA2_CHANNEL_1,
    DMA2_CHANNEL_2,
    DMA2_CHANNEL_3,
    DMA2_CHANNEL_4,
    DMA2_CHANNEL_5
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
    return "xdma, 004, xdma memory to SPI";
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
    // Enable Peripheral DMA
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_DMA1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA1);
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
    // Disable Peripheral DMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_DMA1);  
}

//*****************************************************************************
//
//! \brief Ininite the DMA case which is needed
//!
//! \param None
//!
//! \details This function is to ininite the DMA including clock source and 
//!  enable DMA 
//!
//! \return none
//
//*****************************************************************************
void DMAChannel0Init(void)
{
    unsigned long i;
    //
    // Enable Peripheral DMA
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_DMA1);
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA1);
    
    for(i = 0; i < 7; i++)
    {
        DMAChannelDeAssign(ulDMAChannel[i]);
        DMADisable(ulDMAChannel[i]);
    }
    
    ulAssignChannelNum = DMAChannelDynamicAssign(DMA_REQUEST_MEM, 
                                                 DMA_REQUEST_SPI1_TX);

}

//*****************************************************************************
//
//! \brief xdma 005 test of SPI1 initialization.
//!
//! \return None.
//
//*****************************************************************************
static void SPI1Init(void)
{
    //
    // Enable Peripheral SPI1
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI1);  
    SysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO); 
    SysCtlPeripheralEnable(SYSCTL_PERIPH_IOPA); 
    
    //
    // Configure Some GPIO pins as SPI Mode
    //
    xGPIOSDirModeSet(PA5, GPIO_TYPE_IN_FLOATING);
    xGPIOSDirModeSet(PA7, GPIO_TYPE_IN_FLOATING);
    xGPIOSDirModeSet(PA6, GPIO_DIR_MODE_HWSTD);
    xGPIOSDirModeSet(PA4, GPIO_TYPE_IN_FLOATING);
    
    //
    // Master Mode polarity 0,Rx latched at rising edge Tx changed at rising edge
    // 200000Hz 8Bits Data windth  SPI MSB First
    //
    xSPIConfigSet(SPI1_BASE, 10000, SPI_FORMAT_MODE_3 | SPI_DATA_WIDTH8 | 
                                    SPI_LSB_FIRST | SPI_MODE_SLAVE);																							 
    //
    // Software Control Transfer Select SS0
    //
    SPISSModeConfig(SPI1_BASE, SPI_SS_HARDWARE);
    
    SPIDMAEnable(SPI1_BASE, SPI_DMA_TX);
    
    xSPIEnable(SPI1_BASE);
    
}
//*****************************************************************************
//
//! \brief DMA Configure and Trig transfer
//!
//! \param None
//!
//! \details This function is to configure DMA and Trig transfer.
//!
//! \return None
//
//*****************************************************************************
static void xdmaTransferMtoPTest(void)
{
    unsigned long i,ulTemp;
    
    ulTemp = SPI1_BASE + SPI_DR;
    
    DMAChannel0Init();
    SPI1Init();
    
    //
    // Set Channel control  parameter
    //
    DMAChannelControlSet(ulAssignChannelNum, DMA_MEM_WIDTH_8BIT | 
                                             DMA_PER_WIDTH_8BIT |
                                             DMA_MEM_DIR_INC |
                                             DMA_PER_DIR_FIXED);
    //
    // Trig DMA Transfer
    //
    for(i = 0; i < 28; i++)
    {
        xSPIDisable(SPI1_BASE);
        DMAChannelTransferSet(ulAssignChannelNum, ulSrcMem, (void *)ulTemp, 16);
        DMAEnable(ulAssignChannelNum);
        xSPIEnable(SPI1_BASE);
        SPIDataGet(SPI1_BASE, &ulDestSPI[i]);
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