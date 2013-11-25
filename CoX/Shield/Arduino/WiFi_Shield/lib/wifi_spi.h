//*****************************************************************************
//
//! \file wifi_spi.h
//! \brief define types for Arduino WiFi Shield
//! \version 2.1.1.0
//! \date 20/02/2013
//! \author CooCoX
//! \copy
//!
//! Copyright (c)  2013, CooCoX
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
#ifndef _WIFI_SPI_H
#define _WIFI_SPI_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#include "wl_definitions.h"

#define CMD_FLAG            0
#define REPLY_FLAG          1<<7
#define DATA_FLAG           0x40

#define WIFI_SPI_ACK        1
#define WIFI_SPI_ERR        0xFF

#define TIMEOUT_CHAR        1000

//#define   MAX_SOCK_NUM        4   /**< Maxmium number of socket  */
#define NO_SOCKET_AVAIL     255

#define START_CMD           0xE0
#define END_CMD             0xEE
#define ERR_CMD             0xEF

enum {
    SET_NET_CMD              = 0x10,
    SET_PASSPHRASE_CMD       = 0x11,
    SET_KEY_CMD              = 0x12,
    TEST_CMD                 = 0x13,

    GET_CONN_STATUS_CMD      = 0x20,
    GET_IPADDR_CMD           = 0x21,
    GET_MACADDR_CMD          = 0x22,
    GET_CURR_SSID_CMD        = 0x23,
    GET_CURR_BSSID_CMD       = 0x24,
    GET_CURR_RSSI_CMD        = 0x25,
    GET_CURR_ENCT_CMD        = 0x26,
    SCAN_NETWORKS            = 0x27,
    START_SERVER_TCP_CMD     = 0x28,
    GET_STATE_TCP_CMD        = 0x29,
    DATA_SENT_TCP_CMD        = 0x2A,
    AVAIL_DATA_TCP_CMD       = 0x2B,
    GET_DATA_TCP_CMD         = 0x2C,
    START_CLIENT_TCP_CMD     = 0x2D,
    STOP_CLIENT_TCP_CMD      = 0x2E,
    GET_CLIENT_STATE_TCP_CMD = 0x2F,
    DISCONNECT_CMD           = 0x30,
    GET_IDX_SSID_CMD         = 0x31,
    GET_IDX_RSSI_CMD         = 0x32,
    GET_IDX_ENCT_CMD         = 0x33,
    REQ_HOST_BY_NAME_CMD     = 0x34,
    GET_HOST_BY_NAME_CMD     = 0x35,
    START_SCAN_NETWORKS      = 0x36,
    GET_FW_VERSION_CMD       = 0x37,

    // All command with DATA_FLAG 0x40 send a 16bit Len

    SEND_DATA_TCP_CMD       = 0x44,
    GET_DATABUF_TCP_CMD     = 0x45,
};


enum wl_tcp_state
{
  CLOSED      = 0,
  LISTEN      = 1,
  SYN_SENT    = 2,
  SYN_RCVD    = 3,
  ESTABLISHED = 4,
  FIN_WAIT_1  = 5,
  FIN_WAIT_2  = 6,
  CLOSE_WAIT  = 7,
  CLOSING     = 8,
  LAST_ACK    = 9,
  TIME_WAIT   = 10
};


enum numParams
{
    PARAM_NUMS_0,
    PARAM_NUMS_1,
    PARAM_NUMS_2,
    PARAM_NUMS_3,
    PARAM_NUMS_4,
    PARAM_NUMS_5,
    MAX_PARAM_NUMS
};

#define MAX_PARAMS MAX_PARAM_NUMS-1
#define PARAM_LEN_SIZE 1

typedef struct
{
    uint8_t     paramLen;
    uint8_t*    param;
}tParam;

typedef struct
{
    uint16_t    dataLen;
    uint8_t*    data;
}tDataParam;


typedef struct
{
    uint8_t     cmd;
    uint8_t     tcmd;
    uint8_t     nParam;
    tParam      params[MAX_PARAMS];
}tSpiMsg;

typedef struct
{
    uint8_t     cmd;
    uint8_t     tcmd;
    uint8_t     nParam;
    tDataParam  params[MAX_PARAMS];
}tSpiMsgData;


typedef struct
{
    uint8_t     cmd;
    uint8_t     tcmd;
    //uint8_t   totLen;
    uint8_t     nParam;
}tSpiHdr;

typedef struct
{
    uint8_t     paramLen;
    uint32_t    param;
}tLongParam;

typedef struct
{
    uint8_t     paramLen;
    uint16_t    param;
}tIntParam;

typedef struct
{
    uint8_t     paramLen;
    uint8_t     param;
}tByteParam;

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // _WIFI_SPI_H

