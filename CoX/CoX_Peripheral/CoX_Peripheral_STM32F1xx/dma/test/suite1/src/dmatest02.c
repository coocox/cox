//*****************************************************************************
//
//! @page xdma_testcase xcore register test
//!
//! File: @ref xdmatest.c
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
#define DMA_CHANNEL             7
//
// DMA Channel IDs Array
//
unsigned long ulChanID[15] = 
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
unsigned long ulDMABaseAddr[] =
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

unsigned long ulControl[] =
{
    xDMA_SRC_SIZE_8 | xDMA_DST_SIZE_8 | xDMA_SRC_INC_8 | xDMA_DST_INC_NONE,
    xDMA_SRC_SIZE_8 | xDMA_DST_SIZE_16 | xDMA_SRC_INC_8 | xDMA_DST_INC_NONE,
    xDMA_SRC_SIZE_8 | xDMA_DST_SIZE_32 | xDMA_SRC_INC_8 | xDMA_DST_INC_NONE,
    xDMA_SRC_SIZE_16 | xDMA_DST_SIZE_32 | xDMA_SRC_INC_8 | xDMA_DST_INC_NONE,
    xDMA_SRC_SIZE_8 | xDMA_DST_SIZE_8 | xDMA_SRC_INC_NONE | xDMA_DST_INC_NONE,
    xDMA_SRC_SIZE_8 | xDMA_DST_SIZE_16 | xDMA_SRC_INC_NONE | xDMA_DST_INC_NONE,
    xDMA_SRC_SIZE_8 | xDMA_DST_SIZE_32 | xDMA_SRC_INC_NONE | xDMA_DST_INC_NONE,
    xDMA_SRC_SIZE_16 | xDMA_DST_SIZE_32 | xDMA_SRC_INC_NONE | xDMA_DST_INC_NONE,
    xDMA_SRC_SIZE_8 | xDMA_DST_SIZE_8 | xDMA_SRC_INC_NONE | xDMA_DST_INC_8,
    xDMA_SRC_SIZE_8 | xDMA_DST_SIZE_16 | xDMA_SRC_INC_NONE | xDMA_DST_INC_8,
    xDMA_SRC_SIZE_8 | xDMA_DST_SIZE_32 | xDMA_SRC_INC_NONE | xDMA_DST_INC_8,
    xDMA_SRC_SIZE_32 | xDMA_DST_SIZE_16 | xDMA_SRC_INC_NONE | xDMA_DST_INC_8,
    xDMA_SRC_SIZE_32 | xDMA_DST_SIZE_8 | xDMA_SRC_INC_NONE | xDMA_DST_INC_8,
    xDMA_SRC_SIZE_32 | xDMA_DST_SIZE_32 | xDMA_SRC_INC_NONE | xDMA_DST_INC_8,
    xDMA_SRC_SIZE_16 | xDMA_DST_SIZE_8 | xDMA_SRC_INC_NONE | xDMA_DST_INC_8,
    xDMA_SRC_SIZE_16 | xDMA_DST_SIZE_32 | xDMA_SRC_INC_NONE | xDMA_DST_INC_8
};

unsigned long ulControlget[] =
{
    xDMA_DST_SIZE_8 | xDMA_SRC_SIZE_8 | xDMA_DST_INC_8 | xDMA_SRC_INC_NONE,
    xDMA_DST_SIZE_8 | xDMA_SRC_SIZE_16 | xDMA_DST_INC_8 | xDMA_SRC_INC_NONE,
    xDMA_DST_SIZE_8 | xDMA_SRC_SIZE_32 | xDMA_DST_INC_8 | xDMA_SRC_INC_NONE,
    xDMA_DST_SIZE_16 | xDMA_SRC_SIZE_32 | xDMA_DST_INC_8 | xDMA_SRC_INC_NONE,
    xDMA_DST_SIZE_8 | xDMA_SRC_SIZE_8 | xDMA_DST_INC_NONE | xDMA_SRC_INC_NONE,
    xDMA_DST_SIZE_8 | xDMA_SRC_SIZE_16 | xDMA_DST_INC_NONE | xDMA_SRC_INC_NONE,
    xDMA_DST_SIZE_8 | xDMA_SRC_SIZE_32 | xDMA_DST_INC_NONE | xDMA_SRC_INC_NONE,
    xDMA_DST_SIZE_16 | xDMA_SRC_SIZE_32 | xDMA_DST_INC_NONE | xDMA_SRC_INC_NONE,
    xDMA_DST_SIZE_8 | xDMA_SRC_SIZE_8 | xDMA_DST_INC_NONE | xDMA_SRC_INC_8,
    xDMA_DST_SIZE_8 | xDMA_SRC_SIZE_16 | xDMA_DST_INC_NONE | xDMA_SRC_INC_8,
    xDMA_DST_SIZE_8 | xDMA_SRC_SIZE_32 | xDMA_DST_INC_NONE | xDMA_SRC_INC_8,
    xDMA_DST_SIZE_32 | xDMA_SRC_SIZE_16 | xDMA_DST_INC_NONE | xDMA_SRC_INC_8,
    xDMA_DST_SIZE_32 | xDMA_SRC_SIZE_8 | xDMA_DST_INC_NONE | xDMA_SRC_INC_8,
    xDMA_DST_SIZE_32 | xDMA_SRC_SIZE_32 | xDMA_DST_INC_NONE | xDMA_SRC_INC_8,
    xDMA_DST_SIZE_16 | xDMA_SRC_SIZE_8 | xDMA_DST_INC_NONE | xDMA_SRC_INC_8,
    xDMA_DST_SIZE_16 | xDMA_SRC_SIZE_32 | xDMA_DST_INC_NONE | xDMA_SRC_INC_8
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
    return "xdma, 002, DMA Channel Control Set test";
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
    SysCtlPeripheralReset(SYSCTL_PERIPH_DMA1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA1);
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
    SysCtlPeripheralDisable(SYSCTL_PERIPH_DMA1);  
}
//*****************************************************************************
//
//! \brief xdma 002 test of xDMA Channel Control Set test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaChannelControlSetTest(void)
{
    unsigned long i,ulRegVal,ulTemp;
    unsigned long ulChannel;
     
    for(i = 0;i < 16;i++)
    {
        ulChannel = DMAChannelDynamicAssign(xDMA_REQUEST_MEM, DMA_REQUEST_UART3_TX);
        ulTemp = ulControl[i];
        xDMAChannelControlSet(ulChannel ,ulControl[i]);
        DMAChannelDeAssign(ulChannel);
        ulRegVal = xHWREG(ulDMABaseAddr[ulChannel]);
        ulRegVal &= ~DMA_CCR1_DIR;
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulDMABaseAddr[ulChannel]) = 0x0000;
        
        ulChannel = DMAChannelDynamicAssign(DMA_REQUEST_ADC0_RX, xDMA_REQUEST_MEM);
        xDMAChannelControlSet(ulChannel ,ulTemp);
        DMAChannelDeAssign(ulChannel);
        ulTemp = ulControlget[i];
        ulRegVal = xHWREG(ulDMABaseAddr[ulChannel]);
        ulRegVal &= ~DMA_CCR1_DIR;
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulDMABaseAddr[ulChannel]) = 0x0000;
    }    
}

//*****************************************************************************
//
//! \brief xdma 002 test of DMA Channel Control Set test .
//!
//! \return None.
//
//*****************************************************************************
static void dmaChannelControlSetTest(void)
{
    unsigned long i,ulRegVal,ulTemp;
    
    //
    // Channel Control Set Test
    //
    for(i = 0;i < DMA_CHANNEL;i++)
    {
        ulTemp = DMA_MEM_WIDTH_8BIT | DMA_PER_WIDTH_8BIT | DMA_MEM_DIR_INC | 
                 DMA_PER_DIR_FIXED;
        DMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulDMABaseAddr[i]);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulDMABaseAddr[i]) = 0x0000;

    } 

    for(i = 0;i < DMA_CHANNEL;i++)
    {
        ulTemp = DMA_MEM_WIDTH_8BIT | DMA_PER_WIDTH_8BIT | DMA_MEM_DIR_FIXED | 
                 DMA_PER_DIR_FIXED;
        DMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulDMABaseAddr[i]);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulDMABaseAddr[i]) = 0x0000;
    }

    for(i = 0;i < DMA_CHANNEL;i++)
    {
        ulTemp = DMA_MEM_WIDTH_8BIT | DMA_PER_WIDTH_8BIT | DMA_MEM_DIR_INC | 
                 DMA_PER_DIR_INC;
        DMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulDMABaseAddr[i]);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulDMABaseAddr[i]) = 0x0000;
    }

    for(i = 0;i < DMA_CHANNEL;i++)
    {
        ulTemp = DMA_MEM_WIDTH_8BIT | DMA_PER_WIDTH_8BIT | DMA_MEM_DIR_FIXED | 
                 DMA_PER_DIR_INC;
        DMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulDMABaseAddr[i]);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulDMABaseAddr[i]) = 0x0000;
    }
    
    for(i = 0;i < DMA_CHANNEL;i++)
    {
        ulTemp = DMA_MEM_WIDTH_16BIT | DMA_PER_WIDTH_16BIT | DMA_MEM_DIR_INC | 
                 DMA_PER_DIR_FIXED;
        DMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulDMABaseAddr[i]);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulDMABaseAddr[i]) = 0x0000;
        
    } 

    for(i = 0;i < DMA_CHANNEL;i++)
    {
        ulTemp = DMA_MEM_WIDTH_16BIT | DMA_PER_WIDTH_16BIT | DMA_MEM_DIR_FIXED | 
                 DMA_PER_DIR_FIXED;
        DMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulDMABaseAddr[i]);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulDMABaseAddr[i]) = 0x0000;
    }

    for(i = 0;i < DMA_CHANNEL;i++)
    {
        ulTemp = DMA_MEM_WIDTH_16BIT | DMA_PER_WIDTH_16BIT | DMA_MEM_DIR_INC | 
                 DMA_PER_DIR_INC;
        DMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulDMABaseAddr[i]);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulDMABaseAddr[i]) = 0x0000;
    }

    for(i = 0;i < DMA_CHANNEL;i++)
    {
        ulTemp = DMA_MEM_WIDTH_16BIT | DMA_PER_WIDTH_16BIT | DMA_MEM_DIR_FIXED | 
                 DMA_PER_DIR_INC;
        DMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulDMABaseAddr[i]);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulDMABaseAddr[i]) = 0x0000;
    }
    for(i = 0;i < DMA_CHANNEL;i++)
    {
        ulTemp = DMA_MEM_WIDTH_32BIT | DMA_PER_WIDTH_32BIT | DMA_MEM_DIR_INC | 
                 DMA_PER_DIR_FIXED;
        DMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulDMABaseAddr[i]);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulDMABaseAddr[i]) = 0x0000;
        
    } 

    for(i = 0;i < DMA_CHANNEL;i++)
    {
        ulTemp = DMA_MEM_WIDTH_32BIT | DMA_PER_WIDTH_32BIT | DMA_MEM_DIR_FIXED | 
                 DMA_PER_DIR_FIXED;
        DMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulDMABaseAddr[i]);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulDMABaseAddr[i]) = 0x0000;
    }

    for(i = 0;i < DMA_CHANNEL;i++)
    {
        ulTemp = DMA_MEM_WIDTH_32BIT | DMA_PER_WIDTH_32BIT | DMA_MEM_DIR_INC | 
                 DMA_PER_DIR_INC;
        DMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulDMABaseAddr[i]);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulDMABaseAddr[i]) = 0x0000;
    }

    for(i = 0;i < DMA_CHANNEL;i++)
    {
        ulTemp = DMA_MEM_WIDTH_32BIT | DMA_PER_WIDTH_32BIT | DMA_MEM_DIR_FIXED | 
                 DMA_PER_DIR_INC;
        DMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulDMABaseAddr[i]);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulDMABaseAddr[i]) = 0x0000;
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
    dmaChannelControlSetTest();
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