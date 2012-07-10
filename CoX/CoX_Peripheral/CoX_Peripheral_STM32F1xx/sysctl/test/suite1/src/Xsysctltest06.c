//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: MCBSTM32<br><br>
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



typedef struct 
{
    unsigned long ulPeripheralBase;
    unsigned long ulPeripheralID;
    unsigned long ulPeripheralIntNum;
}
tPeripheralTable;

//*****************************************************************************
//
// An array that maps the peripheral base and peripheral ID and interrupt number
// together to enablea peripheral or peripheral interrupt by a peripheral base.
//
//*****************************************************************************
static const tPeripheralTable g_pPeripherals[] =
{
    {ADC1_BASE,        xSYSCTL_PERIPH_ADC1,    xINT_ADC0},
    {ADC2_BASE,        xSYSCTL_PERIPH_ADC2,    xINT_ADC0},
    {DMA1_BASE,        xSYSCTL_PERIPH_DMA1,    xINT_DMA1},
    {DMA2_BASE,        xSYSCTL_PERIPH_DMA2,    xINT_DMA2},
    {GPIOA_BASE,       xSYSCTL_PERIPH_GPIOA,   xINT_GPIOA},
    {GPIOB_BASE,       xSYSCTL_PERIPH_GPIOB,   xINT_GPIOA},
    {GPIOC_BASE,       xSYSCTL_PERIPH_GPIOC,   xINT_GPIOA},
    {GPIOD_BASE,       xSYSCTL_PERIPH_GPIOD,   xINT_GPIOA},
    {GPIOE_BASE,       xSYSCTL_PERIPH_GPIOE,   xINT_GPIOA},
    {GPIOF_BASE,       xSYSCTL_PERIPH_GPIOF,   xINT_GPIOA},
    {GPIOG_BASE,       xSYSCTL_PERIPH_GPIOG,   xINT_GPIOA},
    {I2C1_BASE,        xSYSCTL_PERIPH_I2C1,    xINT_I2C1},
    {I2C2_BASE,        xSYSCTL_PERIPH_I2C2,    xINT_I2C2},
    {RTC_BASE,         xSYSCTL_PERIPH_RTC,     xINT_RTC},
    {SPI1_BASE,        xSYSCTL_PERIPH_SPI1,    xINT_SPI1},
    {SPI2_BASE,        xSYSCTL_PERIPH_SPI2,    xINT_SPI2},
    {SPI3_BASE,        xSYSCTL_PERIPH_SPI3,    xINT_SPI3},
    {TIM1_BASE,        xSYSCTL_PERIPH_TIMER1,  xINT_TIMER1},
    {TIM2_BASE,        xSYSCTL_PERIPH_TIMER2,  xINT_TIMER2},
    {TIM3_BASE,        xSYSCTL_PERIPH_TIMER3,  xINT_TIMER3},
    {TIM4_BASE,        xSYSCTL_PERIPH_TIMER4,  xINT_TIMER4},
    {TIM5_BASE,        xSYSCTL_PERIPH_TIMER5,  xINT_TIMER5},
    {TIM6_BASE,        xSYSCTL_PERIPH_TIMER6,  xINT_TIMER6},
    {TIM7_BASE,        xSYSCTL_PERIPH_TIMER7,  xINT_TIMER7},
    {TIM8_BASE,        xSYSCTL_PERIPH_TIMER8,  0},
    {TIM9_BASE,        xSYSCTL_PERIPH_TIMER9,  0},
    {TIM10_BASE,       xSYSCTL_PERIPH_TIMER10, 0},
    {TIM11_BASE,       xSYSCTL_PERIPH_TIMER11, 0},
    {TIM12_BASE,       xSYSCTL_PERIPH_TIMER12, 0},
    {TIM13_BASE,       xSYSCTL_PERIPH_TIMER13, 0},
    {TIM14_BASE,       xSYSCTL_PERIPH_TIMER14, 0},
    {USART1_BASE,      xSYSCTL_PERIPH_UART1,   xINT_UART1},
    {USART2_BASE,      xSYSCTL_PERIPH_UART2,   xINT_UART2},
    {USART3_BASE,      xSYSCTL_PERIPH_UART3,   xINT_UART3},
    {USART4_BASE,      xSYSCTL_PERIPH_UART4,   xINT_UART4},
    {USART5_BASE,      xSYSCTL_PERIPH_UART5,   xINT_UART5},
    {WWDG_BASE,        xSYSCTL_PERIPH_WDOG,    xINT_WDT},
};


//*****************************************************************************
//
//! \brief Get the Test description of xsysctl0601 register test.
//!
//! \return the desccription of the xcore0601 test.
//
//*****************************************************************************
static char* xSysctl0601GetTest(void)
{
    return "xsysctl, 0601, xSysCtlPeripheraIntNumGet function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl0601 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0601Setup(void)
{
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl0601 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0601TearDown(void)
{   

}


//*****************************************************************************
//
//! \brief xsysctl 0601 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0601Execute(void)
{
    unsigned long ulSize = 0;
    unsigned long i = 0;
    unsigned long ulTmp = 0;
    
    ulSize = sizeof(g_pPeripherals)/sizeof(g_pPeripherals[0]);
    for(i = 0; i < ulSize; i++) 
    {
        ulTmp = xSysCtlPeripheraIntNumGet(g_pPeripherals[i].ulPeripheralBase);
        TestAssert((ulTmp == g_pPeripherals[i].ulPeripheralIntNum),
                            "xSysCtl Function xSysCtlPeripheraIntNumGet Error");
    }
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl0601Register = {
    xSysctl0601GetTest,
    xSysctl0601Setup,
    xSysctl0601TearDown,
    xSysctl0601Execute,
};





//*****************************************************************************
//
//! \brief Get the Test description of xsysctl0602 register test.
//!
//! \return the desccription of the xcore0602 test.
//
//*****************************************************************************
static char* xSysctl0602GetTest(void)
{
    return "xsysctl, 0602, SysCtlRtcOutPutConfig function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl0602 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0602Setup(void)
{
    xHWREG(RCC_APB1ENR) |= RCC_APB1ENR_BKPEN;
    xHWREG(RCC_APB1ENR) |= RCC_APB1ENR_PWREN;
    xHWREG(PWR_CR)      |= PWR_CR_DBP;
    xHWREG(RCC_BDCR)    |= RCC_BDCR_BDRST;
    xHWREG(RCC_BDCR)    &= ~RCC_BDCR_BDRST;

    xHWREG(BKP_RTCCR) = (unsigned long) 0x00; 
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl0602 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0602TearDown(void)
{   
    
    xHWREG(BKP_RTCCR) = (unsigned long) 0x00;

    xHWREG(PWR_CR)      &= ~PWR_CR_DBP;
    xHWREG(RCC_APB1ENR) &= ~RCC_APB1ENR_BKPEN;
    xHWREG(RCC_APB1ENR) &= ~RCC_APB1ENR_PWREN;
    
}


//*****************************************************************************
//
//! \brief xsysctl 0602 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0602Execute(void)
{
    unsigned long OutputSource[4] = 
    {
       SYSCTL_RTC_NONE, 
       SYSCTL_RTC_SECOND,
       SYSCTL_RTC_ALARM,   
       SYSCTL_RTC_CALIBCLOCK,
    };
    unsigned long ulSize = 0;
    unsigned long i = 0;
    unsigned long ulTmp = 0;
    
    ulSize = sizeof(OutputSource)/sizeof(OutputSource[0]);
    for(i = 0; i < ulSize; i++) 
    {
        SysCtlRtcOutPutConfig(OutputSource[i]); 
        ulTmp = xHWREG(BKP_RTCCR);
        TestAssert((ulTmp == OutputSource[i]),
                "xSysCtl test 0602: SysCtlRtcOutPutConfig failed");
    }
    
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl0602Register = {
    xSysctl0602GetTest,
    xSysctl0602Setup,
    xSysctl0602TearDown,
    xSysctl0602Execute,
};




//*****************************************************************************
//
//! \brief Get the Test description of xsysctl0603 register test.
//!
//! \return the desccription of the xcore0603 test.
//
//*****************************************************************************
static char* xSysctl0603GetTest(void)
{
    return "xsysctl, 0603, SysCtlSetCalibValue function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl0603 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0603Setup(void)
{
    xHWREG(RCC_APB1ENR) |= RCC_APB1ENR_BKPEN;
    xHWREG(RCC_APB1ENR) |= RCC_APB1ENR_PWREN;
    xHWREG(PWR_CR)      |= PWR_CR_DBP;
    xHWREG(RCC_BDCR)    |= RCC_BDCR_BDRST;
    xHWREG(RCC_BDCR)    &= ~RCC_BDCR_BDRST;
    xHWREG(BKP_RTCCR) = (unsigned long) 0x00; 
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl0603 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0603TearDown(void)
{   
    xHWREG(BKP_RTCCR) = (unsigned long) 0x00; 
    xHWREG(PWR_CR)      &= ~PWR_CR_DBP;
    xHWREG(RCC_APB1ENR) &= ~RCC_APB1ENR_BKPEN;
    xHWREG(RCC_APB1ENR) &= ~RCC_APB1ENR_PWREN;
}


//*****************************************************************************
//
//! \brief xsysctl 0603 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0603Execute(void)
{
    unsigned long ulTestData[4] = 
    {
       0x00000000, 
       0x00000030, 
       0x0000007F, 
       0xFFFFFFFF, 
    };
    unsigned long ulSize = 0;
    unsigned long i = 0;
    unsigned long ulTmp = 0;
    
    ulSize = sizeof(ulTestData)/sizeof(ulTestData[0]);
    for(i = 0; i < ulSize; i++) 
    {
        SysCtlSetCalibValue(ulTestData[i]); 
        ulTmp = xHWREG(BKP_RTCCR) & 0x0000007F;
        TestAssert((ulTmp == (ulTestData[i] & 0x0000007F)),
                "xSysCtl test 0603: SysCtlSetCalibValue failed");
    }
    
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl0603Register = {
    xSysctl0603GetTest,
    xSysctl0603Setup,
    xSysctl0603TearDown,
    xSysctl0603Execute,
};


//*****************************************************************************
//
//! \brief Get the Test description of xsysctl0604 register test.
//!
//! \return the desccription of the xcore0604 test.
//
//*****************************************************************************
static char* xSysctl0604GetTest(void)
{
    return "xsysctl, 0604, SysCtlTamperPinActiveLevelConfig function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl0604 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0604Setup(void)
{
    xHWREG(RCC_APB1ENR) |= RCC_APB1ENR_BKPEN;
    xHWREG(RCC_APB1ENR) |= RCC_APB1ENR_PWREN;
    xHWREG(PWR_CR)      |= PWR_CR_DBP;
    xHWREG(RCC_BDCR)    |= RCC_BDCR_BDRST;
    xHWREG(RCC_BDCR)    &= ~RCC_BDCR_BDRST;
    xHWREG(BKP_CR)       = (unsigned long) 0x00;
    xHWREG(BKP_CSR)      = (unsigned long) 0x00; 
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl0604 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0604TearDown(void)
{   
    xHWREG(BKP_CR)       = (unsigned long) 0x00;
    xHWREG(BKP_CSR)      = (unsigned long) 0x00; 
    xHWREG(PWR_CR)      &= ~PWR_CR_DBP;
    xHWREG(RCC_APB1ENR) &= ~RCC_APB1ENR_BKPEN;
    xHWREG(RCC_APB1ENR) &= ~RCC_APB1ENR_PWREN;
}

//*****************************************************************************
//
//! \brief Test SysCtlTamperPinActiveLevelConfig function 
//!
//! \return None.
//
//*****************************************************************************
static void SysCtlTamperPinActiveLevelConfigTest(void)
{
    unsigned long ulTmp = 0;
    
    SysCtlTamperPinActiveLevelConfig(BKP_CR_TPAL_HIGH);
    ulTmp = xHWREG(BKP_CR);
    TestAssert(((ulTmp & BKP_CR_TPAL) == 0),
            "xSysCtl test 0604: SysCtlTamperPinActiveLevelConfig Set High failed");

    SysCtlTamperPinActiveLevelConfig(BKP_CR_TPAL_LOW);
    ulTmp = xHWREG(BKP_CR);
    TestAssert(((ulTmp & BKP_CR_TPAL) != 0),
            "xSysCtl test 0604: SysCtlTamperPinActiveLevelConfig Set Low failed");

}


//*****************************************************************************
//
//! \brief Test SysCtlTamperPinEnableTest function 
//!
//! \return None.
//
//*****************************************************************************
static void SysCtlTamperPinEnableTest(void)
{
    unsigned long tmp = 0;
    SysCtlTamperPinEnable();
    tmp = xHWREG(BKP_CR) & BKP_CR_TPE;
    TestAssert((tmp != 0), "xSysCtl test 0604: SysCtlTamperPinEnable failed");
}

//*****************************************************************************
//
//! \brief Test SysCtlTamperPinDisableTest function 
//!
//! \return None.
//
//*****************************************************************************
static void SysCtlTamperPinDisableTest(void)
{
    unsigned long tmp = 0;
    SysCtlTamperPinDisable();
    tmp = xHWREG(BKP_CR) & BKP_CR_TPE;
    TestAssert((tmp == 0), "xSysCtl test 0604: SysCtlTamperPinDisable failed");
}

//*****************************************************************************
//
//! \brief Test SysCtlTamperIntEnableTest function 
//!
//! \return None.
//
//*****************************************************************************
static void SysCtlTamperIntEnableTest(void)
{
    unsigned long tmp = 0;
    SysCtlTamperIntEnable();
    tmp = xHWREG(BKP_CSR) & BKP_CSR_TPIE;
    TestAssert((tmp != 0), "xSysCtl test 0604: SysCtlTamperIntEnable failed");

}

//*****************************************************************************
//
//! \brief Test SysCtlTamperIntDisableTest function 
//!
//! \return None.
//
//*****************************************************************************
static void SysCtlTamperIntDisableTest(void)
{
    unsigned long tmp = 0;
    SysCtlTamperIntDisable();
    tmp = xHWREG(BKP_CSR) & BKP_CSR_TPIE;
    TestAssert((tmp == 0), "xSysCtl test 0604: SysCtlTamperIntDisable failed");

}

//*****************************************************************************
//
//! \brief xsysctl 0604 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0604Execute(void)
{
    SysCtlTamperPinActiveLevelConfigTest();
    SysCtlTamperPinEnableTest();
    SysCtlTamperPinDisableTest();
    SysCtlTamperIntEnableTest();
    SysCtlTamperIntDisableTest();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl0604Register = {
    xSysctl0604GetTest,
    xSysctl0604Setup,
    xSysctl0604TearDown,
    xSysctl0604Execute,
};




//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl06[] =
{
    &sTestXSysctl0601Register,
    &sTestXSysctl0602Register,
    &sTestXSysctl0603Register,
    &sTestXSysctl0604Register,
    0
};

