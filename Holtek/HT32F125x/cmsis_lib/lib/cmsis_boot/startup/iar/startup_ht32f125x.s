;/*---------------------------------------------------------------------------------------------------------*/
;/* Holtek Semiconductor Inc.                                                                               */
;/*                                                                                                         */
;/* Copyright (c) 2011 by Holtek Semiconductor Inc.                                                         */
;/* All rights reserved.                                                                                    */
;/*                                                                                                         */
;/*-----------------------------------------------------------------------------------------------------------
;  File Name        : startup_ht32f125x.s
;  Version          : V1.0
;  Date[mm/dd/yyyy] : 04/11/2011
;  Description      : Startup code.
;-----------------------------------------------------------------------------------------------------------*/

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit        
        PUBLIC  __vector_table

;*******************************************************************************
; Fill-up the Vector Table entries with the exceptions ISR address
;*******************************************************************************
        DATA

__vector_table           

        DCD  sfe(CSTACK)                        ; Top address of Stack
        DCD  Reset_Handler                      ; Reset Handler
        DCD  NMI_Handler                        ; NMI Handler
        DCD  HardFault_Handler                  ; Hard Fault Handler
        DCD  MemManage_Handler                  ; Memory Management Fault Handler
        DCD  BusFault_Handler                   ; Bus Fault Handler
        DCD  UsageFault_Handler                 ; Usage Fault Handler
        DCD  0                                  ; Reserved
        DCD  0                                  ; Reserved
        DCD  0                                  ; Reserved
        DCD  0                                  ; Reserved
        DCD  SVC_Handler                        ; SVC Handler
        DCD  DebugMon_Handler                   ; Debug Monitor Handler
        DCD  0                                  ; Reserved
        DCD  PendSV_Handler                     ; PendSV Handler
        DCD  SysTick_Handler                    ; SysTick Handler
        
        ; External Interrupt Handler
        DCD  CKRDY_IRQHandler
        DCD  LVD_IRQHandler
        DCD  BOD_IRQHandler
        DCD  WDT_IRQHandler
        DCD  RTC_IRQHandler
        DCD  FLASH_IRQHandler                    
        DCD  EVWUP_IRQHandler
        DCD  LPWUP_IRQHandler
        DCD  EXTI0_IRQHandler
        DCD  EXTI1_IRQHandler
        DCD  EXTI2_IRQHandler
        DCD  EXTI3_IRQHandler
        DCD  EXTI4_IRQHandler
        DCD  EXTI5_IRQHandler
        DCD  EXTI6_IRQHandler
        DCD  EXTI7_IRQHandler
        DCD  EXTI8_IRQHandler
        DCD  EXTI9_IRQHandler
        DCD  EXTI10_IRQHandler
        DCD  EXTI11_IRQHandler
        DCD  EXTI12_IRQHandler
        DCD  EXTI13_IRQHandler
        DCD  EXTI14_IRQHandler
        DCD  EXTI15_IRQHandler
        DCD  COMP_IRQHandler
        DCD  ADC_IRQHandler
        DCD  0
        DCD  0
        DCD  0
        DCD  0
        DCD  0
        DCD  0
        DCD  0
        DCD  0
        DCD  0
        DCD  GPTM0_IRQHandler
        DCD  GPTM1_IRQHandler
        DCD  0
        DCD  0
        DCD  0
        DCD  0
        DCD  0
        DCD  0
        DCD  I2C_IRQHandler
        DCD  0
        DCD  SPI_IRQHandler
        DCD  0
        DCD  USART_IRQHandler
                    
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0
        
        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER(1)
SysTick_Handler
        B SysTick_Handler


        PUBWEAK CKRDY_IRQHandler
        SECTION .text:CODE:REORDER(1)
CKRDY_IRQHandler
        B CKRDY_IRQHandler

        PUBWEAK LVD_IRQHandler
        SECTION .text:CODE:REORDER(1)
LVD_IRQHandler
        B LVD_IRQHandler
        
        PUBWEAK BOD_IRQHandler
        SECTION .text:CODE:REORDER(1)
BOD_IRQHandler
        B BOD_IRQHandler

        PUBWEAK WDT_IRQHandler
        SECTION .text:CODE:REORDER(1)
WDT_IRQHandler
        B WDT_IRQHandler

        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:REORDER(1)
FLASH_IRQHandler
        B FLASH_IRQHandler

        PUBWEAK EVWUP_IRQHandler
        SECTION .text:CODE:REORDER(1)
EVWUP_IRQHandler
        B EVWUP_IRQHandler
        
        PUBWEAK LPWUP_IRQHandler
        SECTION .text:CODE:REORDER(1)
LPWUP_IRQHandler
        B LPWUP_IRQHandler

        PUBWEAK EXTI0_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI0_IRQHandler
        B EXTI0_IRQHandler

        PUBWEAK EXTI1_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI1_IRQHandler
        B EXTI1_IRQHandler

        PUBWEAK EXTI2_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI2_IRQHandler
        B EXTI2_IRQHandler

        PUBWEAK EXTI3_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI3_IRQHandler
        B EXTI3_IRQHandler

        PUBWEAK EXTI4_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI4_IRQHandler
        B EXTI4_IRQHandler

        PUBWEAK EXTI5_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI5_IRQHandler
        B EXTI5_IRQHandler

        PUBWEAK EXTI6_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI6_IRQHandler
        B EXTI6_IRQHandler

        PUBWEAK EXTI7_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI7_IRQHandler
        B EXTI7_IRQHandler

        PUBWEAK EXTI8_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI8_IRQHandler
        B EXTI8_IRQHandler

        PUBWEAK EXTI9_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI9_IRQHandler
        B EXTI9_IRQHandler

        PUBWEAK EXTI10_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI10_IRQHandler
        B EXTI10_IRQHandler

        PUBWEAK EXTI11_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI11_IRQHandler
        B EXTI11_IRQHandler

        PUBWEAK EXTI12_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI12_IRQHandler
        B EXTI12_IRQHandler

        PUBWEAK EXTI13_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI13_IRQHandler
        B EXTI13_IRQHandler

        PUBWEAK EXTI14_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI14_IRQHandler
        B EXTI14_IRQHandler

        PUBWEAK EXTI15_IRQHandler
        SECTION .text:CODE:REORDER(1)
EXTI15_IRQHandler
        B EXTI15_IRQHandler

        PUBWEAK COMP_IRQHandler
        SECTION .text:CODE:REORDER(1)
COMP_IRQHandler
        B COMP_IRQHandler

        PUBWEAK ADC_IRQHandler
        SECTION .text:CODE:REORDER(1)
ADC_IRQHandler
        B ADC_IRQHandler

        PUBWEAK GPTM0_IRQHandler
        SECTION .text:CODE:REORDER(1)
GPTM0_IRQHandler
        B GPTM0_IRQHandler

        PUBWEAK GPTM1_IRQHandler
        SECTION .text:CODE:REORDER(1)
GPTM1_IRQHandler
        B GPTM1_IRQHandler

        PUBWEAK I2C_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2C_IRQHandler
        B I2C_IRQHandler

        PUBWEAK SPI_IRQHandler
        SECTION .text:CODE:REORDER(1)
SPI_IRQHandler
        B SPI_IRQHandler

        PUBWEAK USART_IRQHandler
        SECTION .text:CODE:REORDER(1)
USART_IRQHandler
        B USART_IRQHandler

        END
