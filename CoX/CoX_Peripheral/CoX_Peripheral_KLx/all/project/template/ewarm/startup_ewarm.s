;//*****************************************************************************
;//
;//! \file startup_coide.c
;//! \brief Cortex-M0/M3 Devices Startup code for EWARM.
;//!        This module performs:
;//!           - Set the initial SP
;//!           - Set the vector table entries with the exceptions ISR address
;//!           - Initialize data and bss		
;//!           - Call the application's entry point.
;//!           .
;//! \version V2.1.1.0
;//! \date 11/14/2011
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
        
        DCD     DMA0IntHandler             ; DMA channel 0 transfer complete and error handler
        DCD     DMA1IntHandler             ; DMA channel 1 transfer complete and error handler
        DCD     DMA2IntHandler             ; DMA channel 2 transfer complete and error handler
        DCD     DMA3IntHandler             ; DMA channel 3 transfer complete and error handler
        DCD     0        
        DCD     FTFAIntHandler             ; Command complete and read collision
        DCD     LVDIntHandler              ; Low-voltage detect, low-voltage warning
        DCD     LLWUIntHandler             ; Low Leakage Wakeup
        DCD     I2C0IntHandler             ; I2C0 handler
        DCD     I2C1IntHandler             ; I2C1 handler
        DCD     SPI0IntHandler             ; SPI0 handler
        DCD     SPI1IntHandler             ; SPI1 handler
        DCD     UART0SEIntHandler          ; UART0SE handler
        DCD     UART1SEIntHandler          ; UART1SE handler
        DCD     UART2SEIntHandler          ; UART2SE handler
        DCD     ADCIntHandler              ; ADC handler
        DCD     ACMPIntHandler             ; ACMP handler
        DCD     FTM0IntHandler             ; FTM0 handler
        DCD     FTM1IntHandler             ; FTM1 handler
        DCD     FTM2IntHandler             ; FTM2 handler
        DCD     RTCAIntHandler             ; RTCA handler
        DCD     RTCSIntHandler             ; RTCS handler
        DCD     PITIntHandler              ; PIT handler
        DCD     0 
        DCD     USBOTGIntHandler           ; USBOTG handler
        DCD     DACIntHandler              ; DAC handler
        DCD     TSIIntHandler              ; TSI handler
        DCD     MCGIntHandler              ; MCG handler
        DCD     LPTMRIntHandler            ; PIT handler 
        DCD     0 
        DCD     PORTAIntHandler            ; PORTA handler
        DCD     PORTDIntHandler            ; PORTD handler
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved    
        DCD     0xffffffff                  ; CONFIG_1
        DCD     0xffffffff                  ; CONFIG_2
        DCD     0xffffffff                  ; CONFIG_3
        DCD     0xfffffffe                  ; CONFIG_4
                                     

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
      PUBWEAK DMA0IntHandler
      PUBWEAK DMA1IntHandler
      PUBWEAK DMA2IntHandler
      PUBWEAK DMA3IntHandler
      PUBWEAK FTFAIntHandler
      PUBWEAK LVDIntHandler
      PUBWEAK LLWUIntHandler
      PUBWEAK I2C0IntHandler
      PUBWEAK I2C1IntHandler
      PUBWEAK SPI0IntHandler
      PUBWEAK SPI1IntHandler
      PUBWEAK UART0SEIntHandler
      PUBWEAK UART1SEIntHandler
      PUBWEAK UART2SEIntHandler
      PUBWEAK ADCIntHandler
      PUBWEAK ACMPIntHandler
      PUBWEAK FTM0IntHandler
      PUBWEAK FTM1IntHandler
      PUBWEAK FTM2IntHandler
      PUBWEAK RTCAIntHandler
      PUBWEAK RTCSIntHandler
      PUBWEAK PITIntHandler
      PUBWEAK USBOTGIntHandler
      PUBWEAK DACIntHandler
      PUBWEAK TSIIntHandler
      PUBWEAK MCGIntHandler
      PUBWEAK LPTMRIntHandler
      PUBWEAK PORTAIntHandler
      PUBWEAK PORTDIntHandler  

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
DefaultIntHandler
DMA0IntHandler
DMA1IntHandler
DMA2IntHandler
DMA3IntHandler
FTFAIntHandler
LVDIntHandler
LLWUIntHandler
I2C0IntHandler
I2C1IntHandler
SPI0IntHandler
SPI1IntHandler
UART0SEIntHandler
UART1SEIntHandler
UART2SEIntHandler
ADCIntHandler
ACMPIntHandler
FTM0IntHandler
FTM1IntHandler
FTM2IntHandler
RTCAIntHandler
RTCSIntHandler
PITIntHandler
USBOTGIntHandler
DACIntHandler
TSIIntHandler
MCGIntHandler
LPTMRIntHandler
PORTAIntHandler
PORTDIntHandler          
        B DefaultIntHandler 
        

        END
