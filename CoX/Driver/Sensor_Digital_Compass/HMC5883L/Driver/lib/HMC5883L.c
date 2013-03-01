//*****************************************************************************
//
//! \file HMC5883L.c
//! \brief the Digital compass ic Driver.
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

#include "HMC5883L.h"

#define I2C_TRAN_END            1
#define I2C_TRAN_NOT_END        0


////////////////////////// Port Function I2C Interface ////////////////////////
//! For use Digital compass, you need to rewrite three functions
//! _I2CComPortInit  : Initialize the communication hardware port
//! _I2CRegWriteByte : Write a byte to accelerometer register
//! _I2CRegReadByte  : Read a byte from accelerometer register


//*****************************************************************************
//
//! \brief Initialize I2C
//!
//! \param None
//!
//! This function initialize the mcu I2C as master and specified I2C port.
//! The master block will be set up to transfer data at 100 kbps.
//!
//! \note internal function, used in this file only.
//! \return None.
//
//*****************************************************************************
static Result _I2CComPortInit(void)
{
    //I2C default clock: 100K
    uint32_t I2CInitClkRate = 100000;

    xSysCtlPeripheralEnable(HMC5883L_I2C_GPIO);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

    //
    // Enable the I2C which is connected with HMC5883L
    //
    xSysCtlPeripheralEnable2(HMC5883L_PIN_I2C_PORT);

    //
    // Set HMC5883L_PIN_I2C_SCK as I2C SCK Pin
    //
    xSPinTypeI2C(HMC5883L_I2C_SCK, HMC5883L_PIN_I2C_SCK);

    //
    // Set HMC5883L_PIN_I2C_SDA as I2C SDA Pin
    //
    xSPinTypeI2C(HMC5883L_I2C_SDA, HMC5883L_PIN_I2C_SDA);

    //
    // I2C enable
    //
    xI2CMasterEnable(HMC5883L_PIN_I2C_PORT);

    //
    // Initializes the I2C Master block.
    //
    xI2CMasterInit(HMC5883L_PIN_I2C_PORT, I2CInitClkRate);

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Write one byte to special register
//!
//! \param RegAddr specifies the target register address.
//! \param Data is the data written to target register.
//!
//!  This function is to write one byte to HMC5883L register,one byte will be
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
    retv = xI2CMasterWriteS1(HMC5883L_PIN_I2C_PORT, HMC5883L_I2C_ADDR,
            RegAddr, I2C_TRAN_NOT_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    // Send the wanted data to I2C bus
    // then Send STOP signal to release I2C bus
    retv = xI2CMasterWriteS2(HMC5883L_PIN_I2C_PORT, Data, I2C_TRAN_END);
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
//!  This function is to read one byte from HMC5883L register,
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

    // Begin to I2C Transfer
    // first send START signal to control I2C bus
    // then send 7-bit address and R/W bit to I2C salve
    // at last send target register address
    retv = xI2CMasterWriteS1(HMC5883L_PIN_I2C_PORT, HMC5883L_I2C_ADDR,
            RegAddr, I2C_TRAN_NOT_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    // Send restart signal then receive one byte from I2C bus
    // at last Send STOP signal to release I2C bus
    retv = xI2CMasterReadS1(HMC5883L_PIN_I2C_PORT, HMC5883L_I2C_ADDR,
            DataRecvBuf, I2C_TRAN_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return(SUCCESS);
}

//Check device ID
Result HMC5883L_Init(void)
{
    Result  Res  = SUCCESS;
    uint8_t Rec = 0;
    
    Res = _I2CComPortInit();
    if(Res == FAILURE)
    {
        return (FAILURE);
    }

    //ID -- 'H'
    Res = HMC5883L_RegReadByte(HMC5883L_ID_A, &Rec);
    if(Res == FAILURE || Rec != ID_A_VALUE)
    {
        return (FAILURE);
    }
    
    //ID -- '4'
    Res = HMC5883L_RegReadByte(HMC5883L_ID_B, &Rec);
    if(Res == FAILURE || Rec != ID_B_VALUE)
    {
        return (FAILURE);
    }
    
    //ID -- '3'
    Res = HMC5883L_RegReadByte(HMC5883L_ID_C, &Rec);
    if(Res == FAILURE || Rec != ID_C_VALUE)
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Write one byte to special register
//!
//! \param RegAddr specifies the target register address.
//! \param Data is the data written to target register.
//!
//!  This function is to write one byte to HMC5883L register,one byte will be
//!  writen in appointed address.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result HMC5883L_RegWriteByte(uint8_t RegAddr, uint8_t Data)
{

    Result  retv  = SUCCESS;
    uint8_t _TmpReg = 0;

    //Write value to the special Register
    retv =  _I2CRegWriteByte(RegAddr, Data);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Read back the value and check it
    retv =  _I2CRegReadByte(RegAddr, &_TmpReg);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Be sure that Data has written into target register successfully
    if(_TmpReg != Data)
    {
        return (FAILURE);
    }

    //Success read the value into special register
    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Read one byte from special register
//!
//! \param RegAddr specifies the target register address.
//! \param DataRecvBuf is the address you want to store the readback data.
//!
//!  This function is to read one byte from HMC5883L register,
//!  and write the data to the special address.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result HMC5883L_RegReadByte(uint8_t RegAddr, uint8_t * DataRecvBuf)
{
    Result retv = SUCCESS;

    //Read back the value and check it
    retv =  _I2CRegReadByte(RegAddr, DataRecvBuf);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return(retv);
}

//*****************************************************************************
//
//! \brief Configure Digital compass.
//!
//! \param Cfg the paramter can be \b OR of the following value.
//! more information, please reference Macro below.
//!
//! SAMPLE_1
//! SAMPLE_2
//! SAMPLE_4
//! SAMPLE_8
//!                                        
//! DATA_RATE_0_75
//! DATA_RATE_1_5
//! DATA_RATE_3    
//! DATA_RATE_7_5  
//! DATA_RATE_15   
//! DATA_RATE_30   
//! DATA_RATE_75   
//! 
//! GAIN_1370      
//! GAIN_1090      
//! GAIN_820       
//! GAIN_660       
//! GAIN_440       
//! GAIN_390       
//! GAIN_330       
//! GAIN_230       
//! 
//! MODE_CONT      
//! MODE_SIG       
//! MODE_IDLE      
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result HMC5883L_Cfg(uint32_t Cfg)
{
    Result  retv   = FAILURE;
    uint8_t TmpReg = 0;

    //Configure sample and data output rate
    if(Cfg & CFG_A_M)
    {
        TmpReg = 0;
        Cfg &= ~CFG_A_M;
        retv = HMC5883L_RegReadByte(HMC5883L_CFG_A, &TmpReg);
        if(retv == FAILURE)
        {
            return (FAILURE);
        }
        //Clear configure A register bit7
        TmpReg &= 0x7F;
        TmpReg &= (uint8_t)((~Cfg) >> 8);
        TmpReg |= (uint8_t)(( Cfg) >> 0);
        retv = HMC5883L_RegWriteByte(HMC5883L_CFG_A, TmpReg);
        if(retv == FAILURE)
        {
            return (FAILURE);
        }
    }

    //Configure Gain
    if(Cfg & CFG_B_M)
    {
        TmpReg = 0;
        Cfg &= ~CFG_B_M;
        TmpReg = (uint8_t)(Cfg >> 16);
        retv = HMC5883L_RegWriteByte(HMC5883L_CFG_B, TmpReg);
        if(retv == FAILURE)
        {
            return (FAILURE);
        }
    }

    //Configure mode
    if(Cfg & MODE_M)
    {
        TmpReg = 0;
        Cfg &= ~MODE_M;
        TmpReg = (uint8_t)(Cfg >> 24);
        retv = HMC5883L_RegWriteByte(HMC5883L_MODE, TmpReg);
        if(retv == FAILURE)
        {
            return (FAILURE);
        }
    }
    
    return (retv);
}


//*****************************************************************************
//
//! \brief Check  HMC5883L status.
//!
//! \param Flag is the Event(s) to be checked, the paramter can be \b OR of the
//! following value.
//!
//! \b STATUS_LOCK
//! \b STATUS_RDY    
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or \b FAILURE.  when checked event occured and there
//! is no error, then return \b SUCCESS.  others return \b FAILURE.
//
//*****************************************************************************
Result HMC5883L_StatusCheck(uint8_t Flag)
{
    Result  retv   = FAILURE;
    uint8_t TmpReg = 0;
    
    ASSERT(!(Flag & (STATUS_RDY | STATUS_LOCK)));

    retv = HMC5883L_RegReadByte(HMC5883L_STATUS, &TmpReg);
    if(retv == FAILURE)
    {
        return (FAILURE);
    }  

    return (Flag & TmpReg);
}

//*****************************************************************************
//
//! \brief Read Digital compass value.
//!
//! \param pDataX is the receive X axis data buffer addrress.
//! \param pDataY is the receive Y axis data buffer addrress.
//! \param pDataZ is the receive Z axis data buffer addrress.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result HMC5883L_DataGet(int16_t * pDataX, int16_t * pDataY, int16_t * pDataZ)
{
    Result  retv   = FAILURE;
    int16_t Data   = 0;
    uint8_t TmpReg = 0;
    
    ASSERT(pDataX != NULL);
    ASSERT(pDataY != NULL);
    ASSERT(pDataZ != NULL);

    //Read X Axis Data
    retv = HMC5883L_RegReadByte(HMC5883L_DATA_X_MSB, &TmpReg);
    if(retv == FAILURE)
    {
        return (FAILURE);
    }
    Data = (int16_t)TmpReg << 8;

    retv = HMC5883L_RegReadByte(HMC5883L_DATA_X_LSB, &TmpReg);
    if(retv == FAILURE)
    {
        return (FAILURE);
    }
    Data |= (int16_t)TmpReg;

    *pDataX = Data;
    Data    = 0;

    //Read Y Axis Data
    retv = HMC5883L_RegReadByte(HMC5883L_DATA_Y_MSB, &TmpReg);
    if(retv == FAILURE)
    {
        return (FAILURE);
    }
    Data = (int16_t)TmpReg << 8;

    retv = HMC5883L_RegReadByte(HMC5883L_DATA_Y_LSB, &TmpReg);
    if(retv == FAILURE)
    {
        return (FAILURE);
    }
    Data |= (int16_t)TmpReg;

    *pDataY = Data;
    Data    = 0;

    //Read Z Axis Data
    retv = HMC5883L_RegReadByte(HMC5883L_DATA_Z_MSB, &TmpReg);
    if(retv == FAILURE)
    {
        return (FAILURE);
    }
    Data = (int16_t)TmpReg << 8;

    retv = HMC5883L_RegReadByte(HMC5883L_DATA_Z_LSB, &TmpReg);
    if(retv == FAILURE)
    {
        return (FAILURE);
    }
    Data |= (int16_t)TmpReg;

    *pDataZ = Data;
    Data    = 0;

    return (SUCCESS);
}

