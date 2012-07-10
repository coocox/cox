//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest05.c
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
//! \file xsysctltest05.c
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

unsigned long ulBackupDataAddr[] = 
{
    BKP_DR1 ,       // medium-density and low-density devices
    BKP_DR2 ,
    BKP_DR3 ,
    BKP_DR4 ,
    BKP_DR5 ,
    BKP_DR6 ,
    BKP_DR7 ,
    BKP_DR8 ,
    BKP_DR9 ,
    BKP_DR10,       

    BKP_DR11,      // high-density, XL-density and connectivity line devices
    BKP_DR12,
    BKP_DR13,
    BKP_DR14,
    BKP_DR15,
    BKP_DR16,
    BKP_DR17,
    BKP_DR18,
    BKP_DR19,
    BKP_DR20,
    BKP_DR21,
    BKP_DR22,
    BKP_DR23,
    BKP_DR24,
    BKP_DR25,
    BKP_DR26,
    BKP_DR27,
    BKP_DR28,
    BKP_DR29,
    BKP_DR30,
    BKP_DR31,
    BKP_DR32,
    BKP_DR33,
    BKP_DR34,
    BKP_DR35,
    BKP_DR36,
    BKP_DR37,
    BKP_DR38,
    BKP_DR39,
    BKP_DR40,
    BKP_DR41,
    BKP_DR42,
};




//*****************************************************************************
//
//! \brief Get the Test description of xsysctl0501 register test.
//!
//! \return the desccription of the xcore0501 test.
//
//*****************************************************************************
static char* xSysctl0501GetTest(void)
{
    return "xsysctl, 0501, SysCtlBackupDataWrite test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl0501 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0501Setup(void)
{
    unsigned long  i = 0;

    xHWREG(RCC_APB1ENR) |= RCC_APB1ENR_BKPEN;
    xHWREG(RCC_APB1ENR) |= RCC_APB1ENR_PWREN;
    xHWREG(PWR_CR)      |= PWR_CR_DBP;
    xHWREG(RCC_BDCR)    |= RCC_BDCR_BDRST;
    xHWREG(RCC_BDCR)    &= ~RCC_BDCR_BDRST;

    for(i = 0; i < 10; i++) 
    {
        xHWREG(ulBackupDataAddr[i]) = 0;
    }  

#if (defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL))
    for(i = 10; i < 42; i++) 
    {
        xHWREG(ulBackupDataAddr[i]) = 0;
    }  
#endif
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl0501 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0501TearDown(void)
{   
    unsigned long  i = 0;

    xHWREG(PWR_CR)      &= ~PWR_CR_DBP;
    xHWREG(RCC_APB1ENR) &= ~RCC_APB1ENR_BKPEN;
    xHWREG(RCC_APB1ENR) &= ~RCC_APB1ENR_PWREN;

    for(i = 0; i < 10; i++) 
    {
        xHWREG(ulBackupDataAddr[i]) = 0;
    }  

#if (defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL))
    for(i = 10; i < 42; i++) 
    {
        xHWREG(ulBackupDataAddr[i]) = 0;
    }  
#endif
}



//*****************************************************************************
//
//! \brief xsysctl 0501 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0501Execute(void)
{
    unsigned long  i = 0;

    xHWREG(RCC_APB1ENR) |= RCC_APB1ENR_BKPEN;
    xHWREG(RCC_APB1ENR) |= RCC_APB1ENR_PWREN;
    xHWREG(PWR_CR)      |= PWR_CR_DBP;

    for(i = 0; i < 10; i++) 
    {
        SysCtlBackupDataWrite(ulBackupDataAddr[i], i);
    }  

#if (defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL))
    for(i = 10; i < 42; i++) 
    {
        SysCtlBackupDataWrite(ulBackupDataAddr[i], i);
    }  
#endif 


    for(i = 0; i < 10; i++) 
    {
        TestAssert((xHWREG(ulBackupDataAddr[i]) == (unsigned long) i),
                "Test 0501: SysCtlBackupDataWrite function failed");
    }  

#if (defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL))
    for(i = 10; i < 42; i++) 
    {
        TestAssert((xHWREG(ulBackupDataAddr[i]) == (unsigned long) i),
                "Test 0501: SysCtlBackupDataWrite function failed");
    }  
#endif
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl0501Register = {
    xSysctl0501GetTest,
    xSysctl0501Setup,
    xSysctl0501TearDown,
    xSysctl0501Execute,
};



//*****************************************************************************
//
//! \brief Get the Test description of xsysctl0502 register test.
//!
//! \return the desccription of the xcore0502 test.
//
//*****************************************************************************
static char* xSysctl0502GetTest(void)
{
    return "xsysctl, 0502, SysCtlBackupDataRead test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl0502 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0502Setup(void)
{
    unsigned long  i = 0;

    xHWREG(RCC_APB1ENR) |= RCC_APB1ENR_BKPEN;
    xHWREG(RCC_APB1ENR) |= RCC_APB1ENR_PWREN;
    xHWREG(PWR_CR)      |= PWR_CR_DBP;
    xHWREG(RCC_BDCR)    |= RCC_BDCR_BDRST;
    xHWREG(RCC_BDCR)    &= ~RCC_BDCR_BDRST;

    for(i = 0; i < 10; i++) 
    {
        xHWREG(ulBackupDataAddr[i]) =  i;
    }  

#if (defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL))
    for(i = 10; i < 42; i++) 
    {
        xHWREG(ulBackupDataAddr[i]) =  i;
    }  
#endif
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl0502 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0502TearDown(void)
{   
    unsigned long  i = 0;

    xHWREG(PWR_CR)      &= ~PWR_CR_DBP;
    xHWREG(RCC_APB1ENR) &= ~RCC_APB1ENR_BKPEN;
    xHWREG(RCC_APB1ENR) &= ~RCC_APB1ENR_PWREN;

    for(i = 0; i < 10; i++) 
    {
        xHWREG(ulBackupDataAddr[i]) = 0;
    }  

#if (defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL))
    for(i = 10; i < 42; i++) 
    {
        xHWREG(ulBackupDataAddr[i]) = 0;
    }  
#endif
}



//*****************************************************************************
//
//! \brief xsysctl 0502 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0502Execute(void)
{
    unsigned long  i = 0;
    unsigned long  tmp = 0;

    for(i = 0; i < 10; i++) 
    {
        tmp = SysCtlBackupDataRead(ulBackupDataAddr[i]); 
        TestAssert( (tmp == i),
                "Test 0502: SysCtlBackupDataRead function failed");
    }  

#if (defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL))
    for(i = 10; i < 42; i++) 
    {
        tmp = SysCtlBackupDataRead(ulBackupDataAddr[i]); 
        TestAssert( (tmp == i),
                "Test 0502: SysCtlBackupDataRead function failed");
    }  
#endif 

}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl0502Register = {
    xSysctl0502GetTest,
    xSysctl0502Setup,
    xSysctl0502TearDown,
    xSysctl0502Execute,
};



//*****************************************************************************
//
//! \brief Get the Test description of xsysctl0503 register test.
//!
//! \return the desccription of the xcore0503 test.
//
//*****************************************************************************
static char* xSysctl0503GetTest(void)
{
    return "xsysctl, 0503, SysCtlBackupDomainReset test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl0503 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0503Setup(void)
{
    unsigned long  i = 0;

    xHWREG(RCC_APB1ENR) |= RCC_APB1ENR_BKPEN;
    xHWREG(RCC_APB1ENR) |= RCC_APB1ENR_PWREN;
    xHWREG(PWR_CR)      |= PWR_CR_DBP;
    xHWREG(RCC_BDCR)    |= RCC_BDCR_BDRST;
    xHWREG(RCC_BDCR)    &= ~RCC_BDCR_BDRST;

    for(i = 0; i < 10; i++) 
    {
        SysCtlBackupDataWrite(ulBackupDataAddr[i], i);
    }  

#if (defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL))
    for(i = 10; i < 42; i++) 
    {
        SysCtlBackupDataWrite(ulBackupDataAddr[i], i);
    }  
#endif
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl0503 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0503TearDown(void)
{   
    unsigned long  i = 0;

    xHWREG(PWR_CR)      &= ~PWR_CR_DBP;
    xHWREG(RCC_APB1ENR) &= ~RCC_APB1ENR_BKPEN;
    xHWREG(RCC_APB1ENR) &= ~RCC_APB1ENR_PWREN;

    for(i = 0; i < 10; i++) 
    {
        SysCtlBackupDataWrite(ulBackupDataAddr[i], 0);
    }  

#if (defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL))
    for(i = 10; i < 42; i++) 
    {
        SysCtlBackupDataWrite(ulBackupDataAddr[i], 0);
    }  
#endif
}



//*****************************************************************************
//
//! \brief xsysctl 0503 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl0503Execute(void)
{
    unsigned long  i = 0;

    SysCtlBackupDomainReset();

    for(i = 0; i < 10; i++) 
    {
        TestAssert((xHWREG(ulBackupDataAddr[i]) == 0),
                "Backup domain Reset Error");
    }  

#if (defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || defined(STM32F10X_XL) || defined(STM32F10X_CL))
    for(i = 10; i < 42; i++) 
    {
        TestAssert((xHWREG(ulBackupDataAddr[i]) == 0),
                "Backup domain Reset Error");
    }  
#endif
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl0503Register = {
    xSysctl0503GetTest,
    xSysctl0503Setup,
    xSysctl0503TearDown,
    xSysctl0503Execute,
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl05[] =
{
    &sTestXSysctl0501Register,
    &sTestXSysctl0502Register,
    &sTestXSysctl0503Register,
    0,
};

