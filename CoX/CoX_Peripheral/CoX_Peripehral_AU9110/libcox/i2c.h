#ifndef _AU9110_I2C_H_
#define _AU9110_I2C_H_

//*****************************************************************************
//
//! \addtogroup AU9110_I2C
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_I2C_STATUS_Type I2C Status Type
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
//! \addtogroup AU9110_I2C_Transfer_Type I2C Transfer Type
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
//! \addtogroup xI2C_Master_Error xI2C Master Error
//! \brief Values that show I2C Master Error Type
//! Values that can be passed to
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
#define I2C_MASTER_ERR_ADDR_ACK  1

//
//! The transmitted data was not acknowledged.
//
#define I2C_MASTER_ERR_DATA_ACK 2

//
//! The I2C controller lost arbitration
//
#define I2C_MASTER_ERR_ARB_LOST 3

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_Event_Master xI2C Master Event
//! \brief Values that show I2C Master Event Type
//! Values that can be passed to
//! \endverbatim
//! @{
//
//*****************************************************************************

//
// Transmit address/data, or some error occurs
//
#define I2C_MASTER_EVENT_TX    0

//
// Receive a data, or some error occurs
//
#define I2C_MASTER_EVENT_RX    1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xI2C_Event_Slave xI2C Slave Event
//! \brief Values that show I2C Slave Event Type
//! Values that can be passed to
//! @{
//
//*****************************************************************************

//
//! Start Condition
//
#define I2C_SLAVE_EVENT_START  0

//
//! Stop Condition
//
#define I2C_SLAVE_EVENT_STOP   3

//
//! Transmit Request( or address matched in slave transmit mode)
//
#define I2C_SLAVE_EVENT_TREQ   0

//
//! Receive Request
//
#define I2C_SLAVE_EVENT_RREQ   1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_I2C_General_Call I2C General Call
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
//! \addtogroup AU9110_I2C_Address_Type I2C Address type
//! \brief Values that show I2C Address type
//! Values that can be passed to xx().
//! @{
//
//*****************************************************************************
#define I2C_ADDR_7BIT           0x00000000

#define I2C_ADDR_10BIT          0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_I2C_Time_Out I2C Time Out
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
//! \addtogroup AU9110_I2C_INT_Type I2C Interrupt Type
//! \brief Values that show I2C Interrupt Type
//! Values that can be passed to I2CIntEnable(),I2CIntDisable().
//! @{
//
//*****************************************************************************

#define I2C_MASTER_INT_DATA     BIT_32_7

#define I2C_SLAVE_INT_DATA      BIT_32_7

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AU9110_I2C_Exported_APIs AU9110 I2C API
//! \brief AU9110 I2C API Reference.
//! @{
//
//*****************************************************************************

extern unsigned long I2CStatusGet(unsigned long ulBase);
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
extern void I2CWakeupEnable(unsigned long ulBase, xtBoolean bEnable);
extern xtBoolean I2CWakeupStatusGet(unsigned long ulBase);

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
