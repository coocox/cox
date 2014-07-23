//*****************************************************************************
//
//! \file uart.h
//! \brief Prototypes for the UART Driver.
//! \version V2.1.1.0
//! \date 12/28/2011
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

#ifndef __UART_H__
#define __UART_H__

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
//! \addtogroup UART
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_UART
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_UART_INT_Type M051 UART Interrupt Type
//! Values that can be passed to UARTIntEnable, UARTIntDisable, and UARTIntClear
//! as the ulIntFlags parameter, and returned from UARTIntStatus.
//! @{
//
//*****************************************************************************
//
//! LIN RX Break Field Detected Inter
//
#define UART_INT_LIN            0x080

//
//! Wake up CPU function
//
#define UART_INT_WAKEUP         0x040

//
//! Buffer Error Interrupt
//   
#define UART_INT_BUFERR         0x020

//
//! Rx Time out Interrupt
//
#define UART_INT_RTO            0x010

//
//! RModem Status Interrupt
// 
#define UART_INT_MOS            0x008

//
//! Receive Line Status Interrupt
//
#define UART_INT_RLS            0x004

//
//! Transmit Holding Register Empty Interrupt
//     
#define UART_INT_THRE           0x002

//
//! Receive Data Available Interrupt.
//  
#define UART_INT_RDA            0x001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_UART_Line_Config M051 UART Line Configuration
//! Values that can be passed to UARTConfigSetExpClk as the ulConfig parameter
//! and returned by UARTConfigGetExpClk in the pulConfig parameter.
//! Additionally,the UART_CONFIG_PAR_* subset can be passed to UARTParityModeSet
//! as the ulParity parameter, and are returned by UARTParityModeGet.
//! @{
//
//*****************************************************************************
//
//! Mask for extracting word length
//
#define UART_CONFIG_WLEN_MASK   0x00000003

//
//! 8 bit data
//
#define UART_CONFIG_WLEN_8      0x00000003

//
//! 7 bit data
//
#define UART_CONFIG_WLEN_7      0x00000002

//
//! 6 bit data
//
#define UART_CONFIG_WLEN_6      0x00000001

//
//! 5 bit data
//
#define UART_CONFIG_WLEN_5      0x00000000

//
//! Mask for extracting stop bits
//
#define UART_CONFIG_STOP_MASK   0x00000004

//
//! One stop bit
//
#define UART_CONFIG_STOP_ONE    0x00000000

//
//! Two stop bits
//
#define UART_CONFIG_STOP_TWO    0x00000004

//
//! Mask for extracting parity
//
#define UART_CONFIG_PAR_MASK    0x00000038

//
//! No parity
//
#define UART_CONFIG_PAR_NONE    0x00000000

//
//! Even parity
//
#define UART_CONFIG_PAR_EVEN    0x00000018

//
//! Odd parity
//
#define UART_CONFIG_PAR_ODD     0x00000008

//
//! Parity bit is one
//
#define UART_CONFIG_PAR_ONE     0x00000028

//
//! Parity bit is zero
//
#define UART_CONFIG_PAR_ZERO    0x00000038

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_UART_Enable_Blocks M051 UART Enable Blocks
//! Uart logic blocks  that can be passed to UARTEnable or UARTDisable as the
//! ulBlock parameter.
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
//! \addtogroup M051_UART_FIFO_Level M051 UART FIFO Level
//! Values that can be passed to UARTFIFOTriggerLevelSet(), as the ulRxLevel
//! parameter, and returned from UARTFIFOTriggerLevelGet().
//! @{
//
//*****************************************************************************

//
//! 1 byte
//
#define UART_FIFO_1BYTES        0x000

//
//! 4 bytes
//
#define UART_FIFO_4BYTES        0x010

//
//! 8 bytes
//
#define UART_FIFO_8BYTES        0x020

//
//! 14 bytes
//
#define UART_FIFO_14BYTES       0x030 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_UART_OUTPUT_RTS M051 UART OUTPUT RTS
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
//! \addtogroup M051_UART_INPUT_CTS M051 UART INPUT CTS
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
//! \addtogroup M051_UART_Flow_Control M051 UART Flow Control
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
//! \addtogroup M051_UART_Error M051 UART Error
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
//! \addtogroup M051_UART_LIN_Config M051 UART LIN Configuration
//! Values that can be passed to UARTLINConfig as the ulConfig parameter
//! @{
//
//*****************************************************************************

//
//! Mask for LIN Break Field Length
//
#define UART_CONFIG_BKFL_MASK   0x0000000F

//
//! 8 bit data
//
#define UART_CONFIG_LIN_RX_EN   0x00000040

//
//! 7 bit data
//
#define UART_CONFIG_LIN_TX_EN   0x00000080


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_UART_IrDA_Config M051 UART IrDA Configuration
//! Values that can be passed to UARTIrDAConfig() as the ulConfig parameter
//! @{
//
//*****************************************************************************
//
//! Enable IrDA receiver
//
#define UART_CONFIG_IrDA_RX_EN  0x00000000

//
//! Enable IrDA transmitter
//
#define UART_CONFIG_IrDA_TX_EN  0x00000002

//
//! Inverse TX output signal
//
#define UART_CONFIG_IrDA_INV_TX 0x00000020

//
//! Inverse RX input signal
//
#define UART_CONFIG_IrDA_INV_RX 0x00000040

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_UART_Exported_APIs M051 UART API
//! \brief M051 UART API Reference.
//! @{
//
//*****************************************************************************

extern void UARTParityModeSet(unsigned long ulBase, unsigned long ulParity);
extern unsigned long UARTParityModeGet(unsigned long ulBase);
extern void UARTFIFOTriggerLevelSet(unsigned long ulBase, 
		                            unsigned long ulRxLevel);
extern void UARTFIFOTriggerLevelGet(unsigned long ulBase,
		                            unsigned long *pulRxLevel);
extern void UARTConfigSetExpClk(unsigned long ulBase, 
                                unsigned long ulBaud, unsigned long ulConfig);
extern void UARTConfigGetExpClk(unsigned long ulBase,
                                unsigned long *pulBaud,
                                unsigned long *pulConfig);
extern void UARTEnable(unsigned long ulBase, unsigned long ulBlock);
extern void UARTDisable(unsigned long ulBase, unsigned long ulBlock);
extern void UARTEnableIrDA(unsigned long ulBase);
extern void UARTDisableIrDA(unsigned long ulBase);
extern void UARTIrDAConfig(unsigned long ulBase, unsigned long ulConfig);
extern void UARTEnableLIN(unsigned long ulBase);
extern void UARTDisableLIN(unsigned long ulBase);
extern void UARTLINConfig(unsigned long ulBase, unsigned long ulBaud,
                          unsigned long ulConfig);
extern xtBoolean UARTFIFOTxIsEmpty(unsigned long ulBase);
extern xtBoolean UARTFIFOTxIsFull(unsigned long ulBase);
extern long UARTFIFOTxLength(unsigned long ulBase);
extern xtBoolean UARTFIFORxIsEmpty(unsigned long ulBase);
extern xtBoolean UARTFIFORxIsFull(unsigned long ulBase);
extern long UARTFIFORxLength(unsigned long ulBase);
extern long UARTCharGetNonBlocking(unsigned long ulBase);
extern long UARTCharGet(unsigned long ulBase);
extern void UARTBufferRead(unsigned long ulBase, unsigned char *ucBuffer,
                           unsigned long ulLength);
extern xtBoolean UARTCharPutNonBlocking(unsigned long ulBase,
                                       unsigned char ucData);
extern void UARTCharPut(unsigned long ulBase, unsigned char ucData);
extern void UARTBufferWrite(unsigned long ulBase, unsigned char *ucBuffer,
                            unsigned long ulLength);
extern void UARTBreakCtl(unsigned long ulBase, xtBoolean bBreakState);
extern void UARTIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void UARTIntCallbackInit(unsigned long ulBase, 
                                xtEventCallback xtUARTCallback);
extern xtBoolean UARTIntEnableGet(unsigned long ulBase, unsigned long ulIntFlags);
extern void UARTIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern unsigned long UARTIntStatus(unsigned long ulBase, xtBoolean bMasked);
extern void UARTIntClear(unsigned long ulBase, unsigned long ulIntFlags);
extern unsigned long UARTRxErrorGet(unsigned long ulBase);
extern xtBoolean UARTBusy(unsigned long ulBase);
extern void UARTRxErrorClear(unsigned long ulBase);
//extern xtBoolean UARTBusy(unsigned long ulBase);
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
extern void UART485Config(unsigned long ulBase, unsigned long ulBaud,
                          unsigned long ul485Config,
                          unsigned long ulUARTConfig);


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

#endif // __xUART_H__

