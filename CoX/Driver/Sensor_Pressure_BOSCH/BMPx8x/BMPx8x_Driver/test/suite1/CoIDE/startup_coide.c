//*****************************************************************************
//
//! \file startup_coide.c
//! \brief STM32F1xx Devices Startup code for CooCox CoIDE.
//!        This module performs:
//!           - Set the initial SP
//!           - Set the vector table entries with the exceptions ISR address
//!           - Initialize data and bss
//!           - Setup the microcontroller system. 			
//!           - Call the application's entry point.
//!           .
//! \version V2.1.1.0
//! \date 5/24/2012
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
void WEAK  WWDGIntHandler(void);  
void WEAK  PVDIntHandler(void);  
void WEAK  TAMPERIntHandler(void);
void WEAK  RTCIntHandler(void);
void WEAK  FLASHIntHandler(void); 
void WEAK  RCCIntHandler(void);
void WEAK  EXTI0IntHandler(void); 
void WEAK  EXTI1IntHandler(void); 
void WEAK  EXTI2IntHandler(void); 
void WEAK  EXTI3IntHandler(void); 
void WEAK  EXTI4IntHandler(void); 
void WEAK  DMA1Channel1IntHandler(void); 
void WEAK  DMA1Channel2IntHandler(void);
void WEAK  DMA1Channel3IntHandler(void);
void WEAK  DMA1Channel4IntHandler(void); 
void WEAK  DMA1Channel5IntHandler(void); 
void WEAK  DMA1Channel6IntHandler(void); 
void WEAK  DMA1Channel7IntHandler(void); 
void WEAK  ADC12IntHandler(void); 
void WEAK  CAN1TXIntHandler(void); 
void WEAK  CAN1RX0IntHandler(void); 
void WEAK  CAN1RX1IntHandler(void);  
void WEAK  CAN1SCEIntHandler(void);  
void WEAK  EXTI95IntHandler(void); 
void WEAK  TIM1BRKTIM9IntHandler(void);
void WEAK  TIM1UPTIM10IntHandler(void);
void WEAK  TIM1TRGCOMTIM11IntHandler(void);
void WEAK  TIM1CCIntHandler(void);
void WEAK  TIM2IntHandler(void);
void WEAK  TIM3IntHandler(void);
void WEAK  TIM4IntHandler(void);
void WEAK  I2C1EVIntHandler(void);
void WEAK  I2C1ERIntHandler(void);
void WEAK  I2C2EVIntHandler(void);
void WEAK  I2C2ERIntHandler(void);
void WEAK  SPI1IntHandler(void);
void WEAK  SPI2IntHandler(void);
void WEAK  USART1IntHandler(void);
void WEAK  USART2IntHandler(void);
void WEAK  USART3IntHandler(void);
void WEAK  EXTI1510IntHandler(void);
void WEAK  RTCAlarmIntHandler(void);
void WEAK  OTGFSWKUPIntHandler(void);
void WEAK  TIM8BRKTIM12IntHandler(void);
void WEAK  TIM8UPTIM13IntHandler(void);
void WEAK  TIM8TRGCOMTIM14IntHandler(void);
void WEAK  TIM8CCIntHandler(void);
void WEAK  ADC3IntHandler(void);
void WEAK  FSMCIntHandler(void);
void WEAK  SDIOIntHandler(void);
void WEAK  TIM5IntHandler(void);
void WEAK  SPI3IntHandler(void);
void WEAK  UART4IntHandler(void);
void WEAK  UART5IntHandler(void);
void WEAK  TIM6IntHandler(void);
void WEAK  TIM7IntHandler(void);
void WEAK  DMA2Channel1IntHandler(void);
void WEAK  DMA2Channel2IntHandler(void);
void WEAK  DMA2Channel3IntHandler(void);
void WEAK  DMA2Channel4IntHandler(void);
void WEAK  DMA2Channel5IntHandler(void);
void WEAK  ETHIntHandler(void);
void WEAK  ETHWKUPIntHandler(void);
void WEAK  CAN2TXIntHandler(void);
void WEAK  CAN2RX0IntHandler(void);
void WEAK  CAN2RX1IntHandler(void);
void WEAK  CAN2SCEIntHandler(void);
void WEAK  OTGFSIntHandler(void);


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
__attribute__ ((used))         
void ResetHandler(void);   
static void DefaultIntHandler(void);  

//
// The minimal vector table for a Cortex M3.  Note that the proper constructs
// must be placed on this to ensure that it ends up at physical address
// 0x00000000.
//  
__attribute__ ((used,section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
    (void *)&pulStack[STACK_SIZE],          // The initial stack pointer     
    ResetHandler,                           // The reset handler                        
    NMIIntHandler,                          // The NMI handler                        
    HardFaultIntHandler,                    // The hard fault handler                  
    MemManageIntHandler,                    // The MPU fault handler                  
    BusFaultIntHandler,                     // The bus fault handler                   
    UsageFaultIntHandler,                   // The usage fault handler                  
    0,0,0,0,                                // Reserved                            
    SVCIntHandler,                          // SVCall handler                         
    DebugMonIntHandler,                     // Debug monitor handler                    
    0,                                      // Reserved                                  
    PendSVIntHandler,                       // The PendSV handler                      
    SysTickIntHandler,                      // The SysTick handler                    
    WWDGIntHandler,                         // 0 Window Watchdog interrupt
    PVDIntHandler,                          // 1 PVD through EXTI Line detection  
    TAMPERIntHandler,                       // 2 Tamper interrupt 
    RTCIntHandler,                          // 3 RTC global interrupt
    FLASHIntHandler,                        // 4 Flash global interrupt
    RCCIntHandler,                          // 5 RCC global interrupt
    EXTI0IntHandler,                        // 6 EXTI Line0 interrupt
    EXTI1IntHandler,                        // 7 EXTI Line1 interrupt 
    EXTI2IntHandler,                        // 8 EXTI Line2 interrupt
    EXTI3IntHandler,                        // 9 EXTI Line3 interrupt
    EXTI4IntHandler,                        // 10 EXTI Line4 interrupt
    DMA1Channel1IntHandler,                 // 11 DMA1 Channel1 global interrupt
    DMA1Channel2IntHandler,                 // 12 DMA1 Channel2 global interrupt
    DMA1Channel3IntHandler,                 // 13 DMA1 Channel3 global interrupt
    DMA1Channel4IntHandler,                 // 14 DMA1 Channel4 global interrupt
    DMA1Channel5IntHandler,                 // 15 DMA1 Channel5 global interrupt
    DMA1Channel6IntHandler,                 // 16 DMA1 Channel6 global interrupt
    DMA1Channel7IntHandler,                 // 17 DMA1 Channel7 global interrupt
    ADC12IntHandler,                        // 18 ADC1 and ADC2 global interrupt
    CAN1TXIntHandler,                       // 19 CAN1 TX interrupts
    CAN1RX0IntHandler,                      // 20 CAN1 RX0 interrupts
    CAN1RX1IntHandler,                      // 21 CAN1 RX1 interrupt
    CAN1SCEIntHandler,                      // 22 CAN1 SCE interrupt 
    EXTI95IntHandler,                       // 23 EXTI Line[9:5] interrupts 
    TIM1BRKTIM9IntHandler,                  // 24 TIM1 Break interrupt
    TIM1UPTIM10IntHandler,                  // 25 TIM1 Update interrupt
    TIM1TRGCOMTIM11IntHandler,              // 26 TIM1 Trigger and Commutation
    TIM1CCIntHandler,                       // 27 TIM1 Capture Compare interrupt
    TIM2IntHandler,                         // 28 TIM2 global interrupt
    TIM3IntHandler,                         // 29 TIM3 global interrupt
    TIM4IntHandler,                         // 30 TIM4 global interrupt
    I2C1EVIntHandler,                       // 31 I2C1 event interrupt
    I2C1ERIntHandler,                       // 32 I2C1 error interrupt
    I2C2EVIntHandler,                       // 33 I2C2 event interrupt
    I2C2ERIntHandler,                       // 34 I2C2 error interrupt
    SPI1IntHandler,                         // 35 SPI1 global interrupt
    SPI2IntHandler,                         // 36 SPI2 global interrupt
    USART1IntHandler,                       // 37 USART1 global interrupt
    USART2IntHandler,                       // 38 USART2 global interrupt
    USART3IntHandler,                       // 39 USART3 global interrupt
    EXTI1510IntHandler,                     // 40 EXTI Line[15:10] interrupts
    RTCAlarmIntHandler,                     // 41 RTC alarm through EXTI line
    OTGFSWKUPIntHandler,                    // 42 USB On-The-Go FS Wakeup
    TIM8BRKTIM12IntHandler,                 // 43 TIM8 Break interrupt
    TIM8UPTIM13IntHandler,                  // 44 TIM8 Update interrupt
    TIM8TRGCOMTIM14IntHandler,              // 45 TIM8 Trigger and Commutation
    TIM8CCIntHandler,                       // 46 TIM8 Capture Compare interrupt
    ADC3IntHandler,                         // 47 ADC3 global interrupt
    FSMCIntHandler,                         // 48 FSMC global interrupt
    SDIOIntHandler,                         // 49 SDIO global interrupt
    TIM5IntHandler,                         // 50 TIM5 global interrupt
    SPI3IntHandler,                         // 51 SPI3 global interrupt
    UART4IntHandler,                        // 52 UART4 global interrupt
    UART5IntHandler,                        // 53 UART5 global interrupt
    TIM6IntHandler,                         // 54 TIM6 global interrupt
    TIM7IntHandler,                         // 55 TIM7 global interrupt
    DMA2Channel1IntHandler,                 // 56 DMA2 Channel1 global interrupt
    DMA2Channel2IntHandler,                 // 57 DMA2 Channel2 global interrupt
    DMA2Channel3IntHandler,                 // 58 DMA2 Channel3 global interrupt
    DMA2Channel4IntHandler,                 // 59 DMA2 Channel4 global interrupt
    DMA2Channel5IntHandler,                 // 60 DMA2 Channel5 global interrupt
    ETHIntHandler,                          // 61 Ethernet global interrupt
    ETHWKUPIntHandler,                      // 62 Ethernet Wakeup through EXTI line
    CAN2TXIntHandler,                       // 63 CAN2 TX interrupts
    CAN2RX0IntHandler,                      // 64 CAN2 RX0 interrupts
    CAN2RX1IntHandler,                      // 65 CAN2 RX1 interrupt
    CAN2SCEIntHandler,                      // 66 CAN2 SCE interrupt
    OTGFSIntHandler,                        // 67 USB On The Go FS global interrupt
    (void *)0xF108F85F                      // Boot in RAM mode 
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
#pragma weak WWDGIntHandler = DefaultIntHandler  
#pragma weak PVDIntHandler = DefaultIntHandler  
#pragma weak TAMPERIntHandler = DefaultIntHandler
#pragma weak RTCIntHandler = DefaultIntHandler
#pragma weak FLASHIntHandler = DefaultIntHandler 
#pragma weak RCCIntHandler = DefaultIntHandler
#pragma weak EXTI0IntHandler = DefaultIntHandler 
#pragma weak EXTI1IntHandler = DefaultIntHandler 
#pragma weak EXTI2IntHandler = DefaultIntHandler 
#pragma weak EXTI3IntHandler = DefaultIntHandler 
#pragma weak EXTI4IntHandler = DefaultIntHandler 
#pragma weak DMA1Channel1IntHandler = DefaultIntHandler 
#pragma weak DMA1Channel2IntHandler = DefaultIntHandler
#pragma weak DMA1Channel3IntHandler = DefaultIntHandler
#pragma weak DMA1Channel4IntHandler = DefaultIntHandler 
#pragma weak DMA1Channel5IntHandler = DefaultIntHandler 
#pragma weak DMA1Channel6IntHandler = DefaultIntHandler 
#pragma weak DMA1Channel7IntHandler = DefaultIntHandler 
#pragma weak ADC12IntHandler = DefaultIntHandler 
#pragma weak CAN1TXIntHandler = DefaultIntHandler 
#pragma weak CAN1RX0IntHandler = DefaultIntHandler 
#pragma weak CAN1RX1IntHandler = DefaultIntHandler  
#pragma weak CAN1SCEIntHandler = DefaultIntHandler  
#pragma weak EXTI95IntHandler = DefaultIntHandler 
#pragma weak TIM1BRKTIM9IntHandler = DefaultIntHandler
#pragma weak TIM1UPTIM10IntHandler = DefaultIntHandler
#pragma weak TIM1TRGCOMTIM11IntHandler = DefaultIntHandler
#pragma weak TIM1CCIntHandler = DefaultIntHandler
#pragma weak TIM2IntHandler = DefaultIntHandler  
#pragma weak TIM3IntHandler = DefaultIntHandler 
#pragma weak TIM4IntHandler = DefaultIntHandler 
#pragma weak I2C1EVIntHandler = DefaultIntHandler 
#pragma weak I2C1ERIntHandler = DefaultIntHandler 
#pragma weak I2C2EVIntHandler = DefaultIntHandler 
#pragma weak I2C2ERIntHandler = DefaultIntHandler 
#pragma weak SPI1IntHandler = DefaultIntHandler 
#pragma weak SPI2IntHandler = DefaultIntHandler 
#pragma weak USART1IntHandler = DefaultIntHandler 
#pragma weak USART2IntHandler = DefaultIntHandler 
#pragma weak USART3IntHandler = DefaultIntHandler 
#pragma weak EXTI1510IntHandler = DefaultIntHandler 
#pragma weak RTCAlarmIntHandler = DefaultIntHandler 
#pragma weak OTGFSWKUPIntHandler = DefaultIntHandler
#pragma weak TIM8BRKTIM12IntHandler = DefaultIntHandler
#pragma weak TIM8UPTIM13IntHandler = DefaultIntHandler
#pragma weak TIM8TRGCOMTIM14IntHandler = DefaultIntHandler
#pragma weak TIM8CCIntHandler = DefaultIntHandler
#pragma weak ADC3IntHandler = DefaultIntHandler
#pragma weak FSMCIntHandler = DefaultIntHandler
#pragma weak SDIOIntHandler = DefaultIntHandler
#pragma weak TIM5IntHandler = DefaultIntHandler 
#pragma weak SPI3IntHandler = DefaultIntHandler 
#pragma weak UART4IntHandler = DefaultIntHandler 
#pragma weak UART5IntHandler = DefaultIntHandler 
#pragma weak TIM6IntHandler = DefaultIntHandler 
#pragma weak TIM7IntHandler = DefaultIntHandler 
#pragma weak DMA2Channel1IntHandler = DefaultIntHandler 
#pragma weak DMA2Channel2IntHandler = DefaultIntHandler 
#pragma weak DMA2Channel3IntHandler = DefaultIntHandler 
#pragma weak DMA2Channel4IntHandler = DefaultIntHandler 
#pragma weak DMA2Channel5IntHandler = DefaultIntHandler 
#pragma weak ETHIntHandler = DefaultIntHandler 
#pragma weak ETHWKUPIntHandler = DefaultIntHandler 
#pragma weak CAN2TXIntHandler = DefaultIntHandler 
#pragma weak CAN2RX0IntHandler = DefaultIntHandler 
#pragma weak CAN2RX1IntHandler = DefaultIntHandler 
#pragma weak CAN2SCEIntHandler = DefaultIntHandler 
#pragma weak OTGFSIntHandler = DefaultIntHandler 
  

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


