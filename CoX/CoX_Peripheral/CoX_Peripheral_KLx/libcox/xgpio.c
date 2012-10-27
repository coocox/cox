//*****************************************************************************
//
//! \file xgpio.c
//! \brief Driver for the GPIO AFIO and EXTI controller
//! \version V2.2.1.0
//! \date 7/31/2012
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
    {0,0},
};

//*****************************************************************************
//
// An array that maps Port base.
//
//*****************************************************************************
static const unsigned long g_pulPortBase[] =
{
    PORTA_BASE,
    PORTB_BASE,
    PORTC_BASE,
    PORTD_BASE,
    PORTE_BASE
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
           (ulPort == GPIOE_BASE));
}
#endif

//*****************************************************************************
//
//! \internal
//! \brief GPIO A  ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void PORTAIntHandler(void)
{
    unsigned long ulGpaStatus;
    unsigned long i;
    
    /* Keep the interrupt source */
    ulGpaStatus = xHWREG(PORTA_BASE+PORT_ISFR);

    /* Clear the interrupt */
    xHWREG(PORTA_BASE+PORT_ISFR) |= ulGpaStatus;

    /* Call the callback function of GPIOA interrupt */
    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xFFFF0000) == 
           (unsigned long)((GPIOA_BASE & 0x0000FFFF) << 16))
        {
            if((g_psGPIOPinIntAssignTable[i].ulpinID & 0x0000FFFF & 
                ulGpaStatus))
            {
                if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
                {
                    g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback
                    (0,ulGpaStatus,0,0);
                }
            }
        }
    } 
}

//*****************************************************************************
//
//! \internal
//! \brief GPIO D ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void PORTDIntHandler(void)
{
    unsigned long ulGpdStatus;
    unsigned long i;
    
    /* Keep the interrupt source */
    ulGpdStatus = xHWREG(PORTD_BASE+PORT_ISFR);

    /* Clear the interrupt */
    xHWREG(PORTD_BASE+PORT_ISFR) |= ulGpdStatus;

    /* Call the callback function of GPIOCDE interrupt */
    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xFFFF0000) == 
           (unsigned long)((GPIOD_BASE & 0x0000FFFF) << 16))
        {
            if((g_psGPIOPinIntAssignTable[i].ulpinID & 0x0000FFFF & 
                ulGpdStatus))
            {
                if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
                {
                    g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback
                    (0,ulGpdStatus,0,0);
                }
            }
        }
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
//! - \b xGPIO_DIR_MODE_HW
//!
//! where \b GPIO_DIR_MODE_IN specifies that the pin will be programmed as
//! a software controlled input, \b GPIO_DIR_MODE_OUT specifies that the pin
//! will be programmed as a software controlled output, and
//! \b GPIO_DIR_MODE_HW specifies that the pin will be placed under
//! hardware control.
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
            (ulPinIO == xGPIO_DIR_MODE_HW));

    //
    // Set the pin direction and mode.
    //
    for(ulBit=0; ulBit<32; ulBit++)
    {
        if(ulPins & (1 << ulBit))
        {
            GPIODirModeSet(ulPort, ulBit, ulPinIO);
        }
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

    for(ulBits=0; ulBits<32; ulBits++)
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
//! \brief Gets the GPIO corresponding Port base.
//!
//! \param ulPort is the base address of the GPIO port.
//!
//! \return Returns the GPIO corresponding Port base.
//
//*****************************************************************************
static 
unsigned long GPIOToPortGet(unsigned long ulPort)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    if(ulPort == GPIOA_BASE)
    {
	return PORTA_BASE;
    }
    else if(ulPort == GPIOB_BASE)
    {
        return PORTB_BASE;
    }
    else if(ulPort == GPIOC_BASE)
    {
        return PORTC_BASE;
    }
    else if(ulPort == GPIOD_BASE)
    {
        return PORTD_BASE;
    }
    else if(ulPort == GPIOE_BASE)
    {
        return PORTE_BASE;
    }
    return 0;
}

//*****************************************************************************
//
//! \brief Sets the direction and mode of the specified pin.
//!
//! \param ulPort is the base address of the GPIO port
//! \param ulBit is the bit number of a port.
//! \param ulPinIO is the pin direction and/or mode.
//!
//! This function will set the specified pin(Only 1 pin) on the selected GPIO 
//! port as either an input or output under software control, or it will set 
//! the pin to be under hardware control.
//!
//! The parameter \e ulPinIO is an enumerated data type that can be one of
//! the following values:
//!
//! - \b GPIO_DIR_MODE_IN
//! - \b GPIO_DIR_MODE_OUT
//!
//! where \b GPIO_DIR_MODE_IN specifies that the pin will be programmed as
//! a software controlled input, \b GPIO_DIR_MODE_OUT specifies that the pin
//! will be programmed as a software controlled output.
//!
//! \return None.
//
//*****************************************************************************
void
GPIODirModeSet(unsigned long ulPort, unsigned long ulBit,
               unsigned long ulPinIO)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    xASSERT((ulPinIO == GPIO_DIR_MODE_IN) || (ulPinIO == GPIO_DIR_MODE_OUT));

    //
    // Set the pin direction and mode.
    //
    xHWREG(ulPort + GPIO_PDDR) &= ~(1 << ulBit);
    xHWREG(ulPort + GPIO_PDDR) |= (ulPinIO << ulBit);
	
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
    return ((xHWREG(ulPort + GPIO_PDDR) >> ulBit) & 0x00000001);
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
//! - \b GPIO_LEVEL_LOW
//! - \b GPIO_LEVEL_HIGH
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
    unsigned long ulPortBase;
    
    ulPortBase = GPIOToPortGet(ulPort); 

    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    xASSERT((ulIntType == GPIO_FALLING_EDGE) ||
            (ulIntType == GPIO_RISING_EDGE) || 
            (ulIntType == GPIO_BOTH_EDGES) || 
	    (ulIntType == GPIO_LEVEL_LOW) ||
	    (ulIntType == GPIO_LEVEL_HIGH));
    
    for(ulBit = 0; ulBit < 32; ulBit++)
    {
        if(((ulPins >> ulBit) & 1) != 0)
        { 
	    xHWREG(ulPortBase + PORT_PCR + ulBit * 4) &= ~PORT_PCR_IRQC_M;
            xHWREG(ulPortBase + PORT_PCR + ulBit * 4) |= ulIntType;
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
    unsigned long ulBit;
    unsigned long ulPortBase;
    ulPortBase = GPIOToPortGet(ulPort); 

    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    
    for(ulBit = 0; ulBit < 32; ulBit++)
    {
        if(((ulPins >> ulBit) & 1) != 0)
        { 
	    xHWREG(ulPortBase + PORT_PCR + ulBit * 4) &= ~PORT_PCR_IRQC_M;
        }
    }
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
//! \param ulPort is the base address of the GPIO port.
//!
//! \return Returns a bit-packed byte, where each bit that is set identifies
//! an active masked or raw interrupt, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//
//*****************************************************************************
unsigned long
GPIOPinIntStatus(unsigned long ulPort)
{
    unsigned long ulPortBase;

    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    
    ulPortBase = GPIOToPortGet(ulPort); 
	
    //
    // Return the interrupt status.
    //
    return(xHWREG(ulPortBase + PORT_ISFR));

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
    unsigned long ulPortBase;
 
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    ulPortBase = GPIOToPortGet(ulPort); 

    //
    // Clear the interrupts.
    //
    xHWREG(ulPortBase + PORT_ISFR) |= ulPins; 
}

//*****************************************************************************
//
//! \brief Sets the DMA Edge for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//! \param ulDMAEdge specifies the type of DMA trigger mechanism.
//!
//! The parameter ulDMAEdge can be one of the following values:
//!
//! - \b GPIO_DMA_DIS
//! - \b GPIO_DMA_RISE
//! - \b GPIO_DMA_FALL
//! - \b GPIO_DMA_BOTH
//!
//! \return None.
//
//*****************************************************************************
void 
GPIODMAEdgeSet(unsigned long ulPort, unsigned long ulPins,
                           unsigned long ulDMAEdge)
{
    unsigned long ulPortBase;
    unsigned long ulBit;

    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    
    ulPortBase = GPIOToPortGet(ulPort);

    for(ulBit = 0; ulBit < 32; ulBit++)
    {
        if(((ulPins >> ulBit) & 1) != 0)
        { 
	    xHWREG(ulPortBase + PORT_PCR + ulBit * 4) &= ~PORT_PCR_IRQC_M;
    	    xHWREG(ulPortBase + PORT_PCR + ulBit * 4) |= ulDMAEdge;
        }
    }
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
    return(xHWREG(ulPort + GPIO_PDIR) & (ulPins));
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
    xHWREG(ulPort + GPIO_PDOR) = ((ucVal & 1) ?
                                (xHWREG(ulPort + GPIO_PDOR) | ulPins) :
                                (xHWREG(ulPort + GPIO_PDOR) & ~(ulPins)));
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
    xHWREG(ulPort + GPIO_PSOR) = ulPins;
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
    xHWREG(ulPort + GPIO_PCOR) = ulPins;
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
GPIOPinMaskSet(unsigned long ulPort, unsigned long ulPins)
{
    unsigned long ulPortBase;
    unsigned long ulBit;

    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    
	ulPortBase = GPIOToPortGet(ulPort);

    for(ulBit = 0; ulBit < 32; ulBit++)
    {
        if(((ulPins >> ulBit) & 1) != 0)
        { 
	    if(ulBit < 16)
            {
	        xHWREG(ulPortBase + PORT_GPCLR) |= (1 << (ulBit + 16));
            }
            else
	    {
	        xHWREG(ulPortBase + PORT_GPCHR) |= (1 << (ulBit + 16)); 
	    }
        }
    }
}

//*****************************************************************************
//
//! \brief Get GPIO port mask register of the specified GPIO pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//!
//! \return None.
//
//*****************************************************************************
long 
GPIOPortMaskGet(unsigned long ulPort)
{
    unsigned long ulPortBase;
	unsigned long ulPinMask;

    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    
	ulPortBase = GPIOToPortGet(ulPort);

	ulPinMask = xHWREG(ulPortBase + PORT_GPCHR);
	ulPinMask = ulPinMask << 16;
	ulPinMask |= xHWREG(ulPortBase + PORT_GPCLR);  

    return ulPinMask;
}

//*****************************************************************************
//
//! \brief Get GPIO port Dout register of the specified GPIO.
//!
//! \param ulPort is the base address of the GPIO port.
//!
//! \return The value of the specified GPIO DOUT.
//
//*****************************************************************************
long 
GPIOPinPortDoutGet(unsigned long ulPort)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

	return(xHWREG(ulPort + GPIO_PDOR));
}

//*****************************************************************************
//
//! \brief Selects the driving current of specified GPIO pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//! \param ulStrength is Selection of output driving current.it can be selected
//! one of the following values:
//! 
//! - \ref GPIO_DRIVER_STR_DIS
//! - \ref GPIO_DRIVER_STR_ENA
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void 
GPIOPadConfigSet(unsigned long ulPort, unsigned long ulPins, 
                 unsigned long ulStrength)
{
    unsigned long ulPortBase;
	unsigned long ulBit;

    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    
	ulPortBase = GPIOToPortGet(ulPort);

    for(ulBit = 0; ulBit < 32; ulBit++)
    {
        if(((ulPins >> ulBit) & 1) != 0)
        {
	    //
            // Drive Strength select
            //
            xHWREG(ulPortBase + PORT_PCR + ulBit * 4) &= ~PORT_PCR_DSE_HIGH ;
            xHWREG(ulPortBase + PORT_PCR + ulBit * 4) |= ulStrength ;

        }
    }
}

//*****************************************************************************
//
//! \brief Enable the Port pin Pull. 
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//! \param ulPullType is Selection of pull register.
//! \param ulPullCfg is pull enable configure.
//!
//! The pull ulPullCfg configure is chosen with one of the following values:
//! - \ref GPIO_PULL_ENABLE
//! - \ref GPIO_PULL_DISABLE
//!
//! \param ulPadType is the one of the following values:
//! - \ref GPIO_PULL_DOWN
//! - \ref GPIO_PULL_UP
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note there are some problem in this API,will modify it later.
//!
//! \return None.
//
//*****************************************************************************
void 
GPIOPullConfigure(unsigned long ulPort, unsigned long ulPins, 
                  unsigned long ulPullCfg, unsigned long ulPullType)
{
    unsigned long ulPortBase;
	unsigned long ulBit;

    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    
	ulPortBase = GPIOToPortGet(ulPort);

    for(ulBit = 0; ulBit < 32; ulBit++)
    {
        if(((ulPins >> ulBit) & 1) != 0)
        {

            //
            // Pull enable select
            //
            xHWREG(ulPortBase + PORT_PCR + ulBit * 4) &= ~PORT_PCR_PE_ENABLE ;
            xHWREG(ulPortBase + PORT_PCR + ulBit * 4) |= ulPullCfg ;
            
            //
            // pull resistor configure
            //
	    xHWREG(ulPortBase + PORT_PCR + ulBit * 4) &= ~PORT_PCR_PS_ENABLE ;
            xHWREG(ulPortBase + PORT_PCR + ulBit * 4) |= ulPullType ;
        }
    }
}

//*****************************************************************************
//
//! \brief Configure the pin passive 
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//! \param ulPassiveCfg is Selection of pull register.
//! 
//! \param ulPassiveCfg is the one of the following values:
//! - \ref GPIO_PASSIVE_FILTER_DIS
//! - \ref GPIO_PASSIVE_FILTER_ENA
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note there are some problem in this API,will modify it later.
//!
//! \return None.
//
//*****************************************************************************
void 
GPIOPassiveConfigure(unsigned long ulPort, unsigned long ulPins, 
                                    unsigned long ulPassiveCfg)
{
    unsigned long ulPortBase;
	unsigned long ulBit;

    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    ulPortBase = GPIOToPortGet(ulPort);

    for(ulBit = 0; ulBit < 32; ulBit++)
    {
        if(((ulPins >> ulBit) & 1) != 0)
        {
            //
            // Passive Filter configure
            //
            xHWREG(ulPortBase + PORT_PCR + ulBit * 4) &= ~PORT_PCR_PFE_ENABLE ;
            xHWREG(ulPortBase + PORT_PCR + ulBit * 4) |= ulPassiveCfg ;
        }
    }
}

//*****************************************************************************
//
//! \brief Configure the Slew Rate 
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//! \param ulPassiveCfg is Selection of pull register.
//! 
//! \param ulSlewRateCfg is the one of the following values:
//! - \ref GPIO_SLEW_RATE_FAST
//! - \ref GPIO_SLEW_RATE_SLOW
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note there are some problem in this API,will modify it later.
//!
//! \return None.
//
void 
GPIOSlewRataConfigure(unsigned long ulPort, unsigned long ulPins,
                                            unsigned long ulSlewRateCfg)
{
    unsigned long ulPortBase;
	unsigned long ulBit;

    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    
	ulPortBase = GPIOToPortGet(ulPort);

    for(ulBit = 0; ulBit < 32; ulBit++)
    {
        if(((ulPins >> ulBit) & 1) != 0)
        {
            //
            // Passive Filter configure
            //
            xHWREG(ulPortBase + PORT_PCR + ulBit * 4) &= ~PORT_PCR_SRE_ENABLE ;
            xHWREG(ulPortBase + PORT_PCR + ulBit * 4) |= ulSlewRateCfg ;
        }
    }
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
GPIOPinConfigure(unsigned long ulPinConfig)
{
    unsigned long ulPortBase, ulPinBase, ulMux;
    unsigned long ulShift;

    //
    // Extract the Port Base shift.
    //
    ulShift = (ulPinConfig >> 12) & 0x0f;
    ulPortBase = g_pulPortBase[ulShift]; 

    //
    // Extract the pin shift number.
    // 
    ulShift = (ulPinConfig >> 4) & 0xff; 
    ulPinBase = ulShift * 4;

    //
    // Extract the pin mux.
    // 
    ulMux = ulPinConfig & 0x0f; 
    
    //
    // Clear the corresponding pin mux first.
    //
    xHWREG(ulPortBase + ulPinBase) &= ~PORT_PCR_PIN_MUX_M;

    //
    // Set the corresponding pin mux.
    //
    xHWREG(ulPortBase + ulPinBase) |= (ulMux << 8);
}

//*****************************************************************************
//
//! \brief Get the GPIO port from a short Pin.
//!
//! \param eShortPin is the base address of the GPIO port
//!
//! \note None.
//! 
//! \return GPIO port address which is used by GPIO API.
//
//*****************************************************************************
unsigned long 
GPIOPinToPort(unsigned long ulPort, unsigned long ulPin)
{      
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    return ulPort;
}

//*****************************************************************************
//
//! \brief Get the GPIO pin number from a short Pin.
//!
//! \param ulPort is the base address of the GPIO port
//!
//! \note None.
//! 
//! \return GPIO pin number which is used by GPIO API.
//
//*****************************************************************************
unsigned long 
GPIOPinToPin(unsigned long ulPort, unsigned long ulPin)
{        
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    return ulPin;
}

