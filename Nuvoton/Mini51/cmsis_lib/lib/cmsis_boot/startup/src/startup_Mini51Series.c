//*****************************************************************************
//
//! \file startup_M051Series.c
//! \author Nuvoton
//! \version v1.02.002
//! \date 21/09/2011
//! \brief M051Series Devices Startup code.
//!           This module performs:
//!               - Set the initial SP
//!               - Set the vector table entries with the exceptions ISR address
//!               - Initialize data and bss
//!               - Setup the microcontroller system.             
//!               - Call the application's entry point.
//!            After Reset the Cortex-M0 processor is in Thread mode,
//!            priority is Privileged, and the Stack is set to Main.
//
//*****************************************************************************
 
//*****************************************************************************
//
//! Stack Configuration
//
//***************************************************************************** 

//
//! Stack size (in Words)    
//
#define STACK_SIZE       0x00000100
__attribute__ ((section(".co_stack")))
unsigned long pulStack[STACK_SIZE];      

//*****************************************************************************
//
//! Macro definition
//
//***************************************************************************** 

#define WEAK __attribute__ ((weak))           

//*****************************************************************************
//
//! Declaration of the default fault handlers
//
//***************************************************************************** 

//
//! System exception vector handler
//
void WEAK  Reset_Handler(void);
void WEAK  NMI_Handler(void);
void WEAK  HardFault_Handler(void);
void WEAK  SVC_Handler(void);
void WEAK  PendSV_Handler(void);
void WEAK  SysTick_Handler(void);
void WEAK  BOD_IRQHandler(void);  
void WEAK  WDT_IRQHandler(void);  
void WEAK  EINT0_IRQHandler(void);
void WEAK  EINT1_IRQHandler(void);
void WEAK  GPIO01_IRQHandler(void);
void WEAK  GPIO234_IRQHandler(void);
void WEAK  PWM_IRQHandler(void);
void WEAK  TMR0_IRQHandler(void); 
void WEAK  TMR1_IRQHandler(void);
void WEAK  UART0_IRQHandler(void);
void WEAK  SPI0_IRQHandler(void); 
void WEAK  I2C_IRQHandler(void); 
void WEAK  PDWU_IRQHandler(void);
void WEAK  ADC_IRQHandler(void);
void WEAK  ACMP_IRQHandler(void);
void WEAK  FB_IRQHandler(void);
void WEAK  GPIO5_IRQHandler(void);
void WEAK  HIRC_IRQHandler(void);

//*****************************************************************************
//
//! Symbols defined in linker script
//
//*****************************************************************************

//
//! Start address for the initialization values of the .data section. 
// 
extern unsigned long _sidata;    

//
//! Start address for the .data section 
//
extern unsigned long _sdata;    

//
//! End address for the .data section
// 
extern unsigned long _edata;     

//
//! Start address for the .bss section 
//  
extern unsigned long _sbss;     

//
//! End address for the .bss section
//
extern unsigned long _ebss;     

//
//! End address for ram 
//    
extern void _eram;        

//*****************************************************************************
//
//! Function prototypes
//
//*****************************************************************************

//
//! The entry point for the application.
//
extern int main(void);       

//
//! Setup the microcontroller system(CMSIS) 
//
extern void SystemInit(void);  

//
//! Default reset handler 
//
void Default_Reset_Handler(void);  

//
//! Default exception handler
//
static void Default_Handler(void);  

//*****************************************************************************
//
//! \brief The minimal vector table for a Cortex M0.  Note that the proper constructs
//!        must be placed on this to ensure that it ends up at physical address
//!        0x00000000.  
//
//*****************************************************************************
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
  //***************************************************************************
  //
  //! Core Exceptions
  //
  //***************************************************************************

  //
  //! The initial stack pointer
  //
  (void *)&pulStack[STACK_SIZE],    
 
  //
  //! The reset handler
  //
  Reset_Handler,                     
  
  //
  //! The NMI handler
  //
  NMI_Handler,                         
  
  //
  //! The hard fault handler
  //
  HardFault_Handler, 
  
  // 
  //! Reserved
  //
  0,0,0,0,0,0,0,

  //
  //! SVCall handler
  //
  SVC_Handler,  

  // 
  //! Reserved
  // 
  0,0, 
  
  //
  //! The PendSV handler 
  //
  PendSV_Handler,  
 
  //
  //! The SysTick handler 
  //
  SysTick_Handler, 
  
  //***************************************************************************
  //
  //! External Exceptions
  //
  //***************************************************************************
  BOD_IRQHandler,  
  WDT_IRQHandler,  
  EINT0_IRQHandler,
  EINT1_IRQHandler,
  GPIO01_IRQHandler,
  GPIO234_IRQHandler,
  PWM_IRQHandler,
  FB_IRQHandler,
  TMR0_IRQHandler, 
  TMR1_IRQHandler,
  Default_Handler,
  Default_Handler,
  UART0_IRQHandler,
  Default_Handler,
  SPI0_IRQHandler, 
  Default_Handler,
  GPIO5_IRQHandler,
  HIRC_IRQHandler,
  I2C_IRQHandler, 
  Default_Handler, 
  Default_Handler, 
  Default_Handler,
  Default_Handler, 
  Default_Handler,  
  Default_Handler,  
  ACMP_IRQHandler,
  Default_Handler,
  Default_Handler,
  PDWU_IRQHandler,
  ADC_IRQHandler,
  Default_Handler,  
  Default_Handler, 
};


//*****************************************************************************
//
//! \brief  This is the code that gets called when the processor first
//!         starts execution following a reset event. Only the absolutely
//!         necessary set is performed, after which the application
//!         supplied main() routine is called. 
//! \param  None
//! \retval None
//!
//*****************************************************************************
void Default_Reset_Handler(void)
{
  /* Initialize data and bss */
  unsigned long *pulSrc, *pulDest;

  /* Copy the data segment initializers from flash to SRAM */
  pulSrc = &_sidata;

  for(pulDest = &_sdata; pulDest < &_edata; )
  {
    *(pulDest++) = *(pulSrc++);
  }
  
  /* Zero fill the bss segment. */
  for(pulDest = &_sbss; pulDest < &_ebss; )
  {
    *(pulDest++) = 0;
  }

  /* Setup the microcontroller system. */
  SystemInit();
    
  /* Call the application's entry point.*/
  main();
}



//*****************************************************************************
//
//! \brief Provide weak aliases for each Exception handler to the Default_Handler. 
//!        As they are weak aliases, any function with the same name will override 
//!        this definition.
//
//*****************************************************************************
  
#pragma weak Reset_Handler = Default_Reset_Handler
#pragma weak NMI_Handler = Default_Handler
#pragma weak HardFault_Handler = Default_Handler
#pragma weak SVC_Handler = Default_Handler
#pragma weak PendSV_Handler = Default_Handler
#pragma weak SysTick_Handler = Default_Handler
#pragma weak BOD_IRQHandler = Default_Handler  
#pragma weak WDT_IRQHandler = Default_Handler  
#pragma weak EINT0_IRQHandler = Default_Handler
#pragma weak EINT1_IRQHandler = Default_Handler
#pragma weak GPIOP0P1_IRQHandler = Default_Handler 
#pragma weak GPIOP2P3P4_IRQHandler = Default_Handler
#pragma weak PWMA_IRQHandler = Default_Handler 
#pragma weak PWMB_IRQHandler = Default_Handler 
#pragma weak TMR0_IRQHandler = Default_Handler 
#pragma weak TMR1_IRQHandler = Default_Handler 
#pragma weak TMR2_IRQHandler = Default_Handler 
#pragma weak TMR3_IRQHandler = Default_Handler 
#pragma weak UART0_IRQHandler = Default_Handler
#pragma weak UART1_IRQHandler = Default_Handler
#pragma weak SPI0_IRQHandler = Default_Handler 
#pragma weak SPI1_IRQHandler = Default_Handler 
#pragma weak SPI2_IRQHandler = Default_Handler 
#pragma weak SPI3_IRQHandler = Default_Handler 
#pragma weak I2C_IRQHandler = Default_Handler 
#pragma weak USBD_IRQHandler = Default_Handler  
#pragma weak PS2_IRQHandler = Default_Handler  
#pragma weak PDMA_IRQHandler = Default_Handler
#pragma weak I2S_IRQHandler = Default_Handler
#pragma weak PWRWU_IRQHandler = Default_Handler
#pragma weak ADC_IRQHandler = Default_Handler

//*****************************************************************************
//
//! \brief  This is the code that gets called when the processor receives an 
//!         unexpected interrupt.  This simply enters an infinite loop, 
//!         preserving the system state for examination by a debugger.
//! \param  None
//! \retval None 
// 
//*****************************************************************************
static void Default_Handler(void) 
{
  //
  //! Go into an infinite loop. 
  //
  while (1) 
  {
  }
}

//*****************************************************************************
//
// Copyright(c) 2009 Nuvoton Technology Corp. All rights reserved.  
//
//*****************************************************************************
