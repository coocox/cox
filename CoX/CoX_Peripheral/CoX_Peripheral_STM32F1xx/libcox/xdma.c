//*****************************************************************************
//
//! \file xdma.c
//! \brief Driver for the DMA Controller.
//! \version V2.2.1.0
//! \date 06/24/2012
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

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_config.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_dma.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xdma.h"

typedef struct
{
    //
    // Channel ID.
    //
    unsigned long ulChannelID;

    //
    //
    //
    xtEventCallback pfnDMAChannelHandlerCallback;

    //
    // Channel Assignment status
    //
    xtBoolean bChannelAssigned;

}
tDMAChannelAsssign;

//
// DMA Service channel base address.
//
static unsigned long g_psDMAChannel[] =
{
    0x40020008,   //DMA 1 Ch 1
    0x4002001C,   //DMA 1 Ch 2
    0x40020030,   //DMA 1 Ch 3
    0x40020044,   //DMA 1 Ch 4
    0x40020058,   //DMA 1 Ch 5
    0x4002006C,   //DMA 1 Ch 6
    0x40020080,   //DMA 1 Ch 7
    0x40020408,   //DMA 2 Ch 1
    0x4002041C,   //DMA 2 Ch 2
    0x40020430,   //DMA 2 Ch 3
    0x40020444,   //DMA 2 Ch 4
    0x40020458    //DMA 2 Ch 5
};

#define DMA_BASE(a)    g_psDMABaseReg[(((a) >> 28) & 0x3)]
#define DMA_CHANNEL(a) ((a) & 0xF)
#define DMA_ADDR(a)    g_psDMAChannel[DMA_CHANNEL(a)]

//*****************************************************************************
//
// An array is DMA Callback function point
//
//*****************************************************************************
// static xtEventCallback g_pfnDMAGHandlerCallbacks[9]={0};

//
// DMA Channels Assignment table.
//
static tDMAChannelAsssign g_psDMAChannelAssignTable[] =
{
    { xDMA_CHANNEL_0,   0,      xfalse },
    { xDMA_CHANNEL_1,   0,      xfalse },
    { xDMA_CHANNEL_2,   0,      xfalse },
    { xDMA_CHANNEL_3,   0,      xfalse },
    { xDMA_CHANNEL_4,   0,      xfalse },
    { xDMA_CHANNEL_5,   0,      xfalse },
    { xDMA_CHANNEL_6,   0,      xfalse },
    { xDMA_CHANNEL_7,   0,      xfalse },
    { xDMA_CHANNEL_8,   0,      xfalse },
    { xDMA_CHANNEL_9,   0,      xfalse },
    { xDMA_CHANNEL_10,  0,      xfalse },
    { xDMA_CHANNEL_11,  0,      xfalse },

    //
    // End.
    //
    { xDMA_CHANNEL_NOT_EXIST,   xfalse },

};

//*****************************************************************************
//
//! \internal
//! Checks a DMA channel ID.
//!
//! \param ulChannelID is the DMA channel ID.
//!
//! This function determines if a DMA channel ID is valid.
//!
//! \return Returns \b xtrue if the ID is valid and \b xfalse
//! otherwise.
//
//*****************************************************************************
#ifdef xDEBUG
static xtBoolean
xDMAChannelIDValid(unsigned long ulChannelID)
{
    return(((ulChannelID >= 0) && (ulChannelID <= 11)));
}
#endif


//*****************************************************************************
//
//! DMA channel 1 Interrupt Handler.
//!
//! The interrupt handler for DMA interrupts from the channel 1.
//!
//! \return None.
//
//*****************************************************************************
void
DMA1Channel1IntHandler(void)
{
    unsigned long ulChannelID = 0;
    unsigned long ulStatus;
    ulStatus = xHWREG(DMA1_BASE + DMA_ISR);
    xHWREG(DMA1_BASE + DMA_IFCR) = (ulStatus & (0xF << ulChannelID*4));
    if(g_psDMAChannelAssignTable[ulChannelID].bChannelAssigned == xtrue)
    {
        if(ulStatus & DMA_ISR_TCIF1)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_TC,0);
           }
        }
        else if(ulStatus & DMA_ISR_TEIF1)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_ERROR,0);
           }
        }
        else if(ulStatus & DMA_ISR_HTIF1)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_HT,0);
           }
        }
    }
}

//*****************************************************************************
//
//! DMA channel 3 Interrupt Handler.
//!
//! The interrupt handler for DMA interrupts from the channel 3.
//!
//! \return None.
//
//*****************************************************************************
void
DMA1Channel3IntHandler(void)
{
    unsigned long ulChannelID = 2;
    unsigned long ulStatus;
    ulStatus = xHWREG(DMA1_BASE + DMA_ISR);
    xHWREG(DMA1_BASE + DMA_IFCR) = (ulStatus & (0xF << ulChannelID*4));
    if(g_psDMAChannelAssignTable[ulChannelID].bChannelAssigned == xtrue)
    {
        if(ulStatus & DMA_ISR_TCIF3)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_TC,0);
           }
        }
        else if(ulStatus & DMA_ISR_TEIF3)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_ERROR,0);
           }
        }
        else if(ulStatus & DMA_ISR_HTIF3)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_HT,0);
           }
        }
    }
}

//*****************************************************************************
//
//! DMA channel 2 Interrupt Handler.
//!
//! The interrupt handler for DMA interrupts from the channel 2.
//!
//! \return None.
//
//*****************************************************************************
void
DMA1Channel2IntHandler(void)
{
    unsigned long ulChannelID = 1;
    unsigned long ulStatus;
    ulStatus = xHWREG(DMA1_BASE + DMA_ISR);
    xHWREG(DMA1_BASE + DMA_IFCR) = (ulStatus & 0xF0);
    if(g_psDMAChannelAssignTable[ulChannelID].bChannelAssigned == xtrue)
    {
        if(ulStatus & DMA_ISR_TCIF2)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_TC,0);
           }
        }
        else if(ulStatus & DMA_ISR_TEIF2)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_ERROR,0);
           }
        }
        else if(ulStatus & DMA_ISR_HTIF2)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_HT,0);
           }
        }
    }
}

//*****************************************************************************
//
//! DMA channel 4 Interrupt Handler.
//!
//! The interrupt handler for DMA interrupts from the channel 4.
//!
//! \return None.
//
//*****************************************************************************
void
DMA1Channel4IntHandler(void)
{
    unsigned long ulChannelID = 3;
    unsigned long ulStatus;
    ulStatus = xHWREG(DMA1_BASE + DMA_ISR);
    xHWREG(DMA1_BASE + DMA_IFCR) = (ulStatus & (0xF << ulChannelID*4));
    if(g_psDMAChannelAssignTable[ulChannelID].bChannelAssigned == xtrue)
    {
        if(ulStatus & DMA_ISR_TCIF4)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_TC,0);
           }
        }
        else if(ulStatus & DMA_ISR_TEIF4)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_ERROR,0);
           }
        }
        else if(ulStatus & DMA_ISR_HTIF4)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_HT,0);
           }
        }
    }
}

//*****************************************************************************
//
//! DMA1 channel 5 Interrupt Handler.
//!
//! The interrupt handler for DMA1 interrupts from the channel 5.
//!
//! \return None.
//
//*****************************************************************************
void
DMA1Channel5IntHandler(void)
{
    unsigned long ulChannelID = 4;
    unsigned long ulStatus;
    ulStatus = xHWREG(DMA1_BASE + DMA_ISR);
    xHWREG(DMA1_BASE + DMA_IFCR) = (ulStatus & (0xF << ulChannelID*4));
    if(g_psDMAChannelAssignTable[ulChannelID].bChannelAssigned == xtrue)
    {
        if(ulStatus & DMA_ISR_TCIF5)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_TC,0);
           }
        }
        else if(ulStatus & DMA_ISR_TEIF5)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_ERROR,0);
           }
        }
        else if(ulStatus & DMA_ISR_HTIF5)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_HT,0);
           }
        }
    }
}

//*****************************************************************************
//
//! DMA1 channel 6 Interrupt Handler.
//!
//! The interrupt handler for DMA1 interrupts from the channel 6.
//!
//! \return None.
//
//*****************************************************************************
void
DMA1Channel6IntHandler(void)
{
    unsigned long ulChannelID = 5;
    unsigned long ulStatus;
    ulStatus = xHWREG(DMA1_BASE + DMA_ISR);
    xHWREG(DMA1_BASE + DMA_IFCR) = (ulStatus & (0xF << ulChannelID*4));
    if(g_psDMAChannelAssignTable[ulChannelID].bChannelAssigned == xtrue)
    {
        if(ulStatus & DMA_ISR_TCIF6)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_TC,0);
           }
        }
        else if(ulStatus & DMA_ISR_TEIF6)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_ERROR,0);
           }
        }
        else if(ulStatus & DMA_ISR_HTIF6)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_HT,0);
           }
        }
    }
}

//*****************************************************************************
//
//! DMA1 channel 7 Interrupt Handler.
//!
//! The interrupt handler for DMA1 interrupts from the channel 7.
//!
//! \return None.
//
//*****************************************************************************
void
DMA1Channel7IntHandler(void)
{
    unsigned long ulChannelID = 6;
    unsigned long ulStatus;
    ulStatus = xHWREG(DMA1_BASE + DMA_ISR);
    xHWREG(DMA1_BASE + DMA_IFCR) = (ulStatus & (0xF << ulChannelID*4));
    if(g_psDMAChannelAssignTable[ulChannelID].bChannelAssigned == xtrue)
    {
        if(ulStatus & DMA_ISR_TCIF7)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_TC,0);
           }
        }
        else if(ulStatus & DMA_ISR_TEIF7)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_ERROR,0);
           }
        }
        else if(ulStatus & DMA_ISR_HTIF7)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_HT,0);
           }
        }
    }
}

//*****************************************************************************
//
//! DMA2 channel 1 Interrupt Handler.
//!
//! The interrupt handler for DMA2 interrupts from the channel 1.
//!
//! \return None.
//
//*****************************************************************************
void
DMA2Channel1IntHandler(void)
{
    unsigned long ulChannelID = 0;
    unsigned long ulStatus;
    ulStatus = xHWREG(DMA2_BASE + DMA_ISR);
    xHWREG(DMA2_BASE + DMA_IFCR) = (ulStatus & (0xF << ulChannelID*4));
    if(g_psDMAChannelAssignTable[ulChannelID].bChannelAssigned == xtrue)
    {
        if(ulStatus & DMA_ISR_TCIF1)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_TC,0);
           }
        }
        else if(ulStatus & DMA_ISR_TEIF1)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_ERROR,0);
           }
        }
        else if(ulStatus & DMA_ISR_HTIF1)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_HT,0);
           }
        }
    }
}

//*****************************************************************************
//
//! DMA2 channel 2 Interrupt Handler.
//!
//! The interrupt handler for DMA2 interrupts from the channel 2.
//!
//! \return None.
//
//*****************************************************************************
void
DMA2Channel2IntHandler(void)
{
    unsigned long ulChannelID = 1;
    unsigned long ulStatus;
    ulStatus = xHWREG(DMA2_BASE + DMA_ISR);
    xHWREG(DMA2_BASE + DMA_IFCR) = (ulStatus & (0xF << ulChannelID*4));
    if(g_psDMAChannelAssignTable[ulChannelID].bChannelAssigned == xtrue)
    {
        if(ulStatus & DMA_ISR_TCIF2)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_TC,0);
           }
        }
        else if(ulStatus & DMA_ISR_TEIF2)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_ERROR,0);
           }
        }
        else if(ulStatus & DMA_ISR_HTIF2)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_HT,0);
           }
        }
    }
}

//*****************************************************************************
//
//! DMA2 channel 3 Interrupt Handler.
//!
//! The interrupt handler for DMA2 interrupts from the channel 3.
//!
//! \return None.
//
//*****************************************************************************
void
DMA2Channel3IntHandler(void)
{
    unsigned long ulChannelID = 2;
    unsigned long ulStatus;
    ulStatus = xHWREG(DMA2_BASE + DMA_ISR);
    xHWREG(DMA2_BASE + DMA_IFCR) = (ulStatus & (0xF << ulChannelID*4));
    if(g_psDMAChannelAssignTable[ulChannelID].bChannelAssigned == xtrue)
    {
        if(ulStatus & DMA_ISR_TCIF3)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_TC,0);
           }
        }
        else if(ulStatus & DMA_ISR_TEIF3)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_ERROR,0);
           }
        }
        else if(ulStatus & DMA_ISR_HTIF3)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_HT,0);
           }
        }
    }
}

//*****************************************************************************
//
//! DMA2 channel 4 Interrupt Handler.
//!
//! The interrupt handler for DMA2 interrupts from the channel 4.
//!
//! \return None.
//
//*****************************************************************************
void
DMA2Channel4IntHandler(void)
{
    unsigned long ulChannelID = 3;
    unsigned long ulStatus;
    ulStatus = xHWREG(DMA2_BASE + DMA_ISR);
    xHWREG(DMA2_BASE + DMA_IFCR) = (ulStatus & (0xF << ulChannelID*4));
    if(g_psDMAChannelAssignTable[ulChannelID].bChannelAssigned == xtrue)
    {
        if(ulStatus & DMA_ISR_TCIF4)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_TC,0);
           }
        }
        else if(ulStatus & DMA_ISR_TEIF4)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_ERROR,0);
           }
        }
        else if(ulStatus & DMA_ISR_HTIF4)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_HT,0);
           }
        }
    }
}

//*****************************************************************************
//
//! DMA2 channel 5 Interrupt Handler.
//!
//! The interrupt handler for DMA2 interrupts from the channel 5.
//!
//! \return None.
//
//*****************************************************************************
void
DMA2Channel5IntHandler(void)
{
    unsigned long ulChannelID = 4;
    unsigned long ulStatus;
    ulStatus = xHWREG(DMA2_BASE + DMA_ISR);
    xHWREG(DMA2_BASE + DMA_IFCR) = (ulStatus & (0xF << ulChannelID*4));
    if(g_psDMAChannelAssignTable[ulChannelID].bChannelAssigned == xtrue)
    {
        if(ulStatus & DMA_ISR_TCIF5)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_TC,0);
           }
        }
        else if(ulStatus & DMA_ISR_TEIF5)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_ERROR,0);
           }
        }
        else if(ulStatus & DMA_ISR_HTIF5)
        {
           if (g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback != 0)
           {
                g_psDMAChannelAssignTable[ulChannelID].pfnDMAChannelHandlerCallback(0,0,DMA_EVENT_HT,0);
           }
        }
    }
}

//*****************************************************************************
//
//! \brief Enable Special DMA Channel.
//!
//! \param ulChannelID is the channel ID that have been enabled.
//! The channel ID can be one of the following value:
//!
//! - DMA1_CHANNEL_1
//! - DMA1_CHANNEL_2
//! - DMA1_CHANNEL_3
//! - DMA1_CHANNEL_4
//! - DMA1_CHANNEL_5
//! - DMA1_CHANNEL_6
//! - DMA1_CHANNEL_7
//! - DMA2_CHANNEL_1
//! - DMA2_CHANNEL_2
//! - DMA2_CHANNEL_3
//! - DMA2_CHANNEL_4
//! - DMA2_CHANNEL_5
//! .
//!
//! \return None.
//
//*****************************************************************************
void
DMAEnable(unsigned long ulChannelID)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));

    //
    // Enable DMA channel.
    //
    xHWREG(g_psDMAChannel[ulChannelID]) |= DMA_CCR1_EN;
}

//*****************************************************************************
//
//! \brief Disable Special DMA Channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! The channel ID can be one of the following value:
//!
//! - DMA1_CHANNEL_1
//! - DMA1_CHANNEL_2
//! - DMA1_CHANNEL_3
//! - DMA1_CHANNEL_4
//! - DMA1_CHANNEL_5
//! - DMA1_CHANNEL_6
//! - DMA1_CHANNEL_7
//! - DMA2_CHANNEL_1
//! - DMA2_CHANNEL_2
//! - DMA2_CHANNEL_3
//! - DMA2_CHANNEL_4
//! - DMA2_CHANNEL_5
//! .
//!
//! \return None.
//
//*****************************************************************************
void
DMADisable(unsigned long ulChannelID)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));

    //
    // Disable DMA channel.
    //
    xHWREG(g_psDMAChannel[ulChannelID]) &= ~DMA_CCR1_EN;
}

//*****************************************************************************
//
//! \brief Enable the DMA interrupt of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! \param ulIntFlags is the interrupt type of DMA.
//! The channel ID can be one of the following value:
//!
//! - DMA1_CHANNEL_1
//! - DMA1_CHANNEL_2
//! - DMA1_CHANNEL_1
//! - DMA1_CHANNEL_2
//! - DMA1_CHANNEL_3
//! - DMA1_CHANNEL_4
//! - DMA1_CHANNEL_5
//! - DMA1_CHANNEL_6
//! - DMA1_CHANNEL_7
//! - DMA2_CHANNEL_1
//! - DMA2_CHANNEL_2
//! - DMA2_CHANNEL_3
//! - DMA2_CHANNEL_4
//! - DMA2_CHANNEL_5
//! .
//! The interrupt type can be OR of the following value:
//! - DMA_INT_TG
//! - DMA_INT_TC
//! - DMA_INT_HT
//! - DMA_INT_ERROR
//! .
//!
//! \return None.
//
//*****************************************************************************
void
DMAChannelIntEnable(unsigned long ulChannelID, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));
    xASSERT(((ulIntFlags & DMA_INT_TG) == DMA_INT_TG) ||
            ((ulIntFlags & DMA_INT_TC) == DMA_INT_TC) ||
            ((ulIntFlags & DMA_INT_HT) == DMA_INT_HT) ||
            ((ulIntFlags & DMA_INT_ERROR) == DMA_INT_ERROR));

    //
    // Enable DMA channel interrupt.
    //
    xHWREG(g_psDMAChannel[ulChannelID]) |= ulIntFlags;
}

//*****************************************************************************
//
//! \brief Disable the DMA interrupt of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! \param ulIntFlags is the interrupt type of DMA.
//! The channel ID can be one of the following value:
//!
//! - DMA1_CHANNEL_1
//! - DMA1_CHANNEL_2
//! - DMA1_CHANNEL_1
//! - DMA1_CHANNEL_2
//! - DMA1_CHANNEL_3
//! - DMA1_CHANNEL_4
//! - DMA1_CHANNEL_5
//! - DMA1_CHANNEL_6
//! - DMA1_CHANNEL_7
//! - DMA2_CHANNEL_1
//! - DMA2_CHANNEL_2
//! - DMA2_CHANNEL_3
//! - DMA2_CHANNEL_4
//! - DMA2_CHANNEL_5
//! .
//! The interrupt type can be OR of the following value:
//! - DMA_INT_TG
//! - DMA_INT_TC
//! - DMA_INT_HT
//! - DMA_INT_ERROR
//! .
//!
//! \return None.
//
//*****************************************************************************
void
DMAChannelIntDisable(unsigned long ulChannelID, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));
    xASSERT(((ulIntFlags & DMA_INT_TG) == DMA_INT_TG) ||
            ((ulIntFlags & DMA_INT_TC) == DMA_INT_TC) ||
            ((ulIntFlags & DMA_INT_HT) == DMA_INT_HT) ||
            ((ulIntFlags & DMA_INT_ERROR) == DMA_INT_ERROR));

    //
    // Disable DMA channel interrupt.
    //
    xHWREG(g_psDMAChannel[ulChannelID]) &= ~ulIntFlags;
}

//*****************************************************************************
//
//! \brief Dynamic assign a channel through the request.
//!
//! \param ulDMASrcRequest is the source DMA request signal. for more info
//! refrence \ref STM32F1xx_DMA_Request_Connections.
//! \param ulDMADestRequest is the destination DMA request signal.
//! for more info refrence \ref STM32F1xx_DMA_Request_Connections.

//! This function dynamic allocate a channel according the DMA requests.
//! The \ref ulDMASrcRequest and \ref ulDMADestRequest can be:
//! - \ref DMA_REQUEST_ADC1_RX
//! - \ref DMA_REQUEST_TIM2_CH3
//! - \ref DMA_REQUEST_TIM4_CH1
//! - \ref DMA_REQUEST_UART3_TX
//! - \ref DMA_REQUEST_TIM1_CH1
//! - \ref DMA_REQUEST_TIM2_UP
//! - \ref DMA_REQUEST_TIM3_CH3
//! - \ref DMA_REQUEST_SPI1_RX
//! - \ref DMA_REQUEST_UART3_RX
//! - \ref DMA_REQUEST_TIM1_CH2
//! - \ref DMA_REQUEST_TIM3_CH4
//! - \ref DMA_REQUEST_TIM3_UP
//! - others refrence \ref STM32F1xx_DMA_Request_Connections
//! .
//!
//! \note ulDMASrcRequest can only be XX_RX and TIMx_CHx
//! ulDMADestRequest can only be XX_TX,TIMx_TRIG,TIMx_COM and TIMx_UP.
//!
//! \return Returns a Channel ID that dynamic assignment.
//! The channel ID can be:
//! - DMA1_CHANNEL_1
//! - DMA1_CHANNEL_2
//! - others refrence \ref STM32F1xx_DMA_Channel_IDs
//! .
//
//*****************************************************************************
unsigned long
DMAChannelDynamicAssign(unsigned long ulDMASrcRequest, unsigned long ulDMADestRequest)
{
    unsigned long ulChannelID = 0;
    //
    // Check the arguments.
    //
    xASSERT(
           (ulDMASrcRequest == DMA_REQUEST_ADC1_RX)   ||
           (ulDMASrcRequest == DMA_REQUEST_TIM2_CH3)  ||
           (ulDMASrcRequest == DMA_REQUEST_TIM4_CH1)  ||
           (ulDMASrcRequest == DMA_REQUEST_MEM)       ||
           (ulDMASrcRequest == DMA_REQUEST_TIM1_CH1)  ||
           (ulDMASrcRequest == DMA_REQUEST_TIM3_CH3)  ||
           (ulDMASrcRequest == DMA_REQUEST_SPI1_RX)   ||
           (ulDMASrcRequest == DMA_REQUEST_TIM3_CH4)  ||
           (ulDMASrcRequest == DMA_REQUEST_TIM1_CH4)  ||
           (ulDMASrcRequest == DMA_REQUEST_TIM4_CH2)  ||
           (ulDMASrcRequest == DMA_REQUEST_SPI2_RX)   ||
           (ulDMASrcRequest == DMA_REQUEST_I2S2_RX)   ||
           (ulDMASrcRequest == DMA_REQUEST_TIM2_CH1)  ||
           (ulDMASrcRequest == DMA_REQUEST_TIM4_CH3)  ||
           (ulDMASrcRequest == DMA_REQUEST_I2C2_RX)   ||
           (ulDMASrcRequest == DMA_REQUEST_TIM1_CH3)  ||
           (ulDMASrcRequest == DMA_REQUEST_TIM3_CH1)  ||
           (ulDMASrcRequest == DMA_REQUEST_TIM2_CH2)  ||
           (ulDMASrcRequest == DMA_REQUEST_TIM2_CH4)  ||
           (ulDMASrcRequest == DMA_REQUEST_I2C1_RX)   ||
           (ulDMASrcRequest == DMA_REQUEST_TIM5_CH4)  ||
           (ulDMASrcRequest == DMA_REQUEST_TIM8_CH3)  ||
           (ulDMASrcRequest == DMA_REQUEST_SPI3_RX)   ||
           (ulDMASrcRequest == DMA_REQUEST_I2S3_RX)   ||
           (ulDMASrcRequest == DMA_REQUEST_TIM8_CH4)  ||
           (ulDMASrcRequest == DMA_REQUEST_TIM5_CH3)  ||
           (ulDMASrcRequest == DMA_REQUEST_TIM8_CH1)  ||
           (ulDMASrcRequest == DMA_REQUEST_TIM5_CH2)  ||
           (ulDMASrcRequest == DMA_REQUEST_SDIO_RX)   ||
           (ulDMASrcRequest == DMA_REQUEST_ADC3_RX)   ||
           (ulDMASrcRequest == DMA_REQUEST_TIM8_CH2)  ||
           (ulDMASrcRequest == DMA_REQUEST_TIM5_CH1)  ||
           (ulDMASrcRequest == DMA_REQUEST_TIM1_CH2)  );

    xASSERT((ulDMADestRequest == DMA_REQUEST_UART3_TX) ||
           (ulDMADestRequest == DMA_REQUEST_TIM1_UP)   ||
           (ulDMADestRequest == DMA_REQUEST_MEM)       ||
           (ulDMADestRequest == DMA_REQUEST_TIM3_UP)   ||
           (ulDMADestRequest == DMA_REQUEST_SPI1_TX)   ||
           (ulDMADestRequest == DMA_REQUEST_UART1_TX)  ||
           (ulDMADestRequest == DMA_REQUEST_TIM1_TRIG) ||
           (ulDMADestRequest == DMA_REQUEST_TIM1_COM)  ||
           (ulDMADestRequest == DMA_REQUEST_I2C2_TX)   ||
           (ulDMADestRequest == DMA_REQUEST_TIM1_UP)   ||
           (ulDMADestRequest == DMA_REQUEST_SPI2_TX)   ||
           (ulDMADestRequest == DMA_REQUEST_I2S2_TX)   ||
           (ulDMADestRequest == DMA_REQUEST_TIM3_TRIG) ||
           (ulDMADestRequest == DMA_REQUEST_I2C1_TX)   ||
           (ulDMADestRequest == DMA_REQUEST_UART2_TX)  ||
           (ulDMADestRequest == DMA_REQUEST_TIM4_UP)   ||
           (ulDMADestRequest == DMA_REQUEST_TIM5_TRIG) ||
           (ulDMADestRequest == DMA_REQUEST_TIM8_UP)   ||
           (ulDMADestRequest == DMA_REQUEST_TIM8_TRIG) ||
           (ulDMADestRequest == DMA_REQUEST_TIM8_COM)  ||
           (ulDMADestRequest == DMA_REQUEST_TIM5_UP)   ||
           (ulDMADestRequest == DMA_REQUEST_SPI3_TX)   ||
           (ulDMADestRequest == DMA_REQUEST_I2S3_TX)   ||
           (ulDMADestRequest == DMA_REQUEST_TIM6_UP)   ||
           (ulDMADestRequest == DMA_REQUEST_DAC_CH1)   ||
           (ulDMADestRequest == DMA_REQUEST_SDIO_TX)   ||
           (ulDMADestRequest == DMA_REQUEST_TIM7_UP)   ||
           (ulDMADestRequest == DMA_REQUEST_DAC_CH2)   ||
           (ulDMADestRequest == DMA_REQUEST_UART4_TX)  );

    //
    // STM32F1xx DMA support P to P
    //
    if((ulDMASrcRequest != DMA_REQUEST_MEM) && (ulDMADestRequest != DMA_REQUEST_MEM))
    {
        //1
        if(g_psDMAChannelAssignTable[DMA_CHANNEL(ulDMASrcRequest)].bChannelAssigned == xfalse)
        {
            g_psDMAChannelAssignTable[DMA_CHANNEL(ulDMASrcRequest)].bChannelAssigned = xtrue;
            xHWREG(DMA_ADDR(ulDMASrcRequest)) &= ~(DMA_CCR1_DIR | DMA_CCR1_MEM2MEM);
            xHWREG(DMA_ADDR(ulDMASrcRequest)) |= DMA_CCR1_DIR;
            return g_psDMAChannelAssignTable[DMA_CHANNEL(ulDMASrcRequest)].ulChannelID;
        }
        else
        {
            return xDMA_CHANNEL_NOT_EXIST;
        }
    }

    if((ulDMASrcRequest == DMA_REQUEST_MEM) && (ulDMADestRequest & 0x00000100))
    {
        if(g_psDMAChannelAssignTable[DMA_CHANNEL(ulDMADestRequest)].bChannelAssigned == xfalse)
        {
            g_psDMAChannelAssignTable[DMA_CHANNEL(ulDMADestRequest)].bChannelAssigned = xtrue;
            xHWREG(DMA_ADDR(ulDMADestRequest)) &= ~(DMA_CCR1_DIR | DMA_CCR1_MEM2MEM);
            xHWREG(DMA_ADDR(ulDMADestRequest)) |= DMA_CCR1_DIR;
            return g_psDMAChannelAssignTable[DMA_CHANNEL(ulDMADestRequest)].ulChannelID;
        }
        else
        {
            return xDMA_CHANNEL_NOT_EXIST;
        }
    }

    if((ulDMADestRequest == DMA_REQUEST_MEM) && (ulDMASrcRequest != DMA_REQUEST_MEM) &&
       !(ulDMASrcRequest & 0x00000100))
    {
        if(g_psDMAChannelAssignTable[DMA_CHANNEL(ulDMASrcRequest)].bChannelAssigned == xfalse)
        {
            g_psDMAChannelAssignTable[DMA_CHANNEL(ulDMASrcRequest)].bChannelAssigned = xtrue;
            xHWREG(DMA_ADDR(ulDMASrcRequest)) &= ~(DMA_CCR1_DIR | DMA_CCR1_MEM2MEM);

            return g_psDMAChannelAssignTable[DMA_CHANNEL(ulDMASrcRequest)].ulChannelID;
        }
        else
        {
            return xDMA_CHANNEL_NOT_EXIST;
        }
    }

    //
    // Mem to Mem type
    //
    if((ulDMASrcRequest & DMA_REQUEST_MEM) && (ulDMADestRequest & DMA_REQUEST_MEM))
    {
        for(ulChannelID = 0;
            g_psDMAChannelAssignTable[ulChannelID].ulChannelID != xDMA_CHANNEL_NOT_EXIST;
            ulChannelID++)
        {
            if(g_psDMAChannelAssignTable[ulChannelID].bChannelAssigned == xfalse)
            {
                g_psDMAChannelAssignTable[ulChannelID].bChannelAssigned = xtrue;
                break;
            }
        }
        xHWREG(g_psDMAChannel[ulChannelID]) &= ~(DMA_CCR1_DIR | DMA_CCR1_MEM2MEM);
        xHWREG(g_psDMAChannel[ulChannelID]) |= (DMA_CCR1_MEM2MEM);
        return g_psDMAChannelAssignTable[ulChannelID].ulChannelID;
    }

    //
    // when the src request is tx type, or dest request is rx type, assign false.
    //
    return xDMA_CHANNEL_NOT_EXIST;
}

//*****************************************************************************
//
//! \brief Free the assignment of  a channel.
//!
//! \param ulChannelID is the channel ID that have been assigned.
//! The channel ID can be:
//! - DMA1_CHANNEL_1
//! - DMA1_CHANNEL_2
//! - others refrence \ref STM32F1xx_DMA_Channel_IDs
//! .
//!
//! \return None.
//
//*****************************************************************************
void
DMAChannelDeAssign(unsigned long ulChannelID)
{
    int i = 0;

    xASSERT(xDMAChannelIDValid(ulChannelID));

    for(i = 0; g_psDMAChannelAssignTable[i].ulChannelID != xDMA_CHANNEL_NOT_EXIST; i++)
    {
        if(g_psDMAChannelAssignTable[i].ulChannelID == ulChannelID)
        {
            g_psDMAChannelAssignTable[i].bChannelAssigned = xfalse;
            return;
        }
    }
}

//*****************************************************************************
//
//! \brief Get the assignment status of a channel.
//!
//! \param ulChannelID is the channel ID that have been assigned.
//! The channel ID can be:
//! - xDMA_CHANNEL_0
//! - xDMA_CHANNEL_1
//! - others refrence \ref xDMA_Channel_IDs
//! .
//!
//! \return Returns \b xtrue if the channel has been assigned and \b xfalse
//! if the channel is idle.
//
//*****************************************************************************
xtBoolean
DMAChannelAssignmentGet(unsigned long ulChannelID)
{
    int i = 0;

    xASSERT(xDMAChannelIDValid(ulChannelID));

    for(i = 0; g_psDMAChannelAssignTable[i].ulChannelID != xDMA_CHANNEL_NOT_EXIST; i++)
    {
        if(g_psDMAChannelAssignTable[i].ulChannelID == ulChannelID)
        {
            if(g_psDMAChannelAssignTable[i].bChannelAssigned == xfalse)
            {
                return xfalse;
            }
            else
            {
                return xtrue;
            }
        }
    }
    return xfalse;
}


//*****************************************************************************
//
//! \brief Sets the control parameters for a DMA channel.
//!
//! \param ulChannelID is the DMA channel ID.
//! \param ulControl is logical OR of several control values to set the control
//! parameters for the channel.
//!
//! This function is used to set control parameters for a uDMA transfer.  These
//! are typically parameters that are not changed often.
//!
//! The \e ulControl parameter is the logical OR of five values: the data size
//! of Memory, the data size of Peripheral, the Circular mode enable or not,
//! the Memory address increment, the Peripheral address increment.
//!
//! Choose the data size of Memory from one of \b DMA_MEM_WIDTH_8BIT,
//! \b DMA_MEM_WIDTH_16BIT,  \b or DMA_MEM_WIDTH_32BIT to select a data size
//! of 8, 16, or 32 bits.
//!
//! Choose the data size of Peripheral from one of \b DMA_PER_WIDTH_8BIT,
//! \b DMA_PER_WIDTH_16BIT,  \b or DMA_PER_WIDTH_32BIT to select a data size
//! of 8, 16, or 32 bits.
//!
//! Choose the Memory address increment from one of \b DMA_MEM_DIR_INC,
//! \b DMA_MEM_DIR_FIXED to selectan address increment or  select
//! non-incrementing.
//!
//! Choose the Peripheral address increment from one of \b DMA_PER_DIR_INC,
//! \b DMA_PER_DIR_FIXED to selectan address increment or  select
//! non-incrementing .
//!
//! Choose the the Circular mode from one of \b DMA_MODE_CIRC_EN,
//! \b DMA_MODE_CIRC_DIS to Enable circular mode or  disable
//! circular mode.
//!
//! \note The address increment cannot be smaller than the data size.
//! The transfer may use burst or single.
//!
//! \note This function will first reset MSIZE, PSIZE, MINC, PINC, CIRC into
//!       default value then write user parameter into CCR register, so, unless
//!       your modify those register bit via ulControl parameter, otherwise, it's
//!       will reserved default value.
//!       MSIZE --> 8-bit
//!       PSIZE --> 8-bit
//!       MINC  --> Memory increment mode disabled
//!       PINC  --> Peripheral increment mode disabled
//!       CIRC  --> Circular mode disabled
//!
//! \return None.
//
//*****************************************************************************
void
DMAChannelControlSet(unsigned long ulChannelID, unsigned long ulControl)
{
    unsigned long ulTmpReg  = 0 ;
    unsigned long ulRegMask =
           ( DMA_MEM_WIDTH_8BIT | DMA_MEM_WIDTH_16BIT | DMA_MEM_WIDTH_32BIT |
             DMA_PER_WIDTH_8BIT | DMA_PER_WIDTH_16BIT | DMA_PER_WIDTH_32BIT |
             DMA_MEM_DIR_INC    | DMA_MEM_DIR_FIXED   |
             DMA_PER_DIR_INC    | DMA_PER_DIR_FIXED   |
             DMA_MODE_CIRC_EN   | DMA_MODE_CIRC_DIS   );

    //Check parameters valid
    xASSERT(xDMAChannelIDValid(ulChannelID));
    xASSERT((ulControl & ulRegMask) != 0);

    //Read CCR register value
    ulTmpReg = xHWREG(g_psDMAChannel[ulChannelID]);

    //Set CCR MSIZE[1:0] PSIZE[1:0] MINC PINC CIRC to default value.
    //MSIZE --> 8-bit
    //PSIZE --> 8-bit
    //MINC  --> Memory increment mode disabled
    //PINC  --> Peripheral increment mode disabled
    //CIRC  --> Circular mode disabled
    ulTmpReg &= ~ulRegMask;

    ulTmpReg |= ulControl;

    //Write back to CCR register
    xHWREG(g_psDMAChannel[ulChannelID]) = ulTmpReg;

}

//*****************************************************************************
//
//! \brief Convert Memory and Peripheral to source and destination.
//!
//! \param ulControl is logical OR of several control values to set the control
//! .
//!
//! \return values after convertting.
//
//*****************************************************************************
unsigned long
DMAPTOM(unsigned long ulControl)
{
    unsigned long ulTemp;
    ulTemp = ulControl & 0xFFFFF03F;
    ulTemp |= ((ulControl & 0x300) << 2);
    ulTemp |= ((ulControl & 0x040) << 1);
    ulTemp |= ((ulControl & 0xC00) >> 2);
    ulTemp |= ((ulControl & 0x080) >> 1);
    return ulTemp;
}

//*****************************************************************************
//
//! Sets the transfer parameters for a uDMA channel control structure.
//!
//! \param ulChannelID is the uDMA channel ID.
//! \param ulMode is the type of uDMA transfer.
//! \param pvSrcAddr is the source address for the transfer.
//! \param pvDstAddr is the destination address for the transfer.
//! \param ulTransferSize is the number of data items to transfer.
//!
//! This function is used to set the parameters for a uDMA transfer.  These are
//! typically parameters that are changed often.  The function
//! uDMAChannelControlSet() MUST be called at least once for this channel prior
//! to calling this function.
//!
//! The \e ulChannelStructIndex parameter should be the logical OR of the
//! channel number with one of \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT to
//! choose whether the primary or alternate data structure is used.
//!
//! The \e ulMode parameter should be one of the following values:
//!
//! - \b UDMA_MODE_BASIC to perform a basic transfer based on request.
//! - \b UDMA_MODE_AUTO to perform a transfer that will always complete once
//!   started even if request is removed.
//! .
//!
//! The \e pvSrcAddr and \e pvDstAddr parameters are pointers to the first
//! location of the data to be transferred.  These addresses should be aligned
//! according to the item size.  The compiler will take care of this if the
//! pointers are pointing to storage of the appropriate data type.
//!
//! The \e ulTransferSize parameter is the number of data items, not the number
//! of bytes.
//!
//! The channel must also be enabled using uDMAChannelEnable() after calling
//! this function.  The transfer will not begin until the channel has been set
//! up and enabled.  Note that the channel is automatically disabled after the
//! transfer is completed, meaning that uDMAChannelEnable() must be called
//! again after setting up the next transfer.
//!
//! \note Great care must be taken to not modify a channel control structure
//! that is in use or else the results will be unpredictable, including the
//! possibility of undesired data transfers to or from memory or peripherals.
//! For BASIC and AUTO modes, it is safe to make changes when the channel is
//! disabled.
//!
//! \return None.
//
//*****************************************************************************
void
DMAChannelTransferSet(unsigned long ulChannelID, void *pvSrcAddr,
                       void *pvDstAddr, unsigned long ulTransferSize)
{
    xASSERT(xDMAChannelIDValid(ulChannelID));

    xHWREG(g_psDMAChannel[ulChannelID]) &= ~DMA_CCR1_EN;

    xHWREG(g_psDMAChannel[ulChannelID] + 0x8) = (unsigned long)pvSrcAddr;

    xHWREG(g_psDMAChannel[ulChannelID] + 0xC) = (unsigned long)pvDstAddr;

    xHWREG(g_psDMAChannel[ulChannelID] + 0x4) = ulTransferSize;

    //xHWREG(g_psDMAChannel[ulChannelID]) |= DMA_CCR1_EN;

}

//*****************************************************************************
//
//! \brief Init the DMA channel Interrupt Callback function.
//!
//! \param ulChannelID is channel ID.
//! \param pfnCallback is the callback function.
//!
//! When there is any channel interrupt occrus, Interrupt Handler will
//! call the callback function.
//!
//! param of pfnCallback
//! - pvCBData not used, always 0.
//! - ulEvent is the interrupt event.
//! - ulEvent not used, always 0.
//! - pvMsgData not used, always 0.
//! .
//!
//! \return None.
//
//*****************************************************************************
void
DMAChannelIntCallbackInit(unsigned long ulChannelID, xtEventCallback pfnCallback)
{
    int i = 0;
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));

    for(i = 0; g_psDMAChannelAssignTable[i].ulChannelID != xDMA_CHANNEL_NOT_EXIST; i++)
    {
        if(g_psDMAChannelAssignTable[i].ulChannelID == ulChannelID)
        {
            g_psDMAChannelAssignTable[i].pfnDMAChannelHandlerCallback = pfnCallback;

            return;
        }
    }

}

//*****************************************************************************
//
//! \brief Get the DMA interrupt flag of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! \param ulIntFlags is the interrupt type of DMA.
//! The channel ID can be:
//! - DMA1_CHANNEL_1
//! - DMA1_CHANNEL_2
//! - others refrence \ref STM32F1xx_DMA_Channel_IDs
//! .
//! The interrupt type can be:
//! - DMA_INT_TG
//! - DMA_INT_TC
//! - DMA_INT_HT
//! - DMA_INT_ERROR
//! .
//!
//! \return the Status of The DMA interrupt.
//
//*****************************************************************************
xtBoolean
DMAChannelIntFlagGet(unsigned long ulChannelID, unsigned long ulIntFlags)
{
    
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));
    xASSERT(((ulIntFlags & DMA_INT_TG) == DMA_INT_TG) ||
            ((ulIntFlags & DMA_INT_TC) == DMA_INT_TC) ||
            ((ulIntFlags & DMA_INT_HT) == DMA_INT_HT) ||                
            ((ulIntFlags & DMA_INT_ERROR) == DMA_INT_ERROR));

    if((ulChannelID) < 7)
    {
        ulIntFlags = (ulIntFlags << (ulChannelID*4));
        if((xHWREG(DMA1_BASE + DMA_ISR) & ulIntFlags) == ulIntFlags)
        {
            return (xtrue);
        }
        else
        {
            return (xfalse);
        }
        
        //return ((xHWREG(DMA1_BASE + DMA_ISR) | (ulIntFlags << ulChannelID*4))
        //        ? xtrue : xfalse);
    }
    else
    {
        ulIntFlags = (ulIntFlags << ((ulChannelID-1024) * 4));
        if((xHWREG(DMA1_BASE + DMA_ISR) & ulIntFlags) == ulIntFlags)
        {
            return (xtrue);
        }
        else
        {
            return (xfalse);
        }
        
        //return ((xHWREG(DMA2_BASE + DMA_ISR) |
        //        (ulIntFlags << (ulChannelID-1024)*4))
        //        ? xtrue : xfalse);
    }
}

//*****************************************************************************
//
//! \brief Clear the DMA interrupt flag of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! \param ulIntFlags is the interrupt type of DMA.
//! The channel ID can be:
//! - DMA1_CHANNEL_1
//! - DMA1_CHANNEL_2
//! - others refrence \ref STM32F1xx_DMA_Channel_IDs
//! .
//! The interrupt type can be:
//! - DMA_INT_TG
//! - DMA_INT_TC
//! - DMA_INT_HT
//! - DMA_INT_ERROR
//! .
//!
//! \return the Status of The DMA interrupt.
//
//*****************************************************************************
void
DMAChannelIntFlagClear(unsigned long ulChannelID, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));
    xASSERT(((ulIntFlags & DMA_INT_TG) == DMA_INT_TG) ||
            ((ulIntFlags & DMA_INT_TC) == DMA_INT_TC) ||
            ((ulIntFlags & DMA_INT_HT) == DMA_INT_HT) ||
            ((ulIntFlags & DMA_INT_ERROR) == DMA_INT_ERROR));

    if((ulChannelID) < 7)
    {
        //xHWREG(DMA1_BASE + DMA_IFCR) |= (ulIntFlags << ulChannelID*4);
        ulIntFlags = ulIntFlags << (ulChannelID * 4);
        xHWREG(DMA1_BASE + DMA_IFCR) |= ulIntFlags;
    }
    else
    {
        //xHWREG(DMA2_BASE + DMA_IFCR) |= (ulIntFlags << (ulChannelID-1024)*4);
        ulIntFlags = ulIntFlags << ((ulChannelID-1024) * 4);
        xHWREG(DMA1_BASE + DMA_IFCR) |= ulIntFlags;
    }
}

//*****************************************************************************
//
//! \brief Get the DMA remaining Byte Count of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! \param ulIntFlags is the interrupt type of DMA.
//! The channel ID can be:
//! - DMA1_CHANNEL_0
//! - DMA1_CHANNEL_1
//! - others refrence \ref STM32F1xx_DMA_Channel_IDs
//! .
//!
//! \return the DMA remaining Byte Count.
//
//*****************************************************************************
unsigned long
DMARemainTransferCountGet(unsigned long ulChannelID)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));

    return xHWREG(g_psDMAChannel[ulChannelID] + 4);
}

//*****************************************************************************
//
//! \brief Set attributes of a DMA channel.
//!
//! \param ulChannelID is the channel to configure.
//! \param ulAttr is a combination of attributes for the channel.
//!
//! The \e ulAttr parameter is the logical OR of any of the following:
//!
//! - Channel Priority:
//!   - \b DMA_ATTR_PRIORITY_LOW is used to set the channel to low priority.
//!   - \b DMA_ATTR_PRIORITY_MEDIUM medium priority.
//!   - \b DMA_ATTR_PRIORITY_HIGH high priority.
//!   - \b DMA_ATTR_PRIORITY_VHIGH very high priority.
//!   .
//! .
//!
//! \return None.
//
//*****************************************************************************
void
DMAChannelAttributeSet(unsigned long ulChannelID, unsigned long ulAttr)
{
    unsigned long ulTmpReg = 0;
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));
    xASSERT((ulAttr == DMA_ATTR_PRIORITY_LOW   ) ||
            (ulAttr == DMA_ATTR_PRIORITY_MEDIUM) ||
            (ulAttr == DMA_ATTR_PRIORITY_HIGH  ) ||
            (ulAttr == DMA_ATTR_PRIORITY_VHIGH ) );
    
    ulTmpReg = xHWREG(g_psDMAChannel[ulChannelID]);
    ulTmpReg &= ~DMA_ATTR_PRIORITY_MASK;
    ulTmpReg |= ulAttr;
    xHWREG(g_psDMAChannel[ulChannelID]) = ulTmpReg;
}

//*****************************************************************************
//
//! \brief Gets the attributes of a DMA channel.
//!
//! \param ulChannelID is the channel to configure.
//!
//! This function returns a combination of flags representing the attributes of
//! the DMA channel.
//!
//! \return Returns the logical OR of the attributes of the DMA channel, which
//! can be any of the following:
//! - Channel Priority:
//!   - \b DMA_ATTR_PRIORITY_LOW is used to set the channel to low priority.
//!   - \b DMA_ATTR_PRIORITY_MEDIUM medium priority.
//!   - \b DMA_ATTR_PRIORITY_HIGH high priority.
//!   - \b DMA_ATTR_PRIORITY_VHIGH very high priority.
//!   .
//! .
//
//*****************************************************************************
unsigned long
DMAChannelAttributeGet(unsigned long ulChannelID)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));
    return (xHWREG(g_psDMAChannel[ulChannelID]) & DMA_ATTR_PRIORITY_MASK);
}

