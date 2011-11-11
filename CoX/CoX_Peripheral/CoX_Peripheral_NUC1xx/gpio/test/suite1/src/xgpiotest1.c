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
                                        xGPIO_PIN_6, xGPIO_PIN_7, xGPIO_PIN_8, 
                                        xGPIO_PIN_9, xGPIO_PIN_10, xGPIO_PIN_11, 
                                        xGPIO_PIN_12, xGPIO_PIN_13, xGPIO_PIN_14, 
                                        xGPIO_PIN_15};

//
// GPIO Pin Mode
//
static unsigned long ulPinMode[5] = {xGPIO_DIR_MODE_IN, xGPIO_DIR_MODE_OUT, 
                                     xGPIO_DIR_MODE_OD, xGPIO_DIR_MODE_QB,
                                     xGPIO_DIR_MODE_HW};

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
static unsigned long ulPinValue[3] = {GPIO_PIN_0, GPIO_PIN_8, GPIO_PIN_15};

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
        for(ulPin = 0; ulPin < 16; ulPin++)
        {        
            for(i = 0; i < 5; i++)
            {
                if(ulPort != 1 && ulPort != 3)
                {
                    xGPIODirModeSet(ulGPIO[ulPort], ulPackedPin[ulPin], ulPinMode[i]);        
                    ulvalue = xGPIODirModeGet(ulGPIO[ulPort], ulPackedPin[ulPin]);
                    TestAssert((ulvalue == ulPinMode[i]), 
                                "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
                }
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
        for(ulPin = 0; ulPin < 16; ulPin++)
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
    for(ulPort = 0; ulPort < 5; ulPort++)
    {
        for(ulPin = 0; ulPin < 16; ulPin++)
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
        for(ulPin = 0; ulPin < 16; ulPin++)
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
        for(ulPin = 0; ulPin < 16; ulPin++)
        {
            GPIOPinDebounceEnable(ulGPIO[ulPort], ulPackedPin[ulPin]);
            ulTemp = xHWREG(ulGPIO[ulPort] + GPIO_DBEN) & ulPackedPin[ulPin];
            TestAssert(ulTemp == ulPackedPin[ulPin],
                       "xgpio, \"De-bounce enable test \" error");  
        }   
        
        //
        // De-bounce disable test
        //
        for(ulPin = 0; ulPin < 16; ulPin++)
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
    for(ulPort = 0; ulPort < 5; ulPort++)
    {
        for(ulPin = 0; ulPin < 16; ulPin++)
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
    ulTemp = xGPIOSPinToPin(PB8);
    TestAssert(ulTemp == ulPinValue[1],
               "xgpio, \" Short pin to pin test \" error");        
    ulTemp = xGPIOSPinToPin(PE15);
    TestAssert(ulTemp == ulPinValue[2],
               "xgpio, \" Short pin to pin test \" error");   
    
    //
    // Short pin dir mode set test
    //
    for(i = 0; i < 5; i++)
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
    // Turn pin to gpio mode test
    //  
    xGPIOSPinTypeGPIOInput(PA0);
    ulTemp = xHWREG(GCR_GPAMFP) & GPIO_PIN_0;
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to gpio mode test \" error"); 
    
    //
    // Turn pin to ADC input function
    //
    xSPinTypeADC(ADC0, PA0);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP0;
    TestAssert(ulTemp == GCR_GPAMFP_MFP0,
               "xgpio, \"Turn pin to ADC0 input \" error");   
    
    xSPinTypeADC(ADC1, PA1);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP1;
    TestAssert(ulTemp == GCR_GPAMFP_MFP1,
               "xgpio, \"Turn pin to ADC1 input \" error"); 
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN | GCR_ALTMFP_EBI_HB_EN_4);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to ADC1 input \" error"); 
    
    xSPinTypeADC(ADC2, PA2);  
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP2;
    TestAssert(ulTemp == GCR_GPAMFP_MFP2,
               "xgpio, \"Turn pin to ADC2 input \" error"); 
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN | GCR_ALTMFP_EBI_HB_EN_3);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to ADC2 input \" error");    
    
    xSPinTypeADC(ADC3, PA3);  
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP3;
    TestAssert(ulTemp == GCR_GPAMFP_MFP3,
               "xgpio, \"Turn pin to ADC3 input \" error"); 
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN | GCR_ALTMFP_EBI_HB_EN_2);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to ADC3 input \" error");   
    
    xSPinTypeADC(ADC4, PA4);  
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP4;
    TestAssert(ulTemp == GCR_GPAMFP_MFP4,
               "xgpio, \"Turn pin to ADC4 input \" error"); 
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN | GCR_ALTMFP_EBI_HB_EN_1);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to ADC4 input \" error");
    
    xSPinTypeADC(ADC5, PA5);  
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP5;
    TestAssert(ulTemp == GCR_GPAMFP_MFP5,
               "xgpio, \"Turn pin to ADC5 input \" error"); 
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN | GCR_ALTMFP_EBI_HB_EN_0);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to ADC5 input \" error");
    
    xSPinTypeADC(ADC6, PA6);  
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP6;
    TestAssert(ulTemp == GCR_GPAMFP_MFP6,
               "xgpio, \"Turn pin to ADC6 input \" error"); 
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to ADC6 input \" error");
    
    xSPinTypeADC(ADC7, PA7);  
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP7;
    TestAssert(ulTemp == GCR_GPAMFP_MFP7,
               "xgpio, \"Turn pin to ADC7 input \" error"); 
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to ADC7 input \" error");    
    ulTemp = xHWREG(GCR_ALTMFP) & GCR_ALTMFP_PA7_S21;
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to ADC7 input \" error");   
    
    //
    // Ture pin to I2C function
    //
    xSPinTypeI2C(I2C0SCK, PA9);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP9;
    TestAssert(ulTemp == GCR_GPAMFP_MFP9,
               "xgpio, \"Turn pin to I2C input \" error");    
    
    xSPinTypeI2C(I2C0SDA, PA8);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP8;
    TestAssert(ulTemp == GCR_GPAMFP_MFP8,
               "xgpio, \"Turn pin to I2C input \" error");  
    
    xSPinTypeI2C(I2C1SCK, PA11);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP11;
    TestAssert(ulTemp == GCR_GPAMFP_MFP11,
               "xgpio, \"Turn pin to I2C input \" error");     
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to I2C input \" error");   
    
    xSPinTypeI2C(I2C1SDA, PA10);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP10;
    TestAssert(ulTemp == GCR_GPAMFP_MFP10,
               "xgpio, \"Turn pin to I2C input \" error");     
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to I2C input \" error");    
    
    //
    // Turn pin to CAN function 
    //    
    xSPinTypeCAN(CAN0RX, PD6);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP6;
    TestAssert(ulTemp == GCR_GPDMFP_MFP6,
               "xgpio, \"Turn pin to CAN function \" error"); 
    
    xSPinTypeCAN(CAN0TX, PD7);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP7;
    TestAssert(ulTemp == GCR_GPDMFP_MFP7,
               "xgpio, \"Turn pin to CAN function \" error");   
    
    //
    // Turn pin to I2S function
    //
    xSPinTypeI2S(I2S0RXMCLK, PA15);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP15;
    TestAssert(ulTemp == GCR_GPAMFP_MFP15,
               "xgpio, \"Turn pin to I2S function \" error");     
    ulTemp = xHWREG(GCR_ALTMFP) & GCR_ALTMFP_PA15_I2SMCLK;
    TestAssert(ulTemp == GCR_ALTMFP_PA15_I2SMCLK,
               "xgpio, \"Turn pin to I2S function \" error");   
    
    xSPinTypeI2S(I2S0RXSCK, PC1);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP1;
    TestAssert(ulTemp == GCR_GPCMFP_MFP1,
               "xgpio, \"Turn pin to I2S function \" error");        
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PC1_I2SBCLK);
    TestAssert(ulTemp == GCR_ALTMFP_PC1_I2SBCLK,
               "xgpio, \"Turn pin to I2S function \" error");  
    
    xSPinTypeI2S(I2S0RXSD, PC2);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP2;
    TestAssert(ulTemp == GCR_GPCMFP_MFP2,
               "xgpio, \"Turn pin to I2S function \" error");        
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PC2_I2SDI);
    TestAssert(ulTemp == GCR_ALTMFP_PC2_I2SDI,
               "xgpio, \"Turn pin to I2S function \" error");  
    
    xSPinTypeI2S(I2S0RXWS, PC0);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP0;
    TestAssert(ulTemp == GCR_GPCMFP_MFP0,
               "xgpio, \"Turn pin to I2S function \" error");        
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PC0_I2SLRCLK);
    TestAssert(ulTemp == GCR_ALTMFP_PC0_I2SLRCLK,
               "xgpio, \"Turn pin to I2S function \" error");      
    
    xSPinTypeI2S(I2S0TXMCLK, PA15);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP15;
    TestAssert(ulTemp == GCR_GPAMFP_MFP15,
               "xgpio, \"Turn pin to I2S function \" error");         
    ulTemp = xHWREG(GCR_ALTMFP) & GCR_ALTMFP_PA15_I2SMCLK;
    TestAssert(ulTemp == GCR_ALTMFP_PA15_I2SMCLK,
               "xgpio, \"Turn pin to I2S function \" error");   
 
    xSPinTypeI2S(I2S0TXSCK, PC1);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP1;
    TestAssert(ulTemp == GCR_GPCMFP_MFP1,
               "xgpio, \"Turn pin to I2S function \" error");        
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PC1_I2SBCLK);
    TestAssert(ulTemp == GCR_ALTMFP_PC1_I2SBCLK,
               "xgpio, \"Turn pin to I2S function \" error");   
    
    xSPinTypeI2S(I2S0TXSD, PC3);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP3;
    TestAssert(ulTemp == GCR_GPCMFP_MFP3,
               "xgpio, \"Turn pin to I2S function \" error");        
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PC3_I2SDO);
    TestAssert(ulTemp == GCR_ALTMFP_PC3_I2SDO,
               "xgpio, \"Turn pin to I2S function \" error");  

    xSPinTypeI2S(I2S0TXWS, PC0);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP0;
    TestAssert(ulTemp == GCR_GPCMFP_MFP0,
               "xgpio, \"Turn pin to I2S function \" error");        
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PC0_I2SLRCLK);
    TestAssert(ulTemp == GCR_ALTMFP_PC0_I2SLRCLK,
               "xgpio, \"Turn pin to I2S function \" error");    
    
    //
    // Turn pin to pwm mode
    //
    xSPinTypePWM(PWM0, PA12);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP12;
    TestAssert(ulTemp == GCR_GPAMFP_MFP12,
               "xgpio, \"Turn pin to I2S function \" error");  
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN | GCR_ALTMFP_EBI_HB_EN_5);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to PWM input \" error");   
   
    xSPinTypePWM(PWM1, PA13);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP13;
    TestAssert(ulTemp == GCR_GPAMFP_MFP13,
               "xgpio, \"Turn pin to I2S function \" error");  
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN | GCR_ALTMFP_EBI_HB_EN_6);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to PWM input \" error");       
    
    xSPinTypePWM(PWM2, PA14);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP14;
    TestAssert(ulTemp == GCR_GPAMFP_MFP14,
               "xgpio, \"Turn pin to I2S function \" error");  
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN | GCR_ALTMFP_EBI_HB_EN_7);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to PWM input \" error");     
    
    xSPinTypePWM(PWM3, PA15);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP15;
    TestAssert(ulTemp == GCR_GPAMFP_MFP15,
               "xgpio, \"Turn pin to I2S function \" error");  
    ulTemp = xHWREG(GCR_ALTMFP) & GCR_ALTMFP_PA15_I2SMCLK;
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to PWM function \" error");    
    
    xSPinTypePWM(PWM4, PB11);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP11;
    TestAssert(ulTemp == GCR_GPBMFP_MFP11,
               "xgpio, \"Turn pin to I2S function \" error");    
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PB11_PWM4);
    TestAssert(ulTemp == GCR_ALTMFP_PB11_PWM4,
               "xgpio, \"Turn pin to PWM input \" error");     
    
    xSPinTypePWM(PWM5, PE5);
    ulTemp = xHWREG(GCR_GPEMFP) & GCR_GPEMFP_MFP5;
    TestAssert(ulTemp == GCR_GPEMFP_MFP5,
               "xgpio, \"Turn pin to I2S function \" error");    
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PE5_T1EX);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to PWM input \" error"); 
    
    xSPinTypePWM(PWM6, PE0);
    ulTemp = xHWREG(GCR_GPEMFP) & GCR_GPEMFP_MFP0;
    TestAssert(ulTemp == GCR_GPEMFP_MFP0,
               "xgpio, \"Turn pin to PWM function \" error");    
    
    xSPinTypePWM(PWM7, PE1);
    ulTemp = xHWREG(GCR_GPEMFP) & GCR_GPEMFP_MFP1;
    TestAssert(ulTemp == GCR_GPEMFP_MFP1,
               "xgpio, \"Turn pin to PWM function \" error");  
    
    //
    // Turn pin to spi function test
    //
    xSPinTypeSPI(SPI0CLK, PC1);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP1;
    TestAssert(ulTemp == GCR_GPCMFP_MFP1,
               "xgpio, \"Turn pin to SPI function \" error");      
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PC1_I2SBCLK);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to SPI function \" error"); 

    xSPinTypeSPI(SPI0MOSI, PC5);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP5;
    TestAssert(ulTemp == GCR_GPCMFP_MFP5,
               "xgpio, \"Turn pin to SPI function \" error");  
    
    xSPinTypeSPI(SPI0MOSI, PC3);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP3;
    TestAssert(ulTemp == GCR_GPCMFP_MFP3,
               "xgpio, \"Turn pin to SPI function \" error"); 
    
    xSPinTypeSPI(SPI0MISO, PC2);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP2;
    TestAssert(ulTemp == GCR_GPCMFP_MFP2,
               "xgpio, \"Turn pin to SPI function \" error");  
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PC2_I2SDI);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to I2S function \" error"); 
    
    xSPinTypeSPI(SPI0MISO, PC4);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP4;
    TestAssert(ulTemp == GCR_GPCMFP_MFP4,
               "xgpio, \"Turn pin to SPI function \" error");     
    
    xSPinTypeSPI(SPI0CS, PC0);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP0;
    TestAssert(ulTemp == GCR_GPCMFP_MFP0,
               "xgpio, \"Turn pin to SPI function \" error");   
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PC0_I2SLRCLK);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to SPI function \" error");  

    xSPinTypeSPI(SPI0CS, PB10);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP10;
    TestAssert(ulTemp == GCR_GPBMFP_MFP10,
               "xgpio, \"Turn pin to SPI function \" error");   
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PB10_S01);
    TestAssert(ulTemp == GCR_ALTMFP_PB10_S01,
               "xgpio, \"Turn pin to SPI function \" error");
    
    xSPinTypeSPI(SPI0CS, PC0);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP0;
    TestAssert(ulTemp == GCR_GPCMFP_MFP0,
               "xgpio, \"Turn pin to SPI function \" error");   
    
    xSPinTypeSPI(SPI1MOSI, PC13);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP13;
    TestAssert(ulTemp == GCR_GPCMFP_MFP13,
               "xgpio, \"Turn pin to SPI function \" error");   
    
    xSPinTypeSPI(SPI1MOSI, PC11);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP11;
    TestAssert(ulTemp == GCR_GPCMFP_MFP11,
               "xgpio, \"Turn pin to SPI function \" error");   
    
    xSPinTypeSPI(SPI1MISO, PC12);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP12;
    TestAssert(ulTemp == GCR_GPCMFP_MFP12,
               "xgpio, \"Turn pin to SPI function \" error");   
    
    xSPinTypeSPI(SPI1MISO, PC10);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP10;
    TestAssert(ulTemp == GCR_GPCMFP_MFP10,
               "xgpio, \"Turn pin to SPI function \" error");    
    
    xSPinTypeSPI(SPI1CS, PB9);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP9;
    TestAssert(ulTemp == GCR_GPBMFP_MFP9,
               "xgpio, \"Turn pin to SPI function \" error");  
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PB9_S11);
    TestAssert(ulTemp == GCR_ALTMFP_PB9_S11,
               "xgpio, \"Turn pin to SPI function \" error");  
    
    xSPinTypeSPI(SPI1CS, PC8);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP8;
    TestAssert(ulTemp == GCR_GPCMFP_MFP8,
               "xgpio, \"Turn pin to SPI function \" error");   
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to SPI function \" error");    
    
    xSPinTypeSPI(SPI2CLK, PD1);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP1;
    TestAssert(ulTemp == GCR_GPDMFP_MFP1,
               "xgpio, \"Turn pin to SPI function \" error");   
    
    xSPinTypeSPI(SPI2MOSI, PD3);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP3;
    TestAssert(ulTemp == GCR_GPDMFP_MFP3,
               "xgpio, \"Turn pin to SPI function \" error");     
    
    xSPinTypeSPI(SPI2MOSI, PD5);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP5;
    TestAssert(ulTemp == GCR_GPDMFP_MFP5,
               "xgpio, \"Turn pin to SPI function \" error");    
    
    xSPinTypeSPI(SPI2MISO, PD4);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP4;
    TestAssert(ulTemp == GCR_GPDMFP_MFP4,
               "xgpio, \"Turn pin to SPI function \" error");    
    
    xSPinTypeSPI(SPI2MISO, PD2);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP2;
    TestAssert(ulTemp == GCR_GPDMFP_MFP2,
               "xgpio, \"Turn pin to SPI function \" error"); 
    
    xSPinTypeSPI(SPI2CS, PA7);
    ulTemp = xHWREG(GCR_GPAMFP) & GCR_GPAMFP_MFP7;
    TestAssert(ulTemp == GCR_GPAMFP_MFP7,
               "xgpio, \"Turn pin to SPI function \" error");     
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PA7_S21);
    TestAssert(ulTemp == GCR_ALTMFP_PA7_S21,
               "xgpio, \"Turn pin to SPI function \" error");
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to SPI function \" error");   
    
    xSPinTypeSPI(SPI2CS, PD0);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP0;
    TestAssert(ulTemp == GCR_GPDMFP_MFP0,
               "xgpio, \"Turn pin to SPI function \" error");  
    
    xSPinTypeSPI(SPI3CLK, PD9);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP9;
    TestAssert(ulTemp == GCR_GPDMFP_MFP9,
               "xgpio, \"Turn pin to SPI function \" error");    
    
    xSPinTypeSPI(SPI3MOSI, PD11);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP11;
    TestAssert(ulTemp == GCR_GPDMFP_MFP11,
               "xgpio, \"Turn pin to SPI function \" error");  
    
    xSPinTypeSPI(SPI3MOSI, PD13);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP13;
    TestAssert(ulTemp == GCR_GPDMFP_MFP13,
               "xgpio, \"Turn pin to SPI function \" error");   
    
    xSPinTypeSPI(SPI3MISO, PD10);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP10;
    TestAssert(ulTemp == GCR_GPDMFP_MFP10,
               "xgpio, \"Turn pin to SPI function \" error");     
    
    xSPinTypeSPI(SPI3MISO, PD12);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP12;
    TestAssert(ulTemp == GCR_GPDMFP_MFP12,
               "xgpio, \"Turn pin to SPI function \" error"); 
    
    
    xSPinTypeSPI(SPI3CS, PB14);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP14;
    TestAssert(ulTemp == GCR_GPBMFP_MFP14,
               "xgpio, \"Turn pin to SPI function \" error");     
    ulTemp =  xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PB14_S31);  
    TestAssert(ulTemp == GCR_ALTMFP_PB14_S31,
               "xgpio, \"Turn pin to SPI function \" error");  
    
    
    xSPinTypeSPI(SPI3CS, PD8);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP8;
    TestAssert(ulTemp == GCR_GPDMFP_MFP8,
               "xgpio, \"Turn pin to SPI function \" error");   
    
    //
    // Turn pin to timer function test
    //
    xSPinTypeTimer(TIMCCP0, PB8);   
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP8;
    TestAssert(ulTemp == GCR_GPBMFP_MFP8,
               "xgpio, \"Turn pin to TIMER function \" error");      
    
    xSPinTypeTimer(TIMCCP1, PB9);   
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP9;
    TestAssert(ulTemp == GCR_GPBMFP_MFP9,
               "xgpio, \"Turn pin to TIMER function \" error");        
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PB9_S11);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to TIMER function \" error"); 
    
    xSPinTypeTimer(TIMCCP2, PB10);   
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP10;
    TestAssert(ulTemp == GCR_GPBMFP_MFP10,
               "xgpio, \"Turn pin to TIMER function \" error");        
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PB10_S01);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to TIMER function \" error");     
    
    xSPinTypeTimer(TIMCCP3, PB11);   
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP11;
    TestAssert(ulTemp == GCR_GPBMFP_MFP11,
               "xgpio, \"Turn pin to TIMER function \" error");        
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PB11_PWM4);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to TIMER function \" error");  
    
    // 
    // Turn pin to uart function test
    //
    xSPinTypeUART(UART0RX, PB0);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP0;
    TestAssert(ulTemp == GCR_GPBMFP_MFP0,
               "xgpio, \"Turn pin to UART function \" error");  
    
    xSPinTypeUART(UART0TX, PB1);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP1;
    TestAssert(ulTemp == GCR_GPBMFP_MFP1,
               "xgpio, \"Turn pin to UART function \" error");     
    
    xSPinTypeUART(UART0RTS, PB2);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP2;
    TestAssert(ulTemp == GCR_GPBMFP_MFP2,
               "xgpio, \"Turn pin to UART function \" error");   
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN | GCR_ALTMFP_EBI_nWRL_EN);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to UART function \" error");      
    ulTemp =  xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PB2_T2EX);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to UART function \" error");    

    xSPinTypeUART(UART0CTS, PB3);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP3;
    TestAssert(ulTemp == GCR_GPBMFP_MFP3,
               "xgpio, \"Turn pin to UART function \" error");   
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN | GCR_ALTMFP_EBI_nWRH_EN);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to UART function \" error");
    ulTemp =  xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_PB3_T3EX);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to UART function \" error");  
    
    xSPinTypeUART(UART1RTS, PB6);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP6;
    TestAssert(ulTemp == GCR_GPBMFP_MFP6,
               "xgpio, \"Turn pin to UART function \" error");   
    ulTemp =  xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to UART function \" error");  
    
    xSPinTypeUART(UART1RX, PB4);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP4;
    TestAssert(ulTemp == GCR_GPBMFP_MFP4,
               "xgpio, \"Turn pin to UART function \" error");   
    
    xSPinTypeUART(UART1TX, PB5);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP5;
    TestAssert(ulTemp == GCR_GPBMFP_MFP5,
               "xgpio, \"Turn pin to UART function \" error");   
    
    xSPinTypeUART(UART2RX, PD14);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP14;
    TestAssert(ulTemp == GCR_GPDMFP_MFP14,
               "xgpio, \"Turn pin to UART function \" error");       

    xSPinTypeUART(UART2TX, PD15);
    ulTemp = xHWREG(GCR_GPDMFP) & GCR_GPDMFP_MFP15;
    TestAssert(ulTemp == GCR_GPDMFP_MFP15,
               "xgpio, \"Turn pin to UART function \" error");      
    
    //
    // Turn pin to ACMP function test
    //
    xSPinTypeACMP(CMP0P, PC6);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP6;
    TestAssert(ulTemp == GCR_GPCMFP_MFP6,
               "xgpio, \"Turn pin to SPI function \" error");   
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to SPI function \" error"); 
    
    xSPinTypeACMP(CMP0N, PC7);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP7;
    TestAssert(ulTemp == GCR_GPCMFP_MFP7,
               "xgpio, \"Turn pin to SPI function \" error");   
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to SPI function \" error"); 

    xSPinTypeACMP(CMP0O, PB12);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP12;
    TestAssert(ulTemp == GCR_GPBMFP_MFP12,
               "xgpio, \"Turn pin to SPI function \" error");   
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to SPI function \" error");  

    xSPinTypeACMP(CMP1P, PC14);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP14;
    TestAssert(ulTemp == GCR_GPCMFP_MFP14,
               "xgpio, \"Turn pin to SPI function \" error");   
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to SPI function \" error");      
    
    xSPinTypeACMP(CMP1N, PC15);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP15;
    TestAssert(ulTemp == GCR_GPCMFP_MFP15,
               "xgpio, \"Turn pin to SPI function \" error");   
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to SPI function \" error");   
    
    xSPinTypeACMP(CMP1O, PB13);
    ulTemp = xHWREG(GCR_GPBMFP) & GCR_GPBMFP_MFP13;
    TestAssert(ulTemp == GCR_GPBMFP_MFP13,
               "xgpio, \"Turn pin to SPI function \" error");   
    ulTemp = xHWREG(GCR_ALTMFP) & (GCR_ALTMFP_EBI_EN);
    TestAssert(ulTemp == 0,
               "xgpio, \"Turn pin to SPI function \" error");        
    
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
