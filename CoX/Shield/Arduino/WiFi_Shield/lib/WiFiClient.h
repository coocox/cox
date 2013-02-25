//*****************************************************************************
//
//! \file WiFiClient.h
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
#ifndef _WIFICLIENT_H_
#define _WIFICLIENT_H_

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
#include <stdint.h>

void     WiFiClient_Init(uint8_t sock);
int32_t  WiFiClient_Connect(uint8_t* NetAddr, uint16_t port);
uint16_t WiFiClient_WriteByte(uint8_t b);
uint16_t WiFiClient_WriteBlock(uint8_t *buf, uint16_t size);
int32_t  WiFiClient_Available(void);
uint8_t  WiFiClient_ReadByte(void);
int32_t  WiFiClient_ReadBlock(uint8_t* buf, uint16_t size);
int32_t  WiFiClient_Peek(void);
void     WiFiClient_Flush(void);
void     WiFiClient_Stop(void);
uint8_t  WiFiClient_Connected(void);
uint8_t  WiFiClient_Status(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //_WIFICLIENT_H_

