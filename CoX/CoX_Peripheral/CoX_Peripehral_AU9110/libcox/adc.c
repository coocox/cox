//*****************************************************************************
//
//! \file xadc.c
//! \brief Driver for the ADC Controller.
//! \version V2.1.1.0
//! \date 7/18/2014
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
#include "hw_adc.h"
#include "adc.h"

static xtEventCallback g_fnADCHandlerCallbacks[3] = {0};


//*****************************************************************************
//
//! \brief ADC0 Interrupt Handler.
//!
//! If users want to user the ADC0 Callback feature, Users should promise
//! that the ADC0 Handle in the vector table is ADCIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
ADCIntHandler(void)
{
    unsigned long ulBase = ADC_BASE;
    if (((xHWREG(ulBase + ADC_INT) & ADC_INT_IE) == ADC_INT_IE)
    		&& ((xHWREG(ulBase + ADC_CMPR0) && ADC_CMPR01_CMPF) != ADC_CMPR01_CMPF)
    		&& ((xHWREG(ulBase + ADC_CMPR1) && ADC_CMPR01_CMPF) != ADC_CMPR01_CMPF)
    		)
    {
    	g_fnADCHandlerCallbacks[0](0,0,0,0);
    }

    if((xHWREG(ulBase + ADC_CMPR0) && ADC_CMPR01_CMPF) == ADC_CMPR01_CMPF)
    {
        //
    	// Clear the flag
    	//
    	xHWREG(ulBase + ADC_CMPR0) |= ADC_CMPR01_CMPF;

    }

    if((xHWREG(ulBase + ADC_CMPR1) && ADC_CMPR01_CMPF) == ADC_CMPR01_CMPF)
    {
        //
    	// Clear the flag
    	//
    	xHWREG(ulBase + ADC_CMPR1) |= ADC_CMPR01_CMPF;

    }

}

//*****************************************************************************
//
//! \brief Enable individual ADC interrupt sources.
//!
//! \param ulBase is the base address of the ADC.
//!
//! \return None.
//
//*****************************************************************************
void
ADCIntEnable(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    xHWREG(ulBase + ADC_INT) |= ADC_INT_IE;
}

//*****************************************************************************
//
//! \brief Register user's ADC interrupt function.
//!
//! \param ulBase is the base address of the ADC.
//!
//! \return None.
//
//*****************************************************************************
void
ADCIntDisable(unsigned long ulBase, unsigned long ulIntFlags)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    xHWREG(ulBase + ADC_INT) &= ~ADC_INT_IE;
}

//*****************************************************************************
//
//! \brief Register user's ADC comparator interrupt function.
//!
//! \param ulBase is the base address of the ADC.
//!
//! \return None.
//
//*****************************************************************************
void
ADCIntCallbackInit(unsigned long ulBase, xtEventCallback pfnCallback)
{
	g_fnADCHandlerCallbacks[0] = pfnCallback;
}

//*****************************************************************************
//
//! \brief Register user's ADC comparator interrupt function.
//!
//! \param ulBase is the base address of the ADC.
//!
//! \return None.
//
//*****************************************************************************
void
ADCCompIntCallbackInit(unsigned long ulBase, unsigned long ulComp,
		               xtEventCallback pfnCallback)
{
    if(ulComp == 0)
    {
    	g_fnADCHandlerCallbacks[1] = pfnCallback;
    }
    else
    {
    	g_fnADCHandlerCallbacks[2] = pfnCallback;
	}

}


//*****************************************************************************
//
//! \brief Set the
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulClkDiv is the ADC clock divider.
//!
//! \return None.
//
//*****************************************************************************
void
ADCClockDiv(unsigned long ulBase, unsigned long ulClkDiv)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulClkDiv >= 2) && (ulClkDiv < 0x000000FF));

    xHWREG(ulBase + ADC_DIV) = ulClkDiv;
}

//*****************************************************************************
//
//! \brief ADC Decimation Control.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulOSR is decimation over-sampling ration.
//! \param ulGAIN is the
//!
//!
//! \return None.
//
//*****************************************************************************
void
ADCDEControl(unsigned long ulBase, unsigned long ulOSR,
		                 unsigned long ulGAIN)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Set the OSR
    //
    xHWREG(ulBase + ADC_DEC) &= ~(ADC_DEC_OSR_M << ADC_DEC_OSR_S);
    xHWREG(ulBase + ADC_DEC) |= (ulOSR << ADC_DEC_OSR_S);

    //
    // Set the GAIN
    //
    xHWREG(ulBase + ADC_DEC) &= ~(ADC_DEC_GAIN_M << ADC_DEC_GAIN_S);
    xHWREG(ulBase + ADC_DEC) |= (ulGAIN << ADC_DEC_GAIN_S)

}

//*****************************************************************************
//
//! \brief Enable the ADC moudle.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! Allows the specified sample sequence to be captured when its trigger is
//! detected.
//!
//! \return None.
//
//*****************************************************************************
void
ADCEnable(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // A/D Converter Enable
    //
    xHWREG(ulBase + ADC_EN) |= ADC_EN_CREN;

}

//*****************************************************************************
//
//! \brief Disable the ADC sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! Prevents the sample sequence from being captured when its trigger
//! is detected.  The sample sequence should be disabled before it 
//! is configured.
//!
//! \return None.
//
//*****************************************************************************
void
ADCDisable(unsigned long ulBase)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // A/D Converter Enable
    //
    xHWREG(ulBase + ADC_EN) &= ~ADC_EN_CREN;
}

//*****************************************************************************
//
//! \brief Get the captured data for the ADC sample channel.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! \return Returns the sample data.
//
//*****************************************************************************
unsigned long
ADCDataGet(unsigned long ulBase)
{
    unsigned long ulData;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Get the ADC_DRx register content
    //
    ulData = xHWREG(ulBase + ADC_OUT);

    return (ulData & 0x0000FFFF);
}

//*****************************************************************************
//
//! \brief Enable ADC DMA operation.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! The specified ADC DMA features are enabled.  The ADC can be
//! configured to use DMA for transmit  AD conversion data.
//!
//! \return None.
//
//*****************************************************************************
void
ADCPDMAEnable(unsigned long ulBase)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Enable ADC PDMA Receive Channel
    //
    xHWREG(ulBase + ADC_PDMA) |= ADC_PDMA_RXDMAEN;
}

//*****************************************************************************
//
//! \brief Disable ADC DMA operation.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function is used to disable ADC DMA features that were enabled
//! by ADCPDMAEnable().  The specified SSI DMA features are disabled. 
//!
//! \return None.
//
//*****************************************************************************
void
ADCPDMADisable(unsigned long ulBase)    
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);

    //
    // Enable ADC PDMA Receive Channel
    //
    xHWREG(ulBase + ADC_PDMA) &= ~ADC_PDMA_RXDMAEN;
}

//*****************************************************************************
//
//! \brief Configure the compare data of an ADC digital comparator.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulComp is the index of the comparator to configure.
//! \param usCompData is the compare data.
//! \param ucMatchCnt is the compare match count.
//!
//! This function will configure a comparator data.  When the compare
//! result meets the setting, compare match counter will increase 1, 
//! otherwise, the compare match counter will be clear to 0. When counter
//! value reach the setting of (ucMatchCnt)  then the ADC_INT_COMP0/1 status
//! will be set to 1, if the corresponding interrupt is enabled, and then 
//! interrupt is generated.
//!
//! \return None.
//
//*****************************************************************************
void
ADCCompDataSet(unsigned long ulBase, unsigned long ulComp,
               unsigned long ulCompData, unsigned long ulMatchCnt)
{
    unsigned long ulCompRegAddr;
    unsigned long ulConfig;
    
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulComp >= 0) && (ulComp < 2));
    xASSERT(ulCompData < 0x0000FFFF);
    xASSERT(ulMatchCnt < 16);

    //
    // Get the ADC_CMPRx register address
    //
    ulCompRegAddr = ulBase + ADC_CMPR0 + (4 * ulComp);

    //
    // Set the comparison data
    //
    xHWREG(ulCompRegAddr) &= ~(ADC_CMPR01_CMPD_M << ADC_CMPR01_CMPD_S);
    xHWREG(ulCompRegAddr) |= (ulCompData << ADC_CMPR01_CMPD_S);

    //
    // Set the match data
    //
    xHWREG(ulCompRegAddr) &= ~(ADC_CMPR01_CMPMATCNT_M << ADC_CMPR01_CMPMATCNT_S);
    xHWREG(ulCompRegAddr) |= (ulMatchCnt << ADC_CMPR01_CMPMATCNT_S);

}

//*****************************************************************************
//
//! \brief Configure the compare data of an ADC digital comparator.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulComp is the index of the comparator to configure.
//! \param ulCompCondition is the compare condition.
//!
//! The param \e ulCompCondition can be select form the following data:
//! \b ADC_COMP_LESS_THAN, \b ADC_COMP_GREATER_EQUAL
//!
//! This function will configure a comparator condition. When the internal
//! counter reaches the value (CMPMATCNT+1), the CMPF bit will be set.
//!
//! \return None.
//
//*****************************************************************************
void
ADCCompConditionSet(unsigned long ulBase, unsigned long ulComp,
		                        unsigned long ulCompCondition)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Set the compare condition
    //
    xHWREG(ulBase + ADC_CMPR0 + (4 * ulComp)) &= ~ADC_CMPR01_CMPCOND;
    xHWREG(ulBase + ADC_CMPR0 + (4 * ulComp)) |= ulCompCondition;

}

//*****************************************************************************
//
//! \brief Enable the ADC digital comparator.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulComp is the comparator index number(0, 1), 0 OR 1.
//!
//! Enables the comparator to monitor the along input.
//!
//! \return None.
//
//*****************************************************************************
void
ADCCompEnable(unsigned long ulBase, unsigned long ulComp)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulComp >= 0) && (ulComp < 2));
    xASSERT((ulComp >= 0) && (ulComp <= 0x0000FFFF));

    //
    // Compare enable
    //
    xHWREG(ulBase + ADC_CMPR0 + 4*ulComp) |= ADC_CMPR01_CMPEN;
}

//*****************************************************************************
//
//! \brief Disable the ADC digital comparator .
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulComp is the comparator index number. it can be 0 or 1.
//!
//! Disables the comparator to monitor the along input.
//!
//! \return None.
//
//*****************************************************************************
void
ADCCompDisable(unsigned long ulBase, unsigned long ulComp) 
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Disables the corresponding comparator
    //
    xHWREG(ulBase + ADC_CMPR0 + 4*ulComp) &= ~ADC_CMPR01_CMPEN;
}

//*****************************************************************************
//
//! \brief Enable the ADC digital comparator.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulComp is the comparator index number. it can be 0 or 1.
//!
//! Disables the comparator to monitor the along input.
//!
//! \return None.
//
//*****************************************************************************
void ADCCompIntEnable(unsigned long ulBase, unsigned long ulComp)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Enable the corresponding comparator interrupt
    //
    xHWREG(ulBase + ADC_CMPR0 + 4*ulComp) |= ADC_CMPR01_CMPIE;

}

//*****************************************************************************
//
//! \brief Enable the ADC digital comparator.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulComp is the comparator index number. it can be 0 or 1.
//!
//! Disables the comparator to monitor the along input.
//!
//! \return None.
//
//*****************************************************************************
void ADCCompIntDisable(unsigned long ulBase, unsigned long ulComp)
{
    //
    // Check the arguments
    //
    xASSERT(ulBase == ADC_BASE);
    xASSERT((ulComp >= 0) && (ulComp < 2));

    //
    // Enable the corresponding comparator interrupt
    //
    xHWREG(ulBase + ADC_CMPR0 + 4*ulComp) &= ~ADC_CMPR01_CMPIE;

}

//*****************************************************************************
//
//! \brief Init the ADC  Interrupt Callback function.
//!
//! \param ulBase is the base address of the ADC.
//! \param pfnCallback is the callback function.
//!
//! When there is any ADC intrrupt occrus, Interrupt Handler will
//! call the callback function.
//!
//! param of pfnCallback
//! - pvCBData not used, always 0.
//! - ulEvent is the interrupt event..
//! - ulMsgParam not used, always 0.
//! - pvMsgData not used, always 0.
//! .
//!
//! \return None.
//
//*****************************************************************************
void
xADCIntCallbackInit(unsigned long ulBase, xtEventCallback pfnCallback)
{
	ADCIntCallbackInit(ulBase, pfnCallback);
	ADCCompIntCallbackInit(ulBase, 0, pfnCallback);
	ADCCompIntCallbackInit(ulBase, 1, pfnCallback);
}

//*****************************************************************************
//
//! \brief Enable individual ADC interrupt sources.
//!
//! \param ulBase is the base address of the ADC.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated ADC interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//!
//! - \b xADC_INT_END_CONVERSION - AD conversion interrupt
//! - \b xADC_INT_COMP0 - Comp0 interrupt
//! - \b xADC_INT_COMP1 - Comp1 interrupt
//! .
//!
//! \return None.
//
//*****************************************************************************
void
xADCIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
	if (ulIntFlags == xADC_INT_COMP0)
	{
		ADCCompIntEnable(ulBase, 0);
	}
	else
	{
		ADCCompIntEnable(ulBase, 1);
	}
}

//*****************************************************************************
//
//! \brief Disable ADC sample sequence interrupts.
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulIntFlags is the interrupt flags.
//!
//! This function disables the requested ADC interrupts.
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
xADCIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
	if (ulIntFlags == xADC_INT_COMP0)
	{
		ADCCompIntDisable(ulBase, 0);
	}
	else
	{
		ADCCompIntDisable(ulBase, 1);
	}
}

//*****************************************************************************
//
//! \brief Enable ADC DMA operation.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! The specified ADC DMA features are enabled.  The ADC can be
//! configured to use DMA for transmit AD conversion data.
//!
//! \return None.
//
//*****************************************************************************
void
xADCDMAEnable(unsigned long ulBase)
{
	ADCPDMAEnable(ulBase);
}

//*****************************************************************************
//
//! \brief Disable ADC DMA operation.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! This function is used to disable ADC DMA features that were enabled
//! by xADCDMAEnable().  The specified SSI DMA features are disabled.
//!
//! \return None.
//
//*****************************************************************************
void
xADCDMADisable(unsigned long ulBase)
{
	ADCPDMADisable(ulBase);
}

//*****************************************************************************
//
//! \brief Enable ADC sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! Allows the specified sample sequence to be captured when its trigger is
//! detected.  A sample sequence must be configured before it is enabled.
//!
//! \return None.
//
//*****************************************************************************
void
xADCEnable(unsigned long ulBase)
{
	ADCEnable(ulBase);
}

//*****************************************************************************
//
//! \brief Disable the ADC sample sequence.
//!
//! \param ulBase is the base address of the ADC module.
//!
//! Prevents the sample sequence from being captured when its trigger
//! is detected.
//! \note The sample sequence should be disabled before it is configured.
//!
//! \return None.
//
//*****************************************************************************
void xADCDisable(unsigned long ulBase)
{
	ADCDisable(ulBase);
}

//*****************************************************************************
//
//! \brief Enable the ADC digital comparator .
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulCompID is the comparator ID.
//!
//! Enables the comparator to monitor the along input.
//!
//! \return None.
//
//*****************************************************************************
void
xADCCompEnable(unsigned long ulBase, unsigned long ulCompID)
{
	ADCCompEnable(ulBase, ulCompID);
}

//*****************************************************************************
//
//! \brief Disable the ADC digital comparator .
//!
//! \param ulBase is the base address of the ADC module.
//! \param ulCompID is the comparator ID.
//!
//! Disables the comparator to monitor the along input.
//!
//! \note In the Stellaris Implement, The comparators do note need to enable.
//! Users can switch to use other comparators or not use comparator function.
//!
//! \return None.
//
//*****************************************************************************
void
xADCCompDisable(unsigned long ulBase, unsigned long ulCompID)
{
	ADCCompDisable(ulBase, ulCompID);
}


