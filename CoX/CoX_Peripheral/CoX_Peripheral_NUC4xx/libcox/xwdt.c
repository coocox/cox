//*****************************************************************************
//
//! \file xwdt.c
//! \brief Driver for the WDT
//! \version V2.2.1.0
//! \date 11/15/2013
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
#include "CoX.h"
#include "xhw_sysctl.h"
#include "xhw_wdt.h"



//*****************************************************************************
//
// An array is WATCHDOG Callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnWATCHDOGHandlerCallbacks[1]={0};


//*****************************************************************************
//
//! \brief The WatchDog Timer(WDT) default IRQ, declared in StartUp code. 
//!
//! \param None.
//!
//! This function is to give a default WatchDog Timer(WDT) IRQ service.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTIntHandler(void)
{
    //
    // Clear the WDT INT Flag
    //
    xHWREG(WDT_WTCR) |= WDT_WTCR_WTIF;

    if (g_pfnWATCHDOGHandlerCallbacks[0] != 0)
    {
        g_pfnWATCHDOGHandlerCallbacks[0](0, 0, 0, 0);
    }
}

//*****************************************************************************
//
//! \brief Configurate The WatchDog Timer(WDT)'s Timer Interval. 
//!
//! \param ulConfig is the Timer Interval Selection.
//!
//! This function is to Configurate The WatchDog Timer(WDT)'s Timer Interval.
//!
//! The \e ulConfig parameter is the one of any of the following:
//! \b WDT_INTERVAL_2_4T,\b WDT_INTERVAL_2_6T,\b WDT_INTERVAL_2_8T,
//! \b WDT_INTERVAL_2_10T,\b WDT_INTERVAL_2_12T,\b WDT_INTERVAL_2_14T,
//! \b WDT_INTERVAL_2_16T,\b WDT_INTERVAL_2_18T.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerInit(unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT((ulConfig == WDT_INTERVAL_2_4T) || 
            (ulConfig == WDT_INTERVAL_2_6T) ||
            (ulConfig == WDT_INTERVAL_2_8T) ||
            (ulConfig == WDT_INTERVAL_2_10T) ||
            (ulConfig == WDT_INTERVAL_2_12T) ||
            (ulConfig == WDT_INTERVAL_2_14T) ||
            (ulConfig == WDT_INTERVAL_2_16T) ||
            (ulConfig == WDT_INTERVAL_2_18T));         

    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) &= ~WDT_WTCR_WTE;
    xHWREG(WDT_WTCR) &= ~WDT_WTCR_WTIS_M;
    xHWREG(WDT_WTCR) |= ulConfig;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief Enable the Watchdog timer. 
//!
//! \param None.
//!
//! This function is to Enable the Watchdog timer.
//!
//! \note When use watch dog WDTimerEnable() should be called after call 
//! WDTimerInit(ulConfig).
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerEnable(void)
{   
    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) |= WDT_WTCR_WTE;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief Disable the Watchdog timer. 
//!
//! \param None.
//!
//! This function is to disable the Watchdog timer.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerDisable(void)
{   
    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) &= ~WDT_WTCR_WTE;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief Restart the Watchdog timer interrupt. 
//!
//! \param None.
//!
//! This function is to restart the Watchdog timer interrupt.
//!
//! \note this is use to feed the watch dog.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerRestart(void)
{   
    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) |= WDT_WTCR_WTR;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief Initialize interrupt callback for the Watchdog timer.
//!
//! \param xtPortCallback is callback for the Watchdog timer.
//!
//! Initialize interrupt callback for the Watchdog timer.
//!
//! \return None.
//
//*****************************************************************************
void
WDTimerIntCallbackInit(xtEventCallback xtWDTCallback)
{
    
    if (xtWDTCallback != 0)
    {
        g_pfnWATCHDOGHandlerCallbacks[0] = xtWDTCallback;
    }
}

//*****************************************************************************
//
//! \brief Enable the watch dog timer's function. 
//!
//! \param ulFunction is the watch dog timer's function.
//!
//! This function is to enable the watch dog timer's function such as Interrupt
//! reset\wake up \stop in ICE mode.
//! 
//! The \e ulFunction parameter is the OR value of any of the following:
//! \b WDT_INT_FUNCTION,\b WDT_RESET_FUNCTION,\b WDT_WAKEUP_FUNCTION,
//! \b WDT_HOLD_IN_ICE.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerFunctionEnable(unsigned long ulFunction)
{   
    //
    // Check the arguments.
    //
    xASSERT(((ulFunction & WDT_INT_FUNCTION) == WDT_INT_FUNCTION) || 
            ((ulFunction & WDT_RESET_FUNCTION) == WDT_RESET_FUNCTION) ||
            ((ulFunction & WDT_WAKEUP_FUNCTION) == WDT_WAKEUP_FUNCTION) ||
            ((ulFunction & WDT_HOLD_IN_ICE) == WDT_HOLD_IN_ICE));
    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) |= ulFunction;
    SysCtlKeyAddrLock();
}


//*****************************************************************************
//
//! \brief Disable the watch dog timer's function. 
//!
//! \param ulFunction is the watch dog timer's function.
//!
//! This function is to disable the watch dog timer's function such as Interrupt
//! reset\wake up \stop in ICE mode.
//! 
//! The \e ulFunction parameter is the OR value of any of the following:
//! \b WDT_INT_FUNCTION,\b WDT_RESET_FUNCTION,\b WDT_WAKEUP_FUNCTION,
//! \b WDT_HOLD_IN_ICE.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTimerFunctionDisable(unsigned long ulFunction)
{   
    //
    // Check the arguments.
    //
    xASSERT(((ulFunction & WDT_INT_FUNCTION) == WDT_INT_FUNCTION) || 
            ((ulFunction & WDT_RESET_FUNCTION) == WDT_RESET_FUNCTION) ||
            ((ulFunction & WDT_WAKEUP_FUNCTION) == WDT_WAKEUP_FUNCTION) ||
            ((ulFunction & WDT_HOLD_IN_ICE) == WDT_HOLD_IN_ICE));
    SysCtlKeyAddrUnlock();
    xHWREG(WDT_WTCR) &= ~ulFunction;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief Clear the Watchdog Timer Wake-Up Flag of the WDT. 
//!
//! \param None.
//!
//! This function is to clear the Watchdog Timer Wake-Up Flag of the WDT.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTWakeUpFlagClear(void)
{
    xHWREG(WDT_WTCR) |= WDT_WTCR_WTWKF;
}

//*****************************************************************************
//
//! \brief Clear the Watchdog Timer Reset Flag of the WDT. 
//!
//! \param None.
//!
//! This function is to clear the Watchdog Timer Reset Flag of the WDT.
//!
//! \return None.
//
//*****************************************************************************
void 
WDTResetFlagClear(void)
{
    xHWREG(WDT_WTCR) |= WDT_WTCR_WTRF;
}


//*****************************************************************************
//
//! \brief  Configurate The WatchDog Timer(WDT)'s Timer Interval.
//!         This function is to configure The WatchDog Timer(WDT)'s Timer Interval.
//!         There are three factors to determine the Timer Interval, they are:
//!             - clock source
//!             - Prescaler divider
//!             - reload value
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//!
//! \param  [in] ulConfig is the WDT clock source Selection.
//!              - \ref xWDT_S_INTSL
//!              - \ref xWDT_S_EXTSL
//!
//! \param  [in] ulReload is the WDT's reload value.
//!              0xFF <= ulReload <= 0xFFFFFFFF
//!
//! \return None.
//!
//! \note   xWDTInit(ulBase, ulConfig, ulReload) must be called before function:
//!         - \ref xWDTEnable and - \ref xWDTFunctionEnable.
//!
//
//*****************************************************************************
void xWDTInit(unsigned long ulBase, unsigned long ulConfig,
              unsigned long ulReload)
{
	SysCtlIPClockDividerSet(ulConfig);
	WDTimerInit(ulReload);
}

//*****************************************************************************
//
//! \brief  Enable the Watchdog timer module.
//!         This function is to Enable the Watchdog timer and start counter.
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//!
//! \return None.
//!
//! \note   xWDTInit(ulBase, ulConfig, ulReload) must be called before function:
//!         - \ref xWDTEnable and - \ref xWDTFunctionEnable.
//
//*****************************************************************************
void xWDTEnable(unsigned long ulBase)
{
	WDTimerEnable();
}

//*****************************************************************************
//
//! \brief  Disable the Watchdog timer.
//!         This function is to Disable the Watchdog timer module and stop
//!         the counter.
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//!
//! \return None.
//!
//
//*****************************************************************************
void xWDTDisable(unsigned long ulBase)
{
	WDTimerDisable();
}

//*****************************************************************************
//
//! \brief  Register user interrupt callback function for the Watchdog timer.
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//!
//! \param  [in] xtPortCallback is user's callback function for the Watchdog
//!              timer.
//!
//! \return None.
//
//*****************************************************************************
void xWDTIntCallbackInit(unsigned long ulBase,
                         xtEventCallback xtWDTCallback)
{
	WDTimerIntCallbackInit(xtWDTCallback);
}

//*****************************************************************************
//
//! \brief  Restart the Watchdog timer counter.
//!         This function is to restart the Watchdog timer by feed watchdog.
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//!
//! \return None.
//!
//! \note   User can use this function to feed the watch dog interval.
//
//*****************************************************************************
void xWDTRestart(unsigned long ulBase)
{
	WDTimerRestart();
}

//*****************************************************************************
//
//! \brief  Enable the watch dog timer's function.
//!         This function is to Enable the watch dog timer's function such as
//!         Interrupt reset.
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//!
//! \param  [in] ulFunction is the watch dog timer's function.
//!              This parameter is the OR value of any of the following:
//!              - \ref xWDT_INT_FUNCTION
//!              - \ref xWDT_RESET_FUNCTION
//!
//! \note   xWDTInit(ulBase, ulConfig, ulReload) must be called before function:
//!         \ref xWDTEnable and \ref xWDTFunctionEnable.
//
//*****************************************************************************
void xWDTFunctionEnable(unsigned long ulBase, unsigned long ulFunction)
{
	WDTimerFunctionEnable(ulFunction);
}

//*****************************************************************************
//
//! \brief  Disable the watch dog timer's function.
//!         This function is to disable the watch dog timer's function such as
//!         Interrupt reset.
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//!
//! \param  [in] ulFunction is the watch dog timer's function.
//!              This parameter is the OR value of any of the following:
//!              - \ref xWDT_INT_FUNCTION
//!              - \ref xWDT_RESET_FUNCTION
//!
//! \return None.
//!
//! \note   For LPC17xx, You can't Disable Those functions.
//
//*****************************************************************************
void xWDTFunctionDisable(unsigned long ulBase, unsigned long ulFunction)
{
	WDTimerFunctionDisable(ulFunction);
}
