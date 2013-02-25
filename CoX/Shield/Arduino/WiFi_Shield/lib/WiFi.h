//*****************************************************************************
//
//! \file WiFi.h
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
#ifndef _WIFI_H_
#define _WIFI_H_

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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

#include "spi_drv.h"
#include "wifi_drv.h"
#include "WiFiClient.h"

// Network encrytion type
// used in WiFiBegin Function
#define OPEN                    1
#define WEP                     2
#define WPA                     3

#define CURRENT                 ((uint8_t)(-1))

void     WiFi_Init(void);
uint8_t  WiFi_PortAvilGet(void);
uint8_t* WiFi_FwVerGet(void);
int32_t  WiFi_Begin(uint8_t NetType, uint8_t* ssid, ...);
int8_t   WiFi_Disconnect(void);
uint8_t* WiFi_MacAddrGet(uint8_t* mac);
void     WiFi_LocalIPGet(uint8_t * ip);
void     WiFi_SubnetMaskGet(uint8_t * mask);
void     WiFi_GatewayIPGet(uint8_t * gateway);
uint8_t* WiFi_BSSIDGet(uint8_t* bssid);
int8_t   WiFi_ScanNetworks(void);
uint8_t* WiFi_SSIDGet(uint8_t networkItem);
uint8_t  WiFi_EncryptionTypeGet(uint8_t networkItem);
int32_t  WiFi_RSSIGet(uint8_t networkItem);
uint8_t  WiFi_StatusGet(void);
int32_t  WiFi_HostToIP(uint8_t* aHostname, uint8_t * aResult);
int32_t  IPToNetAddr(uint8_t* IPStr, uint8_t * NetAddr);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  _WIFI_H_
