/**
 ******************************************************************************
 * @file      startup_Cortex_M4.c
 * @author    Coocox
 * @version   V1.0
 * @date      06/06/2014
 * @brief     Cortex M4 Devices Startup code.
 *            This module performs:
 *                - Set the initial SP
 *                - Set the vector table entries with the exceptions ISR address
 *                - Initialize data and bss
 *                - Call the application's entry point.
 *            After Reset the Cortex-M4 processor is in Thread mode,
 *            priority is Privileged, and the Stack is set to Main.
 *******************************************************************************
 */
 
//#ifdef __cplusplus
// extern "C" {
//#endif

/*----------Stack Configuration-----------------------------------------------*/  
#define STACK_SIZE       0x00000800      /*!< Stack size (in Words)           */
__attribute__ ((section(".co_stack")))
unsigned long pulStack[STACK_SIZE];      


/*----------Macro definition--------------------------------------------------*/  
#define WEAK __attribute__ ((weak))           


/*----------Declaration of the default fault handlers-------------------------*/  
/* System exception vector handler */
__attribute__ ((used))
void WEAK  Reset_Handler(void);   
void WEAK  NMI_Handler(void);       
void WEAK  HardFault_Handler(void); 
void WEAK  MemManage_Handler(void); 
void WEAK  BusFault_Handler(void);  
void WEAK  UsageFault_Handler(void);
void WEAK  SVC_Handler(void);       
void WEAK  DebugMon_Handler(void);  
void WEAK  PendSV_Handler(void);    
void WEAK  SysTick_Handler(void);   

void WEAK  BOD_IRQHandler(void);
void WEAK  IRC_IRQHandler(void);
void WEAK  PWRWU_IRQHandler(void);
void WEAK  SRAMF_IRQHandler(void);
void WEAK  CLKF_IRQHandler(void);
void WEAK  RTC_IRQHandler(void);
void WEAK  TAMPER_IRQHandler(void);
void WEAK  EINT0_IRQHandler(void);
void WEAK  EINT1_IRQHandler(void);
void WEAK  EINT2_IRQHandler(void);
void WEAK  EINT3_IRQHandler(void);
void WEAK  EINT4_IRQHandler(void);
void WEAK  EINT5_IRQHandler(void);
void WEAK  EINT6_IRQHandler(void);
void WEAK  EINT7_IRQHandler(void);
void WEAK  GPA_IRQHandler(void);
void WEAK  GPB_IRQHandler(void);
void WEAK  GPC_IRQHandler(void);
void WEAK  GPD_IRQHandler(void);
void WEAK  GPE_IRQHandler(void);
void WEAK  GPF_IRQHandler(void);
void WEAK  GPG_IRQHandler(void);
void WEAK  GPH_IRQHandler(void);
void WEAK  GPI_IRQHandler(void);
void WEAK  TMR0_IRQHandler(void);
void WEAK  TMR1_IRQHandler(void);
void WEAK  TMR2_IRQHandler(void);
void WEAK  TMR3_IRQHandler(void);
void WEAK  PDMA_IRQHandler(void);
void WEAK  ADC_IRQHandler(void);
void WEAK  WDT_IRQHandler(void);
void WEAK  WWDT_IRQHandler(void);
void WEAK  EADC0_IRQHandler(void);
void WEAK  EADC1_IRQHandler(void);
void WEAK  EADC2_IRQHandler(void);
void WEAK  EADC3_IRQHandler(void);
void WEAK  ACMP_IRQHandler(void);
void WEAK  OPA0_IRQHandler(void);
void WEAK  OPA1_IRQHandler(void);
void WEAK  ICAP0_IRQHandler(void);
void WEAK  ICAP1_IRQHandler(void);
void WEAK  PWM0CH0_IRQHandler(void);
void WEAK  PWM0CH1_IRQHandler(void);
void WEAK  PWM0CH2_IRQHandler(void);
void WEAK  PWM0CH3_IRQHandler(void);
void WEAK  PWM0CH4_IRQHandler(void);
void WEAK  PWM0CH5_IRQHandler(void);
void WEAK  PWM0_BRK_IRQHandler(void);
void WEAK  QEI0_IRQHandler(void);
void WEAK  PWM1CH0_IRQHandler(void);
void WEAK  PWM1CH1_IRQHandler(void);
void WEAK  PWM1CH2_IRQHandler(void);
void WEAK  PWM1CH3_IRQHandler(void);
void WEAK  PWM1CH4_IRQHandler(void);
void WEAK  PWM1CH5_IRQHandler(void);
void WEAK  PWM1_BRK_IRQHandler(void);
void WEAK  QEI1_IRQHandler(void);
void WEAK  EPWM0_IRQHandler(void);
void WEAK  EPWM0BRK_IRQHandler(void);
void WEAK  EPWM1_IRQHandler(void);
void WEAK  EPWM1BRK_IRQHandler(void);
void WEAK  USBD_IRQHandler(void);
void WEAK  USBH_IRQHandler(void);
void WEAK  USB_OTG_IRQHandler(void);
void WEAK  EMAC_TX_IRQHandler(void);
void WEAK  EMAC_RX_IRQHandler(void);
void WEAK  SPI0_IRQHandler(void);
void WEAK  SPI1_IRQHandler(void);
void WEAK  SPI2_IRQHandler(void);
void WEAK  SPI3_IRQHandler(void);
void WEAK  UART0_IRQHandler(void);
void WEAK  UART1_IRQHandler(void);
void WEAK  UART2_IRQHandler(void);
void WEAK  UART3_IRQHandler(void);
void WEAK  UART4_IRQHandler(void);
void WEAK  UART5_IRQHandler(void);
void WEAK  I2C0_IRQHandler(void);
void WEAK  I2C1_IRQHandler(void);
void WEAK  I2C2_IRQHandler(void);
void WEAK  I2C3_IRQHandler(void);
void WEAK  I2C4_IRQHandler(void);
void WEAK  SC0_IRQHandler(void);
void WEAK  SC1_IRQHandler(void);
void WEAK  SC2_IRQHandler(void);
void WEAK  SC3_IRQHandler(void);
void WEAK  SC4_IRQHandler(void);
void WEAK  SC5_IRQHandler(void);
void WEAK  CAN0_IRQHandler(void);
void WEAK  CAN1_IRQHandler(void);
void WEAK  I2S0_IRQHandler(void);
void WEAK  I2S1_IRQHandler(void);
void WEAK  SD_IRQHandler(void);
void WEAK  PS2D_IRQHandler(void);
void WEAK  CAP_IRQHandler(void);
void WEAK  CRYPTO_IRQHandler(void);
void WEAK  CRC_IRQHandler(void);

/*----------Symbols defined in linker script----------------------------------*/  
extern unsigned long _sidata;    /*!< Start address for the initialization 
                                      values of the .data section.            */
extern unsigned long _sdata;     /*!< Start address for the .data section     */    
extern unsigned long _edata;     /*!< End address for the .data section       */    
extern unsigned long _sbss;      /*!< Start address for the .bss section      */
extern unsigned long _ebss;      /*!< End address for the .bss section        */      
extern void _eram;               /*!< End address for ram                     */


/*----------Function prototypes-----------------------------------------------*/  
extern int main(void);           /*!< The entry point for the application.    */
void Default_Reset_Handler(void);   /*!< Default reset handler                */
static void Default_Handler(void);  /*!< Default exception handler            */


/**
  *@brief The minimal vector table for a Cortex M4.  Note that the proper constructs
  *       must be placed on this to ensure that it ends up at physical address
  *       0x00000000.  
  */
__attribute__ ((used,section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{	
  /*----------Core Exceptions------------------------------------------------ */
  (void *)&pulStack[STACK_SIZE-1],     /*!< The initial stack pointer         */
  Reset_Handler,             /*!< Reset Handler                               */
  NMI_Handler,               /*!< NMI Handler                                 */
  HardFault_Handler,         /*!< Hard Fault Handler                          */
  MemManage_Handler,         /*!< MPU Fault Handler                           */
  BusFault_Handler,          /*!< Bus Fault Handler                           */
  UsageFault_Handler,        /*!< Usage Fault Handler                         */
  0,0,0,0,                   /*!< Reserved                                    */
  SVC_Handler,               /*!< SVCall Handler                              */
  DebugMon_Handler,          /*!< Debug Monitor Handler                       */
  0,                         /*!< Reserved                                    */
  PendSV_Handler,            /*!< PendSV Handler                              */
  SysTick_Handler,           /*!< SysTick Handler                             */
  BOD_IRQHandler,
  IRC_IRQHandler,
  PWRWU_IRQHandler,
  SRAMF_IRQHandler,
  CLKF_IRQHandler,
  0,
  RTC_IRQHandler,
  TAMPER_IRQHandler,
  EINT0_IRQHandler,
  EINT1_IRQHandler,
  EINT2_IRQHandler,
  EINT3_IRQHandler,
  EINT4_IRQHandler,
  EINT5_IRQHandler,
  EINT6_IRQHandler,
  EINT7_IRQHandler,
  GPA_IRQHandler,
  GPB_IRQHandler,
  GPC_IRQHandler,
  GPD_IRQHandler,
  GPE_IRQHandler,
  GPF_IRQHandler,
  GPG_IRQHandler,
  GPH_IRQHandler,
  GPI_IRQHandler,
  0,0,0,0,0,0,0,
  TMR0_IRQHandler,
  TMR1_IRQHandler,
  TMR2_IRQHandler,
  TMR3_IRQHandler,
  0,0,0,0,
  PDMA_IRQHandler,
  0,
  ADC_IRQHandler,
  0,0,0,
  WDT_IRQHandler,
  WWDT_IRQHandler,
  EADC0_IRQHandler,
  EADC1_IRQHandler,
  EADC2_IRQHandler,
  EADC3_IRQHandler,
  0,0,0,0,
  ACMP_IRQHandler,
  0,0,0,
  OPA0_IRQHandler,
  OPA1_IRQHandler,
  ICAP0_IRQHandler,
  ICAP1_IRQHandler,
  PWM0CH0_IRQHandler,
  PWM0CH1_IRQHandler,
  PWM0CH2_IRQHandler,
  PWM0CH3_IRQHandler,
  PWM0CH4_IRQHandler,
  PWM0CH5_IRQHandler,
  PWM0_BRK_IRQHandler,
  QEI0_IRQHandler,
  PWM1CH0_IRQHandler,
  PWM1CH1_IRQHandler,
  PWM1CH2_IRQHandler,
  PWM1CH3_IRQHandler,
  PWM1CH4_IRQHandler,
  PWM1CH5_IRQHandler,
  PWM1_BRK_IRQHandler,
  QEI1_IRQHandler,
  EPWM0_IRQHandler,
  EPWM0BRK_IRQHandler,
  EPWM1_IRQHandler,
  EPWM1BRK_IRQHandler,
  0,0,0,0,
  USBD_IRQHandler,
  USBH_IRQHandler,
  USB_OTG_IRQHandler,
  0,
  EMAC_TX_IRQHandler,
  EMAC_RX_IRQHandler,
  0,0,
  SPI0_IRQHandler,
  SPI1_IRQHandler,
  SPI2_IRQHandler,
  SPI3_IRQHandler,
  0,0,0,0,
  UART0_IRQHandler,
  UART1_IRQHandler,
  UART2_IRQHandler,
  UART3_IRQHandler,
  UART4_IRQHandler,
  UART5_IRQHandler,
  0,0,
  I2C0_IRQHandler,
  I2C1_IRQHandler,
  I2C2_IRQHandler,
  I2C3_IRQHandler,
  I2C4_IRQHandler,
  0,0,0,
  SC0_IRQHandler,
  SC1_IRQHandler,
  SC2_IRQHandler,
  SC3_IRQHandler,
  SC4_IRQHandler,
  SC5_IRQHandler,
  0,0,
  CAN0_IRQHandler,
  CAN1_IRQHandler,
  0,0,
  I2S0_IRQHandler,
  I2S1_IRQHandler,
  0,0,
  SD_IRQHandler,
  0,
  PS2D_IRQHandler,
  CAP_IRQHandler,
  CRYPTO_IRQHandler,
  CRC_IRQHandler,
  /*----------External Exceptions---------------------------------------------*/
};


/**
  * @brief  This is the code that gets called when the processor first
  *         starts execution following a reset event. Only the absolutely
  *         necessary set is performed, after which the application
  *         supplied main() routine is called. 
  * @param  None
  * @retval None
  */
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
  
  /* Zero fill the bss segment.  This is done with inline assembly since this
     will clear the value of pulDest if it is not kept in a register. */
  __asm("  ldr     r0, =_sbss\n"
        "  ldr     r1, =_ebss\n"
        "  mov     r2, #0\n"
        "  .thumb_func\n"
        "zero_loop:\n"
        "    cmp     r0, r1\n"
        "    it      lt\n"
        "    strlt   r2, [r0], #4\n"
        "    blt     zero_loop");

#ifdef __FPU_USED
  /* Enable FPU.*/
  __asm("  LDR.W R0, =0xE000ED88\n"
        "  LDR R1, [R0]\n"
        "  ORR R1, R1, #(0xF << 20)\n"
        "  STR R1, [R0]");
#endif

#ifdef SUPPORT_CPLUSPLUS
    extern void __libc_init_array(void);
    __libc_init_array();
#endif
	
    /* Call the application's entry point.*/
    main();
}


/**
  *@brief Provide weak aliases for each Exception handler to the Default_Handler. 
  *       As they are weak aliases, any function with the same name will override 
  *       this definition.
  */
#pragma weak Reset_Handler = Default_Reset_Handler
#pragma weak NMI_Handler = Default_Handler     
#pragma weak HardFault_Handler = Default_Handler     
#pragma weak MemManage_Handler = Default_Handler     
#pragma weak BusFault_Handler = Default_Handler      
#pragma weak UsageFault_Handler = Default_Handler    
#pragma weak SVC_Handler = Default_Handler           
#pragma weak DebugMon_Handler = Default_Handler      
#pragma weak PendSV_Handler = Default_Handler        
#pragma weak SysTick_Handler = Default_Handler  
    
#pragma weak  BOD_IRQHandler= Default_Handler
#pragma weak  IRC_IRQHandler= Default_Handler
#pragma weak  PWRWU_IRQHandler= Default_Handler
#pragma weak  SRAMF_IRQHandler= Default_Handler
#pragma weak  CLKF_IRQHandler= Default_Handler
#pragma weak  RTC_IRQHandler= Default_Handler
#pragma weak  TAMPER_IRQHandler= Default_Handler
#pragma weak  EINT0_IRQHandler= Default_Handler
#pragma weak  EINT1_IRQHandler= Default_Handler
#pragma weak  EINT2_IRQHandler= Default_Handler
#pragma weak  EINT3_IRQHandler= Default_Handler
#pragma weak  EINT4_IRQHandler= Default_Handler
#pragma weak  EINT5_IRQHandler= Default_Handler
#pragma weak  EINT6_IRQHandler= Default_Handler
#pragma weak  EINT7_IRQHandler= Default_Handler
#pragma weak  GPA_IRQHandler= Default_Handler
#pragma weak  GPB_IRQHandler= Default_Handler
#pragma weak  GPC_IRQHandler= Default_Handler
#pragma weak  GPD_IRQHandler= Default_Handler
#pragma weak  GPE_IRQHandler= Default_Handler
#pragma weak  GPF_IRQHandler= Default_Handler
#pragma weak  GPG_IRQHandler= Default_Handler
#pragma weak  GPH_IRQHandler= Default_Handler
#pragma weak  GPI_IRQHandler= Default_Handler
#pragma weak  TMR0_IRQHandler= Default_Handler
#pragma weak  TMR1_IRQHandler= Default_Handler
#pragma weak  TMR2_IRQHandler= Default_Handler
#pragma weak  TMR3_IRQHandler= Default_Handler
#pragma weak  PDMA_IRQHandler= Default_Handler
#pragma weak  ADC_IRQHandler= Default_Handler
#pragma weak  WDT_IRQHandler= Default_Handler
#pragma weak  WWDT_IRQHandler= Default_Handler
#pragma weak  EADC0_IRQHandler= Default_Handler
#pragma weak  EADC1_IRQHandler= Default_Handler
#pragma weak  EADC2_IRQHandler= Default_Handler
#pragma weak  EADC3_IRQHandler= Default_Handler
#pragma weak  ACMP_IRQHandler= Default_Handler
#pragma weak  OPA0_IRQHandler= Default_Handler
#pragma weak  OPA1_IRQHandler= Default_Handler
#pragma weak  ICAP0_IRQHandler= Default_Handler
#pragma weak  ICAP1_IRQHandler= Default_Handler
#pragma weak  PWM0CH0_IRQHandler= Default_Handler
#pragma weak  PWM0CH1_IRQHandler= Default_Handler
#pragma weak  PWM0CH2_IRQHandler= Default_Handler
#pragma weak  PWM0CH3_IRQHandler= Default_Handler
#pragma weak  PWM0CH4_IRQHandler= Default_Handler
#pragma weak  PWM0CH5_IRQHandler= Default_Handler
#pragma weak  PWM0_BRK_IRQHandler= Default_Handler
#pragma weak  QEI0_IRQHandler= Default_Handler
#pragma weak  PWM1CH0_IRQHandler= Default_Handler
#pragma weak  PWM1CH1_IRQHandler= Default_Handler
#pragma weak  PWM1CH2_IRQHandler= Default_Handler
#pragma weak  PWM1CH3_IRQHandler= Default_Handler
#pragma weak  PWM1CHCH4_IRQHandler= Default_Handler
#pragma weak  PWM1CH5_IRQHandler= Default_Handler
#pragma weak  PWM1_BRK_IRQHandler= Default_Handler
#pragma weak  QEI1_IRQHandler= Default_Handler
#pragma weak  EPWM0_IRQHandler= Default_Handler
#pragma weak  EPWM0BRK_IRQHandler= Default_Handler
#pragma weak  EPWM1_IRQHandler= Default_Handler
#pragma weak  EPWM1BRK_IRQHandler= Default_Handler
#pragma weak  USBD_IRQHandler= Default_Handler
#pragma weak  USBH_IRQHandler= Default_Handler
#pragma weak  USB_OTG_IRQHandler= Default_Handler
#pragma weak  EMAC_TX_IRQHandler= Default_Handler
#pragma weak  EMAC_RX_IRQHandler= Default_Handler
#pragma weak  SPI0_IRQHandler= Default_Handler
#pragma weak  SPI1_IRQHandler= Default_Handler
#pragma weak  SPI2_IRQHandler= Default_Handler
#pragma weak  SPI3_IRQHandler= Default_Handler
#pragma weak  UART0_IRQHandler= Default_Handler
#pragma weak  UART1_IRQHandler= Default_Handler
#pragma weak  UART2_IRQHandler= Default_Handler
#pragma weak  UART3_IRQHandler= Default_Handler
#pragma weak  UART4_IRQHandler= Default_Handler
#pragma weak  UART5_IRQHandler= Default_Handler
#pragma weak  I2C0_IRQHandler= Default_Handler
#pragma weak  I2C1_IRQHandler= Default_Handler
#pragma weak  I2C2_IRQHandler= Default_Handler
#pragma weak  I2C3_IRQHandler= Default_Handler
#pragma weak  I2C4_IRQHandler= Default_Handler
#pragma weak  SC0_IRQHandler= Default_Handler
#pragma weak  SC1_IRQHandler= Default_Handler
#pragma weak  SC2_IRQHandler= Default_Handler
#pragma weak  SC3_IRQHandler= Default_Handler
#pragma weak  SC4_IRQHandler= Default_Handler
#pragma weak  SC5_IRQHandler= Default_Handler
#pragma weak  CAN0_IRQHandler= Default_Handler
#pragma weak  CAN1_IRQHandler= Default_Handler
#pragma weak  I2S0_IRQHandler= Default_Handler
#pragma weak  I2S1_IRQHandler= Default_Handler
#pragma weak  SD_IRQHandler= Default_Handler
#pragma weak  PS2D_IRQHandler= Default_Handler
#pragma weak  CAP_IRQHandler= Default_Handler
#pragma weak  CRYPTO_IRQHandler= Default_Handler
#pragma weak  CRC_IRQHandler= Default_Handler

/**
  * @brief  This is the code that gets called when the processor receives an
  *         unexpected interrupt.  This simply enters an infinite loop,
  *         preserving the system state for examination by a debugger.
  * @param  None
  * @retval None
  */
static void Default_Handler(void)
{
    /* Go into an infinite loop. */
    while (1)
    {
    }
}

//#ifdef __cplusplus
//}
//#endif

/*********************** (C) COPYRIGHT 2014 Coocox ************END OF FILE*****/
