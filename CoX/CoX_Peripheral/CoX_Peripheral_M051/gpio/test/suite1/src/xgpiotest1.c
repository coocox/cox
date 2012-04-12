//*****************************************************************************
//
//! @page xgpio_testcase xgpio register test
//!
//! File: @ref xgpiotest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xgpio sub component.<br><br>
//! - \p Board: NUC140 <br><br>
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
static unsigned long ulGPIO[5] = {xGPIO_PORTA_BASE,xGPIO_PORTB_BASE,
                                  xGPIO_PORTC_BASE,xGPIO_PORTD_BASE,
                                  xGPIO_PORTE_BASE};

//
//
//
static unsigned long ulPackedPin[16] = {xGPIO_PIN_0, xGPIO_PIN_1, xGPIO_PIN_2,
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
                                     xGPIO_BOTH_EDGES, xGPIO_BOTH_LEVEL,
                                     xGPIO_LOW_LEVEL, xGPIO_HIGH_LEVEL};

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
    // GPIO mode set and get. 
    //
    for(ulPort = 0; ulPort < 5; ulPort++)
    {
        for(ulPin = 0; ulPin < 8; ulPin++)
        {        
            for(i = 0; i < 4; i++)
            {
              //  if(ulPort != 1 && ulPort != 3)
              //  {
                    xGPIODirModeSet(ulGPIO[ulPort], ulPackedPin[ulPin], ulPinMode[i]);        
                    ulvalue = xGPIODirModeGet(ulGPIO[ulPort], ulPackedPin[ulPin]);
                    TestAssert((ulvalue == ulPinMode[i]), 
                                "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
              //  }
            }
        }
    }
    
    xIntDisable(xINT_GPIOA);
    xIntDisable(xINT_GPIOB);
    xIntDisable(xINT_GPIOC);
    xIntDisable(xINT_GPIOD);  
    xIntDisable(xINT_GPIOE);
    
    //
    // Interrupt enable.
    //
    for(ulPort = 0; ulPort < 5; ulPort++)
    {
        for(ulPin = 0; ulPin < 8; ulPin++)
        { 
            for(i = 0; i < 6; i++)
            {
                xGPIOPinIntEnable(ulGPIO[ulPort], ulPackedPin[ulPin], ulIntType[i]);
                if(ulIntType[i] & 0x10)
                { 
                    ulTemp = xHWREG(ulGPIO[ulPort] + GPIO_IMD) & ulPackedPin[ulPin];
                    TestAssert(ulTemp == ulPackedPin[ulPin],
                               "xgpio, \"Level INT type enable \" error");
                }
                else
                {
                    ulTemp = xHWREG(ulGPIO[ulPort] + GPIO_IMD) & ulPackedPin[ulPin];
                    TestAssert(ulTemp == 0,
                               "xgpio, \"Edge INT type enable \" error");
                }
                if(ulIntType[i] & 2)
                {
                    ulTemp = xHWREG(ulGPIO[ulPort] + GPIO_IEN) & (ulPackedPin[ulPin] << 16);
                    TestAssert(ulTemp == (ulPackedPin[ulPin] << 16),
                               "xgpio, \"Rising or high level Int \" error");                    
                }
                if(ulIntType[i] & 1)
                {
                    ulTemp = xHWREG(ulGPIO[ulPort] + GPIO_IEN) & ulPackedPin[ulPin];
                    TestAssert(ulTemp == ulPackedPin[ulPin],
                               "xgpio, \"Falling or low level Int \" error");  
                }
            }
        }
    }
   
    //
    // Interrupt disable test
    //
    for(ulPort = 0; ulPort < 4; ulPort++)
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
    // Pin Out/in value test
    //
    for(ulPort = 0; ulPort < 5; ulPort++)
    {
        //
        // Output pin value set
        //
        for(ulPin = 0; ulPin < 8; ulPin++)
        {
            xGPIODirModeSet( ulGPIO[ulPort], ulPackedPin[ulPin], GPIO_DIR_MODE_OUT );
            xGPIOPinWrite(ulGPIO[ulPort], ulPackedPin[ulPin], 1);
            ulTemp = xHWREG(ulGPIO[ulPort] + GPIO_DOUT) & ulPackedPin[ulPin];
            TestAssert(ulTemp == ulPackedPin[ulPin],
                       "xgpio, \"Output pin value set \" error"); 
        }    
    }
    
    //
    // De-bounce enable/disable test
    //
    for(ulPort = 0; ulPort < 5; ulPort++)
    {
        //
        // De-bounce enable test
        //
        for(ulPin = 0; ulPin < 8; ulPin++)
        {
            GPIOPinDebounceEnable(ulGPIO[ulPort], ulPackedPin[ulPin]);
            ulTemp = xHWREG(ulGPIO[ulPort] + GPIO_DBEN) & ulPackedPin[ulPin];
            TestAssert(ulTemp == ulPackedPin[ulPin],
                       "xgpio, \"De-bounce enable test \" error");  
        }   
        
        //
        // De-bounce disable test
        //
        for(ulPin = 0; ulPin < 8; ulPin++)
        {
            GPIOPinDebounceDisable(ulGPIO[ulPort], ulPackedPin[ulPin]);
            ulTemp = xHWREG(ulGPIO[ulPort] + GPIO_DBEN) & ulPackedPin[ulPin];
            TestAssert(ulTemp == 0,
                       "xgpio, \"De-bounce Disable test \" error");  
        }  
    }
    
    //
    // Mask set/get test
    // 
    for(ulPort = 0; ulPort < 4; ulPort++)
    {
        for(ulPin = 0; ulPin < 8; ulPin++)
        {
            GPIOPinMaskSet(ulGPIO[ulPort], ulPackedPin[ulPin]);
            ulTemp = GPIOPortMaskGet(ulGPIO[ulPort]) & ulPackedPin[ulPin];     
            TestAssert(ulTemp == ulPackedPin[ulPin],
                       "xgpio, \" Mask set/get test \" error");  
        }
    }
    
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
    xSPinTypeADC(ADC0, PB0);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP0;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT0;
    TestAssert((ulTemp == GCR_GPBMFP_MFP0) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to ADC AIN0 \" error");      
    
    xSPinTypeADC(ADC1, PB1);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP1;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT1;
    TestAssert((ulTemp == GCR_GPBMFP_MFP1) && (ulTemp1 == 0),
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
    
    xSPinTypeADC(ADC6, PB6);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP6;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT6;
    TestAssert((ulTemp == GCR_GPBMFP_MFP6) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to ADC AIN6 \" error");    
    
    xSPinTypeADC(ADC7, PB7);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP7;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT7;
    TestAssert((ulTemp == GCR_GPBMFP_MFP7) && (ulTemp1 == 0),
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
    xSPinTypePWM(PWM0, PC0);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP0;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT0;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT0),
               "xgpio, \"Turn pin to PWM function \" error");    
   
    xSPinTypePWM(PWM1, PC1);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP1;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT1;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT1),
               "xgpio, \"Turn pin to PWM function \" error");
    
    xSPinTypePWM(PWM2, PC2);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP2;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT2;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT2),
               "xgpio, \"Turn pin to PWM function \" error");    
    
    xSPinTypePWM(PWM3, PC3);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP3;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT3;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT3),
               "xgpio, \"Turn pin to PWM function \" error");       

    xSPinTypePWM(PWM0, PE0);
    ulTemp = xHWREG(GCR_GPEMFP) & GCR_GPEMFP_MFP0;
    ulTemp1 = xHWREG(GCR_GPEMFP) & GCR_GPEMFP_ALT0;
    TestAssert((ulTemp == GCR_GPEMFP_MFP0) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to PWM function \" error");
    
    xSPinTypePWM(PWM1, PE1);
    ulTemp = xHWREG(GCR_GPEMFP) & GCR_GPEMFP_MFP1;
    ulTemp1 = xHWREG(GCR_GPEMFP) & GCR_GPEMFP_ALT1;
    TestAssert((ulTemp == GCR_GPEMFP_MFP1) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to PWM function \" error");    

    xSPinTypePWM(PWM2, PE2);
    ulTemp = xHWREG(GCR_GPEMFP) & GCR_GPEMFP_MFP2;
    TestAssert((ulTemp == GCR_GPEMFP_MFP2),
               "xgpio, \"Turn pin to PWM function \" error");
    
    xSPinTypePWM(PWM3, PE3);
    ulTemp = xHWREG(GCR_GPEMFP) & GCR_GPEMFP_MFP3;
    TestAssert((ulTemp == GCR_GPEMFP_MFP3),
               "xgpio, \"Turn pin to PWM function \" error");    
    
    xSPinTypePWM(PWM4, PC4);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP4;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT4;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT4),
               "xgpio, \"Turn pin to PWM function \" error");   

    xSPinTypePWM(PWM5, PC5);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP5;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT5;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT5),
               "xgpio, \"Turn pin to PWM function \" error");       

    xSPinTypePWM(PWM6, PC6);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP6;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT6;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT6),
               "xgpio, \"Turn pin to PWM function \" error"); 

    xSPinTypePWM(PWM7, PC7);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP7;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT7;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT7),
               "xgpio, \"Turn pin to PWM function \" error"); 
    
    //
    // Turn pin to spi function test
    //
    xSPinTypeSPI(SPI0CLK, PB7);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP7;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT7;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT7),
               "xgpio, \"Turn pin to SPI function \" error");      

    xSPinTypeSPI(SPI0MOSI, PB5);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP5;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT5;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT5),
               "xgpio, \"Turn pin to SPI function \" error");    

    xSPinTypeSPI(SPI0MISO, PB6);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP6;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT6;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT6),
               "xgpio, \"Turn pin to SPI function \" error"); 
    
    xSPinTypeSPI(SPI0CS, PB4);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP4;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT4;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT4),
               "xgpio, \"Turn pin to SPI function \" error");     
    
    xSPinTypeSPI(SPI1CLK, PA7);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP7;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT7;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPAMFP_ALT7),
               "xgpio, \"Turn pin to SPI function \" error");     
    
    xSPinTypeSPI(SPI1MOSI, PA5);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP5;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT5;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPAMFP_ALT5),
               "xgpio, \"Turn pin to SPI function \" error");     
    
    xSPinTypeSPI(SPI1MISO, PA6);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP6;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT6;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPAMFP_ALT6),
               "xgpio, \"Turn pin to SPI function \" error");    
    
    xSPinTypeSPI(SPI1CS, PA4);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP4;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT4;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPAMFP_ALT4),
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
    
    xSPinTypeTimer(TIMCCP2, PB0);   
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP0;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT0;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPBMFP_ALT0),
               "xgpio, \"Turn pin to TIMER function \" error");  
    
    xSPinTypeTimer(TIMCCP3, PB1);   
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP1;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT1;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPBMFP_ALT1),
               "xgpio, \"Turn pin to TIMER function \" error"); 
    
    // 
    // Turn pin to uart function test
    //
    xSPinTypeUART(UART0RX, PD0);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP0;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT0;    
    TestAssert((ulTemp == GCR_GPDMFP_MFP0) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to UART function \" error");  
    
    xSPinTypeUART(UART0TX, PD1);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP1;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT1;    
    TestAssert((ulTemp == GCR_GPDMFP_MFP1) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to UART function \" error");      
    
    xSPinTypeUART(UART0RX, PA3);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP3;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT3;    
    TestAssert((ulTemp == GCR_GPAMFP_MFP3) && (ulTemp1 == GCR_GPAMFP_ALT3),
               "xgpio, \"Turn pin to UART function \" error");
  
    xSPinTypeUART(UART0TX, PA2);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP2;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT2;    
    TestAssert((ulTemp == GCR_GPAMFP_MFP2) && (ulTemp1 == GCR_GPAMFP_ALT2),
               "xgpio, \"Turn pin to UART function \" error");    
    
    xSPinTypeUART(UART0RTS, PA3);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP3;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT3;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPAMFP_ALT3),
               "xgpio, \"Turn pin to UART function \" error");  
    
    xSPinTypeUART(UART0CTS, PA2);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP2;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT2;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPAMFP_ALT2),
               "xgpio, \"Turn pin to UART function \" error");  
    
    xSPinTypeUART(UART1CTS, PA0);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP0;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT0;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPAMFP_ALT0),
               "xgpio, \"Turn pin to UART function \" error");     

    xSPinTypeUART(UART1RTS, PA1);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP1;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT1;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPAMFP_ALT1),
               "xgpio, \"Turn pin to UART function \" error");  
    
    xSPinTypeUART(UART1RX, PA1);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP1;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT1;    
    TestAssert((ulTemp == GCR_GPAMFP_MFP1) && (ulTemp1 == GCR_GPAMFP_ALT1),
               "xgpio, \"Turn pin to UART function \" error");      
    
    xSPinTypeUART(UART1TX, PA0);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP0;
    ulTemp1 = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_ALT0;    
    TestAssert((ulTemp == GCR_GPAMFP_MFP0) && (ulTemp1 == GCR_GPAMFP_ALT0),
               "xgpio, \"Turn pin to UART function \" error");    
    
    xSPinTypeUART(UART1RX, PB2);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP2;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT2;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPBMFP_ALT2),
               "xgpio, \"Turn pin to UART function \" error");      
 
    xSPinTypeUART(UART1TX, PB3);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP3;
    ulTemp1 = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_ALT3;    
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPBMFP_ALT3),
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
/*
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
*/
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
    
    xSPinTypeEXTINT(NINT1, PD3);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP3;
    ulTemp1 = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_ALT3;    
    TestAssert((ulTemp == GCR_GPDMFP_MFP3) && (ulTemp1 == 0),
               "xgpio, \"Turn pin to INT function \" error");     
    
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
