//*****************************************************************************
//
//! \file MCP98242_3.h
//! \brief header file of Driver for MCP98242_3
//! \version 1.0
//! \date 8/25/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox All rights reserved.
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

#include "xhw_types.h"
#include "xi2c.h"
#include "xhw_MCP98242_3.h"

#ifndef __MCP98242_3_H__
#define __MCP98242_3_H__

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

//*****************************************************************************
//
//! \addtogroup COX_Driver_Lib
//! @{
//! \addtogroup Sensor 
//! @{
//! \addtogroup Temperature_Sensor 
//! @{
//! \addtogroup MCP98242_3_TempSensor_EEPROM 
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242_3_Driver MCP98242_3 Driver
//! MCP98242_3 Driver.
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242_3_Peripheral_Config MCP98242_3 Peripheral Config
//! Enable and Set I2C, and related GPIO Pins.
//! @{
//
//*****************************************************************************

typedef struct
{
    unsigned long  I2CBase;        // I2C Base
    unsigned long  SensorSlaAddr;  // Temperature Sensor Slave Address
    unsigned long  EEPROMSlaAddr;  // EEPROM Slave Address
    unsigned long  PWPSlaAddr;     // PWP Slave Address
    unsigned long  EventPort;      // Event Pin Port
    unsigned long  EventPin;       // Event Pin 
    unsigned long  EventIntVec;    // Event Interrupt ID

    //
    // pinSet Function:
    //      1. Enable GPIO Clock 
    //      2. Set GPIO Pin Funciton
    //
    void (*pinSet)(void);

}MCP98242_3Dev;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup MCP98242_3_Capability  MCP98242_3 Capability
//! @{
//
//*****************************************************************************

//
//! Temperature Accuracy: ¡À1¡ãC from +75¡ãC to +95¡ãC (Active Range) and 
//! ¡À2¡ãC from +40¡ãC to +125¡ãC.
//
#define   MCP98242_3_ACR_1    0x00000002

//
//! Temperature Accuracy: ¡À2¡ãC from +75¡ãC to +95¡ãC (Active Range) and 
//! ¡À3¡ãC from +40¡ãC to +125¡ãC.
//
#define   MCP98242_3_ACR_2    0x00000000

//
//! Temperature Measurement Range: The part can measure 
//! temperature below 0¡ãC (power-up default).
//
#define   MCP98242_3_MEAS_1  0x00000004

//
//! TA = 0 (decimal) for temperature below 0¡ãC 
//
#define   MCP98242_3_MEAS_2  0x00000000

#ifdef   MCP98243

//
//! Pin A0 accepts High Voltage for the EEPROM Write Protect 
//! feature (power-up default).
//
#define   MCP98242_3_HV     0x00000020

//
//! Pin A0 does not accept High Voltage.
//
#define   MCP98242_3_HV_NO     0x00000000

//
//! Bus time-out range is 25 ms to 35 ms.
//
#define   MCP98242_3_TOUT_1   0x00000040

//
//! Bus time-out range is 10 ms to 60 ms.
//
#define   MCP98242_3_TOUT_2   0x00000000

//
//! Event output de-asserts during shutdown. After shutdown, 
//! it takes T_CONV to re-assert the Event output (power-up default)
//
#define   MCP98242_3_SHDN_DE   0x00000080

//
//! Event output remains in previous state.  If the output asserts before 
//! shutdown command, it remains asserted during shutdown.
//
#define   MCP98242_3_SHDN_PRE   0x00000000

#endif

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242_3_Event_Conf  MCP98242_3 Event Config
//! Set Event Output Mode.
//! @{
//
//*****************************************************************************

//
//! Set Event Output Mode as Comparator output(power-up default)
//
#define  EVENT_COMP      0

//
//! Set Event Output Mode as interrupt output
//
#define  EVENT_INT       1

//
//! Event Output Select: for T_UPPER, T_LOWER and T_CRIT (power-up default)
//
#define  EVENT_SEL_ALL    0x0000

//
//! Event Output Select: T_A ¡Ý T_CRIT only.
//
#define  EVENT_SEL_CRIT   0x0004

//
//! Event Output Polarity: Active-high.
//
#define   EVENT_HIGH_LEVEL      0x00000002

//
//! Event Output Polarity: Active low.
//
#define   EVENT_LOW_LEVEL       0x00000000

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup MCP98242_3_LimitLock  MCP98242_3 Limit Lock
//! Config Limit Temperature Lock Bit
//! @{
//
//*****************************************************************************

#define  LOCK_M        0x00C0    //Lock Bits Mask
#define  CRIT_LOCK     0x0080    //Lock T_CRIT Bit
#define  CRIT_UNLOCK   0x0000    //Unlock T_CRIT Bit
#define  WIN_LOCK      0x0040    //Lock the T_UPPER and T_LOWER Window
#define  WIN_UNLOCK    0x0000    //Unock the T_UPPER and T_LOWER Window

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup MCP98242_3_Event_Condition  MCP98242_3 Event Condition
//! Enable and Set I2C, and related GPIO Pins.
//! @{
//
//*****************************************************************************

//
//! T_A >= T_LOWER OR T_A <= T_UPPER - T_HYST
//
#define  EVENT_COND_1      0

//
//! T_A < T_LOWER - T_HYST
//
#define  EVENT_COND_2      1

//
//! T_A > T_UPPER OR T_A < T_CRIT - T_HYST
//
#define  EVENT_COND_3      2
//
//! T_A >= T_CRIT
//
#define  EVENT_COND_4      6

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242_3_TempSensor_Mode  MCP98242_3 Temp-Sensor Mode
//! MCP98242_3 Temperature Sensor Mode.
//! @{
//
//*****************************************************************************

//
//! Set to be Continuous Mode
//
#define   MCP98242_3_SEN_CONTI  0

//
//! Set to be Shut Down Mode
//
#define   MCP98242_3_SEN_SHDN   1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup MCP98242_3_TempSensor_Res MCP98242_3 Temp-Sensor Res
//! MCP98242_3 Temperature Sensor Resolution.
//! @{
//
//*****************************************************************************

//
//! Set the Temperature Sensor Resolution to be 0.5¡æ
//
#define   RESOLUTION_5     0x00000000

//
//! Set the Temperature Sensor Resolution to be 0.25¡æ
//
#define   RESOLUTION_25    0x00000001

//
//! Set the Temperature Sensor Resolution to be 0.125¡æ
//
#define   RESOLUTION_125   0x00000002

//
//! Set the Temperature Sensor Resolution to be 0.0625¡æ
//
#define   RESOLUTION_0625  0x00000003

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup MCP98242_3_TempSensor_Hyst  MCP98242_3 TempSensor Hyst
//! MCP98242_3 Temperature Sensor Hysteresis.
//! @{
//
//*****************************************************************************

//
//! The Hysteresis Offset
//
#define   HYSTERESIS_S     0x00000009

//
//! The Mask of Hysteresis
//
#define   HYSTERESIS_M     0x00000600

//
//! Set the Temperature Sensor Resolution to be 0¡æ
//
#define   HYSTERESIS_0      0x00000000

//
//! Set the Temperature Sensor Resolution to be 1.5¡æ
//
#define   HYSTERESIS_1_5    0x00000200

//
//! Set the Temperature Sensor Resolution to be 3¡æ 
//
#define   HYSTERESIS_3      0x00000400

//
//! Set the Temperature Sensor Resolution to be 6¡æ 
//
#define   HYSTERESIS_6      0x00000600

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242_3_MCP98242_3_ID  MCP98242_3 MCP98242_3 ID
//! @{
//
//*****************************************************************************
typedef struct{
    unsigned short  MANU_ID;
    unsigned char  REVISION;
    unsigned char  DEV_ID;
}MCP98242_3_ID;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************  


//*****************************************************************************
//
//! \addtogroup MCP98242_3_APIs MCP98242_3 APIs
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242_3_TempSen_APIs
//! @{
//
//*****************************************************************************

void  MCP98242_3RegSet(MCP98242_3Dev *pDev, void *vpValue, 
                        unsigned short usType, char cTransType);
void  MCP98242_3RegGet(MCP98242_3Dev *pDev, void *vpValue, 
                        unsigned short usType, char cTransType);

extern void  MCP98242_3SENInit(MCP98242_3Dev *pDev, unsigned long ulRate);
extern void  MCP98242_3SENDeInit(MCP98242_3Dev *pDev);
extern void  MCP98242_3Config(MCP98242_3Dev *pDev, unsigned short usConfig);
extern void  MCP98242_3IntEnable(MCP98242_3Dev *pDev);
extern void  MCP98242_3IntConfig(MCP98242_3Dev *pDev, xtEventCallback xtIntCallback,
                unsigned long ulTrigMode, unsigned long ulEventMode);
extern void  MCP98242_3IntDisable(MCP98242_3Dev *pDev);
extern xtBoolean  MCP98242_3ModeSet(MCP98242_3Dev *pDev, char cMode);
extern char  MCP98242_3ModeGet(MCP98242_3Dev *pDev);
extern char  MCP98242_3EvnCondGet(MCP98242_3Dev *pDev);
extern void  MCP98242_3ResSet(MCP98242_3Dev *pDev, unsigned char sResol);
extern char  MCP98242_3ResGet(MCP98242_3Dev *pDev);
extern void  MCP98242_3HystSet(MCP98242_3Dev *pDev, unsigned long ulHyst);
extern unsigned short MCP98242_3HystGet(MCP98242_3Dev *pDev);
extern void  MCP98242_3GetID(MCP98242_3Dev *pDev, MCP98242_3_ID *id);
extern void  MCP98242_3IntClear(MCP98242_3Dev *pDev);

//*****************************************************************************
//
//! \brief Get the Capability of Temperature Sensor. 
//!
//! \param pDev specifies the device
//! \param sencap specifies Capability of Temperature Sensor.
//!
//! This function is to get the Capability of Temperature Sensor.
//! 
//! \return None.
//
//*****************************************************************************                                                   
#define  MCP98242_3CapGet(pDev, sencap)                                       \
         MCP98242_3RegGet(pDev, sencap, MCP98242_3_Cap, I2C_TRANSFER_POLLING)


//*****************************************************************************
//
//! \brief Get the Config register of Temperature Sensor. 
//!
//! \param pDev specifies the device
//! \param senconfig specifies Config register of Temperature Sensor.
//!
//! This function is to get the Config register of Temperature Sensor.
//!
//! \return None.
//
//*****************************************************************************         
#define  MCP98242_3ConfigGet(pDev, senconfig)                                 \
         MCP98242_3RegGet(pDev, senconfig, MCP98242_3_CONFIG, I2C_TRANSFER_POLLING)

//*****************************************************************************
//
//! \brief Set the Upper limit temperature of Temperature Sensor. 
//!
//! \param pDev specifies the device
//! \param limValue specifies limit temperature.
//!
//! This function is to set upper limit temperature of Temperature Sensor.
//!
//! The \e limitValue can be type of int or Float. 
//!
//! \return None.
//
//***************************************************************************** 
#define  MCP98242_3UpperSet(pDev, limValue)                                   \
         MCP98242_3RegSet(pDev, limValue, (MCP98242_3_UPPER | 0x10),          \
                        I2C_TRANSFER_POLLING)

//*****************************************************************************
//
//! \brief Get the Upper limit temperature of Temperature Sensor with a float 
//! type value. 
//!
//! \param pDev specifies the device
//! \param fLimValue specifies limit temperature.
//!
//! This function is to get upper limit temperature in float type.
//!
//! \return None.                                                                    
//
//***************************************************************************** 
#define  MCP98242_3UpperGetFt(pDev, fLimValue)                                \
         MCP98242_3RegGet(pDev, fLimValue, (MCP98242_3_UPPER | 0x10),         \
                        I2C_TRANSFER_POLLING)

//*****************************************************************************
//
//! \brief Get the Upper limit temperature of Temperature Sensor with a short 
//! type value. 
//!
//! \param pDev specifies the device
//! \param sLimValue specifies limit temperature.
//!
//! This function is to get upper limit temperature in short type.
//!
//! \return None.
//
//***************************************************************************** 
#define  MCP98242_3UpperGetDec(pDev, sLimValue)                               \
         MCP98242_3RegGet(pDev, sLimValue, (MCP98242_3_UPPER | 0x20),         \
                        I2C_TRANSFER_POLLING)

//*****************************************************************************
//
//! \brief Set the lower limit temperature of Temperature Sensor. 
//!
//! \param pDev specifies the device
//! \param limValue specifies limit temperature.
//!
//! This function is to set lower limit temperature of Temperature Sensor.
//!
//! \return None.
//
//***************************************************************************** 
#define  MCP98242_3LowerSet(pDev, limValue)                                   \
         MCP98242_3RegSet(pDev, limValue, (MCP98242_3_LOWER | 0x10),          \
                        I2C_TRANSFER_POLLING)

//*****************************************************************************
//
//! \brief Get the Lower limit temperature of Temperature Sensor with a float 
//! type value. 
//!
//! \param pDev specifies the device
//! \param fLimValue specifies limit temperature.
//!
//! This function is to get lower limit temperature in float type.
//!
//! \return None.
//
//***************************************************************************** 
#define  MCP98242_3LowerGetFt(pDev, fLimValue)                                \
         MCP98242_3RegGet(pDev, fLimValue, (MCP98242_3_LOWER | 0x10),         \
                        I2C_TRANSFER_POLLING)
         
//*****************************************************************************
//
//! \brief Get the Lower limit temperature of Temperature Sensor with a short 
//! type value. 
//!
//! \param pDev specifies the device
//! \param sLimValue specifies limit temperature.
//!
//! This function is to get lower limit temperature in short type.
//!
//! \return None.
//
//***************************************************************************** 
#define  MCP98242_3LowerGetDec(pDev, sLimValue)                               \
         MCP98242_3RegGet(pDev, sLimValue, (MCP98242_3_LOWER | 0x20),         \
                        I2C_TRANSFER_POLLING)

//*****************************************************************************
//
//! \brief Set the Critical limit temperature of Temperature Sensor. 
//!
//! \param pDev specifies the device
//! \param limValue specifies limit temperature.
//!
//! This function is to set critical limit temperature of Temperature Sensor.
//!
//! \return None.
//
//***************************************************************************** 
#define  MCP98242_3CritSet(pDev, limValue)                                    \
         MCP98242_3RegSet(pDev, limValue, (MCP98242_3_CRITICAL | 0x10),       \
                        I2C_TRANSFER_POLLING)

//*****************************************************************************
//
//! \brief Get the Critical limit temperature of Temperature Sensor with a float 
//! type value. 
//!
//! \param pDev specifies the device
//! \param fLimValue specifies limit temperature.
//!
//! This function is to get critical limit temperature in float type.
//!
//! \return None.
//
//***************************************************************************** 
#define  MCP98242_3CritGetFt(pDev, fLimValue)                                 \
         MCP98242_3RegGet(pDev, fLimValue, (MCP98242_3_CRITICAL | 0x10),      \
                        I2C_TRANSFER_POLLING)
     
//*****************************************************************************
//
//! \brief Get the Critical limit temperature of Temperature Sensor with a short 
//! type value. 
//!
//! \param pDev specifies the device
//! \param sLimValue specifies limit temperature.
//!
//! This function is to get critical limit temperature in short type.
//!
//! \return None.
//
//*****************************************************************************
#define  MCP98242_3CritGetDec(pDev, sLimValue)                                \
         MCP98242_3RegGet(pDev, sLimValue, (MCP98242_3_CRITICAL | 0x20),      \
                        I2C_TRANSFER_POLLING)

//*****************************************************************************
//
//! \brief Get the ambient temperature of Temperature Sensor in float type. 
//!
//! \param pDev specifies the device
//! \param fValue specifies ambient temperature.
//!
//! \return None.
//
//***************************************************************************** 
#define  MCP98242_3GetTempFt(pDev, fValue)                                    \
      MCP98242_3RegGet(pDev, fValue, (MCP98242_3_TEMP | 0x10), I2C_TRANSFER_POLLING)
         
//*****************************************************************************
//
//! \brief Get the ambient temperature of Temperature Sensor in short type. 
//!
//! \param pDev specifies the device
//! \param sValue specifies ambient temperature.
//!
//! \return None.
//
//***************************************************************************** 
#define  MCP98242_3GetTempDec(pDev, sValue)                                   \
      MCP98242_3RegGet(pDev, sValue, (MCP98242_3_TEMP | 0x20), I2C_TRANSFER_POLLING)



//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup MCP98242_3_EEPROM_APIs
//! @{
//
//*****************************************************************************

extern void  MCP98242_3EEPROMInit(MCP98242_3Dev *pDev, unsigned long ulRate);
extern void  MCP98242_3EEPROMDeInit(MCP98242_3Dev *pDev);
extern void  MCP98242_3ByteWrite(MCP98242_3Dev *pDev, unsigned short usAddr,  \
                char *cpValue, char cTransType);
extern void  MCP98242_3ByteRead(MCP98242_3Dev *pDev, unsigned short usAddr,   \
                char *cpValue, char cTransType);
extern xtBoolean MCP98242_3MutiByteWrite(MCP98242_3Dev *pDev, unsigned short  \
                usAddr, char *cpValue, char cTransType, unsigned char ucNum);
extern void MCP98242_3PageWrite(MCP98242_3Dev *pDev, unsigned short usAddr,   \
                char *cpValue, char cTransType);
extern void MCP98242_3MemRead(MCP98242_3Dev *pDev, char cAddr, char *cpValue, \
                    char cTransType, unsigned char ucNum);


//*****************************************************************************
//
//! \brief Read one byte from SWP Protected Array.  
//!
//! \param pDev specifies the device
//! \param addr specifies address.
//! \param value specifies value.
//! \param TransType specifies I2C transfer type.
//!
//! The \e addr should be between 0x00 to 0x7f, the Protected array.
//!
//! The \e value is 8 bits.
//!
//! The \e TransType can be \b XI2C_TRANSFER_POLLING or 
//! \b XI2C_TRANSFER_INTERRUPT.
//!
//! \return None.
//
//***************************************************************************** 
#define  MCP98242_3SWPRead(pDev, addr, value, TransType)                      \
               MCP98242_3ByteRead(pDev, (addr | 0x100), value, TransType)

//*****************************************************************************
//
//! \brief Write one byte to SWP Protected Array. 
//!
//! \param pDev specifies the device
//! \param addr specifies address.
//! \param value specifies value.
//! \param TransType specifies I2C transfer type.
//!
//! The \e addr should be between 0x00 to 0x7f, the Protected array.
//!
//! The \e value is 8 bits.
//!
//! The \e TransType can be \b XI2C_TRANSFER_POLLING or 
//! \b XI2C_TRANSFER_INTERRUPT.
//!
//! \return None.
//
//***************************************************************************** 
#define  MCP98242_3SWPWrite(pDev, addr, value, TransType)                     \
                     MCP98242_3ByteWrite(pDev, (addr | 0x100), value, TransType)

//*****************************************************************************
//
//! \brief Read one byte from Software Write-Protect (SWP) of EEPROM 
//! Protected Array. 
//!
//! \param pDev specifies the device
//! \param addr specifies address.
//! \param value specifies value.
//! \param TransType specifies I2C transfer type.
//!
//! The \e addr should be between 0x00 to 0x7f, the Protected array.
//!
//! The \e value is 8 bits.
//!
//! The \e TransType can be \b XI2C_TRANSFER_POLLING or 
//!\b XI2C_TRANSFER_INTERRUPT.
//!
//! \return None.
//
//***************************************************************************** 
#define  MCP98242_3CWPRead(pDev, addr, value, TransType)                      \
                  MCP98242_3ByteRead(pDev, (addr | 0x200), value, TransType)

//*****************************************************************************
//
//! \brief Clear one byte of SWP Protected Array. 
//!
//! \param pDev specifies the device
//! \param addr specifies address.
//! \param value specifies value.
//! \param TransType specifies I2C transfer type.
//!
//! The \e addr should be between 0x00 to 0x7f, the Protected array.
//!
//! The \e value is 8 bits.
//!
//! The \e TransType can be \b XI2C_TRANSFER_POLLING or 
//!\b XI2C_TRANSFER_INTERRUPT.
//!
//! \return None.
//
//***************************************************************************** 
#define  MCP98242_3CWPWrite(pDev, addr, value, TransType)                     \
                  MCP98242_3ByteWrite(pDev, (addr | 0x200), value, TransType)

//*****************************************************************************
//
//! \brief Read one byte from PWP Protected Array. 
//!
//! \param pDev specifies the device
//! \param addr specifies address.
//! \param value specifies value.
//! \param TransType specifies I2C transfer type.
//!
//! The \e addr should be between 0x00 to 0x7f, the Protected array.
//!
//! The \e value is 8 bits.
//!
//! The \e TransType can be \b XI2C_TRANSFER_POLLING or 
//!\b XI2C_TRANSFER_INTERRUPT.
//!
//! \return None.
//
//***************************************************************************** 
#define  MCP98242_3PWPRead(pDev, addr, value, TransType)                      \
                MCP98242_3ByteRead(pDev, (addr | 0x300), value, TransType)

//*****************************************************************************
//
//! \brief Write one byte to PWP Protected Array. 
//!
//! \param pDev specifies the device
//! \param addr specifies address.
//! \param value specifies value.
//! \param TransType specifies I2C transfer type.
//!
//! The \e addr should be between 0x00 to 0x7f, the Protected array.
//!
//! The \e value is 8 bits.
//!
//! The \e TransType can be \b XI2C_TRANSFER_POLLING or 
//!\b XI2C_TRANSFER_INTERRUPT.
//!
//! \return None.
//
//***************************************************************************** 
#define  MCP98242_3PWPWrite(pDev, addr, value, TransType)                     \
                MCP98242_3ByteWrite(pDev, (addr | 0x300), value, TransType)

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

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
