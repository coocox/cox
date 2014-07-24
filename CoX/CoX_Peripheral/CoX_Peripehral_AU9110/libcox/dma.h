#ifndef _AU9110_DMA_H_
#define _AU9110_DMA_H_

//*****************************************************************************
//
//! \addtogroup AU9110_PDMA 
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PDMA_Channel_IDs AU9110 PDMA Channel IDs
//! \brief Defines for the AU9110 PDMA Channel IDs
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
//! \addtogroup AU9110_PDMA_Event_Flags  AU9110 PDMA Event Flags
//! \brief Defines for the AU9110 PDMA Event Flags
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
//! \addtogroup AU9110_PDMA_Channel_Control_Config AU9110 PDMA Channel Control 
//! Configure
//! \brief Defines for the AU9110 PDMA Channel Control Configure
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
//! \addtogroup AU9110_PDMA_Request_Connections AU9110 PDMA Request Connections
//! \brief Defines for the AU9110 PDMA Request Connections
//! @{
//
//*****************************************************************************

#define PDMA_REQUEST_NOT_EXIST  0x00000000
#define PDMA_REQUEST_MEM        0x00000001

#define PDMA_REQUEST_UART0_RX   0x000F000F
#define PDMA_REQUEST_UART0_TX   0x0014010F

#define PDMA_REQUEST_SPI0_RX    0x0000000F
#define PDMA_REQUEST_SPI0_TX    0x0004010F

#define PDMA_REQUEST_IIS0_RX    0x0018000F
#define PDMA_REQUEST_IIS0_TX    0x001C010F

#define PDMA_REQUEST_ADC_RX     0x0018000F

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_PDMA_Exported_APIs AU9110 PDMA APIs
//! \brief AU9110 PDMA API Reference.
//! @{
//
//*****************************************************************************

extern void PDMAChannelSoftwareReset(unsigned long ulChannelID);
extern xtBoolean PDMAChannelIsBusy(unsigned long ulChannelID);
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

#endif
