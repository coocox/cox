//*****************************************************************************
//
//! \file DrvGPIO.c
//! \brief Driver for the GPIO.
//! \version v1.02.002
//! \date 09/05/2011
//! \author Nuvoton
//! \copy
//!
//! Copyright (c)  2011, Nuvoton 
//! All rights reserved.
//
//*****************************************************************************

//*****************************************************************************
//
//! Include related headers
//
//*****************************************************************************
#include <stdio.h>
#include "DrvGPIO.h"
#include "Assert.h"

//*****************************************************************************
//
//! Macro, type and constant definitions
//
//*****************************************************************************
#define PORT_OFFSET   0x40

//*****************************************************************************
//
//! Global file scope (static) variables 
//
//*****************************************************************************
static void (*_pfP0P1Callback)(uint32_t u32P0Status, uint32_t u32P1Status);
static void (*_pfP2P3P4Callback)(uint32_t u32P2Status, uint32_t u32P3Status, uint32_t u32P4Status);
static void (*_pfP5Callback)(uint32_t u32P5Status);
static void (*_pfEINT0Callback)(void);
static void (*_pfEINT1Callback)(void);

//*****************************************************************************
//
//! \brief Port 0, 1 ISR  
//!
//! \param None
//!
//! \return None.  
//
//*****************************************************************************
void GPIO01_IRQHandler(void)
{
    uint32_t u32P0Status, u32P1Status;
    //
    // Keep the interrupt source 
    //
    u32P0Status = GPIO0->ISR;
    u32P1Status = GPIO1->ISR;

    //
    // Clear the interrupt 
    //
    GPIO0->ISR = u32P0Status;
    GPIO1->ISR = u32P1Status;

    //
    // Call the callback function of P0/P1 interrupt 
    //
    if (_pfP0P1Callback)
        _pfP0P1Callback(u32P0Status, u32P1Status);    
}

//*****************************************************************************
//
//! \brief Port 2, 3, 4 ISR  
//!
//! \param None
//!
//! \return None.  
//
//*****************************************************************************
void GPIO234_IRQHandler(void)
{
    uint32_t u32P2Status, u32P3Status, u32P4Status;
    
    //
    // Keep the interrupt source 
    //
    u32P2Status = GPIO2->ISR;
    u32P3Status = GPIO3->ISR;
    u32P4Status = GPIO4->ISR;

    //
    // Avoid to clear EINT0/1 INT flag 
    //
    u32P3Status = u32P3Status & ~(0x1 << 2); 

    //
    // Clear the interrupt 
    //
    GPIO2->ISR = u32P2Status;
    GPIO3->ISR = u32P3Status;
    GPIO4->ISR = u32P4Status;

    //
    // Call the callback function of P2/P3/P4 interrupt 
    //
    if (_pfP2P3P4Callback)
        _pfP2P3P4Callback(u32P2Status, u32P3Status, u32P4Status);    
}

//*****************************************************************************
//
//! \brief Port 5 ISR  
//!
//! \param None
//!
//! \return None.  
//
//*****************************************************************************
void GPIO5_IRQHandler(void)
{
    uint32_t u32P5Status;
    
    //
    // Keep the interrupt source 
    //
    u32P5Status = GPIO5->ISR;

    //
    // Avoid to clear EINT0/1 INT flag 
    //
    u32P5Status = u32P5Status & ~(0x1 << 2); 

    //
    // Clear the interrupt 
    //
    GPIO5->ISR = u32P5Status;

    //
    // Call the callback function of P5 interrupt 
    //
    if (_pfP5Callback)
        _pfP5Callback(u32P5Status);    
}

//*****************************************************************************
//
//! \brief External INT0(Port32) ISR 
//!
//! \param None
//!
//! \return None.  
//
//*****************************************************************************
void EINT0_IRQHandler(void)
{
    //
    // For P32, clear the INT flag 
    //
    GPIO3->ISR =  1UL << 2;
    
    if (_pfEINT0Callback)
        _pfEINT0Callback();
}

//*****************************************************************************
//
//! \brief External INT1(Port33) ISR 
//!
//! \param None
//!
//! \return None.  
//
//*****************************************************************************

void EINT1_IRQHandler(void)
{
    //
    // For P52, clear the INT flag 
    //
    GPIO5->ISR =  1UL << 2;
    
    if (_pfEINT1Callback)
        _pfEINT1Callback();
}

//*****************************************************************************
//
//! \brief Set the specified GPIO pin to the specified GPIO operation mode. 
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param pin Specify pin of the GPIO port. It could be E_PIN0, E_PIN2 ... 
//!  ~ E_PIN7. 
//!
//! \param IOMode set the specified GPIO pin to be E_IO_INPUT, E_IO_OUTPUT,
//!  E_IO_OPENDRAIN or E_IO_QUASI mode.
//!
//! \return None.  
//
//*****************************************************************************
void DrvGPIO_Open(E_DRVGPIO_PORT port, uint32_t pin, E_DRVGPIO_IO IOMode)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);
    base->PMD &= ~(0x3<<(pin*2));
    base->PMD |= (IOMode<<(pin*2));
}

//*****************************************************************************
//
//! \brief Close the specified GPIO pin function and set the pin to 
//!  quasi-bidirectional mode. 
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param pin Specify pin of the GPIO port. It could be E_PIN0, E_PIN2 ... 
//!  ~ E_PIN7. 
//!
//! \return None.  
//
//*****************************************************************************
void DrvGPIO_Close(E_DRVGPIO_PORT port, uint32_t pin)
{  
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    base->PMD &= ~(0x3<<(pin*2));

    //
    // disable GPIO debounce clock 
    //
    GPIODBNCE->CON_BITS.DBCLKEN = 0; 
}   

//*****************************************************************************
//
//! \brief Set the specified GPIO pin to 1.  
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param pin Specify pin of the GPIO port. It could be E_PIN0, E_PIN2 ... 
//!  ~ E_PIN7. 
//!
//! \return E_SUCCESS                       Operation successful
//
//*****************************************************************************
int32_t DrvGPIO_SetBit(E_DRVGPIO_PORT port, uint32_t pin)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    base->DOUT |= (1 << pin);

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Get the pin value from the specified input GPIO pin. 
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param pin Specify pin of the GPIO port. It could be E_PIN0, E_PIN2 ... 
//!  ~ E_PIN7. 
//!
//! \return The specified input pin value                   0 / 1 
//
//*****************************************************************************
int32_t DrvGPIO_GetBit(E_DRVGPIO_PORT port, uint32_t pin)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    return ((base->PIN >> pin) & 0x1);
}

//*****************************************************************************
//
//! \brief Set the specified GPIO pin to 0.
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param pin Specify pin of the GPIO port. It could be E_PIN0, E_PIN2 ... 
//!  ~ E_PIN7. 
//!
//! \return E_SUCCESS                       Operation successful 
//
//*****************************************************************************
int32_t DrvGPIO_ClrBit(E_DRVGPIO_PORT port, uint32_t pin)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    base->DOUT &= ~(1 << pin);

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Set the output port value to the specified GPIO port. 
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param i32PortValue The data output value. It could be 0~0xFF.
//!
//! \return E_SUCCESS                       Operation successful 
//
//*****************************************************************************
int32_t DrvGPIO_SetPortBits(E_DRVGPIO_PORT port, int32_t i32PortValue)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    base->DOUT = i32PortValue;

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Get the input port value from the specified GPIO port. 
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \return The specified input port value                  0 ~ 0xFF 
//
//*****************************************************************************
int32_t DrvGPIO_GetPortBits(E_DRVGPIO_PORT port)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    return base->PIN;
}

//*****************************************************************************
//
//! \brief Get the bit value from the specified Data Output Value Register. If
//!  the bit value is 1, it's meaning the pin is output data to high. Otherwise,
//!  it's output data to low.
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param pin Specify pin of the GPIO port. It could be E_PIN0, E_PIN2 ... 
//!  ~ E_PIN7. 
//!
//! \return The bit value of the specified register         0 / 1 
//
//*****************************************************************************
int32_t DrvGPIO_GetDoutBit(E_DRVGPIO_PORT port, uint32_t pin)
{    
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    return ((base->DOUT>>pin) & 0x1);
}

//*****************************************************************************
//
//! \brief Get the port value from the specified Data Output Value Register.
//!  If the corresponding bit of the return port value is 1, it's meaning the 
//!  the corresponding bit is output data to high. Otherwise, it's output data 
//!  to low.
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5. 
//!
//! \return The portt value of the specified register       0 ~ 0xFF 
//
//*****************************************************************************
int32_t DrvGPIO_GetPortDoutBits(E_DRVGPIO_PORT port)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    return (base->DOUT);
}

//*****************************************************************************
//
//! \brief This function is used to protect the write data function of the 
//!  corresponding GPIO pin. the bit value is 1, it's meaning the pin is output 
//!  data to high. Otherwise, it's output data to low. 
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param pin Specify pin of the GPIO port. It could be E_PIN0, E_PIN2 ... 
//!  ~ E_PIN7. 
//!
//! \return The bit value of the specified register         0 / 1 
//
//*****************************************************************************
int32_t DrvGPIO_SetBitMask(E_DRVGPIO_PORT port, uint32_t pin)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    base->DMASK |= (1<<pin);

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Get the bit value from the specified Data Output Write Mask Register. 
//!  If the bit value is 1, it's meaning the corresponding bit is protected. 
//!  And write data to the bit is ignored.  
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param pin Specify pin of the GPIO port. It could be E_PIN0, E_PIN2 ... 
//!  ~ E_PIN7. 
//!
//! \return The bit value of the specified register         0 / 1 
//
//*****************************************************************************
int32_t DrvGPIO_GetBitMask(E_DRVGPIO_PORT port, uint32_t pin)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    return ((base->DMASK>>pin) & 0x1);
}

//*****************************************************************************
//
//! \brief This function is used to remove the write protect function of the the 
//!  corresponding GPIO  pin. After remove the bit mask, write data to the 
//!  corresponding bit is workable.
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param pin Specify pin of the GPIO port. It could be E_PIN0, E_PIN2 ... 
//!  ~ E_PIN7. 
//!
//! \return E_SUCCESS                       Operation successful 
//
//*****************************************************************************
int32_t DrvGPIO_ClrBitMask(E_DRVGPIO_PORT port, uint32_t pin)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    base->DMASK &= ~(1<<pin);

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief This function is used to protect the write data function of the  
//!  corresponding GPIO pins. When set the bits are masked, write data to the 
//!  protect bits are ignored.
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param i32PortValue Specify pins of the GPIO port. It could be 0~0xFF. 
//!
//! \return E_SUCCESS                       Operation successful 
//
//*****************************************************************************
int32_t DrvGPIO_SetPortMask(E_DRVGPIO_PORT port, int32_t i32PortValue)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    base->DMASK |= i32PortValue;

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Get the port value from the specified Data Output Write Mask Register.  
//!  If the corresponding bit of the return port value is 1, it's meaning the  
//!  bits are protected. And write data to the bits are ignored.
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param i32PortValue Specify pins of the GPIO port. It could be 0~0xFF. 
//!
//! \return The portt value of the specified register       0 ~ 0xFF 
//
//*****************************************************************************
int32_t DrvGPIO_GetPortMask(E_DRVGPIO_PORT port)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    return (base->DMASK); 
}

//*****************************************************************************
//
//! \brief This function is used to remove the write protect function of the the  
//!  corresponding GPIO pins. After remove those bits mask, write data to the 
//!  corresponding bits are workable.
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param i32PortValue Specify pins of the GPIO port. It could be 0~0xFF. 
//!
//! \return E_SUCCESS                       operation successful 
//
//*****************************************************************************
int32_t DrvGPIO_ClrPortMask(E_DRVGPIO_PORT port, int32_t i32PortValue)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    base->DMASK &= ~i32PortValue;
    
    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Enable the debounce function of the specified GPIO input pin. 
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param pin Specify pin of the GPIO port. It could be E_PIN0, E_PIN2 ... 
//!  ~ E_PIN7. 
//!
//! \return E_SUCCESS                       Operation successful 
//
//*****************************************************************************
int32_t DrvGPIO_EnableDebounce(E_DRVGPIO_PORT port, uint32_t pin)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    base->DBEN |= (1<<pin);    

    GPIODBNCE->CON_BITS.DBCLKEN = 1;

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Disable the debounce function of the specified GPIO input pin. 
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param pin Specify pin of the GPIO port. It could be E_PIN0, E_PIN2 ... 
//!  ~ E_PIN7. 
//!
//! \return E_SUCCESS                       Operation successful 
//
//*****************************************************************************
int32_t DrvGPIO_DisableDebounce(E_DRVGPIO_PORT port, uint32_t pin)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    base->DBEN &= ~(1<<pin);    

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Set the interrupt debounce sampling time based on the debounce counter 
//!  clock source. If the debounce clock source is from internal 10 KHz and 
//!  sampling cycle selection is 4. The target debounce time is (2^4)*(1/(10*1000)) 
//!  s = 16*0.0001 s = 1600 us, and system will sampling interrupt input once 
//!  per 1600 us.
//!
//! \param u32CycleSelection The number of sampling cycle selection, the range  
//!  of value is from 0 ~ 15. The target debounce time is (2^(u32CycleSelection))
//!  *(ClockSource) second.
//!
//! \param ClockSource it could be DBCLKSRC_HCLK or DBCLKSRC_10K.
//!
//! \return E_SUCCESS                       Operation successful
//!         E_DRVGPIO_ARGUMENT              Incorrect argument 
//
//*****************************************************************************
int32_t DrvGPIO_SetDebounceTime(uint32_t u32CycleSelection, E_DRVGPIO_DBCLKSRC ClockSource)
{
    //
    // Maximum debounce time is 2^(15)*(clk src) 
    //
    assert_param(CHECK_GPIO_DEBCYCLE(u32CycleSelection));
    
    GPIODBNCE->CON_BITS.DBCLKSEL = u32CycleSelection ; 

    GPIODBNCE->CON_BITS.DBCLKSRC = ClockSource ; 

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief This function is used to get the number of debounce sampling cycle 
//!  selection. 
//!
//! \param None 
//!
//! \return Number of the sampling cycle selection          0 ~ 15 
//
//*****************************************************************************
int32_t DrvGPIO_GetDebounceSampleCycle(void)
{
    return GPIODBNCE->CON_BITS.DBCLKSEL;
}

//*****************************************************************************
//
//! \brief Enable the interrupt function of the specified GPIO pin. Except for 
//!  Port3-2 and Port5-2 pins are for external interrupt used.  
//!
//! \param port It could be E_PORT0, E_PORT1, E_PORT2, E_PORT3, E_PORT4 and 
//!  E_PORT5.
//!
//! \param pin Specify pin of the GPIO port. It could be E_PIN0, E_PIN2 ... ~   
//!  E_PIN7. But the Port3-2 and Port3-3 are only used for external interrupt 0/1.
//!
//! \param Type Specify the interrupt trigger type. It could be E_IO_RISING, 
//!  E_IO_FALLING or E_IO_BOTH_EDGE and it's meaning the interrupt function 
//!  enable by rising egde/high level, falling edge/low level or both riging 
//!  edge and falling egde. If the interrupt mode is E_MODE_LEVEL and interrupt 
//!  type is E_BOTH_EDGE¡Athen calling this API is ignored.
//!
//! \param Mode Specify the interrupt mode. It could be E_MODE_EDGE or 
//!  E_MODE_LEVEL to control the interrupt is by edge trigger or by level trigger.
//!  If the interrupt mode is E_MODE_LEVEL and interrupt type is E_BOTH_EDGE 
//!  then calling this API is ignored. 
//!
//! \return E_SUCCESS                       Operation successful
//!         E_DRVGPIO_ARGUMENT              Incorrect argument
//
//*****************************************************************************
int32_t DrvGPIO_EnableInt(E_DRVGPIO_PORT port, uint32_t pin, E_DRVGPIO_INT_TYPE Type, E_DRVGPIO_INT_MODE Mode)
{
    GPIO_TypeDef *base;

    assert_param(CHECK_GPIO_EINT0(port, pin));
    assert_param(CHECK_GPIO_EINT1(port, pin));
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    //
    // Configure the interrupt to be rising/falling when edge trigger or high/low level when level trigger 
    //
    if (Type == E_IO_RISING)
   	    base->IER |= (1 << (pin+16));
    else if(Type == E_IO_FALLING)
   	    base->IER |= (1 << pin);
    else if(Type == E_IO_BOTH_EDGE)  
   	    base->IER |= ((1<<pin) | (1 << (pin+16)));
    else
        return E_DRVGPIO_ARGUMENT;

    //
    // Configure to be level trigger or edge trigger 
    //
    if(Mode == E_MODE_EDGE)
        base->IMD &= ~(1<<pin);
    else if(Mode ==E_MODE_LEVEL)
        base->IMD |= (1<<pin);
    else
        return E_DRVGPIO_ARGUMENT;

    //
    // Configure the relative interrupt of M0 
    //
    if ((port == E_PORT0) || (port == E_PORT1))
    {
        NVIC_SetPriority(GPIO01_IRQn, (1<<__NVIC_PRIO_BITS) - 2);
        NVIC_EnableIRQ(GPIO01_IRQn);
    }

    if ((port == E_PORT2) || (port == E_PORT3) || (port == E_PORT4))
    {
        NVIC_SetPriority(GPIO234_IRQn, (1<<__NVIC_PRIO_BITS) - 2);
        NVIC_EnableIRQ(GPIO234_IRQn);
    } 
    
    if (port == E_PORT5)
    {
        NVIC_SetPriority(GPIO5_IRQn, (1<<__NVIC_PRIO_BITS) - 2);
        NVIC_EnableIRQ(GPIO5_IRQn);
    } 
    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Disable the interrupt function of the specified GPIO pin. Except for 
//!  Port3-2 and Port3-2 pins are for external interrupt used.
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, 
//!  E_PORT3, E_PORT4 and E_PORT5.
//!
//! \param pin Specify pin of the GPIO port. It could be E_PIN0, E_PIN2 ... 
//!  ~ E_PIN7. 
//!
//! \return E_SUCCESS                       Operation successful 
//
//*****************************************************************************
int32_t DrvGPIO_DisableInt(E_DRVGPIO_PORT port, uint32_t pin)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    base->IER &= ~((1<<pin) | (1 << (pin+16)));
     
    if ((port == E_PORT0) || (port == E_PORT1))
        NVIC_DisableIRQ(GPIO01_IRQn);

    if ((port == E_PORT2) || (port == E_PORT3) || (port == E_PORT4))
        NVIC_DisableIRQ(GPIO234_IRQn);

    if (port == E_PORT5)
        NVIC_DisableIRQ(GPIO5_IRQn);

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Install the interrupt callback function for GPIO Port0/Port1 and  
//!  Port2/Port3/Port4.
//!
//! \param pfP0P1Callback The function pointer of Port0/Port1 callback function.
//!
//! \param pfP2P3P4Callback the function pointer of Port2/Port3/Port4 callback.  
//!  function. 
//!
//! \return None 
//
//*****************************************************************************
void DrvGPIO_SetIntCallback(P0P1_CALLBACK pfP0P1Callback, P2P3P4_CALLBACK pfP2P3P4Callback, P5_CALLBACK pfP5Callback)
{
    _pfP0P1Callback  = (void (*)(uint32_t, uint32_t))pfP0P1Callback;
    _pfP2P3P4Callback = (void (*)(uint32_t, uint32_t, uint32_t))pfP2P3P4Callback;    
    _pfP5Callback  = (void (*)(uint32_t))pfP5Callback;
}

//*****************************************************************************
//
//! \brief Enable the interrupt function for external GPIO interrupt from 
//!  P32/P33 pin.
//!
//! \param pin Specify the external INT pin of GPIO Port3 and Port5. It could be
//!  E_EINT0_PIN (Port3-2) or E_EINT1_PIN (Port5-2).  
//!
//! \param Type Specify the interrupt trigger type. It could be E_IO_RISING,  
//!  E_IO_FALLING or E_IO_BOTH_EDGE and it's meaning the interrupt function 
//!  enable by rising egde/high level, falling edge/low level or both riging 
//!  edge and falling egde. If the interrupt mode is E_MODE_LEVEL and interrupt 
//!  type is E_BOTH_EDGE¡Athen calling this API is ignored.
//!
//! \param Mode Specify the interrupt mode. It could be E_MODE_EDGE or  
//!  E_MODE_LEVEL to control the interrupt is by edge trigger or by level trigger.
//!  If the interrupt mode is E_MODE_LEVEL and interrupt type is E_BOTH_EDGE¡A
//!  then calling this API is ignored.
//!
//! \return E_SUCCESS                       Operation successful 
//
//*****************************************************************************
int32_t DrvGPIO_EnableEINT(E_DRVGPIO_EXT_INT_PIN pin, E_DRVGPIO_INT_TYPE Type, E_DRVGPIO_INT_MODE Mode, EINT_CALLBACK pfEINTCallback)
{
    GPIO_TypeDef *port;

    if (pin == E_EINT0_PIN)
   	    port = GPIO3;
    else 
        port = GPIO5;

    if (Type == E_IO_RISING)
        port->IER |= (1 << 18);
    else if(Type == E_IO_FALLING)
        port->IER |= (1 << 2);
    else if(Type == E_IO_BOTH_EDGE)  
        port->IER |= ((1<<2) | (1 << 18));
    else
        return E_DRVGPIO_ARGUMENT;

    //
    // Configure to be level trigger or edge trigger 
    //
    if (Mode == E_MODE_EDGE)
   	    port->IMD &= ~(1<<2);
    else if(Mode ==E_MODE_LEVEL)
   	    port->IMD |= (1<<2);
    else
        return E_DRVGPIO_ARGUMENT;

    if (pin == E_EINT0_PIN)
    {
        _pfEINT0Callback = pfEINTCallback;
        NVIC_EnableIRQ(EINT0_IRQn);
    }
    else 
    {
        _pfEINT1Callback = pfEINTCallback;
        NVIC_EnableIRQ(EINT1_IRQn);
    }

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Disable the interrupt function for specified external GPIO interrupt   
//!  from P32/P33 pin.
//!
//! \param pin Specify the external INT pin of GPIO Port3. It could be 
//!  E_EINT0_PIN or E_EINT1_PIN. And E_EINT0_PIN is the pin2, E_EINT1_PIN is the
//!  pin3.
//!
//! \return E_SUCCESS                       Operation successful  
//
//*****************************************************************************
int32_t DrvGPIO_DisableEINT(E_DRVGPIO_EXT_INT_PIN pin)
{
    GPIO_TypeDef *port;
    volatile uint32_t u32Reg;
   
    if (pin == E_EINT0_PIN)
		port = GPIO3;
    else
		port = GPIO5;

    port->IER &= (~((1UL << 2) | (1UL << (2 + 16))));

    if (pin == E_EINT0_PIN)
        NVIC_DisableIRQ(EINT0_IRQn);
    else
        NVIC_DisableIRQ(EINT1_IRQn);

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Get the port value from the specified Interrupt Trigger Source    
//!  Indicator Register. If the corresponding bit of the return port value is 1,
//!  it's meaning the interrupt occurred at the corresponding bit. Otherwise, 
//!  no interrupt occurred at that bit.
//!
//! \param port Specify GPIO port. It could be E_PORT0, E_PORT1, E_PORT2, E_PORT3 
//!  and E_PORT4.
//!
//! \return The portt value of the specified register       0 ~ 0xFF 
//
//*****************************************************************************
int32_t DrvGPIO_GetIntStatus(E_DRVGPIO_PORT port)
{
    GPIO_TypeDef *base;
    assert_param(CHECK_GPIO_PORT(port));

    base = (GPIO_TypeDef *)get_port_base(port);

    return base->ISR;
}

//*****************************************************************************
//
//! \brief Initialize the specified function and configure the relative pins for   
//!   specified function used. 
//!
//! \param function Specify the relative GPIO pins as special function pins. It 
//!  could be : 
//!           FUNC_GPIO
//!               set all IO pins as GPIO pins.
//!           FUNC_I2C
//!               P3.4 & P3.5 as I2C SDA & SCL pins.
//!           FUNC_SPI
//!               P0.4~P0.7 as SPI pins.
//!           FUNC_ADC0 / FUNC_ADC1 / FUNC_ADC2 / FUNC_ADC3 /
//!           FUNC_ADC4 / FUNC_ADC5 / FUNC_ADC6 / FUNC_ADC7
//!               P1.0, P1.2~P1.5, P3.0~P3.1 are ADC0~ADC7 pins.
//!           FUNC_EXTINT0 / FUNC_EXTINT1
//!               P3.2 and P5.2 as external INT pins.
//!           FUNC_TMR0 / FUNC_TMR1
//!               P3.4, P3.5 as TIMER0~1 counter input pins or toggle out pins. 
//!           FUNC_UART
//!               P1.2, P1.3, P0.0 and P0.1 as UART RX/TX/CTS/RTS.
//!           FUNC_PWM0 / FUNC_PWM1 / FUNC_PWM2 / FUNC_PWM3,
//!           FUNC_PWM4 / FUNC_PWM5
//!               P2.2~P2.6, P0.4 pins as PWM channel 0~5.
//!           FUNC_ICE
//!               P4.6, P4.7 and ICE CLK and DAT pins.
//!           FUNC_ACMP0 / FUNC_ACMP1
//!               P1.4, P1.5, P3.6 pins for ACMP0 and P3.0, P3.1, P2.6 pins for 
//!               ACMP1.
//!           FUNC_T0EX / FUNC_T1EX
//!               P3.2, P3.6 pins as capture input source for TIMER0~1.
//!
//! \return E_SUCCESS                       Operation successful 
//
//*****************************************************************************
int32_t DrvGPIO_InitFunction(uint32_t function)
{
    uint32_t shift0, shift1;
    uint32_t mask0, mask1;
    uint32_t val0, val1;
    uint32_t port0, port1;
    uint32_t base, value;

    if (function == FUNC_GPIO)
    {
        GCR->P0_MFP = 0;
        GCR->P1_MFP = 0;
        GCR->P2_MFP = 0;
        GCR->P3_MFP = 0;
        GCR->P4_MFP = 0;
        GCR->P5_MFP = 0;
    }

    port0 = (function & 0xF000000) >> 24;
    port1 = (function & 0xF0000000) >> 28;

    if (port0 != 0xF)
    {
        base = (GCR_BASE + 0x30) + (port0 << 2);
        shift0 = (function & 0xF0000) >> 16;
        mask0 = (function & 0xF00) >> 8;
        val0 = (((function & 0xC) << 6) | (function & 0x3)) << shift0;

        if (mask0 & 0x2)
			      val0 |= (val0 << 1);
        if (mask0 & 0x4)
            val0 |= (val0 << 2);
        if (mask0 & 0x8)
            val0 |= (val0 << 3);

        mask0 |= (mask0 << 8);
        value = inpw(base);
        value &= ~(mask0 << shift0);
        outpw(base, value|val0);
    }

    if (port1 != 0xF)
    {
        base = (GCR_BASE + 0x30) + (port1 << 2);
        shift1 = (function & 0xF00000) >> 20;
        mask1 = (function & 0xF000) >> 12;
        val1 = (((function & 0xC0) << 2) | ((function & 0x30) >> 4)) << shift1;

        if (mask1 & 0x2)
            val1 |= (val1 << 1);
        if (mask1 & 0x4)
            val1 |= (val1 << 2);
        if (mask1 & 0x8)
            val1 |= (val1 << 3);

        mask1 |= (mask1 << 8);
        value = inpw(base);
        value &= ~(mask1 << shift1);
        outpw(base, value|val1);
    }

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Initialize the specified function and configure the relative pins for   
//!   specified function used. 
//!
//! \param function Specify the relative GPIO pins as special function pins. It 
//!  could be : 
//!           FUNC_GPIO
//!               set all IO pins as GPIO pins.
//!           FUNC_I2C
//!               P3.4 & P3.5 as I2C SDA & SCL pins.
//!           FUNC_SPI
//!               P0.4~P0.7 as SPI pins.
//!           FUNC_ADC0 / FUNC_ADC1 / FUNC_ADC2 / FUNC_ADC3 /
//!           FUNC_ADC4 / FUNC_ADC5 / FUNC_ADC6 / FUNC_ADC7
//!               P1.0, P1.2~P1.5, P3.0~P3.1 are ADC0~ADC7 pins.
//!           FUNC_EXTINT0 / FUNC_EXTINT1
//!               P3.2 and P5.2 as external INT pins.
//!           FUNC_TMR0 / FUNC_TMR1
//!               P3.4, P3.5 as TIMER0~1 counter input pins or toggle out pins. 
//!           FUNC_UART
//!               P1.2, P1.3, P0.0 and P0.1 as UART RX/TX/CTS/RTS.
//!           FUNC_PWM0 / FUNC_PWM1 / FUNC_PWM2 / FUNC_PWM3,
//!           FUNC_PWM4 / FUNC_PWM5
//!               P2.2~P2.6, P0.4 pins as PWM channel 0~5.
//!           FUNC_ICE
//!               P4.6, P4.7 and ICE CLK and DAT pins.
//!           FUNC_ACMP0 / FUNC_ACMP1
//!               P1.4, P1.5, P3.6 pins for ACMP0 and P3.0, P3.1, P2.6 pins for 
//!               ACMP1.
//!           FUNC_T0EX / FUNC_T1EX
//!               P3.2, P3.6 pins as capture input source for TIMER0~1.
//!
//! \return E_SUCCESS                       Operation successful 
//
//*****************************************************************************
int32_t DrvGPIO_SelectFunction(uint32_t function)
{
    uint32_t shift0;
    uint32_t mask0;
    uint32_t val0;
    uint32_t port0;
    uint32_t base, value;

    port0 = (function & 0xF000000) >> 24;

    if (port0 != 0xF)
    {
        base = (GCR_BASE + 0x30) + (port0 << 2);
        shift0 = (function & 0xF0000) >> 16;
        mask0 = (function & 0xF00) >> 8;
        val0 = (((function & 0xC) << 6) | (function & 0x3)) << shift0;

       if (val0)
       {
           mask0 |= (mask0 << 8);
           value = inpw(base);
           value &= ~(mask0 << shift0);
           outpw(base, value|val0);
       }
       else
           outpw(base, 0);
    }

    return E_SUCCESS;
}

//*****************************************************************************
//
//! \brief Initialize the specified function and configure the relative pins for  
//!  specified function used with option.
//!
//! \param function Specify the relative GPIO pins as special function pins.
//!  It could be :
//!           FUNC_GPIO_P0 / FUNC_GPIO_P1 / FUNC_GPIO_P2 / FUNC_GPIO_P3 / 
//!           FUNC_GPIO_P4 / FUNC_GPIO_P5 / FUNC_UART_TX_P00 / FUNC_UART_RX_P01 / 
//!           FUNC_UART_CTS_P00 / FUNC_UART_RTS_P01 / FUNC_UART_RX_P12 / F
//!           UNC_UART_TX_P13 / FUNC_SPI_SS_P04 / FUNC_SPI_SS_P01
//!
//! \return E_SUCCESS                       Operation successful
//
//*****************************************************************************
int32_t DrvGPIO_GetVersion(void)
{
    return DRVGPIO_VERSION_NUM;
}


