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
#include "test.h"
#include "xdma.h"
#include "xhw_dma.h"

//*****************************************************************************
//
//!\page test_xdma_register
//!
//!<h2>Description</h2>
//!Test xdma register. <br>
//!
//
//*****************************************************************************
unsigned long ulSrcArrayTest[64];

unsigned long ulDestArrayTest[64];

//
// DMA Channel IDs Array
//
static unsigned long ulChannelID[4] = 
{
    DMA_CHANNEL_0,
    DMA_CHANNEL_1,
    DMA_CHANNEL_2,
    DMA_CHANNEL_3
};
//
// DMA Channel Base
//
static unsigned long ulDMAbase[4] = 
{    
    DMA0_BASE,
    DMA1_BASE,
    DMA2_BASE,
    DMA3_BASE
};

static unsigned long ulDestAddr[] = 
{
    xDMA_REQUEST_UART0_TX, 
    xDMA_REQUEST_UART1_TX, 
    xDMA_REQUEST_UART2_TX,	
    xDMA_REQUEST_SPI0_TX, 
    xDMA_REQUEST_SPI1_TX, 
    xDMA_REQUEST_MEM
};

static unsigned long ulSourceAddr[] = 
{
    xDMA_REQUEST_UART0_RX, 
    xDMA_REQUEST_UART1_RX,
    xDMA_REQUEST_UART2_RX,	
    xDMA_REQUEST_SPI0_RX, 
    xDMA_REQUEST_SPI1_RX,    
    xDMA_REQUEST_MEM
};
//*****************************************************************************
//
//! \brief Get the Test description of xdma001 register test.
//!
//! \return the desccription of the xdma001 test.
//
//*****************************************************************************
static char* xDma001GetTest(void)
{
    return "xdma, 001, xdma register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xdma001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma001Setup(void)
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
static void xDma001TearDown(void)
{   
    //
    // Disable Peripheral DMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_DMA); 
    SysCtlPeripheralDisable(SYSCTL_PERIPH_DMAMUX); 
}

//*****************************************************************************
//
//! \brief xdma 001 test of DMA enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaEnableTest(void)
{
    unsigned long i,ulRegVal;
    //
    // Test DMA Enable
    //
    for(i = 0; i < 4; i++)
    {
        DMAEnable(ulChannelID[i]);
     
        ulRegVal = xHWREGB(DMAMUX0_BASE + ulChannelID[i]) & DMAMUX0_CHCFG_ENBL;
        TestAssert((ulRegVal == DMAMUX0_CHCFG_ENBL), "dma API error!");
    }
}


//*****************************************************************************
//
//! \brief xdma 001 test of DMA disable test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaDisableTest(void)
{
    unsigned long i,ulRegVal;
    //
    // Test DMA Disable
    //
    for(i = 0; i < 4; i++)
    {
        DMADisable(ulChannelID[i]); 
        ulRegVal = xHWREGB(DMAMUX0_BASE + ulChannelID[i]) & DMAMUX0_CHCFG_ENBL;
        TestAssert(ulRegVal == 0, "dma API error!");
    }
}

//*****************************************************************************
//
//! \brief xdma 001 test of DMA reset test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaResetTest(void)
{
    unsigned long i, ulRegVal, ulTemp;
	
    //
    // Test DMA Reset
    //
    for(i = 0; i < 4; i++)
    {
        DMAEnable(ulChannelID[i]);
		
        //
        // DMA Channel Control Set
        //
        ulTemp = DMA_DST_SIZE_32 | DMA_SRC_SIZE_32 | DMA_SRC_DIR_INC | DMA_DST_DIR_INC;            
                                                             
        DMAChannelControlSet(ulChannelID[i], ulTemp);
	ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR) & 0x007e0000;
        TestAssert(ulRegVal == ulTemp, "DMAChannelControlSet() error!");
		
        //
        // DMA Channel Transfer Set
        //
        DMAChannelTransferSet(ulChannelID[i], ulSrcArrayTest, 
                                                           ulDestArrayTest ,64);
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_SAR);
        TestAssert(ulRegVal == ((unsigned long)(&ulSrcArrayTest) ), 
		                  "DMAChannelTransferSet() error!");
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DAR);
        TestAssert(ulRegVal == ((unsigned long)(&ulDestArrayTest)), 
		                  "DMAChannelTransferSet() error!");
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DSR_BCR) & DMA_DSR_BCR_BCR_M;
        TestAssert(ulRegVal == 64, "DMAChannelTransferSet() error!");
    }
}


//*****************************************************************************
//
//! \brief xdma 001 test of DMA Interrupt Enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaIntEnableTest(void)
{
    unsigned long i,ulRegVal;
    
    //
    // Test DMA Interrupt Enable of DMA_EVENT_TC
    //
    for(i = 0; i < 4; i++)
    {
        DMAChannelIntEnable(ulChannelID[i] ,DMA_EVENT_TC);
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR);
        TestAssert((0x80000000 == ulRegVal), "dma API error!");
    }
    
    //
    // Test DMA Interrupt Enable of DMA_EVENT_ERROR
    //
    for(i = 0; i < 4; i++)
    {
        DMAChannelIntEnable(ulChannelID[i] ,DMA_EVENT_ERROR);
        ulRegVal = xHWREG(ulDMAbase[i] + DMA_DCR);
        TestAssert((0x80000000 == ulRegVal), "dma API error!");
    }
}


//*****************************************************************************
//
//! \brief xdma 001 test of DMA Channel Dynamic Assign  test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaChannelDynamicAssignTest(void)
{
    unsigned long ulRegVal,i;
    
    //
    // Test DMA Channel Dynamic Assign
    //
    for(i = 0; i < 6; i++)
    {
        ulRegVal = DMAChannelDynamicAssign(xDMA_REQUEST_MEM, ulDestAddr[i]);
        TestAssert(((ulRegVal < 4)&&(ulRegVal >=0)), "dma API error!");
        DMAChannelDeAssign(ulRegVal);
    }
    
    for(i = 0; i < 6; i++)
    {
        ulRegVal = DMAChannelDynamicAssign(ulSourceAddr[i], xDMA_REQUEST_MEM);
        TestAssert(((ulRegVal < 4)&&(ulRegVal >=0)),"dma API error!");
        DMAChannelDeAssign(ulRegVal);
    }  
}

//*****************************************************************************
//
//! \brief xdma 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xDma001Execute(void)
{
    xdmaEnableTest();
    xdmaDisableTest();
    xdmaIntEnableTest();
    xdmaChannelDynamicAssignTest();
    xdmaResetTest();
}

//
// xdma register test case struct.
//
const tTestCase sTestXDma001Register = {
    xDma001GetTest,
    xDma001Setup,
    xDma001TearDown,
    xDma001Execute
};

//
// Xdma test suits.
//
const tTestCase * const psPatternXdma00[] =
{
    &sTestXDma001Register,
    0
};