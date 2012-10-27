//*****************************************************************************
//
//! @page xdma_testcase xcore register test
//!
//! File: @ref xdmatest.c
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
//! - \subpage test_xdma_register
//! .
//! \file xdmatest.c
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
//!\page test_xdma_register
//!
//!<h2>Description</h2>
//!Test xdma register. <br>
//!
//
//*****************************************************************************

//
// DMA Channel IDs Array
//
static unsigned long ulChanID[11] = 
{
    DMA_CHANNEL_0,
    DMA_CHANNEL_1,
    DMA_CHANNEL_2,
    DMA_CHANNEL_3
};
//
// DMA Channel Base
//
static unsigned long ulDMAbase[9] = 
{    
    DMA0_BASE,
    DMA1_BASE,
    DMA2_BASE,
    DMA3_BASE
};


//*****************************************************************************
//
//! \brief Get the Test description of xdma003 register test.
//!
//! \return the desccription of the xdma003 test.
//
//*****************************************************************************
static char* xDma002GetTest(void)
{
    return "xdma, 003, DMA Channel Control Set test";
}


//*****************************************************************************
//
//! \brief something should do before the test execute of xdma003 test.
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
//! \brief something should do after the test execute of xdma001 test.
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
//! \brief xdma 002 test of DMA Channel Control Set test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaChannelControlSetTest(void)
{
    unsigned long i, ulRegVal, ulTemp;
    
    //
    // Channel Control Set Test
    //
    for(i = 0; i < 4; i++)
    {
        ulTemp = DMA_DST_SIZE_8 | DMA_SRC_SIZE_8 | DMA_SRC_DIR_INC | DMA_DST_DIR_FIXED;
        DMAChannelControlSet(ulChanID[i], ulTemp);
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR) & 0x007e0000;
        TestAssert((ulTemp == ulRegVal), "dma API error!");
    }

    for(i = 0; i < 4; i++)
    {
        ulTemp = DMA_DST_SIZE_8 | DMA_SRC_SIZE_8 | DMA_SRC_DIR_FIXED | DMA_DST_DIR_FIXED;
        DMAChannelControlSet(ulChanID[i], ulTemp);
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR) & 0x007e0000;
        TestAssert((ulTemp == ulRegVal), "dma API error!");
    }

    for(i = 0;i < 4;i++)
    {
        ulTemp = DMA_DST_SIZE_8 | DMA_SRC_SIZE_8 | DMA_SRC_DIR_INC | DMA_DST_DIR_INC;
        DMAChannelControlSet(ulChanID[i], ulTemp);
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR) & 0x007e0000;
        TestAssert((ulTemp == ulRegVal), "dma API error!");
    }

    for(i = 0; i < 4; i++)
    {
        ulTemp = DMA_DST_SIZE_8 | DMA_SRC_SIZE_8 | DMA_SRC_DIR_FIXED | DMA_DST_DIR_INC;
        DMAChannelControlSet(ulChanID[i], ulTemp);
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR) & 0x007e0000;
        TestAssert((ulTemp == ulRegVal), "dma API error!");
    }
    
    for(i = 0; i < 4; i++)
    {
        ulTemp = DMA_DST_SIZE_16 | DMA_SRC_SIZE_16 | DMA_SRC_DIR_INC | DMA_DST_DIR_FIXED;
        DMAChannelControlSet(ulChanID[i], ulTemp);
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR) & 0x007e0000;
        TestAssert((ulTemp == ulRegVal), "dma API error!");
    }
    for(i = 0; i < 4; i++)
    {
        ulTemp = DMA_DST_SIZE_16 | DMA_SRC_SIZE_16 | DMA_SRC_DIR_INC | DMA_DST_DIR_INC;
        DMAChannelControlSet(ulChanID[i], ulTemp);
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR) & 0x007e0000;
        TestAssert((ulTemp == ulRegVal), "dma API error!");
    }

    for(i = 0; i < 4; i++)
    {
        ulTemp = DMA_DST_SIZE_16 | DMA_SRC_SIZE_16 | DMA_SRC_DIR_FIXED | DMA_DST_DIR_FIXED;
        DMAChannelControlSet(ulChanID[i], ulTemp);
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR) & 0x007e0000;
        TestAssert((ulTemp == ulRegVal), "dma API error!");
    }
    
    for(i = 0; i < 4; i++)
    {
        ulTemp = DMA_DST_SIZE_16 | DMA_SRC_SIZE_16 | DMA_SRC_DIR_FIXED | DMA_DST_DIR_INC;
        DMAChannelControlSet(ulChanID[i], ulTemp);
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR) & 0x007e0000;
        TestAssert((ulTemp == ulRegVal), "dma API error!");
    }
    
    for(i = 0; i < 4; i++)
    {
        ulTemp = DMA_DST_SIZE_32 | DMA_SRC_SIZE_32 | DMA_SRC_DIR_FIXED | DMA_DST_DIR_INC;
        DMAChannelControlSet(ulChanID[i], ulTemp);
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR) & 0x007e0000;
        TestAssert((ulTemp == ulRegVal), "dma API error!");
    }
    
    for(i = 0; i < 4; i++)
    {
        ulTemp = DMA_DST_SIZE_32 | DMA_SRC_SIZE_32 | DMA_SRC_DIR_INC | DMA_DST_DIR_FIXED;                                       
        DMAChannelControlSet(ulChanID[i], ulTemp);
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR) & 0x007e0000;
        TestAssert((ulTemp == ulRegVal), "dma API error!");
    }
    
    for(i = 0; i < 4; i++)
    {
        ulTemp =  DMA_DST_SIZE_32 | DMA_SRC_SIZE_32 | DMA_SRC_DIR_INC | DMA_DST_DIR_INC;
        DMAChannelControlSet(ulChanID[i], ulTemp);
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR) & 0x007e0000;
        TestAssert((ulTemp == ulRegVal), "dma API error!");
    }
    
    for(i = 0; i < 4; i++)
    {
        ulTemp = DMA_DST_SIZE_32 | DMA_SRC_SIZE_32 | DMA_SRC_DIR_FIXED | DMA_DST_DIR_FIXED;
        DMAChannelControlSet(ulChanID[i], ulTemp);
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR) & 0x007e0000;
        TestAssert((ulTemp == ulRegVal), "dma API error!");
    }

}
//*****************************************************************************
//
//! \brief xdma 003 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xDma002Execute(void)
{
    xdmaChannelControlSetTest();
}

//
// xdma register test case struct.
//
const tTestCase sTestXDma002 = {
    xDma002GetTest,
    xDma002Setup,
    xDma002TearDown,
    xDma002Execute
};

//
// Xdma test suits.
//
const tTestCase * const psPatternXdma02[] =
{
    &sTestXDma002,
    0
};