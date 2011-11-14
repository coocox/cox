//*****************************************************************************
//
//! \file xwdt.h
//! \brief Prototypes for the WDT Driver.
//! \version V2.1.1.1
//! \date 11/14/2011
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
//! \brief Values that show xWDT Function Type
//! \n
//! \section xWDT_Function_Type_Section 1. Where to use this group
//! Values that can be passed to xWDTFunctionEnable(), 
//! xWDTFunctionDisable() as the ulFunction parameter. 
//! \n
//! \section xWDT_Function_Type_CoX 2. CoX Port Details 
//! \verbatim
//! +------------------------ +----------------+------------------------+
//! |xWDT Function Type       |       CoX      |         NUC1xx         |
//! |------------------------ |----------------|------------------------|
//! |xWDT_INT_FUNCTION        |    Mandatory   |            Y           |
//! |------------------------ |----------------|------------------------|
//! |xWDT_RESET_FUNCTION      |    Mandatory   |            Y           |
//! |------------------------ |----------------|------------------------|
//! |xWDT_WAKEUP_FUNCTION     |  Non-Mandatory |            Y           |
//! |------------------------ |----------------|------------------------|
//! |xWDT_HOLD_IN_ICE         |  Non-Mandatory |            Y           |
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

//
//! Watchdog timer timeout can wake-up chip from power down mode.
//
#define xWDT_WAKEUP_FUNCTION    WDT_WAKEUP_FUNCTION

//
//! Watchdog Timer counter will keep going no matter ICE debug mode
//! acknowledged or not.
//
#define xWDT_HOLD_IN_ICE        WDT_HOLD_IN_ICE

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
//! |Clock Configuration     |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |xWDT_S_INTSL            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDT_S_EXTSL            |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDT_S_HCLK_DIV         |  Non-Mandatory |            Y           |
//! |------------------------|----------------|------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! The watch dog source is int. 10 KHz
//
#define xWDT_S_INTSL            SYSCTL_PERIPH_WDG_S_INT10K     

//
//! The watch dog source is ext. 32 KHz
//
#define xWDT_S_EXTSL            SYSCTL_PERIPH_WDG_S_EXT32K

//
//! The watch dog source is the HCLK/2048
//
#define xWDT_S_HCLK_DIV         SYSCTL_PERIPH_WDG_S_HCLK_2048


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT_Time_Reload_Config xWDT Time Reload Configuration
//! \brief Values that show xWDT Time Reload Configuration
//! \n
//! \section xWDT_Time_Reload_Config_Section 1. Where to use this group
//! Values that can be passed to xWDTimerInit() as the ulConfig parameter 
//! \n
//! \section xWDT_Time_Reload_Config_CoX 2.CoX Port Details 
//! \verbatim
//! +------------------------+----------------+------------------------+
//! |Time Reload Config      |       CoX      |         NUC1xx         |
//! |------------------------|----------------|------------------------|
//! |Time Reload Value       |  Non-Mandatory |   xWDT_INTERVAL_2_4T   |
//! |                        |                |------------------------|
//! |unsigned value          |                |           ...          |
//! |                        |                |------------------------|
//! |                        |                |   xWDT_INTERVAL_2_18T  |
//! +------------------------+----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Timeout Interval Selection is 2 4 * TWDT
//
#define xWDT_INTERVAL_2_4T      WDT_INTERVAL_2_4T

//
//! Timeout Interval Selection is 2 6 * TWDT
//
#define xWDT_INTERVAL_2_6T      WDT_INTERVAL_2_6T

//
//! Timeout Interval Selection is 2 8 * TWDT
//
#define xWDT_INTERVAL_2_8T      WDT_INTERVAL_2_8T

//
//! Timeout Interval Selection is 2 10 * TWDT
//
#define xWDT_INTERVAL_2_10T     WDT_INTERVAL_2_10T

//
//! Timeout Interval Selection is 2 12 * TWDT
//
#define xWDT_INTERVAL_2_12T     WDT_INTERVAL_2_12T

//
//! Timeout Interval Selection is 2 14 * TWDT
//
#define xWDT_INTERVAL_2_14T     WDT_INTERVAL_2_14T

//
//! Timeout Interval Selection is 2 16 * TWDT
//
#define xWDT_INTERVAL_2_16T     WDT_INTERVAL_2_16T

//
//! Timeout Interval Selection is 2 18 * TWDT
//
#define xWDT_INTERVAL_2_18T     WDT_INTERVAL_2_18T


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
//! |xWDT API                |       CoX      |         NUC1xx         |
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
//! |xWDTFunctionEnable      |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTFunctionDisable     |    Mandatory   |            Y           |
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
//! Details please refer to \ref xWDT_Clock_Config and
//! xWDT_Time_Reload_Config.
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
//! For NUC1xx,there is no Prescaler divider and the clock source can be:
//! \b xWDT_S_INTSL, \b xWDT_S_EXTSL, 
//! \b xWDT_S_HCLK_DIV.
//! Details please refer to \ref xWDT_Clock_Config_CoX.
//!
//! The \e ulReload parameter is the value which will reload the counter when 
//! feeding the watch dog.The value range depends on the number of bits of 
//! corresponding counter.
//! For NUC1xx, the reload value can only be one of the following:
//! \b xWDT_INTERVAL_2_4T, \b xWDT_INTERVAL_2_6T, \b xWDT_INTERVAL_2_8T,
//! \b xWDT_INTERVAL_2_10T, \b xWDT_INTERVAL_2_12T, \b xWDT_INTERVAL_2_14T,
//! \b xWDT_INTERVAL_2_16T, \b xWDT_INTERVAL_2_18T.
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
         SysCtlPeripheralClockSourceSet(ulConfig);                            \
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
        do                                                                    \
        {                                                                     \
         xASSERT(ulBase == xWDT_BASE);                                        \
         WDTimerEnable();                                                     \
        }while(0) 


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
        do                                                                    \
        {                                                                     \
         xASSERT(ulBase == xWDT_BASE);                                        \
         WDTimerDisable();                                                    \
        }while(0) 
        
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
//! reset\wake up \stop in ICE mode.
//! 
//! The \e ulFunction parameter is the OR value of any of the following:
//! \b xWDT_INT_FUNCTION,\b xWDT_RESET_FUNCTION,
//! \b xWDT_WAKEUP_FUNCTION,\b xWDT_HOLD_IN_ICE.
//! Details please refer to \ref xWDT_Function_Type_CoX.
//!
//! \note None.
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
//! reset\wake up \stop in ICE mode.
//! 
//! The \e ulFunction parameter is the OR value of any of the following:
//! \b xWDT_INT_FUNCTION,\b xWDT_RESET_FUNCTION,
//! \b xWDT_WAKEUP_FUNCTION,\b xWDT_HOLD_IN_ICE.
//! Details please refer to \ref xWDT_Function_Type_CoX.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************      
#define xWDTFunctionDisable(ulBase, ulFunction)                               \
        do                                                                    \
        {                                                                     \
         xASSERT(ulBase == xWDT_BASE);                                        \
         WDTimerFunctionDisable(ulFunction);                                  \
        }while(0) 

        
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
//! \addtogroup NUC1xx_WDT
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup WDT_Function_Type WDT Function Type
//! \brief Values that show WDT Function Type
//! Values that can be passed to WDTimerFunctionEnable(),WDTimerFunctionDisable 
//! ().
//! @{
//
//*****************************************************************************

//
//! Generate Interrupt when watch dog time out
//
#define WDT_INT_FUNCTION        0x00000040

//
//! Reset CPU when watch dog time out
//
#define WDT_RESET_FUNCTION      0x00000002

//
//! Watchdog timer timeout can wake-up chip from power down mode.
//
#define WDT_WAKEUP_FUNCTION     0x00000010

//
//! Watchdog Timer counter will keep going no matter ICE debug mode
//! acknowledged or not.
//
#define WDT_HOLD_IN_ICE         0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup WDT_Time_Interval_Config WDT Time Interval Configuration
//! \brief WDT Time Interval Configuration
//! Values that can be passed to WDTimerInit().
//! @{
//
//*****************************************************************************

//
//! Timeout Interval Selection is 2 4 * TWDT
//
#define WDT_INTERVAL_2_4T       0x00000000

//
//! Timeout Interval Selection is 2 6 * TWDT
//
#define WDT_INTERVAL_2_6T       0x00000100

//
//! Timeout Interval Selection is 2 8 * TWDT
//
#define WDT_INTERVAL_2_8T       0x00000200

//
//! Timeout Interval Selection is 2 10 * TWDT
//
#define WDT_INTERVAL_2_10T      0x00000300

//
//! Timeout Interval Selection is 2 12 * TWDT
//
#define WDT_INTERVAL_2_12T      0x00000400

//
//! Timeout Interval Selection is 2 14 * TWDT
//
#define WDT_INTERVAL_2_14T      0x00000500

//
//! Timeout Interval Selection is 2 16 * TWDT
//
#define WDT_INTERVAL_2_16T      0x00000600

//
//! Timeout Interval Selection is 2 18 * TWDT
//
#define WDT_INTERVAL_2_18T      0x00000700


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_WDT_Exported_APIs NUC1xx WDT API
//! \brief NUC1xx WDT API Reference.
//! @{
//! @{
//
//*****************************************************************************

extern void WDTimerInit(unsigned long ulConfig);
extern void WDTimerEnable(void);
extern void WDTimerDisable(void);
extern void WDTimerRestart(void);
extern void WDTimerIntCallbackInit(xtEventCallback xtWDTCallback);
extern void WDTimerFunctionEnable(unsigned long ulFunction);
extern void WDTimerFunctionDisable(unsigned long ulFunction);

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


