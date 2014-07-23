//*****************************************************************************
//
//! \file i2c.h
//! \brief Prototypes for the I2C Driver.
//! \version V2.1.1.0
//! \date 12/30/2011
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

#ifndef __I2C_H__
#define __I2C_H__

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
//! \addtogroup I2C
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_I2C
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_I2C_STATUS_Type I2C Status Type
//! \brief Values that can be passed to UARTIntEnable, I2CIntDisable, and 
//! I2CIntClear as the ulIntFlags parameter, and returned from I2CIntStatus.
//! @{
//
//*****************************************************************************

//
//! A Bus Error
//
#define I2C_I2STAT_BUS_ERROR    (0x00000000) 

//
//! No relevant information
//
#define I2C_I2STAT_NO_INF       (0x000000F8) 

//
//! A start condition has been transmitted in Master transmit mode
//
#define I2C_I2STAT_M_TX_START   (0x00000008)  

//
//! A repeat start condition has been transmitted in Master transmit mode
//
#define I2C_I2STAT_M_TX_RESTART (0x00000010)

//
//! SLA+W has been transmitted, ACK has been received in Master transmit mode
//
#define I2C_I2STAT_M_TX_SLAW_ACK                                              \
                                (0x00000018)

//
//! SLA+W has been transmitted, NACK has been received in Master transmit mode
//
#define I2C_I2STAT_M_TX_SLAW_NACK                                             \
                                (0x00000020)

//
//! Data has been transmitted, ACK has been received in Master transmit mode
//
#define I2C_I2STAT_M_TX_DAT_ACK (0x00000028)

//
//! Data has been transmitted, NACK has been received in Master transmit mode
//
#define I2C_I2STAT_M_TX_DAT_NACK                                              \
                                (0x00000030)

//
//! Arbitration lost in SLA+R/W or Data bytes in Master transmit mode
//
#define I2C_I2STAT_M_TX_ARB_LOST                                              \
                                (0x00000038)

//
//! SLA+R has been transmitted, ACK has been received in Master receive mode
//
#define I2C_I2STAT_M_RX_SLAR_ACK                                              \
                                (0x00000040)

//
//! SLA+R has been transmitted, NACK has been received in Master receive mode
//
#define I2C_I2STAT_M_RX_SLAR_NACK                                             \
                                (0x00000048)

//
//! Data has been received, ACK has been returned in Master receive mode
//
#define I2C_I2STAT_M_RX_DAT_ACK                                               \
                                (0x00000050)

//
//! Data has been received, NACK has been return in Master receive mode
//
#define I2C_I2STAT_M_RX_DAT_NACK                                              \
                                (0x00000058)

//
//! Own slave address has been received, ACK has been returned in Slave 
//! receive mode
//
#define I2C_I2STAT_S_RX_SLAW_ACK                                              \
                                (0x00000060)

//
//! Arbitration lost in SLA+R/W as master Own SLA+W has been received, 
//! ACK returned in Slave receive mode
//
#define I2C_I2STAT_S_RX_ARB_LOST_M_SLA                                        \
                                (0x00000068)

//
//! General call address has been received, ACK has been returned
//! in Slave receive mode
//
#define I2C_I2STAT_S_RX_GENCALL_ACK                                           \
                                (0x00000070)

//
//! Arbitration lost in SLA+R/W (GENERAL CALL) as master General Call address
//! has been received, ACK has been returned in Slave receive mode
//
#define I2C_I2STAT_S_RX_ARB_LOST_M_GENCALL                                    \
                                (0x00000078)

//
//! Previously addressed with own SLV address;Data has been received, ACK has 
//! been return in Slave receive mode
//
#define I2C_I2STAT_S_RX_PRE_SLA_DAT_ACK                                       \
                                (0x00000080)

//
//! Previously addressed with own SLV address;Data has been received,  NOT ACK  
//! has been return in Slave receive mode
//
#define I2C_I2STAT_S_RX_PRE_SLA_DAT_NACK                                      \
                                (0x00000088)

//
//! Previously addressed with General Call;Data has been received, ACK  
//! has been return in Slave receive mode
//
#define I2C_I2STAT_S_RX_PRE_GENCALL_DAT_ACK                                   \
                                (0x00000090)

//
//! Previously addressed with General Call;Data has been received,  NOT ACK  
//! has been return in Slave receive mode
//
#define I2C_I2STAT_S_RX_PRE_GENCALL_DAT_NACK                                  \
                                (0x00000098)

//
//! A STOP condition or repeated START condition has been received while still 
//! addressed as SLV/REC (Slave Receive) or SLV/TRX (Slave Transmit) 
//
#define I2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX                                 \
                                (0x000000A0)

//
//! Own SLA+R has been received, ACK has been returned  
//! in Slave transmit mode
//
#define I2C_I2STAT_S_TX_SLAR_ACK                                              \
                                (0x000000A8)

//
//! Arbitration lost in SLA+R/W as master Own SLA+R has been received, ACK has
//! has been returned in Slave transmit mode
//
#define I2C_I2STAT_S_TX_ARB_LOST_M_SLA                                        \
                                (0x000000B0)

//
//! Data has been transmitted, ACK has been received 
//! in Slave transmit mode
//
#define I2C_I2STAT_S_TX_DAT_ACK                                               \
                                (0x000000B8)

//
//! Data has been transmitted, NACK has been received  
//! in Slave transmit mode
//
#define I2C_I2STAT_S_TX_DAT_NACK                                              \
                                (0x000000C0)

//
//! Last data byte in I2DAT has been transmitted (AA = 0);ACK has been received  
//! in Slave transmit mode
//
#define I2C_I2STAT_S_TX_LAST_DAT_ACK                                          \
                                (0x000000C8)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_I2C_Transfer_Type I2C Transfer Type
//! @{
//
//*****************************************************************************
#define I2C_TRANSFER_POLLING    0
#define I2C_TRANSFER_INTERRUPT  1
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_I2C_General_Call I2C General Call
//! \brief Values that can be passed to I2CSlaveOwnAddressSet().
//! @{
//
//*****************************************************************************
#define I2C_GENERAL_CALL_EN     0x00000001
#define I2C_GENERAL_CALL_DIS    0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_I2C_Time_Out I2C Time Out
//! \brief Values that can be passed to I2CTimeoutCounterSet().
//! @{
//
//*****************************************************************************
#define I2C_TIMEOUT_EN          0x00000004
#define I2C_TIMEOUT_DIS         0x00000000
#define I2C_TIMEOUT_DIV4        0x00000002
#define I2C_TIMEOUT_DIV_NO      0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_I2C_INT_Type I2C Interrupt Type
//! \brief Values that can be passed to I2CIntEnable(),I2CIntDisable().
//! @{
//
//*****************************************************************************
#define I2C_INT_FUNCTION        0x00000080
#define I2C_INT_TIMEOUT         0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_I2C_Exported_Types M051 I2C Exported Types
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! I2C Master transfer setup data structure definitions
//
//*****************************************************************************
typedef struct 
{
    //
    //! Slave address 
    // 
    unsigned long ulSlave;  
    
    //
    //! Pointer to transmit data
    //    
    const void *  pvWBuf;
    
    //
    //! Length of transmit data 
    //
    unsigned long ulWLen;  
    
    //
    //! The actual length of the data transmited
    //
    unsigned long ulWCount; 
    
    //
    //! Pointer to receive data 
    //
    void *        pvRBuf;     
    
    //
    //! Length of receive data
    //
    unsigned long ulRLen;   
    
    //
    //! The actual length of the data received
    //
    unsigned long ulRCount; 
    
} 
tI2CMasterTransferCfg;

//*****************************************************************************
//
//! I2C slave transfer setup data structure definitions
//
//*****************************************************************************
typedef struct 
{
    
    //
    //! Pointer to transmit data
    //    
    const void *  pvWBuf;  
    
    //
    //! Length of transmit data 
    //
    unsigned long ulWLen;  
    
    //
    //! The actual length of the data transmited
    //
    unsigned long ulWCount; 
    
    //
    //! Pointer to receive data 
    //
    void *        pvRBuf;     
    
    //
    //! Length of receive data
    //
    unsigned long ulRLen;   
    
    //
    //! The actual length of the data received
    //
    unsigned long ulRCount; 
    
} 
tI2CSlaveTransferCfg;

//*****************************************************************************
//
//! I2C I2C device configuration structure type
//
//*****************************************************************************
typedef struct 
{
    
    //
    //! Transmission ulSetup
    //    
    unsigned long  ulSetup;  
    
    //
    //! Current direction phase, 0 - write, 1 - read
    //
    unsigned long  ulDir;   

    xtEventCallback g_pfnI2CHandlerCallbacks;
} 
tI2CConfig;


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup M051_I2C_Exported_APIs M051 I2C API
//! @{
//
//*****************************************************************************

extern void I2CMasterInit(unsigned long ulBase, unsigned long ulI2CClk);

extern xtBoolean I2CMasterTransfer(unsigned long ulBase, 
                                   tI2CMasterTransferCfg *tCfg,
                                   unsigned long ulOption);
extern xtBoolean I2CSlaveTransfer(unsigned long ulBase, 
                                   tI2CSlaveTransferCfg *tCfg,
                                   unsigned long ulOption);

extern xtBoolean I2CMasterTransferComplete(unsigned long ulBase);
extern xtBoolean I2CSlaveTransferComplete(unsigned long ulBase);

extern void I2CMasterHandler (unsigned long ulBase);
extern void I2CSlaveHandler (unsigned long ulBase);

extern void I2CIntCallbackInit(unsigned long ulBase, 
                               xtEventCallback xtI2CCallback);

extern void I2CDisable(unsigned long ulBase);
extern void I2CEnable(unsigned long ulBase);

extern unsigned long I2CStatusGet(unsigned long ulBase);
extern void I2CSlaveInit(unsigned long ulBase, unsigned char ucSlaveAddr, 
                         unsigned long ulGeneralCall);
extern void I2CSlaveOwnAddressSet(unsigned long ulBase, 
                                  unsigned char ucSlaveNum, 
                                  unsigned char ucSlaveAddr, 
                                  unsigned long ulGeneralCall);
extern void I2CSlaveOwnAddressMaskSet(unsigned long ulBase,
                                      unsigned char ucSlaveNum,
                                      unsigned char ucSlaveAddrMask);
extern void I2CIntFlagClear(unsigned long ulBase);
extern void I2CTimeoutFlagClear(unsigned long ulBase);
extern void I2CTimeoutCounterSet(unsigned long ulBase, unsigned long ulEnable,
                                 unsigned long ulDiv4);
extern xtBoolean I2CIntFlagGet(unsigned long ulBase);
extern xtBoolean I2CTimeoutFlagGet(unsigned long ulBase);
extern void I2CIntDisable(unsigned long ulBase);
extern void I2CIntEnable(unsigned long ulBase);


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

#endif // __xI2C_H__
