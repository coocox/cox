//*****************************************************************************
//
//! \file xi2c.h
//! \brief Prototypes for the I2C Driver.
//! \version V2.2.1.0
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
//! \addtogroup xI2C_INT_Master xI2C Master Interrupt
//! 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xI2C Master Interrupts  |       CoX      |        Klx            |
//! |------------------------|----------------|------------------------|
//! |xI2C_MASTER_INT_DATA    |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Transmit / Receive a data, or an error occurs
//
#define xI2C_MASTER_INT_DATA    I2C_INT_FUNCTION

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
//! |xI2C Master Event       |       CoX      |        Klx            |
//! |------------------------|----------------|------------------------|
//! |xI2C_MASTER_EVENT_TX    |    Mandatory   |            Y           |
//! |xI2C_MASTER_EVENT_RX    |    Mandatory   |            Y           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Transmit address/data, or some error occurs
//
#define xI2C_MASTER_EVENT_TX    0

//
//! Receive a data, or some error occurs
//
#define xI2C_MASTER_EVENT_RX    1

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
//! |xI2C Slave Interrupts   |       CoX      |        Klx            |
//! |------------------------|----------------|------------------------|
//! |xI2C_SLAVE_INT_START    |    Optional    |            N           |
//! |xI2C_SLAVE_INT_STOP     |    Optional    |            Y           |
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
#define xI2C_SLAVE_INT_STOP    I2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX

//
//! A data received or data requested or error occurs
//
#define xI2C_SLAVE_INT_DATA    I2C_INT_FUNCTION


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
//! |xI2C Slave Event        |       CoX      |        Klx            |
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
#define xI2C_SLAVE_EVENT_STOP   3

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
//! |xI2C Master Error       |       CoX      |        Klx            |
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
#define xI2C_MASTER_ERR_NONE    0

//
//! The transmitted address was not acknowledged
//
#define xI2C_MASTER_ERR_ADDR_ACK                                              \
                                1

//
//! The transmitted data was not acknowledged.
//
#define xI2C_MASTER_ERR_DATA_ACK                                              \
                                2

//
//! The I2C controller lost arbitration
//
#define xI2C_MASTER_ERR_ARB_LOST                                              \
                                3

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
//! |xI2C General Call       |       CoX      |         Klx           |
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
//! \addtogroup xI2C_Exported_APIs xI2C API
//! \brief xI2C API Reference.
//!
//! \section xI2C_Exported_APIs_Port CoX Port Details
//! \verbatim
//! +--------------------------+----------------+------------------------+
//! |xI2C API                  |       CoX      |         Klx           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterInit            |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterEnable          |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterDisable         |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterBusBusy         |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterBusy            |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterError           |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterDataPut         |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterDataGet         |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterStop            |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterWriteRequestS1  |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterWriteRequestS2  |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterWriteS1         |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterWriteS2         |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterWriteBufS1      |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterWriteBufS2      |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterReadRequestS1   |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterReadRequestS2   |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterReadLastRequestS2|    Mandatory  |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterReadS1          |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterReadS2          |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterReadBufS1       |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterReadBufS2       |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterIntEnable       |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CMasterIntDisable      |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveIntEnable        |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveIntDisable       |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveIntInit          |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveEnable           |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveDisable          |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CIntCallbackInit       |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveDataPut          |    Mandatory   |            Y           |
//! |--------------------------|----------------|------------------------|
//! |xI2CSlaveDataGet          |    Mandatory   |            Y           |
//! +--------------------------+----------------+------------------------+
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
        I2CMasterInit(ulBase, ulI2CClk)

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
        I2CEnable(ulBase)

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
        I2CDisable(ulBase)

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
        I2CMasterBusy(ulBase)

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
        I2CMasterError(ulBase)

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
        I2CMasterDataPut(ulBase, ucData)

//*****************************************************************************
//
//! Receives a byte that has been sent to the I2C Master.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function reads a byte of data from the I2C Master Data Register.
//!
//! \return Returns the byte received from by the I2C Master, cast as an
//! unsigned long.
//
//*****************************************************************************
#define xI2CMasterDataGet(ulBase)                                             \
        I2CMasterDataGet(ulBase)

//*****************************************************************************
//
//! Gets the current I2C Master status.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This function reads the bytes of data from the I2C Master status Register.
//!
//! \return Returns the bytes(unsigned long) of I2C Master status Register.
//
//*****************************************************************************
#define xI2CMasterIntFlagGet(ulBase)                                          \
        I2CStatusGet(ulBase)

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
//! hander.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterWriteRequestS1(ulBase, ucSlaveAddr, ucData, bEndTransmition)\
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
//! hander.
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
#define xI2CMasterWriteBufS1(ulBase,ucAddr,pucDataBuf,ulLen,bEndTransmition)  \
        I2CMasterWriteBufS1(ulBase,ucAddr,pucDataBuf,ulLen,bEndTransmition)

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
//! hander.
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
#define xI2CMasterReadBufS1(ulBase,ucAddr,pucDataBuf,ulLen,bEndTransmition)   \
        I2CMasterReadBufS1(ulBase,ucAddr,pucDataBuf,ulLen,bEndTransmition)

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
//! \brief Enable I2C interrupt of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulIntType specifies the I2C interrupt type.
//! Details please refer to \ref xI2C_INT_Type.
//!
//! This function is to enable I2C interrupt of the specified I2C port.
//!
//! The \e ulBase must be: \b xI2C0_BASE.
//!
//! \return None.
//
//***************************************************************************** 
#define xI2CMasterIntEnable(ulBase, ulIntType)                                \
        I2CIntEnable(ulBase, ulIntType)

//*****************************************************************************
//
//! \brief Disable I2C interrupt of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulIntType specifies the I2C interupt type.
//! Details please refer to \ref xI2C_INT_Type.
//!
//! This function is to disable I2C interrupt of the specified I2C port.
//!
//! The \e ulBase must be: \b I2C0_BASE.
//!
//!
//! \return None.
//
//*****************************************************************************
#define xI2CMasterIntDisable(ulBase, ulIntType)                               \
        I2CIntDisable(ulBase, ulIntType)

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
        I2CIntEnable(ulBase, ulIntType)

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
        I2CIntDisable(ulBase, ulIntType)

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
//! The \e ulBase must be:\b I2C0_BASE.
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
#define xI2CSlaveInit(ulBase, ucSlaveAddr, ulGeneralCall)                      \
        I2CSlaveInit(ulBase, ucSlaveAddr, ulGeneralCall)

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
#define xI2CSlaveEnable(ulBase)                                                \
        I2CEnable(ulBase)

//*****************************************************************************
//
//! \brief Disables the I2C Slave block.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This will disable operation of the I2C Slave block.
//!
//! \return None.
//
//***************************************************************************** 
#define xI2CSlaveDisable(ulBase)                                               \
        I2CDisable(ulBase)

//*****************************************************************************
//
//! Transmits a byte from the I2C Slave.
//!
//! \param ulBase is the base address of the I2C module.
//! \param ucData data to be transmitted from the I2C Slave
//!
//! This function will place the supplied data into I2C Slave Data Register.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CSlaveDataPut(ulBase, ucData)                                       \
        xI2CMasterDataPut(ulBase, ucData)

//*****************************************************************************
//
//! Receives a byte that has been sent to the I2C Slave.
//!
//! \param ulBase is the base address of the I2C Slave module.
//!
//! This function reads a byte of data from the I2C Slave Data Register.
//!
//! \return Returns the byte received from by the I2C Slave, cast as an
//! unsigned long.
//
//*****************************************************************************
#define xI2CSlaveDataGet(ulBase)                                               \
        xI2CMasterDataGet(ulBase)

//*****************************************************************************
//
//! Gets the current I2C Slave status.
//!
//! \param ulBase is the base address of the I2C module.
//!
//! This function reads the bytes of data from the I2C Slave status Register.
//!
//! \return Returns the bytes(unsigned long) of I2C Slave status Register.
//
//*****************************************************************************
#define xI2CSlaveIntFlagGet(ulBase)                                            \
        xI2CMasterIntFlagGet(ulBase)

//*****************************************************************************
//
//! \brief Init interrupts callback for the specified I2C Port.
//!
//! \param ulPort is the base address of the UART port.
//! \param xtUARTCallback is callback for the specified I2C Port.
//!
//! Init interrupts callback for the specified I2C Port.
//!
//! \return None.
//
//*****************************************************************************
#define xI2CIntCallbackInit(ulBase, xtI2CCallback)                             \
        I2CIntCallbackInit(ulBase, xtI2CCallback)

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
//! \addtogroup KLx_I2C
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Klx_I2C_General_Call I2C General Call
//! \brief Values that can be passed to I2CSlaveOwnAddressSet().
//! @{
//
//*****************************************************************************
#define I2C_GENERAL_CALL_EN     0x00000080
#define I2C_GENERAL_CALL_DIS    0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Klx_I2C_Address_Bit I2C Address Bit
//! \brief Values that can be passed to I2CSlaveOwnAddressSet().
//! @{
//
//*****************************************************************************
#define I2C_ADDRESS_7BIT        0x00000000
#define I2C_ADDRESS_10BIT       0x00000040

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Klx_I2C_INT_Type Klx_I2C Interrupt type
//! \brief Values that can be passed to I2CIntEnable().
//! @{
//
//*****************************************************************************

//
//! Interrupt function
//
#define I2C_INT_FUNCTION        0x00000040

//
//! Interrupt stop
//
#define I2C_INT_BUS_STOP        0x00000020

//
//! Interrupt time out
//
#define I2C_INT_TIMEOUT         0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Klx_I2C_EVENT_Type Klx_I2C event type
//! \brief Values that can be passed to ().
//! @{
//
//*****************************************************************************

//
//! Transmit address/data, or some error occurs
//
#define I2C_MASTER_EVENT_TX     0x000000A2

//
//! Receive a data, or some error occurs
//
#define I2C_MASTER_EVENT_RX     0x000000A6

//
//! Start Condition
//
#define I2C_SLAVE_EVENT_START   0x00000000

//
//! Stop Condition
//
#define I2C_SLAVE_EVENT_STOP    0x00000040

//
//! Transmit Request( or address matched in slave transmit mode)
//
#define I2C_SLAVE_EVENT_TREQ    0x00000026

//
//! Receive Request
//
#define I2C_SLAVE_EVENT_RREQ    0x00000022

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Klx_I2C_Time_Out_Flsg I2C Time Out flag
//! \brief Values that can be passed to I2CTimeoutFlagGet().
//! @{
//
//*****************************************************************************

//
//! SCL Low Timeout Flag Low timeout occurs
//
#define I2C_TIMEOUT_SCL_LOW     0x00000008

//
//! SCL High Timeout Flag 1 SCL high and SDA high timeout occurs
//
#define I2C_TIMEOUT_SCL_HIGH1   0x00000004

//
//! SCL High Timeout Flag 2 SCL high and SDA low timeout occurs
//
#define I2C_TIMEOUT_SCL_HIGH2   0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Klx_I2C_Time_Out I2C Time Out
//! \brief Values that can be passed to I2CTimeoutCounterSet().
//! @{
//
//*****************************************************************************
//#define I2C_TIMEOUT_EN          0x00000004
//#define I2C_TIMEOUT_DIS         0x00000000
#define I2C_TIMEOUT_DIV64       0x00000010
#define I2C_TIMEOUT_DIV_NO      0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Klx_I2C_Master_Error Klx_I2C Master Error
//! \brief Values that can be returned from ().
//! @{
//
//*****************************************************************************

//
//! Every thing is OK
//
#define I2C_MASTER_ERR_NONE     0

//
//! The transmitted address was not acknowledged
//
#define I2C_MASTER_ERR_ADDR_ACK 0x00000001

//
//! The transmitted data was not acknowledged.
//
#define I2C_MASTER_ERR_DATA_ACK 0x00000001

//
//! The I2C controller lost arbitration
//
#define I2C_MASTER_ERR_ARB_LOST 0x00000010

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Klx_I2C_Exported_APIs Klx I2C API
//! @{
//
//*****************************************************************************

extern void I2CMasterInit(unsigned long ulBase, unsigned long ulI2CClk);

extern void I2CIntCallbackInit(unsigned long ulBase, 
                               xtEventCallback xtI2CCallback);

extern void I2CDisable(unsigned long ulBase);
extern void I2CEnable(unsigned long ulBase);

extern unsigned long I2CStatusGet(unsigned long ulBase);
extern void I2CSlaveInit(unsigned long ulBase, unsigned short usSlaveAddr, 
                         unsigned long ulGeneralCall, unsigned long ulAddrBit);

extern void I2CIntFlagClear(unsigned long ulBase);
extern void I2CTimeoutFlagClear(unsigned long ulBase, unsigned long ulTimeout);
extern void I2CTimeoutCounterSet(unsigned long ulBase,
                                 unsigned long ulDiv64, unsigned long ulTimeout);
extern xtBoolean I2CIntFlagGet(unsigned long ulBase);
extern xtBoolean I2CTimeoutFlagGet(unsigned long ulBase, unsigned long ulTimeout);
extern void I2CIntDisable(unsigned long ulBase, unsigned long ulIntType);
extern void I2CIntEnable(unsigned long ulBase, unsigned long ulIntType);

extern void I2CSlaveSecondAddressSet(unsigned long ulBase, 
                                     unsigned char ucSlaveAddr);
extern void I2CSecondAddressDisable(unsigned long ulBase);
extern void I2CHighDriverEnable(unsigned long ulBase);
extern void I2CHighDriverDisable(unsigned long ulBase);
extern void I2CSlaveBaudEnable(unsigned long ulBase);
extern void I2CSlaveBaudDisable(unsigned long ulBase);
extern void I2CWakeupEnable(unsigned long ulBase);
extern void I2CWakeupDisable(unsigned long ulBase);
extern void I2CDMAEnable(unsigned long ulBase);
extern void I2CDMADisable(unsigned long ulBase);
extern void I2CRangeAddrEnable(unsigned long ulBase, 
                               unsigned long ulRangeAddress);
extern void I2CRangeAddrDisable(unsigned long ulBase);
extern void I2CGlitchFilterSet(unsigned long ulBase, unsigned char ucFilter);

extern xtBoolean I2CMasterBusBusy(unsigned long ulBase);
extern xtBoolean I2CMasterBusy(unsigned long ulBase);
extern unsigned long I2CMasterError(unsigned long ulBase);
extern void I2CMasterDataPut(unsigned long ulBase, 
                              unsigned char ucData);
extern unsigned long I2CMasterDataGet(unsigned long ulBase);
extern void I2CStopSend (unsigned long ulBase);
extern void I2CMasterWriteRequestS1(unsigned long ulBase, 
                                     unsigned char ucSlaveAddr, 
                                     unsigned char ucData,
                                     xtBoolean bEndTransmition);
extern void I2CMasterWriteRequestS2(unsigned long ulBase,  
                                     unsigned char ucData,
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
                                         unsigned char *pucDataBuf,
                                         unsigned long ulLen,
                                         xtBoolean bEndTransmition);
extern unsigned long I2CMasterReadBufS2(unsigned long ulBase,
                                         unsigned char *pucDataBuf,
                                         unsigned long ulLen,
                                         xtBoolean bEndTransmition);
									 
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
