//*****************************************************************************
//
//! \file xtimer.c
//! \brief Driver for the Timer
//! \version V2.1.1.0
//! \date 3/27/2012
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
static xtEventCallback g_pfnTimerHandlerCallbacks[2]={0};

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
    unsigned long ulTemp0;
    //
    //! Clear the Timer INT Flag
    //
    ulTemp0 = xHWREG(ulBase + TIMER_ICTR) ;
    xHWREG(ulBase + TIMER_ICTR) = ulTemp0;     

    if (g_pfnTimerHandlerCallbacks[0] != 0)        
    {
        g_pfnTimerHandlerCallbacks[0](0, 0, ulTemp0, 0);
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
    unsigned long ulTemp0;
    //
    //! Clear the Timer INT Flag
    //
    ulTemp0 = xHWREG(ulBase + TIMER_ICTR) ;
    xHWREG(ulBase + TIMER_ICTR) = ulTemp0;  

    if (g_pfnTimerHandlerCallbacks[1] != 0)        
    {
        g_pfnTimerHandlerCallbacks[1](0, 0, ulTemp0, 0);
    }
}

//*****************************************************************************
//
//! \brief Configures the CHx as input.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the Input channel.
//! \param ulPolarity is CHxI polarity.
//! \param ulSelect is the channel capture source selection.
//! \param ulFilter is the input capture filter. This parameter must be a value 
//!        between 0x00 and 0x0F.
//!
//! The \e ulChannel parameter can be one of the values:
//! \b TIMER_CH_0, \b TIMER_CH_1, \b TIMER_CH_2 and \b TIMER_CH_3.
//!
//! The \e ulPolarity parameter can be one of the values:
//! \b TIMER_CHP_NONINVERTED, \b TIMER_CHP_INVERTED.
//!
//! The \e ulSelect parameter can be one of the values:
//! \b TIMER_CHCCS_DIRECT, \b TIMER_CHCCS_INDIRECT, \b TIMER_CHCCS_TRCED.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
static void 
TimerChannelConfigure(unsigned long ulBase, unsigned long ulChannel, 
       unsigned long ulPolarity, unsigned long ulSelect, unsigned char ucFilter)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE)); 
    xASSERT((ulChannel == TIMER_CH_0) || (ulChannel == TIMER_CH_1) ||
            (ulChannel == TIMER_CH_2) || (ulChannel == TIMER_CH_3)); 
    xASSERT((ulPolarity == TIMER_CHP_NONINVERTED) || 
            (ulPolarity == TIMER_CHP_INVERTED)); 
    xASSERT((ulSelect == TIMER_CHCCS_DIRECT) || 
            (ulSelect == TIMER_CHCCS_INDIRECT) ||
            (ulSelect == TIMER_CHCCS_TRCED));
    xASSERT((ucFilter >= 0) && (ucFilter <= 0x0F));

    //
    // Disable the channel
    //
    xHWREG(ulBase + TIMER_CHCTR) &= ~(1 << (ulChannel * 2));
    
    //
    // Select the input and set the filter
    //
    xHWREG(ulBase + TIMER_CH0ICFR + ulChannel * 2) &= 
                             ~(TIMER_CH0ICFR_CH0CCS_M | TIMER_CH0ICFR_TI0F_M);
    xHWREG(ulBase + TIMER_CH0ICFR + ulChannel * 2) |= (ulSelect | ucFilter);
    
    //
    // Select the polarity 
    //
    xHWREG(ulBase + TIMER_CHPOLR) &= ~(1 << (ulChannel * 2));
    xHWREG(ulBase + TIMER_CHPOLR) |= ulPolarity << (ulChannel * 2);
    
    //
    // Set the channel state
    //
    xHWREG(ulBase + TIMER_CHCTR) |= 1 << (ulChannel * 2);
}

//*****************************************************************************
//
//! \brief Configurate The Timer's mode and tick frequency. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//! \param ulConfig is the mode Configuratation of the Timer port.
//! Details please refer to \ref xTIMER_Count_Direction and 
//! \ref xTIMER_Mode_Type
//! \param ulTickFreq is the tick frequency of the Timer port.
//!
//! This function is to configurate The Timer's mode and tick frequency.
//!
//! The \e ulConfig parameter is the OR value of two values:
//! - Timer's mode
//! Details please refer to \ref xTIMER_Count_Direction_CoX
//! - Timer's direction
//! Details please refer to \ref xTIMER_Mode_Type_CoX
//!
//! \b xTIMER_MODE_ONESHOT, \b xTIMER_MODE_PERIODIC, \b xTIMER_MODE_TOGGLE and
//! \b xTIMER_MODE_CONTINUOUS is the Timer's mode
//! 
//! \b xTIMER_COUNT_UP, \b xTIMER_COUNT_DOWN is the Timer's direction.
//!
//! The \e ulTickFreq parameter is the the timer tick frequency.It can be any
//! values but ulTickFreq > 0 and ulTickFreq < timer clock source.
//!
//! \note For HT32F125x,each timer only one channel.
//!
//! \return None.
//
//*****************************************************************************
void
xTimerInitConfig(unsigned long ulBase, unsigned long ulChannel, 
                 unsigned long ulConfig, unsigned long ulTickFreq)
{
    unsigned long ulInternalClk;
    unsigned long ulPreScale;
    unsigned long ulTCMPRValue;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE)); 
    xASSERT((ulChannel == xTIMER_CHANNEL0) || 
            (ulChannel == xTIMER_CHANNEL1) ||
            (ulChannel == xTIMER_CHANNEL2) ||
            (ulChannel == xTIMER_CHANNEL3));
    
    
    ulInternalClk = SysCtlClockGet();
    
    for (ulPreScale = 1; ulPreScale < 0x0000FFFF; ulPreScale++)
    {
        ulTCMPRValue = ulInternalClk / (ulTickFreq * ulPreScale);
 
        //
        //The TCMPR value must > 1 
        //
        if ((ulTCMPRValue > 1) && (ulTCMPRValue < 0x0000FFFF))
            break;
    }
    
    switch(ulConfig & 0x000000F0)
    {
    case xTIMER_MODE_ONESHOT:
      {
        TimerOnePulseModeConfigure(ulBase, TIMER_ONE_PULSE_MODE_EN);
        break;
      }
    case xTIMER_MODE_PERIODIC:
      {
        TimerOnePulseModeConfigure(ulBase, TIMER_ONE_PULSE_MODE_DIS);
        break;
      }
    case xTIMER_MODE_TOGGLE:
      {
        TimerOnePulseModeConfigure(ulBase, TIMER_ONE_PULSE_MODE_DIS);
        TimerOutputConfigure(ulBase, ulChannel, TIMER_CHCTL_ENABLE, 
                TIMER_CHP_NONINVERTED, TIMER_OM_MATCH_TOGGLE, ulTCMPRValue/2);
        break;
      }
    case xTIMER_MODE_CONTINUOUS:
      {
        break;
      }
    case xTIMER_MODE_CAPTURE:
      {
        TimerCaptureConfigure(ulBase, ulChannel, TIMER_CHP_NONINVERTED, 
                              TIMER_CHCCS_DIRECT, TIMER_CHPSC_OFF, 0);
        break;
      }
    }
    
    //
    // Set the CRR and PSCR register
    // 
    xHWREG(ulBase + TIMER_PSCR) = ulPreScale;
    TimerCRRSet(ulBase, ulTCMPRValue);
    
}

//*****************************************************************************
//
//! \brief Enable The Timer counter interrupt. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//! \param ulIntFlags is the interrupt type of the Timer port.
//! Details please refer to \ref xTIMER_INT_Type
//!
//! This function is to enable The Timer counter interrupt.
//! 
//! The \e ulIntFlags parameter is one of the following value:
//! \b xTIMER_INT_MATCH, \b xTIMER_INT_CAP_EVENT.
//! Details please refer to \ref xTIMER_INT_Type_CoX
//!
//! \return None.
//
//*****************************************************************************
void xTimerIntEnable(unsigned long ulBase, unsigned long ulChannel, 
                            unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulIntFlags == xTIMER_INT_MATCH) || 
            (ulIntFlags == xTIMER_INT_CAP_EVENT));
    
    if(ulIntFlags == xTIMER_INT_MATCH)
    {
        xHWREG(ulBase + TIMER_ICTR) |= TIMER_CHCTR_UEVIE;
    }
    else
    {
        xHWREG(ulBase + TIMER_ICTR) |= (TIMER_CHCTR_CH0CCIE << (ulChannel * 2));
    }
}

//*****************************************************************************
//
//! \brief Disable The Timer counter interrupt. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//! \param ulIntFlags is the interrupt type of the Timer port.
//! Details please refer to \ref xTIMER_INT_Type
//!
//! This function is to enable The Timer counter interrupt.
//! 
//! The \e ulIntFlags parameter is one of the following value:
//! \b xTIMER_INT_MATCH, \b xTIMER_INT_CAP_EVENT.
//! Details please refer to \ref xTIMER_INT_Type_CoX
//!
//! \return None.
//
//*****************************************************************************
void xTimerIntDisable(unsigned long ulBase, unsigned long ulChannel, 
                              unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulIntFlags == xTIMER_INT_MATCH) || 
            (ulIntFlags == xTIMER_INT_CAP_EVENT));
    
    if(ulIntFlags == xTIMER_INT_MATCH)
    {
        xHWREG(ulBase + TIMER_ICTR) &= ~TIMER_CHCTR_UEVIE;
    }
    else
    {
        xHWREG(ulBase + TIMER_ICTR) &= ~(TIMER_CHCTR_CH0CCIE << (ulChannel * 2));
    }
}

//*****************************************************************************
//
//! \brief Get The Timer counter interrupt Status. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulIntFlags is the interrupt type of the Timer port.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! \b TIMER_INT_CH0CC, \b TIMER_INT_CH1CC, \b TIMER_INT_CH2CC, 
//! \b TIMER_INT_CH3CC, \b TIMER_INT_UEV1, \b TIMER_INT_TEV.
//!
//! \note When use this API ,the ulIntFlags parameter one of the interrupt event
//!
//! \return xtrue: the interrupt occured.
//!         xfalse: the interrupt didn't occure.
//
//*****************************************************************************
xtBoolean 
xTimerStatusGet(unsigned long ulBase, unsigned long ulChannel, 
                                 unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulIntFlags == xTIMER_INT_MATCH) || 
            (ulIntFlags == xTIMER_INT_CAP_EVENT));
    
    if(ulIntFlags == xTIMER_INT_MATCH)
    {
        if(xHWREG(ulBase + TIMER_ICTR) & TIMER_INT_UEV1)
        {  
            return xtrue;
        }
    }
    else
    {
        if(xHWREG(ulBase + TIMER_ICTR) & (TIMER_CHCTR_CH0CCIE << (ulChannel * 2)))
        {
           return xfalse;
        }
    }   
    return xfalse;
}

//*****************************************************************************
//
//! \brief Select The Timer counter capture detect edge. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulEdge is the capture detect edge of the Timer port.
//! Details please refer to \ref xTIMER_Capture_Edge_Type.
//!
//! This function is to select The Timer counter capture detect edge.
//! 
//! The \e ulPhase parameter can be one of the values:
//! \b xTIMER_CAP_RISING, \b xTIMER_CAP_FALLING.
//! Details please refer to \ref xTIMER_Capture_Edge_Type_CoX.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
xTimerCaptureEdgeSelect(unsigned long ulBase, unsigned long ulChannel,
                                    unsigned long ulEdge)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulEdge == xTIMER_CAP_RISING) || 
            (ulEdge == xTIMER_CAP_FALLING));
    
    //
    // Set the Output Compare Polarity
    //
    xHWREG(ulBase + TIMER_CHPOLR) &= ~(1 << (ulChannel * 2));
    xHWREG(ulBase + TIMER_CHPOLR) |= ulEdge << (ulChannel * 2);
}

//*****************************************************************************
//
//! \brief Initializes the GPTM counter to reload, prescaler and counter mode. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulCountMode is the Counter Mode.
//! \param ulCRR is the counter reload value.
//! \param ulPrescaler is the Prescaler value.
//!
//! The \e ulCountMode parameter can be one of the values:
//! \b TIMER_CNT_MODE_UP, \b TIMER_CNT_MODE_CA1, \b TIMER_CNT_MODE_CA2 and
//! \b TIMER_CNT_MODE_CA3, \b TIMER_CNT_MODE_DOWN.
//!
//! The \e ulCRR parameter can be one of the values:
//! \b TIMER_PSC_RLD_UPDATE, \b TIMER_PSC_RLD_IMMEDIATE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void TimeBaseConfigure(unsigned long ulBase, unsigned long ulCountMode, 
         unsigned long ulCRR, unsigned long ulPrescaler, unsigned long ulReMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE)); 
    xASSERT((ulCountMode == TIMER_CNT_MODE_UP) || 
            (ulCountMode == TIMER_CNT_MODE_CA1) || 
            (ulCountMode == TIMER_CNT_MODE_CA2) ||
            (ulCountMode == TIMER_CNT_MODE_CA3) ||
            (ulCountMode == TIMER_CNT_MODE_DOWN));
    xASSERT((ulCRR >= 0) && (ulCRR <= 65535));
    xASSERT((ulPrescaler >= 0) && (ulPrescaler <= 65535));
    xASSERT((ulReMode == TIMER_PSC_RLD_UPDATE) || 
            (ulReMode == TIMER_PSC_RLD_IMMEDIATE));
    
    //
    // Set the counter reload value
    //
    xHWREG(ulBase + TIMER_CRR) = ulCRR;
    
    //
    // Set the Prescaler value
    //
    xHWREG(ulBase + TIMER_PSCR) = ulPrescaler;
    
    //
    // Select the Counter Mode and set the clock dir
    //
    xHWREG(ulBase + TIMER_CNTCFR) &= ~TIMER_CNTCFR_CMSEL_M;
    xHWREG(ulBase + TIMER_CNTCFR) &= ~TIMER_CNTCFR_DIR;
    xHWREG(ulBase + TIMER_CNTCFR) |= ulCountMode;
    
    //
    // To reload the Prescaler value immediatly or next update event 1 
    //
    xHWREG(ulBase + TIMER_EVGR) |= TIMER_EVGR_UEVG;
}

//*****************************************************************************
//
//! \brief Initializes the TIMERx channel x output. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the Output channel.
//! \param ulOutEnable is CHxO output state.
//! \param ulPolarity is CHxO polarity.
//! \param ulOutputMode is Channel output mode selection.
//! \param ulOutCompare is the value for CHxCCR register.
//!
//! This function is to configurate The Timer's mode and tick frequency.
//!
//! The \e ulChannel parameter can be one of the values:
//! \b TIMER_CH_0, \b TIMER_CH_1, \b TIMER_CH_2 and \b TIMER_CH_3.
//!
//! The \e ulChannelulOutEnable parameter can be one of the values:
//! \b TIMER_CHCTL_DISABLE, \b TIMER_CHCTL_ENABLE.
//!
//! The \e ulPolarity parameter can be one of the values:
//! \b TIMER_CHP_NONINVERTED, \b TIMER_CHP_INVERTED.
//!
//! The \e ulOutputMode parameter can be one of the values:
//! \b TIMER_OM_MATCH_NOCHANGE, \b TIMER_OM_MATCH_INACTIVE, 
//! \b TIMER_OM_MATCH_ACTIVE, \b TIMER_OM_MATCH_TOGGLE,
//! \b TIMER_OM_FORCED_INACTIVE, \b TIMER_OM_FORCED_ACTIVE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void TimerOutputConfigure(unsigned long ulBase, unsigned long ulChannel, 
                     unsigned long ulOutEnable, unsigned long ulPolarity, 
                     unsigned long ulOutputMode, unsigned long ulOutCompare)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE)); 
    xASSERT((ulChannel == TIMER_CH_0) || (ulChannel == TIMER_CH_1) ||
            (ulChannel == TIMER_CH_2) || (ulChannel == TIMER_CH_3)); 
    xASSERT((ulOutEnable == TIMER_CHCTL_DISABLE) || 
            (ulOutEnable == TIMER_CHCTL_ENABLE));
    xASSERT((ulPolarity == TIMER_CHP_NONINVERTED) || 
            (ulPolarity == TIMER_CHP_INVERTED)); 
    xASSERT((ulOutputMode == TIMER_OM_MATCH_NOCHANGE) ||
            (ulOutputMode == TIMER_OM_MATCH_INACTIVE) ||
            (ulOutputMode == TIMER_OM_MATCH_ACTIVE) || 
            (ulOutputMode == TIMER_OM_MATCH_TOGGLE) ||
            (ulOutputMode == TIMER_OM_FORCED_INACTIVE) ||
            (ulOutputMode == TIMER_OM_FORCED_ACTIVE));
    xASSERT((ulOutCompare >= 0) && (ulOutCompare <= 65535));
    
    //
    // Disable the channel
    //
    xHWREG(ulBase + TIMER_CHCTR) &= ~(1 << (ulChannel * 2));
    
    //
    // Set the Output Compare Polarity
    //
    xHWREG(ulBase + TIMER_CHPOLR) &= ~(1 << (ulChannel * 2));
    xHWREG(ulBase + TIMER_CHPOLR) |= ulPolarity << (ulChannel * 2);
    
    //
    // Select the Output Compare Mode
    //
    xHWREG(ulBase + TIMER_CH0OCFR + ulChannel * 4) &= ~TIMER_CH0OCFR_CH0OM_M;
    xHWREG(ulBase + TIMER_CH0OCFR + ulChannel * 4) |= ulOutputMode;
    
    //
    //  Set the Capture Compare Register value
    //
    xHWREG(ulBase + TIMER_CH0CCR + ulChannel * 4) |= ulOutCompare;
    
    //
    // Set the channel state
    //
    xHWREG(ulBase + TIMER_CHCTR) |= ulOutEnable << (ulChannel * 2);
    
}

//*****************************************************************************
//
//! \brief Initializes input capture of the Timer channel.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the Input channel.
//! \param ulPolarity is CHxI polarity.
//! \param ulSelect is the channel capture source selection.
//! \param ulPrescaler is Channel Capture prescaler.
//! \param ulFilter is the input capture filter. This parameter must be a value 
//!        between 0x00 and 0x0F.
//!
//! The \e ulChannel parameter can be one of the values:
//! \b TIMER_CH_0, \b TIMER_CH_1, \b TIMER_CH_2 and \b TIMER_CH_3.
//!
//! The \e ulPolarity parameter can be one of the values:
//! \b TIMER_CHP_NONINVERTED, \b TIMER_CHP_INVERTED.
//!
//! The \e ulSelect parameter can be one of the values:
//! \b TIMER_CHCCS_DIRECT, \b TIMER_CHCCS_INDIRECT, \b TIMER_CHCCS_TRCED.
//!
//! The \e ulPrescaler parameter can be one of the values:
//! \b TIMER_CHPSC_OFF, \b TIMER_CHPSC_2, \b TIMER_CHPSC_4, \b TIMER_CHPSC_8.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCaptureConfigure(unsigned long ulBase, unsigned long ulChannel, 
                      unsigned long ulPolarity, unsigned long ulSelect, 
                      unsigned long ulPrescaler, unsigned char ucFilter)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE)); 
    xASSERT((ulChannel == TIMER_CH_0) || (ulChannel == TIMER_CH_1) ||
            (ulChannel == TIMER_CH_2) || (ulChannel == TIMER_CH_3)); 
    xASSERT((ulPolarity == TIMER_CHP_NONINVERTED) || 
            (ulPolarity == TIMER_CHP_INVERTED)); 
    xASSERT((ulSelect == TIMER_CHCCS_DIRECT) || 
            (ulSelect == TIMER_CHCCS_INDIRECT) ||
            (ulSelect == TIMER_CHCCS_TRCED));
    xASSERT((ulPrescaler == TIMER_CHPSC_OFF) || (ulPrescaler == TIMER_CHPSC_2) ||
            (ulPrescaler == TIMER_CHPSC_4) || (ulPrescaler == TIMER_CHPSC_8));
    xASSERT((ucFilter >= 0) && (ucFilter <= 0x0F));
    
    TimerChannelConfigure(ulBase, ulChannel, ulPolarity, ulSelect, ucFilter);
    
    TimerCHPSCConfigure(ulBase, ulChannel, ulPrescaler);  
}

//*****************************************************************************
//
//! \brief Initializes input capture of the Timer channel.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the Input channel.
//! \param ulPrescaler is Channel Capture prescaler.
//!
//! The \e ulChannel parameter can be one of the values:
//! \b TIMER_CH_0, \b TIMER_CH_1, \b TIMER_CH_2 and \b TIMER_CH_3.
//!
//! The \e ulPrescaler parameter can be one of the values:
//! \b TIMER_CHPSC_OFF, \b TIMER_CHPSC_2, \b TIMER_CHPSC_4, \b TIMER_CHPSC_8.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCHPSCConfigure(unsigned long ulBase, unsigned long ulChannel, 
                    unsigned long ulPrescaler)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE)); 
    xASSERT((ulChannel == TIMER_CH_0) || (ulChannel == TIMER_CH_1) ||
            (ulChannel == TIMER_CH_2) || (ulChannel == TIMER_CH_3)); 
    xASSERT((ulPrescaler == TIMER_CHPSC_OFF) || (ulPrescaler == TIMER_CHPSC_2) ||
            (ulPrescaler == TIMER_CHPSC_4) || (ulPrescaler == TIMER_CHPSC_8)); 
    
    //
    // Set the capture input prescaler value
    //
    xHWREG(ulBase + TIMER_CH0ICFR + ulChannel * 4) &= ~TIMER_CH0ICFR_CH0PSC_M;
    xHWREG(ulBase + TIMER_CH0ICFR + ulChannel * 4) |= ulPrescaler;
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
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xHWREG(ulBase + TIMER_CTR) |= TIMER_CTR_TME;

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
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xHWREG(ulBase + TIMER_CTR) &= ~TIMER_CTR_TME;
}

//*****************************************************************************
//
//! \brief Configures external clock mode of the GPTM. Used ITIx as the clock 
//! source. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulTriggerSource is Trigger source.
//!
//! The \e ulTriggerSource parameter can be one of the values:
//! \b TIMER_TRSEL_ITI0.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerITIExtClkConfigure(unsigned long ulBase, unsigned long ulTriggerSource)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulTriggerSource == TIMER_TRSEL_ITI0));    
    
    //
    // Select the Internal Trigger. Slave mode will be disable in this function
    //
    TimerSTIConfigure(ulBase, ulTriggerSource);
    
    //
    // Select the STIED as external clock source
    //
    xHWREG(ulBase + TIMER_MDCFR) |= TIMER_MDCFR_SMSEL_STIED;
}

//*****************************************************************************
//
//! \brief Configures external clock mode of the GPTM . Used CHx as the clock 
//! source.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulPolarity is CHx polarity.
//! \param ulSelect is the channel source.
//! \param ulFilter is the input capture filter. This parameter must be a value 
//!        between 0x00 and 0x0F.
//!
//! The \e ulPolarity parameter can be one of the values:
//! \b TIMER_CHP_NONINVERTED, \b TIMER_CHP_INVERTED.
//!
//! The \e ulSelect parameter can be one of the values:
//! \b TIMER_TRSEL_TI0S0, \b TIMER_TRSEL_TI1S1, \b TIMER_TRSEL_TI0BED.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCHExtClkConfigure(unsigned long ulBase, unsigned long ulSelect,
                       unsigned long ulPolarity, unsigned char ucFilter)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulSelect == TIMER_TRSEL_TI0BED) || (ulSelect == TIMER_TRSEL_TI0S0) ||
            (ulSelect == TIMER_TRSEL_TI1S1));
    xASSERT((ulPolarity == TIMER_CHP_NONINVERTED) || 
            (ulPolarity == TIMER_CHP_INVERTED));
    
    //
    // Configure the Timer Input Clock Source
    //
    if(ulSelect == TIMER_TRSEL_TI1S1)
    {
        TimerChannelConfigure(ulBase, TIMER_CH_1, ulPolarity, TIMER_CHCCS_DIRECT,
                              ucFilter);  
    }
    else
    {
        TimerChannelConfigure(ulBase, TIMER_CH_0, ulPolarity, TIMER_CHCCS_DIRECT,
                              ucFilter);  
    }
    
    //
    // Select the external clock source. Slave mode will be disable in this function
    //
    TimerSTIConfigure(ulBase, ulSelect);
    
    //
    // Select the STIED as external clock source
    //
    xHWREG(ulBase + TIMER_MDCFR) |= TIMER_MDCFR_SMSEL_STIED;
    
}

//*****************************************************************************
//
//! \brief Selects the STI source.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulTriggerSource is Trigger source.
//!
//! The \e ulTriggerSource parameter can be one of the values:
//! \b TIMER_TRSEL_UEV1G, \b TIMER_TRSEL_TI0S0, \b TIMER_TRSEL_TI1S1
//! \b TIMER_TRSEL_ETIF, \b TIMER_TRSEL_TI0BED, \b TIMER_TRSEL_ITI0.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerSTIConfigure(unsigned long ulBase, unsigned long ulTriggerSource)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulTriggerSource == TIMER_TRSEL_UEV1G) || 
            (ulTriggerSource == TIMER_TRSEL_TI0S0) ||
            (ulTriggerSource == TIMER_TRSEL_TI1S1) || 
            (ulTriggerSource == TIMER_TRSEL_ETIF) ||
            (ulTriggerSource == TIMER_TRSEL_TI0BED) ||
            (ulTriggerSource == TIMER_TRSEL_ITI0));
    
    //
    // Disable slave mode
    //
    xHWREG(ulBase + TIMER_MDCFR) &= ~TIMER_MDCFR_SMSEL_M;
    
    //
    // Clear the trigger Source Selection
    //
    xHWREG(ulBase + TIMER_TRCFR) &= ~TIMER_TRCFR_TRSEL_M;
    
    //
    // Set the STI source
    //
    xHWREG(ulBase + TIMER_TRCFR) |= ulTriggerSource;
    
}

//*****************************************************************************
//
//! \brief Configures external clock mode of the GPTM. Used ETI as the clock 
//! source.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulEXIPrescale is the external Trigger Prescaler.
//! \param ulEXIPolarity is the external trigger input polarity.
//! \param ucFilter is filter for ETI input.This parameter must be a value 
//!        between 0x00 and 0x0F
//!
//! The \e ulEXIPrescale parameter can be one of the values:
//! \b TIMER_ETIPSC_OFF, \b TIMER_ETIPSC_2, \b TIMER_ETIPSC_4
//! \b TIMER_ETIPSC_8.
//!
//! The \e ulETIPolarity parameter can be one of the values:
//! \b TIMER_ETIPOL_NONINVERTED, \b TIMER_ETIPOL_INVERTED.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerETIExtClkConfigure(unsigned long ulBase, unsigned long ulEXIPrescale,
                            unsigned long ulEXIPolarity, unsigned char ucFilter)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulEXIPrescale == TIMER_ETIPSC_OFF) || 
            (ulEXIPrescale == TIMER_ETIPSC_2) ||
            (ulEXIPrescale == TIMER_ETIPSC_4) ||
            (ulEXIPrescale == TIMER_ETIPSC_8));
    xASSERT((ulEXIPolarity == TIMER_ETIPOL_NONINVERTED) ||
            (ulEXIPolarity == TIMER_ETIPOL_INVERTED));
    xASSERT((ucFilter >= 0) && (ucFilter <= 0x0F));
    
    //
    // Configure the ETI Clock source
    //
    TimerETIConfigure(ulBase, ulEXIPrescale, ulEXIPolarity, ucFilter);
      
    //
    // Enable the external clock mode
    //
    xHWREG(ulBase + TIMER_TRCFR) |= TIMER_TRCFR_ECME;
}

//*****************************************************************************
//
//! \brief Configures external clock mode of the GPTM. Used ETI as the clock 
//! source.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulEXIPrescale is the external Trigger Prescaler.
//! \param ulEXIPolarity is the external trigger input polarity.
//! \param ucFilter is filter for ETI input.This parameter must be a value 
//!        between 0x00 and 0x0F
//!
//! The \e ulEXIPrescale parameter can be one of the values:
//! \b TIMER_ETIPSC_OFF, \b TIMER_ETIPSC_2, \b TIMER_ETIPSC_4
//! \b TIMER_ETIPSC_8.
//!
//! The \e ulETIPolarity parameter can be one of the values:
//! \b TIMER_ETIPOL_NONINVERTED, \b TIMER_ETIPOL_INVERTED.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerETIConfigure(unsigned long ulBase, unsigned long ulEXIPrescale, 
             unsigned long ulEXIPolarity, unsigned char ucFilter)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulEXIPrescale == TIMER_ETIPSC_OFF) || 
            (ulEXIPrescale == TIMER_ETIPSC_2) ||
            (ulEXIPrescale == TIMER_ETIPSC_4) ||
            (ulEXIPrescale == TIMER_ETIPSC_8));
    xASSERT((ulEXIPolarity == TIMER_ETIPOL_NONINVERTED) ||
            (ulEXIPolarity == TIMER_ETIPOL_INVERTED));
    xASSERT((ucFilter >= 0) && (ucFilter <= 0x0F));
    
    //
    // Clear the corresponding bits first
    //
    xHWREG(ulBase + TIMER_TRCFR) &= ~(TIMER_TRCFR_ETIPOL | TIMER_TRCFR_ETIPSC_M
                                      | TIMER_TRCFR_ETF_M);
    
    //
    // Set the prescaler, filter and polarity for ETI inpit
    // 
    xHWREG(ulBase + TIMER_TRCFR) |= (ulEXIPrescale | ulEXIPolarity | 
                                     ((unsigned long)ucFilter << 8));
}

//*****************************************************************************
//
//! \brief Configures external clock mode of the GPTM. Used ETI as the clock 
//! source.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulPrescale is the prescaler value. This parameter must be a value 
//!        between 0 and 0x0000FFFF.
//! \param ulPSCReloadTime is the TIMER prescaler reload time.
//!
//! The \e ulPSCReloadTime parameter can be one of the values:
//! \b TIMER_PSC_RLD_UPDATE, \b TIMER_PSC_RLD_IMMEDIATE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerPrescalerConfigure(unsigned long ulBase, unsigned long ulPrescale,
                                    unsigned long ulPSCReloadTime)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulPSCReloadTime == TIMER_PSC_RLD_UPDATE) || 
            (ulPSCReloadTime == TIMER_PSC_RLD_IMMEDIATE));
    
    //
    // Set the prescaler value
    //
    xHWREG(ulBase + TIMER_PSCR) = ulPrescale;
    
    //
    // Set the UEV1G bit or not
    //
    xHWREG(ulBase + TIMER_EVGR) &= ~TIMER_EVGR_UEVG;
    xHWREG(ulBase + TIMER_EVGR) |= ulPSCReloadTime;
}

//*****************************************************************************
//
//! \brief Configures counter mode
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulCountMode is the counter mode to be used
//!
//! The \e ulCountMode parameter can be one of the values:
//! \b TIMER_CNT_MODE_UP, \b TIMER_CNT_MODE_CA1, \b TIMER_CNT_MODE_CA2,
//! \b TIMER_CNT_MODE_CA3, \b TIMER_CNT_MODE_DOWN.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCNTModeConfigure(unsigned long ulBase, unsigned long ulCountMode)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulCountMode == TIMER_CNT_MODE_UP) ||
            (ulCountMode == TIMER_CNT_MODE_CA1) ||
            (ulCountMode == TIMER_CNT_MODE_CA2) ||
            (ulCountMode == TIMER_CNT_MODE_CA3) ||
            (ulCountMode == TIMER_CNT_MODE_DOWN));
    
    //
    // Reset the CMSEL and DIR Bits
    //
    xHWREG(ulBase + TIMER_CNTCFR) &= ~TIMER_CNTCFR_DIR;
    xHWREG(ulBase + TIMER_CNTCFR) &= ~TIMER_CNTCFR_CMSEL_M;
    
    //
    // Set the Counter Mode
    //
    xHWREG(ulBase + TIMER_CNTCFR) |= ulCountMode;   
}

//*****************************************************************************
//
//! \brief Configures encoder interface.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulDecodeMode is the decoder mode.
//! \param ulCH0P is the CH0 polarity.
//! \param ulCH1P is the CH0 polarity.
//!
//! The \e ulDecodeMode parameter can be one of the values:
//! \b TIMER_SMSEL_DECODER1, \b TIMER_SMSEL_DECODER2, \b TIMER_SMSEL_DECODER3.
//!
//! The \e ulCH0P parameter can be one of the values:
//! \b TIMER_CHP_NONINVERTED, \b TIMER_CHP_INVERTED.
//!
//! The \e ulCH1P parameter can be one of the values:
//! \b TIMER_CHP_NONINVERTED, \b TIMER_CHP_INVERTED.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerDecoderConfig(unsigned long ulBase, unsigned long ulDecodeMode,
                               unsigned long ulCH0P, unsigned long ulCH1P)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulDecodeMode == TIMER_SMSEL_DECODER1) || 
            (ulDecodeMode == TIMER_SMSEL_DECODER2) ||
            (ulDecodeMode == TIMER_SMSEL_DECODER3));
    xASSERT((ulCH0P == TIMER_CHP_NONINVERTED) || (ulCH0P == TIMER_CHP_INVERTED));
    xASSERT((ulCH1P == TIMER_CHP_NONINVERTED) || (ulCH1P == TIMER_CHP_INVERTED));
    
    //
    // Set the decoder mode
    //
    xHWREG(ulBase + TIMER_MDCFR) &= ~TIMER_MDCFR_SMSEL_M;
    xHWREG(ulBase + TIMER_MDCFR) |= ulDecodeMode;
    
    //
    // Select the channel 0 and the channel 1 as input and clear CH0SRC
    //
    xHWREG(ulBase + TIMER_CH0ICFR) &= ~(TIMER_CH0ICFR_CH0CCS_M | 
                                        TIMER_CH0ICFR_TI0SRC);
    xHWREG(ulBase + TIMER_CH1ICFR) &= ~TIMER_CH0ICFR_CH0CCS_M;
    xHWREG(ulBase + TIMER_CH0ICFR) |= TIMER_CHCCS_DIRECT;
    xHWREG(ulBase + TIMER_CH1ICFR) |= TIMER_CHCCS_DIRECT;
    
    //
    // Set the CH0 and the CH1 polarities
    //
    xHWREG(ulBase + TIMER_CHPOLR) &= ~(TIMER_CHCTR_CH0P | TIMER_CHCTR_CH1P);
    xHWREG(ulBase + TIMER_CHPOLR) |= (ulCH0P | (ulCH1P << 2));
    
}

//*****************************************************************************
//
//! \brief Forces CHxOREF waveform to active or inactive level.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the Timer channe mode.
//! \param ForcedAction is the forced action to be set to the output waveform.
//!
//! The \e ulChannel parameter can be one of the values:
//! \b TIMER_CH_0, \b TIMER_CH_1, \b TIMER_CH_2, \b TIMER_CH_3.
//!
//! The \e ForcedAction parameter can be one of the values:
//! \b TIMER_OM_FORCED_INACTIVE, \b TIMER_OM_FORCED_ACTIVE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerForcedOREF(unsigned long ulBase, unsigned long ulChannel, 
                                      unsigned long ForcedAction)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulChannel == TIMER_CH_0) || (ulChannel == TIMER_CH_1) ||
            (ulChannel == TIMER_CH_2) || (ulChannel == TIMER_CH_3)); 
    xASSERT((ForcedAction == TIMER_OM_FORCED_INACTIVE) || 
            (ForcedAction == TIMER_OM_FORCED_ACTIVE));
    
    //
    // Configure The forced output mode
    //
    xHWREG(ulBase + TIMER_CH0OCFR  + ulChannel * 4) &= ~TIMER_CH0OCFR_CH0OM_M;
    xHWREG(ulBase + TIMER_CH0OCFR  + ulChannel * 4) |= ForcedAction;
  
}

//*****************************************************************************
//
//! \brief Enables or Disables Timer CRR preload function.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulProload is the selection of CRR preload control bit
//!
//! The \e ulProload parameter can be one of the values:
//! \b TIMER_CRR_PROLOAD_IMM, \b TIMER_CRR_PROLOAD_UD.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCRRPreloadConfigure(unsigned long ulBase, unsigned long ulProload)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulProload == TIMER_CRR_PROLOAD_IMM) || 
            (ulProload == TIMER_CRR_PROLOAD_UD));
    
    if(ulProload == TIMER_CRR_PROLOAD_IMM)
    {
        xHWREG(ulBase + TIMER_CTR) |= TIMER_CTR_CRBE; 
    }
    else
    {
        xHWREG(ulBase + TIMER_CTR) &= ~TIMER_CTR_CRBE;
    }
    
}

//*****************************************************************************
//
//! \brief Enables or Disables Timer CRR preload function.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the Timer channe mode.
//! \param ulProload is the selection of CHxCRR preload control bit
//!
//! The \e ulChannel parameter can be one of the values:
//! \b TIMER_CH_0, \b TIMER_CH_1, \b TIMER_CH_2, \b TIMER_CH_3.
//!
//! The \e ulProload parameter can be one of the values:
//! \b TIMER_CRR_PROLOAD_IMM, \b TIMER_CRR_PROLOAD_UD.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCHCRRPreloadConfigure(unsigned long ulBase, unsigned long ulChannel, 
                           unsigned long ulProload)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulChannel == TIMER_CH_0) || (ulChannel == TIMER_CH_1) ||
            (ulChannel == TIMER_CH_2) || (ulChannel == TIMER_CH_3));
    xASSERT((ulProload == TIMER_CRR_PROLOAD_IMM) || 
            (ulProload == TIMER_CRR_PROLOAD_UD));
    
    if(ulProload == TIMER_CRR_PROLOAD_IMM)
    {
        xHWREG(ulBase + TIMER_CH0OCFR + 4 * ulChannel) |= TIMER_CH0OCFR_CH0PRE; 
    }
    else
    {
        xHWREG(ulBase + TIMER_CH0OCFR + 4 * ulChannel) &= ~TIMER_CH0OCFR_CH0PRE;
    }
    
}

//*****************************************************************************
//
//! \brief Enables or Disables Timer Reference Output Clear.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the Timer channe mode.
//! \param ulOREFClear is the selection of Reference Output Clear bit
//!
//! The \e ulChannel parameter can be one of the values:
//! \b TIMER_CH_0, \b TIMER_CH_1, \b TIMER_CH_2, \b TIMER_CH_3.
//!
//! The \e ulOREFClear parameter can be one of the values:
//! \b TIMER_OREF_CLEAR_DIS, \b TIMER_OREF_CLEAR_EN.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOREFClrConfigure(unsigned long ulBase, unsigned long ulChannel,
                                  unsigned long ulOREFClear)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulChannel == TIMER_CH_0) || (ulChannel == TIMER_CH_1) ||
            (ulChannel == TIMER_CH_2) || (ulChannel == TIMER_CH_3)); 
    xASSERT((ulOREFClear == TIMER_OREF_CLEAR_DIS) || 
            (ulOREFClear == TIMER_OREF_CLEAR_EN));
    
    xHWREG(ulBase + TIMER_CH0OCFR + 4 * ulChannel) &= ~TIMER_CH0OCFR_REF0CE;
    xHWREG(ulBase + TIMER_CH0OCFR + 4 * ulChannel) |= ulOREFClear;
}

//*****************************************************************************
//
//! \brief Configures polarity of the Timer channel x.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the Timer channe mode.
//! \param ulPolarity is the selection of Reference Output Clear bit
//!
//! The \e ulChannel parameter can be one of the values:
//! \b TIMER_CH_0, \b TIMER_CH_1, \b TIMER_CH_2, \b TIMER_CH_3.
//!
//! The \e ulPolarity parameter can be one of the values:
//! \b TIMER_CHP_NONINVERTED, \b TIMER_CHP_INVERTED.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCHPolarityConfigure(unsigned long ulBase, unsigned long ulChannel,
                                     unsigned long ulPolarity)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulChannel == TIMER_CH_0) || (ulChannel == TIMER_CH_1) ||
            (ulChannel == TIMER_CH_2) || (ulChannel == TIMER_CH_3)); 
    xASSERT((ulPolarity == TIMER_CHP_NONINVERTED) || 
            (ulPolarity == TIMER_CHP_INVERTED));
    
    xHWREG(ulBase + TIMER_CHPOLR) &= ~(1 << (ulChannel * 2) );
    xHWREG(ulBase + TIMER_CHPOLR) |= ulPolarity << (ulChannel * 2);
}

//*****************************************************************************
//
//! \brief Enables or Disables the one pulse immediate active function.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the Timer channe mode.
//! \param ulActive is the selection of Reference Output Clear bit.
//!
//! The \e ulChannel parameter can be one of the values:
//! \b TIMER_CH_0, \b TIMER_CH_1, \b TIMER_CH_2, \b TIMER_CH_3.
//!
//! The \e ulPolarity parameter can be one of the values:
//! \b TIMER_ONE_PULSE_ACTIVE_DIS, \b TIMER_ONE_PULSE_ACTIVE_EN.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
Timer1PulseActiveConfigure(unsigned long ulBase, unsigned long ulChannel,
                                       unsigned long ulActive)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulChannel == TIMER_CH_0) || (ulChannel == TIMER_CH_1) ||
            (ulChannel == TIMER_CH_2) || (ulChannel == TIMER_CH_3)); 
    xASSERT((ulActive == TIMER_ONE_PULSE_ACTIVE_DIS) || 
            (ulActive == TIMER_ONE_PULSE_ACTIVE_EN));

    if(ulActive == TIMER_ONE_PULSE_ACTIVE_DIS) 
    {
        xHWREG(ulBase + TIMER_CH0OCFR + ulChannel * 4) &= ~TIMER_CH0OCFR_CH0IMAE;
    }
    else
    {
        xHWREG(ulBase + TIMER_CH0OCFR + ulChannel * 4) |= TIMER_CH0OCFR_CH0IMAE;
    }
}

//*****************************************************************************
//
//! \brief Enables or Disables the one pulse immediate active function.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the Timer channe mode.
//! \param ulActive is the selection of Reference Output Clear bit.
//!
//! The \e ulChannel parameter can be one of the values:
//! \b TIMER_CH_0, \b TIMER_CH_1, \b TIMER_CH_2, \b TIMER_CH_3.
//!
//! The \e ulControl parameter can be one of the values:
//! \b TIMER_CHCTL_DISABLE, \b TIMER_CHCTL_ENABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCHConfigure(unsigned long ulBase, unsigned long ulChannel, 
                             unsigned long ulControl)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulChannel == TIMER_CH_0) || (ulChannel == TIMER_CH_1) ||
            (ulChannel == TIMER_CH_2) || (ulChannel == TIMER_CH_3)); 
    xASSERT((ulControl == TIMER_CHCTL_DISABLE) || 
            (ulControl == TIMER_CHCTL_ENABLE)); 
    
    //
    // Reset the CHxE
    //
    xHWREG(ulBase + TIMER_CHCTR) &= ~(1 << (ulChannel * 2)); 
    
    //
    // Set the CHxE
    //
    xHWREG(ulBase + TIMER_CHCTR) |= (ulControl << (ulChannel * 2)); 
}

//*****************************************************************************
//
//! \brief Enables or Disables the one pulse immediate active function.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulUpdate is the selection of Update event Disable control.
//!
//! The \e ulUpdate parameter can be one of the values:
//! \b TIMER_UPDATE_EVENT_EN, \b TIMER_UPDATE_EVENT_DIS.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerUpdateConfigure(unsigned long ulBase, unsigned long ulUpdate)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulUpdate == TIMER_UPDATE_EVENT_EN) || 
            (ulUpdate == TIMER_UPDATE_EVENT_DIS));
    
    if(ulUpdate == TIMER_UPDATE_EVENT_EN)
    {
        xHWREG(ulBase + TIMER_CNTCFR) &= ~TIMER_CNTCFR_UEVDIS;     
    }
    else
    {
        xHWREG(ulBase + TIMER_CNTCFR) |= TIMER_CNTCFR_UEVDIS; 
    }    
}

//*****************************************************************************
//
//! \brief Enables the update event interrupt.
//!
//! \param ulBase is the base address of the Timer port.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerUpdateIntEnable(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    xHWREG(ulBase + TIMER_CNTCFR) |= TIMER_CNTCFR_UGDIS;
}

//*****************************************************************************
//
//! \brief Disable the update event interrupt.
//!
//! \param ulBase is the base address of the Timer port.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerUpdateIntDisable(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    xHWREG(ulBase + TIMER_CNTCFR) &= ~TIMER_CNTCFR_UGDIS;
}

//*****************************************************************************
//
//! \brief Disable the update event interrupt.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulConfigure is selection of Enable or Disable the Hall interface.
//!
//! The \e ulConfigure parameter can be one of the values:
//! \b TIMER_HALL_INTERFACE_EN, \b TIMER_HALL_INTERFACE_DIS.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerHallInterfaceConfigure(unsigned long ulBase,  unsigned long ulConfigure)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulConfigure == TIMER_HALL_INTERFACE_EN) ||
            (ulConfigure == TIMER_HALL_INTERFACE_DIS));
    
    if(ulConfigure == TIMER_HALL_INTERFACE_EN)
    {
        xHWREG(ulBase + TIMER_CH0ICFR) &= ~TIMER_CH0ICFR_TI0SRC;
    }
    else
    {
        xHWREG(ulBase + TIMER_CH0ICFR) |= TIMER_CH0ICFR_TI0SRC;
    }
}

//*****************************************************************************
//
//! \brief Disable the Single Pulse Mode.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulConfigure is selection of Enable or Disable one pulse mode.
//!
//! The \e ulConfigure parameter can be one of the values:
//! \b TIMER_ONE_PULSE_MODE_EN, \b TIMER_ONE_PULSE_MODE_DIS.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOnePulseModeConfigure(unsigned long ulBase, unsigned long ulConfigure)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulConfigure == TIMER_ONE_PULSE_MODE_EN) ||
            (ulConfigure == TIMER_ONE_PULSE_MODE_DIS));
    
    if(ulConfigure == TIMER_ONE_PULSE_MODE_EN)
    {
        xHWREG(ulBase + TIMER_MDCFR) |= TIMER_MDCFR_SPMSET;
    }
    else
    {
        xHWREG(ulBase + TIMER_MDCFR) &= ~TIMER_MDCFR_SPMSET;
    }
}

//*****************************************************************************
//
//! \brief Selects master trigger output source of the Timer.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulSelect is selection of master trigger output source.
//!
//! The \e ulSelect parameter can be one of the values:
//! \b TIMER_ONE_PULSE_MODE_EN, \b TIMER_ONE_PULSE_MODE_DIS.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerMasterOutputSrcSelect(unsigned long ulBase, unsigned long ulSelect)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulSelect == TIMER_MMSEL_RESET) || 
            (ulSelect == TIMER_MMSEL_ENABLE) ||
            (ulSelect == TIMER_MMSEL_UPDATE) ||
            (ulSelect == TIMER_MMSEL_CH0CC) ||
            (ulSelect == TIMER_MMSEL_CH0OREF) ||
            (ulSelect == TIMER_MMSEL_CH1OREF) || 
            (ulSelect == TIMER_MMSEL_CH2OREF) || 
            (ulSelect == TIMER_MMSEL_CH3OREF));
    
    xHWREG(ulBase + TIMER_MDCFR) &= ~TIMER_MDCFR_MMSEL_M;
    xHWREG(ulBase + TIMER_MDCFR) |= ulSelect;
}

//*****************************************************************************
//
//! \brief Selects Selects slave mode of the Timer.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulSelect is selection of slave mode.
//!
//! The \e ulSelect parameter can be one of the values:
//! \b TIMER_SMSEL_RESTART, \b TIEMR_SMSEL_PAUSE,
//! \b TIMER_SMSEL_TRIGGER, \b TIMER_SMSEL_STIED.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerSlaveModeConfigure(unsigned long ulBase, unsigned long ulSelect)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulSelect == TIMER_SMSEL_RESTART) || 
            (ulSelect == TIEMR_SMSEL_PAUSE) ||
            (ulSelect == TIMER_SMSEL_TRIGGER) ||
            (ulSelect == TIMER_SMSEL_STIED)); 
    
    xHWREG(ulBase + TIMER_MDCFR) &= ~TIMER_MDCFR_SMSEL_M;
    xHWREG(ulBase + TIMER_MDCFR) |= ulSelect;
    
}

//*****************************************************************************
//
//! \brief  Enables or Disables the master & slave Timer synchronous function.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulConfigure is Enable or Disable the Synchronization.
//!
//! The \e ulConfigure parameter can be one of the values:
//! \b TIMER_SYNC_ENABLE, \b TIMER_SYNC_DISABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerSyncConfigure(unsigned long ulBase, unsigned long ulConfigure)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulConfigure == TIMER_SYNC_ENABLE) ||
            (ulConfigure == TIMER_SYNC_DISABLE));
    
    xHWREG(ulBase + TIMER_MDCFR) &= ~TIMER_MDCFR_SMSEL_TSE;
    xHWREG(ulBase + TIMER_MDCFR) |= ulConfigure;
    
}

//*****************************************************************************
//
//! \brief Sets counter register value.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulCounter is the counter register new value. It is a value between 0
//! and Ox0000FFFF.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCounterSet(unsigned long ulBase, unsigned long ulCounter)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulCounter >= 0) && (ulCounter <= 0x0000FFFF));
    
    xHWREG(ulBase + TIMER_CNTR) = ulCounter; 
}

//*****************************************************************************
//
//! \brief Sets counter reload register value.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulCRRValue is the counter reload register new value. It is a value 
//! between 0 and Ox0000FFFF.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCRRSet(unsigned long ulBase, unsigned long ulCRRValue)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulCRRValue >= 0) && (ulCRRValue <= 0x0000FFFF));
    
    xHWREG(ulBase + TIMER_CRR) = ulCRRValue;    
}

//*****************************************************************************
//
//! \brief Get counter reload register value.
//!
//! \param ulBase is the base address of the Timer port.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
TimerCRRGet(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    return (xHWREG(ulBase + TIMER_CRR));
}

//*****************************************************************************
//
//! \brief Sets channel x capture/compare register value.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulCCValue is the the CHxCCR register new value. It is a value 
//! between 0 and Ox0000FFFF.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCaptureCompareSet(unsigned long ulBase, unsigned long ulChannel, 
                                   unsigned long ulCCValue)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulCCValue >= 0) && (ulCCValue <= 0x0000FFFF));
    
    xHWREG(ulBase + TIMER_CH0CCR + ulChannel * 4) = ulCCValue;   
    
}

//*****************************************************************************
//
//! \brief Sets clock division value of the Timer.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulDiv is the clock division value
//!
//! The \e ulDiv parameter can be one of the values:
//! \b TIMER_CKDIV_OFF, \b TIMER_CKDIV_2, \b TIMER_CKDIV_4.
//! 
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCKDivConfigure(unsigned long ulBase, unsigned long ulDiv)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulDiv == TIMER_CKDIV_OFF) || 
            (ulDiv == TIMER_CKDIV_2) || (ulDiv == TIMER_CKDIV_4));
    
    xHWREG(ulBase + TIMER_CNTCFR) &= ~TIMER_CNTCFR_CKDIV_M;
    xHWREG(ulBase + TIMER_CNTCFR) |= ulDiv;
    
}

//*****************************************************************************
//
//! \brief Get channel x capture/compare register value.
//!
//! \param ulBase is the base address of the Timer port.
//!
//! \note None
//!
//! \return Value of CHxCCR register.
//
//*****************************************************************************
unsigned long 
TimerCaptureCompareGet(unsigned long ulBase, unsigned long ulChannel)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulChannel == TIMER_CH_0) || (ulChannel == TIMER_CH_1) ||
            (ulChannel == TIMER_CH_2) || (ulChannel == TIMER_CH_3)); 

    return (xHWREG(ulBase + TIMER_CH0CCR + ulChannel * 4));    
}

//*****************************************************************************
//
//! \brief Get the counter value of TIMERx.
//!
//! \param ulBase is the base address of the Timer port.
//!
//! \note None
//!
//! \return Value of Counter register.
//
//*****************************************************************************
unsigned long 
TimerCounterGet(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    return (xHWREG(ulBase + TIMER_CNTR));
}

//*****************************************************************************
//
//! \brief Get the  prescaler value of TIMERx.
//!
//! \param ulBase is the base address of the Timer port.
//!
//! \note None
//!
//! \return Value of Prescaler register.
//
//*****************************************************************************
unsigned long 
TimerPerscalerGet(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    return (xHWREG(ulBase + TIMER_PSCR));
}

//*****************************************************************************
//
//! \brief  Generate Timer events.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulEvent is the event source.
//!
//! The \e ulEvent parameter can be one of the values:
//! \b TIMER_EVENT_CHOCC, \b TIMER_EVENT_CH1CC, \b TIMER_EVENT_CH2CC,
//! \b TIMER_EVENT_CH3CC, \b TIMER_EVENT_UEV1, \b TIMER_EVENT_TEV.
//!
//! \note None
//!
//! \return None
//
//*****************************************************************************
void 
TimerEventGenerate(unsigned long ulBase, unsigned long ulEvent)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulEvent == TIMER_EVENT_CHOCC) || (ulEvent == TIMER_EVENT_CH1CC) ||
            (ulEvent == TIMER_EVENT_CH2CC) || (ulEvent == TIMER_EVENT_CH3CC) ||
            (ulEvent == TIMER_EVENT_UEV1) || (ulEvent == TIMER_EVENT_TEV));
    
    xHWREG(ulBase + TIMER_EVGR) |= ulEvent;
}


//*****************************************************************************
//
//! \brief whether the specified Timer flag has been set.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulFlag is the specified Flag.
//!
//! The \e ulFlag parameter can be one of the values:
//! \b TIMER_FLAG_CH0CC, \b TIMER_FLAG_CH1CC, \b TIMER_FLAG_CH2CC,
//! \b TIMER_FLAG_CH3CC, \b TIMER_FLAG_CH0OC, \b TIMER_FLAG_CH1OC,
//! \b TIMER_FLAG_CH2OC, \b TIMER_FLAG_CH3OC, \b TIMER_FLAG_UEV1, 
//! \b TIMER_FLAG_TEV.
//!
//! \note None
//!
//! \return xtrue the flag is set
//!         xfalse the flag is not set.
//
//*****************************************************************************
xtBoolean 
TimerFlagStatusGet(unsigned long ulBase, unsigned long ulFlag)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulFlag == TIMER_FLAG_CH0CC) || (ulFlag == TIMER_FLAG_CH1CC) ||
            (ulFlag == TIMER_FLAG_CH2CC) || (ulFlag == TIMER_FLAG_CH3CC) ||
            (ulFlag == TIMER_FLAG_CH0OC) || (ulFlag == TIMER_FLAG_CH1OC) ||
            (ulFlag == TIMER_FLAG_CH2OC) || (ulFlag == TIMER_FLAG_CH3OC) ||
            (ulFlag == TIMER_FLAG_UEV1) || (ulFlag == TIMER_FLAG_TEV));
    
    if((xHWREG(ulBase + TIMER_INTSR) & ulFlag))
    {
        return xtrue;  
    }
    else
    {
        return xfalse;
    }
}

//*****************************************************************************
//
//! \brief Clears flags of the Timer.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulFlag is the specified Flag.
//!
//! The \e ulFlag parameter can be one of the values:
//! \b TIMER_FLAG_CH0CC, \b TIMER_FLAG_CH1CC, \b TIMER_FLAG_CH2CC,
//! \b TIMER_FLAG_CH3CC, \b TIMER_FLAG_CH0OC, \b TIMER_FLAG_CH1OC,
//! \b TIMER_FLAG_CH2OC, \b TIMER_FLAG_CH3OC, \b TIMER_FLAG_UEV1, 
//! \b TIMER_FLAG_TEV.
//!
//! \note None
//!
//! \return None
//
//*****************************************************************************
void 
TimerFlagStatusClear(unsigned long ulBase, unsigned long ulFlag)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulFlag == TIMER_FLAG_CH0CC) || (ulFlag == TIMER_FLAG_CH1CC) ||
            (ulFlag == TIMER_FLAG_CH2CC) || (ulFlag == TIMER_FLAG_CH3CC) ||
            (ulFlag == TIMER_FLAG_CH0OC) || (ulFlag == TIMER_FLAG_CH1OC) ||
            (ulFlag == TIMER_FLAG_CH2OC) || (ulFlag == TIMER_FLAG_CH3OC) ||
            (ulFlag == TIMER_FLAG_UEV1) || (ulFlag == TIMER_FLAG_TEV));
    
    xHWREG(ulBase + TIMER_INTSR) &= ~ulFlag;
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the timer.
//!
//! \param ulBase is the base address of the Timer port.
//! \param xtTimerCallback is callback for the timer.
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
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
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
        }
    }
}

//*****************************************************************************
//
//! \brief Enables or Disables the specified interrupts of the Timer. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulIntFlags is the interrupt type of the Timer port.
//!
//! This function is to enable The Timer counter interrupt.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! \b TIMER_INT_CH0CC, \b TIMER_INT_CH1CC, \b TIMER_INT_CH2CC, 
//! \b TIMER_INT_CH3CC, \b TIMER_INT_UEV1, \b TIMER_INT_TEV.
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
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulIntFlags == TIMER_INT_CH0CC) || (ulIntFlags == TIMER_INT_CH1CC) ||
            (ulIntFlags == TIMER_INT_CH2CC) || (ulIntFlags == TIMER_INT_CH3CC) ||
            (ulIntFlags == TIMER_INT_UEV1) || (ulIntFlags == TIMER_INT_TEV));
    
    xHWREG(ulBase + TIMER_ICTR) |= ulIntFlags;
}

//*****************************************************************************
//
//! \brief Disable The Timer counter interrupt. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulIntFlags is the interrupt type of the Timer port.
//!
//! This function is to Disable The Timer counter interrupt.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! \b TIMER_INT_CH0CC, \b TIMER_INT_CH1CC, \b TIMER_INT_CH2CC, 
//! \b TIMER_INT_CH3CC, \b TIMER_INT_UEV1, \b TIMER_INT_TEV.
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
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulIntFlags == TIMER_INT_CH0CC) || (ulIntFlags == TIMER_INT_CH1CC) ||
            (ulIntFlags == TIMER_INT_CH2CC) || (ulIntFlags == TIMER_INT_CH3CC) ||
            (ulIntFlags == TIMER_INT_UEV1) || (ulIntFlags == TIMER_INT_TEV));
    
    xHWREG(ulBase + TIMER_ICTR) &= ~ulIntFlags;
}

//*****************************************************************************
//
//! \brief Get The Timer counter interrupt Status. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulIntFlags is the interrupt type of the Timer port.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! \b TIMER_INT_CH0CC, \b TIMER_INT_CH1CC, \b TIMER_INT_CH2CC, 
//! \b TIMER_INT_CH3CC, \b TIMER_INT_UEV1, \b TIMER_INT_TEV.
//!
//! \note When use this API ,the ulIntFlags parameter one of the interrupt event
//!
//! \return xtrue: the interrupt occured.
//!         xfalse: the interrupt didn't occure.
//
//*****************************************************************************
xtBoolean
TimerIntStatus(unsigned long ulBase, unsigned long ulIntFlags)
{
    unsigned long ulIntStatus, ulIntEnable;
    //
    // Check the arguments.
    //  
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xASSERT((ulIntFlags == TIMER_INT_CH0CC) || (ulIntFlags == TIMER_INT_CH1CC) ||
            (ulIntFlags == TIMER_INT_CH2CC) || (ulIntFlags == TIMER_INT_CH3CC) ||
            (ulIntFlags == TIMER_INT_UEV1) || (ulIntFlags == TIMER_INT_TEV));

    ulIntStatus = xHWREG(ulBase + TIMER_INTSR) & ulIntFlags;
    ulIntEnable = xHWREG(ulBase + TIMER_ICTR) & ulIntFlags;
    
    if ((ulIntStatus != 0) && (ulIntEnable != 0))
    {
        return xtrue;
    }
    else
    {
        return xfalse;
    }
}

//*****************************************************************************
//
//! \brief Clears interrupt pending bits of the Timer. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulIntFlags is the interrupt type of the Timer port.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! \b TIMER_INT_CH0CC, \b TIMER_INT_CH1CC, \b TIMER_INT_CH2CC, 
//! \b TIMER_INT_CH3CC, \b TIMER_INT_UEV1, \b TIMER_INT_TEV.
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
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    xHWREG(ulBase + TIMER_INTSR) &= ~ulIntFlags;

}

//*****************************************************************************
//
//! \brief Disables slave mode to clock the prescaler directly with the internal
//! clock. 
//!
//! \param ulBase is the base address of the Timer port.
//!
//! \return None.
//
//*****************************************************************************
void 
TimerInternalClkConfigure(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    xHWREG(ulBase + TIMER_MDCFR) &= ~TIMER_MDCFR_SMSEL_M;
}