//*****************************************************************************
//
//! \file startup_coide.c
//! \brief HT32F125x Devices Startup code for CooCox CoIDE.
//!        This module performs:
//!           - Set the initial SP
//!           - Set the vector table entries with the exceptions ISR address
//!           - Initialize data and bss
//!           - Setup the microcontroller system.
//!           - Call the application's entry point.
//!           .
//! \version V2.1.1.0
//! \date 2/22/2011
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

//***************************************************************************** 
//
// Stack Configuration
//
//*****************************************************************************
//
// Stack size (in Words)
//
#define STACK_SIZE       0x00000100
__attribute__ ((section(".co_stack")))
unsigned long pulStack[STACK_SIZE];
 
#define WEAK __attribute__ ((weak))

//*****************************************************************************
//
// Declaration of the default fault handlers
//
//*****************************************************************************
void WEAK  ResetHandler(void);
void WEAK  NMIIntHandler(void);
void WEAK  HardFaultIntHandler(void);
void WEAK  MemManageIntHandler(void);
void WEAK  BusFaultIntHandler(void);
void WEAK  UsageFaultIntHandler(void);
void WEAK  SVCIntHandler(void);
void WEAK  DebugMonIntHandler(void);
void WEAK  PendSVIntHandler(void);
void WEAK  SysTickIntHandler(void);
void WEAK  CKRDYIntHandler(void);
void WEAK  LVDIntHandler(void);
void WEAK  BODIntHandler(void);
void WEAK  WDTIntHandler(void);
void WEAK  RTCIntHandler(void);
void WEAK  FMCIntHandler(void);
void WEAK  EVWUPIntHandler(void);
void WEAK  LPWUPIntHandler(void);
void WEAK  EINT0IntHandler(void);
void WEAK  EINT1IntHandler(void);
void WEAK  EINT2IntHandler(void);
void WEAK  EINT3IntHandler (void);
void WEAK  EINT4IntHandler(void);
void WEAK  EINT5IntHandler(void);
void WEAK  EINT6IntHandler(void);
void WEAK  EINT7IntHandler(void);
void WEAK  EINT8IntHandler(void);
void WEAK  EINT9IntHandler(void);
void WEAK  EINT10IntHandler(void);
void WEAK  EINT11IntHandler(void);
void WEAK  EINT12IntHandler(void);
void WEAK  EINT13IntHandler(void);
void WEAK  EINT14IntHandler(void);
void WEAK  EINT15IntHandler(void);
void WEAK  COMPIntHandler(void);
void WEAK  ADCIntHandler(void);
void WEAK  TIMER0IntHandler(void);
void WEAK  TIMER1IntHandler(void);
void WEAK  I2C0IntHandler(void);
void WEAK  SPI0IntHandler(void);
void WEAK  UART0IntHandler(void);
//*****************************************************************************
//
// Symbols defined in linker script
//
//*****************************************************************************
//
// Start address for the initialization values of the .data section.
//  
extern unsigned long _sidata;

//
// Start address for the .data section
//
extern unsigned long _sdata;

//
// End address for the .data section
//
extern unsigned long _edata;

//
// Start address for the .bss section
//
extern unsigned long _sbss;

//
// End address for the .bss section
//
extern unsigned long _ebss;

//
// End address for ram 
//
extern void _eram;

//*****************************************************************************
//
// Function prototypes
//
//*****************************************************************************
extern int main(void);
void ResetHandler(void);
static void DefaultIntHandler(void);

//
// The minimal vector table for a Cortex M0.  Note that the proper constructs
// must be placed on this to ensure that it ends up at physical address
// 0x00000000.
//  
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
    (void *)&pulStack[STACK_SIZE],          // The initial stack pointer
    ResetHandler,                           // Reset Handler
    NMIIntHandler,                          // NMI Handler
    HardFaultIntHandler,                    // Hard Fault Handler
    MemManageIntHandler,                    // Memory Management Fault Handler
    BusFaultIntHandler,                     // Bus Fault Handler
    UsageFaultIntHandler,                   // Usage Fault Handler
    0,0,0,0,                                // Reserved
    SVCIntHandler,                          // SVCall Handler
    DebugMonIntHandler,                     // Debug Monitor Handler
    0,                                      // Reserved
    PendSVIntHandler,                       // PendSV Handler
    SysTickIntHandler,                      // SysTick Handler
    CKRDYIntHandler,                        // Clock ready interrupt(HSE,HSI,LSE,LSI or PLL)
    LVDIntHandler,                          // Low voltage detection interrupt
    BODIntHandler,                          // Brownout low voltage detected interrupt
    WDTIntHandler,                          // Watch Dog Timer interrupt
    RTCIntHandler,                          // RTC global interrupt
    FMCIntHandler,                          // FMC global interrupt
    EVWUPIntHandler,                        // EXTI Event wakeup interrupt
    LPWUPIntHandler,                        // WAKEUP pin interrupt
    EINT0IntHandler,                        // EXTI Line 0 interrupt
    EINT1IntHandler,                        // EXTI Line 1 interrupt
    EINT2IntHandler,                        // EXTI Line 2 interrupt
    EINT3IntHandler,                        // EXTI Line 3 interrupt
    EINT4IntHandler,                        // EXTI Line 4 interrupt
    EINT5IntHandler,                        // EXTI Line 5 interrupt
    EINT6IntHandler,                        // EXTI Line 6 interrupt
    EINT7IntHandler,                        // EXTI Line 7 interrupt
    EINT8IntHandler,                        // EXTI Line 8 interrupt
    EINT9IntHandler,                        // EXTI Line 9 interrupt
    EINT10IntHandler,                       // EXTI Line 10 interrupt
    EINT11IntHandler,                       // EXTI Line 11 interrupt
    EINT12IntHandler,                       // EXTI Line 12 interrupt
    EINT13IntHandler,                       // EXTI Line 13 interrupt
    EINT14IntHandler,                       // EXTI Line 14 interrupt
    EINT15IntHandler,                       // EXTI Line 15 interrupt
    COMPIntHandler,                         // Comparator global interrupt
    ADCIntHandler,                          // ADC interrupt
    0,0,0,0,0,0,0,0,0,                      // Reserved
    TIMER0IntHandler,                        // GPTM0 global interrupt
    TIMER1IntHandler,                        // GPTM1 global interrupt
    0,0,0,0,0,0,                            // Reserved
    I2C0IntHandler,                         // I2C global interrupt
    0,                                      // Reserved
    SPI0IntHandler,                         // SPI0 global interrupt
    0,                                      // Reserved
    UART0IntHandler,                        // UART0 global interrupt
};

//*****************************************************************************
//
//! \brief This is the code that gets called when the processor first
//! starts execution following a reset event. 
//!
//! \param None.
//!
//! Only the absolutely necessary set is performed, after which the
//! application supplied main() routine is called. 
//!
//! \return None.
//
//*****************************************************************************
void Default_ResetHandler(void)
{
    //
    // Initialize data and bss
    //
    unsigned long *pulSrc, *pulDest;

    //
    // Copy the data segment initializers from flash to SRAM
    //
    pulSrc = &_sidata;

    for(pulDest = &_sdata; pulDest < &_edata; )
    {
        *(pulDest++) = *(pulSrc++);
    }

    //
    // Zero fill the bss segment.
    //
    for(pulDest = &_sbss; pulDest < &_ebss; )
    {
        *(pulDest++) = 0;
    }

    //
    // Call the application's entry point.
    //
    main();
}

//*****************************************************************************
//
// Provide weak aliases for each Exception handler to the DefaultIntHandler.
// As they are weak aliases, any function with the same name will override
// this definition.
//
//*****************************************************************************
#pragma weak ResetHandler = Default_ResetHandler
#pragma weak NMIIntHandler = DefaultIntHandler
#pragma weak HardFaultIntHandler = DefaultIntHandler
#pragma weak MemManageIntHandler = DefaultIntHandler
#pragma weak BusFaultIntHandler = DefaultIntHandler
#pragma weak UsageFaultIntHandler = DefaultIntHandler
#pragma weak SVCIntHandler = DefaultIntHandler
#pragma weak DebugMonIntHandler = DefaultIntHandler
#pragma weak PendSVIntHandler = DefaultIntHandler
#pragma weak SysTickIntHandler = DefaultIntHandler
#pragma weak CKRDYIntHandler = DefaultIntHandler
#pragma weak LVDIntHandler = DefaultIntHandler
#pragma weak BODIntHandler = DefaultIntHandler
#pragma weak WDTIntHandler = DefaultIntHandler
#pragma weak RTCIntHandler = DefaultIntHandler
#pragma weak FMCIntHandler = DefaultIntHandler
#pragma weak EVWUPIntHandler = DefaultIntHandler
#pragma weak LPWUPIntHandler = DefaultIntHandler
#pragma weak EINT0IntHandler = DefaultIntHandler
#pragma weak EINT1IntHandler = DefaultIntHandler
#pragma weak EINT2IntHandler = DefaultIntHandler
#pragma weak EINT3IntHandler = DefaultIntHandler
#pragma weak EINT4IntHandler = DefaultIntHandler
#pragma weak EINT5IntHandler = DefaultIntHandler
#pragma weak EINT6IntHandler = DefaultIntHandler
#pragma weak EINT7IntHandler = DefaultIntHandler
#pragma weak EINT8IntHandler = DefaultIntHandler
#pragma weak EINT9IntHandler = DefaultIntHandler
#pragma weak EINT10IntHandler = DefaultIntHandler
#pragma weak EINT11IntHandler = DefaultIntHandler
#pragma weak EINT12IntHandler = DefaultIntHandler
#pragma weak EINT13IntHandler = DefaultIntHandler
#pragma weak EINT14IntHandler = DefaultIntHandler
#pragma weak EINT15IntHandler = DefaultIntHandler
#pragma weak COMPIntHandler = DefaultIntHandler
#pragma weak ADCIntHandler = DefaultIntHandler
#pragma weak TIMER0IntHandler = DefaultIntHandler
#pragma weak TIMER1IntHandler = DefaultIntHandler
#pragma weak I2C0IntHandler = DefaultIntHandler
#pragma weak SPI0IntHandler = DefaultIntHandler
#pragma weak UART0IntHandler = DefaultIntHandler

//*****************************************************************************
//
//! \brief This is the code that gets called when the processor receives an
//! unexpected interrupt.
//!
//! \param None.
//!
//! This simply enters an infinite loop, preserving the system state for
//! examination by a debugger.
//!
//! \return None.
//*****************************************************************************
static void DefaultIntHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}
