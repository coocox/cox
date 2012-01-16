//*****************************************************************************
//
//! \file startup_coide.c
//! \brief M051 Devices Startup code for CooCox CoIDE.
//!        This module performs:
//!           - Set the initial SP
//!           - Set the vector table entries with the exceptions ISR address
//!           - Initialize data and bss
//!           - Setup the microcontroller system. 			
//!           - Call the application's entry point.
//!           .
//! \version V2.1.1.0
//! \date 12/22/2011
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
void WEAK  SVCIntHandler(void);
void WEAK  PendSVIntHandler(void);
void WEAK  SysTickIntHandler(void);
void WEAK  BODIntHandler(void);  
void WEAK  WDTIntHandler(void);  
void WEAK  EINT0IntHandler(void);
void WEAK  EINT1IntHandler(void);
void WEAK  GPABIntHandler(void); 
void WEAK  GPCDEIntHandler(void);
void WEAK  PWMAIntHandler(void);
void WEAK  PWMBIntHandler(void);
void WEAK  TIMER0IntHandler(void); 
void WEAK  TIMER1IntHandler(void); 
void WEAK  TIMER2IntHandler(void); 
void WEAK  TIMER3IntHandler(void); 
void WEAK  UART0IntHandler(void);
void WEAK  UART1IntHandler(void);
void WEAK  SPI0IntHandler(void); 
void WEAK  SPI1IntHandler(void);  
void WEAK  I2C0IntHandler(void); 
void WEAK  ACMPIntHandler(void);
void WEAK  PWRWUIntHandler(void);
void WEAK  ADCIntHandler(void);

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
    ResetHandler,                           // The reset handler                        
    NMIIntHandler,                          // The NMI handler                        
    HardFaultIntHandler,                    // The hard fault handler                  
    0,0,0,0,0,0,0,                          // Reserved                            
    SVCIntHandler,                          // SVCall handler                  
    0,0,                                    // Reserved                                  
    PendSVIntHandler,                       // The PendSV handler                      
    SysTickIntHandler,                      // The SysTick handler                    
    BODIntHandler,                          // Brownout low voltage detected
    WDTIntHandler,                          // Watch Dog Timer  
    EINT0IntHandler,                        // External signal interrupt from
                                            // PD.2 pin 
    EINT1IntHandler,                        // External signal interrupt from
                                            // PD.3 pin 
    GPABIntHandler,                         // External signal interrupt from 
                                            // PA[7:0] / PB[7:0]
    GPCDEIntHandler,                        // External interrupt from 
                                            // PC[7:0]/PD[7:0]/PE[7:0],except PD.2 and PD.3
    PWMAIntHandler,                         // PWM0 or PWM2,PWM1 or PWM3
    PWMBIntHandler,                         // PWM4 or PWM5,PWM6 or PWM7   
    TIMER0IntHandler,                       // Timer 0 
    TIMER1IntHandler,                       // Timer 1
    TIMER2IntHandler,                       // Timer 2
    TIMER3IntHandler,                       // Timer 3
    UART0IntHandler,                        // UART0
    UART1IntHandler,                        // UART1
    SPI0IntHandler,                         // SPI0 
    SPI1IntHandler,                         // SPI1
    DefaultIntHandler,                      // Reserved
    DefaultIntHandler,                      // Reserved
    I2C0IntHandler,                         // I2C
    DefaultIntHandler,                      // Reserved
    DefaultIntHandler,                      // Reserved
    DefaultIntHandler,                      // Reserved
    DefaultIntHandler,                      // Reserved
    DefaultIntHandler,                      // Reserved
    DefaultIntHandler,                      // Reserved
    ACMPIntHandler,                         // Analog Comparator
    DefaultIntHandler,                      // Reserved
    DefaultIntHandler,                      // Reserved
    PWRWUIntHandler,                        // Clock controller
    ADCIntHandler,                          // ADC
    DefaultIntHandler,                      // Reserved
    DefaultIntHandler,                      // Reserved
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
#pragma weak SVCIntHandler = DefaultIntHandler
#pragma weak PendSVIntHandler = DefaultIntHandler
#pragma weak SysTickIntHandler = DefaultIntHandler
#pragma weak BODIntHandler = DefaultIntHandler  
#pragma weak WDTIntHandler = DefaultIntHandler  
#pragma weak EINT0IntHandler = DefaultIntHandler
#pragma weak EINT1IntHandler = DefaultIntHandler
#pragma weak GPABIntHandler = DefaultIntHandler 
#pragma weak GPCDEIntHandler = DefaultIntHandler
#pragma weak PWMAIntHandler = DefaultIntHandler
#pragma weak PWMBIntHandler = DefaultIntHandler 
#pragma weak TIMER0IntHandler = DefaultIntHandler 
#pragma weak TIMER1IntHandler = DefaultIntHandler 
#pragma weak TIMER2IntHandler = DefaultIntHandler 
#pragma weak TIMER3IntHandler = DefaultIntHandler 
#pragma weak UART0IntHandler = DefaultIntHandler
#pragma weak UART1IntHandler = DefaultIntHandler
#pragma weak SPI0IntHandler = DefaultIntHandler 
#pragma weak SPI1IntHandler = DefaultIntHandler 
#pragma weak I2C0IntHandler = DefaultIntHandler 
#pragma weak ACMPIntHandler = DefaultIntHandler  
#pragma weak PWRWUIntHandler = DefaultIntHandler
#pragma weak ADCIntHandler = DefaultIntHandler  

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
    while (1) 
    {
    }
}