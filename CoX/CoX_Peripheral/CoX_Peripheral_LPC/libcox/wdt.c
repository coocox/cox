//*****************************************************************************
//
//! \file wdt.c
//! \brief Driver for the WDT
//! \version V3.0.0.0
//! \date 8/15/2014
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2014, CooCox 
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
#include "hw_sysctl.h"
#include "hw_wdt.h"

#define WDT_CFG_MODE_M          (BIT_32_1 | BIT_32_0)
#define WDT_CFG_CLKSRC_M        (BIT_32_3 | BIT_32_2)

static unsigned long _PreValue = 0;

//*****************************************************************************
//
// An array is Watchdog callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnWDTHandlerCallbacks = 0;

//*****************************************************************************
//
//! \brief  WDT interrupt handler.
//!         This function is the WDT interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//!
//! \return None.
//!
//
//*****************************************************************************
void WDTIntHandler(void)
{
    if(g_pfnWDTHandlerCallbacks != 0)
    {
        g_pfnWDTHandlerCallbacks(0, 0, 0, 0);
    }
    else
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief  Register user interrupts callback function  for the WDT.
//!
//! \param  [in] xtPortCallback is user callback for the WDT.
//!
//! \return None.
//
//*****************************************************************************
unsigned long xWDTIntCallbackInit(unsigned long ulBase, xtEventCallback pfnCallback)
{
    // Check the parameters.
    xASSERT(pfnCallback != 0);

    g_pfnWDTHandlerCallbacks = pfnCallback;

    return (0);

}

//*****************************************************************************
//
//! \brief  Configurate The WatchDog Timer Module.
//!         This function is to configure The WatchDog Timer(WDT) clock source
//!         and mode.
//!
//! \param  [in] ulConfig is the WDT clock source Selection and Mode.
//!              This value can be OR of two type of value:
//!              - clock source
//!                 - \ref WDT_CFG_CLKSRC_IRC
//!                 - \ref WDT_CFG_CLKSRC_APB
//!                 - \ref WDT_CFG_CLKSRC_RTC
//!              - clock source
//!                 - \ref WDT_CFG_INT_MODE
//!                 - \ref WDT_CFG_RESET_MODE
//!
//! \param  [in] ulValue is the Timer's reload value.
//!              0xFF <= ulReload <= 0xFFFFFFFF
//!
//! \return None.
//!
//! \note   xWDTInit(ulBase, ulConfig, ulReload) must be called before function:
//!         \ref xWDTEnable and \ref xWDTFunctionEnable.
//!
//
//*****************************************************************************
static void WDTCfg(unsigned long ulCfg, unsigned long ulValue)
{
    unsigned long ulTmpReg = 0;

/************ Configure Watchdog Mode and Clock source **************/
    switch(ulCfg & WDT_CFG_MODE_M)
    {
        case WDT_CFG_INT_MODE:                             // Triggle Interrupt when underflow.
            {
                ulTmpReg = xHWREG(WDT_BASE + WDT_MOD);
                //ulTmpReg |= WDMOD_EN;
                ulTmpReg &= ~WDMOD_RESET;
                xHWREG(WDT_BASE + WDT_MOD) = ulTmpReg;
                break;
            }
        case WDT_CFG_RESET_MODE:                           // Reset MCU when underflow.
            {
                ulTmpReg = xHWREG(WDT_BASE + WDT_MOD);
                ulTmpReg |= /*WDMOD_EN |*/ WDMOD_RESET;
                xHWREG(WDT_BASE + WDT_MOD) = ulTmpReg;
                break;
            }
    }

    switch(ulCfg & WDT_CFG_CLKSRC_M)
    {
        case WDT_CFG_CLKSRC_IRC:                           // Internal RC clock.
            {
                ulTmpReg = xHWREG(WDT_BASE + WDT_CLKSEL);
                ulTmpReg &= ~WDCLKSEL_WDSEL_M;
                ulTmpReg |= WDCLKSEL_WDSEL_IRC;
                xHWREG(WDT_BASE + WDT_CLKSEL) = ulTmpReg;
                break;
            }
        case WDT_CFG_CLKSRC_APB:                           // APB Clock source.
            {
                ulTmpReg = xHWREG(WDT_BASE + WDT_CLKSEL);
                ulTmpReg &= ~WDCLKSEL_WDSEL_M;
                ulTmpReg |= WDCLKSEL_WDSEL_APB;
                xHWREG(WDT_BASE + WDT_CLKSEL) = ulTmpReg;
                break;
            }
        case WDT_CFG_CLKSRC_RTC:                          // RTC Clock source.
            {
                ulTmpReg = xHWREG(WDT_BASE + WDT_CLKSEL);
                ulTmpReg &= ~WDCLKSEL_WDSEL_M;
                ulTmpReg |= WDCLKSEL_WDSEL_RTC;
                xHWREG(WDT_BASE + WDT_CLKSEL) = ulTmpReg;
                break;
            }
    }


/************* Configure Watchdog const value register **************/
    if(ulValue < (unsigned long)0xFF)
    {
        ulValue = 0xFF;
    }

    xHWREG(WDT_BASE + WDT_TC) = ulValue;

    // Feed watchdog.
    xHWREG(WDT_BASE + WDT_FEED) = (unsigned long) 0xAA;
    xHWREG(WDT_BASE + WDT_FEED) = (unsigned long) 0x55;
}

//*****************************************************************************
//
//! \brief  Enable WDT Module.
//!         This function is used to Enable WDT module and start counter.
//!
//! \param  None.
//!
//! \return None.
//!
//
//*****************************************************************************
void xWDTEnable(unsigned long ulBase)
{
    // Avoid Compiler warning.
    (void) ulBase;
	
    // Enable Watchdog bit.
    xHWREG(WDT_BASE + WDT_MOD) |= WDMOD_EN;

    // Feed dog to clock the watchdog.
    xHWREG(WDT_BASE + WDT_FEED) = (unsigned long) 0xAA;
    xHWREG(WDT_BASE + WDT_FEED) = (unsigned long) 0x55;
}

//*****************************************************************************
//
//! \brief  Disable WDT Module.
//!         This function is used to Disable WDT module and Stop counter.
//!
//! \param  None.
//!
//! \return None.
//!
//
//*****************************************************************************
void xWDTDisable(unsigned long ulBase)
{
    // Avoid Compiler warning.
    (void) ulBase;
	
    // Enable Watchdog bit.
    xHWREG(WDT_BASE + WDT_MOD) &= ~WDMOD_EN;

    // Feed dog to clock the watchdog.
    xHWREG(WDT_BASE + WDT_FEED) = (unsigned long) 0xAA;
    xHWREG(WDT_BASE + WDT_FEED) = (unsigned long) 0x55;
}

//*****************************************************************************
//
//! \brief  Configurate The WatchDog Timer(WDT)'s Timer Interval.
//!         This function is to configureThe WatchDog Timer(WDT)'s Timer Interval.
//!         There are three factors to determine the Timer Interval, they are:
//!             - clock source
//!             - Prescaler divider
//!             - reload value
//!
//! \param  [in] ulBase is the base address of the WatchDog Timer(WDT) module.
//!              This value must be \ref xWDT_BASE.
//!
//! \param  [in] ulConfig is the Timer's Prescaler divider and clock source Selection.
//!              - \ref xWDT_S_INTSL
//!              - \ref xWDT_S_EXTSL
//!
//! \param  [in] ulReload is the Timer's reload value.
//!              0xFF <= ulReload <= 0xFFFFFFFF
//!
//! \return None.
//!
//! \note   xWDTInit(ulBase, ulConfig, ulReload) must be called before function:
//!         \ref xWDTEnable and \ref xWDTFunctionEnable.
//!
//
//*****************************************************************************
void xWDTInit(unsigned long ulBase, unsigned long ulConfig, unsigned long ulReload)
{
    // Avoid Compiler warning.
    (void) ulBase;

    // Configure WDT clock source.
    _PreValue = ulReload;
    WDTCfg(ulConfig, ulReload);
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
    // Avoid Compiler warning.
    (void) ulBase;

    // User must call xWDTInit function to set reload value at first!
    if(_PreValue == 0)
    {
        while(1);
    }

    // Configure WDT interrupt/reset mode.
    WDTCfg(ulFunction, _PreValue);
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
    // Avoid compiler warning
    (void) ulBase;
    (void) ulFunction;

    // Check input parameters valid.
    xASSERT(ulBase == xWDT_BASE);
    xASSERT((ulFunction == xWDT_INT_FUNCTION) || (ulFunction == xWDT_RESET_FUNCTION));

    // Set watch dog mode register to default value.
    xHWREG(WDT_BASE + WDT_MOD) = 0x00;

    // Feed watchdog.
    xHWREG(WDT_BASE + WDT_FEED) = (unsigned long) 0xAA;
    xHWREG(WDT_BASE + WDT_FEED) = (unsigned long) 0x55;
}
