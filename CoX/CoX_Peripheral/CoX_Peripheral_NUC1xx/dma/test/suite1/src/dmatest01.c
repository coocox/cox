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
unsigned long ulChannelIDArray[11] = 
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
unsigned long ulPDMAbaseArray[9] = 
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
//! \brief Get the Test description of xdma002 api test.
//!
//! \return the desccription of the xdma002 test.
//
//*****************************************************************************
static char* xDma002GetTest(void)
{
    return "xdma, 002, PDMA Channel Transfer Set Test";
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
    // Enable Peripheral PDMA
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PDMA);
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
    SysCtlPeripheralReset(SYSCTL_PERIPH_PDMA);
    //
    // Disable Peripheral PDMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_PDMA);  
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
    for(i = 0;i < 9;i++)
    {
        //
        // Enable PDMA channel
        //
        PDMAEnable(ulChannelIDArray[i]);
        //
        // PDMA Channel Control Set
        //
        PDMAChannelControlSet(ulChannelIDArray[i], PDMA_WIDTH_32BIT 
                                                   | PDMA_SRC_DIR_INC             
                                                   | PDMA_DST_DIR_INC);
        //
        //PDMA Channel Transfer Set
        //
        PDMAChannelTransferSet(ulChannelIDArray[i], ulSrcArray, ulDestArray ,64);
        ulRegVal = xHWREG(ulPDMAbaseArray[i] + PDMA_CSR);
        ulReg = xHWREG(ulPDMAbaseArray[i] + PDMA_BCR);
        ulTemp = PDMA_WIDTH_32BIT | PDMA_SRC_DIR_INC | PDMA_DST_DIR_INC       
                                                     | PDMA_CSR_CEN
                                                     | PDMA_CSR_TEN;             
        TestAssert((ulTemp == ulRegVal), 
                  "xspi API \"PDMAChannelTransferSet(ulChannelID[i])\"error!");
        TestAssert((ulReg == 64), 
                  "xspi API \"PDMAChannelTransferSet(ulChannelID[i])\"error!");
        
        xHWREG(ulPDMAbaseArray[i] + PDMA_CSR) = 0x0000;
        xHWREG(ulPDMAbaseArray[i] + PDMA_BCR) = 0x0000;
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