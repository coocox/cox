//*****************************************************************************
//
//! \file xwdt.h
//! \brief Prototypes for the WDT Driver.
//! \version V2.2.1.0
//! \date 6/14/2012
//! \author CooCox
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

#ifndef __xWDT_H__
#define __xWDT_H__

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
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup WDT
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT_Function_Type xWDT Function Type
//! \n
//! \section xWDT_Function_Type_Section 1. Where to use this group
//! Values that can be passed to xWDTFunctionEnable(), 
//! xWDTFunctionDisable() as the ulFunction parameter. 
//! \n
//! \section xWDT_Function_Type_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------ +----------------+------------------------+
//! |xWDT Function Type       |       CoX      |        STM32F1xx       |
//! |------------------------ |----------------|------------------------|
//! |xWDT_INT_FUNCTION        |    Mandatory   |            Y           |
//! |------------------------ |----------------|------------------------|
//! |xWDT_RESET_FUNCTION      |    Mandatory   |            Y           |
//! |------------------------ |----------------|------------------------|
//! |xWDT_WAKEUP_FUNCTION     |  Non-Mandatory |            N           |
//! |------------------------ |----------------|------------------------|
//! |xWDT_HOLD_IN_ICE         |  Non-Mandatory |            N           |
//! +------------------------ +----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Generate Interrupt when watch dog time out
//
#define xWDT_INT_FUNCTION       WDT_INT_FUNCTION

//
//! Reset CPU when watch dog time out
//
#define xWDT_RESET_FUNCTION     WDT_RESET_FUNCTION

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT_Clock_Config xWDT Clock Configuration
//! \brief Values that show xWDT Clock Configuration
//! \n
//! \section xWDT_Clock_Config_Section 1. Where to use this group
//! Watch dog clock Configs. Such as clock source, Prescaler divider.
//! Values that can be passed to xWDTInit as the ulConfig parameter 
//! \n
//! \section xWDT_Clock_Config_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |Clock Configuration     |       CoX      |        STM32F1xx       |
//! |------------------------|----------------|------------------------|
//! |xWDT_S_INTSL            |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xWDT_S_EXTSL            |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xWDT_S_HCLK_DIV         |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! The watch dog source is fractional frequency of HCLK
//
#define xWDT_S_HCLK_DIV         0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT_Time_Reload_Config xWDT Time Reload Configuration
//! \n
//! \section xWDT_Time_Reload_Config_Section 1. Where to use this group
//! Values that can be passed to xWDTimerInit() as the ulConfig parameter 
//! \n
//! \section xWDT_Time_Reload_Config_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |Time Reload Config      |       CoX      |       STM32F1xx        |
//! |------------------------|----------------|------------------------|
//! |Time Reload Value       |  Non-Mandatory |   xWDT_Reload_0        |
//! |                        |                |------------------------|
//! |unsigned value          |                |           ...          |
//! |                        |                |------------------------|
//! |                        |                |   xWDT_Reload_0xFFF    |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Reload Value is 0
//
#define xWDT_Reload_0           0

//
//! Reload Value is 0x7F 
//
#define xWDT_Reload_0x7F       0x0000007F


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT_Exported_APIs xWDT API
//! \brief xWDT API Reference.
//!
//! \section xWDT_Exported_APIs_Port CoX Port Details
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |xWDT API                |       CoX      |       STM32F1xx        |
//! |------------------------|----------------|------------------------|
//! |xWDTInit                |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTEnable              |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTIntCallbackInit     |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTDisable             |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTRestart             |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTFunctionEnable      |    Mandatory   |            N           |
//! |------------------------|----------------|------------------------|
//! |xWDTFunctionDisable     |    Mandatory   |            N           |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Configurate The WatchDog Timer(WDT)'s Timer Interval. 
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//! \param ulConfig is the Timer's Prescaler divider and clock source 
//! Selection.
//! Details please refer to \ref xWDT_Clock_Config and xWDT_Time_Reload_Config.
//! \param ulReload is the Timer's reload value.
//!
//! This function is to configureThe WatchDog Timer(WDT)'s Timer Interval.
//! There are three factors to determine the Timer Interval, they are:
//! - clock source
//! - Prescaler divider
//! - reload value
//!
//! The \e ulConfig parameter contains clock source and Prescaler divider;
//! When being used,this parameter is the logical OR of the two values.
//! For STM32F1xx,there is no Prescaler divider and the clock source can be:
//! \b xWDT_S_HCLK_DIV
//! Details please refer to \ref xWDT_Clock_Config_CoX.
//!
//! The \e ulReload parameter is the value which will reload the counter when 
//! feeding the watch dog.The value range depends on the number of bits of 
//! corresponding counter.
//! For STM32F1xx, the reload value can only be one of the following:
//! \b 0 to 0x7F.
//! Details please refer to \ref xWDT_Time_Reload_Config_CoX.
//! 
//! \note When using watch dog xWDTEnable() should be called after call 
//! xWDTInit(ulBase, ulConfig, ulReload).
//!
//! \return None.
//
//*****************************************************************************

#define xWDTInit(ulBase, ulConfig, ulReload)                                  \
        do                                                                    \
        {                                                                     \
         xASSERT(ulBase == xWDT_BASE);                                        \
         SysCtlPeripheralClockSourceSet(ulConfig, 0);                         \
         WDTimerInit(ulReload);                                               \
        }while(0)  

//*****************************************************************************
//
//! \brief Enable the Watchdog timer interrupt. 
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//!
//! This function is to Enable the Watchdog timer interrupt.
//!
//! \note When use watch dog xWDTimerEnable() should be called after call 
//! xWDTInit(ulBase, ulConfig, ulReload).
//!
//! \return None.
//
//*****************************************************************************       
#define xWDTEnable(ulBase)                                                    \
        WWDGEnable(ulBase)


//*****************************************************************************
//
//! \brief Init interrupts callback for the Watchdog timer.
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//! \param xtPortCallback is callback for the Watchdog timer.
//!
//! Init interrupts callback for the Watchdog timer.
//!
//! \return None.
//
//*****************************************************************************     
#define xWDTIntCallbackInit(ulBase, xtWDTCallback)                            \
        do                                                                    \
        {                                                                     \
         xASSERT(ulBase == xWDT_BASE);                                        \
         WDTimerIntCallbackInit(xtWDTCallback);                               \
        }while(0) 
        
//*****************************************************************************
//
//! \brief Disable the Watchdog timer interrupt. 
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//!
//! This function is to disable the Watchdog timer interrupt.
//!
//! \return None.
//
//*****************************************************************************
#define xWDTDisable(ulBase)                                                   \
        WWDGDisable(ulBase)
//*****************************************************************************
//
//! \brief Restart the Watchdog timer interrupt. 
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//!
//! This function is to restart the Watchdog timer interrupt.
//!
//! \note this is use to feed the watch dog.
//!
//! \return None.
//
//*****************************************************************************       
#define xWDTRestart(ulBase)                                                   \
        do                                                                    \
        {                                                                     \
         xASSERT(ulBase == xWDT_BASE);                                        \
         WDTimerRestart();                                                    \
        }while(0) 

//*****************************************************************************
//
//! \brief Enable the watch dog timer's function. 
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//! \param ulFunction is the watch dog timer's function.
//! Details please refer to \ref xWDT_Function_Type.
//!
//! This function is to enable the watch dog timer's function such as Interrupt
//! reset.
//! 
//! The \e ulFunction parameter is the OR value of any of the following:
//! \b xWDT_INT_FUNCTION,\b xWDT_RESET_FUNCTION
//! Details please refer to \ref xWDT_Function_Type_CoX.
//!
//! \return None.
//
//*****************************************************************************
#define xWDTFunctionEnable(ulBase, ulFunction)                                \
        do                                                                    \
        {                                                                     \
         xASSERT(ulBase == xWDT_BASE);                                        \
         WDTimerFunctionEnable(ulFunction);                                   \
        }while(0) 
        
//*****************************************************************************
//
//! \brief Disable the watch dog timer's function. 
//!
//! \param ulBase is the base address of the WatchDog Timer(WDT) module.
//! \param ulFunction is the watch dog timer's function.
//! Details please refer to \ref xWDT_Function_Type.
//!
//! This function is to disable the watch dog timer's function such as Interrupt
//! reset
//! 
//! The \e ulFunction parameter is the OR value of any of the following:
//! \b xWDT_INT_FUNCTION,\b xWDT_RESET_FUNCTION,
//! Details please refer to \ref xWDT_Function_Type_CoX.
//!
//! \return None.
//
//*****************************************************************************      
#define xWDTFunctionDisable(ulBase, ulFunction)                               0

        
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
//! \addtogroup STM32F1xx_WDT
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup WDT_Status_Type WDT Status Type
//! Values that can be return from WDTimerStatusGet().
//! @{
//
//*****************************************************************************

//
//! Watchdog Timer Early wakeup interrupt flag
//
#define WDT_EVENT_EWIF          0x00000001


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup WDT_Function_Type WDT Function Type
//! Values that can be passed to WDTimerIntEnable().
//! ().
//! @{
//
//*****************************************************************************

//
//! Generate Interrupt when watch dog time out
//
#define WDT_INT_FUNCTION        0x00000200

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup WDT_Prescaler_Value WDT Prescaler Value
//! Values that can be passed to WDTimerPrescalerSet().
//! @{
//
//*****************************************************************************

//
//! WDT Prescaler Value is 1
//
#define WDT_PRESCALER_1         0x00000000

//
//! WDT Prescaler Value is 2
//
#define WDT_PRESCALER_2         0x00000080

//
//! WDT Prescaler Value is 4
//
#define WDT_PRESCALER_4         0x00000100

//
//! WDT Prescaler Value is 8
//
#define WDT_PRESCALER_8         0x00000180


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup IWDG_Prescaler_Value IWDG Prescaler Value
//! Values that can be passed to IWDGTimerPrescalerSet().
//! @{
//
//*****************************************************************************

//
//! IWDG Prescaler Value is 4
//
#define IWDT_PRESCALER_4        0x00000000

//
//! IWDG Prescaler Value is 8
//
#define IWDT_PRESCALER_8        0x00000001

//
//! IWDG Prescaler Value is 16
//
#define IWDT_PRESCALER_16       0x00000002

//
//! IWDG Prescaler Value is 32
//
#define IWDT_PRESCALER_32       0x00000003

//
//! IWDG Prescaler Value is 64
//
#define IWDT_PRESCALER_64       0x00000004

//
//! IWDG Prescaler Value is 128
//
#define IWDT_PRESCALER_128      0x00000005

//
//! IWDG Prescaler Value is 256
//
#define IWDT_PRESCALER_256      0x00000006

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup STM32F1xx_WDT_Exported_APIs STM32F1xx WDT API
//! \brief STM32F1xx WDT API Reference.
//! @{
//
//*****************************************************************************

extern void WDTimerInit(unsigned long ulConfig);
extern unsigned long WDTimerStatusGet(void);
extern void WDTimerRestart(void);
extern void WDTimerIntCallbackInit(xtEventCallback xtWDTCallback);
extern void WDTimerIntEnable(void);
extern void WDTimerDisable(void);
extern void WDTimerWindowValueSet(unsigned long ulConfig);
extern void WDTimerPrescalerSet(unsigned long ulDivide);
extern void WWDGEnable(unsigned long ulBase);
extern void WDTimerStatusClear(void);

extern void IWDGTimerInit(unsigned long ulConfig);
extern void IWDGTimerStart(void);
extern void IWDGTimerRestart(void);
extern unsigned long IWDGTimerStatusGet(void);
extern void IWDGTimerPrescalerSet(unsigned long ulDivide);

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

#endif // __xWDT_H__


