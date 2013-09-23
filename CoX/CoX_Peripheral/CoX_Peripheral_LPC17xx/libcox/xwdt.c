#include "xhw_types.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xhw_wdt.h"
#include "xwdt.h"

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
unsigned long WDTIntCallbackInit(xtEventCallback pfnCallback)
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
void WDTCfg(unsigned long ulCfg, unsigned long ulValue)
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
//! \brief  Feed WDT.
//!         This function is used to Feed WDT Module in case of WDT time-out.
//!
//! \param  None.
//!
//! \return None.
//!
//! \note   User must call this function to feed watchdog before WDT counter
//!         overflow.
//!
//
//*****************************************************************************
void WDTFeed(void)
{
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
void WDTEnable(void)
{
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
void WDTDisable(void)
{
    // Enable Watchdog bit.
    xHWREG(WDT_BASE + WDT_MOD) &= ~WDMOD_EN;

    // Feed dog to clock the watchdog.
    xHWREG(WDT_BASE + WDT_FEED) = (unsigned long) 0xAA;
    xHWREG(WDT_BASE + WDT_FEED) = (unsigned long) 0x55;
}

//*****************************************************************************
//
//! \brief  Get WDT status.
//!         This function is used to get WDT status.
//!
//! \param  None.
//!
//! \return The status of WDT, which contains of the OR of following value:
//!         - \ref WDT_FLAG_TIMEOUT
//!         - \ref WDT_FLAG_INT
//!
//
//*****************************************************************************
unsigned long WDTStatusFlagGet(void)
{
    return xHWREG(WDT_BASE + WDT_MOD);
}

//*****************************************************************************
//
//! \brief  Check WDT status flag.
//!         This function checks whether special flag is set or not.
//!
//! \param  [in] ulFlags is the flag you want to check
//!         This value is the OR of the following value:
//!              - \ref WDT_FLAG_TIMEOUT
//!              - \ref WDT_FLAG_INT
//!
//! \return The status of special flag.
//!         - xtrue The check flag has been set.
//!         - xflase The check flag has not been set.
//!
//
//*****************************************************************************
xtBoolean WDTStatusFlagCheck(unsigned long ulFlags)
{
    // Parameters valid ?
    xASSERT((ulFlags  == WDT_FLAG_TIMEOUT) ||
            (ulFlags  == WDT_FLAG_INT    ) ||
            (ulFlags  == (WDT_FLAG_TIMEOUT |  WDT_FLAG_INT))
           );

    // Check flag.
    if( xHWREG(WDT_BASE + WDT_MOD) & ulFlags )
    {
        return (xtrue);
    }
    else
    {
        return (xfalse);
    }
}

//*****************************************************************************
//
//! \brief  Clear WDT status flag.
//!         This function can be used to clear special wdt status flag.
//!
//! \param  [in] ulFlags is WDT status flag.
//!              This parameter must be \ref WDT_FLAG_TIMEOUT.
//!
//! \return None.
//!
//! \note
//!       1. This function only can be used to clear WDT_FLAG_TIMEOUT flag.
//!       2. When mcu reset, user must call \ref WDTStatusFlagCheck to check
//!          whether watchdog timeout, if timeout flag is set, then user must
//!          call \ref WDTStatusFlagClear to clear this flag.
//!
//
//*****************************************************************************
void WDTStatusFlagClear(unsigned long ulFlags)
{

    // Parameters valid ?
    xASSERT(ulFlags == WDT_FLAG_TIMEOUT);

    // Clear Timeout Flag.
    xHWREG(WDT_BASE + WDT_MOD) &= ~WDMOD_TOF;

    // Feed watchdog to action.
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

