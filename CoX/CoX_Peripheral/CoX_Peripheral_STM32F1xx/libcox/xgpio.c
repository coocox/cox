//*****************************************************************************
//
//! \file xgpio.c
//! \brief Driver for the GPIO AFIO and EXTI controller
//! \version V2.2.1.0
//! \date 12/16/2011
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
#include "xhw_gpio.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xcore.h"
#include "xgpio.h"


typedef struct
{
    //
    // Pin ID.
    //
    unsigned long ulpinID;

    //
    //
    //
    xtEventCallback pfnGPIOPinHandlerCallback;
}
tGPIOPinIntAsssign;

//
// GPIO Pins Interrupt Assignment table.
//
static tGPIOPinIntAsssign g_psGPIOPinIntAssignTable[xGPIO_INT_NUMBER] =
{
    {0,0}
};

//*****************************************************************************
//
// An array that maps the "GPIO set" number (which is stored in the upper
// nibble of the GPIO_*_* defines) to the AFIO_MAPR? register that
// controls the GPIO function for that GPIO.
//
//*****************************************************************************
static const unsigned long g_pulRemapRegs[] =
{
    AFIO_MAPR,
    AFIO_MAPR2
};

//*****************************************************************************
//
//! \internal
//! Checks a GPIO base address.
//!
//! \param ulPort is the base address of the GPIO port.
//!
//! This function determines if a GPIO port base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef xDEBUG
static xtBoolean
GPIOBaseValid(unsigned long ulPort)
{
    return((ulPort == GPIOA_BASE) ||
           (ulPort == GPIOB_BASE) ||
           (ulPort == GPIOC_BASE) ||
           (ulPort == GPIOD_BASE) ||
           (ulPort == GPIOE_BASE) ||
           (ulPort == GPIOF_BASE) ||
           (ulPort == GPIOG_BASE) );
}
#endif

//*****************************************************************************
//
//! \internal
//! \brief External interrupt/event line 0 ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EXTI0IntHandler(void)
{
    unsigned long i, ulTemp;

    //
    // Clear the interrupt flag.
    //
    ulTemp = xHWREG(EXTI_PR);
	xHWREG(EXTI_PR) |= (0x00000001 << 0);

    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xffff) == GPIO_PIN_0)
        {
            if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
            {
                g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback(0,ulTemp,0,0);
            }
        }
    }
}

//*****************************************************************************
//
//! \internal
//! \brief External interrupt/event line 1 ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EXTI1IntHandler(void)
{
    unsigned long i, ulTemp;

    // Clear the interrupt flag.
    //
    ulTemp = xHWREG(EXTI_PR);
	xHWREG(EXTI_PR) |= (0x00000001 << 1);
    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xffff) == GPIO_PIN_1)
        {
            if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
            {
                g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback(0,ulTemp,0,0);
            }
        }
    }
}

//*****************************************************************************
//
//! \internal
//! \brief External interrupt/event line 2 ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EXTI2IntHandler(void)
{
    unsigned long i, ulTemp;

	//
    // Clear the interrupt flag.
    //
    ulTemp = xHWREG(EXTI_PR);
	xHWREG(EXTI_PR) |= (0x00000001 << 2);

    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xffff) == GPIO_PIN_2)
        {
            if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
            {
                g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback(0,ulTemp,0,0);
            }
        }
    }
}

//*****************************************************************************
//
//! \internal
//! \brief External interrupt/event line 3 ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EXTI3IntHandler(void)
{
    unsigned long i, ulTemp;

	//
    // Clear the interrupt flag.
    //
    ulTemp = xHWREG(EXTI_PR);
	xHWREG(EXTI_PR) |= (0x00000001 << 3);

    //
    // Clear the interrupt flag.
    //

    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xffff) == GPIO_PIN_3)
        {
            if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
            {
                g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback(0,ulTemp,0,0);
            }
        }
    }
}

//*****************************************************************************
//
//! \internal
//! \brief External interrupt/event line 4 ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EXTI4IntHandler(void)
{
    unsigned long i, ulTemp;

	//
    // Clear the interrupt flag.
    //
    ulTemp = xHWREG(EXTI_PR);
	xHWREG(EXTI_PR) |= (0x00000001 << 4);

    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xffff) == GPIO_PIN_4)
        {
            if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
            {
                g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback(0,ulTemp,0,0);
            }
        }
    }
}

//*****************************************************************************
//
//! \internal
//! \brief External interrupt/event line 9-5 ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EXTI95IntHandler(void)
{
    unsigned long i, ulTemp, ulShift;

	//
    // Clear the interrupt flag.
    //
    ulTemp = xHWREG(EXTI_PR);
    if((ulTemp & (0x00000001 << 5)) != 0)
	{
	    ulShift = 5;
	}
	else if((ulTemp & (0x00000001 << 6)) != 0)
	{
	    ulShift = 6;
	}
	else if((ulTemp & (0x00000001 << 7)) != 0)
	{
	    ulShift = 7;
	}
	else if((ulTemp & (0x00000001 << 8)) != 0)
	{
	    ulShift = 8;
	}
	else
	{
	    ulShift = 9;
	}


	xHWREG(EXTI_PR) |= (0x00000001 << ulShift);


    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xffff) == (GPIO_PIN_0 << ulShift))
        {
            if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
            {
                g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback(0,0,0,0);
            }
        }
    }

}

//*****************************************************************************
//
//! \internal
//! \brief External interrupt/event line 15-10 ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EXTI1510IntHandler(void)
{
    unsigned long i, ulTemp, ulShift;

	//
    // Clear the interrupt flag.
    //
    ulTemp = xHWREG(EXTI_PR);
    if((ulTemp & (0x00000001 << 10)) != 0)
	{
	    ulShift = 10;
	}
	else if((ulTemp & (0x00000001 << 11)) != 0)
	{
	    ulShift = 11;
	}
	else if((ulTemp & (0x00000001 << 12)) != 0)
	{
	    ulShift = 12;
	}
	else if((ulTemp & (0x00000001 << 13)) != 0)
	{
	    ulShift = 13;
	}
	else if((ulTemp & (0x00000001 << 14)) != 0)
	{
	    ulShift = 14;
	}
	else
	{
	    ulShift = 15;
	}

	xHWREG(EXTI_PR) |= (0x00000001 << ulShift);


    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xffff) == (GPIO_PIN_0 << ulShift))
        {
            if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
            {
                g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback(0,ulTemp,0,0);
            }
        }
    }
}

//*****************************************************************************
//
//! \brief Sets the direction and pad configuration of the specified pin.
//!
//! \param ulPort is the base address of the GPIO port
//! \param ulBit is the bit number of a port.
//! \param ulPinType is the pin direction and/or pad configuration.
//! \param ulPinSpeed is input or output speed of specified pin.
//!
//! This function will set the specified pin(Only 1 pin) on the selected GPIO
//! port as either an input or output under software control, or it will set
//! the pin to be under hardware control.
//!
//! The parameter \e ulPinType is an enumerated data type that can be one of
//! the following values:
//!
//! - \b GPIO_TYPE_IN_ANALOG
//! - \b GPIO_TYPE_IN_FLOATING
//! - \b GPIO_TYPE_IN_WPU_WPD
//! - \b GPIO_TYPE_OUT_STD
//! - \b GPIO_TYPE_OUT_OD
//! - \b GPIO_TYPE_AFOUT_STD
//! - \b GPIO_TYPE_AFOUT_OD
//!
//! The parameter \e ulPinSpeed is an enumerated data type that can be one of
//! the following values:
//!
//! - \b GPIO_IN_SPEED_FIXED
//! - \b GPIO_OUT_SPEED_10M
//! - \b GPIO_OUT_SPEED_2M
//! - \b GPIO_OUT_SPEED_50M
//!
//!
//! \return None.
//
//*****************************************************************************
void
GPIODirModeSet(unsigned long ulPort, unsigned long ulBit,
               unsigned long ulPinType, unsigned long ulPinSpeed)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    xASSERT(ulBit < 16);
    xASSERT((ulPinType == GPIO_TYPE_IN_ANALOG) ||
            (ulPinType == GPIO_TYPE_IN_FLOATING) ||
            (ulPinType == GPIO_TYPE_IN_WPU_WPD) ||
            (ulPinType == GPIO_TYPE_OUT_STD) ||
            (ulPinType == GPIO_TYPE_OUT_OD) ||
            (ulPinType == GPIO_TYPE_AFOUT_STD) ||
            (ulPinType == GPIO_TYPE_AFOUT_OD));

    xASSERT((ulPinSpeed == GPIO_IN_SPEED_FIXED) ||
            (ulPinSpeed == GPIO_OUT_SPEED_10M) ||
            (ulPinSpeed == GPIO_OUT_SPEED_2M) ||
            (ulPinSpeed == GPIO_OUT_SPEED_50M));
    //
    // Set the pin direction and mode.
    //
    if(ulBit < 8)
    {
        xHWREG(ulPort + GPIO_CRL) &=
        (~((GPIO_CRL_MODE0_M | GPIO_CRL_CNF0_M) << (ulBit * 4)));

        xHWREG(ulPort + GPIO_CRL) = (xHWREG(ulPort + GPIO_CRL) |               \
        (((ulPinSpeed | ulPinType)) << (ulBit * 4)));
    }
    else
    {
        xHWREG(ulPort + GPIO_CRH) &=
        (~((GPIO_CRH_MODE8_M | GPIO_CRH_CNF8_M) << ((ulBit -8) * 4)));

        xHWREG(ulPort + GPIO_CRH) = (xHWREG(ulPort + GPIO_CRH) |               \
        (((ulPinSpeed | ulPinType)) << ((ulBit -8) * 4)));
    }
}

//*****************************************************************************
//
//! \brief Sets the direction and mode of the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port
//! \param ulPins is the bit-packed representation of the pin(s).
//! \param ulPinIO is the pin direction and/or mode.
//!
//! This function will set the specified pin(s) on the selected GPIO port
//! as either an input or output under software control, or it will set the
//! pin to be under hardware control.
//!
//! The parameter \e ulPinIO is an enumerated data type that can be one of
//! the following values:
//!
//! - \b xGPIO_DIR_MODE_IN
//! - \b xGPIO_DIR_MODE_OUT
//! - \b xGPIO_DIR_MODE_OD
//! - \b xGPIO_DIR_MODE_HW
//!
//! where \b GPIO_DIR_MODE_IN specifies that the pin will be programmed as
//! a software controlled input, \b GPIO_DIR_MODE_OUT specifies that the pin
//! will be programmed as a software controlled output, and
//! \b GPIO_DIR_MODE_HW specifies that the pin will be placed under
//! hardware control.\b GPIO_DIR_MODE_OD specifies that the pin will be
//! programmed as a Open-Drain.\b GPIO_DIR_MODE_QB specifies that the pin
//! will be programmed as Quasi-bidirectional
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void
xGPIODirModeSet(unsigned long ulPort, unsigned long ulPins,
               unsigned long ulPinIO)
{
    unsigned long ulBit;

    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    xASSERT((ulPinIO == xGPIO_DIR_MODE_IN) || (ulPinIO == xGPIO_DIR_MODE_OUT) ||
            (ulPinIO == xGPIO_DIR_MODE_OD));

    //
    // Set the pin direction and mode.
    //
    for(ulBit=0; ulBit<16; ulBit++)
    {
        if(ulPins & (1 << ulBit))
        {
            GPIODirModeSet(ulPort, ulBit, ulPinIO & 0xC, ulPinIO & 0x3);
        }

    }
}

//*****************************************************************************
//
//! Gets the direction and mode of a pin.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulBit is the pin number.
//!
//! This function gets the direction and control mode for a specified pin on
//! the selected GPIO port.  The pin can be configured as either an input or
//! output under software control, or it can be under hardware control.  The
//! type of control and direction are returned as an enumerated data type.
//!
//! \return Returns one of the enumerated data types described for
//! GPIODirModeSet().
//
//*****************************************************************************
unsigned long
GPIODirModeGet(unsigned long ulPort, unsigned long ulBit)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    xASSERT(ulBit < 16);

    //
    // Return the pin direction and mode.
    //
    if(ulBit < 8)
    {
        return((xHWREG(ulPort + GPIO_CRL) &
               (0xF << (ulBit * 4))) >> (ulBit * 4));
    }
    else
    {
        return((xHWREG(ulPort + GPIO_CRH) &
               (0xF << ((ulBit - 8) * 4))) >> ((ulBit - 8) * 4));
    }
}

//*****************************************************************************
//
//! \brief Gets the direction and mode of a pin.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPin is the bit-packed representation of the pin.
//!
//! This function gets the direction and control mode for a specified pin on
//! the selected GPIO port.  The pin can be configured as either an input or
//! output under software control, or it can be under hardware control.  The
//! type of control and direction are returned as an enumerated data type.
//!
//! \return Returns one of the enumerated data types described for
//! GPIODirModeSet().
//
//*****************************************************************************
unsigned long
xGPIODirModeGet(unsigned long ulPort, unsigned long ulPin)
{
    unsigned long ulBits;
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    for(ulBits=0; ulBits<16; ulBits++)
    {
        if(ulPin & (1 << ulBits))
        {
            break;
        }
    }

    //
    // Return the pin direction and mode.
    //
    return GPIODirModeGet(ulPort, ulBits);
}

//*****************************************************************************
//
//! \brief Sets the interrupt type and Enables interrupts for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//! \param ulIntType specifies the type of interrupt trigger mechanism.
//!
//! This function sets up the various interrupt trigger mechanisms for the
//! specified pin(only one pin) on the selected GPIO port.
//!
//! The parameter \e ulIntType is an enumerated data type that can be one of
//! the following values:
//!
//! - \b GPIO_FALLING_EDGE
//! - \b GPIO_RISING_EDGE
//! - \b GPIO_BOTH_EDGES
//!
//! where the different values describe the interrupt detection mechanism
//! (edge or level) and the particular triggering event (falling, rising,
//! or both edges for edge detect, low or high for level detect).
//!
//! \note In order to avoid any spurious interrupts, the user must
//! ensure that the GPIO inputs remain stable for the duration of
//! this function.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinIntEnable(unsigned long ulPort, unsigned long ulPins,
                 unsigned long ulIntType)
{
    unsigned long ulBit;
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    xASSERT((ulIntType == GPIO_FALLING_EDGE) ||
            (ulIntType == GPIO_RISING_EDGE) ||
            (ulIntType == GPIO_BOTH_EDGES));

    for(ulBit = 0; ulBit < 16; ulBit++)
    {
        if(((ulPins >> ulBit) & 1) != 0)
        {
            //
            // Set the pin interrupt type.
            //
            xHWREG(AFIO_EXTICR1 + (ulBit>>2)*4) &=
                                 ~(AFIO_EXTICR1_EXTI0_M << (ulBit%4)*4);
            xHWREG(AFIO_EXTICR1 + (ulBit>>2)*4) |=
                                 ((((ulPort&0xFFFF) >> 10) -2) << (ulBit%4)*4);

            xHWREG(EXTI_RTSR) = ((ulIntType & 2) ?
                                 (xHWREG(EXTI_RTSR) | (1 << ulBit)) :
                                 (xHWREG(EXTI_RTSR) & ~(1 << ulBit)));
            xHWREG(EXTI_FTSR) = ((ulIntType & 1) ?
                                 (xHWREG(EXTI_FTSR) | (1 << ulBit)) :
                                 (xHWREG(EXTI_FTSR) & ~(1 << ulBit)));
            xHWREG(EXTI_IMR) |= (1 << ulBit);
        }
    }
}

//*****************************************************************************
//
//! \brief Disables interrupts for the specified pin.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//!
//! Masks the interrupt for the specified pin.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinIntDisable(unsigned long ulPort, unsigned long ulPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Disable the interrupts.
    //
    xHWREG(EXTI_IMR) &= ~ulPins;
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the specified Port.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPin is the bit-packed representation of the pin.
//! \param xtPortCallback is callback for the specified Port.
//!
//! Init interrupts callback for the specified Port.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinIntCallbackInit(unsigned long ulPort, unsigned long ulPin,
                       xtEventCallback xtPortCallback)
{
    int i;
    unsigned long ulPinID;
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // changed ?? (ulPort  << 16) | i ?? to ?? (ulPort  << 16) | ulPin ?? by
    // niuyj 09/09/2011
    //
    ulPinID = (ulPort  << 16) | ulPin;

    //
    // Init the interrupts callback.
    //
    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if(g_psGPIOPinIntAssignTable[i].ulpinID == ulPinID)
        {
            g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback =
                                         xtPortCallback;
            break;
        }
        if (g_psGPIOPinIntAssignTable[i].ulpinID == 0)
        {
            g_psGPIOPinIntAssignTable[i].ulpinID = ulPinID;
            g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback =
                                         xtPortCallback;
            break;
        }
    }
}

//*****************************************************************************
//
//! \brief Gets interrupt status for the specified GPIO port.
//!
//! \return Returns a bit-packed byte, where each bit that is set identifies
//! an active masked or raw interrupt, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//! Bits 31:20 should be ignored.
//
//*****************************************************************************
unsigned long
GPIOPinIntStatus(void)
{
    //
    // Return the interrupt status.
    //
    return(xHWREG(EXTI_PR));

}

//*****************************************************************************
//
//! \brief Clears the interrupt for the specified pin(s).
//!
//! \param ulPins is the bit-packed representation of the pin(s).
//!
//! Clears the interrupt for the specified pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinIntClear(unsigned long ulPort, unsigned long ulPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Clear the interrupts.
    //
    xHWREG(EXTI_PR) |= ulPins;
}

//*****************************************************************************
//
//! \brief Reads the values present of the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//!
//! The values at the specified pin(s) are read, as specified by \e ucPins.
//! Values are returned for both input and output pin(s), and the value
//! for pin(s) that are not specified by \e ucPins are set to 0.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return Returns a bit-packed byte providing the state of the specified
//! pin, where bit 0 of the byte represents GPIO port pin 0, bit 1 represents
//! GPIO port pin 1, and so on.  Any bit that is not specified by \e ucPins
//! is returned as a 0.  Bits 31:16 should be ignored.
//
//*****************************************************************************
long
GPIOPinRead(unsigned long ulPort, unsigned long ulPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Return the pin value(s).
    //
    return(xHWREG(ulPort +GPIO_IDR ) & (ulPins));
}

//*****************************************************************************
//
//! \brief Reads the values present of the specified Port.
//!
//! \param ulPort is the base address of the GPIO port.
//!
//! The values at the specified Port are read
//!
//! \return Returns a bit-packed byte providing the state of the specified
//! Port
//
//*****************************************************************************
long
GPIOPortRead(unsigned long ulPort)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Return the pin value(s).
    //
    return(xHWREG(ulPort +GPIO_IDR ));
}

//*****************************************************************************
//
//! \brief Writes a value to the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//! \param ucVal is the value to write to the pin(s).
//!
//! Writes the corresponding bit values to the output pin(s) specified by
//! \e ucPins.  Writing to a pin configured as an input pin has no effect.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinWrite(unsigned long ulPort, unsigned long ulPins, unsigned char ucVal)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Write the pins.
    //
    xHWREG(ulPort + GPIO_ODR) = ((ucVal & 1) ?
                                (xHWREG(ulPort + GPIO_ODR) | ulPins) :
                                (xHWREG(ulPort + GPIO_ODR) & ~(ulPins)));
}

//*****************************************************************************
//
//! \brief Writes a value to the specified Port.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucVal is the value to write to the Port.
//!
//! Writes the corresponding bit values to the output Port
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPortWrite(unsigned long ulPort, unsigned long ulVal)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Write the pins.
    //
    xHWREG(ulPort + GPIO_ODR) = ulVal;
}

//*****************************************************************************
//
//! \brief Set a value 1 to the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//!
//! Writes the corresponding bit value 1 to the output pin(s) specified by
//! \e ucPins.  Writing to a pin configured as an input pin has no effect.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinSet(unsigned long ulPort, unsigned long ulPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Write the pins.
    //
    xHWREG(ulPort + GPIO_BSRR) = ulPins;
}

//*****************************************************************************
//
//! \brief Set a value 0 to the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//!
//! Writes the corresponding bit value 0 to the output pin(s) specified by
//! \e ucPins.  Writing to a pin configured as an input pin has no effect.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinReset(unsigned long ulPort, unsigned long ulPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Write the pins.
    //
    xHWREG(ulPort + GPIO_BRR) = ulPins;
}

//*****************************************************************************
//
//! \brief Set GPIO port mask register of the specified GPIO pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//!
//! Set GPIO port mask register of the specified GPIO pin(s) specified by
//! \e ucPins.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinLockConfig(unsigned long ulPort, unsigned long ulPins)
{
    unsigned long ulTemp = GPIO_LCKR_KEY;
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Reset the LCKR
    //
  	xHWREG(ulPort + GPIO_LCKR) &= ulTemp;

	  //
	  // Write the data
	  //
	  xHWREG(ulPort + GPIO_LCKR) = ulPins;

	  //
	  // Write the LCKR
	  //
    xHWREG(ulPort + GPIO_LCKR) = (ulPins | ulTemp);

    //
    // Reset LCKK bit.
    //
	  xHWREG(ulPort + GPIO_LCKR) = ulPins;

    //
    // Set LCKK bit.
    //
    xHWREG(ulPort + GPIO_LCKR) = (ulPins | ulTemp);;

    //
    // Read LCKK bit.
    //
    ulTemp = xHWREG(ulPort + GPIO_LCKR);
    ulTemp = xHWREG(ulPort + GPIO_LCKR);

}

//*****************************************************************************
//
//! \brief Configures the alternate function of a GPIO pin.
//!
//! \param ulPinConfig is the pin configuration value, specified as only one of
//! the \b GPIO_P??_??? values.
//!
//! This function configures the pin mux that selects the peripheral function
//! associated with a particular GPIO pin.  Only one peripheral function at a
//! time can be associated with a GPIO pin, and each peripheral function should
//! only be associated with a single GPIO pin at a time (despite the fact that
//! many of them can be associated with more than one GPIO pin).
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinConfigure(unsigned long ulPort, unsigned long ulPins,
                 unsigned long ulPinConfig)
{
    unsigned long ulBase, ulShift, ulInout;
    int i;
    //
    // Check the argument.
    //
    xASSERT(((ulPinConfig >> 28) & 0x1) <= 2 );

    //
    // Extract the base address index from the input value.
    //

    ulBase = g_pulRemapRegs[(ulPinConfig >> 28) & 0x1];


    //
    // Extract the shift from the input value.
    //
    ulShift = (ulPinConfig ) & 0x0FFFFFFF;

    ulInout = (ulPinConfig >> 29) & 0x07;


    for(i=0; i<16; i++)
    {
        if((ulPins >> i) == 1)
                break;
    }

    if(ulInout == 0)
    {
        GPIODirModeSet(ulPort, i, GPIO_TYPE_IN_ANALOG, GPIO_IN_SPEED_FIXED);
    }
    else if(ulInout == 1)
    {
        GPIODirModeSet(ulPort, i, GPIO_TYPE_IN_FLOATING, GPIO_IN_SPEED_FIXED);
    }
    else if(ulInout == 3)
    {
        GPIODirModeSet(ulPort, i, GPIO_TYPE_AFOUT_STD, GPIO_OUT_SPEED_50M);
    }
    else if(ulInout == 4)
    {
        GPIODirModeSet(ulPort, i, GPIO_TYPE_AFOUT_OD, GPIO_OUT_SPEED_50M);
    }

    //
    // Write the requested pin muxing value for this GPIO pin.
    //
    xHWREG(ulBase) &= ~(ulShift);
    xHWREG(ulBase) |= (ulShift);
}

//*****************************************************************************
//
//! \brief Get the GPIO Peripheral Id from a short Pin.
//!
//! \param eShortPin is the base address of the GPIO port
//!
//! \note For M051,all GPIO port use the some Peripheral clock.
//!
//! \return GPIO port code which is used by \ref xSysCtlPeripheralEnable,
//! \ref xSysCtlPeripheralDisable, \ref xSysCtlPeripheralReset.
//
//*****************************************************************************
unsigned long
GPIOPinToPeripheralId(unsigned long ulPort, unsigned long ulPin)
{

    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    switch (ulPort)
    {
    case GPIOA_BASE:
        {
            return SYSCTL_PERIPH_IOPA;
            break;
        }
    case GPIOB_BASE:
        {
            return SYSCTL_PERIPH_IOPB;
            break;
        }
    case GPIOC_BASE:
        {
            return SYSCTL_PERIPH_IOPC;
            break;
        }
    case GPIOD_BASE:
        {
            return SYSCTL_PERIPH_IOPD;
            break;
        }
    case GPIOE_BASE:
        {
            return SYSCTL_PERIPH_IOPE;
            break;
        }
    case GPIOF_BASE:
        {
            return SYSCTL_PERIPH_IOPF;
            break;
        }
    }
    return 0;

}
