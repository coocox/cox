//*****************************************************************************
//
//! \file wifi_drv.h
//! \brief Prototypes for Arduino WiFi Shield
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
#ifndef _WiFI_DRV_H_
#define _WiFI_DRV_H_

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

#include <stdint.h>
#include "wifi_spi.h"

// Key index length
#define KEY_IDX_LEN                 1
// 5 secs of delay to have the connection established
#define WL_DELAY_START_CONNECTION   5000
// firmware version string length
#define WL_FW_VER_LENGTH            6

void     WiFiDrv_GetNetworkData(uint8_t *ip, uint8_t *mask, uint8_t *gwip);
void     WiFiDrv_Init(void);
int8_t   WiFiDrv_SetNetwork(uint8_t* ssid, uint8_t ssid_len);
int8_t   WiFiDrv_SetPassphrase(uint8_t* ssid, uint8_t ssid_len, uint8_t *passphrase, uint8_t len);
int8_t   WiFiDrv_SetKey(uint8_t* ssid, uint8_t ssid_len, uint8_t key_idx, uint8_t *key, uint8_t len);
int8_t   WiFiDrv_Disconnect(void);
uint8_t  WiFiDrv_GetConnectionStatus(void);
uint8_t* WiFiDrv_GetMacAddress(void);
void     WiFiDrv_GetIpAddress(uint8_t *ip);
void     WiFiDrv_GetSubnetMask(uint8_t *mask);
void     WiFiDrv_GetGatewayIP(uint8_t *ip);
uint8_t* WiFiDrv_GetCurrentSSID(void);
uint8_t* WiFiDrv_GetCurrentBSSID(void);
int32_t  WiFiDrv_GetCurrentRSSI(void);
uint8_t  WiFiDrv_GetCurrentEncryptionType(void);
int8_t   WiFiDrv_StartScanNetworks(void);
uint8_t  WiFiDrv_GetScanNetworks(void);
uint8_t* WiFiDrv_GetSSIDNetoworks(uint8_t networkItem);
uint8_t  WiFiDrv_GetEncTypeNetowrks(uint8_t networkItem);
int32_t  WiFiDrv_GetRSSINetoworks(uint8_t networkItem);
uint8_t  WiFiDrv_ReqHostByName(uint8_t* aHostname);
int32_t  WiFiDrv_GetHostByName(uint8_t* aHostname, uint8_t *aResult);
uint8_t* WiFiDrv_GetFwVersion(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  //  _WiFI_DRV_H_

