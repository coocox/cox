#ifndef _NUC4XX_DMA_H_
#define _NUC4XX_DMA_H_

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Channel_IDs NUC4xx DMA Channel IDs
//! \brief Defines for the NUC4xx DMA Channel IDs
//! @{
//
//*****************************************************************************

#define DMA_CHANNEL_COUNT       9
#define DMA_CHANNEL_NOT_EXIST   0xFFFFFFFF

#define DMA_CHANNEL_0           0
#define DMA_CHANNEL_1           1
#define DMA_CHANNEL_2           2
#define DMA_CHANNEL_3           3
#define DMA_CHANNEL_4           4
#define DMA_CHANNEL_5           5
#define DMA_CHANNEL_6           6
#define DMA_CHANNEL_7           7
#define DMA_CHANNEL_8           8
#define DMA_CHANNEL_9           9
#define DMA_CHANNEL_10          10
#define DMA_CHANNEL_11          11
#define DMA_CHANNEL_12          12
#define DMA_CHANNEL_13          13
#define DMA_CHANNEL_14          14
#define DMA_CHANNEL_15          15

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Event_Flags  NUC4xx DMA Event Flags
//! \brief Defines for the NUC4xx DMA Event Flags
//! @{
//
//*****************************************************************************

//
//! Table Empty Interrupt
//
#define DMA_EVENT_TEMPTY        0x00000004

//
//! Transfer complete.
//
#define DMA_EVENT_TC            0x00000002

//
//! Error occurs when DMA channel transfer.
//
#define DMA_EVENT_ERROR         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Channel_Control_Config NUC4xx DMA Channel Control
//! Configure
//! \brief Defines for the NUC4xx DMA Channel Control Configure
//! @{
//
//*****************************************************************************

#define DMA_DST_DIR_INC         0x00000000
#define DMA_DST_DIR_FIXED       0x000000C0

#define DMA_SRC_DIR_INC         0x00000000
#define DMA_SRC_DIR_FIXED       0x00000030

#define DMA_WIDTH_8BIT          0x00000000
#define DMA_WIDTH_16BIT         0x00001000
#define DMA_WIDTH_32BIT         0x00002000

#define DMA_SRC_INC_8           (DMA_SRC_DIR_INC|DMA_WIDTH_8BIT)
#define DMA_SRC_INC_16          (DMA_SRC_DIR_INC|DMA_WIDTH_16BIT)
#define DMA_SRC_INC_32          (DMA_SRC_DIR_INC|DMA_WIDTH_32BIT)
#define DMA_SRC_INC_NONE        DMA_SRC_DIR_FIXED

#define DMA_DST_INC_8           (DMA_DST_DIR_INC|DMA_WIDTH_8BIT)
#define DMA_DST_INC_16          (DMA_DST_DIR_INC|DMA_WIDTH_16BIT)
#define DMA_DST_INC_32          (DMA_DST_DIR_INC|DMA_WIDTH_32BIT)
#define DMA_DST_INC_NONE        DMA_DST_DIR_FIXED

#define DMA_SRC_WIDTH_8         DMA_WIDTH_8BIT
#define DMA_SRC_WIDTH_16        DMA_WIDTH_8BIT
#define DMA_SRC_WIDTH_32        DMA_WIDTH_8BIT

#define DMA_DST_WIDTH_8         DMA_WIDTH_8BIT
#define DMA_DST_WIDTH_16        DMA_WIDTH_8BIT
#define DMA_DST_WIDTH_32        DMA_WIDTH_8BIT

#define DMA_MODE_BASIC          0x00000004
#define DMA_MODE_AUTO           0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Request_Connections NUC4xx DMA Request Connections
//! \brief Defines for the NUC4xx DMA Request Connections
//! @{
//
//*****************************************************************************

#define DMA_REQUEST_NOT_EXIST   0x00000000
#define DMA_REQUEST_MEM         0x00000001

#define DMA_REQUEST_UART0_RX    0x0011001F
#define DMA_REQUEST_UART0_TX    0x0004011F

#define DMA_REQUEST_UART1_RX    0x0012001F
#define DMA_REQUEST_UART1_TX    0x0005011F

#define DMA_REQUEST_UART2_RX    0x0013001F
#define DMA_REQUEST_UART2_TX    0x0006011F

#define DMA_REQUEST_UART3_RX    0x0014001F
#define DMA_REQUEST_UART3_TX    0x0007011F

#define DMA_REQUEST_UART4_RX    0x0015001F
#define DMA_REQUEST_UART4_TX    0x0008011F

#define DMA_REQUEST_UART5_RX    0x0016001F
#define DMA_REQUEST_UART5_TX    0x0009011F

#define DMA_REQUEST_SPI0_RX     0x000D001F
#define DMA_REQUEST_SPI0_TX     0x0000011F

#define DMA_REQUEST_SPI1_RX     0x000E001F
#define DMA_REQUEST_SPI1_TX     0x0001011F

#define DMA_REQUEST_SPI2_RX     0x000F001F
#define DMA_REQUEST_SPI2_TX     0x0002011F

#define DMA_REQUEST_SPI3_RX     0x0010001F
#define DMA_REQUEST_SPI3_TX     0x0003011F

#define DMA_REQUEST_IIS0_RX     0x0019001F
#define DMA_REQUEST_IIS0_TX     0x000B011F

#define DMA_REQUEST_IIS1_RX     0x001A001F
#define DMA_REQUEST_IIS1_TX     0x000C011F

#define DMA_REQUEST_ADC_RX      0x0018001F

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_DMA_Exported_APIs NUC4xx DMA APIs
//! \brief NUC4xx DMA API Reference.
//! @{
//
//*****************************************************************************


extern xtEventCallback DMAChannelIntCallbackGet(unsigned long ulChannelID);

extern xtBoolean DMAChannelIntFlagGet(unsigned long ulChannelID,
                                       unsigned long ulIntFlags);
extern void DMAChannelIntFlagClear(unsigned long ulChannelID,
                                    unsigned long ulIntFlags);

extern unsigned long DMACurrentSourceAddrGet(unsigned long ulChannelID);
extern unsigned long DMACurrentDestAddrGet(unsigned long ulChannelID);
extern unsigned long DMARemainTransferCountGet(unsigned long ulChannelID);

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
