//*****************************************************************************
//
//! \file xgpio.c
//! \brief Driver for the System Controller.
//! \version V2.1.1.0
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

#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_types.h"
#include "xdebug.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"

typedef struct
{
    //
    // Pin ID( PORT[31:16] | Pin[15:0])
    //
    unsigned long ulPinID;

    //
    // Pin interrupt callback function
    //
    xtEventCallback pfnGPIOPinHandlerCallback;
}
tGPIOPinIntAsssign;

//
// GPIO Pins Interrupt Assignment table.
//
static tGPIOPinIntAsssign g_psGPIOPinIntAssignTable[xGPIO_INT_NUMBER] = {0};


//*****************************************************************************
//
// The base addresses of all the GPIO modules.  Both the APB and AHB apertures
// are provided.
//
//*****************************************************************************
static const unsigned long g_pulGPIOBaseAddrs[] =
{
    GPIO_PORTA_BASE, GPIO_PORTA_AHB_BASE,
    GPIO_PORTB_BASE, GPIO_PORTB_AHB_BASE,
    GPIO_PORTC_BASE, GPIO_PORTC_AHB_BASE,
    GPIO_PORTD_BASE, GPIO_PORTD_AHB_BASE,
    GPIO_PORTE_BASE, GPIO_PORTE_AHB_BASE,
    GPIO_PORTF_BASE, GPIO_PORTF_AHB_BASE,
    GPIO_PORTG_BASE, GPIO_PORTG_AHB_BASE,
    GPIO_PORTH_BASE, GPIO_PORTH_AHB_BASE,
    GPIO_PORTJ_BASE, GPIO_PORTJ_AHB_BASE,
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
    return((ulPort == GPIO_PORTA_BASE) || (ulPort == GPIO_PORTA_AHB_BASE) ||
           (ulPort == GPIO_PORTB_BASE) || (ulPort == GPIO_PORTB_AHB_BASE) ||
           (ulPort == GPIO_PORTC_BASE) || (ulPort == GPIO_PORTC_AHB_BASE) ||
           (ulPort == GPIO_PORTD_BASE) || (ulPort == GPIO_PORTD_AHB_BASE) ||
           (ulPort == GPIO_PORTE_BASE) || (ulPort == GPIO_PORTE_AHB_BASE) ||
           (ulPort == GPIO_PORTF_BASE) || (ulPort == GPIO_PORTF_AHB_BASE) ||
           (ulPort == GPIO_PORTG_BASE) || (ulPort == GPIO_PORTG_AHB_BASE) ||
           (ulPort == GPIO_PORTH_BASE) || (ulPort == GPIO_PORTH_AHB_BASE) ||
           (ulPort == GPIO_PORTJ_BASE) || (ulPort == GPIO_PORTJ_AHB_BASE));
}
#endif

//*****************************************************************************
//
//! \brief Get the GPIO Peripheral Id from a short Pin.
//!
//! \param eShortPin is the base address of the GPIO port
//!
//! \note For NUC1xx,all GPIO port use the some Peripheral clock.
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

    return xSysCtlPeripheralIdGet(ulPort);
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
//! \param eShortPin is the base address of the GPIO port
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


//*****************************************************************************
//
//! \brief Sets the direction and mode of the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port
//! \param ucPins is the bit-packed representation of the pin(s).
//! \param ulPinIO is the pin direction and/or mode.
//!
//! This function will set the specified pin(s) on the selected GPIO port
//! as either an input or output under software control, or it will set the
//! pin to be under hardware control.
//!
//! The parameter \e ulPinIO is an enumerated data type that can be one of
//! the following values:
//!
//! - \b GPIO_DIR_MODE_IN
//! - \b GPIO_DIR_MODE_OUT
//! - \b GPIO_DIR_MODE_HW
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
//! \note GPIOPadConfigSet() must also be used to configure the corresponding
//! pad(s) in order for them to propagate the signal to/from the GPIO.
//!
//! \return None.
//
//*****************************************************************************
void
GPIODirModeSet(unsigned long ulPort, unsigned char ucPins,
               unsigned long ulPinIO)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    xASSERT((ulPinIO == GPIO_DIR_MODE_IN) || (ulPinIO == GPIO_DIR_MODE_OUT) ||
           (ulPinIO == GPIO_DIR_MODE_HW));

    //
    // Set the pin direction and mode.
    //
    xHWREG(ulPort + GPIO_DIR) = ((ulPinIO & 1) ?
                                  (xHWREG(ulPort + GPIO_DIR) | ucPins) :
                                  (xHWREG(ulPort + GPIO_DIR) & ~(ucPins)));
    xHWREG(ulPort + GPIO_AFSEL) = ((ulPinIO & 2) ?
                                    (xHWREG(ulPort + GPIO_AFSEL) | ucPins) :
                                    (xHWREG(ulPort + GPIO_AFSEL) &
                                     ~(ucPins)));
}

//*****************************************************************************
//
//! \brief Gets the direction and mode of a pin.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPin is the pin number.
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
GPIODirModeGet(unsigned long ulPort, unsigned char ucPin)
{
    unsigned long ulDir, ulAFSEL;

    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    xASSERT(ucPin < 8);

    //
    // Convert from a pin number to a bit position.
    //
    ucPin = 1 << ucPin;

    //
    // Return the pin direction and mode.
    //
    ulDir = xHWREG(ulPort + GPIO_DIR);
    ulAFSEL = xHWREG(ulPort + GPIO_AFSEL);
    return(((ulDir & ucPin) ? 1 : 0) | ((ulAFSEL & ucPin) ? 2 : 0));
}

//*****************************************************************************
//
//! \brief Sets the interrupt type for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//! \param ulIntType specifies the type of interrupt trigger mechanism.
//!
//! \details This function sets up the various interrupt trigger mechanisms for the
//! specified pin(s) on the selected GPIO port.
//!
//! The parameter \e ulIntType is an enumerated data type that can be one of
//! the following values:
//!
//! - \b GPIO_FALLING_EDGE
//! - \b GPIO_RISING_EDGE
//! - \b GPIO_BOTH_EDGES
//! - \b GPIO_LOW_LEVEL
//! - \b GPIO_HIGH_LEVEL
//!
//! where the different values describe the interrupt detection mechanism
//! (edge or level) and the particular triggering event (falling, rising,
//! or both edges for edge detect, low or high for level detect).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note In order to avoid any spurious interrupts, the user must
//! ensure that the GPIO inputs remain stable for the duration of
//! this function.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOIntTypeSet(unsigned long ulPort, unsigned char ucPins,
               unsigned long ulIntType)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    xASSERT((ulIntType == GPIO_FALLING_EDGE) ||
           (ulIntType == GPIO_RISING_EDGE) || (ulIntType == GPIO_BOTH_EDGES) ||
           (ulIntType == GPIO_LOW_LEVEL) || (ulIntType == GPIO_HIGH_LEVEL));

    //
    // Set the pin interrupt type.
    //
    xHWREG(ulPort + GPIO_IBE) = ((ulIntType & 1) ?
                                  (xHWREG(ulPort + GPIO_IBE) | ucPins) :
                                  (xHWREG(ulPort + GPIO_IBE) & ~(ucPins)));
    xHWREG(ulPort + GPIO_IS) = ((ulIntType & 2) ?
                                 (xHWREG(ulPort + GPIO_IS) | ucPins) :
                                 (xHWREG(ulPort + GPIO_IS) & ~(ucPins)));
    xHWREG(ulPort + GPIO_IEV) = ((ulIntType & 4) ?
                                  (xHWREG(ulPort + GPIO_IEV) | ucPins) :
                                  (xHWREG(ulPort + GPIO_IEV) & ~(ucPins)));
}

//*****************************************************************************
//
//! \brief Gets the interrupt type for a pin.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPin is the pin number.
//!
//! This function gets the interrupt type for a specified pin on the selected
//! GPIO port.  The pin can be configured as a falling edge, rising edge, or
//! both edge detected interrupt, or it can be configured as a low level or
//! high level detected interrupt.  The type of interrupt detection mechanism
//! is returned as an enumerated data type.
//!
//! \return Returns one of the enumerated data types described for
//! GPIOIntTypeSet().
//
//*****************************************************************************
unsigned long
GPIOIntTypeGet(unsigned long ulPort, unsigned char ucPin)
{
    unsigned long ulIBE, ulIS, ulIEV;

    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    xASSERT(ucPin < 8);

    //
    // Convert from a pin number to a bit position.
    //
    ucPin = 1 << ucPin;

    //
    // Return the pin interrupt type.
    //
    ulIBE = xHWREG(ulPort + GPIO_IBE);
    ulIS = xHWREG(ulPort + GPIO_IS);
    ulIEV = xHWREG(ulPort + GPIO_IEV);
    return(((ulIBE & ucPin) ? 1 : 0) | ((ulIS & ucPin) ? 2 : 0) |
           ((ulIEV & ucPin) ? 4 : 0));
}

//*****************************************************************************
//
//! \brief Sets the pad configuration for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//! \param ulStrength specifies the output drive strength.
//! \param ulPinType specifies the pin type.
//!
//! This function sets the drive strength and type for the specified pin(s)
//! on the selected GPIO port.  For pin(s) configured as input ports, the
//! pad is configured as requested, but the only real effect on the input
//! is the configuration of the pull-up or pull-down termination.
//!
//! The parameter \e ulStrength can be one of the following values:
//!
//! - \b GPIO_STRENGTH_2MA
//! - \b GPIO_STRENGTH_4MA
//! - \b GPIO_STRENGTH_8MA
//! - \b GPIO_STRENGTH_8MA_SC
//!
//! where \b GPIO_STRENGTH_xMA specifies either 2, 4, or 8 mA output drive
//! strength, and \b GPIO_OUT_STRENGTH_8MA_SC specifies 8 mA output drive with
//! slew control.
//!
//! The parameter \e ulPinType can be one of the following values:
//!
//! - \b GPIO_PIN_TYPE_STD
//! - \b GPIO_PIN_TYPE_STD_WPU
//! - \b GPIO_PIN_TYPE_STD_WPD
//! - \b GPIO_PIN_TYPE_OD
//! - \b GPIO_PIN_TYPE_OD_WPU
//! - \b GPIO_PIN_TYPE_OD_WPD
//! - \b GPIO_PIN_TYPE_ANALOG
//!
//! where \b GPIO_PIN_TYPE_STD* specifies a push-pull pin, \b GPIO_PIN_TYPE_OD*
//! specifies an open-drain pin, \b *_WPU specifies a weak pull-up, \b *_WPD
//! specifies a weak pull-down, and \b GPIO_PIN_TYPE_ANALOG specifies an
//! analog input (for the comparators).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPadConfigSet(unsigned long ulPort, unsigned char ucPins,
                 unsigned long ulStrength, unsigned long ulPinType)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    xASSERT((ulStrength == GPIO_STRENGTH_2MA) ||
           (ulStrength == GPIO_STRENGTH_4MA) ||
           (ulStrength == GPIO_STRENGTH_8MA) ||
           (ulStrength == GPIO_STRENGTH_8MA_SC));
    xASSERT((ulPinType == GPIO_PIN_TYPE_STD) ||
           (ulPinType == GPIO_PIN_TYPE_STD_WPU) ||
           (ulPinType == GPIO_PIN_TYPE_STD_WPD) ||
           (ulPinType == GPIO_PIN_TYPE_OD) ||
           (ulPinType == GPIO_PIN_TYPE_OD_WPU) ||
           (ulPinType == GPIO_PIN_TYPE_OD_WPD) ||
           (ulPinType == GPIO_PIN_TYPE_ANALOG))

    //
    // Set the output drive strength.
    //
    xHWREG(ulPort + GPIO_DR2R) = ((ulStrength & 1) ?
                                   (xHWREG(ulPort + GPIO_DR2R) | ucPins) :
                                   (xHWREG(ulPort + GPIO_DR2R) & ~(ucPins)));
    xHWREG(ulPort + GPIO_DR4R) = ((ulStrength & 2) ?
                                   (xHWREG(ulPort + GPIO_DR4R) | ucPins) :
                                   (xHWREG(ulPort + GPIO_DR4R) & ~(ucPins)));
    xHWREG(ulPort + GPIO_DR8R) = ((ulStrength & 4) ?
                                   (xHWREG(ulPort + GPIO_DR8R) | ucPins) :
                                   (xHWREG(ulPort + GPIO_DR8R) & ~(ucPins)));
    xHWREG(ulPort + GPIO_SLR) = ((ulStrength & 8) ?
                                  (xHWREG(ulPort + GPIO_SLR) | ucPins) :
                                  (xHWREG(ulPort + GPIO_SLR) & ~(ucPins)));

    //
    // Set the pin type.
    //
    xHWREG(ulPort + GPIO_ODR) = ((ulPinType & 1) ?
                                  (xHWREG(ulPort + GPIO_ODR) | ucPins) :
                                  (xHWREG(ulPort + GPIO_ODR) & ~(ucPins)));
    xHWREG(ulPort + GPIO_PUR) = ((ulPinType & 2) ?
                                  (xHWREG(ulPort + GPIO_PUR) | ucPins) :
                                  (xHWREG(ulPort + GPIO_PUR) & ~(ucPins)));
    xHWREG(ulPort + GPIO_PDR) = ((ulPinType & 4) ?
                                  (xHWREG(ulPort + GPIO_PDR) | ucPins) :
                                  (xHWREG(ulPort + GPIO_PDR) & ~(ucPins)));
    xHWREG(ulPort + GPIO_DEN) = ((ulPinType & 8) ?
                                  (xHWREG(ulPort + GPIO_DEN) | ucPins) :
                                  (xHWREG(ulPort + GPIO_DEN) & ~(ucPins)));

    //
    // Set the analog mode select register.  This register only appears in
    // DustDevil-class (and later) devices, but is a harmless write on
    // Sandstorm- and Fury-class devices.
    //
    xHWREG(ulPort + GPIO_AMSEL) =
        ((ulPinType == GPIO_PIN_TYPE_ANALOG) ?
         (xHWREG(ulPort + GPIO_AMSEL) | ucPins) :
         (xHWREG(ulPort + GPIO_AMSEL) & ~(ucPins)));
}

//*****************************************************************************
//
//! \brief Gets the pad configuration for a pin.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPin is the pin number.
//! \param pulStrength is a pointer to storage for the output drive strength.
//! \param pulPinType is a pointer to storage for the output drive type.
//!
//! This function gets the pad configuration for a specified pin on the
//! selected GPIO port.  The values returned in \e pulStrength and
//! \e pulPinType correspond to the values used in GPIOPadConfigSet().  This
//! function also works for pin(s) configured as input pin(s); however, the
//! only meaningful data returned is whether the pin is terminated with a
//! pull-up or down resistor.
//!
//! \return None
//
//*****************************************************************************
void
GPIOPadConfigGet(unsigned long ulPort, unsigned char ucPin,
                 unsigned long *pulStrength, unsigned long *pulPinType)
{
    unsigned long ulTemp1, ulTemp2, ulTemp3, ulTemp4;

    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    xASSERT(ucPin < 8);

    //
    // Convert from a pin number to a bit position.
    //
    ucPin = (1 << ucPin);

    //
    // Get the drive strength for this pin.
    //
    ulTemp1 = xHWREG(ulPort + GPIO_DR2R);
    ulTemp2 = xHWREG(ulPort + GPIO_DR4R);
    ulTemp3 = xHWREG(ulPort + GPIO_DR8R);
    ulTemp4 = xHWREG(ulPort + GPIO_SLR);
    *pulStrength = (((ulTemp1 & ucPin) ? 1 : 0) | ((ulTemp2 & ucPin) ? 2 : 0) |
                    ((ulTemp3 & ucPin) ? 4 : 0) | ((ulTemp4 & ucPin) ? 8 : 0));

    //
    // Get the pin type.
    //
    ulTemp1 = xHWREG(ulPort + GPIO_ODR);
    ulTemp2 = xHWREG(ulPort + GPIO_PUR);
    ulTemp3 = xHWREG(ulPort + GPIO_PDR);
    ulTemp4 = xHWREG(ulPort + GPIO_DEN);
    *pulPinType = (((ulTemp1 & ucPin) ? 1 : 0) | ((ulTemp2 & ucPin) ? 2 : 0) |
                   ((ulTemp3 & ucPin) ? 4 : 0) | ((ulTemp4 & ucPin) ? 8 : 0));
}

//*****************************************************************************
//
//! \brief Init the GPIO Port X Interrupt Callback function.
//!
//! \param ulPort is the base address of the GPIO port.
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//! \param ulPin is the bit-packed representation of the pin.
//! Details please refer to \ref xGPIO_General_Pin_IDs.
//! \param pfnCallback is the callback function.
//! Details please refer to \ref xLowLayer_Exported_Types.
//!
//! When there is any pins interrupt occrus, Interrupt Handler will 
//! call the callback function. 
//! 
//! param of pfnCallback
//! - pvCBData not used, always 0.
//! - ulEvent not used, always 0.
//! - ulMsgParam not used, always 0.
//! Details please refer to \ref xGPIO_General_Pin_IDs_CoX.
//! - pvMsgData not used, always 0.
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

    ulPinID = (ulPort  << 16) | ulPin;

    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        //
        // Find the corresponding pin, Set the interrupts callback.
        //        
        if(g_psGPIOPinIntAssignTable[i].ulPinID == ulPinID)
        {
            g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback =
                                         xtPortCallback;
            break;
        }
        
        //
        // Below are empty item, have not assigned this pin
        // Assign the pin item
        //
        if (g_psGPIOPinIntAssignTable[i].ulPinID == 0)
        {
            g_psGPIOPinIntAssignTable[i].ulPinID = ulPinID;
            g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback =
                                         xtPortCallback;
            break;
        }
    } 
}

//*****************************************************************************
//
//! \brief GPIO Port x Interrupt Handler.
//!
//! \param ulPort is the base address of the GPIO port. 
//!
//! \return Returns the pins which interrupt happen.
//
//*****************************************************************************
unsigned long
GPIOIntHandler(unsigned long ulPort)    
{
    unsigned long ulIntPins;
    int i;
    
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    
    //
    // Gets interrupt status
    //
    ulIntPins = GPIOPinIntStatus(ulPort, xfalse);

    //
    // Clear Int flag
    //
    GPIOPinIntClear(ulPort, ulIntPins);

    //
    // Call Callback function
    //
    for(i = 0; i < xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulPinID & 0xFFFF0000) == 
           ((ulPort & 0x0000FFFF) << 16))
        {
            if((g_psGPIOPinIntAssignTable[i].ulPinID & 0x0000FFFF & 
                ulIntPins))
            {
                if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
                {
                    g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback
                    (0,0,0,0);
                }
            }
        }
    }
    
    return ulIntPins;

}

//*****************************************************************************
//
//! \brief GPIO Port A Interrupt Handler.
//!
//! If users want to user the GPIO Callback feature, Users should promise 
//! that the GPIO Handle in the vector table is GPIOAIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOAIntHandler(void)    
{
    volatile unsigned long ulIntPins;
    
    //
    // Call pin interrupt callback functions
    //
    ulIntPins = GPIOIntHandler(GPIO_PORTA_BASE);
    
    //
    // TODO: User can use the ulIntPins to do more things if have not 
    // init the callback function.
    //
}

//*****************************************************************************
//
//! \brief GPIO Port B Interrupt Handler.
//!
//! If users want to user the GPIO Callback feature, Users should promise 
//! that the GPIO Handle in the vector table is GPIOBIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOBIntHandler(void)    
{
    volatile unsigned long ulIntPins;
    
    //
    // Call pin interrupt callback functions
    //
    ulIntPins = GPIOIntHandler(GPIO_PORTB_BASE);
    
    //
    // TODO: User can use the ulIntPins to do more things if have not 
    // init the callback function.
    //

}

//*****************************************************************************
//
//! \brief GPIO Port C Interrupt Handler.
//!
//! If users want to user the GPIO Callback feature, Users should promise 
//! that the GPIO Handle in the vector table is GPIOCIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOCIntHandler(void)    
{
    volatile unsigned long ulIntPins;
    
    //
    // Call pin interrupt callback functions
    //
    ulIntPins = GPIOIntHandler(GPIO_PORTC_BASE);
    
    //
    // TODO: User can use the ulIntPins to do more things if have not 
    // init the callback function.
    //
}

//*****************************************************************************
//
//! \brief GPIO Port D Interrupt Handler.
//!
//! If users want to user the GPIO Callback feature, Users should promise 
//! that the GPIO Handle in the vector table is GPIODIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
GPIODIntHandler(void)    
{
    volatile unsigned long ulIntPins;
    
    //
    // Call pin interrupt callback functions
    //
    ulIntPins = GPIOIntHandler(GPIO_PORTD_BASE);
    
    //
    // TODO: User can use the ulIntPins to do more things if have not 
    // init the callback function.
    //
}

//*****************************************************************************
//
//! \brief GPIO Port E Interrupt Handler.
//!
//! If users want to user the GPIO Callback feature, Users should promise 
//! that the GPIO Handle in the vector table is GPIOEIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOEIntHandler(void)    
{
    volatile unsigned long ulIntPins;
    
    //
    // Call pin interrupt callback functions
    //
    ulIntPins = GPIOIntHandler(GPIO_PORTE_BASE);
    
    //
    // TODO: User can use the ulIntPins to do more things if have not 
    // init the callback function.
    //
}

//*****************************************************************************
//
//! \brief GPIO Port F Interrupt Handler.
//!
//! If users want to user the GPIO Callback feature, Users should promise 
//! that the GPIO Handle in the vector table is GPIOFIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOFIntHandler(void)    
{
    volatile unsigned long ulIntPins;
    
    //
    // Call pin interrupt callback functions
    //
    ulIntPins = GPIOIntHandler(GPIO_PORTF_BASE);
    
    //
    // TODO: User can use the ulIntPins to do more things if have not 
    // init the callback function.
    //
}

//*****************************************************************************
//
//! \brief GPIO Port G Interrupt Handler.
//!
//! If users want to user the GPIO Callback feature, Users should promise 
//! that the GPIO Handle in the vector table is GPIOGIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOGIntHandler(void)    
{
    volatile unsigned long ulIntPins;
    
    //
    // Call pin interrupt callback functions
    //
    ulIntPins = GPIOIntHandler(GPIO_PORTG_BASE);
    
    //
    // TODO: User can use the ulIntPins to do more things if have not 
    // init the callback function.
    //
}

//*****************************************************************************
//
//! \brief GPIO Port H Interrupt Handler.
//!
//! If users want to user the GPIO Callback feature, Users should promise 
//! that the GPIO Handle in the vector table is GPIOHIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOHIntHandler(void)    
{
    volatile unsigned long ulIntPins;
    
    //
    // Call pin interrupt callback functions
    //
    ulIntPins = GPIOIntHandler(GPIO_PORTH_BASE);
    
    //
    // TODO: User can use the ulIntPins to do more things if have not 
    // init the callback function.
    //
}

//*****************************************************************************
//
//! \brief GPIO Port J Interrupt Handler.
//!
//! If users want to user the GPIO Callback feature, Users should promise 
//! that the GPIO Handle in the vector table is GPIOJIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOJIntHandler(void)    
{
    volatile unsigned long ulIntPins;
    
    //
    // Call pin interrupt callback functions
    //
    ulIntPins = GPIOIntHandler(GPIO_PORTJ_BASE);
    
    //
    // TODO: User can use the ulIntPins to do more things if have not 
    // init the callback function.
    //
}

//*****************************************************************************
//
//! \brief Enables interrupts for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! Unmasks the interrupt for the specified pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinIntEnable(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Enable the interrupts.
    //
    xHWREG(ulPort + GPIO_IM) |= ucPins;
}

//*****************************************************************************
//
//! \brief Disables interrupts for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! Masks the interrupt for the specified pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinIntDisable(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Disable the interrupts.
    //
    xHWREG(ulPort + GPIO_IM) &= ~(ucPins);
}

//*****************************************************************************
//
//! \brief Gets interrupt status for the specified GPIO port.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param bMasked specifies whether masked or raw interrupt status is
//! returned.
//!
//! If \e bMasked is set as \b true, then the masked interrupt status is
//! returned; otherwise, the raw interrupt status will be returned.
//!
//! \return Returns a bit-packed byte, where each bit that is set identifies
//! an active masked or raw interrupt, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//! Bits 31:8 should be ignored.
//
//*****************************************************************************
long
GPIOPinIntStatus(unsigned long ulPort, xtBoolean bMasked)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Return the interrupt status.
    //
    if(bMasked)
    {
        return(xHWREG(ulPort + GPIO_MIS));
    }
    else
    {
        return(xHWREG(ulPort + GPIO_RIS));
    }
}

//*****************************************************************************
//
//! \brief Clears the interrupt for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! Clears the interrupt for the specified pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note Because there is a write buffer in the Cortex-M3 processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinIntClear(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Clear the interrupts.
    //
    xHWREG(ulPort + GPIO_ICR) = ucPins;
}

//*****************************************************************************
//
//! \brief Reads the values present of the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
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
//! is returned as a 0.  Bits 31:8 should be ignored.
//
//*****************************************************************************
long
GPIOPinRead(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Return the pin value(s).
    //
    return(xHWREG(ulPort + (GPIO_DATA + (ucPins << 2))));
}

//*****************************************************************************
//
//! \brief Writes a value to the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
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
GPIOPinWrite(unsigned long ulPort, unsigned char ucPins, unsigned char ucVal)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Write the pins.
    //
    xHWREG(ulPort + (GPIO_DATA + (ucPins << 2))) = ucVal;
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use as analog-to-digital converter inputs.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The analog-to-digital converter input pins must be properly configured
//! to function correctly on DustDevil-class devices.  This function provides
//! the proper configuration for those pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note This cannot be used to turn any pin into an ADC input; it only
//! configures an ADC input pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeADC(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be inputs.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_IN);

    //
    // Set the pad(s) for analog operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_ANALOG);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use as a CAN device.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The CAN pins must be properly configured for the CAN peripherals to
//! function correctly.  This function provides a typical configuration for
//! those pin(s); other configurations may work as well depending upon the
//! board setup (for example, using the on-chip pull-ups).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note This cannot be used to turn any pin into a CAN pin; it only
//! configures a CAN pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeCAN(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be inputs.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use as an analog comparator input.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The analog comparator input pins must be properly configured for the analog
//! comparator to function correctly.  This function provides the proper
//! configuration for those pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note This cannot be used to turn any pin into an analog comparator input;
//! it only configures an analog comparator pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeACMPAnalog(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be inputs.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_IN);

    //
    // Set the pad(s) for analog operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_ANALOG);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use as an analog comparator output.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The analog comparator output pins must be properly configured for the analog
//! comparator to function correctly.  This function provides the proper
//! configuration for those pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeACMPDigital(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be inputs.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for digital output.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use as GPIO inputs.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The GPIO pins must be properly configured in order to function correctly as
//! GPIO inputs; this is especially true of Fury-class devices where the
//! digital input enable is turned off by default.  This function provides the
//! proper configuration for those pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeGPIOInput(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be inputs.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_IN);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use as GPIO outputs.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The GPIO pins must be properly configured in order to function correctly as
//! GPIO outputs; this is especially true of Fury-class devices where the
//! digital input enable is turned off by default.  This function provides the
//! proper configuration for those pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeGPIOOutput(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be outputs.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_OUT);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use as GPIO open drain outputs.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The GPIO pins must be properly configured in order to function correctly as
//! GPIO outputs; this is especially true of Fury-class devices where the
//! digital input enable is turned off by default.  This function provides the
//! proper configuration for those pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeGPIOOutputOD(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be outputs.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_OUT);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_OD);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use by the I2C peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The I2C pins must be properly configured for the I2C peripheral to function
//! correctly.  This function provides the proper configuration for those
//! pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note This cannot be used to turn any pin into an I2C pin; it only
//! configures an I2C pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeI2C(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for open-drain operation with a weak pull-up.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_OD_WPU);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use by the PWM peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The PWM pins must be properly configured for the PWM peripheral to function
//! correctly.  This function provides a typical configuration for those
//! pin(s); other configurations may work as well depending upon the board
//! setup (for example, using the on-chip pull-ups).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note This cannot be used to turn any pin into a PWM pin; it only
//! configures a PWM pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypePWM(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use by the QEI peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The QEI pins must be properly configured for the QEI peripheral to function
//! correctly.  This function provides a typical configuration for those
//! pin(s); other configurations may work as well depending upon the board
//! setup (for example, not using the on-chip pull-ups).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note This cannot be used to turn any pin into a QEI pin; it only
//! configures a QEI pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeQEI(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation with a weak pull-up.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use by the SSI peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The SSI pins must be properly configured for the SSI peripheral to function
//! correctly.  This function provides a typical configuration for those
//! pin(s); other configurations may work as well depending upon the board
//! setup (for example, using the on-chip pull-ups).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note This cannot be used to turn any pin into a SSI pin; it only
//! configures a SSI pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeSPI(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use by the Timer peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The CCP pins must be properly configured for the timer peripheral to
//! function correctly.  This function provides a typical configuration for
//! those pin(s); other configurations may work as well depending upon the
//! board setup (for example, using the on-chip pull-ups).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note This cannot be used to turn any pin into a timer pin; it only
//! configures a timer pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeTimer(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use by the UART peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The UART pins must be properly configured for the UART peripheral to
//! function correctly.  This function provides a typical configuration for
//! those pin(s); other configurations may work as well depending upon the
//! board setup (for example, using the on-chip pull-ups).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note This cannot be used to turn any pin into a UART pin; it only
//! configures a UART pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeUART(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use by the USB peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! Some USB digital pins must be properly configured for the USB peripheral to
//! function correctly.  This function provides a typical configuration for
//! the digital USB pin(s); other configurations may work as well depending
//! upon the board setup (for example, using the on-chip pull-ups).
//!
//! This function should only be used with EPEN and PFAULT pins as all other
//! USB pins are analog in nature or are not used in devices without OTG
//! functionality.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note This cannot be used to turn any pin into a USB pin; it only
//! configures a USB pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeUSBDigital(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use by the USB peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! Some USB analog pins must be properly configured for the USB peripheral to
//! function correctly.  This function provides the proper configuration for
//! any USB pin(s).  This can also be used to configure the EPEN and PFAULT pins
//! so that they are no longer used by the USB controller.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note This cannot be used to turn any pin into a USB pin; it only
//! configures a USB pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeUSBAnalog(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be inputs.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_IN);

    //
    // Set the pad(s) for analog operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_ANALOG);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use by the I2S peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! Some I2S pins must be properly configured for the I2S peripheral to
//! function correctly.  This function provides a typical configuration for
//! the digital I2S pin(s); other configurations may work as well depending
//! upon the board setup (for example, using the on-chip pull-ups).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note This cannot be used to turn any pin into a I2S pin; it only
//! configures a I2S pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeI2S(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use by the Ethernet peripheral as LED signals.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The Ethernet peripheral provides two signals that can be used to drive
//! an LED (e.g. for link status/activity).  This function provides a typical
//! configuration for the pins.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note This cannot be used to turn any pin into an Ethernet LED pin; it only
//! configures an Ethernet LED pin for proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeEthernetLED(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! \brief Configures pin(s) for use by the external peripheral interface.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The external peripheral interface pins must be properly configured for the
//! external peripheral interface to function correctly.  This function
//! provides a typica configuration for those pin(s); other configurations may
//! work as well depending upon the board setup (for exampe, using the on-chip
//! pull-ups).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note This cannot be used to turn any pin into an external peripheral
//! interface pin; it only configures an external peripheral interface pin for
//! proper operation.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeEPI(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be peripheral controlled.
    //
    GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD);
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
//! \note This function is only valid on Tempest-class devices.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinConfigure(unsigned long ulPinConfig)
{
    unsigned long ulBase, ulShift;

    //
    // Check the argument.
    //
    xASSERT(((ulPinConfig >> 16) & 0xff) < 9);
    xASSERT(((ulPinConfig >> 8) & 0xe3) == 0);

    //
    // Extract the base address index from the input value.
    //
    ulBase = (ulPinConfig >> 16) & 0xff;

    //
    // Get the base address of the GPIO module, selecting either the APB or the
    // AHB aperture as appropriate.
    //
    if(xHWREG(SYSCTL_GPIOHBCTL) & (1 << ulBase))
    {
        ulBase = g_pulGPIOBaseAddrs[(ulBase << 1) + 1];
    }
    else
    {
        ulBase = g_pulGPIOBaseAddrs[ulBase << 1];
    }

    //
    // Extract the shift from the input value.
    //
    ulShift = (ulPinConfig >> 8) & 0xff;

    //
    // Write the requested pin muxing value for this GPIO pin.
    //
    xHWREG(ulBase + GPIO_PCTL) = ((xHWREG(ulBase + GPIO_PCTL) &
                                    ~(0xf << ulShift)) |
                                   ((ulPinConfig & 0xf) << ulShift));

}

