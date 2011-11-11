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

//
// PDMA Channel IDs Array
//
unsigned long ulChanID[11] = 
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
    9,
    10
};
//
// PDMA Channel Base
//
unsigned long ulPDMABaseAddr[9] = 
{    
    PDMA0_BASE,
    PDMA1_BASE,
    PDMA2_BASE,
    PDMA3_BASE,
    PDMA4_BASE,
    PDMA5_BASE,
    PDMA6_BASE,
    PDMA7_BASE,
    PDMA8_BASE
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
    return "xdma, 003, PDMA Channel Control Set test";
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
    // Enable Peripheral PDMA
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PDMA);
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
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
    SysCtlIPClockDividerSet(SYSCTL_PERIPH_UART_D | 1);
    //
    // Disable Peripheral PDMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_PDMA);  
}

//*****************************************************************************
//
//! \brief xdma 002 test of PDMA Channel Control Set test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaChannelControlSetTest(void)
{
    unsigned long i,ulRegVal,ulTemp;
    
    //
    // Channel Control Set Test
    //
    for(i = 0;i < 9;i++)
    {
        ulTemp = PDMA_WIDTH_8BIT | PDMA_SRC_DIR_INC | PDMA_DST_DIR_FIXED;
        PDMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulPDMABaseAddr[i] + PDMA_CSR);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulPDMABaseAddr[i] + PDMA_CSR) = 0x0000;
    }

    for(i = 0;i < 9;i++)
    {
        ulTemp = PDMA_WIDTH_8BIT | PDMA_SRC_DIR_FIXED | PDMA_DST_DIR_FIXED;
        PDMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulPDMABaseAddr[i] + PDMA_CSR);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulPDMABaseAddr[i] + PDMA_CSR) = 0x0000;
    }

    for(i = 0;i < 9;i++)
    {
        ulTemp = PDMA_WIDTH_8BIT | PDMA_SRC_DIR_INC | PDMA_DST_DIR_INC;
        PDMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulPDMABaseAddr[i] + PDMA_CSR);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulPDMABaseAddr[i] + PDMA_CSR) = 0x0000;
    }

    for(i = 0;i < 9;i++)
    {
        ulTemp = PDMA_WIDTH_8BIT | PDMA_SRC_DIR_FIXED | PDMA_DST_DIR_INC;
        PDMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulPDMABaseAddr[i] + PDMA_CSR);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulPDMABaseAddr[i] + PDMA_CSR) = 0x0000;
    }
    
    for(i = 0;i < 9;i++)
    {
        ulTemp = PDMA_WIDTH_16BIT | PDMA_SRC_DIR_INC | PDMA_DST_DIR_FIXED;
        PDMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulPDMABaseAddr[i] + PDMA_CSR);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulPDMABaseAddr[i] + PDMA_CSR) = 0x0000;
    }
    for(i = 0;i < 9;i++)
    {
        ulTemp = PDMA_WIDTH_16BIT | PDMA_SRC_DIR_INC | PDMA_DST_DIR_INC;
        PDMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulPDMABaseAddr[i] + PDMA_CSR);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulPDMABaseAddr[i] + PDMA_CSR) = 0x0000;
    }

    for(i = 0;i < 9;i++)
    {
        ulTemp = PDMA_WIDTH_16BIT | PDMA_SRC_DIR_FIXED | PDMA_DST_DIR_FIXED;
        PDMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulPDMABaseAddr[i] + PDMA_CSR);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulPDMABaseAddr[i] + PDMA_CSR) = 0x0000;
    }
    
    for(i = 0;i < 9;i++)
    {
        ulTemp = PDMA_WIDTH_16BIT | PDMA_SRC_DIR_FIXED | PDMA_DST_DIR_INC;
        PDMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulPDMABaseAddr[i] + PDMA_CSR);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulPDMABaseAddr[i] + PDMA_CSR) = 0x0000;
    }
    
    for(i = 0;i < 9;i++)
    {
        ulTemp = PDMA_WIDTH_32BIT | PDMA_SRC_DIR_FIXED | PDMA_DST_DIR_INC;
        PDMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulPDMABaseAddr[i] + PDMA_CSR);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulPDMABaseAddr[i] + PDMA_CSR) = 0x0000;
    }
    
    for(i = 0;i < 9;i++)
    {
        ulTemp = PDMA_WIDTH_32BIT | PDMA_SRC_DIR_INC | PDMA_DST_DIR_FIXED;                                       
        PDMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulPDMABaseAddr[i] + PDMA_CSR);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulPDMABaseAddr[i] + PDMA_CSR) = 0x0000;
    }
    
    for(i = 0;i < 9;i++)
    {
        ulTemp =  PDMA_WIDTH_32BIT | PDMA_SRC_DIR_INC | PDMA_DST_DIR_INC;
        PDMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulPDMABaseAddr[i] + PDMA_CSR);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulPDMABaseAddr[i] + PDMA_CSR) = 0x0000;
    }
    
    for(i = 0;i < 9;i++)
    {
        ulTemp = PDMA_WIDTH_32BIT | PDMA_SRC_DIR_FIXED | PDMA_DST_DIR_FIXED;
        PDMAChannelControlSet(ulChanID[i] ,ulTemp);
        ulRegVal = xHWREG(ulPDMABaseAddr[i] + PDMA_CSR);
        TestAssert((ulTemp == ulRegVal), "dma API error!");
        xHWREG(ulPDMABaseAddr[i] + PDMA_CSR) = 0x0000;
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