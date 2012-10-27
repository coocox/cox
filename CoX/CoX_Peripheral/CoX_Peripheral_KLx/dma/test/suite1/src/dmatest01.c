//*****************************************************************************
//
//! @page xdma_testcase xcore api test
//!
//! File: @ref xdmaAPItest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xdma sub component.<br><br>
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
//! - \subpage test_xdma_api
//! .
//! \file xdmaAPItest.c
//! \brief xdma test source file
//! \brief xdma test header file <br>
//
//*****************************************************************************
#include "test.h"
#include "xhw_dma.h"
#include "xdma.h"

//*****************************************************************************
//
//!\page test_xdma_api
//!
//!<h2>Description</h2>
//!Test xdma api. <br>
//!
//
//*****************************************************************************
static unsigned long ulChannelIDArray[] = 
{
    DMA_CHANNEL_0,
    DMA_CHANNEL_1,
    DMA_CHANNEL_2,
    DMA_CHANNEL_3
};

static unsigned long ulAddModVal[] = {
  DMA_MOD_0, DMA_MOD_16, DMA_MOD_32, DMA_MOD_64, DMA_MOD_128, DMA_MOD_256, 
  DMA_MOD_512, DMA_MOD_1k, DMA_MOD_2k, DMA_MOD_4k, DMA_MOD_8k, DMA_MOD_16k,
  DMA_MOD_32k, DMA_MOD_64k, DMA_MOD_128k, DMA_MOD_256k
};

//
// DMA Channel Base
//
static unsigned long ulDMAbase[] = 
{    
    DMA0_BASE,
    DMA1_BASE,
    DMA2_BASE,
    DMA3_BASE
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
    return "xdma, 002, DMA Channel Transfer Address Modulo Set Test";
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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMAMUX);
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
    //
    // Disable Peripheral DMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_DMA);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_DMAMUX);  
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
    unsigned long i, j, ulRegVal;
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 16; j++)
        { 
            DMATransferAddressModulo(ulChannelIDArray[i], ulAddModVal[j], DMA_MOD_SMODE);
            ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR) & DMA_DCR_SMOD_M;
            TestAssert((ulRegVal == (ulAddModVal[j] << DMA_DCR_SMOD_S)), "dma API error!");  
        }
                     
        for(j = 0; j < 16; j++)
        { 
            DMATransferAddressModulo(ulChannelIDArray[i], ulAddModVal[j], DMA_MOD_DMODE);
            ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR) & DMA_DCR_DMOD_M;
            TestAssert((ulRegVal == (ulAddModVal[j] << DMA_DCR_DMOD_S)), "dma API error!");  
        }
    }
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