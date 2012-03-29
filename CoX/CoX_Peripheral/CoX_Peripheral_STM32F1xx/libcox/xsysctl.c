//*****************************************************************************
//
//! \file xsysctl.c
//! \brief Driver for the system controller
//! \version V2.1.1.0
//! \date 11/20/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox 
//! All rights reserved.
//! 
//! Redistribution and use in source and binary forms, with or without 
//! modification, are permitted provided that the following conditions 
//! are met: 
//! 
//!     * Redistributions of source code must retain the above copyright 
//! notice, this list of conditions and the following disclaimer. 
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution. 
//!     * Neither the name of the <ORGANIZATION> nor the names of its 
//! contributors may be used to endorse or promote products derived 
//! from this software without specific prior written permission. 
//! 
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xcore.h"

static unsigned long s_ulExtClockMHz = 12;

//*****************************************************************************
//
// This macro extracts the array index out of the peripheral number.
//
//*****************************************************************************
#define SYSCTL_PERIPH_INDEX(a)  (((a) >> 28) & 0xf)

//*****************************************************************************
//
// This macro constructs the peripheral bit mask from the peripheral number.
//
//*****************************************************************************
#define SYSCTL_PERIPH_MASK(a)   (((a) & 0xffff) << (((a) & 0x001f0000) >> 16))

//*****************************************************************************
//
// This macro extracts the array index out of the peripheral clock source.
//
//*****************************************************************************
#define SYSCTL_PERIPH_INDEX_CLK(a)                                            \
                                (((a) >> 28) & 0xf)

//*****************************************************************************
//
// This macro constructs the peripheral bit mask from the peripheral clock source.
//
//*****************************************************************************
#define SYSCTL_PERIPH_ENUM_CLK(a)                                             \
                                (((a) & 0xff) << (((a) & 0x1f0000) >> 16))

//*****************************************************************************
//
// An array that maps the "peripheral set" number (which is stored in the upper
// nibble of the SYSCTL_PERIPH_* defines) to the GCR_IPRSTC? register that
// controls the software reset for that peripheral.
//
//*****************************************************************************
static const unsigned long g_pulIPRSTRegs[] =
{
    RCC_AHBRSTR,
    RCC_APB2RSTR,
    RCC_APB1RSTR
};

//*****************************************************************************
//
// An array that maps the "peripheral set" number (which is stored in the upper
// nibble of the SYSCTL_PERIPH_* defines) to the SYSCLK_AHBCLK register that
// controls the run-mode enable for that peripheral.
//
//*****************************************************************************
static const unsigned long g_pulAXBCLKRegs[] =
{
    RCC_AHBENR,
    RCC_APB2ENR,
    RCC_APB1ENR,
    RCC_BDCR
};

//*****************************************************************************
//
// An array that maps the "peripheral clock source set" number (which is stored
// in the upper nibble of the SYSCTL_PERIPH_* defines) to the SYSCLK_? 
// register that set the Clock source for that peripheral.
//
//*****************************************************************************
static const unsigned long g_pulCLKSELRegs[] =
{
    RCC_CFGR,
    RCC_BDCR,
    RCC_CFGR2
};

static volatile const unsigned char g_APBAHBPrescTable[16] = 
       {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
static volatile const unsigned char g_ADCPrescTable[4] = {2, 4, 6, 8};

//*****************************************************************************
//
//! Peripheral Base and ID Table structure type
//
//*****************************************************************************
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
    {DMA2_BASE,        xSYSCTL_PERIPH_DMA2,    xINT_DMA1},
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
//! \brief Provides a small delay.
//!
//! \param ulCount is the number of delay loop iterations to perform.
//!
//! This function provides a means of generating a constant length delay.  It
//! is written in assembly to keep the delay consistent across tool chains,
//! avoiding the need to tune the delay based on the tool chain in use.
//!
//! The loop takes 3 cycles/loop.
//!
//! \return None.
//
//*****************************************************************************
#if defined(gcc) || defined(__GNUC__)
void __attribute__((naked))
SysCtlDelay(unsigned long ulCount)
{
    __asm("    subs    r0, #1\n"
          "    bne     SysCtlDelay\n"
          "    bx      lr");
}
#endif
#if defined(ewarm) || defined(__ICCARM__)
void
SysCtlDelay(unsigned long ulCount)
{
    __asm("    subs    r0, #1\n"
          "    bne.n   SysCtlDelay\n"
          "    bx      lr");
}
#endif
#if defined(rvmdk) || defined(__CC_ARM)
__asm void
SysCtlDelay(unsigned long ulCount)
{
    subs    r0, #1;
    bne     SysCtlDelay;
    bx      lr;
}
#endif

//*****************************************************************************
//
//! \internal
//! Checks a peripheral identifier.
//!
//! \param ulPeripheral is the peripheral identifier.
//!
//! This function determines if a peripheral identifier is valid.
//!
//! \return Returns \b true if the peripheral identifier is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef xDEBUG
static xtBoolean
SysCtlPeripheralValid(unsigned long ulPeripheral)
{
    return((ulPeripheral == SYSCTL_PERIPH_ETHMAC) ||
           (ulPeripheral == SYSCTL_PERIPH_USBOTG) ||
           (ulPeripheral == SYSCTL_PERIPH_TIM11) ||
           (ulPeripheral == SYSCTL_PERIPH_TIM10) ||
           (ulPeripheral == SYSCTL_PERIPH_TIM9) ||
           (ulPeripheral == SYSCTL_PERIPH_ADC3) ||
           (ulPeripheral == SYSCTL_PERIPH_USART1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIM8) ||
           (ulPeripheral == SYSCTL_PERIPH_SPI1) ||
           (ulPeripheral == SYSCTL_PERIPH_TIM1) ||
           (ulPeripheral == SYSCTL_PERIPH_ADC2) ||
           (ulPeripheral == SYSCTL_PERIPH_ADC1) ||
           (ulPeripheral == SYSCTL_PERIPH_IOPG) ||
           (ulPeripheral == SYSCTL_PERIPH_IOPF) ||
           (ulPeripheral == SYSCTL_PERIPH_IOPE) ||
           (ulPeripheral == SYSCTL_PERIPH_IOPD) ||
           (ulPeripheral == SYSCTL_PERIPH_IOPC) ||
           (ulPeripheral == SYSCTL_PERIPH_IOPB) ||
           (ulPeripheral == SYSCTL_PERIPH_IOPA) ||
           (ulPeripheral == SYSCTL_PERIPH_AFIO) ||
           (ulPeripheral == SYSCTL_PERIPH_DAC) ||
           (ulPeripheral == SYSCTL_PERIPH_PWR) ||
           (ulPeripheral == SYSCTL_PERIPH_BKP) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN2) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN1) ||
           (ulPeripheral == SYSCTL_PERIPH_USB) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C2) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C1) ||
           (ulPeripheral == SYSCTL_PERIPH_UART5) ||
           (ulPeripheral == SYSCTL_PERIPH_UART4) ||
           (ulPeripheral == SYSCTL_PERIPH_USART3) ||
           (ulPeripheral == SYSCTL_PERIPH_USART2) ||
           (ulPeripheral == SYSCTL_PERIPH_SPI3) ||
           (ulPeripheral == SYSCTL_PERIPH_SPI2) ||
           (ulPeripheral == SYSCTL_PERIPH_WWDG) ||
           (ulPeripheral == SYSCTL_PERIPH_TIM14) ||
           (ulPeripheral == SYSCTL_PERIPH_TIM13) ||
           (ulPeripheral == SYSCTL_PERIPH_TIM12) ||
           (ulPeripheral == SYSCTL_PERIPH_TIM7) ||
           (ulPeripheral == SYSCTL_PERIPH_TIM6) ||
           (ulPeripheral == SYSCTL_PERIPH_TIM5) ||
           (ulPeripheral == SYSCTL_PERIPH_TIM4) ||
           (ulPeripheral == SYSCTL_PERIPH_TIM3) ||
           (ulPeripheral == SYSCTL_PERIPH_TIM2) ||
           (ulPeripheral == SYSCTL_PERIPH_ADC1));
}
#endif

//*****************************************************************************
//
//! Performs a software reset of a peripheral.
//!
//! \param ulPeripheral is the peripheral to reset.
//!
//! This function performs a software reset of the specified peripheral.  An
//! individual peripheral reset signal is asserted for a brief period and then
//! deasserted, returning the internal state of the peripheral to its reset
//! condition.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC1.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralReset(unsigned long ulPeripheral)
{
    //
    // Check the arguments.
    //
    xASSERT(SysCtlPeripheralValid(ulPeripheral));

    //
    // Put the peripheral into the reset state.
    //
    xHWREG(g_pulIPRSTRegs[SYSCTL_PERIPH_INDEX(ulPeripheral)]) |=
        SYSCTL_PERIPH_MASK(ulPeripheral);

    //
    // Delay for a little bit.
    //
    SysCtlDelay(16);

    //
    // Take the peripheral out of the reset state.
    //
    xHWREG(g_pulIPRSTRegs[SYSCTL_PERIPH_INDEX(ulPeripheral)]) &=
        ~(SYSCTL_PERIPH_MASK(ulPeripheral));
}

//*****************************************************************************
//
//! Enable a peripheral.
//!
//! \param ulPeripheral is the peripheral to enable.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC1.
//!
//! \note It takes five clock cycles after the write to enable a peripheral
//! before the the peripheral is actually enabled.  During this time, attempts
//! to access the peripheral will result in a bus fault.  Care should be taken
//! to ensure that the peripheral is not accessed during this brief time
//! period.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralEnable(unsigned long ulPeripheral)
{
    //
    // Check the arguments.
    //
    xASSERT(SysCtlPeripheralValid(ulPeripheral) ||
            (ulPeripheral == SYSCTL_PERIPH_ETHMACRX) ||
            (ulPeripheral == SYSCTL_PERIPH_ETHMACTX) ||
            (ulPeripheral == SYSCTL_PERIPH_SDIO) ||
            (ulPeripheral == SYSCTL_PERIPH_FSMC) ||
            (ulPeripheral == SYSCTL_PERIPH_CRC) ||
            (ulPeripheral == SYSCTL_PERIPH_FLITF) ||
            (ulPeripheral == SYSCTL_PERIPH_SRAM) ||
            (ulPeripheral == SYSCTL_PERIPH_DMA2) ||
            (ulPeripheral == SYSCTL_PERIPH_DMA1) ||
            (ulPeripheral == SYSCTL_PERIPH_RTC)
            );

    //
    // Enable this peripheral.
    //
    xHWREG(g_pulAXBCLKRegs[SYSCTL_PERIPH_INDEX(ulPeripheral)]) |=
        SYSCTL_PERIPH_MASK(ulPeripheral);
}

//*****************************************************************************
//
//! Disable a peripheral.
//!
//! \param ulPeripheral is the peripheral to disable.
//!
//! Peripherals are disabled with this function.  Once disabled, they will not
//! operate or respond to register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC1
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralDisable(unsigned long ulPeripheral)
{
    //
    // Check the arguments.
    //
    xASSERT(SysCtlPeripheralValid(ulPeripheral));

    //
    // Disable this peripheral.
    //
    xHWREG(g_pulAXBCLKRegs[SYSCTL_PERIPH_INDEX(ulPeripheral)]) &=
        ~(SYSCTL_PERIPH_MASK(ulPeripheral));
}
        
//*****************************************************************************
//
//! \brief Enables a peripheral.
//!
//! \param ulPeripheralBase a Peripheral base indicate which peripheral to be 
//! enabled.Details please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
void 
xSysCtlPeripheralEnable2(unsigned long ulPeripheralBase)
{
    unsigned long i;
    for(i=0; g_pPeripherals[i].ulPeripheralBase != 0; i++)
    {
        if(ulPeripheralBase == g_pPeripherals[i].ulPeripheralBase)
        {
            SysCtlPeripheralEnable(g_pPeripherals[i].ulPeripheralID);
            break;
        }
    }
}
        
//*****************************************************************************
//
//! \brief Disables a peripheral.
//!
//! \param ulPeripheralBase a Peripheral base indicate which peripheral to be 
//! enabled.Details please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! Peripherals are disabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
void 
xSysCtlPeripheralDisable2(unsigned long ulPeripheralBase)
{
    unsigned long i;
    for(i=0; g_pPeripherals[i].ulPeripheralBase != 0; i++)
    {
        if(ulPeripheralBase == g_pPeripherals[i].ulPeripheralBase)
        {
            SysCtlPeripheralDisable(g_pPeripherals[i].ulPeripheralID);
            break;
        }
    }
}
        
//*****************************************************************************
//
//! \brief Reset a peripheral.
//!
//! \param ulPeripheralBase a Peripheral base indicate which peripheral to be 
//! Reset.Details please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! Peripherals are Reset with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! \note None.
//!
//! \return None.
//
//*****************************************************************************
void 
xSysCtlPeripheralReset2(unsigned long ulPeripheralBase)
{
    unsigned long i;
    for(i=0; g_pPeripherals[i].ulPeripheralBase != 0; i++)
    {
        if(ulPeripheralBase == g_pPeripherals[i].ulPeripheralBase)
        {
            SysCtlPeripheralReset(g_pPeripherals[i].ulPeripheralID);
            break;
        }
    }
}

//*****************************************************************************
//
//! \brief Get the peripheral interrupt number through peripheral base.
//!
//! \param ulPeripheral The peripheral's base  
//!
//! \note It's especially useful to enable the short pin's corresponding 
//! peripheral interrupt: Use the short pin to Get the GPIO base through 
//! \ref xGPIOSPinToPort function, and then use this function to enable the GPIO
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
xSysCtlPeripheraIntNumGet(unsigned long ulPeripheralBase)
{
    unsigned long i;
    
    //
    // Check the arguments.
    //
    xASSERT((ulPeripheralBase == xGPIO_PORTA_BASE)       
            );
            
    for(i=0; g_pPeripherals[i].ulPeripheralBase != 0; i++)
    {
        if(ulPeripheralBase == g_pPeripherals[i].ulPeripheralBase)
        {
            break;
        }
    }
    return g_pPeripherals[i].ulPeripheralIntNum;
}

//*****************************************************************************
//
//! \brief Sets the clock of the device.
//!
//! \param ulConfig is the required configuration of the device clock.
//!
//! This function configures the clock of the device.  The input crystal
//! frequency, oscillator to be used, use of the PLL, and the system clock
//! divider are all configured with this function.
//!
//! The \e ulConfig parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The external crystal frequency is chosen with one of the following values:
//! \ref SYSCTL_XTAL_4MHZ, \ref SYSCTL_XTAL_5MHZ, \ref SYSCTL_XTAL_6MHZ,
//! \ref SYSCTL_XTAL_16MHZ.
//!
//! The oscillator source is chosen with one of the following values:
//! \ref SYSCTL_OSC_MAIN, \ref SYSCTL_OSC_INT.
//!
//! The internal and main oscillators and PLL are disabled with the
//! \ref SYSCTL_INT_OSC_DIS and \ref SYSCTL_MAIN_OSC_DIS flags, 
//! \ref SYSCTL_PLL_PWRDN respectively.
//! The external oscillator must be enabled in order to use an external clock
//! source.  Note that attempts to disable the oscillator used to clock the
//! device will be prevented by the hardware.
//! <br />
//! Details please refer to \ref XSysCtl_Clock_Set_Config_CoX.
//! 
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlClockSet(unsigned long ulSysClk, unsigned long ulConfig)
{
    volatile unsigned long ulStartUpCounter;
    xtBoolean xtStatus;
    unsigned long ulOscFreq;
    xASSERT((ulSysClk > 0 && ulSysClk <= 72000000));

    //
    // Set HSION bit
    //
    xHWREG(RCC_CR) |= RCC_CR_HSION;

    //
    // Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits
    //
    xHWREG(RCC_CFGR) &= 0xF0FF0000;
    
    //
    // Reset HSEON, CSSON and PLLON bits 
    //
    xHWREG(RCC_CR) &= 0xFEF6FFFF;

    //
    // Reset HSEBYP bit
    //
    xHWREG(RCC_CR) &= 0xFFFBFFFF;

    //
    // Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits
    //
    xHWREG(RCC_CFGR) &= 0xFF80FFFF;

    //
    // Reset HSEBYP bit
    //
    xHWREG(RCC_CR) &= 0xEBFFFFFF;
    
    //
    // Disable all interrupts and clear pending bits
    //
    xHWREG(RCC_CIR) &= 0x00FF0000;

    //
    // Disable all interrupts and clear pending bits
    //
    xHWREG(RCC_CFGR2) = 0x00000000; 
    
    //
    // Calc oscillator freq
    //
    s_ulExtClockMHz = ((ulConfig & SYSCTL_XTAL_MASK) >> 8);
    switch(ulConfig & SYSCTL_OSCSRC_M)
    {
        case SYSCTL_OSC_MAIN:
        case xSYSCTL_OSC_MAIN:
        {
            xASSERT(!(ulConfig & SYSCTL_MAIN_OSC_DIS));

            xHWREG(RCC_CR) &= ~RCC_CR_HSEON;
            xHWREG(RCC_CR) &= ~RCC_CR_HSERDY;

            xHWREG(RCC_CR) |= RCC_CR_HSEON;

            //
            // Wait till HSE is ready and if Time out is reached exit 
            //
            do
            {
                xtStatus = (xHWREG(RCC_CR) & RCC_CR_HSERDY) ? xtrue : xfalse;
                ulStartUpCounter++;  
            } while((ulStartUpCounter != 0x0500) && (xtStatus == xfalse));

            if(xtStatus == xtrue)
            {
                xHWREG(RCC_CFGR) &= ~RCC_CFGR_SW_M;
                xHWREG(RCC_CFGR) |= 1;

                while((xHWREG(RCC_CFGR) & RCC_CFGR_SWS_M) != 0x04);
            }
            else
            {
                while(1);
            }
            
            ulOscFreq = s_ulExtClockMHz*1000000; 
            
            if((ulConfig & SYSCTL_INT_OSC_DIS)!=0)
            {
                xHWREG(RCC_CR) &= ~RCC_CR_HSION;
            }
            if((ulConfig & SYSCTL_PLL_PWRDN)!=0)
            {
                xHWREG(RCC_CR) |= RCC_CR_PLLON;
            }
            break;
        }
        case SYSCTL_OSC_INT:
        {
            xASSERT(!(ulConfig & SYSCTL_INT_OSC_DIS));

            xHWREG(RCC_CR) |= RCC_CR_HSION;

            //
            // Wait till HSI is ready 
            //
            while((xHWREG(RCC_CR) & RCC_CR_HSIRDY) != RCC_CR_HSIRDY);

            xHWREG(RCC_CFGR) &= ~RCC_CFGR_SW_M;
            xHWREG(RCC_CFGR) |= 0;
            
            while((xHWREG(RCC_CFGR) & RCC_CFGR_SWS_M) != 0x00); 
            
            if((ulConfig & SYSCTL_INT_OSC_DIS)!=0)
            {
                xHWREG(RCC_CR) &= ~RCC_CR_HSION;
            }
            if((ulConfig & SYSCTL_PLL_PWRDN)!=0)
            {
                xHWREG(RCC_CR) |= RCC_CR_PLLON;
            }
            break;
        }
        default:
        {
            xASSERT(0);
            break;
        }
    }
    xHWREG(RCC_CFGR) &= ~(RCC_CFGR_PPRE2_M | RCC_CFGR_PPRE1_M | RCC_CFGR_HPRE_M);
    if(ulSysClk == ulOscFreq)
    {
        return;
    }
    else if (ulSysClk < ulOscFreq)
    {
        if((ulOscFreq % ulSysClk) == 0)
        {
            xHWREG(RCC_CFGR) |= (ulOscFreq / ulSysClk) << RCC_CFGR_HPRE_S;
            xHWREG(RCC_CFGR) |= SYSCTL_APB1CLOCK_DIV << RCC_CFGR_PPRE1_S;
            xHWREG(RCC_CFGR) |= SYSCTL_APB2CLOCK_DIV << RCC_CFGR_PPRE2_S;
        }
        else
        {
            xASSERT(0);
        }
        
    }
    else
    {
        xASSERT(!(ulConfig & xSYSCTL_PLL_PWRDN));
        xASSERT(((ulConfig & SYSCTL_OSCSRC_M) == xSYSCTL_OSC_MAIN) ||
                ((ulConfig & SYSCTL_OSCSRC_M) == xSYSCTL_OSC_INT));
        
        if((ulConfig & SYSCTL_PLL_MAIN) == SYSCTL_PLL_MAIN)
        {
            if((ulSysClk % ulOscFreq) == 0)
            {
                xHWREG(RCC_CFGR) |= RCC_CFGR_PLLSRC;
                xHWREG(RCC_CFGR) &= ~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL_M);
                xHWREG(RCC_CFGR) |= ((ulSysClk / ulOscFreq -2) << 
                                     RCC_CFGR_PLLMUL_S) & RCC_CFGR_PLLMUL_M;
            }
            else if(((ulSysClk*2) % ulOscFreq) == 0)
            {
                xHWREG(RCC_CFGR) |= RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC;
                xHWREG(RCC_CFGR) &= ~(RCC_CFGR_PLLMUL_M);
                xHWREG(RCC_CFGR) |= ((ulSysClk * 2 / ulOscFreq -2) << 
                                     RCC_CFGR_PLLMUL_S) & RCC_CFGR_PLLMUL_M;
            }
            else
            {
                xASSERT(0);
                return;
            }
        }
        else
        {
            if(((ulSysClk*2) % ulOscFreq) == 0)
            {
                xHWREG(RCC_CFGR) &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMUL_M);
                xHWREG(RCC_CFGR) |= ((ulSysClk * 2 / ulOscFreq) << 
                                     RCC_CFGR_PLLMUL_S) & RCC_CFGR_PLLMUL_M;
            }
            else
            {
                xASSERT(0);
                return;
            }
        }
        xHWREG(RCC_CFGR) |= SYSCTL_APB1CLOCK_DIV << RCC_CFGR_PPRE1_S;
        xHWREG(RCC_CFGR) |= SYSCTL_APB2CLOCK_DIV << RCC_CFGR_PPRE2_S;
        xHWREG(RCC_CR) |= RCC_CR_PLLON;
        while((xHWREG(RCC_CR) | RCC_CR_PLLRDY) == 0);
        xHWREG(RCC_CFGR) &= ~RCC_CFGR_SW_M;
        xHWREG(RCC_CFGR) |= 2;
        while((xHWREG(RCC_CFGR) & RCC_CFGR_SWS_M) != 0x08);
        return;
    }
}

//*****************************************************************************
//
//! \brief Enable the system control interrupts.
//!
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.  
//!
//! Enables the indicated Sysctl interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//! \b SYSCTL_INT_LSI, \b SYSCTL_INT_LSE, \b SYSCTL_INT_HSE, 
//! \b SYSCTL_INT_HSI,  \b SYSCTL_INT_PLL,  \b SYSCTL_INT_PLL2,
//! \b SYSCTL_INT_PLL3,
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlIntEnable(unsigned long ulIntFlags)
{ 
    //
    // Check the arguments.
    //
    xASSERT(((ulIntFlags & SYSCTL_INT_LSI) == SYSCTL_INT_LSI) || 
            ((ulIntFlags & SYSCTL_INT_LSE) == SYSCTL_INT_LSE) ||
            ((ulIntFlags & SYSCTL_INT_HSE) == SYSCTL_INT_HSE) ||
            ((ulIntFlags & SYSCTL_INT_HSI) == SYSCTL_INT_HSI) ||
            ((ulIntFlags & SYSCTL_INT_PLL) == SYSCTL_INT_PLL) ||
            ((ulIntFlags & SYSCTL_INT_PLL2) == SYSCTL_INT_PLL2) ||
            ((ulIntFlags & SYSCTL_INT_PLL3) == SYSCTL_INT_PLL3)
           );
    //
    // Enable the specified interrupts.
    //
    xHWREG(RCC_CIR) |= (ulIntFlags << 8);
}

//*****************************************************************************
//
//! \brief Disable the system control interrupts.
//!
//! \param ulIntFlags is the bit mask of the interrupt sources to be disabled.  
//!
//! Disable the indicated Sysctl interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//! \b SYSCTL_INT_LSI, \b SYSCTL_INT_LSE, \b SYSCTL_INT_HSE, 
//! \b SYSCTL_INT_HSI,  \b SYSCTL_INT_PLL,  \b SYSCTL_INT_PLL2,
//! \b SYSCTL_INT_PLL3,
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlIntDisable(unsigned long ulIntFlags)
{ 
    //
    // Check the arguments.
    //
    xASSERT(((ulIntFlags & SYSCTL_INT_LSI) == SYSCTL_INT_LSI) || 
            ((ulIntFlags & SYSCTL_INT_LSE) == SYSCTL_INT_LSE) ||
            ((ulIntFlags & SYSCTL_INT_HSE) == SYSCTL_INT_HSE) ||
            ((ulIntFlags & SYSCTL_INT_HSI) == SYSCTL_INT_HSI) ||
            ((ulIntFlags & SYSCTL_INT_PLL) == SYSCTL_INT_PLL) ||
            ((ulIntFlags & SYSCTL_INT_PLL2) == SYSCTL_INT_PLL2) ||
            ((ulIntFlags & SYSCTL_INT_PLL3) == SYSCTL_INT_PLL3)
           );
    //
    // Enable the specified interrupts.
    //
    xHWREG(RCC_CIR) &= ~(ulIntFlags << 8);
}

//*****************************************************************************
//
//! \brief Clear the system control interrupts flag.
//!
//! \param ulIntFlags is the bit mask of the interrupt flag to be cleared.  
//!
//! Clear the indicated Sysctl interrupt flag.
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//! \b SYSCTL_INT_LSI, \b SYSCTL_INT_LSE, \b SYSCTL_INT_HSE, 
//! \b SYSCTL_INT_HSI,  \b SYSCTL_INT_PLL,  \b SYSCTL_INT_PLL2,
//! \b SYSCTL_INT_PLL3,\b SYSCTL_INT_CSS.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlIntFlagClear(unsigned long ulIntFlags)
{ 
    //
    // Check the arguments.
    //
    xASSERT(((ulIntFlags & SYSCTL_INT_LSI) == SYSCTL_INT_LSI) || 
            ((ulIntFlags & SYSCTL_INT_LSE) == SYSCTL_INT_LSE) ||
            ((ulIntFlags & SYSCTL_INT_HSE) == SYSCTL_INT_HSE) ||
            ((ulIntFlags & SYSCTL_INT_HSI) == SYSCTL_INT_HSI) ||
            ((ulIntFlags & SYSCTL_INT_PLL) == SYSCTL_INT_PLL) ||
            ((ulIntFlags & SYSCTL_INT_PLL2) == SYSCTL_INT_PLL2) ||
            ((ulIntFlags & SYSCTL_INT_CSS) == SYSCTL_INT_CSS) ||
            ((ulIntFlags & SYSCTL_INT_PLL3) == SYSCTL_INT_PLL3)
           );
    //
    // Enable the specified interrupts.
    //
    xHWREG(RCC_CIR) |= (ulIntFlags << 16);
}

//*****************************************************************************
//
//! \brief Get the system control interrupts flag.
//!
//! \param None.  
//!
//! Get the indicated Sysctl interrupt flag.
//!
//! \return the return value is the logical OR of any of the following:
//! \b SYSCTL_INT_LSI, \b SYSCTL_INT_LSE, \b SYSCTL_INT_HSE, 
//! \b SYSCTL_INT_HSI,  \b SYSCTL_INT_PLL,  \b SYSCTL_INT_PLL2,
//! \b SYSCTL_INT_PLL3,\b SYSCTL_INT_CSS.
//
//*****************************************************************************
unsigned long 
SysCtlIntFlagGet(void)
{ 
    //
    // return the system control interrupts flag.
    //
    return (xHWREG(RCC_CIR) & 0xFF);
}

//*****************************************************************************
//
//! \brief Get the system control reset flag.
//!
//! \param None.  
//!
//! Get the indicated Sysctl reset flag.
//!
//! \return the return value is the logical OR of any of the following:
//! \b SYSCTL_RESET_LPWR, \b SYSCTL_RESET_WWDG, \b SYSCTL_RESET_IWDG,
//! \b SYSCTL_RESET_SFT, \b SYSCTL_RESET_POR, \b SYSCTL_RESET_PIN.
//
//*****************************************************************************
unsigned long
SysCtlResetFlagGet(void)
{ 
    //
    // return the system control reset flag.
    //
    return (xHWREG(RCC_CSR) & 0xFC000000);
}

//*****************************************************************************
//
//! \brief Clear the system control reset flag.
//!
//! \param None.  
//!
//! Clear the indicated Sysctl reset flag.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlResetFlagClear(void)
{ 
    //
    // Clear the system control reset flag.
    //
    xHWREG(RCC_CSR) |= RCC_CSR_RMVF;
}

//*****************************************************************************
//
//! \brief Config the system control LSI clock.
//!
//! \param ulLSIConfig.  
//!
//! Config the system control LSI clock.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlLSIConfig(unsigned long ulLSIConfig)
{ 
    //
    // Check the arguments.
    //
    xASSERT((ulLSIConfig == SYSCTL_LSI_OSC_DIS) ||
            (ulLSIConfig == SYSCTL_LSI_OSC_EN));
    
    //
    // Config the system control LSI clock.
    //
    xHWREG(RCC_CSR) &= ~(RCC_CSR_LSION | RCC_CSR_RMVF);
    xHWREG(RCC_CSR) |= ulLSIConfig;
    while(!(xHWREG(RCC_CSR) & RCC_CSR_LSIRDY));
}

//*****************************************************************************
//
//! \brief Config the system control LSE clock.
//!
//! \param ulLSEConfig .  
//!
//! Config the system control LSE clock.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlLSEConfig(unsigned long ulLSEConfig)
{ 
    //
    // Check the arguments.
    //
    xASSERT((ulLSEConfig == SYSCTL_LSE_OSC_DIS) ||
            (ulLSEConfig == SYSCTL_LSE_OSC_EN));
    //
    // Config the system control LSE clock.
    //
    xHWREG(RCC_BDCR) &= ~RCC_BDCR_LSEON;
    xHWREG(RCC_BDCR) |= ulLSEConfig;
    while(!(xHWREG(RCC_BDCR) & RCC_BDCR_LSERDY));
}

//*****************************************************************************
//
//! \brief Set a peripheral clock source and peripheral divide.
//!
//! \param ulPeripheralSrc is the peripheral clock source to set.
//!
//! Peripherals clock source are seted with this function.  At power-up, all 
//! Peripherals clock source are Peripherals clock source; they must be set in 
//! order to operate or respond to register reads/writes.
//!
//! The \e ulPeripheralSrc parameter must be only one of the following values:
//! \ref STM32F1xx_SysCtl_Stclk_Src.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralClockSourceSet(unsigned long ulPeripheralSrc)
{
 //
    // Check the arguments.
    //
    xASSERT((ulPeripheralSrc==SYSCTL_RTC_LSE)||
            (ulPeripheralSrc==SYSCTL_RTC_LSI)||
            (ulPeripheralSrc==SYSCTL_RTC_LSE_128)||
            (ulPeripheralSrc==SYSCTL_MCO_SYSCLK)||
            (ulPeripheralSrc==SYSCTL_MCO_HSI)||
            (ulPeripheralSrc==SYSCTL_MCO_HSE)||
            (ulPeripheralSrc==SYSCTL_MCO_PLL_2)||
            (ulPeripheralSrc==SYSCTL_MCO_PLL3_2)||
            (ulPeripheralSrc==SYSCTL_MCO_XT1)||
            (ulPeripheralSrc==SYSCTL_MCO_PLL3)||
            (ulPeripheralSrc==SYSCTL_I2S3_SYSCLK)||
            (ulPeripheralSrc==SYSCTL_I2S3_PLL3)||
            (ulPeripheralSrc==SYSCTL_I2S2_SYSCLK)||
            (ulPeripheralSrc==SYSCTL_I2S2_PLL3)|||
            (ulPeripheralSrc==SYSCTL_MCO_PLL2)         
           );
    if(SYSCTL_PERIPH_INDEX_CLK(ulPeripheralSrc) == 1)
    {
        xHWREG(RCC_BDCR) &= ~(RCC_BDCR_RTCSEL_M);
    }
    else if(SYSCTL_PERIPH_INDEX_CLK(ulPeripheralSrc) == 0)
    {
        xHWREG(RCC_CFGR) &= ~(RCC_CFGR_MCO_M);
    }
    else if(SYSCTL_PERIPH_INDEX_CLK(ulPeripheralSrc) == 2)
    {
        xHWREG(RCC_CFGR2) &= ~(SYSCTL_PERIPH_ENUM_CLK(ulPeripheralSrc | 1));
    }
    xHWREG(g_pulCLKSELRegs[SYSCTL_PERIPH_INDEX_CLK(ulPeripheralSrc)]) |=
        SYSCTL_PERIPH_ENUM_CLK(ulPeripheralSrc);
}

//*****************************************************************************
//
//! \brief Resets the device.
//!
//! This function will perform a software reset of the entire device.  The
//! processor and all peripherals will be reset and all device registers will
//! return to their default values (with the exception of the reset cause
//! register, which will maintain its current value but have the software reset
//! bit set as well).
//!
//! \return This function does not return.
//
//*****************************************************************************
void
SysCtlReset(void)
{
    //
    // Perform a software reset request.  This will cause the device to reset,
    // no further code will be executed.
    //
    xHWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;

    //
    // The device should have reset, so this should never be reached.  Just in
    // case, loop forever.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
//! \brief Puts the processor into sleep mode.
//!
//! This function places the processor into sleep mode; it will not return
//! until the processor returns to run mode.  The peripherals that are enabled
//! via SysCtlPeripheralSleepEnable() continue to operate and can wake up the
//! processor (if automatic clock gating is enabled with
//! SysCtlPeripheralClockGating(), otherwise all peripherals continue to
//! operate).
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlSleep(void)
{
    //
    // Wait for an interrupt.
    //
    xCPUwfi();
}

//*****************************************************************************
//
//! \brief The function is used to Reset Backup domain 
//!
//! \param None.
//!
//! The function is used to Reset Backup domain 
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlBackupDomainReset(void)
{
    xHWREG(RCC_BDCR) |= RCC_BDCR_BDRST;
}

//*****************************************************************************
//
//! \brief The function is used to Get HCLK clock and the UNIT is in Hz
//!
//! \param None.
//!
//! The function is used to Get HCLK clock and the UNIT is in Hz
//!
//! \return HCLK clock frequency in Hz 
//
//*****************************************************************************
unsigned long 
SysCtlHClockGet(void)
{
    unsigned long ulTemp = 0, ulPllMull = 0, ulPllSource = 0, ulPresc = 0;
    unsigned long ulHclk;

    //
    // STM32F10X_CL
    //
#ifdef  STM32F10X_CL
    unsigned long ulPrediv1Source = 0, ulPrediv1Factor = 0, ulPrediv2Factor = 0, 
                  ulPll2Mull = 0;
#endif 

#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)
    unsigned long ulPrediv1Factor = 0;
#endif
    
    //
    // Get SYSCLK source
    //
    ulTemp = xHWREG(RCC_CFGR) & RCC_CFGR_SWS_M;
    switch (ulTemp)
    {
        //
        // HSI used as system clock
        //
        case 0x00: 
        {
            ulHclk = (unsigned long)8000000;
            break;
        }
        //
        // HSE used as system clock
        //
        case 0x04: 
        {
            ulHclk = s_ulExtClockMHz*1000000;
            break;
        }
        //
        // PLL used as system clock
        //
        case 0x08: 
        {
            //
            // Get PLL clock source and multiplication factor
            //
            ulPllMull = xHWREG(RCC_CFGR) & RCC_CFGR_PLLMUL_M;
            ulPllSource = xHWREG(RCC_CFGR) & RCC_CFGR_PLLSRC;
                  
#ifndef STM32F10X_CL      
            ulPllMull = ( ulPllMull >> 18) + 2;
      
            if (ulPllSource == 0x00)
            {
                //
                // HSI oscillator clock divided by 2 selected as PLL clock entry 
                //
                ulHclk = (8000000 >> 1) * ulPllMull;
            }
            else
            {
 #if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)
                ulPrediv1Factor = (xHWREG(RCC_CFGR2) & RCC_CFGR2_PREDIV1_M) + 1;
                //
                // HSE oscillator clock selected as PREDIV1 clock entry 
                //
                ulHclk = (s_ulExtClockMHz*1000000 / ulPrediv1Factor) * ulPllMull; 
 #else
                //
                // HSE selected as PLL clock entry 
                //
                if ((xHWREG(RCC_CFGR) & RCC_CFGR_PLLXTPRE) != 0)
                {
                    //
                    // HSE oscillator clock divided by 2 
                    //
                    ulHclk = ((s_ulExtClockMHz*1000000) >> 1) * ulPllMull;
                }
                else
                {
                    ulHclk = s_ulExtClockMHz*1000000 * ulPllMull;
                }
 #endif
            }
#else
            ulPllMull = ulPllMull >> 18;
          
            if (ulPllMull != 0x0D)
            {
                ulPllMull += 2;
            }
            else
            { 
                //
                // PLL multiplication factor = PLL input clock * 6.5 
                //
                ulPllMull = 13 / 2; 
            }
                  
            if (ulPllSource == 0x00)
            {
                //
                // HSI oscillator clock divided by 2 selected as PLL clock entry 
                //
                ulHclk = (8000000 >> 1) * ulPllMull;
            }
            else
            {
                //
                // PREDIV1 selected as PLL clock entry 
                //
                
                //
                // Get PREDIV1 clock source and division factor
                //
                ulPrediv1Source = (xHWREG(RCC_CFGR2) & RCC_CFGR2_PREDIV1SRC);
                ulPrediv1Factor = (xHWREG(RCC_CFGR2) & RCC_CFGR2_PREDIV1_M) + 1;
              
                if (ulPrediv1Source == 0)
                { 
                    //
                    // HSE oscillator clock selected as PREDIV1 clock entry 
                    //
                    ulHclk = (s_ulExtClockMHz*1000000 / ulPrediv1Factor) * ulPllMull;          
                }
                else
                {
                    //
                    // PLL2 clock selected as PREDIV1 clock entry 
                    //
        
                    //
                    // Get PREDIV2 division factor and PLL2 multiplication factor 
                    //
                    ulPrediv2Factor = ((xHWREG(RCC_CFGR2) & RCC_CFGR2_PREDIV2_M)
                                        >> RCC_CFGR2_PREDIV2_S) + 1;
                    ulPll2Mull = ((xHWREG(RCC_CFGR2) & RCC_CFGR2_PLL2MUL_M) >> 8 ) + 2; 
                    ulHclk = (((s_ulExtClockMHz*1000000 / ulPrediv2Factor) * 
                             ulPll2Mull) / ulPrediv1Factor) * ulPllMull;                         
                }
            }
#endif 
        break;
        }
        default: 
        {
            ulHclk = 8000000;
            break;
        }
    }
    ulTemp = (xHWREG(RCC_CFGR) & RCC_CFGR_HPRE_M) >> RCC_CFGR_HPRE_S;
    ulPresc = g_APBAHBPrescTable[ulTemp];
    ulHclk = ulHclk >> ulPresc;
    return ulHclk;
}

//*****************************************************************************
//
//! \brief The function is used to Get APB1 clock and the UNIT is in Hz
//!
//! \param None.
//!
//! The function is used to Get APB1 clock and the UNIT is in Hz
//!
//! \return APB1 clock frequency in Hz 
//
//*****************************************************************************
unsigned long 
SysCtlAPB1ClockGet(void)
{
    unsigned long ulTemp,ulAPB1Clock;
    ulAPB1Clock = SysCtlHClockGet();
    ulTemp = (xHWREG(RCC_CFGR) & RCC_CFGR_PPRE1_M) >> RCC_CFGR_PPRE1_S;
    ulTemp = (unsigned long)g_APBAHBPrescTable[ulTemp];
    ulAPB1Clock = ulAPB1Clock >> ulTemp;
    return ulAPB1Clock;
}

//*****************************************************************************
//
//! \brief The function is used to Get APB2 clock and the UNIT is in Hz
//!
//! \param None.
//!
//! The function is used to Get APB2 clock and the UNIT is in Hz
//!
//! \return APB2 clock frequency in Hz 
//
//*****************************************************************************
unsigned long 
SysCtlAPB2ClockGet(void)
{
    unsigned long ulTemp,ulAPB2Clock;
    ulAPB2Clock = SysCtlHClockGet();
    ulTemp = (xHWREG(RCC_CFGR) & RCC_CFGR_PPRE2_M) >> RCC_CFGR_PPRE2_S;
    ulTemp = (unsigned long)g_APBAHBPrescTable[ulTemp];
    ulAPB2Clock = ulAPB2Clock >> ulTemp;
    return ulAPB2Clock;
}

//*****************************************************************************
//
//! \brief Enables access to the RTC and backup registers.
//!
//! \param None.
//!
//! The function is used to enable access to the RTC and backup registers.
//!
//! \return None 
//
//*****************************************************************************
void 
SysCtlBackupAccessEnable(void)
{
    xHWREG(PWR_CR) |= PWR_CR_DBP;
}

//*****************************************************************************
//
//! \brief Disables access to the RTC and backup registers.
//!
//! \param None.
//!
//! The function is used to disable access to the RTC and backup registers.
//!
//! \return None 
//
//*****************************************************************************
void 
SysCtlBackupAccessDisable(void)
{
    xHWREG(PWR_CR) &= ~PWR_CR_DBP;
}

//*****************************************************************************
//
//! \brief Configures the voltage threshold detected by the Power Voltage 
//! Detector(PVD).
//!
//! \param ulConfig specifies the PVD detection level configurations
//!
//! The \e ulConfig parameter is the logical OR of two different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The enable or disable PVD is chosen with one of the following values:
//! \ref SYSCTL_PVD_EN, \ref SYSCTL_PVD_DIS.
//!
//! The PVD detection level is chosen with one of the following values:
//! \ref SYSCTL_PVDLEVEL_2V2, \ref SYSCTL_PVDLEVEL_2V3 \ref SYSCTL_PVDLEVEL_2V4,
//! \ref SYSCTL_PVDLEVEL_2V5, \ref SYSCTL_PVDLEVEL_2V6, \ref SYSCTL_PVDLEVEL_2V7,
//! \ref SYSCTL_PVDLEVEL_2V8, \ref SYSCTL_PVDLEVEL_2V9.
//!
//! The function is used to configures the voltage threshold detected by the 
//! Power Voltage Detector(PVD).
//!
//! \return None 
//
//*****************************************************************************
void
SysCtlPVDLevelConfig(unsigned long ulConfig)
{
    xHWREG(PWR_CR) &= ~(PWR_CR_PVDE | PWR_CR_PLS_M);
    xHWREG(PWR_CR) |= ulConfig;
}

//*****************************************************************************
//
//! \brief Enables the WakeUp Pin functionality.
//!
//! \param None.
//!
//! The function is used to enable the WakeUp Pin functionality.
//!
//! \return None 
//
//*****************************************************************************
void 
SysCtlWakeUpPinEnable(void)
{
    xHWREG(PWR_CSR) |= PWR_CSR_EWUP;
}

//*****************************************************************************
//
//! \brief Disables the WakeUp Pin functionality.
//!
//! \param None.
//!
//! The function is used to disable the WakeUp Pin functionality.
//!
//! \return None 
//
//*****************************************************************************
void 
SysCtlWakeUpPinDisable(void)
{
    xHWREG(PWR_CSR) &= ~PWR_CSR_EWUP;
}

//*****************************************************************************
//
//! \brief Enters STOP mode.
//!
//! \param ulConfig specifies the STOP mode configurations.
//!
//! The \e ulConfig parameter is the logical OR of two different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The Voltage regulator is chosen with one of the following values:
//! \ref SYSCTL_REGULATOR_ON, \ref SYSCTL_REGULATOR_LP.
//!
//! The WFI or WFE instruction is chosen with one of the following values:
//! \ref SYSCTL_STOP_WFI, \ref SYSCTL_STOP_WFE.
//!
//! The function is used to disable the WakeUp Pin functionality.
//!
//! \return None 
//
//*****************************************************************************
void 
SysCtlStopModeConfig(unsigned long ulConfig)
{
    xHWREG(PWR_CR) &= ~(PWR_CR_PDDS | PWR_CR_LPDS);
    xHWREG(PWR_CR) |= (ulConfig & PWR_CR_LPDS);
    xHWREG(NVIC_SYS_CTRL) |= NVIC_SYS_CTRL_SLEEPDEEP;
    if(ulConfig & SYSCTL_STOP_WFI)
    {
        xCPUwfi();
    }
    else
    {
        xCPUwfe();
    }
}

//*****************************************************************************
//
//! \brief Enters STANDBY mode.
//!
//! \param None.
//!
//! The function is used to enters STANDBY mode.
//!
//! \return None 
//
//*****************************************************************************
void 
SysCtlEnterStandbyMode(void)
{
    xHWREG(PWR_CR) |= PWR_CR_CWUF;
    xHWREG(PWR_CR) |= PWR_CR_PDDS;
    xHWREG(NVIC_SYS_CTRL) |= NVIC_SYS_CTRL_SLEEPDEEP;
    xCPUwfi();
}

//*****************************************************************************
//
//! \brief Get all the PWR flag is set or not.
//!
//! \param None.
//!
//! The function is used to check whether the specified PWR flag is set or not.
//!
//! \return Flag status 
//! Flag status can be "OR" value of the following values:
//! \ref SYSCTL_WAKEUP_FLAG, \ref SYSCTL_STANDBY_FLAG, \ref SYSCTL_PVD_FLAG.
//
//*****************************************************************************
unsigned long 
SysCtlFlagStatusGet(void)
{
    return (xHWREG(PWR_CSR) & (PWR_CSR_WUF | PWR_CSR_SBF | PWR_CSR_PVDO));
}

//*****************************************************************************
//
//! \brief Clears the PWR's pending flags.
//!
//! \param None.
//! This parameter can be "OR" value of the following values:
//! \ref SYSCTL_WAKEUP_FLAG, \ref SYSCTL_STANDBY_FLAG, \ref SYSCTL_PVD_FLAG.
//!
//! The function is used to check whether the specified PWR flag is set or not.
//!
//! \return Flag status 
//! Flag status can be "OR" value of the following values:
//! \ref SYSCTL_WAKEUP_FLAG, \ref SYSCTL_STANDBY_FLAG, \ref SYSCTL_PVD_FLAG.
//
//*****************************************************************************
void
SysCtlFlagStatusClear(unsigned long ulFlag)
{
    xHWREG(PWR_CR) |= (ulFlag & (PWR_CR_CWUF | PWR_CR_CSBF)) << 2;
}

