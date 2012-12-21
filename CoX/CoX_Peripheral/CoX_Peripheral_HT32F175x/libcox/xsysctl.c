//*****************************************************************************
//
//! \file xsysctl.c
//! \brief Driver for the system controller
//! \version V2.2.1.0
//! \date 5/7/2012
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
#include "xhw_rtc.h"
#include "xhw_wdt.h"

static unsigned s_ulExtClockMHz;

//*****************************************************************************
//
// This macro extracts the array index out of the peripheral number for reset.
//
//*****************************************************************************
#define SYSCTL_PERIPH_INDEX_R(a)(((a) >> 30) & 0x3)

//*****************************************************************************
//
// This macro constructs the peripheral bit mask from the peripheral number for
// reset.
//
//*****************************************************************************
#define SYSCTL_PERIPH_MASK_R(a) ((a) & 0x20000000) ?                          \
                             (((a) & 0xff0000) >> (((a) & 0x1f000000) >> 24)):\
                             (((a) & 0xff0000) >> (((a) & 0x1f000000) >> 24))

//*****************************************************************************
//
// This macro extracts the array index out of the peripheral number for enable.
//
//*****************************************************************************
#define SYSCTL_PERIPH_INDEX_E(a)(((a) >> 14) & 0x3)

//*****************************************************************************
//
// This macro constructs the peripheral bit mask from the peripheral number for 
// enable.
//
//*****************************************************************************
#define SYSCTL_PERIPH_MASK_E(a) ((a) & 0x00002000) ?                          \
                                (((a) & 0xff) << (((a) & 0x1f00) >> 8)) :     \
                                (((a) & 0xff) << (((a) & 0x1f00) >> 8))

//*****************************************************************************
//
// An array that maps the "peripheral set" number (which is stored in the upper
// nibble of the SYSCTL_PERIPH_* defines) to the GCR_IPRSTC? register that
// controls the software reset for that peripheral.
//
//*****************************************************************************
static const unsigned long g_pulIPRSTRegs[] =
{
    RSTCU_AHBPRSTR,
    RSTCU_APBPRSTR0,
    RSTCU_APBPRSTR1
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
    SYSCLK_AHBCCR,
    SYSCLK_APBCCR0,
    SYSCLK_APBCCR1
};

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
//! An array that maps the peripheral base and peripheral ID and interrupt number
//! together to enablea peripheral or peripheral interrupt by a peripheral base.
//
//*****************************************************************************
static const tPeripheralTable g_pPeripherals[] =
{
    {xWDT_BASE,        xSYSCTL_PERIPH_WDOG,  INT_WDT},
    {xUART0_BASE,      xSYSCTL_PERIPH_UART0, INT_UART0},
    {xUART1_BASE,      xSYSCTL_PERIPH_UART1, INT_UART1},
    {xTIMER0_BASE,     xSYSCTL_PERIPH_TIMER0, INT_TIMER0},
    {xTIMER1_BASE,     xSYSCTL_PERIPH_TIMER1, INT_TIMER1},
    {xSPI0_BASE,       xSYSCTL_PERIPH_SPI0, INT_SPI0},
    {xSPI1_BASE,       xSYSCTL_PERIPH_SPI1, INT_SPI1},
    {xI2C0_BASE,       xSYSCTL_PERIPH_I2C0, INT_I2C0},
    {xI2C1_BASE,       xSYSCTL_PERIPH_I2C1, INT_I2C1},
    {xADC0_BASE,       xSYSCTL_PERIPH_ADC0, INT_ADC},
    {xACMP0_BASE,      xSYSCTL_PERIPH_ACMP0, INT_ACMP},
    {xGPIO_PORTA_BASE, xSYSCTL_PERIPH_GPIOA, 0},
    {xGPIO_PORTB_BASE, xSYSCTL_PERIPH_GPIOB, 0},
    {xGPIO_PORTC_BASE, xSYSCTL_PERIPH_GPIOC, 0},
    {xGPIO_PORTD_BASE, xSYSCTL_PERIPH_GPIOD, 0},
    {xGPIO_PORTE_BASE, xSYSCTL_PERIPH_GPIOE, 0},
    {0,                0,                   0},
};

//*****************************************************************************
//
// An array is ClockReady Callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnCKRDYHandlerCallbacks[1]={0};

static xtEventCallback g_pfnLVDHandlerCallbacks[1]={0};
static xtEventCallback g_pfnBODHandlerCallbacks[1]={0};

//*****************************************************************************
//
//! \brief Clock ready (HSE,HSI,LSE,LSI or PLL) IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default Clock ready IRQ service.
//!
//! \return None.
//
//*****************************************************************************
void 
CKRDYIntHandler(void)
{
    unsigned long ulTemp0, ulTemp1, ulTemp2, ulTemp3, ulTemp4, ulTemp5;

    //
    // Clear the CKRDY INT Flag
    //
    ulTemp0 = (xHWREG(SYSCLK_GCIR) & SYSCLK_GCIR_CKSF);
    xHWREG(SYSCLK_GCIR) |= ulTemp0;
    ulTemp1 = (xHWREG(SYSCLK_GCIR) & SYSCLK_GCIR_PLLRDYF);
    xHWREG(SYSCLK_GCIR) |= ulTemp1;
    ulTemp2 = (xHWREG(SYSCLK_GCIR) & SYSCLK_GCIR_HSERDYF);
    xHWREG(SYSCLK_GCIR) |= ulTemp2;
    ulTemp3 = (xHWREG(SYSCLK_GCIR) & SYSCLK_GCIR_HSIRDYF);
    xHWREG(SYSCLK_GCIR) |= ulTemp3;
    ulTemp4 = (xHWREG(SYSCLK_GCIR) & SYSCLK_GCIR_LSERDYF);
    xHWREG(SYSCLK_GCIR) |= ulTemp4;
    ulTemp5 = (xHWREG(SYSCLK_GCIR) & SYSCLK_GCIR_LSIRDYF);
    xHWREG(SYSCLK_GCIR) |= ulTemp5;

    if (g_pfnCKRDYHandlerCallbacks[0] != 0)
    {
        g_pfnCKRDYHandlerCallbacks[0](0, 0, ulTemp0 | ulTemp1 | ulTemp2 |
                                            ulTemp3 | ulTemp4 | ulTemp5, 0);
    }
}

//*****************************************************************************
//
//! \brief Low voltage detection default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default Low voltage detection IRQ service.
//!
//! \return None.
//
//*****************************************************************************
void 
LVDIntHandler(void)
{

    unsigned long ulTemp0;
    
    //
    // Clear LVD INT Flag
    //
    ulTemp0 = (xHWREG(PWRCU_LVDCSR) & PWRCU_LVDCSR_LVDF);
    xHWREG(PWRCU_LVDCSR) = ulTemp0;

    if (g_pfnLVDHandlerCallbacks[0] != 0)        
    {
        g_pfnLVDHandlerCallbacks[0](0, 0, ulTemp0, 0);
    }
}

//*****************************************************************************
//
//! \brief Brownout low voltage detected IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default Brownout low voltage IRQ service.
//!
//! \return None.
//
//*****************************************************************************
void 
BODIntHandler(void)
{
    unsigned long ulTemp0;
    
    //
    // Clear the BOD INT Flag
    //
    ulTemp0 = (xHWREG(PWRCU_LVDCSR) & PWRCU_LVDCSR_BODF);
    xHWREG(PWRCU_LVDCSR) = ulTemp0;

    if (g_pfnBODHandlerCallbacks[0] != 0)        
    {
        g_pfnBODHandlerCallbacks[0](0, 0, ulTemp0, 0);
    }
}

//*****************************************************************************
//
//! \brief Provides a small delay.
//!
//! \param ulCount is the number of delay loop iterations to perform.
//!
//! This function provides a means of generating a constant length delay.It is
//! written in assembly to keep the delay consistent across tool chains,avoiding
//! the need to tune the delay based on the tool chain in use.
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
    __asm("    sub     r0, #1\n"
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
//! \brief Checks a peripheral identifier.
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
    return((ulPeripheral == SYSCTL_PERIPH_SRAM) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIOA)||
           (ulPeripheral == SYSCTL_PERIPH_GPIOB)||
           (ulPeripheral == SYSCTL_PERIPH_GPIOC)||
           (ulPeripheral == SYSCTL_PERIPH_GPIOD)||
           (ulPeripheral == SYSCTL_PERIPH_GPIOE)||
           (ulPeripheral == SYSCTL_PERIPH_BFTM0)||
           (ulPeripheral == SYSCTL_PERIPH_BFTM1)||
           (ulPeripheral == SYSCTL_PERIPH_AFIO) ||
           (ulPeripheral == SYSCTL_PERIPH_MCTM) ||
           (ulPeripheral == SYSCTL_PERIPH_EXTI) ||
           (ulPeripheral == SYSCTL_PERIPH_UART0)||
           (ulPeripheral == SYSCTL_PERIPH_UART1)||
           (ulPeripheral == SYSCTL_PERIPH_TMR0)||
           (ulPeripheral == SYSCTL_PERIPH_TMR1)||
           (ulPeripheral == SYSCTL_PERIPH_I2C0)||
           (ulPeripheral == SYSCTL_PERIPH_I2C1)||
           (ulPeripheral == SYSCTL_PERIPH_SPI0)||
           (ulPeripheral == SYSCTL_PERIPH_SPI1)||
           (ulPeripheral == SYSCTL_PERIPH_CSIF)||
           (ulPeripheral == SYSCTL_PERIPH_WDT) ||
           (ulPeripheral == SYSCTL_PERIPH_DMA) ||
           (ulPeripheral == SYSCTL_PERIPH_USB) ||
           (ulPeripheral == SYSCTL_PERIPH_RTC) ||
           (ulPeripheral == SYSCTL_PERIPH_ADC) ||
           (ulPeripheral == SYSCTL_PERIPH_FMC) ||
           (ulPeripheral == SYSCTL_PERIPH_OPA0)||
           (ulPeripheral == SYSCTL_PERIPH_OPA1));
}
#endif
//*****************************************************************************
//
//! \brief Set a peripheral clock source and peripheral divide.
//!
//! \param ulPeripheralSrc is the peripheral clock source to set.
//! \param ulDivide is the peripheral clock divide to be set.
//!
//! Peripherals clock source are seted with this function.  At power-up, all 
//! Peripherals clock source are Peripherals clock source; they must be set in 
//! order to operate or respond to register reads/writes.
//!
//! The \e ulPeripheralSrc parameter must be only one of the following values:
//! \ref xSysCtl_Peripheral_Src_Clk.
//!
//! \return None.
//
//*****************************************************************************
void
xSysCtlPeripheralClockSourceSet(unsigned long ulPeripheralSrc,
                                unsigned long ulDivide)
{
    unsigned long ulTemp = 0;
    //
    // Check the arguments.
    //
    xASSERT((ulPeripheralSrc==xSYSCTL_WDT0_EXTSL)||
            (ulPeripheralSrc==xSYSCTL_WDT0_INTSL)||
            (ulPeripheralSrc==xSYSCTL_ADC0_HCLK) ||
            (ulPeripheralSrc==xSYSCTL_UART0_HCLK)||
            (ulPeripheralSrc==xSYSCTL_RTC_EXTSL) ||
            (ulPeripheralSrc==xSYSCTL_RTC_INTSL)       
           );
    xASSERT((ulDivide <= 32768) && (ulDivide >= 1));

    while(!SysCtlBackupReadyStateGet());

    SysCtlBackupDomainReset();
    //
    // Set this peripheral clock source
    //   
    if(ulPeripheralSrc == xSYSCTL_WDT0_EXTSL)
    {
        for(ulTemp=0; ulTemp<8; ulTemp++)
        {
            if(ulDivide == (1 << ulTemp))
                break;
        }
        xHWREG(RTC_CR) |= RTC_CR_LSEEN; 
        xHWREG(SYSCLK_GCFGR) &= ~SYSCLK_GCFGR_WDTSRC_M;
        xHWREG(SYSCLK_GCFGR) |= SYSCTL_PERIPH_WDG_S_EXTSL;
        xHWREG(WDT_PR) = WDT_PR_PROTECT_DIS;
        xHWREG(WDT_MR1) &= ~WDT_MR1_WPSC_M;
        xHWREG(WDT_MR1) |= (ulTemp << WDT_MR1_WPSC_S);
        xHWREG(WDT_PR) = WDT_PR_PROTECT_EN;
    }
    else if(ulPeripheralSrc == xSYSCTL_WDT0_INTSL)
    {
        for(ulTemp=0; ulTemp<8; ulTemp++)
        {
            if(ulDivide == (1 << ulTemp))
                break;
        }
	    xHWREG(RTC_CR) |= RTC_CR_LSIEN; 
        xHWREG(SYSCLK_GCFGR) &= ~SYSCLK_GCFGR_WDTSRC_M;
        xHWREG(SYSCLK_GCFGR) |= 0x00000000;
        xHWREG(WDT_PR) = WDT_PR_PROTECT_DIS;
        xHWREG(WDT_MR1) &= ~WDT_MR1_WPSC_M;
        xHWREG(WDT_MR1) |= (ulTemp << WDT_MR1_WPSC_S);
        xHWREG(WDT_PR) = WDT_PR_PROTECT_EN;
    }
    else if(ulPeripheralSrc == xSYSCTL_RTC_EXTSL)
    {
        for(ulTemp=0; ulTemp<16; ulTemp++)
        {
            if(ulDivide == (1 << ulTemp))
                break;
        }
        xHWREG(RTC_CR) |= RTC_CR_LSEEN; 
        xHWREG(RTC_CR) |= RTC_CR_RTCSRC_LSE;
        xHWREG(RTC_CR) &= ~RTC_CR_RPRE_M;
        xHWREG(RTC_CR) |= (ulDivide << RTC_CR_RPRE_S);
    }
    else if(ulPeripheralSrc == xSYSCTL_RTC_INTSL)
    {
        for(ulTemp=0; ulTemp<16; ulTemp++)
        {
            if(ulDivide == (1 << ulTemp))
                break;
        }
        xHWREG(RTC_CR) |= RTC_CR_LSIEN; 
        xHWREG(RTC_CR) |= RTC_CR_RTCSRC_LSI;
        xHWREG(RTC_CR) &= ~RTC_CR_RPRE_M;
        xHWREG(RTC_CR) |= (ulDivide << RTC_CR_RPRE_S);
    }
    else if(ulPeripheralSrc == xSYSCTL_ADC0_HCLK)
    {
        for(ulTemp=0; ulTemp<7; ulTemp++)
        {
            if(ulDivide == (1 << ulTemp))
                break;
        }
        if(ulDivide == 6)
        {
            ulTemp = 7;
        }
        xHWREG(SYSCLK_APBCFGR) &= ~SYSCLK_APBCFGR_ADCDIV_M;
        xHWREG(SYSCLK_APBCFGR) |= (ulTemp << SYSCLK_APBCFGR_ADCDIV_S);
    }
    else if(ulPeripheralSrc == xSYSCTL_UART0_HCLK)
    {
		if(ulDivide == 1)
		{
            xHWREG(SYSCLK_GCFGR) &= ~SYSCLK_GCFGR_URPRE_M;
		}
        else
		{
            xHWREG(SYSCLK_GCFGR) &= ~SYSCLK_GCFGR_URPRE_M;
            xHWREG(SYSCLK_GCFGR) |= SYSCLK_GCFGR_URPRE_2;
		}
    }
    
}
//*****************************************************************************
//
//! \brief Set the clock of the device(HCLK).
//!
//! \param ulSysClk is the clock rate that you will set.
//! \param ulConfig is the required configuration of the device clock.
//!
//! This function configures the clock of the device.The input crystal frequency,
//! oscillator to be used, use of the PLL, and the system clock divider are all
//! configured with this function.
//!
//! The \e ulConfig parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The external crystal frequency is chosen with one of the following values:
//! \ref xSYSCTL_XTAL_4MHZ, \ref xSYSCTL_XTAL_5MHZ, \ref xSYSCTL_XTAL_6MHZ, ...
//! \ref xSYSCTL_XTAL_16MHZ.
//!
//! The oscillator source is chosen with one of the following values:
//! \ref xSYSCTL_OSC_MAIN, \ref xSYSCTL_OSC_INT.
//!
//! The external oscillator must be enabled in order to use an external clock
//! source.
//! <br />
//! Details please refer to \ref XSysCtl_Clock_Set_Config_CoX.
//!
//! \return None.
//
//*****************************************************************************
void
xSysCtlClockSet(unsigned long ulSysClk, unsigned long ulConfig)
{
    unsigned long ulOscFreq = 0;
    unsigned long ulNF2, ulNO2, i;

    unsigned long ulTemp;
    xASSERT((ulSysClk > 0 && ulSysClk <= 72000000));
    
    //
    // Calc oscillator freq
    //
    s_ulExtClockMHz = ((ulConfig & SYSCTL_XTAL_MASK) >> 8);
    //
    // Enable Bus Matrix,APB0 bridge,APB1 bridge Clock
    //
    xHWREG(SYSCLK_AHBCCR) |= (SYSCLK_AHBCCR_BM_EN | SYSCLK_AHBCCR_APB0_EN |
                                                    SYSCLK_AHBCCR_APB1_EN); 
    switch(ulConfig & SYSCTL_OSCSRC_M)
    {
        case xSYSCTL_OSC_INT:
        {

            xHWREG(SYSCLK_GCCR) |= SYSCLK_GCCR_HSIEN;
            //
            // Wait for Internal 8 MHz Oscillator Clock Source is stable.
            //
            while(!(xHWREG(SYSCLK_GCSR) & SYSCLK_GCSR_HSIRDY));
            ulOscFreq = 8000000;
            //
            // System clock source is HSI
            //
            xHWREG(SYSCLK_GCCR) |= SYSCLK_GCCR_SYSSRC_HSI;
            //
            // Wait until system clock takes effect or time-out occurred
            //
            while(1)
            {
                if((xHWREG(SYSCLK_GCCR) & SYSCLK_GCCR_SW_M)
				                    == SYSCLK_GCCR_SYSSRC_HSI)
                {
                    break;
                }  
            }
            break;
		}

        case xSYSCTL_OSC_MAIN:
        {
            xHWREG(SYSCLK_GCCR) |= SYSCLK_GCCR_HSEEN;
            //
            // Wait for external 4~16 MHz Oscillator Clock Source is stable.
            //
            while(!(xHWREG(SYSCLK_GCSR) & SYSCLK_GCSR_HSERDY));

            ulOscFreq = s_ulExtClockMHz * 1000000;
            //
            // System clock source is HSE
            //

            ulTemp = xHWREG(SYSCLK_GCCR) & 0xFFFFFFFC;
            xHWREG(SYSCLK_GCCR) &= (SYSCLK_GCCR_SYSSRC_HSE | ulTemp);
/*
            xHWREG(SYSCLK_GCCR) &= ~SYSCLK_GCCR_SW_M;
            xHWREG(SYSCLK_GCCR) |= SYSCLK_GCCR_SYSSRC_HSE;
*/
            //
            // Wait until system clock takes effect or time-out occurred
            //
            while(1)
            {
                if ((xHWREG(SYSCLK_GCCR) & SYSCLK_GCCR_SW_M)
				                    == SYSCLK_GCCR_SYSSRC_HSE)
                {
                    break;
                }  
            } 
            break;
        }
        default:
        {
            xASSERT(0);
            break;
        }
    }

    if(ulOscFreq >= ulSysClk)
    {
        unsigned long ulSysDiv[4] = {SYSCLK_AHBCFGR_AHBPRE_CKSYS_1,
                                     SYSCLK_AHBCFGR_AHBPRE_CKSYS_2,
                                     SYSCLK_AHBCFGR_AHBPRE_CKSYS_4,
                                     SYSCLK_AHBCFGR_AHBPRE_CKSYS_8,
                                    };

        if(ulSysClk > 48000000)
        {
            xHWREG(FLASH_CFCR) |= 0x03;
        }
        else if(ulSysClk > 24000000)
        {
            xHWREG(FLASH_CFCR) |= 0x02;
        }
        else
        {
            xHWREG(FLASH_CFCR) |= 0x01;
        }

        for(i=0; i<4; i++)
        {
            if((ulOscFreq / ulSysDiv[i]) <= ulSysClk)
            {
                break;
            }
        }
        xASSERT(ulSysDiv[i] < 9);
        xHWREG(SYSCLK_AHBCFGR) |= ulSysDiv[i];
    }

    if(ulOscFreq < ulSysClk)
    {
        ulNO2 = 0;
        if((ulConfig & SYSCTL_OSCSRC_M)==xSYSCTL_OSC_INT)
        {
            ulNF2 = ulSysClk / 8000000;
            //
            // PLL clock source is HSI
            //
            xHWREG(SYSCLK_GCFGR) |= SYSCLK_GCFGR_PLLSRC_HSI;
        }
        else
        {
            //
            // PLL clock source is HSE
            //
            xHWREG(SYSCLK_GCFGR) &= 0xFFFFFEFF;
            ulNF2 = ulSysClk / (s_ulExtClockMHz*1000000);
            //
            // Enable HSE Clock Monitor.
            //
            xHWREG(SYSCLK_GCCR) |= SYSCLK_GCCR_CKMEN;
        }
        xHWREG(SYSCLK_PLLCFGR) &= ~SYSCLK_PLLCFGR_POTD_M;
        xHWREG(SYSCLK_PLLCFGR) &= ~SYSCLK_PLLCFGR_PFBD_M;
        xHWREG(SYSCLK_PLLCFGR) |= (ulNO2 << SYSCLK_PLLCFGR_POTD_S) |
                                  (ulNF2 << SYSCLK_PLLCFGR_PFBD_S);
        xHWREG(SYSCLK_GCCR) |= SYSCLK_GCCR_PLLEN;

        //
        // Wait for PLL is stable
        //
        while(!(xHWREG(SYSCLK_GCSR) & SYSCLK_GCSR_PLLRDY));
        xHWREG(SYSCLK_AHBCFGR) &= ~0xFFFFFFFF;

        if(ulSysClk > 48000000)
        {
            xHWREG(FLASH_CFCR) |= 0x03;
        }
        else if(ulSysClk > 24000000)
        {
            xHWREG(FLASH_CFCR) |= 0x02;
		}
        else
        {
            xHWREG(FLASH_CFCR) |= 0x01;
        }

        //
        // System clock source is PLL
        //
        ulTemp = xHWREG(SYSCLK_GCCR) & 0xFFFFFFF1;
        xHWREG(SYSCLK_GCCR) &= ulTemp; 
        //
        // Wait until system clock takes effect or time-out occurred
        //
        while(1)
        {
            if((xHWREG(SYSCLK_GCCR) & SYSCLK_GCCR_SW_M)
				                    == SYSCLK_GCCR_SYSSRC_PLL)
            {
                break;
            }  
        }  
	}
}

//*****************************************************************************
//
//! \brief The function is used to Get System clock(Hclk) and the UNIT is in Hz
//!
//! \param None.
//!
//! The function is used to Get System clock and the UNIT is in Hz
//!
//! \return System clock frequency in Hz 
//
//*****************************************************************************
unsigned long 
xSysCtlClockGet(void)
{
    unsigned long  ulFreqout = 0, ulNF2, ulNO2, ulSysDiv, ulPLLSrc, ulClkSrc;

    ulPLLSrc = xHWREG(SYSCLK_GCFGR) & SYSCLK_GCFGR_PLLSRC_M;
    ulClkSrc = (xHWREG(SYSCLK_GCCR) & SYSCLK_GCCR_SW_M);
    
    //
    // HSE.
    //
    if(ulClkSrc == SYSCTL_OSC_MAIN)
    {
        ulSysDiv = xHWREG(SYSCLK_AHBCFGR) & SYSCLK_AHBCFGR_AHBPRE_M;
        ulFreqout = (s_ulExtClockMHz*1000000)/(1<<ulSysDiv);
    }
    //
    // HSI.
    //
    else if (ulClkSrc == SYSCTL_OSC_INT)
    {
        ulSysDiv = xHWREG(SYSCLK_AHBCFGR) & SYSCLK_AHBCFGR_AHBPRE_M;
        ulFreqout = (8000000)/(1<<ulSysDiv);
    }
    //
    // HSI+PLL.
    //
    else if((ulClkSrc | ulPLLSrc)== xSYSCTL_OSC_INT)
    {
        ulNO2 = 1;
        ulNF2 = (xHWREG(SYSCLK_PLLCFGR) & SYSCLK_PLLCFGR_PFBD_M) >>           \
                                          SYSCLK_PLLCFGR_PFBD_S;
        ulFreqout = (8000000*ulNF2)/ulNO2;
    }
    //
    // HSE+PLL.
    //
    else                              
    {
        ulNO2 = 1;
        ulNF2 = (xHWREG(SYSCLK_PLLCFGR) & SYSCLK_PLLCFGR_PFBD_M) >>           \
                                          SYSCLK_PLLCFGR_PFBD_S;
        ulFreqout =  (s_ulExtClockMHz*ulNF2*1000000)/ulNO2;
    }

    return ulFreqout;
}

//*****************************************************************************
//
//! \brief Enable a peripheral.
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
//! \brief Disable a peripheral.
//!
//! \param ulPeripheralBase a Peripheral base indicate which peripheral to be 
//! disbled.Details please refer to \ref xLowLayer_Peripheral_Memmap.
//!
//! Peripherals are disabled with this function.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
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
//! The \e ulPeripheral parameter must be only one of the following values:
//! Details please refer to \ref xLowLayer_Peripheral_Memmap.
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
//! \ref xGPIOSPinToPort() function, and then use this function to enable 
//! the GPIO interrupt.
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
xSysCtlPeripheralIntNumGet(unsigned long ulPeripheralBase)
{
    unsigned long i;
    
    //
    // Check the arguments.
    //
    xASSERT((ulPeripheralBase == xTIMER0_BASE)||
            (ulPeripheralBase == xTIMER1_BASE)||
            (ulPeripheralBase == xUART0_BASE)||
            (ulPeripheralBase == xUART1_BASE)||
            (ulPeripheralBase == xACMP0_BASE)||
            (ulPeripheralBase == xSPI0_BASE)||
            (ulPeripheralBase == xSPI1_BASE)||
            (ulPeripheralBase == xI2C0_BASE)||
            (ulPeripheralBase == xI2C1_BASE)||
            (ulPeripheralBase == xADC0_BASE)||
            (ulPeripheralBase == xWDT_BASE)
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
//! \brief Puts the processor into sleep mode.
//!
//! This function places the processor into sleep mode; it will not return until
//! the processor returns to run mode.
//!
//! \return None.
//
//*****************************************************************************

void
xSysCtlSleep(void)
{
    //
    // Wait for an interrupt to wake up.
    //
    xHWREG(xSYSCTL_BASE) &= ~xSYSCTL_SLEEPDEEP;
    xCPUwfi();
}

//*****************************************************************************
//
//! \brief Set clock source for a peripheral.
//!
//! \param ulPeripheralSrc is the peripheral clock source to set.
//!
//! Peripherals clock source are seted with this function.  At power-up, all 
//! Peripherals clock source are Peripherals clock source; they must be set in 
//! order to operate or respond to register reads/writes.
//!
//! The \e ulPeripheralSrc parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_ADC_S_HCLK,   \b SYSCTL_PERIPH_ADC_S_HCLK_2,
//! \b SYSCTL_PERIPH_ADC_S_HCLK_4, \b SYSCTL_PERIPH_ADC_S_HCLK_6,
//! \b SYSCTL_PERIPH_ADC_S_HCLK_8, \b SYSCTL_PERIPH_ADC_S_HCLK_16,
//! \b SYSCTL_PERIPH_ADC_S_HCLK_32,\b SYSCTL_PERIPH_ADC_S_HCLK_64,
//! \b SYSCTL_PERIPH_WDG_S_EXTSL,  \b SYSCTL_PERIPH_WDG_S_INTER,
//! \b SYSCTL_PERIPH_UART_S_HCLK,  \b SYSCTL_PERIPH_UART_S_HCLK_2.
//!
//! \return None.
//
//*****************************************************************************

void
SysCtlPeripheralClockSourceSet(unsigned long ulPeripheralSrc)
{
    unsigned long ulADCClkSrc[7] = {SYSCTL_PERIPH_ADC_S_HCLK,
                                    SYSCTL_PERIPH_ADC_S_HCLK_2,
                                    SYSCTL_PERIPH_ADC_S_HCLK_4,
                                    SYSCTL_PERIPH_ADC_S_HCLK_8,
                                    SYSCTL_PERIPH_ADC_S_HCLK_16,
                                    SYSCTL_PERIPH_ADC_S_HCLK_32,
                                    SYSCTL_PERIPH_ADC_S_HCLK_64
                                   };
    unsigned long ulTemp;
    //
    // Check the arguments.
    //
    xASSERT((ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_HCLK) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_WDG_S_EXTSL) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_WDG_S_INTER) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_HCLK_8)||
            (ulPeripheralSrc == SYSCTL_PERIPH_UART_S_HCLK) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_HCLK_2) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_HCLK_4) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_HCLK_64) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_UART_S_HCLK_2) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_HCLK_16) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_HCLK_32) ||
            (ulPeripheralSrc == SYSCTL_PERIPH_ADC_S_HCLK_6));

    //
    // Set this peripheral clock source
    //
    if(ulPeripheralSrc == SYSCTL_PERIPH_WDG_S_EXTSL)
    {
        xHWREG(SYSCLK_GCFGR) &= ~SYSCLK_GCFGR_WDTSRC_M;
        xHWREG(SYSCLK_GCFGR) |= SYSCTL_PERIPH_WDG_S_EXTSL;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_UART_S_HCLK)
    {
        xHWREG(SYSCLK_GCFGR) &= ~SYSCLK_GCFGR_URPRE_M;
        xHWREG(SYSCLK_GCFGR) |= 0x00000000;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_WDG_S_INTER)
    {
        xHWREG(SYSCLK_GCFGR) &= ~SYSCLK_GCFGR_WDTSRC_M;
        xHWREG(SYSCLK_GCFGR) |= 0x00000000;
    }
    else if(ulPeripheralSrc == SYSCTL_PERIPH_UART_S_HCLK_2)
    {
        xHWREG(SYSCLK_GCFGR) &= ~SYSCLK_GCFGR_URPRE_M;
        xHWREG(SYSCLK_GCFGR) |= SYSCTL_PERIPH_UART_S_HCLK_2;
    }
    else
    {
        if((ulPeripheralSrc & SYSCLK_APBCFGR_ADCDIV_M & SYSCTL_PERIPH_ADC_S_HCLK_6)
                                                     == SYSCTL_PERIPH_ADC_S_HCLK_6)
        {
            xHWREG(SYSCLK_APBCFGR) &= ~SYSCLK_APBCFGR_ADCDIV_M;
            xHWREG(SYSCLK_APBCFGR) |= SYSCTL_PERIPH_ADC_S_HCLK_6;
        }
        else
        {
            ulTemp = (ulPeripheralSrc & SYSCLK_APBCFGR_ADCDIV_M)>>SYSCLK_APBCFGR_ADCDIV_S;
            xHWREG(SYSCLK_APBCFGR) &= ~SYSCLK_APBCFGR_ADCDIV_M;
            xHWREG(SYSCLK_APBCFGR) |= ulADCClkSrc[ulTemp];
        }
    }
}

//*****************************************************************************
//
//! \brief Performs a software reset of a peripheral.
//!
//! \param ulPeripheral is the peripheral to be reset.
//!
//! This function performs a software reset of the specified peripheral.  An
//! individual peripheral reset signal is asserted for a brief period and then
//! deasserted, returning the internal state of the peripheral to its reset
//! condition.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_GPIO, \b SYSCTL_PERIPH_TMR0,\b SYSCTL_PERIPH_TMR1,
//! \b SYSCTL_PERIPH_I2C0, \b SYSCTL_PERIPH_SPI0,\b SYSCTL_PERIPH_UART0,
//! \b SYSCTL_PERIPH_ADC, \b SYSCTL_PERIPH_OPA0, \b SYSCTL_PERIPH_OPA1,
//! \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_SPI1,\b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_WDT, \b SYSCTL_PERIPH_BFTM0, \b SYSCTL_PERIPH_BFTM1,
//! \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_SPI1,\b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_SCI, \b SYSCTL_PERIPH_USB, \b SYSCTL_PERIPH_MCTM,
//! \b SYSCTL_PERIPH_AFIO, \b SYSCTL_PERIPH_EXTI.
//!  
//!  
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralReset(unsigned long ulPeripheral)
{
    volatile unsigned long ulDelay;

    //
    // Check the arguments.
    //
    xASSERT(SysCtlPeripheralValid(ulPeripheral));

    //
    // Put the peripheral into the reset state.
    //
    xHWREG(g_pulIPRSTRegs[SYSCTL_PERIPH_INDEX_R(ulPeripheral)]) |=
        SYSCTL_PERIPH_MASK_R(ulPeripheral);

    //
    // Delay for a little bit.
    //
    for(ulDelay = 0; ulDelay < 16; ulDelay++)
    {
    }

    //
    // Take the peripheral out of the reset state.
    //
    xHWREG(g_pulIPRSTRegs[SYSCTL_PERIPH_INDEX_R(ulPeripheral)]) &=
        ~(SYSCTL_PERIPH_MASK_R(ulPeripheral));
}

//*****************************************************************************
//
//! \brief Enable a peripheral.
//!
//! \param ulPeripheral is the peripheral base address to be enabled.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_SRAM, \b SYSCTL_PERIPH_FMC,\b SYSCTL_PERIPH_TMR0,
//! \b SYSCTL_PERIPH_TMR1, \b SYSCTL_PERIPH_I2C0,\b SYSCTL_PERIPH_WDT,
//! \b SYSCTL_PERIPH_SPI0, \b SYSCTL_PERIPH_ADC,\b SYSCTL_PERIPH_OPA0,
//! \b SYSCTL_PERIPH_OPA1, \b SYSCTL_PERIPH_ACMP,\b SYSCTL_PERIPH_UART0
//! \b SYSCTL_PERIPH_GPIOA,\b SYSCTL_PERIPH_GPIOB.
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
    xASSERT(SysCtlPeripheralValid(ulPeripheral));

    //
    // Enable this peripheral.
    //
    xHWREG(g_pulAXBCLKRegs[SYSCTL_PERIPH_INDEX_E(ulPeripheral)]) |=
                                            SYSCTL_PERIPH_MASK_E(ulPeripheral);
}

//*****************************************************************************
//
//! \brief Disable a peripheral.
//!
//! \param ulPeripheral is the peripheral base address to be Disabled.
//!
//! Peripherals are disabled with this function.  Once disabled, they will not
//! operate or respond to register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_TMR0,\b SYSCTL_PERIPH_TMR1,\b SYSCTL_PERIPH_WDT,
//! \b SYSCTL_PERIPH_I2C0,\b SYSCTL_PERIPH_SPI0, \b SYSCTL_PERIPH_ADC,
//! \b SYSCTL_PERIPH_OPA0,\b SYSCTL_PERIPH_OPA1,\b SYSCTL_PERIPH_UART0
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
    xHWREG(g_pulAXBCLKRegs[SYSCTL_PERIPH_INDEX_E(ulPeripheral)]) &=
                                          ~(SYSCTL_PERIPH_MASK_E(ulPeripheral));
}

//*****************************************************************************
//
//! \brief Puts the processor into sleep mode.
//!
//! \param ulEnterMode is the mode of entering sleep status.
//! 
//! This function places the processor into sleep mode; it will not return until
//! the processor returns to run mode.
//!
//! \return None.
//
//*****************************************************************************

void
SysCtlSleep(unsigned long ulEnterMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulEnterMode == SYSCTL_SLEEP_WFI_MOD) ||
            (ulEnterMode == SYSCTL_SLEEP_WFE_MOD)
           );
    //
    // Wait for an interrupt or event to wake up.
    //
    xHWREG(xSYSCTL_BASE) &= ~xSYSCTL_SLEEPDEEP;
    if(ulEnterMode == SYSCTL_SLEEP_WFI_MOD)
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
//! \brief Puts the processor into deep-sleep mode 1.
//!
//! \param ulEnterMode is the mode of entering sleep status.
//!
//! This function places the processor into deep-sleep mode 1; it will not return
//! until the processor returns to run mode.
//!
//! \return None.
//
//*****************************************************************************

void
SysCtlDeepSleep1(unsigned long ulEnterMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulEnterMode == SYSCTL_SLEEP_WFI_MOD) ||
            (ulEnterMode == SYSCTL_SLEEP_WFE_MOD)
           );
    xHWREG(PWRCU_BAKCR) &= ~PWRCU_BAKCR_LDOOFF;
    xHWREG(PWRCU_BAKCR) &= ~PWRCU_BAKCR_DMOSON;
    xHWREG(xSYSCTL_BASE) |= xSYSCTL_SLEEPDEEP;
    //
    // Wait for interrupt or event.
    //
    if(ulEnterMode == SYSCTL_SLEEP_WFI_MOD)
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
//! \brief Puts the processor into deep-sleep mode 2.
//!
//! \param ulEnterMode is the mode of entering sleep status.
//!
//! This function places the processor into deep-sleep mode 2; it will not return
//! until the processor returns to run mode.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlDeepSleep2(unsigned long ulEnterMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulEnterMode == SYSCTL_SLEEP_WFI_MOD) ||
            (ulEnterMode == SYSCTL_SLEEP_WFE_MOD)
           );
    xHWREG(PWRCU_BAKCR) &= ~PWRCU_BAKCR_LDOOFF;
    xHWREG(PWRCU_BAKCR) |= PWRCU_BAKCR_DMOSON;
    xHWREG(xSYSCTL_BASE) |= xSYSCTL_SLEEPDEEP;
    //
    // Wait for interrupt or event.
    //
    if(ulEnterMode == SYSCTL_SLEEP_WFI_MOD)
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
//! \brief Puts the processor into power down mode.
//!
//! \param ulEnterMode is the mode of entering sleep status.
//!
//! This function places the processor into power down; it will not return until
//! the processor returns to run mode.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPowerDown(unsigned long ulEnterMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulEnterMode == SYSCTL_SLEEP_WFI_MOD) ||
            (ulEnterMode == SYSCTL_SLEEP_WFE_MOD)
           );
    xHWREG(PWRCU_BAKCR) |= PWRCU_BAKCR_LDOOFF;
    xHWREG(PWRCU_BAKCR) &= ~PWRCU_BAKCR_DMOSON;
    xHWREG(xSYSCTL_BASE) |= xSYSCTL_SLEEPDEEP;

    //
    // Wait for interrupt or event.
    //
    if(ulEnterMode == SYSCTL_SLEEP_WFI_MOD)
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
//! \brief The function is used to Get reset source from last operation
//!
//! \param None.
//!
//! The function is used to Get reset source from last operation
//!
//! \return Reset source enumerated as a bit field of
//! \b RSTCU_GRSR_PORSTF, \b RSTCU_GRSR_WDTRSTF, \b RSTCU_GRSR_EXTRSTF,
//! \b RSTCU_GRSR_SYSRSTF.
//
//*****************************************************************************
unsigned long 
SysCtlResetSrcGet(void)
{
    //
    // Get reset source from last operation.
    //
    return xHWREG(RSTCU_GRSR);
}


//*****************************************************************************
//
//! \brief The function is used to Set Clock Output source. 
//!
//! \param ulPresSel is the clock source of Clock Output.
//!
//! The function is used to Set Clock Output source.
//!
//! \return None.
//
//*****************************************************************************
void SysCtlClkOututSrcSet(unsigned long ulClkOutSrc)
{
    //
    // Check the arguments.
    //
    xASSERT((ulClkOutSrc == SYSCLK_GCFGR_CKOUTSRC_PLL_16) ||
            (ulClkOutSrc == SYSCLK_GCFGR_CKOUTSRC_AHB_16) ||
            (ulClkOutSrc == SYSCLK_GCFGR_CKOUTSRC_SYS_16) ||
            (ulClkOutSrc == SYSCLK_GCFGR_CKOUTSRC_HSE_16) ||
            (ulClkOutSrc == SYSCLK_GCFGR_CKOUTSRC_HSI_16) ||
            (ulClkOutSrc == SYSCLK_GCFGR_CKOUTSRC_LSE) ||
            (ulClkOutSrc == SYSCLK_GCFGR_CKOUTSRC_LSI)
           );
    //
    // Select Output Clock Source.
    //
    xHWREG(SYSCLK_GCFGR) &= ~SYSCLK_GCFGR_CKOUTSRC_M;
    xHWREG(SYSCLK_GCFGR) |= ulClkOutSrc;
}
//*****************************************************************************
//
//! \brief The function is used to Get Lower Power Mode Status
//!
//! \param None.
//!
//! The function is used to Lower Power Mode Status.
//!
//! \return Lower Power Mode Status enumerated as a bit field of
//! \b SYSCLK_GCFGR_LPMOD_DEEPSLEEP1, \b SYSCLK_GCFGR_LPMOD_RUN,
//! \b SYSCLK_GCFGR_LPMOD_DEEPSLEEP2, \b SYSCLK_GCFGR_LPMOD_SLEEP, 
//! \b SYSCLK_GCFGR_LPMOD_POWERDOWN.
//
//*****************************************************************************
unsigned long 
SysCtlLowerPowerModeGet(void)
{
    //
    // Get Lower Power Mode Status.
    //
    return (xHWREG(SYSCLK_GCFGR)&SYSCLK_GCFGR_LPMOD_M);
}

//*****************************************************************************
//
//! \brief The function is used to Clear reset source by write 1 
//!
//! \param ulSrc The corresponding bit of reset source.
//!
//! The function is used to Get reset source from last operation
//!
//! The \e ulSrc parameter must be only one of the following values:
//! \b RSTCU_GRSR_PORSTF, \b RSTCU_GRSR_WDTRSTF, \b RSTCU_GRSR_EXTRSTF,
//! \b RSTCU_GRSR_SYSRSTF.
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlResetSrcClear(unsigned long ulSrc)
{
    //
    // Check the arguments.
    //
    xASSERT((ulSrc == RSTCU_GRSR_PORSTF) ||
            (ulSrc == RSTCU_GRSR_WDTRSTF) ||
            (ulSrc == RSTCU_GRSR_EXTRSTF) ||
            (ulSrc == RSTCU_GRSR_SYSRSTF)
           );
    //
    // Clear reset source from last operation.
    //
    xHWREG(RSTCU_GRSR) |= ulSrc;
}

//*****************************************************************************
//
//! \brief The function is used to enable BOD function
//!
//! \param bEnable is a boolean that is \b true if Enable BOD function and 
//! \b false if not.
//!
//! The function is used to Enable BOD function
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlBODEnable(xtBoolean bEnable)
{
    //
    // Enable BOD function or not.
    //
    if(bEnable)
    {
        xHWREG(PWRCU_LVDCSR) |= PWRCU_LVDCSR_BODEN;
    }
    else
    {
        xHWREG(PWRCU_LVDCSR) &= ~PWRCU_LVDCSR_BODEN;
    }
}

//*****************************************************************************
//
//! \brief The function is used to enable LVD function
//!
//! \param bEnable is a boolean that is \b true if Enable LVD function and 
//! \b false if not.
//!
//! The function is used to Enable LVD function
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlLVDEnable(xtBoolean bEnable)
{
    //
    // Enable LVD function or not.
    //
    if(bEnable)
    {
        xHWREG(PWRCU_LVDCSR) |= PWRCU_LVDCSR_LVDEN;
    }
    else
    {
        xHWREG(PWRCU_LVDCSR) &= ~PWRCU_LVDCSR_LVDEN;
    }
}

//*****************************************************************************
//
//! \brief The function is used to enable DMOS function
//!
//! \param bEnable is a boolean that is \b true if Enable DMOS function and 
//! \b false if not.
//!
//! The function is used to Enable DMOS function
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlDMOSEnable(xtBoolean bEnable)
{
    //
    // Enable DMOS function or not.
    //
    
    if(bEnable)
    {
        xHWREG(PWRCU_BAKCR) |= PWRCU_BAKCR_DMOSON;
    }
    else
    {
        xHWREG(PWRCU_BAKCR) &= ~PWRCU_BAKCR_DMOSON;
    }
}
//*****************************************************************************
//
//! \brief The function is used to enable LVD interrupt or Wakeup LDO function
//!
//! \param bEnable is a boolean that is \b true if Enable LVD interrupt or Wakeup
//! LDO and \b false if not.
//!
//! The function is used to Enable LVD interrupt
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlLVDIntEnable(xtBoolean bEnable)
{
    //
    // Enable LVD interrupt or not.
    //
    
    if(bEnable)
    {
        xHWREG(PWRCU_LVDCSR) |= PWRCU_LVDCSR_LVDIWEN;
    }
    else
    {
        xHWREG(PWRCU_LVDCSR) &= ~PWRCU_LVDCSR_LVDIWEN;
    }
}

//*****************************************************************************
//
//! \brief The function is used to Get LVD state
//!
//! \param None.
//!
//! The function is used to Get LVD state
//!
//! \return LVD state enumerated as a bit field of
//! \b 1 Low Voltage event occured(VDD33 is equal to or lower than the specific
//! voltage level). 
//! \b 0 Low Voltage event has not occurred(VDD33 is higher than the specific 
//! voltage level). 
//
//*****************************************************************************
xtBoolean
SysCtlLVDStateGet(void)
{
    //
    // Get LVD state.
    //
    
    return (xHWREG(PWRCU_LVDCSR) & PWRCU_LVDCSR_LVDF)>>19;
}

//*****************************************************************************
//
//! \brief The function is used to Get BOD state
//!
//! \param None.
//!
//! The function is used to Get BOD state
//!
//! \return BOD state enumerated as a bit field of
//! \b 1 the detected voltage is lower than BOD threshold voltage,
//! \b 0 the detected voltage is higher than BOD threshold voltage.
//
//*****************************************************************************
xtBoolean
SysCtlBODStateGet(void)
{
    //
    // Get BOD state.
    //
    
    return (xHWREG(PWRCU_LVDCSR) & PWRCU_LVDCSR_BODF)>>3;
}

//*****************************************************************************
//
//! \brief The function is used to Get DMOS state
//!
//! \param None.
//!
//! The function is used to Get DMOS state
//!
//! \return DMOS state enumerated as a bit field of
//! \b 1 if the DMOSON bit in this register has seen set to 1.
//! \b 0 if the DMOSON bit has seen set to 0 or if a BOD reset occurred.
//
//*****************************************************************************
xtBoolean
SysCtlDMOSStateGet(void)
{
    //
    // Get DMOS state.
    //
    
    return (xHWREG(PWRCU_BAKCR) & PWRCU_BAKCR_DMOSSTS)>>15;
}

//*****************************************************************************
//
//! \brief The function is used to set BOD reset or Interrupt selection
//!
//! \param ulBodFunction is the selection of the BOD function,it only can be
//! PWRCU_LVDCSR_BODRST or PWRCU_LVDCSR_BODINT.
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlBODFunctionSelect(unsigned long ulBodFunction)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBodFunction == PWRCU_LVDCSR_BODRST) ||
            (ulBodFunction == PWRCU_LVDCSR_BODINT)
           );
    //
    // Enable BOD reset function or interrupt function.
    //
    xHWREG(PWRCU_LVDCSR) |= ulBodFunction;
}

//*****************************************************************************
//
//! \brief The function is used to set Low Voltage Detect Level threshold voltage
//!
//! \param ulVoltage the volt will be set
//!
//! The function is used to Select LVD threshold voltage
//!
//! The \e ulVoltage parameter must be only one of the following values:
//! \b PWRCU_LVDCSR_LVDS_2V7, \b PWRCU_LVDCSR_LVDS_2V8,
//! \b PWRCU_LVDCSR_LVDS_2V9, \b PWRCU_LVDCSR_LVDS_3V0.
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlLVDVoltSelect(unsigned long ulVoltage)
{
    //
    // Check the arguments.
    //
    xASSERT((ulVoltage == PWRCU_LVDCSR_LVDS_2V7) ||
            (ulVoltage == PWRCU_LVDCSR_LVDS_2V8) ||
            (ulVoltage == PWRCU_LVDCSR_LVDS_2V9) ||
            (ulVoltage == PWRCU_LVDCSR_LVDS_3V0)
           );
    //
    // Select LVD threshold voltage.
    //
    xHWREG(PWRCU_LVDCSR) &= ~PWRCU_LVDCSR_LVDS_M;
    xHWREG(PWRCU_LVDCSR) |= ulVoltage;
}

//*****************************************************************************
//
//! \brief The function is used to enable extern  function.
//!
//! \param bEnable is a boolean that is \b true if Enable LVD function and 
//! \b false if not.
//!
//! The function is used to enable extern WakeUp pin function
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlWakeUpPinEnable(xtBoolean bEnable)
{
    //
    // Enable extern WakeUp function pin.
    //
    if(bEnable)
    {
        xHWREG(PWRCU_BAKCR) |= PWRCU_BAKCR_WUPEN;
    }
    else
    {
        xHWREG(PWRCU_BAKCR) &= ~PWRCU_BAKCR_WUPEN;
    }
}

//*****************************************************************************
//
//! \brief The function is used to enable extern WakeUp pin interrupt.
//!
//! \param bEnable is a boolean that is \b true if Enable extern WakeUp pin interrupt
//! and \b false if not.
//!
//! The function is used to Enable extern WakeUp pin interrupt
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlWakeUpIntEnable(xtBoolean bEnable)
{
    //
    // Enable extern WakeUp pin interrupt or not.
    //
    
    if(bEnable)
    {
        xHWREG(PWRCU_BAKCR) |= PWRCU_BAKCR_WUPIEN;
    }
    else
    {
        xHWREG(PWRCU_BAKCR) &= ~PWRCU_BAKCR_WUPIEN;
    }
}

//*****************************************************************************
//
//! \brief The function is used to (Software)Reset Backup Domain.
//!
//! \param None.
//!
//! The function is used to (Software)Reset Backup Domain. 
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlBackupDomainReset(void)
{
    xHWREG(PWRCU_BAKCR) |= PWRCU_BAKCR_BAKRST;
	while(xHWREG(PWRCU_BAKCR));
}

//*****************************************************************************
//
//! \brief The function is used to check the RTC & PWRCU can be accessed or not.
//!
//! \param None
//!
//! The function is used to to check the RTC & PWRCU can be accessed or not.
//!
//! \return The state of RTC & PWRCU as a bit field of
//! \b 1 the RTC & PWRCU has been ready,you can access them.
//! \b 0 the RTC & PWRCU has not been ready,you can't access them.
//
//*****************************************************************************
xtBoolean 
SysCtlBackupReadyStateGet(void)
{
    unsigned long ulTimeOutCnt = 36000000;
    unsigned long ulTest;

    //
    // Clear Backup Domain Isolation.
    //
    xHWREG(SYSCLK_LPCR) |= SYSCLK_LPCR_BKISO_EN;

    while(--ulTimeOutCnt)
    {   
        ulTest = xHWREG(PWRCU_BAKTEST);
        if(ulTest == SYSCTL_BACKUP_TEST_VALUE)
        {
		        unsigned long ulWrite = ~(xHWREG(PWRCU_BAKREG9));
			      unsigned long ulBackUp = xHWREG(PWRCU_BAKREG9);
			      while(1)
			      {
			          xHWREG(PWRCU_BAKREG9) = ulWrite;
				        if(xHWREG(PWRCU_BAKREG9) == ulWrite)
				        {
				            break;
				        }
			      }
			      xHWREG(PWRCU_BAKREG9) = ulBackUp;
            return xtrue;
        }
    }
    return xfalse;
}

//*****************************************************************************
//
//! \brief The function is used to Write the data to the Backup register
//!
//! \param ulIndex is the index of the backup register and it must be between 0
//!  and 9.
//! \param ulData is the data which will be written to the  backup register and 
//!  it must be smaller than 0xFFFFFFFF.
//!
//! The function is used to write data to backup register.
//!
//! \note You must call SysCtlBackupReadyStateGet() before using this function
//! 
//! \return None.
//
//*****************************************************************************
void
SysCtlBackupRegWrite(unsigned long ulIndex, unsigned long ulData)
{
    xASSERT((ulIndex >= 0 && ulIndex <= 9));
    xASSERT(ulData <= 0xFFFFFFFF);

    xHWREG(PWRCU_BAKREG0 + ulIndex*4) |= ulData;
}

//*****************************************************************************
//
//! \brief The function is used to Read the values of Backup register
//!
//! \param ulIndex is the index of the backup register and it must be between 0
//!  and 9.
//!
//! The function is used to Read Backup register
//!
//! \note You must call SysCtlBackupReadyStateGet() before using this function
//!
//! \return the value of Backup register X.
//
//*****************************************************************************
unsigned long
SysCtlBackupRegRead(unsigned long ulIndex)
{
    unsigned long ulTemp;
    xASSERT((ulIndex >= 0) && (ulIndex <= 9));
    
    //
    // Get the value of backup register.
    //
    ulTemp = xHWREG(PWRCU_BAKREG0 + ulIndex*4);

    return ulTemp;
}

//*****************************************************************************
//
//! \brief The function is used to set ready counter bit length of HSI.
//!
//! \param ulBitLength is the bit length will be set
//!
//! The function is used to set ready counter bit length of HSI.
//!
//! The \e ulBitLength parameter must be only one of the following values:
//! \b PWRCU_HSIRCR_HSIRCBL_7, \b PWRCU_HSIRCR_HSIRCBL_8,
//! \b PWRCU_HSIRCR_HSIRCBL_9, \b PWRCU_HSIRCR_HSIRCBL_10.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlHSIReadyCounterBitLengthSet(unsigned long ulBitLength)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBitLength == PWRCU_HSIRCR_HSIRCBL_7) ||
            (ulBitLength == PWRCU_HSIRCR_HSIRCBL_6) ||
            (ulBitLength == PWRCU_HSIRCR_HSIRCBL_5) ||
            (ulBitLength == PWRCU_HSIRCR_HSIRCBL_4)
           );
    //
    // Select ready counter bit length of HSI.
    //
    xHWREG(PWRCU_HSIRCR) &= ~PWRCU_HSIRCR_HSIRCBL_M;
    xHWREG(PWRCU_HSIRCR) |= ulBitLength;
}

//*****************************************************************************
//
//! \brief Get individual Clock Ready interrupt sources.
//!
//! \param ulIntFlags is the bit mask of the interrupt sources which have happened.
//!
//! If the indicated Clock Ready interrupt sources, return xtrue, otherwise return 
//! xfalse.
//!
//! The \e ulIntFlags parameter is the one of any of the following:
//!
//! - \b SYSCLK_GCIR_CKSF          - HSE Clock Stuck Interrupt Flag
//! - \b SYSCLK_GCIR_PLLRDYF       - PLL Ready Interrupt Flag
//! - \b SYSCLK_GCIR_HSERDYF       - HSE Ready Interrupt Flag
//! - \b SYSCLK_GCIR_HSIRDYF       - HSI Ready Interrupt Flag
//! - \b SYSCLK_GCIR_LSERDYF       - LSE Ready Interrupt Flag
//! - \b SYSCLK_GCIR_LSIRDYF       - LSI Ready Interrupt Flag
//!
//! \return If the indicated UART interrupt sources, return xtrue, otherwise return
//! xfalse.
//
//*****************************************************************************
xtBoolean
SysCtlClockReadyIntGet(unsigned long ulIntFlags)
{
    //
    // Get enable the specified interrupts.
    //

    return ((xHWREG(SYSCLK_GCIR) & (ulIntFlags & 0xF)) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Enable individual Clock Ready interrupt.
//!
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! The \e ulIntFlags parameter is the one of any of the following:
//!
//! - \b SYSCLK_GCIR_CKSIE          - Clock Stuck Interrupt Enable
//! - \b SYSCLK_GCIR_PLLRDYIE       - PLL Ready Interrupt Enable
//! - \b SYSCLK_GCIR_HSERDYIE       - HSE Ready Interrupt Enable
//! - \b SYSCLK_GCIR_HSIRDYIE       - HSI Ready Interrupt Enable
//! - \b SYSCLK_GCIR_LSERDYIE       - LSE Ready Interrupt Enable
//! - \b SYSCLK_GCIR_LSIRDYIE       - LSI Ready Interrupt Enable
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlClockReadyIntEnable(unsigned long ulIntFlags)
{
    //
    // Enable the specified interrupts.
    //

    xHWREG(SYSCLK_GCIR) |= ulIntFlags;
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the CKRDY.
//!
//! \param xtPortCallback is callback for the Clock Ready.
//!
//! This function is to init interrupts callback for clock ready.
//!
//! \return None.
//
//*****************************************************************************
void 
CKRDYIntCallbackInit(xtEventCallback pfnCallback)
{
    g_pfnCKRDYHandlerCallbacks[0] = pfnCallback;
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the LVD.
//!
//! \param xtPortCallback is callback for the LVD.
//!
//! This function is to init interrupts callback for the LVD.
//!
//! \return None.
//
//*****************************************************************************
void 
LVDIntCallbackInit(xtEventCallback pfnCallback)
{
    g_pfnLVDHandlerCallbacks[0] = pfnCallback;
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the BOD.
//!
//! \param xtPortCallback is callback for the BOD.
//!
//! This function is to init interrupts callback for the BOD.
//!
//! \return None.
//
//*****************************************************************************
void 
BODIntCallbackInit(xtEventCallback pfnCallback)
{
    g_pfnBODHandlerCallbacks[0] = pfnCallback;
}

//*****************************************************************************
//
//! \brief Set the clock of the USB.
//!
//! \param ulUsbClk is the clock rate that you will set.
//! \param ulConfig is the required configuration of the usb clock.
//!
//! This function configures the clock of the device.The input crystal frequency,
//! oscillator to be used, use of the PLL, and the system clock divider are all
//! configured with this function.
//!
//! The \e ulConfig parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The external crystal frequency is chosen with one of the following values:
//! \ref xSYSCTL_XTAL_4MHZ, \ref xSYSCTL_XTAL_5MHZ, \ref xSYSCTL_XTAL_6MHZ, ...
//! \ref xSYSCTL_XTAL_16MHZ.
//!
//! The oscillator source is chosen with one of the following values:
//! \ref SYSCTL_PLL_MAIN, \ref SYSCTL_PLL_INT.
//!
//! The external oscillator must be enabled in order to use an external clock
//! source.
//!
//! \return None.
//
//*****************************************************************************
void
USBClockSet(unsigned long ulUsbClk, unsigned long ulConfig)
{
    unsigned long ulOscFreq = 0;
    unsigned long ulNF2, ulNO2, i;

	  unsigned long ulTemp;
    xASSERT((ulUsbClk > 0 && ulUsbClk <= 48000000));

    //
    // Calc oscillator freq
    //
    s_ulExtClockMHz = ((ulConfig & SYSCTL_XTAL_MASK) >> 8);

    switch(ulConfig & SYSCTL_PLL_MAIN)
    {
        case SYSCTL_PLL_INT:
        {

            xHWREG(SYSCLK_GCCR) |= SYSCLK_GCCR_HSIEN;
            //
            // Wait for Internal 8 MHz High Speed Oscillator Clock Source is stable.
            //
            while(!(xHWREG(SYSCLK_GCSR) & SYSCLK_GCSR_HSIRDY));
            ulOscFreq = 8000000;
            //
            // PLL clock source is HSI
            //
            xHWREG(SYSCLK_GCFGR) |= SYSCLK_GCFGR_PLLSRC_HSI;
			      break;
		    }
        case SYSCTL_PLL_MAIN:
        {

            xHWREG(SYSCLK_GCCR) |= SYSCLK_GCCR_HSEEN;
            //
            // Wait for Internal 8 MHz High Speed Oscillator Clock Source is stable.
            //
            while(!(xHWREG(SYSCLK_GCSR) & SYSCLK_GCSR_HSERDY));
            ulOscFreq = (s_ulExtClockMHz*1000000);
            //
            // PLL clock source is HSE
            //
            xHWREG(SYSCLK_GCFGR) &= 0xFFFFFEFF;
			      break;
		    }
        default:
        {
            xASSERT(0);
            break;
        }
    }
    if(ulOscFreq <= ulUsbClk)
    {
        ulNO2 = 0;
        ulNF2 = ulUsbClk / ulOscFreq;
        xHWREG(SYSCLK_GCFGR) &= ~(SYSCTL_USB_PLL_2 | SYSCTL_USB_PLL_3);

    }
    else
    {
        ulNO2 = 0;
        ulNF2 = 1;
        for(i=0; i<3; i++)
        {
                    
            ulTemp = ulOscFreq / (i + 1);
            if(ulTemp <= ulUsbClk)
            {
                    xHWREG(SYSCLK_GCFGR) |= i << SYSCLK_GCFGR_USBPRE_S;
                    break;
            }
        }
    }
    xHWREG(SYSCLK_PLLCFGR) &= ~SYSCLK_PLLCFGR_POTD_M;
    xHWREG(SYSCLK_PLLCFGR) &= ~SYSCLK_PLLCFGR_PFBD_M;
    xHWREG(SYSCLK_PLLCFGR) |= ((ulNO2 << SYSCLK_PLLCFGR_POTD_S) |
                               (ulNF2 << SYSCLK_PLLCFGR_PFBD_S));
    xHWREG(SYSCLK_GCCR) |= SYSCLK_GCCR_PLLEN;
}

//*****************************************************************************
//
//! \brief Set the clock of the CSIF.
//!
//! \param ulCsifClk is the clock rate that you will set.
//! \param ulConfig is the required configuration of the usb clock.
//!
//! This function configures the clock of the device.The input crystal frequency,
//! oscillator to be used, use of the PLL, and the system clock divider are all
//! configured with this function.
//!
//! The \e ulConfig parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The external crystal frequency is chosen with one of the following values:
//! \ref xSYSCTL_XTAL_4MHZ, \ref xSYSCTL_XTAL_5MHZ, \ref xSYSCTL_XTAL_6MHZ, ...
//! \ref xSYSCTL_XTAL_16MHZ.
//!
//! The oscillator source is chosen with one of the following values:
//! \ref SYSCTL_PLL_MAIN, \ref SYSCTL_PLL_INT.
//!
//! The external oscillator must be enabled in order to use an external clock
//! source.
//!
//! \return None.
//
//*****************************************************************************
void
CSIFClockSet(unsigned long ulCsifClk, unsigned long ulConfig)
{
    unsigned long ulOscFreq = 0;
    unsigned long ulNF2, ulNO2, i;

	  unsigned long ulTemp;
    xASSERT((ulCsifClk > 0 && ulCsifClk <= 24000000));

    //
    // Calc oscillator freq
    //
    s_ulExtClockMHz = ((ulConfig & SYSCTL_XTAL_MASK) >> 8);

    switch(ulConfig & SYSCTL_PLL_MAIN)
    {
        case SYSCTL_PLL_INT:
        {

            xHWREG(SYSCLK_GCCR) |= SYSCLK_GCCR_HSIEN;
            //
            // Wait for Internal 8 MHz High Speed Oscillator Clock Source is stable.
            //
            while(!(xHWREG(SYSCLK_GCSR) & SYSCLK_GCSR_HSIRDY));
            ulOscFreq = 8000000;
            //
            // PLL clock source is HSI
            //
            xHWREG(SYSCLK_GCFGR) |= SYSCLK_GCFGR_PLLSRC_HSI;
			      break;
		    }
        case SYSCTL_PLL_MAIN:
        {

            xHWREG(SYSCLK_GCCR) |= SYSCLK_GCCR_HSEEN;
            //
            // Wait for Internal 8 MHz High Speed Oscillator Clock Source is stable.
            //
            while(!(xHWREG(SYSCLK_GCSR) & SYSCLK_GCSR_HSERDY));
            ulOscFreq = (s_ulExtClockMHz*1000000);
            //
            // PLL clock source is HSE
            //
            xHWREG(SYSCLK_GCFGR) &= 0xFFFFFEFF;
			      break;
		    }
        default:
        {
            xASSERT(0);
            break;
        }
    }
    if(ulOscFreq <= ulCsifClk)
    {
        ulNO2 = 0;
        ulNF2 = ulCsifClk / ulOscFreq;
        xHWREG(SYSCLK_GCFGR) &= ~(SYSCTL_USB_PLL_2 | SYSCTL_USB_PLL_3);

    }
    else
    {
        ulNO2 = 0;
        ulNF2 = 1;
        for(i=0; i<32; i++)
        {
                
            ulTemp = ulOscFreq / ((i+1)*2);
            if(ulTemp <= ulCsifClk)
            {
                    xHWREG(SYSCLK_GCFGR) |= i << SYSCLK_GCFGR_USBPRE_S;
                    break;
            }
        }
    }
    xHWREG(SYSCLK_PLLCFGR) &= ~SYSCLK_PLLCFGR_POTD_M;
    xHWREG(SYSCLK_PLLCFGR) &= ~SYSCLK_PLLCFGR_PFBD_M;
    xHWREG(SYSCLK_PLLCFGR) |= ((ulNO2 << SYSCLK_PLLCFGR_POTD_S) |
                               (ulNF2 << SYSCLK_PLLCFGR_PFBD_S));
    xHWREG(SYSCLK_GCCR) |= SYSCLK_GCCR_PLLEN;
}