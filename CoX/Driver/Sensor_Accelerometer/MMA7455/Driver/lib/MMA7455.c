//*****************************************************************************
//
//! \file LIS302DL.c
//! \brief the Accelerometer LIS302DL Driver.
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

#include "MMA7455.h"


#if defined(MMA7455_PORT_I2C)
#define I2C_TRAN_END            1
#define I2C_TRAN_NOT_END        0
#endif


////////////////////////// Port Function I2C Interface ////////////////////////
//! For use accelerometer, you need to rewrite three functions
//! _I2CComPortInit  or _SPIComPortInit  : Initialize the communication hardware port
//! _I2CRegWriteByte or _SPIRegWriteByte : Write a byte to accelerometer register
//! _I2CRegReadByte  or _SPIRegReadByte  : Read a byte from accelerometer register

#if defined(MMA7455_PORT_I2C)

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

    xSysCtlPeripheralEnable(MMA7455_I2C_GPIO);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

    //
    // Enable the I2C which is connected with MMA7455
    //
    xSysCtlPeripheralEnable2(MMA7455_PIN_I2C_PORT);

    //
    // Set MMA7455_PIN_I2C_SCK as I2C SCK Pin
    //
    xSPinTypeI2C(MMA7455_I2C_SCK, MMA7455_PIN_I2C_SCK);

    //
    // Set MMA7455_PIN_I2C_SDA as I2C SDA Pin
    //
    xSPinTypeI2C(MMA7455_I2C_SDA, MMA7455_PIN_I2C_SDA);

    //
    // I2C enable
    //
    xI2CMasterEnable(MMA7455_PIN_I2C_PORT);

    //
    // Initializes the I2C Master block.
    //
    xI2CMasterInit(MMA7455_PIN_I2C_PORT, I2CInitClkRate);

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Write one byte to special register
//!
//! \param RegAddr specifies the target register address.
//! \param Data is the data written to target register.
//!
//!  This function is to write one byte to MMA7455 register,one byte will be
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
    retv = xI2CMasterWriteS1(MMA7455_PIN_I2C_PORT, MMA7455_I2C_ADDR,
            RegAddr, I2C_TRAN_NOT_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    // Send the wanted data to I2C bus
    // then Send STOP signal to release I2C bus
    retv = xI2CMasterWriteS2(MMA7455_PIN_I2C_PORT, Data, I2C_TRAN_END);
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
//!  This function is to read one byte from MMA7455 register,
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
    retv = xI2CMasterWriteS1(MMA7455_PIN_I2C_PORT, MMA7455_I2C_ADDR,
            RegAddr, I2C_TRAN_NOT_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    // Send restart signal then receive one byte from I2C bus
    // at last Send STOP signal to release I2C bus
    retv = xI2CMasterReadS1(MMA7455_PIN_I2C_PORT, MMA7455_I2C_ADDR,
            DataRecvBuf, I2C_TRAN_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return(SUCCESS);
}

#elif defined(MMA7455_PORT_SPI)
#error This version of the driver does NOT support SPI communication port
#else
#error You must select MMA7455 communction port(I2C/SPI) first.
#endif  

Result MMA7455_Init(void)
{
#if defined(MMA7455_PORT_I2C)
    return ( _I2CComPortInit() );
#elif defined(MMA7455_PORT_SPI)
#error This version of the driver does NOT support SPI communication port,\
    please select I2C port
#else
#error You must select MMA7455 communction port(I2C/SPI) first.
#endif
}

//*****************************************************************************
//
//! \brief Write one byte to special register
//!
//! \param RegAddr specifies the target register address.
//! \param Data is the data written to target register.
//!
//!  This function is to write one byte to MMA7455 register,one byte will be
//!  writen in appointed address.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA7455_RegWriteByte(uint8_t RegAddr, uint8_t Data)
{

#if defined(MMA7455_PORT_I2C)
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
#elif defined(MMA7455_PORT_SPI)
#error This version of the driver does NOT support SPI communication port,\
    please select I2C port
#else
#error You must select MMA7455 communction port(I2C/SPI) first.
#endif
}

//*****************************************************************************
//
//! \brief Read one byte from special register
//!
//! \param RegAddr specifies the target register address.
//! \param DataRecvBuf is the address you want to store the readback data.
//!
//!  This function is to read one byte from MMA7455 register,
//!  and write the data to the special address.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA7455_RegReadByte(uint8_t RegAddr, uint8_t * DataRecvBuf)
{
#if defined(MMA7455_PORT_I2C)
    Result retv = SUCCESS;

    //Read back the value and check it
    retv =  _I2CRegReadByte(RegAddr, DataRecvBuf);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return(retv);
#elif defined(MMA7455_PORT_SPI)
#error This version of the driver does NOT support SPI communication port,\
    please select I2C port
#else
#error You must select MMA7455 communction port(I2C/SPI) first.
#endif
}

//*****************************************************************************
//
//! \brief Read accelerometer 8-bit data.
//!
//! \param Axis is the axis data which you want to read. this paramter can be
//! one of the following value: \b AXIS_X \b AXIS_Y \b AXIS_Z.
//!
//! \param DataRecvBuf is the receive buffer addrress.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA7455_ReadAccData_8(uint32_t Axis, int8_t * DataRecvBuf)
{
    uint8_t  RegAddr = 0;
    uint8_t  RegVal  = 0;
    Result   retv    = SUCCESS;

    //Check param vaild
    ASSERT ((Axis == AXIS_X) || (Axis == AXIS_Y) || (Axis == AXIS_Z));
    ASSERT (DataRecvBuf != NULL);

    RegAddr = (uint8_t) (Axis >> 8);

    //Read Low 8 bit
    retv = MMA7455_RegReadByte(RegAddr, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    *DataRecvBuf = RegVal;

    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Read accelerometer 10-bit data.
//!
//! \param Axis is the axis data which you want to read. this paramter can be
//! one of the following value: \b AXIS_X \b AXIS_Y \b AXIS_Z.
//!
//! \param DataRecvBuf is the receive buffer addrress.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA7455_ReadAccData_10(uint32_t Axis, int16_t * DataRecvBuf)
{
    uint8_t  RegAddr = 0;
    uint8_t  RegVal  = 0;
    uint16_t TmpVal  = 0;
    Result   retv    = SUCCESS;

    //Check param vaild
    ASSERT ((Axis == AXIS_X) || (Axis == AXIS_Y) || (Axis == AXIS_Z));
    ASSERT (DataRecvBuf != NULL);

    RegAddr = (uint8_t) (Axis);

    //Read Low 8 bit
    retv = MMA7455_RegReadByte(RegAddr, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }
    TmpVal = (uint16_t)RegVal;

    //Read High 2 bit
    retv = MMA7455_RegReadByte(RegAddr+1, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }
    TmpVal  |= ((uint16_t)RegVal << 8);

    *DataRecvBuf = (int16_t) TmpVal;
    
    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Check MMA7455 Event status.
//!
//! \param Event is the Event(s) to be checked, the paramter can be \b OR of the
//! following value.
//!
//! \b ENEVT_DATA_READY        
//! \b ENEVT_DATA_OVER_WRITE   
//! \b ENEVT_PARITY_ERROR      
//! \b 
//! \b ENEVT_LEVEL_X           
//! \b ENEVT_LEVEL_Y           
//! \b ENEVT_LEVEL_Z           
//! \b ENEVT_PULSE_X           
//! \b ENEVT_PULSE_Y           
//! \b ENEVT_PULSE_Z           
//! \b ENEVT_INT_1             
//! \b ENEVT_INT_2 
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or \b FAILURE.  when checked event occured and there
//! is no error, then return \b SUCCESS.  others return \b FAILURE.
//
//*****************************************************************************
Result MMA7455_EventCheck(uint16_t Event)
{
    uint16_t RegValue = 0;
    uint8_t  TmpValue = 0;
    Result   retv     = SUCCESS;

    //Check paramter voild
    ASSERT ((Event & ~ENEVT_MASK) == 0);

    retv = MMA7455_RegReadByte(MMA7455_REG_STATUS, &TmpValue);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }
    RegValue = TmpValue;

    retv = MMA7455_RegReadByte(MMA7455_REG_DETSRC, &TmpValue);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }
    RegValue |= (TmpValue << 8);

    if( (RegValue & Event) != 0 )
    {
        return(SUCCESS);
    }
    else
    {
        return(FAILURE);
    }
}

//*****************************************************************************
//
//! \brief Get Accelerometer ID.
//!
//! \param ID is the receive buffer addrress.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//*****************************************************************************
Result MMA7455_GetID(uint8_t * ID)
{
    ASSERT ((Event & ~ENEVT_MASK) == 0);
    return (MMA7455_RegReadByte(MMA7455_REG_WHOAMI, ID));
}

//*****************************************************************************
//
//! \brief Check MMA7455 Event status.
//!
//! \param Axis is the axis data which you want to read. this paramter can be
//! one of the following value: \b AXIS_X \b AXIS_Y \b AXIS_Z.
//!
//! \param OffSet is used for setting and storing the offset calibrations to
//! eliminate the 0g offset. Please refer to Freescale application note AN3745
//! for detailed instructions on the process to set and store the calibration
//! values.  
//! NOTE: OffSet <= 0x3FF
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//*****************************************************************************
Result MMA7455_OffSetWrite(uint32_t Axis, uint16_t OffSet)
{
    uint8_t  RegAddr = 0;
    uint32_t Mask    = 0x3FF;
    Result   retv    = SUCCESS;

    ASSERT ((Axis == AXIS_X) || (Axis == AXIS_Y) || (Axis == AXIS_Z));
    ASSERT (OffSet <= 0x3FF);

    //Offset Drift X/Y/Z LSB
    RegAddr = (uint8_t) (Axis >> 16);
    OffSet &= Mask;
    retv = MMA7455_RegWriteByte(RegAddr, (uint8_t) OffSet);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    //Offset Drift X/Y/Z MSB
    RegAddr += 1;
    retv = MMA7455_RegWriteByte(RegAddr, (uint8_t) (OffSet >> 8));
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Configure MMA7455
//!
//! \param Cfg the paramter can be \b OR of the following value.
//! more information, please reference Macro below.
//! \b CFG_DATA_RDY_OUT_EN         
//! \b CFG_DATA_RDY_OUT_DIS        
//
//! \b CFG_SPI_3_WIRE              
//! \b CFG_SPI_4_WIRE              
//
//! \b CFG_SELFTEST_EN             
//! \b CFG_SELFTEST_DIS            
//
//! \b CFG_RANGE_2G                
//! \b CFG_RANGE_4G                
//! \b CFG_RANGE_8G                
//
//! \b CFG_MODE_STANDBY            
//! \b CFG_MODE_MEASUREMENT        
//! \b CFG_MODE_LEVEL              
//! \b CFG_MODE_PULSE              
//
//! \b CFG_FILTER_BAND_62_5        
//! \b CFG_FILTER_BAND_125         
//
//! \b CFG_THRESHOLD_VALUE_ABS     
//! \b CFG_THRESHOLD_VALUE_INT     
//
//! \b CFG_AXIS_Z_EN               
//! \b CFG_AXIS_Z_DIS              
//! \b CFG_AXIS_Y_EN               
//! \b CFG_AXIS_Y_DIS              
//! \b CFG_AXIS_X_EN               
//! \b CFG_AXIS_X_DIS              
//
//! \b CFG_INT_MODE_0              
//! \b CFG_INT_MODE_1              
//! \b CFG_INT_MODE_2              
//
//! \b CFG_INT_PIN_NORMAL          
//! \b CFG_INT_PIN_EXCHANGE        
//
//! \b CFG_STRENGTH_STANDARD       
//! \b CFG_STRENGTH_STRONGE        
//
//! \b CFG_PULSE_DETECTION_OR      
//! \b CFG_PULSE_DETECTION_AND     
//
//! \b CFG_LEVEL_DETECTION_OR      
//! \b CFG_LEVEL_DETECTION_AND     
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************

Result MMA7455_Cfg(uint64_t Cfg)
{
    uint8_t   RegValue   =   0;
    Result    retv       =   SUCCESS;

    ASSERT ((Cfg & ~CFG_MASK) == 0);

    //Configure Mode control register
    if(Cfg & CFG_MASK_1)
    {
        retv = MMA7455_RegReadByte(MMA7455_REG_MCTL, &RegValue);
        if (retv != SUCCESS)
        {
            return (FAILURE);
        }

        if(Cfg & CFG_RANGE_MASK)
        {
            RegValue &= ~CFG_RANGE_MASK;
        }

        if(Cfg & CFG_MODE_MASK)
        {
            RegValue &= ~CFG_MODE_MASK;
        }

        RegValue |= (uint8_t)  (Cfg >> 0);
        RegValue &= (uint8_t) ~(Cfg >> 8);

        retv = MMA7455_RegWriteByte(MMA7455_REG_MCTL, RegValue);
        if (retv != SUCCESS)
        {
            return (FAILURE);
        }
    }

    //Configure control register 1
    if(Cfg & CFG_MASK_2)
    {
        retv = MMA7455_RegReadByte(MMA7455_REG_CTL1, &RegValue);
        if (retv != SUCCESS)
        {
            return (FAILURE);
        }

        if(Cfg & CFG_INT_MODE_M)
        {
            RegValue &= ~CFG_INT_MODE_M;
        }

        RegValue |= (uint8_t)  (Cfg >> 16);
        RegValue &= (uint8_t) ~(Cfg >> 24);

        retv = MMA7455_RegWriteByte(MMA7455_REG_CTL1, RegValue);
        if (retv != SUCCESS)
        {
            return (FAILURE);
        }
    }

    //Configure control register 2
    if(Cfg & CFG_MASK_3)
    {
        retv = MMA7455_RegReadByte(MMA7455_REG_CTL2, &RegValue);
        if (retv != SUCCESS)
        {
            return (FAILURE);
        }

        RegValue |= (uint8_t)  (Cfg >> 32);
        RegValue &= (uint8_t) ~(Cfg >> 40);

        retv = MMA7455_RegWriteByte(MMA7455_REG_CTL2, RegValue);
        if (retv != SUCCESS)
        {
            return (FAILURE);
        }
    }

    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Clear Interrupt flag.
//!
//! \param IntID is the interrupt number you want to clear, this paramter can be one
//! of the following value.  \b INT_ID_1 , \b INT_ID_1.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA7455_IntFlagClear(uint8_t IntID)
{
    Result    retv       =   SUCCESS;

    ASSERT ((IntID & ~INT_ID_M) == 0);

    retv = MMA7455_RegWriteByte(MMA7455_REG_INTRST, IntID);
    if (retv != SUCCESS)
    {
        return (FAILURE);
    }

    retv = MMA7455_RegWriteByte(MMA7455_REG_INTRST, 0);
    if (retv != SUCCESS)
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Set Level ThresHold value.
//!
//! \param ThresHold is Level detection threshold value.
//! If THOPT bit in Detection Control Register is ¡°0¡±,
//!    it is unsigned 7 bits value and LDTH[7] should be ¡°0¡±.
//! If THOPT bit is ¡°1¡±,
//!    it is signed 8 bits value.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA7455_LevelThresHoldSet(uint8_t ThresHold)
{
    return( MMA7455_RegWriteByte(MMA7455_REG_LDTH, ThresHold) );
}

//*****************************************************************************
//
//! \brief Set Pulse ThresHold value.
//!
//! \param ThresHold is Pulse detection threshold value (unsigned 7 bits).
//! NOTE: ThresHold <= 0x7F
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA7455_PulseThresHoldSet(uint8_t ThresHold)
{
    ASSERT (ThresHold <= 0x7F);
    return( MMA7455_RegWriteByte(MMA7455_REG_PDTH, ThresHold & 0x7F) );
}

//*****************************************************************************
//
//! \brief Set Pulse Duration value.
//!
//! \param Dur is Pulse Duration value, used for click.
//! NOTE: 0 <= Dur <= 255 mean: 0.5ms --> 127.5ms
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA7455_PulseDurationSet(uint8_t Dur)
{
    return( MMA7455_RegWriteByte(MMA7455_REG_PW, Dur) );
}

//*****************************************************************************
//
//! \brief Set Latency time.
//!
//! \param Latency is used for double click.
//! NOTE: 0 <= Latency <= 255 mean: 1ms --> 255ms
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA7455_LatencyTimeSet(uint8_t Latency)
{
    return( MMA7455_RegWriteByte(MMA7455_REG_LT, Latency) );
}

//*****************************************************************************
//
//! \brief Set windows value.
//!
//! \param Windows is used for double click.
//! NOTE: 0 <= Windows <= 255 mean: 1ms --> 255ms
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA7455_WindowsSet(uint8_t Windows)
{
    return( MMA7455_RegWriteByte(MMA7455_REG_TW, Windows) );
}

