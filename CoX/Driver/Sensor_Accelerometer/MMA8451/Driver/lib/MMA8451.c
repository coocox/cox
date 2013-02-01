//*****************************************************************************
//
//! \file MMA8451.c
//! \brief the Accelerometer MMA8451 Driver.
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

#include "MMA8451.h"

#define I2C_TRAN_END            1
#define I2C_TRAN_NOT_END        0


//Register defalut value
typedef struct RegInfo
{
    uint8_t Addr;
    uint8_t Val;
} REG_INFO;

static REG_INFO MMA8451_Regs[] = 
{
    {0x09,0x00},
    {0x0A,0x00},
    {0x0E,0x00},
    {0x0F,0x00},
    {0x11,0x80},
    {0x12,0x00},
    {0x13,0x44},
    {0x14,0x84},
    {0x15,0x00},
    {0x17,0x00},
    {0x18,0x00},
    {0x1D,0x00},
    {0x1F,0x00},
    {0x20,0x00},
    {0x21,0x00},
    {0x23,0x00},
    {0x24,0x00},
    {0x25,0x00},
    {0x26,0x00},
    {0x27,0x00},
    {0x28,0x00},
    {0x29,0x00},
    {0x2A,0x00},
    {0x2B,0x00},
    {0x2C,0x00},
    {0x2D,0x00},
    {0x2E,0x00},
    {0x2F,0x00},
    {0x30,0x00},
    {0x31,0x00},

};

static int RegsLen = sizeof(MMA8451_Regs)/sizeof(REG_INFO);

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

    xSysCtlPeripheralEnable(MMA8451_I2C_GPIO);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

    //
    // Enable the I2C which is connected with MMA8451
    //
    xSysCtlPeripheralEnable2(MMA8451_PIN_I2C_PORT);

    //
    // Set MMA8451_PIN_I2C_SCK as I2C SCK Pin
    //
    xSPinTypeI2C(MMA8451_I2C_SCK, MMA8451_PIN_I2C_SCK);

    //
    // Set MMA8451_PIN_I2C_SDA as I2C SDA Pin
    //
    xSPinTypeI2C(MMA8451_I2C_SDA, MMA8451_PIN_I2C_SDA);

    //
    // I2C enable
    //
    xI2CMasterEnable(MMA8451_PIN_I2C_PORT);

    //
    // Initializes the I2C Master block.
    //
    xI2CMasterInit(MMA8451_PIN_I2C_PORT, I2CInitClkRate);

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Write one byte to special register
//!
//! \param RegAddr specifies the target register address.
//! \param Data is the data written to target register.
//!
//!  This function is to write one byte to MMA8451 register,one byte will be
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
    retv = xI2CMasterWriteS1(MMA8451_PIN_I2C_PORT, MMA8451_I2C_ADDR,
            RegAddr, I2C_TRAN_NOT_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    // Send the wanted data to I2C bus
    // then Send STOP signal to release I2C bus
    retv = xI2CMasterWriteS2(MMA8451_PIN_I2C_PORT, Data, I2C_TRAN_END);
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
//!  This function is to read one byte from MMA8451 register,
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
    retv = xI2CMasterWriteS1(MMA8451_PIN_I2C_PORT, MMA8451_I2C_ADDR,
            RegAddr, I2C_TRAN_NOT_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    // Send restart signal then receive one byte from I2C bus
    // at last Send STOP signal to release I2C bus
    retv = xI2CMasterReadS1(MMA8451_PIN_I2C_PORT, MMA8451_I2C_ADDR,
            DataRecvBuf, I2C_TRAN_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Write one byte to special register
//!
//! \param RegAddr specifies the target register address.
//! \param Data is the data written to target register.
//!
//!  This function is to write one byte to MMA8451 register,one byte will be
//!  writen in appointed address.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA8451_RegWriteByte(uint8_t RegAddr, uint8_t Data)
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
//!  This function is to read one byte from MMA8451 register,
//!  and write the data to the special address.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA8451_RegReadByte(uint8_t RegAddr, uint8_t * DataRecvBuf)
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
//! \brief Init The Accelerometer Module.
//!
//! \param none.
//!
//!  This function is to initialize the accelerometer communication port and
//!  reset register to default value.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//***************************************************************************** 
Result MMA8451_Init(void)
{
    Result retv = SUCCESS;
    uint8_t i   = 0;

    //After power-on, your need wait module to work.
    SysCtlDelay(0xFFFF);

    //Initialize I2C Port.
    retv = _I2CComPortInit();
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }
    SysCtlDelay(0xFFFF);

    //Set Register to default value.
    for (i = 0; i < RegsLen; i++)
    {
        retv = MMA8451_RegWriteByte(MMA8451_Regs[i].Addr, MMA8451_Regs[i].Val);
        if(retv != SUCCESS)
        {
            return (FAILURE);
        }
        SysCtlDelay(0xFF);
    }

    //Initialize successfully, you can use accelerometer now.
    return (SUCCESS);
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
Result MMA8451_GetID(uint8_t * ID)
{
    return (MMA8451_RegReadByte(MMA8451_REG_WHO_AM_I, ID));
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
Result MMA8451_ReadAccData_8(uint8_t Axis, int8_t * DataRecvBuf)
{
    uint8_t  RegAddr = 0;
    Result   retv    = SUCCESS;

    //Check param vaild
    ASSERT ((Axis == AXIS_X) || (Axis == AXIS_Y) || (Axis == AXIS_Z));
    ASSERT (DataRecvBuf != NULL);

    //Get Offset Register Address
    switch(Axis)
    {
        case AXIS_X:
            {
                RegAddr = MMA8451_REG_OUT_X_MSB;
                break;
            }

        case AXIS_Y:
            {
                RegAddr = MMA8451_REG_OUT_Y_MSB;
                break;
            }

        case AXIS_Z:
            {
                RegAddr = MMA8451_REG_OUT_Z_MSB;
                break;
            }
        default:
            {
                return(FAILURE);
            }
    }

    //Read MSB 8 bit
    retv = MMA8451_RegReadByte(RegAddr, (uint8_t *)DataRecvBuf);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Read accelerometer 14-bit data.
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
Result MMA8451_ReadAccData_14(uint8_t Axis, int16_t * DataRecvBuf)
{
    uint8_t  RegAddr = 0;
    uint8_t  TmpVal  = 0;
    Result   retv    = SUCCESS;

    //Check param vaild
    ASSERT ((Axis == AXIS_X) || (Axis == AXIS_Y) || (Axis == AXIS_Z));
    ASSERT (DataRecvBuf != NULL);

    //Get Offset Register Address
    switch(Axis)
    {
        case AXIS_X:
            {
                RegAddr = MMA8451_REG_OUT_X_MSB;
                break;
            }

        case AXIS_Y:
            {
                RegAddr = MMA8451_REG_OUT_Y_MSB;
                break;
            }

        case AXIS_Z:
            {
                RegAddr = MMA8451_REG_OUT_Z_MSB;
                break;
            }
        default:
            {
                return(FAILURE);
            }
    }

    //Clear user's data buffer
    *DataRecvBuf = 0;

    //Read MSB 8 bit
    retv = MMA8451_RegReadByte(RegAddr, &TmpVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }
    //TODO check
    *DataRecvBuf |= ((uint16_t)TmpVal << 8);

    //Read LSB 8 bit
    retv = MMA8451_RegReadByte(RegAddr + 1, &TmpVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }
    *DataRecvBuf |= TmpVal;

    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Check MMA8451 Data status.
//!
//! \param Event is the Event(s) to be checked, the paramter can be \b OR of the
//! following value.
//!
//! \b
//! \b AXIS_XYZ_OW    
//! \b AXIS_X_OW      
//! \b AXIS_Y_OW      
//! \b AXIS_Z_OW    
//! \b AXIS_XYZ_DR    
//! \b AXIS_X_DR      
//! \b AXIS_Y_DR      
//! \b AXIS_Z_DR      
//! \b 
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or \b FAILURE.  when checked event occured and there
//! is no error, then return \b SUCCESS.  others return \b FAILURE.
//
//*****************************************************************************
Result MMA8451_DataStatusCheck(uint8_t Event)
{
    uint8_t  RegVal  = 0;
    Result   retv    = SUCCESS;

    //Get Data status
    retv = MMA8451_RegReadByte(MMA8451_REG_STATUSR, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    //Check user's specifical bit
    if(RegVal & Event)
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
//! \brief Check MMA8451 interrupt status.
//!
//! \param Event is the Event(s) to be checked, the paramter can be \b OR of the
//! following value.
//!
//! \b
//! \b EVENT_ASLP  
//! \b EVENT_FIFO  
//! \b EVENT_TRANS 
//! \b EVENT_LNDPRT
//! \b EVENT_PULSE 
//! \b EVENT_FF_MT 
//! \b EVENT_DRDY  
//! \b 
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or \b FAILURE.  when checked event occured and there
//! is no error, then return \b SUCCESS.  others return \b FAILURE.
//
//*****************************************************************************
Result MMA8451_IntStatusCheck(uint8_t Event)
{
    uint8_t  RegVal  = 0;
    Result   retv    = SUCCESS;

    //Get Data status
    retv = MMA8451_RegReadByte(MMA8451_REG_INT_SOURCE, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    //Check user's specifical bit
    if(RegVal & Event)
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
//! \brief Set Module to \b ACTIVE Mode.
//!
//! \param none.
//!
//! This function is used to set module into \b ACTIVE mode.
//!
//! When Enter into \b ACTIVE (WAKE/SLEEP) mode.
//! 1: I2C communication with MMA8451Q is possible
//! 2: VDD is ON
//! 3: VDDIO = High
//! 4: VDD = High
//! 5: ACTIVE bit is set
//! 6: All blocks are enabled (digital, analog).
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA8451_Active(void)
{
    uint8_t  RegVal  = 0;
    Result   retv    = SUCCESS;

    retv = MMA8451_RegReadByte(MMA8451_REG_CTRL_REG1, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    RegVal |= CTRL_REG1_ACTIVE;

    retv = MMA8451_RegWriteByte(MMA8451_REG_CTRL_REG1, RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Set Module to \b STANDBY Mode.
//!
//! \param none.
//!
//! This function is used to set module into \b STANDBY mode.
//!
//! When Enter into \b STANDBY mode.
//! 1: I2C communication with MMA8451Q is possible
//! 2: VDD is ON
//! 3: VDDIO = High
//! 4: VDD = High
//! 5: ACTIVE bit is cleared
//! 6: Only digital blocks are enabled. 
//! 7: Analog subsystem is disabled.
//! 8: Internal clocks disabled. 
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//***************************************************************************** 
Result MMA8451_Standby(void)
{
    uint8_t  RegVal  = 0;
    Result   retv    = SUCCESS;

    retv = MMA8451_RegReadByte(MMA8451_REG_CTRL_REG1, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    RegVal &= ~CTRL_REG1_ACTIVE;

    retv = MMA8451_RegWriteByte(MMA8451_REG_CTRL_REG1, RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Configure MMA8451 interrupt.
//!
//! \param Cfg the paramter can be \b OR of the following value.
//! more information, please reference Macro define.
//!
//! WAKE_TRANS_EN 
//! WAKE_TRANS_DIS
//! 
//! WAKE_LP_EN    
//! WAKE_LP_DIS   
//! 
//! WAKE_PULSE_EN 
//! WAKE_PULSE_DIS
//! 
//! WAKE_FFMT_EN  
//! WAKE_FFMT_DIS 
//! 
//! ACTIVE_HIGH   
//! ACTIVE_LOW    
//! 
//! PAD_OD        
//! PAD_PP        
//! 
//! INT_ASLP_EN   
//! INT_ASLP_DIS  
//! 
//! INT_FIFO_EN   
//! INT_FIFO_DIS  
//! 
//! INT_TRANS_EN  
//! INT_TRANS_DIS 
//! 
//! INT_LP_EN     
//! INT_LP_DIS    
//! 
//! INT_PULSE_EN  
//! INT_PULSE_DIS 
//! 
//! INT_FFMT_EN   
//! INT_FFMT_DIS  
//! 
//! INT_DRDY_EN   
//! INT_DRDY_DIS  
//! 
//! INT_ASLP_INT1 
//! INT_ASLP_INT2 
//! 
//! INT_FIFO_INT1 
//! INT_FIFO_INT2 
//! 
//! INT_TRANS_INT1
//! INT_TRANS_INT2
//! 
//! INT_LP_INT1   
//! INT_LP_INT2   
//! 
//! INT_PULSE_INT1
//! INT_PULSE_INT2
//! 
//! INT_FFMT_INT1 
//! INT_FFMT_INT2 
//! 
//! INT_DRDY_INT1 
//! INT_DRDY_INT2 
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA8451_IntCfg(uint64_t Cfg)
{
    uint8_t  RegVal  = 0;
    Result   retv    = SUCCESS;

    //Configure control register 3.
    if(Cfg & CTRL_REG3_MASK)
    {
        retv = MMA8451_RegReadByte(MMA8451_REG_CTRL_REG3, &RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }

        RegVal &= (uint8_t) ~(Cfg >> 8);
        RegVal |= (uint8_t)  (Cfg >> 0);

        retv = MMA8451_RegWriteByte(MMA8451_REG_CTRL_REG3, RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }
    }

    //Configure control register 4.
    if(Cfg & CTRL_REG4_MASK)
    {
        retv = MMA8451_RegReadByte(MMA8451_REG_CTRL_REG4, &RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }

        RegVal &= (uint8_t) ~(Cfg >> 24);
        RegVal |= (uint8_t)  (Cfg >> 16);

        retv = MMA8451_RegWriteByte(MMA8451_REG_CTRL_REG4, RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }
    }

    //Configure control register 5.
    if(Cfg & CTRL_REG5_MASK)
    {
        retv = MMA8451_RegReadByte(MMA8451_REG_CTRL_REG5, &RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }

        RegVal &= (uint8_t) ~(Cfg >> 40);
        RegVal |= (uint8_t)  (Cfg >> 32);

        retv = MMA8451_RegWriteByte(MMA8451_REG_CTRL_REG5, RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }
    }

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Configure MMA8451.
//!
//! \param Cfg the paramter can be \b OR of the following value.
//! more information, please reference Macro define.
//!
//! SLEEP_RATE_50_HZ        
//! SLEEP_RATE_12_5_HZ      
//! SLEEP_RATE_6_25_HZ      
//! SLEEP_RATE_1_56_HZ      
//! 
//! NORMAL_RATE_800_HZ      
//! NORMAL_RATE_400_HZ      
//! NORMAL_RATE_200_HZ      
//! NORMAL_RATE_100_HZ      
//! NORMAL_RATE_50_HZ       
//! NORMAL_RATE_12_5_HZ     
//! NORMAL_RATE_6_25_HZ     
//! NORMAL_RATE_1_56_HZ     
//! 
//! LOW_NOISE_EN            
//! LOW_NOISE_DIS           
//! 
//! FAST_READ_EN            
//! FAST_READ_DIS           
//! 
//! SELFTEST_EN             
//! SELFTEST_DIS            
//! 
//! SLEEP_MODE_NOR          
//! SLEEP_MODE_LNLP         
//! SLEEP_MODE_HR           
//! SLEEP_MODE_LP           
//! 
//! AUTO_SLEEP_EN           
//! AUTO_SLEEP_DIS          
//! 
//! ACTIVE_MODE_NOR         
//! ACTIVE_MODE_LNLP        
//! ACTIVE_MODE_HR          
//! ACTIVE_MODE_LP          
//! 
//! HPF_EN                  
//! HPF_DIS                 
//! RANGE_2G                
//! RANGE_4G                
//! RANGE_8G                
//! 
//! HPF_CUTOFF_8X           
//! HPF_CUTOFF_4X           
//! HPF_CUTOFF_2X           
//! HPF_CUTOFF_1X           
//! 
//! PULSE_HPF_EN            
//! PULSE_HPF_DIS           
//! 
//! PULSE_LPF_EN            
//! PULSE_LPF_DIS           
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//***************************************************************************** 
Result MMA8451_Cfg(uint64_t Cfg)
{
    uint8_t  RegVal  = 0;
    Result   retv    = SUCCESS;

    //Configure control register 1.
    if(Cfg & REG_1_MASK)
    {
        retv = MMA8451_RegReadByte(MMA8451_REG_CTRL_REG1, &RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }

        if(Cfg & SLEEP_RATE_MASK)
        {
            RegVal &= ~CTRL_REG1_ASLP_RATE_M;
        }

        if(Cfg & NORMAL_RATE_MASK)
        {
            RegVal &= ~CTRL_REG1_DR_M;
        }

        RegVal &= (uint8_t) ~(Cfg >> 24);
        RegVal |= (uint8_t)  (Cfg >> 16);

        retv = MMA8451_RegWriteByte(MMA8451_REG_CTRL_REG1, RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }
    }

    //Configure control register 2.
    if(Cfg & REG_2_MASK)
    {
        retv = MMA8451_RegReadByte(MMA8451_REG_CTRL_REG2, &RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }

        if(Cfg & SLEEP_MODE_MASK)
        {
            RegVal &= ~CTRL_REG2_SMODS_M;
        }

        if(Cfg & ACTIVE_MODE_MASK)
        {
            RegVal &= ~CTRL_REG2_MODS_M;
        }

        RegVal &= (uint8_t) ~(Cfg >> 8);
        RegVal |= (uint8_t)  (Cfg >> 0);

        retv = MMA8451_RegWriteByte(MMA8451_REG_CTRL_REG2, RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }
    }

    //Configure data control register.
    if(Cfg & DATA_CFG_1_MASK)
    {
        retv = MMA8451_RegReadByte(MMA8451_REG_XYZ_DATA_CFG, &RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }

        if(Cfg & RANGE_MASK)
        {
            RegVal &= ~XYZ_DATA_CFG_FS_M;
        }

        RegVal &= (uint8_t) ~(Cfg >> 40);
        RegVal |= (uint8_t)  (Cfg >> 32);

        retv = MMA8451_RegWriteByte(MMA8451_REG_XYZ_DATA_CFG, RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }
    }

    //Configure high pass filter control register.
    if(Cfg & HPF_CFG_MASK)
    {
        retv = MMA8451_RegReadByte(MMA8451_REG_HP_FILTER_CUTOFF, &RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }

        RegVal &= (uint8_t) ~(Cfg >> 56);
        RegVal |= (uint8_t)  (Cfg >> 48);

        retv = MMA8451_RegWriteByte(MMA8451_REG_HP_FILTER_CUTOFF, RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }
    }

    return(SUCCESS);
}



//*****************************************************************************
//
//! \brief Configure MMA8451 Portrait/Landscape mode.
//!
//! \param Cfg the paramter can be \b OR of the following value.
//! more information, please reference Macro define.
//!
//!  PL_CNT_DEC                   
//!  PL_CNT_RST                   
//!                               
//!  PL_EN                        
//!  PL_DIS                       
//!
//! \param Angle the paramter can be \b OR of the following value.
//!  more information, please reference Macro define.                            
//!
//!  PL_BKFR_65                   
//!  PL_BKFR_70                   
//!  PL_BKFR_75                   
//!  PL_BKFR_80                   
//!                               
//!  PL_ZLOCK_14                  
//!  PL_ZLOCK_18                  
//!  PL_ZLOCK_21                  
//!  PL_ZLOCK_25                  
//!  PL_ZLOCK_29                  
//!  PL_ZLOCK_33                  
//!  PL_ZLOCK_37                  
//!  PL_ZLOCK_42                  
//!                               
//!  PL_THRESHOLD_15              
//!  PL_THRESHOLD_20              
//!  PL_THRESHOLD_30              
//!  PL_THRESHOLD_35              
//!  PL_THRESHOLD_40              
//!  PL_THRESHOLD_45              
//!  PL_THRESHOLD_55              
//!  PL_THRESHOLD_60              
//!  PL_THRESHOLD_70              
//!  PL_THRESHOLD_75              
//!                               
//!  PL_HYS_0                     
//!  PL_HYS_4                     
//!  PL_HYS_7                     
//!  PL_HYS_11                    
//!  PL_HYS_14                    
//!  PL_HYS_17                    
//!  PL_HYS_21                    
//!  PL_HYS_24                    
//!
//! \param Cnt is Portrait/Landscape Debounce Counter.  0 <= Cnt <= 255
//! 
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA8451_PLCfg(uint32_t Cfg, uint32_t Angle, uint8_t Cnt)
{
    uint8_t  RegVal = 0;
    Result   retv   = SUCCESS;

    //Configure PL control register.
    retv = MMA8451_RegReadByte(MMA8451_REG_PL_CFG, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    RegVal &= (uint8_t) ~(Cfg >> 8);
    RegVal |= (uint8_t)  (Cfg >> 0);

    retv = MMA8451_RegWriteByte(MMA8451_REG_PL_CFG, RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    //Configure Back/Front and Z Compensation Register
    if(Angle & PL_BK_CMP_MASK)
    {
        retv = MMA8451_RegReadByte(MMA8451_REG_PL_BF_ZCOMP, &RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }

        RegVal &= (uint8_t) ~(Angle >> 8);
        RegVal |= (uint8_t)  (Angle >> 0);

        retv = MMA8451_RegWriteByte(MMA8451_REG_PL_BF_ZCOMP, RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }
    }

    //Configure Portrait/Landscape Threshold and Hysteresis Register
    if(Angle & PL_THS_MASK)
    {
        retv = MMA8451_RegReadByte(MMA8451_REG_PL_THS_REG, &RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }

        RegVal &= (uint8_t) ~(Angle >> 24);
        RegVal |= (uint8_t)  (Angle >> 16);

        retv = MMA8451_RegWriteByte(MMA8451_REG_PL_THS_REG, RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }
    }

    //Configure  Portrait/Landscape Debounce Counter register.
    retv = MMA8451_RegWriteByte(MMA8451_REG_PL_COUNT, Cnt);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    return(SUCCESS);
}



//*****************************************************************************
//
//! \brief Check MMA8451 FreeFall/MotionDetect Status.
//!
//! \param Event is the Event(s) to be checked, the paramter can be \b OR of the
//! following value.
//!
//! \b
//! \b FFMT_EA                 
//! \b FFMT_MOTION_Z           
//! \b FFMT_POLARITY_Z         
//! \b FFMT_MOTION_Y           
//! \b FFMT_POLARITY_Y         
//! \b FFMT_MOTION_X           
//! \b FFMT_POLARITY_X         
//! \b 
//!
//! \note if you want to decide the Portrait of axis, you can use FFMT_POLARITY_n(XYZ).
//! Function return \b FAILURE means Positive, return \b SUCCESS means Negative.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or \b FAILURE.  when checked event occured and there
//! is no error, then return \b SUCCESS.  others return \b FAILURE.
//
//*****************************************************************************
Result MMA8451_FFMTStatusCheck(uint8_t Event)
{
    uint8_t  RegVal  = 0;
    Result   retv    = SUCCESS;

    //Get Data status
    retv = MMA8451_RegReadByte(MMA8451_REG_FF_MT_SRC, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    //Check user's specifical bit
    if(RegVal & Event)
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
//! \brief Configure MMA8451 FreeFall/MotionDetect mode.
//!
//! \param Cfg the paramter can be \b OR of the following value.
//! more information, please reference Macro define.
//!
//!  FFMT_INT_LATCH_EN                
//!  FFMT_INT_LATCH_DIS               
//!  FFMT_FREEFALL                    
//!  FFMT_MOTION                      
//!  FFMT_INT_Z_EN                    
//!  FFMT_INT_Y_EN                    
//!  FFMT_INT_X_EN                    
//!  FFMT_INT_Z_DIS                   
//!  FFMT_INT_Y_DIS                   
//!  FFMT_INT_X_DIS                   
//!  FFMT_CNT_DEC                     
//!  FFMT_CNT_RST                     
//!
//! \param ThresHold is  Freefall and Motion Threshold Register.  0 <= Cnt <= 127
//!
//!  The threshold resolution is 0.063g/LSB and the threshold regist er has a range
//!  of 0 to 127 counts. The maximum range is to 8g. Note that even when the full
//!  scale value is set to 2g or 4g the motion detects up to 8g. If the Low Noise
//!  bit is set in Register 0x2A then the maximum threshold will be limited to 4g
//!  regardless of the full scale range
//!
//! \param Cnt is FreeFall/MotionDetect Debounce Counter.  0 <= Cnt <= 255
//! 
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA8451_FFMTCfg(uint32_t Cfg, uint8_t ThresHold, uint8_t Cnt)
{
    uint8_t  RegVal  = 0;
    Result   retv    = SUCCESS;

    if(Cfg & FFMT_CFG_MASK)
    {
        retv = MMA8451_RegReadByte(MMA8451_REG_FF_MT_CFG, &RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }

        RegVal &= (uint8_t) ~(Cfg >> 8);
        RegVal |= (uint8_t)  (Cfg >> 0);

        retv = MMA8451_RegWriteByte(MMA8451_REG_FF_MT_CFG, RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }
    }

    retv = MMA8451_RegReadByte(MMA8451_REG_FF_MT_THS, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    RegVal &= ~FF_MT_THS_THS_M;
    RegVal |= ThresHold;

    if(Cfg & FFTS_CNT_MASK)
    {
        RegVal &= (uint8_t) ~(Cfg >> 24);
        RegVal |= (uint8_t)  (Cfg >> 16);
    }

    retv = MMA8451_RegWriteByte(MMA8451_REG_FF_MT_THS, RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    retv = MMA8451_RegWriteByte(MMA8451_REG_FF_MT_COUNT, Cnt);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    return(SUCCESS);
}


//*****************************************************************************
//
//! \brief Check MMA8451 Transient Status.
//!
//! \param Event is the Event(s) to be checked, the paramter can be \b OR of the
//! following value.
//!
//! \b
//! \b TS_EA                
//! \b TS_EVENT_Z           
//! \b TS_POLARITY_Z        
//! \b TS_EVENT_Y           
//! \b TS_POLARITY_Y
//! \b TS_EVENT_X           
//! \b TS_POLARITY_X
//! \b 
//!
//! \note If you want to decide the Portrait of axis, you can use TS_POLARITY_n(XYZ).
//! Function return \b FAILURE means Positive, return \b SUCCESS means Negative.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or \b FAILURE.  when checked event occured and there
//! is no error, then return \b SUCCESS.  others return \b FAILURE.
//
//*****************************************************************************  
Result MMA8451_TSStatusCheck(uint8_t Event)
{
    uint8_t  RegVal  = 0;
    Result   retv    = SUCCESS;

    //Get Data status
    retv = MMA8451_RegReadByte(MMA8451_REG_TRANSIENT_SRC, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    //Check user's specifical bit
    if(RegVal & Event)
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
//! \brief Configure MMA8451 Transient mode.
//!
//! \param Cfg the paramter can be \b OR of the following value.
//! more information, please reference Macro define.
//!
//!  TS_INT_LATCH_EN          
//!  TS_INT_LATCH_DIS         
//!  TS_X_EN                  
//!  TS_Y_EN                  
//!  TS_Z_EN                  
//!  TS_X_DIS                 
//!  TS_Y_DIS                 
//!  TS_Z_DIS                 
//!  TS_HPF_EN                
//!  TS_HPF_DIS               
//!                           
//!  TS_CNT_DEC               
//!  TS_CNT_RST               
//!
//! \param ThresHold is Transient Threshold value.  0 <= Cnt <= 127
//!
//! The threshold is a 7-bit unsigned  number, 0.063g/LSB. The maximum
//! threshold is 8g. Even if the part is set to full scale at 2g or 4g this
//! function will still operate up to 8g. If th e Low Noise bit is set in Register
//! 0x2A the maximum threshold to be reached is 4g
//!
//! \param Cnt is Transient Debounce Counter.  0 <= Cnt <= 255
//! 
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//***************************************************************************** 
Result MMA8451_TransCfg(uint32_t Cfg, uint8_t ThresHold, uint8_t Cnt)
{
    uint8_t  RegVal  = 0;
    Result   retv    = SUCCESS;

    if(Cfg & TS_CFG_MASK)
    {
        retv = MMA8451_RegReadByte(MMA8451_REG_TRANSIENT_CFG, &RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }

        RegVal &= (uint8_t) ~(Cfg >> 8);
        RegVal |= (uint8_t)  (Cfg >> 0);

        retv = MMA8451_RegWriteByte(MMA8451_REG_TRANSIENT_CFG, RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }
    }

    //Set ThresHold value.
    //Note: ThresHold is 7-bit unsigned char type.
    retv = MMA8451_RegReadByte(MMA8451_REG_TRANSIENT_THS, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    RegVal &= ~TRANSIENT_THS_THS_M;
    RegVal |= ThresHold;

    //Configure Counter Mode, decrement or reset.
    if(Cfg & TS_CNT_MASK)
    {
        RegVal &= (uint8_t) ~(Cfg >> 24);
        RegVal |= (uint8_t)  (Cfg >> 16);
    }

    retv = MMA8451_RegWriteByte(MMA8451_REG_TRANSIENT_THS, RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    //Configure Transient counter value.
    retv = MMA8451_RegWriteByte(MMA8451_REG_TRANSIENT_COUNT, Cnt);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    return(SUCCESS);
}


//*****************************************************************************
//
//! \brief Check MMA8451 Pulse Status.
//!
//! \param Event is the Event(s) to be checked, the paramter can be \b OR of the
//! following value.
//!
//! \b
//! \b PULSE_EA                
//! \b PULSE_EVENT_Z           
//! \b PULSE_EVENT_Y           
//! \b PULSE_EVENT_X           
//! \b PULSE_DOUBLE            
//! \b PULSE_POL_Z             
//! \b PULSE_POL_Y             
//! \b PULSE_POL_X             
//! \b
//!
//! \note If you want to decide the Portrait of axis, you can use
//! PULSE_POLARITY_n(XYZ).
//! Function return \b FAILURE means Positive, return \b SUCCESS means Negative.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or \b FAILURE.  when checked event occured and there
//! is no error, then return \b SUCCESS.  others return \b FAILURE.
//
//*****************************************************************************
Result MMA8451_PulseStatusCheck(uint8_t Event)
{
    uint8_t  RegVal  = 0;
    Result   retv    = SUCCESS;

    //Get Data status
    retv = MMA8451_RegReadByte(MMA8451_REG_PULSE_SRC, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    //Check user's specifical bit
    if(RegVal & Event)
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
//! \brief Configure MMA8451 Pulse mode.
//!
//! \param Cfg the paramter can be \b OR of the following value.
//! more information, please reference Macro define.
//!
//! DP_ABORT_EN             
//! DP_ABORT_DIS            
//! PULSE_INT_LATCH_EN      
//! PULSE_INT_LATCH_DIS     
//! PULSE_SGL_X_EN          
//! PULSE_SGL_Y_EN          
//! PULSE_SGL_Z_EN          
//! PULSE_SGL_X_DIS         
//! PULSE_SGL_Y_DIS         
//! PULSE_SGL_Z_DIS         
//! PULSE_DBL_X_EN          
//! PULSE_DBL_Y_EN          
//! PULSE_DBL_Z_EN          
//! PULSE_DBL_X_DIS         
//! PULSE_DBL_Y_DIS         
//! PULSE_DBL_Z_DIS         
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//***************************************************************************** 
Result MMA8451_PulseCfg(uint32_t Cfg)
{
    uint8_t  RegVal  = 0;
    Result   retv    = SUCCESS;

    retv = MMA8451_RegReadByte(MMA8451_REG_PULSE_CFG, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    RegVal &= (uint8_t) ~(Cfg >> 8);
    RegVal |= (uint8_t)  (Cfg >> 0);

    retv = MMA8451_RegWriteByte(MMA8451_REG_PULSE_CFG, RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Set Pulse ThresHold value.
//!
//! \param Axis is the axis data which you want to read. this paramter can be
//! one of the following value: \b AXIS_X \b AXIS_Y \b AXIS_Z.
//!
//! \param ThresHold is pulse threshold value.
//! The threshold values range from 1 to 127 with steps of 0.63g/LSB at a fixed 8g
//! acceleration range, thus the minimum resolution is always fixed at 0.063g/LSB.
//! If the Low Noise bit in  Register 0x2A is set then the maximum threshold will
//! be 4g. T he PULSE_THSX, PULSE_THSY and PULSE_THSZ registers define the
//! threshold which is used by the system to start the pulse detection procedure.
//! The threshold value is expressed over 7-bits as an unsigned number.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//*****************************************************************************
Result MMA8451_PulseThresHoldSet(uint8_t Axis, uint8_t ThresHold)
{
    uint8_t  RegAddr = 0;
    Result   retv    = SUCCESS;

    //Check param vaild
    ASSERT ((Axis == AXIS_X) || (Axis == AXIS_Y) || (Axis == AXIS_Z));
    ASSERT (ThresHold != NULL);

    //Get Offset Register Address
    switch(Axis)
    {
        case AXIS_X:
            {
                RegAddr = MMA8451_REG_PULSE_THSX;
                ThresHold &= PULSE_THSX_M;
                break;
            }

        case AXIS_Y:
            {
                RegAddr = MMA8451_REG_PULSE_THSY;
                ThresHold &= PULSE_THSY_M;
                break;
            }

        case AXIS_Z:
            {
                RegAddr = MMA8451_REG_PULSE_THSZ;
                ThresHold &= PULSE_THSZ_M;
                break;
            }
        default:
            {
                return(FAILURE);
            }
    }

    retv = MMA8451_RegWriteByte(RegAddr, ThresHold);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    return (SUCCESS);
}


//*****************************************************************************
//
//! \brief Set Pulse Limit value.
//!
//! \param Limit define the maximum time interval that can elapse between the
//!  start of the ! acceleration on the selected axis exceeding the specified
//!  threshold and the end ! when the acceleration on the selected axis must go
//!  below the specified ! threshold to be considered a valid pulse.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA8451_PulseLimitSet(uint8_t Limit)
{
    return (MMA8451_RegWriteByte(MMA8451_REG_PULSE_TMLT, Limit));
}

//*****************************************************************************
//
//! \brief Set Pulse Latency value.
//!
//! \param Latency define the time interval that starts after the first pulse
//!  detection.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//***************************************************************************** 
Result MMA8451_PulseLatencySet(uint8_t Latency)
{
    return (MMA8451_RegWriteByte(MMA8451_REG_PULSE_LTCY, Latency));
}

//*****************************************************************************
//
//! \brief Set Pulse Window value.
//!
//! \param Latency define the time interval that starts after the first pulse
//!  detection.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//***************************************************************************** 
Result MMA8451_PulseWindowSet(uint8_t Window)
{
    return (MMA8451_RegWriteByte(MMA8451_REG_PULSE_WIND, Window));
}


//*****************************************************************************
//
//! \brief Set Auto-WAKE/SLEEP Detection Counter value.
//!
//! \param Cnt defines the minimum duration time to change current ODR value
//!  from DR to  ASLP_RATE.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result MMA8451_SleepCntSet(uint8_t Cnt)
{
    return (MMA8451_RegWriteByte(MMA8451_REG_ASLP_COUNT, Cnt));
}

//*****************************************************************************
//
//! \brief Set User Offset Correction value.
//!
//! \param Axis is the axis data which you want to read. this paramter can be
//! one of the following value: \b AXIS_X \b AXIS_Y \b AXIS_Z.
//!
//! \param OffSet.
//! For more information on how to calibrate the 0g Offset refer to AN4069
//! Offset Calibration Using the MMA8451Q. The 2¡¯s complement offset correction
//! registers values are used to realign the Zero-g position of the X, Y, and
//! Z-axis after device board mount. The resolution of the offset registers is 2
//! mg per LSB. The 2¡¯s complement 8-bit value would result in an offset
//! compensation range (+/-)256 mg.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//***************************************************************************** 
Result MMA8451_OffSetWrite(uint32_t Axis, uint8_t OffSet)
{
    uint8_t  RegAddr = 0;
    Result   retv    = SUCCESS;

    ASSERT ((Axis == AXIS_X) || (Axis == AXIS_Y) || (Axis == AXIS_Z));

    //Get Offset Register Address
    switch(Axis)
    {
        case AXIS_X:
            {
                RegAddr = MMA8451_REG_OFF_X;
                break;
            }

        case AXIS_Y:
            {
                RegAddr = MMA8451_REG_OFF_Y;
                break;
            }

        case AXIS_Z:
            {
                RegAddr = MMA8451_REG_OFF_Z;
                break;
            }
        default:
            {
                return(FAILURE);
            }
    }

    //Write user's value to offset register
    retv = MMA8451_RegWriteByte(RegAddr, OffSet);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    return(SUCCESS);
}

