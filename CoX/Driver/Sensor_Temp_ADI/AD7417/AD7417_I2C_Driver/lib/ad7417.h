//*****************************************************************************
// 
//! \file di_ad7417.h
//! \brief Temperature Sensor (AD7416) and Four Single-Channel ADC drver
//! \version V2.1.1.0
//! \date 25. Aug. 2011
//! \author CooCox
//!
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

#ifndef __I2C_TEMP_AD7417_H__
#define __I2C_TEMP_AD7417_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this heADer
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup CoX_Driver_Lib
//! @{
//! \addtogruop Sensor
//! @{  
//! \addtogroup Temperature_Sensor
//! @{
//! \addtogroup AD7417
//! @{  
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup AD7417_Mode_Config AD7417 Mode Config
//! \brief Values that to config the AD7417 mode, it can be transfer into
//!  AD7417Init().  
//! @{
//
//*****************************************************************************

//
//! Enable the shut down mode
//  
#define AD7417_ShutDown_Enable  0x00000001
  
//
//! Disable the shut down mode
// 
#define AD7417_ShutDown_Disable 0x00000000   
  
//
//! Enable the triger mode
//  
#define AD7417_Triger_Enable    0x00000080  
  
//
//! Disable the triger mode
//  
#define AD7417_Triger_Disable   0x00000000
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************  
  
//*****************************************************************************
//
//! \addtogroup AD7417_ADC_Channel_Select AD7417 ADC Channel Select
//! \brief Select the ADC channel, it can be pass to the AD7417ADConfig()  
//! @{
//  
//***************************************************************************** 

//
//! ADC convert channel select
//  
#define AD7417_ADC_Channel1     0x00000020
#define AD7417_ADC_Channel2     0x00000040
#define AD7417_ADC_Channel3     0x00000060
#define AD7417_ADC_Channel4     0x00000080  
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************  

//*****************************************************************************
//
//! \addtogroup AD7417_TempGet_Config AD7417 TempGet Config
//! \brief The value can be transfered  to AD7417TempGetConfig()
//! @{
//
//*****************************************************************************  
 
//
//! OTI operation mode
//  
#define AD7417_OTI_CMP          0x00000000
#define AD7417_OTI_INT          0x00000002

//
//! OTI output active value
//  
#define AD7417_OTI_ACTIVE_LOW   0x00000000
#define AD7417_OTI_ACTIVE_HIGH  0x00000004

//
//! Fault queue value
//  
#define AD7417_FAULTQUE_1       0x00000000
#define AD7417_FAULTQUE_2       0x00000008
#define AD7417_FAULTQUE_4       0x00000010
#define AD7417_FAULTQUE_6       0x00000018  
  
//
//! Temperature channel 
//  
#define AD7417_TEMP_CHANNEL     0x00000000  
  
//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup AD7417_Filter_Config AD7417 Filter Config
//! \brief The value can be transfered  to AD7417I2CFilterConfig()  
//! @{
//
//*****************************************************************************    
 
//
//! Filter config
//
#define AD7417_FILTER_ENABLE    0x00000000
#define AD7417_FILTER_DISABLE   0x00000040  
  
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup AD7417_APIs AD7417 APIs
//! @{
//
//*****************************************************************************
  
extern void AD7417Init(unsigned long ulRate, unsigned long ulMode);

extern void AD7417UpLimitSetFloat(float fTemp);
extern void AD7417UpLimitSetLong(short lTemp);
extern void AD7417LowLimitSetFloat(float fTemp);
extern void AD7417LowLimitSetLong(short lTemp);

extern void AD7417TempConfig(unsigned char ucCfg);
extern void AD7417OTIntEnable(void);
extern void AD7417OTIntDisable(void);
extern void AD7417OTIntCallbackInit(xtEventCallback xtI2CCallback);
extern long AD7417TempReadLDC(void);
extern long AD7417TempReadMSB10Bit(void);
extern float AD7417TempReadFDC(void);

extern void AD7417ADConfig(unsigned short ucCfg);
extern unsigned long AD7417ADCRead(void);

extern void AD7417ShutdownEnable(void);
extern void AD7417ShutdownDisable(void);
extern void AD7417ShutDownConvst(void);

extern void AD7417TriggerEnable(void);
extern void AD7417TriggerDisable(void);
extern void AD7417TriggerConvst(void);

extern void AD7417I2CFilterConfig( short ucTest);

extern void AD7417Reset(void);
extern void AD7417DeInit(void);

//
// If the AD7417 API can not meet your need, you can use the API below operated 
// on the lowlayer.
//
extern short AD7417RegRead (unsigned char ucReg);  
extern void AD7417RegWrite(unsigned char ucReg, short ulValue);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup AD7417_Application_Configs AD7417 Application Configs
//! \brief It is Static preach, the 4 macros must be define with the right value
//! according your application before use the APIS.
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! AD7417 Device config ,here must be configured before use the API.
//
//*****************************************************************************

//
//! Config the device i2c Address
//
#define AD7417Addr             0x28

//
//! Config the devide i2c bus master
//
#define AD7417MasterBase       I2C0_BASE

//
//! Config the i2c0 SDA pin
//
#define AD7417_I2C0_SDA        PA8

//
//! Config the i2c0 SCL pin
//
#define AD7417_I2C0_SCL        PA9

//
//! Config the i2c1 SDA pin
//
#define AD7417_I2C1_SDA        PA10

//
//! Config the i2c1 SCL pin
//
#define AD7417_I2C1_SCL        PA11

//
//! Config the OTI connect pin
// 
#define AD7417_OTI_PIN         PB13

//
//! Config the OTI active level
//
#define AD7417_OTI_ACTIVE      xGPIO_LOW_LEVEL

// 
//! Config the /Convst pin
//
#define AD7417_CONVST_PIN      PC4

//*****************************************************************************
//
//! @}
//
//*****************************************************************************



//*****************************************************************************
//
//! @}
//! @}
//! @}
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif

