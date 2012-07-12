//*****************************************************************************
//
//! file MCP98242.h
//! brief header file of Driver for MCP98242/3
//! version 2.1.2.0
//! date 20/11/2011
//! author CooCox
//! copy
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
#include "hw_MCP98242_3.h"

#ifndef __MCP98242_H__
#define __MCP98242_H__

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
//! \addtogroup CoX_Driver_Lib  
//! @{
//! \addtogroup Sensor 
//! @{
//! \addtogroup Temperature_Sensor  
//! @{
//! \addtogroup MCP98242_TempSensor_EEPROM 
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242_Driver MCP98242 Driver
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242_Peripheral_Config MCP98242 Peripheral Config
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

}MCP98242Dev;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup MCP98242_Limit_Type  MCP98242 Limit Type
//! @{
//
//*****************************************************************************

#define  MCP_UPPER              0x00000002      // Upper Temperature
#define  MCP_LOWER              0x00000003      // Low Temperature
#define  MCP_CRITICAL           0x00000004      // Critical Temperature


//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup MCP98242_Temp_DataType  MCP98242 Tempterature Data Type
//! @{
//
//*****************************************************************************

#define  MCP_FLOAT              0x00000001      // Float data type
#define  MCP_INT                0x00000002      // Integer data type

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup MCP98242_EEPROM_AREA  MCP98242 EEPROM AREA
//! @{
//
//*****************************************************************************

#define  MCP_EEPROM_STD         0x00000000      // Standard Area
#define  MCP_EEPROM_SWP         0x00000001      // Software Write-Protect
#define  MCP_EEPROM_CWP         0x00000002      // Clear Write-Protect
#define  MCP_EEPROM_PWP         0x00000003      // Permanently Write-Protect

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242_Event_Conf  MCP98242 Event Config
//! Set Event Output Mode.
//! @{
//
//*****************************************************************************

//
//! Set Event Output Mode as Comparator output(power-up default)
//
#define MCP_EVENT_COMP          0x00000000

//
//! Set Event Output Mode as interrupt output
//
#define MCP_EVENT_INT           0x00000001

//
//! Event Output Select: for MCP_UPPER, MCP_LOWER and T_CRIT (power-up default)
//
#define MCP_EVENT_SEL_ALL       0x00000000

//
//! Event Output Select: T_A ¡Ý T_CRIT only.
//
#define MCP_EVENT_SEL_CRIT      0x00000004

//
//! Event Output Polarity: Active-high.
//
#define MCP_EVENT_HIGH_LEVEL    0x00000002

//
//! Event Output Polarity: Active low.
//
#define MCP_EVENT_LOW_LEVEL     0x00000000

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup MCP98242_LimitLock  MCP98242 Limit Lock
//! Config Limit Temperature Lock Bit
//! @{
//
//*****************************************************************************

#define  MCP_LOCK_M             0x000000C0  //Lock Bits Mask
#define  MCP_CRIT_LOCK          0x00000080  //Lock T_CRIT Bit
#define  MCP_CRIT_UNLOCK        0x00000000  //Unlock T_CRIT Bit
#define  MCP_WIN_LOCK           0x00000040  //Lock the UPPER and LOWER Window
#define  MCP_WIN_UNLOCK         0x00000000  //Unock the UPPER and LOWER Window

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup MCP98242_Event_Condition  MCP98242 Event Condition
//! Enable and Set I2C, and related GPIO Pins.
//! @{
//
//*****************************************************************************

//
//! T_A >= MCP_LOWER OR T_A <= MCP_UPPER - T_HYST
//
#define  MCP_EVENT_COND_1       0x00000000

//
//! T_A < MCP_LOWER - T_HYST
//
#define  MCP_EVENT_COND_2       0x00000001

//
//! T_A > MCP_UPPER OR T_A < T_CRIT - T_HYST
//
#define  MCP_EVENT_COND_3       0x00000002
//
//! T_A >= T_CRIT
//
#define  MCP_EVENT_COND_4       0x00000006

//*****************************************************************************
//
//! @}
//
//*****************************************************************************  

//*****************************************************************************
//
//! \addtogroup MCP98242_TempSensor_Res MCP98242 Temp-Sensor Res
//! MCP98242 Temperature Sensor Resolution.
//! @{
//
//*****************************************************************************

//
//! Set the Temperature Sensor Resolution to be 0.5¡æ
//
#define   MCP_RESOLUTION_5      0x00000000

//
//! Set the Temperature Sensor Resolution to be 0.25¡æ
//
#define   MCP_RESOLUTION_25     0x00000001

//
//! Set the Temperature Sensor Resolution to be 0.125¡æ
//
#define   MCP_RESOLUTION_125    0x00000002

//
//! Set the Temperature Sensor Resolution to be 0.0625¡æ
//
#define   MCP_RESOLUTION_0625   0x00000003

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup MCP98242_TempSensor_Hyst  MCP98242 TempSensor Hyst
//! MCP98242 Temperature Sensor Hysteresis.
//! @{
//
//*****************************************************************************

//
//! The Hysteresis Offset
//
#define   MCP_HYSTERESIS_S      0x00000009

//
//! The Mask of Hysteresis
//
#define   MCP_HYSTERESIS_M      0x00000600

//
//! Set the Temperature Sensor Resolution to be 0¡æ
//
#define   MCP_HYSTERESIS_0      0x00000000

//
//! Set the Temperature Sensor Resolution to be 1.5¡æ
//
#define   MCP_HYSTERESIS_1_5    0x00000200

//
//! Set the Temperature Sensor Resolution to be 3¡æ 
//
#define   MCP_HYSTERESIS_3      0x00000400

//
//! Set the Temperature Sensor Resolution to be 6¡æ 
//
#define   MCP_HYSTERESIS_6      0x00000600

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242__ID  MCP98242 ID
//! @{
//
//*****************************************************************************
typedef struct{
    unsigned short  MANU_ID;   // MANUFACTURER ID
    unsigned char  REVISION;   // DEVICE ID
    unsigned char  DEV_ID;     // REVISION
}MCP98242_ID;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************  


//*****************************************************************************
//
//! \addtogroup MCP98242_APIs MCP98242 APIs
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP98242_TempSen_APIs MCP98242 Temp-Sensor APIs
//! @{
//
//*****************************************************************************

void  MCP98242RegSet(MCP98242Dev *pDev, void *vpValue, 
                     unsigned char ucType, unsigned char ucTransType);
void  MCP98242RegGet(MCP98242Dev *pDev, void *vpValue, 
                     unsigned char ucType, unsigned char ucTransType);

extern void  MCP98242SensorInit(MCP98242Dev *pDev, unsigned long ulRate);
extern unsigned short MCP98242CapGet(MCP98242Dev *pDev);
extern void  MCP98242Config(MCP98242Dev *pDev, unsigned short usConfig,
                            unsigned long ulResol, unsigned long ulHyst);
extern void  MCP98242IntEnable(MCP98242Dev *pDev);
extern void  MCP98242IntConfig(MCP98242Dev *pDev, 
                               xtEventCallback xtIntCallback,
                               unsigned long ulTrigMode, 
                               unsigned long ulEventMode);
extern void  MCP98242IntClear(MCP98242Dev *pDev);
extern void  MCP98242IntDisable(MCP98242Dev *pDev);
extern xtBoolean  MCP98242SHDNEnable(MCP98242Dev *pDev);
extern void  MCP98242SHDNDisable(MCP98242Dev *pDev);
extern char  MCP98242EvnCondGet(MCP98242Dev *pDev);
extern void  MCP98242LimitSet(MCP98242Dev *pDev, void *vpValue, 
                              unsigned char ucLimitType);
extern void  MCP98242TempGet(MCP98242Dev *pDev, void *vpValue, 
                             unsigned char ucDataType);
extern void  MCP98242GetID(MCP98242Dev *pDev, MCP98242_ID *id);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup MCP98242_EEPROM_APIs  MCP98242 EEPROM APIs
//! @{
//
//*****************************************************************************

extern void  MCP98242EEPROMInit(MCP98242Dev *pDev, unsigned long ulRate);
extern void  MCP98242ByteWrite(MCP98242Dev *pDev, unsigned char ucAddr,  
                               unsigned char ucValue);
extern void  MCP98242PageWrite(MCP98242Dev *pDev, unsigned char ucAddr,   
                               unsigned char *ucpValue);
extern unsigned char MCP98242ByteRead(MCP98242Dev *pDev, unsigned char ucAddr);
extern void MCP98242MemRead(MCP98242Dev *pDev, unsigned char ucAddr, 
                            unsigned char *ucpValue, unsigned char ucNum);
extern void  MCP98242ProtWrite(MCP98242Dev *pDev, unsigned char ucAddr,  
                               unsigned char ucValue, unsigned char cType);
extern void  MCP98242ProtClear(MCP98242Dev *pDev, unsigned char ucAddr);
                                                                  
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
