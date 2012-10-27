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
static unsigned long ulPinMode[2] = {xGPIO_DIR_MODE_IN, xGPIO_DIR_MODE_OUT};

//
// GPIO interrupt type 
//
static unsigned long ulIntType[5] = {xGPIO_FALLING_EDGE, xGPIO_RISING_EDGE,
                                     xGPIO_BOTH_EDGES, xGPIO_LOW_LEVEL, 
                                     xGPIO_HIGH_LEVEL};

//
// GPIO pin
//
static unsigned long ulPinValue[3] = {GPIO_PIN_0, GPIO_PIN_8, GPIO_PIN_15};

//
// GPIO DMA Trigger edge
//
static unsigned long ulDMAEdge[4] = {GPIO_DMA_DIS, GPIO_DMA_RISE,
                                     GPIO_DMA_FALL, GPIO_DMA_BOTH};

//
// Port pin pad strength
//
static unsigned long ulPinStrength[2] = {GPIO_DRIVER_STR_DIS, 
                                         GPIO_DRIVER_STR_ENA};

//
// Port pin pull configure
//
static unsigned long ulPinPull[2] = {GPIO_PULL_DOWN, GPIO_PULL_UP};

//
// Pull configure
//
static unsigned long ulPullCfg[2] = {GPIO_PULL_ENABLE, GPIO_PULL_DISABLE};

//
// Passive configure
//
static unsigned long ulPassiveCfg[2] = {GPIO_PASSIVE_FILTER_DIS, 
                                        GPIO_PASSIVE_FILTER_ENA};

//
// Slew Rata Configure
//
static unsigned long ulSlewRateCfg[2] = {GPIO_SLEW_RATE_FAST, 
                                         GPIO_SLEW_RATE_SLOW};

//*****************************************************************************
//
//! \brief Get the Test description of xgpio001 register test.
//!
//! \return the desccription of the xgpio001 test.
//
//*****************************************************************************
const char* xgpio001GetTest(void)
{
    static const char * const pcName = "xgpio, 001, xgpio register test";
    return pcName;
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
    xSysCtlClockSet(12000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_12MHZ);
    
    //
    // Enable the peripheral
    //
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);  
  
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
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOA);
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOB);
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOC);
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOD);
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOE);  
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
    unsigned long ulvalue, ulTemp, ulTemp1;  
    int i;
 
/*    
    //
    // GPIO PortA mode set and get. 
    //
	for(i = 0; i < 2; i++)
	{
        xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_0, ulPinMode[i]);        
        ulvalue = xGPIODirModeGet(xGPIO_PORTA_BASE, xGPIO_PIN_0);
        TestAssert((ulvalue == ulPinMode[i]), 
                  "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
	}
	for(i = 0; i < 2; i++)
	{
        xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_1, ulPinMode[i]);        
        ulvalue = xGPIODirModeGet(xGPIO_PORTA_BASE, xGPIO_PIN_1);
        TestAssert((ulvalue == ulPinMode[i]), 
                  "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
	}

	//
	// GPIO PortB mode set and get.
	//
	for(i = 0; i < 2; i++)
	{
        xGPIODirModeSet(xGPIO_PORTB_BASE, xGPIO_PIN_1, ulPinMode[i]);        
        ulvalue = xGPIODirModeGet(xGPIO_PORTB_BASE, xGPIO_PIN_1);
        TestAssert((ulvalue == ulPinMode[i]), 
                  "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
	}
	for(i = 0; i < 2; i++)
	{
        xGPIODirModeSet(xGPIO_PORTB_BASE, xGPIO_PIN_2, ulPinMode[i]);        
        ulvalue = xGPIODirModeGet(xGPIO_PORTB_BASE, xGPIO_PIN_2);
        TestAssert((ulvalue == ulPinMode[i]), 
                  "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
	}

	//
	// GPIO PortC mode set and get.
	//
	for(i = 0; i < 2; i++)
	{
        xGPIODirModeSet(xGPIO_PORTC_BASE, xGPIO_PIN_7, ulPinMode[i]);        
        ulvalue = xGPIODirModeGet(xGPIO_PORTC_BASE, xGPIO_PIN_7);
        TestAssert((ulvalue == ulPinMode[i]), 
                  "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
	}
	for(i = 0; i < 2; i++)
	{
        xGPIODirModeSet(xGPIO_PORTC_BASE, xGPIO_PIN_8, ulPinMode[i]);        
        ulvalue = xGPIODirModeGet(xGPIO_PORTC_BASE, xGPIO_PIN_8);
        TestAssert((ulvalue == ulPinMode[i]), 
                  "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
	}

	//
	// GPIO PortD mode set and get.
	//
	for(i = 0; i < 2; i++)
	{
        xGPIODirModeSet(xGPIO_PORTD_BASE, xGPIO_PIN_0, ulPinMode[i]);        
        ulvalue = xGPIODirModeGet(xGPIO_PORTD_BASE, xGPIO_PIN_0);
        TestAssert((ulvalue == ulPinMode[i]), 
                  "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
	}
	for(i = 0; i < 2; i++)
	{
        xGPIODirModeSet(xGPIO_PORTD_BASE, xGPIO_PIN_1, ulPinMode[i]);        
        ulvalue = xGPIODirModeGet(xGPIO_PORTD_BASE, xGPIO_PIN_1);
        TestAssert((ulvalue == ulPinMode[i]), 
                  "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
	}

	//
	// GPIO PortE mode set and get.
	//
	for(i = 0; i < 2; i++)
	{
        xGPIODirModeSet(xGPIO_PORTE_BASE, xGPIO_PIN_0, ulPinMode[i]);        
        ulvalue = xGPIODirModeGet(xGPIO_PORTE_BASE, xGPIO_PIN_0);
        TestAssert((ulvalue == ulPinMode[i]), 
                  "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
	}
	for(i = 0; i < 2; i++)
	{
        xGPIODirModeSet(xGPIO_PORTE_BASE, xGPIO_PIN_1, ulPinMode[i]);        
        ulvalue = xGPIODirModeGet(xGPIO_PORTE_BASE, xGPIO_PIN_1);
        TestAssert((ulvalue == ulPinMode[i]), 
                  "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
	}
*/    
    xIntDisable(xINT_GPIOA);
    xIntDisable(xINT_GPIOD);  
      
    //
    // Interrupt enable.
    //
    for(i = 0; i < 5; i++)
    {
        xGPIOPinIntEnable(xGPIO_PORTA_BASE, xGPIO_PIN_12, ulIntType[i]);
        ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 4 *12) & PORT_PCR_IRQC_M;
        TestAssert((ulTemp == ulIntType[i]), 
                  "xgpio, \" xGPIOPinIntEnable()\" error");
    }

    for(i = 0; i < 5; i++)
    {
        xGPIOPinIntEnable(xGPIO_PORTD_BASE, xGPIO_PIN_0, ulIntType[i]);
	ulTemp = xHWREG(PORTD_BASE + PORT_PCR) & PORT_PCR_IRQC_M;
        TestAssert((ulTemp == ulIntType[i]), 
                  "xgpio, \" xGPIOPinIntEnable()\" error");
    }
  
    //
    // Interrupt disable test
    //	
    xGPIOPinIntDisable(xGPIO_PORTD_BASE, xGPIO_PIN_0);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR) & PORT_PCR_IRQC_M;
    TestAssert(ulTemp == 0, "xgpio, \"Interrupt disable test \" error");
    xGPIOPinIntDisable(xGPIO_PORTD_BASE, xGPIO_PIN_1);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 4) & PORT_PCR_IRQC_M;
    TestAssert(ulTemp == 0, "xgpio, \"Interrupt disable test \" error"); 		 
    
    //
    // Pin Out/in value test
    //
    xGPIOSPinTypeGPIOOutput(PD0);
    xGPIOSPinTypeGPIOOutput(PD1);
    xGPIOPinWrite(xGPIO_PORTD_BASE, xGPIO_PIN_0 | xGPIO_PIN_1, 1);
    ulTemp = xHWREG(xGPIO_PORTD_BASE + GPIO_PDOR) & (xGPIO_PIN_0 | xGPIO_PIN_1);
    TestAssert(ulTemp == xGPIO_PIN_0 | xGPIO_PIN_1,
               "xgpio, \"Output pin value set \" error"); 
    xGPIOPinWrite(xGPIO_PORTD_BASE, xGPIO_PIN_0 | xGPIO_PIN_1, 0);
    ulTemp = xHWREG(xGPIO_PORTD_BASE + GPIO_PDOR) & (xGPIO_PIN_0 | xGPIO_PIN_1);
    TestAssert(ulTemp == 0,
               "xgpio, \"Output pin value set \" error"); 
    
    //
    // Short pin to port test
    //
    ulTemp = xGPIOSPinToPort(PA0);
    TestAssert(ulTemp == xGPIO_PORTA_BASE,
               "xgpio, \"Short pin to port test \" error"); 

    //
    // Short pin to pin test
    //
    ulTemp = xGPIOSPinToPin(PA0);	   
    TestAssert(ulTemp == GPIO_PIN_0,
               "xgpio, \"Short pin to pin test \" error");
			   
    //
    // Short pin dir mode set test
    //
    for(i = 0; i < 2; i++)
    {
        xGPIOSPinDirModeSet(PA0, ulPinMode[i]);        
        ulvalue = xGPIODirModeGet(xGPIO_PORTA_BASE, xGPIO_PIN_0);
        TestAssert((ulvalue == ulPinMode[i]), 
                  "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
    }
     
    //
    //  Short pin int enable
    //
    for(i = 0; i < 5; i++)
    {
        xGPIOSPinIntEnable(PA12, ulIntType[i]);
        ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 4*12) & PORT_PCR_IRQC_M;
        TestAssert((ulTemp == ulIntType[i]), 
                  "xgpio, \" xGPIOPinIntEnable()\" error");
    }
    
    //
    // Short pin int disable
    //
    xGPIOSPinIntDisable(PA12);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 4*12) & PORT_PCR_IRQC_M;
    TestAssert(ulTemp == 0, "xgpio, \"Interrupt disable test \" error"); 
    
    //
    // Short pin data output
    //
    xGPIOSPinTypeGPIOOutput(PB0);
    xGPIOSPinWrite(PB0, 1);
    ulTemp = xHWREG(xGPIO_PORTB_BASE + GPIO_PDOR) & xGPIO_PIN_0;
    TestAssert(ulTemp == xGPIO_PIN_0,
               "xgpio, \"Output pin value set \" error"); 
    xGPIOSPinWrite(PB0, 0);
    ulTemp = xHWREG(xGPIO_PORTB_BASE + GPIO_PDOR) & xGPIO_PIN_0;
    TestAssert(ulTemp == 0,
               "xgpio, \"Output pin value set \" error"); 

    
////////////////////////////////////////////////////////////////////////////////
    //
    // GPIO Mode set test
    //
    for(i = 0; i < 2; i++)
    {
        GPIODirModeSet(GPIOA_BASE, GPIO_PIN_0, ulPinMode[i]);        
        ulvalue = GPIODirModeGet(GPIOA_BASE, GPIO_PIN_0);
        TestAssert((ulvalue == ulPinMode[i]), 
                  "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
    }
    /*
    //
    // Interrupt enable.
    //
    for(i = 0; i < 5; i++)
    {
        GPIOPinIntEnable(GPIOB_BASE, GPIO_PIN_0, ulIntType[i]);
	ulTemp = xHWREG(PORTB_BASE + PORT_PCR) & PORT_PCR_IRQC_M;
        TestAssert((ulTemp == ulPinMode[i]), 
                  "xgpio, \" GPIOPinIntEnable()\" error");
    }
    */
    //
    // DMA Edge set test
    //
    for(i = 0; i < 5; i++)
    {
        GPIODMAEdgeSet(GPIOA_BASE, GPIO_PIN_0 | GPIO_PIN_1, ulDMAEdge[i]);
        ulTemp = xHWREG(PORTA_BASE + PORT_PCR) & PORT_PCR_IRQC_M;
        TestAssert((ulTemp == ulDMAEdge[i]), 
                  "xgpio, \" DMA Edge set()\" error");
        ulTemp1 = xHWREG(PORTA_BASE + PORT_PCR + 4) & PORT_PCR_IRQC_M; 
                TestAssert((ulTemp1 == ulDMAEdge[i]), 
                  "xgpio, \" DMA Edge set()\" error");  
    }
    
    //
    // Pin write
    //
    GPIODirModeSet(GPIOA_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIOA_BASE, GPIO_PIN_0 | GPIO_PIN_1, 1);
    ulTemp = xHWREG(GPIOA_BASE + GPIO_PDOR) & (GPIO_PIN_0 | GPIO_PIN_1);
    TestAssert(ulTemp == GPIO_PIN_0 | GPIO_PIN_1,
               "xgpio, \"Output pin value set \" error"); 
    GPIOPinWrite(GPIOD_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0);
    ulTemp = xHWREG(GPIOD_BASE + GPIO_PDOR) & (GPIO_PIN_0 | GPIO_PIN_1);
    TestAssert(ulTemp == 0,
               "xgpio, \"Output pin value set \" error");     
        
    //
    // Pin set test
    //
    GPIOPinWrite(GPIOA_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0);
    GPIOPinSet(GPIOA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    ulTemp = xHWREG(GPIOA_BASE + GPIO_PDOR) & (GPIO_PIN_0 | GPIO_PIN_1);
    TestAssert(ulTemp == GPIO_PIN_0 | GPIO_PIN_1,
               "xgpio, \"Pin set test \" error"); 
  
    //
    // Pin reset test
    // 
    GPIOPinReset(GPIOA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    ulTemp = xHWREG(GPIOA_BASE + GPIO_PDOR) & (GPIO_PIN_0 | GPIO_PIN_1);
    TestAssert(ulTemp == 0, "xgpio, \"Pin set test \" error"); 
    
    //
    // Pin mask configure
    //
    GPIOPinMaskSet(GPIOB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    ulTemp = GPIOPortMaskGet(GPIOB_BASE) & GPIO_PIN_0 | GPIO_PIN_1;
    TestAssert(ulTemp == GPIO_PIN_0 | GPIO_PIN_1, "Pin mask configure");     
    
    
    //
    // Pin pad strength set test
    //
    for(i = 0; i < 2; i++)
    {
        GPIOPadConfigSet(GPIOB_BASE, GPIO_PIN_0, ulPinStrength[i]);
        ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 0 * 4) & PORT_PCR_DSE_HIGH ;
        TestAssert(ulTemp == ulPinStrength[i], "Pin mask configure");  
    }
    
    //
    // Pull configure
    //
    for(i = 0; i < 2; i++)
    {
        GPIOPullConfigure(GPIOB_BASE, GPIO_PIN_0 | GPIO_PIN_1, ulPullCfg[i],
                          ulPinPull[0]);
        ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 0 * 4) & PORT_PCR_PE_ENABLE ;
        TestAssert(ulTemp == ulPullCfg[i], "Pin pull configure");
        ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 1 * 4) & PORT_PCR_PE_ENABLE ;
        TestAssert(ulTemp == ulPullCfg[i], "Pin pull configure");                
    }
/******************************************************************************        
    //
    // Pull Select
    //
    for(i = 0; i < 2; i++)
    {
        GPIOPullConfigure(GPIOD_BASE, GPIO_PIN_0, ulPullCfg[0],
                          ulPinPull[i]);
        ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 0 * 4) & PORT_PCR_PS_ENABLE ;
        TestAssert(ulTemp == ulPinPull[i], "Pin pull configure");         
    }  
   
    //
    // Passive configure
    //
    for(i = 0; i < 2; i++)
    {
        GPIOPassiveConfigure(GPIOB_BASE, GPIO_PIN_0, 
                             ulPassiveCfg[i]);
        ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 0 * 4) & PORT_PCR_PFE_ENABLE ;
        TestAssert(ulTemp == ulPassiveCfg[i], "Pin passive configure");        
    }
  
    
    //
    // Slew rate configure
    // 
    for(i = 0; i < 2; i++)
    {
        GPIOSlewRataConfigure(GPIOB_BASE, GPIO_PIN_0, 
                              ulSlewRateCfg[i]);
        ulTemp =  xHWREG(PORTB_BASE + PORT_PCR + 0 * 4) & PORT_PCR_SRE_ENABLE ;
        TestAssert(ulTemp == ulSlewRateCfg[i], "Slew rate configure");      
    } 
*******************************************************************************/    
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
   
 
 /*   
    //
    // Turn pin to ADC input function
    //
    xSPinTypeADC(ADC0, PE20);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 20 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error");  
    xSPinTypeADC(ADC11, PC2);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 2 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error");   
    xSPinTypeADC(ADC3, PE22);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 22 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error"); 
    xSPinTypeADC(ADC6, PD5);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 5 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error");   
    xSPinTypeADC(ADC7, PD6);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 6 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error");   
    xSPinTypeADC(ADC7, PE23);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 23 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error");        
    xSPinTypeADC(ADC8, PB0);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 0 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error");
    xSPinTypeADC(ADC9, PB1);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 1 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error");    
    xSPinTypeADC(ADC11, PC2);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 2 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error");   
    xSPinTypeADC(ADC12, PB2);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 2 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error"); 
    xSPinTypeADC(ADC13, PB3);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 3 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error");  
    xSPinTypeADC(ADC14, PC0);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 0 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error");    
    xSPinTypeADC(ADC15, PC1);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 1 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error");   
    xSPinTypeADC(ADC23, PE30);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 30 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error"); 
    xSPinTypeADC(ADCDP0, PE20);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 20 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error");    
    xSPinTypeADC(ADCDP3, PE22);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 22 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error");
    xSPinTypeADC(ADCDM0, PE21);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 21 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error");           
    xSPinTypeADC(ADCDM3, PE23);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 23 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT0,
               "xgpio, \" Turn pin to ADC \" error");  
    xGPIOSPinTypeGPIOInput(PE23);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 23 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_GPIO,
               "xgpio, \" Turn pin to ADC \" error");      
  */  
   /* 
    //
    // Turn pin to I2C input function
    //
    xSPinTypeI2C(I2C0SCK, PB0);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 0 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to I2C \" error"); 
    xSPinTypeI2C(I2C0SCK, PB2);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 2 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to I2C \" error"); 
    xSPinTypeI2C(I2C0SCK, PC8);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 8 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to I2C \" error");   
    xSPinTypeI2C(I2C0SCK, PE24);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 24 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT5,
               "xgpio, \" Turn pin to I2C \" error");       
    xSPinTypeI2C(I2C1SCK, PC10);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 10 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to I2C \" error");        
    xSPinTypeI2C(I2C1SDA, PC11);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 11 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to I2C \" error");
    
    xSPinTypeI2C(I2C1SCK, PC1);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 1 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to I2C \" error");    
    xSPinTypeI2C(I2C1SCK, PE1);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 1 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT6,
               "xgpio, \" Turn pin to I2C \" error");            
    xSPinTypeI2C(I2C1SDA, PA4);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 4 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to I2C \" error");
    xSPinTypeI2C(I2C1SDA, PC2);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 2 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to I2C \" error");  
    xSPinTypeI2C(I2C1SDA, PE0);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 0 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT6,
               "xgpio, \" Turn pin to I2C \" error");    
    xGPIOSPinTypeGPIOInput(PE0);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 0 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_GPIO,
               "xgpio, \" Turn pin to I2C \" error");           
  
 
    //
    // Turn pin to SPI
    //
    xSPinTypeSPI(SPI0CLK, PA15);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 15 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");  
    xSPinTypeSPI(SPI0CLK, PC5);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 5 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");
    xSPinTypeSPI(SPI0CLK, PD1);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 1 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");  
    
    xSPinTypeSPI(SPI0MOSI, PA16);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 16 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");
    xSPinTypeSPI(SPI0MOSI, PA17);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 17 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT5,
               "xgpio, \" Turn pin to SPI \" error"); 
    xSPinTypeSPI(SPI0MOSI, PC6);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 6 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");   
    xSPinTypeSPI(SPI0MOSI, PC7);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 7 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT5,
               "xgpio, \" Turn pin to SPI \" error");    
    xSPinTypeSPI(SPI0MOSI, PD2);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 2 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");  
    xSPinTypeSPI(SPI0MOSI, PD3);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 3 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT5,
               "xgpio, \" Turn pin to SPI \" error");    
  
    xSPinTypeSPI(SPI0MISO, PA16);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 16 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT5,
               "xgpio, \" Turn pin to SPI \" error");
    xSPinTypeSPI(SPI0MISO, PA17);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 17 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error"); 
    xSPinTypeSPI(SPI0MISO, PC6);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 6 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT5,
               "xgpio, \" Turn pin to SPI \" error");   
    xSPinTypeSPI(SPI0MISO, PC7);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 7 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");    
    xSPinTypeSPI(SPI0MISO, PD2);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 2 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT5,
               "xgpio, \" Turn pin to SPI \" error");  
    xSPinTypeSPI(SPI0MISO, PD3);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 3 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");   
    
    xSPinTypeSPI(SPI0CS, PA14);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 14 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error"); 
    xSPinTypeSPI(SPI0CS, PC4);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 4 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error"); 
    xSPinTypeSPI(SPI0CS, PD0);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 0 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");    
    xSPinTypeSPI(SPI1CLK, PB11);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 11 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error"); 
    xSPinTypeSPI(SPI1CLK, PE2);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 2 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");   
    xSPinTypeSPI(SPI1CLK, PD5);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 5 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");  
    
    xSPinTypeSPI(SPI1MOSI, PB16);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 16 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error"); 
    xSPinTypeSPI(SPI1MOSI, PB17);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 17 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT5,
               "xgpio, \" Turn pin to SPI \" error"); 
    xSPinTypeSPI(SPI1MOSI, PD6);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 6 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");  
     xSPinTypeSPI(SPI1MOSI, PD7);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 7 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT5,
               "xgpio, \" Turn pin to SPI \" error");    
     xSPinTypeSPI(SPI1MOSI, PE1);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 1 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");      
       xSPinTypeSPI(SPI1MOSI, PE3);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 3 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT5,
               "xgpio, \" Turn pin to SPI \" error");  

    xSPinTypeSPI(SPI1MISO, PB16);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 16 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT5,
               "xgpio, \" Turn pin to SPI \" error"); 
    xSPinTypeSPI(SPI1MISO, PB17);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 17 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error"); 
    xSPinTypeSPI(SPI1MISO, PD6);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 6 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT5,
               "xgpio, \" Turn pin to SPI \" error");  
     xSPinTypeSPI(SPI1MISO, PD7);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 7 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");    
     xSPinTypeSPI(SPI1MISO, PE1);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 1 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT5,
               "xgpio, \" Turn pin to SPI \" error");      
    xSPinTypeSPI(SPI1MISO, PE3);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 3 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");       
    
    xSPinTypeSPI(SPI1CS, PB10);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 10 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");  
    xSPinTypeSPI(SPI1CS, PD4);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 4 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error"); 
  
    
    xSPinTypeSPI(SPI1CS, PE4);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 4 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to SPI \" error");  
  */  
   /*  
    //
    // Turn pin to timer
    //
 
     xSPinTypeTimer(TIM0CH0, PC1);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 1 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");       
     xSPinTypeTimer(TIM0CH0, PD0);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 0 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");       
     xSPinTypeTimer(TIM0CH0, PE24);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 24 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error"); 
    
    xSPinTypeTimer(TIM0CH1, PA4);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 4 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");   
     xSPinTypeTimer(TIM0CH1, PC2);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 2 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");       
     xSPinTypeTimer(TIM0CH1, PD1);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 1 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");       
     xSPinTypeTimer(TIM0CH1, PE25);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 25 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");  
    
    xSPinTypeTimer(TIM0CH2, PA5);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 5 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");   
     xSPinTypeTimer(TIM0CH2, PC3);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 3 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");       
     xSPinTypeTimer(TIM0CH2, PD2);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 2 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");       
     xSPinTypeTimer(TIM0CH2, PE29);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 29 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error"); 

    xSPinTypeTimer(TIM0CH3, PC4);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 4 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error"); 
    xSPinTypeTimer(TIM0CH3, PD3);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 3 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");   
    xSPinTypeTimer(TIM0CH3, PE30);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 30 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");   
    
    xSPinTypeTimer(TIM0CH4, PC8);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 8 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error"); 
    xSPinTypeTimer(TIM0CH4, PD4);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 4 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");   
    xSPinTypeTimer(TIM0CH4, PE31);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 31 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");    
   
    xSPinTypeTimer(TIM0CH5, PC9);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 9 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");    
    xSPinTypeTimer(TIM0CH5, PD5);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 5 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");   
   
    xSPinTypeTimer(TIM0CLKIN, PA18);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 18 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");
    xSPinTypeTimer(TIM0CLKIN, PB16);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 16 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");    
    xSPinTypeTimer(TIM0CLKIN, PC12);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 12 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");
    xSPinTypeTimer(TIM0CLKIN, PE29);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 29 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");       
    
    xSPinTypeTimer(TIM1CH0, PA12);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 12 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error"); 
    xSPinTypeTimer(TIM1CH0, PB0);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 0 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");     
    xSPinTypeTimer(TIM1CH0, PE20);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 20 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");         
    
    xSPinTypeTimer(TIM1CH1, PA13);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 13 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error"); 
    xSPinTypeTimer(TIM1CH1, PB1);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 1 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");     
    xSPinTypeTimer(TIM1CH1, PE21);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 21 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error"); 
   
    xSPinTypeTimer(TIM1CLKIN, PA19);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 19 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");
    xSPinTypeTimer(TIM1CLKIN, PB17);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 17 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");    
    xSPinTypeTimer(TIM1CLKIN, PC13);
    ulTemp = xHWREG(PORTC_BASE + PORT_PCR + 13 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");
    xSPinTypeTimer(TIM1CLKIN, PE30);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 30 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");  
  
    xSPinTypeTimer(TIM2CH0, PA1);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 1 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");
    xSPinTypeTimer(TIM2CH0, PB2);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 2 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");
    xSPinTypeTimer(TIM2CH0, PB18);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 18 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");       
    xSPinTypeTimer(TIM2CH0, PE22);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 22 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");    
    
    xSPinTypeTimer(TIM2CH1, PA2);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 2 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");
    xSPinTypeTimer(TIM2CH1, PB3);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 3 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");
    xSPinTypeTimer(TIM2CH1, PB19);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 19 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");       
    xSPinTypeTimer(TIM2CH1, PE23);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 23 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error"); 
  
   //
   // Turn pin to uart 
   // 
    xSPinTypeTimer(UART0RX, PA15);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 15 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error"); 
    xSPinTypeTimer(UART0RX, PB16);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 16 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");  
    xSPinTypeTimer(UART0RX, PD6);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 6 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");         
    xSPinTypeTimer(UART0RX, PE21);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 21 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error"); 

    xSPinTypeTimer(UART0TX, PA2);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 2 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT2,
               "xgpio, \" Turn pin to timer \" error");     
    xSPinTypeTimer(UART0TX, PA14);
    ulTemp = xHWREG(PORTA_BASE + PORT_PCR + 15 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error"); 
    xSPinTypeTimer(UART0TX, PB17);
    ulTemp = xHWREG(PORTB_BASE + PORT_PCR + 16 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");  
    xSPinTypeTimer(UART0TX, PD7);
    ulTemp = xHWREG(PORTD_BASE + PORT_PCR + 6 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT3,
               "xgpio, \" Turn pin to timer \" error");         
    xSPinTypeTimer(UART0TX, PE20);
    ulTemp = xHWREG(PORTE_BASE + PORT_PCR + 21 * 4) & PORT_PCR_PIN_MUX_M;
    TestAssert(ulTemp == PORT_PCR_PIN_ALT4,
               "xgpio, \" Turn pin to timer \" error");
    */ 
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
