//*****************************************************************************
//
//! \file xi2c.c
//! \brief Driver for the I2C
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
//static tI2CConfig g_tI2CSetup[2];
//static unsigned long g_ulI2CMasterComplete[2];
//static unsigned long g_ulI2CSlaveComplete[2];


//*****************************************************************************
//
// An array is I2C callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnI2CHandlerCallbacks[1]={0};
static xtBoolean xtStartFlag;

//*****************************************************************************
//
//! \internal
//! \brief Get the I2C number. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get the I2C number.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE
//!
//! \return value of I2C number,it can only be 0.
//
//*****************************************************************************
unsigned long I2CNumGet (unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
	
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
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE
//!
//! \note This is only for master
//!
//! \return value of I2C status register after generate a start condition.
//
//*****************************************************************************
static void I2CStartSend (unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
    xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_MST;
    SysCtlDelay(1000);

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
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE
//!
//! \note This is only for master
//!
//! \return None.
//
//*****************************************************************************
void 
I2CStopSend (unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    xHWREGB(ulBase + I2C_CON1) &= ~I2C_CON1_MST;
    xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
    
	xHWREGB(ulBase + I2C_CON1) &= ~I2C_CON1_TXAK;

    xtStartFlag = xfalse;
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
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE
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
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));

    xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_TX;
            
    //
    // Send data to I2C BUS
    //
    xHWREGB(ulBase + I2C_DAT) = ucData;
        
    //
    // Make sure AA and EI bit is not active,and clear SI 
    //
    xHWREGB(ulBase + I2C_CON1) &= ~(I2C_CON1_TXAK | I2C_CON1_IE);
        
    //
    // Wait the SI be set again by hardware
    //
    while (!(xHWREGB(ulBase + I2C_STATUS) & I2C_STATUS_IF));
        
    //
    // Return the i2c status
    //
    return (xHWREGB(ulBase + I2C_STATUS));
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
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
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
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    //
    // Make sure start bit is not active 
    //
    if (ucAck == 1)
    {
        xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_TXAK;
    }
    else
    {
        xHWREGB(ulBase + I2C_CON1) &= ~I2C_CON1_TXAK;
    }
    xHWREGB(ulBase + I2C_CON1) &= ~I2C_CON1_TX;
    xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
    
    while (!(xHWREGB(ulBase + I2C_STATUS) & I2C_STATUS_IF));
    *ucpData = (unsigned char)xHWREGB(ulBase + I2C_DAT);
    return (xHWREGB(ulBase + I2C_STATUS));
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
    unsigned long ulStatus;

    ulStatus = xHWREGB(ulBase + I2C_STATUS);

    if(xHWREGB(ulBase + I2C_CON1) & I2C_CON1_MST)
    {
        if((ulStatus == I2C_MASTER_EVENT_TX))
        {
            g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_MASTER_EVENT_TX, 0);
        }
        else if((ulStatus == I2C_MASTER_EVENT_RX))
        {
            g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_MASTER_EVENT_RX, 0);
        }
        else
        {
            xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
        }
        
    }
    else
    {
        if((ulStatus == I2C_SLAVE_EVENT_TREQ))
        {
            g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_SLAVE_EVENT_TREQ, 0);
        }
        else if((ulStatus == I2C_SLAVE_EVENT_RREQ))
        {
            g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_SLAVE_EVENT_RREQ, 0);
        }
        else if(ulStatus & I2C_STATUS_IAAS)
        {
            xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
            xHWREGB(ulBase + I2C_CON1) |= 0;
        }
        else if(xHWREGB(ulBase + I2C_STATUS) == I2C_SLAVE_EVENT_STOP)
        {
            xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
            xHWREGB(ulBase + I2C_CON1) |= 0;
        }
        else 
        {
            xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
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
//! This function is the I2C1 interrupt handler,it will Clear the I2C1 interrupt
//! flag and execute the callback function if there be one.
//!
//! \note There are two source of this interrupt.One is I2C1 function and one is
//! I2C1 time out.
//!
//! \return None.
//
//*****************************************************************************
void 
I2C1IntHandler(void)
{
    unsigned long ulBase = I2C1_BASE;
    unsigned long ulStatus;

    ulStatus = xHWREGB(ulBase + I2C_STATUS);

    if(xHWREGB(ulBase + I2C_CON1) & I2C_CON1_MST)
    {
        if((ulStatus == I2C_MASTER_EVENT_TX))
        {
            g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_MASTER_EVENT_TX, 0);
        }
        else if((ulStatus == I2C_MASTER_EVENT_RX))
        {
            g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_MASTER_EVENT_RX, 0);
        }
        else
        {
            xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
        }
        
    }
    else
    {
        if((ulStatus == I2C_SLAVE_EVENT_TREQ))
        {
            g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_SLAVE_EVENT_TREQ, 0);
        }
        else if((ulStatus == I2C_SLAVE_EVENT_RREQ))
        {
            g_pfnI2CHandlerCallbacks[0](0, 0, xI2C_SLAVE_EVENT_RREQ, 0);
        }
        else if(ulStatus & I2C_STATUS_IAAS)
        {
            xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
            xHWREGB(ulBase + I2C_CON1) |= 0;
        }
        else if(xHWREGB(ulBase + I2C_STATUS) == I2C_SLAVE_EVENT_STOP)
        {
            xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
            xHWREGB(ulBase + I2C_CON1) |= 0;
        }
        else 
        {
            xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
        }
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
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
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
    unsigned long ulBusClk;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    
    xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_EN;
    
    ulBusClk = SysCtlBusClkGet();
    
    xHWREGB(ulBase + I2C_FREQ) = 0x80;

    xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_TX;
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
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
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
I2CSlaveInit(unsigned long ulBase, unsigned short usSlaveAddr, 
             unsigned long ulGeneralCall, unsigned long ulAddrBit)
{    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));    

    xHWREGB(ulBase + I2C_CON2) &= ~(I2C_CON2_GCAEN | I2C_CON2_ADEXT);
    xHWREGB(ulBase + I2C_CON2) = ulGeneralCall | ulAddrBit;
    
    if(ulAddrBit == I2C_ADDRESS_7BIT)
    {
        xHWREGB(ulBase + I2C_A1) = (usSlaveAddr << 1);
    }
    else
    {
        xHWREGB(ulBase + I2C_A1) = (usSlaveAddr & 0xFF) << 1;
        xHWREGB(ulBase + I2C_CON2) = (usSlaveAddr & 0x700) >> 8;
    }
        
    xHWREGB(ulBase + I2C_CON1) &= ~I2C_CON1_MST;
}

//*****************************************************************************
//
//! \brief Set the second slave address of the specified I2C port.
//!
//! \param ulBase specifies the I2C module base address.
//! \param ucSlaveAddr specifies the slave address.
//!
//! This function is to Set 4 7-bit slave addresses and enable General Call 
//! function of specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//!
//! The \e ucSlaveAddr is the I2C slave address,There are 4 slave addrss.
//! The ucSlaveAddr can be a 7-bit value.
//!
//! \note this is only for slave
//!
//! \return None.
//
//*****************************************************************************
void 
I2CSlaveSecondAddressSet(unsigned long ulBase, unsigned char ucSlaveAddr)
{   
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));   
        
    xHWREGB(ulBase + I2C_SMB) |= (I2C_SMB_SIICAEN);
    xHWREGB(ulBase + I2C_A2) = ((ucSlaveAddr << 1));
}

//*****************************************************************************
//
//! \brief Disable I2C second slave address of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to disable I2C second slave address of the 
//! specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CSecondAddressDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    xHWREGB(ulBase + I2C_SMB) &= ~(I2C_SMB_SIICAEN);
}

//*****************************************************************************
//
//! \brief Get I2C status of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get I2C status of the specified I2C port.
//! There are 26 status codes. Please refer to xi2c.h M051_I2C_STATUS_Type
//! in detail.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
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
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));

    return (xHWREGB(ulBase + I2C_STATUS));
}

//*****************************************************************************
//
//! \brief Enable I2C interrupt of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulIntType specifies the I2C interrupt type.
//!
//! This function is to enable I2C interrupt of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//!
//! \return None.
//
//*****************************************************************************    
void 
I2CIntEnable(unsigned long ulBase, unsigned long ulIntType)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    xASSERT(((ulIntType & I2C_INT_FUNCTION) == I2C_INT_FUNCTION) || 
            ((ulIntType & I2C_INT_BUS_STOP) == I2C_INT_BUS_STOP) ||
            ((ulIntType & I2C_INT_TIMEOUT) == I2C_INT_TIMEOUT));
    
    if(ulIntType & I2C_INT_FUNCTION)
    {
        xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_IE;
    }
    if(ulIntType & I2C_INT_BUS_STOP)
    {
        xHWREGB(ulBase + I2C_FLT) |= I2C_FLT_STOPIE;
    }
    if(ulIntType & I2C_INT_TIMEOUT)
    {
        xHWREGB(ulBase + I2C_SMB) |= I2C_SMB_SHTF2IE;
    }
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
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    g_pfnI2CHandlerCallbacks[0] = xtI2CCallback;

}

//*****************************************************************************
//
//! \brief Disable I2C interrupt of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulIntType specifies the I2C interrupt type.
//!
//! This function is to disable I2C interrupt of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CIntDisable(unsigned long ulBase, unsigned long ulIntType)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    if(ulIntType & I2C_INT_FUNCTION)
    {
        xHWREGB(ulBase + I2C_CON1) &= ~I2C_CON1_IE;
    }
    if(ulIntType & I2C_INT_BUS_STOP)
    {
        xHWREGB(ulBase + I2C_FLT) &= ~I2C_FLT_STOPIE;
    }
    if(ulIntType & I2C_INT_TIMEOUT)
    {
        xHWREGB(ulBase + I2C_SMB) &= ~I2C_SMB_SHTF2IE;
    }
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
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
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
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_EN;
}

//*****************************************************************************
//
//! \brief Disable I2C module of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to disable I2C module of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
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
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    xHWREGB(ulBase + I2C_CON1) &= ~I2C_CON1_EN;
}

//*****************************************************************************
//
//! \brief Enable I2C high driver of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to enable I2C high driver of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CHighDriverEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    xHWREGB(ulBase + I2C_CON2) |= I2C_CON2_HDRS;
}

//*****************************************************************************
//
//! \brief Disable I2C high driver of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to disable I2C high driver of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CHighDriverDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    xHWREGB(ulBase + I2C_CON2) &= ~I2C_CON2_HDRS;
}

//*****************************************************************************
//
//! \brief Enable I2C slave independent baud rate  of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to enable I2C slave independent baud rate  of the 
//! specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CSlaveBaudEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    xHWREGB(ulBase + I2C_CON2) |= I2C_CON2_SBRC;
}

//*****************************************************************************
//
//! \brief Disable I2C slave independent baud rate  of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to disable I2C slave independent baud rate  of the 
//! specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CSlaveBaudDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    xHWREGB(ulBase + I2C_CON2) &= ~I2C_CON2_SBRC;
}

//*****************************************************************************
//
//! \brief Enable I2C wake up of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to enable I2C wake up of the 
//! specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CWakeupEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_WUEN;
}

//*****************************************************************************
//
//! \brief Disable I2C wake up of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to disable I2C wake up of the 
//! specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CWakeupDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    xHWREGB(ulBase + I2C_CON1) &= ~I2C_CON1_WUEN;
}

//*****************************************************************************
//
//! \brief Enable I2C DMA of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to enable I2C DMA of the 
//! specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CDMAEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_DMAEN;
}

//*****************************************************************************
//
//! \brief Disable I2C DMA of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to disable I2C DMA of the 
//! specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CDMADisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    xHWREGB(ulBase + I2C_CON1) &= ~I2C_CON1_DMAEN;
}

//*****************************************************************************
//
//! \brief Enable I2C Range Address Matching of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulRangeAddress specifies the I2C module Range Address.
//!
//! This function is to enable I2C Range Address Matching of the 
//! specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CRangeAddrEnable(unsigned long ulBase, unsigned long ulRangeAddress)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    xHWREGB(ulBase + I2C_CON2) |= I2C_CON2_RMEN;
	xHWREGB(ulBase + I2C_RA) = ulRangeAddress << 1;
}

//*****************************************************************************
//
//! \brief Disable I2C Range Address Matching of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to disable I2C Range Address Matching of the 
//! specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CRangeAddrDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    xHWREGB(ulBase + I2C_CON2) &= ~I2C_CON2_RMEN;
}

//*****************************************************************************
//
//! \brief Set I2C Programmable Filter Factor of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ucFilter Filter glitches up to width of n bus clock cycles.
//!
//! This function is to Set I2C Programmable Filter Factor of the 
//! specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//! The \e ucFilter can be: 0-31.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CGlitchFilterSet(unsigned long ulBase, unsigned char ucFilter)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    xASSERT((ulBase >= 0) && ((ulBase <= 31)));
    
    xHWREGB(ulBase + I2C_FLT) &= ~I2C_FLT_FLT_M;
    xHWREGB(ulBase + I2C_FLT) |= ucFilter;
}

//*****************************************************************************
//
//! \brief Get the I2C interrupt flag of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to get the I2C interrupt flag of the specified I2C port.
//!
//! The \e ulBase must be: \b I2C0_BASE, \b I2C1_BASE.
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
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    return ((xHWREGB(ulBase + I2C_STATUS) & I2C_STATUS_IF) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Get the I2C time out flag of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulTimeout specifies whitch timeout flag to get.
//!
//! This function is to get the I2C time out flag of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//! The \e ulTimeout must be:\b I2C_TIMEOUT_SCL_LOW,  \b I2C_TIMEOUT_SCL_HIGH1
//! \b I2C_TIMEOUT_SCL_HIGH2.
//!
//! \return could be:\b xtrue the Time out has been occur.
//! \b xfalse the Time out has not been occur.
//*****************************************************************************
xtBoolean 
I2CTimeoutFlagGet(unsigned long ulBase, unsigned long ulTimeout)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    xASSERT((ulBase == I2C_TIMEOUT_SCL_LOW) || 
            (ulBase == I2C_TIMEOUT_SCL_HIGH2) ||
            (ulBase == I2C_TIMEOUT_SCL_HIGH1));
    
    return ((xHWREGB(ulBase + I2C_SMB) & ulTimeout) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Clear the I2C interrupt flag of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//!
//! This function is to clear the I2C interrupt flag of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
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
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));

    xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
}

//*****************************************************************************
//
//! \brief Clear the I2C time out flag of the specified I2C port. 
//!
//! \param ulBase specifies the I2C module base address.
//! \param ulTimeout specifies whitch timeout flag to clear.
//!
//! This function is to clear the I2C time out flag of the specified I2C port.
//!
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//! The \e ulTimeout must be:\b I2C_TIMEOUT_SCL_LOW,  \b I2C_TIMEOUT_SCL_HIGH2.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CTimeoutFlagClear(unsigned long ulBase, unsigned long ulTimeout)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    xASSERT((ulTimeout == I2C_TIMEOUT_SCL_LOW) || 
            ((ulTimeout == I2C_TIMEOUT_SCL_HIGH2)));

    xHWREGB(ulBase + I2C_SMB) |= ulTimeout;
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
//! The \e ulBase must be:\b I2C0_BASE, \b I2C1_BASE.
//!
//! The \e ulEnable can be one of the following values:
//! \b I2C_TIMEOUT_EN, \b I2C_TIMEOUT_DIS.
//!
//! The \e ulDiv4 can be one of the following values:
//! \b I2C_TIMEOUT_DIV64, \b I2C_TIMEOUT_DIV_NO.
//!
//! \return None.
//
//*****************************************************************************
void 
I2CTimeoutCounterSet(unsigned long ulBase, unsigned long ulDiv64,
                     unsigned long ulTimeout)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));

    //
    // Check the arguments.
    //
    xASSERT((ulDiv64 == I2C_TIMEOUT_DIV64) || 
            (ulDiv64 == I2C_TIMEOUT_DIV_NO));

    xHWREGB(ulBase + I2C_SMB) &= ~I2C_TIMEOUT_DIV64;
    xHWREGB(ulBase + I2C_SMB) |= ulDiv64;
    xHWREGB(ulBase + I2C_SLTH) = (ulTimeout & 0xFF00) >> 8;
    xHWREGB(ulBase + I2C_SLTL) = (ulTimeout & 0x00FF);
}

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
xtBoolean 
I2CMasterBusBusy(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));

    return (xHWREGB(ulBase + I2C_STATUS) & I2C_STATUS_BUSY) ? xtrue : xfalse;
}

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
xtBoolean
I2CMasterBusy(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));

    return (xHWREGB(ulBase + I2C_STATUS) & I2C_STATUS_TCF) ? xtrue : xfalse;
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
void I2CMasterDataPut(unsigned long ulBase, unsigned char ucData)
{
    //
    // Send data to I2C BUS
    //
    xHWREGB(ulBase + I2C_DAT) = ucData;
        
    //
    // Make sure AA bit is active,and clear EI 
    //
    xHWREGB(ulBase + I2C_CON1) &= ~I2C_CON1_TXAK;
    xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
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
unsigned long I2CMasterDataGet(unsigned long ulBase)
{
    unsigned long ulData;
    ulData = xHWREGB(ulBase + I2C_DAT);
    xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
    return ulData;
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
I2CMasterWriteRequestS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                         unsigned char ucData, xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    xASSERT(!(ucSlaveAddr & 0x80));

    if(xtStartFlag == xfalse)
    {
        //
        // Send start
        //    
        I2CStartSend(ulBase);
        xtStartFlag = xtrue;
    }
    else
    {
        //
        // Send Repeat start
        //   
        xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
        xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_RSTA;
    }
    
    if(!(xHWREGB(ulBase + I2C_STATUS) & I2C_STATUS_BUSY))
    {
        I2CStopSend(ulBase);
        return;
    }
        
    //
    // Send address
    //
    ulStatus = I2CByteSend(ulBase, (ucSlaveAddr << 1)); 
    if(!(ulStatus == I2C_MASTER_EVENT_TX))
    {
        I2CStopSend(ulBase);
        return;
    }
    xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;  
    //
    // Send data to I2C BUS
    //
    xHWREGB(ulBase + I2C_DAT) = ucData;
        
    //
    // Make sure AA and EI bit is not active,and clear EI 
    //
    //xHWREGB(ulBase + I2C_O_CON) &= ~(I2C_CON_AA | I2C_CON_EI);
    
    
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
I2CMasterWriteRequestS2(unsigned long ulBase, unsigned char ucData,
                         xtBoolean bEndTransmition)
{    
    //
    // Check the arguments.
    //    
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    //
    // Send data to I2C BUS
    //
    xHWREGB(ulBase + I2C_DAT) = ucData;
        
    //
    // Make sure AA and EI bit is not active,and clear EI 
    //
    xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
    
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
I2CMasterWriteS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                  unsigned char ucData, xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //    
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    xASSERT(!(ucSlaveAddr & 0x80));
    
    //
    // Send write request
    //
    xI2CMasterWriteRequestS1(ulBase, ucSlaveAddr, ucData, xfalse);
    
    //
    // Wait the SI be set again by hardware
    //
    while (!(xHWREGB(ulBase + I2C_STATUS) & I2C_STATUS_IF));
    ulStatus = xHWREGB(ulBase + I2C_STATUS);
    if(!(ulStatus == I2C_MASTER_EVENT_TX))
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
I2CMasterWriteS2(unsigned long ulBase, unsigned char ucData,
                  xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //    
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    //
    // Send write request
    //
    xI2CMasterWriteRequestS2(ulBase, ucData, xfalse);
    
    //
    // Wait the SI be set again by hardware
    //
    while (!(xHWREGB(ulBase + I2C_STATUS) & I2C_STATUS_IF));
    ulStatus = xHWREGB(ulBase + I2C_STATUS);
    if(!(ulStatus == I2C_MASTER_EVENT_TX))
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
I2CMasterWriteBufS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                     const unsigned char *pucDataBuf, unsigned long ulLen, 
                     xtBoolean bEndTransmition)
{
    
    unsigned long ulStatus;
    unsigned long ulWritten;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    xASSERT(pucDataBuf);
    
    if(ulLen == 1)
    {
        ulStatus = xI2CMasterWriteS1(ulBase, ucSlaveAddr, 
                                    pucDataBuf[0], bEndTransmition);
        
        return (ulStatus == xI2C_MASTER_ERR_NONE) ? 1 : 0;
    }

    if(xtStartFlag == xfalse)
    {
        //
        // Send start
        //    
        I2CStartSend(ulBase);
        xtStartFlag = xtrue;
    }
    else
    {
        //
        // Send Repeat start
        //   
        xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
        xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_RSTA;
    }
    if(!(xHWREGB(ulBase + I2C_STATUS) & I2C_STATUS_BUSY))
    {
        I2CStopSend(ulBase);
        return 0;
    }
    //
    // Send address
    //    
    ulStatus = I2CByteSend(ulBase, (ucSlaveAddr << 1));
    if(!(ulStatus == I2C_MASTER_EVENT_TX))
    {
        I2CStopSend(ulBase);
        return 0;
    }

    //
    // Send data
    //    
    I2CByteSend(ulBase, *pucDataBuf);
    
    //
    // Check if any error occurs
    //
    if(!(ulStatus == I2C_MASTER_EVENT_TX))
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
I2CMasterWriteBufS2(unsigned long ulBase, const unsigned char *pucDataBuf,
                     unsigned long ulLen, xtBoolean bEndTransmition)
{
    unsigned long i;
    unsigned long ulStatus;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
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
        if(!(ulStatus == I2C_MASTER_EVENT_TX))
        {
            I2CStopSend(ulBase);
            return i;
               
        }      
    }   
    //
    // Waiting the I2C controller to idle
    //    
    ulStatus = I2CByteSend(ulBase, *pucDataBuf);
    if(!(ulStatus == I2C_MASTER_EVENT_TX))
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
I2CMasterReadRequestS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                        xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    xHWREGB(ulBase + I2C_CON1) &= ~I2C_CON1_TXAK;

    if(xtStartFlag == xfalse)
    {
        //
        // Send start
        //    
        I2CStartSend(ulBase);
        xtStartFlag = xtrue;
    }
    else
    {
        //
        // Send Repeat start
        //   
        xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
        xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_RSTA;
    }
    if(!(xHWREGB(ulBase + I2C_STATUS) & I2C_STATUS_BUSY))
    {
        I2CStopSend(ulBase);
        return ;
    }
    //
    // Send address
    //    
    ulStatus = I2CByteSend(ulBase, (ucSlaveAddr << 1) | 1) ;
    if(!(ulStatus == I2C_MASTER_EVENT_RX))
    {
        I2CStopSend(ulBase);
        return ;
    }
    if(bEndTransmition)
    {
        xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_TXAK;
        I2CStopSend(ulBase);
    }
    else
    {
        xHWREGB(ulBase + I2C_CON1) &= ~I2C_CON1_TXAK;
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
I2CMasterReadRequestS2(unsigned long ulBase, xtBoolean bEndTransmition)
{  
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    //
    // Send the stop if End Transmition.
    //
    if(bEndTransmition)
    {
        xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_TXAK;
        I2CStopSend(ulBase);
    }
    else
    {
        xHWREGB(ulBase + I2C_CON1) &= ~I2C_CON1_TXAK;
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
I2CMasterReadLastRequestS2(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    //
    // RECEIVE operation with negative ACK(no stop)
    //
    xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_TXAK;    
    
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
I2CMasterReadS1(unsigned long ulBase, 
                 unsigned char ucSlaveAddr,
                 unsigned char *pucData,
                 xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    xASSERT(pucData);
    
    xI2CMasterReadRequestS1(ulBase, ucSlaveAddr, xfalse);

    SysCtlDelay(100);
    xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
    
    while (!(xHWREGB(ulBase + I2C_STATUS) & I2C_STATUS_IF));

    *pucData = xHWREGB(ulBase + I2C_DAT);
    
    ulStatus = (xHWREGB(ulBase + I2C_STATUS));
    
    if (ulStatus != I2C_MASTER_EVENT_RX)
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
I2CMasterReadS2(unsigned long ulBase,
                 unsigned char *pucData,
                 xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));

    xI2CMasterReadRequestS2(ulBase, xfalse);

    if(bEndTransmition)
    {
        xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_TXAK;
    } 
    
    xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
    
    //
    // Waiting the I2C controller to be transmited
    //
    while (!(xHWREGB(ulBase + I2C_STATUS) & I2C_STATUS_IF));
    *pucData = (unsigned char)xHWREGB(ulBase + I2C_DAT);
    
    //
    // Get the Status code
    //
    ulStatus =  (xHWREGB(ulBase + I2C_STATUS));
    
    //
    // Waiting the I2C controller to be transmited
    //
    if (ulStatus != I2C_MASTER_EVENT_RX)
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
I2CMasterReadBufS1(unsigned long ulBase, unsigned char ucSlaveAddr,
                    unsigned char* pucDataBuf, unsigned long ulLen,
                    xtBoolean bEndTransmition)
{
    unsigned long ulStatus;
    unsigned long ulRead;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
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
            pucDataBuf[0] = xHWREGB(ulBase + I2C_DAT);
            
            return 1;
        }
        else
        {
            return 0;   
        }
    }

    //xHWREGB(ulBase + I2C_O_CON) |= I2C_CON_AA;
    
    if(xtStartFlag == xfalse)
    {
        //
        // Send start
        //    
        I2CStartSend(ulBase);
        xtStartFlag = xtrue;
    }
    else
    {
        //
        // Send Repeat start
        //   
        xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
        xHWREGB(ulBase + I2C_CON1) |= I2C_CON1_RSTA;
    }
    if(!(xHWREGB(ulBase + I2C_STATUS) & I2C_STATUS_BUSY))
    {
        I2CStopSend(ulBase);
        return 0;
    }
    //
    // Send address
    //    
    ulStatus = I2CByteSend(ulBase, (ucSlaveAddr << 1) | 1) ;
    
    if(!(ulStatus == I2C_MASTER_EVENT_RX))
    {
        I2CStopSend(ulBase);
        return 0;
    }

    //
    // Waiting the I2C controller to be transmited
    //
    //xI2CMasterReadRequestS1(ulBase, ucSlaveAddr, xfalse);
    
    ulStatus = I2CByteGet(ulBase, &pucDataBuf[0], 1);
    
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
I2CMasterReadBufS2(unsigned long ulBase, unsigned char *pucDataBuf,
                    unsigned long ulLen, xtBoolean bEndTransmition)
{
    unsigned long i;
    unsigned long ulStatus;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
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
        if (ulStatus != I2C_MASTER_EVENT_RX)
        {
            I2CStopSend(ulBase);
            return i;
        }
    }  

    if(bEndTransmition)
    {
        xHWREGB(ulBase + I2C_CON1) |= ~(I2C_CON1_TXAK);
        xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
    }
    
    xHWREGB(ulBase + I2C_STATUS) |= I2C_STATUS_IF;
    
    while (!(xHWREGB(ulBase + I2C_STATUS) & I2C_STATUS_IF));

    *pucDataBuf = xHWREGB(ulBase + I2C_DAT);

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
unsigned long 
I2CMasterError(unsigned long ulBase)
{
    unsigned long ulStatus;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == I2C0_BASE) || ((ulBase == I2C1_BASE)));
    
    ulStatus = (xHWREGB(ulBase + I2C_STATUS));
    
    if((ulStatus & I2C_STATUS_RXAK))
    {
        return xI2C_MASTER_ERR_ADDR_ACK;
    }
    if((ulStatus & I2C_STATUS_RXAK))
    {
        return xI2C_MASTER_ERR_DATA_ACK;
    }
    if((ulStatus & I2C_STATUS_ARBL))
    {
        return xI2C_MASTER_ERR_ARB_LOST;
    }
    return xI2C_MASTER_ERR_NONE;
}

