//*****************************************************************************
//
//! \file mem2men.c
//! \brief example of memory to memory for the DMA
//! \version V2.1.1.1
//! \date 5/24/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox 
//! All rights reserved.
//! 
//! Redistribution and use in source and binary forms, with or without 
//! modification, are permitted provided that the following conditions 
//! are met: 
//! 
//!     * Redistributions of source code must retain the above copyright 
//! notice, this list of conditions and the following disclaimer. 
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution. 
//!     * Neither the name of the <ORGANIZATION> nor the names of its 
//! contributors may be used to endorse or promote products derived 
//! from this software without specific prior written permission. 
//! 
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

#include <stdint.h>
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_uart.h"
#include "xuart.h"
#include "xi2c.h"
#include "xhw_dma.h"
#include "xdma.h"

unsigned long ulSrcTemp[64] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
                                0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
                                0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
                                0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
                                0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
                                0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
                                0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
                                0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80};

unsigned long ulDestTemp[64];

//
// Install callback function
//
unsigned long DmaChannel0Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     return 0;
}
//
// Callback function
//
xtEventCallback DmaCallbackFunc[1] = {DmaChannel0Callback,
                                    };


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
    //
    // Enable Peripheral DMA
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_DMA1);
    SysCtlPeripheralReset(SYSCTL_PERIPH_DMA2);
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA2);
    
    xIntEnable(xINT_DMA1);
    xIntEnable(xINT_DMA2);
    
    DMAChannelDeAssign(DMA1_CHANNEL_1);
    DMADisable(DMA1_CHANNEL_1); 
    DMAChannelDynamicAssign(DMA_REQUEST_MEM, DMA_REQUEST_MEM);

    DMAChannelIntEnable(DMA1_CHANNEL_1, DMA_EVENT_TC);
    DMAChannelIntCallbackInit(DMA1_CHANNEL_1, DmaCallbackFunc[0]);
}

//*****************************************************************************
//
//! \brief DMA memory to memory Trig transfer
//!
//! \param None
//!
//! \details This function is to memory to memory Trig transfer.
//!
//! \return None
//
//*****************************************************************************
static void DmaMem2Mem(void)
{
    DMAInit();
    
    //
    // Set Channel control  parameter
    //
    DMAChannelControlSet(DMA1_CHANNEL_1, DMA_MEM_WIDTH_32BIT |
                                                DMA_PER_WIDTH_32BIT |
                                                DMA_MEM_DIR_INC |
                                                DMA_PER_DIR_INC);
    //
    // Trig DMA Transfer
    //
    DMAChannelTransferSet(DMA1_CHANNEL_1, ulSrcTemp, ulDestTemp ,64);
        
    DMAEnable(DMA1_CHANNEL_1);    
    
    //
    // Check Transfer is over or not
    //
    while(DMARemainTransferCountGet(DMA1_CHANNEL_1));
    
}

int main(void)
{
    //
    // Do the main test
    //
    DmaMem2Mem();

    while(1);
}