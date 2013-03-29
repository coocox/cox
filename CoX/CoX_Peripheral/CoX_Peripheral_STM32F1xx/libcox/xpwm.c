//*****************************************************************************
//
//! \file xpwm.c
//! \brief Driver for the PWM
//! \version V2.2.1.0
//! \date 6/25/2012
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
#include "xpwm.h"

//*****************************************************************************
//
// Some arrays are PWM Callback function points
//
//*****************************************************************************
static xtEventCallback g_pfnPWMHandlerCallbacks[12]={0};

//*****************************************************************************
//
//! \internal
//! \brief Checks a PWM base address.
//!
//! \param ulBase is the base address of the PWM port.
//!
//! This function determines if a PWM port base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef xDEBUG
static xtBoolean
PWMBaseValid(unsigned long ulBase)
{
    return((ulBase == TIM1_BASE) || (ulBase == TIM8_BASE) ||
           (ulBase == TIM2_BASE) || (ulBase == TIM3_BASE) ||
           (ulBase == TIM4_BASE) || (ulBase == TIM5_BASE) ||
           (ulBase == TIM9_BASE) || (ulBase == TIM12_BASE) ||
           (ulBase == TIM10_BASE) || (ulBase == TIM11_BASE) ||
           (ulBase == TIM13_BASE) || (ulBase == TIM14_BASE));
}
#endif

#if (TIM1_FUNCTION_SELECT == TIM_PWM)
//*****************************************************************************
//
//! \brief The PWMA default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default PWMA IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a 
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
TIM1CCIntHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = xPWMA_BASE;
    
    //
    // Clear the PWMA INT Flag
    //
 
    ulPWMStastus = xHWREG(ulBase + TIMER_SR);
    xHWREG(ulBase + TIMER_SR) &= ~ulPWMStastus;
    
    if (g_pfnPWMHandlerCallbacks[0] != 0)        
    {
        if(ulPWMStastus != 0)
        {
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
    }
}
#endif

#if (STM32F1xx_DEVICE == STM32F10X_XL || STM32F1xx_DEVICE == STM32F10X_HD_VL)
#if (TIM8_FUNCTION_SELECT == TIM_PWM)
//*****************************************************************************
//
//! \brief The PWMB default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default PWMB IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a 
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
TIM8CCIntHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = xPWMB_BASE;
    
    //
    // Clear the PWMA INT Flag
    //        
    ulPWMStastus = xHWREG(ulBase + TIMER_SR) & 0x1E;
    xHWREG(ulBase + TIMER_SR) &= ~ulPWMStastus;
    
    if (g_pfnPWMHandlerCallbacks[1] != 0)        
    {
        if(ulPWMStastus != 0)
        {
            g_pfnPWMHandlerCallbacks[1](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
    }
}
#endif
#endif

#if (TIM2_FUNCTION_SELECT == TIM_PWM)
//*****************************************************************************
//
//! \brief The PWMC default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default PWMC IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a 
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
TIM2IntHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = xPWMC_BASE;
    
    //
    // Clear the PWMA INT Flag
    //        
    ulPWMStastus = xHWREG(ulBase + TIMER_SR) & 0x1E;
    xHWREG(ulBase + TIMER_SR) &= ~ulPWMStastus;
    
    if (g_pfnPWMHandlerCallbacks[2] != 0)        
    {
        if(ulPWMStastus != 0)
        {
            g_pfnPWMHandlerCallbacks[2](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
    }
}
#endif

#if (TIM3_FUNCTION_SELECT == TIM_PWM)
//*****************************************************************************
//
//! \brief The PWMD default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default PWMD IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a 
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
TIM3IntHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = xPWMD_BASE;
    
    //
    // Clear the PWMA INT Flag
    //        
    ulPWMStastus = xHWREG(ulBase + TIMER_SR) & 0x1E;
    xHWREG(ulBase + TIMER_SR) &= ~ulPWMStastus;
    
    if (g_pfnPWMHandlerCallbacks[3] != 0)        
    {
        if(ulPWMStastus != 0)
        {
            g_pfnPWMHandlerCallbacks[3](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
    }
}
#endif

#if (TIM4_FUNCTION_SELECT == TIM_PWM)
//*****************************************************************************
//
//! \brief The PWME default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default PWME IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a 
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
TIM4IntHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = xPWME_BASE;
    
    //
    // Clear the PWMA INT Flag
    //        
    ulPWMStastus = xHWREG(ulBase + TIMER_SR) & 0x1E;
    xHWREG(ulBase + TIMER_SR) &= ~ulPWMStastus;
    
    if (g_pfnPWMHandlerCallbacks[4] != 0)        
    {
        if(ulPWMStastus != 0)
        {
            g_pfnPWMHandlerCallbacks[4](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
    }
}
#endif

#if (TIM5_FUNCTION_SELECT == TIM_PWM)
//*****************************************************************************
//
//! \brief The PWMF default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default PWMF IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a 
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
TIM5IntHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = xPWMF_BASE;
    
    //
    // Clear the PWMA INT Flag
    //        
    ulPWMStastus = xHWREG(ulBase + TIMER_SR) & 0x1E;
    xHWREG(ulBase + TIMER_SR) &= ~ulPWMStastus;
    
    if (g_pfnPWMHandlerCallbacks[5] != 0)        
    {
        if(ulPWMStastus != 0)
        {
            g_pfnPWMHandlerCallbacks[5](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
    }
}
#endif

#if (STM32F1xx_DEVICE == STM32F10X_XL)
#if (TIM9_FUNCTION_SELECT == TIM_PWM)
//*****************************************************************************
//
//! \brief The PWMG default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default PWMG IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a 
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
TIM1BRKTIM9IntHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = xPWMG_BASE;
    
    //
    // Clear the PWMA INT Flag
    //        
    ulPWMStastus = xHWREG(ulBase + TIMER_SR) & 0x1E;
    xHWREG(ulBase + TIMER_SR) &= ~ulPWMStastus;
    
    if (g_pfnPWMHandlerCallbacks[6] != 0)        
    {
        if(ulPWMStastus != 0)
        {
            g_pfnPWMHandlerCallbacks[6](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
    }
}
#endif

#if (TIM12_FUNCTION_SELECT == TIM_PWM)
//*****************************************************************************
//
//! \brief The PWMH default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default PWMH IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a 
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
TIM8BRKTIM12IntHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = xPWMH_BASE;
    
    //
    // Clear the PWMA INT Flag
    //        
    ulPWMStastus = xHWREG(ulBase + TIMER_SR) & 0x1E;
    xHWREG(ulBase + TIMER_SR) &= ~ulPWMStastus;
    
    if (g_pfnPWMHandlerCallbacks[7] != 0)        
    {
        if(ulPWMStastus != 0)
        {
            g_pfnPWMHandlerCallbacks[7](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
    }
}
#endif

#if (TIM10_FUNCTION_SELECT == TIM_PWM)
//*****************************************************************************
//
//! \brief The PWMI default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default PWMI IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a 
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
TIM1UPTIM10IntHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = xPWMI_BASE;
    
    //
    // Clear the PWMA INT Flag
    //        
    ulPWMStastus = xHWREG(ulBase + TIMER_SR) & 0x1E;
    xHWREG(ulBase + TIMER_SR) &= ~ulPWMStastus;
    
    if (g_pfnPWMHandlerCallbacks[8] != 0)        
    {
        if(ulPWMStastus != 0)
        {
            g_pfnPWMHandlerCallbacks[8](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
    }
}
#endif

#if (TIM11_FUNCTION_SELECT == TIM_PWM)
//*****************************************************************************
//
//! \brief The PWMJ default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default PWMJ IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a 
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
TIM1TRGCOMTIM11IntHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = xPWMJ_BASE;
    
    //
    // Clear the PWMA INT Flag
    //        
    ulPWMStastus = xHWREG(ulBase + TIMER_SR) & 0x1E;
    xHWREG(ulBase + TIMER_SR) &= ~ulPWMStastus;
    
    if (g_pfnPWMHandlerCallbacks[9] != 0)        
    {
        if(ulPWMStastus != 0)
        {
            g_pfnPWMHandlerCallbacks[9](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
    }
}
#endif

#if (TIM13_FUNCTION_SELECT == TIM_PWM)
//*****************************************************************************
//
//! \brief The PWMK default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default PWMK IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a 
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
TIM8UPTIM13IntHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = xPWMK_BASE;
    
    //
    // Clear the PWMA INT Flag
    //        
    ulPWMStastus = xHWREG(ulBase + TIMER_SR) & 0x1E;
    xHWREG(ulBase + TIMER_SR) &= ~ulPWMStastus;
    
    if (g_pfnPWMHandlerCallbacks[10] != 0)        
    {
        if(ulPWMStastus != 0)
        {
            g_pfnPWMHandlerCallbacks[10](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
    }
}
#endif

#if (TIM14_FUNCTION_SELECT == TIM_PWM)
//*****************************************************************************
//
//! \brief The PWML default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default PWML IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a 
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
TIM8TRGCOMTIM14IntHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = xPWML_BASE;
    
    //
    // Clear the PWMA INT Flag
    //        
    ulPWMStastus = xHWREG(ulBase + TIMER_SR) & 0x1E;
    xHWREG(ulBase + TIMER_SR) &= ~ulPWMStastus;
    
    if (g_pfnPWMHandlerCallbacks[11] != 0)        
    {
        if(ulPWMStastus != 0)
        {
            g_pfnPWMHandlerCallbacks[11](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
    }
}
#endif
#endif

//*****************************************************************************
//
//! \brief Initialize and configure the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulConfig is the configuration of PWM channel.
//! \param ulDir is the timer counter direction.
//!
//! This function is to initialize and configure channel of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3.
//!
//! The \e ulConfig parameter is the logical OR of four values: The PWM mode,
//! Inverter or not,and use dead zero or not and dead zone length. 
//! \b PWM_OUTPUT_INVERTER_EN,\b PWM_OUTPUT_INVERTER_DIS is to enable Inverter or not.
//! \b PWM_DEAD_ZONE_EN, \b PWM_DEAD_ZONE_DIS is to enable dead zone Generator or not.
//! 
//! The dead zone length should be set at the 16~23 bits of the ulConfig.
//!
//! \note When Dead-Zone Generator is enabled, the pair of PWM0 and PWM1 
//! becomes a complementary pair for PWM group A and the pair of PWM4 and 
//! PWM5 becomes a complementary pair for PWM group B.
//!
//! \return None.
//
//*****************************************************************************
void 
xPWMInitConfigure(unsigned long ulBase, unsigned long ulChannel, 
                                        unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));

    //
    // Set PWM Mode
    //
    xHWREG(ulBase + TIMER_CCMR1 + (ulChannel/2)*4) |= (TIMER_CCMR1_OC1M_PWMM2 <<
                                                      (ulChannel%2)*8);
    if((ulBase==xPWMA_BASE) || (ulBase==xPWMB_BASE))
    {
        //
        // Dead-Zone Setting
        //
        xHWREG(ulBase + TIMER_CCER) &= ~(PWM_DEAD_ZONE_EN << (ulChannel*4));
        xHWREG(ulBase + TIMER_CCER) |= ((PWM_DEAD_ZONE_EN & ulConfig) << (ulChannel*4));

        xHWREG(ulBase + TIMER_BDTR) &= ~TIMER_BDTR_DTG_M;
        xHWREG(ulBase + TIMER_BDTR) |= ((TIMER_BDTR_DTG_M<<16) & ulConfig)>>16;
    
        //
        // Inverter Setting
        //
        if(PWM_OUTPUT_INVERTER_EN & ulConfig)
        {
            xHWREG(ulBase + TIMER_BDTR) |= TIMER_BDTR_MOE;  	
            xHWREG(ulBase + TIMER_CCER) &= ~(PWM_DEAD_ZONE_EN << (ulChannel*4));
            xHWREG(ulBase + TIMER_CCER) |= (PWM_DEAD_ZONE_EN << (ulChannel*4));
            xHWREG(ulBase + TIMER_BDTR) &= ~PWM_OUTPUT_INVERTER_EN;
            xHWREG(ulBase + TIMER_BDTR) |= PWM_OUTPUT_INVERTER_EN;
        }
    }
}

//*****************************************************************************
//
//! \brief Initialize and configure the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulConfig is the configuration of PWM channel.
//! \param ulDir is the timer counter direction.
//!
//! This function is to initialize and configure channel of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3.
//!
//! The \e ulMode parameter can be values:
//! \b PWM_OM_1, \b PWM_OM_2.
//!
//! The \e ulDir parameter can be values:
//! \b PWM_CNT_MODE_UP, \b PWM_CNT_MODE_DOWN, \b PWM_CNT_MODE_CENTER_1,
//! \b PWM_CNT_MODE_CENTER_2, \b PWM_CNT_MODE_CENTER_3.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMInitConfigure(unsigned long ulBase, unsigned long ulChannel,
                 unsigned long ulMode, unsigned long ulDir)
{
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));

    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));

    xASSERT((ulMode == PWM_OM_1) || (ulMode == PWM_OM_2));

    xASSERT((ulDir == PWM_CNT_MODE_UP)   || (ulDir == PWM_CNT_MODE_CENTER_1) ||
            (ulDir == PWM_CNT_MODE_DOWN) || (ulDir == PWM_CNT_MODE_CENTER_2) ||
            (ulDir == PWM_CNT_MODE_CENTER_3));

    //
    // Selcet the count direction
    //
    xHWREG(ulBase + TIMER_CR1) &= ~(PWM_CNT_MODE_DOWN|PWM_CNT_MODE_CENTER_3);
    xHWREG(ulBase + TIMER_CR1) |= ulDir;
    
    //
    // Set PWM Mode
    //
    xHWREG(ulBase + TIMER_CCMR1 + (ulChannel/2)*4) &= ~(PWM_OM_2 << (ulChannel%2)*8);  
    xHWREG(ulBase + TIMER_CCMR1 + (ulChannel/2)*4) |= (ulMode << (ulChannel%2)*8);  
}

//*****************************************************************************
//
//! \brief Sets counter reload register value.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulCRRValue is the counter reload register new value. It is a value 
//! between 0 and Ox0000FFFF.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMARRSet(unsigned long ulBase, unsigned long ulCRRValue)
{
    //
    // Check the arguments
    //
    xASSERT(PWMBaseValid(ulBase));
    xASSERT((ulCRRValue >= 0) && (ulCRRValue <= 0x0000FFFF));
    
    xHWREG(ulBase + TIMER_ARR) &= ~TIMER_ARR_CH3IMAE_M;  
    xHWREG(ulBase + TIMER_ARR) = ulCRRValue;    
}

//*****************************************************************************
//
//! \brief Get counter reload register value.
//!
//! \param ulBase is the base address of the PWM port.
//!
//!
//! \return counter reload register value.
//
//*****************************************************************************
unsigned long  
PWMARRGet(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT(PWMBaseValid(ulBase));
    
    return (xHWREG(ulBase + TIMER_ARR) & TIMER_ARR_CH3IMAE_M);
}

//*****************************************************************************
//
//! \brief Set the PWM duty of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulDuty is the duty of PWM channel.
//!
//! This function is to set the PWM duty of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3.
//!
//! The \e ulDuty parameter can be values:  duty > 0 && duty <= 100. 
//!
//! \note Duty should not be 0;
//!
//! \return None.
//
//*****************************************************************************
void 
PWMDutySet(unsigned long ulBase, unsigned long ulChannel, 
           unsigned char ulDuty)
{
    unsigned long ulCMRData;
    
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));
    xASSERT(((ulDuty > 0) || (ulDuty <= 100)));

    ulCMRData = (PWMARRGet(ulBase) *  ulDuty) / 100;
    if ((PWMARRGet(ulBase) *  ulDuty) / 100 == 0)
    {
        ulCMRData = 0;
    }

    xHWREG(ulBase + TIMER_CCR1 + ulChannel * 4) &= ~TIMER_CCR1_CCR1_M;
    xHWREG(ulBase + TIMER_CCR1 + ulChannel * 4) |= ulCMRData;
}

//*****************************************************************************
//
//! \brief Get the PWM duty of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to get the PWM duty of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3.
//!
//! \return the Actual duty of PWM.
//
//*****************************************************************************
unsigned long
PWMDutyGet(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulCMRData;
    unsigned long ulCNRData;
    
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));
    xASSERT((ulChannel >= 0) || (ulChannel <= 3));

    ulCNRData = PWMARRGet(ulBase);
    ulCMRData = xHWREG(ulBase + TIMER_CCR1 + ulChannel * 4);
    ulChannel = (ulCMRData + 1) * 100 / (ulCNRData + 1);
    
    //
    // Return the Actual duty of PWM
    //
    return ulChannel;
}

//*****************************************************************************
//
//! \brief Enable the PWM interrupt of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//!
//! This function is to enable the PWM interrupt of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3.
//!
//! The \e ulIntType parameter can be values:
//! \b PWM_INT_CHXCC, \b PWM_INT_UEV1.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMIntEnable(unsigned long ulBase, unsigned long ulChannel,
                         unsigned long ulIntType)
{
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));
    xASSERT((ulIntType == PWM_INT_CHXCC) || (ulIntType == PWM_INT_UEV1));

    if (ulIntType == PWM_INT_UEV1)
    {
        xHWREG(ulBase + TIMER_DIER) |= PWM_INT_UEV1; 
    }
    else
    {
        xHWREG(ulBase + TIMER_DIER) |= (PWM_INT_CHXCC << ulChannel);
    }
}

//*****************************************************************************
//
//! \brief Disable the PWM interrupt of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//!
//! This function is to enable the PWM interrupt of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3.
//!
//! //! The \e ulIntType parameter can be values:
//! \b PWM_INT_CHXCC, \b PWM_INT_UEV1.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMIntDisable(unsigned long ulBase, unsigned long ulChannel,
                          unsigned long ulIntType)
{   
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));
    xASSERT((ulIntType == PWM_INT_CHXCC) || (ulIntType == PWM_INT_UEV1));

    if (ulIntType == PWM_INT_UEV1)
    {
        xHWREG(ulBase + TIMER_DIER) &= ~PWM_INT_UEV1; 
    }
    else
    {
        xHWREG(ulBase + TIMER_DIER) &= ~(PWM_INT_CHXCC << ulChannel);
    } 
}

//*****************************************************************************
//
//! \brief Get the PWM interrupt flag of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//!
//! This function is to get the PWM interrupt flag of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3.
//!
//! The \e ulIntType parameter can be values:
//! \b PWM_INT_CHXCC, \b PWM_INT_UEV1.
//!
//! \return None.
//
//*****************************************************************************
xtBoolean 
PWMIntFlagGet(unsigned long ulBase, unsigned long ulChannel,
                               unsigned long ulIntType)
{
    unsigned long ulIntStatus;
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));
    xASSERT((ulIntType == PWM_INT_CHXCC) || (ulIntType == PWM_INT_UEV1));

    if (ulIntType == PWM_INT_UEV1)
    {
        ulIntStatus = xHWREG(ulBase + TIMER_SR) & ulIntType;
        if(ulIntStatus != 0)
        {
            return xtrue;
        }
    }
    else
    {
        ulIntStatus = xHWREG(ulBase + TIMER_SR) & (PWM_INT_CHXCC << ulChannel);
        if(ulIntStatus != 0)
        {
            return xtrue;
        }
    }  
    
    return xfalse;
}

//*****************************************************************************
//
//! \brief Clear the PWM interrupt flag of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//!
//! This function is to get the PWM interrupt flag of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3.
//!
//! The \e ulIntType parameter can be values:
//! \b PWM_INT_CHXCC, \b PWM_INT_UEV1.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMIntFlagClear(unsigned long ulBase, unsigned long ulChannel,
                            unsigned long ulIntType)
{
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));
    xASSERT((ulIntType == PWM_INT_CHXCC) || (ulIntType == PWM_INT_UEV1));

    if (ulIntType == PWM_INT_UEV1)
    {
        xHWREG(ulBase + TIMER_SR) &= ~ulIntType;
    }
    else
    {
        xHWREG(ulBase + TIMER_SR) &= ~(PWM_INT_CHXCC << ulChannel);
    } 
}

//*****************************************************************************
//
//! \brief Start the PWM of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMStart(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));

    xHWREG(ulBase + TIMER_CR1) |= TIMER_CR1_CEN;
    xHWREG(ulBase + TIMER_BDTR) |= TIMER_BDTR_MOE;
}

//*****************************************************************************
//
//! \brief Stop the PWM of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMStop(unsigned long ulBase)
{   
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));

    xHWREG(ulBase + TIMER_CR1) &= ~TIMER_CR1_CEN;
    xHWREG(ulBase + TIMER_BDTR) &= ~TIMER_BDTR_MOE;
}

//*****************************************************************************
//
//! \brief Set the PWM frequency of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulFrequency is the PWM frequency of PWM channel.
//!
//! This function is to set the PWM frequency of the PWM module.
//!
//! The \e ulFrequency parameter can be values: Any values ,ulFrequency > 0 &&
//! ulFrequency < PWM module input clock.
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
unsigned long 
PWMFrequencySet(unsigned long ulBase, unsigned long ulFrequency)
{
    unsigned long ulFrepDiv;
    unsigned long ulActualFrep;
    unsigned long ulPreScale, ulTemp;
    unsigned short usCNRData;
    
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));
    xASSERT((ulFrequency > 0) || (ulFrequency <= SysCtlHClockGet()));

    if((ulBase==TIM1_BASE) || (ulBase==TIM8_BASE) || (ulBase==TIM9_BASE)||
    	 (ulBase==TIM10_BASE) || (ulBase==TIM11_BASE))
    {
        ulTemp = (xHWREG(RCC_CFGR) & RCC_CFGR_PPRE2_M) >> RCC_CFGR_PPRE2_S;
        if((ulTemp != 4) || (ulTemp != 5) || (ulTemp != 6) || (ulTemp != 7))
        {
            ulFrepDiv =  SysCtlAPB2ClockGet() / ulFrequency;
        }
        else
        {
            ulFrepDiv =  (2*SysCtlAPB2ClockGet()) / ulFrequency;
        }
    }
    else
    {
        ulTemp = (xHWREG(RCC_CFGR) & RCC_CFGR_PPRE1_M) >> RCC_CFGR_PPRE1_S;
        if((ulTemp != 4) || (ulTemp != 5) || (ulTemp != 6) || (ulTemp != 7))
        {
            ulFrepDiv =  SysCtlAPB1ClockGet() / ulFrequency;
        }
        else
        {
            ulFrepDiv =  (2*SysCtlAPB1ClockGet()) / ulFrequency;
        }
    }
    ulPreScale = 1;
    while((ulFrepDiv / ulPreScale) > 0xFFFF)
    {
        ulPreScale++;
    }
    
    if(ulPreScale > 0xFFFF)
    {
        return 0;
    }
    
    usCNRData = ulFrepDiv / ulPreScale;

    xHWREG(ulBase + TIMER_ARR) = usCNRData;
    xHWREG(ulBase + TIMER_PSC) = ulPreScale - 1;

    if((ulBase==TIM1_BASE) || (ulBase==TIM8_BASE) || (ulBase==TIM9_BASE)||
    	 (ulBase==TIM10_BASE) || (ulBase==TIM11_BASE))
    {
        ulTemp = (xHWREG(RCC_CFGR) & RCC_CFGR_PPRE2_M) >> RCC_CFGR_PPRE2_S;
        if((ulTemp != 4) || (ulTemp != 5) || (ulTemp != 6) || (ulTemp != 7))
        {
            ulActualFrep = SysCtlAPB2ClockGet() / usCNRData / ulPreScale;
        }
        else
        {
            ulActualFrep = (2*SysCtlAPB2ClockGet()) / usCNRData / ulPreScale;
        }
    }
    else
    {
        ulTemp = (xHWREG(RCC_CFGR) & RCC_CFGR_PPRE1_M) >> RCC_CFGR_PPRE1_S;
        if((ulTemp != 4) || (ulTemp != 5) || (ulTemp != 6) || (ulTemp != 7))
        {
            ulActualFrep = SysCtlAPB1ClockGet() / usCNRData / ulPreScale;
        }
        else
        {
            ulActualFrep = (2*SysCtlAPB1ClockGet()) / usCNRData / ulPreScale;
        }
    }
    
    return ulActualFrep;
}

//*****************************************************************************
//
//! \brief get the PWM frequency of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//!
//! \note None
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
unsigned long 
PWMFrequencyGet(unsigned long ulBase)
{
    unsigned long ulPreScale, ulTemp;
    unsigned short usCNRData, ulActualFrep;  
    
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));


    ulPreScale = xHWREG(ulBase + TIMER_PSC) + 1;
    usCNRData = xHWREG(ulBase + TIMER_ARR);

    if((ulBase==TIM1_BASE) || (ulBase==TIM8_BASE) || (ulBase==TIM9_BASE)||
    	 (ulBase==TIM10_BASE) || (ulBase==TIM11_BASE))
    {
        ulTemp = (xHWREG(RCC_CFGR) & RCC_CFGR_PPRE2_M) >> RCC_CFGR_PPRE2_S;
        if((ulTemp != 4) || (ulTemp != 5) || (ulTemp != 6) || (ulTemp != 7))
        {
            ulActualFrep = SysCtlAPB2ClockGet() / usCNRData / ulPreScale;
        }
        else
        {
            ulActualFrep = (2*SysCtlAPB2ClockGet()) / usCNRData / ulPreScale;
        }
    }
    else
    {
        ulTemp = (xHWREG(RCC_CFGR) & RCC_CFGR_PPRE1_M) >> RCC_CFGR_PPRE1_S;
        if((ulTemp != 4) || (ulTemp != 5) || (ulTemp != 6) || (ulTemp != 7))
        {
            ulActualFrep = SysCtlAPB1ClockGet() / usCNRData / ulPreScale;
        }
        else
        {
            ulActualFrep = (2*SysCtlAPB1ClockGet()) / usCNRData / ulPreScale;
        }
    }

    return ulActualFrep;
}

//*****************************************************************************
//
//! \brief Set the PWM frequency of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulConfig is the configuration of PWM channel's frequency.
//!
//! This function is to set the PWM frequency of the PWM module.
//!
//! The \e ulConfig parameter is the logical OR of two values: The PreScale
//! value, the PWM Counter Register value.
//!
//! \note The PWM Counter Register value should be set at the 16~31 bits of the ulConfig.
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
unsigned long 
PWMFrequencyConfig(unsigned long ulBase, unsigned long ulConfig)
{
    unsigned long ulPreScale, ulTemp, ulCNRData, ulActualFrep;
    
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));
    
    ulPreScale = ulConfig & 0xFFFF;
    ulCNRData = ((ulConfig & 0xFFFF0000) >> 16);
    
    xHWREG(ulBase + TIMER_ARR) = ulCNRData;
    xHWREG(ulBase + TIMER_PSC) = ulPreScale - 1;

    if((ulBase==TIM1_BASE) || (ulBase==TIM8_BASE) || (ulBase==TIM9_BASE)||
    	 (ulBase==TIM10_BASE) || (ulBase==TIM11_BASE))
    {
        ulTemp = (xHWREG(RCC_CFGR) & RCC_CFGR_PPRE2_M) >> RCC_CFGR_PPRE2_S;
        if((ulTemp != 4) || (ulTemp != 5) || (ulTemp != 6) || (ulTemp != 7))
        {
            ulActualFrep = SysCtlAPB2ClockGet() / ulCNRData / ulPreScale;
        }
        else
        {
            ulActualFrep = (2*SysCtlAPB2ClockGet()) / ulCNRData / ulPreScale;
        }
    }
    else
    {
        ulTemp = (xHWREG(RCC_CFGR) & RCC_CFGR_PPRE1_M) >> RCC_CFGR_PPRE1_S;
        if((ulTemp != 4) || (ulTemp != 5) || (ulTemp != 6) || (ulTemp != 7))
        {
            ulActualFrep = SysCtlAPB1ClockGet() / ulCNRData / ulPreScale;
        }
        else
        {
            ulActualFrep = (2*SysCtlAPB1ClockGet()) / ulCNRData / ulPreScale;
        }
    }

    return ulActualFrep; 
}

//*****************************************************************************
//
//! \brief Enable the corresponding channel. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! \note 
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
void 
PWMOutputEnable(unsigned long ulBase, unsigned long ulChannel)
{
    
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));
    
    //
    // Enable the corresponding channel
    //
    xHWREG(ulBase + TIMER_CR1) |= TIMER_CR1_ARR;
    xHWREG(ulBase + TIMER_CCMR1 + (ulChannel/2)*4) |= (TIMER_CCMR1_OC1PE <<
                                                          (ulChannel%2) * 8);

    xHWREG(ulBase + TIMER_CCER) |= (5 << (ulChannel * 4));
}

//*****************************************************************************
//
//! \brief Disable the corresponding channel. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
void 
PWMOutputDisable(unsigned long ulBase, unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));

    //
    // Disable the corresponding channel
    //
    xHWREG(ulBase + TIMER_CR1) &= ~TIMER_CR1_ARR;
    xHWREG(ulBase + TIMER_CCMR1 + (ulChannel/2)*4) &= ~(TIMER_CCMR1_OC1PE <<
                                                       (ulChannel%2)*8);
    xHWREG(ulBase + TIMER_CCER) &= ~(1 << (ulChannel*4));
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the specified PWM Port.
//!
//! \param ulPort is the base address of the PWM port.
//! \param xtPWMCallback is callback for the specified PWM Port.
//!
//! Init interrupts callback for the specified PWM Port.
//!
//! \return None.
//
//*****************************************************************************
void
PWMIntCallbackInit(unsigned long ulBase, 
                    xtEventCallback xtPWMCallback)
{
    //
    // Check the arguments.
    //
    xASSERT(PWMBaseValid(ulBase));

    switch(ulBase)
    {
        case xPWMA_BASE:
        {
            g_pfnPWMHandlerCallbacks[0] = xtPWMCallback;
            break;
        }
        case xPWMB_BASE:
        {
            g_pfnPWMHandlerCallbacks[1] = xtPWMCallback;
            break;
        }
        case xPWMC_BASE:
        {
            g_pfnPWMHandlerCallbacks[2] = xtPWMCallback;
            break;
        }
        case xPWMD_BASE:
        {
            g_pfnPWMHandlerCallbacks[3] = xtPWMCallback;
            break;
        }
        case xPWME_BASE:
        {
            g_pfnPWMHandlerCallbacks[4] = xtPWMCallback;
            break;
        }
        case xPWMF_BASE:
        {
            g_pfnPWMHandlerCallbacks[5] = xtPWMCallback;
            break;
        }
				case xPWMG_BASE:
        {
            g_pfnPWMHandlerCallbacks[6] = xtPWMCallback;
            break;
        }
				case xPWMH_BASE:
        {
            g_pfnPWMHandlerCallbacks[7] = xtPWMCallback;
            break;
        }
				case xPWMI_BASE:
        {
            g_pfnPWMHandlerCallbacks[8] = xtPWMCallback;
            break;
        }
				case xPWMJ_BASE:
        {
            g_pfnPWMHandlerCallbacks[9] = xtPWMCallback;
            break;
        }
				case xPWMK_BASE:
        {
            g_pfnPWMHandlerCallbacks[10] = xtPWMCallback;
            break;
        }
				case xPWML_BASE:
        {
            g_pfnPWMHandlerCallbacks[11] = xtPWMCallback;
            break;
        }
        default:
            break;
    }
}
