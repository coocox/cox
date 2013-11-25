//*****************************************************************************
//
//! \file xi2c.c
//! \brief Driver for the I2C
//! \version V2.1.1.0
//! \date 11/25/2013
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
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_i2c.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xi2c.h"


//*****************************************************************************
//
// An array is using to save the Transfer_Cfg point when is in interrupt mode 
//
//*****************************************************************************
static tI2CConfig g_tI2CSetup[2];
static unsigned long g_ulI2CMasterComplete[2];
static unsigned long g_ulI2CSlaveComplete[2];


//*****************************************************************************
//
// An array is I2C callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnI2CHandlerCallbacks[1]={0};

//*****************************************************************************
//
//! \internal
//! \brief Get the I2C number. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get the I2C number.
//!
//! The \e ulBase must be:\b I2C0_BASE
//!
//! \return value of I2C number,it can only be 0.
//
//*****************************************************************************
static unsigned long I2CNumGet (unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
	
	return ((ulBase == I2C0_BASE) ? 0 : 1);
}

//*****************************************************************************
//
//! \internal
//! \brief Generate a start condition on I2C bus. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to generate a start condition on specified I2C BUS.
//!
//! The \e ulBase must be:\b I2C0_BASE
//!
//! \note This is only for master
//!
//! \return value of I2C status register after generate a start condition.
//
//*****************************************************************************
static unsigned long I2CStartSend (unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_STA;

    //
    // Wait for complete
    //
    while (!(xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI));
	
    return (xHWREG(ulBase + I2C_O_STATUS) & I2C_STATUS_M);
}

//*****************************************************************************
//
//! \internal
//! \brief Generate a stop condition on I2C bus. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to generate a stop condition on specified I2C BUS.
//!
//! The \e ulBase must be:\b I2C0_BASE
//!
//! \note This is only for master
//!
//! \return None.
//
//*****************************************************************************
static void I2CStopSend (unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    if (xHWREG(ulBase + I2C_O_CON) & I2C_CON_STA)
    {
        xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_STA;
    }
	xHWREG(ulBase + I2C_O_CON) |= I2C_CON_STO;
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
    
	xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_AA;
}

//*****************************************************************************
//
//! \internal
//! \brief Send a byte to I2C bus. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ucData specifies the data which will send to I2C BUS.
//!
//! This function is to send a byte on specified I2C BUS.
//!
//! The \e ulBase must be:\b I2C0_BASE
//!
//! \note This is only for master
//!
//! \return value of I2C status register after send a byte.
//
//*****************************************************************************
static unsigned long I2CByteSend (unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    //
    // Make sure start bit is not active,but do not clear SI 
    //
    if (xHWREG(ulBase + I2C_O_CON) & I2C_CON_STA)
    {
        xHWREG(ulBase + I2C_O_CON) &= ~(I2C_CON_STA | I2C_CON_SI);
    }
            
    //
    // Send data to I2C BUS
    //
    xHWREG(ulBase + I2C_O_DAT) = ucData;
        
    //
    // Make sure AA and EI bit is not active,and clear SI 
    //
    xHWREG(ulBase + I2C_O_CON) &= ~(I2C_CON_AA | I2C_CON_EI);
        
    //
    // Wait the SI be set again by hardware
    //
    while (!(xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI));
        
    //
    // Return the i2c status
    //
    return (xHWREG(ulBase + I2C_O_STATUS) & I2C_STATUS_M);
}

//*****************************************************************************
//
//! \internal
//! \brief Get a byte from I2C bus. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ucpData specifies the data point which will save the data get from 
//! I2C BUS.
//!
//! This function is to get a byte on specified I2C BUS.
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! \note This is only for master
//!
//! \return value of I2C status register after receive a byte.
//
//*****************************************************************************
static unsigned long I2CByteGet (unsigned long ulBase, unsigned char *ucpData, 
                                 unsigned char ucAck)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    //
    // Make sure start bit is not active 
    //
    if (ucAck == 1)
    {
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
    }
    else
    {
        xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_AA;
    }
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
    
    while (!(xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI));
    *ucpData = (unsigned char)xHWREG(ulBase + I2C_O_DAT);
    return (xHWREG(ulBase + I2C_O_STATUS) & I2C_STATUS_M);
}

//*****************************************************************************
//
//! \brief I2C0 interrupt handler. Clear the I2C0 interrupt flag and execute the 
//! callback function.
//!
//! \param none.
//!
//! This function is the I2C0 interrupt handler,it will Clear the I2C0 interrupt
//! flag and execute the callback function if there be one.
//!
//! \note There are two source of this interrupt.One is I2C0 function and one is
//! I2C0 time out.
//!
//! \return None.
//
//*****************************************************************************
void 
I2C0IntHandler(void)
{
    unsigned long ulBase = I2C0_BASE;
    unsigned long ulStatus,ulTimeout;
#if NUC123_LIB_ONLY > 0
#if xI2C_MASTER > 0
    I2CMasterHandler(ulBase);
#endif
#if xI2C_SLAVE > 0
    I2CSlaveHandler(ulBase);
#endif
#else
    ulStatus = xHWREG(ulBase + I2C_O_STATUS);
    
    //
    // 0
    //
    //I2CFlagStatusClear(ulBase, I2C_EVENT_BUSERR | I2C_EVENT_RXNACK |
    //                           I2C_EVENT_ARBLOS);
    
    if((ulStatus == I2C_I2STAT_S_RX_SLAW_ACK) ||
       (ulStatus == I2C_I2STAT_S_RX_GENCALL_ACK) ||
       (ulStatus == I2C_I2STAT_S_RX_PRE_GENCALL_DAT_NACK) ||
       (ulStatus == I2C_I2STAT_S_TX_DAT_NACK) ||
       (ulStatus == I2C_I2STAT_S_TX_SLAR_ACK))
    {
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
    }
    
    if((ulStatus == I2C_I2STAT_S_RX_PRE_SLA_DAT_ACK) ||
       (ulStatus == I2C_I2STAT_S_RX_PRE_GENCALL_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_SLAVE_EVENT_RREQ, 0);
    }
    if((ulStatus == I2C_I2STAT_S_TX_SLAR_ACK) ||
       (ulStatus == I2C_I2STAT_S_TX_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_SLAVE_EVENT_TREQ, 0);
    }
    if((ulStatus == I2C_I2STAT_M_TX_SLAW_ACK) ||
       (ulStatus == I2C_I2STAT_M_TX_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_MASTER_EVENT_TX, 0);
    }
    if((ulStatus == I2C_I2STAT_M_RX_SLAR_ACK) ||
       (ulStatus == I2C_I2STAT_M_RX_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_MASTER_EVENT_RX, 0);
    }
    if((ulStatus == I2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX))
    {
        //
        //Temporally lock the interrupt for timeout condition
        //
        I2CIntDisable(ulBase);
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
        //
        // enable time out
        //
        ulTimeout = 0x10000;
        while(1)
        {
            if (xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI)
            {
                //
                // re-Enable interrupt
                //
                I2CIntEnable(ulBase);
                break;
            } 
            else 
            {
                ulTimeout--;
                if (ulTimeout == 0)
                {
                    //
                    //timeout occur, it's really a stop condition
                    //
                    g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_SLAVE_EVENT_STOP, 0);
                    break;
                }
            }
        }   
    }    
#endif
}

//*****************************************************************************
//
//! \brief General Master Interrupt handler for I2C peripheral. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to give a general Master Interrupt handler for I2C peripheral.
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! \note This is only for master
//!
//! \return None.
//
//*****************************************************************************
void 
I2CMasterHandler (unsigned long ulBase)
{
    unsigned long ulTemp;
    unsigned char ucReturnCode;
    tI2CMasterTransferCfg *tpTxRxsetup;
    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == I2C0_BASE);

    ulTemp = I2CNumGet(ulBase);
    tpTxRxsetup = (tI2CMasterTransferCfg *) g_tI2CSetup[ulTemp].ulSetup;

    //
    // Save current status
    //
    ucReturnCode = (xHWREG(ulBase + I2C_O_STATUS) & I2C_STATUS_M);

    //
    // there's no relevant information
    //
    if (ucReturnCode == I2C_I2STAT_NO_INF)
    {
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
        return;
    }

    //
    // TRANSMIT PHASE 
    //
    if (g_tI2CSetup[ulTemp].ulDir == 0)
    {
        switch (ucReturnCode)
        {
        //
        // A start/repeat start condition has been transmitted 
        //
        case I2C_I2STAT_M_TX_START:
        case I2C_I2STAT_M_TX_RESTART:
            xHWREG(ulBase + I2C_O_CON) &= ~(I2C_CON_STA | I2C_CON_SI);
            //
            // If there's any transmit data, then start to
            // send SLA+W right now, otherwise check whether if there's
            // any receive data for next state.
            // 
            if ((tpTxRxsetup->pvWBuf != 0) && (tpTxRxsetup->ulWLen != 0))
            {
                xHWREG(ulBase + I2C_O_DAT) = (tpTxRxsetup->ulSlave<< 1);
                xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
            } 
            else 
            {
                goto next_stage;
            }
            break;
        //
        // SLA+W has been transmitted, ACK has been received
        //
        case I2C_I2STAT_M_TX_SLAW_ACK:
        //
        // Data has been transmitted, ACK has been received 
        //
        case I2C_I2STAT_M_TX_DAT_ACK:
            //
            // Send more data 
            //
            if ((tpTxRxsetup->ulWCount < tpTxRxsetup->ulWLen) 
                && (tpTxRxsetup->pvWBuf != 0))
            {
                xHWREG(ulBase + I2C_O_CON) &= ~(I2C_CON_STA | I2C_CON_SI);
                xHWREG(ulBase + I2C_O_DAT) =  *(unsigned char *)
                ((unsigned long)tpTxRxsetup->pvWBuf + tpTxRxsetup->ulWCount);
                tpTxRxsetup->ulWCount++;
                xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
            }
            //
            // no more data, switch to next stage
            //
            else 
            {
next_stage:
                //
                // change direction
                //
                g_tI2CSetup[ulTemp].ulDir = 1;
                //
                // Check if any data to receive
                //
                if ((tpTxRxsetup->ulRLen != 0) && 
                    (tpTxRxsetup->pvRBuf != 0))
                {
                    //
                    // check whether if we need to issue an repeat start
                    //
                    if ((tpTxRxsetup->ulWLen != 0) && 
                        (tpTxRxsetup->pvWBuf != 0))
                    {
                        //
                        // Send out an repeat start command
                        //
                        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
                        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_STA;
                    }
                    //
                    // Don't need issue an repeat start, just goto send SLA+R
                    //
                    else 
                    {
                        goto send_slar;
                    }
                }
                //
                // no more data send, the go to end stage now
                //
                else 
                {
                    //
                    // success, goto end stage
                    //

                    goto end_stage;
                }
            }
            break;

        //
        // SLA+W has been transmitted, NACK has been received 
        //
        case I2C_I2STAT_M_TX_SLAW_NACK:
        //
        //Data has been transmitted, NACK has been received 
        //
        case I2C_I2STAT_M_TX_DAT_NACK:
            //
            // update status
            //

            goto retry;
        //
        //Arbitration lost in SLA+R/W or Data bytes 
        //
        case I2C_I2STAT_M_TX_ARB_LOST:
            //
            // update status
            //

        default:
            goto retry;
        }
    }

    //
    // RECEIVE PHASE 
    //
    else if (g_tI2CSetup[ulTemp].ulDir == 1)
    {
        switch (ucReturnCode)
        {
            //
            //A start/repeat start condition has been transmitted 
            //
        case I2C_I2STAT_M_TX_START:
        case I2C_I2STAT_M_TX_RESTART:
            xHWREG(ulBase + I2C_O_CON) &= ~(I2C_CON_STA | I2C_CON_SI);
            //
            // If there's any receive data, then start to
            // send SLA+R right now, otherwise check whether if there's
            // any receive data for end of state.
            //
            if ((tpTxRxsetup->pvRBuf != 0) && 
                (tpTxRxsetup->ulRLen != 0))
            {
send_slar:
                xHWREG(ulBase + I2C_O_DAT) = (tpTxRxsetup->ulSlave << 1) |  
                                              0x01;
                xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
            } 
            else 
            {
                //
                // Success, goto end stage
                //

                goto end_stage;
            }
            break;

        //
        //SLA+R has been transmitted, ACK has been received 
        //
        case I2C_I2STAT_M_RX_SLAR_ACK:
            if (tpTxRxsetup->ulRCount < (tpTxRxsetup->ulRLen - 1)) 
            {
                //
                //Data will be received,  ACK will be return
                //
                xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
            }
            else 
            {
                //
                //Last data will be received,  NACK will be return
                //
                xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_AA;
            }
            xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
            break;

        //
        //Data has been received, ACK has been returned 
        //
        case I2C_I2STAT_M_RX_DAT_ACK:
            // 
            //Note save data and increase counter first, then check later
            // Save data  
            //
            if ((tpTxRxsetup->pvRBuf != 0) && 
                (tpTxRxsetup->ulRCount < tpTxRxsetup->ulRLen))
            {
                *(unsigned char *)((unsigned long)tpTxRxsetup->pvRBuf+ tpTxRxsetup->ulRCount) = 
                (xHWREG(ulBase + I2C_O_DAT) & I2C_DAT_DATA_M);
                tpTxRxsetup->ulRCount++;
            }
            if (tpTxRxsetup->ulRCount < (tpTxRxsetup->ulRLen - 1)) 
            {
                //
                //Data will be received,  ACK will be return
                //
                xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
            }
            else 
            {
                //
                //Last data will be received,  NACK will be return
                //
                xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_AA;
            }

            xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
            break;

        //
        //Data has been received, NACK has been return 
        //
        case I2C_I2STAT_M_RX_DAT_NACK:
            //
            //Save the last data 
            //
            if ((tpTxRxsetup->pvRBuf != 0) && 
                (tpTxRxsetup->ulRCount < tpTxRxsetup->ulRLen))
            {
                *(unsigned char *)((unsigned long)tpTxRxsetup->pvRBuf + tpTxRxsetup->ulRCount) = 
                (xHWREG(ulBase + I2C_O_DAT) & I2C_DAT_DATA_M);
                tpTxRxsetup->ulRCount++;
            }
            //
            // success, go to end stage
            //

            goto end_stage;

        //
        // SLA+R has been transmitted, NACK has been received 
        //
        case I2C_I2STAT_M_RX_SLAR_NACK:
            //
            //update status
            //

            goto retry;

        //
        // Arbitration lost
        //
        case I2C_I2STAT_M_TX_ARB_LOST:
            //
            //update status
            //
            
        default:
retry:
            //
            // check if retransmission is available
            //
            if (1)
            {
                //
                //Clear tx count
                //
                tpTxRxsetup->ulWCount = 0;
                xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
                xHWREG(ulBase + I2C_O_CON) |= I2C_CON_STA;
            }
            //
            //End of stage
            //
            else 
            {        
end_stage:
                ulTemp = I2CNumGet(ulBase);
                if(g_tI2CSetup[ulTemp].g_pfnI2CHandlerCallbacks != 0)
                {
                    g_tI2CSetup[ulTemp].g_pfnI2CHandlerCallbacks(0,0,0,0);
                }
                //
                //Disable interrupt
                //
                I2CDisable(ulBase);
                //
                //Send stop
                //
                I2CStopSend(ulBase);
                g_ulI2CMasterComplete[ulTemp] = xtrue;
            }
            break;
        }
    }
}

//*****************************************************************************
//
//! \brief General slave Interrupt handler for I2C peripheral. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to give a general slave Interrupt handler for I2C peripheral
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! \note this is only for slave
//!
//! \return None.
//
//*****************************************************************************
void 
I2CSlaveHandler (unsigned long ulBase)
{
    unsigned long ulTemp;
    unsigned char ucReturnCode;
    tI2CSlaveTransferCfg *tpTxRxsetup;
    unsigned long ulTimeout;

    ulTemp = I2CNumGet(ulBase);
    tpTxRxsetup = (tI2CSlaveTransferCfg *) g_tI2CSetup[ulTemp].ulSetup;

    ucReturnCode = xHWREG(ulBase + I2C_O_STATUS) & I2C_STATUS_M;

    //
    // Save current status
    // txrx_setup->status = returnCode;
    // there's no relevant information
    //
    if (ucReturnCode == I2C_I2STAT_NO_INF)
    {
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
        return;
    }

    switch (ucReturnCode)
    {

    //
    // No status information 
    //
    case I2C_I2STAT_NO_INF:
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
        break;

    //
    // Reading phase 
    //
    //
    // Own SLA+R has been received, ACK has been returned 
    //
    case I2C_I2STAT_S_RX_SLAW_ACK:
    //
    // General call address has been received, ACK has been returned 
    //
    case I2C_I2STAT_S_RX_GENCALL_ACK:
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
        break;

    //
    // Previously addressed with own SLA;
    // DATA byte has been received;
    // ACK has been returned 
    //
    case I2C_I2STAT_S_RX_PRE_SLA_DAT_ACK:
    //
    // DATA has been received, ACK hasn been return 
    //
    case I2C_I2STAT_S_RX_PRE_GENCALL_DAT_ACK:
        //
        // All data bytes that over-flow the specified receive
        // data length, just ignore them.
        //
        if ((tpTxRxsetup->ulRCount < tpTxRxsetup->ulRLen) && 
            (tpTxRxsetup->pvRBuf != 0))
        {
            *(unsigned char *)((unsigned long)tpTxRxsetup->pvRBuf + tpTxRxsetup->ulRCount) = 
            (unsigned char)(xHWREG(ulBase + I2C_O_DAT));
            tpTxRxsetup->ulRCount++;
        }
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
        break;

    //
    // Previously addressed with own SLA;
    // DATA byte has been received;
    // NOT ACK has been returned 
    //
	case I2C_I2STAT_S_RX_PRE_SLA_DAT_NACK:
    //
    // DATA has been received, NOT ACK has been returned 
    //
	case I2C_I2STAT_S_RX_PRE_GENCALL_DAT_NACK:
		xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
		break;

    //
    // Note that: Return code only let us know a stop condition mixed
    // with a repeat start condition in the same code value.
    // So we should provide a time-out. In case this is really a stop
    // condition, this will return back after time out condition. Otherwise,
    // next session that is slave receive data will be completed.
    //

    //
    // A Stop or a repeat start condition 
    //
    case I2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX:
        //
        //Temporally lock the interrupt for timeout condition
        //
        I2CIntDisable(ulBase);
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
        //
        // enable time out
        //
        ulTimeout = 0x10000;
        while(1)
        {
            if (xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI)
            {
                //
				// re-Enable interrupt
				//
				I2CIntEnable(ulBase);
				break;
            } 
            else 
            {
                ulTimeout--;
                if (ulTimeout == 0)
                {
                    //
                    //timeout occur, it's really a stop condition
                    //
                    goto s_int_end;
                }
            }
        }
        break;

    //
    // Writing phase 
    //
    // Own SLA+R has been received, ACK has been returned 
    //
	case I2C_I2STAT_S_TX_SLAR_ACK:
    //
    // Data has been transmitted, ACK has been received 
    //
	case I2C_I2STAT_S_TX_DAT_ACK:
        //
        // All data bytes that over-flow the specified receive
        // data length, just ignore them.
        //
        if ((tpTxRxsetup->ulWCount < tpTxRxsetup->ulWLen) &&
            (tpTxRxsetup->pvWBuf != 0))
        {
            xHWREG(ulBase + I2C_O_DAT)= 
            *(unsigned char *) ((unsigned long)tpTxRxsetup->pvWBuf + tpTxRxsetup->ulWCount);
            tpTxRxsetup->ulWCount++;
        }
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
        break;

    //
    // Data has been transmitted, NACK has been received,
    // that means there's no more data to send, exit now 
    //
    // Note: Don't wait for stop event since in slave transmit mode,
    // since there no proof lets us know when a stop signal has been received
    // on slave side.
    //
    case I2C_I2STAT_S_TX_DAT_NACK:
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
        
        goto s_int_end;

    // 
    //Other status must be captured
    //
    default:
s_int_end:
        ulTemp = I2CNumGet(ulBase);
        if(g_tI2CSetup[ulTemp].g_pfnI2CHandlerCallbacks != 0)
        {
            g_tI2CSetup[ulTemp].g_pfnI2CHandlerCallbacks(0,0,0,0);
        }
        //
        //Disable interrupt
        //
        I2CIntDisable(ulBase);
        xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_AA;
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
        xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_STA;
        g_ulI2CSlaveComplete[ulTemp] = xtrue;
        break;
    }
}

//*****************************************************************************
//
//! \brief Set the clock rate of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulI2CClk specifies the I2C clock rate.
//!
//! This function is to initialize and set the clock rate specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! The \e ulI2CClk is the I2C clock rate.
//!
//! \note This is only for master
//!
//! \return None.
//
//*****************************************************************************
void 
I2CMasterInit(unsigned long ulBase, unsigned long ulI2CClk)
{
    unsigned long ulHclk;
    unsigned long ulDiv;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    if (ulBase == I2C0_BASE)
    {
        SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
    }
    
    xHWREG(ulBase + I2C_O_CON) = I2C_CON_ENS1;
    
    ulHclk = SysCtlHClockGet();
    
    ulDiv = (unsigned long) (((ulHclk * 10)/(ulI2CClk * 4) + 5) / 10 - 1);
    xHWREG(ulBase + I2C_O_CLK) = ulDiv;

    xHWREG(ulBase + I2C_O_CON) = 0;
    xHWREG(ulBase + I2C_O_CON) = I2C_CON_ENS1;
}

//*****************************************************************************
//
//! \brief Transmit and Receive data in master mode of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//! \param tCfg specifies Pointer to a I2C_M_SETUP_Type structure that contains
//!  specified information about the configuration for master transfer.
//! \param ulOption specifies interrupt or polling mode.
//!
//! This function is to Transmit and Receive data in master mode of specified
//! I2C port.
//!
//! The \e ulBase must be: \b I2C0_BASE.
//!
//! The \e tCfg is the I2C Master transfer setup data structure
//!
//! \note This is only for master
//! In case of using I2C to receive data only, either transmit length set to 0
//! or transmit data pointer set to NULL.
//! In case of using I2C to transmit data only, either receive length set to 0
//! or receive data pointer set to NULL.
//! In case of using I2C to transmit followed by receive data, transmit length,
//! transmit data pointer, receive length and receive data pointer should be set
//! corresponding.
//!
//! \return Master transfer , could be:\b xtrue	master transfer successfully
//! \b xfalse master transfer not transfer successfully
//
//*****************************************************************************
xtBoolean 
I2CMasterTransfer(unsigned long ulBase, tI2CMasterTransferCfg *tCfg,
                  unsigned long ulOption)
{
    unsigned char *ucptxdat;
    unsigned char *ucprxdat;
    unsigned long ulCodeStatus;
    unsigned char ucTemp;

    //
    // Check the arguments.
    //
    xASSERT(ulBase == I2C0_BASE);

    //
    // Check the arguments.
    //
    xASSERT((ulOption == I2C_TRANSFER_POLLING) || 
            (ulOption == I2C_TRANSFER_INTERRUPT));
    
    //
	// reset all default state
	//
	ucptxdat = (unsigned char *) tCfg->pvWBuf;
	ucprxdat = (unsigned char *) tCfg->pvRBuf;

    //
    // Reset I2C setup value to default state
    //
    tCfg->ulWCount = 0;
    tCfg->ulRCount = 0;

    if (ulOption == I2C_TRANSFER_POLLING)
    {
        //
        // First Start condition 
        //
        //tCfg->retransmissions_count = 0;
        
        //
        // reset all default state
        //
        ucptxdat = (unsigned char *) tCfg->pvWBuf;
        ucprxdat = (unsigned char *) tCfg->pvRBuf;
        
        //
        // Reset I2C setup value to default state
        //
        tCfg->ulWCount = 0;
        tCfg->ulRCount = 0;
        ulCodeStatus = 0;

        //
        // Start command
        //
        ulCodeStatus = I2CStartSend(ulBase);
        if ((ulCodeStatus != I2C_I2STAT_M_TX_START) &&
            (ulCodeStatus != I2C_I2STAT_M_TX_RESTART))
        {
            I2CStopSend(ulBase);
            goto error;
        }

        //
        // In case of sending data first 
        //
        if ((tCfg->ulWLen != 0) && (tCfg->pvWBuf != 0))
        {
            // 
            // Send slave address + WR direction bit = 0 
            //
			ulCodeStatus = I2CByteSend(ulBase, (tCfg->ulSlave << 1));
            if (ulCodeStatus != I2C_I2STAT_M_TX_SLAW_ACK)
            {
                I2CStopSend(ulBase);
                goto error;
            }

            //
            // Send a number of data bytes 
            //
            while (tCfg->ulWCount < tCfg->ulWLen)
            {
                ulCodeStatus = I2CByteSend(ulBase, *ucptxdat); 
                if (ulCodeStatus != I2C_I2STAT_M_TX_DAT_ACK)
                {
                    I2CStopSend(ulBase);
                    goto error;
                }
                ucptxdat++;
                tCfg->ulWCount++;
			}
		}

        //
        // Second Start condition (Repeat Start)
        //
		if ((tCfg->ulWLen != 0) && (tCfg->pvWBuf != 0) &&
            (tCfg->ulRLen != 0) && (tCfg->pvRBuf != 0))
        {
            ulCodeStatus = I2CStartSend(ulBase);
            if ((ulCodeStatus != I2C_I2STAT_M_TX_START) &&
                (ulCodeStatus != I2C_I2STAT_M_TX_RESTART))
            {
                I2CStopSend(ulBase);
                goto error;
            }
        }

        // Then, start reading after sending data
        if ((tCfg->ulRLen != 0) && (tCfg->pvRBuf != 0))
        {
            //
            // Send slave address + RD direction bit = 1 
            //
            ulCodeStatus = I2CByteSend(ulBase, ((tCfg->ulSlave << 1) | 0x01));
            if (ulCodeStatus != I2C_I2STAT_M_RX_SLAR_ACK)
            {
                I2CStopSend(ulBase);
                goto error;
            }

            // Receive a number of data bytes
            while (tCfg->ulRCount < tCfg->ulRLen)
            {
                //
                // Note that: if data length is only one, the master should 
                // not issue an ACK signal on bus after reading to avoid of 
                // next data frame on slave side
                //
                if (tCfg->ulRCount< (tCfg->ulRLen- 1))
                {
                    //
                    // Issue an ACK signal for next data frame
                    //
                    ulCodeStatus = I2CByteGet(ulBase, &ucTemp, 1);
                    if (ulCodeStatus != I2C_I2STAT_M_RX_DAT_ACK)
                    {
                        I2CStopSend(ulBase);
                        goto error;
                    }
                } 
                else 
                {
                    //
                    // Do not issue an ACK signal
                    //
                    ulCodeStatus = I2CByteGet(ulBase, &ucTemp, 0);
                    if (ulCodeStatus != I2C_I2STAT_M_RX_DAT_NACK)
                    {
                        I2CStopSend(ulBase);
                        goto error;
					}
                }
				*ucprxdat++ = ucTemp;
				tCfg->ulRCount++;
            }
        }
        //
        // Send STOP condition 
        //
        I2CStopSend(ulBase);
        return xtrue;
error:
        //
        // Send stop condition
        //
        I2CStopSend(ulBase);
        return xfalse;
    }
    else if (ulOption == I2C_TRANSFER_INTERRUPT)
    {
        //
        // Setup tx_rx data, callback and interrupt handler
        //
        ucTemp = I2CNumGet(ulBase);
        g_tI2CSetup[ucTemp].ulSetup = (unsigned long) tCfg;
        
        //
        // Set direction phase, write first
        //
        g_tI2CSetup[ucTemp].ulDir = 0;

        //
        // First Start condition 
        //
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_STA;
		I2CIntEnable(ulBase);

        return (xtrue);
	}

    return xfalse;     
}

//*****************************************************************************
//
//! \brief Check Transfer of Master is complete or not. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get status of Master Transfer
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! \note This is only for master.
//!
//! \return Master transfer status, could be:\b xtrue master transfer completed,
//! \b xfalse master transfer have not completed yet
//
//*****************************************************************************
xtBoolean
I2CMasterTransferComplete(unsigned long ulBase)
{
	unsigned long ulRetval, ulTemp;
	ulTemp = I2CNumGet(ulBase);
	ulRetval = g_ulI2CMasterComplete[ulTemp];
	g_ulI2CMasterComplete[ulTemp] = xfalse;
	return ulRetval;
}


//*****************************************************************************
//
//! \brief Check Slave of Master is complete or not.
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get status of slave Transfer
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! \note this is only for slave
//!
//! \return Slave transfer status, could be:\b xtrue slave transfer completed,
//! \b xfalse slave transfer have not completed yet
//
//*****************************************************************************
xtBoolean
I2CSlaveTransferComplete(unsigned long ulBase)
{
	unsigned long ulRetval, ulTemp;
	ulTemp = I2CNumGet(ulBase);
	ulRetval = g_ulI2CSlaveComplete[ulTemp];
	g_ulI2CSlaveComplete[ulTemp] = xfalse;
	return ulRetval;
}

//*****************************************************************************
//
//! \brief Set the clock rate of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//! \param ucSlaveAddr specifies the slave address.
//! \param ulGeneralCall specifies enable General Call function or not.
//!
//! This function is to Set 4 7-bit slave addresses and enable General Call 
//! function of specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! The \e ucSlaveAddr is the I2C slave address,There are 4 slave addrss.
//! The ucSlaveAddr can be a 7-bit value.
//!
//! The \e ulGeneralCall is to enable the General Call function or not.
//! The ulGeneralCall can be one of the following values:
//! \b I2C_GENERAL_CALL_EN,\b I2C_GENERAL_CALL_DIS.
//!
//! \note this is only for slave
//!
//! \return None.
//
//*****************************************************************************
void 
I2CSlaveInit(unsigned long ulBase, unsigned char ucSlaveAddr, 
             unsigned long ulGeneralCall)
{    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));

    if (ulBase == I2C0_BASE)
    {
        SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
    }
    
    xHWREG(ulBase + I2C_O_CON) = I2C_CON_ENS1;

    xHWREG(ulBase + I2C_O_CON) = 0;
    
    xHWREG(ulBase + I2C_O_ADDR0) = (ucSlaveAddr << 1) | ulGeneralCall;
        
    xHWREG(ulBase + I2C_O_CON) = I2C_CON_ENS1;
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
}

//*****************************************************************************
//
//! \brief Transmit and Receive data in slave mode of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//! \param tCfg specifies Pointer to a I2C_M_SETUP_Type structure that
//!  contains specified information about the configuration for slave transfer.
//! \param ulOption specifies interrupt or polling mode.
//!
//! This function is to Transmit and Receive data in slave mode of specified I2C
//! port.
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! The \e tCfg is the I2C slave transfer setup data structure definitions.
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
//! \return Slave transfer, could be:\b xtrue  Slave transfer successfully
//! \b xfalse  Slave transfer not transfer successfully
//
//*****************************************************************************
xtBoolean 
I2CSlaveTransfer(unsigned long ulBase, tI2CSlaveTransferCfg *tCfg,
                 unsigned long ulOption)
{
    unsigned char *ucptxdat;
    unsigned char *ucprxdat;
    unsigned long ulCodeStatus;
    unsigned long ulTimeout;
    unsigned long ulTimeEn;
    unsigned long ulTemp;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));

    //
    // Check the arguments.
    //
    xASSERT((ulOption == I2C_TRANSFER_POLLING) || 
            (ulOption == I2C_TRANSFER_INTERRUPT));
    
    //
    // reset all default state
    //
    ucptxdat = (unsigned char *) tCfg->pvWBuf;
    ucprxdat = (unsigned char *) tCfg->pvRBuf;

    //
    // Reset I2C setup value to default state
    //
    tCfg->ulWCount = 0;
    tCfg->ulRCount = 0;
    //tCfg->status = 0;

    //
    // Polling option
    //
    if (ulOption == I2C_TRANSFER_POLLING)
    {
        //
        // Set AA bit to ACK command on I2C bus 
        //
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;

        //
        // Clear SI bit to be ready 
        //
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
        xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_STA;

        ulTimeEn = 0;
        ulTimeout = 0;
        
        while (1)
        {
            //
            // Check SI flag ready 
            if (xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI)
            {
                ulTimeEn = 0;
                ulCodeStatus = (xHWREG(ulBase + I2C_O_STATUS) & 
                                        I2C_STATUS_M);
                switch (ulCodeStatus)
                {
                //
                // No status information 
                //
                case I2C_I2STAT_NO_INF:
                    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
                    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
                    break;
                //
                // Reading phase
                //
                //
                // Own SLA+R has been received, ACK has been returned 
                //
                case I2C_I2STAT_S_RX_SLAW_ACK:
                    
                //
                // General call address has been received,ACK has been returned 
                //
                case I2C_I2STAT_S_RX_GENCALL_ACK:
                    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
                    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;                    
                    break;

                //
                // Previously addressed with own SLA;
                // DATA byte has been received;
                // ACK has been returned 
                //
                case I2C_I2STAT_S_RX_PRE_SLA_DAT_ACK:

                //
                // DATA has been received, ACK hasn been return 
                //
                case I2C_I2STAT_S_RX_PRE_GENCALL_DAT_ACK:

                //
                // All data bytes that over-flow the specified receive
                // data length, just ignore them.
                //
                    if ((tCfg->ulRCount < tCfg->ulRLen) && (tCfg->pvRBuf != 0))
                    {
                        *ucprxdat++ = (unsigned char)xHWREG(ulBase + I2C_O_DAT);
                        tCfg->ulRCount++;
                    }
                    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
                    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
                    break;

                //
                // Previously addressed with own SLA;
                // DATA byte has been received;
                // NOT ACK has been returned 
                //
                case I2C_I2STAT_S_RX_PRE_SLA_DAT_NACK:

                //
                // DATA has been received, NOT ACK has been returned 
                //
                case I2C_I2STAT_S_RX_PRE_GENCALL_DAT_NACK:
                    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
                    break;
                //
                // Note that: Return code only let us know a stop condition mixed
                // with a repeat start condition in the same code value.
                // So we should provide a time-out. In case this is really a stop
                // condition, this will return back after time out condition. Otherwise,
                // next session that is slave receive data will be completed.
                //
                //
                // A Stop or a repeat start condition 
                //
                case I2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX:
                    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;

                    //
                    // enable time out
                    //
                    ulTimeEn = 1;
                    ulTimeout = 0;
                    break;   
                    
                //
                // Writing phase 
                // Own SLA+R has been received, ACK has been returned 
                //
                case I2C_I2STAT_S_TX_SLAR_ACK:

                //
                // Data has been transmitted, ACK has been received 
                //
                case I2C_I2STAT_S_TX_DAT_ACK:
                    
                    //
                    // All data bytes that over-flow the specified receive
                    // data length, just ignore them.
                    //
                    if ((tCfg->ulWCount < tCfg->ulWLen) && (tCfg->pvWBuf != 0))
                    {
                        xHWREG(ulBase + I2C_O_DAT) = *ucptxdat++;
                        tCfg->ulWCount++;
                    }
                    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
                    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
                    break;

                //
                // Data has been transmitted, NACK has been received,
                // that means there's no more data to send, exit now 
                //
                //
                // Note: Don't wait for stop event since in slave transmit mode,
                // since there no proof lets us know when a stop signal has been received
                // on slave side.
                //
                case I2C_I2STAT_S_TX_DAT_NACK:
                    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
                    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;

                    //
                    // enable time out
                    //
                    ulTimeEn = 1;
                    ulTimeout = 0;
                    break;
                //
                // Other status must be captured
                //
                default:
                    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
                    goto s_error;
                }
            } 
            else if (ulTimeEn)
            {
                if (ulTimeout++ > 0x10000)
                {
                    //
                    // it's really a stop condition, goto end stage
                    //
                    goto s_end_stage;
                }
            }
        }

s_end_stage:
        //
        // Clear AA bit to disable ACK on I2C bus 
        //
        xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_AA;

        //
        // Check if there's no error during operation
        // Update status
        //
        return xtrue;

s_error:
        //
        // Clear AA bit to disable ACK on I2C bus 
        //
        xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_AA;

        //
		// Update status
		//
        //tCfg->status = ulCodeStatus;
        return xfalse;
    }

    else if (ulOption == I2C_TRANSFER_INTERRUPT)
    {
        //
        // Setup tx_rx data, callback and interrupt handler
        //
        ulTemp = I2CNumGet(ulBase);
        g_tI2CSetup[ulTemp].ulSetup = (unsigned long) tCfg;

        //
        // Set direction phase, read first
        //
        g_tI2CSetup[ulTemp].ulDir = 1;

        //
        // Enable AA
        //
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
        xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_STA;
        I2CIntEnable(ulBase);

        return (xtrue);

    }
    return xfalse;
}

//*****************************************************************************
//
//! \brief Set the slave address of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//! \param ucSlaveNum specifies the salve address number.
//! \param ucSlaveAddr specifies the slave address.
//! \param ulGeneralCall specifies enable General Call function or not.
//!
//! This function is to Set 4 7-bit slave addresses and enable General Call 
//! function of specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE.
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
//!
//! \note this is only for slave
//!
//! \return None.
//
//*****************************************************************************
void 
I2CSlaveOwnAddressSet(unsigned long ulBase, unsigned char ucSlaveNum, 
                      unsigned char ucSlaveAddr,  unsigned long ulGeneralCall)
{
    unsigned long ulTemp[4] = {0x04, 0x18, 0x1C, 0x20};
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));

    //
    // Check the arguments.
    //
    xASSERT((ucSlaveNum == 0) || (ucSlaveNum == 1) ||
            (ucSlaveNum == 2) || (ucSlaveNum == 3));
    
    //
    // Check the arguments.
    //
    xASSERT((ulGeneralCall == I2C_GENERAL_CALL_EN) || 
            (ulGeneralCall == I2C_GENERAL_CALL_DIS));    
        

    xHWREG(ulBase + ulTemp[ucSlaveNum]) |= ((ucSlaveAddr << 1) |
                                            ulGeneralCall);
}

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
//! The \e ulBase must be:\b I2C0_BASE.
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
void 
I2CSlaveOwnAddressMaskSet(unsigned long ulBase,
                          unsigned char ucSlaveNum,
                          unsigned char ucSlaveAddrMask)
{
    unsigned long ulTemp[4] = {0x24, 0x28, 0x2C, 0x30};
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));

    //
    // Check the arguments.
    //
    xASSERT((ucSlaveNum == 0) || (ucSlaveNum == 1) ||
            (ucSlaveNum == 2) || (ucSlaveNum == 3));

    xHWREG(ulBase + ulTemp[ucSlaveNum]) |= (ucSlaveAddrMask << 1);
}

//*****************************************************************************
//
//! \brief Get I2C status of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get I2C status of the specified I2C port.
//! There are 26 status codes. Please refer to xi2c.h NUC123_I2C_STATUS_Type
//! in detail.
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! \return I2C status.
//
//*****************************************************************************
unsigned long 
I2CStatusGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));

    return (xHWREG(ulBase + I2C_O_STATUS) & I2C_STATUS_M);
}

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
void xI2CMasterDataPut(unsigned long ulBase, unsigned char ucData)
{
    //
    // Send data to I2C BUS
    //
    xHWREG(ulBase + I2C_O_DAT) = ucData;
        
    //
    // Make sure AA bit is active,and clear EI 
    //
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
}

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
unsigned long xI2CMasterDataGet(unsigned long ulBase)
{
    unsigned long ulData;
    ulData = xHWREG(ulBase + I2C_O_DAT);
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
    return ulData;
}

//*****************************************************************************
//
//! \brief Enable I2C interrupt of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to enable I2C interrupt of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! \return None.
//
//*****************************************************************************    
void 
I2CIntEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_EI;
    xIntEnable(INT_I2C0);
}

//*****************************************************************************
//
//! \brief initialize interrupts callback for the specified Port.
//!
//! \param ulPort is the base address of the I2C port.
//! \param xtI2CCallback is callback for the specified Port.
//!
//! Initialize interrupts callback for the specified Port.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CIntCallbackInit(unsigned long ulBase, xtEventCallback xtI2CCallback)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    g_pfnI2CHandlerCallbacks[0] = xtI2CCallback;

}

//*****************************************************************************
//
//! \brief Disable I2C interrupt of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to disable I2C interrupt of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CIntDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_EI;
    xIntDisable(INT_I2C0);
}


//*****************************************************************************
//
//! \brief Enable I2C module of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to enable I2C module of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_ENS1;
}

void
I2CWakeupEnable(unsigned long ulBase)
{
	xHWREG(ulBase + I2C_O_WKUPCON) |= I2C_WKUPCON_EN;
}

void
I2CWakeupDisable(unsigned long ulBase)
{
	xHWREG(ulBase + I2C_O_WKUPCON) &= ~I2C_WKUPCON_EN;
}
int
I2CWakeupStatusGet(unsigned long ulBase)
{
	return xHWREG(ulBase + I2C_O_WKUPSTS) & I2C_WKUPCON_IF;
}

//*****************************************************************************
//
//! \brief Disable I2C module of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to disable I2C module of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_ENS1;
}    

//*****************************************************************************
//
//! \brief Get the I2C interrupt flag of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get the I2C interrupt flag of the specified I2C port.
//!
//! The \e ulBase must be: \b I2C0_BASE.
//!
//! \return could be:\b xtrue the interrupt has been triggered.
//! \b xfalse the interrupt has not been triggered.
//
//*****************************************************************************
xtBoolean 
I2CIntFlagGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    return ((xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Get the I2C time out flag of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get the I2C time out flag of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! \return could be:\b xtrue the Time out has been occur.
//! \b xfalse the Time out has not been occur.
//*****************************************************************************
xtBoolean 
I2CTimeoutFlagGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    return ((xHWREG(ulBase + I2C_O_TOC) & I2C_TOC_TIF) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Clear the I2C interrupt flag of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to clear the I2C interrupt flag of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CIntFlagClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));

    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
}

//*****************************************************************************
//
//! \brief Clear the I2C time out flag of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to clear the I2C time out flag of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CTimeoutFlagClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));

    xHWREG(ulBase + I2C_O_TOC) |= I2C_TOC_TIF;
}

//*****************************************************************************
//
//! \brief Enable/Disable I2C 14-bit timeout counter of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulEnable specifies Enable/Disable 14-bit timeout counter.
//! \param ulDiv4 specifies 4 time the 14-bit timeout counter or not.
//!
//! This function is to Enable/Disable I2C 14-bit timeout counter and 
//! set div4 bit of timeout counter of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE.
//!
//! The \e ulEnable can be one of the following values:
//! \b I2C_TIMEOUT_EN, \b I2C_TIMEOUT_DIS.
//!
//! The \e ulDiv4 can be one of the following values:
//! \b I2C_TIMEOUT_DIV4, \b I2C_TIMEOUT_DIV_NO.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CTimeoutCounterSet(unsigned long ulBase, unsigned long ulEnable,
                     unsigned long ulDiv4)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));

    //
    // Check the arguments.
    //
    xASSERT((ulEnable == I2C_TIMEOUT_EN) || (ulEnable == I2C_TIMEOUT_DIS));

    //
    // Check the arguments.
    //
    xASSERT((ulDiv4 == I2C_TIMEOUT_DIV4) || (ulDiv4 == I2C_TIMEOUT_DIV_NO));

    xHWREG(ulBase + I2C_O_TOC) &= ~0x00000006;
    xHWREG(ulBase + I2C_O_TOC) |= ulEnable | ulDiv4;
}

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
//! Users can call I2CMasterBusy() to check if all the bus transmition 
//! complete, the call I2CMasterErr() to check if any error occurs. 
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call I2CMasterWriteRequestS2() to continue transmit data to slave.
//! Users can also call I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! For this function returns immediately, it is always using in the interrupt
//! hander.
//!
//! \return None.
//
//*****************************************************************************
void 
xI2CMasterWriteRequestS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                         unsigned char ucData, xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));
    
    //
    // Send start
    //    
    ulStatus = I2CStartSend(ulBase);
    
    if(!(ulStatus == I2C_I2STAT_M_TX_START))
    {
        I2CStopSend(ulBase);
        return;
    }
        
    //
    // Send address
    //
    ulStatus = I2CByteSend(ulBase, (ucSlaveAddr << 1)); 
    if(!(ulStatus == I2C_I2STAT_M_TX_SLAW_ACK))
    {
        I2CStopSend(ulBase);
        return;
    }
      
    //
    // Send data to I2C BUS
    //
    xHWREG(ulBase + I2C_O_DAT) = ucData;
        
    //
    // Make sure AA and EI bit is not active,and clear EI 
    //
    //xHWREG(ulBase + I2C_O_CON) &= ~(I2C_CON_AA | I2C_CON_EI);
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
    
    if(bEndTransmition)
    {
        I2CStopSend(ulBase);
    }
}

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
//! I2CMasterWriteRequestS1() without any error), and haven't release it, users 
//! can call this function to continue transmit data to slave.
//!
//! This function just send request to transmit the data, and it returns 
//! immediately, no waiting any bus transmition to complete. 
//!
//! Users can call I2CMasterBusy() to check if all the bus transmition 
//! complete, the call I2CMasterErr() to check if any error occurs. Users call
//! also can I2CMasterStop() to terminate this transmition and release the 
//! I2C bus.
//!
//! For this function returns immediately, it is always using in the interrupt
//! hander.
//!
//! \return None.
//
//*****************************************************************************
void
xI2CMasterWriteRequestS2(unsigned long ulBase, unsigned char ucData,
                         xtBoolean bEndTransmition)
{    
    //
    // Check the arguments.
    //    
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    //
    // Send data to I2C BUS
    //
    xHWREG(ulBase + I2C_O_DAT) = ucData;
        
    //
    // Make sure AA and EI bit is not active,and clear EI 
    //
    xHWREG(ulBase + I2C_O_CON) &= ~(I2C_CON_AA | I2C_CON_EI);
    
    //
    // Send the stop if End Transmition.
    //
    if(bEndTransmition)
    {
        I2CStopSend(ulBase);
    }    
}

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
//! - \ref I2C_MASTER_ERR_NONE     - \b 0, no error
//! - \ref I2C_MASTER_ERR_ADDR_ACK - The transmitted address was not acknowledged
//! - \ref I2C_MASTER_ERR_DATA_ACK - The transmitted data was not acknowledged
//! - \ref I2C_MASTER_ERR_ARB_LOST - The I2C controller lost arbitration.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call I2CMasterWriteS2() to continue transmit data to slave.
//! Users call also can I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! This function is always used in thread mode.
//!
//! \return Returns the master error status.
//
//*****************************************************************************
unsigned long 
xI2CMasterWriteS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                  unsigned char ucData, xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //    
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));
    
    //
    // Send write request
    //
    xI2CMasterWriteRequestS1(ulBase, ucSlaveAddr, ucData, xfalse);
    
    //
    // Wait the SI be set again by hardware
    //
    while (!(xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI));
    ulStatus = xHWREG(ulBase + I2C_O_STATUS) & I2C_STATUS_M;
    if(!(ulStatus == I2C_I2STAT_M_TX_DAT_ACK))
    {
        ulStatus = xI2CMasterError(ulBase);
        I2CStopSend(ulBase);
        return ulStatus;
    }

    if(bEndTransmition)
    {
        I2CStopSend(ulBase);
    }
    
    //
    // return the error status
    //
    return xI2C_MASTER_ERR_NONE;
    
}

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
//! I2CMasterWriteS1() without any error), and haven't release it, users 
//! can call this function to continue transmit data to slave.
//!
//! This function transmit the data to the slave, and waiting for all bus 
//! transmition complete.
//!
//! Users can then check the return value to see if any error occurs:
//! - \ref I2C_MASTER_ERR_NONE     - \b 0, no error
//! - \ref I2C_MASTER_ERR_ADDR_ACK - The transmitted address was not acknowledged
//! - \ref I2C_MASTER_ERR_DATA_ACK - The transmitted data was not acknowledged
//! - \ref I2C_MASTER_ERR_ARB_LOST - The I2C controller lost arbitration.
//!
//! Then users can call this function to continue transmit data to slave.
//! Users call also call I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! This function is always used in thread mode.
//!
//! \return Returns the master error status.
//
//*****************************************************************************
unsigned long 
xI2CMasterWriteS2(unsigned long ulBase, unsigned char ucData,
                  xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //    
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    //
    // Send write request
    //
    xI2CMasterWriteRequestS2(ulBase, ucData, xfalse);
    
    //
    // Wait the SI be set again by hardware
    //
    while (!(xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI));
    ulStatus = xHWREG(ulBase + I2C_O_STATUS) & I2C_STATUS_M;
    if(!(ulStatus == I2C_I2STAT_M_TX_DAT_ACK))
    {
        ulStatus = xI2CMasterError(ulBase);
        I2CStopSend(ulBase);
        return ulStatus;
    }

    if(bEndTransmition)
    {
        I2CStopSend(ulBase);
    }
    
    //
    // return the error status
    //
    return xI2C_MASTER_ERR_NONE;   
    
}

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
//! I2CMasterErr() to see what error occurs.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call I2CMasterWriteS2() / I2CMasterWriteBufS2() to continue transmit data 
//! to slave. Users call also call I2CMasterStop() to terminate this transmition 
//! and release the I2C bus.
//!
//! This function is always used in thread mode.
//!
//! \return Returns the data number that have been successully tranmited.
//
//*****************************************************************************
unsigned long
xI2CMasterWriteBufS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                     const unsigned char *pucDataBuf, unsigned long ulLen, 
                     xtBoolean bEndTransmition)
{
    
    unsigned long ulStatus;
    unsigned long ulWritten;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    xASSERT(pucDataBuf);
    
    if(ulLen == 1)
    {
        ulStatus = xI2CMasterWriteS1(ulBase, ucSlaveAddr, 
                                    pucDataBuf[0], bEndTransmition);
        
        return (ulStatus == xI2C_MASTER_ERR_NONE) ? 1 : 0;
    }

    //
    // Send start 
    //    
    ulStatus = I2CStartSend(ulBase);
    if(!(ulStatus == I2C_I2STAT_M_TX_START))
    {
        I2CStopSend(ulBase);
        return 0;
    }
    //
    // Send address
    //    
    ulStatus = I2CByteSend(ulBase, (ucSlaveAddr << 1));
    if(!(ulStatus == I2C_I2STAT_M_TX_SLAW_ACK))
    {
        I2CStopSend(ulBase);
        return 0;
    }

    //
    // Send data
    //    
    ulStatus = I2CByteSend(ulBase, *pucDataBuf);
    
    //
    // Check if any error occurs
    //
    if(!(ulStatus == I2C_I2STAT_M_TX_DAT_ACK))
    {
         I2CStopSend(ulBase);
         return 0;  
    }
    else
    {
        ulWritten = 1;
    }
    
    ulWritten += xI2CMasterWriteBufS2(ulBase, 
                                     &pucDataBuf[1], 
                                     ulLen - 1, 
                                     bEndTransmition);
    
    return ulWritten;

}

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
//! I2CMasterWriteS1() or I2CMasterWriteBufS1() without any error), and haven't 
//! release it, users can call this function to continue transmit data to slave.
//!
//! This function transmit the data one by one to the slave, waiting for every  
//! data transmition complete, and continue next data transmition, until all  
//! complete. If there is any error occurs, the remain data will be canceled.
//!
//! Users can then check the return value to see how many datas have been 
//! successfully transmited. if the number != ulLen, user can call 
//! I2CMasterErr() to see what error occurs.
//!
//! Then users can call I2CMasterWriteS2() or this function to continue  
//! transmit data to slave. Users call also call I2CMasterStop() to terminate  
//! this transmition and release the I2C bus.
//!
//! This function is always used in thread mode.
//!
//! \return Returns the data number that have been successully tranmited.
//
//*****************************************************************************
unsigned long 
xI2CMasterWriteBufS2(unsigned long ulBase, const unsigned char *pucDataBuf,
                     unsigned long ulLen, xtBoolean bEndTransmition)
{
    unsigned long i;
    unsigned long ulStatus;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    xASSERT(pucDataBuf);
    
    for(i = 0; i < ulLen - 1; i++)                              
    {       
        //
        // Send data
        //    
        ulStatus = I2CByteSend(ulBase, *pucDataBuf++);
    
        //
        // Check if any error occurs
        //
        if(!(ulStatus == I2C_I2STAT_M_TX_DAT_ACK))
        {
            I2CStopSend(ulBase);
            return i;
               
        }      
    }   
    //
    // Waiting the I2C controller to idle
    //    
    ulStatus = I2CByteSend(ulBase, *pucDataBuf);
    if(!(ulStatus == I2C_I2STAT_M_TX_DAT_ACK))
    {
        I2CStopSend(ulBase);
        return i;      
    }  
    
    if(bEndTransmition)
    {
        I2CStopSend(ulBase);
    }    
    
    return ulLen;
    
}

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
//! Users can call I2CMasterBusy() to check if all the bus transmition 
//! complete, then call I2CMasterErr() to check if any error occurs. Then user 
//! can get the data by calling I2CMasterDataGet() if there is no error occurs.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call I2CMasterReadRequestS2() to continue receive data from slave.
//! Users call also can I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! For this function returns immediately, it is always using in the interrupt
//! hander.
//!
//! \return None.
//
//*****************************************************************************
void
xI2CMasterReadRequestS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                        xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
    //
    // Send start and address
    //    
    ulStatus = I2CStartSend(ulBase);
    if(!((ulStatus == I2C_I2STAT_M_TX_START) || 
         (ulStatus == I2C_I2STAT_M_TX_RESTART)))
    {
        I2CStopSend(ulBase);
        return ;
    }
    //
    // Send address
    //    
    ulStatus = I2CByteSend(ulBase, (ucSlaveAddr << 1) | 1) ;
    if(!(ulStatus == I2C_I2STAT_M_RX_SLAR_ACK))
    {
        I2CStopSend(ulBase);
        return ;
    }
    if(bEndTransmition)
    {
        xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_AA;
        I2CStopSend(ulBase);
    }
}

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
//! I2CMasterReadRequestS1() without any error), and haven't release it, users 
//! can call this function to continue receive data from slave.
//!
//! If bEndTransmition is xtrue, the receive operation will followed by an 
//! negative ACK and STOP condition.
//!
//! Users can call I2CMasterBusy() to check if all the bus transmition 
//! complete, then call I2CMasterErr() to check if any error occurs. Then user 
//! can get the data by calling I2CMasterDataGet() if there is no error occurs.
//!
//! Then users can call this function to continue receive data from slave.
//! Users call also can I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! For this function returns immediately, it is always using in the interrupt
//! hander.
//!
//! \return None.
//
//*****************************************************************************
void
xI2CMasterReadRequestS2(unsigned long ulBase, xtBoolean bEndTransmition)
{  
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    //
    // Send the stop if End Transmition.
    //
    if(bEndTransmition)
    {
        xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_AA;
        I2CStopSend(ulBase);
    }     
}

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
//! Users can call I2CMasterBusy() to check if all the bus transmition 
//! complete, then call I2CMasterErr() to check if any error occurs. Then user 
//! can get the data by calling I2CMasterDataGet() if there is no error occurs.
//!
//! Users call also can I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! For this function returns immediately, it is always using in the interrupt
//! hander.
//!
//! \return None.
//
//*****************************************************************************
void
xI2CMasterReadLastRequestS2(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    //
    // RECEIVE operation with negative ACK(no stop)
    //
    xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_AA;    
    
}

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
//! - \ref I2C_MASTER_ERR_NONE     - \b 0, no error
//! - \ref I2C_MASTER_ERR_ADDR_ACK - The transmitted address was not acknowledged
//! - \ref I2C_MASTER_ERR_DATA_ACK - The transmitted data was not acknowledged
//! - \ref I2C_MASTER_ERR_ARB_LOST - The I2C controller lost arbitration.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call I2CMasterReadS2() to continue receive data from slave.
//! Users call also can I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! This function is usually used in thread mode.
//!
//! \return Returns the master error status.
//
//*****************************************************************************
unsigned long 
xI2CMasterReadS1(unsigned long ulBase, 
                 unsigned char ucSlaveAddr,
                 unsigned char *pucData,
                 xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    xASSERT(pucData);
    
    xI2CMasterReadRequestS1(ulBase, ucSlaveAddr, xfalse);
 
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
    SysCtlDelay(100);
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
    
    while (!(xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI));

    *pucData = xHWREG(ulBase + I2C_O_DAT);
    
    ulStatus = (xHWREG(ulBase + I2C_O_STATUS) & I2C_STATUS_M);
    
    if (ulStatus != I2C_I2STAT_M_RX_DAT_ACK)
    {
        ulStatus = xI2CMasterError(ulBase);
        I2CStopSend(ulBase);
        return ulStatus;
    }      
    if(bEndTransmition)
    {
        I2CStopSend(ulBase);
    }  
    
    //
    // return the error status
    //
    return xI2C_MASTER_ERR_NONE;       
      
}

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
//! I2CMasterReadS1() without any error), and haven't release it, users can 
//! call this function to continue receive data from the slave.
//!
//! If bEndTransmition is xtrue, the receive operation will followed by an 
//! negative ACK and STOP condition.
//!
//! It will be waiting for all bus transmition complete before return.
//! Users can then check the return value to see if any error occurs:
//! - \ref I2C_MASTER_ERR_NONE     - \b 0, no error
//! - \ref I2C_MASTER_ERR_ADDR_ACK - The transmitted address was not acknowledged
//! - \ref I2C_MASTER_ERR_DATA_ACK - The transmitted data was not acknowledged
//! - \ref I2C_MASTER_ERR_ARB_LOST - The I2C controller lost arbitration.
//!
//! Then useres can call this function to continue receive data from slave.
//! Users call also can I2CMasterStop() to terminate this transmition and 
//! release the I2C bus.
//!
//! This function is usually used in thread mode.
//!
//! \return Returns the master error status.
//
//*****************************************************************************
unsigned long
xI2CMasterReadS2(unsigned long ulBase,
                 unsigned char *pucData,
                 xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));

    xI2CMasterReadRequestS2(ulBase, xfalse);

    if(bEndTransmition)
    {
        xHWREG(ulBase + I2C_O_CON) &= ~I2C_CON_AA;
    } 
    
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
    
    //
    // Waiting the I2C controller to be transmited
    //
    while (!(xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI));
    *pucData = (unsigned char)xHWREG(ulBase + I2C_O_DAT);
    
    //
    // Get the Status code
    //
    ulStatus =  (xHWREG(ulBase + I2C_O_STATUS) & I2C_STATUS_M);
    
    //
    // Waiting the I2C controller to be transmited
    //
    if (ulStatus != I2C_I2STAT_M_RX_DAT_ACK)
    {
        ulStatus = xI2CMasterError(ulBase);
        I2CStopSend(ulBase);
        return ulStatus;
    } 

    if(bEndTransmition)
    {
        I2CStopSend(ulBase);
    } 
    
    //
    // return the error status
    //
    return xI2C_MASTER_ERR_NONE;    
}

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
//! I2CMasterErr() to see what error occurs.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call I2CMasterReadS2() or I2CMasterReadBufS2() to continue receive data .
//! from slave .Users call also can I2CMasterStop() to terminate this transmition
//! and release the I2C bus.
//!
//! This function is usually used in thread mode.
//!
//! \return Returns the data number that have been successully received.
//
//*****************************************************************************
unsigned long 
xI2CMasterReadBufS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                    unsigned char* pucDataBuf, unsigned long ulLen,
                    xtBoolean bEndTransmition)
{
    unsigned long ulStatus,ulStatusStart;
    unsigned long ulRead;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    xASSERT(pucDataBuf);
    
    if(ulLen == 0)
    {
        return 0;   
    }
    
    else if(ulLen == 1)
    {
        ulStatus = xI2CMasterReadS1(ulBase, ucSlaveAddr, 
                                   pucDataBuf, bEndTransmition); 

        if (ulStatus == xI2C_MASTER_ERR_NONE)
        {
            pucDataBuf[0] = xHWREG(ulBase + I2C_O_DAT);
            
            return 1;
        }
        else
        {
            return 0;   
        }
    }

    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA;
    
    //
    // Send start and address
    //    
    ulStatusStart = I2CStartSend(ulBase);
    if(!((ulStatusStart == I2C_I2STAT_M_TX_START) || 
         (ulStatusStart == I2C_I2STAT_M_TX_RESTART)))
    {
        I2CStopSend(ulBase);
        return 0;
    }
    //
    // Send address
    //    
    //ulStatus = I2CByteSend(ulBase, (ucSlaveAddr << 1) | 1) ;
    //
    // Make sure start bit is not active,but do not clear SI 
    //
    if (xHWREG(ulBase + I2C_O_CON) & I2C_CON_STA)
    {
        xHWREG(ulBase + I2C_O_CON) &= ~(I2C_CON_STA | I2C_CON_SI);
    }
            
    //
    // Send data to I2C BUS
    //
    xHWREG(ulBase + I2C_O_DAT) = (ucSlaveAddr << 1) | 1;
        
    //
    // Make sure AA and EI bit is not active,and clear SI 
    //
    xHWREG(ulBase + I2C_O_CON) &= ~(I2C_CON_EI);
        
    //
    // Wait the SI be set again by hardware
    //
    while (!(xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI));
        
    //
    // Return the i2c status
    //
    ulStatus = (xHWREG(ulBase + I2C_O_STATUS) & I2C_STATUS_M);
    if(!(ulStatus == I2C_I2STAT_M_RX_SLAR_ACK))
    {
        I2CStopSend(ulBase);
        return 0;
    }

    //
    // Waiting the I2C controller to be transmited
    //
    //xI2CMasterReadRequestS1(ulBase, ucSlaveAddr, xfalse);
    if(ulStatusStart == I2C_I2STAT_M_TX_RESTART)
    {   
        xHWREG(ulBase + I2C_O_CON) |= I2C_CON_AA; 
    }
    SysCtlDelay(100);
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
    
    while (!(xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI));

    pucDataBuf[0] = xHWREG(ulBase + I2C_O_DAT);
    
    //ulStatus = I2CByteGet(ulBase, &pucDataBuf[0], 1);
    
    ulRead = 1;
    
    ulRead += xI2CMasterReadBufS2(ulBase, 
                                 &pucDataBuf[1], 
                                 ulLen - 1, 
                                 bEndTransmition);    
    
    
    return ulRead;
    
}

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
//! I2CMasterReadS1() or I2CMasterReadBufS1() without any error), and haven't 
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
//! I2CMasterErr() to see what error occurs.
//!
//! After the master obtained control of the bus, and haven't release it, users 
//! can call I2CMasterReadS2() or I2CMasterReadBufS2() to continue receive data
//! from slave. Users call also can I2CMasterStop() to terminate this transmition
//! and release the I2C bus.
//!
//! This function is usually used in thread mode.
//!
//! \return Returns the data number that have been successully received.
//
//*****************************************************************************
unsigned long
xI2CMasterReadBufS2(unsigned long ulBase, unsigned char *pucDataBuf,
                    unsigned long ulLen, xtBoolean bEndTransmition)
{
    unsigned long i;
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    xASSERT(pucDataBuf);

    if(ulLen == 0) 
    {
        return 0;
    }
    

    for(i = 0; i < ulLen - 1; i++)                              
    {                           
        //
        // Issue an ACK signal for next data frame
        //
        ulStatus = I2CByteGet(ulBase, pucDataBuf++, 1);
        if (ulStatus != I2C_I2STAT_M_RX_DAT_ACK)
        {
            I2CStopSend(ulBase);
            return i;
        }
    }  

    if(bEndTransmition)
    {
        xHWREG(ulBase + I2C_O_CON) &= ~(I2C_CON_AA|I2C_CON_SI);
    }
    
    xHWREG(ulBase + I2C_O_CON) |= I2C_CON_SI;
    
    while (!(xHWREG(ulBase + I2C_O_CON) & I2C_CON_SI));

    *pucDataBuf = xHWREG(ulBase + I2C_O_DAT);

    if(bEndTransmition)
    {
        I2CStopSend(ulBase);
    }
    
    return ulLen; 
    
}

//*****************************************************************************
//
//! Gets the error status of the I2C Master module.
//!
//! \param ulBase is the base address of the I2C Master module.
//!
//! This function is used to obtain the error status of the Master module send
//! and receive operations.
//!
//! \return Returns the error status, as one of \b xI2C_MASTER_ERR_NONE,
//! \b xI2C_MASTER_ERR_ADDR_ACK, \b xI2C_MASTER_ERR_DATA_ACK, or
//! \b xI2C_MASTER_ERR_ARB_LOST.
//
//*****************************************************************************
unsigned long xI2CMasterError(unsigned long ulBase)
{
    unsigned long ulStatus;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE));
    
    ulStatus = (xHWREG(ulBase + I2C_O_STATUS) & I2C_STATUS_M);
    
    if((ulStatus == I2C_I2STAT_M_TX_DAT_NACK) ||
       (ulStatus == I2C_I2STAT_M_RX_DAT_NACK))
    {
        return xI2C_MASTER_ERR_ADDR_ACK;
    }
    if((ulStatus == I2C_I2STAT_M_TX_SLAW_NACK) ||
       (ulStatus == I2C_I2STAT_M_RX_SLAR_NACK))
    {
        return xI2C_MASTER_ERR_DATA_ACK;
    }
    if((ulStatus == I2C_I2STAT_M_TX_ARB_LOST))
    {
        return xI2C_MASTER_ERR_ARB_LOST;
    }
    return xI2C_MASTER_ERR_NONE;
}
