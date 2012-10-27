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
//*****************************************************************************
#include "test.h"
#include "xhw_dma.h"
#include "xdma.h"
#include "xspi.h"
#include "xhw_spi.h"

unsigned char ulSrcMem[] = {"The DMA test data is transfering...\r\n"
              "\r\n"
              "Congratulations! The transport is completed successfully!\r\n"
              "\r\n"  
              "                           machunyu at CooCox Team \r\n"
              "                                               2012.10.16"
};

unsigned long ulAssignChannelNum;

static unsigned long ulDMAChannel[] = 
{
    DMA_CHANNEL_0,
    DMA_CHANNEL_1,
    DMA_CHANNEL_2,
    DMA_CHANNEL_3
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
    return "xdma, 005, xdma memory to UART1";
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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMAMUX);
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
    UARTDMADisable(xUART1_BASE, UART_DMA_TC | UART_DMA_T | UART_DMA_R);
    
    //
    // Disable Peripheral DMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_DMA); 
    SysCtlPeripheralDisable(SYSCTL_PERIPH_DMAMUX);
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
    
    for(i = 0; i < 4; i++)
    {
        DMAChannelDeAssign(ulDMAChannel[i]);
        DMAEnable(ulDMAChannel[i]);
    }
    ulAssignChannelNum = DMAChannelDynamicAssign(DMA_REQUEST_MEM, 
                                                 DMA_REQUEST_UART1_TX);
}

//*****************************************************************************
//
//! \brief xdma 005 test of UART1 DMA function initialization.
//!
//! \return None.
//
//*****************************************************************************
static void UART1Init(void)
{
    UARTDMAEnable(UART1_BASE, UART_DMA_TC | UART_DMA_T);
    UARTIntEnable(UART1_BASE, UART_INT_TC | UART_DMA_T);
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
    unsigned long uli, ulTemp = UART1_BASE + UART_12_D;

    DMAChannel0Init();
    
    UART1Init();

    //
    // Set Channel control  parameter
    //
    DMAChannelControlSet(ulAssignChannelNum, DMA_DST_SIZE_8 | 
                                             DMA_SRC_SIZE_8 | 
	                                     DMA_SRC_DIR_INC |
                                             DMA_DST_DIR_FIXED);
    //
    // DMA Transfer Control
    //
    DMAChannelTransferSet(ulAssignChannelNum, ulSrcMem, (void *)ulTemp, sizeof(ulSrcMem));

    //
    // Trig DMA Transfer
    //
    DMAChannelRequest(ulAssignChannelNum);
    
    uli = 1000;   
    while(uli--);
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