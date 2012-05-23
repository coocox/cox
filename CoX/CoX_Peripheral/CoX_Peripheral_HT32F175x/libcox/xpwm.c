//*****************************************************************************
//
//! \file xpwm.c
//! \brief Driver for the PWM
//! \version V2.2.1.0
//! \date 3/31/2012
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
#include "xpwm.h"

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
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
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
    unsigned long ulChannelTemp;

    ulChannelTemp = (ulBase == PWMA_BASE) ? ulChannel : (ulChannel - 4);
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 3)));
    
    xASSERT((ulConfig == PWM_ONE_SHOT_MODE) || 
            (ulConfig == PWM_TOGGLE_MODE));
    
    //
    // Configure as output Mode
    //
    xHWREG(ulBase + TIMER_CH0ICFR + ulChannel * 4) &= ~TIMER_CH0ICFR_CH0CCS_M;

    //
    // Select the pwm mode
    //
    if(ulConfig == xPWM_ONE_SHOT_MODE)
    {
        xHWREG(ulBase + TIMER_MDCFR) |= TIMER_MDCFR_SPMSET;
    }
    else
    {
        xHWREG(ulBase + TIMER_MDCFR) &= ~TIMER_MDCFR_SPMSET;
    } 
    
    xHWREG(ulBase + TIMER_CNTCFR) &= ~TIMER_CNTCFR_CMSEL_M;
    xHWREG(ulBase + TIMER_CNTCFR) |= PWM_CNT_MODE_DOWN;
    xHWREG(ulBase + TIMER_CH0OCFR + ulChannelTemp * 4) &= ~TIMER_CH0OCFR_CH0OM_M;
    xHWREG(ulBase + TIMER_CH0OCFR + ulChannelTemp * 4) |= PWM_OM_1;   
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
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulConfig parameter can be values:
//! \b PWM_ONE_SHOT_MODE, PWM_TOGGLE_MODE
//!
//! The \e ulMode parameter can be values:
//! \b PWM_OM_1, PWM_OM_2
//!
//! The \e ulDir parameter can be values:
//! \b PWM_CNT_MODE_UP, PWM_CNT_MODE_DOWN
//!
//! \return None.
//
//*****************************************************************************
void 
PWMInitConfigure(unsigned long ulBase, unsigned long ulChannel,
                 unsigned long ulConfig, unsigned long ulMode, unsigned long ulDir)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = (ulBase == PWMA_BASE) ? ulChannel : (ulChannel - 4);
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 3)));
    
    xASSERT((ulConfig == PWM_ONE_SHOT_MODE) || 
            (ulConfig == PWM_TOGGLE_MODE));
    xASSERT((ulMode == PWM_OM_1) || (ulMode == PWM_OM_2));
    xASSERT((ulDir == PWM_CNT_MODE_UP) || (ulDir == PWM_CNT_MODE_DOWN));
    
    //
    // Configure as output Mode
    //
    xHWREG(ulBase + TIMER_CH0ICFR + ulChannel * 4) &= ~TIMER_CH0ICFR_CH0CCS_M;
    
    //
    // Select the pwm mode
    //
    if(ulConfig == PWM_ONE_SHOT_MODE)
    {
        xHWREG(ulBase + TIMER_MDCFR) |= TIMER_MDCFR_SPMSET;
    }
    else
    {
        xHWREG(ulBase + TIMER_MDCFR) &= ~TIMER_MDCFR_SPMSET;
    }
    
    //
    // Selcet the count direction
    //
    xHWREG(ulBase + TIMER_CNTCFR) &= ~TIMER_CNTCFR_DIR;
    xHWREG(ulBase + TIMER_CNTCFR) |= ulDir;
    
    //
    // Select the Output Compare Mode
    //
    xHWREG(ulBase + TIMER_CH0OCFR + ulChannelTemp * 4) &= ~TIMER_CH0OCFR_CH0OM_M;
    xHWREG(ulBase + TIMER_CH0OCFR + ulChannelTemp * 4) |= ulMode;    
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
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
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

    ulChannelTemp = (ulBase == PWMA_BASE) ? ulChannel : (ulChannel - 4);
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 3)));
    xASSERT(((ulDuty > 0) || (ulDuty <= 100)));

    ulCMRData = (PWMCRRGet(ulBase) *  ulDuty) / 100;
    if ((PWMCRRGet(ulBase) *  ulDuty) / 100 == 0)
    {
        ulCMRData = 0;
    }
    
    xHWREG(ulBase + TIMER_CH0CCR + ulChannelTemp * 4) = ulCMRData;
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
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
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

    ulChannelTemp = (ulBase == PWMA_BASE) ? ulChannel : (ulChannel - 4);
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT((ulChannelTemp >= 0) || (ulChannelTemp <= 3));

    ulCNRData = PWMCRRGet(ulBase);
    ulCMRData = xHWREG(ulBase + TIMER_CH0CCR + ulChannelTemp * 4);
    ulChannelTemp = (ulCMRData + 1) * 100 / (ulCNRData + 1);
    return ulChannelTemp;
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
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! //! The \e ulIntType parameter can be values:
//! \b PWM_INT_CHXCC, \b PWM_INT_UEV1.
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
    unsigned long ulChannelTemp;  
    ulChannelTemp = (ulBase == PWMA_BASE) ? ulChannel : (ulChannel - 4);
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 3)));
    xASSERT((ulIntType == PWM_INT_CHXCC) || (ulIntType == PWM_INT_UEV1));

    if (ulIntType == PWM_INT_UEV1)
    {
        xHWREG(ulBase + TIMER_ICTR) |= PWM_INT_UEV1; 
    }
    else
    {
        xHWREG(ulBase + TIMER_ICTR) |= (PWM_INT_CHXCC << ulChannelTemp);
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
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! //! The \e ulIntType parameter can be values:
//! \b PWM_INT_CHXCC, \b PWM_INT_UEV1.
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
    unsigned long ulChannelTemp;  
    ulChannelTemp = (ulBase == PWMA_BASE) ? ulChannel : (ulChannel - 4);    
  
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 3)));
    xASSERT((ulIntType == PWM_INT_CHXCC) || (ulIntType == PWM_INT_UEV1));

    if (ulIntType == PWM_INT_UEV1)
    {
        xHWREG(ulBase + TIMER_ICTR) &= ~PWM_INT_UEV1; 
    }
    else
    {
        xHWREG(ulBase + TIMER_ICTR) &= ~(PWM_INT_CHXCC << ulChannelTemp);
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
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulIntType parameter can be values:
//! \b PWM_INT_CHXCC, \b PWM_INT_UEV1.
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
    unsigned long ulChannelTemp; 
    unsigned long ulIntStatus;
    ulChannelTemp = (ulBase == PWMA_BASE) ? ulChannel : (ulChannel - 4);
   
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 3)));
    xASSERT((ulIntType == PWM_INT_CHXCC) || (ulIntType == PWM_INT_UEV1));

    if (ulIntType == PWM_INT_UEV1)
    {
        ulIntStatus = xHWREG(ulBase + TIMER_INTSR) & ulIntType;
        if(ulIntStatus != 0)
        {
            return xtrue;
        }
    }
    else
    {
        ulIntStatus = xHWREG(ulBase + TIMER_INTSR) & (PWM_INT_CHXCC << ulChannelTemp);
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
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulIntType parameter can be values:
//! \b PWM_INT_CHXCC, \b PWM_INT_UEV1.
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
    unsigned long ulChannelTemp; 
    ulChannelTemp = (ulBase == PWMA_BASE) ? ulChannel : (ulChannel - 4);
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 3)));
    xASSERT((ulIntType == PWM_INT_CHXCC) || (ulIntType == PWM_INT_UEV1));

    if (ulIntType == PWM_INT_UEV1)
    {
        xHWREG(ulBase + TIMER_INTSR) &= ~ulIntType;
    }
    else
    {
        xHWREG(ulBase + TIMER_INTSR) &= ~(PWM_INT_CHXCC << ulChannelTemp);
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));

    xHWREG(ulBase + TIMER_CTR) |= TIMER_CTR_TME;
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));

    xHWREG(ulBase + TIMER_CTR) &= ~TIMER_CTR_TME;
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
    unsigned long ulPreScale;
    unsigned short usCNRData;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT((ulFrequency > 0) || (ulFrequency <= xSysCtlClockGet(ulBase)));

    ulFrepDiv =  xSysCtlClockGet() / ulFrequency;
    
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
    xHWREG(ulBase + TIMER_CRR) = usCNRData;
    xHWREG(ulBase + TIMER_PSCR) = ulPreScale - 1;
    
    ulActualFrep = xSysCtlClockGet() / usCNRData / ulPreScale;
    
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
    unsigned short usCNRData;  
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    
    ulPreScale = xHWREG(ulBase + TIMER_PSCR) + 1;
    usCNRData = xHWREG(ulBase + TIMER_CRR);
    
    return(xSysCtlClockGet() / usCNRData / ulPreScale);
     
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
    unsigned long ulPreScale;
    unsigned short usCNRData;
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    
    ulPreScale = ulConfig & 0xFFFF;
    usCNRData = ((ulConfig & 0xFFFF0000) >> 16);
    
    xHWREG(ulBase + TIMER_CRR) = usCNRData;
    xHWREG(ulBase + TIMER_PSCR) = ulPreScale - 1;
    
    return(xSysCtlClockGet() / usCNRData / ulPreScale);    
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
    unsigned long ulChannelTemp;
    ulChannelTemp = (ulBase == PWMA_BASE) ? ulChannel : (ulChannel - 4);
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 3)));
    
    //
    // Enable the corresponding channel
    //
    xHWREG(ulBase + TIMER_CHCTR) |= (1 << ulChannelTemp * 2);
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
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
void 
PWMOutputDisable(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;
    ulChannelTemp = (ulBase == PWMA_BASE) ? ulChannel : (ulChannel - 4);
    
    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 3)));
    
    //
    // Enable the corresponding channel
    //
    xHWREG(ulBase + TIMER_CHCTR) &= ~(1 << ulChannelTemp * 2);
}

//*****************************************************************************
//
//! \brief Sets counter reload register value.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulCRRValue is the counter reload register new value. It is a value 
//! between 0 and Ox0000FFFF.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
PWMCRRSet(unsigned long ulBase, unsigned long ulCRRValue)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT((ulCRRValue >= 0) && (ulCRRValue <= 0x0000FFFF));
    
    xHWREG(ulBase + TIMER_CRR) = ulCRRValue;    
}

//*****************************************************************************
//
//! \brief Get counter reload register value.
//!
//! \param ulBase is the base address of the PWM port.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
unsigned long  
PWMCRRGet(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    
    return (xHWREG(ulBase + TIMER_CRR));
}
