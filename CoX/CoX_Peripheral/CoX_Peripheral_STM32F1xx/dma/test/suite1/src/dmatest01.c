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
//
//*****************************************************************************
#include "xhw_memmap.h"
#include "test.h"
#include "Xsysctl.h"
#include "xdma.h"
#include "xhw_dma.h"
#include "xspi.h"
#include "xhw_spi.h"

//*****************************************************************************
//
//!\page test_xdma_api
//!
//!<h2>Description</h2>
//!Test xdma api. <br>
//!
//
//*****************************************************************************
unsigned long ulSrcArray[64];
unsigned long ulDestArray[64];
#define DMA_CHANNEL             7

//
// DMA Channel IDs Array
//
unsigned long ulChannelIDArray[15] = 
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
    DMA2_CHANNEL_5,
    13,
    14
};
unsigned long ulDMAbaseArray[] =
{
    0x40020008,
    0x4002001C,
    0x40020030,
    0x40020044,
    0x40020058,
    0x4002006C,
    0x40020080,
    0x40020408,
    0x4002041C,
    0x40020430,
    0x40020444,
    0x40020458
};


//*****************************************************************************
//
//! \brief Get the Test description of xdma002 api test.
//!
//! \return the desccription of the xdma002 test.
//
//*****************************************************************************
static char* xDma002GetTest(void)
{
    return "xdma, 001, DMA Channel Transfer Set Test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xdma002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma002Setup(void)
{

    //
    // Enable Peripheral DMA
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_DMA1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA1);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xdma002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma002TearDown(void)
{   
    SysCtlPeripheralReset(SYSCTL_PERIPH_DMA1);
    //
    // Disable Peripheral DMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_DMA1);  
}

//*****************************************************************************
//
//! \brief xdma 002 test of Channel Transfer Set test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaChannelTransferSetTest(void)
{
    unsigned long i,ulRegVal,ulTemp,ulReg;
    //
    // Test  Channel Transfer Set
    //
    for(i = 0;i < DMA_CHANNEL;i++)
    {
        //
        // Enable DMA channel
        //
        DMADisable(ulChannelIDArray[i]);
        //
        // DMA Channel Control Set
        //
        DMAChannelControlSet(ulChannelIDArray[i], DMA_MEM_WIDTH_32BIT |
                                                  DMA_PER_WIDTH_32BIT |
                                                  DMA_MEM_DIR_INC |   
                                                  DMA_MODE_CIRC_DIS |
                                                  DMA_PER_DIR_INC);
        //
        //DMA Channel Transfer Set
        //
        DMAChannelTransferSet(ulChannelIDArray[i], ulSrcArray, ulDestArray ,64);
        ulRegVal = xHWREG(ulDMAbaseArray[i]) & 0xFC1;
        ulReg = xHWREG(ulDMAbaseArray[i] + 4);
        ulTemp = DMA_MEM_WIDTH_32BIT | DMA_PER_WIDTH_32BIT | DMA_MEM_DIR_INC |   
                 DMA_MODE_CIRC_DIS | DMA_PER_DIR_INC;             
        TestAssert((ulTemp == ulRegVal), 
                  "xspi API \"DMAChannelTransferSet(ulChannelID[i])\"error!");
        TestAssert((ulReg == 64), 
                  "xspi API \"DMAChannelTransferSet(ulChannelID[i])\"error!");
        
        xHWREG(ulDMAbaseArray[i]) = 0x0000;
        xHWREG(ulDMAbaseArray[i]) = 0x0000;
    }

}

//*****************************************************************************
//
//! \brief xdma 002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xDma002Execute(void)
{
    xdmaChannelTransferSetTest();
}

//
// xdma register test case struct.
//
const tTestCase sTestXDma002Api = {
    xDma002GetTest,
    xDma002Setup,
    xDma002TearDown,
    xDma002Execute
};

//
// Xdma test suits.
//
const tTestCase * const psPatternXdma01[] =
{
    &sTestXDma002Api,
    0
};