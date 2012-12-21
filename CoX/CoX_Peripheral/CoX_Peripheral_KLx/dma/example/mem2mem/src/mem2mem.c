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
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_uart.h"
#include "xuart.h"
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

unsigned long ulAssignChannel;

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
xtEventCallback DmaCallbackFunc[1] = {DmaChannel0Callback};
 

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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMAMUX);
    
    xIntEnable(INT_DMA0);
    
    DMAChannelDeAssign(DMA_CHANNEL_0);
	DMAChannelDeAssign(DMA_CHANNEL_1);
	DMAChannelDeAssign(DMA_CHANNEL_2);
	DMAChannelDeAssign(DMA_CHANNEL_3);
     
    ulAssignChannel = DMAChannelDynamicAssign(DMA_REQUEST_MEM, DMA_REQUEST_MEM);
	DMAEnable(ulAssignChannel);

    DMAChannelIntEnable(ulAssignChannel, DMA_EVENT_TC);
    DMAChannelIntCallbackInit(ulAssignChannel, DmaCallbackFunc[0]);
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
void DmaMem2Mem(void)
{
    unsigned long uli;
    
    //
    // Configure System clock
    //
    xSysCtlClockSet(48000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    SysCtlDelay(1000000);
    
    DMAInit();
    
    //
    // Set Channel control  parameter
    //
    DMAChannelControlSet(ulAssignChannel, DMA_DST_SIZE_32 |
                                          DMA_SRC_SIZE_32 |
                                          DMA_SRC_DIR_INC |
                                          DMA_DST_DIR_INC);
    //
    // Trig DMA Transfer
    //
    DMAChannelTransferSet(ulAssignChannel, ulSrcTemp, ulDestTemp ,64*4);
          
    DMAChannelRequest(ulAssignChannel);
		
    //
    // Check Transfer is over or not
    //
    uli = 1000;
    while(uli--);   
}
