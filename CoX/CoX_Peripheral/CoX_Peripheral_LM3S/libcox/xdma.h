//*****************************************************************************
//
//! \file xdma.h
//! \brief Defines and Macros for DMA API.
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

#ifndef __xDMA_H__
#define __xDMA_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
//extern "C"
//{
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
//! \addtogroup xDMA_Channel_IDs xDMA Channel ID
//!
//! \section xDMA_Channel_IDs_Section 1. Where to use this group
//! Values that can be passed to all the API in xdma.c 
//! as the ulChannel parameter. 
//! \n
//! \section xDMA_Channel_IDs_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +-------------------------+----------------+----------------+
//! |xDMA Channel IDs         |       CoX      |   Stellaris    |
//! |-------------------------|----------------|----------------|
//! |xDMA_CHANNEL_$x$         |  Non-Mandatory | xDMA_CHANNEL_0 |
//! |                         |                |     ......     |
//! |                         |                | xDMA_CHANNEL_31|
//! |-------------------------|----------------|----------------|
//! |xDMA_CHANNEL_COUNT       |    Mandatory   |        Y       |
//! |-------------------------|----------------|----------------|
//! |xDMA_CHANNEL_NOT_EXIST   |    Mandatory   |        Y       |
//! +-------------------------+----------------+----------------+
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
//! \addtogroup xDMA_Request_Connections xDMA Request Connections
//!
//! \section xDMA_Request_Connections_Section 1. Where to use this group
//! Values that can be passed to XPDMAChannelDynamicAssign() 
//! as the ulDMASrcRequest and ulDMADestRequest parameter. 
//! \n
//! \section xDMA_Request_Connections_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +-------------------------+----------------+----------------------+
//! |xDMA Request Connections |       CoX      |       Stellaris      |
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_NOT_EXIST   |    Mandatory   |           Y          |
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_MEM         |    Mandatory   |           Y          |
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_UART$x$_RX  |  Non-Mandatory | xDMA_REQUEST_UART0_RX|
//! |                         |                | xDMA_REQUEST_UART1_RX|
//! |                         |                | xDMA_REQUEST_UART2_RX|
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_SPI$x$_TX   |  Non-Mandatory | xDMA_REQUEST_SPI0_TX |
//! |                         |                | xDMA_REQUEST_SPI1_TX |
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_IIS$x$_TX   |  Non-Mandatory | xDMA_REQUEST_IIS0_TX |
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_IIS$x$_RX   |  Non-Mandatory | xDMA_REQUEST_IIS0_RX |
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_SPI$x$_RX   |  Non-Mandatory | xDMA_REQUEST_SPI0_RX |
//! |                         |                | xDMA_REQUEST_SPI1_RX |
//! |-------------------------|----------------|----------------------|
//! |xDMA_REQUEST_UART$x$_RX  |  Non-Mandatory | xDMA_REQUEST_UART0_RX|
//! |                         |                | xDMA_REQUEST_UART1_RX|
//! |                         |                | xDMA_REQUEST_UART2_RX|
//! |-------------------------|----------------|----------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
// Stellaris DMA Request Bit Field, From the request, we can kown which primary
// channel number or secondary channel number we can use.
//
// +------------+-----+--------+---------------+-----------+--------+-------------+
// |31          |30   |23 -16  |15 - 8         |7          |6 - 5   |4 - 0        |
// |------------|-----|--------|---------------|-----------|--------|-------------|
// |ismem       |rx/tx|map3    |map2(Secondary)|available  |reserved|map1(Primary)|
// |------------|-----|--------|---------------|-----------|--------|-------------|
// |peripheral:0|rx:0 |not used|Channel ID     |not:0      |        |Channel ID   |
// |mem:1       |tx:1 |        |               |available:1|        |             |
// +------------+-----+--------+---------------+-----------+--------+-------------+
//

#define xDMA_REQUEST_NOT_EXIST  0x00000000
#define xDMA_REQUEST_MEM        0x80000000

//#define xDMA_REQUEST_USB0_EP1_RX                                              \ 
//                                0x00000080
//#define xDMA_REQUEST_USB0_EP1_TX                                              \ 
//                                0x40000081
//#define xDMA_REQUEST_USB0_EP2_RX                                              \ 
//                                0x00000082
//#define xDMA_REQUEST_USB0_EP2_TX                                              \ 
//                                0x40000083
//#define xDMA_REQUEST_USB0_EP3_RX                                              \ 
//                                0x00000084
//#define xDMA_REQUEST_USB0_EP3_TX                                              \ 
//                                0x40000085

//#define xDMA_REQUEST_ETH0_RX    0x00000086
//#define xDMA_REQUEST_ETH0_TX    0x40000087

#define xDMA_REQUEST_UART0_RX   0x00000088
#define xDMA_REQUEST_UART0_TX   0x40000089

#define xDMA_REQUEST_UART1_RX   0x00008896
#define xDMA_REQUEST_UART1_TX   0x40008997

#define xDMA_REQUEST_UART2_RX   0x00008C00
#define xDMA_REQUEST_UART2_TX   0x40008D00

#define xDMA_REQUEST_SPI0_RX    0x0000008A
#define xDMA_REQUEST_SPI0_TX    0x4000008B

#define xDMA_REQUEST_SPI1_RX    0x00008A98
#define xDMA_REQUEST_SPI1_TX    0x40008B99

#define xDMA_REQUEST_IIS0_RX    0x0000009C
#define xDMA_REQUEST_IIS0_TX    0x4000009D

// ADC, timer will be added in the further

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xDMA_Ints xDMA Interrupt
//!
//! \section xDMA_Ints_Section 1. Where to use this group
//! Values that can be passed to XPDMAChannelIntEnable(),
//! XPDMAChannelIntDisable(), XPDMAChannelIntFlagGet(), XPDMAChannelIntFlagClear()
//! as the ulIntFlags parameter. 
//! 
//! \section xDMA_Ints_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +-------------------------+----------------+----------------+
//! |xDMA interrupt source    |       CoX      |   Stellaris    |
//! |-------------------------|----------------|----------------|
//! |xDMA_INT_TC              |    Mandatory   |        Y       |
//! |-------------------------|----------------|----------------|
//! |xDMA_INT_ERROR           |    Mandatory   |        Y       |
//! +-------------------------+----------------+----------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Transfer complete.
//
#define xDMA_INT_TC             0x00000001

//
//! Error occurs when DMA channel transfer.
//
#define xDMA_INT_ERROR          0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xDMA_Event_Flags xDMA Event Flags
//!
//! \section xDMA_Event_Flags_Section 1. Where to use this group
//! Uart Event/Error Flag, Used by IntHandle's Event Callback Function as 
//! ulMsgParam parameter. User Callback function can use this to detect what 
//! event happened.
//!
//! \section xDMA_Event_Flags_CoX 2.CoX Port Details
//! \verbatim
//! +-------------------------+----------------+----------------+
//! |xDMA event flag          |       CoX      |   Stellaris    |
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
//!
//! \section xDMA_Event_Flags_Section 1. Where to use this group
//! None
//! \n
//! \section xDMA_Event_Flags_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +-------------------------+----------------+----------------+
//! |xDMA channel Attr        |       CoX      |   Stellaris    |
//! |-------------------------|----------------|----------------|
//! |xDMA_ATTR_PRIORITY_NORMAL|  Non-Mandatory |        N       |
//! |-------------------------|----------------|----------------|
//! |xDMA_ATTR_PRIORITY_HIGH  |  Non-Mandatory |        N       |
//! |-------------------------|----------------|----------------|
//! |xDMA_ATTR_PRIORITY_MASK  |  Non-Mandatory |        N       |
//! +-------------------------+----------------+----------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

#define xDMA_ATTR_PRIORITY_NORMAL                                             \
                                0x00000000
#define xDMA_ATTR_PRIORITY_HIGH 0x00000001
#define xDMA_ATTR_PRIORITY_MASK 0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xDMA_Channel_Control_Config
//!
//! \section xDMA_Channel_Control_Config_Section 1. Where to use this group
//! Values that can be passed to PDMAChannelControlSet()
//! as the ulControl parameter. 
//! \n
//! \section xDMA_Channel_Control_Config_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +-------------------------+----------------+-----------------+
//! |xDMA Control Config      |       CoX      |    Stellaris    |
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
//! |xDMA_ARB_$x$             |  Non-Mandatory |xDMA_ARB_1       |
//! |                         |                |xDMA_ARB_2       |
//! |                         |                |xDMA_ARB_4       |
//! |                         |                |xDMA_ARB_8       |
//! |                         |                |xDMA_ARB_16      |
//! |                         |                |xDMA_ARB_32      |
//! |                         |                |xDMA_ARB_64      |
//! |                         |                |xDMA_ARB_128     |
//! |                         |                |xDMA_ARB_256     |
//! |                         |                |xDMA_ARB_512     |
//! |                         |                |xDMA_ARB_1024    |
//! |-------------------------|----------------|-----------------|
//! |xDMA_MODE_BASIC          |  Non-Mandatory |        N        |
//! |-------------------------|----------------|-----------------|
//! |xDMA_MODE_AUTO           |  Non-Mandatory |        N        |
//! +-------------------------+----------------+----------------+
//! \endverbatim
//! @{
//
//*****************************************************************************
#define xDMA_DST_INC_8          0x00000000
#define xDMA_DST_INC_16         0x40000000
#define xDMA_DST_INC_32         0x80000000
#define xDMA_DST_INC_NONE       0xc0000000
//#define xDMA_DST_INC(ulDstSize) (ulDstSize << 2)

#define xDMA_SRC_INC_8          0x00000000
#define xDMA_SRC_INC_16         0x04000000
#define xDMA_SRC_INC_32         0x08000000
#define xDMA_SRC_INC_NONE       0x0c000000
//#define xDMA_SRC_INC(ulSrcSize) (ulSrcSize << 2)

#define xDMA_SRC_SIZE_8         0x00000000
#define xDMA_SRC_SIZE_16        0x01000000
#define xDMA_SRC_SIZE_32        0x02000000

#define xDMA_DST_SIZE_8         0x00000000
#define xDMA_DST_SIZE_16        0x10000000
#define xDMA_DST_SIZE_32        0x20000000

//
// The unit is not a byte, is a item
//
#define xDMA_ARB_1              0x00000000
#define xDMA_ARB_2              0x00004000
#define xDMA_ARB_4              0x00008000
#define xDMA_ARB_8              0x0000c000
#define xDMA_ARB_16             0x00010000
#define xDMA_ARB_32             0x00014000
#define xDMA_ARB_64             0x00018000
#define xDMA_ARB_128            0x0001c000
#define xDMA_ARB_256            0x00020000
#define xDMA_ARB_512            0x00024000
#define xDMA_ARB_1024           0x00028000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xDMA_Channel_Mode xDMA Channel Mode
//!
//! Values that can be passed to xDMAChannelTransferSet()
//! as the ulMode parameter. 
//! 
//! \section xDMA_Channel_Control_Config_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +-------------------------+----------------+-----------------+
//! |xDMA Transfer Mode       |       CoX      |    Stellaris    |
//! |-------------------------|----------------|-----------------|
//! |xDMA_MODE_BASIC          |  Non-Mandatory |        Y        |
//! |-------------------------|----------------|-----------------|
//! |xDMA_MODE_AUTO           |  Non-Mandatory |        Y        |
//! +-------------------------+----------------+-----------------+
//! \endverbatim
//!
//! @{
//
//*****************************************************************************

//
//! Perform a basic transfer based on request(request is always present), Basic 
//! mode should not be used in any situation where the request is momentary.
//
#define xDMA_MODE_BASIC         0x00000001
//
//! Perform a transfer that will always complete once started even if request
//!is removed. This mode is suitable for software-triggered transfers.
//
#define xDMA_MODE_AUTO          0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xDMA_Exported_APIs xDMA API
//! @{
//
//*****************************************************************************

extern void xDMAEnable(void);

//*****************************************************************************
//
//! \brief Disables the DMA controller for use.
//!
//! This function disables the DMA controller.  Once disabled, the DMA
//! controller will not operate until re-enabled with xDMAEnable().
//!
//! \return None.
//
//*****************************************************************************
#define xDMADisable()                                                         \
        uDMADisable()

extern unsigned long xDMAChannelDynamicAssign(unsigned long ulDMASrcRequest,    
                                            unsigned long ulDMADestRequest);
extern xtBoolean xDMAChannelAssignmentGet(unsigned long ulChannelID);
extern void xDMAChannelDeAssign(unsigned long ulChannelID);

extern void xDMAChannelAttributeSet(unsigned long ulChannelID, 
                                unsigned long ulAttr);
extern unsigned long xDMAChannelAttributeGet(unsigned long ulChannelID);

extern void xDMAChannelControlSet(unsigned long ulChannelID,
                                unsigned long ulControl);
    
extern void xDMAChannelTransferSet(unsigned long ulChannelID,
                                unsigned long ulMode, void *pvSrcAddr,
                                void *pvDstAddr,
                                unsigned long ulTransferSize);

extern void  xDMAChannelIntCallbackInit(unsigned long ulChannelID, 
                                xtEventCallback pfnCallback);
extern xtEventCallback xDMAChannelIntCallbackGet(unsigned long ulChannelID);

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
//!
//! \note In the stellaris implement, this function do nothing.
//!
//! \return None.
//
//*****************************************************************************
#define xDMAChannelIntEnable(ulChannelID, ulIntFlags)                         \
        {}

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
//!
//! \note In the stellaris implement, this function do nothing.
//!
//! \return None.
//
//*****************************************************************************
#define xDMAChannelIntDisable(ulChannelID, ulIntFlags)                        \
        {}

//*****************************************************************************
//
//! \brief Enables the DMA interrupt through NVIC.
//!
//! Enable the DMA interrupt.
//!
//! \note In the stellaris implement, this function enables 
//! the DMA Software Transfer, and DMA Error interrupt.
//!
//! \return None.
//
//*****************************************************************************
#define xDMAIntEnable()                                                       \
        do                                                                    \
        {                                                                     \
            xIntEnable(INT_UDMA);                                             \
            xIntEnable(INT_UDMAERR);                                          \
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
            xIntDisable(INT_UDMA);                                            \
            xIntDisable(INT_UDMAERR);                                         \
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
//! \addtogroup Stellaris_DMA
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_DMA_Config DMA User Configuration
//! @{
//
//*****************************************************************************
#define UDMA_CONTROL_TABLE_SIZE 1024

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// A structure that defines an entry in the channel control table.  These
// fields are used by the uDMA controller and normally it is not necessary for
// software to directly read or write fields in the table.
//
//*****************************************************************************
typedef struct
{
    //
    // The ending source address of the data transfer.
    //
    volatile void *pvSrcEndAddr;

    //
    // The ending destination address of the data transfer.
    //
    volatile void *pvDstEndAddr;

    //
    // The channel control mode.
    //
    volatile unsigned long ulControl;

    //
    // An unused location.
    //
    volatile unsigned long ulSpare;
}
tDMAControlTable;

//*****************************************************************************
//
//! \brief A helper macro for building scatter-gather task table entries.
//!
//! \param ulTransferCount is the count of items to transfer for this task.
//! \param ulItemSize is the bit size of the items to transfer for this task.
//! \param ulSrcIncrement is the bit size increment for source data.
//! \param pvSrcAddr is the starting address of the data to transfer.
//! \param ulDstIncrement is the bit size increment for destination data.
//! \param pvDstAddr is the starting address of the destination data.
//! \param ulArbSize is the arbitration size to use for the transfer task.
//! \param ulMode is the transfer mode for this task.
//!
//! This macro is intended to be used to help populate a table of uDMA tasks
//! for a scatter-gather transfer.  This macro will calculate the values for
//! the fields of a task structure entry based on the input parameters.
//!
//! There are specific requirements for the values of each parameter.  No
//! checking is done so it is up to the caller to ensure that correct values
//! are used for the parameters.
//!
//! The \e ulTransferCount parameter is the number of items that will be
//! transferred by this task.  It must be in the range 1-1024.
//!
//! The \e ulItemSize parameter is the bit size of the transfer data.  It must
//! be one of \b UDMA_SIZE_8, \b UDMA_SIZE_16, or \b UDMA_SIZE_32.
//!
//! The \e ulSrcIncrement parameter is the increment size for the source data.
//! It must be one of \b UDMA_SRC_INC_8, \b UDMA_SRC_INC_16,
//! \b UDMA_SRC_INC_32, or \b UDMA_SRC_INC_NONE.
//!
//! The \e pvSrcAddr parameter is a void pointer to the beginning of the source
//! data.
//!
//! The \e ulDstIncrement parameter is the increment size for the destination
//! data.  It must be one of \b UDMA_SRC_INC_8, \b UDMA_SRC_INC_16,
//! \b UDMA_SRC_INC_32, or \b UDMA_SRC_INC_NONE.
//!
//! The \e pvDstAddr parameter is a void pointer to the beginning of the
//! location where the data will be transferred.
//!
//! The \e ulArbSize parameter is the arbitration size for the transfer, and
//! must be one of \b UDMA_ARB_1, \b UDMA_ARB_2, \b UDMA_ARB_4, and so on
//! up to \b UDMA_ARB_1024.  This is used to select the arbitration size in
//! powers of 2, from 1 to 1024.
//!
//! The \e ulMode parameter is the mode to use for this transfer task.  It
//! must be one of \b UDMA_MODE_BASIC, \b UDMA_MODE_AUTO,
//! \b UDMA_MODE_MEM_SCATTER_GATHER, or \b UDMA_MODE_PER_SCATTER_GATHER.  Note
//! that normally all tasks will be one of the scatter-gather modes while the
//! last task is a task list will be AUTO or BASIC.
//!
//! This macro is intended to be used to initialize individual entries of
//! a structure of tDMAControlTable type, like this:
//!
//! \verbatim
//!     tDMAControlTable MyTaskList[] =
//!     {
//!         uDMATaskStructEntry(Task1Count, UDMA_SIZE_8,
//!                             UDMA_SRC_INC_8, MySourceBuf,
//!                             UDMA_DST_INC_8, MyDestBuf,
//!                             UDMA_ARB_8, UDMA_MODE_MEM_SCATTER_GATHER),
//!         uDMATaskStructEntry(Task2Count, ... ),
//!     }
//! \endverbatim
//!
//! \return Nothing; this is not a function.
//
//*****************************************************************************
#define uDMATaskStructEntry(ulTransferCount,                                  \
                            ulItemSize,                                       \
                            ulSrcIncrement,                                   \
                            pvSrcAddr,                                        \
                            ulDstIncrement,                                   \
                            pvDstAddr,                                        \
                            ulArbSize,                                        \
                            ulMode)                                           \
    {                                                                         \
        (((ulSrcIncrement) == UDMA_SRC_INC_NONE) ? (pvSrcAddr) :              \
            ((void *)(&((unsigned char *)(pvSrcAddr))[((ulTransferCount) <<   \
                                         ((ulSrcIncrement) >> 26)) - 1]))),   \
        (((ulDstIncrement) == UDMA_DST_INC_NONE) ? (pvDstAddr) :              \
            ((void *)(&((unsigned char *)(pvDstAddr))[((ulTransferCount) <<   \
                                         ((ulDstIncrement) >> 30)) - 1]))),   \
        (ulSrcIncrement) | (ulDstIncrement) | (ulItemSize) | (ulArbSize) |    \
        (((ulTransferCount) - 1) << 4) |                                      \
        ((((ulMode) == UDMA_MODE_MEM_SCATTER_GATHER) ||                       \
          ((ulMode) == UDMA_MODE_PER_SCATTER_GATHER)) ?                       \
                (ulMode) | UDMA_MODE_ALT_SELECT : (ulMode)), 0                \
    }


//*****************************************************************************
//
//! \addtogroup Stellaris_DMA_Channel_Attr DMA Channel Attribute
//!
//! Flags that can be passed to uDMAChannelAttributeEnable(),
//! uDMAChannelAttributeDisable(), and returned from uDMAChannelAttributeGet().
//! @{
//
//*****************************************************************************

#define UDMA_ATTR_USEBURST      0x00000001
#define UDMA_ATTR_ALTSELECT     0x00000002
#define UDMA_ATTR_HIGH_PRIORITY 0x00000004
#define UDMA_ATTR_REQMASK       0x00000008
#define UDMA_ATTR_ALL           0x0000000F

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup Stellaris_DMA_Transfer_Mode DMA Transfer Mode
//!
//! DMA control modes that can be passed to uDMAModeSet() and returned
//! uDMAModeGet().
//! @{
//
//*****************************************************************************

#define UDMA_MODE_STOP          0x00000000
#define UDMA_MODE_BASIC         0x00000001
#define UDMA_MODE_AUTO          0x00000002
#define UDMA_MODE_PINGPONG      0x00000003
#define UDMA_MODE_MEM_SCATTER_GATHER                                          \
                                0x00000004
#define UDMA_MODE_PER_SCATTER_GATHER                                          \
                                0x00000006
#define UDMA_MODE_ALT_SELECT    0x00000001

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup Stellaris_DMA_Channel_Config DMA Channel Configuration
//!
//! Channel configuration values that can be passed to uDMAControlSet().
//! @{
//
//*****************************************************************************

#define UDMA_DST_INC_8          0x00000000
#define UDMA_DST_INC_16         0x40000000
#define UDMA_DST_INC_32         0x80000000
#define UDMA_DST_INC_NONE       0xc0000000
#define UDMA_SRC_INC_8          0x00000000
#define UDMA_SRC_INC_16         0x04000000
#define UDMA_SRC_INC_32         0x08000000
#define UDMA_SRC_INC_NONE       0x0c000000
#define UDMA_SIZE_8             0x00000000
#define UDMA_SIZE_16            0x11000000
#define UDMA_SIZE_32            0x22000000
#define UDMA_ARB_1              0x00000000
#define UDMA_ARB_2              0x00004000
#define UDMA_ARB_4              0x00008000
#define UDMA_ARB_8              0x0000c000
#define UDMA_ARB_16             0x00010000
#define UDMA_ARB_32             0x00014000
#define UDMA_ARB_64             0x00018000
#define UDMA_ARB_128            0x0001c000
#define UDMA_ARB_256            0x00020000
#define UDMA_ARB_512            0x00024000
#define UDMA_ARB_1024           0x00028000
#define UDMA_NEXT_USEBURST      0x00000008

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_DMA_Channel_Number DMA Channel Numbers
//!
//! Channel numbers to be passed to API functions that require a channel number
//! ID.
//! @{
//
//*****************************************************************************

#define UDMA_CHANNEL_USBEP1RX   0
#define UDMA_CHANNEL_USBEP1TX   1
#define UDMA_CHANNEL_USBEP2RX   2
#define UDMA_CHANNEL_USBEP2TX   3
#define UDMA_CHANNEL_USBEP3RX   4
#define UDMA_CHANNEL_USBEP3TX   5
#define UDMA_CHANNEL_ETH0RX     6
#define UDMA_CHANNEL_ETH0TX     7
#define UDMA_CHANNEL_UART0RX    8
#define UDMA_CHANNEL_UART0TX    9
#define UDMA_CHANNEL_SSI0RX     10
#define UDMA_CHANNEL_SSI0TX     11
#define UDMA_CHANNEL_ADC0       14
#define UDMA_CHANNEL_ADC1       15
#define UDMA_CHANNEL_ADC2       16
#define UDMA_CHANNEL_ADC3       17
#define UDMA_CHANNEL_TMR0A      18
#define UDMA_CHANNEL_TMR0B      19
#define UDMA_CHANNEL_TMR1A      20
#define UDMA_CHANNEL_TMR1B      21
#define UDMA_CHANNEL_UART1RX    22
#define UDMA_CHANNEL_UART1TX    23
#define UDMA_CHANNEL_SSI1RX     24
#define UDMA_CHANNEL_SSI1TX     25
#define UDMA_CHANNEL_I2S0RX     28
#define UDMA_CHANNEL_I2S0TX     29
#define UDMA_CHANNEL_SW         30

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_DMA_Channel_Structure_Sel DMA Channel Control structure Select
//!
//! Flags to be OR'd with the channel ID to indicate if the primary or alternate
//! control structure should be used.
//! @{
//
//*****************************************************************************

#define UDMA_PRI_SELECT         0x00000000
#define UDMA_ALT_SELECT         0x00000020

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_DMA_Channel_Secondary_Number DMA Channel Secondary Number
//!
//! Channel numbers to be passed to API functions that require a channel number
//! ID.  These are for secondary peripheral assignments.
//! @{
//
//*****************************************************************************
#define UDMA_SEC_CHANNEL_UART2RX_0                                            \
                                0
#define UDMA_SEC_CHANNEL_UART2TX_1                                            \
                                1
#define UDMA_SEC_CHANNEL_TMR3A  2
#define UDMA_SEC_CHANNEL_TMR3B  3
#define UDMA_SEC_CHANNEL_TMR2A_4                                              \
                                4
#define UDMA_SEC_CHANNEL_TMR2B_5                                              \
                                5
#define UDMA_SEC_CHANNEL_TMR2A_6                                              \
                                6
#define UDMA_SEC_CHANNEL_TMR2B_7                                              \
                                7
#define UDMA_SEC_CHANNEL_UART1RX                                              \
                                8
#define UDMA_SEC_CHANNEL_UART1TX                                              \
                                9
#define UDMA_SEC_CHANNEL_SSI1RX 10
#define UDMA_SEC_CHANNEL_SSI1TX 11
#define UDMA_SEC_CHANNEL_UART2RX_12                                           \
                                12
#define UDMA_SEC_CHANNEL_UART2TX_13                                           \
                                13
#define UDMA_SEC_CHANNEL_TMR2A_14                                             \
                                14
#define UDMA_SEC_CHANNEL_TMR2B_15                                             \
                                15
#define UDMA_SEC_CHANNEL_TMR1A  18
#define UDMA_SEC_CHANNEL_TMR1B  19
#define UDMA_SEC_CHANNEL_EPI0RX 20
#define UDMA_SEC_CHANNEL_EPI0TX 21
#define UDMA_SEC_CHANNEL_ADC10  24
#define UDMA_SEC_CHANNEL_ADC11  25
#define UDMA_SEC_CHANNEL_ADC12  26
#define UDMA_SEC_CHANNEL_ADC13  27
#define UDMA_SEC_CHANNEL_SW     30

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// uDMA default/secondary peripheral selections, to be passed to
// uDMAChannelSelectSecondary() and uDMAChannelSelectDefault().
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_DMA_Channel_Peripheral_Sel DMA Channel Default/Secondary Peripheral Selections
//!
//! uDMA default/secondary peripheral selections, to be passed to
//! uDMAChannelSelectSecondary() and uDMAChannelSelectDefault().
//! @{
//
//*****************************************************************************

#define UDMA_DEF_USBEP1RX_SEC_UART2RX                                         \
                                0x00000001
#define UDMA_DEF_USBEP1TX_SEC_UART2TX                                         \
                                0x00000002
#define UDMA_DEF_USBEP2RX_SEC_TMR3A                                           \
                                0x00000004
#define UDMA_DEF_USBEP2TX_SEC_TMR3B                                           \
                                0x00000008
#define UDMA_DEF_USBEP3RX_SEC_TMR2A                                           \
                                0x00000010
#define UDMA_DEF_USBEP3TX_SEC_TMR2B                                           \
                                0x00000020
#define UDMA_DEF_ETH0RX_SEC_TMR2A                                             \
                                0x00000040
#define UDMA_DEF_ETH0TX_SEC_TMR2B                                             \
                                0x00000080
#define UDMA_DEF_UART0RX_SEC_UART1RX                                          \
                                0x00000100
#define UDMA_DEF_UART0TX_SEC_UART1TX                                          \
                                0x00000200
#define UDMA_DEF_SSI0RX_SEC_SSI1RX                                            \
                                0x00000400
#define UDMA_DEF_SSI0TX_SEC_SSI1TX                                            \
                                0x00000800
#define UDMA_DEF_RESERVED_SEC_UART2RX                                         \
                                0x00001000
#define UDMA_DEF_RESERVED_SEC_UART2TX                                         \
                                0x00002000
#define UDMA_DEF_ADC00_SEC_TMR2A                                              \
                                0x00004000
#define UDMA_DEF_ADC01_SEC_TMR2B                                              \
                                0x00008000
#define UDMA_DEF_ADC02_SEC_RESERVED                                           \
                                0x00010000
#define UDMA_DEF_ADC03_SEC_RESERVED                                           \
                                0x00020000
#define UDMA_DEF_TMR0A_SEC_TMR1A                                              \
                                0x00040000
#define UDMA_DEF_TMR0B_SEC_TMR1B                                              \
                                0x00080000
#define UDMA_DEF_TMR1A_SEC_EPI0RX                                             \
                                0x00100000
#define UDMA_DEF_TMR1B_SEC_EPI0TX                                             \
                                0x00200000
#define UDMA_DEF_UART1RX_SEC_RESERVED                                         \
                                0x00400000
#define UDMA_DEF_UART1TX_SEC_RESERVED                                         \
                                0x00800000
#define UDMA_DEF_SSI1RX_SEC_ADC10                                             \
                                0x01000000
#define UDMA_DEF_SSI1TX_SEC_ADC11                                             \
                                0x02000000
#define UDMA_DEF_RESERVED_SEC_ADC12                                           \
                                0x04000000
#define UDMA_DEF_RESERVED_SEC_ADC13                                           \
                                0x08000000
#define UDMA_DEF_I2S0RX_SEC_RESERVED                                          \
                                0x10000000
#define UDMA_DEF_I2S0TX_SEC_RESERVED                                          \
                                0x20000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_DMA_Exported_APIs
//! @{
//
//*****************************************************************************

extern void uDMAEnable(void);
extern void uDMADisable(void);
extern unsigned long uDMAErrorStatusGet(void);
extern void uDMAErrorStatusClear(void);
extern void uDMAChannelEnable(unsigned long ulChannelNum);
extern void uDMAChannelDisable(unsigned long ulChannelNum);
extern xtBoolean uDMAChannelIsEnabled(unsigned long ulChannelNum);
extern void uDMAControlBaseSet(void *pControlTable);
extern void *uDMAControlBaseGet(void);
extern void *uDMAControlAlternateBaseGet(void);
extern void uDMAChannelRequest(unsigned long ulChannelNum);
extern void uDMAChannelAttributeEnable(unsigned long ulChannelNum,
                                       unsigned long ulAttr);
extern void uDMAChannelAttributeDisable(unsigned long ulChannelNum,
                                        unsigned long ulAttr);
extern unsigned long uDMAChannelAttributeGet(unsigned long ulChannelNum);
extern void uDMAChannelControlSet(unsigned long ulChannelStructIndex,
                                  unsigned long ulControl);
extern void uDMAChannelTransferSet(unsigned long ulChannelStructIndex,
                                   unsigned long ulMode, void *pvSrcAddr,
                                   void *pvDstAddr,
                                   unsigned long ulTransferSize);
extern void uDMAChannelScatterGatherSet(unsigned long ulChannelNum,
                                        unsigned ulTaskCount, void *pvTaskList,
                                        unsigned long ulIsPeriphSG);
extern unsigned long uDMAChannelSizeGet(unsigned long ulChannelStructIndex);
extern unsigned long uDMAChannelModeGet(unsigned long ulChannelStructIndex);
extern void uDMAChannelSelectDefault(unsigned long ulDefPeriphs);
extern void uDMAChannelSelectSecondary(unsigned long ulSecPeriphs);

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
//}
#endif

#endif //  __xDMA_H__
