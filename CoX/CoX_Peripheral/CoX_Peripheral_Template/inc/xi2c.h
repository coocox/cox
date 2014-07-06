//*****************************************************************************
//
//! \file      xi2c.h
//! \brief     Prototypes for the I2C Driver.
//! \version   V2.2.1.0
//! \date      $CURRENTTIME$
//! \author    CooCox
//! \copyright
//!
//! Copyright (c)  2014, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
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
//! THE POSPIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

#ifndef __XI2C_H__
#define __XI2C_H__

#include "i2c.h"
#include "CoX_base.h"

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
//! \addtogroup CoX_Peripheral_Interface
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
//! \addtogroup xI2C_INT_Master xI2C Master Interrupt
//!
//! \section xI2C_INT_Master_section 1. Where to use this group
//! This is use to enable or disable the i2c master interrupt.
//! Values that can be passed to
//! \ref xI2CMasterIntEnable \ref xI2CMasterIntDisable
//! as the ulIntType parameter
//!
//! \section xGPIO_Config_CoX 2.CoX Port Details
//! This is the xI2C Master Interrupt in CoX. It show as same Macro name \ref xI2C_MASTER_INT_DATA
//! in all series of CoX implementation.
//!
//! |  xI2C Master Interrupts  |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xI2C_MASTER_INT_DATA    |    Mandatory   |            Y           |
//!
//! more please refer to [xI2C Master Interrupt in MD file](@ref xI2C_INT_Master_md).
//!
//! @{
//
//*****************************************************************************

//
// Transmit / Receive a data, or an error occurs
//
#define xI2C_MASTER_INT_DATA    I2C_MASTER_INT_DATA

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_Event_Master xI2C Master Event
//!
//! |  xI2C Master Event       |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xI2C_MASTER_EVENT_TX    |    Mandatory   |            Y           |
//! |  xI2C_MASTER_EVENT_RX    |    Mandatory   |            Y           |
//!
//! more please refer to [xI2C Master Event in MD file](@ref xI2C_Event_Master_md).
//!
//! @{
//
//*****************************************************************************

//
// Transmit address/data, or some error occurs
//
#define xI2C_MASTER_EVENT_TX    I2C_MASTER_EVENT_TX

//
// Receive a data, or some error occurs
//
#define xI2C_MASTER_EVENT_RX    I2C_MASTER_EVENT_RX

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_INT_Slave xI2C Slave Interrupt
//! \brief      Slave Interrupt event
//!
//! |  xI2C Slave Interrupts   |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xI2C_SLAVE_INT_DATA     |    Mandatory   |            Y           |
//! |  xI2C_SLAVE_INT_START    |    Optional    |            N           |
//! |  xI2C_SLAVE_INT_STOP     |    Optional    |            N           |
//! more please refer to [xI2C Slave Interrupt in MD file](@ref xI2C_INT_Slave_md).
//!
//! @{
//
//*****************************************************************************

//
//! A data received or data requested or error occurs
//
#define xI2C_SLAVE_INT_DATA     I2C_SLAVE_INT_DATA

#define xI2C_SLAVE_INT_START    I2C_SLAVE_INT_START

#define xI2C_SLAVE_INT_STOP     I2C_SLAVE_INT_STOP


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_Event_Slave xI2C Slave Event
//!
//! |  xI2C Slave Event        |       CoX      |         LPC17xx        |
//! |--------------------------|----------------|------------------------|
//! |  xI2C_SLAVE_EVENT_START  |    Optional    |            N           |
//! |  xI2C_SLAVE_EVENT_STOP   |    Optional    |            N           |
//! |  xI2C_SLAVE_EVENT_TREQ   |    Mandatory   |            Y           |
//! |  xI2C_SLAVE_EVENT_RREQ   |    Mandatory   |            Y           |
//! more please refer to [xI2C Slave Event in MD file](@ref xI2C_Event_Slave_md).
//!
//! @{
//
//*****************************************************************************

//
//! Start Condition
//
#define xI2C_SLAVE_EVENT_START  I2C_SLAVE_EVENT_START

//
//! Stop Condition
//
#define xI2C_SLAVE_EVENT_STOP   I2C_SLAVE_EVENT_STOP

//
//! Transmit Request( or address matched in slave transmit mode)
//
#define xI2C_SLAVE_EVENT_TREQ   I2C_SLAVE_EVENT_TREQ

//
//! Receive Request
//
#define xI2C_SLAVE_EVENT_RREQ   I2C_SLAVE_EVENT_RREQ

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_Master_Error xI2C Master Error
//!
//! |  xI2C Master Error        |       CoX      |         LPC17xx        |
//! |---------------------------|----------------|------------------------|
//! |  xI2C_MASTER_ERR_NONE     |    Mandatory   |            Y           |
//! |  xI2C_MASTER_ERR_ADDR_ACK |    Mandatory   |            Y           |
//! |  xI2C_MASTER_ERR_DATA_ACK |    Mandatory   |            Y           |
//! |  xI2C_MASTER_ERR_ARB_LOST |    Mandatory   |            Y           |
//! more please refer to [xI2C Master Error in MD file](@ref xI2C_Master_Error_md).
//!
//! @{
//
//*****************************************************************************

//
//! Every thing is OK
//
#define xI2C_MASTER_ERR_NONE    I2C_MASTER_ERR_NONE

//
//! The transmitted address was not acknowledged
//
#define xI2C_MASTER_ERR_ADDR_ACK I2C_MASTER_ERR_ADDR_ACK


//
//! The transmitted data was not acknowledged.
//
#define xI2C_MASTER_ERR_DATA_ACK I2C_MASTER_ERR_DATA_ACK


//
//! The I2C controller lost arbitration
//
#define xI2C_MASTER_ERR_ARB_LOST I2C_MASTER_ERR_ARB_LOST

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_General_Call xI2C General Call
//! \brief      Values that show xI2C General Call
//!
//! \section    xI2C_Transfer_Type_Section 1. Where to use this group
//!             Values that can be passed to xI2CSlaveInit() as the
//!             ulGeneralCall parameter.
//!
//! \section    xI2C_Transfer_Type_CoX     2. CoX Mandatory and CoX Non-mandatory
//!
//! |  xI2C General Call      |      CoX      |          LPC17xx          |
//! |-------------------------|---------------|---------------------------|
//! |  xI2C_GENERAL_CALL_DIS  |   Mandatory   |             Y             |
//! |  xI2C_GENERAL_CALL_EN   | Non-Mandatory |             Y             |
//! more please refer to [xI2C General Call in MD file](@ref xI2C_General_Call_md).
//!
//! @{
//
//*****************************************************************************

//! Enable I2C general call function.
#define xI2C_GENERAL_CALL_EN                  I2C_GENERAL_CALL_EN

//! Disable I2C general call function.
#define xI2C_GENERAL_CALL_DIS                 I2C_GENERAL_CALL_DIS

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_Exported_APIs xI2C API
//! \brief      xI2C API Reference.
//!
//! \section    xI2C_Exported_APIs_Port CoX Port Details
//!
//! |       xI2C API                     |     CoX      |    LPC17xx         |
//! |------------------------------------|--------------|--------------------|
//! | \ref  xI2CMasterInit               |  Mandatory   |        Y           |
//! | \ref  xI2CMasterEnable             |  Mandatory   |        Y           |
//! | \ref  xI2CMasterDisable            |  Mandatory   |        Y           |
//! | \ref  xI2CMasterBusBusy            |  Mandatory   |        Y           |
//! | \ref  xI2CMasterBusy               |  Mandatory   |        Y           |
//! | \ref  xI2CMasterError              |  Mandatory   |        Y           |
//! | \ref  xI2CMasterDataPut            |  Mandatory   |        Y           |
//! | \ref  xI2CMasterDataGet            |  Mandatory   |        Y           |
//! | \ref  xI2CMasterStop               |  Mandatory   |        Y           |
//! | \ref  xI2CMasterWriteRequestS1     |  Mandatory   |        Y           |
//! | \ref  xI2CMasterWriteRequestS2     |  Mandatory   |        Y           |
//! | \ref  xI2CMasterWriteS1            |  Mandatory   |        Y           |
//! | \ref  xI2CMasterWriteS2            |  Mandatory   |        Y           |
//! | \ref  xI2CMasterWriteBufS1         |  Mandatory   |        Y           |
//! | \ref  xI2CMasterWriteBufS2         |  Mandatory   |        Y           |
//! | \ref  xI2CMasterReadRequestS1      |  Mandatory   |        Y           |
//! | \ref  xI2CMasterReadRequestS2      |  Mandatory   |        Y           |
//! | \ref  xI2CMasterReadLastRequestS2  |  Mandatory   |        Y           |
//! | \ref  xI2CMasterReadS1             |  Mandatory   |        Y           |
//! | \ref  xI2CMasterReadS2             |  Mandatory   |        Y           |
//! | \ref  xI2CMasterReadBufS1          |  Mandatory   |        Y           |
//! | \ref  xI2CMasterReadBufS2          |  Mandatory   |        Y           |
//! | \ref  xI2CMasterIntEnable          |  Mandatory   |        Y           |
//! | \ref  xI2CMasterIntDisable         |  Mandatory   |        Y           |
//! | \ref  xI2CMasterIntFlagGet         |  Mandatory   |        Y           |
//! | \ref  xI2CSlaveIntEnable           |  Mandatory   |        Y           |
//! | \ref  xI2CSlaveIntDisable          |  Mandatory   |        Y           |
//! | \ref  xI2CSlaveIntFlagGet          |  Mandatory   |        Y           |
//! | \ref  xI2CSlaveInit                |  Mandatory   |        Y           |
//! | \ref  xI2CSlaveEnable              |  Mandatory   |        Y           |
//! | \ref  xI2CSlaveDisable             |  Mandatory   |        Y           |
//! | \ref  xI2CIntCallbackInit          |  Mandatory   |        Y           |
//! | \ref  xI2CSlaveDataPut             |  Mandatory   |        Y           |
//! | \ref  xI2CSlaveDataGet             |  Mandatory   |        Y           |
//! more please refer to [xI2C API in MD file](@ref xI2C_Exported_APIs_md).
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief  Initialize the I2C controller.
//!         This function initializes operation of the I2C Master block.
//!         Upon successful initialization of the I2C block, this function will
//!         have set the bus speed for the master, and will have enabled the I2C
//!         Master block.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] ulI2CClk is the I2C clock bit rate.
//!              0 < ulI2CClk <= 400000
//!
//! \return None.
//
//*****************************************************************************
extern void xI2CMasterInit(unsigned long ulBase, unsigned long ulI2CClk);

//*****************************************************************************
//
//! \brief  Enables the I2C Master block.
//!         This function will enable operation of the I2C Master block.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \return None.
//
//*****************************************************************************
extern void xI2CMasterEnable(unsigned long ulBase);

//*****************************************************************************
//
//! \brief  Disables the I2C master block.
//!         This function will disable operation of the I2C Master block.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \return None.
//
//*****************************************************************************
extern void xI2CMasterDisable(unsigned long ulBase);

//*****************************************************************************
//
//! \brief Enables the I2C Slave block.
//!        This will enable operation of the I2C Slave block.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \return None.
//
//*****************************************************************************
extern void xI2CSlaveEnable(unsigned long ulBase);

//*****************************************************************************
//
//! \brief Disables the I2C slave block.
//!        This will disable operation of the I2C slave block.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \return None.
//
//*****************************************************************************
extern void xI2CSlaveDisable(unsigned long ulBase);

//*****************************************************************************
//
//! \brief  Indicates whether or not the I2C bus is busy.
//!         This function returns an indication of whether or not the I2C bus
//!         is busy. This function can be used in a multi-master environment to
//!         determine if another master is currently using the bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \return The I2C bus status:
//!         - xtrue    if I2C bus is busy.
//!         - xfalse   if I2C bus is free.
//
//*****************************************************************************
extern xtBoolean xI2CMasterBusBusy(unsigned long ulBase);

//*****************************************************************************
//
//! \brief  Indicates whether or not the I2C Master is busy.
//!         This function returns an indication of whether or not the I2C Master
//!         is busy transmitting or receiving data.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \return The I2C bus status:
//!         - xtrue    if I2C bus is busy.
//!         - xfalse   if I2C bus is free.
//
//*****************************************************************************
extern xtBoolean xI2CMasterBusy(unsigned long ulBase);

//*****************************************************************************
//
//! \brief  Register user interrupt callback ISR for the I2C module.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] xtI2CCallback is user callback for the specified I2C Port.
//!
//! \return None.
//
//*****************************************************************************
extern void xI2CIntCallbackInit(unsigned long ulBase,
                                xtEventCallback xtI2CCallback);

//*****************************************************************************
//
//! \brief Slave Send a byte to I2C bus.
//!        This function is to send a byte on specified I2C BUS.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] ucData specifies the data which will send to I2C BUS.
//!
//! \return None.
//!
//! \note   This is only for slave
//
//*****************************************************************************
extern void xI2CSlaveDataPut(unsigned long ulBase, unsigned char ucData);

//*****************************************************************************
//! \brief Slave receive a byte to I2C bus.
//!        This function is to receive a byte on specified I2C BUS.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \return None.
//!
//! \note   This is only for slave
//
//*****************************************************************************
extern unsigned long xI2CSlaveDataGet(unsigned long ulBase);

//*****************************************************************************
//
//! \brief  Enables the I2C Master interrupt.
//!         Enables the I2C Master interrupt source.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] ulIntType is the interrupt type of the I2C module.
//!              which can be one of the following value:
//!              - \ref xI2C_MASTER_INT_DATA
//!
//! \return None.
//
//*****************************************************************************
extern void xI2CMasterIntEnable(unsigned long ulBase, unsigned long ulIntType);

//*****************************************************************************
//
//! \brief  Disables the I2C Master interrupt.
//!         Disables the I2C Master interrupt source.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] ulIntType is the interrupt type of the I2C module.
//!
//! \return None.
//
//*****************************************************************************
extern void xI2CMasterIntDisable(unsigned long ulBase, unsigned long ulIntType);

//*****************************************************************************
//
//! \brief  Initialize I2C slave function.
//!         This function is to 7-bit slave addresses and enable General Call
//!         function of specified I2C port.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] ucSlaveAddr specifies the slave address.
//!              The ucSlaveAddr can be a 7-bit value.
//! \param  [in] ulGeneralCall specifies enable General Call function or not.
//!              The ulGeneralCall can be one of the following values:
//!                - \ref xI2C_GENERAL_CALL_EN
//!                - \ref xI2C_GENERAL_CALL_DIS.
//!
//! \return None.
//!
//! \note   This function is only suit for I2C slave mode.
//
//*****************************************************************************
extern void xI2CSlaveInit(unsigned long ulBase,
                          unsigned char ucSlaveAddr,
                          unsigned long ulGeneralCall);

//*****************************************************************************
//
//! \brief  Enables the I2C Slave interrupt.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] ulIntType is the interrupt type of the I2C module.
//!              This value can be one of the following value:
//!              - \ref xI2C_SLAVE_INT_STOP
//!              - \ref xI2C_SLAVE_INT_DATA
//!
//! \return None.
//
//*****************************************************************************
extern void xI2CSlaveIntEnable(unsigned long ulBase, unsigned long ulIntType);

//*****************************************************************************
//
//! \brief  Disables the I2C Slave interrupt.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] ulIntType is the interrupt type of the I2C module.
//!              This value can be one of the following value:
//!              - \ref xI2C_SLAVE_INT_STOP
//!              - \ref xI2C_SLAVE_INT_DATA
//!
//! \return None.
//
//*****************************************************************************
extern void xI2CSlaveIntDisable(unsigned long ulBase, unsigned long ulIntType);

//*****************************************************************************
//
//! \brief  Gets the error status of the I2C Master module.
//!         This function is used to obtain the error status of the Master module
//!         send and receive operations.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \return Returns the error status, can be one of the following value:
//!         - \ref I2C_MASTER_ERR_NONE
//!         - \ref I2C_MASTER_ERR_ADDR_ACK
//!         - \ref I2C_MASTER_ERR_DATA_ACK
//!         - \ref I2C_MASTER_ERR_ARB_LOST
//
//*****************************************************************************
extern unsigned long xI2CMasterError(unsigned long ulBase);

//*****************************************************************************
//
//! \brief  Transfer an byte on the I2C bus.
//!         This function will put an byte into I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] ucData data to be transmitted from the I2C Master
//!
//! \return None.
//
//*****************************************************************************
extern void xI2CMasterDataPut(unsigned long ulBase, unsigned char ucData);

//*****************************************************************************
//
//! \brief  Receive an byte on the I2C bus.
//!         This function will get an byte into I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \return The data received from I2C bus.
//!
//
//*****************************************************************************
extern unsigned long xI2CMasterDataGet(unsigned long ulBase);

//*****************************************************************************
//
//! \brief  Transmite the STOP condition, master goes to idle state.
//!         This function free the I2C bus. When the master no longer need send
//!         or receive any more data, or need to terminate this transmition after
//!         getting some errors, call this function.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \return None.
//
//*****************************************************************************
extern void xI2CMasterStop(unsigned long ulBase);

//*****************************************************************************
//
//! Gets the current I2C Master status.
//!
//! \param ulBase is the base address of the I2C module.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! This function reads the bytes of data from the I2C Master status Register.
//!
//! \return Returns the bytes(unsigned long) of I2C Master status Register.
//
//*****************************************************************************
extern unsigned long xI2CMasterIntFlagGet(unsigned long ulBase);

//*****************************************************************************
//
//! \brief  Send a master transmit request when the bus is idle.(Write Step1)
//!
//!         This function init a new write transmition. When the master have
//!         not obtained control of the bus, This function send request to
//!         transmit the START condition, the slave address and the data, Then
//!         it returns immediately, no waiting any bus transmition to complete.
//!
//!         Users can call xI2CMasterBusy() to check if all the bus transmition
//!         complete, the call xI2CMasterError() to check if any error occurs.
//!
//!         After the master obtained control of the bus, and haven't release it,
//!         users can call xI2CMasterWriteRequestS2() to continue transmit data
//!         to slave.  Users can also call xI2CMasterStop() to terminate this
//!         transmition and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] ucSlaveAddr is the 7-bit slave address.
//! \param  [in] ucData is the byte to transmit.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP condition
//!              and terminate this transmition.
//!
//! \return None.
//!
//! \note   For this function returns immediately, it is always using in the
//!         interrupt handler.
//
//*****************************************************************************
extern void xI2CMasterWriteRequestS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                                     unsigned char ucData, xtBoolean bEndTransmition);

//*****************************************************************************
//
//! \brief  Send a master data transmit request when the master have obtained
//!         control of the bus.(Write Step2)
//!
//!         After the master obtained control of the bus(have called
//!         xI2CMasterWriteRequestS1() without any error), and haven't release it,
//!         users can call this function to continue transmit data to slave.
//!
//!         This function just send request to transmit the data, and it returns
//!         immediately, no waiting any bus transmition to complete.
//!
//!         Users can call xI2CMasterBusy() to check if all the bus transmition
//!         complete, the call xI2CMasterError() to check if any error occurs.
//!         Users call also can xI2CMasterStop() to terminate this transmition
//!         and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] ucData is the byte to transmit.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP condition
//!              and terminate this transmition.
//!
//! \return None.
//! \note   For this function returns immediately, it is always using in the interrupt
//!         handler.
//
//*****************************************************************************
extern void xI2CMasterWriteRequestS2(unsigned long ulBase, unsigned char ucData,
                                     xtBoolean bEndTransmition);

//*****************************************************************************
//
//! \brief  Write a data to the slave when the bus is idle, and waiting for all
//!         bus transmiton complete.(Write Step1)
//!
//!         This function init a new write transmition. When the master have not
//!         obtained control of the bus, This function transmit the START condition,
//!         the slave address and the data, then waiting for all bus transmition
//!         complete.
//!
//!         After the master obtained control of the bus, and haven't release it,
//!         users can call xI2CMasterWriteS2() to continue transmit data to slave.
//!         Users call also can xI2CMasterStop() to terminate this transmition and
//!         release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] ucSlaveAddr is the 7-bit slave address.
//! \param  [in] ucData is the byte to transmit.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP condition
//!              and terminate this transmition.
//!
//! \return Returns the master error status.
//!
//! \note   This function is always used in thread mode.
//
//*****************************************************************************
extern unsigned long xI2CMasterWriteS1(unsigned long ulBase,
                                       unsigned char ucSlaveAddr,
						               unsigned char ucData,
							           xtBoolean bEndTransmition);
								   
//*****************************************************************************
//
//! \brief  Write a data to the slave, when the master have obtained control of
//!         the bus, and waiting for all bus transmiton complete.(Write Step2)
//!
//!         After the master obtained control of the bus(have called
//!         xI2CMasterWriteS1() without any error), and haven't release it,
//!         users can call this function to continue transmit data to slave.
//!
//!         This function transmit the data to the slave, and waiting for all bus
//!         transmition complete.
//!
//!         Then users can call this function to continue transmit data to slave.
//!         Users call also call xI2CMasterStop() to terminate this transmition
//!         and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] ucData is the byte to transmit.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP condition
//!              and terminate this transmition.
//!
//! \return Returns the master error status.
//! \note   This function is always used in thread mode.
//
//*****************************************************************************
extern unsigned long xI2CMasterWriteS2(unsigned long ulBase,
						               unsigned char ucData,
							           xtBoolean bEndTransmition);

//*****************************************************************************
//
//! \brief  Write a data buffer to the slave when the bus is idle, and waiting
//!         for all bus transmiton complete.(Write Buffer Step1)
//!
//!         This function init a new data buffer write transmition. When the
//!         master have not obtained control of the bus, This function transmit
//!         the START condition, the slave address and the data, then waiting for
//!         the data transmition complete, and continue next data transmition,
//!         until all complete. If there is any error occurs, the remain data
//!         will be canceled.
//!
//!         Users can then check the return value to see how many datas have
//!         been successfully transmited. if the number != ulLen, user can call
//!         xI2CMasterError() to see what error occurs.
//!
//!         After the master obtained control of the bus, and haven't release it,
//!         users can call xI2CMasterWriteS2()/xI2CMasterWriteBufS2() to continue
//!         transmit data to slave. Users call also call xI2CMasterStop() to
//!         terminate this transmition and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] ucSlaveAddr is the 7-bit slave address.
//! \param  [in] pucDataBuf is the data buffer to transmit.
//! \param  [in] ulLen is the data buffer byte size.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP condition
//!              and terminate this transmition.
//!
//! \return Returns the data number that have been successully tranmited.
//!
//! \note   This function is always used in thread mode.
//
//*****************************************************************************

extern unsigned long xI2CMasterWriteBufS1(unsigned long ulBase,
                                          unsigned char ucSlaveAddr,
						                  unsigned char *pucDataBuf,
						                  unsigned long ulLen,
							              xtBoolean bEndTransmition);

//*****************************************************************************
//
//! \brief  Write a data buffer to the slave, when the master have obtained
//!         control of the bus, and waiting for all bus transmiton complete.
//!         (Write Buffer Step2)
//!
//!         After the master obtained control of the bus(have called xI2CMasterWriteS1()
//!         or xI2CMasterWriteBufS1() without any error), and haven't release it,
//!         users can call this function to continue transmit data to slave.
//!
//!         This function transmit the data one by one to the slave, waiting for
//!         every data transmition complete, and continue next data transmition,
//!         until all complete. If there is any error occurs, the remain data will
//!         be canceled.
//!
//!         Users can then check the return value to see how many datas have been
//!         successfully transmited. if the number != ulLen, user can call
//!         xI2CMasterError() to see what error occurs.
//!
//!         Then users can call xI2CMasterWriteS2() or this function to continue
//!         transmit data to slave. Users call also call xI2CMasterStop() to terminate
//!         this transmition and release the I2C bus.!
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] pucDataBuf is the data buffer to transmit.
//! \param  [in] ulLen is the data buffer byte size.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP condition
//!              and terminate this transmition.
//!
//! \return Returns the data number that have been successully tranmited.
//!
//! \note   This function is always used in thread mode.
//
//*****************************************************************************
extern unsigned long xI2CMasterWriteBufS2(unsigned long ulBase,
						                  unsigned char *pucDataBuf,
						                  unsigned long ulLen,
							              xtBoolean bEndTransmition);

//*****************************************************************************
//
//! \brief  Send a master receive request when the bus is idle.(Read Step1)
//!
//!         This function init a new receive transmition. When the master have
//!         not obtained control of the bus, This function send request to
//!         transmit the START condition, the slave address and the data request,
//!         Then it returns immediately, no waiting any bus transmition to complete.
//!
//!         If bEndTransmition is xtrue, the receive operation will followed by
//!         an negative ACK and STOP condition.
//!
//!         Users can call xI2CMasterBusy() to check if all the bus transmition
//!         complete, then call xI2CMasterError() to check if any error occurs.
//!         Then user can get the data by calling xI2CMasterDataGet() if there
//!         is no error occurs.
//!
//!         After the master obtained control of the bus, and haven't release it,
//!         users can call xI2CMasterReadRequestS2() to continue receive data from
//!         slave.  Users call also can xI2CMasterStop() to terminate this transmition
//!         and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] ucSlaveAddr is the 7-bit slave address.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP
//!              condition and terminate this transmition.
//!
//! \return None.
//!
//! \note   For this function returns immediately, it is always using in the
//!         interrupt hander.
//
//*****************************************************************************
extern void xI2CMasterReadRequestS1(unsigned long ulBase,
						            unsigned char ucSlaveAddr,
							        xtBoolean bEndTransmition);

//*****************************************************************************
//
//! \brief  Send a master data receive request when the master have obtained
//!         control of the bus.(Write Step2)
//!
//!         After the master obtained control of the bus(have called
//!         xI2CMasterReadRequestS1() without any error), and haven't release it,
//!         users can call this function to continue receive data from slave.
//!
//!         If bEndTransmition is xtrue, the receive operation will followed
//!         by an negative ACK and STOP condition.
//!
//!         Users can call xI2CMasterBusy() to check if all the bus
//!         transmition complete, then call xI2CMasterError() to check if any
//!         error occurs. Then user can get the data by calling xI2CMasterDataGet()
//!         if there is no error occurs.
//!
//!         Then users can call this function to continue receive data
//!         from slave. Users call also can xI2CMasterStop() to terminate
//!         this transmition and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] bEndTransmition is flag to control if transmit the STOP condition and
//!              terminate this transmition.
//!
//! \return None.
//!
//! \note   For this function returns immediately, it is always using in the
//!         interrupt hander.
//
//*****************************************************************************
extern void xI2CMasterReadRequestS2(unsigned long ulBase,
							        xtBoolean bEndTransmition);

//*****************************************************************************
//
//! \brief  Send a master data receive request with an NACK when the master have
//!         obtained control of the bus(Write Step2).
//!
//!         This function is used to request the last data to receive, and
//!         signal the end of the transfer to the slave transmitter. Then
//!         the master can repeat START condition, switch to transmit or
//!         other slaves without lost control of the bus.
//!
//!         Users can call xI2CMasterBusy() to check if all the bus
//!         transmition complete, then call xI2CMasterError() to check
//!         if any error occurs. Then user can get the data by calling
//!         xI2CMasterDataGet() if there is no error occurs.
//!
//!         Users call also can xI2CMasterStop() to terminate this
//!         transmition and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \return None.
//!
//! \note   For this function returns immediately, it is always using in
//!         the interrupt handler.
//
//*****************************************************************************
extern void xI2CMasterReadLastRequestS2(unsigned long ulBase);

//*****************************************************************************
//
//! \brief  Read a data from a slave when the bus is idle, and waiting for all
//!         bus transmiton complete.(Read Step1)
//!
//!         This function init a new receive transmition. When the master have
//!         not obtained control of the bus, This function send request to
//!         transmit the START condition, the slave address and the data
//!         request, then waiting for all bus transmition complete.
//!
//!         If bEndTransmition is xtrue, the receive operation will followed
//!         by an negative ACK and STOP condition.
//!
//!         After the master obtained control of the bus, and haven't release
//!         it, users can call xI2CMasterReadS2() to continue receive data
//!         from slave.  Users call also can xI2CMasterStop() to terminate
//!         this transmition and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] ucSlaveAddr is the 7-bit slave address.
//! \param  [in] pucData is the buffer where to save the data.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP
//!              condition and terminate this transmition.
//!
//! \return Returns the master error status.
//!
//! \note   This function is usually used in thread mode.
//
//*****************************************************************************
extern unsigned long xI2CMasterReadS1(unsigned long ulBase,
                                      unsigned char ucSlaveAddr,
                                      unsigned char *pucData,
                                      xtBoolean bEndTransmition);

//*****************************************************************************
//
//! \brief  Read a data from a slave when the master have obtained control of
//!         the bus, and waiting for all bus transmiton complete.(Read Step2)
//!
//!         After the master obtained control of the bus(have called
//!         xI2CMasterReadS1() without any error), and haven't release
//!         it, users can call this function to continue receive data
//!         from the slave.
//!
//!         If bEndTransmition is xtrue, the receive operation will
//!         followed by an negative ACK and STOP condition.
//!
//!         Then useres can call this function to continue receive
//!         data from slave.  Users call also can xI2CMasterStop()
//!         to terminate this transmition and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [in] pucData is the buffer where to save the data.
//! \param  [in] bEndTransmition is flag to control if transmit the STOP
//!              condition and terminate this transmition.
//!
//!
//! \return Returns the master error status.
//! \note   This function is usually used in thread mode.
//
//*****************************************************************************
extern unsigned long xI2CMasterReadS2(unsigned long ulBase,
                                      unsigned char *pucData,
                                      xtBoolean bEndTransmition);

//*****************************************************************************
//
//! \brief Read some data from a slave when the bus is idle, and waiting for all
//!        bus transmiton complete.(Read Buffer Step1)
//!
//!        This function init a new data buffer receive transmition. When the
//!        master have not obtained control of the bus, This function send request
//!        to transmit the START condition, the slave address and the data request,
//!        then waiting for the data transmition complete, and continue next data
//!        transmition, until all complete. If there is any error occurs, the remain
//!        data will be canceled.
//!
//!        If bEndTransmition is xtrue, the receive operation will followed by an
//!        negative ACK and STOP condition.
//!
//!        Users can then check the return value to see how many datas have been
//!        successfully received. if the number != ulLen, user can call
//!        xI2CMasterError() to see what error occurs.
//!
//!        After the master obtained control of the bus, and haven't release it,
//!        users can call xI2CMasterReadS2() or xI2CMasterReadBufS2() to continue
//!        receive data .  from slave .Users call also can xI2CMasterStop() to
//!        terminate this transmition and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [out] ucSlaveAddr is the 7-bit slave address.
//!
//! \param  [in]  pucDataBuf is the buffer where to save the data.
//!
//! \param  [in]  ulLen is the data number to receive.
//!
//! \param  [in]  bEndTransmition is flag to control if transmit the STOP condition
//!               and terminate this transmition. this value can be one fo the following
//!               value: \ref xtrue, \ref xflase.
//!
//! \return Returns the data number that have been successully received.
//!
//! \note   This function is usually used in thread mode.
//
//*****************************************************************************
extern unsigned long xI2CMasterReadBufS1(unsigned long ulBase,
                                         unsigned char ucSlaveAddr,
                                         unsigned char *pucDataBuf,
                                         unsigned long ulLen,
                                         xtBoolean bEndTransmition);

//*****************************************************************************
//
//! \brief  Read some data from a slave when the master have obtained control of
//!         the bus,and waiting for all bus transmiton complete.(Write Buffer Step2)
//!
//!         After the master obtained control of the bus(have called
//!         xI2CMasterReadS1() or xI2CMasterReadBufS1() without any error), and haven't
//!         release it, users can call this function to continue receive data from slave.
//!
//!         This function receive data one by one from the slave, waiting for every
//!         data transmition complete, and continue next data transmition, until all
//!         complete. If there is any error occurs, the remain data will be canceled.
//!
//!         If bEndTransmition is xtrue, the receive operation will followed by an
//!         negative ACK and STOP condition.
//!
//!         Users can then check the return value to see how many datas have been
//!         successfully received. if the number != ulLen, user can call
//!         xI2CMasterError() to see what error occurs.
//!
//!         After the master obtained control of the bus, and haven't release it, users
//!         can call xI2CMasterReadS2() or xI2CMasterReadBufS2() to continue receive data
//!         from slave. Users call also can xI2CMasterStop() to terminate this transmition
//!         and release the I2C bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! \param  [out] pucDataBuf is the buffer where to save the data.
//!
//! \param  [in]  ulLen is the data number to receive.
//!
//! \param  [in]  bEndTransmition is flag to control if transmit the STOP condition
//!               and terminate this transmition. this value can be one fo the following
//!               value: \ref xtrue, \ref xflase.
//!
//! \return Returns the data number that have been successully received.
//!
//! \note   This function is usually used in thread mode.
//
//*****************************************************************************
extern unsigned long xI2CMasterReadBufS2(unsigned long ulBase,
                                         unsigned char *pucDataBuf,
                                         unsigned long ulLen,
                                         xtBoolean bEndTransmition);

//*****************************************************************************
//
//! Gets the current I2C Slave status.
//!
//! \param ulBase is the base address of the I2C module.
//!              - \ref xI2C0_BASE
//!              - \ref xI2C1_BASE
//!              - \ref xI2C2_BASE
//!              - \ref xI2C3_BASE
//!              - \ref xI2C4_BASE
//!
//! This function reads the bytes of data from the I2C Slave status Register.
//!
//! \return Returns the bytes(unsigned long) of I2C Slave status Register.
//
//*****************************************************************************
extern unsigned char xI2CSlaveIntFlagGet(unsigned long ulBase);

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

#endif // __XI2C_H__
