//*****************************************************************************
//
//! @page xgpio_testcase xgpio register test
//!
//! File: @ref xgpiotest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xgpio sub component.<br><br>
//! - \p Board: MCBSTM32 Board<br><br>
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
static unsigned long ulGPIO[3] = {xGPIO_PORTA_BASE,     
                                  xGPIO_PORTC_BASE, 
                                  xGPIO_PORTE_BASE};

//
// GPIO bit packed pin
//
static unsigned long ulPackedPin[3] = {xGPIO_PIN_0, xGPIO_PIN_8, xGPIO_PIN_15};

//
// GPIO Pin Bit
//
static unsigned long ulBitPin[3] = {GPIO_BIT_0, GPIO_BIT_8, GPIO_BIT_15};

//
// GPIO Pin Shift
//
static unsigned long ulBitShift[3] = {0, 8, 15};

//
// GPIO Pin Mode
//
static unsigned long ulPinMode[3] = {xGPIO_DIR_MODE_IN, xGPIO_DIR_MODE_OUT, 
                                     xGPIO_DIR_MODE_OD};

//
// GPIO interrupt type 
//
static unsigned long ulIntTypes[3] = {xGPIO_FALLING_EDGE, xGPIO_RISING_EDGE,
                                      xGPIO_BOTH_EDGES};

//
// GPIO interrupt Port
//
static unsigned long ulIntPort[3] = {0, 2, 4};

//
// GPIO port output write data
//
//static unsigned long ulPortData[3] = {0, 10000, 65535};

//
// Pin pad configure
//
static unsigned long ulPinType[7] = {GPIO_TYPE_IN_ANALOG,
                                    GPIO_TYPE_IN_FLOATING,
                                    GPIO_TYPE_IN_WPU_WPD,
                                    GPIO_TYPE_OUT_STD,
                                    GPIO_TYPE_OUT_OD,
                                    GPIO_TYPE_AFOUT_STD, 
                                    GPIO_TYPE_AFOUT_OD};

//
// Pin max speed 
//
static unsigned long ulPinMode2[4] = {GPIO_IN_SPEED_FIXED, 
                                     GPIO_OUT_SPEED_10M, 
                                     GPIO_OUT_SPEED_2M,
                                     GPIO_OUT_SPEED_50M};

//
// EXTI lines 
//
//static unsigned long ulDeBounceTime[3] = {1, 1000, 1000000};

//
// GPIO pin
//
//static unsigned long ulPinValue[3] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2};




//*****************************************************************************
//
//! \brief Get the Test description of xgpio001 register test.
//!
//! \return the desccription of the xgpio001 test.
//
//*****************************************************************************
static char* xgpio001GetTest(void)
{
    return "xgpio, 001, gpio register test";
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
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_IOPA);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_IOPB);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_IOPC);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_IOPD);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_IOPE);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_IOPF);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
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
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_IOPA);
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_IOPB);
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_IOPC);
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_IOPD);
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_IOPE);
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_IOPF);
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_AFIO);
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
   
    static unsigned long ulPin, ulPort, ulMode, ulInt;
    static unsigned long ulTemp, ulTemp1;  
    static unsigned long i, j, k, ulShift;

    xSPinTypeUART(UART1RX,PA10);

    xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulTemp = xGPIODirModeGet(xGPIO_PORTA_BASE, xGPIO_PIN_0);
    TestAssert((ulTemp == xGPIO_DIR_MODE_IN), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error"); 	
    xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_8, xGPIO_DIR_MODE_OUT);
    ulTemp = xGPIODirModeGet(xGPIO_PORTA_BASE, xGPIO_PIN_8);
    TestAssert((ulTemp == xGPIO_DIR_MODE_OUT), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");	
    xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_10, xGPIO_DIR_MODE_OD);
    ulTemp = xGPIODirModeGet(xGPIO_PORTA_BASE, xGPIO_PIN_10);
    TestAssert((ulTemp == xGPIO_DIR_MODE_OD), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");	
	
    xGPIODirModeSet(xGPIO_PORTB_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulTemp = xGPIODirModeGet(xGPIO_PORTB_BASE, xGPIO_PIN_0);
    TestAssert((ulTemp == xGPIO_DIR_MODE_IN), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error"); 	
    xGPIODirModeSet(xGPIO_PORTB_BASE, xGPIO_PIN_8, xGPIO_DIR_MODE_OUT);
    ulTemp = xGPIODirModeGet(xGPIO_PORTB_BASE, xGPIO_PIN_8);
    TestAssert((ulTemp == xGPIO_DIR_MODE_OUT), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTB_BASE, xGPIO_PIN_10, xGPIO_DIR_MODE_OD);
    ulTemp = xGPIODirModeGet(xGPIO_PORTB_BASE, xGPIO_PIN_10);
    TestAssert((ulTemp == xGPIO_DIR_MODE_OD), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
		
    xGPIODirModeSet(xGPIO_PORTC_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulTemp = xGPIODirModeGet(xGPIO_PORTC_BASE, xGPIO_PIN_0);
    TestAssert((ulTemp == xGPIO_DIR_MODE_IN), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error"); 	
    xGPIODirModeSet(xGPIO_PORTC_BASE, xGPIO_PIN_8, xGPIO_DIR_MODE_OUT);
    ulTemp = xGPIODirModeGet(xGPIO_PORTC_BASE, xGPIO_PIN_8);
    TestAssert((ulTemp == xGPIO_DIR_MODE_OUT), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTC_BASE, xGPIO_PIN_10, xGPIO_DIR_MODE_OD);
    ulTemp = xGPIODirModeGet(xGPIO_PORTC_BASE, xGPIO_PIN_10);
    TestAssert((ulTemp == xGPIO_DIR_MODE_OD), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");

    xGPIODirModeSet(xGPIO_PORTD_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulTemp = xGPIODirModeGet(xGPIO_PORTD_BASE, xGPIO_PIN_0);
    TestAssert((ulTemp == xGPIO_DIR_MODE_IN), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error"); 	
    xGPIODirModeSet(xGPIO_PORTD_BASE, xGPIO_PIN_8, xGPIO_DIR_MODE_OUT);
    ulTemp = xGPIODirModeGet(xGPIO_PORTD_BASE, xGPIO_PIN_8);
    TestAssert((ulTemp == xGPIO_DIR_MODE_OUT), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTD_BASE, xGPIO_PIN_10, xGPIO_DIR_MODE_OD);
    ulTemp = xGPIODirModeGet(xGPIO_PORTD_BASE, xGPIO_PIN_10);
    TestAssert((ulTemp == xGPIO_DIR_MODE_OD), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
		
    xGPIODirModeSet(xGPIO_PORTE_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulTemp = xGPIODirModeGet(xGPIO_PORTE_BASE, xGPIO_PIN_0);
    TestAssert((ulTemp == xGPIO_DIR_MODE_IN), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error"); 	
    xGPIODirModeSet(xGPIO_PORTE_BASE, xGPIO_PIN_8, xGPIO_DIR_MODE_OUT);
    ulTemp = xGPIODirModeGet(xGPIO_PORTE_BASE, xGPIO_PIN_8);
    TestAssert((ulTemp == xGPIO_DIR_MODE_OUT), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTE_BASE, xGPIO_PIN_10, xGPIO_DIR_MODE_OD);
    ulTemp = xGPIODirModeGet(xGPIO_PORTE_BASE, xGPIO_PIN_10);
    TestAssert((ulTemp == xGPIO_DIR_MODE_OD), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");

/*
    xGPIODirModeSet(xGPIO_PORTF_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulTemp = xGPIODirModeGet(xGPIO_PORTF_BASE, xGPIO_PIN_0);
    TestAssert((ulTemp == xGPIO_DIR_MODE_IN), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error"); 	
    xGPIODirModeSet(xGPIO_PORTF_BASE, xGPIO_PIN_8, xGPIO_DIR_MODE_OUT);
    ulTemp = xGPIODirModeGet(xGPIO_PORTF_BASE, xGPIO_PIN_8);
    TestAssert((ulTemp == xGPIO_DIR_MODE_OUT), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTF_BASE, xGPIO_PIN_10, xGPIO_DIR_MODE_OD);
    ulTemp = xGPIODirModeGet(xGPIO_PORTF_BASE, xGPIO_PIN_10);
    TestAssert((ulTemp == xGPIO_DIR_MODE_OD), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");		
	
	
    xGPIODirModeSet(xGPIO_PORTG_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulTemp = xGPIODirModeGet(xGPIO_PORTG_BASE, xGPIO_PIN_0);
    TestAssert((ulTemp == xGPIO_DIR_MODE_IN), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error"); 	
    xGPIODirModeSet(xGPIO_PORTG_BASE, xGPIO_PIN_8, xGPIO_DIR_MODE_OUT);
    ulTemp = xGPIODirModeGet(xGPIO_PORTG_BASE, xGPIO_PIN_8);
    TestAssert((ulTemp == xGPIO_DIR_MODE_OUT), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTG_BASE, xGPIO_PIN_10, xGPIO_DIR_MODE_OD);
    ulTemp = xGPIODirModeGet(xGPIO_PORTG_BASE, xGPIO_PIN_10);
    TestAssert((ulTemp == xGPIO_DIR_MODE_OD), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error");
*/		
 	
/*
    for(i = 0; i < 6; i++)
    {  
        //
        // 6 Ports
        //
        ulPort = ulGPIO[i];
        
        for(j = 0; j < 15; j++)
        {
            // 
            // 16 Pins
            //
            ulPin = ulPackedPin[j];

            //
            // GPIO pin mode test
            //
            for(k = 0; k < 3; k++)
            {
                ulMode = ulPinMode[k];
                xGPIODirModeSet(ulPort, ulPin, ulMode);
                ulTemp = xGPIODirModeGet(ulPort, ulPin);
                TestAssert((ulTemp == ulMode), "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error"); 
          
            }
				 }	
		}				 
*/

		//
		// Pin direction and pad configure test
		//
    GPIODirModeSet(xGPIO_PORTA_BASE, GPIO_BIT_0, GPIO_TYPE_IN_ANALOG, GPIO_IN_SPEED_FIXED);
		ulTemp = (xHWREG(xGPIO_PORTA_BASE + GPIO_CRL) & (GPIO_CRL_CNF0_M << (0 * 4))) >> (0 * 4);
		TestAssert((ulTemp == GPIO_TYPE_IN_ANALOG), 
							"xgpio, \" GPIODirModeSet & Type \" error"); 
		
		GPIODirModeSet(GPIOC_BASE,0,GPIO_TYPE_OUT_STD,GPIO_OUT_SPEED_2M);
		//
		// Pin direction and pad configure test
		//		
    for(i = 0; i < 3; i++)
    {  
        //
        // 6 Ports
        //
        ulPort = ulGPIO[i];
        
        for(j = 0; j < 3; j++)
        {
            // 
            // 16 Pins
            //
            ulPin = ulBitPin[j];

            //
            // GPIO pin mode test
            //
            for(k = 0; k < 7; k++)
            {   
                //
                // Pin Type set test
                //
                GPIODirModeSet(ulPort, ulPin, ulPinType[k], ulPinMode2[0]);
                if(ulPin < 8)
                {
                    ulTemp = (xHWREG(ulPort + GPIO_CRL) & (GPIO_CRL_CNF0_M << (ulPin * 4))) >> (ulPin * 4);
                    TestAssert((ulTemp == ulPinType[k]), 
                            "xgpio, \" GPIODirModeSet & Type \" error"); 
                }
                else
                {
                    ulTemp = (xHWREG(ulPort + GPIO_CRH) & (GPIO_CRH_CNF8_M << ((ulPin -8) * 4))) >> (ulPin -8) * 4;
                    TestAssert((ulTemp == ulPinType[k]), 
                            "xgpio, \" GPIODirModeSet & Type\" error"); 
                }
                
            }
            for(k = 0; k  < 4; k++)
            {
                //
                // Pin Mode set test
                //
                GPIODirModeSet(ulPort, ulPin, ulPinType[0], ulPinMode2[k]);
                if(ulPin < 8)
                {
                    ulTemp = (xHWREG(ulPort + GPIO_CRL) & (GPIO_CRL_MODE0_M << (ulPin * 4))) >> (ulPin * 4);
                    TestAssert((ulTemp == ulPinMode2[k]), 
                            "xgpio, \" GPIODirModeSet & Mode \" error"); 
                }
                else
                {
                    ulTemp = (xHWREG(ulPort + GPIO_CRH) & (GPIO_CRH_MODE8_M << ((ulPin -8) * 4))) >> (ulPin -8) * 4;
                    TestAssert((ulTemp == ulPinMode2[k]), 
                            "xgpio, \" GPIODirModeSet & Mode\" error"); 
                }
            }
				 }	
		}		
		
		//
		// GPIO pin Int enable test
		//
    for(i = 0; i < 3; i++)
    {  
        //
        // 6 Ports
        //
        ulPort = ulGPIO[i];
        
        for(j = 0; j < 3; j++)
        {
					  // 
            // 16 Pins
            //
            ulPin = ulPackedPin[j];
					  ulShift = ulBitShift[j];
					
            for(k = 0; k < 3; k++)
            {
                //
                // 3 pin Int type
                //
                ulInt = ulIntTypes[k];
              
							/*
                //
                // Int port test
                //
                xGPIOPinIntEnable(ulPort, ulPin, ulInt);
                ulTemp = (xHWREG(AFIO_EVCR) & AFIO_EVCR_PORT_M) >> AFIO_EVCR_PORT_S;
                TestAssert((ulTemp == ulIntPort[i]), 
                            "xgpio, \" xGPIOPinIntEnable & Int Port\" error"); 
			        */
							
                //
                // Int port test
                //
                xGPIOPinIntEnable(ulPort, ulPin, ulInt);
                ulTemp = ((xHWREG(AFIO_EXTICR1 + (ulShift>>2) * 4) >> (ulShift%4)*4)) & AFIO_EXTICR1_EXTI0_M;
                TestAssert((ulTemp == ulIntPort[i]), 
                            "xgpio, \" xGPIOPinIntEnable & Int Port\" error"); 
                
								
                //
                // Int type test
                //
                ulTemp = (xHWREG(EXTI_RTSR) >> ulShift) & 1;
                ulTemp = ulTemp << 1;
                ulTemp1 = (xHWREG(EXTI_FTSR) >> ulShift) & 1;
                ulTemp |= ulTemp1;
                TestAssert((ulTemp == ulInt), 
                            "xgpio, \" xGPIOPinIntEnable & Int type\" error");
                
                //
                // Int request not mask test
                //
                ulTemp = (xHWREG(EXTI_IMR) >> ulShift) & 1;
                TestAssert((ulTemp == 1), 
                            "xgpio, \" xGPIOPinIntEnable & Int mask\" error");
            }
            
            //
            // GPIO pin Int disable test
            //
            xGPIOPinIntDisable(ulPort, ulPin);
            ulTemp = (xHWREG(EXTI_IMR) >> ulShift) & 1;
            TestAssert((ulTemp == 0), 
                        "xgpio, \" GPIOPinIntDisable \" error"); 
            
				 }	
		}				 		


    for(k = 0; k < 3; k++)
    {
        ulMode = ulPinMode[k];
        xGPIOSPinDirModeSet(PA0, ulMode);
        ulTemp = xGPIODirModeGet(xGPIO_PORTA_BASE, xGPIO_PIN_0);
        TestAssert((ulTemp == ulMode), 
                    "xgpio, \" GPIODirModeSet or GPIODirModeGet()\" error"); 
    }
  
    //
    // Pin write test
    // 
		GPIOPinWrite(GPIOA_BASE, GPIO_PIN_0 | GPIO_PIN_2, 1);
		ulTemp = xHWREG(GPIOA_BASE + GPIO_ODR) & (GPIO_PIN_0 | GPIO_PIN_2);
		TestAssert((ulTemp == GPIO_PIN_0 | GPIO_PIN_2), 
								"xgpio, \" GPIOPinWrite or GPIOPinRead \" error"); 

		//
		// Pin set test
		//
		GPIOPinSet(GPIOA_BASE, GPIO_PIN_0 | GPIO_PIN_2);
		ulTemp = xHWREG(GPIOA_BASE + GPIO_ODR) & (GPIO_PIN_0 | GPIO_PIN_2);
		TestAssert((ulTemp == GPIO_PIN_0 | GPIO_PIN_2), 
								"xgpio, \" GPIOPinSet \" error"); 
		
    //
    // Pin reset test
    //
    GPIOPinReset(GPIOA_BASE, GPIO_PIN_0 | GPIO_PIN_2);
    ulTemp = xHWREG(GPIOA_BASE + GPIO_ODR) & (GPIO_PIN_0 | GPIO_PIN_2);
    TestAssert((ulTemp == 0), "xgpio, \" GPIOPinReset \" error");
								
    //
    // Pin lock test
    //
/*	
    GPIOPinLockConfig(GPIOA_BASE, GPIO_PIN_0);
    ulTemp = xHWREG(GPIOA_BASE + GPIO_LCKR) & GPIO_PIN_0;
    TestAssert((ulTemp == GPIO_PIN_0), 
								"xgpio, \" GPIOPinLockConfig \" error");		
*/		
    
    //
    // ADC AFTO test
    //
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_IOPA);
    xSPinTypeADC(ADC0,PA0);
    ulTemp = xGPIODirModeGet(GPIOA_BASE, GPIO_PIN_0);
    TestAssert((ulTemp == GPIO_TYPE_IN_ANALOG), 
                "xgpio, \" xSPinTypeADC \" error");     
  
    //
    // CAN AFIO test
    //
		
    /*
    xSPinTypeCAN(CAN0RX, PD0);
    ulTemp = xGPIODirModeGet(GPIOD_BASE, GPIO_PIN_0);
    TestAssert((ulTemp == GPIO_DIR_MODE_IN), 
                "xgpio, \" xSPinTypeCAN & mode\" error");
    ulTemp = xHWREG(AFIO_MAPR) & GPIO_PD0_CAN0RX;
    TestAssert((ulTemp == GPIO_PD0_CAN0RX), 
                "xgpio, \" xSPinTypeCAN & remap\" error");
    
    
    xSPinTypeCAN(CAN0TX,PD1);
    ulTemp = xGPIODirModeGet(GPIOD_BASE, GPIO_PIN_1);
    TestAssert((ulTemp == GPIO_DIR_MODE_HWSTD), 
                "xgpio, \" xSPinTypeCAN & mode\" error");
    ulTemp = xHWREG(AFIO_MAPR) & GPIO_PD0_CAN0RX;
    TestAssert((ulTemp == GPIO_PD0_CAN0RX), 
                "xgpio, \" xSPinTypeCAN & remap\" error");  
    */
		
    
    //
    // I2C AFIO test
    //
    xSPinTypeI2C(I2C1SCK, PB8);
    ulTemp = xGPIODirModeGet(GPIOB_BASE, GPIO_PIN_8);
    TestAssert((ulTemp == GPIO_DIR_MODE_HWOD), 
                "xgpio, \" xSPinTypeI2C & mode\" error"); 
    ulTemp = xHWREG(AFIO_MAPR) & GPIO_PB8_I2C1SCK;
    TestAssert((ulTemp == 0x02), 
                "xgpio, \" xSPinTypeI2C & remap\" error");
    xSPinTypeI2C(I2C1SCK, PB8);
    ulTemp = xHWREG(AFIO_MAPR) & GPIO_PB8_I2C1SCK;
    TestAssert((ulTemp == 2), 
                "xgpio, \" xSPinTypeI2C & remap\" error");
    
    //
    // I2S AFIO test
    //
    xSPinTypeI2S(I2S2RXMCLK, PC6);
    ulTemp = xGPIODirModeGet(GPIOC_BASE, GPIO_PIN_6);
    TestAssert((ulTemp == GPIO_DIR_MODE_HWSTD), 
                "xgpio, \" xSPinTypeI2S & mode\" error");
    
    //
    // SPI AFIO test
    //
    xSPinTypeSPI(SPI1CLK(3), PB3);
    ulTemp = xGPIODirModeGet(GPIOB_BASE, GPIO_PIN_3);
    TestAssert((ulTemp == GPIO_DIR_MODE_HWSTD), 
                "xgpio, \" xSPinTypeI2S & mode\" error");
   
    //
    // Timer AFIO test
    //
    xSPinTypeTimer(TIM1ETR, PA12);
		
    //
    // 
    //
    xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_OUT);
    for(j = 0; j < 100; j++)
    {		
        GPIOPinSet(GPIOA_BASE, GPIO_PIN_5);
        for(i = 0; i < 10000; i++);
        GPIOPinReset(GPIOA_BASE, GPIO_PIN_5);
    }
		
		
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
