//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: MCBSTM32 <br><br>
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
//! STM32F1xx_SysCtl_Peripheral_ID Array
//
unsigned long ulSYSCTL_PERIPH[] = { 
SYSCTL_PERIPH_ETHMACRX, SYSCTL_PERIPH_ETHMACTX, SYSCTL_PERIPH_SDIO, 
SYSCTL_PERIPH_FSMC, SYSCTL_PERIPH_CRC, SYSCTL_PERIPH_FLITF ,SYSCTL_PERIPH_SRAM,
SYSCTL_PERIPH_DMA2, SYSCTL_PERIPH_DMA1, SYSCTL_PERIPH_RTC, SYSCTL_PERIPH_ETHMAC,
SYSCTL_PERIPH_USBOTG, SYSCTL_PERIPH_TIM11, SYSCTL_PERIPH_TIM10, 
SYSCTL_PERIPH_TIM9, SYSCTL_PERIPH_ADC3, SYSCTL_PERIPH_USART1, SYSCTL_PERIPH_TIM8,
SYSCTL_PERIPH_SPI1, SYSCTL_PERIPH_TIM1, SYSCTL_PERIPH_ADC2, SYSCTL_PERIPH_ADC1,
SYSCTL_PERIPH_IOPG, SYSCTL_PERIPH_IOPF, SYSCTL_PERIPH_IOPE, SYSCTL_PERIPH_IOPD,
SYSCTL_PERIPH_IOPC, SYSCTL_PERIPH_IOPB, SYSCTL_PERIPH_IOPA, SYSCTL_PERIPH_AFIO,
SYSCTL_PERIPH_DAC, SYSCTL_PERIPH_PWR, SYSCTL_PERIPH_BKP, SYSCTL_PERIPH_CAN2,
SYSCTL_PERIPH_CAN1, SYSCTL_PERIPH_USB, SYSCTL_PERIPH_I2C2, SYSCTL_PERIPH_I2C1,
SYSCTL_PERIPH_UART5, SYSCTL_PERIPH_UART4, SYSCTL_PERIPH_USART3, 
SYSCTL_PERIPH_USART2, SYSCTL_PERIPH_SPI3, SYSCTL_PERIPH_SPI2, SYSCTL_PERIPH_WWDG,
SYSCTL_PERIPH_TIM14, SYSCTL_PERIPH_TIM13, SYSCTL_PERIPH_TIM12, SYSCTL_PERIPH_TIM7,
SYSCTL_PERIPH_TIM6, SYSCTL_PERIPH_TIM5, SYSCTL_PERIPH_TIM4, SYSCTL_PERIPH_TIM3,
SYSCTL_PERIPH_TIM2};


//
//! Peripheral Enable Mask
//
unsigned long ulPeriphEnableMask[] = {
RCC_AHBENR_ETHMACRXEN, RCC_AHBENR_ETHMACTXEN, RCC_AHBENR_SDIOEN,
RCC_AHBENR_FSMCEN, RCC_AHBENR_CRCEN, RCC_AHBENR_FLITFEN,RCC_AHBENR_SRAMEN,
RCC_AHBENR_DMA2EN, RCC_AHBENR_DMA1EN, RCC_BDCR_RTCEN,RCC_AHBENR_ETHMACEN,
RCC_AHBENR_OTGFSEN, RCC_APB2ENR_TIM11EN, RCC_APB2ENR_TIM10EN,
RCC_APB2ENR_TIM9EN, RCC_APB2ENR_ADC3EN, RCC_APB2ENR_USART1EN,RCC_APB2ENR_TIM8EN,
RCC_APB2ENR_SPI1EN, RCC_APB2ENR_TIM1EN,RCC_APB2ENR_ADC2EN, RCC_APB2ENR_ADC1EN,
RCC_APB2ENR_IOPGEN, RCC_APB2ENR_IOPFEN, RCC_APB2ENR_IOPEEN, RCC_APB2ENR_IOPDEN, 
RCC_APB2ENR_IOPCEN, RCC_APB2ENR_IOPBEN, RCC_APB2ENR_IOPAEN, RCC_APB2ENR_AFIOEN,
RCC_APB1ENR_DACEN, RCC_APB1ENR_PWREN,RCC_APB1ENR_BKPEN, RCC_APB1ENR_CAN2EN,
RCC_APB1ENR_CAN1EN, RCC_APB1ENR_USBEN, RCC_APB1ENR_I2C2EN, RCC_APB1ENR_I2C1EN,
RCC_APB1ENR_UART5EN, RCC_APB1ENR_UART4EN, RCC_APB1ENR_USART3EN, 
RCC_APB1ENR_USART2EN, RCC_APB1ENR_SPI3EN, RCC_APB1ENR_SPI2EN, RCC_APB1ENR_WWDGEN,
RCC_APB1ENR_TIM14EN, RCC_APB1ENR_TIM13EN, RCC_APB1ENR_TIM12EN, RCC_APB1ENR_TIM7EN,
RCC_APB1ENR_TIM6EN, RCC_APB1ENR_TIM5EN, RCC_APB1ENR_TIM4EN, RCC_APB1ENR_TIM3EN,
RCC_APB1ENR_TIM2EN};

unsigned long ulPeriprerAddr[] = { 
xDMA1_BASE, xADC1_BASE, xADC2_BASE, xTIMER1_BASE, xSPI1_BASE, 
xUART1_BASE, xGPIO_PORTA_BASE, xGPIO_PORTB_BASE, xGPIO_PORTC_BASE,
xGPIO_PORTD_BASE, xGPIO_PORTE_BASE,
xTIMER2_BASE, xTIMER3_BASE, xTIMER4_BASE, xWDT_BASE, xSPI2_BASE, xUART2_BASE,
xUART3_BASE, xI2C1_BASE, xI2C2_BASE};

unsigned long ulxPeriphEnableMask[] = {
RCC_AHBENR_DMA1EN, RCC_APB2ENR_ADC2EN, RCC_APB2ENR_ADC1EN, RCC_APB2ENR_TIM1EN,
RCC_APB2ENR_SPI1EN, RCC_APB2ENR_USART1EN, RCC_APB2ENR_IOPAEN, RCC_APB2ENR_IOPBEN, 
RCC_APB2ENR_IOPCEN, RCC_APB2ENR_IOPDEN, RCC_APB2ENR_IOPEEN,  
RCC_APB1ENR_TIM2EN, RCC_APB1ENR_TIM3EN, RCC_APB1ENR_TIM4EN, RCC_APB1ENR_WWDGEN,
RCC_APB1ENR_SPI2EN, RCC_APB1ENR_USART2EN, RCC_APB1ENR_USART3EN, 
RCC_APB1ENR_I2C1EN, RCC_APB1ENR_I2C2EN
};

//*****************************************************************************
//
//! \brief Get the Test description of xsysctl001 register test.
//!
//! \return the desccription of the xsysctl001 test.
//
//*****************************************************************************
static char* xSysctl001GetTest(void)
{
    return "xsysctl, 001, xsysctl register and api test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl001Setup(void)
{

}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl001TearDown(void)
{   
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_FLITF);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_SRAM);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

    xSPinTypeUART(UART1RX,PA10);
    xSPinTypeUART(UART1TX,PA9);
    

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
    //SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);

    xUARTConfigSet(USART1_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                        UART_CONFIG_STOP_ONE | 
                                        UART_CONFIG_PAR_NONE));

    xUARTEnable(USART1_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
    TestIOPut('\r');
    TestIOPut('\n');
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
    unsigned long ulTemp,ulRegVal,i;
    
    for(i = 4; i < 9; i++)
    {
        ulTemp = xHWREG(RCC_AHBENR);
        SysCtlPeripheralDisable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(RCC_AHBENR);
        TestAssert((0 == (ulRegVal & ulPeriphEnableMask[i]) && 
        ((ulTemp & (~ulPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!");
        
    }
    for(i = 16; (i < 30); i++)
    {
        ulTemp = xHWREG(RCC_APB2ENR);
        SysCtlPeripheralDisable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(RCC_APB2ENR);
        TestAssert((0 == (ulRegVal & ulPeriphEnableMask[i]) && 
        ((ulTemp & (~ulPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!");
        
    }
    for(i = 31; (i < 54); i++)
    {
        ulTemp = xHWREG(RCC_APB1ENR);
        SysCtlPeripheralDisable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(RCC_APB1ENR);
        TestAssert((0 == (ulRegVal & ulPeriphEnableMask[i]) && 
        ((ulTemp & (~ulPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!");
        
    }
    for(i = 0; i < 1; i++)
    {
        ulTemp = xHWREG(RCC_AHBENR);
        xSysCtlPeripheralDisable2(ulPeriprerAddr[i]);
        ulRegVal = xHWREG(RCC_AHBENR);
        TestAssert((0 == (ulRegVal & ulxPeriphEnableMask[i]) && 
        ((ulTemp & (~ulxPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!"); 
    }
    for(i = 1; i < 11; i++)
    {
        ulTemp = xHWREG(RCC_APB2ENR);
        xSysCtlPeripheralDisable2(ulPeriprerAddr[i]);
        ulRegVal = xHWREG(RCC_APB2ENR);
        TestAssert((0 == (ulRegVal & ulxPeriphEnableMask[i]) && 
        ((ulTemp & (~ulxPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!"); 
    }
    for(i = 11; i < 21; i++)
    {
        ulTemp = xHWREG(RCC_APB1ENR);
        xSysCtlPeripheralDisable2(ulPeriprerAddr[i]);
        ulRegVal = xHWREG(RCC_APB1ENR);
        TestAssert((0 == (ulRegVal & ulxPeriphEnableMask[i]) && 
        ((ulTemp & (~ulxPeriphEnableMask[i]))== ulRegVal)),"xsysctl API error!"); 
    }
}


//*****************************************************************************
//
//! \brief xsysctl 001 test of Peripheral reset test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralReset_test(void)
{
    unsigned long ulTemp;
    
    for (ulTemp = 10;ulTemp <= 54; ulTemp++)
    {
        SysCtlPeripheralReset(ulSYSCTL_PERIPH[ulTemp]);
        TestAssert( (0 == xHWREG(RCC_APB2RSTR))&&(0 == xHWREG(RCC_APB2RSTR)),
                                                          "xsysctl API error!");
    }
}

//*****************************************************************************
//
//! \brief xsysctl 001 test of Peripheral Enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralEnable_test(void)
{
    unsigned long ulTemp,ulRegVal,i;
    
    for(i = 4; (i < 9); i++)
    {
        if(i == 7)
            continue;
        ulTemp = xHWREG(RCC_AHBENR);
        SysCtlPeripheralEnable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(RCC_AHBENR);
        TestAssert((ulPeriphEnableMask[i] == (ulRegVal & ulPeriphEnableMask[i]))
                   ,"xsysctl API error!"); 
    }
    
    for(i = 16; (i < 30); i++)
    {
        if(i == 17 || i == 22 ||i == 23)
            continue;
        ulTemp = xHWREG(RCC_APB2ENR);
        SysCtlPeripheralEnable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(RCC_APB2ENR);
        TestAssert((ulPeriphEnableMask[i] == (ulRegVal & ulPeriphEnableMask[i])),
                   "xsysctl API error!");
    }
    for(i = 31; (i < 54); i++)
    {
        if(i == 33 || i == 38 || i == 39 || i == 42 || i == 45 || i == 46 ||
           i == 47 || i == 48 || i == 49 || i == 50)
            continue;
        ulTemp = xHWREG(RCC_APB1ENR);
        SysCtlPeripheralEnable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(RCC_APB1ENR);
        TestAssert((ulPeriphEnableMask[i] == (ulRegVal & ulPeriphEnableMask[i])),
                   "xsysctl API error!");
    }
    for(i = 0; i < 1; i++)
    {
        ulTemp = xHWREG(RCC_AHBENR);
        xSysCtlPeripheralEnable2(ulPeriprerAddr[i]);
        ulRegVal = xHWREG(RCC_AHBENR);
        TestAssert((ulxPeriphEnableMask[i] == (ulRegVal & ulxPeriphEnableMask[i])),
                   "xsysctl API error!"); 
    }
    for(i = 1; i < 11; i++)
    {
        ulTemp = xHWREG(RCC_APB2ENR);
        xSysCtlPeripheralEnable2(ulPeriprerAddr[i]);
        ulRegVal = xHWREG(RCC_APB2ENR);
        TestAssert((ulxPeriphEnableMask[i] == (ulRegVal & ulxPeriphEnableMask[i])),
                   "xsysctl API error!"); 
    }
    for(i = 11; i < 21; i++)
    {
        ulTemp = xHWREG(RCC_APB1ENR);
        xSysCtlPeripheralEnable2(ulPeriprerAddr[i]);
        ulRegVal = xHWREG(RCC_APB1ENR);
        TestAssert((ulxPeriphEnableMask[i] == (ulRegVal & ulxPeriphEnableMask[i])),
                   "xsysctl API error!"); 
    }
}


//*****************************************************************************
//
//! \brief xsysctl 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl001Execute(void)
{
    SysCtlDelay(100000);
    xsysctl_SysCtlPeripheralEnable_test();
    xsysctl_SysCtlPeripheralDisable_test();
    xsysctl_SysCtlPeripheralReset_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl001Register = {
    xSysctl001GetTest,
    xSysctl001Setup,
    xSysctl001TearDown,
    xSysctl001Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl02[] =
{
    &sTestXSysctl001Register,
    0
};