//*****************************************************************************
//
//! \file xtimer.c
//! \brief Driver for the Timer
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
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_timer.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xtimer.h"

//*****************************************************************************
//
// An array is Timer Callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnTimerHandlerCallbacks[4]={0};

static unsigned long ulEXTClockFreq;

//*****************************************************************************
//
//! \brief The Timer 0 default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default Timer IRQ service.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TIMER0IntHandler(void)
{
    unsigned long ulBase = TIMER0_BASE;
    unsigned long ulTemp0,ulTemp1;
    //
    //! Clear the Timer INT Flag
    //
    ulTemp0 = (xHWREG(ulBase + TIMER_O_TISR) & TIMER_TISR_TIF);
    xHWREG(ulBase + TIMER_O_TISR) = ulTemp0;     
    ulTemp1 = (xHWREG(ulBase + TIMER_O_TEISR) & TIMER_TISR_TIF);
    xHWREG(ulBase + TIMER_O_TEISR) = ulTemp1;

    if (g_pfnTimerHandlerCallbacks[0] != 0)        
    {
        g_pfnTimerHandlerCallbacks[0](0, 0, ulTemp0 | ulTemp1, 0);
    }
}

//*****************************************************************************
//
//! \brief The Timer 1 default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default Timer IRQ service.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TIMER1IntHandler(void)
{
    unsigned long ulBase = TIMER1_BASE;
    unsigned long ulTemp0,ulTemp1;
    //
    //! Clear the Timer INT Flag
    //
    ulTemp0 = (xHWREG(ulBase + TIMER_O_TISR) & TIMER_TISR_TIF);
    xHWREG(ulBase + TIMER_O_TISR) = ulTemp0;     
    ulTemp1 = (xHWREG(ulBase + TIMER_O_TEISR) & TIMER_TISR_TIF);
    xHWREG(ulBase + TIMER_O_TEISR) = ulTemp1;

    if (g_pfnTimerHandlerCallbacks[1] != 0)        
    {
        g_pfnTimerHandlerCallbacks[1](0, 0, ulTemp0 | ulTemp1, 0);
    }
}


//*****************************************************************************
//
//! \brief The Timer 2 default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default Timer IRQ service.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TIMER2IntHandler(void)
{
    unsigned long ulBase = TIMER2_BASE;
    unsigned long ulTemp0,ulTemp1;
    //
    //! Clear the Timer INT Flag
    //
    ulTemp0 = (xHWREG(ulBase + TIMER_O_TISR) & TIMER_TISR_TIF);
    xHWREG(ulBase + TIMER_O_TISR) = ulTemp0;     
    ulTemp1 = (xHWREG(ulBase + TIMER_O_TEISR) & TIMER_TISR_TIF);
    xHWREG(ulBase + TIMER_O_TEISR) = ulTemp1;

    if (g_pfnTimerHandlerCallbacks[2] != 0)        
    {
        g_pfnTimerHandlerCallbacks[2](0, 0, ulTemp0 | ulTemp1, 0);
    }
}


//*****************************************************************************
//
//! \brief The Timer 3 default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default Timer IRQ service.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TIMER3IntHandler(void)
{
    unsigned long ulBase = TIMER3_BASE;
    unsigned long ulTemp0,ulTemp1;
    //
    //! Clear the Timer INT Flag
    //
    ulTemp0 = (xHWREG(ulBase + TIMER_O_TISR) & TIMER_TISR_TIF);
    xHWREG(ulBase + TIMER_O_TISR) = ulTemp0;     
    ulTemp1 = (xHWREG(ulBase + TIMER_O_TEISR) & TIMER_TISR_TIF);
    xHWREG(ulBase + TIMER_O_TEISR) = ulTemp1;

    if (g_pfnTimerHandlerCallbacks[3] != 0)        
    {
        g_pfnTimerHandlerCallbacks[3](0, 0, ulTemp0 | ulTemp1, 0);
    }
}

//*****************************************************************************
//
//! \internal
//! \brief The function is used to get timer clock.
//!
//! \param ulBase is the base address of the timer port.
//!
//! This function gets the timer clock
//! when set the tick frequency of timer.
//!
//! \return Returns the Current timer Clock.
//
//*****************************************************************************
static unsigned long
TimerClockGet(unsigned long ulBase)
{
    volatile unsigned long ucClockSource;
    volatile unsigned long ulTimerClock = 0;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    ucClockSource = (xHWREG(SYSCLK_CLKSEL1) >> (8 + 
                    (((ulBase - TIMER0_BASE)/32)%6)*4)) & 0x7;

    if (ucClockSource == 0)
    {
        //
        // Option 0: Get External Clock From DrvSYS Setting.
        //
        ulTimerClock = 12000000;
    }
    else if (ucClockSource == 1)
    {
        //
        // Option 1: 32K.
        //  
        ulTimerClock = 32768;
    }
    else if (ucClockSource == 2)
    {
        //
        // COption 2: HCLK.
        //
        ulTimerClock = SysCtlHClockGet();
    } 
    else if (ucClockSource == 3)
    {
        //
        // Option 3: External Trigger.
        //
        ulTimerClock = ulEXTClockFreq;
    } 
    else
    {     
        //
        // Option 4: 22MHz.
        //
        ulTimerClock = 22118400;
    }
    return ulTimerClock;
}

//*****************************************************************************
//
//! \brief Configurate The Timer's mode and tick frequency. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulConfig is the mode Configuratation of the Timer port.
//! \param ulTickFreq is the tick frequency of the Timer port.
//!
//! This function is to configurate The Timer's mode and tick frequency.
//!
//! The \e ulConfig parameter can be one of the values:
//! \b TIMER_MODE_ONESHOT, \b TIMER_MODE_PERIODIC, \b TIMER_MODE_TOGGLE and
//! \b TIMER_MODE_CONTINUOUS.
//!
//! The \e ulTickFreq parameter is the the timer tick frequency.It can be any
//! values but ulTickFreq > 0 and ulTickFreq < timer clock source.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerInitConfig(unsigned long ulBase, unsigned long ulConfig,
                unsigned long ulTickFreq)
{    
    unsigned long ulPreScale;
    unsigned long ulTCMPRValue;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    xASSERT(((ulConfig & 0xE7000000) == TIMER_MODE_ONESHOT) || 
            ((ulConfig & 0xE7000000) == TIMER_MODE_PERIODIC) ||
            ((ulConfig & 0xE7000000) == TIMER_MODE_TOGGLE) ||
            ((ulConfig & 0xE7000000) == TIMER_MODE_CONTINUOUS));

    xASSERT(ulTickFreq > 0);
    
    switch(ulBase)
    {
        case TIMER0_BASE:
            SysCtlPeripheralReset(SYSCTL_PERIPH_TMR0);
            break;
        case TIMER1_BASE:
            SysCtlPeripheralReset(SYSCTL_PERIPH_TMR1);
            break;
        case TIMER2_BASE:
            SysCtlPeripheralReset(SYSCTL_PERIPH_TMR2);
            break;
        case TIMER3_BASE:
            SysCtlPeripheralReset(SYSCTL_PERIPH_TMR3);
            break; 
    }
     
    //
    // Disable timer.
    //
    xHWREG(ulBase + TIMER_O_TCSR) = 0;

    //
    // Write 1 to clear interrupt flag for safty .
    //
    xHWREG(ulBase + TIMER_O_TISR) |= TIMER_TISR_TIF;
    
    for (ulPreScale=1; ulPreScale<256; ulPreScale++)
    {
        ulTCMPRValue = TimerClockGet(ulBase) / (ulTickFreq * ulPreScale);

        /* The TCMPR value must > 1 */
        if ((ulTCMPRValue > 1) && (ulTCMPRValue < 0x1000000))
            break;
    }
    xHWREG(ulBase + TIMER_O_TCMPR) = ulTCMPRValue;
    xHWREG(ulBase + TIMER_O_TCSR) = ulPreScale | ulConfig;
}

//*****************************************************************************
//
//! \brief Configurate The Timer as a counter and configurate mode and Boundary. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulConfig is the mode Configuratation of the Timer port.
//! \param ulTickFreq is the tick frequency of the Timer port.
//!
//! This function is to configurate The Timer as a counter and configurate 
//! mode and Boundary.
//!
//! The \e ulConfig parameter can be one of the values:
//! \b TIMER_MODE_ONESHOT, \b TIMER_MODE_PERIODIC, \b TIMER_MODE_TOGGLE and
//! \b TIMER_MODE_CONTINUOUS.
//!
//! The \e ulCounterBound parameter is the the timer counter Boundary.It can be 
//! the values which  ulCounterBound > 1 and ulCounterBound < 1000000.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCounterInitConfig(unsigned long ulBase, unsigned long ulConfig,
                       unsigned long ulCounterBound)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    xASSERT(((ulConfig & 0xE7000000) == TIMER_MODE_ONESHOT) || 
            ((ulConfig & 0xE7000000) == TIMER_MODE_PERIODIC) ||
            ((ulConfig & 0xE7000000) == TIMER_MODE_TOGGLE) ||
            ((ulConfig & 0xE7000000) == TIMER_MODE_CONTINUOUS));

    xASSERT((ulCounterBound > 1) && (ulCounterBound < 1000000));
    
    //
    // Disable timer.
    //
    xHWREG(ulBase + TIMER_O_TCSR) = 0;

    //
    // Write 1 to clear interrupt flag for safty .
    //
    xHWREG(ulBase + TIMER_O_TISR) |= TIMER_TISR_TIF;
    

    xHWREG(ulBase + TIMER_O_TCMPR) = ulCounterBound;
    xHWREG(ulBase + TIMER_O_TCSR) |= ulConfig | TIMER_TCSR_CTB | 
                                     TIMER_TCSR_CTDR_EN; 
} 

//*****************************************************************************
//
//! \brief Start The Timer counter. 
//!
//! \param ulBase is the base address of the Timer port.
//!
//! This function is to start The Timer counter.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerStart(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xHWREG(ulBase + TIMER_O_TCSR) |= TIMER_TCSR_CEN;

}

//*****************************************************************************
//
//! \brief Stop The Timer counter. 
//!
//! \param ulBase is the base address of the Timer port.
//!
//! This function is to stop The Timer counter.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerStop(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xHWREG(ulBase + TIMER_O_TCSR) &= ~TIMER_TCSR_CEN;
}

//*****************************************************************************
//
//! \brief Enable The Timer counter as a counter. 
//!
//! \param ulBase is the base address of the Timer port.
//!
//! This function is to enable The Timer counter as a counter.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCounterEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xHWREG(ulBase + TIMER_O_TCSR) |= TIMER_TCSR_CTB;
}

//*****************************************************************************
//
//! \brief Disable The Timer counter as a counter. 
//!
//! \param ulBase is the base address of the Timer port.
//!
//! This function is to disable The Timer counter as a counter.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCounterDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xHWREG(ulBase + TIMER_O_TCSR) &= ~TIMER_TCSR_CTB;
}

//*****************************************************************************
//
//! \brief Enable The Timer counter as a timer capture. 
//!
//! \param ulBase is the base address of the Timer port.
//!
//! This function is to enable The Timer counter as a timer capture.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCaptureEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xHWREG(ulBase + TIMER_O_TEXCON) |= TIMER_TEXCON_TEXEN;
}

//*****************************************************************************
//
//! \brief Disable The Timer counter as a timer capture. 
//!
//! \param ulBase is the base address of the Timer port.
//!
//! This function is to disable The Timer counter as a timer capture.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCaptureDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xHWREG(ulBase + TIMER_O_TEXCON) &= ~TIMER_TEXCON_TEXEN;
}

//*****************************************************************************
//
//! \brief Enable The Timer counter as a capture. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulCapMode is the capture mode of the Timer port.Which can be the 
//! values: \b TIMER_CAP_MODE_CAP, \b TIMER_CAP_MODE_RST.
//!
//! This function is to enable The Timer counter as a capture.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCaptureModeSet(unsigned long ulBase, unsigned long ulCapMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    xASSERT((ulCapMode == TIMER_CAP_MODE_CAP) || 
            (ulCapMode == TIMER_CAP_MODE_RST)); 

    xHWREG(ulBase + TIMER_O_TEXCON) &= ~TIMER_TEXCON_RSTCAP;
    xHWREG(ulBase + TIMER_O_TEXCON) |= ulCapMode;
}

//*****************************************************************************
//
//! \brief Set The Timer counter Prescale Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulValue is the Prescale Value will be set.
//!
//! This function is to Set The Timer counter Prescale Value.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerPrescaleSet(unsigned long ulBase, unsigned long ulValue)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    xASSERT((ulValue >= 0) && (ulValue <= 255));

    xHWREG(ulBase + TIMER_O_TCSR) &= ~TIMER_TCSR_PRESCALE_M;
    xHWREG(ulBase + TIMER_O_TCSR) |= ulValue;
}

//*****************************************************************************
//
//! \brief Set The Timer counter Compare Match Value. 
//!
//! \param ulBase is the base address of the Timer port.
//!
//! This function is to Set The Timer counter Compare Match Value.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerMatchSet(unsigned long ulBase, unsigned long ulValue)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    xASSERT((ulValue > 1) && (ulValue <= 0xFFFFFF));

    xHWREG(ulBase + TIMER_O_TCMPR) &= ~TIMER_TCMPR_TCMP_M;
    xHWREG(ulBase + TIMER_O_TCMPR) |= ulValue;
}

//*****************************************************************************
//
//! \brief Get The Timer counter Prescale Value. 
//!
//! \param ulBase is the base address of the Timer port.
//!
//! This function is to get The Timer counter Prescale Value.
//!
//! \note None
//!
//! \return the Prescale Value will be get.
//
//*****************************************************************************
unsigned long 
TimerPrescaleGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    return (xHWREG(ulBase + TIMER_O_TCSR) & TIMER_TCSR_PRESCALE_M);
}

//*****************************************************************************
//
//! \brief Get The Timer counter Compare Match Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulValue is the Prescale Value will be set.
//!
//! This function is to get The Timer counter Compare Match Value.
//!
//! \note None
//!
//! \return the Prescale Value will be set.
//
//*****************************************************************************
unsigned long 
TimerMatchGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    return (xHWREG(ulBase + TIMER_O_TCMPR) & TIMER_TCMPR_TCMP_M);
}

//*****************************************************************************
//
//! \brief Get The Timer counter current up timer or up event counter value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulValue is the Prescale Value will be set.
//!
//! This function is to get The Timer counter current up timer or up event
//! counter value.
//!
//! \note None
//!
//! \return current up timer or up event counter value will be set.
//
//*****************************************************************************
unsigned long 
TimerValueGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    return (xHWREG(ulBase + TIMER_O_TDR) & TIMER_TDR_DATA_M);
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the timer.
//!
//! \param ulBase is the base address of the Timer port.
//! \param xtPortCallback is callback for the timer.
//!
//! Init interrupts callback for the timer.
//!
//! \return None.
//
//*****************************************************************************
void 
TimerIntCallbackInit(unsigned long ulBase, xtEventCallback xtTimerCallback)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    if (xtTimerCallback != 0)
    {
        switch(ulBase)
        {
            case TIMER0_BASE:
                g_pfnTimerHandlerCallbacks[0] = xtTimerCallback;
                break;
            case TIMER1_BASE:
                g_pfnTimerHandlerCallbacks[1] = xtTimerCallback;
                break;
            case TIMER2_BASE:
                g_pfnTimerHandlerCallbacks[2] = xtTimerCallback;
                break;
            case TIMER3_BASE:
                g_pfnTimerHandlerCallbacks[3] = xtTimerCallback;
                break;
        }
    }
}

//*****************************************************************************
//
//! \brief Enable The Timer counter interrupt. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulIntFlags is the interrupt type of the Timer port.
//!
//! This function is to enable The Timer counter interrupt.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! \b TIMER_INT_MATCH, \b TIMER_INT_CAP.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xASSERT(((ulIntFlags & TIMER_INT_MATCH) == TIMER_INT_MATCH) || 
            ((ulIntFlags & TIMER_INT_CAP) == TIMER_INT_CAP));

    
    xHWREG(ulBase + TIMER_O_TCSR) |= (ulIntFlags & TIMER_INT_MATCH);
    xHWREG(ulBase + TIMER_O_TEXCON) |= (ulIntFlags & TIMER_INT_CAP);
    
}

//*****************************************************************************
//
//! \brief Disable The Timer counter interrupt. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulIntFlags is the interrupt type of the Timer port.
//!
//! This function is to disable The Timer counter interrupt.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! \b TIMER_INT_MATCH, \b TIMER_INT_CAP.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void
TimerIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xASSERT(((ulIntFlags & TIMER_INT_MATCH) == TIMER_INT_MATCH) || 
            ((ulIntFlags & TIMER_INT_CAP) == TIMER_INT_CAP));

    
    xHWREG(ulBase + TIMER_O_TCSR) &= ~(ulIntFlags & TIMER_INT_MATCH);
    xHWREG(ulBase + TIMER_O_TEXCON) &= ~(ulIntFlags & TIMER_INT_CAP);
}

//*****************************************************************************
//
//! \brief Get The Timer counter interrupt Status. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulIntFlags is the interrupt type of the Timer port.
//!
//! This function is to disable The Timer counter interrupt.
//! 
//! The \e ulIntFlags parameter can be one of the values:
//! \b TIMER_INT_MATCH, \b TIMER_INT_CAP.
//!
//! \note When use this API ,the ulIntFlags parameter one of the interrupt event
//!
//! \return the Status of The Timer counter interrupt.
//
//*****************************************************************************
xtBoolean
TimerIntStatus(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xASSERT(((ulIntFlags) == TIMER_INT_MATCH) || 
            ((ulIntFlags) == TIMER_INT_CAP));

    if (ulIntFlags == TIMER_INT_MATCH) 
    {
        return ((xHWREG(ulBase + TIMER_O_TISR) ? xtrue : xfalse));
    }
    else
    {
        return ((xHWREG(ulBase + TIMER_O_TEISR) ? xtrue : xfalse));
    }
}

//*****************************************************************************
//
//! \brief Clear The Timer counter interrupt flag. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulIntFlags is the interrupt type of the Timer port.
//!
//! This function is to clear The Timer counter interrupt flag.
//! 
//! The \e ulIntFlags parameter can be one of the values:
//! \b TIMER_INT_MATCH, \b TIMER_INT_CAP.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerIntClear(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xASSERT(((ulIntFlags & TIMER_INT_MATCH) == TIMER_INT_MATCH) || 
            ((ulIntFlags & TIMER_INT_CAP) == TIMER_INT_CAP));

    if (ulIntFlags == TIMER_INT_MATCH)
    {
        xHWREG(ulBase + TIMER_O_TISR) |= TIMER_TISR_TIF;
    }
    if (ulIntFlags == TIMER_INT_CAP)
    {
        xHWREG(ulBase + TIMER_O_TEISR) |= TIMER_TISR_TIF;
    }

}

//*****************************************************************************
//
//! \brief Select The Timer counter detect phase. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulPhase is the counter detect phase of the Timer port.
//!
//! This function is to select The Timer counter detect phase.
//! 
//! The \e ulPhase parameter can be one of the values:
//! \b TIMER_COUNTER_RISING, \b TIMER_COUNTER_FALLING.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void
TimerCounterDetectPhaseSelect(unsigned long ulBase, unsigned long ulPhase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xASSERT((ulPhase == TIMER_COUNTER_RISING) || 
            (ulPhase == TIMER_COUNTER_FALLING));

    xHWREG(ulBase + TIMER_O_TEXCON) &= ~TIMER_TEXCON_TX_PHASE;
    xHWREG(ulBase + TIMER_O_TEXCON) |= ulPhase;
}

//*****************************************************************************
//
//! \brief Select The Timer counter capture detect edge. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulEdge is the capture detect edge of the Timer port.
//!
//! This function is to select The Timer counter capture detect edge.
//! 
//! The \e ulPhase parameter can be one of the values:
//! \b TIMER_CAP_RISING, \b TIMER_CAP_FALLING, \b TIMER_CAP_BOTH.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCaptureEdgeSelect(unsigned long ulBase, unsigned long ulEdge)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xASSERT((ulEdge == TIMER_CAP_RISING) || 
            (ulEdge == TIMER_CAP_BOTH) || 
            (ulEdge == TIMER_CAP_FALLING));
    
    xHWREG(ulBase + TIMER_O_TEXCON) &= ~TIMER_TEXCON_TEX_EDGE_M;
    xHWREG(ulBase + TIMER_O_TEXCON) |= ulEdge;
    
}

//*****************************************************************************
//
//! \brief Enable Timer Counter pin De-bounce. 
//!
//! \param ulBase is the base address of the Timer port.
//!
//! This function is to Enable Timer Counter pin De-bounce.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCounterDebounceEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    xHWREG(ulBase + TIMER_O_TEXCON) |= TIMER_TEXCON_TCDB;
}

//*****************************************************************************
//
//! \brief Disable Timer Counter pin De-bounce. 
//!
//! \param ulBase is the base address of the Timer port.
//!
//! This function is to disable Timer Counter pin De-bounce.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCounterDebounceDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xHWREG(ulBase + TIMER_O_TEXCON) &= ~TIMER_TEXCON_TCDB;
}

//*****************************************************************************
//
//! \brief Enable Timer External Capture pin De-bounce. 
//!
//! \param ulBase is the base address of the Timer port.
//!
//! This function is to Enable Timer External Capture pin De-bounce.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCaptureDebounceEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xHWREG(ulBase + TIMER_O_TEXCON) |= TIMER_TEXCON_TEXDB;
}

//*****************************************************************************
//
//! \brief Disable Timer External Capture pin De-bounce. 
//!
//! \param ulBase is the base address of the Timer port.
//!
//! This function is to disable Timer External Capture pin De-bounce.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCaptureDebounceDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xHWREG(ulBase + TIMER_O_TEXCON) &= ~TIMER_TEXCON_TEXDB;
}

//*****************************************************************************
//
//! \brief Set the external clock frequence,it's used for timer clock source.  
//!
//! \param ulClockFreq is the clock frequence (Hz) for external clock source.
//!
//! This function is to set the external clock frequence,it's used for timer
//! clock source.User can change the timer clock source from the external clock
//! source by calling \ref  SysCtlPeripheralClockSourceSet();
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerExtClockFreqSet(unsigned long ulClockFreq)
{
    ulEXTClockFreq = ulClockFreq;
}
