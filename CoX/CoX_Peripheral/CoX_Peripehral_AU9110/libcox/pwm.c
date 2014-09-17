//*****************************************************************************
//
//! \file xpwm.c
//! \brief Driver for the AU9110 PWM
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

#include "CoX.h"
#include "pwm.h"

//*****************************************************************************
//
// An array is PWM Callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnPWMHandlerCallbacks[2]={0};


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
//! interrupt,bit0 in ulPWMStastus shows PWM_CHANNEL0,bit1 in ulPWMStastus 
//! shows PWM_CHANNEL1,bit2 in ulPWMStastus shows PWM_CHANNEL2 and bit3 in 
//! ulPWMStastus shows PWM_CHANNEL3.
//! Only the last four bits(0~3 bits) is effective.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMAIntHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulCAPStastus0;
    unsigned long ulBase = PWMA_BASE;
    
    //
    //! Clear the PWMA INT Flag
    //        
    ulPWMStastus = xHWREG(ulBase + PWM_PIIR) & 0xF;
    xHWREG(ulBase + PWM_PIIR) = ulPWMStastus;

    ulCAPStastus0 = xHWREG(ulBase + PWM_CCR0) & 0x100010;
    
    if (g_pfnPWMHandlerCallbacks[0] != 0)        
    {
        if(ulPWMStastus != 0)
        {
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
        if(ulCAPStastus0 != 0)
        {
            ulPWMStastus = 0;
            if (ulCAPStastus0 & 0x10)
            {
                ulPWMStastus |= (1 << PWM_CHANNEL0);
            }
            if (ulCAPStastus0 & 0x100000)
            {
                ulPWMStastus |= (1 << PWM_CHANNEL1);
            }
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_CAP, ulPWMStastus, 0);
        }
    }
    xHWREG(ulBase + PWM_CCR0) |= ulCAPStastus0;
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
    xASSERT(((ulTemp >= 0) || (ulTemp <= 1)));
    switch(ulChannel)
    {
        case PWM_CHANNEL0:
        case PWM_CHANNEL1:
            ulTemp = ((xHWREG(SYSCLK_CLKSEL1) & SYSCLK_CLKSEL1_PWM01_M) >>
                      SYSCLK_CLKSEL1_PWM01_S);
            break;
        default:
            break;
    }
    if (ulTemp == 0)
    {
        ulPWMFreq = 12000000;
    }
    else if (ulTemp == 1)
    {
        ulPWMFreq = 32768;
    }
    else if (ulTemp == 2)
    {
        ulPWMFreq = SysCtlHClockGet();
    }
    else 
    {
        ulPWMFreq = 22118400;
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
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! The \e ulConfig parameter is the logical OR of four values: The PWM mode,
//! Inverter or not,and use dead zero or not and dead zone length. 
//! \b PWM_ONE_SHOT_MODE,\b PWM_TOGGLE_MODE is the mode selecet.
//! \b PWM_OUTPUT_INVERTER_EN,
//! \b PWM_OUTPUT_INVERTER_DIS is to enable Inverter or not.\b PWM_DEAD_ZONE_EN
//! \b PWM_DEAD_ZONE_DIS is to enable dead zone Generator or not.
//! The dead zone length will be set at the 16~23 bits of the ulConfig.
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
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;
    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 1)));
    xASSERT((ulConfig & 0xFFFFFF00) == 0);
    xASSERT(((ulConfig & PWM_PCR_CH0INV) == PWM_OUTPUT_INVERTER_EN) || 
            ((ulConfig & PWM_PCR_CH0INV) == PWM_OUTPUT_INVERTER_DIS));
    
    xASSERT(((ulConfig & PWM_PCR_CH0MOD) == PWM_ONE_SHOT_MODE) || 
            ((ulConfig & PWM_PCR_CH0MOD) == PWM_TOGGLE_MODE));
    
    xASSERT(((ulConfig & PWM_DEAD_ZONE_EN) == PWM_DEAD_ZONE_EN) || 
            ((ulConfig & PWM_DEAD_ZONE_EN) == PWM_DEAD_ZONE_DIS));
    
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_PWMA);

    xHWREG(ulBase + PWM_PCR) |= ((ulConfig & 0xF) << (ulChannelTemp * 8));
    if (ulConfig & PWM_DEAD_ZONE_EN)
    {
        xHWREG(ulBase + PWM_PCR) |= (PWM_DEAD_ZONE_EN << (ulChannelTemp >> 1));
        xHWREG(ulBase + PWM_PPR) &= ~(PWM_PPR_DZI01_M << 
                                    (ulChannelTemp >> 1) * 8);
        xHWREG(ulBase + PWM_PPR) |= ((ulConfig & PWM_PPR_DZI01_M) << 
                                    (ulChannelTemp >> 1) * 8);
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
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! The \e ulFrequency parameter can be values: Any values ,ulFrequency > 0 &&
//! ulFrequency < PWM module input clock.
//!
//! \note 
//!
//! \return the Actual Frequency of PWM, if return 0 .
//
//*****************************************************************************
unsigned long 
xPWMFrequencySet(unsigned long ulBase, unsigned long ulChannel, 
                unsigned long ulFrequency)
{
    unsigned long ulFrepDiv;
    unsigned long ulActualFrep;
    unsigned short usCNRData;
    unsigned char ucDivider;
    unsigned short usPreScale;
    unsigned char i;
    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 1)));
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

    xHWREG(ulBase + PWM_PPR) &= ~(PWM_PPR_CP01_M << (ulChannel / 2));
    xHWREG(ulBase + PWM_PPR) |= ((usPreScale - 1) << (ulChannel / 2));

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
    xHWREG(ulBase + PWM_CSR) &= ~(PWM_CSR_CSR0_M << (ulChannel << 2));
    xHWREG(ulBase + PWM_CSR) |= (ucDivider << (ulChannel << 2));
    
    xHWREG(ulBase + PWM_CNR0 +(ulChannel * 12)) = usCNRData - 1;

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
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! The \e ulConfig parameter is the logical OR of three values: The PreScale
//! value, The Divider value and the PWM Counter Register value.
//!
//! \note 
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
unsigned long 
xPWMFrequencyConfig(unsigned long ulBase, unsigned long ulChannel, 
                   unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE));
    xASSERT(((ulChannel >= 0) || (ulChannel <= 1)));

    xHWREG(ulBase + PWM_PPR) &= ~(PWM_PPR_CP01_M << (ulChannel / 2 * 8));
    xHWREG(ulBase + PWM_PPR) |= (((ulConfig & 0xFF0000) >> 16) 
                                << (ulChannel / 2 * 8));
    
    xHWREG(ulBase + PWM_CSR) &= ~(PWM_CSR_CSR0_M << (ulChannel << 2));
    xHWREG(ulBase + PWM_CSR) |= (((ulConfig & 0x7000000) >> 24) 
                                << (ulChannel << 2));
    
    xHWREG(ulBase + PWM_CNR0 +(ulChannel * 12)) = (ulConfig & 0xFFFF);
    
    switch(((ulConfig & 0x7000000) >> 24))
    {
        case PWM_CLOCK_DIV_1:
            ulChannel = 1;
            break;
            
        case PWM_CLOCK_DIV_2:
            ulChannel = 2;  
            break; 
            
        case PWM_CLOCK_DIV_4:
            ulChannel = 4;  
            break; 
            
        case PWM_CLOCK_DIV_8:
            ulChannel = 8;  
            break;  
            
        case PWM_CLOCK_DIV_16:
            ulChannel = 16; 
            break;       
    } 

    return (PWMClockGet(ulBase, ulChannel) / (((ulConfig & 0xFF0000) >> 16) + 1) 
            / ulChannel / ((ulConfig & 0xFFFF) + 1));                
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
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! The \e ulDuty parameter can be values:  duty > 0 && duty <= 100. 
//!
//! \note Duty should not be 0;
//!
//! \return None.
//
//*****************************************************************************
void 
xPWMDutySet(unsigned long ulBase, unsigned long ulChannel, 
           unsigned char ulDuty)
{
    unsigned long ulCMRData;
    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 1)));
    xASSERT(((ulDuty > 0) || (ulDuty <= 100)));

    ulCMRData = (xHWREG(ulBase + PWM_CNR0 +(ulChannel * 12)) + 1) * 
                ulDuty / 100 - 1;
    if ((xHWREG(ulBase + PWM_CNR0 +(ulChannel * 12)) + 1) *ulDuty / 100 == 0)
    {
        ulCMRData = 0;
    }
    xHWREG(ulBase + PWM_CMR0 +(ulChannel * 12)) = ulCMRData;
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
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! \note None
//!
//! \return the Actual duty of PWM.
//
//*****************************************************************************
unsigned long
xPWMDutyGet(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulCMRData;
    unsigned long ulCNRData;
    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 1)));

    ulCNRData = (xHWREG(ulBase + PWM_CNR0 +(ulChannel * 12)));
    ulCMRData = (xHWREG(ulBase + PWM_CMR0 +(ulChannel * 12)));
    ulChannel = (ulCMRData + 1) * 100 / (ulCNRData + 1);
    return ulChannel;
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
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! \note None
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
unsigned long 
xPWMFrequencyGet(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulCNRData;
    unsigned char ucDivider;
    unsigned short usPreScale;
    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 1)));

    usPreScale = ((xHWREG(ulBase + PWM_PPR) >> (ulChannel << 2))  & 
                   PWM_CSR_CSR0_M);
    
    ucDivider = (xHWREG(ulBase + PWM_CSR) >> (ulChannel << 2)) & 
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
    ulCNRData = xHWREG(ulBase + PWM_CNR0 +(ulChannel * 12));
    return (PWMClockGet(ulBase, ulChannel) / (usPreScale + 1) / ucDivider /
            ulCNRData);
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
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
xPWMOutputEnable(unsigned long ulBase, unsigned long ulChannel)
{    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 1)));

    xHWREG(ulBase + PWM_POE) |= (PWM_POE_PWM0 << (ulChannel));
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
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
xPWMOutputDisable(unsigned long ulBase, unsigned long ulChannel)
{    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 1)));

    xHWREG(ulBase + PWM_POE) &= ~(PWM_POE_PWM0 << (ulChannel));
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
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
xPWMStart(unsigned long ulBase, unsigned long ulChannel)
{    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 1)));

    xHWREG(ulBase + PWM_PCR) |= (PWM_PCR_CH0EN << (ulChannel << 3));
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
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
xPWMStop(unsigned long ulBase, unsigned long ulChannel)
{    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 1)));

    xHWREG(ulBase + PWM_PCR) &= ~(PWM_PCR_CH0EN << (ulChannel << 3));
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
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! //! The \e ulIntType parameter can be values:
//! \b PWM_INT_CAP_BOTH, \b PWM_INT_CAP_FALL, \b PWM_INT_CAP_RISE and 
//! \b PWM_INT_PWM.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
xPWMIntEnable(unsigned long ulBase, unsigned long ulChannel,
             unsigned long ulIntType)
{    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));
    xASSERT((ulIntType == PWM_INT_CAP_BOTH) || (ulIntType == PWM_INT_CAP_FALL) ||
            (ulIntType == PWM_INT_CAP_RISE) || (ulIntType == PWM_INT_PWM));

    if (ulIntType == PWM_INT_PWM)
    {
        xHWREG(ulBase + PWM_PIER) |= (PWM_PIER_PWMIE0 << ulChannel);
    }
    else
    {
        xHWREG(ulBase + PWM_CCR0 + (ulChannel >> 1)*4) |= 
        (ulIntType << ((ulChannel % 2) ? 16 : 0));
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
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! //! The \e ulIntType parameter can be values:
//! \b PWM_INT_CAP_BOTH, \b PWM_INT_CAP_FALL, \b PWM_INT_CAP_RISE and 
//! \b PWM_INT_PWM.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
xPWMIntDisable(unsigned long ulBase, unsigned long ulChannel,
              unsigned long ulIntType)
{    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));
    
    xASSERT((ulIntType == PWM_INT_CAP_BOTH) || (ulIntType == PWM_INT_CAP_FALL) ||
            (ulIntType == PWM_INT_CAP_RISE) || (ulIntType == PWM_INT_PWM));

    if (ulIntType == PWM_INT_PWM)
    {
        xHWREG(ulBase + PWM_PIER) &= ~(PWM_PIER_PWMIE0 << ulChannel);
    }
    else
    {
        xHWREG(ulBase + PWM_CCR0 + (ulChannel >> 1)*4) &= 
        ~(ulIntType << ((ulChannel % 2) ? 16 : 0));
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
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! //! The \e ulIntType parameter can be values:
//! \b PWM_INT_CAP_BOTH, \b PWM_INT_CAP_FALL, \b PWM_INT_CAP_RISE and 
//! \b PWM_INT_PWM.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
xtBoolean
xPWMIntFlagGet(unsigned long ulBase, unsigned long ulChannel,
              unsigned long ulIntType)
{    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));
    
    xASSERT((ulIntType == PWM_INT_CAP_BOTH) || (ulIntType == PWM_INT_CAP_FALL) ||
            (ulIntType == PWM_INT_CAP_RISE) || (ulIntType == PWM_INT_PWM));

    if (ulIntType == PWM_INT_PWM)
    {
        return ((xHWREG(ulBase + PWM_PIER) & (PWM_PIER_PWMIE0 << ulChannel)) 
                ? xtrue : xfalse);
    }
    else
    {
        return ((xHWREG(ulBase + PWM_CCR0 + (ulChannel << 1)) & 
        (PWM_CCR0_CAPIF0 << ((ulChannel % 2) ? 16 : 0))) ? xtrue : xfalse);
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
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! The \e ulIntType parameter can be values:
//! \b PWM_INT_CAP_BOTH, \b PWM_INT_CAP_FALL, \b PWM_INT_CAP_RISE and 
//! \b PWM_INT_PWM.
//!
//! \note None
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
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));
    
    xASSERT((ulIntType == PWM_INT_CAP_BOTH) || (ulIntType == PWM_INT_CAP_FALL) ||
            (ulIntType == PWM_INT_CAP_RISE) || (ulIntType == PWM_INT_PWM));

    if (ulIntType == PWM_INT_PWM)
    {
        xHWREG(ulBase + PWM_PIIR) |= (PWM_PIER_PWMIE0 << ulChannel);
    }
    else
    {
        xHWREG(ulBase + PWM_CCR0 + (ulChannel << 1)) |= 
        (PWM_CCR0_CAPIF0 << ((ulChannel % 2) ? 16 : 0)) ;
    }
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the PWM timer.
//!
//! \param xtPortCallback is callback for the PWM timer.
//!
//! This function is to init interrupts callback for the PWM timer.
//!
//! \return None.
//
//*****************************************************************************
void 
xPWMIntCallbackInit(unsigned long ulBase, xtEventCallback xtPWMCallback)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);

    if (xtPWMCallback != 0)
    {
        if (ulBase == PWMA_BASE)
        {
            g_pfnPWMHandlerCallbacks[0] = xtPWMCallback;
        }
        else
        {
            g_pfnPWMHandlerCallbacks[1] = xtPWMCallback;
        }
    }
}

//*****************************************************************************
//
//! \brief Enable the Capture of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to Enable the Capture of the PWM module.
//!
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
PWMCAPEnable(unsigned long ulBase, unsigned long ulChannel)
{    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));

    xHWREG(ulBase + PWM_CCR0 + (ulChannel >> 1)*4) |= 
          (PWM_CCR0_CAPCH0EN << ((ulChannel % 2) ? 16 : 0));
    xHWREG(ulBase + PWM_PCR) |= (PWM_PCR_CH0EN << (ulChannel << 3));
}

//*****************************************************************************
//
//! \brief Disable the Capture of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to disable the Capture of the PWM module.
//!
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
PWMCAPDisable(unsigned long ulBase, unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));

    xHWREG(ulBase + PWM_CCR0 + (ulChannel >> 1)*4) &= 
          ~(PWM_CCR0_CAPCH0EN << ((ulChannel % 2) ? 16 : 0));
    xHWREG(ulBase + PWM_PCR) &= ~(PWM_PCR_CH0EN << (ulChannel << 3));
}

//*****************************************************************************
//
//! \brief Enable the Capture input of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to enable the Capture input of the PWM module.
//!
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
PWMCAPInputEnable(unsigned long ulBase, unsigned long ulChannel)
{    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));

    xHWREG(ulBase + PWM_CAPENR) |= (PWM_CAPENR_CAPIE_0 << (ulChannel));
}

//*****************************************************************************
//
//! \brief Disable the Capture input of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to disable the Capture input of the PWM module.
//!
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
PWMCAPInputDisable(unsigned long ulBase, unsigned long ulChannel)
{    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));

    xHWREG(ulBase + PWM_CAPENR) &= ~(PWM_CAPENR_CAPIE_0 << (ulChannel));
}

//*****************************************************************************
//
//! \brief Get the Rising Latched PWM counter of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to Get the Rising Latched PWM counter of the PWM module.
//!
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! \note None
//!
//! \return PWM counter when Channel \b ulChannel has rising transition.
//
//*****************************************************************************
unsigned long 
PWMCAPRisingCounterGet(unsigned long ulBase, unsigned long ulChannel)
{    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));

    return xHWREG(ulBase + PWM_CRLR0 + ulChannel * 8);
}

//*****************************************************************************
//
//! \brief Get the Falling Latched PWM counter of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! This function is to Get the Falling Latched PWM counter of the PWM module.
//!
//! The \e ulChannel parameter can be values: xPWM_CHANNEL0 or xPWM_CHANNEL1.
//!
//! \note None
//!
//! \return PWM counter when Channel \b ulChannel has Falling transition.
//
//*****************************************************************************
unsigned long 
PWMCAPFallingCounterGet(unsigned long ulBase, unsigned long ulChannel)
{    
    //
    // Check the arguments.
    //
    xASSERT(ulBase == PWMA_BASE);
    xASSERT(((ulChannel >= 0) || (ulChannel <= 3)));

    return xHWREG(ulBase + PWM_CFLR0 + ulChannel * 8);
}
