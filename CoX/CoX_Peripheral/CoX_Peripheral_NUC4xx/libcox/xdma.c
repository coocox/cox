//*****************************************************************************
//
//! \file xdma.c
//! \brief Driver for the DMA Controller.
//! \version V2.1.1.1
//! \date 11/14/2011
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

#include "CoX.h"
#include "xhw_dma.h"

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
// DMA Channels Address.
//
static unsigned long g_psDMAChannelAddress[] = 
{
    0x40008000,//DMA Channel 0,
    0x40008010,//DMA Channel 1,
    0x40008020,//DMA Channel 2,
    0x40008030,//DMA Channel 3,
    0x40008040,//DMA Channel 4,
    0x40008050,//DMA Channel 5,
    0x40008060,//DMA Channel 6,
    0x40008070,//DMA Channel 7,
    0x40008080,//DMA Channel 8,
    0x40008090,//DMA Channel 9,
    0x400080A0,//DMA Channel 10,
    0x400080B0,//DMA Channel 11,
    0x400080C0,//DMA Channel 12,
    0x400080D0,//DMA Channel 13,
    0x400080E0,//DMA Channel 14,
    0x400080F0,//DMA Channel 15,
};

//
// PDMA Service Selection Control Register.
//
static unsigned long g_psDMAIPSelectReg[] = 
{
    DMA_SMSEL0,
    DMA_SMSEL1,
    DMA_SMSEL2,
    DMA_SMSEL3
};

#define PDMA_PDSRx(a)  (((a) >> 16) & 0x1F)

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
    { xDMA_CHANNEL_12,  0,      xfalse },
    { xDMA_CHANNEL_13,  0,      xfalse },
    { xDMA_CHANNEL_14,  0,      xfalse },
    { xDMA_CHANNEL_15,  0,      xfalse },
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
    return( (ulChannelID >= 0) && (ulChannelID < 9));
}
#endif


//*****************************************************************************
//
//! DMA Interrupt Handler.
//!
//! The interrupt handler for DMA interrupts from the memory channel.
//!
//! \return None.
//
//*****************************************************************************
void
PDMA_IRQHandler(void)
{
	unsigned long ulBase = DMA0_BASE;
    unsigned long ulChannelID;
    for(ulChannelID = 0; 
        g_psDMAChannelAssignTable[ulChannelID].ulChannelID != 
        xDMA_CHANNEL_NOT_EXIST;
        ulChannelID++)
    {
        if(g_psDMAChannelAssignTable[ulChannelID].bChannelAssigned == xtrue)
        {
            if(xHWREG(ulBase + DMA_ISR) & DMA_EVENT_TC)
            {
                if(xHWREG(ulBase + DMA_TDF) & (1 << ulChannelID))
                {
    			  xHWREG(ulBase + DMA_TDF) |= (1 << ulChannelID);
    			   if (g_psDMAChannelAssignTable
                       [ulChannelID].pfnDMAChannelHandlerCallback != 0)    		
    		    		g_psDMAChannelAssignTable
    		    		[ulChannelID].pfnDMAChannelHandlerCallback(0,0,1,0);							
    			}
            }
            else if(xHWREG(ulBase + DMA_ISR) & DMA_EVENT_ERROR)
            {
                if(xHWREG(ulBase + DMA_ABTF) & (1 << ulChannelID))
                {
    			  xHWREG(ulBase + DMA_ABTF) |= (1 << ulChannelID);
    			   if (g_psDMAChannelAssignTable
                       [ulChannelID].pfnDMAChannelHandlerCallback != 0)    		
    		    		g_psDMAChannelAssignTable
    		    		[ulChannelID].pfnDMAChannelHandlerCallback(0,0,0,0);							
    			}
            }
            else if(xHWREG(ulBase + DMA_ISR) & DMA_EVENT_TEMPTY)
            {
                if(xHWREG(ulBase + DMA_SCATDF) & (1 << ulChannelID))
                {
    			  xHWREG(ulBase + DMA_SCATDF) |= (1 << ulChannelID);
    			   if (g_psDMAChannelAssignTable
                       [ulChannelID].pfnDMAChannelHandlerCallback != 0)
    		    		g_psDMAChannelAssignTable
    		    		[ulChannelID].pfnDMAChannelHandlerCallback(0,0,2,0);
    			}
            }
        }
    }
}

//*****************************************************************************
//
//! \brief Enable the DMA of a channel.
//!
//! \param ulChannelID is the channel ID that have been enabled.
//! The channel ID can be:
//! - DMA_CHANNEL_0
//! - DMA_CHANNEL_1
//! - others refrence \ref NUC4xx_DMA_Channel_IDs
//! .
//!
//! \return None.
//
//*****************************************************************************
void 
xDMAEnable(unsigned long ulChannelID)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));

    //
    // Enable DMA channel.
    //
    xHWREG(DMA0_BASE + DMA_CHCON) |= (1 << ulChannelID);
}

//*****************************************************************************
//
//! \brief Disable the DMA of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! The channel ID can be:
//! - DMA_CHANNEL_0
//! - DMA_CHANNEL_1
//! - others refrence \ref NUC4xx_DMA_Channel_IDs
//! .
//!
//! \return None.
//
//*****************************************************************************
void 
xDMADisable(unsigned long ulChannelID)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));

    //
    // Disable PDMA channel.
    //
    xHWREG(DMA0_BASE + DMA_STOP) |= (1 << ulChannelID);
}

//*****************************************************************************
//
//! \brief Enable the DMA interrupt of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! \param ulIntFlags is the interrupt type of DMA.
//! The channel ID can be:
//! - xDMA_CHANNEL_0
//! - xDMA_CHANNEL_1
//! - others refrence \ref NUC4xx_DMA_Channel_IDs
//! .
//! The interrupt type can be:
//! - xDMA_EVENT_TC
//! - xDMA_EVENT_ERROR
//! - refrence \ref NUC4xx_DMA_Event_Flags
//! .
//!
//! \return None.
//
//*****************************************************************************
void 
xDMAChannelIntEnable(unsigned long ulChannelID, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));
    xASSERT(((ulIntFlags & DMA_EVENT_TC) == DMA_EVENT_TC)       ||
            ((ulIntFlags & DMA_EVENT_ERROR) == DMA_EVENT_ERROR) ||
            ((ulIntFlags & DMA_EVENT_TEMPTY) == DMA_EVENT_TEMPTY));

    //
    // Enable DMA channel interrupt.
    //
    xHWREG(DMA0_BASE + DMA_IER) |= 1 << ulChannelID;
}

//*****************************************************************************
//
//! \brief Disable the DMA interrupt of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! \param ulIntFlags is the interrupt type of DMA.
//! The channel ID can be:
//! - xDMA_CHANNEL_0
//! - xDMA_CHANNEL_1
//! - others refrence \ref NUC4xx_DMA_Channel_IDs
//! .
//! The interrupt type can be:
//! - xDMA_EVENT_TC
//! - xDMA_EVENT_ERROR
//! - refrence \ref NUC4xx_DMA_Event_Flags
//! .
//!
//! \return None.
//
//*****************************************************************************
void 
xDMAChannelIntDisable(unsigned long ulChannelID, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));
    xASSERT(((ulIntFlags & DMA_EVENT_TC) == DMA_EVENT_TC)       ||
            ((ulIntFlags & DMA_EVENT_ERROR) == DMA_EVENT_ERROR) ||
            ((ulIntFlags & DMA_EVENT_TEMPTY) == DMA_EVENT_TEMPTY));

    //
    // Disable DMA channel interrupt.
    //
    xHWREG(DMA0_BASE + DMA_IER) &= ~(1 << ulChannelID);
}

//*****************************************************************************
//
//! \brief Dynamic assign a channel through the request.
//!
//! \param ulDMASrcRequest is the source DMA request signal. for more info 
//! refrence \ref NUC4xx_DMA_Request_Connections.
//! \param ulDMADestRequest is the destination DMA request signal.
//! for more info refrence \ref NUC4xx_DMA_Request_Connections.

//! This function dynamic allocate a channel according the DMA requests.
//! The \ref ulDMASrcRequest and \ref ulDMADestRequest can be:
//! - \ref xDMA_REQUEST_UART0_RX
//! - \ref xDMA_REQUEST_UART0_TX
//! - \ref xDMA_REQUEST_UART1_RX
//! - \ref xDMA_REQUEST_UART1_TX
//! - \ref xDMA_REQUEST_UART2_RX
//! - \ref xDMA_REQUEST_UART2_TX
//! - \ref xDMA_REQUEST_UART3_RX
//! - \ref xDMA_REQUEST_UART3_TX
//! - \ref xDMA_REQUEST_UART4_RX
//! - \ref xDMA_REQUEST_UART4_TX
//! - \ref xDMA_REQUEST_UART5_RX
//! - \ref xDMA_REQUEST_UART5_TX
//! - \ref xDMA_REQUEST_SPI0_RX
//! - \ref xDMA_REQUEST_SPI0_TX
//! - \ref xDMA_REQUEST_SPI1_RX
//! - \ref xDMA_REQUEST_SPI1_TX
//! - \ref xDMA_REQUEST_SPI2_RX
//! - \ref xDMA_REQUEST_SPI2_TX
//! - \ref xDMA_REQUEST_SPI3_RX
//! - \ref xDMA_REQUEST_SPI3_TX
//! - \ref xDMA_REQUEST_IIS0_RX
//! - \ref xDMA_REQUEST_IIS0_TX
//! - \ref xDMA_REQUEST_IIS1_RX
//! - \ref xDMA_REQUEST_IIS1_TX
//! .
//!
//! \note ulDMASrcRequest can only be XX_RX,ulDMADestRequest can only be XX_TX.
//!
//! \return Returns a Channel ID that dynamic assignment.
//! The channel ID can be:
//! - DMA_CHANNEL_0
//! - DMA_CHANNEL_1
//! - others refrence \ref NUC4xx_DMA_Channel_IDs
//! .
//
//*****************************************************************************
unsigned long 
xDMAChannelDynamicAssign(unsigned long ulDMASrcRequest,
                         unsigned long ulDMADestRequest)
{
    unsigned long ulChannelID;
    //
    // Check the arguments.
    //
    xASSERT((ulDMASrcRequest == xDMA_REQUEST_UART0_RX) || 
            (ulDMASrcRequest == xDMA_REQUEST_UART1_RX) ||
            (ulDMASrcRequest == xDMA_REQUEST_UART2_RX) ||
            (ulDMASrcRequest == xDMA_REQUEST_UART3_RX) ||
            (ulDMASrcRequest == xDMA_REQUEST_UART4_RX) ||
            (ulDMASrcRequest == xDMA_REQUEST_UART5_RX) ||
            (ulDMASrcRequest == xDMA_REQUEST_ADC_RX)   ||
            (ulDMASrcRequest == xDMA_REQUEST_MEM)      ||
            (ulDMASrcRequest == xDMA_REQUEST_SPI0_RX)  ||
            (ulDMASrcRequest == xDMA_REQUEST_SPI1_RX)  ||
            (ulDMASrcRequest == xDMA_REQUEST_SPI2_RX)  ||
            (ulDMASrcRequest == xDMA_REQUEST_SPI3_RX)  ||
            (ulDMASrcRequest == xDMA_REQUEST_IIS0_RX)  ||
            (ulDMASrcRequest == xDMA_REQUEST_IIS0_RX)
           );
    xASSERT((ulDMADestRequest == xDMA_REQUEST_UART0_TX) || 
            (ulDMADestRequest == xDMA_REQUEST_UART1_TX) ||
            (ulDMADestRequest == xDMA_REQUEST_UART2_TX) ||
            (ulDMADestRequest == xDMA_REQUEST_UART3_TX) ||
            (ulDMADestRequest == xDMA_REQUEST_UART4_TX) ||
            (ulDMADestRequest == xDMA_REQUEST_UART5_TX) ||
            (ulDMADestRequest == xDMA_REQUEST_MEM)      ||
            (ulDMADestRequest == xDMA_REQUEST_SPI0_TX)  ||
            (ulDMADestRequest == xDMA_REQUEST_SPI1_TX)  ||
            (ulDMADestRequest == xDMA_REQUEST_SPI2_TX)  ||
            (ulDMADestRequest == xDMA_REQUEST_SPI3_TX)  ||
            (ulDMADestRequest == xDMA_REQUEST_IIS0_TX)  ||
            (ulDMADestRequest == xDMA_REQUEST_IIS1_TX)
           );

    //
    // NUC4xx DMA do not support P to P
    //
    if((ulDMASrcRequest != xDMA_REQUEST_MEM) &&
       (ulDMADestRequest != xDMA_REQUEST_MEM))
    {
        return xDMA_CHANNEL_NOT_EXIST;
    }

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

    //
    // MEM to TX type
    //
    if(!(ulDMASrcRequest & xDMA_REQUEST_MEM) && (ulDMASrcRequest & 0x00000100))
    {
        if(g_psDMAChannelAssignTable[ulChannelID].ulChannelID != 
            xDMA_CHANNEL_NOT_EXIST)
        {
            xHWREG(g_psDMAIPSelectReg[ulChannelID/4]) &=
                        ~(0x1F << ((ulChannelID % 4) * 8));
            xHWREG(g_psDMAIPSelectReg[ulChannelID/4]) |=
                        (PDMA_PDSRx(ulDMASrcRequest) << ((ulChannelID % 4) * 8));

            return ulChannelID;
        }
        else
        {
            return xDMA_CHANNEL_NOT_EXIST;
        }
    }

    //
    //! RX to MEM type
    //
    if(!(ulDMADestRequest & xDMA_REQUEST_MEM) && !(ulDMADestRequest & 0x00000100))
    {
        if(g_psDMAChannelAssignTable[ulChannelID].ulChannelID != 
            xDMA_CHANNEL_NOT_EXIST)
        {
            xHWREG(g_psDMAIPSelectReg[ulChannelID/4]) &=
                        ~(0x1F << ((ulChannelID % 4) * 8));
            xHWREG(g_psDMAIPSelectReg[ulChannelID/4]) |=
                        (PDMA_PDSRx(ulDMASrcRequest) << ((ulChannelID % 4) * 8));
            return ulChannelID;
        }
        else
        {
            return xDMA_CHANNEL_NOT_EXIST;
        }
    }

    //
    // when the src request is tx type, or dest request is rx type, assign false.
    //
    return xDMA_CHANNEL_NOT_EXIST;
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
xDMAChannelAssignmentGet(unsigned long ulChannelID)
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
//! \brief Free the assignment of  a channel.
//!
//! \param ulChannelID is the channel ID that have been assigned.
//! The channel ID can be:
//! - xDMA_CHANNEL_0
//! - xDMA_CHANNEL_1
//! - others refrence \ref xDMA_Channel_IDs
//! .
//!
//! \return None.
//
//*****************************************************************************
void
xDMAChannelDeAssign(unsigned long ulChannelID)
{
    int i;
    
    xASSERT(xDMAChannelIDValid(ulChannelID));

    for(i = 0; 
        g_psDMAChannelAssignTable[i].ulChannelID != xDMA_CHANNEL_NOT_EXIST;
        i++)
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
//! \brief Sets the control parameters for a DMA channel.
//!
//! \param ulChannelID is the DMA channel ID.
//! \param ulControl is logical OR of several control values to set the control
//! parameters for the channel.
//!
//! This function is used to set control parameters for a uDMA transfer.  These
//! are typically parameters that are not changed often.
//!
//! The \e ulControl parameter is the logical OR of five values: the data size,
//! the source address increment, the destination address increment.
//!
//! Choose the source data size from one of \b DMA_WIDTH_8BIT,
//! \b DMA_WIDTH_16BIT,  \b or DMA_WIDTH_32BIT to select a data size
//! of 8, 16, or 32 bits.
//!
//! Choose the destination data size from one of \b DMA_WIDTH_8BIT,
//! \b DMA_WIDTH_16BIT,  \b or DMA_WIDTH_32BIT to select a data size
//! of 8, 16, or 32 bits.
//!
//! Choose the source address increment from one of \b DMA_SRC_DIR_INC,
//! \b DMA_SRC_DIR_FIXED to selectan address increment or  select
//! non-incrementing 
//!
//! Choose the destination address increment from one of \b DMA_DST_DIR_INC,
//! \b DMA_DST_DIR_FIXED to selectan address increment or  select
//! non-incrementing 
//!
//! \note The address increment cannot be smaller than the data size. 
//! The transfer may use burst or single.
//!
//! \return None.
//
//*****************************************************************************
void
xDMAChannelControlSet(unsigned long ulChannelID,
                      unsigned long ulControl)
{
    
    xASSERT(xDMAChannelIDValid(ulChannelID));


    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_CTRL) &=
    ~(DMA_CTRL_SAR_INC_M | DMA_CTRL_DAR_INC_M | DMA_CTRL_TWS_M);
    
    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_CTRL) |= ulControl;
}

//*****************************************************************************
//
//! Sets the transfer parameters for a DMA channel control structure.
//!
//! \param ulChannelID is the uDMA channel ID.
//! \param ulMode is the type of DMA transfer.
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
//! - \b xDMA_MODE_BASIC to perform a basic transfer based on request.
//! - \b xDMA_MODE_AUTO to perform a transfer that will always complete once
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
xDMAChannelTransferSet(unsigned long ulChannelID, unsigned long ulMode, unsigned long pvSrcAddr,
                        unsigned long pvDstAddr, unsigned long ulTransferSize)
{
    xASSERT(xDMAChannelIDValid(ulChannelID));
    xASSERT((ulTransferSize == 1)  &&
    		(ulTransferSize == 2)  &&
    		(ulTransferSize == 4)  &&
    		(ulTransferSize == 8)  &&
    		(ulTransferSize == 16) &&
    		(ulTransferSize == 32) &&
    		(ulTransferSize == 64) &&
    		(ulTransferSize == 128));

    xHWREG(DMA0_BASE + DMA_STOP) |= (1 << ulChannelID);

    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_SAR) =
    (unsigned long)pvSrcAddr;
    
    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DAR) =
    (unsigned long)pvDstAddr;
    
    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_CTRL) &= ~DMA_CTRL_REQ_TYPE;
    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_CTRL) |= ulMode;

    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_CTRL) &= ~DMA_CTRL_BUR_SIZE_M;
    switch(ulTransferSize)
    {
    case 1: xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_CTRL) |= 0x7 << DMA_CTRL_BUR_SIZE_S; break;
    case 2: xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_CTRL) |= 0x6 << DMA_CTRL_BUR_SIZE_S; break;
    case 4: xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_CTRL) |= 0x5 << DMA_CTRL_BUR_SIZE_S; break;
    case 8: xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_CTRL) |= 0x4 << DMA_CTRL_BUR_SIZE_S; break;
    case 16: xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_CTRL) |= 0x3 << DMA_CTRL_BUR_SIZE_S; break;
    case 32: xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_CTRL) |= 0x2 << DMA_CTRL_BUR_SIZE_S; break;
    case 64: xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_CTRL) |= 0x1 << DMA_CTRL_BUR_SIZE_S; break;
    case 128: xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_CTRL) |= 0x0 << DMA_CTRL_BUR_SIZE_S; break;
    default: break;
    }
    xHWREG(DMA0_BASE + DMA_CHCON) |= (1 << ulChannelID);
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
//! - ulEvent not used, always 0..
//! - pvMsgData not used, always 0.
//! .
//!
//! \return None.
//
//*****************************************************************************
void 
xDMAChannelIntCallbackInit(unsigned long ulChannelID,
                    xtEventCallback pfnCallback)
{
    int i;
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));

    for(i = 0; g_psDMAChannelAssignTable[i].ulChannelID != 
           xDMA_CHANNEL_NOT_EXIST;
               i++)
    {
        if(g_psDMAChannelAssignTable[i].ulChannelID == ulChannelID)
        {
            g_psDMAChannelAssignTable[i].pfnDMAChannelHandlerCallback = 
                pfnCallback;

            break;
        }
    }
}

//*****************************************************************************
//
//! \brief Get the DMA channel Interrupt Callback function that have been set.
//!
//! \param ulChannelID is channel ID.
//!
//! When there is any channel interrupt occrus, Interrupt Handler will 
//! call the callback function. 
//!
//! \return the call back function point.
//
//*****************************************************************************

xtEventCallback 
DMAChannelIntCallbackGet(unsigned long ulChannelID)
{
    int i;
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));

    for(i = 0; g_psDMAChannelAssignTable[i].ulChannelID != 
           xDMA_CHANNEL_NOT_EXIST;
               i++)
    {
        if(g_psDMAChannelAssignTable[i].ulChannelID == ulChannelID)
        {
            return g_psDMAChannelAssignTable[i].pfnDMAChannelHandlerCallback;
        }
    }

    return 0;
}

//*****************************************************************************
//
//! \brief Get the DMA interrupt flag of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! \param ulIntFlags is the interrupt type of DMA.
//! The channel ID can be:
//! - DMA_CHANNEL_0
//! - DMA_CHANNEL_1
//! - others refrence \ref NUC4xx_DMA_Channel_IDs
//! .
//! The interrupt type can be:
//! - DMA_EVENT_TC
//! - DMA_EVENT_ERROR
//! - refrence \ref NUC4xx_DMA_Event_Flags
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
    xASSERT((ulIntFlags == DMA_EVENT_TC)    ||
            (ulIntFlags == DMA_EVENT_ERROR) ||
            (ulIntFlags == DMA_EVENT_TEMPTY));

    if(ulIntFlags == DMA_EVENT_TC)
    {
        return (((xHWREG(DMA0_BASE + DMA_TDF) & (1 << ulChannelID)) &&
               (xHWREG(DMA0_BASE + DMA_ISR)&DMA_EVENT_TC)) ? xtrue : xfalse);
    }
    if(ulIntFlags == DMA_EVENT_ERROR)
    {
        return (((xHWREG(DMA0_BASE + DMA_ABTF) & (1 << ulChannelID)) &&
               (xHWREG(DMA0_BASE + DMA_ISR) & DMA_EVENT_ERROR)) ? xtrue : xfalse);
    }
    if(ulIntFlags == DMA_EVENT_TEMPTY)
    {
        return (((xHWREG(DMA0_BASE + DMA_SCATDF) & (1 << ulChannelID)) &&
               (xHWREG(DMA0_BASE + DMA_ISR) & DMA_EVENT_TEMPTY)) ? xtrue : xfalse);
    }
    return xfalse;
}

//*****************************************************************************
//
//! \brief Clear the DMA interrupt flag of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! \param ulIntFlags is the interrupt type of DMA.
//! The channel ID can be:
//! - DMA_CHANNEL_0
//! - DMA_CHANNEL_1
//! - others refrence \ref NUC4xx_DMA_Channel_IDs
//! .
//! The interrupt type can be:
//! - DMA_EVENT_TC
//! - DMA_EVENT_ERROR
//! - refrence \ref NUC4xx_DMA_Event_Flags
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
    xASSERT((ulIntFlags == DMA_EVENT_TC)    ||
            (ulIntFlags == DMA_EVENT_ERROR) ||
            (ulIntFlags == DMA_EVENT_TEMPTY));

    if(ulIntFlags == DMA_EVENT_TC)
    {
    	xHWREG(DMA0_BASE + DMA_TDF) |= (1 << ulChannelID);
    }
    if(ulIntFlags == DMA_EVENT_ERROR)
    {
    	xHWREG(DMA0_BASE + DMA_ABTF) |= (1 << ulChannelID);
    }
    if(ulIntFlags == DMA_EVENT_TEMPTY)
    {
        xHWREG(DMA0_BASE + DMA_SCATDF) |= (1 << ulChannelID);
    }
}

//*****************************************************************************
//
//! \brief Get the DMA Current Source Address of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! \param ulIntFlags is the interrupt type of DMA.
//! The channel ID can be:
//! - DMA_CHANNEL_0
//! - DMA_CHANNEL_1
//! - others refrence \ref NUC4xx_DMA_Channel_IDs
//! .
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
PDMACurrentSourceAddrGet(unsigned long ulChannelID)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));

    return xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_SAR);
}

//*****************************************************************************
//
//! \brief Get the DMA Current Destination Address of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! \param ulIntFlags is the interrupt type of DMA.
//! The channel ID can be:
//! - DMA_CHANNEL_0
//! - DMA_CHANNEL_1
//! - others refrence \ref NUC4xx_DMA_Channel_IDs
//! .
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
DMACurrentDestAddrGet(unsigned long ulChannelID)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));

    return xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DAR);
}

//*****************************************************************************
//
//! \brief Get the DMA Current Byte Count of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! \param ulIntFlags is the interrupt type of DMA.
//! The channel ID can be:
//! - DMA_CHANNEL_0
//! - DMA_CHANNEL_1
//! - others refrence \ref NUC4xx_DMA_Channel_IDs
//! .
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
DMARemainTransferCountGet(unsigned long ulChannelID)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));

    return xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_CTRL) >> DMA_CTRL_TFR_CNT_S;
}
