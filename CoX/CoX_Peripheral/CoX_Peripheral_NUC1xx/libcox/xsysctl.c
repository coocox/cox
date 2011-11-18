//*****************************************************************************
//
//! \file xsysctl.c
//! \brief Driver for the system controller
//! \version V2.1.1.1
//! \date 11/14/2011
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
#define SYSCTL_PERIPH_MASK_CLK(a)                                             \
                                ((((((a) & 0x1f0000) >> 16) <= 20) &&         \
                                ((((a) & 0x1f0000) >> 16) >= 8))  ?           \
                                ((0x7) << ((((a) & 0x1f0000) >> 16))) :       \
                                ((0x3) << ((((a) & 0x1f0000) >> 16))))
//*****************************************************************************
//
// This macro constructs the peripheral bit mask from the peripheral clock source.
//
//*****************************************************************************
#define SYSCTL_PERIPH_MASK_DIV(a)                                             \
                                (((((a) & 0x1f00) >> 8) == 16)?            \
                                ((0xFF) << ((((a) & 0x1f00) >> 8))) :      \
                                ((0xF) << ((((a) & 0x1f00) >> 8))))

//*****************************************************************************
//
// This macro constructs the peripheral bit mask from the peripheral clock source.
//
//*****************************************************************************
#define SYSCTL_PERIPH_ENUM_CLK(a)                                             \
                                (((a) & 0xff) << (((a) & 0x1f0000) >> 16))
                                
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
                                (((a) & 0xff0000) << (((a) & 0x1f000000) >> 24))

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
                                (((a) & 0xff) >> (((a) & 0x1f00) >> 8)) :   \
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
    GCR_IPRSTC1,
    GCR_IPRSTC2
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
    SYSCLK_APBCLK
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
    SYSCLK_CLKSEL1,
    SYSCLK_CLKSEL2
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
// An array that maps the peripheral base and peripheral ID and interrupt number
// together to enablea peripheral or peripheral interrupt by a peripheral base.
//
//*****************************************************************************
static const tPeripheralTable g_pPeripherals[] =
{
    {xGPIO_PORTA_BASE, xSYSCTL_PERIPH_GPIOA, INT_GPAB},
    {xGPIO_PORTB_BASE, xSYSCTL_PERIPH_GPIOB, INT_GPAB},
    {xGPIO_PORTC_BASE, xSYSCTL_PERIPH_GPIOC, INT_GPCDE},
    {xGPIO_PORTD_BASE, xSYSCTL_PERIPH_GPIOD, INT_GPCDE},
    {xGPIO_PORTE_BASE, xSYSCTL_PERIPH_GPIOE, INT_GPCDE},
    {xWDT_BASE,        xSYSCTL_PERIPH_WDOG, INT_WDT},
    {xUART0_BASE,      xSYSCTL_PERIPH_UART0, INT_UART02},
    {xUART1_BASE,      xSYSCTL_PERIPH_UART1, INT_UART1},
    {xUART2_BASE,      xSYSCTL_PERIPH_UART2, INT_UART02},
    {xTIMER0_BASE,     xSYSCTL_PERIPH_TIMER0, INT_TIMER0},
    {xTIMER1_BASE,     xSYSCTL_PERIPH_TIMER1, INT_TIMER1},
    {xTIMER2_BASE,     xSYSCTL_PERIPH_TIMER2, INT_TIMER2},
    {xTIMER3_BASE,     xSYSCTL_PERIPH_TIMER3, INT_TIMER3},
    {xSPI0_BASE,       xSYSCTL_PERIPH_SPI0, INT_SPI0},
    {xSPI1_BASE,       xSYSCTL_PERIPH_SPI1, INT_SPI1},
    {xSPI2_BASE,       xSYSCTL_PERIPH_SPI2, INT_SPI2},
    {xSPI3_BASE,       xSYSCTL_PERIPH_SPI3, INT_SPI3},
    {xI2C0_BASE,       xSYSCTL_PERIPH_I2C0, INT_I2C0},
    {xI2C1_BASE,       xSYSCTL_PERIPH_I2C1, INT_I2C1},
    {xADC0_BASE,       xSYSCTL_PERIPH_ADC0, INT_ADC},
    {xACMP0_BASE,      xSYSCTL_PERIPH_ACMP0, INT_ACMP},
    {xPWMA_BASE,       xSYSCTL_PERIPH_PWMA, INT_PWMA},
    {xPWMB_BASE,       xSYSCTL_PERIPH_PWMB, INT_PWMB},
    {0,                0,                   0},
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
    return((ulPeripheral == SYSCTL_PERIPH_PDMA) ||
           (ulPeripheral == SYSCTL_PERIPH_ISP) ||
           (ulPeripheral == SYSCTL_PERIPH_WDT) ||
           (ulPeripheral == SYSCTL_PERIPH_GPIO) ||
           (ulPeripheral == SYSCTL_PERIPH_RTC) ||
           (ulPeripheral == SYSCTL_PERIPH_TMR0) ||
           (ulPeripheral == SYSCTL_PERIPH_TMR1) ||
           (ulPeripheral == SYSCTL_PERIPH_TMR2) ||
           (ulPeripheral == SYSCTL_PERIPH_TMR3) ||
           (ulPeripheral == SYSCTL_PERIPH_FDIV) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C0) ||
           (ulPeripheral == SYSCTL_PERIPH_I2C1) ||
           (ulPeripheral == SYSCTL_PERIPH_SPI0) ||
           (ulPeripheral == SYSCTL_PERIPH_SPI1) ||
           (ulPeripheral == SYSCTL_PERIPH_SPI2) ||
           (ulPeripheral == SYSCTL_PERIPH_SPI3) ||
           (ulPeripheral == SYSCTL_PERIPH_UART0) ||
           (ulPeripheral == SYSCTL_PERIPH_UART1) ||
           (ulPeripheral == SYSCTL_PERIPH_UART2) ||
           (ulPeripheral == SYSCTL_PERIPH_PWM01) ||
           (ulPeripheral == SYSCTL_PERIPH_PWM23) ||
           (ulPeripheral == SYSCTL_PERIPH_PWM45) ||
           (ulPeripheral == SYSCTL_PERIPH_PWM67) ||
           (ulPeripheral == SYSCTL_PERIPH_CAN0) ||
           (ulPeripheral == SYSCTL_PERIPH_USBD) ||
           (ulPeripheral == SYSCTL_PERIPH_ADC) ||
           (ulPeripheral == SYSCTL_PERIPH_I2S) ||
           (ulPeripheral == SYSCTL_PERIPH_ACMP) ||
           (ulPeripheral == SYSCTL_PERIPH_PS2));
}
#endif

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
//! \ref xSYSCTL_XTAL_4MHZ, \ref xSYSCTL_XTAL_5MHZ, \ref xSYSCTL_XTAL_6MHZ,
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
    xASSERT((ulSysClk > 0 && ulSysClk <= 50000000));

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
            
            SysCtlHClockSourceSet(SYSCTL_HLCK_S_EXT12M);
            SysCtlDelay(100);
            ulOscFreq = s_ulExtClockMHz*1000000;      
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
            SysCtlDelay(100);
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
            SysCtlDelay(100);
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
            SysCtlHClockSourceSet(SYSCTL_HLCK_S_EXT32K);
            SysCtlDelay(100);
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
        xASSERT((ulSysClk >= 25000000 && ulSysClk <= 50000000));
        xASSERT(((ulConfig & SYSCTL_OSCSRC_M) == xSYSCTL_OSC_MAIN) ||
                ((ulConfig & SYSCTL_OSCSRC_M) == xSYSCTL_OSC_INT));
        ulSysClk = ulSysClk << 2;
        ulNF = ulSysClk/1000000;
        ulNR = ulOscFreq/1000000;
        ulNO = 0x3;
        if((ulConfig & SYSCLK_PLLCON_PLL_SRC)==0)
        {
            //
            // Check the arguments .
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
        xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC22M_EN;
        SysCtlHClockSourceSet(SYSCTL_HLCK_S_INT22M);
        xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_FB_DV_M;
        xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_IN_DV_M;
        xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_OUT_DV_M;
        xHWREG(SYSCLK_PLLCON) |= ((ulNF-2) << SYSCLK_PLLCON_FB_DV_S);
        xHWREG(SYSCLK_PLLCON) |= ((ulNR-2) << SYSCLK_PLLCON_IN_DV_S);
        xHWREG(SYSCLK_PLLCON) |= (ulNO << SYSCLK_PLLCON_OUT_DV_S);
        xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_OE;
        xHWREG(SYSCLK_PLLCON) &= ~SYSCLK_PLLCON_PD;
        SysCtlDelay(1000);
        SysCtlHClockSourceSet(SYSCTL_HLCK_S_PLL);
        SysCtlDelay(100);
        SysCtlIPClockDividerSet(SYSCTL_PERIPH_HCLK_D | (SYSCTL_SYSDIV_1 + 1));
        if((ulConfig & SYSCLK_PWRCON_OSC22M_EN)!=0)
		{
			xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_OSC22M_EN;
		}
    }
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
    xASSERT((ulPeripheralBase == xGPIO_PORTA_BASE)||
            (ulPeripheralBase == xGPIO_PORTB_BASE)||
            (ulPeripheralBase == xGPIO_PORTC_BASE)||
            (ulPeripheralBase == xGPIO_PORTD_BASE)||
            (ulPeripheralBase == xGPIO_PORTE_BASE)||
            (ulPeripheralBase == xWDT_BASE)||   
            (ulPeripheralBase == xUART0_BASE)||   
            (ulPeripheralBase == xUART1_BASE)||   
            (ulPeripheralBase == xUART2_BASE)||   
            (ulPeripheralBase == xTIMER0_BASE)||    
            (ulPeripheralBase == xTIMER1_BASE)||          
            (ulPeripheralBase == xTIMER2_BASE)||    
            (ulPeripheralBase == xTIMER3_BASE)||        
            (ulPeripheralBase == xSPI0_BASE)||     
            (ulPeripheralBase == xSPI1_BASE)||         
            (ulPeripheralBase == xSPI2_BASE)||           
            (ulPeripheralBase == xSPI3_BASE)||   
            (ulPeripheralBase == xI2C0_BASE)||  
            (ulPeripheralBase == xI2C1_BASE)||
            (ulPeripheralBase == xADC0_BASE)||    
            (ulPeripheralBase == xACMP0_BASE)||       
            (ulPeripheralBase == xPWMA_BASE)||        
            (ulPeripheralBase == xPWMB_BASE)       
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
//! \brief Set a peripheral clock source and peripheral divide.
//!
//! \param ulPeripheralSrc is the peripheral clock source to set.
//! \param ulDivide is the peripheral clock divide to set.
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
    //
    // Check the arguments.
    //
    xASSERT((ulPeripheralSrc==xSYSCTL_WDT0_EXTSL)||
            (ulPeripheralSrc==xSYSCTL_WDT0_HCLK_2048)||
            (ulPeripheralSrc==xSYSCTL_WDT0_INTSL)||
            (ulPeripheralSrc==xSYSCTL_ADC0_MAIN)||
            (ulPeripheralSrc==xSYSCTL_ADC0_PLL)||
            (ulPeripheralSrc==xSYSCTL_ADC0_INT)||
            (ulPeripheralSrc==xSYSCTL_TIMER0_MAIN)||
            (ulPeripheralSrc==xSYSCTL_TIMER0_EXTSL)||
            (ulPeripheralSrc==xSYSCTL_TIMER0_HCLK)||
            (ulPeripheralSrc==xSYSCTL_TIMER0_EXTTRG)||
            (ulPeripheralSrc==xSYSCTL_TIMER0_INT)||
            (ulPeripheralSrc==xSYSCTL_TIMER1_MAIN)||
            (ulPeripheralSrc==xSYSCTL_TIMER1_EXTSL)||
            (ulPeripheralSrc==xSYSCTL_TIMER1_HCLK)||
            (ulPeripheralSrc==xSYSCTL_TIMER1_EXTTRG)||
            (ulPeripheralSrc==xSYSCTL_TIMER1_INT)||
            (ulPeripheralSrc==xSYSCTL_TIMER2_MAIN)||
            (ulPeripheralSrc==xSYSCTL_TIMER2_EXTSL)||
            (ulPeripheralSrc==xSYSCTL_TIMER2_HCLK)||
            (ulPeripheralSrc==xSYSCTL_TIMER2_EXTTRG)||
            (ulPeripheralSrc==xSYSCTL_TIMER2_INT)||
            (ulPeripheralSrc==xSYSCTL_TIMER3_MAIN)||
            (ulPeripheralSrc==xSYSCTL_TIMER3_EXTSL)||
            (ulPeripheralSrc==xSYSCTL_TIMER3_HCLK)||
            (ulPeripheralSrc==xSYSCTL_TIMER3_EXTTRG)||
            (ulPeripheralSrc==xSYSCTL_TIMER3_INT)||
            (ulPeripheralSrc==xSYSCTL_UART0_MAIN)||
            (ulPeripheralSrc==xSYSCTL_UART0_PLL)||
            (ulPeripheralSrc==xSYSCTL_UART0_INT)||
            (ulPeripheralSrc==xSYSCTL_CAN0_MAIN)||
            (ulPeripheralSrc==xSYSCTL_CAN0_PLL)||
            (ulPeripheralSrc==xSYSCTL_CAN0_INT)||
            (ulPeripheralSrc==xSYSCTL_PWMA_MAIN)||
            (ulPeripheralSrc==xSYSCTL_PWMA_EXTSL)||
            (ulPeripheralSrc==xSYSCTL_PWMA_HCLK)||
            (ulPeripheralSrc==xSYSCTL_PWMA_INT)||
            (ulPeripheralSrc==xSYSCTL_PWMB_MAIN)||
            (ulPeripheralSrc==xSYSCTL_PWMB_EXTSL)||
            (ulPeripheralSrc==xSYSCTL_PWMB_HCLK)||
            (ulPeripheralSrc==xSYSCTL_PWMB_INT)||
            (ulPeripheralSrc==xSYSCTL_I2S0_MAIN)||
            (ulPeripheralSrc==xSYSCTL_I2S0_PLL)||
            (ulPeripheralSrc==xSYSCTL_I2S0_HCLK)||
            (ulPeripheralSrc==xSYSCTL_I2S0_INT)||
            (ulPeripheralSrc==xSYSCTL_FRQDIV_MAIN)||
            (ulPeripheralSrc==xSYSCTL_FRQDIV_EXTSL)||
            (ulPeripheralSrc==xSYSCTL_FRQDIV_HCLK)||
            (ulPeripheralSrc==xSYSCTL_FRQDIV_INT)         
           );
    xASSERT((ulDivide <= 256) && (ulDivide >= 1));

    //
    // Set  this peripheral clock source
    //
    SysCtlKeyAddrUnlock();
    xHWREG(g_pulCLKSELRegs[SYSCTL_PERIPH_INDEX_CLK(ulPeripheralSrc)]) &=
        ~(SYSCTL_PERIPH_MASK_CLK(ulPeripheralSrc));
    xHWREG(g_pulCLKSELRegs[SYSCTL_PERIPH_INDEX_CLK(ulPeripheralSrc)]) |=
        SYSCTL_PERIPH_ENUM_CLK(ulPeripheralSrc);
    
    if (ulPeripheralSrc & 0x01000000)
    {
        xHWREG(SYSCLK_CLKDIV) &= ~(SYSCTL_PERIPH_MASK_DIV(ulPeripheralSrc));
        xHWREG(SYSCLK_CLKDIV) |= ((ulDivide-1) << (((ulPeripheralSrc) & 
                                  0x1f00) >> 8));
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
//! \b SYSCTL_PERIPH_PDMA, \b SYSCTL_PERIPH_GPIO, \b SYSCTL_PERIPH_TMR0,
//! \b SYSCTL_PERIPH_TMR1, \b SYSCTL_PERIPH_TMR2, \b SYSCTL_PERIPH_TMR3,
//! \b SYSCTL_PERIPH_I2C0, \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_SPI0,
//! \b SYSCTL_PERIPH_SPI1, \b SYSCTL_PERIPH_SPI2, \b SYSCTL_PERIPH_SPI3,
//! \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1, \b SYSCTL_PERIPH_UART2,
//! \b SYSCTL_PERIPH_PWM01, \b SYSCTL_PERIPH_PWM23, \b SYSCTL_PERIPH_PWM45,
//! \b SYSCTL_PERIPH_PWM67, \b SYSCTL_PERIPH_CAN0, \b SYSCTL_PERIPH_USBD,
//! \b SYSCTL_PERIPH_ADC, \b SYSCTL_PERIPH_I2S, \b SYSCTL_PERIPH_ACMP,
//! \b SYSCTL_PERIPH_PS2.
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
//! \brief Enables a peripheral.
//!
//! \param ulPeripheral is the peripheral to enable.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_PDMA, \b SYSCTL_PERIPH_ISP, \b SYSCTL_PERIPH_TMR0,
//! \b SYSCTL_PERIPH_TMR1, \b SYSCTL_PERIPH_TMR2, \b SYSCTL_PERIPH_TMR3,
//! \b SYSCTL_PERIPH_I2C0, \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_SPI0,
//! \b SYSCTL_PERIPH_SPI1, \b SYSCTL_PERIPH_SPI2, \b SYSCTL_PERIPH_SPI3,
//! \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1, \b SYSCTL_PERIPH_UART2,
//! \b SYSCTL_PERIPH_PWM01, \b SYSCTL_PERIPH_PWM23, \b SYSCTL_PERIPH_PWM45,
//! \b SYSCTL_PERIPH_PWM67, \b SYSCTL_PERIPH_CAN0, \b SYSCTL_PERIPH_USBD,
//! \b SYSCTL_PERIPH_ADC, \b SYSCTL_PERIPH_I2S, \b SYSCTL_PERIPH_ACMP,
//! \b SYSCTL_PERIPH_PS2,\b SYSCTL_PERIPH_RTC, \b SYSCTL_PERIPH_FDIV,
//! \b SYSCTL_PERIPH_WDT.
//!
//! \note None.
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
    SysCtlKeyAddrUnlock();
    xHWREG(g_pulAXBCLKRegs[SYSCTL_PERIPH_INDEX_E(ulPeripheral)]) |=
        SYSCTL_PERIPH_MASK_E(ulPeripheral);
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief Disable a peripheral.
//!
//! \param ulPeripheral is the peripheral to Disable.
//!
//! Peripherals are disabled with this function.  Once disabled, they will not
//! operate or respond to register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_PDMA, \b SYSCTL_PERIPH_ISP,  \b SYSCTL_PERIPH_TMR0,
//! \b SYSCTL_PERIPH_TMR1, \b SYSCTL_PERIPH_TMR2, \b SYSCTL_PERIPH_TMR3,
//! \b SYSCTL_PERIPH_I2C0, \b SYSCTL_PERIPH_I2C1, \b SYSCTL_PERIPH_SPI0,
//! \b SYSCTL_PERIPH_SPI1, \b SYSCTL_PERIPH_SPI2, \b SYSCTL_PERIPH_SPI3,
//! \b SYSCTL_PERIPH_UART0,\b SYSCTL_PERIPH_UART1,\b SYSCTL_PERIPH_UART2,
//! \b SYSCTL_PERIPH_PWM01,\b SYSCTL_PERIPH_PWM23,\b SYSCTL_PERIPH_PWM45,
//! \b SYSCTL_PERIPH_PWM67,\b SYSCTL_PERIPH_CAN0, \b SYSCTL_PERIPH_USBD,
//! \b SYSCTL_PERIPH_ADC,  \b SYSCTL_PERIPH_I2S,  \b SYSCTL_PERIPH_ACMP,
//! \b SYSCTL_PERIPH_PS2,  \b SYSCTL_PERIPH_RTC,  \b SYSCTL_PERIPH_FDIV,
//! \b SYSCTL_PERIPH_WDT.
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
    // Enable this peripheral.
    //
    SysCtlKeyAddrUnlock();
    xHWREG(g_pulAXBCLKRegs[SYSCTL_PERIPH_INDEX_E(ulPeripheral)]) &=
        ~(SYSCTL_PERIPH_MASK_E(ulPeripheral));
    SysCtlKeyAddrLock();
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
//! until the processor returns to run mode.  The peripherals that are enabled
//! via SysCtlPeripheralDeepSleepEnable() continue to operate and can wake up
//! the processor (if automatic clock gating is enabled with
//! SysCtlPeripheralClockGating(), otherwise all peripherals continue to
//! operate).
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
//! \brief Set a peripheral clock source.
//!
//! \param ulPeripheralSrc is the peripheral clock source to set.
//!
//! Peripherals clock source are seted with this function.  At power-up, all 
//! Peripherals clock source are Peripherals clock source; they must be set in 
//! order to operate or respond to register reads/writes.
//!
//! The \e ulPeripheralSrc parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_WDG_S_EXT32K, \b SYSCTL_PERIPH_WDG_S_HCLK_2048, 
//! \b SYSCTL_PERIPH_WDG_S_INT10K, \b SYSCTL_PERIPH_ADC_S_EXT12M, 
//! \b SYSCTL_PERIPH_ADC_S_PLL, \b SYSCTL_PERIPH_ADC_S_INT22M, 
//! \b SYSCTL_PERIPH_TMR0_S_EXT12M, \b SYSCTL_PERIPH_TMR0_S_EXT32K, 
//! \b SYSCTL_PERIPH_TMR0_S_HCLK, \b SYSCTL_PERIPH_TMR0_S_EXTTRG, 
//! \b SYSCTL_PERIPH_TMR0_S_INT22M, \b SYSCTL_PERIPH_UART_S_EXT12M,
//! \b SYSCTL_PERIPH_TMR1_S_EXT12M, \b SYSCTL_PERIPH_TMR1_S_EXT32K, 
//! \b SYSCTL_PERIPH_TMR1_S_HCLK, \b SYSCTL_PERIPH_TMR1_S_EXTTRG, 
//! \b SYSCTL_PERIPH_TMR1_S_INT22M, \b SYSCTL_PERIPH_UART_S_PLL,
//! \b SYSCTL_PERIPH_TMR2_S_EXT12M, \b SYSCTL_PERIPH_TMR2_S_EXT32K, 
//! \b SYSCTL_PERIPH_TMR2_S_HCLK, \b SYSCTL_PERIPH_TMR2_S_EXTTRG, 
//! \b SYSCTL_PERIPH_TMR2_S_INT22M, \b SYSCTL_PERIPH_UART_S_INT22M,
//! \b SYSCTL_PERIPH_TMR3_S_EXT12M, \b SYSCTL_PERIPH_TMR3_S_EXT32K, 
//! \b SYSCTL_PERIPH_TMR3_S_HCLK, \b SYSCTL_PERIPH_TMR3_S_EXTTRG, 
//! \b SYSCTL_PERIPH_TMR3_S_INT22M, \b SYSCTL_PERIPH_CAN_S_EXT12M
//! \b SYSCTL_PERIPH_CAN_S_PLL, \b SYSCTL_PERIPH_CAN_S_INT22M, 
//! \b SYSCTL_PERIPH_PWM01_S_EXT12M, \b SYSCTL_PERIPH_PWM01_S_EXT32K, 
//! \b SYSCTL_PERIPH_PWM01_S_HCLK,\b SYSCTL_PERIPH_PWM01_S_INT22M, 
//! \b SYSCTL_PERIPH_PWM23_S_EXT12M,\b SYSCTL_PERIPH_PWM23_S_EXT32K,
//! \b SYSCTL_PERIPH_PWM23_S_HCLK,\b SYSCTL_PERIPH_PWM23_S_INT22M,
//! \b SYSCTL_PERIPH_I2S_S_EXT12M,\b SYSCTL_PERIPH_I2S_S_PLL,
//! \b SYSCTL_PERIPH_I2S_S_HCLK,\b SYSCTL_PERIPH_I2S_S_INT22M,
//! \b SYSCTL_PERIPH_FRQDIV_S_EXT12M,\b SYSCTL_PERIPH_FRQDIV_S_EXT32K,
//! \b SYSCTL_PERIPH_FRQDIV_S_HCLK,\b SYSCTL_PERIPH_FRQDIV_S_INT22M,
//! \b SYSCTL_PERIPH_PWM45_S_EXT12M,\b SYSCTL_PERIPH_PWM45_S_EXT32K,
//! \b SYSCTL_PERIPH_PWM45_S_HCLK,\b SYSCTL_PERIPH_PWM45_S_INT22M,
//! \b SYSCTL_PERIPH_PWM67_S_EXT12M,\b SYSCTL_PERIPH_PWM67_S_EXT32K,
//! \b SYSCTL_PERIPH_PWM67_S_HCLK,\b SYSCTL_PERIPH_PWM67_S_INT22M,
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
    xASSERT((ulPeripheralSrc==SYSCTL_PERIPH_WDG_S_EXT32K)||
            (ulPeripheralSrc==SYSCTL_PERIPH_WDG_S_HCLK_2048)||
            (ulPeripheralSrc==SYSCTL_PERIPH_WDG_S_INT10K)||
            (ulPeripheralSrc==SYSCTL_PERIPH_ADC_S_EXT12M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_ADC_S_PLL)||
            (ulPeripheralSrc==SYSCTL_PERIPH_ADC_S_INT22M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR0_S_EXT12M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR0_S_EXT32K)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR0_S_HCLK)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR0_S_EXTTRG)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR0_S_INT22M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR1_S_EXT12M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR1_S_EXT32K)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR1_S_HCLK)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR1_S_EXTTRG)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR1_S_INT22M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR2_S_EXT12M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR2_S_EXT32K)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR2_S_HCLK)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR2_S_EXTTRG)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR2_S_INT22M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR3_S_EXT12M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR3_S_EXT32K)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR3_S_HCLK)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR3_S_EXTTRG)||
            (ulPeripheralSrc==SYSCTL_PERIPH_TMR3_S_INT22M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_UART_S_EXT12M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_UART_S_PLL)||
            (ulPeripheralSrc==SYSCTL_PERIPH_UART_S_INT22M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_CAN_S_EXT12M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_CAN_S_PLL)||
            (ulPeripheralSrc==SYSCTL_PERIPH_CAN_S_INT22M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM01_S_EXT12M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM01_S_EXT32K)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM01_S_HCLK)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM01_S_INT22M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM23_S_EXT12M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM23_S_EXT32K)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM23_S_HCLK)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM23_S_INT22M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM45_S_EXT12M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM45_S_EXT32K)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM45_S_HCLK)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM45_S_INT22M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM67_S_EXT12M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM67_S_EXT32K)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM67_S_HCLK)||
            (ulPeripheralSrc==SYSCTL_PERIPH_PWM67_S_INT22M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_I2S_S_EXT12M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_I2S_S_PLL)||
            (ulPeripheralSrc==SYSCTL_PERIPH_I2S_S_HCLK)||
            (ulPeripheralSrc==SYSCTL_PERIPH_I2S_S_INT22M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_FRQDIV_S_EXT12M)||
            (ulPeripheralSrc==SYSCTL_PERIPH_FRQDIV_S_EXT32K)||
            (ulPeripheralSrc==SYSCTL_PERIPH_FRQDIV_S_HCLK)||
            (ulPeripheralSrc==SYSCTL_PERIPH_FRQDIV_S_INT22M)         
           );

    //
    // Set  this peripheral clock source
    //
    SysCtlKeyAddrUnlock();
    xHWREG(g_pulCLKSELRegs[SYSCTL_PERIPH_INDEX_CLK(ulPeripheralSrc)]) &=
        ~(SYSCTL_PERIPH_MASK_CLK(ulPeripheralSrc));
    xHWREG(g_pulCLKSELRegs[SYSCTL_PERIPH_INDEX_CLK(ulPeripheralSrc)]) |=
        SYSCTL_PERIPH_ENUM_CLK(ulPeripheralSrc);
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
//! \b SYSCTL_HLCK_S_EXT12M, \b SYSCTL_HLCK_S_EXT32K, 
//! \b SYSCTL_HLCK_S_PLL, \b SYSCTL_HLCK_S_INT10K, 
//! \b SYSCTL_HLCK_S_INT22M.
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
    //
    // Check the arguments.
    //
    xASSERT(((ulHclkSrcSel==SYSCTL_HLCK_S_EXT12M)?
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
    xHWREG(SYSCLK_CLKSEL0) |=ulHclkSrcSel;
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
//! \b SYSCTL_STCLK_S_EXT12M, \b SYSCTL_STCLK_S_EXT32K, 
//! \b SYSCTL_STCLK_S_EXT12M_2, \b SYSCTL_STCLK_S_HCLK_2, 
//! \b SYSCTL_STCLK_S_INT22M_2.
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
    // Enable HCLK clock source.
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
    xHWREG(GCR_REGLOCK) = 0x59;
    xHWREG(GCR_REGLOCK) = 0x16;
    xHWREG(GCR_REGLOCK) = 0x88;
    
    return xHWREG(GCR_REGLOCK)&0x01;
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
//! \b SYSCTL_RSTSRC_POR, \b SYSCTL_RSTSRC_PAD, \b SYSCTL_RSTSRC_WDG,
//! \b SYSCTL_RSTSRC_LVR, \b SYSCTL_RSTSRC_BOD, \b SYSCTL_RSTSRC_SYS, and
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
//! \b SYSCTL_RSTSRC_LVR, \b SYSCTL_RSTSRC_BOD, \b SYSCTL_RSTSRC_SYS, and
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
//    xASSERT((ulSrc == SYSCTL_RSTSRC_POR) ||
//           (ulSrc == SYSCTL_RSTSRC_PAD) ||
//           (ulSrc == SYSCTL_RSTSRC_WDG) ||
//           (ulSrc == SYSCTL_RSTSRC_LVR) ||
//           (ulSrc == SYSCTL_RSTSRC_BOD) ||
//           (ulSrc == SYSCTL_RSTSRC_SYS) ||
//           (ulSrc == SYSCTL_RSTSRC_CPU));
    //
    // Clear reset source from last operation.
    //
    
    xHWREG(GCR_RSTSRC) |= ulSrc;
}

//*****************************************************************************
//
//! \brief The function is used to Enable BOD function
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
        xHWREG(GCR_BODCR) &= GCR_BODCR_BOD_EN;
    }
    SysCtlKeyAddrLock();
}

//*****************************************************************************
//
//! \brief The function is used to Select BOD threshold voltage
//!
//! \param ulVoltage the volt will be set
//!
//! The function is used to Select BOD threshold voltage
//!
//! The \e ulVoltage parameter must be only one of the following values:
//! \b SYSCTL_BOD_2_2, \b SYSCTL_BOD_2_6, 
//! \b SYSCTL_BOD_3_8, \b SYSCTL_BOD_4_5. 
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
        xHWREG(GCR_BODCR) &= GCR_BODCR_LVR_EN;
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
//! The function is used to Enable BOD reset function or interrupt function
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
//! \brief The function is used to Set RC adjustment value
//!
//! \param ulAdjValue RC adjustment value 
//!
//! The function is used to Set RC adjustment value
//!
//! \return None.
//
//*****************************************************************************
void 
SysCtlRCAdjValueSet(unsigned long ulAdjValue)
{
    //
    // Set RC adjustment value.
    //
    SysCtlKeyAddrUnlock();
    xHWREG(GCR_RCADJ) = ulAdjValue;
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
//! \b SYSCTL_PERIPH_HCLK_D, \b SYSCTL_PERIPH_USB_D, 
//! \b SYSCTL_PERIPH_UART_D, \b SYSCTL_PERIPH_CAN_D, 
//! \b SYSCTL_PERIPH_ADC_D.
//!
//! The divider number is chosen with one of the following values:
//! divider number 1-256 for ADC , 1-16 for other peripheral
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
    xHWREG(SYSCLK_CLKDIV) &= ~(SYSCTL_PERIPH_MASK_DIV(ulConfig));
    xHWREG(SYSCLK_CLKDIV) |= (SYSCTL_PERIPH_ENUM_CLK(ulConfig)-1);
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
    xASSERT(u8Divider<=15);
    
    //
    // Enable BOD reset function or interrupt function.
    //
    if(bEnable)
    {
        xHWREG(SYSCLK_FRQDIV) &= ~SYSCLK_FRQDIV_FSEL_M;
        xHWREG(SYSCLK_FRQDIV) |= u8Divider;
        xHWREG(SYSCLK_FRQDIV) |= SYSCLK_FRQDIV_FDIV_EN;
        SysCtlPeripheralEnable(SYSCTL_PERIPH_FDIV);
        
    }
    else
    {
        xHWREG(SYSCLK_FRQDIV) &= ~SYSCLK_FRQDIV_FDIV_EN;
        SysCtlPeripheralDisable(SYSCTL_PERIPH_FDIV);
    }
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
    // Enable BOD reset function or interrupt function.
    //
    SysCtlKeyAddrUnlock();
    if(bEnable)
    {
        xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_PWR_DO_EN;
    }
    else
    {
        xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_PWR_DO_EN;
    }
    SysCtlKeyAddrLock();
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
    else if((xHWREG(SYSCLK_CLKSEL0) & SYSCLK_CLKSEL0_HCLK_M) ==                \
                                     SYSCLK_CLKSEL0_HCLK32K)     
    {
        ulFreqout = 32000;
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
            ulNO = (xHWREG(SYSCLK_PLLCON) & SYSCLK_PLLCON_OUT_DV_M) >>          \
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
    ulAHBDivider = (xHWREG(SYSCLK_CLKDIV) & SYSCLK_CLKDIV_HCLK_M) + 1 ;
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
//! \b SYSCTL_XTAL_4MHZ, \b SYSCTL_XTAL_5MHZ, 
//! \b SYSCTL_XTAL_6MHZ, \b SYSCTL_XTAL_7MHZ, ...
//! \b SYSCTL_XTAL_24MHZ, 
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
    //
    // Check the arguments .
    //
    //xASSERT((ulConfig & 0XFF)<=64);

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
        SysCtlDelay(100);  
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
        SysCtlDelay(100);
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
    // HLCK clock source is SYSCLK_CLKSEL0_HCLK12M
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
            
            SysCtlDelay(1000);
            
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
            SysCtlDelay(1000);
            
            if((ulConfig & SYSCLK_PWRCON_XTL12M_EN)!=0)
            {
                xHWREG(SYSCLK_PWRCON) &= ~SYSCLK_PWRCON_XTL12M_EN;
            }
        }
        SysCtlHClockSourceSet(SYSCTL_HLCK_S_PLL);
        SysCtlDelay(100);
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
        SysCtlDelay(100);
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
    // HLCK clock source is SYSCLK_CLKSEL0_HCLK12M
    //
    else 
    {
        //
        // Check the arguments .
        //
        xASSERT((ulConfig & SYSCLK_PWRCON_OSC22M_EN)==0);
        
        xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_OSC22M_EN;
        SysCtlHClockSourceSet(SYSCTL_HLCK_S_INT22M);
        SysCtlDelay(100);
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

