#ifndef _AU9110_UART_H_
#define _AU9110_UART_H_

//*****************************************************************************
//
//! \addtogroup AU9110_UART
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_UART_INT_Type AU9110 UART Interrupt Type
//! \brief Values that show AU9110 UART Interrupt Type
//! Values that can be passed to UARTIntEnable, UARTIntDisable, and UARTIntClear
//! as the ulIntFlags parameter, and returned from UARTIntStatus.
//! @{
//
//*****************************************************************************

#define UART_INT_LIN            0x080       // LIN RX Break Field Detected Interrupt
#define UART_INT_WAKEUP         0x040       // Wake up CPU function
#define UART_INT_BUFERR         0x020       // Buffer Error Interrupt
#define UART_INT_RTO            0x010       // Rx Time out Interrupt
#define UART_INT_MOS            0x008       // RModem Status Interrupt
#define UART_INT_RLS            0x004       // Receive Line Status Interrupt
#define UART_INT_THRE           0x002       // Transmit Holding Register Empty Interrupt
#define UART_INT_RDA            0x001       // Receive Data Available Interrupt.

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_UART_Line_Config AU9110 UART Line Configuration
//! \brief Values that show AU9110 UART Line Configuration
//! Values that can be passed to UARTConfigSetExpClk as the ulConfig parameter
//! and returned by UARTConfigGetExpClk in the pulConfig parameter.
//! Additionally, the UART_CONFIG_PAR_* subset can be passed to
//! UARTParityModeSet as the ulParity parameter, and are returned by
//! UARTParityModeGet.
//! @{
//
//*****************************************************************************

#define UART_CONFIG_WLEN_MASK   0x00000003  // Mask for extracting word length
#define UART_CONFIG_WLEN_8      0x00000003  // 8 bit data
#define UART_CONFIG_WLEN_7      0x00000002  // 7 bit data
#define UART_CONFIG_WLEN_6      0x00000001  // 6 bit data
#define UART_CONFIG_WLEN_5      0x00000000  // 5 bit data
#define UART_CONFIG_STOP_MASK   0x00000004  // Mask for extracting stop bits
#define UART_CONFIG_STOP_1      0x00000000  // One stop bit
#define UART_CONFIG_STOP_2      0x00000004  // Two stop bits

#define UART_CONFIG_PAR_MASK    0x00000038  // Mask for extracting parity
#define UART_CONFIG_PAR_NONE    0x00000000  // No parity
#define UART_CONFIG_PAR_EVEN    0x00000018  // Even parity
#define UART_CONFIG_PAR_ODD     0x00000008  // Odd parity
#define UART_CONFIG_PAR_ONE     0x00000028  // Parity bit is one
#define UART_CONFIG_PAR_ZERO    0x00000038  // Parity bit is zero

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_UART_Enable_Blocks AU9110 UART Enable Blocks
//! \brief Values that show AU9110 UART Enable Blocks
//! Uart logic blocks  that can be passed to UARTEnable or UARTDisable as
//! the ulBlock parameter.
//! @{
//
//*****************************************************************************

//
//! Uart block
//
#define UART_BLOCK_UART         0

//
//! Uart transmit block
//
#define UART_BLOCK_TX           0x00000080

//
//! uart receive block
//
#define UART_BLOCK_RX           0x00000040

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_UART_FIFO_Level AU9110 UART FIFO Level
//! \brief Values that show AU9110 UART FIFO Level
//! Values that can be passed to UARTIntEnable, UARTIntDisable, and UARTIntClear
//! as the ulIntFlags parameter, and returned from UARTIntStatus.
//! @{
//
//*****************************************************************************

#define UART_FIFO_1BYTES        0x000       // 1 byte
#define UART_FIFO_4BYTES        0x010       // 4 bytes
#define UART_FIFO_8BYTES        0x020       // 8 bytes
#define UART_FIFO_14BYTES       0x030       // 14 bytes
#define UART_FIFO_30BYTES       0x040       // 30 bytes
#define UART_FIFO_46BYTES       0x050       // 46 bytes
#define UART_FIFO_62BYTES       0x060       // 62 bytes

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_UART_DMA_Flag AU9110 UART DMA Flag
//! \brief Values that show AU9110 UART DMA Flag
//! Values that can be passed to UARTDMAEnable() and UARTDMADisable().
//! @{
//
//*****************************************************************************

#define UART_DMA_TX             0x00004000  // Enable DMA for transmit
#define UART_DMA_RX             0x00008000  // Enable DMA for receive

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_UART_OUTPUT_RTS AU9110 UART OUTPUT RTS
//! \brief Values that show AU9110 UART OUTPUT RTS
//! Values that can be passed to UARTModemControlSet() or returned from
//! UARTModemControlGet().
//! @{
//
//*****************************************************************************

#define UART_TRIGGER_RTS_H      0x00000200
#define UART_TRIGGER_RTS_L      0x00000000
#define UART_OUTPUT_RTS_SET     0x00000002
#define UART_OUTPUT_RTS_GET_H   0x00002000
#define UART_OUTPUT_RTS_GET_L   0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_UART_INPUT_CTS AU9110 UART INPUT CTS
//! \bfief Values that show AU9110 UART INPUT CTS
//! Values that can be returned from UARTModemStatusGet().
//! @{
//
//*****************************************************************************

#define UART_TRIGGER_CTS_H      0x00000100
#define UART_TRIGGER_CTS_L      0x00000000
#define UART_INPUT_CTS_H        0x00000010
#define UART_INPUT_CTS_L        0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup AU9110_UART_Flow_Control AU9110 UART Flow Control
//! \brief Values that show AU9110 UART Flow Control
//! Values that can be passed to UARTFlowControlSet() or returned from
//! UARTFlowControlGet().
//! @{
//
//*****************************************************************************

#define UART_FLOWCONTROL_TX     0x00001000
#define UART_FLOWCONTROL_RX     0x00002000
#define UART_FLOWCONTROL_NONE   0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_UART_Error AU9110 UART Error
//! \brief Values that show AU9110 UART Error
//! Values returned from UARTRxErrorGet().
//! @{
//
//*****************************************************************************

#define UART_RXERROR_OVERRUN    0x00000001
#define UART_RXERROR_BREAK      0x00000040
#define UART_RXERROR_PARITY     0x00000010
#define UART_RXERROR_FRAMING    0x00000020

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_UART_LIN_Config AU9110 UART LIN Configuration
//! \brief Values that show AU9110 UART LIN Configuration
//! Values that can be passed to UARTLINConfig as the ulConfig parameter
//! @{
//
//*****************************************************************************
//
#define UART_CONFIG_BKFL_MASK   0x0000000F  // Mask for LIN Break Field Length
#define UART_CONFIG_LIN_RX_EN   0x00000040  // 8 bit data
#define UART_CONFIG_LIN_TX_EN   0x00000080  // 7 bit data


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_UART_IrDA_Config AU9110 UART IrDA Configuration
//! \brief Values that show AU9110 UART IrDA Configuration
//! Values that can be passed to UARTIrDAConfig as the ulConfig parameter
//! @{
//
//*****************************************************************************

#define UART_CONFIG_IrDA_RX_EN  0x00000000  // Enable IrDA receiver
#define UART_CONFIG_IrDA_TX_EN  0x00000002  // Enable IrDA transmitter
#define UART_CONFIG_IrDA_INV_TX 0x00000020  // Inverse TX output signal
#define UART_CONFIG_IrDA_INV_RX 0x00000040  // Inverse RX input signal


#define UART_IRDA_MODE_NORMAL   0
#define UART_IRDA_MODE_LOW_POWER                                              \
	                            0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_UART_Exported_APIs AU9110 UART API
//! \brief AU9110 UART API Reference.
//! @{
//
//*****************************************************************************

extern void UARTParityModeSet(unsigned long ulBase, unsigned long ulParity);
extern unsigned long UARTParityModeGet(unsigned long ulBase);
extern void xUARTFIFORxLevelGet(unsigned long ulBase,
		                            unsigned long *pulRxLevel);
extern void xUARTConfigGet(unsigned long ulBase,
                                unsigned long *pulBaud,
                                unsigned long *pulConfig);
extern void UARTIrDAConfig(unsigned long ulBase, unsigned long ulConfig);
extern void UARTLINConfig(unsigned long ulBase, unsigned long ulBaud,
                          unsigned long ulConfig);
extern xtBoolean UARTFIFOTxIsEmpty(unsigned long ulBase);
extern xtBoolean UARTFIFOTxIsFull(unsigned long ulBase);
extern long UARTFIFOTxLength(unsigned long ulBase);
extern xtBoolean UARTFIFORxIsEmpty(unsigned long ulBase);
extern xtBoolean UARTFIFORxIsFull(unsigned long ulBase);
extern long UARTFIFORxLength(unsigned long ulBase);
extern void UARTBufferRead(unsigned long ulBase, unsigned char *ucBuffer,
                           unsigned long ulLength);
extern void UARTBufferWrite(unsigned long ulBase, unsigned char *ucBuffer,
                            unsigned long ulLength);
extern void UARTBreakCtl(unsigned long ulBase, xtBoolean bBreakState);
extern void UARTDMAEnable(unsigned long ulBase, unsigned long ulDMAFlags);
extern void UARTDMADisable(unsigned long ulBase, unsigned long ulDMAFlags);
extern unsigned long UARTRxErrorGet(unsigned long ulBase);
extern void UARTRxErrorClear(unsigned long ulBase);
extern void UARTModemControlSet(unsigned long ulBase,
                                unsigned long ulControl);
extern void UARTModemControlClear(unsigned long ulBase,
                                  unsigned long ulControl);
extern unsigned long UARTModemControlGet(unsigned long ulBase);
extern void UARTModemStatusSet(unsigned long ulBase, unsigned long ulCtsTirg);
extern unsigned long UARTModemStatusGet(unsigned long ulBase);
extern void UARTFlowControlSet(unsigned long ulBase, unsigned long ulMode);
extern unsigned long UARTFlowControlGet(unsigned long ulBase);
extern void UARTRxTimeOutSet(unsigned long ulBase, unsigned long ulValue);

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
