//*****************************************************************************
//
//! \file xdma.c
//! \brief Driver for the DMA Controller.
//! \version V2.2.1.0
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

#include "xhw_memmap.h"
#include "xhw_types.h"
#include "xhw_dma.h"
#include "xdebug.h"
#include "xcore.h"
#include "xdma.h"

typedef struct
{
    //
    // Channel ID
    //
    unsigned long ulChannelID;

    //
    // Channel interrupt callback function
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
    DMA0_BASE,
    DMA1_BASE,
    DMA2_BASE,
    DMA3_BASE
};

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
    { xDMA_CHANNEL_16,  0,      xfalse },        
    { xDMA_CHANNEL_17,  0,      xfalse },
    { xDMA_CHANNEL_18,  0,      xfalse },            
    { xDMA_CHANNEL_19,  0,      xfalse },
    
    { xDMA_CHANNEL_20,  0,      xfalse },
    { xDMA_CHANNEL_21,  0,      xfalse },            
    { xDMA_CHANNEL_22,  0,      xfalse },
    { xDMA_CHANNEL_23,  0,      xfalse },        
    { xDMA_CHANNEL_24,  0,      xfalse },
    { xDMA_CHANNEL_25,  0,      xfalse },
    { xDMA_CHANNEL_26,  0,      xfalse },        
    { xDMA_CHANNEL_27,  0,      xfalse },
    { xDMA_CHANNEL_28,  0,      xfalse },            
    { xDMA_CHANNEL_29,  0,      xfalse },
    
    { xDMA_CHANNEL_30,  0,      xfalse },        
    { xDMA_CHANNEL_31,  0,      xfalse },
    { xDMA_CHANNEL_32,  0,      xfalse },
    { xDMA_CHANNEL_33,  0,      xfalse },        
    { xDMA_CHANNEL_34,  0,      xfalse },
    { xDMA_CHANNEL_35,  0,      xfalse },
    { xDMA_CHANNEL_36,  0,      xfalse },        
    { xDMA_CHANNEL_37,  0,      xfalse },
    { xDMA_CHANNEL_38,  0,      xfalse },            
    { xDMA_CHANNEL_39,  0,      xfalse },
	
    { xDMA_CHANNEL_40,  0,      xfalse },        
    { xDMA_CHANNEL_41,  0,      xfalse },
    { xDMA_CHANNEL_42,  0,      xfalse },
    { xDMA_CHANNEL_43,  0,      xfalse },        
    { xDMA_CHANNEL_44,  0,      xfalse },
    { xDMA_CHANNEL_45,  0,      xfalse },
    { xDMA_CHANNEL_46,  0,      xfalse },        
    { xDMA_CHANNEL_47,  0,      xfalse },
    { xDMA_CHANNEL_48,  0,      xfalse },            
    { xDMA_CHANNEL_49,  0,      xfalse },
	
    { xDMA_CHANNEL_50,  0,      xfalse },        
    { xDMA_CHANNEL_51,  0,      xfalse },
    { xDMA_CHANNEL_52,  0,      xfalse },
    { xDMA_CHANNEL_53,  0,      xfalse },        
    { xDMA_CHANNEL_54,  0,      xfalse },
    { xDMA_CHANNEL_55,  0,      xfalse },
    { xDMA_CHANNEL_56,  0,      xfalse },        
    { xDMA_CHANNEL_57,  0,      xfalse },
    { xDMA_CHANNEL_58,  0,      xfalse },            
    { xDMA_CHANNEL_59,  0,      xfalse },
	
    { xDMA_CHANNEL_60,  0,      xfalse },        
    { xDMA_CHANNEL_61,  0,      xfalse },
    { xDMA_CHANNEL_62,  0,      xfalse },
    { xDMA_CHANNEL_63,  0,      xfalse },
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
    return( (ulChannelID >= 0) && (ulChannelID < 4));
}
#endif

//*****************************************************************************
//
//! \internal
//! \brief Checks a DMA request.
//!
//! \param ulRequest is the DMA request.
//!
//! This function determines if a DMA request is valid.
//!
//! \return Returns \b xtrue if the request is valid and \b xfalse
//! otherwise.
//
//*****************************************************************************
#ifdef xDEBUG
static xtBoolean
xDMARequestValid(unsigned long ulRequest)
{
    return((ulRequest == xDMA_REQUEST_MEM) ||
           (ulRequest == xDMA_REQUEST_UART0_RX) ||
           (ulRequest == xDMA_REQUEST_UART0_TX) || 
           (ulRequest == xDMA_REQUEST_UART1_RX) || 
           (ulRequest == xDMA_REQUEST_UART1_TX) || 
           (ulRequest == xDMA_REQUEST_UART2_RX) || 
           (ulRequest == xDMA_REQUEST_UART2_TX) || 
           (ulRequest == xDMA_REQUEST_SPI0_RX)  ||     
           (ulRequest == xDMA_REQUEST_SPI0_TX)  ||
           (ulRequest == xDMA_REQUEST_SPI1_RX)  ||
           (ulRequest == xDMA_REQUEST_SPI1_TX)        
          );
}
#endif

//*****************************************************************************
//
//! DMA channel 0 transfer complete and error Interrupt Handler.
//!
//! The interrupt handler for DMA interrupts from the memory channel. 
//!
//! \return None.
//
//*****************************************************************************
void
DMA0IntHandler(void)
{
    unsigned long ulEvent = 0;
    
    ulEvent = xHWREG(DMA0_BASE + DMA_DSR_BCR) & 0x71000000;
    
    //
    // Clear the transfer complete interrupt flag
    //
    xHWREG(DMA0_BASE + DMA_DSR_BCR) |= DMA_DSR_BCR_DONE;
    if(g_psDMAChannelAssignTable[0].pfnDMAChannelHandlerCallback != 0)
    {
        g_psDMAChannelAssignTable[0].pfnDMAChannelHandlerCallback(0,0,ulEvent,0);
    }
}

//*****************************************************************************
//
//! DMA channel 1 transfer complete and error Interrupt Handler.
//!
//! The interrupt handler for DMA interrupts from the memory channel. 
//!
//! \return None.
//
//*****************************************************************************
void
DMA1IntHandler(void)
{
    unsigned long ulEvent = 0;
    
    ulEvent = xHWREG(DMA0_BASE + DMA_DSR_BCR) & 0x71000000;
    
    //
    // Clear the transfer complete interrupt flag
    //
    xHWREG(DMA1_BASE + DMA_DSR_BCR) |= DMA_DSR_BCR_DONE;
    
    if(g_psDMAChannelAssignTable[1].pfnDMAChannelHandlerCallback != 0)
    {
        g_psDMAChannelAssignTable[1].pfnDMAChannelHandlerCallback(0,0,ulEvent,0);
    }	
}

//*****************************************************************************
//
//! DMA channel 2 transfer complete and error Interrupt Handler.
//!
//! The interrupt handler for DMA interrupts from the memory channel. 
//!
//! \return None.
//
//*****************************************************************************
void
DMA2IntHandler(void)
{
    unsigned long ulEvent = 0;
    
    ulEvent = xHWREG(DMA0_BASE + DMA_DSR_BCR) & 0x71000000;
    
    //
    // Clear the transfer complete interrupt flag
    //
    xHWREG(DMA2_BASE + DMA_DSR_BCR) |= DMA_DSR_BCR_DONE;
    
    if(g_psDMAChannelAssignTable[2].pfnDMAChannelHandlerCallback != 0)
    {
        g_psDMAChannelAssignTable[2].pfnDMAChannelHandlerCallback(0,0,ulEvent,0);
    }	
}

//*****************************************************************************
//
//! DMA channel 3 transfer complete and error Interrupt Handler.
//!
//! The interrupt handler for DMA interrupts from the memory channel. 
//!
//! \return None.
//
//*****************************************************************************
void
DMA3IntHandler(void)
{
    unsigned long ulEvent = 0;
    
    ulEvent = xHWREG(DMA0_BASE + DMA_DSR_BCR) & 0x71000000;
    
    //
    // Clear the transfer complete interrupt flag
    //
    xHWREG(DMA3_BASE + DMA_DSR_BCR) |= DMA_DSR_BCR_DONE;
    
    if(g_psDMAChannelAssignTable[3].pfnDMAChannelHandlerCallback != 0)
    {
        g_psDMAChannelAssignTable[3].pfnDMAChannelHandlerCallback(0,0,ulEvent,0);
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
//! - others refrence \ref KLx_DMA_Channel_IDs
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
    xHWREGB(DMAMUX0_BASE + ulChannelID) |= DMAMUX0_CHCFG_ENBL;
}

//*****************************************************************************
//
//! \brief Disable the DMA of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! The channel ID can be:
//! - DMA_CHANNEL_0
//! - DMA_CHANNEL_1
//! - others refrence \ref KLx_DMA_Channel_IDs
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
    xHWREGB(DMAMUX0_BASE + ulChannelID) &= ~DMAMUX0_CHCFG_ENBL;
}

//*****************************************************************************
//
//! \brief Get the DMA of a channel busy or not.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! The channel ID can be:
//! - DMA_CHANNEL_0
//! - DMA_CHANNEL_1
//! - others refrence \ref KLx_DMA_Channel_IDs
//! .
//!
//! \return returns xtrue if DMA channel is busy or returns xfalse.
//
//*****************************************************************************
xtBoolean 
DMAChannelIsBusy(unsigned long ulChannelID)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));

    return ((xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DSR_BCR) 
            | DMA_DSR_BCR_BSY) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Enable the DMA interrupt of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! \param ulIntFlags is the interrupt type of DMA.
//! The channel ID can be:
//! - DMA_CHANNEL_0
//! - DMA_CHANNEL_1
//! - others refrence \ref KLx_DMA_Channel_IDs
//! .
//! The interrupt type can be:
//! - DMA_EVENT_TC
//! - refrence \ref KLx_DMA_Event_Flags
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
    xASSERT((ulIntFlags == DMA_EVENT_TC) || (ulIntFlags == DMA_EVENT_ERROR));

    //
    // Enable DMA channel interrupt.
    //
    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DCR) |= ulIntFlags;
}

//*****************************************************************************
//
//! \brief Disable the DMA interrupt of a channel.
//!
//! \param ulChannelID is the channel ID that have been disabled.
//! \param ulIntFlags is the interrupt type of DMA.
//! The channel ID can be:
//! - DMA_CHANNEL_0
//! - DMA_CHANNEL_1
//! - others refrence \ref KLx_DMA_Channel_IDs
//! .
//! The interrupt type can be:
//! - DMA_EVENT_TC
//! - refrence \ref KLx_DMA_Event_Flags
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
    xASSERT((ulIntFlags == DMA_EVENT_TC) || (ulIntFlags == DMA_EVENT_ERROR));

    //
    // Disable DMA channel interrupt.
    //
    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DCR) &= ~ulIntFlags;
}

//*****************************************************************************
//
//! \brief Dynamic assign a channel through the request.
//!
//! \param ulDMASrcRequest is the source DMA request signal. for more info 
//! refrence \ref KLx_DMA_Request_Connections.
//! \param ulDMADestRequest is the destination DMA request signal.
//! for more info refrence \ref KLx_DMA_Request_Connections.

//! This function dynamic allocate a channel according the DMA requests.
//! The \ref ulDMASrcRequest and \ref ulDMADestRequest can be:
//! - \ref DMA_REQUEST_UART0_RX
//! - \ref DMA_REQUEST_UART0_TX
//! - \ref DMA_REQUEST_UART1_RX
//! - \ref DMA_REQUEST_UART1_TX
//! - \ref DMA_REQUEST_UART2_RX
//! - \ref DMA_REQUEST_UART2_TX
//! - \ref DMA_REQUEST_SPI0_RX
//! - \ref DMA_REQUEST_SPI0_TX
//! - \ref DMA_REQUEST_SPI1_RX
//! - \ref DMA_REQUEST_SPI1_TX
//! .
//!
//! \note ulDMASrcRequest can only be XX_RX,ulDMADestRequest can only be XX_TX.
//!
//! \return Returns a Channel ID that dynamic assignment.
//! The channel ID can be:
//! - DMA_CHANNEL_0
//! - DMA_CHANNEL_1
//! - others refrence \ref KLx_DMA_Channel_IDs
//! .
//
//*****************************************************************************
unsigned long 
DMAChannelDynamicAssign(unsigned long ulDMASrcRequest,    
                         unsigned long ulDMADestRequest)
{
    unsigned long ulChannelID, ulTemp;
	
    //
    // Check the arguments.
    //
    xASSERT(xDMARequestValid(ulDMASrcRequest));
    xASSERT(xDMARequestValid(ulDMADestRequest));

    //
    // KLx DMA do not support P to P
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
    // RX ----> MEM
    //
    if(!(ulDMASrcRequest & xDMA_REQUEST_MEM) && !(ulDMASrcRequest & 0x40000000))
    {
        //
        // Is assigned ?
        //
        if(g_psDMAChannelAssignTable[ulChannelID].ulChannelID != 
            xDMA_CHANNEL_NOT_EXIST)
        {
            //
            // Do assign
            //
            ulTemp = xHWREGB(DMAMUX0_BASE + ulChannelID);
            ulTemp &= ~DMAMUX0_CHCFG_SOURCE_M;
            ulTemp |= ulDMASrcRequest & 0xFF;
            xHWREGB(DMAMUX0_BASE + ulChannelID) = (unsigned char)ulTemp;
            return ulChannelID; 
        }
        else
        {
            return xDMA_CHANNEL_NOT_EXIST;
        }
    }
    
    //
    // DestRequest is not Mem and DestRequest is Rx Type(MEM ----> TX)
    //
    if(!(ulDMADestRequest & xDMA_REQUEST_MEM) && (ulDMADestRequest & 0x40000000))     
    {
        //
        // Is assigned ?
        //
        if(g_psDMAChannelAssignTable[ulChannelID].ulChannelID != 
            xDMA_CHANNEL_NOT_EXIST)
        {
            //
            // Do assign
            //
            ulTemp = xHWREGB(DMAMUX0_BASE + ulChannelID);
            ulTemp &= ~DMAMUX0_CHCFG_SOURCE_M;
            ulTemp |= ulDMADestRequest & 0xFF;       
            xHWREGB(DMAMUX0_BASE + ulChannelID) = (unsigned char)ulTemp;
            return ulChannelID; 
        }
        else
        {
            return xDMA_CHANNEL_NOT_EXIST;
        }
    }
	
    //
    // Mem to Mem type
    //
    if((ulDMASrcRequest & xDMA_REQUEST_MEM) &&
       (ulDMADestRequest & xDMA_REQUEST_MEM))
    {
        if(g_psDMAChannelAssignTable[ulChannelID].ulChannelID != 
            xDMA_CHANNEL_NOT_EXIST)
        {
            xHWREGB(DMAMUX0_BASE + ulChannelID) &= ~DMAMUX0_CHCFG_SOURCE_M;
            xHWREGB(DMAMUX0_BASE + ulChannelID) |= 61;
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
DMAChannelDeAssign(unsigned long ulChannelID)
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
DMAChannelControlSet(unsigned long ulChannelID, unsigned long ulControl)                    
{  
    //
    // Check the arguments.
    // 
    xASSERT(xDMAChannelIDValid(ulChannelID));

    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DCR) &= 
    ~(DMA_DCR_SINC | DMA_DCR_SSIZE_M | DMA_DCR_DINC | DMA_DCR_DSIZE_M);
    
    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DCR) |= ulControl;
}

//*****************************************************************************
//
//! Sets the transfer parameters for a DMA channel control structure.
//!
//! \param ulChannelID is the DMA channel ID.
//! \param ulMode is the type of DMA transfer.
//! \param pvSrcAddr is the source address for the transfer.
//! \param pvDstAddr is the destination address for the transfer.
//! \param ulTransferSize is the number of data items to transfer.
//!
//! This function is used to set the parameters for a DMA transfer.  These are
//! typically parameters that are changed often.  The function
//! DMAChannelControlSet() MUST be called at least once for this channel prior
//! to calling this function.
//!
//! The \e ulChannelStructIndex parameter should be the logical OR of the
//! channel number with one of \b DMA_PRI_SELECT or \b DMA_ALT_SELECT to
//! choose whether the primary or alternate data structure is used.
//!
//! The \e ulMode parameter should be one of the following values:
//!
//! - \b DMA_MODE_BASIC to perform a basic transfer based on request.
//! - \b DMA_MODE_AUTO to perform a transfer that will always complete once
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
//! The channel must also be enabled using DMAChannelEnable() after calling
//! this function.  The transfer will not begin until the channel has been set
//! up and enabled.  Note that the channel is automatically disabled after the
//! transfer is completed, meaning that DMAChannelEnable() must be called
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
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));
    xASSERT((ulTransferSize >= 0)&&(ulTransferSize <= DMA_DSR_BCR_BCR_M));
	
    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_SAR) = (unsigned long)pvSrcAddr;
    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DAR) = (unsigned long)pvDstAddr;
	
    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DSR_BCR) &= ~DMA_DSR_BCR_BCR_M;
    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DSR_BCR) |= ulTransferSize;  
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
DMAChannelIntCallbackInit(unsigned long ulChannelID, 
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
//! - others refrence \ref KLx_DMA_Channel_IDs
//! .
//! The interrupt type can be:
//! - DMA_EVENT_TC
//! - refrence \ref KLx_DMA_Event_Flags
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
    xASSERT(ulIntFlags == DMA_EVENT_TC);

    return ((xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DSR_BCR_DONE) | ulIntFlags)
            ? xtrue : xfalse);
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
//! - others refrence \ref KLx_DMA_Channel_IDs
//! .
//! The interrupt type can be:
//! - DMA_EVENT_TC
//! - refrence \ref KLx_DMA_Event_Flags
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
    xASSERT(ulIntFlags == DMA_EVENT_TC);

    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DSR_BCR_DONE) |= ulIntFlags;
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
//! - others refrence \ref KLx_DMA_Channel_IDs
//! .
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
DMACurrentSourceAddrGet(unsigned long ulChannelID)
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
//! - others refrence \ref KLx_DMA_Channel_IDs
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
//! - others refrence \ref KLx_DMA_Channel_IDs
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

    return (xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DSR_BCR) & DMA_DSR_BCR_BCR_M);
}

//*****************************************************************************
//
//! \brief Requests a DMA channel to start a transfer.
//!
//! \param ulChannelID is the channel ID on which to request a DMA
//! transfer.
//!
//! This function allows software to request a DMA channel to begin a
//! transfer.  This could be used for performing a memory to memory transfer,
//! or if for some reason a transfer needs to be initiated by software instead
//! of the peripheral associated with that channel.
//!
//! \note If the channel is \b UDMA_CHANNEL_SW and interrupts are used, then
//! the completion will be signaled on the uDMA dedicated interrupt.  If a
//! peripheral channel is used, then the completion will be signaled on the
//! peripheral's interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
DMAChannelRequest(unsigned long ulChannelID)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));

    //
    // Set the bit for this channel in the software DMA request register.
    //
    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DCR) |=
                  (DMA_DCR_CS | DMA_DCR_ERQ |  DMA_DCR_D_REQ | DMA_DCR_EADREQ);
}

//*****************************************************************************
//
//! \brief Gets the DMA error status.
//!
//! \param ulChannelID is the channel ID on which to request a DMA transfer.
//! \param ulErrType is the error flag type of DMA.
//! The error type can be:
//! - DMA_CONFIG_ERROR
//! - DMA_SRCBUS_ERROR 
//! - DMA_DSTBUS_ERROR
//!
//! This function returns the DMA error status.  It should be called from
//! within the uDMA error interrupt handler to determine if a uDMA error
//! occurred.
//!
//! \return Returns non-zero if a DMA error is pending.
//
//*****************************************************************************
xtBoolean 
DMAErrorStatusGet(unsigned long ulChannelID, unsigned long ulErrType)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));
    xASSERT(((ulErrType & DMA_CONFIG_ERROR) == DMA_CONFIG_ERROR) ||
            ((ulErrType & DMA_SRCBUS_ERROR) == DMA_SRCBUS_ERROR) ||
            ((ulErrType & DMA_DSTBUS_ERROR) == DMA_DSTBUS_ERROR));
			
    //
    // Return the DMA error status.
    //
    return(((g_psDMAChannelAddress[ulChannelID] + DMA_DSR_BCR) | ulErrType) 
	           ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Clears the DMA error .
//!
//! \param ulChannelID is the channel ID on which to request a DMA transfer.
//! \param ulErrType is the error flag type of DMA.
//! The error type can be:
//! - DMA_CONFIG_ERROR
//! - DMA_SRCBUS_ERROR 
//! - DMA_DSTBUS_ERROR
//!
//! This function clears a pending DMA error .  It should be called
//! from within the DMA error handler to clear the flag.
//!
//! \return None.
//
//*****************************************************************************
void
DMAErrorStatusClear(unsigned long ulChannelID, unsigned long ulErrType)
{
    //
    // Check the arguments.
    //
    xASSERT(xDMAChannelIDValid(ulChannelID));
    xASSERT(((ulErrType & DMA_CONFIG_ERROR) == DMA_CONFIG_ERROR) ||
            ((ulErrType & DMA_SRCBUS_ERROR) == DMA_SRCBUS_ERROR) ||
            ((ulErrType & DMA_DSTBUS_ERROR) == DMA_DSTBUS_ERROR));
			
    //
    // Clear the DMA error flag.
    //
    xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DSR_BCR) |= DMA_DSR_BCR_DONE;
}

//*****************************************************************************
//
//! \brief Configure the size of the source or destination data circular buffer 
//!         used by the DMA Controller .
//!
//! \param ulChannelID is the channel ID on which to request a DMA transfer.
//! \param ulModVal is the address modulo value.
//! \param ulErrType is the address type.
//! The type can be:
//! - DMA_MOD_SMODE
//! - DMA_MOD_DMODE 
//! 
//! This function Configure the size of the source or destination data  
//!         circular buffer used by the DMA Controller .
//!
//! \return None.
//
//*****************************************************************************
void
DMATransferAddressModulo(unsigned long ulChannelID, unsigned long ulModVal, 
                            unsigned long ulAddrType)
{
    xASSERT(xDMAChannelIDValid(ulChannelID));
    xASSERT((ulAddrType == DMA_MOD_SMODE) || (ulAddrType == DMA_MOD_DMODE));
    xASSERT((ulModVal >= 0) || (ulModVal < 16));
    
    if(ulAddrType == DMA_MOD_SMODE)
    {
        xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DCR) &= ~DMA_DCR_SMOD_M;
        xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DCR) |= (ulModVal << 12);  
    }
    else
    {
        xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DCR) &= ~DMA_DCR_DMOD_M;
        xHWREG(g_psDMAChannelAddress[ulChannelID] + DMA_DCR) |= (ulModVal << 8);
    }
}
