//*****************************************************************************
//
//! \file xpwm.c
//! \brief Driver for the PWM
//! \version V2.2.1.0
//! \date 8/21/2012
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
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_tpm.h"
#include "xpwm.h"

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
//! The \e ulChannel parameter can be values:
//! \b xPWM_CHANNEL0, \b xPWM_CHANNEL1, \b xPWM_CHANNEL2, \b xPWM_CHANNEL3,
//! \b xPWM_CHANNEL4, \b xPWM_CHANNEL5.  
//!
//! The \e ulConfig parameter can be values:
//! \b xPWM_ONE_SHOT_MODE, xPWM_TOGGLE_MODE
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) || 
            (ulBase == PWMC_BASE));
    if(ulBase == PWMA_BASE)
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 5));
    }
    else
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 1));
    }
    xASSERT((ulConfig == xPWM_ONE_SHOT_MODE) || 
            (ulConfig == xPWM_TOGGLE_MODE));

    //
    // Select the pwm mode
    //
    if(ulConfig == xPWM_ONE_SHOT_MODE)
    {
        xHWREG(ulBase + TPM_CONF) |= TPM_CONF_CSOO;
    }
    else
    {
        xHWREG(ulBase + TPM_CONF) &= ~TPM_CONF_CSOO;
    } 
    
    //
    // Edge-aligned PWM
    // 
    xHWREG(ulBase + TPM_SC) &= ~TPM_SC_CPWMS;
    
    //
    // Configure MSnB:MSnA bits as 10 (output pwm) and High-true pulses
    //
    xHWREG(ulBase + TPM_C0SC + ulChannel * 8) &= 
                ~(TPM_CNSC_MSB | TPM_CNSC_MSA | TPM_CNSC_ELSB | TPM_CNSC_ELSA);
    
    xHWREG(ulBase + TPM_C0SC + ulChannel * 8) |= (TPM_CNSC_MSB | TPM_CNSC_ELSB);       
}

//*****************************************************************************
//
//! \brief Initialize and configure the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulMode is the timer counter direction.
//!
//! This function is to initialize and configure channel of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//!
//! The \e ulMode parameter can be values:
//! \b PWM_MODE_EDGE_ALIGNED1, \b PWM_MODE_EDGE_ALIGNED2, 
//! \b PWM_MODE_CENTER_ALIGNED1, \b PWM_MODE_CENTER_ALIGNED2
//!
//! \return None.
//
//*****************************************************************************
void 
PWMInitConfigure(unsigned long ulBase, unsigned long ulChannel, 
                                       unsigned long ulMode)
{
    unsigned long ulTemp = 0;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) || 
            (ulBase == PWMC_BASE));
    if(ulBase == PWMA_BASE)
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 5));
    }
    else
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 1));
    }
    xASSERT((ulMode == PWM_MODE_EDGE_ALIGNED1) ||
            (ulMode == PWM_MODE_EDGE_ALIGNED2) || 
            (ulMode == PWM_MODE_CENTER_ALIGNED1)||
            (ulMode == PWM_MODE_CENTER_ALIGNED2));

    //
    // Configure MSnB:MSnA bits as 10
    //
    xHWREG(ulBase + TPM_C0SC + ulChannel * 8) &= 
                ~(TPM_CNSC_MSB | TPM_CNSC_MSA | TPM_CNSC_ELSB | TPM_CNSC_ELSA);
    
    ulTemp |= TPM_CNSC_MSB;
    
    //
    // Configure the Mode
    //
    if((ulMode == PWM_MODE_EDGE_ALIGNED1) || (ulMode == PWM_MODE_EDGE_ALIGNED2))
    {
        //
        // Edge-aligned PWM
        // 
        xHWREG(ulBase + TPM_SC) &= ~TPM_SC_CPWMS; 

        if(ulMode == PWM_MODE_EDGE_ALIGNED1) 
        {
            //
            // High-true pulses
            //
            ulTemp |= TPM_CNSC_ELSB;
        }
        else
        {
            //
            // Low-true pulses
            //
            ulTemp |= TPM_CNSC_ELSA;
        }
    }
    else
    {
        //
        // Center-aligned PWM
        // 
        xHWREG(ulBase + TPM_SC) |= TPM_SC_CPWMS;  
     
        if(ulMode == PWM_MODE_CENTER_ALIGNED1) 
        {
            //
            // High-true pulses
            //
            ulTemp |= TPM_CNSC_ELSB;
        }
        else
        {
            //
            // Low-true pulses
            //
            ulTemp |= TPM_CNSC_ELSA;
        }
    } 
    xHWREG(ulBase + TPM_C0SC + ulChannel * 8) |= ulTemp; 
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
//! The \e ulChannel parameter can be values:
//! \b PWM_CHANNEL0, \b PWM_CHANNEL1, \b PWM_CHANNEL2, \b PWM_CHANNEL3, 
//! \b PWM_CHANNEL4 . 
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) ||
            (ulBase == PWMC_BASE));
    if(ulBase == PWMA_BASE)
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 5));
    }
    else
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 1));
    }
    xASSERT(((ulDuty > 0) || (ulDuty <= 100)));

    ulCMRData = (PWMMODGet(ulBase) *  ulDuty) / 100;
    if ((PWMMODGet(ulBase) *  ulDuty) / 100 == 0)
    {
        ulCMRData = 0;
    }
    
    xHWREG(ulBase + TPM_C0V + ulChannel * 8) = ulCMRData;
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
//! The \e ulChannel parameter can be values:
//! \b PWM_CHANNEL0, \b PWM_CHANNEL1, \b PWM_CHANNEL2, \b PWM_CHANNEL3, 
//! \b PWM_CHANNEL4 . 
//!
//! \note None
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) ||
            (ulBase == PWMC_BASE));
    if(ulBase == PWMA_BASE)
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 5));
    }
    else
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 1));
    }

    ulCNRData = PWMMODGet(ulBase);
    ulCMRData = xHWREG(ulBase + TPM_C0V + ulChannel * 8);
    return ((ulCMRData + 1) * 100 / (ulCNRData + 1));
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
//! The \e ulChannel parameter can be values:
//! \b PWM_CHANNEL0, \b PWM_CHANNEL1, \b PWM_CHANNEL2, \b PWM_CHANNEL3, 
//! \b PWM_CHANNEL4 . 
//!
//! The \e ulIntType parameter can be values:
//! \b PWM_INT_CHXF, \b PWM_INT_TOF.
//!
//! \note None
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) || 
            (ulBase == PWMC_BASE));
    if(ulBase == PWMA_BASE)
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 5));
    }
    else
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 1));
    }
    xASSERT((ulIntType == PWM_INT_CHXF) || (ulIntType == PWM_INT_TOF));

    if (ulIntType == PWM_INT_TOF)
    {
        xHWREG(ulBase + TPM_SC) |= TPM_SC_TOIE; 
    }
    else
    {
        xHWREG(ulBase + TPM_C0SC + 8 * ulChannel) |= TPM_CNSC_CHIE;
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
//! The \e ulChannel parameter can be values:
//! \b PWM_CHANNEL0, \b PWM_CHANNEL1, \b PWM_CHANNEL2, \b PWM_CHANNEL3, 
//! \b PWM_CHANNEL4 . 
//!
//! The \e ulIntType parameter can be values:
//! \b PWM_INT_CHXF, \b PWM_INT_TOF.
//!
//! \note None
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) ||
            (ulBase == PWMC_BASE));
    if(ulBase == PWMA_BASE)
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 5));
    }
    else
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 1));
    }
    xASSERT((ulIntType == PWM_INT_CHXF) || (ulIntType == PWM_INT_TOF));

    if (ulIntType == PWM_INT_TOF)
    {
        xHWREG(ulBase + TPM_SC) &= ~TPM_SC_TOIE; 
    }
    else
    {
        xHWREG(ulBase + TPM_C0SC + 8 * ulChannel) &= ~TPM_CNSC_CHIE;
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
//! The \e ulChannel parameter can be values:
//! \b PWM_CHANNEL0, \b PWM_CHANNEL1, \b PWM_CHANNEL2, \b PWM_CHANNEL3, 
//! \b PWM_CHANNEL4 . 
//!
//! The \e ulIntType parameter can be values:
//! \b PWM_INT_CHXF, \b PWM_INT_TOF.
//!
//! \note None
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) ||
            (ulBase == PWMC_BASE));
    if(ulBase == PWMA_BASE)
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 5));
    }
    else
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 1));
    }
    xASSERT((ulIntType == PWM_INT_CHXF) || (ulIntType == PWM_INT_TOF));


    if (ulIntType == PWM_INT_TOF)
    {
        ulIntStatus = xHWREG(ulBase + TPM_STATUS) & TPM_STATUS_TOF;
        if(ulIntStatus != 0)
        {
            return xtrue;
        }
    }
    else
    {
        ulIntStatus = xHWREG(ulBase + TPM_STATUS) & (TPM_STATUS_CH0F << ulChannel);
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
//! The \e ulChannel parameter can be values:
//! \b PWM_CHANNEL0, \b PWM_CHANNEL1, \b PWM_CHANNEL2, \b PWM_CHANNEL3, 
//! \b PWM_CHANNEL4 . 
//!
//! The \e ulIntType parameter can be values:
//! \b PWM_INT_CHXF, \b PWM_INT_TOF.
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) ||
            (ulBase == PWMC_BASE));
    if(ulBase == PWMA_BASE)
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 5));
    }
    else
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 1));
    }
    xASSERT((ulIntType == PWM_INT_CHXF) || (ulIntType == PWM_INT_TOF));

    if (ulIntType == PWM_INT_TOF)
    {
        xHWREG(ulBase + TPM_STATUS) |= TPM_STATUS_TOF;
    }
    else
    {
        xHWREG(ulBase + TPM_STATUS) |= (TPM_STATUS_CH0F << ulChannel);
    } 
}

//*****************************************************************************
//
//! \brief Start the PWM of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//!
//! \note None
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) || 
            (ulBase == PWMC_BASE));

    //
    // LPTPM counter increments on every LPTPM counter clock
    //
    xHWREG(ulBase + TPM_SC) &= ~TPM_SC_CMOD_M;
    xHWREG(ulBase + TPM_SC) |= TPM_SC_CMOD_CLK;
}

//*****************************************************************************
//
//! \brief Stop the PWM of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//!
//! \note None
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) || 
            (ulBase == PWMC_BASE));

    //
    // LPTPM counter is disabled
    //
    xHWREG(ulBase + TPM_SC) &= ~TPM_SC_CMOD_M;
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
//! \note 
//!
//! \return the Actual Frequency of PWM, if return 0 .
//
//*****************************************************************************
unsigned long 
PWMFrequencySet(unsigned long ulBase, unsigned long ulFrequency)
{
    unsigned long ulFrepDiv;
    unsigned long ulActualFrep;
    unsigned long ulPreScaleValue;
    unsigned long ulPreScaleBit;
    unsigned short usCNRData;
    unsigned long ulTPMSrc;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) ||
            (ulBase == PWMC_BASE));
    
    //
    // Get TPM clock source
    //
    ulTPMSrc = SysCtlPWMAndUART0ClkGet();
    
    xASSERT((ulFrequency > 0) && (ulFrequency <= ulTPMSrc));

    ulFrepDiv =  ulTPMSrc / ulFrequency;
    
    ulPreScaleValue = 1;
    ulPreScaleBit = 0;
    while((ulFrepDiv / ulPreScaleValue) > 0xFFFF)
    {
        ulPreScaleBit++;
        ulPreScaleValue = ulPreScaleValue * 2;
    }
    
    if(ulPreScaleValue > 128)
    {
        return 0;
    }
    
    usCNRData = ulFrepDiv / ulPreScaleValue;
    xHWREG(ulBase + TPM_MOD) = usCNRData;
    xHWREG(ulBase + TPM_SC) |= ulPreScaleBit ;
    
    ulActualFrep = ulTPMSrc / usCNRData / ulPreScaleValue;
    
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
    unsigned long ulPreScale;
    unsigned long i;
    unsigned short usCNRData;  
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) || 
            (ulBase == PWMC_BASE));
    
    i = xHWREG(ulBase + TPM_SC) & 0xf;
    ulPreScale = 1 << i;
    usCNRData = xHWREG(ulBase + TPM_MOD);
    
    return(SysCtlPWMAndUART0ClkGet() / usCNRData / ulPreScale);
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
//! \note 
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
unsigned long 
PWMFrequencyConfig(unsigned long ulBase, unsigned long ulConfig)
{
    unsigned char ulPreScale;
    unsigned short usMODValue;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) || 
            (ulBase == PWMC_BASE));
    
    ulPreScale = ulConfig & 0x07;
    usMODValue = ((ulConfig & 0xFFFF0000) >> 16);
    
    //
    // Prescale configure
    //
    xHWREG(ulBase + TPM_SC) &= ~TPM_SC_PS_M;
    xHWREG(ulBase + TPM_SC) |= ulPreScale;
    
    //
    // MOD value set
    //
    xHWREG(ulBase + TPM_MOD) = usMODValue;
    
    return(SysCtlPWMAndUART0ClkGet() / usMODValue / ulPreScale); 
}

//*****************************************************************************
//
//! \brief Enable the PWM output of the PWM module. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulMode is the PWM channel output mode.
//!
//! This function is to enable the PWM output of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! \b PWM_CHANNEL0, \b PWM_CHANNEL1, \b PWM_CHANNEL2, \b PWM_CHANNEL3, 
//! \b PWM_CHANNEL4 . 
//!
//! The \e ulMode parameter can be values:
//! \b PWM_MODE_EDGE_ALIGNED1, \b PWM_MODE_EDGE_ALIGNED2, 
//! \b PWM_MODE_CENTER_ALIGNED1, \b PWM_MODE_CENTER_ALIGNED2 . 
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
PWMOutputEnable(unsigned long ulBase, unsigned long ulChannel, 
                                      unsigned long ulMode)
{
    unsigned long ulTemp;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) || 
            (ulBase == PWMC_BASE));
    if(ulBase == PWMA_BASE)
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 5));
    }
    else
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 1));
    }
    xASSERT((ulMode == PWM_MODE_EDGE_ALIGNED1) ||
            (ulMode == PWM_MODE_EDGE_ALIGNED2) || 
            (ulMode == PWM_MODE_CENTER_ALIGNED1)||
            (ulMode == PWM_MODE_CENTER_ALIGNED2));
    
    ulTemp = xHWREG(ulBase + TPM_C0SC + ulChannel * 8);
    xHWREG(ulBase + TPM_C0SC + ulChannel * 8) &= 
                ~(TPM_CNSC_MSB | TPM_CNSC_MSA | TPM_CNSC_ELSB | TPM_CNSC_ELSA);
    ulTemp &= ~(TPM_CNSC_ELSB | TPM_CNSC_ELSA);   
    
    if((ulMode == PWM_MODE_EDGE_ALIGNED1) || 
       (ulMode == PWM_MODE_CENTER_ALIGNED1))
    {
        //
        // High-true pulses
        //
        ulTemp |= TPM_CNSC_ELSB;
    }
    else
    {
        //
        // Low-true pulses
        //
        ulTemp |= TPM_CNSC_ELSA;
    }
    
    xHWREG(ulBase + TPM_C0SC + ulChannel * 8) |= ulTemp;
}

//*****************************************************************************
//
//! \brief Disable the corresponding channel. 
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! \note 
//!
//! \return None.
//
//*****************************************************************************
void 
PWMOutputDisable(unsigned long ulBase, unsigned long ulChannel)
{  
    unsigned long ulTemp;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) || 
            (ulBase == PWMC_BASE));
    if(ulBase == PWMA_BASE)
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 5));
    }
    else
    {
        xASSERT((ulChannel >= 0) && (ulChannel <= 1));
    }
    
    ulTemp = xHWREG(ulBase + TPM_C0SC + ulChannel * 8);
    
    xHWREG(ulBase + TPM_C0SC + ulChannel * 8) &= 
                ~(TPM_CNSC_MSB | TPM_CNSC_MSA | TPM_CNSC_ELSB | TPM_CNSC_ELSA);
    
    //
    // ELSnB:ELSnA 00, Channel disabled
    //
    ulTemp &= ~(TPM_CNSC_ELSB | TPM_CNSC_ELSA);
    
    xHWREG(ulBase + TPM_C0SC + ulChannel * 8) |= ulTemp;
}

//*****************************************************************************
//
//! \brief Sets counter Modulo register value.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulMODValue is the counter reload register new value. It is a value 
//! between 0 and Ox0000FFFF.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
PWMMODSet(unsigned long ulBase, unsigned long ulMODValue)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) || 
            (ulBase == PWMC_BASE));
    xASSERT((ulMODValue >= 0) && (ulMODValue <= 0x0000FFFF));
    
    xHWREG(ulBase + TPM_MOD) = ulMODValue;    
}

//*****************************************************************************
//
//! \brief Get counter Modulo register value.
//!
//! \param ulBase is the base address of the PWM port.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
unsigned long  
PWMMODGet(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) || 
            (ulBase == PWMC_BASE));
    
    return xHWREG(ulBase + TPM_MOD);
}

//*****************************************************************************
//
//! \brief Selects the input trigger to use for starting the counter and/or 
//!        reloading the counter.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulTrigger is the trigger select.
//!
//! The \e ulTrigger parameter can be values:
//! \b PWM_TRGSEL_EXTRGIN, \b PWM_TRGSEL_HSCMP0, \b PWM_TRGSEL_PITRG0, 
//! \b PWM_TRGSEL_PITRG1, \b PWM_TRGSEL_TPM0OF, \b PWM_TRGSEL_TPM1OF, 
//! \b PWM_TRGSEL_TPM2OF, \b PWM_TRGSEL_RTCALARM, \b PWM_TRGSEL_RTCSECONDS, 
//! \b PWM_TRGSEL_LPTMR. 
//!
//! \note This field should only be changed when the LPTPM counter is disabled.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMTriggerSelect(unsigned long ulBase, unsigned long ulTrigger)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) || 
            (ulBase == PWMC_BASE));
    xASSERT((ulTrigger == PWM_TRGSEL_EXTRGIN) || 
            (ulTrigger == PWM_TRGSEL_HSCMP0) ||
            (ulTrigger == PWM_TRGSEL_PITRG0) || 
            (ulTrigger == PWM_TRGSEL_PITRG1) ||
            (ulTrigger == PWM_TRGSEL_TPM0OF) ||
            (ulTrigger == PWM_TRGSEL_TPM1OF) ||
            (ulTrigger == PWM_TRGSEL_TPM2OF) ||
            (ulTrigger == PWM_TRGSEL_RTCALARM) ||
            (ulTrigger == PWM_TRGSEL_RTCSECONDS) ||
            (ulTrigger == PWM_TRGSEL_LPTMR)); 
  
    xHWREG(ulBase + TPM_CONF) &= ~TPM_CONF_TRGSEL_M;
    xHWREG(ulBase + TPM_CONF) |= ulTrigger;
}

//*****************************************************************************
//
//! \brief Counter Reload On Trigger configure.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulCROTCfg is the counter reload on trigger select.
//!
//! The \e ulCROTCfg parameter can be values:
//! \b PWM_CROT_EN, \b PWM_CROT_DIS .
//!
//! \note This field should only be changed when the LPTPM counter is disabled.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMCROTConfigure(unsigned long ulBase, unsigned long ulCROTCfg)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) || 
            (ulBase == PWMC_BASE));
    xASSERT((ulCROTCfg == PWM_CROT_EN) || (ulCROTCfg == PWM_CROT_DIS));
    
    xHWREG(ulBase + TPM_CONF) &= ~TPM_CONF_CROT;
    xHWREG(ulBase + TPM_CONF) |= ulCROTCfg;
}

//*****************************************************************************
//
//! \brief Counter Stop On Overflow.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulCSOOCfg is the counter stop on overflow select.
//!
//! The \e ulCSOOCfg parameter can be values:
//! \b PWM_CSOO_EN, \b PWM_CSOO_DIS .
//!
//! \note This field should only be changed when the LPTPM counter is disabled.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMCSOOConfigure(unsigned long ulBase, unsigned long ulCSOOCfg)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) || 
            (ulBase == PWMC_BASE));
    xASSERT((ulCSOOCfg == PWM_CSOO_EN) || (ulCSOOCfg == PWM_CSOO_DIS));
    
    xHWREG(ulBase + TPM_CONF) &= ~TPM_CONF_CSOO;
    xHWREG(ulBase + TPM_CONF) |= ulCSOOCfg;
}

//*****************************************************************************
//
//! \brief Counter Start on Trigger.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulCSOTCfg is the counter stop on overflow select.
//!
//! The \e ulCSOTCfg parameter can be values:
//! \b PWM_CSOT_EN, \b PWM_CSOT_DIS .
//!
//! \note This field should only be changed when the LPTPM counter is disabled.
//!
//! \return None.
//
//*****************************************************************************
void 
PWMCSOTConfigure(unsigned long ulBase, unsigned long ulCSOTCfg)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE) || 
            (ulBase == PWMC_BASE));
    xASSERT((ulCSOTCfg == PWM_CSOT_EN) || (ulCSOTCfg == PWM_CSOT_DIS));
    
    xHWREG(ulBase + TPM_CONF) &= ~TPM_CONF_CSOT;
    xHWREG(ulBase + TPM_CONF) |= ulCSOTCfg;
    
}
