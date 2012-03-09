//*****************************************************************************
//
//! \file MCP9800_3.h
//! \brief header file of Driver for MCP9800_3
//! \version 2.1.1.0
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
#include "hw_MCP9800_3.h"

#ifndef __MCP9800_H__
#define __MCP9800_H__

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
//! \addtogroup MCP9800_TempSensor 
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP9800_Driver MCP9800 Driver
//! MCP9800 Driver.
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP9800_Peripheral_Config MCP9800 Peripheral Config
//! Enable and Set I2C, and related GPIO Pins.
//! @{
//
//*****************************************************************************

typedef struct
{
    unsigned long  I2CBase;
    unsigned long  SensorSlaAddr;
    unsigned long  EventPort;
    unsigned long  EventPin;
    unsigned long  EventIntVec;

    //
    // pinSet Function:
    //      1. Enable GPIO Clock 
    //      2. Set GPIO Pin Funciton
    //
    void (*pinSet)(void);

}MCP9800Dev;

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup MCP9800_Config  MCP9800 Configuration
//! MCP9800 Temperature Sensor Configuration Register
//! @{
//
//*****************************************************************************
 
//
//! Shut Down Offset.
//
#define   MCP9800_SHDN_S        0x00000000

//
//! COMP/INT Offset.
//
#define   MCP9800_COMPINT_S     0x00000001

//
//! Alert Polarity Offset.
//
#define   MCP9800_ALERTPOL_S    0x00000002

//
//! Fault Queue Offset.
//
#define   MCP9800_FAULTQUE_S    0x00000003

//
//! Fault Queue Mask.
//
#define   MCP9800_FAULTQUE_M    0x00000018

//
//! Resolution Offset.
//
#define   MCP9800_RESOL_S       0x00000005
                                
//
//! Resolution Mask.
//
#define   MCP9800_RESOL_M       0x00000060

//
//! One Shot Offset.
//
#define   MCP9800_ONESHOT_S     0x00000007

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup MCP9800_Event_Mode  MCP9800 Event Mode
//! Set Event Output Mode.
//! @{
//
//*****************************************************************************

//
//! Set Event Output Mode as Comparator output(power-up default)
//
#define  MCP9800_EVENT_COMP     0

//
//! Set Event Output Mode as interrupt output
//
#define  MCP9800_EVENT_INT      1           

//*****************************************************************************
//
//! @}
//                              
//***************************************************************************** 

//*****************************************************************************
//
//! \addtogroup MCP9800_Alert_Pol  MCP9800 Alert Polarity
//! Set Alert Polarity.
//! @{
//
//*****************************************************************************

//
//! Set Alert Polarity as Low(power-up default)
//
#define  MCP9800_ALERTPOL_LOW   0

//
//! Set Alert Polarity as High
//
#define  MCP9800_ALERTPOL_HIGH  1

//*****************************************************************************
//
//! @}
//
//***************************************************************************** 


//*****************************************************************************
//
//! \addtogroup MCP9800_TempSensor_Mode  MCP9800 Temp-Sensor Mode
//! MCP9800 Temperature Sensor Mode.
//! @{
//
//*****************************************************************************

//
//! Set to be Continuous Mode
//
#define   MCP9800_CONTI         0

//
//! Set to be One-Shot Mode
//
#define   MCP9800_ONESHOT       1

//
//! Set to be Shut Down Mode
//
#define   MCP9800_SHDN          2

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup MCP9800_FaultQue MCP9800 Fault Queue
//! MCP9800 Temperature Fault Queue.
//! @{
//
//*****************************************************************************

//
//! Set Fault Queue to be 1
//
#define   MCP9800_FAULTQUE_1    0x00000000

//
//! Set Fault Queue to be 2
//
#define   MCP9800_FAULTQUE_2    0x00000008

//
//! Set Fault Queue to be 4
//
#define   MCP9800_FAULTQUE_4    0x00000010

//
//! Set Fault Queue to be 6
//
#define   MCP9800_FAULTQUE_6    0x00000018

//*****************************************************************************
//
//! @}
//
//*****************************************************************************  

//*****************************************************************************
//
//! \addtogroup MCP9800_TempSensor_Res MCP9800 Temp-Sensor Res
//! MCP9800 Temperature Sensor Resolution.
//! @{
//
//*****************************************************************************

//
//! Set the Temperature Sensor Resolution to be 0.5¡æ
//
#define   MCP9800_RESOL_5       0x00000000

//
//! Set the Temperature Sensor Resolution to be 0.25¡æ
//
#define   MCP9800_RESOL_25      0x00000020

//
//! Set the Temperature Sensor Resolution to be 0.125¡æ
//
#define   MCP9800_RESOL_125     0x00000040

//
//! Set the Temperature Sensor Resolution to be 0.0625¡æ
//
#define   MCP9800_RESOL_0625    0x00000060

//*****************************************************************************
//
//! @}
//
//*****************************************************************************     

//*****************************************************************************
//
//! \addtogroup MCP9800_Temp_DataType  MCP9800 Tempterature Data Type
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
//! \addtogroup MCP9800_APIs MCP9800 APIs
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup MCP9800_Basic_APIs
//! @{
//
//*****************************************************************************

extern void  MCP980xRegSet(MCP9800Dev *pDev, void *vpValue, unsigned short usType, 
                        char cTransType);
extern void  MCP980xRegGet(MCP9800Dev *pDev, void *vpValue, unsigned short usType, 
                        char cTransType);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************    

//*****************************************************************************
//
//! \addtogroup MCP9800_TempSen_APIs
//! @{
//
//*****************************************************************************

extern void  MCP980xInit(MCP9800Dev *pDev, unsigned long ulRate);
extern void  MCP980xDeInit(MCP9800Dev *pDev);
extern void  MCP980xConfig(MCP9800Dev *pDev, unsigned char ucConfig);
extern void  MCP980xIntConfig(MCP9800Dev *pDev, xtEventCallback xtIntCallback,
                unsigned long ulTrigMode, unsigned long ulEventMode);
extern xtBoolean  MCP980xModeSet(MCP9800Dev *pDev, char cMode);
extern char  MCP980xModeGet(MCP9800Dev *pDev);
extern void  MCP980xIntClear(MCP9800Dev *pDev);         
extern void  MCP980xLimitSet(MCP9800Dev *pDev, void *vpValue, 
                               unsigned long ulType);
extern void  MCP980xTempGet(MCP9800Dev *pDev, void *vpValue, 
                              unsigned long ulDataType);

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
