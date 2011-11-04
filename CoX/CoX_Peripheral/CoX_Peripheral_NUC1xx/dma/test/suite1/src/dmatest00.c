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
unsigned long ulSrcArrayTest[64];

unsigned long ulDestArrayTest[64];

//
// PDMA Channel IDs Array
//
unsigned long ulChannelID[11] = 
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
unsigned long ulPDMAbase[9] = 
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

unsigned long ulDestAddr[] = 
{
    xDMA_REQUEST_UART0_TX, 
    xDMA_REQUEST_UART1_TX,   
    xDMA_REQUEST_SPI0_TX, 
    xDMA_REQUEST_SPI1_TX, 
    xDMA_REQUEST_SPI2_TX, 
    xDMA_REQUEST_IIS0_TX, 
    xDMA_REQUEST_SPI3_TX, 
    xDMA_REQUEST_MEM
};

unsigned long ulSourceAddr[] = 
{
    xDMA_REQUEST_UART0_RX, 
    xDMA_REQUEST_UART1_RX,   
    xDMA_REQUEST_SPI0_RX, 
    xDMA_REQUEST_SPI1_RX, 
    xDMA_REQUEST_SPI2_RX, 
    xDMA_REQUEST_IIS0_RX, 
    xDMA_REQUEST_SPI3_RX,
    xDMA_REQUEST_ADC_RX,
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
static void xDma001TearDown(void)
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
//! \brief xdma 001 test of PDMA enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaEnableTest(void)
{
    unsigned long i,ulRegVal,ulReg;
    unsigned long ulTemp = 0;
    //
    // Test PDMA Enable
    //
    for(i = 0;i < 9;i++)
    {
        PDMAEnable(ulChannelID[i]);
        ulRegVal = xHWREG(PDMA_GCRCSR);
        ulTemp |= 1 << (i + 8);
        TestAssert((ulTemp == ulRegVal), "dma API error!"); 
        ulReg = xHWREG(ulPDMAbase[i] + PDMA_CSR);
        TestAssert((ulReg == 0x0001), "dma API error!");
        xHWREG(ulPDMAbase[i] + PDMA_CSR) = 0x0000;
        xHWREG(ulPDMAbase[i] + PDMA_IER) = 0x0000;
    }
}


//*****************************************************************************
//
//! \brief xdma 001 test of PDMA disable test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaDisableTest(void)
{
    unsigned long i,ulRegVal;
    //
    // Test PDMA Disable
    //
    for(i = 0;i < 9;i++)
    {
        PDMADisable(ulChannelID[i]); 
        ulRegVal = xHWREG(ulPDMAbase[i] + PDMA_CSR);
        TestAssert((ulRegVal == 0x0000), "dma API error!");
    }
}


//*****************************************************************************
//
//! \brief xdma 001 test of PDMA reset test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaResetTest(void)
{
    unsigned long i,ulRegVal,ulTemp,ulReg;
    //
    // Test PDMA Reset
    //
    for(i = 0;i < 9;i++)
    {
        PDMAEnable(ulChannelID[i]);
        //
        // PDMA Channel Control Set
        //
        PDMAChannelControlSet(ulChannelID[i], PDMA_WIDTH_32BIT | PDMA_SRC_DIR_INC             
                                                            | PDMA_DST_DIR_INC);
        //
        // PDMA Channel Transfer Set
        //
        PDMAChannelTransferSet(ulChannelID[i], ulSrcArrayTest, 
                                                           ulDestArrayTest ,64);
        //
        // Before the operation of "reset"
        //
        ulTemp = PDMASharedBufferDataGet(ulChannelID[i]);
        ulReg = PDMAInternalBufPointerGet(ulChannelID[i]);
        
        PDMAChannelSoftwareReset(ulChannelID[i]);
        //
        // After the operation of "reset"
        //
        ulTemp = PDMASharedBufferDataGet(ulChannelID[i]);
        ulReg = PDMAInternalBufPointerGet(ulChannelID[i]);
        
        ulRegVal = xHWREG(ulPDMAbase[i] + PDMA_CSR);
        TestAssert((0x00100001 == ulRegVal), "dma API error!");
        
        xHWREG(ulPDMAbase[i] + PDMA_CSR) = 0x0000;
    }

}


//*****************************************************************************
//
//! \brief xdma 001 test of PDMA Interrupt Enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaIntEnableTest(void)
{
    unsigned long i,ulRegVal;
    
    //
    // Test PDMA Interrupt Enable of PDMA_EVENT_TC
    //
    for(i = 0;i < 9;i++)
    {
        PDMAChannelIntEnable(ulChannelID[i] ,PDMA_EVENT_TC);
        ulRegVal = xHWREG(ulPDMAbase[i] + PDMA_IER);
        TestAssert((0x0002 == ulRegVal), "dma API error!");
    }
    
    //
    // Test PDMA Interrupt Enable of PDMA_EVENT_ERROR
    //
    for(i = 0;i < 9;i++)
    {
        PDMAChannelIntEnable(ulChannelID[i] ,PDMA_EVENT_ERROR);
        ulRegVal = xHWREG(ulPDMAbase[i] + PDMA_IER);
        TestAssert((0x0003 == ulRegVal), "dma API error!");
    }

}


//*****************************************************************************
//
//! \brief xdma 001 test of PDMA Channel Dynamic Assign  test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaChannelDynamicAssignTest(void)
{
    unsigned long ulRegVal,i;
    //
    // Test PDMA Channel Dynamic Assign
    //
    for(i = 0; i < 8; i++)
    {
        ulRegVal = PDMAChannelDynamicAssign(xDMA_REQUEST_MEM, ulDestAddr[i]);
        TestAssert(((ulRegVal < 9)&&(ulRegVal >=0)),"dma API error!");
        PDMAChannelDeAssign(ulRegVal);
    }
    
    for(i = 0; i < 9; i++)
    {
        ulRegVal = PDMAChannelDynamicAssign(ulSourceAddr[i], xDMA_REQUEST_MEM);
        TestAssert(((ulRegVal < 9)&&(ulRegVal >=0)),"dma API error!");
    }
    PDMAChannelDeAssign(ulRegVal);
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