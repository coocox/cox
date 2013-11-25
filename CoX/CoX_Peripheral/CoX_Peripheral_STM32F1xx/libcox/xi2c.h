//*****************************************************************************
//
//! \file xi2c.h
//! \brief Prototypes for the I2C Driver.
//! \version V2.2.1.0
//! \date 02/06/2011
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
//! THE POSPIBILITY OF SUCH DAMAGE.
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
//! \addtogroup xI2C_INT_Master xI2C Master Interrupt
//! 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xI2C Master Interrupts  |       CoX      |        STM32F1xx       |
//! |------------------------|----------------|------------------------|
//! |xI2C_MASTER_INT_DATA    |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
// Transmit / Receive a data, or an error occurs
//
#define xI2C_MASTER_INT_DATA    I2C_INT_EVT

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_Event_Master xI2C Master Event
//! 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xI2C Master Event       |       CoX      |        STM32F1xx       |
//! |------------------------|----------------|------------------------|
//! |xI2C_MASTER_EVENT_TX    |    Mandatory   |            Y           |
//! |xI2C_MASTER_EVENT_RX    |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
// Transmit address/data, or some error occurs
//
#define xI2C_MASTER_EVENT_TX    0

//
// Receive a data, or some error occurs
//
#define xI2C_MASTER_EVENT_RX    0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_INT_Slave xI2C Slave Interrupt
//! 
//!
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xI2C Slave Interrupts   |       CoX      |        STM32F1xx       |
//! |------------------------|----------------|------------------------|
//! |xI2C_SLAVE_INT_START    |    Optional    |            N           |
//! |xI2C_SLAVE_INT_STOP     |    Optional    |            N           |
//! |xI2C_SLAVE_INT_DATA     |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Start Condition
//
#define xI2C_SLAVE_INT_START   0

//
//! Stop Condition
//
#define xI2C_SLAVE_INT_STOP    0

//
//! A data received or data requested or error occurs
//
#define xI2C_SLAVE_INT_DATA    I2C_INT_EVT


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_Event_Slave xI2C Slave Event
//!
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xI2C Slave Event        |       CoX      |        STM32F1xx       |
//! |------------------------|----------------|------------------------|
//! |xI2C_SLAVE_EVENT_START  |    Optional    |            N           |
//! |xI2C_SLAVE_EVENT_STOP   |    Optional    |            N           |
//! |xI2C_SLAVE_EVENT_TREQ   |    Mandatory   |            Y           |
//! |xI2C_SLAVE_EVENT_RREQ   |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Start Condition
//
#define xI2C_SLAVE_EVENT_START  0

//
//! Stop Condition
//
#define xI2C_SLAVE_EVENT_STOP   I2C_EVENT_STOPF

//
//! Transmit Request( or address matched in slave transmit mode)
//
#define xI2C_SLAVE_EVENT_TREQ   0

//
//! Receive Request
//
#define xI2C_SLAVE_EVENT_RREQ   1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_Master_Error xI2C Master Error
//!
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xI2C Master Error       |       CoX      |        STM32F1xx       |
//! |------------------------|----------------|------------------------|
//! |xI2C_MASTER_ERR_NONE    |    Mandatory   |            Y           |
//! |xI2C_MASTER_ERR_ADDR_ACK|    Mandatory   |            Y           |
//! |xI2C_MASTER_ERR_DATA_ACK|    Mandatory   |            Y           |
//! |xI2C_MASTER_ERR_ARB_LOST|    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
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
#define xI2C_MASTER_ERR_ADDR_ACK                                              \
                                I2C_MASTER_ERR_ADDR_ACK

//
//! The transmitted data was not acknowledged.
//
#define xI2C_MASTER_ERR_DATA_ACK                                              \
                                I2C_MASTER_ERR_DATA_ACK

//
//! The I2C controller lost arbitration
//
#define xI2C_MASTER_ERR_ARB_LOST                                              \
                                I2C_MASTER_ERR_ARB_LOST

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
//! Values that can be passed to xI2CSlaveIntInit()
//! as the ulGeneralCall parameter. 
//! \n
//! \section xI2C_Transfer_Type_CoX 2.CoX Mandatory and CoX Non-mandatory 
//! \verbatim
//! +------------------------+----------------+---------------------------+
//! |xI2C General Call       |       CoX      |         STM32F1xx         |
//! |------------------------|----------------|---------------------------|
//! |xI2C_GENERAL_CALL_DIS   |    Mandatory   |             Y             |
//! |------------------------|----------------|---------------------------|
//! |xI2C_GENERAL_CALL_EN    |  Non-Mandatory |             Y             |
//! |------------------------|----------------|---------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************
#define xI2C_GENERAL_CALL_EN    0x00000040
#define xI2C_GENERAL_CALL_DIS   0x00000000
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
//! +----------------------------+----------------+------------------------+
//! |xI2C API                    |       CoX      |       STM32F1xx        |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterInit              |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterEnable            |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterDisable           |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterBusBusy           |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterBusy              |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterError             |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterDataPut           |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterDataGet           |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterStop              |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterWriteRequestS1    |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterWriteRequestS2    |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterWriteS1           |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterWriteS2           |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterWriteBufS1        |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterWriteBufS2        |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterReadRequestS1     |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterReadRequestS2     |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterReadLastRequestS2 |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterReadS1            |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterReadS2            |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterReadBufS1         |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterReadBufS2         |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterIntEnable         |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CMasterIntDisable        |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CSlaveIntEnable          |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CSlaveIntDisable         |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CSlaveIntInit            |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CSlaveEnable             |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CSlaveDisable            |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CIntCallbackInit         |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CSlaveDataPut            |    Mandatory   |            Y           |
//! |----------------------------|----------------|------------------------|
//! |xI2CSlaveDataGet            |    Mandatory   |            Y           |
//! +----------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Initialize the I2C controller.
//!
//! \param ulBase is the I2C module base address.
//! \param ulI2CClk is the I2C clock bit rate.
//!
//! This function initializes operation of the I2C Master block.  Upon
//! successful initialization of the I2C block, this function will have set the
//! bus speed for the master, and will have enabled the I2C Master block.
//!
//! The parameter \e ulBase can be:
//! - \ref xI2C0_BASE
//! - \ref xI2C1_BASE
//!
//! The parameter \e ulI2CClk can only be:
//! - \b 100000 - I2C works under standard-mode (Sm), with a bit rate up to 
//!               100 kbit/s
//! - \b 400000 - I2C works under fast-mode (Fm), with a bit rate up to 
//!               400 kbit/s
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterInit(ulBase, ulI2CClk)                                      \
        do                                                                    \
        {                                                                     \
            I2CMasterInit(ulBase, SysCtlAPB1ClockGet(),                       \
                (ulI2CClk == 400000) ? xtrue : xfalse, xtrue);                \
        }while(0)                                     

//*****************************************************************************
//
//! \brief Enables the I2C Master block.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This will enable operation of the I2C Master block.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterEnable(ulBase)                                              \
        I2CMasterEnable(ulBase)

//*****************************************************************************
//
//! \brief Disables the I2C master block.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This will disable operation of the I2C master block.
//!
//! \return None.
//
//*****************************************************************************            
#define xI2CMasterDisable(ulBase)                                             \
        I2CMasterDisable(ulBase)

//*****************************************************************************
//
//! \brief Enables the I2C Slave block.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This will enable operation of the I2C Slave block.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CSlaveEnable(ulBase)                                              \
        I2CMasterEnable(ulBase)

//*****************************************************************************
//
//! \brief Disables the I2C slave block.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This will disable operation of the I2C slave block.
//!
//! \return None.
//
//*****************************************************************************            
#define xI2CSlaveDisable(ulBase)                                             \
        I2CMasterDisable(ulBase)

//*****************************************************************************
//
//! \brief Indicates whether or not the I2C bus is busy.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This function returns an indication of whether or not the I2C bus is busy.
//! This function can be used in a multi-master environment to determine if
//! another master is currently using the bus.
//!
//! \return Returns \b xtrue if the I2C bus is busy; otherwise, returns
//! \b xfalse.
//
//*****************************************************************************
#define xI2CMasterBusBusy(ulBase)                                             \
        I2CMasterBusBusy(ulBase)

//*****************************************************************************
//
//! \brief Indicates whether or not the I2C Master is busy.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function returns an indication of whether or not the I2C Master is
//! busy transmitting or receiving data.
//!
//! \return Returns \b xtrue if the I2C Master is busy; otherwise, returns
//! \b xfalse.
//
//*****************************************************************************
#define xI2CMasterBusy(ulBase)                                                \
        I2CBusBusy(ulBase)

//*****************************************************************************
//
//! \brief Init interrupts callback for the specified I2C Port.
//!
//! \param ulPort is the base address of the I2C port.
//! \param xtI2CCallback is callback for the specified I2C Port.
//!
//! Init interrupts callback for the specified I2C Port.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CIntCallbackInit(ulBase, xtI2CCallback)                            \
        I2CIntCallbackInit(ulBase, xtI2CCallback)

//*****************************************************************************
//! \brief Slave Send a byte to I2C bus. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ucData specifies the data which will send to I2C BUS.
//!
//! This function is to send a byte on specified I2C BUS.
//!
//! The \e ulBase can be one of the following values:
//! \b xI2C1_BASE, \b xI2C2_BASE.
//!
//! \note This is only for slave
//!
//! \return None.
//
//*****************************************************************************

#define xI2CSlaveDataPut(ulBase, ucData)                                      \
        I2CDataPut(ulBase, ucData)


//*****************************************************************************
//! \brief Slave receive a byte to I2C bus. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to receive a byte on specified I2C BUS.
//!
//! The \e ulBase can be one of the following values:
//! \b xI2C1_BASE, \b xI2C2_BASE.
//!
//! \note This is only for slave
//!
//! \return None.
//
//*****************************************************************************

#define xI2CSlaveDataGet(ulBase)                                              \
        I2CDataGet(ulBase)

//*****************************************************************************
//
//! Enables the I2C Master interrupt.
//!
//! \param ulBase is the base address of the I2C module.
//! \param ulIntType is the interrupt type of the I2C module.
//!
//! The \e ulIntType is the interrupt type of the I2C module.
//!
//! Enables the I2C Master interrupt source.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterIntEnable(ulBase, ulIntType)                                \
        I2CIntEnable(ulBase, ulIntType)

//*****************************************************************************
//
//! Disables the I2C Master interrupt.
//!
//! \param ulBase is the base address of the I2C module.
//! \param ulIntType is the interrupt type of the I2C module.
//!
//! The \e ulIntType is the interrupt type of the I2C module.
//!
//! Disables the I2C Master interrupt source.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterIntDisable(ulBase, ulIntType)                               \
        I2CIntDisable(ulBase, ulIntType)

//*****************************************************************************
//
//! Enables the I2C Slave interrupt.
//!
//! \param ulBase is the base address of the I2C module.
//! \param ulIntType is the interrupt type of the I2C module.
//!
//! The \e ulIntType is the interrupt type of the I2C module.
//!
//! Enables the I2C Slave interrupt source.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CSlaveIntEnable(ulBase, ulIntType)                                 \
        I2CIntEnable(ulBase, ulIntType)
        
//*****************************************************************************
//
//! Disables the I2C Slave interrupt.
//!
//! \param ulBase is the base address of the I2C module.
//! \param ulIntType is the interrupt type of the I2C module.
//!
//! The \e ulIntType is the interrupt type of the I2C module.
//!
//! Disables the I2C slave interrupt source.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CSlaveIntDisable(ulBase, ulIntType)                               \
        I2CIntDisable(ulBase, ulIntType)

//*****************************************************************************
//
//! Gets the error status of the I2C Master module.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function is used to obtain the error status of the Master module send
//! and receive operations.
//!
//! \return Returns the error status, as one of \b I2C_MASTER_ERR_NONE,
//! \b I2C_MASTER_ERR_ADDR_ACK, \b I2C_MASTER_ERR_DATA_ACK, or
//! \b I2C_MASTER_ERR_ARB_LOST.
//
//*****************************************************************************
#define xI2CMasterError(ulBase)                                               \
        I2CMasterErr(ulBase)

//*****************************************************************************
//
//! Transmits a byte from the I2C Master.
//!
//! \param ulBase is the base address of the I2C module.
//! \param ucData data to be transmitted from the I2C Master
//!
//! This function will place the supplied data into I2C Master Data Register.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterDataPut(ulBase, ucData)                                     \
        I2CDataPut(ulBase, ucData)

//*****************************************************************************
//
//! Receives a byte that has been sent to the I2C Master.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This function reads a byte of data from the I2C Master Data Register.
//!
//! \return Returns the byte(unsigned char) received from by the I2C Master.
//
//*****************************************************************************
#define xI2CMasterDataGet(ulBase)                                             \
        I2CDataGet(ulBase)

//*****************************************************************************
//
//! \brief Transmite the STOP condition, master goes to idle state.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function free the I2C bus. When the master no longer need send or 
//! receive any more data, or need to terminate this transmition after getting
//! some errors, call this function.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterStop(ulBase)                                                \
        I2CStopSend(ulBase)

//*****************************************************************************
//
//! \brief Send a master transmit request when the bus is idle.(Write Step1)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr is the 7-bit slave address.
//! \param ucData is the byte to transmit.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! This function init a new write transmition. When the master have not obtained
//! control of the bus, This function send request to transmit the START 
//! condition, the slave address and the data, Then it returns immediately, no 
//! waiting any bus transmition to complete. 
//!
//! Users can call xI2CMasterBusy() to check if all the bus  transmition
//! complete, the call xI2CMasterError() to check if any error occurs. 
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call xI2CMasterWriteRequestS2() to continue transmit data to slave.
//! Users can also call xI2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! For this function returns immediately, it is always using in the interrupt
//! handler.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterWriteRequestS1(ulBase, ucSlaveAddr, ucData, bEndTransmition) \
        I2CMasterWriteRequestS1(ulBase, ucSlaveAddr, ucData, bEndTransmition)

//*****************************************************************************
//
//! \brief Send a master data transmit request when the master have obtained 
//! control of the bus.(Write Step2)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucData is the byte to transmit.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! After the master obtained control of the bus(have called  
//! xI2CMasterWriteRequestS1() without any error), and haven't release it, users 
//! can call this function to continue transmit data to slave.
//!
//! This function just send request to transmit the data, and it returns 
//! immediately, no waiting any bus transmition to complete. 
//!
//! Users can call xI2CMasterBusy() to check if all the bus transmition 
//! complete, the call xI2CMasterError() to check if any error occurs. Users call
//! also can xI2CMasterStop() to terminate this transmition and release the 
//! I2C bus.
//!
//! For this function returns immediately, it is always using in the interrupt
//! handler.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterWriteRequestS2(ulBase, ucData, bEndTransmition)             \
        I2CMasterWriteRequestS2(ulBase, ucData, bEndTransmition)

//*****************************************************************************
//
//! \brief Write a data to the slave when the bus is idle, and waiting for all 
//! bus transmiton complete.(Write Step1)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr is the 7-bit slave address.
//! \param ucData is the byte to transmit.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! This function init a new write transmition. When the master have not obtained
//! control of the bus, This function transmit the START condition, the slave 
//! address and the data, then waiting for all bus transmition complete.
//!
//! Users can then check the return value to see if any error occurs:
//! - \ref xI2C_MASTER_ERR_NONE     - \b 0, no error
//! - \ref xI2C_MASTER_ERR_ADDR_ACK - The transmitted address was not acknowledged
//! - \ref xI2C_MASTER_ERR_DATA_ACK - The transmitted data was not acknowledged
//! - \ref xI2C_MASTER_ERR_ARB_LOST - The I2C controller lost arbitration.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call xI2CMasterWriteS2() to continue transmit data to slave.
//! Users call also can xI2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! This function is always used in thread mode.
//!
//! \return Returns the master error status.
//
//*****************************************************************************
#define xI2CMasterWriteS1(ulBase, ucSlaveAddr, ucData, bEndTransmition)       \
        I2CMasterWriteS1(ulBase, ucSlaveAddr, ucData, bEndTransmition)

//*****************************************************************************
//
//! \brief Write a data to the slave, when the master have obtained control of 
//! the bus, and waiting for all bus transmiton complete.(Write Step2)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucData is the byte to transmit.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! After the master obtained control of the bus(have called  
//! xI2CMasterWriteS1() without any error), and haven't release it, users 
//! can call this function to continue transmit data to slave.
//!
//! This function transmit the data to the slave, and waiting for all bus 
//! transmition complete.
//!
//! Users can then check the return value to see if any error occurs:
//! - \ref xI2C_MASTER_ERR_NONE     - \b 0, no error
//! - \ref xI2C_MASTER_ERR_ADDR_ACK - The transmitted address was not acknowledged
//! - \ref xI2C_MASTER_ERR_DATA_ACK - The transmitted data was not acknowledged
//! - \ref xI2C_MASTER_ERR_ARB_LOST - The I2C controller lost arbitration.
//!
//! Then users can call this function to continue transmit data to slave.
//! Users call also call xI2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! This function is always used in thread mode.
//!
//! \return Returns the master error status.
//
//*****************************************************************************
#define xI2CMasterWriteS2(ulBase, ucData, bEndTransmition)                    \
        I2CMasterWriteS2(ulBase, ucData, bEndTransmition)

//*****************************************************************************
//
//! \brief Write a data buffer to the slave when the bus is idle, and waiting   
//! for all bus transmiton complete.(Write Buffer Step1)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr is the 7-bit slave address.
//! \param pucDataBuf is the data buffer to transmit.
//! \param ulLen is the data buffer byte size.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition.
//!
//! This function init a new data buffer write transmition. When the master have 
//! not obtained control of the bus, This function transmit the START condition,  
//! the slave address and the data, then waiting for the data transmition 
//! complete, and continue next data transmition, until all complete. If there 
//! is any error occurs, the remain data will be canceled.
//!
//! Users can then check the return value to see how many datas have been 
//! successfully transmited. if the number != ulLen, user can call 
//! xI2CMasterError() to see what error occurs.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call xI2CMasterWriteS2() / xI2CMasterWriteBufS2() to continue transmit data 
//! to slave. Users call also call xI2CMasterStop() to terminate this transmition 
//! and release the I2C bus.
//!
//! This function is always used in thread mode.
//!
//! \return Returns the data number that have been successully tranmited.
//
//*****************************************************************************
#define xI2CMasterWriteBufS1(ulBase, ucSlaveAddr, pucDataBuf, ulLen, bEndTransmition) \
        I2CMasterWriteBufS1(ulBase, ucSlaveAddr, pucDataBuf, ulLen, bEndTransmition)


//*****************************************************************************
//
//! \brief Write a data buffer to the slave, when the master have obtained  
//! control of the bus, and waiting for all bus transmiton complete.(Write
//! Buffer Step2)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param pucDataBuf is the data buffer to transmit.
//! \param ulLen is the data buffer byte size.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition.
//!
//! After the master obtained control of the bus(have called  
//! xI2CMasterWriteS1() or xI2CMasterWriteBufS1() without any error), and haven't 
//! release it, users can call this function to continue transmit data to slave.
//!
//! This function transmit the data one by one to the slave, waiting for every  
//! data transmition complete, and continue next data transmition, until all  
//! complete. If there is any error occurs, the remain data will be canceled.
//!
//! Users can then check the return value to see how many datas have been 
//! successfully transmited. if the number != ulLen, user can call 
//! xI2CMasterError() to see what error occurs.
//!
//! Then users can call xI2CMasterWriteS2() or this function to continue  
//! transmit data to slave. Users call also call xI2CMasterStop() to terminate  
//! this transmition and release the I2C bus.
//!
//! This function is always used in thread mode.
//!
//! \return Returns the data number that have been successully tranmited.
//
//*****************************************************************************
#define xI2CMasterWriteBufS2(ulBase, pucDataBuf, ulLen, bEndTransmition)      \
        I2CMasterWriteBufS2(ulBase, pucDataBuf, ulLen, bEndTransmition)

//*****************************************************************************
//
//! \brief Send a master receive request when the bus is idle.(Read Step1)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr is the 7-bit slave address.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! This function init a new receive transmition. When the master have not obtained
//! control of the bus, This function send request to transmit the START 
//! condition, the slave address and the data request, Then it returns  
//! immediately, no waiting any bus transmition to complete. 
//!
//! If bEndTransmition is xtrue, the receive operation will followed by an 
//! negative ACK and STOP condition.
//!
//! Users can call xI2CMasterBusy() to check if all the bus transmition 
//! complete, then call xI2CMasterError() to check if any error occurs. Then user 
//! can get the data by calling xI2CMasterDataGet() if there is no error occurs.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call xI2CMasterReadRequestS2() to continue receive data from slave.
//! Users call also can xI2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! For this function returns immediately, it is always using in the interrupt
//! hander.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterReadRequestS1(ulBase, ucSlaveAddr, bEndTransmition)         \
        I2CMasterReadRequestS1(ulBase, ucSlaveAddr, bEndTransmition)

//*****************************************************************************
//
//! \brief Send a master data receive request when the master have obtained 
//! control of the bus.(Write Step2)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! After the master obtained control of the bus(have called  
//! xI2CMasterReadRequestS1() without any error), and haven't release it, users 
//! can call this function to continue receive data from slave.
//!
//! If bEndTransmition is xtrue, the receive operation will followed by an 
//! negative ACK and STOP condition.
//!
//! Users can call xI2CMasterBusy() to check if all the bus transmition 
//! complete, then call xI2CMasterError() to check if any error occurs. Then user 
//! can get the data by calling xI2CMasterDataGet() if there is no error occurs.
//!
//! Then users can call this function to continue receive data from slave.
//! Users call also can xI2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! For this function returns immediately, it is always using in the interrupt
//! hander.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterReadRequestS2(ulBase, bEndTransmition)                      \
        I2CMasterReadRequestS2(ulBase, bEndTransmition)

//*****************************************************************************
//
//! \brief Send a master data receive request with an NACK when the master have  
//! obtained control of the bus(Write Step2).
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function is used to request the last data to receive, and signal the 
//! end of the transfer to the slave transmitter. Then the master can repeat
//! START condition, switch to transmit or other slaves without lost control
//! of the bus.
//!
//! Users can call xI2CMasterBusy() to check if all the bus transmition 
//! complete, then call xI2CMasterError() to check if any error occurs. Then user 
//! can get the data by calling xI2CMasterDataGet() if there is no error occurs.
//!
//! Users call also can xI2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! For this function returns immediately, it is always using in the interrupt
//! handler.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterReadLastRequestS2(ulBase)                                   \
        I2CMasterReadLastRequestS2(ulBase)


//*****************************************************************************
//
//! \brief Read a data from a slave when the bus is idle, and waiting for all 
//! bus transmiton complete.(Read Step1)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr is the 7-bit slave address.
//! \param pucData is the buffer where to save the data.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! This function init a new receive transmition. When the master have not obtained
//! control of the bus, This function send request to transmit the START 
//! condition, the slave address and the data request, then waiting for all bus
//! transmition complete.
//!
//! If bEndTransmition is xtrue, the receive operation will followed by an 
//! negative ACK and STOP condition.
//!
//! Users can then check the return value to see if any error occurs:
//! - \ref xI2C_MASTER_ERR_NONE     - \b 0, no error
//! - \ref xI2C_MASTER_ERR_ADDR_ACK - The transmitted address was not acknowledged
//! - \ref xI2C_MASTER_ERR_DATA_ACK - The transmitted data was not acknowledged
//! - \ref xI2C_MASTER_ERR_ARB_LOST - The I2C controller lost arbitration.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call xI2CMasterReadS2() to continue receive data from slave.
//! Users call also can xI2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! This function is usually used in thread mode.
//!
//! \return Returns the master error status.
//
//*****************************************************************************
#define xI2CMasterReadS1(ulBase, ucSlaveAddr, pucData, bEndTransmition)       \
        I2CMasterReadS1(ulBase, ucSlaveAddr, pucData, bEndTransmition)

//*****************************************************************************
//
//! \brief Read a data from a slave when the master have obtained control of 
//! the bus, and waiting for all bus transmiton complete.(Read Step2)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param pucData is the buffer where to save the data.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! After the master obtained control of the bus(have called  
//! xI2CMasterReadS1() without any error), and haven't release it, users can 
//! call this function to continue receive data from the slave.
//!
//! If bEndTransmition is xtrue, the receive operation will followed by an 
//! negative ACK and STOP condition.
//!
//! It will be waiting for all bus transmition complete before return.
//! Users can then check the return value to see if any error occurs:
//! - \ref xI2C_MASTER_ERR_NONE     - \b 0, no error
//! - \ref xI2C_MASTER_ERR_ADDR_ACK - The transmitted address was not acknowledged
//! - \ref xI2C_MASTER_ERR_DATA_ACK - The transmitted data was not acknowledged
//! - \ref xI2C_MASTER_ERR_ARB_LOST - The I2C controller lost arbitration.
//!
//! Then useres can call this function to continue receive data from slave.
//! Users call also can xI2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! This function is usually used in thread mode.
//!
//! \return Returns the master error status.
//
//*****************************************************************************
#define xI2CMasterReadS2(ulBase, pucData, bEndTransmition)                    \
        I2CMasterReadS2(ulBase, pucData, bEndTransmition)

//*****************************************************************************
//
//! \brief Read some data from a slave when the bus is idle, and waiting for all 
//! bus transmiton complete.(Read Buffer Step1)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr is the 7-bit slave address.
//! \param pucDataBuf is the buffer where to save the data.
//! \param ulLen is the data number to receive.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! This function init a new data buffer receive transmition. When the master 
//! have not obtained control of the bus, This function send request to transmit 
//! the START condition, the slave address and the data request, then waiting for 
//! the data transmition complete, and continue next data transmition, until all 
//! complete. If there is any error occurs, the remain data will be canceled.
//!
//! If bEndTransmition is xtrue, the receive operation will followed by an 
//! negative ACK and STOP condition.
//!
//! Users can then check the return value to see how many datas have been 
//! successfully received. if the number != ulLen, user can call 
//! xI2CMasterError() to see what error occurs.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call xI2CMasterReadS2() or xI2CMasterReadBufS2() to continue receive data .
//! from slave .Users call also can xI2CMasterStop() to terminate this transmition
//! and release the I2C bus.
//!
//! This function is usually used in thread mode.
//!
//! \return Returns the data number that have been successully received.
//
//*****************************************************************************
#define xI2CMasterReadBufS1(ulBase, ucSlaveAddr, pucDataBuf, ulLen, bEndTransmition) \
        I2CMasterReadBufS1(ulBase, ucSlaveAddr, pucDataBuf, ulLen, bEndTransmition)


//*****************************************************************************
//
//! \brief Read some data from a slave when the master have obtained control of
//! the bus, and waiting for all bus transmiton complete.(Write Buffer Step2)
//!
//! \param ulBase is the base address of the I2C Master module.
//! \param ucSlaveAddr is the 7-bit slave address.
//! \param pucDataBuf is the buffer where to save the data.
//! \param ulLen is the data number to receive.
//! \param bEndTransmition is flag to control if transmit the STOP condition and
//! terminate this transmition. 
//!
//! After the master obtained control of the bus(have called  
//! xI2CMasterReadS1() or xI2CMasterReadBufS1() without any error), and haven't 
//! release it, users can call this function to continue receive data from slave.
//!
//! This function receive data one by one from the slave, waiting for every  
//! data transmition complete, and continue next data transmition, until all  
//! complete. If there is any error occurs, the remain data will be canceled.
//!
//! If bEndTransmition is xtrue, the receive operation will followed by an 
//! negative ACK and STOP condition.
//!
//! Users can then check the return value to see how many datas have been 
//! successfully received. if the number != ulLen, user can call 
//! xI2CMasterError() to see what error occurs.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call xI2CMasterReadS2() or xI2CMasterReadBufS2() to continue receive data
//! from slave. Users call also can xI2CMasterStop() to terminate this transmition
//! and release the I2C bus.
//!
//! This function is usually used in thread mode.
//!
//! \return Returns the data number that have been successully received.
//
//*****************************************************************************
#define xI2CMasterReadBufS2(ulBase, pucDataBuf, ulLen, bEndTransmition)       \
        I2CMasterReadBufS2(ulBase, pucDataBuf, ulLen, bEndTransmition)


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
//! \addtogroup STM32F1xx_I2C
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Int_Type Interrupt defines
//! \brief Values that show I2C Interrupt Type
//! Values that can be passed to xx
//! as the xx parameter.
//! @{
//
//*****************************************************************************

//
//! Buffer interrupt enable
//
#define I2C_INT_BUF             0x00000400

//
//! Event interrupt enable
//
#define I2C_INT_EVT             0x00000200

//
//! Error interrupt enable
//
#define I2C_INT_ERR             0x00000100

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_DUAL_EN  Dual Address Mode Enable
//! Values that can be passed to I2COwnAddress2Config() as the ulDual parameter.
//! @{
//
//*****************************************************************************

//
//! Dual Address Mode Enable
//
#define I2C_DUAL_ADD_EN         0x00000001

//
//! Dual Address Mode Disable
//
#define I2C_DUAL_ADD_DIS        0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Event_Type Event defines
//! \brief Values that show I2C Event Type
//! Values that can be passed to xx
//! as the xx parameter.
//! @{
//
//*****************************************************************************

//
//! Start bit sent (Master)
//
#define I2C_EVENT_SB            0x00000001

//
//! Address sent (Master) or Address matched (Slave)
//
#define I2C_EVENT_ADDR          0x00000002

//
//! 10-bit header sent (Master)
//
#define I2C_EVENT_ADD10         0x00000008

//
//! Stop received (Slave)
//
#define I2C_EVENT_STOPF         0x00000010

//
//! Data byte transfer finished
//
#define I2C_EVENT_BTF           0x00000004

//
//! Receive buffer not empty
//
#define I2C_EVENT_RXNE          0x00000040

//
//! Transmit buffer empty
//
#define I2C_EVENT_TXE           0x00000080

//
//! Bus error
//
#define I2C_EVENT_BERR          0x00000100

//
//! Arbitration loss (Master)
//
#define I2C_EVENT_ARLO          0x00000200

//
//! Acknowledge failure
//
#define I2C_EVENT_AF            0x00000400

//
//! Overrun/Underrun
//
#define I2C_EVENT_OVR           0x00000800

//
//! PEC error
//
#define I2C_EVENT_PECERR        0x00001000

//
//! Timeout/Tlow error
//
#define I2C_EVENT_TIMEOUT       0x00004000

//
//! SMBus Alert
//
#define I2C_EVENT_SMBALERT      0x00008000

//
//! I2C master TX
//
#define I2C_MASTER_EVENT_TX     0x00070000

//
//! I2C master RX
//
#define I2C_MASTER_EVENT_RX     0x00030000

//
//! I2C slave TX
//
#define I2C_SLAVE_EVENT_TREQ    0x00060000

//
//! I2C slave RX
//
#define I2C_SLAVE_EVENT_RREQ    0x00020000


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Master_Event I2C Master Events
//! \brief Values that show I2C Master Events
//! Values that can be passed to xx
//! as the xx parameter.
//! @{
//
//*****************************************************************************

//
//! After sending the START condition the master has to wait for this event.
//! It means that the Start condition has been correctly released on the
//! I2C bus (the bus is free, no other devices is communicating).
//! Communication start BUSY, MSL and SB flag
//
#define I2C_EVENT_MASTER_MODE_SELECT                                          \
                                0x00030001

//
//! Address Acknowledge
//! After checking on EV5 (start condition correctly released on the bus), the 
//! master sends the address of the slave(s) with which it will communicate 
//! Then the master has to wait that a slave acknowledges his address.
//! If an acknowledge is sent on the bus, one of the following events will 
//! be set:
//! 
//!  1) In case of Master Receiver (7-bit addressing): the  
//!     I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED event is set.
//!  
//!  2) In case of Master Transmitter (7-bit addressing): the  
//!     I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED is set
//!  
//!  3) In case of 10-Bit addressing mode, the master (just after generating 
//! the START and checking on EV5) has to send the header of 10-bit 
//! addressing mode. Then master should wait on EV9. It means that the 10-bit
//! addressing header has been correctly sent on the bus. Then master should
//! send the second part of the 10-bit address (LSB) using the function
//! xx(). Then master should wait for event EV6.
//!   
//! BUSY, MSL, ADDR, TXE and TRA flags
//
#define I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED                            \
                                0x00070082
//
//! BUSY, MSL and ADDR flags
//                              
#define I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED                               \
                                0x00030002
//
//! BUSY, MSL and ADD10 flags
//
#define I2C_EVENT_MASTER_MODE_ADDRESS10                                       \
                                0x00030008

//
//! Communication events
//! If a communication is established (START condition generated and slave  
//! address acknowledged) then the master has to check on one of the  
//! following events for communication procedures:
//!  
//! 1) Master Receiver mode: The master has to wait on the event EV7 then to 
//!    read the data received from the slave (xx() function).
//! 
//! 2) Master Transmitter mode: The master has to send data (xx() 
//!    function) then to wait on event EV8 or EV8_2.
//!    These two events are similar: 
//!     - EV8 means that the data has been written in the data register and is 
//!       being shifted out.
//!     - EV8_2 means that the data has been physically shifted out and output 
//!       on the bus.
//!     In most cases, using EV8 is sufficient for the application.Using
//!     EV8_2 leads to a slower communication but ensure more reliable test.
//!     EV8_2 is also more suitable than EV8 for testing on the last data  
//!     transmission (before Stop condition generation).
//!     
//!  @note In case the  user software does not guarantee that this event EV7  
//!  is managed before the current byte end of transfer, then user may check 
//!  on EV7 and BTF flag at the same time (ie. (I2C_EVENT_MASTER_BYTE_RECEIVED 
//!  | I2C_FLAG_BTF)). In this case the communication may be slower.
//! Master RECEIVER mode BUSY, MSL and RXNE flags
//
#define I2C_EVENT_MASTER_BYTE_RECEIVED                                        \
                                0x00030040
//
//! Master TRANSMITTER mode TRA, BUSY, MSL, TXE flags
//                              
#define I2C_EVENT_MASTER_BYTE_TRANSMITTING                                    \
                                0x00070080
//
//! Master TRANSMITTER mode TRA, BUSY, MSL, TXE and BTF flags
//
#define I2C_EVENT_MASTER_BYTE_TRANSMITTED                                     \
                                0x00070084

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Slave_Event I2C Slave Events
//! \brief Values that show I2C Slave Events
//! Values that can be passed to xx
//! as the xx parameter.
//! @{
//
//*****************************************************************************

//
//! Communication start events
//! Wait on one of these events at the start of the communication. It means  
//! that the I2C peripheral detected a Start condition on the bus (generated  
//! by master device) followed by the peripheral address. The peripheral  
//! generates an ACK condition on the bus (if the acknowledge feature is enabled 
//! through function xx()) and the events listed above are set :
//!  
//! 1) In normal case (only one address managed by the slave), when the address 
//!   sent by the master matches the own address of the peripheral (configured  
//!   by I2C_OwnAddress1 field) the I2C_EVENT_SLAVE_XXX_ADDRESS_MATCHED event is 
//!   set (where XXX could be TRANSMITTER or RECEIVER).
//!    
//! 2) In case the address sent by the master matches the second address of the 
//!   peripheral (configured by the function xx() and enabled 
//!   by the function xx()) the events I2C_EVENT_SLAVE_XXX_SECONDADDRESS_MATCHED 
//!   (where XXX could be TRANSMITTER or RECEIVER) are set.
//!   
//! 3) In case the address sent by the master is General Call (address 0x00) and 
//!   if the General Call is enabled for the peripheral (using function xx()) 
//!   the following event is set I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED.
//! Case of One Single Address managed by the slave BUSY and ADDR flags
//
#define I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED                              \
                                0x00020002
//
//! Case of One Single Address managed by the slave
//! TRA, BUSY, TXE and ADDR flags 
//                              
#define I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED                           \
                                0x00060082

//
//! Case of Dual address managed by the slave
//! DUALF and BUSY flags
//
#define I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED                        \
                                0x00820000

//
//! Case of Dual address managed by the slave
//! DUALF, TRA, BUSY and TXE flags
//
#define I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED                     \
                                0x00860080

//
//! Case of General Call enabled for the slave
//! GENCALL and BUSY flags
//
#define I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED                            \
                                0x00120000

//
//! Communication events
//! Wait on one of these events when EV1 has already been checked and: 
//! 
//! - Slave RECEIVER mode:
//!     - EV2: When the application is expecting a data byte to be received. 
//!     - EV4: When the application is expecting the end of the communication:  
//!       master sends a stop condition and data transmission is stopped.
//!    
//! - Slave Transmitter mode:
//!    - EV3: When a byte has been transmitted by the slave and the application  
//!      is expecting the end of the byte transmission. The two events 
//!      I2C_EVENT_SLAVE_BYTE_TRANSMITTED and I2C_EVENT_SLAVE_BYTE_TRANSMITTING 
//!      are similar. The second one can optionally be used when the user 
//!      software doesn't guarantee the EV3 is managed before the current byte
//!      end of transfer.
//!    - EV3_2: When the master sends a NACK in order to tell slave that data 
//!      transmission shall end (before sending the STOP condition). In this 
//!      case slave has to stop sending data bytes and expect a Stop condition 
//!      on the bus.
//!      
//!  \note In case the  user software does not guarantee that the event EV2 is 
//!  managed before the current byte end of transfer, then user may check on  
//!  EV2 and BTF flag at the same time (ie. (I2C_EVENT_SLAVE_BYTE_RECEIVED |
//!  I2C_FLAG_BTF)).In this case the communication may be slower.
//! Slave RECEIVER mode, BUSY and RXNE flags
//
#define I2C_EVENT_SLAVE_BYTE_RECEIVED                                         \
                                0x00020040

//
//! Slave RECEIVER mode,STOPF flag
//
#define I2C_EVENT_SLAVE_STOP_DETECTED                                         \
                                0x00000010

//
//! Slave TRANSMITTER mode,TRA, BUSY, TXE and BTF flags
//
#define I2C_EVENT_SLAVE_BYTE_TRANSMITTED                                      \
                                0x00060084

//
//! Slave TRANSMITTER mode,TRA, BUSY and TXE flags
//
#define I2C_EVENT_SLAVE_BYTE_TRANSMITTING                                     \
                                0x00060080

//
//! Slave TRANSMITTER mode,AF flag
//
#define I2C_EVENT_SLAVE_ACK_FAILURE                                           \
                                0x00000400

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Slave_Error I2C Master error status
//! \brief Values that show I2C Master error status
//! Values that can be passed to xx
//! as the xx parameter.
//! @{
//
//*****************************************************************************

#define I2C_MASTER_ERR_NONE     0
#define I2C_MASTER_ERR_ADDR_ACK 0x00000004
#define I2C_MASTER_ERR_DATA_ACK 0x00000008
#define I2C_MASTER_ERR_ARB_LOST 0x00000010

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// I2C Slave action requests
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Slave_Action I2C Slave action requests
//! \brief Values that show I2C Slave action requests
//! Values that can be passed to xx
//! as the xx parameter.
//! @{
//
//*****************************************************************************

#define I2C_SLAVE_ACT_NONE      0
#define I2C_SLAVE_ACT_RREQ      0x00000001  // Master has sent data
#define I2C_SLAVE_ACT_TREQ      0x00000002  // Master has requested data
#define I2C_SLAVE_ACT_RREQ_FBR  0x00000005  // Master has sent first byte

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Miscellaneous I2C driver definitions.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Miscellaneous Miscellaneous I2C driver definitions.
//! \brief Values that show Miscellaneous I2C driver definitions.
//! Values that can be passed to xx
//! as the xx parameter.
//! @{
//
//*****************************************************************************

#define I2C_MASTER_MAX_RETRIES  1000        // Number of retries

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Slave_Int I2C Slave interrupts.
//! \brief Values that show I2C Slave interrupts.
//! Values that can be passed to xx
//! as the xx parameter.
//! @{
//
//*****************************************************************************

#define I2C_SLAVE_INT_STOP      0x00000004  // Stop Condition Interrupt.
#define I2C_SLAVE_INT_START     0x00000002  // Start Condition Interrupt.
#define I2C_SLAVE_INT_DATA      0x00000001  // Data Interrupt.

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_General_Call I2C General Call
//! \brief Values that show I2C General Call
//! Values that can be passed to I2CSlaveOwnAddressSet().
//! @{
//
//*****************************************************************************
#define I2C_GENERAL_CALL_EN     0x00000040
#define I2C_GENERAL_CALL_DIS    0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Address_Type I2C Address type
//! \brief Values that show I2C Address type
//! Values that can be passed to xx().
//! @{
//
//*****************************************************************************
#define I2C_ADDR_7BIT           0x00000000
#define I2C_ADDR_10BIT          0x00008000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_DMA_Last I2C DMA last
//! \brief Values that show I2C DMA last
//! Values that can be passed to xx().
//! @{
//
//*****************************************************************************
#define I2C_DMA_LAST_EN         0x00001000
#define I2C_DMA_LAST_DIS        0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_PEC_Position I2C NOACK Position
//! \brief Values that show I2C NOACK Position 
//! Values that can be passed to I2CPECPositionConfig().
//! @{
//
//*****************************************************************************
#define I2C_NACKPOS_CURRENT     0x00000000
#define I2C_NACKPOS_NEXT        0x00000800

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_PEC_Position I2C PEC Position
//! \brief Values that show I2C PEC Position 
//! Values that can be passed to I2CPECPositionConfig().
//! @{
//
//*****************************************************************************
#define I2C_NACKPOS_CURRENT     0x00000000
#define I2C_PECPOS_NEXT         0x00000800

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_I2C_Exported_APIs STM32F1xx I2C API
//! \brief STM32F1xx I2C API Reference.
//! @{
//
//*****************************************************************************
extern void I2CMasterInit(unsigned long ulBase, unsigned long ulI2CClk,
                          xtBoolean bFast, xtBoolean bDutyCycle);
extern void I2CSlaveInit(unsigned long ulBase, unsigned long ulAddrConfig, 
                         unsigned char ucSlaveAddr, unsigned long ulGeneralCall);
extern void I2CStartSend (unsigned long ulBase);
extern void I2CStopSend (unsigned long ulBase);
extern void I2CEnable(unsigned long ulBase);
extern void I2CDisable(unsigned long ulBase);
extern void I2CMasterEnable(unsigned long ulBase);
extern void I2CMasterDisable(unsigned long ulBase);
extern void I2CIntEnable(unsigned long ulBase, unsigned long ulIntType);
extern void I2CIntDisable(unsigned long ulBase, unsigned long ulIntType);
extern void I2CDMAEnable(unsigned long ulBase, unsigned long ulDMALast);
extern void I2CDMADisable(unsigned long ulBase);
extern void I2COwnAddress2Config(unsigned long ulBase, unsigned long ulDual, 
                                 unsigned char ucAddress);
extern void I2CSoftwareResetEnable(unsigned long ulBase);
extern void I2CSoftwareResetDisable(unsigned long ulBase);
extern void I2CNACKPositionConfig(unsigned long ulBase, 
                                  unsigned long ulNACKPosition);
extern void I2CPECPositionConfig(unsigned long ulBase, 
                                 unsigned long ulPECPosition);
extern void I2CPECConfig(unsigned long ulBase, unsigned long ulConfig);
extern unsigned char I2CPECGet(unsigned long ulBase);
extern void I2CStretchClockEnable(unsigned long ulBase);
extern void I2CStretchClockDisable(unsigned long ulBase);
extern unsigned long I2CStatusGet(unsigned long ulBase);
extern void I2CFlagStatusClear(unsigned long ulBase, unsigned long ulFlag);
extern xtBoolean I2CBusBusy(unsigned long ulBase);
extern unsigned long I2CMasterErr(unsigned long ulBase);
extern void I2CDataPut(unsigned long ulBase, unsigned char ucData);
extern unsigned long I2CDataGet(unsigned long ulBase);
extern unsigned long I2CSlaveStatus(unsigned long ulBase);
extern void I2CMasterWriteRequestS1(unsigned long ulBase, 
                                    unsigned char ucSlaveAddr,
                                    unsigned char ucData, 
                                    xtBoolean bEndTransmition);
extern void I2CMasterWriteRequestS2(unsigned long ulBase, unsigned char ucData,
                                    xtBoolean bEndTransmition);
extern unsigned long I2CMasterWriteS1(unsigned long ulBase, 
                                      unsigned char ucSlaveAddr,
                                      unsigned char ucData, 
                                      xtBoolean bEndTransmition);
extern unsigned long I2CMasterWriteS2(unsigned long ulBase, 
                                      unsigned char ucData,
                                      xtBoolean bEndTransmition);
extern unsigned long I2CMasterWriteBufS1(unsigned long ulBase, 
                                         unsigned char ucSlaveAddr,
                                         const unsigned char *pucDataBuf, 
                                         unsigned long ulLen, 
                                         xtBoolean bEndTransmition);
extern unsigned long I2CMasterWriteBufS2(unsigned long ulBase, 
                                         const unsigned char *pucDataBuf,
                                         unsigned long ulLen, 
                                         xtBoolean bEndTransmition);
extern void I2CMasterReadRequestS1(unsigned long ulBase, 
                                   unsigned char ucSlaveAddr,
                                   xtBoolean bEndTransmition);
extern void I2CMasterReadRequestS2(unsigned long ulBase, 
                                   xtBoolean bEndTransmition);
extern void I2CMasterReadLastRequestS2(unsigned long ulBase);
extern unsigned long I2CMasterReadS1(unsigned long ulBase, 
                                     unsigned char ucSlaveAddr,
                                     unsigned char *pucData,
                                     xtBoolean bEndTransmition);
extern unsigned long I2CMasterReadS2(unsigned long ulBase,
                                     unsigned char *pucData,
                                     xtBoolean bEndTransmition);
extern unsigned long I2CMasterReadBufS1(unsigned long ulBase, 
                                        unsigned char ucSlaveAddr,
                                        unsigned char* pucDataBuf, 
                                        unsigned long ulLen,
                                        xtBoolean bEndTransmition);
extern unsigned long I2CMasterReadBufS2(unsigned long ulBase, 
                                        unsigned char *pucDataBuf,
                                        unsigned long ulLen, 
                                        xtBoolean bEndTransmition);
extern void I2CIntCallbackInit(unsigned long ulBase, 
                               xtEventCallback xtI2CCallback);

extern void I2CInit(unsigned long ulBase, unsigned long ulClk);
extern xtBoolean I2CEventCheck (unsigned long ulBase, unsigned long ulEvent);


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

#endif // __xI2C_H__
