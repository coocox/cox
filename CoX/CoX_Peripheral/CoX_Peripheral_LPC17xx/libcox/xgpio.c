#include "xhw_types.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"

//*****************************************************************************
//
// An array is Watchdog callback function point
//
//*****************************************************************************
static xtEventCallback g_psGPIOPinIntAssignTable[64] =
{
    0,
};

//*****************************************************************************
//
//! \brief  GPIO interrupt handler.
//!         This function is the GPIO interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//!
//! \return None.
//!
//! \note   EINT3 channel is shared with GPIO interrupts.
//
//*****************************************************************************
void EINT3IntHandler(void)
{
    unsigned long i      = 0;

    //Find and call any interrupt function.
    for(i = 0; i < 64; i++)
    {
        if(g_psGPIOPinIntAssignTable[i])
        {
            g_psGPIOPinIntAssignTable[i](0,0,0,0);
        }
    }
}

//*****************************************************************************
//
//! \internal
//! \brief  This function convert gpio ID to the number of the gpio.
//!         For example:
//!
//!         GPIO_PIN_1 --> 1
//!         GPIO_PIN_5 --> 5
//!
//! \param  [in] ulPin is the gpio id, which can be one of the following vaule:
//!              - \ref GPIO_PIN_0
//!              - \ref GPIO_PIN_1
//!              - ...
//!              - \ref GPIO_PIN_31
//!
//! \return The number of GPIO.
//! \note   If call this function with wrong parameter, it will exit with -1.
//!
//
//*****************************************************************************
static unsigned long PinIDToPos(unsigned long ulPin)
{
    unsigned long i      = 0;
    unsigned long ulFlag = 0;

    for(i = 0; i < 32; i++)
    {
        ulFlag = 0x01 << i;
        if(ulPin & ulFlag)
        {
            return (i);
        }
    }

    return (-1);
}

//*****************************************************************************
//
//! \brief  Set the direction and mode of the specified pin(s).
//!         This function will set the specified pin(s) on the selected GPIO
//!         port as either an input or output under software control, or it
//!         will set the pin to be under hardware control.
//!
//! \param  [in] ulPort is the base address of the GPIO port, this value can
//!              be one of the following value:
//!              - \ref GPIOA_BASE
//!              - \ref GPIOB_BASE
//!              - ...
//!              More Information, please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//!              elemnt can be one of the following value:
//!              - \ref GPIO_PIN0
//!              - \ref GPIO_PIN1
//!              - \ref ...
//!              More Information, please refer to \ref xGPIO_General_Pin_IDs.
//!
//! \param  [in] ulPinIO is the pin direction and/or mode.
//!              This parameter can be one of the following value:
//!              Where \ref xGPIO_DIR_MODE_IN specifies that the pin will be
//!              programmed a software controlled input, \ref xGPIO_DIR_MODE_OUT
//!              specifies that the pin will be programmed as a software
//!              controlled output, and \ref xGPIO_DIR_MODE_HW specifies that
//!              the pin will be placed under hardware control.
//!
//! \return None.
//!
//! \note   \ref xGPIOPadConfigSet() must also be used to configure the corresponding
//!         pad(s) in order for them to propagate the signal to/from the GPIO.
//
//*****************************************************************************
void xGPIODirModeSet(unsigned long ulPort, unsigned long ulPins, unsigned long ulPinIO)
{
    unsigned long i = 0;

    for(i = 0; i < 32; i++)
    {
        if(ulPins & (0x01 << i))
        {
            if(0 != ulPinIO)
            {
                GPIOPinModeCfg(ulPort, 0x01<<i, ulPinIO);
            }
        }
    }
}

//*****************************************************************************
//
//! \brief  Get the GPIO port from a Pin.
//!
//! \param  [in] eShortPin is the base address of the GPIO port
//!
//! \return GPIO port code, which is one of the following value:
//!             - \ref xSYSCTL_PERIPH_GPIOC
//!             - \ref xSYSCTL_PERIPH_I2C1
//!             -      ...
//!             - \ref xSYSCTL_PERIPH_TIMER2
//!             - \ref xSYSCTL_PERIPH_TIMER3
//!
//!         which can be used in those functions:
//!             - \ref xSysCtlPeripheralEnable
//!             - \ref xSysCtlPeripheralDisable
//!             - \ref xSysCtlPeripheralReset
//
//*****************************************************************************
unsigned long GPIOPinToPeripheralId(unsigned long ulPort, unsigned long ulPin)
{

    switch (ulPort)
    {
        case GPIOA_BASE:
            {
                return (SYSCTL_PERIPH_GPIOA);
                break;
            }
        case GPIOB_BASE:
            {
                return (SYSCTL_PERIPH_GPIOB);
                break;
            }
        case GPIOC_BASE:
            {
                return (SYSCTL_PERIPH_GPIOC);
                break;
            }
        case GPIOD_BASE:
            {
                return (SYSCTL_PERIPH_GPIOD);
                break;
            }
        case GPIOE_BASE:
            {
                return (SYSCTL_PERIPH_GPIOE);
                break;
            }
    }

    return (0);                      // Error
}

//*****************************************************************************
//
//! \brief  Get the GPIO port from a short Pin.
//!
//! \param  [in] eShortPin is the base address of the GPIO port
//!
//! \return GPIO port address which is used by GPIO API.
//
//*****************************************************************************
unsigned long  GPIOPinToPort(unsigned long ulPort, unsigned long ulPin)
{

    return (ulPort);
}

//*****************************************************************************
//
//! \brief  Get the GPIO pin number from a short Pin.
//!
//! \param  [in] eShortPin is the base address of the GPIO port
//!
//! \return GPIO pin number which is used by GPIO API.
//
//*****************************************************************************
unsigned long  GPIOPinToPin(unsigned long ulPort, unsigned long ulPin)
{

    return (ulPin);
}

//*****************************************************************************
//
//! \brief  Get the direction and mode of a pin.
//!         This function gets the direction and control mode for a specified
//!         pin on the selected GPIO port.  The pin can be configured as either
//!         an input or output under software control, or it can be under
//!         hardware control. The type of control and direction are returned
//!         as an enumerated data type.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPin is the bit-packed representation of the pin.
//!
//! \return Returns one of the enumerated data types
//!         - \ref xGPIO_DIR_MODE_IN
//!         - \ref xGPIO_DIR_MODE_OUT
//!         - \ref xGPIO_DIR_MODE_HW
//!         - \ref xGPIO_DIR_MODE_QB
//!         - \ref xGPIO_DIR_MODE_OD
//
//*****************************************************************************
unsigned long xGPIODirModeGet(unsigned long ulPort, unsigned long ulPin)
{
    //! \todo Finish this function.
    return (0);
}

//*****************************************************************************
//
//! \brief  Register user interrupts callback function  for the GPIO.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPin is the bit-packed representation of the pin.
//!
//! \param  [in] xtPortCallback is user callback for the GPIO.
//!
//! \return None.
//
//*****************************************************************************
void xGPIOPinIntCallbackInit(unsigned long ulPort, unsigned long ulPin,
                                   xtEventCallback xtPortCallback)
{
    unsigned long PinNum = PinIDToPos(ulPin);

    if(GPIOA_BASE == ulPort)
    {
        g_psGPIOPinIntAssignTable[PinNum] = xtPortCallback;
    }
    else if(GPIOC_BASE == ulPort)
    {
        PinNum += 32;
        g_psGPIOPinIntAssignTable[PinNum] = xtPortCallback;
    }
    else           // Error
    {
        while(1);
    }

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
void xGPIOPinIntEnable(unsigned long ulPort, unsigned long ulPins, unsigned long ulIntType)
{
    unsigned long i = 0;

    for(i = 0; i < 32; i++)
    {
        if(ulPins & (0x01 << i))
        {
            GPIOPinIntCfg(ulPort, (0x01 << i), ulIntType);
            GPIOPinIntEnable(ulPort, (0x01 << i));
        }
    }
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
    unsigned long i = 0;

    for(i = 0; i < 32; i++)
    {
        if(ulPins & (0x01 << i))
        {
            GPIOPinIntDisable(ulPort, (0x01 << i));
        }
    }
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
    unsigned long i = 0;

    for(i = 0; i < 32; i++)
    {
        if(ulPins & (0x01 << i))
        {
            GPIOPinIntFlagClear(ulPort, (0x01 << i));
        }
    }
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
unsigned long xGPIOPinRead(unsigned long ulPort, unsigned long ulPins)
{
    xHWREG(ulPort + FIOMASK) = ~ulPins;
    return xHWREG(ulPort + FIOPIN);
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
void xGPIOPinWrite(unsigned long ulPort, unsigned long ulPins,
        unsigned long ulVal)
{
    xHWREG(ulPort + FIOMASK) = ~ulPins;
    xHWREG(ulPort + FIOPIN)  =   ulVal;
}

////////////////////////////////////////////////////////////////////


//*****************************************************************************
//
//! \brief  Configure GPIO function.
//!         This function map gpio to special function.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//! \param  [in] ulCfg is the GPIO configure parameter, which can be one of
//!              the following value;
//!              - \ref GPIO_PA0_PA0
//!              - \ref GPIO_PA0_RD1
//!              - \ref GPIO_PA0_UART3TX
//!              - \ref GPIO_PA0_I2C1SDA
//!              ... and so on, more information, please reference GPIO
//!              alterfunction.
//!
//! \return None.
//
//*****************************************************************************
void GPIOPinFunCfg(unsigned long ulPort, unsigned long ulPin, unsigned long ulCfg)
{
    unsigned long ulRegAddr = 0;
    unsigned long ulTmpReg  = 0;

    switch(ulPort)
    {
        case GPIOA_BASE:               // Port 0
            {
                ulRegAddr = PINSEL0;
                break;
            }
        case GPIOB_BASE:               // Port 1
            {
                ulRegAddr = PINSEL2;
                break;
            }
        case GPIOC_BASE:               // Port 2
            {
                ulRegAddr = PINSEL4;
                break;
            }
        case GPIOD_BASE:               // Port 3
            {
                ulRegAddr = PINSEL6;
                break;
            }
        case GPIOE_BASE:               // Port 4
            {
                ulRegAddr = PINSEL8;
                break;
            }
        default:
            {
                //while(1);            // Error
            }
    }

    ulPin = PinIDToPos(ulPin);
    // Select Pin ID
    if(ulPin >= 16)
    {
        ulPin     -= 16;
        ulRegAddr += 4;
    }

    // Read --> Modify --> WriteBack
    ulTmpReg =  xHWREG(PIN_CON_BASE + ulRegAddr);
    ulTmpReg &= ~(0x03 << (2*ulPin));
    ulTmpReg |= ulCfg;
    xHWREG(PIN_CON_BASE + ulRegAddr) = ulTmpReg;

}

//*****************************************************************************
//
//! \brief  Configure GPIO mode.
//!         This function configure gpio mode, includes open-drain/pull-push/
//!         input/output.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//! \param  [in] ulCfg is the GPIO configure parameter, which can be one of
//!              the following value;
//!              - \ref PIN_MODE_OD_DIS
//!              - \ref PIN_MODE_OD_EN
//!              - \ref PIN_MODE_PULL_UP
//!              - \ref PIN_MODE_REPEATER
//!              - \ref PIN_MODE_NONE
//!              - \ref PIN_MODE_PULL_DOWN
//!              - \ref PIN_MODE_INPUT
//!              - \ref PIN_MODE_OUTPUT
//!
//! \return None.
//
//*****************************************************************************
void GPIOPinModeCfg(unsigned long ulPort, unsigned long ulPin, unsigned long ulCfg)
{
    unsigned long ulRegAddr = 0;
    unsigned long ulTmp     = 0;
    unsigned long ulTmpReg  = 0;
    unsigned long ulTmpMode = 0;

    /******************* Configure Input/Output Mode ****************/
    if(ulCfg & BIT_32_1)                         // Need to configure Input/Output Mode.
    {
        if(ulCfg & BIT_32_0)                     // OutPut Mode.
        {
            xHWREG(ulPort + FIODIR) |= ulPin;
        }
        else                                     // Input Mode
        {
            xHWREG(ulPort + FIODIR) &= ~ulPin;
        }
    }

    /***************** Configure pull-up/pull-down Resister ****************/
    if(ulCfg & BIT_32_4)                         // Need to configure Pull-up/Pull-down
    {
        switch(ulPort)                           //
        {
            case GPIOA_BASE:
                {
                    ulRegAddr = PINMODE0;
                    break;
                }
            case GPIOB_BASE:
                {
                    ulRegAddr = PINMODE2;
                    break;
                }
            case GPIOC_BASE:
                {
                    ulRegAddr = PINMODE4;
                    break;
                }
            case GPIOD_BASE:
                {
                    ulRegAddr = PINMODE6;
                    break;
                }
            case GPIOE_BASE:
                {
                    ulRegAddr = PINMODE8;
                    break;
                }
        }

        ulTmp = PinIDToPos(ulPin);
        if(ulTmp >= 16)
        {
            ulRegAddr += 4;
            ulTmp     -= 16;
        }

        ulTmpReg  = xHWREG(PIN_CON_BASE + ulRegAddr);
        ulTmpReg &= ~((unsigned long)0x03<< (2*ulTmp));
        ulTmpMode = ulCfg & BIT_MASK(32, 3, 2);
        ulTmpMode = (ulTmpMode >> 2) << (2 * ulTmp);
        ulTmpReg |= ulTmpMode;
        xHWREG(PIN_CON_BASE + ulRegAddr)  = ulTmpReg;

    }

    /************************** Configure OD Mode **************************/
    if(ulCfg & BIT_32_6)                         // Configure OD
    {
        switch(ulPort)
        {
            case GPIOA_BASE:
                {
                    ulRegAddr = PINMODE_OD0;
                    break;
                }
            case GPIOB_BASE:
                {
                    ulRegAddr = PINMODE_OD1;
                    break;
                }
            case GPIOC_BASE:
                {
                    ulRegAddr = PINMODE_OD2;
                    break;
                }
            case GPIOD_BASE:
                {
                    ulRegAddr = PINMODE_OD3;
                    break;
                }
            case GPIOE_BASE:
                {
                    ulRegAddr = PINMODE_OD4;
                    break;
                }
        }

        if(ulCfg & BIT_32_5)                     // OD Enable
        {
            xHWREG(PIN_CON_BASE + ulRegAddr)  |= ulPin;
        }
        else                                     // OD Disable
        {
            xHWREG(PIN_CON_BASE + ulRegAddr)  &= ~ulPin;
        }
    }
}

//*****************************************************************************
//
//! \brief  Write 1 to gpio pins.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//!
//! \return None.
//
//*****************************************************************************
void GPIOPinSet(unsigned long ulPort, unsigned long ulPins)
{
    xHWREG(ulPort + FIOMASK) =~ulPins;
    xHWREG(ulPort + FIOSET)  = ulPins;
}

//*****************************************************************************
//
//! \brief  Write 0 to gpio pins.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//!
//! \return None.
//
//*****************************************************************************
void GPIOPinClr(unsigned long ulPort, unsigned long ulPins)
{
    xHWREG(ulPort + FIOMASK) =~ulPins;
    xHWREG(ulPort + FIOCLR)  = ulPins;
}

//*****************************************************************************
//
//! \brief  Write 0 or 1 to select gpio pins.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//!
//! \return None.
//
//*****************************************************************************
void GPIOPinWrite(unsigned long ulPort, unsigned long ulPins, unsigned long ulVal)
{
    xHWREG(ulPort + FIOMASK) = ~ulPins;
    if(0 != ulVal)
    {
        xHWREG(ulPort + FIOSET)   =  ulPins;
    }
    else
    {
        xHWREG(ulPort + FIOCLR)   =  ulPins;
    }
}

//*****************************************************************************
//
//! \brief  Read selected gpio pin value.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPins is the bit-packed representation of the pin(s).
//!
//! \return The value of gpio pin.
//
//*****************************************************************************
unsigned long GPIOPinRead(unsigned long ulPort, unsigned long ulPin)
{
    xHWREG(ulPort + FIOMASK) = ~ulPin;
    return xHWREG(ulPort + FIOPIN);
}

//*****************************************************************************
//
//! \brief  Read selected gpio port value.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//!
//! \return The value of gpio port.
//
//*****************************************************************************
unsigned long GPIOPortRead(unsigned long ulPort)
{
    xHWREG(ulPort + FIOMASK) = (unsigned long) 0x00;
    return xHWREG(ulPort + FIOPIN);
}

//*****************************************************************************
//
//! \brief  Write value to gpio port.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//!
//! \return The value of gpio port.
//
//*****************************************************************************
void GPIOPortWrite(unsigned long ulPort, unsigned long ulVal)
{
    xHWREG(ulPort + FIOMASK) = (unsigned long) 0x00;
    xHWREG(ulPort + FIOPIN)  = ulVal;
}

//*****************************************************************************
//
//! \brief  Configure gpio pin interrupt mode.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//! \param  [in] ulPin is the bit-packed representation of the pin(s).
//! \param  [in] ulCfg is the interrupts configure parameter, which can be logical
//!              OR of the following value:
//!              - \ref INT_TYPE_RISING
//!              - \ref INT_TYPE_FALLING
//!
//! \return None.
//
//*****************************************************************************
void GPIOPinIntCfg(unsigned long ulPort, unsigned long ulPin, unsigned long ulCfg)
{
    switch(ulPort)
    {
        case GPIOA_BASE:                        // Port 0
            {
                if(ulCfg & INT_TYPE_RISING)     // GPIO Rising Int Type
                {
                    xHWREG(GPIO_INT_BASE + IO0IntEnR) |= ulPin;
                }

                if(ulCfg & INT_TYPE_FALLING)    // GPIO Falling Int Type
                {
                    xHWREG(GPIO_INT_BASE + IO0IntEnF) |= ulPin;
                }

                break;
            }

        case GPIOC_BASE:                        // Port 2
            {
                if(ulCfg & INT_TYPE_RISING)     // GPIO Rising Int Type
                {
                    xHWREG(GPIO_INT_BASE + IO2IntEnR) |= ulPin;
                }

                if(ulCfg & INT_TYPE_FALLING)    // GPIO Falling Int Type
                {
                    xHWREG(GPIO_INT_BASE + IO2IntEnF) |= ulPin;
                }
                break;
            }
        default:
            {
                while(1);                       // Error
            }
    }
}

//*****************************************************************************
//
//! \brief  Enable GPIO interrupt.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//!
//! \param  [in] ulPin is the bit-packed representation of the pin(s).
//!
//! \return None.
//!
//! \note   For LPC17xx, The pins belong to the same port share the same interrupt
//!         source.
//
//*****************************************************************************
void GPIOPinIntEnable(unsigned long ulPort, unsigned long ulPin)
{
    // Avoid Compiler warning
    (void) ulPort;
    (void) ulPin;

    xIntEnable(INT_GPIO);
}

//*****************************************************************************
//
//! \brief  Disable GPIO interrupt.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//!
//! \param  [in] ulPin is the bit-packed representation of the pin(s).
//!
//! \return None.
//!
//! \note   For LPC17xx, The pins belong to the same port share the same interrupt
//!         source.
//
//*****************************************************************************
void GPIOPinIntDisable(unsigned long ulPort, unsigned long ulPin)
{
    // Avoid Compiler warning
    (void) ulPort;
    (void) ulPin;

    xIntDisable(INT_GPIO);
}

//*****************************************************************************
//
//! \brief  Get GPIO pin interrupt flag.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//!
//! \param  [in] ulPin is the bit-packed representation of the pin(s).
//!
//! \return The interrupt status of the gpio pin, which is the logical OR of the
//!         following value:
//!         - \ref INT_TYPE_RISING
//!         - \ref INT_TYPE_FALLING
//
//*****************************************************************************
unsigned long GPIOPinIntFlagGet(unsigned long ulPort, unsigned long ulPin)
{
    unsigned long ulResult = 0;

    switch(ulPort)
    {
        case GPIOA_BASE:                           // Port 0
            {

                if(xHWREG(GPIO_INT_BASE + IO0IntEnR) & ulPin)      // GPIO Rising Int Type
                {
                    ulResult |= INT_TYPE_RISING;
                }

                if(xHWREG(GPIO_INT_BASE + IO0IntEnF) & ulPin)      // GPIO Falling Int Type
                {
                    ulResult |= INT_TYPE_FALLING;
                }

                break;
            }

        case GPIOC_BASE:                           // Port 2
            {
                if(xHWREG(GPIO_INT_BASE + IO2IntEnR) & ulPin)      // GPIO Rising Int Type
                {
                    ulResult |= INT_TYPE_RISING;
                }

                if(xHWREG(GPIO_INT_BASE + IO2IntEnF) & ulPin)      // GPIO Falling Int Type
                {
                    ulResult |= INT_TYPE_FALLING;
                }
                break;
            }
        default:
            {
                ulResult  = 0;                     // Error
            }
    }

    return (ulResult);
}

//*****************************************************************************
//
//! \brief  Clear GPIO pin interrupt flag.
//!
//! \param  [in] ulPort is the base address of the GPIO port
//!
//! \param  [in] ulPin is the bit-packed representation of the pin(s).
//!
//! \return None.
//
//*****************************************************************************
void GPIOPinIntFlagClear(unsigned long ulPort, unsigned long ulPin)
{

    switch(ulPort)
    {
        case GPIOA_BASE:                           // Port 0
            {
                xHWREG(GPIO_INT_BASE + IO0IntClr) |= ulPin;
                break;
            }

        case GPIOC_BASE:                           // Port 2
            {
                xHWREG(GPIO_INT_BASE + IO2IntClr) |= ulPin;
                break;
            }
        default:
            {
                while(1);
            }
    }
}

