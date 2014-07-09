//*****************************************************************************
//
//! \file xi2c.c
//! \brief Driver for the I2C
//! \version V2.1.1.1
//! \date 6/14/2014
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2014, CooCox
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
#include "CoX.h"
#include "xhw_sysctl.h"
#include "xhw_i2c.h"

//*****************************************************************************
//
// An array is I2C callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnI2CHandlerCallbacks[5]={0};

//*****************************************************************************
//
//! \brief I2C0 interrupt handler. Clear the I2C0 interrupt flag and execute the
//! callback function.
//!
//! \param none.
//!
//! This function is the I2C0 interrupt handler,it will Clear the I2C0
//! interrupt flag and execute the callback function if there be one.
//!
//! \note There are two source of this interrupt.One is I2C0 function
//! and one is I2C0 time out.
//!
//! \return None.
//
//*****************************************************************************
void
I2C0_IRQHandler(void)
{
    unsigned long ulBase = I2C0_BASE;
    unsigned long ulStatus = xHWREG(ulBase + I2C_STATUS);
    unsigned long ulTimeout;
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
        xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
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
        xI2CSlaveIntDisable(ulBase, 0);
        xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
        //
        // enable time out
        //
        ulTimeout = 0x10000;
        while(1)
        {
            if (xHWREG(ulBase + I2C_CON) & I2C_CON_SI)
            {
                //
                // re-Enable interrupt
                //
                xI2CSlaveIntEnable(ulBase, 0);
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
}

//*****************************************************************************
//
//! \brief I2C1 interrupt handler. Clear the I2C1 interrupt flag and execute the
//! callback function.
//!
//! \param none.
//!
//! This function is the I2C1 interrupt handler,it will Clear the I2C1
//! interrupt flag and execute the callback function if there be one.
//!
//! \note There are two source of this interrupt.One is I2C1 function
//! and one is I2C1 time out.
//!
//! \return None.
//
//*****************************************************************************
void
I2C1_IRQHandler(void)
{
    unsigned long ulBase = I2C1_BASE;
    unsigned long ulStatus = xHWREG(ulBase + I2C_STATUS);
    unsigned long ulTimeout;
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
        xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
    }

    if((ulStatus == I2C_I2STAT_S_RX_PRE_SLA_DAT_ACK) ||
       (ulStatus == I2C_I2STAT_S_RX_PRE_GENCALL_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[1](0, 0, xI2C_SLAVE_EVENT_RREQ, 0);
    }
    if((ulStatus == I2C_I2STAT_S_TX_SLAR_ACK) ||
       (ulStatus == I2C_I2STAT_S_TX_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[1](0, 0, xI2C_SLAVE_EVENT_TREQ, 0);
    }
    if((ulStatus == I2C_I2STAT_M_TX_SLAW_ACK) ||
       (ulStatus == I2C_I2STAT_M_TX_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[1](0, 0, xI2C_MASTER_EVENT_TX, 0);
    }
    if((ulStatus == I2C_I2STAT_M_RX_SLAR_ACK) ||
       (ulStatus == I2C_I2STAT_M_RX_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[1](0, 0, xI2C_MASTER_EVENT_RX, 0);
    }
    if((ulStatus == I2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX))
    {
        //
        //Temporally lock the interrupt for timeout condition
        //
        xI2CSlaveIntDisable(ulBase, 0);
        xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
        //
        // enable time out
        //
        ulTimeout = 0x10000;
        while(1)
        {
            if (xHWREG(ulBase + I2C_CON) & I2C_CON_SI)
            {
                //
                // re-Enable interrupt
                //
                xI2CSlaveIntEnable(ulBase, 0);
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
                    g_pfnI2CHandlerCallbacks[1](0, 0, xI2C_SLAVE_EVENT_STOP, 0);
                    break;
                }
            }
        }
    }
}

//*****************************************************************************
//
//! \brief I2C2 interrupt handler. Clear the I2C2 interrupt flag and execute the
//! callback function.
//!
//! \param none.
//!
//! This function is the I2C2 interrupt handler,it will Clear the I2C2
//! interrupt flag and execute the callback function if there be one.
//!
//! \note There are two source of this interrupt.One is I2C2 function
//! and one is I2C2 time out.
//!
//! \return None.
//
//*****************************************************************************
void
I2C2_IRQHandler(void)
{
    unsigned long ulBase = I2C2_BASE;
    unsigned long ulStatus = xHWREG(ulBase + I2C_STATUS);
    unsigned long ulTimeout;
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
        xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
    }

    if((ulStatus == I2C_I2STAT_S_RX_PRE_SLA_DAT_ACK) ||
       (ulStatus == I2C_I2STAT_S_RX_PRE_GENCALL_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[2](0, 0, xI2C_SLAVE_EVENT_RREQ, 0);
    }
    if((ulStatus == I2C_I2STAT_S_TX_SLAR_ACK) ||
       (ulStatus == I2C_I2STAT_S_TX_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[2](0, 0, xI2C_SLAVE_EVENT_TREQ, 0);
    }
    if((ulStatus == I2C_I2STAT_M_TX_SLAW_ACK) ||
       (ulStatus == I2C_I2STAT_M_TX_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[2](0, 0, xI2C_MASTER_EVENT_TX, 0);
    }
    if((ulStatus == I2C_I2STAT_M_RX_SLAR_ACK) ||
       (ulStatus == I2C_I2STAT_M_RX_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[2](0, 0, xI2C_MASTER_EVENT_RX, 0);
    }
    if((ulStatus == I2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX))
    {
        //
        //Temporally lock the interrupt for timeout condition
        //
        xI2CSlaveIntDisable(ulBase, 0);
        xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
        //
        // enable time out
        //
        ulTimeout = 0x10000;
        while(1)
        {
            if (xHWREG(ulBase + I2C_CON) & I2C_CON_SI)
            {
                //
                // re-Enable interrupt
                //
                xI2CSlaveIntEnable(ulBase, 0);
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
                    g_pfnI2CHandlerCallbacks[2](0, 0, xI2C_SLAVE_EVENT_STOP, 0);
                    break;
                }
            }
        }
    }
}

//*****************************************************************************
//
//! \brief I2C3 interrupt handler. Clear the I2C3 interrupt flag and execute the
//! callback function.
//!
//! \param none.
//!
//! This function is the I2C3 interrupt handler,it will Clear the I2C3
//! interrupt flag and execute the callback function if there be one.
//!
//! \note There are two source of this interrupt.One is I2C3 function
//! and one is I2C3 time out.
//!
//! \return None.
//
//*****************************************************************************
void
I2C3_IRQHandler(void)
{
    unsigned long ulBase = I2C3_BASE;
    unsigned long ulStatus = xHWREG(ulBase + I2C_STATUS);
    unsigned long ulTimeout;
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
        xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
    }

    if((ulStatus == I2C_I2STAT_S_RX_PRE_SLA_DAT_ACK) ||
       (ulStatus == I2C_I2STAT_S_RX_PRE_GENCALL_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[3](0, 0, xI2C_SLAVE_EVENT_RREQ, 0);
    }
    if((ulStatus == I2C_I2STAT_S_TX_SLAR_ACK) ||
       (ulStatus == I2C_I2STAT_S_TX_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[3](0, 0, xI2C_SLAVE_EVENT_TREQ, 0);
    }
    if((ulStatus == I2C_I2STAT_M_TX_SLAW_ACK) ||
       (ulStatus == I2C_I2STAT_M_TX_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[3](0, 0, xI2C_MASTER_EVENT_TX, 0);
    }
    if((ulStatus == I2C_I2STAT_M_RX_SLAR_ACK) ||
       (ulStatus == I2C_I2STAT_M_RX_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[3](0, 0, xI2C_MASTER_EVENT_RX, 0);
    }
    if((ulStatus == I2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX))
    {
        //
        //Temporally lock the interrupt for timeout condition
        //
        xI2CSlaveIntDisable(ulBase, 0);
        xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
        //
        // enable time out
        //
        ulTimeout = 0x10000;
        while(1)
        {
            if (xHWREG(ulBase + I2C_CON) & I2C_CON_SI)
            {
                //
                // re-Enable interrupt
                //
                xI2CSlaveIntEnable(ulBase, 0);
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
                    g_pfnI2CHandlerCallbacks[3](0, 0, xI2C_SLAVE_EVENT_STOP, 0);
                    break;
                }
            }
        }
    }
}

//*****************************************************************************
//
//! \brief I2C4 interrupt handler. Clear the I2C4 interrupt flag and execute the
//! callback function.
//!
//! \param none.
//!
//! This function is the I2C4 interrupt handler,it will Clear the I2C4
//! interrupt flag and execute the callback function if there be one.
//!
//! \note There are two source of this interrupt.One is I2C4 function
//! and one is I2C4 time out.
//!
//! \return None.
//
//*****************************************************************************
void
I2C4_IRQHandler(void)
{
    unsigned long ulBase = I2C4_BASE;
    unsigned long ulStatus = xHWREG(ulBase + I2C_STATUS);
    unsigned long ulTimeout;
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
        xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
    }

    if((ulStatus == I2C_I2STAT_S_RX_PRE_SLA_DAT_ACK) ||
       (ulStatus == I2C_I2STAT_S_RX_PRE_GENCALL_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[4](0, 0, xI2C_SLAVE_EVENT_RREQ, 0);
    }
    if((ulStatus == I2C_I2STAT_S_TX_SLAR_ACK) ||
       (ulStatus == I2C_I2STAT_S_TX_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[4](0, 0, xI2C_SLAVE_EVENT_TREQ, 0);
    }
    if((ulStatus == I2C_I2STAT_M_TX_SLAW_ACK) ||
       (ulStatus == I2C_I2STAT_M_TX_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[4](0, 0, xI2C_MASTER_EVENT_TX, 0);
    }
    if((ulStatus == I2C_I2STAT_M_RX_SLAR_ACK) ||
       (ulStatus == I2C_I2STAT_M_RX_DAT_ACK))
    {
        g_pfnI2CHandlerCallbacks[4](0, 0, xI2C_MASTER_EVENT_RX, 0);
    }
    if((ulStatus == I2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX))
    {
        //
        //Temporally lock the interrupt for timeout condition
        //
        xI2CSlaveIntDisable(ulBase, 0);
        xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
        //
        // enable time out
        //
        ulTimeout = 0x10000;
        while(1)
        {
            if (xHWREG(ulBase + I2C_CON) & I2C_CON_SI)
            {
                //
                // re-Enable interrupt
                //
                xI2CSlaveIntEnable(ulBase, 0);
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
                    g_pfnI2CHandlerCallbacks[4](0, 0, xI2C_SLAVE_EVENT_STOP, 0);
                    break;
                }
            }
        }
    }
}

//*****************************************************************************
//
//! \internal
//! \brief Get the I2C number. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get the I2C number .
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \note None
//!
//! \return value of I2C number,it can only be 0, 1, 2, 3 or 4.
//
//*****************************************************************************
static unsigned long I2CNumGet(unsigned long ulBase)
{
    unsigned char num = 0;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    switch(ulBase){
        case I2C0_BASE: num = 0; break;
        case I2C1_BASE: num = 1; break;
        case I2C2_BASE: num = 2; break;
        case I2C3_BASE: num = 3; break;
        case I2C4_BASE: num = 4; break;
        default: break;
    }
	return num;
}

//*****************************************************************************
//
//! \internal
//! \brief Generate a start condition on I2C bus. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to generate a start condition on 
//! specified I2C BUS.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    
    xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
	xHWREG(ulBase + I2C_CON) |= I2C_CON_STA;

    //
    // Wait for complete
    //
	while (!(xHWREG(ulBase + I2C_CON) & I2C_CON_SI));
	
	return (xHWREG(ulBase + I2C_STATUS) & I2C_STATUS_M);
}

//*****************************************************************************
//
//! \internal
//! \brief Generate a stop condition on I2C bus. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to generate a stop condition on 
//! specified I2C BUS.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    
    if (xHWREG(ulBase + I2C_CON) & I2C_CON_STA)
    {
        xHWREG(ulBase + I2C_CON) &= ~I2C_CON_STA;
    }
	xHWREG(ulBase + I2C_CON) |= I2C_CON_STO;
    xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
    
	xHWREG(ulBase + I2C_CON) &= ~I2C_CON_AA;
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
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    
    //
    // Make sure start bit is not active,but do not clear SI 
    //
    if (xHWREG(ulBase + I2C_CON) & I2C_CON_STA)
    {
        xHWREG(ulBase + I2C_CON) &= ~(I2C_CON_STA | I2C_CON_SI);
    }
            
    //
    // Send i2c address and RW bit 
    //
	xHWREG(ulBase + I2C_DAT) = ucData;
        
    //
    // Make sure AA and EI bit is not active,and clear SI 
    //
	xHWREG(ulBase + I2C_CON) &= ~(I2C_CON_AA | I2C_CON_EI);
        
    //
    // Wait the SI be set again by hardware
    //
	while (!(xHWREG(ulBase + I2C_CON) & I2C_CON_SI));
        
    //
    // Return the i2c status
    //
    return (xHWREG(ulBase + I2C_STATUS) & I2C_STATUS_M);
}

//*****************************************************************************
//
//! \internal
//! \brief Get a byte to I2C bus. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ucpData specifies the data point which will save the data get from 
//! I2C BUS.
//!
//! This function is to get a byte on specified I2C BUS.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \note This is only for master
//!
//! \return value of I2C status register after send a byte.
//
//*****************************************************************************
static unsigned long I2CByteGet (unsigned long ulBase, unsigned char *ucpData, 
                                 unsigned char ucAck)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    
    //
    // Make sure start bit is not active 
    //
    if (ucAck == 1)
    {
        xHWREG(ulBase + I2C_CON) |= I2C_CON_AA;
    }
    else
    {
        xHWREG(ulBase + I2C_CON) &= ~I2C_CON_AA;
    }
	xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
    
	while (!(xHWREG(ulBase + I2C_CON) & I2C_CON_SI));
    *ucpData = (unsigned char)xHWREG(ulBase + I2C_DAT);
    return (xHWREG(ulBase + I2C_STATUS) & I2C_STATUS_M);
}

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
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! The \e ulI2CClk is the I2C clock rate:
//!
//! \note This is only for master
//!
//! \return None.
//
//*****************************************************************************
void 
xI2CMasterInit(unsigned long ulBase, unsigned long ulI2CClk)
{
    unsigned long ulHclk;
    unsigned long ulDiv;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    
    switch(ulBase)
    {
        case I2C0_BASE: xSysCtlPeripheralReset(xSYSCTL_PERIPH_I2C0); break;
        case I2C1_BASE: xSysCtlPeripheralReset(xSYSCTL_PERIPH_I2C1); break;
        case I2C2_BASE: xSysCtlPeripheralReset(xSYSCTL_PERIPH_I2C2); break;
        case I2C3_BASE: xSysCtlPeripheralReset(xSYSCTL_PERIPH_I2C3); break;
        case I2C4_BASE: xSysCtlPeripheralReset(xSYSCTL_PERIPH_I2C4); break;
		default:  break;
    }
    
    ulHclk = xSysCtlClockGet();
    
    ulDiv = (unsigned long) (((ulHclk * 10)/(ulI2CClk * 4) + 5) / 10 - 1);
    xHWREG(ulBase + I2C_CLKDIV) = ulDiv;

    xHWREG(ulBase + I2C_CON) = 0;
    xHWREG(ulBase + I2C_CON) = I2C_CON_ENS1;
}

//*****************************************************************************
//
//! \brief  Indicates whether or not the I2C bus is busy.
//!         This function returns an indication of whether or not the I2C bus
//!         is busy. This function can be used in a multi-master environment to
//!         determine if another master is currently using the bus.
//!
//! \param  [in] ulBase is the I2C module base address.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \return The I2C bus status:
//!         - xtrue    if I2C bus is busy.
//!         - xfalse   if I2C bus is free.
//
//*****************************************************************************
xtBoolean xI2CMasterBusBusy(unsigned long ulBase)
{
    return ((xHWREG(I2C_STATUS)&0xF8) == 0xF8)? xfalse : xtrue;
}

//*****************************************************************************
//
//! \brief  Indicates whether or not the I2C Master is busy.
//!         This function returns an indication of whether or not the I2C Master
//!         is busy transmitting or receiving data.
//!
//! \param  [in] ulBase is the I2C module base address.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \return The I2C bus status:
//!         - xtrue    if I2C bus is busy.
//!         - xfalse   if I2C bus is free.
//
//*****************************************************************************
xtBoolean xI2CMasterBusy(unsigned long ulBase)
{
    return xfalse;
}

//*****************************************************************************
//
//! \brief  Gets the error status of the I2C Master module.
//!         This function is used to obtain the error status of the Master module
//!         send and receive operations.
//!
//! \param  [in] ulBase is the I2C module base address.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \return Returns the error status, can be one of the following value:
//!         - \ref I2C_MASTER_ERR_NONE
//!         - \ref I2C_MASTER_ERR_ADDR_ACK
//!         - \ref I2C_MASTER_ERR_DATA_ACK
//!         - \ref I2C_MASTER_ERR_ARB_LOST
//
//*****************************************************************************
unsigned long xI2CMasterError(unsigned long ulBase)
{
    unsigned long ulStatus;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    ulStatus = (xHWREG(ulBase + I2C_STATUS) & I2C_STATUS_M);

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
    xHWREG(ulBase + I2C_DAT) = ucData;

    //
    // Make sure AA bit is active,and clear EI
    //
    xHWREG(ulBase + I2C_CON) |= I2C_CON_AA;
    xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
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
    unsigned long ulData = xHWREG(ulBase + I2C_DAT);
    xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
    return ulData;
}

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
void xI2CMasterStop(unsigned long ulBase)
{

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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
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
    xHWREG(ulBase + I2C_DAT) = ucData;

    //
    // Make sure AA and EI bit is not active,and clear EI
    //
    //xHWREG(ulBase + I2C_CON) &= ~(I2C_CON_AA | I2C_CON_EI);
    xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;

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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    //
    // Send data to I2C BUS
    //
    xHWREG(ulBase + I2C_DAT) = ucData;

    //
    // Make sure AA and EI bit is not active,and clear EI
    //
    xHWREG(ulBase + I2C_CON) &= ~(I2C_CON_AA | I2C_CON_EI);

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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    xASSERT(!(ucSlaveAddr & 0x80));

    //
    // Send write request
    //
    xI2CMasterWriteRequestS1(ulBase, ucSlaveAddr, ucData, xfalse);

    //
    // Wait the SI be set again by hardware
    //
    while (!(xHWREG(ulBase + I2C_CON) & I2C_CON_SI));
    ulStatus = xHWREG(ulBase + I2C_STATUS) & I2C_STATUS_M;
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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    //
    // Send write request
    //
    xI2CMasterWriteRequestS2(ulBase, ucData, xfalse);

    //
    // Wait the SI be set again by hardware
    //
    while (!(xHWREG(ulBase + I2C_CON) & I2C_CON_SI));
    ulStatus = xHWREG(ulBase + I2C_STATUS) & I2C_STATUS_M;
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
                     unsigned char *pucDataBuf, unsigned long ulLen,
                     xtBoolean bEndTransmition)
{

    unsigned long ulStatus;
    unsigned long ulWritten;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
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
xI2CMasterWriteBufS2(unsigned long ulBase, unsigned char *pucDataBuf,
                     unsigned long ulLen, xtBoolean bEndTransmition)
{
    unsigned long i;
    unsigned long ulStatus;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    xHWREG(ulBase + I2C_CON) |= I2C_CON_AA;
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
        xHWREG(ulBase + I2C_CON) &= ~I2C_CON_AA;
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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    //
    // Send the stop if End Transmition.
    //
    if(bEndTransmition)
    {
        xHWREG(ulBase + I2C_CON) &= ~I2C_CON_AA;
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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    //
    // RECEIVE operation with negative ACK(no stop)
    //
    xHWREG(ulBase + I2C_CON) &= ~I2C_CON_AA;
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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    xASSERT(pucData);

    xI2CMasterReadRequestS1(ulBase, ucSlaveAddr, xfalse);

    xHWREG(ulBase + I2C_CON) |= I2C_CON_AA;
    xSysCtlDelay(100);
    xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;

    while (!(xHWREG(ulBase + I2C_CON) & I2C_CON_SI));

    *pucData = xHWREG(ulBase + I2C_DAT);

    ulStatus = (xHWREG(ulBase + I2C_STATUS) & I2C_STATUS_M);

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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    xI2CMasterReadRequestS2(ulBase, xfalse);

    if(bEndTransmition)
    {
        xHWREG(ulBase + I2C_CON) &= ~I2C_CON_AA;
    }

    xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;

    //
    // Waiting the I2C controller to be transmited
    //
    while (!(xHWREG(ulBase + I2C_CON) & I2C_CON_SI));
    *pucData = (unsigned char)xHWREG(ulBase + I2C_DAT);

    //
    // Get the Status code
    //
    ulStatus =  (xHWREG(ulBase + I2C_STATUS) & I2C_STATUS_M);

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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    xASSERT(pucDataBuf);

    if(ulLen == 0)
        return 0;

    else if(ulLen == 1)
    {
        ulStatus = xI2CMasterReadS1(ulBase, ucSlaveAddr,
                                   pucDataBuf, bEndTransmition);

        if (ulStatus == xI2C_MASTER_ERR_NONE)
        {
            pucDataBuf[0] = xHWREG(ulBase + I2C_DAT);

            return 1;
        }
        else
        {
            return 0;
        }
    }

    xHWREG(ulBase + I2C_CON) |= I2C_CON_AA;

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
    if (xHWREG(ulBase + I2C_CON) & I2C_CON_STA)
    {
        xHWREG(ulBase + I2C_CON) &= ~(I2C_CON_STA | I2C_CON_SI);
    }

    //
    // Send data to I2C BUS
    //
    xHWREG(ulBase + I2C_DAT) = (ucSlaveAddr << 1) | 1;

    //
    // Make sure AA and EI bit is not active,and clear SI
    //
    xHWREG(ulBase + I2C_CON) &= ~(I2C_CON_EI);

    //
    // Wait the SI be set again by hardware
    //
    while (!(xHWREG(ulBase + I2C_CON) & I2C_CON_SI));

    //
    // Return the i2c status
    //
    ulStatus = (xHWREG(ulBase + I2C_STATUS) & I2C_STATUS_M);
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
        xHWREG(ulBase + I2C_CON) |= I2C_CON_AA;
    }
    xSysCtlDelay(100);
    xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;

    while (!(xHWREG(ulBase + I2C_CON) & I2C_CON_SI));

    pucDataBuf[0] = xHWREG(ulBase + I2C_DAT);

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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    xASSERT(pucDataBuf);

    if(ulLen == 0)
        return 0;

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
        xHWREG(ulBase + I2C_CON) &= ~(I2C_CON_AA|I2C_CON_SI);
    }

    xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;

    while (!(xHWREG(ulBase + I2C_CON) & I2C_CON_SI));

    *pucDataBuf = xHWREG(ulBase + I2C_DAT);

    if(bEndTransmition)
    {
        I2CStopSend(ulBase);
    }

    return ulLen;
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
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
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
xI2CSlaveInit(unsigned long ulBase, unsigned char ucSlaveAddr,
             unsigned long ulGeneralCall)
{    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    switch(ulBase)
    {
        case I2C0_BASE: xSysCtlPeripheralReset(xSYSCTL_PERIPH_I2C0); break;
        case I2C1_BASE: xSysCtlPeripheralReset(xSYSCTL_PERIPH_I2C1); break;
        case I2C2_BASE: xSysCtlPeripheralReset(xSYSCTL_PERIPH_I2C2); break;
        case I2C3_BASE: xSysCtlPeripheralReset(xSYSCTL_PERIPH_I2C3); break;
        case I2C4_BASE: xSysCtlPeripheralReset(xSYSCTL_PERIPH_I2C4); break;
		default:  break;
    }
    
    xHWREG(ulBase + I2C_CON) = I2C_CON_ENS1;

    xHWREG(ulBase + I2C_CON) = 0;

    xHWREG(ulBase + I2C_ADDR0) = (ucSlaveAddr << 1) | ulGeneralCall;
        
    xHWREG(ulBase + I2C_CON) = I2C_CON_ENS1;
    xHWREG(ulBase + I2C_CON) |= I2C_CON_AA;
}

//*****************************************************************************
//
//! \brief Slave Send a byte to I2C bus.
//!        This function is to send a byte on specified I2C BUS.
//!
//! \param  [in] ulBase is the I2C module base address.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \param  [in] ucData specifies the data which will send to I2C BUS.
//!
//! \return None.
//!
//! \note   This is only for slave
//
//*****************************************************************************
void xI2CSlaveDataPut(unsigned long ulBase, unsigned char ucData)
{
	xI2CMasterDataPut(ulBase, ucData);
}

//*****************************************************************************
//! \brief Slave receive a byte to I2C bus.
//!        This function is to receive a byte on specified I2C BUS.
//!
//! \param  [in] ulBase is the I2C module base address.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \return None.
//!
//! \note   This is only for slave
//
//*****************************************************************************
unsigned long xI2CSlaveDataGet(unsigned long ulBase)
{
    return xI2CMasterDataGet(ulBase);
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
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

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
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

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
//! There are 26 status codes. Please refer to Xi2c.h NUC4xx_I2C_STATUS_Type
//! in detail.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \note None
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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    return (xHWREG(ulBase + I2C_STATUS) & I2C_STATUS_M);
}

//*****************************************************************************
//
//! \brief Enable I2C interrupt  of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to enable I2C interrupt  of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************    
void 
xI2CMasterIntEnable(unsigned long ulBase, unsigned long ulIntType)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    
    xHWREG(ulBase + I2C_CON) |= I2C_CON_EI;
    if (ulBase == I2C0_BASE)
    {
        xIntEnable(INT_I2C0);
    }
    else if (ulBase == I2C1_BASE)
    {
        xIntEnable(INT_I2C1);
    }
}

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
void
xI2CSlaveIntEnable(unsigned long ulBase, unsigned long ulIntType)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    xHWREG(ulBase + I2C_CON) |= I2C_CON_EI;
}

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
void 
xI2CIntCallbackInit(unsigned long ulBase, xtEventCallback xtI2CCallback)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    g_pfnI2CHandlerCallbacks[I2CNumGet(ulBase)] = xtI2CCallback;
}

//*****************************************************************************
//
//! \brief Disable I2C interrupt  of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to disable I2C interrupt  of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
xI2CMasterIntDisable(unsigned long ulBase, unsigned long ulIntType)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    
    xHWREG(ulBase + I2C_CON) &= ~I2C_CON_EI;
}

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
void
xI2CSlaveIntDisable(unsigned long ulBase, unsigned long ulIntType)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    xHWREG(ulBase + I2C_CON) &= ~I2C_CON_EI;
}

//*****************************************************************************
//
//! \brief Get the I2C interrupt flag of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get the I2C interrupt flag of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \note None
//!
//! \return a xtBoolean value xtrue or xfalse.
//
//*****************************************************************************
unsigned long
xI2CMasterIntFlagGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    
    return ((xHWREG(ulBase + I2C_CON) & I2C_CON_SI) ? xtrue : xfalse);
}

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
unsigned char xI2CSlaveIntFlagGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    return ((xHWREG(ulBase + I2C_CON) & I2C_CON_SI) ? xtrue : xfalse);
}
//*****************************************************************************
//
//! \brief Enable I2C master module of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to enable I2C module of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
xI2CMasterEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    
    xHWREG(ulBase + I2C_CON) |= I2C_CON_ENS1;
}

//*****************************************************************************
//
//! \brief Enables the I2C Slave block.
//!        This will enable operation of the I2C Slave block.
//!
//! \param  [in] ulBase is the I2C module base address.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \return None.
//
//*****************************************************************************
void xI2CSlaveEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    xHWREG(ulBase + I2C_CON) |= I2C_CON_ENS1;
}
//*****************************************************************************
//
//! \brief Disable I2C master module of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to disable I2C module of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void
xI2CMasterDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    
    xHWREG(ulBase + I2C_CON) &= ~I2C_CON_ENS1;
}

//*****************************************************************************
//
//! \brief Disables the I2C slave block.
//!        This will disable operation of the I2C slave block.
//!
//! \param  [in] ulBase is the I2C module base address.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \return None.
//
//*****************************************************************************
void xI2CSlaveDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    xHWREG(ulBase + I2C_CON) &= ~I2C_CON_ENS1;
}
//*****************************************************************************
//
//! \brief Get the I2C time out flag of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get the I2C time out flag of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \note None
//!
//! \return a xtBoolean value xtrue or xfalse.
//
//*****************************************************************************
xtBoolean 
I2CTimeoutFlagGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));
    
    return ((xHWREG(ulBase + I2C_TOCTL) & I2C_TOCTL_TIF) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Clear the I2C interrupt flag of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to clear the I2C interrupt flag of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \note None
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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    xHWREG(ulBase + I2C_CON) |= I2C_CON_SI;
}

//*****************************************************************************
//
//! \brief Clear the I2C time out flag of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to clear the I2C time out flag of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \note None
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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    xHWREG(ulBase + I2C_TOCTL) |= I2C_TOCTL_TIF;
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
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! The \e ulEnable can be one of the following values:
//! \b I2C_TIMEOUT_EN, \b I2C_TIMEOUT_DIS.
//!
//! The \e ulDiv4 can be one of the following values:
//! \b I2C_TIMEOUT_DIV4, \b I2C_TIMEOUT_DIV_NO.
//!
//! \note None
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
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    //
    // Check the arguments.
    //
    xASSERT((ulEnable == I2C_TIMEOUT_EN) || (ulEnable == I2C_TIMEOUT_DIS));

    //
    // Check the arguments.
    //
    xASSERT((ulDiv4 == I2C_TIMEOUT_DIV4) || (ulDiv4 == I2C_TIMEOUT_DIV_NO));

    xHWREG(ulBase + I2C_TOCTL) &= ~0x00000006;
    xHWREG(ulBase + I2C_TOCTL) |= ulEnable | ulDiv4;
}

//*****************************************************************************
//
//! \brief Enable or Disable the I2C wake-up function of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//! \param bEnable specifies the Enable/Disable Wake-up function.
//!
//! This function is to enable or disable the I2C wake-up function of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void
I2CWakeupEnable(unsigned long ulBase, xtBoolean bEnable)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || (ulBase == I2C1_BASE) ||
            (ulBase == I2C2_BASE) || (ulBase == I2C3_BASE) ||
            (ulBase == I2C4_BASE));

    if(bEnable){
    	xHWREG(ulBase + I2C_WKCON) |= I2C_WKCON_I2CWKEN;
    } else {
    	xHWREG(ulBase + I2C_WKCON) &= ~I2C_WKCON_I2CWKEN;
	}
}

//*****************************************************************************
//
//! \brief Get the I2C wake-up flag of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get the I2C wake-up flag of the specified I2C port.
//!
//! The \e ulBase can be one of the following values:
//! \b I2C0_BASE, \b I2C1_BASE, \b I2C2_BASE, \b I2C3_BASE, \b I2C4_BASE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
xtBoolean I2CWakeupStatusGet(unsigned long ulBase)
{
     return xHWREG(ulBase + I2C_WKSTS_I2CWKF) ? 1 : 0;
}
