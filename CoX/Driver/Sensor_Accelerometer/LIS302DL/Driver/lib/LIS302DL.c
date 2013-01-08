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


#include "LIS302DL.h"


#if defined(LIS302DL_PORT_I2C)
#define I2C_TRAN_END            1
#define I2C_TRAN_NOT_END        0
#endif

////////////////////////// Port Function I2C Interface ////////////////////////
//! For use accelerometer, you need to rewrite three functions
//! _I2CComPortInit  or _SPIComPortInit  : Initialize the communication hardware port
//! _I2CRegWriteByte or _SPIRegWriteByte : Write a byte to accelerometer register
//! _I2CRegReadByte  or _SPIRegReadByte  : Read a byte from accelerometer register

#if defined(LIS302DL_PORT_I2C)

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

    xSysCtlPeripheralEnable(LIS302DL_I2C_GPIO);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

    //
    // Enable the I2C which is connected with LIS302DL
    //
    xSysCtlPeripheralEnable2(LIS302DL_PIN_I2C_PORT);

    //
    // Set LIS302DL_PIN_I2C_SCK as I2C SCK Pin
    //
    xSPinTypeI2C(LIS302DL_I2C_SCK, LIS302DL_PIN_I2C_SCK);

    //
    // Set LIS302DL_PIN_I2C_SDA as I2C SDA Pin
    //
    xSPinTypeI2C(LIS302DL_I2C_SDA, LIS302DL_PIN_I2C_SDA);

    //
    // I2C enable
    //
    xI2CMasterEnable(LIS302DL_PIN_I2C_PORT);

    //
    // Initializes the I2C Master block.
    //
    xI2CMasterInit(LIS302DL_PIN_I2C_PORT, I2CInitClkRate);

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Write one byte to special register
//!
//! \param RegAddr specifies the target register address.
//! \param Data is the data written to target register.
//!
//!  This function is to write one byte to LIS302DL register,one byte will be
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
    retv = xI2CMasterWriteS1(LIS302DL_PIN_I2C_PORT, LIS302DL_I2C_ADDR,
            RegAddr, I2C_TRAN_NOT_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    // Send the wanted data to I2C bus
    // then Send STOP signal to release I2C bus
    retv = xI2CMasterWriteS2(LIS302DL_PIN_I2C_PORT, Data, I2C_TRAN_END);
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
//!  This function is to read one byte from LIS302DL register,
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
    retv = xI2CMasterWriteS1(LIS302DL_PIN_I2C_PORT, LIS302DL_I2C_ADDR,
            RegAddr, I2C_TRAN_NOT_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    // Send restart signal then receive one byte from I2C bus
    // at last Send STOP signal to release I2C bus
    retv = xI2CMasterReadS1(LIS302DL_PIN_I2C_PORT, LIS302DL_I2C_ADDR,
            DataRecvBuf, I2C_TRAN_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return(SUCCESS);
}

#elif defined(LIS302DL_PORT_SPI)
#error This version of the driver does NOT support SPI communication port
#else
#error You must select LIS302DL communction port(I2C/SPI) first.
#endif

//*****************************************************************************
//
//! \brief Initialize LIS302DL communication port.
//!
//! \param None
//!
//! This function initialize the LIS302DL communication port(I2C/SPI).
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result LIS302DLInit(void)
{
#if defined(LIS302DL_PORT_I2C)
    Result retv = SUCCESS;
    retv =  _I2CComPortInit();
    return(retv);
#elif defined(LIS302DL_PORT_SPI)
#error This version of the driver does NOT support SPI communication port,\
    please select I2C port
#else
#error You must select LIS302DL communction port(I2C/SPI) first.
#endif
}

//*****************************************************************************
//
//! \brief Write one byte to special register
//!
//! \param RegAddr specifies the target register address.
//! \param Data is the data written to target register.
//!
//!  This function is to write one byte to LIS302DL register,one byte will be
//!  writen in appointed address.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result LIS302DLRegWriteByte(uint8_t RegAddr, uint8_t Data)
{

#if defined(LIS302DL_PORT_I2C)
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
#elif defined(LIS302DL_PORT_SPI)
#error This version of the driver does NOT support SPI communication port,\
    please select I2C port
#else
#error You must select LIS302DL communction port(I2C/SPI) first.
#endif
}

//*****************************************************************************
//
//! \brief Read one byte from special register
//!
//! \param RegAddr specifies the target register address.
//! \param DataRecvBuf is the address you want to store the readback data.
//!
//!  This function is to read one byte from LIS302DL register,
//!  and write the data to the special address.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result LIS302DLRegReadByte(uint8_t RegAddr, uint8_t * DataRecvBuf)
{
#if defined(LIS302DL_PORT_I2C)
    Result retv = SUCCESS;

    //Read back the value and check it
    retv =  _I2CRegReadByte(RegAddr, DataRecvBuf);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return(retv);
#elif defined(LIS302DL_PORT_SPI)
#error This version of the driver does NOT support SPI communication port,\
    please select I2C port
#else
#error You must select LIS302DL communction port(I2C/SPI) first.
#endif
}

//*****************************************************************************
//
//! \brief Configure LIS302DL.
//!  you can use this function to configure LIS302DL.
//!
//! \param Cfg the paramter can be OR of the following value.
//! \b LIS302DL_CLK_100K
//! \b LIS302DL_CLK_400K
//! \b LIS302DL_SCALE_2G
//! \b LIS302DL_SCALE_8G
//! \b LIS302DL_SELF_TEST_EN
//! \b LIS302DL_SELF_TEST_DIS
//! \b LIS302DL_X_EN
//! \b LIS302DL_X_DIS
//! \b LIS302DL_Y_EN
//! \b LIS302DL_Y_DIS
//! \b LIS302DL_Z_EN
//! \b LIS302DL_Z_DIS
//! \b
//! \b LIS302DL_SPI_3_WIRE
//! \b LIS302DL_SPI_4_WIRE
//! \b LIS302DL_CONTENT_NORMAL
//! \b LIS302DL_CONTENT_REBOOT
//! \b LIS302DL_FILTER_EN
//! \b LIS302DL_FILTER_DIS
//! \b LIS302DL_HP_WU1_EN
//! \b LIS302DL_HP_WU1_DIS
//! \b LIS302DL_HP_WU2_EN
//! \b LIS302DL_HP_WU2_DIS
//! \b LIS302DL_HP_COEFF_8X
//! \b LIS302DL_HP_COEFF_4X
//! \b LIS302DL_HP_COEFF_2X
//! \b LIS302DL_HP_COEFF_1X
//! \b
//! \b LIS302DL_INT_HIGH
//! \b LIS302DL_INT_LOW
//! \b LIS302DL_INT_PAD_PP
//! \b LIS302DL_INT_PAD_OD
//! \b LIS302DL_INT1_GND
//! \b LIS302DL_INT1_FF_WU_1
//! \b LIS302DL_INT1_FF_WU_2
//! \b LIS302DL_INT1_FF_WU_1_2
//! \b LIS302DL_INT1_DATA_RDY
//! \b LIS302DL_INT1_CLICK_INT
//! \b LIS302DL_INT2_GND
//! \b LIS302DL_INT2_FF_WU_1
//! \b LIS302DL_INT2_FF_WU_2
//! \b LIS302DL_INT2_FF_WU_1_2
//! \b LIS302DL_INT2_DATA_RDY
//! \b LIS302DL_INT2_CLICK_INT
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result LIS302DLCfg(uint64_t Cfg)
{
    Result    retv     =   SUCCESS;
    uint8_t   TmpReg   =   0;

    ASSERT((Cfg & (~LIS302DL_CFG_MASK)) == 0);

    if(Cfg == 0)
    {
        return (FAILURE);
    }

    //Configure Ctrl 1 register
    if(Cfg & LIS302DL_REG_1_MASK)
    {
        retv = LIS302DLRegReadByte(CTRL_REG1, &TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }

        TmpReg &= (uint8_t)(~(Cfg >> LIS302DL_REG1_UNSET_S));
        TmpReg |= (uint8_t)(  Cfg >> LIS302DL_REG1_SET_S   );

        retv = LIS302DLRegWriteByte(CTRL_REG1, TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }
    }

    //Configure Ctrl 2 register
    if(Cfg & LIS302DL_REG_2_MASK)
    {
        retv = LIS302DLRegReadByte(CTRL_REG2, &TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }

        if(Cfg & LIS302DL_HP_COEFF_MASK)
        {
            TmpReg &= (uint8_t)(~(LIS302DL_HP_COEFF_MASK >> LIS302DL_REG2_UNSET_S));
        }
        TmpReg &= (uint8_t)(~(Cfg >> LIS302DL_REG2_UNSET_S));
        TmpReg |= (uint8_t)(  Cfg >> LIS302DL_REG2_SET_S   );

        retv = LIS302DLRegWriteByte(CTRL_REG2, TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }
    }

    //Configure Ctrl 3 register
    if(Cfg & LIS302DL_REG_3_MASK)
    {
        retv = LIS302DLRegReadByte(CTRL_REG3, &TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }

        if(Cfg & LIS302DL_INT1_MASK)
        {
            TmpReg &= (uint8_t)(~(LIS302DL_INT1_MASK >> LIS302DL_REG3_UNSET_S));
        }
        if(Cfg & LIS302DL_INT2_MASK)
        {
            TmpReg &= (uint8_t)(~(LIS302DL_INT2_MASK >> LIS302DL_REG3_UNSET_S));
        }
        TmpReg &= (uint8_t)(~(Cfg >> LIS302DL_REG3_UNSET_S));
        TmpReg |= (uint8_t)(  Cfg >> LIS302DL_REG3_SET_S   );

        retv = LIS302DLRegWriteByte(CTRL_REG3, TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }
    }

    return (SUCCESS);
}


//*****************************************************************************
//
//! \brief Reset high pass-filter.
//!
//! Reading at this address zeroes instantaneously the content of the internal
//! high pass-filter. If the high pass filter is enabled all three axes are
//! instantaneously set to 0g.  This allows to overcome the settling time of the
//! high pass filter.
//!
//! \param None
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result LIS302DLHPFilterReset(void)
{
    Result    retv   =   SUCCESS;
    uint8_t   TmpReg =   0;

    retv = LIS302DLRegReadByte(HP_FILTER_RESET, &TmpReg);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Read accelerometer data.
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
Result LIS302DLAccDataRead(uint8_t Axis, uint8_t * DataRecvBuf)
{
    Result retv = SUCCESS;

    ASSERT( (Axis == AXIS_X) || (Axis == AXIS_Y) || (Axis == AXIS_Z));

    retv = LIS302DLRegReadByte(Axis, DataRecvBuf);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Get Accelerometer ID.
//!
//! \param ID is the receive buffer addrress.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result LIS302DLIDGet(uint8_t * ID)
{
    Result retv = SUCCESS;

    ASSERT(ID != NULL);

    retv = LIS302DLRegReadByte(WHO_AM_I, ID);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return (retv);
}

//*****************************************************************************
//
//! \brief Begin Accelerometer Measure.
//! This function can be used to set accelerometer into measure mode, then you
//! can read three axis data from accelerometer register. This function must be
//! called after \ref LIS302DLInit and \ref LIS302DLCfg function.
//! NOTE: Once you have Initialize LIS302DL module, you can call LIS302DLStart at
//! any times to begin measure, call LIS302DLStop to stop measure.
//!
//! \param None.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result LIS302DLStart(void)
{
    Result    retv     =   SUCCESS;
    uint8_t   TmpReg   =   0;

    retv = LIS302DLRegReadByte(CTRL_REG1, &TmpReg);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    TmpReg |= CTRL_REG1_PD;

    retv = LIS302DLRegWriteByte(CTRL_REG1, TmpReg);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Stop Accelerometer Measure.
//! This function can be used to set accelerometer into standby mode, then you
//! can read three axis data from accelerometer register. This function must be
//! called after \ref LIS302DLInit and \ref LIS302DLCfg function.
//! NOTE: Once you have Initialize LIS302DL module, you can call LIS302DLStart at
//! any times to begin measure, call LIS302DLStop to stop measure.
//!
//! \param None.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result LIS302DLStop(void)
{
    Result    retv     =   SUCCESS;
    uint8_t   TmpReg   =   0;

    retv = LIS302DLRegReadByte(CTRL_REG1, &TmpReg);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    TmpReg &= ~CTRL_REG1_PD;

    retv = LIS302DLRegWriteByte(CTRL_REG1, TmpReg);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return (SUCCESS);
}


//*****************************************************************************
//
//! \brief Configure LIS302DL Wake-up/Free-Fall.
//!  you can use this function to configure LIS302DL Wake-up/Free-Fall.
//!
//! \param Cfg the paramter can be OR of the following value.
//!
//! \b WUFF1_INT_EVENT_AND
//! \b WUFF1_INT_LATCH_EN
//! \b WUFF1_INT_Z_HIGH_EN
//! \b WUFF1_INT_Z_LOW_EN
//! \b WUFF1_INT_Y_HIGH_EN
//! \b WUFF1_INT_Y_LOW_EN
//! \b WUFF1_INT_X_HIGH_EN
//! \b WUFF1_INT_X_LOW_EN
//!
//! \b WUFF1_INT_EVENT_OR
//! \b WUFF1_INT_LATCH_DIS
//! \b WUFF1_INT_Z_HIGH_DIS
//! \b WUFF1_INT_Z_LOW_DIS
//! \b WUFF1_INT_Y_HIGH_DIS
//! \b WUFF1_INT_Y_LOW_DIS
//! \b WUFF1_INT_X_HIGH_DIS
//! \b WUFF1_INT_X_LOW_DIS
//!
//! \b WUFF2_INT_EVENT_AND
//! \b WUFF2_INT_LATCH_EN
//! \b WUFF2_INT_Z_HIGH_EN
//! \b WUFF2_INT_Z_LOW_EN
//! \b WUFF2_INT_Y_HIGH_EN
//! \b WUFF2_INT_Y_LOW_EN
//! \b WUFF2_INT_X_HIGH_EN
//! \b WUFF2_INT_X_LOW_EN
//!
//! \b WUFF2_INT_EVENT_OR
//! \b WUFF2_INT_LATCH_DIS
//! \b WUFF2_INT_Z_HIGH_DIS
//! \b WUFF2_INT_Z_LOW_DIS
//! \b WUFF2_INT_Y_HIGH_DIS
//! \b WUFF2_INT_Y_LOW_DIS
//! \b WUFF2_INT_X_HIGH_DIS
//! \b WUFF2_INT_X_LOW_DIS
//!
//! \b WUFF1_CNT_RESET
//! \b WUFF1_CNT_DEC
//! \b WUFF2_CNT_RESET
//! \b WUFF2_CNT_DEC
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result LIS302DLWUFFCfg(uint32_t Cfg)
{
    Result    retv     =   SUCCESS;
    uint8_t   TmpReg   =   0;
    uint8_t   RegAddr  =   0;

    ASSERT((Cfg & (~WUFF_CFG_MASK)) == 0);

    if(Cfg & WUFF_INT_MASK)
    {
        RegAddr = FF_WU_CFG_2;
    }
    else
    {
        RegAddr = FF_WU_CFG_1;
    }

    //Read click register value
    retv = LIS302DLRegReadByte(RegAddr, &TmpReg);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    TmpReg &= (uint8_t) ((~Cfg) >> 8);
    TmpReg |= (uint8_t)(Cfg);

    retv = LIS302DLRegWriteByte(RegAddr, TmpReg);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Configure Counter reset mode
    if (Cfg & WUFF_CNT_MASK)
    {
        if((Cfg & WUFF_CNT_MASK) == 0x10000000)
        {
            RegAddr = FF_WU_THS_1;
        }
        else if((Cfg & WUFF_CNT_MASK) == 0x20000000)
        {
            RegAddr = FF_WU_THS_2;
        }
        else
        {
            return (FAILURE);
        }

        retv = LIS302DLRegReadByte(RegAddr, &TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }

        if(Cfg & WUFF_CNT_MODE_MASK)
        {
            TmpReg |= FF_WU_THS_DCRM;
        }
        else
        {
            TmpReg &= (~FF_WU_THS_DCRM);
        }

        retv = LIS302DLRegWriteByte(RegAddr, TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }

    }
    return (SUCCESS);
}


//*****************************************************************************
//
//! \brief Configure LIS302DL.
//!
//! \param Event is the Event(s) to be checked, the paramter can be OR of the
//! following value.
//!
//! \b WUFF1_INT_EVENT_ANY
//! \b WUFF1_INT_EVENT_ZH
//! \b WUFF1_INT_EVENT_ZL
//! \b WUFF1_INT_EVENT_YH
//! \b WUFF1_INT_EVENT_YL
//! \b WUFF1_INT_EVENT_XH
//! \b WUFF1_INT_EVENT_XL
//! \b
//! \b WUFF2_INT_EVENT_ANY
//! \b WUFF2_INT_EVENT_ZH
//! \b WUFF2_INT_EVENT_ZL
//! \b WUFF2_INT_EVENT_YH
//! \b WUFF2_INT_EVENT_YL
//! \b WUFF2_INT_EVENT_XH
//! \b WUFF2_INT_EVENT_XL
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or \b FAILURE.  when checked event occured and there
//! is no error, then return \b SUCCESS.  others return \b FAILURE.
//
//*****************************************************************************
Result LIS302DLWUFFEventCheck(uint32_t Event)
{
    Result    retv     =   SUCCESS;
    uint8_t   TmpReg   =   0;
    uint8_t   RegAddr  =   0;

    ASSERT((Event & (~WUFF_INT_EVENT_MASK)) == 0);

    if(Event & WUFF_INT_MASK)
    {
        RegAddr = FF_WU_SRC_2;
    }
    else
    {
        RegAddr = FF_WU_SRC_1;
    }

    retv = LIS302DLRegReadByte(RegAddr, &TmpReg);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Check the result
    if((TmpReg & (uint8_t)Event) != 0)
    {
        return (SUCCESS);
    }
    else
    {
        return (FAILURE);
    }
}

//*****************************************************************************
//
//! \brief Set Wake-up/Free-Free value.
//!
//! \param ID is WU_FF Module ID, the paramter can be one of the
//! following value.  \b WUFF_ID_1 , \b WUFF_ID_2.
//!
//! \param ThresHold is threshold value. this value must be <= 0x7F.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result LIS302DLWUFFThresHoldSet(uint8_t ID, uint8_t ThresHold)
{
    Result    retv     =   SUCCESS;
    uint8_t   TmpReg   =   0;
    uint8_t   RegAddr  =   0;

    ASSERT((ID == WUFF_ID_1) || (ID == WUFF_ID_2));
    ASSERT(ThresHold <= 0x7F);

    if(ID == WUFF_ID_1)
    {
        RegAddr = FF_WU_THS_1;
    }
    else
    {
        RegAddr = FF_WU_THS_2;
    }

    retv = LIS302DLRegReadByte(RegAddr, &TmpReg);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    if(TmpReg & FF_WU_THS_DCRM)
    {
        ThresHold |= (uint8_t)FF_WU_THS_DCRM;
    }
    else
    {
        ThresHold &= (uint8_t)(~FF_WU_THS_DCRM);
    }

    //Check the result
    retv = LIS302DLRegWriteByte(RegAddr, ThresHold);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Set duration value.
//!
//! \param ID is WU_FF Module ID, the paramter can be one of the
//! following value.  \b WUFF_ID_1 , \b WUFF_ID_2.
//!
//! \param DurValue is duration value you want to set.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//*****************************************************************************
Result LIS302DLWUFFDurValueSet(uint8_t ID, uint8_t DurValue)
{
    Result    retv     =   SUCCESS;
    uint8_t   RegAddr  =   0;

    ASSERT((ID == WUFF_ID_1) || (ID == WUFF_ID_2));

    if(ID == WUFF_ID_1)
    {
        RegAddr = FF_WU_DURATION_1;
    }
    else
    {
        RegAddr = FF_WU_DURATION_2;
    }

    //Check the result
    retv = LIS302DLRegWriteByte(RegAddr, DurValue);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return (SUCCESS);
}


//*****************************************************************************
//
//! \brief Configure LIS302DL Click function.
//!  you can use this function to configure LIS302DL Click function.
//!
//! \param Cfg the paramter can be OR of the following value.
//!
//! \b CLK_INT_REQ_LATCH_EN
//! \b CLK_INT_DBL_Z_EN
//! \b CLK_INT_SIG_Z_EN
//! \b CLK_INT_DBL_Y_EN
//! \b CLK_INT_SIG_Y_EN
//! \b CLK_INT_DBL_X_EN
//! \b CLK_INT_SIG_X_EN
//!
//! \b CLK_INT_REQ_LATCH_DIS
//! \b CLK_INT_DBL_Z_DIS
//! \b CLK_INT_SIG_Z_DIS
//! \b CLK_INT_DBL_Y_DIS
//! \b CLK_INT_SIG_Y_DIS
//! \b CLK_INT_DBL_X_DIS
//! \b CLK_INT_SIG_X_DIS
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result LIS302DLClickCfg(uint32_t Cfg)
{
    Result    retv     =   SUCCESS;
    uint8_t   TmpReg   =   0;

    ASSERT((Cfg & (~CLK_INT_MASK)) == 0);

    //Read click register value
    retv = LIS302DLRegReadByte(CLICK_CFG, &TmpReg);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    TmpReg &= (uint8_t) ((~Cfg) >> 8);
    TmpReg |= (uint8_t)(Cfg);

    retv = LIS302DLRegWriteByte(CLICK_CFG, TmpReg);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Configure LIS302DL Click Event Status.
//!
//! \param Event is the Event(s) to be checked, the paramter can be OR of the
//! following value.
//!
//! \b CLICK_EVENT_ANY
//! \b CLICK_EVENT_SIG_X
//! \b CLICK_EVENT_DBL_X
//! \b CLICK_EVENT_SIG_Y
//! \b CLICK_EVENT_DBL_Y
//! \b CLICK_EVENT_SIG_Z
//! \b CLICK_EVENT_DBL_Z
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or \b FAILURE.  when checked event occured and there
//! is no error, then return \b SUCCESS.  others return \b FAILURE.
//
//*****************************************************************************
Result LIS302DLClickEventCheck(uint8_t Event)
{
    Result    retv     =   SUCCESS;
    uint8_t   TmpReg   =   0;

    ASSERT((Event & (~CLICK_EVENT_MASK)) == 0);

    retv = LIS302DLRegReadByte(CLICK_SRC, &TmpReg);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    //Check the result
    if((TmpReg & Event) != 0)
    {
        return (SUCCESS);
    }
    else
    {
        return (FAILURE);
    }
}

//*****************************************************************************
//
//! \brief Set Wake-up/Free-Free value.
//!
//! \param ThresHold is threshold value. this value can be OR of the following
//! value.
//!
//! \b THRESHOLD_RESET_ALL
//! \b
//! \b THRESHOLD_X_0_5_G
//! \b THRESHOLD_X_1_0_G
//! \b THRESHOLD_X_1_5_G
//! \b THRESHOLD_X_2_0_G
//! \b THRESHOLD_X_2_5_G
//! \b THRESHOLD_X_3_0_G
//! \b THRESHOLD_X_3_5_G
//! \b THRESHOLD_X_4_0_G
//! \b THRESHOLD_X_4_5_G
//! \b THRESHOLD_X_5_0_G
//! \b THRESHOLD_X_5_5_G
//! \b THRESHOLD_X_6_0_G
//! \b THRESHOLD_X_6_5_G
//! \b THRESHOLD_X_7_0_G
//! \b THRESHOLD_X_7_5_G
//! \b
//! \b THRESHOLD_Y_0_5_G
//! \b THRESHOLD_Y_1_0_G
//! \b THRESHOLD_Y_1_5_G
//! \b THRESHOLD_Y_2_0_G
//! \b THRESHOLD_Y_2_5_G
//! \b THRESHOLD_Y_3_0_G
//! \b THRESHOLD_Y_3_5_G
//! \b THRESHOLD_Y_4_0_G
//! \b THRESHOLD_Y_4_5_G
//! \b THRESHOLD_Y_5_0_G
//! \b THRESHOLD_Y_5_5_G
//! \b THRESHOLD_Y_6_0_G
//! \b THRESHOLD_Y_6_5_G
//! \b THRESHOLD_Y_7_0_G
//! \b THRESHOLD_Y_7_5_G
//! \b
//! \b THRESHOLD_Z_0_5_G
//! \b THRESHOLD_Z_1_0_G
//! \b THRESHOLD_Z_1_5_G
//! \b THRESHOLD_Z_2_0_G
//! \b THRESHOLD_Z_2_5_G
//! \b THRESHOLD_Z_3_0_G
//! \b THRESHOLD_Z_3_5_G
//! \b THRESHOLD_Z_4_0_G
//! \b THRESHOLD_Z_4_5_G
//! \b THRESHOLD_Z_5_0_G
//! \b THRESHOLD_Z_5_5_G
//! \b THRESHOLD_Z_6_0_G
//! \b THRESHOLD_Z_6_5_G
//! \b THRESHOLD_Z_7_0_G
//! \b THRESHOLD_Z_7_5_G
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result LIS302DLClickThresholdSet(uint32_t ThresHold)
{
    Result    retv     =   SUCCESS;
    uint8_t   TmpReg   =   0;

    ASSERT((ThresHold & 0xFFFFF000) == 0);

    if(ThresHold == THRESHOLD_RESET_ALL)
    {
        //Reset X Y axis value to 0
        retv = LIS302DLRegReadByte(CLICK_THSY_X, &TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }

        //Modify
        TmpReg = 0;

        //Write back and check the value
        retv = LIS302DLRegWriteByte(CLICK_THSY_X, TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }

        //Reset Z axis value to 0
        retv = LIS302DLRegReadByte(CLICK_THSZ, &TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }

        //Modify
        TmpReg = 0;

        //Write back and check the value
        retv = LIS302DLRegWriteByte(CLICK_THSZ, TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }

        return (SUCCESS);
    }

    //Config X axis ClickThreshold value
    //Read->modify->Write->Check Write
    if(ThresHold & THRESHOLD_X_MASK)
    {
        //Read the origin value
        retv = LIS302DLRegReadByte(CLICK_THSY_X, &TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }

        //Modify
        TmpReg &= (uint8_t)(~THRESHOLD_X_MASK);
        TmpReg |= (uint8_t)(ThresHold & THRESHOLD_X_MASK);

        //Write back and check the value
        retv = LIS302DLRegWriteByte(CLICK_THSY_X, TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }
    }

    //Config Y axis ClickThreshold value
    //Read->modify->Write->Check Write
    if(ThresHold & THRESHOLD_Y_MASK)
    {
        //Read the origin value
        retv = LIS302DLRegReadByte(CLICK_THSY_X, &TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }

        //Modify
        TmpReg &= (uint8_t)(~THRESHOLD_Y_MASK);
        TmpReg |= (uint8_t)(ThresHold & THRESHOLD_Y_MASK);

        //Write back and check the value
        retv = LIS302DLRegWriteByte(CLICK_THSY_X, TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }
    }

    //Config Z axis ClickThreshold value
    //Read->modify->Write->Check Write
    if(ThresHold & THRESHOLD_Z_MASK)
    {
        //Read the origin value
        retv = LIS302DLRegReadByte(CLICK_THSZ, &TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }

        //Modify
        TmpReg &= (uint8_t)(~(THRESHOLD_Z_MASK >> 8));
        TmpReg |= (uint8_t)((ThresHold & THRESHOLD_Z_MASK) >> 8);

        //Write back and check the value
        retv = LIS302DLRegWriteByte(CLICK_THSZ, TmpReg);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }
    }

    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Set Click time limit value.
//! you can use this function to set click time limit value.
//!
//! \param TimeLimit is TimeLimit value. this value must be <= 0xFF.
//! From 0 to 127.5 msec with step of 0.5 msec, set TimeLimit to 0 indicated 0
//! msec, set TimeLimit to 255 indicated 127.5 msec.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result LIS302DLClickTimeLimitSet(uint8_t TimeLimit)
{
    Result    retv     =   SUCCESS;

    retv = LIS302DLRegWriteByte(CLICK_TiMELIMIT, TimeLimit);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Set Click Latency value.
//! you can use this function to set click Latency value.
//!
//! \param Latency is Latency value. this value must be <= 0xFF.
//! From 0 to 255 msec with step of 1 msec, set Latency to 0 indicated 0
//! msec, set Latency to 255 indicated 255 msec.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result LIS302DLClickLatencySet(uint8_t Latency)
{
    Result retv = SUCCESS;

    retv = LIS302DLRegWriteByte(CLICK_LATENCY, Latency);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return (SUCCESS);
}


//*****************************************************************************
//
//! \brief Set Click Window value.
//! you can use this function to set click Window value.
//!
//! \param Window is Window value. this value must be <= 0xFF.
//! From 0 to 255 msec with step of 1 msec, set Window to 0 indicated 0
//! msec, set Window to 255 indicated 255 msec.
//
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result LIS302DLClickWindowSet(uint8_t Window)
{
    Result retv = SUCCESS;

    retv = LIS302DLRegWriteByte(CLICK_WINDOW, Window);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return (SUCCESS);
}

