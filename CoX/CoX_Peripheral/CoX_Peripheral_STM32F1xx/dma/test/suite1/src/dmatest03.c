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

#define DMA_CHANNEL             7

unsigned long ulSrcTemp[64] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
                                0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
                                0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
                                0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
                                0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
                                0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
                                0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
                                0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80};

unsigned long ulDestTemp[64];

unsigned long ulAssignChannel[12];

unsigned long ulDMAChannelID[] = 
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
    DMA2_CHANNEL_5
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

unsigned long DmaChannel9Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('j');
     return 0;
}

unsigned long DmaChannel10Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('k');
     return 0;
}

unsigned long DmaChannel11Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('l');
     return 0;
}
//
// Callback function
//
xtEventCallback DmaCallbackFunc[12] = {DmaChannel0Callback,
                                      DmaChannel1Callback,
                                      DmaChannel2Callback,
                                      DmaChannel3Callback,
                                      DmaChannel4Callback,
                                      DmaChannel5Callback,
                                      DmaChannel6Callback,
                                      DmaChannel7Callback,
                                      DmaChannel8Callback,
                                      DmaChannel9Callback,
                                      DmaChannel10Callback,
                                      DmaChannel11Callback,};
//*****************************************************************************
//
//! \brief Get the Test description of xdma004 register test.
//!
//! \return the desccription of the xdma004 test.
//
//*****************************************************************************
static char* xDma003GetTest(void)
{
    return "xdma, 003, xdma memory to memory and intrrupt test";
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
    SysCtlPeripheralReset(SYSCTL_PERIPH_DMA1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA2);
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
    SysCtlPeripheralDisable(SYSCTL_PERIPH_DMA1);  
    SysCtlPeripheralDisable(SYSCTL_PERIPH_DMA2);  
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
    //
    // Enable Peripheral DMA
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_DMA1);
    SysCtlPeripheralReset(SYSCTL_PERIPH_DMA2);
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA2);
    
    xIntEnable(xINT_DMA1);
    xIntEnable(xINT_DMA2);
    
    for(i = 0; i < DMA_CHANNEL; i++)
    {
        DMAChannelDeAssign(ulDMAChannelID[i]);
        DMADisable(ulDMAChannelID[i]);
    }
    
    for(i = 0; i < DMA_CHANNEL; i++)
    { 
       ulAssignChannel[i] = DMAChannelDynamicAssign(DMA_REQUEST_MEM, 
                                                    DMA_REQUEST_MEM);
    }
    
    for(i = 0; i < DMA_CHANNEL; i++)
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
    unsigned long i,j;
    
    DMAInit();
    
    for(i = 0; i < DMA_CHANNEL; i++)
    {
        //
        // Set Channel control  parameter
        //
        DMAChannelControlSet(ulDMAChannelID[i], DMA_MEM_WIDTH_32BIT |
                                                    DMA_PER_WIDTH_32BIT |
                                                    DMA_MEM_DIR_INC |
                                                    DMA_PER_DIR_INC);
        //
        // Trig DMA Transfer
        //
        DMAChannelTransferSet(ulDMAChannelID[i], ulSrcTemp, ulDestTemp ,64);
            
        DMAEnable(ulDMAChannelID[i]);    
        
        //
        // Check Transfer is over or not
        //
        while(DMARemainTransferCountGet(ulDMAChannelID[i]));
        
        
        for(j = 0;j < 64;j++)
        {
            TestAssert((ulSrcTemp[i] == ulDestTemp[i]), "dma API error!");
        }
    }

    TestAssertQBreak("abcdefg", "Transfer Over Interrupy fialed!", 5000000);
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