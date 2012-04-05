;//*****************************************************************************
;//
;//! \file startup_ewarm.s
;//! \brief HT32F125x Devices Startup code for EWARM.
;//!        This module performs:
;//!           - Set the initial SP
;//!           - Set the vector table entries with the exceptions ISR address
;//!           - Initialize data and bss
;//!           - Setup the microcontroller system.
;//!           - Call the application's entry point.
;//!           .
;//! \version V2.1.1.0
;//! \date 2/21/2012
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
        DCD     MemManageIntHandler         ; Memory Management Fault Handler
        DCD     BusFaultIntHandler          ; Bus Fault Handler
        DCD     UsageFaultIntHandler        ; Usage Fault Handler
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVCIntHandler               ; SVCall Handler
        DCD     DebugMonIntHandler          ; Debug Monitor Handler
        DCD     0                           ; Reserved
        DCD     PendSVIntHandler            ; PendSV Handler
        DCD     SysTickIntHandler           ; SysTick Handler
        
                                            ; External Interrupts

        DCD     CKRDYIntHandler             ; Clock ready interrupt(HSE,HSI,LSE,LSI or PLL)
        DCD     LVDIntHandler               ; Low voltage detection interrupt
        DCD     BODIntHandler               ; Brownout low voltage detected interrupt
        DCD     WDTIntHandler               ; Watch Dog Timer interrupt
        DCD     RTCIntHandler               ; RTC global interrupt
        DCD     FMCIntHandler               ; FMC global interrupt
        DCD     EVWUPIntHandler             ; EXTI Event wakeup interrupt
        DCD     LPWUPIntHandler             ; WAKEUP pin interrupt
        DCD     EINT0IntHandler             ; EXTI Line 0 interrupt
        DCD     EINT1IntHandler             ; EXTI Line 1 interrupt
        DCD     EINT2IntHandler             ; EXTI Line 2 interrupt
        DCD     EINT3IntHandler             ; EXTI Line 3 interrupt
        DCD     EINT4IntHandler             ; EXTI Line 4 interrupt
        DCD     EINT5IntHandler             ; EXTI Line 5 interrupt
        DCD     EINT6IntHandler             ; EXTI Line 6 interrupt
        DCD     EINT7IntHandler             ; EXTI Line 7 interrupt
        DCD     EINT8IntHandler             ; EXTI Line 8 interrupt
        DCD     EINT9IntHandler             ; EXTI Line 9 interrupt
        DCD     EINT10IntHandler            ; EXTI Line 10 interrupt
        DCD     EINT11IntHandler            ; EXTI Line 11 interrupt
        DCD     EINT12IntHandler            ; EXTI Line 12 interrupt
        DCD     EINT13IntHandler            ; EXTI Line 13 interrupt
        DCD     EINT14IntHandler            ; EXTI Line 14 interrupt
        DCD     EINT15IntHandler            ; EXTI Line 15 interrupt
        DCD     COMPIntHandler              ; Comparator global interrupt
        DCD     ADCIntHandler               ; ADC interrupt
        DCD     DefaultIntHandler           ; Reserved
        DCD     DefaultIntHandler           ; Reserved
        DCD     DefaultIntHandler           ; Reserved
        DCD     DefaultIntHandler           ; Reserved
        DCD     DefaultIntHandler           ; Reserved
        DCD     DefaultIntHandler           ; Reserved
        DCD     DefaultIntHandler           ; Reserved
        DCD     DefaultIntHandler           ; Reserved
        DCD     DefaultIntHandler           ; Reserved
        DCD     GTTM0IntHandler             ; GPTM0 global interrupt
        DCD     GTTM1IntHandler             ; GPTM1 global interrupt
        DCD     DefaultIntHandler           ; Reserved
        DCD     DefaultIntHandler           ; Reserved
        DCD     DefaultIntHandler           ; Reserved
        DCD     DefaultIntHandler           ; Reserved
        DCD     DefaultIntHandler           ; Reserved
        DCD     DefaultIntHandler           ; Reserved
        DCD     I2C0IntHandler              ; I2C global interrupt
        DCD     DefaultIntHandler           ; Reserved
        DCD     SPI0IntHandler              ; SPI0 global interrupt
        DCD     DefaultIntHandler           ; Reserved
        DCD     UART0IntHandler             ; UART0 global interrupt

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
      PUBWEAK CKRDYIntHandler
      PUBWEAK LVDIntHandler
      PUBWEAK BODIntHandler
      PUBWEAK WDTIntHandler
      PUBWEAK RTCIntHandler
      PUBWEAK FMCIntHandler
      PUBWEAK EVWUPIntHandler
      PUBWEAK LPWUPIntHandler
      PUBWEAK EINT0IntHandler
      PUBWEAK EINT1IntHandler
      PUBWEAK EINT2IntHandler
      PUBWEAK EINT3IntHandler
      PUBWEAK EINT4IntHandler
      PUBWEAK EINT5IntHandler
      PUBWEAK EINT6IntHandler
      PUBWEAK EINT7IntHandler
      PUBWEAK EINT8IntHandler
      PUBWEAK EINT9IntHandler
      PUBWEAK EINT10IntHandler
      PUBWEAK EINT11IntHandler
      PUBWEAK EINT12IntHandler
      PUBWEAK EINT13IntHandler
      PUBWEAK EINT14IntHandler
      PUBWEAK EINT15IntHandler
      PUBWEAK COMPIntHandler
      PUBWEAK ADCIntHandler
      PUBWEAK GTTM0IntHandler
      PUBWEAK GTTM1IntHandler
      PUBWEAK I2C0IntHandler
      PUBWEAK SPI0IntHandler
      PUBWEAK UART0IntHandler

        THUMB
        SECTION .text:CODE:REORDER(2)
ResetHandler

;****************************************** 
               LDR     R0, =__iar_program_start
               BX      R0
              SECTION .text:CODE:REORDER(2)
NMIIntHandler
HardFaultIntHandler
        LDR    R0, [R13, #24]          ; Get previous PC
        LDRH   R1, [R0]                ; Get instruction
        LDR    R2, =0xBEAB             ; The sepcial BKPT instruction
        CMP    R1, R2                  ; Test if the instruction at previous PC is BKPT
        BNE    HardFaultIntHandler_Ret ; Not BKPT

        ADDS   R0, #4                  ; Skip BKPT and next line
        STR    R0, [R13, #24]          ; Save previous PC

        BX     LR
HardFaultIntHandler_Ret
        B      .

SVCIntHandler
DebugMonIntHandler
PendSVIntHandler
SysTickIntHandler
CKRDYIntHandler
LVDIntHandler
BODIntHandler
WDTIntHandler
RTCIntHandler
FMCIntHandler
EVWUPIntHandler
LPWUPIntHandler
EINT0IntHandler
EINT1IntHandler
EINT2IntHandler
EINT3IntHandler
EINT4IntHandler
EINT5IntHandler
EINT6IntHandler
EINT7IntHandler
EINT8IntHandler
EINT9IntHandler
EINT10IntHandler
EINT11IntHandler
EINT12IntHandler
EINT13IntHandler
EINT14IntHandler
EINT15IntHandler
COMPIntHandler
ADCIntHandler
GTTM0IntHandler
GTTM1IntHandler
I2C0IntHandler
SPI0IntHandler
UART0IntHandler
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