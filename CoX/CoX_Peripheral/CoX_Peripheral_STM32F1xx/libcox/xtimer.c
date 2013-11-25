//*****************************************************************************
//
//! \file xtimer.c
//! \brief Driver for the Timer
//! \version V2.2.1.0
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
#include "xhw_config.h"
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
static xtEventCallback g_pfnTimerHandlerCallbacks[22]={0};

#if (TIM1_FUNCTION_SELECT == TIM_TIMER || TIM9_FUNCTION_SELECT == TIM_TIMER)
//*****************************************************************************
//
//! \brief TIM1 Break and IIM9 global interrupt serivice function.
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
TIM1BRKTIM9IntHandler(void)
{
    unsigned long ulTemp = 0, ulTemp1 = 0;

    //
    // The SR register read cleared
    //
    ulTemp = xHWREG(RCC_APB2ENR) & RCC_APB2ENR_TIM1EN;

    if(ulTemp != 0)
    {
        ulTemp = xHWREG(TIM1_BASE + TIMER_SR);
    }

#if (STM32F1xx_DEVICE == STM32F10X_XL)
    ulTemp1 = xHWREG(RCC_APB2ENR) & RCC_APB2ENR_TIM9EN;
    
    if(ulTemp1 != 0)
    {
        ulTemp1 = xHWREG(TIM9_BASE + TIMER_SR);
    }
#endif

    if((ulTemp & TIMER_SR_BIF) != 0)
    {
        g_pfnTimerHandlerCallbacks[0](0, 0, ulTemp, 0);
    }
    else
    {
        g_pfnTimerHandlerCallbacks[16](0, 0, ulTemp1, 0);
    }
    
}
#endif


#if (TIM1_FUNCTION_SELECT == TIM_TIMER || TIM10_FUNCTION_SELECT == TIM_TIMER)
//*****************************************************************************
//
//! \brief TIM1 Update and TIM10 global interrupt service function.
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
TIM1UPTIM10IntHandler(void)
{
    unsigned long ulTemp = 0, ulTemp1 = 0;

    ulTemp = xHWREG(RCC_APB2ENR) & RCC_APB2ENR_TIM1EN;

    if(ulTemp != 0)
    {
        ulTemp = xHWREG(TIM1_BASE + TIMER_SR);
    }

#if (STM32F1xx_DEVICE == STM32F10X_XL)
    ulTemp1 = xHWREG(RCC_APB2ENR) & RCC_APB2ENR_TIM10EN;
    if(ulTemp1 != 0)
    {
        ulTemp1 = xHWREG(TIM10_BASE + TIMER_SR);
    }
#endif

    if((ulTemp & TIMER_SR_UIF) != 0)
    {
        g_pfnTimerHandlerCallbacks[1](0, 0, ulTemp, 0);
    }
    else
    {
        g_pfnTimerHandlerCallbacks[17](0, 0, ulTemp1, 0);
    }    
}
#endif


#if (TIM1_FUNCTION_SELECT == TIM_TIMER || TIM11_FUNCTION_SELECT == TIM_TIMER)
//*****************************************************************************
//
//! \brief TIM1 Trigger and Commutation and TIM11 global interrupt service 
//!        function.
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
TIM1TRGCOMTIM11IntHandler(void)
{
    unsigned long ulTemp = 0, ulTemp1 = 0;

    //
    // The SR register read cleared
    //
    ulTemp = xHWREG(RCC_APB2ENR) & RCC_APB2ENR_TIM1EN;

    if(ulTemp != 0)
    {
        ulTemp = xHWREG(TIM1_BASE + TIMER_SR);
    }

#if (STM32F1xx_DEVICE == STM32F10X_XL)
    ulTemp1 = xHWREG(RCC_APB2ENR) & RCC_APB2ENR_TIM11EN;
    if(ulTemp1 != 0)
    {
        ulTemp = xHWREG(TIM11_BASE + TIMER_SR);
    }
#endif

    if((ulTemp & TIMER_SR_TIF) != 0)
    {
        g_pfnTimerHandlerCallbacks[2](0, 0, ulTemp, 0);
    }
    else if((ulTemp & TIMER_SR_COMIF) != 0)
    {
        g_pfnTimerHandlerCallbacks[3](0, 0, ulTemp, 0);
    }
    else
    {
        g_pfnTimerHandlerCallbacks[18](0, 0, ulTemp1, 0);
    }    
}
#endif

#if (TIM1_FUNCTION_SELECT == TIM_TIMER)
//*****************************************************************************
//
//! \brief TIM1 Capture Compare interrupt service function.
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
TIM1CCIntHandler(void)
{
    unsigned long ulTemp = 0;

    //
    // The SR register read cleared
    //
    ulTemp = xHWREG(TIM1_BASE + TIMER_SR);
    xHWREG(TIM1_BASE + TIMER_SR) &= ~0x1E;

    g_pfnTimerHandlerCallbacks[4](0, 0, ulTemp, 0);
    
}
#endif

#if (TIM2_FUNCTION_SELECT == TIM_TIMER)
//*****************************************************************************
//
//! \brief TIM2 global interrupt service function.
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
TIM2IntHandler(void)
{
    unsigned long ulTemp = 0;

    //
    // The SR register read cleared
    //
    ulTemp = xHWREG(TIM2_BASE + TIMER_SR);

    g_pfnTimerHandlerCallbacks[5](0, 0, ulTemp, 0);
    
}
#endif

#if (TIM3_FUNCTION_SELECT == TIM_TIMER)
//*****************************************************************************
//
//! \brief TIM3 global interrupt service function.
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
TIM3IntHandler(void)
{
    unsigned long ulTemp = 0;

    //
    // The SR register read cleared
    //
    ulTemp = xHWREG(TIM3_BASE + TIMER_SR);

    g_pfnTimerHandlerCallbacks[6](0, 0, ulTemp, 0);
    
}
#endif

#if (TIM4_FUNCTION_SELECT == TIM_TIMER)
//*****************************************************************************
//
//! \brief TIM4 global interrupt service function.
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
TIM4IntHandler(void)
{
    unsigned long ulTemp = 0;

    //
    // The SR register read cleared
    //
    ulTemp = xHWREG(TIM4_BASE + TIMER_SR);

    g_pfnTimerHandlerCallbacks[7](0, 0, ulTemp, 0);
    
}
#endif

#if (TIM5_FUNCTION_SELECT == TIM_TIMER)
//*****************************************************************************
//
//! \brief TIM5 global interrupt service function.
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
TIM5IntHandler(void)
{
    unsigned long ulTemp = 0;

    //
    // The SR register read cleared
    //
    ulTemp = xHWREG(TIM5_BASE + TIMER_SR);

    g_pfnTimerHandlerCallbacks[8](0, 0, ulTemp, 0);
    
}
#endif

#if (STM32F1xx_DEVICE == STM32F10X_XL || STM32F1xx_DEVICE == STM32F10X_HD_VL || \
     STM32F1xx_DEVICE == STM32F10X_CL)

//*****************************************************************************
//
//! \brief TIM6 global interrupt service function.
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
TIM6IntHandler(void)
{
    unsigned long ulTemp = 0;

    //
    // The SR register read cleared
    //
    ulTemp = xHWREG(TIM6_BASE + TIMER_SR);

    g_pfnTimerHandlerCallbacks[9](0, 0, ulTemp, 0);
    
}

//*****************************************************************************
//
//! \brief TIM7 global interrupt service function.
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
TIM7IntHandler(void)
{
    unsigned long ulTemp = 0;

    //
    // The SR register read cleared
    //
    ulTemp = xHWREG(TIM7_BASE + TIMER_SR);

    g_pfnTimerHandlerCallbacks[10](0, 0, ulTemp, 0);
    
}
#endif

#if (STM32F1xx_DEVICE == STM32F10X_XL || STM32F1xx_DEVICE == STM32F10X_HD_VL)
#if (TIM8_FUNCTION_SELECT == TIM_TIMER || TIM12_FUNCTION_SELECT == TIM_TIMER)
//*****************************************************************************
//
//! \brief TIM8 Break and TIM12 global interrupt serivice function.
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
TIM8BRKTIM12IntHandler(void)
{
    unsigned long ulTemp = 0, ulTemp1 = 0;

    //
    // The SR register read cleared
    //
#if((STM32F1xx_DEVICE == STM32F10X_HD_VL) || (STM32F1xx_DEVICE == STM32F10X_XL))
    ulTemp = xHWREG(RCC_APB2ENR) & RCC_APB2ENR_TIM8EN;

    if(ulTemp != 0)
    {
        ulTemp = xHWREG(TIM8_BASE + TIMER_SR);
    }
#endif

#if(STM32F1xx_DEVICE == STM32F10X_XL)
    ulTemp1 = xHWREG(RCC_APB1ENR) & RCC_APB1ENR_TIM12EN;

    if(ulTemp1 != 0)
    {
        ulTemp1 = xHWREG(TIM12_BASE + TIMER_SR);
    }
#endif

    if(ulTemp & TIMER_SR_BIF != 0)
    {
        g_pfnTimerHandlerCallbacks[11](0, 0, ulTemp, 0);
    }
    else
    {
        g_pfnTimerHandlerCallbacks[19](0, 0, ulTemp1, 0);
    }
    
}
#endif

#if (TIM8_FUNCTION_SELECT == TIM_TIMER || TIM13_FUNCTION_SELECT == TIM_TIMER)
//*****************************************************************************
//
//! \brief TIM8 Update interrupt and TIM13 global interrupt service function.
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
TIM8UPTIM13IntHandler(void)
{
    unsigned long ulTemp = 0, ulTemp1 = 0;

#if((STM32F1xx_DEVICE == STM32F10X_HD_VL) || (STM32F1xx_DEVICE == STM32F10X_XL))
    ulTemp = xHWREG(RCC_APB2ENR) & RCC_APB2ENR_TIM8EN;

    if(ulTemp != 0)
    {
        ulTemp = xHWREG(TIM8_BASE + TIMER_SR);
    }
#endif
#if(STM32F1xx_DEVICE == STM32F10X_XL)
    ulTemp1 = xHWREG(RCC_APB1ENR) & RCC_APB1ENR_TIM13EN;

    if(ulTemp1 != 0)
    {
        ulTemp1 = xHWREG(TIM13_BASE + TIMER_SR);
    }
#endif

    if(ulTemp & TIMER_SR_UIF != 0)
    {
        g_pfnTimerHandlerCallbacks[12](0, 0, ulTemp, 0);
    }
    else
    {
        g_pfnTimerHandlerCallbacks[20](0, 0, ulTemp1, 0);
    }    
}
#endif

#if (TIM8_FUNCTION_SELECT == TIM_TIMER || TIM14_FUNCTION_SELECT == TIM_TIMER)
//*****************************************************************************
//
//! \brief TIM8 Trigger and Commutation and TIM14 global interrupt service 
//!        function.
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
TIM8TRGCOMTIM14IntHandler(void)
{
    unsigned long ulTemp = 0, ulTemp1 = 0;

    //
    // The SR register read cleared
    //
#if((STM32F1xx_DEVICE == STM32F10X_HD_VL) || (STM32F1xx_DEVICE == STM32F10X_XL))
    ulTemp = xHWREG(RCC_APB2ENR) & RCC_APB2ENR_TIM8EN;

    if(ulTemp != 0)
    {
        ulTemp = xHWREG(TIM8_BASE + TIMER_SR);
    }
#endif
#if(STM32F1xx_DEVICE == STM32F10X_XL)
    ulTemp1 = xHWREG(RCC_APB1ENR) & RCC_APB1ENR_TIM14EN;

    if(ulTemp1 != 0)
    {
        ulTemp1 = xHWREG(TIM14_BASE + TIMER_SR);
    }
#endif
    if(ulTemp & TIMER_SR_TIF != 0)
    {
        g_pfnTimerHandlerCallbacks[13](0, 0, ulTemp, 0);
    }
    else if(ulTemp & TIMER_SR_COMIF != 0)
    {
        g_pfnTimerHandlerCallbacks[14](0, 0, ulTemp, 0);
    }
    else
    {
        g_pfnTimerHandlerCallbacks[21](0, 0, ulTemp1, 0);
    }    
}
#endif

#if (TIM8_FUNCTION_SELECT == TIM_TIMER)
//*****************************************************************************
//
//! \brief TIM1 Capture Compare interrupt service function.
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
TIM8CCIntHandler(void)
{
    unsigned long ulTemp = 0;

    //
    // The SR register read cleared
    //
    ulTemp = xHWREG(TIM8_BASE + TIMER_SR);

    g_pfnTimerHandlerCallbacks[15](0, 0, ulTemp, 0);
    
}
#endif
#endif

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
//! \b xTIMER_MODE_CONTINUOUS, \b xTIMER_MODE_CAPTURE is the Timer's mode.
//! 
//! \b xTIMER_COUNT_UP, \b xTIMER_COUNT_DOWN is the Timer's direction.
//!
//! The \e ulTickFreq parameter is the the timer tick frequency.It can be any
//! values but ulTickFreq > 0 and ulTickFreq < timer clock source.
//!
//! \note For HT32F125x, each timer only one channel.
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
    unsigned long ulTemp;
    
    //
    // Check the arguments.
    //
    xASSERT((ulChannel == xTIMER_CHANNEL0) || 
            (ulChannel == xTIMER_CHANNEL1) ||
            (ulChannel == xTIMER_CHANNEL2) ||
            (ulChannel == xTIMER_CHANNEL3));

    //
    // Get the timer clock source frequency
    //
    if((ulBase == xTIMER1_BASE) || (ulBase == xTIMER8_BASE) || 
       (ulBase == xTIMER9_BASE) || (ulBase == xTIMER10_BASE) || 
       (ulBase == xTIMER11_BASE))
    {
        ulInternalClk = SysCtlAPB2ClockGet();
        ulTemp = (xHWREG(RCC_CFGR) & RCC_CFGR_PPRE2_M) >> RCC_CFGR_PPRE2_S;
        if(ulTemp == 1)
        {
            ulInternalClk = ulInternalClk * 2; 
        }
    }
    else
    {
        ulInternalClk = SysCtlAPB1ClockGet();
        ulTemp = (xHWREG(RCC_CFGR) & RCC_CFGR_PPRE1_M) >> RCC_CFGR_PPRE1_S;
        if(ulTemp == 1)
        {
            ulInternalClk = ulInternalClk * 2;
        }
    }
    
    for (ulPreScale = 1; ulPreScale < 0x0000FFFF; ulPreScale++)
    {
        ulTCMPRValue = ulInternalClk / (ulTickFreq * ulPreScale);
 
        //
        // The TCMPR value must > 1 
        //
        if ((ulTCMPRValue > 1) && (ulTCMPRValue < 0x0000FFFF))
            break;
    }
    
    switch(ulConfig & 0x000000F0)
    {
        case xTIMER_MODE_ONESHOT:
        {
            //
            // One shot mode
            // 
            TimerOnePulseModeConfigure(ulBase, TIMER_OPMODE_SINGLE);

            //
            // Output mode timing
            //
            TimerOCxModeSelect(ulBase, ulChannel, TIMER_OCMODE_TIMING);
            break;
        }
        case xTIMER_MODE_PERIODIC:
        {
            //
            // Periodic mode
            //
            TimerOnePulseModeConfigure(ulBase, TIMER_OPMODE_REPETIVE);

            //
            // Output mode timing
            //
            TimerOCxModeSelect(ulBase, ulChannel, TIMER_OCMODE_TIMING);
            break;
        }
        case xTIMER_MODE_TOGGLE:
        {
            TimerOnePulseModeConfigure(ulBase, TIMER_OPMODE_REPETIVE);

            //
            // Output toggle control 
            //
            if(ulChannel == xTIMER_CHANNEL0)
            {
                TimerOC1Configure(ulBase, TIMER_OCMODE_TOGGLE, ulTCMPRValue/2, 
                TIMER_OP_STATE_EN | TIMER_OP_POL_HIGH, 
                TIMER_OP_N_STATE_EN | TIMER_OP_N_POL_HIGH, 
                TIMER_OCIDLESTATE_RESET | TIMER_OCNIDLESTATE_RESET);
            }
            else if(ulChannel == xTIMER_CHANNEL1)
            {
                TimerOC2Configure(ulBase, TIMER_OCMODE_TOGGLE, ulTCMPRValue/2, 
                TIMER_OP_STATE_EN | TIMER_OP_POL_HIGH, 
                TIMER_OP_N_STATE_EN | TIMER_OP_N_POL_HIGH, 
                TIMER_OCIDLESTATE_RESET | TIMER_OCNIDLESTATE_RESET);
            }
            else if(ulChannel == xTIMER_CHANNEL2)
            {
                TimerOC3Configure(ulBase, TIMER_OCMODE_TOGGLE, ulTCMPRValue/2, 
                TIMER_OP_STATE_EN | TIMER_OP_POL_HIGH, 
                TIMER_OP_N_STATE_EN | TIMER_OP_N_POL_HIGH, 
                TIMER_OCIDLESTATE_RESET | TIMER_OCNIDLESTATE_RESET);
            }
            else
            {
                TimerOC4Configure(ulBase, TIMER_OCMODE_TOGGLE, ulTCMPRValue/2, 
                TIMER_OP_STATE_EN | TIMER_OP_POL_HIGH, 
                TIMER_OP_N_STATE_EN | TIMER_OP_N_POL_HIGH, 
                TIMER_OCIDLESTATE_RESET | TIMER_OCNIDLESTATE_RESET);
            }
 
            break;
        }
        case xTIMER_MODE_CONTINUOUS:
        {
            break;
        }
        case xTIMER_MODE_CAPTURE:
        {
            TimerOnePulseModeConfigure(ulBase, TIMER_OPMODE_REPETIVE);
            //
            // Input capture mode cofigure
            //
            TimerICConfigure(ulBase, ulChannel, TIMER_ICPOL_RISING, 
                             TIMER_ICSEL_DIRTI, TIMER_ICPSC_DIV1, 0);
            break;
        }
        default: 
            break; 
    }
    
    if((ulConfig & 0x0000000F) == xTIMER_COUNT_UP)
    {
        //
        // Counter up
        //
        TimerCNTModeConfigure(ulBase, TIMER_CNT_MODE_UP);
    }
    else
    {
        //
        // Counter down
        //
        TimerCNTModeConfigure(ulBase, TIMER_CNT_MODE_DOWN);
    }
    
    //
    // Set the ARR and PSC register
    // 
    TimerARRPreloadConfigure(ulBase, TIMER_ARPE_ENABLE);
    TimerAutoReloadSet(ulBase, ulTCMPRValue);
    TimerPrescalerConfigure(ulBase, ulPreScale, TIMER_PSC_RLD_UPDATE);
    
}

//*****************************************************************************
//
//! \brief Enable The Timer counter as a counter. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port. In external counter, only
//!        xTIMER_CHANNEL0, xTIMER_CHANNEL1 be used.
//! Details please refer to \ref xTIMER_Count_Channel
//!
//! This function is to enable The Timer counter as a counter.
//!
//! \return None.
//
//*****************************************************************************
void 
xTimerCounterEnable(unsigned long ulBase, unsigned long ulChannel)
{
    xASSERT((ulChannel == xTIMER_CHANNEL0) || (ulChannel == xTIMER_CHANNEL1));

    if(ulChannel == xTIMER_CHANNEL0)
    {
        TimerTIxExternalClockConfigure(ulBase, TIMER_TRSEL_TI1FP1, 
                                       TIMER_ICPOL_RISING, 0);
    }
    else
    {
        TimerTIxExternalClockConfigure(ulBase, TIMER_TRSEL_TI2FP2, 
                                       TIMER_ICPOL_RISING, 0);
    }
    //TimerStart(ulBase);
}

//*****************************************************************************
//
//! \brief Disable The Timer counter as a counter. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//!
//! This function is to disable The Timer counter as a counter.
//!
//! \return None.
//
//*****************************************************************************
void 
xTimerCounterDisable(unsigned long ulBase, unsigned long ulChannel)
{
    //
    // Select the External clock mode1
    //
    TimerStop(ulBase);
}

//*****************************************************************************
//
//! \brief Enable The Timer counter as a capture. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//! \param ulCapMode is the capture mode of the Timer port.Which can be the 
//! values: \b xTIMER_CAP_MODE_CAP, \b xTIMER_CAP_MODE_RST.
//! Details please refer to \ref xTIMER_Capture_Mode_Type
//!
//! This function is to enable The Timer counter as a capture.
//!
//! \return None.
//
//*****************************************************************************
void 
xTimerCaptureModeSet(unsigned long ulBase, unsigned long ulChannel, 
                     unsigned long ulCapMode)
{
    if((ulCapMode & 0x0F) == 0x00000002)
    {
        TimerICConfigure(ulBase, ulChannel, TIMER_ICPOL_RISING, 
                         TIMER_ICSEL_DIRTI, TIMER_ICPSC_DIV1, 0);
        TimerSlaveModeConfigure(ulBase, TIMER_SMSEL_RESET);
    }
    else
    {
        TimerICConfigure(ulBase, ulChannel, TIMER_ICPOL_RISING, 
                         TIMER_ICSEL_DIRTI, TIMER_ICPSC_DIV1, 0);
        //TimerSlaveModeConfigure(ulBase, TIMER_SMSEL_DISABLE);
        TimerInternalClkConfigure(ulBase);
    } 
}

//*****************************************************************************
//
//! \brief Set The Timer counter Compare Match Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//! \param ulValue is Timer counter Compare Match Value.
//!
//! This function is to Set The Timer counter Compare Match Value.
//!
//! \return None.
//
//*****************************************************************************
void 
xTimerMatchSet(unsigned long ulBase, unsigned long ulChannel, 
               unsigned long ulValue)
{
    if(ulChannel == xTIMER_CHANNEL0)
    {
        TimerCompare1Set(ulBase, ulValue);
    }
    else if(ulChannel == xTIMER_CHANNEL1)
    {
        TimerCompare2Set(ulBase, ulValue);
    }
    else if(ulChannel == xTIMER_CHANNEL2)
    {
        TimerCompare3Set(ulBase, ulValue);
    }
    else
    {
        TimerCompare4Set(ulBase, ulValue);
    }
}

//*****************************************************************************
//
//! \brief Get The Timer counter Compare Match Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! Details please refer to \ref xTIMER_Count_Channel
//!
//! This function is to get The Timer counter Compare Match Value.
//!
//! \return the Prescale Value will be set.
//
//*****************************************************************************
unsigned long 
xTimerMatchGet(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulTemp = 0;   

    if(ulChannel == xTIMER_CHANNEL0)
    {
        ulTemp = TimerCapture1Get(ulBase);
    }
    else if(ulChannel == xTIMER_CHANNEL1)
    {
        ulTemp = TimerCapture2Get(ulBase);
    }
    else if(ulChannel == xTIMER_CHANNEL2)
    {
        ulTemp = TimerCapture3Get(ulBase);
    }
    else
    {
        ulTemp = TimerCapture4Get(ulBase);
    }
    return ulTemp;
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
//! \b xTIMER_INT_MATCH, \b xTIMER_INT_CAP_EVENT, \b xTIMER_INT_CAP_MATCH.
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
    xASSERT((ulIntFlags == xTIMER_INT_MATCH) || 
            (ulIntFlags == xTIMER_INT_CAP_EVENT) || 
            (ulIntFlags == xTIMER_INT_CAP_MATCH));

    if(ulIntFlags == xTIMER_INT_MATCH)
    {
        xHWREG(ulBase + TIMER_DIER) |= ulIntFlags;    
    }
    else
    {
        xHWREG(ulBase + TIMER_DIER) |= 
        (ulIntFlags & (TIMER_DIER_CC1IE << (ulChannel - 1)));
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
//! \b xTIMER_INT_MATCH, \b xTIMER_INT_CAP_EVENT. \b xTIMER_INT_CAP_MATCH.
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
    xASSERT((ulIntFlags == xTIMER_INT_MATCH) || 
            (ulIntFlags == xTIMER_INT_CAP_EVENT) || 
            (ulIntFlags == xTIMER_INT_CAP_MATCH));

    if(ulIntFlags == xTIMER_INT_MATCH)
    {
        xHWREG(ulBase + TIMER_DIER) &= ~ulIntFlags;    
    }
    else
    {
        xHWREG(ulBase + TIMER_DIER) &= 
        ~(ulIntFlags & (TIMER_DIER_CC1IE << (ulChannel -1)));
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
//! \b xTIMER_INT_MATCH, \b xTIMER_INT_CAP_EVENT. \b xTIMER_INT_CAP_MATCH.
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
    xASSERT((ulIntFlags == xTIMER_INT_MATCH) || 
            (ulIntFlags == xTIMER_INT_CAP_EVENT) || 
            (ulIntFlags == xTIMER_INT_CAP_MATCH));
    
    if(ulIntFlags == xTIMER_INT_MATCH)
    {
        if(xHWREG(ulBase + TIMER_SR) & TIMER_INT_UEV)
        {  
            return xtrue;
        }
    }
    else
    {
        if(xHWREG(ulBase + TIMER_SR) & (TIMER_SR_CC1IF << ulChannel))
        {
           return xtrue;
        }
    }   
    return xfalse;
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
xTimerIntCallbackInit(unsigned long ulBase, xtEventCallback xtTimerCallback)
{
    //
    // Init the interrupts callback.
    //
    switch(ulBase)
    {
        case TIM1_BASE:
            g_pfnTimerHandlerCallbacks[1] = xtTimerCallback;
            g_pfnTimerHandlerCallbacks[4] = xtTimerCallback;
            break;
        case TIM2_BASE:
            g_pfnTimerHandlerCallbacks[5] = xtTimerCallback;
            break;
        case TIM3_BASE:
            g_pfnTimerHandlerCallbacks[6] = xtTimerCallback;
            break;
        case TIM4_BASE:
            g_pfnTimerHandlerCallbacks[7] = xtTimerCallback;
            break;
        case TIM5_BASE:
            g_pfnTimerHandlerCallbacks[8] = xtTimerCallback;
            break;
        case TIM6_BASE:
            g_pfnTimerHandlerCallbacks[9] = xtTimerCallback;
            break;
        case TIM7_BASE:
            g_pfnTimerHandlerCallbacks[10] = xtTimerCallback;
            break;
        case TIM8_BASE:
            g_pfnTimerHandlerCallbacks[12] = xtTimerCallback;
            g_pfnTimerHandlerCallbacks[15] = xtTimerCallback;
            break;
        case TIM9_BASE:
            g_pfnTimerHandlerCallbacks[16] = xtTimerCallback;
            break;
        case TIM10_BASE:
            g_pfnTimerHandlerCallbacks[17] = xtTimerCallback;
            break;
        case TIM11_BASE:
            g_pfnTimerHandlerCallbacks[18] = xtTimerCallback;
            break;
        case TIM12_BASE:
            g_pfnTimerHandlerCallbacks[19] = xtTimerCallback;
            break;
        case TIM13_BASE:
            g_pfnTimerHandlerCallbacks[20] = xtTimerCallback;
            break;
        case TIM14_BASE:
            g_pfnTimerHandlerCallbacks[21] = xtTimerCallback;
            break;
    }
}

//*****************************************************************************
//
//! \brief Select The Timer counter detect phase. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulPhase is the counter detect phase of the Timer port.
//! Details please refer to \ref xTIMER_Counter_Pase_Type.
//! 
//! This function is to select The Timer counter detect phase.
//! 
//! The \e ulPhase parameter can be one of the values:
//! \b xTIMER_COUNTER_RISING, \b xTIMER_COUNTER_FALLING.
//! Details please refer to \ref xTIMER_Counter_Pase_Type_CoX.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
xTimerCounterDetectPhaseSelect(unsigned long ulBase, 
                               unsigned long ulChannel, unsigned long ulPhase)
{
    //
    // Disable the Channel: Reset the CCxE Bit
    //
    xHWREG(ulBase + TIMER_CCER) &= ~(TIMER_CCER_CC1E << ((ulChannel -1) * 4));
    
    //
    // Reset the polarity bit 
    //
    xHWREG(ulBase + TIMER_CCER) &= ~(TIMER_CCER_CC1P << ((ulChannel -1) * 4));

    //
    // Set the polarity bit
    //
    xHWREG(ulBase + TIMER_CCER) |= (ulPhase << ((ulChannel -1) * 4));

    //
    // Enable the channel
    //
    xHWREG(ulBase + TIMER_CCER) |= (TIMER_CCER_CC1E << ((ulChannel -1) * 4));
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
    // Disable the Channel: Reset the CCxE Bit
    //
    xHWREG(ulBase + TIMER_CCER) &= ~(TIMER_CCER_CC1E << ((ulChannel -1) * 4));
    
    //
    // Reset the polarity bit 
    //
    xHWREG(ulBase + TIMER_CCER) &= ~(TIMER_CCER_CC1P << ((ulChannel -1) * 4));

    //
    // Set the polarity bit
    //
    xHWREG(ulBase + TIMER_CCER) |= (ulEdge << ((ulChannel -1) * 4));

    //
    // Enable the channel
    //
    xHWREG(ulBase + TIMER_CCER) |= (TIMER_CCER_CC1E << ((ulChannel -1) * 4));
}

//*****************************************************************************
//
//! \brief Configure the TI1 as Input.
//!
//! \param ulBase is the base address of the Timer port, it can be  1 to 14 
//!        except 6 and 7 .
//! \param ulICPolarity is the Counter Mode.
//! \param ulICSelection is the counter reload value.
//! \param ulICFilter is the Prescaler value.
//!
//! The \e ulICPolarity parameter can be one of the values:
//! \b TIMER_ICPOL_RISING, \b TIMER_ICPOL_FALLING .
//!
//! The \e ulICSelection parameter can be one of the values:
//! \b TIMER_ICSEL_DIRTI, \b TIMER_ICSEL_INDIRTI, \b TIMER_ICSEL_TRC.
//!
//! The \e ulICFilter is a value between 0 to 15.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
static void 
TimerTI1Configure(unsigned long ulBase, unsigned long ulICPolarity, 
                  unsigned long ulICSelection, unsigned long ulICFilter)
{
    unsigned long ulTempccmr1 = 0, ulTempccer = 0;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE)); 
    xASSERT((ulICPolarity == TIMER_ICPOL_RISING) || 
            (ulICPolarity == TIMER_ICPOL_FALLING));    
    xASSERT((ulICSelection == TIMER_ICSEL_DIRTI) || 
            (ulICSelection == TIMER_ICSEL_INDIRTI) || 
            (ulICSelection == TIMER_ICSEL_TRC));    
    xASSERT((ulICFilter >= 0) && (ulICSelection <= 15));        
      
    //
    // Disable the Channel 1: Reset the CC1E Bit
    //
    xHWREG(ulBase + TIMER_CCER) &= ~TIMER_CCER_CC1E;
            
    ulTempccmr1 = xHWREG(ulBase + TIMER_CCMR1);
    ulTempccer = xHWREG(ulBase + TIMER_CCER);
            
    //
    // Select the Input and set the filter
    //
    ulTempccmr1 &= ~(TIMER_CCMR1_CC1S_M | TIMER_CCMR1_IC1F_M);
    ulTempccmr1 |= ulICSelection | (ulICFilter << 4);
            
    if((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
       (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
       (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE))
    {
        //
        // Select the Polarity and set the CC1E Bit
        //
        ulTempccer &= ~TIMER_CCER_CC1P;
        ulTempccer |= (ulICPolarity | TIMER_CCER_CC1E);
              
    }
    else
    {
        //
        // Select the Polarity and set the CC1E Bit
        //
        ulTempccer &= ~(TIMER_CCER_CC1P | TIMER_CCER_CC1NP);
        ulTempccer |= (ulICPolarity | TIMER_CCER_CC1E);
    }
    
    //
    // Write to TIMx CCMR1 and CCER registers
    //
    xHWREG(ulBase + TIMER_CCMR1) = ulTempccmr1;
    xHWREG(ulBase + TIMER_CCER) = ulTempccer;
}

//*****************************************************************************
//
//! \brief Configure the TI2 as Input.
//!
//! \param ulBase is the base address of the Timer port, it can be  1,2,3,4,5,8, 
//!        9, 12.
//! \param ulICPolarity is the Counter Mode.
//! \param ulICSelection is the counter reload value.
//! \param ulICFilter is the Prescaler value.
//!
//! The \e ulICPolarity parameter can be one of the values:
//! \b TIMER_ICPOL_RISING, \b TIMER_ICPOL_FALLING .
//!
//! The \e ulICSelection parameter can be one of the values:
//! \b TIMER_ICSEL_DIRTI, \b TIMER_ICSEL_INDIRTI, \b TIMER_ICSEL_TRC.
//!
//! The \e ulICFilter is a value between 0 to 15.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
static void 
TimerTI2Configure(unsigned long ulBase, unsigned long ulICPolarity, 
                  unsigned long ulICSelection, unsigned long ulICFilter)
{
    unsigned long ulTempccmr1 = 0, ulTempccer = 0, ulTemp;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE)); 
    xASSERT((ulICPolarity == TIMER_ICPOL_RISING) || 
            (ulICPolarity == TIMER_ICPOL_FALLING));    
    xASSERT((ulICSelection == TIMER_ICSEL_DIRTI) || 
            (ulICSelection == TIMER_ICSEL_INDIRTI) || 
            (ulICSelection == TIMER_ICSEL_TRC));    
    xASSERT((ulICFilter >= 0) && (ulICSelection <= 15));        
      
    //
    // Disable the Channel 1: Reset the CC1E Bit
    //
    xHWREG(ulBase + TIMER_CCER) &= ~TIMER_CCER_CC2E;
            
    ulTempccmr1 = xHWREG(ulBase + TIMER_CCMR1);
    ulTempccer = xHWREG(ulBase + TIMER_CCER);
    ulTemp = ulICPolarity << 4;
            
    //
    // Select the Input and set the filter
    //
    ulTempccmr1 &= ~(TIMER_CCMR1_CC2S_M | TIMER_CCMR1_IC2F_M);
    ulTempccmr1 |= ((ulICSelection << 8) | (ulICFilter << 12));
            
    if((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
       (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
       (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE))
    {
        //
        // Select the Polarity and set the CC2E Bit
        //
        ulTempccer &= ~TIMER_CCER_CC2P;
        ulTempccer |= (ulTemp | TIMER_CCER_CC2E);
              
    }
    else
    {
        //
        // Select the Polarity and set the CC2E Bit
        //
        ulTempccer &= ~(TIMER_CCER_CC2P | TIMER_CCER_CC2NP);
        ulTempccer |= (ulTemp | TIMER_CCER_CC2E);
    }
        
    //
    // Write to TIMx CCMR1 and CCER registers
    //
    xHWREG(ulBase + TIMER_CCMR1) = ulTempccmr1;
    xHWREG(ulBase + TIMER_CCER) = ulTempccer;
}

//*****************************************************************************
//
//! \brief Configure the TI3 as Input.
//!
//! \param ulBase is the base address of the Timer port, it can be  1,2,3,4,5,8, 
//!      
//! \param ulICPolarity is the Counter Mode.
//! \param ulICSelection is the counter reload value.
//! \param ulICFilter is the Prescaler value.
//!
//! The \e ulICPolarity parameter can be one of the values:
//! \b TIMER_ICPOL_RISING, \b TIMER_ICPOL_FALLING .
//!
//! The \e ulICSelection parameter can be one of the values:
//! \b TIMER_ICSEL_DIRTI, \b TIMER_ICSEL_INDIRTI, \b TIMER_ICSEL_TRC.
//!
//! The \e ulICFilter is a value between 0 to 15.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
static void 
TimerTI3Configure(unsigned long ulBase, unsigned long ulICPolarity, 
                  unsigned long ulICSelection, unsigned long ulICFilter)
{
    unsigned long ulTempccmr2 = 0, ulTempccer = 0, ulTemp;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE)); 
    xASSERT((ulICPolarity == TIMER_ICPOL_RISING) || 
            (ulICPolarity == TIMER_ICPOL_FALLING));    
    xASSERT((ulICSelection == TIMER_ICSEL_DIRTI) || 
            (ulICSelection == TIMER_ICSEL_INDIRTI) || 
            (ulICSelection == TIMER_ICSEL_TRC));    
    xASSERT((ulICFilter >= 0) && (ulICSelection <= 15));        
      
    //
    // Disable the Channel 1: Reset the CC1E Bit
    //
    xHWREG(ulBase + TIMER_CCER) &= ~TIMER_CCER_CC3E;
            
    ulTempccmr2 = xHWREG(ulBase + TIMER_CCMR2);
    ulTempccer = xHWREG(ulBase + TIMER_CCER);
    ulTemp = ulICPolarity << 8;
            
    //
    // Select the Input and set the filter
    //
    ulTempccmr2 &= ~(TIMER_CCMR2_CC3S_M | TIMER_CCMR2_IC3F_M);
    ulTempccmr2 |= (ulICSelection | (ulICFilter << 4));
            
    if((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
       (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
       (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE))
    {
        //
        // Select the Polarity and set the CC2E Bit
        //
        ulTempccer &= ~TIMER_CCER_CC3P;
        ulTempccer |= (ulTemp | TIMER_CCER_CC3E);
              
    }
    else
    {
        //
        // Select the Polarity and set the CC2E Bit
        //
        ulTempccer &= ~(TIMER_CCER_CC3P | TIMER_CCER_CC3NP);
        ulTempccer |= (ulTemp | TIMER_CCER_CC3E);
    }
    
    //
    // Write to TIMx CCMR1 and CCER registers
    //
    xHWREG(ulBase + TIMER_CCMR2) = ulTempccmr2;
    xHWREG(ulBase + TIMER_CCER) = ulTempccer;
}

//*****************************************************************************
//
//! \brief Configure the TI3 as Input.
//!
//! \param ulBase is the base address of the Timer port, it can be timer 1,2,3,4,5,8, 
//!      
//! \param ulICPolarity is the Counter Mode.
//! \param ulICSelection is the counter reload value.
//! \param ulICFilter is the Prescaler value.
//!
//! The \e ulICPolarity parameter can be one of the values:
//! \b TIMER_ICPOL_RISING, \b TIMER_ICPOL_FALLING .
//!
//! The \e ulICSelection parameter can be one of the values:
//! \b TIMER_ICSEL_DIRTI, \b TIMER_ICSEL_INDIRTI, \b TIMER_ICSEL_TRC.
//!
//! The \e ulICFilter is a value between 0 to 15.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
static void 
TimerTI4Configure(unsigned long ulBase, unsigned long ulICPolarity, 
                  unsigned long ulICSelection, unsigned long ulICFilter)
{
    unsigned long ulTempccmr2 = 0, ulTempccer = 0, ulTemp;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE)); 
    xASSERT((ulICPolarity == TIMER_ICPOL_RISING) || 
            (ulICPolarity == TIMER_ICPOL_FALLING));    
    xASSERT((ulICSelection == TIMER_ICSEL_DIRTI) || 
            (ulICSelection == TIMER_ICSEL_INDIRTI) || 
            (ulICSelection == TIMER_ICSEL_TRC));    
    xASSERT((ulICFilter >= 0) && (ulICSelection <= 15));        
      
    //
    // Disable the Channel 1: Reset the CC1E Bit
    //
    xHWREG(ulBase + TIMER_CCER) &= ~TIMER_CCER_CC4E;
        
    ulTempccmr2 = xHWREG(ulBase + TIMER_CCMR2);
    ulTempccer = xHWREG(ulBase + TIMER_CCER);
    ulTemp = ulICPolarity << 12;
        
    //
    // Select the Input and set the filter
    //
    ulTempccmr2 &= ~(TIMER_CCMR2_CC3S_M | TIMER_CCMR2_IC3F_M);
    ulTempccmr2 |= ((ulICSelection << 8) | (ulICFilter << 4));
        
    if((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
       (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
       (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE))
    {
        //
        // Select the Polarity and set the CC2E Bit
        //
        ulTempccer &= ~TIMER_CCER_CC4P;
        ulTempccer |= (ulTemp | TIMER_CCER_CC4E);
              
    }
    else
    {

    }
        
    //
    // Write to TIMx CCMR1 and CCER registers
    //
    xHWREG(ulBase + TIMER_CCMR2) = ulTempccmr2;
    xHWREG(ulBase + TIMER_CCER) = ulTempccer;
}

//*****************************************************************************
//
//! \brief Initializes the GPTM counter to reload, prescaler and counter mode. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulCountMode is the Counter Mode.
//! \param ulCRRValue is the counter reload value.
//! \param ulPrescaler is the Prescaler value.
//! \param ulCLKDiv is the division ratio between the timer clock frequency and 
//!        sampling clock used by the digital filters.
//! \param ulRepCnt is the repetition counter value.
//!
//! The \e ulCountMode parameter can be one of the values:
//! \b TIMER_CNT_MODE_UP, \b TIMER_CNT_MODE_CA1, \b TIMER_CNT_MODE_CA2 and
//! \b TIMER_CNT_MODE_CA3, \b TIMER_CNT_MODE_DOWN.
//!
//! The \e ulCRRValue is a value between 0 to 65535.
//! 
//! The \e ulPrescaler is a value between 0 to 65535.
//!
//! The \e ulCLKDiv parameter can be one of the values:
//! \b TIMER_CLKDIV_0, \b TIMER_CLKDIV_2, \b TIMER_CLKDIV_4.
//!
//! The \e ulPrescaler is a value between 0 to 255.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerBaseConfigure(unsigned long ulBase, unsigned long ulCountMode, 
                   unsigned long ulCRRValue, unsigned long ulPrescaler, 
                   unsigned long ulCLKDiv, unsigned long ulRepCnt)
{
    unsigned long ulTempCR1;
      
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) ||
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE)); 
    xASSERT((ulCountMode == TIMER_CNT_MODE_UP) || 
            (ulCountMode == TIMER_CNT_MODE_CA1) || 
            (ulCountMode == TIMER_CNT_MODE_CA2) ||
            (ulCountMode == TIMER_CNT_MODE_CA3) ||
            (ulCountMode == TIMER_CNT_MODE_DOWN));
    xASSERT((ulCRRValue >= 0) && (ulCRRValue <= 65535));
    xASSERT((ulPrescaler >= 0) && (ulPrescaler <= 65535));
    xASSERT((ulCLKDiv == TIMER_CLKDIV_0) || 
            (ulCLKDiv == TIMER_CLKDIV_2) ||
            (ulCLKDiv == TIMER_CLKDIV_4));
    xASSERT((ulRepCnt >= 0) && (ulRepCnt <= 255))                
    
    ulTempCR1 = xHWREG(ulBase + TIMER_CR1);
                
    if((ulBase == TIM1_BASE) || (ulBase == TIM8_BASE) ||
       (ulBase == TIM2_BASE) || (ulBase == TIM3_BASE) ||
       (ulBase == TIM4_BASE) || (ulBase == TIM5_BASE))
    {
        //
        // Select the Counter Mode
        //
        ulTempCR1 &= ~(TIMER_CR1_DIR | TIMER_CR1_CMS_M);
        xHWREG(ulBase + TIMER_CR1) = ulTempCR1;
        ulTempCR1 |= ulCountMode;
    }
        
    if((ulBase != TIM6_BASE) && (ulBase != TIM7_BASE))
    {
        //
        // Set the clock division
        //
        ulTempCR1 &= ~TIMER_CR1_CKD_M;
        ulTempCR1 |= ulCLKDiv;            
    }
        
    xHWREG(ulBase + TIMER_CR1) = ulTempCR1;
        
    //
    // Set the Autoreload value
    //
    xHWREG(ulBase + TIMER_ARR) = ulCRRValue;
    
    //
    // Set the Prescaler value
    //
    xHWREG(ulBase + TIMER_PSC) = ulPrescaler;
     
    if((ulBase == TIM1_BASE) || (ulBase == TIM8_BASE))
    {
        //
        // Set the Repetition Counter value
        //
        xHWREG(ulBase + TIMER_RCR) = ulRepCnt;        
    }

    //
    // Generate an update event to reload the Prescaler and the Repetition 
    // counter values immediately
    //
    xHWREG(ulBase + TIMER_EGR) = TIMER_PSC_RLD_IMMEDIATE;
}     

//*****************************************************************************
//
//! \brief Initializes the TIMERx channel 1 output. 
//!
//! \param ulBase is the base address of the Timer port, it can be  1 to 14 
//!        except 6 and 7 .
//! \param ulOutputMode is Channel output compare mode selection.
//! \param ulOutCompare is channel Capture Compare Register value.
//! \param ulOCCfg is the channel output compare state and polarity configuration.
//! \param ulOCNCfg is the channel output compare state and polarity configuration.
//! \param ulOCIdleCfg is the channel output compare pin state during idle state.
//!
//! The \e ulOutputMode parameter can be one of the values:
//! \b TIMER_OCMODE_TIMING, \b TIMER_OCMODE_ACTIVE, \b TIMER_OCMODE_INACTIVE,
//! \b TIMER_OCMODE_TOGGLE, \b TIMER_OCMODE_FINACTIVE, \b TIMER_OCMODE_FACTIVE 
//!
//! The \e ulOCompare is a value between 0 ~ 65535.
//!
//! The \e ulOCCfg parameter is the logic OR of the following values:
//! The output compare state is chosen with one of the following value:
//! \b TIMER_OP_STATE_DIS, \b TIMER_OP_STATE_EN .
//! The output compare polarity is chosen with one of the following value:
//! \b TIMER_OP_POL_HIGH, \b TIMER_OP_POL_LOW .
//! 
//! The \e ulOCNCfg parameter is the logic OR of the following values:
//! The output compare N state is chosen with one of the following value:
//! \b TIMER_OP_N_STATE_DIS, \b TIMER_OP_N_STATE_EN .
//! The output compare N polarity is chosen with one of the following value:
//! \b TIMER_OP_N_POL_HIGH, \b TIMER_OP_N_POL_LOW .
//! 
//! The \e ulOCIdleCfg parameter is the logic OR of the following values:
//! The Output Compare Idle State is chosen with one of the following value:
//! \b TIMER_OCIDLESTATE_SET, \b TIMER_OCIDLESTATE_RESET .
//! The output compare N polarity is chosen with one of the following value:
//! \b TIMER_OCNIDLESTATE_SET, \b TIMER_OCNIDLESTATE_RESET .
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC1Configure(unsigned long ulBase, unsigned long ulOutputMode, 
                       unsigned long ulOCompare,unsigned long ulOCCfg, 
                       unsigned long ulOCNCfg, unsigned long ulOCIdleCfg)
{
    unsigned long ulTempccer = 0, ulTempccmrx = 0, ulTempcr2 = 0;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE)); 
    xASSERT((ulOutputMode == TIMER_OCMODE_TIMING) ||
            (ulOutputMode == TIMER_OCMODE_ACTIVE) ||
            (ulOutputMode == TIMER_OCMODE_INACTIVE) || 
            (ulOutputMode == TIMER_OCMODE_TOGGLE) ||
            (ulOutputMode == TIMER_OCMODE_FINACTIVE) ||
            (ulOutputMode == TIMER_OCMODE_FACTIVE));
    xASSERT((ulOCompare >= 0) && (ulOCompare <= 65535));    
    xASSERT((ulOCCfg == TIMER_OP_STATE_DIS | TIMER_OP_POL_HIGH) ||
            (ulOCCfg == TIMER_OP_STATE_DIS | TIMER_OP_POL_LOW) || 
            (ulOCCfg == TIMER_OP_STATE_EN | TIMER_OP_POL_LOW) ||
            (ulOCCfg == TIMER_OP_STATE_EN | TIMER_OP_POL_HIGH));
    xASSERT((ulOCNCfg == TIMER_OP_N_STATE_DIS | TIMER_OP_N_POL_HIGH) ||
            (ulOCNCfg == TIMER_OP_N_STATE_DIS | TIMER_OP_N_POL_LOW) || 
            (ulOCNCfg == TIMER_OP_N_STATE_EN | TIMER_OP_N_POL_LOW) ||
            (ulOCNCfg == TIMER_OP_N_STATE_EN | TIMER_OP_N_POL_HIGH));
    xASSERT((ulOCIdleCfg == TIMER_OCIDLESTATE_SET | TIMER_OCNIDLESTATE_SET) ||
            (ulOCIdleCfg == TIMER_OCIDLESTATE_SET | TIMER_OCNIDLESTATE_RESET) ||
            (ulOCIdleCfg == TIMER_OCIDLESTATE_RESET | TIMER_OCNIDLESTATE_RESET) ||
            (ulOCIdleCfg == TIMER_OCIDLESTATE_RESET | TIMER_OCNIDLESTATE_SET));        
    
    //
    // Disable the channel
    //
    xHWREG(ulBase + TIMER_CCER) &= ~TIMER_CCER_CC1E;

    //
    // Get the TIMx CCER register value
    //
    ulTempccer = xHWREG(ulBase + TIMER_CCER);
    
    //
    // Get the TIMx CR2 register value
    //
    ulTempcr2 = xHWREG(ulBase + TIMER_CR2);
        
    //
    // Get the TIMx CCMR1 register value
    //
    ulTempccmrx = xHWREG(ulBase + TIMER_CCMR1);
    
    //
    // Set the Output Compare Mode Bits
    //
    ulTempccmrx &= ~(TIMER_CCMR1_OC1M_M | TIMER_CCMR1_CC1S_M);
    ulTempccmrx |= ulOutputMode;
        
    //
    // Set the Output Compare Polarity
    //
    ulTempccer &= ~TIMER_CCER_CC1P;
    ulTempccer |= (ulOCCfg & TIMER_CCER_CC1P);
        
    //
    // Set the Output State
    //
    ulTempccer |= (ulOCCfg & TIMER_CCER_CC1E);
        
    if((ulBase == TIM1_BASE) || (ulBase == TIM8_BASE))
    {   
        //
        // Set the Output N Polarity
        //
        ulTempccer &= ~TIMER_CCER_CC1NP;
        ulTempccer |= (ulOCNCfg & TIMER_CCER_CC1NP);

        //
        // Set the Output N State
        //
        ulTempccer &= ~TIMER_CCER_CC1NE;
        ulTempccer |= (ulOCNCfg & TIMER_CCER_CC1NE);    
            
        //
        // Set the Output Idle/ N Idle state
        //
        ulTempcr2 &= ~(TIMER_CR2_OIS1 | TIMER_CR2_OIS1N);
        ulTempcr2 |= (ulOCIdleCfg & (TIMER_CR2_OIS1 | TIMER_CR2_OIS1N));
    }
        
    //
    // Write to TIMx CR2
    //
    xHWREG(ulBase + TIMER_CR2) = ulTempcr2;
    
    //
    // Write to TIMx CCMR1
    //
    xHWREG(ulBase + TIMER_CCMR1) = ulTempccmrx;
        
    //
    // Set the Capture Compare Register value
    //
    xHWREG(ulBase + TIMER_CCR1) = ulOCompare;
        
    //
    // Write to TIMx CCER
    //
    xHWREG(ulBase + TIMER_CCER) = ulTempccer;
        
}

//*****************************************************************************
//
//! \brief Initializes the TIMERx channel 2 output. 
//!
//! \param ulBase is the base address of the Timer port, it can be 1, 2, 3, 4, 
//!        5, 8, 9, 12.
//! \param ulOutputMode is Channel output compare mode selection.
//! \param ulOutCompare is channel Capture Compare Register value.
//! \param ulOCCfg is the channel output compare state and polarity configuration.
//! \param ulOCNCfg is the channel output compare state and polarity configuration.
//! \param ulOCIdleCfg is the channel output compare pin state during idle state.
//!
//! The \e ulOutputMode parameter can be one of the values:
//! \b TIMER_OCMODE_TIMING, \b TIMER_OCMODE_ACTIVE, \b TIMER_OCMODE_INACTIVE,
//! \b TIMER_OCMODE_TOGGLE, \b TIMER_OCMODE_FINACTIVE, \b TIMER_OCMODE_FACTIVE 
//!
//! The \e ulOCompare is a value between 0 ~ 65535.
//!
//! The \e ulOCCfg parameter is the logic OR of the following values:
//! The output compare state is chosen with one of the following value:
//! \b TIMER_OP_STATE_DIS, \b TIMER_OP_STATE_EN .
//! The output compare polarity is chosen with one of the following value:
//! \b TIMER_OP_POL_HIGH, \b TIMER_OP_POL_LOW .
//! 
//! The \e ulOCNCfg parameter is the logic OR of the following values:
//! The output compare N state is chosen with one of the following value:
//! \b TIMER_OP_N_STATE_DIS, \b TIMER_OP_N_STATE_EN .
//! The output compare N polarity is chosen with one of the following value:
//! \b TIMER_OP_N_POL_HIGH, \b TIMER_OP_N_POL_LOW .
//! 
//! The \e ulOCIdleCfg parameter is the logic OR of the following values:
//! The Output Compare Idle State is chosen with one of the following value:
//! \b TIMER_OCIDLESTATE_SET, \b TIMER_OCIDLESTATE_RESET .
//! The output compare N polarity is chosen with one of the following value:
//! \b TIMER_OCNIDLESTATE_SET, \b TIMER_OCNIDLESTATE_RESET .
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void TimerOC2Configure(unsigned long ulBase, unsigned long ulOutputMode, 
                       unsigned long ulOCompare,unsigned long ulOCCfg, 
                       unsigned long ulOCNCfg, unsigned long ulOCIdleCfg)
{
    unsigned long ulTempccer = 0, ulTempccmrx = 0, ulTempcr2 = 0;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE)); 
    xASSERT((ulOutputMode == TIMER_OCMODE_TIMING) ||
            (ulOutputMode == TIMER_OCMODE_ACTIVE) ||
            (ulOutputMode == TIMER_OCMODE_INACTIVE) || 
            (ulOutputMode == TIMER_OCMODE_TOGGLE) ||
            (ulOutputMode == TIMER_OCMODE_FINACTIVE) ||
            (ulOutputMode == TIMER_OCMODE_FACTIVE));
    xASSERT((ulOCompare >= 0) && (ulOCompare <= 65535));    
    xASSERT((ulOCCfg == TIMER_OP_STATE_DIS | TIMER_OP_POL_HIGH) ||
            (ulOCCfg == TIMER_OP_STATE_DIS | TIMER_OP_POL_LOW) || 
            (ulOCCfg == TIMER_OP_STATE_EN | TIMER_OP_POL_LOW) ||
            (ulOCCfg == TIMER_OP_STATE_EN | TIMER_OP_POL_HIGH));
    xASSERT((ulOCNCfg == TIMER_OP_N_STATE_DIS | TIMER_OP_N_POL_HIGH) ||
            (ulOCNCfg == TIMER_OP_N_STATE_DIS | TIMER_OP_N_POL_LOW) || 
            (ulOCNCfg == TIMER_OP_N_STATE_EN | TIMER_OP_N_POL_LOW) ||
            (ulOCNCfg == TIMER_OP_N_STATE_EN | TIMER_OP_N_POL_HIGH));
    xASSERT((ulOCIdleCfg == TIMER_OCIDLESTATE_SET | TIMER_OCNIDLESTATE_SET) ||
            (ulOCIdleCfg == TIMER_OCIDLESTATE_SET | TIMER_OCNIDLESTATE_RESET) ||
            (ulOCIdleCfg == TIMER_OCIDLESTATE_RESET | TIMER_OCNIDLESTATE_RESET) ||
            (ulOCIdleCfg == TIMER_OCIDLESTATE_RESET | TIMER_OCNIDLESTATE_SET));        
    
    //
    // Disable the channel
    //
    xHWREG(ulBase + TIMER_CCER) &= ~TIMER_CCER_CC2E;

    //
    // Get the TIMx CCER register value
    //
    ulTempccer = xHWREG(ulBase + TIMER_CCER);
        
    //
    // Get the TIMx CR2 register value
    //
    ulTempcr2 = xHWREG(ulBase + TIMER_CR2);
        
    //
    // Get the TIMx CCMR1 register value
    //
    ulTempccmrx = xHWREG(ulBase + TIMER_CCMR1);
        
    //
    // Set the Output Compare Mode Bits
    //
    ulTempccmrx &= ~(TIMER_CCMR1_OC2M_M | TIMER_CCMR1_CC2S_M);
    ulTempccmrx |= (ulOutputMode << 8);
        
    //
    // Set the Output Compare Polarity
    //
    ulTempccer &= ~TIMER_CCER_CC2P;
    ulTempccer |= ((ulOCCfg << 4) & TIMER_CCER_CC2P);
        
    //
    // Set the Output State
    //
    ulTempccer |= ((ulOCCfg << 4) & TIMER_CCER_CC2E);
        
    if((ulBase == TIM1_BASE) || (ulBase == TIM8_BASE))
    {   
        //
        // Set the Output N Polarity
        //
        ulTempccer &= ~TIMER_CCER_CC2NP;
        ulTempccer |= ((ulOCNCfg << 4) & TIMER_CCER_CC2NP);

        //
        // Set the Output N State
        //
        ulTempccer &= ~TIMER_CCER_CC2NE;
        ulTempccer |= ((ulOCNCfg << 4) & TIMER_CCER_CC2NE);    
            
        //
        // Set the Output Idle/ N Idle state
        //
        ulTempcr2 &= ~(TIMER_CR2_OIS2 | TIMER_CR2_OIS2N);
        ulTempcr2 |= ((ulOCIdleCfg << 2) & (TIMER_CR2_OIS2 | TIMER_CR2_OIS2N));
    }
        
    //
    // Write to TIMx CR2
    //
    xHWREG(ulBase + TIMER_CR2) = ulTempcr2;
        
    //
    // Write to TIMx CCMR1
    //
    xHWREG(ulBase + TIMER_CCMR1) = ulTempccmrx;
        
    //
    // Set the Capture Compare Register value
    //
    xHWREG(ulBase + TIMER_CCR2) = ulOCompare;
        
    //
    // Write to TIMx CCER
    //
    xHWREG(ulBase + TIMER_CCER) = ulTempccer;
        
}

//*****************************************************************************
//
//! \brief Initializes the TIMERx channel 3 output. 
//!
//! \param ulBase is the base address of the Timer port, it can be  1, 2, 3, 4,
//!        5, 8.
//! \param ulOutputMode is Channel output compare mode selection.
//! \param ulOutCompare is channel Capture Compare Register value.
//! \param ulOCCfg is the channel output compare state and polarity configuration.
//! \param ulOCNCfg is the channel output compare state and polarity configuration.
//! \param ulOCIdleCfg is the channel output compare pin state during idle state.
//!
//! The \e ulOutputMode parameter can be one of the values:
//! \b TIMER_OCMODE_TIMING, \b TIMER_OCMODE_ACTIVE, \b TIMER_OCMODE_INACTIVE,
//! \b TIMER_OCMODE_TOGGLE, \b TIMER_OCMODE_FINACTIVE, \b TIMER_OCMODE_FACTIVE 
//!
//! The \e ulOCompare is a value between 0 ~ 65535.
//!
//! The \e ulOCCfg parameter is the logic OR of the following values:
//! The output compare state is chosen with one of the following value:
//! \b TIMER_OP_STATE_DIS, \b TIMER_OP_STATE_EN .
//! The output compare polarity is chosen with one of the following value:
//! \b TIMER_OP_POL_HIGH, \b TIMER_OP_POL_LOW .
//! 
//! The \e ulOCNCfg parameter is the logic OR of the following values:
//! The output compare N state is chosen with one of the following value:
//! \b TIMER_OP_N_STATE_DIS, \b TIMER_OP_N_STATE_EN .
//! The output compare N polarity is chosen with one of the following value:
//! \b TIMER_OP_N_POL_HIGH, \b TIMER_OP_N_POL_LOW .
//! 
//! The \e ulOCIdleCfg parameter is the logic OR of the following values:
//! The Output Compare Idle State is chosen with one of the following value:
//! \b TIMER_OCIDLESTATE_SET, \b TIMER_OCIDLESTATE_RESET .
//! The output compare N polarity is chosen with one of the following value:
//! \b TIMER_OCNIDLESTATE_SET, \b TIMER_OCNIDLESTATE_RESET .
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC3Configure(unsigned long ulBase, unsigned long ulOutputMode, 
                  unsigned long ulOCompare,unsigned long ulOCCfg, 
                  unsigned long ulOCNCfg, unsigned long ulOCIdleCfg)
{
      unsigned long ulTempccer = 0, ulTempccmrx = 0, ulTempcr2 = 0;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE)); 
    xASSERT((ulOutputMode == TIMER_OCMODE_TIMING) ||
            (ulOutputMode == TIMER_OCMODE_ACTIVE) ||
            (ulOutputMode == TIMER_OCMODE_INACTIVE) || 
            (ulOutputMode == TIMER_OCMODE_TOGGLE) ||
            (ulOutputMode == TIMER_OCMODE_FINACTIVE) ||
            (ulOutputMode == TIMER_OCMODE_FACTIVE));
    xASSERT((ulOCompare >= 0) && (ulOCompare <= 65535));    
    xASSERT((ulOCCfg == TIMER_OP_STATE_DIS | TIMER_OP_POL_HIGH) ||
            (ulOCCfg == TIMER_OP_STATE_DIS | TIMER_OP_POL_LOW) || 
            (ulOCCfg == TIMER_OP_STATE_EN | TIMER_OP_POL_LOW) ||
            (ulOCCfg == TIMER_OP_STATE_EN | TIMER_OP_POL_HIGH));
    xASSERT((ulOCNCfg == TIMER_OP_N_STATE_DIS | TIMER_OP_N_POL_HIGH) ||
            (ulOCNCfg == TIMER_OP_N_STATE_DIS | TIMER_OP_N_POL_LOW) || 
            (ulOCNCfg == TIMER_OP_N_STATE_EN | TIMER_OP_N_POL_LOW) ||
            (ulOCNCfg == TIMER_OP_N_STATE_EN | TIMER_OP_N_POL_HIGH));
    xASSERT((ulOCIdleCfg == TIMER_OCIDLESTATE_SET | TIMER_OCNIDLESTATE_SET) ||
            (ulOCIdleCfg == TIMER_OCIDLESTATE_SET | TIMER_OCNIDLESTATE_RESET) ||
            (ulOCIdleCfg == TIMER_OCIDLESTATE_RESET | TIMER_OCNIDLESTATE_RESET) ||
            (ulOCIdleCfg == TIMER_OCIDLESTATE_RESET | TIMER_OCNIDLESTATE_SET));        
    
    //
    // Disable the channel
    //
    xHWREG(ulBase + TIMER_CCER) &= ~TIMER_CCER_CC3E;

    //
    // Get the TIMx CCER register value
    //
    ulTempccer = xHWREG(ulBase + TIMER_CCER);
    
    //
    // Get the TIMx CR2 register value
    //
    ulTempcr2 = xHWREG(ulBase + TIMER_CR2);
    
    //
    // Get the TIMx CCMR1 register value
    //
    ulTempccmrx = xHWREG(ulBase + TIMER_CCMR2);
    
    //
    // Set the Output Compare Mode Bits
    //
    ulTempccmrx &= ~(TIMER_CCMR2_OC3M_M | TIMER_CCMR2_CC3S_M);
    ulTempccmrx |= ulOutputMode;
    
    //
    // Set the Output Compare Polarity
    //
    ulTempccer &= ~TIMER_CCER_CC3P;
    ulTempccer |= ((ulOCCfg << 8) & TIMER_CCER_CC3P);
    
    //
    // Set the Output State
    //
    ulTempccer |= ((ulOCCfg << 8) & TIMER_CCER_CC3E);
    
    if((ulBase == TIM1_BASE) || (ulBase == TIM8_BASE))
    {   
        //
        // Set the Output N Polarity
        //
        ulTempccer &= ~TIMER_CCER_CC3NP;
        ulTempccer |= ((ulOCNCfg << 8) & TIMER_CCER_CC3NP);

        //
        // Set the Output N State
        //
        ulTempccer &= ~TIMER_CCER_CC3NE;
        ulTempccer |= ((ulOCNCfg << 8) & TIMER_CCER_CC3NE);    
        
        //
        // Set the Output Idle/ N Idle state
        //
        ulTempcr2 &= ~(TIMER_CR2_OIS3 | TIMER_CR2_OIS3N);
        ulTempcr2 |= ((ulOCIdleCfg << 4) & (TIMER_CR2_OIS3 | TIMER_CR2_OIS3N));
    }
        
    //
    // Write to TIMx CR2
    //
    xHWREG(ulBase + TIMER_CR2) = ulTempcr2;
        
    //
    // Write to TIMx CCMR1
    //
    xHWREG(ulBase + TIMER_CCMR2) = ulTempccmrx;
        
    //
    // Set the Capture Compare Register value
    //
    xHWREG(ulBase + TIMER_CCR3) = ulOCompare;
        
    //
    // Write to TIMx CCER
    //
    xHWREG(ulBase + TIMER_CCER) = ulTempccer;
        
}

//*****************************************************************************
//
//! \brief Initializes the TIMERx channel 4 output. 
//!
//! \param ulBase is the base address of the Timer port, it can be 1, 2, 3, 4, 
//!        5, 8.
//! \param ulOutputMode is Channel output compare mode selection.
//! \param ulOutCompare is channel Capture Compare Register value.
//! \param ulOCCfg is the channel output compare state and polarity configuration.
//! \param ulOCNCfg is the channel output compare state and polarity configuration.
//! \param ulOCIdleCfg is the channel output compare pin state during idle state.
//!
//! The \e ulOutputMode parameter can be one of the values:
//! \b TIMER_OCMODE_TIMING, \b TIMER_OCMODE_ACTIVE, \b TIMER_OCMODE_INACTIVE,
//! \b TIMER_OCMODE_TOGGLE, \b TIMER_OCMODE_FINACTIVE, \b TIMER_OCMODE_FACTIVE 
//!
//! The \e ulOCompare is a value between 0 ~ 65535.
//!
//! The \e ulOCCfg parameter is the logic OR of the following values:
//! The output compare state is chosen with one of the following value:
//! \b TIMER_OP_STATE_DIS, \b TIMER_OP_STATE_EN .
//! The output compare polarity is chosen with one of the following value:
//! \b TIMER_OP_POL_HIGH, \b TIMER_OP_POL_LOW .
//! 
//! The \e ulOCNCfg parameter is the logic OR of the following values:
//! The output compare N state is chosen with one of the following value:
//! \b TIMER_OP_N_STATE_DIS, \b TIMER_OP_N_STATE_EN .
//! The output compare N polarity is chosen with one of the following value:
//! \b TIMER_OP_N_POL_HIGH, \b TIMER_OP_N_POL_LOW .
//! 
//! The \e ulOCIdleCfg parameter is the logic OR of the following values:
//! The Output Compare Idle State is chosen with one of the following value:
//! \b TIMER_OCIDLESTATE_SET, \b TIMER_OCIDLESTATE_RESET .
//! The output compare N polarity is chosen with one of the following value:
//! \b TIMER_OCNIDLESTATE_SET, \b TIMER_OCNIDLESTATE_RESET .
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC4Configure(unsigned long ulBase, unsigned long ulOutputMode, 
                  unsigned long ulOCompare,unsigned long ulOCCfg, 
                  unsigned long ulOCNCfg, unsigned long ulOCIdleCfg)
{
    unsigned long ulTempccer = 0, ulTempccmrx = 0, ulTempcr2 = 0;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE)); 
    xASSERT((ulOutputMode == TIMER_OCMODE_TIMING) ||
            (ulOutputMode == TIMER_OCMODE_ACTIVE) ||
            (ulOutputMode == TIMER_OCMODE_INACTIVE) || 
            (ulOutputMode == TIMER_OCMODE_TOGGLE) ||
            (ulOutputMode == TIMER_OCMODE_FINACTIVE) ||
            (ulOutputMode == TIMER_OCMODE_FACTIVE));
    xASSERT((ulOCompare >= 0) && (ulOCompare <= 65535));    
    xASSERT((ulOCCfg == TIMER_OP_STATE_DIS | TIMER_OP_POL_HIGH) ||
            (ulOCCfg == TIMER_OP_STATE_DIS | TIMER_OP_POL_LOW) || 
            (ulOCCfg == TIMER_OP_STATE_EN | TIMER_OP_POL_LOW) ||
            (ulOCCfg == TIMER_OP_STATE_EN | TIMER_OP_POL_HIGH));
    xASSERT((ulOCNCfg == TIMER_OP_N_STATE_DIS | TIMER_OP_N_POL_HIGH) ||
            (ulOCNCfg == TIMER_OP_N_STATE_DIS | TIMER_OP_N_POL_LOW) || 
            (ulOCNCfg == TIMER_OP_N_STATE_EN | TIMER_OP_N_POL_LOW) ||
            (ulOCNCfg == TIMER_OP_N_STATE_EN | TIMER_OP_N_POL_HIGH));
    xASSERT((ulOCIdleCfg == TIMER_OCIDLESTATE_SET | TIMER_OCNIDLESTATE_SET) ||
            (ulOCIdleCfg == TIMER_OCIDLESTATE_SET | TIMER_OCNIDLESTATE_RESET) ||
            (ulOCIdleCfg == TIMER_OCIDLESTATE_RESET | TIMER_OCNIDLESTATE_RESET) ||
            (ulOCIdleCfg == TIMER_OCIDLESTATE_RESET | TIMER_OCNIDLESTATE_SET));        
    
    //
    // Disable the channel
    //
    xHWREG(ulBase + TIMER_CCER) &= ~TIMER_CCER_CC4E;

    //
    // Get the TIMx CCER register value
    //
    ulTempccer = xHWREG(ulBase + TIMER_CCER);
        
    //
    // Get the TIMx CR2 register value
    //
    ulTempcr2 = xHWREG(ulBase + TIMER_CR2);
        
    //
    // Get the TIMx CCMR2 register value
    //
    ulTempccmrx = xHWREG(ulBase + TIMER_CCMR2);
        
    //
    // Set the Output Compare Mode Bits
    //
    ulTempccmrx &= ~(TIMER_CCMR2_OC4M_M | TIMER_CCMR2_CC4S_M);
    ulTempccmrx |= (ulOutputMode << 8);
        
    //
    // Set the Output Compare Polarity
    //
    ulTempccer &= ~TIMER_CCER_CC4P;
    ulTempccer |= ((ulOCCfg << 12) & TIMER_CCER_CC4P);
        
    //
    // Set the Output State
    //
    ulTempccer |= ((ulOCCfg << 12) & TIMER_CCER_CC2E);
        
    if((ulBase == TIM1_BASE) || (ulBase == TIM8_BASE))
    {   
            
        //
        // Set the Output Idle/ N Idle state
        //
        ulTempcr2 &= ~(TIMER_CR2_OIS4);
        ulTempcr2 |= ((ulOCIdleCfg << 6) & (TIMER_CR2_OIS4));
    }
        
    //
    // Write to TIMx CR2
    //
    xHWREG(ulBase + TIMER_CR2) = ulTempcr2;
        
    //
    // Write to TIMx CCMR1
    //
    xHWREG(ulBase + TIMER_CCMR2) = ulTempccmrx;
        
    //
    // Set the Capture Compare Register value
    //
    xHWREG(ulBase + TIMER_CCR4) = ulOCompare;
        
    //
    // Write to TIMx CCER
    //
    xHWREG(ulBase + TIMER_CCER) = ulTempccer;
        
}

//*****************************************************************************
//
//! \brief Sets the Timer x Input Capture 1 prescaler.
//!
//! \param ulBase is the base address of the Timer port.it can be 1 to 17 
//!        except 6 and 7 .
//! \param ulPrescaler is Channel Capture prescaler.
//!
//! The \e ulPrescaler parameter can be one of the values:
//! \b TIMER_ICPSC_DIV1, \b TIMER_ICPSC_DIV2, \b TIMER_ICPSC_DIV4, 
//! \b TIMER_ICPSC_DIV8.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerIC1PrescalerSet(unsigned long ulBase, unsigned long ulPrescaler)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE)); 
    xASSERT((ulPrescaler == TIMER_ICPSC_DIV1) || 
            (ulPrescaler == TIMER_ICPSC_DIV2) ||
            (ulPrescaler == TIMER_ICPSC_DIV4) ||
            (ulPrescaler == TIMER_ICPSC_DIV8));
    
    //
    // Reset the IC1PSC Bits
    //
    xHWREG(ulBase + TIMER_CCMR1) &= ~TIMER_CCMR1_IC1PSC_M;
    
    //
    // Set the IC1PSC value
    //
    xHWREG(ulBase + TIMER_CCMR1) |= ulPrescaler;
}

//*****************************************************************************
//
//! \brief Sets the Timer x Input Capture 2 prescaler.
//!
//! \param ulBase is the base address of the Timer port.it can be 1, 2, 3, 4, 5, 
//!        8, 9, 12 .
//! \param ulPrescaler is Channel Capture prescaler.
//!
//! The \e ulPrescaler parameter can be one of the values:
//! \b TIMER_ICPSC_DIV1, \b TIMER_ICPSC_DIV2, \b TIMER_ICPSC_DIV4, 
//! \b TIMER_ICPSC_DIV8.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerIC2PrescalerSet(unsigned long ulBase, unsigned long ulPrescaler)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) ||
              (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE)); 
    xASSERT((ulPrescaler == TIMER_ICPSC_DIV1) || 
            (ulPrescaler == TIMER_ICPSC_DIV2) ||
            (ulPrescaler == TIMER_ICPSC_DIV4) ||
            (ulPrescaler == TIMER_ICPSC_DIV8));
    
    //
    // Reset the IC2PSC Bits
    //
    xHWREG(ulBase + TIMER_CCMR1) &= ~TIMER_CCMR1_IC2PSC_M;
    
    //
    // Set the IC2PSC value
    //
    xHWREG(ulBase + TIMER_CCMR1) |= (ulPrescaler << 8) ;
}

//*****************************************************************************
//
//! \brief Sets the Timer x Input Capture 3 prescaler.
//!
//! \param ulBase is the base address of the Timer port.it can be 1, 2, 3, 4, 5, 
//!        8 .
//! \param ulPrescaler is Channel Capture prescaler.
//!
//! The \e ulPrescaler parameter can be one of the values:
//! \b TIMER_ICPSC_DIV1, \b TIMER_ICPSC_DIV2, \b TIMER_ICPSC_DIV4, 
//! \b TIMER_ICPSC_DIV8.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerIC3PrescalerSet(unsigned long ulBase, unsigned long ulPrescaler)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE)); 
    xASSERT((ulPrescaler == TIMER_ICPSC_DIV1) || 
            (ulPrescaler == TIMER_ICPSC_DIV2) ||
            (ulPrescaler == TIMER_ICPSC_DIV4) ||
            (ulPrescaler == TIMER_ICPSC_DIV8));
    
    //
    // Reset the IC3PSC Bits
    //
    xHWREG(ulBase + TIMER_CCMR2) &= ~TIMER_CCMR2_IC3PSC_M;
    
    //
    // Set the IC3PSC value
    //
    xHWREG(ulBase + TIMER_CCMR2) |= ulPrescaler;
}

//*****************************************************************************
//
//! \brief Sets the Timer x Input Capture 4 prescaler.
//!
//! \param ulBase is the base address of the Timer port.it can be 1, 2, 3, 4, 5, 
//!        8 .
//! \param ulPrescaler is Channel Capture prescaler.
//!
//! The \e ulPrescaler parameter can be one of the values:
//! \b TIMER_ICPSC_DIV1, \b TIMER_ICPSC_DIV2, \b TIMER_ICPSC_DIV4, 
//! \b TIMER_ICPSC_DIV8.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerIC4PrescalerSet(unsigned long ulBase, unsigned long ulPrescaler)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
              (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
              (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE)); 
      xASSERT((ulPrescaler == TIMER_ICPSC_DIV1) || 
              (ulPrescaler == TIMER_ICPSC_DIV2) ||
              (ulPrescaler == TIMER_ICPSC_DIV4) ||
              (ulPrescaler == TIMER_ICPSC_DIV8));
    
      //
      // Reset the IC4PSC Bits
      //
      xHWREG(ulBase + TIMER_CCMR2) &= ~TIMER_CCMR2_IC4PSC_M;
    
      //
      // Set the IC4PSC value
      //
      xHWREG(ulBase + TIMER_CCMR2) |= (ulPrescaler << 8);
}

//*****************************************************************************
//
//! \brief Configure the TI1 as Input.
//!
//! \param ulBase is the base address of the Timer port, it can be  1 to 14 
//!        except 6 and 7 .
//! \param ulChannel is the select fo timer channel. 
//! \param ulICPolarity is the Counter Mode.
//! \param ulICSelection is the counter reload value.
//! \param ulPrescaler is Channel Capture prescaler.
//! \param ulICFilter is the Prescaler value.
//!
//! The \e ulChannel parameter can be one of the values:
//! \b TIMER_CH_1, \b TIMER_CH_2, \b TIMER_CH_3 , \b TIMER_CH_4 .
//!
//! The \e ulICPolarity parameter can be one of the values:
//! \b TIMER_ICPOL_RISING, \b TIMER_ICPOL_FALLING, \b TIMER_ICPOL_BOTHEDGE .
//!
//! The \e ulICSelection parameter can be one of the values:
//! \b TIMER_ICSEL_DIRTI, \b TIMER_ICSEL_INDIRTI, \b TIMER_ICSEL_TRC.
//!
//! The \e ulPrescaler parameter can be one of the values:
//! \b TIMER_ICPSC_DIV1, \b TIMER_ICPSC_DIV2, \b TIMER_ICPSC_DIV4, 
//! \b TIMER_ICPSC_DIV8.
//!
//! The \e ulICFilter is a value between 0 to 15.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerICConfigure(unsigned long ulBase, unsigned long ulChannel, 
                 unsigned long ulICPolarity, unsigned long ulICSelection, 
                 unsigned long ulPrescaler, unsigned long ulICFilter)
{
    //
    // Check the arguments.
    //
    xASSERT((ulChannel == TIMER_CH_1) || (ulChannel == TIMER_CH_2) || 
              (ulChannel == TIMER_CH_3) || (ulChannel == TIMER_CH_4));
    
    if((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
       (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
       (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE))
    {
        xASSERT((ulICPolarity == TIMER_ICPOL_RISING) || 
                (ulICPolarity == TIMER_ICPOL_FALLING));
    }
    else
    {
        xASSERT((ulICPolarity == TIMER_ICPOL_RISING) || 
                (ulICPolarity == TIMER_ICPOL_FALLING) ||
                (ulICPolarity == TIMER_ICPOL_BOTHEDGE));
    }
        
    if(ulChannel == TIMER_CH_1)
    {
        //
        // TI1 Configuration
        //
        TimerTI1Configure(ulBase, ulICPolarity, ulICSelection, ulICFilter);
            
        //
        // Set the Input Capture Prescaler value
        //
        TimerIC1PrescalerSet(ulBase, ulPrescaler);
              
    }
    else if(ulChannel == TIMER_CH_2)
    {
        //
        // TI2 Configuration
        //
        TimerTI2Configure(ulBase, ulICPolarity, ulICSelection, ulICFilter);
        
        //
        // Set the Input Capture Prescaler value
        //
        TimerIC2PrescalerSet(ulBase, ulPrescaler);
    }
    else if(ulChannel == TIMER_CH_3)
    {
        //
        // TI3 Configuration
        //
        TimerTI3Configure(ulBase, ulICPolarity, ulICSelection, ulICFilter);
            
        //
        // Set the Input Capture Prescaler value
        //
        TimerIC3PrescalerSet(ulBase, ulPrescaler);
    }
    else
    {
        //
        // TI4 Configuration
        //
        TimerTI4Configure(ulBase, ulICPolarity, ulICSelection, ulICFilter);
            
        //
        // Set the Input Capture Prescaler value
        //
        TimerIC4PrescalerSet(ulBase, ulPrescaler);
    }    
        
}

//*****************************************************************************
//
//! \brief Configure the TI1 as Input.
//!
//! \param ulBase is the base address of the Timer port, it can be  1, 2, 3, 4, 
//!        5, 8, 9, 12 .
//! \param ulChannel is the select fo timer channel. 
//! \param ulICPolarity is the Counter Mode.
//! \param ulICSelection is the counter reload value.
//! \param ulPrescaler is Channel Capture prescaler.
//! \param ulICFilter is the Prescaler value.
//!
//! The \e ulChannel parameter can be one of the values:
//! \b TIMER_CH_1, \b TIMER_CH_2, \b TIMER_CH_3 , \b TIMER_CH_4 .
//!
//! The \e ulICPolarity parameter can be one of the values:
//! \b TIMER_ICPOL_RISING, \b TIMER_ICPOL_FALLING, \b TIMER_ICPOL_BOTHEDGE .
//!
//! The \e ulICSelection parameter can be one of the values:
//! \b TIMER_ICSEL_DIRTI, \b TIMER_ICSEL_INDIRTI, \b TIMER_ICSEL_TRC.
//!
//! The \e ulPrescaler parameter can be one of the values:
//! \b TIMER_ICPSC_DIV1, \b TIMER_ICPSC_DIV2, \b TIMER_ICPSC_DIV4, 
//! \b TIMER_ICPSC_DIV8.
//!
//! The \e ulICFilter is a value between 0 to 15.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerPWMIConfigure(unsigned long ulBase, unsigned long ulChannel, 
                   unsigned long ulICPolarity, unsigned long ulICSelection, 
                   unsigned long ulPrescaler, unsigned long ulICFilter)
{
    unsigned long ulOppositePol = TIMER_ICPOL_RISING;
    unsigned long ulOppositeSel = TIMER_ICSEL_DIRTI;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) ||
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE)); 
    
    //
    // Select the Opposite Input Polarity
    //
    if(ulICPolarity == TIMER_ICPOL_RISING)
    {
        ulOppositePol = TIMER_ICPOL_FALLING;   
    }
    else
    {
        ulOppositePol = TIMER_ICPOL_RISING;
    }
    
    //
    // Select the Opposite Input
    //
    if(ulICSelection == TIMER_ICSEL_DIRTI)
    {
        ulOppositeSel = TIMER_ICSEL_INDIRTI;
    }
    else
    {
        ulOppositeSel = TIMER_ICSEL_DIRTI;
    }
      
    if(ulChannel == TIMER_CH_1)
    {
        //
        // TI1 Configuration
        //
        TimerTI1Configure(ulBase, ulICPolarity, ulICSelection, ulICFilter);
      
        //
        // Set the Input Capture Prescaler value
        //
        TimerIC1PrescalerSet(ulBase, ulPrescaler);
      
        //
        // TI2 Configuration
        //
        TimerTI2Configure(ulBase, ulOppositePol, ulOppositeSel, ulICFilter);
      
        //
        // Set the Input Capture Prescaler value
        //
        TimerIC2PrescalerSet(ulBase, ulPrescaler);
            
    }
    else
    {
        //
        // TI2 Configuration
        //
        TimerTI2Configure(ulBase, ulICPolarity, ulICSelection, ulICFilter);
      
        //
        // Set the Input Capture Prescaler value
        //
        TimerIC2PrescalerSet(ulBase, ulPrescaler);
      
        //
        // TI1 Configuration
        //
        TimerTI1Configure(ulBase, ulOppositePol, ulOppositeSel, ulICFilter);
      
        //
        // Set the Input Capture Prescaler value
        //
        TimerIC1PrescalerSet(ulBase, ulPrescaler);      
    }
        
}

//*****************************************************************************
//
//! \brief Configures the: Break feature, dead time, Lock level, the OSSI,
//!        the OSSR State and the AOE(automatic output enable).
//!
//! \param ulBase is the base address of the Timer port, it can be timer 1, 8.
//! \param ulBDTRConfig is the BDTR Register configuration  information for the
//!        TIM peripheral. 
//!
//! The \e ulBDTRConfig is the logical OR of the following values:
//!    The Off-State selection used in Run mode can be one of the following value:
//! \b TIMER_OSSRSTATE_ENABLE, \b TIMER_OSSRSTATE_DISABLE .
//!    The Off-State selection used in Idle mode can be one of the following value:
//! \b TIMER_OSSISTATE_ENABLE, \b TIMER_OSSISTATE_DISABLE .
//!    The Lock level can be one of the following value:
//! \b TIMER_LOCKLEVEL_OFF, \b TIMER_LOCKLEVEL_1, \b TIMER_LOCKLEVEL_2, 
//! \b TIMER_LOCKLEVEL_3 .
//!    The break input enable disable can be one of the following value:
//! \b TIMER_BREAK_ENABLE, TIMER_BREAK_DISABLE.
//!    The break Polarity can be one of the following value:
//! \b TIMER_BREAKPOL_LOW, TIMER_BREAKPOL_HIGH.
//!    The TIMER AOE Bit Set Reset can be one of the following value:
//! \b TIMER_AUTOOUTPUT_ENABLE, TIMER_AUTOOUTPUT_DISABLE.
//! The dead time interval can be select form 0x00 to 0xFF.
//!
//! The \e ulICFilter is a value between 0 to 15.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerBDTRConfigure(unsigned long ulBase, unsigned long ulBDTRConfig)
{
    xHWREG(ulBase + TIMER_BDTR) = ulBDTRConfig;    
}

//*****************************************************************************
//
//! \brief Start The Timer counter. 
//!
//! \param ulBase is the base address of the Timer port, it can be select form.
//!        timer 1 to 14.
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE)); 

    xHWREG(ulBase + TIMER_CR1) |= TIMER_CR1_CEN;

}

//*****************************************************************************
//
//! \brief Stop The Timer counter. 
//!
//! \param ulBase is the base address of the Timer port, it can be select form.
//!        timer 1 to 14.
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE)); 

    xHWREG(ulBase + TIMER_CR1) &= ~TIMER_CR1_CEN;
}

//*****************************************************************************
//
//! \brief Enables or disables the TIM peripheral Main Outputs.
//!
//! \param ulBase is the base address of the Timer port, it can be timer 1 to 8.
//! \param ulMOConfigure is the new state of the TIM peripheral Main Outputs.
//!
//! The \e ulMOConfigure is one of the following values:
//! \b TIMER_MAINOUTPUT_ENABLE, \b TIMER_MAINOUTPUT_DISABLE .
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerMainOutputConfigure(unsigned long ulBase, unsigned long ulMOConfigure)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM8_BASE)); 
    xASSERT((ulMOConfigure == TIMER_MAINOUTPUT_ENABLE) || 
            (ulMOConfigure == TIMER_MAINOUTPUT_DISABLE));

    if(ulMOConfigure == TIMER_MAINOUTPUT_ENABLE)
    {
         xHWREG(ulBase + TIMER_BDTR) |= TIMER_BDTR_MOE;
    }
    else
    {
         xHWREG(ulBase + TIMER_BDTR) &= ~TIMER_BDTR_MOE;
    }
}

//*****************************************************************************
//
//! \brief Configures the TIMx internal Clock.
//!
//! \param ulBase is the base address of the Timer port. it can be selected timer
//!        1, 2, 3, 4, 5, 8, 9, 12 .
//!
//! \note None
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));
            
    //
    // Disable slave mode to clock the prescaler directly with the internal clock 
    //
    xHWREG(ulBase + TIMER_SMCR) &= ~TIMER_SMCR_SMS_M;
             
} 

//*****************************************************************************
//
//! \brief Configures the TIMx Internal Trigger as External Clock.
//!
//! \param ulBase is the base address of the Timer port. It can be select timer
//!        1, 2, 3, 4, 5, 8, 9, 12.
//! \param ulInputTriggerSource is the Trigger source.
//!
//! The \e ulInputTriggerSource parameter can be one of the values:
//! \b TIMER_TRSEL_ITR0, \b TIMER_TRSEL_ITR1, \b TIMER_TRSEL_ITR2, 
//! \b TIMER_TRSEL_ITR3.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerITRxExternalClockConfigure(unsigned long ulBase, 
                                unsigned long ulInputTriggerSource)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));
    xASSERT((ulInputTriggerSource == TIMER_TRSEL_ITR0) || 
            (ulInputTriggerSource == TIMER_TRSEL_ITR1) || 
            (ulInputTriggerSource == TIMER_TRSEL_ITR2) || 
            (ulInputTriggerSource == TIMER_TRSEL_ITR3));
    
    //
    // Select the External clock mode1
    //        
    xHWREG(ulBase + TIMER_SMCR) |= ulInputTriggerSource;        
     
}

//*****************************************************************************
//
//! \brief Selects the Input Trigger source.
//!
//! \param ulBase is the base address of the Timer port. It can be select timer
//!        1, 2, 3, 4, 5, 8, 9, 12.
//! \param ulInputTriggerSource is the Trigger source.
//!
//! The \e ulInputTriggerSource parameter can be one of the values:
//! \b TIMER_TRSEL_ITR0, \b TIMER_TRSEL_ITR1, \b TIMER_TRSEL_ITR2, 
//! \b TIMER_TRSEL_ITR3.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerInputTriggerSelect(unsigned long ulBase, unsigned long ulInputTriggerSource)
{
    unsigned long ulTempsmcr = 0;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));
    xASSERT((ulInputTriggerSource == TIMER_TRSEL_ITR0) || 
            (ulInputTriggerSource == TIMER_TRSEL_ITR1) ||
            (ulInputTriggerSource == TIMER_TRSEL_ITR2) ||
            (ulInputTriggerSource == TIMER_TRSEL_ITR3) ||
            (ulInputTriggerSource == TIMER_TRSEL_TI1FED) ||
            (ulInputTriggerSource == TIMER_TRSEL_TI1FP1) ||
            (ulInputTriggerSource == TIMER_TRSEL_TI2FP2) ||
            (ulInputTriggerSource == TIMER_TRSEL_ETRF));
    //
    // Get the TIMx SMCR register value
    //
    ulTempsmcr = xHWREG(ulBase + TIMER_SMCR);

    //
    // Reset the TS Bits
    //
    ulTempsmcr &= ~TIMER_SMCR_TS_M;

    //
    // Set the Input Trigger source
    //
    ulTempsmcr |= ulInputTriggerSource;

    //
    // Write to TIMx SMCR
    //
    xHWREG(ulBase + TIMER_SMCR) = ulTempsmcr;
}

//*****************************************************************************
//
//! \brief Configures the TIMx Trigger as External Clock .
//!
//! \param ulBase is the base address of the Timer port. It can be select timer
//!        1, 2, 3, 4, 5, 8, 9, 12.
//! \param ulExtClkSource is the Trigger source.
//! \param ulICPolarity specifies the TIx Polarity.
//! \param ulICFilter specifies the filter value.
//!
//! The \e ulExtClkSource parameter can be one of the values:
//! \b TIMER_TRSEL_TI1FED, \b TIMER_TRSEL_TI1FP1, \b TIMER_TRSEL_TI2FP2 .
//!
//! The \e ulICPolarity parameter can be one of the values:
//! \b TIMER_ICPOL_RISING, \b TIMER_ICPOL_FALLING .
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerTIxExternalClockConfigure(unsigned long ulBase, unsigned long ulExtClkSource,
                               unsigned long ulICPolarity, unsigned long ulICFilter)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));
    xASSERT((ulExtClkSource == TIMER_TRSEL_TI1FED) ||
            (ulExtClkSource == TIMER_TRSEL_TI1FP1) ||
            (ulExtClkSource == TIMER_TRSEL_TI2FP2));
    xASSERT((ulICPolarity == TIMER_ICPOL_RISING) || 
            (ulICPolarity == TIMER_ICPOL_FALLING));
    xASSERT((ulICFilter >= 0) && (ulICFilter <= 0xFF));

    if(ulExtClkSource == TIMER_TRSEL_TI2FP2)
    {
        TimerTI2Configure(ulBase, ulICPolarity, TIMER_ICSEL_DIRTI, ulICFilter);
    }
    else
    {
        TimerTI1Configure(ulBase, ulICPolarity, TIMER_ICSEL_DIRTI, ulICFilter);
    }

    //
    // Select the Trigger source
    //
    TimerInputTriggerSelect(ulBase, ulExtClkSource);

    //
    // Select the External clock mode1
    //
    xHWREG(ulBase + TIMER_SMCR) |= TIMER_SMSEL_EXTERNAL1;
}

//*****************************************************************************
//
//! \brief Configures the External clock Mode1 .
//!
//! \param ulBase is the base address of the Timer port. It can be select timer
//!        1, 2, 3, 4, 5, 8.
//! \param ulExtTRGPrescaler is the external Trigger Prescaler.
//! \param ulExtTRGPloarity specifies external Trigger Polarity.
//! \param ulExtTRGFilter specifies the External Trigger Filter.
//!
//! The \e ulExtTRGPrescaler parameter can be one of the values:
//! \b TIMER_EXTTRGPSC_OFF, \b TIMER_EXTTRGPSC_DIV2,
//! \b TIMER_EXTTRGPSC_DIV4,\b TIMER_EXTTRGPSC_DIV8 .
//!
//! The \e ulExtTRGPloarity parameter can be one of the values:
//! \b TIMER_EXTTRGPOL_INVERTED, \b TIMER_EXTTRGPOL_NONINVERTED.
//!
//! The \e ulExtTRGFilter is a value betweeen 0x00 and 0x0F.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerETRClockMode1Configure(unsigned long ulBase, 
                            unsigned long ulExtTRGPrescaler,
                            unsigned long ulExtTRGPloarity, 
                            unsigned long ulExtTRGFilter)
{
    unsigned long ulTempsmcr = 0;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulExtTRGPrescaler == TIMER_EXTTRGPSC_OFF) ||
            (ulExtTRGPrescaler == TIMER_EXTTRGPSC_DIV2) ||
            (ulExtTRGPrescaler == TIMER_EXTTRGPSC_DIV4) ||
            (ulExtTRGPrescaler == TIMER_EXTTRGPSC_DIV8));
    xASSERT((ulExtTRGPloarity == TIMER_EXTTRGPOL_INVERTED) ||
            (ulExtTRGPloarity == TIMER_EXTTRGPOL_NONINVERTED));
    xASSERT((ulExtTRGFilter >= 0) && (ulExtTRGFilter <= 0x0F));
    
    //
    // Configure the ETR Clock source
    //
    TimerETRConfigure(ulBase, ulExtTRGPrescaler, ulExtTRGPloarity, ulExtTRGFilter);    

    //
    // Get the TIMx SMCR register value
    //
    ulTempsmcr = xHWREG(ulBase + TIMER_SMCR);

    //
    // Reset the SMS Bits
    //
    ulTempsmcr &= ~TIMER_SMCR_SMS_M;

    //
    // Select the External clock mode1
    //
    ulTempsmcr |= TIMER_SMCR_SMS_EXC1;

    //
    // Select the Trigger selection : ETRF
    //
    ulTempsmcr &= ~TIMER_SMCR_TS_M;
    ulTempsmcr |= TIMER_SMCR_TS_ETRF;

    //
    // Write to TIMx SMCR
    //
    xHWREG(ulBase + TIMER_SMCR) = ulTempsmcr;

}

//*****************************************************************************
//
//! \brief Configures the External clock Mode2 .
//!
//! \param ulBase is the base address of the Timer port. It can be select timer
//!        1, 2, 3, 4, 5, 8.
//! \param ulExtTRGPrescaler is the external Trigger Prescaler.
//! \param ulExtTRGPloarity specifies external Trigger Polarity.
//! \param ulExtTRGFilter specifies the External Trigger Filter.
//!
//! The \e ulExtTRGPrescaler parameter can be one of the values:
//! \b TIMER_EXTTRGPSC_OFF, \b TIMER_EXTTRGPSC_DIV2,
//! \b TIMER_EXTTRGPSC_DIV4,\b TIMER_EXTTRGPSC_DIV8 .
//!
//! The \e ulExtTRGPloarity parameter can be one of the values:
//! \b TIMER_EXTTRGPOL_INVERTED, \b TIMER_EXTTRGPOL_NONINVERTED.
//!
//! The \e ulExtTRGFilter is a value betweeen 0x00 and 0x0F.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerETRClockMode2Configure(unsigned long ulBase, 
                            unsigned long ulExtTRGPrescaler,
                            unsigned long ulExtTRGPloarity, 
                            unsigned long ulExtTRGFilter)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulExtTRGPrescaler == TIMER_EXTTRGPSC_OFF) ||
            (ulExtTRGPrescaler == TIMER_EXTTRGPSC_DIV2) ||
            (ulExtTRGPrescaler == TIMER_EXTTRGPSC_DIV4) ||
            (ulExtTRGPrescaler == TIMER_EXTTRGPSC_DIV8));
    xASSERT((ulExtTRGPloarity == TIMER_EXTTRGPOL_INVERTED) ||
            (ulExtTRGPloarity == TIMER_EXTTRGPOL_NONINVERTED));
    xASSERT((ulExtTRGFilter >= 0) && (ulExtTRGFilter <= 0x0F));
    
    //
    // Configure the ETR Clock source
    //
    TimerETRConfigure(ulBase, ulExtTRGPrescaler, ulExtTRGPloarity, ulExtTRGFilter);    

    //
    // Enable the External clock mode2
    //
    xHWREG(ulBase + TIMER_SMCR) |= TIMER_SMCR_ECE;

}

//*****************************************************************************
//
//! \brief Configures the TIMx External Trigger (ETR).
//!
//! \param ulBase is the base address of the Timer port. It can be select timer
//!        1, 2, 3, 4, 5, 8.
//! \param ulExtTRGPrescaler is the external Trigger Prescaler.
//! \param ulExtTRGPloarity specifies external Trigger Polarity.
//! \param ulExtTRGFilter specifies the External Trigger Filter.
//!
//! The \e ulExtTRGPrescaler parameter can be one of the values:
//! \b TIMER_EXTTRGPSC_OFF, \b TIMER_EXTTRGPSC_DIV2,
//! \b TIMER_EXTTRGPSC_DIV4,\b TIMER_EXTTRGPSC_DIV8 .
//!
//! The \e ulExtTRGPloarity parameter can be one of the values:
//! \b TIMER_EXTTRGPOL_INVERTED, \b TIMER_EXTTRGPOL_NONINVERTED.
//!
//! The \e ulExtTRGFilter is a value betweeen 0x00 and 0x0F.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void
TimerETRConfigure(unsigned long ulBase, unsigned long ulExtTRGPrescaler, 
                  unsigned long ulExtTRGPolarity, unsigned long ulExtTRGFilter)
{
    unsigned long ulTempsmcr = 0;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulExtTRGPrescaler == TIMER_EXTTRGPSC_OFF) ||
            (ulExtTRGPrescaler == TIMER_EXTTRGPSC_DIV2) ||
            (ulExtTRGPrescaler == TIMER_EXTTRGPSC_DIV4) ||
            (ulExtTRGPrescaler == TIMER_EXTTRGPSC_DIV8));
    xASSERT((ulExtTRGPolarity == TIMER_EXTTRGPOL_INVERTED) ||
            (ulExtTRGPolarity == TIMER_EXTTRGPOL_NONINVERTED));
    xASSERT((ulExtTRGFilter >= 0) && (ulExtTRGFilter <= 0x0F));
    
    //
    // Get the TIMx SMCR register value
    //
    ulTempsmcr = xHWREG(ulBase + TIMER_SMCR);
    
    //
    // Set the Prescaler, the Filter value and the Polarity
    //
    ulTempsmcr &= ~(TIMER_SMCR_ETP | TIMER_SMCR_ETPS_M | TIMER_SMCR_ETF_M);
    ulTempsmcr |= (ulExtTRGPrescaler | ulExtTRGPolarity | (ulExtTRGFilter << 8));
    
    //
    // Write to TIMx SMCR
    //
    xHWREG(ulBase + TIMER_SMCR) = ulTempsmcr;     
}

//*****************************************************************************
//
//! \brief Configures the TIMx Prescaler.
//!
//! \param ulBase is the base address of the Timer port. It can be selected form 
//!        timer 0 ~ 14.
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) ||
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE)); 
    xASSERT((ulPrescale >= 0) && (ulPrescale <= 0x0000FFFF));
    xASSERT((ulPSCReloadTime == TIMER_PSC_RLD_UPDATE) || 
            (ulPSCReloadTime == TIMER_PSC_RLD_IMMEDIATE));
    
    //
    // Set the prescaler value
    //
    xHWREG(ulBase + TIMER_PSC) = ulPrescale;
    
    //
    // Set or reset the UG Bit
    //
    xHWREG(ulBase + TIMER_EGR) = ulPSCReloadTime;
}

//*****************************************************************************
//
//! \brief Configures counter mode
//! \param ulBase is the base address of the Timer port. Timer 1, 2, 3, 4, 5, 8
//!        can be selected.
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
    unsigned long ulTempCR1;
    
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulCountMode == TIMER_CNT_MODE_UP) ||
            (ulCountMode == TIMER_CNT_MODE_CA1) ||
            (ulCountMode == TIMER_CNT_MODE_CA2) ||
            (ulCountMode == TIMER_CNT_MODE_CA3) ||
            (ulCountMode == TIMER_CNT_MODE_DOWN));
    
    ulTempCR1 = xHWREG(ulBase + TIMER_CR1);
                
    //
    // Select the Counter Mode
    //
    ulTempCR1 &= ~(TIMER_CR1_DIR | TIMER_CR1_CMS_M);
    xHWREG(ulBase + TIMER_CR1) = ulTempCR1;
    ulTempCR1 |= ulCountMode;
    
    //
    // Set the Counter Mode
    //
    xHWREG(ulBase + TIMER_CR1) |= ulCountMode;   
}

//*****************************************************************************
//
//! \brief Configures encoder interface.
//!
//! \param ulBase is the base address of the Timer port. Timer 1, 2, 3, 4, 5, 8
//!        can be selected.
//! \param ulEncoderMode specifies the TIMx Encoder Mode.
//! \param ulIC1Polarity specifies the IC1 Polarity.
//! \param ulIC2Polarity specifies the IC2 Polarity.
//!
//! The \e ulEncoderMode parameter can be one of the values:
//! \b TIMER_SMSEL_ENCODER1, \b TIMER_SMSEL_ENCODER2, \b TIMER_SMSEL_ENCODER3.
//!
//! The \e ulIC1Polarity parameter can be one of the values:
//! \b TIMER_ICPOL_RISING, \b TIMER_ICPOL_FALLING.
//!
//! The \e ulIC2Polarity parameter can be one of the values:
//! \b TIMER_ICPOL_RISING, \b TIMER_ICPOL_FALLING.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerEncoderInterfaceConfigure(unsigned long ulBase, unsigned long ulEncoderMode,
                       unsigned long ulIC1Polarity, unsigned long ulIC2Polarity)
{
    unsigned long ulTempsmcr = 0, ulTempccmr1 = 0, ulTempccer = 0; 

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulEncoderMode == TIMER_SMSEL_ENCODER1) || 
            (ulEncoderMode == TIMER_SMSEL_ENCODER2) ||
            (ulEncoderMode == TIMER_SMSEL_ENCODER3));
    xASSERT((ulIC1Polarity == TIMER_ICPOL_RISING) || 
            (ulIC1Polarity == TIMER_ICPOL_FALLING));
    xASSERT((ulIC2Polarity == TIMER_ICPOL_RISING) || 
            (ulIC2Polarity == TIMER_ICPOL_FALLING));
    
    //
    // Disable the CC1E ,CC2E
    //
    xHWREG(ulBase + TIMER_CCER) &= ~(TIMER_CCER_CC1E | TIMER_CCER_CC2E);    

    //
    // Get the TIMx SMCR register value
    //
    ulTempsmcr = xHWREG(ulBase + TIMER_SMCR);

    //
    // Get the TIMx CCMR1 register value
    //
    ulTempccmr1 = xHWREG(ulBase + TIMER_CCMR1);

    //
    // Get the TIMx CCER register value
    //
    ulTempccer = xHWREG(ulBase + TIMER_CCER);

    //
    // Set the encoder Mode
    //
    ulTempsmcr &= ~TIMER_SMCR_SMS_M;
    ulTempsmcr |= ulEncoderMode;

    //
    // Select the Capture Compare 1 and the Capture Compare 2 as input
    //
    ulTempccmr1 &= ~(TIMER_CCMR1_CC1S_M | TIMER_CCMR1_CC2S_M);
    ulTempccmr1 |= (TIMER_CCMR1_CC1S_IC1TI1 | TIMER_CCMR1_CC2S_IC2TI2); 
    
    //
    // Set the TI1 and the TI2 Polarities
    //
    ulTempccer &= ~(TIMER_CCER_CC1P | TIMER_CCER_CC2P);
    ulTempccer |= (ulIC1Polarity | (ulIC2Polarity << 4)); 
    
    //
    // Write to TIMx SMCR
    //
    xHWREG(ulBase + TIMER_SMCR) = ulTempsmcr;
    
    //
    // Write to TIMx CCMR1
    //
    xHWREG(ulBase + TIMER_CCMR1) = ulTempccmr1;
    
    //
    // Write to TIMx CCER
    //
    xHWREG(ulBase + TIMER_CCER) =  ulTempccer; 
    xHWREG(ulBase + TIMER_CCER) |= TIMER_CCER_CC1E | TIMER_CCER_CC2E;

}

//*****************************************************************************
//
//! \brief Forces the TIMx output 1 waveform to active or inactive level.
//!
//! \param ulBase is the base address of the Timer port. It can be  1 to 14 
//!        except 6 and 7 to select the TIM peripheral.
//! \param ulForcedAction is the forced action to be set to the output waveform.
//!
//! The \e ForcedAction parameter can be one of the values:
//! \b TIMER_FORCED_ACTIVE, \b TIMER_FORCED_INACTIVE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerForcedOC1Configure(unsigned long ulBase, unsigned long ulForcedAction)
{
    unsigned long ulTempccmr1 = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) ||
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) ||
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) ||     
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) ||
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));

    xASSERT((ulForcedAction == TIMER_FORCED_ACTIVE) || 
            (ulForcedAction == TIMER_FORCED_INACTIVE));

    //
    // Write to TIMx CCMR1
    //
    ulTempccmr1 = xHWREG(ulBase + TIMER_CCMR1);

    //
    // Reset the OC1M Bits
    //
    ulTempccmr1 &= ~TIMER_CCMR1_OC1M_M;

    //
    // Configure The Forced output Mode
    //
    ulTempccmr1 |= ulForcedAction;

    //
    // Write to TIMx CCMR1 register
    //
    xHWREG(ulBase + TIMER_CCMR1) = ulTempccmr1;
     
}

//*****************************************************************************
//
//! \brief Forces the TIMx output 2 waveform to active or inactive level.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1, 2, 
//!        3, 4, 5, 8, 9, 12.
//! \param ulForcedAction is the forced action to be set to the output waveform.
//!
//! The \e ForcedAction parameter can be one of the values:
//! \b TIMER_FORCED_ACTIVE, \b TIMER_FORCED_INACTIVE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerForcedOC2Configure(unsigned long ulBase, unsigned long ulForcedAction)
{
    unsigned long ulTempccmr1 = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) ||
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) ||
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));

    xASSERT((ulForcedAction == TIMER_FORCED_ACTIVE) || 
            (ulForcedAction == TIMER_FORCED_INACTIVE));

    //
    // Write to TIMx CCMR1
    //
    ulTempccmr1 = xHWREG(ulBase + TIMER_CCMR1);

    //
    // Reset the OC1M Bits
    //
    ulTempccmr1 &= ~TIMER_CCMR1_OC2M_M;

    //
    // Configure The Forced output Mode
    //
    ulTempccmr1 |= (ulForcedAction << 8);

    //
    // Write to TIMx CCMR1 register
    //
    xHWREG(ulBase + TIMER_CCMR1) = ulTempccmr1;
     
}

//*****************************************************************************
//
//! \brief Forces the TIMx output 3 waveform to active or inactive level.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1, 2, 
//!        3, 4, 5, 8.
//! \param ulForcedAction is the forced action to be set to the output waveform.
//!
//! The \e ForcedAction parameter can be one of the values:
//! \b TIMER_FORCED_ACTIVE, \b TIMER_FORCED_INACTIVE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerForcedOC3Configure(unsigned long ulBase, unsigned long ulForcedAction)
{
    unsigned long ulTempccmr2 = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulForcedAction == TIMER_FORCED_ACTIVE) || 
            (ulForcedAction == TIMER_FORCED_INACTIVE));

    //
    // Write to TIMx CCMR2
    //
    ulTempccmr2 = xHWREG(ulBase + TIMER_CCMR2);

    //
    // Reset the OC3M Bits
    //
    ulTempccmr2 &= ~TIMER_CCMR2_OC3M_M;

    //
    // Configure The Forced output Mode
    //
    ulTempccmr2 |= ulForcedAction;

    //
    // Write to TIMx CCMR2 register
    //
    xHWREG(ulBase + TIMER_CCMR2) = ulTempccmr2;
     
}

//*****************************************************************************
//
//! \brief Forces the TIMx output 4 waveform to active or inactive level.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1, 2, 
//!        3, 4, 5, 8.
//! \param ulForcedAction is the forced action to be set to the output waveform.
//!
//! The \e ForcedAction parameter can be one of the values:
//! \b TIMER_FORCED_ACTIVE, \b TIMER_FORCED_INACTIVE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerForcedOC4Configure(unsigned long ulBase, unsigned long ulForcedAction)
{
    unsigned long ulTempccmr2 = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulForcedAction == TIMER_FORCED_ACTIVE) || 
            (ulForcedAction == TIMER_FORCED_INACTIVE));

    //
    // Write to TIMx CCMR2
    //
    ulTempccmr2 = xHWREG(ulBase + TIMER_CCMR2);

    //
    // Reset the OC3M Bits
    //
    ulTempccmr2 &= ~TIMER_CCMR2_OC4M_M;

    //
    // Configure The Forced output Mode
    //
    ulTempccmr2 |= (ulForcedAction << 8);

    //
    // Write to TIMx CCMR2 register
    //
    xHWREG(ulBase + TIMER_CCMR2) = ulTempccmr2;
     
}

//*****************************************************************************
//
//! \brief Enables or disables TIMx peripheral Preload register on ARR.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1 to 14.
//!      
//! \param ulARRProload is the new state of the TIMx peripheral Preload register.
//!
//! The \e ForcedAction parameter can be one of the values:
//! \b TIMER_ARPE_ENABLE, \b TIMER_ARPE_DISABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerARRPreloadConfigure(unsigned long ulBase, unsigned long ulARRProload)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulARRProload == TIMER_ARPE_ENABLE) || 
            (ulARRProload == TIMER_ARPE_DISABLE));

    if(ulARRProload == TIMER_ARPE_ENABLE)
    {
        xHWREG(ulBase + TIMER_CR1) |= TIMER_CR1_ARR;
    }
    else
    {
        xHWREG(ulBase + TIMER_CR1) &= ~TIMER_CR1_ARR;
    }

}

//*****************************************************************************
//
//! \brief Selects the TIM peripheral Commutation event.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1, 8.
//! \param ulCCUSelect is the Capture/compare control update selection.
//!
//! The \e ForcedAction parameter can be one of the values:
//! \b TIMER_CCUS_ENABLE, \b TIMER_CCUS_DISABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCCUSelect(unsigned long ulBase, unsigned long ulCCUSelect)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulCCUSelect == TIMER_CCUS_ENABLE) || 
            (ulCCUSelect == TIMER_CCUS_DISABLE));

    if(ulCCUSelect == TIMER_CCUS_ENABLE)
    {
        xHWREG(ulBase + TIMER_CR2) |= TIMER_CR2_MMS_CCUS; 
    }
    else
    {
          xHWREG(ulBase + TIMER_CR2) &= ~TIMER_CR2_MMS_CCUS; 
    }

}

//*****************************************************************************
//
//! \brief Selects the TIMx peripheral Capture Compare DMA source.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1, 2, 
//!        3, 4, 5, 8 .
//! \param ulCCDSelect is Capture/compare DMA selection. 
//!
//! The \e ForcedAction parameter can be one of the values:
//! \b TIMER_CCDS_ENABLE, \b TIMER_CCDS_DISABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCCDSelect(unsigned long ulBase, unsigned long ulCCDSelect)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulCCDSelect == TIMER_CCDS_ENABLE) || 
            (ulCCDSelect == TIMER_CCDS_DISABLE));

    if(ulCCDSelect == TIMER_CCDS_ENABLE)
    {
        xHWREG(ulBase + TIMER_CR2) |= TIMER_CR2_MMS_CCDS; 
    }
    else
    {
        xHWREG(ulBase + TIMER_CR2) &= ~TIMER_CR2_MMS_CCDS;
    }
}

//*****************************************************************************
//
//! \brief Sets or Resets the TIM peripheral Capture Compare Preload Control bit.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1, 2, 
//!        3, 4, 5, 8 .
//! \param ulCCPreload is new state of the Capture Compare Preload Control bit.
//!
//! The \e ulCCPreload parameter can be one of the values:
//! \b TIMER_CCPC_SET, \b TIMER_CCPC_RESET.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCCPreloadControl(unsigned long ulBase, unsigned long ulCCPreload)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulCCPreload == TIMER_CCPC_SET) || 
            (ulCCPreload == TIMER_CCPC_RESET));
            
    if(ulCCPreload == TIMER_CCPC_SET)
    {
        xHWREG(ulBase + TIMER_CR2) |= TIMER_CR2_MMS_CCPC;
    }
    else
    {
        xHWREG(ulBase + TIMER_CR2) &= ~TIMER_CR2_MMS_CCPC;
    }             
}

//*****************************************************************************
//
//! \brief Enables or disables the TIMx peripheral Output Compare 1 preload .
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1 to
//!        14 except 6 and 7 .      
//! \param ulOCPreload is the new state of the TIMx peripheral Preload register.
//!
//! The \e ulOCPreload parameter can be one of the values:
//! \b TIMER_OCPROLOAD_ENABLE, \b TIMER_OCPROLOAD_DISABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC1PreloadConfigure(unsigned long ulBase, unsigned long ulOCPreload)
{
    unsigned long ulTempccmr1 = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulOCPreload == TIMER_OCPROLOAD_ENABLE) || 
            (ulOCPreload == TIMER_OCPROLOAD_DISABLE));
   
    ulTempccmr1 = xHWREG(ulBase + TIMER_CCMR1);
    
    //
    // Reset the OC1PE Bit  
    //
    ulTempccmr1 &= ~TIMER_CCMR1_OC1PE;
    ulTempccmr1 |= ulOCPreload;

    xHWREG(ulBase + TIMER_CCMR1) = ulTempccmr1;
}

//*****************************************************************************
//
//! \brief Enables or disables the TIMx peripheral Output Compare 2 preload .
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1, 2, 
//!        3, 4, 5, 8, 9, 12.
//!      
//! \param ulOCPreload is the new state of the TIMx peripheral Preload register.
//!
//! The \e ulOCPreload parameter can be one of the values:
//! \b TIMER_OCPROLOAD_ENABLE, \b TIMER_OCPROLOAD_DISABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC2PreloadConfigure(unsigned long ulBase, unsigned long ulOCPreload)
{
    unsigned long ulTempccmr1 = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));
    xASSERT((ulOCPreload == TIMER_OCPROLOAD_ENABLE) || 
            (ulOCPreload == TIMER_OCPROLOAD_DISABLE));
   
    ulTempccmr1 = xHWREG(ulBase + TIMER_CCMR1);
    
    //
    // Reset the OC2PE Bit  
    //
    ulTempccmr1 &= ~TIMER_CCMR1_OC2PE;
    ulTempccmr1 |= (ulOCPreload << 8);

    xHWREG(ulBase + TIMER_CCMR1) = ulTempccmr1;
} 

//*****************************************************************************
//
//! \brief Enables or disables the TIMx peripheral Output Compare 3 preload .
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1, 2, 
//!        3, 4, 5, 8 .
//!      
//! \param ulOCPreload is the new state of the TIMx peripheral Preload register.
//!
//! The \e ulOCPreload parameter can be one of the values:
//! \b TIMER_OCPROLOAD_ENABLE, \b TIMER_OCPROLOAD_DISABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC3PreloadConfigure(unsigned long ulBase, unsigned long ulOCPreload)
{
    unsigned long ulTempccmr2 = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));
    xASSERT((ulOCPreload == TIMER_OCPROLOAD_ENABLE) || 
            (ulOCPreload == TIMER_OCPROLOAD_DISABLE));
   
    ulTempccmr2 = xHWREG(ulBase + TIMER_CCMR2);
    
    //
    // Reset the OC3PE Bit  
    //
    ulTempccmr2 &= ~TIMER_CCMR2_OC3PE;
    ulTempccmr2 |= ulOCPreload;

    xHWREG(ulBase + TIMER_CCMR2) = ulTempccmr2;
}

//*****************************************************************************
//
//! \brief Enables or disables the TIMx peripheral Output Compare 4 preload .
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1, 2, 
//!        3, 4, 5, 8 .
//!      
//! \param ulOCPreload is the new state of the TIMx peripheral Preload register.
//!
//! The \e ulOCPreload parameter can be one of the values:
//! \b TIMER_OCPROLOAD_ENABLE, \b TIMER_OCPROLOAD_DISABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC4PreloadConfigure(unsigned long ulBase, unsigned long ulOCPreload)
{
    unsigned long ulTempccmr2 = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));
    xASSERT((ulOCPreload == TIMER_OCPROLOAD_ENABLE) || 
            (ulOCPreload == TIMER_OCPROLOAD_DISABLE));
   
    ulTempccmr2 = xHWREG(ulBase + TIMER_CCMR2);
    
    //
    // Reset the OC4PE Bit  
    //
    ulTempccmr2 &= ~TIMER_CCMR2_OC4PE;
    ulTempccmr2 |= (ulOCPreload << 8);

    xHWREG(ulBase + TIMER_CCMR2) = ulTempccmr2;
} 

//*****************************************************************************
//
//! \brief Configures the TIMx Output Compare 1 Fast feature.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1 to
//!        14 except 6 and 7 .  
//! \param ulOCFast is the new state of the Output Compare Fast Enable Bit.
//!
//! The \e ulOCFast parameter can be one of the values:
//! \b TIMER_OCFAST_ENABLE, \b TIMER_OCFAST_DISABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC1FastConfigure(unsigned long ulBase, unsigned long ulOCFast)
{
    unsigned long ulTempccmr1 = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulOCFast == TIMER_OCFAST_ENABLE) || 
            (ulOCFast == TIMER_OCFAST_DISABLE));

    ulTempccmr1 = xHWREG(ulBase + TIMER_CCMR1);

    //
    // Reset the OC1FE Bit
    //
    ulTempccmr1    &= ~TIMER_CCMR1_OC1FE;
    
    //
    // Enable or Disable the Output Compare Fast Bit
    //
    ulTempccmr1 |= ulOCFast;
    
    //
    // Write to TIMx CCMR1
    //
    xHWREG(ulBase + TIMER_CCMR1) = ulTempccmr1;

}

//*****************************************************************************
//
//! \brief Configures the TIMx Output Compare 2 Fast feature.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1, 2, 
//!        3, 4, 5, 8, 9, 12.
//! \param ulOCFast is the new state of the Output Compare Fast Enable Bit.
//!
//! The \e ulOCFast parameter can be one of the values:
//! \b TIMER_OCFAST_ENABLE, \b TIMER_OCFAST_DISABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC2FastConfigure(unsigned long ulBase, unsigned long ulOCFast)
{
    unsigned long ulTempccmr1 = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));
    xASSERT((ulOCFast == TIMER_OCFAST_ENABLE) || 
            (ulOCFast == TIMER_OCFAST_DISABLE));

    ulTempccmr1 = xHWREG(ulBase + TIMER_CCMR1);

    //
    // Reset the OC1FE Bit
    //
    ulTempccmr1    &= ~TIMER_CCMR1_OC2FE;
    
    //
    // Enable or Disable the Output Compare Fast Bit
    //
    ulTempccmr1 |= (ulOCFast << 8);
    
    //
    // Write to TIMx CCMR1
    //
    xHWREG(ulBase + TIMER_CCMR1) = ulTempccmr1;

}  

//*****************************************************************************
//
//! \brief Configures the TIMx Output Compare 3 Fast feature.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1, 2, 
//!        3, 4, 5, 8 .
//! \param ulOCFast is the new state of the Output Compare Fast Enable Bit.
//!
//! The \e ulOCFast parameter can be one of the values:
//! \b TIMER_OCFAST_ENABLE, \b TIMER_OCFAST_DISABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC3FastConfigure(unsigned long ulBase, unsigned long ulOCFast)
{
    unsigned long ulTempccmr2 = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulOCFast == TIMER_OCFAST_ENABLE) || 
            (ulOCFast == TIMER_OCFAST_DISABLE));

    ulTempccmr2 = xHWREG(ulBase + TIMER_CCMR2);

    //
    // Reset the OC3FE Bit
    //
    ulTempccmr2    &= ~TIMER_CCMR2_OC3FE;
    
    //
    // Enable or Disable the Output Compare Fast Bit
    //
    ulTempccmr2 |= ulOCFast;
    
    //
    // Write to TIMx CCMR2
    //
    xHWREG(ulBase + TIMER_CCMR2) = ulTempccmr2;

}

//*****************************************************************************
//
//! \brief Configures the TIMx Output Compare 4 Fast feature.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1, 2, 
//!        3, 4, 5, 8 .
//! \param ulOCFast is the new state of the Output Compare Fast Enable Bit.
//!
//! The \e ulOCFast parameter can be one of the values:
//! \b TIMER_OCFAST_ENABLE, \b TIMER_OCFAST_DISABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC4FastConfigure(unsigned long ulBase, unsigned long ulOCFast)
{
    unsigned long ulTempccmr2 = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulOCFast == TIMER_OCFAST_ENABLE) || 
            (ulOCFast == TIMER_OCFAST_DISABLE));

    ulTempccmr2 = xHWREG(ulBase + TIMER_CCMR2);

    //
    // Reset the OC4FE Bit
    //
    ulTempccmr2    &= ~TIMER_CCMR2_OC4FE;
    
    //
    // Enable or Disable the Output Compare Fast Bit
    //
    ulTempccmr2 |= (ulOCFast << 8);
    
    //
    // Write to TIMx CCMR2
    //
    xHWREG(ulBase + TIMER_CCMR2) = ulTempccmr2;

}

//*****************************************************************************
//
//! \brief Clears or safeguards the OCREFx signal on an external event
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1, 2, 
//!        3, 4, 5, 8 .
//! \param ulChannel is the selected timer channel.
//! \param ulOCClear is the new state of the Output Compare Clear Enable Bit.
//!
//! The \e ulOCFast parameter can be one of the values:
//! \b TIMER_OCCLEAR_ENABLE, \b TIMER_OCCLEAR_DISABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOCxRefClear(unsigned long ulBase, unsigned long ulChannel, 
                 unsigned long ulOCClear)
{
    unsigned long ulTempccmr = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulChannel == TIMER_CH_1) || (ulChannel == TIMER_CH_2) ||
            (ulChannel == TIMER_CH_3) || (ulChannel == TIMER_CH_4));
    xASSERT((ulOCClear == TIMER_OCCLEAR_ENABLE) || 
            (ulOCClear == TIMER_OCCLEAR_DISABLE));

    if((ulChannel == TIMER_CH_1) || (ulChannel == TIMER_CH_2))
    {
        ulTempccmr = xHWREG(ulBase + TIMER_CCMR1);
        if(ulChannel == TIMER_CH_1)
        {
            ulTempccmr &= ~TIMER_CCMR1_OC1CE;

            //
            // Enable or Disable the Output Compare Clear Bit
            //
            ulTempccmr |= ulOCClear;
        }
        else
        {
            ulTempccmr &= ~TIMER_CCMR1_OC2CE;

            //
            // Enable or Disable the Output Compare Clear Bit
            //
            ulTempccmr |= (ulOCClear << 8);
        }
        xHWREG(ulBase + TIMER_CCMR1) = ulTempccmr;
    }
    else
    {
        ulTempccmr = xHWREG(ulBase + TIMER_CCMR2);
        if(ulChannel == TIMER_CH_3)
        {
            ulTempccmr &= ~TIMER_CCMR2_OC3CE;

            //
            // Enable or Disable the Output Compare Clear Bit
            //
            ulTempccmr |= ulOCClear;
        }
        else
        {
            ulTempccmr &= ~TIMER_CCMR2_OC4CE;

            //
            // Enable or Disable the Output Compare Clear Bit
            //
            ulTempccmr |= (ulOCClear << 8);
        }
        xHWREG(ulBase + TIMER_CCMR2) = ulTempccmr;
    }
}

//*****************************************************************************
//
//! \brief Configures the TIMx channel 1 polarity.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1 to
//!        14 except 6 and 7 .      
//! \param ulPolarity specifies the OC1 Polarity
//!
//! The \e ulPolarity parameter can be one of the values:
//! \b TIMER_OP_POL_HIGH, \b TIMER_OP_POL_LOW.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC1PolarityConfigure(unsigned long ulBase, unsigned long ulPolarity)
{
    unsigned long ulTempccer = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulPolarity == TIMER_OP_POL_HIGH) ||
            (ulPolarity == TIMER_OP_POL_LOW));

    ulTempccer = xHWREG(ulBase + TIMER_CCER);

    //
    // Set or Reset the CC1P Bit
    //
    ulTempccer &= ~TIMER_CCER_CC1P;
    ulTempccer |= ulPolarity;
     
    //
    // Write to TIMx CCER register
    //
    xHWREG(ulBase + TIMER_CCER) = ulTempccer;
}

//*****************************************************************************
//
//! \brief Configures the TIMx channel 1N polarity.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1 to
//!        14 except 6 and 7 .      
//! \param ulPolarity specifies the OC1 Polarity
//!
//! The \e ulPolarity parameter can be one of the values:
//! \b TIMER_OP_N_POL_HIGH, \b TIMER_OP_N_POL_LOW.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC1NPolarityConfigure(unsigned long ulBase, unsigned long ulPolarity)
{
    unsigned long ulTempccer = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulPolarity == TIMER_OP_N_POL_HIGH) ||
            (ulPolarity == TIMER_OP_N_POL_LOW));

    ulTempccer = xHWREG(ulBase + TIMER_CCER);

    //
    // Set or Reset the CC1NP Bit
    //
    ulTempccer &= ~TIMER_CCER_CC1NP;
    ulTempccer |= ulPolarity;
     
    //
    // Write to TIMx CCER register
    //
    xHWREG(ulBase + TIMER_CCER) = ulTempccer;
}

//*****************************************************************************
//
//! \brief Configures the TIMx channel 2 polarity.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1,2,3
//!        ,4, 5, 8, 9, 12 .      
//! \param ulPolarity specifies the OC2 Polarity .
//!
//! The \e ulPolarity parameter can be one of the values:
//! \b TIMER_OP_POL_HIGH, \b TIMER_OP_POL_LOW.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC2PolarityConfigure(unsigned long ulBase, unsigned long ulPolarity)
{
    unsigned long ulTempccer = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));
    xASSERT((ulPolarity == TIMER_OP_POL_HIGH) ||
            (ulPolarity == TIMER_OP_POL_LOW));

    ulTempccer = xHWREG(ulBase + TIMER_CCER);

    //
    // Set or Reset the CC2P Bit
    //
    ulTempccer &= ~TIMER_CCER_CC2P;
    ulTempccer |= (ulPolarity << 4);
     
    //
    // Write to TIMx CCER register
    //
    xHWREG(ulBase + TIMER_CCER) = ulTempccer;
}

//*****************************************************************************
//
//! \brief Configures the TIMx channel 2N polarity.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1,2,3
//!        ,4, 5, 8, 9, 12 .      
//! \param ulPolarity specifies the OC2 Polarity
//!
//! The \e ulPolarity parameter can be one of the values:
//! \b TIMER_OP_N_POL_HIGH, \b TIMER_OP_N_POL_LOW.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC2NPolarityConfigure(unsigned long ulBase, unsigned long ulPolarity)
{
    unsigned long ulTempccer = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));
    xASSERT((ulPolarity == TIMER_OP_N_POL_HIGH) ||
            (ulPolarity == TIMER_OP_N_POL_LOW));

    ulTempccer = xHWREG(ulBase + TIMER_CCER);

    //
    // Set or Reset the CC1NP Bit
    //
    ulTempccer &= ~TIMER_CCER_CC2NP;
    ulTempccer |= (ulPolarity << 4);
     
    //
    // Write to TIMx CCER register
    //
    xHWREG(ulBase + TIMER_CCER) = ulTempccer;
}

//*****************************************************************************
//
//! \brief Configures the TIMx channel 3 polarity.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1,2,3
//!        ,4, 5, 8 .      
//! \param ulPolarity specifies the OC2 Polarity .
//!
//! The \e ulPolarity parameter can be one of the values:
//! \b TIMER_OP_POL_HIGH, \b TIMER_OP_POL_LOW.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC3PolarityConfigure(unsigned long ulBase, unsigned long ulPolarity)
{
    unsigned long ulTempccer = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulPolarity == TIMER_OP_POL_HIGH) ||
            (ulPolarity == TIMER_OP_POL_LOW));

    ulTempccer = xHWREG(ulBase + TIMER_CCER);

    //
    // Set or Reset the CC2P Bit
    //
    ulTempccer &= ~TIMER_CCER_CC3P;
    ulTempccer |= (ulPolarity << 8);
     
    //
    // Write to TIMx CCER register
    //
    xHWREG(ulBase + TIMER_CCER) = ulTempccer;
}

//*****************************************************************************
//
//! \brief Configures the TIMx channel 3N polarity.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1,2,3
//!        ,4, 5, 8 .      
//! \param ulPolarity specifies the OC3 Polarity
//!
//! The \e ulPolarity parameter can be one of the values:
//! \b TIMER_OP_N_POL_HIGH, \b TIMER_OP_N_POL_LOW.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC3NPolarityConfigure(unsigned long ulBase, unsigned long ulPolarity)
{
    unsigned long ulTempccer = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulPolarity == TIMER_OP_N_POL_HIGH) ||
            (ulPolarity == TIMER_OP_N_POL_LOW));

    ulTempccer = xHWREG(ulBase + TIMER_CCER);

    //
    // Set or Reset the CC1NP Bit
    //
    ulTempccer &= ~TIMER_CCER_CC3NP;
    ulTempccer |= (ulPolarity << 8);
     
    //
    // Write to TIMx CCER register
    //
    xHWREG(ulBase + TIMER_CCER) = ulTempccer;
}

//*****************************************************************************
//
//! \brief Configures the TIMx channel 4 polarity.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1,2,3
//!        ,4, 5, 8 .      
//! \param ulPolarity specifies the OC2 Polarity .
//!
//! The \e ulPolarity parameter can be one of the values:
//! \b TIMER_OP_POL_HIGH, \b TIMER_OP_POL_LOW.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOC4PolarityConfigure(unsigned long ulBase, unsigned long ulPolarity)
{
    unsigned long ulTempccer = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulPolarity == TIMER_OP_POL_HIGH) ||
            (ulPolarity == TIMER_OP_POL_LOW));

    ulTempccer = xHWREG(ulBase + TIMER_CCER);

    //
    // Set or Reset the CC2P Bit
    //
    ulTempccer &= ~TIMER_CCER_CC4P;
    ulTempccer |= (ulPolarity << 12);
     
    //
    // Write to TIMx CCER register
    //
    xHWREG(ulBase + TIMER_CCER) = ulTempccer;
}

//*****************************************************************************
//
//! \brief Enables or disables the TIM Capture Compare Channel x.
//!
//! \param ulBase is the base address of the Timer port. The timer can be 
//!        selected form timer 1 to 14, except 6, 7.
//! \param ulChannel is the specified timer channel.
//! \param ulCCx specifies the TIM Channel CCxE bit new state.
//!
//! The \e ulChannel parameter can be one of the values:
//! \b TIMER_CH_1, \b TIMER_CH_2, \b TIMER_CH_3, \b TIMER_CH_4.
//!
//! The \e ulCCx parameter can be one of the values:
//! \b TIMER_CH_ENABLE, \b TIMER_CH_DISABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCHConfigure(unsigned long ulBase, unsigned long ulChannel, 
                             unsigned long ulCCx)
{
    unsigned long ulTemp = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulChannel == TIMER_CH_1) || (ulChannel == TIMER_CH_2) ||
            (ulChannel == TIMER_CH_3) || (ulChannel == TIMER_CH_4)); 
    xASSERT((ulCCx == TIMER_CH_ENABLE) || 
            (ulCCx == TIMER_CH_DISABLE)); 
   
    ulTemp = (TIMER_CH_ENABLE << ((ulChannel -1) * 4)); 

    //
    // Reset the CCxE Bit
    //
    xHWREG(ulBase + TIMER_CCER) &= ~ulTemp; 
    
    //
    // Set the CCxE Bit
    //
    xHWREG(ulBase + TIMER_CCER) |= ulCCx << ((ulChannel -1) * 4); 
}

//*****************************************************************************
//
//! \brief Enables or disables the TIM Capture Compare Channel xN.
//!
//! \param ulBase is the base address of the Timer port. The timer can be 
//!        selected form timer 1 to 14, except 6, 7.
//! \param ulChannel is the specified timer channel.
//! \param ulCCxN specifies the TIM Channel CCxNE bit new state.
//!
//! The \e ulChannel parameter can be one of the values:
//! \b TIMER_CH_1, \b TIMER_CH_2, \b TIMER_CH_3 .
//!
//! The \e ulCCxN parameter can be one of the values:
//! \b TIMER_CHN_ENABLE, \b TIMER_CHN_DISABLE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCHNConfigure(unsigned long ulBase, unsigned long ulChannel, 
                             unsigned long ulCCxN)
{
    unsigned long ulTemp = 0;

    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulChannel == TIMER_CH_1) || (ulChannel == TIMER_CH_2) ||
            (ulChannel == TIMER_CH_3)); 
    xASSERT((ulCCxN == TIMER_CHN_ENABLE) || 
            (ulCCxN == TIMER_CHN_DISABLE)); 
   
    ulTemp = (TIMER_CHN_ENABLE << ((ulChannel -1) * 4)); 

    //
    // Reset the CCxE Bit
    //
    xHWREG(ulBase + TIMER_CCER) &= ~ulTemp; 
    
    //
    // Set the CCxE Bit
    //
    xHWREG(ulBase + TIMER_CCER) |= ulCCxN << ((ulChannel -1) * 4); 
}

//*****************************************************************************
//
//! \brief Initializes the TIMERx channel x output mode. 
//!
//! \param ulBase is the base address of the Timer port, it can be  1 to 14 
//!        except 6 and 7 .
//! \param ulOutputMode is Channel output compare mode selection.
//!
//! The \e ulOutputMode parameter can be one of the values:
//! \b TIMER_OCMODE_TIMING, \b TIMER_OCMODE_ACTIVE, \b TIMER_OCMODE_INACTIVE,
//! \b TIMER_OCMODE_TOGGLE, \b TIMER_OCMODE_FINACTIVE, \b TIMER_OCMODE_FACTIVE 
//!
//! \note This function disables the selected channel before changing the Output
//!            Compare Mode.User has to enable this channel using TimerCHConfigure 
//!            and TimerCHNConfigure functions.
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOCxModeSelect(unsigned long ulBase, unsigned long ulChannel, 
                             unsigned long ulOutputMode)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulChannel == TIMER_CH_1) || (ulChannel == TIMER_CH_2) ||
            (ulChannel == TIMER_CH_3) || (ulChannel == TIMER_CH_4)); 
    xASSERT((ulOutputMode == TIMER_OCMODE_TIMING) ||
            (ulOutputMode == TIMER_OCMODE_ACTIVE) ||
            (ulOutputMode == TIMER_OCMODE_INACTIVE) || 
            (ulOutputMode == TIMER_OCMODE_TOGGLE) ||
            (ulOutputMode == TIMER_OCMODE_FINACTIVE) ||
            (ulOutputMode == TIMER_OCMODE_FACTIVE));
    
    //
    // Disable the Channel: Reset the CCxE Bit
    //
    xHWREG(ulBase + TIMER_CCER) &= ~(0x00000001 << ((ulChannel -1) * 4));
    
    if((ulChannel == TIMER_CH_1) || (ulChannel == TIMER_CH_3))
    {
        //
        // Reset the OCxM bits in the CCMRx register
        //
        xHWREG(ulBase + TIMER_CCMR1 + (ulChannel / 3) * 4) &= ~TIMER_CCMR1_OC1M_M;

        //
        // Configure the OCxM bits in the CCMRx register
        //
        xHWREG(ulBase + TIMER_CCMR1 + (ulChannel / 3) * 4) |= ulOutputMode;
    }
    else
    {
        //
        // Reset the OCxM bits in the CCMRx register
        //
        xHWREG(ulBase + TIMER_CCMR1 + (ulChannel / 4) * 4) &= ~TIMER_CCMR1_OC2M_M;
        xHWREG(ulBase + TIMER_CCMR1 + (ulChannel / 4) * 4) |= (ulOutputMode << 8);
    }   
}

//*****************************************************************************
//
//! \brief Enables or Disables the TIMx Update event.
//!
//! \param ulBase is the base address of the Timer port, it can be  1 to 14.
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulUpdate == TIMER_UPDATE_EVENT_EN) || 
            (ulUpdate == TIMER_UPDATE_EVENT_DIS));
    
    if(ulUpdate == TIMER_UPDATE_EVENT_EN)
    {
        xHWREG(ulBase + TIMER_CR1) &= ~TIMER_CR1_UDIS;     
    }
    else
    {
        xHWREG(ulBase + TIMER_CR1) |= TIMER_CR1_UDIS; 
    }    
}

//*****************************************************************************
//
//! \brief Configures the TIMx Update Request Interrupt source.
//!
//! \param ulBase is the base address of the Timer port, it can be  1 to 14.
//! \param ulUpdateSource specifies the Update source.
//!
//! The \e ulUpdateSource parameter can be one of the values:
//! \b TIMER_UPDATESOURCE_GLOBAL, \b TIMER_UPDATESOURCE_REGULAR.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerUpdateRequestConfigure(unsigned long ulBase, unsigned long ulUpdateSource)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulUpdateSource == TIMER_UPDATESOURCE_GLOBAL) || 
            (ulUpdateSource == TIMER_UPDATESOURCE_REGULAR));
    
    if(ulUpdateSource == TIMER_UPDATESOURCE_GLOBAL)
    {
        xHWREG(ulBase + TIMER_CR1) &= ~TIMER_CR1_URS; 
    }
    else
    {
        xHWREG(ulBase + TIMER_CR1) |= TIMER_CR1_URS; 
    }        
                     
}

//*****************************************************************************
//
//! \brief Configures the TIMx Update Request Interrupt source.
//!
//! \param ulBase is the base address of the Timer port, it can be timer 1, 2, 
//!        3, 4, 5, 8.
//! \param ulHallSensor is the new state of the TIMx Hall sensor interface.
//!
//! The \e ulUpdateSource parameter can be one of the values:
//! \b TIMER_HALL_INTERFACE_EN, \b TIMER_HALL_INTERFACE_DIS.
//!
//! \note None
//!
//! \return None.
//
void 
TimerHallSensorSelect(unsigned long ulBase, unsigned long ulHallSensor)
{
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulHallSensor == TIMER_HALL_INTERFACE_EN) || 
            (ulHallSensor == TIMER_HALL_INTERFACE_DIS));

    if(ulHallSensor == TIMER_HALL_INTERFACE_DIS)
    {
        xHWREG(ulBase + TIMER_CR2) &= ~TIMER_CR2_TI1S;
    }
    else
    {
        xHWREG(ulBase + TIMER_CR2) |= TIMER_CR2_TI1S;
    }
  
}

//*****************************************************************************
//
//! \brief Disable the Single Pulse Mode.
//!
//! \param ulBase is the base address of the Timer port. it can be timer 1 to 14
//! \param ulConfigure is selection of Enable or Disable one pulse mode.
//!
//! The \e ulConfigure parameter can be one of the values:
//! \b TIMER_OPMODE_SINGLE, \b TIMER_OPMODE_REPETIVE.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOnePulseModeConfigure(unsigned long ulBase, unsigned long ulOPMode)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulOPMode == TIMER_OPMODE_SINGLE) ||
            (ulOPMode == TIMER_OPMODE_REPETIVE));
    
    //
    // Reset the OPM Bit
    //
    xHWREG(ulBase + TIMER_CR1) &= ~TIMER_CR1_OPM ;

    //
    // Configure the OPM Mode
    //
    xHWREG(ulBase + TIMER_CR1) |= ulOPMode ;
}

//*****************************************************************************
//
//! \brief Selects the TIMx Trigger Output Mode.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1, 2, 3,
//!        4, 5, 6, 7, 8, 9, 12.
//! \param ulSelect is selection of trigger output source.
//!
//! The \e ulSelect parameter can be one of the values:
//! \b TIMER_TRGOSRC_RESET, \b TIMER_TRGOSRC_ENABLE, \b TIMER_TRGOSRC_UPDATE,
//! \b TIMER_TRGOSRC_CH1CC, \b TIMER_TRGOSRC_CH1OREF, \b TIMER_TRGOSRC_CH2OREF,
//! \b TIMER_TRGOSRC_CH3OREF, \b TIMER_TRGOSRC_CH4OREF.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerOutputSrcSelect(unsigned long ulBase, unsigned long ulSelect)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));
    xASSERT((ulSelect == TIMER_TRGOSRC_RESET) || 
            (ulSelect == TIMER_TRGOSRC_ENABLE) ||
            (ulSelect == TIMER_TRGOSRC_UPDATE) ||
            (ulSelect == TIMER_TRGOSRC_CH1CC) ||
            (ulSelect == TIMER_TRGOSRC_CH1OREF) ||
            (ulSelect == TIMER_TRGOSRC_CH2OREF) || 
            (ulSelect == TIMER_TRGOSRC_CH3OREF) || 
            (ulSelect == TIMER_TRGOSRC_CH4OREF));
    
    //
    // Reset the MMS Bits
    //
    xHWREG(ulBase + TIMER_CR2) &= ~TIMER_CR2_MMS_M;

    //
    // Select the TRGO source
    //
    xHWREG(ulBase + TIMER_CR2) |= ulSelect;
}

//*****************************************************************************
//
//! \brief Selects slave mode of the Timer.
//!
//! \param ulBase is the base address of the Timer port. The timer can be 
//!        selected 1, 2, 3, 4, 5, 8, 9, 12 .
//! \param ulSelect is selection of slave mode.
//!
//! The \e ulSelect parameter can be one of the values:
//! \b TIMER_SMSEL_RESET, \b TIEMR_SMSEL_GATED,
//! \b TIMER_SMSEL_TRIGGER, \b TIMER_SMSEL_EXTERNAL1.
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) ||
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));
    xASSERT((ulSelect == TIMER_SMSEL_RESET) || 
            (ulSelect == TIEMR_SMSEL_GATED) ||
            (ulSelect == TIMER_SMSEL_TRIGGER) ||
            (ulSelect == TIMER_SMSEL_EXTERNAL1)); 
    
    //
    // Reset the SMS Bits 
    //
    xHWREG(ulBase + TIMER_SMCR) &= ~TIMER_SMCR_SMS_M;

    //
    // Select the Slave Mode
    //
    xHWREG(ulBase + TIMER_SMCR) |= ulSelect;
    
}

//*****************************************************************************
//
//! \brief  Enables or Disables the master & slave Timer synchronous function.
//!
//! \param ulBase is the base address of the Timer port. The timer can be 
//!        selected 1, 2, 3, 4, 5, 8, 9, 12 .
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) ||
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));
    xASSERT((ulConfigure == TIMER_SYNC_ENABLE) ||
            (ulConfigure == TIMER_SYNC_DISABLE));
    
    //
    // Reset the MSM Bit
    //
    xHWREG(ulBase + TIMER_SMCR) &= ~TIMER_SMCR_MSM;
    xHWREG(ulBase + TIMER_SMCR) |= ulConfigure;
    
}

//*****************************************************************************
//
//! \brief Sets counter register value.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1 to 14.
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulCounter >= 0) && (ulCounter <= 0x0000FFFF));
    
    xHWREG(ulBase + TIMER_CNT) = ulCounter; 
}

//*****************************************************************************
//
//! \brief Get the counter value of TIMERx.
//!
//! \param ulBase is the base address of the Timer port.It can be timer 1 to 14.
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    
    return (xHWREG(ulBase + TIMER_CNT));
}

//*****************************************************************************
//
//! \brief Set counter reload register value.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1 to 14.
//! \param ulARRValue is the counter reload register new value. It is a value 
//! between 0 and Ox0000FFFF.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerAutoReloadSet(unsigned long ulBase, unsigned long ulARRValue)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulARRValue >= 0) && (ulARRValue <= 0x0000FFFF));
    
    xHWREG(ulBase + TIMER_ARR) = ulARRValue;    
}

//*****************************************************************************
//
//! \brief Get counter reload register value.
//!
//! \param ulBase is the base address of the Timer port. It can be timer 1 to 14.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
TimerARRReloadGet(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    
    return (xHWREG(ulBase + TIMER_ARR));
}

//*****************************************************************************
//
//! \brief Sets the TIMx Capture Compare1 Register value.
//!
//! \param ulBase is the base address of the Timer port.It can be timer 1 to 14
//!        except timer 6, 7.
//! \param ulCompare1 specifies the Capture Compare1 register new value.
//! between 0 and Ox0000FFFF.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCompare1Set(unsigned long ulBase, unsigned long ulCompare1)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulCompare1 >= 0) && (ulCompare1 <= 0x0000FFFF));
    
    xHWREG(ulBase + TIMER_CCR1) = ulCompare1;    
}

//*****************************************************************************
//
//! \brief Sets the TIMx Capture Compare2 Register value.
//!
//! \param ulBase is the base address of the Timer port.It can be timer 1, 2, 3, 
//!        4, 5, 8, 9, 12 .
//! \param ulCompare2 specifies the Capture Compare1 register new value.
//! between 0 and Ox0000FFFF.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCompare2Set(unsigned long ulBase, unsigned long ulCompare2)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));
    xASSERT((ulCompare2 >= 0) && (ulCompare2 <= 0x0000FFFF));
    
    xHWREG(ulBase + TIMER_CCR2) = ulCompare2;    
}

//*****************************************************************************
//
//! \brief Sets the TIMx Capture Compare3 Register value.
//!
//! \param ulBase is the base address of the Timer port.It can be timer 1, 2, 3, 
//!        4, 5, 8 .
//! \param ulCompare3 specifies the Capture Compare1 register new value.
//! between 0 and Ox0000FFFF.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCompare3Set(unsigned long ulBase, unsigned long ulCompare3)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulCompare3 >= 0) && (ulCompare3 <= 0x0000FFFF));
    
    xHWREG(ulBase + TIMER_CCR3) = ulCompare3;    
}

//*****************************************************************************
//
//! \brief Sets the TIMx Capture Compare4 Register value.
//!
//! \param ulBase is the base address of the Timer port.It can be timer 1, 2, 3, 
//!        4, 5, 8 .
//! \param ulCompare3 specifies the Capture Compare1 register new value.
//! between 0 and Ox0000FFFF.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCompare4Set(unsigned long ulBase, unsigned long ulCompare4)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulCompare4 >= 0) && (ulCompare4 <= 0x0000FFFF));
    
    xHWREG(ulBase + TIMER_CCR4) = ulCompare4;    
}

//*****************************************************************************
//
//! \brief Sets clock division value of the Timer.
//!
//! \param ulBase is the base address of the Timer port.It can be timer 1 to 14
//!        except timer 6, 7.
//! \param ulDiv is the clock division value
//!
//! The \e ulDiv parameter can be one of the values:
//! \b TIMER_CLKDIV_0, \b TIMER_CLKDIV_2, \b TIMER_CLKDIV_4.
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulDiv == TIMER_CLKDIV_0) || (ulDiv == TIMER_CLKDIV_2) || 
            (ulDiv == TIMER_CLKDIV_4));
    
    //
    // Reset the CKD Bits
    //
    xHWREG(ulBase + TIMER_CR1) &= ~TIMER_CR1_CKD_M;

    //
    // Set the CKD value
    //
    xHWREG(ulBase + TIMER_CR1) |= ulDiv;
    
}

//*****************************************************************************
//
//! \brief Gets the TIMx Input Capture 1 value.
//!
//! \param ulBase is the base address of the Timer port.It can be timer 1 to 14
//!        except timer 6, 7.
//!
//! \note None
//!
//! \return Value of CCR1 register.
//
//*****************************************************************************
unsigned long 
TimerCapture1Get(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));

    return xHWREG(ulBase + TIMER_CCR1);    
}

//*****************************************************************************
//
//! \brief Gets the TIMx Input Capture 2 value.
//!
//! \param ulBase is the base address of the Timer port.It can be timer 1, 2, 3, 
//!        4, 5, 8, 9, 12 .
//!
//! \note None
//!
//! \return Value of CCR2 register.
//
//*****************************************************************************
unsigned long 
TimerCapture2Get(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE));

    return xHWREG(ulBase + TIMER_CCR2);    
}

//*****************************************************************************
//
//! \brief Gets the TIMx Input Capture 3 value.
//!
//! \param ulBase is the base address of the Timer port.It can be timer 1, 2, 3, 
//!        4, 5, 8 .
//!
//! \note None
//!
//! \return Value of CCR3 register.
//
//*****************************************************************************
unsigned long 
TimerCapture3Get(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));

    return xHWREG(ulBase + TIMER_CCR3);    
}

//*****************************************************************************
//
//! \brief Gets the TIMx Input Capture 4 value.
//!
//! \param ulBase is the base address of the Timer port.It can be timer 1, 2, 3, 
//!        4, 5, 8 .
//!
//! \note None
//!
//! \return Value of CCR4 register.
//
//*****************************************************************************
unsigned long 
TimerCapture4Get(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));

    return xHWREG(ulBase + TIMER_CCR4);    
}

//*****************************************************************************
//
//! \brief Get the  prescaler value of TIMERx.
//!
//! \param ulBase is the base address of the Timer port.It can be timer 1 to 14.
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) ||
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) ||  
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    
    return (xHWREG(ulBase + TIMER_PSC));
}

//*****************************************************************************
//
//! \brief Configures the TIMx event to be generate by software. 
//!
//! \param ulBase is the base address of the Timer port, it can be selected form 
//!        timer 1 to 14.  
//! \param ulEventSource specifies the event source.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! \b TIMER_EVENT_UEV, \b TIMER_EVENT_CH1CC, \b TIMER_EVENT_CH2CC, 
//! \b TIMER_EVENT_CH3CC, \b TIMER_EVENT_CH4CC,  \b TIMER_EVENT_COM,
//! \b TIMER_EVENT_TEV,   \b TIMER_EVENT_BRK .
//!
//! \note - TIM6 and TIM7 can only generate an update event. 
//!       - TIM_EventSource_COM and TIM_EventSource_Break are used only with 
//!         TIM1 and TIM8.  
//!
//! \return None.
//
//*****************************************************************************
void 
TimerEventGenerate(unsigned long ulBase, unsigned long ulEventSource)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE)); 
    xASSERT((ulEventSource == TIMER_EVENT_UEV) || 
            (ulEventSource == TIMER_EVENT_CH1CC) ||
            (ulEventSource == TIMER_EVENT_CH2CC) ||
            (ulEventSource == TIMER_EVENT_CH3CC) ||
            (ulEventSource == TIMER_EVENT_CH4CC) ||
            (ulEventSource == TIMER_EVENT_COM) ||
            (ulEventSource == TIMER_EVENT_TEV) ||
            (ulEventSource == TIMER_EVENT_BRK));

    xHWREG(ulBase + TIMER_EGR) = ulEventSource;
}

//*****************************************************************************
//
//! \brief Configures the TIMx event to be generate by software. 
//!
//! \param ulBase is the base address of the Timer port, it can be timer 1, 2, 3,
//!        4, 5, 8.  
//! \param ulDMABase specifies DMA Base address.
//! \param ulDMABurstLength specifies DMA Burst length.
//! 
//! The \e ulDMABase parameter is one of the following values:
//! \b TIMER_DMABASE_CR1, \b TIMER_DMABASE_CR2, \b TIMER_DMABASE_SMCR, 
//! \b TIMER_DMABASE_DIER, \b TIMER_DMABASE_SR,  \b TIMER_DMABASE_EGR,
//! \b TIMER_DMABASE_CCMR1, \b TIMER_DMABASE_CCMR2, \b TIMER_DMABASE_CCER
//! \b TIMER_DMABASE_CNT, \b TIMER_DMABASE_PSC, \b TIMER_DMABASE_ARR, 
//! \b TIMER_DMABASE_RCR, \b TIMER_DMABASE_CCR1, \b TIMER_DMABASE_CCR2, 
//! \b TIMER_DMABASE_CCR3, \b TIMER_DMABASE_CCR4, \b TIMER_DMABASE_BDTR, 
//! \b TIMER_DMABASE_DCR.
//!
//! The \e ulDMABurstLength parameter is one of the following values:
//! \b TIMER_DMABURSTLEN_1, \b TIMER_DMABURSTLEN_2, \b TIMER_DMABURSTLEN_3, 
//! \b TIMER_DMABURSTLEN_4, \b TIMER_DMABURSTLEN_5,  \b TIMER_DMABURSTLEN_6,
//! \b TIMER_DMABURSTLEN_7, \b TIMER_DMABURSTLEN_8, \b TIMER_DMABURSTLEN_9
//! \b TIMER_DMABURSTLEN_10, \b TIMER_DMABURSTLEN_11, \b TIMER_DMABURSTLEN_12, 
//! \b TIMER_DMABURSTLEN_13, \b TIMER_DMABURSTLEN_14, \b TIMER_DMABURSTLEN_15, 
//! \b TIMER_DMABURSTLEN_16, \b TIMER_DMABURSTLEN_17, \b TIMER_DMABURSTLEN_18.
//!
//! \note - TIM6 and TIM7 can only generate an update event. 
//!       - TIM_EventSource_COM and TIM_EventSource_Break are used only with 
//!         TIM1 and TIM8.  
//!
//! \return None.
//
//*****************************************************************************
void 
TimerDMAConfigure(unsigned long ulBase, unsigned long ulDMABase, 
                  unsigned long ulDMABurstLength)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulDMABase == TIMER_DMABASE_CR1) || 
            (ulDMABase == TIMER_DMABASE_CR2) ||
            (ulDMABase == TIMER_DMABASE_SMCR) ||
            (ulDMABase == TIMER_DMABASE_DIER) ||
            (ulDMABase == TIMER_DMABASE_SR) ||
            (ulDMABase == TIMER_DMABASE_EGR) ||
            (ulDMABase == TIMER_DMABASE_CCMR1) ||
            (ulDMABase == TIMER_DMABASE_CCMR2) ||
            (ulDMABase == TIMER_DMABASE_CCER) ||
            (ulDMABase == TIMER_DMABASE_CNT) ||
            (ulDMABase == TIMER_DMABASE_ARR) ||
            (ulDMABase == TIMER_DMABASE_RCR) ||
            (ulDMABase == TIMER_DMABASE_CCR1) ||
            (ulDMABase == TIMER_DMABASE_CCR2) ||
            (ulDMABase == TIMER_DMABASE_CCR3) ||
            (ulDMABase == TIMER_DMABASE_CCR4) ||
            (ulDMABase == TIMER_DMABASE_BDTR) ||
            (ulDMABase == TIMER_DMABASE_DCR));
    xASSERT((ulDMABurstLength == TIMER_DMABURSTLEN_1) || 
            (ulDMABurstLength == TIMER_DMABURSTLEN_2) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_3) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_3) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_4) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_5) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_6) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_7) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_8) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_9) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_10) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_11) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_12) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_13) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_14) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_15) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_16) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_17) ||
            (ulDMABurstLength == TIMER_DMABURSTLEN_18));

       xHWREG(ulBase + TIMER_DCR) = (ulDMABase | ulDMABurstLength);
}

//*****************************************************************************
//
//! \brief Enables or disables the TIMx's DMA Requests. It can be timer 1, 2, 3,
//!        4, 5, 6, 7, 8.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulDMASource specifies the DMA Request sources.
//! 
//! The \e ulDMASource parameter is the logical OR of the following values:
//! \b TIMER_DMA_UPDATA, \b TIMER_DMA_CH1CC, \b TIMER_DMA_CH2CC, 
//! \b TIMER_DMA_CH3CC,  \b TIMER_DMA_CH4CC, \b TIMER_DMA_COM, 
//! \b TIMER_DMA_TRIGGER.
//!
//! \return None
//
//*****************************************************************************
void 
TimerDMAEnable(unsigned long ulBase, unsigned long ulDMASource)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulDMASource == TIMER_DMA_UPDATA) || 
            (ulDMASource == TIMER_DMA_CH1CC) ||
            (ulDMASource == TIMER_DMA_CH2CC) || 
            (ulDMASource == TIMER_DMA_CH3CC) ||
            (ulDMASource == TIMER_DMA_CH4CC) ||
            (ulDMASource == TIMER_DMA_COM) ||
            (ulDMASource == TIMER_DMA_TRIGGER));
            
    //
    //    Enable the DMA sources
    //
    xHWREG(ulBase + TIMER_DIER) |= ulDMASource;              
}

//*****************************************************************************
//
//! \brief Disable or disables the TIMx's DMA Requests. It can be timer 1, 2, 3,
//!        4, 5, 6, 7, 8.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulDMASource specifies the DMA Request sources.
//! 
//! The \e ulDMASource parameter is the logical OR of the following values:
//! \b TIMER_DMA_UPDATA, \b TIMER_DMA_CH1CC, \b TIMER_DMA_CH2CC, 
//! \b TIMER_DMA_CH3CC,  \b TIMER_DMA_CH4CC, \b TIMER_DMA_COM, 
//! \b TIMER_DMA_TRIGGER.
//!
//! \return None
//
//*****************************************************************************
void 
TimerDMADisable(unsigned long ulBase, unsigned long ulDMASource)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE));
    xASSERT((ulDMASource == TIMER_DMA_UPDATA) || 
            (ulDMASource == TIMER_DMA_CH1CC) ||
            (ulDMASource == TIMER_DMA_CH2CC) || 
            (ulDMASource == TIMER_DMA_CH3CC) ||
            (ulDMASource == TIMER_DMA_CH4CC) ||
            (ulDMASource == TIMER_DMA_COM) ||
            (ulDMASource == TIMER_DMA_TRIGGER));
            
    //
    //    Enable the DMA sources
    //
    xHWREG(ulBase + TIMER_DIER) &= ~ulDMASource;     
}


//*****************************************************************************
//
//! \brief Checks whether the specified TIM flag is set or not.
//!
//! \param ulBase is the base address of the Timer port. Timer 1 to 14 can be 
//!        selected
//! \param ulFlag is the specified Flag.
//!
//! The \e ulFlag parameter can be one of the values:
//! \b TIMER_FLAG_UPDATE,  \b TIMER_FLAG_CH1CC, \b TIMER_FLAG_CH2CC,
//! \b TIMER_FLAG_CH3CC,   \b TIMER_FLAG_CH4CC, \b TIMER_FLAG_COM,
//! \b TIMER_FLAG_TRIGGER, \b TIMER_FLAG_BREAK, \b TIMER_FLAG_CH1OF, 
//! \b TIMER_FLAG_CH2OF,   \b TIMER_FLAG_CH3OF, \b TIMER_FLAG_CH4OF.
//!
//! \note - TIM6 and TIM7 can only generate an update interrupt.
//!       - TIM9, TIM12 and TIM15 can have only TIM_IT_Update, TIM_IT_CC1,
//!         TIM_IT_CC2 or TIM_IT_Trigger. 
//!       - TIM10, TIM11, TIM13, TIM14, TIM16 and TIM17 can have TIM_IT_Update 
//!         or TIM_IT_CC1.
//!       - TIM_IT_Break is used only with TIM1, TIM8.
//!       - TIM_IT_COM is used only with TIM1, TIM8.
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) ||
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) ||  
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulFlag == TIMER_FLAG_UPDATE) || (ulFlag == TIMER_FLAG_CH1CC) ||
            (ulFlag == TIMER_FLAG_CH2CC) || (ulFlag == TIMER_FLAG_CH3CC) ||
            (ulFlag == TIMER_FLAG_CH4CC) || (ulFlag == TIMER_FLAG_COM) ||
            (ulFlag == TIMER_FLAG_TRIGGER) || (ulFlag == TIMER_FLAG_BREAK) ||
            (ulFlag == TIMER_FLAG_CH1OF) || (ulFlag == TIMER_FLAG_CH2OF)||
            (ulFlag == TIMER_FLAG_CH3OF) || (ulFlag == TIMER_FLAG_CH4OF));
    
    if((xHWREG(ulBase + TIMER_SR) & ulFlag))
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
//! \param ulBase is the base address of the Timer port. Timer 1 to 14 can be 
//!        selected
//! \param ulFlag is the specified Flag.
//!
//! The \e ulFlag parameter can be one of the values:
//! \b TIMER_FLAG_UPDATE,  \b TIMER_FLAG_CH1CC, \b TIMER_FLAG_CH2CC,
//! \b TIMER_FLAG_CH3CC,   \b TIMER_FLAG_CH4CC, \b TIMER_FLAG_COM,
//! \b TIMER_FLAG_TRIGGER, \b TIMER_FLAG_BREAK, \b TIMER_FLAG_CH1OF, 
//! \b TIMER_FLAG_CH2OF,   \b TIMER_FLAG_CH3OF, \b TIMER_FLAG_CH4OF.
//!
//! \note - TIM6 and TIM7 can only generate an update flag.
//!       - TIM9, TIM12 can have only TIMER_FLAG_UPDATE, TIMER_FLAG_CH1CC,
//!         TIMER_FLAG_CH2CC or TIMER_FLAG_TRIGGER. 
//!       - TIM10, TIM11, TIM13, TIM14 can have TIMER_FLAG_UPDATE 
//!         or TIMER_FLAG_CH1CC.
//!       - TIMER_FLAG_BREAK is used only with TIM1, TIM8.
//!       - TIMER_FLAG_COM is used only with TIM1, TIM8.
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) ||
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) ||  
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
    xASSERT((ulFlag == TIMER_FLAG_CH1CC) || (ulFlag == TIMER_FLAG_CH2CC) ||
            (ulFlag == TIMER_FLAG_CH3CC) || (ulFlag == TIMER_FLAG_CH4CC) ||
            (ulFlag == TIMER_FLAG_CH1OF) || (ulFlag == TIMER_FLAG_CH2OF) ||
            (ulFlag == TIMER_FLAG_CH3OF) || (ulFlag == TIMER_FLAG_CH4OF) ||
            (ulFlag == TIMER_FLAG_UPDATE) || (ulFlag == TIMER_FLAG_BREAK) ||
            (ulFlag == TIMER_FLAG_COM) || (ulFlag == TIMER_FLAG_TRIGGER));
    
    //
    // RC_W0 Software can read as well as clear this bit by writing 0. 
    // Writing ¡®1¡¯ has no effect on the bit value
    //
    xHWREG(ulBase + TIMER_SR) = ~ulFlag;
}



//*****************************************************************************
//
//! \brief Init interrupts callback for the timer.
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulIntType is the interrupt type.
//! \param xtTimerCallback is callback for the timer.
//!
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! \b TIMER_INT_CH1CC, \b TIMER_INT_CH2CC, \b TIMER_INT_CH3CC, 
//! \b TIMER_INT_CH4CC, \b TIMER_INT_UEV1,  \b TIMER_INT_TEV,
//! \b TIMER_INT_COM,   \b TIMER_INT_BRK .
//!
//! \note - TIM6 and TIM7 can only generate an update interrupt.
//!       - TIM9, TIM12 and TIM15 can have only TIM_INT_UPDATE, TIM_INT_CH1CC,
//!         TIMER_INT_CH2CC or TIMER_INT_TEV. 
//!       - TIM10, TIM11, TIM13, TIM14 can have TIMER_INT_UEV 
//!         or TIMER_INT_CH1CC.
//!       - TIMER_INT_BRK is used only with TIM1, TIM8.
//!       - TIMER_INT_COM is used only with TIM1, TIM8.
//!
//! Init interrupts callback for the timer.
//!
//! \return None.
//
//*****************************************************************************
void 
TimerIntCallbackInit(unsigned long ulBase, unsigned long ulIntType,
                     xtEventCallback xtTimerCallback)
{
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE)); 
    xASSERT((ulIntType == TIMER_INT_CH1CC) || (ulIntType == TIMER_INT_CH2CC) ||
            (ulIntType == TIMER_INT_CH3CC) || (ulIntType == TIMER_INT_CH4CC) ||
            (ulIntType == TIMER_INT_UEV) || (ulIntType == TIMER_INT_TEV) ||
            (ulIntType == TIMER_INT_COM) || (ulIntType == TIMER_INT_BRK));

    //
    // Init the interrupts callback.
    //
    switch(ulBase)
    {
        case TIM1_BASE:
            if(ulIntType == TIMER_INT_BRK)
            {
                g_pfnTimerHandlerCallbacks[0] = xtTimerCallback;
            }
            else if(ulIntType == TIMER_INT_UEV)
            {
                g_pfnTimerHandlerCallbacks[1] = xtTimerCallback;
            }
            else if(ulIntType == TIMER_INT_TEV)
            {
                g_pfnTimerHandlerCallbacks[2] = xtTimerCallback;
            }
            else if(ulIntType == TIMER_INT_COM)
            {
                g_pfnTimerHandlerCallbacks[3] = xtTimerCallback;
            }
            else
            {
                g_pfnTimerHandlerCallbacks[4] = xtTimerCallback;
            }
            break;
        case TIM2_BASE:
            g_pfnTimerHandlerCallbacks[5] = xtTimerCallback;
            break;
        case TIM3_BASE:
            g_pfnTimerHandlerCallbacks[6] = xtTimerCallback;
            break;
        case TIM4_BASE:
            g_pfnTimerHandlerCallbacks[7] = xtTimerCallback;
            break;
        case TIM5_BASE:
            g_pfnTimerHandlerCallbacks[8] = xtTimerCallback;
            break;
        case TIM6_BASE:
            g_pfnTimerHandlerCallbacks[9] = xtTimerCallback;
            break;
        case TIM7_BASE:
            g_pfnTimerHandlerCallbacks[10] = xtTimerCallback;
            break;
        case TIM8_BASE:
            if(ulIntType == TIMER_INT_BRK)
            {
                g_pfnTimerHandlerCallbacks[11] = xtTimerCallback;
            }
            else if(ulIntType == TIMER_INT_UEV)
            {
                g_pfnTimerHandlerCallbacks[12] = xtTimerCallback;
            }
            else if(ulIntType == TIMER_INT_TEV)
            {
                g_pfnTimerHandlerCallbacks[13] = xtTimerCallback;
            }
            else if(ulIntType == TIMER_INT_COM)
            {
                g_pfnTimerHandlerCallbacks[14] = xtTimerCallback;
            }
            else
            {
                g_pfnTimerHandlerCallbacks[15] = xtTimerCallback;
            }
            break;
        case TIM9_BASE:
            g_pfnTimerHandlerCallbacks[16] = xtTimerCallback;
            break;
        case TIM10_BASE:
            g_pfnTimerHandlerCallbacks[17] = xtTimerCallback;
            break;
        case TIM11_BASE:
            g_pfnTimerHandlerCallbacks[18] = xtTimerCallback;
            break;
        case TIM12_BASE:
            g_pfnTimerHandlerCallbacks[19] = xtTimerCallback;
            break;
        case TIM13_BASE:
            g_pfnTimerHandlerCallbacks[20] = xtTimerCallback;
            break;
        case TIM14_BASE:
            g_pfnTimerHandlerCallbacks[21] = xtTimerCallback;
            break;
    }
}

//*****************************************************************************
//
//! \brief Enables the specified interrupts of the Timer. 
//!
//! \param ulBase is the base address of the Timer port, it can be selected form 
//!        timer 1 to 14.  
//! \param ulIntFlags is the interrupt type of the Timer port.
//!
//! This function is to enable The Timer counter interrupt.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! \b TIMER_INT_CH1CC, \b TIMER_INT_CH2CC, \b TIMER_INT_CH3CC, 
//! \b TIMER_INT_CH4CC, \b TIMER_INT_UEV1,  \b TIMER_INT_TEV,
//! \b TIMER_INT_COM,   \b TIMER_INT_BRK .
//!
//! \note - TIM6 and TIM7 can only generate an update interrupt.
//!       - TIM9, TIM12 and TIM15 can have only TIM_INT_UPDATE, TIM_INT_CH1CC,
//!         TIMER_INT_CH2CC or TIMER_INT_TEV. 
//!       - TIM10, TIM11, TIM13, TIM14 can have TIMER_INT_UEV 
//!         or TIMER_INT_CH1CC.
//!       - TIMER_INT_BRK is used only with TIM1, TIM8.
//!       - TIMER_INT_COM is used only with TIM1, TIM8.
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE)); 
    xASSERT((ulIntFlags == TIMER_INT_CH1CC) || (ulIntFlags == TIMER_INT_CH2CC) ||
            (ulIntFlags == TIMER_INT_CH3CC) || (ulIntFlags == TIMER_INT_CH4CC) ||
            (ulIntFlags == TIMER_INT_UEV) || (ulIntFlags == TIMER_INT_TEV) ||
            (ulIntFlags == TIMER_INT_COM) || (ulIntFlags == TIMER_INT_BRK));
    
    xHWREG(ulBase + TIMER_DIER) |= ulIntFlags;
}

//*****************************************************************************
//
//! \brief Disable the specified interrupts of the Timer. 
//!
//! \param ulBase is the base address of the Timer port, it can be selected form 
//!        timer 1 to 14.  
//! \param ulIntFlags is the interrupt type of the Timer port.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! \b TIMER_INT_CH1CC, \b TIMER_INT_CH2CC, \b TIMER_INT_CH3CC, 
//! \b TIMER_INT_CH4CC, \b TIMER_INT_UEV1,  \b TIMER_INT_TEV,
//! \b TIMER_INT_COM,   \b TIMER_INT_BRK .
//!
//! \note - TIM6 and TIM7 can only generate an update interrupt.
//!       - TIM9, TIM12 and TIM15 can have only TIM_INT_UPDATE, TIM_INT_CH1CC,
//!         TIMER_INT_CH2CC or TIMER_INT_TEV. 
//!       - TIM10, TIM11, TIM13, TIM14 can have TIMER_INT_UEV 
//!         or TIMER_INT_CH1CC.
//!       - TIMER_INT_BRK is used only with TIM1, TIM8.
//!       - TIMER_INT_COM is used only with TIM1, TIM8.
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE)); 
    xASSERT((ulIntFlags == TIMER_INT_CH1CC) || (ulIntFlags == TIMER_INT_CH2CC) ||
            (ulIntFlags == TIMER_INT_CH3CC) || (ulIntFlags == TIMER_INT_CH4CC) ||
            (ulIntFlags == TIMER_INT_UEV) || (ulIntFlags == TIMER_INT_TEV) ||
            (ulIntFlags == TIMER_INT_COM) || (ulIntFlags == TIMER_INT_BRK));
    
    xHWREG(ulBase + TIMER_DIER) &= ~ulIntFlags;
}

//*****************************************************************************
//
//! \brief Get The Timer counter interrupt Status. 
//!
//! \param ulBase is the base address of the Timer port. it can be selected form 
//!        timer 1 to 14.
//! \param ulIntFlags is the interrupt type of the Timer port.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! \b TIMER_INT_UEV, \b TIMER_INT_CH1CC, \b TIMER_INT_CH2CC, \b TIMER_INT_TEV,
//! \b TIMER_INT_CH3CC, \b TIMER_INT_CH4CC, \b TIMER_INT_COM, \b TIMER_INT_COM, 
//! \b TIMER_INT_BRK.
//!
//! \note - TIM6 and TIM7 can only generate an update interrupt.
//!       - TIM9, TIM12 and TIM15 can have only TIM_INT_UPDATE, TIM_INT_CH1CC,
//!         TIMER_INT_CH2CC or TIMER_INT_TEV. 
//!       - TIM10, TIM11, TIM13, TIM14 can have TIMER_INT_UEV 
//!         or TIMER_INT_CH1CC.
//!       - TIMER_INT_BRK is used only with TIM1, TIM8.
//!       - TIMER_INT_COM is used only with TIM1, TIM8.
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE)); 
    xASSERT((ulIntFlags == TIMER_INT_CH1CC) || (ulIntFlags == TIMER_INT_CH2CC) ||
            (ulIntFlags == TIMER_INT_CH3CC) || (ulIntFlags == TIMER_INT_CH4CC) ||
            (ulIntFlags == TIMER_INT_UEV) || (ulIntFlags == TIMER_INT_TEV) ||
            (ulIntFlags == TIMER_INT_COM) || (ulIntFlags == TIMER_INT_BRK));

    ulIntStatus = xHWREG(ulBase + TIMER_SR) & ulIntFlags;
    ulIntEnable = xHWREG(ulBase + TIMER_DIER) & ulIntFlags;
    
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
//! \param ulBase is the base address of the Timer port. it can be selected form 
//!        timer 1 to 14.
//! \param ulIntFlags is the interrupt type of the Timer port.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! \b TIMER_INT_UEV, \b TIMER_INT_CH1CC, \b TIMER_INT_CH2CC, \b TIMER_INT_TEV,
//! \b TIMER_INT_CH3CC, \b TIMER_INT_CH4CC, \b TIMER_INT_COM, \b TIMER_INT_COM, 
//! \b TIMER_INT_BRK.
//!
//! \note - TIM6 and TIM7 can only generate an update interrupt.
//!       - TIM9, TIM12 and TIM15 can have only TIM_INT_UPDATE, TIM_INT_CH1CC,
//!         TIMER_INT_CH2CC or TIMER_INT_TEV. 
//!       - TIM10, TIM11, TIM13, TIM14 can have TIMER_INT_UEV 
//!         or TIMER_INT_CH1CC.
//!       - TIMER_INT_BRK is used only with TIM1, TIM8.
//!       - TIMER_INT_COM is used only with TIM1, TIM8.1, \b TIMER_INT_TEV.
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
    xASSERT((ulBase == TIM1_BASE) || (ulBase == TIM2_BASE) || 
            (ulBase == TIM3_BASE) || (ulBase == TIM4_BASE) || 
            (ulBase == TIM6_BASE) || (ulBase == TIM7_BASE) || 
            (ulBase == TIM5_BASE) || (ulBase == TIM8_BASE) || 
            (ulBase == TIM9_BASE) || (ulBase == TIM10_BASE) || 
            (ulBase == TIM11_BASE) || (ulBase == TIM12_BASE) || 
            (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE)); 
    xASSERT((ulIntFlags == TIMER_INT_CH1CC) || (ulIntFlags == TIMER_INT_CH2CC) ||
            (ulIntFlags == TIMER_INT_CH3CC) || (ulIntFlags == TIMER_INT_CH4CC) ||
            (ulIntFlags == TIMER_INT_UEV) || (ulIntFlags == TIMER_INT_TEV) ||
            (ulIntFlags == TIMER_INT_COM) || (ulIntFlags == TIMER_INT_BRK));
    
    xHWREG(ulBase + TIMER_SR) &= ~ulIntFlags;

}
