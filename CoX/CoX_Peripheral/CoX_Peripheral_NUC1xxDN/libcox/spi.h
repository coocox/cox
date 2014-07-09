#ifndef _NUC1XX_SPI_H_
#define _NUC1XX_SPI_H_

//*****************************************************************************
//
//! \addtogroup NUC1xx_SPI
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SPI_Ints NUC1xx SPI Interrupts
//! \brief Values show that NUC1xx SPI Interrupts
//! Values that can be passed to SPIIntEnable, SPIIntDisable, and SPIIntClear
//! as the ulIntFlags parameter, and returned from SPIIntStatus.
//! @{
//
//*****************************************************************************

//
//! All Error Interrupt Mask
//
#define SPI_INT_EOT             0x00010000
#define SPI_INT_TX              0x00000008
#define SPI_INT_RX              0x00000004
#define SPI_INT_RXOVERRUN       0x00000040
#define SPI_INT_RXTIMEOUT       0x00100000
#define SPI_INT_3WIRE           0x00000400

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SPI_Config NUC1xx SPI Configure
//! \brief Values show that NUC1xx SPI Configure
//! Values that can be passed to SPIConfig.
//! @{
//
//*****************************************************************************

//
//! polarity 0,
//! Tx changed at rising edge
//! Rx latched at rising edge
//
#define SPI_FORMAT_MODE_0       0x00000000

//
//! Moto Format, polarity 0, phase 0  M0
//! Tx changed at falling edge
//! Rx latched at rising edge
//
#define SPI_FORMAT_MODE_1       0x00000004

//
//! Moto Format, polarity 0, phase 1  M1
//! Tx changed at rising edge
//! Rx latched at falling edge
//
#define SPI_FORMAT_MODE_2       0x00000002

//
//! polarity 0
//! Tx changed at falling edge
//! Rx latched at falling edge
//
#define SPI_FORMAT_MODE_3       0x00000006

//
//! polarity 1
//! Tx changed at rising edge
//! Rx latched at rising edge
//
#define SPI_FORMAT_MODE_4       0x00000800

//
//! Moto Format, polarity 1, phase 1  M4
//! Tx changed at falling edge
//! Rx latched at rising edge
//
#define SPI_FORMAT_MODE_5       0x00000804

//
//! Moto Format, polarity 1, phase 0  M3
//! Tx changed at rising edge
//! Rx latched at falling edge
//
#define SPI_FORMAT_MODE_6       0x00000802

//
//! polarity 1
//! Tx changed at falling edge
//! Rx latched at falling edge
//
#define SPI_FORMAT_MODE_7       0x00000806

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
#define SPI_LSB_FIRST           0x00000400

//
//! data width 1 bit
//
#define SPI_DATA_WIDTH1         0x00000008

//
//! data width 2 bit
//
#define SPI_DATA_WIDTH2         0x00000010

//
//! data width 3 bit
//
#define SPI_DATA_WIDTH3         0x00000018

//
//! data width 4 bit
//
#define SPI_DATA_WIDTH4         0x00000020

//
//! data width 5 bit
//
#define SPI_DATA_WIDTH5         0x00000028

//
//! data width 6 bit
//
#define SPI_DATA_WIDTH6         0x00000030

//
//! data width 7 bit
//
#define SPI_DATA_WIDTH7         0x00000038

//
//! data width 8 bit
//
#define SPI_DATA_WIDTH8         0x00000040

//
//! data width 9 bit
//
#define SPI_DATA_WIDTH9         0x00000048

//
//! data width 10 bit
//
#define SPI_DATA_WIDTH10        0x00000050

//
//! data width 11 bit
//
#define SPI_DATA_WIDTH11        0x00000058

//
//! data width 12 bit
//
#define SPI_DATA_WIDTH12        0x00000060

//
//! data width 13 bit
//
#define SPI_DATA_WIDTH13        0x00000068

//
//! data width 14 bit
//
#define SPI_DATA_WIDTH14        0x00000070

//
//! data width 15 bit
//
#define SPI_DATA_WIDTH15        0x00000078

//
//! data width 16 bit
//
#define SPI_DATA_WIDTH16        0x00000080

//
//! data width 17 bit
//
#define SPI_DATA_WIDTH17        0x00000088

//
//! data width 18 bit
//
#define SPI_DATA_WIDTH18        0x00000090

//
//! data width 19 bit
//
#define SPI_DATA_WIDTH19        0x00000098

//
//! data width 20 bit
//
#define SPI_DATA_WIDTH20        0x000000A0

//
//! data width 21 bit
//
#define SPI_DATA_WIDTH21        0x000000A8

//
//! data width 22 bit
//
#define SPI_DATA_WIDTH22        0x000000B0

//
//! data width 23 bit
//
#define SPI_DATA_WIDTH23        0x000000B8

//
//! data width 24 bit
//
#define SPI_DATA_WIDTH24        0x000000C0

//
//! data width 25 bit
//
#define SPI_DATA_WIDTH25        0x000000C8

//
//! data width 26 bit
//
#define SPI_DATA_WIDTH26        0x000000D0

//
//! data width 27 bit
//
#define SPI_DATA_WIDTH27        0x000000D8

//
//! data width 28 bit
//
#define SPI_DATA_WIDTH28        0x000000E0

//
//! data width 29 bit
//
#define SPI_DATA_WIDTH29        0x000000E8

//
//! data width 30 bit
//
#define SPI_DATA_WIDTH30        0x000000F0

//
//! data width 31 bit
//
#define SPI_DATA_WIDTH31        0x000000F8

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
//! \addtogroup NUC1xx_SPI_DMA NUC1xx SPI DMA
//! \brief Values that show NUC1xx SPI DMA
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
//! \addtogroup NUC1xx_SPI_SlaveSel NUC1xx SPI Slave Select
//! \brief Values that show NUC1xx SPI Slave Select
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
//! \addtogroup NUC1xx_SPI_SlaveSel_Config NUC1xx SPI Slave Select Configure
//! \brief Values that show NUC1xx SPI Slave Select Configure
//! Values that can be passed to SPIAutoSSEnable() SPISSSet()  SPISSClear()
//! SPISSConfig().
//! @{
//
//*****************************************************************************

#define SPI_SS_HARDWARE         0x00000008
#define SPI_SS_SOFTWARE         0x00000000

//
//! No Slave Pin Select
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
//! \addtogroup NUC1xx_SPI_FIFOStatus NUC1xx SPI FIFO Status
//! \brief Values that show NUC1xx SPI FIFO Status
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
//! \addtogroup NUC1xx_SPI_ByteReorder NUC1xx SPI Byte Reorder
//! \brief Values that show NUC1xx SPI Byte Reorder
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

//
//! Enable byte reorder function, but disable byte suspend function.
//
#define SPI_BYTE_REORDER        0x00000002

//
//! Disable byte reorder function, but insert a suspend interval
//
#define SPI_BYTE_SUSPEND        0x00000003

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_SPI_Exported_APIs  NUC1xx SPI API
//! \brief NUC1xx SPI API Reference
//! @{
//
//*****************************************************************************

extern void SPIConfig(unsigned long ulBase, unsigned long ulBitRate,
                      unsigned long ulConfig);

extern void SPIBurstDataRead(unsigned long ulBase, unsigned long *pulData);
extern unsigned long SPIRxRegisterGet(unsigned long ulBase,
                                      unsigned long *pulData,
                                      unsigned long ulCount);

extern void SPIBurstDataWrite(unsigned long ulBase, unsigned long *pulData);
extern unsigned long SPITxRegisterSet(unsigned long ulBase,
                                      unsigned long *pulData,
                                      unsigned long ulCount);
extern void SPIBitGoBusySet(unsigned long ulBase);
extern void SPIBitGoBusyClear(unsigned long ulBase);
extern void SPIIntFlagClear(unsigned long ulBase);
extern void SPIAutoSSEnable(unsigned long ulBase, unsigned long ulSlaveSel);
extern void SPIAutoSSDisable(unsigned long ulBase);
extern void SPISSSet(unsigned long ulBase, unsigned long ulSlaveSel);
extern void SPISSClear(unsigned long ulBase, unsigned long ulSlaveSel);
extern void SPISSConfig(unsigned long ulBase, unsigned long ulSSTriggerMode,
                        unsigned long ulSSActType);
extern xtBoolean SPILevelTriggerStatusGet(unsigned long ulBase);
extern unsigned long SPIFIFOStatusGet(unsigned long ulBase);
extern void SPIFIFOClear(unsigned long ulBase, unsigned long ulRxTx);
extern void SPIFIFOModeSet(unsigned long ulBase, xtBoolean xtEnable,
                           unsigned long ulInterval);
extern void SPIByteReorderSet(unsigned long ulBase,
                              unsigned long ulByteReorder);
extern void SPIVariableClockSet(unsigned long ulBase, unsigned long ulPattern,
                                xtBoolean xtEnable, unsigned long ulClock1,
                                unsigned long ulClock2);
extern void SPIDivOneFunction(unsigned long ulBase, xtBoolean xtEnable);
extern void SPI3WireFunction(unsigned long ulBase, xtBoolean xtEnable);
extern void SPI3WireAbort(unsigned long ulBase);
extern void SPI3WireStartIntEnable(unsigned long ulBase);
extern void SPI3WireStartIntDisable(unsigned long ulBase);
extern unsigned long SPI3WireStartIntFlagGet(unsigned long ulBase);
extern void SPI3WireStartIntFlagClear(unsigned long ulBase);


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
