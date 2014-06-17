//*****************************************************************************
//
//! \file xsysctl.c
//! \brief Driver for the system controller
//! \version V2.2.1.0
//! \date 6/15/2014
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
#include "CoX.h"
#include "xhw_sysctl.h"

static unsigned long s_ulExtClockMHz = 12;

//*****************************************************************************
//
// This macro extracts the array index out of the peripheral clock source.
//
//*****************************************************************************
#define SYSCTL_PERIPH_INDEX_CLK(a)                                            \
                                (((a) >> 28) & 0x3)

//*****************************************************************************
//
// This macro constructs the peripheral bit mask from the peripheral clock source.
//
//*****************************************************************************
#define SYSCTL_PERIPH_MASK_CLK(a)                                             \
                                (((((a) >> 25) & 0x7 )) << ((((a) >> 20) & 0x1f)))

//*****************************************************************************
//
// This macro extracts the array index out of the peripheral clock divider.
//
//*****************************************************************************
#define SYSCTL_PERIPH_INDEX_DIV(a)                                            \
                                (((a) >> 18) & 0x3)

//*****************************************************************************
//
// This macro constructs the peripheral bit mask from the clock divider.
//
//*****************************************************************************
#define SYSCTL_PERIPH_MASK_DIV(a)                                             \
		                        ((((a) >> 10) & 0xff) << (((a) >> 5) & 0x1f))


//*****************************************************************************
//
// This macro constructs the peripheral enum of the peripheral clock source.
//
//*****************************************************************************
#define SYSCTL_PERIPH_ENUM_CLK(a)                                             \
                                (((a) & 0xff) << (((a) & 0x1f0000) >> 16))
                                
//*****************************************************************************
//
// This macro extracts the array index out of the peripheral number for reset.
//
//*****************************************************************************
#define SYSCTL_PERIPH_INDEX_R(a)(((a) >> 24) & 0x3)

//*****************************************************************************
//
// This macro constructs the peripheral bit mask from the peripheral number for 
// reset.
//
//*****************************************************************************
#define SYSCTL_PERIPH_MASK_R(a) (1 <<((a) & 0x00ffffff))

//*****************************************************************************
//
// This macro extracts the array index out of the peripheral number for enable.
//
//*****************************************************************************
#define SYSCTL_PERIPH_INDEX_E(a)(((a) >> 30) & 0x3)

//*****************************************************************************
//
// This macro constructs the peripheral bit mask from the peripheral number for 
// enable.
//
//*****************************************************************************
#define SYSCTL_PERIPH_MASK_E(a) ((a >> 0) & 0x1F)

//*****************************************************************************
//
// An array that maps the "peripheral set" number (which is stored in the upper
// nibble of the SYSCTL_PERIPH_* defines) to the GCR_IPRSTC? register that
// controls the software reset for that peripheral.
//
//*****************************************************************************
static const unsigned long g_pulIPRSTRegs[] =
{
    GCR_IPRSTC1,
    GCR_IPRSTC2,
    GCR_IPRSTC3
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
    SYSCLK_AHBCLK,
    SYSCLK_APBCLK0,
    SYSCLK_APBCLK1
};

//*****************************************************************************
//
// An array that maps the "peripheral clock source set" number (which is stored
// in the upper nibble of the SYSCTL_PERIPH_* defines) to the SYSCLK_CLKSEL? 
// register that set the Clock source for that peripheral.
//
//*****************************************************************************
static const unsigned long g_pulCLKSELRegs[] =
{
    SYSCLK_CLKSEL0,
    SYSCLK_CLKSEL1,
    SYSCLK_CLKSEL2,
    SYSCLK_CLKSEL3
};

static const unsigned long g_pulCLKDivRegs[] =
{
    SYSCLK_CLKDIV0,
    SYSCLK_CLKDIV1,
    SYSCLK_CLKDIV2,
    SYSCLK_CLKDIV3
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
}tPeripheralTable;

//*****************************************************************************
//
//! An array that maps the peripheral base and peripheral ID and interrupt number
//! together to enablea peripheral or peripheral interrupt by a peripheral base.
//
//*****************************************************************************
static const tPeripheralTable g_pPeripherals[] =
{
    {xADC0_BASE,       xSYSCTL_PERIPH_ADC0,    xINT_ADC0},
    {xADC1_BASE,       xSYSCTL_PERIPH_ADC1,    xINT_ADC1},
    {xACMP_BASE,       xSYSCTL_PERIPH_ACMP,    xINT_ACMP},
    {xDMA0_BASE,       xSYSCTL_PERIPH_DMA0,    xINT_DMA0},
    {xGPIO_PORTA_BASE, xSYSCTL_PERIPH_GPIOA,   xINT_GPIOA},
    {xGPIO_PORTB_BASE, xSYSCTL_PERIPH_GPIOB,   xINT_GPIOB},
    {xGPIO_PORTC_BASE, xSYSCTL_PERIPH_GPIOC,   xINT_GPIOC},
    {xGPIO_PORTD_BASE, xSYSCTL_PERIPH_GPIOD,   xINT_GPIOD},
    {xGPIO_PORTE_BASE, xSYSCTL_PERIPH_GPIOE,   xINT_GPIOE},
    {xGPIO_PORTF_BASE, xSYSCTL_PERIPH_GPIOF,   xINT_GPIOF},
    {xGPIO_PORTG_BASE, xSYSCTL_PERIPH_GPIOG,   xINT_GPIOG},
    {xGPIO_PORTH_BASE, xSYSCTL_PERIPH_GPIOH,   xINT_GPIOH},
    {xGPIO_PORTI_BASE, xSYSCTL_PERIPH_GPIOI,   xINT_GPIOI},
    {xI2C0_BASE,       xSYSCTL_PERIPH_I2C0,    xINT_I2C0},
    {xI2C1_BASE,       xSYSCTL_PERIPH_I2C1,    xINT_I2C1},
    {xI2C2_BASE,       xSYSCTL_PERIPH_I2C2,    xINT_I2C2},
    {xI2C3_BASE,       xSYSCTL_PERIPH_I2C3,    xINT_I2C3},
    {xI2C4_BASE,       xSYSCTL_PERIPH_I2C4,    xINT_I2C4},
    {RTC_BASE,         xSYSCTL_PERIPH_RTC,     xINT_RTC},
    {xSPI0_BASE,       xSYSCTL_PERIPH_SPI0,    xINT_SPI0},
    {xSPI1_BASE,       xSYSCTL_PERIPH_SPI1,    xINT_SPI1},
    {xSPI2_BASE,       xSYSCTL_PERIPH_SPI2,    xINT_SPI2},
    {xSPI3_BASE,       xSYSCTL_PERIPH_SPI3,    xINT_SPI3},
    {xTIMER0_BASE,     xSYSCTL_PERIPH_TIMER0,  xINT_TIMER0},
    {xTIMER1_BASE,     xSYSCTL_PERIPH_TIMER1,  xINT_TIMER1},
    {xTIMER2_BASE,     xSYSCTL_PERIPH_TIMER2,  xINT_TIMER2},
    {xTIMER3_BASE,     xSYSCTL_PERIPH_TIMER3,  xINT_TIMER3},
    {xUART0_BASE,      xSYSCTL_PERIPH_UART0,   xINT_UART0},
    {xUART1_BASE,      xSYSCTL_PERIPH_UART1,   xINT_UART1},
    {xUART2_BASE,      xSYSCTL_PERIPH_UART2,   xINT_UART2},
    {xUART3_BASE,      xSYSCTL_PERIPH_UART3,   xINT_UART3},
    {xUART4_BASE,      xSYSCTL_PERIPH_UART4,   xINT_UART4},
    {xUART5_BASE,      xSYSCTL_PERIPH_UART5,   xINT_UART5},
    {xPWMA_BASE,       xSYSCTL_PERIPH_PWMA,    xINT_PWMA},
    {xPWMB_BASE,       xSYSCTL_PERIPH_PWMB,    xINT_PWMB},
    {xWDT_BASE,        xSYSCTL_PERIPH_WDOG,    xINT_WDT},
    {0,                0,                      0},
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
xSysCtlDelay(unsigned long ulCount)
{
    __asm("    subs    r0, #1\n"
          "    bne     xSysCtlDelay\n"
          "    bx      lr");
}
#endif
#if defined(ewarm) || defined(__ICCARM__)
void
xSysCtlDelay(unsigned long ulCount)
{
    __asm("    subs    r0, #1\n"
          "    bne.n   xSysCtlDelay\n"
          "    bx      lr");
}
#endif
#if defined(rvmdk) || defined(__CC_ARM)
__asm void
xSysCtlDelay(unsigned long ulCount)
{
    subs    r0, #1;
    bne     xSysCtlDelay;
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
    return((ulPeripheral == SYSCTL_PERIPH_ISP) ||
           (ulPeripheral == SYSCTL_PERIPH_WDT) ||
           (ulPeripheral == SYSCTL_PERIPH_PDMA)||
           (ulPeripheral == SYSCTL_PERIPH_CRC)||
           (ulPeripheral == SYSCTL_PERIPH_CAP)||
           (ulPeripheral == SYSCTL_PERIPH_GPIOA)||
           (ulPeripheral == SYSCTL_PERIPH_GPIOA)||
           (ulPeripheral == SYSCTL_PERIPH_GPIOB)||
           (ulPeripheral == SYSCTL_PERIPH_GPIOC)||
           (ulPeripheral == SYSCTL_PERIPH_GPIOD)||
           (ulPeripheral == SYSCTL_PERIPH_GPIOE)||
           (ulPeripheral == SYSCTL_PERIPH_GPIOF)||
           (ulPeripheral == SYSCTL_PERIPH_GPIOG)||
           (ulPeripheral == SYSCTL_PERIPH_GPIOH)||
           (ulPeripheral == SYSCTL_PERIPH_GPIOI)||
           (ulPeripheral == SYSCTL_PERIPH_RTC) ||
           (ulPeripheral == SYSCTL_PERIPH_TMR0)||
           (ulPeripheral == SYSCTL_PERIPH_TMR1)||
           (ulPeripheral == SYSCTL_PERIPH_TMR2)||
           (ulPeripheral == SYSCTL_PERIPH_TMR3)||
           (ulPeripheral == SYSCTL_PERIPH_I2C0)||
           (ulPeripheral == SYSCTL_PERIPH_I2C1)||
           (ulPeripheral == SYSCTL_PERIPH_I2C2)||
           (ulPeripheral == SYSCTL_PERIPH_I2C3)||
           (ulPeripheral == SYSCTL_PERIPH_I2C4)|| 
           (ulPeripheral == SYSCTL_PERIPH_SPI0)||
           (ulPeripheral == SYSCTL_PERIPH_SPI1)||
           (ulPeripheral == SYSCTL_PERIPH_SPI2)||
           (ulPeripheral == SYSCTL_PERIPH_SPI3)||
           (ulPeripheral == SYSCTL_PERIPH_I2S0)||
           (ulPeripheral == SYSCTL_PERIPH_I2S1)||
           (ulPeripheral == SYSCTL_PERIPH_CAN0)||
           (ulPeripheral == SYSCTL_PERIPH_CAN1)||
           (ulPeripheral == SYSCTL_PERIPH_UART0)||
           (ulPeripheral == SYSCTL_PERIPH_UART1)||
           (ulPeripheral == SYSCTL_PERIPH_UART2)||
           (ulPeripheral == SYSCTL_PERIPH_UART3)||
           (ulPeripheral == SYSCTL_PERIPH_UART4)||
           (ulPeripheral == SYSCTL_PERIPH_UART5)||
           (ulPeripheral == SYSCTL_PERIPH_PWM01)||
           (ulPeripheral == SYSCTL_PERIPH_PWM23)||
           (ulPeripheral == SYSCTL_PERIPH_USBD) ||
           (ulPeripheral == SYSCTL_PERIPH_EMAC) ||
           (ulPeripheral == SYSCTL_PERIPH_PS2));
}
#endif

//*****************************************************************************
//
//! \brief Set the clock of the device.
//!
//! \param ulSysClk is the clock rate that you will set.
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
//! \ref xSYSCTL_XTAL_4MHZ, \ref xSYSCTL_XTAL_5MHZ, \ref xSYSCTL_XTAL_6MHZ, ...
//! \ref xSYSCTL_XTAL_24MHZ.
//!
//! The oscillator source is chosen with one of the following values:
//! \ref xSYSCTL_OSC_MAIN, \ref xSYSCTL_OSC_INT, \ref xSYSCTL_OSC_INTSL,
//! \ref xSYSCTL_OSC_EXTSL.
//!
//! The internal and main oscillators and PLL are disabled with the
//! \ref xSYSCTL_INT_OSC_DIS and \ref xSYSCTL_MAIN_OSC_DIS flags, 
//! \ref xSYSCTL_PLL_PWRDN respectively.
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
xSysCtlClockSet(unsigned long ulSysClk, unsigned long ulConfig)
{
    unsigned long ulOscFreq, ulSysDiv;
    unsigned long ulNF, ulNR, ulNO;
    xASSERT((ulSysClk > 0 && ulSysClk <= 84000000));

    //
    // Calc oscillator freq
    //
    s_ulExtClockMHz = ((ulConfig & SYSCTL_XTAL_MASK) >> 8);
    SysCtlKeyAddrUnlock();

    switch(ulConfig & SYSCTL_OSCSRC_M)
    {
        case xSYSCTL_OSC_MAIN:
        {
            xASSERT(!(ulConfig & xSYSCTL_MAIN_OSC_DIS));
            
            xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL12M_EN;
            //
            // Wait for the External 4~24 MHz High Speed Crystal Clock Source is stable
            //
            while(!(xHWREG(SYSCLK_CLKSTATUS) & 0x00000001));
            xHWREG(SYSCLK_CLKSEL0) &= ~SYSCLK_CLKSEL0_HCLK_M;
            xHWREG(SYSCLK_CLKDIV0) &= ~0x0F;
            ulOscFreq = s_ulExtClockMHz * 1000000;
            if((ulConfig & SYSCLK_PWRCON_OSC22M_EN)!=0)
            {
                xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_OSC22M_EN;
            }
            if((ulConfig & SYSCLK_PLLCON_PD)!=0)
            {
                xHWREG(SYSCLK_PLLCON) |= SYSCLK_PLLCON_PD;
            }
            break;
        }

        case xSYSCTL_OSC_INT:
        {
            xASSERT(!(ulConfig & xSYSCTL_INT_OSC_DIS));  
            xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC22M_EN;
            SysCtlHClockSourceSet(SYSCTL_HLCK_S_INT22M);
            //
            // Wait for Internal 22.1184 MHz High Speed Oscillator Clock Source is stable
            //
            while(!(xHWREG(SYSCLK_CLKSTATUS) & 0x00000010));
            ulOscFreq = 22000000;
            if((ulConfig & SYSCLK_PWRCON_XTL12M_EN)!=0)
            {
                xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_XTL12M_EN;
            }
            if((ulConfig & SYSCLK_PLLCON_PD)!=0)
            {
                xHWREG(SYSCLK_PLLCON) |= SYSCLK_PLLCON_PD;
            }
            break;
        }
        case xSYSCTL_OSC_INTSL:
        {
            ulOscFreq = 10000;
            xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC10K_EN;
            SysCtlHClockSourceSet(SYSCTL_HLCK_S_INT10K);
            //
            // Wait for Internal 10 kHz Low Speed Oscillator Clock Source is stable
            //
            while(!(xHWREG(SYSCLK_CLKSTATUS) & 0x00000008));
            if((ulConfig & SYSCLK_PWRCON_OSC22M_EN)!=0)
            {
                xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_OSC22M_EN;
            }
            if((ulConfig & SYSCLK_PWRCON_XTL12M_EN)!=0)
            {
                xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_XTL12M_EN;
            }
            if((ulConfig & SYSCLK_PLLCON_PD)!=0)
            {
                xHWREG(SYSCLK_PLLCON) |= SYSCLK_PLLCON_PD;
            }
            break;
        }
        case xSYSCTL_OSC_EXTSL:
        {
        	ulOscFreq = 32768;
            xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL32K_EN;
            //
            // Wait for Internal 10 kHz Low Speed Oscillator Clock Source is stable
            //
            while(!(xHWREG(SYSCLK_CLKSTATUS) & 0x00000002));
            SysCtlHClockSourceSet(SYSCTL_HLCK_S_EXT32K);
            if((ulConfig & SYSCLK_PWRCON_OSC22M_EN)!=0)
            {
                xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_OSC22M_EN;
            }
            if((ulConfig & SYSCLK_PWRCON_XTL12M_EN)!=0)
            {
                xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_XTL12M_EN;
            }
            if((ulConfig & SYSCLK_PLLCON_PD)!=0)
            {
                xHWREG(SYSCLK_PLLCON) |= SYSCLK_PLLCON_PD;
            }
            break;
        }
        default:
        {
            xASSERT(0);
            break;
        }
                
    }
    if(ulSysClk == ulOscFreq)
    {
        SysCtlIPClockDividerSet(SYSCTL_PERIPH_HCLK_D | (SYSCTL_SYSDIV_1 + 1));
    }
    else if (ulSysClk <= ulOscFreq)
    {
        //
        // Calc the SysDiv
        //    
        xASSERT(ulSysClk <= ulOscFreq);
            
        for(ulSysDiv = 1; ulSysDiv < 16; ulSysDiv++)
        {
            if((ulOscFreq / (ulSysDiv + 1)) <= ulSysClk)
            {
                break;
            }
        }
        xASSERT(ulSysDiv < 16);
        SysCtlIPClockDividerSet(SYSCTL_PERIPH_HCLK_D | (ulSysDiv + 1));
    }
    else
    {
        xASSERT(!(ulConfig & xSYSCTL_PLL_PWRDN));
        xASSERT((ulSysClk >= 25000000 && ulSysClk <= 84000000));
        xASSERT(((ulConfig & SYSCTL_OSCSRC_M) == xSYSCTL_OSC_MAIN) ||
                ((ulConfig & SYSCTL_OSCSRC_M) == xSYSCTL_OSC_INT));
        if(ulSysClk < 50000000){
            ulSysClk <<= 2; ulNO = 0x3;
        } else {
        	ulSysClk <<= 1; ulNO = 0x1;
        }
        ulNF = ulSysClk/1000000;
        ulNR = ulOscFreq/1000000;

        if((ulConfig & SYSCLK_PLLCON_PLL_SRC)==0)
        {
            //
            // Check the arguments.
            //
            xASSERT((ulConfig & SYSCLK_PWRCON_XTL12M_EN)==0); 
            xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_PLL_SRC;
            if(ulNR%4 == 0)
            {
                ulNF >>= 2;
                ulNR >>= 2;
            }
            else if(ulNR%2 == 0)
            {
                ulNF >>= 1;
                ulNR >>= 1;
            }    
            else 
            {
                if(ulSysClk % ulOscFreq == 0)
                {
                    ulNR = ulOscFreq/1000000/2;
                    ulNF = ulSysClk*ulNR/ulOscFreq;
                }
                else
                xASSERT(0);
            }
        }
        else 
        {
            //
            // Check the arguments .
            //
            xASSERT((ulConfig & SYSCLK_PWRCON_OSC22M_EN)==0);   
            xHWREG(SYSCLK_PLLCON) |= SYSCLK_PLLCON_PLL_SRC;
            ulNF >>= 1;
            ulNR >>= 1;
            if((ulConfig & SYSCLK_PWRCON_XTL12M_EN)!=0)
            {
                xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_XTL12M_EN;
            }
        }

        xHWREG(SYSCLK_PLLCON) |= SYSCLK_PLLCON_PD;
        xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_FB_DV_M;
        xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_IN_DV_M;
        xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_OUT_DV_M;
        xHWREG(SYSCLK_PLLCON) |= ((ulNF-2) << SYSCLK_PLLCON_FB_DV_S);
        xHWREG(SYSCLK_PLLCON) |= ((ulNR-2) << SYSCLK_PLLCON_IN_DV_S);
        xHWREG(SYSCLK_PLLCON) |= (ulNO << SYSCLK_PLLCON_OUT_DV_S);
        xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_OE;
        xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_PD;

        xSysCtlDelay(1000);
        //
        // Wait for Internal PLL Clock Source is stable
        //
        while(!(xHWREG(SYSCLK_CLKSTATUS) & 0x00000004));

        SysCtlHClockSourceSet(SYSCTL_HLCK_S_PLL);
        xHWREG(SYSCLK_CLKDIV0) &= ~SYSCLK_CLKDIV_HCLK_M;

        if((ulConfig & SYSCLK_PWRCON_OSC22M_EN)!=0)
        {
            xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_OSC22M_EN;
        }
    }

    xHWREG(SYSCLK_CLKSEL0) |= SYSCLK_CLKSEL0_PCLK_S; // PCLK = HCLK/2

    SysCtlKeyAddrLock();
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
            xSysCtlPeripheralEnable(g_pPeripherals[i].ulPeripheralID);
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
            xSysCtlPeripheralDisable(g_pPeripherals[i].ulPeripheralID);
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
            xSysCtlPeripheralReset(g_pPeripherals[i].ulPeripheralID);
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
//! \ref xGPIOSPinToPort() function, and then use this function to enable the 
//! GPIO interrupt.
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
    xASSERT((ulPeripheralBase == xGPIO_PORTA_BASE)||
            (ulPeripheralBase == xGPIO_PORTB_BASE)||
            (ulPeripheralBase == xGPIO_PORTC_BASE)||
            (ulPeripheralBase == xGPIO_PORTD_BASE)||
            (ulPeripheralBase == xWDT_BASE)||   
            (ulPeripheralBase == xUART0_BASE)||   
            (ulPeripheralBase == xUART1_BASE)||   
            (ulPeripheralBase == xTIMER0_BASE)||    
            (ulPeripheralBase == xTIMER1_BASE)||          
            (ulPeripheralBase == xTIMER2_BASE)||    
            (ulPeripheralBase == xTIMER3_BASE)||        
            (ulPeripheralBase == xSPI0_BASE)||     
            (ulPeripheralBase == xSPI1_BASE)||
            (ulPeripheralBase == xI2C0_BASE)||   
            (ulPeripheralBase == xPWMA_BASE)  
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

void xSysCtlPeripheralClockSourceSet(unsigned long ulPeripheralSrc, unsigned long ulDivide)
{

}

//*****************************************************************************
//
//! \brief  This function set selected module clock source and module clock divider
//!
//! \param  ulPeripheralSrc is module index.
//! \param  ulClkSrc is module clock source.
//! \param  ulClkDiv is module clock divider.
//!
//! \return None
//!
//! details Valid parameter combinations listed in following table:
//
//*****************************************************************************
void xSysCtlPeripheralClockSourceSet2(unsigned long ulPeripheralSrc,
                                 unsigned long ulClkSrc, unsigned long ulDivide)
{
    //unsigned long ulTmp = 0;
    
    //
    // Check the arguments.
    //
    xASSERT((ulPeripheralSrc == SYSCTL_PERIPH_USBD)||
            (ulPeripheralSrc == SYSCTL_PERIPH_EMAC)||
            (ulPeripheralSrc == SYSCTL_PERIPH_CAP)||
            (ulPeripheralSrc == SYSCTL_PERIPH_WDT)||
            (ulPeripheralSrc == SYSCTL_PERIPH_WWDT)||
            (ulPeripheralSrc == SYSCTL_PERIPH_TMR0)||
            (ulPeripheralSrc == SYSCTL_PERIPH_TMR1)||
            (ulPeripheralSrc == SYSCTL_PERIPH_TMR2)||
            (ulPeripheralSrc == SYSCTL_PERIPH_TMR3)||
            (ulPeripheralSrc == SYSCTL_PERIPH_FDIV)||
            (ulPeripheralSrc == SYSCTL_PERIPH_SPI0)||
            (ulPeripheralSrc == SYSCTL_PERIPH_SPI1)||
            (ulPeripheralSrc == SYSCTL_PERIPH_SPI2)||
            (ulPeripheralSrc == SYSCTL_PERIPH_SPI3)||
            (ulPeripheralSrc == SYSCTL_PERIPH_UART0)||
            (ulPeripheralSrc == SYSCTL_PERIPH_UART1)||
            (ulPeripheralSrc == SYSCTL_PERIPH_UART2)||
            (ulPeripheralSrc == SYSCTL_PERIPH_UART3)||
            (ulPeripheralSrc == SYSCTL_PERIPH_UART4)||
            (ulPeripheralSrc == SYSCTL_PERIPH_UART5)||
            (ulPeripheralSrc == SYSCTL_PERIPH_ADC)||
            (ulPeripheralSrc == SYSCTL_PERIPH_SC0)||
            (ulPeripheralSrc == SYSCTL_PERIPH_SC1)||
            (ulPeripheralSrc == SYSCTL_PERIPH_SC2)||
            (ulPeripheralSrc == SYSCTL_PERIPH_SC3)||
            (ulPeripheralSrc == SYSCTL_PERIPH_SC4)||
            (ulPeripheralSrc == SYSCTL_PERIPH_SC5)||
            (ulPeripheralSrc == SYSCTL_PERIPH_PWMA01)||
            (ulPeripheralSrc == SYSCTL_PERIPH_PWMA23)||
            (ulPeripheralSrc == SYSCTL_PERIPH_PWMA45)||
            (ulPeripheralSrc == SYSCTL_PERIPH_PWMB01)||
            (ulPeripheralSrc == SYSCTL_PERIPH_PWMB23)||
            (ulPeripheralSrc == SYSCTL_PERIPH_PWMB45)||
            (ulPeripheralSrc == SYSCTL_PERIPH_SC5)||
           );
    xASSERT((ulDivide <= 256) && (ulDivide >= 1));
    //
    // Set the peripheral clock source
    //
    SysCtlKeyAddrUnlock();
    if(((ulPeripheralSrc >> 25) & 0x7) != 0x0){
#if 0
        switch(ulPeripheralSrc)
        {
            case SYSCTL_PERIPH_SPI0:
            case SYSCTL_PERIPH_SPI1:
            case SYSCTL_PERIPH_SPI2:
            case SYSCTL_PERIPH_SPI3:
                {
        		    if(ulClkSrc == 0) ulClkSrc = 0;
        	    }
        	    break;
            case SYSCTL_PERIPH_UART0:
            case SYSCTL_PERIPH_UART1:
            case SYSCTL_PERIPH_UART2:
            case SYSCTL_PERIPH_UART3:
            case SYSCTL_PERIPH_UART4:
            case SYSCTL_PERIPH_UART5:
                {

                }
                break;
            case SYSCTL_PERIPH_PWMA01:

        }
#endif
    	xHWREG(g_pulCLKSELRegs[SYSCTL_PERIPH_INDEX_CLK(ulPeripheralSrc)]) &=
    			        ~SYSCTL_PERIPH_MASK_CLK(ulPeripheralSrc);
    	xHWREG(g_pulCLKSELRegs[SYSCTL_PERIPH_INDEX_CLK(ulPeripheralSrc)]) |=
    			       (ulClkSrc << (((ulPeripheralSrc) >> 20) & 0x1F));
        //ulTmp = xHWREG(g_pulCLKSELRegs[(ulPeripheralSrc >> 28) & 0x3]);
        //ulTmp = (ulTmp & ~SYSCTL_PERIPH_MASK_CLK(ulPeripheralSrc)) | ulClkSrc;
        //xHWREG(g_pulCLKSELRegs[(ulPeripheralSrc >> 28) & 0x3]) = ulTmp;
    }

    if(((ulPeripheralSrc >> 10) & 0xff) != 0x0){
    	xHWREG(g_pulCLKDivRegs[SYSCTL_PERIPH_INDEX_DIV(ulPeripheralSrc)]) &=
    			             ~SYSCTL_PERIPH_MASK_DIV(ulPeripheralSrc);
    	xHWREG(g_pulCLKDivRegs[SYSCTL_PERIPH_INDEX_DIV(ulPeripheralSrc)]) |=
    			          (ulDivide << (((ulPeripheralSrc) >> 5) & 0x1F));
        //ulTmp = xHWREG(g_pulCLKDivRegs[(ulPeripheralSrc >> 18) & 0x3]);
        //ulTmp = (ulTmp & ~SYSCTL_PERIPH_MASK_DIV(ulPeripheralSrc)) | ulDivide;
        //xHWREG(g_pulCLKDivRegs[(ulPeripheralSrc >> 18) & 0x3]) = ulTmp;
    }
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief Performs a software reset of a peripheral.
//!
//! \param ulPeripheral is the peripheral to reset.
//!
//! This function performs a software reset of the specified peripheral.  An
//! individual peripheral reset signal is asserted for a brief period and then
//! deasserted, returning the internal state of the peripheral to its reset
//! condition.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_GPIO, \b SYSCTL_PERIPH_TMR0,\b SYSCTL_PERIPH_TMR1,
//! \b SYSCTL_PERIPH_TMR2, \b SYSCTL_PERIPH_TMR3,\b SYSCTL_PERIPH_I2C0,
//! \b SYSCTL_PERIPH_SPI0,\b SYSCTL_PERIPH_SPI1,\b SYSCTL_PERIPH_UART0,
//! \b SYSCTL_PERIPH_UART1,\b SYSCTL_PERIPH_PWM01, \b SYSCTL_PERIPH_PWM23,
//! \b SYSCTL_PERIPH_USBD,\b SYSCTL_PERIPH_PS2.
//!  
//! \return None.
//
//*****************************************************************************
void
xSysCtlPeripheralReset(unsigned long ulPeripheral)
{
    volatile unsigned long ulDelay;

    //
    // Check the arguments.
    //
    xASSERT(SysCtlPeripheralValid(ulPeripheral));

    //
    // Put the peripheral into the reset state.
    //
    if(ulPeripheral == xSYSCTL_PERIPH_PWMA){
        xHWREG(GCR_IPRSTC2) |= GCR_IPRSTC2_PWM0;
    } else if(ulPeripheral == xSYSCTL_PERIPH_PWMB){
        xHWREG(GCR_IPRSTC2) |= GCR_IPRSTC2_PWM1;
    } else {
        xHWREG(g_pulIPRSTRegs[SYSCTL_PERIPH_INDEX_R(ulPeripheral)]) |=
            SYSCTL_PERIPH_MASK_R(ulPeripheral);
    }
    //
    // Delay for a little bit.
    //
    for(ulDelay = 0; ulDelay < 16; ulDelay++);

    //
    // Take the peripheral out of the reset state.
    //
    if(ulPeripheral == xSYSCTL_PERIPH_PWMA){
        xHWREG(GCR_IPRSTC2) &= ~GCR_IPRSTC2_PWM0;
    } else if(ulPeripheral == xSYSCTL_PERIPH_PWMB){
        xHWREG(GCR_IPRSTC2) &= ~GCR_IPRSTC2_PWM1;
    } else {
        xHWREG(g_pulIPRSTRegs[SYSCTL_PERIPH_INDEX_R(ulPeripheral)]) &=
            ~(SYSCTL_PERIPH_MASK_R(ulPeripheral));
    }
}

//*****************************************************************************
//
//! \brief Enables a peripheral.
//!
//! \param ulPeripheral is the peripheral base address to be enabled.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_ISP, \b SYSCTL_PERIPH_TMR0,\b SYSCTL_PERIPH_WDT,
//! \b SYSCTL_PERIPH_TMR1,\b SYSCTL_PERIPH_TMR2,\b SYSCTL_PERIPH_TMR3,
//! \b SYSCTL_PERIPH_I2C0,\b SYSCTL_PERIPH_SPI0,\b SYSCTL_PERIPH_SPI1,
//! \b SYSCTL_PERIPH_USBD,\b SYSCTL_PERIPH_PS2,\b SYSCTL_PERIPH_RTC,
//! \b SYSCTL_PERIPH_UART0,\b SYSCTL_PERIPH_UART1, \b SYSCTL_PERIPH_PWM01
//! \b SYSCTL_PERIPH_PWM23
//!
//! \return None.
//
//*****************************************************************************
void
xSysCtlPeripheralEnable(unsigned long ulPeripheral)
{
    //
    // Check the arguments.
    //
    xASSERT(SysCtlPeripheralValid(ulPeripheral));

    //
    // Enable this peripheral.
    //
    SysCtlKeyAddrUnlock();
    if(ulPeripheral == xSYSCTL_PERIPH_PWMA){
        xHWREG(SYSCLK_APBCLK1) |= (SYSCLK_APBCLK1_PWMA01_EN|SYSCLK_APBCLK1_PWMA23_EN|SYSCLK_APBCLK1_PWMA45_EN);
    } else if(ulPeripheral == xSYSCTL_PERIPH_PWMB){
    	xHWREG(SYSCLK_APBCLK1) |= (SYSCLK_APBCLK1_PWMB01_EN|SYSCLK_APBCLK1_PWMB23_EN|SYSCLK_APBCLK1_PWMB45_EN);
    } else {
        xHWREG(g_pulAXBCLKRegs[SYSCTL_PERIPH_INDEX_E(ulPeripheral)]) |=
            1 << SYSCTL_PERIPH_MASK_E(ulPeripheral);
    }
    SysCtlKeyAddrLock();
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
//! \b SYSCTL_PERIPH_ISP, \b SYSCTL_PERIPH_TMR0,\b SYSCTL_PERIPH_WDT,
//! \b SYSCTL_PERIPH_TMR1,\b SYSCTL_PERIPH_TMR2,\b SYSCTL_PERIPH_TMR3,
//! \b SYSCTL_PERIPH_I2C0,\b SYSCTL_PERIPH_SPI0,\b SYSCTL_PERIPH_SPI1,
//! \b SYSCTL_PERIPH_USBD,\b SYSCTL_PERIPH_PS2,\b SYSCTL_PERIPH_RTC,
//! \b SYSCTL_PERIPH_UART0,\b SYSCTL_PERIPH_UART1,\b SYSCTL_PERIPH_PWM01,
//! \b SYSCTL_PERIPH_PWM23.
//!
//! \return None.
//
//*****************************************************************************
void
xSysCtlPeripheralDisable(unsigned long ulPeripheral)
{
    //
    // Check the arguments.
    //
    xASSERT(SysCtlPeripheralValid(ulPeripheral));

    //
    // Disable this peripheral.
    //
    SysCtlKeyAddrUnlock();
    if(ulPeripheral == xSYSCTL_PERIPH_PWMA){
        xHWREG(SYSCLK_APBCLK1) &= ~(SYSCLK_APBCLK1_PWMA01_EN|SYSCLK_APBCLK1_PWMA23_EN|SYSCLK_APBCLK1_PWMA45_EN);
    } else if(ulPeripheral == xSYSCTL_PERIPH_PWMB){
        xHWREG(SYSCLK_APBCLK1) &= ~(SYSCLK_APBCLK1_PWMB01_EN|SYSCLK_APBCLK1_PWMB23_EN|SYSCLK_APBCLK1_PWMB45_EN);
    } else {
        xHWREG(g_pulAXBCLKRegs[SYSCTL_PERIPH_INDEX_E(ulPeripheral)]) &=
            ~(1 << SYSCTL_PERIPH_MASK_E(ulPeripheral));
    }
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief Resets the device.
//!
//! This function will perform a software reset of the entire device. Processor
//! and all peripherals will be reset and all device registers will return to
//! their default values (with the exception of the reset cause register, which
//! will maintain its current value but have the software reset bit set as well).
//!
//! \return This function does not return.
//
//*****************************************************************************
void
xSysCtlReset(void)
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
//! until the processor returns to run mode.
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
    SysCtlPowerDownEnable(1);
    SysCtlPowerDownWaitCPUSet(1);
    xCPUwfi();
    SysCtlPowerDownEnable(0);
    SysCtlPowerDownWaitCPUSet(0);
}

//*****************************************************************************
//
//! \brief Puts the processor into deep-sleep mode.
//!
//! This function places the processor into deep-sleep mode; it will not return
//! until the processor returns to run mode.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlDeepSleep(void)
{
    //
    // Enable deep-sleep.
    //
    xHWREG(NVIC_SYS_CTRL) |= NVIC_SYS_CTRL_SLEEPDEEP;
    SysCtlPowerDownEnable(1);
    SysCtlPowerDownWaitCPUSet(1);

    //
    // Wait for an interrupt.
    //
    xCPUwfi();

    //
    // Disable deep-sleep so that a future sleep will work correctly.
    //
    xHWREG(NVIC_SYS_CTRL) &= ~(NVIC_SYS_CTRL_SLEEPDEEP);
    SysCtlPowerDownEnable(0);
    SysCtlPowerDownWaitCPUSet(0);
}

//*****************************************************************************
//
//! \brief This function is used to control power down entry condition  
//!
//! \param bEnable is a boolean that is \b true if active power down entry and 
//! \b false if not.
//! 
//! This function is used to control power down entry condition 
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlPowerDownWaitCPUSet(xtBoolean bEnable)
{    
    //
    // Enable BOD reset function or interrupt function.
    //
    SysCtlKeyAddrUnlock();
    if(bEnable)
    {
        xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_PD_WAIT_CPU;
    }
    else
    {
        xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_PD_WAIT_CPU;
    }
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief Set a HCLK clock source.
//!
//! \param ulHclkSrcSel is the HCLK clock source to set.
//!
//! The function is used to select HCLK clock source
//!
//! The \e ulHclkSrcSel parameter must be only one of the following values:
//! \b SYSCTL_HLCK_S_EXT12M, \b SYSCTL_HLCK_S_EXT32K, \b SYSCTL_HLCK_S_PLL,
//! \b SYSCTL_HLCK_S_INT10K, \b SYSCTL_HLCK_S_INT22M.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlHClockSourceSet(unsigned long ulHclkSrcSel)
{
    //
    // Check the arguments.
    //
    xASSERT(((ulHclkSrcSel == SYSCTL_HLCK_S_EXT12M)?
              (xHWREG(SYSCLK_PWRCON) & SYSCLK_PWRCON_XTL12M_EN)
              == SYSCLK_PWRCON_XTL12M_EN
          : 1)||
            ((ulHclkSrcSel==SYSCTL_HLCK_S_EXT32K)?
             (xHWREG(SYSCLK_PWRCON) & SYSCLK_PWRCON_XTL32K_EN)
             ==SYSCLK_PWRCON_XTL32K_EN
          : 1)||
            ((ulHclkSrcSel==SYSCTL_HLCK_S_PLL)?
             (xHWREG(SYSCLK_PLLCON)&SYSCLK_PLLCON_OE)==0 &&
             (xHWREG(SYSCLK_PLLCON)&SYSCLK_PLLCON_PD)==0
          : 1)||
            ((ulHclkSrcSel==SYSCTL_HLCK_S_INT10K)?
             (xHWREG(SYSCLK_PWRCON) & SYSCLK_PWRCON_OSC10K_EN)
             == SYSCLK_PWRCON_OSC10K_EN
          : 1)||
            ((ulHclkSrcSel==SYSCTL_HLCK_S_INT22M)?
             (xHWREG(SYSCLK_PWRCON) & SYSCLK_PWRCON_OSC22M_EN)
             == SYSCLK_PWRCON_OSC22M_EN
          : 1)
           );

    //
    // Enable HCLK clock source.
    //
    SysCtlKeyAddrUnlock();
    xHWREG(SYSCLK_CLKSEL0) &=~SYSCLK_CLKSEL0_HCLK_M;
    xHWREG(SYSCLK_CLKSEL0) |= ulHclkSrcSel;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief Set a SysTick clock source.
//!
//! \param ulHclkSrcSel is the SysTick clock source to set.
//!
//! The function is used to select SysTick clock source
//!
//! The \e ulHclkSrcSel parameter must be only one of the following values:
//! \b SYSCTL_STCLK_S_EXT12M, \b SYSCTL_STCLK_S_EXT32K, \b SYSCTL_STCLK_S_HCLK_2, 
//! \b SYSCTL_STCLK_S_EXT12M_2, \b SYSCTL_STCLK_S_INT22M_2.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlSysTickSourceSet(unsigned long ulHclkSrcSel)
{
    //
    // Check the arguments.
    //
    xASSERT((ulHclkSrcSel==SYSCTL_STCLK_S_EXT12M)||
            (ulHclkSrcSel==SYSCTL_STCLK_S_EXT32K)||
            (ulHclkSrcSel==SYSCTL_STCLK_S_EXT12M_2)||
            (ulHclkSrcSel==SYSCTL_STCLK_S_HCLK_2)||
            (ulHclkSrcSel==SYSCTL_STCLK_S_INT22M_2)         
           );

    //
    // Enable SysTickclock source.
    //
    SysCtlKeyAddrUnlock();
    xHWREG(SYSCLK_CLKSEL0) &=~SYSCLK_CLKSEL0_STCLK_M;
    xHWREG(SYSCLK_CLKSEL0) |=ulHclkSrcSel;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief The function is used to Reset CPU 
//!
//! \param None.
//!
//! The function is used to Reset CPU 
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlCPUReset(void)
{
    SysCtlKeyAddrUnlock();
    xHWREG(GCR_IPRSTC1) |= GCR_IPRSTC1_CPU;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief The function is used to Reset chip 
//!
//! \param None.
//!
//! The function is used to Reset chip 
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlChipReset(void)
{
    SysCtlKeyAddrUnlock();
    xHWREG(GCR_IPRSTC1) |= GCR_IPRSTC1_CHIP;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief The function is used to Unlock protected registers
//!
//! \param None.
//!
//! The function is used to Unlock protected registers
//!
//! \return Returns \b true if the protected registers is unlocked and \b false 
//! if it is not.
//
//*****************************************************************************
xtBoolean 
SysCtlKeyAddrUnlock(void)
{
    //
    // Unlock the protected registers.
    //
    while(xHWREG(GCR_REGLOCK) != 0x01){
        xHWREG(GCR_REGLOCK) = 0x59;
        xHWREG(GCR_REGLOCK) = 0x16;
        xHWREG(GCR_REGLOCK) = 0x88;
    }
    return 1;
}

//*****************************************************************************
//
//! \brief The function is used to lock protected registers
//!
//! \param None.
//!
//! The function is used to lock protected registers
//!
//! \return Returns \b true if the protected registers is unlocked and \b false 
//! if it is not.
//
//*****************************************************************************
xtBoolean 
SysCtlKeyAddrLock(void)
{
    //
    // Lock the protected registers.
    //
    xHWREG(GCR_REGLOCK) = 0x00;
    
    return xHWREG(GCR_REGLOCK)&0x01;
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
//! \b SYSCTL_RSTSRC_POR, \b SYSCTL_RSTSRC_WDG, \b SYSCTL_RSTSRC_LVR,
//! \b SYSCTL_RSTSRC_BOD, \b SYSCTL_RSTSRC_SYS, and \b SYSCTL_RSTSRC_PAD
//! \b SYSCTL_RSTSRC_CPU.
//
//*****************************************************************************
unsigned long 
SysCtlResetSrcGet(void)
{
    //
    // Get reset source from last operation.
    //
    
    return xHWREG(GCR_RSTSRC);
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
//! \b SYSCTL_RSTSRC_POR, \b SYSCTL_RSTSRC_PAD, \b SYSCTL_RSTSRC_WDG,
//! \b SYSCTL_RSTSRC_LVR, \b SYSCTL_RSTSRC_BOD, \b SYSCTL_RSTSRC_SYS,
//! \b SYSCTL_RSTSRC_CPU.
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
    xASSERT((ulSrc == SYSCTL_RSTSRC_POR) ||
            (ulSrc == SYSCTL_RSTSRC_PAD) ||
            (ulSrc == SYSCTL_RSTSRC_WDG) ||
            (ulSrc == SYSCTL_RSTSRC_LVR) ||
            (ulSrc == SYSCTL_RSTSRC_BOD) ||
            (ulSrc == SYSCTL_RSTSRC_SYS) ||
            (ulSrc == SYSCTL_RSTSRC_CPU));
    //
    // Clear reset source from last operation.
    //
    
    xHWREG(GCR_RSTSRC) |= ulSrc;
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
    SysCtlKeyAddrUnlock();
    if(bEnable)
    {
        xHWREG(GCR_BODCR) |= GCR_BODCR_BOD_EN;
    }
    else
    {
        xHWREG(GCR_BODCR) &= ~GCR_BODCR_BOD_EN;
    }
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief The function is used to Set BOD threshold voltage
//!
//! \param ulVoltage the volt will be set
//!
//! The function is used to Select BOD threshold voltage
//!
//! The \e ulVoltage parameter must be only one of the following values:
//! \b SYSCTL_BOD_2_2, \b SYSCTL_BOD_2_6, \b SYSCTL_BOD_3_8,\b SYSCTL_BOD_4_5.
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlBODVoltSelect(unsigned char ulVoltage)
{
    //
    // Check the arguments.
    //
    xASSERT((ulVoltage == SYSCTL_BOD_2_2) ||
           (ulVoltage == SYSCTL_BOD_2_6) ||
           (ulVoltage == SYSCTL_BOD_3_8) ||
           (ulVoltage == SYSCTL_BOD_4_5));
    //
    // Select BOD threshold voltage.
    //
    SysCtlKeyAddrUnlock();
    xHWREG(GCR_BODCR) &= ~GCR_BODCR_BOD_VL_M;
    xHWREG(GCR_BODCR) |= ulVoltage;
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief The function is used to Enable BOD low power mode
//!
//! \param bEnable is a boolean that is \b true if Enable BOD low power mode and 
//! \b false if not.
//!
//! The function is used to Enable BOD low power mode
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlBODLowPowerModeEnable(xtBoolean bEnable)
{
    //
    // Enable BOD low power mode or not.
    //
    SysCtlKeyAddrUnlock();
    if(bEnable)
    {
        xHWREG(GCR_BODCR) |= GCR_BODCR_BOD_LPM;
    }
    else
    {
        xHWREG(GCR_BODCR) &= ~GCR_BODCR_BOD_LPM;
    }
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief The function is used to Enable low voltage reset
//!
//! \param bEnable is a boolean that is \b true if Enable low voltage reset and 
//! \b false if not.
//!
//! The function is used to Enable low voltage reset
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlLowVoltRstEnable(xtBoolean bEnable)
{
    //
    // Enable Enable low voltage reset or not.
    //
    SysCtlKeyAddrUnlock();
    if(bEnable)
    {
        xHWREG(GCR_BODCR) |= GCR_BODCR_LVR_EN;
    }
    else
    {
        xHWREG(GCR_BODCR) &= ~GCR_BODCR_LVR_EN;
    }
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief The function is used to Get BOD state
//!
//! \param None.
//!
//! The function is used to Get BOD state
//!
//! \return Reset source enumerated as a bit field of
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
    
    return (xHWREG(GCR_BODCR) & GCR_BODCR_BOD_OUT)>>6;
}

//*****************************************************************************
//
//! \brief The function is used to Enable BOD reset function or interrupt function
//!
//! \param bEnable is a boolean that is \b true if Enable BOD reset function and 
//! \b false if not.
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlBODRstEnable(xtBoolean bEnable)
{
    //
    // Enable BOD reset function or interrupt function.
    //
    SysCtlKeyAddrUnlock();
    if(bEnable)
    {
        xHWREG(GCR_BODCR) |= GCR_BODCR_BOD_RSTEN;
    }
    else
    {
        xHWREG(GCR_BODCR) &= ~GCR_BODCR_BOD_RSTEN;
    }
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief This function is used to set IP divider number from the corresponding 
//! clock source.
//!
//! \param ulConfig is the required configuration of the IP divider.
//!
//! The \e ulConfig parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The peripheral is chosen with one of the following values:
//! \b SYSCTL_PERIPH_HCLK_D, \b SYSCTL_PERIPH_USB_D, \b SYSCTL_PERIPH_UART_D
//!
//! The divider number is chosen with one of the following values:
//! divider 1-16 for peripheral
//! 
//! \return None.
//
//*****************************************************************************
void
SysCtlIPClockDividerSet(unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT((ulConfig & 0xFF)<=256);
    
    //
    // Set  this peripheral clock source
    //
    xHWREG(g_pulCLKDivRegs[SYSCTL_PERIPH_INDEX_CLK(ulConfig)]) &=
    		                  ~(((ulConfig) >> 8) << (ulConfig >> 16));
    xHWREG(g_pulCLKDivRegs[SYSCTL_PERIPH_INDEX_CLK(ulConfig)]) |=
    		               (((ulConfig & 0xff) - 1) << (ulConfig >> 16));
}

//*****************************************************************************
//
//! \brief The function is used to  Enable or disable PD_WU interrupt function
//! and enable 64 clock cycle delay to wait oscillator clock stable 
//!
//! \param bEnable is a boolean that is \b true if active power down function and 
//! \b false if not.
//! 
//! \param bDelay  is \b true if Enable 64 clock cycle delay \b false if not.
//!
//! The function is used to  Enable or disable PD_WU interrupt function
//! and enable 64 clock cycle delay to wait oscillator clock stable
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlPWRWUIntEnable(xtBoolean bEnable, xtBoolean bDelay)
{    
    //
    // Enable BOD reset function or interrupt function.
    //
    SysCtlKeyAddrUnlock();
    if(bEnable)
    {
        xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_PD_INT_EN;
        if(bDelay)
        {
            xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_WU_DLY;
        }
        else
        {
            xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_WU_DLY;
        }
    }
    else
    {
        xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_PD_INT_EN;
        xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_WU_DLY;
    }
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief The function is used to Enable or active power down function 
//!
//! \param bEnable is a boolean that is \b true if active power down function and 
//! \b false if not.
//! 
//! The function is used to Enable or active power down function 
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlPowerDownEnable(xtBoolean bEnable)
{    
    //
    // Enable or active power down function.
    //
    SysCtlKeyAddrUnlock();
    if(bEnable)
    {
    	xHWREG(NVIC_SYS_CTRL) |= NVIC_SYS_CTRL_SLEEPDEEP;
        xHWREG(SYSCLK_PWRCON) |= (SYSCLK_PWRCON_PWR_DO_EN | SYSCLK_PWRCON_WU_DLY);
    }
    else
    {
    	xHWREG(NVIC_SYS_CTRL) &= ~NVIC_SYS_CTRL_SLEEPDEEP;
        xHWREG(SYSCLK_PWRCON) &= ~(SYSCLK_PWRCON_PWR_DO_EN | SYSCLK_PWRCON_WU_DLY);
    }
    SysCtlKeyAddrLock();
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
xSysCtlClockGet(void)
{
    unsigned long  ulFreqout = 0, ulAHBDivider, ulPLLSrc, ulNF, ulNR, ulNO;
    unsigned long ulMap[4] = {1, 2, 2, 4};
    //
    // external 12MHz crystal clock.
    //
    if ((xHWREG(SYSCLK_CLKSEL0) & SYSCLK_CLKSEL0_HCLK_M) ==                    \
                                 SYSCLK_CLKSEL0_HCLK12M)
    {
        ulFreqout = s_ulExtClockMHz*1000000;  
    }
    //
    // external 32KHz crystal clock.
    //
    else if((xHWREG(SYSCLK_CLKSEL0) & SYSCLK_CLKSEL0_HCLK_M) ==
                                     SYSCLK_CLKSEL0_HCLK32K)
    {
        ulFreqout = 32768;
    }
    //
    // PLL clock.
    //
    else if((xHWREG(SYSCLK_CLKSEL0) & SYSCLK_CLKSEL0_HCLK_M) ==                \
                                     SYSCLK_CLKSEL0_HCLKPLL)    
    {
        if((xHWREG(SYSCLK_PLLCON) & SYSCLK_PLLCON_PLL_SRC))
        {
            ulPLLSrc = 22000000;
        }
        else
        {
            ulPLLSrc = s_ulExtClockMHz*1000000;
        }
        if ((xHWREG(SYSCLK_PLLCON) & SYSCLK_PLLCON_PD))
        {
            ulFreqout = 0;
        }
        else
        {
            ulNF = (xHWREG(SYSCLK_PLLCON) & SYSCLK_PLLCON_FB_DV_M);
            ulNR = (xHWREG(SYSCLK_PLLCON) & SYSCLK_PLLCON_IN_DV_M) >>          \
                                           SYSCLK_PLLCON_IN_DV_S;
            ulNO = (xHWREG(SYSCLK_PLLCON) & SYSCLK_PLLCON_OUT_DV_M) >>         \
                                           SYSCLK_PLLCON_OUT_DV_S;
            ulFreqout =  ulPLLSrc*(ulNF+2)/(ulNR+2)/(ulMap[ulNO]);
        }
    }
    //
    // internal 10KHz oscillator clock.
    //
    else if((xHWREG(SYSCLK_CLKSEL0) & SYSCLK_CLKSEL0_HCLK_M) ==                \
                                     SYSCLK_CLKSEL0_HCLK10K)   
    {
        ulFreqout = 10000;
    }
    //
    // internal 22MHz oscillator clock.
    //
    else                              
    {
        ulFreqout = 22000000;
    }
    ulAHBDivider = (xHWREG(SYSCLK_CLKDIV0) & SYSCLK_CLKDIV_HCLK_M) + 1 ;
    return (ulFreqout/ulAHBDivider);
}

//*****************************************************************************
//
//! \brief This function is used to set HCLK for the system
//!
//! \param ulConfig is the required configuration of the device clocking.
//!
//! The \e ulConfig parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The system clock divider is chosen with one of the following values:
//! \b SYSCTL_SYSDIV_1, \b SYSCTL_SYSDIV_2, \b SYSCTL_SYSDIV_3, ...
//! \b SYSCTL_SYSDIV_16.
//! 
//! The external crystal frequency is chosen with one of the following values:
//! \b SYSCTL_XTAL_4MHZ, \b SYSCTL_XTAL_5MHZ, \b SYSCTL_XTAL_6MHZ,
//! \b SYSCTL_XTAL_7MHZ, ..., \b SYSCTL_XTAL_24MHZ, 
//!
//! The HCLK source is chosen with one of the following values:
//! \b SYSCTL_OSC_MAIN, \b SYSCTL_OSC_EXTSL, \b SYSCTL_OSC_PLL,
//! \b SYSCTL_OSC_INT, or \b SYSCTL_OSC_INTSL. 
//!
//! The PLL source is chosen with one of the following values:
//! \b SYSCTL_PLL_MAIN, \b SYSCTL_PLL_INT.
//!
//! The internal and main oscillators and PLL are disabled with the
//! \b SYSCTL_INT_OSC_DIS and \b SYSCTL_MAIN_OSC_DIS flags, 
//! \b SYSCTL_PLL_PWRDN respectively.
//! The external oscillator must be enabled in order to use an external clock
//! source.  Note that attempts to disable the oscillator used to clock the
//! device will be prevented by the hardware.
//!
//! \note If HCLK source is chosen PLL, Then the PLL out will be 48 Mhz
//! 
//! \return None.
//
//*****************************************************************************
void
SysCtlHClockSet(unsigned long ulConfig)
{

    s_ulExtClockMHz = ((ulConfig & SYSCTL_XTAL_MASK) >> 8);
    SysCtlKeyAddrUnlock();
    //
    // HLCK clock source is SYSCLK_CLKSEL0_HCLK12M
    //
    if(((ulConfig & 0xF0) >> 4) == SYSCLK_CLKSEL0_HCLK12M)
    {
        //
        // Check the arguments .
        //
        xASSERT((ulConfig & SYSCLK_PWRCON_XTL12M_EN)==0);
        
        xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL12M_EN;
        SysCtlHClockSourceSet(SYSCTL_HLCK_S_EXT12M);
        //
        // Wait for the External 4~24 MHz High Speed Crystal Clock Source is stable
        //
        while(!(xHWREG(SYSCLK_CLKSTATUS) & 0x00000001));  
        SysCtlIPClockDividerSet(SYSCTL_PERIPH_HCLK_D |                        \
                               (((ulConfig & 0x0F000000) >> 24)+1));
        if((ulConfig & SYSCLK_PWRCON_OSC22M_EN)!=0)
        {
            xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_OSC22M_EN;
        }

        if((ulConfig & SYSCLK_PLLCON_PD)!=0)
        {
            xHWREG(SYSCLK_PLLCON) |= SYSCLK_PLLCON_PD;
        }
        
    }
    //
    // HLCK clock source is SYSCLK_CLKSEL0_HCLK32K
    //
    else if(((ulConfig & 0xF0) >> 4) == SYSCLK_CLKSEL0_HCLK32K)
    {
        xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL32K_EN;
        SysCtlHClockSourceSet(SYSCTL_HLCK_S_EXT32K);
        //
        // Wait for External 32.768 kHz Low Speed Crystal Clock Source is stable
        //
        while(!(xHWREG(SYSCLK_CLKSTATUS) & 0x00000002));
        SysCtlIPClockDividerSet(SYSCTL_PERIPH_HCLK_D |
                               (((ulConfig & 0x0F000000) >> 24)+1));
        if((ulConfig & SYSCLK_PWRCON_OSC22M_EN)!=0)
        {
            xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_OSC22M_EN;
        }
        if((ulConfig & SYSCLK_PWRCON_XTL12M_EN)!=0)
        {
            xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_XTL12M_EN;
        }
        if((ulConfig & SYSCLK_PLLCON_PD)!=0)
        {
            xHWREG(SYSCLK_PLLCON) |= SYSCLK_PLLCON_PD;
        }
    }
    //
    // HLCK clock source is SYSCLK_CLKSEL0_HCLKPLL
    //
    else if(((ulConfig & 0xF0) >> 4) == SYSCLK_CLKSEL0_HCLKPLL)
    {
        //
        // Check the arguments .
        //
        xASSERT((ulConfig & SYSCLK_PLLCON_PD)==0);
        
        if((ulConfig & SYSCLK_PLLCON_PLL_SRC)==0)
        {
            //
            // Check the arguments .
            //
            xASSERT((ulConfig & SYSCLK_PWRCON_XTL12M_EN)==0);
            
            xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL12M_EN;

            xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_PLL_SRC;

            xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_OE;

            xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_PD;
            
            xSysCtlDelay(1000);
            
            if((ulConfig & SYSCLK_PWRCON_OSC22M_EN)!=0)
            {
                xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_OSC22M_EN;
            }           
        }
        else 
        {
            //
            // Check the arguments .
            //
            xASSERT((ulConfig & SYSCLK_PWRCON_OSC22M_EN)==0);

            xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC22M_EN;

            SysCtlHClockSourceSet(SYSCTL_HLCK_S_INT22M);

            xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_FB_DV_M;
            xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_IN_DV_M;
            xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_OUT_DV_M;
            
            xHWREG(SYSCLK_PLLCON) |= (0x5E << SYSCLK_PLLCON_FB_DV_S);
            xHWREG(SYSCLK_PLLCON) |= (0x9 << SYSCLK_PLLCON_IN_DV_S);
            xHWREG(SYSCLK_PLLCON) |= (0x3 << SYSCLK_PLLCON_OUT_DV_S);
            
            xHWREG(SYSCLK_PLLCON) |= SYSCLK_PLLCON_PLL_SRC;

            xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_OE;
            xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_PD;
            xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_BP;
            xSysCtlDelay(1000);
            
            if((ulConfig & SYSCLK_PWRCON_XTL12M_EN)!=0)
            {
                xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_XTL12M_EN;
            }
        }
        SysCtlHClockSourceSet(SYSCTL_HLCK_S_PLL);
        //
        // Wait for Internal PLL Clock Source is stable
        //
        while(!(xHWREG(SYSCLK_CLKSTATUS) & 0x00000004));
        SysCtlIPClockDividerSet(SYSCTL_PERIPH_HCLK_D |                        \
                               (((ulConfig & 0x0F000000) >> 24)+1));
    }
    //
    // HLCK clock source is SYSCLK_CLKSEL0_HCLK10K
    //
    else if(((ulConfig & 0xF0) >> 4) == SYSCLK_CLKSEL0_HCLK10K)
    {
        xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC10K_EN;
        SysCtlHClockSourceSet(SYSCTL_HLCK_S_INT10K);
        //
        // Wait for Internal 10 kHz Low Speed Oscillator Clock Source is stable
        //
        while(!(xHWREG(SYSCLK_CLKSTATUS) & 0x00000008));
        SysCtlIPClockDividerSet(SYSCTL_PERIPH_HCLK_D |                        \
                               (((ulConfig & 0x0F000000) >> 24)+1));
        if((ulConfig & SYSCLK_PWRCON_OSC22M_EN)!=0)
        {
            xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_OSC22M_EN;
        }
        if((ulConfig & SYSCLK_PWRCON_XTL12M_EN)!=0)
        {
            xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_XTL12M_EN;
        }
        if((ulConfig & SYSCLK_PLLCON_PD)!=0)
        {
            xHWREG(SYSCLK_PLLCON) |= SYSCLK_PLLCON_PD;
        }
    }
    //
    // HLCK clock source is SYSCLK_PWRCON_OSC22M_EN
    //
    else 
    {
        //
        // Check the arguments .
        //
        xASSERT((ulConfig & SYSCLK_PWRCON_OSC22M_EN)==0);
        
        xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC22M_EN;
        SysCtlHClockSourceSet(SYSCTL_HLCK_S_INT22M);
        //
        // Wait for Internal 22.1184 MHz High Speed Oscillator Clock Source is stable
        //
        while(!(xHWREG(SYSCLK_CLKSTATUS) & 0x00000010));
        SysCtlIPClockDividerSet(SYSCTL_PERIPH_HCLK_D |                        \
                               (((ulConfig & 0x0F000000) >> 24)+1));
        if((ulConfig & SYSCLK_PWRCON_XTL12M_EN)!=0)
        {
            xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_XTL12M_EN;
        }
        if((ulConfig & SYSCLK_PLLCON_PD)!=0)
        {
            xHWREG(SYSCLK_PLLCON) |= SYSCLK_PLLCON_PD;
        }
    }
    SysCtlKeyAddrLock();
}


//*****************************************************************************
//
//! \brief The function is used to Enable Tempature Sensor
//!
//! \param bEnable is a boolean that is \b true if Enable Tempature Sensor and
//! \b false if not.
//!
//! The function is used to Enable Tempature Sensor
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlTempatureSensorEnable(xtBoolean bEnable)
{
    //
    // Enable Enable Tempature Sensor or not.
    //
    if(bEnable)
    {
        xHWREG(GCR_TEMPCR) |= GCR_TEMPCR_VTEMP_EN;
    }
    else
    {
        xHWREG(GCR_TEMPCR) &= ~GCR_TEMPCR_VTEMP_EN;
    }
}


//*****************************************************************************
//
//! \brief The function is used to Enable frequency clock output and set its
//! divider value
//!
//! \param bEnable is a boolean that is \b true if Enable frequency clock
//! output and \b false if not.
//!
//! \param u8Divider is the divider value
//!
//! The function is used to Enable frequency clock output and set its divider
//! value
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlFreqDividerOutputEnable(xtBoolean bEnable, unsigned char u8Divider)
{
    //
    // Check the arguments.
    //
    xASSERT(u8Divider <= 15);

    //
    // Enable BOD reset function or interrupt function.
    //
    if(bEnable)
    {
        xHWREG(SYSCLK_FRQDIV) &= ~SYSCLK_FRQDIV_FSEL_M;
        xHWREG(SYSCLK_FRQDIV) |= u8Divider;
        xHWREG(SYSCLK_FRQDIV) |= SYSCLK_FRQDIV_EN;
        xSysCtlPeripheralEnable(SYSCTL_PERIPH_FDIV);
    }
    else
    {
        xHWREG(SYSCLK_FRQDIV) &= ~SYSCLK_FRQDIV_EN;
        xSysCtlPeripheralDisable(SYSCTL_PERIPH_FDIV);
    }
}
