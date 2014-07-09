//*****************************************************************************
//
//! \file xgpio.c
//! \brief Driver for the GPIO controller
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
#include "xhw_gpio.h"
#include "xhw_sysctl.h"


int test0,test1;

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
static const unsigned long g_pulGPIOMFPRegs[] =
{
	GCR_GPAMFPL,
	GCR_GPAMFPH,
	GCR_GPBMFPL,
	GCR_GPBMFPH,
	GCR_GPCMFPL,
	GCR_GPCMFPH,
	GCR_GPDMFPL,
	GCR_GPDMFPH,
	GCR_GPEMFPL,
	GCR_GPEMFPH,
	GCR_GPFMFPL,
	GCR_GPFMFPH,
	GCR_GPGMFPL,
	GCR_GPGMFPH,
	GCR_GPHMFPL,
	GCR_GPHMFPH,
	GCR_GPIMFPL,
	GCR_GPIMFPH
};
#define GPIO_MFP_REG_GET(a)     ((a >> 12) & 0x1F)
#define GPIO_PIN_SHIFT_GET(a)   ((a >> 8) & 0xF)
#define GPIO_MUT_VALUE_GET(a)   ((a) & 0xF)
#define GPIO_MFP_BIT_MASK       0x0000000F


#define GPIO_BIT_DOUT(x,y)      ((x) + (0x200) + 0x4 * y)

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
           (ulPort == GPIOF_BASE) ||
           (ulPort == GPIOE_BASE) ||
           (ulPort == GPIOG_BASE) ||
           (ulPort == GPIOH_BASE) ||
           (ulPort == GPIOI_BASE) ||
           (ulPort == GPIOD_BASE));
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
void GPA_IRQHandler(void)
{
    unsigned long ulGpaStatus;
    unsigned long i;

    //
    // Keep the interrupt source
    //
    ulGpaStatus = xHWREG(GPIOA_BASE+GPIO_ISRC);

    //
    // Clear the interrupt
    //
    xHWREG(GPIOA_BASE+GPIO_ISRC) = ulGpaStatus;

    //
    // Call the callback function of GPIOAB interrupt
    //
    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xFFFF0000) ==
           ((GPIOA_BASE & 0x0000FFFF) << 16))
        {
            if((g_psGPIOPinIntAssignTable[i].ulpinID & 0x0000FFFF &
                ulGpaStatus))
            {
                if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
                {
                    g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback
                    (0,0,0,0);
                }
            }
        }
    }
}

//*****************************************************************************
//
//! \internal
//! \brief GPIO B  ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void GPB_IRQHandler(void)
{
    unsigned long ulGpbStatus;
    unsigned long i;

    //
    // Keep the interrupt source
    //
    ulGpbStatus = xHWREG(GPIOB_BASE+GPIO_ISRC);

    //
    // Clear the interrupt
    //
    xHWREG(GPIOB_BASE+GPIO_ISRC) = ulGpbStatus;

    //
    // Call the callback function of GPIOAB interrupt
    //
    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xFFFF0000) ==
           ((GPIOB_BASE & 0x0000FFFF) << 16))
        {
            if((g_psGPIOPinIntAssignTable[i].ulpinID & 0x0000FFFF &
            	ulGpbStatus))
            {
                if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
                {
                    g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback
                    (0,0,0,0);
                }
            }
        }
    }
}


//*****************************************************************************
//
//! \internal
//! \brief GPIO C  ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void GPC_IRQHandler(void)
{
    unsigned long ulGpcStatus;
    unsigned long i;

    //
    // Keep the interrupt source
    //
    ulGpcStatus = xHWREG(GPIOC_BASE+GPIO_ISRC);

    //
    // Clear the interrupt
    //
    xHWREG(GPIOC_BASE+GPIO_ISRC) = ulGpcStatus;

    //
    // Call the callback function of GPIOAB interrupt
    //
    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xFFFF0000) ==
           ((GPIOC_BASE & 0x0000FFFF) << 16))
        {
            if((g_psGPIOPinIntAssignTable[i].ulpinID & 0x0000FFFF &
            		ulGpcStatus))
            {
                if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
                {
                    g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback
                    (0,0,0,0);
                }
            }
        }
    }
}


//*****************************************************************************
//
//! \internal
//! \brief GPIO D  ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void GPD_IRQHandler(void)
{
    unsigned long ulGpdStatus;
    unsigned long i;

    //
    // Keep the interrupt source
    //
    ulGpdStatus = xHWREG(GPIOD_BASE+GPIO_ISRC);

    //
    // Clear the interrupt
    //
    xHWREG(GPIOD_BASE+GPIO_ISRC) = ulGpdStatus;

    //
    // Call the callback function of GPIOAB interrupt
    //
    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xFFFF0000) ==
           ((GPIOD_BASE & 0x0000FFFF) << 16))
        {
            if((g_psGPIOPinIntAssignTable[i].ulpinID & 0x0000FFFF &
            		ulGpdStatus))
            {
                if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
                {
                    g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback
                    (0,0,0,0);
                }
            }
        }
    }
}

//*****************************************************************************
//
//! \internal
//! \brief GPIO E  ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void GPE_IRQHandler(void)
{
    unsigned long ulGPIOStatus;
    unsigned long i;

    //
    // Keep the interrupt source
    //
    ulGPIOStatus = xHWREG(GPIOE_BASE+GPIO_ISRC);

    //
    // Clear the interrupt
    //
    xHWREG(GPIOE_BASE+GPIO_ISRC) = ulGPIOStatus;

    //
    // Call the callback function of GPIOAB interrupt
    //
    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xFFFF0000) ==
           ((GPIOE_BASE & 0x0000FFFF) << 16))
        {
            if((g_psGPIOPinIntAssignTable[i].ulpinID & 0x0000FFFF &
            	ulGPIOStatus))
            {
                if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
                {
                    g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback
                    (0,0,0,0);
                }
            }
        }
    }
}

//*****************************************************************************
//
//! \internal
//! \brief GPIO F  ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void GPF_IRQHandler(void)
{
    unsigned long ulGPIOStatus;
    unsigned long i;

    //
    // Keep the interrupt source
    //
    ulGPIOStatus = xHWREG(GPIOF_BASE+GPIO_ISRC);

    //
    // Clear the interrupt
    //
    xHWREG(GPIOF_BASE+GPIO_ISRC) = ulGPIOStatus;

    //
    // Call the callback function of GPIOAB interrupt
    //
    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xFFFF0000) ==
           ((GPIOF_BASE & 0x0000FFFF) << 16))
        {
            if((g_psGPIOPinIntAssignTable[i].ulpinID & 0x0000FFFF &
            	ulGPIOStatus))
            {
                if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
                {
                    g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback
                    (0,0,0,0);
                }
            }
        }
    }
}

//*****************************************************************************
//
//! \internal
//! \brief GPIO G  ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void GPG_IRQHandler(void)
{
    unsigned long ulGPIOStatus;
    unsigned long i;

    //
    // Keep the interrupt source
    //
    ulGPIOStatus = xHWREG(GPIOG_BASE+GPIO_ISRC);

    //
    // Clear the interrupt
    //
    xHWREG(GPIOG_BASE+GPIO_ISRC) = ulGPIOStatus;

    //
    // Call the callback function of GPIOAB interrupt
    //
    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xFFFF0000) ==
           ((GPIOG_BASE & 0x0000FFFF) << 16))
        {
            if((g_psGPIOPinIntAssignTable[i].ulpinID & 0x0000FFFF &
            	ulGPIOStatus))
            {
                if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
                {
                    g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback
                    (0,0,0,0);
                }
            }
        }
    }
}

//*****************************************************************************
//
//! \internal
//! \brief GPIO H  ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void GPH_IRQHandler(void)
{
    unsigned long ulGPIOStatus;
    unsigned long i;

    //
    // Keep the interrupt source
    //
    ulGPIOStatus = xHWREG(GPIOH_BASE+GPIO_ISRC);

    //
    // Clear the interrupt
    //
    xHWREG(GPIOH_BASE+GPIO_ISRC) = ulGPIOStatus;

    //
    // Call the callback function of GPIOAB interrupt
    //
    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xFFFF0000) ==
           ((GPIOH_BASE & 0x0000FFFF) << 16))
        {
            if((g_psGPIOPinIntAssignTable[i].ulpinID & 0x0000FFFF &
            	ulGPIOStatus))
            {
                if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
                {
                    g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback
                    (0,0,0,0);
                }
            }
        }
    }
}

//*****************************************************************************
//
//! \internal
//! \brief GPIO I  ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void GPI_IRQHandler(void)
{
    unsigned long ulGPIOStatus;
    unsigned long i;

    //
    // Keep the interrupt source
    //
    ulGPIOStatus = xHWREG(GPIOI_BASE+GPIO_ISRC);

    //
    // Clear the interrupt
    //
    xHWREG(GPIOI_BASE+GPIO_ISRC) = ulGPIOStatus;

    //
    // Call the callback function of GPIOAB interrupt
    //
    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID & 0xFFFF0000) ==
           ((GPIOI_BASE & 0x0000FFFF) << 16))
        {
            if((g_psGPIOPinIntAssignTable[i].ulpinID & 0x0000FFFF &
            	ulGPIOStatus))
            {
                if(g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback != 0)
                {
                    g_psGPIOPinIntAssignTable[i].pfnGPIOPinHandlerCallback
                    (0,0,0,0);
                }
            }
        }
    }
}

//*****************************************************************************
//
//! \internal
//! \brief External INT0(PortA 0) ISR.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EINT0_IntHandler(void)
{
    unsigned long i;
    //
    // For PA0, clear the INT flag
    //
    xHWREG(GPIOA_BASE+GPIO_ISRC) |= GPIO_PIN_0;

    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID) ==
           (((GPIOA_BASE & 0x0000FFFF) << 16) | GPIO_PIN_0))
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
//! \brief External INT1(PortB 0) ISR .
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EINT1_IntHandler(void)
{
    unsigned long i;

    //
    // For PB0, clear the INT flag
    //
    xHWREG(GPIOB_BASE+GPIO_ISRC) |= GPIO_PIN_0;

    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID) ==
           (((GPIOB_BASE & 0x0000FFFF) << 16) | GPIO_PIN_0))
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
//! \brief External INT2(PortC 0) ISR .
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EINT2_IntHandler(void)
{
    unsigned long i;

    //
    // For PC0, clear the INT flag
    //
    xHWREG(GPIOC_BASE+GPIO_ISRC) |= GPIO_PIN_0;

    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID) ==
           (((GPIOC_BASE & 0x0000FFFF) << 16) | GPIO_PIN_0))
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
//! \brief External INT3(PortD 0) ISR .
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EINT3_IntHandler(void)
{
    unsigned long i;

    //
    // For PD0, clear the INT flag
    //
    xHWREG(GPIOD_BASE+GPIO_ISRC) |= GPIO_PIN_0;

    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID) ==
           (((GPIOD_BASE & 0x0000FFFF) << 16) | GPIO_PIN_0))
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
//! \brief External INT4(PortE 0) ISR .
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EINT4_IntHandler(void)
{
    unsigned long i;

    //
    // For PE0, clear the INT flag
    //
    xHWREG(GPIOE_BASE+GPIO_ISRC) |= GPIO_PIN_0;

    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID) ==
           (((GPIOE_BASE & 0x0000FFFF) << 16) | GPIO_PIN_0))
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
//! \brief External INT5(PortF 0) ISR .
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EINT5_IntHandler(void)
{
    unsigned long i;

    //
    // For PF0, clear the INT flag
    //
    xHWREG(GPIOF_BASE+GPIO_ISRC) |= GPIO_PIN_0;

    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID) ==
           (((GPIOF_BASE & 0x0000FFFF) << 16) | GPIO_PIN_0))
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
//! \brief External INT6(PortG 0) ISR .
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EINT6_IntHandler(void)
{
    unsigned long i;

    //
    // For PF0, clear the INT flag
    //
    xHWREG(GPIOG_BASE+GPIO_ISRC) |= GPIO_PIN_0;

    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID) ==
           (((GPIOG_BASE & 0x0000FFFF) << 16) | GPIO_PIN_0))
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
//! \brief External INT7(PortH 0) ISR .
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void EINT7_IntHandler(void)
{
    unsigned long i;

    //
    // For PH0, clear the INT flag
    //
    xHWREG(GPIOH_BASE+GPIO_ISRC) |= GPIO_PIN_0;

    for(i=0; i<xGPIO_INT_NUMBER; i++)
    {
        if((g_psGPIOPinIntAssignTable[i].ulpinID) ==
           (((GPIOH_BASE & 0x0000FFFF) << 16) | GPIO_PIN_0))
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
//! \brief Get the GPIO Peripheral Id from a short Pin.
//!
//! \param eShortPin is the base address of the GPIO port
//!
//! \note For NUC122,all GPIO port use the some Peripheral clock.
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

    return SYSCTL_PERIPH_GPIO;
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
//! - \b xGPIO_DIR_MODE_QB
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
           (ulPinIO == xGPIO_DIR_MODE_HW) || (ulPinIO == xGPIO_DIR_MODE_OD)  ||
           (ulPinIO == xGPIO_DIR_MODE_QB));

    //
    // Set the pin direction and mode.
    //
    for(ulBit=0; ulBit<16; ulBit++)
    {
        if(ulPins & (1 << ulBit))
        {
            GPIODirModeSet(ulPort, ulBit, ulPinIO);
        }

    }
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
//! - \b GPIO_DIR_MODE_OD
//! - \b GPIO_DIR_MODE_QB
//! - \b GPIO_DIR_MODE_HW
//!
//! where \b GPIO_DIR_MODE_IN specifies that the pin will be programmed as
//! a software controlled input, \b GPIO_DIR_MODE_OUT specifies that the pin
//! will be programmed as a software controlled output, and
//! \b GPIO_DIR_MODE_HW specifies that the pin will be placed under
//! hardware control.\b GPIO_DIR_MODE_OD specifies that the pin will be
//! programmed as a Open-Drain.\b GPIO_DIR_MODE_QB specifies that the pin
//! will be programmed as Quasi-bidirectional
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
    xASSERT((ulPinIO == GPIO_DIR_MODE_IN) || (ulPinIO == GPIO_DIR_MODE_OUT) ||
           (ulPinIO == GPIO_DIR_MODE_HW) || (ulPinIO == GPIO_DIR_MODE_OD)  ||
           (ulPinIO == GPIO_DIR_MODE_QB));

    //
    // Set the pin direction and mode.
    //
    xHWREG(ulPort + GPIO_PMD) = (xHWREG(ulPort + GPIO_PMD) &                    \
                               (~(3 << (ulBit * 2))));

    xHWREG(ulPort + GPIO_PMD) = (xHWREG(ulPort + GPIO_PMD) |                    \
                               ((ulPinIO & GPIO_PMD_PMD0_M) << (ulBit * 2)));
}

void
GPIODigitalInputEnable(unsigned long ulPort, unsigned long ulPins)
{
	xASSERT(GPIOBaseValid(ulPort));
	xHWREG(ulPort + GPIO_OFFD) &= ~(ulPins << 16);
}
void
GPIODigitalInputDisable(unsigned long ulPort, unsigned long ulPins)
{
	xASSERT(GPIOBaseValid(ulPort));
	xHWREG(ulPort + GPIO_OFFD) |= (ulPins << 16);
}
void
GPIOSchmittTrigEnable(unsigned long ulPort, unsigned long ulPins)
{
	xASSERT(GPIOBaseValid(ulPort));

//	xHWREG(GCR_GPAMFP + ((ulPort & 0x1FF) >> 4)) |= (ulPins << 16);
}
void
GPIOSchmittTrigDisable(unsigned long ulPort, unsigned long ulPins)
{
	xASSERT(GPIOBaseValid(ulPort));

//	xHWREG(GCR_GPAMFP + ((ulPort & 0x1FF) >> 4)) &= ~(ulPins << 16);
}
//void
//GPIOStrongDrivingEnable(unsigned long ulPort, unsigned long ulPins)
//{
//	xASSERT(GPIOBaseValid(ulPort));
//
//	xHWREG(GCR_GPAIOCR + ((ulPort & 0x1FF) >> 4)) |= (ulPins);
//}
//void
//GPIOStrongDrivingDisable(unsigned long ulPort, unsigned long ulPins)
//{
//	xASSERT(GPIOBaseValid(ulPort));
//
//	xHWREG(GCR_GPAIOCR + ((ulPort & 0x1FF) >> 4)) &= ~(ulPins);
//}
//long
//GPIOConflictStatusGet(void)
//{
//	return xHWREG(GCR_DFPCSR);
//}

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
    return((xHWREG(ulPort + GPIO_PMD) & (3 << (ulBits * 2))) >> (ulBits * 2));
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

    //
    // Return the pin direction and mode.
    //
    return((xHWREG(ulPort + GPIO_PMD) & (3 << (ulBit * 2))) >> (ulBit * 2));
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
//! - \b GPIO_BOTH_EDGES
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
    xHWREG(ulPort + GPIO_IMD) = ((ulIntType & 0x10) ?
                                (xHWREG(ulPort + GPIO_IMD) | (ulPins)) :
                                (xHWREG(ulPort + GPIO_IMD) & ~(ulPins)));
    xHWREG(ulPort + GPIO_IEN) = ((ulIntType & 2) ?
                                (xHWREG(ulPort + GPIO_IEN) | (ulPins << 16)) :
                                (xHWREG(ulPort + GPIO_IEN) & ~(ulPins << 16)));
    xHWREG(ulPort + GPIO_IEN) = ((ulIntType & 1) ?
                                (xHWREG(ulPort + GPIO_IEN) | ulPins) :
                                (xHWREG(ulPort + GPIO_IEN) & ~(ulPins)));
}

//*****************************************************************************
//
//! \brief Disables interrupts for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
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
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Disable the interrupts.
    //
    xHWREG(ulPort + GPIO_IEN) &= ~(ulPins);
    xHWREG(ulPort + GPIO_IEN) &= ~(ulPins << 16);
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
//! \param bMasked specifies whether masked or raw interrupt status is
//! returned.
//!
//! \return Returns a bit-packed byte, where each bit that is set identifies
//! an active masked or raw interrupt, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//! Bits 31:16 should be ignored.
//
//*****************************************************************************
unsigned long
GPIOPinIntStatus(unsigned long ulPort)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Return the interrupt status.
    //
    return(xHWREG(ulPort + GPIO_ISRC));

}

//*****************************************************************************
//
//! \brief Clears the interrupt for the specified pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//!
//! Clears the interrupt for the specified pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note Because there is a write buffer in the Cortex-M0 processor, it may
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
GPIOPinIntClear(unsigned long ulPort, unsigned long ulPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Clear the interrupts.
    //
    xHWREG(ulPort + GPIO_ISRC) |= ulPins;
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
    return(xHWREG(ulPort +GPIO_PIN ) & (ulPins));
}

long
GPIOBitRead(unsigned long ulPort, unsigned long ulBit)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Return the pin value(s).
    //
    return xHWREG(GPIO_BIT_DOUT(ulPort, ulBit));
}
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
    return xHWREG(ulPort +GPIO_PIN );
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
    xHWREG(ulPort + GPIO_DOUT) = ((ucVal & 1) ?
                                (xHWREG(ulPort + GPIO_DOUT) | ulPins) :
                                (xHWREG(ulPort + GPIO_DOUT) & ~(ulPins)));
}

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
    xHWREG(ulPort + GPIO_DOUT) = ulVal;
}

void
GPIOBitWrite(unsigned long ulPort, unsigned long ulBit, unsigned char ucVal)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));
    xHWREG(GPIO_BIT_DOUT(ulPort, ulBit)) = ucVal;
}

//*****************************************************************************
//
//! \brief Enable the debounce function of the specified GPIO pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//!
//! Enable the corresponding bit debounce function to pin(s) specified by
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
GPIOPinDebounceEnable(unsigned long ulPort, unsigned long ulPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Write the pins.
    //
    xHWREG(ulPort + GPIO_DBEN) |=  ulPins;
}


//*****************************************************************************
//
//! \brief Disable the debounce function of the specified GPIO pin(s).
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ulPins is the bit-packed representation of the pin(s).
//!
//! Disable the corresponding bit debounce function to pin(s) specified by
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
GPIOPinDebounceDisable(unsigned long ulPort, unsigned long ulPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Disable the pins Debounce.
    //
    xHWREG(ulPort + GPIO_DBEN) &=  ~ulPins;
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
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Set the pins mask.
    //
    xHWREG(ulPort + GPIO_DMASK) |=  ulPins;
}

//*****************************************************************************
//
//! \brief Set the De-bounce sampling cycle.
//!
//! \param ulClockSource is the De-bounce sampling clock source.
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
GPIODebounceTimeSet(unsigned long ulClockSource, unsigned long ulDebounceClk)
{
    //
    // Check the arguments.
    //
    xASSERT((ulClockSource == GPIO_DBCLKSRC_HCLK) ||
            (ulClockSource == GPIO_DBCLKSRC_10K));
    xASSERT(ulDebounceClk<=15);

    //
    // Write the pins.
    //
    xHWREG(GPIOA_BASE + GPIO_DBNCECON) =  ((ulClockSource & 1) ?
                              (xHWREG(GPIOA_BASE + GPIO_DBNCECON) | GPIO_DBNCECON_DBCLKSRC) :
                              (xHWREG(GPIOA_BASE + GPIO_DBNCECON) & ~(GPIO_DBNCECON_DBCLKSRC)));
    xHWREG(GPIOA_BASE + GPIO_DBNCECON) &= ~GPIO_DBNCECON_DBCLKSEL_M;
    xHWREG(GPIOA_BASE + GPIO_DBNCECON) |= ulDebounceClk;
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
GPIODebounceTimeGet(void)
{
    //
    // Get the De-bounce sampling cycle
    //
    return (xHWREG(GPIOA_BASE + GPIO_DBNCECON) &  GPIO_DBNCECON_DBCLKSEL_M);
}

//*****************************************************************************
//
//! \brief Get current GPIO port mask setting.
//!
//! \param ulPort is the base address of the GPIO port.
//!
//! \return The value of Specified GPIO port mask register.
//
//*****************************************************************************
long
GPIOPortMaskGet(unsigned long ulPort)
{
    //
    // Get current GPIO port mask setting
    //
    return (xHWREG(ulPort + GPIO_DMASK) & GPIO_DBEN_DBEN_M);
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
    return(xHWREG(ulPort + GPIO_DOUT));

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
GPIOPinConfigure(unsigned long ulPort, unsigned long ulPins, unsigned long ulPinConfig)
{

    //
    // Check the argument.
    //
	xASSERT(GPIOBaseValid(ulPort));
    xASSERT(((ulPinConfig >> 12) & 0x1F) <= 17 );

    //
    // Enable the corresponding Alternative Multiple Function Pin or not.
    //
    if(ulPinConfig & 0x10)
    {
    	xHWREG(ulPort + GPIO_SLEWCTL) |= ulPins;
    }

    xHWREG(g_pulGPIOMFPRegs[GPIO_MFP_REG_GET(ulPinConfig)]) &=
    		~(GPIO_MFP_BIT_MASK << GPIO_PIN_SHIFT_GET(ulPinConfig));

    xHWREG(g_pulGPIOMFPRegs[GPIO_MFP_REG_GET(ulPinConfig)]) |=
    		(GPIO_MUT_VALUE_GET(ulPinConfig) << GPIO_PIN_SHIFT_GET(ulPinConfig));

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
//! - \b xGPIO_STRENGTH_2MA
//! - \b xGPIO_STRENGTH_4MA
//! - \b xGPIO_STRENGTH_8MA
//!
//! where \b xGPIO_STRENGTH_xMA specifies either 2, 4, or 8 mA output drive
//! strength, and \b xGPIO_OUT_STRENGTH_8MA_SC specifies 8 mA output drive with
//! slew control.
//!
//! The parameter \e ulPinType can be one of the following values:
//!
//! - \b xGPIO_PIN_TYPE_STD
//! - \b xGPIO_PIN_TYPE_STD_WPU
//! - \b xGPIO_PIN_TYPE_STD_WPD
//! - \b xGPIO_PIN_TYPE_OD
//! - \b xGPIO_PIN_TYPE_OD_WPU
//! - \b xGPIO_PIN_TYPE_OD_WPD
//! - \b xGPIO_PIN_TYPE_ANALOG
//!
//! where \b xGPIO_PIN_TYPE_STD* specifies a push-pull pin, \b xGPIO_PIN_TYPE_OD*
//! specifies an open-drain pin, \b *_WPU specifies a weak pull-up, \b *_WPD
//! specifies a weak pull-down, and \b xGPIO_PIN_TYPE_ANALOG specifies an
//! analog input (for the comparators).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
void xGPIOPadConfigSet(unsigned long ulPort, unsigned long ulPins,
		               unsigned long ulStrength, unsigned long ulPadType)
{
	return;
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
//! \e pulPinType correspond to the values used in xGPIOPadConfigSet().  This
//! function also works for pin(s) configured as input pin(s); however, the
//! only meaningful data returned is whether the pin is terminated with a
//! pull-up or down resistor.
//!
//! \return None.
//
//*****************************************************************************
void xGPIOPadConfigGet(unsigned long ulPort, unsigned long ulPins,
		               unsigned long *ulStrength, unsigned long *ulPadType)
{
	return;
}


//*****************************************************************************
//
//! \brief  Register user's gpio interrupt function.
//!
//! \param  [in] ulPort is the base address of the GPIO port.
//! \param  [in] ulPin is the bit-packed representation of the pin.
//! \param  [in] pfnCallback is the callback function.
//!
//! \return None.
//
//*****************************************************************************
void xGPIOPinIntCallbackInit(unsigned long ulPort, unsigned long ulPin,
                             xtEventCallback xtPortCallback)
{
	GPIOPinIntCallbackInit(ulPort, ulPin, xtPortCallback);
}

//*****************************************************************************
//
//! \brief  Set the interrupt type and Enable interrupt for the specified pin(s).
//!         This function sets up the various interrupt trigger mechanisms for the
//!         specified pin(s) on the selected GPIO port.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//! \param  [in] ulIntType specifies the type of interrupt trigger mechanism.
//!
//! \return None.
//!
//! \note   In order to avoid any spurious interrupts, the user must ensure that
//!         the GPIO inputs remain stable for the duration of this function.
//
//*****************************************************************************
void xGPIOPinIntEnable(unsigned long ulPort, unsigned long ulPins,
                       unsigned long ulIntType)
{
	GPIOPinIntEnable(ulPort, ulPins, ulIntType);
}


//*****************************************************************************
//
//! \brief  Disables interrupts for the specified pin(s).
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//!
//! \return None.
//
//*****************************************************************************
void xGPIOPinIntDisable(unsigned long ulPort, unsigned long ulPins)
{
	GPIOPinIntDisable(ulPort, ulPins);
}


//*****************************************************************************
//
//! \brief  Clear the interrupt for the specified pin(s).
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//!
//! \return None.
//!
//! \note   Because there is a write buffer in the Cortex-M0 processor, it may
//!         take several clock cycles before the interrupt source is actually
//!         cleared. Therefore, it is recommended that the interrupt source
//!         be cleared early in the interrupt handler (as opposed to the very
//!         last action) to avoid returning from the interrupt handler before
//!         the interrupt source i actually cleared.  Failure to do so may
//!         result in the interrupt handler being immediately reentered (because
//!         the interrupt controller still see the interrupt source asserted).
//
//*****************************************************************************
void xGPIOPinIntClear(unsigned long ulPort, unsigned long ulPins)
{
	GPIOPinIntClear(ulPort, ulPins);
}


//*****************************************************************************
//
//! \brief  Reads the values present of the specified pin(s).
//!         The values at the specified pin(s) are read, as specified by \e ucPins.
//!         Values are returned for both input and output pin(s), and the value
//!         for pin(s) that are not specified by \e ucPins are set to 0.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//!
//! \return Returns a bit-packed byte, where each bit that is set identifie
//!         an active masked or raw interrupt, and where bit 0 of the byte
//!         represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and
//!         so on.
//
//*****************************************************************************
inline unsigned long xGPIOPinRead(unsigned long ulPort, unsigned long ulPins)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Return the pin value(s).
    //
    return (xHWREG(ulPort +GPIO_PIN ) & (ulPins)) ? 1:0;
}


//*****************************************************************************
//
//! \brief Write a value to the specified pin(s).
//!        Write the corresponding bit values to the output pin(s) specified by
//!        \e ucPins.  Writing to a pin configured as an input pin has no effect.
//!
//! \param [in] ulPort is the base address of the GPIO port
//! \param [in] ulPins is the bit-packed representation of the pin(s).
//! \param [in] ucVal is the value to write to the pin(s), 0 or 1.
//!
//! \return None.
//
//*****************************************************************************
inline void xGPIOPinWrite(unsigned long ulPort, unsigned long ulPins,
                   unsigned long ucVal)
{
    //
    // Check the arguments.
    //
    xASSERT(GPIOBaseValid(ulPort));

    //
    // Write the pins.
    //
    xHWREG(ulPort + GPIO_DOUT) = ((ucVal & 1) ?
                                (xHWREG(ulPort + GPIO_DOUT) | ulPins) :
                                (xHWREG(ulPort + GPIO_DOUT) & ~(ulPins)));
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
inline unsigned long xGPIOPortRead(unsigned long ulPort)
{
	return xHWREG(ulPort + GPIO_DOUT);
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
inline void xGPIOPortWrite(unsigned long ulPort, unsigned long ulVal)
{
	xHWREG(ulPort + GPIO_DOUT) = ulVal;
}


//*****************************************************************************
//
//! \brief  Get interrupt status for the specified GPIO port.
//!
//! \param  [in] ulPort is the base address of the GPIO port.
//!
//! \return Returns a bit-packed byte, where each bit that is set identifie
//!         an active masked or raw interrupt, and where bit 0 of the byte
//!         represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and
//!         so on.
//
//*****************************************************************************
unsigned long xGPIOPinIntStatus(unsigned long ulPort)
{
	return GPIOPinIntStatus(ulPort);
}
