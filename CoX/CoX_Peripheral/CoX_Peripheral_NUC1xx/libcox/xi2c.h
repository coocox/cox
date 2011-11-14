//*****************************************************************************
//
//! \file xi2c.h
//! \brief Prototypes for the I2C Driver.
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

#ifndef __xI2C_H__
#define __xI2C_H__

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
//! \addtogroup xI2C
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_Config xI2C interrupt handle config
//! 
//! \section xI2C_Config_section 1. Where to use this group
//! This is use to config xI2C intrerrupt handle.
//! 
//! \section xI2C_Config_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xGPIO General Pin ID    |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xI2C_MASTER             |    Mandatory   |   xI2C_MASTER          |
//! +------------------------+----------------+------------------------+
//! |xI2C_SLAVE              |    Mandatory   |   xI2C_SLAVE           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! use I2C xI2CMasterHandler 
//
#define xI2C_MASTER             1

//
//! use I2C xI2CSlaveTransfer
//
#define xI2C_SLAVE              0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_INT_Type xI2C Interrupt Type
//! \brief Values that show xI2C Interrupt Type
//! \n
//! \section xI2C_INT_Type_Section 1. Where to use this group
//! Values that can be passed to I2CIntEnable(),I2CIntDisable()
//! as the ulIntFlags parameter. 
//! \n
//! \section xI2C_INT_Type_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xI2C Interrupts         |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xI2C_INT_FUNCTION       |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xI2C_INT_ERROR          |  Non-Mandatory |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************
#define xI2C_INT_FUNCTION       I2C_INT_FUNCTION

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup xI2C_STATUS_Type xI2C Status Type
//! \brief Values that show xI2C Status Type,
//! \n
//! \section xI2C_STATUS_Type_Section 1. Where to use this group
//! I2C Event/Error Flag, Used by IntHandle's Event Callback Function as 
//! ulMsgParam parameter. User Callback function can user this to detect what 
//! event happened.
//! \n
//! \section xI2C_STATUS_Type_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +----------------------------------------+----------------+----------+
//! |xI2C Status Type                        |       CoX      |  NUC1xx  |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_BUS_ERROR                   |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_NO_INF                      |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_M_TX_START                  |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_M_TX_RESTART                |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_M_TX_SLAW_ACK               |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_M_TX_SLAW_NACK              |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_M_TX_DAT_ACK                |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_M_TX_DAT_NACK               |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_M_TX_ARB_LOST               |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_M_RX_SLAR_ACK               |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_M_RX_SLAR_NACK              |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_M_RX_DAT_ACK                |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_M_RX_DAT_NACK               |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_S_RX_SLAW_ACK               |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_S_RX_ARB_LOST_M_SLA         |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_S_RX_GENCALL_ACK            |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_S_RX_ARB_LOST_M_GENCALL     |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_S_RX_PRE_SLA_DAT_ACK        |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_S_RX_PRE_SLA_DAT_NACK       |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_S_RX_PRE_GENCALL_DAT_ACK    |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_S_RX_PRE_GENCALL_DAT_NACK   |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX  |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_S_TX_SLAR_ACK               |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_S_TX_ARB_LOST_M_SLA         |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_S_TX_DAT_ACK                |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_S_TX_DAT_NACK               |    Mandatory   |     Y    |
//! |----------------------------------------|----------------|----------|
//! |xI2C_I2STAT_S_TX_LAST_DAT_ACK           |    Mandatory   |     Y    |
//! +----------------------------------------+----------------+----------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! A Bus Error
//
#define xI2C_I2STAT_BUS_ERROR   (0x00000000) 

//
//! No relevant information
//
#define xI2C_I2STAT_NO_INF      (0x000000F8) 

//
//! A start condition has been transmitted in Master transmit mode
//
#define xI2C_I2STAT_M_TX_START  (0x00000008)  

//
//! A repeat start condition has been transmitted in Master transmit mode
//
#define xI2C_I2STAT_M_TX_RESTART                                              \
                                (0x00000010)

//
//! SLA+W has been transmitted, ACK has been received in Master transmit mode
//
#define xI2C_I2STAT_M_TX_SLAW_ACK                                             \
                                (0x00000018)

//
//! SLA+W has been transmitted, NACK has been received in Master transmit mode
//
#define xI2C_I2STAT_M_TX_SLAW_NACK                                            \
                                (0x00000020)

//
//! Data has been transmitted, ACK has been received in Master transmit mode
//
#define xI2C_I2STAT_M_TX_DAT_ACK                                              \
                                (0x00000028)

//
//! Data has been transmitted, NACK has been received in Master transmit mode
//
#define xI2C_I2STAT_M_TX_DAT_NACK                                             \
                                (0x00000030)

//
//! Arbitration lost in SLA+R/W or Data bytes in Master transmit mode
//
#define xI2C_I2STAT_M_TX_ARB_LOST                                             \
                                (0x00000038)

//
//! SLA+R has been transmitted, ACK has been received in Master receive mode
//
#define xI2C_I2STAT_M_RX_SLAR_ACK                                             \
                                (0x00000040)

//
//! SLA+R has been transmitted, NACK has been received in Master receive mode
//
#define xI2C_I2STAT_M_RX_SLAR_NACK                                            \
                                (0x00000048)

//
//! Data has been received, ACK has been returned in Master receive mode
//
#define xI2C_I2STAT_M_RX_DAT_ACK                                              \
                                (0x00000050)

//
//! Data has been received, NACK has been return in Master receive mode
//
#define xI2C_I2STAT_M_RX_DAT_NACK                                             \
                                (0x00000058)

//
//! Own slave address has been received, ACK has been returned in Slave 
//! receive mode
//
#define xI2C_I2STAT_S_RX_SLAW_ACK                                             \
                                (0x00000060)

//
//! Arbitration lost in SLA+R/W as master Own SLA+W has been received, 
//! ACK returned in Slave receive mode
//
#define xI2C_I2STAT_S_RX_ARB_LOST_M_SLA                                       \
                                (0x00000068)

//
//! General call address has been received, ACK has been returned
//! in Slave receive mode
//
#define xI2C_I2STAT_S_RX_GENCALL_ACK                                          \
                                (0x00000070)

//
//! Arbitration lost in SLA+R/W (GENERAL CALL) as master General Call address
//! has been received, ACK has been returned in Slave receive mode
//
#define xI2C_I2STAT_S_RX_ARB_LOST_M_GENCALL                                   \
                                (0x00000078)

//
//! Previously addressed with own SLV address;Data has been received, ACK has 
//! been return in Slave receive mode
//
#define xI2C_I2STAT_S_RX_PRE_SLA_DAT_ACK                                      \
                                (0x00000080)

//
//! Previously addressed with own SLV address;Data has been received,  NOT ACK  
//! has been return in Slave receive mode
//
#define xI2C_I2STAT_S_RX_PRE_SLA_DAT_NACK                                     \
                                (0x00000088)

//
//! Previously addressed with General Call;Data has been received, ACK  
//! has been return in Slave receive mode
//
#define xI2C_I2STAT_S_RX_PRE_GENCALL_DAT_ACK                                  \
                                (0x00000090)

//
//! Previously addressed with General Call;Data has been received,  NOT ACK  
//! has been return in Slave receive mode
//
#define xI2C_I2STAT_S_RX_PRE_GENCALL_DAT_NACK                                 \
                                (0x00000098)

//
//! A STOP condition or repeated START condition has been received while still 
//! addressed as SLV/REC (Slave Receive) or SLV/TRX (Slave Transmit) 
//
#define xI2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX                                \
                                (0x000000A0)

//
//! Own SLA+R has been received, ACK has been returned  
//! in Slave transmit mode
//
#define xI2C_I2STAT_S_TX_SLAR_ACK                                             \
                                (0x000000A8)

//
//! Arbitration lost in SLA+R/W as master Own SLA+R has been received, ACK has been returned
//! has been returned in Slave transmit mode
//
#define xI2C_I2STAT_S_TX_ARB_LOST_M_SLA                                       \
                                (0x000000B0)

//
//! Data has been transmitted, ACK has been received 
//! in Slave transmit mode
//
#define xI2C_I2STAT_S_TX_DAT_ACK                                              \
                                (0x000000B8)

//
//! Data has been transmitted, NACK has been received  
//! in Slave transmit mode
//
#define xI2C_I2STAT_S_TX_DAT_NACK                                             \
                                (0x000000C0)

//
//! Last data byte in I2DAT has been transmitted (AA = 0);ACK has been received  
//! in Slave transmit mode
//
#define xI2C_I2STAT_S_TX_LAST_DAT_ACK                                         \
                                (0x000000C8)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_Transfer_Type xI2C Transfer Type
//! \brief Values that show xI2C Transfer Type
//! \n
//! \section xI2C_Transfer_Type_Section 1. Where to use this group
//! Values that can be passed to I2CSlaveTransfer(),I2CMasterTransfer()
//! as the ulOption parameter. 
//! \n
//! \section xI2C_Transfer_Type_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xI2C Transfer Type      |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xI2C_TRANSFER_POLLING   |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xI2C_TRANSFER_INTERRUPT |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************
#define xI2C_TRANSFER_POLLING   I2C_TRANSFER_POLLING
#define xI2C_TRANSFER_INTERRUPT I2C_TRANSFER_INTERRUPT
//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_General_Call xI2C General Call
//! \brief Values that show xI2C General Call
//! \n
//! \section xI2C_Transfer_Type_Section 1. Where to use this group
//! Values that can be passed to I2CSlaveOwnAddressSet()
//! as the ulGeneralCall parameter. 
//! \n
//! \section xI2C_Transfer_Type_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xI2C General Call       |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xI2C_GENERAL_CALL_DIS   |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xI2C_GENERAL_CALL_EN    |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************
#define xI2C_GENERAL_CALL_EN    I2C_GENERAL_CALL_EN
#define xI2C_GENERAL_CALL_DIS   I2C_GENERAL_CALL_DIS

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_Exported_Types xI2C Exported Types
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! I2C Master transfer setup data structure definitions
//
//*****************************************************************************

#define xtI2CMasterTransferCfg  tI2CMasterTransferCfg

//*****************************************************************************
//
//! I2C slave transfer setup data structure definitions
//
//*****************************************************************************

#define xtI2CSlaveTransferCfg   tI2CSlaveTransferCfg

//*****************************************************************************
//
//! I2C I2C device configuration structure type
//
//*****************************************************************************


#define xtI2CConfig             tI2CConfig

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_Exported_APIs xI2C API
//! \brief xI2C API Reference.
//!
//! \section xI2C_Exported_APIs_Port CoX Port Details
//! \verbatim
//! +--------------------------+----------------+------------------------+
//! |xI2C API                  |       CoX      |         NUC1xx         |
//! |--------------------------|----------------|------------------------|
//! |xI2CIntCallbackInit       |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterInit            |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterTransfer        |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterTransferComplete|    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveTransferComplete |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterStatusGet       |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterIntEnable       |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterIntDisable      |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterIntFlagGet      |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterHandler         |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveInit             |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveTransfer         |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveOwnAddressSet    |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveOwnAddressMaskSet|    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveStatusGet        |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveIntEnable        |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveIntDisable       |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveIntFlagGet       |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveHandler          |    Mandatory   |            Y           |
//! +--------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Init interrupts callback for the specified Port.
//!
//! \param ulPort is the base address of the I2C port.
//! \param xtI2CCallback is callback for the specified Port.
//!
//! Init interrupts callback for the specified Port.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CIntCallbackInit(ulBase, xtI2CCallback)                            \
        I2CIntCallbackInit(ulBase, xtI2CCallback)
        
//*****************************************************************************
//
//! \brief Set the clock rate of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulI2CClk specifies the I2C clock rate.
//!
//! This function is to init and set the clock rate 
//! specified SPI port.
//!
//! The \e ulBase can be one of the following values:
//! \b xI2C0_BASE, \b xI2C1_BASE.
//!
//! The \e ulI2CClk is the I2C clock rate:
//!
//! \note this is only for master
//!
//! \return None.
//
//*****************************************************************************

#define xI2CMasterInit(ulBase, ulI2CClk)                                      \
        I2CMasterInit(ulBase, ulI2CClk)

//*****************************************************************************
//
//! \brief Transmit and Receive data in master mode of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//! \param tCfg specifies Pointer to a I2C_M_SETUP_Type structure that
//!  contains specified information about the configuration for master transfer.
//! Details please refer to \ref xtI2CMasterTransferCfg.
//! \param ulOption specifies interrupt or polling mode.
//! Details please refer to \ref xI2C_Transfer_Type.
//!
//! This function is to Transmit and Receive data in master mode of 
//! specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b xI2C0_BASE, \b xI2C1_BASE.
//!
//! The \e tCfg is the I2C Transfer data structure.
//! Details please refer to \ref xtI2CMasterTransferCfg.
//!
//! \note this is only for master
//! In case of using I2C to receive data only, either transmit length set to 0
//! or transmit data pointer set to NULL.
//! In case of using I2C to transmit data only, either receive length set to 0
//! or receive data pointer set to NULL.
//! In case of using I2C to transmit followed by receive data, transmit length,
//! transmit data pointer, receive length and receive data pointer should be set
//! corresponding.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterTransfer(ulBase, tCfg, ulOption)                            \
        I2CMasterTransfer(ulBase, tCfg, ulOption)

//*****************************************************************************
//
//! \brief Get status of Master Transfer. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get status of Master Transfer
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE.
//!
//! \note this is only for master
//!
//! \return Master transfer status, could be:\b xtrue	master transfer 
//! completed, \b xfalse master transfer have not completed yet
//
//*****************************************************************************
#define xI2CMasterTransferComplete(ulBase)                                    \
        I2CMasterTransferComplete(ulBase)

//*****************************************************************************
//
//! \brief Get status of slave Transfer. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get status of slave Transfer
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE.
//!
//! \note this is only for slave
//!
//! \return Master transfer status, could be:\b xtrue	slave transfer 
//! completed, \b xfalse slave transfer have not completed yet
//
//*****************************************************************************
#define xI2CSlaveTransferComplete(ulBase)                                     \
        I2CSlaveTransferComplete(ulBase)

//*****************************************************************************
//
//! \brief Get I2C status of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get I2C status of the specified I2C port.
//! There are 26 status codes. Please refer to Xi2c.h NUC1xx_I2C_STATUS_Type
//! in detail.
//!
//! The \e ulBase can be one of the following values:
//! \b xI2C0_BASE, \b xI2C1_BASE.
//!
//! \note None
//!
//! \return I2C status.
//
//*****************************************************************************
#define xI2CMasterStatusGet(ulBase)                                           \
        I2CStatusGet(ulBase)

//*****************************************************************************
//
//! \brief Enable I2C interrupt  of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulIntType specifies the I2C interrupt type.
//! Details please refer to \ref xI2C_INT_Type.
//!
//! This function is to enable I2C interrupt  of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b xI2C0_BASE, \b xI2C1_BASE.
//!
//! \note None
//!
//! \return None.
//
//***************************************************************************** 
#define xI2CMasterIntEnable(ulBase, ulIntType)                                \
        I2CIntEnable(ulBase)

//*****************************************************************************
//
//! \brief Disable I2C interrupt  of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulIntType specifies the I2C interupt type.
//! Details please refer to \ref xI2C_INT_Type.
//!
//! This function is to disable I2C interrupt  of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterIntDisable(ulBase, ulIntType)                               \
        I2CIntDisable(ulBase)

//*****************************************************************************
//
//! \brief Get the I2C interrupt flag of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulIntType specifies the I2C interupt type.
//! Details please refer to \ref xI2C_INT_Type.
//!
//! This function is to get the I2C interrupt flag of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE.
//!
//! \note None
//!
//! \return an xtBoolean value xtrue or xfalse.
//
//*****************************************************************************
#define xI2CMasterIntFlagGet(ulBase, ulIntType)                               \
        I2CIntFlagGet(ulBase)

//*****************************************************************************
//
//! \brief General Master Interrupt handler for I2C peripheral. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to give an eneral Master Interrupt handler for I2C 
//! peripheral
//!
//! The \e ulBase can be one of the following values:
//! \b xI2C0_BASE, \b xI2C1_BASE.
//!
//! \note this is only for master
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterHandler(ulBase)                                             \
        I2CMasterHandler(ulBase)

//*****************************************************************************
//
//! \brief Set the clock rate of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//! \param ucSlaveAddr specifies the slave address.
//! \param ulGeneralCall specifies enable General Call function or not.
//! Details please refer to \ref xI2C_General_Call.
//!
//! This function is to Set 4 7-bit slave addresses and enable General Call 
//! function of specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE.
//!
//! The \e ucSlaveAddr is the I2C slave address,There are 4 slave address.
//! The ucSlaveAddr can be a 7-bit value.
//!
//! The \e ulGeneralCall is to enable the General Call function or not.
//! The ulGeneralCall can be one of the following values:
//! \b I2C_GENERAL_CALL_EN,\b I2C_GENERAL_CALL_DIS.
//! Details please refer to \ref xI2C_General_Call_CoX.
//!
//! \note this is only for slave
//!
//! \return None.
//
//*****************************************************************************
#define xI2CSlaveInit(ulBase, ucSlaveAddr, ulGeneralCall)                     \
        I2CSlaveInit(ulBase, ucSlaveAddr, ulGeneralCall)

//*****************************************************************************
//
//! \brief Transmit and Receive data in slave mode of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//! \param tCfg specifies Pointer to a I2C_M_SETUP_Type structure that
//!  contains specified information about the configuration for slave transfer.
//! Details please refer to \ref xtI2CSlaveTransferCfg.
//! \param ulOption specifies interrupt or polling mode.
//!
//! This function is to Transmit and Receive data in slave mode of 
//! specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b xI2C0_BASE, \b xI2C1_BASE.
//!
//! The \e tCfg is the I2C slave Transfer data structure.
//! Details please refer to \ref xtI2CSlaveTransferCfg.
//!
//! \note this is only for slave
//! In case of using I2C to receive data only, either transmit length set to 0
//! or transmit data pointer set to NULL.
//! In case of using I2C to transmit data only, either receive length set to 0
//! or receive data pointer set to NULL.
//! In case of using I2C to transmit followed by receive data, transmit length,
//! transmit data pointer, receive length and receive data pointer should be set
//! corresponding.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CSlaveTransfer(ulBase, tCfg, ulOption)                             \
        I2CSlaveTransfer(ulBase, tCfg, ulOption)

//*****************************************************************************
//
//! \brief Set the slave address of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//! \param ucSlaveNum specifies the salve address number.
//! \param ucSlaveAddr specifies the slave address.
//! \param ulGeneralCall specifies enable General Call function or not.
//! Details please refer to \ref xI2C_General_Call.
//!
//! This function is to Set 4 7-bit slave addresses and enable General Call 
//! function of specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE.
//!
//! The \e ucSlaveNum is the I2C slave address number,There are 4 slave addrss,so
//! The ucSlaveNum can be: \b 0, \b 1, \b 2, \b 3.
//!
//! The \e ucSlaveAddr is the I2C slave address,There are 4 slave addrss.
//! The ucSlaveAddr can be a 7-bit value.
//!
//! The \e ulGeneralCall is to enable the General Call function or not.
//! The ulGeneralCall can be one of the following values:
//! \b I2C_GENERAL_CALL_EN,\b I2C_GENERAL_CALL_DIS.
//! Details please refer to \ref xI2C_General_Call_CoX.
//!
//! \note this is only for slave
//!
//! \return None.
//
//*****************************************************************************
#define xI2CSlaveOwnAddressSet(ulBase, ucSlaveNum, ucSlaveAddr, ulGeneralCall)\
        I2CSlaveOwnAddressSet(ulBase, ucSlaveNum, ucSlaveAddr, ulGeneralCall)

//*****************************************************************************
//
//! \brief Set 4 7-bit slave address mask of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//! \param ucSlaveNum specifies the salve address number.
//! \param ucSlaveAddrMask specifies the slave address mask.
//!
//! This function is to Set 4 7-bit slave address mask 
//! of specified I2C port.The corresponding address bit is "Don't Care"
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE.
//!
//! The \e ucSlaveNum is the I2C slave address number,There are 4 slave addrss,so
//! The ucSlaveNum can be: \b 0, \b 1, \b 2, \b 3.
//!
//! The \e ucSlaveAddrMask is the I2C slave address mask,There are 4 slave addrss.
//! The ucSlaveAddrMask can be a 7-bit value.
//!
//! \note this is only for slave
//!
//! \return None.
//
//*****************************************************************************
#define xI2CSlaveOwnAddressMaskSet(ulBase, ucSlaveNum, ucSlaveAddrMask)       \
        I2CSlaveOwnAddressMaskSet(ulBase, ucSlaveNum, ucSlaveAddrMask)

//*****************************************************************************
//
//! \brief Get I2C status of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get I2C status of the specified I2C port.
//! There are 26 status codes. Please refer to Xi2c.h NUC1xx_I2C_STATUS_Type
//! in detail.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE.
//!
//! \note None
//!
//! \return I2C status.
//
//*****************************************************************************
#define xI2CSlaveStatusGet(ulBase)                                            \
        I2CStatusGet(ulBase)

//*****************************************************************************
//
//! \brief Enable I2C interrupt  of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulIntType specifies the I2C interupt type.
//! Details please refer to \ref xI2C_INT_Type.
//!
//! This function is to enable I2C interrupt  of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b xI2C0_BASE, \b xI2C1_BASE.
//!
//! \note None
//!
//! \return None.
//
//***************************************************************************** 
#define xI2CSlaveIntEnable(ulBase, ulIntType)                                 \
        I2CIntEnable(ulBase)

//*****************************************************************************
//
//! \brief Disable I2C interrupt  of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulIntType specifies the I2C interupt type.
//! Details please refer to \ref xI2C_INT_Type.
//!
//! This function is to disable I2C interrupt  of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
#define xI2CSlaveIntDisable(ulBase, ulIntType)                                \
        I2CIntDisable(ulBase)

//*****************************************************************************
//
//! \brief Get the I2C interrupt flag of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulIntType specifies the I2C interupt type.
//! Details please refer to \ref xI2C_INT_Type.
//!
//! This function is to get the I2C interrupt flag of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE.
//!
//! \note None
//!
//! \return a xtBoolean value xtrue or xfalse.
//
//*****************************************************************************
#define xI2CSlaveIntFlagGet(ulBase, ulIntType)                                \
        I2CIntFlagGet(ulBase)

//*****************************************************************************
//
//! \brief General slave Interrupt handler for I2C peripheral. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to give a general slave Interrupt handler for I2C 
//! peripheral
//!
//! The \e ulBase can be one of the following values:
//! \b xI2C0_BASE, \b xI2C1_BASE.
//!
//! \note this is only for slave
//!
//! \return None.
//
//*****************************************************************************
#define xI2CSlaveHandler(ulBase)                                              \
        I2CSlaveHandler(ulBase)

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
//! \addtogroup NUC1xx_I2C
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_I2C_STATUS_Type I2C Status Type
//! \brief Values that show I2C Status Type
//! Values that can be passed to UARTIntEnable, I2CIntDisable, and I2CIntClear
//! as the ulIntFlags parameter, and returned from I2CIntStatus.
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
//! Arbitration lost in SLA+R/W as master Own SLA+R has been received, ACK has been returned
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
//! \addtogroup NUC1xx_I2C_Transfer_Type I2C Transfer Type
//! \brief Values that show I2C Transfer Type
//! Values that can be passed to 
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
//! \addtogroup NUC1xx_I2C_General_Call I2C General Call
//! \brief Values that show I2C General Call
//! Values that can be passed to I2CSlaveOwnAddressSet().
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
//! \addtogroup NUC1xx_I2C_Time_Out I2C Time Out
//! \brief Values that show I2C Time Out
//! Values that can be passed to I2CTimeoutCounterSet().
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
//! \addtogroup NUC1xx_I2C_INT_Type I2C Interrupt Type
//! \brief Values that show I2C Interrupt Type
//! Values that can be passed to I2CIntEnable(),I2CIntDisable().
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
//! \addtogroup NUC1xx_I2C_Exported_Types NUC1xx I2C Exported Types
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
//! \addtogroup NUC1xx_I2C_Exported_APIs NUC1xx I2C API
//! \brief NUC1xx I2C API Reference.
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
extern xtBoolean I2CMasterCheckSlave(unsigned long ulBase, 
                                     tI2CMasterTransferCfg *tCfg);

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


