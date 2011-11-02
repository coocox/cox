//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
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
//! - \subpage test_xsysctl_register
//! .
//! \file xsysctltest.c
//! \brief xsysctl test source file
//! \brief xsysctl test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_memmap.h"

//*****************************************************************************
//
//!\page test_xsysctl_register test_xsysctl_register
//!
//!<h2>Description</h2>
//!Test xsysctl register. <br>
//!
//
//*****************************************************************************
//
//! NUC1xx_SysCtl_Peripheral_ID Array
//
unsigned long ulSYSCTL_PERIPH[] = { 
     SYSCTL_PERIPH_PDMA,SYSCTL_PERIPH_GPIO,
     SYSCTL_PERIPH_TMR0,SYSCTL_PERIPH_TMR1,
     SYSCTL_PERIPH_TMR3,SYSCTL_PERIPH_TMR2,
     SYSCTL_PERIPH_I2C0,SYSCTL_PERIPH_I2C1,
     SYSCTL_PERIPH_SPI0,SYSCTL_PERIPH_SPI1,
     SYSCTL_PERIPH_SPI2,SYSCTL_PERIPH_SPI3,
     SYSCTL_PERIPH_UART2,SYSCTL_PERIPH_PWM01,
     SYSCTL_PERIPH_PWM23,SYSCTL_PERIPH_PWM45,
     SYSCTL_PERIPH_PWM67,SYSCTL_PERIPH_CAN0,
     SYSCTL_PERIPH_USBD,SYSCTL_PERIPH_ADC,
     SYSCTL_PERIPH_I2S,SYSCTL_PERIPH_ACMP,
     SYSCTL_PERIPH_UART1,SYSCTL_PERIPH_PS2};

//*****************************************************************************
//
//! \brief Get the Test description of xsysctl002 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* XSysctl003GetTest(void)
{
    return "xsysctl, 003, xsysctl register and api test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl002 test.
//!
//! \return None.
//
//*****************************************************************************
static void XSysctl003Setup(void)
{
	SysCtlKeyAddrUnlock();
	xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL12M_EN;
	xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL32K_EN;
	xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC22M_EN;
	xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC10K_EN;
	xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_OE;
	xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_PD;
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void XSysctl003TearDown(void)
{   
    unsigned long ulTemp;
    ulTemp = SYSCTL_SYSDIV_1|SYSCTL_XTAL_12MHZ|SYSCTL_OSC_MAIN|SYSCTL_PLL_PWRDN
                                                           | SYSCTL_INT_OSC_DIS;
	SysCtlHClockSet(ulTemp);

	SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
	SysCtlIPClockDividerSet(SYSCTL_PERIPH_UART_D|1);
}

//*****************************************************************************
//
//! \brief xsysctl 001 test of Peripheral Enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralEnable2_test(void)
{
    unsigned long ulTemp,ulRegVal;
    //
    // Enable Peripheral WDT Test
    //
    
	xSysCtlPeripheralEnable2(WDT_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_WDCLK_EN == (ulRegVal & SYSCLK_APBCLK_WDCLK_EN)), 
		  "xsysctl API \"xSysCtlPeripheralEnable2(SYSCTL_PERIPH_WDT)\" error!");
	
	xSysCtlPeripheralEnable2(GPIO_PORTA_BASE);
    ulTemp = xHWREG(0x50000208);
	TestAssert((ulTemp == (xHWREG(0x50000208))), 
		 "xsysctl API \"xSysCtlPeripheralEnable2(SYSCTL_PERIPH_GPIO)\" error!");
	//
    // Enable Peripheral TIME0 Test
    //
    xSysCtlPeripheralEnable2(TIMER0_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_TMR0_EN == (ulRegVal & SYSCLK_APBCLK_TMR0_EN)), 
		 "xsysctl API \"xSysCtlPeripheralEnable2(SYSCTL_PERIPH_TMR0)\" error!");
	
    xSysCtlPeripheralEnable2(TIMER1_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_TMR1_EN == (ulRegVal & SYSCLK_APBCLK_TMR1_EN)), 
		 "xsysctl API \"xSysCtlPeripheralEnable2(SYSCTL_PERIPH_TMR1)\" error!");
	
    xSysCtlPeripheralEnable2(TIMER2_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_TMR2_EN == (ulRegVal & SYSCLK_APBCLK_TMR2_EN)), 
		 "xsysctl API \"xSysCtlPeripheralEnable2(SYSCTL_PERIPH_TMR2)\" error!");
	
    xSysCtlPeripheralEnable2(TIMER3_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_TMR3_EN == (ulRegVal & SYSCLK_APBCLK_TMR3_EN)), 
		 "xsysctl API \"xSysCtlPeripheralEnable2(SYSCTL_PERIPH_TMR3)\" error!");
	//
    // Enable Peripheral I2C Test
    //
    xSysCtlPeripheralEnable2(I2C0_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_I2C0_EN == (ulRegVal & SYSCLK_APBCLK_I2C0_EN)), 
			      "xsysctl API \"xSysCtlPeripheralEnable2(I2C0_BASE)\" error!");
	
    xSysCtlPeripheralEnable2(I2C1_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_I2C1_EN == (ulRegVal & SYSCLK_APBCLK_I2C1_EN)), 
			      "xsysctl API \"xSysCtlPeripheralEnable2(I2C1_BASE)\" error!");
    
	xSysCtlPeripheralEnable2(SPI0_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_SPI0_EN == (ulRegVal & SYSCLK_APBCLK_SPI0_EN)), 
			      "xsysctl API \"xSysCtlPeripheralEnable2(SPI0_BASE)\" error!");
	
    xSysCtlPeripheralEnable2(SPI1_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_SPI1_EN == (ulRegVal & SYSCLK_APBCLK_SPI1_EN)), 
			      "xsysctl API \"xSysCtlPeripheralEnable2(SPI1_BASE)\" error!");
	
    xSysCtlPeripheralEnable2(SPI2_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_SPI2_EN == (ulRegVal & SYSCLK_APBCLK_SPI2_EN)), 
			      "xsysctl API \"xSysCtlPeripheralEnable2(SPI2_BASE)\" error!");
	//
    // Enable Peripheral SPI3 Test
    //
    xSysCtlPeripheralEnable2(SPI3_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_SPI3_EN == (ulRegVal & SYSCLK_APBCLK_SPI3_EN)), 
			      "xsysctl API \"xSysCtlPeripheralEnable2(SPI3_BASE)\" error!");
	
    xSysCtlPeripheralEnable2(UART1_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_UART1_EN == (ulRegVal & SYSCLK_APBCLK_UART1_EN)), 
		         "xsysctl API \"xSysCtlPeripheralEnable2(UART1_BASE)\" error!");
	
    xSysCtlPeripheralEnable2(UART2_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_UART2_EN == (ulRegVal & SYSCLK_APBCLK_UART2_EN)), 
		         "xsysctl API \"xSysCtlPeripheralEnable2(UART2_BASE)\" error!");
    //
    // Enable Peripheral PWMA Test
    //
    xSysCtlPeripheralEnable2(PWMA_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_PWM01_EN == (ulRegVal & SYSCLK_APBCLK_PWM01_EN)),
				  "xsysctl API \"xSysCtlPeripheralEnable2(PWMA_BASE)\" error!");
	
    xSysCtlPeripheralEnable2(PWMB_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_PWM23_EN == (ulRegVal & SYSCLK_APBCLK_PWM23_EN)),
				  "xsysctl API \"xSysCtlPeripheralEnable2(PWMB_BASE)\" error!");
    
    xSysCtlPeripheralEnable2(ACMP_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_ACMP_EN == (ulRegVal & SYSCLK_APBCLK_ACMP_EN)),
		          "xsysctl API \"xSysCtlPeripheralEnable2(ACMP_BASE)\" error!");
}

//*****************************************************************************
//
//! \brief xsysctl 002 test of Peripheral Disable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralDisable2_test(void)
{
    unsigned long ulTemp,ulRegVal;
	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(WDT_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_WDCLK_EN) && 
			      ((ulTemp & (~SYSCLK_APBCLK_WDCLK_EN)) == ulRegVal)), 
			      "xsysctl API \"xSysCtlPeripheralDisable2(WDT_BASE)\" error!");

	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(GPIO_PORTA_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & 0) && ((ulTemp & (~0)) == ulRegVal)), 
		   "xsysctl API \"xSysCtlPeripheralDisable2(GPIO_PORTA_BASE)\" error!");
    
    ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(GPIO_PORTB_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & 0) && ((ulTemp & (~0)) == ulRegVal)), 
		   "xsysctl API \"xSysCtlPeripheralDisable2(GPIO_PORTB_BASE)\" error!");

    ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(GPIO_PORTC_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & 0) && ((ulTemp & (~0)) == ulRegVal)), 
		   "xsysctl API \"xSysCtlPeripheralDisable2(GPIO_PORTC_BASE)\" error!");
    
    ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(GPIO_PORTD_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & 0) && ((ulTemp & (~0)) == ulRegVal)), 
		   "xsysctl API \"xSysCtlPeripheralDisable2(GPIO_PORTD_BASE)\" error!");
    
    ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(GPIO_PORTE_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & 0) && ((ulTemp & (~0)) == ulRegVal)), 
		   "xsysctl API \"xSysCtlPeripheralDisable2(GPIO_PORTE_BASE)\" error!");
    
	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(TIMER0_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_TMR0_EN) && 
			((ulTemp & (~SYSCLK_APBCLK_TMR0_EN)) == ulRegVal)), 
			   "xsysctl API \"xSysCtlPeripheralDisable2(TIMER0_BASE)\" error!");

	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(TIMER1_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_TMR1_EN) && 
			((ulTemp & (~SYSCLK_APBCLK_TMR1_EN)) == ulRegVal)), 
			   "xsysctl API \"xSysCtlPeripheralDisable2(TIMER1_BASE)\" error!");

	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(TIMER2_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_TMR2_EN) && 
			((ulTemp & (~SYSCLK_APBCLK_TMR2_EN)) == ulRegVal)),
			   "xsysctl API \"xSysCtlPeripheralDisable2(TIMER2_BASE)\" error!");
    //
    // Disable Peripheral Timer3 Test
    //
	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(TIMER3_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_TMR3_EN) && 
			((ulTemp & (~SYSCLK_APBCLK_TMR3_EN)) == ulRegVal)), 
			     "xsysctl API \"SysCtlPeripheralDisable(TIMER3_BASE)\" error!");

	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(I2C0_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_I2C0_EN) && 
			((ulTemp & (~SYSCLK_APBCLK_I2C0_EN)) == ulRegVal)),
			     "xsysctl API \"xSysCtlPeripheralDisable2(I2C0_BASE)\" error!");

	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(I2C1_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_I2C1_EN) && 
			((ulTemp & (~SYSCLK_APBCLK_I2C1_EN)) == ulRegVal)), 
			     "xsysctl API \"xSysCtlPeripheralDisable2(I2C1_BASE)\" error!");

	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(SPI0_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_SPI0_EN) && 
			((ulTemp & (~SYSCLK_APBCLK_SPI0_EN)) == ulRegVal)), 
			     "xsysctl API \"xSysCtlPeripheralDisable2(SPI0_BASE)\" error!");

	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(SPI1_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_SPI1_EN) && 
			((ulTemp & (~SYSCLK_APBCLK_SPI1_EN)) == ulRegVal)),
			     "xsysctl API \"xSysCtlPeripheralDisable2(SPI1_BASE)\" error!");

	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(SPI2_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_SPI2_EN) && 
			((ulTemp & (~SYSCLK_APBCLK_SPI2_EN)) == ulRegVal)),
			     "xsysctl API \"xSysCtlPeripheralDisable2(SPI2_BASE)\" error!");

	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(SPI3_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_SPI3_EN) &&
			((ulTemp & (~SYSCLK_APBCLK_SPI3_EN)) == ulRegVal)),
			     "xsysctl API \"xSysCtlPeripheralDisable2(SPI3_BASE)\" error!");

/*	ultemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(UART0_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_UART0_EN) &&
			((ultemp & (~SYSCLK_APBCLK_UART0_EN)) == ulRegVal)),
			    "xsysctl API \"SysCtlPeripheralDisable(UART0_BASE)\" error!");*/
    //
    // Disable Peripheral UART1 TEST
    //
	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(UART1_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_UART1_EN) && 
			((ulTemp & (~SYSCLK_APBCLK_UART1_EN)) == ulRegVal)),
			    "xsysctl API \"xSysCtlPeripheralDisable2(UART1_BASE)\" error!");

	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(UART2_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_UART2_EN) && 
			((ulTemp & (~SYSCLK_APBCLK_UART2_EN)) == ulRegVal)),
			    "xsysctl API \"xSysCtlPeripheralDisable2(UART2_BASE)\" error!");

	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(PWMA_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_PWM01_EN & SYSCLK_APBCLK_PWM23_EN)
	&&((ulTemp & (~SYSCLK_APBCLK_PWM01_EN) & (~SYSCLK_APBCLK_PWM23_EN)) == ulRegVal)),
			     "xsysctl API \"xSysCtlPeripheralDisable2(PWMA_BASE)\" error!");
 
	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(PWMB_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & ulRegVal & SYSCLK_APBCLK_PWM45_EN & SYSCLK_APBCLK_PWM67_EN)
	&&((ulTemp & (~SYSCLK_APBCLK_PWM45_EN) & (~SYSCLK_APBCLK_PWM67_EN)) == ulRegVal)),
			     "xsysctl API \"xSysCtlPeripheralDisable2(PWMB_BASE)\" error!");

	ulTemp = xHWREG(0x50000208);
	xSysCtlPeripheralDisable2(ACMP_BASE);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_ACMP_EN) && 
			                 ((ulTemp & (~SYSCLK_APBCLK_ACMP_EN)) == ulRegVal)), 
			       "xsysctl API \"SysCtlPeripheralDisable(ACMP_BASE)\" error!");
}

//*****************************************************************************
//
//! \brief xsysctl 002 test of reset() test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_Reset_test(void)
{
    unsigned long ulTemp;
    xtBoolean xtTemp;
//    SysCtlCPUReset();
//    SysCtlChipReset();
    ulTemp = SysCtlResetSrcGet();
    TestAssert(ulTemp == ulTemp, "xsysctl API \"SysCtlResetSrcGet\" error!");
    
    xtTemp = SysCtlKeyAddrUnlock();
    TestAssert(xtTemp == 1, "xsysctl API \"SysCtlKeyAddrUnlock\" error!");
    
    xtTemp = SysCtlKeyAddrLock();
    TestAssert(xtTemp == 0, "xsysctl API \"SysCtlKeyAddrUnlock\" error!");
    
    SysCtlResetSrcClear(SysCtlResetSrcGet());
    ulTemp = xHWREG(0x50000004);
    TestAssert(ulTemp == 0, "xsysctl API \"SysCtlKeyAddrUnlock\" error!");
}

//*****************************************************************************
//
//! \brief xsysctl 002 test of tempature sensor enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlTempatureSensorEnable_test(void)
{
    unsigned long ulTemp;
    SysCtlTempatureSensorEnable(xtrue);
    ulTemp = xHWREG(0x5000001C);
    TestAssert(ulTemp == 0x00000001, "xsysctl API \"SysCtlTempatureSensorEnable(xtrue)\" error!");
}


//*****************************************************************************
//
//! \brief xsysctl 002 test of SysCtl Power Down Enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPowerDownEnable_test(void)
{
    unsigned long ulTemp;
    SysCtlPowerDownEnable(xtrue);
    ulTemp = xHWREG(0x50000200);
    TestAssert(ulTemp == 0x0000009F, "xsysctl API \"SysCtlPowerDownEnable(xtrue)\" error!");
}

//*****************************************************************************
//
//! \brief xsysctl 002 test of BOD reset enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlBODRstEnable_test(void)
{
    unsigned long ulTemp;
    SysCtlBODRstEnable(xtrue);
    ulTemp = xHWREG(0x50000018);
    TestAssert(ulTemp == 0x0000008E, "xsysctl API \"SysCtlBODRstEnable(xtrue)\" error!");
}

//*****************************************************************************
//
//! \brief xsysctl 002 test of Peripheral reset test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_xSysCtlPeripheralReset2_test(void)
{
    unsigned long i;
    //
    //! NUC1xx_SysCtl_Peripheral_Base_Address Array
    //
    unsigned long ulSYSCTL_PERIPH_Addr[] = {ADC_BASE,PWMB_BASE,GPIO_PORTC_BASE,
    WDT_BASE,GPIO_PORTA_BASE,GPIO_PORTB_BASE,SPI0_BASE,SPI1_BASE,GPIO_PORTD_BASE,
    SPI2_BASE,GPIO_PORTE_BASE,SPI3_BASE,I2C0_BASE,I2C1_BASE,PWMA_BASE,UART1_BASE,
    UART2_BASE,TIMER0_BASE,TIMER1_BASE,TIMER2_BASE};
    
    for(i = 0; i <=20; i++)
    {
		xSysCtlPeripheralReset2(ulSYSCTL_PERIPH_Addr[i]);
		TestAssert( (0 == xHWREG(0x50000008))&&(0 == xHWREG(0x5000000C)), \
	   "xsysctl API \"xSysCtlPeripheralReset2(ulSYSCTL_PERIPH_Addr[i])\" error!");
    }
}

//*****************************************************************************
//
//! \brief xsysctl 002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void XSysctl003Execute(void)
{
    xsysctl_SysCtlPeripheralEnable2_test();
    xsysctl_SysCtlPeripheralDisable2_test();
    xsysctl_Reset_test();
    xsysctl_SysCtlTempatureSensorEnable_test();
    xsysctl_SysCtlBODRstEnable_test();
    xsysctl_SysCtlPowerDownEnable_test();
    xsysctl_xSysCtlPeripheralReset2_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl003Register = {
		XSysctl003GetTest,
		XSysctl003Setup,
		XSysctl003TearDown,
		XSysctl003Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl02[] =
{
    &sTestXSysctl003Register,
    0
};