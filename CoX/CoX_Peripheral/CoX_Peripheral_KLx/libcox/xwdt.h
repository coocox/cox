//*****************************************************************************
//
//! \file xwdt.h
//! \brief Prototypes for the WDT Driver.
//! \version V2.1.1.1
//! \date 11/14/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox 
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
//! |xWDT Function Type       |       CoX      |         KLxx           |
//! |------------------------ |----------------|------------------------|
//! |xWDT_INT_FUNCTION        |    Mandatory   |            N           |
//! |------------------------ |----------------|------------------------|
//! |xWDT_RESET_FUNCTION      |    Mandatory   |            N           |
//! +------------------------ +----------------+------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Generate Interrupt when watch dog time out
//
#define xWDT_INT_FUNCTION       0

//
//! Reset CPU when watch dog time out
//
#define xWDT_RESET_FUNCTION     0

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
//! +------------------------+-----------------+------------------------+
//! |Clock Configuration     |       CoX       |         KLxx           |
//! |------------------------|-----------------|------------------------|
//! |xWDT_S_INTSL            |    Mandatory    |            Y           |
//! |------------------------|-----------------|------------------------|
//! |xWDT_S_EXTSL            |    Mandatory    |            N           |
//! |------------------------|-----------------|------------------------|
//! |xWDT_S_BUSCLK           |  Non-Mandatory  |            Y           |
//! |------------------------|-----------------|------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! The watch dog source is int. 1 KHz
//
#define xWDT_S_INTSL            0x0000000 

//
//! The watch dog source is ext.
//
#define xWDT_S_EXTSL            0

//
//! The watch dog source is the system bus clock
//
#define xWDT_S_BUSCLK           0x00000002 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup xWDT_Mode_Config xWDT Mode Configuration
//! \brief Values that show xWDT Mode Configuration
//! \n
//! \section xWDT_Mode_Config_Section 1. Where to use this group
//! Watch dog Mode Configs. Such as clock source, Prescaler divider.
//! Values that can be passed to xWDTInit as the ulConfig parameter 
//! \n
//! \section xWDT_Mode_Config_CoX 2.CoX Port Details 
//! \verbatim
//! +--------------------------+-----------------+------------------------+
//! |  Mode_Configuration      |       CoX       |         KLxx           |
//! |--------------------------|-----------------|------------------------|
//! |  xWDT_MODE_NORMAL        |  Non-Mandatory  |           Y            |
//! |--------------------------|-----------------|------------------------|
//! |  xWDT_MODE_WINDOWED      |  Non-Mandatory  |           Y            |
//! |--------------------------|-----------------|------------------------|
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! The watch dog mode: Normal
//
#define xWDT_MODE_NORMAL        WDT_MODE_NORMAL         

//
//! The watch dog mode: Windowed
//
#define xWDT_MODE_WINDOWED      WDT_MODE_WINDOWED       

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
//! +--------------------------+------------------+-----------------------------+
//! |  Time Reload Config      |       CoX        |         KLxx                |
//! |--------------------------|------------------|-----------------------------|
//! |                          |                  |   xWDT_INTERVAL_1K_32MS     |
//! |                          |                  |-----------------------------|
//! |  Time Interval value     |  Non-Mandatory   |   xWDT_INTERVAL_1K_256MS    |
//! |                          |                  |-----------------------------|
//! |                          |                  |   xWDT_INTERVAL_1K_1024MS   |
//! |                          |                  |-----------------------------|
//! |                          |                  |   xWDT_INTERVAL_BUS_2_13T   |
//! |                          |                  |-----------------------------|
//! |                          |                  |   xWDT_INTERVAL_BUS_2_16T   |
//! |                          |                  |-----------------------------|
//! |                          |                  |   xWDT_INTERVAL_BUS_2_18T   |
//! +--------------------------+------------------+-----------------------------+
//! \endverbatim
//! @{
//
//*****************************************************************************

//
//! Timeout Interval Configure : Inter 1K clock 32ms
//
#define xWDT_INTERVAL_1K_32MS   WDT_INTERVAL_1K_32MS

//
//! Timeout Interval Configure : Inter 1K clock 256ms
//

#define xWDT_INTERVAL_1K_256MS  WDT_INTERVAL_1K_256MS   

//
//! Timeout Interval Configure : Inter 1K clock 1024ms
//
#define xWDT_INTERVAL_1K_1024MS WDT_INTERVAL_1K_1024MS 

//
//! Timeout Interval Configure : Bus clock 2 13 * Tick
//
#define xWDT_INTERVAL_BUS_2_13T WDT_INTERVAL_BUS_2_13T  

//
//! Timeout Interval Configure : Bus clock 2 16 * Tick
//
#define xWDT_INTERVAL_BUS_2_16T WDT_INTERVAL_BUS_2_16T  

//
//! Timeout Interval Configure : Bus clock 2 18 * Tick
//
#define xWDT_INTERVAL_BUS_2_18T WDT_INTERVAL_BUS_2_18T



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
//! |xWDT API                |       CoX      |           KLxx         |
//! |------------------------|----------------|------------------------|
//! |xWDTInit                |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTEnable              |    Mandatory   |            Y           |
//! |------------------------|----------------|------------------------|
//! |xWDTIntCallbackInit     |    Mandatory   |            N           |
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
//! Selection and Watch dog Mode selection.
//! Details please refer to \ref xWDT_Clock_Config and
//! xWDT_Time_Reload_Config and xWDT_Mode_Config.
//!
//! \param ulReload is the Timer's reload value.
//!
//! This function is to configureThe WatchDog Timer(WDT)'s Timer Interval.
//! There are three factors to determine the Timer Interval, they are:
//! - clock source
//! - Prescaler divider
//! - reload value
//!
//! The \e ulConfig parameter contains clock source and Prescaler divider and 
//! Mode;
//! When being used,this parameter is the logical OR of the two values.
//! For KLxx  ,there is no Prescaler divider and the clock source can be:
//! \b xWDT_S_INTSL,\b xWDT_S_BUSCLK.
//! Details please refer to \ref xWDT_Clock_Config_CoX.
//! The \e ulReload parameter is the value which will reload the counter when 
//! feeding the watch dog.The value range depends on the number of bits of 
//! corresponding counter.
//! For KLxx  , the reload value can only be one of the following:
//! \b xWDT_INTERVAL_1K_32MS, \b xWDT_INTERVAL_1K_256MS,
//! \b xWDT_INTERVAL_1K_1024MS, \b xWDT_INTERVAL_BUS_2_13T,
//! \b xWDT_INTERVAL_BUS_2_16T, \b xWDT_INTERVAL_BUS_2_18T,
//! Details please refer to \ref xWDT_Time_Reload_Config_CoX.
//! 
//! \note When using watch dog xWDTEnable() should be called after call 
//! xWDTInit(ulBase, ulConfig, ulReload).
//!
//! \return None.
//
//*****************************************************************************
#define xWDTInit(ulBase, ulConfig, ulReload)                                  \
                                WDTInit((ulConfig) | (ulReload))

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
                                WDTEnable()


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
#define xWDTIntCallbackInit(ulBase, xtWDTCallback)
                               
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
                                WDTDisable()
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
                                WDTRestart()

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
#define xWDTFunctionEnable(ulBase, ulFunction)
        
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
#define xWDTFunctionDisable(ulBase, ulFunction)

        
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
//! \addtogroup KLxx_WDT
//! @{
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup WDT_Mode_Config WDT Mode Configuration
//! \brief Values that show WDT Mode Configuration
//! Values that can be passed to WDTimerInit().
//! @{
//
//*****************************************************************************

//
//! The watch dog mode: Normal
//
#define WDT_MODE_NORMAL         0x00000000  

//
//! The watch dog mode: Windowed
//
#define WDT_MODE_WINDOWED       0x00000001  

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
//! Timeout Interval Configure : Inter 1K clock 32ms
//
#define WDT_INTERVAL_1K_32MS    0x00000004

//
//! Timeout Interval Configure : Inter 1K clock 256ms
//

#define WDT_INTERVAL_1K_256MS   0x00000008   

//
//! Timeout Interval Configure : Inter 1K clock 1024ms
//
#define WDT_INTERVAL_1K_1024MS  0x0000000C  

//
//! Timeout Interval Configure : Bus clock 2 13 * Tick
//
#define WDT_INTERVAL_BUS_2_13T  0x00000006  

//
//! Timeout Interval Configure : Bus clock 2 16 * Tick
//
#define WDT_INTERVAL_BUS_2_16T  0x0000000A  

//
//! Timeout Interval Configure : Bus clock 2 18 * Tick
//
#define WDT_INTERVAL_BUS_2_18T  0x0000000E  



//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_WDT_Exported_APIs KLxx   WDT API
//! \brief KLxx   WDT API Reference.
//! @{
//! @{
//
//*****************************************************************************

extern void WDTimerInit(unsigned long ulConfig);
extern void WDTimerEnable(void);
extern void WDTimerDisable(void);
extern void WDTimerRestart(void);

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


