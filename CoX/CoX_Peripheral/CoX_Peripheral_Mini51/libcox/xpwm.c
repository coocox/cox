//*****************************************************************************
//
//! \file xpwm.c
//! \brief Driver for the PWM
//! \version V2.1.1.0
//! \date 1/31/2012
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
#include "xhw_pwm.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xpwm.h"



//*****************************************************************************
//
// An array is PWM Callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnPWMHandlerCallbacks[1] = {0};
static xtEventCallback g_pfnFBHandlerCallbacks[1] = {0};

//*****************************************************************************
//
//! \brief The PWMA default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default PWMA IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM Duty or Period interrupt.And the other one show which channel have
//! a  interrupt,bit0 in ulPWMStastus shows PWM_CHANNEL0,bit1 in ulPWMStastus 
//! shows PWM_CHANNEL1,bit2 in ulPWMStastus shows PWM_CHANNEL2 and bit3 in 
//! ulPWMStastus shows PWM_CHANNEL3.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMAIntHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = PWMA_BASE;
    
    //
    // Clear the PWMA INT Flag
    //
    ulPWMStastus = xHWREG(ulBase + PWM_PIIR) & 0x3F3F;
    xHWREG(ulBase + PWM_PIIR) = ulPWMStastus;

    if (g_pfnPWMHandlerCallbacks[0] != 0)
    {
        if(ulPWMStastus != 0)
        {
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
    }
}

//*****************************************************************************
//
//! \brief The PWM external fault brake default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default PWM external fault brake IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM external fault brake interrupt.
//!
//! \return None.
//
//*****************************************************************************
void 
FBIntHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = PWMA_BASE;
    
    //
    // Clear the fault break INT Flag
    //
    ulPWMStastus = xHWREG(ulBase + PWM_PIIR) & 0x30000;
    xHWREG(ulBase + PWM_PIIR) = ulPWMStastus;
    
    if (g_pfnFBHandlerCallbacks[0] != 0)
    {
        if(ulPWMStastus != 0)
        {
            g_pfnFBHandlerCallbacks[0](0, PWM_EVENT_FB, ulPWMStastus, 0);
        }
    }
}

//*****************************************************************************
//
//! \internal
//! \brief Get the PWM module's clock. 
//!
//! \param ulBase is the base address of the PWM port.
//!
//! This function is to get the PWM module's clock.
//!
//! \note To set PWRCON[1:0] to select 12 MHz or 32 KHz crystal clock.
//!
//! \return the PWM module's input clock.
//
//*****************************************************************************
static unsigned long 
PWMClockGet(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulTemp;
    unsigned long ulPWMFreq;

    ulTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulTemp >= 0) || (ulTemp <= 5)));
    switch(ulChannel)
    {
        case PWM_CHANNEL0:
        case PWM_CHANNEL1:
            ulTemp = ((xHWREG(SYSCLK_CLKSEL1) & SYSCLK_CLKSEL1_PWM01_M) >>
                      SYSCLK_CLKSEL1_PWM01_S);
            break;
            
        case PWM_CHANNEL2:
        case PWM_CHANNEL3:
            ulTemp = ((xHWREG(SYSCLK_CLKSEL1) & SYSCLK_CLKSEL1_PWM23_M) >>
                      SYSCLK_CLKSEL1_PWM23_S);
            break;
            
        case PWM_CHANNEL4:
        case PWM_CHANNEL5:
            ulTemp = ((xHWREG(SYSCLK_CLKSEL2) & SYSCLK_CLKSEL2_PWM45_M) >>
                      SYSCLK_CLKSEL2_PWM45_S);
            break;
            
        default:
            break;
    }

    if (ulTemp == 2)
    {
        ulPWMFreq = SysCtlHClockGet();
    }
    
    return ulPWMFreq;
}

//*****************************************************************************
//
//! \brief Initialize and configure the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulConfig is the configuration of PWM channel.
//!
//! This function is to initialize and configure channel of the PWM module.
//!
//! The \e ulChannel parameter must be values:0~5.
//!
//! The \e ulConfig parameter is the logical OR of four values: The PWM mode,
//! Inverter or not,and use dead zero or not, dead zone length,Operating Mode
//! and Aligned Type.
//! \b PWM_ONE_SHOT_MODE,\b PWM_TOGGLE_MODE is the mode selecet.
//! \b PWM_OUTPUT_INVERTER_EN,
//! \b PWM_OUTPUT_INVERTER_DIS is to enable Inverter or not.\b PWM_DEAD_ZONE_EN
//! \b PWM_DEAD_ZONE_DIS is to enable dead zone Generator or not.
//! \b PWM_INDEPENDENT_MODE,\b PWM_COMPLEMENTARY_MODE,\b PWM_SYNCHRONIZED_MODE
//! \b PWM_GROUP_MODE is the Operating Mode Selection.
//! \b PWM_CENTER_ALLIGNED_TYPE,\b PWM_EDGE_ALLIGNED_TYPE is the  Aligned Type 
//! Selection.
//! The dead zone length will be set at the 16~23 bits of the ulConfig.
//! \note When Dead-Zone Generator is enabled, the pair of PWM0 and PWM1 
//! becomes a complementary pair for PWM and so on,at the same time, the pwm
//! operating mode should select "Complementary mode".
//!
//! \return None.
//
//*****************************************************************************
void 
PWMInitConfigure(unsigned long ulBase, unsigned long ulChannel,
                 unsigned long ulConfig)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xASSERT(((ulConfig & PWM_PCR_CH0INV) == PWM_OUTPUT_INVERTER_EN) || 
            ((ulConfig & PWM_PCR_CH0INV) == PWM_OUTPUT_INVERTER_DIS));
    
    xASSERT(((ulConfig & PWM_PCR_CH0MOD) == PWM_ONE_SHOT_MODE) || 
            ((ulConfig & PWM_PCR_CH0MOD) == PWM_TOGGLE_MODE));
    
    xASSERT(((ulConfig & PWM_DEAD_ZONE_EN) == PWM_DEAD_ZONE_EN) || 
            ((ulConfig & PWM_DEAD_ZONE_EN) == PWM_DEAD_ZONE_DIS));
            
    xASSERT(((ulConfig & PWM_INDEPENDENT_MODE) == PWM_INDEPENDENT_MODE) || 
            ((ulConfig & PWM_SYNCHRONIZED_MODE) == PWM_SYNCHRONIZED_MODE) || 
            ((ulConfig & PWM_COMPLEMENTARY_MODE) == PWM_COMPLEMENTARY_MODE));
            
    xASSERT(((ulConfig & PWM_CENTER_ALLIGNED_TYPE) == PWM_CENTER_ALLIGNED_TYPE) || 
            ((ulConfig & PWM_EDGE_ALLIGNED_TYPE) == PWM_EDGE_ALLIGNED_TYPE));
            
    xASSERT(((ulConfig & PWM_GROUP_MODE) == PWM_GROUP_MODE));
    
    SysCtlPeripheralReset(SYSCTL_PERIPH_PWM01);

    xHWREG(ulBase + PWM_PCR) |= ((ulConfig & 0xF) << (ulChannelTemp * 4))
                                | (ulConfig & 0xF0000000);
    
    if (ulConfig & PWM_DEAD_ZONE_EN)
    {
        xHWREG(ulBase + PWM_PCR) |= (PWM_DEAD_ZONE_EN << (ulChannelTemp / 2));
        xHWREG(ulBase + PWM_PDZIR) &= ~(PWM_PDZIR_DZI01_M << 
                                       (ulChannelTemp / 2) * 8);
        ulConfig = ulConfig >> 16;
        xHWREG(ulBase + PWM_PDZIR) |= ((ulConfig & PWM_PDZIR_DZI01_M) << 
                                      (ulChannelTemp / 2) * 8);
    }
}

//*****************************************************************************
//
//! \brief Set the PWM frequency of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulFrequency is the PWM frequency of PWM channel.
//!
//! This function is to set the PWM frequency of the PWM module.
//!
//! The \e ulChannel parameter must be values:0~5
//!
//! The \e ulFrequency parameter can be values: Any values ,ulFrequency > 0 &&
//! ulFrequency < PWM module input clock.
//!
//! \return the Actual Frequency of PWM, if return 0 .
//
//*****************************************************************************
unsigned long 
PWMFrequencySet(unsigned long ulBase, unsigned long ulChannel, 
                unsigned long ulFrequency)
{
    unsigned long ulChannelTemp;
    unsigned long ulFrepDiv;
    unsigned long ulActualFrep;
    unsigned short usCNRData;
    unsigned char ucDivider;
    unsigned short usPreScale;
    unsigned char i;
    
    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));
    xASSERT(((ulFrequency > 0) || 
            (ulFrequency <= PWMClockGet(ulBase, ulChannel))));

    ulFrepDiv = PWMClockGet(ulBase, ulChannel) / ulFrequency;

    xASSERT(ulFrepDiv <= 0x10000000);

    ucDivider = 1;
    usPreScale = 1;

    if (ulFrepDiv < 0x100000)
    {
        i = 0;
        while((ulFrepDiv/(ucDivider << i++)) > 65536);
        ucDivider = ucDivider << (i - 1);
    }
    else 
    {
        usPreScale = ulFrepDiv / 65536; 
        if (ulFrepDiv / usPreScale > 65536)
        {
            usPreScale++;
        }
        if (usPreScale > 256)
        {
            usPreScale = 256;
            ulFrepDiv = ulFrepDiv / usPreScale;
            ucDivider = ulFrepDiv / 65536;
                
            if(ulFrepDiv / ucDivider > 65536)
                ucDivider++;
            i = 0;
            while(1)    
            {
                if((1 << i++) > ucDivider)
                {
                    break;
                }
            }
            ucDivider = 1 << (i - 1);
                
            if (ucDivider > 16)
            {
                return 0; 
            }
                    
            ulFrepDiv = ulFrepDiv * usPreScale;
        } 
    } 
    usCNRData = (unsigned short)(ulFrepDiv / usPreScale / ucDivider);
    ulActualFrep = (PWMClockGet(ulBase, ulChannel) / usPreScale / ucDivider / 
                   usCNRData);

    xHWREG(ulBase + PWM_PPR) &= ~(PWM_PPR_CP01_M << (ulChannelTemp / 2));
    xHWREG(ulBase + PWM_PPR) |= ((usPreScale - 1) << (ulChannelTemp / 2));

    switch(ucDivider)
    {
        case 1:
            ucDivider = PWM_CLOCK_DIV_1;
            break;
            
        case 2:
            ucDivider = PWM_CLOCK_DIV_2;  
            break;  
            
        case 4:
            ucDivider = PWM_CLOCK_DIV_4;  
            break;  
            
        case 8:
            ucDivider = PWM_CLOCK_DIV_8;  
            break; 
            
        case 16:
            ucDivider = PWM_CLOCK_DIV_16; 
            break;   
            
    }  
    xHWREG(ulBase + PWM_CSR) &= ~(PWM_CSR_CSR0_M << (ulChannelTemp << 2));
    xHWREG(ulBase + PWM_CSR) |= ((ucDivider) << (ulChannelTemp << 2));
    
    if(xHWREG(ulBase + PWM_PCR) & PWM_EDGE_ALLIGNED_TYPE)
    {
        xHWREG(ulBase + PWM_CNR0 +(ulChannelTemp * 4)) = (usCNRData - 1) / 2;
    }
    else
    {
        xHWREG(ulBase + PWM_CNR0 +(ulChannelTemp * 4)) = usCNRData - 1;
    }
    return ulActualFrep;
}

//*****************************************************************************
//
//! \brief Set the PWM frequency of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulConfig is the configuration of PWM channel' frequency.
//!
//! This function is to set the PWM frequency of the PWM module.
//!
//! The \e ulChannel parameter must be values:0~5
//!
//! The \e ulConfig parameter is the logical OR of three values: The PreScale
//! value, The Divider value and the PWM Counter Register value.
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
unsigned long 
PWMFrequencyConfig(unsigned long ulBase, unsigned long ulChannel, 
                   unsigned long ulConfig)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_PPR) &= ~(PWM_PPR_CP01_M << (ulChannelTemp / 2 * 8));
    xHWREG(ulBase + PWM_PPR) |= (((ulConfig & 0xFF0000) >> 16) 
                                << (ulChannelTemp / 2 * 8));
    
    xHWREG(ulBase + PWM_CSR) &= ~(PWM_CSR_CSR0_M << (ulChannelTemp << 2));
    xHWREG(ulBase + PWM_CSR) |= (((ulConfig & 0x7000000) >> 24) 
                                << (ulChannelTemp << 2));
    
    xHWREG(ulBase + PWM_CNR0 +(ulChannelTemp * 4)) = (ulConfig & 0xFFFF);
    
    switch(((ulConfig & 0x7000000) >> 24))
    {
        case PWM_CLOCK_DIV_1:
            ulChannelTemp = 1;
            break;
            
        case PWM_CLOCK_DIV_2:
            ulChannelTemp = 2;
            break; 
            
        case PWM_CLOCK_DIV_4:
            ulChannelTemp = 4;
            break; 
            
        case PWM_CLOCK_DIV_8:
            ulChannelTemp = 8;
            break;  
            
        case PWM_CLOCK_DIV_16:
            ulChannelTemp = 16;
            break;       
    } 

    return (PWMClockGet(ulBase, ulChannel) / (((ulConfig & 0xFF0000) >> 16) + 1) 
            / ulChannelTemp / ((ulConfig & 0xFFFF) + 1));
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
//! The \e ulChannel parameter must be values:0~5
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
    unsigned long ulChannelTemp;
    unsigned long ulCMRData;

    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));
    xASSERT(((ulDuty > 0) || (ulDuty <= 100)));
    if(xHWREG(ulBase + PWM_PCR) & PWM_EDGE_ALLIGNED_TYPE)
    {
        ulCMRData = (xHWREG(ulBase + PWM_CNR0 +(ulChannelTemp * 4)) + 1) * 
                    ulDuty / 100 - 1;
    }
    else
    {
        ulCMRData = xHWREG(ulBase + PWM_CNR0 +(ulChannelTemp * 4)) -           
                    (xHWREG(ulBase + PWM_CNR0 +(ulChannelTemp * 4)) + 1) * ulDuty / 100;
    }
    
    if(xHWREG(ulBase + PWM_PCR) & PWM_EDGE_ALLIGNED_TYPE)
    {
        if ((xHWREG(ulBase + PWM_CNR0 +(ulChannelTemp * 4)) + 1) *ulDuty / 100 == 0)
        {
            ulCMRData = 0;
        }
        else
        {
            ulCMRData = xHWREG(ulBase + PWM_CNR0 +(ulChannelTemp * 4));
        }
    }
    xHWREG(ulBase + PWM_CMR0 +(ulChannelTemp * 4)) = ulCMRData;
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
//! The \e ulChannel parameter must be values:0~5
//!
//! \return the Actual duty of PWM.
//
//*****************************************************************************
unsigned long
PWMDutyGet(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;
    unsigned long ulCMRData;
    unsigned long ulCNRData;

    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));
    
    ulCNRData = (xHWREG(ulBase + PWM_CNR0 +(ulChannelTemp * 4)));
    ulCMRData = (xHWREG(ulBase + PWM_CMR0 +(ulChannelTemp * 4)));
    
    if(xHWREG(ulBase + PWM_PCR) & PWM_CENTER_ALLIGNED_TYPE)
    {
        ulChannelTemp = (ulCNRData - ulCMRData) * 100 / (ulCNRData + 1);
    }
    else
    {
        ulChannelTemp = (ulCMRData + 1) * 100 / (ulCNRData + 1);
        ulChannelTemp = 100-ulChannelTemp;
    }

    return ulChannelTemp;
}

//*****************************************************************************
//
//! \brief get the PWM frequency of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to get the PWM frequency of the PWM module.
//!
//! The \e ulChannel parameter must be values:0~5
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
unsigned long 
PWMFrequencyGet(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;
    unsigned long ulCNRData;
    unsigned long ulFrequency;
    unsigned char ucDivider;
    unsigned short usPreScale;

    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    usPreScale = ((xHWREG(ulBase + PWM_PPR) >> ((ulChannelTemp/2) << 3))  & 
                   PWM_CSR_CSR0_M);
    
    ucDivider = (xHWREG(ulBase + PWM_CSR) >> (ulChannelTemp << 2)) & 
                 PWM_CSR_CSR0_M; 
        
    switch(ucDivider)
    {
        case PWM_CLOCK_DIV_1:
            ucDivider = 1;
            break;
            
        case PWM_CLOCK_DIV_2:
            ucDivider = 2;  
            break; 
            
        case PWM_CLOCK_DIV_4:
            ucDivider = 4;  
            break; 
            
        case PWM_CLOCK_DIV_8:
            ucDivider = 8;  
            break;  
            
        case PWM_CLOCK_DIV_16:
            ucDivider = 16; 
            break;   
        default:
            break;
    } 
    ulCNRData = xHWREG(ulBase + PWM_CNR0 +(ulChannelTemp * 4));
    if(xHWREG(ulBase + PWM_PCR) & PWM_CENTER_ALLIGNED_TYPE)
    {
        ulFrequency = (PWMClockGet(ulBase, ulChannel) / (usPreScale + 1) /
                       ucDivider /ulCNRData);
    }
    else
    {
        ulFrequency = (PWMClockGet(ulBase, ulChannel) / (usPreScale + 1) /
                       ucDivider /ulCNRData);
    }
    return ulFrequency;
}

//*****************************************************************************
//
//! \brief Enable the PWM output of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to enable the PWM output of the PWM module.
//!
//! The \e ulChannel parameter must be values:0~5
//!
//! \return None.
//
//*****************************************************************************
void 
PWMOutputEnable(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_POE) |= (PWM_POE_PWM0 << (ulChannelTemp));
}

//*****************************************************************************
//
//! \brief Disable the PWM output of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to disable the PWM output of the PWM module.
//!
//! The \e ulChannel parameter must be values:0~5
//!
//! \return None.
//
//*****************************************************************************
void 
PWMOutputDisable(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_POE) &= ~(PWM_POE_PWM0 << (ulChannelTemp));
}

//*****************************************************************************
//
//! \brief Start the PWM of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to start the PWM of the PWM module.
//!
//! The \e ulChannel parameter must be values:0~5
//!
//! \return None.
//
//*****************************************************************************
void 
PWMStart(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_PCR) |= (PWM_PCR_CH0EN << (ulChannelTemp << 2));
}

//*****************************************************************************
//
//! \brief Stop the PWM of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to stop the PWM of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~5
//!
//! \return None.
//
//*****************************************************************************
void 
PWMStop(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_PCR) &= ~(PWM_PCR_CH0EN << (ulChannelTemp << 2));
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
//! The \e ulChannel parameter must be values:0~5
//!
//! The \e ulIntType parameter can be values:
//! \b PWM_INT_DUTY, \b PWM_INT_BRAKE, \b PWM_INT_PWM.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMIntEnable(unsigned long ulBase, unsigned long ulChannel,
             unsigned long ulIntType)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));
    xASSERT((ulIntType == PWM_INT_DUTY) || (ulIntType == PWM_INT_BRAKE) ||
            (ulIntType == PWM_INT_PWM));

    if(ulIntType == PWM_INT_PWM)
    {
        xHWREG(ulBase + PWM_PIER) |= (PWM_PIER_PWMPIE0 << ulChannelTemp) | 
                                      PWM_INT_PWM;
    }
    else if(ulIntType == PWM_INT_DUTY)
    {
        xHWREG(ulBase + PWM_PIER) |= (PWM_PIER_PWMDIE0 << ulChannelTemp) |
                                      PWM_INT_DUTY;
    }
    else
    {
        xHWREG(ulBase + PWM_PIER) |= PWM_PIER_BRKIE;
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
//! This function is to disable the PWM interrupt of the PWM module.
//!
//! The \e ulChannel parameter must be values:0~5
//!
//! The \e ulIntType parameter can be values:
//! \b PWM_INT_DUTY, \b PWM_INT_BRAKE, \b PWM_INT_PWM.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMIntDisable(unsigned long ulBase, unsigned long ulChannel,
              unsigned long ulIntType)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));
    xASSERT((ulIntType == PWM_INT_DUTY) || (ulIntType == PWM_INT_BRAKE) ||
            (ulIntType == PWM_INT_PWM));

    if(ulIntType == PWM_INT_PWM)
    {
        xHWREG(ulBase + PWM_PIER) &= ~(PWM_PIER_PWMPIE0 << ulChannelTemp);
    }
    else if(ulIntType == PWM_INT_DUTY)
    {
        xHWREG(ulBase + PWM_PIER) &= ~(PWM_PIER_PWMDIE0 << ulChannelTemp);
    }
    else
    {
        xHWREG(ulBase + PWM_PIER) &= ~PWM_PIER_BRKIE;
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
//! The \e ulChannel parameter must be values:0~5
//!
//! The \e ulIntType parameter can be values:
//! \b PWM_INT_DUTY, \b PWM_INT_BRAKE, \b PWM_INT_PWM.
//!
//! \return None.
//
//*****************************************************************************
xtBoolean
PWMIntFlagGet(unsigned long ulBase, unsigned long ulChannel,
              unsigned long ulIntType)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));
    
    xASSERT((ulIntType == PWM_INT_DUTY) || (ulIntType == PWM_INT_BRAKE) ||
            (ulIntType == PWM_INT_PWM));

    if(ulIntType == PWM_INT_PWM)
    {
        return((xHWREG(ulBase + PWM_PIIR) & (PWM_PIER_PWMPIF0 << ulChannelTemp)) 
                ? xtrue : xfalse);
    }
    else if(ulIntType == PWM_INT_DUTY)
    {
        return((xHWREG(ulBase + PWM_PIIR) & (PWM_PIER_PWMDIF0 << ulChannelTemp)) 
                ? xtrue : xfalse);
    }
    else
    {
        return((xHWREG(ulBase + PWM_PIIR) & (PWM_PIER_BKF0 | PWM_PIER_BKF1))
                ? xtrue : xfalse);
    }
}

//*****************************************************************************
//
//! \brief Clear the PWM interrupt flag of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//!
//! This function is to Clear the PWM interrupt flag of the PWM module.
//!
//! The \e ulChannel parameter must be values:0~5
//!
//! The \e ulIntType parameter can be values:
//! \b PWM_INT_CAP_BOTH, \b PWM_INT_CAP_FALL, \b PWM_INT_CAP_RISE and 
//! \b PWM_INT_PWM.
//!
//! \return None.
//
//*****************************************************************************
void
PWMIntFlagClear(unsigned long ulBase, unsigned long ulChannel,
                unsigned long ulIntType)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));
    xASSERT((ulIntType == PWM_INT_DUTY) || (ulIntType == PWM_INT_BRAKE) ||
            (ulIntType == PWM_INT_PWM));

    if(ulIntType == PWM_INT_PWM)
    {
        xHWREG(ulBase + PWM_PIIR) |= (PWM_PIER_PWMPIF0 << ulChannelTemp);
    }
    else if(ulIntType == PWM_INT_DUTY)
    {
        xHWREG(ulBase + PWM_PIIR) |= (PWM_PIER_PWMDIF0 << ulChannelTemp);
    }
    else
    {
        xHWREG(ulBase + PWM_PIIR) |= (PWM_PIER_BKF0 | PWM_PIER_BKF1);
    }
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the PWM timer.
//!
//! \param ulBase is the base address of the PWM port.
//! \param xtPortCallback is callback for the PWM timer.
//!
//! This function is to init interrupts callback for the PWM timer.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMIntCallbackInit(unsigned long ulBase, xtEventCallback xtPWMCallback)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);

    if (xtPWMCallback != 0)
    {
        g_pfnPWMHandlerCallbacks[0] = xtPWMCallback;
    }
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the PWM Fault Brake.
//!
//! \param ulBase is the base address of the PWM port.
//! \param xtPortCallback is callback for the PWM Fault Brake.
//!
//! This function is to init interrupts callback for the PWM Fault Brake.
//!
//! \return None.
//
//*****************************************************************************
void 
FBIntCallbackInit(unsigned long ulBase, xtEventCallback xtFBCallback)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);

    if (xtFBCallback != 0)
    {
        g_pfnFBHandlerCallbacks[0] = xtFBCallback;
    }
}
//*****************************************************************************
//
//! \brief Set PWM fault break output level.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulLevel is the PWM fault break output level.
//!
//! This function is to Set PWM fault break output level.
//!
//! The \e ulChannel parameter must be values:0~5
//! The \e ulLevel parameter must be values:0 or 1.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMFaultBreakOutputLevelSet(unsigned long ulBase, unsigned long ulChannel,
                            unsigned long ulLevel)
{
    unsigned long ulChannelTemp,ulTemp;

    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));
    
    ulTemp = xHWREG(ulBase + PWM_PFBCON);
    if(ulLevel == 1)
    {
        if(ulChannelTemp != 0)
        {
            ulTemp = (ulTemp & ~0x3F000080) | (ulLevel << (ulChannelTemp + 24));
        }
        else
        {
            ulTemp = (ulTemp & ~0x3F000080) | 0x01000000;
        }
    }
    else
    {
        ulTemp = (ulTemp & ~0x3F000080) & (~(ulChannelTemp << 24));
    }
    xHWREG(ulBase + PWM_PFBCON) = ulTemp;
}

//*****************************************************************************
//
//! \brief Enable fault break function.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulFaultBreakSource is the Mini51 PWM fault break source.
//!
//! This function is to Enable fault break function.
//!
//! \return None.
//
//*****************************************************************************

void 
PWMFaultBreakEnable(unsigned long ulBase, unsigned long ulFaultBreakSource)
{

    unsigned long ulTemp;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE));
    
    ulTemp = xHWREG(ulBase + PWM_PFBCON);
    
	switch(ulFaultBreakSource) 
	{
		case PWM_FB_EINT0:
            ulTemp |= PWM_FB_EINT0;
			break;
		case PWM_FB_CPO0:
            ulTemp |= PWM_FB_CPO0 | PWM_FB_EINT1;                        
            break;		
		case PWM_FB_EINT1:	
            ulTemp = (ulTemp & ~4) | 2;
            break;
		default:
			break;
	}
    xHWREG(ulBase + PWM_PFBCON) = ulTemp;

}

//*****************************************************************************
//
//! \brief Disable fault break function.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulFaultBreakSource is the Mini51 PWM fault break source.
//!
//! This function is to Disable fault break function.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMFaultBreakDisable(unsigned long ulBase, unsigned long  ulFaultBreakSource)
{

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE));
    
	switch(ulFaultBreakSource) 
	{
		case PWM_FB_EINT0:
            xHWREG(ulBase + PWM_PFBCON) &= ~PWM_FB_EINT0;
			break;
		case PWM_FB_CPO0:
		case PWM_FB_EINT1:	
            xHWREG(ulBase + PWM_PFBCON) &= ~PWM_FB_EINT1;
            break;
		default:
			break;
	}
}

//*****************************************************************************
//
//! \brief Clear Fault Break.
//!
//! \param ulBase is the base address of the PWM port.
//!
//! This function is to Clear Fault Break.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMFaultBreakClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE));
    
    xHWREG(ulBase + PWM_PFBCON) |= PWM_EVENT_FAULT_BRAEK;
}
