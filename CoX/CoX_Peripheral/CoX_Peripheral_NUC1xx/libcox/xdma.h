//*****************************************************************************
//
//! \file xdma.h
//! \brief Defines and Macros for DMA API.
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

#ifndef __xDMA_H__
#define __xDMA_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup DMA
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xDMA
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xDMA_Config
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xDMA_Channel_IDs xDMA Channel IDs
//! \brief Values show channel IDs
//! \n
//! \section xDMA_Channel_IDs_Section 1. Where to use this group
//! Values that can be passed to all the API in xdma.c 
//! as the ulChannel parameter. 
//! \n
//! \section xDMA_Channel_IDs_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +-------------------------+----------------+----------------+
//! |xDMA Channel IDs         |       CoX      |     NUC1xx     |
//! |-------------------------|----------------|----------------|
//! |xDMA_CHANNEL_$x$         |  Non-Mandatory | xDMA_CHANNEL_0 |
//! |                         |                |     ......     |
//! |                         |                | xDMA_CHANNEL_8 |
//! |-------------------------|----------------|----------------|
//! |xDMA_CHANNEL_COUNT       |    Mandatory   |        Y       |
//! |-------------------------|----------------|----------------|
//! |xDMA_CHANNEL_NOT_EXIST   |    Mandatory   |        Y       |
//! |-------------------------|----------------|----------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xDMA_CHANNEL_COUNT      32
#define xDMA_CHANNEL_NOT_EXIST  0xFFFFFFFF 

#define xDMA_CHANNEL_0          0
#define xDMA_CHANNEL_1          1
#define xDMA_CHANNEL_2          2
#define xDMA_CHANNEL_3          3
#define xDMA_CHANNEL_4          4
#define xDMA_CHANNEL_5          5
#define xDMA_CHANNEL_6          6
#define xDMA_CHANNEL_7          7
#define xDMA_CHANNEL_8          8
#define xDMA_CHANNEL_9          9
#define xDMA_CHANNEL_10         10
#define xDMA_CHANNEL_11         11
#define xDMA_CHANNEL_12         12
#define xDMA_CHANNEL_13         13
#define xDMA_CHANNEL_14         14
#define xDMA_CHANNEL_15         15
#define xDMA_CHANNEL_16         16
#define xDMA_CHANNEL_17         17
#define xDMA_CHANNEL_18         18
#define xDMA_CHANNEL_19         19
#define xDMA_CHANNEL_20         20
#define xDMA_CHANNEL_21         21
#define xDMA_CHANNEL_22         22
#define xDMA_CHANNEL_23         23
#define xDMA_CHANNEL_24         24
#define xDMA_CHANNEL_25         25
#define xDMA_CHANNEL_26         26
#define xDMA_CHANNEL_27         27
#define xDMA_CHANNEL_28         28
#define xDMA_CHANNEL_29         29
#define xDMA_CHANNEL_30         30
#define xDMA_CHANNEL_31         31

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xDMA_Request_Connections  xDMA Request Connections
//! \brief Values show request connecttions
//! \n
//! \section xDMA_Request_Connections_Section 1. Where to use this group
//! Values that can be passed to XPDMAChannelDynamicAssign() 
//! as the ulDMASrcRequest and ulDMADestRequest parameter. 
//! \n
//! \section xDMA_Request_Connections_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +-------------------------+----------------+----------------------+
//! |xDMA Request Connections |       CoX      |        NUC1xx        |
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_NOT_EXIST   |    Mandatory   |           Y          |
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_MEM         |    Mandatory   |           Y          |
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_UART$x$_RX  |  Non-Mandatory | xDMA_REQUEST_UART0_RX|
//! |                         |                | xDMA_REQUEST_UART1_RX|
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_SPI$x$_TX   |  Non-Mandatory | xDMA_REQUEST_SPI0_TX |
//! |                         |                | xDMA_REQUEST_SPI1_TX |
//! |                         |                | xDMA_REQUEST_SPI2_TX |
//! |                         |                | xDMA_REQUEST_SPI3_TX |
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_IIS$x$_TX   |  Non-Mandatory | xDMA_REQUEST_IIS0_TX |
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_IIS$x$_RX   |  Non-Mandatory | xDMA_REQUEST_IIS0_RX |
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_SPI$x$_RX   |  Non-Mandatory | xDMA_REQUEST_SPI0_RX |
//! |                         |                | xDMA_REQUEST_SPI1_RX |
//! |                         |                | xDMA_REQUEST_SPI2_RX |
//! |                         |                | xDMA_REQUEST_SPI3_RX |
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_UART$x$_RX  |  Non-Mandatory | xDMA_REQUEST_UART0_TX|
//! |                         |                | xDMA_REQUEST_UART1_TX|
//! |-------------------------|----------------|----------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************


#define xDMA_REQUEST_NOT_EXIST  PDMA_REQUEST_NOT_EXIST
#define xDMA_REQUEST_MEM        PDMA_REQUEST_MEM

#define xDMA_REQUEST_UART0_RX   PDMA_REQUEST_UART0_RX
#define xDMA_REQUEST_UART0_TX   PDMA_REQUEST_UART0_TX

#define xDMA_REQUEST_UART1_RX   PDMA_REQUEST_UART1_RX
#define xDMA_REQUEST_UART1_TX   PDMA_REQUEST_UART1_TX

#define xDMA_REQUEST_SPI0_RX    PDMA_REQUEST_SPI0_RX
#define xDMA_REQUEST_SPI0_TX    PDMA_REQUEST_SPI0_TX

#define xDMA_REQUEST_SPI1_RX    PDMA_REQUEST_SPI1_RX
#define xDMA_REQUEST_SPI1_TX    PDMA_REQUEST_SPI1_TX

#define xDMA_REQUEST_SPI2_RX    PDMA_REQUEST_SPI2_RX
#define xDMA_REQUEST_SPI2_TX    PDMA_REQUEST_SPI2_TX

#define xDMA_REQUEST_SPI3_RX    PDMA_REQUEST_SPI3_RX
#define xDMA_REQUEST_SPI3_TX    PDMA_REQUEST_SPI3_TX

#define xDMA_REQUEST_IIS0_RX    PDMA_REQUEST_IIS0_RX
#define xDMA_REQUEST_IIS0_TX    PDMA_REQUEST_IIS0_TX

#define xDMA_REQUEST_ADC_RX     PDMA_REQUEST_ADC_RX

// ADC, timer will be added in the further

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xDMA_Ints xDMA Interrupts
//! \brief Values show xDMA interrupt
//! \n
//! \section xDMA_Ints_Section 1. Where to use this group
//! Values that can be passed to XPDMAChannelIntEnable(),
//! XPDMAChannelIntDisable(), XPDMAChannelIntFlagGet(), XPDMAChannelIntFlagClear()
//! as the ulIntFlags  parameter. 
//! \n
//! \section xDMA_Ints_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +-------------------------+----------------+----------------+
//! |xDMA interrupt source    |       CoX      |     NUC1xx     |
//! |-------------------------|----------------|----------------|
//! |xDMA_INT_TC              |    Mandatory   |        Y       |
//! |-------------------------|----------------|----------------|
//! |xDMA_INT_ERROR           |    Mandatory   |        Y       |
//! |-------------------------|----------------|----------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Transfer complete.
//
#define xDMA_INT_TC             PDMA_EVENT_TC

//
//! Error occurs when DMA channel transfer.
//
#define xDMA_INT_ERROR          PDMA_EVENT_ERROR

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xDMA_Event_Flags xDMA Event Flags
//! \brief Values show xDMA Event Flags
//! \n
//! \section xDMA_Event_Flags_Section 1. Where to use this group
//! Uart Event/Error Flag, Used by IntHandle's Event Callback Function as 
//! ulMsgParam parameter. User Callback function can use this to detect what 
//! event happened.
//! \n
//! \section xDMA_Event_Flags_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +-------------------------+----------------+----------------+
//! |xDMA event flag          |       CoX      |     NUC1xx     |
//! |-------------------------|----------------|----------------|
//! |xDMA_EVENT_TC            |    Mandatory   |        Y       |
//! |-------------------------|----------------|----------------|
//! |xDMA_EVENT_ERROR         |    Mandatory   |        Y       |
//! |-------------------------|----------------|----------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Transfer complete.
//
#define xDMA_EVENT_TC           xDMA_INT_TC

//
//! Error occurs when DMA channel transfer.
//
#define xDMA_EVENT_ERROR        xDMA_INT_ERROR

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup xDMA_Channel_Attr xDMA Channel Attribution
//! \brief Values show xDMA Channel Attribution
//! \n
//! \section xDMA_Event_Flags_Section 1. Where to use this group
//! None
//! \n
//! \section xDMA_Event_Flags_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +-------------------------+----------------+----------------+
//! |xDMA channel Attr        |       CoX      |     NUC1xx     |
//! |-------------------------|----------------|----------------|
//! |xDMA_ATTR_PRIORITY_NORMAL|  Non-Mandatory |        N       |
//! |-------------------------|----------------|----------------|
//! |xDMA_ATTR_PRIORITY_HIGH  |  Non-Mandatory |        N       |
//! |-------------------------|----------------|----------------|
//! |xDMA_ATTR_PRIORITY_MASK  |  Non-Mandatory |        N       |
//! |-------------------------|----------------|----------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xDMA_ATTR_PRIORITY_NORMAL                                      
#define xDMA_ATTR_PRIORITY_HIGH 
#define xDMA_ATTR_PRIORITY_MASK 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xDMA_Channel_Control_Config xDMA Channel Control Configure
//! \brief Values show xDMA Channel Control Configuration
//! \n
//! \section xDMA_Channel_Control_Config_Section 1. Where to use this group
//! Values that can be passed to PDMAChannelControlSet()
//! as the ulControl parameter. 
//! \n
//! \section xDMA_Channel_Control_Config_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +-------------------------+----------------+-----------------+
//! |xDMA Control Config      |       CoX      |     NUC1xx      |
//! |-------------------------|----------------|-----------------|
//! |xDMA_DST_INC_$x$         |  Non-Mandatory | xDMA_DST_INC_8  |
//! |                         |                | xDMA_DST_INC_16 |
//! |                         |                | xDMA_DST_INC_32 |
//! |                         |                |xDMA_DST_INC_NONE|
//! |-------------------------|----------------|-----------------|
//! |xDMA_SRC_INC_$x$         |  Non-Mandatory | xDMA_SRC_INC_8  |
//! |                         |                | xDMA_SRC_INC_16 |
//! |                         |                | xDMA_SRC_INC_32 |
//! |                         |                |xDMA_SRC_INC_NONE|
//! |-------------------------|----------------|-----------------|
//! |xDMA_DST_SIZE_$x$        |  Non-Mandatory | xDMA_DST_SIZE_8 |
//! |                         |                |xDMA_DST_SIZE_16 |
//! |                         |                |xDMA_DST_SIZE_32 |
//! |-------------------------|----------------|-----------------|
//! |xDMA_SRC_SIZE_$x$        |  Non-Mandatory | xDMA_SRC_SIZE_8 |
//! |                         |                |xDMA_SRC_SIZE_16 |
//! |                         |                |xDMA_SRC_SIZE_32 |
//! |-------------------------|----------------|-----------------|
//! |xDMA_ARB_$x$             |  Non-Mandatory |        N        |
//! |-------------------------|----------------|-----------------|
//! |xDMA_MODE_BASIC          |  Non-Mandatory |        N        |
//! |-------------------------|----------------|-----------------|
//! |xDMA_MODE_AUTO           |  Non-Mandatory |        N        |
//! |-------------------------|----------------|-----------------|
//! \endverbatim
//! @{
//
//*****************************************************************************
#define xDMA_DST_INC_8          PDMA_DST_DIR_INC
#define xDMA_DST_INC_16         PDMA_DST_DIR_INC
#define xDMA_DST_INC_32         PDMA_DST_DIR_INC
#define xDMA_DST_INC_NONE       PDMA_DST_DIR_FIXED
#define xDMA_DST_INC(ulDstSize) 

#define xDMA_SRC_INC_8          PDMA_SRC_DIR_INC
#define xDMA_SRC_INC_16         PDMA_SRC_DIR_INC
#define xDMA_SRC_INC_32         PDMA_SRC_DIR_INC
#define xDMA_SRC_INC_NONE       PDMA_SRC_DIR_FIXED
#define xDMA_SRC_INC(ulSrcSize) 

#define xDMA_SRC_SIZE_8         PDMA_WIDTH_8BIT
#define xDMA_SRC_SIZE_16        PDMA_WIDTH_16BIT
#define xDMA_SRC_SIZE_32        PDMA_WIDTH_32BIT

#define xDMA_DST_SIZE_8         PDMA_WIDTH_8BIT
#define xDMA_DST_SIZE_16        PDMA_WIDTH_16BIT
#define xDMA_DST_SIZE_32        PDMA_WIDTH_32BIT

//
// The unit is not a byte, is a item
//
#define xDMA_ARB_1              
#define xDMA_ARB_2              
#define xDMA_ARB_4              
#define xDMA_ARB_8              
#define xDMA_ARB_16             
#define xDMA_ARB_32             
#define xDMA_ARB_64             
#define xDMA_ARB_128            
#define xDMA_ARB_256            
#define xDMA_ARB_512            
#define xDMA_ARB_1024           

#define xDMA_MODE_BASIC         
#define xDMA_MODE_AUTO          

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xDMA_Exported_APIs DMA API 
//! \brief xDMA API Reference
//!
//! \section xDMA_Exported_APIs_Port CoX Port Details
//! \verbatim
//! +---------------------------+----------------+--------+
//! |xDMA API                   |       CoX      | NUC1xx |
//! |---------------------------|----------------|--------|
//! |xDMAEnable                 |    Mandatory   |    Y   |
//! |---------------------------|----------------|--------|
//! |xDMADisable                |    Mandatory   |    Y   |
//! |---------------------------|----------------|--------|
//! |xDMAChannelDynamicAssign   |    Mandatory   |    Y   |
//! |---------------------------|----------------|--------|
//! |xDMAChannelAssignmentGet   |    Mandatory   |    Y   |
//! |---------------------------|----------------|--------|
//! |xDMAChannelDeAssign        |    Mandatory   |    Y   |
//! |---------------------------|----------------|--------|
//! |xDMAChannelAttributeSet    |  Non-Mandatory |    N   |
//! |---------------------------|----------------|--------|
//! |xDMAChannelAttributeGet    |  Non-Mandatory |    N   |
//! |---------------------------|----------------|--------|
//! |xDMAChannelControlSet      |    Mandatory   |    Y   |
//! |---------------------------|----------------|--------|
//! |xDMAChannelTransferSet     |    Mandatory   |    Y   |
//! |---------------------------|----------------|--------|
//! |xDMAChannelIntCallbackInit |    Mandatory   |    Y   |
//! |---------------------------|----------------|--------|
//! |xDMAChannelIntCallbackGet  |  Non-Mandatory |    Y   |
//! |---------------------------|----------------|--------|
//! |xDMAChannelIntEnable       |    Mandatory   |    Y   |
//! |---------------------------|----------------|--------|
//! |xDMAChannelIntDisable      |    Mandatory   |    Y   |
//! |---------------------------|----------------|--------|
//! |xDMAIntEnable              |  Non-Mandatory |    Y   |
//! |---------------------------|----------------|--------|
//! |xDMAIntDisable             |  Non-Mandatory |    Y   |
//! |---------------------------|----------------|--------|
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xDMAEnable(ulChannelID)                                               \
        PDMAEnable(ulChannelID)
        
//*****************************************************************************
//
//! \brief Disables the uDMA controller for use.
//!
//! This function disables the uDMA controller.  Once disabled, the uDMA
//! controller will not operate until re-enabled with xDMAEnable().
//!
//! \return None.
//
//*****************************************************************************                                                        
#define xDMADisable(ulChannelID)                                              \
        PDMADisable(ulChannelID)

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
//! .
//!
//! \return Returns a Channel ID that dynamic assignment.
//! The channel ID can be:
//! - xDMA_CHANNEL_0
//! - xDMA_CHANNEL_1
//! - others refrence \ref xDMA_Channel_IDs
//! .
//
//*****************************************************************************
#define xDMAChannelDynamicAssign(ulDMASrcRequest, ulDMADestRequest)           \
        PDMAChannelDynamicAssign(ulDMASrcRequest, ulDMADestRequest)

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
#define xDMAChannelAssignmentGet(ulChannelID)                                 \
        PDMAChannelAssignmentGet(ulChannelID)

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
#define xDMAChannelDeAssign(ulChannelID)                                      \
        PDMAChannelDeAssign(ulChannelID)

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
#define xDMAChannelAttributeSet(ulChannelID, ulAttr) 

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
#define xDMAChannelAttributeGet(ulChannelID) 

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
//! xDMA_DST_INC(ulSrcSize) to selectan address increment of 8-bit bytes, 
//! 16-bit halfwords, 32-bit words,  select non-incrementing or 
//! destination data size.
//!
//! The arbitration size determines how many items are transferred before
//! the uDMA controller re-arbitrates for the bus.  Choose the arbitration size
//! from one of \b UDMA_ARB_1, \b UDMA_ARB_2, \b UDMA_ARB_4, \b UDMA_ARB_8,
//! through \b UDMA_ARB_1024 to select the arbitration size from 1 to 1024
//! items, in powers of 2.
//!
//! \note The address increment cannot be smaller than the data size. 
//! The transfer may use burst or single.
//!
//! \return None.
//
//*****************************************************************************
#define xDMAChannelControlSet(ulChannelID, ulControl)                         \
        PDMAChannelControlSet(ulChannelID, ulControl)    

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
#define xDMAChannelTransferSet(ulChannelID, ulMode, pvSrcAddr,                \
                               pvDstAddr, ulTransferSize)                     \
        PDMAChannelTransferSet(ulChannelID, pvSrcAddr,                        \
                               pvDstAddr, ulTransferSize)

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
#define xDMAChannelIntCallbackInit(ulChannelID, pfnCallback)                  \
        PDMAChannelIntCallbackInit(ulChannelID, pfnCallback)

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
#define xDMAChannelIntCallbackGet(ulChannelID)                                \
        PDMAChannelIntCallbackGet(ulChannelID)

//*****************************************************************************
//
//! \brief Enables individual DMA channel interrupt sources.
//!
//! \param ulChannelID is the channel ID.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated DMA channel interrupt sources.  
//! Only the sources that are enabled can be reflected to the processor 
//! interrupt; disabled sources have no effect on the processor.
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//!
//! - \b xDMA_EVENT_TC - transfer complete.
//! - \b xDMA_EVENT_ERROR - DMA Error interrupt.
//! .
//!
//! \note In the stellaris implement, this function do nothing.
//! \return None.
//
//*****************************************************************************
#define xDMAChannelIntEnable(ulChannelID, ulIntFlags)                         \
        PDMAChannelIntEnable(ulChannelID, ulIntFlags)

//*****************************************************************************
//
//! \brief Disables individual DMA channel interrupt sources.
//!
//! \param ulChannelID is the channel ID.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Disables the indicated DMA channel interrupt sources.  
//! Only the sources that are enabled can be reflected to the processor 
//! interrupt; disabled sources have no effect on the processor.
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//!
//! - \b xDMA_EVENT_TC - transfer complete.
//! - \b xDMA_EVENT_ERROR - DMA Error interrupt.
//! .
//!
//! \note In the stellaris implement, this function do nothing.
//! \return None.
//
//*****************************************************************************
#define xDMAChannelIntDisable(ulChannelID, ulIntFlags)                        \
        PDMAChannelIntDisable(ulChannelID, ulIntFlags)

//*****************************************************************************
//
//! \brief Enables the DMA interrupt through NVIC.
//!
//! Enable the DMA interrupt.
//!
//! \note In the stellaris implement, this function enables 
//! the uDMA Software Transfer, and uDMA Error interrupt.
//!
//! \return None.
//
//*****************************************************************************
#define xDMAIntEnable()                                                       \
        do                                                                    \
        {                                                                     \
            xIntEnable(INT_PDMA);                                             \
        }                                                                     \
        while(0)

//*****************************************************************************
//
//! \brief Disables the DMA interrupt through NVIC.
//!
//! Disables the DMA interrupt.
//!
//! \note In the stellaris implement, this function disables 
//! the uDMA Software Transfer, and uDMA Error interrupt.
//!
//! \return None.
//
//*****************************************************************************
#define xDMAIntDisable()                                                      \
        do                                                                    \
        {                                                                     \
            xIntDisable(INT_PDMA);                                            \
        }                                                                     \
        while(0)        

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_PDMA 
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_PDMA_Channel_IDs NUC1xx PDMA Channel IDs
//! \brief Defines for the NUC1xx PDMA Channel IDs
//! @{
//
//*****************************************************************************

#define PDMA_CHANNEL_COUNT      9
#define PDMA_CHANNEL_NOT_EXIST  0xFFFFFFFF 

#define PDMA_CHANNEL_0          0
#define PDMA_CHANNEL_1          1
#define PDMA_CHANNEL_2          2
#define PDMA_CHANNEL_3          3
#define PDMA_CHANNEL_4          4
#define PDMA_CHANNEL_5          5
#define PDMA_CHANNEL_6          6
#define PDMA_CHANNEL_7          7
#define PDMA_CHANNEL_8          8

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_PDMA_Event_Flags  NUC1xx PDMA Event Flags
//! \brief Defines for the NUC1xx PDMA Event Flags
//! @{
//
//*****************************************************************************

//
//! Transfer complete.
//
#define PDMA_EVENT_TC           0x00000002

//
//! Error occurs when DMA channel transfer.
//
#define PDMA_EVENT_ERROR        0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_PDMA_Channel_Control_Config NUC1xx PDMA Channel Control 
//! Configure
//! \brief Defines for the NUC1xx PDMA Channel Control Configure
//! @{
//
//*****************************************************************************

#define PDMA_DST_DIR_INC        0x00000000
#define PDMA_DST_DIR_FIXED      0x00000080

#define PDMA_SRC_DIR_INC        0x00000000
#define PDMA_SRC_DIR_FIXED      0x00000020

#define PDMA_WIDTH_8BIT         0x00000000
#define PDMA_WIDTH_16BIT        0x00080000
#define PDMA_WIDTH_32BIT        0x00100000

#define PDMA_MODE_MTOM          0x00000000
#define PDMA_MODE_MTOP          0x00000008
#define PDMA_MODE_PTOM          0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_PDMA_Request_Connections NUC1xx PDMA Request Connections
//! \brief Defines for the NUC1xx PDMA Request Connections
//! @{
//
//*****************************************************************************

#define PDMA_REQUEST_NOT_EXIST  0x00000000
#define PDMA_REQUEST_MEM        0x00000001

#define PDMA_REQUEST_UART0_RX   0x1000000F
#define PDMA_REQUEST_UART0_TX   0x1004010F

#define PDMA_REQUEST_UART1_RX   0x1008000F
#define PDMA_REQUEST_UART1_TX   0x100C010F

#define PDMA_REQUEST_SPI0_RX    0x0000000F
#define PDMA_REQUEST_SPI0_TX    0x0004010F

#define PDMA_REQUEST_SPI1_RX    0x0008000F
#define PDMA_REQUEST_SPI1_TX    0x000C010F

#define PDMA_REQUEST_SPI2_RX    0x0010000F
#define PDMA_REQUEST_SPI2_TX    0x0014010F

#define PDMA_REQUEST_SPI3_RX    0x0018000F
#define PDMA_REQUEST_SPI3_TX    0x001C010F

#define PDMA_REQUEST_IIS0_RX    0x2000000F
#define PDMA_REQUEST_IIS0_TX    0x2004010F

#define PDMA_REQUEST_ADC_RX     0x1018000F

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_PDMA_Exported_APIs NUC1xx PDMA APIs
//! \brief NUC1xx PDMA API Reference.
//! @{
//
//*****************************************************************************

extern void PDMAEnable(unsigned long ulChannelID);
extern void PDMADisable(unsigned long ulChannelID);
extern void PDMAChannelSoftwareReset(unsigned long ulChannelID);
extern xtBoolean PDMAChannelIsBusy(unsigned long ulChannelID);
extern void PDMAChannelIntDisable(unsigned long ulChannelID, 
                                 unsigned long ulIntFlags);
extern void PDMAChannelIntEnable(unsigned long ulChannelID, 
                                unsigned long ulIntFlags);
extern unsigned long PDMAChannelDynamicAssign(unsigned long ulDMASrcRequest,    
                                            unsigned long ulDMADestRequest);
extern xtBoolean PDMAChannelAssignmentGet(unsigned long ulChannelID);
extern void PDMAChannelDeAssign(unsigned long ulChannelID);

extern void PDMAChannelAttributeSet(unsigned long ulChannelID, 
                                unsigned long ulAttr);
extern unsigned long PDMAChannelAttributeGet(unsigned long ulChannelID);

extern void PDMAChannelControlSet(unsigned long ulChannelID,
                                unsigned long ulControl);
    
extern void PDMAChannelTransferSet(unsigned long ulChannelID,
                                   void *pvSrcAddr,
                                   void *pvDstAddr,
                                   unsigned long ulTransferSize);

extern void PDMAChannelIntCallbackInit(unsigned long ulChannelID, 
                                xtEventCallback pfnCallback);
extern xtEventCallback PDMAChannelIntCallbackGet(unsigned long ulChannelID);

extern xtBoolean PDMAChannelIntFlagGet(unsigned long ulChannelID, 
                                       unsigned long ulIntFlags);
extern void PDMAChannelIntFlagClear(unsigned long ulChannelID, 
                                    unsigned long ulIntFlags);

extern unsigned long PDMACurrentSourceAddrGet(unsigned long ulChannelID);
extern unsigned long PDMACurrentDestAddrGet(unsigned long ulChannelID);
extern unsigned long PDMARemainTransferCountGet(unsigned long ulChannelID);
extern unsigned long PDMASharedBufferDataGet(unsigned long ulChannelID);
extern unsigned long PDMAInternalBufPointerGet(unsigned long ulChannelID);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  __xDMA_H__

