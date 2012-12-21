//*****************************************************************************
//
//! @page xdma_testcase xcore register test
//!
//! File: @ref xdmatest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xdma sub component.<br><br>
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
//! - \subpage test_xdma_register
//! .
//! \file xdmatest.c
//! \brief xdma test source file
//! \brief xdma test header file <br>
//
//*****************************************************************************
#include "xhw_memmap.h"
#include "test.h"
#include "Xsysctl.h"
#include "xdma.h"
#include "xhw_dma.h"
#include "xspi.h"
#include "xhw_spi.h"
//*****************************************************************************
//
//!\page test_xdma_register
//!
//!<h2>Description</h2>
//!Test xdma register. <br>
//!
//
//*****************************************************************************

#define DMA_CHANNEL             7

unsigned long ulSrcArrayTest[64];

unsigned long ulDestArrayTest[64];

//
// DMA Channel IDs Array
//
unsigned long ulChannelID[15] = 
{
    DMA1_CHANNEL_1,
    DMA1_CHANNEL_2,
    DMA1_CHANNEL_3,
    DMA1_CHANNEL_4,
    DMA1_CHANNEL_5,
    DMA1_CHANNEL_6,
    DMA1_CHANNEL_7,
    DMA2_CHANNEL_1,
    DMA2_CHANNEL_2,
    DMA2_CHANNEL_3,
    DMA2_CHANNEL_4,
    DMA2_CHANNEL_5,
    13,
    14
};
unsigned long ulDMAbase[] =
{
    0x40020008,
    0x4002001C,
    0x40020030,
    0x40020044,
    0x40020058,
    0x4002006C,
    0x40020080,
    0x40020408,
    0x4002041C,
    0x40020430,
    0x40020444,
    0x40020458
};

unsigned long ulDestAddr[] = 
{
    DMA_REQUEST_UART3_TX, 
    DMA_REQUEST_TIM1_UP,  
    xDMA_REQUEST_MEM, 
    DMA_REQUEST_TIM3_UP,     
    DMA_REQUEST_SPI1_TX,
    DMA_REQUEST_UART1_TX,     
    DMA_REQUEST_TIM1_TRIG,
    DMA_REQUEST_TIM1_COM,
    DMA_REQUEST_I2C2_TX,
    DMA_REQUEST_TIM1_UP,
    DMA_REQUEST_SPI2_TX,
    DMA_REQUEST_I2S2_TX,
    DMA_REQUEST_TIM3_TRIG,
    DMA_REQUEST_I2C1_TX,
    DMA_REQUEST_UART2_TX,
    DMA_REQUEST_TIM4_UP,
    /*DMA_REQUEST_TIM5_TRIG,
    DMA_REQUEST_TIM8_UP,
    DMA_REQUEST_TIM8_TRIG,
    DMA_REQUEST_TIM8_COM,
    DMA_REQUEST_TIM5_UP,
    DMA_REQUEST_SPI3_TX,
    DMA_REQUEST_I2S3_TX,
    DMA_REQUEST_TIM6_UP,
    DMA_REQUEST_DAC_CH1,
    DMA_REQUEST_SDIO_TX,
    DMA_REQUEST_TIM7_UP,
    DMA_REQUEST_DAC_CH2,
    DMA_REQUEST_UART4_TX*/
};

unsigned long ulSourceAddr[] = 
{
    DMA_REQUEST_ADC0_RX, 
    DMA_REQUEST_TIM2_CH3, 
    DMA_REQUEST_TIM4_CH1, 
    DMA_REQUEST_MEM, 
    DMA_REQUEST_TIM1_CH1,     
    DMA_REQUEST_TIM3_CH3,
    DMA_REQUEST_SPI1_RX,     
    DMA_REQUEST_TIM3_CH4,
    DMA_REQUEST_TIM1_CH4,
    DMA_REQUEST_TIM4_CH2,
    DMA_REQUEST_SPI2_RX,
    DMA_REQUEST_I2S2_RX,
    DMA_REQUEST_TIM2_CH1,
    DMA_REQUEST_TIM4_CH3,
    DMA_REQUEST_I2C2_RX,
    DMA_REQUEST_TIM1_CH3,
    DMA_REQUEST_TIM3_CH1,
    DMA_REQUEST_TIM2_CH2,
    DMA_REQUEST_TIM2_CH4,
    DMA_REQUEST_I2C1_RX,
    /*DMA_REQUEST_TIM5_CH4,
    DMA_REQUEST_TIM8_CH3,
    DMA_REQUEST_SPI3_RX,
    DMA_REQUEST_I2S3_RX,
    DMA_REQUEST_TIM8_CH4,
    DMA_REQUEST_TIM5_CH3,
    DMA_REQUEST_TIM8_CH1,
    DMA_REQUEST_TIM5_CH2,
    DMA_REQUEST_SDIO_RX,
    DMA_REQUEST_ADC3_RX,
    DMA_REQUEST_TIM8_CH2,
    DMA_REQUEST_TIM5_CH1,
    DMA_REQUEST_TIM1_CH2*/
};
//*****************************************************************************
//
//! \brief Get the Test description of xdma001 register test.
//!
//! \return the desccription of the xdma001 test.
//
//*****************************************************************************
static char* xDma001GetTest(void)
{
    return "xdma, 000, xdma register test";
}


//*****************************************************************************
//
//! \brief something should do before the test execute of xdma001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma001Setup(void)
{
    //
    // Enable Peripheral DMA
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_DMA1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_DMA2);
}


//*****************************************************************************
//
//! \brief something should do after the test execute of xdma001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma001TearDown(void)
{   
    //
    // Disable Peripheral DMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_DMA1);  
    SysCtlPeripheralDisable(SYSCTL_PERIPH_DMA2); 
}


//*****************************************************************************
//
//! \brief xdma 001 test of DMA enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaEnableTest(void)
{
    unsigned long i,ulRegVal;
    //
    // Test DMA Enable
    //
    for(i = 0;i < DMA_CHANNEL;i++)
    {
        DMAEnable(ulChannelID[i]);
        ulRegVal = xHWREG(ulDMAbase[i]);
        TestAssert((DMA_CCR1_EN & ulRegVal), "dma API error!"); 

    }
}


//*****************************************************************************
//
//! \brief xdma 001 test of DMA disable test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaDisableTest(void)
{
    unsigned long i,ulRegVal;
    //
    // Test DMA Disable
    //
    for(i = 0;i < DMA_CHANNEL;i++)
    {
        DMADisable(ulChannelID[i]); 
        ulRegVal = xHWREG(ulDMAbase[i]);
        TestAssert(((DMA_CCR1_EN & ulRegVal)  == 0x0000), "dma API error!");
    }
}

//*****************************************************************************
//
//! \brief xdma 001 test of DMA Interrupt Enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaIntEnableTest(void)
{
    unsigned long i,ulRegVal;
    
    //
    // Test DMA Interrupt Enable of DMA_EVENT_TC
    //
    for(i = 0;i < DMA_CHANNEL;i++)
    {
        DMAChannelIntEnable(ulChannelID[i] ,DMA_EVENT_TC);
        ulRegVal = xHWREG(ulDMAbase[i]) & DMA_CCR1_TCIE;
        TestAssert((DMA_CCR1_TCIE == ulRegVal), "dma API error!");
    }
    
    //
    // Test DMA Interrupt Enable of DMA_EVENT_ERROR
    //
    for(i = 0;i < DMA_CHANNEL;i++)
    {
        DMAChannelIntEnable(ulChannelID[i] ,DMA_EVENT_ERROR);
        ulRegVal = xHWREG(ulDMAbase[i]) & DMA_CCR1_TEIE;
        TestAssert((DMA_CCR1_TEIE == ulRegVal), "dma API error!");
    }
    
    //
    // Test DMA Interrupt Enable of DMA_EVENT_ERROR
    //
    for(i = 0;i < DMA_CHANNEL;i++)
    {
        DMAChannelIntEnable(ulChannelID[i] ,DMA_EVENT_HT);
        ulRegVal = xHWREG(ulDMAbase[i]) & DMA_CCR1_HTIE;
        TestAssert((DMA_CCR1_HTIE == ulRegVal), "dma API error!");
    }

}


//*****************************************************************************
//
//! \brief xdma 001 test of DMA Channel Dynamic Assign  test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaChannelDynamicAssignTest(void)
{
    unsigned long ulRegVal,i;
    //
    // Test DMA Channel Dynamic Assign
    //
    for(i = 0; i < 16; i++)
    {
        ulRegVal = DMAChannelDynamicAssign(xDMA_REQUEST_MEM, ulDestAddr[i]);
        DMAChannelDeAssign(ulRegVal);
        TestAssert((((ulRegVal < DMA_CHANNEL)&&(ulRegVal >=0))),"dma API error!");
        
    }
    
    for(i = 0; i < 20; i++)
    {
        ulRegVal = DMAChannelDynamicAssign(ulSourceAddr[i], xDMA_REQUEST_MEM);
        DMAChannelDeAssign(ulRegVal);
        TestAssert((((ulRegVal < DMA_CHANNEL)&&(ulRegVal >=0))),"dma API error!");
    }
    
}

//*****************************************************************************
//
//! \brief xdma 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xDma001Execute(void)
{
    xdmaEnableTest();
    xdmaDisableTest();
    xdmaIntEnableTest();
    xdmaChannelDynamicAssignTest();
}

//
// xdma register test case struct.
//
const tTestCase sTestXDma001Register = {
    xDma001GetTest,
    xDma001Setup,
    xDma001TearDown,
    xDma001Execute
};

//
// Xdma test suits.
//
const tTestCase * const psPatternXdma00[] =
{
    &sTestXDma001Register,
    0
};