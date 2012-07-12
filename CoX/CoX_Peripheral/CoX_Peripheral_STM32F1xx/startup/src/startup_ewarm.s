;//*****************************************************************************
;//
;//! \file startup_ewarm.s
;//! \brief STM32F1xx Devices Startup code for EWARM.
;//!        This module performs:
;//!           - Set the initial SP
;//!           - Set the vector table entries with the exceptions ISR address
;//!           - Initialize data and bss
;//!           - Setup the microcontroller system. 			
;//!           - Call the application's entry point.
;//!           .
;//! \version V2.1.1.1
;//! \date 5/24/2012
;//! \author CooCox
;//! \copy
;//!
;//! Copyright (c)  2011, CooCox 
;//! All rights reserved.
;//! 
;//! Redistribution and use in source and binary forms, with or without 
;//! modification, are permitted provided that the following conditions 
;//! are met: 
;//! 
;//!     * Redistributions of source code must retain the above copyright 
;//! notice, this list of conditions and the following disclaimer. 
;//!     * Redistributions in binary form must reproduce the above copyright
;//! notice, this list of conditions and the following disclaimer in the
;//! documentation and/or other materials provided with the distribution. 
;//!     * Neither the name of the <ORGANIZATION> nor the names of its 
;//! contributors may be used to endorse or promote products derived 
;//! from this software without specific prior written permission. 
;//! 
;//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
;//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
;//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
;//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
;//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
;//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
;//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
;//! THE POSSIBILITY OF SUCH DAMAGE.
;//
;//*****************************************************************************

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)
        
        EXTERN  __iar_program_start
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)                 ; Top of Stack
        DCD     ResetHandler                ; Reset Handler
        DCD     NMIIntHandler               ; NMI Handler
        DCD     HardFaultIntHandler         ; Hard Fault Handler
        DCD     MemManageIntHandler         ; The MPU fault handler
        DCD     BusFaultIntHandler          ; The bus fault handler
        DCD     UsageFaultIntHandler        ; The usage fault handler
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVCIntHandler               ; SVCall Handler
        DCD     DebugMonIntHandler          ; Debug monitor handler
        DCD     0                           ; Reserved
        DCD     PendSVIntHandler            ; PendSV Handler
        DCD     SysTickIntHandler           ; SysTick Handler
        
                                            ; External Interrupts

        DCD     WWDGIntHandler              ; 0 Window Watchdog interrupt                 
        DCD     PVDIntHandler               ; 1 PVD through EXTI Line detection  
        DCD     TAMPERIntHandler            ; 2 Tamper interrupt 
        DCD     RTCIntHandler               ; 3 RTC global interrupt
        DCD     FLASHIntHandler             ; 4 Flash global interrupt
        DCD     RCCIntHandler               ; 5 RCC global interrupt
        DCD     EXTI0IntHandler             ; 6 EXTI Line0 interrupt
        DCD     EXTI1IntHandler             ; 7 EXTI Line1 interrupt 
        DCD     EXTI2IntHandler             ; 8 EXTI Line2 interrupt
        DCD     EXTI3IntHandler             ; 9 EXTI Line3 interrupt
        DCD     EXTI4IntHandler             ; 10 EXTI Line4 interrupt
        DCD     DMA1Channel1IntHandler      ; 11 DMA1 Channel1 global interrupt
        DCD     DMA1Channel2IntHandler      ; 12 DMA1 Channel2 global interrupt
        DCD     DMA1Channel3IntHandler      ; 13 DMA1 Channel3 global interrupt
        DCD     DMA1Channel4IntHandler      ; 14 DMA1 Channel4 global interrupt
        DCD     DMA1Channel5IntHandler      ; 15 DMA1 Channel5 global interrupt
        DCD     DMA1Channel6IntHandler      ; 16 DMA1 Channel6 global interrupt
        DCD     DMA1Channel7IntHandler      ; 17 DMA1 Channel7 global interrupt
        DCD     ADC12IntHandler             ; 18 ADC1 and ADC2 global interrupt
        DCD     CAN1TXIntHandler            ; 19 CAN1 TX interrupts
        DCD     CAN1RX0IntHandler           ; 20 CAN1 RX0 interrupts
        DCD     CAN1RX1IntHandler           ; 21 CAN1 RX1 interrupt
        DCD     CAN1SCEIntHandler           ; 22 CAN1 SCE interrupt 
        DCD     EXTI95IntHandler            ; 23 EXTI Line[9:5] interrupts 
        DCD     TIM1BRKTIM9IntHandler       ; 24 TIM1 Break interrupt
        DCD     TIM1UPTIM10IntHandler       ; 25 TIM1 Update interrupt
        DCD     TIM1TRGCOMTIM11IntHandler   ; 26 TIM1 Trigger and Commutation
        DCD     TIM1CCIntHandler            ; 27 TIM1 Capture Compare interrupt
        DCD     TIM2IntHandler              ; 28 TIM2 global interrupt
        DCD     TIM3IntHandler              ; 29 TIM3 global interrupt
        DCD     TIM4IntHandler              ; 30 TIM4 global interrupt
        DCD     I2C1EVIntHandler            ; 31 I2C1 event interrupt
        DCD     I2C1ERIntHandler            ; 32 I2C1 error interrupt
        DCD     I2C2EVIntHandler            ; 33 I2C2 event interrupt
        DCD     I2C2ERIntHandler            ; 34 I2C2 error interrupt
        DCD     SPI1IntHandler              ; 35 SPI1 global interrupt
        DCD     SPI2IntHandler              ; 36 SPI2 global interrupt
        DCD     USART1IntHandler            ; 37 USART1 global interrupt
        DCD     USART2IntHandler            ; 38 USART2 global interrupt
        DCD     USART3IntHandler            ; 39 USART3 global interrupt
        DCD     EXTI1510IntHandler          ; 40 EXTI Line[15:10] interrupts
        DCD     RTCAlarmIntHandler          ; 41 RTC alarm through EXTI line
        DCD     OTGFSWKUPIntHandler         ; 42 USB On-The-Go FS Wakeup
        DCD     TIM8BRKTIM12IntHandler      ; 43 TIM8 Break interrupt
        DCD     TIM8UPTIM13IntHandler       ; 44 TIM8 Update interrupt
        DCD     TIM8TRGCOMTIM14IntHandler   ; 45 TIM8 Trigger and Commutation
        DCD     TIM8CCIntHandler            ; 46 TIM8 Capture Compare interrupt
        DCD     ADC3IntHandler              ; 47 ADC3 global interrupt
        DCD     FSMCIntHandler              ; 48 FSMC global interrupt
        DCD     SDIOIntHandler              ; 49 SDIO global interrupt
        DCD     TIM5IntHandler              ; 50 TIM5 global interrupt
        DCD     SPI3IntHandler              ; 51 SPI3 global interrupt
        DCD     UART4IntHandler             ; 52 UART4 global interrupt
        DCD     UART5IntHandler             ; 53 UART5 global interrupt
        DCD     TIM6IntHandler              ; 54 TIM6 global interrupt
        DCD     TIM7IntHandler              ; 55 TIM7 global interrupt
        DCD     DMA2Channel1IntHandler      ; 56 DMA2 Channel1 global interrupt
        DCD     DMA2Channel2IntHandler      ; 57 DMA2 Channel2 global interrupt
        DCD     DMA2Channel3IntHandler      ; 58 DMA2 Channel3 global interrupt
        DCD     DMA2Channel4IntHandler      ; 59 DMA2 Channel4 global interrupt
        DCD     DMA2Channel5IntHandler      ; 60 DMA2 Channel5 global interrupt
        DCD     ETHIntHandler               ; 61 Ethernet global interrupt
        DCD     ETHWKUPIntHandler           ; 62 Ethernet Wakeup through EXTI line
        DCD     CAN2TXIntHandler            ; 63 CAN2 TX interrupts
        DCD     CAN2RX0IntHandler           ; 64 CAN2 RX0 interrupts
        DCD     CAN2RX1IntHandler           ; 65 CAN2 RX1 interrupt
        DCD     CAN2SCEIntHandler           ; 66 CAN2 SCE interrupt
        DCD     OTGFSIntHandler             ; 67 USB On The Go FS global interrupt
        DCD     0xF108F85F                  ; Boot in RAM mode                           

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
      PUBWEAK ResetHandler
      PUBWEAK NMIIntHandler       
      PUBWEAK HardFaultIntHandler 
      PUBWEAK MemManageIntHandler
      PUBWEAK BusFaultIntHandler
      PUBWEAK UsageFaultIntHandler
      PUBWEAK SVCIntHandler
      PUBWEAK DebugMonIntHandler
      PUBWEAK PendSVIntHandler
      PUBWEAK SysTickIntHandler
      PUBWEAK WWDGIntHandler  
      PUBWEAK PVDIntHandler  
      PUBWEAK TAMPERIntHandler
      PUBWEAK RTCIntHandler
      PUBWEAK FLASHIntHandler 
      PUBWEAK RCCIntHandler
      PUBWEAK EXTI0IntHandler 
      PUBWEAK EXTI1IntHandler 
      PUBWEAK EXTI2IntHandler 
      PUBWEAK EXTI3IntHandler 
      PUBWEAK EXTI4IntHandler 
      PUBWEAK DMA1Channel1IntHandler 
      PUBWEAK DMA1Channel2IntHandler
      PUBWEAK DMA1Channel3IntHandler
      PUBWEAK DMA1Channel4IntHandler 
      PUBWEAK DMA1Channel5IntHandler 
      PUBWEAK DMA1Channel6IntHandler 
      PUBWEAK DMA1Channel7IntHandler 
      PUBWEAK ADC12IntHandler 
      PUBWEAK CAN1TXIntHandler 
      PUBWEAK CAN1RX0IntHandler 
      PUBWEAK CAN1RX1IntHandler  
      PUBWEAK CAN1SCEIntHandler  
      PUBWEAK EXTI95IntHandler 
      PUBWEAK TIM1BRKTIM9IntHandler
      PUBWEAK TIM1UPTIM10IntHandler
      PUBWEAK TIM1TRGCOMTIM11IntHandler
      PUBWEAK TIM1CCIntHandler
      PUBWEAK TIM2IntHandler  
      PUBWEAK TIM3IntHandler 
      PUBWEAK TIM4IntHandler 
      PUBWEAK I2C1EVIntHandler 
      PUBWEAK I2C1ERIntHandler 
      PUBWEAK I2C2EVIntHandler 
      PUBWEAK I2C2ERIntHandler 
      PUBWEAK SPI1IntHandler 
      PUBWEAK SPI2IntHandler 
      PUBWEAK USART1IntHandler 
      PUBWEAK USART2IntHandler 
      PUBWEAK USART3IntHandler 
      PUBWEAK EXTI1510IntHandler 
      PUBWEAK RTCAlarmIntHandler 
      PUBWEAK OTGFSWKUPIntHandler
      PUBWEAK TIM8BRKTIM12IntHandler
      PUBWEAK TIM8UPTIM13IntHandler
      PUBWEAK TIM8TRGCOMTIM14IntHandler
      PUBWEAK TIM8CCIntHandler
      PUBWEAK ADC3IntHandler
      PUBWEAK FSMCIntHandler
      PUBWEAK SDIOIntHandler
      PUBWEAK TIM5IntHandler 
      PUBWEAK SPI3IntHandler 
      PUBWEAK UART4IntHandler 
      PUBWEAK UART5IntHandler 
      PUBWEAK TIM6IntHandler 
      PUBWEAK TIM7IntHandler 
      PUBWEAK DMA2Channel1IntHandler 
      PUBWEAK DMA2Channel2IntHandler 
      PUBWEAK DMA2Channel3IntHandler 
      PUBWEAK DMA2Channel4IntHandler 
      PUBWEAK DMA2Channel5IntHandler 
      PUBWEAK ETHIntHandler 
      PUBWEAK ETHWKUPIntHandler 
      PUBWEAK CAN2TXIntHandler 
      PUBWEAK CAN2RX0IntHandler 
      PUBWEAK CAN2RX1IntHandler 
      PUBWEAK CAN2SCEIntHandler 
      PUBWEAK OTGFSIntHandler     

        THUMB
        SECTION .text:CODE:REORDER(2)
ResetHandler

;****************************************** 
               LDR     R0, =__iar_program_start
               BX      R0
              SECTION .text:CODE:REORDER(2)
NMIIntHandler       
HardFaultIntHandler
        LDR    R0, [R13, #24]        ; Get previous PC
        LDRH   R1, [R0]              ; Get instruction
        LDR    R2, =0xBEAB           ; The sepcial BKPT instruction
        CMP    R1, R2                ; Test if the instruction at previous PC is BKPT
        BNE    HardFaultIntHandler_Ret ; Not BKPT

        ADDS   R0, #4                ; Skip BKPT and next line
        STR    R0, [R13, #24]        ; Save previous PC

        BX     LR
HardFaultIntHandler_Ret
        B      .

MemManageIntHandler
BusFaultIntHandler
UsageFaultIntHandler
SVCIntHandler
DebugMonIntHandler
PendSVIntHandler
SysTickIntHandler
WWDGIntHandler  
PVDIntHandler  
TAMPERIntHandler
RTCIntHandler
FLASHIntHandler 
RCCIntHandler
EXTI0IntHandler 
EXTI1IntHandler 
EXTI2IntHandler 
EXTI3IntHandler 
EXTI4IntHandler 
DMA1Channel1IntHandler 
DMA1Channel2IntHandler
DMA1Channel3IntHandler
DMA1Channel4IntHandler 
DMA1Channel5IntHandler 
DMA1Channel6IntHandler 
DMA1Channel7IntHandler 
ADC12IntHandler 
CAN1TXIntHandler 
CAN1RX0IntHandler 
CAN1RX1IntHandler  
CAN1SCEIntHandler  
EXTI95IntHandler 
TIM1BRKTIM9IntHandler
TIM1UPTIM10IntHandler
TIM1TRGCOMTIM11IntHandler
TIM1CCIntHandler
TIM2IntHandler  
TIM3IntHandler 
TIM4IntHandler 
I2C1EVIntHandler 
I2C1ERIntHandler 
I2C2EVIntHandler 
I2C2ERIntHandler 
SPI1IntHandler 
SPI2IntHandler 
USART1IntHandler 
USART2IntHandler 
USART3IntHandler 
EXTI1510IntHandler 
RTCAlarmIntHandler 
OTGFSWKUPIntHandler
TIM8BRKTIM12IntHandler
TIM8UPTIM13IntHandler
TIM8TRGCOMTIM14IntHandler
TIM8CCIntHandler
ADC3IntHandler
FSMCIntHandler
SDIOIntHandler
TIM5IntHandler 
SPI3IntHandler 
UART4IntHandler 
UART5IntHandler 
TIM6IntHandler 
TIM7IntHandler 
DMA2Channel1IntHandler 
DMA2Channel2IntHandler 
DMA2Channel3IntHandler 
DMA2Channel4IntHandler 
DMA2Channel5IntHandler 
ETHIntHandler 
ETHWKUPIntHandler 
CAN2TXIntHandler 
CAN2RX0IntHandler 
CAN2RX1IntHandler 
CAN2SCEIntHandler 
OTGFSIntHandler     
DefaultIntHandler          
        B DefaultIntHandler 
        
; int SH_DoCommand(int n32In_R0, int n32In_R1, int *pn32Out_R0);
; Input
;	R0,n32In_R0: semihost register 0
;	R1,n32In_R1: semihost register 1
; Output
;	R2,*pn32Out_R0: semihost register 0
; Return
;	0: No ICE debug
;	1: ICE debug
SH_DoCommand	
        EXPORT SH_DoCommand
        BKPT   0xAB                  ; Wait ICE or HardFault
                                     ; ICE will step over BKPT directly
                                     ; HardFault will step BKPT and the next line
        B      SH_ICE
SH_HardFault                         ; Captured by HardFault
        MOVS   R0, #0                ; Set return value to 0
        BX     lr                    ; Return
SH_ICE                               ; Captured by ICE
        ; Save return value
        CMP    R2, #0
        BEQ    SH_End
        STR    R0, [R2]              ; Save the return value to *pn32Out_R0
SH_End
        MOVS   R0, #1                ; Set return value to 1
        BX     lr                    ; Return

        END
