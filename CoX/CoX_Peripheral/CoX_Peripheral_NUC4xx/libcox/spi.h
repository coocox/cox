#ifndef _NUC4XX_SPI_H_
#define _NUC4XX_SPI_H_

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup SPI
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI_Ints_Flag xSPI Interrupts Flag
//! \brief Values show that xSPI Interrupts Flag
//! Values that can be passed to  SPIIntFlagClear, SPIIntFlagGet
//! as the ulIntFlags parameter.
//! @{
//
//*****************************************************************************

//
//! All Interrupt Flag  Mask
//
#define SPI_FLAG_EOT            BIT_32_16
#define SPI_FLAG_RX_INTEN       BIT_32_0
#define SPI_FLAG_TX_INTEN       BIT_32_4
#define SPI_FLAG_RX_OVERRUN     BIT_32_2
#define SPI_FLAG_TIMEOUT        BIT_32_20
#define SPI_FLAG_3WIRE          BIT_32_11

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xSPI_Ints xSPI Interrupts
//! \brief Values show that xSPI Interrupts
//! Values that can be passed to SPIIntEnable, SPIIntDisable
//! as the ulIntFlags parameter.
//! @{
//
//*****************************************************************************

//
//! All Interrupt Mask
//
#define SPI_INT_EOT             0x00020000
#define SPI_INT_RX              0x20000004
#define SPI_INT_TX              0x20000008
#define SPI_INT_ERROR           0x10000300

#define SPI_INT_SLAVE_TIMEOUT   0x10020020
#define SPI_INT_RX_OVERRUN      0x20000020
#define SPI_INT_TIMEOUT         0x10000020

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_Config NUC4xx SPI Configure
//! \brief Values show that NUC4xx SPI Configure
//! Values that can be passed to SPIConfig.
//! @{
//
//*****************************************************************************

//
//! polarity 0,
//! Tx changed at rising edge
//! Rx latched at rising edge
//
#define SPI_FORMAT_MODE_0       0x00000004

//
//! Moto Format, polarity 0, phase 0  M0
//! Tx changed at falling edge
//! Rx latched at rising edge
//
#define SPI_FORMAT_MODE_1       0x00000002

//
//! Moto Format, polarity 0, phase 1  M1
//! Tx changed at rising edge
//! Rx latched at falling edge
//
#define SPI_FORMAT_MODE_2       0x0000000A

//
//! polarity 0
//! Tx changed at falling edge
//! Rx latched at falling edge
//
#define SPI_FORMAT_MODE_3       0x0000000C

//
//£¡ SPI master
//
#define SPI_MODE_MASTER         0x00000000

//
//! SPI slave
//
#define SPI_MODE_SLAVE          0x00040000

//
//! SPI MSB First
//
#define SPI_MSB_FIRST           0x00000000

//
//! SPI LSB First
//
#define SPI_LSB_FIRST           0x00002000

//
//! data width 8 bit
//
#define SPI_DATA_WIDTH8         0x00000800

//
//! data width 9 bit
//
#define SPI_DATA_WIDTH9         0x00000900

//
//! data width 10 bit
//
#define SPI_DATA_WIDTH10        0x00000A00

//
//! data width 11 bit
//
#define SPI_DATA_WIDTH11        0x00000B00

//
//! data width 12 bit
//
#define SPI_DATA_WIDTH12        0x00000C00

//
//! data width 13 bit
//
#define SPI_DATA_WIDTH13        0x00000D00

//
//! data width 14 bit
//
#define SPI_DATA_WIDTH14        0x00000E00

//
//! data width 15 bit
//
#define SPI_DATA_WIDTH15        0x00000F00

//
//! data width 16 bit
//
#define SPI_DATA_WIDTH16        0x00001000

//
//! data width 17 bit
//
#define SPI_DATA_WIDTH17        0x00001100

//
//! data width 18 bit
//
#define SPI_DATA_WIDTH18        0x00001200

//
//! data width 19 bit
//
#define SPI_DATA_WIDTH19        0x00001300

//
//! data width 20 bit
//
#define SPI_DATA_WIDTH20        0x00001400

//
//! data width 21 bit
//
#define SPI_DATA_WIDTH21        0x00001500

//
//! data width 22 bit
//
#define SPI_DATA_WIDTH22        0x00001600

//
//! data width 23 bit
//
#define SPI_DATA_WIDTH23        0x00001700

//
//! data width 24 bit
//
#define SPI_DATA_WIDTH24        0x00001800

//
//! data width 25 bit
//
#define SPI_DATA_WIDTH25        0x00001900

//
//! data width 26 bit
//
#define SPI_DATA_WIDTH26        0x00001A00

//
//! data width 27 bit
//
#define SPI_DATA_WIDTH27        0x00001B00

//
//! data width 28 bit
//
#define SPI_DATA_WIDTH28        0x00001C00

//
//! data width 29 bit
//
#define SPI_DATA_WIDTH29        0x00001D00

//
//! data width 30 bit
//
#define SPI_DATA_WIDTH30        0x00001E00

//
//! data width 31 bit
//
#define SPI_DATA_WIDTH31        0x00001F00

//
//! data width 32 bit
//
#define SPI_DATA_WIDTH32        0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_DMA NUC4xx SPI DMA
//! \brief Values that show NUC4xx SPI DMA
//! Values that can be passed to SPIDMAEnable() and SPIDMADisable().
//! @{
//
//*****************************************************************************

//
//! Enable DMA for transmit
//
#define SPI_DMA_TX              0x00000002

//
//! Enable DMA for receive
//
#define SPI_DMA_RX              0x00000001

//
//! Enable DMA for receive and transmit
//
#define SPI_DMA_BOTH            0x00000003

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_DUAL NUC4xx SPI DUAL IO
//! \brief Values that show NUC4xx SPI DUAL IO DIR
//! Values that can be passed to SPIPDualIOEnable() as ulDir.
//! @{
//
//*****************************************************************************

//
//! SPI dual io output
//
#define SPI_DUAL_IO_OUT         SPI_CNTRL_DUAL_IO_DIR

//
//! SPI dual io input
//
#define SPI_DUAL_IO_IN          0


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_SlaveSel NUC4xx SPI Slave Select
//! \brief Values that show NUC4xx SPI Slave Select
//! Values that can be passed to SPIAutoSSEnable() SPISSSet()and SPISSClear().
//! @{
//
//*****************************************************************************

//
//! No Slave Select
//
#define SPI_SS_NONE             0x00000000

//
//! SPISSx0
//
#define SPI_SS0                 0x00000001

//
//! SPISSx1
//
#define SPI_SS1                 0x00000002

//
//! SPISSx0 and SPISSx1
//
#define SPI_SS0_SS1             0x00000003

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_SlaveSel_Config NUC4xx SPI Slave Select Configure
//! \brief Values that show NUC4xx SPI Slave Select Configure
//! Values that can be passed to SPIAutoSSEnable() SPISSSet()  SPISSClear()
//! SPISSConfig().
//! @{
//
//*****************************************************************************

#define SPI_SS_HARDWARE         0x00000008
#define SPI_SS_SOFTWARE         0x00000000

//
//! The input slave select signal is edge-trigger.
//
#define SPI_SS_EDGE_TRIGGER     0x00000000

//
//! The slave select signal will be level-trigger.
//
#define SPI_SS_LEVEL_TRIGGER    0x00000010

//
//! SPISSx0/1 is active at low-level falling-edge
//
#define SPI_SS_ACTIVE_LOW_FALLING                                             \
                                0x00000000

//
//! SPISSx0/1 is active at high-level rising-edge
//
#define SPI_SS_ACTIVE_HIGH_RISING                                             \
                                0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_FIFOStatus NUC4xx SPI FIFO Status
//! \brief Values that show NUC4xx SPI FIFO Status
//! Values that can be passed to SPIFIFOStatusGet().
//! @{
//
//*****************************************************************************

//
//! Received FIFO_EMPTY STATUS
//
#define SPI_CNTRL_RX_EMPTY      0x01000000

//
//! Received FIFO_FULL STATUS
//
#define SPI_CNTRL_RX_FULL       0x02000000

//
//! Transmitted FIFO_EMPTY STATUS
//
#define SPI_CNTRL_TX_EMPTY      0x04000000

//
//! Transmitted FIFO_FULL STATUS
//
#define SPI_CNTRL_TX_FULL       0x08000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_ByteReorder NUC4xx SPI Byte Reorder
//! \brief Values that show NUC4xx SPI Byte Reorder
//! Values that can be passed to SPIByteReorderSet().
//! @{
//
//*****************************************************************************

//
//! Disable both byte reorder and byte suspend functions.
//
#define SPI_BYTE_REORDER_SUSPEND_DISABLE                                      \
                                0x00000000
//
//! Enable byte reorder function and insert a byte suspend interval
//
#define SPI_BYTE_REORDER_SUSPEND                                              \
                                0x00000001


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_SPI_Exported_APIs  NUC4xx SPI API
//! \brief NUC4xx SPI API Reference
//! @{
//
//*****************************************************************************

extern void SPIIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern xtBoolean SPIIntFlagGet(unsigned long ulBase, unsigned long ulIntFlags);
extern void SPIIntFlagClear(unsigned long ulBase, unsigned long ulIntFlags);
extern void SPIAutoSSEnable(unsigned long ulBase, unsigned long ulSlaveSel);
extern void SPIAutoSSDisable(unsigned long ulBase);
extern void SPISSSet(unsigned long ulBase, unsigned long ulSlaveSel);
extern void SPISSClear(unsigned long ulBase, unsigned long ulSlaveSel);
extern void SPISSConfig(unsigned long ulBase, unsigned long ulSSTriggerMode,
                        unsigned long ulSSActType);
extern unsigned long SPIFIFOStatusGet(unsigned long ulBase);
extern void SPIFIFOClear(unsigned long ulBase, unsigned long ulRxTx);
extern void SPIFIFOModeSet(unsigned long ulBase, xtBoolean xtEnable,
                           unsigned long ulInterval);
extern void SPIByteReorderSet(unsigned long ulBase, xtBoolean xtEnable);
extern void SPI3WireFunction(unsigned long ulBase, xtBoolean xtEnable);
extern void SPIPDMAEnable(unsigned long ulBase, unsigned long ulDmaMode);
extern void SPIPDMADisable(unsigned long ulBase, unsigned long ulDmaMode);
extern void SPIPDMAReset(unsigned long ulBase);
extern void SPIPDualIOEnable(unsigned long ulBase, unsigned long ulDir);
extern void SPIPDualIODisable(unsigned long ulBase);
extern void SPIPDuadIOEnable(unsigned long ulBase, unsigned long ulDir);
extern void SPIPDuadIODisable(unsigned long ulBase);

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

#endif
