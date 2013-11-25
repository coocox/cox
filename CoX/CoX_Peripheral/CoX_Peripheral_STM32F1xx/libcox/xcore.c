//*****************************************************************************
//
//! \file xcore.c
//! \brief Instruction wrappers for special CPU instructions.
//! Driver for the NVIC Interrupt Controller.
//! Driver for the SysTick driver.
//! \version V2.2.1.0
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
#include "xhw_config.h"
#include "xhw_nvic.h"
#include "xdebug.h"
#include "xcore.h"

//*****************************************************************************
//
// This is a mapping between priority grouping encodings and the number of
// preemption priority bits.
//
//*****************************************************************************
static const unsigned long g_pulPriority[] =
{
    NVIC_APINT_PRIGROUP_0_8, NVIC_APINT_PRIGROUP_1_7, NVIC_APINT_PRIGROUP_2_6,
    NVIC_APINT_PRIGROUP_3_5, NVIC_APINT_PRIGROUP_4_4, NVIC_APINT_PRIGROUP_5_3,
    NVIC_APINT_PRIGROUP_6_2, NVIC_APINT_PRIGROUP_7_1
};

//*****************************************************************************
//
// This is a mapping between interrupt number and the register that contains
// the priority encoding for that interrupt.
//
//*****************************************************************************
static const unsigned long g_pulRegs[] =
{
    0, NVIC_SYS_PRI1, NVIC_SYS_PRI2, NVIC_SYS_PRI3, NVIC_PRI0, NVIC_PRI1,
    NVIC_PRI2, NVIC_PRI3, NVIC_PRI4, NVIC_PRI5, NVIC_PRI6, NVIC_PRI7,
    NVIC_PRI8, NVIC_PRI9, NVIC_PRI10, NVIC_PRI11, NVIC_PRI12, NVIC_PRI13,
    NVIC_PRI14, NVIC_PRI15, NVIC_PRI16, NVIC_PRI17, NVIC_PRI18
};

//Note: Commented by cedar 2013-5-27
//      To avoid the compiler warning: 
//      "Warning[Pe177]: function "IntDefaultHandler" was declared but never referenced"
#if 0
//*****************************************************************************
//
//! \internal
//! The default interrupt handler.
//!
//! This is the default interrupt handler for all interrupts.  It simply loops
//! forever so that the system state is preserved for observation by a
//! debugger.  Since interrupts should be disabled before unregistering the
//! corresponding handler, this should never be called.
//!
//! \return None.
//
//*****************************************************************************
static void
IntDefaultHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}
#endif 

//*****************************************************************************
//
// Wrapper function for the CPSID instruction.  Returns the state of PRIMASK
// on entry.
//
//*****************************************************************************
#if defined(gcc) || defined(__GNUC__)
unsigned long __attribute__((naked))
xCPUcpsid(void)
{
    unsigned long ulRet;

    //
    // Read PRIMASK and disable interrupts.
    //
    __asm("    mrs     r0, PRIMASK\n"
          "    cpsid   i\n"
          "    bx      lr\n"
          : "=r" (ulRet));

    //
    // The return is handled in the inline assembly, but the compiler will
    // still complain if there is not an explicit return here (despite the fact
    // that this does not result in any code being produced because of the
    // naked attribute).
    //
    return(ulRet);
}
#endif
#if defined(ewarm)
unsigned long
xCPUcpsid(void)
{
    //
    // Read PRIMASK and disable interrupts.
    //
    __asm("    mrs     r0, PRIMASK\n"
          "    cpsid   i\n");

    //
    // "Warning[Pe940]: missing return statement at end of non-void function"
    // is suppressed here to avoid putting a "bx lr" in the inline assembly
    // above and a superfluous return statement here.
    //
#pragma diag_suppress=Pe940
}
#pragma diag_default=Pe940
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
__asm unsigned long
xCPUcpsid(void)
{
    //
    // Read PRIMASK and disable interrupts.
    //
    mrs     r0, PRIMASK;
    cpsid   i;
    bx      lr
}
#endif

//*****************************************************************************
//
// Wrapper function returning the state of PRIMASK (indicating whether
// interrupts are enabled or disabled).
//
//*****************************************************************************
#if defined(gcc) || defined(__GNUC__)
unsigned long __attribute__((naked))
xCPUprimask(void)
{
    unsigned long ulRet;

    //
    // Read PRIMASK and disable interrupts.
    //
    __asm("    mrs     r0, PRIMASK\n"
          "    bx      lr\n"
          : "=r" (ulRet));

    //
    // The return is handled in the inline assembly, but the compiler will
    // still complain if there is not an explicit return here (despite the fact
    // that this does not result in any code being produced because of the
    // naked attribute).
    //
    return(ulRet);
}
#endif
#if defined(ewarm)
unsigned long
xCPUprimask(void)
{
    //
    // Read PRIMASK and disable interrupts.
    //
    __asm("    mrs     r0, PRIMASK\n");

    //
    // "Warning[Pe940]: missing return statement at end of non-void function"
    // is suppressed here to avoid putting a "bx lr" in the inline assembly
    // above and a superfluous return statement here.
    //
#pragma diag_suppress=Pe940
}
#pragma diag_default=Pe940
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
__asm unsigned long
xCPUprimask(void)
{
    //
    // Read PRIMASK and disable interrupts.
    //
    mrs     r0, PRIMASK;
    bx      lr
}
#endif

//*****************************************************************************
//
// Wrapper function for the CPSIE instruction.  Returns the state of PRIMASK
// on entry.
//
//*****************************************************************************
#if defined(gcc) || defined(__GNUC__)
unsigned long __attribute__((naked))
xCPUcpsie(void)
{
    unsigned long ulRet;

    //
    // Read PRIMASK and enable interrupts.
    //
    __asm("    mrs     r0, PRIMASK\n"
          "    cpsie   i\n"
          "    bx      lr\n"
          : "=r" (ulRet));

    //
    // The return is handled in the inline assembly, but the compiler will
    // still complain if there is not an explicit return here (despite the fact
    // that this does not result in any code being produced because of the
    // naked attribute).
    //
    return(ulRet);
}
#endif
#if defined(ewarm)
unsigned long
xCPUcpsie(void)
{
    //
    // Read PRIMASK and enable interrupts.
    //
    __asm("    mrs     r0, PRIMASK\n"
          "    cpsie   i\n");

    //
    // "Warning[Pe940]: missing return statement at end of non-void function"
    // is suppressed here to avoid putting a "bx lr" in the inline assembly
    // above and a superfluous return statement here.
    //
#pragma diag_suppress=Pe940
}
#pragma diag_default=Pe940
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
__asm unsigned long
xCPUcpsie(void)
{
    //
    // Read PRIMASK and enable interrupts.
    //
    mrs     r0, PRIMASK;
    cpsie   i;
    bx      lr
}
#endif

//*****************************************************************************
//
// Wrapper function for the WFI instruction.
//
//*****************************************************************************
#if defined(gcc) || defined(__GNUC__)
void __attribute__((naked))
xCPUwfi(void)
{
    //
    // Wait for the next interrupt.
    //
    __asm("    wfi\n"
          "    bx      lr\n");
}
#endif
#if defined(ewarm)
void
xCPUwfi(void)
{
    //
    // Wait for the next interrupt.
    //
    __asm("    wfi\n");
}
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
__asm void
xCPUwfi(void)
{
    //
    // Wait for the next interrupt.
    //
    wfi;
    bx      lr
}
#endif

//*****************************************************************************
//
// Wrapper function for the WFE instruction.
//
//*****************************************************************************
#if defined(gcc) || defined(__GNUC__)
void __attribute__((naked))
xCPUwfe(void)
{
    //
    // Wait for the next interrupt.
    //
    __asm("    wfe\n"
          "    bx      lr\n");
}
#endif
#if defined(ewarm)
void
xCPUwfe(void)
{
    //
    // Wait for the next interrupt.
    //
    __asm("    wfe\n");
}
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
__asm void
xCPUwfe(void)
{
    //
    // Wait for the next interrupt.
    //
    wfe;
    bx      lr
}
#endif

//*****************************************************************************
//
// Wrapper function for writing the BASEPRI register.
//
//*****************************************************************************
#if defined(gcc) || defined(__GNUC__)
void __attribute__((naked))
xCPUbasepriSet(unsigned long ulNewBasepri)
{

    //
    // Set the BASEPRI register
    //
    __asm("    msr     BASEPRI, r0\n"
          "    bx      lr\n");
}
#endif
#if defined(ewarm)
void
xCPUbasepriSet(unsigned long ulNewBasepri)
{
    //
    // Set the BASEPRI register
    //
    __asm("    msr     BASEPRI, r0\n");
}
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
__asm void
xCPUbasepriSet(unsigned long ulNewBasepri)
{
    //
    // Set the BASEPRI register
    //
    msr     BASEPRI, r0;
    bx      lr
}
#endif

//*****************************************************************************
//
// Wrapper function for reading the BASEPRI register.
//
//*****************************************************************************
#if defined(gcc) || defined(__GNUC__)
unsigned long __attribute__((naked))
xCPUbasepriGet(void)
{
    unsigned long ulRet;

    //
    // Read BASEPRI
    //
    __asm("    mrs     r0, BASEPRI\n"
          "    bx      lr\n"
          : "=r" (ulRet));

    //
    // The return is handled in the inline assembly, but the compiler will
    // still complain if there is not an explicit return here (despite the fact
    // that this does not result in any code being produced because of the
    // naked attribute).
    //
    return(ulRet);
}
#endif
#if defined(ewarm)
unsigned long
xCPUbasepriGet(void)
{
    //
    // Read BASEPRI
    //
    __asm("    mrs     r0, BASEPRI\n");

    //
    // "Warning[Pe940]: missing return statement at end of non-void function"
    // is suppressed here to avoid putting a "bx lr" in the inline assembly
    // above and a superfluous return statement here.
    //
#pragma diag_suppress=Pe940
}
#pragma diag_default=Pe940
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
__asm unsigned long
xCPUbasepriGet(void)
{
    //
    // Read BASEPRI
    //
    mrs     r0, BASEPRI;
    bx      lr
}
#endif

//*****************************************************************************
//
// Wrapper function for writing the PSP register.
//
//*****************************************************************************
#if defined(gcc) || defined(__GNUC__)
void __attribute__((naked))
xCPUpspSet(unsigned long ulNewPspStack)
{

    //
    // Set the psp register
    //
    __asm("    msr     psp, r0\n"
          "    bx      lr\n");
}
#endif
#if defined(ewarm)
void
xCPUpspSet(unsigned long ulNewPspStack)
{
    //
    // Set the psp register
    //
    __asm("    msr     psp, r0\n");
}
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
__asm void
xCPUpspSet(unsigned long ulNewPspStack)
{
    //
    // Set the psp register
    //
    msr psp, r0
    bx lr
}
#endif

//*****************************************************************************
//
// Wrapper function for reading the psp register.
//
//*****************************************************************************
#if defined(gcc) || defined(__GNUC__)
unsigned long __attribute__((naked))
xCPUpspGet(void)
{
    unsigned long ulRet;

    //
    // Read psp
    //
    __asm("    mrs     r0, psp\n"
          "    bx      lr\n"
          : "=r" (ulRet));

    //
    // The return is handled in the inline assembly, but the compiler will
    // still complain if there is not an explicit return here (despite the fact
    // that this does not result in any code being produced because of the
    // naked attribute).
    //
    return(ulRet);
}
#endif
#if defined(ewarm)
unsigned long
xCPUpspGet(void)
{
    //
    // Read psp
    //
    __asm("    mrs     r0, psp\n");

    //
    // "Warning[Pe940]: missing return statement at end of non-void function"
    // is suppressed here to avoid putting a "bx lr" in the inline assembly
    // above and a superfluous return statement here.
    //
#pragma diag_suppress=Pe940
}
#pragma diag_default=Pe940
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
__asm unsigned long
xCPUpspGet(void)
{
    //
    // Read psp
    //
    mrs     r0, psp;
    bx      lr
}
#endif
#if defined(ccs)
unsigned long
xCPUpspGet(void)
{
    //
    // Read psp
    //
    __asm("    mrs     r0, psp\n"
          "    bx      lr\n");

    //
    // The following keeps the compiler happy, because it wants to see a
    // return value from this function.  It will generate code to return
    // a zero.  However, the real return is the "bx lr" above, so the
    // return(0) is never executed and the function returns with the value
    // you expect in R0.
    //
    return(0);
}
#endif

//*****************************************************************************
//
// Wrapper function for writing the msp register.
//
//*****************************************************************************
#if defined(gcc) || defined(__GNUC__)
void __attribute__((naked))
xCPUmspSet(unsigned long ulNewmspStack)
{

    //
    // Set the msp register
    //
    __asm("    msr     msp, r0\n"
          "    bx      lr\n");
}
#endif
#if defined(ewarm)
void
xCPUmspSet(unsigned long ulNewmspStack)
{
    //
    // Set the msp register
    //
    __asm("    msr     msp, r0\n");
}
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
__asm void
xCPUmspSet(unsigned long ulNewmspStack)
{
    //
    // Set the msp register
    //
    msr msp, r0
    bx lr
}
#endif
#if defined(ccs)
void
xCPUmspSet(unsigned long ulNewmspStack)
{
    //
    // Set the msp register
    //
    __asm("    msr     msp, r0\n");
}
#endif


//*****************************************************************************
//
// Wrapper function for reading the msp register.
//
//*****************************************************************************
#if defined(gcc) || defined(__GNUC__)
unsigned long __attribute__((naked))
xCPUmspGet(void)
{
    unsigned long ulRet;

    //
    // Read msp
    //
    __asm("    mrs     r0, msp\n"
          "    bx      lr\n"
          : "=r" (ulRet));

    //
    // The return is handled in the inline assembly, but the compiler will
    // still complain if there is not an explicit return here (despite the fact
    // that this does not result in any code being produced because of the
    // naked attribute).
    //
    return(ulRet);
}
#endif
#if defined(ewarm)
unsigned long
xCPUmspGet(void)
{
    //
    // Read msp
    //
    __asm("    mrs     r0, msp\n");

    //
    // "Warning[Pe940]: missing return statement at end of non-void function"
    // is suppressed here to avoid putting a "bx lr" in the inline assembly
    // above and a superfluous return statement here.
    //
#pragma diag_suppress=Pe940
}
#pragma diag_default=Pe940
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
__asm unsigned long
xCPUmspGet(void)
{
    //
    // Read msp
    //
    mrs     r0, msp;
    bx      lr
}
#endif
#if defined(ccs)
unsigned long
xCPUmspGet(void)
{
    //
    // Read msp
    //
    __asm("    mrs     r0, msp\n"
          "    bx      lr\n");

    //
    // The following keeps the compiler happy, because it wants to see a
    // return value from this function.  It will generate code to return
    // a zero.  However, the real return is the "bx lr" above, so the
    // return(0) is never executed and the function returns with the value
    // you expect in R0.
    //
    return(0);
}
#endif

//*****************************************************************************
//
//! Enables the processor interrupt.
//!
//! Allows the processor to respond to interrupts.  This does not affect the
//! set of interrupts enabled in the interrupt controller; it just gates the
//! single interrupt from the controller to the processor.
//!
//! \return Returns \b true if interrupts were disabled when the function was
//! called or \b false if they were initially enabled.
//
//*****************************************************************************
xtBoolean
xIntMasterEnable(void)
{
    //
    // Enable processor interrupts.
    //
    return(xCPUcpsie());
}

//*****************************************************************************
//
//! Disables the processor interrupt.
//!
//! Prevents the processor from receiving interrupts.  This does not affect the
//! set of interrupts enabled in the interrupt controller; it just gates the
//! single interrupt from the controller to the processor.
//!
//! \return Returns \b true if interrupts were already disabled when the
//! function was called or \b false if they were initially enabled.
//
//*****************************************************************************
xtBoolean
xIntMasterDisable(void)
{
    //
    // Disable processor interrupts.
    //
    return(xCPUcpsid());
}

//*****************************************************************************
//
//! Sets the priority grouping of the interrupt controller.
//!
//! \param ulBits specifies the number of bits of preemptable priority.
//!
//! This function specifies the split between preemptable priority levels and
//! subpriority levels in the interrupt priority specification.  The range of
//! the grouping values are dependent upon the hardware implementation; on
//! the Stellaris family, three bits are available for hardware interrupt
//! prioritization and therefore priority grouping values of three through
//! seven have the same effect.
//!
//! \return None.
//
//*****************************************************************************
void
xIntPriorityGroupingSet(unsigned long ulBits)
{
    //
    // Check the arguments.
    //
    xASSERT(ulBits < NUM_PRIORITY);

    //
    // Set the priority grouping.
    //
    xHWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | g_pulPriority[ulBits];
}

//*****************************************************************************
//
//! Gets the priority grouping of the interrupt controller.
//!
//! This function returns the split between preemptable priority levels and
//! subpriority levels in the interrupt priority specification.
//!
//! \return The number of bits of preemptable priority.
//
//*****************************************************************************
unsigned long
xIntPriorityGroupingGet(void)
{
    unsigned long ulLoop, ulValue;

    //
    // Read the priority grouping.
    //
    ulValue = xHWREG(NVIC_APINT) & NVIC_APINT_PRIGROUP_M;

    //
    // Loop through the priority grouping values.
    //
    for(ulLoop = 0; ulLoop < NUM_PRIORITY; ulLoop++)
    {
        //
        // Stop looping if this value matches.
        //
        if(ulValue == g_pulPriority[ulLoop])
        {
            break;
        }
    }

    //
    // Return the number of priority bits.
    //
    return(ulLoop);
}

//*****************************************************************************
//
//! Sets the priority of an interrupt.
//!
//! \param ulInterrupt specifies the interrupt in question.
//! \param ucPriority specifies the priority of the interrupt.
//!
//! This function is used to set the priority of an interrupt.  When multiple
//! interrupts are asserted simultaneously, the ones with the highest priority
//! are processed before the lower priority interrupts.  Smaller numbers
//! correspond to higher interrupt priorities; priority 0 is the highest
//! interrupt priority.
//!
//! The hardware priority mechanism will only look at the upper N bits of the
//! priority level (where N is 3 for the Stellaris family), so any
//! prioritization must be performed in those bits.  The remaining bits can be
//! used to sub-prioritize the interrupt sources, and may be used by the
//! hardware priority mechanism on a future part.  This arrangement allows
//! priorities to migrate to different NVIC implementations without changing
//! the gross prioritization of the interrupts.
//!
//! \return None.
//
//*****************************************************************************
void
xIntPrioritySet(unsigned long ulInterrupt, unsigned char ucPriority)
{
    unsigned long ulTemp;

    //
    // Check the arguments.
    //
    xASSERT(((ulInterrupt & 0xFF) == 0) || (((ulInterrupt & 0xFF) >= 4) && 
            ((ulInterrupt & 0xFF) < NUM_INTERRUPTS)));

    if((ulInterrupt & 0xFF) != 0)
    {
        //
        // Set the interrupt priority.
        //
        ulTemp = xHWREG(g_pulRegs[(ulInterrupt & 0xFF) >> 2]);
        ulTemp &= ~(0xFF << (8 * ((ulInterrupt & 0xFF) & 3)));
        ulTemp |= ucPriority << (8 * ((ulInterrupt & 0xFF) & 3));
        xHWREG(g_pulRegs[(ulInterrupt & 0xFF) >> 2]) = ulTemp;
    }
    else if(ulInterrupt == INT_TIM1)
    {
        ulTemp = ucPriority | (ucPriority << 8) | (ucPriority << 16) | 
                 (ucPriority << 24);
        xHWREG(NVIC_PRI6) = ulTemp;
    }
    else if(ulInterrupt == INT_GPIO)
    {
        ulTemp = xHWREG(NVIC_PRI1);
        ulTemp &= 0x0000FFFF;
        ulTemp = (ucPriority << 16) | (ucPriority << 24);
        xHWREG(NVIC_PRI1) = ulTemp;
        
        ulTemp = xHWREG(NVIC_PRI2);
        ulTemp &= 0xFF000000;
        ulTemp = (ucPriority << 8) | (ucPriority << 16) | (ucPriority << 24);
        xHWREG(NVIC_PRI2) = ulTemp;

        ulTemp = xHWREG(NVIC_PRI5);
        ulTemp &= 0x00FFFFFF;
        ulTemp = (ucPriority << 24);
        xHWREG(NVIC_PRI5) = ulTemp;

        ulTemp = xHWREG(NVIC_PRI10);
        ulTemp &= 0xFFFFFF00;
        ulTemp = ucPriority;
        xHWREG(NVIC_PRI10) = ulTemp;
    }
    else if(ulInterrupt == INT_DMA1)
    {
        ulTemp = xHWREG(NVIC_PRI2);
        ulTemp &= 0x00FFFFFF;
        ulTemp = (ucPriority << 24);
        xHWREG(NVIC_PRI2) = ulTemp;
        
        ulTemp = ucPriority | (ucPriority << 8) | (ucPriority << 16) | 
                 (ucPriority << 24);
        xHWREG(NVIC_PRI3) = ulTemp;
        
        ulTemp = xHWREG(NVIC_PRI4);
        ulTemp &= 0xFFFF0000;
        ulTemp = ucPriority | (ucPriority << 8);
        xHWREG(NVIC_PRI4) = ulTemp;
    }
    else if(ulInterrupt == INT_DMA2)
    {        
        ulTemp = ucPriority | (ucPriority << 8) | (ucPriority << 16) | 
                 (ucPriority << 24);
        xHWREG(NVIC_PRI14) = ulTemp;
        
        ulTemp = xHWREG(NVIC_PRI15);
        ulTemp &= 0xFFFFFF00;
        ulTemp = ucPriority;
        xHWREG(NVIC_PRI15) = ulTemp;
    }
}

//*****************************************************************************
//
//! Gets the priority of an interrupt.
//!
//! \param ulInterrupt specifies the interrupt in question.
//!
//! This function gets the priority of an interrupt.  See XIntPrioritySet() for
//! a definition of the priority value.
//!
//! \return Returns the interrupt priority, or -1 if an invalid interrupt was
//! specified.
//
//*****************************************************************************
long
xIntPriorityGet(unsigned long ulInterrupt)
{
    //
    // Check the arguments.
    //
    xASSERT(((ulInterrupt & 0xFF) == 0) || (((ulInterrupt & 0xFF) >= 4) && 
            ((ulInterrupt & 0xFF) < NUM_INTERRUPTS)));

    if((ulInterrupt & 0xFF) != 0)
    {
        //
        // Return the interrupt priority.
        //
        return((xHWREG(g_pulRegs[ulInterrupt >> 2]) >> (8 * (ulInterrupt & 3))) &
               0xFF);
    }
    else if(ulInterrupt == INT_TIM1)
    {
        return ((xHWREG(NVIC_PRI6) >> 16) &0xFF);
    }
    else if(ulInterrupt == INT_GPIO)
    {
        return ((xHWREG(NVIC_PRI1) >> 16) &0xFF);
    }
    else if(ulInterrupt == INT_DMA1)
    {
        return ((xHWREG(NVIC_PRI3)) &0xFF);
    }
    else if(ulInterrupt == INT_DMA2)
    {
        return ((xHWREG(NVIC_PRI14)) &0xFF);
    }
    return -1;
}

//*****************************************************************************
//
//! Enables an interrupt.
//!
//! \param ulInterrupt specifies the interrupt to be enabled.
//!
//! The specified interrupt is enabled in the interrupt controller.  Other
//! enables for the interrupt (such as at the peripheral level) are unaffected
//! by this function.
//!
//! \return None.
//
//*****************************************************************************
void
xIntEnable(unsigned long ulInterrupt)
{
    //
    // Check the arguments.
    //
    xASSERT((ulInterrupt & 0xFF) < NUM_INTERRUPTS);

    //
    // Determine the interrupt to enable.
    //
    if(ulInterrupt == FAULT_MPU)
    {
        //
        // Enable the MemManage interrupt.
        //
        xHWREG(NVIC_SYS_HND_CTRL) |= NVIC_SYS_HND_CTRL_MEM;
    }
    else if(ulInterrupt == FAULT_BUS)
    {
        //
        // Enable the bus fault interrupt.
        //
        xHWREG(NVIC_SYS_HND_CTRL) |= NVIC_SYS_HND_CTRL_BUS;
    }
    else if(ulInterrupt == FAULT_USAGE)
    {
        //
        // Enable the usage fault interrupt.
        //
        xHWREG(NVIC_SYS_HND_CTRL) |= NVIC_SYS_HND_CTRL_USAGE;
    }
    else if(ulInterrupt == FAULT_SYSTICK)
    {
        //
        // Enable the System Tick interrupt.
        //
        xHWREG(NVIC_ST_CTRL) |= NVIC_ST_CTRL_INTEN;
    }
    else if(((ulInterrupt & 0xFF) >= 16) && 
            ((ulInterrupt & 0xFF) < xNUM_INTERRUPTS))
    {
        //
        // Enable the general interrupt.
        //
        xHWREG(NVIC_EN0 + (((ulInterrupt & 0xFF)-16)/32)*4) 
        = 1 << (((ulInterrupt & 0xFF)-16)%32);
    }
    else if((((ulInterrupt >> 8) & 0xFF) >= 16) &&
            (((ulInterrupt >> 8) & 0xFF) <= xNUM_INTERRUPTS))
    {
        //
        // Enable the general interrupt.
        //
        xHWREG(NVIC_EN0 + ((((ulInterrupt >> 8) & 0xFF)-16)/32)*4) 
        = 1 << ((((ulInterrupt >> 8) & 0xFF)-16)%32);
    }
    else if(ulInterrupt == INT_TIM1)
    {
        xHWREG(NVIC_EN0) = 1 << (INT_TIM1BRK - 16);
        xHWREG(NVIC_EN0) = 1 << (INT_TIM1UP - 16);
        xHWREG(NVIC_EN0) = 1 << (INT_TIM1TRGCOM - 16);
        xHWREG(NVIC_EN0) = 1 << (INT_TIM1CC - 16);
    }
    else if(ulInterrupt == INT_GPIO)
    {
        xHWREG(NVIC_EN0) = 1 << (INT_EXTI0 - 16);
        xHWREG(NVIC_EN0) = 1 << (INT_EXTI1 - 16);
        xHWREG(NVIC_EN0) = 1 << (INT_EXTI2 - 16);
        xHWREG(NVIC_EN0) = 1 << (INT_EXTI3 - 16);
        xHWREG(NVIC_EN0) = 1 << (INT_EXTI4 - 16);
        xHWREG(NVIC_EN0) = 1 << (INT_EXTI95 - 16);
        xHWREG(NVIC_EN1) = 1 << (INT_EXTI1510 - 48);
    }
    else if(ulInterrupt == INT_DMA1)
    {
        xHWREG(NVIC_EN0) = 1 << (INT_DMA1C1 - 16);
        xHWREG(NVIC_EN0) = 1 << (INT_DMA1C2 - 16);
        xHWREG(NVIC_EN0) = 1 << (INT_DMA1C3 - 16);
        xHWREG(NVIC_EN0) = 1 << (INT_DMA1C4 - 16);
        xHWREG(NVIC_EN0) = 1 << (INT_DMA1C5 - 16);
        xHWREG(NVIC_EN0) = 1 << (INT_DMA1C6 - 16);
        xHWREG(NVIC_EN0) = 1 << (INT_DMA1C7 - 16);
    }
    else if(ulInterrupt == INT_DMA2)
    {
        xHWREG(NVIC_EN1) = 1 << (INT_DMA2C1 - 48);
        xHWREG(NVIC_EN1) = 1 << (INT_DMA2C2 - 48);
        xHWREG(NVIC_EN1) = 1 << (INT_DMA2C3 - 48);
        xHWREG(NVIC_EN1) = 1 << (INT_DMA2C4 - 48);
        xHWREG(NVIC_EN1) = 1 << (INT_DMA2C5 - 48);
    }
}

//*****************************************************************************
//
//! Disables an interrupt.
//!
//! \param ulInterrupt specifies the interrupt to be disabled.
//!
//! The specified interrupt is disabled in the interrupt controller.  Other
//! enables for the interrupt (such as at the peripheral level) are unaffected
//! by this function.
//!
//! \return None.
//
//*****************************************************************************
void
xIntDisable(unsigned long ulInterrupt)
{
    //
    // Check the arguments.
    //
    xASSERT((ulInterrupt & 0xFF) < NUM_INTERRUPTS);

    //
    // Determine the interrupt to disable.
    //
    if(ulInterrupt == FAULT_MPU)
    {
        //
        // Disable the MemManage interrupt.
        //
        xHWREG(NVIC_SYS_HND_CTRL) &= ~(NVIC_SYS_HND_CTRL_MEM);
    }
    else if(ulInterrupt == FAULT_BUS)
    {
        //
        // Disable the bus fault interrupt.
        //
        xHWREG(NVIC_SYS_HND_CTRL) &= ~(NVIC_SYS_HND_CTRL_BUS);
    }
    else if(ulInterrupt == FAULT_USAGE)
    {
        //
        // Disable the usage fault interrupt.
        //
        xHWREG(NVIC_SYS_HND_CTRL) &= ~(NVIC_SYS_HND_CTRL_USAGE);
    }
    else if(ulInterrupt == FAULT_SYSTICK)
    {
        //
        // Disable the System Tick interrupt.
        //
        xHWREG(NVIC_ST_CTRL) &= ~(NVIC_ST_CTRL_INTEN);
    }
    else if(((ulInterrupt & 0xFF) >= 16) && 
            ((ulInterrupt & 0xFF) < xNUM_INTERRUPTS))
    {
        //
        // Enable the general interrupt.
        //
        xHWREG(NVIC_DIS0 + ((ulInterrupt & 0xFF)/32)*4) 
        = 1 << ((ulInterrupt & 0xFF)%32);
    }
    else if((((ulInterrupt >> 8) & 0xFF) >= 16) &&
            (((ulInterrupt >> 8) & 0xFF) <= xNUM_INTERRUPTS))
    {
        //
        // Enable the general interrupt.
        //
        xHWREG(NVIC_DIS0 + (((ulInterrupt >> 8) & 0xFF)/32)*4) 
        = 1 << (((ulInterrupt >> 8) & 0xFF)%32);
    }
    else if(ulInterrupt == INT_TIM1)
    {
        xHWREG(NVIC_DIS0) = 1 << (INT_TIM1BRK - 16);
        xHWREG(NVIC_DIS0) = 1 << (INT_TIM1UP - 16);
        xHWREG(NVIC_DIS0) = 1 << (INT_TIM1TRGCOM - 16);
        xHWREG(NVIC_DIS0) = 1 << (INT_TIM1CC - 16);
    }
    else if(ulInterrupt == INT_GPIO)
    {
        xHWREG(NVIC_DIS0) = 1 << (INT_EXTI0 - 16);
        xHWREG(NVIC_DIS0) = 1 << (INT_EXTI1 - 16);
        xHWREG(NVIC_DIS0) = 1 << (INT_EXTI2 - 16);
        xHWREG(NVIC_DIS0) = 1 << (INT_EXTI3 - 16);
        xHWREG(NVIC_DIS0) = 1 << (INT_EXTI4 - 16);
        xHWREG(NVIC_DIS0) = 1 << (INT_EXTI95 - 16);
        xHWREG(NVIC_DIS1) = 1 << (INT_EXTI1510 - 48);
    }
    else if(ulInterrupt == INT_DMA1)
    {
        xHWREG(NVIC_DIS0) = 1 << (INT_DMA1C1 - 16);
        xHWREG(NVIC_DIS0) = 1 << (INT_DMA1C2 - 16);
        xHWREG(NVIC_DIS0) = 1 << (INT_DMA1C3 - 16);
        xHWREG(NVIC_DIS0) = 1 << (INT_DMA1C4 - 16);
        xHWREG(NVIC_DIS0) = 1 << (INT_DMA1C5 - 16);
        xHWREG(NVIC_DIS0) = 1 << (INT_DMA1C6 - 16);
        xHWREG(NVIC_DIS0) = 1 << (INT_DMA1C7 - 16);
    }
    else if(ulInterrupt == INT_DMA2)
    {
        xHWREG(NVIC_DIS1) = 1 << (INT_DMA2C1 - 48);
        xHWREG(NVIC_DIS1) = 1 << (INT_DMA2C2 - 48);
        xHWREG(NVIC_DIS1) = 1 << (INT_DMA2C3 - 48);
        xHWREG(NVIC_DIS1) = 1 << (INT_DMA2C4 - 48);
        xHWREG(NVIC_DIS1) = 1 << (INT_DMA2C5 - 48);
    }
}

//*****************************************************************************
//
//! Pends an interrupt.
//!
//! \param ulInterrupt specifies the interrupt to be pended.
//!
//! The specified interrupt is pended in the interrupt controller.  This will
//! cause the interrupt controller to execute the corresponding interrupt
//! handler at the next available time, based on the current interrupt state
//! priorities.  For example, if called by a higher priority interrupt handler,
//! the specified interrupt handler will not be called until after the current
//! interrupt handler has completed execution.  The interrupt must have been
//! enabled for it to be called.
//!
//! \return None.
//
//*****************************************************************************
void
xIntPendSet(unsigned long ulInterrupt)
{
    //
    // Check the arguments.
    //
    xASSERT((ulInterrupt & 0xFF) < NUM_INTERRUPTS);

    //
    // Determine the interrupt to pend.
    //
    if(ulInterrupt == FAULT_NMI)
    {
        //
        // Pend the NMI interrupt.
        //
        xHWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_NMI_SET;
    }
    else if(ulInterrupt == FAULT_PENDSV)
    {
        //
        // Pend the PendSV interrupt.
        //
        xHWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_PEND_SV;
    }
    else if(ulInterrupt == FAULT_SYSTICK)
    {
        //
        // Pend the SysTick interrupt.
        //
        xHWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_PENDSTSET;
    }
    else if(((ulInterrupt & 0xFF) >= 16) && 
            ((ulInterrupt & 0xFF) < xNUM_INTERRUPTS))
    {
        //
        // Enable the general interrupt.
        //
        xHWREG(NVIC_PEND0 + ((ulInterrupt & 0xFF)/32)*4) 
        = 1 << ((ulInterrupt & 0xFF)%32);
    }
    else if((((ulInterrupt >> 8) & 0xFF) >= 16) &&
            (((ulInterrupt >> 8) & 0xFF) <= xNUM_INTERRUPTS))
    {
        //
        // Enable the general interrupt.
        //
        xHWREG(NVIC_PEND0 + (((ulInterrupt >> 8) & 0xFF)/32)*4) 
        = 1 << (((ulInterrupt >> 8) & 0xFF)%32);
    }
    else if(ulInterrupt == INT_TIM1)
    {
        xHWREG(NVIC_PEND0) = 1 << (INT_TIM1BRK - 16);
        xHWREG(NVIC_PEND0) = 1 << (INT_TIM1UP - 16);
        xHWREG(NVIC_PEND0) = 1 << (INT_TIM1TRGCOM - 16);
        xHWREG(NVIC_PEND0) = 1 << (INT_TIM1CC - 16);
    }
    else if(ulInterrupt == INT_GPIO)
    {
        xHWREG(NVIC_PEND0) = 1 << (INT_EXTI0 - 16);
        xHWREG(NVIC_PEND0) = 1 << (INT_EXTI1 - 16);
        xHWREG(NVIC_PEND0) = 1 << (INT_EXTI2 - 16);
        xHWREG(NVIC_PEND0) = 1 << (INT_EXTI3 - 16);
        xHWREG(NVIC_PEND0) = 1 << (INT_EXTI4 - 16);
        xHWREG(NVIC_PEND0) = 1 << (INT_EXTI95 - 16);
        xHWREG(NVIC_PEND1) = 1 << (INT_EXTI1510 - 48);
    }
    else if(ulInterrupt == INT_DMA1)
    {
        xHWREG(NVIC_PEND0) = 1 << (INT_DMA1C1 - 16);
        xHWREG(NVIC_PEND0) = 1 << (INT_DMA1C2 - 16);
        xHWREG(NVIC_PEND0) = 1 << (INT_DMA1C3 - 16);
        xHWREG(NVIC_PEND0) = 1 << (INT_DMA1C4 - 16);
        xHWREG(NVIC_PEND0) = 1 << (INT_DMA1C5 - 16);
        xHWREG(NVIC_PEND0) = 1 << (INT_DMA1C6 - 16);
        xHWREG(NVIC_PEND0) = 1 << (INT_DMA1C7 - 16);
    }
    else if(ulInterrupt == INT_DMA2)
    {
        xHWREG(NVIC_PEND1) = 1 << (INT_DMA2C1 - 48);
        xHWREG(NVIC_PEND1) = 1 << (INT_DMA2C2 - 48);
        xHWREG(NVIC_PEND1) = 1 << (INT_DMA2C3 - 48);
        xHWREG(NVIC_PEND1) = 1 << (INT_DMA2C4 - 48);
        xHWREG(NVIC_PEND1) = 1 << (INT_DMA2C5 - 48);
    }
}

//*****************************************************************************
//
//! Unpends an interrupt.
//!
//! \param ulInterrupt specifies the interrupt to be unpended.
//!
//! The specified interrupt is unpended in the interrupt controller.  This will
//! cause any previously generated interrupts that have not been handled yet
//! (due to higher priority interrupts or the interrupt no having been enabled
//! yet) to be discarded.
//!
//! \return None.
//
//*****************************************************************************
void
xIntPendClear(unsigned long ulInterrupt)
{
    //
    // Check the arguments.
    //
    xASSERT((ulInterrupt & 0xFF) < NUM_INTERRUPTS);

    //
    // Determine the interrupt to unpend.
    //
    if(ulInterrupt == FAULT_PENDSV)
    {
        //
        // Unpend the PendSV interrupt.
        //
        xHWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_UNPEND_SV;
    }
    else if(ulInterrupt == FAULT_SYSTICK)
    {
        //
        // Unpend the SysTick interrupt.
        //
        xHWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_PENDSTCLR;
    }
    else if(((ulInterrupt & 0xFF) >= 16) && 
            ((ulInterrupt & 0xFF) < xNUM_INTERRUPTS))
    {
        //
        // Enable the general interrupt.
        //
        xHWREG(NVIC_UNPEND0 + ((ulInterrupt & 0xFF)/32)*4) 
        = 1 << ((ulInterrupt & 0xFF)%32);
    }
    else if((((ulInterrupt >> 8) & 0xFF) >= 16) &&
            (((ulInterrupt >> 8) & 0xFF) <= xNUM_INTERRUPTS))
    {
        //
        // Enable the general interrupt.
        //
        xHWREG(NVIC_UNPEND0 + (((ulInterrupt >> 8) & 0xFF)/32)*4) 
        = 1 << (((ulInterrupt >> 8) & 0xFF)%32);
    }
    else if(ulInterrupt == INT_TIM1)
    {
        xHWREG(NVIC_UNPEND0) = 1 << (INT_TIM1BRK - 16);
        xHWREG(NVIC_UNPEND0) = 1 << (INT_TIM1UP - 16);
        xHWREG(NVIC_UNPEND0) = 1 << (INT_TIM1TRGCOM - 16);
        xHWREG(NVIC_UNPEND0) = 1 << (INT_TIM1CC - 16);
    }
    else if(ulInterrupt == INT_GPIO)
    {
        xHWREG(NVIC_UNPEND0) = 1 << (INT_EXTI0 - 16);
        xHWREG(NVIC_UNPEND0) = 1 << (INT_EXTI1 - 16);
        xHWREG(NVIC_UNPEND0) = 1 << (INT_EXTI2 - 16);
        xHWREG(NVIC_UNPEND0) = 1 << (INT_EXTI3 - 16);
        xHWREG(NVIC_UNPEND0) = 1 << (INT_EXTI4 - 16);
        xHWREG(NVIC_UNPEND0) = 1 << (INT_EXTI95 - 16);
        xHWREG(NVIC_UNPEND1) = 1 << (INT_EXTI1510 - 48);
    }
    else if(ulInterrupt == INT_DMA1)
    {
        xHWREG(NVIC_UNPEND0) = 1 << (INT_DMA1C1 - 16);
        xHWREG(NVIC_UNPEND0) = 1 << (INT_DMA1C2 - 16);
        xHWREG(NVIC_UNPEND0) = 1 << (INT_DMA1C3 - 16);
        xHWREG(NVIC_UNPEND0) = 1 << (INT_DMA1C4 - 16);
        xHWREG(NVIC_UNPEND0) = 1 << (INT_DMA1C5 - 16);
        xHWREG(NVIC_UNPEND0) = 1 << (INT_DMA1C6 - 16);
        xHWREG(NVIC_UNPEND0) = 1 << (INT_DMA1C7 - 16);
    }
    else if(ulInterrupt == INT_DMA2)
    {
        xHWREG(NVIC_UNPEND1) = 1 << (INT_DMA2C1 - 48);
        xHWREG(NVIC_UNPEND1) = 1 << (INT_DMA2C2 - 48);
        xHWREG(NVIC_UNPEND1) = 1 << (INT_DMA2C3 - 48);
        xHWREG(NVIC_UNPEND1) = 1 << (INT_DMA2C4 - 48);
        xHWREG(NVIC_UNPEND1) = 1 << (INT_DMA2C5 - 48);
    }
}

//*****************************************************************************
//
//! Sets the priority masking level
//!
//! \param ulPriorityMask is the priority level that will be masked.
//!
//! This function sets the interrupt priority masking level so that all
//! interrupts at the specified or lesser priority level is masked.  This
//! can be used to globally disable a set of interrupts with priority below
//! a predetermined threshold.  A value of 0 disables priority
//! masking.
//!
//! Smaller numbers correspond to higher interrupt priorities.  So for example
//! a priority level mask of 4 will allow interrupts of priority level 0-3,
//! and interrupts with a numerical priority of 4 and greater will be blocked.
//!
//! The hardware priority mechanism will only look at the upper N bits of the
//! priority level (where N is 3 for the Stellaris family), so any
//! prioritization must be performed in those bits.
//!
//! \return None.
//
//*****************************************************************************
void
xIntPriorityMaskSet(unsigned long ulPriorityMask)
{
    xCPUbasepriSet(ulPriorityMask);
}

//*****************************************************************************
//
//! Gets the priority masking level
//!
//! This function gets the current setting of the interrupt priority masking
//! level.  The value returned is the priority level such that all interrupts
//! of that and lesser priority are masked.  A value of 0 means that priority
//! masking is disabled.
//!
//! Smaller numbers correspond to higher interrupt priorities.  So for example
//! a priority level mask of 4 will allow interrupts of priority level 0-3,
//! and interrupts with a numerical priority of 4 and greater will be blocked.
//!
//! The hardware priority mechanism will only look at the upper N bits of the
//! priority level (where N is 3 for the Stellaris family), so any
//! prioritization must be performed in those bits.
//!
//! \return Returns the value of the interrupt priority level mask.
//
//*****************************************************************************
unsigned long
xIntPriorityMaskGet(void)
{
    return(xCPUbasepriGet());
}

//*****************************************************************************
//
//! Enables the SysTick counter.
//!
//! This will start the SysTick counter.  If an interrupt handler has been
//! registered, it will be called when the SysTick counter rolls over.
//!
//! \note Calling this function will cause the SysTick counter to (re)commence
//! counting from its current value.  The counter is not automatically reloaded
//! with the period as specified in a previous call to XSysTickPeriodSet().  If
//! an immediate reload is required, the \b NVIC_ST_CURRENT register must be
//! written to force this.  Any write to this register clears the SysTick
//! counter to 0 and will cause a reload with the supplied period on the next
//! clock.
//!
//! \return None.
//
//*****************************************************************************
void
xSysTickEnable(void)
{
    //
    // Enable SysTick.
    //
    xHWREG(NVIC_ST_CTRL) |= NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_ENABLE;
}

//*****************************************************************************
//
//! Disables the SysTick counter.
//!
//! This will stop the SysTick counter.  If an interrupt handler has been
//! registered, it will no longer be called until SysTick is restarted.
//!
//! \return None.
//
//*****************************************************************************
void
xSysTickDisable(void)
{
    //
    // Disable SysTick.
    //
    xHWREG(NVIC_ST_CTRL) &= ~(NVIC_ST_CTRL_ENABLE);
}


//*****************************************************************************
//
//! Enables the SysTick interrupt.
//!
//! This function will enable the SysTick interrupt, allowing it to be
//! reflected to the processor.
//!
//! \note The SysTick interrupt handler does not need to clear the SysTick
//! interrupt source as this is done automatically by NVIC when the interrupt
//! handler is called.
//!
//! \return None.
//
//*****************************************************************************
void
xSysTickIntEnable(void)
{
    //
    // Enable the SysTick interrupt.
    //
    xHWREG(NVIC_ST_CTRL) |= NVIC_ST_CTRL_INTEN;
}

//*****************************************************************************
//
//! Disables the SysTick interrupt.
//!
//! This function will disable the SysTick interrupt, preventing it from being
//! reflected to the processor.
//!
//! \return None.
//
//*****************************************************************************
void
xSysTickIntDisable(void)
{
    //
    // Disable the SysTick interrupt.
    //
    xHWREG(NVIC_ST_CTRL) &= ~(NVIC_ST_CTRL_INTEN);
}

//*****************************************************************************
//
//! Sets the period of the SysTick counter.
//!
//! \param ulPeriod is the number of clock ticks in each period of the SysTick
//! counter; must be between 1 and 16,777,216, inclusive.
//!
//! This function sets the rate at which the SysTick counter wraps; this
//! equates to the number of processor clocks between interrupts.
//!
//! \note Calling this function does not cause the SysTick counter to reload
//! immediately.  If an immediate reload is required, the \b NVIC_ST_CURRENT
//! register must be written.  Any write to this register clears the SysTick
//! counter to 0 and will cause a reload with the \e ulPeriod supplied here on
//! the next clock after the SysTick is enabled.
//!
//! \return None.
//
//*****************************************************************************
void
xSysTickPeriodSet(unsigned long ulPeriod)
{
    //
    // Check the arguments.
    //
    xASSERT((ulPeriod > 0) && (ulPeriod <= 16777216));

    //
    // Set the period of the SysTick counter.
    //
    xHWREG(NVIC_ST_RELOAD) = ulPeriod - 1;
}

//*****************************************************************************
//
//! Gets the period of the SysTick counter.
//!
//! This function returns the rate at which the SysTick counter wraps; this
//! equates to the number of processor clocks between interrupts.
//!
//! \return Returns the period of the SysTick counter.
//
//*****************************************************************************
unsigned long
xSysTickPeriodGet(void)
{
    //
    // Return the period of the SysTick counter.
    //
    return(xHWREG(NVIC_ST_RELOAD) + 1);
}

//*****************************************************************************
//
//! Gets the current value of the SysTick counter.
//!
//! This function returns the current value of the SysTick counter; this will
//! be a value between the period - 1 and zero, inclusive.
//!
//! \return Returns the current value of the SysTick counter.
//
//*****************************************************************************
unsigned long
xSysTickValueGet(void)
{
    //
    // Return the current value of the SysTick counter.
    //
    return(xHWREG(NVIC_ST_CURRENT));
}

