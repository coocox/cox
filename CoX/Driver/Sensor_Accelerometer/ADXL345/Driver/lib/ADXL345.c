//*****************************************************************************
//
//! \file ADXL345.c
//! \brief the Accelerometer  ADXL345 Driver.
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

#include "ADXL345.h"

#define I2C_TRAN_END            1
#define I2C_TRAN_NOT_END        0


//Register defalut value
typedef struct RegInfo
{
    uint8_t Addr;
    uint8_t Val;
} REG_INFO;

static REG_INFO ADXL345_Regs[] = 
{

    {0x1D,0x00},
    {0x1E,0x00},
    {0x1F,0x00},
    {0x20,0x00},
    {0x21,0x00},
    {0x22,0x00},
    {0x23,0x00},
    {0x24,0x00},
    {0x25,0x00},
    {0x26,0x00},
    {0x27,0x00},
    {0x28,0x00},
    {0x29,0x00},
    {0x2A,0x00},
    {0x2C,0x0A},
    {0x2D,0x00},
    {0x2E,0x00},
    {0x2F,0x00},
    {0x31,0x00},
    {0x38,0x00}, 

};

static uint8_t RegsLen = sizeof(ADXL345_Regs)/sizeof(REG_INFO);

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

    xSysCtlPeripheralEnable(ADXL345_I2C_GPIO);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

    //
    // Enable the I2C which is connected with ADXL345
    //
    xSysCtlPeripheralEnable2(ADXL345_PIN_I2C_PORT);

    //
    // Set ADXL345_PIN_I2C_SCK as I2C SCK Pin
    //
    xSPinTypeI2C(ADXL345_I2C_SCK, ADXL345_PIN_I2C_SCK);

    //
    // Set ADXL345_PIN_I2C_SDA as I2C SDA Pin
    //
    xSPinTypeI2C(ADXL345_I2C_SDA, ADXL345_PIN_I2C_SDA);

    //
    // I2C enable
    //
    xI2CMasterEnable(ADXL345_PIN_I2C_PORT);

    //
    // Initializes the I2C Master block.
    //
    xI2CMasterInit(ADXL345_PIN_I2C_PORT, I2CInitClkRate);

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Write one byte to special register
//!
//! \param RegAddr specifies the target register address.
//! \param Data is the data written to target register.
//!
//!  This function is to write one byte to ADXL345 register,one byte will be
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
    retv = xI2CMasterWriteS1(ADXL345_PIN_I2C_PORT, ADXL345_I2C_ADDR,
            RegAddr, I2C_TRAN_NOT_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    // Send the wanted data to I2C bus
    // then Send STOP signal to release I2C bus
    retv = xI2CMasterWriteS2(ADXL345_PIN_I2C_PORT, Data, I2C_TRAN_END);
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
//!  This function is to read one byte from ADXL345 register,
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
    retv = xI2CMasterWriteS1(ADXL345_PIN_I2C_PORT, ADXL345_I2C_ADDR,
            RegAddr, I2C_TRAN_NOT_END);
    if(retv != SUCCESS)
    {
        return (FAILURE);
    }

    // Send restart signal then receive one byte from I2C bus
    // at last Send STOP signal to release I2C bus
    retv = xI2CMasterReadS1(ADXL345_PIN_I2C_PORT, ADXL345_I2C_ADDR,
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
//!  This function is to write one byte to ADXL345 register,one byte will be
//!  writen in appointed address.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result ADXL345_RegWriteByte(uint8_t RegAddr, uint8_t Data)
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
//!  This function is to read one byte from ADXL345 register,
//!  and write the data to the special address.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result ADXL345_RegReadByte(uint8_t RegAddr, uint8_t * DataRecvBuf)
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
Result ADXL345_Init(void)
{
    uint8_t i   = 0;
    Result retv = SUCCESS;

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
        retv = ADXL345_RegWriteByte(ADXL345_Regs[i].Addr, ADXL345_Regs[i].Val);
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
Result ADXL345_ReadAccData(uint8_t Axis, int16_t * DataRecvBuf)
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
                RegAddr = ADXL345_REG_DATAX0;
                break;
            }

        case AXIS_Y:
            {
                RegAddr = ADXL345_REG_DATAY0;
                break;
            }

        case AXIS_Z:
            {
                RegAddr = ADXL345_REG_DATAZ0;
                break;
            }
        default:
            {
                return(FAILURE);
            }
    }

    //Clear user's data buffer
    *DataRecvBuf = 0;

    //Read LSB 8 bit
    retv = ADXL345_RegReadByte(RegAddr, &TmpVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }
    //TODO check
    *DataRecvBuf |= (uint16_t)TmpVal;

    //Read MSB 8 bit
    retv = ADXL345_RegReadByte(RegAddr + 1, &TmpVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }
    *DataRecvBuf |= ((uint16_t)TmpVal << 8);

    return (SUCCESS);
}

//*****************************************************************************
//
//! \brief Set User Offset Correction value.
//!
//! \param Axis is the axis data which you want to read. this paramter can be
//! one of the following value: \b AXIS_X \b AXIS_Y \b AXIS_Z.
//!
//! \param OffSet is offset value.
//!
//! The OFSX, OFSY, and OFSZ registers are each eight bits and 
//! offer user-set offset adjustments in twos complement format 
//! with a scale factor of 15.6 mg/LSB (that is, 0x7F = 2 g). The 
//! value stored in the offset registers is automatically added to the 
//! acceleration data, and the resulting value is stored in the output 
//! data registers.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//***************************************************************************** 
Result ADXL345_OffSetWrite(uint8_t Axis, uint8_t OffSet)
{
    uint8_t  RegAddr = 0;
    Result   retv    = SUCCESS;

    ASSERT ((Axis == AXIS_X) || (Axis == AXIS_Y) || (Axis == AXIS_Z));

    //Get Offset Register Address
    switch(Axis)
    {
        case AXIS_X:
            {
                RegAddr = ADXL345_REG_OFSX;
                break;
            }

        case AXIS_Y:
            {
                RegAddr = ADXL345_REG_OFSY;
                break;
            }

        case AXIS_Z:
            {
                RegAddr = ADXL345_REG_OFSZ;
                break;
            }
        default:
            {
                return(FAILURE);
            }
    }

    //Write user's value to offset register
    retv = ADXL345_RegWriteByte(RegAddr, OffSet);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Set Tap ThresHold value.
//!
//! \param ThresHold is pulse threshold value.
//!
//! The THRESH_TAP register is eight bits and holds the threshold 
//! value for tap interrupts. The data format is unsigned, therefore, 
//! the magnitude of the tap event is compared with the value  
//! in THRESH_TAP for normal tap detection. The scale factor is 
//! 62.5 m g/LSB (that is, 0xFF = 16 g). A value of 0 may result in 
//! undesirable behavior if single tap/double tap interrupts are enabled. 
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//*****************************************************************************
Result ADXL345_TapThresholdSet(uint8_t ThresHold)
{
    return (ADXL345_RegWriteByte(ADXL345_REG_THRESH_TAP, ThresHold));
}

//*****************************************************************************
//
//! \brief Set window value.
//!
//! \param Window is eight bits and contains an unsigned time 
//! value representing the amount of time after the expiration of the 
//! latency time (determined by the latent register) during which a 
//! second valid tap can begin. The scale factor is 1.25 ms/LSB. A 
//! value of 0 disables the double tap function.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//*****************************************************************************
Result ADXL345_WindowSet(uint8_t Window)
{
    return (ADXL345_RegWriteByte(ADXL345_REG_Window,  Window));
}

//*****************************************************************************
//
//! \brief Set Latency value.
//!
//! \param Latentcy register is eight bits and contains an unsigned time 
//! value representing the wait time from the detection of a tap 
//! event to the start of the time window (defined by the window 
//! register) during which a possible second tap event can be detected. 
//! The scale factor is 1.25 ms/LSB. A value of 0 disables the double tap function. 
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//*****************************************************************************
Result ADXL345_LatencySet(uint8_t Latency)
{
    return (ADXL345_RegWriteByte(ADXL345_REG_Latent, Latency));
}

//*****************************************************************************
//
//! \brief Set Duration value.
//!
//! \param Duration is eight bits and contains an unsigned time 
//! value representing the maximum time that an event must be 
//! above the THRESH_TAP threshold to qualify as a tap event. The 
//! scale factor is 625 us/LSB. A value of 0 disables the single tap/ 
//! double tap functions.
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//*****************************************************************************
Result ADXL345_DurationSet(uint8_t Duration)
{
    return (ADXL345_RegWriteByte(ADXL345_REG_DUR, Duration));
}

//*****************************************************************************
//
//! \brief Set Active ThresHold value.
//!
//! \param  ThresHoldr is eight bits and holds the threshold 
//! value for detecting activity. The data format is unsigned, so the 
//! magnitude of the activity event is compared with the value in 
//! the THRESH_ACT register. The scale factor is 62.5 m g /LSB.  
//! A value of 0 may result in undesirable behavior if the activity 
//! interrupt is enabled.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//*****************************************************************************
Result ADXL345_ActThresholdSet(uint8_t ThresHold)
{
    return (ADXL345_RegWriteByte(ADXL345_REG_THRESH_ACT, ThresHold));
}

//*****************************************************************************
//
//! \brief Set Inactive ThresHold value.
//!
//! \param  ThresHoldr is eight bits and holds the threshold 
//! value for detecting inactivity. The data format is unsigned, so 
//! the magnitude of the inactivity event is compared with the value 
//! in the THRESH_INACT register. The scale factor is 62.5 m g/LSB. 
//! A value of 0 may result in undesirable behavior if the inactivity 
//! interrupt is enabled.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//*****************************************************************************
Result ADXL345_InactThresholdSet(uint8_t ThresHold)
{
    return (ADXL345_RegWriteByte(ADXL345_REG_THRESH_INACT, ThresHold));
}

//*****************************************************************************
//
//! \brief Set Inactive time value.
//!
//! \param Time is eight bits and contains an unsigned 
//! time value representing the amount of time that acceleration 
//! must be less than the value in the THRESH_INACT register for 
//! inactivity to be declared. The scale factor is 1 sec/LSB. Unlike 
//! the other interrupt functions, which use unfiltered data (see the 
//! Threshold  section), the inactivity function uses filtered output 
//! data. At least one output sample must be generated for the 
//! inactivity interrupt to be triggered. This results in the function 
//! appearing unresponsive if the TIME_INACT register is set to a 
//! value less than the time constant of the output data rate. A value 
//! of 0 results in an interrupt when the output data is less than the 
//! value in the THRESH_INACT register. 
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//*****************************************************************************
Result ADXL345_InactTimeSet(uint8_t Time)
{
    return (ADXL345_RegWriteByte(ADXL345_REG_TIME_INACT, Time));
}


//*****************************************************************************
//
//! \brief Configure action detect
//!
//! \param Cfg the paramter can be \b OR of the following value.
//! more information, please reference Macro define.
//!
//! ACT_AC                   
//! ACT_X_EN          
//! ACT_Y_EN                 
//! ACT_Z_EN                 
//! INACT_AC                 
//! INACT_X_EN               
//! INACT_Y_EN               
//! INACT_Z_EN               
//!                          
//! ACT_DC                   
//! ACT_X_DIS                
//! ACT_Y_DIS                
//! ACT_Z_DIS                
//! INACT_DC                 
//! INACT_X_DIS              
//! INACT_Y_DIS              
//! INACT_Z_DIS  
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result ADXL345_ActCfg(uint32_t Cfg)
{
    uint8_t  RegVal = 0;
    Result   retv    = SUCCESS;

    retv = ADXL345_RegReadByte(ADXL345_REG_ACT_INACT_CTL, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    RegVal &= (uint8_t) ~(Cfg >> 8);
    RegVal |= (uint8_t)  (Cfg >> 0);

    retv = ADXL345_RegWriteByte(ADXL345_REG_ACT_INACT_CTL, RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Set FreeFall ThresHold value.
//!
//! \param  ThresHold is eight bits and holds the threshold 
//! value, in unsigned format, for free-fall detection. The acceleration on 
//! all axes is compared with the value in THRESH_FF to determine if 
//! a free-fall event occurred. The scale factor is 62.5 mg /LSB. Note 
//! that a value of 0 m g  may result in undesirable behavior if the free-fall
//! interrupt is enabled. Values between 300 mg and 600 m g (0x05 to 0x09) are
//! recommended.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//*****************************************************************************
Result ADXL345_FFThresholdSet(uint8_t ThresHold)
{
    return (ADXL345_RegWriteByte(ADXL345_REG_THRESH_FF, ThresHold));
}

//*****************************************************************************
//
//! \brief Set FreeFall Time value.
//!
//! \param Time is eight bits and stores an unsigned time 
//! value representing the minimum time that the value of all axes 
//! must be less than THRESH_FF to generate a free-fall interrupt. 
//! The scale factor is 5 ms/LSB. A value of 0 may result in undesirable 
//! behavior if the free-fall interrupt is enabled. Values between 100 ms 
//! and 350 ms (0x14 to 0x46) are recommended. 
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//*****************************************************************************
Result ADXL345_FFTimeSet(uint8_t Time)
{
    return (ADXL345_RegWriteByte(ADXL345_REG_TIME_FF, Time));
}

//*****************************************************************************
//
//! \brief Configure Tap detect
//!
//! \param Cfg the paramter can be \b OR of the following value.
//! more information, please reference Macro define.
//!
//! TAP_SUPRESS_EN           
//! TAP_X_EN                 
//! TAP_Y_EN                 
//! TAP_Z_EN                 
//! TAP_SUPRESS_DIS          
//! TAP_X_DIS                
//! TAP_Y_DIS                
//! TAP_Z_DIS  
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result ADXL345_TapCfg(uint32_t Cfg)
{
    uint8_t  RegVal = 0;
    Result   retv   = SUCCESS;

    retv = ADXL345_RegReadByte(ADXL345_REG_TAP_AXES, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    RegVal &= (uint8_t) ~(Cfg >> 8);
    RegVal |= (uint8_t)  (Cfg >> 0);

    retv = ADXL345_RegWriteByte(ADXL345_REG_TAP_AXES, RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Check ADXL345 Event Status.
//!
//! \param Event is the Event(s) to be checked, the paramter can be \b OR of the
//! following value.more information, please reference Macro define.
//! 
//! EVENT_ACT_X        
//! EVENT_ACT_Y        
//! EVENT_ACT_Z        
//! EVENT_ASLEEP       
//! EVENT_TAP_X        
//! EVENT_TAP_Y        
//! EVENT_TAP_Z        
//! EVENT_DATA_READY   
//! EVENT_SINGLE_TAP   
//! EVENT_DOUBLE_TAP   
//! EVENT_ACTIVITY     
//! EVENT_INACTIVITY   
//! EVENT_FREE_FALL    
//! EVENT_WATERMARK    
//! EVENT_OVERRUN      
//! EVENT_FIFO_TRG
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or \b FAILURE.  when checked event occured and there
//! is no error, then return \b SUCCESS.  others return \b FAILURE.
//
//*****************************************************************************
Result ADXL345_StatusCheck(uint32_t Event)
{
    uint8_t  RegVal_1 = 0;
    uint8_t  RegVal_2 = 0;
    uint8_t  RegVal_3 = 0;

    Result   retv   = SUCCESS;

    //Check Action and tap status register
    retv = ADXL345_RegReadByte(ADXL345_REG_ACT_TAP_STATUS, &RegVal_1);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    //Check interrupt status register
    retv = ADXL345_RegReadByte(ADXL345_REG_INT_SOURCE, &RegVal_2);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    //Check FIFO status register
    retv = ADXL345_RegReadByte(ADXL345_REG_FIFO_STATUS, &RegVal_3);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    RegVal_1 &= (uint8_t) (Event >> 0);
    RegVal_2 &= (uint8_t) (Event >> 8);
    RegVal_3 &= (uint8_t) (Event >> 16);

    if(RegVal_1 | RegVal_2 | RegVal_3)
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
//! \brief Configure Power Mode
//!
//! \param Cfg the paramter can be \b OR of the following value.
//! more information, please reference Macro define.
//!
//! LOW_POWER_EN             
//! LOW_POWER_DIS            
//! OUTPUT_RATE_3200         
//! OUTPUT_RATE_1600         
//! OUTPUT_RATE_800          
//! OUTPUT_RATE_400          
//! OUTPUT_RATE_200          
//! OUTPUT_RATE_100          
//! OUTPUT_RATE_50           
//! OUTPUT_RATE_25           
//! OUTPUT_RATE_12_5         
//! OUTPUT_RATE_6_25         
//! OUTPUT_RATE_3_13         
//! OUTPUT_RATE_1_56         
//! OUTPUT_RATE_0_78         
//! OUTPUT_RATE_0_39         
//! OUTPUT_RATE_0_20         
//! OUTPUT_RATE_0_10         
//! LINK_EN                  
//! AUTO_SLEEP_EN            
//! MEASURE_EN               
//! SLEEP_EN                 
//! LINK_DIS                 
//! AUTO_SLEEP_DIS           
//! MEASURE_DIS              
//! SLEEP_DIS                
//! SLEEP_RATE_8             
//! SLEEP_RATE_4             
//! SLEEP_RATE_2             
//! SLEEP_RATE_1  
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result ADXL345_PowerCfg(uint32_t Cfg)
{
    uint8_t  RegVal = 0;
    Result   retv   = SUCCESS;


    if(Cfg & 0x0000FFFF)
    {
        retv = ADXL345_RegReadByte(ADXL345_REG_BW_RATE, &RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }

        RegVal &= (uint8_t) ~(Cfg >> 8);
        RegVal |= (uint8_t)  (Cfg >> 0);

        retv = ADXL345_RegWriteByte(ADXL345_REG_BW_RATE, RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }
    }

    if(Cfg & 0xFFFF0000)
    {
        retv = ADXL345_RegReadByte(ADXL345_REG_POWER_CTL, &RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }

        RegVal &= (uint8_t) ~(Cfg >> 24);
        RegVal |= (uint8_t)  (Cfg >> 16);

        retv = ADXL345_RegWriteByte(ADXL345_REG_POWER_CTL, RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }
    }

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Configure Interrupt
//!
//! \param Cfg the paramter can be \b OR of the following value.
//! more information, please reference Macro define.
//!
//! INT_DATA_READY_EN      
//! INT_SINGLE_TAP_EN      
//! INT_DOUBLE_TAP_EN      
//! INT_ACTIVITY_EN        
//! INT_INACTIVITY_EN      
//! INT_FREE_FALL_EN       
//! INT_WATERMARK_EN       
//! INT_OVERRUN_EN         
//! 
//! INT_DATA_READY_DIS     
//! INT_SINGLE_TAP_DIS     
//! INT_DOUBLE_TAP_DIS     
//! INT_ACTIVITY_DIS       
//! INT_INACTIVITY_DIS     
//! INT_FREE_FALL_DIS      
//! INT_WATERMARK_DIS      
//! INT_OVERRUN_DIS        
//! 
//! DATA_READY_INT1        
//! SINGLE_TAP_INT1        
//! DOUBLE_TAP_INT1        
//! ACTIVITY_INT1          
//! INACTIVITY_INT1        
//! FREE_FALL_INT1         
//! WATERMARK_INT1         
//! OVERRUN_INT1           
//! 
//! DATA_READY_INT2        
//! SINGLE_TAP_INT2        
//! DOUBLE_TAP_INT2        
//! ACTIVITY_INT2          
//! INACTIVITY_INT2        
//! FREE_FALL_INT2         
//! WATERMARK_INT2         
//! OVERRUN_INT2  
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result ADXL345_IntCfg(uint32_t Cfg)
{
    uint8_t  RegVal = 0;
    Result   retv   = SUCCESS;

    if(Cfg & 0x0000FFFF)
    {
        retv = ADXL345_RegReadByte(ADXL345_REG_INT_ENABLE, &RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }

        RegVal &= (uint8_t) ~(Cfg >> 8);
        RegVal |= (uint8_t)  (Cfg >> 0);

        retv = ADXL345_RegWriteByte(ADXL345_REG_INT_ENABLE, RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }
    }

    if(Cfg & 0xFFFF0000)
    {
        retv = ADXL345_RegReadByte(ADXL345_REG_INT_MAP, &RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }

        RegVal &= (uint8_t) ~(Cfg >> 24);
        RegVal |= (uint8_t)  (Cfg >> 16);

        retv = ADXL345_RegWriteByte(ADXL345_REG_INT_MAP, RegVal);
        if (retv != SUCCESS)
        {
            return(FAILURE);
        }
    }

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Configure Data Format
//!
//! \param Cfg the paramter can be \b OR of the following value.
//! more information, please reference Macro define.
//!
//! SELF_TEST_EN      
//! SPI_3_WIRE        
//! INT_LOW           
//! FULL_RES_EN       
//! JUSTIFY_LEFT      
//!                   
//! SELF_TEST_DIS     
//! SPI_4_WIRE        
//! INT_HIGH          
//! FULL_RES_DIS      
//! JUSTIFY_RIGHT     
//!                   
//! RANGE_2_G         
//! RANGE_4_G         
//! RANGE_8_G         
//! RANGE_16_G   
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result ADXL345_DataCfg(uint32_t Cfg)
{
    uint8_t  RegVal = 0;
    Result   retv   = SUCCESS;

    retv = ADXL345_RegReadByte(ADXL345_REG_DATA_FORMAT, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    RegVal &= (uint8_t) ~(Cfg >> 8);
    RegVal |= (uint8_t)  (Cfg >> 0);

    retv = ADXL345_RegWriteByte(ADXL345_REG_DATA_FORMAT, RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Configure Data Format
//!
//! \param Cfg the paramter can be \b OR of the following value.
//! more information, please reference Macro define.
//!
//! MODE_BYPASS              
//! MODE_FIFO                
//! MODE_STREAM              
//! MODE_TRIGGER             
//! FIFO_INT1                
//! FIFO_INT2  
//!
//! \param Sample
//! 
//! The function of these bits depends on the FIFO mode selected 
//! (see  Table below). Entering a value of 0 in the samples bits immediately 
//! sets the watermark status bit in the INT_SOURCE register, 
//! regardless of which FIFO mode is selected. Undesirable operation 
//! may occur if a value of 0 is used for the samples bits when trigger 
//! mode is used. 
//! 
//!  ==================================Table=====================================
//! |----------------------------------------------------------------------------|
//! | Bypass | None.                                                             |
//! |--------|-------------------------------------------------------------------|
//! | FIFO   | Specifies how many FIFO entries are needed to trigger a watermark |
//! |        | interrupt.                                                        |
//! |--------|-------------------------------------------------------------------|
//! | Stream | Specifies how many FIFO entries are needed to trigger a watermark |
//! |        | interrupt.                                                        |
//! |--------|-------------------------------------------------------------------|
//! | Trigger| Specifies how many FIFO samples are retained in the FIFO buffer   |
//! |        | before a trigger event.                                           |
//! |----------------------------------------------------------------------------|
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE .
//
//*****************************************************************************
Result ADXL345_FIFOCfg(uint32_t Cfg, uint8_t Sample)
{
    uint8_t  RegVal    = 0;
    uint8_t  EntryMask = 0x1F;
    Result   retv      = SUCCESS;

    retv = ADXL345_RegReadByte(ADXL345_REG_FIFO_CTL, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    RegVal &= ~EntryMask ;
    RegVal |= (Sample & EntryMask);

    RegVal &= (uint8_t) ~(Cfg >> 8);
    RegVal |= (uint8_t)  (Cfg >> 0);

    retv = ADXL345_RegWriteByte(ADXL345_REG_FIFO_CTL, RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    return(SUCCESS);
}

//*****************************************************************************
//
//! \brief Get FIFO Entries
//!
//! \param pEntry is the receive buffer addrress.
//!
//! \note Entry report how many data values are stored in FIFO. 
//! Access to collect the data from FIFO is provided through the 
//! DATAX, DATAY, and DATAZ registers. FIFO reads must be 
//! done in burst or multiple-byte mode because each FIFO level is 
//! cleared after any read (single- or multiple-byte) of FIFO. FIFO 
//! stores a maximum of 32 entries, which equates to a maximum 
//! of 33 entries available at any given time because an additional 
//! entry is available at the output filter of the device.
//!
//! \return Indicate the status of operation which can be one of the following
//! value \b SUCCESS or  \b FAILURE.
//
//*****************************************************************************
Result ADXL345_EntryGet(uint8_t * pEntry)
{
    uint8_t  RegVal    = 0;
    uint8_t  EntryMask = 0x1F;
    Result   retv      = SUCCESS;

    retv = ADXL345_RegReadByte(ADXL345_REG_FIFO_CTL, &RegVal);
    if (retv != SUCCESS)
    {
        return(FAILURE);
    }

    *pEntry = (RegVal & EntryMask);

    return(SUCCESS);

}

