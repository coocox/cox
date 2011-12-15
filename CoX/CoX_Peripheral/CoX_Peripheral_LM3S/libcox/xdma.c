//*****************************************************************************
//
//! \file xdma.c
//! \brief Driver for the DMA Controller.
//! \version V2.1.1.0
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


//*****************************************************************************
//
// The control table used by the uDMA controller.  This table must be aligned
// to a 1024 byte boundary.
//
//*****************************************************************************
#if defined(ewarm)
#pragma data_alignment=1024
unsigned char g_pucControlTable[UDMA_CONTROL_TABLE_SIZE];
#else
unsigned char g_pucControlTable[UDMA_CONTROL_TABLE_SIZE] __attribute__ ((aligned(1024)));
#endif


static const unsigned long g_pulDMAChannelSWMap[] = 
{

    //
    // +---------+-----------------+--------+----------+
    // |7        |6                |5       |4 - 0     |
    // |---------|-----------------|--------|----------+
    // |available|primary/secondary|reserved|Channel ID|
    // |---------|-----------------|--------|----------+
    // |not:0    |primary:0        |        |          |
    // |yes:1    |secondary:1      |        |          |
    // +---------+-----------------+--------+----------+
    //
    
    //
    // channel  16  13  12 30
    //
    0xD08D8C9E,

    //
    // channel  26  23  22 17
    //
    0x9AD7D6D1,

    //
    // channel  null  29  28 27
    //
    0x00DDDC9B,

    //
    // End
    //
    (unsigned long)-1,
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

    //
    // End.
    //
    { xDMA_CHANNEL_NOT_EXIST,   xfalse },       
         
};

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
           (ulRequest == xDMA_REQUEST_UART1_RX) || 
           (ulRequest == xDMA_REQUEST_UART2_RX) || 
           (ulRequest == xDMA_REQUEST_UART2_TX) || 
           (ulRequest == xDMA_REQUEST_SPI0_RX)  ||     
           (ulRequest == xDMA_REQUEST_SPI0_TX)  ||
           (ulRequest == xDMA_REQUEST_SPI1_RX)  ||
           (ulRequest == xDMA_REQUEST_SPI0_TX)  ||
           (ulRequest == xDMA_REQUEST_IIS0_RX)  ||    
           (ulRequest == xDMA_REQUEST_IIS0_TX)        
          );
}
#endif

//*****************************************************************************
//
//! \internal
//! \brief Checks a DMA channel ID.
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
    return( (ulChannelID >= 0) && (ulChannelID < 32));
}
#endif

//*****************************************************************************
//
//! \brief Enables the DMA controller for use. 
//!
//! This function enables the DMA controller.  The DMA controller must be
//! enabled before it can be configured and used.
//! In Stellaris implement, it then set the control table base point.
//!
//! \return None.
//
//*****************************************************************************
void
xDMAEnable(void)
{
    void* pControlTable = g_pucControlTable;
    
    //
    // Check the arguments.
    //
    xASSERT(((unsigned long)pControlTable & ~0x3FF) ==
            (unsigned long)pControlTable);
    xASSERT((unsigned long)pControlTable >= 0x20000000);

    //
    // Set the master enable bit in the config register.
    //
    xHWREG(UDMA_CFG) = UDMA_CFG_MASTEN;

    //
    // Program the base address into the register.
    //
    xHWREG(UDMA_CTLBASE) = (unsigned long)pControlTable;
}


//*****************************************************************************
//
//! \internal
//! \brief Set the channel assignment status.
//!
//! \param ulChannelID is the DMA channel ID.
//! \param bAssigned is the new assignment status.
//!
//! \return None.
//
//*****************************************************************************
static void
xDMAChannelAssignmentSet(unsigned long ulChannelID, xtBoolean bAssigned)
{
    int i;
    
    xASSERT(xDMAChannelIDValid(ulChannelID));

    for(i = 0; 
        g_psDMAChannelAssignTable[i].ulChannelID != xDMA_CHANNEL_NOT_EXIST;
        i++)
    {
        if(g_psDMAChannelAssignTable[i].ulChannelID == ulChannelID)
        {
            g_psDMAChannelAssignTable[i].bChannelAssigned = bAssigned;
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
//!
//! \return Returns \b xtrue if the channel has been assigned and \b xfalse
//! if the channel is idle.
//
//*****************************************************************************
xtBoolean
xDMAChannelAssignmentGet(unsigned long ulChannelID)
{
    int i;
    
    xASSERT(xDMAChannelIDValid(ulChannelID));

    for(i = 0; 
        g_psDMAChannelAssignTable[i].ulChannelID != xDMA_CHANNEL_NOT_EXIST;
        i++)
    {
        if(g_psDMAChannelAssignTable[i].ulChannelID == ulChannelID)
        {
            return g_psDMAChannelAssignTable[i].bChannelAssigned;
        }
    }

    return xfalse;
    
}

//*****************************************************************************
//
//! \brief Dynamic assign a channel through the request.
//!
//! \param ulDMASrcRequest is the source DMA request signal. for more info 
//! refrence \ref xDMA_Request_Connections.
//! \param ulDMADestRequest is the destination DMA request signal.
//! for more info refrence \ref xDMA_Request_Connections.

//! This function dynamic allocate a channel according the DMA requests.
//! The \ref ulDMASrcRequest and \ref ulDMADestRequest can be:
//! - \ref xDMA_REQUEST_MEM
//! - \ref xDMA_REQUEST_UART0_RX
//! - \ref xDMA_REQUEST_UART0_TX
//! - \ref xDMA_REQUEST_UART1_RX
//! - \ref xDMA_REQUEST_UART1_TX
//! - \ref xDMA_REQUEST_UART2_RX
//! - \ref xDMA_REQUEST_UART2_TX
//! - \ref xDMA_REQUEST_SPI0_RX
//! - \ref xDMA_REQUEST_SPI0_TX
//! - \ref xDMA_REQUEST_SPI1_RX
//! - \ref xDMA_REQUEST_SPI1_TX
//! - \ref xDMA_REQUEST_IIS0_RX
//! - \ref xDMA_REQUEST_IIS0_TX
//!
//! \return Returns a Channel ID that dynamic assignment.
//! The channel ID can be:
//! - xDMA_CHANNEL_0
//! - xDMA_CHANNEL_1
//! - others refrence \ref xDMA_Channel_IDs
//
//*****************************************************************************
unsigned long
xDMAChannelDynamicAssign(unsigned long ulDMASrcRequest, 
                                  unsigned long ulDMADestRequest)
{
    int i, j;
    unsigned long ulChannelAssign, ulChannelID;
    
    xASSERT(xDMARequestValid(ulDMASrcRequest));
    xASSERT(xDMARequestValid(ulDMADestRequest));
    
    //
    // Stellaris DMA do not support P to P
    //
    if((ulDMASrcRequest != xDMA_REQUEST_MEM) &&
       (ulDMADestRequest != xDMA_REQUEST_MEM))
    {
        return xDMA_CHANNEL_NOT_EXIST;
    }

    if(!(ulDMASrcRequest & xDMA_REQUEST_MEM) && ulDMASrcRequest & 0x40000000)
    {
        //
        // first check the primary assignment 
        //
        ulChannelAssign = ulDMASrcRequest & 0xFF;
        
        //
        // Check the validity of this assignment
        //
        if(ulChannelAssign & 0x80)
        {
            ulChannelID = ulChannelAssign & 0x1F;
            //
            // Is assigned ?
            //
            if(xDMAChannelAssignmentGet(ulChannelID) == xfalse)
            {
                //
                // Do assign
                //
                xDMAChannelAssignmentSet(ulChannelID, xtrue);
                uDMAChannelSelectDefault(1 << ulChannelID);
                return ulChannelID;
            }  
        }

        //
        // then check the secondary assignment
        //
        ulChannelAssign = (ulDMASrcRequest >> 8) & 0xFF;
        if(ulChannelAssign & 0x80)
        {
            ulChannelID = ulChannelAssign & 0x1F;
            if(xDMAChannelAssignmentGet(ulChannelID) == xfalse)
            {
                xDMAChannelAssignmentSet(ulChannelID, xtrue);
                uDMAChannelSelectSecondary(1 << ulChannelID);
                return ulChannelID;
            }
        }
    }

    //
    // DestRequest is not Mem and DestRequest is Rx Type
    //
    if(!(ulDMADestRequest & xDMA_REQUEST_MEM) && 
       !(ulDMADestRequest & 0x40000000))
    {
        //
        // first check the primary assignment 
        //
        ulChannelAssign = ulDMADestRequest & 0xFF;
        if(ulChannelAssign & 0x80)
        {
            ulChannelID = ulChannelAssign & 0x1F;
            if(xDMAChannelAssignmentGet(ulChannelID) == xfalse)
            {
                xDMAChannelAssignmentSet(ulChannelID, xtrue);
                uDMAChannelSelectDefault(1 << ulChannelID);
                return ulChannelID;
            }     
        }

        //
        // then check the secondary assignment
        //
        ulChannelAssign = (ulDMADestRequest >> 8) & 0xFF;
        if(ulChannelAssign & 0x80)
        {
            ulChannelID = ulChannelAssign & 0x1F;
            if(xDMAChannelAssignmentGet(ulChannelID) == xfalse)
            {
                xDMAChannelAssignmentSet(ulChannelID, xtrue);
                uDMAChannelSelectSecondary(1 << ulChannelID);
                return ulChannelID;
            }
        }
    }  

    //
    // Mem to Mem type
    //
    if((ulDMASrcRequest & xDMA_REQUEST_MEM) &&
       (ulDMADestRequest & xDMA_REQUEST_MEM))
    {
        for(i = 0; g_pulDMAChannelSWMap[i] != (unsigned long)-1; i++)
        {
            for(j = 0; j < 4; j++)    
            {
                ulChannelAssign = g_pulDMAChannelSWMap[i] >> (8 * j);
                if(ulChannelAssign & 0x80)
                {
                    ulChannelID = ulChannelAssign & 0x1F;
                    if(xDMAChannelAssignmentGet(ulChannelID) == xfalse)
                    {
                        xDMAChannelAssignmentSet(ulChannelAssign, xtrue);
                        if(ulChannelAssign & 0x40)
                        {
                            uDMAChannelSelectSecondary(1 << ulChannelID);    
                        }
                        else
                        {
                            uDMAChannelSelectDefault(1 << ulChannelID);
                        }
                        return ulChannelID;
                    }
                }
            }
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
//!
//! \return None.
//
//*****************************************************************************
void
xDMAChannelDeAssign(unsigned long ulChannelID)
{
    xASSERT(xDMAChannelIDValid(ulChannelID));
    
    uDMAChannelSelectDefault(1 << ulChannelID);

    xDMAChannelAssignmentSet(ulChannelID, xfalse);
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
//!   - \b UDMA_ATTR_PRIORITY_HIGH is used to set the channel to high priority.
//!   - \b UDMA_ATTR_PRIORITY_NORMAL normal priority.
//!   .
//! .
//!
//! \return None.
//
//*****************************************************************************
void 
xDMAChannelAttributeSet(unsigned long ulChannelID, unsigned long ulAttr)
{
    xASSERT(xDMAChannelIDValid(ulChannelID));
    
    //
    // Set channel priority
    //
    if(ulAttr & xDMA_ATTR_PRIORITY_MASK == xDMA_ATTR_PRIORITY_HIGH)
    {
        xHWREG(UDMA_PRIOSET) = 1 << ulChannelID;
    }
    else
    {
        xHWREG(UDMA_PRIOCLR) = 1 << ulChannelID;
    }
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
//!   - \b UDMA_ATTR_PRIORITY_HIGH is used to set the channel to high priority.
//!   - \b UDMA_ATTR_PRIORITY_NORMAL normal priority.
//!   .
//! .
//
//*****************************************************************************
unsigned long
xDMAChannelAttributeGet(unsigned long ulChannelID)
{
    unsigned long ulAttr = xDMA_ATTR_PRIORITY_NORMAL;

    xASSERT(xDMAChannelIDValid(ulChannelID));

    //
    // Get the priority attr
    //
    if(xHWREG(UDMA_PRIOSET) & (1 << ulChannelID))
    {
        ulAttr |= xDMA_ATTR_PRIORITY_HIGH;
    }

    return ulAttr;
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
//! the source address increment, the destination address increment, the
//! arbitration size, and the use burst flag.  The choices available for each
//! of these values is described below.
//!
//! Choose the source data size from one of \b xDMA_SRC_SIZE_8, 
//! \b xDMA_SRC_SIZE_16,  \b or xDMA_SRC_SIZE_32 to select a data size 
//! of 8, 16, or 32 bits.
//!
//! Choose the destination data size from one of \b xDMA_DST_SIZE_8, 
//! \b xDMA_DST_SIZE_16,  \b or xDMA_DST_SIZE_32 to select a data size 
//! of 8, 16, or 32 bits.
//!
//! Choose the source address increment from one of \b xDMA_SRC_INC_8,
//! \b xDMA_SRC_INC_16, \b xDMA_SRC_INC_32, \b xDMA_SRC_INC_NONE, or
//! xDMA_SRC_INC(ulSrcSize) to selectan address increment of 8-bit bytes, 
//! 16-bit halfwords, 32-bit words,  select non-incrementing or 
//! source data size.
//!
//! Choose the destination address increment from one of \b xDMA_DST_INC_8,
//! \b xDMA_DST_INC_16, \b xDMA_DST_INC_32, \b xDMA_DST_INC_NONE, or
//! xDMA_DST_INC(ulSrcSize) to select an address increment of 8-bit bytes, 
//! 16-bit halfwords, 32-bit words,  select non-incrementing or 
//! destination data size.
//!
//! The arbitration size determines how many items are transferred before
//! the uDMA controller re-arbitrates for the bus.  Choose the arbitration size
//! from one of \b UDMA_ARB_1, \b UDMA_ARB_2, \b UDMA_ARB_4, \b UDMA_ARB_8,
//! through \b UDMA_ARB_1024 to select the arbitration size.
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
    unsigned long ulChannelStructIndex;
    tDMAControlTable *pCtl;
    
    xASSERT(xDMAChannelIDValid(ulChannelID));

    //
    // Get the control data structure that used ? primary or alternate?
    //
    ulChannelStructIndex = ulChannelID;
    if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
    {
        ulChannelStructIndex |= UDMA_ALT_SELECT;
    }

    //
    // Get the base address of the control table.
    //
    pCtl = (tDMAControlTable *)xHWREG(UDMA_CTLBASE);

    //
    // Get the current control word value and mask off the fields to be
    // changed, then OR in the new settings.
    //
    pCtl[ulChannelStructIndex].ulControl =
        ((pCtl[ulChannelStructIndex].ulControl &
          ~(UDMA_CHCTL_DSTINC_M |
            UDMA_CHCTL_DSTSIZE_M |
            UDMA_CHCTL_SRCINC_M |
            UDMA_CHCTL_SRCSIZE_M |
            UDMA_CHCTL_ARBSIZE_M)) |
         ulControl);
    
}


//*****************************************************************************
//
//! \brief Sets the transfer parameters for a uDMA channel control structure.
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
xDMAChannelTransferSet(unsigned long ulChannelID,
                       unsigned long ulMode, void *pvSrcAddr,
                       void *pvDstAddr,
                       unsigned long ulTransferSize)
{
    unsigned long ulChannelStructIndex;

    xASSERT(xDMAChannelIDValid(ulChannelID));
    
    //
    // Get the control data structure that used ? primary or alternate?
    //
    ulChannelStructIndex = ulChannelID;
    if(xHWREG(UDMA_ALTSET) & (1 << ulChannelID))
    {
        ulChannelStructIndex |= UDMA_ALT_SELECT;
    }

    uDMAChannelTransferSet(ulChannelStructIndex, ulMode, pvSrcAddr,
                    pvDstAddr, ulTransferSize);
    
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
//! - ulMsgParam not used, always 0..
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
xDMAChannelIntCallbackGet(unsigned long ulChannelID)
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
//! \brief DMA Interrupt Handler.
//!
//! The interrupt handler for uDMA interrupts from the memory channel. 
//! If users want to user the UART0 Callback feature, Users should promise 
//! that the uDMA Software Transfer Handle in the vector table is uDMAIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAIntHandler(void)
{
    unsigned long ulChannelStructIndex;
    tDMAControlTable *pCtl;
    int i;

    //
    // Get the base address of the control table.
    //
    pCtl = (tDMAControlTable *)xHWREG(UDMA_CTLBASE);
        
    for(i = 0; g_psDMAChannelAssignTable[i].ulChannelID != 
               xDMA_CHANNEL_NOT_EXIST;
        i++)
    {
        if(g_psDMAChannelAssignTable[i].pfnDMAChannelHandlerCallback != 0)
        {
            //
            // Get the control data structure that used ? primary or alternate?
            //
            ulChannelStructIndex = g_psDMAChannelAssignTable[i].ulChannelID;
            if(xHWREG(UDMA_ALTSET) & 
               (1 << g_psDMAChannelAssignTable[i].ulChannelID))
            {
                ulChannelStructIndex |= UDMA_ALT_SELECT;
            }
            
            if(pCtl[ulChannelStructIndex].pvDstEndAddr)
            {
                //
                // Clear Dst address to indicate the channel no long in use,
                // user must reinit the channel transfer by xDMAChannelTransferSet
                //
                pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                                
                //
                // Call Callback function
                //
                g_psDMAChannelAssignTable[i].pfnDMAChannelHandlerCallback(0, 
                                xDMA_INT_TC, 
                                0, 0);

            }
        }
    }
}

//*****************************************************************************
//
//! \brief DMA Error Interrupt Handler.
//!
//! The interrupt handler for uDMA interrupts from the memory channel. 
//! If users want to user the UART0 Callback feature, Users should promise 
//! that the uDMA Error Handle in the vector table is uDMAErrorHandler.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAErrorIntHandler(void)
{
    unsigned long ulStatus;
    unsigned long ulChannelStructIndex;
    tDMAControlTable *pCtl;
    int i;

    //
    // Check for uDMA error bit
    //
    ulStatus = uDMAErrorStatusGet();

    if(ulStatus)
    {
        //
        // clear the error
        // 
        uDMAErrorStatusClear();

        //
        // Find which channel cause the error
        //
        //
        // Get the base address of the control table.
        //
        pCtl = (tDMAControlTable *)xHWREG(UDMA_CTLBASE);

        for(i = 0; g_psDMAChannelAssignTable[i].ulChannelID != 
                   xDMA_CHANNEL_NOT_EXIST;
            i++)
        {
            if(g_psDMAChannelAssignTable[i].pfnDMAChannelHandlerCallback != 0)
            {
                //
                // Get the control data structure that used ? primary or alternate?
                //
                ulChannelStructIndex = g_psDMAChannelAssignTable[i].ulChannelID;
                if(xHWREG(UDMA_ALTSET) & 
                   (1 << g_psDMAChannelAssignTable[i].ulChannelID))
                {
                    ulChannelStructIndex |= UDMA_ALT_SELECT;
                }
                
                if(pCtl[ulChannelStructIndex].pvDstEndAddr)
                {
                    //
                    // Clear Dst address to indicate the channel no long in use,
                    // user must reinit the channel transfer by xDMAChannelTransferSet
                    //
                    pCtl[ulChannelStructIndex].pvDstEndAddr = 0;
                    
                    //
                    // Call Callback function
                    //
                    g_psDMAChannelAssignTable[i].pfnDMAChannelHandlerCallback(0, 
                                    xDMA_INT_ERROR, 
                                    0, 0);

                }
            }
        }        
    }


}


//*****************************************************************************
//
//! \brief Enables the uDMA controller for use.
//!
//! This function enables the uDMA controller.  The uDMA controller must be
//! enabled before it can be configured and used.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAEnable(void)
{
    //
    // Set the master enable bit in the config register.
    //
    xHWREG(UDMA_CFG) = UDMA_CFG_MASTEN;
}

//*****************************************************************************
//
//! \brief Disables the uDMA controller for use.
//!
//! This function disables the uDMA controller.  Once disabled, the uDMA
//! controller will not operate until re-enabled with uDMAEnable().
//!
//! \return None.
//
//*****************************************************************************
void
uDMADisable(void)
{
    //
    // Clear the master enable bit in the config register.
    //
    xHWREG(UDMA_CFG) = 0;
}

//*****************************************************************************
//
//! \brief Gets the uDMA error status.
//!
//! This function returns the uDMA error status.  It should be called from
//! within the uDMA error interrupt handler to determine if a uDMA error
//! occurred.
//!
//! \return Returns non-zero if a uDMA error is pending.
//
//*****************************************************************************
unsigned long
uDMAErrorStatusGet(void)
{
    //
    // Return the uDMA error status.
    //
    return(xHWREG(UDMA_ERRCLR));
}

//*****************************************************************************
//
//! \brief Clears the uDMA error interrupt.
//!
//! This function clears a pending uDMA error interrupt.  It should be called
//! from within the uDMA error interrupt handler to clear the interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAErrorStatusClear(void)
{
    //
    // Clear the uDMA error interrupt.
    //
    xHWREG(UDMA_ERRCLR) = 1;
}

//*****************************************************************************
//
//! \brief Enables a uDMA channel for operation.
//!
//! \param ulChannelNum is the channel number to enable.
//!
//! This function enables a specific uDMA channel for use.  This function must
//! be used to enable a channel before it can be used to perform a uDMA
//! transfer.
//!
//! When a uDMA transfer is completed, the channel will be automatically
//! disabled by the uDMA controller.  Therefore, this function should be called
//! prior to starting up any new transfer.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelEnable(unsigned long ulChannelNum)
{
    //
    // Check the arguments.
    //
    xASSERT(ulChannelNum < 32);

    //
    // Set the bit for this channel in the enable set register.
    //
    xHWREG(UDMA_ENASET) = 1 << ulChannelNum;
}

//*****************************************************************************
//
//! \brief Disables a uDMA channel for operation.
//!
//! \param ulChannelNum is the channel number to disable.
//!
//! This function disables a specific uDMA channel.  Once disabled, a channel
//! will not respond to uDMA transfer requests until re-enabled via
//! uDMAChannelEnable().
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelDisable(unsigned long ulChannelNum)
{
    //
    // Check the arguments.
    //
    xASSERT(ulChannelNum < 32);

    //
    // Set the bit for this channel in the enable clear register.
    //
    xHWREG(UDMA_ENACLR) = 1 << ulChannelNum;
}

//*****************************************************************************
//
//! \brief Checks if a uDMA channel is enabled for operation.
//!
//! \param ulChannelNum is the channel number to check.
//!
//! This function checks to see if a specific uDMA channel is enabled.  This
//! can be used to check the status of a transfer, since the channel will
//! be automatically disabled at the end of a transfer.
//!
//! \return Returns \b true if the channel is enabled, \b false if disabled.
//
//*****************************************************************************
xtBoolean
uDMAChannelIsEnabled(unsigned long ulChannelNum)
{
    //
    // Check the arguments.
    //
    xASSERT(ulChannelNum < 32);

    //
    // AND the specified channel bit with the enable register, and return the
    // result.
    //
    return((xHWREG(UDMA_ENASET) & (1 << ulChannelNum)) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Sets the base address for the channel control table.
//!
//! \param pControlTable is a pointer to the 1024 byte aligned base address
//! of the uDMA channel control table.
//!
//! This function sets the base address of the channel control table.  This
//! table resides in system memory and holds control information for each uDMA
//! channel.  The table must be aligned on a 1024 byte boundary.  The base
//! address must be set before any of the channel functions can be used.
//!
//! The size of the channel control table depends on the number of uDMA
//! channels, and which transfer modes are used.  Refer to the introductory
//! text and the microcontroller datasheet for more information about the
//! channel control table.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAControlBaseSet(void *pControlTable)
{
    //
    // Check the arguments.
    //
    xASSERT(((unsigned long)pControlTable & ~0x3FF) ==
            (unsigned long)pControlTable);
    xASSERT((unsigned long)pControlTable >= 0x20000000);

    //
    // Program the base address into the register.
    //
    xHWREG(UDMA_CTLBASE) = (unsigned long)pControlTable;
}

//*****************************************************************************
//
//! \brief Gets the base address for the channel control table.
//!
//! This function gets the base address of the channel control table.  This
//! table resides in system memory and holds control information for each uDMA
//! channel.
//!
//! \return Returns a pointer to the base address of the channel control table.
//
//*****************************************************************************
void *
uDMAControlBaseGet(void)
{
    //
    // Read the current value of the control base register, and return it to
    // the caller.
    //
    return((void *)xHWREG(UDMA_CTLBASE));
}

//*****************************************************************************
//
//! \brief Gets the base address for the channel control table alternate structures.
//!
//! This function gets the base address of the second half of the channel
//! control table that holds the alternate control structures for each channel.
//!
//! \return Returns a pointer to the base address of the second half of the
//! channel control table.
//
//*****************************************************************************
void *
uDMAControlAlternateBaseGet(void)
{
    //
    // Read the current value of the control base register, and return it to
    // the caller.
    //
    return((void *)xHWREG(UDMA_ALTBASE));
}

//*****************************************************************************
//
//! \brief Requests a uDMA channel to start a transfer.
//!
//! \param ulChannelNum is the channel number on which to request a uDMA
//! transfer.
//!
//! This function allows software to request a uDMA channel to begin a
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
uDMAChannelRequest(unsigned long ulChannelNum)
{
    //
    // Check the arguments.
    //
    xASSERT(ulChannelNum < 32);

    //
    // Set the bit for this channel in the software uDMA request register.
    //
    xHWREG(UDMA_SWREQ) = 1 << ulChannelNum;
}

//*****************************************************************************
//
//! \brief Enables attributes of a uDMA channel.
//!
//! \param ulChannelNum is the channel to configure.
//! \param ulAttr is a combination of attributes for the channel.
//!
//! The \e ulAttr parameter is the logical OR of any of the following:
//!
//! - \b UDMA_ATTR_USEBURST is used to restrict transfers to use only a burst
//!   mode.
//! - \b UDMA_ATTR_ALTSELECT is used to select the alternate control structure
//!   for this channel (it is very unlikely that this flag should be used)
//! - \b UDMA_ATTR_HIGH_PRIORITY is used to set this channel to high priority
//! - \b UDMA_ATTR_REQMASK is used to mask the hardware request signal from the
//!   peripheral for this channel.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelAttributeEnable(unsigned long ulChannelNum, unsigned long ulAttr)
{
    //
    // Check the arguments.
    //
    xASSERT(ulChannelNum < 32);
    xASSERT((ulAttr & ~(UDMA_ATTR_USEBURST | UDMA_ATTR_ALTSELECT |
                       UDMA_ATTR_HIGH_PRIORITY | UDMA_ATTR_REQMASK)) == 0);

    //
    // Set the useburst bit for this channel if set in ulConfig.
    //
    if(ulAttr & UDMA_ATTR_USEBURST)
    {
        xHWREG(UDMA_USEBURSTSET) = 1 << ulChannelNum;
    }

    //
    // Set the alternate control select bit for this channel,
    // if set in ulConfig.
    //
    if(ulAttr & UDMA_ATTR_ALTSELECT)
    {
        xHWREG(UDMA_ALTSET) = 1 << ulChannelNum;
    }

    //
    // Set the high priority bit for this channel, if set in ulConfig.
    //
    if(ulAttr & UDMA_ATTR_HIGH_PRIORITY)
    {
        xHWREG(UDMA_PRIOSET) = 1 << ulChannelNum;
    }

    //
    // Set the request mask bit for this channel, if set in ulConfig.
    //
    if(ulAttr & UDMA_ATTR_REQMASK)
    {
        xHWREG(UDMA_REQMASKSET) = 1 << ulChannelNum;
    }
}

//*****************************************************************************
//
//! \brief Disables attributes of a uDMA channel.
//!
//! \param ulChannelNum is the channel to configure.
//! \param ulAttr is a combination of attributes for the channel.
//!
//! This function is used to disable attributes of a uDMA channel.
//!
//! The \e ulAttr parameter is the logical OR of any of the following:
//!
//! - \b UDMA_ATTR_USEBURST is used to restrict transfers to use only a burst
//!   mode.
//! - \b UDMA_ATTR_ALTSELECT is used to select the alternate control structure
//!   for this channel.
//! - \b UDMA_ATTR_HIGH_PRIORITY is used to set this channel to high priority.
//! - \b UDMA_ATTR_REQMASK is used to mask the hardware request signal from the
//!   peripheral for this channel.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelAttributeDisable(unsigned long ulChannelNum, unsigned long ulAttr)
{
    //
    // Check the arguments.
    //
    xASSERT(ulChannelNum < 32);
    xASSERT((ulAttr & ~(UDMA_ATTR_USEBURST | UDMA_ATTR_ALTSELECT |
                       UDMA_ATTR_HIGH_PRIORITY | UDMA_ATTR_REQMASK)) == 0);

    //
    // Clear the useburst bit for this channel if set in ulConfig.
    //
    if(ulAttr & UDMA_ATTR_USEBURST)
    {
        xHWREG(UDMA_USEBURSTCLR) = 1 << ulChannelNum;
    }

    //
    // Clear the alternate control select bit for this channel, if set in
    // ulConfig.
    //
    if(ulAttr & UDMA_ATTR_ALTSELECT)
    {
        xHWREG(UDMA_ALTCLR) = 1 << ulChannelNum;
    }

    //
    // Clear the high priority bit for this channel, if set in ulConfig.
    //
    if(ulAttr & UDMA_ATTR_HIGH_PRIORITY)
    {
        xHWREG(UDMA_PRIOCLR) = 1 << ulChannelNum;
    }

    //
    // Clear the request mask bit for this channel, if set in ulConfig.
    //
    if(ulAttr & UDMA_ATTR_REQMASK)
    {
        xHWREG(UDMA_REQMASKCLR) = 1 << ulChannelNum;
    }
}

//*****************************************************************************
//
//! \brief Gets the enabled attributes of a uDMA channel.
//!
//! \param ulChannelNum is the channel to configure.
//!
//! This function returns a combination of flags representing the attributes of
//! the uDMA channel.
//!
//! \return Returns the logical OR of the attributes of the uDMA channel, which
//! can be any of the following:
//! - \b UDMA_ATTR_USEBURST is used to restrict transfers to use only a burst
//!   mode.
//! - \b UDMA_ATTR_ALTSELECT is used to select the alternate control structure
//!   for this channel.
//! - \b UDMA_ATTR_HIGH_PRIORITY is used to set this channel to high priority.
//! - \b UDMA_ATTR_REQMASK is used to mask the hardware request signal from the
//!   peripheral for this channel.
//
//*****************************************************************************
unsigned long
uDMAChannelAttributeGet(unsigned long ulChannelNum)
{
    unsigned long ulAttr = 0;

    //
    // Check the arguments.
    //
    xASSERT(ulChannelNum < 32);

    //
    // Check to see if useburst bit is set for this channel.
    //
    if(xHWREG(UDMA_USEBURSTSET) & (1 << ulChannelNum))
    {
        ulAttr |= UDMA_ATTR_USEBURST;
    }

    //
    // Check to see if the alternate control bit is set for this channel.
    //
    if(xHWREG(UDMA_ALTSET) & (1 << ulChannelNum))
    {
        ulAttr |= UDMA_ATTR_ALTSELECT;
    }

    //
    // Check to see if the high priority bit is set for this channel.
    //
    if(xHWREG(UDMA_PRIOSET) & (1 << ulChannelNum))
    {
        ulAttr |= UDMA_ATTR_HIGH_PRIORITY;
    }

    //
    // Check to see if the request mask bit is set for this channel.
    //
    if(xHWREG(UDMA_REQMASKSET) & (1 << ulChannelNum))
    {
        ulAttr |= UDMA_ATTR_REQMASK;
    }

    //
    // Return the configuration flags.
    //
    return(ulAttr);
}

//*****************************************************************************
//
//! \brief Sets the control parameters for a uDMA channel control structure.
//!
//! \param ulChannelStructIndex is the logical OR of the uDMA channel number
//! with \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT.
//! \param ulControl is logical OR of several control values to set the control
//! parameters for the channel.
//!
//! This function is used to set control parameters for a uDMA transfer.  These
//! are typically parameters that are not changed often.
//!
//! The \e ulChannelStructIndex parameter should be the logical OR of the
//! channel number with one of \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT to
//! choose whether the primary or alternate data structure is used.
//!
//! The \e ulControl parameter is the logical OR of five values: the data size,
//! the source address increment, the destination address increment, the
//! arbitration size, and the use burst flag.  The choices available for each
//! of these values is described below.
//!
//! Choose the data size from one of \b UDMA_SIZE_8, \b UDMA_SIZE_16, or
//! \b UDMA_SIZE_32 to select a data size of 8, 16, or 32 bits.
//!
//! Choose the source address increment from one of \b UDMA_SRC_INC_8,
//! \b UDMA_SRC_INC_16, \b UDMA_SRC_INC_32, or \b UDMA_SRC_INC_NONE to select
//! an address increment of 8-bit bytes, 16-bit halfwords, 32-bit words, or
//! to select non-incrementing.
//!
//! Choose the destination address increment from one of \b UDMA_DST_INC_8,
//! \b UDMA_DST_INC_16, \b UDMA_DST_INC_32, or \b UDMA_DST_INC_NONE to select
//! an address increment of 8-bit bytes, 16-bit halfwords, 32-bit words, or
//! to select non-incrementing.
//!
//! The arbitration size determines how many items are transferred before
//! the uDMA controller re-arbitrates for the bus.  Choose the arbitration size
//! from one of \b UDMA_ARB_1, \b UDMA_ARB_2, \b UDMA_ARB_4, \b UDMA_ARB_8,
//! through \b UDMA_ARB_1024 to select the arbitration size from 1 to 1024
//! items, in powers of 2.
//!
//! The value \b UDMA_NEXT_USEBURST is used to force the channel to only
//! respond to burst requests at the tail end of a scatter-gather transfer.
//!
//! \note The address increment cannot be smaller than the data size.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelControlSet(unsigned long ulChannelStructIndex,
                      unsigned long ulControl)
{
    tDMAControlTable *pCtl;

    //
    // Check the arguments.
    //
    xASSERT(ulChannelStructIndex < 64);
    xASSERT(xHWREG(UDMA_CTLBASE) != 0);

    //
    // Get the base address of the control table.
    //
    pCtl = (tDMAControlTable *)xHWREG(UDMA_CTLBASE);

    //
    // Get the current control word value and mask off the fields to be
    // changed, then OR in the new settings.
    //
    pCtl[ulChannelStructIndex].ulControl =
        ((pCtl[ulChannelStructIndex].ulControl &
          ~(UDMA_CHCTL_DSTINC_M |
            UDMA_CHCTL_DSTSIZE_M |
            UDMA_CHCTL_SRCINC_M |
            UDMA_CHCTL_SRCSIZE_M |
            UDMA_CHCTL_ARBSIZE_M |
            UDMA_CHCTL_NXTUSEBURST)) |
         ulControl);
}

//*****************************************************************************
//
//! \brief Sets the transfer parameters for a uDMA channel control structure.
//!
//! \param ulChannelStructIndex is the logical OR of the uDMA channel number
//! with either \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT.
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
//! - \b UDMA_MODE_STOP stops the uDMA transfer.  The controller sets the mode
//!   to this value at the end of a transfer.
//! - \b UDMA_MODE_BASIC to perform a basic transfer based on request.
//! - \b UDMA_MODE_AUTO to perform a transfer that will always complete once
//!   started even if request is removed.
//! - \b UDMA_MODE_PINGPONG to set up a transfer that switches between the
//!   primary and alternate control structures for the channel.  This allows
//!   use of ping-pong buffering for uDMA transfers.
//! - \b UDMA_MODE_MEM_SCATTER_GATHER to set up a memory scatter-gather
//!   transfer.
//! - \b UDMA_MODE_PER_SCATTER_GATHER to set up a peripheral scatter-gather
//!   transfer.
//!
//! The \e pvSrcAddr and \e pvDstAddr parameters are pointers to the first
//! location of the data to be transferred.  These addresses should be aligned
//! according to the item size.  The compiler will take care of this if the
//! pointers are pointing to storage of the appropriate data type.
//!
//! The \e ulTransferSize parameter is the number of data items, not the number
//! of bytes.
//!
//! The two scatter/gather modes, memory and peripheral, are actually different
//! depending on whether the primary or alternate control structure is
//! selected.  This function will look for the \b UDMA_PRI_SELECT and
//! \b UDMA_ALT_SELECT flag along with the channel number and will set the
//! scatter/gather mode as appropriate for the primary or alternate control
//! structure.
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
//! disabled, or the uDMAChannelModeGet() returns \b UDMA_MODE_STOP.  For
//! PINGPONG or one of the SCATTER_GATHER modes, it is safe to modify the
//! primary or alternate control structure only when the other is being used.
//! The uDMAChannelModeGet() function will return \b UDMA_MODE_STOP when a
//! channel control structure is inactive and safe to modify.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelTransferSet(unsigned long ulChannelStructIndex,
                       unsigned long ulMode, void *pvSrcAddr, void *pvDstAddr,
                       unsigned long ulTransferSize)
{
    tDMAControlTable *pControlTable;
    unsigned long ulControl;
    unsigned long ulInc;
    unsigned long ulBufferBytes;

    //
    // Check the arguments.
    //
    xASSERT(ulChannelStructIndex < 64);
    xASSERT(xHWREG(UDMA_CTLBASE) != 0);
    xASSERT(ulMode <= UDMA_MODE_PER_SCATTER_GATHER);
    xASSERT((unsigned long)pvSrcAddr >= 0x20000000);
    xASSERT((unsigned long)pvDstAddr >= 0x20000000);
    xASSERT((ulTransferSize != 0) && (ulTransferSize <= 1024));

    //
    // Get the base address of the control table.
    //
    pControlTable = (tDMAControlTable *)xHWREG(UDMA_CTLBASE);

    //
    // Get the current control word value and mask off the mode and size
    // fields.
    //
    ulControl = (pControlTable[ulChannelStructIndex].ulControl &
                 ~(UDMA_CHCTL_XFERSIZE_M | UDMA_CHCTL_XFERMODE_M));

    //
    // Adjust the mode if the alt control structure is selected.
    //
    if(ulChannelStructIndex & UDMA_ALT_SELECT)
    {
        if((ulMode == UDMA_MODE_MEM_SCATTER_GATHER) ||
           (ulMode == UDMA_MODE_PER_SCATTER_GATHER))
        {
            ulMode |= UDMA_MODE_ALT_SELECT;
        }
    }

    //
    // Set the transfer size and mode in the control word (but don't write the
    // control word yet as it could kick off a transfer).
    //
    ulControl |= ulMode | ((ulTransferSize - 1) << 4);

    //
    // Get the address increment value for the source, from the control word.
    //
    ulInc = (ulControl & UDMA_CHCTL_SRCINC_M);

    //
    // Compute the ending source address of the transfer.  If the source
    // increment is set to none, then the ending address is the same as the
    // beginning.
    //
    if(ulInc != UDMA_SRC_INC_NONE)
    {
        ulInc = ulInc >> 26;
        ulBufferBytes = ulTransferSize << ulInc;
        pvSrcAddr = (void *)((unsigned long)pvSrcAddr + ulBufferBytes - 1);
    }

    //
    // Load the source ending address into the control block.
    //
    pControlTable[ulChannelStructIndex].pvSrcEndAddr = pvSrcAddr;

    //
    // Get the address increment value for the destination, from the control
    // word.
    //
    ulInc = ulControl & UDMA_CHCTL_DSTINC_M;

    //
    // Compute the ending destination address of the transfer.  If the
    // destination increment is set to none, then the ending address is the
    // same as the beginning.
    //
    if(ulInc != UDMA_DST_INC_NONE)
    {
        //
        // There is a special case if this is setting up a scatter-gather
        // transfer.  The destination pointer needs to point to the end of
        // the alternate structure for this channel instead of calculating
        // the end of the buffer in the normal way.
        //
        if((ulMode == UDMA_MODE_MEM_SCATTER_GATHER) ||
           (ulMode == UDMA_MODE_PER_SCATTER_GATHER))
        {
            pvDstAddr =
                (void *)&pControlTable[ulChannelStructIndex |
                                       UDMA_ALT_SELECT].ulSpare;
        }
        //
        // Not a scatter-gather transfer, calculate end pointer normally.
        //
        else
        {
            ulInc = ulInc >> 30;
            ulBufferBytes = ulTransferSize << ulInc;
            pvDstAddr = (void *)((unsigned long)pvDstAddr + ulBufferBytes - 1);
        }
    }

    //
    // Load the destination ending address into the control block.
    //
    pControlTable[ulChannelStructIndex].pvDstEndAddr = pvDstAddr;

    //
    // Write the new control word value.
    //
    pControlTable[ulChannelStructIndex].ulControl = ulControl;
}

//*****************************************************************************
//
//! \brief Configures a uDMA channel for scatter-gather mode.
//!
//! \param ulChannelNum is the uDMA channel number.
//! \param ulTaskCount is the number of scatter-gather tasks to execute.
//! \param pvTaskList is a pointer to the beginning of the scatter-gather
//! task list.
//! \param ulIsPeriphSG is a flag to indicate it is a peripheral scatter-gather
//! transfer (else it will be memory scatter-gather transfer)
//!
//! This function is used to configure a channel for scatter-gather mode.
//! The caller must have already set up a task list, and pass a pointer to
//! the start of the task list as the \e pvTaskList parameter.  The
//! \e ulTaskCount parameter is the count of tasks in the task list, not the
//! size of the task list.  The flag \e bIsPeriphSG should be used to indicate
//! if the scatter-gather should be configured for a peripheral or memory
//! scatter-gather operation.
//!
//! \sa uDMATaskStructEntry
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelScatterGatherSet(unsigned long ulChannelNum, unsigned ulTaskCount,
                            void *pvTaskList, unsigned long ulIsPeriphSG)
{
    tDMAControlTable *pControlTable;
    tDMAControlTable *pTaskTable;

    //
    // Check the parameters
    //
    xASSERT(ulChannelNum < 32);
    xASSERT(xHWREG(UDMA_CTLBASE) != 0);
    xASSERT(pvTaskList != 0);
    xASSERT(ulTaskCount <= 1024);
    xASSERT(ulTaskCount != 0);

    //
    // Get the base address of the control table.
    //
    pControlTable = (tDMAControlTable *)xHWREG(UDMA_CTLBASE);

    //
    // Get a handy pointer to the task list
    //
    pTaskTable = (tDMAControlTable *)pvTaskList;

    //
    // Compute the ending address for the source pointer.  This will be the
    // last element of the last task in the task table
    //
    pControlTable[ulChannelNum].pvSrcEndAddr =
        &pTaskTable[ulTaskCount - 1].ulSpare;

    //
    // Compute the ending address for the destination pointer.  This will be
    // the end of the alternate structure for this channel.
    //
    pControlTable[ulChannelNum].pvDstEndAddr =
        &pControlTable[ulChannelNum | UDMA_ALT_SELECT].ulSpare;

    //
    // Compute the control word.  Most configurable items are fixed for
    // scatter-gather.  Item and increment sizes are all 32-bit and arb
    // size must be 4.  The count is the number of items in the task list
    // times 4 (4 words per task).
    //
    pControlTable[ulChannelNum].ulControl =
        (UDMA_CHCTL_DSTINC_32 | UDMA_CHCTL_DSTSIZE_32 |
         UDMA_CHCTL_SRCINC_32 | UDMA_CHCTL_SRCSIZE_32 |
         UDMA_CHCTL_ARBSIZE_4 |
         (((ulTaskCount * 4) - 1) << UDMA_CHCTL_XFERSIZE_S) |
         (ulIsPeriphSG ? UDMA_CHCTL_XFERMODE_PER_SG :
          UDMA_CHCTL_XFERMODE_MEM_SG));
}

//*****************************************************************************
//
//! \brief Gets the current transfer size for a uDMA channel control structure.
//!
//! \param ulChannelStructIndex is the logical OR of the uDMA channel number
//! with either \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT.
//!
//! This function is used to get the uDMA transfer size for a channel.  The
//! transfer size is the number of items to transfer, where the size of an item
//! might be 8, 16, or 32 bits.  If a partial transfer has already occurred,
//! then the number of remaining items will be returned.  If the transfer is
//! complete, then 0 will be returned.
//!
//! \return Returns the number of items remaining to transfer.
//
//*****************************************************************************
unsigned long
uDMAChannelSizeGet(unsigned long ulChannelStructIndex)
{
    tDMAControlTable *pControlTable;
    unsigned long ulControl;

    //
    // Check the arguments.
    //
    xASSERT(ulChannelStructIndex < 64);
    xASSERT(xHWREG(UDMA_CTLBASE) != 0);

    //
    // Get the base address of the control table.
    //
    pControlTable = (tDMAControlTable *)xHWREG(UDMA_CTLBASE);

    //
    // Get the current control word value and mask off all but the size field
    // and the mode field.
    //
    ulControl = (pControlTable[ulChannelStructIndex].ulControl &
                 (UDMA_CHCTL_XFERSIZE_M | UDMA_CHCTL_XFERMODE_M));

    //
    // If the size field and mode field are 0 then the transfer is finished
    // and there are no more items to transfer
    //
    if(ulControl == 0)
    {
        return(0);
    }

    //
    // Otherwise, if either the size field or more field is non-zero, then
    // not all the items have been transferred.
    //
    else
    {
        //
        // Shift the size field and add one, then return to user.
        //
        return((ulControl >> 4) + 1);
    }
}

//*****************************************************************************
//
//! \brief Gets the transfer mode for a uDMA channel control structure.
//!
//! \param ulChannelStructIndex is the logical OR of the uDMA channel number
//! with either \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT.
//!
//! This function is used to get the transfer mode for the uDMA channel.  It
//! can be used to query the status of a transfer on a channel.  When the
//! transfer is complete the mode will be \b UDMA_MODE_STOP.
//!
//! \return Returns the transfer mode of the specified channel and control
//! structure, which will be one of the following values: \b UDMA_MODE_STOP,
//! \b UDMA_MODE_BASIC, \b UDMA_MODE_AUTO, \b UDMA_MODE_PINGPONG,
//! \b UDMA_MODE_MEM_SCATTER_GATHER, or \b UDMA_MODE_PER_SCATTER_GATHER.
//
//*****************************************************************************
unsigned long
uDMAChannelModeGet(unsigned long ulChannelStructIndex)
{
    tDMAControlTable *pControlTable;
    unsigned long ulControl;

    //
    // Check the arguments.
    //
    xASSERT(ulChannelStructIndex < 64);
    xASSERT(xHWREG(UDMA_CTLBASE) != 0);

    //
    // Get the base address of the control table.
    //
    pControlTable = (tDMAControlTable *)xHWREG(UDMA_CTLBASE);

    //
    // Get the current control word value and mask off all but the mode field.
    //
    ulControl = (pControlTable[ulChannelStructIndex].ulControl &
                 UDMA_CHCTL_XFERMODE_M);

    //
    // Check if scatter/gather mode, and if so, mask off the alt bit.
    //
    if(((ulControl & ~UDMA_MODE_ALT_SELECT) == UDMA_MODE_MEM_SCATTER_GATHER) ||
       ((ulControl & ~UDMA_MODE_ALT_SELECT) == UDMA_MODE_PER_SCATTER_GATHER))
    {
        ulControl &= ~UDMA_MODE_ALT_SELECT;
    }

    //
    // Return the mode to the caller.
    //
    return(ulControl);
}

//*****************************************************************************
//
//! \brief Selects the secondary peripheral for a set of uDMA channels.
//!
//! \param ulSecPeriphs is the logical or of the uDMA channels for which to
//! use the secondary peripheral, instead of the default peripheral.
//!
//! This function is used to select the secondary peripheral assignment for
//! a set of uDMA channels.  By selecting the secondary peripheral assignment
//! for a channel, the default peripheral assignment is no longer available
//! for that channel.
//!
//! The parameter \e ulSecPeriphs can be the logical OR of any of the
//! following macros.  If one of the macros below is in the list passed
//! to this function, then the secondary peripheral (marked as \b _SEC_)
//! will be selected.
//!
//! - \b UDMA_DEF_USBEP1RX_SEC_UART2RX
//! - \b UDMA_DEF_USBEP1TX_SEC_UART2TX
//! - \b UDMA_DEF_USBEP2RX_SEC_TMR3A
//! - \b UDMA_DEF_USBEP2TX_SEC_TMR3B
//! - \b UDMA_DEF_USBEP3RX_SEC_TMR2A
//! - \b UDMA_DEF_USBEP3TX_SEC_TMR2B
//! - \b UDMA_DEF_ETH0RX_SEC_TMR2A
//! - \b UDMA_DEF_ETH0TX_SEC_TMR2B
//! - \b UDMA_DEF_UART0RX_SEC_UART1RX
//! - \b UDMA_DEF_UART0TX_SEC_UART1TX
//! - \b UDMA_DEF_SSI0RX_SEC_SSI1RX
//! - \b UDMA_DEF_SSI0TX_SEC_SSI1TX
//! - \b UDMA_DEF_RESERVED_SEC_UART2RX
//! - \b UDMA_DEF_RESERVED_SEC_UART2TX
//! - \b UDMA_DEF_ADC00_SEC_TMR2A
//! - \b UDMA_DEF_ADC01_SEC_TMR2B
//! - \b UDMA_DEF_ADC02_SEC_RESERVED
//! - \b UDMA_DEF_ADC03_SEC_RESERVED
//! - \b UDMA_DEF_TMR0A_SEC_TMR1A
//! - \b UDMA_DEF_TMR0B_SEC_TMR1B
//! - \b UDMA_DEF_TMR1A_SEC_EPI0RX
//! - \b UDMA_DEF_TMR1B_SEC_EPI0TX
//! - \b UDMA_DEF_UART1RX_SEC_RESERVED
//! - \b UDMA_DEF_UART1TX_SEC_RESERVED
//! - \b UDMA_DEF_SSI1RX_SEC_ADC10
//! - \b UDMA_DEF_SSI1TX_SEC_ADC11
//! - \b UDMA_DEF_RESERVED_SEC_ADC12
//! - \b UDMA_DEF_RESERVED_SEC_ADC13
//! - \b UDMA_DEF_I2S0RX_SEC_RESERVED
//! - \b UDMA_DEF_I2S0TX_SEC_RESERVED
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelSelectSecondary(unsigned long ulSecPeriphs)
{
    //
    // Select the secondary peripheral for the specified channels.
    //
    xHWREG(UDMA_CHASGN) |= ulSecPeriphs;
}

//*****************************************************************************
//
//! \brief Selects the default peripheral for a set of uDMA channels.
//!
//! \param ulDefPeriphs is the logical or of the uDMA channels for which to
//! use the default peripheral, instead of the secondary peripheral.
//!
//! This function is used to select the default peripheral assignment for
//! a set of uDMA channels.
//!
//! The parameter \e ulDefPeriphs can be the logical OR of any of the
//! following macros.  If one of the macros below is in the list passed
//! to this function, then the default peripheral (marked as \b _DEF_)
//! will be selected.
//!
//! - \b UDMA_DEF_USBEP1RX_SEC_UART2RX
//! - \b UDMA_DEF_USBEP1TX_SEC_UART2TX
//! - \b UDMA_DEF_USBEP2RX_SEC_TMR3A
//! - \b UDMA_DEF_USBEP2TX_SEC_TMR3B
//! - \b UDMA_DEF_USBEP3RX_SEC_TMR2A
//! - \b UDMA_DEF_USBEP3TX_SEC_TMR2B
//! - \b UDMA_DEF_ETH0RX_SEC_TMR2A
//! - \b UDMA_DEF_ETH0TX_SEC_TMR2B
//! - \b UDMA_DEF_UART0RX_SEC_UART1RX
//! - \b UDMA_DEF_UART0TX_SEC_UART1TX
//! - \b UDMA_DEF_SSI0RX_SEC_SSI1RX
//! - \b UDMA_DEF_SSI0TX_SEC_SSI1TX
//! - \b UDMA_DEF_RESERVED_SEC_UART2RX
//! - \b UDMA_DEF_RESERVED_SEC_UART2TX
//! - \b UDMA_DEF_ADC00_SEC_TMR2A
//! - \b UDMA_DEF_ADC01_SEC_TMR2B
//! - \b UDMA_DEF_ADC02_SEC_RESERVED
//! - \b UDMA_DEF_ADC03_SEC_RESERVED
//! - \b UDMA_DEF_TMR0A_SEC_TMR1A
//! - \b UDMA_DEF_TMR0B_SEC_TMR1B
//! - \b UDMA_DEF_TMR1A_SEC_EPI0RX
//! - \b UDMA_DEF_TMR1B_SEC_EPI0TX
//! - \b UDMA_DEF_UART1RX_SEC_RESERVED
//! - \b UDMA_DEF_UART1TX_SEC_RESERVED
//! - \b UDMA_DEF_SSI1RX_SEC_ADC10
//! - \b UDMA_DEF_SSI1TX_SEC_ADC11
//! - \b UDMA_DEF_RESERVED_SEC_ADC12
//! - \b UDMA_DEF_RESERVED_SEC_ADC13
//! - \b UDMA_DEF_I2S0RX_SEC_RESERVED
//! - \b UDMA_DEF_I2S0TX_SEC_RESERVED
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelSelectDefault(unsigned long ulDefPeriphs)
{
    //
    // Select the default peripheral for the specified channels.
    //
    xHWREG(UDMA_CHASGN) &= ~ulDefPeriphs;
}



