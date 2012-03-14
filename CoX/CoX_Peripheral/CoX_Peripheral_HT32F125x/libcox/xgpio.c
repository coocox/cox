//*****************************************************************************
//
//! \file xgpio.c
//! \brief Driver for the GPIO controller
//! \version V2.1.1.0
//! \date 2/25/2012
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
    { 0,   0 },
    { 0,   0 },            
    { 0,   0 },
    { 0,   0 },        
    { 0,   0 },
    { 0,   0 },
    { 0,   0 },        
    { 0,   0 }                  
};

//*****************************************************************************
//
// An array that maps the "GPIO set" number (which is stored in the upper
// nibble of the GPIO_*_* defines) to the GCR_GP?MFP register that
// controls the GPIO function for that GPIO.
//
//*****************************************************************************
static const unsigned long g_pulIPRSTRegs[] =
{
    AFIO_GPACFGR,
    AFIO_GPBCFGR
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
    return((ulPort == GPIO_PORTA_BASE) || 
           (ulPort == GPIO_PORTB_BASE));
}
#endif

//*****************************************************************************
//
//! \internal
//! \brief External INT0 ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EVWUPIntHandler(void)
{
    //
    // Clear the interrupt flag.
    //
    xHWREG(GPIO_EXTI_BASE + EXTI_WAKUPFLG) |= 0x0000FFFF;
       
}

//*****************************************************************************
//
//! \internal
//! \brief External INT0 ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EINT0IntHandler(void)
{
    unsigned long i;
    
    //
    // Clear the interrupt flag.
    //
    xHWREG(GPIO_EXTI_BASE + EXTI_EDGEFLGR) |= GPIO_PIN_0;
   
    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID) ==  GPIO_PIN_0)
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
//! \brief External INT1 ISR .
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EINT1IntHandler(void)
{   
    unsigned long i;
    
    //
    // Clear the interrupt flag.
    //
    xHWREG(GPIO_EXTI_BASE + EXTI_EDGEFLGR) |= GPIO_PIN_1;
    
    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID) == GPIO_PIN_1)
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
//! \brief Sets the direction and mode of the specified pin.
//!
//! \param ulPort is the base address of the GPIO port
//! \param ulPins is the bit-packed representation of the pin.
//! \param ulPinIO is the pin direction and/or hardware contorl mode.
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
//! - \b GPIO_DIR_MODE_HW
//!
//! where \b GPIO_DIR_MODE_IN specifies that the pin will be programmed as
//! a software controlled input, \b GPIO_DIR_MODE_OUT specifies that the pin
//! will be programmed as a software controlled output.\b GPIO_DIR_MODE_HW 
//! specifies that the pin will controled by hardware.
//!
//! \return None.
//
//*****************************************************************************
void
GPIODirModeSet(unsigned long ulPort, unsigned long ulPins, unsigned long ulPinIO)
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
    if(ulPinIO == GPIO_DIR_MODE_IN)
    {
        xHWREG(ulPort + GPIO_DIRCR) &= ~ulPins;
        GPIOInputConfigure(ulPort, ulPins, GPIO_INPUT_ENABLE);
    }
    else if(ulPinIO == GPIO_DIR_MODE_OUT)
    {
        xHWREG(ulPort + GPIO_DIRCR) |= ulPins;
    }
    else if(ulPinIO == GPIO_DIR_MODE_HW)
    {
          
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
    unsigned long ulBit;
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    for(ulBit=0; ulBit<16; ulBit++)
    {
        if(ulPin & (1 << ulBit))
        {
            break;
        }
    }
    return GPIODirModeGet(ulPort, ulBit);
}

//*****************************************************************************
//
//! Gets the direction and mode of a pin.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucBit is the pin number.
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
    
    if(xHWREG(ulPort + GPIO_ODR) & (1 << ulBit))
    {
        return GPIO_DIR_MODE_OD;
    }
    
    if(xHWREG(ulPort + GPIO_DIRCR) & (1 << ulBit))
    {
        return GPIO_DIR_MODE_OUT;
    }
    else
    {
        return GPIO_DIR_MODE_IN;
    }
}

//*****************************************************************************
//
//! \brief Enables or Disables the input control of specified GPIO pins(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//! \param ulEnable is to enable or disable the input control. it can be selected
//! from the following value:
//!
//! - \ref GPIO_INPUT_ENABLE
//! - \ref GPIO_INPUT_DISABLE
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void 
GPIOInputConfigure(unsigned long ulPort, unsigned long ulPins, unsigned long ulEnable)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    
    if(ulEnable == GPIO_INPUT_ENABLE)
    {
        xHWREG(ulPort + GPIO_INER) |= ulPins;   
    }
    else if(ulEnable == GPIO_INPUT_DISABLE)
    {
        xHWREG(ulPort + GPIO_INER) &= ~ulPins;  
    }
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
//! specified pin(s) on the selected GPIO port.
//!
//! The parameter \e ulIntType is an enumerated data type that can be one of
//! the following values:
//!
//! - \b GPIO_FALLING_EDGE
//! - \b GPIO_RISING_EDGE
//! - \b GPIO_LOW_LEVEL
//! - \b GPIO_HIGH_LEVEL
//! - \b GPIO_BOTH_LEVEL
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
GPIOPinIntEnable(unsigned long ulPort, unsigned long ulPins,
               unsigned long ulIntType)
{
    int i;
    unsigned char ucFlag;
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
    for(i = 0; i < 16; i++)
    {
        ucFlag = ((ulPins >> i) & 0x01) ? 1 : 0;
        if(ucFlag == 1)
        {    
             //
             // Set the EXTI line source
             //
             if(ulPort == GPIO_PORTA_BASE)
             {
                 if(i < 8)
                 {
                     xHWREG(GPIO_AFIO_BASE + AFIO_ESSRO) &= ~(1 << (i * 4));  
                 }
                 else
                 {
                     xHWREG(GPIO_AFIO_BASE + AFIO_ESSR1) &= ~(1 << ((i - 8) * 4)); 
                 }
             }
             else
             {
                 if(i < 8)
                 {
                     xHWREG(GPIO_AFIO_BASE + AFIO_ESSRO) |= (1 << (i * 4));  
                 }
                 else
                 {
                     xHWREG(GPIO_AFIO_BASE + AFIO_ESSR1) |= (1 << ((i - 8) * 4)); 
                 }
             }
      
             //
             // Set the EXTI INT trigger type
             //
             xHWREG(GPIO_EXTI_BASE + EXTI_CFGR0 + i * 4) &= ~EXTI_CFGR0_SRCTYPE_M;
             xHWREG(GPIO_EXTI_BASE + EXTI_CFGR0 + i * 4) |= ulIntType;
        }   
    }
    
    //
    // Enable the pin interrupt.
    //
    xHWREG(GPIO_EXTI_BASE + EXTI_ICR) |= ulPins; 
    
}

//*****************************************************************************
//
//! \brief Disables interrupts for the specified pin(s).
//!
//! \param ulPort is the base address of the EXTI.
//! \param ulPins is the bit-packed representation of the pin(s).
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
GPIOPinIntDisable(unsigned long ulPort, unsigned long ulPins)
{
  
    //
    // Disable the interrupts.
    //
    xHWREG(GPIO_EXTI_BASE + EXTI_ICR) &= ~ulPins;
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the specified Port.
//!
//! \param ulPort is the base address of the EXTI.
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
    ulPinID = ulPin;

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
//! \brief Get the EXTI interrupt Edge flag.
//!
//! \param None.
//!
//! \return Returns a bit-packed byte providing the state of the specified
//! pin, where bit 0 of the byte represents GPIO port pin 0, bit 1 represents
//! GPIO port pin 1, and so on.  Any bit that is not specified by \e ucPins
//! is returned as a 0.  Bits 31:16 should be ignored.
//
//*****************************************************************************
unsigned long 
EXTIIntEdgeStatusGet(void)
{
    return(xHWREG(GPIO_EXTI_BASE + EXTI_EDGEFLGR));
}

//*****************************************************************************
//
//! \brief Clear the EXTI interrupt Edge flag and status.
//!
//! \param ulEXTILine is the corresponding EXTI line status which should be clear.
//!  Please refer to \ref HT32F125x_EXTI_LINES.
//!
//! \return None.
//
//*****************************************************************************
void 
EXTIIntEdgeClear(unsigned long ulEXTILines)
{
    //
    // Write 1 to clear the corresponding EXTI intterrupt EDGE flag.
    //
    xHWREG(GPIO_EXTI_BASE + EXTI_EDGEFLGR) |= ulEXTILines;
      
    //
    // Write 1 to clear the corresponding EXTI intterrupt EDGE status.
    //
    xHWREG(GPIO_EXTI_BASE + EXTI_EDGESR) |= ulEXTILines;
}

//*****************************************************************************
//
//! \brief Clear the EXTI interrupt Edge flag and status.
//!
//! \param ulBase is use for short pin function.
//! \param ulEXTILine is the corresponding EXTI line status which should be clear.
//!  Please refer to \ref HT32F125x_EXTI_LINES.
//!
//! \return None.
//
//*****************************************************************************
void 
EXTIIntEdgeClear2(unsigned long ulBase, unsigned long ulEXTILines)
{
    //
    // Write 1 to clear the corresponding EXTI intterrupt EDGE flag.
    //
    xHWREG(GPIO_EXTI_BASE + EXTI_EDGEFLGR) |= ulEXTILines;
      
    //
    // Write 1 to clear the corresponding EXTI intterrupt EDGE flag.
    //
    xHWREG(GPIO_EXTI_BASE + EXTI_EDGESR) |= ulEXTILines;
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
    return(xHWREG(ulPort + GPIO_INR ) & (ulPins));
}

//*****************************************************************************
//
//! \brief Writes a value to the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//! \param ucVal is the value(0 or 1) to write to the pin(s).
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
    if(ucVal == 1)
    {
         xHWREG(ulPort + GPIO_SRR) |= ulPins; 
    }
    else if(ucVal == 0)
    {
         xHWREG(ulPort + GPIO_RR) |= ulPins;  
    }
}

//*****************************************************************************
//
//! \brief Writes a value to the specified GPIO port.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulVal is the value to write to the specified GPIO port.
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
    // Write data to the specified gpio port data.
    //
    xHWREG(ulPort + GPIO_OUTR) = ulVal;
}

//*****************************************************************************
//
//! \brief Gets output data for the specified GPIO port.
//!
//! \param ulPort is the base address of the GPIO port.
//!
//! \return Returns a bit-packed byte, where each bit that is set identifies
//! an active masked or raw interrupt, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//! Bits 31:16 should be ignored.
//
//*****************************************************************************
long
GPIOPinPortDoutGet(unsigned long ulPort)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Return the interrupt status.
    //
    return(xHWREG(ulPort + GPIO_OUTR));

}

//*****************************************************************************
//
//! \brief Selects the driving current of specified GPIO pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//! \param ulDrive is Selection of output driving current.it can be selected one
//! of the following values:
//! 
//! - \ref GPIO_DV_4MA
//! - \ref GPIO_DV_8MA
//!
//! \param ulPadType is the logical OR of several different values, many of 
//!  which are grouped into sets where only one can be chosen.
//!
//£¡The open drain mode is chosen with one of the following values:
//! - \ref GPIO_DIR_MODE_OD_EN
//! - \ref GPIO_DIR_MODE_OD_DIS
//!
//! The pull resistor configure is chosen with one of the following values:
//! - \ref GPIO_PIN_TYPE_STD_WPU
//! - \ref GPIO_PIN_TYPE_STD_WPD
//! - \ref GPIO_PR_DISABLE
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
                             unsigned long ulStrength, unsigned long ulPadType)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    xASSERT((ulStrength == GPIO_STRENGTH_4MA) ||
            (ulStrength == GPIO_STRENGTH_8MA));
    xASSERT((GPIO_DIR_MODE_OD_EN == (ulPadType & 0x00000010)) ||
            (GPIO_DIR_MODE_OD_DIS == (ulPadType & 0x00000010)) ||
            (GPIO_PIN_TYPE_STD_WPU == (ulPadType & 0x00000003)) ||
            (GPIO_PIN_TYPE_STD_WPD == (ulPadType & 0x00000003)) || 
            (GPIO_PR_DISABLE == (ulPadType & 0x00000003)));
    
    //
    // Pad strength configure
    //
    if(ulStrength == GPIO_STRENGTH_4MA)
    {
        xHWREG(ulPort + GPIO_DRVR) &= ~ulPins;
    }   
    else
    {
        xHWREG(ulPort + GPIO_DRVR) |= ulPins;
    }   
    
    //
    // Pad open drain configure
    //
    if(GPIO_DIR_MODE_OD_EN == (ulPadType & 0x00000010))
    {
        xHWREG(ulPort + GPIO_ODR) |= ulPins;
    }
    else
    {
         xHWREG(ulPort + GPIO_ODR) &= ~ulPins;
    }
        
    //
    // Pad pull resistor configure
    //
    if(GPIO_PIN_TYPE_STD_WPU == (ulPadType & 0x00000003))
    {
        xHWREG(ulPort + GPIO_PUR) |= ulPins;
        xHWREG(ulPort + GPIO_PDR) &= ~ulPins;            
    }
    else if(GPIO_PIN_TYPE_STD_WPD == (ulPadType & 0x00000003))
    {
        xHWREG(ulPort + GPIO_PUR) &= ~ulPins;
        xHWREG(ulPort + GPIO_PDR) |= ulPins;     
    }
    else
    {
        xHWREG(ulPort + GPIO_PUR) &= ~ulPins;
        xHWREG(ulPort + GPIO_PDR) &= ~ulPins;     
    }
}

//*****************************************************************************
//
//! \brief Lock configuration of GPIO pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void 
GPIOPinLockSet(unsigned long ulPort, unsigned long ulPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort)); 
    
    xHWREG(ulPort + GPIO_LOCKER) |= (0x5FA00000 | ulPins);
    
}

//*****************************************************************************
//
//! \brief Gets the lock state of specified GPIO port pin..
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPin is the bit-packed representation of the pin.
//!
//! The pin are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return xtrue represent the corresponding pin locked,
//!         xfalse represent the corresponding pin unlocked.
//
//*****************************************************************************
xtBoolean 
GPIOPinLockGet(unsigned long ulPort, unsigned long ulPin)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort)); 
    
    if(xHWREG(ulPort + GPIO_LOCKER) >> 16)
    {
        if(xHWREG(ulPort + GPIO_LOCKER) & ulPin)
        {
            return xtrue;
        }
        else
        {
            return xfalse;
        }
    }
    else
    {
        return  xfalse; 
    }
}

//*****************************************************************************
//
//! \brief Activate the specified EXTI line by software.
//!
//! \param ulEXTILine is the corresponding EXTI line which should be trigger.
//!
//! Enable the corresponding bit debounce function to EXTI line specified by
//! \e ulEXTILines, pleasure reference to /ref HT32F125x_EXTI_LINES.  
//!
//! \return None.
//
//*****************************************************************************
void 
EXTILineSoftwareTrigger(unsigned long ulEXTILine)
{
    xHWREG(GPIO_EXTI_BASE + EXTI_SSCR) |= ulEXTILine;
}

//*****************************************************************************
//
//! \brief Clear the specified EXTI line(s) by software.
//!
//! \param ulEXTILine is the corresponding EXTI line which should be clear.
//!
//! Enable the corresponding bit debounce function to EXTI line(s) specified by
//! \e ulEXTILines, pleasure reference to /ref HT32F125x_EXTI_LINES.  
//!
//! \return None.
//
//*****************************************************************************
void 
EXTILineSoftwareClear(unsigned long ulEXTILine)
{
    xHWREG(GPIO_EXTI_BASE + EXTI_SSCR) &= ~ulEXTILine;
}

//*****************************************************************************
//
//! \brief Enable the EXTI wakeup interrupt function.
//! 
//! \param ulEnable is to enable or disable EXTI wakeup interrupt, it can be
//! selected from the following values:
//!
//! - \ref EXTI_WAKEUP_INT_ENABLE
//! - \ref EXTI_WAKEUP_INT_DISABLE
//! 
//! \return None.
//
//*****************************************************************************
void 
EXTIWakeUpIntConfigure(unsigned long ulEnable)
{
    //
    // Check the arguments.
    //
    xASSERT((ulEnable == EXTI_WAKEUP_INT_ENABLE) ||
            (ulEnable == EXTI_WAKEUP_INT_DISABLE)); 
    if(ulEnable == EXTI_WAKEUP_INT_ENABLE)
    {
        xHWREG(GPIO_EXTI_BASE + EXTI_WAKUPCR) |= EXTI_WAKUPCR_EVWUPIEN;
    }
    else
    {
        xHWREG(GPIO_EXTI_BASE + EXTI_WAKUPCR) &= ~EXTI_WAKUPCR_EVWUPIEN;
    }
}

//*****************************************************************************
//
//! \brief EXTI Wake Up lines configure.
//! 
//! \param ulEXTILines is the logical or of extern interrupt line number.
//! \param ulLevel is the wake up active level, it can be selected from the 
//! following values:
//!
//! - \ref EXTI_LINE_WAKEUP_LOW
//! - \ref EXTI_LINE_WAKEUP_HIGH
//! 
//! \param ulEnable is to enable or disable the EXTI lines wake up function
//! 
//! - \ref EXTI_LINES_WAKEUP_ENABLE
//! - \ref EXTI_LINES_WAKEUP_DISABLE
//!
//! \return None.
//
//*****************************************************************************
void 
EXTILineWakeUpConfigure(unsigned long ulEXTILines, unsigned long ulLevel,
                                    unsigned long ulEnable)
{
    unsigned long ulBits;  
    
    //
    // Check the arguments.
    //
    xASSERT((ulLevel == EXTI_LINE_WAKEUP_HIGH) || 
            (ulLevel == EXTI_LINE_WAKEUP_HIGH));
    xASSERT((ulEnable == EXTI_LINES_WAKEUP_ENABLE) || 
            (ulEnable == EXTI_LINES_WAKEUP_DISABLE));
    
    for(ulBits=0; ulBits<16; ulBits++)
    {
        if(ulEXTILines & (1 << ulBits))
        {
            if(ulEnable == EXTI_LINES_WAKEUP_ENABLE)
            {
                //
                // Select the wakeup level
                //
                if(ulLevel == EXTI_LINE_WAKEUP_LOW)
                {
                    xHWREG(GPIO_EXTI_BASE + EXTI_WAKUPPOLR) |= (1 << ulBits);
                }
                else
                {
                    xHWREG(GPIO_EXTI_BASE + EXTI_WAKUPPOLR) &= ~(1 << ulBits);
                }
                    
                //
                // Enable the corresponding EXTI line wake up function.
                //
                xHWREG(GPIO_EXTI_BASE + EXTI_WAKUPCR) |= (1 << ulBits); 
            }
            else
            {
                //
                // Disable the corresponding EXTI line wake up function.
                //
                xHWREG(GPIO_EXTI_BASE + EXTI_WAKUPCR) &= ~(1 << ulBits); 
            }   
        }     
    }    
}

//*****************************************************************************
//
//! \brief EXTI Wake Up status get.
//! 
//! \param None
//!
//! \return Returns a bit-packed byte, where each bit that is set identifies
//! an active masked or raw interrupt, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//! Bits 31:16 should be ignored.
//
//*****************************************************************************
unsigned long 
EXTIWakeUpStatusGet(void)
{
    unsigned long ulStatus;
    
    ulStatus = xHWREG(GPIO_EXTI_BASE + EXTI_WAKUPFLG);
    
    return ulStatus;
}

//*****************************************************************************
//
//! \brief EXTI Wake Up status Clear.
//! 
//! \param ulEXTILine is the corresponding EXTI line status which should be clear.
//!  Please refer to \ref HT32F125x_EXTI_LINES.
//!
//! \return None.
//
//*****************************************************************************
void 
EXTIWakeUpStatusClear(unsigned long ulEXTILines)
{
    //
    // Write 1 to clear the corresponding EXTI line status.
    //
    xHWREG(GPIO_EXTI_BASE + EXTI_WAKUPFLG) |= ulEXTILines;
}

//*****************************************************************************
//
//! \brief Enable the debounce function of the specified EXTI line(s).
//!
//! \param ulEXTILines is the logical or of extern interrupt line number.
//!
//! Enable the corresponding bit debounce function to EXTI line(s) specified by
//! \e ulEXTILines, pleasure reference to /ref HT32F125x_EXTI_LINES.  
//!
//! \return None.
//
//*****************************************************************************
void
EXTILineDebounceEnable(unsigned long ulEXTILines)
{
    int i;
    
    for(i = 0; i < 16; i++)
    {
         if((ulEXTILines >> i) & 0x1)
         {
             xHWREG(GPIO_EXTI_BASE + EXTI_CFGR0 + i * 4) |=  EXTI_CFGR0_DBEN;
         }
    }
}


//*****************************************************************************
//
//! \brief Disable the debounce function of the specified GPIO pin(s).
//!
//! \param ulEXTILines is the logical or of extern interrupt line number.
//!
//! Enable the corresponding bit debounce function to EXTI line(s) specified by
//! \e ulEXTILines, pleasure reference to /ref HT32F125x_EXTI_LINES.  
//!
//! \return None.
//
//*****************************************************************************
void
EXTILineDebounceDisable(unsigned long ulEXTILines)
{
    int i;
    
    for(i = 0; i < 16; i++)
    {
         if((ulEXTILines >> i) & 0x1)
         {
             xHWREG(GPIO_EXTI_BASE + EXTI_CFGR0 + i * 4) &=  ~EXTI_CFGR0_DBEN;
         }
    }
}

//*****************************************************************************
//
//! \brief Set the De-bounce sampling cycle.
//!
//! \param ulDebounceClk is the De-bounce sampling clock.
//!
//! Set the De-bounce sampling cycle.  
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void
EXTIDebounceTimeSet(unsigned long ulEXTILines, unsigned long ulDebounceClk)
{
    int i;
    
    xASSERT(ulDebounceClk < EXTI_CFGR0_DBCNT_M);
    for(i = 0; i < 16; i++)
    {
         if((ulEXTILines >> i) & 0x1)
         {
             xHWREG(GPIO_EXTI_BASE + EXTI_CFGR0 + i * 4) &=  ~EXTI_CFGR0_DBCNT_M;
             xHWREG(GPIO_EXTI_BASE + EXTI_CFGR0 + i * 4) |= 
                           (ulDebounceClk & EXTI_CFGR0_DBCNT_M);
         }
    }              
}

//*****************************************************************************
//
//! \brief Get the De-bounce sampling cycle.
//!
//! \param None.
//!
//! \return The De-bounce sampling cycle.
//
//*****************************************************************************
long
EXTIDebounceTimeGet(unsigned long ulEXTILine)
{
    int i; 
    for(i = 0; i < 16; i++)
    {
        if((ulEXTILine >> i) & 0x1)
        {
           break;
        }
    }
     return (xHWREG(GPIO_EXTI_BASE + EXTI_CFGR0 + i * 4) & EXTI_CFGR0_DBCNT_M);
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
    unsigned long ulBase, ulShift, ulType;

    //
    // Check the argument.
    //
    xASSERT(((ulPinConfig >> 12) & 0xf) <= 2 );

    //
    // Extract the base address index from the input value.
    //

    ulBase = g_pulIPRSTRegs[(ulPinConfig >> 12) & 0xf];


    //
    // Extract the shift from the input value.
    //
    ulShift = (ulPinConfig >> 8) & 0xf;
    ulType = ulPinConfig & 0xf;
    
    //
    // Write the requested pin muxing value for this GPIO pin.
    //
    xHWREG(GPIO_AFIO_BASE + ulBase) &= ~(3 << (ulShift * 2) );
    xHWREG(GPIO_AFIO_BASE + ulBase) |= (ulType  << (ulShift * 2));

}

//*****************************************************************************
//
//! \brief Initialize the multi-function pin's specified fucntion.
//!
//! \param 
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//!
//! Initialize the multi-function pin's of the specified function.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinFunctionSet(unsigned long ulFunction, unsigned long ulPort, 
                   unsigned long ulPins)
{
  
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    xASSERT((ulFunction == GPIO_FUNCTION_SPI) ||
            (ulFunction == GPIO_FUNCTION_GPIO) ||
            (ulFunction == GPIO_FUNCTION_ADC) ||
            (ulFunction == GPIO_FUNCTION_ACMP) ||
            (ulFunction == GPIO_FUNCTION_I2C) ||
            (ulFunction == GPIO_FUNCTION_PWM) ||
            (ulFunction == GPIO_FUNCTION_TIM) ||
            (ulFunction == GPIO_FUNCTION_UART) ||
            (ulFunction == GPIO_FUNCTION_GPIO)
           );

    //
    // Initialize the multi-function pin's of the specified function.
    //
    switch(ulPort)
    {
        case GPIO_PORTA_BASE:
        {
            if (ulFunction == GPIO_FUNCTION_GPIO)
            {
                if((ulPins & GPIO_PIN_0))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT0_S);
                }
                if((ulPins & GPIO_PIN_1))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT1_S);
                }
                if((ulPins & GPIO_PIN_2))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT2_S);
                }
                if((ulPins & GPIO_PIN_3))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT3_S);
                }
                if((ulPins & GPIO_PIN_4))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT4_S);
                }
                if((ulPins & GPIO_PIN_5))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT5_S);
                }
                if((ulPins & GPIO_PIN_6))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT6_S);
                }
                if((ulPins & GPIO_PIN_7))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT7_S);
                }
                if((ulPins & GPIO_PIN_8))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT8_S);
                }
                if((ulPins & GPIO_PIN_9))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT9_S);
                }
                if((ulPins & GPIO_PIN_10))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT10_S);
                }
                if((ulPins & GPIO_PIN_11))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT11_S);
                } 
                if((ulPins & GPIO_PIN_12))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT12_S);
                }
                if ((ulPins & GPIO_PIN_13))
                {
                    //
                    // Clear the corresponding bits first
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT13_S);
                    
                    //
                    // Set the corresponding bits
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) |= 
                      (AFIO_GPACFGR_FUN1 << AFIO_GPACFGR_BIT13_S);                  
                }
                if((ulPins & GPIO_PIN_14))
                {
                    //
                    // Clear the corresponding bits first
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT14_S);
                    
                    //
                    // Set the corresponding bits
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) |= 
                      (AFIO_GPACFGR_FUN1 << AFIO_GPACFGR_BIT14_S);
                }
                if((ulPins & GPIO_PIN_15))
                {
                    //
                    // Clear the corresponding bits first
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) &= 
                      ~(AFIO_GPACFGR_FUN3 << AFIO_GPACFGR_BIT15_S);
                    
                    //
                    // Set the corresponding bits
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) |= 
                      (AFIO_GPACFGR_FUN1 << AFIO_GPACFGR_BIT15_S);  
                }       
            }
        }break;

        case GPIO_PORTB_BASE:
        {        
            if (ulFunction == GPIO_FUNCTION_GPIO)
            {
                if((ulPins & GPIO_PIN_0))
                {
                    //
                    // Clear the corresponding bits first
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT0_S);
                    
                    //
                    // Set the corresponding bits
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) |= 
                      (AFIO_GPBCFGR_FUN1 << AFIO_GPBCFGR_BIT0_S);  
                }
                if((ulPins & GPIO_PIN_1))
                {
                    //
                    // Clear the corresponding bits first
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT1_S);
                    
                    //
                    // Set the corresponding bits
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) |= 
                      (AFIO_GPBCFGR_FUN1 << AFIO_GPBCFGR_BIT1_S);  
                }
                if((ulPins & GPIO_PIN_2))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT2_S);
                }
                if((ulPins & GPIO_PIN_3))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT3_S);
                }
                if((ulPins & GPIO_PIN_4))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT4_S);
                }
                if((ulPins & GPIO_PIN_5))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT5_S);
                }
                if((ulPins & GPIO_PIN_6))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT6_S);
                }
                if((ulPins & GPIO_PIN_7))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT7_S);
                }
                if((ulPins & GPIO_PIN_8))
                {
                    //
                    // Clear the corresponding bits first
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT8_S);
                    
                    //
                    // Set the corresponding bits
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) |= 
                      (AFIO_GPBCFGR_FUN1 << AFIO_GPBCFGR_BIT8_S);  
                }
                if((ulPins & GPIO_PIN_9))
                {
                    //
                    // Clear the corresponding bits first
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT9_S);
                    
                    //
                    // Set the corresponding bits
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) |= 
                      (AFIO_GPBCFGR_FUN1 << AFIO_GPBCFGR_BIT9_S);  
                }
                if((ulPins & GPIO_PIN_10))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT10_S);
                }
                if((ulPins & GPIO_PIN_11))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT11_S);
                } 
                if((ulPins & GPIO_PIN_12))
                {
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT12_S);
                }
                if ((ulPins & GPIO_PIN_13))
                {
                    //
                    // Clear the corresponding bits first
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT13_S);
                    
                    //
                    // Set the corresponding bits
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) |= 
                      (AFIO_GPBCFGR_FUN1 << AFIO_GPBCFGR_BIT13_S);                  
                }
                if((ulPins & GPIO_PIN_14))
                {
                    //
                    // Clear the corresponding bits first
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT14_S);
                    
                    //
                    // Set the corresponding bits
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) |= 
                      (AFIO_GPACFGR_FUN1 << AFIO_GPACFGR_BIT14_S);
                }
                if((ulPins & GPIO_PIN_15))
                {
                    //
                    // Clear the corresponding bits first
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) &= 
                      ~(AFIO_GPBCFGR_FUN3 << AFIO_GPBCFGR_BIT15_S);
                    
                    //
                    // Set the corresponding bits
                    //
                    xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) |= 
                      (AFIO_GPBCFGR_FUN1 << AFIO_GPBCFGR_BIT15_S);  
                }       
            }
        }break;
    }
}

