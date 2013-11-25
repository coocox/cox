//*****************************************************************************
//
//! \file spi_drv.c
//! \brief Function for Arduino WiFi Shield.
//! \version 2.1.1.0
//! \date 20/2/2013
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2013, CooCox
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


#include "spi_drv.h"

//About 15us
#define DELAY_TRANSFER() delay(0x5F)

//*****************************************************************************
//
//! \brief Delay Function
//!
//! \param tick.
//!
//! \return None
//! \note This function is only used internal.
//
//*****************************************************************************
static void delay(volatile uint32_t tick)
{
    while(tick--);
}

//! when you port wifi driver to other platform, you only rewrite those functions.
//! void    SpiDrv_Init(void)
//! void    SpiDrv_Stop(void)
//! void    SpiDrv_SlaveSelect(void)
//! void    SpiDrv_SlaveDeselect(void)
//! uint8_t SpiDrv_Transfer(uint8_t data)
//! void    SpiDrv_WaitForSlaveReady(void)

//*****************************************************************************
//
//! \brief Init Spi communction port and wifi handshake pin.
//
//! WiFi shield IO refence volatge == 3.3V
//! Pin map is below:
//! HAND_PIN  --> PA3
//! SPI1_NSS  --> PA4
//! SPI1_SCK  --> PA5
//! SPI1_MISO --> PA6
//! SPI1_MOSI --> PA7
//!
//! \param none.
//!
//! \return None
//
//*****************************************************************************
void SpiDrv_Init(void)
{
    
    xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);

    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

    xGPIOSPinTypeGPIOInput(PA3);
    xGPIOSPinTypeGPIOOutput(PA4);

    xSPinTypeSPI(SPI1CLK(3),  PA5);
    xSPinTypeSPI(SPI1MOSI(3), PA7);
    xSPinTypeSPI(SPI1MISO(1), PA6);

    //
    // Configure MCU as a master device , 8 bits data width ,MSB first,Mode_0
    //
    xSPIConfigSet(xSPI1_BASE, 4000000, xSPI_MOTO_FORMAT_MODE_0 |
                                                xSPI_MODE_MASTER |
                                                xSPI_MSB_FIRST |
                                                xSPI_DATA_WIDTH8);
    xSPISSSet(xSPI1_BASE, xSPI_SS_SOFTWARE, xSPI_SS0);

    xSPIEnable(xSPI1_BASE);
}

//*****************************************************************************
//
//! \brief Disable Spi Port
//!
//! \param none.
//!
//! \return None
//
//*****************************************************************************
void SpiDrv_Stop(void)
{
    //SPI_Cmd(SPI1, DISABLE);
}

//*****************************************************************************
//
//! \brief Select the SPI Salave.
//!
//! \param none.
//!
//! \return None
//
//*****************************************************************************
void SpiDrv_SlaveSelect(void)
{
    //Select the SPI slave
    //GPIO_ResetBits(GPIOA, GPIO_Pin_4);
    xGPIOPinWrite(xGPIO_PORTA_BASE, xGPIO_PIN_4, 0);
}

//*****************************************************************************
//
//! \brief Deselect the SPI Salave.
//!
//! \param none.
//!
//! \return None
//
//*****************************************************************************
void SpiDrv_SlaveDeselect(void)
{
    //Deselect the SPI slave
    //GPIO_SetBits(GPIOA, GPIO_Pin_4);
    xGPIOPinWrite(xGPIO_PORTA_BASE, xGPIO_PIN_4, 1);
}

//*****************************************************************************
//
//! \brief Write an byte to SPI Bus then read back an byte.
//!
//! \param data is the byte to be transfered.
//!
//! \return the byte read back from spi salave.
//! \note after read byte, you must wait 10us.
//
//*****************************************************************************
uint8_t SpiDrv_Transfer(uint8_t ucData)
{
    /*
    uint8_t recv = 0;
    
    recv = xSPISingleDataReadWrite(xSPI1_BASE, data);
    
    //This delay is must
    //Note By CooCox Cedar
    delay(0x5F);
    
    return (recv);
    */
        
    unsigned long ucRecv = 0;

	while(xSPIIsTxEmpty(xSPI1_BASE) == xfalse);
	SPIDataPut(xSPI1_BASE, ucData);
	while(SPIIsRxNotEmpty(xSPI1_BASE) == xfalse);
	xSPIDataGet(xSPI1_BASE, &ucRecv);
	delay(0x5F);
	return (ucRecv);
}

//*****************************************************************************
//
//! \brief wait for salave ready.
//!
//! \param none.
//!
//! \return none.
//! 
//! \note this handshake pin is must when use spi communication mode.
//
//*****************************************************************************
void SpiDrv_WaitForSlaveReady(void)
{
    //Wait WiFi SPI idle.
    //while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == Bit_SET);
    while(xGPIOPinRead(xGPIO_PORTA_BASE, xGPIO_PIN_3) != 0);
}

//////////////////////////////////////////////////////////////////////////

//*****************************************************************************
//
//! \brief wait for special byte.
//!
//! \param waitChar is the byte you want tu wait for.
//!
//! \return value can be one of -1 or 1 or 0.
//!     -1: Cmd is error
//!     0 : there is no error, but can not wait the byte.
//!     1 : successful wait the byte.
//! 
//
//*****************************************************************************
int32_t SpiDrv_WaitChar(uint8_t waitChar)
{
    uint8_t _readChar = 0;
    int16_t timeout   = TIMEOUT_CHAR;
    
    do{
        _readChar = SpiDrv_ReadChar();
        if (_readChar == ERR_CMD)
        {
            return (-1);
        }
    }while((timeout-- > 0) && (_readChar != waitChar));
    
    return  (_readChar == waitChar);
}

//*****************************************************************************
//
//! \brief Read And Check Char.
//!
//! \param checkChar is the check char.
//! \param readChar pointer to the address you want to store the read byte.
//!
//! \return value can be one of 1 or 0.
//!     0 : not equal
//!     1 : equal
//! 
//
//*****************************************************************************
int32_t SpiDrv_ReadAndCheckChar(uint8_t checkChar, uint8_t* readChar)
{
    SpiDrv_GetParam(readChar);
    
    return  (*readChar == checkChar);
}

//*****************************************************************************
//
//! \brief Read an byte from SPI Bus.
//!
//! \param none.
//!
//! \return the byte that get from spi bus.
//! 
//
//*****************************************************************************
uint8_t SpiDrv_ReadChar(void)
{
    uint8_t readChar = 0;
    
    readChar = SpiDrv_Transfer(DUMMY_DATA);
    DELAY_TRANSFER();
    
    return readChar;
}

//*****************************************************************************
//
//! \brief get an byte from SPI Bus.
//!
//! \param param is char pointer.
//!
//! \return none.
//! 
//
//*****************************************************************************
void SpiDrv_GetParam(uint8_t* param)
{
    // Get Params data
    *param = SpiDrv_Transfer(DUMMY_DATA);
    DELAY_TRANSFER();
}

//*****************************************************************************
//
//! \brief wait response command and read the param
//!
//! \param cmd is the command you want to wait.
//! \param numParam is the lenght of param you want to read. 
//! \param Param is buffer to store received param.
//! \param param_len is the lenght of param.
//!
//! \return 0: failure 1:success.
//! 
//
//*****************************************************************************
int32_t SpiDrv_WaitResponseCmd(uint8_t cmd, uint8_t numParam, uint8_t* param, uint8_t* param_len)
{
    uint8_t i     = 0;
    uint8_t _data = 0;
    
    if(!SpiDrv_WaitChar(START_CMD))
    {
        return 0;
    }
    else
    {
        if (!SpiDrv_ReadAndCheckChar(cmd | REPLY_FLAG, &_data))
        {
            return 0;
        }
        
        if (!SpiDrv_ReadAndCheckChar(numParam, &_data))
        {
            return 0;
        }
        else
        {
            SpiDrv_ReadParamLen8(param_len);
            for (i=0; i<(*param_len); ++i)
            {
                // Get Params data
                SpiDrv_GetParam(&param[i]);
            }
        }
        
        SpiDrv_ReadAndCheckChar(END_CMD, &_data);
    }
    
    return 1;
}

//*****************************************************************************
//
//! \brief wait 16-bit length response data.
//!
//! \param cmd is the command you want to wait.
//! \param Param is buffer to store received param.
//! \param param_len is the lenght of param.
//!
//! \return 0: failure 1:success.
//! 
//
//*****************************************************************************
int32_t SpiDrv_WaitResponseData16(uint8_t cmd, uint8_t* param, uint16_t* param_len)
{
    uint8_t  _data    = 0;
    uint8_t  numParam = 0;
    uint16_t i        = 0;
    
    if(!SpiDrv_WaitChar(START_CMD))
    {
        return 0;
    }
    else
    {
        if (!SpiDrv_ReadAndCheckChar(cmd | REPLY_FLAG, &_data))
        {
            return 0;
        }
        numParam = SpiDrv_ReadChar();
        if (numParam != 0)
        {
            SpiDrv_ReadParamLen16(param_len);
            for (i=0; i<(*param_len); ++i)
            {
                // Get Params data
                SpiDrv_GetParam(&param[i]);
            }
        }
        
        SpiDrv_ReadAndCheckChar(END_CMD, &_data);
    }
    
    return 1;
}

//*****************************************************************************
//
//! \brief wait 8-bit length response data.
//!
//! \param cmd is the command you want to wait.
//! \param Param is buffer to store received param.
//! \param param_len is the lenght of param.
//!
//! \return 0: failure 1:success.
//! 
//
//*****************************************************************************
int32_t SpiDrv_WaitResponseData8(uint8_t cmd, uint8_t* param, uint8_t* param_len)
{
    uint8_t i        = 0;
    uint8_t _data    = 0;
    uint8_t numParam = 0;
    
    if(!SpiDrv_WaitChar(START_CMD))
    {
        return 0;
    }
    else
    {
        if (!SpiDrv_ReadAndCheckChar(cmd | REPLY_FLAG, &_data))
        {
            return 0;
        }
        
        numParam = SpiDrv_ReadChar();
        if (numParam != 0)
        {
            SpiDrv_ReadParamLen8(param_len);
            for (i=0; i<(*param_len); ++i)
            {
                // Get Params data
                SpiDrv_GetParam(&param[i]);
            }
        }
        
        SpiDrv_ReadAndCheckChar(END_CMD, &_data);
    }
    
    return 1;
}

//*****************************************************************************
//
//! \brief wait cmd and read response param.
//!
//! \param cmd is the command you want to wait.
//! \param numParam is the length of param.
//! \param params is the buffer to store received data.
//!
//! \return 0: failure 1:success.
//! 
//
//*****************************************************************************
int32_t SpiDrv_WaitResponseParams(uint8_t cmd, uint8_t numParam, tParam* params)
{
    uint8_t i         = 0;
    uint8_t ii        = 0;
    uint8_t _data     = 0;
    uint8_t _numParam = 0;
    
    if(!SpiDrv_WaitChar(START_CMD))
    {
        return 0;
    }
    else
    {
        if (!SpiDrv_ReadAndCheckChar(cmd | REPLY_FLAG, &_data))
        {
            return 0;
        }
        
        _numParam = SpiDrv_ReadChar();
        if (_numParam != 0)
        {
            if (numParam != _numParam)
            {
                /*WARN("Mismatch numParam");*/
                return 0;
            }
            
            for (i=0; i<_numParam; ++i)
            {
                params[i].paramLen = SpiDrv_ReadParamLen8(NULL);
                for (ii=0; ii<params[i].paramLen; ++ii)
                {
                    // Get Params data
                    params[i].param[ii] = SpiDrv_Transfer(DUMMY_DATA);
                }
            }
        }
        else
        {
            /*WARN("Error numParam == 0");*/
            return 0;
        }
        
        SpiDrv_ReadAndCheckChar(END_CMD, &_data);
    }
    return 1;
}


//*****************************************************************************
//
//! \brief wait cmd and read response param.
//!
//! \param cmd is the command you want to wait.
//! \param numParamRead is the length of param.
//! \param params is the buffer to store received data.
//! \param maxNumParams is the max length of param.
//!
//! \return 0: failure 1:success.
//! 
//
//*****************************************************************************
int32_t SpiDrv_WaitResponse(uint8_t cmd, uint8_t* numParamRead, uint8_t** params, uint8_t maxNumParams)
{
    uint8_t _data    = 0;
    int     i        = 0;
    int     ii       = 0;
    uint8_t numParam = 0;
    uint8_t paramLen = 0;
    
    char    *index[WL_SSID_MAX_LENGTH];
    
    for (i = 0 ; i < WL_NETWORKS_LIST_MAXNUM ; i++)
    {
        index[i] = (char *)params + WL_SSID_MAX_LENGTH*i;
    }
    
    if(!SpiDrv_WaitChar(START_CMD))
    {
        return 0;
    }
    else
    {
        if (!SpiDrv_ReadAndCheckChar(cmd | REPLY_FLAG, &_data))
        {
            return 0;
        }
        
        numParam = SpiDrv_ReadChar();
        
        if (numParam > maxNumParams)
        {
            numParam = maxNumParams;
        }
        *numParamRead = numParam;
        if (numParam != 0)
        {
            for (i=0; i<numParam; ++i)
            {
                paramLen = SpiDrv_ReadParamLen8(NULL);
                for (ii=0; ii<paramLen; ++ii)
                {
                    // Get Params data
                    index[i][ii] = SpiDrv_Transfer(DUMMY_DATA);
                }
                index[i][ii]=0;
            }
        }
        else
        {
            /*WARN("Error numParams == 0");*/
            SpiDrv_ReadAndCheckChar(END_CMD, &_data);
            return 0;
        }
        SpiDrv_ReadAndCheckChar(END_CMD, &_data);
    }
    return 1;
}

//*****************************************************************************
//
//! \brief Send Param to SPI Bus
//!
//! \param param is the buffer to store received data.
//! \param Param_len is the length of param.
//! \param lastParam is the indicate whether is lastparam.
//!
//! \return none.
//! 
//
//*****************************************************************************
void SpiDrv_SendParam(uint8_t* param, uint8_t param_len, uint8_t lastParam)
{
    int i = 0;
    
    // Send Spi paramLen
    SpiDrv_SendParamLen8(param_len);
    
    // Send Spi param data
    for (i=0; i<param_len; ++i)
    {
        SpiDrv_Transfer(param[i]);
    }
    
    // if lastParam==1 Send Spi END CMD
    if (lastParam == 1)
    {
        SpiDrv_Transfer(END_CMD);
    }
}

//*****************************************************************************
//
//! \brief Send 8-bit Param to SPI Bus
//!
//! \param Param_len is the param.
//!
//! \return none.
//! 
//
//*****************************************************************************
void SpiDrv_SendParamLen8(uint8_t param_len)
{
    // Send Spi paramLen
    SpiDrv_Transfer(param_len);
}

//*****************************************************************************
//
//! \brief Send 16-bit Param to SPI Bus
//!
//! \param Param_len is the param.
//!
//! \return none.
//! 
//
//*****************************************************************************
void SpiDrv_SendParamLen16(uint16_t param_len)
{
    // Send Spi paramLen
    SpiDrv_Transfer((uint8_t)(param_len >> 8));
    SpiDrv_Transfer((uint8_t)param_len);
}

//*****************************************************************************
//
//! \brief read 8-bit Param from SPI Bus
//!
//! \param Param_len is buffer to store the read back param.
//!
//! \return is the param read from spi bus.
//! 
//
//*****************************************************************************
uint8_t SpiDrv_ReadParamLen8(uint8_t* param_len)
{
    uint8_t _param_len = SpiDrv_Transfer(DUMMY_DATA);
    if (param_len != NULL)
    {
        *param_len = _param_len;
    }
    return _param_len;
}

//*****************************************************************************
//
//! \brief read 16-bit Param from SPI Bus
//!
//! \param Param_len is buffer to store the read back param.
//!
//! \return is the param read from spi bus.
//! 
//
//*****************************************************************************
uint16_t SpiDrv_ReadParamLen16(uint16_t* param_len)
{
    uint16_t _param_len = 0;
    
    _param_len  = SpiDrv_Transfer(DUMMY_DATA) << 8;
    _param_len |= SpiDrv_Transfer(DUMMY_DATA) & 0xff;
    
    if (param_len != NULL)
    {
        *param_len = _param_len;
    }
    return _param_len;
}

//*****************************************************************************
//
//! \brief send block data to SPI Bus
//!
//! \param param is the buffer to store data.
//! \param Param_len is length of the param.
//! \param lastParam is the indicate whether is lastparam.
//! 
//! \return none.
//
//*****************************************************************************
void SpiDrv_SendBuffer(uint8_t* param, uint16_t param_len, uint8_t lastParam)
{
    uint16_t i = 0;
    
    // Send Spi paramLen
    SpiDrv_SendParamLen16(param_len);
    
    // Send Spi param data
    for (i=0; i<param_len; ++i)
    {
        SpiDrv_Transfer(param[i]);
    }
    
    // if lastParam==1 Send Spi END CMD
    if (lastParam == 1)
    {
        SpiDrv_Transfer(END_CMD);
    }
}

//*****************************************************************************
//
//! \brief send 16-bit param to spi bus.
//!
//! \param param is the data to be sended.
//! \param lastParam is the indicate whether is lastparam.
//! 
//! \return none.
//
//*****************************************************************************
void SpiDrv_SendParam16(uint16_t param, uint8_t lastParam)
{
    // Send Spi paramLen
    SpiDrv_SendParamLen8(2);
    
    SpiDrv_Transfer((uint8_t)((param & 0xff00)>>8));
    SpiDrv_Transfer((uint8_t)(param & 0xff));
    
    // if lastParam==1 Send Spi END CMD
    if (lastParam == 1)
    {
        SpiDrv_Transfer(END_CMD);
    }
}

//*****************************************************************************
//
//! \brief send cmd to spi bus
//!
//! \param cmd is the cmd to be sended.
//! \param numParam is the number of paramters.
//! \note the Cmd Struct Message is like below:
//! __________________________________________________________________________________
//! | START CMD | C/R  | CMD  |[TOT LEN]| N.PARAM | PARAM LEN | PARAM  | .. | END CMD |
//! |___________|______|______|_________|_________|___________|________|____|_________|
//! |   8 bit   | 1bit | 7bit |  8bit   |  8bit   |   8bit    | nbytes | .. |   8bit  |
//! |___________|______|______|_________|_________|___________|________|____|_________|
//!
//! \return none.
//
//*****************************************************************************
void SpiDrv_SendCmd(uint8_t cmd, uint8_t numParam)
{
    // Send Spi START CMD
    SpiDrv_Transfer(START_CMD);
    
    //wait the interrupt trigger on slave
    DELAY_TRANSFER();
    DELAY_TRANSFER();
    
    // Send Spi C + cmd
    SpiDrv_Transfer(cmd & ~(REPLY_FLAG));
    
    // Send Spi numParam
    SpiDrv_Transfer(numParam);
    
    // Check Param length
    if (numParam == 0)
    {
        SpiDrv_Transfer(END_CMD);
    }
    
}

/*--------------------------- FILE END --------------------------------------*/

