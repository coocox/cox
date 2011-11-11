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

unsigned long ulAssignChannel[9];

unsigned long ulDMAChannelID[] = 
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

unsigned long DmaChannel4Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('e');
     return 0;
}
unsigned long DmaChannel5Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('f');
     return 0;
}

unsigned long DmaChannel6Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('g');
     return 0;
}

unsigned long DmaChannel7Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('h');
     return 0;
}

unsigned long DmaChannel8Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('i');
     return 0;
}
//
// Callback function
//
xtEventCallback DmaCallbackFunc[9] = {DmaChannel0Callback,
                                      DmaChannel1Callback,
                                      DmaChannel2Callback,
                                      DmaChannel3Callback,
                                      DmaChannel4Callback,
                                      DmaChannel5Callback,
                                      DmaChannel6Callback,
                                      DmaChannel7Callback,
                                      DmaChannel8Callback};
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
    // Enable Peripheral PDMA
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PDMA);
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
    // Disable Peripheral PDMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_PDMA);  
}

//*****************************************************************************
//
//! \brief Ininite the PDMA case which is needed
//!
//! \param None
//!
//! \details This function is to ininite the PDMA including clock source and 
//!  enable PDMA 
//!
//! \return none
//
//*****************************************************************************
void PDMAInit(void)
{
    unsigned long i;
    //
    // Enable Peripheral PDMA
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_PDMA);
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PDMA);
    
    xIntEnable(INT_PDMA);
    
    xIntPrioritySet(INT_PDMA, 1);
    
    for(i = 0; i < 9; i++)
    {
        PDMAChannelDeAssign(ulDMAChannelID[i]);
        PDMAEnable(ulDMAChannelID[i]);
    }
    
    for(i = 0; i < 9; i++)
    { 
       ulAssignChannel[i] = PDMAChannelDynamicAssign(PDMA_REQUEST_MEM, 
                                                              PDMA_REQUEST_MEM);
    }
    
    for(i = 0; i < 9; i++)
    {
        PDMAChannelIntEnable(ulDMAChannelID[i], PDMA_EVENT_TC);
        PDMAChannelIntCallbackInit(ulDMAChannelID[i], DmaCallbackFunc[i]);
    }
}

//*****************************************************************************
//
//! \brief PDMA Configure and Trig transfer
//!
//! \param None
//!
//! \details This function is to configure PDMA and Trig transfer.
//!
//! \return None
//
//*****************************************************************************
static void xdmaTransferTest(void)
{
    unsigned long i;
    
    PDMAInit();
    
    for(i = 0; i < 9; i++)
    {
    //
    // Set Channel control  parameter
    //
        PDMAChannelControlSet(ulDMAChannelID[i], PDMA_WIDTH_32BIT                 
                                                  | PDMA_SRC_DIR_INC 
                                                  | PDMA_DST_DIR_INC);
    //
    // Trig DMA Transfer
    //
        PDMAChannelTransferSet(ulDMAChannelID[i], ulSrcTemp, ulDestTemp ,1504);
    
    //
    // Check Transfer is over or not
    //
        while(PDMARemainTransferCountGet(ulDMAChannelID[i]));
    
        for(i = 0;i < 64;i++)
        {
            TestAssert((ulSrcTemp[i] == ulDestTemp[i]), "dma API error!");
        }
    }

    TestAssertQBreak("abcdefghi", "Transfer Over Interrupy fialed!", 5000000);
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