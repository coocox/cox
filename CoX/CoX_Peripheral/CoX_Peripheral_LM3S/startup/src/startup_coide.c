//*****************************************************************************
//
//! \file startup_coide.c
//! \brief TI Stellaris(LM3S) Devices Startup code for CooCox CoIDE.
//!        This module performs:
//!           - Set the initial SP
//!           - Set the vector table entries with the exceptions ISR address
//!           - Initialize data and bss			
//!           - Call the application's entry point.
//!           .
//! \version V2.1.1.0
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
void WEAK  MemFaultIntHandler(void);
void WEAK  BusFaultIntHandler(void);
void WEAK  UsageFaultIntHandler(void);
void WEAK  SVCIntHandler(void);
void WEAK  DebugMonitorIntHandler(void);
void WEAK  PendSVIntHandler(void);    
void WEAK  SysTickIntHandler(void);  
void WEAK  GPIOAIntHandler(void);             
void WEAK  GPIOBIntHandler(void);             
void WEAK  GPIOCIntHandler(void);             
void WEAK  GPIODIntHandler(void);             
void WEAK  GPIOEIntHandler(void);             
void WEAK  UART0IntHandler(void);             
void WEAK  UART1IntHandler(void);             
void WEAK  SSI0IntHandler(void);              
void WEAK  I2C0IntHandler(void);              
void WEAK  PWMFaultIntHandler(void);          
void WEAK  PWM0IntHandler(void);              
void WEAK  PWM1IntHandler(void);              
void WEAK  PWM2IntHandler(void);              
void WEAK  QEI0IntHandler(void);              
void WEAK  ADC0Seq0IntHandler(void);          
void WEAK  ADC0Seq1IntHandler(void);          
void WEAK  ADC0Seq2IntHandler(void);          
void WEAK  ADC0Seq3IntHandler(void);          
void WEAK  WDTIntHandler(void);               
void WEAK  TIMER0AIntHandler(void);           
void WEAK  TIMER0BIntHandler(void);           
void WEAK  TIMER1AIntHandler(void);           
void WEAK  TIMER1BIntHandler(void);           
void WEAK  TIMER2AIntHandler(void);           
void WEAK  TIMER2BIntHandler(void);           
void WEAK  ACMP0IntHandler(void);             
void WEAK  ACMP1IntHandler(void);             
void WEAK  ACMP2IntHandler(void);             
void WEAK  SysCtlIntHandler(void);            
void WEAK  FMCIntHandler(void);               
void WEAK  GPIOFIntHandler(void);             
void WEAK  GPIOGIntHandler(void);             
void WEAK  GPIOHIntHandler(void);             
void WEAK  UART2IntHandler(void);             
void WEAK  SSI1IntHandler(void);              
void WEAK  TIMER3AIntHandler(void);           
void WEAK  TIMER3BIntHandler(void);           
void WEAK  I2C1IntHandler(void);              
void WEAK  QEI1IntHandler(void);              
void WEAK  CAN0IntHandler(void);              
void WEAK  CAN1IntHandler(void);              
void WEAK  CAN2IntHandler(void);              
void WEAK  EthernetIntHandler(void);          
void WEAK  HibernateIntHandler(void);         
void WEAK  USB0IntHandler(void);              
void WEAK  PWM3IntHandler(void);              
void WEAK  uDMAIntHandler(void);              
void WEAK  uDMAErrorIntHandler(void);         
void WEAK  ADC1Seq0IntHandler(void);          
void WEAK  ADC1Seq1IntHandler(void);          
void WEAK  ADC1Seq2IntHandler(void);          
void WEAK  ADC1Seq3IntHandler(void);          
void WEAK  I2S0IntHandler(void);              
void WEAK  EBI0IntHandler(void);              
void WEAK  GPIOJIntHandler(void); 


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
// The minimal vector table for a Cortex M3.  Note that the proper constructs
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
    MemFaultIntHandler,                     // The MPU fault handler                  
    BusFaultIntHandler,                     // The bus fault handler                   
    UsageFaultIntHandler,                   // The usage fault handler                  
    0,0,0,0,                                // Reserved                            
    SVCIntHandler,                          // SVCall handler                         
    DebugMonitorIntHandler,                 // Debug monitor handler                    
    0,                                      // Reserved                                  
    PendSVIntHandler,                       // The PendSV handler                      
    SysTickIntHandler,                      // The SysTick handler

                                            // External Interrupts
    GPIOAIntHandler,                        // GPIO Port A
    GPIOBIntHandler,                        // GPIO Port B
    GPIOCIntHandler,                        // GPIO Port C
    GPIODIntHandler,                        // GPIO Port D
    GPIOEIntHandler,                        // GPIO Port E
    UART0IntHandler,                        // UART0 Rx and Tx
    UART1IntHandler,                        // UART1 Rx and Tx
    SSI0IntHandler,                         // SSI0 Rx and Tx
    I2C0IntHandler,                         // I2C0 Master and Slave
    PWMFaultIntHandler,                     // PWM Fault
    PWM0IntHandler,                         // PWM Generator 0
    PWM1IntHandler,                         // PWM Generator 1
    PWM2IntHandler,                         // PWM Generator 2
    QEI0IntHandler,                         // Quadrature Encoder 0
    ADC0Seq0IntHandler,                     // ADC Sequence 0
    ADC0Seq1IntHandler,                     // ADC Sequence 1
    ADC0Seq2IntHandler,                     // ADC Sequence 2
    ADC0Seq3IntHandler,                     // ADC Sequence 3
    WDTIntHandler,                          // Watchdog timer
    TIMER0AIntHandler,                      // Timer 0 subtimer A
    TIMER0BIntHandler,                      // Timer 0 subtimer B
    TIMER1AIntHandler,                      // Timer 1 subtimer A
    TIMER1BIntHandler,                      // Timer 1 subtimer B
    TIMER2AIntHandler,                      // Timer 2 subtimer A
    TIMER2BIntHandler,                      // Timer 2 subtimer B
    ACMP0IntHandler,                        // Analog Comparator 0
    ACMP1IntHandler,                        // Analog Comparator 1
    ACMP2IntHandler,                        // Analog Comparator 2
    SysCtlIntHandler,                       // System Control (PLL, OSC, BO)
    FMCIntHandler,                          // FLASH Control
    GPIOFIntHandler,                        // GPIO Port F
    GPIOGIntHandler,                        // GPIO Port G
    GPIOHIntHandler,                        // GPIO Port H
    UART2IntHandler,                        // UART2 Rx and Tx
    SSI1IntHandler,                         // SSI1 Rx and Tx
    TIMER3AIntHandler,                      // Timer 3 subtimer A
    TIMER3BIntHandler,                      // Timer 3 subtimer B
    I2C1IntHandler,                         // I2C1 Master and Slave
    QEI1IntHandler,                         // Quadrature Encoder 1
    CAN0IntHandler,                         // CAN0
    CAN1IntHandler,                         // CAN1
    CAN2IntHandler,                         // CAN2
    EthernetIntHandler,                     // Ethernet
    HibernateIntHandler,                    // Hibernate
    USB0IntHandler,                         // USB0
    PWM3IntHandler,                         // PWM Generator 3
    uDMAIntHandler,                         // uDMA Software Transfer
    uDMAErrorIntHandler,                    // uDMA Error
    ADC1Seq0IntHandler,                     // ADC1 Sequence 0
    ADC1Seq1IntHandler,                     // ADC1 Sequence 1
    ADC1Seq2IntHandler,                     // ADC1 Sequence 2
    ADC1Seq3IntHandler,                     // ADC1 Sequence 3
    I2S0IntHandler,                         // I2S0
    EBI0IntHandler,                         // External Bus Interface 0
    GPIOJIntHandler,                        // GPIO Port J 
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
#pragma weak DebugMonitorIntHandler = DefaultIntHandler
#pragma weak PendSVIntHandler = DefaultIntHandler
#pragma weak SysTickIntHandler = DefaultIntHandler
#pragma weak GPIOAIntHandler = DefaultIntHandler             
#pragma weak GPIOBIntHandler = DefaultIntHandler             
#pragma weak GPIOCIntHandler = DefaultIntHandler             
#pragma weak GPIODIntHandler = DefaultIntHandler             
#pragma weak GPIOEIntHandler = DefaultIntHandler             
#pragma weak UART0IntHandler = DefaultIntHandler             
#pragma weak UART1IntHandler = DefaultIntHandler             
#pragma weak SSI0IntHandler = DefaultIntHandler              
#pragma weak I2C0IntHandler = DefaultIntHandler              
#pragma weak PWMFaultIntHandler = DefaultIntHandler          
#pragma weak PWM0IntHandler = DefaultIntHandler              
#pragma weak PWM1IntHandler = DefaultIntHandler              
#pragma weak PWM2IntHandler = DefaultIntHandler              
#pragma weak QEI0IntHandler = DefaultIntHandler              
#pragma weak ADC0Seq0IntHandler = DefaultIntHandler          
#pragma weak ADC0Seq1IntHandler = DefaultIntHandler          
#pragma weak ADC0Seq2IntHandler = DefaultIntHandler          
#pragma weak ADC0Seq3IntHandler = DefaultIntHandler          
#pragma weak WDTIntHandler = DefaultIntHandler               
#pragma weak TIMER0AIntHandler = DefaultIntHandler           
#pragma weak TIMER0BIntHandler = DefaultIntHandler           
#pragma weak TIMER1AIntHandler = DefaultIntHandler           
#pragma weak TIMER1BIntHandler = DefaultIntHandler           
#pragma weak TIMER2AIntHandler = DefaultIntHandler           
#pragma weak TIMER2BIntHandler = DefaultIntHandler           
#pragma weak ACMP0IntHandler = DefaultIntHandler             
#pragma weak ACMP1IntHandler = DefaultIntHandler             
#pragma weak ACMP2IntHandler = DefaultIntHandler             
#pragma weak SysCtlIntHandler = DefaultIntHandler            
#pragma weak FMCIntHandler = DefaultIntHandler               
#pragma weak GPIOFIntHandler = DefaultIntHandler             
#pragma weak GPIOGIntHandler = DefaultIntHandler             
#pragma weak GPIOHIntHandler = DefaultIntHandler             
#pragma weak UART2IntHandler = DefaultIntHandler             
#pragma weak SSI1IntHandler = DefaultIntHandler              
#pragma weak TIMER3AIntHandler = DefaultIntHandler           
#pragma weak TIMER3BIntHandler = DefaultIntHandler           
#pragma weak I2C1IntHandler = DefaultIntHandler              
#pragma weak QEI1IntHandler = DefaultIntHandler              
#pragma weak CAN0IntHandler = DefaultIntHandler              
#pragma weak CAN1IntHandler = DefaultIntHandler              
#pragma weak CAN2IntHandler = DefaultIntHandler              
#pragma weak EthernetIntHandler = DefaultIntHandler          
#pragma weak HibernateIntHandler = DefaultIntHandler         
#pragma weak USB0IntHandler = DefaultIntHandler              
#pragma weak PWM3IntHandler = DefaultIntHandler              
#pragma weak uDMAIntHandler = DefaultIntHandler              
#pragma weak uDMAErrorIntHandler = DefaultIntHandler         
#pragma weak ADC1Seq0IntHandler = DefaultIntHandler          
#pragma weak ADC1Seq1IntHandler = DefaultIntHandler          
#pragma weak ADC1Seq2IntHandler = DefaultIntHandler          
#pragma weak ADC1Seq3IntHandler = DefaultIntHandler          
#pragma weak I2S0IntHandler = DefaultIntHandler              
#pragma weak EBI0IntHandler = DefaultIntHandler              
#pragma weak GPIOJIntHandler = DefaultIntHandler 

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


