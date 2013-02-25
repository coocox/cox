//*****************************************************************************
//
//! \file server_drv.c
//! \brief Control for Sensor Shield.
//! \version 2.1.1.0
//! \date 08/11/2012
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

#include "server_drv.h"
#include "spi_drv.h"

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

//*****************************************************************************
//
//! \brief Start server TCP on port specified
//!
//! \param port is the listen port.
//! \param sock is the servver ID.
//! 
//! \return none.
//
//*****************************************************************************
void ServerDrv_StartServer(uint16_t port, uint8_t sock)
{

    uint8_t _data    = 0;
    uint8_t _dataLen = 0;

    //WAIT_FOR_SLAVE_SELECT();
    SpiDrv_WaitForSlaveReady();
    SpiDrv_SlaveSelect();

    // Send Command
    SpiDrv_SendCmd(START_SERVER_TCP_CMD, PARAM_NUMS_2);
    SpiDrv_SendParam16(port, NO_LAST_PARAM);
    SpiDrv_SendParam(&sock, 1, LAST_PARAM);

    //Wait the reply elaboration
    SpiDrv_WaitForSlaveReady();

    // Wait for reply
    if (!SpiDrv_WaitResponseCmd(START_SERVER_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        //WARN("error waitResponse");
    }
    SpiDrv_SlaveDeselect();
}

//*****************************************************************************
//
//! \brief Start client on port specified
//!
//! \param ipAddress is the target IP adress.
//! \param port is the listen port.
//! \param sock is the servver ID.
//! 
//! \return none.
//
//*****************************************************************************
void ServerDrv_StartClient(uint32_t ipAddress, uint16_t port, uint8_t sock)
{
    uint8_t _data    = 0;
    uint8_t _dataLen = 0;

    //WAIT_FOR_SLAVE_SELECT();
    SpiDrv_WaitForSlaveReady();
    SpiDrv_SlaveSelect();

    // Send Command
    SpiDrv_SendCmd(START_CLIENT_TCP_CMD, PARAM_NUMS_3);
    SpiDrv_SendParam((uint8_t*)&ipAddress, sizeof(ipAddress), NO_LAST_PARAM);
    SpiDrv_SendParam16(port, NO_LAST_PARAM);
    SpiDrv_SendParam(&sock, 1, LAST_PARAM);

    //Wait the reply elaboration
    SpiDrv_WaitForSlaveReady();

    // Wait for reply
    if (!SpiDrv_WaitResponseCmd(START_CLIENT_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        //WARN("error waitResponse");
    }
    SpiDrv_SlaveDeselect();
}

//*****************************************************************************
//
//! \brief stop client
//!
//! \param sock.
//! 
//! \return none.
//
//*****************************************************************************
void ServerDrv_StopClient(uint8_t sock)
{
    uint8_t _data    = 0;
    uint8_t _dataLen = 0;

    //WAIT_FOR_SLAVE_SELECT();
    SpiDrv_WaitForSlaveReady();
    SpiDrv_SlaveSelect();

    // Send Command
    SpiDrv_SendCmd(STOP_CLIENT_TCP_CMD, PARAM_NUMS_1);
    SpiDrv_SendParam(&sock, 1, LAST_PARAM);

    //Wait the reply elaboration
    SpiDrv_WaitForSlaveReady();

    // Wait for reply
    if (!SpiDrv_WaitResponseCmd(STOP_CLIENT_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        //WARN("error waitResponse");
    }
    SpiDrv_SlaveDeselect();
}

//*****************************************************************************
//
//! \brief check server state
//!
//! \param sock is the server id you want to check.
//! 
//! \return the state of special server.
//
//*****************************************************************************
uint8_t ServerDrv_GetServerState(uint8_t sock)
{
    uint8_t _data    = 0;
    uint8_t _dataLen = 0;

    //WAIT_FOR_SLAVE_SELECT();
    SpiDrv_WaitForSlaveReady();
    SpiDrv_SlaveSelect();

    // Send Command
    SpiDrv_SendCmd(GET_STATE_TCP_CMD, PARAM_NUMS_1);
    SpiDrv_SendParam(&sock, 1, LAST_PARAM);

    //Wait the reply elaboration
    SpiDrv_WaitForSlaveReady();

    // Wait for reply
    if (!SpiDrv_WaitResponseCmd(GET_STATE_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        //WARN("error waitResponse");
    }
    SpiDrv_SlaveDeselect();

    return (_data);
}


//*****************************************************************************
//
//! \brief check client state
//!
//! \param sock is the client id you want to check.
//! 
//! \return the state of special client.
//
//*****************************************************************************
uint8_t ServerDrv_GetClientState(uint8_t sock)
{
    uint8_t _data    = 0;
    uint8_t _dataLen = 0;

    //WAIT_FOR_SLAVE_SELECT();
    SpiDrv_WaitForSlaveReady();
    SpiDrv_SlaveSelect();
    // Send Command
    SpiDrv_SendCmd(GET_CLIENT_STATE_TCP_CMD, PARAM_NUMS_1);
    SpiDrv_SendParam(&sock, 1, LAST_PARAM);

    //Wait the reply elaboration
    SpiDrv_WaitForSlaveReady();

    // Wait for reply
    if (!SpiDrv_WaitResponseCmd(GET_CLIENT_STATE_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        //WARN("error waitResponse");
    }
    SpiDrv_SlaveDeselect();

    return (_data);
}

//*****************************************************************************
//
//! \brief check data state.
//!
//! \param sock is the client id you want to check.
//! 
//! \return 1: data is available 0: not available now.
//
//*****************************************************************************
int32_t ServerDrv_AvailData(uint8_t sock)
{
    uint8_t _data    = 0;
    uint8_t _dataLen = 0;

    //WAIT_FOR_SLAVE_SELECT();
    SpiDrv_WaitForSlaveReady();
    SpiDrv_SlaveSelect();

    // Send Command
    SpiDrv_SendCmd(AVAIL_DATA_TCP_CMD, PARAM_NUMS_1);
    SpiDrv_SendParam(&sock, sizeof(sock), LAST_PARAM);

    //Wait the reply elaboration
    SpiDrv_WaitForSlaveReady();

    // Wait for reply
    if (!SpiDrv_WaitResponseCmd(AVAIL_DATA_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
    {
        //WARN("error waitResponse");
    }
    SpiDrv_SlaveDeselect();

    if (_dataLen!=0)
    {
        return (_data == 1);
    }
    return (0);
}

//*****************************************************************************
//
//! \brief get data on special port
//!
//! \param sock is the socket you want to check.
//! \param data is the buffer store the data.
//! \param peek.
//! 
//! \return 1: get the data, 0: not get the data.
//
//*****************************************************************************
int32_t ServerDrv_GetData(uint8_t sock, uint8_t *data, uint8_t peek)
{
    uint8_t _data    = 0;
    uint8_t _dataLen = 0;

    //WAIT_FOR_SLAVE_SELECT();
    SpiDrv_WaitForSlaveReady();
    SpiDrv_SlaveSelect();

    // Send Command
    SpiDrv_SendCmd(GET_DATA_TCP_CMD, PARAM_NUMS_2);
    SpiDrv_SendParam(&sock, 1, NO_LAST_PARAM);
    //NOTE check this @cedar
    SpiDrv_SendParam16(peek, LAST_PARAM);

    //Wait the reply elaboration
    SpiDrv_WaitForSlaveReady();

    // Wait for reply
    if (!SpiDrv_WaitResponseData8(GET_DATA_TCP_CMD, &_data, &_dataLen))
    {
        //WARN("error waitResponse");
    }
    SpiDrv_SlaveDeselect();
    if (_dataLen!=0)
    {
        *data = _data;
        return (1);
    }
    return (0);
}

//*****************************************************************************
//
//! \brief get data on special port
//!
//! \param sock is the socket you want to check.
//! \param _data is the buffer store the data.
//! \param _datalen is the length of read data.
//! 
//! \return 1: get the data, 0: not get the data.
//
//*****************************************************************************
int32_t ServerDrv_GetDataBuf(uint8_t sock, uint8_t *_data, uint16_t *_dataLen)
{
    //WAIT_FOR_SLAVE_SELECT();
    SpiDrv_WaitForSlaveReady();
    SpiDrv_SlaveSelect();

    // Send Command
    SpiDrv_SendCmd(GET_DATABUF_TCP_CMD, PARAM_NUMS_1);
    SpiDrv_SendBuffer(&sock, 1, LAST_PARAM);

    //Wait the reply elaboration
    SpiDrv_WaitForSlaveReady();

    // Wait for reply
    if (!SpiDrv_WaitResponseData16(GET_DATABUF_TCP_CMD, _data, _dataLen))
    {
        //WARN("error waitResponse");
    }

    SpiDrv_SlaveDeselect();
    if (*_dataLen!=0)
    {
        return (1);
    }
    return (0);
}

//*****************************************************************************
//
//! \brief send data to special port
//!
//! \param sock is the socket you want to send.
//! \param data is the buffer store the data.
//! \param datalen is the length of read data.
//! 
//! \return 1: send the data, 0: not send the data.
//
//*****************************************************************************
int32_t ServerDrv_SendData(uint8_t sock, uint8_t *data, uint16_t len)
{
    uint8_t _data    = 0;
    uint8_t _dataLen = 0;

    //WAIT_FOR_SLAVE_SELECT();
    SpiDrv_WaitForSlaveReady();
    SpiDrv_SlaveSelect();

    // Send Command
    SpiDrv_SendCmd(SEND_DATA_TCP_CMD, PARAM_NUMS_2);
    SpiDrv_SendBuffer(&sock, 1, NO_LAST_PARAM);
    SpiDrv_SendBuffer((uint8_t *)data, len, LAST_PARAM);

    //Wait the reply elaboration
    SpiDrv_WaitForSlaveReady();

    // Wait for reply
    if (!SpiDrv_WaitResponseData8(SEND_DATA_TCP_CMD, &_data, &_dataLen))
    {
        //WARN("error waitResponse");
    }
    SpiDrv_SlaveDeselect();
    if (_dataLen!=0)
    {
        return (_data == 1);
    }
    return (0);
}

//*****************************************************************************
//
//! \brief check the data whether has beed sended.
//!
//! \param sock is the socket you want to send.
//! 
//! \return 1: send , 0: not send
//
//*****************************************************************************
int32_t ServerDrv_CheckDataSent(uint8_t sock)
{
    uint16_t timeout = 0;
    uint8_t _data    = 0;
    uint8_t _dataLen = 0;
    const uint16_t TIMEOUT_DATA_SENT = 25;

    do
    {
        //WAIT_FOR_SLAVE_SELECT();
        SpiDrv_WaitForSlaveReady();
        SpiDrv_SlaveSelect();

        // Send Command
        SpiDrv_SendCmd(DATA_SENT_TCP_CMD, PARAM_NUMS_1);
        SpiDrv_SendParam(&sock, sizeof(sock), LAST_PARAM);

        //Wait the reply elaboration
        SpiDrv_WaitForSlaveReady();

        // Wait for reply
        if (!SpiDrv_WaitResponseCmd(DATA_SENT_TCP_CMD, PARAM_NUMS_1, &_data, &_dataLen))
        {
            //WARN("error waitResponse isDataSent");
        }
        SpiDrv_SlaveDeselect();

        if (_data)
        {
            timeout = 0;
        }
        else
        {
            ++timeout;
            delay(100);
        }

    }while((_data==0)&&(timeout<TIMEOUT_DATA_SENT));

    if(timeout==TIMEOUT_DATA_SENT)
    {
        return (0);
    }
    else
    {
        return (1);
    }
}

/*--------------------------- FILE END --------------------------------------*/

