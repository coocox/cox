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


//*****************************************************************************
//
//! \brief Get the Test description of xsysctl002 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* XSysctl002GetTest(void)
{
    return "xsysctl, 002, xsysctl register and api test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl002 test.
//!
//! \return None.
//
//*****************************************************************************
static void XSysctl002Setup(void)
{
	SysCtlKeyAddrUnlock();
	xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL12M_EN;
	xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL32K_EN;
	xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC22M_EN;
	xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC10K_EN;
    //
    //  PLL FOUT enable
    //
	xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_OE;
	xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_PD;
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl002 test.
//!
//! \return None.
//
//*****************************************************************************
static void XSysctl002TearDown(void)
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
//! \brief xsysctl 002 test of Peripheral reset test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralReset_test(void)
{
    unsigned long ultemp;
    //
    // NUC1xx_SysCtl_Peripheral_ID Array
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
    for (ultemp = 0;ultemp <=24; ultemp++)
    {
		SysCtlPeripheralReset(ulSYSCTL_PERIPH[ultemp]);
		TestAssert( (0 == xHWREG(0x50000008))&&(0 == xHWREG(0x5000000C)), \
	   "xsysctl API \"SysCtlPeripheralReset(ulSYSCTL_PERIPH[ultemp])\" error!");
    }
}

//*****************************************************************************
//
//! \brief xsysctl 002 test of Peripheral Enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralEnable_test(void)
{
    unsigned long ultemp,ulRegVal;
    //
    // Enable Peripheral DMA Test
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PDMA);
    ulRegVal = xHWREG(0x50000204);
	TestAssert((SYSCLK_AHBCLK_PDMA_EN == (ulRegVal & SYSCLK_AHBCLK_PDMA_EN)), 
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_PDMA)\" error!");
    
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ISP);
    ulRegVal = xHWREG(0x50000204);
	TestAssert((SYSCLK_AHBCLK_ISP_EN == (ulRegVal & SYSCLK_AHBCLK_ISP_EN)),
		    "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_ISP)\" error!");
    
	SysCtlPeripheralEnable(SYSCTL_PERIPH_WDT);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_WDCLK_EN == (ulRegVal & SYSCLK_APBCLK_WDCLK_EN)), 
			"xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_WDT)\" error!");
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    ultemp = xHWREG(0x50000208);
	TestAssert((ultemp == (xHWREG(0x50000208))), 
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_RTC);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_RTC_EN == (ulRegVal & SYSCLK_APBCLK_RTC_EN)), 
			"xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_RTC)\" error!");
	//
    // Enable Peripheral TIME0 Test
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TMR0);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_TMR0_EN == (ulRegVal & SYSCLK_APBCLK_TMR0_EN)), 
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_TMR0)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TMR1);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_TMR1_EN == (ulRegVal & SYSCLK_APBCLK_TMR1_EN)), 
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_TMR1)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TMR2);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_TMR2_EN == (ulRegVal & SYSCLK_APBCLK_TMR2_EN)), 
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_TMR2)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TMR3);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_TMR3_EN == (ulRegVal & SYSCLK_APBCLK_TMR3_EN)), 
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_TMR3)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_FDIV);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_FDIV_EN == (ulRegVal & SYSCLK_APBCLK_FDIV_EN)), 
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_FDIV)\" error!");
	//
    // Enable Peripheral I2C Test
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_I2C0_EN == (ulRegVal & SYSCLK_APBCLK_I2C0_EN)), 
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_I2C1_EN == (ulRegVal & SYSCLK_APBCLK_I2C1_EN)), 
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1)\" error!");
    
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_SPI0_EN == (ulRegVal & SYSCLK_APBCLK_SPI0_EN)), 
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI1);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_SPI1_EN == (ulRegVal & SYSCLK_APBCLK_SPI1_EN)), 
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI1)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI2);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_SPI2_EN == (ulRegVal & SYSCLK_APBCLK_SPI2_EN)), 
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI2)\" error!");
	//
    // Enable Peripheral SPI3 Test
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI3);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_SPI3_EN == (ulRegVal & SYSCLK_APBCLK_SPI3_EN)), 
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI3)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_UART1_EN == (ulRegVal & SYSCLK_APBCLK_UART1_EN)), 
		  "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_UART2_EN == (ulRegVal & SYSCLK_APBCLK_UART2_EN)), 
		  "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM01);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_PWM01_EN == (ulRegVal & SYSCLK_APBCLK_PWM01_EN)),
		  "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM01)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM23);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_PWM23_EN == (ulRegVal & SYSCLK_APBCLK_PWM23_EN)),
		  "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM23)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM45);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_PWM45_EN == (ulRegVal & SYSCLK_APBCLK_PWM45_EN)),
		  "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM45)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM67);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_PWM67_EN == (ulRegVal & SYSCLK_APBCLK_PWM67_EN)),
		  "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM67)\" error!");
	//
    // Enable Peripheral CAN0 Test
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_CAN0_EN == (ulRegVal & SYSCLK_APBCLK_CAN0_EN)),
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_USBD);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_USBD_EN == (ulRegVal & SYSCLK_APBCLK_USBD_EN)),
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_USBD)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_ADC_EN == (ulRegVal & SYSCLK_APBCLK_ADC_EN)),
			"xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2S);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_I2S_EN == (ulRegVal & SYSCLK_APBCLK_I2S_EN)),
			"xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_I2S)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ACMP);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_ACMP_EN == (ulRegVal & SYSCLK_APBCLK_ACMP_EN)),
		   "xsysctl API \"SysCtlPeripheralEnable(SYSCTL_PERIPH_ACMP)\" error!");
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PS2);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((SYSCLK_APBCLK_PS2_EN == (ulRegVal & SYSCLK_APBCLK_PS2_EN)),
			 "xsysctl API \"SysCtlPeripheralReset(SYSCTL_PERIPH_PS2)\" error!");
}

//*****************************************************************************
//
//! \brief xsysctl 001 test of Peripheral Disable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralDisable_test(void)
{
    unsigned long ultemp,ulRegVal;

	ultemp = xHWREG(0x50000204);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_PDMA);
    ulRegVal = xHWREG(0x50000204);
	TestAssert((0 == (ulRegVal & SYSCLK_AHBCLK_PDMA_EN) && 
			((ultemp & (~SYSCLK_AHBCLK_PDMA_EN)) == ulRegVal)),
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_PDMA)\" error!");

	ultemp = xHWREG(0x50000204);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_ISP);
    ulRegVal = xHWREG(0x50000204);
	TestAssert((0 == (ulRegVal & SYSCLK_AHBCLK_ISP_EN) && 
			((ultemp & (~SYSCLK_AHBCLK_ISP_EN)) == ulRegVal)), 
		   "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_ISP)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_WDT);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_WDCLK_EN) && 
			((ultemp & (~SYSCLK_APBCLK_WDCLK_EN)) == ulRegVal)), 
		   "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_WDT)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIO);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & 0) && ((ultemp & (~0)) == ulRegVal)), 
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIO)\" error!");
    
	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_RTC);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_RTC_EN) && 
			((ultemp & (~SYSCLK_APBCLK_RTC_EN)) == ulRegVal)),
		   "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_RTC)\" error!");
    
	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_TMR0);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_TMR0_EN) && 
			((ultemp & (~SYSCLK_APBCLK_TMR0_EN)) == ulRegVal)), 
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_TMR0)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_TMR1);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_TMR1_EN) && 
			((ultemp & (~SYSCLK_APBCLK_TMR1_EN)) == ulRegVal)), 
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_TMR1)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_TMR2);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_TMR2_EN) && 
			((ultemp & (~SYSCLK_APBCLK_TMR2_EN)) == ulRegVal)),
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_TMR2)\" error!");
    //
    // Disable Peripheral Timer3 Test
    //
	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_TMR3);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_TMR3_EN) && 
			((ultemp & (~SYSCLK_APBCLK_TMR3_EN)) == ulRegVal)), 
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_TMR3)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_FDIV);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_FDIV_EN) &&
			((ultemp & (~SYSCLK_APBCLK_FDIV_EN)) == ulRegVal)),
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_FDIV)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_I2C0);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_I2C0_EN) && 
			((ultemp & (~SYSCLK_APBCLK_I2C0_EN)) == ulRegVal)),
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_I2C0)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_I2C1);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_I2C1_EN) && 
			((ultemp & (~SYSCLK_APBCLK_I2C1_EN)) == ulRegVal)), 
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_I2C1)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI0);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_SPI0_EN) && 
			((ultemp & (~SYSCLK_APBCLK_SPI0_EN)) == ulRegVal)), 
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI0)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI1);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_SPI1_EN) && 
			((ultemp & (~SYSCLK_APBCLK_SPI1_EN)) == ulRegVal)),
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI1)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI2);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_SPI2_EN) && 
			((ultemp & (~SYSCLK_APBCLK_SPI2_EN)) == ulRegVal)),
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI2)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI3);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_SPI3_EN) &&
			((ultemp & (~SYSCLK_APBCLK_SPI3_EN)) == ulRegVal)),
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI3)\" error!");

	/*ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_UART0);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_UART0_EN) &&
			((ultemp & (~SYSCLK_APBCLK_UART0_EN)) == ulRegVal)),
		 "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_UART0)\" error!");
    */
    //
    // Disable Peripheral UART1 TEST
    //
	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_UART1);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_UART1_EN) && 
			((ultemp & (~SYSCLK_APBCLK_UART1_EN)) == ulRegVal)),
		 "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_UART1)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_UART2);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_UART2_EN) && 
			((ultemp & (~SYSCLK_APBCLK_UART2_EN)) == ulRegVal)),
		 "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_UART2)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_PWM01);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_PWM01_EN) &&
			((ultemp & (~SYSCLK_APBCLK_PWM01_EN)) == ulRegVal)),
		 "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_PWM01)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_PWM23);
	TestAssert((0 == (xHWREG(0x50000208) & SYSCLK_APBCLK_PWM23_EN) &&
			((ultemp & (~SYSCLK_APBCLK_PWM23_EN)) == xHWREG(0x50000208))),
		 "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_PWM23)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_PWM45);
	TestAssert((0 == (xHWREG(0x50000208) & SYSCLK_APBCLK_PWM45_EN) &&
			((ultemp & (~SYSCLK_APBCLK_PWM45_EN)) == xHWREG(0x50000208))),
		 "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_PWM45)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_PWM67);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_PWM67_EN) &&
			((ultemp & (~SYSCLK_APBCLK_PWM67_EN)) == ulRegVal)),
		 "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_PWM67)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_CAN0);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_CAN0_EN) &&
			((ultemp & (~SYSCLK_APBCLK_CAN0_EN)) == ulRegVal)),
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_CAN0)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_USBD);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_USBD_EN) &&
			((ultemp & (~SYSCLK_APBCLK_USBD_EN)) == ulRegVal)), 
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_USBD)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_ADC);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_ADC_EN) && 
			((ultemp & (~SYSCLK_APBCLK_ADC_EN)) == ulRegVal)), 
		   "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_ADC)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_I2S);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_I2S_EN) && 
			((ultemp & (~SYSCLK_APBCLK_I2S_EN)) == ulRegVal)), 
		   "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_I2S)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_ACMP);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_ACMP_EN) && 
			((ultemp & (~SYSCLK_APBCLK_ACMP_EN)) == ulRegVal)), 
		  "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_ACMP)\" error!");

	ultemp = xHWREG(0x50000208);
	SysCtlPeripheralDisable(SYSCTL_PERIPH_PS2);
    ulRegVal = xHWREG(0x50000208);
	TestAssert((0 == (ulRegVal & SYSCLK_APBCLK_PS2_EN) && 
			((ultemp & (~SYSCLK_APBCLK_PS2_EN)) == ulRegVal)),
		   "xsysctl API \"SysCtlPeripheralDisable(SYSCTL_PERIPH_PS2)\" error!");
  
}

//*****************************************************************************
//
//! \brief xsysctl 002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void XSysctl002Execute(void)
{
	xsysctl_SysCtlPeripheralReset_test();
	xsysctl_SysCtlPeripheralEnable_test();
	xsysctl_SysCtlPeripheralDisable_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl002Register = {
		XSysctl002GetTest,
		XSysctl002Setup,
		XSysctl002TearDown,
		XSysctl002Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl01[] =
{
    &sTestXSysctl002Register,
    0
};