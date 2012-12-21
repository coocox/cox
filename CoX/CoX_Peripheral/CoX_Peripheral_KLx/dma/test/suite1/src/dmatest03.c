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

#include "xhw_types.h"
#include "Xsysctl.h"
#include "Xhw_sysctl.h"
#include "xhw_dma.h"
#include "xdma.h"
#include "test.h"
unsigned long ulSrcTemp[64] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
                                0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
                                0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
                                0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
                                0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
                                0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
                                0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
                                0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80};

unsigned long ulDestTemp[64];

unsigned long ulAssignChannel[4];

static unsigned long ulDMAChannelID[] = 
{
    DMA_CHANNEL_0,
    DMA_CHANNEL_1,
    DMA_CHANNEL_2,
    DMA_CHANNEL_3
};

//
// Install callback function
//
unsigned long DmaChannel0Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('a');
     return 0;
}
unsigned long DmaChannel1Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('b');
     return 0;
}
unsigned long DmaChannel2Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('c');
     return 0;
}
unsigned long DmaChannel3Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('d');
     return 0;
}

//
// Callback function
//
xtEventCallback DmaCallbackFunc[4] = {DmaChannel0Callback,
                                      DmaChannel1Callback,
                                      DmaChannel2Callback,
                                      DmaChannel3Callback};
//*****************************************************************************
//
//! \brief Get the Test description of xdma004 register test.
//!
//! \return the desccription of the xdma004 test.
//
//*****************************************************************************
static char* xDma003GetTest(void)
{
    return "xdma, 004, xdma memory to memory and intrrupt test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xdma003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma003Setup(void)
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
static void xDma003TearDown(void)
{   
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
void DMAInit(void)
{
    unsigned long i;

    xIntEnable(INT_DMA0);
    xIntEnable(INT_DMA1);
    xIntEnable(INT_DMA2);
    xIntEnable(INT_DMA3);
    
    for(i = 0; i < 4; i++)
    {
        DMAChannelDeAssign(ulDMAChannelID[i]);
        DMAEnable(ulDMAChannelID[i]);
    }
    
    for(i = 0; i < 4; i++)
    { 
       ulAssignChannel[i] = DMAChannelDynamicAssign(DMA_REQUEST_MEM, 
                                                    DMA_REQUEST_MEM);
    }
    
    for(i = 0; i < 4; i++)
    {
        DMAChannelIntEnable(ulDMAChannelID[i], DMA_EVENT_TC);
        DMAChannelIntCallbackInit(ulDMAChannelID[i], DmaCallbackFunc[i]);
    }
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
static void xdmaTransferTest(void)
{
    unsigned long uli, ulj;
    
    DMAInit();

    for(uli = 0; uli < 4; uli++)
    {
        //
        // Set Channel control  parameter
        //
        DMAChannelControlSet(ulDMAChannelID[uli], DMA_DST_SIZE_32 | 
                                                  DMA_SRC_SIZE_32 |                
                                                  DMA_SRC_DIR_INC |
                                                  DMA_DST_DIR_INC);
        //
        // Trig DMA Transfer
        //
        DMAChannelTransferSet(ulDMAChannelID[uli], ulSrcTemp, ulDestTemp, 64*4);
        
        DMAChannelRequest(ulDMAChannelID[uli]);
        
        //
        // Wait for the end of transmission
        //
        ulj = 1000;
        while(ulj--);
        
        for(ulj = 0; ulj < 64; ulj++)
        {
            TestAssert((ulSrcTemp[ulj] == ulDestTemp[ulj]), "dma API error!");
        }
    }

    TestAssertQBreak("abcd", "Transfer Over Interrupy fialed!", 5000000);
}

//*****************************************************************************
//
//! \brief xdma 004 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xDma003Execute(void)
{
    xdmaTransferTest();
}

//
// xdma register test case struct.
//
const tTestCase sTestXDma003 = {
    xDma003GetTest,
    xDma003Setup,
    xDma003TearDown,
    xDma003Execute
};

//
// Xdma test suits.
//
const tTestCase * const psPatternXdma03[] =
{
    &sTestXDma003,
    0
};