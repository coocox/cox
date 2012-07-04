//*****************************************************************************
// 
//! \file adt75.h
//! \brief Temperature Sensor (AD7416) and Four Single-Channel ADC drver
//! \version 1.0
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

#ifndef __I2C_TEMP_ADT75_H__
#define __I2C_TEMP_ADT75_H__

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
//! \addtogroup Sensor
//! @{  
//! \addtogroup Temperature_Sensor
//! @{
//! \addtogroup ADT75
//! @{  
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup ADT75_Application_CON ADT75 Application Configures
//! \brief ADT75 Device config, here must be configured before use the API.
//! @{
//
//*****************************************************************************

//
//! Config the device i2c Address
//
#define ADT75_I2C_ADDRESS       0x48

//
//! Config the devide i2c bus master
//
#define ADT75_MASTER_BASE       xI2C0_BASE

//
//! Config the i2c0 SDA pin
// 
#define ADT75_PIN_I2CSDA        PA8
 
//
//! Config the i2c0 SCL pin
//
#define ADT75_PIN_I2CSCK        PA9
  
//
//! Config the OTI connect pin
// 
#define ADT75_PIN_OS            PB13

//
//! Config the OS/Alert active level
//
#define ADT75_LEVEL_OS         xGPIO_LOW_LEVEL  

//*****************************************************************************
//
//! @}
//
//*****************************************************************************  
  
//*****************************************************************************
//
//! \addtogroup ADT75_Device_Init Devide init mode configure
//! \brief The value can be passed to ADT75Init function
//! @{
//
//*****************************************************************************

//
//! Shut down mode 
//
#define ADT75_POWER_SHOTDOWN    0x00000001

//
//! Normal mode (default mode)
//
#define ADT75_POWER_NORMAL      0x00000000

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 
  
//*****************************************************************************
//
//! \addtogroup ADT75_Int_Mode_Con Temperature Int Mode Configure
//! \brief Select the Int mode, these can be passed to ADT75IntModeConfig()
//! @{
//
//*****************************************************************************

//
//! Select the compare mode
//
#define ADT75_OPEMODE_CMP       0x00000000

//
//! Select the int mode
//
#define ADT75_OPEMODE_INT       0x00000002
                                
//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup ADT75_OSAlert_Pin_Polarity OSAlert Pin Polarity
//! \brief OS/ALERT Pin Polarity select, these value can be passed to 
//! ADT75OSActiveLevelConfig() function. 
//! @{
//
//*****************************************************************************
//
//! Select OS/ALERT polarity active low 
//
#define ADT75_OSALERT_LEVEL_LOW 0x00000000

//
//! Select OS/ALERT polarity active high
//
#define ADT75_OSALERT_LEVEL_HIGH                                              \
                                0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************  
  
//*****************************************************************************
//
//! \addtogroup ADT75_OverTemp_Fault_Queue OverTemp Fault Queue
//! \brief Over temperature fault queue, these value can be passed to 
//! ADT75FaultQueueConfig().  
//! @{
//
//*****************************************************************************

//
//! Set the Queue num
//
#define ADT75_FAULTQUE_1        0x00000000
#define ADT75_FAULTQUE_2        0x00000008
#define ADT75_FAULTQUE_4        0x00000010
#define ADT75_FAULTQUE_6        0x00000018

//*****************************************************************************
//
//! @}
//
//*****************************************************************************  

//*****************************************************************************
//
//! \addtogroup ADT75_SMBus_Alert_Con  SMBus Alert Configure
//! \brief SMBus Alert configure, these value can be passed to ADT75AlertConfig()
//! @{
//
//*****************************************************************************

//
//! Enable SMBus alert function
//
#define ADT75_ALERT_ENABLE      0x00000080

//
//! Disable SMBus alert function
//
#define ADT75_ALERT_DISABLE     0x00000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************
  
//*****************************************************************************
//
//! \addtogroup ADT75_APIs ADT75 APIs
//! @{
//
//*****************************************************************************
  
extern void ADT75Init(unsigned long ulRate, unsigned long ulMode);

extern void ADT75ShutDown(void);
extern void ADT75WakeUp(void);

extern void ADT75IntModeConfig(unsigned long ulIntMode);
extern void ADT75OSActiveLevelConfig(unsigned long ulOSLevel);
extern void ADT75FaultQueueConfig(unsigned long ulFaultQueue);
extern void ADT75AlertConfig(unsigned long ulSMBusAlert);

extern void ADT75OneShotEnable(void);
extern void ADT75OneShotDisable(void);
extern void ADT75OneShotConvst(void);

extern void ADT75UpLimitSetFloat(float fTemp);
extern void ADT75UpLimitSetLong(long lTemp);
extern void ADT75LowLimitSetFloat(float fTemp);
extern void ADT75LowLimitSetLong(long lTemp);

extern long ADT75TempReadLDC(void);
extern long ADT75TempReadMSB10Bit(void);
extern float ADT75TempReadFDC(void);

extern void ADT75IntEnable(void);
extern void ADT75IntDisable(void);
extern void ADT75IntCallbackInit(xtEventCallback xtI2CCallback);

extern void ADT75DeInit(void);
//
// If the ADT75 API can not meet your need, you can use the API below operated 
// on the lowlayer.
//
extern long ADT75RegRead (unsigned char ucReg);  
extern long ADT75RegWrite(unsigned char ucReg, short ulValue);

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

