//*****************************************************************************
//
//! \file spi_drv.h
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
#ifndef _SPI_DRV_H_
#define _SPI_DRV_H_

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
#include <stdint.h>
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xspi.h"    
    
#include "wifi_spi.h"

#define NO_LAST_PARAM                  0
#define LAST_PARAM                     1

#define DUMMY_DATA                     0xFF


void     SpiDrv_Init(void);
void     SpiDrv_Stop(void);
void     SpiDrv_SlaveSelect(void);
void     SpiDrv_SlaveDeselect(void);
uint8_t  SpiDrv_Transfer(uint8_t data);
void     SpiDrv_WaitForSlaveReady(void);
int32_t  SpiDrv_WaitChar(uint8_t waitChar);
int32_t  SpiDrv_ReadAndCheckChar(uint8_t checkChar, uint8_t* readChar);
uint8_t  SpiDrv_ReadChar(void);
void     SpiDrv_GetParam(uint8_t* param);
int32_t  SpiDrv_WaitResponseCmd(uint8_t cmd, uint8_t numParam, uint8_t* param, uint8_t* param_len);
int32_t  SpiDrv_WaitResponseData16(uint8_t cmd, uint8_t* param, uint16_t* param_len);
int32_t  SpiDrv_WaitResponseData8(uint8_t cmd, uint8_t* param, uint8_t* param_len);
int32_t  SpiDrv_WaitResponseParams(uint8_t cmd, uint8_t numParam, tParam* params);
int32_t  SpiDrv_WaitResponse(uint8_t cmd, uint8_t* numParamRead, uint8_t** params, uint8_t maxNumParams);
void     SpiDrv_SendParam(uint8_t* param, uint8_t param_len, uint8_t lastParam);
void     SpiDrv_SendParamLen8(uint8_t param_len);
void     SpiDrv_SendParamLen16(uint16_t param_len);
uint8_t  SpiDrv_ReadParamLen8(uint8_t* param_len);
uint16_t SpiDrv_ReadParamLen16(uint16_t* param_len);
void     SpiDrv_SendBuffer(uint8_t* param, uint16_t param_len, uint8_t lastParam);
void     SpiDrv_SendParam16(uint16_t param, uint8_t lastParam);
void     SpiDrv_SendCmd(uint8_t cmd, uint8_t numParam);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //__SPI_DRV_H_

