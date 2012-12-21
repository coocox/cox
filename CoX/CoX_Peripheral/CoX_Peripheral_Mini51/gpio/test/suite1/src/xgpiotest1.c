//*****************************************************************************
//
//! @page xgpio_testcase xgpio register test
//!
//! File: @ref xgpiotest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xgpio sub component.<br><br>
//! - \p Board: NuTiny-LB-Mini51 v2.0 <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. <br><br>
//! .
//!
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define:
//! <br>(1)None.<br><br>
//! - \p Option-hardware:
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:
//! <br>Connect an COM cable to the development board.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//!
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_xgpio_register
//! .
//! \file xgpiotest1.c
//! \brief xgpio test source file
//! \brief xgpio test header file <br>
//
//*****************************************************************************

#include "test.h"

//*****************************************************************************
//
//!\page test_xgpio_register test_xgpio_register
//!
//!<h2>Description</h2>
//!Test xgpio register. <br>
//!
//
//*****************************************************************************

//
// GPIO base value
//
static unsigned long ulGPIO[6] = {xGPIO_PORTA_BASE,xGPIO_PORTB_BASE,
                                  xGPIO_PORTC_BASE,xGPIO_PORTD_BASE,
                                  xGPIO_PORTE_BASE,xGPIO_PORTF_BASE};

//
// GPIO bit packed pin
//
static unsigned long ulPackedPin[8] = {xGPIO_PIN_0, xGPIO_PIN_1, xGPIO_PIN_2,
                                       xGPIO_PIN_3, xGPIO_PIN_4, xGPIO_PIN_5,
                                       xGPIO_PIN_6, xGPIO_PIN_7};

//
// GPIO Pin Mode
//
static unsigned long ulPinMode[4] = {xGPIO_DIR_MODE_IN, xGPIO_DIR_MODE_OUT, 
                                     xGPIO_DIR_MODE_QB, xGPIO_DIR_MODE_OD};

//
// GPIO interrupt type 
//
static unsigned long ulIntType[6] = {xGPIO_FALLING_EDGE, xGPIO_RISING_EDGE,
                                     xGPIO_BOTH_EDGES,   xGPIO_BOTH_LEVEL,
                                     xGPIO_LOW_LEVEL,    xGPIO_HIGH_LEVEL};

//
// De-bounce delay source
//
static unsigned long ulDelay[2] = {GPIO_DBCLKSRC_HCLK, GPIO_DBCLKSRC_10K};

//
// De-bounce delay cycle
//
static unsigned long ulDelayCycle[3] = {0, 10, 15};

//
// Peripheral ID
//
static unsigned long ulPeripheralID[1] = {SYSCTL_PERIPH_GPIO};

//
// GPIO pin
//
static unsigned long ulPinValue[3] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2};

//*****************************************************************************
//
//! \brief Get the Test description of xgpio001 register test.
//!
//! \return the desccription of the xgpio001 test.
//
//*****************************************************************************
static char* xgpio001GetTest(void)
{
    return "xgpio, 001, xgpio register test";
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xgpio001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio001Setup(void)
{
    
}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xgpio001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio001TearDown(void)
{
    xSysCtlPeripheralReset(SYSCTL_PERIPH_GPIO);
}

//*****************************************************************************
//
//! \brief xgpio001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio001Execute(void)
{
   
    unsigned long ulPin, ulPort;
    unsigned long ulvalue, ulTemp, ulTemp1;  
    int i, j;

    //
    // GPIOA PIN mode test
    //
    xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTA_BASE, xGPIO_PIN_0) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");      
    xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTA_BASE, xGPIO_PIN_0) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error"); 
    
    xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTA_BASE, xGPIO_PIN_4) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTA_BASE, xGPIO_PIN_4) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error"); 
    
    //
    // GPIOB pin mode test
    //
    xGPIODirModeSet(xGPIO_PORTB_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTB_BASE, xGPIO_PIN_0) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");      
    xGPIODirModeSet(xGPIO_PORTB_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTB_BASE, xGPIO_PIN_0) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");     
    xGPIODirModeSet(xGPIO_PORTB_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTB_BASE, xGPIO_PIN_4) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTB_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTB_BASE, xGPIO_PIN_4) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");   
    
    //
    // GPIOC pin mode test
    //
    xGPIODirModeSet(xGPIO_PORTC_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTC_BASE, xGPIO_PIN_4) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTC_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTC_BASE, xGPIO_PIN_4) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");     
    xGPIODirModeSet(xGPIO_PORTC_BASE, xGPIO_PIN_2, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTC_BASE, xGPIO_PIN_2) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTC_BASE, xGPIO_PIN_2, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTC_BASE, xGPIO_PIN_2) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");
    
    //
    // GPIOD pin mode test
    //
    xGPIODirModeSet(xGPIO_PORTD_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTD_BASE, xGPIO_PIN_0) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");      
    xGPIODirModeSet(xGPIO_PORTD_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTD_BASE, xGPIO_PIN_0) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error"); 
    
    xGPIODirModeSet(xGPIO_PORTD_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTD_BASE, xGPIO_PIN_4) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTD_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTD_BASE, xGPIO_PIN_4) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");     
    
    //
    // GPIOE pin mode test
    //
    xGPIODirModeSet(xGPIO_PORTE_BASE, xGPIO_PIN_6, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTE_BASE, xGPIO_PIN_6) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");      
    xGPIODirModeSet(xGPIO_PORTE_BASE, xGPIO_PIN_6, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTE_BASE, xGPIO_PIN_6) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error"); 
    
    xGPIODirModeSet(xGPIO_PORTE_BASE, xGPIO_PIN_7, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTE_BASE, xGPIO_PIN_7) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTE_BASE, xGPIO_PIN_7, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTE_BASE, xGPIO_PIN_7) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");
    
    //
    // GPIOF pin mode test
    //
    xGPIODirModeSet(xGPIO_PORTF_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTF_BASE, xGPIO_PIN_0) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error"); 
    
    xGPIODirModeSet(xGPIO_PORTF_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTF_BASE, xGPIO_PIN_4) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTF_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTF_BASE, xGPIO_PIN_4) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");  
       
    xIntDisable(xINT_GPIOA);
    xIntDisable(xINT_GPIOB);
    xIntDisable(xINT_GPIOC);
    xIntDisable(xINT_GPIOD);
    xIntDisable(xINT_GPIOE);
    
    //
    // GPIOA int enable test
    //
    for(i = 0; i < 6; i++)
    {
        xGPIOPinIntEnable(xGPIO_PORTA_BASE, xGPIO_PIN_0, ulIntType[i]);
        if(ulIntType[i] & 0x10)
        { 
            ulTemp = xHWREG(xGPIO_PORTA_BASE + GPIO_IMD) & xGPIO_PIN_0;
            TestAssert(ulTemp == xGPIO_PIN_0,
                       "xgpio, \"Level INT type enable \" error");
        }
        else
        {
            ulTemp = xHWREG(xGPIO_PORTA_BASE + GPIO_IMD) & xGPIO_PIN_0;
            TestAssert(ulTemp == 0,
                       "xgpio, \"Edge INT type enable \" error");
        }
        if(ulIntType[i] & 2)
        {
            ulTemp = xHWREG(xGPIO_PORTA_BASE + GPIO_IEN) & (xGPIO_PIN_0 << 16);
            TestAssert(ulTemp == (xGPIO_PIN_0 << 16),
                       "xgpio, \"Rising or high level Int \" error");                    
        }
        if(ulIntType[i] & 1)
        {
            ulTemp = xHWREG(xGPIO_PORTA_BASE + GPIO_IEN) & xGPIO_PIN_0;
            TestAssert(ulTemp ==xGPIO_PIN_0,
                       "xgpio, \"Falling or low level Int \" error");  
        }    
    }
    
    //
    // GPIOB int enable test
    //
    for(i = 0; i < 6; i++)
    {
        xGPIOPinIntEnable(xGPIO_PORTB_BASE, xGPIO_PIN_0, ulIntType[i]);
        if(ulIntType[i] & 0x10)
        { 
            ulTemp = xHWREG(xGPIO_PORTB_BASE + GPIO_IMD) & xGPIO_PIN_0;
            TestAssert(ulTemp == xGPIO_PIN_0,
                       "xgpio, \"Level INT type enable \" error");
        }
        else
        {
            ulTemp = xHWREG(xGPIO_PORTB_BASE + GPIO_IMD) & xGPIO_PIN_0;
            TestAssert(ulTemp == 0,
                       "xgpio, \"Edge INT type enable \" error");
        }
        if(ulIntType[i] & 2)
        {
            ulTemp = xHWREG(xGPIO_PORTB_BASE + GPIO_IEN) & (xGPIO_PIN_0 << 16);
            TestAssert(ulTemp == (xGPIO_PIN_0 << 16),
                       "xgpio, \"Rising or high level Int \" error");                    
        }
        if(ulIntType[i] & 1)
        {
            ulTemp = xHWREG(xGPIO_PORTB_BASE + GPIO_IEN) & xGPIO_PIN_0;
            TestAssert(ulTemp ==xGPIO_PIN_0,
                       "xgpio, \"Falling or low level Int \" error");  
        }    
    }    
    
    //
    // GPIOC int enable test
    //
    for(i = 0; i < 6; i++)
    {
        xGPIOPinIntEnable(xGPIO_PORTC_BASE, xGPIO_PIN_2, ulIntType[i]);
        if(ulIntType[i] & 0x10)
        { 
            ulTemp = xHWREG(xGPIO_PORTC_BASE + GPIO_IMD) & xGPIO_PIN_2;
            TestAssert(ulTemp == xGPIO_PIN_2,
                       "xgpio, \"Level INT type enable \" error");
        }
        else
        {
            ulTemp = xHWREG(xGPIO_PORTC_BASE + GPIO_IMD) & xGPIO_PIN_2;
            TestAssert(ulTemp == 0,
                       "xgpio, \"Edge INT type enable \" error");
        }
        if(ulIntType[i] & 2)
        {
            ulTemp = xHWREG(xGPIO_PORTC_BASE + GPIO_IEN) & (xGPIO_PIN_2 << 16);
            TestAssert(ulTemp == (xGPIO_PIN_2 << 16),
                       "xgpio, \"Rising or high level Int \" error");                    
        }
        if(ulIntType[i] & 1)
        {
            ulTemp = xHWREG(xGPIO_PORTC_BASE + GPIO_IEN) & xGPIO_PIN_2;
            TestAssert(ulTemp ==xGPIO_PIN_2,
                       "xgpio, \"Falling or low level Int \" error");  
        }    
    }   
    
    //
    // GPIOD int enable test
    //
    for(i = 0; i < 6; i++)
    {
        xGPIOPinIntEnable(xGPIO_PORTD_BASE, xGPIO_PIN_6, ulIntType[i]);
        if(ulIntType[i] & 0x10)
        { 
            ulTemp = xHWREG(xGPIO_PORTD_BASE + GPIO_IMD) & xGPIO_PIN_6;
            TestAssert(ulTemp == xGPIO_PIN_6,
                       "xgpio, \"Level INT type enable \" error");
        }
        else
        {
            ulTemp = xHWREG(xGPIO_PORTD_BASE + GPIO_IMD) & xGPIO_PIN_6;
            TestAssert(ulTemp == 0,
                       "xgpio, \"Edge INT type enable \" error");
        }
        if(ulIntType[i] & 2)
        {
            ulTemp = xHWREG(xGPIO_PORTD_BASE + GPIO_IEN) & (xGPIO_PIN_6 << 16);
            TestAssert(ulTemp == (xGPIO_PIN_6 << 16),
                       "xgpio, \"Rising or high level Int \" error");                    
        }
        if(ulIntType[i] & 1)
        {
            ulTemp = xHWREG(xGPIO_PORTD_BASE + GPIO_IEN) & xGPIO_PIN_6;
            TestAssert(ulTemp ==xGPIO_PIN_6,
                       "xgpio, \"Falling or low level Int \" error");  
        }    
    }  
    
    //
    // GPIOE int enable test
    //
    for(i = 0; i < 6; i++)
    {
        xGPIOPinIntEnable(xGPIO_PORTE_BASE, xGPIO_PIN_6, ulIntType[i]);
        if(ulIntType[i] & 0x10)
        { 
            ulTemp = xHWREG(xGPIO_PORTE_BASE + GPIO_IMD) & xGPIO_PIN_6;
            TestAssert(ulTemp == xGPIO_PIN_6,
                       "xgpio, \"Level INT type enable \" error");
        }
        else
        {
            ulTemp = xHWREG(xGPIO_PORTE_BASE + GPIO_IMD) & xGPIO_PIN_6;
            TestAssert(ulTemp == 0,
                       "xgpio, \"Edge INT type enable \" error");
        }
        if(ulIntType[i] & 2)
        {
            ulTemp = xHWREG(xGPIO_PORTE_BASE + GPIO_IEN) & (xGPIO_PIN_6 << 16);
            TestAssert(ulTemp == (xGPIO_PIN_6 << 16),
                       "xgpio, \"Rising or high level Int \" error");                    
        }
        if(ulIntType[i] & 1)
        {
            ulTemp = xHWREG(xGPIO_PORTE_BASE + GPIO_IEN) & xGPIO_PIN_6;
            TestAssert(ulTemp ==xGPIO_PIN_6,
                       "xgpio, \"Falling or low level Int \" error");  
        }    
    }     
    
    //
    // GPIOF int enable test
    //
    for(i = 0; i < 6; i++)
    {
        xGPIOPinIntEnable(xGPIO_PORTF_BASE, xGPIO_PIN_5, ulIntType[i]);
        if(ulIntType[i] & 0x10)
        { 
            ulTemp = xHWREG(xGPIO_PORTF_BASE + GPIO_IMD) & xGPIO_PIN_5;
            TestAssert(ulTemp == xGPIO_PIN_5,
                       "xgpio, \"Level INT type enable \" error");
        }
        else
        {
            ulTemp = xHWREG(xGPIO_PORTF_BASE + GPIO_IMD) & xGPIO_PIN_5;
            TestAssert(ulTemp == 0,
                       "xgpio, \"Edge INT type enable \" error");
        }
        if(ulIntType[i] & 2)
        {
            ulTemp = xHWREG(xGPIO_PORTF_BASE + GPIO_IEN) & (xGPIO_PIN_5 << 16);
            TestAssert(ulTemp == (xGPIO_PIN_5 << 16),
                       "xgpio, \"Rising or high level Int \" error");                    
        }
        if(ulIntType[i] & 1)
        {
            ulTemp = xHWREG(xGPIO_PORTF_BASE + GPIO_IEN) & xGPIO_PIN_5;
            TestAssert(ulTemp ==xGPIO_PIN_5,
                       "xgpio, \"Falling or low level Int \" error");  
        }    
    }  
    
    //
    // Interrupt disable test
    //
    for(ulPort = 0; ulPort < 6; ulPort++)
    {
        for(ulPin = 0; ulPin < 8; ulPin++)
        {
            xGPIOPinIntDisable(ulGPIO[ulPort], ulPackedPin[ulPin]);
            ulTemp = xHWREG(ulGPIO[ulPort] + GPIO_IEN) & (ulPackedPin[ulPin] << 16);
            ulTemp1 = xHWREG(ulGPIO[ulPort] + GPIO_IEN) & ulPackedPin[ulPin];
            ulTemp |= ulTemp1;
            TestAssert(ulTemp == 0,
                       "xgpio, \"Interrupt disable test \" error"); 
        }
    }
    
    //
    // GPIOA out/in test
    //
    xGPIODirModeSet( xGPIO_PORTA_BASE, xGPIO_PIN_0, GPIO_DIR_MODE_OUT );
    xGPIOPinWrite(xGPIO_PORTA_BASE, xGPIO_PIN_0, 1);
    ulTemp = xHWREG(xGPIO_PORTA_BASE + GPIO_DOUT) & xGPIO_PIN_0;
    TestAssert(ulTemp == xGPIO_PIN_0,
               "xgpio, \"Output pin value set \" error");   
    
    //
    // GPIOB out/in test
    //
    xGPIODirModeSet( xGPIO_PORTB_BASE, xGPIO_PIN_0, GPIO_DIR_MODE_OUT );
    xGPIOPinWrite(xGPIO_PORTB_BASE, xGPIO_PIN_0, 1);
    ulTemp = xHWREG(xGPIO_PORTB_BASE + GPIO_DOUT) & xGPIO_PIN_0;
    TestAssert(ulTemp == xGPIO_PIN_0,
               "xgpio, \"Output pin value set \" error");
    
    //
    // GPIOC out/in test
    //
    xGPIODirModeSet( xGPIO_PORTC_BASE, xGPIO_PIN_2, GPIO_DIR_MODE_OUT );
    xGPIOPinWrite(xGPIO_PORTC_BASE, xGPIO_PIN_2, 1);
    ulTemp = xHWREG(xGPIO_PORTC_BASE + GPIO_DOUT) & xGPIO_PIN_2;
    TestAssert(ulTemp == xGPIO_PIN_2,
               "xgpio, \"Output pin value set \" error");
    
    //
    // GPIOD out/in test
    //
    xGPIODirModeSet( xGPIO_PORTD_BASE, xGPIO_PIN_2, GPIO_DIR_MODE_OUT );
    xGPIOPinWrite(xGPIO_PORTD_BASE, xGPIO_PIN_2, 1);
    ulTemp = xHWREG(xGPIO_PORTD_BASE + GPIO_DOUT) & xGPIO_PIN_2;
    TestAssert(ulTemp == xGPIO_PIN_2,
               "xgpio, \"Output pin value set \" error");
    
    //
    // GPIOE out/in test
    //
    xGPIODirModeSet( xGPIO_PORTE_BASE, xGPIO_PIN_6, GPIO_DIR_MODE_OUT );
    xGPIOPinWrite(xGPIO_PORTE_BASE, xGPIO_PIN_6, 1);
    ulTemp = xHWREG(xGPIO_PORTE_BASE + GPIO_DOUT) & xGPIO_PIN_6;
    TestAssert(ulTemp == xGPIO_PIN_6,
               "xgpio, \"Output pin value set \" error"); 
    
    //
    // GPIOF out/in test
    //
    xGPIODirModeSet( xGPIO_PORTF_BASE, xGPIO_PIN_2, GPIO_DIR_MODE_OUT );
    xGPIOPinWrite(xGPIO_PORTF_BASE, xGPIO_PIN_2, 1);
    ulTemp = xHWREG(xGPIO_PORTF_BASE + GPIO_DOUT) & xGPIO_PIN_2;
    TestAssert(ulTemp == xGPIO_PIN_2,
               "xgpio, \"Output pin value set \" error"); 
      
    //
    // GPIOA De-bounce enable test
    //
    GPIOPinDebounceEnable(xGPIO_PORTA_BASE, xGPIO_PIN_0);
    ulTemp = xHWREG(xGPIO_PORTA_BASE + GPIO_DBEN) & xGPIO_PIN_0;
    TestAssert(ulTemp == xGPIO_PIN_0,
               "xgpio, \"De-bounce enable test \" error");  
    
    //
    // GPIOB De-bounce enable test
    //
    GPIOPinDebounceEnable(xGPIO_PORTB_BASE, xGPIO_PIN_0);
    ulTemp = xHWREG(xGPIO_PORTB_BASE + GPIO_DBEN) & xGPIO_PIN_0;
    TestAssert(ulTemp == xGPIO_PIN_0,
               "xgpio, \"De-bounce enable test \" error");  
    
    //
    // GPIOC De-bounce enable test
    //
    GPIOPinDebounceEnable(xGPIO_PORTC_BASE, xGPIO_PIN_2);
    ulTemp = xHWREG(xGPIO_PORTC_BASE + GPIO_DBEN) & xGPIO_PIN_2;
    TestAssert(ulTemp == xGPIO_PIN_2,
               "xgpio, \"De-bounce enable test \" error");
    
    //
    // GPIOD De-bounce enable test
    //
    GPIOPinDebounceEnable(xGPIO_PORTD_BASE, xGPIO_PIN_6);
    ulTemp = xHWREG(xGPIO_PORTD_BASE + GPIO_DBEN) & xGPIO_PIN_6;
    TestAssert(ulTemp == xGPIO_PIN_6,
               "xgpio, \"De-bounce enable test \" error");
    
    //
    // GPIOE De-bounce enable test
    //
    GPIOPinDebounceEnable(xGPIO_PORTE_BASE, xGPIO_PIN_6);
    ulTemp = xHWREG(xGPIO_PORTE_BASE + GPIO_DBEN) & xGPIO_PIN_6;
    TestAssert(ulTemp == xGPIO_PIN_6,
               "xgpio, \"De-bounce enable test \" error");
    
    //
    // GPIOE De-bounce enable test
    //
    GPIOPinDebounceEnable(xGPIO_PORTF_BASE, xGPIO_PIN_0);
    ulTemp = xHWREG(xGPIO_PORTF_BASE + GPIO_DBEN) & xGPIO_PIN_0;
    TestAssert(ulTemp == xGPIO_PIN_0,
               "xgpio, \"De-bounce enable test \" error");  
    
    //
    // GPIOA mask set/get test
    //
    GPIOPinMaskSet(xGPIO_PORTA_BASE, xGPIO_PIN_0);
    ulTemp = GPIOPortMaskGet(xGPIO_PORTA_BASE) & xGPIO_PIN_0;     
    TestAssert(ulTemp == xGPIO_PIN_0,
               "xgpio, \" Mask set/get test \" error"); 
    
    //
    // GPIOB mask set/get test
    //    
    GPIOPinMaskSet(xGPIO_PORTB_BASE, xGPIO_PIN_0);
    ulTemp = GPIOPortMaskGet(xGPIO_PORTB_BASE) & xGPIO_PIN_0;     
    TestAssert(ulTemp == xGPIO_PIN_0,
               "xgpio, \" Mask set/get test \" error"); 
    
    //
    // GPIOC mask set/get test
    //
    GPIOPinMaskSet(xGPIO_PORTC_BASE, xGPIO_PIN_2);
    ulTemp = GPIOPortMaskGet(xGPIO_PORTC_BASE) & xGPIO_PIN_2;     
    TestAssert(ulTemp == xGPIO_PIN_2,
               "xgpio, \" Mask set/get test \" error"); 
    
    //
    // GPIOD mask set/get test
    //
    GPIOPinMaskSet(xGPIO_PORTD_BASE, xGPIO_PIN_2);
    ulTemp = GPIOPortMaskGet(xGPIO_PORTD_BASE) & xGPIO_PIN_2;     
    TestAssert(ulTemp == xGPIO_PIN_2,
               "xgpio, \" Mask set/get test \" error"); 
    
    //
    // GPIOE mask set/get test
    //
    GPIOPinMaskSet(xGPIO_PORTE_BASE, xGPIO_PIN_6);
    ulTemp = GPIOPortMaskGet(xGPIO_PORTE_BASE) & xGPIO_PIN_6;     
    TestAssert(ulTemp == xGPIO_PIN_6,
               "xgpio, \" Mask set/get test \" error"); 
    
    
    //
    // GPIOF mask set/get test
    //
    GPIOPinMaskSet(xGPIO_PORTF_BASE, xGPIO_PIN_2);
    ulTemp = GPIOPortMaskGet(xGPIO_PORTF_BASE) & xGPIO_PIN_2;     
    TestAssert(ulTemp == xGPIO_PIN_2,
               "xgpio, \" Mask set/get test \" error");     
    
    //
    // De-bounce time set and get test
    //
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 3; j++)
        {
            GPIODebounceTimeSet(ulDelay[i], ulDelayCycle[j]);
            ulTemp = xHWREG(GPIO_DBNCECON) & 0x10;
            if(i == 0)
            {
                TestAssert(ulTemp == 0,
                           "xgpio, \" De-bounce source set \" error");  
            }
            else
            {  
                TestAssert(ulTemp == 0x10,
                           "xgpio, \" De-bounce source set \" error");  
            }
            ulTemp1 = GPIODebounceTimeGet();
            TestAssert(ulTemp1 == ulDelayCycle[j],
                       "xgpio, \" De-bounce cycle test \" error");  
        }
    }
    
    //
    // Pin to peripheral ID test
    //
    ulTemp = xGPIOSPinToPeripheralId(PA0);
    TestAssert(ulTemp == ulPeripheralID[0],
               "xgpio, \" Pin to peripheral ID test \" error");  
    
    //
    // Short pin to pin test
    //
    ulTemp = xGPIOSPinToPin(PA0);
    TestAssert(ulTemp == ulPinValue[0],
               "xgpio, \" Short pin to pin test \" error");  
    ulTemp = xGPIOSPinToPin(PA1);
    TestAssert(ulTemp == ulPinValue[1],
               "xgpio, \" Short pin to pin test \" error");        
    ulTemp = xGPIOSPinToPin(PA2);
    TestAssert(ulTemp == ulPinValue[2],
               "xgpio, \" Short pin to pin test \" error");   
    
    //
    // Short pin dir mode set test
    //
    for(i = 0; i < 4; i++)
    {
        xGPIOSPinDirModeSet(PA0, ulPinMode[i]);
        ulTemp = xGPIODirModeGet(xGPIO_PORTA_BASE, GPIO_PIN_0);
        TestAssert(ulTemp == ulPinMode[i],
                   "xgpio, \" Short pin dir mode set test \" error");       
    }
    
    //
    // Short pin interrupt enable
    //
    for(i = 0; i < 6; i++)
    {
        xGPIOSPinIntEnable(PA0, ulIntType[i]);
        if(ulIntType[i] & 0x10)
        { 
            ulTemp = xHWREG(xGPIO_PORTA_BASE + GPIO_IMD) & GPIO_PIN_0;
            TestAssert(ulTemp == GPIO_PIN_0,
                       "xgpio, \"ShortPin INT type enable \" error");
        }
        else
        {
            ulTemp = xHWREG(xGPIO_PORTA_BASE + GPIO_IMD) & GPIO_PIN_0;
            TestAssert(ulTemp == 0,
                       "xgpio, \"ShortPin INT type enable \" error");
        }
        if(ulIntType[i] & 2)
        {
            ulTemp = xHWREG(xGPIO_PORTA_BASE + GPIO_IEN) & (GPIO_PIN_0 << 16);
            TestAssert(ulTemp == (GPIO_PIN_0 << 16),
                       "xgpio, \"ShortPin INT type enable \" error");                    
        }
        if(ulIntType[i] & 1)
        {
            ulTemp = xHWREG(xGPIO_PORTA_BASE + GPIO_IEN) & GPIO_PIN_0;
            TestAssert(ulTemp == GPIO_PIN_0,
                       "xgpio, \"ShortPin INT type enable \" error");  
        }
    }
    
    //
    // Short pin interrupt disable
    // 
    xGPIOSPinIntDisable(PA0);
    ulTemp = xHWREG(xGPIO_PORTA_BASE + GPIO_IEN) & (GPIO_PIN_0 << 16);
    ulTemp1 = xHWREG(xGPIO_PORTA_BASE + GPIO_IEN) & GPIO_PIN_0;
    ulTemp |= ulTemp1;
    TestAssert(ulTemp == 0,
               "xgpio, \"Short pin interrupt disable \" error"); 
    
    //
    // Short pin write test
    //
    xGPIOSPinWrite(PA0, 1);
    ulTemp = xHWREG(xGPIO_PORTA_BASE + GPIO_DOUT) & GPIO_PIN_0;
    TestAssert(ulTemp == GPIO_PIN_0,
               "xgpio, \"Short pin write test \" error"); 
    
    //
    // Ture pin to ADC function
    //    
    xSPinTypeADC(ADC0, PF3);
    ulTemp = xHWREG(GCR_GPFMFP) & GCR_GPFMFP_MFP3;
    ulTemp1 = xHWREG(GCR_GPFMFP) & GCR_GPFMFP_ALT3;
    TestAssert((ulTemp == GCR_GPFMFP_MFP3) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to ADC AIN0 \" error");      
    
    xSPinTypeADC(ADC1, PB0);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP0;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT0;
    TestAssert((ulTemp == GCR_GPBMFP_MFP0) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to ADC AIN1 \" error");  
    
    xSPinTypeADC(ADC2, PB2);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP2;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT2;
    TestAssert((ulTemp == GCR_GPBMFP_MFP2) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to ADC AIN2 \" error");     

    xSPinTypeADC(ADC3, PB3);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP3;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT3;
    TestAssert((ulTemp == GCR_GPBMFP_MFP3) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to ADC AIN3 \" error"); 
    
    xSPinTypeADC(ADC4, PB4);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP4;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT4;
    TestAssert((ulTemp == GCR_GPBMFP_MFP4) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to ADC AIN4 \" error");  
    
    xSPinTypeADC(ADC5, PB5);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP5;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT5;
    TestAssert((ulTemp == GCR_GPBMFP_MFP5) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to ADC AIN5 \" error"); 
    
    xSPinTypeADC(ADC6, PD0);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP0;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT0;
    TestAssert((ulTemp == GCR_GPDMFP_MFP0) && (ulTemp1 == GCR_GPDMFP_ALT0),
               "xgpio, \"Turn pin to ADC AIN6 \" error");    
    
    xSPinTypeADC(ADC7, PD1);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP1;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT1;
    TestAssert((ulTemp == GCR_GPDMFP_MFP1) && (ulTemp1 == GCR_GPDMFP_ALT1),
               "xgpio, \"Turn pin to ADC AIN7 \" error"); 
    
    //
    // Ture pin to I2C function
    //    
    xSPinTypeI2C(I2C0SDA, PD4);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP4;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT4;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPDMFP_ALT4),
               "xgpio, \"Turn pin to I2C SCK \" error");      
    
    xSPinTypeI2C(I2C0SCK, PD5);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP5;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT5;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPDMFP_ALT5),
               "xgpio, \"Turn pin to I2C SDA \" error");           
    
    //
    // Turn pin to pwm mode
    //
    xSPinTypePWM(PWM0, PC2);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP2;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT2;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT2),
               "xgpio, \"Turn pin to PWM function \" error");    
   
    xSPinTypePWM(PWM1, PC3);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP3;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT3;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT3),
               "xgpio, \"Turn pin to PWM function \" error");
    
    xSPinTypePWM(PWM2, PC4);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP4;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT4;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT4),
               "xgpio, \"Turn pin to PWM function \" error");    
    
    xSPinTypePWM(PWM3, PC5);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP5;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT5;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT5),
               "xgpio, \"Turn pin to PWM function \" error");       
    
    xSPinTypePWM(PWM4, PC6);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP6;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT6;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT6),
               "xgpio, \"Turn pin to PWM function \" error");   

    xSPinTypePWM(PWM5, PA4);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP5;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT5;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT5),
               "xgpio, \"Turn pin to PWM function \" error");       

    //
    // Turn pin to spi function test
    //
    xSPinTypeSPI(SPI0CLK, PA7);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP7;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT7;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPAMFP_ALT7),
               "xgpio, \"Turn pin to SPI function \" error");      

    xSPinTypeSPI(SPI0MOSI, PA5);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP5;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT5;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPAMFP_ALT5),
               "xgpio, \"Turn pin to SPI function \" error");    

    xSPinTypeSPI(SPI0MISO, PA6);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP6;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT6;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPAMFP_ALT6),
               "xgpio, \"Turn pin to SPI function \" error"); 
    
    xSPinTypeSPI(SPI0CS, PA4);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP4;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT4;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPAMFP_ALT4),
               "xgpio, \"Turn pin to SPI function \" error");     
    
    xSPinTypeSPI(SPI0CS, PA1);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP1;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT1;    
    TestAssert((ulTemp == GCR_GPAMFP_MFP1) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to SPI function \" error"); 
    
    //
    // Turn pin to timer function test
    //
    xSPinTypeTimer(TIMCCP0, PD4);   
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP4;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT4;    
    TestAssert((ulTemp == GCR_GPDMFP_MFP4) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to TIMER function \" error");    

    xSPinTypeTimer(TIMCCP1, PD5);   
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP5;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT5;    
    TestAssert((ulTemp == GCR_GPDMFP_MFP5) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to TIMER function \" error");      
    
    xSPinTypeTimer(T0EX, PD2);   
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP2;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT2;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPDMFP_ALT2),
               "xgpio, \"Turn pin to TIMER function \" error");  
    
    xSPinTypeTimer(T1EX, PD6);   
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP6;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT6;    
    TestAssert((ulTemp == GCR_GPDMFP_MFP6) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to TIMER function \" error");  
    
    // 
    // Turn pin to uart function test
    //
    xSPinTypeUART(UART0RX, PB2);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP2;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT2;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPBMFP_ALT2),
               "xgpio, \"Turn pin to UART function \" error");  

    xSPinTypeUART(UART0TX, PB3);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP3;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT3;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPBMFP_ALT3),
               "xgpio, \"Turn pin to UART function \" error");          
    
    xSPinTypeUART(UART0RX, PA1);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP1;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT1;    
    TestAssert((ulTemp == GCR_GPAMFP_MFP1) && (ulTemp1 == GCR_GPAMFP_ALT1),
               "xgpio, \"Turn pin to UART function \" error");
  
    xSPinTypeUART(UART0TX, PA0);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP0;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT0;    
    TestAssert((ulTemp == GCR_GPAMFP_MFP0) && (ulTemp1 == GCR_GPAMFP_ALT0),
               "xgpio, \"Turn pin to UART function \" error");    
    
    xSPinTypeUART(UART0RTS, PA1);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP1;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT1;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPAMFP_ALT1),
               "xgpio, \"Turn pin to UART function \" error");  
    
    xSPinTypeUART(UART0CTS, PA0);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP0;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT0;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPAMFP_ALT0),
               "xgpio, \"Turn pin to UART function \" error");  
    
    //
    // Turn the pin to ACMP function
    //
    xSPinTypeACMP(CMP0P, PB5);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP5;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT5;    
    TestAssert((ulTemp == GCR_GPBMFP_MFP5) && (ulTemp1 == GCR_GPBMFP_ALT5),
               "xgpio, \"Turn pin to ACMP function \" error");  
    
    xSPinTypeACMP(CMP0N, PB4);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP4;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT4;    
    TestAssert((ulTemp == GCR_GPBMFP_MFP4) && (ulTemp1 == GCR_GPBMFP_ALT4),
               "xgpio, \"Turn pin to ACMP function \" error");       

    xSPinTypeACMP(CMP0O, PD6);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP6;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT6;    
    TestAssert((ulTemp == GCR_GPDMFP_MFP6) && (ulTemp1 == GCR_GPDMFP_ALT6),
               "xgpio, \"Turn pin to ACMP function \" error");     

    xSPinTypeACMP(CMP1P, PD1);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP1;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT1;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPDMFP_ALT1),
               "xgpio, \"Turn pin to ACMP function \" error"); 

    xSPinTypeACMP(CMP1N, PD0);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP0;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT0;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPDMFP_ALT0),
               "xgpio, \"Turn pin to ACMP function \" error"); 

    xSPinTypeACMP(CMP1O, PC6);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP6;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT6;    
    TestAssert((ulTemp == GCR_GPCMFP_MFP6) && (ulTemp1 == GCR_GPCMFP_ALT6),
               "xgpio, \"Turn pin to ACMP function \" error"); 
    
    //
    // Turn pin to INT function
    //
    xSPinTypeEXTINT(NINT0, PD2);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP2;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT2;    
    TestAssert((ulTemp == GCR_GPDMFP_MFP2) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to INT function \" error");     
    
    xSPinTypeEXTINT(NINT1, PF2);
    ulTemp = xHWREG(GCR_GPFMFP) & GCR_GPFMFP_MFP2;
    ulTemp1 = xHWREG(GCR_GPFMFP) & GCR_GPFMFP_ALT2;    
    TestAssert((ulTemp == GCR_GPFMFP_MFP2) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to INT function \" error");    
    
    //
    // Turn pin to CLKO function
    //
    xSPinTypeCLKO(CLK0, PD6);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP6;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT6;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPDMFP_ALT6),
               "xgpio, \"Turn pin to CLKO function \" error");    
}   

//
// xgpio001 register test case struct.
//
const tTestCase sTestxGpio001Register = {
    xgpio001GetTest,
    xgpio001Setup,
    xgpio001TearDown,
    xgpio001Execute
};

//
// Xgpio test suits.
//
const tTestCase * const psPatternxgpio1[] =
{
    &sTestxGpio001Register,
    0
};
