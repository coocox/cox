//*****************************************************************************
//
//! \file pwm.c
//! \brief Driver for the PWM
//! \version V2.2.1.0
//! \date 11/15/2013
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
#include "hw_gpio.h"
#include "hw_sysctl.h"
#include "hw_pwm.h"



//*****************************************************************************
//
// An array is PWM Callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnPWMHandlerCallbacks[18]={0};


//*****************************************************************************
//
//! \brief The PWMA default IRQ, declared in StartUp code.
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
//! Only the last 6 bits(0~5 bits) is effective.
//!
//! \return None.
//
//*****************************************************************************
void
PWM0CH0_IRQHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = PWMA_BASE;

    //
    // Clear the PWMA INT Flag
    //
    ulPWMStastus = xHWREG(ulBase + PWM_INTSTS) & 0x01010101;
    xHWREG(ulBase + PWM_INTSTS) = ulPWMStastus;


    if (g_pfnPWMHandlerCallbacks[0] != 0)
    {
        if(ulPWMStastus & 0x0101)
        {
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
        if((ulPWMStastus & 0x01010000))
        {
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_CAP, (1 << PWM_CHANNEL0), 0);
        }
    }
}

//*****************************************************************************
//
//! \brief The PWMA default IRQ, declared in StartUp code.
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
//! Only the last 6 bits(0~5 bits) is effective.
//!
//! \return None.
//
//*****************************************************************************
void
PWM0CH1_IRQHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = PWMA_BASE;

    //
    // Clear the PWMA INT Flag
    //
    ulPWMStastus = xHWREG(ulBase + PWM_INTSTS) & 0x02020202;
    xHWREG(ulBase + PWM_INTSTS) = ulPWMStastus;


    if (g_pfnPWMHandlerCallbacks[0] != 0)
    {
        if(ulPWMStastus & 0x0202)
        {
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
        if((ulPWMStastus & 0x02020000))
        {
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_CAP, (1 << PWM_CHANNEL1), 0);
        }
    }
}

//*****************************************************************************
//
//! \brief The PWMA default IRQ, declared in StartUp code.
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
//! Only the last 6 bits(0~5 bits) is effective.
//!
//! \return None.
//
//*****************************************************************************
void
PWM0CH2_IRQHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = PWMA_BASE;

    //
    // Clear the PWMA INT Flag
    //
    ulPWMStastus = xHWREG(ulBase + PWM_INTSTS) & 0x04040404;
    xHWREG(ulBase + PWM_INTSTS) = ulPWMStastus;


    if (g_pfnPWMHandlerCallbacks[0] != 0)
    {
        if(ulPWMStastus & 0x0404)
        {
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
        if((ulPWMStastus & 0x04040000))
        {
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_CAP, (1 << PWM_CHANNEL2), 0);
        }
    }
}

//*****************************************************************************
//
//! \brief The PWMA default IRQ, declared in StartUp code.
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
//! Only the last 6 bits(0~5 bits) is effective.
//!
//! \return None.
//
//*****************************************************************************
void
PWM0CH3_IRQHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = PWMA_BASE;

    //
    // Clear the PWMA INT Flag
    //
    ulPWMStastus = xHWREG(ulBase + PWM_INTSTS) & 0x08080808;
    xHWREG(ulBase + PWM_INTSTS) = ulPWMStastus;


    if (g_pfnPWMHandlerCallbacks[0] != 0)
    {
        if(ulPWMStastus & 0x0808)
        {
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
        if((ulPWMStastus & 0x08080000))
        {
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_CAP, (1 << PWM_CHANNEL3), 0);
        }
    }
}

//*****************************************************************************
//
//! \brief The PWMA default IRQ, declared in StartUp code.
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
//! Only the last 6 bits(0~5 bits) is effective.
//!
//! \return None.
//
//*****************************************************************************
void
PWM0CH4_IRQHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = PWMA_BASE;

    //
    // Clear the PWMA INT Flag
    //
    ulPWMStastus = xHWREG(ulBase + PWM_INTSTS) & 0x10101010;
    xHWREG(ulBase + PWM_INTSTS) = ulPWMStastus;


    if (g_pfnPWMHandlerCallbacks[0] != 0)
    {
        if(ulPWMStastus & 0x1010)
        {
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
        if((ulPWMStastus & 0x10100000))
        {
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_CAP, (1 << PWM_CHANNEL4), 0);
        }
    }
}

//*****************************************************************************
//
//! \brief The PWMA default IRQ, declared in StartUp code.
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
//! Only the last 6 bits(0~5 bits) is effective.
//!
//! \return None.
//
//*****************************************************************************
void
PWM0CH5_IRQHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = PWMA_BASE;

    //
    // Clear the PWMA INT Flag
    //
    ulPWMStastus = xHWREG(ulBase + PWM_INTSTS) & 0x20202020;
    xHWREG(ulBase + PWM_INTSTS) = ulPWMStastus;


    if (g_pfnPWMHandlerCallbacks[0] != 0)
    {
        if(ulPWMStastus & 0x2020)
        {
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
        if((ulPWMStastus & 0x20200000))
        {
            g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_CAP, (1 << PWM_CHANNEL5), 0);
        }
    }
}

//*****************************************************************************
//
//! \brief The PWMB default IRQ, declared in StartUp code.
//!
//! \param None.
//!
//! This function is to give a default PWMB IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a
//! interrupt,bit0 in ulPWMStastus shows PWM_CHANNEL0,bit1 in ulPWMStastus
//! shows PWM_CHANNEL1,bit2 in ulPWMStastus shows PWM_CHANNEL2 and bit3 in
//! ulPWMStastus shows PWM_CHANNEL3.
//! Only the last 6 bits(0~5 bits) is effective.
//!
//! \return None.
//
//*****************************************************************************
void
PWM1CH0_IRQHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = PWMB_BASE;

    //
    // Clear the PWMB INT Flag
    //
    ulPWMStastus = xHWREG(ulBase + PWM_INTSTS) & 0x01010101;
    xHWREG(ulBase + PWM_INTSTS) = ulPWMStastus;


    if (g_pfnPWMHandlerCallbacks[0] != 0)
    {
        if(ulPWMStastus & 0x0101)
        {
            g_pfnPWMHandlerCallbacks[1](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
        if((ulPWMStastus & 0x01010000))
        {
            g_pfnPWMHandlerCallbacks[1](0, PWM_EVENT_CAP, (1 << PWM_CHANNEL0), 0);
        }
    }
}

//*****************************************************************************
//
//! \brief The PWMB default IRQ, declared in StartUp code.
//!
//! \param None.
//!
//! This function is to give a default PWMB IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a
//! interrupt,bit0 in ulPWMStastus shows PWM_CHANNEL0,bit1 in ulPWMStastus
//! shows PWM_CHANNEL1,bit2 in ulPWMStastus shows PWM_CHANNEL2 and bit3 in
//! ulPWMStastus shows PWM_CHANNEL3.
//! Only the last 6 bits(0~5 bits) is effective.
//!
//! \return None.
//
//*****************************************************************************
void
PWM1CH1_IRQHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = PWMB_BASE;

    //
    // Clear the PWMB INT Flag
    //
    ulPWMStastus = xHWREG(ulBase + PWM_INTSTS) & 0x02020202;
    xHWREG(ulBase + PWM_INTSTS) = ulPWMStastus;


    if (g_pfnPWMHandlerCallbacks[0] != 0)
    {
        if(ulPWMStastus & 0x0202)
        {
            g_pfnPWMHandlerCallbacks[1](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
        if((ulPWMStastus & 0x02020000))
        {
            g_pfnPWMHandlerCallbacks[1](0, PWM_EVENT_CAP, (1 << PWM_CHANNEL1), 0);
        }
    }
}

//*****************************************************************************
//
//! \brief The PWMB default IRQ, declared in StartUp code.
//!
//! \param None.
//!
//! This function is to give a default PWMB IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a
//! interrupt,bit0 in ulPWMStastus shows PWM_CHANNEL0,bit1 in ulPWMStastus
//! shows PWM_CHANNEL1,bit2 in ulPWMStastus shows PWM_CHANNEL2 and bit3 in
//! ulPWMStastus shows PWM_CHANNEL3.
//! Only the last 6 bits(0~5 bits) is effective.
//!
//! \return None.
//
//*****************************************************************************
void
PWM1CH2_IRQHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = PWMB_BASE;

    //
    // Clear the PWMB INT Flag
    //
    ulPWMStastus = xHWREG(ulBase + PWM_INTSTS) & 0x04040404;
    xHWREG(ulBase + PWM_INTSTS) = ulPWMStastus;


    if (g_pfnPWMHandlerCallbacks[0] != 0)
    {
        if(ulPWMStastus & 0x0404)
        {
            g_pfnPWMHandlerCallbacks[1](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
        if((ulPWMStastus & 0x04040000))
        {
            g_pfnPWMHandlerCallbacks[1](0, PWM_EVENT_CAP, (1 << PWM_CHANNEL2), 0);
        }
    }
}

//*****************************************************************************
//
//! \brief The PWMB default IRQ, declared in StartUp code.
//!
//! \param None.
//!
//! This function is to give a default PWMB IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a
//! interrupt,bit0 in ulPWMStastus shows PWM_CHANNEL0,bit1 in ulPWMStastus
//! shows PWM_CHANNEL1,bit2 in ulPWMStastus shows PWM_CHANNEL2 and bit3 in
//! ulPWMStastus shows PWM_CHANNEL3.
//! Only the last 6 bits(0~5 bits) is effective.
//!
//! \return None.
//
//*****************************************************************************
void
PWM1CH3_IRQHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = PWMB_BASE;

    //
    // Clear the PWMB INT Flag
    //
    ulPWMStastus = xHWREG(ulBase + PWM_INTSTS) & 0x08080808;
    xHWREG(ulBase + PWM_INTSTS) = ulPWMStastus;


    if (g_pfnPWMHandlerCallbacks[0] != 0)
    {
        if(ulPWMStastus & 0x0808)
        {
            g_pfnPWMHandlerCallbacks[1](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
        if((ulPWMStastus & 0x08080000))
        {
            g_pfnPWMHandlerCallbacks[1](0, PWM_EVENT_CAP, (1 << PWM_CHANNEL3), 0);
        }
    }
}

//*****************************************************************************
//
//! \brief The PWMB default IRQ, declared in StartUp code.
//!
//! \param None.
//!
//! This function is to give a default PWMB IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a
//! interrupt,bit0 in ulPWMStastus shows PWM_CHANNEL0,bit1 in ulPWMStastus
//! shows PWM_CHANNEL1,bit2 in ulPWMStastus shows PWM_CHANNEL2 and bit3 in
//! ulPWMStastus shows PWM_CHANNEL3.
//! Only the last 6 bits(0~5 bits) is effective.
//!
//! \return None.
//
//*****************************************************************************
void
PWM1CH4_IRQHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = PWMB_BASE;

    //
    // Clear the PWMB INT Flag
    //
    ulPWMStastus = xHWREG(ulBase + PWM_INTSTS) & 0x10101010;
    xHWREG(ulBase + PWM_INTSTS) = ulPWMStastus;


    if (g_pfnPWMHandlerCallbacks[0] != 0)
    {
        if(ulPWMStastus & 0x1010)
        {
            g_pfnPWMHandlerCallbacks[1](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
        if((ulPWMStastus & 0x10100000))
        {
            g_pfnPWMHandlerCallbacks[1](0, PWM_EVENT_CAP, (1 << PWM_CHANNEL4), 0);
        }
    }
}

//*****************************************************************************
//
//! \brief The PWMB default IRQ, declared in StartUp code.
//!
//! \param None.
//!
//! This function is to give a default PWMB IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a
//! interrupt,bit0 in ulPWMStastus shows PWM_CHANNEL0,bit1 in ulPWMStastus
//! shows PWM_CHANNEL1,bit2 in ulPWMStastus shows PWM_CHANNEL2 and bit3 in
//! ulPWMStastus shows PWM_CHANNEL3.
//! Only the last 6 bits(0~5 bits) is effective.
//!
//! \return None.
//
//*****************************************************************************
void
PWM1CH5_IRQHandler(void)
{
    unsigned long ulPWMStastus;
    unsigned long ulBase = PWMB_BASE;

    //
    // Clear the PWMB INT Flag
    //
    ulPWMStastus = xHWREG(ulBase + PWM_INTSTS) & 0x20202020;
    xHWREG(ulBase + PWM_INTSTS) = ulPWMStastus;


    if (g_pfnPWMHandlerCallbacks[0] != 0)
    {
        if(ulPWMStastus & 0x2020)
        {
            g_pfnPWMHandlerCallbacks[1](0, PWM_EVENT_PWM, ulPWMStastus, 0);
        }
        if((ulPWMStastus & 0x20200000))
        {
            g_pfnPWMHandlerCallbacks[1](0, PWM_EVENT_CAP, (1 << PWM_CHANNEL5), 0);
        }
    }
}

//*****************************************************************************
//
//! \brief The PWMA default IRQ, declared in StartUp code.
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
//! Only the last 6 bits(0~5 bits) is effective.
//!
//! \return None.
//
//*****************************************************************************
void
PWM0_BRK_IRQHandler(void)
{
    unsigned long ulPWMStastus;
	unsigned long ulBase = PWMA_BASE;

	//
	// Clear the PWMB INT Flag
	//
	ulPWMStastus = xHWREG(ulBase + PWM_INTSTS) & 0xC0;
	xHWREG(ulBase + PWM_INTSTS) = ulPWMStastus;

	if (g_pfnPWMHandlerCallbacks[0] != 0)
	{
		if(ulPWMStastus & 0xC0)
		{
			g_pfnPWMHandlerCallbacks[0](0, PWM_EVENT_PWM, (ulPWMStastus), 0);
		}
	}
}

//*****************************************************************************
//
//! \brief The PWMB default IRQ, declared in StartUp code.
//!
//! \param None.
//!
//! This function is to give a default PWMB IRQ service.
//!
//! \note The Callback function have two effective parameters,One is indicate
//! is a PWM or Capture interrupt.And the other one show which channel have a
//! interrupt,bit0 in ulPWMStastus shows PWM_CHANNEL0,bit1 in ulPWMStastus
//! shows PWM_CHANNEL1,bit2 in ulPWMStastus shows PWM_CHANNEL2 and bit3 in
//! ulPWMStastus shows PWM_CHANNEL3.
//! Only the last 6 bits(0~5 bits) is effective.
//!
//! \return None.
//
//*****************************************************************************
void
PWM1_BRK_IRQHandler(void)
{
    unsigned long ulPWMStastus;
	unsigned long ulBase = PWMB_BASE;

	//
	// Clear the PWMB INT Flag
	//
	ulPWMStastus = xHWREG(ulBase + PWM_INTSTS) & 0xC0;
	xHWREG(ulBase + PWM_INTSTS) = ulPWMStastus;


	if (g_pfnPWMHandlerCallbacks[0] != 0)
	{
		if(ulPWMStastus & 0xC0)
		{
			g_pfnPWMHandlerCallbacks[1](0, PWM_EVENT_PWM, (ulPWMStastus), 0);
		}
	}
}

//*****************************************************************************
//
//! \internal
//! \brief Get the PWM module's clock.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//!
//! The \e ulChannel parameter can be values:0~3
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
    unsigned long ulChannelTemp = 0;
    unsigned long ulPWMFreq;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannel >= 0) || (ulChannel <= 5)));

    ulChannelTemp += (ulBase == PWMA_BASE) ? 0 : 6;
    switch(ulChannelTemp)
    {
        case PWM_CHANNEL0:
        case PWM_CHANNEL1:
            ulTemp = ((xHWREG(SYSCLK_CLKSEL2) & 0x7) >> 0);
            break;

        case PWM_CHANNEL2:
        case PWM_CHANNEL3:
            ulTemp = ((xHWREG(SYSCLK_CLKSEL2) & 0x70) >>
                      4);
            break;
        case PWM_CHANNEL4:
        case PWM_CHANNEL5:
            ulTemp = ((xHWREG(SYSCLK_CLKSEL2) & 0x700) >>
                      8);
            break;
        case 6:
        case 7:
            ulTemp = ((xHWREG(SYSCLK_CLKSEL2) & 0x7000) >>
                      12);
            break;
        case 8:
		case 9:
			ulTemp = ((xHWREG(SYSCLK_CLKSEL2) & 0x70000) >>
					  16);
			break;
        case 10:
		case 11:
			ulTemp = ((xHWREG(SYSCLK_CLKSEL2) & 0x700000) >>
					  20);
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
        ulPWMFreq = xSysCtlClockGet();
    }
    else if (ulTemp == 3)
    {
        ulPWMFreq = 22118400;
    }
    else
    {
        ulPWMFreq = 32768;
    }
    return ulPWMFreq;
}

//*****************************************************************************
//
//! \brief Initialize and configure the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//! \param ulConfig is the configuration of PWM channel.
//!
//! This function is to initialize and configure channel of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3
//!
//! The \e ulConfig parameter is the logical OR of four values: The PWM mode,
//! Inverter or not,and use dead zero or not and dead zone length.
//! \b PWM_ONE_SHOT_MODE,\b PWM_TOGGLE_MODE is the mode selecet.
//! \b PWM_OUTPUT_INVERTER_EN,
//! \b PWM_OUTPUT_INVERTER_DIS is to enable Inverter or not.\b PWM_DEAD_ZONE_EN
//! \b PWM_DEAD_ZONE_DIS is to enable dead zone Generator or not.
//! The dead zone length will be set at the 8~15 bits of the ulConfig.
//!
//! \note When Dead-Zone Generator is enabled, the pair of PWM0 and PWM1
//! becomes a complementary pair for PWM group A.
//!
//! \return None.
//
//*****************************************************************************
void
PWMInitConfigure(unsigned long ulBase, unsigned long ulChannel,
                 unsigned long ulConfig)
{
//    unsigned long ulChannelTemp;
//
//    ulChannelTemp = (ulBase == PWMA_BASE) ? ulChannel : (ulChannel + 6);

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 11)));
    xASSERT((ulConfig & 0xFFFFFF00) == 0);
    xASSERT(((ulConfig & PWM_OUTPUT_INVERTER_EN) == PWM_OUTPUT_INVERTER_EN) ||
            ((ulConfig & PWM_OUTPUT_INVERTER_EN) == PWM_OUTPUT_INVERTER_DIS));

    xASSERT(((ulConfig & PWM_TOGGLE_MODE) == PWM_ONE_SHOT_MODE) ||
            ((ulConfig & PWM_TOGGLE_MODE) == PWM_TOGGLE_MODE));

    xASSERT(((ulConfig & PWM_DEAD_ZONE_EN) == PWM_DEAD_ZONE_EN) ||
            ((ulConfig & PWM_DEAD_ZONE_EN) == PWM_DEAD_ZONE_DIS));


//    SysCtlPeripheralReset(SYSCTL_PERIPH_PWM01);

    xHWREG(ulBase + PWM_CTL) |= ((ulConfig & 0x3F3F) << (ulChannel));
    if (ulConfig & PWM_DEAD_ZONE_EN)
    {
        xHWREG(ulBase + PWM_DTCTL) |= (PWM_DEAD_ZONE_EN << (ulChannel >> 1));
        xHWREG(ulBase + PWM_DTCTL) &= ~(PWM_DTCTL_DTCNT01_M <<
                                       (ulChannel >> 1) * 8);
        xHWREG(ulBase + PWM_DTCTL) |= (((ulConfig >> 8) & PWM_DTCTL_DTCNT01_M) <<
                                    (ulChannel >> 1) * 8);
    }
}


//*****************************************************************************
//
//! \brief Set the PWM frequency of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//! \param ulFrequency is the PWM frequency of PWM channel.
//!
//! This function is to set the PWM frequency of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~3
//!
//! The \e ulFrequency parameter can be values: Any values ,ulFrequency > 0 &&
//! ulFrequency < PWM module input clock.
//!
//! \return the Actual Frequency of PWM.
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

//    ulChannelTemp = ulChannel;
    ulChannelTemp = ulChannel ;


    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
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

    xHWREG(ulBase + PWM_CLKPSC) &= ~(PWM_PPR_CP01_M << (ulChannelTemp / 2));
    xHWREG(ulBase + PWM_CLKPSC) |= ((usPreScale - 1) << (ulChannelTemp / 2));

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
    xHWREG(ulBase + PWM_CLKDIV) &= ~(PWM_CSR_CSR0_M << (ulChannelTemp << 2));
    xHWREG(ulBase + PWM_CLKDIV) |= (ucDivider << (ulChannelTemp << 2));

    xHWREG(ulBase + PWM_PERIOD0 +(ulChannelTemp * 4)) = usCNRData - 1;

    return ulActualFrep;
}

//*****************************************************************************
//
//! \brief Set the PWM frequency of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//! \param ulConfig is the configuration of PWM channel frequency.
//!
//! This function is to set the PWM frequency of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3
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
    xASSERT((ulBase == PWMA_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_CLKPSC) &= ~(PWM_PPR_CP01_M << (ulChannelTemp / 2 * 8));
    xHWREG(ulBase + PWM_CLKPSC) |= (((ulConfig & 0xFF0000) >> 16)
                                << (ulChannelTemp / 2 * 8));

    xHWREG(ulBase + PWM_CLKDIV) &= ~(PWM_CSR_CSR0_M << (ulChannelTemp << 2));
    xHWREG(ulBase + PWM_CLKDIV) |= (((ulConfig & 0x7000000) >> 24)
                                << (ulChannelTemp << 2));

    xHWREG(ulBase + PWM_PERIOD0 +(ulChannelTemp * 4)) = (ulConfig & 0xFFFF);

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
//! The \e ulChannel parameter can be values: 0~3
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));
    xASSERT(((ulDuty > 0) || (ulDuty <= 100)));


    ulCMRData = (xHWREG(ulBase + PWM_PERIOD0 +(ulChannelTemp * 4)) + 1) *
                ulDuty / 100 - 1;
    if ((xHWREG(ulBase + PWM_CMPDAT0 +(ulChannelTemp * 4)) + 1) *ulDuty / 100 == 0)
    {
        ulCMRData = 0;
    }
    xHWREG(ulBase + PWM_CMPDAT0 +(ulChannelTemp * 4)) = ulCMRData;
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
    unsigned long ulChannelTemp;
    unsigned long ulCMRData;
    unsigned long ulCNRData;

    ulChannelTemp = ulChannel;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    ulCNRData = (xHWREG(ulBase + PWM_PERIOD0 +(ulChannelTemp * 4)));
    ulCMRData = (xHWREG(ulBase + PWM_CMPDAT0 +(ulChannelTemp * 4)));
    ulChannelTemp = (ulCMRData + 1) * 100 / (ulCNRData + 1);
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
//! The \e ulChannel parameter can be values: 0~3
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
unsigned long
PWMFrequencyGet(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;
    unsigned long ulCNRData;
    unsigned char ucDivider;
    unsigned short usPreScale;

    ulChannelTemp = ulChannel;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    usPreScale = ((xHWREG(ulBase + PWM_CLKPSC) >> (ulChannelTemp << 2))  &
                   PWM_PPR_CP01_M);

    ucDivider = (xHWREG(ulBase + PWM_CLKDIV) >> (ulChannelTemp << 2)) &
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
    ulCNRData = xHWREG(ulBase + PWM_PERIOD0 +(ulChannelTemp * 4));
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
//! The \e ulChannel parameter can be values:0~3
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_POEN) |= (1 << (ulChannelTemp));
}

//*****************************************************************************
//
//! \brief Disable the PWM output of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//!
//! This function is to disable the PWM output of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~3
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_POEN) &= ~(1 << (ulChannelTemp));
}

//*****************************************************************************
//
//! \brief Start the PWM of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//!
//! This function is to start the PWM of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~3
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_CNTEN) |= (1 << (ulChannelTemp));
}

//*****************************************************************************
//
//! \brief Stop the PWM of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//!
//! This function is to stop the PWM of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3.
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_CNTEN) &= ~(1 << (ulChannelTemp));
}

//*****************************************************************************
//
//! \brief Enable the PWM interrupt of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//!
//! This function is to enable the PWM interrupt of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3
//!
//! The \e ulIntType parameter can be values: \b PWM_INT_CAP_BOTH,
//! \b PWM_INT_CAP_FALL, \b PWM_INT_CAP_RISE and \b PWM_INT_PWM.
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));
//    xASSERT((ulIntType == PWM_INT_CAP_BOTH) || (ulIntType == PWM_INT_CAP_FALL) ||
//            (ulIntType == PWM_INT_CAP_RISE) || (ulIntType == PWM_INT_PWM));

    if (ulIntType & PWM_INT_PWM)
    {
        xHWREG(ulBase + PWM_INTEN) |= (1 << ulChannelTemp);
        if(ulIntType & BIT_32_16)
        {
        	xHWREG(ulBase + PWM_INTCTL) |= (1 << (ulChannelTemp));
        }
        else
        {
        	xHWREG(ulBase + PWM_INTCTL) &= ~(1 << (ulChannelTemp));
		}
    }
    if(ulIntType & PWM_INT_DUTY)
    {
    	xHWREG(ulBase + PWM_INTEN) |= (0x100 << ulChannelTemp);
    }
    if(ulIntType & PWM_INT_CAP_BOTH)
    {
//    	xHWREG(ulBase + PWM_PBCR) |= PWM_PBCR_BC;
    	xHWREG(ulBase + PWM_INTEN) |= (0x01010000 << ulChannelTemp);;
    }
}

//*****************************************************************************
//
//! \brief Disable the PWM interrupt of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//!
//! This function is to disable the PWM interrupt of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~3
//!
//! The \e ulIntType parameter can be values: \b PWM_INT_CAP_BOTH,
//! \b PWM_INT_CAP_FALL, \b PWM_INT_CAP_RISE and \b PWM_INT_PWM.
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

//    xASSERT((ulIntType == PWM_INT_CAP_BOTH) || (ulIntType == PWM_INT_CAP_FALL) ||
//            (ulIntType == PWM_INT_CAP_RISE) || (ulIntType == PWM_INT_PWM));

    if (ulIntType == PWM_INT_PWM)
    {
        xHWREG(ulBase + PWM_INTEN) &= ~(1 << ulChannelTemp);
    }
    if(ulIntType & PWM_INT_DUTY)
    {
    	xHWREG(ulBase + PWM_INTEN) &= ~(0x100 << ulChannelTemp);
    }
    if(ulIntType & PWM_INT_CAP_BOTH)
    {
    	xHWREG(ulBase + PWM_INTEN) &= ~(0x01010000 << ulChannelTemp);
    }
}

//*****************************************************************************
//
//! \brief Get the PWM interrupt flag of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//!
//! This function is to get the PWM interrupt flag of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~3
//!
//! The \e ulIntType parameter can be values:\b PWM_INT_CAP_BOTH,
//!  \b PWM_INT_CAP_FALL, \b PWM_INT_CAP_RISE and \b PWM_INT_PWM.
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

//    xASSERT((ulIntType == PWM_INT_CAP_BOTH) || (ulIntType == PWM_INT_CAP_FALL) ||
//            (ulIntType == PWM_INT_CAP_RISE) || (ulIntType == PWM_INT_PWM));

    if (ulIntType == PWM_INT_PWM)
    {
        return ((xHWREG(ulBase + PWM_INTSTS) & (1 << ulChannelTemp))
                ? xtrue : xfalse);
    }
    else if (ulIntType == PWM_INT_DUTY)
    {
        return ((xHWREG(ulBase + PWM_INTSTS) & (0x100 << ulChannelTemp))
                ? xtrue : xfalse);
    }
    else
    {
        return ((xHWREG(ulBase + PWM_INTSTS) & (0x01010000 << ulChannelTemp))
                ? xtrue : xfalse);
    }
}

//*****************************************************************************
//
//! \brief Clear the PWM interrupt flag of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//!
//! This function is to Clear the PWM interrupt flag of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~3
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

//    xASSERT((ulIntType == PWM_INT_CAP_BOTH) || (ulIntType == PWM_INT_CAP_FALL) ||
//            (ulIntType == PWM_INT_CAP_RISE) || (ulIntType == PWM_INT_PWM));

    if (ulIntType & PWM_INT_PWM)
    {
        xHWREG(ulBase + PWM_INTSTS) |= (1 << ulChannelTemp);
    }
    if (ulIntType & PWM_INT_DUTY)
    {
        xHWREG(ulBase + PWM_INTSTS) |= (0x100 << ulChannelTemp);
    }
    if (ulIntType & PWM_INT_CAP_BOTH)
    {
    	xHWREG(ulBase + PWM_INTSTS) |= (0x01010000 << ulChannelTemp);
    }
}

//*****************************************************************************
//
//! \brief Init interrupt callback for the PWM timer.
//!
//! \param ulBase is the base address of the PWM.
//! \param xtPortCallback is callback for the PWM timer.
//!
//! This function is to init interrupt callback for the PWM timer.
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
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));

    if (xtPWMCallback != 0)
    {
    	if(ulBase == PWMA_BASE)
    	{
            g_pfnPWMHandlerCallbacks[0] = xtPWMCallback;
    	}
    	else {
    		g_pfnPWMHandlerCallbacks[1] = xtPWMCallback;
		}

    }
}

//*****************************************************************************
//
//! \brief Enable the Capture of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//!
//! This function is to Enable the Capture of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~3
//!
//! \return None.
//
//*****************************************************************************
void
PWMCAPEnable(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_CAPCTL) |=(1 << ulChannelTemp);
}

//*****************************************************************************
//
//! \brief Disable the Capture of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//!
//! This function is to disable the Capture of the PWM module.
//!
//! The \e ulChannel parameter can be values: 0~3
//!
//! \return None.
//
//*****************************************************************************
void
PWMCAPDisable(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_CAPCTL) &= ~(1 << ulChannelTemp);
}

//*****************************************************************************
//
//! \brief Enable the Capture input of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//!
//! This function is to enable the Capture input of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3
//!
//! \return None.
//
//*****************************************************************************
void
PWMCAPInputEnable(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_CAPINEN) |= (1 << (ulChannelTemp));
}

//*****************************************************************************
//
//! \brief Disable the Capture input of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//!
//! This function is to disable the Capture input of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3
//!
//! \return None.
//
//*****************************************************************************
void
PWMCAPInputDisable(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_CAPINEN) &= ~(1 << (ulChannelTemp));
}

//*****************************************************************************
//
//! \brief Get the Rising Latched PWM counter of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//!
//! This function is to Get the Rising Latched PWM counter of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3
//!
//! \return PWM counter when Channel \b ulChannel has rising transition.
//
//*****************************************************************************
unsigned long
PWMCAPRisingCounterGet(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    return xHWREG(ulBase + PWM_RCAPDAT0 + ulChannelTemp * 8);
}

//*****************************************************************************
//
//! \brief Get the Falling Latched PWM counter of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//!
//! This function is to Get the Falling Latched PWM counter of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3
//!
//! \return PWM counter when Channel \b ulChannel has Falling transition.
//
//*****************************************************************************
unsigned long
PWMCAPFallingCounterGet(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    return xHWREG(ulBase + PWM_FCAPDAT0 + ulChannelTemp * 8);
}

//*****************************************************************************
//
//! \brief Get the Falling Latched PWM counter of the PWM module.
//!
//! \param ulBase is the base address of the PWM.
//! \param ulChannel is the PWM channel.
//!
//! This function is to Get the Falling Latched PWM counter of the PWM module.
//!
//! The \e ulChannel parameter can be values:0~3
//!
//! \return PWM counter when Channel \b ulChannel has Falling transition.
//
//*****************************************************************************
void
PWMCAPLatchFlagClear(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_CAPSTS) |= (0x101 << ulChannelTemp);
}

void
PWMTriggerEnable(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_TRGADCTL) |= (0x01010101 << ulChannelTemp);
}

void
PWMTriggerDisable(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_TRGADCTL) &= ~(0x01010101 << ulChannelTemp);
}

void
PWMTriggerFlagClear(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    xHWREG(ulBase + PWM_TRGADCSTS) |= (0x01010101 << ulChannelTemp);
}

xtBoolean
PWMTriggerFlagGet(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    return ((xHWREG(ulBase + PWM_TRGADCSTS) &
    		((0x01010101 << ulChannelTemp))) ? xtrue : xfalse);
}

xtBoolean
PWMBusyStatusGet(unsigned long ulBase, unsigned long ulChannel)
{
    unsigned long ulChannelTemp;

    ulChannelTemp = ulChannel;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));

    return ((xHWREG(ulBase + PWM_SBS0 + (ulChannelTemp << 2)) &
    		(PWM_SYNCBUSY0_BUSY)) ? xtrue : xfalse);
}

void
PWMPWMIntTypeSel(unsigned long ulBase, unsigned long ulChannel,
		         unsigned long ulIntType)
{
//    unsigned long ulChannelTemp;
//
//    ulChannelTemp = ulChannel;

    //
    // Check the arguments.
    //
    xASSERT((ulBase == PWMA_BASE) || (ulBase == PWMB_BASE));
    xASSERT(((ulChannelTemp >= 0) || (ulChannelTemp <= 5)));


    xHWREG(ulBase + PWM_INTCTL) |= (ulIntType << (ulChannel));
}


//*****************************************************************************
//
//! \brief Initialize and configure the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulConfig is the configuration of PWM channel.
//! Details please refer to \ref xPWM_Config.
//!
//! This function is to initialize and configure channel of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulConfig parameter is the logical OR of four values: The PWM mode.
//! \b xPWM_ONE_SHOT_MODE,\b xPWM_TOGGLE_MODE is the mode selecet.
//!
//! \note When Dead-Zone Generator is enabled, the pair of PWM0 and PWM1
//! becomes a complementary pair for PWM group A and the pair of PWM4 and
//! PWM5 becomes a complementary pair for PWM group B.
//!
//! \return None.
//
//*****************************************************************************
void xPWMInitConfigure(unsigned long ulBase, unsigned long ulChannel,
                        unsigned long ulConfig)
{
	PWMInitConfigure(ulBase, ulChannel, ulConfig);
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
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulFrequency parameter can be values: Any values ,ulFrequency > 0 &&
//! ulFrequency < PWM module input clock.
//!
//! \note
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
unsigned long xPWMFrequencySet(unsigned long ulBase, unsigned long ulChannel,
                               unsigned long ulFrequency)
{
	return PWMFrequencySet(ulBase, ulChannel, ulFrequency);
}

//*****************************************************************************
//
//! \brief Set the PWM frequency of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulConfig is the configuration of PWM channel' frequency.
//! Details please refer to \ref xPWM_Freq_Config.
//!
//! This function is to set the PWM frequency of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulConfig parameter is the logical OR of three values: The PreScale
//! value, The Divider value and the PWM Counter Register value.
//! Details please refer to \ref xPWM_Freq_Config_CoX.
//!
//! \note Config will not the same since diff manu,but for HT32F175x_275x is the above
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
unsigned long xPWMFrequencyConfig(unsigned long ulBase, unsigned long ulChannel,
                                  unsigned long ulConfig)
{
	return PWMFrequencyConfig(ulBase, ulChannel, ulConfig);
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
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
//!
//! \return the Actual Frequency of PWM.
//
//*****************************************************************************
unsigned long xPWMFrequencyGet(unsigned long ulBase, unsigned long ulChannel)
{
	return PWMFrequencyGet(ulBase, ulChannel);
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
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void xPWMOutputEnable(unsigned long ulBase, unsigned long ulChannel)
{
	PWMOutputEnable(ulBase, ulChannel);
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
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void xPWMOutputDisable(unsigned long ulBase, unsigned long ulChannel)
{
	PWMOutputDisable(ulBase, ulChannel);
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
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void xPWMStart(unsigned long ulBase, unsigned long ulChannel)
{
	PWMStart(ulBase, ulChannel);
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
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void xPWMStop(unsigned long ulBase, unsigned long ulChannel)
{
	PWMStop(ulBase, ulChannel);
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
void xPWMDutySet(unsigned long ulBase, unsigned long ulChannel, unsigned long ulDuty)
{
	PWMDutySet(ulBase, ulChannel, ulDuty);
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
unsigned long xPWMDutyGet(unsigned long ulBase, unsigned long ulChannel)
{
	return PWMDutyGet(ulBase, ulChannel);
}

//*****************************************************************************
//
//! \brief Enable the PWM interrupt of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//! Details please refer to \ref xPWM_Int_Type.
//!
//! This function is to enable the PWM interrupt of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulIntType parameter can be values:
//! \b xPWM_INT_PWM.
//! Details please refer to \ref xPWM_Int_Type_CoX.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void xPWMIntEnable(unsigned long ulBase, unsigned long ulChannel, unsigned long ulIntType)
{
	PWMIntEnable(ulBase, ulChannel, ulIntType);
}

//*****************************************************************************
//
//! \brief Disable the PWM interrupt of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//! Details please refer to \ref xPWM_Int_Type.
//!
//! This function is to disable the PWM interrupt of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulIntType parameter can be values:
//! \b xPWM_INT_PWM.
//! Details please refer to \ref xPWM_Int_Type_CoX.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void xPWMIntDisable(unsigned long ulBase, unsigned long ulChannel, unsigned long ulIntType)
{
	PWMIntDisable(ulBase, ulChannel, ulIntType);
}

//*****************************************************************************
//
//! \brief Get the PWM interrupt flag of the PWM module.
//!
//! \param ulBase is the base address of the PWM port.
//! \param ulChannel is the PWM channel.
//! \param ulIntType is the PWM channel interrupt type.
//! Details please refer to \ref xPWM_Int_Type.
//!
//! This function is to get the PWM interrupt flag of the PWM module.
//!
//! The \e ulChannel parameter can be values:
//! 0~7,when the \e ulBase is PWMA_BASE,the \e ulChannel parameter can be value
//! 0~3,when the \e ulBase is PWMB_BASE,the \e ulChannel parameter can be value
//! 4~7.
//!
//! The \e ulIntType parameter can be values:
//! \b xPWM_INT_PWM.
//! Details please refer to \ref xPWM_Int_Type_CoX
//!
//! \note None
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
xtBoolean xPWMIntFlagGet(unsigned long ulBase, unsigned long ulChannel, unsigned long ulIntType)
{
	return PWMIntFlagGet(ulBase, ulChannel, ulIntType);
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
void xPWMIntCallbackInit(unsigned long ulBase, xtEventCallback xtPWMCallback)
{
	PWMIntCallbackInit(ulBase, xtPWMCallback);
}
