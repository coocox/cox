//*****************************************************************************
//
//! \file WiFiClient.c
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

#include "wl_definitions.h"
//#include "wl_types.h"
#include "WiFi.h"
#include "WiFiClient.h"
#include "server_drv.h"

//static uint16_t _srcport = 1024;
static uint8_t _sock;
//uint8_t getFirstSocket();

static int32_t _ConnectViaHost(uint8_t* host, uint16_t port);
static int32_t _ConnectViaIP(uint8_t* ip, uint16_t port);

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
//! \brief Init the WiFiClient
//!
//! \param sock is the sock you special.
//!
//! \return none.
//
//*****************************************************************************
void WiFiClient_Init(uint8_t sock)
{
    _sock = sock;
}

//*****************************************************************************
//
//! \brief Connect to network via Host
//!
//! \param NetAddr.
//! \param port.
//! ServerAddr can be Host or IP
//! Example:
//! WiFiClient_Connect("www.baidu.com", 80);
//! WiFiClient_Connect("192.168.2.71", 80);
//!
//! \return 0: FAILURE 1:SUCCESS
//
//*****************************************************************************
int32_t WiFiClient_Connect(uint8_t* NetAddr, uint16_t port)
{
    int32_t Result = 0;
    uint8_t _NetAddr[4] = {0, 0, 0, 0};

    // check parameter vaild
    if(NetAddr == NULL)
    {
        return (0);
    }

    if(WiFi_HostToIP(NetAddr, _NetAddr))       // Host
    {
        Result = _ConnectViaHost(NetAddr, port);
    }
    else                                       // IP
    {
        Result = _ConnectViaIP(_NetAddr, port);        
    }

    return (Result);
}

//*****************************************************************************
//
//! \brief Connect to network via Host
//!
//! \param host.
//! \param port.
//!
//! \return 0: FAILURE 1:SUCCESS
//
//*****************************************************************************
static int32_t _ConnectViaHost(uint8_t* host, uint16_t port) 
{
    uint8_t remote_addr[4] = {0, 0, 0, 0};

    if (WiFi_HostToIP(host, remote_addr))
    {
        return _ConnectViaIP(remote_addr, port);
    }
    return (0);
}

//*****************************************************************************
//
//! \brief Connect to network via IP
//!
//! \param ip.
//! \param port.
//!
//! \return 0: FAILURE 1:SUCCESS
//
//*****************************************************************************
static int32_t _ConnectViaIP(uint8_t* ip, uint16_t port) 
{
    int32_t cnt = 50;

    //_sock = WiFi_SocketAvilGet();
    if (_sock != NO_SOCKET_AVAIL)
    {
        ServerDrv_StartClient(*((uint32_t *)ip), port, _sock);
        //_state[_sock] = _sock;

        while(cnt-- > 0)
        {
            if(WiFiClient_Connected())
            {
                break;
            }

            delay(1000);
        }

        if (!WiFiClient_Connected())
        {
            return (0);
        }
    }
    else
    {
        //Serial.println("No Socket available");
        return (0);
    }
    return (1);
}

//*****************************************************************************
//
//! \brief Write an byte to client.
//!
//! \param b is the data you want to write.
//!
//! \return 0: FAILURE others is the number of write.
//
//*****************************************************************************
uint16_t WiFiClient_WriteByte(uint8_t b) 
{
      return WiFiClient_WriteBlock(&b, 1);
}

//*****************************************************************************
//
//! \brief Write Block data to client.
//!
//! \param buf is the buffer of store data.
//! \param size is the length of buffer.
//!
//! \return 0: FAILURE others is the number of write.
//
//*****************************************************************************
uint16_t WiFiClient_WriteBlock(uint8_t *buf, uint16_t size) 
{
    if (_sock >= MAX_SOCK_NUM)
    {
        //setWriteError();
        return (0);
    }
    if (size==0)
    {
        //setWriteError();
        return (0);
    }

    if (!ServerDrv_SendData(_sock, buf, size))
    {
        //setWriteError();
        return (0);
    }
    if (!ServerDrv_CheckDataSent(_sock))
    {
        //setWriteError();
        return (0);
    }

    return (size);
}

//*****************************************************************************
//
//! \brief Check Data status.
//!
//! \param none.
//!
//! \return 
//
//*****************************************************************************
int32_t WiFiClient_Available(void) 
{
    if (_sock != 255)
    {
        return ServerDrv_AvailData(_sock);
    }

    return (0);
}

//*****************************************************************************
//
//! \brief Read byte from client.
//!
//! \param none.
//!
//! \return -1: FAILURE, others is the data.
//
//*****************************************************************************
uint8_t WiFiClient_ReadByte(void) 
{
    uint8_t b;

    if (!WiFiClient_Available())
    {
        return (-1);
    }

    ServerDrv_GetData(_sock, &b, 0);

    return (b);
}

//*****************************************************************************
//
//! \brief Read Block data from client.
//!
//! \param buf is the buffer of store data.
//! \param size is the length of buffer.
//!
//! \return 0: SUCCESS -1: FAILURE.
//
//*****************************************************************************
int32_t WiFiClient_ReadBlock(uint8_t* buf, uint16_t size)
{
    if (!ServerDrv_GetDataBuf(_sock, buf, &size))
    {
        return (-1);
    }
    return (0);
}

//*****************************************************************************
//
//! \brief Peek
//!
//! \param none.
//!
//! \return the Data Get From Client.
//
//*****************************************************************************
int32_t WiFiClient_Peek(void) 
{
    uint8_t b;

    if (!WiFiClient_Available())
    {
        return -1;
    }

    ServerDrv_GetData(_sock, &b, 1);

    return (b);
}

//*****************************************************************************
//
//! \brief Flush the Client data buffer.
//!
//! \param none.
//!
//! \return .
//
//*****************************************************************************
void WiFiClient_Flush(void) 
{
    while (WiFiClient_Available())
    {
        WiFiClient_ReadByte();
    }
}

//*****************************************************************************
//
//! \brief Stop the Client.
//!
//! \param none.
//!
//! \return .
//
//*****************************************************************************
void WiFiClient_Stop(void) 
{
    uint32_t i = 0;

    if (_sock == 255)
    {
        return;
    }

    ServerDrv_StopClient(_sock);

    // wait a second for the connection to close
    while ((WiFiClient_Status() != CLOSED) && (i++ < 1000))
    {
        delay(10);
    }
    _sock = 255;
}

//*****************************************************************************
//
//! \brief Check the client Connected status.
//!
//! \param none.
//!
//! \return the status.
//
//*****************************************************************************
uint8_t WiFiClient_Connected(void) 
{
    uint8_t s = 0;

    if (_sock == 255) 
    {
        return 0;
    }
    else 
    {
        s = WiFiClient_Status();

        return !(s == LISTEN || s == CLOSED || s == FIN_WAIT_1 ||
                s == FIN_WAIT_2 || s == TIME_WAIT ||
                s == SYN_SENT || s== SYN_RCVD ||
                (s == CLOSE_WAIT && !WiFiClient_Available()));
    }
}

//*****************************************************************************
//
//! \brief Get the Client status
//!
//! \param none.
//!
//! \return the status.
//
//*****************************************************************************
uint8_t WiFiClient_Status(void) 
{
    if (_sock == 255) 
    {
        return (CLOSED);
    }
    else 
    {
        return ServerDrv_GetClientState(_sock);
    }
}

/*--------------------------- FILE END --------------------------------------*/
