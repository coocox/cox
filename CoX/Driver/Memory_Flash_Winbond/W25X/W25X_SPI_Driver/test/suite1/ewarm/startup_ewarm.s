;//*****************************************************************************
;//
;//! \file startup_coide.c
;//! \brief NUC1xx Devices Startup code for EWARM.
;//!        This module performs:
;//!           - Set the initial SP
;//!           - Set the vector table entries with the exceptions ISR address
;//!           - Initialize data and bss
;//!           - Setup the microcontroller system. 			
;//!           - Call the application's entry point.
;//!           .
;//! \version 1.0
;//! \date 8/13/2011
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
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)                 ; Top of Stack
        DCD     ResetHandler                ; Reset Handler
        DCD     NMIIntHandler               ; NMI Handler
        DCD     HardFaultIntHandler         ; Hard Fault Handler
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVCIntHandler               ; SVCall Handler
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     PendSVIntHandler            ; PendSV Handler
        DCD     SysTickIntHandler           ; SysTick Handler
        
                                            ; External Interrupts

        DCD     BODIntHandler               ; Brownout low voltage detected interrupt                 
        DCD     WDTIntHandler               ; Watch Dog Timer interrupt                              
        DCD     EINT0IntHandler             ; External signal interrupt from PB.14 pin                
        DCD     EINT1IntHandler             ; External signal interrupt from PB.15 pin                
        DCD     GPABIntHandler              ; External signal interrupt from PA[15:0] / PB[13:0]     
        DCD     GPCDEIntHandler             ; External interrupt from PC[15:0]/PD[15:0]/PE[15:0]     
        DCD     PWMAIntHandler              ; PWM0 or PWM2 interrupt                                 
        DCD     PWMBIntHandler              ; PWM1 or PWM3 interrupt                                 
        DCD     TIMER0IntHandler            ; Timer 0 interrupt                                      
        DCD     TIMER1IntHandler            ; Timer 1 interrupt                                      
        DCD     TIMER2IntHandler            ; Timer 2 interrupt                                      
        DCD     TIMER3IntHandler            ; Timer 3 interrupt                                      
        DCD     UART02IntHandler            ; UART0 interrupt                                        
        DCD     UART1IntHandler             ; UART1 interrupt                                        
        DCD     SPI0IntHandler              ; SPI0 interrupt                                         
        DCD     SPI1IntHandler              ; SPI1 interrupt                                         
        DCD     SPI2IntHandler              ; SPI2 interrupt                                         
        DCD     SPI3IntHandler              ; SPI3 interrupt                                         
        DCD     I2C0IntHandler              ; I2C0 interrupt                                         
        DCD     I2C1IntHandler              ; I2C1 interrupt                                         
        DCD     CAN0IntHandler              ; CAN0 interrupt                                         
        DCD     DefaultIntHandler           ; Reserved                                         
        DCD     DefaultIntHandler           ; Reserved
        DCD     USBDIntHandler              ; USB FS Device interrupt                                
        DCD     PS2IntHandler               ; PS2 interrupt                                          
        DCD     ACMPIntHandler              ; Analog Comparator-0 or Comaprator-1 interrupt          
        DCD     PDMAIntHandler              ; PDMA interrupt  
        DCD     I2SIntHandler               ; I2S interrupt
        DCD     PWRWUIntHandler             ; Clock controller interrupt for chip wake up from power-
        DCD     ADCIntHandler               ; ADC interrupt                                          
        DCD     DefaultIntHandler           ; Reserved
        DCD     RTCIntHandler               ; Real time clock interrupt                              

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
      PUBWEAK ResetHandler
      PUBWEAK NMIIntHandler       
      PUBWEAK HardFaultIntHandler 
      PUBWEAK SVCIntHandler       
      PUBWEAK PendSVIntHandler    
      PUBWEAK SysTickIntHandler   
      PUBWEAK BODIntHandler   
      PUBWEAK WDTIntHandler   
      PUBWEAK EINT0IntHandler 
      PUBWEAK EINT1IntHandler 
      PUBWEAK GPABIntHandler  
      PUBWEAK GPCDEIntHandler 
      PUBWEAK PWMAIntHandler  
      PUBWEAK PWMBIntHandler  
      PUBWEAK TIMER0IntHandler  
      PUBWEAK TIMER1IntHandler  
      PUBWEAK TIMER2IntHandler  
      PUBWEAK TIMER3IntHandler  
      PUBWEAK UART02IntHandler 
      PUBWEAK UART1IntHandler 
      PUBWEAK SPI0IntHandler  
      PUBWEAK SPI1IntHandler  
      PUBWEAK SPI2IntHandler  
      PUBWEAK SPI3IntHandler  
      PUBWEAK I2C0IntHandler  
      PUBWEAK I2C1IntHandler  
      PUBWEAK CAN0IntHandler   
      PUBWEAK USBDIntHandler   
      PUBWEAK PS2IntHandler   
      PUBWEAK ACMPIntHandler  
      PUBWEAK PDMAIntHandler 
      PUBWEAK I2SIntHandler
      PUBWEAK PWRWUIntHandler  
      PUBWEAK ADCIntHandler    
      PUBWEAK RTCIntHandler    

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

SVCIntHandler       
PendSVIntHandler    
SysTickIntHandler   
BODIntHandler   
WDTIntHandler   
EINT0IntHandler 
EINT1IntHandler 
GPABIntHandler  
GPCDEIntHandler 
PWMAIntHandler  
PWMBIntHandler  
TIMER0IntHandler  
TIMER1IntHandler  
TIMER2IntHandler  
TIMER3IntHandler  
UART02IntHandler 
UART1IntHandler 
SPI0IntHandler  
SPI1IntHandler  
SPI2IntHandler  
SPI3IntHandler  
I2C0IntHandler  
I2C1IntHandler  
CAN0IntHandler  
USBDIntHandler   
PS2IntHandler   
ACMPIntHandler  
PDMAIntHandler  
I2SIntHandler
PWRWUIntHandler
ADCIntHandler    
RTCIntHandler    
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
