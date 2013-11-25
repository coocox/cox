//*****************************************************************************
//
//! \file PCF8574.c
//! \brief Remote 8-bit I/O expander for I2C-bus driver.
//! \version V2.1.1.0
//! \date 4/1/2013
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

#include "PCF8574.h"

#define I2C_TRAN_END            1
#define I2C_TRAN_NOT_END        0

//*****************************************************************************
//
//! \brief Initialize I2C
//!
//! \param None
//!
//! This function initialize the mcu I2C as master and specified I2C port.
//!
//! \note internal function, used in this file only.
//! \note The max data rate is 100KHz.
//! \return None.
//
//*****************************************************************************
static Result _I2CComPortInit(void)
{
    //I2C Max clock: 100K
    uint32_t I2CInitClkRate = 100000;

    xSysCtlPeripheralEnable(PCF8574_I2C_GPIO);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

    //
    // Enable the I2C which is connected with PCF8574
    //
    xSysCtlPeripheralEnable2(PCF8574_PIN_I2C_PORT);

    //
    // Set PCF8574_PIN_I2C_SCK as I2C SCK Pin
    //
    xSPinTypeI2C(PCF8574_I2C_SCK, PCF8574_PIN_I2C_SCK);

    //
    // Set PCF8574_PIN_I2C_SDA as I2C SDA Pin
    //
    xSPinTypeI2C(PCF8574_I2C_SDA, PCF8574_PIN_I2C_SDA);

    //
    // I2C enable
    //
    xI2CMasterEnable(PCF8574_PIN_I2C_PORT);

    //
    // Initializes the I2C Master block.
    //
    xI2CMasterInit(PCF8574_PIN_I2C_PORT, I2CInitClkRate);

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Write one byte to special register
//!
//! \param RegAddr specifies the target register address.
//! \param Data is the data written to target register.
//!
//!  This function is to write one byte to PCF8574 register,one byte will be
//!  writen in appointed address.
//!
//! \note internal function, used in this file only.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
static Result _I2CRegWriteByte(uint8_t RegAddr, uint8_t Data)
{
    Result retv = SUCCESS;

    // Begin to I2C Transfer
    // first send START signal to control I2C bus
    // then send 7-bit address and R/W bit to I2C salve
    // at last send target register address
    retv = xI2CMasterWriteS1(PCF8574_PIN_I2C_PORT, PCF8574_I2C_ADDR,
            RegAddr, I2C_TRAN_NOT_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    // Send the wanted data to I2C bus
    // then Send STOP signal to release I2C bus
    retv = xI2CMasterWriteS2(PCF8574_PIN_I2C_PORT, Data, I2C_TRAN_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Read one byte from special register
//!
//! \param RegAddr specifies the target register address.
//! \param DataRecvBuf is the address you want to store the readback data.
//!
//!  This function is to read one byte from PCF8574 register,
//!  and write the data to the special address.
//!
//! \note internal function, used in this file only.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
static Result _I2CRegReadByte(uint8_t RegAddr, uint8_t * DataRecvBuf)
{
    Result retv = SUCCESS;

    //! Read Data from I2C bus port
    //! \note the second data received is vaild. Show as below
    //! Transfer format
    //! S SalveI2CAddress+R A Data_1  A  Data_2 NA E
    //!                       Invaild    Vaild
    //! S : Start
    //! A : Acknowledge
    //! NA: NoAcknowledge
    //! E : End

    // Send Salve address and receive an invaild data(8-bit).
    retv = xI2CMasterReadS1(PCF8574_PIN_I2C_PORT, PCF8574_I2C_ADDR,
            DataRecvBuf, I2C_TRAN_NOT_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    // Receive an vaild data(8-bit).
    retv = xI2CMasterReadS2(PCF8574_PIN_I2C_PORT, DataRecvBuf, I2C_TRAN_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Initialize the Remote 8-bit I/O expander for I2C-bus Hardwire.
//!
//! \param none.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//***************************************************************************** 
Result PCF8574_Init(void)
{
    return (_I2CComPortInit());
}

//*****************************************************************************
//
//! \brief Write an Byte to IO Port.
//!
//! \param Val is the Port Value you want to write.
//!  the port is 8-bit width.
//!  MSB is respond to PIN7
//!  LSB is respond to PIN0
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//***************************************************************************** 
Result PCF8574_WriteByte(uint8_t Val)
{
    uint8_t UseLessData = 0;
    return (_I2CRegWriteByte(UseLessData , Val));
}

//*****************************************************************************
//
//! \brief Read an Byte from IO Port.
//!
//! \param pVal is the buffer address stored the received Port value.
//!  the port value is 8-bit width.
//!  MSB is respond to PIN7
//!  LSB is respond to PIN0
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//***************************************************************************** 
Result PCF8574_ReadByte(uint8_t * pVal)
{
    uint8_t UseLessData = 0;
    return (_I2CRegReadByte(UseLessData , pVal));
}

//*****************************************************************************
//
//! \brief Write the special bit(s).
//!
//! \param Mask is the bit(s) you want to write. 8-bit width.
//!  MSB is respond to PIN7
//!  LSB is respond to PIN0
//!
//! \param Val is bit value respond to masked bit.
//! 
//! \note:
//! if you want to set PIO5 to 1, PIO3 to 0.
//! then, bit mask is (1<<5) | (1<<3)  that is 0x28
//!       bit value is (1<<5) | (0<<3) that is 0x20
//! so, you can call WriteBits like below:
//!  PCF8574_WriteBits(0x28, 0x20);
//!
//! \note: you must check the function return value to ensure the data is vaild.
//! 
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result PCF8574_WriteBits(uint8_t Mask, uint8_t Val)
{
    uint8_t RegVal      = 0; 
    uint8_t UseLessData = 0;
    Result  retv        = SUCCESS;

    retv =  _I2CRegReadByte(UseLessData, &RegVal);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }
    
    Val &= Mask;
    RegVal &= ~Mask;
    RegVal |= Val;

    retv =  _I2CRegWriteByte(UseLessData, RegVal);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Read the special bit(s) value.
//!
//! \param Mask is the bit(s) you want to read. 8-bit width.
//!  MSB is respond to PIN7
//!  LSB is respond to PIN0
//!
//! \param pVal is the buffer address stored the received Port value.
//! 
//! \note:
//! if you want to check the PIO5 value.
//! then, bit mask is (1<<5) that is 0x20
//! so, you can call WriteBits like below:
//!  retv = PCF8574_ReadBits(0x20, &Buf);
//!  if(retv != SUCCESS)
//!  {
//!      return (FAILURE);
//!  }
//!  //Do your work here.
//! 
//! \note: you must check the function return value to ensure the data is vaild.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result PCF8574_ReadBits(uint8_t Mask, uint8_t * pVal)
{
    uint8_t RegVal      = 0; 
    uint8_t UseLessData = 0;
    Result  retv        = SUCCESS;

    retv =  _I2CRegReadByte(UseLessData, &RegVal);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    *pVal &= Mask;

    return (SUCCESS);
}

